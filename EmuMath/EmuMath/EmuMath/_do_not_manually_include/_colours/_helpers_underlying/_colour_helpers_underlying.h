#ifndef EMU_MATH_COLOUR_HELPERS_UNDERLYING_H_INC_
#define EMU_MATH_COLOUR_HELPERS_UNDERLYING_H_INC_ 1

#include "_colour_helpers_underlying_common_includes.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuMath::Helpers::_underlying_colour_funcs
{
	template<typename ChannelType_>
	[[nodiscard]] constexpr inline ChannelType_ _colour_colour_max_channel_intensity_force_fp()
	{
		return ChannelType_(1);
	}
	template<typename ChannelType_>
	[[nodiscard]] constexpr inline ChannelType_ _colour_colour_max_channel_intensity_force_int()
	{
		return std::numeric_limits<ChannelType_>::max();
	}

	template<typename ChannelType_>
	[[nodiscard]] constexpr inline ChannelType_ _colour_min_channel_intensity()
	{
		return ChannelType_(0);
	}

	template<typename ChannelType_>
	[[nodiscard]] constexpr inline ChannelType_ _colour_max_channel_intensity()
	{
		if constexpr (std::is_floating_point_v<ChannelType_>)
		{
			return _colour_colour_max_channel_intensity_force_fp<ChannelType_>();
		}
		else
		{
			return _colour_colour_max_channel_intensity_force_int<ChannelType_>();
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
			constexpr OutRatio_ max_reciprocal_ = OutRatio_(1) / _colour_max_channel_intensity<InChannel_>();
			return static_cast<OutRatio_>(in_) * max_reciprocal_;
		}
	}

	template<typename OutChannel_, typename InChannel_>
	[[nodiscard]] constexpr inline OutChannel_ _colour_get_intensity_from_other_ratio(InChannel_ to_convert_)
	{
		using calc_type = typename EmuCore::TMP::first_floating_point<OutChannel_, InChannel_, double>::type;
		constexpr calc_type max_out_calc = static_cast<calc_type>(_colour_max_channel_intensity<OutChannel_>());

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
				calc_type ratio_ = EmuCore::do_clamp<calc_type, calc_type, calc_type>()(static_cast<calc_type>(to_convert_), min_ratio_, max_ratio_);
				return static_cast<OutChannel_>(max_out_calc * ratio_);
			}
		}
		else
		{
			constexpr calc_type max_in_calc_reciprocal = calc_type(1) / static_cast<calc_type>(_colour_colour_max_channel_intensity_force_int<InChannel_>());
			calc_type ratio_ = to_convert_ * max_in_calc_reciprocal;
			if constexpr (std::is_floating_point_v<OutChannel_>)
			{
				return static_cast<OutChannel_>(ratio_);
			}
			else
			{
				constexpr calc_type min_ratio_ = std::is_unsigned_v<OutChannel_> ? calc_type(0) : calc_type(-1);
				constexpr calc_type max_ratio_ = calc_type(1);
				ratio_ = EmuCore::do_clamp<calc_type, calc_type, calc_type>()(ratio_, min_ratio_, max_ratio_);
				return static_cast<OutChannel_>(max_out_calc * ratio_);
			}
		}
	}

	template<typename OutChannel_, typename InChannel_>
	[[nodiscard]] constexpr inline OutChannel_ _colour_convert_channel(InChannel_ to_convert_)
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
			return _colour_get_intensity_from_other_ratio<OutChannel_, InChannel_>(to_convert_);
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
						_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_.R()))),
						_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.G(), rhs_.G()))),
						_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.B(), rhs_.B()))),
						_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.A(), rhs_.A())))
					);
				}
				else
				{
					return OutColour_
					(
						_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_.R()))),
						_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.G(), rhs_.G()))),
						_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.B(), rhs_.B()))),
						_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(lhs_.A()))
					);
				}
			}
			else
			{
				return OutColour_
				(
					_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_.R()))),
					_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.G(), rhs_.G()))),
					_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.B(), rhs_.B())))
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
						_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_.template at<0>()))),
						_colour_convert_channel<out_channel_type, lhs_channel_type>(lhs_.G()),
						_colour_convert_channel<out_channel_type, lhs_channel_type>(lhs_.B()),
						_colour_convert_channel<out_channel_type, lhs_channel_type>(lhs_.A())
					);
				}
				else if constexpr (RhsVector_::size == 2)
				{
					return OutColour_
					(
						_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_.template at<0>()))),
						_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.G(), rhs_.template at<1>()))),
						_colour_convert_channel<out_channel_type, lhs_channel_type>(lhs_.B()),
						_colour_convert_channel<out_channel_type, lhs_channel_type>(lhs_.A())
					);
				}
				else if constexpr (RhsVector_::size == 3)
				{
					return OutColour_
					(
						_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_.template at<0>()))),
						_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.G(), rhs_.template at<1>()))),
						_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.B(), rhs_.template at<2>()))),
						_colour_convert_channel<out_channel_type, lhs_channel_type>(lhs_.A())
					);
				}
				else
				{
					if constexpr (IncludeAlpha_)
					{
						return OutColour_
						(
							_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_.template at<0>()))),
							_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.G(), rhs_.template at<1>()))),
							_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.B(), rhs_.template at<2>()))),
							_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.A(), rhs_.template at<3>())))
						);
					}
					else
					{
						return OutColour_
						(
							_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_.template at<0>()))),
							_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.G(), rhs_.template at<1>()))),
							_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.B(), rhs_.template at<2>()))),
							_colour_convert_channel<out_channel_type, lhs_channel_type>(lhs_.A())
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
						_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_.template at<0>()))),
						_colour_convert_channel<out_channel_type, lhs_channel_type>(lhs_.G()),
						_colour_convert_channel<out_channel_type, lhs_channel_type>(lhs_.B())
					);
				}
				else if constexpr (RhsVector_::size == 2)
				{
					return OutColour_
					(
						_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_.template at<0>()))),
						_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.G(), rhs_.template at<1>()))),
						_colour_convert_channel<out_channel_type, lhs_channel_type>(lhs_.B())
					);
				}
				else
				{
					return OutColour_
					(
						_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_.template at<0>()))),
						_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.G(), rhs_.template at<1>()))),
						_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.B(), rhs_.template at<2>())))
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
				_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_))),
				_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.G(), rhs_))),
				_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.B(), rhs_))),
				_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.A(), rhs_)))
			);
		}
		else
		{
			return OutColour_
			(
				_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.R(), rhs_))),
				_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.G(), rhs_))),
				_colour_convert_channel<out_channel_type, lhs_channel_type>(static_cast<lhs_channel_type>(func_(lhs_.B(), rhs_)))
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
				static_assert(EmuCore::TMP::get_false<Rhs_>(), "Attempted to perform arithmetic with an EmuMath Colour, but the provided lhs_ was not an EmuMath Colour type.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Rhs_>(), "Attempted to perform arithmetic with an EmuMath Colour, but provided a non-EmuMath-Colour output OutColour_ type.");
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
				static_assert(EmuCore::TMP::get_false<AndOr_>(), "Attempted to compare two EmuMath Colours, but the provided rhs_ was not an EmuMath colour.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<AndOr_>(), "Attempted to compare two EmuMath Colours, but the provided lhs_ was not an EmuMath colour.");
		}
	}

	template<bool IncludeAlpha_, class OutColour_, class ColourA_, class ColourB_, class ColourT_>
	[[nodiscard]] constexpr inline OutColour_ _colour_lerp_t_colour(const ColourA_& a_, const ColourB_& b_, const ColourT_& t_)
	{
		using a_channel_type = typename ColourA_::value_type;
		using b_channel_type = typename ColourB_::value_type;

		if constexpr (compatible_channel_types<a_channel_type, b_channel_type>())
		{
			using out_channel_type = typename OutColour_::value_type;
			using t_channel_type = typename ColourT_::value_type;
			using t_ratio_type = typename EmuCore::TMP::first_floating_point<t_channel_type, double>::type;
			using Lerp_ = EmuCore::do_lerp<a_channel_type, b_channel_type, t_ratio_type>;
			Lerp_ lerp_ = Lerp_();

			// Only need to lerp alpha if at least A or B contains manual alpha, since implicit alpha is always 1.0 (or integral translation of such)
			// --- Additionally lerp(x, x, t) == x in all cases, so lerping the default with any other default would still result in the default
			if constexpr (IncludeAlpha_ && OutColour_::contains_alpha && (ColourA_::contains_alpha || ColourB_::contains_alpha))
			{
				return OutColour_
				(
					_colour_convert_channel<out_channel_type, a_channel_type>
					(
						static_cast<a_channel_type>(lerp_(a_.R(), b_.R(), _colour_channel_ratio<t_ratio_type, t_channel_type>(t_.R())))
					),
					_colour_convert_channel<out_channel_type, a_channel_type>
					(
						static_cast<a_channel_type>(lerp_(a_.G(), b_.G(), _colour_channel_ratio<t_ratio_type, t_channel_type>(t_.G())))
					),
					_colour_convert_channel<out_channel_type, a_channel_type>
					(
						static_cast<a_channel_type>(lerp_(a_.B(), b_.B(), _colour_channel_ratio<t_ratio_type, t_channel_type>(t_.B())))
					),
					_colour_convert_channel<out_channel_type, a_channel_type>
					(
						static_cast<a_channel_type>(lerp_(a_.A(), b_.A(), _colour_channel_ratio<t_ratio_type, t_channel_type>(t_.A())))
					)
				);
			}
			else
			{
				return OutColour_
				(
					_colour_convert_channel<out_channel_type, a_channel_type>
					(
						static_cast<a_channel_type>(lerp_(a_.R(), b_.R(), _colour_channel_ratio<t_ratio_type, t_channel_type>(t_.R())))
					),
					_colour_convert_channel<out_channel_type, a_channel_type>
					(
						static_cast<a_channel_type>(lerp_(a_.G(), b_.G(), _colour_channel_ratio<t_ratio_type, t_channel_type>(t_.G())))
					),
					_colour_convert_channel<out_channel_type, a_channel_type>
					(
						static_cast<a_channel_type>(lerp_(a_.B(), b_.B(), _colour_channel_ratio<t_ratio_type, t_channel_type>(t_.B())))
					)
				);
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<OutColour_>(), "Provided a_ and b_ colours with incompatible channels to _colour_lerp_t_colour. Channel compatibility should be resolved via colour_lerp.");
		}
	}

	template<bool IncludeAlpha_, class OutColour_, class ColourA_, class ColourB_, class VectorT_>
	[[nodiscard]] constexpr inline OutColour_ _colour_lerp_t_vector(const ColourA_& a_, const ColourB_& b_, const VectorT_& t_)
	{
		using a_channel_type = typename ColourA_::value_type;
		using b_channel_type = typename ColourB_::value_type;

		if constexpr (compatible_channel_types<a_channel_type, b_channel_type>())
		{
			using out_channel_type = typename OutColour_::value_type;
			using t_value_type = typename VectorT_::value_type;
			using Lerp_ = EmuCore::do_lerp<a_channel_type, b_channel_type, t_value_type>;
			Lerp_ lerp_ = Lerp_();

			// Only need to lerp alpha if at least A or B contains manual alpha, since implicit alpha is always 1.0 (or integral translation of such)
			// --- Additionally lerp(x, x, t) == x in all cases, so lerping the default with any other default would still result in the default
			// --- Furthermore, lerp(x, y, 0) == x in all cases, so only lerp A when an alpha t is provided.
			if constexpr (IncludeAlpha_ && OutColour_::contains_alpha && (ColourA_::contains_alpha || ColourB_::contains_alpha) && VectorT_::size >= 4)
			{
				return OutColour_
				(
					_colour_convert_channel<out_channel_type, a_channel_type>
					(
						static_cast<a_channel_type>(lerp_(a_.R(), b_.R(), t_.template at<0>()))
					),
					_colour_convert_channel<out_channel_type, a_channel_type>
					(
						static_cast<a_channel_type>(lerp_(a_.G(), b_.G(), t_.template at<1>()))
					),
					_colour_convert_channel<out_channel_type, a_channel_type>
					(
						static_cast<a_channel_type>(lerp_(a_.B(), b_.B(), t_.template at<2>()))
					),
					_colour_convert_channel<out_channel_type, a_channel_type>
					(
						static_cast<a_channel_type>(lerp_(a_.A(), b_.A(), t_.template at<3>()))
					)
				);
			}
			else
			{
				// Omit lerps in any cases where t_ is implied 0 (i.e. does not exist), since any lerp(a, b, 0) == a
				if constexpr (VectorT_::size == 0)
				{
					// All indices in t_ are implied 0, so just return a_ converted to our output type
					return OutColour_(a_);
				}
				else if constexpr (VectorT_::size == 1)
				{
					return OutColour_
					(
						_colour_convert_channel<out_channel_type, a_channel_type>
						(
							static_cast<a_channel_type>(lerp_(a_.R(), b_.R(), t_.template at<0>()))
						),
						_colour_convert_channel<out_channel_type, a_channel_type>(a_.G()),
						_colour_convert_channel<out_channel_type, a_channel_type>(a_.B())
					);
				}
				else if constexpr (VectorT_::size == 2)
				{
					return OutColour_
					(
						_colour_convert_channel<out_channel_type, a_channel_type>
						(
							static_cast<a_channel_type>(lerp_(a_.R(), b_.R(), t_.template at<0>()))
						),
						_colour_convert_channel<out_channel_type, a_channel_type>
						(
							static_cast<a_channel_type>(lerp_(a_.G(), b_.G(), t_.template at<1>()))
						),
						_colour_convert_channel<out_channel_type, a_channel_type>(a_.B())
					);
				}
				else
				{
					return OutColour_
					(
						_colour_convert_channel<out_channel_type, a_channel_type>
						(
							static_cast<a_channel_type>(lerp_(a_.R(), b_.R(), t_.template at<0>()))
						),
						_colour_convert_channel<out_channel_type, a_channel_type>
						(
							static_cast<a_channel_type>(lerp_(a_.G(), b_.G(), t_.template at<1>()))
						),
						_colour_convert_channel<out_channel_type, a_channel_type>
						(
							static_cast<a_channel_type>(lerp_(a_.B(), b_.B(), t_.template at<2>()))
						)
					);
				}
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<OutColour_>(), "Provided a_ and b_ colours with incompatible channels to _colour_lerp_t_vector. Channel compatibility should be resolved via colour_lerp.");
		}
	}

	template<bool IncludeAlpha_, class OutColour_, class ColourA_, class ColourB_, class ScalarT_>
	[[nodiscard]] constexpr inline OutColour_ _colour_lerp_t_scalar(const ColourA_& a_, const ColourB_& b_, const ScalarT_& t_)
	{
		using a_channel_type = typename ColourA_::value_type;
		using b_channel_type = typename ColourB_::value_type;

		if constexpr (compatible_channel_types<a_channel_type, b_channel_type>())
		{
			using out_channel_type = typename OutColour_::value_type;
			using Lerp_ = EmuCore::do_lerp<a_channel_type, b_channel_type, ScalarT_>;
			Lerp_ lerp_ = Lerp_();

			// Only need to lerp alpha if at least A or B contains manual alpha, since implicit alpha is always 1.0 (or integral translation of such)
			// --- Additionally lerp(x, x, t) == x in all cases, so lerping the default with any other default would still result in the default
			if constexpr (IncludeAlpha_ && OutColour_::contains_alpha && (ColourA_::contains_alpha || ColourB_::contains_alpha))
			{
				return OutColour_
				(
					_colour_convert_channel<out_channel_type, a_channel_type>(static_cast<a_channel_type>(lerp_(a_.R(), b_.R(), t_))),
					_colour_convert_channel<out_channel_type, a_channel_type>(static_cast<a_channel_type>(lerp_(a_.G(), b_.G(), t_))),
					_colour_convert_channel<out_channel_type, a_channel_type>(static_cast<a_channel_type>(lerp_(a_.B(), b_.B(), t_))),
					_colour_convert_channel<out_channel_type, a_channel_type>(static_cast<a_channel_type>(lerp_(a_.A(), b_.A(), t_)))
				);
			}
			else
			{
				return OutColour_
				(
					_colour_convert_channel<out_channel_type, a_channel_type>(static_cast<a_channel_type>(lerp_(a_.R(), b_.R(), t_))),
					_colour_convert_channel<out_channel_type, a_channel_type>(static_cast<a_channel_type>(lerp_(a_.G(), b_.G(), t_))),
					_colour_convert_channel<out_channel_type, a_channel_type>(static_cast<a_channel_type>(lerp_(a_.B(), b_.B(), t_)))
				);
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<OutColour_>(), "Provided a_ and b_ colours with incompatible channels to _colour_lerp_t_scalar. Channel compatibility should be resolved via colour_lerp.");
		}
	}

	template<bool IncludeAlpha_, class OutColour_, class ColourA_, class ColourB_, class T_>
	[[nodiscard]] constexpr inline OutColour_ colour_lerp(const ColourA_& a_, const ColourB_& b_, const T_& t_)
	{
		if constexpr (EmuMath::TMP::is_emu_colour_v<OutColour_>)
		{
			if constexpr (EmuMath::TMP::is_emu_colour_v<ColourA_>)
			{
				if constexpr (EmuMath::TMP::is_emu_colour_v<ColourB_>)
				{
					using a_channel_type = typename ColourA_::value_type;
					using b_channel_type = typename ColourB_::value_type;
					if constexpr (compatible_channel_types<a_channel_type, b_channel_type>())
					{
						if constexpr (EmuMath::TMP::is_emu_colour_v<T_>)
						{
							return _colour_lerp_t_colour<IncludeAlpha_, OutColour_, ColourA_, ColourB_, T_>(a_, b_, t_);
						}
						else if constexpr (EmuMath::TMP::is_emu_vector_v<T_>)
						{
							return _colour_lerp_t_vector<IncludeAlpha_, OutColour_, ColourA_, ColourB_, T_>(a_, b_, t_);
						}
						else
						{
							return _colour_lerp_t_scalar<IncludeAlpha_, OutColour_, ColourA_, ColourB_, T_>(a_, b_, t_);
						}
					}
					else
					{
						if constexpr (std::is_floating_point_v<b_channel_type>)
						{
							using a_conversion_type = EmuMath::Colour<b_channel_type, ColourA_::contains_alpha>;
							return colour_lerp<IncludeAlpha_, OutColour_>(a_conversion_type(a_), b_, t_);
						}
						else
						{
							using b_conversion_type = EmuMath::Colour<a_channel_type, ColourB_::contains_alpha>;
							return colour_lerp<IncludeAlpha_, OutColour_>(a_, b_conversion_type(b_), t_);
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<T_>(), "Attempted to linearly interpolate two EmuMath Colours, but the provided input a_ was not an EmuMath Colour.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<T_>(), "Attempted to linearly interpolate two EmuMath Colours, but the provided input a_ was not an EmuMath Colour.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<T_>(), "Attempted to linearly interpolate two EmuMath Colours, but the provided output OutColour_ was not an EmuMath Colour type.");
		}
	}

	template<bool IncludeAlpha_, typename Out_, class Colour_, class Func_>
	[[nodiscard]] constexpr inline Out_ colour_min_or_max(const Colour_& in_)
	{
		if constexpr (EmuMath::TMP::is_emu_colour_v<Colour_>)
		{
			Func_ func_ = Func_();
			using in_channel_type = typename Colour_::value_type;
			in_channel_type min_or_max_ = func_(in_.R(), in_.G());
			if constexpr (IncludeAlpha_)
			{
				// Need to check Alpha as well, so perform an additional store
				min_or_max_ = func_(min_or_max_, in_.B());
				return static_cast<Out_>(func_(min_or_max_, in_.A()));
			}
			else
			{
				// Only need to compare result to Blue channel, so just output that result directly
				return static_cast<Out_>(func_(min_or_max_, in_.B()));
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Out_>(), "Attempted to find an EmuMath Colour's min or max element, but the provided input Colour_ was not an EmuMath Colour.");
		}
	}

	template<class OutColour_, class InColour_>
	[[nodiscard]] constexpr inline bool _assert_colour_greyscale()
	{
		if constexpr (EmuMath::TMP::is_emu_colour_v<OutColour_>)
		{
			if constexpr (EmuMath::TMP::is_emu_colour_v<InColour_>)
			{
				return true;
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<InColour_>(), "Attempted to greyscale an EmuMath Colour, but the provided in_ colour was not an EmuMath Colour.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<InColour_>(), "Attempted to greyscale an EmuMath Colour, but the provided output OutColour_ type was not an EmuMath Colour type.");
		}
	}

	template<class OutColour_, class InColour_>
	[[nodiscard]] constexpr inline OutColour_ _colour_greyscale_basic_average(const InColour_& in_)
	{
		if constexpr (_assert_colour_greyscale<OutColour_, InColour_>())
		{
			// Ensure safe calculation by enforcing ratios rather than integers
			using in_channel_type = typename InColour_::value_type;
			using out_channel_type = typename OutColour_::value_type;
			using in_ratio_type = EmuCore::TMP::first_floating_point_t<in_channel_type, out_channel_type, float>;
			in_ratio_type average_ratio_ = _colour_channel_ratio<in_ratio_type, in_channel_type>(in_.R());
			average_ratio_ += _colour_channel_ratio<in_ratio_type, in_channel_type>(in_.G());
			average_ratio_ += _colour_channel_ratio<in_ratio_type, in_channel_type>(in_.B());

			constexpr in_ratio_type div_by_3_reciprocal = in_ratio_type(1) / in_ratio_type(3);
			average_ratio_ *= div_by_3_reciprocal;
			out_channel_type out_average_ = _colour_convert_channel<out_channel_type, in_ratio_type>(average_ratio_);

			if constexpr (OutColour_::contains_alpha)
			{
				return OutColour_(out_average_, out_average_, out_average_, _colour_convert_channel<out_channel_type, in_channel_type>(in_.A()));
			}
			else
			{
				return OutColour_(out_average_, out_average_, out_average_);
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<OutColour_>(), "Invalid arguments provided to colour_greyscale_basic_average.");
		}
	}

	template<class OutColour_, class InColour_>
	[[nodiscard]] constexpr inline OutColour_ _colour_greyscale_luminance_average(const InColour_& in_)
	{
		if constexpr (_assert_colour_greyscale<OutColour_, InColour_>())
		{
			// Ensure safe calculation by enforcing ratios rather than integers
			using in_channel_type = typename InColour_::value_type;
			using out_channel_type = typename OutColour_::value_type;
			using in_ratio_type = EmuCore::TMP::first_floating_point_t<in_channel_type, out_channel_type, float>;
			constexpr in_ratio_type red_mult_ = in_ratio_type(0.3L);
			constexpr in_ratio_type green_mult_ = in_ratio_type(0.59L);
			constexpr in_ratio_type blue_mult_ = in_ratio_type(0.11L);

			in_ratio_type average_ratio_ = _colour_channel_ratio<in_ratio_type, in_channel_type>(in_.R()) * red_mult_;
			average_ratio_ += _colour_channel_ratio<in_ratio_type, in_channel_type>(in_.G()) * green_mult_;
			average_ratio_ += _colour_channel_ratio<in_ratio_type, in_channel_type>(in_.B()) * blue_mult_;

			out_channel_type out_average_ = _colour_convert_channel<out_channel_type, in_ratio_type>(average_ratio_);
			if constexpr (OutColour_::contains_alpha)
			{
				return OutColour_(out_average_, out_average_, out_average_, _colour_convert_channel<out_channel_type, in_channel_type>(in_.A()));
			}
			else
			{
				return OutColour_(out_average_, out_average_, out_average_);
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<OutColour_>(), "Invalid arguments provided to colour_greyscale_luminance_average.");
		}
	}

	template<class OutColour_, class InColour_>
	[[nodiscard]] constexpr inline OutColour_ _colour_greyscale_desaturate(const InColour_& in_)
	{
		if constexpr (_assert_colour_greyscale<OutColour_, InColour_>())
		{
			// Ensure safe calculation by enforcing ratios rather than integers
			using in_channel_type = typename InColour_::value_type;
			using out_channel_type = typename OutColour_::value_type;
			using in_ratio_type = EmuCore::TMP::first_floating_point_t<in_channel_type, out_channel_type, float>;
			constexpr in_ratio_type two_reciprocal_ = in_ratio_type(1) / in_ratio_type(2);
			in_ratio_type min_ratio_ = _colour_channel_ratio<in_ratio_type, in_channel_type>
			(
				colour_min_or_max<false, in_channel_type, InColour_, EmuCore::do_min<in_channel_type, in_channel_type>>(in_)
			);
			in_ratio_type max_ratio_ = _colour_channel_ratio<in_ratio_type, in_channel_type>
			(
				colour_min_or_max<false, in_channel_type, InColour_, EmuCore::do_max<in_channel_type, in_channel_type>>(in_)
			);

			out_channel_type out_grey_ = _colour_convert_channel<out_channel_type, in_ratio_type>((min_ratio_ + max_ratio_) * two_reciprocal_);

			if constexpr (OutColour_::contains_alpha)
			{
				return OutColour_(out_grey_, out_grey_, out_grey_, _colour_convert_channel<out_channel_type, in_channel_type>(in_.A()));
			}
			else
			{
				return OutColour_(out_grey_, out_grey_, out_grey_);
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<OutColour_>(), "Invalid arguments provided to colour_greyscale_desaturate.");
		}
	}

	template<class OutColour_, class InColour_, class MinOrMaxFunc_>
	[[nodiscard]] constexpr inline OutColour_ _colour_greyscale_decompose(const InColour_& in_)
	{
		if constexpr (_assert_colour_greyscale<OutColour_, InColour_>())
		{
			using in_channel_type = typename InColour_::value_type;
			using out_channel_type = typename OutColour_::value_type;

			out_channel_type out_grey_ = _colour_convert_channel<out_channel_type, in_channel_type>
			(
				colour_min_or_max<false, in_channel_type, InColour_, MinOrMaxFunc_>(in_)
			);

			if constexpr (OutColour_::contains_alpha)
			{
				return OutColour_(out_grey_, out_grey_, out_grey_, _colour_convert_channel<out_channel_type, in_channel_type>(in_.A()));
			}
			else
			{
				return OutColour_(out_grey_, out_grey_, out_grey_);
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<OutColour_>(), "Invalid arguments provided to colour_greyscale_decompose.");
		}
	}
}

#endif
