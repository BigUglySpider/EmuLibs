#ifndef EMU_MATH_COLOUR_HELPERS_H_INC_
#define EMU_MATH_COLOUR_HELPERS_H_INC_ 1

#include "ColourTMP.h"
#include "../../../EmuCore/Functors/Arithmetic.h"
#include "../../../EmuCore/Functors/MiscMath.h"
#include <type_traits>

namespace EmuMath::Helpers
{
	template<typename ChannelType_>
	[[nodiscard]] constexpr inline ChannelType_ max_channel_intensity_force_fp()
	{
		return ChannelType_(1);
	}
	template<typename ChannelType_>
	[[nodiscard]] constexpr inline ChannelType_ max_channel_intensity_force_int()
	{
		return std::numeric_limits<ChannelType_>::max();
	}

	template<typename ChannelType_>
	[[nodiscard]] constexpr inline ChannelType_ min_channel_intensity()
	{
		return ChannelType_(0);
	}

	template<typename ChannelType_>
	[[nodiscard]] constexpr inline ChannelType_ max_channel_intensity()
	{
		if constexpr (std::is_floating_point_v<ChannelType_>)
		{
			return max_channel_intensity_force_fp<ChannelType_>();
		}
		else
		{
			return max_channel_intensity_force_int<ChannelType_>();
		}
	}

	template<typename OutChannel_, typename InChannelInt_>
	[[nodiscard]] constexpr inline OutChannel_ wrap_colour_channel_int(InChannelInt_ to_wrap_int_)
	{
		using calc_type = typename EmuCore::TMPHelpers::first_floating_point<OutChannel_, double>::type;
		constexpr OutChannel_ min_out = min_channel_intensity<OutChannel_>();
		constexpr OutChannel_ max_out = max_channel_intensity<OutChannel_>();
		constexpr InChannelInt_ max_in = max_channel_intensity_force_int<InChannelInt_>();
		constexpr calc_type max_in_reciprocal = calc_type(1) / static_cast<calc_type>(max_in);

		// No need for negative checks when the integer is unsigned; free branch dodge
		if constexpr (std::is_signed_v<InChannelInt_>)
		{
			if (to_wrap_int_ < 0)
			{
				if (to_wrap_int_ == std::numeric_limits<InChannelInt_>::min())
				{
					// signed_min == (-signed_max) - 1; therefore, signed_min starts a wrap over again.
					return max_out;
				}
				else
				{
					// Create positive form of the wrapped number
					to_wrap_int_ = max_in + to_wrap_int_;
				}
			}
		}

		calc_type ratio_ = static_cast<calc_type>(to_wrap_int_) * max_in_reciprocal;
		if constexpr (std::is_floating_point_v<OutChannel_>)
		{
			// Since we're outputting a floating point, we just need a simple cast of the ratio.
			return static_cast<OutChannel_>(ratio_);
		}
		else
		{
			// If output is integral, we need to multiply the maximum output by the input's ratio to produce a similar channel.
			return static_cast<OutChannel_>(static_cast<calc_type>(max_out) * ratio_);
		}
	}

	template<typename OutRatio_, typename InChannel_>
	[[nodiscard]] constexpr inline OutRatio_ colour_channel_ratio(InChannel_ in_)
	{
		static_assert(std::is_floating_point_v<OutRatio_>, "Provided a non-floating-point OutRatio_ type to colour_channel_ratio. The output ratio must be a floating-point.");

		if constexpr (std::is_floating_point_v<InChannel_>)
		{
			return static_cast<OutRatio_>(in_);
		}
		else
		{
			constexpr OutRatio_ max_reciprocal_ = OutRatio_(1) / max_channel_intensity<InChannel_>();
			return static_cast<OutRatio_>(in_) * max_reciprocal_;
		}
	}

