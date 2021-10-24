#ifndef EMU_MATH_GRADIENT_H_INC_
#define EMU_MATH_GRADIENT_H_INC_ 1

#include "ColourT.h"
#include "ColourArithmeticFunctors.h"
#include "ColourComparisonFunctors.h"
#include <algorithm>
#include <map>
#include <ostream>

namespace EmuMath
{
	template<class Channel_>
	class Gradient
	{
	public:
		using channel_type = Channel_;
		using colour_type = EmuMath::ColourRGB<channel_type>;
		using anchor_type = float;
		using colour_map = std::map<anchor_type, colour_type>;
		using alpha_map = std::map<anchor_type, channel_type>;

#pragma region PUBLIC_STATIC_HELPERS
		/// <summary> The smallest valid value for an anchor within this gradient. </summary>
		static constexpr anchor_type min_anchor = anchor_type(0);
		/// <summary> The greatest valid value for an anchor within this gradient. </summary>
		static constexpr anchor_type max_anchor = anchor_type(1);

		/// <summary> Static helper used to wrap an anchor value for this gradient into a valid 0:1 range. </summary>
		[[nodiscard]] static constexpr inline anchor_type clamp_anchor(const anchor_type anchor_)
		{
			return (anchor_ <= min_anchor) ? min_anchor : (anchor_ >= max_anchor) ? max_anchor : anchor_;
		}

		/// <summary> Static helper used to clamp an alpha value for this gradient's channel type into a valid min_intensity:max_intensity range. </summary>
		[[nodiscard]] static constexpr inline channel_type clamp_alpha(const channel_type alpha_)
		{
			return EmuMath::Helpers::clamp_colour_channel<channel_type, channel_type>(alpha_);
		}

		/// <summary> Static helper used to wrap an anchor value for this gradient into a valid 0:1 range. </summary>
		[[nodiscard]] static constexpr inline anchor_type wrap_anchor(anchor_type anchor_)
		{
			// We know we're wrapping a 0:1 range, so just defer to this.
			return EmuCore::do_normalised_wrap<anchor_type, true>()(anchor_);
		}

		/// <summary> Static helper used to wrap an alpha value for this gradient's channel type into a valid min_intensity:max_intensity range. </summary>
		[[nodiscard]] static constexpr inline channel_type wrap_alpha(const channel_type alpha_)
		{
			return EmuMath::Helpers::wrap_colour_channel<channel_type, channel_type>(alpha_);
		}
#pragma endregion

#pragma region CONSTRUCTORS
		/// <summary> Constructs a gradient with only the default colour and maximum alpha intensity stored. </summary>
		Gradient() : colours(_make_empty_colours()), alphas(_make_empty_alphas())
		{
		}
		/// <summary> Constructs a copy of the passed gradient. </summary>
		/// <param name="to_copy_">Gradient to copy the colours and alphas of.</param>
		inline Gradient(const Gradient<Channel_>& to_copy_) : colours(to_copy_.colours), alphas(to_copy_.alphas)
		{
			// Validity check in case an invalid gradient was copied
			ForceValidation();
		}
		/// <summary> Constructs this gradient by moving the data of the passed gradient into its own data. </summary>
		/// <param name="to_move_">Gradient to move the data of.</param>
		inline Gradient(Gradient<Channel_>&& to_move_) : colours(std::move(to_move_.colours)), alphas(std::move(to_move_.alphas))
		{
			// Validity check in case an invalid gradient was moved
			ForceValidation();
		}
		/// <summary>
		/// <para> Constructs a copy of the passed gradient of a differing channel_type. </para>
		/// <para> The passed gradient's channel intensity values will be converted to this gradient's channel intensity values. </para>
		/// </summary>
		/// <param name="to_copy_">Gradient to copy the colours and alphas of; necessary channel conversions will be performed by the constructor.</param>
		template<class OtherChannel_, typename = std::enable_if_t<std::is_convertible_v<OtherChannel_, channel_type> && !std::is_same_v<OtherChannel_, channel_type>>>
		inline Gradient(const Gradient<OtherChannel_>& to_copy_) : colours(), alphas()
		{
			_copy_gradient(to_copy_);
		}
#pragma endregion

#pragma region CONST_OPERATORS
		/// <summary>
		/// <para> Shorthand for `GetColour` with the same argument(s). </para>
		/// <para> Returns an EmuMath Colour, formed from the provided anchor_point_ within this gradient's colour map. </para>
		/// <para> The colour's channels value will be converted to suit the output type if necessary. </para>
		/// <para> 
		///		If the output colour contains alpha (defaults to no alpha), it will be that colour's default value for its alpha channel. 
		///		To output a colour formed from an anchor point on both the colour and alpha maps of this gradient, use `Get`.
		/// </para>
		/// <para> The provided anchor point will be clamped into a valid 0:1 range. </para>
		/// </summary>
		/// <typeparam name="OutChannel_">
		///		Type of channel to be contained in the output colour. Conversions are automatically performed. Defaults to this gradient's channel_type.
		/// </typeparam>
		/// <param name="anchor_point_">Anchor point within this gradient to form the output colour via.</param>
		/// <returns>EmuMath Colour formed by the provided anchor point within this gradient's colour map, with a valid conversion if needed.</returns>
		template<class OutChannel_ = channel_type, bool OutContainsAlpha_ = false>
		[[nodiscard]] inline EmuMath::Colour<OutChannel_, OutContainsAlpha_> operator[](anchor_type anchor_point_) const
		{
			return GetColour<OutChannel_, OutContainsAlpha_>(anchor_point_);
		}
		template<bool OutContainsAlpha_>
		[[nodiscard]] inline EmuMath::Colour<channel_type, OutContainsAlpha_> operator[](anchor_type anchor_point_) const
		{
			return GetColour<OutContainsAlpha_>(anchor_point_);
		}

