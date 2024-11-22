#ifndef EMU_IO_ARG_PARSER_PARAMETER_TYPE_HPP_INC_
#define EMU_IO_ARG_PARSER_PARAMETER_TYPE_HPP_INC_ 1

#include <cstdint>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>

#include "../../../EmuCore/CommonConcepts/CommonRequirements.h"
#include "../../../EmuCore/TMPHelpers/OperatorChecks.h"
#include "../../../EmuCore/TMPHelpers/Values.h"

namespace EmuIO
{
	enum class ParameterType : std::uint32_t
	{
		Array = 0x10000000,
		Enum  = 0x20000000,
		Const = 0x40000000,

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
		String  = 0x00000400,
		Bool    = 0x00000800,

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

		ValueTypeMask = Int8 | Int16 | Int32 | Int64 | Uint8 | Uint16 | Uint32 | Uint64 | Float32 | Float64 | String | Bool,
		MetaMask      = Array | Enum | Const,

		Invalid = ~(ValueTypeMask | MetaMask) // Invalid is a mask of all bits that are never used
	};
	[[nodiscard]] constexpr inline ParameterType operator|(const ParameterType a, const ParameterType b) noexcept
	{
		return static_cast<ParameterType>
		(
			static_cast<std::underlying_type<ParameterType>::type>(a) |
			static_cast<std::underlying_type<ParameterType>::type>(b)
		);
	}
	[[nodiscard]] constexpr inline ParameterType operator&(const ParameterType a, const ParameterType b) noexcept
	{
		return static_cast<ParameterType>
		(
			static_cast<std::underlying_type<ParameterType>::type>(a) &
			static_cast<std::underlying_type<ParameterType>::type>(b)
		);
	}
	[[nodiscard]] constexpr inline ParameterType operator^(const ParameterType a, const ParameterType b) noexcept
	{
		return static_cast<ParameterType>
		(
			static_cast<std::underlying_type<ParameterType>::type>(a) ^
			static_cast<std::underlying_type<ParameterType>::type>(b)
		);
	}

