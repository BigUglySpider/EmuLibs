#ifndef EMU_MATH_COLOUR_T_H_INC_
#define EMU_MATH_COLOUR_T_H_INC_ 1

#include "ColourHelpers.h"
#include "../../../EmuCore/Functors/Arithmetic.h"
#include "../../../EmuCore/TMPHelpers/TypeComparators.h"
#include "../../../EmuCore/TMPHelpers/Values.h"
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
		using vector_rgb_return_type = std::conditional_t<contains_alpha, EmuMath::Vector<3, value_type>, const channels_vector&>;
		using vector_rgba_return_type = std::conditional_t<contains_alpha, const channels_vector&, EmuMath::Vector<4, value_type>>;

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
			if constexpr (EmuCore::TMP::are_all_static_castable_v<value_type, R_, G_, B_>)
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
				static_assert(EmuCore::TMP::get_false<R_>(), "Attempted to make an EmuMath colour using at least one input channel argument that is not convertible to the colour's value type.");
			}
		}
		template<typename R_, typename G_, typename B_, typename A_>
		[[nodiscard]] static constexpr inline channels_vector _make_colour(R_&& r_, G_&& g_, B_&& b_, A_&& a_)
		{
			using check_type = std::conditional_t
			<
				contains_alpha,
				EmuCore::TMP::are_all_static_castable<value_type, R_, G_, B_, A_>,
				EmuCore::TMP::are_all_static_castable<value_type, R_, G_, B_>
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
				static_assert(EmuCore::TMP::get_false<R_>(), "Attempted to make an EmuMath colour using at least one input channel argument that is not convertible to the colour's value type.");
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
							EmuMath::Helpers::colour_convert_channel<value_type, RhsT_>(rhs_.channels.at<0>()),
							EmuMath::Helpers::colour_convert_channel<value_type, RhsT_>(rhs_.channels.at<1>()),
							EmuMath::Helpers::colour_convert_channel<value_type, RhsT_>(rhs_.channels.at<2>()),
							EmuMath::Helpers::colour_convert_channel<value_type, RhsT_>(rhs_.channels.at<3>())
						);
					}
					else
					{
						return channels_vector
						(
							EmuMath::Helpers::colour_convert_channel<value_type, RhsT_>(rhs_.channels.at<0>()),
							EmuMath::Helpers::colour_convert_channel<value_type, RhsT_>(rhs_.channels.at<1>()),
							EmuMath::Helpers::colour_convert_channel<value_type, RhsT_>(rhs_.channels.at<2>()),
							max_intensity
						);
					}
				}
				else
				{
					return channels_vector
					(
						EmuMath::Helpers::colour_convert_channel<value_type, RhsT_>(rhs_.channels.at<0>()),
						EmuMath::Helpers::colour_convert_channel<value_type, RhsT_>(rhs_.channels.at<1>()),
						EmuMath::Helpers::colour_convert_channel<value_type, RhsT_>(rhs_.channels.at<2>())
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
							EmuMath::Helpers::vector_get_theoretical<0>(channels_to_copy_),
							EmuMath::Helpers::vector_get_theoretical<1>(channels_to_copy_),
							EmuMath::Helpers::vector_get_theoretical<2>(channels_to_copy_),
							max_intensity
						);
					}
				}
				else
				{
					return channels_vector
					(
						EmuMath::Helpers::vector_get_theoretical<0>(channels_to_copy_),
						EmuMath::Helpers::vector_get_theoretical<1>(channels_to_copy_),
						EmuMath::Helpers::vector_get_theoretical<2>(channels_to_copy_)
					);
				}
			}
		}

	public:
		static constexpr channels_vector _default_colour = _make_default_colour();