		/// <summary>
		/// <para> Shorthand for `Get` with the same argument(s). </para>
		/// <para> Returns a colour containing RGBA values, formed from the provided anchor_point_ in both the colour and alpha maps. </para>
		/// <para> May alternatively provide two anchor points for the colour and alpha anchors respectively. </para>
		/// <para> The provided anchor point(s) will be clamped into a valid 0:1 range. </para>
		/// </summary>
		/// <typeparam name="OutChannel_">
		///		Type of channel to be contained in the output colour. Conversions are automatically performed. Defaults to this gradient's channel_type.
		/// </typeparam>
		/// <param name="anchor_point_">Anchor point within this gradient to form the colour via. May provide a separate anchor point for the alpha value.</param>
		/// <returns>EmuMath Colour containing RGBA values determined by the provided anchor point(s) within this gradient, with channel conversions if needed.</returns>
		template<class OutChannel_ = channel_type>
		[[nodiscard]] inline EmuMath::ColourRGBA<OutChannel_> operator()(anchor_type anchor_point_) const
		{
			return Get<OutChannel_>(anchor_point_);
		}
		template<class OutChannel_ = channel_type>
		[[nodiscard]] inline EmuMath::ColourRGBA<OutChannel_> operator()(anchor_type colour_anchor_point_, anchor_type alpha_anchor_point_) const
		{
			return Get<OutChannel_>(colour_anchor_point_, alpha_anchor_point_);
		}

		/// <summary>
		/// <para> Returns a boolean indicating if this gradient contains equal anchors for colours and alphas compared to the passed gradient. </para>
		/// <para> Channel conversions are performed where necessary. </para>
		/// <para> Note that channel conversions are lossy when switching between floating-point and integral channel types. </para>
		/// </summary>
		/// <param name="rhs_">Gradient to compare this gradient to.</param>
		/// <returns>True if all of this gradient's anchor points match up with the provided rhs_ gradient; otherwise false.</returns>
		template<class RhsChannel_>
		[[nodiscard]] inline bool operator==(const EmuMath::Gradient<RhsChannel_>& rhs_) const
		{
			return _do_cmp_equal(rhs_);
		}

		/// <summary>
		/// <para> Returns a boolean indicating if this gradient contains different anchors for colours and alphas compared to the passed gradient. </para>
		/// <para> Channel conversions are performed where necessary. </para>
		/// <para> Note that channel conversions are lossy when switching between floating-point and integral channel types. </para>
		/// </summary>
		/// <param name="rhs_">Gradient to compare this gradient to.</param>
		/// <returns>True if at least one of this gradient's anchor points do not match up with the provided rhs_ gradient; otherwise false.</returns>
		template<class RhsChannel_>
		[[nodiscard]] inline bool operator!=(const EmuMath::Gradient<RhsChannel_>& rhs_) const
		{
			return !_do_cmp_equal(rhs_);
		}
#pragma endregion

#pragma region NON_CONST_OPERATORS
		inline Gradient<channel_type>& operator=(Gradient<channel_type>&& to_move_)
		{
			colours = std::move(to_move_.colours);
			alphas = std::move(to_move_.alphas);
			// Validity check in case an invalid gradient was moved
			ForceValidation();
			return *this;
		}

		template<class OtherChannel_, typename = std::enable_if_t<std::is_convertible_v<OtherChannel_, channel_type> || std::is_same_v<OtherChannel_, channel_type>>>
		inline Gradient<channel_type>& operator=(const EmuMath::Gradient<OtherChannel_>& to_copy_)
		{
			_copy_gradient(to_copy_);
			return *this;
		}
#pragma endregion

#pragma region COMPARISON_FUNCS
		/// <summary>
		/// <para> Returns a boolean indicating if this gradient contains equal anchors for colours and alphas compared to the passed gradient. </para>
		/// <para> Channel conversions are performed where necessary. </para>
		/// <para> Note that channel conversions are lossy when switching between floating-point and integral channel types. </para>
		/// </summary>
		/// <param name="rhs_">Gradient to compare this gradient to.</param>
		/// <returns>True if all of this gradient's anchor points match up with the provided rhs_ gradient; otherwise false.</returns>
		template<class RhsChannel_>
		[[nodiscard]] inline bool HasMatchingAnchors(const EmuMath::Gradient<RhsChannel_>& rhs_) const
		{
			return _do_cmp_equal(rhs_);
		}

		/// <summary>
		/// <para> Returns a boolean indicating if this gradient contains equal anchors for colours compared to the passed gradient. </para>
		/// <para> Channel conversions are performed where necessary. </para>
		/// <para> Note that channel conversions are lossy when switching between floating-point and integral channel types. </para>
		/// </summary>
		/// <param name="rhs_">Gradient to compare this gradient to.</param>
		/// <returns>True if all of this gradient's colour anchor points match up with the provided rhs_ gradient; otherwise false.</returns>
		template<class RhsChannel_>
		[[nodiscard]] inline bool HasMatchingColourAnchors(const EmuMath::Gradient<RhsChannel_>& rhs_) const
		{
			return _do_single_container_cmp_equal
			(
				colours,
				rhs_.ViewColours(),
				[](const auto& a_, const auto& b_) 
				{ 
					return 
					(
						(a_.first == b_.first) && 
						(a_.second == b_.second)
					);
				}
			);
		}

		/// <summary>
		/// <para> Returns a boolean indicating if this gradient contains equal anchors for alpha compared to the passed gradient. </para>
		/// <para> Channel conversions are performed where necessary. </para>
		/// <para> Note that channel conversions are lossy when switching between floating-point and integral channel types. </para>
		/// </summary>
		/// <param name="rhs_">Gradient to compare this gradient to.</param>
		/// <returns>True if all of this gradient's alpha anchor points match up with the provided rhs_ gradient; otherwise false.</returns>
		template<class RhsChannel_>
		[[nodiscard]] inline bool HasMatchingAlphaAnchors(const EmuMath::Gradient<RhsChannel_>& rhs_) const
		{
			return _do_single_container_cmp_equal
			(
				alphas,
				rhs_.ViewAlphas(),
				[](const auto& a_, const auto& b_)
				{
					return 
					(
						(a_.first == b_.first) &&
						(a_.second == EmuMath::Helpers::convert_colour_channel<channel_type, RhsChannel_>(b_.second))
					); 
				}
			);
		}
#pragma endregion

#pragma region CLEARING_FUNCTIONS
		/// <summary>
		/// <para> Erases the item from this gradient's colour map at the provided index. </para>
		/// <para> If this removes the final element, the colour map will reset to its default state. </para>
		/// </summary>
		/// <param name="index_">Index of the item to remove from this gradient's colour map.</param>
		/// <returns>True if an item was erased; otherwise false.</returns>
		inline bool EraseColourIndex(std::size_t index_)
		{
			bool anything_erased_ = _erase_index_from_container(index_, colours);
			_validate_colours();
			return anything_erased_;
		}

