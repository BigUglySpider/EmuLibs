#ifndef EMU_MATH_NEW_VECTOR_T_H_INC_
#define EMU_MATH_NEW_VECTOR_T_H_INC_ 1

#include "_helpers/_vector_helpers.h"
#include <array>
#include <ostream>

namespace EmuMath
{
	/// <summary>
	/// <para> Mathematical Vector of any number of dimensions. </para>
	/// <para> 
	///		Provides support for Vectors of lvalue references.
	///		References to a type T are intended to be stored as vector_internal_ref&lt;T&gt;.
	///		As such, instantiations of `Vector&lt;size, T&amp;&gt;` are identical to instantiations of `Vector&lt;size, vector_internal_ref&lt;T&gt;&gt;`.
	/// </para>
	/// </summary>
	/// <typeparam name="T_">
	///		Type for this Vector to store.
	///		If T_ is an l-value reference type, it will be reinterpreted as `vector_internal_ref&lt;std::remove_ref_t&lt;T_&gt;&gt;`.
	/// </typeparam>
	template<std::size_t Size_, typename T_>
	struct NewVector
	{
#pragma region COMMON_STATIC_INFO
	public:
		using this_type = NewVector<Size_, T_>;
		using vector_info = EmuMath::TMP::common_vector_info<Size_, T_, true>;

		using stored_type = typename vector_info::stored_type;
		using value_type = typename vector_info::value_type;
		using value_type_uq = typename vector_info::value_type_uq;
		using alternative_rep = typename vector_info::alternative_vector_rep;
		friend typename alternative_rep;

		static constexpr std::size_t size = vector_info::size;
		static constexpr bool contains_ref = vector_info::contains_ref;
		static constexpr bool contains_const_ref = vector_info::contains_const_ref;
		static constexpr bool contains_non_const_ref = vector_info::contains_non_const_ref;
		static constexpr bool is_integral = vector_info::is_integral;
		static constexpr bool is_floating_point = vector_info::is_floating_point;
		static constexpr bool is_class = vector_info::is_class;
		static constexpr std::size_t element_byte_size = vector_info::element_byte_size;
		static constexpr bool is_default_constructible = vector_info::is_default_constructible;
		static constexpr bool has_alternative_representation = vector_info::has_alternative_representation;

		using data_storage_type = std::array<stored_type, size>;

		template<class...Args_>
		[[nodiscard]] static constexpr inline bool valid_template_construction_args()
		{
			return vector_info::template valid_template_construct_args<Args_...>();
		}

		template<std::size_t OtherSize_, typename OtherT_>
		[[nodiscard]] static constexpr inline bool valid_template_vector_copy_construct_arg()
		{
			return 
			(
				vector_info::template valid_template_vector_copy_construct_arg<OtherSize_, OtherT_>() &&
				!vector_info::template is_valid_lone_type_for_set_all_construction<EmuMath::NewVector<OtherSize_, OtherT_>&>()
			);
		}

		template<std::size_t OtherSize_, typename OtherT_>
		[[nodiscard]] static constexpr inline bool valid_template_vector_const_copy_construct_arg()
		{
			return 
			(
				vector_info::template valid_template_vector_const_copy_construct_arg<OtherSize_, OtherT_>() &&
				!vector_info::template is_valid_lone_type_for_set_all_construction<const EmuMath::NewVector<OtherSize_, OtherT_>&>()
			);
		}

		template<std::size_t OtherSize_, typename OtherT_>
		[[nodiscard]] static constexpr inline bool valid_template_vector_move_construct_arg()
		{
			return
			(
				vector_info::template valid_template_vector_move_construct_arg<OtherSize_, OtherT_>() &&
				!vector_info::template is_valid_lone_type_for_set_all_construction<EmuMath::NewVector<OtherSize_, OtherT_>&&>()
			);
		}

		template<std::size_t InSize_, typename InT_, bool in_is_const, bool in_is_temp>
		[[nodiscard]] static constexpr inline bool is_valid_vector_for_set()
		{
			return vector_info::template is_valid_vector_for_set<InSize_, InT_, in_is_const, in_is_temp>();
		}

		template<typename T_>
		[[nodiscard]] static constexpr inline bool is_valid_type_for_single_set()
		{
			return vector_info::template is_valid_type_for_single_set<T_>();
		}

		template<typename T_>
		[[nodiscard]] static constexpr inline bool is_valid_type_for_set_all()
		{
			return vector_info::template is_valid_type_for_set_all<T_>();
		}

		template<typename T_, bool WhileConst_>
		[[nodiscard]] static constexpr inline bool is_valid_try_get_output_ref()
		{
			return vector_info::template is_valid_try_get_output_ref<T_, WhileConst_>();
		}

		template<typename T_>
		[[nodiscard]] static constexpr inline bool is_valid_lone_type_for_set_all_construction()
		{
			return vector_info::template is_valid_lone_type_for_set_all_construction<T_>();
		}

		[[nodiscard]] static constexpr inline value_type_uq get_implied_zero()
		{
			return EmuMath::Helpers::new_vector_get_non_contained<this_type>();
		}

		template<typename Arg_>
		[[nodiscard]] static constexpr inline bool is_valid_template_copy_arg()
		{
			return vector_info::template is_valid_template_copy_arg<Arg_, false>();
		}

		template<typename Arg_>
		[[nodiscard]] static constexpr inline bool is_valid_template_assign_arg()
		{
			return vector_info::template is_valid_template_copy_arg<Arg_, true>();
		}

	private:
		struct _dummy_arg_for_private_constexpr_default
		{
			constexpr inline _dummy_arg_for_private_constexpr_default() {}
		};

		struct _dummy_arg_for_private_lazy_default
		{
			constexpr inline _dummy_arg_for_private_lazy_default() {}
		};

		using _dummy_arg_for_private_default = std::conditional_t
		<
			is_default_constructible,
			_dummy_arg_for_private_constexpr_default,
			_dummy_arg_for_private_lazy_default
		>;

		// Helper to decide if a type should be an EmuMath Vector of size Size__ and type T__, or void.
		// --- If std::is_void_v<T__> is true, the underlying type will be void; otherwise, it will be Vector<Size__, T__>.
		template<std::size_t Size__, typename T__, typename = void>
		struct _vector_or_void
		{
			using type = EmuMath::NewVector<Size__, T__>;
		};
		template<std::size_t Size__, typename T__>
		struct _vector_or_void<Size__, T__, std::enable_if_t<std::is_void_v<T__>>>
		{
			using type = void;
		};

		template<typename In_>
		[[nodiscard]] constexpr inline std::conditional_t<std::is_constructible_v<stored_type, In_>, In_&&, stored_type> _do_stored_type_construction(In_&& in_)
		{
			if constexpr (std::is_constructible_v<stored_type, In_>)
			{
				return std::forward<In_>(in_);
			}
			else if constexpr (std::is_convertible_v<In_, stored_type>)
			{
				return static_cast<stored_type>(in_);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<In_>(),
					"Attempted to construct an EmuMath Vector with an input type that is neither usable in construction of or conversion to the Vector's stored_type."
				);
			}
		}
#pragma endregion

#pragma region CONSTRUCTORS
	public:
		/// <summary>
		/// <para> Default constructs all elements within this Vector. </para>
		/// <para> This is only available for Vectors which contain default-constructible, non-reference types. </para>
		/// </summary>
		template<typename OnlyIfNonRefAndContainsDefaultConstructibles_ = std::enable_if_t<is_default_constructible>>
		constexpr inline NewVector() : _data()
		{
		}

		/// <summary>
		/// <para> Constructs a copy of the passed non-const Vector reference. </para>
		/// </summary>
		/// <param name="to_copy_">
		///		: Non-const reference to an EmuMath Vector to copy. If this vector contains references, it will reference the same data as the passed Vector.
		/// </param>
		constexpr inline NewVector(this_type& to_copy_) : _data(to_copy_._data)
		{
		}

		/// <summary>
		/// <para> Constructs a copy of the passed const Vector reference. </para>
		/// <para> This is only avaialble for Vectors which do not contain non-const references. </para>
		/// </summary>
		/// <param name="to_copy_">
		///		: Const reference to an EmuMath Vector to copy. If this vector contains references, it will reference the same data as the passed Vector.
		/// </param>
		template<typename = std::enable_if_t<!contains_non_const_ref>>
		constexpr inline NewVector(const this_type& to_copy_) : _data(to_copy_._data)
		{
		}

		/// <summary>
		/// <para> Moves the data of the passed Vector reference into a newly constructed Vector. </para>
		/// </summary>
		/// <param name="to_move_">: Vector to move into the newly constructed vector.</param>
		constexpr inline NewVector(this_type&& to_move_) noexcept : _data(std::move(to_move_._data))
		{
		}

		/// <summary>
		/// <para> 
		///		Constructs a copy of the passed non-const Vector reference,
		///		whose underlying structure is the same as this Vector but with different template arguments.
		/// </para>
		/// <para> This is only available for reference-containing Vectors, where has_alternative_representation is true. </para>
		/// <para> If this construction method is invalid, the input type for this constructor will be std::false_type. </para>
		/// </summary>
		/// <param name="to_copy_">
		///		: Non-const reference to an EmuMath Vector to copy. If this vector contains references, it will reference the same data as the passed Vector.
		/// </param>
		template<typename OnlyIfAlternativeRepExists_ = std::enable_if_t<has_alternative_representation>>
		constexpr inline NewVector(alternative_rep& to_copy_) : _data(to_copy_._data)
		{
		}

		/// <summary>
		/// <para> 
		///		Constructs a copy of the passed const Vector reference,
		///		whose underlying structure is the same as this Vector but with different template arguments.
		/// </para>
		/// <para> This is only available for const-reference-containing Vectors, where has_alternative_representation is true. </para>
		/// <para> If there is no alternative representation, the input type for this constructor will be std::false_type. </para>
		/// </summary>
		/// <param name="to_copy_">
		///		: Const reference to an EmuMath Vector to copy. If this vector contains references, it will reference the same data as the passed Vector.
		/// </param>
		template<typename OnlyIfAlternativeRepExists_ = std::enable_if_t<has_alternative_representation && !contains_non_const_ref>>
		constexpr inline NewVector(const alternative_rep& to_copy_) : _data(to_copy_._data)
		{
		}

		/// <summary>
		/// <para> 
		///		Moves the data of the passed Vector reference, whose underlying structure is the same as this Vector but with different template arguments,
		///		into a newly constructed Vector.
		/// </para>
		/// <para> This is only available for reference-containing Vectors, where has_alternative_representation is true. </para>
		/// <para> If there is no alternative representation, the input type for this constructor will be std::false_type. </para>
		/// </summary>
		/// <param name="to_move_">: EmuMath Vector to move into the newly constructed vector.</param>
		template<typename OnlyIfAlternativeRepExists_ = std::enable_if_t<has_alternative_representation>>
		constexpr inline NewVector(alternative_rep&& to_move_) noexcept : _data(std::move(to_move_._data))
		{
		}

		/// <summary>
		/// <para> Constructs a Vector with custom template arguments, where each argument is used to construct the respective element within the new Vector. </para>
		/// <para> Only 1 argument may be provided per element, and the provided number of arguments must be equal to this vector's size. </para>
		/// <para> Additionally, provided arguments must be valid for constructing this Vector's stored_type. </para>
		/// <para> Provided arguments represent elements in order from index 0 to the final index (e.g. 0, 1, 2...n-1 in a vector of size n). </para>
		/// </summary>
		/// <typeparam name="ConstructionArgs_">Types of all provided arguments provided for construction.</typeparam>
		/// <param name="construction_args_"> 
		///		: Ordered arguments representing respective elements within the constructed Vector, used to construct their respective element.
		/// </param>
		template
		<
			class...ConstructionArgs_,
			typename = std::enable_if_t<valid_template_construction_args<ConstructionArgs_...>()>
		>
		explicit constexpr inline NewVector(ConstructionArgs_&&...construction_args_) : 
			_data({ stored_type(std::forward<ConstructionArgs_>(construction_args_))... })
		{
		}

		/// <summary>
		/// <para> Constructs this Vector as a copy of the provided EmuMath Vector. </para>
		/// <para> If this Vector contains more elements than the passed Vector to_copy_, non-contained elements will be interpreted as implied zeroes. </para>
		/// <para> If this Vector contains references, the passed Vector to_copy_ must contain at least as many elements as this Vector. </para>
		/// </summary>
		/// <param name="to_copy_">: Non-constant reference to an EmuMath Vector to copy into the newly constructed Vector.</param>
		template
		<
			std::size_t OtherSize_,
			typename OtherT_,
			typename = std::enable_if_t<valid_template_vector_copy_construct_arg<OtherSize_, OtherT_>()>
		>
		explicit constexpr inline NewVector(EmuMath::NewVector<OtherSize_, OtherT_>& to_copy_) : NewVector(_dummy_arg_for_private_default())
		{
			EmuMath::Helpers::new_vector_set(*this, to_copy_);
		}

		/// <summary>
		/// <para> Constructs this Vector as a copy of the provided EmuMath Vector. </para>
		/// <para> If this Vector contains more elements than the passed Vector to_copy_, non-contained elements will be interpreted as implied zeroes. </para>
		/// <para> If this Vector contains references, the passed Vector to_copy_ must contain at least as many elements as this Vector. </para>
		/// <para> This constructor is not available for Vectors which contain non-const references.</para>
		/// </summary>
		/// <param name="to_copy_">: Constant reference to an EmuMath Vector to copy into the newly constructed Vector.</param>
		template
		<
			std::size_t OtherSize_,
			typename OtherT_,
			typename = std::enable_if_t<valid_template_vector_const_copy_construct_arg<OtherSize_, OtherT_>() && !contains_non_const_ref>
		>
		explicit constexpr inline NewVector(const EmuMath::NewVector<OtherSize_, OtherT_>& to_copy_) : NewVector(_dummy_arg_for_private_default())
		{
			EmuMath::Helpers::new_vector_set(*this, to_copy_);
		}

		/// <summary>
		/// <para> Constructs this Vector as a copy of the provided EmuMath Vector, which attempts to move its contained elements. </para>
		/// <para> If this Vector contains more elements than the passed Vector to_move_, non-contained elements will be interpreted as implied zeroes. </para>
		/// <para> If this Vector contains references, the passed Vector to_move_ must contain at least as many elements as this Vector. </para>
		/// <para> This constructor is not available for Vectors which contain non-const references. </para>
		/// </summary>
		/// <param name="to_move_">: rvalue reference to an EmuMath Vector to copy into the newly constructed Vector, with attempts to move used elements.</param>
		template
		<
			std::size_t OtherSize_,
			typename OtherT_,
			typename = std::enable_if_t<valid_template_vector_move_construct_arg<OtherSize_, OtherT_>()>
		>
		explicit constexpr inline NewVector(EmuMath::NewVector<OtherSize_, OtherT_>&& to_move_) : NewVector(_dummy_arg_for_private_default())
		{
			// Checks are here so that temporaries aren't resolved to the const copy constructor
			// --- This comes with the unfortunate effect that this constructor may appear usable in TMP in situations where it is not
			// ------ This is, however, considered better than allowing silent dangling references to form
			if constexpr (contains_ref)
			{
				if constexpr (!EmuMath::NewVector<OtherSize_, OtherT_>::contains_ref)
				{
					static_assert
					(
						EmuCore::TMP::get_false<OtherT_>(),
						"Attempted to construct a reference-containing EmuMath Vector via a temporary EmuMath Vector that does not contain references. This behaviour will result in dangling references, and has been prohibited as a result."
					);
				}
				else
				{
					EmuMath::Helpers::new_vector_set(*this, std::move(to_move_));
				}
			}
			else
			{
				EmuMath::Helpers::new_vector_set(*this, std::move(to_move_));
			}
		}