#pragma region CONSTRUCTORS
		/// <summary>
		/// <para> Constructs a default colour with its main channel intensities set to their minimum. </para>
		/// <para> If this colour contains an alpha channel, that channel will be set to its maximum intensity. </para>
		/// </summary>
		constexpr Colour() : channels(_default_colour)
		{
		}
		/// <summary> Constructs a copy of the passed colour. </summary>
		/// <param name="to_copy_">Colour to copy.</param>
		constexpr Colour(const this_type& to_copy_) : channels(to_copy_.channels)
		{
		}
		/// <summary>
		/// <para> Constructs a copy of the passed colour. </para>
		/// <para> If this colour DOES NOT contain an explicit Alpha channel: the passed colour's Alpha channel will be ignored. </para>
		/// <para> If this colour DOES contain an explicit Alpha channel: this colour's Alpha channel will be initialised at max_intensity. </para>
		/// </summary>
		/// <param name="to_copy_">Colour to copy the Red, Green, and Blue channels of.</param>
		constexpr Colour(const EmuMath::Colour<value_type, !contains_alpha>& to_copy_) :
			channels
			(
				_make_colour
				(
					to_copy_.channels.at<0>(),
					to_copy_.channels.at<1>(),
					to_copy_.channels.at<2>()
				)
			)
		{
		}
		/// <summary> Move constructor to create a colour from moved colour data. </summary>
		/// <param name="to_move_">Colour to move the data of into the newly constructed colour.</param>
		constexpr Colour(this_type&& to_move_) noexcept : channels(std::move(to_move_.channels))
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
		explicit constexpr Colour(channels_vector&& channels_to_move_) noexcept : channels(channels_to_move_)
		{
		}
		/// <summary>
		/// <para> Constructs a copy of the passed colour, matching intensities in each respective channel. </para>
		/// <para> Performs any necessary conversions (e.g. converting 0:255 byte ranges to 0:1 floating-point ranges) to represent the same colour. </para>
		/// </summary>
		/// <typeparam name="CopyChannelType_">Type of channel contained in the passed colour to copy.</typeparam>
		/// <param name="to_copy_">Colour to copy to the newly constructed colour.</param>
		template
		<
			typename CopyChannelType_,
			bool RhsContainsAlpha_,
			typename = std::enable_if_t<!std::is_same_v<value_type, CopyChannelType_>>
		>
		explicit constexpr Colour(const EmuMath::Colour<CopyChannelType_, RhsContainsAlpha_>& to_copy_) :
			channels(_make_colour_from_arbitrary_other<CopyChannelType_, RhsContainsAlpha_>(to_copy_))
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
		template<typename R_, typename G_, typename B_, typename = std::enable_if_t<EmuCore::TMP::are_all_static_castable_v<value_type, R_, G_, B_>>>
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
			typename OnlyAvailableWith4Channels_ = std::enable_if_t<EmuCore::TMP::are_all_static_castable_v<value_type, R_, G_, B_, A_> && contains_alpha>
		>
		constexpr Colour(R_&& r_, G_&& g_, B_&& b_, A_&& a_) : channels(_make_colour(r_, g_, b_, a_))
		{
		}
		/// <summary>
		/// <para> Constructs a colour whichz copies the RGB channels of the passed colour, and initialises its Alpha channel as a custom provided value. </para>
		/// <para> This constructor is only available for colours which explicitly contain a modifiable Alpha channel. </para>
		/// </summary>
		/// <param name="to_copy_rgb_">Colour to copy the Red, Green, and Blue channels of.</param>
		/// <param name="a_">Value to initialise this colour's Alpha channel via.</param>
		template
		<
			typename ToCopyChannel_,
			bool ToCopyContainsAlpha_,
			typename A_,
			typename OnlyAvailableWith4Channels_ = std::enable_if_t<contains_alpha && EmuCore::TMP::are_all_static_castable_v<value_type, ToCopyChannel_, A_>>
		>
		constexpr Colour(const EmuMath::Colour<ToCopyChannel_, ToCopyContainsAlpha_>& to_copy_rgb_, A_&& a_) :
			channels
			(
				EmuMath::Helpers::colour_convert_channel<value_type, ToCopyChannel_>(to_copy_rgb_.at<0>()),
				EmuMath::Helpers::colour_convert_channel<value_type, ToCopyChannel_>(to_copy_rgb_.at<1>()),
				EmuMath::Helpers::colour_convert_channel<value_type, ToCopyChannel_>(to_copy_rgb_.at<2>()),
				static_cast<value_type>(a_)
			)
		{
		}
