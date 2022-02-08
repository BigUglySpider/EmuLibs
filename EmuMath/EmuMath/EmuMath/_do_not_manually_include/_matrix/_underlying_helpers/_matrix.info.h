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
		using matrix_vector_type = EmuMath::Vector<size, T_>;
		static constexpr bool contains_ref = matrix_vector_type::contains_ref;
		static constexpr bool contains_const_ref = matrix_vector_type::contains_const_ref;
		static constexpr bool contains_non_const_ref = matrix_vector_type::contains_non_const_ref;

		// Type info for elements
		using stored_type = typename matrix_vector_type::stored_type;
		using value_type = typename matrix_vector_type::value_type;
		using value_type_uq = typename matrix_vector_type::value_type_uq;
		using preferred_floating_point = typename matrix_vector_type::preferred_floating_point;
	};
}

#endif
