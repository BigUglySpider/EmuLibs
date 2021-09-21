#ifndef EMU_MATH_MATRIX_T_H_INC_
#define EMU_MATH_MATRIX_T_H_INC_

#include "MatrixHelpers.h"
#include "MatrixInfo.h"

namespace EmuMath
{
	/// <summary>
	/// <para> Template matrix type used for arbitrarily sized matrices containing any arithmetic type, stored in order of columns or rows. </para>
	/// <para>
	///		NOTE: The ColumnMajor_ bool affects only the memory layout of a matrix. 
	///		Positions of elements, such as when generating transformation matrices, will always be at the same column and row indices regardless of major order. 
	/// </para>
	/// <para>
	///		All default arguments where a matrix is provided will use that matrix's major order. 
	///		Otherwise, if no matrix is available to copy, the default argument will always be for column major (true).
	/// </para>
	/// </summary>
	/// <typeparam name="T_"></typeparam>
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_ = true>
	struct Matrix
	{
	private:
		// Formed using decltype on a constructor call in order to trigger an assertion before doing anything further
		using _matrix_assert = decltype(EmuMath::_underlying_components::MatrixAssert<NumColumns_, NumRows_, T_, ColumnMajor_>());

	public:
		/// <summary> Underlying default MatrixInfo regarding this matrix's static information, including common type aliases. </summary>
		using matrix_info = EmuMath::_underlying_components::MatrixInfo<NumColumns_, NumRows_, T_, ColumnMajor_>;

		/// <summary> The number of columns contained in this matrix. </summary>
		static constexpr std::size_t num_columns = matrix_info::num_columns;
		/// <summary> The number of rows contained in this matrix. </summary>
		static constexpr std::size_t num_rows = matrix_info::num_rows;
		/// <summary> The total number of elements contained in this matrix. This is not the memory-size of this matrix acquired via sizeof. </summary>
		static constexpr std::size_t size = matrix_info::size;
		/// <summary> Boolean indicating if this matrix's elements are stored contiguously as columns. Mutually exclusive with is_row_major. </summary>
		static constexpr bool is_column_major = matrix_info::is_column_major;
		/// <summary> Boolean indicating if this matrix's elements are stored contiguously as rows. Mutually exclusive with is_column_major. </summary>
		static constexpr bool is_row_major = matrix_info::is_row_major;
		/// <summary> Boolean indicating if this is a matrix with an equal number of columns and rows. </summary>
		static constexpr bool is_square = matrix_info::is_square;

		/// <summary> The number of major elements in this matrix (i.e. num_columns if column-major, or num_rows if row-major). </summary>
		static constexpr std::size_t num_major_elements = matrix_info::num_major_elements;
		/// <summary> The number of non-major elements in this matrix (i.e. num_rows if column-major, or num_columns if row-major). </summary>
		static constexpr std::size_t num_non_major_elements = matrix_info::num_non_major_elements;

		/// <summary> The type contained within this matrix. </summary>
		using contained_type = typename matrix_info::contained_type;
		/// <summary> Boolean indicating if this matrix contains reference wrapping types. </summary>
		static constexpr bool contains_reference_wrappers = matrix_info::contains_reference_wrappers;
		/// <summary> The raw value_type within this matrix before its const qualifier is forcibly removed. </summary>
		using raw_value_type = typename matrix_info::raw_value_type;
		/// <summary> Value type of the items stored within this matrix, without const qualifiers where applicable. </summary>
		using value_type = typename matrix_info::value_type;
		/// <summary> The preferred floating point type for this matrix. Float if this matrix contains non-floating-point types, otherwise matches value_type. </summary>
		using preferred_floating_point = typename matrix_info::preferred_floating_point;
		/// <summary> Boolean indicating if the reference wrappers within this matrix contain constant references. Always false if contains_reference_wrappers is false. </summary>
		static constexpr bool contains_const_reference_wrappers = matrix_info::contains_const_reference_wrappers;
		/// <summary> Boolean indicating if the reference wrappers within this matrix contain non-constant references. Always false if contains_reference_wrappers is false. </summary>
		static constexpr bool contains_non_const_reference_wrappers = matrix_info::contains_non_const_reference_wrappers;

