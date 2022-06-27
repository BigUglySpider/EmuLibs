#ifndef EMU_SIMD_HELPERS_ALIASES_H_INC_
#define EMU_SIMD_HELPERS_ALIASES_H_INC_ 1

#include "_underlying_template_helpers/_common_underlying_simd_template_helper_includes.h"
#include "_underlying_template_helpers/_simd_helpers_underlying_tmp.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD::TMP
{
	[[nodiscard]] inline constexpr bool _valid_simd_register_width(std::size_t width_)
	{
		return width_ == 128 || width_ == 256 || width_ == 512;
	}
	template<std::size_t Width_>
	[[nodiscard]] inline constexpr bool _assert_valid_simd_register_width()
	{
		if constexpr (_valid_simd_register_width(Width_))
		{
			return true;
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<std::size_t, Width_>(), "Invalid SIMD register width provided. Supported widths: 128, 256, 512.");
			return false;
		}
	}

	template<std::size_t Width_ = 128>
	struct integer_register_type
	{
		static_assert(_assert_valid_simd_register_width<Width_>(), "Provided invalid width for integer_register_type finder.");
		using type = std::conditional_t
		<
			Width_ == 128,
			EmuSIMD::i128_generic,
			std::conditional_t
			<
				Width_ == 256,
				EmuSIMD::i256_generic,
				std::conditional_t
				<
					Width_ == 512,
					EmuSIMD::i512_generic,
					void
				>
			>
		>;
	};
	template<std::size_t Width_ = 128>
	using integer_register_type_t = typename integer_register_type<Width_>::type;

	template<std::size_t Width_ = 128>
	struct integer_register_arg_type
	{
		static_assert(_assert_valid_simd_register_width<Width_>(), "Provided invalid width for integer_register_arg_type finder.");
		using type = std::conditional_t
		<
			Width_ == 128,
			EmuSIMD::i128_generic_arg,
			std::conditional_t
			<
				Width_ == 256,
				EmuSIMD::i256_generic_arg,
				std::conditional_t
				<
					Width_ == 512,
					EmuSIMD::i512_generic_arg,
					void
				>
			>
		>;
	};
	template<std::size_t Width_ = 128>
	using integer_register_arg_type_t = typename integer_register_arg_type<Width_>::type;

	template<typename T_, std::size_t Width_ = 128>
	struct register_type
	{
		static_assert(_assert_valid_simd_register_width<Width_>(), "Provided invalid width for register_type finder.");
		using type = typename std::conditional_t
		<
			std::is_integral_v<T_>,
			integer_register_type<Width_>,
			EmuCore::TMP::dummy_type_wrapper<void>
		>::type;
	};

	template<typename T_, std::size_t Width_ = 128>
	struct register_arg_type
	{
		static_assert(_assert_valid_simd_register_width<Width_>(), "Provided invalid width for register_arg_type finder.");
		using type = typename std::conditional_t
		<
			std::is_integral_v<T_>,
			integer_register_arg_type<Width_>,
			EmuCore::TMP::dummy_type_wrapper<void>
		>::type;
	};

#pragma region SPECIALISATIONS_128_BIT
	template<>
	struct register_type<float, 128>
	{
		using type = EmuSIMD::f32x4;
	};

	template<>
	struct register_type<double, 128>
	{
		using type = EmuSIMD::f64x2;
	};

	template<>
	struct register_arg_type<float, 128>
	{
		using type = EmuSIMD::f32x4_arg;
	};

	template<>
	struct register_arg_type<double, 128>
	{
		using type = EmuSIMD::f64x2_arg;
	};
#pragma endregion

#pragma region SPECIALISATIONS_256_BIT
	template<>
	struct register_type<float, 256>
	{
		using type = EmuSIMD::f32x8;
	};

	template<>
	struct register_type<double, 256>
	{
		using type = EmuSIMD::f64x4;
	};

	template<>
	struct register_arg_type<float, 256>
	{
		using type = EmuSIMD::f32x8_arg;
	};

	template<>
	struct register_arg_type<double, 256>
	{
		using type = EmuSIMD::f64x4_arg;
	};
#pragma endregion

#pragma region SPECIALISATIONS_512_BIT
	template<>
	struct register_type<float, 512>
	{
		using type = EmuSIMD::f32x16;
	};

	template<>
	struct register_type<double, 512>
	{
		using type = EmuSIMD::f64x8;
	};

	template<>
	struct register_arg_type<float, 512>
	{
		using type = EmuSIMD::f32x16_arg;
	};

	template<>
	struct register_arg_type<double, 512>
	{
		using type = EmuSIMD::f64x8_arg;
	};
#pragma endregion

	template<class T_, std::size_t Width_ = 128>
	using register_type_t = typename register_type<T_, Width_>::type;

	template<class T_, std::size_t Width_ = 128>
	using register_arg_type_t = typename register_arg_type<T_, Width_>::type;
}

#endif
