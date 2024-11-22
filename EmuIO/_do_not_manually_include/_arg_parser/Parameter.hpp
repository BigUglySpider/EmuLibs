#ifndef EMU_IO_ARG_PARSER_PARAMETER_HPP_INC_
#define EMU_IO_ARG_PARSER_PARAMETER_HPP_INC_ 1

#include <cstdint>
#include <limits>
#include <optional>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_set>
#include <utility>
#include <variant>

#include "../../../EmuCore/CommonConcepts/CommonRequirements.h"
#include "../../../EmuCore/TMPHelpers/OperatorChecks.h"
#include "../../../EmuCore/TMPHelpers/VariadicHelpers.h"

#include "ParameterType.hpp"

namespace EmuIO
{
	template<ParameterType Type>
	struct parameter_enum_builder_arg
	{
	private:
		[[nodiscard]] static constexpr auto get() noexcept
		{
			if constexpr ((Type & ParameterType::Enum) == ParameterType::Enum)
			{
				if constexpr ((Type & ParameterType::ValueTypeMask) == ParameterType::String)
				{
					return std::string{};
				}
				else
				{
					return std::pair<std::string, typename parameter_type_value<Type>::type>{};
				}
			}
			else
			{
				return std::tuple<>{};
			}
		}

	public:
		using type = decltype(get());
	};

	template<ParameterType Type, class...ScalarArgs>
	struct valid_scalar_args_for_enum_builder_arg
	{
		static constexpr bool value{ false };
	};
	template<ParameterType Type, class FirstScalarArg>
	requires((Type & ParameterType::ValueTypeMask) == ParameterType::String)
	struct valid_scalar_args_for_enum_builder_arg<Type, FirstScalarArg>
	{
		static constexpr bool value{ std::is_constructible_v<std::string, FirstScalarArg> };
	};
	template<ParameterType Type, class FirstScalarArg, class...RemainingScalarArgs>
	requires((Type & ParameterType::ValueTypeMask) == ParameterType::String)
	struct valid_scalar_args_for_enum_builder_arg<Type, FirstScalarArg, RemainingScalarArgs...>
	{
		static constexpr bool value{ std::is_constructible_v<std::string, FirstScalarArg> && (... && std::is_constructible_v<std::string, RemainingScalarArgs>) };
	};
	template<ParameterType Type, class NameArg, class ValueArg>
	requires((Type & ParameterType::ValueTypeMask) != ParameterType::String)
	struct valid_scalar_args_for_enum_builder_arg<Type, NameArg, ValueArg>
	{
		static constexpr bool value{ std::is_constructible_v<typename parameter_enum_builder_arg<Type | ParameterType::Enum>::type, NameArg, ValueArg> };
	};
	template<ParameterType Type, class NameArg, class ValueArg, class...RemainingArgs>
	requires((Type & ParameterType::ValueTypeMask) != ParameterType::String)
	struct valid_scalar_args_for_enum_builder_arg<Type, NameArg, ValueArg, RemainingArgs...>
	{
		static constexpr bool value{ valid_scalar_args_for_enum_builder_arg<Type, NameArg, ValueArg>::value && valid_scalar_args_for_enum_builder_arg<Type, RemainingArgs...>::value };
	};

	class Parameter
	{
	public:
		using value_type = std::variant
		<
			std::monostate,
			std::int8_t, std::int16_t, std::int32_t, std::int64_t,
			std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t,
			float, double,
			std::string,
			bool
		>;
		using enum_info_type = std::variant
		<
			std::monostate,
			std::string,
			std::pair<std::string, value_type>
		>;

		Parameter() = delete;
		Parameter(const Parameter&) = delete;
		Parameter& operator=(const Parameter&) = delete;

		Parameter(Parameter&& to_move) noexcept :
			values{ std::move(to_move.values) },
			inputs{ std::move(to_move.inputs) },
			default_value{ std::move(to_move.default_value) },
			type{ to_move.type },
			enum_info{ std::move(to_move.enum_info) },
			default_enum_info{ std::move(to_move.default_enum_info) },
			current_enum_info{ std::move(to_move.current_enum_info) },
			modified{ to_move.modified }
		{
		}

		Parameter& operator=(Parameter&& to_move) noexcept
		{
			values = std::move(to_move.values);
			inputs = std::move(to_move.inputs);
			default_value = std::move(to_move.default_value);
			type = to_move.type;
			enum_info = std::move(to_move.enum_info);
			default_enum_info = std::move(to_move.default_enum_info);
			current_enum_info = std::move(to_move.current_enum_info);
			modified = to_move.modified;
			return *this;
		}

		template<ParameterType ParamType, class DefaultValue>
		requires((ParamType & ParameterType::Enum) != ParameterType::Enum)
		[[nodiscard]] static Parameter make(DefaultValue&& default_value_)
		{
			if constexpr (EmuConcepts::UnqualifiedMatch<DefaultValue, std::monostate>)
			{
				static_assert
				(
					(ParamType & ParameterType::Array) == ParameterType::Array,
					"Invalid construction args provided for the specified ParameterType: `std::monostate` was provided, but this is only valid for ParameterTypes where the `Array` bit is enabled."
				);
			}
			else
			{
				constexpr bool valid_construction{ valid_construction_args_for_param_type<DefaultValue>(ParamType) };
				static_assert(valid_construction, "Invalid construction args provided for the specified ParameterType.");
			}
			return Parameter(ParamType, std::forward<DefaultValue>(default_value_));
		}

		template<ParameterType ParamType, class...EnumInfoSets>
		requires((ParamType & ParameterType::Enum) == ParameterType::Enum && sizeof...(EnumInfoSets) != 0 && !(... && EmuConcepts::CanExplicitlyConstruct<EnumInfoSets, typename EmuIO::parameter_enum_builder_arg<ParamType>::type>))
		[[nodiscard]] static Parameter make(std::string default_enum_, EnumInfoSets&&...enum_singles_or_pairs)
		{
			constexpr std::size_t enum_info_args_count{ sizeof...(EnumInfoSets) };
			constexpr bool uses_string_values{ (ParamType & ParameterType::ValueTypeMask) == ParameterType::String };
			constexpr std::size_t per_info_item_count{ uses_string_values ? 1 : 2 };
			static_assert
			(
				(enum_info_args_count % per_info_item_count) == 0,
				"Invalid number of arguments for creating the enum info for a parameter: The input must come in sequential order of strings and values for each potential value if the value type of the parameter is `String`; otherwise there must be 1 string (and nothing else) for each potential value."
			);

			if constexpr (uses_string_values)
			{
				static_assert
				(
					(... && EmuConcepts::CanExplicitlyConstruct<EnumInfoSets, std::string>),
					"Invalid arguments passed for creating a string enum parameter: At least one argument is not a valid type to construct `std::string`."
				);
				return Parameter(ParamType, std::move(default_enum_), std::string{ std::forward<EnumInfoSets>(enum_singles_or_pairs) }...);
			}
			else
			{
				return _underlying_make_enum_type_with_pairs<ParamType>
				(
					std::move(default_enum_),
					std::forward_as_tuple<EnumInfoSets&&...>(std::forward<EnumInfoSets>(enum_singles_or_pairs)...),
					EmuCore::TMP::make_even_index_sequence<enum_info_args_count>(),
					EmuCore::TMP::make_odd_index_sequence<enum_info_args_count>()
				);
			}
		}

