#ifndef EMU_MATH_NEW_VECTOR_INFO_H_INC_
#define EMU_MATH_NEW_VECTOR_INFO_H_INC_ 1

#include "_vector_tmp.h"

namespace EmuMath::TMP
{
	template<std::size_t Size_, typename T_, bool AllowAssertions_ = true>
	struct common_vector_info
	{
#pragma region HELPER_STRUCTS
	private:
		using this_info = common_vector_info<Size_, T_, AllowAssertions_>;

		template<class StoredType_>
		struct _find_value_type
		{
			using type = StoredType_;
		};
		template<class StoredReferenceType_>
		struct _find_value_type<EmuMath::vector_internal_ref<StoredReferenceType_>>
		{
			using type = StoredReferenceType_;
		};

		template<class InType_>
		struct _find_alternative_vector_rep
		{
			using type = std::conditional_t
			<
				std::is_lvalue_reference_v<InType_>,
				EmuMath::NewVector<Size_, EmuMath::vector_internal_ref<std::remove_reference_t<InType_>>>,
				std::false_type
			>;
		};
		template<class InReferencedType_>
		struct _find_alternative_vector_rep<EmuMath::vector_internal_ref<InReferencedType_>>
		{
			using type = EmuMath::NewVector<Size_, InReferencedType_&>;
		};
		
		template<std::size_t Size_, typename InT_, bool in_is_const, bool in_is_temp>
		struct _is_valid_vector_for_set
		{
			static constexpr inline bool _may_be_created_from_get_return()
			{
				using in_vector_type = EmuMath::NewVector<Size_, InT_>;
				using in_get_type = typename EmuCore::TMP::conditional_const_t<in_is_const, typename in_vector_type::value_type>&;
				return
				(
					std::is_assignable_v<stored_type, in_get_type> ||
					std::is_constructible_v<stored_type, in_get_type> ||
					std::is_convertible_v<in_get_type, stored_type>
				);
			}

			[[nodiscard]] static constexpr inline bool get()
			{
				using in_vector_type = EmuMath::NewVector<Size_, InT_>;
				using in_get_type = typename EmuCore::TMP::conditional_const_t<in_is_const, typename in_vector_type::value_type>&;

				if constexpr (contains_ref)
				{
					if constexpr (in_is_temp && !(in_vector_type::contains_ref))
					{
						// Dangling references formed in this case
						return false;
					}
					else
					{
						if constexpr (contains_non_const_ref)
						{
							// Must be non-const input to maintain const safety
							if constexpr (in_is_const || std::is_const_v<in_get_type>)
							{
								return false;
							}
							else
							{
								return _may_be_created_from_get_return();
							}
						}
						else
						{
							// Fine to return true as const will be fine, and non-const will implicitly cast to const
							return _may_be_created_from_get_return();
						}
					}
				}
				else
				{
					return _may_be_created_from_get_return();
				}
			}
		};
#pragma endregion
#pragma region TYPE_ALIASES
	public:
		/// <summary>
		/// <para> The underlying type stored within vectors initialised with the provided Size_ and T_ args. </para>
		/// <para> If the provided type is an lvalue reference (e.g. Type&amp; or const Type&amp;): `EmuMath::vector_internal_ref&lt;std::remove_reference_t&lt;T_&gt;&gt;`. </para>
		/// <para> If the provided type is an rvalue reference (e.g. Type&amp;&amp;): `std::false_type.` </para>
		/// <para> If the provided type is none of the above: `T_`. </para>
		/// </summary>
		using stored_type = std::conditional_t
		<
			std::is_lvalue_reference_v<T_>,
			EmuMath::vector_internal_ref<std::remove_reference_t<T_>>,
			std::conditional_t
			<
				std::is_rvalue_reference_v<T_>,
				std::false_type,
				T_
			>
		>;

		/// <summary> 
		/// <para> Type representing a value within a vector initialised with the provided Size_ and T_ args. </para>
		/// <para> If the provided type is an lvalue reference: the type referenced (e.g. where `T_` == `const Type&amp;`, this will be `const Type`). </para>
		/// <para> If the provided type is none of the above: The same as stored_type. </para>
		/// </summary>
		using value_type = typename _find_value_type<stored_type>::type;

		/// <summary>
		/// <para> Type represented within a vector initialised with the provided Size_ and T_ args, without any `const`/`volatile` qualifiers. </para>
		/// <para> This will always be equal to `std::remove_cv_t&lt;value_type&gt;`. </para>
		/// <para> Where `value_type` does not have any `const` or `volatile` qualifiers, this will be the same as `value_type`. </para>
		/// </summary>
		using value_type_uq = std::remove_cv_t<value_type>;
		