		/// <summary> Boolean indcating if this matrix's values are integral. </summary>
		static constexpr bool has_integral_elements = matrix_info::has_integral_elements;
		/// <summary> Boolean indcating if this matrix's values are floating-points. </summary>
		static constexpr bool has_floating_point_elements = matrix_info::has_floating_point_elements;
		/// <summary> Boolean indicating if this matrix's values are constant. </summary>
		static constexpr bool has_const_values = matrix_info::has_const_values;

		/// <summary> The type used to store this matrix's underlying data. Effectively a vector of vectors. </summary>
		using data_storage_type = typename matrix_info::data_storage_type;

		/// <summary> Type used to randomly access a row referencing this matrix. </summary>
		using random_access_row = typename matrix_info::random_access_row;
		/// <summary> Type used to randomly access a column referencing this matrix. </summary>
		using random_access_column = typename matrix_info::random_access_column;
		/// <summary> Type used to randomly access a row referencing this matrix with constant constraints. </summary>
		using const_random_access_row = typename matrix_info::const_random_access_row;
		/// <summary> Type used to randomly access a column referencing this matrix with constant constraints. </summary>
		using const_random_access_column = typename matrix_info::const_random_access_column;

		/// <summary> This matrix type. </summary>
		using this_type = EmuMath::Matrix<num_columns, num_rows, contained_type, is_column_major>;
		/// <summary> Type used to receive a copy of this matrix. This is the same as this_type normally, but will remove qualifiers and references where applicable. </summary>
		using copy_type = EmuMath::Matrix<num_columns, num_rows, value_type, is_column_major>;
		/// <summary> Type used to receive a copy of this matrix. This is the same as this_type normally, but with references removed if it is a reference wrapper. </summary>
		using raw_copy_type = EmuMath::Matrix<num_columns, num_rows, raw_value_type, is_column_major>;

#pragma region CONSTRUCTORS
		constexpr Matrix() : data_()
		{
		}
		constexpr Matrix(data_storage_type& toCopy_) : data_(toCopy_)
		{
		}
		constexpr Matrix(const data_storage_type& toCopy_) : data_(toCopy_)
		{
		}
		constexpr Matrix(this_type& toCopy_) : data_(toCopy_.data_)
		{
		}
		template<typename = std::enable_if_t<!contains_non_const_reference_wrappers>>
		constexpr Matrix(const this_type& toCopy_) : data_(toCopy_.data_)
		{
		}
		template<std::size_t...Sizes_, typename...Ts_>
		constexpr Matrix(EmuMath::Vector<Sizes_, Ts_>&&...major_vectors_) : data_(std::forward<EmuMath::Vector<Sizes_, Ts_>>(major_vectors_)...)
		{
			static_assert(std::is_constructible_v<data_storage_type, EmuMath::Vector<Sizes_, Ts_>...>, "Attempted to construct an EmuMath matrix via a template constructor, using Vector data which cannot be used to construct the matrix's underlying data.");
		}
		/// <summary>
		/// <para> Template constructor to create this matrix type via scalar arguments. </para>
		/// <para> Arguments are taken in contiguous order within this matrix. </para>
		/// <para>
		///		Passed arguments must be valid types for constructing this matrix's contained_type, 
		///		and the number of arguments must be equal to the total number of elements within this matrix.
		/// </para>
		/// </summary>
		/// <typeparam name="ScalarArgs_">Types of scalars to form this matrix with. Must be valid individual types to construct this matrix's contained_type.</typeparam>
		/// <param name="contiguous_scalar_args_">Scalars to form this matrix with. Must be valid individual types to construct this matrix's contained_type.</param>
		template
		<
			typename...ScalarArgs_,
			typename = std::enable_if_t
			<
				EmuCore::TMPHelpers::are_all_comparisons_true<std::is_constructible, contained_type, ScalarArgs_...>::value &&
				sizeof...(ScalarArgs_) == size
			>
		>
		constexpr Matrix(ScalarArgs_&&...contiguous_scalar_args_) : Matrix()
		{
			if constexpr (sizeof...(ScalarArgs_) == size)
			{
				if constexpr (EmuCore::TMPHelpers::are_all_comparisons_true<std::is_constructible, contained_type, ScalarArgs_...>::value)
				{
					EmuMath::Helpers::_underlying_matrix_funcs::_matrix_maker<this_type>()(*this, std::make_index_sequence<size>(), contiguous_scalar_args_...);
				}
				else
				{
					static_assert(false, "Attempted to construct an EmuMath matrix using scalar arguments, but at least one of the provided arguments could not be used to construct an element within the matrix.");
				}
			}
			else
			{
				static_assert(false, "Attempted to construct an EmuMath matrix using scalar arguments, but the provided number of arguments did not match the number of elements within the matrix.");
			}
		}
#pragma endregion

#pragma region RANDOM_ACCESS
		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		[[nodiscard]] constexpr inline raw_value_type& at()
		{
			if constexpr (_valid_static_indices<ColumnIndex_, RowIndex_>())
			{
				return _get_index<ColumnIndex_, RowIndex_>();
			}
			else
			{
				static_assert(false, "Failed to retrieve an EmuMath matrix element due to invalid indices being provided.");
			}
		}
		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		[[nodiscard]] constexpr inline const raw_value_type& at() const
		{
			if constexpr (_valid_static_indices<ColumnIndex_, RowIndex_>())
			{
				return _get_index<ColumnIndex_, RowIndex_>();
			}
			else
			{
				static_assert(false, "Failed to retrieve an EmuMath matrix element due to invalid indices being provided.");
			}
		}
		[[nodiscard]] constexpr inline raw_value_type& at(const std::size_t columnIndex_, const std::size_t rowIndex_)
		{
			return _get_index(columnIndex_, rowIndex_);
		}
		[[nodiscard]] constexpr inline const raw_value_type& at(const std::size_t columnIndex_, const std::size_t rowIndex_) const
		{
			return _get_index(columnIndex_, rowIndex_);
		}

