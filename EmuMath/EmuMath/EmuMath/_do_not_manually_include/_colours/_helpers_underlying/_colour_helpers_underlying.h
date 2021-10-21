#ifndef EMU_MATH_COLOUR_HELPERS_UNDERLYING_H_INC_
#define EMU_MATH_COLOUR_HELPERS_UNDERLYING_H_INC_ 1

#include "_colour_helpers_underlying_common_includes.h"

namespace EmuMath::Helpers::_underlying_colour_funcs
{
	template<typename ChannelType_>
	[[nodiscard]] constexpr inline ChannelType_ _max_channel_intensity_force_fp()
	{
		return ChannelType_(1);
	}
	template<typename ChannelType_>
	[[nodiscard]] constexpr inline ChannelType_ _max_channel_intensity_force_int()
	{
		return std::numeric_limits<ChannelType_>::max();
	}

	template<typename ChannelType_>
	[[nodiscard]] constexpr inline ChannelType_ _min_channel_intensity()
	{
		return ChannelType_(0);
	}

	template<typename ChannelType_>
	[[nodiscard]] constexpr inline ChannelType_ _max_channel_intensity()
	{
		if constexpr (std::is_floating_point_v<ChannelType_>)
		{
			return _max_channel_intensity_force_fp<ChannelType_>();
		}
		else
		{
			return _max_channel_intensity_force_int<ChannelType_>();
		}
	}

	template<typename OutRatio_, typename InChannel_>
	[[nodiscard]] constexpr inline OutRatio_ _colour_channel_ratio(InChannel_ in_)
	{
		static_assert(std::is_floating_point_v<OutRatio_>, "Provided a non-floating-point OutRatio_ type to _colour_channel_ratio. The output ratio must be a floating-point.");

		if constexpr (std::is_floating_point_v<InChannel_>)
		{
			return static_cast<OutRatio_>(in_);
		}
		else
		{
			constexpr OutRatio_ max_reciprocal_ = OutRatio_(1) / _max_channel_intensity<InChannel_>();
			return static_cast<OutRatio_>(in_) * max_reciprocal_;
		}
	}