		template<ParameterType ParamType, class...EnumInfoSets>
		requires((ParamType & ParameterType::Enum) == ParameterType::Enum && (ParamType & ParameterType::Array) == ParameterType::Array && sizeof...(EnumInfoSets) != 0 && !(... && EmuConcepts::CanExplicitlyConstruct<EnumInfoSets, typename EmuIO::parameter_enum_builder_arg<ParamType>::type>))
		[[nodiscard]] static Parameter make(std::monostate default_enum_, EnumInfoSets&&...enum_singles_or_pairs)
		{
			constexpr std::size_t enum_info_args_count{ sizeof...(EnumInfoSets) };
			constexpr bool uses_string_values{ (ParamType & ParameterType::ValueTypeMask) == ParameterType::String };
			constexpr std::size_t per_info_item_count{ uses_string_values ? 1 : 2 };
			static_assert
			(
				(enum_info_args_count % per_info_item_count) == 0,
				"Invalid number of arguments for creating the enum info for a parameter: The input must come in sequential order of strings and values for each potential value if the value type of the parameter is `String`; otherwise there must be 1 string (and nothing else) for each potential value."
			);

			if constexpr (uses_string_values)
			{
				static_assert
				(
					(... && EmuConcepts::CanExplicitlyConstruct<EnumInfoSets, std::string>),
					"Invalid arguments passed for creating a string enum parameter: At least one argument is not a valid type to construct `std::string`."
				);
				return Parameter(ParamType, std::move(default_enum_), std::string{ std::forward<EnumInfoSets>(enum_singles_or_pairs) }...);
			}
			else
			{
				return _underlying_make_enum_type_with_pairs<ParamType>
				(
					std::move(default_enum_),
					std::forward_as_tuple<EnumInfoSets&&...>(std::forward<EnumInfoSets>(enum_singles_or_pairs)...),
					EmuCore::TMP::make_even_index_sequence<enum_info_args_count>(),
					EmuCore::TMP::make_odd_index_sequence<enum_info_args_count>()
				);
			}
		}

		template<ParameterType ParamType, class...EnumInfos>
		requires((ParamType & ParameterType::Enum) == ParameterType::Enum && sizeof...(EnumInfos) != 0 && (... && EmuConcepts::CanExplicitlyConstruct<EnumInfos, typename EmuIO::parameter_enum_builder_arg<ParamType>::type>))
		[[nodiscard]] static Parameter make(std::string default_enum_, EnumInfos&&...enum_infos_)
		{
			return Parameter(ParamType, std::move(default_enum_), std::forward<EnumInfos>(enum_infos_)...);
		}

		template<ParameterType ParamType, class...EnumInfos>
		requires((ParamType& ParameterType::Enum) == ParameterType::Enum && (ParamType & ParameterType::Array) == ParameterType::Array && sizeof...(EnumInfos) != 0 && (... && EmuConcepts::CanExplicitlyConstruct<EnumInfos, typename EmuIO::parameter_enum_builder_arg<ParamType>::type>))
		[[nodiscard]] static Parameter make(std::monostate default_enum_, EnumInfos&&...enum_infos_)
		{
			return Parameter(ParamType, std::move(default_enum_), std::forward<EnumInfos>(enum_infos_)...);
		}

		[[nodiscard]] constexpr const value_type& GetDefault() const noexcept
		{
			return default_value;
		}
		template<class Out>
		[[nodiscard]] const Out& GetDefault() const
		{
			return std::get<Out>(default_value);
		}

		[[nodiscard]] const value_type& GetValue() const noexcept
		{
			return values.back();
		}
		template<class Out>
		[[nodiscard]] const Out& GetValue() const
		{
			return std::get<Out>(values.back());
		}

		[[nodiscard]] const std::vector<value_type>& GetAllValues() const noexcept
		{
			return values;
		}
		template<class Out>
		[[nodiscard]] std::vector<const Out*> GetAllValues() const
		{
			std::vector<const Out*> value_pointers{};
			value_pointers.reserve(values.size());
			for (std::size_t i{ 0u }, end{ values.size() }; i < end; ++i)
			{
				value_pointers.emplace_back(&(std::get<Out>(values[i])));
			}
			return value_pointers;
		}

		[[nodiscard]] const std::string& GetInput() const noexcept
		{
			return inputs.back();
		}

		[[nodiscard]] constexpr const std::vector<std::string>& GetAllInputs() const noexcept
		{
			return inputs;
		}

		[[nodiscard]] constexpr ParameterType GetType() const noexcept
		{
			return type;
		}