	template<typename OutChannel_, typename InChannel_>
	[[nodiscard]] constexpr inline OutChannel_ get_colour_intensity_from_other_ratio(InChannel_ to_convert_)
	{
		using calc_type = typename EmuCore::TMPHelpers::first_floating_point<OutChannel_, InChannel_, double>::type;
		constexpr calc_type max_out_calc = static_cast<calc_type>(max_channel_intensity<OutChannel_>());

		if constexpr (std::is_floating_point_v<InChannel_>)
		{
			if constexpr (std::is_floating_point_v<OutChannel_>)
			{
				return static_cast<OutChannel_>(to_convert_);
			}
			else
			{
				constexpr calc_type min_ratio_ = std::is_unsigned_v<OutChannel_> ? calc_type(0) : calc_type(-1);
				constexpr calc_type max_ratio_ = calc_type(1);
				constexpr EmuCore::do_clamp<calc_type, calc_type, calc_type> clamp_(min_ratio_, max_ratio_);
				calc_type ratio_ = clamp_(static_cast<calc_type>(to_convert_));
				return static_cast<OutChannel_>(max_out_calc * ratio_);
			}
		}
		else
		{
			constexpr calc_type max_in_calc_reciprocal = calc_type(1) / static_cast<calc_type>(max_channel_intensity_force_int<InChannel_>());
			calc_type ratio_ = to_convert_ * max_in_calc_reciprocal;
			if constexpr (std::is_floating_point_v<OutChannel_>)
			{
				return static_cast<OutChannel_>(ratio_);
			}
			else
			{
				constexpr calc_type min_ratio_ = std::is_unsigned_v<OutChannel_> ? calc_type(0) : calc_type(-1);
				constexpr calc_type max_ratio_ = calc_type(1);
				constexpr EmuCore::do_clamp<calc_type, calc_type, calc_type> clamp_(min_ratio_, max_ratio_);
				ratio_ = clamp_(ratio_);
				return static_cast<OutChannel_>(max_out_calc * ratio_);
			}
		}
	}

	template<typename OutChannel_, typename InChannel_>
	[[nodiscard]] constexpr inline OutChannel_ convert_colour_channel(InChannel_ to_convert_)
	{
		if constexpr (std::is_same_v<OutChannel_, InChannel_>)
		{
			// Same type so just return the input
			return to_convert_;
		}
		else if constexpr (std::is_floating_point_v<OutChannel_> && std::is_floating_point_v<InChannel_>)
		{
			// No need for more than a cast since all floats reside in the same 0:1 range as far as min:max intensity goes.
			return static_cast<OutChannel_>(to_convert_);
		}
		else
		{
			return get_colour_intensity_from_other_ratio<OutChannel_, InChannel_>(to_convert_);
		}
	}

	template<typename OutChannel_, typename InChannelFP_>
	[[nodiscard]] constexpr inline OutChannel_ wrap_colour_channel_fp(InChannelFP_ to_wrap_fp_)
	{
		constexpr OutChannel_ min_out = min_channel_intensity<OutChannel_>();
		constexpr OutChannel_ max_out = max_channel_intensity<OutChannel_>();
		constexpr InChannelFP_ in_zero = InChannelFP_(0);

		if constexpr (std::is_floating_point_v<InChannelFP_>)
		{
			constexpr InChannelFP_ max_in = max_channel_intensity_force_fp<InChannelFP_>();

			if (to_wrap_fp_ == in_zero)
			{
				return min_out;
			}
			else
			{
				// Convert to positive form if needed
				if (to_wrap_fp_ < in_zero)
				{
					InChannelFP_ negated_floor_ = -(EmuCore::do_floor_constexpr<InChannelFP_>()(to_wrap_fp_));
					to_wrap_fp_ = negated_floor_ + to_wrap_fp_;
				}

				// Wrap in the inclusive range 0:1. zero values will be integers, of which all non-zeroes represent maximum intensity.
				to_wrap_fp_ = EmuCore::do_mod<InChannelFP_, InChannelFP_>()(to_wrap_fp_, InChannelFP_(1));
				if (to_wrap_fp_ == in_zero)
				{
					return max_out;
				}

				// Only reach this point if the passed FP_ is neither min nor max after initial wrap
				if constexpr (std::is_floating_point_v<OutChannel_>)
				{
					// Only need to cast if we're outputting a floating point, since it's already wrapped to valid FP range.
					return static_cast<OutChannel_>(to_wrap_fp_);
				}
				else
				{
					// Convert to output channel type using the wrapped range 0:1 as a ratio applied to the maximum intensity.
					return static_cast<OutChannel_>(static_cast<InChannelFP_>(max_out) * to_wrap_fp_);
				}
			}
		}
		else
		{
			if (to_wrap_fp_ == in_zero)
			{
				return min_out;
			}
			else
			{
				return max_out;
			}
		}
	}

