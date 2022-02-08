#ifndef EMU_MATH_VECTOR_T_H_INC_
#define EMU_MATH_VECTOR_T_H_INC_ 1

#include "_helpers/_vector_helpers.h"
#include <array>
#include <functional>
#include <ostream>
#include <sstream>
#include <stdexcept>

namespace EmuMath
{
	template<std::size_t Size_, typename T_>
	struct Vector
	{
#pragma region COMMON_STATIC_INFO
	public:
		using this_type = EmuMath::Vector<Size_, T_>;
		using vector_info = EmuMath::TMP::common_vector_info<Size_, T_, true>;

		using stored_type = typename vector_info::stored_type;
		using value_type = typename vector_info::value_type;
		using value_type_uq = typename vector_info::value_type_uq;
		using preferred_floating_point = typename vector_info::preferred_floating_point;
		using alternative_rep = typename vector_info::alternative_vector_rep;
		friend typename alternative_rep;

		/// <summary> STL-compliant random-access iterator for this Vector type. </summary>
		using iterator = EmuMath::vector_iterator<this_type>;
		/// <summary> STL-compliant constant random-access iterator for this Vector type. </summary>
		using const_iterator = EmuMath::vector_const_iterator<this_type>;
		/// <summary> STL-compliant reverse random-access iterator for this Vector type. </summary>
		using reverse_iterator = EmuMath::vector_reverse_iterator<this_type>;
		/// <summary> STL-compliant constant reverse random-access iterator for this Vector type. </summary>
		using const_reverse_iterator = EmuMath::vector_const_reverse_iterator<this_type>;

		/// <summary> The number of elements contained within this Vector type. </summary>
		static constexpr std::size_t size = vector_info::size;
		/// <summary> True if this Vector contains any kind of reference(s). </summary>
		static constexpr bool contains_ref = vector_info::contains_ref;
		/// <summary> True if this Vector contains const-qualified reference(s). </summary>
		static constexpr bool contains_const_ref = vector_info::contains_const_ref;
		/// <summary> True if this Vector contains non-const-qualified reference(s). </summary>
		static constexpr bool contains_non_const_ref = vector_info::contains_non_const_ref;
		/// <summary> True if the data stored within this Vector type is integral. </summary>
		static constexpr bool is_integral = vector_info::is_integral;
		/// <summary> True if the data stored within this Vector type is floating-point. </summary>
		static constexpr bool is_floating_point = vector_info::is_floating_point;
		/// <summary> True if the data stored within this Vector type is of a class type. </summary>
		static constexpr bool is_class = vector_info::is_class;
		/// <summary> The size of each element of this Vector in bytes. </summary>
		static constexpr std::size_t element_byte_size = vector_info::element_byte_size;
		/// <summary> True if this Vector type can be represented with different template arguments. This is limited to primarily reference-containing Vector types. </summary>
		static constexpr bool has_alternative_representation = vector_info::has_alternative_representation;
		/// <summary>
		/// <para> The number of Vector depths within this Vector type. </para>
		/// <para> If this Vector contains non-Vectors: This is 0. </para>
		/// <para> 
		///		If this Vector contains EmuMath Vectors: This starts at 1, incrementing for every layer of EmuMath Vectors 
		///		(i.e. it is incremented when stored_type::stored_type... is an EmuMath Vector, and continues until ...::stored_type is not an EmuMath Vector.
		/// </para>
		/// <para> For example, Vector&lt;3, Vector&lt;10, Vector&lt;2, float&gt;&gt;&gt; has a depth of 2, as there are 2 layers of internal EmuMath Vectors. </para>
		/// </summary>
		static constexpr std::size_t depth = vector_info::depth;

		using data_storage_type = std::array<stored_type, size>;
		using index_sequence = std::make_index_sequence<size>;

		/// <summary> Functional approach to retrieve this Vector's size. Returns this type's `size` value. </summary>
		[[nodiscard]] static constexpr inline std::size_t get_size()
		{
			return size;
		}

		template<typename T_, bool WhileConst_>
		[[nodiscard]] static constexpr inline bool is_valid_try_get_output_ref()
		{
			return vector_info::template is_valid_try_get_output_ref<T_, WhileConst_>();
		}

		[[nodiscard]] static constexpr inline value_type_uq get_implied_zero()
		{
			return EmuMath::Helpers::vector_get_non_contained<this_type>();
		}

		// Helper to decide if a type should be an EmuMath Vector of size Size__ and type T__, or void.
		// --- If std::is_void_v<T__> is true, the underlying type will be void; otherwise, it will be Vector<Size__, T__>.
		template<std::size_t Size__, typename T__, typename = void>
		struct _vector_or_void
		{
			using type = EmuMath::Vector<Size__, T__>;
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

#pragma region CONSTRUCTOR_VALIDITY_CHECKS
	private:
		template<class Arg_, bool IsVector_ = EmuMath::TMP::is_emu_vector_v<Arg_>>
		struct _func_is_valid_arg_for_stored_type
		{
			template<std::size_t Index_, std::size_t ReadOffset_, bool AllowScalarMoves_, bool DoAssertions_>
			[[nodiscard]] static constexpr inline bool get()
			{
				return false;
			}
		};

		template<class Arg_>
		struct _func_is_valid_arg_for_stored_type<Arg_, true>
		{
			// CHECK FOR EMU VECTOR ARG_
			template<std::size_t Index_, std::size_t ReadOffset_, bool AllowScalarMoves_, bool DoAssertions_>
			[[nodiscard]] static constexpr inline bool get()
			{
				using arg_uq = EmuCore::TMP::remove_ref_cv_t<Arg_>;
				constexpr std::size_t arg_index_ = Index_ + ReadOffset_;
				constexpr bool is_theoretical_index_ = arg_index_ >= arg_uq::size;			

				using arg_get_result = decltype(EmuMath::Helpers::vector_get_theoretical<arg_index_>(EmuCore::TMP::lval_ref_cast<Arg_>(std::declval<Arg_>())));
				if constexpr (EmuMath::TMP::is_emu_vector_v<stored_type> && !EmuMath::TMP::is_emu_vector_v<arg_get_result>)
				{
					// We pass the lval cast instead of forwarding the arg to prevent repeated moves where applicable
					// --- This scenario is for cases such as Vec<4, Vec<4, float>> a = Vec<4, float>(...), where each internal vector will copy the passed Vector
					using passed_defer_type = std::conditional_t
					<
						AllowScalarMoves_,
						decltype(std::forward<Arg_>(std::declval<Arg_>())),
						decltype(EmuCore::TMP::lval_ref_cast<Arg_>(std::forward<Arg_>(std::declval<Arg_>())))
					>;

					if constexpr (std::is_constructible_v<stored_type, passed_defer_type>)
					{
						return true;
					}
					else
					{
						static_assert(!DoAssertions_, "Attempted to create the stored_type of an EmuMath Vector which contains EmuMath Vectors, using an EmuMath Vector which contains non-Vector elements, but the internal Vectors of the output Vector cannot be constructed from the provided input Vector.");
						return false;
					}
				}
				else if constexpr (std::is_lvalue_reference_v<Arg_> || is_theoretical_index_)
				{
					// No explicit std::move allowed
					constexpr bool assigning_theoretical_to_ref_ = is_theoretical_index_ && contains_ref;
					if constexpr (!assigning_theoretical_to_ref_)
					{
						if constexpr (std::is_constructible_v<stored_type, arg_get_result> || EmuCore::TMP::is_static_castable_v<arg_get_result, stored_type>)
						{
							return true;
						}
						else
						{
							static_assert(!DoAssertions_, "Attempted to create an EmuMath Vector's stored_type from an EmuMath Vector argument, but the result of getting one of the indices within the input Vector could not be used to construct or static_cast to the Vector's stored_type.");
							return false;
						}
					}
					else
					{
						static_assert(!DoAssertions_, "Attempted to create an EmuMath Vector's stored_type from an EmuMath Vector argument, but one of the attempted indices to access from the input Vector is a theoretical index, and the output Vector contains references. This would result in a dangling reference, and has been prohibited as a result.");
						return false;
					}
				}
				else
				{
					using arg_move_result = decltype(std::move(EmuCore::TMP::lval_ref_cast<Arg_>(std::declval<Arg_>()).template at<arg_index_>()));
					if constexpr(!contains_ref)
					{
						// Explicit std::move allowed
						if constexpr (std::is_constructible_v<stored_type, arg_move_result> || EmuCore::TMP::is_static_castable_v<arg_move_result, stored_type>)
						{
							return true;
						}
						else
						{
							static_assert(!DoAssertions_, "Attempted to create an EmuMath Vector's stored_type from a moveable EmuMath Vector argument, but the output Vector's stored_type could not be formed from moving or copying the get result of the input Vector.");
							return false;
						}
					}
					else if constexpr(arg_uq::contains_ref)
					{
						// Outputting reference; don't explicitly move references since we aren't actually moving them
						// --- Perform some additional const checks - only doable safely if out is const ref, or input is non-const and contains non-const refs
						constexpr bool compatible_ref_ = contains_const_ref || (arg_uq::contains_non_const_ref && !std::is_const_v<Arg_>);
						if constexpr (compatible_ref_)
						{
							if constexpr (std::is_constructible_v<stored_type, arg_get_result> || EmuCore::TMP::is_static_castable_v<arg_get_result, stored_type>)
							{
								return true;
							}
							else
							{
								static_assert(!DoAssertions_, "Attempted to create an EmuMath Vector of references' stored_type from a moveable EmuMath Vector of references, but the output Vector's stored_type could not be constructed or static_cast to from getting a valid index from the input Vector.");
								return false;
							}
						}
						else
						{
							static_assert(!DoAssertions_, "Attempted to create an EmuMath Vector of references' stored_type from a moveable EmuMath Vector of references, but the constness of references of the input Vector is not compatible with that of the output Vector. If the output Vector contains non-const references, the input Vector must not be const qualified, regardless of the constness of its stored references.");
							return false;
						}
					}
					else
					{
						static_assert(!DoAssertions_, "Attempted to create an EmuMath Vector of references' stored_type from a moveable EmuMath Vector argument which does not contain references. As a moveable argument is considered a likely temporary, this is liable to result in a dangling reference and is thus prohibited.");
						return false;
					}
				}
			}
		};

		template<class Arg_>
		struct _func_is_valid_arg_for_stored_type<Arg_, false>
		{
			// CHECK FOR NON-EMU-VECTOR ARG_
			template<std::size_t Index_, std::size_t ReadOffset_, bool AllowScalarMoves_, bool DoAssertions_>
			[[nodiscard]] static constexpr inline bool get()
			{
				if constexpr(!AllowScalarMoves_)
				{
					// We only allow reference creation if Arg_ is of lvalue reference type to prevent dangling ref creation
					using lval_ref_arg_type = decltype(EmuCore::TMP::lval_ref_cast<Arg_>(std::forward<Arg_>(std::declval<Arg_>())));			
					if constexpr (std::is_lvalue_reference_v<Arg_> || !contains_ref)
					{
						if constexpr(std::is_constructible_v<stored_type, lval_ref_arg_type> && EmuCore::TMP::is_static_castable_v<lval_ref_arg_type, stored_type>)
						{
							return true;
						}
						else
						{
							static_assert(!DoAssertions_, "Attempted to create an EmuMath Vector's stored_type from a non-Vector argument, but it cannot be constructed or static_cast to from an lvalue reference to the provided argument. Note: non-lvalue references will have been cast to an lvalue reference to prevent repeated moves. To avoid this behaviour and perform moves (which may be valid), an argument is required for each index.");
							return false;
						}
					}
					else
					{
						if constexpr (EmuMath::TMP::is_recognised_vector_ref_wrapper_v<Arg_>)
						{
							using wrapped_ref_type = decltype(EmuCore::TMP::lval_ref_cast<Arg_>(std::declval<Arg_>()).get());
							if constexpr (EmuCore::TMP::valid_construct_or_cast<stored_type, Arg_>())
							{
								return true;
							}
							else
							{
								static_assert(!DoAssertions_, "Attempted to create an EmuMath Vector's stored type using a recongised reference-wrapper argument, but the contained reference within the wrapper is not compatible with the output Vector.");
								return false;
							}
						}
						else
						{
							static_assert(!DoAssertions_, "Attempted to create an EmuMath Vector's stored_type from a non-Vector argument, but the output Vector contains references and the provided Arg_ is not an lvalue reference or a recognised reference wrapper. As this is likely to result in dangling references, such behaviour is prohibited.");
							return false;
						}
					}
				}
				else
				{
					if constexpr (std::is_lvalue_reference_v<Arg_>)
					{
						// No explicit move
						using lval_ref_arg_type = decltype(EmuCore::TMP::lval_ref_cast<Arg_>(std::forward<Arg_>(std::declval<Arg_>())));
			
						if constexpr(std::is_constructible_v<stored_type, lval_ref_arg_type> || EmuCore::TMP::is_static_castable_v<lval_ref_arg_type, stored_type>)
						{
							return true;
						}
						else
						{
							static_assert(!DoAssertions_, "Attempted to create an EmuMath Vector's stored_type from a lvalue-reference to a non-Vector argument.");
							return false;
						}
					}
					else
					{
						if constexpr (!contains_ref)
						{
							// Explicit move allowed
							using moved_arg_result = decltype(std::move(std::declval<Arg_>()));
							if constexpr (std::is_constructible_v<stored_type, moved_arg_result> || EmuCore::TMP::is_static_castable_v<moved_arg_result, stored_type>)
							{
								return true;
							}
							else
							{
								static_assert(!DoAssertions_, "Attempted to create an EmuMath Vector's stored_type from a moveable non-Vector argument, but the Vector's stored_type could not be constructed from said argument after a std::move.");
								return false;
							}
						}
						else if constexpr (EmuMath::TMP::is_recognised_vector_ref_wrapper_v<Arg_>)
						{
							using wrapped_ref_type = decltype(EmuCore::TMP::lval_ref_cast<Arg_>(std::declval<Arg_>()).get());
							if constexpr (EmuCore::TMP::valid_construct_or_cast<stored_type, wrapped_ref_type>())
							{
								return true;
							}
							else
							{
								static_assert(!DoAssertions_, "Attempted to create an EmuMath Vector of references' stored_type from a moveable reference wrapper (std::reference_wrapper, EmuMath::vector_internal_ref, or EmuMath::vector_internal_const_ref), but the stored_type could not be used to reference the wrapper's underlying reference.");
								return false;
							}
						}
						else
						{
							static_assert(!DoAssertions_, "Attempted to create an EmuMath Vector of references' stored_type from a moveable scalar that is not a std::reference_wrapper, EmuMath::vector_internal_ref, or EmuMath::vector_internal_const_ref. As this is likely a temporary non-reference-wrapper, such behaviour is prohibited.");
							return false;
						}
					}
				}
			}
		};

