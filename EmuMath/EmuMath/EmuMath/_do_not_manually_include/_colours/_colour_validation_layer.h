#ifndef EMU_MATH_COLOUR_VALIDATION_LAYER_H_INC_
#define EMU_MATH_COLOUR_VALIDATION_LAYER_H_INC_ 1

#include "_colour_t.h"

namespace EmuMath::Helpers
{
	/// <summary> Wrapper used to form a validation layer for EmuMath colour. This is for internal EmuMath use, and should not be used outside of alias indirection. </summary>
	template<typename Channel_, bool ContainsAlpha_, class ValidationFunc_>
	class _colour_validation_layer
	{
	public:
		/// <summary> Functor type used for validation. Constructed on demand as compiler is likely to optimise out, and helps with the byte size of colours. </summary>
		using validate_func = ValidationFunc_;
		using underlying_colour = EmuMath::Colour<Channel_, ContainsAlpha_>;
		static constexpr bool contains_alpha = underlying_colour::contains_alpha;
		static constexpr std::size_t size = underlying_colour::size;

		using value_type = typename underlying_colour::value_type;
		using this_type = _colour_validation_layer<value_type, contains_alpha, ValidationFunc_>;
		using channels_vector = typename underlying_colour::channels_vector;
		using vector_rgb_return_type = typename underlying_colour::vector_rgb_return_type;
		using vector_rgba_return_type = typename underlying_colour::vector_rgba_return_type;

		static constexpr bool is_floating_point = std::is_floating_point_v<value_type>;
		static constexpr bool is_integral = std::is_integral_v<value_type>;

		static constexpr value_type min_intensity = underlying_colour::min_intensity;
		static constexpr value_type max_intensity = underlying_colour::max_intensity;
		static constexpr channels_vector _default_colour = underlying_colour::_default_colour;

	private:
		/// <summary>
		/// <para> Private constructor which can be used to copy an underlying_colour without performing validation. </para>
		/// <para> Only for use in functions returning this_type where it is guaranteed that the output colour will be in a valid state without validation. </para>
		/// </summary>
		template<typename Dummy_>
		constexpr _colour_validation_layer(const underlying_colour& safe_colour_to_set_, Dummy_&& dummy_arg_) : colour(safe_colour_to_set_)
		{
		}
		/// <summary>
		/// <para> Private constructor which can be used to move an underlying_colour without performing validation. </para>
		/// <para> Only for use in functions returning this_type where it is guaranteed that the output colour will be in a valid state without validation. </para>
		/// </summary>
		template<typename Dummy_, typename = std::enable_if_t<std::is_move_constructible_v<underlying_colour>>>
		constexpr _colour_validation_layer(underlying_colour&& safe_colour_to_set_, Dummy_&& dummy_arg_) noexcept : 
			colour(std::forward<underlying_colour>(safe_colour_to_set_))
		{
		}