		template<std::size_t MajorIndex_>
		[[nodiscard]] constexpr inline EmuMath::Vector<num_non_major_elements, contained_type>& at()
		{
			return this->template GetMajor<MajorIndex_>();
		}
		template<std::size_t MajorIndex_>
		[[nodiscard]] constexpr inline const EmuMath::Vector<num_non_major_elements, contained_type>& at() const
		{
			return this->template GetMajor<MajorIndex_>();
		}
		[[nodiscard]] constexpr inline EmuMath::Vector<num_non_major_elements, contained_type>& at(const std::size_t majorIndex_)
		{
			return this->GetMajor(majorIndex_);
		}
		[[nodiscard]] constexpr inline const EmuMath::Vector<num_non_major_elements, contained_type>& at(const std::size_t majorIndex_) const
		{
			return this->GetMajor(majorIndex_);
		}

		[[nodiscard]] constexpr inline EmuMath::Vector<num_non_major_elements, contained_type>& operator[](const std::size_t majorIndex_)
		{
			return this->at(majorIndex_);
		}
		[[nodiscard]] constexpr inline const EmuMath::Vector<num_non_major_elements, contained_type>& operator[](const std::size_t majorIndex_) const
		{
			return this->at(majorIndex_);
		}

		[[nodiscard]] constexpr inline raw_value_type& operator()(const std::size_t columnIndex_, const std::size_t rowIndex_)
		{
			return this->at(columnIndex_, rowIndex_);
		}
		[[nodiscard]] constexpr inline const raw_value_type& operator()(const std::size_t columnIndex_, const std::size_t rowIndex_) const
		{
			return this->at(columnIndex_, rowIndex_);
		}

		template<std::size_t MajorIndex_>
		constexpr inline EmuMath::Vector<num_non_major_elements, contained_type>& GetMajor()
		{
			if constexpr (MajorIndex_ < num_major_elements)
			{
				return data_.template at<MajorIndex_>();
			}
			else
			{
				static_assert(false, "Attempted to access a major element within an EmuMath matrix using an invalid MajorIndex_.");
			}
		}
		template<std::size_t MajorIndex_>
		constexpr inline const EmuMath::Vector<num_non_major_elements, contained_type>& GetMajor() const
		{
			if constexpr (MajorIndex_ < num_major_elements)
			{
				return data_.template at<MajorIndex_>();
			}
			else
			{
				static_assert(false, "Attempted to access a major element within an EmuMath matrix using an invalid MajorIndex_.");
			}
		}

		constexpr inline EmuMath::Vector<num_non_major_elements, contained_type>& GetMajor(const std::size_t majorIndex_)
		{
			return data_.at(majorIndex_);
		}
		constexpr inline const EmuMath::Vector<num_non_major_elements, contained_type>& GetMajor(const std::size_t majorIndex_) const
		{
			return data_.at(majorIndex_);
		}