		template
		<
			typename InT_,
			typename = std::enable_if_t<is_valid_lone_type_for_set_all_construction<InT_&&>()>
		>
		explicit constexpr inline NewVector(InT_&& to_set_all_to_) : NewVector(_dummy_arg_for_private_default())
		{
			SetAll(std::forward<InT_>(to_set_all_to_));
		}

		template
		<
			typename InT_,
			typename = std::enable_if_t<is_valid_lone_type_for_set_all_construction<InT_&>()>
		>
		explicit constexpr inline NewVector(InT_& to_set_all_to_) : NewVector(_dummy_arg_for_private_default())
		{
			SetAll(to_set_all_to_);
		}

		template
		<
			typename InT_,
			typename = std::enable_if_t<is_valid_lone_type_for_set_all_construction<const InT_&>()>
		>
		explicit constexpr inline NewVector(const InT_& to_set_all_to_) : NewVector(_dummy_arg_for_private_default())
		{
			SetAll(to_set_all_to_);
		}

	private:
		// Empty constructor used to perform a lazy-default when construction is executed within the constructor body; inaccessible out of this struct
		// --- Only available when we cannot default construct
		// --- Disable warning about uninitialised data since that's the point of this constructor
#pragma warning(disable : 26495)
		explicit constexpr inline NewVector(_dummy_arg_for_private_lazy_default dummy_arg_)
		{
		}
		// Empty constructor used to perform a default-construction when full construction is executed within the constructor body; inaccessible out of this struct
		// --- Only available when we can default construct
		explicit constexpr inline NewVector(_dummy_arg_for_private_constexpr_default dummy_arg_) : NewVector()
		{
		}
#pragma endregion

#pragma region ACCESS
	public:
		/// <summary>
		/// <para> Provides safe access to the provided Index_ within this Vector. If the Index_ is invalid, a compile-time error will be generated. </para>
		/// </summary>
		/// <returns>Reference to the element at the provided index within this Vector.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline value_type& at()
		{
			if constexpr (Index_ < size)
			{
				return std::get<Index_>(_data);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, Index_>(),
					"Attempted to access an element at an invalid Index_ within an EmuMath Vector via its template `at<Index_>` member. Valid indices are in the inclusive range 0:size-1."
				);
			}
		}
		/// <summary>
		/// <para> Provides safe const access to the provided Index_ within this Vector. If the Index_ is invalid, a compile-time error will be generated. </para>
		/// </summary>
		/// <returns>Const reference to the element at the provided index within this Vector.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline const value_type& at() const
		{
			return const_cast<this_type*>(this)->template at<Index_>();
		}

		/// <summary>
		/// <para> Provides access to the provided Index_ within this Vector. If the Index_ is invalid, behaviour is undefined. </para>
		/// <para> If the provided index_ is known at compile-time, it is recommended to use the template version of this function to enforce index safety. </para>
		/// </summary>
		/// <returns>Reference to the element at the provided index within this Vector.</returns>
		[[nodiscard]] constexpr inline value_type& at(const std::size_t index_)
		{
			return _data.at(index_);
		}
		/// <summary>
		/// <para> Provides const access to the provided Index_ within this Vector. If the Index_ is invalid, behaviour is undefined. </para>
		/// <para> If the provided index_ is known at compile-time, it is recommended to use the template version of this function to enforce index safety. </para>
		/// </summary>
		/// <returns>Reference to the element at the provided index within this Vector.</returns>
		[[nodiscard]] constexpr inline const value_type& at(const std::size_t index_) const
		{
			return const_cast<this_type*>(this)->at(index_);
		}
		/// <summary>
		/// <para> Provides access to the provided Index_ within this Vector. If the Index_ is invalid, behaviour is undefined. </para>
		/// <para> If the provided index_ is known at compile-time, it is recommended to use the template version of the `at` function to enforce index safety. </para>
		/// </summary>
		/// <returns>Reference to the element at the provided index within this Vector.</returns>
		[[nodiscard]] constexpr inline value_type& operator[](const std::size_t index_)
		{
			return at(index_);
		}
		/// <summary>
		/// <para> Provides const access to the provided Index_ within this Vector. If the Index_ is invalid, behaviour is undefined. </para>
		/// <para> If the provided index_ is known at compile-time, it is recommended to use the template version of the `at` function to enforce index safety. </para>
		/// </summary>
		/// <returns>Reference to the element at the provided index within this Vector.</returns>
		[[nodiscard]] constexpr inline const value_type& operator[](const std::size_t index_) const
		{
			return at(index_);
		}

		/// <summary>
		/// <para> Returns the item theoretically stored at the provided index within this Vector. </para>
		/// <para> If Index_ is a valid contained index within this Vector (0:size-1, inclusive): Returns a value_type reference to the item at the provided Index_. </para>
		/// <para> If none of the above is true: Returns an implied-zero, newly constructed value_type_uq. </para>
		/// </summary>
		/// <returns>Result of `at&lt;Index_&gt;()` if Index_ is a valid contained index in this Vector; otherwise, result of `get_implied_zero()`.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline EmuMath::TMP::emu_vector_theoretical_return_t<Index_, this_type> AtTheoretical()
		{
			return EmuMath::Helpers::new_vector_get_theoretical<Index_>(*this);
		}
		/// <summary>
		/// <para> Returns the item theoretically stored at the provided index within this Vector. </para>
		/// <para> If Index_ is a valid contained index within this Vector (0:size-1, inclusive): Returns a const value_type reference to the item at the provided Index_. </para>
		/// <para> If none of the above is true: Returns an implied-zero, newly constructed value_type_uq. </para>
		/// </summary>
		/// <returns>Result of `at&lt;Index_&gt;()` if Index_ is a valid contained index in this Vector; otherwise, result of `get_implied_zero()`.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline EmuMath::TMP::emu_vector_theoretical_return_t<Index_, const this_type> AtTheoretical() const
		{
			return EmuMath::Helpers::new_vector_get_theoretical<Index_>(*this);
		}

		/// <summary>
		/// <para> Attempts to retrieve the specified index_ within this Vector, outputting the element via out_ if the index_ is valid. </para>
		/// <para>
		///		Out_ must be assignable, convertible-to, or constructible from a reference to this Vector's value_type. 
		///		Assignment will be prioritised over conversion, and conversion will be prioritised over construction.
		/// </para>
		/// </summary>
		/// <typeparam name="Out_">Type of reference provided to output to via out_.</typeparam>
		/// <param name="index_">: Index to try and retrieve an element from within this Vector.</param>
		/// <param name="out_"> 
		///		: Reference to output to if the get is successful. Must be assignable, convertible-to, or constructible from a reference to this Vector's value_type.
		/// </param>
		/// <returns>True if the provided index is valid, otherwise false.</returns>
		template<typename Out_, typename = std::enable_if_t<is_valid_try_get_output_ref<Out_, false>()>>
		[[nodiscard]] constexpr inline bool TryAt(const std::size_t index_, Out_& out_)
		{
			return EmuMath::Helpers::vector_try_get<Out_, Size_, T_>(*this, index_, out_);
		}
		/// <summary>
		/// <para> Attempts to retrieve the specified index_ within this Vector, outputting the element via out_ if the index_ is valid. </para>
		/// <para>
		///		Out_ must be assignable, convertible-to, or constructible from a reference to this Vector's value_type. 
		///		Assignment will be prioritised over conversion, and conversion will be prioritised over construction.
		/// </para>
		/// </summary>
		/// <typeparam name="Out_">Type of reference provided to output to via out_.</typeparam>
		/// <param name="index_">: Index to try and retrieve an element from within this Vector.</param>
		/// <param name="out_"> 
		///		: Reference to output to if the get is successful. Must be assignable, convertible-to, or constructible from a const reference to this Vector's value_type.
		/// </param>
		/// <returns>True if the provided index is valid, otherwise false.</returns>
		template<typename Out_, typename = std::enable_if_t<is_valid_try_get_output_ref<Out_, true>()>>
		[[nodiscard]] constexpr inline bool TryAt(const std::size_t index_, Out_& out_) const
		{
			return EmuMath::Helpers::vector_try_get<Out_, Size_, T_>(*this, index_, out_);
		}

		/// <summary>
		/// <para> 
		///		Attempts to retrieve the specified index_ within this Vector,
		///		outputting a pointer to the element to the pointer pointed to by pp_out_
		/// </para>
		/// <para> If index_ is a valid index: The pointer pointed to by pp_out_ will be set to point to the element at the provided index in this Vector. </para>
		/// <para> If index_ is an invalid index: The pointer pointed to by pp_out_ will be set to nullptr if NullptrIfFailed_ is true; otherwise it will be unmodified. </para>
		/// </summary>
		/// <param name="index_">: Index to try and retrieve a pointer to within this Vector.</param>
		/// <param name="pp_out_">Non-const pointer to the pointer to output to.</param>
		/// <returns>True if the provided index is valid, otherwise false.</returns>
		template<bool NullptrIfFailed_ = false>
		[[nodiscard]] constexpr inline bool TryAt(const std::size_t index_, value_type** pp_out_)
		{
			return EmuMath::Helpers::vector_try_get<NullptrIfFailed_, Size_, T_>(*this, index_, pp_out_);
		}
		/// <summary>
		/// <para> 
		///		Attempts to retrieve the specified index_ within this Vector,
		///		outputting a const pointer to the element to the pointer pointed to by pp_const_out_.
		/// </para>
		/// <para> If index_ is a valid index: The const pointer pointed to by pp_const_out_ will be set to point to the element at the provided index in this Vector. </para>
		/// <para> 
		///		If index_ is an invalid index: The const pointer pointed to by pp_const_out_ will be set to nullptr if NullptrIfFailed_ is true; 
		///		otherwise it will be unmodified.
		/// </para>
		/// </summary>
		/// <param name="index_">: Index to try and retrieve a constant pointer to within this Vector.</param>
		/// <param name="pp_const_out_">Const pointer to the pointer to output to.</param>
		/// <returns>True if the provided index is valid, otherwise false.</returns>
		template<bool NullptrIfFailed_ = false>
		[[nodiscard]] constexpr inline bool TryAt(const std::size_t index_, const value_type** pp_const_out_) const
		{
			return EmuMath::Helpers::vector_try_get<NullptrIfFailed_, Size_, T_>(*this, index_, pp_const_out_);
		}

		/// <summary>
		/// <para> Shorthand for `TryAt` with the same arguments and const state. </para>
		/// <para> Attempts to retrieve the specified index_ within this Vector, outputting the element via out_ if the index_ is valid. </para>
		/// <para>
		///		Out_ must be assignable, convertible-to, or constructible from a reference to this Vector's value_type. 
		///		Assignment will be prioritised over conversion, and conversion will be prioritised over construction.
		/// </para>
		/// </summary>
		/// <typeparam name="Out_">Type of reference provided to output to via out_.</typeparam>
		/// <param name="index_">: Index to try and retrieve an element from within this Vector.</param>
		/// <param name="out_"> 
		///		: Reference to output to if the get is successful. Must be assignable, convertible-to, or constructible from a reference to this Vector's value_type.
		/// </param>
		/// <returns>True if the provided index is valid, otherwise false.</returns>
		template<typename Out_, typename = std::enable_if_t<is_valid_try_get_output_ref<Out_, false>()>>
		[[nodiscard]] constexpr inline bool operator()(const std::size_t index_, Out_& out_)
		{
			return TryAt(index_, out_);
		}
		/// <summary>
		/// <para> Shorthand for `TryAt` with the same arguments and const state. </para>
		/// <para> Attempts to retrieve the specified index_ within this Vector, outputting the element via out_ if the index_ is valid. </para>
		/// <para>
		///		Out_ must be assignable, convertible-to, or constructible from a reference to this Vector's value_type. 
		///		Assignment will be prioritised over conversion, and conversion will be prioritised over construction.
		/// </para>
		/// </summary>
		/// <typeparam name="Out_">Type of reference provided to output to via out_.</typeparam>
		/// <param name="index_">: Index to try and retrieve an element from within this Vector.</param>
		/// <param name="out_"> 
		///		: Reference to output to if the get is successful. Must be assignable, convertible-to, or constructible from a const reference to this Vector's value_type.
		/// </param>
		/// <returns>True if the provided index is valid, otherwise false.</returns>
		template<typename Out_, typename = std::enable_if_t<is_valid_try_get_output_ref<Out_, true>()>>
		[[nodiscard]] constexpr inline bool operator()(const std::size_t index_, Out_& out_) const
		{
			return TryAt(index_, out_);
		}

		/// <summary>
		/// <para> Shorthand for `TryAt` with the same arguments. </para>
		/// <para> 
		///		Attempts to retrieve the specified index_ within this Vector,
		///		outputting a pointer to the element to the pointer pointed to by pp_out_
		/// </para>
		/// <para> If index_ is a valid index: The pointer pointed to by pp_out_ will be set to point to the element at the provided index in this Vector. </para>
		/// <para> If index_ is an invalid index: The pointer pointed to by pp_out_ will be set to nullptr if NullptrIfFailed_ is true; otherwise it will be unmodified. </para>
		/// </summary>
		/// <param name="index_">: Index to try and retrieve a pointer to within this Vector.</param>
		/// <param name="pp_out_">Non-const pointer to the pointer to output to.</param>
		/// <returns>True if the provided index is valid, otherwise false.</returns>
		template<bool NullptrIfFailed_ = false>
		[[nodiscard]] constexpr inline bool operator()(const std::size_t index_, value_type** pp_out_)
		{
			return TryAt<NullptrIfFailed_>(index_, pp_out_);
		}
		/// <summary>
		/// <para> Shorthand for `TryAt` with the same arguments. </para>
		/// <para> 
		///		Attempts to retrieve the specified index_ within this Vector,
		///		outputting a const pointer to the element to the pointer pointed to by pp_const_out_.
		/// </para>
		/// <para> If index_ is a valid index: The const pointer pointed to by pp_const_out_ will be set to point to the element at the provided index in this Vector. </para>
		/// <para> 
		///		If index_ is an invalid index: The const pointer pointed to by pp_const_out_ will be set to nullptr if NullptrIfFailed_ is true; 
		///		otherwise it will be unmodified.
		/// </para>
		/// </summary>
		/// <param name="index_">: Index to try and retrieve a constant pointer to within this Vector.</param>
		/// <param name="pp_const_out_">Const pointer to the pointer to output to.</param>
		/// <returns>True if the provided index is valid, otherwise false.</returns>
		template<bool NullptrIfFailed_ = false>
		[[nodiscard]] constexpr inline bool operator()(const std::size_t index_, const value_type** pp_const_out_) const
		{
			return TryAt<NullptrIfFailed_>(index_, pp_const_out_);
		}

		/// <summary>
		/// <para> Provides a pointer to the start of contiguous data within this Vector. </para>
		/// <para> If this Vector contains references, this will generate a compile-time error, since contiguous data is not guaranteed to be referenced. </para>
		/// </summary>
		/// <returns>Pointer to the 0th element within this Vector.</returns>
		[[nodiscard]] constexpr inline stored_type* data()
		{
			if constexpr (!contains_ref)
			{
				return _data.data();
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<T_>(),
					"Attempted to access a contiguous data pointer of an EmuMath Vector which contains references. This behaviour is prohibited."
				);
			}
		}
		/// <summary>
		/// <para> Provides a const pointer to the start of contiguous data within this Vector. </para>
		/// <para> If this Vector contains references, this will generate a compile-time error, since contiguous data is not guaranteed to be referenced. </para>
		/// </summary>
		/// <returns>Const pointer to the 0th element within this Vector.</returns>
		[[nodiscard]] constexpr inline const stored_type* data() const
		{
			return const_cast<this_type*>(this)->data();
		}

		/// <summary>
		/// <para> Provides a pointer to the start of contiguous data within this Vector from the specified Index_. </para>
		/// <para> If this Vector contains references, this will generate a compile-time error, since contiguous data is not guaranteed to be referenced. </para>
		/// </summary>
		/// <returns>Pointer to the start of the element within this Vector at the provided Index_.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline stored_type* data()
		{
			if constexpr (Index_ < size)
			{
				return data() + Index_;
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, Index_>(),
					"Attempted to access a contiguous data pointer of an EmuMath Vector from a specified Index_, but the provided Index_ was invalid. The valid index range is 0:size-1 (inclusive)."
				);
			}
		}
		/// <summary>
		/// <para> Provides a const pointer to the start of contiguous data within this Vector from the specified Index_. </para>
		/// <para> If this Vector contains references, this will generate a compile-time error, since contiguous data is not guaranteed to be referenced. </para>
		/// </summary>
		/// <returns>Const pointer to the start of the element within this Vector at the provided Index_.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline const stored_type* data() const
		{
			return const_cast<this_type*>(this)->template data<Index_>();
		}