		using vector_rep = EmuMath::NewVector<Size_, T_>;
		using alternative_vector_rep = typename _find_alternative_vector_rep<T_>::type;
#pragma endregion

#pragma region STATIC_INFO
	public:
		static constexpr std::size_t size = Size_;

		/// <summary> Boolean indicating if a vector initialised with the provided Size_ and T_ args contains references. </summary>
		static constexpr bool contains_ref = std::is_lvalue_reference_v<T_> ? true : false;

		/// <summary> Boolean indicating if a vector initialised with the provided Size_ and T_ args contains constant references. </summary>
		static constexpr bool contains_const_ref = contains_ref && std::is_const_v<value_type>;

		/// <summary> Boolean indicating if a vector initialised with the provided Size_ and T_ args contains non-constant references. </summary>
		static constexpr bool contains_non_const_ref = contains_ref && !std::is_const_v<value_type>;

		/// <summary> Boolean indicating if a vector initialised with the provided Size_ and T_ args contains integral types or references. </summary>
		static constexpr bool is_integral = std::is_integral_v<value_type_uq>;

		/// <summary> Boolean indicating if a vector initialised with the provided Size_ and T_ args contains floating-point types or references. </summary>
		static constexpr bool is_floating_point = std::is_floating_point_v<value_type_uq>;

		/// <summary> Boolean indicating if a vector initialised with the provided Size_ and T_ args contains class types or references. </summary>
		static constexpr bool is_class = std::is_class_v<value_type_uq>;

		/// <summary> The number of bytes contained within a single element within a vector initialised with the provided Size_ and T_ args. </summary>
		static constexpr std::size_t element_byte_size = sizeof(stored_type);

		static constexpr bool is_default_constructible = !contains_ref && std::is_default_constructible_v<stored_type>;

		static constexpr bool has_alternative_representation = !std::is_same_v<std::false_type, alternative_vector_rep>;
#pragma endregion

#pragma region PUBLIC_HELPER_FUNCS
		template<class...Args_>
		[[nodiscard]] static constexpr inline bool valid_template_construct_args()
		{
			if constexpr (sizeof...(Args_) == 0)
			{
				// Covered by default constructor, so blanket disable
				return false;
			}
			else
			{
				if constexpr (sizeof...(Args_) == size)
				{
					return EmuCore::TMP::are_all_comparisons_true<std::is_constructible, stored_type, Args_...>::value;
				}
				else
				{
					// Number of args must be equal to the number of contained elements
					return false;
				}
			}
		}

		template<std::size_t InSize_, typename InT_, bool in_is_const, bool in_is_temp>
		[[nodiscard]] static constexpr inline bool is_valid_vector_for_set()
		{
			return _is_valid_vector_for_set<InSize_, InT_, in_is_const, in_is_temp>::get();
		}

		template<typename T_>
		[[nodiscard]] static constexpr inline bool is_stored_type_settable_via_type()
		{
			return
			(
				std::is_assignable_v<stored_type, T_> ||
				std::is_constructible_v<stored_type, T_> ||
				std::is_convertible_v<T_, stored_type>
			);
		}

		template<typename T_>
		[[nodiscard]] static constexpr inline bool is_valid_type_for_single_set()
		{
			if constexpr (contains_ref)
			{
				if constexpr (!std::is_lvalue_reference_v<T_>)
				{
					// Temp, so will result in dangling references
					// --- We allow EmuMath Vectors of references for this, however, 
					// --- to allow Vectors of references to Vectors of references (not a typo).
					if constexpr (is_stored_type_settable_via_type<T_>() && EmuMath::TMP::is_emu_new_vector_v<T_>)
					{
						if constexpr (contains_non_const_ref)
						{
							// We need non-const references to maintain const safety
							return T_::contains_non_const_ref;
						}
						else
						{
							// Don't care about T_ ref constness as non-const will implicitly cast to const
							return T_::contains_ref;
						}
					}
					else
					{
						return false;
					}
				}
				else
				{
					if constexpr (contains_non_const_ref)
					{
						// We need a non-const T_ to be able to assign our non-const references to maintain const safety.
						if constexpr (std::is_const_v<T_>)
						{
							return false;
						}
						else
						{
							return is_stored_type_settable_via_type<T_>();
						}
					}
					else
					{
						// No need to worry about constness as non-const will implicitly cast to const
						return is_stored_type_settable_via_type<T_>();
					}
				}
			}
			else
			{
				return is_stored_type_settable_via_type<T_>();
			}
		}

