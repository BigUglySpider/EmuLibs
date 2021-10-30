#ifndef EMU_MATH_SIMD_HELPERS_ALIASES_H_INC_
#define EMU_MATH_SIMD_HELPERS_ALIASES_H_INC_ 1

#include "_common_simd_helpers_includes.h"

namespace EmuMath::SIMD::TMP
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
			static_assert(false, "Invalid SIMD register width provided. Supported widths: 128, 256, 512.");
			return false;
		}
	}

	template<std::size_t Width_>
	struct integer_register_type
	{
		static_assert(_assert_valid_simd_register_width<Width_>(), "Provided invalid width for integer_register_type finder.");
		using type = std::conditional_t
		<
			Width_ == 128,
			__m128i,
			std::conditional_t
			<
				Width_ == 256,
				__m256i,
				std::conditional_t
				<
					Width_ == 512,
					__m512i,
					void
				>
			>
		>;
	};
	template<std::size_t Width_>
	using integer_register_type_t = typename integer_register_type<Width_>::type;

	template<typename T_, std::size_t Width_ = 128>
	struct register_type
	{
		static_assert(_assert_valid_simd_register_width<Width_>(), "Provided invalid width for register_type finder.");
		using type = typename std::conditional_t
		<
			std::is_integral_v<T_>,
			integer_register_type<Width_>,
			std::void_t<void>
		>::type;
	};

#pragma region SPECIALISATIONS_128_BIT
	template<>
	struct register_type<float, 128>
	{
		using type = __m128;
	};

	template<>
	struct register_type<double, 128>
	{
		using type = __m128d;
	};
#pragma endregion

#pragma region SPECIALISATIONS_256_BIT
	template<>
	struct register_type<float, 256>
	{
		using type = __m256;
	};

	template<>
	struct register_type<double, 256>
	{
		using type = __m256d;
	};
#pragma endregion

#pragma region SPECIALISATIONS_512_BIT
	template<>
	struct register_type<float, 512>
	{
		using type = __m512;
	};

	template<>
	struct register_type<double, 512>
	{
		using type = __m512d;
	};
#pragma endregion

	template<class T_, std::size_t Width_ = 128>
	using register_type_t = typename register_type<T_, Width_>::type;
}

#endif