		/*
		* @brief Parses the input string and appends it as the most recent value for this parameter.
		*        If this is an array parameter: Adds the parsed value to the end of its values array.
		*        If this is a scalar parameter: Replaces the current value with the parsed value.
		*        If this is a const parameter: Returns an error if the value has already been modified.
		* @param input_ String to parse as this paramter's value type and apply as described.
		* @returns Optional string describing the error if one occurs.
		*          On success, this will not have a value (`std::nullopt`).
		*/
		template<bool InArrayMode = false>
		std::optional<std::string> AppendInput(std::string input_)
		{
			if (IsConst() && modified)
			{
				return _make_err_str("Input value `", input_, "` is ignored for parameter (of type ", arg_param_type_to_string(type),
									 ") as its target parameter is flagged as constant and has already been set.");
			}

			if constexpr (!InArrayMode)
			{
				// Don't do special parsing if we're not even an array param
				if (IsArray() && input_.starts_with('[') && input_.ends_with(']'))
				{
					// Array mode
					input_ = input_.substr(1, input_.size() - 2);
					if (input_.empty())
					{
						return _make_err_str("Input value `", input_, "` is an empty array and thus has not changed anything.");
					}

					using namespace std::string_view_literals;
					constexpr std::string_view separator{ ","sv };
					std::string err_str{};
					std::size_t search_offset{ 0u };
					std::size_t current_begin{ 0u };
					do
					{
						std::size_t separator_i{ input_.find(separator, search_offset) };
						if (separator_i == std::string::npos)
						{
							std::string this_value = _array_substr(input_, current_begin);
							std::optional<std::string> current_err{ AppendInput<true>(this_value) };
							if (current_err.has_value())
							{
								if (!err_str.empty()) err_str += '\n';
								err_str += (std::move(*current_err));
							}
							break;
						}
						else if (separator_i == 0)
						{
							// Just an empty string; we won't disallow this as it could have some meaning for some implementation
							std::optional<std::string> current_err{ AppendInput<true>("") };
							if (current_err.has_value())
							{
								if (!err_str.empty()) err_str += '\n';
								err_str += (std::move(*current_err));
							}
							++search_offset;
							++current_begin;
							continue;
						}
						else
						{
							if (input_[separator_i - 1] == '\\')
							{
								const std::size_t escape_index{ separator_i - 1 };
								if (escape_index > 0 && input_[escape_index - 1] == '\\')
								{
									// Do not use the backslash to escape the separator since the users seems to want it as part of the string
									// --- This means this separator is valid so we don't move to a new loop iteration here
									// --- We want to erase one backslash since that's what we're escaping, and this will offset `separator_i` by -1
									input_.erase(escape_index);
									--separator_i;
								}
								else
								{
									// Skip this separator as its escaped and thus part of the input
									input_.erase(escape_index);
									search_offset = separator_i + (separator.size() - 1); // this will be the character after the escaped separator since its preceding char is gone now
									continue;
								}
							}

							std::string this_value = _array_substr(input_, current_begin, separator_i - current_begin);
							std::optional<std::string> current_err{ AppendInput<true>(this_value) };
							if (current_err.has_value())
							{
								if (!err_str.empty()) err_str += '\n';
								err_str += (std::move(*current_err));
							}
							search_offset = separator_i + separator.size();
							current_begin = search_offset;
						}
					} while (true); // Broken manually inside loop when there are no more separators

					if (err_str.empty())
					{
						return std::nullopt;
					}
					else
					{
						return std::move(err_str);
					}
				}
				else if (input_.starts_with("\\["))
				{
					input_ = input_.substr(1);
				}
			}

			std::optional<std::string> err{ std::nullopt };
			value_type new_item = _parse_input(input_, err);
			if (new_item.index() != 0) // Index 0 = monostate, translating to failure
			{
				if ((type & ParameterType::Array) == ParameterType::Array)
				{
					if (!modified)
					{
						// Empty the array if this is the first parse since we don't want the defaults present anymore
						// --- Especially considering having an empty monostate at the start on any array would be a little odd
						values.clear();
						inputs.clear();
					}
					values.emplace_back(std::move(new_item));
					inputs.emplace_back(std::move(input_));
				}
				else
				{
					values[0] = std::move(new_item);
					inputs[0] = std::move(input_);
				}
				modified = true;
			}
			return err;
		}

		[[nodiscard]] constexpr bool IsArray() const noexcept
		{
			return (type & ParameterType::Array) == ParameterType::Array;
		}

		[[nodiscard]] constexpr bool IsConst() const noexcept
		{
			return (type & ParameterType::Const) == ParameterType::Const;
		}

		[[nodiscard]] constexpr bool IsEnum() const noexcept
		{
			return (type & ParameterType::Enum) == ParameterType::Enum;
		}

		[[nodiscard]] std::string_view GetEnumString() const
		{
			if (!IsEnum())
			{
				throw _make_exception<std::runtime_error>("Attempted to access the enum string of a parameter whose type does not use enums (", arg_param_type_to_string(type), ')');
			}
			return get_enum_string_from_enum_info(current_enum_info.back());
		}

		[[nodiscard]] std::vector<std::string_view> GetAllEnumStringsArray() const
		{
			if (IsArray() && current_enum_info.back() == nullptr)
			{
				return std::vector<std::string_view>{};
			}

			std::vector<std::string_view> result{};
			result.reserve(current_enum_info.size());
			for (size_t i{ 0u }; i < current_enum_info.size(); ++i)
			{
				auto* const this_enum_info{ current_enum_info[i] };
				if (this_enum_info)
				{
					result[i] = get_enum_string_from_enum_info(this_enum_info);
				}
				else
				{
					using namespace std::string_view_literals;
					result[i] = "null"sv;
				}
			}
			return result;
		}

		[[nodiscard]] std::string_view GetDefaultEnumString() const
		{
			if (!IsEnum())
			{
				throw _make_exception<std::runtime_error>("Attempted to access the default enum string of a parameter whose type does not use enums (", arg_param_type_to_string(type), ')');
			}

			return get_enum_string_from_enum_info(default_enum_info);
		}

		template<bool Indent = false>
		void AppendValidEnumStringsToStream(std::ostream& str) const
		{
			if (!IsEnum())
			{
				return;
			}

			size_t const num_valid_enums{ enum_info.size() };
			if (num_valid_enums <= 0)
			{
				return;
			}

			if constexpr (Indent)
			{
				str << '\t';
			}
			_append_enum_info_to_stream(str, &(enum_info[0]));
			if (num_valid_enums != 1)
			{
				size_t i{ 1u };
				do
				{
					str << '\n';
					if constexpr (Indent)
					{
						str << '\t';
					}
					_append_enum_info_to_stream(str, &(enum_info[i]));
				} while ((++i) < num_valid_enums);
			}
		}

		template<bool ReturnResult, class Func>
		requires(EmuIO::is_valid_function_for_any_possible_param_value<Func, ReturnResult, false>())
		[[nodiscard]] constexpr decltype(auto) UseMostRecentValue(Func&& func) const
		{
			switch (type & ParameterType::ValueTypeMask)
			{
			case ParameterType::Bool:
				if constexpr (ReturnResult) { return std::forward<Func>(func)(std::get<bool>(values.back())); }
				else { std::forward<Func>(func)(std::get<bool>(values.back())); }
				break;
			case ParameterType::Int8:
				if constexpr (ReturnResult) { return std::forward<Func>(func)(std::get<std::int8_t>(values.back())); }
				else                        { std::forward<Func>(func)(std::get<std::int8_t>(values.back())); }
				break;
			case ParameterType::Int16:
				if constexpr (ReturnResult) { return std::forward<Func>(func)(std::get<std::int16_t>(values.back())); }
				else                        { std::forward<Func>(func)(std::get<std::int16_t>(values.back())); }
				break;
			case ParameterType::Int32:
				if constexpr (ReturnResult) { return std::forward<Func>(func)(std::get<std::int32_t>(values.back())); }
				else                        { std::forward<Func>(func)(std::get<std::int32_t>(values.back())); }
				break;
			case ParameterType::Int64:
				if constexpr (ReturnResult) { return std::forward<Func>(func)(std::get<std::int64_t>(values.back())); }
				else                        { std::forward<Func>(func)(std::get<std::int64_t>(values.back())); }
				break;
			case ParameterType::Uint8:
				if constexpr (ReturnResult) { return std::forward<Func>(func)(std::get<std::uint8_t>(values.back())); }
				else                        { std::forward<Func>(func)(std::get<std::uint8_t>(values.back())); }
				break;
			case ParameterType::Uint16:
				if constexpr (ReturnResult) { return std::forward<Func>(func)(std::get<std::uint16_t>(values.back())); }
				else                        { std::forward<Func>(func)(std::get<std::uint16_t>(values.back())); }
				break;
			case ParameterType::Uint32:
				if constexpr (ReturnResult) { return std::forward<Func>(func)(std::get<std::uint32_t>(values.back())); }
				else                        { std::forward<Func>(func)(std::get<std::uint32_t>(values.back())); }
				break;
			case ParameterType::Uint64:
				if constexpr (ReturnResult) { return std::forward<Func>(func)(std::get<std::uint64_t>(values.back())); }
				else                        { std::forward<Func>(func)(std::get<std::uint64_t>(values.back())); }
				break;
			case ParameterType::Float32:
				if constexpr (ReturnResult) { return std::forward<Func>(func)(std::get<float>(values.back())); }
				else                        { std::forward<Func>(func)(std::get<float>(values.back())); }
				break;
			case ParameterType::Float64:
				if constexpr (ReturnResult) { return std::forward<Func>(func)(std::get<double>(values.back())); }
				else                        { std::forward<Func>(func)(std::get<double>(values.back())); }
				break;
			case ParameterType::String:
				if constexpr (ReturnResult) { return std::forward<Func>(func)(std::get<std::string>(values.back())); }
				else                        { std::forward<Func>(func)(std::get<std::string>(values.back())); }
				break;
			default:
				throw _make_exception<std::runtime_error>("Attempted to use the most recent value of a parameter whose type is in an invalid state.");
			}
		}