		template<typename T_>
		[[nodiscard]] static constexpr inline bool is_valid_type_for_set_all()
		{
			return is_valid_type_for_single_set<T_>();
		}

		template<typename T_>
		[[nodiscard]] static constexpr inline bool is_valid_lone_type_for_set_all_construction()
		{
			if constexpr (size <= 1)
			{
				// Never true if size == 1, as this is covered by variadic construction.
				return false;
			}
			else
			{
				using t_uq = EmuCore::TMP::remove_ref_cv_t<T_>;
				if constexpr (std::is_same_v<vector_rep, t_uq> || (has_alternative_representation && std::is_same_v<t_uq, alternative_vector_rep>))
				{
					// These constructors are covered explicitly and perform full moves/copies; alternative behaviour is not allowed.
					return false;
				}
				else
				{
					if constexpr (is_valid_type_for_set_all<T_>())
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}

		template<std::size_t OtherSize_, typename OtherT_>
		[[nodiscard]] static constexpr inline bool valid_template_vector_copy_construct_arg()
		{
			using other_vector = EmuMath::NewVector<OtherSize_, OtherT_>;
			if constexpr (valid_template_construct_args<EmuMath::NewVector<OtherSize_, other_vector>>())
			{
				// If this is a valid vector arg for template construction, defer to that as the instantiation speed is likely improved.
				// --- This is because a copy is likely to be a default-then-copy-in-the-body situation.
				return false;
			}
			else
			{
				constexpr bool same_size = Size_ == OtherSize_;
				constexpr bool same_vector = std::is_same_v<T_, OtherT_> && same_size;
				if constexpr (same_vector)
				{
					// Explicit constructor will be provided for same-vector copies to avoid default-then-copy-in-the-body.
					return false;
				}
				else
				{
					constexpr bool same_contained_type = std::is_same_v<stored_type, typename other_vector::stored_type>;
					if constexpr (same_contained_type && same_size)
					{
						// Same size and contained type means we can have an alternative representation of this vector type while being the same under-the-hood
						// --- Exists purely for `Type&` syntactic sugar when forming reference vectors, 
						// --- as the actual contained type is EmuMath::vector_internal_ref<Type_>
						// ------ Explicit construction for alternatives is provided where applicable
						return false;
					}
					else
					{
						// No other conflicts
						if constexpr (contains_ref)
						{
							// Require a Vector large enough to initialise all references
							return other_vector::size >= size;
						}
						else
						{
							return true;
						}
					}
				}
			}
		}

		template<std::size_t OtherSize_, typename OtherT_>
		[[nodiscard]] static constexpr inline bool valid_template_vector_const_copy_construct_arg()
		{
			if constexpr (valid_template_vector_copy_construct_arg<OtherSize_, OtherT_>())
			{
				return !contains_non_const_ref;
			}
			else
			{
				return false;
			}
		}

		template<std::size_t OtherSize_, typename OtherT_>
		[[nodiscard]] static constexpr inline bool valid_template_vector_move_construct_arg()
		{
			return valid_template_vector_copy_construct_arg<OtherSize_, OtherT_>();
		}

		template<typename T_, bool WhenConst_>
		[[nodiscard]] static constexpr inline bool is_valid_try_get_output_ref()
		{
			using get_return_type = EmuCore::TMP::conditional_const_t<WhenConst_, value_type>&;
			return 
			(
				!std::is_const_v<T_> && // Can't output to const
				!std::is_rvalue_reference_v<T_> && // ravlue output is pointless
				!EmuCore::TMP::is_any_comparison_true<std::is_same, T_, value_type**, const value_type**>::value && // Reserved for outputting a reference pointer
				(
					std::is_assignable_v<T_, get_return_type> ||
					std::is_constructible_v<T_, get_return_type> ||
					std::is_convertible_v<get_return_type, T_>
				) // Must be possible to create in one of these standard ways
			);
		}
#pragma endregion

	private:
#pragma region ASSERTION_MANAGEMENT
		[[nodiscard]] static constexpr inline bool _do_assertion()
		{
			if constexpr (AllowAssertions_)
			{
				if constexpr (std::is_rvalue_reference_v<T_>)
				{
					static_assert(false, "Provided an rvalue reference for forming an EmuMath Vector (e.g. `T_` = `Type&&`). Only values or lvalue references may be stored within EmuMath Vectors.");
					return false;
				}
				else
				{
					return true;
				}
			}
			else
			{
				return true;
			}
		}
		static_assert(_do_assertion(), "Invalid arguments provided for forming a conforming EmuMath Vector.");
#pragma endregion
	};
}

#endif