	template<typename OutChannel_, typename InChannel_>
	[[nodiscard]] constexpr inline OutChannel_ wrap_colour_channel(const InChannel_& in_)
	{
		if constexpr (std::is_floating_point_v<InChannel_>)
		{
			return wrap_colour_channel_fp<OutChannel_, InChannel_>(in_);
		}
		else
		{
			return wrap_colour_channel_int<OutChannel_, InChannel_>(in_);
		}
	}

	template<typename OutChannel_, typename InChannel_>
	[[nodiscard]] constexpr inline OutChannel_ clamp_colour_channel(InChannel_ to_clamp_)
	{
		constexpr InChannel_ min_in = min_channel_intensity<InChannel_>();
		constexpr InChannel_ max_in = max_channel_intensity<InChannel_>();
		constexpr OutChannel_ max_out = max_channel_intensity<OutChannel_>();

		if (to_clamp_ <= min_in)
		{
			to_clamp_ = min_in;
		}
		else if (to_clamp_ >= max_in)
		{
			to_clamp_ = max_in;
		}


		if constexpr (std::is_same_v<InChannel_, OutChannel_>)
		{
			return to_clamp_;
		}
		if constexpr (std::is_floating_point_v<InChannel_>)
		{
			if constexpr (std::is_floating_point_v<OutChannel_>)
			{
				return static_cast<OutChannel_>(to_clamp_);
			}
			else
			{
				return static_cast<OutChannel_>(to_clamp_ * static_cast<InChannel_>(max_out));
			}
		}
		else
		{
			using calc_type = typename EmuCore::TMPHelpers::first_floating_point<OutChannel_, double>::type;
			constexpr calc_type max_in_reciprocal_ = calc_type(1) / static_cast<calc_type>(max_in);
			calc_type ratio_ = static_cast<calc_type>(to_clamp_) * max_in_reciprocal_;
			if constexpr (std::is_floating_point_v<OutChannel_>)
			{
				return static_cast<OutChannel_>(ratio_);
			}
			else
			{
				return static_cast<OutChannel_>(ratio_ * static_cast<calc_type>(max_out));
			}
		}
	}

	template<typename OutChannel_, typename InChannel_>
	[[nodiscard]] constexpr inline OutChannel_ colour_channel_invert(InChannel_ in_)
	{
		constexpr InChannel_ max_in = max_channel_intensity<InChannel_>();
		if constexpr (std::is_same_v<OutChannel_, InChannel_>)
		{
			return max_in - in_;
		}
		else if constexpr(std::is_floating_point_v<OutChannel_> && std::is_floating_point_v<InChannel_>)
		{
			return static_cast<OutChannel_>(max_in - in_);
		}
		else
		{
			return get_colour_intensity_from_other_ratio<OutChannel_, InChannel_>(max_in - in_);
		}
	}

	template<bool IncludeAlpha_ = false, class InColour_>
	[[nodiscard]] constexpr inline InColour_ colour_invert(const InColour_& in_)
	{
		if constexpr (EmuMath::TMP::is_emu_colour_v<InColour_>)
		{
			using channel_type = typename InColour_::value_type;
			if constexpr (!InColour_::contains_alpha)
			{
				return InColour_
				(
					colour_channel_invert<channel_type, channel_type>(in_.R()),
					colour_channel_invert<channel_type, channel_type>(in_.G()),
					colour_channel_invert<channel_type, channel_type>(in_.B())
				);
			}
			else
			{
				if constexpr (IncludeAlpha_)
				{
					return InColour_
					(
						colour_channel_invert<channel_type, channel_type>(in_.R()),
						colour_channel_invert<channel_type, channel_type>(in_.G()),
						colour_channel_invert<channel_type, channel_type>(in_.B()),
						colour_channel_invert<channel_type, channel_type>(in_.A())
					);
				}
				else
				{
					return InColour_
					(
						colour_channel_invert<channel_type, channel_type>(in_.R()),
						colour_channel_invert<channel_type, channel_type>(in_.G()),
						colour_channel_invert<channel_type, channel_type>(in_.B()),
						in_.A()
					);
				}
			}
		}
		else
		{
			static_assert(false, "Attempted to invert a colour, but provided a non-EmuMath-Colour in_ type.");
		}
	}
	template<bool IncludeAlpha_ = false, class InOutColour_>
	constexpr inline InOutColour_& colour_invert(const InOutColour_& in_, InOutColour_& out_)
	{
		if constexpr (EmuMath::TMP::is_emu_colour_v<InOutColour_>)
		{
			using channel_type = typename InOutColour_::value_type;
			if constexpr (!InOutColour_::contains_alpha)
			{
				out_.R(colour_channel_invert<channel_type, channel_type>(in_.R()));
				out_.G(colour_channel_invert<channel_type, channel_type>(in_.G()));
				out_.B(colour_channel_invert<channel_type, channel_type>(in_.B()));
			}
			else
			{
				if constexpr (IncludeAlpha_)
				{
					out_.R(colour_channel_invert<channel_type, channel_type>(in_.R()));
					out_.G(colour_channel_invert<channel_type, channel_type>(in_.G()));
					out_.B(colour_channel_invert<channel_type, channel_type>(in_.B()));
					out_.A(colour_channel_invert<channel_type, channel_type>(in_.A()));
				}
				else
				{
					out_.R(colour_channel_invert<channel_type, channel_type>(in_.R()));
					out_.G(colour_channel_invert<channel_type, channel_type>(in_.G()));
					out_.B(colour_channel_invert<channel_type, channel_type>(in_.B()));
				}
			}
		}
		else
		{
			static_assert(false, "Attempted to invert a colour, but provided a non-EmuMath-Colour in_ type.");
		}
	}