		template<std::size_t Index_, std::size_t ReadOffset_, class Arg_, bool AllowScalarMoves_, bool DoAssertions_>
		[[nodiscard]] static constexpr inline bool _is_valid_arg_for_stored_type()
		{
			return _func_is_valid_arg_for_stored_type<Arg_>::template get<Index_, ReadOffset_, AllowScalarMoves_, DoAssertions_>();
		}

		template<std::size_t ReadOffset_, class Arg_, std::size_t...Indices_>
		[[nodiscard]] static constexpr inline bool _underlying_valid_arg_for_all_same_construction(std::index_sequence<Indices_...> indices_)
		{
			using arg_uq = EmuCore::TMP::remove_ref_cv_t<Arg_>;
			if constexpr (!std::is_same_v<this_type, arg_uq>)
			{
				return EmuCore::TMP::variadic_and_v
				<
					_is_valid_arg_for_stored_type<Indices_, ReadOffset_, Arg_, false, false>()...
				>;
			}
			else
			{
				// Reserved for explicit copy/move constructors
				return false;
			}
		}

	public:
		[[nodiscard]] static constexpr inline bool is_default_constructible()
		{
			return 
			(
				!contains_ref &&
				(
					std::is_default_constructible_v<data_storage_type> || std::is_default_constructible_v<stored_type>
				)
			);
		}

		template<std::size_t ReadOffset_, class Arg_>
		[[nodiscard]] static constexpr inline bool valid_arg_for_all_same_construction()
		{
			return _underlying_valid_arg_for_all_same_construction<ReadOffset_, Arg_>(index_sequence());
		}

		template<class Vector_, std::size_t ReadOffset_ = 0>
		[[nodiscard]] static constexpr inline bool is_valid_vector_conversion_arg()
		{
			return EmuCore::TMP::variadic_and_v
			<
				EmuMath::TMP::is_emu_vector_v<Vector_>,
				!std::is_same_v<EmuCore::TMP::remove_ref_cv_t<Vector_>, this_type>,
				valid_arg_for_all_same_construction<ReadOffset_, Vector_>()
			>;
		}

		template<class Vector_, std::size_t ReadOffset_ = 0>
		[[nodiscard]] static constexpr inline bool is_valid_const_vector_conversion_arg()
		{
			return !contains_non_const_ref && is_valid_vector_conversion_arg<Vector_, ReadOffset_>();
		}

		template<std::size_t ReadOffset_, class...Args_>
		[[nodiscard]] static constexpr inline bool valid_args_for_per_element_construction()
		{
			if constexpr (size != 0 && sizeof...(Args_) == size) // 0-args reserved for default
			{
				// For validity:
				// 1: Must be more than 1 argument *or* the only argument is not an EmuMath Vector (as a single argument will use Vector conversion construction instead)
				// 2: Must be at least one of A and B, with A taking priority over B:
				// --- A: All Args_ are immediately valid for constructing data_storage_type when forwarded to an initialiser list for data_storage_type construction
				// --- B: All Args_ are valid lone types for making a stored_type
				return
				(
					(size != 1 || !EmuMath::TMP::is_emu_vector_v<EmuCore::TMP::first_variadic_arg_t<Args_...>>) &&
					(
						std::is_constructible_v<data_storage_type, decltype(std::forward<Args_>(std::declval<Args_>()))...> ||
						EmuCore::TMP::variadic_and_v<_is_valid_arg_for_stored_type<0, ReadOffset_, Args_, true, false>()...>						
					)
				);
			}
			else
			{
				return false;
			}
		}
		template<class...Args_>
		[[nodiscard]] static constexpr inline bool valid_args_for_per_element_construction()
		{
			return valid_args_for_per_element_construction<0, Args_...>();
		}		

		template<std::size_t ReadOffset_, class...Args_>
		[[nodiscard]] static constexpr inline bool valid_args_for_variadic_constructor()
		{
			constexpr bool valid_ = 
			(
				valid_args_for_per_element_construction<ReadOffset_, Args_...>()
			);
			
			if constexpr (!valid_)
			{
				if constexpr (sizeof...(Args_) == 1)
				{
					using arg_type = EmuCore::TMP::first_variadic_arg_t<Args_...>;
					return
					(
						is_valid_vector_conversion_arg<arg_type, ReadOffset_>() ||
						is_valid_const_vector_conversion_arg<arg_type, ReadOffset_>() ||
						valid_arg_for_all_same_construction<ReadOffset_, arg_type>()
					);
				}
				else
				{
					return false;
				}
			}
			else
			{
				return true;
			}
		}
		template<class...Args_>
		[[nodiscard]] static constexpr inline bool valid_args_for_variadic_constructor()
		{
			return valid_args_for_variadic_constructor<0, Args_...>();
		}
#pragma endregion

#pragma region UNDERLYING_CONSTRUCTION_HELPERS
	private:
		template<class Arg_, bool IsVector_ = EmuMath::TMP::is_emu_vector_v<Arg_>>
		struct _func_make_stored_type_from_arg
		{
			// Dummy - partial specialisations will always replace this
			template<std::size_t Index_, std::size_t ReadOffset_, bool AllowScalarMoves_>
			[[nodiscard]] static constexpr inline Arg_&& get(Arg_&& arg_)
			{
				return arg_;
			}
		};

