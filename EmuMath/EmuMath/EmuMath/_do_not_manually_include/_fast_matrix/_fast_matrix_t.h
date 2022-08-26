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
		static constexpr std::size_t register_width = major_vector_type::register_width;
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

		/// <summary>
		/// <para> Constructor for a FastMatrix which will load or set its registers via respective data within the passed Matrix. </para>
		/// <para> 
		///		Optimised loads will be used where possible if the input Matrix has the same `stored_type` as this FastMatrix type's `value_type`, 
		///		and it shares the same major storage order. Otherwise, only sets will be used.
		/// </para>
		/// </summary>
		/// <param name="scalar_matrix_">Normal EmuMath Matrix to load or set the new FastMatrix's registers via.</param>
		template<class Matrix_>
		requires EmuConcepts::EmuMatrix<Matrix_>
		explicit constexpr inline FastMatrix(Matrix_&& scalar_matrix_) :
			major_vectors(EmuMath::Helpers::fast_matrix_make_majors_from_scalar_matrix<this_type>(std::forward<Matrix_>(scalar_matrix_), major_index_sequence()))
		{
		}

		template
		<
			EmuConcepts::EmuFastVector...MajorVectors_,
			typename = std::enable_if
			<
				sizeof...(MajorVectors_) == num_major_elements &&
				(... && std::is_same_v<typename EmuCore::TMP::remove_ref_cv<MajorVectors_>::type, major_vector_type>)
			>
		>
		explicit constexpr inline FastMatrix(MajorVectors_&&...major_vectors_) :
			major_vectors({std::forward<MajorVectors_>(major_vectors_)...})
		{
		}
#pragma endregion

#pragma region GETTERS
	public:
		/// <summary>
		/// <para> Retrieves a reference to this FastMatrix's major Vector at the provided index. </para>
		/// <para> If this FastMatrix is column-major, this retrieves the column at the specified index. </para>
		/// <para> If this FastMatrix is row-major, this retrieves the row at the specified index. </para>
		/// </summary>
		/// <returns>Reference to this FastMatrix's major Vector at the specified index.</returns>
		template<std::size_t MajorIndex_>
		[[nodiscard]] constexpr inline major_vector_type& GetMajor()
		{
			if constexpr (MajorIndex_ < num_major_elements)
			{
				return major_vectors[MajorIndex_];
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<MajorIndex_>(),
					"Attempted to retrieve a Major Vector from an EmuMath Fast Matrix, but the provided MajorIndex_ exceeds the number of Major Vectors that the FastMatrix contains."
				);
			}
		}

		template<std::size_t MajorIndex_>
		[[nodiscard]] constexpr inline const major_vector_type& GetMajor() const
		{
			return const_cast<this_type*>(this)->template GetMajor<MajorIndex_>();
		}

		/// <summary>
		/// <para> Stores the data of this FastMatrix to a normal EmuMath Matrix of the specified type. </para>
		/// <para> 
		///		All arguments for the output Matrix type may be omitted, in which case they will match that of this FastMatrix 
		///		(except for `T_`, which will instead be this FastMatrix's `value_type`).
		/// </para>
		/// <para> Indices that this FastMatrix does not encapsulate will be zeroed. </para>
		/// <para> This may not be used to output references. </para>
		/// </summary>
		/// <returns>EmuMath Matrix of the specified type containing respective data of this Matrix's registers.</returns>
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

		/// <summary>
		/// <para> Stores the data of this FastMatrix to the passed normal EmuMath Matrix. </para>
		/// <para>
		///		Where possible, data will be stored directly to contiguous chunks of the output Matrix without an intermediate. 
		///		This requires that the output Matrix's `stored_type` is the same as this FastMatrix's `value_type`, 
		///		and that is shares the same major storage order.
		/// </para>
		/// <para> Indices that this FastMatrix does not encapsulate will be zeroed. </para>
		/// </summary>
		/// <param name="out_matrix_">EmuMath Matrix reference to output respective data to.</param>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		[[nodiscard]] constexpr inline void Store(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_) const
		{
			return EmuMath::Helpers::fast_matrix_store(*this, out_matrix_);
		}
#pragma endregion

#pragma region CONST_ARITHMETIC_FUNCS
	public:
		template<class Rhs_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
		[[nodiscard]] constexpr inline auto _naive_multiply_impl_rm_cm
		(
			Rhs_&& rhs_,
			std::index_sequence<ColumnIndices_...>,
			std::index_sequence<RowIndices_...>
		) const
		{
			return this_type
			(
				EmuMath::Matrix<num_columns, num_rows, value_type, true>
				(
					major_vectors[ColumnIndices_].Dot(rhs_.major_vectors[RowIndices_]).template at<0>()...
				)
			);
		}

		template<class RhsMatrix_>
		requires EmuConcepts::EmuFastMatrixMultPair<this_type, RhsMatrix_>
		[[nodiscard]] constexpr inline auto Multiply(RhsMatrix_&& rhs_matrix_) const
			-> auto
		{
			return EmuMath::Helpers::fast_matrix_multiply(*this, std::forward<RhsMatrix_>(rhs_matrix_));
		}
#pragma endregion

#pragma region DATA
	public:
		/// <summary>
		/// <para> Array of SIMD-optimised Vectors, each representing a single major chunk within this Matrix. </para>
		/// <para> If this FastMatrix is column-major, this is an array of its columns. </para>
		/// <para> If this FastMatrix is row-major, this is an array of its rows. </para>
		/// </summary>
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