		template<std::size_t RowIndex_>
		constexpr inline random_access_row GetRow()
		{
			return EmuMath::Helpers::MatrixGetRow<RowIndex_, this_type>(*this);
		}
		template<std::size_t RowIndex_>
		constexpr inline const_random_access_row GetRow() const
		{
			return EmuMath::Helpers::MatrixGetRow<RowIndex_, this_type>(*this);
		}
		template<std::size_t RowIndex_>
		constexpr inline const_random_access_row GetRowConst() const
		{
			return EmuMath::Helpers::MatrixGetRow<RowIndex_, this_type>(*this);
		}

		template<std::size_t ColumnIndex_>
		constexpr inline random_access_column GetColumn()
		{
			return EmuMath::Helpers::MatrixGetColumn<ColumnIndex_, this_type>(*this);
		}
		template<std::size_t ColumnIndex_>
		constexpr inline const_random_access_column GetColumn() const
		{
			return EmuMath::Helpers::MatrixGetColumn<ColumnIndex_, this_type>(*this);
		}
		template<std::size_t ColumnIndex_>
		constexpr inline const_random_access_column GetColumnConst() const
		{
			return EmuMath::Helpers::MatrixGetColumn<ColumnIndex_, this_type>(*this);
		}
#pragma endregion

#pragma region CONST_OPERATORS
		template<bool TestAllIndices_ = false, std::size_t LhsNumColumns_, std::size_t RhsNumColumns_, typename rhs_contained_type, bool RhsColumnMajor_>
		constexpr inline bool operator==(const EmuMath::Matrix<LhsNumColumns_, RhsNumColumns_, rhs_contained_type, RhsColumnMajor_>& rhs_) const
		{
			return EmuMath::Helpers::MatrixCmpEqual<TestAllIndices_, this_type, EmuMath::Matrix<LhsNumColumns_, RhsNumColumns_, rhs_contained_type, RhsColumnMajor_>>
			(
				*this,
				rhs_
			);
		}

		template<bool TestAllIndices_ = false, std::size_t LhsNumColumns_, std::size_t RhsNumColumns_, typename rhs_contained_type, bool RhsColumnMajor_>
		constexpr inline bool operator!=(const EmuMath::Matrix<LhsNumColumns_, RhsNumColumns_, rhs_contained_type, RhsColumnMajor_>& rhs_) const
		{
			return EmuMath::Helpers::MatrixCmpNotEqual<TestAllIndices_, this_type, EmuMath::Matrix<LhsNumColumns_, RhsNumColumns_, rhs_contained_type, RhsColumnMajor_>>
			(
				*this,
				rhs_
			);
		}

		template<typename Rhs_>
		constexpr inline copy_type operator+(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixAdd<num_columns, num_rows, value_type, is_column_major, this_type, Rhs_>(*this, rhs_);
		}
		constexpr inline copy_type operator+() const
		{
			return EmuMath::Helpers::MatrixAs<num_columns, num_rows, value_type, is_column_major, this_type>(*this);
		}

		template<typename Rhs_>
		constexpr inline copy_type operator-(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixSubtract<num_columns, num_rows, value_type, is_column_major, this_type, Rhs_>(*this, rhs_);
		}
		constexpr inline copy_type operator-() const
		{
			return EmuMath::Helpers::MatrixNegate<num_columns, num_rows, value_type, is_column_major, this_type>(*this);
		}

		template<typename Rhs_>
		constexpr inline auto operator*(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixMultiply(*this, rhs_);
		}

		template<typename Rhs_>
		constexpr inline copy_type operator/(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixDivideBasic<num_columns, num_rows, value_type, is_column_major, this_type, Rhs_>(*this, rhs_);
		}

		template<typename Rhs_>
		constexpr inline copy_type operator%(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixModBasic<num_columns, num_rows, value_type, is_column_major, this_type, Rhs_>(*this, rhs_);
		}

		template<typename Rhs_>
		constexpr inline copy_type operator&(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixAnd<num_columns, num_rows, value_type, is_column_major, this_type, Rhs_>(*this, rhs_);
		}

		template<typename Rhs_>
		constexpr inline copy_type operator|(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixOr<num_columns, num_rows, value_type, is_column_major, this_type, Rhs_>(*this, rhs_);
		}

