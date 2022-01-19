#ifndef EMU_MATH_MATRIX_INFO_H_INC_
#define EMU_MATH_MATRIX_INFO_H_INC_ 1

#include "_matrix_tmp.h"
#include "../../../Vector.h"

namespace EmuMath::TMP
{
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	struct common_matrix_info
	{
		// Template info
		static constexpr std::size_t num_columns = NumColumns_;
		static constexpr std::size_t num_rows = NumRows_;
		static constexpr bool is_column_major = ColumnMajor_;
		static constexpr bool is_row_major = !is_column_major;

		// Extra size info
		static constexpr std::size_t num_major_elements = is_column_major ? num_columns : num_rows;
		static constexpr std::size_t num_non_major_elements = is_column_major ? num_rows : num_columns;
		static constexpr std::size_t size = num_columns * num_rows;

		// Matrix storage types and info regarding their elements
		// --- Effectively a vector of major vectors.
		using major_vector_type = EmuMath::Vector<num_non_major_elements, T_>;
		using matrix_vector_type = EmuMath::Vector<num_major_elements, major_vector_type>;
		static constexpr bool contains_ref = major_vector_type::contains_ref;
		static constexpr bool contains_const_ref = major_vector_type::contains_const_ref;
		static constexpr bool contains_non_const_ref = major_vector_type::contains_non_const_ref;

		// Type info for elements
		using stored_type = typename major_vector_type::stored_type;
		using value_type = typename major_vector_type::value_type;
		using value_type_uq = typename major_vector_type::value_type_uq;
		using preferred_floating_point = typename major_vector_type::preferred_floating_point;

		// Vectorwise access types
		// --- Const ref gets for non-majors still return a const EmuMath Vector, to provide a consistent interface for both major-orders
		using column_get_ref_type = std::conditional_t<is_column_major, major_vector_type&, EmuMath::Vector<num_rows, value_type&>>;
		using row_get_ref_type = std::conditional_t<is_row_major, major_vector_type&, EmuMath::Vector<num_columns, value_type&>>;
		using column_get_const_ref_type = std::conditional_t<is_column_major, const major_vector_type&, const EmuMath::Vector<num_rows, const value_type&>>;
		using row_get_const_ref_type = std::conditional_t<is_row_major, const major_vector_type&, const EmuMath::Vector<num_columns, const value_type&>>;
		using major_get_ref_type = major_vector_type&;
		using major_get_const_ref_type = const major_vector_type&;
		using non_major_get_ref_type = std::conditional_t<is_column_major, row_get_ref_type, column_get_ref_type>;
		using non_major_get_const_ref_type = std::conditional_t<is_column_major, row_get_const_ref_type, column_get_const_ref_type>;

		// Misc info
		static constexpr bool is_contiguous = sizeof(matrix_vector_type) == (sizeof(stored_type) * size);
	};
}

#endif
