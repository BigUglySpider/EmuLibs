#ifndef EMU_MATH_COLOUR_RGB_H_INC_
#define EMU_MATH_COLOUR_RGB_H_INC_ 1

#include "ColourHelpers.h"
#include "../../../EmuCore/Functors/Arithmetic.h"
#include "../../../EmuCore/TMPHelpers/TypeComparators.h"
#include "../../Vector.h"
#include <limits>
#include <ostream>
#include <type_traits>

namespace EmuMath
{
	/// <summary>
	/// <para> Colour that contains intensities for Red, Green, and Blue channels. </para>
	/// <para> Does not store an alpha, but provides an implicit alpha value of the value_type's maximum intensity. </para>
	/// <para> If the provided Channel_ type is a floating-point: intensities will be considered to have the valid range 0:1. </para>
	/// <para> If the provided Channel_ type is an integer: intensities will be considered to have the valid range range 0:std::numeric_limits&lt;Channel_&gt;::max(). </para>
	/// </summary>
	template<typename Channel_>
	struct ColourRGB
	{
	public:
		using value_type = Channel_;
		using this_type = EmuMath::ColourRGB<value_type>;
		using contained_vector = EmuMath::Vector<3, value_type>;

		static constexpr bool is_floating_point = std::is_floating_point_v<value_type>;
		static constexpr bool is_integral = std::is_integral_v<value_type>;
		static_assert
		(
			is_floating_point || is_integral,
			"Provided a type to an EmuMath::ColourRGB template instantiation which is neither floating point nor integral. Contained Channel_ types must meet one of these criteria."
		);

		static constexpr value_type min_intensity = value_type(0);
		static constexpr value_type max_intensity = is_floating_point ? value_type(1) : std::numeric_limits<value_type>::max();

		constexpr ColourRGB() : channels(min_intensity, min_intensity, min_intensity)
		{
		}
		constexpr ColourRGB(const this_type& to_copy_) : channels(to_copy_)
		{
		}
		template<typename RhsChannel_>
		explicit constexpr ColourRGB(const ColourRGB<RhsChannel_>& to_convert_) :
			channels
			(
				EmuMath::Helpers::convert_colour_channel<value_type, RhsChannel_>(to_convert_.channels.at<0>()),
				EmuMath::Helpers::convert_colour_channel<value_type, RhsChannel_>(to_convert_.channels.at<1>()),
				EmuMath::Helpers::convert_colour_channel<value_type, RhsChannel_>(to_convert_.channels.at<2>())
			)
		{
		}
		template<typename...Args_, typename = std::enable_if_t<std::is_constructible_v<contained_vector, Args_...>>>
		constexpr ColourRGB(Args_&&...args_) : channels(args_...)
		{
		}

#pragma region CONST_OPERATORS
		template<typename RhsChannel_>
		constexpr inline bool operator==(const EmuMath::ColourRGB<RhsChannel_>& rhs_) const
		{
			return EmuMath::Helpers::colour_cmp_equal<value_type, RhsChannel_>(*this, rhs_);
		}

		template<typename Rhs_>
		constexpr inline this_type operator*(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::colour_multiply<value_type, Rhs_>(*this, rhs_);
		}

		template<typename Rhs_>
		constexpr inline this_type operator/(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::colour_divide<value_type, Rhs_>(*this, rhs_);
		}
#pragma endregion

		template<std::size_t Index_>
		[[nodiscard]] constexpr inline value_type& at()
		{
			if constexpr (Index_ <= 4)
			{
				return channels.at<Index_>();
			}
		}

		[[nodiscard]] constexpr inline value_type& R()
		{
			return channels.at<0>();
		}
		[[nodiscard]] constexpr inline const value_type& R() const
		{
			return channels.at<0>();
		}
		[[nodiscard]] constexpr inline value_type& G()
		{
			return channels.at<1>();
		}
		[[nodiscard]] constexpr inline const value_type& G() const
		{
			return channels.at<1>();
		}
		[[nodiscard]] constexpr inline value_type& B()
		{
			return channels.at<2>();
		}
		[[nodiscard]] constexpr inline const value_type& B() const
		{
			return channels.at<2>();
		}

		[[nodiscard]] static constexpr inline std::size_t size()
		{
			return 3;
		}

		template<typename out_contained_type = value_type>
		[[nodiscard]] constexpr inline EmuMath::ColourRGB<out_contained_type> MakeWrapped() const
		{
			return EmuMath::Helpers::wrap_colour<out_contained_type, value_type>(*this);
		}
		inline this_type& Wrap()
		{
			return EmuMath::Helpers::wrap_colour(*this, *this);
		}

		template<typename out_contained_type = value_type>
		[[nodiscard]] constexpr inline EmuMath::ColourRGB<out_contained_type> MakeClamped() const
		{
			return EmuMath::Helpers::clamp_colour<out_contained_type, value_type>(*this);
		}
		inline this_type& Clamp()
		{
			return EmuMath::Helpers::clamp_colour(*this, *this);
		}

		template<typename out_contained_type>
		[[nodiscard]] constexpr inline EmuMath::ColourRGB<out_contained_type> As() const
		{
			return EmuMath::ColourRGB<out_contained_type>(*this);
		}

		contained_vector channels;
	};
}

template<typename T_>
std::ostream& operator<<(std::ostream& str_, const EmuMath::ColourRGB<T_>& colour_)
{
	str_ << colour_.channels;
	return str_;
}

template<typename T_>
std::wostream& operator<<(std::wostream& str_, const EmuMath::ColourRGB<T_>& colour_)
{
	str_ << colour_.channels;
	return str_;
}

#endif