#pragma endregion

#pragma region ASSIGNMENT_OPERATORS
	public:
		constexpr inline this_type& operator=(this_type&& to_move_) noexcept
		{
			_data = std::move(to_move_._data);
			return *this;
		}

		template<typename = std::enable_if_t<has_alternative_representation>>
		constexpr inline this_type& operator=(alternative_rep&& to_move_) noexcept
		{
			_data = std::move(to_move_._data);
			return *this;
		}

		constexpr inline this_type& operator=(this_type& to_copy_)
		{
			if constexpr (contains_ref)
			{
				Copy(to_copy_);
			}
			else
			{
				_data = to_copy_._data;
			}
			return *this;
		}
		template<typename = std::enable_if_t<has_alternative_representation>>
		constexpr inline this_type& operator=(alternative_rep& to_copy_)
		{
			if constexpr (contains_ref)
			{
				Copy(to_copy_);
			}
			else
			{
				_data = to_copy_._data;
			}
			return *this;
		}

		constexpr inline this_type& operator=(const this_type& to_copy_)
		{
			if constexpr (contains_ref)
			{
				Copy(to_copy_);
			}
			else
			{
				_data = to_copy_._data;
			}
			return *this;
		}
		template<typename = std::enable_if_t<has_alternative_representation>>
		constexpr inline this_type& operator=(const alternative_rep& to_copy_)
		{
			if constexpr (contains_ref)
			{
				Copy(to_copy_);
			}
			else
			{
				_data = to_copy_._data;
			}
			return *this;
		}

		template<class Arg_, typename = std::enable_if_t<is_valid_template_assign_arg<Arg_>()>>
		constexpr inline this_type& operator=(Arg_& to_copy_)
		{
			Copy(to_copy_);
			return *this;
		}
		template<class Arg_, typename = std::enable_if_t<is_valid_template_assign_arg<const Arg_>()>>
		constexpr inline this_type& operator=(const Arg_& to_copy_)
		{
			Copy(to_copy_);
			return *this;
		}
#pragma endregion