		template<class T, class Func>
		requires
		(
			std::is_invocable_v<Func, const typename std::remove_cvref<T>::type&> &&
			!std::is_void_v<typename std::invoke_result<Func, const typename std::remove_cvref<T>::type&>::type>
		)
		[[nodiscard]] constexpr decltype(auto) UseMostRecentValue(Func&& func) const
		{
			return std::forward<Func>(func)(std::get<T>(values.back()));
		}

		template<class T, class Func>
		requires
		(
			std::is_invocable_v<Func, const typename std::remove_cvref<T>::type&> &&
			std::is_void_v<typename std::invoke_result<Func, const typename std::remove_cvref<T>::type&>::type>
		)
		constexpr void UseMostRecentValue(Func&& func) const
		{
			std::forward<Func>(func)(std::get<T>(values.back()));
		}

		template<class Func>
		requires(EmuIO::is_valid_function_for_any_possible_param_value<Func, false, false>())
		[[nodiscard]] constexpr decltype(auto) UseAllValues(Func&& func) const
		{
			switch (type & ParameterType::ValueTypeMask)
			{
			case ParameterType::Bool:
				UseAllValues<bool>(std::forward<Func>(func));
				break;
			case ParameterType::Int8:
				UseAllValues<std::int8_t>(std::forward<Func>(func));
				break;
			case ParameterType::Int16:
				UseAllValues<std::int16_t>(std::forward<Func>(func));
				break;
			case ParameterType::Int32:
				UseAllValues<std::int32_t>(std::forward<Func>(func));
				break;
			case ParameterType::Int64:
				UseAllValues<std::int64_t>(std::forward<Func>(func));
				break;
			case ParameterType::Uint8:
				UseAllValues<std::uint8_t>(std::forward<Func>(func));
				break;
			case ParameterType::Uint16:
				UseAllValues<std::uint16_t>(std::forward<Func>(func));
				break;
			case ParameterType::Uint32:
				UseAllValues<std::uint32_t>(std::forward<Func>(func));
				break;
			case ParameterType::Uint64:
				UseAllValues<std::uint64_t>(std::forward<Func>(func));
				break;
			case ParameterType::Float32:
				UseAllValues<float>(std::forward<Func>(func));
				break;
			case ParameterType::Float64:
				UseAllValues<double>(std::forward<Func>(func));
				break;
			case ParameterType::String:
				UseAllValues<std::string>(std::forward<Func>(func));
				break;
			default:
				throw _make_exception<std::runtime_error>("Attempted to use all values of a parameter whose type is in an invalid state.");
			}
		}

		template<class T, class Func>
		requires(std::is_invocable_v<Func, const typename std::remove_cvref<T>::type&>)
		constexpr void UseAllValues(Func func) const
		{
			for (std::size_t i{ 0u }, end{ values.size() }; i < end; ++i)
			{
				func(std::get<T>(values[i]));
			}
		}

		void AppendValueToStream(std::ostream& str) const
		{
			if (IsEnum())
			{
				_append_enum_info_to_stream(str, current_enum_info.back());
			}
			else
			{
				_append_value_to_stream(str, values.back());
			}
		}

		void AppendAllValuesToStream(std::ostream& str) const
		{
			if (IsArray() && !modified && default_value.index() == 0)
			{
				str << "[]";
				return;
			}

			str << '[';
			if (IsEnum())
			{
				const std::size_t final_index{ current_enum_info.size() - 1 };
				for (std::size_t i{ 0u }, end{ current_enum_info.size() }; i < end; ++i)
				{
					_append_enum_info_to_stream(str, current_enum_info[i]);
					if (i != final_index)
					{
						str << ", ";
					}
				}
			}
			else
			{
				UseAllValues([&str, count = std::size_t{ 0u }, end = size_t{values.size()}](const auto& value_) mutable
				{
					if constexpr (EmuConcepts::UnqualifiedMatch<decltype(value_), std::monostate>)
					{
						str << "null";
					}
					else if constexpr (EmuConcepts::UnqualifiedMatch<decltype(value_), std::string>)
					{
						str << '"' << value_ << '"';
					}
					else if constexpr (EmuConcepts::UnqualifiedMatch<decltype(value_), bool>)
					{
						str << (value_ ? "True" : "False");
					}
					else if constexpr (EmuConcepts::UnqualifiedMatch<decltype(value_), std::int8_t> || EmuConcepts::UnqualifiedMatch<decltype(value_), std::uint8_t>)
					{
						// Cast to int to output numbers instead of characters
						str << static_cast<int>(value_);
					}
					else
					{
						str << value_;
					}
					if ((++count) < end)
					{
						str << ", ";
					}
				});
			}
			str << ']';
		}

		void AppendDefaultValueToStream(std::ostream& str) const
		{
			const bool is_array{ IsArray() };
			if (is_array)
			{
				if (default_value.index() == 0)
				{
					str << "[]";
					return;
				}
				else
				{
					str << '[';
				}
			}

			if (IsEnum())
			{
				_append_enum_info_to_stream(str, default_enum_info);
			}
			else
			{
				_append_value_to_stream(str, default_value);
			}

			if (is_array)
			{
				str << ']';
			}
		}

