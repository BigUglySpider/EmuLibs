#ifndef EMU_MATH_MATRIX_INFO_H_INC_
#define EMU_MATH_MATRIX_INFO_H_INC_

#include "../../Vector.h"

namespace EmuMath::_underlying_components
{
	/// <summary>
	/// <para> Type used to provide consistent defaults to EmuMath matrices created with the same template arguments. </para>
	/// <para> For any specialisations of EmuMath::Matrix, it is highly recommended to use this MatrixInfo to mimic any defaults that you do not wish to modify. </para>
	/// </summary>
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	struct MatrixInfo
	{
		static constexpr std::size_t num_columns = NumColumns_;
		static constexpr std::size_t num_rows = NumRows_;
		static constexpr std::size_t size = num_columns * num_rows;
		static constexpr bool is_column_major = ColumnMajor_;
		static constexpr bool is_row_major = !is_column_major;
		static constexpr bool is_square = (num_columns == num_rows);

		/// <summary> num_columns if is_column_major is true, otherwise num_rows. </summary>
		static constexpr std::size_t num_major_elements = is_column_major ? num_columns : num_rows;
		/// <summary> num_rows if is_column_major is true, otherwise num_columns. </summary>
		static constexpr std::size_t num_non_major_elements = is_column_major ? num_rows : num_columns;

		/// <summary> The type contained within this matrix. </summary>
		using contained_type = T_;
		/// <summary> Boolean indicating if this matrix contains reference wrapping types. </summary>
		static constexpr bool contains_reference_wrappers = EmuCore::TMP::is_reference_wrapper<contained_type>::value;
		/// <summary> The raw value_type within this matrix before its const qualifier is forcibly removed. </summary>
		using raw_value_type = typename EmuCore::TMP::get_reference_wrapper_contained_type<contained_type>::type;
		/// <summary> Value type of the items stored within this matrix, without const qualifiers where applicable. </summary>
		using value_type = std::remove_const_t<raw_value_type>;
		/// <summary> The preferred floating point type for this matrix. Float if this matrix contains non-floating-point types, otherwise matches value_type. </summary>
		using preferred_floating_point = EmuCore::TMP::first_floating_point_t<value_type, float>;
		/// <summary> Boolean indicating if the reference wrappers within this matrix contain constant references. Always false if contains_reference_wrappers is false. </summary>
		static constexpr bool contains_const_reference_wrappers = std::is_const_v<raw_value_type> && contains_reference_wrappers;
		/// <summary> Boolean indicating if the reference wrappers within this matrix contain non-constant references. Always false if contains_reference_wrappers is false. </summary>
		static constexpr bool contains_non_const_reference_wrappers = contains_reference_wrappers && !contains_const_reference_wrappers;

		/// <summary> Boolean indcating if this matrix's values are integral. </summary>
		static constexpr bool has_integral_elements = std::is_integral_v<std::remove_cv_t<value_type>>;
		/// <summary> Boolean indcating if this matrix's values are floating-points. </summary>
		static constexpr bool has_floating_point_elements = std::is_floating_point_v<std::remove_cv_t<value_type>>;
		/// <summary> Boolean indicating if this matrix's values are constant. </summary>
		static constexpr bool has_const_values = std::is_const_v<raw_value_type>;

		using major_storage_type = EmuMath::Vector<num_non_major_elements, contained_type>;
		using data_storage_type = EmuMath::Vector<num_major_elements, major_storage_type>;
		using random_access_vector_contained_type = std::conditional_t<contains_reference_wrappers, contained_type, EmuMath::InternalVectorReference<contained_type>>;
		using const_random_access_vector_contained_type = std::conditional_t
		<
			contains_reference_wrappers,
			std::conditional_t<contains_const_reference_wrappers, contained_type, EmuMath::InternalVectorReference<const value_type>>, 
			EmuMath::InternalVectorReference<const contained_type>
		>;

		using random_access_row = EmuMath::Vector<num_columns, random_access_vector_contained_type>;
		using random_access_column = EmuMath::Vector<num_rows, random_access_vector_contained_type>;
		using const_random_access_row = EmuMath::Vector<num_columns, const_random_access_vector_contained_type>;
		using const_random_access_column = EmuMath::Vector<num_rows, const_random_access_vector_contained_type>;
	};

	/// <summary>
	/// <para> Type used to perform a consistent static_assertion across EmuMath::Matrix specialisations. </para>
	/// <para> What items are asserted may be customised with the additional boolean arguments. By default, all assertion checks will always be performed. </para>
	/// <para> For any specialisations of EmuMath::Matrix, it is highly recommended to use this matrix_assert to mimic any required static_asserts that should be made. </para>
	/// </summary>
	template
	<
		std::size_t NumColumns_,
		std::size_t NumRows_,
		typename T_,
		bool ColumnMajor_,
		bool AtLeastOneColumn_ = true,
		bool AtLeastOneRow_ = true,
		bool NoVoid_ = true,
		bool NoBasicRef_ = true,
		bool RequireArithmetic_ = true
	>
	struct matrix_assert
	{
		constexpr matrix_assert()
		{
		}

		static_assert(!AtLeastOneColumn_ || NumColumns_ != 0, "Attempted to instantiate an EmuMath matrix with 0 columns. A matrix must contain at least 1 column.");
		static_assert(!AtLeastOneRow_ || NumRows_ != 0, "Attempted to instantiate an EmuMath matrix with 0 rows. A matrix must contain at least 1 row.");
		static_assert(!NoVoid_ || !std::is_same_v<T_, void>, "Unable to create an EmuMath matrix which contains void elements.");
		static_assert(!NoBasicRef_ || !std::is_reference_v<T_>, "Attempted to form an EmuMath matrix with an internal reference type. To have a matrix storing references, use EmuMath::InternalMatrixReference<T> as the matrix's stored type, or create a matrix via the EmuMath::RefMatrix or EmuMath::ConstRefMatrix aliases to achieve the same with cleaner semantics.");

		using matrix_info = EmuMath::_underlying_components::MatrixInfo<NumColumns_, NumRows_, T_, ColumnMajor_>;
		static_assert(!RequireArithmetic_ || std::is_arithmetic_v<typename matrix_info::value_type>, "Attempted to create an EmuMath matrix with a non-arithmetic value_type. This behaviour is not supported.");
	};
}

#endif