#pragma region UNARY_ARITHMETIC_OPERATORS
	public:
		// INCREMENT OPERATORS
		constexpr inline this_type& operator++()
		{
			return EmuMath::Helpers::new_vector_pre_increment(*this);
		}
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> operator++()
		{
			return EmuMath::Helpers::new_vector_pre_increment<OutSize_, OutT_>(*this);
		}
		template<typename OutT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> operator++()
		{
			return EmuMath::Helpers::new_vector_pre_increment<size, OutT_>(*this);
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> operator++(int)
		{
			return EmuMath::Helpers::new_vector_post_increment<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		constexpr inline typename _vector_or_void<size, OutT_>::type operator++(int)
		{
			if constexpr (std::is_void_v<OutT_>)
			{
				EmuMath::Helpers::new_vector_post_increment_no_copy(*this);
			}
			else
			{
				return EmuMath::Helpers::new_vector_post_increment<size, OutT_>(*this);
			}
		}

		// DECREMENT OPERATORS
		constexpr inline this_type& operator--()
		{
			return EmuMath::Helpers::new_vector_pre_decrement(*this);
		}
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> operator--()
		{
			return EmuMath::Helpers::new_vector_pre_decrement<OutSize_, OutT_>(*this);
		}
		template<typename OutT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> operator--()
		{
			return EmuMath::Helpers::new_vector_pre_decrement<size, OutT_>(*this);
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> operator--(int)
		{
			return EmuMath::Helpers::new_vector_post_decrement<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline typename _vector_or_void<size, OutT_>::type operator--(int)
		{
			if constexpr (std::is_void_v<OutT_>)
			{
				EmuMath::Helpers::new_vector_post_decrement_no_copy(*this);
			}
			else
			{
				return EmuMath::Helpers::new_vector_post_decrement<size, OutT_>(*this);
			}
		}
		
		// NEGATION OPERATORS
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> operator-() const
		{
			return EmuMath::Helpers::new_vector_negate<OutSize_, OutT_>(*this);
		}

		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> operator-() const
		{
			return EmuMath::Helpers::new_vector_negate<size, OutT_>(*this);
		}
#pragma endregion

#pragma region UNARY_ARITHMETIC_FUNCS
		/// <summary>
		/// <para> Peforms a pre-increment on this Vector, equivalent to `++this_vector`. </para>
		/// </summary>
		/// <returns>Reference to this Vector if no template args are provided; otherwise, a copy of this Vector after the increment.</returns>
		constexpr inline this_type& PreIncrement()
		{
			return EmuMath::Helpers::new_vector_pre_increment(*this);
		}
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> PreIncrement()
		{
			return EmuMath::Helpers::new_vector_pre_increment<OutSize_, OutT_>(*this);
		}
		template<typename OutT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> PreIncrement()
		{
			return EmuMath::Helpers::new_vector_pre_increment<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Performs a post-increment on this Vector, equivalent to `this_vector++`. </para>
		/// <para> Creating an unwanted copy may be avoided by passing `void` as the only template argument. </para>
		/// </summary>
		/// <returns>Copy of this Vector before the increment if not provided with only `void` as a template argument; otherwise, no return.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> PostIncrement()
		{
			return EmuMath::Helpers::new_vector_post_increment<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		constexpr inline typename _vector_or_void<size, OutT_>::type PostIncrement()
		{
			if constexpr (std::is_void_v<OutT_>)
			{
				EmuMath::Helpers::new_vector_post_increment_no_copy(*this);
			}
			else
			{
				return EmuMath::Helpers::new_vector_post_increment<size, OutT_>(*this);
			}
		}

		/// <summary>
		/// <para> Peforms a pre-decrement on this Vector, equivalent to `--this_vector`. </para>
		/// </summary>
		/// <returns>Reference to this Vector if no template args are provided; otherwise, a copy of this Vector after the decrement.</returns>
		constexpr inline this_type& PreDecrement()
		{
			return EmuMath::Helpers::new_vector_pre_decrement(*this);
		}
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> PreDecrement()
		{
			return EmuMath::Helpers::new_vector_pre_decrement<OutSize_, OutT_>(*this);
		}
		template<typename OutT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> PreDecrement()
		{
			return EmuMath::Helpers::new_vector_pre_decrement<size, OutT_>();
		}

		/// <summary>
		/// <para> Performs a post-decrement on this Vector, equivalent to `this_vector--`. </para>
		/// <para> Creating an unwanted copy may be avoided by passing `void` as the only template argument. </para>
		/// </summary>
		/// <returns>Copy of this Vector before the decrement if not provided with only `void` as a template argument; otherwise, no return.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> PostDecrement()
		{
			return EmuMath::Helpers::new_vector_post_decrement<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		constexpr inline typename _vector_or_void<size, OutT_>::type PostDecrement()
		{
			if constexpr (std::is_void_v<OutT_>)
			{
				EmuMath::Helpers::new_vector_post_decrement_no_copy(*this);
			}
			else
			{
				return EmuMath::Helpers::new_vector_post_decrement<size, OutT_>(*this);
			}
		}

		/// <summary> Returns a negated form of this Vector, equivalent to `-this_vector`. </summary>
		/// <returns>Copy of this Vector with its elements negated, using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq).</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Negate() const
		{
			return EmuMath::Helpers::new_vector_negate<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Negate() const
		{
			return EmuMath::Helpers::new_vector_negate<size, OutT_>(*this);
		}
		
		/// <summary> Ouputs a negated form of this Vector to the provided out_vector_, equivalent to `out_vector_ = -this_vector`. </summary>
		/// <param name="out_vector_">: EmuMath Vector to output the negated form of this Vector to.</param>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void Negate(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::new_vector_negate(out_vector_, *this);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with the provided index range negated. </para>
		/// <para> BeginIndex_: Inclusive index at which to start negating elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop negating elements. </para>
		/// </summary>
		/// <returns>
		///		EmuMath Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq),
		///		containing a copy of this Vector with the provided index range negated.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> NegateRange() const
		{
			return EmuMath::Helpers::new_vector_negate_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> NegateRange() const
		{
			return EmuMath::Helpers::new_vector_negate_range<size, OutT_, BeginIndex_, EndIndex_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with the provided index range negated, to the provided out_vector_. </para>
		/// <para> BeginIndex_: Inclusive index at which to start negating elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop negating elements. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_>
		constexpr inline void NegateRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::new_vector_negate_range<BeginIndex_, EndIndex_>(out_vector_, *this);
		}

		/// <summary>
		/// <para>
		///		Returns a new EmuMath Vector with its indices outside of the specified range index default-constructed, 
		///		and elements within the provided range constructed as negated forms of this Vector's elements, starting at index NegateBegin_.
		/// </para>
		/// <para> OutBegin_: Inclusive index in the output vector at which to start writing negated forms of this Vector's elements. </para>
		/// <para> OutEnd_: Exclusive index in the output vector at which to stop writing negated forms of this Vector's elements. </para>
		/// <para> NegateBegin_: Inclusive index at which to start reading elements from this Vector in order to perform negations. </para>
		/// </summary>
		/// <returns>
		///		EmuMath Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq),
		///		containing a partial negated copy of this Vector in the specified range, and default values outside of said range.
		/// </returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t NegateBegin_, std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> NegateRangeNoCopy() const
		{
			return EmuMath::Helpers::new_vector_negate_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, NegateBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t NegateBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> NegateRangeNoCopy() const
		{
			return EmuMath::Helpers::new_vector_negate_range_no_copy<size, OutT_, OutBegin, OutEnd_, NegateBegin_>(*this);
		}

		/// <summary>
		/// <para> Outputs sequential negated elements within this Vector, starting at index RoundBegin_, to the provided index range in out_vector_.
		/// </para>
		/// <para> Indices outside of the specified range in out_vector_ will not be modified. </para>
		/// <para> OutBegin_: Inclusive index in the output vector at which to start writing negated forms of this Vector's elements. </para>
		/// <para> OutEnd_: Exclusive index in the output vector at which to stop writing negated forms of this Vector's elements. </para>
		/// <para> NegateBegin_: Inclusive index at which to start reading elements from this Vector in order to perform negations. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t NegateBegin_, std::size_t OutSize_, typename OutT_>
		constexpr inline void NegateRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::new_vector_negate_range_no_copy<OutBegin_, OutEnd_, NegateBegin_>(out_vector_, *this);
		}
#pragma endregion

#pragma region MISC_ARITHMETIC_FUNCS
		/// <summary> Returns the absolute form of this Vector. </summary>
		/// <returns>Copy of this Vector with its elements made absolute, using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq).</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Abs() const
		{
			return EmuMath::Helpers::new_vector_abs<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Abs() const
		{
			return EmuMath::Helpers::new_vector_abs<size, OutT_>(*this);
		}

		/// <summary> Outputs the absolute form of this Vector to the provided out_vector_. </summary>
		/// <param name="out_vector_">: EmuMath Vector to output absolute elements to.</param>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void Abs(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::new_vector_abs(out_vector_, *this);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with the provided index range converted to absolute form. </para>
		/// <para> BeginIndex_: Inclusive index at which to start converting elements to absolute forms. </para>
		/// <para> EndIndex_: Exclusive index at which to stop converting elements to absolute forms. </para>
		/// </summary>
		/// <returns>
		///		EmuMath Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq),
		///		containing a copy of this Vector with the provided index range converted to absolute form.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> AbsRange() const
		{
			return EmuMath::Helpers::new_vector_abs_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> AbsRange() const
		{
			return EmuMath::Helpers::new_vector_abs_range<size, OutT_, BeginIndex_, EndIndex_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with the provided index range converted to absolute form, to the provided out_vector_. </para>
		/// <para> BeginIndex_: Inclusive index at which to start converting elements to absolute forms. </para>
		/// <para> EndIndex_: Exclusive index at which to stop converting elements to absolute forms. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_>
		constexpr inline void AbsRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::new_vector_abs_range<BeginIndex_, EndIndex_>(out_vector_, *this);
		}

		/// <summary>
		/// <para>
		///		Returns a new EmuMath Vector with its indices outside of the specified range index default-constructed, 
		///		and elements within the provided range constructed as absolute forms of this Vector's elements, starting at index AbsBegin_.
		/// </para>
		/// <para> OutBegin_: Inclusive index in the output vector at which to start writing absolute forms of this Vector's elements. </para>
		/// <para> OutEnd_: Exclusive index in the output vector at which to stop writing absolute forms of this Vector's elements. </para>
		/// <para> AbsBegin_: Inclusive index at which to start reading elements from this Vector in order to perform absolute conversions. </para>
		/// </summary>
		/// <returns>
		///		EmuMath Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq),
		///		containing a partial absolute copy of this Vector in the specified range, and default values outside of said range.
		/// </returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AbsBegin_, std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> AbsRangeNoCopy() const
		{
			return EmuMath::Helpers::new_vector_abs_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, AbsBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t AbsBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> AbsRangeNoCopy() const
		{
			return EmuMath::Helpers::new_vector_abs_range_no_copy<size, OutT_, OutBegin, OutEnd_, AbsBegin_>(*this);
		}

		/// <summary>
		/// <para> Outputs sequential absolute forms of this Vector's elements, starting at index AbsBegin_, to the provided index range in out_vector_. </para>
		/// <para> Indices outside of the specified range in out_vector_ will not be modified. </para>
		/// <para> OutBegin_: Inclusive index in the output vector at which to start writing absolute forms of this Vector's elements. </para>
		/// <para> OutEnd_: Exclusive index in the output vector at which to stop writing absolute forms of this Vector's elements. </para>
		/// <para> AbsBegin_: Inclusive index at which to start reading elements from this Vector in order to perform absolute conversions. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AbsBegin_, std::size_t OutSize_, typename OutT_>
		constexpr inline void AbsRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::new_vector_abs_range_no_copy<OutBegin_, OutEnd_, AbsBegin_>(out_vector_, *this);
		}

		/// <summary>
		/// <para> Returns the result of linearly interpolating this Vector with the provided b_ and t_ args, summarised as `a + ((b - a) * t). </para>
		/// <para> If either b_ or t_ is an EmuMath Vector, respective indices in said Vector(s) will be used for interpolation arguments. </para>
		/// </summary>
		/// <param name="b_">Scalar or EmuMath Vector to use as target point(s) for interpolation.</param>
		/// <param name="t_">Scalar or EmuMath Vector to use as weighting(s) for interpolation.</param>
		/// <returns>EmuMath Vector of the provided OutSize (defaults to size) and OutT_ (defaults to value_type_uq) containing interpolation results.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename ArgB_, typename ArgT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Lerp(ArgB_&& b_, ArgT_&& t_) const
		{
			return EmuMath::Helpers::new_vector_lerp<OutSize_, OutT_>(*this, std::forward<ArgB_>(b_), std::forward<ArgT_>(t_));
		}
		template<typename OutT_ = value_type_uq, typename ArgB_, typename ArgT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Lerp(ArgB_&& b_, ArgT_&& t_) const
		{
			return EmuMath::Helpers::new_vector_lerp<size, OutT_>(*this, std::forward<ArgB_>(b_), std::forward<ArgT_>(t_));
		}

		/// <summary>
		/// <para> Outputs the result of linearly interpolating this Vector with the provided b_ and t_ args, summarised as `a + ((b - a) * t), to out_vector_. </para>
		/// <para> If either b_ or t_ is an EmuMath Vector, respective indices in said Vector(s) will be used for interpolation arguments. </para>
		/// </summary>
		/// <param name="out_vector_">EmuMath Vector to output to.</param>
		/// <param name="b_">Scalar or EmuMath Vector to use as target point(s) for interpolation.</param>
		/// <param name="t_">Scalar or EmuMath Vector to use as weighting(s) for interpolation.</param>
		template<typename ArgB_, typename ArgT_, std::size_t OutSize_, typename OutT_>
		constexpr inline void Lerp(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, ArgB_&& b_, ArgT_&& t_) const
		{
			EmuMath::Helpers::new_vector_lerp(out_vector_, *this, std::forward<ArgB_>(b_), std::forward<ArgT_>(t_));
		}

		/// <summary>
		/// <para> 
		///		Returns a copy of this Vector, with indices in the provided range set to the result of linearly interpolating this Vector with the provided b_ and t_ args,
		///		summarised as `a + ((b - a) * t).
		/// </para>
		/// <para> If either b_ or t_ is an EmuMath Vector, respective indices in said Vector(s) will be used for interpolation arguments. </para>
		/// </summary>
		/// <param name="b_">Scalar or EmuMath Vector to use as target point(s) for interpolation.</param>
		/// <param name="t_">Scalar or EmuMath Vector to use as weighting(s) for interpolation.</param>
		/// <returns>EmuMath Vector copy of this Vector, with the provided index range linearly interpolated.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, typename ArgB_, typename ArgT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> LerpRange(ArgB_&& b_, ArgT_&& t_) const
		{
			return EmuMath::Helpers::new_vector_lerp_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<ArgB_>(b_), std::forward<ArgT_>(t_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename ArgB_, typename ArgT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> LerpRange(ArgB_&& b_, ArgT_&& t_) const
		{
			return EmuMath::Helpers::new_vector_lerp_range<size, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<ArgB_>(b_), std::forward<ArgT_>(t_));
		}

		/// <summary>
		/// <para> 
		///		Outputs a copy of this Vector to the provided out_vector_,
		///		with indices in the provided range set to the result of linearly interpolating this Vector with the provided b_ and t_ args, summarised as `a + ((b - a) * t).
		/// </para>
		/// <para> If either b_ or t_ is an EmuMath Vector, respective indices in said Vector(s) will be used for interpolation arguments. </para>
		/// </summary>
		/// <param name="out_vector_">EmuMath Vector to output to.</param>
		/// <param name="b_">Scalar or EmuMath Vector to use as target point(s) for interpolation.</param>
		/// <param name="t_">Scalar or EmuMath Vector to use as weighting(s) for interpolation.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_, typename ArgB_, typename ArgT_>
		constexpr inline void LerpRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, ArgB_&& b_, ArgT_&& t_) const
		{
			EmuMath::Helpers::new_vector_lerp_range<BeginIndex_, EndIndex_>(out_vector_, *this, std::forward<ArgB_>(b_), std::forward<ArgT_>(t_));
		}


		/// <summary>
		/// <para> 
		///		Returns the results of linearly interpolating this Vector with the provided b_ and t_ args, starting from index LerpBegin_,
		///		summarised as `a + ((b - a) * t), to the provided index range within an EmuMath Vector.
		/// </para>
		/// <para> If either b_ or t_ is an EmuMath Vector, respective indices in said Vector(s) will be used for interpolation arguments. </para>
		/// <para> Indices outside of the specified range will be default-constructed. </para>
		/// <para> OutBegin_: Inclusive index in the output vector at which to start writing interpolation results. </para>
		/// <para> OutEnd_: Exclusive index in the output vector at which to stop writing interpolation results. </para>
		/// <para> AbsBegin_: Inclusive index at which to start reading elements from this Vector (and Vector args) to perform interpolations. </para>
		/// </summary>
		/// <param name="b_">Scalar or EmuMath Vector to use as target point(s) for interpolation.</param>
		/// <param name="t_">Scalar or EmuMath Vector to use as weighting(s) for interpolation.</param>
		/// <returns>EmuMath Vector with results of linearly interpolating this vector with the provided arguments in the specified index range, and defaults elsewhere.</returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t LerpBegin_, std::size_t OutSize_, typename OutT_ = value_type_uq, typename ArgB_, typename ArgT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> LerpRangeNoCopy(ArgB_&& b_, ArgT_&& t_) const
		{
			return EmuMath::Helpers::new_vector_lerp_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, LerpBegin_>(*this, std::forward<ArgB_>(b_), std::forward<ArgT_>(t_));
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t LerpBegin_, typename OutT_ = value_type_uq, typename ArgB_, typename ArgT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> LerpRangeNoCopy(ArgB_&& b_, ArgT_&& t_) const
		{
			return EmuMath::Helpers::new_vector_lerp_range_no_copy<size, OutT_, OutBegin, OutEnd_, LerpBegin_>(*this, std::forward<ArgB_>(b_), std::forward<ArgT_>(t_));
		}

		/// <summary>
		/// <para> 
		///		Outputs the results of linearly interpolating this Vector with the provided b_ and t_ args, starting from index LerpBegin_,
		///		summarised as `a + ((b - a) * t), to the provided index range within the passed out_vector_.
		/// </para>
		/// <para> If either b_ or t_ is an EmuMath Vector, respective indices in said Vector(s) will be used for interpolation arguments. </para>
		/// <para> Indices outside of the specified range will not be modified. </para>
		/// <para> OutBegin_: Inclusive index in the output vector at which to start writing interpolation results. </para>
		/// <para> OutEnd_: Exclusive index in the output vector at which to stop writing interpolation results. </para>
		/// <para> AbsBegin_: Inclusive index at which to start reading elements from this Vector (and Vector args) to perform interpolations. </para>
		/// </summary>
		/// <param name="out_vector_">EmuMath Vector to output to.</param>
		/// <param name="b_">Scalar or EmuMath Vector to use as target point(s) for interpolation.</param>
		/// <param name="t_">Scalar or EmuMath Vector to use as weighting(s) for interpolation.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t LerpBegin_, std::size_t OutSize_, typename OutT_, typename ArgB_, typename ArgT_>
		constexpr inline void LerpRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, ArgB_&& b_, ArgT_&& t_) const
		{
			EmuMath::Helpers::new_vector_lerp_range_no_copy<OutBegin_, OutEnd_, LerpBegin_>(out_vector_, *this, std::forward<ArgB_>(b_), std::forward<ArgT_>(t_));
		}
#pragma endregion

#pragma region ROUNDING_FUNCS
		/// <summary>
		/// <para> Returns a copy of this Vector with its elements rounded toward negative infinity. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `FloorConstexpr` instead. </para>
		/// </summary>
		/// <returns>Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq>, containing a floored copy of this Vector.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Floor() const
		{
			return EmuMath::Helpers::new_vector_floor<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Floor() const
		{
			return EmuMath::Helpers::new_vector_floor<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with its elements rounded toward negative infinity, to the provided out_vector_. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `FloorConstexpr` instead. </para>
		/// </summary>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void Floor(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::new_vector_ceil(out_vector_, *this);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with the provided index range rounded toward negative infinity. </para>
		/// <para> BeginIndex_: Inclusive index at which to start rounding elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop rounding elements. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `FloorRangeConstexpr` instead. </para>
		/// </summary>
		/// <returns>
		///		EmuMath Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq),
		///		containing a copy of this Vector with the provided index range floored.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> FloorRange() const
		{
			return EmuMath::Helpers::new_vector_floor_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> FloorRange() const
		{
			return EmuMath::Helpers::new_vector_floor_range<size, OutT_, BeginIndex_, EndIndex_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with the provided index range rounded toward negative infinity, to the provided out_vector_. </para>
		/// <para> BeginIndex_: Inclusive index at which to start rounding elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop rounding elements. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `FloorRangeConstexpr` instead. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_>
		constexpr inline void FloorRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::new_vector_floor_range<BeginIndex_, EndIndex_>(out_vector_, *this);
		}

		/// <summary>
		/// <para>
		///		Returns a new EmuMath Vector with its indices outside of the specified range index default-constructed, 
		///		and elements within the provided range constructed as floored forms of this Vector's elements, starting at index RoundBegin_.
		/// </para>
		/// <para> OutBegin_: Inclusive index in the output vector at which to start writing rounded forms of this Vector's elements. </para>
		/// <para> OutEnd_: Exclusive index in the output vector at which to stop writing rounded forms of this Vector's elements. </para>
		/// <para> RoundBegin_: Inclusive index at which to start reading elements from this Vector in order to perform rounds. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `FloorRangeNoCopyConstexpr` instead. </para>
		/// </summary>
		/// <returns>
		///		EmuMath Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq),
		///		containing a partial floored copy of this Vector in the specified range, and default values outside of said range.
		/// </returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t RoundBegin_, std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> FloorRangeNoCopy() const
		{
			return EmuMath::Helpers::new_vector_floor_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, RoundBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t RoundBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> FloorRangeNoCopy() const
		{
			return EmuMath::Helpers::new_vector_floor_range_no_copy<size, OutT_, OutBegin, OutEnd_, RoundBegin_>(*this);
		}

		/// <summary>
		/// <para> Outputs sequential floored elements within this Vector, starting at index RoundBegin_, to the provided index range in out_vector_. </para>
		/// <para> Indices outside of the specified range in out_vector_ will not be modified. </para>
		/// <para> OutBegin_: Inclusive index in the output vector at which to start writing rounded forms of this Vector's elements. </para>
		/// <para> OutEnd_: Exclusive index in the output vector at which to stop writing rounded forms of this Vector's elements. </para>
		/// <para> RoundBegin_: Inclusive index at which to start reading elements from this Vector in order to perform rounds. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `FloorRangeNoCopyConstexpr` instead. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t RoundBegin_, std::size_t OutSize_, typename OutT_>
		constexpr inline void FloorRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::new_vector_floor_range_no_copy<OutBegin_, OutEnd_, RoundBegin_>(out_vector_, *this);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with its elements rounded toward positive infinity. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `CeilConstexpr` instead. </para>
		/// </summary>
		/// <returns>Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq>, containing a ceiled copy of this Vector.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Ceil() const
		{
			return EmuMath::Helpers::new_vector_ceil<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Ceil() const
		{
			return EmuMath::Helpers::new_vector_ceil<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with its elements rounded toward positive infinity, to the provided out_vector_. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `CeilConstexpr` instead. </para>
		/// </summary>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void Ceil(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::new_vector_ceil(out_vector_, *this);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with the provided index range rounded toward positive infinity. </para>
		/// <para> BeginIndex_: Inclusive index at which to start rounding elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop rounding elements. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `CeilRangeConstexpr` instead. </para>
		/// </summary>
		/// <returns>
		///		EmuMath Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq),
		///		containing a copy of this Vector with the provided index range ceiled.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> CeilRange() const
		{
			return EmuMath::Helpers::new_vector_ceil_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> CeilRange() const
		{
			return EmuMath::Helpers::new_vector_ceil_range<size, OutT_, BeginIndex_, EndIndex_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with the provided index range rounded toward positive infinity, to the provided out_vector_. </para>
		/// <para> BeginIndex_: Inclusive index at which to start rounding elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop rounding elements. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `CeilRangeConstexpr` instead. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_>
		constexpr inline void CeilRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::new_vector_ceil_range<BeginIndex_, EndIndex_>(out_vector_, *this);
		}

		/// <summary>
		/// <para>
		///		Returns a new EmuMath Vector with its indices outside of the specified range index default-constructed, 
		///		and elements within the provided range constructed as ceiled forms of this Vector's elements, starting at index RoundBegin_.
		/// </para>
		/// <para> OutBegin_: Inclusive index in the output vector at which to start writing rounded forms of this Vector's elements. </para>
		/// <para> OutEnd_: Exclusive index in the output vector at which to stop writing rounded forms of this Vector's elements. </para>
		/// <para> RoundBegin_: Inclusive index at which to start reading elements from this Vector in order to perform rounds. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `CeilRangeNoCopyConstexpr` instead. </para>
		/// </summary>
		/// <returns>
		///		EmuMath Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq),
		///		containing a partial ceiled copy of this Vector in the specified range, and default values outside of said range.
		/// </returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t RoundBegin_, std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> CeilRangeNoCopy() const
		{
			return EmuMath::Helpers::new_vector_ceil_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, RoundBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t RoundBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> CeilRangeNoCopy() const
		{
			return EmuMath::Helpers::new_vector_ceil_range_no_copy<size, OutT_, OutBegin, OutEnd_, RoundBegin_>(*this);
		}

		/// <summary>
		/// <para> Outputs sequential ceiled elements within this Vector, starting at index RoundBegin_, to the provided index range in out_vector_. </para>
		/// <para> Indices outside of the specified range in out_vector_ will not be modified. </para>
		/// <para> OutBegin_: Inclusive index in the output vector at which to start writing rounded forms of this Vector's elements. </para>
		/// <para> OutEnd_: Exclusive index in the output vector at which to stop writing rounded forms of this Vector's elements. </para>
		/// <para> RoundBegin_: Inclusive index at which to start reading elements from this Vector in order to perform rounds. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `CeilRangeNoCopyConstexpr` instead. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t RoundBegin_, std::size_t OutSize_, typename OutT_>
		constexpr inline void CeilRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::new_vector_ceil_range_no_copy<OutBegin_, OutEnd_, RoundBegin_>(out_vector_, *this);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with its elements rounded toward 0. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `TruncConstexpr` instead. </para>
		/// </summary>
		/// <returns>Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq>, containing a truncated copy of this Vector.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Trunc() const
		{
			return EmuMath::Helpers::new_vector_trunc<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Trunc() const
		{
			return EmuMath::Helpers::new_vector_trunc<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with its elements rounded toward 0, to the provided out_vector_. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `TruncConstexpr` instead. </para>
		/// </summary>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void Trunc(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::new_vector_trunc(out_vector_, *this);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with the provided index range rounded toward 0. </para>
		/// <para> BeginIndex_: Inclusive index at which to start rounding elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop rounding elements. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `TruncRangeConstexpr` instead. </para>
		/// </summary>
		/// <returns>
		///		EmuMath Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq),
		///		containing a copy of this Vector with the provided index range truncated.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> TruncRange() const
		{
			return EmuMath::Helpers::new_vector_trunc_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> TruncRange() const
		{
			return EmuMath::Helpers::new_vector_trunc_range<size, OutT_, BeginIndex_, EndIndex_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with the provided index range rounded toward 0, to the provided out_vector_. </para>
		/// <para> BeginIndex_: Inclusive index at which to start rounding elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop rounding elements. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `TruncRangeConstexpr` instead. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_>
		constexpr inline void TruncRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::new_vector_trunc_range<BeginIndex_, EndIndex_>(out_vector_, *this);
		}

		/// <summary>
		/// <para>
		///		Returns a new EmuMath Vector with its indices outside of the specified range index default-constructed, 
		///		and elements within the provided range constructed as truncated forms of this Vector's elements, starting at index RoundBegin_.
		/// </para>
		/// <para> OutBegin_: Inclusive index in the output vector at which to start writing rounded forms of this Vector's elements. </para>
		/// <para> OutEnd_: Exclusive index in the output vector at which to stop writing rounded forms of this Vector's elements. </para>
		/// <para> RoundBegin_: Inclusive index at which to start reading elements from this Vector in order to perform rounds. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `TruncRangeNoCopyConstexpr` instead. </para>
		/// </summary>
		/// <returns>
		///		EmuMath Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq),
		///		containing a partial truncated copy of this Vector in the specified range, and default values outside of said range.
		/// </returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t RoundBegin_, std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> TruncRangeNoCopy() const
		{
			return EmuMath::Helpers::new_vector_trunc_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, RoundBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t RoundBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> TruncRangeNoCopy() const
		{
			return EmuMath::Helpers::new_vector_trunc_range_no_copy<size, OutT_, OutBegin, OutEnd_, RoundBegin_>(*this);
		}

		/// <summary>
		/// <para> Outputs sequential truncated elements within this Vector, starting at index RoundBegin_, to the provided index range in out_vector_. </para>
		/// <para> Indices outside of the specified range in out_vector_ will not be modified. </para>
		/// <para> OutBegin_: Inclusive index in the output vector at which to start writing rounded forms of this Vector's elements. </para>
		/// <para> OutEnd_: Exclusive index in the output vector at which to stop writing rounded forms of this Vector's elements. </para>
		/// <para> RoundBegin_: Inclusive index at which to start reading elements from this Vector in order to perform rounds. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `TruncRangeNoCopyConstexpr` instead. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t RoundBegin_, std::size_t OutSize_, typename OutT_>
		constexpr inline void TruncRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::new_vector_trunc_range_no_copy<OutBegin_, OutEnd_, RoundBegin_>(out_vector_, *this);
		}
#pragma endregion

#pragma region CONSTEXPR_ROUNDING_FUNCS
		/// <summary>
		/// <para> Returns a copy of this Vector with its elements rounded toward negative infinity. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `Floor` if calling at runtime. </para>
		/// </summary>
		/// <returns>Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq>, containing a floored copy of this Vector.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> FloorConstexpr() const
		{
			return EmuMath::Helpers::new_vector_floor_constexpr<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> FloorConstexpr() const
		{
			return EmuMath::Helpers::new_vector_floor_constexpr<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with its elements rounded toward negative infinity, to the provided out_vector_. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `Floor` if calling at runtime. </para>
		/// </summary>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void FloorConstexpr(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			return EmuMath::Helpers::new_vector_floor_constexpr(out_vector_, *this);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with the provided index range rounded toward negative infinity. </para>
		/// <para> BeginIndex_: Inclusive index at which to start rounding elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop rounding elements. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `FloorRange` if calling at runtime. </para>
		/// </summary>
		/// <returns>
		///		EmuMath Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq),
		///		containing a copy of this Vector with the provided index range floored.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> FloorRangeConstexpr() const
		{
			return EmuMath::Helpers::new_vector_floor_range_constexpr<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> FloorRangeConstexpr() const
		{
			return EmuMath::Helpers::new_vector_floor_range_constexpr<size, OutT_, BeginIndex_, EndIndex_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with the provided index range rounded toward negative infinity, to the provided out_vector_. </para>
		/// <para> BeginIndex_: Inclusive index at which to start rounding elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop rounding elements. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `FloorRange` if calling at runtime. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_>
		constexpr inline void FloorRangeConstexpr(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::new_vector_floor_range_constexpr<BeginIndex_, EndIndex_>(out_vector_, *this);
		}

		/// <summary>
		/// <para>
		///		Returns a new EmuMath Vector with its indices outside of the specified range index default-constructed, 
		///		and elements within the provided range constructed as floored forms of this Vector's elements, starting at index RoundBegin_.
		/// </para>
		/// <para> OutBegin_: Inclusive index in the output vector at which to start writing rounded forms of this Vector's elements. </para>
		/// <para> OutEnd_: Exclusive index in the output vector at which to stop writing rounded forms of this Vector's elements. </para>
		/// <para> RoundBegin_: Inclusive index at which to start reading elements from this Vector in order to perform rounds. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `FloorRangeNoCopy` if calling at runtime. </para>
		/// </summary>
		/// <returns>
		///		EmuMath Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq),
		///		containing a partial floored copy of this Vector in the specified range, and default values outside of said range.
		/// </returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t RoundBegin_, std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> FloorRangeNoCopyConstexpr() const
		{
			return EmuMath::Helpers::new_vector_floor_range_no_copy_constexpr<OutSize_, OutT_, OutBegin_, OutEnd_, RoundBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t RoundBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> FloorRangeNoCopyConstexpr() const
		{
			return EmuMath::Helpers::new_vector_floor_range_no_copy_constexpr<size, OutT_, OutBegin, OutEnd_, RoundBegin_>(*this);
		}

		/// <summary>
		/// <para> Outputs sequential floored elements within this Vector, starting at index RoundBegin_, to the provided index range in out_vector_. </para>
		/// <para> Indices outside of the specified range in out_vector_ will not be modified. </para>
		/// <para> OutBegin_: Inclusive index in the output vector at which to start writing rounded forms of this Vector's elements. </para>
		/// <para> OutEnd_: Exclusive index in the output vector at which to stop writing rounded forms of this Vector's elements. </para>
		/// <para> RoundBegin_: Inclusive index at which to start reading elements from this Vector in order to perform rounds. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `FloorRangeNoCopy` if calling at runtime. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t RoundBegin_, std::size_t OutSize_, typename OutT_>
		constexpr inline void FloorRangeNoCopyConstexpr(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::new_vector_floor_range_no_copy_constexpr<OutBegin_, OutEnd_, RoundBegin_>(out_vector_, *this);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with its elements rounded toward positive infinity. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `Ceil` if calling at runtime. </para>
		/// </summary>
		/// <returns>Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq>, containing a ceiled copy of this Vector.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> CeilConstexpr() const
		{
			return EmuMath::Helpers::new_vector_ceil_constexpr<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> CeilConstexpr() const
		{
			return EmuMath::Helpers::new_vector_ceil_constexpr<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with its elements rounded toward positive infinity, to the provided out_vector_. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `Ceil` if calling at runtime. </para>
		/// </summary>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void CeilConstexpr(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			return EmuMath::Helpers::new_vector_ceil_constexpr(out_vector_, *this);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with the provided index range rounded toward positive infinity. </para>
		/// <para> BeginIndex_: Inclusive index at which to start rounding elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop rounding elements. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `CeilRange` if calling at runtime. </para>
		/// </summary>
		/// <returns>
		///		EmuMath Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq),
		///		containing a copy of this Vector with the provided index range ceiled.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> CeilRangeConstexpr() const
		{
			return EmuMath::Helpers::new_vector_ceil_range_constexpr<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> CeilRangeConstexpr() const
		{
			return EmuMath::Helpers::new_vector_ceil_range_constexpr<size, OutT_, BeginIndex_, EndIndex_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with the provided index range rounded toward positive infinity, to the provided out_vector_. </para>
		/// <para> BeginIndex_: Inclusive index at which to start rounding elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop rounding elements. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `CeilRange` if calling at runtime. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_>
		constexpr inline void CeilRangeConstexpr(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::new_vector_ceil_range_constexpr<BeginIndex_, EndIndex_>(out_vector_, *this);
		}

		/// <summary>
		/// <para>
		///		Returns a new EmuMath Vector with its indices outside of the specified range index default-constructed, 
		///		and elements within the provided range constructed as ceiled forms of this Vector's elements, starting at index RoundBegin_.
		/// </para>
		/// <para> OutBegin_: Inclusive index in the output vector at which to start writing rounded forms of this Vector's elements. </para>
		/// <para> OutEnd_: Exclusive index in the output vector at which to stop writing rounded forms of this Vector's elements. </para>
		/// <para> RoundBegin_: Inclusive index at which to start reading elements from this Vector in order to perform rounds. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `CeilRangeNoCopy` if calling at runtime. </para>
		/// </summary>
		/// <returns>
		///		EmuMath Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq),
		///		containing a partial ceiled copy of this Vector in the specified range, and default values outside of said range.
		/// </returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t RoundBegin_, std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> CeilRangeNoCopyConstexpr() const
		{
			return EmuMath::Helpers::new_vector_ceil_range_no_copy_constexpr<OutSize_, OutT_, OutBegin_, OutEnd_, RoundBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t RoundBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> CeilRangeNoCopyConstexpr() const
		{
			return EmuMath::Helpers::new_vector_ceil_range_no_copy_constexpr<size, OutT_, OutBegin, OutEnd_, RoundBegin_>(*this);
		}

		/// <summary>
		/// <para> Outputs sequential ceiled elements within this Vector, starting at index RoundBegin_, to the provided index range in out_vector_. </para>
		/// <para> Indices outside of the specified range in out_vector_ will not be modified. </para>
		/// <para> OutBegin_: Inclusive index in the output vector at which to start writing rounded forms of this Vector's elements. </para>
		/// <para> OutEnd_: Exclusive index in the output vector at which to stop writing rounded forms of this Vector's elements. </para>
		/// <para> RoundBegin_: Inclusive index at which to start reading elements from this Vector in order to perform rounds. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `CeilRangeNoCopy` if calling at runtime. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t RoundBegin_, std::size_t OutSize_, typename OutT_>
		constexpr inline void CeilRangeNoCopyConstexpr(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::new_vector_ceil_range_no_copy_constexpr<OutBegin_, OutEnd_, RoundBegin_>(out_vector_, *this);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with its elements rounded toward 0. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `Trunc` if calling at runtime. </para>
		/// </summary>
		/// <returns>Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq>, containing a truncated copy of this Vector.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> TruncConstexpr() const
		{
			return EmuMath::Helpers::new_vector_trunc_constexpr<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> TruncConstexpr() const
		{
			return EmuMath::Helpers::new_vector_trunc_constexpr<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with its elements rounded toward 0, to the provided out_vector_. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `Trunc` if calling at runtime. </para>
		/// </summary>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void TruncConstexpr(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			return EmuMath::Helpers::new_vector_trunc_constexpr(out_vector_, *this);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with the provided index range rounded toward 0. </para>
		/// <para> BeginIndex_: Inclusive index at which to start rounding elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop rounding elements. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `TruncRange` if calling at runtime. </para>
		/// </summary>
		/// <returns>
		///		EmuMath Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq),
		///		containing a copy of this Vector with the provided index range truncated.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> TruncRangeConstexpr() const
		{
			return EmuMath::Helpers::new_vector_trunc_range_constexpr<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> TruncRangeConstexpr() const
		{
			return EmuMath::Helpers::new_vector_trunc_range_constexpr<size, OutT_, BeginIndex_, EndIndex_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with the provided index range rounded toward 0, to the provided out_vector_. </para>
		/// <para> BeginIndex_: Inclusive index at which to start rounding elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop rounding elements. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `TruncRange` if calling at runtime. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_>
		constexpr inline void TruncRangeConstexpr(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::new_vector_trunc_range_constexpr<BeginIndex_, EndIndex_>(out_vector_, *this);
		}

		/// <summary>
		/// <para>
		///		Returns a new EmuMath Vector with its indices outside of the specified range index default-constructed, 
		///		and elements within the provided range constructed as truncated forms of this Vector's elements, starting at index RoundBegin_.
		/// </para>
		/// <para> OutBegin_: Inclusive index in the output vector at which to start writing rounded forms of this Vector's elements. </para>
		/// <para> OutEnd_: Exclusive index in the output vector at which to stop writing rounded forms of this Vector's elements. </para>
		/// <para> RoundBegin_: Inclusive index at which to start reading elements from this Vector in order to perform rounds. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `TruncRangeNoCopy` if calling at runtime. </para>
		/// </summary>
		/// <returns>
		///		EmuMath Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq),
		///		containing a partial truncated copy of this Vector in the specified range, and default values outside of said range.
		/// </returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t RoundBegin_, std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> TruncRangeNoCopyConstexpr() const
		{
			return EmuMath::Helpers::new_vector_trunc_range_no_copy_constexpr<OutSize_, OutT_, OutBegin_, OutEnd_, RoundBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t RoundBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> TruncRangeNoCopyConstexpr() const
		{
			return EmuMath::Helpers::new_vector_trunc_range_no_copy_constexpr<size, OutT_, OutBegin, OutEnd_, RoundBegin_>(*this);
		}

		/// <summary>
		/// <para> Outputs sequential truncated elements within this Vector, starting at index RoundBegin_, to the provided index range in out_vector_. </para>
		/// <para> Indices outside of the specified range in out_vector_ will not be modified. </para>
		/// <para> OutBegin_: Inclusive index in the output vector at which to start writing rounded forms of this Vector's elements. </para>
		/// <para> OutEnd_: Exclusive index in the output vector at which to stop writing rounded forms of this Vector's elements. </para>
		/// <para> RoundBegin_: Inclusive index at which to start reading elements from this Vector in order to perform rounds. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `TruncRangeNoCopy` if calling at runtime. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t RoundBegin_, std::size_t OutSize_, typename OutT_>
		constexpr inline void TruncRangeNoCopyConstexpr(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::new_vector_trunc_range_no_copy_constexpr<OutBegin_, OutEnd_, RoundBegin_>(out_vector_, *this);
		}
#pragma endregion

#pragma region SHUFFLES
	public:
		/// <summary>
		/// <para> Creates an EmuMath Vector containing the specified OutT_ (defaults to value_type_uq) from elements within this Vector. </para>
		/// <para> The size of the output Vector will be equal to the number of provided Indices_ args. </para>
		/// <para>
		///		Indices_: Variadic sequence of 1 or more indices within this Vector to use to form the element for the output Vector's index at that arg's position. 
		///		(e.g. with the args 2, 4, 0, the result will be out[0] = this[2], out[1] = this[4], out[2] = this[0]).
		/// </para>
		/// <para> At least one Indices_ arg must be provided. </para>
		/// <para> This can be used to output a shuffled reference Vector, but it is recommended to use RefShuffle instead. </para>
		/// <para> This may not be used to shuffle theoretical indices. For such behaviour, use ShuffleTheoretical. </para>
		/// </summary>
		/// <typeparam name="OutT_">Type to be contained in the output Vector. Defaults to this Vector's value_type_uq if not provided.</typeparam>
		/// <returns>
		///		EmuMath Vector containing the provided OutT_ (defaults to value_type_uq), containing a number of indices equal to the number of provided Indices_ args, 
		///		with respective elements constructed from the provided Indices_ within this Vector.
		/// </returns>
		template<typename OutT_, std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), OutT_> Shuffle()
		{
			return EmuMath::Helpers::new_vector_shuffle<OutT_, Indices_...>(*this);
		}
		template<typename OutT_, std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), OutT_> Shuffle() const
		{
			return EmuMath::Helpers::new_vector_shuffle<OutT_, Indices_...>(*this);
		}

		template<std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), value_type_uq> Shuffle()
		{
			return EmuMath::Helpers::new_vector_shuffle<value_type_uq, Indices_...>(*this);
		}
		template<std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), value_type_uq> Shuffle() const
		{
			return EmuMath::Helpers::new_vector_shuffle<value_type_uq, Indices_...>(*this);
		}

		/// <summary>
		/// <para> Creates an EmuMath Vector containing the specified OutT_ (defaults to value_type_uq) from elements within this Vector. </para>
		/// <para> The size of the output Vector will be equal to the number of provided Indices_ args. </para>
		/// <para>
		///		Indices_: Variadic sequence of 1 or more indices within this Vector to use to form the element for the output Vector's index at that arg's position. 
		///		(e.g. with the args 2, 4, 0, the result will be out[0] = this[2], out[1] = this[4], out[2] = this[0]).
		/// </para>
		/// <para> At least one Indices_ arg must be provided. </para>
		/// <para> This can be used to output a shuffled reference Vector, but it is recommended to use RefShuffle instead. </para>
		/// <para> This may be used to shuffle theoretical indices. To safely limit to only contained indices, use Shuffle. </para>
		/// </summary>
		/// <typeparam name="OutT_">Type to be contained in the output Vector. Defaults to this Vector's value_type_uq if not provided.</typeparam>
		/// <returns>
		///		EmuMath Vector containing the provided OutT_ (defaults to value_type_uq), containing a number of indices equal to the number of provided Indices_ args, 
		///		with respective elements constructed from the provided theoretical Indices_ within this Vector.
		/// </returns>
		template<typename OutT_, std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), OutT_> ShuffleTheoretical()
		{
			return EmuMath::Helpers::new_vector_shuffle_theoretical<OutT_, Indices_...>(*this);
		}
		template<typename OutT_, std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), OutT_> ShuffleTheoretical() const
		{
			return EmuMath::Helpers::new_vector_shuffle_theoretical<OutT_, Indices_...>(*this);
		}

		template<std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), value_type_uq> ShuffleTheoretical()
		{
			return EmuMath::Helpers::new_vector_shuffle_theoretical<value_type_uq, Indices_...>(*this);
		}
		template<std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), value_type_uq> ShuffleTheoretical() const
		{
			return EmuMath::Helpers::new_vector_shuffle_theoretical<value_type_uq, Indices_...>(*this);
		}

		/// <summary>
		/// <para> Creates an EmuMath Vector containing references to this Vector's elements at the specified Indices_. </para>
		/// <para> The size of the output Vector will be equal to the number of provided Indices_ args. </para>
		/// <para>
		///		Indices_: Variadic sequence of 1 or more indices within this Vector to use to reference in the output Vector's index at that arg's position. 
		///		(e.g. with the args 2, 4, 0, the result will be out[0] = this[2], out[1] = this[4], out[2] = this[0]).
		/// </para>
		/// <para> At least one Indices_ arg must be provided. </para>
		/// <para> Theoretical indices may not be referenced, and using theoretical indices will result in a compile-time error. </para>
		/// </summary>
		/// <returns>EmuMath Vector containing references to this Vector's data, or this Vector's references if it is also a reference-containing Vector.</returns>
		template<std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), value_type&> RefShuffle()
		{
			return EmuMath::Helpers::new_vector_shuffle<value_type&, Indices_...>(*this);
		}
		template<std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), const value_type&> RefShuffle() const
		{
			return EmuMath::Helpers::new_vector_shuffle<const value_type&, Indices_...>(*this);
		}

		/// <summary>
		/// <para> Creates an EmuMath Vector containing constant references to this Vector's elements at the specified Indices_. </para>
		/// <para> The size of the output Vector will be equal to the number of provided Indices_ args. </para>
		/// <para>
		///		Indices_: Variadic sequence of 1 or more indices within this Vector to use to reference in the output Vector's index at that arg's position. 
		///		(e.g. with the args 2, 4, 0, the result will be out[0] = this[2], out[1] = this[4], out[2] = this[0]).
		/// </para>
		/// <para> At least one Indices_ arg must be provided. </para>
		/// <para> Theoretical indices may not be referenced, and using theoretical indices will result in a compile-time error. </para>
		/// </summary>
		/// <returns>EmuMath Vector containing const references to this Vector's data, or this Vector's references if it is also a reference-containing Vector.</returns>
		template<std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), const value_type&> ConstRefShuffle() const
		{
			return EmuMath::Helpers::new_vector_shuffle<const value_type&, Indices_...>(*this);
		}
#pragma endregion

#pragma region MUTATIONS
	public:
		/// <summary>
		/// <para> Crates a Vector of this Vector's size and value_type_uq using the provided mutation func_. </para>
		/// <para> The provided arguments will be provided to func_ for every index within the output Vector. </para>
		/// <para> For any Arg_ that is an EmuMath Vector: The argument at the matching index will be passed to the Func_ instance, instead of the full Vector. </para>
		/// <para> IncludeSelf_ indicates if (and how) this Vector should be included as an argument for mutation. </para>
		/// <para> If IncludeSelf_ == 0: This Vector will not be passed as an argument for mutation. </para>
		/// <para> If IncludeSelf &lt; 0: This Vector will be passed as the first argument for mutation. </para>
		/// <para> If IncludeSelf &gt; 0: This Vector will be passed as the final argument for mutation. </para>
		/// </summary>
		/// <typeparam name="Func_">Mutation function to invoke for every index within the output Vector.</typeparam>
		/// <typeparam name="Args_">All (or additional, if this Vector is also being passed based on IncludeSelf_) argument types being passed to the mutation function.</typeparam>
		/// <param name="args_">All (or additional, if this Vector is being passed based on IncludeSelf_) arguments to pass to the mutation function.</param>
		/// <returns>EmuMath Vector created from mutating the provided arguments via an instance of the provided Func_ at every index within the output Vector.</returns>
		template<std::size_t IncludeSelf_, class Func_, class...Args_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, value_type_uq> Mutate(Func_ func_, Args_&&...args_)
		{
			if constexpr (IncludeSelf_ < 0)
			{
				return EmuMath::Helpers::new_vector_mutate<size, value_type_uq, Func_&>(func_, *this, std::forward<Args_>(args_)...);
			}
			else if constexpr (IncludeSelf_ > 0)
			{
				return EmuMath::Helpers::new_vector_mutate<size, value_type_uq, Func_&>(func_, std::forward<Args_>(args_)..., *this);
			}
			else
			{
				return EmuMath::Helpers::new_vector_mutate<size, value_type_uq, Func_&>(func_, std::forward<Args_>(args_)...);
			}
		}
		template<std::size_t IncludeSelf_, class Func_, class...Args_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, value_type_uq> Mutate(Func_ func_, Args_&&...args_) const
		{
			if constexpr (IncludeSelf_ < 0)
			{
				return EmuMath::Helpers::new_vector_mutate<size, value_type_uq, Func_&>(func_, *this, std::forward<Args_>(args_)...);
			}
			else if constexpr (IncludeSelf_ > 0)
			{
				return EmuMath::Helpers::new_vector_mutate<size, value_type_uq, Func_&>(func_, std::forward<Args_>(args_)..., *this);
			}
			else
			{
				return EmuMath::Helpers::new_vector_mutate<size, value_type_uq, Func_&>(func_, std::forward<Args_>(args_)...);
			}
		}

		/// <summary>
		/// <para> Crates a Vector of this Vector's size and value_type_uq using the provided mutation Func_ type. </para>
		/// <para> The provided arguments will be provided to an instance of Func_ for every index within the output Vector. </para>
		/// <para> For any Arg_ that is an EmuMath Vector: The argument at the matching index will be passed to the Func_ instance, instead of the full Vector. </para>
		/// <para> IncludeSelf_ indicates if (and how) this Vector should be included as an argument for mutation. </para>
		/// <para> If IncludeSelf_ == 0: This Vector will not be passed as an argument for mutation. </para>
		/// <para> If IncludeSelf &lt; 0: This Vector will be passed as the first argument for mutation. </para>
		/// <para> If IncludeSelf &gt; 0: This Vector will be passed as the final argument for mutation. </para>
		/// </summary>
		/// <typeparam name="Func_">Mutation function to invoke for every index within the output Vector.</typeparam>
		/// <typeparam name="Args_">All (or additional, if this Vector is also being passed based on IncludeSelf_) argument types being passed to the mutation function.</typeparam>
		/// <param name="args_">All (or additional, if this Vector is being passed based on IncludeSelf_) arguments to pass to the mutation function.</param>
		/// <returns>EmuMath Vector created from mutating the provided arguments via an instance of the provided Func_ at every index within the output Vector.</returns>
		template<class Func_, std::size_t IncludeSelf_, class...Args_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, value_type_uq> Mutate(Args_&&...args_)
		{
			if constexpr (IncludeSelf_ < 0)
			{
				return EmuMath::Helpers::new_vector_mutate<Func_, size, value_type_uq>(*this, std::forward<Args_>(args_)...);
			}
			else if constexpr (IncludeSelf_ > 0)
			{
				return EmuMath::Helpers::new_vector_mutate<Func_, size, value_type_uq>(std::forward<Args_>(args_)..., *this);
			}
			else
			{
				return EmuMath::Helpers::new_vector_mutate<Func_, size, value_type_uq>(std::forward<Args_>(args_)...);
			}
		}
		template<class Func_, std::size_t IncludeSelf_, class...Args_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, value_type_uq> Mutate(Args_&&...args_) const
		{
			if constexpr (IncludeSelf_ < 0)
			{
				return EmuMath::Helpers::new_vector_mutate<Func_, size, value_type_uq>(*this, std::forward<Args_>(args_)...);
			}
			else if constexpr (IncludeSelf_ > 0)
			{
				return EmuMath::Helpers::new_vector_mutate<Func_, size, value_type_uq>(std::forward<Args_>(args_)..., *this);
			}
			else
			{
				return EmuMath::Helpers::new_vector_mutate<Func_, size, value_type_uq>(std::forward<Args_>(args_)...);
			}
		}

		/// <summary>
		/// <para> Outputs to the provided EmuMath Vector using the provided mutation func_. </para>
		/// <para> The provided arguments will be provided to func_ for every index within the output Vector. </para>
		/// <para> For any Arg_ that is an EmuMath Vector: The argument at the matching index will be passed to the Func_ instance, instead of the full Vector. </para>
		/// <para> IncludeSelf_ indicates if (and how) this Vector should be included as an argument for mutation. </para>
		/// <para> If IncludeSelf_ == 0: This Vector will not be passed as an argument for mutation. </para>
		/// <para> If IncludeSelf &lt; 0: This Vector will be passed as the first argument for mutation. </para>
		/// <para> If IncludeSelf &gt; 0: This Vector will be passed as the final argument for mutation. </para>
		/// </summary>
		/// <typeparam name="Func_">Mutation function to invoke for every index within the output Vector.</typeparam>
		/// <typeparam name="Args_">All (or additional, if this Vector is also being passed based on IncludeSelf_) argument types being passed to the mutation function.</typeparam>
		/// <param name="func_">Mutation function to call for every index in the out_vector_.</param>
		/// <param name="out_vector_">Non-const EmuMath Vector reference to output mutation results to.</param>
		/// <param name="args_">All (or additional, if this Vector is being passed based on IncludeSelf_) arguments to pass to the mutation function.</param>
		template<std::size_t IncludeSelf_, class Func_, class...Args_, std::size_t OutSize_, typename OutT_>
		constexpr inline void MutateTo(Func_ func_, EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Args_&&...args_)
		{
			if constexpr (IncludeSelf_ < 0)
			{
				EmuMath::Helpers::new_vector_mutate_to<Func_&>(func_, out_vector_, *this, std::forward<Args_>(args_)...);
			}
			else if constexpr (IncludeSelf_ > 0)
			{
				EmuMath::Helpers::new_vector_mutate_to<Func_&>(func_, out_vector_, std::forward<Args_>(args_)..., *this);
			}
			else
			{
				EmuMath::Helpers::new_vector_mutate_to<Func_&>(func_, out_vector_, std::forward<Args_>(args_)...);
			}
		}
		template<std::size_t IncludeSelf_, class Func_, class...Args_, std::size_t OutSize_, typename OutT_>
		constexpr inline void MutateTo(Func_ func_, EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Args_&&...args_) const
		{
			if constexpr (IncludeSelf_ < 0)
			{
				EmuMath::Helpers::new_vector_mutate_to<Func_&>(func_, out_vector_, *this, std::forward<Args_>(args_)...);
			}
			else if constexpr (IncludeSelf_ > 0)
			{
				EmuMath::Helpers::new_vector_mutate_to<Func_&>(func_, out_vector_, std::forward<Args_>(args_)..., *this);
			}
			else
			{
				EmuMath::Helpers::new_vector_mutate_to<Func_&>(func_, out_vector_, std::forward<Args_>(args_)...);
			}
		}

		/// <summary>
		/// <para> Outputs to the provided EmuMath Vector using the provided mutation func_. </para>
		/// <para> The provided arguments will be provided to func_ for every index within the output Vector. </para>
		/// <para> For any Arg_ that is an EmuMath Vector: The argument at the matching index will be passed to the Func_ instance, instead of the full Vector. </para>
		/// <para> IncludeSelf_ indicates if (and how) this Vector should be included as an argument for mutation. </para>
		/// <para> If IncludeSelf_ == 0: This Vector will not be passed as an argument for mutation. </para>
		/// <para> If IncludeSelf &lt; 0: This Vector will be passed as the first argument for mutation. </para>
		/// <para> If IncludeSelf &gt; 0: This Vector will be passed as the final argument for mutation. </para>
		/// </summary>
		/// <typeparam name="Func_">Mutation function to invoke for every index within the output Vector.</typeparam>
		/// <typeparam name="Args_">All (or additional, if this Vector is also being passed based on IncludeSelf_) argument types being passed to the mutation function.</typeparam>
		/// <param name="out_vector_">Non-const EmuMath Vector reference to output mutation results to.</param>
		/// <param name="args_">All (or additional, if this Vector is being passed based on IncludeSelf_) arguments to pass to the mutation function.</param>
		template<class Func_, std::size_t IncludeSelf_, class...Args_, std::size_t OutSize_, typename OutT_>
		constexpr inline void MutateTo(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Args_&&...args_)
		{
			if constexpr (IncludeSelf_ < 0)
			{
				EmuMath::Helpers::new_vector_mutate_to<Func_>(out_vector_, *this, std::forward<Args_>(args_)...);
			}
			else if constexpr (IncludeSelf_ > 0)
			{
				EmuMath::Helpers::new_vector_mutate_to<Func_>(out_vector_, std::forward<Args_>(args_)..., *this);
			}
			else
			{
				EmuMath::Helpers::new_vector_mutate_to<Func_>(out_vector_, std::forward<Args_>(args_)...);
			}
		}
		template<class Func_, std::size_t IncludeSelf_, class...Args_, std::size_t OutSize_, typename OutT_>
		constexpr inline void MutateTo(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Args_&&...args_) const
		{
			if constexpr (IncludeSelf_ < 0)
			{
				EmuMath::Helpers::new_vector_mutate_to<Func_>(out_vector_, *this, std::forward<Args_>(args_)...);
			}
			else if constexpr (IncludeSelf_ > 0)
			{
				EmuMath::Helpers::new_vector_mutate_to<Func_>(out_vector_, std::forward<Args_>(args_)..., *this);
			}
			else
			{
				EmuMath::Helpers::new_vector_mutate_to<Func_>(out_vector_, std::forward<Args_>(args_)...);
			}
		}

		/// <summary>
		/// <para> Outputs to the specified index range within out_vector_ using the provided mutation func_. </para>
		/// <para> The provided arguments will be provided to func_ for every index within the output range. </para>
		/// <para>
		///		For any Arg_ that is an EmuMath Vector: The argument at the current ArgIndex_ will be used. 
		///		This is increased by 1 for every iteration, and starts at ArgBeginIndex_, which defaults to 0 if not provided.
		/// </para>
		/// <para> BeginIndex_ is the inclusive index at which to begin writing to out_vector_. </para>
		/// <para> EndIndex_ is the exclusive index at which to end writing to out_vector_. </para>
		/// <para> IncludeSelf_ indicates if (and how) this Vector should be included as an argument for mutation. </para>
		/// <para> If IncludeSelf_ == 0: This Vector will not be passed as an argument for mutation. </para>
		/// <para> If IncludeSelf &lt; 0: This Vector will be passed as the first argument for mutation. </para>
		/// <para> If IncludeSelf &gt; 0: This Vector will be passed as the final argument for mutation. </para>
		/// </summary>
		/// <typeparam name="Func_">Mutation function to invoke for every index within the provided range.</typeparam>
		/// <typeparam name="Args_">All (or additional, if this Vector is also being passed based on IncludeSelf_) argument types being passed to the mutation function.</typeparam>
		/// <param name="func_">
		///		: Function invocable with each of the provided arguments (or theoretical index equivalents for EmuMath Vector args_), 
		///		which additionally returns a type that may be copied to a value within out_vector_.
		/// </param>
		/// <param name="args_">: All (or additional, if this Vector is being passed based on IncludeSelf_) arguments to pass to the mutation function.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ArgBeginIndex_, std::size_t IncludeSelf_, class Func_, class...Args_, std::size_t OutSize_, typename OutT_>
		constexpr inline void MutateRange(Func_ func_, EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Args_&&...args_)
		{
			if constexpr (IncludeSelf_ < 0)
			{
				EmuMath::Helpers::new_vector_mutate_range<BeginIndex_, EndIndex_, ArgBeginIndex_, Func_&>(func_, out_vector_, *this, std::forward<Args_>(args_)...);
			}
			else if constexpr (IncludeSelf_ > 0)
			{
				EmuMath::Helpers::new_vector_mutate_range<BeginIndex_, EndIndex_, ArgBeginIndex_, Func_&>(func_, out_vector_, std::forward<Args_>(args_)..., *this);
			}
			else
			{
				EmuMath::Helpers::new_vector_mutate_range<BeginIndex_, EndIndex_, ArgBeginIndex_, Func_&>(func_, out_vector_, std::forward<Args_>(args_)...);
			}
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ArgBeginIndex_, std::size_t IncludeSelf_, class Func_, class...Args_, std::size_t OutSize_, typename OutT_>
		constexpr inline void MutateRange(Func_ func_, EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Args_&&...args_) const
		{
			if constexpr (IncludeSelf_ < 0)
			{
				EmuMath::Helpers::new_vector_mutate_range<BeginIndex_, EndIndex_, ArgBeginIndex_, Func_&>(func_, out_vector_, *this, std::forward<Args_>(args_)...);
			}
			else if constexpr (IncludeSelf_ > 0)
			{
				EmuMath::Helpers::new_vector_mutate_range<BeginIndex_, EndIndex_, ArgBeginIndex_, Func_&>(func_, out_vector_, std::forward<Args_>(args_)..., *this);
			}
			else
			{
				EmuMath::Helpers::new_vector_mutate_range<BeginIndex_, EndIndex_, ArgBeginIndex_, Func_&>(func_, out_vector_, std::forward<Args_>(args_)...);
			}
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t IncludeSelf_, class Func_, class...Args_, std::size_t OutSize_, typename OutT_>
		constexpr inline void MutateRange(Func_ func_, EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Args_&&...args_)
		{
			MutateRange<BeginIndex_, EndIndex_, 0, IncludeSelf_, Func_&>(func_, out_vector_, std::forward<Args_>(args_)...);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t IncludeSelf_, class Func_, class...Args_, std::size_t OutSize_, typename OutT_>
		constexpr inline void MutateRange(Func_ func_, EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Args_&&...args_) const
		{
			MutateRange<BeginIndex_, EndIndex_, 0, IncludeSelf_, Func_&>(func_, out_vector_, std::forward<Args_>(args_)...);
		}
		template<class Func_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ArgBeginIndex_, std::size_t IncludeSelf_, class...Args_, std::size_t OutSize_, typename OutT_>
		constexpr inline void MutateRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Args_&&...args_)
		{
			if constexpr (std::is_default_constructible_v<Func_>)
			{
				Func_ func_ = Func_();
				MutateRange<BeginIndex_, EndIndex_, ArgBeginIndex_, IncludeSelf_, Func_&>(func_, out_vector_, std::forward<Args_>(args_)...);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Func_>(),
					"Attempted to use an EmuMath Vector's MutateRange member without passing a func_, but the provided Func_ type is not default-constructible. Only default-constructible Func_ types may be omitted."
				);
			}
		}
		template<class Func_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ArgBeginIndex_, std::size_t IncludeSelf_, class...Args_, std::size_t OutSize_, typename OutT_>
		constexpr inline void MutateRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Args_&&...args_) const
		{
			if constexpr (std::is_default_constructible_v<Func_>)
			{
				Func_ func_ = Func_();
				MutateRange<BeginIndex_, EndIndex_, ArgBeginIndex_, IncludeSelf_, Func_&>(func_, out_vector_, std::forward<Args_>(args_)...);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Func_>(),
					"Attempted to use an EmuMath Vector's MutateRange member without passing a func_, but the provided Func_ type is not default-constructible. Only default-constructible Func_ types may be omitted."
				);
			}
		}
		template<class Func_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t IncludeSelf_, class...Args_, std::size_t OutSize_, typename OutT_>
		constexpr inline void MutateRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Args_&&...args_)
		{
			MutateRange<Func_, BeginIndex_, EndIndex_, 0, IncludeSelf_>(out_vector_, std::forward<Args_>(args_)...);
		}
		template<class Func_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t IncludeSelf_, class...Args_, std::size_t OutSize_, typename OutT_>
		constexpr inline void MutateRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Args_&&...args_) const
		{
			MutateRange<Func_, BeginIndex_, EndIndex_, 0, IncludeSelf_>(out_vector_, std::forward<Args_>(args_)...);
		}
#pragma endregion

#pragma region CONVERSIONS
		/// <summary>
		/// <para> Converts this Vector to its alternative template representation, if it has one. </para>
		/// <para> This is purely to convert reference-containing vectors between their `T_&amp;` and `internal_vector_reference&lt;T_&gt;` variants. </para>
		/// <para>
		///		For example, `Vector&lt;size, float&amp;&gt;` instantiates an identical type to `Vector&lt;size, internal_vector_reference&lt;float&gt;&gt;`,
		///		in terms of implementation and functionality; the only difference is the type in the template signature.
		/// </para>
		/// <para> This is not available for Vectors that do not have an alternative template representation. </para>
		/// </summary>
		/// <returns>Alternative template representation of this Vector to create the same underlying structure, (non-const) copying this Vector's internals.</returns>
		template<typename = std::enable_if_t<has_alternative_representation>>
		[[nodiscard]] constexpr inline alternative_rep AsAlternativeRep()
		{
			return alternative_rep(*this);
		}

		/// <summary>
		/// <para> Converts this Vector to its alternative template representation, if it has one. </para>
		/// <para> This is purely to convert reference-containing vectors between their `T_&amp;` and `internal_vector_reference&lt;T_&gt;` variants. </para>
		/// <para>
		///		For example, `Vector&lt;size, float&amp;&gt;` instantiates an identical type to `Vector&lt;size, internal_vector_reference&lt;float&gt;&gt;`,
		///		in terms of implementation and functionality; the only difference is the type in the template signature.
		/// </para>
		/// <para> This is not available for Vectors that do not have an alternative template representation. </para>
		/// <para> This const variant is further not available for Vectors that contain non-const references. </para>
		/// </summary>
		/// <returns>Alternative template representation of this Vector to create the same underlying structure, (const) copying this Vector's internals.</returns>
		template<typename = std::enable_if_t<has_alternative_representation && !contains_non_const_ref>>
		[[nodiscard]] constexpr inline alternative_rep AsAlternativeRep() const
		{
			return alternative_rep(*this);
		}
#pragma endregion

#pragma region COPIES
		/// <summary>
		/// <para> Copies the provided argument to this Vector's elements. </para>
		/// <para> If this Vector contains references, this will copy the provided Arg_ to the referenced value_types. </para>
		/// <para>
		///		If to_copy_ is an EmuMath Vector: Respective indices will be copied (e.g. this[1] = to_copy_[1]).
		///		Non-contained elements will be interpreted as implied-zeroes.
		/// </para>
		/// <para> If to_copy_ is none of the above: All indices will be set as a copy of to_copy_. </para>
		/// </summary>
		/// <param name="to_copy_">Argument to copy to indices as described.</param>
		template<typename Arg_, typename = std::enable_if_t<is_valid_template_copy_arg<Arg_&>()>>
		constexpr inline void Copy(Arg_& to_copy_)
		{
			EmuMath::Helpers::new_vector_copy<Arg_>(*this, to_copy_);
		}
		template<typename Arg_, typename = std::enable_if_t<is_valid_template_copy_arg<Arg_&>()>>
		constexpr inline void Copy(const Arg_& to_copy_)
		{
			EmuMath::Helpers::new_vector_copy<Arg_>(*this, to_copy_);
		}

		/// <summary>
		/// <para> Copies the provided argument to this Vector's elements within the provided index range. </para>
		/// <para> If this Vector contains references, this will copy the provided Arg_ to the referenced value_types. </para>
		/// <para>
		///		If to_copy_ is an EmuMath Vector: Respective indices will be copied (e.g. this[1] = to_copy_[1]).
		///		Non-contained elements will be interpreted as implied-zeroes.
		/// </para>
		/// <para> If to_copy_ is none of the above: All indices will be set as a copy of to_copy_. </para>
		/// </summary>
		/// <param name="to_copy_">Argument to copy to the provided index range as described.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Arg_>
		constexpr inline void Copy(Arg_& to_copy_)
		{
			EmuMath::Helpers::new_vector_copy<BeginIndex_, EndIndex_, Arg_>(*this, to_copy_);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Arg_>
		constexpr inline void Copy(const Arg_& to_copy_)
		{
			EmuMath::Helpers::new_vector_copy<BeginIndex_, EndIndex_, Arg_>(*this, to_copy_);
		}

		/// <summary>
		/// <para> Copies the provided argument to this Vector's elements within the provided index range. </para>
		/// <para> If this Vector contains references, this will copy the provided Arg_ to the referenced value_types. </para>
		/// <para>
		///		If to_copy_ is an EmuMath Vector: Respective indices will be copied (e.g. this[1] = to_copy_[1]).
		///		Non-contained elements will be interpreted as implied-zeroes if CopyNonContained_ is true; otherwise, non-shared indices will not be modified.
		/// </para>
		/// <para> If to_copy_ is none of the above: All indices will be set as a copy of to_copy_. </para>
		/// </summary>
		/// <param name="to_copy_">Argument to copy to the provided index range as described.</param>
		template<bool CopyNonContained_, typename Arg_>
		constexpr inline void Copy(Arg_& to_copy_)
		{
			EmuMath::Helpers::new_vector_copy<CopyNonContained_, Arg_>(*this, to_copy_);
		}
		template<bool CopyNonContained_, typename Arg_>
		constexpr inline void Copy(const Arg_& to_copy_)
		{
			EmuMath::Helpers::new_vector_copy<CopyNonContained_, Arg_>(*this, to_copy_);
		}

		/// <summary>
		/// <para> Copies the provided argument to this Vector's elements within the provided index range. </para>
		/// <para> If this Vector contains references, this will copy the provided Arg_ to the referenced value_types. </para>
		/// <para>
		///		If to_copy_ is an EmuMath Vector: Progressively iterating indices from 0 will be copied (e.g. this[BeginIndex_ + 1] = to_copy_[1]).
		///		Non-contained elements will be interpreted as implied-zeroes. 
		///		Reading of to_copy_ will start at index 0; to begin reading from BeginIndex_, use `Copy`.
		/// </para>
		/// <para> If to_copy_ is none of the above: All indices will be set as a copy of to_copy_. </para>
		/// </summary>
		/// <param name="to_copy_">Argument to copy to the provided index range as described.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_ = size, typename Arg_>
		constexpr inline void CopyFromStart(Arg_& to_copy_)
		{
			EmuMath::Helpers::new_vector_copy_from_start<BeginIndex_, EndIndex_, Arg_>(*this, to_copy_);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_ = size, typename Arg_>
		constexpr inline void CopyFromStart(const Arg_& to_copy_)
		{
			EmuMath::Helpers::new_vector_copy_from_start<BeginIndex_, EndIndex_, Arg_>(*this, to_copy_);
		}

		/// <summary>
		/// <para> Copies the provided argument to this Vector's elements within the provided index range. </para>
		/// <para> If this Vector contains references, this will copy the provided Arg_ to the referenced value_types. </para>
		/// <para>
		///		If to_copy_ is an EmuMath Vector: Progressively iterating indices from 0 will be copied (e.g. this[BeginIndex_ + 1] = to_copy_[1]).
		///		Non-shared indices will not be modified. 
		///		Reading of to_copy_ will start at index 0; to begin reading from BeginIndex_, use `Copy`.
		/// </para>
		/// <para> If to_copy_ is none of the above: All indices will be set as a copy of to_copy_. </para>
		/// </summary>
		/// <param name="to_copy_">Argument to copy to the provided index range as described.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_ = size, typename Arg_>
		constexpr inline void CopyFromStartContainedOnly(Arg_& to_copy_)
		{
			EmuMath::Helpers::new_vector_copy_from_start_contained_only<BeginIndex_, EndIndex_, Arg_>(*this, to_copy_);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_ = size, typename Arg_>
		constexpr inline void CopyFromStartContainedOnly(const Arg_& to_copy_)
		{
			EmuMath::Helpers::new_vector_copy_from_start_contained_only<BeginIndex_, EndIndex_, Arg_>(*this, to_copy_);
		}
#pragma endregion

#pragma region SETS
		/// <summary>
		/// <para> Sets the stored elements of this Vector to via moving respective elements in the passed Vector. </para>
		/// <para> If to_move_set_ contains less elements than this Vector, non-contained elements will be interpreted as implied zeroes. </para>
		/// <para> If this Vector contains references, this will update what is referenced by respective references. </para>
		/// </summary>
		/// <param name="to_move_set_">EmuMath Vector to move stored elements from when assigning this Vector's stored elements.</param>
		template
		<
			std::size_t InSize_,
			typename InT_,
			typename = std::enable_if_t<is_valid_vector_for_set<InSize_, InT_, false, true>()>
		>
		constexpr inline void Set(EmuMath::NewVector<InSize_, InT_>&& to_move_set_)
		{
			EmuMath::Helpers::new_vector_set<T_, Size_, InSize_, InT_>(*this, std::move(to_move_set_));
		}

		/// <summary>
		/// <para> Sets the stored elements of this Vector to via moving respective elements in the passed Vector. </para>
		/// <para> If to_move_set_ contains less elements than this Vector, non-contained elements will be interpreted as implied zeroes. </para>
		/// <para> If this Vector contains references, this will update what is referenced by respective references. </para>
		/// </summary>
		/// <param name="to_move_set_">EmuMath Vector to move stored elements from when assigning this Vector's stored elements.</param>
		template
		<
			std::size_t InSize_,
			typename InT_,
			typename = std::enable_if_t<is_valid_vector_for_set<InSize_, InT_, true, true>()>
		>
		constexpr inline void Set(const EmuMath::NewVector<InSize_, InT_>&& to_move_set_)
		{
			EmuMath::Helpers::new_vector_set<T_, Size_, InSize_, InT_>(*this, std::move(to_move_set_));
		}

		/// <summary>
		/// <para> Sets the stored elements of this Vector to via copying respective elements in the passed Vector. </para>
		/// <para> If to_copy_set_ contains less elements than this Vector, non-contained elements will be interpreted as implied zeroes. </para>
		/// <para> If this Vector contains references, this will update what is referenced by respective references. </para>
		/// </summary>
		/// <param name="to_copy_set_">EmuMath Vector to copy stored elements from when assigning this Vector's stored elements.</param>
		template
		<
			std::size_t InSize_,
			typename InT_,
			typename = std::enable_if_t<is_valid_vector_for_set<InSize_, InT_, false, false>()>
		>
		constexpr inline void Set(EmuMath::NewVector<InSize_, InT_>& to_copy_set_)
		{
			EmuMath::Helpers::new_vector_set<T_, Size_, InSize_, InT_>(*this, to_copy_set_);
		}

		/// <summary>
		/// <para> Sets the stored elements of this Vector to via copying respective elements in the passed Vector. </para>
		/// <para> If to_copy_set_ contains less elements than this Vector, non-contained elements will be interpreted as implied zeroes. </para>
		/// <para> If this Vector contains references, this will update what is referenced by respective references. </para>
		/// </summary>
		/// <param name="to_copy_set_">EmuMath Vector to copy stored elements from when assigning this Vector's stored elements.</param>
		template
		<
			std::size_t InSize_,
			typename InT_,
			typename = std::enable_if_t<is_valid_vector_for_set<InSize_, InT_, true, false>()>
		>
		constexpr inline void Set(const EmuMath::NewVector<InSize_, InT_>& to_copy_set_)
		{
			EmuMath::Helpers::new_vector_set<T_, Size_, InSize_, InT_>(*this, to_copy_set_);
		}

		/// <summary>
		/// <para> Sets the stored elements of this Vector to via moving respective elements in the passed Vector. </para>
		/// <para> If to_move_set_ contains less elements than this Vector, elements in non-shared indices will not be modified. </para>
		/// <para> If this Vector contains references, this will update what is referenced by respective references. </para>
		/// </summary>
		/// <param name="to_move_set_">EmuMath Vector to move stored elements from when assigning this Vector's stored elements.</param>
		template
		<
			std::size_t InSize_,
			typename InT_,
			typename = std::enable_if_t<is_valid_vector_for_set<InSize_, InT_, false, true>()>
		>
		constexpr inline void SetContainedOnly(EmuMath::NewVector<InSize_, InT_>&& to_move_set_)
		{
			EmuMath::Helpers::new_vector_set_contained_only<T_, Size_, InSize_, InT_>(*this, std::move(to_move_set_));
		}

		/// <summary>
		/// <para> Sets the stored elements of this Vector to via moving respective elements in the passed Vector. </para>
		/// <para> If to_move_set_ contains less elements than this Vector, elements in non-shared indices will not be modified. </para>
		/// <para> If this Vector contains references, this will update what is referenced by respective references. </para>
		/// </summary>
		/// <param name="to_move_set_">EmuMath Vector to move stored elements from when assigning this Vector's stored elements.</param>
		template
		<
			std::size_t InSize_,
			typename InT_,
			typename = std::enable_if_t<is_valid_vector_for_set<InSize_, InT_, true, true>()>
		>
		constexpr inline void SetContainedOnly(const EmuMath::NewVector<InSize_, InT_>&& to_move_set_)
		{
			EmuMath::Helpers::new_vector_set_contained_only<T_, Size_, InSize_, InT_>(*this, std::move(to_move_set_));
		}

		/// <summary>
		/// <para> Sets the stored elements of this Vector to via copying respective elements in the passed Vector. </para>
		/// <para> If to_move_set_ contains less elements than this Vector, elements in non-shared indices will not be modified. </para>
		/// <para> If this Vector contains references, this will update what is referenced by respective references. </para>
		/// </summary>
		/// <param name="to_copy_set_">EmuMath Vector to copy stored elements from when assigning this Vector's stored elements.</param>
		template
		<
			std::size_t InSize_,
			typename InT_,
			typename = std::enable_if_t<is_valid_vector_for_set<InSize_, InT_, false, false>()>
		>
		constexpr inline void SetContainedOnly(EmuMath::NewVector<InSize_, InT_>& to_copy_set_)
		{
			EmuMath::Helpers::new_vector_set_contained_only<T_, Size_, InSize_, InT_>(*this, to_copy_set_);
		}

		/// <summary>
		/// <para> Sets the stored elements of this Vector to via copying respective elements in the passed Vector. </para>
		/// <para> If to_move_set_ contains less elements than this Vector, elements in non-shared indices will not be modified. </para>
		/// <para> If this Vector contains references, this will update what is referenced by respective references. </para>
		/// </summary>
		/// <param name="to_copy_set_">EmuMath Vector to copy stored elements from when assigning this Vector's stored elements.</param>
		template
		<
			std::size_t InSize_,
			typename InT_,
			typename = std::enable_if_t<is_valid_vector_for_set<InSize_, InT_, true, false>()>
		>
		constexpr inline void SetContainedOnly(const EmuMath::NewVector<InSize_, InT_>& to_copy_set_)
		{
			EmuMath::Helpers::new_vector_set_contained_only<T_, Size_, InSize_, InT_>(*this, to_copy_set_);
		}

		/// <summary>
		/// <para> Sets the stored_type at the provided Index_ within this Vector via the provided arg_. </para>
		/// <para> If this Vector contains references, this will update what is referenced by said reference. </para>
		/// <para> If multiple arguments are provided, this will attempt to construct the stored_type via the provided args_. </para>
		/// </summary>
		/// <param name="arg_">Argument to set the stored_type at the provided Index_ via.</param>
		template
		<
			std::size_t Index_,
			typename Arg_,
			typename = std::enable_if_t<is_valid_type_for_single_set<Arg_>()>
		>
		constexpr inline void Set(Arg_&& arg_)
		{
			if constexpr (Index_ < size)
			{
				if constexpr (std::is_assignable_v<stored_type, Arg_>)
				{
					std::get<Index_>(_data) = std::forward<Arg_>(arg_);
				}
				else if constexpr (std::is_convertible_v<Arg_, stored_type>)
				{
					std::get<Index_>(_data) = static_cast<stored_type>(arg_);
				}
				else if constexpr (std::is_constructible_v<stored_type, Arg_>)
				{
					std::get<Index_>(_data) = stored_type(std::forward<Arg_>(arg_));
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Arg_>(),
						"Attempted to `Set` an Index_ within an EmuMath Vector, but the provided Arg_ cannot be used to assign, construct, or convert-to the Vector's stored_type."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Arg_>(),
					"Attempted to `Set` an invalid Index_ within an EmuMath Vector."
				);
			}
		}

		/// <summary>
		/// <para> Constructs a stored_type via the provided construction_args_ and sets the stored_type at the provided index via it. </para>
		/// <para> If this Vector contains references, this will update what is referenced by said reference. </para>
		/// </summary>
		/// <param name="construction_args_">Arguments to construct an instance of this Vector's stored_type.</param>
		template
		<
			std::size_t Index_,
			typename...Args_,
			typename = std::enable_if_t<(sizeof...(Args_) > 1) && std::is_constructible_v<stored_type, Args_...>>
		>
		constexpr inline void Set(Args_&&...construction_args_)
		{
			if constexpr (Index_ < size)
			{
				if constexpr (std::is_constructible_v<stored_type, Args_...>)
				{
					std::get<Index_>(_data) = stored_type(std::forward<Args_>(construction_args_)...);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Args_...>(),
						"Attempted to `Set` an Index_ within an EmuMath Vector with multiple arguments, but the stored_type cannot be constructed from the provided arguments."
					);
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Args_...>(), "Attempted to `Set` an invalid Index_ within an EmuMath Vector.");
			}
		}

		/// <summary>
		/// <para> Sets all stored_types at indices in the specified range within this Vector via the provided arg_. </para>
		/// <para> If this Vector contains references, this will update what is referenced by all references. </para>
		/// <para> BeginIndex_ indicates the inclusive index to start setting stored elements from. This defaults to 0.</para>
		/// <para> EndIndex_ indicates the exclusive index to stop setting stored elements at. This defaults to the size of this Vector. </para>
		/// </summary>
		/// <param name="arg_">Argument to set all stored_types in the specified index range within this Vector via.</param>
		template
		<
			std::size_t BeginIndex_ = 0,
			std::size_t EndIndex_ = size,
			typename Arg_,
			typename = std::enable_if_t<is_valid_type_for_set_all<Arg_&&>()>
		>
		constexpr inline void SetAll(Arg_&& arg_)
		{
			EmuMath::Helpers::new_vector_set_all<BeginIndex_, EndIndex_>(*this, std::move(arg_));
		}

		/// <summary>
		/// <para> Sets all stored_types at indices in the specified range within this Vector via the provided arg_. </para>
		/// <para> If this Vector contains references, this will update what is referenced by all references. </para>
		/// <para> BeginIndex_ indicates the inclusive index to start setting stored elements from. This defaults to 0.</para>
		/// <para> EndIndex_ indicates the exclusive index to stop setting stored elements at. This defaults to the size of this Vector. </para>
		/// </summary>
		/// <param name="arg_">Argument to set all stored_types in the specified index range within this Vector via.</param>
		template
		<
			std::size_t BeginIndex_ = 0,
			std::size_t EndIndex_ = size,
			typename Arg_,
			typename = std::enable_if_t<is_valid_type_for_set_all<Arg_&>()>
		>
		constexpr inline void SetAll(Arg_& arg_)
		{
			EmuMath::Helpers::new_vector_set_all<BeginIndex_, EndIndex_>(*this, arg_);
		}

		/// <summary>
		/// <para> Sets all stored_types at indices in the specified range within this Vector via the provided arg_. </para>
		/// <para> If this Vector contains references, this will update what is referenced by all references. </para>
		/// <para> BeginIndex_ indicates the inclusive index to start setting stored elements from. This defaults to 0.</para>
		/// <para> EndIndex_ indicates the exclusive index to stop setting stored elements at. This defaults to the size of this Vector. </para>
		/// </summary>
		/// <param name="arg_">Argument to set all stored_types in the specified index range within this Vector via.</param>
		template
		<
			std::size_t BeginIndex_ = 0,
			std::size_t EndIndex_ = size,
			typename Arg_,
			typename = std::enable_if_t<is_valid_type_for_set_all<const Arg_&>()>
		>
		constexpr inline void SetAll(const Arg_& arg_)
		{
			EmuMath::Helpers::new_vector_set_all<BeginIndex_, EndIndex_>(*this, arg_);
		}
#pragma endregion

	private:
		/// <summary> Contiguous element data stored within this Vector. </summary>
		data_storage_type _data;
	};
}

#endif