		template<class Arg_>
		struct _func_make_stored_type_from_arg<Arg_, true>
		{
			// CREATE FROM ANOTHER EMUMATH VECTOR
			template<std::size_t Index_, std::size_t ReadOffset_, bool AllowScalarMoves_>
			[[nodiscard]] static constexpr inline stored_type get(Arg_&& arg_)
			{
				using arg_uq = EmuCore::TMP::remove_ref_cv_t<Arg_>;
				constexpr std::size_t arg_index_ = Index_ + ReadOffset_;
				constexpr bool is_theoretical_index_ = arg_index_ >= arg_uq::size;		
			
				using lval_ref_arg_type = decltype(EmuCore::TMP::lval_ref_cast<Arg_>(std::forward<Arg_>(arg_)));
				lval_ref_arg_type lval_ref_arg_ = EmuCore::TMP::lval_ref_cast<Arg_>(std::forward<Arg_>(arg_));

				using arg_get_result = decltype(EmuMath::Helpers::vector_get_theoretical<arg_index_>(lval_ref_arg_));
				if constexpr (EmuMath::TMP::is_emu_vector_v<stored_type> && !EmuMath::TMP::is_emu_vector_v<arg_get_result>)
				{
					// This scenario is for cases such as Vec<4, Vec<4, float>> a = Vec<4, float>(...), where each internal vector will copy the passed Vector
					if constexpr (std::is_constructible_v<stored_type, lval_ref_arg_type>)
					{
						if constexpr (AllowScalarMoves_)
						{
							return stored_type(std::forward<Arg_>(arg_));
						}
						else
						{
							return stored_type(lval_ref_arg_);
						}
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<Arg_>(),
							"Attempted to create the stored_type of an EmuMath Vector which contains EmuMath Vectors, using an EmuMath Vector which contains non-Vector elements, but the internal Vectors of the output Vector cannot be constructed from the provided input Vector."
						);
					}
				}
				else if constexpr (std::is_lvalue_reference_v<Arg_> || is_theoretical_index_)
				{
					// No explicit std::move allowed
					constexpr bool assigning_theoretical_to_ref_ = is_theoretical_index_ && contains_ref;
					if constexpr (!assigning_theoretical_to_ref_)
					{
						if constexpr (EmuCore::TMP::valid_construct_or_cast<stored_type, arg_get_result>())
						{
							return EmuCore::TMP::construct_or_cast<stored_type>(EmuMath::Helpers::vector_get_theoretical<arg_index_>(lval_ref_arg_));
						}
						else
						{
							static_assert
							(
								EmuCore::TMP::get_false<std::size_t, arg_index_>(),
								"Attempted to create an EmuMath Vector's stored_type from an EmuMath Vector argument, but the result of getting one of the indices within the input Vector could not be used to construct or static_cast to the Vector's stored_type."
							);
						}
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<std::size_t, arg_index_>(),
							"Attempted to create an EmuMath Vector's stored_type from an EmuMath Vector argument, but one of the attempted indices to access from the input Vector is a theoretical index, and the output Vector contains references. This would result in a dangling reference, and has been prohibited as a result."
						);
					}
				}
				else
				{
					using arg_move_result = decltype(std::move(lval_ref_arg_.template at<arg_index_>()));
					if constexpr(!contains_ref)
					{
						// Explicit std::move allowed
						if constexpr (EmuCore::TMP::valid_construct_or_cast<stored_type, arg_move_result>())
						{
							return EmuCore::TMP::construct_or_cast<stored_type>(std::move(lval_ref_arg_.template at<arg_index_>()));
						}
						else
						{
							static_assert
							(
								EmuCore::TMP::get_false<std::size_t, arg_index_>(),
								"Attempted to create an EmuMath Vector's stored_type from a moveable EmuMath Vector argument, but the output Vector's stored_type could not be formed from moving or copying the get result of the input Vector."
							);
						}
					}
					else if constexpr(arg_uq::contains_ref)
					{
						// Outputting reference; don't explicitly move references since we aren't actually moving them
						// --- Perform some additional const checks - only doable safely if out is const ref, or input is non-const and contains non-const refs
						constexpr bool compatible_ref_ = contains_const_ref || (arg_uq::contains_non_const_ref && !std::is_const_v<Arg_>);
						if constexpr (compatible_ref_)
						{
							if constexpr (EmuCore::TMP::valid_construct_or_cast<stored_type, arg_get_result>())
							{
								return EmuCore::TMP::construct_or_cast<stored_type>(lval_ref_arg_.template at<arg_index_>());
							}
							else
							{
								static_assert
								(
									EmuCore::TMP::get_false<Arg_>(),
									"Attempted to create an EmuMath Vector of references' stored_type from a moveable EmuMath Vector of references, but the output Vector's stored_type could not be constructed or static_cast to from getting a valid index from the input Vector."
								);
							}
						}
						else
						{
							static_assert
							(
								EmuCore::TMP::get_false<Arg_>(),
								"Attempted to create an EmuMath Vector of references' stored_type from a moveable EmuMath Vector of references, but the constness of references of the input Vector is not compatible with that of the output Vector. If the output Vector contains non-const references, the input Vector must not be const qualified, regardless of the constness of its stored references."
							);
						}
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<Arg_>(),
							"Attempted to create an EmuMath Vector of references' stored_type from a moveable EmuMath Vector argument which does not contain references. As a moveable argument is considered a likely temporary, this is liable to result in a dangling reference and is thus prohibited."
						);
					}
				}
			}
		};

		template<class Arg_>
		struct _func_make_stored_type_from_arg<Arg_, false>
		{
			// CREATE FROM A NON-EMU-VECTOR TYPE
			template<std::size_t Index_, std::size_t ReadOffset_, bool AllowScalarMoves_>
			[[nodiscard]] static constexpr inline stored_type get(Arg_&& arg_)
			{
				if constexpr(!AllowScalarMoves_)
				{
					// We do not allow this arg to be moved as it is used for all output arguments.
					// --- We only allow reference creation if Arg_ is of lvalue reference type to prevent dangling ref creation
			
					if constexpr (std::is_lvalue_reference_v<Arg_> || !contains_ref)
					{
						using lval_ref_arg_type = decltype(EmuCore::TMP::lval_ref_cast<Arg_>(std::forward<Arg_>(arg_)));
						lval_ref_arg_type lval_ref_arg_ = EmuCore::TMP::lval_ref_cast<Arg_>(std::forward<Arg_>(arg_));
						if constexpr (EmuCore::TMP::valid_construct_or_cast<stored_type, lval_ref_arg_type>())
						{
							return EmuCore::TMP::construct_or_cast<stored_type>(lval_ref_arg_);
						}
						else
						{
							static_assert
							(
								EmuCore::TMP::get_false<Arg_>(),
								"Attempted to create an EmuMath Vector's stored_type from a non-Vector argument, but it cannot be constructed or static_cast to from an lvalue reference to the provided argument. Note: non-lvalue references will have been cast to an lvalue reference to prevent repeated moves. To avoid this behaviour and perform moves (which may be valid), an argument is required for each index."
							);
						}
					}
					else
					{
						if constexpr (EmuMath::TMP::is_recognised_vector_ref_wrapper_v<Arg_>)
						{
							using lval_ref_arg_type = decltype(EmuCore::TMP::lval_ref_cast<Arg_>(std::forward<Arg_>(arg_)));
							lval_ref_arg_type lval_ref_arg_ = EmuCore::TMP::lval_ref_cast<Arg_>(std::forward<Arg_>(arg_));
							using wrapped_arg_type = decltype(lval_ref_arg_.get());
							if constexpr (EmuCore::TMP::valid_construct_or_cast<stored_type, wrapped_arg_type>())
							{
								return EmuCore::TMP::construct_or_cast<stored_type>(lval_ref_arg_.get());
							}
							else
							{
								static_assert
								(
									EmuCore::TMP::get_false<Arg_>(),
									"Attempted to create an EmuMath Vector's stored_type from a recognised reference-wrapper argument, but the output Vector does not supported the reference wrapped by it."
								);
							}
						}
						else
						{
							static_assert
							(
								EmuCore::TMP::get_false<Arg_>(),
								"Attempted to create an EmuMath Vector's stored_type from a non-Vector argument, but the output Vector contains references and the provided Arg_ is not an lvalue reference. As this is likely to result in dangling references, such behaviour is prohibited."
							);
						}
					}
				}
				else
				{
					if constexpr (std::is_lvalue_reference_v<Arg_>)
					{
						// No explicit move		
						using lval_ref_arg_type = decltype(EmuCore::TMP::lval_ref_cast<Arg_>(std::forward<Arg_>(arg_)));
						lval_ref_arg_type lval_ref_arg_ = EmuCore::TMP::lval_ref_cast<Arg_>(std::forward<Arg_>(arg_));
						if constexpr (EmuCore::TMP::valid_construct_or_cast<stored_type, lval_ref_arg_type>())
						{
							return EmuCore::TMP::construct_or_cast<stored_type>(lval_ref_arg_);
						}
						else
						{
							static_assert
							(
								EmuCore::TMP::get_false<Arg_>(),
								"Attempted to create an EmuMath Vector's stored_type from a lvalue-reference to a non-Vector argument."
							);
						}
					}
					else if constexpr (!contains_ref)
					{
						// Explicit move allowed
						using moved_arg_result = decltype(std::move(std::declval<Arg_>()));
						if constexpr (EmuCore::TMP::valid_construct_or_cast<stored_type, moved_arg_result>())
						{
							return EmuCore::TMP::construct_or_cast<stored_type>(std::move(arg_));
						}
						else
						{
							static_assert
							(
								EmuCore::TMP::get_false<Arg_>(),
								"Attempted to create an EmuMath Vector's stored_type from a moveable non-Vector argument, but the Vector's stored_type could not be constructed from said argument after a std::move."
							);
						}
					}
					else if constexpr (EmuMath::TMP::is_recognised_vector_ref_wrapper_v<Arg_>)
					{
						using lval_ref_arg_type = decltype(EmuCore::TMP::lval_ref_cast<Arg_>(std::forward<Arg_>(arg_)));
						lval_ref_arg_type lval_ref_arg_ = EmuCore::TMP::lval_ref_cast<Arg_>(std::forward<Arg_>(arg_));
						using wrapped_ref_type = decltype(lval_ref_arg_.get());
						if constexpr (EmuCore::TMP::valid_construct_or_cast<stored_type, wrapped_ref_type>())
						{
							return EmuCore::TMP::construct_or_cast<stored_type>(lval_ref_arg_.get());
						}
						else
						{
							static_assert
							(
								EmuCore::TMP::get_false<Arg_>(),
								"Attempted to create an EmuMath Vector of references' stored_type from a moveable reference wrapper (std::reference_wrapper, EmuMath::vector_internal_ref, or EmuMath::vector_internal_const_ref), but the stored_type could not be used to reference the wrapper's underlying reference."
							);
						}
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<Arg_>(),
							"Attempted to create an EmuMath Vector of references' stored_type from a moveable scalar that is not a std::reference_wrapper, EmuMath::vector_internal_ref, or EmuMath::vector_internal_const_ref. As this is likely a temporary non-reference-wrapper, such behaviour is prohibited."
						);
					}
				}
			}
		};

		template<std::size_t...Indices_>
		[[nodiscard]] static constexpr inline data_storage_type _construct_from_default_stored_types_only(std::index_sequence<Indices_...> indices_)
		{
			return data_storage_type(EmuCore::TMP::type_and_discard_val_t<stored_type, Indices_>()...);
		}

		[[nodiscard]] static constexpr inline data_storage_type _default_construct()
		{
			if constexpr (std::is_default_constructible_v<data_storage_type>)
			{
				return data_storage_type();
			}
			else
			{
				return _construct_from_default_stored_types_only(index_sequence());
			}
		}

		template<class Other_, std::size_t...Indices_>
		[[nodiscard]] static constexpr inline data_storage_type _copy_or_move_other_data(std::index_sequence<Indices_...> indices_, Other_&& to_copy_or_move_)
		{
			if constexpr (std::is_lvalue_reference_v<Other_>)
			{
				// COPY
				return data_storage_type({ to_copy_or_move_[Indices_]... });
			}
			else
			{
				// MOVE
				return data_storage_type({ std::move(to_copy_or_move_[Indices_])... });
			}
		}

		template<std::size_t Index_, std::size_t ReadOffset_, bool AllowScalarMoves_, class Arg_>
		[[nodiscard]] static constexpr inline stored_type _make_stored_type_from_arg(Arg_&& arg_)
		{
			return _func_make_stored_type_from_arg<Arg_>::template get<Index_, ReadOffset_, AllowScalarMoves_>(std::forward<Arg_>(arg_));
		}

		template<std::size_t ReadOffset_, class Arg_, std::size_t...Indices_>
		[[nodiscard]] static constexpr inline data_storage_type _construct_all_from_single_arg(std::index_sequence<Indices_...> indices_, Arg_&& arg_)
		{
			if constexpr (EmuMath::TMP::is_emu_vector_v<Arg_>)
			{
				constexpr bool allow_move_between_depths_ = depth <= EmuCore::TMP::remove_ref_cv_t<Arg_>::depth;
				// Disable Visual Studio warning about using moved-from object, as repeated moves are not allowed here due to the Vector depth requirement
#pragma warning(push)
#pragma warning(disable: 26800)
				return data_storage_type({ _make_stored_type_from_arg<Indices_, ReadOffset_, allow_move_between_depths_>(std::forward<Arg_>(arg_))... });
#pragma warning(pop)
			}
			else
			{
				if constexpr (size == 1)
				{
					return data_storage_type({ _make_stored_type_from_arg<Indices_, ReadOffset_, true>(std::forward<Arg_>(arg_))... });
				}
				else
				{
					// Disable Visual Studio warning about using moved-from object, as we aren't even moving here, but repeated forwarding draws a false positive
#pragma warning(push)
#pragma warning(disable: 26800)
					return data_storage_type({ _make_stored_type_from_arg<Indices_, ReadOffset_, false>(std::forward<Arg_>(arg_))... });
#pragma warning(pop)
				}
			}
		}

		template<std::size_t ReadOffset_, class Arg_>
		[[nodiscard]] static constexpr inline std::conditional_t
		<
			(ReadOffset_ == 0 || !EmuMath::TMP::is_emu_vector_v<stored_type>) && EmuCore::TMP::is_any_same_v<stored_type, Arg_, std::remove_reference_t<Arg_>>,
			decltype(std::forward<Arg_>(std::declval<Arg_>())),
			stored_type
		> _forward_or_make_stored_type(Arg_&& arg_)
		{
			if constexpr ((ReadOffset_ == 0 || !EmuMath::TMP::is_emu_vector_v<stored_type>) && EmuCore::TMP::is_any_same_v<stored_type, Arg_, std::remove_reference_t<Arg_>>)
			{
				return std::forward<Arg_>(arg_);
			}
			else
			{
				return _make_stored_type_from_arg<0, ReadOffset_, true>(std::forward<Arg_>(arg_));
			}
		}

		template<std::size_t ReadOffset_, class...Args_>
		[[nodiscard]] static constexpr inline data_storage_type _construct_all_from_one_arg_per_element(Args_&&...args_)
		{
			if constexpr (std::is_constructible_v<data_storage_type, decltype(std::forward<Args_>(args_))...>)
			{
				return data_storage_type({ std::forward<Args_>(args_)... });
			}
			else
			{
				return data_storage_type({ _forward_or_make_stored_type<ReadOffset_>(std::forward<Args_>(args_))... });
			}
		}

		template<std::size_t ReadOffset_, class...Args_>
		[[nodiscard]] static constexpr inline data_storage_type _variadic_construct(Args_&&...args_)
		{
			if constexpr (valid_args_for_per_element_construction<ReadOffset_, Args_...>())
			{
				return _construct_all_from_one_arg_per_element<ReadOffset_>(std::forward<Args_>(args_)...);
			}
			else if constexpr(sizeof...(Args_) == 1)
			{
				constexpr bool is_vector_conversion_ = 
				(
					is_valid_vector_conversion_arg<EmuCore::TMP::first_variadic_arg_t<Args_...>, ReadOffset_>() ||
					is_valid_const_vector_conversion_arg<EmuCore::TMP::first_variadic_arg_t<Args_...>, ReadOffset_>()
				);
				if constexpr (is_vector_conversion_)
				{
					return _construct_all_from_single_arg<ReadOffset_>(index_sequence(), std::forward<Args_>(args_)...);
				}
				else if constexpr (valid_arg_for_all_same_construction<ReadOffset_, EmuCore::TMP::first_variadic_arg_t<Args_...>>())
				{
					return _construct_all_from_single_arg<ReadOffset_>(index_sequence(), std::forward<Args_>(args_)...);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false(),
						"Internal SFINAE Failure: Invalid variadic construction arguments for an EmuMath Vector have been provided as no possible branch for variadic construction with 1 argument was true."
					);
					return data_storage_type();
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false(),
					"Internal SFINAE Failure: Invalid variadic construction arguments for an EmuMath Vector have been provided as no possible branch for variadic construction with a number of arguments not equal to 1 was true."
				);
				return data_storage_type();
			}
		}
#pragma endregion

#pragma region CONSTRUCTORS
	public:
		/// <summary>
		/// <para> Default constructs all elements within this Vector. </para>
		/// <para> This is only available for Vectors which contain default-constructible, non-reference types. </para>
		/// </summary>
		template<typename OnlyIfNonRefAndContainsDefaultConstructibles_ = std::enable_if_t<is_default_constructible()>>
		constexpr inline Vector() : _data(_default_construct())
		{
		}

		/// <summary>
		/// <para> Constructs a copy of the passed non-const Vector reference. </para>
		/// </summary>
		/// <param name="to_copy_">
		///		: Non-const reference to an EmuMath Vector to copy. If this vector contains references, it will reference the same data as the passed Vector.
		/// </param>
		constexpr inline Vector(this_type& to_copy_) : 
			_data(_copy_or_move_other_data<data_storage_type&>(index_sequence(), to_copy_._data))
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
		constexpr inline Vector(const this_type& to_copy_) : 
			_data(_copy_or_move_other_data<const data_storage_type&>(index_sequence(), to_copy_._data))
		{
		}

		/// <summary>
		/// <para> Moves the data of the passed Vector reference into a newly constructed Vector. </para>
		/// </summary>
		/// <param name="to_move_">: Vector to move into the newly constructed vector.</param>
		constexpr inline Vector(this_type&& to_move_) noexcept : 
			_data(_copy_or_move_other_data<data_storage_type>(index_sequence(), std::move(to_move_._data)))
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
		constexpr inline Vector(alternative_rep& to_copy_) :
			_data(_copy_or_move_other_data<data_storage_type&>(index_sequence(), to_copy_._data))
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
		constexpr inline Vector(const alternative_rep& to_copy_) :
			_data(_copy_or_move_other_data<const data_storage_type&>(index_sequence(), to_copy_._data))
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
		constexpr inline Vector(alternative_rep&& to_move_) noexcept :
			_data(_copy_or_move_other_data<data_storage_type>(index_sequence(), std::move(to_move_._data)))
		{
		}


		template
		<
			class...ConstructionArgs_,
			typename = std::enable_if_t<valid_args_for_variadic_constructor<0, ConstructionArgs_...>()>
		>
		explicit constexpr inline Vector(ConstructionArgs_&&...construction_args_) :
			_data(_variadic_construct<0>(std::forward<ConstructionArgs_>(construction_args_)...))
		{
		}
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
					if constexpr (EmuCore::TMP::feature_constexpr_dynamic_memory())
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

