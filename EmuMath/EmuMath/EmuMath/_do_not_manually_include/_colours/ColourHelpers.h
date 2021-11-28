#ifndef EMU_MATH_COLOUR_HELPERS_H_INC_
#define EMU_MATH_COLOUR_HELPERS_H_INC_ 1

#include "_helpers_underlying/_colour_helpers_underlying_common_includes.h"
#include "_helpers_underlying/_colour_helpers_underlying.h"

namespace EmuMath::Helpers
{
	template<typename ChannelType_>
	[[nodiscard]] constexpr inline ChannelType_ colour_colour_max_channel_intensity_force_fp()
	{
		return _underlying_colour_funcs::_colour_colour_max_channel_intensity_force_fp<ChannelType_>();
	}
	template<typename ChannelType_>
	[[nodiscard]] constexpr inline ChannelType_ colour_colour_max_channel_intensity_force_int()
	{
		return _underlying_colour_funcs::_colour_colour_max_channel_intensity_force_int<ChannelType_>();
	}

	template<typename ChannelType_>
	[[nodiscard]] constexpr inline ChannelType_ colour_min_channel_intensity()
	{
		return _underlying_colour_funcs::_colour_min_channel_intensity<ChannelType_>();
	}

	template<typename ChannelType_>
	[[nodiscard]] constexpr inline ChannelType_ colour_max_channel_intensity()
	{
		return _underlying_colour_funcs::_colour_max_channel_intensity<ChannelType_>();
	}

	template<typename OutChannel_, typename InChannelInt_>
	[[nodiscard]] constexpr inline OutChannel_ colour_wrap_channel_int(InChannelInt_ to_wrap_int_)
	{
		using calc_type = typename EmuCore::TMPHelpers::first_floating_point<OutChannel_, double>::type;
		constexpr OutChannel_ min_out = colour_min_channel_intensity<OutChannel_>();
		constexpr OutChannel_ max_out = colour_max_channel_intensity<OutChannel_>();
		constexpr InChannelInt_ max_in = colour_colour_max_channel_intensity_force_int<InChannelInt_>();
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
		return _underlying_colour_funcs::_colour_channel_ratio<OutRatio_, InChannel_>(in_);
	}

	template<typename OutChannel_, typename InChannel_>
	[[nodiscard]] constexpr inline OutChannel_ colour_get_intensity_from_other_ratio(InChannel_ to_convert_)
	{
		return _underlying_colour_funcs::_colour_get_intensity_from_other_ratio<OutChannel_, InChannel_>(to_convert_);
	}

	template<typename OutChannel_, typename InChannel_>
	[[nodiscard]] constexpr inline OutChannel_ colour_convert_channel(InChannel_ to_convert_)
	{
		return _underlying_colour_funcs::_colour_convert_channel<OutChannel_, InChannel_>(to_convert_);
	}