		template<bool Type = true, bool Value = true, bool Default = true, bool Modified = true, bool ValidEnums = true>
		std::ostream& AppendToStream(std::ostream& str) const
		{
			if constexpr (Type)
			{
				str << EmuIO::arg_param_type_to_string(type);
			}

			if constexpr (Value)
			{
				if constexpr (Type)
				{
					str << '\n';
				}

				str << "Value";
				if (IsArray())
				{
					str << "s: ";
					AppendAllValuesToStream(str);
				}
				else
				{
					str << ": ";
					AppendValueToStream(str);
				}
			}

			if constexpr (Default)
			{
				if constexpr (Type || Value)
				{
					str << '\n';
				}
				str << "Default: ";
				AppendDefaultValueToStream(str);
			}

			if constexpr (Modified)
			{
				if constexpr (Type || Value || Default)
				{
					str << '\n';
				}
				str << "Modified: " << (modified ? "True" : "False");;
			}

			if constexpr (ValidEnums)
			{
				if (IsEnum())
				{
					if constexpr (Type || Value || Default || Modified)
					{
						str << '\n';
					}
					str << "Possible values:\n";
					AppendValidEnumStringsToStream<true>(str);
				}
			}
			return str;
		}

	private:
		[[nodiscard]] static std::string _array_substr(const std::string& input_, std::size_t begin, std::size_t count = std::string::npos)
		{
			std::string result = input_.substr(begin, count);
			if (!result.empty())
			{
				if (std::isspace(result[0]))
				{
					// Unescaped, so clear whitespace as it's considered padding to help with command readability in this context
					std::size_t whitespace_count{ 1u };
					while (whitespace_count < result.size())
					{
						if (std::isspace(result[whitespace_count]))
						{
							++whitespace_count;
						}
						else
						{
							break;
						}
					}
					return result.substr(whitespace_count);
				}
				else if (result.size() > 1)
				{
					if (result[0] == '\\' && (std::isspace(result[1]) || result[1] == '\\'))
					{
						// Space escaped to say "this is part of my input and not just to make my input command more human-readable")
						// --- As a result, clear the escape backslash
						// --- We also clear it if we're escaping an escape backslash since that'll be needed to allow strings that start as "\ " for example
						return result.substr(1);
					}
				}
			}
			return result;
		}

		static void _append_value_to_stream(std::ostream& str, const value_type& value_)
		{
			std::visit
			(
				[&str](const auto& translated_value)
				{
					if constexpr (EmuConcepts::UnqualifiedMatch<decltype(translated_value), std::monostate>)
					{
						str << "null";
					}
					else if constexpr (EmuConcepts::UnqualifiedMatch<decltype(translated_value), bool>)
					{
						str << (translated_value ? "True" : "False");
					}
					else if constexpr (EmuConcepts::UnqualifiedMatch<decltype(translated_value), std::int8_t> || EmuConcepts::UnqualifiedMatch<decltype(translated_value), std::uint8_t>)
					{
						// Cast to int to output numbers instead of characters
						str << static_cast<int>(translated_value);
					}
					else if constexpr (EmuConcepts::UnqualifiedMatch<decltype(translated_value), std::string>)
					{
						str << '"' << translated_value << '"';
					}
					else
					{
						str << translated_value;
					}
				},
				value_
			);
		}

		void _append_enum_info_to_stream(std::ostream& str, const enum_info_type* enum_info_) const
		{
			if (!enum_info_)
			{
				str << "null";
				return;
			}

			if ((type & ParameterType::ValueTypeMask) == ParameterType::String)
			{
				str << '"' << std::get<std::string>(*enum_info_) << '"';
			}
			else
			{
				const std::pair<std::string, value_type> translated_info{ std::get<std::pair<std::string, value_type>>(*enum_info_) };
				str << '"' << std::get<std::string>(translated_info) << '"';
				str << " (";
				std::visit
				(
					[&str](const auto& val_) mutable
					{
						if constexpr (EmuConcepts::UnqualifiedMatch<decltype(val_), std::monostate>)
						{
							str << "null";
						}
						else if constexpr (EmuConcepts::UnqualifiedMatch<decltype(val_), bool>)
						{
							str << (val_ ? "True" : "False");
						}
						else if constexpr (EmuConcepts::UnqualifiedMatch<decltype(val_), std::int8_t> || EmuConcepts::UnqualifiedMatch<decltype(val_), std::uint8_t>)
						{
							// Cast to int to output numbers instead of characters
							str << static_cast<int>(val_);
						}
						else if constexpr (EmuConcepts::UnqualifiedMatch<decltype(val_), std::string>)
						{
							str << '"' << val_ << '"';
						}
						else
						{
							// Output default
							str << val_;
						}
					},
					translated_info.second
				);
				str << ')';
			}
		}

		template<class...Args>
		[[nodiscard]] static std::string _make_err_str(Args&&...args)
		{
			std::ostringstream err_str;
			((err_str << std::forward<Args>(args)), ...);
			return err_str.str();
		}