#pragma endregion

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
				static_assert(EmuCore::TMP::get_false<std::size_t, Index_>(), "Attempted to access an invalid channel index within an EmuMath Colour.");
			}
		}

		/// <summary> 
		/// <para> Retrieves a copy of the channel value at the provided index within this Colour's channels. </para>
		/// <para> If this Colour does not contain an explicit Alpha value, this cannot be used to acquire its implicit Alpha value. Use A() in such scenarios. </para>
		/// </summary>
		/// <returns>Copy of the channel value at the provided index within this Colour's channels.</returns>
		[[nodiscard]] constexpr inline value_type at(const std::size_t index_) const
		{
			return channels.at(index_);
		}
		[[nodiscard]] constexpr inline value_type operator[](const std::size_t index_) const
		{
			return channels[index_];
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
		template<typename R_, typename = std::enable_if_t<EmuCore::TMP::is_static_castable_v<R_, value_type>>>
		constexpr inline void R(R_&& r_)
		{
			channels.at<0>() = static_cast<value_type>(r_);
		}
		/// <summary> Sets this colour's Green channel to the passed value. </summary>
		/// <param name="g_">Value to set this colour's Green channel to. This will not be modified.</param>
		template<typename G_, typename = std::enable_if_t<EmuCore::TMP::is_static_castable_v<G_, value_type>>>
		constexpr inline void G(G_&& g_)
		{
			channels.at<1>() = static_cast<value_type>(g_);
		}
		/// <summary> Sets this colour's Blue channel to the passed value. </summary>
		/// <param name="b_">Value to set this colour's Blue channel to. This will not be modified.</param>
		template<typename B_, typename = std::enable_if_t<EmuCore::TMP::is_static_castable_v<B_, value_type>>>
		constexpr inline void B(B_&& b_)
		{
			channels.at<2>() = static_cast<value_type>(b_);
		}
		/// <summary> Sets this colour's Alpha channel to the passed value. Only available if this colour contains an explicit Alpha channel. </summary>
		/// <param name="a_">Value to set this colour's Alpha channel to. This will not be modified.</param>
		template<typename A_, typename MayOnlyModifyAlphaIfContained_ = std::enable_if_t<EmuCore::TMP::is_static_castable_v<A_, value_type> && contains_alpha>>
		constexpr inline void A(A_&& a_)
		{
			channels.at<3>() = static_cast<value_type>(a_);
		}

		/// <summary> Shorthand to set via the R, G, and B functions with the respective provided arguments. </summary>
		/// <param name="r_">Value to set this colour's Red channel to. This will not be modified.</param>
		/// <param name="g_">Value to set this colour's Green channel to. This will not be modified.</param>
		/// <param name="b_">Value to set this colour's Blue channel to. This will not be modified.</param>
		/// <returns>Reference to this colour.</returns>
		template<typename R_, typename G_, typename B_, typename = std::enable_if_t<EmuCore::TMP::are_all_static_castable_v<value_type, R_, G_, B_>>>
		constexpr inline this_type& Set(R_&& r_, G_&& g_, B_&& b_)
		{
			R(r_);
			G(g_);
			B(b_);
			return *this;
		}
		/// <summary> 
		///		Shorthand to set via the R, G, and B functions with the respective provided arguments. 
		///		May only provide Alpha if this colour contains an explicit Alpha channel. 
		/// </summary>
		/// <param name="r_">Value to set this colour's Red channel to. This will not be modified.</param>
		/// <param name="g_">Value to set this colour's Green channel to. This will not be modified.</param>
		/// <param name="b_">Value to set this colour's Blue channel to. This will not be modified.</param>
		/// <param name="a_">Value to set this colour's Alpha channel to. This will not be modified.</param>
		/// <returns>Reference to this colour.</returns>
		template
		<
			typename R_,
			typename G_,
			typename B_,
			typename A_,
			typename MayOnlyModifyAlphaIfContained_ = std::enable_if_t<EmuCore::TMP::are_all_static_castable_v<value_type, R_, G_, B_, A_> && contains_alpha>
		>
		constexpr inline this_type& Set(R_&& r_, G_&& g_, B_&& b_, A_&& a_)
		{
			R(r_);
			G(g_);
			B(b_);
			A(a_);
			return *this;
		}
#pragma endregion

#pragma region CONST_OPERATORS
		template<bool IncludeAlpha_, typename rhs_contained_type, bool RhsContainsAlpha_>
		[[nodiscard]] constexpr inline bool operator==(const EmuMath::Colour<rhs_contained_type, RhsContainsAlpha_>& rhs_) const
		{
			return EmuMath::Helpers::colour_cmp_equal<IncludeAlpha_>(*this, rhs_);
		}
		template<typename rhs_contained_type, bool RhsContainsAlpha_>
		[[nodiscard]] constexpr inline bool operator==(const EmuMath::Colour<rhs_contained_type, RhsContainsAlpha_>& rhs_) const
		{
			return EmuMath::Helpers::colour_cmp_equal<contains_alpha || RhsContainsAlpha_>(*this, rhs_);
		}

		template<bool IncludeAlpha_, typename rhs_contained_type, bool RhsContainsAlpha_>
		[[nodiscard]] constexpr inline bool operator!=(const EmuMath::Colour<rhs_contained_type, RhsContainsAlpha_>& rhs_) const
		{
			return EmuMath::Helpers::colour_cmp_not_equal<IncludeAlpha_>(*this, rhs_);
		}
		template<typename rhs_contained_type, bool RhsContainsAlpha_>
		[[nodiscard]] constexpr inline bool operator!=(const EmuMath::Colour<rhs_contained_type, RhsContainsAlpha_>& rhs_) const
		{
			return EmuMath::Helpers::colour_cmp_not_equal<contains_alpha || RhsContainsAlpha_>(*this, rhs_);
		}

		template<bool IncludeAlpha_ = contains_alpha, class Rhs_>
		[[nodiscard]] constexpr inline this_type operator+(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::colour_add<this_type, IncludeAlpha_, this_type, Rhs_>(*this, rhs_);
		}

		template<bool IncludeAlpha_ = contains_alpha, class Rhs_>
		[[nodiscard]] constexpr inline this_type operator-(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::colour_subtract<this_type, IncludeAlpha_, this_type, Rhs_>(*this, rhs_);
		}

		template<bool IncludeAlpha_ = contains_alpha, class Rhs_>
		[[nodiscard]] constexpr inline this_type operator*(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::colour_multiply<this_type, IncludeAlpha_, this_type, Rhs_>(*this, rhs_);
		}

		template<bool IncludeAlpha_ = contains_alpha, class Rhs_>
		[[nodiscard]] constexpr inline this_type operator/(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::colour_divide<this_type, IncludeAlpha_, this_type, Rhs_>(*this, rhs_);
		}

		template<bool IncludeAlpha_ = contains_alpha, class Rhs_>
		[[nodiscard]] constexpr inline this_type operator%(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::colour_mod<this_type, IncludeAlpha_, this_type, Rhs_>(*this, rhs_);
		}
#pragma endregion

#pragma region NON_CONST_OPERATORS
		constexpr inline this_type& operator=(const this_type& rhs_)
		{
			channels = rhs_.channels;
			return *this;
		}
		constexpr inline this_type& operator=(this_type&& rhs_) noexcept
		{
			channels = std::move(rhs_.channels);
			return *this;
		}
		constexpr inline this_type& operator=(const EmuMath::Colour<value_type, !contains_alpha>& rhs_)
		{
			_set_channels_from_other_channels_vector(rhs_.channels);
			return *this;
		}

		template<bool IncludeAlpha_ = contains_alpha, class Rhs_>
		constexpr inline this_type& operator+=(const Rhs_& rhs_)
		{
			return this->operator=(EmuMath::Helpers::colour_add<this_type, IncludeAlpha_, this_type, Rhs_>(*this, rhs_));
		}

		template<bool IncludeAlpha_ = contains_alpha, class Rhs_>
		constexpr inline this_type& operator-=(const Rhs_& rhs_)
		{
			return this->operator=(EmuMath::Helpers::colour_subtract<this_type, IncludeAlpha_, this_type, Rhs_>(*this, rhs_));
		}

		template<bool IncludeAlpha_ = contains_alpha, class Rhs_>
		constexpr inline this_type& operator*=(const Rhs_& rhs_)
		{
			return this->operator=(EmuMath::Helpers::colour_multiply<this_type, IncludeAlpha_, this_type, Rhs_>(*this, rhs_));
		}

		template<bool IncludeAlpha_ = contains_alpha, class Rhs_>
		constexpr inline this_type& operator/=(const Rhs_& rhs_)
		{
			return this->operator=(EmuMath::Helpers::colour_divide<this_type, IncludeAlpha_, this_type, Rhs_>(*this, rhs_));
		}

		template<bool IncludeAlpha_ = contains_alpha, class Rhs_>
		constexpr inline this_type& operator%=(const Rhs_& rhs_)
		{
			return this->operator=(EmuMath::Helpers::colour_mod<this_type, IncludeAlpha_, this_type, Rhs_>(*this, rhs_));
		}
#pragma endregion

#pragma region ARITHMETIC_FUNCTIONS
		/// <summary>
		/// <para> Returns a copy of this colour with the provided rhs_ added to it. </para>
		/// <para> If rhs_ is an EmuMath Colour: the amount added will be based on the colour's intensity translation, rather than the raw stored values. </para>
		/// <para> If rhs_ is an EmuMath Vector: elements in the vector will be added to the output colour's respective channels. </para>
		/// <para> If rhs_ is none of the above: rhs_ will be added directly to each of the output colour's channels. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type used to store the output colour's channels. Defaults to this Colour's value_type./</typeparam>
		/// <typeparam name="Rhs_">Type of item to add to this colour.</typeparam>
		/// <param name="rhs_">Item to add to this colour as described above.</param>
		/// <returns>Copy of this colour with the provided rhs_ added to it.</returns>
		template<typename out_contained_type = value_type, bool OutContainsAlpha_ = contains_alpha, bool IncludeAlpha_ = OutContainsAlpha_, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Colour<out_contained_type, OutContainsAlpha_> Add(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::colour_add<EmuMath::Colour<out_contained_type, OutContainsAlpha_>, IncludeAlpha_, this_type, Rhs_>(*this, rhs_);
		}
		template<bool OutContainsAlpha_, bool IncludeAlpha_ = OutContainsAlpha_, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Colour<value_type, OutContainsAlpha_> Add(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::colour_add<EmuMath::Colour<value_type, OutContainsAlpha_>, IncludeAlpha_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Returns a copy of this colour with the provided rhs_ subtracted it. </para>
		/// <para> If rhs_ is an EmuMath Colour: the amount subtracted will be based on the colour's intensity translation, rather than the raw stored values. </para>
		/// <para> If rhs_ is an EmuMath Vector: elements in the vector will be subtracted from the output colour's respective channels. </para>
		/// <para> If rhs_ is none of the above: rhs_ will be subtracted directly from each of the output colour's channels. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type used to store the output colour's channels. Defaults to this Colour's value_type./</typeparam>
		/// <typeparam name="Rhs_">Type of item to subtract from this colour.</typeparam>
		/// <param name="rhs_">Item to subtract from this colour as described above.</param>
		/// <returns>Copy of this colour with the provided rhs_ subtracted from it.</returns>
		template<typename out_contained_type = value_type, bool OutContainsAlpha_ = contains_alpha, bool IncludeAlpha_ = OutContainsAlpha_, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Colour<out_contained_type, OutContainsAlpha_> Subtract(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::colour_subtract<EmuMath::Colour<out_contained_type, OutContainsAlpha_>, IncludeAlpha_, this_type, Rhs_>(*this, rhs_);
		}
		template<bool OutContainsAlpha_, bool IncludeAlpha_ = OutContainsAlpha_, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Colour<value_type, OutContainsAlpha_> Subtract(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::colour_subtract<EmuMath::Colour<value_type, OutContainsAlpha_>, IncludeAlpha_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Returns a copy of this colour multiplied by the provided rhs_. </para>
		/// <para> If rhs_ is an EmuMath Colour: the amount multiplied will be based on the colour's intensity translation, rather than the raw stored values. </para>
		/// <para> 
		///		If rhs_ is an EmuMath Vector: elements in the vector will be used as multipliers for the output colour's respective channels. 
		///		Non-contained elements will be interpreted as 1, and will make no changes to respective channels.
		/// </para>
		/// <para> If rhs_ is none of the above: rhs_ will be used as a multiplier directly for each of the output colour's channels. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type used to store the output colour's channels. Defaults to this Colour's value_type./</typeparam>
		/// <typeparam name="Rhs_">Type of item to multiply this colour by.</typeparam>
		/// <param name="rhs_">Item to multiply this colour by as described above.</param>
		/// <returns>Copy of this colour multiplied by the provided rhs_.</returns>
		template<typename out_contained_type = value_type, bool OutContainsAlpha_ = contains_alpha, bool IncludeAlpha_ = OutContainsAlpha_, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Colour<out_contained_type, OutContainsAlpha_> Multiply(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::colour_multiply<EmuMath::Colour<out_contained_type, OutContainsAlpha_>, IncludeAlpha_, this_type, Rhs_>(*this, rhs_);
		}
		template<bool OutContainsAlpha_, bool IncludeAlpha_ = OutContainsAlpha_, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Colour<value_type, OutContainsAlpha_> Multiply(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::colour_multiply<EmuMath::Colour<value_type, OutContainsAlpha_>, IncludeAlpha_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Returns a copy of this colour divided by the provided rhs_. </para>
		/// <para> If rhs_ is an EmuMath Colour: the amount divided will be based on the colour's intensity translation, rather than the raw stored values. </para>
		/// <para> 
		///		If rhs_ is an EmuMath Vector: elements in the vector will be used as divisors for the output colour's respective channels. 
		///		Non-contained elements will be interpreted as 1, and will make no changes to respective channels.
		/// </para>
		/// <para> If rhs_ is none of the above: rhs_ will be used as a divisor directly for each of the output colour's channels. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type used to store the output colour's channels. Defaults to this Colour's value_type./</typeparam>
		/// <typeparam name="Rhs_">Type of item to divide this colour by.</typeparam>
		/// <param name="rhs_">Item to divide this colour by as described above.</param>
		/// <returns>Copy of this colour divided by the provided rhs_.</returns>
		template<typename out_contained_type = value_type, bool OutContainsAlpha_ = contains_alpha, bool IncludeAlpha_ = OutContainsAlpha_, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Colour<out_contained_type, OutContainsAlpha_> Divide(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::colour_divide<EmuMath::Colour<out_contained_type, OutContainsAlpha_>, IncludeAlpha_, this_type, Rhs_>(*this, rhs_);
		}
		template<bool OutContainsAlpha_, bool IncludeAlpha_ = OutContainsAlpha_, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Colour<value_type, OutContainsAlpha_> Divide(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::colour_divide<EmuMath::Colour<value_type, OutContainsAlpha_>, IncludeAlpha_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Returns a copy of this colour resulting from a modulo division by the provided rhs_. </para>
		/// <para> If rhs_ is an EmuMath Colour: the amount divided will be based on the colour's intensity translation, rather than the raw stored values. </para>
		/// <para> 
		///		If rhs_ is an EmuMath Vector: elements in the vector will be used as divisors for the output colour's respective channels. 
		///		Non-contained elements will be interpreted as 1, and will make no changes to respective channels.
		/// </para>
		/// <para> If rhs_ is none of the above: rhs_ will be used as a divisor directly for each of the output colour's channels. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type used to store the output colour's channels. Defaults to this Colour's value_type./</typeparam>
		/// <typeparam name="Rhs_">Type of item to divide this colour by.</typeparam>
		/// <param name="rhs_">Item to divide this colour by as described above.</param>
		/// <returns>Copy of this colour resulting from a modulo division by the provided rhs_.</returns>
		template<typename out_contained_type = value_type, bool OutContainsAlpha_ = contains_alpha, bool IncludeAlpha_ = OutContainsAlpha_, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Colour<out_contained_type, OutContainsAlpha_> Mod(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::colour_mod<EmuMath::Colour<out_contained_type, OutContainsAlpha_>, IncludeAlpha_, this_type, Rhs_>(*this, rhs_);
		}
		template<bool OutContainsAlpha_, bool IncludeAlpha_ = OutContainsAlpha_, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Colour<value_type, OutContainsAlpha_> Mod(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::colour_mod<EmuMath::Colour<value_type, OutContainsAlpha_>, IncludeAlpha_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Linearly interpolates this colour (a) with the passed colour, b_, using the provided t_ as weightings for each channel's interpolation. </para>
		/// <para> If t_ is an EmuMath Colour: the value of t_ will be based on the colour's intensity translation, rather than the raw stored values. </para>
		/// <para> If t_ is an EmuMath Vector: elements in the vector will be used as weightings for the the interpolation of respective channels in each colour. </para>
		/// <para> If t_ is none of the above: t_ will be used directly as the weighting for all linear interpolations. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type used to store the output colour's channels. Defaults to this Colour's value_type./</typeparam>
		/// <typeparam name="ColourB_">Type of EmuMath Colour appearing as b in linear interpolation.</typeparam>
		/// <typeparam name="T_">Type used to provide weighting(s) for linear interpolations.</typeparam>
		/// <param name="b_">EmuMath Colour appearing as b in the equation `a + ((b - a) * t)`.</param>
		/// <param name="t_">Weightings appearing as t in the equation `a + ((b - a) * t), used as described above.</param>
		/// <returns>Copy of this colour linearly interpolated with the provided colour and weightings, resulting from the equation `a + ((b - a) * t)`.</returns>
		template<typename out_contained_type = value_type, bool OutContainsAlpha_ = contains_alpha, bool IncludeAlpha_ = OutContainsAlpha_, class ColourB_, class T_>
		[[nodiscard]] constexpr inline EmuMath::Colour<out_contained_type, OutContainsAlpha_> Lerp(const ColourB_& b_, const T_& t_) const
		{
			return EmuMath::Helpers::colour_lerp<EmuMath::Colour<out_contained_type, OutContainsAlpha_>, IncludeAlpha_, this_type, ColourB_, T_>(*this, b_, t_);
		}
		template<bool OutContainsAlpha_, bool IncludeAlpha_ = OutContainsAlpha_, class ColourB_, class T_>
		[[nodiscard]] constexpr inline EmuMath::Colour<value_type, OutContainsAlpha_> Lerp(const ColourB_& b_, const T_& t_) const
		{
			return EmuMath::Helpers::colour_lerp<EmuMath::Colour<value_type, OutContainsAlpha_>, IncludeAlpha_, this_type, ColourB_, T_>(*this, b_, t_);
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

		/// <summary> Provides read-only access to this Colour's channels as an EmuMath Vector. </summary>
		/// <returns> Constant reference to this colour's underlying channels. </returns>
		[[nodiscard]] constexpr inline const channels_vector& AsVector() const
		{
			return channels;
		}

		/// <summary> Provides read-only access to this Colour's RGB channels as an EmuMath Vector. </summary>
		/// <returns> EmuMath Vector representation of this colour's underlying channels in RGB format. </returns>
		[[nodiscard]] constexpr inline vector_rgb_return_type AsVectorRGB() const
		{
			if constexpr (contains_alpha)
			{
				return vector_rgb_return_type(channels.at<0>(), channels.at<1>(), channels.at<2>());
			}
			else
			{
				return channels;
			}
		}

		/// <summary> Provides read-only access to this Colour's RGBA channels as an EmuMath Vector. </summary>
		/// <returns> EmuMath Vector representation of this colour's underlying channels in RGBA format. </returns>
		[[nodiscard]] constexpr inline vector_rgba_return_type AsVectorRGBA() const
		{
			if constexpr (contains_alpha)
			{
				return channels;
			}
			else
			{
				return vector_rgba_return_type(channels.at<0>(), channels.at<1>(), channels.at<2>(), max_intensity);
			}
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
		constexpr inline void Invert()
		{
			EmuMath::Helpers::colour_invert<IncludeAlpha_, this_type>(*this, *this);
		}

		/// <summary> Returns a copy of this colour with all of its channels wrapped into a valid range. </summary>
		/// <typeparam name="out_contained_type">Type used to store the output colour's channels. Defaults to this Colour's value_type./</typeparam>
		/// <returns>Copy of this colour with all channels wrapped into a valid intensity range.</returns>
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

		/// <summary> Wraps the stored channels within this colour instance so they are in a valid intensity range. </summary>
		constexpr inline void Wrap()
		{
			EmuMath::Helpers::colour_wrap<this_type, this_type>(*this, *this);
		}

		/// <summary> Returns a copy of this colour with all of its channels clamped into the range min_intensity:max_intensity. </summary>
		/// <typeparam name="out_contained_type">Type used to store the output colour's channels. Defaults to this Colour's value_type./</typeparam>
		/// <returns>Copy of this colour with all channels clamped into a valid intensity range.</returns>
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

		/// <summary> Clamps the stored channels within this colour instance into the range min_intensity:max_intensity. </summary>
		constexpr inline void Clamp()
		{
			EmuMath::Helpers::colour_clamp<this_type, this_type>(*this, *this);
		}

		/// <summary> Finds the lowest-valued channel within this Colour. Excludes Alpha by default, but may include it if provided a `true` template argument. </summary>
		/// <returns>Copy of the highest value stored within this Colour's channels.</returns>
		template<bool IncludeAlpha_ = false>
		[[nodiscard]] constexpr inline value_type Min() const
		{
			return EmuMath::Helpers::colour_min<value_type, IncludeAlpha_, this_type>(*this);
		}

		/// <summary> Finds the highest-valued channel within this Colour. Excludes Alpha by default, but may include it if provided a `true` template argument. </summary>
		/// <returns>Copy of the highest value stored within this Colour's channels.</returns>
		template<bool IncludeAlpha_ = false>
		[[nodiscard]] constexpr inline value_type Max() const
		{
			return EmuMath::Helpers::colour_max<value_type, IncludeAlpha_, this_type>(*this);
		}

		/// <summary> Returns a copy of this colour converted to greyscale using a basic average of its RGB channels. </summary>
		/// <returns>Copy of this channel with each channel set to the mean average of this colour's RGB channels.</returns>
		template<typename out_contained_type = value_type, bool OutContainsAlpha_ = contains_alpha>
		[[nodiscard]] constexpr inline EmuMath::Colour<out_contained_type, OutContainsAlpha_> GreyscaleBasic() const
		{
			return EmuMath::Helpers::colour_greyscale_basic_average<EmuMath::Colour<out_contained_type, OutContainsAlpha_>, this_type>(*this);
		}
		template<bool OutContainsAlpha_>
		[[nodiscard]] constexpr inline EmuMath::Colour<value_type, OutContainsAlpha_> GreyscaleBasic() const
		{
			return EmuMath::Helpers::colour_greyscale_basic_average<EmuMath::Colour<value_type, OutContainsAlpha_>, this_type>(*this);
		}

		/// <summary> Returns a copy of this colour converted to greyscale using a luminance average of its RGB channels. </summary>
		/// <returns>Copy of this channel with each channel set to a scaled luminance average of this colour's RGB channels.</returns>
		template<typename out_contained_type = value_type, bool OutContainsAlpha_ = contains_alpha>
		[[nodiscard]] constexpr inline EmuMath::Colour<out_contained_type, OutContainsAlpha_> GreyscaleLuminance() const
		{
			return EmuMath::Helpers::colour_greyscale_luminance_average<EmuMath::Colour<out_contained_type, OutContainsAlpha_>, this_type>(*this);
		}
		template<bool OutContainsAlpha_>
		[[nodiscard]] constexpr inline EmuMath::Colour<value_type, OutContainsAlpha_> GreyscaleLuminance() const
		{
			return EmuMath::Helpers::colour_greyscale_luminance_average<EmuMath::Colour<value_type, OutContainsAlpha_>, this_type>(*this);
		}

		/// <summary> Returns a copy of this colour converted to greyscale via desaturation. </summary>
		/// <returns>Copy of this channel with each channel set to a value resulting from desaturating this colour's RGB channels.</returns>
		template<typename out_contained_type = value_type, bool OutContainsAlpha_ = contains_alpha>
		[[nodiscard]] constexpr inline EmuMath::Colour<out_contained_type, OutContainsAlpha_> GreyscaleDesaturate() const
		{
			return EmuMath::Helpers::colour_greyscale_desaturate<EmuMath::Colour<out_contained_type, OutContainsAlpha_>, this_type>(*this);
		}
		template<bool OutContainsAlpha_>
		[[nodiscard]] constexpr inline EmuMath::Colour<value_type, OutContainsAlpha_> GreyscaleDesaturate() const
		{
			return EmuMath::Helpers::colour_greyscale_desaturate<EmuMath::Colour<value_type, OutContainsAlpha_>, this_type>(*this);
		}

		/// <summary> Returns a copy of this colour converted to greyscale via its lowest RGB channel. </summary>
		/// <returns>Copy of this channel with each channel set to the value of this colour's lowest RGB channel.</returns>
		template<typename out_contained_type = value_type, bool OutContainsAlpha_ = contains_alpha>
		[[nodiscard]] constexpr inline EmuMath::Colour<out_contained_type, OutContainsAlpha_> GreyscaleMin() const
		{
			return EmuMath::Helpers::colour_greyscale_decompose_min<EmuMath::Colour<out_contained_type, OutContainsAlpha_>, this_type>(*this);
		}
		template<bool OutContainsAlpha_>
		[[nodiscard]] constexpr inline EmuMath::Colour<value_type, OutContainsAlpha_> GreyscaleMin() const
		{
			return EmuMath::Helpers::colour_greyscale_decompose_min<EmuMath::Colour<value_type, OutContainsAlpha_>, this_type>(*this);
		}

		/// <summary> Returns a copy of this colour converted to greyscale via its highest RGB channel. </summary>
		/// <returns>Copy of this channel with each channel set to the value of this colour's highest RGB channel.</returns>
		template<typename out_contained_type = value_type, bool OutContainsAlpha_ = contains_alpha>
		[[nodiscard]] constexpr inline EmuMath::Colour<out_contained_type, OutContainsAlpha_> GreyscaleMax() const
		{
			return EmuMath::Helpers::colour_greyscale_decompose_max<EmuMath::Colour<out_contained_type, OutContainsAlpha_>, this_type>(*this);
		}
		template<bool OutContainsAlpha_>
		[[nodiscard]] constexpr inline EmuMath::Colour<value_type, OutContainsAlpha_> GreyscaleMax() const
		{
			return EmuMath::Helpers::colour_greyscale_decompose_max<EmuMath::Colour<value_type, OutContainsAlpha_>, this_type>(*this);
		}
#pragma endregion

		/// <summary> 
		/// <para> Underlying colour channels represented by this colour. </para>
		/// <para> If this colour DOES NOT contain an explicit Alpha channel: Stored in RGB order. </para>
		/// <para> If this colour DOES contain an explicit Alpha channel: Stored in RGBA order. </para>
		/// <para> 
		///		This is not guaranteed to be available, as per the EmuMath Colour contract, 
		///		and must not be referred to in templates for EmuMath colour interactions. 
		/// </para>
		/// </summary>
		channels_vector channels;

	private:
		inline void _set_channels_from_other_channels_vector(const typename EmuMath::Colour<value_type, !contains_alpha>::channels_vector& to_copy_)
		{
			channels.at<0>() = to_copy_.template at<0>();
			channels.at<1>() = to_copy_.template at<1>();
			channels.at<2>() = to_copy_.template at<2>();
		}
	};

	/// <summary> Colour containing Red, Green, and Blue channels of the provided Channel_ type. Shorthand for EmuMath::Colour with a false boolean argument. </summary>
	template<typename Channel_>
	using ColourRGB = EmuMath::Colour<Channel_, false>;

	/// <summary> Colour containing Red, Green, Blue, and Alpha channels of the provided Channel_ type. Shorthand for EmuMath::Colour with a true boolean argument. </summary>
	template<typename Channel_>
	using ColourRGBA = EmuMath::Colour<Channel_, true>;
}

template<typename T_, bool ContainsAlpha_>
std::ostream& operator<<(std::ostream& str_, const EmuMath::Colour<T_, ContainsAlpha_>& colour_)
{
	using unqualified_channel_type = std::remove_reference_t<std::remove_cv_t<T_>>;
	str_ << "{ ";
	if constexpr (EmuCore::TMP::is_any_same_v<unqualified_channel_type, std::uint8_t, std::int8_t>)
	{
		str_ << (+colour_.R()) << ", " << (+colour_.G()) << ", " << (+colour_.B());
		if constexpr (ContainsAlpha_)
		{
			str_ << ", " << (+colour_.A());
		}
	}
	else
	{
		str_ << colour_.R() << ", " << colour_.G() << ", " << colour_.B();
		if constexpr (ContainsAlpha_)
		{
			str_ << ", " << colour_.A();
		}
	}
	str_ << " }";
	return str_;
}

template<typename T_, bool ContainsAlpha_>
std::wostream& operator<<(std::wostream& str_, const EmuMath::Colour<T_, ContainsAlpha_>& colour_)
{
	using unqualified_channel_type = std::remove_reference_t<std::remove_cv_t<T_>>;
	str_ << L"{ ";
	if constexpr (EmuCore::TMP::is_any_same_v<unqualified_channel_type, std::uint8_t, std::int8_t>)
	{
		str_ << (+colour_.R()) << L", " << (+colour_.G()) << L", " << (+colour_.B());
		if constexpr (ContainsAlpha_)
		{
			str_ << L", " << (+colour_.A());
		}
	}
	else
	{
		str_ << colour_.R() << L", " << colour_.G() << L", " << colour_.B();
		if constexpr (ContainsAlpha_)
		{
			str_ << L", " << colour_.A();
		}
	}
	str_ << L" }";
	return str_;
}

#endif