#pragma region STL_ACCESS
	public:
		[[nodiscard]] constexpr inline const_iterator cbegin() const
		{
			return const_iterator(_data.data(), 0);
		}

		[[nodiscard]] constexpr inline const_iterator cend() const
		{
			using diff_type = typename const_reverse_iterator::difference_type;
			constexpr diff_type size_as_diff_ = static_cast<diff_type>(size);
			return const_iterator(_data.data() + size, size_as_diff_);
		}

		[[nodiscard]] constexpr inline const_reverse_iterator crbegin() const
		{
			using diff_type = typename const_reverse_iterator::difference_type;
			constexpr diff_type final_index_ = static_cast<diff_type>(size) - 1;
			return const_reverse_iterator(_data.data() + final_index_, final_index_);
		}

		[[nodiscard]] constexpr inline const_reverse_iterator crend() const
		{
			using diff_type = typename const_reverse_iterator::difference_type;
			constexpr diff_type minus_one_ = diff_type(-1);
			return const_reverse_iterator(_data.data() - 1, minus_one_);
		}

		[[nodiscard]] constexpr inline iterator begin()
		{
			return iterator(_data.data(), 0);
		}

		[[nodiscard]] constexpr inline const_iterator begin() const
		{
			return cbegin();
		}

		[[nodiscard]] constexpr inline iterator end()
		{
			using diff_type = typename const_reverse_iterator::difference_type;
			constexpr diff_type size_as_diff_ = static_cast<diff_type>(size);
			return iterator(_data.data() + size, size_as_diff_);
		}

		[[nodiscard]] constexpr inline const_iterator end() const
		{
			return cend();
		}

		[[nodiscard]] constexpr inline reverse_iterator rbegin()
		{
			using diff_type = typename const_reverse_iterator::difference_type;
			constexpr diff_type final_index_ = static_cast<diff_type>(size) - 1;
			return reverse_iterator(_data.data() + final_index_, final_index_);
		}

		[[nodiscard]] constexpr inline const_reverse_iterator rbegin() const
		{
			return crbegin();
		}

		[[nodiscard]] constexpr inline reverse_iterator rend()
		{
			using diff_type = typename const_reverse_iterator::difference_type;
			constexpr diff_type minus_one_ = diff_type(-1);
			return reverse_iterator(_data.data() - 1, minus_one_);
		}

		[[nodiscard]] constexpr inline const_reverse_iterator rend() const
		{
			return crend();
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> operator++()
		{
			return EmuMath::Helpers::vector_pre_increment<OutSize_, OutT_>(*this);
		}
		template<typename OutT_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> operator++()
		{
			return EmuMath::Helpers::vector_pre_increment<size, OutT_>(*this);
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> operator++(int)
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> operator--()
		{
			return EmuMath::Helpers::vector_pre_decrement<OutSize_, OutT_>(*this);
		}
		template<typename OutT_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> operator--()
		{
			return EmuMath::Helpers::vector_pre_decrement<size, OutT_>(*this);
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> operator--(int)
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> operator-() const
		{
			return EmuMath::Helpers::vector_negate<OutSize_, OutT_>(*this);
		}

		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> operator-() const
		{
			return EmuMath::Helpers::vector_negate<size, OutT_>(*this);
		}
#pragma endregion

#pragma region ASSIGNMENT_OPERATORS
		constexpr inline this_type& operator=(this_type& rhs_)
		{
			EmuMath::Helpers::vector_copy(*this, rhs_);
			return *this;
		}

		template<typename = std::enable_if_t<(!contains_non_const_ref)>>
		constexpr inline this_type& operator=(const this_type& rhs_)
		{
			EmuMath::Helpers::vector_copy(*this, rhs_);
			return *this;
		}

		constexpr inline this_type& operator=(this_type&& rhs_) noexcept
		{
			EmuMath::Helpers::vector_copy(*this, std::forward<this_type>(rhs_));
			return *this;
		}

		template<typename = std::enable_if_t<has_alternative_representation>>
		constexpr inline this_type& operator=(alternative_rep& rhs_)
		{
			EmuMath::Helpers::vector_copy(*this, rhs_);
			return *this;
		}

		template<typename = std::enable_if_t<has_alternative_representation && !contains_non_const_ref>>
		constexpr inline this_type& operator=(const alternative_rep& rhs_)
		{
			EmuMath::Helpers::vector_copy(*this, rhs_);
			return *this;
		}

		template<typename = std::enable_if_t<has_alternative_representation>>
		constexpr inline this_type& operator=(alternative_rep&& rhs_)
		{
			EmuMath::Helpers::vector_copy(*this, std::forward<alternative_rep>(rhs_));
			return *this;
		}

		template<typename = std::enable_if_t<has_alternative_representation && !contains_non_const_ref>>
		constexpr inline this_type& operator=(const alternative_rep&& rhs_)
		{
			EmuMath::Helpers::vector_copy(*this, std::forward<alternative_rep>(rhs_));
			return *this;
		}

		template
		<
			class Rhs_,
			typename = std::enable_if_t
			<
				(
					!std::is_same_v<this_type, EmuCore::TMP::remove_ref_cv_t<Rhs_>> ||
					has_alternative_representation && !std::is_same_v<this_type, EmuCore::TMP::remove_ref_cv_t<Rhs_>>
				)
			>
		>
		constexpr inline this_type& operator=(Rhs_&& rhs_)
		{
			EmuMath::Helpers::vector_copy<0, size, 0>(*this, std::forward<Rhs_>(rhs_));
			return *this;
		}

		template<std::size_t ReadOffset_, class Rhs_>
		constexpr inline this_type& operator=(Rhs_&& rhs_)
		{
			EmuMath::Helpers::vector_copy<0, size, ReadOffset_>(*this, std::forward<Rhs_>(rhs_));
			return *this;
		}

		template<std::size_t CopyBegin_, std::size_t CopyEnd_, std::size_t ReadOffset_ = 0, class Rhs_>
		constexpr inline this_type& operator=(Rhs_&& rhs_)
		{
			EmuMath::Helpers::vector_copy<CopyBegin_, CopyEnd_, ReadOffset_>(*this, std::forward<Rhs_>(rhs_));
			return *this;
		}
#pragma endregion

#pragma region CONST_ARITHMETIC_OPERATORS
	public:
		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> operator+(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_add<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> operator+(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_add<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> operator-(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_subtract<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> operator-(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_subtract<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> operator*(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_multiply<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> operator*(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_multiply<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> operator/(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_divide<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> operator/(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_divide<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> operator%(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_mod<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> operator%(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_mod<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region CONST_BITWISE_OPERATORS
	public:
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> operator~() const
		{
			return EmuMath::Helpers::vector_bitwise_not<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> operator~() const
		{
			return EmuMath::Helpers::vector_bitwise_not<size, OutT_>(*this);
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> operator&(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_and<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> operator&(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_and<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> operator|(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_or<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> operator|(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_or<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> operator^(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_xor<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> operator^(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_xor<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> operator<<(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_left<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> operator<<(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_left<size, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> operator>>(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_right<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> operator>>(Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> PreIncrement()
		{
			return EmuMath::Helpers::vector_pre_increment<OutSize_, OutT_>(*this);
		}
		template<typename OutT_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> PreIncrement()
		{
			return EmuMath::Helpers::vector_pre_increment<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Performs a post-increment on this Vector, equivalent to `this_vector++`. </para>
		/// <para> Creating an unwanted copy may be avoided by passing `void` as the only template argument. </para>
		/// </summary>
		/// <returns>Copy of this Vector before the increment if not provided with only `void` as a template argument; otherwise, no return.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> PostIncrement()
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> PreDecrement()
		{
			return EmuMath::Helpers::vector_pre_decrement<OutSize_, OutT_>(*this);
		}
		template<typename OutT_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> PreDecrement()
		{
			return EmuMath::Helpers::vector_pre_decrement<size, OutT_>();
		}

		/// <summary>
		/// <para> Performs a post-decrement on this Vector, equivalent to `this_vector--`. </para>
		/// <para> Creating an unwanted copy may be avoided by passing `void` as the only template argument. </para>
		/// </summary>
		/// <returns>Copy of this Vector before the decrement if not provided with only `void` as a template argument; otherwise, no return.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> PostDecrement()
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Negate() const
		{
			return EmuMath::Helpers::vector_negate<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Negate() const
		{
			return EmuMath::Helpers::vector_negate<size, OutT_>(*this);
		}
		
		/// <summary> Ouputs a negated form of this Vector to the provided out_vector_, equivalent to `out_vector_ = -this_vector`. </summary>
		/// <param name="out_vector_">: EmuMath Vector to output the negated form of this Vector to.</param>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void Negate(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> NegateRange() const
		{
			return EmuMath::Helpers::vector_negate_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> NegateRange() const
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
		constexpr inline void NegateRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> NegateRangeNoCopy() const
		{
			return EmuMath::Helpers::vector_negate_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, NegateBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t NegateBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> NegateRangeNoCopy() const
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
		constexpr inline void NegateRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Add(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_add<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Add(Rhs_&& rhs_) const
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
		constexpr inline void Add(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> AddRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_add_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> AddRange(Rhs_&& rhs_) const
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
		constexpr inline void AddRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> AddRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_add_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, AddBegin_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AddBegin_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> AddRangeNoCopy(Rhs_&& rhs_) const
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
		constexpr inline void AddRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Subtract(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_subtract<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Subtract(Rhs_&& rhs_) const
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
		constexpr inline void Subtract(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> SubtractRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_subtract_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> SubtractRange(Rhs_&& rhs_) const
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
		constexpr inline void SubtractRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> SubtractRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_subtract_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, SubBegin_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t SubBegin_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> SubtractRangeNoCopy(Rhs_&& rhs_) const
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
		constexpr inline void SubtractRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Multiply(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_multiply<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Multiply(Rhs_&& rhs_) const
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
		constexpr inline void Multiply(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> MultiplyRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_multiply_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> MultiplyRange(Rhs_&& rhs_) const
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
		constexpr inline void MultiplyRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> MultiplyRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_multiply_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, MulBegin_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MulBegin_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> MultiplyRangeNoCopy(Rhs_&& rhs_) const
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
		constexpr inline void MultiplyRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Divide(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_divide<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Divide(Rhs_&& rhs_) const
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
		constexpr inline void Divide(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> DivideRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_divide_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> DivideRange(Rhs_&& rhs_) const
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
		constexpr inline void DivideRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> DivideRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_divide_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, DivBegin_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t DivBegin_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> DivideRangeNoCopy(Rhs_&& rhs_) const
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
		constexpr inline void DivideRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Mod(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_mod<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Mod(Rhs_&& rhs_) const
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
		constexpr inline void Mod(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> ModRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_mod_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> ModRange(Rhs_&& rhs_) const
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
		constexpr inline void ModRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> ModRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_mod_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, ModBegin_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ModBegin_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> ModRangeNoCopy(Rhs_&& rhs_) const
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
		constexpr inline void ModRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_mod_range_no_copy<OutBegin_, OutEnd_, ModBegin_>(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Outputs the result of a fused multiply-add operation on this Vector with the provided y_ and z_ arguments. </para>
		/// <para> This operation will perform only one floating-point round operation; the intermediate from this_vector * y_ is unrounded. </para>
		/// <para> If Y_ is an EmuMath Vector: Respective elements in this Vector and y_ will be multiplied. Otherwise, all elements in this Vector will be multiplied by y_. </para>
		/// <para>
		///		If Z_ is an EmuMath Vector: Intermediate results from each multiplication in specific indices will have the respective indices of z_ added. 
		///		Otherwise, all intermediate multiplication results will have z_ added directly.
		/// </para>
		/// </summary>
		/// <param name="y_">: Scalar or EmuMath Vector to multiply this Vector by.</param>
		/// <param name="z_">: Scalar or EmuMath Vector to add to intermediate multiplication results.</param>
		/// <returns>EmuMath Vector containing the results of a fused multiply-add operation on this Vector with the provided arguments.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq, class Y_, class Z_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Fmadd(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::vector_fmadd<OutSize_, OutT_>(*this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		template<typename OutT_ = value_type_uq, class Y_, class Z_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Fmadd(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::vector_fmadd<size, OutT_>(*this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		template<class Y_, class Z_, std::size_t OutSize_, typename OutT_>
		constexpr inline void Fmadd(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Y_&& y_, Z_&& z_) const
		{
			EmuMath::Helpers::vector_fmadd(out_vector_, *this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector as the desired EmuMath Vector type, with fused multiply-add operations performed in the provided range. </para>
		/// <para> When a fmadd operation is performed, it will perform only one floating-point round operation; the intermediate from this_vector * y_ is unrounded. </para>
		/// <para> If Y_ is an EmuMath Vector: Respective elements in this Vector and y_ will be multiplied. Otherwise, all elements in this Vector will be multiplied by y_. </para>
		/// <para>
		///		If Z_ is an EmuMath Vector: Intermediate results from each multiplication in specific indices will have the respective indices of z_ added. 
		///		Otherwise, all intermediate multiplication results will have z_ added directly.
		/// </para>
		/// <para> BeginIndex_: Inclusive index at which to start fused multiply-adding elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop fused multiply-adding elements. </para>
		/// </summary>
		/// <param name="y_">: Scalar or EmuMath Vector to multiply this Vector by.</param>
		/// <param name="z_">: Scalar or EmuMath Vector to add to intermediate multiplication results.</param>
		/// <returns>Copy of this Vector, with fused multiply-addition performed with the provided y_ and z_ arguments as described within the specified index range.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, class Y_, class Z_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> FmaddRange(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::vector_fmadd_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, class Y_, class Z_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> FmaddRange(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::vector_fmadd_range<size, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Y_, class Z_, std::size_t OutSize_, typename OutT_>
		constexpr inline void FmaddRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Y_&& y_, Z_&& z_) const
		{
			EmuMath::Helpers::vector_fmadd_range<BeginIndex_, EndIndex_>(out_vector_, *this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		/// <summary>
		/// <para> 
		///		Outputs the results of a fused multiply-add on this Vector with the provided y_ and z_ arguments to the specified index range of an output vector, 
		///		starting from index AddBegin_ within any provided input Vectors (including this Vector).
		/// </para>
		/// <para> When a fmadd operation is performed, it will perform only one floating-point round operation; the intermediate from this_vector * y_ is unrounded. </para>
		/// <para> If Y_ is an EmuMath Vector: Respective elements in this Vector and y_ will be multiplied. Otherwise, all elements in this Vector will be multiplied by y_. </para>
		/// <para>
		///		If Z_ is an EmuMath Vector: Intermediate results from each multiplication in specific indices will have the respective indices of z_ added. 
		///		Otherwise, all intermediate multiplication results will have z_ added directly.
		/// </para>
		/// <para> Indices outside of the specified output range will be default-constructed. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing fused arithmetic results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing fused arithmetic results to the output Vector. </para>
		/// <para> FmaddBegin_: Inclusive index at which to start reading elements from this Vector (and y_ and z_ if they are EmuMath Vectors) to perform arithmetic. </para>
		/// </summary>
		/// <param name="y_">: Scalar or EmuMath Vector to multiply this Vector by.</param>
		/// <param name="z_">: Scalar or EmuMath Vector to add to intermediate multiplication results.</param>
		/// <returns>
		///		EmuMath Vector of the desired OutSize_ (defaults to this Vector's size) and OutT_ (defaults to this Vector's value_type_uq), 
		///		containing the results of fused multiply-addition in the specified index range as described, and default values outside of said range.
		/// </returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t FmaddBegin_, std::size_t OutSize_, typename OutT_ = value_type_uq, class Y_, class Z_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> FmaddRangeNoCopy(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::vector_fmadd_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, FmaddBegin_>(*this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t FmaddBegin_, typename OutT_ = value_type_uq, class Y_, class Z_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> FmaddRangeNoCopy(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::vector_fmadd_range_no_copy<size, OutT_, OutBegin_, OutEnd_, FmaddBegin_>(*this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		/// <summary>
		/// <para> 
		///		Outputs the results of a fused multiply-add on this Vector with the provided y_ and z_ arguments to the specified index range of the provided out_vector_, 
		///		starting from index AddBegin_ within any provided input Vectors (including this Vector).
		/// </para>
		/// <para> When a fmadd operation is performed, it will perform only one floating-point round operation; the intermediate from this_vector * y_ is unrounded. </para>
		/// <para> If Y_ is an EmuMath Vector: Respective elements in this Vector and y_ will be multiplied. Otherwise, all elements in this Vector will be multiplied by y_. </para>
		/// <para>
		///		If Z_ is an EmuMath Vector: Intermediate results from each multiplication in specific indices will have the respective indices of z_ added. 
		///		Otherwise, all intermediate multiplication results will have z_ added directly.
		/// </para>
		/// <para> Indices outside of the specified output range will not be modified. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing fused arithmetic results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing fused arithmetic results to the output Vector. </para>
		/// <para> FmaddBegin_: Inclusive index at which to start reading elements from this Vector (and y_ and z_ if they are EmuMath Vectors) to perform arithmetic. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="y_">: Scalar or EmuMath Vector to multiply this Vector by.</param>
		/// <param name="z_">: Scalar or EmuMath Vector to add to intermediate multiplication results.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t FmaddBegin_, class Y_, class Z_, std::size_t OutSize_, typename OutT_>
		constexpr inline void FmaddRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Y_&& y_, Z_&& z_) const
		{
			EmuMath::Helpers::vector_fmadd_range_no_copy<OutBegin_, OutEnd_, FmaddBegin_>(out_vector_, *this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		/// <summary>
		/// <para> Outputs the result of a fused multiply-subtract operation on this Vector with the provided y_ and z_ arguments. </para>
		/// <para> This operation will perform only one floating-point round operation; the intermediate from this_vector * y_ is unrounded. </para>
		/// <para> If Y_ is an EmuMath Vector: Respective elements in this Vector and y_ will be multiplied. Otherwise, all elements in this Vector will be multiplied by y_. </para>
		/// <para>
		///		If Z_ is an EmuMath Vector: Intermediate results from each multiplication in specific indices will have the respective indices of z_ subtracted. 
		///		Otherwise, all intermediate multiplication results will have z_ subtracted directly.
		/// </para>
		/// </summary>
		/// <param name="y_">: Scalar or EmuMath Vector to multiply this Vector by.</param>
		/// <param name="z_">: Scalar or EmuMath Vector to subtract from intermediate multiplication results.</param>
		/// <returns>EmuMath Vector containing the results of a fused multiply-subtract operation on this Vector with the provided arguments.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq, class Y_, class Z_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Fmsub(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::vector_fmsub<OutSize_, OutT_>(*this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		template<typename OutT_ = value_type_uq, class Y_, class Z_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Fmsub(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::vector_fmsub<size, OutT_>(*this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		template<class Y_, class Z_, std::size_t OutSize_, typename OutT_>
		constexpr inline void Fmsub(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Y_&& y_, Z_&& z_) const
		{
			EmuMath::Helpers::vector_fmsub(out_vector_, *this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector as the desired EmuMath Vector type, with fused multiply-subtract operations performed in the provided range. </para>
		/// <para> When a fmsub operation is performed, it will perform only one floating-point round operation; the intermediate from this_vector * y_ is unrounded. </para>
		/// <para> If Y_ is an EmuMath Vector: Respective elements in this Vector and y_ will be multiplied. Otherwise, all elements in this Vector will be multiplied by y_. </para>
		/// <para>
		///		If Z_ is an EmuMath Vector: Intermediate results from each multiplication in specific indices will have the respective indices of z_ subtracted. 
		///		Otherwise, all intermediate multiplication results will have z_ subtracted directly.
		/// </para>
		/// <para> BeginIndex_: Inclusive index at which to start fused multiply-subtracting elements. </para>
		/// <para> EndIndex_: Exclusive index at which to stop fused multiply-subtracting elements. </para>
		/// </summary>
		/// <param name="y_">: Scalar or EmuMath Vector to multiply this Vector by.</param>
		/// <param name="z_">: Scalar or EmuMath Vector to subtract from intermediate multiplication results.</param>
		/// <returns>Copy of this Vector, with fused multiply-subtraction performed with the provided y_ and z_ arguments as described within the specified index range.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, class Y_, class Z_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> FmsubRange(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::vector_fmsub_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, class Y_, class Z_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> FmsubRange(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::vector_fmsub_range<size, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		template<std::size_t BeginIndex_, std::size_t EndIndex_, class Y_, class Z_, std::size_t OutSize_, typename OutT_>
		constexpr inline void FmsubRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Y_&& y_, Z_&& z_) const
		{
			EmuMath::Helpers::vector_fmsub_range<BeginIndex_, EndIndex_>(out_vector_, *this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		/// <summary>
		/// <para> 
		///		Outputs the results of a fused multiply-subtract on this Vector with the provided y_ and z_ arguments to the specified index range of an output vector, 
		///		starting from index AddBegin_ within any provided input Vectors (including this Vector).
		/// </para>
		/// <para> When a fmsub operation is performed, it will perform only one floating-point round operation; the intermediate from this_vector * y_ is unrounded. </para>
		/// <para> If Y_ is an EmuMath Vector: Respective elements in this Vector and y_ will be multiplied. Otherwise, all elements in this Vector will be multiplied by y_. </para>
		/// <para>
		///		If Z_ is an EmuMath Vector: Intermediate results from each multiplication in specific indices will have the respective indices of z_ subtracted. 
		///		Otherwise, all intermediate multiplication results will have z_ subtracted directly.
		/// </para>
		/// <para> Indices outside of the specified output range will be default-constructed. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing fused arithmetic results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing fused arithmetic results to the output Vector. </para>
		/// <para> FmaddBegin_: Inclusive index at which to start reading elements from this Vector (and y_ and z_ if they are EmuMath Vectors) to perform fused arithmetic. </para>
		/// </summary>
		/// <param name="y_">: Scalar or EmuMath Vector to multiply this Vector by.</param>
		/// <param name="z_">: Scalar or EmuMath Vector to subtract from intermediate multiplication results.</param>
		/// <returns>
		///		EmuMath Vector of the desired OutSize_ (defaults to this Vector's size) and OutT_ (defaults to this Vector's value_type_uq), 
		///		containing the results of fused multiply-subtraction in the specified index range as described, and default values outside of said range.
		/// </returns>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t FmaddBegin_, std::size_t OutSize_, typename OutT_ = value_type_uq, class Y_, class Z_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> FmsubRangeNoCopy(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::vector_fmsub_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, FmaddBegin_>(*this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t FmaddBegin_, typename OutT_ = value_type_uq, class Y_, class Z_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> FmsubRangeNoCopy(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::vector_fmsub_range_no_copy<size, OutT_, OutBegin_, OutEnd_, FmaddBegin_>(*this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		/// <summary>
		/// <para> 
		///		Outputs the results of a fused multiply-subtract on this Vector with the provided y_ and z_ arguments to the specified index range of the provided out_vector_, 
		///		starting from index AddBegin_ within any provided input Vectors (including this Vector).
		/// </para>
		/// <para> When a fmsub operation is performed, it will perform only one floating-point round operation; the intermediate from this_vector * y_ is unrounded. </para>
		/// <para> If Y_ is an EmuMath Vector: Respective elements in this Vector and y_ will be multiplied. Otherwise, all elements in this Vector will be multiplied by y_. </para>
		/// <para>
		///		If Z_ is an EmuMath Vector: Intermediate results from each multiplication in specific indices will have the respective indices of z_ subtracted. 
		///		Otherwise, all intermediate multiplication results will have z_ subtracted directly.
		/// </para>
		/// <para> Indices outside of the specified output range will not be modified. </para>
		/// <para> OutBegin_: Inclusive index at which to start writing fused arithmetic results to the output Vector. </para>
		/// <para> OutEnd_: Exclusive index at which to stop writing fused arithmetic results to the output Vector. </para>
		/// <para> FmaddBegin_: Inclusive index at which to start reading elements from this Vector (and y_ and z_ if they are EmuMath Vectors) to perform fused arithmetic. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		/// <param name="y_">: Scalar or EmuMath Vector to multiply this Vector by.</param>
		/// <param name="z_">: Scalar or EmuMath Vector to subtract from intermediate multiplication results.</param>
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t FmaddBegin_, class Y_, class Z_, std::size_t OutSize_, typename OutT_>
		constexpr inline void FmsubRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Y_&& y_, Z_&& z_) const
		{
			EmuMath::Helpers::vector_fmsub_range_no_copy<OutBegin_, OutEnd_, FmaddBegin_>(out_vector_, *this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}
#pragma endregion

#pragma region CONST_BITWISE_FUNCS
	public:
		/// <summary>
		/// <para> Returns the result of bitwise ANDing this Vector with rhs_. </para>
		/// <para> If Rhs_ is an EmuMath Vector: Respective elements will be ANDed. Otherwise, all elements be ANDed with rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Vector to AND with this Vector.</param>
		/// <returns>Copy of this Vector ANDed with rhs_, using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq).</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> And(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_and<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> And(Rhs_&& rhs_) const
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
		constexpr inline void And(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> AndRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_and_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> AndRange(Rhs_&& rhs_) const
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
		constexpr inline void AndRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> AndRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_and_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, AndBegin_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AndBegin_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> AndRangeNoCopy(Rhs_&& rhs_) const
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
		constexpr inline void AndRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Or(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_or<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Or(Rhs_&& rhs_) const
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
		constexpr inline void Or(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> OrRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_or_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> OrRange(Rhs_&& rhs_) const
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
		constexpr inline void OrRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> OrRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_or_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, OrBegin_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t OrBegin_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> OrRangeNoCopy(Rhs_&& rhs_) const
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
		constexpr inline void OrRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Xor(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_xor<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Xor(Rhs_&& rhs_) const
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
		constexpr inline void Xor(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> XorRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_xor_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> XorRange(Rhs_&& rhs_) const
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
		constexpr inline void XorRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> XorRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_bitwise_or_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, XorBegin_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t XorBegin_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> XorRangeNoCopy(Rhs_&& rhs_) const
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
		constexpr inline void XorRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> ShiftLeft(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_left<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> ShiftLeft(Rhs_&& rhs_) const
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
		constexpr inline void ShiftLeft(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> ShiftLeftRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_left_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> ShiftLeftRange(Rhs_&& rhs_) const
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
		constexpr inline void ShiftLeftRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> ShiftLeftRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_left_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, ShiftBegin_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ShiftBegin_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> ShiftLeftRangeNoCopy(Rhs_&& rhs_) const
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
		constexpr inline void ShiftLeftRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> ShiftRight(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_right<OutSize_, OutT_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> ShiftRight(Rhs_&& rhs_) const
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
		constexpr inline void ShiftRight(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> ShiftRightRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_right_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> ShiftRightRange(Rhs_&& rhs_) const
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
		constexpr inline void ShiftRightRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> ShiftRightRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::vector_shift_right_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, ShiftBegin_>(*this, std::forward<Rhs_>(rhs_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ShiftBegin_, typename OutT_ = value_type_uq, typename Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> ShiftRightRangeNoCopy(Rhs_&& rhs_) const
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
		constexpr inline void ShiftRightRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::vector_shift_right_range_no_copy<OutBegin_, OutEnd_, ShiftBegin_>(out_vector_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary> Returns a bitwise NOT form of this Vector, equivalent to `-this_vector`. </summary>
		/// <returns>Copy of this Vector with its elements bitwise NOT-ed, using the OutSize_ arg (defaults to size) and OutT_ arg (defaults to value_type_uq).</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Not() const
		{
			return EmuMath::Helpers::vector_bitwise_not<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Not() const
		{
			return EmuMath::Helpers::vector_bitwise_not<size, OutT_>(*this);
		}
		
		/// <summary> Ouputs a bitwise NOT form of this Vector to the provided out_vector_, equivalent to `out_vector_ = ~this_vector`. </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void Not(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> NotRange() const
		{
			return EmuMath::Helpers::vector_bitwise_not_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> NotRange() const
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
		constexpr inline void NotRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> NotRangeNoCopy() const
		{
			return EmuMath::Helpers::vector_bitwise_not_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, NotBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t NotBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> NotRangeNoCopy() const
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
		constexpr inline void NotRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
	public:
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Abs() const
		{
			return EmuMath::Helpers::vector_abs<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Abs() const
		{
			return EmuMath::Helpers::vector_abs<size, OutT_>(*this);
		}

		/// <summary> Outputs the absolute form of this Vector to the provided out_vector_. </summary>
		/// <param name="out_vector_">: EmuMath Vector to output absolute elements to.</param>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void Abs(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> AbsRange() const
		{
			return EmuMath::Helpers::vector_abs_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> AbsRange() const
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
		constexpr inline void AbsRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> AbsRangeNoCopy() const
		{
			return EmuMath::Helpers::vector_abs_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, AbsBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t AbsBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> AbsRangeNoCopy() const
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
		constexpr inline void AbsRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Lerp(ArgB_&& b_, ArgT_&& t_) const
		{
			return EmuMath::Helpers::vector_lerp<OutSize_, OutT_>(*this, std::forward<ArgB_>(b_), std::forward<ArgT_>(t_));
		}
		template<typename OutT_ = value_type_uq, typename ArgB_, typename ArgT_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Lerp(ArgB_&& b_, ArgT_&& t_) const
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
		constexpr inline void Lerp(EmuMath::Vector<OutSize_, OutT_>& out_vector_, ArgB_&& b_, ArgT_&& t_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> LerpRange(ArgB_&& b_, ArgT_&& t_) const
		{
			return EmuMath::Helpers::vector_lerp_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<ArgB_>(b_), std::forward<ArgT_>(t_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq, typename ArgB_, typename ArgT_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> LerpRange(ArgB_&& b_, ArgT_&& t_) const
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
		constexpr inline void LerpRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_, ArgB_&& b_, ArgT_&& t_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> LerpRangeNoCopy(ArgB_&& b_, ArgT_&& t_) const
		{
			return EmuMath::Helpers::vector_lerp_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, LerpBegin_>(*this, std::forward<ArgB_>(b_), std::forward<ArgT_>(t_));
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t LerpBegin_, typename OutT_ = value_type_uq, typename ArgB_, typename ArgT_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> LerpRangeNoCopy(ArgB_&& b_, ArgT_&& t_) const
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
		constexpr inline void LerpRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, ArgB_&& b_, ArgT_&& t_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Min(B_&& b_) const
		{
			return EmuMath::Helpers::vector_min<OutSize_, OutT_>(*this, std::forward<B_>(b_));
		}
		template<typename OutT_ = preferred_floating_point, typename B_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Min(B_&& b_) const
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
		constexpr inline void Min(EmuMath::Vector<OutSize_, OutT_>& out_vector_, B_&& b_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> MinRange(B_&& b_) const
		{
			return EmuMath::Helpers::vector_min_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<B_>(b_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = preferred_floating_point, typename B_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> MinRange(B_&& b_) const
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
		constexpr inline void MinRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_, B_&& b_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> MinRangeNoCopy(B_&& b_) const
		{
			return EmuMath::Helpers::vector_min_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, MinBegin_>(*this, std::forward<B_>(b_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MinBegin_, typename OutT_ = preferred_floating_point, typename B_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> MinRangeNoCopy(B_&& b_) const
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
		constexpr inline void MinRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, B_&& b_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Max(B_&& b_) const
		{
			return EmuMath::Helpers::vector_max<OutSize_, OutT_>(*this, std::forward<B_>(b_));
		}
		template<typename OutT_ = preferred_floating_point, typename B_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Max(B_&& b_) const
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
		constexpr inline void Max(EmuMath::Vector<OutSize_, OutT_>& out_vector_, B_&& b_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> MaxRange(B_&& b_) const
		{
			return EmuMath::Helpers::vector_max_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<B_>(b_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = preferred_floating_point, typename B_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> MaxRange(B_&& b_) const
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
		constexpr inline void MaxRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_, B_&& b_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> MaxRangeNoCopy(B_&& b_) const
		{
			return EmuMath::Helpers::vector_max_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, MaxBegin_>(*this, std::forward<B_>(b_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MaxBegin_, typename OutT_ = preferred_floating_point, typename B_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> MaxRangeNoCopy(B_&& b_) const
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
		constexpr inline void MaxRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, B_&& b_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> ClampMin(Min_&& min_) const
		{
			return EmuMath::Helpers::vector_clamp_min<OutSize_, OutT_>(*this, std::forward<Min_>(min_));
		}
		template<typename OutT_ = preferred_floating_point, typename Min_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> ClampMin(Min_&& min_) const
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
		constexpr inline void ClampMin(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Min_&& min_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> ClampMinRange(Min_&& min_) const
		{
			return EmuMath::Helpers::vector_clamp_min_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Min_>(min_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = preferred_floating_point, typename Min_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> ClampMinRange(Min_&& min_) const
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
		constexpr inline void ClampMinRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Min_&& min_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> ClampMinRangeNoCopy(Min_&& min_) const
		{
			return EmuMath::Helpers::vector_clamp_min_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, ClampBegin_>(*this, std::forward<Min_>(min_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ClampBegin_, typename OutT_ = preferred_floating_point, typename Min_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> ClampMinRangeNoCopy(Min_&& min_) const
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
		constexpr inline void ClampMinRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Min_&& min_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> ClampMax(Max_&& max_) const
		{
			return EmuMath::Helpers::vector_clamp_max<OutSize_, OutT_>(*this, std::forward<Max_>(max_));
		}
		template<typename OutT_ = preferred_floating_point, typename Max_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> ClampMax(Max_&& max_) const
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
		constexpr inline void ClampMax(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Max_&& max_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> ClampMaxRange(Max_&& max_) const
		{
			return EmuMath::Helpers::vector_clamp_max_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Max_>(max_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = preferred_floating_point, typename Max_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> ClampMaxRange(Max_&& max_) const
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
		constexpr inline void ClampMaxRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Max_&& max_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> ClampMaxRangeNoCopy(Max_&& max_) const
		{
			return EmuMath::Helpers::vector_clamp_max_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, ClampBegin_>(*this, std::forward<Max_>(max_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ClampBegin_, typename OutT_ = preferred_floating_point, typename Max_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> ClampMaxRangeNoCopy(Max_&& max_) const
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
		constexpr inline void ClampMaxRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Max_&& max_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Clamp(Min_&& min_, Max_&& max_) const
		{
			return EmuMath::Helpers::vector_clamp<OutSize_, OutT_>(*this, std::forward<Min_>(min_), std::forward<Max_>(max_));
		}
		template<typename OutT_ = preferred_floating_point, typename Min_, typename Max_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Clamp(Min_&& min_, Max_&& max_) const
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
		constexpr inline void Clamp(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Min_&& min_, Max_&& max_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> ClampRange(Min_&& min_, Max_&& max_) const
		{
			return EmuMath::Helpers::vector_clamp_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, std::forward<Min_>(min_), std::forward<Max_>(max_));
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = preferred_floating_point, typename Min_, typename Max_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> ClampRange(Min_&& min_, Max_&& max_) const
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
		constexpr inline void ClampRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Min_&& min_, Max_&& max_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> ClampRangeNoCopy(Min_&& min_, Max_&& max_) const
		{
			return EmuMath::Helpers::vector_clamp_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, ClampBegin_>(*this, std::forward<Min_>(min_), std::forward<Max_>(max_));
		}
		template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ClampBegin_, typename OutT_ = preferred_floating_point, typename Min_, typename Max_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> ClampRangeNoCopy(Min_&& min_, Max_&& max_) const
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
		constexpr inline void ClampRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, Min_&& min_, Max_&& max_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Floor() const
		{
			return EmuMath::Helpers::vector_floor<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Floor() const
		{
			return EmuMath::Helpers::vector_floor<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with its elements rounded toward negative infinity, to the provided out_vector_. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `FloorConstexpr` instead. </para>
		/// </summary>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void Floor(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> FloorRange() const
		{
			return EmuMath::Helpers::vector_floor_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> FloorRange() const
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
		constexpr inline void FloorRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> FloorRangeNoCopy() const
		{
			return EmuMath::Helpers::vector_floor_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, RoundBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t RoundBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> FloorRangeNoCopy() const
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
		constexpr inline void FloorRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::vector_floor_range_no_copy<OutBegin_, OutEnd_, RoundBegin_>(out_vector_, *this);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with its elements rounded toward positive infinity. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `CeilConstexpr` instead. </para>
		/// </summary>
		/// <returns>Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq>, containing a ceiled copy of this Vector.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Ceil() const
		{
			return EmuMath::Helpers::vector_ceil<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Ceil() const
		{
			return EmuMath::Helpers::vector_ceil<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with its elements rounded toward positive infinity, to the provided out_vector_. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `CeilConstexpr` instead. </para>
		/// </summary>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void Ceil(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> CeilRange() const
		{
			return EmuMath::Helpers::vector_ceil_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> CeilRange() const
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
		constexpr inline void CeilRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> CeilRangeNoCopy() const
		{
			return EmuMath::Helpers::vector_ceil_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, RoundBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t RoundBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> CeilRangeNoCopy() const
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
		constexpr inline void CeilRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::vector_ceil_range_no_copy<OutBegin_, OutEnd_, RoundBegin_>(out_vector_, *this);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with its elements rounded toward 0. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `TruncConstexpr` instead. </para>
		/// </summary>
		/// <returns>Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq>, containing a truncated copy of this Vector.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Trunc() const
		{
			return EmuMath::Helpers::vector_trunc<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Trunc() const
		{
			return EmuMath::Helpers::vector_trunc<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with its elements rounded toward 0, to the provided out_vector_. </para>
		/// <para> Does not provide a guarantee to be constexpr-evaluable if possible; for such behaviour, use `TruncConstexpr` instead. </para>
		/// </summary>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void Trunc(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> TruncRange() const
		{
			return EmuMath::Helpers::vector_trunc_range<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> TruncRange() const
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
		constexpr inline void TruncRange(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> TruncRangeNoCopy() const
		{
			return EmuMath::Helpers::vector_trunc_range_no_copy<OutSize_, OutT_, OutBegin_, OutEnd_, RoundBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t RoundBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> TruncRangeNoCopy() const
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
		constexpr inline void TruncRangeNoCopy(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> FloorConstexpr() const
		{
			return EmuMath::Helpers::vector_floor_constexpr<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> FloorConstexpr() const
		{
			return EmuMath::Helpers::vector_floor_constexpr<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with its elements rounded toward negative infinity, to the provided out_vector_. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `Floor` if calling at runtime. </para>
		/// </summary>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void FloorConstexpr(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> FloorRangeConstexpr() const
		{
			return EmuMath::Helpers::vector_floor_range_constexpr<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> FloorRangeConstexpr() const
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
		constexpr inline void FloorRangeConstexpr(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> FloorRangeNoCopyConstexpr() const
		{
			return EmuMath::Helpers::vector_floor_range_no_copy_constexpr<OutSize_, OutT_, OutBegin_, OutEnd_, RoundBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t RoundBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> FloorRangeNoCopyConstexpr() const
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
		constexpr inline void FloorRangeNoCopyConstexpr(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::vector_floor_range_no_copy_constexpr<OutBegin_, OutEnd_, RoundBegin_>(out_vector_, *this);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with its elements rounded toward positive infinity. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `Ceil` if calling at runtime. </para>
		/// </summary>
		/// <returns>Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq>, containing a ceiled copy of this Vector.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> CeilConstexpr() const
		{
			return EmuMath::Helpers::vector_ceil_constexpr<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> CeilConstexpr() const
		{
			return EmuMath::Helpers::vector_ceil_constexpr<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with its elements rounded toward positive infinity, to the provided out_vector_. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `Ceil` if calling at runtime. </para>
		/// </summary>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void CeilConstexpr(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> CeilRangeConstexpr() const
		{
			return EmuMath::Helpers::vector_ceil_range_constexpr<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> CeilRangeConstexpr() const
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
		constexpr inline void CeilRangeConstexpr(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> CeilRangeNoCopyConstexpr() const
		{
			return EmuMath::Helpers::vector_ceil_range_no_copy_constexpr<OutSize_, OutT_, OutBegin_, OutEnd_, RoundBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t RoundBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> CeilRangeNoCopyConstexpr() const
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
		constexpr inline void CeilRangeNoCopyConstexpr(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::vector_ceil_range_no_copy_constexpr<OutBegin_, OutEnd_, RoundBegin_>(out_vector_, *this);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with its elements rounded toward 0. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `Trunc` if calling at runtime. </para>
		/// </summary>
		/// <returns>Vector of the provided OutSize_ (defaults to size) and OutT_ (defaults to value_type_uq>, containing a truncated copy of this Vector.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> TruncConstexpr() const
		{
			return EmuMath::Helpers::vector_trunc_constexpr<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> TruncConstexpr() const
		{
			return EmuMath::Helpers::vector_trunc_constexpr<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Outputs a copy of this Vector, with its elements rounded toward 0, to the provided out_vector_. </para>
		/// <para> Provides a guarantee to be constexpr-evaluable if possible, but may make sacrifices. One may prefer to use `Trunc` if calling at runtime. </para>
		/// </summary>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void TruncConstexpr(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> TruncRangeConstexpr() const
		{
			return EmuMath::Helpers::vector_trunc_range_constexpr<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> TruncRangeConstexpr() const
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
		constexpr inline void TruncRangeConstexpr(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> TruncRangeNoCopyConstexpr() const
		{
			return EmuMath::Helpers::vector_trunc_range_no_copy_constexpr<OutSize_, OutT_, OutBegin_, OutEnd_, RoundBegin_>(*this);
		}
		template<std::size_t OutBegin, std::size_t OutEnd_, std::size_t RoundBegin_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> TruncRangeNoCopyConstexpr() const
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
		constexpr inline void TruncRangeNoCopyConstexpr(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<sizeof...(Indices_), OutT_> Shuffle()
		{
			return EmuMath::Helpers::vector_shuffle<OutT_, Indices_...>(*this);
		}
		template<typename OutT_, std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::Vector<sizeof...(Indices_), OutT_> Shuffle() const
		{
			return EmuMath::Helpers::vector_shuffle<OutT_, Indices_...>(*this);
		}

		template<std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::Vector<sizeof...(Indices_), value_type_uq> Shuffle()
		{
			return EmuMath::Helpers::vector_shuffle<value_type_uq, Indices_...>(*this);
		}
		template<std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::Vector<sizeof...(Indices_), value_type_uq> Shuffle() const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<sizeof...(Indices_), OutT_> ShuffleTheoretical()
		{
			return EmuMath::Helpers::vector_shuffle_theoretical<OutT_, Indices_...>(*this);
		}
		template<typename OutT_, std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::Vector<sizeof...(Indices_), OutT_> ShuffleTheoretical() const
		{
			return EmuMath::Helpers::vector_shuffle_theoretical<OutT_, Indices_...>(*this);
		}

		template<std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::Vector<sizeof...(Indices_), value_type_uq> ShuffleTheoretical()
		{
			return EmuMath::Helpers::vector_shuffle_theoretical<value_type_uq, Indices_...>(*this);
		}
		template<std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::Vector<sizeof...(Indices_), value_type_uq> ShuffleTheoretical() const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<sizeof...(Indices_), value_type&> RefShuffle()
		{
			return EmuMath::Helpers::vector_shuffle<value_type&, Indices_...>(*this);
		}
		template<std::size_t...Indices_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
		[[nodiscard]] constexpr inline EmuMath::Vector<sizeof...(Indices_), const value_type&> RefShuffle() const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<sizeof...(Indices_), const value_type&> ConstRefShuffle() const
		{
			return EmuMath::Helpers::vector_shuffle<const value_type&, Indices_...>(*this);
		}
#pragma endregion

#pragma region CONCAT_FUNCS
	public:
		/// <summary>
		/// <para> Concatenates this Vector with the passed EmuMath Vector to form a new single Vector. </para>
		/// <para> If Left_ is true, this Vector will appear on the left of concatenation; otherwise, it will appear on the right. </para>
		/// </summary>
		/// <typeparam name="OutT_">T_ argument for the output Vector.</typeparam>
		/// <param name="other_vector_">EmuMath Vector to concatenate this Vector with.</param>
		/// <returns>This Vector concatenated with the passed EmuMath Vector.</returns>
		template<typename OutT_ = value_type_uq, bool Left_ = true, std::size_t OtherSize_, typename OtherT_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size + OtherSize_, OutT_> Concat(const EmuMath::Vector<OtherSize_, OtherT_>& other_vector_)
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
		[[nodiscard]] constexpr inline EmuMath::Vector<size + OtherSize_, OutT_> Concat(const EmuMath::Vector<OtherSize_, OtherT_>& other_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<size + OtherSize_, OutT_> Concat(EmuMath::Vector<OtherSize_, OtherT_>& other_vector_)
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
		[[nodiscard]] constexpr inline EmuMath::Vector<size + OtherSize_, OutT_> Concat(EmuMath::Vector<OtherSize_, OtherT_>& other_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<size + OtherSize_, OutT_> Concat(EmuMath::Vector<OtherSize_, OtherT_>&& other_vector_)
		{
			if constexpr (Left_)
			{
				return EmuMath::Helpers::vector_concat<OutT_>(*this, std::forward<EmuMath::Vector<OtherSize_, OtherT_>>(other_vector_));
			}
			else
			{
				return EmuMath::Helpers::vector_concat<OutT_>(std::forward<EmuMath::Vector<OtherSize_, OtherT_>>(other_vector_), *this);
			}
		}
		template<typename OutT_ = value_type_uq, bool Left_ = true, std::size_t OtherSize_, typename OtherT_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size + OtherSize_, OutT_> Concat(EmuMath::Vector<OtherSize_, OtherT_>&& other_vector_) const
		{
			if constexpr (Left_)
			{
				return EmuMath::Helpers::vector_concat<OutT_>(*this, std::forward<EmuMath::Vector<OtherSize_, OtherT_>>(other_vector_));
			}
			else
			{
				return EmuMath::Helpers::vector_concat<OutT_>(std::forward<EmuMath::Vector<OtherSize_, OtherT_>>(other_vector_), *this);
			}
		}
#pragma endregion

#pragma region VECTOR_OPERATIONS
	public:
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
		[[nodiscard]] constexpr inline Out_ Dot(const EmuMath::Vector<SizeB_, TB_>& vector_b_) const
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
		[[nodiscard]] constexpr inline Out_ Dot(const EmuMath::Vector<SizeB_, TB_>& vector_b_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> NormaliseConstexpr() const
		{
			return EmuMath::Helpers::vector_normalise_constexpr<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> NormaliseConstexpr() const
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
		constexpr inline void NormaliseConstexpr(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> NormaliseConstexpr() const
		{
			return EmuMath::Helpers::vector_normalise_range_constexpr<BeginIndex_, EndIndex_, OutSize_, OutT_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> NormaliseConstexpr() const
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
		constexpr inline void NormaliseConstexpr(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
		{
			EmuMath::Helpers::vector_normalise_range_constexpr<BeginIndex_, EndIndex_>(out_vector_, *this);
		}

		/// <summary>
		/// <para> Calculates and outputs a copy of this Vector with normalised elements. </para>
		/// <para> For a guarantee to produce a compile-time result if possible, use `NormaliseConstexpr` instead. </para>
		/// </summary>
		/// <returns>EmuMath Vector copy of this Vector normalised.</returns>
		template<std::size_t OutSize_, typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Normalise() const
		{
			return EmuMath::Helpers::vector_normalise<OutSize_, OutT_>(*this);
		}
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Normalise() const
		{
			return EmuMath::Helpers::vector_normalise<size, OutT_>(*this);
		}

		/// <summary>
		/// <para> Calculates and outputs a copy of this Vector with normalised elements, via the provided out_vector_. </para>
		/// <para> For a guarantee to produce a compile-time result if possible, use `NormaliseConstexpr` instead. </para>
		/// </summary>
		/// <param name="out_vector_">: EmuMath Vector to output to.</param>
		template<std::size_t OutSize_, typename OutT_>
		constexpr inline void Normalise(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Normalise() const
		{
			return EmuMath::Helpers::vector_normalise_range<BeginIndex_, EndIndex_, OutSize_, OutT_>(*this);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Normalise() const
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
		constexpr inline void Normalise(EmuMath::Vector<OutSize_, OutT_>& out_vector_) const
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
		[[nodiscard]] constexpr inline Out_ AngleCosConstexpr(const EmuMath::Vector<SizeB_, TB_>& vector_b_) const
		{
			return EmuMath::Helpers::vector_angle_cos_constexpr<Out_, Radians_>(*this, vector_b_);
		}
		template<bool Radians_ = true, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline preferred_floating_point AngleCosConstexpr(const EmuMath::Vector<SizeB_, TB_>& vector_b_) const
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
		[[nodiscard]] constexpr inline Out_ AngleCos(const EmuMath::Vector<SizeB_, TB_>& vector_b_) const
		{
			return EmuMath::Helpers::vector_angle_cos<Out_, Radians_>(*this, vector_b_);
		}
		template<bool Radians_ = true, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline preferred_floating_point AngleCos(const EmuMath::Vector<SizeB_, TB_>& vector_b_) const
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
		[[nodiscard]] constexpr inline Out_ Angle(const EmuMath::Vector<SizeB_, TB_>& vector_b_) const
		{
			return EmuMath::Helpers::vector_angle<Out_, Radians_>(*this, vector_b_);
		}
		template<bool Radians_ = true, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline preferred_floating_point Angle(const EmuMath::Vector<SizeB_, TB_>& vector_b_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Cross3(const EmuMath::Vector<SizeB_, TB_>& b_) const
		{
			return EmuMath::Helpers::vector_cross_3d<OutSize_, OutT_>(*this, b_);
		}
		template<typename OutT_ = preferred_floating_point, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> Cross3(const EmuMath::Vector<SizeB_, TB_>& b_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Cross3(const EmuMath::Vector<SizeB_, TB_>& b_) const
		{
			return EmuMath::Helpers::vector_cross_3d<OutSize_, OutT_, I0_, I1_, I2_>(*this, b_);
		}
		template<std::size_t I0_, std::size_t I1_, std::size_t I2_, typename OutT_ = preferred_floating_point, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> Cross3(const EmuMath::Vector<SizeB_, TB_>& b_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Cross3(const EmuMath::Vector<SizeB_, TB_>& b_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> Cross3(const EmuMath::Vector<SizeB_, TB_>& b_) const
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
		[[nodiscard]] constexpr inline Out_ SquareDistance(const EmuMath::Vector<ToSize_, ToT_>& to_) const
		{
			return EmuMath::Helpers::vector_square_distance<Out_, IncludeNonContained_>(*this, to_);
		}
		template<bool IncludeNonContained_, std::size_t ToSize_, typename ToT_>
		[[nodiscard]] constexpr inline preferred_floating_point SquareDistance(const EmuMath::Vector<ToSize_, ToT_>& to_) const
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
		[[nodiscard]] constexpr inline Out_ SquareDistance(const EmuMath::Vector<ToSize_, ToT_>& to_) const
		{
			return EmuMath::Helpers::vector_square_distance<Out_, BeginIndex_, EndIndex_>(*this, to_);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ToSize_, typename ToT_>
		[[nodiscard]] constexpr inline preferred_floating_point SquareDistance(const EmuMath::Vector<ToSize_, ToT_>& to_) const
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
		[[nodiscard]] constexpr inline Out_ Distance(const EmuMath::Vector<ToSize_, ToT_>& to_) const
		{
			return EmuMath::Helpers::vector_distance<Out_, IncludeNonContained_>(*this, to_);
		}
		template<bool IncludeNonContained_, std::size_t ToSize_, typename ToT_>
		[[nodiscard]] constexpr inline preferred_floating_point Distance(const EmuMath::Vector<ToSize_, ToT_>& to_) const
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
		[[nodiscard]] constexpr inline Out_ Distance(const EmuMath::Vector<ToSize_, ToT_>& to_) const
		{
			return EmuMath::Helpers::vector_distance<Out_, BeginIndex_, EndIndex_>(*this, to_);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ToSize_, typename ToT_>
		[[nodiscard]] constexpr inline preferred_floating_point Distance(const EmuMath::Vector<ToSize_, ToT_>& to_) const
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
		[[nodiscard]] constexpr inline Out_ DistanceConstexpr(const EmuMath::Vector<ToSize_, ToT_>& to_) const
		{
			return EmuMath::Helpers::vector_distance_constexpr<Out_, IncludeNonContained_>(*this, to_);
		}
		template<bool IncludeNonContained_, std::size_t ToSize_, typename ToT_>
		[[nodiscard]] constexpr inline preferred_floating_point DistanceConstexpr(const EmuMath::Vector<ToSize_, ToT_>& to_) const
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
		[[nodiscard]] constexpr inline Out_ DistanceConstexpr(const EmuMath::Vector<ToSize_, ToT_>& to_) const
		{
			return EmuMath::Helpers::vector_distance_constexpr<Out_, BeginIndex_, EndIndex_>(*this, to_);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ToSize_, typename ToT_>
		[[nodiscard]] constexpr inline preferred_floating_point DistanceConstexpr(const EmuMath::Vector<ToSize_, ToT_>& to_) const
		{
			return EmuMath::Helpers::vector_distance_constexpr<preferred_floating_point, BeginIndex_, EndIndex_>(*this, to_);
		}

		/// <summary>
		/// <para> Calculates a reflection of this Vector using the provided surface_normal_ Vector. </para>
		/// </summary>
		/// <param name="surface_normal_">: Normal describing a reflection surface. This is expected to be normalised, and treated as such.</param>
		/// <returns>EmuMath Vector representing the reflection of this Vector on the provided surface_normal_.</returns>
		template<std::size_t OutSize_, typename OutT_ = preferred_floating_point, std::size_t NormalSize_, typename NormalT_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Reflect(const EmuMath::Vector<NormalSize_, NormalT_>& surface_normal_) const
		{
			return EmuMath::Helpers::vector_reflect_normal<OutSize_, OutT_>(*this, surface_normal_);
		}
		template<typename OutT_ = preferred_floating_point, std::size_t NormalSize_, typename NormalT_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Reflect(const EmuMath::Vector<NormalSize_, NormalT_>& surface_normal_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Reflect(const EmuMath::Vector<NormalSize_, NormalT_>& surface_normal_) const
		{
			return EmuMath::Helpers::vector_reflect_normal<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, surface_normal_);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = preferred_floating_point, std::size_t NormalSize_, typename NormalT_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Reflect(const EmuMath::Vector<NormalSize_, NormalT_>& surface_normal_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> NormalToPlane3NoNorm
		(
			const EmuMath::Vector<SizeB_, TB_>& point_b_,
			const EmuMath::Vector<SizeC_, TC_>& point_c_
		) const
		{
			return EmuMath::Helpers::vector_normal_to_plane_3d_no_norm<OutSize_, OutT_, ReadOffset_>(*this, point_b_, point_c_);
		}
		template<typename OutT_ = preferred_floating_point, std::size_t ReadOffset_ = 0, std::size_t SizeB_, typename TB_, std::size_t SizeC_, typename TC_>
		[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> NormalToPlane3NoNorm
		(
			const EmuMath::Vector<SizeB_, TB_>& point_b_,
			const EmuMath::Vector<SizeC_, TC_>& point_c_
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> NormalToPlane3Constexpr
		(
			const EmuMath::Vector<SizeB_, TB_>& point_b_,
			const EmuMath::Vector<SizeC_, TC_>& point_c_
		) const
		{
			return EmuMath::Helpers::vector_normal_to_plane_3d_constexpr<OutSize_, OutT_, ReadOffset_>(*this, point_b_, point_c_);
		}
		template<typename OutT_ = preferred_floating_point, std::size_t ReadOffset_ = 0, std::size_t SizeB_, typename TB_, std::size_t SizeC_, typename TC_>
		[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> NormalToPlane3Constexpr
		(
			const EmuMath::Vector<SizeB_, TB_>& point_b_,
			const EmuMath::Vector<SizeC_, TC_>& point_c_
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> NormalToPlane3
		(
			const EmuMath::Vector<SizeB_, TB_>& point_b_,
			const EmuMath::Vector<SizeC_, TC_>& point_c_
		) const
		{
			return EmuMath::Helpers::vector_normal_to_plane_3d<OutSize_, OutT_, ReadOffset_>(*this, point_b_, point_c_);
		}
		template<typename OutT_ = preferred_floating_point, std::size_t ReadOffset_ = 0, std::size_t SizeB_, typename TB_, std::size_t SizeC_, typename TC_>
		[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> NormalToPlane3
		(
			const EmuMath::Vector<SizeB_, TB_>& point_b_,
			const EmuMath::Vector<SizeC_, TC_>& point_c_
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Project(const EmuMath::Vector<SizeB_, TB_>& onto_) const
		{
			return EmuMath::Helpers::vector_project<OutSize_, OutT_>(*this, onto_);
		}
		template<typename OutT_ = preferred_floating_point, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Project(const EmuMath::Vector<SizeB_, TB_>& onto_) const
		{
			return EmuMath::Helpers::vector_project<size, OutT_>(*this, onto_);
		}

		/// <summary>
		/// <para> Calculates the Vector resulting from projecting this Vector onto the Vector onto_, using indices within the specified range. </para>
		/// </summary>
		/// <param name="onto_">: EmuMath Vector to project this Vector onto.</param>
		/// <returns>EmuMath Vector resulting from a projection of this Vector onto the Vector onto_, using indices within the specified range.</returns>
		template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_ = preferred_floating_point, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Project(const EmuMath::Vector<SizeB_, TB_>& onto_) const
		{
			return EmuMath::Helpers::vector_project<OutSize_, OutT_, BeginIndex_, EndIndex_>(*this, onto_);
		}
		template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_ = preferred_floating_point, std::size_t SizeB_, typename TB_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Project(const EmuMath::Vector<SizeB_, TB_>& onto_) const
		{
			return EmuMath::Helpers::vector_project<size, OutT_, BeginIndex_, EndIndex_>(*this, onto_);
		}

		/// <summary>
		/// <para> Calculates the projection of this Vector onto the plane defined by the passed plane_normal_. </para>
		/// </summary>
		/// <param name="plane_normal_">: EmuMath Vector describing the plane to reflect onto. This is expected to be normalised, and treated as such.</param>
		/// <returns>EmuMath Vector resulting from projecting this Vector onto the plane defined by the provided plane_normal_.</returns>
		template<std::size_t OutSize_, typename OutT_ = preferred_floating_point, std::size_t NormSize_, typename NormT_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> ProjectPlane(const EmuMath::Vector<NormSize_, NormT_>& plane_normal_) const
		{
			return EmuMath::Helpers::vector_project_plane<OutSize_, OutT_>(*this, plane_normal_);
		}
		template<typename OutT_ = preferred_floating_point, std::size_t NormSize_, typename NormT_>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> ProjectPlane(const EmuMath::Vector<NormSize_, NormT_>& plane_normal_) const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> ProjectPlane3Constexpr
		(
			const EmuMath::Vector<SizeA_, TA_>& plane_point_a_,
			const EmuMath::Vector<SizeB_, TB_>& plane_point_b_,
			const EmuMath::Vector<SizeC_, TC_>& plane_point_c_
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
		[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> ProjectPlane3Constexpr
		(
			const EmuMath::Vector<SizeA_, TA_>& plane_point_a_,
			const EmuMath::Vector<SizeB_, TB_>& plane_point_b_,
			const EmuMath::Vector<SizeC_, TC_>& plane_point_c_
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> ProjectPlane3
		(
			const EmuMath::Vector<SizeA_, TA_>& plane_point_a_,
			const EmuMath::Vector<SizeB_, TB_>& plane_point_b_,
			const EmuMath::Vector<SizeC_, TC_>& plane_point_c_
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
		[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> ProjectPlane3
		(
			const EmuMath::Vector<SizeA_, TA_>& plane_point_a_,
			const EmuMath::Vector<SizeB_, TB_>& plane_point_b_,
			const EmuMath::Vector<SizeC_, TC_>& plane_point_c_
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
	public:
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
	public:
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
	public:
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
	public:
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
	public:
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
	public:
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
	public:
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Cast() const
		{
			return EmuMath::Helpers::vector_cast<OutSize_, OutT_, Offset_>(*this);
		}
		template
		<
			std::size_t OutSize_,
			std::size_t Offset_ = 0,
			typename = std::enable_if_t<EmuMath::Helpers::vector_cast_is_valid<const this_type&, OutSize_, value_type_uq, Offset_>()>
		>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, value_type_uq> Cast() const
		{
			return EmuMath::Helpers::vector_cast<OutSize_, value_type_uq, Offset_>(*this);
		}
		template
		<
			typename OutT_,
			std::size_t Offset_ = 0,
			typename = std::enable_if_t<EmuMath::Helpers::vector_cast_is_valid<const this_type&, get_size(), OutT_, Offset_>()>
		>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Cast() const
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
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Cast()
		{
			return EmuMath::Helpers::vector_cast<OutSize_, OutT_, Offset_>(*this);
		}
		template
		<
			std::size_t OutSize_,
			std::size_t Offset_ = 0,
			typename = std::enable_if_t<EmuMath::Helpers::vector_cast_is_valid<this_type&, OutSize_, value_type_uq, Offset_>()>
		>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, value_type_uq> Cast()
		{
			return EmuMath::Helpers::vector_cast<OutSize_, value_type_uq, Offset_>(*this);
		}
		template
		<
			typename OutT_,
			std::size_t Offset_ = 0,
			typename = std::enable_if_t<EmuMath::Helpers::vector_cast_is_valid<this_type&, get_size(), OutT_, Offset_>()>
		>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Cast()
		{
			return EmuMath::Helpers::vector_cast<size, OutT_, Offset_>(*this);
		}

		/// <summary> Explicit cast operator for converting this Vector to an alternative EmuMath Vector instance. </summary>
		template<std::size_t OutSize_, typename OutT_, typename = std::enable_if_t<EmuMath::Helpers::vector_cast_is_valid<const this_type&, OutSize_, OutT_, 0>()>>
		explicit constexpr inline operator EmuMath::Vector<OutSize_, OutT_>() const
		{
			return EmuMath::Helpers::vector_cast<OutSize_, OutT_, 0>(*this);
		}

		template<std::size_t OutSize_, typename OutT_, typename = std::enable_if_t<EmuMath::Helpers::vector_cast_is_valid<this_type&, OutSize_, OutT_, 0>()>>
		explicit constexpr inline operator EmuMath::Vector<OutSize_, OutT_>()
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
	struct hash<EmuMath::Vector<Size_, T_>>
	{
	private:
		using _element_hash = std::hash<typename EmuMath::Vector<Size_, T_>::value_type_uq>;

		// Recursive call to allow constexpr-evaluation
		// --- Constexpr is not guaranteed with standard, but there's no reason to not allow it in case of change/user specialisations
		template<std::size_t Index_, std::size_t MultiplierPrimeConstant_>
		static constexpr inline void _do_all_elements(const EmuMath::Vector<Size_, T_>& vector_, std::size_t& out_)
		{
			if constexpr (Index_ < EmuMath::Vector<Size_, T_>::size)
			{
				out_ *= MultiplierPrimeConstant_;
				out_ += _element_hash()(vector_.at<Index_>());

				if constexpr ((Index_ + 1) < EmuMath::Vector<Size_, T_>::size)
				{
					_do_all_elements<Index_ + 1, MultiplierPrimeConstant_>(vector_, out_);
				}
			}
		}

	public:
		constexpr hash()
		{
		}

		constexpr inline std::size_t operator()(const EmuMath::Vector<Size_, T_>& vector_) const
		{
			constexpr std::size_t starting_prime_ = 37;
			std::size_t out_ = starting_prime_;
			_do_all_elements<0, 397>(vector_, out_);
			return out_;
		}
	};
}

#endif