		template<typename Rhs_>
		constexpr inline copy_type operator^(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixXor<num_columns, num_rows, value_type, is_column_major, this_type, Rhs_>(*this, rhs_);
		}

		template<typename Shifts_>
		constexpr inline copy_type operator<<(const Shifts_& num_shifts_) const
		{
			return EmuMath::Helpers::MatrixShiftLeft<num_columns, num_rows, value_type, is_column_major, this_type, Shifts_>(*this, num_shifts_);
		}

		template<typename Shifts_>
		constexpr inline copy_type operator>>(const Shifts_& num_shifts_) const
		{
			return EmuMath::Helpers::MatrixShiftRight<num_columns, num_rows, value_type, is_column_major, this_type, Shifts_>(*this, num_shifts_);
		}

		constexpr inline copy_type operator~() const
		{
			return EmuMath::Helpers::MatrixNot<num_columns, num_rows, value_type, is_column_major, this_type>(*this);
		}
#pragma endregion

#pragma region NON_CONST_OPERATORS
		template<typename Rhs_>
		constexpr inline this_type& operator=(const Rhs_& to_copy_)
		{
			return EmuMath::Helpers::MatrixCopy(*this, to_copy_);
		}

		template<typename Rhs_>
		constexpr inline this_type& operator+=(const Rhs_& rhs_)
		{
			return this->operator=(this->operator+(rhs_));
		}

		template<typename Rhs_>
		constexpr inline this_type& operator-=(const Rhs_& rhs_)
		{
			return this->operator=(this->operator-(rhs_));
		}

		template
		<
			typename Rhs_,
			typename = std::enable_if_t<EmuMath::TMP::is_matching_size_matrix_multiply_result_v<this_type, Rhs_>>
		>
		constexpr inline this_type& operator*=(const Rhs_& rhs_)
		{
			return this->operator=(this->operator*(rhs_));
		}

		template<typename Rhs_>
		constexpr inline this_type& operator/=(const Rhs_& rhs_)
		{
			return this->operator=(this->operator/(rhs_));
		}

		template<typename Rhs_>
		constexpr inline this_type& operator%=(const Rhs_& rhs_)
		{
			return this->operator=(this->operator%(rhs_));
		}

		template<typename Rhs_>
		constexpr inline this_type& operator&=(const Rhs_& rhs_)
		{
			return this->operator=(this->operator&(rhs_));
		}

		template<typename Rhs_>
		constexpr inline this_type& operator|=(const Rhs_& rhs_)
		{
			return this->operator=(this->operator|(rhs_));
		}

		template<typename Rhs_>
		constexpr inline this_type& operator^=(const Rhs_& rhs_)
		{
			return this->operator=(this->operator^(rhs_));
		}

		template<typename Shifts_>
		constexpr inline this_type& operator<<=(const Shifts_& num_shifts_)
		{
			return this->operator=(this->operator<<(num_shifts_));
		}

		template<typename Shifts_>
		constexpr inline this_type& operator>>=(const Shifts_& num_shifts_)
		{
			return this->operator=(this->operator>>(num_shifts_));
		}
#pragma endregion

#pragma region MATRIX_OPERATIONS
		/// <summary>
		/// <para> Transposes this matrix, effectively turning columns into rows and vice versa. </para>
		/// <para> The output matrix will always be of dimensions [Y, X], where X=this_matrix::num_columns, and Y=this_matrix::num_rows. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output transpose matrix.</typeparam>
		/// <returns>Tranposed form of this matrix.</returns>
		template<typename out_contained_type = value_type, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, OutColumnMajor_, this_type>::type Transpose() const
		{
			return EmuMath::Helpers::MatrixTranspose<out_contained_type, OutColumnMajor_, this_type>(*this);
		}

		/// <summary>
		/// <para> Calculates the trace of this matrix (i.e. the sum of all diagonal elements from the top-left to the bottom right). </para>
		/// <para> The trace is only defined for a square matrix, and as such this function may only be validly executed on square matrices. </para>
		/// </summary>
		/// <typeparam name="OutT_">Type to output the trace as.</typeparam>
		/// <returns>Trace of this matrix, represented as the provided OutT_.</returns>
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline OutT_ Trace() const
		{
			return EmuMath::Helpers::MatrixTrace<OutT_, this_type>(*this);
		}