	template<class OutColour_, class InColour_>
	[[nodiscard]] constexpr inline OutColour_ colour_wrap(const InColour_& in_)
	{
		if constexpr (EmuMath::TMP::is_emu_colour_v<InColour_>)
		{
			if constexpr (EmuMath::TMP::is_emu_colour_v<OutColour_>)
			{
				using in_channel_type = typename InColour_::value_type;
				using out_channel_type = typename OutColour_::value_type;
				if constexpr (OutColour_::contains_alpha)
				{
					if constexpr (InColour_::contains_alpha)
					{
						return OutColour_
						(
							wrap_colour_channel<out_channel_type, in_channel_type>(in_.R()),
							wrap_colour_channel<out_channel_type, in_channel_type>(in_.G()),
							wrap_colour_channel<out_channel_type, in_channel_type>(in_.B()),
							wrap_colour_channel<out_channel_type, in_channel_type>(in_.A())
						);
					}
					else
					{
						return OutColour_
						(
							wrap_colour_channel<out_channel_type, in_channel_type>(in_.R()),
							wrap_colour_channel<out_channel_type, in_channel_type>(in_.G()),
							wrap_colour_channel<out_channel_type, in_channel_type>(in_.B()),
							OutColour_::max_intensity
						);
					}
				}
				else
				{
					return OutColour_
					(
						wrap_colour_channel<out_channel_type, in_channel_type>(in_.R()),
						wrap_colour_channel<out_channel_type, in_channel_type>(in_.G()),
						wrap_colour_channel<out_channel_type, in_channel_type>(in_.B())
					);
				}
			}
			else
			{
				static_assert(false, "Attempted to wrap an EmuMath Colour, but the provided OutColour_ type was not an EmuMath colour.");
			}
		}
		else
		{
			static_assert(false, "Attempted to wrap an EmuMath Colour, but the provided in_ colour was not an EmuMath colour.");
		}
	}
	template<class OutColour_, class InColour_>
	constexpr inline OutColour_& colour_wrap(const InColour_& in_, OutColour_& out_)
	{
		if constexpr (EmuMath::TMP::is_emu_colour_v<InColour_>)
		{
			if constexpr (EmuMath::TMP::is_emu_colour_v<OutColour_>)
			{
				using in_channel_type = typename InColour_::value_type;
				using out_channel_type = typename OutColour_::value_type;
				if constexpr (OutColour_::contains_alpha)
				{
					if constexpr (InColour_::contains_alpha)
					{
						out_.R(wrap_colour_channel<out_channel_type, in_channel_type>(in_.R()));
						out_.G(wrap_colour_channel<out_channel_type, in_channel_type>(in_.G()));
						out_.B(wrap_colour_channel<out_channel_type, in_channel_type>(in_.B()));
						out_.A(wrap_colour_channel<out_channel_type, in_channel_type>(in_.A()));
					}
					else
					{
						out_.R(wrap_colour_channel<out_channel_type, in_channel_type>(in_.R()));
						out_.G(wrap_colour_channel<out_channel_type, in_channel_type>(in_.G()));
						out_.B(wrap_colour_channel<out_channel_type, in_channel_type>(in_.B()));
						out_.A(OutColour_::max_intensity);
					}
				}
				else
				{
					out_.R(wrap_colour_channel<out_channel_type, in_channel_type>(in_.R()));
					out_.G(wrap_colour_channel<out_channel_type, in_channel_type>(in_.G()));
					out_.B(wrap_colour_channel<out_channel_type, in_channel_type>(in_.B()));
				}
				return out_;
			}
			else
			{
				static_assert(false, "Attempted to wrap an EmuMath Colour, but the provided OutColour_ type was not an EmuMath colour.");
			}
		}
		else
		{
			static_assert(false, "Attempted to wrap an EmuMath Colour, but the provided in_ colour was not an EmuMath colour.");
		}
	}

