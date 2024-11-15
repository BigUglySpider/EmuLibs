#ifndef EMU_IO_ARG_PARSER_PARAMETER_TYPE_HPP_INC_
#define EMU_IO_ARG_PARSER_PARAMETER_TYPE_HPP_INC_ 1

#include <cstdint>
#include <string>
#include <string_view>
#include <type_traits>

#include "../../../EmuCore/CommonConcepts/CommonRequirements.h"
#include "../../../EmuCore/TMPHelpers/Values.h"

namespace EmuIO
{
	enum class ParameterType : std::uint32_t
	{
		Array = 0x10000000,
		Enum  = 0x20000000,
		// TODO: Const

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
	[[nodiscard]] constexpr inline ParameterType type_to_parameter_type_enum()
	{
		if constexpr (std::is_enum_v<typename std::remove_cvref<T>::type>)
		{
			return
			(
				ParameterType::Enum |
				type_to_parameter_type_enum<typename std::underlying_type<typename std::remove_cvref<T>::type>::type>()
			);
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
			static_assert(EmuCore::TMP::get_false<std::is_same_v<T, std::int32_t>>(), "Unsupported ype passed to EmuIO::type_to_parameter_type_enum.");
		}
	}

	template<ParameterType Type>
	struct parameter_type_value
	{
	private:
		[[nodiscard]] static constexpr auto _get() noexcept
		{
			if constexpr ((Type & ParameterType::Int8) == ParameterType::Int8)
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

	[[nodiscard]] constexpr inline std::string_view arg_param_type_to_string(const ParameterType type) noexcept
	{
		using namespace std::string_view_literals;
		switch (type)
		{
		case ParameterType::Int8:
			return "Int8"sv;
		case ParameterType::Int16:
			return "Int16"sv;
		case ParameterType::Int32:
			return "Int32"sv;
		case ParameterType::Int64:
			return "Int64"sv;
		case ParameterType::Uint8:
			return "Uint8"sv;
		case ParameterType::Uint16:
			return "Uint16"sv;
		case ParameterType::Uint32:
			return "Uint32"sv;
		case ParameterType::Uint64:
			return "Uint64"sv;
		case ParameterType::Float32:
			return "Float32"sv;
		case ParameterType::Float64:
			return "Float64"sv;
		case ParameterType::String:
			return "String"sv;

		case ParameterType::Int8Array:
			return "Int8 Array"sv;
		case ParameterType::Int16Array:
			return "Int16 Array"sv;
		case ParameterType::Int32Array:
			return "Int32 Array"sv;
		case ParameterType::Int64Array:
			return "Int64 Array"sv;
		case ParameterType::Uint8Array:
			return "Uint8 Array"sv;
		case ParameterType::Uint16Array:
			return "Uint16 Array"sv;
		case ParameterType::Uint32Array:
			return "Uint32 Array"sv;
		case ParameterType::Uint64Array:
			return "Uint64 Array"sv;
		case ParameterType::Float32Array:
			return "Float32 Array"sv;
		case ParameterType::Float64Array:
			return "Float64 Array"sv;
		case ParameterType::StringArray:
			return "String Array"sv;

		case ParameterType::Int8Enum:
			return "Int8 Enum"sv;
		case ParameterType::Int16Enum:
			return "Int16 Enum"sv;
		case ParameterType::Int32Enum:
			return "Int32 Enum"sv;
		case ParameterType::Int64Enum:
			return "Int64 Enum"sv;
		case ParameterType::Uint8Enum:
			return "Uint8 Enum"sv;
		case ParameterType::Uint16Enum:
			return "Uint16 Enum"sv;
		case ParameterType::Uint32Enum:
			return "Uint32 Enum"sv;
		case ParameterType::Uint64Enum:
			return "Uint64 Enum"sv;
		case ParameterType::Float32Enum:
			return "Float32 Enum"sv;
		case ParameterType::Float64Enum:
			return "Float64 Enum"sv;
		case ParameterType::StringEnum:
			return "String Enum"sv;
		default:
			return "Invalid"sv;
		}
	}
}

#endif