		/// <summary>
		/// <para> Erases the item from this gradient's colour map with the provided anchor_point_. </para>
		/// <para> If this removes the final element, the colour map will reset to its default state. </para>
		/// </summary>
		/// <param name="anchor_point_">Anchor point to remove from this gradient's colour map.</param>
		/// <returns>True if an item was erased; otherwise false.</returns>
		inline bool EraseColourAnchor(anchor_type anchor_point_)
		{
			bool anything_erased_ = _erase_anchor_point_from_container(clamp_anchor(anchor_point_), colours);
			_validate_colours();
			return anything_erased_;
		}

		/// <summary>
		/// <para> Erases the item from this gradient's alpha map at the provided index. </para>
		/// <para> If this removes the final element, the alpha map will reset to its default state. </para>
		/// </summary>
		/// <param name="index_">Index of the item to remove from this gradient's alpha map.</param>
		/// <returns>True if an item was erased; otherwise false.</returns>
		inline bool EraseAlphaIndex(std::size_t index_)
		{
			bool anything_erased_ = _erase_index_from_container(index_, alphas);
			_validate_alphas();
			return anything_erased_;
		}

		/// <summary>
		/// <para> Erases the item from this gradient's alpha map with the provided anchor_point_. </para>
		/// <para> If this removes the final element, the alpha map will reset to its default state. </para>
		/// </summary>
		/// <param name="anchor_point_">Anchor point to remove from this gradient's alpha map.</param>
		/// <returns>True if an item was erased; otherwise false.</returns>
		inline bool EraseAlphaAnchor(anchor_type anchor_point_)
		{
			bool anything_erased_ = _erase_anchor_point_from_container(clamp_anchor(anchor_point_), alphas);
			_validate_alphas();
			return anything_erased_;
		}

		/// <summary> Resets this gradient's colour map to its default state. </summary>
		inline void ClearColours()
		{
			_make_empty_colours().swap(colours);
		}

		/// <summary> Resets this gradient's alpha map to its default state. </summary>
		inline void ClearAlphas()
		{
			_make_empty_alphas().swap(alphas);
		}

		/// <summary> Resets this gradient to its default state. </summary>
		inline void Clear()
		{
			ClearColours();
			ClearAlphas();
		}
#pragma endregion

#pragma region INSERTION_FUNCS
		/// <summary>
		/// <para> Adds the provided colour_ at the provided anchor_ point, clamping the provided colour into a valid intensity range. </para>
		/// <para> If the provided anchor_ point is already in use, this will replace the existing colour at that point. </para>
		/// </summary>
		/// <param name="anchor_">Normalised 0:1 anchor point at which to place the passed colour. This will be clamped into the range 0:1.</param>
		/// <param name="colour_">EmuMath Colour to set at the stated anchor_ point. If the channel type is incompatible, a conversion will be performed.</param>
		template<typename InChannelType_, bool InContainsAlpha_>
		inline void AddClampedColourAnchor(anchor_type anchor_, const EmuMath::Colour<InChannelType_, InContainsAlpha_>& colour_)
		{
			_add_item_to_container(clamp_anchor(anchor_), colour_.Clamped<channel_type, false>(), colours);
		}
		/// <summary>
		/// <para> Adds the provided colour_ at the provided anchor_ point, wrapping the provided colour into a valid intensity range. </para>
		/// <para> If the provided anchor_ point is already in use, this will replace the existing colour at that point. </para>
		/// </summary>
		/// <param name="anchor_">Normalised 0:1 anchor point at which to place the passed colour. This will be clamped into the range 0:1.</param>
		/// <param name="colour_">EmuMath Colour to set at the stated anchor_ point. If the channel type is incompatible, a conversion will be performed.</param>
		template<typename InChannelType_, bool InContainsAlpha_>
		inline void AddWrappedColourAnchor(anchor_type anchor_, const EmuMath::Colour<InChannelType_, InContainsAlpha_>& colour_)
		{
			_add_item_to_container(clamp_anchor(anchor_), colour_.Wrapped<channel_type, false>(), colours);
		}

		/// <summary>
		/// <para> Adds the provided alpha_ at the provided anchor_ point, clamping the provided alpha into a valid intensity range. </para>
		/// <para> If the provided anchor_ point is already in use, this will replace the existing alpha at that point. </para>
		/// </summary>
		/// <param name="anchor_">Normalised 0:1 anchor point at which to place the passed alpha. This will be clamped into the range 0:1.</param>
		/// <param name="alpha_">Alpha to set at the stated anchor_ point. This is read as-is, and will not be converted if incompatible.</param>
		template<typename InAlpha_, typename = std::enable_if_t<std::is_convertible_v<InAlpha_, channel_type>>>
		inline void AddClampedAlphaAnchor(anchor_type anchor_, const InAlpha_& alpha_)
		{
			_add_item_to_container(clamp_anchor(anchor_), clamp_alpha(static_cast<channel_type>(alpha_)), alphas);
		}
		/// <summary>
		/// <para> Adds the provided alpha_ at the provided anchor_ point, wrapping the provided alpha into a valid intensity range. </para>
		/// <para> If the provided anchor_ point is already in use, this will replace the existing alpha at that point. </para>
		/// </summary>
		/// <param name="anchor_">Normalised 0:1 anchor point at which to place the passed alpha. This will be clamped into the range 0:1.</param>
		/// <param name="alpha_">Alpha to set at the stated anchor_ point. This is read as-is, and will not be converted if incompatible.</param>
		template<typename InAlpha_, typename = std::enable_if_t<std::is_convertible_v<InAlpha_, channel_type>>>
		inline void AddWrappedAlphaAnchor(anchor_type anchor_, const InAlpha_& alpha_)
		{
			_add_item_to_container(clamp_anchor(anchor_), wrap_alpha(static_cast<channel_type>(alpha_)), alphas);
		}

