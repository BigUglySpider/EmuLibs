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
	private:
		template<std::size_t...MajorIndices_>
		[[nodiscard]] constexpr inline void _dump_data(value_type* p_dump_, std::index_sequence<MajorIndices_...> major_indices_) const
		{
			(
				major_vectors[MajorIndices_].template Store<false>
				(
					p_dump_ + (MajorIndices_ * full_width_size_per_major)
				), ...
			);
		}

		template<EmuConcepts::EmuMatrix OutMatrix_, std::size_t ColumnIndex_, std::size_t RowIndex_>
		[[nodiscard]] static constexpr inline decltype(auto) _get_index_for_matrix_store(value_type* p_dump_)
		{
			if constexpr ((ColumnIndex_ < num_columns) && (RowIndex_ < num_rows))
			{
				constexpr std::size_t major_index = is_column_major ? ColumnIndex_ : RowIndex_;
				constexpr std::size_t non_major_index = is_column_major ? RowIndex_ : ColumnIndex_;

				// Offset major index by full register size as we dump all data from a major for better efficiency
				constexpr std::size_t flattened_index = (major_index * full_width_size_per_major) + non_major_index;
				return std::move(*(p_dump_ + flattened_index));
			}
			else
			{
				using _out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
				return _out_mat_uq::get_implied_zero();
			}
		}

		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
		[[nodiscard]] static constexpr inline auto _store_to_new_matrix
		(
			value_type* p_dump_,
			std::index_sequence<ColumnIndices_...> out_column_indices_,
			std::index_sequence<RowIndices_...> out_row_indices_
		) -> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
		{
			// We won't be moving the same index of the pointed-to memory twice, so silence this warning for its false positives
#pragma warning(push)
#pragma warning(disable: 26800)
			return EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				_get_index_for_matrix_store<EmuMath::Matrix<OutNumColumns_, OutNumColumns_, OutT_, OutColumnMajor_>, ColumnIndices_, RowIndices_>
				(
					p_dump_
				)...
			);
#pragma warning(pop)
		}

	public:
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline auto Store() const
			-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
		{
			using _out_mat = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>;

			// Load as few major elements as possible (e.g. if 4x4CM outputting to a 2x4 (any major), we only need 2 of our majors as it only has 2 columns)
			// --- On the contrary, if 4x4RM outputting to a 2x4 (any major), we still need all 4 majors as the output has 4 rows
			constexpr std::size_t out_mat_matching_major_size = is_column_major ? _out_mat::num_columns : _out_mat::num_rows;
			constexpr std::size_t smallest_major_size = num_major_elements <= out_mat_matching_major_size ? num_major_elements : out_mat_matching_major_size;
			value_type data_dump[smallest_major_size * full_width_size_per_major];
			_dump_data(data_dump, std::make_index_sequence<smallest_major_size>());

			// Moved relevant dumped data to the output Matrix
			using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<_out_mat>;
			using out_column_indices = typename out_indices::column_index_sequence;
			using out_row_indices = typename out_indices::row_index_sequence;
			return _store_to_new_matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(data_dump, out_column_indices(), out_row_indices());
		}

		template<typename OutT_ = value_type, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline auto Store() const
			-> EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_>
		{
			return Store<num_columns, num_rows, OutT_, OutColumnMajor_>();
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
