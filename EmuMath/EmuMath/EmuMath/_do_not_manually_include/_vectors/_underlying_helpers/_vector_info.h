#ifndef EMU_MATH_VECTOR_INFO_H_INC_
#define EMU_MATH_VECTOR_INFO_H_INC_ 1

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
				EmuMath::Vector<Size_, EmuMath::vector_internal_ref<std::remove_reference_t<InType_>>>,
				std::false_type
			>;
		};
		template<class InReferencedType_>
		struct _find_alternative_vector_rep<EmuMath::vector_internal_ref<InReferencedType_>>
		{
			using type = EmuMath::Vector<Size_, InReferencedType_&>;
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

		/// <summary>
		/// <para> Floating-point type to be used with Vector's initialised with the provided Size_ and T_ args in cases where real numbers are preferred. </para>
		/// <para> By default, if value_type_uq is a floating-point type, this will be value_type_uq. Otherwise, it will be float. </para>
		/// </summary>
		using preferred_floating_point = typename EmuMath::TMP::preferred_vector_fp<T_>::type;
		
		using vector_rep = EmuMath::Vector<Size_, T_>;
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

	private:
#pragma region ASSERTION_MANAGEMENT
		[[nodiscard]] static constexpr inline bool _do_assertion()
		{
			if constexpr (AllowAssertions_)
			{
				if constexpr (std::is_rvalue_reference_v<T_>)
				{
					static_assert
					(
						EmuCore::TMP::get_false<T_>(),
						"Provided an rvalue reference for forming an EmuMath Vector (e.g. `T_` = `Type&&`). Only values or lvalue references may be stored within EmuMath Vectors."
					);
					return false;
				}
				else
				{
					return true;
				}
			}
			else
			{
				// Return value is used for a static_assert, but since we aren't allowed to do assertions we shouldn't trigger it, so this is always true
				return true;
			}
		}
		static_assert(_do_assertion(), "Invalid arguments provided for forming a conforming EmuMath Vector.");
#pragma endregion
	};
}

#endif
