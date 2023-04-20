#ifndef EMU_SIMD_HELPERS_UNDERLYING_BITWISE_H_INC_
#define EMU_SIMD_HELPERS_UNDERLYING_BITWISE_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "_simd_helpers_underlying_index_masks.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD::_underlying_simd_helpers
{
	template<class Register_>
	[[nodiscard]] inline Register_ _and(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::and_f32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::and_f32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::and_f32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::and_f64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::and_f64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::and_f64x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::and_i32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::and_i32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::and_i32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::and_i8x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::and_i16x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::and_i32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::and_i64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::and_i8x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::and_i16x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::and_i32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::and_i64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::and_i8x64(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::and_i16x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::and_i32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::and_i64x8(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform bitwise AND of a SIMD register using EmuSIMD helpers, but the provided SIMD register is not supported for this operation");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform bitwise AND of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _or(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return _mm_or_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return _mm256_or_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return _mm512_or_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return _mm_or_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return _mm256_or_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return _mm512_or_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				return _mm_or_si128(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				return _mm256_or_si256(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				return _mm512_or_si512(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform bitwise OR of a SIMD register using EmuSIMD helpers, but the provided SIMD register is not supported for this operation");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform bitwise OR of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _xor(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return _mm_xor_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return _mm256_xor_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return _mm512_xor_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return _mm_xor_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return _mm256_xor_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return _mm512_xor_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				return _mm_xor_si128(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				return _mm256_xor_si256(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				return _mm512_xor_si512(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform bitwise XOR of a SIMD register using EmuSIMD helpers, but the provided SIMD register is not supported for this operation");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform bitwise XOR of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _andnot(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return _mm_andnot_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return _mm256_andnot_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return _mm512_andnot_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return _mm_andnot_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return _mm256_andnot_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return _mm512_andnot_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				return _mm_andnot_si128(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				return _mm256_andnot_si256(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				return _mm512_andnot_si512(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform bitwise ANDNOT of a SIMD register using EmuSIMD helpers, but the provided SIMD register is not supported for this operation");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform bitwise ANDNOT of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _not(Register_ to_not_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			constexpr bool is_supported_register_ = EmuCore::TMP::is_any_comparison_true
			<
				std::is_same,
				register_type_uq,
				EmuSIMD::f32x4, EmuSIMD::f32x8, EmuSIMD::f32x16,
				EmuSIMD::f64x2, EmuSIMD::f64x4, EmuSIMD::f64x8,
				EmuSIMD::i128_generic, EmuSIMD::i256_generic, EmuSIMD::i512_generic
			>::value;
			if constexpr (is_supported_register_)
			{
				using all_indices_mask_generator = _underlying_simd_helpers::_per_index_mask<register_type_uq, true>;
				if constexpr (_is_valid_per_index_mask_instance<all_indices_mask_generator>::value)
				{
					// A XOR (11...11) == ~A
					return _xor(to_not_, all_indices_mask_generator::get());
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform bitwise NOT of a SIMD register using EmuSIMD helpers, but a mask to perform the operation could not be successfully generated.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform bitwise NOT of a SIMD register using EmuSIMD helpers, but provided a SIMD register that is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform bitwise NOT of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register.");
		}
	}

#pragma region LEFT_SHIFTS
	template<class Register_, int NumShifts_, std::size_t PerElementWidthIfInt_>
	[[nodiscard]] inline Register_ _shift_left(Register_ lhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;

		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(lhs_), NumShifts_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return _mm256_castsi256_ps(_mm256_slli_epi32(_mm256_castps_si256(lhs_), NumShifts_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return _mm512_castsi512_ps(_mm512_slli_epi32(_mm512_castps_si512(lhs_), NumShifts_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return _mm_castsi128_pd(_mm_slli_epi64(_mm_castpd_si128(lhs_), NumShifts_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return _mm256_castsi256_pd(_mm256_slli_epi64(_mm256_castpd_si256(lhs_), NumShifts_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return _mm512_castsi512_pd(_mm512_slli_epi64(_mm512_castpd_si512(lhs_), NumShifts_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					constexpr char keep_mask = 0xFF << NumShifts_;
					return _mm_and_si128(_mm_set1_epi8(keep_mask), _mm_slli_epi32(lhs_, NumShifts_));
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return _mm_slli_epi16(lhs_, NumShifts_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return _mm_slli_epi32(lhs_, NumShifts_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return _mm_slli_epi64(lhs_, NumShifts_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise left shift of an integral SIMD register using EmuSIMD helpers, but the provided width per element is invalid; only 8, 16, 32, and 64 are valid widths."
					);
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					constexpr char keep_mask = 0xFF << NumShifts_;
					return _mm256_and_si256(_mm256_set1_epi8(keep_mask), _mm256_slli_epi32(lhs_, NumShifts_));
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return _mm256_slli_epi16(lhs_, NumShifts_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return _mm256_slli_epi32(lhs_, NumShifts_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return _mm256_slli_epi64(lhs_, NumShifts_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise left shift of an integral SIMD register using EmuSIMD helpers, but the provided width per element is invalid; only 8, 16, 32, and 64 are valid widths."
					);
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					constexpr char keep_mask = 0xFF << NumShifts_;
					return _mm512_and_si512(_mm512_set1_epi8(keep_mask), _mm512_slli_epi32(lhs_, NumShifts_));
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return _mm512_slli_epi16(lhs_, NumShifts_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return _mm512_slli_epi32(lhs_, NumShifts_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return _mm512_slli_epi64(lhs_, NumShifts_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise left shift of an integral SIMD register using EmuSIMD helpers, but the provided width per element is invalid; only 8, 16, 32, and 64 are valid widths."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Register_>(),
					"Attempted to perform bitwise left shift of a SIMD register using EmuSIMD helpers, but the provided SIMD register is not supported for this operation"
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Register_>(),
				"Attempted to perform bitwise left shift of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register."
			);
		}
	}

	template<class Register_, std::size_t PerElementWidthIfInt_>
	[[nodiscard]] inline Register_ _shift_left(Register_ lhs_, EmuSIMD::i128_generic rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;

		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return _mm_castsi128_ps(_mm_sll_epi32(_mm_castps_si128(lhs_), rhs_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return _mm256_castsi256_ps(_mm256_sll_epi32(_mm256_castps_si256(lhs_), rhs_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return _mm512_castsi512_ps(_mm512_sll_epi32(_mm512_castps_si512(lhs_), rhs_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return _mm_castsi128_pd(_mm_sll_epi64(_mm_castpd_si128(lhs_), rhs_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return _mm256_castsi256_pd(_mm256_sll_epi64(_mm256_castpd_si256(lhs_), rhs_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return _mm512_castsi512_pd(_mm512_sll_epi64(_mm512_castpd_si512(lhs_), rhs_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise left-shift of an 8-bit integral SIMD register using EmuSIMD registers, with a SIMD register shift argument. This function is not available with register arguments; if a constant argument for each shift is possible, use the function which takes a template NumShifts_ argument instead."
					);
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return _mm_sll_epi16(lhs_, rhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return _mm_sll_epi32(lhs_, rhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return _mm_sll_epi64(lhs_, rhs_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise left shift of an integral SIMD register using EmuSIMD helpers, but the provided width per element is invalid; only 8, 16, 32, and 64 are valid widths."
					);
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise left-shift of an 8-bit integral SIMD register using EmuSIMD registers, with a SIMD register shift argument. This function is not available with register arguments; if a constant argument for each shift is possible, use the function which takes a template NumShifts_ argument instead."
					);
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return _mm256_sll_epi16(lhs_, rhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return _mm256_sll_epi32(lhs_, rhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return _mm256_sll_epi64(lhs_, rhs_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise left shift of an integral SIMD register using EmuSIMD helpers, but the provided width per element is invalid; only 8, 16, 32, and 64 are valid widths."
					);
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise left-shift of an 8-bit integral SIMD register using EmuSIMD registers, with a SIMD register shift argument. This function is not available with register arguments; if a constant argument for each shift is possible, use the function which takes a template NumShifts_ argument instead."
					);
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return _mm512_sll_epi16(lhs_, rhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return _mm512_sll_epi32(lhs_, rhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return _mm512_sll_epi64(lhs_, rhs_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise left shift of an integral SIMD register using EmuSIMD helpers, but the provided width per element is invalid; only 8, 16, 32, and 64 are valid widths."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Register_>(),
					"Attempted to perform bitwise left shift of a SIMD register using EmuSIMD helpers, but the provided SIMD register is not supported for this operation"
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Register_>(),
				"Attempted to perform bitwise left shift of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register."
			);
		}
	}
#pragma endregion

#pragma region ARITHMETIC_RIGHT_SHIFTS
	template<class Register_, int NumShifts_, std::size_t PerElementWidthIfInt_>
	[[nodiscard]] inline Register_ _shift_right_arithmetic(Register_ lhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;

		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return _mm_castsi128_ps(_mm_srai_epi32(_mm_castps_si128(lhs_), NumShifts_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return _mm256_castsi256_ps(_mm256_srai_epi32(_mm256_castps_si256(lhs_), NumShifts_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return _mm512_castsi512_ps(_mm512_srai_epi32(_mm512_castps_si512(lhs_), NumShifts_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return _mm_castsi128_pd(_mm_srai_epi64(_mm_castpd_si128(lhs_), NumShifts_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return _mm256_castsi256_pd(_mm256_srai_epi64(_mm256_castpd_si256(lhs_), NumShifts_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return _mm512_castsi512_pd(_mm512_srai_epi64(_mm512_castpd_si512(lhs_), NumShifts_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					constexpr char keep_mask = 0xFF >> NumShifts_;
					return _mm_and_si128(_mm_set1_epi8(keep_mask), _mm_srai_epi32(lhs_, NumShifts_));
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return _mm_srai_epi16(lhs_, NumShifts_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return _mm_srai_epi32(lhs_, NumShifts_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return _mm_srai_epi64(lhs_, NumShifts_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise arithmetic right shift of an integral SIMD register using EmuSIMD helpers, but the provided width per element is invalid; only 8, 16, 32, and 64 are valid widths."
					);
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					constexpr char keep_mask = 0xFF >> NumShifts_;
					return _mm256_and_si256(_mm256_set1_epi8(keep_mask), _mm256_srai_epi32(lhs_, NumShifts_));
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return _mm256_srai_epi16(lhs_, NumShifts_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return _mm256_srai_epi32(lhs_, NumShifts_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return _mm256_srai_epi64(lhs_, NumShifts_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise arithmetic right shift of an integral SIMD register using EmuSIMD helpers, but the provided width per element is invalid; only 8, 16, 32, and 64 are valid widths."
					);
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					constexpr char keep_mask = 0xFF << NumShifts_;
					return _mm512_and_si512(_mm512_set1_epi8(keep_mask), _mm512_srai_epi32(lhs_, NumShifts_));
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return _mm512_srai_epi16(lhs_, NumShifts_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return _mm512_srai_epi32(lhs_, NumShifts_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return _mm512_srai_epi64(lhs_, NumShifts_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise arithmetic right shift of an integral SIMD register using EmuSIMD helpers, but the provided width per element is invalid; only 8, 16, 32, and 64 are valid widths."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Register_>(),
					"Attempted to perform bitwise arithmetic right shift of a SIMD register using EmuSIMD helpers, but the provided SIMD register is not supported for this operation"
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Register_>(),
				"Attempted to perform bitwise arithmetic right shift of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register."
			);
		}
	}

	template<class Register_, std::size_t PerElementWidthIfInt_>
	[[nodiscard]] inline Register_ _shift_right_arithmetic(Register_ lhs_, EmuSIMD::i128_generic rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;

		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return _mm_castsi128_ps(_mm_sra_epi32(_mm_castps_si128(lhs_), rhs_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return _mm256_castsi256_ps(_mm256_sra_epi32(_mm256_castps_si256(lhs_), rhs_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return _mm512_castsi512_ps(_mm512_sra_epi32(_mm512_castps_si512(lhs_), rhs_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return _mm_castsi128_pd(_mm_sra_epi64(_mm_castpd_si128(lhs_), rhs_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return _mm256_castsi256_pd(_mm256_sra_epi64(_mm256_castpd_si256(lhs_), rhs_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return _mm512_castsi512_pd(_mm512_sra_epi64(_mm512_castpd_si512(lhs_), rhs_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise arithmetic right shift of an 8-bit integral SIMD register using EmuSIMD registers, with a SIMD register shift argument. This function is not available with register arguments; if a constant argument for each shift is possible, use the function which takes a template NumShifts_ argument instead."
					);
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return _mm_sra_epi16(lhs_, rhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return _mm_sra_epi32(lhs_, rhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return _mm_sra_epi64(lhs_, rhs_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise arithmetic right shift of an integral SIMD register using EmuSIMD helpers, but the provided width per element is invalid; only 8, 16, 32, and 64 are valid widths."
					);
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise arithmetic right shift of an 8-bit integral SIMD register using EmuSIMD registers, with a SIMD register shift argument. This function is not available with register arguments; if a constant argument for each shift is possible, use the function which takes a template NumShifts_ argument instead."
					);
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return _mm256_sra_epi16(lhs_, rhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return _mm256_sra_epi32(lhs_, rhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return _mm256_sra_epi64(lhs_, rhs_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise arithmetic right shift of an integral SIMD register using EmuSIMD helpers, but the provided width per element is invalid; only 8, 16, 32, and 64 are valid widths."
					);
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise arithmetic right shift of an 8-bit integral SIMD register using EmuSIMD registers, with a SIMD register shift argument. This function is not available with register arguments; if a constant argument for each shift is possible, use the function which takes a template NumShifts_ argument instead."
					);
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return _mm512_sra_epi16(lhs_, rhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return _mm512_sra_epi32(lhs_, rhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return _mm512_sra_epi64(lhs_, rhs_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise arithmetic right shift of an integral SIMD register using EmuSIMD helpers, but the provided width per element is invalid; only 8, 16, 32, and 64 are valid widths."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Register_>(),
					"Attempted to perform bitwise arithmetic right shift of a SIMD register using EmuSIMD helpers, but the provided SIMD register is not supported for this operation"
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Register_>(),
				"Attempted to perform bitwise arithmetic right shift of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register."
			);
		}
	}
#pragma endregion

#pragma region LOGCAL_RIGHT_SHIFTS
	template<class Register_, int NumShifts_, std::size_t PerElementWidthIfInt_>
	[[nodiscard]] inline Register_ _shift_right_logical(Register_ lhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;

		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return _mm_castsi128_ps(_mm_srli_epi32(_mm_castps_si128(lhs_), NumShifts_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return _mm256_castsi256_ps(_mm256_srli_epi32(_mm256_castps_si256(lhs_), NumShifts_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return _mm512_castsi512_ps(_mm512_srli_epi32(_mm512_castps_si512(lhs_), NumShifts_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return _mm_castsi128_pd(_mm_srli_epi64(_mm_castpd_si128(lhs_), NumShifts_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return _mm256_castsi256_pd(_mm256_srli_epi64(_mm256_castpd_si256(lhs_), NumShifts_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return _mm512_castsi512_pd(_mm512_srli_epi64(_mm512_castpd_si512(lhs_), NumShifts_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					constexpr char keep_mask = 0xFF >> NumShifts_;
					return _mm_and_si128(_mm_set1_epi8(keep_mask), _mm_srli_epi32(lhs_, NumShifts_));
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return _mm_srli_epi16(lhs_, NumShifts_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return _mm_srli_epi32(lhs_, NumShifts_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return _mm_srli_epi64(lhs_, NumShifts_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise logical right shift of an integral SIMD register using EmuSIMD helpers, but the provided width per element is invalid; only 8, 16, 32, and 64 are valid widths."
					);
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					constexpr char keep_mask = 0xFF >> NumShifts_;
					return _mm256_and_si256(_mm256_set1_epi8(keep_mask), _mm256_srli_epi32(lhs_, NumShifts_));
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return _mm256_srli_epi16(lhs_, NumShifts_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return _mm256_srli_epi32(lhs_, NumShifts_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return _mm256_srli_epi64(lhs_, NumShifts_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise logical right shift of an integral SIMD register using EmuSIMD helpers, but the provided width per element is invalid; only 8, 16, 32, and 64 are valid widths."
					);
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					constexpr char keep_mask = 0xFF << NumShifts_;
					return _mm512_and_si512(_mm512_set1_epi8(keep_mask), _mm512_srli_epi32(lhs_, NumShifts_));
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return _mm512_srli_epi16(lhs_, NumShifts_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return _mm512_srli_epi32(lhs_, NumShifts_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return _mm512_srli_epi64(lhs_, NumShifts_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise logical right shift of an integral SIMD register using EmuSIMD helpers, but the provided width per element is invalid; only 8, 16, 32, and 64 are valid widths."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Register_>(),
					"Attempted to perform bitwise logical right shift of a SIMD register using EmuSIMD helpers, but the provided SIMD register is not supported for this operation"
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Register_>(),
				"Attempted to perform bitwise logical right shift of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register."
			);
		}
	}

	template<class Register_, std::size_t PerElementWidthIfInt_>
	[[nodiscard]] inline Register_ _shift_right_logical(Register_ lhs_, EmuSIMD::i128_generic rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;

		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return _mm_castsi128_ps(_mm_srl_epi32(_mm_castps_si128(lhs_), rhs_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return _mm256_castsi256_ps(_mm256_srl_epi32(_mm256_castps_si256(lhs_), rhs_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return _mm512_castsi512_ps(_mm512_srl_epi32(_mm512_castps_si512(lhs_), rhs_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return _mm_castsi128_pd(_mm_srl_epi64(_mm_castpd_si128(lhs_), rhs_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return _mm256_castsi256_pd(_mm256_srl_epi64(_mm256_castpd_si256(lhs_), rhs_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return _mm512_castsi512_pd(_mm512_srl_epi64(_mm512_castpd_si512(lhs_), rhs_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise logical right shift of an 8-bit integral SIMD register using EmuSIMD registers, with a SIMD register shift argument. This function is not available with register arguments; if a constant argument for each shift is possible, use the function which takes a template NumShifts_ argument instead."
					);
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return _mm_srl_epi16(lhs_, rhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return _mm_srl_epi32(lhs_, rhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return _mm_srl_epi64(lhs_, rhs_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise logical right shift of an integral SIMD register using EmuSIMD helpers, but the provided width per element is invalid; only 8, 16, 32, and 64 are valid widths."
					);
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise logical right shift of an 8-bit integral SIMD register using EmuSIMD registers, with a SIMD register shift argument. This function is not available with register arguments; if a constant argument for each shift is possible, use the function which takes a template NumShifts_ argument instead."
					);
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return _mm256_srl_epi16(lhs_, rhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return _mm256_srl_epi32(lhs_, rhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return _mm256_srl_epi64(lhs_, rhs_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise logical right shift of an integral SIMD register using EmuSIMD helpers, but the provided width per element is invalid; only 8, 16, 32, and 64 are valid widths."
					);
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise logical right shift of an 8-bit integral SIMD register using EmuSIMD registers, with a SIMD register shift argument. This function is not available with register arguments; if a constant argument for each shift is possible, use the function which takes a template NumShifts_ argument instead."
					);
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return _mm512_srl_epi16(lhs_, rhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return _mm512_srl_epi32(lhs_, rhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return _mm512_srl_epi64(lhs_, rhs_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to perform bitwise logical right shift of an integral SIMD register using EmuSIMD helpers, but the provided width per element is invalid; only 8, 16, 32, and 64 are valid widths."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Register_>(),
					"Attempted to perform bitwise logical right shift of a SIMD register using EmuSIMD helpers, but the provided SIMD register is not supported for this operation"
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Register_>(),
				"Attempted to perform bitwise logical right shift of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register."
			);
		}
	}
#pragma endregion
}

#endif
