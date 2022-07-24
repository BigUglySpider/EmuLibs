#ifndef EMU_SIMD_HELPERS_UNDERLYING_GET_H_INC_
#define EMU_SIMD_HELPERS_UNDERLYING_GET_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "_simd_helpers_underlying_shuffle.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD::_underlying_simd_helpers
{
	template<std::size_t Index_, typename OutT_, std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline OutT_ _get_register_index(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::f32x4, EmuSIMD::f32x8, EmuSIMD::f32x16>::value)
			{
				if constexpr (EmuCore::TMP::is_static_castable_v<float, OutT_>)
				{
					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
					{
						if constexpr (Index_ <= 3)
						{
							if constexpr (Index_ != 0)
							{
								return static_cast<OutT_>(_mm_cvtss_f32(_execute_shuffle<Index_>(register_)));
							}
							else
							{
								return static_cast<OutT_>(_mm_cvtss_f32(register_));
							}
						}
						else
						{
							static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to extract an index from a 128-bit float SIMD register using EmuSIMD helpers, but the provided Index_ was invalid. Valid indices: 0, 1, 2, 3.");
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
					{
						if constexpr (Index_ <= 7)
						{
							constexpr int is_hi_ = static_cast<int>(Index_ >= 4);
							constexpr std::size_t index_in_half_ = Index_ - (4 * is_hi_);
							return _get_register_index<index_in_half_, OutT_, PerElementWidthIfInt_>(_mm256_extractf128_ps(register_, is_hi_));
						}
						else
						{
							static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to extract an index from a 256-bit float SIMD register using EmuSIMD helpers, but the provided Index_ was invalid. Valid indices: 0, 1, 2, 3, 4, 5, 6, 7.");
						}
					}
					else
					{
						if constexpr (Index_ <= 15)
						{
							constexpr int chunk_index_ = static_cast<int>(Index_ / 4);
							constexpr std::size_t index_128_ = Index_ - (4 * chunk_index_);
							return _get_register_index<index_128_, OutT_, PerElementWidthIfInt_>(_mm512_extractf32x4_ps(register_, chunk_index_));
						}
						else
						{
							static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to extract an index from a 512-bit float SIMD register using EmuSIMD helpers, but the provided Index_ was invalid. Valid indices: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15.");
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to extract an index from a float-containing SIMD register using EmuSIMD helpers, but the provided output type cannot be created from a float value.");
				}
			}
			else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::f64x2, EmuSIMD::f64x4, EmuSIMD::f64x8>::value)
			{
				if constexpr (EmuCore::TMP::is_static_castable_v<double, OutT_>)
				{
					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
					{
						if constexpr (Index_ <= 1)
						{
							if constexpr (Index_ != 0)
							{
								return static_cast<OutT_>(_mm_cvtsd_f64(_execute_shuffle<Index_>(register_)));
							}
							else
							{
								return static_cast<OutT_>(_mm_cvtsd_f64(register_));
							}
						}
						else
						{
							static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to extract an index from a 128-bit double SIMD register using EmuSIMD helpers, but the provided Index_ was invalid. Valid indices: 0, 1.");
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
					{
						if constexpr (Index_ <= 3)
						{
							constexpr int is_hi_ = static_cast<int>(Index_ >= 2);
							constexpr std::size_t index_128_ = Index_ - (2 * is_hi_);
							return _get_register_index<index_128_, OutT_, PerElementWidthIfInt_>(_mm256_extractf128_pd(register_, is_hi_));
						}
						else
						{
							static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to extract an index from a 256-bit double SIMD register using EmuSIMD helpers, but the provided Index_ was invalid. Valid indices: 0, 1, 2, 3.");
						}
					}
					else
					{
						if constexpr (Index_ <= 7)
						{
							constexpr int chunk_index_ = static_cast<int>(Index_ / 2);
							constexpr std::size_t index_128_ = Index_ - (2 * chunk_index_);
							return _get_register_index<index_128_, OutT_, PerElementWidthIfInt_>(_mm512_extractf64x2_pd(register_, chunk_index_));
						}
						else
						{
							static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to extract an index from a 512-bit double SIMD register using EmuSIMD helpers, but the provided Index_ was invalid. Valid indices: 0, 1, 2, 3, 4, 5, 6, 7.");
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to extract an index from a double-containing SIMD register using EmuSIMD helpers, but the provided output type cannot be created from a double value.");
				}
			}
			else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::i128_generic, EmuSIMD::i256_generic, EmuSIMD::i512_generic>::value)
			{
				if constexpr(EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidthIfInt_>())
				{
					using int_type = EmuCore::TMP::int_of_size_t<PerElementWidthIfInt_ / 8>;
					if constexpr (EmuCore::TMP::is_static_castable_v<int_type, OutT_>)
					{
						constexpr std::size_t chunk_divisor_ = std::size_t(128) / PerElementWidthIfInt_;
						if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
						{
							constexpr std::size_t first_invalid_index_ = chunk_divisor_;
							if constexpr (Index_ < first_invalid_index_)
							{
								constexpr int index_as_int_ = static_cast<int>(Index_);
								if constexpr (PerElementWidthIfInt_ == 8)
								{
									return static_cast<OutT_>(_mm_extract_epi8(register_, index_as_int_));
								}
								else if constexpr (PerElementWidthIfInt_ == 16)
								{
									return static_cast<OutT_>(_mm_extract_epi16(register_, index_as_int_));
								}
								else if constexpr (PerElementWidthIfInt_ == 32)
								{
									return static_cast<OutT_>(_mm_extract_epi32(register_, index_as_int_));
								}
								else
								{
									return static_cast<OutT_>(_mm_extract_epi64(register_, index_as_int_));
								}
							}
							else
							{
								static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to extract an index from a 128-bit integral SIMD register using EmuSIMD helpers, but the provided index is invalid for the provided width. The valid index range is 0:(128 / PerElementWidthIfInt_)-1.");
							}
						}
						else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
						{
							constexpr std::size_t first_invalid_index_ = std::size_t(256) / PerElementWidthIfInt_;
							if constexpr (Index_ < first_invalid_index_)
							{
								constexpr int is_hi_ = static_cast<int>(Index_ >= chunk_divisor_);
								constexpr std::size_t index_in_chunk_ = Index_ - (chunk_divisor_ * is_hi_);
								return _get_register_index<index_in_chunk_, OutT_, PerElementWidthIfInt_>(_mm256_extractf128_si256(register_, is_hi_));
							}
							else
							{
								static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to extract an index from a 256-bit integral SIMD register using EmuSIMD helpers, but the provided index is invalid for the provided width. The valid index range is 0:(256 / PerElementWidthIfInt_)-1.");
							}
						}
						else
						{
							constexpr std::size_t first_invalid_index_ = std::size_t(512) / PerElementWidthIfInt_;
							if constexpr (Index_ < first_invalid_index_)
							{
								constexpr int chunk_index_ = static_cast<int>(Index_ / chunk_divisor_);
								constexpr std::size_t index_in_chunk_ = Index_ - (index_in_chunk_ * chunk_divisor_);
								return _get_register_index<index_in_chunk_, OutT_, PerElementWidthIfInt_>(_mm512_extracti32x4_epi32(register_, chunk_index_));
							}
							else
							{
								static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to extract an index from a 512-bit integral SIMD register using EmuSIMD helpers, but the provided index is invalid for the provided width. The valid index range is 0:(512 / PerElementWidthIfInt_)-1.");
							}
						}
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to extract an index from an integral SIMD register using EmuSIMD helpers, but the provided output type cannot be created from an integer of the provided width.");
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to extract an index from an integral SIMD register using EmuSIMD helpers, but the provided bit width per element is invalid.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to extract an index from a SIMD register using EmuSIMD helpers, but the provided SIMD register is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to extract an index from a SIMD register using EmuSIMD helpers, but the provided register is not a supported SIMD register type.");
		}
	}

	template<typename Out_, class Register_, typename NoConstReq_ = std::enable_if_t<!std::is_const_v<Out_>>>
	[[nodiscard]] inline void _store_register(Register_ register_, Out_* p_out_)
	{
		if constexpr (EmuSIMD::TMP::is_simd_register_v<Register_>)
		{
			using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				_mm_store_ps(reinterpret_cast<float*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				_mm_store_pd(reinterpret_cast<double*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				_mm256_store_ps(reinterpret_cast<float*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				_mm256_store_pd(reinterpret_cast<double*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				_mm512_store_ps(reinterpret_cast<void*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				_mm512_store_pd(reinterpret_cast<void*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				_mm_store_si128(reinterpret_cast<EmuSIMD::i128_generic*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				_mm256_store_si256(reinterpret_cast<EmuSIMD::i256_generic*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				_mm512_store_si512(reinterpret_cast<void*>(p_out_), register_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to store a SIMD register to a pointer via an EmuSIMD helper, but the provided register_ could not be recognised.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to store a SIMD register to a pointer via an EmuSIMD helper, but the provided register_ was not a supported SIMD register.");
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::f32x4 _extract_lane_f32x4_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x4>)
		{
			return EmuSIMD::f32x4(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return _mm256_extractf128_ps(std::forward<In_>(in_), LaneIndex_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return _mm512_extractf32x4_ps(std::forward<In_>(in_), LaneIndex_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x2>)
		{
			return EmuSIMD::Funcs::cast_f64x2_f32x4(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::cast_f64x2_f32x4(_mm256_extractf128_pd(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::cast_f64x2_f32x4(_mm512_extractf64x2_pd(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i128_generic, EmuSIMD::i8x16, EmuSIMD::i16x8, EmuSIMD::i32x4, EmuSIMD::i64x2>)
		{
			return EmuSIMD::Funcs::cast_i32x4_f32x4(std::forward<In_>(in_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i256_generic, EmuSIMD::i8x32, EmuSIMD::i16x16, EmuSIMD::i32x8, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::cast_i32x4_f32x4(_mm256_extracti128_si256(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i512_generic, EmuSIMD::i8x64, EmuSIMD::i16x32, EmuSIMD::i32x16, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::cast_i32x4_f32x4(_mm512_extracti32x4_epi32(std::forward<In_>(in_), LaneIndex_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a f32x4 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::f32x8 _extract_lane_f32x8_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::f32x8(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return _mm512_extractf32x8_ps(std::forward<In_>(in_), LaneIndex_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::cast_f64x4_f32x8(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::cast_f64x4_f32x8(_mm512_extractf64x4_pd(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i256_generic, EmuSIMD::i8x32, EmuSIMD::i16x16, EmuSIMD::i32x8, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::cast_i32x8_f32x8(std::forward<In_>(in_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i512_generic, EmuSIMD::i8x64, EmuSIMD::i16x32, EmuSIMD::i32x16, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::cast_i32x8_f32x8(_mm512_extracti32x8_epi32(std::forward<In_>(in_), LaneIndex_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a f32x8 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::f32x16 _extract_lane_f32x16_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::f32x16(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::cast_f64x8_f32x16(std::forward<In_>(in_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i512_generic, EmuSIMD::i8x64, EmuSIMD::i16x32, EmuSIMD::i32x16, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::cast_i32x16_f32x16(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a f32x16 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::f64x2 _extract_lane_f64x2_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x4>)
		{
			return EmuSIMD::Funcs::cast_f32x4_f64x2(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::cast_f32x4_f64x2(_mm256_extractf128_ps(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::cast_f32x4_f64x2(_mm512_extractf32x4_ps(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x2>)
		{
			return EmuSIMD::f64x2(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return _mm256_extractf128_pd(std::forward<In_>(in_), LaneIndex_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return _mm512_extractf64x2_pd(std::forward<In_>(in_), LaneIndex_);
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i128_generic, EmuSIMD::i8x16, EmuSIMD::i16x8, EmuSIMD::i32x4, EmuSIMD::i64x2>)
		{
			return EmuSIMD::Funcs::cast_i64x2_f64x2(std::forward<In_>(in_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i256_generic, EmuSIMD::i8x32, EmuSIMD::i16x16, EmuSIMD::i32x8, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::cast_i64x2_f64x2(_mm256_extracti128_si256(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i512_generic, EmuSIMD::i8x64, EmuSIMD::i16x32, EmuSIMD::i32x16, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::cast_i64x2_f64x2(_mm512_extracti64x2_epi64(std::forward<In_>(in_), LaneIndex_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a f64x2 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::f64x4 _extract_lane_f64x4_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::cast_f32x8_f64x4(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::cast_f32x8_f64x4(_mm512_extractf32x8_ps(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::f64x4(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return _mm512_extractf64x4_pd(std::forward<In_>(in_), LaneIndex_);
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i256_generic, EmuSIMD::i8x32, EmuSIMD::i16x16, EmuSIMD::i32x8, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::cast_i64x4_f64x4(std::forward<In_>(in_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i512_generic, EmuSIMD::i8x64, EmuSIMD::i16x32, EmuSIMD::i32x16, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::cast_i64x4_f64x4(_mm512_extracti64x4_epi64(std::forward<In_>(in_), LaneIndex_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a f64x4 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::f64x8 _extract_lane_f64x8_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::cast_f32x16_f64x8(_mm512_extractf32x8_ps(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::f64x8(std::forward<In_>(in_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i512_generic, EmuSIMD::i8x64, EmuSIMD::i16x32, EmuSIMD::i32x16, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::cast_i64x8_f64x8(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a f64x8 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i8x16 _extract_lane_i8x16_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x4>)
		{
			return EmuSIMD::Funcs::cast_f32x4_i8x16(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::cast_f32x4_i8x16(_mm256_extractf128_ps(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::cast_f32x4_i8x16(_mm512_extractf32x4_ps(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x2>)
		{
			return EmuSIMD::Funcs::cast_f64x2_i8x16(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::cast_f64x2_i8x16(_mm256_extractf128_pd(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::cast_f64x2_i8x16(_mm512_extractf64x2_pd(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i128_generic, EmuSIMD::i8x16, EmuSIMD::i16x8, EmuSIMD::i32x4, EmuSIMD::i64x2>)
		{
			return EmuSIMD::i8x16(std::forward<In_>(in_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i256_generic, EmuSIMD::i8x32, EmuSIMD::i16x16, EmuSIMD::i32x8, EmuSIMD::i64x4>)
		{
			return _mm256_extracti128_si256(std::forward<In_>(in_), LaneIndex_);
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i512_generic, EmuSIMD::i8x64, EmuSIMD::i16x32, EmuSIMD::i32x16, EmuSIMD::i64x8>)
		{
			return _mm512_extracti32x4_epi32(std::forward<In_>(in_), LaneIndex_);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i8x16 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i8x32 _extract_lane_i8x32_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::cast_f32x8_i8x32(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::cast_f32x8_i8x32(_mm512_extractf32x8_ps(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::cast_f64x4_i8x32(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::cast_f64x4_i8x32(_mm512_extractf64x4_pd(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i256_generic, EmuSIMD::i8x32, EmuSIMD::i16x16, EmuSIMD::i32x8, EmuSIMD::i64x4>)
		{
			return EmuSIMD::i8x32(std::forward<In_>(in_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i512_generic, EmuSIMD::i8x64, EmuSIMD::i16x32, EmuSIMD::i32x16, EmuSIMD::i64x8>)
		{
			return _mm512_extracti32x8_epi32(std::forward<In_>(in_), LaneIndex_);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i8x32 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i8x64 _extract_lane_i8x64_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::cast_f32x16_i8x64(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::cast_f64x8_i8x64(std::forward<In_>(in_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i512_generic, EmuSIMD::i8x64, EmuSIMD::i16x32, EmuSIMD::i32x16, EmuSIMD::i64x8>)
		{
			return EmuSIMD::i8x64(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i8x64 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i8x16 _extract_lane_i16x8_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x4>)
		{
			return EmuSIMD::Funcs::cast_f32x4_i16x8(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::cast_f32x4_i16x8(_mm256_extractf128_ps(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::cast_f32x4_i16x8(_mm512_extractf32x4_ps(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x2>)
		{
			return EmuSIMD::Funcs::cast_f64x2_i16x8(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::cast_f64x2_i16x8(_mm256_extractf128_pd(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::cast_f64x2_i16x8(_mm512_extractf64x2_pd(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i128_generic, EmuSIMD::i8x16, EmuSIMD::i16x8, EmuSIMD::i32x4, EmuSIMD::i64x2>)
		{
			return EmuSIMD::i8x16(std::forward<In_>(in_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i256_generic, EmuSIMD::i8x32, EmuSIMD::i16x16, EmuSIMD::i32x8, EmuSIMD::i64x4>)
		{
			return _mm256_extracti128_si256(std::forward<In_>(in_), LaneIndex_);
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i512_generic, EmuSIMD::i8x64, EmuSIMD::i16x32, EmuSIMD::i32x16, EmuSIMD::i64x8>)
		{
			return _mm512_extracti32x4_epi32(std::forward<In_>(in_), LaneIndex_);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i16x8 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i16x16 _extract_lane_i16x16_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::cast_f32x8_i16x16(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::cast_f32x8_i16x16(_mm512_extractf32x8_ps(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::cast_f64x4_i16x16(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::cast_f64x4_i16x16(_mm512_extractf64x4_pd(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i256_generic, EmuSIMD::i8x32, EmuSIMD::i16x16, EmuSIMD::i32x8, EmuSIMD::i64x4>)
		{
			return EmuSIMD::i16x16(std::forward<In_>(in_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i512_generic, EmuSIMD::i8x64, EmuSIMD::i16x32, EmuSIMD::i32x16, EmuSIMD::i64x8>)
		{
			return _mm512_extracti32x8_epi32(std::forward<In_>(in_), LaneIndex_);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i16x16 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i16x32 _extract_lane_i16x32_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::cast_f32x16_i16x32(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::cast_f64x8_i16x32(std::forward<In_>(in_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i512_generic, EmuSIMD::i8x64, EmuSIMD::i16x32, EmuSIMD::i32x16, EmuSIMD::i64x8>)
		{
			return EmuSIMD::i16x32(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i16x32 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i32x4 _extract_lane_i32x4_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x4>)
		{
			return EmuSIMD::Funcs::cast_f32x4_i32x4(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::cast_f32x4_i32x4(_mm256_extractf128_ps(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::cast_f32x4_i32x4(_mm512_extractf32x4_ps(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x2>)
		{
			return EmuSIMD::Funcs::cast_f64x2_i32x4(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::cast_f64x2_i32x4(_mm256_extractf128_pd(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::cast_f64x2_i32x4(_mm512_extractf64x2_pd(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i128_generic, EmuSIMD::i8x16, EmuSIMD::i16x8, EmuSIMD::i32x4, EmuSIMD::i64x2>)
		{
			return EmuSIMD::i32x4(std::forward<In_>(in_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i256_generic, EmuSIMD::i8x32, EmuSIMD::i16x16, EmuSIMD::i32x8, EmuSIMD::i64x4>)
		{
			return _mm256_extracti128_si256(std::forward<In_>(in_), LaneIndex_);
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i512_generic, EmuSIMD::i8x64, EmuSIMD::i16x32, EmuSIMD::i32x16, EmuSIMD::i64x8>)
		{
			return _mm512_extracti32x4_epi32(std::forward<In_>(in_), LaneIndex_);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i32x4 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i32x8 _extract_lane_i32x8_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::cast_f32x8_i32x8(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::cast_f32x8_i32x8(_mm512_extractf32x8_ps(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::cast_f64x4_i32x8(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::cast_f64x4_i32x8(_mm512_extractf64x4_pd(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i256_generic, EmuSIMD::i8x32, EmuSIMD::i16x16, EmuSIMD::i32x8, EmuSIMD::i64x4>)
		{
			return EmuSIMD::i32x8(std::forward<In_>(in_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i512_generic, EmuSIMD::i8x64, EmuSIMD::i16x32, EmuSIMD::i32x16, EmuSIMD::i64x8>)
		{
			return _mm512_extracti32x8_epi32(std::forward<In_>(in_), LaneIndex_);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i32x8 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i32x16 _extract_lane_i32x16_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::cast_f32x16_i32x16(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::cast_f64x8_i32x16(std::forward<In_>(in_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i512_generic, EmuSIMD::i8x64, EmuSIMD::i16x32, EmuSIMD::i32x16, EmuSIMD::i64x8>)
		{
			return EmuSIMD::i32x16(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i32x16 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i64x2 _extract_lane_i64x2_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x4>)
		{
			return EmuSIMD::Funcs::cast_f32x4_i64x2(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::cast_f32x4_i64x2(_mm256_extractf128_ps(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::cast_f32x4_i64x2(_mm512_extractf32x4_ps(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x2>)
		{
			return EmuSIMD::Funcs::cast_f64x2_i64x2(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::cast_f64x2_i64x2(_mm256_extractf128_pd(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::cast_f64x2_i64x2(_mm512_extractf64x2_pd(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i128_generic, EmuSIMD::i8x16, EmuSIMD::i16x8, EmuSIMD::i32x4, EmuSIMD::i64x2>)
		{
			return EmuSIMD::i64x2(std::forward<In_>(in_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i256_generic, EmuSIMD::i8x32, EmuSIMD::i16x16, EmuSIMD::i32x8, EmuSIMD::i64x4>)
		{
			return _mm256_extracti128_si256(std::forward<In_>(in_), LaneIndex_);
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i512_generic, EmuSIMD::i8x64, EmuSIMD::i16x32, EmuSIMD::i32x16, EmuSIMD::i64x8>)
		{
			return _mm512_extracti64x2_epi64(std::forward<In_>(in_), LaneIndex_);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i64x2 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i64x4 _extract_lane_i64x4_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::cast_f32x8_i64x4(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::cast_f32x8_i64x4(_mm512_extractf32x8_ps(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::cast_f64x4_i64x4(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::cast_f64x4_i64x4(_mm512_extractf64x4_pd(std::forward<In_>(in_), LaneIndex_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i256_generic, EmuSIMD::i8x32, EmuSIMD::i16x16, EmuSIMD::i32x8, EmuSIMD::i64x4>)
		{
			return EmuSIMD::i64x4(std::forward<In_>(in_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i512_generic, EmuSIMD::i8x64, EmuSIMD::i16x32, EmuSIMD::i32x16, EmuSIMD::i64x8>)
		{
			return _mm512_extracti64x4_epi64(std::forward<In_>(in_), LaneIndex_);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i64x4 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i64x8 _extract_lane_i64x8_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::cast_f32x16_i64x8(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::cast_f64x8_i64x8(std::forward<In_>(in_));
		}
		else if constexpr (EmuCore::TMP::is_any_same_v<in_uq, EmuSIMD::i512_generic, EmuSIMD::i8x64, EmuSIMD::i16x32, EmuSIMD::i32x16, EmuSIMD::i64x8>)
		{
			return EmuSIMD::i64x8(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i64x8 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}
}

#endif
