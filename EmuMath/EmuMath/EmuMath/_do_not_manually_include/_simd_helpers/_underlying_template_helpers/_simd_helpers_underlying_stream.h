#ifndef EMU_MATH_SIMD_TEMPLATE_HELPERS_UNDERLYING_STREAM_H_INC_
#define EMU_MATH_SIMD_TEMPLATE_HELPERS_UNDERLYING_STREAM_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "_simd_helpers_underlying_get.h"

namespace EmuMath::SIMD::_underlying_simd_helpers
{
	template<bool IsWide_, std::size_t OutputIntWidth_, bool OutputIntSigned_, class Stream_, class Register_>
	inline Stream_& _append_to_stream_int(Stream_& str_, Register_ register_)
	{
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<Register_>)
		{
			if constexpr (EmuMath::SIMD::TMP::_assert_valid_simd_int_element_width<OutputIntWidth_>())
			{
				using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
				if constexpr (EmuMath::SIMD::TMP::is_integral_simd_register_v<register_type_uq>)
				{
					if constexpr (IsWide_)
					{
						str_ << L"{ ";
					}
					else
					{
						str_ << "{ ";
					}

					using int_type = std::conditional_t
					<
						OutputIntSigned_,
						EmuCore::TMPHelpers::int_of_size_t<OutputIntWidth_ / 8>,
						EmuCore::TMPHelpers::uint_of_size_t<OutputIntWidth_ / 8>
					>;
					constexpr std::size_t num_elements_ = EmuMath::SIMD::TMP::simd_register_width_v<register_type_uq> / OutputIntWidth_;
					int_type data_[num_elements_] = {};
					_underlying_simd_helpers::_store_register(register_, data_);

					str_ << +data_[0];
					for (std::size_t i = 1; i < num_elements_; ++i)
					{
						str_ << ", " << +data_[i];
					}

					if constexpr (IsWide_)
					{
						str_ << L" }";
					}
					else

					{
						str_ << " }";
					}
					return str_;
				}
				else
				{
					static_assert(false, "Attempted to append an integral SIMD register to a stream via EmuMath SIMD helpers, but the provided register was not a supported integral register.");
				}
			}
			else
			{
				static_assert(false, "Attempted to append an integral SIMD register to a stream via EmuMath SIMD helpers, but the provided width to interpret elements of the register as was invalid.");
			}
		}
		else
		{
			static_assert(false, "Attempted to append an integral SIMD register to a stream via EmuMath SIMD helpers, but the provided register_ was not a supported SIMD register.");
		}
	}

	template<bool IsWide_, class Stream_, class Register_>
	inline Stream_& _append_to_stream_fp(Stream_& str_, Register_ register_)
	{
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<Register_>)
		{
			using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
			if constexpr (EmuMath::SIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				if constexpr (IsWide_)
				{
					str_ << L"{ ";
				}
				else
				{
					str_ << "{ ";
				}

				using fp_type = std::conditional_t
				<
					EmuCore::TMPHelpers::is_any_comparison_true<std::is_same, register_type_uq, __m128, __m256, __m512>::value,
					float,
					double
				>;
				constexpr std::size_t num_elements_ = EmuMath::SIMD::TMP::floating_point_register_element_count_v<register_type_uq>;
				fp_type data_[num_elements_] = {};
				_underlying_simd_helpers::_store_register(register_, data_);
				str_ << data_[0];
				for (std::size_t i = 1; i < num_elements_; ++i)
				{
					str_ << ", " << data_[i];
				}

				if constexpr (IsWide_)
				{
					str_ << L" }";
				}
				else

				{
					str_ << " }";
				}
				return str_;
			}
			else
			{
				static_assert(false, "Attempted to append a floating-point SIMD register to a stream via EmuMath SIMD helpers, but the provided register was not a supported floating-point register.");
			}
		}
		else
		{
			static_assert(false, "Attempted to append a floating-point SIMD register to a stream via EmuMath SIMD helpers, but the provided register_ was not a supported SIMD register.");
		}
	}


	template<bool IsWide_, std::size_t OutputWidthIfInt_ = 32, bool OutputSignedIfInt_ = true, class Stream_, class Register_>
	inline Stream_& _append_to_stream(Stream_& str_, Register_ register_)
	{
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<Register_>)
		{
			if constexpr (EmuMath::SIMD::TMP::is_floating_point_simd_register_v<Register_>)
			{
				return _append_to_stream_fp<IsWide_>(str_, register_);
			}
			else if constexpr (EmuMath::SIMD::TMP::is_integral_simd_register_v<Register_>)
			{
				return _append_to_stream_int<IsWide_, OutputWidthIfInt_, OutputSignedIfInt_>(str_, register_);
			}
			else
			{
				static_assert(false, "Attempted to append a SIMD register to a stream via EmuMath SIMD helpers, but it could not be determined whether the register contained floating-point or integral elements.");
			}
		}
		else
		{
			static_assert(false, "Attempted to append a SIMD register to a stream via EmuMath SIMD helpers, but the provided register_ was not a supported SIMD register.");
		}
	}
}

#endif