	public:
#pragma region CONSTRUCTORS
		/// <summary>
		/// <para> Constructs a default colour with its main channel intensities set to their minimum. </para>
		/// <para> If this colour contains an alpha channel, that channel will be set to its maximum intensity. </para>
		/// </summary>
		constexpr _colour_validation_layer() : colour()
		{
		}
		/// <summary> Constructs a copy of the passed colour. </summary>
		/// <param name="to_copy_">Colour to copy.</param>
		constexpr _colour_validation_layer(const this_type& to_copy_) : colour(to_copy_.colour)
		{
		}
		/// <summary> Move constructor to create a colour from moved colour data. </summary>
		/// <param name="to_move_">Colour to move the data of into the newly constructed colour.</param>
		constexpr _colour_validation_layer(this_type&& to_move_) noexcept : colour(std::move(to_move_.colour))
		{
		}
		/// <summary> Constructs a copy of the passed colour. </summary>
		/// <param name="to_copy_">Colour to copy.</param>
		constexpr _colour_validation_layer(const underlying_colour& to_copy_) : colour(to_copy_)
		{
			validate_func()(colour);
		}
		/// <summary> Move constructor to create a colour from moved colour data. </summary>
		/// <param name="to_move_">Colour to move the data of into the newly constructed colour.</param>
		constexpr _colour_validation_layer(underlying_colour&& to_move_) noexcept : colour(std::move(to_move_))
		{
			validate_func()(colour);
		}
		/// <summary>
		/// <para> Constructs a copy of the passed colour. </para>
		/// <para> If this colour DOES NOT contain an explicit Alpha channel: the passed colour's Alpha channel will be ignored. </para>
		/// <para> If this colour DOES contain an explicit Alpha channel: this colour's Alpha channel will be initialised at max_intensity. </para>
		/// </summary>
		/// <param name="to_copy_">Colour to copy the Red, Green, and Blue channels of.</param>
		template<class OtherFunc_>
		constexpr _colour_validation_layer(const EmuMath::Helpers::_colour_validation_layer<value_type, !contains_alpha, OtherFunc_>& to_copy_) :
			colour(to_copy_.Get())
		{
		}
		/// <summary>
		/// <para> Constructs a copy of the passed colour. </para>
		/// <para> If this colour DOES NOT contain an explicit Alpha channel: the passed colour's Alpha channel will be ignored. </para>
		/// <para> If this colour DOES contain an explicit Alpha channel: this colour's Alpha channel will be initialised at max_intensity. </para>
		/// </summary>
		/// <param name="to_copy_">Colour to copy the Red, Green, and Blue channels of.</param>
		constexpr _colour_validation_layer(const EmuMath::Colour<value_type, !contains_alpha>& to_copy_) : colour(to_copy_)
		{
			validate_func()(colour);
		}
		/// <summary>
		/// <para> Creates a colour with its contained channels being a direct copy of the passed EmuMath vector. </para>
		/// </summary>
		/// <param name="channels_to_copy_">EmuMath vector representing channels to copy.</param>
		explicit constexpr _colour_validation_layer(const channels_vector& channels_to_copy_) : colour(channels_to_copy_)
		{
			validate_func()(colour);
		}
		/// <summary> Creates a colour by moving the passed channels vector into its stored channel data. </summary>
		/// <param name="channels_to_move_">EmuMath vector to move into the constructed colour's channel data.</param>
		explicit constexpr _colour_validation_layer(channels_vector&& channels_to_move_) noexcept : colour(channels_to_move_)
		{
			validate_func()(colour);
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
			class OtherFunc_,
			typename = std::enable_if_t<!std::is_same_v<value_type, CopyChannelType_>>
		>
		explicit constexpr _colour_validation_layer(const EmuMath::Helpers::_colour_validation_layer<CopyChannelType_, RhsContainsAlpha_, OtherFunc_>& to_copy_) :
			colour(to_copy_)
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
		explicit constexpr _colour_validation_layer(const EmuMath::Colour<CopyChannelType_, RhsContainsAlpha_>& to_copy_) : colour(to_copy_)
		{
			validate_func()(colour);
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
		constexpr _colour_validation_layer(R_&& r_, G_&& g_, B_&& b_) : colour(r_, g_, b_)
		{
			validate_func()(colour);
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
		constexpr _colour_validation_layer(R_&& r_, G_&& g_, B_&& b_, A_&& a_) : colour(r_, g_, b_, a_)
		{
			validate_func()(colour);
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
		constexpr _colour_validation_layer(const EmuMath::Colour<ToCopyChannel_, ToCopyContainsAlpha_>& to_copy_rgb_, A_&& a_) : colour(to_copy_rgb_, a_)
		{
			validate_func()(colour);
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
			return colour.template at<Index_>();
		}

		/// <summary> 
		/// <para> Retrieves a copy of the channel value at the provided index within this Colour's channels. </para>
		/// <para> If this Colour does not contain an explicit Alpha value, this cannot be used to acquire its implicit Alpha value. Use A() in such scenarios. </para>
		/// </summary>
		/// <returns>Copy of the channel value at the provided index within this Colour's channels.</returns>
		[[nodiscard]] constexpr inline value_type at(const std::size_t index_) const
		{
			return colour.at(index_);
		}
		[[nodiscard]] constexpr inline value_type operator[](const std::size_t index_) const
		{
			return colour[index_];
		}

		/// <summary>Returns a copy of this colour's Red channel.</summary>
		/// <returns>Copy of this colour's Red channel.</returns>
		[[nodiscard]] constexpr inline value_type R() const
		{
			return colour.R();
		}
		/// <summary>Returns a copy of this colour's Green channel.</summary>
		/// <returns>Copy of this colour's Green channel.</returns>
		[[nodiscard]] constexpr inline value_type G() const
		{
			return colour.G();
		}
		/// <summary>Returns a copy of this colour's Blue channel.</summary>
		/// <returns>Copy of this colour's Blue channel.</returns>
		[[nodiscard]] constexpr inline value_type B() const
		{
			return colour.B();
		}
		/// <summary>Returns a copy of this colour's Alpha channel.</summary>
		/// <returns>Copy of this colour's Alpha channel. If this colour type does not contain an explicit Alpha value, this will always be max_intensity.</returns>
		[[nodiscard]] constexpr inline value_type A() const
		{
			return colour.A();
		}

		/// <summary>Provides read-only access to the colour wrapped by this validation layer.</summary>
		/// <returns>Copy of the underlying EmuMath Colour stored within this item.</returns>
		[[nodiscard]] constexpr inline const underlying_colour& Get() const
		{
			return colour;
		}
#pragma endregion

#pragma region SETS
		/// <summary> Sets this colour's Red channel to the passed value. </summary>
		/// <param name="r_">Value to set this colour's Red channel to. This will not be modified.</param>
		template<typename R_, typename = std::enable_if_t<EmuCore::TMP::is_static_castable_v<R_, value_type>>>
		constexpr inline void R(R_&& r_)
		{
			colour.R(validate_func()(r_));
		}
		/// <summary> Sets this colour's Green channel to the passed value. </summary>
		/// <param name="g_">Value to set this colour's Green channel to. This will not be modified.</param>
		template<typename G_, typename = std::enable_if_t<EmuCore::TMP::is_static_castable_v<G_, value_type>>>
		constexpr inline void G(G_&& g_)
		{
			colour.G(validate_func()(g_));
		}
		/// <summary> Sets this colour's Blue channel to the passed value. </summary>
		/// <param name="b_">Value to set this colour's Blue channel to. This will not be modified.</param>
		template<typename B_, typename = std::enable_if_t<EmuCore::TMP::is_static_castable_v<B_, value_type>>>
		constexpr inline void B(B_&& b_)
		{
			colour.B(validate_func()(b_));
		}
		/// <summary> Sets this colour's Alpha channel to the passed value. Only available if this colour contains an explicit Alpha channel. </summary>
		/// <param name="a_">Value to set this colour's Alpha channel to. This will not be modified.</param>
		template<typename A_, typename MayOnlyModifyAlphaIfContained_ = std::enable_if_t<EmuCore::TMP::is_static_castable_v<A_, value_type> && contains_alpha>>
		constexpr inline void A(A_&& a_)
		{
			colour.A(validate_func()(a_));
		}

		/// <summary> Shorthand to set via the R, G, and B functions with the respective provided arguments. </summary>
		/// <param name="r_">Value to set this colour's Red channel to. This will not be modified.</param>
		/// <param name="g_">Value to set this colour's Green channel to. This will not be modified.</param>
		/// <param name="b_">Value to set this colour's Blue channel to. This will not be modified.</param>
		/// <returns>Reference to this colour.</returns>
		template<typename R_, typename G_, typename B_, typename = std::enable_if_t<EmuCore::TMP::are_all_static_castable_v<value_type, R_, G_, B_>>>
		constexpr inline this_type& Set(R_&& r_, G_&& g_, B_&& b_)
		{
			validate_func validate_ = validate_func();
			colour.R(validate_(r_));
			colour.G(validate_(g_));
			colour.B(validate_(b_));
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
			validate_func validate_ = validate_func();
			colour.R(validate_(r_));
			colour.G(validate_(g_));
			colour.B(validate_(b_));
			colour.A(validate_(a_));
			return *this;
		}
#pragma endregion

#pragma region CONST_OPERATORS
		template<bool IncludeAlpha_, typename rhs_contained_type, bool RhsContainsAlpha_>
		[[nodiscard]] constexpr inline bool operator==(const EmuMath::Colour<rhs_contained_type, RhsContainsAlpha_>& rhs_) const
		{
			return colour.template operator==<IncludeAlpha_, rhs_contained_type, RhsContainsAlpha_>(rhs_);
		}
		template<typename rhs_contained_type, bool RhsContainsAlpha_>
		[[nodiscard]] constexpr inline bool operator==(const EmuMath::Colour<rhs_contained_type, RhsContainsAlpha_>& rhs_) const
		{
			return colour.template operator==<rhs_contained_type, RhsContainsAlpha_>(rhs_);
		}
		template<bool IncludeAlpha_, typename rhs_contained_type, bool RhsContainsAlpha_, class RhsValidationFunc_>
		[[nodiscard]] constexpr inline bool operator==
		(
			const EmuMath::Helpers::_colour_validation_layer<rhs_contained_type, RhsContainsAlpha_, RhsValidationFunc_>& rhs_
		) const
		{
			return colour.template operator==<IncludeAlpha_>(rhs_.Get());
		}
		template<typename rhs_contained_type, bool RhsContainsAlpha_, class RhsValidationFunc_>
		[[nodiscard]] constexpr inline bool operator==
		(
			const EmuMath::Helpers::_colour_validation_layer<rhs_contained_type, RhsContainsAlpha_, RhsValidationFunc_>& rhs_
		) const
		{
			return colour.operator==(rhs_.Get());
		}

		template<bool IncludeAlpha_, typename rhs_contained_type, bool RhsContainsAlpha_>
		[[nodiscard]] constexpr inline bool operator!=(const EmuMath::Colour<rhs_contained_type, RhsContainsAlpha_>& rhs_) const
		{
			return colour.template operator!=<IncludeAlpha_>(rhs_);
		}
		template<typename rhs_contained_type, bool RhsContainsAlpha_>
		[[nodiscard]] constexpr inline bool operator!=(const EmuMath::Colour<rhs_contained_type, RhsContainsAlpha_>& rhs_) const
		{
			return colour.operator!=(rhs_);
		}
		template<bool IncludeAlpha_, typename rhs_contained_type, bool RhsContainsAlpha_, class RhsValidationFunc_>
		[[nodiscard]] constexpr inline bool operator!=
		(
			const EmuMath::Helpers::_colour_validation_layer<rhs_contained_type, RhsContainsAlpha_, RhsValidationFunc_>& rhs_
		) const
		{
			return colour.template operator!=<IncludeAlpha_>(rhs_.Get());
		}
		template<typename rhs_contained_type, bool RhsContainsAlpha_, class RhsValidationFunc_>
		[[nodiscard]] constexpr inline bool operator!=
		(
			const EmuMath::Helpers::_colour_validation_layer<rhs_contained_type, RhsContainsAlpha_, RhsValidationFunc_>& rhs_
		) const
		{
			return colour.operator!=(rhs_.Get());
		}

		template<bool IncludeAlpha_ = contains_alpha, class Rhs_>
		[[nodiscard]] constexpr inline this_type operator+(const Rhs_& rhs_) const
		{
			return this_type(colour.template operator+<IncludeAlpha_>(_get_rhs(rhs_)));
		}

		template<bool IncludeAlpha_ = contains_alpha, class Rhs_>
		[[nodiscard]] constexpr inline this_type operator-(const Rhs_& rhs_) const
		{
			return this_type(colour.template operator-<IncludeAlpha_>(_get_rhs(rhs_)));
		}

		template<bool IncludeAlpha_ = contains_alpha, class Rhs_>
		[[nodiscard]] constexpr inline this_type operator*(const Rhs_& rhs_) const
		{
			return this_type(colour.template operator*<IncludeAlpha_>(_get_rhs(rhs_)));
		}

		template<bool IncludeAlpha_ = contains_alpha, class Rhs_>
		[[nodiscard]] constexpr inline this_type operator/(const Rhs_& rhs_) const
		{
			return this_type(colour.template operator/<IncludeAlpha_>(_get_rhs(rhs_)));
		}

		template<bool IncludeAlpha_ = contains_alpha, class Rhs_>
		[[nodiscard]] constexpr inline this_type operator%(const Rhs_& rhs_) const
		{
			return this_type(colour.template operator%<IncludeAlpha_>(_get_rhs(rhs_)));
		}
#pragma endregion

#pragma region NON_CONST_OPERATORS
		constexpr inline this_type& operator=(const this_type& rhs_)
		{
			colour = rhs_.colour;
			return *this;
		}
		constexpr inline this_type& operator=(this_type&& rhs_) noexcept
		{
			colour = std::move(rhs_.colour);
			return *this;
		}
		constexpr inline this_type& operator=(const underlying_colour& rhs_)
		{
			colour = rhs_;
			validate_func()(colour);
			return *this;
		}
		constexpr inline this_type& operator=(underlying_colour&& rhs_) noexcept
		{
			colour = std::move(rhs_);
			validate_func()(colour);
			return *this;
		}
		constexpr inline this_type& operator=(const EmuMath::Colour<value_type, !contains_alpha>& rhs_)
		{
			colour = rhs_;
			return *this;
		}

		template<bool IncludeAlpha_ = contains_alpha, class Rhs_>
		constexpr inline this_type& operator+=(const Rhs_& rhs_)
		{
			validate_func()(colour.template operator+=<IncludeAlpha_>(_get_rhs(rhs_)));
			return *this;
		}

		template<bool IncludeAlpha_ = contains_alpha, class Rhs_>
		constexpr inline this_type& operator-=(const Rhs_& rhs_)
		{
			validate_func()(colour.template operator-=<IncludeAlpha_>(_get_rhs(rhs_)));
			return *this;
		}

		template<bool IncludeAlpha_ = contains_alpha, class Rhs_>
		constexpr inline this_type& operator*=(const Rhs_& rhs_)
		{
			validate_func()(colour.template operator*=<IncludeAlpha_>(_get_rhs(rhs_)));
			return *this;
		}

		template<bool IncludeAlpha_ = contains_alpha, class Rhs_>
		constexpr inline this_type& operator/=(const Rhs_& rhs_)
		{
			validate_func()(colour.template operator/=<IncludeAlpha_>(_get_rhs(rhs_)));
			return *this;
		}

		template<bool IncludeAlpha_ = contains_alpha, class Rhs_>
		constexpr inline this_type& operator%=(const Rhs_& rhs_)
		{
			validate_func()(colour.template operator%=<IncludeAlpha_>(_get_rhs(rhs_)));
			return *this;
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
		[[nodiscard]] constexpr inline _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func> Add(const Rhs_& rhs_) const
		{
			return _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func>
			(
				colour.template Add<out_contained_type, OutContainsAlpha_, IncludeAlpha_>(_get_rhs(rhs_))
			);
		}
		template<bool OutContainsAlpha_, bool IncludeAlpha_ = OutContainsAlpha_, class Rhs_>
		[[nodiscard]] constexpr inline _colour_validation_layer<value_type, OutContainsAlpha_, validate_func> Add(const Rhs_& rhs_) const
		{
			return _colour_validation_layer<value_type, OutContainsAlpha_, validate_func>
			(
				colour.template Add<value_type, OutContainsAlpha_, IncludeAlpha_>(_get_rhs(rhs_))
			);
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
		[[nodiscard]] constexpr inline _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func> Subtract(const Rhs_& rhs_) const
		{
			return _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func>
			(
				colour.template Subtract<out_contained_type, OutContainsAlpha_, IncludeAlpha_>(_get_rhs(rhs_))
			);
		}
		template<bool OutContainsAlpha_, bool IncludeAlpha_ = OutContainsAlpha_, class Rhs_>
		[[nodiscard]] constexpr inline _colour_validation_layer<value_type, OutContainsAlpha_, validate_func> Subtract(const Rhs_& rhs_) const
		{
			return _colour_validation_layer<value_type, OutContainsAlpha_, validate_func>
			(
				colour.template Subtract<value_type, OutContainsAlpha_, IncludeAlpha_>(_get_rhs(rhs_))
			);
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
		[[nodiscard]] constexpr inline _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func> Multiply(const Rhs_& rhs_) const
		{
			return _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func>
			(
				colour.template Multiply<out_contained_type, OutContainsAlpha_, IncludeAlpha_>(_get_rhs(rhs_))
			);
		}
		template<bool OutContainsAlpha_, bool IncludeAlpha_ = OutContainsAlpha_, class Rhs_>
		[[nodiscard]] constexpr inline _colour_validation_layer<value_type, OutContainsAlpha_, validate_func> Multiply(const Rhs_& rhs_) const
		{
			return _colour_validation_layer<value_type, OutContainsAlpha_, validate_func>
			(
				colour.template Multiply<value_type, OutContainsAlpha_, IncludeAlpha_>(_get_rhs(rhs_))
			);
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
		[[nodiscard]] constexpr inline _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func> Divide(const Rhs_& rhs_) const
		{
			return _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func>
			(
				colour.template Divide<out_contained_type, OutContainsAlpha_, IncludeAlpha_>(_get_rhs(rhs_))
			);
		}
		template<bool OutContainsAlpha_, bool IncludeAlpha_ = OutContainsAlpha_, class Rhs_>
		[[nodiscard]] constexpr inline _colour_validation_layer<value_type, OutContainsAlpha_, validate_func> Divide(const Rhs_& rhs_) const
		{
			return _colour_validation_layer<value_type, OutContainsAlpha_, validate_func>
			(
				colour.template Divide<value_type, OutContainsAlpha_, IncludeAlpha_>(_get_rhs(rhs_))
			);
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
		[[nodiscard]] constexpr inline _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func> Mod(const Rhs_& rhs_) const
		{
			return _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func>
			(
				colour.template Mod<out_contained_type, OutContainsAlpha_, IncludeAlpha_>(_get_rhs(rhs_))
			);
		}
		template<bool OutContainsAlpha_, bool IncludeAlpha_ = OutContainsAlpha_, class Rhs_>
		[[nodiscard]] constexpr inline _colour_validation_layer<value_type, OutContainsAlpha_, validate_func> Mod(const Rhs_& rhs_) const
		{
			return _colour_validation_layer<value_type, OutContainsAlpha_, validate_func>
			(
				colour.template Mod<value_type, OutContainsAlpha_, IncludeAlpha_>(_get_rhs(rhs_))
			);
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
		[[nodiscard]] constexpr inline _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func> Lerp(const ColourB_& b_, const T_& t_) const
		{
			return _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func>
			(
				colour.template Lerp<out_contained_type, OutContainsAlpha_, IncludeAlpha_>(_get_rhs(b_), _get_rhs(t_))
			);
		}
		template<bool OutContainsAlpha_, bool IncludeAlpha_ = OutContainsAlpha_, class ColourB_, class T_>
		[[nodiscard]] constexpr inline _colour_validation_layer<value_type, OutContainsAlpha_, validate_func> Lerp(const ColourB_& b_, const T_& t_) const
		{
			return _colour_validation_layer<value_type, OutContainsAlpha_, validate_func>
			(
				colour.template Lerp<OutContainsAlpha_, IncludeAlpha_>(_get_rhs(b_), _get_rhs(t_))
			);
		}
#pragma endregion

#pragma region CONVERSIONS
		/// <summary> Shorthand to construct this colour as an alternate channel representation. May optionally change if output contains an Alpha channel. </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output colour.</typeparam>
		/// <returns>This colour converted to one containing the provided channel type.</returns>
		template<typename out_contained_type, bool OutContainsAlpha_ = contains_alpha>
		[[nodiscard]] constexpr inline EmuMath::Helpers::_colour_validation_layer<out_contained_type, OutContainsAlpha_, ValidationFunc_> As() const
		{
			return EmuMath::Helpers::_colour_validation_layer<out_contained_type, OutContainsAlpha_, ValidationFunc_>(*this);
		}

		/// <summary> 
		///	Shorthand to construct this colour as an alternate channel representation, outside of a validation wrapper. 
		///	May optionally change if output contains an Alpha channel.
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output colour.</typeparam>
		/// <returns>This colour converted to one containing the provided channel type, without a validation layer.</returns>
		template<typename out_contained_type, bool OutContainsAlpha_ = contains_alpha>
		[[nodiscard]] constexpr inline EmuMath::Colour<out_contained_type, OutContainsAlpha_> AsUnvalidated() const
		{
			return colour.template As<out_contained_type, OutContainsAlpha_>();
		}

		/// <summary> Provides read-only access to this Colour's channels as an EmuMath Vector. </summary>
		/// <returns> Constant reference to this colour's underlying channels. </returns>
		[[nodiscard]] constexpr inline const channels_vector& AsVector() const
		{
			return colour.AsVector();
		}

		/// <summary> Provides read-only access to this Colour's RGB channels as an EmuMath Vector. </summary>
		/// <returns> EmuMath Vector representation of this colour's underlying channels in RGB format. </returns>
		[[nodiscard]] constexpr inline vector_rgb_return_type AsVectorRGB() const
		{
			return colour.AsVectorRGB();
		}

		/// <summary> Provides read-only access to this Colour's RGBA channels as an EmuMath Vector. </summary>
		/// <returns> EmuMath Vector representation of this colour's underlying channels in RGBA format. </returns>
		[[nodiscard]] constexpr inline vector_rgba_return_type AsVectorRGBA() const
		{
			return colour.AsVectorRGBA();
		}

		template<typename OutChannel_, bool OutContainsAlpha_>
		explicit constexpr inline operator EmuMath::Colour<OutChannel_, OutContainsAlpha_>() const
		{
			return EmuMath::Colour<OutChannel_, OutContainsAlpha_>(colour);
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
			return this_type(colour.template Inverse<IncludeAlpha_>(), 0);
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
			// If the colour is already valid, inversion will not make it invalid
			colour.template Invert<IncludeAlpha_>();
		}

		/// <summary> 
		/// <para> Returns a copy of this colour with all of its channels wrapped into a valid range. </para>
		/// <para> As this colour includes a validation layer, it is assumed to always be valid and as such this function will simply return a copy of this colour. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type used to store the output colour's channels. Defaults to this Colour's value_type./</typeparam>
		/// <returns>Copy of this colour with all channels wrapped into a valid intensity range.</returns>
		template<typename out_contained_type = value_type, bool OutContainsAlpha_ = contains_alpha>
		[[nodiscard]] constexpr inline _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func> Wrapped() const
		{
			if constexpr (std::is_same_v<out_contained_type, value_type> && OutContainsAlpha_ == contains_alpha)
			{
				return this_type(colour, 0);
			}
			else
			{
				return _colour_validation_layer<value_type, OutContainsAlpha_, validate_func>(colour);
			}
		}
		template<bool OutContainsAlpha_>
		[[nodiscard]] constexpr inline EmuMath::Colour<value_type, OutContainsAlpha_> Wrapped() const
		{
			if constexpr (OutContainsAlpha_ == contains_alpha)
			{
				return this_type(colour, 0);
			}
			else
			{
				return _colour_validation_layer<value_type, OutContainsAlpha_, validate_func>(colour);
			}
		}

		/// <summary> 
		/// <para> Wraps the stored channels within this colour instance so they are in a valid intensity range. </para>
		/// <para> As this colour includes a validation layer, it is assumed to always be valid and as such this function will do nothing. </para>
		/// </summary>
		constexpr inline void Wrap()
		{
		}

		/// <summary> 
		/// <para> Returns a copy of this colour with all of its channels clamped into the range min_intensity:max_intensity. </para>
		/// <para> As this colour includes a validation layer, it is assumed to always be valid and as such this function will simply return a copy of this colour. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type used to store the output colour's channels. Defaults to this Colour's value_type./</typeparam>
		/// <returns>Copy of this colour with all channels clamped into a valid intensity range.</returns>
		template<typename out_contained_type = value_type, bool OutContainsAlpha_ = contains_alpha>
		[[nodiscard]] constexpr inline EmuMath::Colour<out_contained_type, OutContainsAlpha_> Clamped() const
		{
			if constexpr (std::is_same_v<out_contained_type, value_type> && OutContainsAlpha_ == contains_alpha)
			{
				return this_type(colour, 0);
			}
			else
			{
				return _colour_validation_layer<value_type, OutContainsAlpha_, validate_func>(colour);
			}
		}
		template<bool OutContainsAlpha_>
		[[nodiscard]] constexpr inline EmuMath::Colour<value_type, OutContainsAlpha_> Clamped() const
		{
			if constexpr (OutContainsAlpha_ == contains_alpha)
			{
				return this_type(colour, 0);
			}
			else
			{
				return _colour_validation_layer<value_type, OutContainsAlpha_, validate_func>(colour);
			}
		}

		/// <summary>
		/// <para> Clamps the stored channels within this colour instance into the range min_intensity:max_intensity. </para>
		/// <para> As this colour includes a validation layer, it is assumed to always be valid and as such this function will do nothing. </para>
		/// </summary>
		inline void Clamp()
		{
		}

		/// <summary> Finds the lowest-valued channel within this Colour. Excludes Alpha by default, but may include it if provided a `true` template argument. </summary>
		/// <returns>Copy of the highest value stored within this Colour's channels.</returns>
		template<bool IncludeAlpha_ = false>
		[[nodiscard]] constexpr inline value_type Min() const
		{
			return colour.template Min<IncludeAlpha_>();
		}

		/// <summary> Finds the highest-valued channel within this Colour. Excludes Alpha by default, but may include it if provided a `true` template argument. </summary>
		/// <returns>Copy of the highest value stored within this Colour's channels.</returns>
		template<bool IncludeAlpha_ = false>
		[[nodiscard]] constexpr inline value_type Max() const
		{
			return colour.template Max<IncludeAlpha_>();
		}

		/// <summary> Returns a copy of this colour converted to greyscale using a basic average of its RGB channels. </summary>
		/// <returns>Copy of this channel with each channel set to the mean average of this colour's RGB channels.</returns>
		template<typename out_contained_type = value_type, bool OutContainsAlpha_ = contains_alpha>
		[[nodiscard]] constexpr inline _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func> GreyscaleBasic() const
		{
			// APPLIES TO ALL GREYSCALE FUNCTIONS UNLESS STATED OTHERWISE IN BODY:
			// --- As this wrapper is assumed to keep its contained colour valid, the result of grayscaling will also be valid
			// --- As such, we skip validation whenever possible.
			if constexpr (std::is_same_v<out_contained_type, value_type> && OutContainsAlpha_ == contains_alpha)
			{
				return this_type(colour.template GreyscaleBasic<out_contained_type, OutContainsAlpha_>(), 0);
			}
			else
			{
				return _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func>(colour.template GreyscaleBasic<out_contained_type, OutContainsAlpha_>());
			}
		}
		template<bool OutContainsAlpha_>
		[[nodiscard]] constexpr inline _colour_validation_layer<value_type, OutContainsAlpha_, validate_func> GreyscaleBasic() const
		{
			if constexpr (OutContainsAlpha_ == contains_alpha)
			{
				return this_type(colour.template GreyscaleBasic<OutContainsAlpha_>(), 0);
			}
			else
			{
				return _colour_validation_layer<value_type, OutContainsAlpha_, validate_func>(colour.template GreyscaleBasic<OutContainsAlpha_>());
			}
		}

		/// <summary> Returns a copy of this colour converted to greyscale using a luminance average of its RGB channels. </summary>
		/// <returns>Copy of this channel with each channel set to a scaled luminance average of this colour's RGB channels.</returns>
		template<typename out_contained_type = value_type, bool OutContainsAlpha_ = contains_alpha>
		[[nodiscard]] constexpr inline _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func> GreyscaleLuminance() const
		{
			if constexpr (std::is_same_v<out_contained_type, value_type> && OutContainsAlpha_ == contains_alpha)
			{
				return this_type(colour.template GreyscaleLuminance<out_contained_type, OutContainsAlpha_>(), 0);
			}
			else
			{
				return _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func>(colour.template GreyscaleLuminance<out_contained_type, OutContainsAlpha_>());
			}
		}
		template<bool OutContainsAlpha_>
		[[nodiscard]] constexpr inline _colour_validation_layer<value_type, OutContainsAlpha_, validate_func> GreyscaleLuminance() const
		{
			if constexpr (OutContainsAlpha_ == contains_alpha)
			{
				return this_type(colour.template GreyscaleLuminance<OutContainsAlpha_>(), 0);
			}
			else
			{
				return _colour_validation_layer<value_type, OutContainsAlpha_, validate_func>(colour.template GreyscaleLuminance<OutContainsAlpha_>());
			}
		}

		/// <summary> Returns a copy of this colour converted to greyscale via desaturation. </summary>
		/// <returns>Copy of this channel with each channel set to a value resulting from desaturating this colour's RGB channels.</returns>
		template<typename out_contained_type = value_type, bool OutContainsAlpha_ = contains_alpha>
		[[nodiscard]] constexpr inline _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func> GreyscaleDesaturate() const
		{
			if constexpr (std::is_same_v<out_contained_type, value_type> && OutContainsAlpha_ == contains_alpha)
			{
				return this_type(colour.template GreyscaleDesaturate<out_contained_type, OutContainsAlpha_>(), 0);
			}
			else
			{
				return _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func>(colour.template GreyscaleDesaturate<out_contained_type, OutContainsAlpha_>());
			}
		}
		template<bool OutContainsAlpha_>
		[[nodiscard]] constexpr inline _colour_validation_layer<value_type, OutContainsAlpha_, validate_func> GreyscaleDesaturate() const
		{
			if constexpr (OutContainsAlpha_ == contains_alpha)
			{
				return this_type(colour.template GreyscaleDesaturate<OutContainsAlpha_>(), 0);
			}
			else
			{
				return _colour_validation_layer<value_type, OutContainsAlpha_, validate_func>(colour.template GreyscaleDesaturate<OutContainsAlpha_>());
			}
		}

		/// <summary> Returns a copy of this colour converted to greyscale via its lowest RGB channel. </summary>
		/// <returns>Copy of this channel with each channel set to the value of this colour's lowest RGB channel.</returns>
		template<typename out_contained_type = value_type, bool OutContainsAlpha_ = contains_alpha>
		[[nodiscard]] constexpr inline _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func> GreyscaleMin() const
		{
			if constexpr (std::is_same_v<out_contained_type, value_type> && OutContainsAlpha_ == contains_alpha)
			{
				return this_type(colour.template GreyscaleMin<out_contained_type, OutContainsAlpha_>(), 0);
			}
			else
			{
				return _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func>(colour.template GreyscaleMin<out_contained_type, OutContainsAlpha_>());
			}
		}
		template<bool OutContainsAlpha_>
		[[nodiscard]] constexpr inline _colour_validation_layer<value_type, OutContainsAlpha_, validate_func> GreyscaleMin() const
		{
			if constexpr (OutContainsAlpha_ == contains_alpha)
			{
				return this_type(colour.template GreyscaleMin<OutContainsAlpha_>(), 0);
			}
			else
			{
				return _colour_validation_layer<value_type, OutContainsAlpha_, validate_func>(colour.template GreyscaleMin<OutContainsAlpha_>());
			}
		}

		/// <summary> Returns a copy of this colour converted to greyscale via its highest RGB channel. </summary>
		/// <returns>Copy of this channel with each channel set to the value of this colour's highest RGB channel.</returns>
		template<typename out_contained_type = value_type, bool OutContainsAlpha_ = contains_alpha>
		[[nodiscard]] constexpr inline _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func> GreyscaleMax() const
		{
			if constexpr (std::is_same_v<out_contained_type, value_type> && OutContainsAlpha_ == contains_alpha)
			{
				return this_type(colour.template GreyscaleMax<out_contained_type, OutContainsAlpha_>(), 0);
			}
			else
			{
				return _colour_validation_layer<out_contained_type, OutContainsAlpha_, validate_func>(colour.template GreyscaleMax<out_contained_type, OutContainsAlpha_>());
			}
		}
		template<bool OutContainsAlpha_>
		[[nodiscard]] constexpr inline _colour_validation_layer<value_type, OutContainsAlpha_, validate_func> GreyscaleMax() const
		{
			if constexpr (OutContainsAlpha_ == contains_alpha)
			{
				return this_type(colour.template GreyscaleMax<OutContainsAlpha_>(), 0);
			}
			else
			{
				return _colour_validation_layer<value_type, OutContainsAlpha_, validate_func>(colour.template GreyscaleMax<OutContainsAlpha_>());
			}
		}
#pragma endregion

		underlying_colour colour;

		template<class T_>
		struct _is_colour_validation_layer
		{
			static constexpr bool value = std::conditional_t
			<
				std::is_same_v<T_, std::remove_cv_t<T_>>,
				std::conditional_t
				<
					std::is_same_v<T_, std::remove_reference_t<T_>>,
					std::false_type,
					_is_colour_validation_layer<std::remove_reference_t<T_>>
				>,
				_is_colour_validation_layer<std::remove_cv_t<T_>>
			>::value;
		};
		template<class ChannelType__, bool ContainsAlpha__, class ValidationFunc__>
		struct _is_colour_validation_layer<EmuMath::Helpers::_colour_validation_layer<ChannelType__, ContainsAlpha__, ValidationFunc__>>
		{
			static constexpr bool value = true;
		};

		/// <summary>
		/// <para> Helper function for getting a reference to a colour if the rhs_ is a validation layer. Returns the passed reference if not. </para>
		/// </summary>
		template<class Rhs_>
		[[nodiscard]] static constexpr inline const auto& _get_rhs(const Rhs_& rhs_)
		{
			if constexpr (_is_colour_validation_layer<Rhs_>::value)
			{
				return rhs_.Get();
			}
			else
			{
				return rhs_;
			}
		}
	};
}

namespace EmuMath::TMP
{
	template<typename Channel_, bool ContainsAlpha_, class ValidationFunc_>
	struct is_emu_colour<EmuMath::Helpers::_colour_validation_layer<Channel_, ContainsAlpha_, ValidationFunc_>>
	{
		static constexpr bool value = true;
	};
}

template<typename T_, bool ContainsAlpha_, class ValidationFunc_>
std::ostream& operator<<(std::ostream& str_, const EmuMath::Helpers::_colour_validation_layer<T_, ContainsAlpha_, ValidationFunc_>& colour_)
{
	str_ << colour_.Get();
	return str_;
}

template<typename T_, bool ContainsAlpha_, class ValidationFunc_>
std::wostream& operator<<(std::wostream& str_, const EmuMath::Helpers::_colour_validation_layer<T_, ContainsAlpha_, ValidationFunc_>& colour_)
{
	str_ << colour_.Get();
	return str_;
}

#endif