		/// <summary>
		/// <para> Adds the provided colour_ at the provided anchor_ point, clamping the provided colour into a valid intensity range. </para>
		/// <para> If the provided anchor_ point is already in use, this will replace the existing colour at that point. </para>
		/// <para> Returned Index Validity: The returned index is valid for as long as no indices before or equal to it are inserted or removed. </para>
		/// </summary>
		/// <param name="anchor_">Normalised 0:1 anchor point at which to place the passed colour. This will be clamped into the range 0:1.</param>
		/// <param name="colour_">EmuMath Colour to set at the stated anchor_ point. If the channel type is incompatible, a conversion will be performed.</param>
		/// <returns>Index at which the anchor was placed.</returns>
		template<typename InChannelType_, bool InContainsAlpha_>
		[[nodiscard]] inline std::size_t AddClampedColourAnchor_GetIndex(anchor_type anchor_, const EmuMath::Colour<InChannelType_, InContainsAlpha_>& colour_)
		{
			return _add_item_to_container_with_index_return(clamp_anchor(anchor_), colour_.Clamped<channel_type, false>(), colours);
		}
		/// <summary>
		/// <para> Adds the provided colour_ at the provided anchor_ point, wrapping the provided colour into a valid intensity range. </para>
		/// <para> If the provided anchor_ point is already in use, this will replace the existing colour at that point. </para>
		/// <para> Returned Index Validity: The returned index is valid for as long as no indices before or equal to it are inserted or removed. </para>
		/// </summary>
		/// <param name="anchor_">Normalised 0:1 anchor point at which to place the passed colour. This will be clamped into the range 0:1.</param>
		/// <param name="colour_">EmuMath Colour to set at the stated anchor_ point. If the channel type is incompatible, a conversion will be performed.</param>
		/// <returns>Index at which the anchor was placed.</returns>
		template<typename InChannelType_, bool InContainsAlpha_>
		[[nodiscard]] inline std::size_t AddWrappedColourAnchor_GetIndex(anchor_type anchor_, const EmuMath::Colour<InChannelType_, InContainsAlpha_>& colour_)
		{
			return _add_item_to_container_with_index_return(clamp_anchor(anchor_), colour_.Wrapped<channel_type, false>(), colours);
		}

		/// <summary>
		/// <para> Adds the provided alpha_ at the provided anchor_ point, clamping the provided alpha into a valid intensity range. </para>
		/// <para> If the provided anchor_ point is already in use, this will replace the existing alpha at that point. </para>
		/// <para> Returned Index Validity: The returned index is valid for as long as no indices before or equal to it are inserted or removed. </para>
		/// </summary>
		/// <param name="anchor_">Normalised 0:1 anchor point at which to place the passed alpha. This will be clamped into the range 0:1.</param>
		/// <param name="alpha_">Alpha to set at the stated anchor_ point. This is read as-is, and will not be converted if incompatible.</param>
		/// <returns>Index at which the anchor was placed.</returns>
		template<typename InAlpha_, typename = std::enable_if_t<std::is_convertible_v<InAlpha_, channel_type>>>
		[[nodiscard]] inline std::size_t AddClampedAlphaAnchor_GetIndex(anchor_type anchor_, const InAlpha_& alpha_)
		{
			return _add_item_to_container_with_index_return(clamp_anchor(anchor_), clamp_alpha(static_cast<channel_type>(alpha_)), alphas);
		}
		/// <summary>
		/// <para> Adds the provided alpha_ at the provided anchor_ point, wrapping the provided alpha into a valid intensity range. </para>
		/// <para> If the provided anchor_ point is already in use, this will replace the existing alpha at that point. </para>
		/// <para> Returned Index Validity: The returned index is valid for as long as no indices before or equal to it are inserted or removed. </para>
		/// </summary>
		/// <param name="anchor_">Normalised 0:1 anchor point at which to place the passed alpha. This will be clamped into the range 0:1.</param>
		/// <param name="alpha_">Alpha to set at the stated anchor_ point. This is read as-is, and will not be converted if incompatible.</param>
		/// <returns>Index at which the anchor was placed.</returns>
		template<typename InAlpha_, typename = std::enable_if_t<std::is_convertible_v<InAlpha_, channel_type>>>
		[[nodiscard]] inline std::size_t AddWrappedAlphaAnchor_GetIndex(anchor_type anchor_, const InAlpha_& alpha_)
		{
			return _add_item_to_container_with_index_return(clamp_anchor(anchor_), wrap_alpha(static_cast<channel_type>(alpha_)), alphas);
		}

		inline void ReverseColours()
		{
			_reverse_container(colours);
		}

		inline void ReverseAlphas()
		{
			_reverse_container(alphas);
		}

		inline void Reverse()
		{
			_reverse_container(colours);
			_reverse_container(alphas);
		}

		template<class Container_>
		static inline void _reverse_container(Container_& container_)
		{
			Container_ reversed_ = Container_();
			std::transform
			(
				container_.rbegin(),
				container_.rend(),
				std::inserter(reversed_, reversed_.end()),
				[](const auto& pair_) 
				{
					return typename Container_::value_type(max_anchor - pair_.first, pair_.second);
				}
			);
			container_.swap(reversed_);
		}
#pragma endregion

#pragma region ACCESS_FUNCTIONS
		/// <summary>
		/// <para> Returns an EmuMath Colour, formed from the provided anchor_point_ within this gradient's colour map. </para>
		/// <para> The colour's channels value will be converted to suit the output type if necessary. </para>
		/// <para> 
		///		If the output colour contains alpha (defaults to no alpha), it will be that colour's default value for its alpha channel. 
		///		To output a colour formed from an anchor point on both the colour and alpha maps of this gradient, use `Get`.
		/// </para>
		/// <para> The provided anchor point will be clamped into a valid 0:1 range. </para>
		/// </summary>
		/// <typeparam name="OutChannel_">
		///		Type of channel to be contained in the output colour. Conversions are automatically performed. Defaults to this gradient's channel_type.
		/// </typeparam>
		/// <param name="anchor_point_">Anchor point within this gradient to form the output colour via.</param>
		/// <returns>EmuMath Colour formed by the provided anchor point within this gradient's colour map, with a valid conversion if needed.</returns>
		template<class OutChannel_ = channel_type, bool OutContainsAlpha_ = false>
		[[nodiscard]] inline EmuMath::Colour<OutChannel_, OutContainsAlpha_> GetColour(anchor_type anchor_point_) const
		{
			if constexpr (std::is_same_v<OutChannel_, channel_type> && !OutContainsAlpha_)
			{
				return _find_item(clamp_anchor(anchor_point_), colours);
			}
			else
			{
				return EmuMath::Colour<OutChannel_, OutContainsAlpha_>(_find_item(clamp_anchor(anchor_point_), colours));
			}
		}
		template<bool OutContainsAlpha_>
		[[nodiscard]] inline EmuMath::Colour<channel_type, OutContainsAlpha_> GetColour(anchor_type anchor_point_) const
		{
			if constexpr (!OutContainsAlpha_)
			{
				return _find_item(clamp_anchor(anchor_point_), colours);
			}
			else
			{
				return EmuMath::Colour<channel_type, OutContainsAlpha_>(_find_item(clamp_anchor(anchor_point_), colours));
			}
		}