		/// <summary>
		/// <para> Retrieves a smaller matrix from within this matrix, which is formed of all elements excluding those in the provided row and column. </para>
		/// <para> This will always yield a matrix of size [X-1, Y-1], where X=this_matrix::num_columns, and Y=this_matrix::num_rows. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output submatrix.</typeparam>
		/// <returns>Copy of the submatrix within the this matrix, formed of all elements excluding those in the provided column or row indices.</returns>
		template<std::size_t ExcludeColumn_, std::size_t ExcludeRow_, typename out_contained_type = value_type, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<out_contained_type, OutColumnMajor_, this_type>::type
		ExclusiveSubmatrix()
		{
			return EmuMath::Helpers::MatrixExclusiveSubmatrix<ExcludeColumn_, ExcludeRow_, out_contained_type, OutColumnMajor_, this_type>(*this);
		}
		template<std::size_t ExcludeColumn_, std::size_t ExcludeRow_, typename out_contained_type = value_type, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<out_contained_type, OutColumnMajor_, this_type>::type
		ExclusiveSubmatrix() const
		{
			return EmuMath::Helpers::MatrixExclusiveSubmatrix<ExcludeColumn_, ExcludeRow_, out_contained_type, OutColumnMajor_, const this_type>(*this);
		}

		/// <summary>
		/// <para> Calculates the determinant of this matrix using Laplace Expansion. </para>
		/// <para> NOTE: Laplace Expansion grows exponentially more expensive as the size of a matrix increases. </para>
		/// </summary>
		/// <typeparam name="OutDet_">Type to output the passed matrix's determinant as.</typeparam>
		/// <returns>Determinant of this matrix, represented as the provided OutDet_ type.</returns>
		template<typename OutDet_ = preferred_floating_point>
		[[nodiscard]] constexpr inline OutDet_ DeterminantLaplace() const
		{
			return EmuMath::Helpers::MatrixDeterminantLaplace<OutDet_, this_type>(*this);
		}

		/// <summary>
		/// <para> Calculates the matrix of minors this matrix using Laplace Expansion. </para>
		/// <para> Each element in the output matrix may be summarised as the determinant of the submatrix which excludes said element's column and row. </para>
		/// <para> NOTE: Laplace Expansion grows exponentially more expensive as the size of a matrix increases. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output minor matrix.</typeparam>
		/// <returns>Matrix of minors to this matrix.</returns>
		template<typename out_contained_type = preferred_floating_point, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> MatrixOfMinorsLaplace() const
		{
			return EmuMath::Helpers::MatrixOfMinorsLaplace<out_contained_type, OutColumnMajor_, this_type>(*this);
		}

		/// <summary>
		/// <para> Calculates the matrix of cofactors to this matrix using Laplace Expansion. </para>
		/// <para> NOTE: Laplace Expansion grows exponentially more expensive as the size of a matrix increases. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output cofactor matrix.</typeparam>
		/// <returns>Matrix of cofactors to this matrix.</returns>
		template<typename out_contained_type = preferred_floating_point, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> MatrixOfCofactorsLaplace() const
		{
			return EmuMath::Helpers::MatrixOfCofactorsLaplace<out_contained_type, OutColumnMajor_, this_type>(*this);
		}

		/// <summary>
		/// <para> Calculates the adjugate matrix to this matrix using Laplace Expansion. </para>
		/// <para> The resulting matrix can be summarised as the transpose to this matrix's matrix of cofactors. </para>
		/// <para> NOTE: Laplace Expansion grows exponentially more expensive as the size of a matrix increases. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output adjugate matrix.</typeparam>
		/// <returns>Adjugate matrix to this matrix.</returns>
		template<typename out_contained_type = preferred_floating_point, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, OutColumnMajor_, this_type>::type AdjugateLaplace() const
		{
			return EmuMath::Helpers::MatrixAdjugateLaplace<out_contained_type, OutColumnMajor_, this_type>(*this);
		}