	template<class OutColour_, class InColour_>
	[[nodiscard]] constexpr inline OutColour_ colour_clamp(const InColour_& in_)
	{
		if constexpr (EmuMath::TMP::is_emu_colour_v<InColour_>)
		{
			if constexpr (EmuMath::TMP::is_emu_colour_v<OutColour_>)
			{
				using in_channel_type = typename InColour_::value_type;
				using out_channel_type = typename OutColour_::value_type;
				if constexpr (OutColour_::contains_alpha)
				{
					if constexpr (InColour_::contains_alpha)
					{
						return OutColour_
						(
							clamp_colour_channel<out_channel_type, in_channel_type>(in_.R()),
							clamp_colour_channel<out_channel_type, in_channel_type>(in_.G()),
							clamp_colour_channel<out_channel_type, in_channel_type>(in_.B()),
							clamp_colour_channel<out_channel_type, in_channel_type>(in_.A())
						);
					}
					else
					{
						return OutColour_
						(
							clamp_colour_channel<out_channel_type, in_channel_type>(in_.R()),
							clamp_colour_channel<out_channel_type, in_channel_type>(in_.G()),
							clamp_colour_channel<out_channel_type, in_channel_type>(in_.B()),
							OutColour_::max_intensity
						);
					}
				}
				else
				{
					return OutColour_
					(
						clamp_colour_channel<out_channel_type, in_channel_type>(in_.R()),
						clamp_colour_channel<out_channel_type, in_channel_type>(in_.G()),
						clamp_colour_channel<out_channel_type, in_channel_type>(in_.B())
					);
				}
			}
			else
			{
				static_assert(false, "Attempted to clamp an EmuMath Colour, but the provided OutColour_ type was not an EmuMath colour.");
			}
		}
		else
		{
			static_assert(false, "Attempted to clamp an EmuMath Colour, but the provided in_ colour was not an EmuMath colour.");
		}
	}
	template<class OutColour_, class InColour_>
	constexpr inline OutColour_& colour_clamp(const InColour_& in_, OutColour_& out_)
	{
		if constexpr (EmuMath::TMP::is_emu_colour_v<InColour_>)
		{
			if constexpr (EmuMath::TMP::is_emu_colour_v<OutColour_>)
			{
				using in_channel_type = typename InColour_::value_type;
				using out_channel_type = typename OutColour_::value_type;
				if constexpr (OutColour_::contains_alpha)
				{
					if constexpr (InColour_::contains_alpha)
					{
						out_.R(clamp_colour_channel<out_channel_type, in_channel_type>(in_.R()));
						out_.G(clamp_colour_channel<out_channel_type, in_channel_type>(in_.G()));
						out_.B(clamp_colour_channel<out_channel_type, in_channel_type>(in_.B()));
						out_.A(clamp_colour_channel<out_channel_type, in_channel_type>(in_.A()));
					}
					else
					{
						out_.R(clamp_colour_channel<out_channel_type, in_channel_type>(in_.R()));
						out_.G(clamp_colour_channel<out_channel_type, in_channel_type>(in_.G()));
						out_.B(clamp_colour_channel<out_channel_type, in_channel_type>(in_.B()));
						out_.A(OutColour_::max_intensity);
					}
				}
				else
				{
					out_.R(clamp_colour_channel<out_channel_type, in_channel_type>(in_.R()));
					out_.G(clamp_colour_channel<out_channel_type, in_channel_type>(in_.G()));
					out_.B(clamp_colour_channel<out_channel_type, in_channel_type>(in_.B()));
				}
				return out_;
			}
			else
			{
				static_assert(false, "Attempted to clamp an EmuMath Colour, but the provided OutColour_ type was not an EmuMath colour.");
			}
		}
		else
		{
			static_assert(false, "Attempted to clamp an EmuMath Colour, but the provided in_ colour was not an EmuMath colour.");
		}
	}

