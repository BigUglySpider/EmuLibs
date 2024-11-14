#ifndef EMU_IO_ARG_PARSER_HPP_INC_
#define EMU_IO_ARG_PARSER_HPP_INC_ 1

#include <cstdint>
#include <iostream>
#include <limits>
#include <map>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <variant>

#include "../EmuCore/CommonConcepts/CommonRequirements.h"
#include "../EmuCore/TMPHelpers/Values.h"

namespace EmuIO
{
	enum class ArgParameterType : std::uint32_t
	{
		Array = 0x10000000,
		Enum  = 0x20000000,

		Int8   = 0x00000001,
		Int16  = 0x00000002,
		Int32  = 0x00000004,
		Int64  = 0x00000008,
		Uint8  = 0x00000010,
		Uint16 = 0x00000020,
		Uint32 = 0x00000040,
		Uint64 = 0x00000080,
		
		Float32 = 0x00000100,
		Float64 = 0x00000200,

		String = 0x00001000,

		Int8Array   = Int8   | Array,
		Int16Array  = Int16  | Array,
		Int32Array  = Int32  | Array,
		Int64Array  = Int64  | Array,
		Uint8Array  = Uint8  | Array,
		Uint16Array = Uint16 | Array,
		Uint32Array = Uint32 | Array,
		Uint64Array = Uint64 | Array,

		Float32Array = Float32 | Array,
		Float64Array = Float64 | Array,

		StringArray = String | Array,

		Int8Enum   = Int8   | Enum,
		Int16Enum  = Int16  | Enum,
		Int32Enum  = Int32  | Enum,
		Int64Enum  = Int64  | Enum,
		Uint8Enum  = Uint8  | Enum,
		Uint16Enum = Uint16 | Enum,
		Uint32Enum = Uint32 | Enum,
		Uint64Enum = Uint64 | Enum,

		Float32Enum = Float32 | Enum,
		Float64Enum = Float64 | Enum,

		StringEnum = String | Enum,


		ValueTypeMask = Int8 | Int16 | Int32 | Int64 | Uint8 | Uint16 | Uint32 | Uint64 | Float32 | Float64 | String
	};
	[[nodiscard]] constexpr inline ArgParameterType operator|(const ArgParameterType a, const ArgParameterType b) noexcept
	{
		return static_cast<ArgParameterType>
		(
			static_cast<std::underlying_type<ArgParameterType>::type>(a) |
			static_cast<std::underlying_type<ArgParameterType>::type>(b)
		);
	}
	[[nodiscard]] constexpr inline ArgParameterType operator&(const ArgParameterType a, const ArgParameterType b) noexcept
	{
		return static_cast<ArgParameterType>
		(
			static_cast<std::underlying_type<ArgParameterType>::type>(a) &
			static_cast<std::underlying_type<ArgParameterType>::type>(b)
		);
	}
	[[nodiscard]] constexpr inline ArgParameterType operator^(const ArgParameterType a, const ArgParameterType b) noexcept
	{
		return static_cast<ArgParameterType>
		(
			static_cast<std::underlying_type<ArgParameterType>::type>(a) ^
			static_cast<std::underlying_type<ArgParameterType>::type>(b)
		);
	}