		/// <summary>
		/// <para> Returns an EmuMath Colour, formed from the provided anchor_point_ within this gradient's colour map. </para>
		/// <para> The colour's channels value will be converted to suit the output type if necessary. </para>
		/// <para> 
		///		If the output colour contains alpha (defaults to no alpha), it will be that colour's default value for its alpha channel. 
		///		To output a colour formed from an anchor point on both the colour and alpha maps of this gradient, use `Get`.
		/// </para>
		/// <para> The provided anchor point will be wrapped into a valid 0:1 range. </para>
		/// </summary>
		/// <typeparam name="OutChannel_">
		///		Type of channel to be contained in the output colour. Conversions are automatically performed. Defaults to this gradient's channel_type.
		/// </typeparam>
		/// <param name="anchor_point_">Anchor point within this gradient to form the output colour via.</param>
		/// <returns>EmuMath Colour formed by the provided anchor point within this gradient's colour map, with a valid conversion if needed.</returns>
		template<class OutChannel_ = channel_type, bool OutContainsAlpha_ = false>
		[[nodiscard]] inline EmuMath::Colour<OutChannel_, OutContainsAlpha_> GetColourWrapped(anchor_type anchor_point_) const
		{
			if constexpr (std::is_same_v<OutChannel_, channel_type> && !OutContainsAlpha_)
			{
				return _find_item(wrap_anchor(anchor_point_), colours);
			}
			else
			{
				return EmuMath::Colour<OutChannel_, OutContainsAlpha_>(_find_item(wrap_anchor(anchor_point_), colours));
			}
		}
		template<bool OutContainsAlpha_>
		[[nodiscard]] inline EmuMath::Colour<channel_type, OutContainsAlpha_> GetColourWrapped(anchor_type anchor_point_) const
		{
			if constexpr (!OutContainsAlpha_)
			{
				return _find_item(wrap_anchor(anchor_point_), colours);
			}
			else
			{
				return EmuMath::Colour<channel_type, OutContainsAlpha_>(_find_item(wrap_anchor(anchor_point_), colours));
			}
		}

		/// <summary>
		/// <para> Returns an alpha channel, formed from the provided anchor_point_ within this gradient's alpha map. </para>
		/// <para> The returned alpha channel value will be converted to suit the output type if necessary. </para>
		/// <para> The provided anchor point will be clamped into a valid 0:1 range. </para>
		/// </summary>
		/// <typeparam name="OutChannel_">Type of channel to output. Conversions are automatically performed. Defaults to this gradient's channel_type.</typeparam>
		/// <param name="anchor_point_">Anchor point within this gradient to form the output alpha via.</param>
		/// <returns>Alpha channel formed by the provided anchor point within this gradient's alpha map, with a valid conversion if needed.</returns>
		template<typename OutChannel_ = channel_type>
		[[nodiscard]] inline channel_type GetAlpha(anchor_type anchor_point_) const
		{
			return EmuMath::Helpers::convert_colour_channel<OutChannel_, channel_type>(_find_item(clamp_anchor(anchor_point_), alphas));
		}

		/// <summary>
		/// <para> Returns an alpha channel, formed from the provided anchor_point_ within this gradient's alpha map. </para>
		/// <para> The returned alpha channel value will be converted to suit the output type if necessary. </para>
		/// <para> The provided anchor point will be wrapped into a valid 0:1 range. </para>
		/// </summary>
		/// <typeparam name="OutChannel_">Type of channel to output. Conversions are automatically performed. Defaults to this gradient's channel_type.</typeparam>
		/// <param name="anchor_point_">Anchor point within this gradient to form the output alpha via.</param>
		/// <returns>Alpha channel formed by the provided anchor point within this gradient's alpha map, with a valid conversion if needed.</returns>
		template<typename OutChannel_ = channel_type>
		[[nodiscard]] inline channel_type GetAlphaWrapped(anchor_type anchor_point_) const
		{
			return EmuMath::Helpers::convert_colour_channel<OutChannel_, channel_type>(_find_item(wrap_anchor(anchor_point_), alphas));
		}

		/// <summary>
		/// <para> Returns a colour containing RGBA values, formed from the provided anchor_point_ in both the colour and alpha maps. </para>
		/// <para> May alternatively provide two anchor points for the colour and alpha anchors respectively. </para>
		/// <para> The provided anchor point(s) will be clamped into a valid 0:1 range. </para>
		/// </summary>
		/// <typeparam name="OutChannel_">
		///		Type of channel to be contained in the output colour. Conversions are automatically performed. Defaults to this gradient's channel_type.
		/// </typeparam>
		/// <param name="anchor_point_">Anchor point within this gradient to form the colour via. May provide a separate anchor point for the alpha value.</param>
		/// <returns>EmuMath Colour containing RGBA values determined by the provided anchor point(s) within this gradient, with channel conversions if needed.</returns>
		template<typename OutChannel_ = channel_type>
		[[nodiscard]] inline EmuMath::ColourRGBA<OutChannel_> Get(anchor_type anchor_point_) const
		{
			anchor_point_ = clamp_anchor(anchor_point_);
			return EmuMath::ColourRGBA<OutChannel_>
			(
				_find_item(anchor_point_, colours),
				EmuMath::Helpers::convert_colour_channel<OutChannel_, channel_type>(_find_item(anchor_point_, alphas))
			);
		}
		template<typename OutChannel_ = channel_type>
		[[nodiscard]] inline EmuMath::ColourRGBA<OutChannel_> Get(anchor_type colour_anchor_point_, anchor_type alpha_anchor_point_) const
		{
			return EmuMath::ColourRGBA<OutChannel_>
			(
				_find_item(clamp_anchor(colour_anchor_point_), colours),
				EmuMath::Helpers::convert_colour_channel<OutChannel_, channel_type>(_find_item(clamp_anchor(alpha_anchor_point_), alphas))
			);
		}