	//template<typename lhs_channel_type, typename rhs_channel_type>
	//[[nodiscard]] constexpr inline bool colour_cmp_equal(const EmuMath::ColourRGB<lhs_channel_type>& lhs_, const EmuMath::ColourRGB<rhs_channel_type>& rhs_)
	//{
	//	if constexpr (std::is_same_v<lhs_channel_type, rhs_channel_type>)
	//	{
	//		return lhs_.channels.CmpAllEqualTo(rhs_.channels);
	//	}
	//	else if constexpr (std::is_floating_point_v<lhs_channel_type> && std::is_floating_point_v<rhs_channel_type>)
	//	{
	//		return lhs_.channels.CmpAllEqualTo(rhs_.channels);
	//	}
	//	else if constexpr (std::is_floating_point_v<rhs_channel_type>)
	//	{
	//		return colour_cmp_equal(EmuMath::ColourRGB<rhs_channel_type>(lhs_), rhs_);
	//	}
	//	else
	//	{
	//		return colour_cmp_equal(lhs_, EmuMath::ColourRGB<lhs_channel_type>(rhs_));
	//	}
	//}
	//
	//template<typename lhs_contained_type, typename rhs_type>
	//[[nodiscard]] constexpr inline EmuMath::ColourRGB<lhs_contained_type> colour_multiply(const EmuMath::ColourRGB<lhs_contained_type>& lhs_, const rhs_type& rhs_)
	//{
	//	if constexpr (EmuMath::TMP::is_emu_colour_v<rhs_type>)
	//	{
	//		using rhs_contained_type = typename rhs_type::value_type;
	//		using ratio_type = typename EmuCore::TMPHelpers::first_floating_point<lhs_contained_type, rhs_contained_type, float>::type;
	//		return colour_multiply<lhs_contained_type, EmuMath::Vector<3, ratio_type>>
	//		(
	//			lhs_,
	//			EmuMath::Vector<3, ratio_type>
	//			(
	//				colour_channel_ratio<ratio_type, rhs_contained_type>(rhs_.R()),
	//				colour_channel_ratio<ratio_type, rhs_contained_type>(rhs_.G()),
	//				colour_channel_ratio<ratio_type, rhs_contained_type>(rhs_.B())
	//			)
	//		);
	//	}
	//	else
	//	{
	//		return EmuMath::ColourRGB<lhs_contained_type>(lhs_.channels.Multiply(rhs_));
	//	}
	//}
	//
	//template<typename lhs_contained_type, typename rhs_type>
	//[[nodiscard]] constexpr inline EmuMath::ColourRGB<lhs_contained_type> colour_divide(const EmuMath::ColourRGB<lhs_contained_type>& lhs_, const rhs_type& rhs_)
	//{
	//	if constexpr (EmuMath::TMP::is_emu_colour_v<rhs_type>)
	//	{
	//		using rhs_contained_type = typename rhs_type::value_type;
	//		using ratio_type = typename EmuCore::TMPHelpers::first_floating_point<lhs_contained_type, rhs_contained_type, float>::type;
	//		constexpr ratio_type zero_ = ratio_type(0);
	//		constexpr ratio_type one_ = ratio_type(1);
	//		return colour_multiply<lhs_contained_type, EmuMath::Vector<3, ratio_type>>
	//		(
	//			lhs_,
	//			EmuMath::Vector<3, ratio_type>
	//			(
	//				rhs_.R() == zero_ ? one_ : (one_ / colour_channel_ratio<ratio_type, rhs_contained_type>(rhs_.R())),
	//				rhs_.G() == zero_ ? one_ : (one_ / colour_channel_ratio<ratio_type, rhs_contained_type>(rhs_.G())),
	//				rhs_.B() == zero_ ? one_ : (one_ / colour_channel_ratio<ratio_type, rhs_contained_type>(rhs_.B()))
	//			)
	//		);
	//	}
	//	else
	//	{
	//		return EmuMath::ColourRGB<lhs_contained_type>(lhs_.channels.Divide(rhs_));
	//	}
	//}
}

#endif