	template<ArgParameterType Type>
	struct parameter_type_value
	{
	private:
		[[nodiscard]] static constexpr auto _get() noexcept
		{
			if constexpr ((Type & ArgParameterType::Int8) == ArgParameterType::Int8)
			{
				return std::int8_t{};
			}
			else if constexpr ((Type & ArgParameterType::Int16) == ArgParameterType::Int16)
			{
				return std::int16_t{};
			}
			else if constexpr ((Type & ArgParameterType::Int32) == ArgParameterType::Int32)
			{
				return std::int32_t{};
			}
			else if constexpr ((Type & ArgParameterType::Int64) == ArgParameterType::Int64)
			{
				return std::int64_t{};
			}
			else if constexpr ((Type & ArgParameterType::Uint8) == ArgParameterType::Uint8)
			{
				return std::uint8_t{};
			}
			else if constexpr ((Type & ArgParameterType::Uint16) == ArgParameterType::Uint16)
			{
				return std::uint16_t{};
			}
			else if constexpr ((Type & ArgParameterType::Uint32) == ArgParameterType::Uint32)
			{
				return std::uint32_t{};
			}
			else if constexpr ((Type & ArgParameterType::Uint64) == ArgParameterType::Uint64)
			{
				return std::uint64_t{};
			}
			else if constexpr ((Type & ArgParameterType::Float32) == ArgParameterType::Float32)
			{
				return float{};
			}
			else if constexpr ((Type & ArgParameterType::Float64) == ArgParameterType::Float64)
			{
				return double{};
			}
			else if constexpr ((Type & ArgParameterType::String) == ArgParameterType::String)
			{
				return std::string{};
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Type>(),
					"Invalid type input to `EmuIO::parameter_type_value`: It does not have a recognised value type flag."
				);
				return int{};
			}
		}