		/// <summary>
		/// <para> Returns a colour containing RGBA values, formed from the provided anchor_point_ in both the colour and alpha maps. </para>
		/// <para> May alternatively provide two anchor points for the colour and alpha anchors respectively. </para>
		/// <para> The provided anchor point(s) will be wrapped into a valid 0:1 range. </para>
		/// </summary>
		/// <typeparam name="OutChannel_">
		///		Type of channel to be contained in the output colour. Conversions are automatically performed. Defaults to this gradient's channel_type.
		/// </typeparam>
		/// <param name="anchor_point_">Anchor point within this gradient to form the colour via. May provide a separate anchor point for the alpha value.</param>
		/// <returns>EmuMath Colour containing RGBA values determined by the provided anchor point(s) within this gradient, with channel conversions if needed.</returns>
		template<typename OutChannel_ = channel_type>
		[[nodiscard]] inline EmuMath::ColourRGBA<OutChannel_> GetWrapped(anchor_type anchor_point_) const
		{
			anchor_point_ = wrap_anchor(anchor_point_);
			return EmuMath::ColourRGBA<OutChannel_>
			(
				_find_item(anchor_point_, colours),
				EmuMath::Helpers::convert_colour_channel<OutChannel_, channel_type>(_find_item(anchor_point_, alphas))
			);
		}
		template<typename OutChannel_ = channel_type>
		[[nodiscard]] inline EmuMath::ColourRGBA<OutChannel_> GetWrapped(anchor_type colour_anchor_point_, anchor_type alpha_anchor_point_) const
		{
			return EmuMath::ColourRGBA<OutChannel_>
			(
				_find_item(wrap_anchor(colour_anchor_point_), colours),
				EmuMath::Helpers::convert_colour_channel<OutChannel_, channel_type>(_find_item(wrap_anchor(alpha_anchor_point_), alphas))
			);
		}

		/// <summary> Provides the number of colours currently stored in this gradient. </summary>
		/// <returns>Size of this gradient's colour map.</returns>
		[[nodiscard]] inline std::size_t NumColours() const
		{
			return colours.size();
		}

		/// <summary> Provides the number of alphas currently stored in this gradient. </summary>
		/// <returns>Size of this gradient's alpha map.</returns>
		[[nodiscard]] inline std::size_t NumAlphas() const
		{
			return alphas.size();
		}

		/// <summary> Provides read-only access to this gradient's colour map. </summary>
		/// <returns>Constant reference to this gradient's colour map.</returns>
		[[nodiscard]] inline const colour_map& ViewColours() const
		{
			return colours;
		}

		/// <summary> Provides read-only access to this gradient's alpha map. </summary>
		/// <returns>Constant reference to this gradient's alpha map.</returns>
		[[nodiscard]] inline const alpha_map& ViewAlphas() const
		{
			return alphas;
		}
#pragma endregion

#pragma region VALIDATION_FUNCTIONS
		/// <summary> 
		/// <para> Forces this gradient to perform a validty check, and correct itself into a valid state. </para>
		/// <para> Unless this gradient has been moved or modified outside of its member functions, it is guaranteed to already be in a valid state. </para>
		/// </summary>
		inline void ForceValidation()
		{
			_validate_colours();
			_validate_alphas();
		}
#pragma endregion

#pragma region STREAM_FUNCTIONS
		/// <summary> Appends a list of this gradient's colours and their anchors to the provided stream in the format "[anchor]: colour", separated by new lines. </summary>
		/// <param name="str_">Stream to append to.</param>
		/// <returns>Reference to the passed stream.</returns>
		std::ostream& AppendColoursToStream(std::ostream& str_) const
		{
			return _do_stream_append<false>(str_, colours);
		}
		std::wostream& AppendColoursToStream(std::wostream& str_) const
		{
			return _do_stream_append<true>(str_, colours);
		}

		/// <summary> Appends a list of this gradient's alphas and their anchors to the provided stream in the format "[anchor]: alpha", separated by new lines. </summary>
		/// <param name="str_">Stream to append to.</param>
		/// <returns>Reference to the passed stream.</returns>
		std::ostream& AppendAlphasToStream(std::ostream& str_) const
		{
			return _do_stream_append<false>(str_, alphas);
		}
		std::wostream& AppendAlphasToStream(std::wostream& str_) const
		{
			return _do_stream_append<true>(str_, alphas);
		}
#pragma endregion

	private:
#pragma region PRIVATE_STATIC_HELPERS
		template<class Item_, class Container_>
		static inline auto _add_item_to_container(anchor_type anchor_, Item_&& item_, Container_& container_)
		{
			auto it_ = container_.find(anchor_);
			if (it_ != container_.end())
			{
				it_->second = item_;
			}
			else
			{
				it_ = container_.insert(std::pair<anchor_type, typename Container_::mapped_type>(anchor_, item_)).first;
			}
			return it_;
		}

		template<class Item_, class Container_>
		static inline std::size_t _add_item_to_container_with_index_return(anchor_type anchor_, Item_&& item_, Container_& container_)
		{
			return _find_iterator_index(_add_item_to_container(anchor_, item_, container_), container_);
		}