	template<typename OutChannel_, typename InChannel_>
	[[nodiscard]] constexpr inline OutChannel_ _get_colour_intensity_from_other_ratio(InChannel_ to_convert_)
	{
		using calc_type = typename EmuCore::TMPHelpers::first_floating_point<OutChannel_, InChannel_, double>::type;
		constexpr calc_type max_out_calc = static_cast<calc_type>(_max_channel_intensity<OutChannel_>());

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
			constexpr calc_type max_in_calc_reciprocal = calc_type(1) / static_cast<calc_type>(_max_channel_intensity_force_int<InChannel_>());
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
	[[nodiscard]] constexpr inline OutChannel_ _convert_colour_channel(InChannel_ to_convert_)
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
			return _get_colour_intensity_from_other_ratio<OutChannel_, InChannel_>(to_convert_);
		}
	}

	template<typename ChannelA_, typename ChannelB_>
	[[nodiscard]] constexpr inline bool compatible_channel_types()
	{
		return 
		(
			std::is_same_v<ChannelA_, ChannelB_> ||
			(std::is_floating_point_v<ChannelA_> && std::is_floating_point_v<ChannelB_>)
		);
	}

	template<bool IncludeAlpha_, template<typename Lhs__, typename Rhs__> class FuncTemplate_, class OutColour_, class LhsColour_, class RhsColour_>
	[[nodiscard]] constexpr inline OutColour_ _colour_arithmetic_rhs_colour(const LhsColour_& lhs_, const RhsColour_& rhs_)
	{
		// Arithmetic with two colours, so we're working with intensity translation rather than raw values
		using lhs_channel_type = typename LhsColour_::value_type;
		using out_channel_type = typename OutColour_::value_type;
		using rhs_channel_type = typename RhsColour_::value_type;
		if constexpr (compatible_channel_types<lhs_channel_type, rhs_channel_type>())
		{
			using Func_ = FuncTemplate_<lhs_channel_type, rhs_channel_type>;
			Func_ func_ = Func_();
			if constexpr (OutColour_::contains_alpha)
			{
				if constexpr (IncludeAlpha_ && (LhsColour_::contains_alpha || RhsColour_::contains_alpha))
				{
					return OutColour_
					(
						_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_.R()))),
						_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.G(), rhs_.G()))),
						_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.B(), rhs_.B()))),
						_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.A(), rhs_.A())))
					);
				}
				else
				{
					return OutColour_
					(
						_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_.R()))),
						_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.G(), rhs_.G()))),
						_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.B(), rhs_.B()))),
						_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(lhs_.A()))
					);
				}
			}
			else
			{
				return OutColour_
				(
					_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_.R()))),
					_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.G(), rhs_.G()))),
					_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.B(), rhs_.B())))
				);
			}
			
		}
		else
		{
			if constexpr (std::is_floating_point_v<rhs_channel_type>)
			{
				using lhs_conversion_type = EmuMath::Colour<rhs_channel_type, LhsColour_::contains_alpha>;
				return _colour_arithmetic_rhs_colour<IncludeAlpha_, FuncTemplate_, OutColour_>(lhs_conversion_type(lhs_), rhs_);
			}
			else
			{
				using rhs_conversion_type = EmuMath::Colour<lhs_channel_type, RhsColour_::contains_alpha>;
				return _colour_arithmetic_rhs_colour<IncludeAlpha_, FuncTemplate_, OutColour_>(lhs_, rhs_conversion_type(rhs_));
			}
		}
	}

	template<bool IncludeAlpha_, template<typename Lhs__, typename Rhs__> class FuncTemplate_, class OutColour_, class LhsColour_, class RhsVector_>
	[[nodiscard]] constexpr inline OutColour_ _colour_arithmetic_rhs_vector(const LhsColour_& lhs_, const RhsVector_& rhs_)
	{
		using lhs_channel_type = typename LhsColour_::value_type;
		using rhs_value_type = typename RhsVector_::value_type;
		using out_channel_type = typename OutColour_::value_type;

		// Exceptional vector usage
		// --- This is used to partially multiply a colour with partial vectors.
		// ------ As such, theoretical values are not necessarily considered 0, but whatever value would result in no change in an arithmetic operation
		// --------- E.g. 0 when adding/subtracting, 1 when multiplying/dividing
		if constexpr (RhsVector_::size == 0)
		{
			return OutColour_(lhs_);
		}
		else
		{
			using Func_ = FuncTemplate_<lhs_channel_type, rhs_value_type>;
			Func_ func_ = Func_();
			if constexpr (OutColour_::contains_alpha)
			{
				if constexpr (RhsVector_::size == 1)
				{
					return OutColour_
					(
						_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_.template at<0>()))),
						_convert_colour_channel<out_channel_type, lhs_channel_type>(lhs_.G()),
						_convert_colour_channel<out_channel_type, lhs_channel_type>(lhs_.B()),
						_convert_colour_channel<out_channel_type, lhs_channel_type>(lhs_.A())
					);
				}
				else if constexpr (RhsVector_::size == 2)
				{
					return OutColour_
					(
						_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_.template at<0>()))),
						_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.G(), rhs_.template at<1>()))),
						_convert_colour_channel<out_channel_type, lhs_channel_type>(lhs_.B()),
						_convert_colour_channel<out_channel_type, lhs_channel_type>(lhs_.A())
					);
				}
				else if constexpr (RhsVector_::size == 3)
				{
					return OutColour_
					(
						_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_.template at<0>()))),
						_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.G(), rhs_.template at<1>()))),
						_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.B(), rhs_.template at<2>()))),
						_convert_colour_channel<out_channel_type, lhs_channel_type>(lhs_.A())
					);
				}
				else
				{
					if constexpr (IncludeAlpha_)
					{
						return OutColour_
						(
							_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_.template at<0>()))),
							_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.G(), rhs_.template at<1>()))),
							_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.B(), rhs_.template at<2>()))),
							_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.A(), rhs_.template at<3>())))
						);
					}
					else
					{
						return OutColour_
						(
							_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_.template at<0>()))),
							_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.G(), rhs_.template at<1>()))),
							_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.B(), rhs_.template at<2>()))),
							_convert_colour_channel<out_channel_type, lhs_channel_type>(lhs_.A())
						);
					}
				}
			}
			else
			{
				if constexpr (RhsVector_::size == 1)
				{
					return OutColour_
					(
						_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_.template at<0>()))),
						_convert_colour_channel<out_channel_type, lhs_channel_type>(lhs_.G()),
						_convert_colour_channel<out_channel_type, lhs_channel_type>(lhs_.B())
					);
				}
				else if constexpr (RhsVector_::size == 2)
				{
					return OutColour_
					(
						_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_.template at<0>()))),
						_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.G(), rhs_.template at<1>()))),
						_convert_colour_channel<out_channel_type, lhs_channel_type>(lhs_.B())
					);
				}
				else
				{
					return OutColour_
					(
						_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_.template at<0>()))),
						_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.G(), rhs_.template at<1>()))),
						_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.B(), rhs_.template at<2>())))
					);
				}
			}
		}
	}

	template<bool IncludeAlpha_, template<typename Lhs__, typename Rhs__> class FuncTemplate_, class OutColour_, class LhsColour_, class RhsScalar_>
	[[nodiscard]] constexpr inline OutColour_ _colour_arithmetic_rhs_scalar(const LhsColour_& lhs_, const RhsScalar_& rhs_)
	{
		using lhs_channel_type = typename LhsColour_::value_type;
		using out_channel_type = typename OutColour_::value_type;
		using Func_ = FuncTemplate_<lhs_channel_type, RhsScalar_>;
		Func_ func_ = Func_();
		if constexpr (IncludeAlpha_ && OutColour_::contains_alpha)
		{
			return OutColour_
			(
				_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_))),
				_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.G(), rhs_))),
				_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.B(), rhs_))),
				_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.A(), rhs_)))
			);
		}
		else
		{
			return OutColour_
			(
				_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_))),
				_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.G(), rhs_))),
				_convert_colour_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.B(), rhs_)))
			);
		}
	}

	template<bool IncludeAlpha_, template<typename Lhs__, typename Rhs__> class FuncTemplate_, class OutColour_, class LhsColour_, class Rhs_>
	[[nodiscard]] constexpr inline OutColour_ colour_arithmetic(const LhsColour_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_colour_v<OutColour_>)
		{
			if constexpr (EmuMath::TMP::is_emu_colour_v<LhsColour_>)
			{
				if constexpr (EmuMath::TMP::is_emu_colour_v<Rhs_>)
				{
					return _colour_arithmetic_rhs_colour<IncludeAlpha_, FuncTemplate_, OutColour_, LhsColour_, Rhs_>(lhs_, rhs_);
				}
				else
				{
					// Arithmetic with non-colour rhs, so we're working with raw values
					if constexpr (EmuMath::TMP::is_emu_vector_v<Rhs_>)
					{
						// Special case for vectors so we can apply specific operations to each channel in just one call
						return _colour_arithmetic_rhs_vector<IncludeAlpha_, FuncTemplate_, OutColour_, LhsColour_, Rhs_>(lhs_, rhs_);
					}
					else
					{
						return _colour_arithmetic_rhs_scalar<IncludeAlpha_, FuncTemplate_, OutColour_, LhsColour_, Rhs_>(lhs_, rhs_);
					}
				}
			}
			else
			{
				static_assert(false, "Attempted to perform arithmetic with an EmuMath Colour, but the provided lhs_ was not an EmuMath Colour type.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform arithmetic with an EmuMath Colour, but provided a non-EmuMath-Colour output OutColour_ type.");
		}
	}

	template<bool IncludeAlpha_, template<typename Lhs__, typename Rhs__> class CmpTemplate_, class AndOr_, class LhsColour_, class RhsColour_>
	[[nodiscard]] constexpr inline bool colour_cmp(const LhsColour_& lhs_, const RhsColour_& rhs_, AndOr_ and_or_)
	{
		if constexpr (EmuMath::TMP::is_emu_colour_v<LhsColour_>)
		{
			if constexpr (EmuMath::TMP::is_emu_colour_v<RhsColour_>)
			{
				using lhs_channel_type = typename LhsColour_::value_type;
				using rhs_channel_type = typename RhsColour_::value_type;
				if constexpr(compatible_channel_types<lhs_channel_type, rhs_channel_type>())
				{
					// Passed colours contain either the same type, or floating points that lie in the same 0:1 range.
					// --- This allows us to compare without any conversions
					using Cmp_ = CmpTemplate_<lhs_channel_type, rhs_channel_type>;
					Cmp_ cmp_ = Cmp_();
					if constexpr (IncludeAlpha_ && (LhsColour_::contains_alpha || RhsColour_::contains_alpha))
					{
						return and_or_
						(
							cmp_(lhs_.R(), rhs_.R()),
							and_or_
							(
								cmp_(lhs_.G(), rhs_.G()),
								and_or_
								(
									cmp_(lhs_.B(), rhs_.B()),
									cmp_(lhs_.A(), rhs_.A())
								)
							)
						);
					}
					else
					{
						return and_or_
						(
							cmp_(lhs_.R(), rhs_.R()),
							and_or_
							(
								cmp_(lhs_.G(), rhs_.G()),
								cmp_(lhs_.B(), rhs_.B())
							)
						);
					}
				}
				else
				{
					// Passed colours contain incompatible intensity values, so a conversion is required
					// --- Prioritise floating-point comparison as float->int conversion is lossy which can lead to situations of (A == B) && (B != A)
					// --- These are recursive calls of this function which guarantee that the above constexpr branch is true
					// --- Conversions are automatically performed upon construction
					if constexpr (std::is_floating_point_v<rhs_channel_type>)
					{
						using lhs_conversion_type = EmuMath::Colour<rhs_channel_type, LhsColour_::contains_alpha>;
						return colour_cmp<IncludeAlpha_, CmpTemplate_, AndOr_&>(lhs_conversion_type(lhs_), rhs_, and_or_);
					}
					else
					{
						using rhs_conversion_type = EmuMath::Colour<lhs_channel_type, RhsColour_::contains_alpha>;
						return colour_cmp<IncludeAlpha_, CmpTemplate_, AndOr_&>(lhs_, rhs_conversion_type(rhs_), and_or_);
					}
				}
			}
			else
			{
				static_assert(false, "Attempted to compare two EmuMath Colours, but the provided rhs_ was not an EmuMath colour.");
			}
		}
		else
		{
			static_assert(false, "Attempted to compare two EmuMath Colours, but the provided lhs_ was not an EmuMath colour.");
		}
	}
}

#endif