	template<typename OutChannel_, typename InChannelFP_>
	[[nodiscard]] constexpr inline OutChannel_ colour_wrap_channel_fp(InChannelFP_ to_wrap_fp_)
	{
		constexpr OutChannel_ min_out = colour_min_channel_intensity<OutChannel_>();
		constexpr OutChannel_ max_out = colour_max_channel_intensity<OutChannel_>();
		constexpr InChannelFP_ in_zero = InChannelFP_(0);

		if constexpr (std::is_floating_point_v<InChannelFP_>)
		{
			constexpr InChannelFP_ max_in = colour_colour_max_channel_intensity_force_fp<InChannelFP_>();

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
	[[nodiscard]] constexpr inline OutChannel_ colour_wrap_channel(const InChannel_& in_)
	{
		if constexpr (std::is_floating_point_v<InChannel_>)
		{
			return colour_wrap_channel_fp<OutChannel_, InChannel_>(in_);
		}
		else
		{
			return colour_wrap_channel_int<OutChannel_, InChannel_>(in_);
		}
	}

	template<typename OutChannel_, typename InChannel_>
	[[nodiscard]] constexpr inline OutChannel_ colour_clamp_channel(InChannel_ to_clamp_)
	{
		constexpr InChannel_ min_in = colour_min_channel_intensity<InChannel_>();
		constexpr InChannel_ max_in = colour_max_channel_intensity<InChannel_>();
		constexpr OutChannel_ max_out = colour_max_channel_intensity<OutChannel_>();

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
		constexpr InChannel_ max_in = colour_max_channel_intensity<InChannel_>();
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
			return colour_get_intensity_from_other_ratio<OutChannel_, InChannel_>(max_in - in_);
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
							colour_wrap_channel<out_channel_type, in_channel_type>(in_.R()),
							colour_wrap_channel<out_channel_type, in_channel_type>(in_.G()),
							colour_wrap_channel<out_channel_type, in_channel_type>(in_.B()),
							colour_wrap_channel<out_channel_type, in_channel_type>(in_.A())
						);
					}
					else
					{
						return OutColour_
						(
							colour_wrap_channel<out_channel_type, in_channel_type>(in_.R()),
							colour_wrap_channel<out_channel_type, in_channel_type>(in_.G()),
							colour_wrap_channel<out_channel_type, in_channel_type>(in_.B()),
							OutColour_::max_intensity
						);
					}
				}
				else
				{
					return OutColour_
					(
						colour_wrap_channel<out_channel_type, in_channel_type>(in_.R()),
						colour_wrap_channel<out_channel_type, in_channel_type>(in_.G()),
						colour_wrap_channel<out_channel_type, in_channel_type>(in_.B())
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
						out_.R(colour_wrap_channel<out_channel_type, in_channel_type>(in_.R()));
						out_.G(colour_wrap_channel<out_channel_type, in_channel_type>(in_.G()));
						out_.B(colour_wrap_channel<out_channel_type, in_channel_type>(in_.B()));
						out_.A(colour_wrap_channel<out_channel_type, in_channel_type>(in_.A()));
					}
					else
					{
						out_.R(colour_wrap_channel<out_channel_type, in_channel_type>(in_.R()));
						out_.G(colour_wrap_channel<out_channel_type, in_channel_type>(in_.G()));
						out_.B(colour_wrap_channel<out_channel_type, in_channel_type>(in_.B()));
						out_.A(OutColour_::max_intensity);
					}
				}
				else
				{
					out_.R(colour_wrap_channel<out_channel_type, in_channel_type>(in_.R()));
					out_.G(colour_wrap_channel<out_channel_type, in_channel_type>(in_.G()));
					out_.B(colour_wrap_channel<out_channel_type, in_channel_type>(in_.B()));
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
							colour_clamp_channel<out_channel_type, in_channel_type>(in_.R()),
							colour_clamp_channel<out_channel_type, in_channel_type>(in_.G()),
							colour_clamp_channel<out_channel_type, in_channel_type>(in_.B()),
							colour_clamp_channel<out_channel_type, in_channel_type>(in_.A())
						);
					}
					else
					{
						return OutColour_
						(
							colour_clamp_channel<out_channel_type, in_channel_type>(in_.R()),
							colour_clamp_channel<out_channel_type, in_channel_type>(in_.G()),
							colour_clamp_channel<out_channel_type, in_channel_type>(in_.B()),
							OutColour_::max_intensity
						);
					}
				}
				else
				{
					return OutColour_
					(
						colour_clamp_channel<out_channel_type, in_channel_type>(in_.R()),
						colour_clamp_channel<out_channel_type, in_channel_type>(in_.G()),
						colour_clamp_channel<out_channel_type, in_channel_type>(in_.B())
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
						out_.R(colour_clamp_channel<out_channel_type, in_channel_type>(in_.R()));
						out_.G(colour_clamp_channel<out_channel_type, in_channel_type>(in_.G()));
						out_.B(colour_clamp_channel<out_channel_type, in_channel_type>(in_.B()));
						out_.A(colour_clamp_channel<out_channel_type, in_channel_type>(in_.A()));
					}
					else
					{
						out_.R(colour_clamp_channel<out_channel_type, in_channel_type>(in_.R()));
						out_.G(colour_clamp_channel<out_channel_type, in_channel_type>(in_.G()));
						out_.B(colour_clamp_channel<out_channel_type, in_channel_type>(in_.B()));
						out_.A(OutColour_::max_intensity);
					}
				}
				else
				{
					out_.R(colour_clamp_channel<out_channel_type, in_channel_type>(in_.R()));
					out_.G(colour_clamp_channel<out_channel_type, in_channel_type>(in_.G()));
					out_.B(colour_clamp_channel<out_channel_type, in_channel_type>(in_.B()));
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

	template<bool IncludeAlpha_ = true, class LhsColour_, class RhsColour_>
	[[nodiscard]] constexpr inline bool colour_cmp_equal(const LhsColour_& lhs_, const RhsColour_& rhs_)
	{
		using Combiner_ = std::logical_and<bool>;
		return _underlying_colour_funcs::colour_cmp
		<
			IncludeAlpha_,
			EmuCore::do_cmp_equal_to,
			Combiner_,
			LhsColour_,
			RhsColour_
		>(lhs_, rhs_, Combiner_());
	}
	template<bool IncludeAlpha_ = true, class LhsColour_, class RhsColour_>
	[[nodiscard]] constexpr inline bool colour_cmp_not_equal(const LhsColour_& lhs_, const RhsColour_& rhs_)
	{
		using Combiner_ = std::logical_or<bool>;
		return _underlying_colour_funcs::colour_cmp
		<
			IncludeAlpha_,
			EmuCore::do_cmp_not_equal_to,
			Combiner_,
			LhsColour_,
			RhsColour_
		>(lhs_, rhs_, Combiner_());
	}

	template<class OutColour_, bool IncludeAlpha_ = true, class LhsColour_, class Rhs_>
	[[nodiscard]] constexpr inline OutColour_ colour_multiply(const LhsColour_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_colour_funcs::colour_arithmetic
		<
			IncludeAlpha_,
			EmuCore::do_multiply,
			OutColour_,
			LhsColour_,
			Rhs_
		>(lhs_, rhs_);
	}

	template<typename OutColour_, bool IncludeAlpha_ = true, class LhsColour_, class Rhs_>
	[[nodiscard]] constexpr inline OutColour_ colour_divide(const LhsColour_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_colour_funcs::colour_arithmetic
		<
			IncludeAlpha_,
			EmuCore::do_divide,
			OutColour_,
			LhsColour_,
			Rhs_
		>(lhs_, rhs_);
	}

	template<typename OutColour_, bool IncludeAlpha_ = true, class LhsColour_, class Rhs_>
	[[nodiscard]] constexpr inline OutColour_ colour_add(const LhsColour_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_colour_funcs::colour_arithmetic
		<
			IncludeAlpha_,
			EmuCore::do_add,
			OutColour_,
			LhsColour_,
			Rhs_
		>(lhs_, rhs_);
	}

	template<typename OutColour_, bool IncludeAlpha_ = true, class LhsColour_, class Rhs_>
	[[nodiscard]] constexpr inline OutColour_ colour_subtract(const LhsColour_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_colour_funcs::colour_arithmetic
		<
			IncludeAlpha_,
			EmuCore::do_subtract,
			OutColour_,
			LhsColour_,
			Rhs_
		>(lhs_, rhs_);
	}

	template<typename OutColour_, bool IncludeAlpha_ = true, class LhsColour_, class Rhs_>
	[[nodiscard]] constexpr inline OutColour_ colour_mod(const LhsColour_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_colour_funcs::colour_arithmetic
		<
			IncludeAlpha_,
			EmuCore::do_mod,
			OutColour_,
			LhsColour_,
			Rhs_
		>(lhs_, rhs_);
	}

	template<class OutColour_, bool IncludeAlpha_ = true, class ColourA_, class ColourB_, class T_>
	[[nodiscard]] constexpr inline OutColour_ colour_lerp(const ColourA_& a_, const ColourB_& b_, const T_& t_)
	{
		return _underlying_colour_funcs::colour_lerp
		<
			IncludeAlpha_,
			OutColour_,
			ColourA_,
			ColourB_,
			T_
		>(a_, b_, t_);
	}

	template<typename Out_, bool IncludeAlpha_ = false, class Colour_>
	[[nodiscard]] constexpr inline Out_ colour_min(const Colour_& colour_)
	{
		return _underlying_colour_funcs::colour_min_or_max
		<
			IncludeAlpha_,
			Out_,
			Colour_,
			EmuCore::do_min<typename Colour_::value_type, typename Colour_::value_type>
		>(colour_);
	}

	template<typename Out_, bool IncludeAlpha_ = false, class Colour_>
	[[nodiscard]] constexpr inline Out_ colour_max(const Colour_& colour_)
	{
		return _underlying_colour_funcs::colour_min_or_max
		<
			IncludeAlpha_,
			Out_,
			Colour_,
			EmuCore::do_max<typename Colour_::value_type, typename Colour_::value_type>
		>(colour_);
	}

	template<class OutColour_, class InColour_>
	[[nodiscard]] constexpr inline OutColour_ colour_greyscale_basic_average(const InColour_& in_)
	{
		return _underlying_colour_funcs::_colour_greyscale_basic_average<OutColour_, InColour_>(in_);
	}
	template<class OutColour_, class InColour_>
	[[nodiscard]] constexpr inline OutColour_ colour_greyscale_luminance_average(const InColour_& in_)
	{
		return _underlying_colour_funcs::_colour_greyscale_luminance_average<OutColour_, InColour_>(in_);
	}
	template<class OutColour_, class InColour_>
	[[nodiscard]] constexpr inline OutColour_ colour_greyscale_desaturate(const InColour_& in_)
	{
		return _underlying_colour_funcs::_colour_greyscale_desaturate<OutColour_, InColour_>(in_);
	}
	template<class OutColour_, class InColour_>
	[[nodiscard]] constexpr inline OutColour_ colour_greyscale_decompose_min(const InColour_& in_)
	{
		using in_channel_type = typename InColour_::value_type;
		return _underlying_colour_funcs::_colour_greyscale_decompose<OutColour_, InColour_, EmuCore::do_min<in_channel_type, in_channel_type>>(in_);
	}
	template<class OutColour_, class InColour_>
	[[nodiscard]] constexpr inline OutColour_ colour_greyscale_decompose_max(const InColour_& in_)
	{
		using in_channel_type = typename InColour_::value_type;
		return _underlying_colour_funcs::_colour_greyscale_decompose<OutColour_, InColour_, EmuCore::do_max<in_channel_type, in_channel_type>>(in_);
	}
}

#endif