		/// <summary>
		/// <para> Finds and calculates the item at the specified anchor point within the passed container_. </para>
		/// <para> This effectively performs a linear interpolation between the items to the left and right of the anchor. </para>
		/// <para> If the anchor does not lie between two elements, this will instead return a copy of the closest element to the provided anchor_. </para>
		/// </summary>
		/// <param name="anchor_">Anchor point to find the item of.</param>
		/// <param name="container_">Container to search and return the mapped_type of.</param>
		/// <returns>Item for the provided anchor point within the provided container.</returns>
		template<class Container_>
		[[nodiscard]] static inline const typename Container_::mapped_type _find_item(anchor_type anchor_, Container_& container_)
		{
			using out_type = typename Container_::mapped_type;
			using Lerp_ = EmuCore::do_lerp<out_type, out_type, anchor_type>;

			std::size_t index_ = 0;
			auto right_it_ = _find_first_item_greater_equal_to_anchor(anchor_, index_, container_);

			// If the index_ is 0, we have nothing to the left of our right item, which means we are fully the found item.
			// --- Additionally, if the item's anchor is not greater than or equal to the passed anchor_,
			// --- it means we're past the last item and should fully use that instead.
			if ((index_ != 0) && (right_it_->first >= anchor_))
			{
				auto left_it_ = right_it_;
				--left_it_;

				anchor_ -= left_it_->first;
				anchor_type anchor_diff_ = right_it_->first - left_it_->first;
				return Lerp_()(left_it_->second, right_it_->second, anchor_ / anchor_diff_);
			}
			else
			{
				// Reached end, so return this item in its entirety
				return right_it_->second;
			}
		}

		/// <summary>
		/// <para> Finds the first item in the provided container with an anchor point greater than or equal to the provided anchor_. </para>
		/// <para> This effectively finds the right-hand item (b) for a linear interpolation. </para>
		/// <para> If no index is greater than or equal to the provided anchor, this will provide the final item. </para>
		/// </summary>
		/// <param name="anchor_">Anchor point to search for.</param>
		/// <param name="out_index_">Reference to output the item's integral index to.</param>
		/// <param name="container_">Container to retrieve an item from.</param>
		/// <returns>Iterator to the first item to meet the described constraints.</returns>
		template<class Container_>
		[[nodiscard]] static inline auto _find_first_item_greater_equal_to_anchor(const anchor_type anchor_, std::size_t& out_index_, Container_& container_)
		{
			out_index_ = 0;
			auto it_ = container_.begin();
			if (it_->first >= anchor_)
			{
				return it_;
			}
			else
			{
				auto end_ = container_.end();
				auto next_it_ = it_;
				++next_it_;
				while (next_it_ != end_)
				{
					++out_index_;
					it_ = next_it_;
					if (it_->first >= anchor_)
					{
						return it_;
					}
					else
					{
						++next_it_;
					}

				}
				return it_;
			}
		}

		/// <summary>
		/// <para> Appends a single container iterator to the passed stream, in the format "[anchor]: value". </para>
		/// <para> If the IsWide_ boolean is true, wide strings will be appended where applicable. </para>
		/// <para> If IncludeNewline_ is true, a new line will be appended immediately before the iterator's contents. </para>
		/// </summary>
		/// <param name="str_">Stream to append the iterator's contents to.</param>
		/// <param name="it_">Iterator to append the contents of to the provided stream.</param>
		template<bool IsWide_, bool IncludeNewline_, class Stream_, class It_>
		static inline void _append_it_to_stream(Stream_& str_, It_& it_)
		{
			if constexpr (IncludeNewline_)
			{

				if constexpr (IsWide_)
				{
					str_ << L"\n[" << it_->first << L"]: " << it_->second;
				}
				else
				{
					str_ << "\n[" << it_->first << "]: " << it_->second;
				}
			}
			else
			{
				if constexpr (IsWide_)
				{
					str_ << L"[" << it_->first << L"]: " << it_->second;
				}
				else
				{
					str_ << "[" << it_->first << "]: " << it_->second;
				}
			}
		}

		/// <summary> Appends an entire container to the passed stream in the format "[anchor]: value". </summary>
		/// <param name="str_">Stream to append the entire container to.</param>
		/// <param name="container_">Container to append the entirety of to the provided stream.</param>
		/// <returns>Reference to the stream being appended to.</returns>
		template<bool IsWide_, class Stream_, class Container_>
		static inline Stream_& _do_stream_append(Stream_& str_, Container_& container_)
		{
			auto it_ = container_.begin();
			auto end_ = container_.end();
			if (it_ != end_)
			{
				_append_it_to_stream<IsWide_, false>(str_, it_);
				++it_;
				while (it_ != end_)
				{
					_append_it_to_stream<IsWide_, true>(str_, it_);
					++it_;
				}
			}
			return str_;
		}

		/// <summary>
		/// <para> Finds the integral index of the iterator to_find_ before the end of the passed container_. </para>
		/// <para> If the passed iterator cannot be found, this will return the size of the container (i.e. maximum valid index + 1). </para>
		/// </summary>
		/// <param name="to_find_">Iterator to find the index of.</param>
		/// <param name="container_">Container to search.</param>
		/// <returns>Index at which the iterator was found within the provided container, or the container's size if it cannot be found.</returns>
		template<typename ItToFind_, class Container_>
		[[nodiscard]] static inline std::size_t _find_iterator_index(ItToFind_ to_find_, Container_& container_)
		{
			auto it_ = container_.begin();
			auto end_ = container_.end();
			std::size_t count_ = 0;
			while (it_ != end_)
			{
				if (it_ == to_find_)
				{
					return count_;
				}
				else
				{
					++count_;
					++it_;
				}
			}
			// Only reach this point if to_find_ wasn't found before end_.
			return container_.size();
		}

		/// <summary>
		/// <para> Finds the iterator at the provided integral index_ within the passed container_. </para>
		/// <para> If the passed index_ exceeds the highest index in the passed container, this will return container_.end(). </para>
		/// </summary>
		/// <param name="index_">Integral index to find the iterator for.</param>
		/// <param name="container_">Container to search.</param>
		/// <returns>Iterator for the provided index_ in the passed container_, or container_.end() if the index_ exceeds the range of container_.</returns>
		template<class Container_>
		static inline auto _find_iterator_by_index(std::size_t index_, Container_& container_)
		{
			if (index_ < container_.size())
			{
				auto it_ = container_.begin();
				for (std::size_t i = 0; i < index_; ++i)
				{
					++it_;
				}
				return it_;
			}
			else
			{
				return container_.end();
			}
		}