	public:
		using type = decltype(_get());
	};

	template<class...Args>
	[[nodiscard]] constexpr inline bool valid_construction_args_for_param_type(const ArgParameterType type) noexcept
	{
		switch (type & ArgParameterType::ValueTypeMask)
		{
		case ArgParameterType::Int8:
			return std::is_constructible_v<std::int8_t, Args...>;
		case ArgParameterType::Int16:
			return std::is_constructible_v<std::int16_t, Args...>;
		case ArgParameterType::Int32:
			return std::is_constructible_v<std::int32_t, Args...>;
		case ArgParameterType::Int64:
			return std::is_constructible_v<std::int64_t, Args...>;
		case ArgParameterType::Uint8:
			return std::is_constructible_v<std::uint8_t, Args...>;
		case ArgParameterType::Uint16:
			return std::is_constructible_v<std::uint16_t, Args...>;
		case ArgParameterType::Uint32:
			return std::is_constructible_v<std::uint32_t, Args...>;
		case ArgParameterType::Uint64:
			return std::is_constructible_v<std::uint64_t, Args...>;
		case ArgParameterType::Float32:
			return std::is_constructible_v<float, Args...>;
		case ArgParameterType::Float64:
			return std::is_constructible_v<double, Args...>;
		case ArgParameterType::String:
			return std::is_constructible_v<std::string, Args...>;
		default:
			return false;
		}
	}

	template<ArgParameterType Type>
	struct arg_parameter_enum_builder_arg
	{
	private:
		[[nodiscard]] static constexpr auto get() noexcept
		{
			if constexpr ((Type & ArgParameterType::Enum) == ArgParameterType::Enum)
			{
				if constexpr ((Type & ArgParameterType::ValueTypeMask) == ArgParameterType::String)
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

	[[nodiscard]] constexpr inline std::string_view arg_param_type_to_string(const ArgParameterType type) noexcept
	{
		using namespace std::string_view_literals;
		switch (type)
		{
		case ArgParameterType::Int8:
			return "Int8"sv;
		case ArgParameterType::Int16:
			return "Int16"sv;
		case ArgParameterType::Int32:
			return "Int32"sv;
		case ArgParameterType::Int64:
			return "Int64"sv;
		case ArgParameterType::Uint8:
			return "Uint8"sv;
		case ArgParameterType::Uint16:
			return "Uint16"sv;
		case ArgParameterType::Uint32:
			return "Uint32"sv;
		case ArgParameterType::Uint64:
			return "Uint64"sv;
		case ArgParameterType::Float32:
			return "Float32"sv;
		case ArgParameterType::Float64:
			return "Float64"sv;
		case ArgParameterType::String:
			return "String"sv;

		case ArgParameterType::Int8Array:
			return "Int8 Array"sv;
		case ArgParameterType::Int16Array:
			return "Int16 Array"sv;
		case ArgParameterType::Int32Array:
			return "Int32 Array"sv;
		case ArgParameterType::Int64Array:
			return "Int64 Array"sv;
		case ArgParameterType::Uint8Array:
			return "Uint8 Array"sv;
		case ArgParameterType::Uint16Array:
			return "Uint16 Array"sv;
		case ArgParameterType::Uint32Array:
			return "Uint32 Array"sv;
		case ArgParameterType::Uint64Array:
			return "Uint64 Array"sv;
		case ArgParameterType::Float32Array:
			return "Float32 Array"sv;
		case ArgParameterType::Float64Array:
			return "Float64 Array"sv;
		case ArgParameterType::StringArray:
			return "String Array"sv;

		case ArgParameterType::Int8Enum:
			return "Int8 Enum"sv;
		case ArgParameterType::Int16Enum:
			return "Int16 Enum"sv;
		case ArgParameterType::Int32Enum:
			return "Int32 Enum"sv;
		case ArgParameterType::Int64Enum:
			return "Int64 Enum"sv;
		case ArgParameterType::Uint8Enum:
			return "Uint8 Enum"sv;
		case ArgParameterType::Uint16Enum:
			return "Uint16 Enum"sv;
		case ArgParameterType::Uint32Enum:
			return "Uint32 Enum"sv;
		case ArgParameterType::Uint64Enum:
			return "Uint64 Enum"sv;
		case ArgParameterType::Float32Enum:
			return "Float32 Enum"sv;
		case ArgParameterType::Float64Enum:
			return "Float64 Enum"sv;
		case ArgParameterType::StringEnum:
			return "String Enum"sv;
		default:
			return "Invalid"sv;
		}
	}

	class ArgParameter
	{
	public:
		using value_type = std::variant
		<
			std::monostate,
			std::int8_t,  std::int16_t,  std::int32_t,  std::int64_t,
			std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t,
			float,        double,
			std::string
		>;
		using enum_info_type = std::variant
		<
			std::monostate,
			std::string,
			std::pair<std::string, value_type>
		>;

		ArgParameter() = delete;
		ArgParameter(const ArgParameter&) = delete;
		ArgParameter& operator=(const ArgParameter&) = delete;

		constexpr ArgParameter(ArgParameter&& to_move) noexcept :
			values{ std::move(to_move.values) },
			inputs{ std::move(to_move.inputs) },
			default_value{ std::move(to_move.default_value) },
			type{ to_move.type },
			enum_info{ std::move(to_move.enum_info) }
		{
		}

		constexpr ArgParameter& operator=(ArgParameter&& to_move) noexcept
		{
			values = std::move(to_move.values);
			inputs = std::move(to_move.inputs);
			default_value = std::move(to_move.default_value);
			type = to_move.type;
			enum_info = std::move(to_move.enum_info);
			return *this;
		}

		template<ArgParameterType ParamType, class DefaultValue>
		requires((ParamType & ArgParameterType::Enum) != ArgParameterType::Enum)
		[[nodiscard]] static ArgParameter make(DefaultValue&& default_value_)
		{
			constexpr bool valid_construction{valid_construction_args_for_param_type<DefaultValue>(ParamType)};
			static_assert(valid_construction, "Invalid construction args provided for the specified ArgParameterType.");

			return ArgParameter(ParamType, std::forward<DefaultValue>(default_value_));
		}

		template<ArgParameterType ParamType, class DefaultValue, class...EnumInfos>
		requires((ParamType& ArgParameterType::Enum) == ArgParameterType::Enum)
		[[nodiscard]] static ArgParameter make(DefaultValue&& default_value_, EnumInfos&&...enum_infos)
		{
			constexpr bool valid_construction{ valid_construction_args_for_param_type<DefaultValue>(ParamType) };
			static_assert(valid_construction, "Invalid construction args provided for the specified ArgParameterType.");

			constexpr bool valid_enum_info_count{ sizeof...(EnumInfos) != 0 };
			static_assert(valid_enum_info_count, "Invalid enum info args provided for the specfied ArgParameterType which contains an `Enum` flag: Must be at least 1 enum value.");

			constexpr bool valid_enum_info_types{ (... && EmuConcepts::UnqualifiedMatch<typename arg_parameter_enum_builder_arg<ParamType>::type, EnumInfos>) };
			static_assert(valid_enum_info_types, "Invalid enum info args provided for the specified ArgParameterType which contains an `Enum` flag: At least 1 info's type is mismatched with `arg_parameter_enum_builder_arg<ParamType>::type`.");

			return ArgParameter(ParamType, std::forward<DefaultValue>(default_value_), std::forward<EnumInfos>(enum_infos)...);
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

		[[nodiscard]] constexpr const value_type& GetValue() const noexcept
		{
			return values.back();
		}
		template<class Out>
		[[nodiscard]] const Out& GetValue() const
		{
			return std::get<Out>(values.back());
		}

		[[nodiscard]] constexpr const std::vector<value_type>& GetAllValues() const noexcept
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

		[[nodiscard]] constexpr const std::string& GetInput() const noexcept
		{
			return inputs.back();
		}

		[[nodiscard]] constexpr const std::vector<std::string>& GetAllInputs() const noexcept
		{
			return inputs;
		}

		[[nodiscard]] constexpr ArgParameterType GetType() const noexcept
		{
			return type;
		}

		std::optional<std::string> AppendInput(std::string input_)
		{
			std::optional<std::string> err{ std::nullopt };
			value_type new_item = _parse_input(input_, err);
			if (new_item.index() != 0) // Index 0 = monostate, translating to failure
			{
				if ((type & ArgParameterType::Array) == ArgParameterType::Array)
				{
					values.emplace_back(std::move(new_item));
					inputs.emplace_back(std::move(input_));
				}
				else
				{
					values[0] = std::move(new_item);
					inputs[0] = std::move(input_);
				}
			}
			return err;
		}

	private:
		template<class...Args>
		[[nodiscard]] static std::string _make_err_str(Args&&...args)
		{
			std::ostringstream err_str;
			((err_str << std::forward<Args>(args)), ...);
			return err_str.str();
		}

		[[nodiscard]] value_type _parse_input(const std::string& input_, std::optional<std::string>& err) const
		{
			if ((type & ArgParameterType::Enum) == ArgParameterType::Enum)
			{
				// TODO: Enum
				err.emplace("Parsing of enums not yet implemented.");
				return std::monostate{};
			}
			else
			{
				switch (type & ArgParameterType::ValueTypeMask)
				{
				case ArgParameterType::Int8:
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
				case ArgParameterType::Int16:
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
				case ArgParameterType::Int32:
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
				case ArgParameterType::Int64:
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
				case ArgParameterType::Uint8:
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
				case ArgParameterType::Uint16:
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
				case ArgParameterType::Uint32:
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
				case ArgParameterType::Uint64:
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
				case ArgParameterType::Float32:
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
				case ArgParameterType::Float64:
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
				case ArgParameterType::String:
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
			switch (type & ArgParameterType::ValueTypeMask)
			{
			case ArgParameterType::Int8:
				if constexpr (std::is_constructible_v<std::int8_t, Value>)
				{
					return static_cast<std::int8_t>(std::forward<Value>(value_));
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `ArgParameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ArgParameterType::ValueTypeMask));
				}
				break;
			case ArgParameterType::Int16:
				if constexpr (std::is_constructible_v<std::int16_t, Value>)
				{
					return static_cast<std::int16_t>(std::forward<Value>(value_));
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `ArgParameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ArgParameterType::ValueTypeMask));
				}
				break;
			case ArgParameterType::Int32:
				if constexpr (std::is_constructible_v<std::int32_t, Value>)
				{
					return static_cast<std::int32_t>(std::forward<Value>(value_));
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `ArgParameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ArgParameterType::ValueTypeMask));
				}
				break;
			case ArgParameterType::Int64:
				if constexpr (std::is_constructible_v<std::int64_t, Value>)
				{
					return static_cast<std::int64_t>(std::forward<Value>(value_));
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `ArgParameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ArgParameterType::ValueTypeMask));
				}
				break;
			case ArgParameterType::Uint8:
				if constexpr (std::is_constructible_v<std::uint8_t, Value>)
				{
					return static_cast<std::uint8_t>(std::forward<Value>(value_));
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `ArgParameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ArgParameterType::ValueTypeMask));
				}
				break;
			case ArgParameterType::Uint16:
				if constexpr (std::is_constructible_v<std::uint16_t, Value>)
				{
					return static_cast<std::uint16_t>(std::forward<Value>(value_));
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `ArgParameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ArgParameterType::ValueTypeMask));
				}
				break;
			case ArgParameterType::Uint32:
				if constexpr (std::is_constructible_v<std::uint32_t, Value>)
				{
					return static_cast<std::uint32_t>(std::forward<Value>(value_));
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `ArgParameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ArgParameterType::ValueTypeMask));
				}
				break;
			case ArgParameterType::Uint64:
				if constexpr (std::is_constructible_v<std::uint64_t, Value>)
				{
					return static_cast<std::uint64_t>(std::forward<Value>(value_));
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `ArgParameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ArgParameterType::ValueTypeMask));
				}
				break;
			case ArgParameterType::Float32:
				if constexpr (std::is_constructible_v<float, Value>)
				{
					return static_cast<float>(std::forward<Value>(value_));
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `ArgParameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ArgParameterType::ValueTypeMask));
				}
				break;
			case ArgParameterType::Float64:
				if constexpr (std::is_constructible_v<double, Value>)
				{
					return static_cast<double>(std::forward<Value>(value_));
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `ArgParameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ArgParameterType::ValueTypeMask));
				}
				break;
			case ArgParameterType::String:
				if constexpr (std::is_constructible_v<std::string, Value>)
				{
					return std::string{ std::forward<Value>(value_) };
				}
				else
				{
					throw _make_exception<std::invalid_argument>("Failed to make a value for an `ArgParameter` as its value type could not be constructed with the input type. Target value type: ", arg_param_type_to_string(type & ArgParameterType::ValueTypeMask));
				}
				break;
			default:
				return std::monostate{}; // Should never be reached due to validation
			}
		}

		template<class Value>
		ArgParameter(ArgParameterType type_, Value&& default_value_) :
			values{},
			inputs{},
			default_value{ std::monostate{} },
			type{ type_ },
			enum_info{}
		{
			// Set everything or nothing relating to the initial value; `_make_value` will trigger an exception if erroneous
			// --- We don't care about validating `default_value` as this constructor cannot be called directly,
			//     and is instead called by a deferring static builder function
			// --- Additionally, we don't care to validate that this isn't an enum since the static builder will check at compile time
			default_value = _make_value(std::forward<Value>(default_value_));
			values.emplace_back(default_value);
			inputs.emplace_back();
		}

		template<class Value, class...EnumInfos>
		ArgParameter(ArgParameterType type_, Value&& default_value_, EnumInfos&&...enum_infos) :
			ArgParameter(type_, std::forward<Value>(default_value_))
		{
			enum_info.reserve(sizeof...(EnumInfos));
			((enum_info.emplace_back(std::forward<EnumInfos>(enum_infos))), ...);
		}

		std::vector<value_type> values;
		std::vector<std::string> inputs;
		value_type default_value;
		ArgParameterType type;
		std::vector<enum_info_type> enum_info;
	};

	class ArgParser
	{
	public:

	private:
		std::unordered_map<std::string, ArgParameter> parameters;
		std::unordered_map<std::string, std::string_view> alias_to_param_map;
		std::unordered_map<std::string_view, std::vector<std::string_view>> param_to_aliases_map;
	};
}

#endif
