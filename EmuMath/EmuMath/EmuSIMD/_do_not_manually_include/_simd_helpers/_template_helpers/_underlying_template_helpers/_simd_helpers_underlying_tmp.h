#ifndef EMU_SIMD_UNDERLYING_SIMD_HELPERS_TMP_H_INC_
#define EMU_SIMD_UNDERLYING_SIMD_HELPERS_TMP_H_INC_ 1

#include "../../../../../EmuCore/ArithmeticHelpers/BitHelpers.h"
#include "../../../../../EmuCore/TMPHelpers/TypeComparators.h"
#include "../../../../../EmuCore/TMPHelpers/TypeConvertors.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"
#include <cstdlib>
#include <immintrin.h>
#include <stdexcept>

namespace EmuSIMD::TMP
{
	[[nodiscard]] constexpr inline bool _valid_simd_int_element_width(std::size_t width_)
	{
		return width_ == 8 || width_ == 16 || width_ == 32 || width_ == 64;
	}
	template<std::size_t Width_>
	constexpr inline bool _assert_valid_simd_int_element_width()
	{
		if constexpr (_valid_simd_int_element_width(Width_))
		{
			return true;
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<std::size_t, Width_>(), "Invalid element width for a SIMD register provided. Valid per-element widths for integral SIMD registers are: 8, 16, 32, 64.");
			return false;
		}
	}

	template<class RegisterType_>
	struct is_simd_register
	{
		static constexpr bool value = std::conditional_t
		<
			std::is_same_v<RegisterType_, typename EmuCore::TMP::remove_ref_cv<RegisterType_>::type>,
			std::false_type,
			is_simd_register<typename EmuCore::TMP::remove_ref_cv<RegisterType_>::type>
		>::value;
	};
	template<>
	struct is_simd_register<__m128>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_simd_register<__m128d>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_simd_register<__m128i>
	{
		static constexpr bool value = true;
	};

	template<>
	struct is_simd_register<__m256>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_simd_register<__m256d>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_simd_register<__m256i>
	{
		static constexpr bool value = true;
	};

	template<>
	struct is_simd_register<__m512>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_simd_register<__m512d>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_simd_register<__m512i>
	{
		static constexpr bool value = true;
	};
	template<class Register_>
	static constexpr bool is_simd_register_v = is_simd_register<Register_>::value;

	template<class Register_>
	struct simd_register_width
	{
		// Formed as a recursive call on itself if the passed type is a SIMD register, since unqualified specialisations are used for value sets.

		static constexpr std::size_t value = std::conditional_t
		<
			is_simd_register_v<Register_>,
			simd_register_width<typename EmuCore::TMP::remove_ref_cv<Register_>::type>,
			std::integral_constant<std::size_t, 0>
		>::value;
	};
	template<>
	struct simd_register_width<__m128>
	{
		static constexpr std::size_t value = 128;
	};
	template<>
	struct simd_register_width<__m128d>
	{
		static constexpr std::size_t value = 128;
	};
	template<>
	struct simd_register_width<__m128i>
	{
		static constexpr std::size_t value = 128;
	};
	template<>
	struct simd_register_width<__m256>
	{
		static constexpr std::size_t value = 256;
	};
	template<>
	struct simd_register_width<__m256d>
	{
		static constexpr std::size_t value = 256;
	};
	template<>
	struct simd_register_width<__m256i>
	{
		static constexpr std::size_t value = 256;
	};
	template<>
	struct simd_register_width<__m512>
	{
		static constexpr std::size_t value = 512;
	};
	template<>
	struct simd_register_width<__m512d>
	{
		static constexpr std::size_t value = 512;
	};
	template<>
	struct simd_register_width<__m512i>
	{
		static constexpr std::size_t value = 512;
	};
	template<class Register_>
	static constexpr std::size_t simd_register_width_v = simd_register_width<Register_>::value;

	template<class Register_>
	struct is_integral_simd_register
	{
		// Formed as a recursive call on itself if the passed type is a SIMD register, since unqualified specialisations are used for value sets.

		static constexpr bool value = std::conditional_t
		<
			is_simd_register_v<Register_>,
			is_integral_simd_register<typename EmuCore::TMP::remove_ref_cv<Register_>::type>,
			std::false_type
		>::value;
	};
	template<>
	struct is_integral_simd_register<__m128>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_integral_simd_register<__m128d>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_integral_simd_register<__m128i>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_integral_simd_register<__m256>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_integral_simd_register<__m256d>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_integral_simd_register<__m256i>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_integral_simd_register<__m512>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_integral_simd_register<__m512d>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_integral_simd_register<__m512i>
	{
		static constexpr bool value = true;
	};
	template<class Register_>
	static constexpr bool is_integral_simd_register_v = is_integral_simd_register<Register_>::value;

	template<class Register_>
	struct is_floating_point_simd_register
	{
		// Solved via an inversion of a deferred call to is_integral_simd_register if we know this is a simd register.
		// --- Otherwise, we invert the value of true_type, which is equal to false.

		static constexpr bool value = !std::conditional_t
		<
			is_simd_register_v<Register_>,
			is_integral_simd_register<Register_>,
			std::true_type
		>::value;
	};
	template<class Register_>
	static constexpr bool is_floating_point_simd_register_v = is_floating_point_simd_register<Register_>::value;

	template<class Register_>
	struct floating_point_register_element_count
	{
		// Formed as a recursive call on itself if the passed type is a FP SIMD register, since unqualified specialisations are used for value sets.

		static constexpr std::size_t value = std::conditional_t
		<
			is_floating_point_simd_register_v<Register_>,
			floating_point_register_element_count<typename EmuCore::TMP::remove_ref_cv<Register_>::type>,
			0
		>;
	};
	template<>
	struct floating_point_register_element_count<__m128>
	{
		static constexpr std::size_t value = 4;
	};
	template<>
	struct floating_point_register_element_count<__m128d>
	{
		static constexpr std::size_t value = 2;
	};
	template<>
	struct floating_point_register_element_count<__m256>
	{
		static constexpr std::size_t value = 8;
	};
	template<>
	struct floating_point_register_element_count<__m256d>
	{
		static constexpr std::size_t value = 4;
	};
	template<>
	struct floating_point_register_element_count<__m512>
	{
		static constexpr std::size_t value = 16;
	};
	template<>
	struct floating_point_register_element_count<__m512d>
	{
		static constexpr std::size_t value = 8;
	};
	template<class Register_>
	static constexpr std::size_t floating_point_register_element_count_v = floating_point_register_element_count<Register_>::value;

	template<class Register_, std::size_t Index_, std::size_t PerElementWidthIfIntegral_ = 32>
	struct valid_register_index
	{
		// Formed as a recursive call on itself if the passed type is a SIMD register, since unqualified specialisations are used for value sets.

		static constexpr bool value = std::conditional_t
		<
			is_simd_register_v<Register_> && !std::is_same_v<Register_, typename EmuCore::TMP::remove_ref_cv<Register_>::type>,
			valid_register_index<typename EmuCore::TMP::remove_ref_cv<Register_>::type>,
			std::false_type
		>::value;
	};
	template<std::size_t Index_, std::size_t PerElementWidthIfIntegral_>
	struct valid_register_index<__m128, Index_, PerElementWidthIfIntegral_>
	{
		static constexpr std::size_t max_index = std::size_t(3);
		static constexpr bool value = Index_ <= max_index;
	};
	template<std::size_t Index_, std::size_t PerElementWidthIfIntegral_>
	struct valid_register_index<__m256, Index_, PerElementWidthIfIntegral_>
	{
		static constexpr std::size_t max_index = std::size_t(7);
		static constexpr bool value = Index_ <= max_index;
	};
	template<std::size_t Index_, std::size_t PerElementWidthIfIntegral_>
	struct valid_register_index<__m512, Index_, PerElementWidthIfIntegral_>
	{
		static constexpr std::size_t max_index = std::size_t(15);
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfIntegral_>
	struct valid_register_index<__m128d, Index_, PerElementWidthIfIntegral_>
	{
		static constexpr std::size_t max_index = std::size_t(1);
		static constexpr bool value = Index_ <= max_index;
	};
	template<std::size_t Index_, std::size_t PerElementWidthIfIntegral_>
	struct valid_register_index<__m256d, Index_, PerElementWidthIfIntegral_>
	{
		static constexpr std::size_t max_index = std::size_t(3);
		static constexpr bool value = Index_ <= max_index;
	};
	template<std::size_t Index_, std::size_t PerElementWidthIfIntegral_>
	struct valid_register_index<__m512d, Index_, PerElementWidthIfIntegral_>
	{
		static constexpr std::size_t max_index = std::size_t(7);
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidth_>
	struct valid_register_index<__m128i, Index_, PerElementWidth_>
	{
		static constexpr bool valid_element_width = _assert_valid_simd_int_element_width<PerElementWidth_>();
		static_assert(valid_element_width, "Invalid per-element width provided when checking for a valid integral SIMD register index via valid_register_index.");

		static constexpr std::size_t max_index = (simd_register_width_v<__m128i> / PerElementWidth_) - std::size_t(1);
		static constexpr bool value = Index_ <= max_index;
	};
	template<std::size_t Index_, std::size_t PerElementWidth_>
	struct valid_register_index<__m256i, Index_, PerElementWidth_>
	{
		static constexpr bool valid_element_width = _assert_valid_simd_int_element_width<PerElementWidth_>();
		static_assert(valid_element_width, "Invalid per-element width provided when checking for a valid integral SIMD register index via valid_register_index.");

		static constexpr std::size_t max_index = (simd_register_width_v<__m256i> / PerElementWidth_) - std::size_t(1);
		static constexpr bool value = Index_ <= max_index;
	};
	template<std::size_t Index_, std::size_t PerElementWidth_>
	struct valid_register_index<__m512i, Index_, PerElementWidth_>
	{
		static constexpr bool valid_element_width = _assert_valid_simd_int_element_width<PerElementWidth_>();
		static_assert(valid_element_width, "Invalid per-element width provided when checking for a valid integral SIMD register index via valid_register_index.");

		static constexpr std::size_t max_index = (simd_register_width_v<__m512i> / PerElementWidth_) - std::size_t(1);
		static constexpr bool value = Index_ <= max_index;
	};
	template<class Register_, std::size_t Index_, std::size_t PerElementWidthIfIntegral_ = 32>
	static constexpr bool valid_register_index_v = valid_register_index<Register_, Index_, PerElementWidthIfIntegral_>::value;
}

#endif