		/// <summary> Erases the provided anchor point from the passed container, if it exists. </summary>
		/// <param name="anchor_">Anchor point to erase.</param>
		/// <param name="container_">Container to erase an element of.</param>
		/// <returns>True if an element was erased; otherwise false.</returns>
		template<class Container_>
		static inline bool _erase_anchor_point_from_container(anchor_type anchor_, Container_& container_)
		{
			auto it_ = container_.find(anchor_);
			if (it_ != container_.end())
			{
				container_.erase(it_);
				return true;
			}
			else
			{
				return false;
			}
		}

		/// <summary> Erases the provided index from the passed container, if it exists. </summary>
		/// <param name="index_">Index of the element to erase.</param>
		/// <param name="container_">Container to erase an element of.</param>
		/// <returns>True if an element was erased; otherwise false.</returns>
		template<class Container_>
		static inline bool _erase_index_from_container(std::size_t index_, Container_& container_)
		{
			if (index_ < container_.size())
			{
				container_.erase(_find_iterator_by_index(index_, container_));
				return true;
			}
			else
			{
				return false;
			}
		}

		/// <summary> Returns a valid colour_map for use whenever this gradient contains less than 1 colour. </summary>
		[[nodiscard]] static inline colour_map _make_empty_colours()
		{
			colour_map out_ = colour_map();
			out_.insert(std::pair<anchor_type, colour_type>(min_anchor, colour_type()));
			return out_;
		}
		/// <summary> Returns a valid alpha_map for use whenever this gradient contains less than 1 alpha. </summary>
		[[nodiscard]] static inline alpha_map _make_empty_alphas()
		{
			alpha_map out_ = alpha_map();
			out_.insert(std::pair<anchor_type, channel_type>(min_anchor, colour_type::max_intensity));
			return out_;
		}

		template<class LhsContainer_, class RhsContainer_, class ValueCmp_>
		[[nodiscard]] static inline bool _do_single_container_cmp_equal(const LhsContainer_& lhs_, const RhsContainer_& rhs_, ValueCmp_ cmp_)
		{
			if (lhs_.size() == rhs_.size())
			{
				return std::equal(lhs_.begin(), lhs_.end(), rhs_.begin(), cmp_);
			}
			else
			{
				return false;
			}
		}
#pragma endregion

#pragma region PRIVATE_MEMBER_HELPERS
		/// <summary> Ensures this item's colours are in a valid state, such as preventing it from containing less than 1 colour. </summary>
		inline void _validate_colours()
		{
			if (colours.size() == 0)
			{
				colours = _make_empty_colours();
			}
		}

		/// <summary> Ensures this item's alphas are in a valid state, such as preventing it from containing less than 1 alpha. </summary>
		inline void _validate_alphas()
		{
			if (alphas.size() == 0)
			{
				alphas = _make_empty_alphas();
			}
		}

		/// <summary>
		/// <para> Copies the passed gradient, performing any necessary channel conversions if needed. </para>
		/// </summary>
		/// <param name="to_copy_">Gradient to copy the data of.</param>
		template<class OtherChannel_>
		inline void _copy_gradient(const Gradient<OtherChannel_>& to_copy_)
		{
			colours.insert(to_copy_.ViewColours().begin(), to_copy_.ViewColours().end());
			std::transform
			(
				to_copy_.ViewAlphas().begin(),
				to_copy_.ViewAlphas().end(),
				std::inserter(alphas, alphas.end()),
				[&](const auto& item_)	// Lambda will convert the passed item's alpha to the correct channel type; this is automatically handled for colours
				{
					return typename alpha_map::value_type
					(
						item_.first,
						EmuMath::Helpers::convert_colour_channel<channel_type, OtherChannel_>(item_.second)
					); 
				}
			);
			// Validity check in case an invalid gradient was copied
			ForceValidation();
		}
		/// <summary> Optimised copy of the same type of gradient, avoiding unneeeded operations. </summary>
		/// <param name="to_copy_">Gradient to copy the data of.</param>
		template<>
		inline void _copy_gradient<channel_type>(const Gradient<channel_type>& to_copy_)
		{
			colours = to_copy_.colours;
			alphas = to_copy_.colours;
			ForceValidation();
		}

		/// <summary> Performs an equality comparison with the rhs_ gradient, performing any necessary conversions if RhsChannel_ is incompatible. </summary>
		/// <param name="rhs_">Gradient of any Channel_ type to compare this gradient to.</param>
		/// <returns>True if the comparisons returned true, otherwise false.</returns>
		template<class RhsChannel_>
		[[nodiscard]] inline bool _do_cmp_equal(const EmuMath::Gradient<RhsChannel_>& rhs_) const
		{
			const auto& rhs_alphas_ = rhs_.ViewAlphas();
			const auto& rhs_colours_ = rhs_.ViewColours();

			if ((alphas.size() == rhs_alphas_.size()) && (colours.size() == rhs_colours_.size()))
			{
				bool equal_ = std::equal
				(
					alphas.begin(),
					alphas.end(),
					rhs_alphas_.begin(),
					[](const auto& a_, const auto& b_)
					{
						return 
						(
							(a_.first == b_.first) &&
							(a_.second == EmuMath::Helpers::convert_colour_channel<channel_type, RhsChannel_>(b_.second))
						);
					}
				);

				if (!equal_)
				{
					return false;
				}
				else
				{
					return std::equal
					(
						colours.begin(),
						colours.end(),
						rhs_colours_.begin(),
						[](const auto& a_, const auto& b_)
						{
							return (a_.first == b_.first) && (a_.second == b_.second);
						}
					);
				}
			}
			else
			{
				return false;
			}
		}
#pragma endregion

		colour_map colours;
		alpha_map alphas;
	};
}

template<class Channel_>
inline std::ostream& operator<<(std::ostream& str_, const EmuMath::Gradient<Channel_>& gradient_)
{
	str_ << "Colours:\n";
	gradient_.AppendColoursToStream(str_);
	str_ << "\nAlphas:\n";
	gradient_.AppendAlphasToStream(str_);
	return str_;
}

template<class Channel_>
inline std::wostream& operator<<(std::wostream& str_, const EmuMath::Gradient<Channel_>& gradient_)
{
	str_ << L"Colours:\n";
	gradient_.AppendColoursToStream(str_);
	str_ << L"\nAlphas:\n";
	gradient_.AppendAlphasToStream(str_);
	return str_;
}

#endif
