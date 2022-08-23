#ifndef EMU_MATH_FAST_MATRIX_T_H_INC_
#define EMU_MATH_FAST_MATRIX_T_H_INC_ 1

#include "_helpers/_all_fast_matrix_helpers.h"
#include "../../FastVector.h"
#include <array>

namespace EmuMath
{
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool IsColumnMajor_, std::size_t RegisterWidth_>
	struct FastMatrix
	{
#pragma region COMMON_STATIC_INFO
	public:
		static constexpr std::size_t num_columns = NumColumns_;
		static constexpr std::size_t num_rows = NumRows_;
		static constexpr bool is_column_major = IsColumnMajor_;
		static constexpr bool is_row_major = !is_column_major;

		static constexpr std::size_t num_major_elements = is_column_major ? num_columns : num_rows;
		static constexpr std::size_t num_non_major_elements = is_column_major ? num_rows : num_columns;
		static constexpr std::size_t size = num_columns * num_rows;
		static constexpr std::size_t smallest_direction_size = (num_columns <= num_rows) ? num_columns : num_rows;
		static constexpr std::size_t greatest_direction_size = (num_columns >= num_rows) ? num_columns : num_rows;

		using this_type = EmuMath::FastMatrix<NumColumns_, NumRows_, T_, IsColumnMajor_, RegisterWidth_>;
		using major_vector_type = EmuMath::FastVector<num_non_major_elements, T_, RegisterWidth_>;
		using value_type = typename major_vector_type::value_type;
		using preferred_floating_point = typename major_vector_type::preferred_floating_point;
		using matrix_type = EmuMath::Matrix<num_columns, num_rows, value_type, is_column_major>;

		using register_type = typename major_vector_type::register_type;
		using register_arg_type = typename major_vector_type::register_arg_type;
		using shift_register_type = typename major_vector_type::shift_register_type;
		static constexpr std::size_t shift_register_per_element_width = major_vector_type::shift_register_per_element_width;

		static constexpr bool is_integral = major_vector_type::is_integral;
		static constexpr bool is_floating_point = major_vector_type::is_floating_point;
		static constexpr bool is_signed = major_vector_type::is_signed;

		static constexpr std::size_t per_element_byte_size = major_vector_type::per_element_byte_size;
		static constexpr std::size_t per_element_width = major_vector_type::per_element_width;
		static constexpr std::size_t total_element_width = major_vector_type::total_element_width;
		static constexpr std::size_t elements_per_register = major_vector_type::elements_per_register;
		static constexpr bool requires_partial_registers = major_vector_type::requires_partial_register;
		static constexpr std::size_t partial_register_length = major_vector_type::partial_register_length;
		static constexpr std::size_t num_registers_per_major = major_vector_type::num_registers;
		static constexpr std::size_t num_registers = num_registers_per_major * num_major_elements;
		static constexpr bool majors_contain_multiple_registers = major_vector_type::contains_multiple_registers;
		static constexpr bool contains_multiple_registers = majors_contain_multiple_registers || (num_major_elements > 1);
		static constexpr std::size_t full_width_size_per_major = major_vector_type::full_width_size;
		static constexpr std::size_t full_width_size = full_width_size_per_major * num_major_elements;

		using data_type = std::array<major_vector_type, num_major_elements>;

		/// <summary> Standard index sequence that may be used to statically iterate over this Matrix's major Vectors. </summary>
		using major_index_sequence = std::make_index_sequence<num_major_elements>;
		using major_register_index_sequence = std::make_index_sequence<num_registers_per_major>;
#pragma endregion

#pragma region CONSTRUCTORS
	public:
		/// <summary>
		/// <para> Default constructor for a FastMatrix, which uses the default construction method of its underlying major Vectors. </para>
		/// </summary>
		constexpr inline FastMatrix() noexcept : major_vectors()
		{
		};

		/// <summary>
		/// <para> Copy constructor for a FastMatrix which copies all respective elements of the passed FastMatrix of the same type. </para>
		/// </summary>
		/// <param name="to_copy_">EmuMath FastMatrix of the same type to copy.</param>
		constexpr inline FastMatrix(const this_type& to_copy_) noexcept :
			major_vectors(EmuMath::Helpers::fast_matrix_copy_data_type(to_copy_), major_index_sequence())
		{
		}

		/// <summary>
		/// <para> Move constructor for a FastMatrix which moves all respective elements of the passed FastMatrix of the same type. </para>
		/// </summary>
		/// <param name="to_move_">EmuMath FastMatrix of the same type to move.</param>
		constexpr inline FastMatrix(this_type&& to_move_) noexcept :
			major_vectors(EmuMath::Helpers::fast_matrix_move_data_type(std::move(to_move_), major_index_sequence()))
		{
		}

		template<class Matrix_>
		requires EmuConcepts::EmuMatrix<Matrix_>
		explicit constexpr inline FastMatrix(Matrix_&& scalar_matrix_) :
			major_vectors(EmuMath::Helpers::fast_matrix_make_majors_from_scalar_matrix<this_type>(std::forward<Matrix_>(scalar_matrix_), major_index_sequence()))
		{
		}
#pragma endregion

#pragma region STORERS
	public:
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline auto Store() const
			-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
		{
			return EmuMath::Helpers::fast_matrix_store<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<typename OutT_ = value_type, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline auto Store() const
			-> EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_>
		{
			return EmuMath::Helpers::fast_matrix_store<num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}
#pragma endregion
#pragma region DATA
	public:
		data_type major_vectors;
#pragma endregion
	};
}

template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool IsColumnMajor_, std::size_t RegisterWidth_>
inline std::ostream& operator<<(std::ostream& str_, const EmuMath::FastMatrix<NumColumns_, NumRows_, T_, IsColumnMajor_, RegisterWidth_>& fast_matrix_)
{
	str_ << fast_matrix_.Store();
	return str_;
}

#endif