		[[nodiscard]] value_type _parse_input(const std::string& input_, std::optional<std::string>& err)
		{
			if ((type & ParameterType::Enum) == ParameterType::Enum)
			{
				if ((type & ParameterType::ValueTypeMask) == ParameterType::String)
				{
					// String only
					for (const enum_info_type& this_enum_info : enum_info)
					{
						if (input_ == std::get<std::string>(this_enum_info))
						{
							if ((type & ParameterType::Array) == ParameterType::Array)
							{
								if (!modified)
								{
									current_enum_info.clear();
								}
								current_enum_info.emplace_back(&this_enum_info);
							}
							else
							{
								current_enum_info[0] = &this_enum_info;
							}
							return input_;
						}
					}
				}
				else
				{
					// String/Value pairs
					for (const enum_info_type& this_enum_info : enum_info)
					{
						const auto& fetched_enum_info{ std::get<std::pair<std::string, value_type>>(this_enum_info) };
						if (input_ == fetched_enum_info.first)
						{
							if ((type & ParameterType::Array) == ParameterType::Array)
							{
								if (!modified)
								{
									current_enum_info.clear();
								}
								current_enum_info.emplace_back(&this_enum_info);
							}
							else
							{
								current_enum_info[0] = &this_enum_info;
							}
							return fetched_enum_info.second;
						}
					}
				}
				err.emplace(_make_err_str("Input value `", input_, "` is invalid for parameter (of type ", arg_param_type_to_string(type),
										  ") as it does not match any of the valid enums for that parameter."));
			}
			else
			{
				switch (type & ParameterType::ValueTypeMask)
				{
				case ParameterType::Bool:
				{
					std::string lower{ input_ };
					std::transform(lower.begin(), lower.end(), lower.begin(), [](const char char_) { return std::tolower(char_); });
					if (lower == "true" || lower == "yes" || lower == "1")
					{
						return true;
					}
					else if (lower == "false" || lower == "no" || lower == "0")
					{
						return false;
					}
					else
					{
						err.emplace(_make_err_str("Input value `", input_, "` is invalid for paramater (of type ", arg_param_type_to_string(type), ") as it cannot be successfully interpreted as the target value type."));
					}
					break;
				}
				case ParameterType::Int8:
				{
					try
					{
						int result = std::stoi(input_);
						if (result < std::numeric_limits<std::int8_t>::lowest() || result > std::numeric_limits<int8_t>::max())
						{
							throw std::out_of_range{ "out of 8-bit stoi range" };
						}
						return static_cast<std::int8_t>(result);
					}
					catch ([[maybe_unused]] std::out_of_range& out_of_range)
					{
						err.emplace(_make_err_str("Input value `", input_, "` is invalid for paramater (of type ", arg_param_type_to_string(type),
							") as the value is outside of the representable range (",
							// cast range to int so that it's represented correctly in the string as a number instead of a single character
							int(std::numeric_limits<std::int8_t>::lowest()), ':', int(std::numeric_limits<std::int8_t>::max()), ')'));
					}
					catch ([[maybe_unused]] std::invalid_argument& invalid_arg)
					{
						err.emplace(_make_err_str("Input value `", input_, "` is invalid for paramater (of type ", arg_param_type_to_string(type), ") as it cannot be successfully interpreted as the target value type."));
					}
					break;
				}
				case ParameterType::Int16:
				{
					try
					{
						int result = std::stoi(input_);
						if (result < std::numeric_limits<std::int16_t>::lowest() || result > std::numeric_limits<int16_t>::max())
						{
							throw std::out_of_range{ "out of 16-bit stoi range" };
						}
						return static_cast<std::int16_t>(result);
					}
					catch ([[maybe_unused]] std::out_of_range& out_of_range)
					{
						err.emplace(_make_err_str("Input value `", input_, "` is invalid for paramater (of type ", arg_param_type_to_string(type),
							") as the value is outside of the representable range (",
							std::numeric_limits<std::int16_t>::lowest(), ':', std::numeric_limits<std::int16_t>::max(), ')'));
					}
					catch ([[maybe_unused]] std::invalid_argument& invalid_arg)
					{
						err.emplace(_make_err_str("Input value `", input_, "` is invalid for paramater (of type ", arg_param_type_to_string(type), ") as it cannot be successfully interpreted as the target value type."));
					}
					break;
				}
				case ParameterType::Int32:
				{
					try
					{
						int result = std::stoi(input_);
						return static_cast<std::int32_t>(result);
					}
					catch ([[maybe_unused]] std::out_of_range& out_of_range)
					{
						err.emplace(_make_err_str("Input value `", input_, "` is invalid for paramater (of type ", arg_param_type_to_string(type),
							") as the value is outside of the representable range (",
							std::numeric_limits<std::int32_t>::lowest(), ':', std::numeric_limits<std::int32_t>::max(), ')'));
					}
					catch ([[maybe_unused]] std::invalid_argument& invalid_arg)
					{
						err.emplace(_make_err_str("Input value `", input_, "` is invalid for paramater (of type ", arg_param_type_to_string(type), ") as it cannot be successfully interpreted as the target value type."));
					}
					break;
				}
				case ParameterType::Int64:
				{
					try
					{
						long long result = std::stoll(input_);
						return static_cast<std::int64_t>(result);
					}
					catch ([[maybe_unused]] std::out_of_range& out_of_range)
					{
						err.emplace(_make_err_str("Input value `", input_, "` is invalid for paramater (of type ", arg_param_type_to_string(type),
							") as the value is outside of the representable range (",
							std::numeric_limits<std::int64_t>::lowest(), ':', std::numeric_limits<std::int64_t>::max(), ')'));
					}
					catch ([[maybe_unused]] std::invalid_argument& invalid_arg)
					{
						err.emplace(_make_err_str("Input value `", input_, "` is invalid for paramater (of type ", arg_param_type_to_string(type), ") as it cannot be successfully interpreted as the target value type."));
					}
					break;
				}
				case ParameterType::Uint8:
				{
					try
					{
						unsigned long result = std::stoul(input_);
						if (result < std::numeric_limits<std::uint8_t>::lowest() || result > std::numeric_limits<uint8_t>::max())
						{
							throw std::out_of_range{ "out of 8-bit stou range" };
						}
						return static_cast<std::uint8_t>(result);
					}
					catch ([[maybe_unused]] std::out_of_range& out_of_range)
					{
						err.emplace(_make_err_str("Input value `", input_, "` is invalid for paramater (of type ", arg_param_type_to_string(type),
							") as the value is outside of the representable range (",
							// cast range to int so that it's represented correctly in the string as a number instead of a single character
							int(std::numeric_limits<std::uint8_t>::lowest()), ':', int(std::numeric_limits<std::uint8_t>::max()), ')'));
					}
					catch ([[maybe_unused]] std::invalid_argument& invalid_arg)
					{
						err.emplace(_make_err_str("Input value `", input_, "` is invalid for paramater (of type ", arg_param_type_to_string(type), ") as it cannot be successfully interpreted as the target value type."));
					}
					break;
				}
				case ParameterType::Uint16:
				{
					try
					{
						unsigned long result = std::stoul(input_);
						if (result < std::numeric_limits<std::uint16_t>::lowest() || result > std::numeric_limits<uint16_t>::max())
						{
							throw std::out_of_range{ "out of 16-bit stou range" };
						}
						return static_cast<std::uint16_t>(result);
					}
					catch ([[maybe_unused]] std::out_of_range& out_of_range)
					{
						err.emplace(_make_err_str("Input value `", input_, "` is invalid for paramater (of type ", arg_param_type_to_string(type),
							") as the value is outside of the representable range (",
							std::numeric_limits<std::uint16_t>::lowest(), ':', std::numeric_limits<std::uint16_t>::max(), ')'));
					}
					catch ([[maybe_unused]] std::invalid_argument& invalid_arg)
					{
						err.emplace(_make_err_str("Input value `", input_, "` is invalid for paramater (of type ", arg_param_type_to_string(type), ") as it cannot be successfully interpreted as the target value type."));
					}
					break;
				}
				case ParameterType::Uint32:
				{
					try
					{
						unsigned long result = std::stoul(input_);
						if constexpr (sizeof(long) != sizeof(std::int32_t))
						{
							// Supported platforms may have long as 32- or 64-bit, so we need to add the range check for uint32
							if (result < std::numeric_limits<std::uint32_t>::lowest() || result > std::numeric_limits<uint32_t>::max())
							{
								throw std::out_of_range{ "out of 32-bit stou range" };
							}
						}
						return static_cast<std::uint32_t>(result);
					}
					catch ([[maybe_unused]] std::out_of_range& out_of_range)
					{
						err.emplace(_make_err_str("Input value `", input_, "` is invalid for paramater (of type ", arg_param_type_to_string(type),
							") as the value is outside of the representable range (",
							std::numeric_limits<std::uint32_t>::lowest(), ':', std::numeric_limits<std::uint32_t>::max(), ')'));
					}
					catch ([[maybe_unused]] std::invalid_argument& invalid_arg)
					{
						err.emplace(_make_err_str("Input value `", input_, "` is invalid for paramater (of type ", arg_param_type_to_string(type), ") as it cannot be successfully interpreted as the target value type."));
					}
					break;
				}
				case ParameterType::Uint64:
				{
					try
					{
						unsigned long long result = std::stoull(input_);
						return static_cast<std::uint64_t>(result);
					}
					catch ([[maybe_unused]] std::out_of_range& out_of_range)
					{
						err.emplace(_make_err_str("Input value `", input_, "` is invalid for paramater (of type ", arg_param_type_to_string(type),
							") as the value is outside of the representable range (",
							std::numeric_limits<std::uint64_t>::lowest(), ':', std::numeric_limits<std::uint64_t>::max(), ')'));
					}
					catch ([[maybe_unused]] std::invalid_argument& invalid_arg)
					{
						err.emplace(_make_err_str("Input value `", input_, "` is invalid for paramater (of type ", arg_param_type_to_string(type), ") as it cannot be successfully interpreted as the target value type."));
					}
					break;
				}
				case ParameterType::Float32:
				{
					try
					{
						float result = std::stof(input_);
						return result;
					}
					catch ([[maybe_unused]] std::out_of_range& out_of_range)
					{
						err.emplace(_make_err_str("Input value `", input_, "` is invalid for paramater (of type ", arg_param_type_to_string(type),
							") as the value is outside of the representable range (",
							std::numeric_limits<float>::lowest(), ':', std::numeric_limits<float>::max(), ')'));
					}
					catch ([[maybe_unused]] std::invalid_argument& invalid_arg)
					{
						err.emplace(_make_err_str("Input value `", input_, "` is invalid for paramater (of type ", arg_param_type_to_string(type), ") as it cannot be successfully interpreted as the target value type."));
					}
					break;
				}
				case ParameterType::Float64:
				{
					try
					{
						double result = std::stof(input_);
						return result;
					}
					catch ([[maybe_unused]] std::out_of_range& out_of_range)
					{
						err.emplace(_make_err_str("Input value `", input_, "` is invalid for paramater (of type ", arg_param_type_to_string(type),
							") as the value is outside of the representable range (",
							std::numeric_limits<double>::lowest(), ':', std::numeric_limits<double>::max(), ')'));
					}
					catch ([[maybe_unused]] std::invalid_argument& invalid_arg)
					{
						err.emplace(_make_err_str("Input value `", input_, "` is invalid for paramater (of type ", arg_param_type_to_string(type), ") as it cannot be successfully interpreted as the target value type."));
					}
					break;
				}
				case ParameterType::String:
				{
					return input_;
					break;
				}
				default:
				{
					err.emplace(_make_err_str("The parameter is in an invalid state as its type does not contain a recognised value type flag."));
					break;
				}
				}
			}
			return std::monostate{}; // Should only be reached if an error occurs in parsing
		}