		/// <summary>
		/// <para> Calculates the inverse to this matrix using Laplace Expansion. May optionally output the determinant as a customisable type. </para>
		/// <para>
		///		Note that this operation does not check that the determinant is not 0. As matrices with a determinant of 0 have no inverse, it is recommended to 
		///		use the outDeterminant argument to test if the output matrix is valid if there should there be a chance that the passed matrix's determinant will be 0.
		/// </para>
		/// <para> NOTE: Laplace Expansion grows exponentially more expensive as the size of a matrix increases. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output inverse matrix.</typeparam>
		/// <typeparam name="OutDeterminant_">Type to optionally output the matrix's determinant as.</typeparam>
		/// <param name="matrix_">EmuMath matrix to find the inverse of.</param>
		/// <param name="outDeterminant_">
		///		Optional reference to output the passed matrix's determinant to. 
		///		Useful to test if the determinant is 0 in cases where a non-invertible matrix may potentially be passed.
		/// </param>
		/// <returns>Inverted version of this matrix if it is invertible. Otherwise, a matrix containing the results of multiplying its adjugate by (1/0).</returns>
		template<typename out_contained_type = preferred_floating_point, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, OutColumnMajor_, this_type>::type InverseLaplace() const
		{
			return EmuMath::Helpers::MatrixInverseLaplace<out_contained_type, OutColumnMajor_, this_type>(*this);
		}
		template<typename out_contained_type = preferred_floating_point, bool OutColumnMajor_ = is_column_major, typename OutDeterminant_>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, OutColumnMajor_, this_type>::type InverseLaplace
		(
			OutDeterminant_& out_determinant_
		) const
		{
			return EmuMath::Helpers::MatrixInverseLaplace<out_contained_type, OutColumnMajor_, this_type, OutDeterminant_>(*this, out_determinant_);
		}
#pragma endregion

#pragma region REINTERPRETATIONS
		/// <summary>
		/// <para> Casts this matrix to an alternative matrix type with the provided template arguments. </para>
		/// <para> Template arguments must be in order of the arguments provided to instantiate an EmuMath::Matrix type. </para>
		/// <para>
		///		Arguments may be omitted. Where omitted, they will be automatically matched up to this matrix's own arguments, 
		///		with the exception of out_contained_type which will be this matrix's value_type instead.
		/// </para>
		/// <para> To easily convert straight to an existing EmuMath::Matrix type, use AsMatrix instead, which takes a single EmuMath::Matrix template argument. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output matrix.</typeparam>
		/// <returns>This matrix cast to an EmuMath matrix instantiated with the provided template arguments.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> As() const
		{
			return EmuMath::Helpers::MatrixAs<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_, this_type>(*this);
		}
		template<typename out_contained_type, bool OutColumnMajor_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, OutColumnMajor_> As() const
		{
			return EmuMath::Helpers::MatrixAs<num_columns, num_rows, out_contained_type, OutColumnMajor_, this_type>(*this);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_> As() const
		{
			return EmuMath::Helpers::MatrixAs<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_, this_type>(*this);
		}
		template<bool OutColumnMajor_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, typename value_type, OutColumnMajor_> As() const
		{
			return EmuMath::Helpers::MatrixAs<num_columns, num_rows, value_type, OutColumnMajor_, this_type>(*this);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, is_column_major> As() const
		{
			return EmuMath::Helpers::MatrixAs<OutNumColumns_, OutNumRows_, out_contained_type, is_column_major, this_type>(*this);
		}
		template<typename out_contained_type>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, out_contained_type, is_column_major> As() const
		{
			return EmuMath::Helpers::MatrixAs<num_columns, num_rows, out_contained_type, is_column_major, this_type>(*this);
		}
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, value_type, is_column_major> As() const
		{
			return EmuMath::Helpers::MatrixAs<OutNumColumns_, OutNumRows_, value_type, is_column_major, this_type>(*this);
		}

		/// <summary>
		/// <para> Casts this matrix to the provided EmuMath matrix template argument type. </para>
		/// <para> 
		///		Note that reference casts are not provided by this function; 
		///		output will be the provided matrix's raw_copy_type, which is the same type for non-ref matrices.
		/// </para>
		/// </summary>
		/// <typeparam name="TargetCastMatrix_">Type of matrix to cast this matrix to. Note that the cast will effectively be a raw copy type.</typeparam>
		/// <returns>This matrix cast to the raw_copy_type of the passed EmuMath matrix template argument.</returns>
		template<typename TargetCastMatrix_>
		[[nodiscard]] constexpr inline typename TargetCastMatrix_::raw_copy_type AsMatrix() const
		{
			if constexpr (EmuMath::TMP::is_emu_matrix_v<TargetCastMatrix_>)
			{
				using cast_raw_copy_type = typename TargetCastMatrix_::raw_copy_type;
				return As<cast_raw_copy_type::num_columns, cast_raw_copy_type::num_rows, cast_raw_copy_type::contained_type, cast_raw_copy_type::is_column_major>();
			}
			else
			{
				static_assert(false, "Attempted to convert an EmuMath matrix to another matrix type via AsMatrix, but the provided TargetCastMatrix_ type was not an EmuMath matrix.");
			}
		}
#pragma endregion

#pragma region STATIC OPERATIONS
		/// <summary> Provides the identity matrix to this matrix type, assuming it is a square matrix. </summary>
		/// <returns>Identity to this matrix type.</returns>
		[[nodiscard]] constexpr static inline copy_type Identity()
		{
			return EmuMath::Helpers::MatrixIdentity<this_type>();
		}
#pragma endregion

	private:
		data_storage_type data_;
#pragma region SELF_HELPERS
		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		static constexpr inline bool _valid_static_indices()
		{
			if constexpr (ColumnIndex_ < num_columns)
			{
				if constexpr (RowIndex_ < num_rows)
				{
					return true;
				}
				else
				{
					static_assert(false, "Provided an invalid ColumnIndex_ when attempting to access a row of an EmuMath matrix.");
					return false;
				}
			}
			else
			{
				static_assert(false, "Provided an invalid ColumnIndex_ when attempting to access a column of an EmuMath matrix.");
				return false;
			}
		}

		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		constexpr inline raw_value_type& _get_index()
		{
			if constexpr (is_column_major)
			{
				return data_.template at<ColumnIndex_>().template at<RowIndex_>();
			}
			else
			{
				return data_.template at<RowIndex_>().template at<ColumnIndex_>();
			}
		}
		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		constexpr inline const raw_value_type& _get_index() const
		{
			if constexpr (is_column_major)
			{
				return data_.template at<ColumnIndex_>().template at<RowIndex_>();
			}
			else
			{
				return data_.template at<RowIndex_>().template at<ColumnIndex_>();
			}
		}

		constexpr inline raw_value_type& _get_index(const std::size_t columnIndex_, std::size_t rowIndex_)
		{
			if constexpr (is_column_major)
			{
				return data_.at(columnIndex_).at(rowIndex_);
			}
			else
			{
				return data_.at(rowIndex_).at(columnIndex_);
			}
		}
		constexpr inline const raw_value_type& _get_index(const std::size_t columnIndex_, std::size_t rowIndex_) const
		{
			if constexpr (is_column_major)
			{
				return data_.at(columnIndex_).at(rowIndex_);
			}
			else
			{
				return data_.at(rowIndex_).at(columnIndex_);
			}
		}

		template<std::size_t NonMajorIndex_, std::size_t MajorIndex_, typename Out_>
		constexpr inline void _assign_non_major_reference(Out_& out_)
		{
			if constexpr (MajorIndex_ < num_major_elements)
			{
				out_.template Set<MajorIndex_>(data_.template at<MajorIndex_>().template at<NonMajorIndex_>());
				_assign_non_major_reference<NonMajorIndex_, MajorIndex_ + 1, Out_>(out_);
			}
		}
		template<std::size_t NonMajorIndex_, std::size_t MajorIndex_, typename Out_>
		constexpr inline void _assign_non_major_reference(Out_& out_) const
		{
			if constexpr (MajorIndex_ < num_major_elements)
			{
				out_.template Set<MajorIndex_>(data_.template at<MajorIndex_>().template at<NonMajorIndex_>());
				_assign_non_major_reference<NonMajorIndex_, MajorIndex_ + 1, Out_>(out_);
			}
		}
#pragma endregion
	};
}

template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_, std::size_t Index_ = 0>
inline std::ostream& operator<<(std::ostream& str_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
{
	if constexpr (Index_ < EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::num_rows)
	{
		str_ << matrix_.GetRowConst<Index_>();
		if constexpr ((Index_ + 1) < EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::num_rows)
		{
			str_ << "\n";
			return operator<<<NumColumns_, NumRows_, T_, ColumnMajor_, Index_ + 1>(str_, matrix_);
		}
		else
		{
			return str_;
		}
	}
	else
	{
		return str_;
	}
}

#endif