	template<class T>
	[[nodiscard]] constexpr inline ParameterType type_to_parameter_type_enum() noexcept
	{
		if constexpr (std::is_pointer_v<typename std::remove_cvref<T>::type>)
		{
			static_assert(EmuCore::TMP::get_false<std::is_same_v<T, std::int32_t>>(), "Pointer type passed to EmuIO::type_to_parameter_type_enum.");
		}
		else if constexpr (std::is_enum_v<typename std::remove_cvref<T>::type>)
		{
			return
			(
				ParameterType::Enum |
				type_to_parameter_type_enum<typename EmuCore::TMP::conditional_const<std::is_const_v<T>, typename std::underlying_type<typename std::remove_cvref<T>::type>::type>::type>()
			);
		}
		else if constexpr (std::is_array_v<typename std::remove_cvref<T>::type>)
		{
			constexpr ParameterType unarrayed_type
			{
				type_to_parameter_type_enum<typename std::remove_extent<typename std::remove_reference<T>::type>::type>()
			};
			static_assert((unarrayed_type & ParameterType::Array) == ParameterType{}, "Multidimensional arrays are not supported conversions for EmuIO::type_to_parameter_type_enum");
			return unarrayed_type | ParameterType::Array;
		}
		else if constexpr (std::is_const_v<typename std::remove_reference<T>::type>)
		{
			return
			(
				ParameterType::Const |
				type_to_parameter_type_enum<typename std::remove_cvref<T>::type>()
			);
		}
		else if constexpr (EmuConcepts::UnqualifiedMatch<T, bool>)
		{
			return ParameterType::Bool;
		}
		else if constexpr (EmuConcepts::UnqualifiedMatch<T, std::int8_t>)
		{
			return ParameterType::Int8;
		}
		else if constexpr (EmuConcepts::UnqualifiedMatch<T, std::int16_t>)
		{
			return ParameterType::Int16;
		}
		else if constexpr (EmuConcepts::UnqualifiedMatch<T, std::int32_t>)
		{
			return ParameterType::Int32;
		}
		else if constexpr (EmuConcepts::UnqualifiedMatch<T, std::int64_t>)
		{
			return ParameterType::Int64;
		}
		else if constexpr (EmuConcepts::UnqualifiedMatch<T, std::uint8_t>)
		{
			return ParameterType::Uint8;
		}
		else if constexpr (EmuConcepts::UnqualifiedMatch<T, std::uint16_t>)
		{
			return ParameterType::Uint16;
		}
		else if constexpr (EmuConcepts::UnqualifiedMatch<T, std::uint32_t>)
		{
			return ParameterType::Uint32;
		}
		else if constexpr (EmuConcepts::UnqualifiedMatch<T, std::uint64_t>)
		{
			return ParameterType::Uint64;
		}
		else if constexpr (EmuConcepts::UnqualifiedMatch<T, float>)
		{
			return ParameterType::Float32;
		}
		else if constexpr (EmuConcepts::UnqualifiedMatch<T, double>)
		{
			return ParameterType::Float64;
		}
		else if constexpr (EmuConcepts::UnqualifiedMatch<T, std::string> || EmuConcepts::UnqualifiedMatch<T, std::string_view> || EmuConcepts::UnqualifiedMatch<T, char*>)
		{
			return ParameterType::String;
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<std::is_same_v<T, std::int32_t>>(), "Unsupported type passed to EmuIO::type_to_parameter_type_enum.");
		}
	}

	template<class ValueType, bool Array, bool Const, bool Enum>
	[[nodiscard]] constexpr inline ParameterType make_parameter_type() noexcept
	{
		constexpr ParameterType array_bit{ Array ? ParameterType::Array : ParameterType{} };
		constexpr ParameterType const_bit{ Const ? ParameterType::Const : ParameterType{} };
		constexpr ParameterType enum_bit { Enum  ? ParameterType::Enum  : ParameterType{} };
		constexpr ParameterType value_bit{ type_to_parameter_type_enum<ValueType>() };
		return array_bit | const_bit | enum_bit | value_bit;
	}

	template<ParameterType Type>
	struct parameter_type_value
	{
	private:
		[[nodiscard]] static constexpr auto _get() noexcept
		{
			if constexpr ((Type & ParameterType::Bool) == ParameterType::Bool)
			{
				return bool{};
			}
			else if constexpr ((Type & ParameterType::Int8) == ParameterType::Int8)
			{
				return std::int8_t{};
			}
			else if constexpr ((Type & ParameterType::Int16) == ParameterType::Int16)
			{
				return std::int16_t{};
			}
			else if constexpr ((Type & ParameterType::Int32) == ParameterType::Int32)
			{
				return std::int32_t{};
			}
			else if constexpr ((Type & ParameterType::Int64) == ParameterType::Int64)
			{
				return std::int64_t{};
			}
			else if constexpr ((Type & ParameterType::Uint8) == ParameterType::Uint8)
			{
				return std::uint8_t{};
			}
			else if constexpr ((Type & ParameterType::Uint16) == ParameterType::Uint16)
			{
				return std::uint16_t{};
			}
			else if constexpr ((Type & ParameterType::Uint32) == ParameterType::Uint32)
			{
				return std::uint32_t{};
			}
			else if constexpr ((Type & ParameterType::Uint64) == ParameterType::Uint64)
			{
				return std::uint64_t{};
			}
			else if constexpr ((Type & ParameterType::Float32) == ParameterType::Float32)
			{
				return float{};
			}
			else if constexpr ((Type & ParameterType::Float64) == ParameterType::Float64)
			{
				return double{};
			}
			else if constexpr ((Type & ParameterType::String) == ParameterType::String)
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
	[[nodiscard]] constexpr inline bool valid_construction_args_for_param_type(const ParameterType type) noexcept
	{
		switch (type & ParameterType::ValueTypeMask)
		{
		case ParameterType::Bool:
			return std::is_constructible_v<bool, Args...>;
		case ParameterType::Int8:
			return std::is_constructible_v<std::int8_t, Args...>;
		case ParameterType::Int16:
			return std::is_constructible_v<std::int16_t, Args...>;
		case ParameterType::Int32:
			return std::is_constructible_v<std::int32_t, Args...>;
		case ParameterType::Int64:
			return std::is_constructible_v<std::int64_t, Args...>;
		case ParameterType::Uint8:
			return std::is_constructible_v<std::uint8_t, Args...>;
		case ParameterType::Uint16:
			return std::is_constructible_v<std::uint16_t, Args...>;
		case ParameterType::Uint32:
			return std::is_constructible_v<std::uint32_t, Args...>;
		case ParameterType::Uint64:
			return std::is_constructible_v<std::uint64_t, Args...>;
		case ParameterType::Float32:
			return std::is_constructible_v<float, Args...>;
		case ParameterType::Float64:
			return std::is_constructible_v<double, Args...>;
		case ParameterType::String:
			return std::is_constructible_v<std::string, Args...>;
		default:
			return false;
		}
	}

	[[nodiscard]] inline std::string arg_param_type_to_string(const ParameterType type) noexcept
	{
		std::ostringstream str{};

		// Prefixes
		if ((type & ParameterType::Const) == ParameterType::Const)
		{
			str << "Const ";
		}

		// Value type
		switch (type & ParameterType::ValueTypeMask)
		{
		case ParameterType::Bool:
			str << "Bool";
			break;
		case ParameterType::Int8:
			str << "Int8";
			break;
		case ParameterType::Int16:
			str << "Int16";
			break;
		case ParameterType::Int32:
			str << "Int32";
			break;
		case ParameterType::Int64:
			str << "Int64";
			break;
		case ParameterType::Uint8:
			str << "Uint8";
			break;
		case ParameterType::Uint16:
			str << "Uint16";
			break;
		case ParameterType::Uint32:
			str << "Uint32";
			break;
		case ParameterType::Uint64:
			str << "Uint64";
			break;
		case ParameterType::Float32:
			str << "Float32";
			break;
		case ParameterType::Float64:
			str << "Float64";
			break;
		case ParameterType::String:
			str << "String";
			break;
		default:
			str << "Invalid";
			break;
		}

		// Suffixes
		if ((type & ParameterType::Enum) == ParameterType::Enum)
		{
			str << " Enum";
		}
		if ((type & ParameterType::Array) == ParameterType::Array)
		{
			str << " Array";
		}

		return str.str();
	}
	
	template<template<class, class...> class Trait, class...Ts>
	[[nodiscard]] constexpr inline bool is_trait_satisfied_for_any_possible_param_value_pre() noexcept
	{
		return
		(
			Trait<Ts..., const bool&>::value          &&
			Trait<Ts..., const std::int8_t&>::value   &&
			Trait<Ts..., const std::int16_t&>::value  &&
			Trait<Ts..., const std::int32_t&>::value  &&
			Trait<Ts..., const std::int64_t&>::value  &&
			Trait<Ts..., const std::uint8_t&>::value  &&
			Trait<Ts..., const std::uint16_t&>::value &&
			Trait<Ts..., const std::uint32_t&>::value &&
			Trait<Ts..., const std::uint64_t&>::value &&
			Trait<Ts..., const float&>::value         &&
			Trait<Ts..., const double&>::value        &&
			Trait<Ts..., const std::string&>::value
		);
	}

	template<template<class, class...> class Trait, class...Ts>
	[[nodiscard]] constexpr inline bool is_trait_satisfied_for_any_possible_param_value_post() noexcept
	{
		return
		(
			Trait<const bool&, Ts...>::value          &&
			Trait<const std::int8_t&, Ts...>::value   &&
			Trait<const std::int16_t&, Ts...>::value  &&
			Trait<const std::int32_t&, Ts...>::value  &&
			Trait<const std::int64_t&, Ts...>::value  &&
			Trait<const std::uint8_t&, Ts...>::value  &&
			Trait<const std::uint16_t&, Ts...>::value &&
			Trait<const std::uint32_t&, Ts...>::value &&
			Trait<const std::uint64_t&, Ts...>::value &&
			Trait<const float&, Ts...>::value         &&
			Trait<const double&, Ts...>::value        &&
			Trait<const std::string&, Ts...>::value
		);
	}
	
	template<template<class, class...> class Trait, class...Ts>
	[[nodiscard]] constexpr inline bool is_trait_matching_for_all_possible_param_values_pre() noexcept
	{
		return
		(
			(Trait<Ts..., const bool&>::value == Trait<Ts..., const std::int8_t&>::value)   &&
			(Trait<Ts..., const bool&>::value == Trait<Ts..., const std::int16_t&>::value)  &&
			(Trait<Ts..., const bool&>::value == Trait<Ts..., const std::int32_t&>::value)  &&
			(Trait<Ts..., const bool&>::value == Trait<Ts..., const std::int64_t&>::value)  &&
			(Trait<Ts..., const bool&>::value == Trait<Ts..., const std::uint8_t&>::value)  &&
			(Trait<Ts..., const bool&>::value == Trait<Ts..., const std::uint16_t&>::value) &&
			(Trait<Ts..., const bool&>::value == Trait<Ts..., const std::uint32_t&>::value) &&
			(Trait<Ts..., const bool&>::value == Trait<Ts..., const std::uint64_t&>::value) &&
			(Trait<Ts..., const bool&>::value == Trait<Ts..., const float&>::value)         &&
			(Trait<Ts..., const bool&>::value == Trait<Ts..., const double&>::value)        &&
			(Trait<Ts..., const bool&>::value == Trait<Ts..., const std::string&>::value)
		);
	}
	
	template<template<class, class...> class Trait, class...Ts>
	[[nodiscard]] constexpr inline bool is_trait_matching_for_all_possible_param_values_post() noexcept
	{
		return
		(
			(Trait<const bool&, Ts...>::value == Trait<const std::int8_t&, Ts...>::value)   &&
			(Trait<const bool&, Ts...>::value == Trait<const std::int16_t&, Ts...>::value)  &&
			(Trait<const bool&, Ts...>::value == Trait<const std::int32_t&, Ts...>::value)  &&
			(Trait<const bool&, Ts...>::value == Trait<const std::int64_t&, Ts...>::value)  &&
			(Trait<const bool&, Ts...>::value == Trait<const std::uint8_t&, Ts...>::value)  &&
			(Trait<const bool&, Ts...>::value == Trait<const std::uint16_t&, Ts...>::value) &&
			(Trait<const bool&, Ts...>::value == Trait<const std::uint32_t&, Ts...>::value) &&
			(Trait<const bool&, Ts...>::value == Trait<const std::uint64_t&, Ts...>::value) &&
			(Trait<const bool&, Ts...>::value == Trait<const float&, Ts...>::value)         &&
			(Trait<const bool&, Ts...>::value == Trait<const double&, Ts...>::value)        &&
			(Trait<const bool&, Ts...>::value == Trait<const std::string&, Ts...>::value)
		);
	}

	template<class Func, bool Returns = true, bool Assert = false>
	[[nodiscard]] constexpr inline bool is_valid_function_for_any_possible_param_value() noexcept
	{
		constexpr bool invocable = is_trait_satisfied_for_any_possible_param_value_pre<std::is_invocable, Func>();
		if constexpr (!invocable)
		{
			if constexpr (Assert)
			{
				static_assert
				(
					EmuCore::TMP::get_false<Func>(),
					"Invalid function type provided as it cannot be invoked with every possible parameter value type."
				);
			}
			return false;
		}
		else if constexpr (!Returns)
		{
			return true;
		}
		else
		{
			constexpr bool all_return_or_not = is_trait_matching_for_all_possible_param_values_pre<EmuCore::TMP::invoking_has_return, Func>();
			if constexpr (!all_return_or_not)
			{
				if constexpr (Assert)
				{
					static_assert
					(
						EmuCore::TMP::get_false<Func>(),
						"Invalid function type provided as it does not consistently return either void or non-void across all possible parameter value types. If return is not used, set the `Returns` flag to `false`."
					);
				}
				return false;
			}
			else
			{
				using bool_return_type = typename std::invoke_result<Func, const bool&>::type;
				if constexpr (std::is_void_v<bool_return_type>)
				{
					// Nothing else to do as we know all void by this point
					return true;
				}
				else
				{
					constexpr bool all_return_same_type = is_trait_matching_for_all_possible_param_values_pre<std::is_invocable_r, bool_return_type, Func>();
					if constexpr (all_return_same_type)
					{
						return true;
					}
					else
					{
						if constexpr (Assert)
						{
							static_assert
							(
								EmuCore::TMP::get_false<Func>(),
								"Invalid function type provided as it does not consistently return the same non-void type across all possible parameter value types. If return is not used, set the `Returns` flag to `false`."
							);
						}
						return false;
					}
				}
			}
		}
	}
}

#endif
