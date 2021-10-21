#ifndef EMU_MATH_COLOUR_T_H_INC_
#define EMU_MATH_COLOUR_T_H_INC_ 1

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
	/// <para> Colour that contains intensities for Red, Green, Blue, and optionally Alpha channels. </para>
	/// <para> Colours that do not store an alpha provide an implicit alpha value of the value_type's maximum intensity. </para>
	/// <para> If the provided Channel_ type is a floating-point: intensities will be considered to have the valid range 0:1. </para>
	/// <para> If the provided Channel_ type is an integer: intensities will be considered to have the valid range range 0:std::numeric_limits&lt;Channel_&gt;::max(). </para>
	/// </summary>
	template<typename Channel_, bool ContainsAlpha_>
	struct Colour
	{
	public:
		static constexpr bool contains_alpha = ContainsAlpha_;
		static constexpr std::size_t size = contains_alpha ? 4 : 3;

		using value_type = Channel_;
		using this_type = EmuMath::Colour<value_type, ContainsAlpha_>;
		using channels_vector = EmuMath::Vector<size, value_type>;

		static constexpr bool is_floating_point = std::is_floating_point_v<value_type>;
		static constexpr bool is_integral = std::is_integral_v<value_type>;
		static_assert
		(
			is_floating_point || is_integral,
			"Provided a type to an EmuMath::Colour template instantiation which is neither floating point nor integral. Contained Channel_ types must meet one of these criteria."
		);

		static constexpr value_type min_intensity = value_type(0);
		static constexpr value_type max_intensity = is_floating_point ? value_type(1) : std::numeric_limits<value_type>::max();

	private:
		[[nodiscard]] static constexpr inline channels_vector _make_default_colour()
		{
			if constexpr (contains_alpha)
			{
				return channels_vector(min_intensity, min_intensity, min_intensity, max_intensity);
			}
			else
			{
				return channels_vector(min_intensity, min_intensity, min_intensity);
			}
		}

		template<typename R_, typename G_, typename B_>
		[[nodiscard]] static constexpr inline channels_vector _make_colour(R_&& r_, G_&& g_, B_&& b_)
		{
			if constexpr (EmuCore::TMPHelpers::are_all_convertible_v<value_type, R_, G_, B_>)
			{
				if constexpr (contains_alpha)
				{
					return channels_vector(r_, g_, b_, max_intensity);
				}
				else
				{
					return channels_vector(r_, g_, b_);
				}
			}
			else
			{
				static_assert(false, "Attempted to make an EmuMath colour using at least one input channel argument that is not convertible to the colour's value type.");
			}
		}
		template<typename R_, typename G_, typename B_, typename A_>
		[[nodiscard]] static constexpr inline channels_vector _make_colour(R_&& r_, G_&& g_, B_&& b_, A_&& a_)
		{
			using check_type = std::conditional_t
			<
				contains_alpha,
				EmuCore::TMPHelpers::are_all_convertible<value_type, R_, G_, B_, A_>,
				EmuCore::TMPHelpers::are_all_convertible<value_type, R_, G_, B_>
			>;
			if constexpr (check_type::value)
			{
				if constexpr (contains_alpha)
				{
					return channels_vector(r_, g_, b_, a_);
				}
				else
				{
					return channels_vector(r_, g_, b_);
				}
			}
			else
			{
				static_assert(false, "Attempted to make an EmuMath colour using at least one input channel argument that is not convertible to the colour's value type.");
			}
		}

		[[nodiscard]] static constexpr inline channels_vector _make_colour_from_other_channels_with_diff_alpha(const EmuMath::Colour<value_type, !contains_alpha>& to_copy_)
		{
			if constexpr (contains_alpha)
			{
				return channels_vector(to_copy_.channels.at<0>(), to_copy_.channels.at<1>(), to_copy_.channels.at<2>(), max_intensity);
			}
			else
			{
				return channels_vector(to_copy_.channels.at<0>(), to_copy_.channels.at<1>(), to_copy_.channels.at<2>());
			}
		}

		template<typename RhsT_, bool RhsAlpha_>
		[[nodiscard]] static constexpr inline channels_vector _make_colour_from_arbitrary_other(const EmuMath::Colour<RhsT_, RhsAlpha_>& rhs_)
		{
			if constexpr (std::is_same_v<value_type, RhsT_>)
			{
				if constexpr (contains_alpha == RhsAlpha_)
				{
					return rhs_.channels;
				}
				else
				{
					return _make_colour_from_other_channels_with_diff_alpha(rhs_);
				}
			}
			else
			{
				if constexpr (contains_alpha)
				{
					if constexpr (RhsAlpha_)
					{
						return channels_vector
						(
							EmuMath::Helpers::convert_colour_channel<value_type, RhsT_>(rhs_.channels.at<0>()),
							EmuMath::Helpers::convert_colour_channel<value_type, RhsT_>(rhs_.channels.at<1>()),
							EmuMath::Helpers::convert_colour_channel<value_type, RhsT_>(rhs_.channels.at<2>()),
							EmuMath::Helpers::convert_colour_channel<value_type, RhsT_>(rhs_.channels.at<3>())
						);
					}
					else
					{
						return channels_vector
						(
							EmuMath::Helpers::convert_colour_channel<value_type, RhsT_>(rhs_.channels.at<0>()),
							EmuMath::Helpers::convert_colour_channel<value_type, RhsT_>(rhs_.channels.at<1>()),
							EmuMath::Helpers::convert_colour_channel<value_type, RhsT_>(rhs_.channels.at<2>()),
							max_intensity
						);
					}
				}
				else
				{
					return channels_vector
					(
						EmuMath::Helpers::convert_colour_channel<value_type, RhsT_>(rhs_.channels.at<0>()),
						EmuMath::Helpers::convert_colour_channel<value_type, RhsT_>(rhs_.channels.at<1>()),
						EmuMath::Helpers::convert_colour_channel<value_type, RhsT_>(rhs_.channels.at<2>())
					);
				}
			}
		}

		template<std::size_t Size_, typename VectorT_>
		[[nodiscard]] static constexpr inline channels_vector _make_colour_from_vector(const EmuMath::Vector<Size_, VectorT_>& channels_to_copy_)
		{
			if constexpr (std::is_same_v<EmuMath::Vector<Size_, VectorT_>, channels_vector>)
			{
				return channels_to_copy_;
			}
			else
			{
				if constexpr (contains_alpha)
				{
					if constexpr (Size_ >= 4)
					{
						// We know we have access to all required indices, so just use at instead of theoretical get
						return channels_vector
						(
							channels_to_copy_.at<0>(),
							channels_to_copy_.at<1>(),
							channels_to_copy_.at<2>(),
							channels_to_copy_.at<3>()
						);
					}
					else
					{
						// Exceptional case for vector args: Non-provided arguments for alpha are determined to mean max_intensity instead of 0
						// --- Since theoretical gets interpret non-contained elements as 0,
						// --- and we know there is no <3> element, we need to manually give max_intensity for the alpha
						return channels_vector
						(
							EmuMath::Helpers::VectorGetTheoretical<0>(channels_to_copy_),
							EmuMath::Helpers::VectorGetTheoretical<1>(channels_to_copy_),
							EmuMath::Helpers::VectorGetTheoretical<2>(channels_to_copy_),
							max_intensity
						);
					}
				}
				else
				{
					return channels_vector
					(
						EmuMath::Helpers::VectorGetTheoretical<0>(channels_to_copy_),
						EmuMath::Helpers::VectorGetTheoretical<1>(channels_to_copy_),
						EmuMath::Helpers::VectorGetTheoretical<2>(channels_to_copy_)
					);
				}
			}
		}

	public:
		static constexpr channels_vector _default_colour = _make_default_colour();

		/// <summary>
		/// <para> Constructs a default colour with its main channel intensities set to their minimum. </para>
		/// <para> If this colour contains an alpha channel, that channel will be set to its maximum intensity. </para>
		/// </summary>
		constexpr Colour() : channels(_default_colour)
		{
		}
		/// <summary>
		/// <para> Constructs a copy of the passed colour, matching intensities in each respective channel. </para>
		/// <para> Performs any necessary conversions (e.g. converting 0:255 byte ranges to 0:1 floating-point ranges) to represent the same colour. </para>
		/// </summary>
		/// <typeparam name="CopyChannelType_">Type of channel contained in the passed colour to copy.</typeparam>
		/// <param name="to_copy_">Colour to copy to the newly constructed colour.</param>
		template<typename CopyChannelType_, bool RhsContainsAlpha_>
		explicit constexpr Colour(const EmuMath::Colour<CopyChannelType_, RhsContainsAlpha_>& to_copy_) :
			channels(_make_colour_from_arbitrary_other<CopyChannelType_, RhsContainsAlpha_>(to_copy_))
		{
		}
		/// <summary> Constructs a copy of the passed colour. </summary>
		/// <param name="to_copy_">Colour to copy.</param>
		template<>
		constexpr Colour(const this_type& to_copy_) : channels(to_copy_.channels)
		{
		}
		/// <summary> Move constructor to create a colour from moved colour data. </summary>
		/// <param name="to_move_">Colour to move the data of into the newly constructed colour.</param>
		constexpr Colour(this_type&& to_move_) noexcept : channels(std::move(to_move_.channels))
		{
		}
		/// <summary>
		/// <para> Constructs a colour with its Red, Green, and Blue channels set via the passed r_, g_, and b_ values respectively. </para>
		/// <para> If this colour contains an Alpha value, it will be initialised at max_intensity. </para>
		/// </summary>
		/// <typeparam name="R_">Type used to provided the argument for this colour's Red channel.</typeparam>
		/// <typeparam name="G_">Type used to provided the argument for this colour's Green channel.</typeparam>
		/// <typeparam name="B_">Type used to provided the argument for this colour's Blue channel.</typeparam>
		/// <param name="r_">Value to initiaalise this colour's Red channel via.</param>
		/// <param name="g_">Value to initiaalise this colour's Green channel via.</param>
		/// <param name="b_">Value to initiaalise this colour's Blue channel via.</param>
		template<typename R_, typename G_, typename B_, typename = std::enable_if_t<EmuCore::TMPHelpers::are_all_convertible_v<value_type, R_, G_, B_>>>
		constexpr Colour(R_&& r_, G_&& g_, B_&& b_) : channels(_make_colour(r_, g_, b_))
		{
		}
		/// <summary>
		/// <para> Constructs a colour with its Red, Green, Blue, and Alpha channels set via the passed r_, g_, b_, and a_ values respectively. </para>
		/// <para> This constructor is only available for colours which explicitly contain a modifiable Alpha channel. </para>
		/// </summary>
		/// <typeparam name="R_">Type used to provided the argument for this colour's Red channel.</typeparam>
		/// <typeparam name="G_">Type used to provided the argument for this colour's Green channel.</typeparam>
		/// <typeparam name="B_">Type used to provided the argument for this colour's Blue channel.</typeparam>
		/// <typeparam name="A_">Type used to provided the argument for this colour's Alpha channel.</typeparam>
		/// <param name="r_">Value to initiaalise this colour's Red channel via.</param>
		/// <param name="g_">Value to initiaalise this colour's Green channel via.</param>
		/// <param name="b_">Value to initiaalise this colour's Blue channel via.</param>
		/// <param name="a_">Value to initiaalise this colour's Alpha channel via.</param>
		template
		<
			typename R_,
			typename G_,
			typename B_,
			typename A_,
			typename OnlyAvailableWith4Channels_ = std::enable_if_t<EmuCore::TMPHelpers::are_all_convertible_v<value_type, R_, G_, B_, A_> && contains_alpha>
		>
		constexpr Colour(R_&& r_, G_&& g_, B_&& b_, A_&& a_) : channels(_make_colour(r_, g_, b_, a_))
		{
		}
		/// <summary>
		/// <para> Creates a colour with its contained channels being a direct copy of the passed EmuMath vector. </para>
		/// </summary>
		/// <param name="channels_to_copy_">EmuMath vector representing channels to copy.</param>
		explicit constexpr Colour(const channels_vector& channels_to_copy_) : channels(channels_to_copy_)
		{
		}
		/// <summary> Creates a colour by moving the passed channels vector into its stored channel data. </summary>
		/// <param name="channels_to_move_">EmuMath vector to move into the constructed colour's channel data.</param>
		explicit constexpr Colour(channels_vector&& channels_to_move_) noexcept : channels(std::forward(channels_to_move_))
		{
		}


#pragma region ACCESS
		/// <summary> 
		/// <para> Retrieves a copy of the channel value at the provided index within this Colour's channels. </para>
		/// <para> If this Colour does not contain an explicit Alpha value, providing the Alpha index will result in max_intensity being returned. </para>
		/// </summary>
		/// <returns>Copy of the channel value at the provided index within this Colour's channels.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline value_type at() const
		{
			if constexpr (Index_ <= 3)
			{
				if constexpr (contains_alpha)
				{
					return channels.at<Index_>();
				}
				else
				{
					if constexpr (Index_ != 3)
					{
						return channels.at<Index_>();
					}
					else
					{
						return max_intensity;
					}
				}
			}
			else
			{
				static_assert(false, "Attempted to access an invalid channel index within an EmuMath Colour.");
			}
		}

		/// <summary>Returns a copy of this colour's Red channel.</summary>
		/// <returns>Copy of this colour's Red channel.</returns>
		[[nodiscard]] constexpr inline value_type R() const
		{
			return at<0>();
		}
		/// <summary>Returns a copy of this colour's Green channel.</summary>
		/// <returns>Copy of this colour's Green channel.</returns>
		[[nodiscard]] constexpr inline value_type G() const
		{
			return at<1>();
		}
		/// <summary>Returns a copy of this colour's Blue channel.</summary>
		/// <returns>Copy of this colour's Blue channel.</returns>
		[[nodiscard]] constexpr inline value_type B() const
		{
			return at<2>();
		}
		/// <summary>Returns a copy of this colour's Alpha channel.</summary>
		/// <returns>Copy of this colour's Alpha channel. If this colour type does not contain an explicit Alpha value, this will always be max_intensity.</returns>
		[[nodiscard]] constexpr inline value_type A() const
		{
			return at<3>();
		}
#pragma endregion

#pragma region SETS
		/// <summary> Sets this colour's Red channel to the passed value. </summary>
		/// <param name="r_">Value to set this colour's Red channel to. This will not be modified.</param>
		template<typename R_, typename = std::enable_if_t<std::is_convertible_v<R_, value_type>>>
		inline void R(R_&& r_)
		{
			channels.at<0>() = static_cast<value_type>(r_);
		}
		/// <summary> Sets this colour's Green channel to the passed value. </summary>
		/// <param name="g_">Value to set this colour's Green channel to. This will not be modified.</param>
		template<typename G_, typename = std::enable_if_t<std::is_convertible_v<G_, value_type>>>
		inline void G(G_&& g_)
		{
			channels.at<1>() = static_cast<value_type>(g_);
		}
		/// <summary> Sets this colour's Blue channel to the passed value. </summary>
		/// <param name="b_">Value to set this colour's Blue channel to. This will not be modified.</param>
		template<typename B_, typename = std::enable_if_t<std::is_convertible_v<B_, value_type>>>
		inline void B(B_&& b_)
		{
			channels.at<2>() = static_cast<value_type>(b_);
		}
		/// <summary> Sets this colour's Alpha channel to the passed value. Only available if this colour contains an explicit Alpha channel. </summary>
		/// <param name="a_">Value to set this colour's Alpha channel to. This will not be modified.</param>
		template<typename A_, typename MayOnlyModifyAlphaIfContained_ = std::enable_if_t<std::is_convertible_v<A_, value_type> && contains_alpha>>
		inline void A(A_&& a_)
		{
			channels.at<3>() = static_cast<value_type>(a_);
		}
#pragma endregion

#pragma region CONVERSIONS
		/// <summary> Shorthand to construct this colour as an alternate channel representation. May optionally change if output contains an Alpha channel. </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output colour.</typeparam>
		/// <returns>This colour converted to one containing the provided channel type.</returns>
		template<typename out_contained_type, bool OutContainsAlpha_ = contains_alpha>
		[[nodiscard]] constexpr inline EmuMath::Colour<out_contained_type, OutContainsAlpha_> As() const
		{
			return EmuMath::Colour<out_contained_type, OutContainsAlpha_>(*this);
		}
#pragma endregion

#pragma region COLOUR_OPERATIONS
		/// <summary>
		/// <para> Inverts the channels of this colour and outputs the inverted form as a new colour. </para>
		/// <para> Inverted channels can be summarised as "channel[x]` = max_intensity - channel[x]". </para>
		/// <para>
		///		Alpha inversion is optional and disabled by default, and may be enabled with a true template argument;
		///		changing this does nothing for 3-channel colours.
		/// </para>
		/// </summary>
		/// <returns>Copy of this colour with its channels inverted.</returns>
		template<bool IncludeAlpha_ = false>
		[[nodiscard]] constexpr inline this_type Inverse() const
		{
			return EmuMath::Helpers::colour_invert<IncludeAlpha_, this_type>(*this);
		}
		/// <summary>
		/// <para> Inverts the channels of this colour. </para>
		/// <para> Inverted channels can be summarised as "channel[x]` = max_intensity - channel[x]". </para>
		/// <para>
		///		Alpha inversion is optional and disabled by default, and may be enabled with a true template argument;
		///		changing this does nothing for 3-channel colours.
		/// </para>
		/// </summary>
		template<bool IncludeAlpha_ = false>
		inline void Invert()
		{
			EmuMath::Helpers::colour_invert<IncludeAlpha_, this_type>(*this, *this);
		}

		template<typename out_contained_type = value_type, bool OutContainsAlpha_ = contains_alpha>
		[[nodiscard]] constexpr inline EmuMath::Colour<out_contained_type, OutContainsAlpha_> Wrapped() const
		{
			return EmuMath::Helpers::colour_wrap<EmuMath::Colour<out_contained_type, OutContainsAlpha_>, this_type>(*this);
		}
		template<bool OutContainsAlpha_>
		[[nodiscard]] constexpr inline EmuMath::Colour<value_type, OutContainsAlpha_> Wrapped() const
		{
			return EmuMath::Helpers::colour_wrap<EmuMath::Colour<value_type, OutContainsAlpha_>, this_type>(*this);
		}
		inline void Wrap()
		{
			EmuMath::Helpers::colour_wrap<this_type, this_type>(*this, *this);
		}

		template<typename out_contained_type = value_type, bool OutContainsAlpha_ = contains_alpha>
		[[nodiscard]] constexpr inline EmuMath::Colour<out_contained_type, OutContainsAlpha_> Clamped() const
		{
			return EmuMath::Helpers::colour_clamp<EmuMath::Colour<out_contained_type, OutContainsAlpha_>, this_type>(*this);
		}
		template<bool OutContainsAlpha_>
		[[nodiscard]] constexpr inline EmuMath::Colour<value_type, OutContainsAlpha_> Clamped() const
		{
			return EmuMath::Helpers::colour_clamp<EmuMath::Colour<value_type, OutContainsAlpha_>, this_type>(*this);
		}
		inline void Clamp()
		{
			EmuMath::Helpers::colour_clamp<this_type, this_type>(*this, *this);
		}
#pragma endregion

		/// <summary> 
		/// <para> Underlying colour channels represented by this colour. </para>
		/// <para> If this colour DOES NOT contain an explicit Alpha channel: Stored in RGB order. </para>
		/// <para> If this colour DOES contain an explicit Alpha channel: Stored in RGBA order. </para>
		/// </summary>
		channels_vector channels;
	};

	/// <summary> Colour contains Red, Green, and Blue channels of the provided Channel_ type. Shorthand for EmuMath::Colour with a false boolean argument. </summary>
	template<typename Channel_>
	using ColourRGB = EmuMath::Colour<Channel_, false>;

	/// <summary> Colour contains Red, Green, Blue, and Alpha channels of the provided Channel_ type. Shorthand for EmuMath::Colour with a true boolean argument. </summary>
	template<typename Channel_>
	using ColourRGBA = EmuMath::Colour<Channel_, true>;
}

template<typename T_, bool ContainsAlpha_>
std::ostream& operator<<(std::ostream& str_, const EmuMath::Colour<T_, ContainsAlpha_>& colour_)
{
	str_ << colour_.channels;
	return str_;
}

template<typename T_, bool ContainsAlpha_>
std::wostream& operator<<(std::wostream& str_, const EmuMath::Colour<T_, ContainsAlpha_>& colour_)
{
	str_ << colour_.channels;
	return str_;
}

#endif
