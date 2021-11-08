#ifndef EMU_SIMD_HELPERS_UNDERLYING_GET_H_INC_
#define EMU_SIMD_HELPERS_UNDERLYING_GET_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "_simd_helpers_underlying_shuffle.h"

namespace EmuSIMD::_underlying_simd_helpers
{
	template<std::size_t Index_, typename OutT_, std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline OutT_ _get_register_index(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuCore::TMPHelpers::is_any_comparison_true<std::is_same, register_type_uq, __m128, __m256, __m512>::value)
			{
				if constexpr (std::is_convertible_v<float, OutT_>)
				{
					if constexpr (std::is_same_v<register_type_uq, __m128>)
					{
						if constexpr (Index_ <= 3)
						{
							if constexpr (Index_ != 0)
							{
								register_ = _execute_shuffle<Index_>(register_);
							}
							return _mm_cvtss_f32(register_);
						}
						else
						{
							static_assert(false, "Attempted to extract an index from a 128-bit float SIMD register using EmuSIMD helpers, but the provided Index_ was invalid. Valid indices: 0, 1, 2, 3.");
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, __m256>)
					{
						if constexpr (Index_ <= 7)
						{
							constexpr int is_hi_ = static_cast<int>(Index_ >= 4);
							constexpr std::size_t index_in_half_ = Index_ - (4 * is_hi_);
							return _get_register_index<index_in_half_, OutT_, PerElementWidthIfInt_>(_mm256_extractf128_ps(register_, is_hi_));
						}
						else
						{
							static_assert(false, "Attempted to extract an index from a 256-bit float SIMD register using EmuSIMD helpers, but the provided Index_ was invalid. Valid indices: 0, 1, 2, 3, 4, 5, 6, 7.");
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
							static_assert(false, "Attempted to extract an index from a 512-bit float SIMD register using EmuSIMD helpers, but the provided Index_ was invalid. Valid indices: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15.");
						}
					}
				}
				else
				{
					static_assert(false, "Attempted to extract an index from a float-containing SIMD register using EmuSIMD helpers, but the provided output type cannot be created from a float value.");
				}
			}
			else if constexpr (EmuCore::TMPHelpers::is_any_comparison_true<std::is_same, register_type_uq, __m128d, __m256d, __m512d>::value)
			{
				if constexpr (std::is_convertible_v<double, OutT_>)
				{
					if constexpr (std::is_same_v<register_type_uq, __m128d>)
					{
						if constexpr (Index_ <= 1)
						{
							if constexpr (Index_ != 0)
							{
								register_ = _execute_shuffle<Index_>(register_);
							}
							return static_cast<OutT_>(_mm_cvtsd_f64(register_));
						}
						else
						{
							static_assert(false, "Attempted to extract an index from a 128-bit double SIMD register using EmuSIMD helpers, but the provided Index_ was invalid. Valid indices: 0, 1.");
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, __m256d>)
					{
						if constexpr (Index_ <= 3)
						{
							constexpr int is_hi_ = static_cast<int>(Index_ >= 2);
							constexpr std::size_t index_128_ = Index_ - (2 * is_hi_);
							return _get_register_index<index_128_, OutT_, PerElementWidthIfInt_>(_mm256_extractf128_pd(register_, is_hi_));
						}
						else
						{
							static_assert(false, "Attempted to extract an index from a 256-bit double SIMD register using EmuSIMD helpers, but the provided Index_ was invalid. Valid indices: 0, 1, 2, 3.");
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
							static_assert(false, "Attempted to extract an index from a 512-bit double SIMD register using EmuSIMD helpers, but the provided Index_ was invalid. Valid indices: 0, 1, 2, 3, 4, 5, 6, 7.");
						}
					}
				}
				else
				{
					static_assert(false, "Attempted to extract an index from a double-containing SIMD register using EmuSIMD helpers, but the provided output type cannot be created from a double value.");
				}
			}
			else if constexpr (EmuCore::TMPHelpers::is_any_comparison_true<std::is_same, register_type_uq, __m128i, __m256i, __m512i>::value)
			{
				if constexpr(EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidthIfInt_>())
				{
					using int_type = EmuCore::TMPHelpers::int_of_size_t<PerElementWidthIfInt_ / 8>;
					if constexpr (std::is_convertible_v<int_type, OutT_>)
					{
						constexpr std::size_t chunk_divisor_ = std::size_t(128) / PerElementWidthIfInt_;
						if constexpr (std::is_same_v<register_type_uq, __m128i>)
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
								static_assert(false, "Attempted to extract an index from a 128-bit integral SIMD register using EmuSIMD helpers, but the provided index is invalid for the provided width. The valid index range is 0:(128 / PerElementWidthIfInt_)-1.");
							}
						}
						else if constexpr (std::is_same_v<register_type_uq, __m256i>)
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
								static_assert(false, "Attempted to extract an index from a 256-bit integral SIMD register using EmuSIMD helpers, but the provided index is invalid for the provided width. The valid index range is 0:(256 / PerElementWidthIfInt_)-1.");
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
								static_assert(false, "Attempted to extract an index from a 512-bit integral SIMD register using EmuSIMD helpers, but the provided index is invalid for the provided width. The valid index range is 0:(512 / PerElementWidthIfInt_)-1.");
							}
						}
					}
					else
					{
						static_assert(false, "Attempted to extract an index from an integral SIMD register using EmuSIMD helpers, but the provided output type cannot be created from an integer of the provided width.");
					}
				}
				else
				{
					static_assert(false, "Attempted to extract an index from an integral SIMD register using EmuSIMD helpers, but the provided bit width per element is invalid.");
				}
			}
			else
			{
				static_assert(false, "Attempted to extract an index from a SIMD register using EmuSIMD helpers, but the provided SIMD register is not supported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to extract an index from a SIMD register using EmuSIMD helpers, but the provided register is not a supported SIMD register type.");
		}
	}

	template<typename Out_, class Register_, typename NoConstReq_ = std::enable_if_t<!std::is_const_v<Out_>>>
	[[nodiscard]] inline void _store_register(Register_ register_, Out_* p_out_)
	{
		if constexpr (EmuSIMD::TMP::is_simd_register_v<Register_>)
		{
			using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				_mm_store_ps(reinterpret_cast<float*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				_mm_store_pd(reinterpret_cast<double*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				_mm256_store_ps(reinterpret_cast<float*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				_mm256_store_pd(reinterpret_cast<double*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				_mm512_store_ps(reinterpret_cast<void*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				_mm512_store_pd(reinterpret_cast<void*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128i>)
			{
				_mm_store_si128(reinterpret_cast<__m128i*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256i>)
			{
				_mm256_store_si256(reinterpret_cast<__m256i*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512i>)
			{
				_mm512_store_si512(reinterpret_cast<void*>(p_out_), register_);
			}
			else
			{
				static_assert(false, "Attempted to store a SIMD register to a pointer via an EmuSIMD helper, but the provided register_ could not be recognised.");
			}
		}
		else
		{
			static_assert(false, "Attempted to store a SIMD register to a pointer via an EmuSIMD helper, but the provided register_ was not a supported SIMD register.");
		}
	}
}

#endif