		template<class Exception, class...Args>
		[[nodiscard]] static Exception _make_exception(Args&&...args)
		{
			std::ostringstream msg_str{};
			((msg_str << std::forward<Args>(args)), ...);
			return Exception{ msg_str.str().c_str() };
		}

		template<class Value>
		[[nodiscard]] constexpr value_type _make_value(Value&& value_)
		{
			switch (type & ParameterType::ValueTypeMask)
			{
			case ParameterType::Bool:
				if constexpr (std::is_constructible_v<bool, Value>)
				{
					return static_cast<bool>(std::forward<Value>(value_));
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `Parameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ParameterType::ValueTypeMask));
				}
				break;
			case ParameterType::Int8:
				if constexpr (std::is_constructible_v<std::int8_t, Value>)
				{
					return static_cast<std::int8_t>(std::forward<Value>(value_));
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `Parameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ParameterType::ValueTypeMask));
				}
				break;
			case ParameterType::Int16:
				if constexpr (std::is_constructible_v<std::int16_t, Value>)
				{
					return static_cast<std::int16_t>(std::forward<Value>(value_));
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `Parameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ParameterType::ValueTypeMask));
				}
				break;
			case ParameterType::Int32:
				if constexpr (std::is_constructible_v<std::int32_t, Value>)
				{
					return static_cast<std::int32_t>(std::forward<Value>(value_));
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `Parameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ParameterType::ValueTypeMask));
				}
				break;
			case ParameterType::Int64:
				if constexpr (std::is_constructible_v<std::int64_t, Value>)
				{
					return static_cast<std::int64_t>(std::forward<Value>(value_));
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `Parameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ParameterType::ValueTypeMask));
				}
				break;
			case ParameterType::Uint8:
				if constexpr (std::is_constructible_v<std::uint8_t, Value>)
				{
					return static_cast<std::uint8_t>(std::forward<Value>(value_));
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `Parameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ParameterType::ValueTypeMask));
				}
				break;
			case ParameterType::Uint16:
				if constexpr (std::is_constructible_v<std::uint16_t, Value>)
				{
					return static_cast<std::uint16_t>(std::forward<Value>(value_));
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `Parameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ParameterType::ValueTypeMask));
				}
				break;
			case ParameterType::Uint32:
				if constexpr (std::is_constructible_v<std::uint32_t, Value>)
				{
					return static_cast<std::uint32_t>(std::forward<Value>(value_));
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `Parameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ParameterType::ValueTypeMask));
				}
				break;
			case ParameterType::Uint64:
				if constexpr (std::is_constructible_v<std::uint64_t, Value>)
				{
					return static_cast<std::uint64_t>(std::forward<Value>(value_));
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `Parameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ParameterType::ValueTypeMask));
				}
				break;
			case ParameterType::Float32:
				if constexpr (std::is_constructible_v<float, Value>)
				{
					return static_cast<float>(std::forward<Value>(value_));
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `Parameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ParameterType::ValueTypeMask));
				}
				break;
			case ParameterType::Float64:
				if constexpr (std::is_constructible_v<double, Value>)
				{
					return static_cast<double>(std::forward<Value>(value_));
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `Parameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ParameterType::ValueTypeMask));
				}
				break;
			case ParameterType::String:
				if constexpr (std::is_constructible_v<std::string, Value>)
				{
					return std::string{ std::forward<Value>(value_) };
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `Parameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ParameterType::ValueTypeMask));
				}
				break;
			default:
				return std::monostate{}; // Should never be reached due to validation
			}
		}
		
		template<ParameterType ParamType, class...EnumInfoSets, std::size_t...FirstIndices, std::size_t...SecondIndices, class DefaultEnum>
		[[nodiscard]] static Parameter _underlying_make_enum_type_with_pairs(DefaultEnum&& default_enum_, std::tuple<EnumInfoSets...> enum_pairs, std::index_sequence<FirstIndices...>, std::index_sequence<SecondIndices...>)
		{
			static_assert
			(
				(... && std::is_constructible_v<std::pair<std::string, typename EmuIO::parameter_type_value<ParamType>::type>,
												typename std::tuple_element<FirstIndices,  std::tuple<EnumInfoSets...>>::type,
												typename EmuIO::parameter_type_value<ParamType>::type>),
				"Invalid arguments for making a non-string enum param: The values were not ordered in pairs that could successfully construct a `std::string` followed by the parameter's value type."
			);
			static_assert
			(
				(... && EmuCore::TMP::is_static_castable_v<decltype(std::forward<typename std::tuple_element<SecondIndices, std::tuple<EnumInfoSets...>>::type>(std::get<SecondIndices>(enum_pairs))),
				                                           typename EmuIO::parameter_type_value<ParamType>::type>),
				"Invalid arguments for makign a non-string enum param: The values were not ordered in pairs that could successfully convert the second value of each pair to the parameter's `value_type` via  a static_cast."
			);

			static_assert
			(
				(
					EmuConcepts::UnqualifiedMatch<DefaultEnum, std::string> ||
					(EmuConcepts::UnqualifiedMatch<DefaultEnum, std::monostate> && (ParamType & ParameterType::Array) == ParameterType::Array)
				),
				"Invalid type input for making an Enum type parameter with pairs: The default value must be a `std::string`, or optionally `std::monostate` if the parameter type is an array that should be initialised as empty."
			);

			return Parameter
			(
				ParamType,
				std::forward<DefaultEnum>(default_enum_),
				std::pair<std::string, typename EmuIO::parameter_type_value<ParamType>::type>
				(
					std::forward<typename std::tuple_element<FirstIndices,  std::tuple<EnumInfoSets...>>::type>(std::get<FirstIndices>(enum_pairs)),
					static_cast<typename EmuIO::parameter_type_value<ParamType>::type>(std::forward<typename std::tuple_element<SecondIndices, std::tuple<EnumInfoSets...>>::type>(std::get<SecondIndices>(enum_pairs)))
				)...
			);
		}

		template<class Value>
		Parameter(ParameterType type_, Value&& default_value_) :
			values{},
			inputs{},
			default_value{ std::monostate{} },
			type{ type_ },
			enum_info{},
			default_enum_info{ nullptr },
			current_enum_info{},
			modified{ false }
		{
			// Set everything or nothing relating to the initial value; `_make_value` will trigger an exception if erroneous
			// --- We don't care about validating `default_value` as this constructor cannot be called directly,
			//     and is instead called by a deferring static builder function
			// --- Additionally, we don't care to validate that this isn't an enum since the static builder will check at compile time
			if constexpr (EmuConcepts::UnqualifiedMatch<Value, std::monostate>)
			{
				if (IsArray())
				{
					default_value.emplace<std::monostate>();
					values.emplace_back(std::monostate{});
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for a `Parameter` as monostate was provided, but the type flags of the parameter do not allow it to be initialised as empty (this is only possible with arrays).");
				}
			}
			else
			{
				default_value = _make_value(std::forward<Value>(default_value_));
				values.emplace_back(default_value);
			}
			inputs.emplace_back();
		}

		template<class Value, class...EnumInfos>
		requires(sizeof...(EnumInfos) != 0)
		Parameter(ParameterType type_, Value&& default_value_, EnumInfos&&...enum_infos) :
			values{},
			inputs{},
			default_value{ std::monostate{} },
			type{ type_ },
			enum_info{},
			default_enum_info{ nullptr },
			current_enum_info{},
			modified{false}
		{
			enum_info = std::vector<enum_info_type>{ std::forward<EnumInfos>(enum_infos)... };
			std::unordered_set<std::string_view> registered_enum_names{};
			for (const enum_info_type& this_enum_info_ : enum_info)
			{
				std::string_view current_name{ get_enum_string_from_enum_info(&this_enum_info_) };
				if (registered_enum_names.contains(current_name))
				{
					throw _make_exception<std::invalid_argument>("Invalid enum Parameter initialisation as a duplicate enum string has been provided: ", current_name);
				}
				else
				{
					registered_enum_names.emplace(std::move(current_name));
				}
			}

			if constexpr (std::is_constructible_v<std::string, Value>)
			{
				std::string value_string{ std::forward<Value>(default_value_) };
				if ((type & ParameterType::ValueTypeMask) == ParameterType::String)
				{
					// String only
					for (const enum_info_type& this_enum_info_ : enum_info)
					{
						if (value_string == std::get<std::string>(this_enum_info_))
						{
							default_enum_info = &this_enum_info_;
							current_enum_info = { default_enum_info };
							default_value.emplace<std::string>(std::move(value_string));
							break;
						}
					}
				}
				else
				{
					// String/Value pairs
					for (const enum_info_type& this_enum_info_ : enum_info)
					{
						const std::pair<std::string, value_type>& fetched_enum_info{ std::get<std::pair<std::string, value_type>>(this_enum_info_) };
						if (value_string == fetched_enum_info.first)
						{
							default_enum_info = &this_enum_info_;
							current_enum_info = { default_enum_info };
							default_value = fetched_enum_info.second;
							break;
						}
					}
				}

				// Will be set to non-null in above loops if valid
				if (default_enum_info == nullptr)
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an enum `Parameter` as the provided string value could not be translated to one of the provided enum strings for that parameter.");
				}
				values.emplace_back(default_value);
				inputs.emplace_back();
			}
			else if constexpr (EmuConcepts::UnqualifiedMatch<Value, std::monostate>)
			{
				if (IsArray())
				{
					default_enum_info = nullptr;
					current_enum_info = { default_enum_info };
					default_value.emplace<std::monostate>();
					values.emplace_back(std::monostate{});
					inputs.emplace_back();
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an enum `Parameter` as monostate was provided, but the type flags of the parameter do not allow it to be initialised as empty (this is only possible with arrays).");
				}
			}
			else
			{
				// This should be asserted beforehand by the static `make` helper
				throw _make_exception<std::invalid_argument>("Failed to make a value for an enum `Parameter` as the input value could not be used to construct a string.");
			}
		}

		[[nodiscard]] std::string_view get_enum_string_from_enum_info(const enum_info_type* enum_info_) const
		{
			if ((type & ParameterType::ValueTypeMask) == ParameterType::String)
			{
				if (enum_info_)
				{
					return std::get<std::string>(*enum_info_);
				}
				else
				{
					return "null";
				}
			}
			else
			{
				if (enum_info_)
				{
					return std::get<std::pair<std::string, value_type>>(*enum_info_).first;
				}
				else
				{
					return "null";
				}
			}
		}

		std::vector<value_type> values;
		std::vector<std::string> inputs;
		value_type default_value;
		ParameterType type;
		std::vector<enum_info_type> enum_info;
		const enum_info_type* default_enum_info;
		std::vector<const enum_info_type*> current_enum_info;
		bool modified;
	};
}

#endif
