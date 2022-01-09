#ifndef EMU_MATH_vector_T_H_INC_
#define EMU_MATH_vector_T_H_INC_ 1

#include "_helpers/_vector_helpers.h"
#include <array>
#include <functional>
#include <ostream>
#include <sstream>
#include <stdexcept>

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
		using preferred_floating_point = typename vector_info::preferred_floating_point;
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
			return EmuMath::Helpers::vector_get_non_contained<this_type>();
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
			else if constexpr (EmuCore::TMP::is_static_castable_v<In_, stored_type>)
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
			EmuMath::Helpers::vector_set(*this, to_copy_);
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
			EmuMath::Helpers::vector_set(*this, to_copy_);
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
					EmuMath::Helpers::vector_set(*this, std::move(to_move_));
				}
			}
			else
			{
				EmuMath::Helpers::vector_set(*this, std::move(to_move_));
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
		/// <para> Provides access to the provided Index_ within this Vector. If the Index_ is invalid, a runtime exception will be thrown. </para>
		/// <para> If the provided index_ is known at compile-time, it is recommended to use the template version of this function to enforce index safety. </para>
		/// </summary>
		/// <returns>Reference to the element at the provided index within this Vector.</returns>
		[[nodiscard]] constexpr inline value_type& at(const std::size_t index_)
		{
			if(index_ < size)
			{
				return _data[index_];
			}
			else
			{
				if constexpr (size != 0)
				{
					// NOTE: Under MSVC, constexpr_str_ will always be false without the /Zc:__cplusplus switch enabled, as of 2022/01/05
					constexpr bool constexpr_str_ = __cplusplus >= 201907L;
					if constexpr (constexpr_str_)
					{
						// We can provide some extra information if we have access to constexpr strings
						// --- This is to allow `at(index_)` to still satisfy constexpr constraints in standards before C++20
						std::string out_str_;
						out_str_.reserve(150); // Reserves enough space for all literal chars, alongside some extra for size-1 and index_ after conversion.
						out_str_ += "Attempted to access an invalid contained index of an EmuMath Vector.\nProvided index: ";
						out_str_ += std::to_string(index_);
						out_str_ += "\nInclusive valid index range: 0:";
						out_str_ += std::to_string(size - 1);
						throw std::out_of_range(out_str_);
					}
					else
					{
						throw std::out_of_range("Attempted to access an invalid contained index of an EmuMath Vector.");
					}
				}
				else
				{
					throw std::out_of_range("Attempted to access a contained index of an EmuMath Vector which contains 0 elements.");
				}
			}
		}
		/// <summary>
		/// <para> Provides const access to the provided Index_ within this Vector. If the Index_ is invalid, a runtime exception may be thrown. </para>
		/// <para> If the provided index_ is known at compile-time, it is recommended to use the template version of this function to enforce index safety. </para>
		/// </summary>
		/// <returns>Const reference to the element at the provided index within this Vector.</returns>
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
			return _data[index_];
		}
		/// <summary>
		/// <para> Provides const access to the provided Index_ within this Vector. If the Index_ is invalid, behaviour is undefined. </para>
		/// <para> If the provided index_ is known at compile-time, it is recommended to use the template version of the `at` function to enforce index safety. </para>
		/// </summary>
		/// <returns>Const reference to the element at the provided index within this Vector.</returns>
		[[nodiscard]] constexpr inline const value_type& operator[](const std::size_t index_) const
		{
			return const_cast<this_type*>(this)->operator[](index_);
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
			return EmuMath::Helpers::vector_get_theoretical<Index_>(*this);
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
			return EmuMath::Helpers::vector_get_theoretical<Index_>(*this);
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
			return EmuMath::Helpers::vector_pre_increment(*this);
		}
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> operator++()
		{
			return EmuMath::Helpers::vector_pre_increment<OutSize_, OutT_>(*this);
		}
		template<typename OutT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> operator++()
		{
			return EmuMath::Helpers::vector_pre_increment<size, OutT_>(*this);
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> operator++(int)
		{
			return EmuMath::Helpers::vector_post_increment<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		constexpr inline typename _vector_or_void<size, OutT_>::type operator++(int)
		{
			if constexpr (std::is_void_v<OutT_>)
			{
				EmuMath::Helpers::vector_post_increment_no_copy(*this);
			}
			else
			{
				return EmuMath::Helpers::vector_post_increment<size, OutT_>(*this);
			}
		}

		// DECREMENT OPERATORS
		constexpr inline this_type& operator--()
		{
			return EmuMath::Helpers::vector_pre_decrement(*this);
		}
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> operator--()
		{
			return EmuMath::Helpers::vector_pre_decrement<OutSize_, OutT_>(*this);
		}
		template<typename OutT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> operator--()
		{
			return EmuMath::Helpers::vector_pre_decrement<size, OutT_>(*this);
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> operator--(int)
		{
			return EmuMath::Helpers::vector_post_decrement<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline typename _vector_or_void<size, OutT_>::type operator--(int)
		{
			if constexpr (std::is_void_v<OutT_>)
			{
				EmuMath::Helpers::vector_post_decrement_no_copy(*this);
			}
			else
			{
				return EmuMath::Helpers::vector_post_decrement<size, OutT_>(*this);
			}
		}
		
		// NEGATION OPERATORS
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> operator-() const
		{
			return EmuMath::Helpers::vector_negate<OutSize_, OutT_>(*this);
		}

		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> operator-() const
		{
			return EmuMath::Helpers::vector_negate<size, OutT_>(*this);
		}
#pragma endregion

#pragma region CONST_ARITHMETIC_OPERATORS
	public:
		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> operator+(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_add<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> operator+(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_add<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> operator-(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_subtract<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> operator-(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_subtract<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> operator*(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_multiply<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> operator*(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_multiply<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> operator/(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_divide<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> operator/(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_divide<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> operator%(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_mod<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> operator%(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_mod<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region CONST_BITWISE_OPERATORS
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> operator~() const
		{
			return EmuMath::Helpers::vector_bitwise_not<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> operator~() const
		{
			return EmuMath::Helpers::vector_bitwise_not<size, OutT_>(*this);
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> operator&(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_and<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> operator&(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_and<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> operator|(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_or<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> operator|(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_or<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> operator^(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_xor<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> operator^(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_xor<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> operator<<(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_left<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> operator<<(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_left<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> operator>>(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_right<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> operator>>(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_right<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region CMP_OPERATORS
	public:
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool operator==(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_equal<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool operator==(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_equal<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool operator!=(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_not_equal<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool operator!=(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_not_equal<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool operator>(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_greater<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool operator>(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_greater<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool operator<(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_less<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool operator<(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_less<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool operator>=(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_greater_equal<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool operator>=(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_greater_equal<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool operator<=(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_less_equal<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool operator<=(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_less_equal<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region ARITHMETIC_ASSIGN_OPERATORS
	public:
		template<typename Rhs_>
		constexpr inline this_type& operator+=(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_add_assign(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_>
		constexpr inline this_type& operator+=(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_add_assign<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<typename Rhs_>
		constexpr inline this_type& operator-=(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_subtract_assign(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_>
		constexpr inline this_type& operator-=(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_subtract_assign<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<typename Rhs_>
		constexpr inline this_type& operator*=(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_multiply_assign(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_>
		constexpr inline this_type& operator*=(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_multiply_assign<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<typename Rhs_>
		constexpr inline this_type& operator/=(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_divide_assign(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_>
		constexpr inline this_type& operator/=(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_divide_assign<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<typename Rhs_>
		constexpr inline this_type& operator%=(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_mod_assign(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_>
		constexpr inline this_type& operator%=(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_mod_assign<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region BITWISE_ASSIGN_OPERATORS
	public:
		template<typename Rhs_>
		constexpr inline this_type& operator&=(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_bitwise_and_assign(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_>
		constexpr inline this_type& operator&=(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_bitwise_and_assign<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<typename Rhs_>
		constexpr inline this_type& operator|=(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_bitwise_or_assign(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_>
		constexpr inline this_type& operator|=(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_bitwise_or_assign<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<typename Rhs_>
		constexpr inline this_type& operator^=(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_bitwise_xor_assign(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_>
		constexpr inline this_type& operator^=(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_bitwise_xor_assign<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region UNARY_ARITHMETIC_FUNCS
	public:
		/// <summary>
		/// <para> Peforms a pre-increment on this Vector, equivalent to `++this_vector`. </para>
		/// </summary>
		/// <returns>Reference to this Vector if no template args are provided; otherwise, a copy of this Vector after the increment.</returns>
		constexpr inline this_type& PreIncrement()
		{
			return EmuMath::Helpers::vector_pre_increment(*this);
		}
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> PreIncrement()
		{
			return EmuMath::Helpers::vector_pre_increment<OutSize_, OutT_>(*this);
		}
		template<typename OutT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> PreIncrement()
		{
			return EmuMath::Helpers::vector_pre_increment<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Performs a post-increment on this Vector, equivalent to `this_vector++`. </para>
		/// <para> Creating an unwanted copy may be avoided by passing `void` as the only template argument. </para>
		/// </summary>
		/// <returns>Copy of this Vector before the increment if not provided with only `void` as a template argument; otherwise, no return.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> PostIncrement()
		{
			return EmuMath::Helpers::vector_post_increment<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		constexpr inline typename _vector_or_void<size, OutT_>::type PostIncrement()
		{
			if constexpr (std::is_void_v<OutT_>)
			{
				EmuMath::Helpers::vector_post_increment_no_copy(*this);
			}
			else
			{
				return EmuMath::Helpers::vector_post_increment<size, OutT_>(*this);
			}
		}

		/// <summary>
		/// <para> Peforms a pre-decrement on this Vector, equivalent to `--this_vector`. </para>
		/// </summary>
		/// <returns>Reference to this Vector if no template args are provided; otherwise, a copy of this Vector after the decrement.</returns>
		constexpr inline this_type& PreDecrement()
		{
			return EmuMath::Helpers::vector_pre_decrement(*this);
		}
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> PreDecrement()
		{
			return EmuMath::Helpers::vector_pre_decrement<OutSize_, OutT_>(*this);
		}
		template<typename OutT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> PreDecrement()
		{
			return EmuMath::Helpers::vector_pre_decrement<size, OutT_>();
		}

		/// <summary>
		/// <para> Performs a post-decrement on this Vector, equivalent to `this_vector--`. </para>
		/// <para> Creating an unwanted copy may be avoided by passing `void` as the only template argument. </para>
		/// </summary>
		/// <returns>Copy of this Vector before the decrement if not provided with only `void` as a template argument; otherwise, no return.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> PostDecrement()
		{
			return EmuMath::Helpers::vector_post_decrement<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		constexpr inline typename _vector_or_void<size, OutT_>::type PostDecrement()
		{
			if constexpr (std::is_void_v<OutT_>)
			{
				EmuMath::Helpers::vector_post_decrement_no_copy(*this);
			}
			else
			{
				return EmuMath::Helpers::vector_post_decrement<size, OutT_>(*this);
			}
		}

		/// <summary> Returns a negated form of this Vector, equivalent to `-this_vector`. </summary>
		/// <returns>Copy of this Vector with its elements negated, using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq).</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Negate() const
		{
			return EmuMath::Helpers::vector_negate<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Negate() const
		{
			return EmuMath::Helpers::vector_negate<size, OutT_>(*this);
		}
		
		/// <summary> Ouputs a negated form of this Vector to the provided out_vector_, equivalent to `out_vector_ = -this_vector`. </summary>
		/// <param name="out_vector_">: EmuMath Vector to output the negated form of this Vector to.</param>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void Negate(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::vector_negate(out_vector_, *this);
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
			return EmuMath::Helpers::vector_negate_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> NegateRange() const
		{
			return EmuMath::Helpers::vector_negate_range<size, OutT_, BeginIndex_, EndIndex_>(*this);
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
			EmuMath::Helpers::vector_negate_range<BeginIndex_, EndIndex_>(out_vector_, *this);
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
			return EmuMath::Helpers::vector_negate_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, NegateBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t NegateBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> NegateRangeNoCopy() const
		{
			return EmuMath::Helpers::vector_negate_range_no_copy<size, OutT_, OutBegin, OutEnd_, NegateBegin_>(*this);
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
			EmuMath::Helpers::vector_negate_range_no_copy<OutBegin_, OutEnd_, NegateBegin_>(out_vector_, *this);
		}
#pragma endregion

#pragma region CONST_ARITHMETIC_FUNCS
	public:
		/// <summary>
		/// <para> Returns the result of adding rhs_ to this Vector. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be added. Otherwise, all elements have rhs_ added. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to add to this Vector.</param>
		/// <returns>Copy of this Vector with rhs_ added, using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq).</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Add(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_add<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Add(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_add<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Outputs the result of adding rhs_ to this Vector, via the provided out_vector_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be added. Otherwise, all elements have rhs_ added. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to add to this Vector.</param>
		template<typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void Add(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_add(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of adding rhs_ to this Vector within the provided index range, with copies of elements in indices outside of said range. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be added. Otherwise, all elements have rhs_ added. </para>
		/// <para> BeginIndex_: Inclusive index at which to start adding elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop adding elements. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to add to elements in the specified range.</param>
		/// <returns>Copy of this Vector using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq), with rhs_ added to indices in the provided range.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> AddRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_add_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> AddRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_add_range<size, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of adding rhs_ to this Vector within the provided index range,
		///		with copies of elements in indices outside of said range, via the provided out_vector_.
		/// </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be added. Otherwise, all elements have rhs_ added. </para>
		/// <para> BeginIndex_: Inclusive index at which to start adding elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop adding elements. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to add to elements in the specified range.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void AddRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_add_range<BeginIndex_, EndIndex_>(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of adding rhs_ to this Vector within the provided index range. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be added. Otherwise, all elements have rhs_ added. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing arithmetic results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing arithmetic results to the output Vector. </para>
		/// <para> AddBegin_: Inclusive index at which to start reading elements from this Vector (and rhs_ if it is an EmuMath Vector) to perform arithmetic. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to add to elements in the specified range.</param>
		/// <returns>
		///		EmuMath Vector using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq),
		///		with rhs_ added to indices within this Vector in the provided range, and default-constructed elements elsewhere.
		/// </returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AddBegin_, std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> AddRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_add_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, AddBegin_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AddBegin_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> AddRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_add_range_no_copy<size, OutT_, OutBegin_, OutEnd_, AddBegin_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Outputs the result of adding rhs_ to this Vector within the provided index range, via the provided out_vector_. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be added. Otherwise, all elements have rhs_ added. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing arithmetic results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing arithmetic results to the output Vector. </para>
		/// <para> AddBegin_: Inclusive index at which to start reading elements from this Vector (and rhs_ if it is an EmuMath Vector) to perform arithmetic. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to add to elements in the specified range.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AddBegin_, typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void AddRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_add_range_no_copy<OutBegin_, OutEnd_, AddBegin_>(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of subtracting rhs_ from this Vector. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be added. Otherwise, all elements have rhs_ added. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to subtract from this Vector.</param>
		/// <returns>Copy of this Vector with rhs_ subtracted, using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq).</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Subtract(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_subtract<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Subtract(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_subtract<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Outputs the result of subtracting rhs_ from this Vector, via the provided out_vector_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be subtracted. Otherwise, all elements have rhs_ subtracted. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to subtract from this Vector.</param>
		template<typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void Subtract(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_subtract(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of subtracting rhs_ from this Vector within the provided index range, with copies of elements in indices outside of said range. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be subtracted. Otherwise, all elements have rhs_ subtracted. </para>
		/// <para> BeginIndex_: Inclusive index at which to start subtracting elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop subtracting elements. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to subtract from elements in the specified range.</param>
		/// <returns>
		///		Copy of this Vector using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq), 
		///		with rhs_ subtracted from indices in the provided range.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> SubtractRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_subtract_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> SubtractRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_subtract_range<size, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of subtracting rhs_ from this Vector within the provided index range,
		///		with copies of elements in indices outside of said range, via the provided out_vector_.
		/// </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be subtracted. Otherwise, all elements have rhs_ subtracted. </para>
		/// <para> BeginIndex_: Inclusive index at which to start subtracting elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop subtracting elements. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to subtract from elements in the specified range.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void SubtractRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_subtract_range<BeginIndex_, EndIndex_>(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of subtracting rhs_ from this Vector within the provided index range. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be subtracted. Otherwise, all elements have rhs_ subtracted. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing arithmetic results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing arithmetic results to the output Vector. </para>
		/// <para> SubBegin_: Inclusive index at which to start reading elements from this Vector (and rhs_ if it is an EmuMath Vector) to perform arithmetic. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to subtract from elements in the specified range.</param>
		/// <returns>
		///		EmuMath Vector using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq),
		///		with rhs_ subtracted from indices within this Vector in the provided range, and default-constructed elements elsewhere.
		/// </returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t SubBegin_, std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> SubtractRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_subtract_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, SubBegin_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t SubBegin_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> SubtractRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_subtract_range_no_copy<size, OutT_, OutBegin_, OutEnd_, SubBegin_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Outputs the result of subtracting rhs_ from this Vector within the provided index range, via the provided out_vector_. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be subtracted. Otherwise, all elements have rhs_ subtracted. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing arithmetic results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing arithmetic results to the output Vector. </para>
		/// <para> SubBegin_: Inclusive index at which to start reading elements from this Vector (and rhs_ if it is an EmuMath Vector) to perform arithmetic. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to subtract from elements in the specified range.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t SubBegin_, typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void SubtractRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_subtract_range_no_copy<OutBegin_, OutEnd_, SubBegin_>(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of multiplying this Vector by rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be multiplied. Otherwise, all elements are multiplied by rhs_. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to multiply this Vector by.</param>
		/// <returns>Copy of this Vector multiplied by rhs_, using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq).</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Multiply(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_multiply<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Multiply(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_multiply<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Outputs the result of multiplying this Vector by rhs_, via the provided out_vector_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be multiplied. Otherwise, all elements are multiplied by rhs_. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to multiply this Vector by.</param>
		template<typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void Multiply(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_multiply(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of multiplying this Vector by rhs_ within the provided index range, with copies of elements in indices outside of said range. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be multiplied. Otherwise, all elements are multiplied by rhs_. </para>
		/// <para> BeginIndex_: Inclusive index at which to start multiplying elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop multiplying elements. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to multiply elements by in the specified range.</param>
		/// <returns>
		///		Copy of this Vector using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq), 
		///		with indices in the provided range multiplied by rhs_.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> MultiplyRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_multiply_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> MultiplyRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_multiply_range<size, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of multiplying this Vector by rhs_ within the provided index range,
		///		with copies of elements in indices outside of said range, via the provided out_vector_.
		/// </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be multiplied. Otherwise, all elements are multiplied by rhs_. </para>
		/// <para> BeginIndex_: Inclusive index at which to start multiplying elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop multiplying elements. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to multiply elements by in the specified range.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void MultiplyRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_multiply_range<BeginIndex_, EndIndex_>(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of multiplying this Vector by rhs_ within the provided index range. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be multiplied. Otherwise, all elements are multiplied by rhs_. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing arithmetic results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing arithmetic results to the output Vector. </para>
		/// <para> MulBegin_: Inclusive index at which to start reading elements from this Vector (and rhs_ if it is an EmuMath Vector) to perform arithmetic. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to multiply elements by in the specified range.</param>
		/// <returns>
		///		EmuMath Vector using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq),
		///		with indices within this Vector multiplied by rhs_ in the provided range, and default-constructed elements elsewhere.
		/// </returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MulBegin_, std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> MultiplyRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_multiply_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, MulBegin_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MulBegin_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> MultiplyRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_multiply_range_no_copy<size, OutT_, OutBegin_, OutEnd_, MulBegin_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Outputs the result of multiplying this Vector by rhs_ within the provided index range, via the provided out_vector_. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be multiplied. Otherwise, all elements are multiplied by rhs_. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing arithmetic results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing arithmetic results to the output Vector. </para>
		/// <para> MulBegin_: Inclusive index at which to start reading elements from this Vector (and rhs_ if it is an EmuMath Vector) to perform arithmetic. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to multiply elements by in the specified range.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MulBegin_, typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void MultiplyRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_multiply_range_no_copy<OutBegin_, OutEnd_, MulBegin_>(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of dividing this Vector by rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be divided. Otherwise, all elements are divided by rhs_. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to divide this Vector by.</param>
		/// <returns>Copy of this Vector divided by rhs_, using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq).</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Divide(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_divide<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Divide(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_divide<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Outputs the result of dividing this Vector by rhs_, via the provided out_vector_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be divided. Otherwise, all elements are divided by rhs_. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to divide this Vector by.</param>
		template<typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void Divide(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_divide(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of dividing this Vector by rhs_ within the provided index range, with copies of elements in indices outside of said range. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be divided. Otherwise, all elements are divided by rhs_. </para>
		/// <para> BeginIndex_: Inclusive index at which to start dividing elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop dividing elements. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to divide elements by in the specified range.</param>
		/// <returns>
		///		Copy of this Vector using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq), 
		///		with indices in the provided range divided by rhs_.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> DivideRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_divide_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> DivideRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_divide_range<size, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of dividing this Vector by rhs_ within the provided index range,
		///		with copies of elements in indices outside of said range, via the provided out_vector_.
		/// </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be divided. Otherwise, all elements are divided by rhs_. </para>
		/// <para> BeginIndex_: Inclusive index at which to start dividing elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop dividing elements. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to divide elements by in the specified range.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void DivideRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_divide_range<BeginIndex_, EndIndex_>(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of dividing this Vector by rhs_ within the provided index range. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be divided. Otherwise, all elements are divided by rhs_. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing arithmetic results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing arithmetic results to the output Vector. </para>
		/// <para> DivBegin_: Inclusive index at which to start reading elements from this Vector (and rhs_ if it is an EmuMath Vector) to perform arithmetic. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to divide elements by in the specified range.</param>
		/// <returns>
		///		EmuMath Vector using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq),
		///		with indices within this Vector divided by rhs_ in the provided range, and default-constructed elements elsewhere.
		/// </returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t DivBegin_, std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> DivideRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_divide_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, DivBegin_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t DivBegin_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> DivideRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_divide_range_no_copy<size, OutT_, OutBegin_, OutEnd_, DivBegin_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Outputs the result of dividing this Vector by rhs_ within the provided index range, via the provided out_vector_. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be divided. Otherwise, all elements are divided by rhs_. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing arithmetic results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing arithmetic results to the output Vector. </para>
		/// <para> DivBegin_: Inclusive index at which to start reading elements from this Vector (and rhs_ if it is an EmuMath Vector) to perform arithmetic. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to divide elements by in the specified range.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t DivBegin_, typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void DivideRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_divide_range_no_copy<OutBegin_, OutEnd_, DivBegin_>(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of modulo-dividing this Vector by rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be modulo-divided. Otherwise, all elements are modulo-divided by rhs_. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to modulo-divide this Vector by.</param>
		/// <returns>Copy of this Vector modulo-divided by rhs_, using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq).</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Mod(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_mod<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Mod(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_mod<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Outputs the result of modulo-dividing this Vector by rhs_, via the provided out_vector_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be modulo-divided. Otherwise, all elements are modulo-divided by rhs_. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to modulo-divide this Vector by.</param>
		template<typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void Mod(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_mod(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of modulo-dividing this Vector by rhs_ within the provided index range, with copies of elements in indices outside of said range. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be modulo-divided. Otherwise, all elements are modulo-divided by rhs_. </para>
		/// <para> BeginIndex_: Inclusive index at which to start modulo-dividing elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop modulo-dividing elements. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to modulo-divide elements by in the specified range.</param>
		/// <returns>
		///		Copy of this Vector using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq), 
		///		with indices in the provided range modulo-divided by rhs_.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> ModRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_mod_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> ModRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_mod_range<size, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of modulo-dividing this Vector by rhs_ within the provided index range,
		///		with copies of elements in indices outside of said range, via the provided out_vector_.
		/// </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be modulo-divided. Otherwise, all elements are divided by rhs_. </para>
		/// <para> BeginIndex_: Inclusive index at which to start modulo-dividing elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop modulo-dividing elements. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to modulo-divide elements by in the specified range.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void ModRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_mod_range<BeginIndex_, EndIndex_>(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of modulo-dividing this Vector by rhs_ within the provided index range. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be modulo-divided. Otherwise, all elements are modulo-divided by rhs_. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing arithmetic results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing arithmetic results to the output Vector. </para>
		/// <para> ModBegin_: Inclusive index at which to start reading elements from this Vector (and rhs_ if it is an EmuMath Vector) to perform arithmetic. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to modulo-divide elements by in the specified range.</param>
		/// <returns>
		///		EmuMath Vector using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq),
		///		with indices within this Vector modulo-divided by rhs_ in the provided range, and default-constructed elements elsewhere.
		/// </returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ModBegin_, std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> ModRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_mod_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, ModBegin_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ModBegin_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> ModRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_mod_range_no_copy<size, OutT_, OutBegin_, OutEnd_, ModBegin_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Outputs the result of modulo-dividing this Vector by rhs_ within the provided index range, via the provided out_vector_. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be modulo-divided. Otherwise, all elements are modulo-divided by rhs_. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing arithmetic results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing arithmetic results to the output Vector. </para>
		/// <para> ModBegin_: Inclusive index at which to start reading elements from this Vector (and rhs_ if it is an EmuMath Vector) to perform arithmetic. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to modulo-divide elements by in the specified range.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ModBegin_, typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void ModRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_mod_range_no_copy<OutBegin_, OutEnd_, ModBegin_>(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region CONST_BITWISE_FUNCS
		/// <summary>
		/// <para> Returns the result of bitwise ANDing this Vector with rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be ANDed. Otherwise, all elements be ANDed with rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to AND with this Vector.</param>
		/// <returns>Copy of this Vector ANDed with rhs_, using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq).</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> And(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_and<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> And(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_and<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Outputs the result of bitwise ANDing this Vector with rhs_, via the provided out_vector_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be ANDed. Otherwise, all elements be ANDed with rhs_ directly. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to AND with this Vector.</param>
		template<typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void And(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_bitwise_and(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of bitwise ANDing this Vector with rhs_ within the provided index range, with copies of elements in indices outside of said range. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be ANDed. Otherwise, all elements be ANDed with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start performing bitwise operations. </para>
		/// <para> EndIndex_: Exclusive index at which to stop performing bitwise operations. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to AND with this Vector within the specified index range.</param>
		/// <returns>
		///		Copy of this Vector using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq),
		///		with rhs_ ANDed with indices in the provided range.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> AndRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_and_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> AndRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_and_range<size, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of bitwise ANDing this Vector with rhs_ within the provided index range,
		///		with copies of elements in indices outside of said range, via the provided out_vector_.
		/// </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be ANDed. Otherwise, all elements be ANDed with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start performing bitwise operations. </para>
		/// <para> EndIndex_: Exclusive index at which to stop performing bitwise operations. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to AND with this Vector within the specified index range.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void AndRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_bitwise_and_range<BeginIndex_, EndIndex_>(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of bitwise ANDing this Vector with rhs_ within the provided index range. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be ANDed. Otherwise, all elements be ANDed with rhs_ directly. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing bitwise operation results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing bitwise operation results to the output Vector. </para>
		/// <para> AndBegin_: Inclusive index at which to start reading elements from this Vector (and rhs_ if it is an EmuMath Vector) to perform bitwise operations. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to AND with this Vector's elements in the specified range.</param>
		/// <returns>
		///		EmuMath Vector using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq),
		///		with indices within the provided range containing AND results starting AndBegin_, and default-constructed elements elsewhere.
		/// </returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AndBegin_, std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> AndRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_and_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, AndBegin_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AndBegin_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> AndRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_and_range_no_copy<size, OutT_, OutBegin_, OutEnd_, AndBegin_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Outputs the result of bitwise ANDing this Vector with rhs_ within the provided index range, via the provided out_vector_. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be ANDed. Otherwise, all elements be ANDed with rhs_ directly. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing bitwise operation results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing bitwise operation results to the output Vector. </para>
		/// <para> AndBegin_: Inclusive index at which to start reading elements from this Vector (and rhs_ if it is an EmuMath Vector) to perform bitwise operations. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to AND with this Vector's elements in the specified range.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AndBegin_, typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void AndRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_bitwise_and_range_no_copy<OutBegin_, OutEnd_, AndBegin_>(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of bitwise ORing this Vector with rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be ORed. Otherwise, all elements be ORed with rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to OR with this Vector.</param>
		/// <returns>Copy of this Vector ORed with rhs_, using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq).</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Or(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_or<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Or(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_or<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Outputs the result of bitwise ORing this Vector with rhs_, via the provided out_vector_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be ORed. Otherwise, all elements be ORed with rhs_ directly. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to OR with this Vector.</param>
		template<typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void Or(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_bitwise_or(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of bitwise ORing this Vector with rhs_ within the provided index range, with copies of elements in indices outside of said range. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be ORed. Otherwise, all elements be ORed with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start performing bitwise operations. </para>
		/// <para> EndIndex_: Exclusive index at which to stop performing bitwise operations. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to OR with this Vector within the specified index range.</param>
		/// <returns>
		///		Copy of this Vector using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq),
		///		with rhs_ ORed with indices in the provided range.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> OrRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_or_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> OrRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_or_range<size, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of bitwise ORing this Vector with rhs_ within the provided index range,
		///		with copies of elements in indices outside of said range, via the provided out_vector_.
		/// </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be ORed. Otherwise, all elements be ORed with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start performing bitwise operations. </para>
		/// <para> EndIndex_: Exclusive index at which to stop performing bitwise operations. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to OR with this Vector within the specified index range.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void OrRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_bitwise_or_range<BeginIndex_, EndIndex_>(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of bitwise ORing this Vector with rhs_ within the provided index range. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be ORed. Otherwise, all elements be ORed with rhs_ directly. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing bitwise operation results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing bitwise operation results to the output Vector. </para>
		/// <para> OrBegin_: Inclusive index at which to start reading elements from this Vector (and rhs_ if it is an EmuMath Vector) to perform bitwise operations. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to OR with this Vector's elements in the specified range.</param>
		/// <returns>
		///		EmuMath Vector using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq),
		///		with indices within the provided range containing OR results starting OrBegin_, and default-constructed elements elsewhere.
		/// </returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t OrBegin_, std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> OrRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_or_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, OrBegin_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t OrBegin_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> OrRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_or_range_no_copy<size, OutT_, OutBegin_, OutEnd_, OrBegin_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Outputs the result of bitwise ORing this Vector with rhs_ within the provided index range, via the provided out_vector_. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be ORed. Otherwise, all elements be ORed with rhs_ directly. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing bitwise operation results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing bitwise operation results to the output Vector. </para>
		/// <para> OrBegin_: Inclusive index at which to start reading elements from this Vector (and rhs_ if it is an EmuMath Vector) to perform bitwise operations. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to OR with this Vector's elements in the specified range.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t OrBegin_, typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void OrRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_bitwise_or_range_no_copy<OutBegin_, OutEnd_, OrBegin_>(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of bitwise XORing this Vector with rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be ORed. Otherwise, all elements be XORed with rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to XOR with this Vector.</param>
		/// <returns>Copy of this Vector XORed with rhs_, using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq).</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Xor(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_xor<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Xor(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_xor<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Outputs the result of bitwise XORing this Vector with rhs_, via the provided out_vector_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be XORed. Otherwise, all elements be XORed with rhs_ directly. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to XOR with this Vector.</param>
		template<typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void Xor(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_bitwise_xor(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of bitwise XORing this Vector with rhs_ within the provided index range, with copies of elements in indices outside of said range. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be XORed. Otherwise, all elements be XORed with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start performing bitwise operations. </para>
		/// <para> EndIndex_: Exclusive index at which to stop performing bitwise operations. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to XOR with this Vector within the specified index range.</param>
		/// <returns>
		///		Copy of this Vector using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq),
		///		with rhs_ XORed with indices in the provided range.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> XorRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_xor_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> XorRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_xor_range<size, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of bitwise XORing this Vector with rhs_ within the provided index range,
		///		with copies of elements in indices outside of said range, via the provided out_vector_.
		/// </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be XORed. Otherwise, all elements be XORed with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start performing bitwise operations. </para>
		/// <para> EndIndex_: Exclusive index at which to stop performing bitwise operations. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to XOR with this Vector within the specified index range.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void XorRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_bitwise_xor_range<BeginIndex_, EndIndex_>(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of bitwise XORing this Vector with rhs_ within the provided index range. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be XORed. Otherwise, all elements be ORed with rhs_ directly. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing bitwise operation results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing bitwise operation results to the output Vector. </para>
		/// <para> XorBegin_: Inclusive index at which to start reading elements from this Vector (and rhs_ if it is an EmuMath Vector) to perform bitwise operations. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to XOR with this Vector's elements in the specified range.</param>
		/// <returns>
		///		EmuMath Vector using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq),
		///		with indices within the provided range containing XOR results starting XorBegin_, and default-constructed elements elsewhere.
		/// </returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t XorBegin_, std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> XorRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_or_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, XorBegin_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t XorBegin_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> XorRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_or_range_no_copy<size, OutT_, OutBegin_, OutEnd_, XorBegin_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Outputs the result of bitwise XORing this Vector with rhs_ within the provided index range, via the provided out_vector_. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be XORed. Otherwise, all elements be XORed with rhs_ directly. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing bitwise operation results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing bitwise operation results to the output Vector. </para>
		/// <para> XorBegin_: Inclusive index at which to start reading elements from this Vector (and rhs_ if it is an EmuMath Vector) to perform bitwise operations. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to XOR with this Vector's elements in the specified range.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t XorBegin_, typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void XorRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_bitwise_or_range_no_copy<OutBegin_, OutEnd_, XorBegin_>(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of left-shifting this Vector with rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be used for shifts. Otherwise, all elements will be shifted with rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to shift this Vector's elements via.</param>
		/// <returns>Copy of this Vector left-shifted with rhs_, using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq).</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> ShiftLeft(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_left<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> ShiftLeft(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_left<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Outputs the result of bitwise left-shifting this Vector with rhs_, via the provided out_vector_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be used for shifts. Otherwise, all elements will be shifted with rhs_ directly. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to shift this Vector's elements via.</param>
		template<typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void ShiftLeft(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_shift_left(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of left-shifting this Vector with rhs_ within the provided index range, with copies of elements in indices outside of said range. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be used for shifts. Otherwise, all elements will be shifted with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start performing shift operations. </para>
		/// <para> EndIndex_: Exclusive index at which to stop performing shift operations. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to shift this Vector's elements via.</param>
		/// <returns>
		///		Copy of this Vector using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq),
		///		with indices in the provided range left-shifted using rhs_.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> ShiftLeftRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_left_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> ShiftLeftRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_left_range<size, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of left-shifting this Vector with rhs_ within the provided index range,
		///		with copies of elements in indices outside of said range, via the provided out_vector_.
		/// </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be used for shifts. Otherwise, all elements will be shifted with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start performing shift operations. </para>
		/// <para> EndIndex_: Exclusive index at which to stop performing shift operations. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to shift this Vector's elements via.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void ShiftLeftRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_shift_left_range<BeginIndex_, EndIndex_>(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of left-shifting this Vector with rhs_ within the provided index range. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be used for shifts. Otherwise, all elements will be shifted with rhs_ directly. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing shift operation results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing shift operation results to the output Vector. </para>
		/// <para> ShiftBegin_: Inclusive index at which to start reading elements from this Vector (and rhs_ if it is an EmuMath Vector) to perform shift operations. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to shift this Vector's elements via.</param>
		/// <returns>
		///		EmuMath Vector using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq),
		///		with indices within the provided range containing left-shift results starting at ShiftBegin_, and default-constructed elements elsewhere.
		/// </returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ShiftBegin_, std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> ShiftLeftRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_left_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, ShiftBegin_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ShiftBegin_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> ShiftLeftRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_left_range_no_copy<size, OutT_, OutBegin_, OutEnd_, ShiftBegin_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Outputs the result of left-shifting this Vector with rhs_ within the provided index range, via the provided out_vector_. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be used for shifts. Otherwise, all elements will be shifted with rhs_ directly. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing shift operation results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing shift operation results to the output Vector. </para>
		/// <para> ShiftBegin_: Inclusive index at which to start reading elements from this Vector (and rhs_ if it is an EmuMath Vector) to perform shift operations. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to shift this Vector's elements via.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ShiftBegin_, typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void ShiftLeftRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_shift_left_range_no_copy<OutBegin_, OutEnd_, ShiftBegin_>(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of right-shifting this Vector with rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be used for shifts. Otherwise, all elements will be shifted with rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to shift this Vector's elements via.</param>
		/// <returns>Copy of this Vector right-shifted with rhs_, using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq).</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> ShiftRight(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_right<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> ShiftRight(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_right<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Outputs the result of bitwise right-shifting this Vector with rhs_, via the provided out_vector_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be used for shifts. Otherwise, all elements will be shifted with rhs_ directly. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to shift this Vector's elements via.</param>
		template<typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void ShiftRight(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_shift_right(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of right-shifting this Vector with rhs_ within the provided index range, with copies of elements in indices outside of said range. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be used for shifts. Otherwise, all elements will be shifted with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start performing shift operations. </para>
		/// <para> EndIndex_: Exclusive index at which to stop performing shift operations. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to shift this Vector's elements via.</param>
		/// <returns>
		///		Copy of this Vector using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq),
		///		with indices in the provided range right-shifted using rhs_.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> ShiftRightRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_right_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> ShiftRightRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_right_range<size, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of right-shifting this Vector with rhs_ within the provided index range,
		///		with copies of elements in indices outside of said range, via the provided out_vector_.
		/// </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be used for shifts. Otherwise, all elements will be shifted with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start performing shift operations. </para>
		/// <para> EndIndex_: Exclusive index at which to stop performing shift operations. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to shift this Vector's elements via.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void ShiftRightRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_shift_right_range<BeginIndex_, EndIndex_>(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the result of right-shifting this Vector with rhs_ within the provided index range. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be used for shifts. Otherwise, all elements will be shifted with rhs_ directly. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing shift operation results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing shift operation results to the output Vector. </para>
		/// <para> ShiftBegin_: Inclusive index at which to start reading elements from this Vector (and rhs_ if it is an EmuMath Vector) to perform shift operations. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to shift this Vector's elements via.</param>
		/// <returns>
		///		EmuMath Vector using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq),
		///		with indices within the provided range containing right-shift results starting at ShiftBegin_, and default-constructed elements elsewhere.
		/// </returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ShiftBegin_, std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> ShiftRightRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_right_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, ShiftBegin_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ShiftBegin_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> ShiftRightRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_right_range_no_copy<size, OutT_, OutBegin_, OutEnd_, ShiftBegin_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Outputs the result of right-shifting this Vector with rhs_ within the provided index range, via the provided out_vector_. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be used for shifts. Otherwise, all elements will be shifted with rhs_ directly. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing shift operation results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing shift operation results to the output Vector. </para>
		/// <para> ShiftBegin_: Inclusive index at which to start reading elements from this Vector (and rhs_ if it is an EmuMath Vector) to perform shift operations. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Vector to shift this Vector's elements via.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ShiftBegin_, typename Rhs_, std::size_t OutSize_, typename OutT_>
		constexpr inline void ShiftRightRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_shift_right_range_no_copy<OutBegin_, OutEnd_, ShiftBegin_>(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary> Returns a bitwise NOT form of this Vector, equivalent to `-this_vector`. </summary>
		/// <returns>Copy of this Vector with its elements bitwise NOT-ed, using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq).</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Not() const
		{
			return EmuMath::Helpers::vector_bitwise_not<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Not() const
		{
			return EmuMath::Helpers::vector_bitwise_not<size, OutT_>(*this);
		}
		
		/// <summary> Ouputs a bitwise NOT form of this Vector to the provided out_vector_, equivalent to `out_vector_ = ~this_vector`. </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void Not(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::vector_bitwise_not(out_vector_, *this);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with the provided index range bitwise NOT-ed. </para>
		/// <para> BeginIndex_: Inclusive index at which to start bitwise NOT-ing elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop bitwise NOT-ing elements. </para>
		/// </summary>
		/// <returns>
		///		EmuMath Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq),
		///		containing a copy of this Vector with the provided index range bitwise NOT-ed.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> NotRange() const
		{
			return EmuMath::Helpers::vector_bitwise_not_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> NotRange() const
		{
			return EmuMath::Helpers::vector_bitwise_not_range<size, OutT_, BeginIndex_, EndIndex_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with the provided index range bitwise NOT-ed, to the provided out_vector_. </para>
		/// <para> BeginIndex_: Inclusive index at which to start bitwise NOT-ing elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop bitwise NOT-ing elements. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_>
		constexpr inline void NotRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::vector_bitwise_not_range<BeginIndex_, EndIndex_>(out_vector_, *this);
		}

		/// <summary>
		/// <para>
		///		Returns a new EmuMath Vector with its indices outside of the specified range index default-constructed, 
		///		and elements within the provided range constructed as bitwise NOT-ed forms of this Vector's elements, starting at index NotBegin_.
		/// </para>
		/// <para> Indices outside of the specified range in out_vector_ will be default-constructed. </para>
		/// <para> OutBegin_: Inclusive index in the output vector at which to start writing bitwise NOT-ed forms of this Vector's elements. </para>
		/// <para> OutEnd_: Exclusive index in the output vector at which to stop writing bitwise NOT-ed forms of this Vector's elements. </para>
		/// <para> NotBegin_: Inclusive index at which to start reading elements from this Vector in order to perform bitwise operations. </para>
		/// </summary>
		/// <returns>
		///		EmuMath Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq),
		///		containing a partial bitwise NOT copy of this Vector in the specified range, and default values outside of said range.
		/// </returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t NotBegin_, std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> NotRangeNoCopy() const
		{
			return EmuMath::Helpers::vector_bitwise_not_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, NotBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t NotBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> NotRangeNoCopy() const
		{
			return EmuMath::Helpers::vector_bitwise_not_range_no_copy<size, OutT_, OutBegin, OutEnd_, NotBegin_>(*this);
		}

		/// <summary>
		/// <para> Outputs sequential bitwise NOT-ed elements within this Vector, starting at index NotBegin_, to the provided index range in out_vector_.
		/// </para>
		/// <para> Indices outside of the specified range in out_vector_ will not be modified. </para>
		/// <para> OutBegin_: Inclusive index in the output vector at which to start writing bitwise NOT-ed forms of this Vector's elements. </para>
		/// <para> OutEnd_: Exclusive index in the output vector at which to stop writing bitwise NOT-ed forms of this Vector's elements. </para>
		/// <para> NotBegin_: Inclusive index at which to start reading elements from this Vector in order to perform bitwise operations. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t NotBegin_, std::size_t OutSize_, typename OutT_>
		constexpr inline void NotRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::vector_bitwise_not_range_no_copy<OutBegin_, OutEnd_, NotBegin_>(out_vector_, *this);
		}
#pragma endregion

#pragma region ARITHMETIC_ASSIGN_FUNCS
	public:
		/// <summary>
		/// <para> Performs an add-assign operation on this Vector, equivalent to `this_vector += rhs_`. </para>
		/// <para> If rhs_ is an EmuMath Vector: Respective indices will be used for each arithmetic operation; otherwise, all operations will use rhs_ directly. </para>
		/// <para> If both a BeginIndex_ and EndIndex_ is provided, the operation will only be performed for indices within the specified range. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of arithmetic operations.</param>
		/// <returns>Reference to this Vector.</returns>
		template<typename Rhs_>
		constexpr inline this_type& AddAssign(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_add_assign(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_>
		constexpr inline this_type& AddAssign(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_add_assign<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs a subtract-assign operation on this Vector, equivalent to `this_vector -= rhs_`. </para>
		/// <para> If rhs_ is an EmuMath Vector: Respective indices will be used for each arithmetic operation; otherwise, all operations will use rhs_ directly. </para>
		/// <para> If both a BeginIndex_ and EndIndex_ is provided, the operation will only be performed for indices within the specified range. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of arithmetic operations.</param>
		/// <returns>Reference to this Vector.</returns>
		template<typename Rhs_>
		constexpr inline this_type& SubtractAssign(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_subtract_assign(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_>
		constexpr inline this_type& SubtractAssign(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_subtract_assign<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs a multiply-assign operation on this Vector, equivalent to `this_vector *= rhs_`. </para>
		/// <para> If rhs_ is an EmuMath Vector: Respective indices will be used for each arithmetic operation; otherwise, all operations will use rhs_ directly. </para>
		/// <para> If both a BeginIndex_ and EndIndex_ is provided, the operation will only be performed for indices within the specified range. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of arithmetic operations.</param>
		/// <returns>Reference to this Vector.</returns>
		template<typename Rhs_>
		constexpr inline this_type& MultiplyAssign(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_multiply_assign(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_>
		constexpr inline this_type& MultiplyAssign(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_multiply_assign<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs a divide-assign operation on this Vector, equivalent to `this_vector /= rhs_`. </para>
		/// <para> If rhs_ is an EmuMath Vector: Respective indices will be used for each arithmetic operation; otherwise, all operations will use rhs_ directly. </para>
		/// <para> If both a BeginIndex_ and EndIndex_ is provided, the operation will only be performed for indices within the specified range. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of arithmetic operations.</param>
		/// <returns>Reference to this Vector.</returns>
		template<typename Rhs_>
		constexpr inline this_type& DivideAssign(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_divide_assign(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_>
		constexpr inline this_type& DivideAssign(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_divide_assign<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs a modulo-divide-assign operation on this Vector, equivalent to `this_vector %= rhs_`. </para>
		/// <para> If rhs_ is an EmuMath Vector: Respective indices will be used for each arithmetic operation; otherwise, all operations will use rhs_ directly. </para>
		/// <para> If both a BeginIndex_ and EndIndex_ is provided, the operation will only be performed for indices within the specified range. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of arithmetic operations.</param>
		/// <returns>Reference to this Vector.</returns>
		template<typename Rhs_>
		constexpr inline this_type& ModAssign(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_mod_assign(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_>
		constexpr inline this_type& ModAssign(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_mod_assign<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region BITWISE_ASSIGN_FUNCS
		/// <summary>
		/// <para> Performs a bitwise AND-assign operation on this Vector, equivalent to `this_vector &= rhs_`. </para>
		/// <para> If rhs_ is an EmuMath Vector: Respective indices will be used for each bitwise operation; otherwise, all operations will use rhs_ directly. </para>
		/// <para> If both a BeginIndex_ and EndIndex_ is provided, the operation will only be performed for indices within the specified range. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of bitwise operations.</param>
		/// <returns>Reference to this Vector.</returns>
		template<typename Rhs_>
		constexpr inline this_type& AndAssign(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_bitwise_and_assign(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_>
		constexpr inline this_type& AndAssign(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_bitwise_and_assign<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs a bitwise OR-assign operation on this Vector, equivalent to `this_vector |= rhs_`. </para>
		/// <para> If rhs_ is an EmuMath Vector: Respective indices will be used for each bitwise operation; otherwise, all operations will use rhs_ directly. </para>
		/// <para> If both a BeginIndex_ and EndIndex_ is provided, the operation will only be performed for indices within the specified range. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of bitwise operations.</param>
		/// <returns>Reference to this Vector.</returns>
		template<typename Rhs_>
		constexpr inline this_type& OrAssign(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_bitwise_or_assign(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_>
		constexpr inline this_type& OrAssign(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_bitwise_or_assign<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs a bitwise XOR-assign operation on this Vector, equivalent to `this_vector ^= rhs_`. </para>
		/// <para> If rhs_ is an EmuMath Vector: Respective indices will be used for each bitwise operation; otherwise, all operations will use rhs_ directly. </para>
		/// <para> If both a BeginIndex_ and EndIndex_ is provided, the operation will only be performed for indices within the specified range. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of bitwise operations.</param>
		/// <returns>Reference to this Vector.</returns>
		template<typename Rhs_>
		constexpr inline this_type& XorAssign(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_bitwise_xor_assign(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_>
		constexpr inline this_type& XorAssign(Rhs_&& rhs_)
		{
			return EmuMath::Helpers::vector_bitwise_xor_assign<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region MISC_ARITHMETIC_FUNCS
	public:
		/// <summary> Returns the absolute form of this Vector. </summary>
		/// <returns>Copy of this Vector with its elements made absolute, using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq).</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Abs() const
		{
			return EmuMath::Helpers::vector_abs<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Abs() const
		{
			return EmuMath::Helpers::vector_abs<size, OutT_>(*this);
		}

		/// <summary> Outputs the absolute form of this Vector to the provided out_vector_. </summary>
		/// <param name="out_vector_">: EmuMath Vector to output absolute elements to.</param>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void Abs(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::vector_abs(out_vector_, *this);
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
			return EmuMath::Helpers::vector_abs_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> AbsRange() const
		{
			return EmuMath::Helpers::vector_abs_range<size, OutT_, BeginIndex_, EndIndex_>(*this);
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
			EmuMath::Helpers::vector_abs_range<BeginIndex_, EndIndex_>(out_vector_, *this);
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
			return EmuMath::Helpers::vector_abs_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, AbsBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t AbsBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> AbsRangeNoCopy() const
		{
			return EmuMath::Helpers::vector_abs_range_no_copy<size, OutT_, OutBegin, OutEnd_, AbsBegin_>(*this);
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
			EmuMath::Helpers::vector_abs_range_no_copy<OutBegin_, OutEnd_, AbsBegin_>(out_vector_, *this);
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
			return EmuMath::Helpers::vector_lerp<OutSize_, OutT_>(*this, std::forward<ArgB_>(b_), std::forward<ArgT_>(t_));
		}
		template<typename OutT_ = value_type_uq, typename ArgB_, typename ArgT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Lerp(ArgB_&& b_, ArgT_&& t_) const
		{
			return EmuMath::Helpers::vector_lerp<size, OutT_>(*this, std::forward<ArgB_>(b_), std::forward<ArgT_>(t_));
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
			EmuMath::Helpers::vector_lerp(out_vector_, *this, std::forward<ArgB_>(b_), std::forward<ArgT_>(t_));
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
			return EmuMath::Helpers::vector_lerp_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<ArgB_>(b_), std::forward<ArgT_>(t_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename ArgB_, typename ArgT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> LerpRange(ArgB_&& b_, ArgT_&& t_) const
		{
			return EmuMath::Helpers::vector_lerp_range<size, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<ArgB_>(b_), std::forward<ArgT_>(t_));
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
			EmuMath::Helpers::vector_lerp_range<BeginIndex_, EndIndex_>(out_vector_, *this, std::forward<ArgB_>(b_), std::forward<ArgT_>(t_));
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
			return EmuMath::Helpers::vector_lerp_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, LerpBegin_>(*this, std::forward<ArgB_>(b_), std::forward<ArgT_>(t_));
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t LerpBegin_, typename OutT_ = value_type_uq, typename ArgB_, typename ArgT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> LerpRangeNoCopy(ArgB_&& b_, ArgT_&& t_) const
		{
			return EmuMath::Helpers::vector_lerp_range_no_copy<size, OutT_, OutBegin, OutEnd_, LerpBegin_>(*this, std::forward<ArgB_>(b_), std::forward<ArgT_>(t_));
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
		/// <para> LerpBegin_: Inclusive index at which to start reading elements from this Vector (and Vector args) to perform interpolations. </para>
		/// </summary>
		/// <param name="out_vector_">EmuMath Vector to output to.</param>
		/// <param name="b_">Scalar or EmuMath Vector to use as target point(s) for interpolation.</param>
		/// <param name="t_">Scalar or EmuMath Vector to use as weighting(s) for interpolation.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t LerpBegin_, std::size_t OutSize_, typename OutT_, typename ArgB_, typename ArgT_>
		constexpr inline void LerpRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, ArgB_&& b_, ArgT_&& t_) const
		{
			EmuMath::Helpers::vector_lerp_range_no_copy<OutBegin_, OutEnd_, LerpBegin_>(out_vector_, *this, std::forward<ArgB_>(b_), std::forward<ArgT_>(t_));
		}

		/// <summary> Finds the lowest value within this Vector. </summary>
		/// <returns>Lowest value within this Vector, represented as the provided Out_ type (defaults to value_type_uq).</returns>
		template<typename Out_ = value_type_uq>
		[[nodiscard]] constexpr inline Out_ Min() const
		{
			return EmuMath::Helpers::vector_min<Out_>(*this);
		}
		template<typename Out_ = value_type_uq>
		[[nodiscard]] constexpr inline Out_ Min()
		{
			return EmuMath::Helpers::vector_min<Out_>(*this);
		}

		/// <summary>
		/// <para> Finds the lowest value within this Vector. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading values from this Vector. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading values from this Vector. </para>
		/// </summary>
		/// <returns>Lowest value in the provided index range within this Vector, represented as the provided Out_ type (defaults to value_type_uq).</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Out_ = value_type_uq>
		[[nodiscard]] constexpr inline Out_ Min() const
		{
			return EmuMath::Helpers::vector_min<Out_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Out_ = value_type_uq>
		[[nodiscard]] constexpr inline Out_ Min()
		{
			return EmuMath::Helpers::vector_min<Out_, BeginIndex_, EndIndex_>(*this);
		}

		/// <summary>
		/// <para> Outputs a Vector containing the lowest values between this Vector's respective indices and b_. </para>
		/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in this Vector will be compared with b_ directly. </para>
		/// </summary>
		/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
		/// <returns>EmuMath Vector formed of the lowest values of this Vector and b_ in respective indices.</returns>
		template<std::size_t OutSize_, typename OutT_ = preferred_floating_point, typename B_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Min(B_&& b_) const
		{
			return EmuMath::Helpers::vector_min<OutSize_, OutT_>(*this, std::forward<B_>(b_));
		}
		template<typename OutT_ = preferred_floating_point, typename B_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Min(B_&& b_) const
		{
			return EmuMath::Helpers::vector_min<size, OutT_>(*this, std::forward<B_>(b_));
		}

		/// <summary>
		/// <para> Outputs a Vector containing the lowest values between this Vector's respective indices and b_. </para>
		/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in this Vector will be compared with b_ directly. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
		template<typename B_, std::size_t OutSize_, typename OutT_>
		constexpr inline void Min(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, B_&& b_) const
		{
			EmuMath::Helpers::vector_min(out_vector_, *this, std::forward<B_>(b_));
		}

		/// <summary>
		/// <para> Outputs a Vector containing the lowest values between this Vector's respective indices and b_ within the provided index range. </para>
		/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in this Vector will be compared with b_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start outputting min results. </para>
		/// <para> EndIndex_: Exclusive index at which to stop outputting min results. </para>
		/// </summary>
		/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
		/// <returns>
		///		EmuMath Vector formed of the lowest values of this Vector and b_ in respective indices within the provided index range,
		///		and copied values from this Vector outside of said range.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = preferred_floating_point, typename B_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> MinRange(B_&& b_) const
		{
			return EmuMath::Helpers::vector_min_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<B_>(b_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = preferred_floating_point, typename B_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> MinRange(B_&& b_) const
		{
			return EmuMath::Helpers::vector_min_range<size, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<B_>(b_));
		}

		/// <summary>
		/// <para> Outputs a Vector containing the lowest values between this Vector's respective indices and b_ within the provided index range, via the passed out_vector_. </para>
		/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in this Vector will be compared with b_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start outputting min results. </para>
		/// <para> EndIndex_: Exclusive index at which to stop outputting min results. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename B_, std::size_t OutSize_, typename OutT_>
		constexpr inline void MinRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, B_&& b_) const
		{
			EmuMath::Helpers::vector_min_range<BeginIndex_, EndIndex_>(out_vector_, *this, std::forward<B_>(b_));
		}

		/// <summary>
		/// <para> Outputs a Vector with indices in the provided range containing lowest values between this Vector's indices and b_, starting from MinBegin_. </para>
		/// <para> Indices outside of the provided output range will be default-constructed. </para>
		/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in this Vector will be compared with b_ directly. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing to the output Vector. </para>
		/// <para> MinBegin_: Inclusive index at which to start performing operations with this Vector (and b_ if it is an EmuMath Vector). </para>
		/// </summary>
		/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
		/// <returns>EmuMath Vector containing min results from the provided range within the provided output range, and default elements outside of said range.</returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MinBegin_, std::size_t OutSize_, typename OutT_ = preferred_floating_point, typename B_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> MinRangeNoCopy(B_&& b_) const
		{
			return EmuMath::Helpers::vector_min_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, MinBegin_>(*this, std::forward<B_>(b_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MinBegin_, typename OutT_ = preferred_floating_point, typename B_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> MinRangeNoCopy(B_&& b_) const
		{
			return EmuMath::Helpers::vector_min_range_no_copy<size, OutT_, OutBegin_, OutEnd_, MinBegin_>(*this, std::forward<B_>(b_));
		}

		/// <summary>
		/// <para> Outputs the lowest values between this Vector's indices and b_, starting from MinBegin_, to the passed out_vector_ in the provided index range. </para>
		/// <para> Indices outside of the provided output range will not be modified. </para>
		/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in this Vector will be compared with b_ directly. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing to the output Vector. </para>
		/// <para> MinBegin_: Inclusive index at which to start performing operations with this Vector (and b_ if it is an EmuMath Vector). Incremented per iteration. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MinBegin_, typename B_, std::size_t OutSize_, typename OutT_>
		constexpr inline void MinRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, B_&& b_) const
		{
			EmuMath::Helpers::vector_min_range_no_copy<OutBegin_, OutEnd_, MinBegin_>(out_vector_, *this, std::forward<B_>(b_));
		}

		/// <summary> Finds the greatest value within this Vector. </summary>
		/// <returns>Greatest value within this Vector, represented as the provided Out_ type (defaults to value_type_uq).</returns>
		template<typename Out_ = value_type_uq>
		[[nodiscard]] constexpr inline Out_ Max() const
		{
			return EmuMath::Helpers::vector_max<Out_>(*this);
		}
		template<typename Out_ = value_type_uq>
		[[nodiscard]] constexpr inline Out_ Max()
		{
			return EmuMath::Helpers::vector_max<Out_>(*this);
		}

		/// <summary>
		/// <para> Finds the greatest value within this Vector, using only indices within the provided (theoretical) range. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading values from this Vector. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading values from this Vector. </para>
		/// </summary>
		/// <returns>Greatest value in the provided index range within this Vector, represented as the provided Out_ type (defaults to value_type_uq).</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Out_ = value_type_uq>
		[[nodiscard]] constexpr inline Out_ Max() const
		{
			return EmuMath::Helpers::vector_max<Out_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Out_ = value_type_uq>
		[[nodiscard]] constexpr inline Out_ Max()
		{
			return EmuMath::Helpers::vector_max<Out_, BeginIndex_, EndIndex_>(*this);
		}

		/// <summary>
		/// <para> Outputs a Vector containing the greatest values between this Vector's respective indices and b_. </para>
		/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in this Vector will be compared with b_ directly. </para>
		/// </summary>
		/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
		/// <returns>EmuMath Vector formed of the greatest values of this Vector and b_ in respective indices.</returns>
		template<std::size_t OutSize_, typename OutT_ = preferred_floating_point, typename B_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Max(B_&& b_) const
		{
			return EmuMath::Helpers::vector_max<OutSize_, OutT_>(*this, std::forward<B_>(b_));
		}
		template<typename OutT_ = preferred_floating_point, typename B_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Max(B_&& b_) const
		{
			return EmuMath::Helpers::vector_max<size, OutT_>(*this, std::forward<B_>(b_));
		}

		/// <summary>
		/// <para> Outputs a Vector containing the greatest values between this Vector's respective indices and b_. </para>
		/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in this Vector will be compared with b_ directly. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
		template<typename B_, std::size_t OutSize_, typename OutT_>
		constexpr inline void Max(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, B_&& b_) const
		{
			EmuMath::Helpers::vector_max(out_vector_, *this, std::forward<B_>(b_));
		}

		/// <summary>
		/// <para> Outputs a Vector containing the greatest values between this Vector's respective indices and b_ within the provided index range. </para>
		/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in this Vector will be compared with b_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start outputting min results. </para>
		/// <para> EndIndex_: Exclusive index at which to stop outputting min results. </para>
		/// </summary>
		/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
		/// <returns>
		///		EmuMath Vector formed of the greatest values of this Vector and b_ in respective indices within the provided index range,
		///		and copied values from this Vector outside of said range.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = preferred_floating_point, typename B_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> MaxRange(B_&& b_) const
		{
			return EmuMath::Helpers::vector_max_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<B_>(b_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = preferred_floating_point, typename B_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> MaxRange(B_&& b_) const
		{
			return EmuMath::Helpers::vector_max_range<size, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<B_>(b_));
		}

		/// <summary>
		/// <para> Outputs a Vector containing the greatest values between this Vector's respective indices and b_ within the provided index range, via the passed out_vector_. </para>
		/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in this Vector will be compared with b_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start outputting min results. </para>
		/// <para> EndIndex_: Exclusive index at which to stop outputting min results. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename B_, std::size_t OutSize_, typename OutT_>
		constexpr inline void MaxRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, B_&& b_) const
		{
			EmuMath::Helpers::vector_max_range<BeginIndex_, EndIndex_>(out_vector_, *this, std::forward<B_>(b_));
		}

		/// <summary>
		/// <para> Outputs a Vector with indices in the provided range containing the greatest values between this Vector's indices and b_, starting from MaxBegin_. </para>
		/// <para> Indices outside of the provided output range will be default-constructed. </para>
		/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in this Vector will be compared with b_ directly. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing to the output Vector. </para>
		/// <para> MaxBegin_: Inclusive index at which to start performing operations with this Vector (and b_ if it is an EmuMath Vector). </para>
		/// </summary>
		/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
		/// <returns>EmuMath Vector containing max results from the provided range within the provided output range, and default elements outside of said range.</returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MaxBegin_, std::size_t OutSize_, typename OutT_ = preferred_floating_point, typename B_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> MaxRangeNoCopy(B_&& b_) const
		{
			return EmuMath::Helpers::vector_max_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, MaxBegin_>(*this, std::forward<B_>(b_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MaxBegin_, typename OutT_ = preferred_floating_point, typename B_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> MaxRangeNoCopy(B_&& b_) const
		{
			return EmuMath::Helpers::vector_max_range_no_copy<size, OutT_, OutBegin_, OutEnd_, MaxBegin_>(*this, std::forward<B_>(b_));
		}

		/// <summary>
		/// <para> Outputs the greatest values between this Vector's indices and b_, starting from MaxBegin_, to the passed out_vector_ in the provided index range. </para>
		/// <para> Indices outside of the provided output range will not be modified. </para>
		/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in this Vector will be compared with b_ directly. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing to the output Vector. </para>
		/// <para> MaxBegin_: Inclusive index at which to start performing operations with this Vector (and b_ if it is an EmuMath Vector). Incremented per iteration. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MaxBegin_, typename B_, std::size_t OutSize_, typename OutT_>
		constexpr inline void MaxRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, B_&& b_) const
		{
			EmuMath::Helpers::vector_max_range_no_copy<OutBegin_, OutEnd_, MaxBegin_>(out_vector_, *this, std::forward<B_>(b_));
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector with elements clamped to a minimum of min_. </para>
		/// <para> If Min_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to min_ directly. </para>
		/// </summary>
		/// <param name="min_">: Scalar or EmuMath Vector to clamp this Vector's elements to a minimum of.</param>
		/// <returns>EmuMath Vector copy of this Vector with elements clamped to a minimum of min_.</returns>
		template<std::size_t OutSize_, typename OutT_ = preferred_floating_point, typename Min_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> ClampMin(Min_&& min_) const
		{
			return EmuMath::Helpers::vector_clamp_min<OutSize_, OutT_>(*this, std::forward<Min_>(min_));
		}
		template<typename OutT_ = preferred_floating_point, typename Min_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> ClampMin(Min_&& min_) const
		{
			return EmuMath::Helpers::vector_clamp_min<size, OutT_>(*this, std::forward<Min_>(min_));
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector with elements clamped to a minimum of min_. </para>
		/// <para> If Min_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to min_ directly. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="min_">: Scalar or EmuMath Vector to clamp this Vector's elements to a minimum of.</param>
		template<typename Min_, std::size_t OutSize_, typename OutT_>
		constexpr inline void ClampMin(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Min_&& min_) const
		{
			EmuMath::Helpers::vector_clamp_min(out_vector_, *this, std::forward<Min_>(min_));
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector with elements in the provided range clamped to a minimum of min_. </para>
		/// <para> If Min_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to min_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start clamping elements. </para>
		/// <para> EndIndex_: Inclusive index at which to stop clamping elements. </para>
		/// </summary>
		/// <param name="min_">: Scalar or EmuMath Vector to clamp this Vector's elements to a minimum of.</param>
		/// <returns>EmuMath Vector copy of this Vector with elements in the provided range clamped to a minimum of min_.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = preferred_floating_point, typename Min_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> ClampMinRange(Min_&& min_) const
		{
			return EmuMath::Helpers::vector_clamp_min_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Min_>(min_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = preferred_floating_point, typename Min_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> ClampMinRange(Min_&& min_) const
		{
			return EmuMath::Helpers::vector_clamp_min_range<size, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Min_>(min_));
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector with elements in the provided range clamped to a minimum of min_. </para>
		/// <para> If Min_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to min_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start clamping elements. </para>
		/// <para> EndIndex_: Inclusive index at which to stop clamping elements. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="min_">: Scalar or EmuMath Vector to clamp this Vector's elements to a minimum of.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Min_, std::size_t OutSize_, typename OutT_>
		constexpr inline void ClampMinRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Min_&& min_) const
		{
			EmuMath::Helpers::vector_clamp_min_range<BeginIndex_, EndIndex_>(out_vector_, *this, std::forward<Min_>(min_));
		}

		/// <summary>
		/// <para>
		///		Outputs an EmuMath Vector with values in the provided range containing the results of clamping this Vector to a minimum of min_,
		///		starting from index ClampBegin_.
		/// </para>
		/// <para> Indices outside of the specified range will be default-constructed. </para>
		/// <para> If Min_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to min_ directly. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing clamp results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing clamp results to the output Vector. </para>
		/// <para> ClampBegin_: Inclusive index at which to start reading from EmuMath Vector arguments to perform clamps. Incremented by 1 after each clamp. </para>
		/// </summary>
		/// <param name="min_">: Scalar or EmuMath Vector to clamp this Vector's elements to a minimum of.</param>
		/// <returns>EmuMath Vector containing clamp results in the specified output range, and default elements outside of said range.</returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ClampBegin_, std::size_t OutSize_, typename OutT_ = preferred_floating_point, typename Min_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> ClampMinRangeNoCopy(Min_&& min_) const
		{
			return EmuMath::Helpers::vector_clamp_min_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, ClampBegin_>(*this, std::forward<Min_>(min_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ClampBegin_, typename OutT_ = preferred_floating_point, typename Min_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> ClampMinRangeNoCopy(Min_&& min_) const
		{
			return EmuMath::Helpers::vector_clamp_min_range_no_copy<size, OutT_, OutBegin_, OutEnd_, ClampBegin_>(*this, std::forward<Min_>(min_));
		}

		/// <summary>
		/// <para> Outputs the results of clamping this Vector to a minimum of min_, starting from index ClampBegin_, via the passed out_vector_. </para>
		/// <para> Indices outside of the specified range will be default-constructed. </para>
		/// <para> If Min_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to min_ directly. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing clamp results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing clamp results to the output Vector. </para>
		/// <para> ClampBegin_: Inclusive index at which to start reading from EmuMath Vector arguments to perform clamps. Incremented by 1 after each clamp. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="min_">: Scalar or EmuMath Vector to clamp this Vector's elements to a minimum of.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ClampBegin_, typename Min_, std::size_t OutSize_, typename OutT_>
		constexpr inline void ClampMinRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Min_&& min_) const
		{
			EmuMath::Helpers::vector_clamp_min_range_no_copy<OutBegin_, OutEnd_, ClampBegin_>(out_vector_, *this, std::forward<Min_>(min_));
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector with elements clamped to a maximum of max_. </para>
		/// <para> If Max_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to max_ directly. </para>
		/// </summary>
		/// <param name="max_">: Scalar or EmuMath Vector to clamp this Vector's elements to a maximum of.</param>
		/// <returns>EmuMath Vector copy of this Vector with elements clamped to a maximum of max_.</returns>
		template<std::size_t OutSize_, typename OutT_ = preferred_floating_point, typename Max_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> ClampMax(Max_&& max_) const
		{
			return EmuMath::Helpers::vector_clamp_max<OutSize_, OutT_>(*this, std::forward<Max_>(max_));
		}
		template<typename OutT_ = preferred_floating_point, typename Max_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> ClampMax(Max_&& max_) const
		{
			return EmuMath::Helpers::vector_clamp_max<size, OutT_>(*this, std::forward<Max_>(max_));
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector with elements clamped to a maximum of max_. </para>
		/// <para> If Max_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to max_ directly. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="max_">: Scalar or EmuMath Vector to clamp this Vector's elements to a maximum of.</param>
		template<typename Max_, std::size_t OutSize_, typename OutT_>
		constexpr inline void ClampMax(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Max_&& max_) const
		{
			EmuMath::Helpers::vector_clamp_max(out_vector_, *this, std::forward<Max_>(max_));
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector with elements in the provided range clamped to a maximum of max_. </para>
		/// <para> If Max_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to max_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start clamping elements. </para>
		/// <para> EndIndex_: Inclusive index at which to stop clamping elements. </para>
		/// </summary>
		/// <param name="max_">: Scalar or EmuMath Vector to clamp this Vector's elements to a maximum of.</param>
		/// <returns>EmuMath Vector copy of this Vector with elements in the provided range clamped to a maximum of max_.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = preferred_floating_point, typename Max_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> ClampMaxRange(Max_&& max_) const
		{
			return EmuMath::Helpers::vector_clamp_max_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Max_>(max_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = preferred_floating_point, typename Max_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> ClampMaxRange(Max_&& max_) const
		{
			return EmuMath::Helpers::vector_clamp_max_range<size, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Max_>(max_));
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector with elements in the provided range clamped to a maximum of max_. </para>
		/// <para> If Max_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to max_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start clamping elements. </para>
		/// <para> EndIndex_: Inclusive index at which to stop clamping elements. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="max_">: Scalar or EmuMath Vector to clamp this Vector's elements to a maximum of.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Max_, std::size_t OutSize_, typename OutT_>
		constexpr inline void ClampMaxRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Max_&& max_) const
		{
			EmuMath::Helpers::vector_clamp_max_range<BeginIndex_, EndIndex_>(out_vector_, *this, std::forward<Max_>(max_));
		}

		/// <summary>
		/// <para>
		///		Outputs an EmuMath Vector with values in the provided range containing the results of clamping this Vector to a maximum of max_,
		///		starting from index ClampBegin_.
		/// </para>
		/// <para> Indices outside of the specified range will be default-constructed. </para>
		/// <para> If Max_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to max_ directly. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing clamp results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing clamp results to the output Vector. </para>
		/// <para> ClampBegin_: Inclusive index at which to start reading from EmuMath Vector arguments to perform clamps. Incremented by 1 after each clamp. </para>
		/// </summary>
		/// <param name="max_">: Scalar or EmuMath Vector to clamp this Vector's elements to a maximum of.</param>
		/// <returns>EmuMath Vector containing clamp results in the specified output range, and default elements outside of said range.</returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ClampBegin_, std::size_t OutSize_, typename OutT_ = preferred_floating_point, typename Max_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> ClampMaxRangeNoCopy(Max_&& max_) const
		{
			return EmuMath::Helpers::vector_clamp_max_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, ClampBegin_>(*this, std::forward<Max_>(max_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ClampBegin_, typename OutT_ = preferred_floating_point, typename Max_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> ClampMaxRangeNoCopy(Max_&& max_) const
		{
			return EmuMath::Helpers::vector_clamp_max_range_no_copy<size, OutT_, OutBegin_, OutEnd_, ClampBegin_>(*this, std::forward<Max_>(max_));
		}

		/// <summary>
		/// <para> Outputs the results of clamping this Vector to a maximum of max_, starting from index ClampBegin_, via the passed out_vector_. </para>
		/// <para> Indices outside of the specified range will be default-constructed. </para>
		/// <para> If Max_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to max_ directly. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing clamp results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing clamp results to the output Vector. </para>
		/// <para> ClampBegin_: Inclusive index at which to start reading from EmuMath Vector arguments to perform clamps. Incremented by 1 after each clamp. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="max_">: Scalar or EmuMath Vector to clamp this Vector's elements to a maximum of.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ClampBegin_, typename Max_, std::size_t OutSize_, typename OutT_>
		constexpr inline void ClampMaxRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Max_&& max_) const
		{
			EmuMath::Helpers::vector_clamp_max_range_no_copy<OutBegin_, OutEnd_, ClampBegin_>(out_vector_, *this, std::forward<Max_>(max_));
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector with elements clamped to the inclusive range min_:max_. </para>
		/// <para> If Min_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to min_ directly. </para>
		/// <para> If Max_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to max_ directly. </para>
		/// </summary>
		/// <param name="min_">: Scalar or EmuMath Vector to clamp this Vector's elements to a minimum of.</param>
		/// <param name="max_">: Scalar or EmuMath Vector to clamp this Vector's elements to a maximum of.</param>
		/// <returns>EmuMath Vector copy of this Vector with elements clamped to the inclusive range min_:max_.</returns>
		template<std::size_t OutSize_, typename OutT_ = preferred_floating_point, typename Min_, typename Max_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Clamp(Min_&& min_, Max_&& max_) const
		{
			return EmuMath::Helpers::vector_clamp<OutSize_, OutT_>(*this, std::forward<Min_>(min_), std::forward<Max_>(max_));
		}
		template<typename OutT_ = preferred_floating_point, typename Min_, typename Max_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Clamp(Min_&& min_, Max_&& max_) const
		{
			return EmuMath::Helpers::vector_clamp<size, OutT_>(*this, std::forward<Min_>(min_), std::forward<Max_>(max_));
		}

		// <summary>
		/// <para> Outputs a copy of this Vector with elements clamped to the inclusive range min_:max_, via the passed out_vector_. </para>
		/// <para> If Min_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to min_ directly. </para>
		/// <para> If Max_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to max_ directly. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="min_">: Scalar or EmuMath Vector to clamp this Vector's elements to a minimum of.</param>
		/// <param name="max_">: Scalar or EmuMath Vector to clamp this Vector's elements to a maximum of.</param>
		template<typename Min_, typename Max_, std::size_t OutSize_, typename OutT_>
		constexpr inline void Clamp(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Min_&& min_, Max_&& max_) const
		{
			EmuMath::Helpers::vector_clamp(out_vector_, *this, std::forward<Min_>(min_), std::forward<Max_>(max_));
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector with elements in the provided range clamped to the inclusive range min_:max_. </para>
		/// <para> If Min_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to min_ directly. </para>
		/// <para> If Max_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to max_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start clamping elements. </para>
		/// <para> EndIndex_: Inclusive index at which to stop clamping elements. </para>
		/// </summary>
		/// <param name="min_">: Scalar or EmuMath Vector to clamp this Vector's elements to a minimum of.</param>
		/// <param name="max_">: Scalar or EmuMath Vector to clamp this Vector's elements to a maximum of.</param>
		/// <returns>EmuMath Vector copy of this Vector with elements in the provided range clamped to the inclusive range min_:max_.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = preferred_floating_point, typename Min_, typename Max_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> ClampRange(Min_&& min_, Max_&& max_) const
		{
			return EmuMath::Helpers::vector_clamp_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Min_>(min_), std::forward<Max_>(max_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = preferred_floating_point, typename Min_, typename Max_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> ClampRange(Min_&& min_, Max_&& max_) const
		{
			return EmuMath::Helpers::vector_clamp_range<size, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Min_>(min_), std::forward<Max_>(max_));
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector with elements in the provided range clamped to the inclusive range min_:max_, via the passed out_vector_. </para>
		/// <para> If Min_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to min_ directly. </para>
		/// <para> If Max_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to max_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start clamping elements. </para>
		/// <para> EndIndex_: Inclusive index at which to stop clamping elements. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="min_">: Scalar or EmuMath Vector to clamp this Vector's elements to a minimum of.</param>
		/// <param name="max_">: Scalar or EmuMath Vector to clamp this Vector's elements to a maximum of.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Min_, typename Max_, std::size_t OutSize_, typename OutT_>
		constexpr inline void ClampRange(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Min_&& min_, Max_&& max_) const
		{
			EmuMath::Helpers::vector_clamp_range<BeginIndex_, EndIndex_>(out_vector_, *this, std::forward<Min_>(min_), std::forward<Max_>(max_));
		}

		/// <summary>
		/// <para>
		///		Outputs an EmuMath Vector with values in the provided range containing the results of clamping this Vector to the inclusive range min_:max_,
		///		starting from index ClampBegin_.
		/// </para>
		/// <para> Indices outside of the specified range will be default-constructed. </para>
		/// <para> If Min_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to min_ directly. </para>
		/// <para> If Max_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to max_ directly. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing clamp results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing clamp results to the output Vector. </para>
		/// <para> ClampBegin_: Inclusive index at which to start reading from EmuMath Vector arguments to perform clamps. Incremented by 1 after each clamp. </para>
		/// </summary>
		/// <param name="min_">: Scalar or EmuMath Vector to clamp this Vector's elements to a minimum of.</param>
		/// <param name="max_">: Scalar or EmuMath Vector to clamp this Vector's elements to a maximum of.</param>
		/// <returns>EmuMath Vector containing clamp results in the specified output range, and default elements outside of said range.</returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ClampBegin_, std::size_t OutSize_, typename OutT_ = preferred_floating_point, typename Min_, typename Max_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> ClampRangeNoCopy(Min_&& min_, Max_&& max_) const
		{
			return EmuMath::Helpers::vector_clamp_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, ClampBegin_>(*this, std::forward<Min_>(min_), std::forward<Max_>(max_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ClampBegin_, typename OutT_ = preferred_floating_point, typename Min_, typename Max_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> ClampRangeNoCopy(Min_&& min_, Max_&& max_) const
		{
			return EmuMath::Helpers::vector_clamp_range_no_copy<size, OutT_, OutBegin_, OutEnd_, ClampBegin_>(*this, std::forward<Min_>(min_), std::forward<Max_>(max_));
		}

		/// <summary>
		/// <para> Outputs the results of clamping this Vector to the inclusve range min_:max_, starting from index ClampBegin_, via the passed out_vector_. </para>
		/// <para> Indices outside of the specified range will not be modified. </para>
		/// <para> If Max_ is an EmuMath Vector: Respective indices will be clamped to. Otherwise, all indices in this Vector will be clamped to max_ directly. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing clamp results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing clamp results to the output Vector. </para>
		/// <para> ClampBegin_: Inclusive index at which to start reading from EmuMath Vector arguments to perform clamps. Incremented by 1 after each clamp. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="min_">: Scalar or EmuMath Vector to clamp this Vector's elements to a minimum of.</param>
		/// <param name="max_">: Scalar or EmuMath Vector to clamp this Vector's elements to a maximum of.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ClampBegin_, typename Min_, typename Max_, std::size_t OutSize_, typename OutT_>
		constexpr inline void ClampRangeNoCopy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Min_&& min_, Max_&& max_) const
		{
			EmuMath::Helpers::vector_clamp_range_no_copy<OutBegin_, OutEnd_, ClampBegin_>(out_vector_, *this, std::forward<Min_>(min_), std::forward<Max_>(max_));
		}
#pragma endregion

#pragma region ROUNDING_FUNCS
	public:
		/// <summary>
		/// <para> Returns a copy of this Vector with its elements rounded toward negative infinity. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `FloorConstexpr` instead. </para>
		/// </summary>
		/// <returns>Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq>, containing a floored copy of this Vector.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Floor() const
		{
			return EmuMath::Helpers::vector_floor<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Floor() const
		{
			return EmuMath::Helpers::vector_floor<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with its elements rounded toward negative infinity, to the provided out_vector_. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `FloorConstexpr` instead. </para>
		/// </summary>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void Floor(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::vector_ceil(out_vector_, *this);
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
			return EmuMath::Helpers::vector_floor_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> FloorRange() const
		{
			return EmuMath::Helpers::vector_floor_range<size, OutT_, BeginIndex_, EndIndex_>(*this);
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
			EmuMath::Helpers::vector_floor_range<BeginIndex_, EndIndex_>(out_vector_, *this);
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
			return EmuMath::Helpers::vector_floor_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, RoundBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t RoundBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> FloorRangeNoCopy() const
		{
			return EmuMath::Helpers::vector_floor_range_no_copy<size, OutT_, OutBegin, OutEnd_, RoundBegin_>(*this);
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
			EmuMath::Helpers::vector_floor_range_no_copy<OutBegin_, OutEnd_, RoundBegin_>(out_vector_, *this);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with its elements rounded toward positive infinity. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `CeilConstexpr` instead. </para>
		/// </summary>
		/// <returns>Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq>, containing a ceiled copy of this Vector.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Ceil() const
		{
			return EmuMath::Helpers::vector_ceil<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Ceil() const
		{
			return EmuMath::Helpers::vector_ceil<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with its elements rounded toward positive infinity, to the provided out_vector_. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `CeilConstexpr` instead. </para>
		/// </summary>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void Ceil(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::vector_ceil(out_vector_, *this);
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
			return EmuMath::Helpers::vector_ceil_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> CeilRange() const
		{
			return EmuMath::Helpers::vector_ceil_range<size, OutT_, BeginIndex_, EndIndex_>(*this);
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
			EmuMath::Helpers::vector_ceil_range<BeginIndex_, EndIndex_>(out_vector_, *this);
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
			return EmuMath::Helpers::vector_ceil_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, RoundBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t RoundBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> CeilRangeNoCopy() const
		{
			return EmuMath::Helpers::vector_ceil_range_no_copy<size, OutT_, OutBegin, OutEnd_, RoundBegin_>(*this);
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
			EmuMath::Helpers::vector_ceil_range_no_copy<OutBegin_, OutEnd_, RoundBegin_>(out_vector_, *this);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with its elements rounded toward 0. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `TruncConstexpr` instead. </para>
		/// </summary>
		/// <returns>Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq>, containing a truncated copy of this Vector.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Trunc() const
		{
			return EmuMath::Helpers::vector_trunc<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Trunc() const
		{
			return EmuMath::Helpers::vector_trunc<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with its elements rounded toward 0, to the provided out_vector_. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `TruncConstexpr` instead. </para>
		/// </summary>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void Trunc(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::vector_trunc(out_vector_, *this);
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
			return EmuMath::Helpers::vector_trunc_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> TruncRange() const
		{
			return EmuMath::Helpers::vector_trunc_range<size, OutT_, BeginIndex_, EndIndex_>(*this);
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
			EmuMath::Helpers::vector_trunc_range<BeginIndex_, EndIndex_>(out_vector_, *this);
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
			return EmuMath::Helpers::vector_trunc_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, RoundBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t RoundBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> TruncRangeNoCopy() const
		{
			return EmuMath::Helpers::vector_trunc_range_no_copy<size, OutT_, OutBegin, OutEnd_, RoundBegin_>(*this);
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
			EmuMath::Helpers::vector_trunc_range_no_copy<OutBegin_, OutEnd_, RoundBegin_>(out_vector_, *this);
		}
#pragma endregion

#pragma region CONSTEXPR_ROUNDING_FUNCS
	public:
		/// <summary>
		/// <para> Returns a copy of this Vector with its elements rounded toward negative infinity. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `Floor` if calling at runtime. </para>
		/// </summary>
		/// <returns>Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq>, containing a floored copy of this Vector.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> FloorConstexpr() const
		{
			return EmuMath::Helpers::vector_floor_constexpr<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> FloorConstexpr() const
		{
			return EmuMath::Helpers::vector_floor_constexpr<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with its elements rounded toward negative infinity, to the provided out_vector_. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `Floor` if calling at runtime. </para>
		/// </summary>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void FloorConstexpr(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			return EmuMath::Helpers::vector_floor_constexpr(out_vector_, *this);
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
			return EmuMath::Helpers::vector_floor_range_constexpr<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> FloorRangeConstexpr() const
		{
			return EmuMath::Helpers::vector_floor_range_constexpr<size, OutT_, BeginIndex_, EndIndex_>(*this);
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
			EmuMath::Helpers::vector_floor_range_constexpr<BeginIndex_, EndIndex_>(out_vector_, *this);
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
			return EmuMath::Helpers::vector_floor_range_no_copy_constexpr<OutSize_, OutT_, OutBegin_, OutEnd_, RoundBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t RoundBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> FloorRangeNoCopyConstexpr() const
		{
			return EmuMath::Helpers::vector_floor_range_no_copy_constexpr<size, OutT_, OutBegin, OutEnd_, RoundBegin_>(*this);
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
			EmuMath::Helpers::vector_floor_range_no_copy_constexpr<OutBegin_, OutEnd_, RoundBegin_>(out_vector_, *this);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with its elements rounded toward positive infinity. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `Ceil` if calling at runtime. </para>
		/// </summary>
		/// <returns>Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq>, containing a ceiled copy of this Vector.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> CeilConstexpr() const
		{
			return EmuMath::Helpers::vector_ceil_constexpr<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> CeilConstexpr() const
		{
			return EmuMath::Helpers::vector_ceil_constexpr<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with its elements rounded toward positive infinity, to the provided out_vector_. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `Ceil` if calling at runtime. </para>
		/// </summary>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void CeilConstexpr(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			return EmuMath::Helpers::vector_ceil_constexpr(out_vector_, *this);
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
			return EmuMath::Helpers::vector_ceil_range_constexpr<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> CeilRangeConstexpr() const
		{
			return EmuMath::Helpers::vector_ceil_range_constexpr<size, OutT_, BeginIndex_, EndIndex_>(*this);
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
			EmuMath::Helpers::vector_ceil_range_constexpr<BeginIndex_, EndIndex_>(out_vector_, *this);
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
			return EmuMath::Helpers::vector_ceil_range_no_copy_constexpr<OutSize_, OutT_, OutBegin_, OutEnd_, RoundBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t RoundBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> CeilRangeNoCopyConstexpr() const
		{
			return EmuMath::Helpers::vector_ceil_range_no_copy_constexpr<size, OutT_, OutBegin, OutEnd_, RoundBegin_>(*this);
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
			EmuMath::Helpers::vector_ceil_range_no_copy_constexpr<OutBegin_, OutEnd_, RoundBegin_>(out_vector_, *this);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with its elements rounded toward 0. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `Trunc` if calling at runtime. </para>
		/// </summary>
		/// <returns>Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq>, containing a truncated copy of this Vector.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> TruncConstexpr() const
		{
			return EmuMath::Helpers::vector_trunc_constexpr<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> TruncConstexpr() const
		{
			return EmuMath::Helpers::vector_trunc_constexpr<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with its elements rounded toward 0, to the provided out_vector_. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `Trunc` if calling at runtime. </para>
		/// </summary>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void TruncConstexpr(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			return EmuMath::Helpers::vector_trunc_constexpr(out_vector_, *this);
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
			return EmuMath::Helpers::vector_trunc_range_constexpr<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> TruncRangeConstexpr() const
		{
			return EmuMath::Helpers::vector_trunc_range_constexpr<size, OutT_, BeginIndex_, EndIndex_>(*this);
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
			EmuMath::Helpers::vector_trunc_range_constexpr<BeginIndex_, EndIndex_>(out_vector_, *this);
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
			return EmuMath::Helpers::vector_trunc_range_no_copy_constexpr<OutSize_, OutT_, OutBegin_, OutEnd_, RoundBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t RoundBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> TruncRangeNoCopyConstexpr() const
		{
			return EmuMath::Helpers::vector_trunc_range_no_copy_constexpr<size, OutT_, OutBegin, OutEnd_, RoundBegin_>(*this);
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
			EmuMath::Helpers::vector_trunc_range_no_copy_constexpr<OutBegin_, OutEnd_, RoundBegin_>(out_vector_, *this);
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
			return EmuMath::Helpers::vector_shuffle<OutT_, Indices_...>(*this);
		}
		template<typename OutT_, std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), OutT_> Shuffle() const
		{
			return EmuMath::Helpers::vector_shuffle<OutT_, Indices_...>(*this);
		}

		template<std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), value_type_uq> Shuffle()
		{
			return EmuMath::Helpers::vector_shuffle<value_type_uq, Indices_...>(*this);
		}
		template<std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), value_type_uq> Shuffle() const
		{
			return EmuMath::Helpers::vector_shuffle<value_type_uq, Indices_...>(*this);
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
			return EmuMath::Helpers::vector_shuffle_theoretical<OutT_, Indices_...>(*this);
		}
		template<typename OutT_, std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), OutT_> ShuffleTheoretical() const
		{
			return EmuMath::Helpers::vector_shuffle_theoretical<OutT_, Indices_...>(*this);
		}

		template<std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), value_type_uq> ShuffleTheoretical()
		{
			return EmuMath::Helpers::vector_shuffle_theoretical<value_type_uq, Indices_...>(*this);
		}
		template<std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), value_type_uq> ShuffleTheoretical() const
		{
			return EmuMath::Helpers::vector_shuffle_theoretical<value_type_uq, Indices_...>(*this);
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
			return EmuMath::Helpers::vector_shuffle<value_type&, Indices_...>(*this);
		}
		template<std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), const value_type&> RefShuffle() const
		{
			return EmuMath::Helpers::vector_shuffle<const value_type&, Indices_...>(*this);
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
			return EmuMath::Helpers::vector_shuffle<const value_type&, Indices_...>(*this);
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
				return EmuMath::Helpers::vector_mutate<size, value_type_uq, Func_&>(func_, *this, std::forward<Args_>(args_)...);
			}
			else if constexpr (IncludeSelf_ > 0)
			{
				return EmuMath::Helpers::vector_mutate<size, value_type_uq, Func_&>(func_, std::forward<Args_>(args_)..., *this);
			}
			else
			{
				return EmuMath::Helpers::vector_mutate<size, value_type_uq, Func_&>(func_, std::forward<Args_>(args_)...);
			}
		}
		template<std::size_t IncludeSelf_, class Func_, class...Args_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, value_type_uq> Mutate(Func_ func_, Args_&&...args_) const
		{
			if constexpr (IncludeSelf_ < 0)
			{
				return EmuMath::Helpers::vector_mutate<size, value_type_uq, Func_&>(func_, *this, std::forward<Args_>(args_)...);
			}
			else if constexpr (IncludeSelf_ > 0)
			{
				return EmuMath::Helpers::vector_mutate<size, value_type_uq, Func_&>(func_, std::forward<Args_>(args_)..., *this);
			}
			else
			{
				return EmuMath::Helpers::vector_mutate<size, value_type_uq, Func_&>(func_, std::forward<Args_>(args_)...);
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
				return EmuMath::Helpers::vector_mutate<Func_, size, value_type_uq>(*this, std::forward<Args_>(args_)...);
			}
			else if constexpr (IncludeSelf_ > 0)
			{
				return EmuMath::Helpers::vector_mutate<Func_, size, value_type_uq>(std::forward<Args_>(args_)..., *this);
			}
			else
			{
				return EmuMath::Helpers::vector_mutate<Func_, size, value_type_uq>(std::forward<Args_>(args_)...);
			}
		}
		template<class Func_, std::size_t IncludeSelf_, class...Args_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, value_type_uq> Mutate(Args_&&...args_) const
		{
			if constexpr (IncludeSelf_ < 0)
			{
				return EmuMath::Helpers::vector_mutate<Func_, size, value_type_uq>(*this, std::forward<Args_>(args_)...);
			}
			else if constexpr (IncludeSelf_ > 0)
			{
				return EmuMath::Helpers::vector_mutate<Func_, size, value_type_uq>(std::forward<Args_>(args_)..., *this);
			}
			else
			{
				return EmuMath::Helpers::vector_mutate<Func_, size, value_type_uq>(std::forward<Args_>(args_)...);
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
				EmuMath::Helpers::vector_mutate_to<Func_&>(func_, out_vector_, *this, std::forward<Args_>(args_)...);
			}
			else if constexpr (IncludeSelf_ > 0)
			{
				EmuMath::Helpers::vector_mutate_to<Func_&>(func_, out_vector_, std::forward<Args_>(args_)..., *this);
			}
			else
			{
				EmuMath::Helpers::vector_mutate_to<Func_&>(func_, out_vector_, std::forward<Args_>(args_)...);
			}
		}
		template<std::size_t IncludeSelf_, class Func_, class...Args_, std::size_t OutSize_, typename OutT_>
		constexpr inline void MutateTo(Func_ func_, EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Args_&&...args_) const
		{
			if constexpr (IncludeSelf_ < 0)
			{
				EmuMath::Helpers::vector_mutate_to<Func_&>(func_, out_vector_, *this, std::forward<Args_>(args_)...);
			}
			else if constexpr (IncludeSelf_ > 0)
			{
				EmuMath::Helpers::vector_mutate_to<Func_&>(func_, out_vector_, std::forward<Args_>(args_)..., *this);
			}
			else
			{
				EmuMath::Helpers::vector_mutate_to<Func_&>(func_, out_vector_, std::forward<Args_>(args_)...);
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
				EmuMath::Helpers::vector_mutate_to<Func_>(out_vector_, *this, std::forward<Args_>(args_)...);
			}
			else if constexpr (IncludeSelf_ > 0)
			{
				EmuMath::Helpers::vector_mutate_to<Func_>(out_vector_, std::forward<Args_>(args_)..., *this);
			}
			else
			{
				EmuMath::Helpers::vector_mutate_to<Func_>(out_vector_, std::forward<Args_>(args_)...);
			}
		}
		template<class Func_, std::size_t IncludeSelf_, class...Args_, std::size_t OutSize_, typename OutT_>
		constexpr inline void MutateTo(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Args_&&...args_) const
		{
			if constexpr (IncludeSelf_ < 0)
			{
				EmuMath::Helpers::vector_mutate_to<Func_>(out_vector_, *this, std::forward<Args_>(args_)...);
			}
			else if constexpr (IncludeSelf_ > 0)
			{
				EmuMath::Helpers::vector_mutate_to<Func_>(out_vector_, std::forward<Args_>(args_)..., *this);
			}
			else
			{
				EmuMath::Helpers::vector_mutate_to<Func_>(out_vector_, std::forward<Args_>(args_)...);
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
				EmuMath::Helpers::vector_mutate_range<BeginIndex_, EndIndex_, ArgBeginIndex_, Func_&>(func_, out_vector_, *this, std::forward<Args_>(args_)...);
			}
			else if constexpr (IncludeSelf_ > 0)
			{
				EmuMath::Helpers::vector_mutate_range<BeginIndex_, EndIndex_, ArgBeginIndex_, Func_&>(func_, out_vector_, std::forward<Args_>(args_)..., *this);
			}
			else
			{
				EmuMath::Helpers::vector_mutate_range<BeginIndex_, EndIndex_, ArgBeginIndex_, Func_&>(func_, out_vector_, std::forward<Args_>(args_)...);
			}
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ArgBeginIndex_, std::size_t IncludeSelf_, class Func_, class...Args_, std::size_t OutSize_, typename OutT_>
		constexpr inline void MutateRange(Func_ func_, EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Args_&&...args_) const
		{
			if constexpr (IncludeSelf_ < 0)
			{
				EmuMath::Helpers::vector_mutate_range<BeginIndex_, EndIndex_, ArgBeginIndex_, Func_&>(func_, out_vector_, *this, std::forward<Args_>(args_)...);
			}
			else if constexpr (IncludeSelf_ > 0)
			{
				EmuMath::Helpers::vector_mutate_range<BeginIndex_, EndIndex_, ArgBeginIndex_, Func_&>(func_, out_vector_, std::forward<Args_>(args_)..., *this);
			}
			else
			{
				EmuMath::Helpers::vector_mutate_range<BeginIndex_, EndIndex_, ArgBeginIndex_, Func_&>(func_, out_vector_, std::forward<Args_>(args_)...);
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

#pragma region CONCAT_FUNCS
		/// <summary>
		/// <para> Concatenates this Vector with the passed EmuMath Vector to form a new single Vector. </para>
		/// <para> If Left_ is true, this Vector will appear on the left of concatenation; otherwise, it will appear on the right. </para>
		/// </summary>
		/// <typeparam name="OutT_">T_ argument for the output Vector.</typeparam>
		/// <param name="other_vector_">EmuMath Vector to concatenate this Vector with.</param>
		/// <returns>This Vector concatenated with the passed EmuMath Vector.</returns>
		template<typename OutT_ = value_type_uq, bool Left_ = true, std::size_t OtherSize_, typename OtherT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size + OtherSize_, OutT_> Concat(const EmuMath::NewVector<OtherSize_, OtherT_>& other_vector_)
		{
			if constexpr (Left_)
			{
				return EmuMath::Helpers::vector_concat<OutT_>(*this, other_vector_);
			}
			else
			{
				return EmuMath::Helpers::vector_concat<OutT_>(other_vector_, *this);
			}
		}
		template<typename OutT_ = value_type_uq, bool Left_ = true, std::size_t OtherSize_, typename OtherT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size + OtherSize_, OutT_> Concat(const EmuMath::NewVector<OtherSize_, OtherT_>& other_vector_) const
		{
			if constexpr (Left_)
			{
				return EmuMath::Helpers::vector_concat<OutT_>(*this, other_vector_);
			}
			else
			{
				return EmuMath::Helpers::vector_concat<OutT_>(other_vector_, *this);
			}
		}

		template<typename OutT_ = value_type_uq, bool Left_ = true, std::size_t OtherSize_, typename OtherT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size + OtherSize_, OutT_> Concat(EmuMath::NewVector<OtherSize_, OtherT_>& other_vector_)
		{
			if constexpr (Left_)
			{
				return EmuMath::Helpers::vector_concat<OutT_>(*this, other_vector_);
			}
			else
			{
				return EmuMath::Helpers::vector_concat<OutT_>(other_vector_, *this);
			}
		}
		template<typename OutT_ = value_type_uq, bool Left_ = true, std::size_t OtherSize_, typename OtherT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size + OtherSize_, OutT_> Concat(EmuMath::NewVector<OtherSize_, OtherT_>& other_vector_) const
		{
			if constexpr (Left_)
			{
				return EmuMath::Helpers::vector_concat<OutT_>(*this, other_vector_);
			}
			else
			{
				return EmuMath::Helpers::vector_concat<OutT_>(other_vector_, *this);
			}
		}

		template<typename OutT_ = value_type_uq, bool Left_ = true, std::size_t OtherSize_, typename OtherT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size + OtherSize_, OutT_> Concat(EmuMath::NewVector<OtherSize_, OtherT_>&& other_vector_)
		{
			if constexpr (Left_)
			{
				return EmuMath::Helpers::vector_concat<OutT_>(*this, std::forward<EmuMath::NewVector<OtherSize_, OtherT_>>(other_vector_));
			}
			else
			{
				return EmuMath::Helpers::vector_concat<OutT_>(std::forward<EmuMath::NewVector<OtherSize_, OtherT_>>(other_vector_), *this);
			}
		}
		template<typename OutT_ = value_type_uq, bool Left_ = true, std::size_t OtherSize_, typename OtherT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size + OtherSize_, OutT_> Concat(EmuMath::NewVector<OtherSize_, OtherT_>&& other_vector_) const
		{
			if constexpr (Left_)
			{
				return EmuMath::Helpers::vector_concat<OutT_>(*this, std::forward<EmuMath::NewVector<OtherSize_, OtherT_>>(other_vector_));
			}
			else
			{
				return EmuMath::Helpers::vector_concat<OutT_>(std::forward<EmuMath::NewVector<OtherSize_, OtherT_>>(other_vector_), *this);
			}
		}
#pragma endregion

#pragma region VECTOR_OPERATIONS
		/// <summary>
		/// <para>
		///		Calculates the dot product of this Vector and the passed vector_b_,
		///		output as the provided Out_ type (defaults to this Vector's preferred_floating_point).
		/// </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output the calculated dot product as. Defaults to preferred_floating_point.</typeparam>
		/// <param name="vector_b_">: EmuMath Vector to calculate the dot product of this Vector with.</param>
		/// <returns>Dot product of this Vector and the passed vector_b_.</returns>
		template<typename Out_ = preferred_floating_point, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline Out_ Dot(const EmuMath::NewVector<SizeB_, TB_>& vector_b_) const
		{
			return EmuMath::Helpers::vector_dot<Out_>(*this, vector_b_);
		}
		/// <summary>
		/// <para>
		///		Calculates the dot product of this Vector and the passed vector_b_, using indices in the provided range,
		///		and outputted as the provided Out_ type (defaults to this Vector's preferred_floating_point).
		/// </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading from both Vectors to form a dot product. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading from both Vectors to form a dot product. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output the calculated dot product as. Defaults to preferred_floating_point.</typeparam>
		/// <param name="vector_b_">: EmuMath Vector to calculate the dot product of this Vector with.</param>
		/// <returns>Dot product of this Vector and the passed vector_b_.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Out_ = preferred_floating_point, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline Out_ Dot(const EmuMath::NewVector<SizeB_, TB_>& vector_b_) const
		{
			return EmuMath::Helpers::vector_dot<BeginIndex_, EndIndex_, Out_>(*this, vector_b_);
		}

		/// <summary>
		/// <para> Calculates the squared magnitude of this Vector, output as the provided Out_ type (defaults to this Vector's preferred_floating_point). </para>
		/// <para> This is equivalent to forming the dot product of this Vector with itself. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output the calculated square magnitude as. Defaults to preferred_floating_point.</typeparam>
		/// <returns>Squared magnitude of this Vector.</returns>
		template<typename Out_ = preferred_floating_point>
		[[nodiscard]] constexpr inline Out_ SquareMagnitude() const
		{
			return EmuMath::Helpers::vector_square_magnitude<Out_>(*this);
		}
		/// <summary>
		/// <para>
		///		Calculates the squared magnitude of this Vector, using only indices in the provided range,
		///		and outputted as the provided Out_ type (defaults to this Vector's preferred_floating_point).
		/// </para>
		/// <para> This is equivalent to forming the dot product of this Vector with itself within the specified range. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output the calculated square magnitude as. Defaults to preferred_floating_point.</typeparam>
		/// <returns>Squared magnitude of this Vector, using the provided index range.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Out_ = preferred_floating_point>
		[[nodiscard]] constexpr inline Out_ SquareMagnitude() const
		{
			return EmuMath::Helpers::vector_square_magnitude<BeginIndex_, EndIndex_, Out_>(*this);
		}

		/// <summary>
		/// <para> Calculates the magnitude of this Vector, output as the provided Out_ type (defaults to this Vector's preferred_floating_point). </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output the calculated magnitude as. Defaults to preferred_floating_point.</typeparam>
		/// <returns>Magnitude of this Vector.</returns>
		template<typename Out_ = preferred_floating_point>
		[[nodiscard]] constexpr inline Out_ MagnitudeConstexpr() const
		{
			return EmuMath::Helpers::vector_magnitude_constexpr<Out_>(*this);
		}
		/// <summary>
		/// <para>
		///		Calculates the magnitude of this Vector, using only indices in the provided range,
		///		and outputted as the provided Out_ type (defaults to this Vector's preferred_floating_point).
		/// </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output the calculated magnitude as. Defaults to preferred_floating_point.</typeparam>
		/// <returns>Magnitude of this Vector, using the provided index range.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Out_ = preferred_floating_point>
		[[nodiscard]] constexpr inline Out_ MagnitudeConstexpr() const
		{
			return EmuMath::Helpers::vector_magnitude_constexpr<BeginIndex_, EndIndex_, Out_>(*this);
		}

		/// <summary>
		/// <para> Calculates the magnitude of this Vector, output as the provided Out_ type (defaults to this Vector's preferred_floating_point). </para>
		/// <para> For a guarantee to produce a compile-time result if possible, use `MagnitudeConstexpr` instead. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output the calculated magnitude as. Defaults to preferred_floating_point.</typeparam>
		/// <returns>Magnitude of this Vector.</returns>
		template<typename Out_ = preferred_floating_point>
		[[nodiscard]] constexpr inline Out_ Magnitude() const
		{
			return EmuMath::Helpers::vector_magnitude<Out_>(*this);
		}
		/// <summary>
		/// <para>
		///		Calculates the magnitude of this Vector, using only indices in the provided range,
		///		and outputted as the provided Out_ type (defaults to this Vector's preferred_floating_point).
		/// </para>
		/// <para> For a guarantee to produce a compile-time result if possible, use `MagnitudeConstexpr` instead. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output the calculated magnitude as. Defaults to preferred_floating_point.</typeparam>
		/// <returns>Magnitude of this Vector, using the provided index range.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Out_ = preferred_floating_point>
		[[nodiscard]] constexpr inline Out_ Magnitude() const
		{
			return EmuMath::Helpers::vector_magnitude<BeginIndex_, EndIndex_, Out_>(*this);
		}

		/// <summary>
		/// <para> Calculates and outputs a copy of this Vector with normalised elements. </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <returns>EmuMath Vector copy of this Vector normalised.</returns>
		template<std::size_t OutSize_, typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> NormaliseConstexpr() const
		{
			return EmuMath::Helpers::vector_normalise_constexpr<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> NormaliseConstexpr() const
		{
			return EmuMath::Helpers::vector_normalise_constexpr<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Calculates and outputs a copy of this Vector with normalised elements, via the provided out_vector_. </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void NormaliseConstexpr(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::vector_normalise_constexpr(out_vector_, *this);
		}

		/// <summary>
		/// <para> Calculates and outputs a copy of this Vector with normalised elements. </para>
		/// <para> Only indices in the provided range will be normalised; indices outside of said range will be copied without modification. </para>
		/// <para> BeginIndex_: Inclusive index at which to start normalising elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop normalising elements. </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <returns>EmuMath Vector copy of this Vector normalised.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> NormaliseConstexpr() const
		{
			return EmuMath::Helpers::vector_normalise_range_constexpr<BeginIndex_, EndIndex_, OutSize_, OutT_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> NormaliseConstexpr() const
		{
			return EmuMath::Helpers::vector_normalise_range_constexpr<BeginIndex_, EndIndex_, size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Calculates and outputs a copy of this Vector with normalised elements. </para>
		/// <para> Only indices in the provided range will be normalised; indices outside of said range will be copied without modification. </para>
		/// <para> BeginIndex_: Inclusive index at which to start normalising elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop normalising elements. </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_>
		constexpr inline void NormaliseConstexpr(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::vector_normalise_range_constexpr<BeginIndex_, EndIndex_>(out_vector_, *this);
		}

		/// <summary>
		/// <para> Calculates and outputs a copy of this Vector with normalised elements. </para>
		/// <para> For a guarantee to produce a compile-time result if possible, use `NormaliseConstexpr` instead. </para>
		/// </summary>
		/// <returns>EmuMath Vector copy of this Vector normalised.</returns>
		template<std::size_t OutSize_, typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Normalise() const
		{
			return EmuMath::Helpers::vector_normalise<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Normalise() const
		{
			return EmuMath::Helpers::vector_normalise<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Calculates and outputs a copy of this Vector with normalised elements, via the provided out_vector_. </para>
		/// <para> For a guarantee to produce a compile-time result if possible, use `NormaliseConstexpr` instead. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void Normalise(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::vector_normalise(out_vector_, *this);
		}

		/// <summary>
		/// <para> Calculates and outputs a copy of this Vector with normalised elements. </para>
		/// <para> Only indices in the provided range will be normalised; indices outside of said range will be copied without modification. </para>
		/// <para> BeginIndex_: Inclusive index at which to start normalising elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop normalising elements. </para>
		/// <para> For a guarantee to produce a compile-time result if possible, use `NormaliseConstexpr` instead. </para>
		/// </summary>
		/// <returns>EmuMath Vector copy of this Vector normalised.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Normalise() const
		{
			return EmuMath::Helpers::vector_normalise_range<BeginIndex_, EndIndex_, OutSize_, OutT_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Normalise() const
		{
			return EmuMath::Helpers::vector_normalise_range<BeginIndex_, EndIndex_, size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Calculates and outputs a copy of this Vector with normalised elements. </para>
		/// <para> Only indices in the provided range will be normalised; indices outside of said range will be copied without modification. </para>
		/// <para> BeginIndex_: Inclusive index at which to start normalising elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop normalising elements. </para>
		/// <para> For a guarantee to produce a compile-time result if possible, use `NormaliseConstexpr` instead. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_>
		constexpr inline void Normalise(EmuMath::NewVector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::vector_normalise_range<BeginIndex_, EndIndex_>(out_vector_, *this);
		}

		/// <summary>
		/// <para> Calculates the cosine of the angle between this Vector and the passed vector_b_. </para>
		/// <para> Radians_: If true, output will be in radians; otherwise, it will be in degrees. Defaults to true. </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <param name="vector_b_">EmuMath Vector to find the cosine of the angle between itself and this Vector.</param>
		/// <returns>Cosine of the angle between this Vector and vector_b_, in radians or degrees depending on the Radians_ arg.</returns>
		template<typename Out_, bool Radians_ = true, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline Out_ AngleCosConstexpr(const EmuMath::NewVector<SizeB_, TB_>& vector_b_) const
		{
			return EmuMath::Helpers::vector_angle_cos_constexpr<Out_, Radians_>(*this, vector_b_);
		}
		template<bool Radians_ = true, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline preferred_floating_point AngleCosConstexpr(const EmuMath::NewVector<SizeB_, TB_>& vector_b_) const
		{
			return EmuMath::Helpers::vector_angle_cos_constexpr<preferred_floating_point, Radians_>(*this, vector_b_);
		}

		/// <summary>
		/// <para> Calculates the cosine of the angle between this Vector and the passed vector_b_. </para>
		/// <para> Radians_: If true, output will be in radians; otherwise, it will be in degrees. Defaults to true. </para>
		/// <para> For a guarantee to produce a compile-time result if possible, use `AngleCosConstexpr` instead. </para>
		/// </summary>
		/// <param name="vector_b_">EmuMath Vector to find the cosine of the angle between itself and this Vector.</param>
		/// <returns>Cosine of the angle between this Vector and vector_b_, in radians or degrees depending on the Radians_ arg.</returns>
		template<typename Out_, bool Radians_ = true, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline Out_ AngleCos(const EmuMath::NewVector<SizeB_, TB_>& vector_b_) const
		{
			return EmuMath::Helpers::vector_angle_cos<Out_, Radians_>(*this, vector_b_);
		}
		template<bool Radians_ = true, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline preferred_floating_point AngleCos(const EmuMath::NewVector<SizeB_, TB_>& vector_b_) const
		{
			return EmuMath::Helpers::vector_angle_cos<preferred_floating_point, Radians_>(*this, vector_b_);
		}

		/// <summary>
		/// <para> Calculates the angle between this Vector and the passed vector_b_. </para>
		/// <para> Radians_: If true, output will be in radians; otherwise, it will be in degrees. Defaults to true. </para>
		/// </summary>
		/// <param name="vector_b_">EmuMath Vector to find the angle between itself and this Vector.</param>
		/// <returns>Angle between this Vector and vector_b_, in radians or degrees depending on the Radians_ arg.</returns>
		template<typename Out_, bool Radians_ = true, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline Out_ Angle(const EmuMath::NewVector<SizeB_, TB_>& vector_b_) const
		{
			return EmuMath::Helpers::vector_angle<Out_, Radians_>(*this, vector_b_);
		}
		template<bool Radians_ = true, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline preferred_floating_point Angle(const EmuMath::NewVector<SizeB_, TB_>& vector_b_) const
		{
			return EmuMath::Helpers::vector_angle<preferred_floating_point, Radians_>(*this, vector_b_);
		}

		/// <summary>
		/// <para> Outputs the 3D cross product of this Vector and b_, using theoretical indices 0, 1, 2. </para>
		/// <para> Listed output will be provided for output Vectors which contain at least up to that element (note that this Vector is `a_`): </para>
		/// <para> [0] = (a_[1] * b_[2]) - (a_[2] * b_[1]) </para>
		/// <para> [1] = (a_[2] * b_[0]) - (a_[0] * b_[2]) </para>
		/// <para> [2] = (a_[0] * b_[1]) - (a_[1] * b_[0]) </para>
		/// <para> [...] = default, or implied 0 if default construction is not possible. </para>
		/// <para> Unlike most member functions, if no OutSize_ is provided this will always default to 3 instead of this Vector's size, due to the meaning of cross products. </para>
		/// </summary>
		/// <param name="b_">: EmuMath Vector appearing as `b_` in the listed calculations.</param>
		/// <returns>3D cross product of this Vector and b_, using theoretical indices 0, 1, 2.</returns>
		template<std::size_t OutSize_, typename OutT_ = preferred_floating_point, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Cross3(const EmuMath::NewVector<SizeB_, TB_>& b_) const
		{
			return EmuMath::Helpers::vector_cross_3d<OutSize_, OutT_>(*this, b_);
		}
		template<typename OutT_ = preferred_floating_point, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<3, OutT_> Cross3(const EmuMath::NewVector<SizeB_, TB_>& b_) const
		{
			return EmuMath::Helpers::vector_cross_3d<3, OutT_>(*this, b_);
		}

		/// <summary>
		/// <para> Outputs the 3D cross product of this Vector and b_, using theoretical indices I0_, I1_, I2_. </para>
		/// <para> Listed output will be provided for output Vectors which contain at least up to that element (note that this Vector is `a_`): </para>
		/// <para> [0] = (a_[I1_] * b_[I2_]) - (a_[I2_] * b_[I1_]) </para>
		/// <para> [1] = (a_[I2_] * b_[I0_]) - (a_[I0_] * b_[I2_]) </para>
		/// <para> [2] = (a_[I0_] * b_[I1_]) - (a_[I1_] * b_[I0_]) </para>
		/// <para> [...] = default, or implied 0 if default construction is not possible. </para>
		/// <para> Unlike most member functions, if no OutSize_ is provided this will always default to 3 instead of this Vector's size, due to the meaning of cross products. </para>
		/// </summary>
		/// <param name="b_">: EmuMath Vector appearing as `b_` in the listed calculations.</param>
		/// <returns>3D cross product of this Vector and b_, using theoretical indices I0_, I1_, I2_.</returns>
		template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t OutSize_, typename OutT_ = preferred_floating_point, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Cross3(const EmuMath::NewVector<SizeB_, TB_>& b_) const
		{
			return EmuMath::Helpers::vector_cross_3d<OutSize_, OutT_, I0_, I1_, I2_>(*this, b_);
		}
		template<std::size_t I0_, std::size_t I1_, std::size_t I2_, typename OutT_ = preferred_floating_point, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<3, OutT_> Cross3(const EmuMath::NewVector<SizeB_, TB_>& b_) const
		{
			return EmuMath::Helpers::vector_cross_3d<3, OutT_, I0_, I1_, I2_>(*this, b_);
		}

		/// <summary>
		/// <para> Outputs the 3D cross product of this Vector and b_, using theoretical indices A0_, A1_, A2_ from this Vector, and B0_, B1_, B2_ from b_. </para>
		/// <para> Listed output will be provided for output Vectors which contain at least up to that element (note that this Vector is `a_`): </para>
		/// <para> [0] = (a_[A1_] * b_[B2_]) - (a_[A2_] * b_[B1_]) </para>
		/// <para> [1] = (a_[A2_] * b_[B0_]) - (a_[A0_] * b_[B2_]) </para>
		/// <para> [2] = (a_[A0_] * b_[B1_]) - (a_[A1_] * b_[B0_]) </para>
		/// <para> [...] = default, or implied 0 if default construction is not possible. </para>
		/// <para> Unlike most member functions, if no OutSize_ is provided this will always default to 3 instead of this Vector's size, due to the meaning of cross products. </para>
		/// </summary>
		/// <param name="b_">: EmuMath Vector appearing as `b_` in the listed calculations.</param>
		/// <returns>3D cross product of this Vector and b_ using theoretical indices A0_, A1_, A2_ from this Vector, and B0_, B1_, B2_ from b_.</returns>
		template
		<
			std::size_t A0_,
			std::size_t A1_,
			std::size_t A2_,
			std::size_t B0_,
			std::size_t B1_,
			std::size_t B2_,
			std::size_t OutSize_,
			typename OutT_ = preferred_floating_point,
			std::size_t SizeB_,
			typename TB_
		>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Cross3(const EmuMath::NewVector<SizeB_, TB_>& b_) const
		{
			return EmuMath::Helpers::vector_cross_3d<OutSize_, OutT_, A0_, A1_, A2_, B0_, B1_, B2_>(*this, b_);
		}
		template
		<
			std::size_t A0_,
			std::size_t A1_,
			std::size_t A2_,
			std::size_t B0_,
			std::size_t B1_,
			std::size_t B2_,
			typename OutT_ = preferred_floating_point,
			std::size_t SizeB_,
			typename TB_
		>
		[[nodiscard]] constexpr inline EmuMath::NewVector<3, OutT_> Cross3(const EmuMath::NewVector<SizeB_, TB_>& b_) const
		{
			return EmuMath::Helpers::vector_cross_3d<3, OutT_, A0_, A1_, A2_, B0_, B1_, B2_>(*this, b_);
		}

		/// <summary>
		/// <para> Calculates the squared distance between this Vector and to_. Equivalent to the square magnitude of (to_ - this_vector). </para>
		/// <para> IncludeNonContained_: If true, all contained-indices will be used for forming the distance. Otherwise, only the indices of the smallest Vector will be used. </para>
		/// </summary>
		/// <param name="to_">: EmuMath Vector to calculate the distance to.</param>
		/// <returns>Distance between this Vector and to_ before a square root operation is performed.</returns>
		template<typename Out_ = preferred_floating_point, bool IncludeNonContained_ = true, std::size_t ToSize_, typename ToT_>
		[[nodiscard]] constexpr inline Out_ SquareDistance(const EmuMath::NewVector<ToSize_, ToT_>& to_) const
		{
			return EmuMath::Helpers::vector_square_distance<Out_, IncludeNonContained_>(*this, to_);
		}
		template<bool IncludeNonContained_, std::size_t ToSize_, typename ToT_>
		[[nodiscard]] constexpr inline preferred_floating_point SquareDistance(const EmuMath::NewVector<ToSize_, ToT_>& to_) const
		{
			return EmuMath::Helpers::vector_square_distance<preferred_floating_point, IncludeNonContained_>(*this, to_);
		}

		/// <summary>
		/// <para> Calculates the squared distance between this Vector and to_. Equivalent to the square magnitude of (to_ - this_vector). </para>
		/// <para> IncludeNonContained_: If true, all contained-indices will be used for forming the distance. Otherwise, only the indices of the smallest Vector will be used. </para>
		/// </summary>
		/// <param name="to_">: EmuMath Vector to calculate the distance to.</param>
		/// <returns>Distance between this Vector and to_ before a square root operation is performed.</returns>
		template<typename Out_ = preferred_floating_point, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ToSize_, typename ToT_>
		[[nodiscard]] constexpr inline Out_ SquareDistance(const EmuMath::NewVector<ToSize_, ToT_>& to_) const
		{
			return EmuMath::Helpers::vector_square_distance<Out_, BeginIndex_, EndIndex_>(*this, to_);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ToSize_, typename ToT_>
		[[nodiscard]] constexpr inline preferred_floating_point SquareDistance(const EmuMath::NewVector<ToSize_, ToT_>& to_) const
		{
			return EmuMath::Helpers::vector_square_distance<preferred_floating_point, BeginIndex_, EndIndex_>(*this, to_);
		}

		/// <summary>
		/// <para> Calculates the distance between this Vector and to_. Equivalent to the magnitude of (to_ - this_vector). </para>
		/// <para> IncludeNonContained_: If true, all contained-indices will be used for forming the distance. Otherwise, only the indices of the smallest Vector will be used. </para>
		/// <para> For a guarantee to be constexpr-evaluable if possible, use DistanceConstexpr instead. </para>
		/// </summary>
		/// <param name="to_">: EmuMath Vector to calculate the distance to.</param>
		/// <returns>Distance between this Vector and to_ before a square root operation is performed.</returns>
		template<typename Out_ = preferred_floating_point, bool IncludeNonContained_ = true, std::size_t ToSize_, typename ToT_>
		[[nodiscard]] constexpr inline Out_ Distance(const EmuMath::NewVector<ToSize_, ToT_>& to_) const
		{
			return EmuMath::Helpers::vector_distance<Out_, IncludeNonContained_>(*this, to_);
		}
		template<bool IncludeNonContained_, std::size_t ToSize_, typename ToT_>
		[[nodiscard]] constexpr inline preferred_floating_point Distance(const EmuMath::NewVector<ToSize_, ToT_>& to_) const
		{
			return EmuMath::Helpers::vector_distance<preferred_floating_point, IncludeNonContained_>(*this, to_);
		}

		/// <summary>
		/// <para> Calculates the distance between this Vector and to_. Equivalent to the magnitude of (to_ - this_vector). </para>
		/// <para> IncludeNonContained_: If true, all contained-indices will be used for forming the distance. Otherwise, only the indices of the smallest Vector will be used. </para>
		/// <para> For a guarantee to be constexpr-evaluable if possible, use DistanceConstexpr instead. </para>
		/// </summary>
		/// <param name="to_">: EmuMath Vector to calculate the distance to.</param>
		/// <returns>Distance between this Vector and to_.</returns>
		template<typename Out_ = preferred_floating_point, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ToSize_, typename ToT_>
		[[nodiscard]] constexpr inline Out_ Distance(const EmuMath::NewVector<ToSize_, ToT_>& to_) const
		{
			return EmuMath::Helpers::vector_distance<Out_, BeginIndex_, EndIndex_>(*this, to_);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ToSize_, typename ToT_>
		[[nodiscard]] constexpr inline preferred_floating_point Distance(const EmuMath::NewVector<ToSize_, ToT_>& to_) const
		{
			return EmuMath::Helpers::vector_distance<preferred_floating_point, BeginIndex_, EndIndex_>(*this, to_);
		}

		/// <summary>
		/// <para> Calculates the distance between this Vector and to_. Equivalent to the magnitude of (to_ - this_vector). </para>
		/// <para> IncludeNonContained_: If true, all contained-indices will be used for forming the distance. Otherwise, only the indices of the smallest Vector will be used. </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <param name="to_">: EmuMath Vector to calculate the distance to.</param>
		/// <returns>Distance between this Vector and to_ before a square root operation is performed.</returns>
		template<typename Out_ = preferred_floating_point, bool IncludeNonContained_ = true, std::size_t ToSize_, typename ToT_>
		[[nodiscard]] constexpr inline Out_ DistanceConstexpr(const EmuMath::NewVector<ToSize_, ToT_>& to_) const
		{
			return EmuMath::Helpers::vector_distance_constexpr<Out_, IncludeNonContained_>(*this, to_);
		}
		template<bool IncludeNonContained_, std::size_t ToSize_, typename ToT_>
		[[nodiscard]] constexpr inline preferred_floating_point DistanceConstexpr(const EmuMath::NewVector<ToSize_, ToT_>& to_) const
		{
			return EmuMath::Helpers::vector_distance_constexpr<preferred_floating_point, IncludeNonContained_>(*this, to_);
		}

		/// <summary>
		/// <para> Calculates the distance between this Vector and to_. Equivalent to the magnitude of (to_ - this_vector). </para>
		/// <para> IncludeNonContained_: If true, all contained-indices will be used for forming the distance. Otherwise, only the indices of the smallest Vector will be used. </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <param name="to_">: EmuMath Vector to calculate the distance to.</param>
		/// <returns>Distance between this Vector and to_.</returns>
		template<typename Out_ = preferred_floating_point, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ToSize_, typename ToT_>
		[[nodiscard]] constexpr inline Out_ DistanceConstexpr(const EmuMath::NewVector<ToSize_, ToT_>& to_) const
		{
			return EmuMath::Helpers::vector_distance_constexpr<Out_, BeginIndex_, EndIndex_>(*this, to_);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ToSize_, typename ToT_>
		[[nodiscard]] constexpr inline preferred_floating_point DistanceConstexpr(const EmuMath::NewVector<ToSize_, ToT_>& to_) const
		{
			return EmuMath::Helpers::vector_distance_constexpr<preferred_floating_point, BeginIndex_, EndIndex_>(*this, to_);
		}

		/// <summary>
		/// <para> Calculates a reflection of this Vector using the provided surface_normal_ Vector. </para>
		/// </summary>
		/// <param name="surface_normal_">: Normal describing a reflection surface. This is expected to be normalised, and treated as such.</param>
		/// <returns>EmuMath Vector representing the reflection of this Vector on the provided surface_normal_.</returns>
		template<std::size_t OutSize_, typename OutT_ = preferred_floating_point, std::size_t NormalSize_, typename NormalT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Reflect(const EmuMath::NewVector<NormalSize_, NormalT_>& surface_normal_) const
		{
			return EmuMath::Helpers::vector_reflect_normal<OutSize_, OutT_>(*this, surface_normal_);
		}
		template<typename OutT_ = preferred_floating_point, std::size_t NormalSize_, typename NormalT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Reflect(const EmuMath::NewVector<NormalSize_, NormalT_>& surface_normal_) const
		{
			return EmuMath::Helpers::vector_reflect_normal<size, OutT_>(*this, surface_normal_);
		}

		/// <summary>
		/// <para> Calculates a reflection of this Vector using the provided surface_normal_ Vector, using indices within the provided range. </para>
		/// <para>
		///		Calculations will be performed as though the indices within the provided range form a Vector of that size. 
		///		For example, if using 3 indices within a Vector of 8 indices, the reflection will be performed as though on a 3-element Vector.
		/// </para>
		/// <para> BeginIndex_: Inclusive index at which to start performing reflection calculations. </para>
		/// <para> EndIndex_: Exclusive index at which to stop performing reflection calculations. </para>
		/// </summary>
		/// <param name="surface_normal_">: Normal describing a reflection surface. This is expected to be normalised, and treated as such.</param>
		/// <returns>EmuMath Vector representing the reflection of this Vector on the provided surface_normal_, using indices within the provided range.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = preferred_floating_point, std::size_t NormalSize_, typename NormalT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Reflect(const EmuMath::NewVector<NormalSize_, NormalT_>& surface_normal_) const
		{
			return EmuMath::Helpers::vector_reflect_normal<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, surface_normal_);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = preferred_floating_point, std::size_t NormalSize_, typename NormalT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Reflect(const EmuMath::NewVector<NormalSize_, NormalT_>& surface_normal_) const
		{
			return EmuMath::Helpers::vector_reflect_normal<size, OutT_, BeginIndex_, EndIndex_>(*this, surface_normal_);
		}

		/// <summary>
		/// <para> Calculates the Vector normal to a plane defined by this Vector and 2 other points in 3D space, before normalisation. </para>
		/// <para> The result may be summarised as Cross(point_b_ - point_a_, point_c_ - point_a_), where this Vector is `point_a_`. </para>
		/// <para> ReadOffset_: Optional inclusive index offset at which to start reading Vectors. Defaults to 0. </para>
		/// <para> Unlike most member functions, if no OutSize_ is provided this will always default to 3 instead of this Vector's size, due to its 3D focus. </para>
		/// </summary>
		/// <param name="point_b_">EmuMath Vector to interpret as a 3D cartesian coordinate, appearing as `point_b_` in described calculations.</param>
		/// <param name="point_c_">EmuMath Vector to interpret as a 3D cartesian coordinate, appearing as `point_c_` in described calculations.</param>
		/// <returns>EmuMath Vector normal to the plane defined by this Vector and the passed 2 other coordinates, before normalisation.</returns>
		template<std::size_t OutSize_, typename OutT_ = preferred_floating_point, std::size_t ReadOffset_ = 0, std::size_t SizeB_, typename TB_, std::size_t SizeC_, typename TC_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> NormalToPlane3NoNorm
		(
			const EmuMath::NewVector<SizeB_, TB_>& point_b_,
			const EmuMath::NewVector<SizeC_, TC_>& point_c_
		) const
		{
			return EmuMath::Helpers::vector_normal_to_plane_3d_no_norm<OutSize_, OutT_, ReadOffset_>(*this, point_b_, point_c_);
		}
		template<typename OutT_ = preferred_floating_point, std::size_t ReadOffset_ = 0, std::size_t SizeB_, typename TB_, std::size_t SizeC_, typename TC_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<3, OutT_> NormalToPlane3NoNorm
		(
			const EmuMath::NewVector<SizeB_, TB_>& point_b_,
			const EmuMath::NewVector<SizeC_, TC_>& point_c_
		) const
		{
			return EmuMath::Helpers::vector_normal_to_plane_3d_no_norm<3, OutT_, ReadOffset_>(*this, point_b_, point_c_);
		}

		/// <summary>
		/// <para> Calculates the Vector normal to a plane defined by this Vector and 2 other points in 3D space. </para>
		/// <para> The result may be summarised as Normalise(Cross(point_b_ - point_a_, point_c_ - point_a_)), where this Vector is `point_a_`. </para>
		/// <para> ReadOffset_: Optional inclusive index offset at which to start reading Vectors. Defaults to 0. </para>
		/// <para> Unlike most member functions, if no OutSize_ is provided this will always default to 3 instead of this Vector's size, due to its 3D focus. </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <param name="point_b_">EmuMath Vector to interpret as a 3D cartesian coordinate, appearing as `point_b_` in described calculations.</param>
		/// <param name="point_c_">EmuMath Vector to interpret as a 3D cartesian coordinate, appearing as `point_c_` in described calculations.</param>
		/// <returns>EmuMath Vector normal to the plane defined by this Vector and the passed 2 other coordinates.</returns>
		template<std::size_t OutSize_, typename OutT_ = preferred_floating_point, std::size_t ReadOffset_ = 0, std::size_t SizeB_, typename TB_, std::size_t SizeC_, typename TC_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> NormalToPlane3Constexpr
		(
			const EmuMath::NewVector<SizeB_, TB_>& point_b_,
			const EmuMath::NewVector<SizeC_, TC_>& point_c_
		) const
		{
			return EmuMath::Helpers::vector_normal_to_plane_3d_constexpr<OutSize_, OutT_, ReadOffset_>(*this, point_b_, point_c_);
		}
		template<typename OutT_ = preferred_floating_point, std::size_t ReadOffset_ = 0, std::size_t SizeB_, typename TB_, std::size_t SizeC_, typename TC_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<3, OutT_> NormalToPlane3Constexpr
		(
			const EmuMath::NewVector<SizeB_, TB_>& point_b_,
			const EmuMath::NewVector<SizeC_, TC_>& point_c_
		) const
		{
			return EmuMath::Helpers::vector_normal_to_plane_3d_constexpr<3, OutT_, ReadOffset_>(*this, point_b_, point_c_);
		}



		/// <summary>
		/// <para> Calculates the Vector normal to a plane defined by this Vector and 2 other points in 3D space. </para>
		/// <para> The result may be summarised as Normalise(Cross(point_b_ - point_a_, point_c_ - point_a_)), where this Vector is `point_a_`. </para>
		/// <para> ReadOffset_: Optional inclusive index offset at which to start reading Vectors. Defaults to 0. </para>
		/// <para> Unlike most member functions, if no OutSize_ is provided this will always default to 3 instead of this Vector's size, due to its 3D focus. </para>
		/// <para> For a guarantee to be constexpr-evaluable if possible, use NormalToPlane3Constexpr instead. </para>
		/// </summary>
		/// <param name="point_b_">EmuMath Vector to interpret as a 3D cartesian coordinate, appearing as `point_b_` in described calculations.</param>
		/// <param name="point_c_">EmuMath Vector to interpret as a 3D cartesian coordinate, appearing as `point_c_` in described calculations.</param>
		/// <returns>EmuMath Vector normal to the plane defined by this Vector and the passed 2 other coordinates.</returns>
		template<std::size_t OutSize_, typename OutT_ = preferred_floating_point, std::size_t ReadOffset_ = 0, std::size_t SizeB_, typename TB_, std::size_t SizeC_, typename TC_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> NormalToPlane3
		(
			const EmuMath::NewVector<SizeB_, TB_>& point_b_,
			const EmuMath::NewVector<SizeC_, TC_>& point_c_
		) const
		{
			return EmuMath::Helpers::vector_normal_to_plane_3d<OutSize_, OutT_, ReadOffset_>(*this, point_b_, point_c_);
		}
		template<typename OutT_ = preferred_floating_point, std::size_t ReadOffset_ = 0, std::size_t SizeB_, typename TB_, std::size_t SizeC_, typename TC_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<3, OutT_> NormalToPlane3
		(
			const EmuMath::NewVector<SizeB_, TB_>& point_b_,
			const EmuMath::NewVector<SizeC_, TC_>& point_c_
		) const
		{
			return EmuMath::Helpers::vector_normal_to_plane_3d<3, OutT_, ReadOffset_>(*this, point_b_, point_c_);
		}

		/// <summary>
		/// <para> Calculates the Vector resulting from projecting this Vector onto the Vector onto_. </para>
		/// </summary>
		/// <param name="onto_">: EmuMath Vector to project this Vector onto.</param>
		/// <returns>EmuMath Vector resulting from a projection of this Vector onto the Vector onto_.</returns>
		template<std::size_t OutSize_, typename OutT_ = preferred_floating_point, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Project(const EmuMath::NewVector<SizeB_, TB_>& onto_) const
		{
			return EmuMath::Helpers::vector_project<OutSize_, OutT_>(*this, onto_);
		}
		template<typename OutT_ = preferred_floating_point, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Project(const EmuMath::NewVector<SizeB_, TB_>& onto_) const
		{
			return EmuMath::Helpers::vector_project<size, OutT_>(*this, onto_);
		}

		/// <summary>
		/// <para> Calculates the Vector resulting from projecting this Vector onto the Vector onto_, using indices within the specified range. </para>
		/// </summary>
		/// <param name="onto_">: EmuMath Vector to project this Vector onto.</param>
		/// <returns>EmuMath Vector resulting from a projection of this Vector onto the Vector onto_, using indices within the specified range.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = preferred_floating_point, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Project(const EmuMath::NewVector<SizeB_, TB_>& onto_) const
		{
			return EmuMath::Helpers::vector_project<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, onto_);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = preferred_floating_point, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Project(const EmuMath::NewVector<SizeB_, TB_>& onto_) const
		{
			return EmuMath::Helpers::vector_project<size, OutT_, BeginIndex_, EndIndex_>(*this, onto_);
		}

		/// <summary>
		/// <para> Calculates the projection of this Vector onto the plane defined by the passed plane_normal_. </para>
		/// </summary>
		/// <param name="plane_normal_">: EmuMath Vector describing the plane to reflect onto. This is expected to be normalised, and treated as such.</param>
		/// <returns>EmuMath Vector resulting from projecting this Vector onto the plane defined by the provided plane_normal_.</returns>
		template<std::size_t OutSize_, typename OutT_ = preferred_floating_point, std::size_t NormSize_, typename NormT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> ProjectPlane(const EmuMath::NewVector<NormSize_, NormT_>& plane_normal_) const
		{
			return EmuMath::Helpers::vector_project_plane<OutSize_, OutT_>(*this, plane_normal_);
		}
		template<typename OutT_ = preferred_floating_point, std::size_t NormSize_, typename NormT_>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> ProjectPlane(const EmuMath::NewVector<NormSize_, NormT_>& plane_normal_) const
		{
			return EmuMath::Helpers::vector_project_plane<size, OutT_>(*this, plane_normal_);
		}

		/// <summary>
		/// <para> Calculates the resulting Vector from a projection of this Vector onto the 3D plane defined by the passed 3 points </para>
		/// <para>
		///		PlaneReadOffset_: Inclusive index at which to start reading the plane points. Defaults to 0.  
		///		This offset does not apply to reads from this Vector, which will always read from 0.
		/// </para>
		/// <para> If a normal for the defined plane is already available, it is recommended to use vector_project_plane with that normal to minimise normalisation costs. </para>
		/// <para> Unlike most member functions, if no OutSize_ is provided this will always default to 3 instead of this Vector's size, due to its 3D focus. </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <param name="plane_point_a_">
		///		: Cartesian point a defining the plane to project onto. For more information on how this is used, see NormalToPlane3 
		///		(Note that `plane_point_a_` is this Vector when calling NormalToPlane3).
		/// </param>
		/// <param name="plane_point_b_">: Cartesian point b defining the plane to project onto. For more information on how this is used, see NormalToPlane3.</param>
		/// <param name="plane_point_c_">: Cartesian point c defining the plane to project onto. For more information on how this is used, see NormalToPlane3.</param>
		/// <returns>EmuMath Vector resulting from the projection of this Vector onto the 3D plane defined by the passed 3 points.</returns>
		template
		<
			std::size_t OutSize_,
			typename OutT_ = preferred_floating_point,
			std::size_t PlaneReadOffset_ = 0,
			std::size_t SizeA_,
			typename TA_,
			std::size_t SizeB_,
			typename TB_,
			std::size_t SizeC_,
			typename TC_
		>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> ProjectPlane3Constexpr
		(
			const EmuMath::NewVector<SizeA_, TA_>& plane_point_a_,
			const EmuMath::NewVector<SizeB_, TB_>& plane_point_b_,
			const EmuMath::NewVector<SizeC_, TC_>& plane_point_c_
		) const
		{
			return EmuMath::Helpers::vector_project_plane_3d_constexpr<OutSize_, OutT_, PlaneReadOffset_>(*this, plane_point_a_, plane_point_b_, plane_point_c_);
		}
		template
		<
			typename OutT_ = preferred_floating_point,
			std::size_t PlaneReadOffset_ = 0,
			std::size_t SizeA_,
			typename TA_,
			std::size_t SizeB_,
			typename TB_,
			std::size_t SizeC_,
			typename TC_
		>
		[[nodiscard]] constexpr inline EmuMath::NewVector<3, OutT_> ProjectPlane3Constexpr
		(
			const EmuMath::NewVector<SizeA_, TA_>& plane_point_a_,
			const EmuMath::NewVector<SizeB_, TB_>& plane_point_b_,
			const EmuMath::NewVector<SizeC_, TC_>& plane_point_c_
		) const
		{
			return EmuMath::Helpers::vector_project_plane_3d_constexpr<3, OutT_, PlaneReadOffset_>(*this, plane_point_a_, plane_point_b_, plane_point_c_);
		}

		/// <summary>
		/// <para> Calculates the resulting Vector from a projection of this Vector onto the 3D plane defined by the passed 3 points </para>
		/// <para>
		///		PlaneReadOffset_: Inclusive index at which to start reading the plane points. Defaults to 0.  
		///		This offset does not apply to reads from this Vector, which will always read from 0.
		/// </para>
		/// <para> If a normal for the defined plane is already available, it is recommended to use vector_project_plane with that normal to minimise normalisation costs. </para>
		/// <para> Unlike most member functions, if no OutSize_ is provided this will always default to 3 instead of this Vector's size, due to its 3D focus. </para>
		/// <para> For a guarantee to be constexpr-evaluable if possible, use ProjectPlane3Constexpr instead. </para>
		/// </summary>
		/// <param name="plane_point_a_">
		///		: Cartesian point a defining the plane to project onto. For more information on how this is used, see NormalToPlane3 
		///		(Note that `plane_point_a_` is this Vector when calling NormalToPlane3).
		/// </param>
		/// <param name="plane_point_b_">: Cartesian point b defining the plane to project onto. For more information on how this is used, see NormalToPlane3.</param>
		/// <param name="plane_point_c_">: Cartesian point c defining the plane to project onto. For more information on how this is used, see NormalToPlane3.</param>
		/// <returns>EmuMath Vector resulting from the projection of this Vector onto the 3D plane defined by the passed 3 points.</returns>
		template
		<
			std::size_t OutSize_,
			typename OutT_ = preferred_floating_point,
			std::size_t PlaneReadOffset_ = 0,
			std::size_t SizeA_,
			typename TA_,
			std::size_t SizeB_,
			typename TB_,
			std::size_t SizeC_,
			typename TC_
		>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> ProjectPlane3
		(
			const EmuMath::NewVector<SizeA_, TA_>& plane_point_a_,
			const EmuMath::NewVector<SizeB_, TB_>& plane_point_b_,
			const EmuMath::NewVector<SizeC_, TC_>& plane_point_c_
		) const
		{
			return EmuMath::Helpers::vector_project_plane_3d<OutSize_, OutT_, PlaneReadOffset_>(*this, plane_point_a_, plane_point_b_, plane_point_c_);
		}
		template
		<
			typename OutT_ = preferred_floating_point,
			std::size_t PlaneReadOffset_ = 0,
			std::size_t SizeA_,
			typename TA_,
			std::size_t SizeB_,
			typename TB_,
			std::size_t SizeC_,
			typename TC_
		>
		[[nodiscard]] constexpr inline EmuMath::NewVector<3, OutT_> ProjectPlane3
		(
			const EmuMath::NewVector<SizeA_, TA_>& plane_point_a_,
			const EmuMath::NewVector<SizeB_, TB_>& plane_point_b_,
			const EmuMath::NewVector<SizeC_, TC_>& plane_point_c_
		) const
		{
			return EmuMath::Helpers::vector_project_plane_3d<3, OutT_, PlaneReadOffset_>(*this, plane_point_a_, plane_point_b_, plane_point_c_);
		}
#pragma endregion

#pragma region GENERIC_CMP_FUNCS
	public:
		/// <summary>
		/// <para> Returns the boolean result of a comparison of this Vector and rhs_, using the provided Cmp_ function. </para>
		/// <para> Returns true only if all comparisons are true. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para>
		///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
		///		If false, comparisons will only be performed until the end of the smallest Vector. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <param name="cmp_">
		///		: Invocable item to perform comparisons. Must return a type that may be interpreted as a bool when invoked with this Vector and rhs_ as described.
		/// </param>
		/// <returns>True if all comparisons with the provided Cmp_ are true, otherwise false.</returns>
		template<bool IncludeNonContained_ = true, class Cmp_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAll(Rhs_&& rhs_, Cmp_ cmp_) const
		{
			return EmuMath::Helpers::vector_cmp_all<IncludeNonContained_, std::add_lvalue_reference_t<Cmp_>>(*this, std::forward<Rhs_>(rhs_), cmp_);
		}

		template<class Cmp_, bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAll(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_all<Cmp_, IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the boolean result of a comparison between this Vector and rhs_, using an automatically selected instantiation of the provided CmpTemplate_. </para>
		/// <para> CmpTemplate_ must be possible to instantiate with two type arguments. The provided type arguments will be based on this Vector and Rhs_. </para>
		/// <para> Returns true only if all comparisons are true. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para>
		///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
		///		If false, comparisons will only be performed until the end of the smallest Vector. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if all comparisons using the provided CmpTemplate_ are true, otherwise false.</returns>
		template<template<class...> class CmpTemplate_, bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAll(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_all<CmpTemplate_, IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the boolean result of a comparison between this Vector and rhs_, using the provided Cmp_ function. </para>
		/// <para> Returns true only if all comparisons in the provided index range are true. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading values from Vectors for comparison. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading values from Vectors for comparison. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <param name="cmp_">
		///		: Invocable item to perform comparisons. Must return a type that may be interpreted as a bool when invoked with this Vector and rhs_ as described.
		/// </param>
		/// <returns>True if all comparisons with the provided Cmp_ within the provided index range are true, otherwise false.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Cmp_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAll(Rhs_&& rhs_, Cmp_ cmp_) const
		{
			return EmuMath::Helpers::vector_cmp_all<BeginIndex_, EndIndex_, std::add_lvalue_reference_t<Cmp_>>(*this, std::forward<Rhs_>(rhs_), cmp_);
		}

		template<class Cmp_, std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAll(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_all<Cmp_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the boolean result of a comparison between this Vector and rhs_, using an automatically selected instantiation of the provided CmpTemplate_. </para>
		/// <para> CmpTemplate_ must be possible to instantiate with two type arguments. The provided type arguments will be based on this Vector and Rhs_. </para>
		/// <para> Returns true only if all comparisons in the provided index range are true. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading values from Vectors for comparison. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading values from Vectors for comparison. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if all comparisons using the provided CmpTemplate_ within the provided index range are true, otherwise false.</returns>
		template<template<class...> class CmpTemplate_, std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAll(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_all<CmpTemplate_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the boolean result of a comparison of this Vector and rhs_, using the provided Cmp_ function. </para>
		/// <para> Returns true if at least 1 comparison is true. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para>
		///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
		///		If false, comparisons will only be performed until the end of the smallest Vector. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <param name="cmp_">
		///		: Invocable item to perform comparisons. Must return a type that may be interpreted as a bool when invoked with this Vector and rhs_ as described.
		/// </param>
		/// <returns>True if at least 1 comparison with the provided Cmp_ is true, otherwise false.</returns>
		template<bool IncludeNonContained_ = true, class Cmp_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAny(Rhs_&& rhs_, Cmp_ cmp_) const
		{
			return EmuMath::Helpers::vector_cmp_any<IncludeNonContained_, std::add_lvalue_reference_t<Cmp_>>(*this, std::forward<Rhs_>(rhs_), cmp_);
		}

		template<class Cmp_, bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAny(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_any<Cmp_, IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the boolean result of a comparison between this Vector and rhs_, using an automatically selected instantiation of the provided CmpTemplate_. </para>
		/// <para> CmpTemplate_ must be possible to instantiate with two type arguments. The provided type arguments will be based on this Vector and Rhs_. </para>
		/// <para> Returns true if at least 1 comparison is true. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para>
		///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
		///		If false, comparisons will only be performed until the end of the smallest Vector. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if at least 1 comparison using the provided CmpTemplate_ is true, otherwise false.</returns>
		template<template<class...> class CmpTemplate_, bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAny(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_any<CmpTemplate_, IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the boolean result of a comparison between this Vector and rhs_, using the provided Cmp_ function. </para>
		/// <para> Returns true if at least 1 comparison is true. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading values from Vectors for comparison. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading values from Vectors for comparison. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <param name="cmp_">
		///		: Invocable item to perform comparisons. Must return a type that may be interpreted as a bool when invoked with this Vector and rhs_ as described.
		/// </param>
		/// <returns>True if at least 1 comparison with the provided Cmp_ within the provided index range is true, otherwise false.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Cmp_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAny(Rhs_&& rhs_, Cmp_ cmp_) const
		{
			return EmuMath::Helpers::vector_cmp_any<BeginIndex_, EndIndex_, std::add_lvalue_reference_t<Cmp_>>(*this, std::forward<Rhs_>(rhs_), cmp_);
		}

		template<class Cmp_, std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAny(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_any<Cmp_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns the boolean result of a comparison between this Vector and rhs_, using an automatically selected instantiation of the provided CmpTemplate_. </para>
		/// <para> CmpTemplate_ must be possible to instantiate with two type arguments. The provided type arguments will be based on this Vector and Rhs_. </para>
		/// <para> Returns true if at least 1 comparison is true. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading values from Vectors for comparison. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading values from Vectors for comparison. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if at least 1 comparison using the provided CmpTemplate_ within the provided index range is true, otherwise false.</returns>
		template<template<class...> class CmpTemplate_, std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAny(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_any<CmpTemplate_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region CMP_NEAR_FUNCS
		/// <summary>
		/// <para> Adaptive near-equality comparison which changes behaviour based on the provided Rhs_ type, intended for safer floating-point equality checks. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Equivalent to CmpAllNear. </para>
		/// <para> If Rhs_ is none of the above: Compares the magnitude of this Vector to rhs_, or the square magnitude in allowing situations (where rhs_ may be squared). </para>
		/// <para> IncludeNonContained_: Unused if Rhs_ is not an EmuMath Vector, otherwise used as in CmpAllNear. </para>
		/// </summary>
		/// <param name="rhs_">EmuMath Vector appearing on the right of per-element comparison, or scalar appearing on the right of magnitude comparison.</param>
		/// <returns>If Rhs_: is an EmuMath Vector: true if all comparisons are true, otherwise false. Otherwise, true if rhs_ is near-equal to this Vector's magnitude.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpNear(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_near<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Adaptive near-equality comparison which changes behaviour based on the provided Rhs_ type, intended for safer floating-point equality checks. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Equivalent to CmpAllNear. </para>
		/// <para> If Rhs_ is none of the above: Compares the magnitude of this Vector to rhs_, or the square magnitude in allowing situations (where rhs_ may be squared). </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for either performing comparisons or calculating magnitude. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for either performing comparisons or calculating magnitude. </para>
		/// </summary>
		/// <param name="rhs_">EmuMath Vector appearing on the right of per-element comparison, or scalar appearing on the right of magnitude comparison.</param>
		/// <returns>
		///		If Rhs_: is an EmuMath Vector: true if all comparisons in the provided range are true, otherwise false. 
		///		Otherwise, true if rhs_ is near-equal to this Vector's magnitude when calculated using only indices within the provided range.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpNear(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_near<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if all indices within this Vector are near-equal to rhs_, intended for safer floating-point equality checks. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para>
		///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
		///		If false, comparisons will only be performed until the end of the smallest Vector. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if all comparisons are true, otherwise false.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllNear(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_all_near<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if all indices in the provided range within this Vector are near-equal to rhs_, intended for safer floating-point equality checks. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if all comparisons within the provided range are true, otherwise false.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllNear(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_all_near<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if any indices within this Vector are near-equal to rhs_, intended for safer floating-point equality checks. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para>
		///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
		///		If false, comparisons will only be performed until the end of the smallest Vector. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if at least 1 comparison is true, otherwise false.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyNear(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_any_near<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if any indices in the provided range within this Vector are near-equal to rhs_, intended for safer floating-point equality checks. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if at least 1 comparison within the provided range is true, otherwise false.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyNear(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_any_near<BeginIndex_, EndIndex_>(std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region CMP_NOT_NEAR_FUNCS
		/// <summary>
		/// <para> Adaptive not near-equality comparison which changes behaviour based on the provided Rhs_ type, intended for safer floating-point inequality checks. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Equivalent to CmpAllNear. </para>
		/// <para> If Rhs_ is none of the above: Compares the magnitude of this Vector to rhs_, or the square magnitude in allowing situations (where rhs_ may be squared). </para>
		/// <para> IncludeNonContained_: Unused if Rhs_ is not an EmuMath Vector, otherwise used as in CmpAllNear. </para>
		/// </summary>
		/// <param name="rhs_">EmuMath Vector appearing on the right of per-element comparison, or scalar appearing on the right of magnitude comparison.</param>
		/// <returns>If Rhs_: is an EmuMath Vector: true if all comparisons are true, otherwise false. Otherwise, true if rhs_ is not near-equal to this Vector's magnitude.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpNotNear(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_not_near<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Adaptive not near-equality comparison which changes behaviour based on the provided Rhs_ type, intended for safer floating-point inequality checks. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Equivalent to CmpAllNear. </para>
		/// <para> If Rhs_ is none of the above: Compares the magnitude of this Vector to rhs_, or the square magnitude in allowing situations (where rhs_ may be squared). </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for either performing comparisons or calculating magnitude. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for either performing comparisons or calculating magnitude. </para>
		/// </summary>
		/// <param name="rhs_">EmuMath Vector appearing on the right of per-element comparison, or scalar appearing on the right of magnitude comparison.</param>
		/// <returns>
		///		If Rhs_: is an EmuMath Vector: true if all comparisons in the provided range are true, otherwise false. 
		///		Otherwise, true if rhs_ is not near-equal to this Vector's magnitude when calculated using only indices within the provided range.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpNotNear(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_not_near<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if all indices within this Vector are not near-equal to rhs_, intended for safer floating-point equality checks. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para>
		///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
		///		If false, comparisons will only be performed until the end of the smallest Vector. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if all comparisons are true, otherwise false.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllNotNear(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_all_not_near<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if all indices in the provided range within this Vector are not near-equal to rhs_, intended for safer floating-point equality checks. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if all comparisons within the provided range are true, otherwise false.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllNotNear(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_all_not_near<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if any indices within this Vector are not near-equal to rhs_, intended for safer floating-point equality checks. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para>
		///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
		///		If false, comparisons will only be performed until the end of the smallest Vector. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if at least 1 comparison is true, otherwise false.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyNotNear(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_any_not_near<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if any indices in the provided range within this Vector are not near-equal to rhs_, intended for safer floating-point equality checks. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if at least 1 comparison within the provided range is true, otherwise false.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyNotNear(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_any_not_near<BeginIndex_, EndIndex_>(std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region CMP_EQUAL_FUNCS
		/// <summary>
		/// <para> Adaptive equality comparison which changes behaviour based on the provided Rhs_ type. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Equivalent to CmpAllNear. </para>
		/// <para> If Rhs_ is none of the above: Compares the magnitude of this Vector to rhs_, or the square magnitude in allowing situations (where rhs_ may be squared). </para>
		/// <para> IncludeNonContained_: Unused if Rhs_ is not an EmuMath Vector, otherwise used as in CmpAllNear. </para>
		/// </summary>
		/// <param name="rhs_">EmuMath Vector appearing on the right of per-element comparison, or scalar appearing on the right of magnitude comparison.</param>
		/// <returns>If Rhs_: is an EmuMath Vector: true if all comparisons are true, otherwise false. Otherwise, true if rhs_ is equal to this Vector's magnitude.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_equal<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Adaptive equality comparison which changes behaviour based on the provided Rhs_ type. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Equivalent to CmpAllNear. </para>
		/// <para> If Rhs_ is none of the above: Compares the magnitude of this Vector to rhs_, or the square magnitude in allowing situations (where rhs_ may be squared). </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for either performing comparisons or calculating magnitude. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for either performing comparisons or calculating magnitude. </para>
		/// </summary>
		/// <param name="rhs_">EmuMath Vector appearing on the right of per-element comparison, or scalar appearing on the right of magnitude comparison.</param>
		/// <returns>
		///		If Rhs_: is an EmuMath Vector: true if all comparisons in the provided range are true, otherwise false. 
		///		Otherwise, true if rhs_ is equal to this Vector's magnitude when calculated using only indices within the provided range.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_equal<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if all indices within this Vector are equal to rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para>
		///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
		///		If false, comparisons will only be performed until the end of the smallest Vector. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if all comparisons are true, otherwise false.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_all_equal<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if all indices in the provided range within this Vector are equal to rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if all comparisons within the provided range are true, otherwise false.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_all_equal<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if any indices within this Vector are equal to rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para>
		///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
		///		If false, comparisons will only be performed until the end of the smallest Vector. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if at least 1 comparison is true, otherwise false.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_any_equal<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if any indices in the provided range within this Vector are equal to rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if at least 1 comparison within the provided range is true, otherwise false.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_any_equal<BeginIndex_, EndIndex_>(std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region CMP_NOT_EQUAL_FUNCS
	public:
		/// <summary>
		/// <para> Adaptive inequality comparison which changes behaviour based on the provided Rhs_ type. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Equivalent to CmpAllNear. </para>
		/// <para> If Rhs_ is none of the above: Compares the magnitude of this Vector to rhs_, or the square magnitude in allowing situations (where rhs_ may be squared). </para>
		/// <para> IncludeNonContained_: Unused if Rhs_ is not an EmuMath Vector, otherwise used as in CmpAllNear. </para>
		/// </summary>
		/// <param name="rhs_">EmuMath Vector appearing on the right of per-element comparison, or scalar appearing on the right of magnitude comparison.</param>
		/// <returns>If Rhs_: is an EmuMath Vector: true if all comparisons are true, otherwise false. Otherwise, true if rhs_ is not equal to this Vector's magnitude.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpNotEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_not_equal<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Adaptive inequality comparison which changes behaviour based on the provided Rhs_ type. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Equivalent to CmpAllNear. </para>
		/// <para> If Rhs_ is none of the above: Compares the magnitude of this Vector to rhs_, or the square magnitude in allowing situations (where rhs_ may be squared). </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for either performing comparisons or calculating magnitude. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for either performing comparisons or calculating magnitude. </para>
		/// </summary>
		/// <param name="rhs_">EmuMath Vector appearing on the right of per-element comparison, or scalar appearing on the right of magnitude comparison.</param>
		/// <returns>
		///		If Rhs_: is an EmuMath Vector: true if all comparisons in the provided range are true, otherwise false. 
		///		Otherwise, true if rhs_ is not equal to this Vector's magnitude when calculated using only indices within the provided range.
		/// </returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpNotEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_not_equal<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if all indices within this Vector are not equal to rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para>
		///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
		///		If false, comparisons will only be performed until the end of the smallest Vector. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if all comparisons are true, otherwise false.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllNotEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_all_not_equal<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if all indices in the provided range within this Vector are not equal to rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if all comparisons within the provided range are true, otherwise false.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllNotEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_all_not_equal<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if any indices within this Vector are not equal to rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para>
		///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
		///		If false, comparisons will only be performed until the end of the smallest Vector. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if at least 1 comparison is true, otherwise false.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyNotEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_any_not_equal<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if any indices in the provided range within this Vector are not equal to rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if at least 1 comparison within the provided range is true, otherwise false.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyNotEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_any_not_equal<BeginIndex_, EndIndex_>(std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region CMP_GREATER_FUNCS
		/// <summary>
		/// <para> Returns true if the magnitude of this Vector is greater than that of rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Both Vector's magnitudes will be compared. Otherwise, this Vector's magnitude will be compared with rhs_ directly. </para>
		/// <para> 
		///		IncludeNonContained_: If true, all elements of each Vector will be used to determine their magnitude. 
		///		If false, only elements up to the end of the smallest Vector will be used to determine magnitude. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">EmuMath Vector whose magnitude appears on the right of comparison, or scalar appearing on the right of comparison.</param>
		/// <returns>True if this Vector's magnitude is greater than that of rhs_, otherwise false.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpGreater(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_greater<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if the magnitude of this Vector is greater than that of rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Both Vector's magnitudes will be compared. Otherwise, this Vector's magnitude will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors to calculate their magnitude. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors to calculate their magnitude. </para>
		/// </summary>
		/// <param name="rhs_">EmuMath Vector whose magnitude appears on the right of comparison, or scalar appearing on the right of comparison.</param>
		/// <returns>True if this Vector's magnitude is greater than that of rhs_, otherwise false.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpGreater(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_greater<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if all indices within this Vector are greater than rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para>
		///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
		///		If false, comparisons will only be performed until the end of the smallest Vector. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if all comparisons are true, otherwise false.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllGreater(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_all_greater<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if all indices in the provided range within this Vector are greater than rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if all comparisons within the provided range are true, otherwise false.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllGreater(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_all_greater<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if any indices within this Vector are greater than rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para>
		///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
		///		If false, comparisons will only be performed until the end of the smallest Vector. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if at least 1 comparison is true, otherwise false.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyGreater(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_any_greater<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if any indices in the provided range within this Vector are greater than rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if at least 1 comparison within the provided range is true, otherwise false.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyGreater(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_any_greater<BeginIndex_, EndIndex_>(std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region CMP_LESS_FUNCS
		/// <summary>
		/// <para> Returns true if the magnitude of this Vector is less than that of rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Both Vector's magnitudes will be compared. Otherwise, this Vector's magnitude will be compared with rhs_ directly. </para>
		/// <para> 
		///		IncludeNonContained_: If true, all elements of each Vector will be used to determine their magnitude. 
		///		If false, only elements up to the end of the smallest Vector will be used to determine magnitude. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">EmuMath Vector whose magnitude appears on the right of comparison, or scalar appearing on the right of comparison.</param>
		/// <returns>True if this Vector's magnitude is less than that of rhs_, otherwise false.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpLess(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_less<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if the magnitude of this Vector is less than that of rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Both Vector's magnitudes will be compared. Otherwise, this Vector's magnitude will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors to calculate their magnitude. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors to calculate their magnitude. </para>
		/// </summary>
		/// <param name="rhs_">EmuMath Vector whose magnitude appears on the right of comparison, or scalar appearing on the right of comparison.</param>
		/// <returns>True if this Vector's magnitude is less than that of rhs_, otherwise false.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpLess(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_less<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if all indices within this Vector are less than rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para>
		///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
		///		If false, comparisons will only be performed until the end of the smallest Vector. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if all comparisons are true, otherwise false.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllLess(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_all_less<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if all indices in the provided range within this Vector are less than rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if all comparisons within the provided range are true, otherwise false.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllLess(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_all_less<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if any indices within this Vector are less than rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para>
		///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
		///		If false, comparisons will only be performed until the end of the smallest Vector. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if at least 1 comparison is true, otherwise false.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyLess(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_any_less<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if any indices in the provided range within this Vector are less than rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if at least 1 comparison within the provided range is true, otherwise false.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyLess(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_any_less<BeginIndex_, EndIndex_>(std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region CMP_GREATER_EQUAL_FUNCS
		/// <summary>
		/// <para> Returns true if the magnitude of this Vector is greater than or equal to that of rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Both Vector's magnitudes will be compared. Otherwise, this Vector's magnitude will be compared with rhs_ directly. </para>
		/// <para> 
		///		IncludeNonContained_: If true, all elements of each Vector will be used to determine their magnitude. 
		///		If false, only elements up to the end of the smallest Vector will be used to determine magnitude. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">EmuMath Vector whose magnitude appears on the right of comparison, or scalar appearing on the right of comparison.</param>
		/// <returns>True if this Vector's magnitude is greater than or equal to that of rhs_, otherwise false.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpGreaterEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_greater_equal<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if the magnitude of this Vector is greater than or equal to that of rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Both Vector's magnitudes will be compared. Otherwise, this Vector's magnitude will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors to calculate their magnitude. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors to calculate their magnitude. </para>
		/// </summary>
		/// <param name="rhs_">EmuMath Vector whose magnitude appears on the right of comparison, or scalar appearing on the right of comparison.</param>
		/// <returns>True if this Vector's magnitude is greater than or equal to that of rhs_, otherwise false.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpGreaterEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_greater_equal<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if all indices within this Vector are greater than or equal to rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para>
		///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
		///		If false, comparisons will only be performed until the end of the smallest Vector. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if all comparisons are true, otherwise false.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllGreaterEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_all_greater_equal<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if all indices in the provided range within this Vector are greater than or equal to rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if all comparisons within the provided range are true, otherwise false.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllGreaterEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_all_greater_equal<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if any indices within this Vector are greater than or equal to rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para>
		///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
		///		If false, comparisons will only be performed until the end of the smallest Vector. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if at least 1 comparison is true, otherwise false.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyGreaterEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_any_greater_equal<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if any indices in the provided range within this Vector are greater than or equal to rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if at least 1 comparison within the provided range is true, otherwise false.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyGreaterEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_any_greater_equal<BeginIndex_, EndIndex_>(std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region CMP_LESS_EQUAL_FUNCS
		/// <summary>
		/// <para> Returns true if the magnitude of this Vector is less than or equal to that of rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Both Vector's magnitudes will be compared. Otherwise, this Vector's magnitude will be compared with rhs_ directly. </para>
		/// <para> 
		///		IncludeNonContained_: If true, all elements of each Vector will be used to determine their magnitude. 
		///		If false, only elements up to the end of the smallest Vector will be used to determine magnitude. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">EmuMath Vector whose magnitude appears on the right of comparison, or scalar appearing on the right of comparison.</param>
		/// <returns>True if this Vector's magnitude is less than or equal to that of rhs_, otherwise false.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpLessEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_less_equal<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if the magnitude of this Vector is less than or equal to that of rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Both Vector's magnitudes will be compared. Otherwise, this Vector's magnitude will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors to calculate their magnitude. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors to calculate their magnitude. </para>
		/// </summary>
		/// <param name="rhs_">EmuMath Vector whose magnitude appears on the right of comparison, or scalar appearing on the right of comparison.</param>
		/// <returns>True if this Vector's magnitude is less than or equal to that of rhs_, otherwise false.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpLessEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_less_equal<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if all indices within this Vector are less than or equal to rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para>
		///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
		///		If false, comparisons will only be performed until the end of the smallest Vector. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if all comparisons are true, otherwise false.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllLessEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_all_less_equal<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if all indices in the provided range within this Vector are less than or equal to rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if all comparisons within the provided range are true, otherwise false.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllLessEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_all_less_equal<BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if any indices within this Vector are less than or equal to rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para>
		///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
		///		If false, comparisons will only be performed until the end of the smallest Vector. 
		///		Has no effect if Rhs_ is not an EmuMath Vector. 
		///		Defaults to true.
		/// </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if at least 1 comparison is true, otherwise false.</returns>
		template<bool IncludeNonContained_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyLessEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_any_less_equal<IncludeNonContained_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if any indices in the provided range within this Vector are less than or equal to rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in this Vector will be compared with rhs_ directly. </para>
		/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
		/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
		/// <returns>True if at least 1 comparison within the provided range is true, otherwise false.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyLessEqual(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_cmp_any_less_equal<BeginIndex_, EndIndex_>(std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region CONVERSIONS
	public:
		/// <summary>
		/// <para> Outputs a cast of this Vector as an EmuMath Vector composed of the provided OutSize_ and OutT_ args. </para>
		/// <para> OutSize_: Size of the output Vector. If not provided, this will default to this Vector's size. </para>
		/// <para> OutT_: Typearg for the output Vector. If not provided, this will default to the this Vector's value_type_uq. </para>
		/// <para> At least 1 of OutSize_ or OutT_ must be provided. </para>
		/// <para> Offset_: Optional offset at which to start reading this Vector for forming the output cast. Defaults to 0. </para>
		/// </summary>
		/// <returns>Cast of this Vector as an EmuMath Vector with the provided OutSize_ and OutT_ args.</returns>
		template
		<
			std::size_t OutSize_,
			typename OutT_,
			std::size_t Offset_ = 0,
			typename = std::enable_if_t<EmuMath::Helpers::vector_cast_is_valid<const this_type&, OutSize_, OutT_, Offset_>()>
		>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Cast() const
		{
			return EmuMath::Helpers::vector_cast<OutSize_, OutT_, Offset_>(*this);
		}
		template
		<
			std::size_t OutSize_,
			std::size_t Offset_ = 0,
			typename = std::enable_if_t<EmuMath::Helpers::vector_cast_is_valid<const this_type&, OutSize_, value_type_uq, Offset_>()>
		>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, value_type_uq> Cast() const
		{
			return EmuMath::Helpers::vector_cast<OutSize_, value_type_uq, Offset_>(*this);
		}
		template
		<
			typename OutT_,
			std::size_t Offset_ = 0,
			typename = std::enable_if_t<EmuMath::Helpers::vector_cast_is_valid<const this_type&, size, OutT_, Offset_>()>
		>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Cast() const
		{
			return EmuMath::Helpers::vector_cast<size, OutT_, Offset_>(*this);
		}

		template
		<
			std::size_t OutSize_,
			typename OutT_,
			std::size_t Offset_ = 0,
			typename = std::enable_if_t<EmuMath::Helpers::vector_cast_is_valid<this_type&, OutSize_, OutT_, Offset_>()>
		>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> Cast()
		{
			return EmuMath::Helpers::vector_cast<OutSize_, OutT_, Offset_>(*this);
		}
		template
		<
			std::size_t OutSize_,
			std::size_t Offset_ = 0,
			typename = std::enable_if_t<EmuMath::Helpers::vector_cast_is_valid<this_type&, OutSize_, value_type_uq, Offset_>()>
		>
		[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, value_type_uq> Cast()
		{
			return EmuMath::Helpers::vector_cast<OutSize_, value_type_uq, Offset_>(*this);
		}
		template
		<
			typename OutT_,
			std::size_t Offset_ = 0,
			typename = std::enable_if_t<EmuMath::Helpers::vector_cast_is_valid<this_type&, size, OutT_, Offset_>()>
		>
		[[nodiscard]] constexpr inline EmuMath::NewVector<size, OutT_> Cast()
		{
			return EmuMath::Helpers::vector_cast<size, OutT_, Offset_>(*this);
		}

		/// <summary> Explicit cast operator for converting this Vector to an alternative EmuMath Vector instance. </summary>
		template<std::size_t OutSize_, typename OutT_, typename = std::enable_if_t<EmuMath::Helpers::vector_cast_is_valid<const this_type&, OutSize_, OutT_, 0>()>>
		explicit constexpr inline operator EmuMath::NewVector<OutSize_, OutT_>() const
		{
			return EmuMath::Helpers::vector_cast<OutSize_, OutT_, 0>(*this);
		}

		template<std::size_t OutSize_, typename OutT_, typename = std::enable_if_t<EmuMath::Helpers::vector_cast_is_valid<this_type&, OutSize_, OutT_, 0>()>>
		explicit constexpr inline operator EmuMath::NewVector<OutSize_, OutT_>()
		{
			return EmuMath::Helpers::vector_cast<OutSize_, OutT_, 0>(*this);
		}

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
	public:
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
			EmuMath::Helpers::vector_copy<Arg_>(*this, to_copy_);
		}
		template<typename Arg_, typename = std::enable_if_t<is_valid_template_copy_arg<Arg_&>()>>
		constexpr inline void Copy(const Arg_& to_copy_)
		{
			EmuMath::Helpers::vector_copy<Arg_>(*this, to_copy_);
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
			EmuMath::Helpers::vector_copy<BeginIndex_, EndIndex_, Arg_>(*this, to_copy_);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Arg_>
		constexpr inline void Copy(const Arg_& to_copy_)
		{
			EmuMath::Helpers::vector_copy<BeginIndex_, EndIndex_, Arg_>(*this, to_copy_);
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
			EmuMath::Helpers::vector_copy<CopyNonContained_, Arg_>(*this, to_copy_);
		}
		template<bool CopyNonContained_, typename Arg_>
		constexpr inline void Copy(const Arg_& to_copy_)
		{
			EmuMath::Helpers::vector_copy<CopyNonContained_, Arg_>(*this, to_copy_);
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
			EmuMath::Helpers::vector_copy_from_start<BeginIndex_, EndIndex_, Arg_>(*this, to_copy_);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_ = size, typename Arg_>
		constexpr inline void CopyFromStart(const Arg_& to_copy_)
		{
			EmuMath::Helpers::vector_copy_from_start<BeginIndex_, EndIndex_, Arg_>(*this, to_copy_);
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
			EmuMath::Helpers::vector_copy_from_start_contained_only<BeginIndex_, EndIndex_, Arg_>(*this, to_copy_);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_ = size, typename Arg_>
		constexpr inline void CopyFromStartContainedOnly(const Arg_& to_copy_)
		{
			EmuMath::Helpers::vector_copy_from_start_contained_only<BeginIndex_, EndIndex_, Arg_>(*this, to_copy_);
		}
#pragma endregion

#pragma region SETS
	public:
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
			EmuMath::Helpers::vector_set<T_, Size_, InSize_, InT_>(*this, std::move(to_move_set_));
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
			EmuMath::Helpers::vector_set<T_, Size_, InSize_, InT_>(*this, std::move(to_move_set_));
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
			EmuMath::Helpers::vector_set<T_, Size_, InSize_, InT_>(*this, to_copy_set_);
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
			EmuMath::Helpers::vector_set<T_, Size_, InSize_, InT_>(*this, to_copy_set_);
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
			EmuMath::Helpers::vector_set_contained_only<T_, Size_, InSize_, InT_>(*this, std::move(to_move_set_));
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
			EmuMath::Helpers::vector_set_contained_only<T_, Size_, InSize_, InT_>(*this, std::move(to_move_set_));
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
			EmuMath::Helpers::vector_set_contained_only<T_, Size_, InSize_, InT_>(*this, to_copy_set_);
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
			EmuMath::Helpers::vector_set_contained_only<T_, Size_, InSize_, InT_>(*this, to_copy_set_);
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
				else if constexpr (EmuCore::TMP::is_static_castable_v<Arg_, stored_type>)
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
			EmuMath::Helpers::vector_set_all<BeginIndex_, EndIndex_>(*this, std::move(arg_));
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
			EmuMath::Helpers::vector_set_all<BeginIndex_, EndIndex_>(*this, arg_);
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
			EmuMath::Helpers::vector_set_all<BeginIndex_, EndIndex_>(*this, arg_);
		}
#pragma endregion

	private:
		/// <summary> Contiguous element data stored within this Vector. </summary>
		data_storage_type _data;
	};
}

namespace std
{
	/// <summary>
	/// <para> Basic additive hash partial-specialisation that performs a hash for an EmuMath Vector's value_type_uq, combining all elements into a single hash. </para>
	/// </summary>
	template<std::size_t Size_, typename T_>
	struct hash<EmuMath::NewVector<Size_, T_>>
	{
	private:
		using _element_hash = std::hash<typename EmuMath::NewVector<Size_, T_>::value_type_uq>;

		// Recursive call to allow constexpr-evaluation
		// --- Constexpr is not guaranteed with standard, but there's no reason to not allow it in case of change/user specialisations
		template<std::size_t Index_, std::size_t MultiplierPrimeConstant_>
		static constexpr inline void _do_all_elements(const EmuMath::NewVector<Size_, T_>& vector_, std::size_t& out_)
		{
			if constexpr (Index_ < EmuMath::NewVector<Size_, T_>::size)
			{
				out_ *= MultiplierPrimeConstant_;
				out_ += _element_hash()(vector_.at<Index_>());

				if constexpr ((Index_ + 1) < EmuMath::NewVector<Size_, T_>::size)
				{
					_do_all_elements<Index_ + 1, MultiplierPrimeConstant_>(vector_, out_);
				}
			}
		}

	public:
		constexpr hash()
		{
		}

		constexpr inline std::size_t operator()(const EmuMath::NewVector<Size_, T_>& vector_) const
		{
			constexpr std::size_t starting_prime_ = 37;
			std::size_t out_ = starting_prime_;
			_do_all_elements<0, 397>(vector_, out_);
			return out_;
		}
	};
}

#endif
