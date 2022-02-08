#ifndef EMU_MATH_MATRIX_T_H_INC_
#define EMU_MATH_MATRIX_T_H_INC_ 1

#include "_helpers/_all_matrix_helpers.h"
#include <exception>
#include <tuple>
#include <utility>

namespace EmuMath
{
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	struct Matrix
	{
#pragma region TMP_INFO
	public:
		template<std::size_t, std::size_t, typename, bool> friend struct Matrix;

		using this_type = Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		using matrix_info = EmuMath::TMP::common_matrix_info<NumColumns_, NumRows_, T_, ColumnMajor_>;
		static constexpr std::size_t num_columns = matrix_info::num_columns;
		static constexpr std::size_t num_rows = matrix_info::num_rows;
		static constexpr std::size_t size = matrix_info::size;
		static constexpr std::size_t num_major_elements = matrix_info::num_major_elements;
		static constexpr std::size_t num_non_major_elements = matrix_info::num_non_major_elements;
		static constexpr bool is_column_major = matrix_info::is_column_major;
		static constexpr bool is_row_major = matrix_info::is_row_major;
		static constexpr bool contains_ref = matrix_info::contains_ref;
		static constexpr bool contains_const_ref = matrix_info::contains_const_ref;
		static constexpr bool contains_non_const_ref = matrix_info::contains_non_const_ref;
		static constexpr bool is_square = num_columns == num_rows;

		/// <summary> Representation of this Matrix type flattened as an EmuMath Vector. </summary>
		using matrix_vector_type = typename matrix_info::matrix_vector_type;
		using stored_type = typename matrix_info::stored_type;
		using value_type = typename matrix_info::value_type;
		using value_type_uq = typename matrix_info::value_type_uq;
		using preferred_floating_point = typename matrix_info::preferred_floating_point;
#pragma endregion

#pragma region HELPER_STATIC_FUNCS
	public:
		/// <summary>
		/// <para> Outputs a copy of the major index of the two provided indices for this Matrix type. </para>
		/// </summary>
		/// <returns> column_index_ if this Matrix type is column-major, otherwise row_index_. </returns>
		[[nodiscard]] static constexpr inline std::size_t get_major_index(std::size_t column_index_, std::size_t row_index_)
		{
			if constexpr (is_column_major)
			{
				return column_index_;
			}
			else
			{
				return row_index_;
			}
		}

		/// <summary>
		/// <para> Outputs a copy of the non-major index of the two provided indices for this Matrix type. </para>
		/// </summary>
		/// <returns> row_index_ if this Matrix type is column-major, otherwise column_index_. </returns>
		[[nodiscard]] static constexpr inline std::size_t get_non_major_index(std::size_t column_index_, std::size_t row_index_)
		{
			if constexpr (is_column_major)
			{
				return row_index_;
			}
			else
			{
				return column_index_;
			}
		}

		[[nodiscard]] static constexpr inline std::size_t get_flattened_index(std::size_t column_index_, std::size_t row_index_)
		{
			if constexpr (is_column_major)
			{
				return (column_index_ * num_rows) + row_index_;
			}
			else
			{
				return (row_index_ * num_columns) + column_index_;
			}
		}

		[[nodiscard]] static constexpr inline std::size_t get_flattened_index(std::pair<std::size_t, std::size_t> column_row_index_pair_)
		{
			return get_flattened_index(column_row_index_pair_.first, column_row_index_pair_.second);
		}

		[[nodiscard]] static constexpr inline std::size_t get_unflattened_column_index(std::size_t flattened_index_)
		{
			if constexpr (is_column_major)
			{
				return flattened_index_ / num_rows;
			}
			else
			{
				return flattened_index_ % num_rows;
			}
		}

		[[nodiscard]] static constexpr inline std::size_t get_unflattened_row_index(std::size_t flattened_index_)
		{
			if constexpr (is_column_major)
			{
				return flattened_index_ % num_columns;
			}
			else
			{
				return flattened_index_ / num_columns;
			}
		}

		[[nodiscard]] static constexpr inline std::pair<std::size_t, std::size_t> get_unflattened_index(std::size_t flattened_index_)
		{
			return std::pair<std::size_t, std::size_t>(get_unflattened_column_index(flattened_index_), get_unflattened_row_index(flattened_index_));
		}
#pragma endregion

#pragma region CONSTRUCTION_CHECKS
	private:
		// Component of is_variadic_constructible; Assumes no reservations for provided args
		template<std::size_t ArgCount_, class...Args_>
		static constexpr inline bool _valid_variadic_scalar_construction_args()
		{
			return 
			(
				ArgCount_ == size &&
				std::is_constructible_v<matrix_vector_type, decltype(std::forward<Args_>(std::declval<Args_>()))...>
			);
		}

	public:
		static constexpr inline bool is_default_constructible()
		{
			return std::is_default_constructible_v<matrix_vector_type>;
		}

		static constexpr inline bool is_const_copy_constructible()
		{
			return std::is_constructible_v<matrix_vector_type, const matrix_vector_type&>;
		}

		static constexpr inline bool is_non_const_copy_constructible()
		{
			return std::is_constructible_v<matrix_vector_type, matrix_vector_type&>;
		}

		static constexpr inline bool is_move_constructible()
		{
			return std::is_constructible_v<matrix_vector_type, matrix_vector_type&&>;
		}

		template<class...Args_>
		static constexpr inline bool is_variadic_constructible()
		{
			constexpr std::size_t num_args_ = sizeof...(Args_);
			if constexpr (num_args_ != 0)
			{
				return
				(
					(num_args_ != 1 || !EmuMath::TMP::is_emu_matrix_v<EmuCore::TMP::first_variadic_arg_t<Args_...>>) && // Reserved for Matrix copies/moves/conversions
					(
						_valid_variadic_scalar_construction_args<num_args_, Args_...>() ||
						false // insert other potential results here
					)
				);
			}
			else
			{
				return false; // Reserved for default constructor test
			}
		}
#pragma endregion

#pragma region GENERAL_STATIC_FUNCS
	public:
		[[nodiscard]] static constexpr inline value_type_uq get_implied_zero()
		{
			return EmuMath::Helpers::matrix_get_non_contained<this_type>();
		}

		[[nodiscard]] static constexpr inline typename EmuMath::TMP::matrix_non_contained_column<this_type>::type get_implied_zero_column()
		{
			return EmuMath::Helpers::matrix_get_column_non_contained<this_type>();
		}

		[[nodiscard]] static constexpr inline typename EmuMath::TMP::matrix_non_contained_row<this_type>::type get_implied_zero_row()
		{
			return EmuMath::Helpers::matrix_get_row_non_contained<this_type>();
		}

		[[nodiscard]] static constexpr inline decltype(EmuMath::Helpers::matrix_get_major_non_contained<this_type>()) get_implied_zero_major()
		{
			return EmuMath::Helpers::matrix_get_major_non_contained<this_type>();
		}

		[[nodiscard]] static constexpr inline decltype(EmuMath::Helpers::matrix_get_non_major_non_contained<this_type>()) get_implied_zero_non_major()
		{
			return EmuMath::Helpers::matrix_get_non_major_non_contained<this_type>();
		}
#pragma endregion

#pragma region VALID_FUNCTION_ARG_CHECKS
		template<std::size_t RhsSize_>
		[[nodiscard]] static constexpr inline bool valid_vector_multiply_arg_size()
		{
			return RhsSize_ == num_rows || (RhsSize_ == num_rows - 1);
		}

		template<std::size_t RhsNumColumns_, std::size_t RhsNumRows_>
		[[nodiscard]] static constexpr inline bool valid_matrix_multiply_arg_size()
		{
			return num_columns == RhsNumRows_;
		}
#pragma endregion

#pragma region CONSTRUCTORS
	private:
		template<class...Args_>
		static constexpr inline matrix_vector_type _do_variadic_construction(Args_&&...args_)
		{
			// Visual studio does not play nice with constexpr std::size_t val = sizeof...(Args_); thanks for that :)
			if constexpr (_valid_variadic_scalar_construction_args<sizeof...(Args_), Args_...>())
			{
				return matrix_vector_type(std::forward<Args_>(args_)...);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Args_...>(),
					"False-positive variadic construction triggered for an EmuMath Matrix. This is an internal EmuMath error, as variadic construction should not have been possible with the provided arguments."
				);
			}
		}

	public:
		template<typename = std::enable_if_t<is_default_constructible()>>
		constexpr Matrix() :
			_data()
		{
		}

		template<typename = std::enable_if_t<is_const_copy_constructible()>>
		constexpr Matrix(const Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& to_const_copy) :
			_data(to_const_copy._data)
		{
		}

		template<typename = std::enable_if_t<is_non_const_copy_constructible()>>
		constexpr Matrix(Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& to_copy_) :
			_data(to_copy_._data)
		{
		}

		template<typename = std::enable_if_t<is_move_constructible()>>
		constexpr Matrix(Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&& to_move_) noexcept :
			_data(std::move(to_move_._data))
		{
		}

		template<class...Args_, typename = std::enable_if_t<is_variadic_constructible<Args_...>()>>
		constexpr Matrix(Args_&&...contiguous_element_args_) :
			_data(_do_variadic_construction(std::forward<Args_>(contiguous_element_args_)...))
		{
		}
#pragma endregion

#pragma region ACCESS
	public:
		/// <summary>
		/// <para> Accesses the element at the provided Column and Row within this Matrix, performing a compile-time validity check. </para>
		/// </summary>
		/// <returns>Reference to this Matrix's element at the provided index.</returns>
		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		[[nodiscard]] constexpr inline value_type& at()
		{
			if constexpr (ColumnIndex_ < num_columns)
			{
				if constexpr (RowIndex_ < num_rows)
				{
					return _data.template at<get_flattened_index(ColumnIndex_, RowIndex_)>();
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<std::size_t, RowIndex_>(),
						"Attempted to retrieve an index from an EmuMath Matrix within an invalid row. The valid inclusive index range for rows is 0:(num_rows - 1)"
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, ColumnIndex_>(),
					"Attempted to retrieve an index from an EmuMath Matrix within an invalid column. The valid inclusive index range for columns is 0:(num_columns - 1)"
				);
			}
		}

		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		[[nodiscard]] constexpr inline const value_type& at() const
		{
			return const_cast<this_type*>(this)->template at<ColumnIndex_, RowIndex_>();
		}

		/// <summary>
		/// <para> Accesses the element at the provided flattened, contiguous index within this Matrix, performing a compile-time validity check. </para>
		/// </summary>
		/// <returns>Reference to this Matrix's element at the provided contiguous flattened index.</returns>
		template<std::size_t FlattenedIndex_>
		[[nodiscard]] constexpr inline value_type& at()
		{
			if constexpr (FlattenedIndex_ < size)
			{
				return _data.template at<FlattenedIndex_>();
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, FlattenedIndex_>(),
					"Attempted to retrieve an index from an EmuMath Matrix using an invalid flattened index. The valid inclusive flattened index range is 0:(size - 1)."
				);
			}
		}

		template<std::size_t FlattenedIndex_>
		[[nodiscard]] constexpr inline const value_type& at() const
		{
			return const_cast<this_type*>(this)->template at<FlattenedIndex_>();
		}

		/// <summary>
		/// <para> Accesses the element at the provided Column and Row within this Matrix, performing a runtime validity check. </para>
		/// <para> Throws a std::out_of_range exception if an invalid index is provided. </para>
		/// </summary>
		/// <param name="column_index_">: Index of the column to access. Valid inclusive range is 0:(num_columns - 1).</param>
		/// <param name="row_index_">: Index of the row to access. Valid inclusive range is 0:(num_rows - 1).</param>
		/// <returns>Reference to this Matrix's element at the provided contiguous flattened index.</returns>
		[[nodiscard]] constexpr inline value_type& at(std::size_t column_index_, std::size_t row_index_)
		{
			const std::size_t flattened_index_ = get_flattened_index(column_index_, row_index_);
			if (flattened_index_ >= size)
			{
				if constexpr (EmuCore::TMP::feature_constexpr_dynamic_memory())
				{
					std::ostringstream str_;
					str_ << "Attempted to access an invalid Column + Row Index within an EmuMath Matrix.";
					str_ << "\nColumn: " << column_index_ << ", Valid Column Range (Inclusive): 0:" << (num_columns - 1);
					str_ << "\nRow: " << row_index_ << ", Valid Row Range (Inclusive): 0:" << (num_rows - 1);
					throw std::out_of_range(str_.str());
				}
				else
				{
					throw std::out_of_range("Attempted to access an invalid Column + Row Index within an EmuMath Matrix.");
				}
			}
			return _data[flattened_index_];
		}

		[[nodiscard]] constexpr inline const value_type& at(std::size_t column_index_, std::size_t row_index_) const
		{
			return const_cast<this_type*>(this)->at(column_index_, row_index_);
		}

		/// <summary>
		/// <para> Accesses the element at the provided flattened, contiguous index within this Matrix, performing a runtime validity check. </para>
		/// <para> Throws a std::out_of_range exception if an invalid index is provided. </para>
		/// </summary>
		/// <param name="flattened_index_">: Flattened, contiguous index to access. Valid inclusive range is 0:(size - 1).</param>
		/// <returns>Reference to this Matrix's element at the provided contiguous flattened index.</returns>
		[[nodiscard]] constexpr inline value_type& at(std::size_t flattened_index_)
		{
			if (flattened_index_ >= size)
			{
				if constexpr (EmuCore::TMP::feature_constexpr_dynamic_memory())
				{
					std::ostringstream str_;
					str_ << "Attempted to access an invalid Flattened Index within an EmuMath Matrix.";
					str_ << "\nIndex: " << flattened_index_ << ", Valid Flattened Index Range (Inclusive): 0:" << (size - 1);
					throw std::out_of_range(str_.str());
				}
				else
				{
					throw std::out_of_range("Attempted to access an invalid Flattened Index within an EmuMath Matrix.");
				}
			}
			return _data[flattened_index_];
		}

		/// <summary>
		/// <para> Accesses the theoretical element at the provided Column and Row within this Matrix. </para>
		/// <para> Returns this Matrix type's implied-zero if the provided index is not contained. </para>
		/// </summary>
		/// <returns>Reference to this Matrix's element at the provided index if it is contained, otherwise a newly-constructed implied-zero for this Matrix type.</returns>
		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_theoretical_get_result<ColumnIndex_, RowIndex_, this_type&>::type AtTheoretical()
		{
			return EmuMath::Helpers::matrix_get_theoretical<ColumnIndex_, RowIndex_>(*this);
		}

		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_theoretical_get_result<ColumnIndex_, RowIndex_, const this_type&>::type AtTheoretical() const
		{
			return EmuMath::Helpers::matrix_get_theoretical<ColumnIndex_, RowIndex_>(*this);
		}

		/// <summary>
		/// <para> Accesses the theoretical element at the provided contiguous flattened index within this Matrix. </para>
		/// <para> Returns this Matrix type's implied-zero if the provided index is not contained. </para>
		/// </summary>
		/// <returns>Reference to this Matrix's element at the provided index if it is contained, otherwise a newly-constructed implied-zero for this Matrix type.</returns>
		template<std::size_t FlattenedIndex_>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_flattened_theoretical_get_result<FlattenedIndex_, this_type&>::type AtTheoretical()
		{
			return EmuMath::Helpers::matrix_get_theoretical<FlattenedIndex_>(*this);
		}

		template<std::size_t FlattenedIndex_>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_flattened_theoretical_get_result<FlattenedIndex_, const this_type&>::type AtTheoretical() const
		{
			return EmuMath::Helpers::matrix_get_theoretical<FlattenedIndex_>(*this);
		}

		/// <summary>
		/// <para> Outputs a contiguous pointer to this Matrix's stored data, with an optional offset which performs compile-time validity checks. </para>
		/// <para> A static assertion will be triggered if this Matrix contains references or 0 elements, or if the provided offset is too large. </para>
		/// </summary>
		/// <returns>Pointer to the contiguous data stored within this Matrix.</returns>
		template<std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline stored_type* data()
		{
			if constexpr (!contains_ref)
			{
				if constexpr (size != 0)
				{
					if constexpr (Offset_ == 0)
					{
						return _data.data();
					}
					else
					{
						if constexpr (Offset_ < size)
						{
							return (_data.data()) + Offset_;
						}
						else
						{
							static_assert
							(
								EmuCore::TMP::get_false<std::size_t, Offset_>(),
								"Attempted to access a contiguous data pointer for an EmuMath Matrix using an offset which would take the pointer to memory outside of the Matrix's data."
							);
						}
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<std::size_t, size>(),
						"Attempted to access a contiguous data pointer for an EmuMath Matrix which contains no data."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<stored_type>(),
					"Attempted to access a contiguous data pointer for an EmuMath Matrix which contains references. As referenced data is not guaranteed to be contiguous, this behaviour is prohibited."
				);
			}
		}

		template<std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline const stored_type* data() const
		{
			return const_cast<this_type*>(this)->template data<Offset_>();
		}
#pragma endregion

#pragma region ASSIGNMENT_OPERATORS
	public:
		constexpr inline this_type& operator=(this_type&& to_move_) noexcept
		{
			EmuMath::Helpers::matrix_copy(*this, std::forward<this_type>(to_move_));
			return *this;
		}

		template
		<
			std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
			typename = std::enable_if_t
			<
				EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&>()
			>
		>
		constexpr inline this_type& operator=(EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& to_copy_)
		{
			EmuMath::Helpers::matrix_copy(*this, to_copy_);
			return *this;
		}

		template
		<
			std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
			typename = std::enable_if_t
			<
				EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&>()
			>
		>
		constexpr inline this_type& operator=(const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& to_copy_)
		{
			EmuMath::Helpers::matrix_copy(*this, to_copy_);
			return *this;
		}

		template
		<
			std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
			typename = std::enable_if_t
			<
				EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>() &&
				!std::is_same_v<this_type, EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>
			>
		>
		constexpr inline this_type& operator=(EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&& to_move_copy_)
		{
			EmuMath::Helpers::matrix_copy
			(
				*this,
				std::forward<EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>(to_move_copy_)
			);
			return *this;
		}

		template
		<
			std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
			typename = std::enable_if_t
			<
				EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>()
			>
		>
		constexpr inline this_type& operator=(const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&& to_move_copy_)
		{
			EmuMath::Helpers::matrix_copy
			(
				*this,
				std::forward<EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>(to_move_copy_)
			);
			return *this;
		}
#pragma endregion

#pragma region CONST_ARITHMETIC_OPERATORS
	public:
		// BASIC ARITHMETIC OPERATOR+
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> operator+(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_add<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> operator+(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_add<num_columns, num_rows, OutT_, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> operator+(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_add<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		// BASIC ARITHMETIC OPERATOR-
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> operator-(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_subtract<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> operator-(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_subtract<num_columns, num_rows, OutT_, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> operator-(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_subtract<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		// BASIC ARITHMETIC OPERATOR/
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> operator/(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_divide<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> operator/(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_divide<num_columns, num_rows, OutT_, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> operator/(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_divide<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		// BASIC ARITHMETIC OPERATOR%
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> operator%(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_mod<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> operator%(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_mod<num_columns, num_rows, OutT_, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> operator%(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_mod<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		// ADAPTIVE ARITHMETIC OPERATOR* : UNSPECIALISED FALLBACK TO BASIC_MULTIPLY
		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_, typename = std::enable_if_t<!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>()>>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> operator*(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_multiply<OutT_, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<bool OutColumnMajor_ = is_column_major, class Rhs_, typename = std::enable_if_t<!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>()>>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> operator*(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_multiply<value_type_uq, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		// ADAPTIVE ARITHMETIC OPERATOR*: SPECIALISED VECTOR MULTIPLY
		template
		<
			typename OutT_,
			bool OutColumnMajor_ = is_column_major,
			typename RhsT_,
			std::size_t RhsSize_,
			typename = std::enable_if_t<valid_vector_multiply_arg_size<RhsSize_>()>
		>
		[[nodiscard]] constexpr inline EmuMath::Vector<RhsSize_, OutT_> operator*(const EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_) const
		{
			return EmuMath::Helpers::matrix_multiply<OutT_, OutColumnMajor_>(*this, rhs_vector_);
		}

		template
		<
			bool OutColumnMajor_ = is_column_major,
			typename RhsT_,
			std::size_t RhsSize_,
			typename = std::enable_if_t<valid_vector_multiply_arg_size<RhsSize_>()>
		>
		[[nodiscard]] constexpr inline EmuMath::Vector<RhsSize_, typename EmuMath::Vector<RhsSize_, RhsT_>::preferred_floating_point> operator*
		(
			const EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_
		) const
		{
			using rhs_fp = typename EmuMath::Vector<RhsSize_, RhsT_>::preferred_floating_point;
			return EmuMath::Helpers::matrix_multiply<rhs_fp, OutColumnMajor_>(*this, rhs_vector_);
		}

		// ADAPTIVE ARITHMETIC OPERATOR*: SPECIALISED MATRIX MULTIPLY
		template
		<
			typename OutT_,
			bool OutColumnMajor_ = is_column_major,
			typename RhsT_,
			std::size_t RhsNumColumns_,
			std::size_t RhsNumRows_,
			bool RhsColumnMajor_,
			typename = std::enable_if_t<valid_matrix_multiply_arg_size<RhsNumColumns_, RhsNumRows_>()>
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<RhsNumColumns_, num_rows, OutT_, OutColumnMajor_> operator*
		(
			const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_
		)
		{
			return EmuMath::Helpers::matrix_multiply<OutT_, OutColumnMajor_>(*this, rhs_matrix_);
		}

		template
		<
			bool OutColumnMajor_ = is_column_major,
			typename RhsT_,
			std::size_t RhsNumColumns_,
			std::size_t RhsNumRows_,
			bool RhsColumnMajor_,
			typename = std::enable_if_t<valid_matrix_multiply_arg_size<RhsNumColumns_, RhsNumRows_>()>
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<RhsNumColumns_, num_rows, preferred_floating_point, OutColumnMajor_> operator*
		(
			const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_
		)
		{
			return EmuMath::Helpers::matrix_multiply<preferred_floating_point, OutColumnMajor_>(*this, rhs_matrix_);
		}
#pragma endregion

#pragma region ARITHMETIC_ASSIGN_OPERATORS
		template<bool ColumnMajorOrder_ = is_column_major, class Rhs_>
		constexpr inline this_type& operator+=(Rhs_&& rhs_)
		{
			EmuMath::Helpers::matrix_add_assign<ColumnMajorOrder_>(*this, std::forward<Rhs_>(rhs_));
			return *this;
		}

		template<bool ColumnMajorOrder_ = is_column_major, class Rhs_>
		constexpr inline this_type& operator-=(Rhs_&& rhs_)
		{
			EmuMath::Helpers::matrix_subtract_assign<ColumnMajorOrder_>(*this, std::forward<Rhs_>(rhs_));
			return *this;
		}

		template<bool ColumnMajorOrder_ = is_column_major, class Rhs_>
		constexpr inline this_type& operator/=(Rhs_&& rhs_)
		{
			EmuMath::Helpers::matrix_divide_assign<ColumnMajorOrder_>(*this, std::forward<Rhs_>(rhs_));
			return *this;
		}

		template<bool ColumnMajorOrder_ = is_column_major, class Rhs_>
		constexpr inline this_type& operator%=(Rhs_&& rhs_)
		{
			EmuMath::Helpers::matrix_mod_assign<ColumnMajorOrder_>(*this, std::forward<Rhs_>(rhs_));
			return *this;
		}

		template<bool ColumnMajorOrder_ = is_column_major, class Rhs_, typename = std::enable_if_t<!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>()>>
		constexpr inline this_type& operator*=(Rhs_&& rhs_)
		{
			EmuMath::Helpers::matrix_multiply_assign<ColumnMajorOrder_>(*this, std::forward<Rhs_>(rhs_));
			return *this;
		}

		template
		<
			bool ColumnMajorOrder_ = is_column_major, std::size_t RhsSize_, typename RhsT_,
			typename = std::enable_if_t<EmuMath::Helpers::is_valid_matrix_multiply_assign_rhs_vector<NumColumns_, NumRows_, T_, ColumnMajor_, RhsSize_, RhsT_>()>
		>
		constexpr inline EmuMath::Vector<RhsSize_, RhsT_>& operator*=(EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_) const
		{
			EmuMath::Helpers::matrix_multiply_assign<ColumnMajorOrder_>(*this, rhs_vector_);
			return rhs_vector_;
		}

		template
		<
			bool ColumnMajorOrder_ = is_column_major, std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
			typename = std::enable_if_t<valid_matrix_multiply_arg_size<RhsNumColumns_, RhsNumRows_>() && is_square && RhsNumColumns_ == num_columns && RhsNumRows_ == num_rows>
		>
		constexpr inline this_type& operator*=(const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_)
		{
			EmuMath::Helpers::matrix_multiply_assign<ColumnMajorOrder_>(*this, rhs_matrix_);
			return *this;
		}
#pragma endregion

#pragma region COPY_FUNCS
	public:
		/// <summary>
		/// <para> Copies the theoretical indices of the provided input Matrix to respective indices within this Matrix. </para>
		/// </summary>
		/// <param name="to_copy_">: EmuMath Matrix to copy to this Matrix.</param>
		template
		<
			std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
			typename = std::enable_if_t<EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&>()>
		>
		constexpr inline void Copy(EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& to_copy_)
		{
			EmuMath::Helpers::matrix_copy(*this, to_copy_);
		}

		template
		<
			std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
			typename = std::enable_if_t<EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&>()>
		>
		constexpr inline void Copy(const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& to_copy_)
		{
			EmuMath::Helpers::matrix_copy(*this, to_copy_);
		}

		template
		<
			std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
			typename = std::enable_if_t<EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>()>
		>
		constexpr inline void Copy(EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&& to_move_copy_)
		{
			EmuMath::Helpers::matrix_copy
			(
				*this,
				std::forward<EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>(to_move_copy_)
			);
		}

		template
		<
			std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
			typename = std::enable_if_t<EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>()>
		>
		constexpr inline void Copy(const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&& to_move_copy_)
		{
			EmuMath::Helpers::matrix_copy
			(
				*this,
				std::forward<EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>(to_move_copy_)
			);
		}
#pragma endregion

#pragma region CONST_BASIC_ARITHMETIC_FUNCS
	public:
		/// <summary>
		/// <para>
		///		Outputs the result of adding the provided rhs_ argument to this Matrix, as an EmuMath Matrix with the specified template arguments, 
		///		with size/column-major arguments matching those of this Matrix if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
		/// </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be added. </para>
		/// <para> If Rhs_ is none of the above: All index additions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of addition.</param>
		/// <returns>EmuMath Matrix containing the results of addition in respective indices.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> Add(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_add<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> Add(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_add<num_columns, num_rows, OutT_, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> Add(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_add<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		constexpr inline void Add(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::matrix_add(out_matrix_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of adding the provided rhs_ argument to this Matrix, as an EmuMath Matrix with the specified template arguments, 
		///		with size/column-major arguments matching those of this Matrix if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
		/// </para>
		/// <para> Indices within the provided range will contain results of respective addition operations. </para>
		/// <para> Indices outside of the provided range will be copies of the respective indices in this Matrix. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be added. </para>
		/// <para> If Rhs_ is none of the above: All index additions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of addition.</param>
		/// <returns>EmuMath Matrix containing the results of addition in respective indices within the provided range, and copied respective elements elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Rhs_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> AddRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_add_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> AddRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_add_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> AddRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_add_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class Rhs_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
		>
		constexpr inline void AddRange(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Rhs_&& rhs_)
		{
			EmuMath::Helpers::matrix_add_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of adding the provided lhs_matrix_ and rhs_ arguments as an EmuMath Matrix with the specified template arguments, 
		///		with size/column-major arguments matching those of lhs_matrix_ if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
		/// </para>
		/// <para> Indices within the provided range will contain results of respective addition operations. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be added. </para>
		/// <para> If Rhs_ is none of the above: All index additions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left-hand side of addition.</param>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of addition.</param>
		/// <returns>EmuMath Matrix containing the results of addition in respective indices within the provided range, and default-constructed elements elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Rhs_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> AddRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_add_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> AddRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_add_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> AddRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_add_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class Rhs_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
		>
		constexpr inline void AddRangeNoCopy(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_add_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of subtracting the provided rhs_ argument from this Matrix as an EmuMath Matrix with the specified template arguments, 
		///		with size/column-major arguments matching those of this Matrix if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
		/// </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be subtracted. </para>
		/// <para> If Rhs_ is none of the above: All index subtractions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of subtraction.</param>
		/// <returns>EmuMath Matrix containing the results of subtraction in respective indices.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> Subtract(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_subtract<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> Subtract(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_subtract<num_columns, num_rows, OutT_, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> Subtract(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_subtract<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		constexpr inline void Subtract(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::matrix_subtract(out_matrix_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of subtracting the provided rhs_ argument from this Matrix as an EmuMath Matrix with the specified template arguments, 
		///		with size/column-major arguments matching those of this Matrix if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
		/// </para>
		/// <para> Indices within the provided range will contain results of respective subtraction operations. </para>
		/// <para> Indices outside of the provided range will be copies of the respective indices in lhs_matrix_. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be subtracted. </para>
		/// <para> If Rhs_ is none of the above: All index subtractions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of subtraction.</param>
		/// <returns>EmuMath Matrix containing the results of subtraction in respective indices within the provided range, and copied respective elements elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Rhs_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> SubtractRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_subtract_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> SubtractRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_subtract_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> SubtractRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_subtract_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class Rhs_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
		>
		constexpr inline void SubtractRange(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_subtract_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of subtracting the provided rhs_ from this Matrix as an EmuMath Matrix with the specified template arguments, 
		///		with size/column-major arguments matching those of this Matrix if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
		/// </para>
		/// <para> Indices within the provided range will contain results of respective subtraction operations. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be subtracted. </para>
		/// <para> If Rhs_ is none of the above: All index subtractions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of subtraction.</param>
		/// <returns>EmuMath Matrix containing the results of subtraction in respective indices within the provided range, and default-constructed elements elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Rhs_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> SubtractRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_subtract_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> SubtractRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_subtract_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> SubtractRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_subtract_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		/// <summary>
		/// <para> Outputs the result of subtracting the provided rhs_ argument from this Matrix via the provided out_matrix_. </para>
		/// <para> Indices within the provided range will contain results of respective subtraction operations. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be subtracted. </para>
		/// <para> If Rhs_ is none of the above: All index subtractions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of subtraction.</param>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class Rhs_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
		>
		constexpr inline void SubtractRangeNoCopy(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_subtract_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of multiplying this Matrix by the provided rhs_ argument as an EmuMath Matrix with the specified template arguments, 
		///		with size/column-major arguments matching those of this Matrix if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
		/// </para>
		/// <para>
		///		This is a basic, non-standard Matrix multiplication. 
		///		If Rhs_ is a Matrix it will not perform a standard Matrix multiplication using dot products of columns and rows. 
		///		For a standard Matrix multiplication, use `Multiply` instead.
		/// </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be multiplied. </para>
		/// <para> If Rhs_ is none of the above: All index multiplications will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of basic multiplication.</param>
		/// <returns>EmuMath Matrix containing the results of basic multiplication in respective indices.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> MultiplyBasic(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_multiply_basic<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> MultiplyBasic(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_multiply_basic<num_columns, num_rows, OutT_, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> MultiplyBasic(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_multiply_basic<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		constexpr inline void MultiplyBasic(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::matrix_multiply_basic(out_matrix_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of multiplying this Matrix by the provided rhs_ argument as an EmuMath Matrix with the specified template arguments, 
		///		with size/column-major arguments matching those of this Matrix if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
		/// </para>
		/// <para>
		///		This is a basic, non-standard Matrix multiplication. 
		///		If Rhs_ is a Matrix it will not perform a standard Matrix multiplication using dot products of columns and rows. 
		///		For a standard Matrix multiplication, use `Multiply` instead. 
		///		Range-based standard variants as this function is used are not available.
		/// </para>
		/// <para> Indices within the provided range will contain results of respective multiplication operations. </para>
		/// <para> Indices outside of the provided range will be copies of the respective indices in lhs_matrix_. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be multiplied. </para>
		/// <para> If Rhs_ is none of the above: All index multiplications will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of basic multiplication.</param>
		/// <returns>EmuMath Matrix containing the results of basic multiplication in respective indices within the provided range, and copied respective elements elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Rhs_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> MultiplyBasicRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_multiply_basic_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> MultiplyBasicRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_multiply_basic_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> MultiplyBasicRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_multiply_basic_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class Rhs_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
		>
		constexpr inline void MultiplyBasicRange(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_multiply_basic_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of multiplying this Matrix by the provided rhs_ argument as an EmuMath Matrix with the specified template arguments, 
		///		with size/column-major arguments matching those of this Matrx if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
		/// </para>
		/// <para>
		///		This is a basic, non-standard Matrix multiplication. 
		///		If Rhs_ is a Matrix it will not perform a standard Matrix multiplication using dot products of columns and rows. 
		///		For a standard Matrix multiplication, use `Multiply` instead. 
		///		Range-based standard variants as this function is used are not available.
		/// </para>
		/// <para> Indices within the provided range will contain results of respective multiplication operations. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be multiplied. </para>
		/// <para> If Rhs_ is none of the above: All index multiplications will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of basic multiplication.</param>
		/// <returns>EmuMath Matrix containing the results of basic multiplication in respective indices within the provided range, and default-constructed elements elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Rhs_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> MultiplyBasicRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_multiply_basic_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> MultiplyBasicRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_multiply_basic_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> MultiplyBasicRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_multiply_basic_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		/// <summary>
		/// <para> Outputs the result of multiplying this Matrix by the provided rhs_ argument via the provided out_matrix_. </para>
		/// <para>
		///		This is a basic, non-standard Matrix multiplication. 
		///		If Rhs_ is a Matrix it will not perform a standard Matrix multiplication using dot products of columns and rows. 
		///		For a standard Matrix multiplication, use `matrix_multiply` instead. 
		///		Range-based standard variants as this function is used are not available.
		/// </para>
		/// <para> Indices within the provided range will contain results of respective multiplication operations. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be multiplied. </para>
		/// <para> If Rhs_ is none of the above: All index multiplications will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of basic multiplication.</param>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class Rhs_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
		>
		constexpr inline void MultiplyBasicRangeNoCopy(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_multiply_basic_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of dividing this Matrix by the provided rhs_ argument as an EmuMath Matrix with the specified template arguments, 
		///		with size/column-major arguments matching those of this Matrix if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
		/// </para>
		/// <para>
		///		This is a basic, non-standard Matrix division. As a standard division is mathemtically undefined, there is no alternative. 
		///		To create an effect similar to what could be considered standard division when rhs_ is a Matrix, consider multiplying this Matrix by the inverse of rhs_.
		/// </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be divided. </para>
		/// <para> If Rhs_ is none of the above: All index divisions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of basic division.</param>
		/// <returns>EmuMath Matrix containing the results of basic division in respective indices.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> Divide(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_divide<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> Divide(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_divide<num_columns, num_rows, OutT_, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> Divide(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_divide<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		constexpr inline void Divide(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::matrix_divide(out_matrix_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of dividing this Matrix by the provided rhs_ argument as an EmuMath Matrix with the specified template arguments, 
		///		with size/column-major arguments matching those of this Matrix if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
		/// </para>
		/// <para>
		///		This is a basic, non-standard Matrix division. As a standard division is mathemtically undefined, there is no alternative. 
		///		To create an effect similar to what could be considered standard division when rhs_ is a Matrix, consider multiplying lhs_matrix_ by the inverse of rhs_.
		/// </para>
		/// <para> Indices within the provided range will contain results of respective division operations. </para>
		/// <para> Indices outside of the provided range will be copies of the respective indices in lhs_matrix_. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be divided. </para>
		/// <para> If Rhs_ is none of the above: All index divisions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of basic division.</param>
		/// <returns>EmuMath Matrix containing the results of basic division in respective indices within the provided range, and copied respective elements elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Rhs_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> DivideRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_divide_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> DivideRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_divide_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> DivideRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_divide_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class Rhs_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
		>
		constexpr inline void DivideRange(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_divide_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of dividing the provided this Matrix by the provided rhs_ argument as an EmuMath Matrix with the specified template arguments, 
		///		with size/column-major arguments matching those of this Matrix if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
		/// </para>
		/// <para>
		///		This is a basic, non-standard Matrix division. As a standard division is mathemtically undefined, there is no alternative. 
		///		To create an effect similar to what could be considered standard division when rhs_ is a Matrix, consider multiplying this Matrix by the inverse of rhs_.
		/// </para>
		/// <para> Indices within the provided range will contain results of respective division operations. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be divided. </para>
		/// <para> If Rhs_ is none of the above: All index divisions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of basic division.</param>
		/// <returns>EmuMath Matrix containing the results of basic division in respective indices within the provided range, and default-constructed elements elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Rhs_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> DivideRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_divide_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> DivideRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_divide_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> DivideRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_divide_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		/// <summary>
		/// <para> Outputs the result of dividing this Matrix by the provided rhs_ argument via the provided out_matrix_. </para>
		/// <para>
		///		This is a basic, non-standard Matrix division. As a standard division is mathemtically undefined, there is no alternative. 
		///		To create an effect similar to what could be considered standard division when rhs_ is a Matrix, consider multiplying lhs_matrix_ by the inverse of rhs_.
		/// </para>
		/// <para> Indices within the provided range will contain results of respective division operations. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be divided. </para>
		/// <para> If Rhs_ is none of the above: All index divisions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of basic division.</param>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class Rhs_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
		>
		constexpr inline void DivideRangeNoCopy(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_divide_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of modulo-dividing this Matrix by the provided rhs_ argument as an EmuMath Matrix with the specified template arguments, 
		///		with size/column-major arguments matching those of this Matrix if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
		/// </para>
		/// <para> This is a basic, non-standard Matrix modulo-division. As a standard modulo-division is mathemtically undefined, there is no alternative. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be modulo-divided. </para>
		/// <para> If Rhs_ is none of the above: All index modulo-divisions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of basic modulo-division.</param>
		/// <returns>EmuMath Matrix containing the results of basic modulo-division in respective indices.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> Mod(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_mod<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> Mod(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_mod<num_columns, num_rows, OutT_, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> Mod(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_mod<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		constexpr inline void Mod(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::matrix_mod(out_matrix_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of modulo-dividing this Matrix by the provided rhs_ argument as an EmuMath Matrix with the specified template arguments, 
		///		with size/column-major arguments matching those of this Matrix if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
		/// </para>
		/// <para> This is a basic, non-standard Matrix modulo-division. As a standard modulo-division is mathemtically undefined, there is no alternative. </para>
		/// <para> Indices within the provided range will contain results of respective modulo-division operations. </para>
		/// <para> Indices outside of the provided range will be copies of the respective indices in lhs_matrix_. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be modulo-divided. </para>
		/// <para> If Rhs_ is none of the above: All index modulo-divisions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of basic modulo-division.</param>
		/// <returns>EmuMath Matrix containing the results of basic modulo-division in respective indices within the provided range, and copied respective elements elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Rhs_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> ModRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_mod_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> ModRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_mod_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> ModRange(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_mod_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class Rhs_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
		>
		constexpr inline void ModRange(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Rhs_&& rhs_) const
		{
			EmuMath::Helpers::matrix_mod_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of modulo-dividing this Matrix by the provided rhs_ argument as an EmuMath Matrix with the specified template arguments, 
		///		with size/column-major arguments matching those of this Matrix if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
		/// </para>
		/// <para> This is a basic, non-standard Matrix modulo-division. As a standard modulo-division is mathemtically undefined, there is no alternative. </para>
		/// <para> Indices within the provided range will contain results of respective modulo-division operations. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be modulo-divided. </para>
		/// <para> If Rhs_ is none of the above: All index modulo-divisions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of basic modulo-division.</param>
		/// <returns>EmuMath Matrix containing the results of basic modulo-division in respective indices within the provided range, and default-constructed elements elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Rhs_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> ModRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_mod_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> ModRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_mod_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> ModRangeNoCopy(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_mod_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
			(
				*this,
				std::forward<Rhs_>(rhs_)
			);
		}

		/// <summary>
		/// <para> Outputs the result of modulo-dividing this Matrix by the provided rhs_ argument via the provided out_matrix_. </para>
		/// <para> This is a basic, non-standard Matrix modulo-division. As a standard modulo-division is mathemtically undefined, there is no alternative. </para>
		/// <para> Indices within the provided range will contain results of respective modulo-division operations. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be modulo-divided. </para>
		/// <para> If Rhs_ is none of the above: All index modulo-divisions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of modulo-basic division.</param>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class Rhs_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
		>
		constexpr inline void ModRangeNoCopy(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_mod_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of a fused multiply-add operation on this Matrix, using arguments y_ and z_,
		///		with output size/column-major arguments matching those of this Matrix if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
		/// </para>
		/// <para> If Y_ is an EmuMath Matrix: Respective elements in this Matrix and y_ will be multiplied. Otherwise, all elements in this Matrix will be multiplied by y_. </para>
		/// <para>
		///		If Z_ is an EmuMath Matrix: Intermediate results from each multiplication in specific indices will have the respective indices of z_ added. 
		///		Otherwise, all intermediate multiplication results will have z_ added directly.
		/// </para>
		/// </summary>
		/// <param name="y_">: Scalar or EmuMath Matrix to multiply this Matrix by.</param>
		/// <param name="z_">: Scalar or EmuMath Matrix to add to intermediate multiplication results.</param>
		/// <returns>EmuMath Matrix containing the results of fmadd operations on this Matrix with the provided arguments in respective indices.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Y_, class Z_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> Fmadd(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::matrix_fmadd<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class Y_, class Z_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> Fmadd(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::matrix_fmadd<num_columns, num_rows, OutT_, OutColumnMajor_>(*this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		template<bool OutColumnMajor_ = is_column_major, class Y_, class Z_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> Fmadd(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::matrix_fmadd<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		template<class Y_, class Z_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		constexpr inline void Fmadd(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Y_&& y_, Z_&& z_) const
		{
			EmuMath::Helpers::matrix_fmadd(out_matrix_, *this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of a fused multiply-add operation on this Matrix, using arguments y_ and z_,
		///		with output size/column-major arguments matching those of this Matrix if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
		/// </para>
		/// <para> If Y_ is an EmuMath Matrix: Respective elements in this Matrix and y_ will be multiplied. Otherwise, all elements in this Matrix will be multiplied by y_. </para>
		/// <para>
		///		If Z_ is an EmuMath Matrix: Intermediate results from each multiplication in specific indices will have the respective indices of z_ added. 
		///		Otherwise, all intermediate multiplication results will have z_ added directly.
		/// </para>
		/// <para> Indices within the provided range will contain results of respective fused multiply-addition operations. </para>
		/// <para> Indices outside of the provided range will be copies of the respective indices in matrix_x_. </para>
		/// </summary>
		/// <param name="y_">: Scalar or EmuMath Matrix to multiply this Matrix by.</param>
		/// <param name="z_">: Scalar or EmuMath Matrix to add to intermediate multiplication results.</param>
		/// <returns>EmuMath Matrix containing the results of fmadd in respective indices within the provided range, and copied respective elements of this Matrix elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Y_, class Z_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> FmaddRange(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::matrix_fmadd_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Y_>(y_),
				std::forward<Z_>(z_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major,
			class Y_, class Z_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> FmaddRange(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::matrix_fmadd_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Y_>(y_),
				std::forward<Z_>(z_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class Y_, class Z_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> FmaddRange(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::matrix_fmadd_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
			(
				*this,
				std::forward<Y_>(y_),
				std::forward<Z_>(z_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class Y_, class Z_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
		>
		constexpr inline void FmaddRange(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Y_&& y_, Z_&& z_) const
		{
			EmuMath::Helpers::matrix_fmadd_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of a fused multiply-add operation on this Matrix, using arguments y_ and z_,
		///		with output size/column-major arguments matching those of this Matrix if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
		/// </para>
		/// <para> If Y_ is an EmuMath Matrix: Respective elements in this Matrix and y_ will be multiplied. Otherwise, all elements in this Matrix will be multiplied by y_. </para>
		/// <para>
		///		If Z_ is an EmuMath Matrix: Intermediate results from each multiplication in specific indices will have the respective indices of z_ added. 
		///		Otherwise, all intermediate multiplication results will have z_ added directly.
		/// </para>
		/// <para> Indices within the provided range will contain results of respective fused multiply-addition operations. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// </summary>
		/// <param name="y_">: Scalar or EmuMath Matrix to multiply this Matrix by.</param>
		/// <param name="z_">: Scalar or EmuMath Matrix to add to intermediate multiplication results.</param>
		/// <returns>EmuMath Matrix containing the results of fmadd in respective indices within the provided range, and default-constructed elements elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Y_, class Z_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> FmaddRangeNoCopy(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::matrix_fmadd_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Y_>(y_),
				std::forward<Z_>(z_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major,
			class Y_, class Z_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> FmaddRangeNoCopy(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::matrix_fmadd_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Y_>(y_),
				std::forward<Z_>(z_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class Y_, class Z_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> FmaddRangeNoCopy(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::matrix_fmadd_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
			(
				*this,
				std::forward<Y_>(y_),
				std::forward<Z_>(z_)
			);
		}

		/// <summary>
		/// <para> Outputs the result of a fused multiply-add operation on this Matrix using arguments y_ and z_, via the provided out_matrix_. </para>
		/// <para> If Y_ is an EmuMath Matrix: Respective elements in this Matrix and y_ will be multiplied. Otherwise, all elements in this Matrix will be multiplied by y_. </para>
		/// <para>
		///		If Z_ is an EmuMath Matrix: Intermediate results from each multiplication in specific indices will have the respective indices of z_ added. 
		///		Otherwise, all intermediate multiplication results will have z_ added directly.
		/// </para>
		/// <para> Indices within the provided range will contain results of respective fused multiply-addition operations. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// </summary>
		/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
		/// <param name="y_">: Scalar or EmuMath Matrix to multiply this Matrix by.</param>
		/// <param name="z_">: Scalar or EmuMath Matrix to add to intermediate multiplication results.</param>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class Y_, class Z_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
		>
		constexpr inline void FmaddRangeNoCopy(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::matrix_fmadd_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}













		/// <summary>
		/// <para>
		///		Outputs the result of a fused multiply-subtract operation on this Matrix, using arguments y_ and z_,
		///		with output size/column-major arguments matching those of this Matrix if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
		/// </para>
		/// <para> If Y_ is an EmuMath Matrix: Respective elements in this Matrix and y_ will be multiplied. Otherwise, all elements in this Matrix will be multiplied by y_. </para>
		/// <para>
		///		If Z_ is an EmuMath Matrix: Intermediate results from each multiplication in specific indices will have the respective indices of z_ subtracted. 
		///		Otherwise, all intermediate multiplication results will have z_ subtracted directly.
		/// </para>
		/// </summary>
		/// <param name="y_">: Scalar or EmuMath Matrix to multiply this Matrix by.</param>
		/// <param name="z_">: Scalar or EmuMath Matrix to subtract from intermediate multiplication results.</param>
		/// <returns>EmuMath Matrix containing the results of fmsub operations on this Matrix with the provided arguments in respective indices.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Y_, class Z_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> Fmsub(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::matrix_fmsub<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class Y_, class Z_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> Fmsub(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::matrix_fmsub<num_columns, num_rows, OutT_, OutColumnMajor_>(*this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		template<bool OutColumnMajor_ = is_column_major, class Y_, class Z_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> Fmsub(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::matrix_fmsub<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		template<class Y_, class Z_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		constexpr inline void Fmsub(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Y_&& y_, Z_&& z_) const
		{
			EmuMath::Helpers::matrix_fmsub(out_matrix_, *this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of a fused multiply-subtract operation on this Matrix, using arguments y_ and z_,
		///		with output size/column-major arguments matching those of this Matrix if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
		/// </para>
		/// <para> If Y_ is an EmuMath Matrix: Respective elements in this Matrix and y_ will be multiplied. Otherwise, all elements in this Matrix will be multiplied by y_. </para>
		/// <para>
		///		If Z_ is an EmuMath Matrix: Intermediate results from each multiplication in specific indices will have the respective indices of z_ subtracted. 
		///		Otherwise, all intermediate multiplication results will have z_ subtracted directly.
		/// </para>
		/// <para> Indices within the provided range will contain results of respective fused multiply-subtraction operations. </para>
		/// <para> Indices outside of the provided range will be copies of the respective indices in matrix_x_. </para>
		/// </summary>
		/// <param name="y_">: Scalar or EmuMath Matrix to multiply this Matrix by.</param>
		/// <param name="z_">: Scalar or EmuMath Matrix to subtract from intermediate multiplication results.</param>
		/// <returns>EmuMath Matrix containing the results of fmsub in respective indices within the provided range, and copied respective elements of this Matrix elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Y_, class Z_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> FmsubRange(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::matrix_fmsub_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Y_>(y_),
				std::forward<Z_>(z_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major,
			class Y_, class Z_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> FmsubRange(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::matrix_fmsub_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Y_>(y_),
				std::forward<Z_>(z_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class Y_, class Z_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> FmsubRange(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::matrix_fmsub_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
			(
				*this,
				std::forward<Y_>(y_),
				std::forward<Z_>(z_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class Y_, class Z_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
		>
		constexpr inline void FmsubRange(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Y_&& y_, Z_&& z_) const
		{
			EmuMath::Helpers::matrix_fmsub_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}

		/// <summary>
		/// <para>
		///		Outputs the result of a fused multiply-subtract operation on this Matrix, using arguments y_ and z_,
		///		with output size/column-major arguments matching those of this Matrix if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
		/// </para>
		/// <para> If Y_ is an EmuMath Matrix: Respective elements in this Matrix and y_ will be multiplied. Otherwise, all elements in this Matrix will be multiplied by y_. </para>
		/// <para>
		///		If Z_ is an EmuMath Matrix: Intermediate results from each multiplication in specific indices will have the respective indices of z_ subtracted. 
		///		Otherwise, all intermediate multiplication results will have z_ subtracted directly.
		/// </para>
		/// <para> Indices within the provided range will contain results of respective fused multiply-subtraction operations. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// </summary>
		/// <param name="y_">: Scalar or EmuMath Matrix to multiply this Matrix by.</param>
		/// <param name="z_">: Scalar or EmuMath Matrix to subtract from intermediate multiplication results.</param>
		/// <returns>EmuMath Matrix containing the results of fmsub in respective indices within the provided range, and default-constructed elements elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Y_, class Z_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> FmsubRangeNoCopy(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::matrix_fmsub_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Y_>(y_),
				std::forward<Z_>(z_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major,
			class Y_, class Z_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> FmsubRangeNoCopy(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::matrix_fmsub_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Y_>(y_),
				std::forward<Z_>(z_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class Y_, class Z_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> FmsubRangeNoCopy(Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::matrix_fmsub_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
			(
				*this,
				std::forward<Y_>(y_),
				std::forward<Z_>(z_)
			);
		}

		/// <summary>
		/// <para> Outputs the result of a fused multiply-add operation on this Matrix using arguments y_ and z_, via the provided out_matrix_. </para>
		/// <para> If Y_ is an EmuMath Matrix: Respective elements in this Matrix and y_ will be multiplied. Otherwise, all elements in this Matrix will be multiplied by y_. </para>
		/// <para>
		///		If Z_ is an EmuMath Matrix: Intermediate results from each multiplication in specific indices will have the respective indices of z_ added. 
		///		Otherwise, all intermediate multiplication results will have z_ added directly.
		/// </para>
		/// <para> Indices within the provided range will contain results of respective fused multiply-addition operations. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// </summary>
		/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
		/// <param name="y_">: Scalar or EmuMath Matrix to multiply this Matrix by.</param>
		/// <param name="z_">: Scalar or EmuMath Matrix to add to intermediate multiplication results.</param>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class Y_, class Z_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
		>
		constexpr inline void FmsubRangeNoCopy(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Y_&& y_, Z_&& z_) const
		{
			return EmuMath::Helpers::matrix_fmsub_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<Y_>(y_), std::forward<Z_>(z_));
		}
#pragma endregion

#pragma region CONST_STD_ARITHMETIC_FUNCS
		/// <summary>
		/// <para> Outputs an EmuMath Matrix resulting from basic multiplication of this Matrix with the provided Rhs_ argument. </para>
		/// <para> 
		///		This function will only be available for rhs-arguments which are NOT specialised for standard multiplication 
		///		(unlike Matrices and Vectors, which are specialised). 
		/// </para>
		/// <para> To always perform basic multiplication regardless of argument type, use `MultiplyBasic` instead. </para>
		/// </summary>
		/// <param name="rhs_">: Unspecialised argument appearing on the right of multiplication.</param>
		/// <returns>EmuMath Matrix containing the results of basic multiplication in respective indices.</returns>
		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_, typename = std::enable_if_t<!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>()>>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> Multiply(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_multiply<OutT_, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<bool OutColumnMajor_ = is_column_major, class Rhs_, typename = std::enable_if_t<!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>()>>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> Multiply(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_multiply<value_type_uq, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template
		<
			class Rhs_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
			typename = std::enable_if_t<!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>()>
		>
		constexpr inline void Multiply(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::matrix_multiply(out_matrix_, *this, rhs_);
		}

		/// <summary>
		/// <para> Outputs an EmuMath Vector resulting from a multiplication with this Matrix. The Vector will be treated as a single-column Matrix. </para>
		/// <para> The Vector must meet constraint A or B: </para>
		/// <para> A: The Vector's size is equal to num_rows. </para>
		/// <para> B: The Vector's size is equal to (num_rows - 1). In this case, the non-contained index will be treated as 1. </para>
		/// <para> NOTE: OutColumnMajor_ is unused in this function. It is only present to allow a consistent interface for templates. </para>
		/// </summary>
		/// <param name="rhs_vector_">: EmuMath Vector to multiply via this Matrix.</param>
		/// <returns>EmuMath Vector resulting from a multiplication of this Matrix and the provided Vector.</returns>
		template<typename OutT_, bool OutColumnMajor_ = is_column_major, typename RhsT_, std::size_t RhsSize_>
		[[nodiscard]] constexpr inline EmuMath::Vector<RhsSize_, OutT_> Multiply(const EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_) const
		{
			return EmuMath::Helpers::matrix_multiply<OutT_, OutColumnMajor_>(*this, rhs_vector_);
		}

		template<bool OutColumnMajor_ = is_column_major, typename RhsT_, std::size_t RhsSize_>
		[[nodiscard]] constexpr inline EmuMath::Vector<RhsSize_, typename EmuMath::Vector<RhsSize_, RhsT_>::preferred_floating_point> Multiply
		(
			const EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_
		)
		{
			using rhs_fp = typename EmuMath::Vector<RhsSize_, RhsT_>::preferred_floating_point;
			return EmuMath::Helpers::matrix_multiply<rhs_fp, OutColumnMajor_>(*this, rhs_vector_);
		}

		template<typename RhsT_, std::size_t RhsSize_, typename OutT_, std::size_t OutSize_>
		constexpr inline void Multiply(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_) const
		{
			EmuMath::Helpers::matrix_multiply(out_vector_, *this, rhs_vector_);
		}

		/// <summary>
		/// <para> Outputs the result of a standard Matrix multiplication with the passed Matrix, where this Matrix appears on the left-hand side. </para>
		/// <para> The output Matrix will have a number of columns equal to that of rhs_matrix_, and a number of rows equal to that of this Matrix. </para>
		/// <para> The number of columns in this Matrix must be equal to the number of rows in rhs_matrix_. </para>
		/// <para>
		///		Output indices will be the dot product of the row in this Matrix and the column in rhs_matrix_. 
		///		For example, out(1, 3) would be (in pseudocode) dot(this_matrix.Rows[3], rhs_matrix_.Columns[1]).
		/// </para>
		/// </summary>
		/// <param name="rhs_matrix_">: EmuMath Matrix appearing on the right of Matrix multiplication.</param>
		/// <returns>EmuMath Matrix resulting from a standard Matrix multiplication of this Matrix and the provided rhs_matrix_, where this Matrix appears on the left.</returns>
		template<typename OutT_, bool OutColumnMajor_ = is_column_major, std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<RhsNumColumns_, num_rows, OutT_, OutColumnMajor_> Multiply
		(
			const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_
		) const
		{
			return EmuMath::Helpers::matrix_multiply<OutT_, OutColumnMajor_>(*this, rhs_matrix_);
		}

		template<bool OutColumnMajor_ = is_column_major, std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<RhsNumColumns_, num_rows, preferred_floating_point, OutColumnMajor_> Multiply
		(
			const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_
		) const
		{
			return EmuMath::Helpers::matrix_multiply<preferred_floating_point, OutColumnMajor_>(*this, rhs_matrix_);
		}

		template
		<
			std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
		>
		constexpr inline void Multiply
		(
			EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
			const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_
		) const
		{
			EmuMath::Helpers::matrix_multiply(out_matrix_, *this, rhs_matrix_);
		}
#pragma endregion

#pragma region BASIC_ARITHMETIC_ASSIGN_FUNCS
	public:
		/// <summary>
		/// <para> Performs an arithmetic add-assign (e.g. operator+=) on this Matrix with the provided rhs_ argument. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be added. </para>
		/// <para> If Rhs_ is none of the above: All index additions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of addition.</param>
		template<bool ColumnMajorOrder_ = is_column_major, class Rhs_>
		constexpr inline void AddAssign(Rhs_&& rhs_)
		{
			EmuMath::Helpers::matrix_add_assign<ColumnMajorOrder_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs an arithmetic add-assign (e.g. operator+=) on this Matrix with the provided rhs_ argument. </para>
		/// <para> Operations will only be performed for indices within the provided range. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be added. </para>
		/// <para> If Rhs_ is none of the above: All index additions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of addition.</param>
		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool ColumnMajorOrder_ = is_column_major, class Rhs_>
		constexpr inline void AddAssignRange(Rhs_&& rhs_)
		{
			EmuMath::Helpers::matrix_add_assign_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, ColumnMajorOrder_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs an arithmetic subtract-assign (e.g. operator-=) on this Matrix with the provided rhs_ argument. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be subtracted. </para>
		/// <para> If Rhs_ is none of the above: All index subtractions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of subtraction.</param>
		template<bool ColumnMajorOrder_ = is_column_major, class Rhs_>
		constexpr inline void SubtractAssign(Rhs_&& rhs_)
		{
			EmuMath::Helpers::matrix_subtract_assign<ColumnMajorOrder_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs an arithmetic subtract-assign (e.g. operator-=) on this Matrix with the provided rhs_ argument. </para>
		/// <para> Operations will only be performed for indices within the provided range. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be subtracted. </para>
		/// <para> If Rhs_ is none of the above: All index subtractions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of subtraction.</param>
		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool ColumnMajorOrder_ = is_column_major, class Rhs_>
		constexpr inline void SubtractAssignRange(Rhs_&& rhs_)
		{
			EmuMath::Helpers::matrix_subtract_assign_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, ColumnMajorOrder_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs an arithmetic multiply-assign (e.g. operator*=) on this Matrix with the provided rhs_ argument. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be multiplied. </para>
		/// <para> If Rhs_ is none of the above: All index multiplications will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of basic multiplication.</param>
		template<bool ColumnMajorOrder_ = is_column_major, class Rhs_>
		constexpr inline void MultiplyBasicAssign(Rhs_&& rhs_)
		{
			EmuMath::Helpers::matrix_multiply_basic_assign<ColumnMajorOrder_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs an arithmetic multiply-assign (e.g. operator*=) on this Matrix with the provided rhs_ argument. </para>
		/// <para> Operations will only be performed for indices within the provided range. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be multiplied. </para>
		/// <para> If Rhs_ is none of the above: All index multiplications will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of basic multiplication.</param>
		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool ColumnMajorOrder_ = is_column_major, class Rhs_>
		constexpr inline void MultiplyBasicAssignRange(Rhs_&& rhs_)
		{
			EmuMath::Helpers::matrix_multiply_basic_assign_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, ColumnMajorOrder_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs an arithmetic subtract-assign (e.g. operator/=) on this Matrix with the provided rhs_ argument. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be divided. </para>
		/// <para> If Rhs_ is none of the above: All index divisions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of division.</param>
		template<bool ColumnMajorOrder_ = is_column_major, class Rhs_>
		constexpr inline void DivideAssign(Rhs_&& rhs_)
		{
			EmuMath::Helpers::matrix_divide_assign<ColumnMajorOrder_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs an arithmetic subtract-assign (e.g. operator/=) on this Matrix with the provided rhs_ argument. </para>
		/// <para> Operations will only be performed for indices within the provided range. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be divided. </para>
		/// <para> If Rhs_ is none of the above: All index divisions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of division.</param>
		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool ColumnMajorOrder_ = is_column_major, class Rhs_>
		constexpr inline void DivideAssignRange(Rhs_&& rhs_)
		{
			EmuMath::Helpers::matrix_divide_assign_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, ColumnMajorOrder_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs an arithmetic mod-assign (e.g. operator%=) on this Matrix with the provided rhs_ argument. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be modulo-divided. </para>
		/// <para> If Rhs_ is none of the above: All index modulo-divisions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of modulo-division.</param>
		template<bool ColumnMajorOrder_ = is_column_major, class Rhs_>
		constexpr inline void ModAssign(Rhs_&& rhs_)
		{
			EmuMath::Helpers::matrix_mod_assign<ColumnMajorOrder_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs an arithmetic mod-assign (e.g. operator%=) on this Matrix with the provided rhs_ argument. </para>
		/// <para> Operations will only be performed for indices within the provided range. </para>
		/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be modulo-divided. </para>
		/// <para> If Rhs_ is none of the above: All index modulo-divisions will use the rhs_ directly. </para>
		/// </summary>
		/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of modulo-division.</param>
		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool ColumnMajorOrder_ = is_column_major, class Rhs_>
		constexpr inline void ModAssignRange(Rhs_&& rhs_)
		{
			EmuMath::Helpers::matrix_mod_assign_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, ColumnMajorOrder_>(*this, std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region STD_ARITHMETIC_ASSIGN_FUNCS
		/// <summary>
		/// <para> Performs an arithmetic multiply-assign (e.g. operator*=) on this Matrix with the provided rhs_ argument. </para>
		/// <para> 
		///		This function will only be available for rhs-arguments which are NOT specialised for standard multiplication 
		///		(unlike Matrices and Vectors, which are specialised). 
		/// </para>
		/// </summary>
		/// <param name="rhs_">: Unspecialised item appearing on the right of Matrix multiplication.</param>
		template<bool ColumnMajorOrder_ = is_column_major, class Rhs_, typename = std::enable_if_t<!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>()>>
		constexpr inline void MultiplyAssign(Rhs_&& rhs_)
		{
			EmuMath::Helpers::matrix_multiply_assign<ColumnMajorOrder_>(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs a multiply-assign operation (e.g. operator*=) between this Matrix and the passed EmuMath Vector. </para>
		/// <para>
		///		Unlike most arithmetic-assign operations, this will assign to the right-hand operand, as the result will be a Vector of equal size instead of a Matrix. 
		///		As a result, this function may be called on a const-qualified Matrix unlike other `...Assign` functions.
		/// </para>
		/// <para> If needed, a copy of the provided Vector will be formed automatically to prevent invalid results developing from its assignment. </para>
		/// <para> The passed Vector will be treated as a single-column Matrix, and must meet constraint A or B: </para>
		/// <para> A: The Vector's size is equal to the number of rows stored in this Matrix. </para>
		/// <para> B: The Vector's size + 1 is equal to the number of rows stored in this Matrix. In this case, the non-contained coordinate will be treated as 1. </para>
		/// <para> NOTE: ColumnMajorOrder_ is not used by this function, and is only present to allow consistency for use in templates. </para>
		/// </summary>
		/// <param name="rhs_vector_">: EmuMath Vector to multiply with this Matrix, and to output results to. This may not be const-qualified due to use for output.</param>
		template<bool ColumnMajorOrder_ = is_column_major, typename RhsT_, std::size_t RhsSize_>
		constexpr inline void MultiplyAssign(EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_) const
		{
			EmuMath::Helpers::matrix_multiply_assign<ColumnMajorOrder_>(*this, rhs_vector_);
		}

		/// <summary>
		/// <para> Performs a multiply-assign operation (e.g. operator*=) between this Matrix and the passed EmuMath Matrix. </para>
		/// <para> A copy of this Matrix will be formed automatically to prevent invalid results developing from its assignment. </para>
		/// </summary>
		/// <param name="rhs_matrix_">: EmuMath Matrix appearing on the right of multiplication.</param>
		template<bool ColumnMajorOrder_ = is_column_major, typename RhsT_, std::size_t RhsNumColumns_, std::size_t RhsNumRows_, bool RhsColumnMajor_>
		constexpr inline void MultiplyAssign(const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_)
		{
			EmuMath::Helpers::matrix_multiply_assign<ColumnMajorOrder_>(*this, rhs_matrix_);
		}

		/// <summary>
		/// <para> Performs a standard multiplication of this Matrix with itself and stores the result within this Matrix. </para>
		/// <para> Squaring is performed using a copy of this Matrix to ensure results are correct and unaffected by updates to this Matrix's elements. </para>
		/// <para> This function is only available where this Matrix type can be standard multiplied by another Matrix of the same size. </para>
		/// </summary>
		/// <returns>Reference to this Matrix after squaring.</returns>
		template<bool ColumnMajorOrder_ = is_column_major, typename = std::enable_if_t<valid_matrix_multiply_arg_size<NumColumns_, NumRows_>()>>
		constexpr inline this_type& SquareAssign()
		{
			EmuMath::Helpers::matrix_square_assign<ColumnMajorOrder_>(*this);
			return *this;
		}
#pragma endregion

#pragma region ROUNDING_FUNCS
		/// <summary> 
		/// <para> Returns a version of this Matrix with all of its elements rounded toward negative infinity. </para>
		/// <para> This does not provide a guarantee to be constexpr where possible. For such behaviour, use `FloorConstexpr`. </para>
		/// </summary>
		/// <returns>Copy of this Matrix with its elements rounded toward negative infinity.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> Floor() const
		{
			return EmuMath::Helpers::matrix_floor<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> Floor() const
		{
			return EmuMath::Helpers::matrix_floor<num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}

		template<bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> Floor() const
		{
			return EmuMath::Helpers::matrix_floor<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this);
		}

		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		constexpr inline void Floor(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_) const
		{
			EmuMath::Helpers::matrix_floor(out_matrix_, *this);
		}

		/// <summary>
		/// <para> Returns a version of this Matrix with all of its elements rounded toward negative infinity. </para>
		/// <para> Indices within the provided range will contain results of respective rounding operations. </para>
		/// <para> Indices outside of the provided range will be copies of the respective indices within this Matrix. </para>
		/// <para> This does not provide a guarantee to be constexpr where possible. For such behaviour, use `FloorRangeConstexpr`. </para>
		/// </summary>
		/// <returns>Copy of this Matrix with its elements rounded toward negative infinity.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> FloorRange() const
		{
			return EmuMath::Helpers::matrix_floor_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> FloorRange() const
		{
			return EmuMath::Helpers::matrix_floor_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> FloorRange() const
		{
			return EmuMath::Helpers::matrix_floor_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		constexpr inline void FloorRange(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_) const
		{
			EmuMath::Helpers::matrix_floor_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this);
		}

		/// <summary>
		/// <para> Returns a version of this Matrix with all of its elements rounded toward negative infinity. </para>
		/// <para> Indices within the provided range will contain results of respective rounding operations. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// <para> This does not provide a guarantee to be constexpr where possible. For such behaviour, use `FloorRangeNoCopyConstexpr`. </para>
		/// </summary>
		/// <returns>Copy of this Matrix with its elements rounded toward negative infinity.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> FloorRangeNoCopy() const
		{
			return EmuMath::Helpers::matrix_floor_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> FloorRangeNoCopy() const
		{
			return EmuMath::Helpers::matrix_floor_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> FloorRangeNoCopy() const
		{
			return EmuMath::Helpers::matrix_floor_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this);
		}

		/// <summary>
		/// <para> Outputs a version of this Matrix with all of its elements rounded toward negative infinity via the provided out_matrix_. </para>
		/// <para> Indices within the provided range will contain results of respective rounding operations. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// <para> This does not provide a guarantee to be constexpr where possible. For such behaviour, use `FloorRangeNoCopyConstexpr`. </para>
		/// </summary>
		/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		constexpr inline void FloorRangeNoCopy(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_) const
		{
			EmuMath::Helpers::matrix_floor_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this);
		}

		/// <summary> 
		/// <para> Returns a version of this Matrix with all of its elements rounded toward positive infinity. </para>
		/// <para> This does not provide a guarantee to be constexpr where possible. For such behaviour, use `CeilConstexpr`. </para>
		/// </summary>
		/// <returns>Copy of this Matrix with its elements rounded toward positive infinity.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> Ceil() const
		{
			return EmuMath::Helpers::matrix_ceil<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> Ceil() const
		{
			return EmuMath::Helpers::matrix_ceil<num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}

		template<bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> Ceil() const
		{
			return EmuMath::Helpers::matrix_ceil<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this);
		}

		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		constexpr inline void Ceil(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_) const
		{
			EmuMath::Helpers::matrix_ceil(out_matrix_, *this);
		}

		/// <summary>
		/// <para> Returns a version of this Matrix with all of its elements rounded toward positive infinity. </para>
		/// <para> Indices within the provided range will contain results of respective rounding operations. </para>
		/// <para> Indices outside of the provided range will be copies of the respective indices within this Matrix. </para>
		/// <para> This does not provide a guarantee to be constexpr where possible. For such behaviour, use `CeilRangeConstexpr`. </para>
		/// </summary>
		/// <returns>Copy of this Matrix with its elements rounded toward positive infinity.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> CeilRange() const
		{
			return EmuMath::Helpers::matrix_ceil_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> CeilRange() const
		{
			return EmuMath::Helpers::matrix_ceil_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> CeilRange() const
		{
			return EmuMath::Helpers::matrix_ceil_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		constexpr inline void CeilRange(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_) const
		{
			EmuMath::Helpers::matrix_ceil_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this);
		}

		/// <summary>
		/// <para> Returns a version of this Matrix with all of its elements rounded toward positive infinity. </para>
		/// <para> Indices within the provided range will contain results of respective rounding operations. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// <para> This does not provide a guarantee to be constexpr where possible. For such behaviour, use `CeilRangeNoCopyConstexpr`. </para>
		/// </summary>
		/// <returns>Copy of this Matrix with its elements rounded toward positive infinity.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> CeilRangeNoCopy() const
		{
			return EmuMath::Helpers::matrix_ceil_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> CeilRangeNoCopy() const
		{
			return EmuMath::Helpers::matrix_ceil_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> CeilRangeNoCopy() const
		{
			return EmuMath::Helpers::matrix_ceil_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this);
		}

		/// <summary>
		/// <para> Outputs a version of this Matrix with all of its elements rounded toward positive infinity via the provided out_matrix_. </para>
		/// <para> Indices within the provided range will contain results of respective rounding operations. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// <para> This does not provide a guarantee to be constexpr where possible. For such behaviour, use `CeilRangeNoCopyConstexpr`. </para>
		/// </summary>
		/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		constexpr inline void CeilRangeNoCopy(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_) const
		{
			EmuMath::Helpers::matrix_ceil_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this);
		}

		/// <summary> 
		/// <para> Returns a version of this Matrix with all of its elements rounded toward 0. </para>
		/// <para> This does not provide a guarantee to be constexpr where possible. For such behaviour, use `TruncConstexpr`. </para>
		/// </summary>
		/// <returns>Copy of this Matrix with its elements rounded toward 0.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> Trunc() const
		{
			return EmuMath::Helpers::matrix_trunc<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> Trunc() const
		{
			return EmuMath::Helpers::matrix_trunc<num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}

		template<bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> Trunc() const
		{
			return EmuMath::Helpers::matrix_trunc<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this);
		}

		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		constexpr inline void Trunc(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_) const
		{
			EmuMath::Helpers::matrix_trunc(out_matrix_, *this);
		}

		/// <summary>
		/// <para> Returns a version of this Matrix with all of its elements rounded toward 0. </para>
		/// <para> Indices within the provided range will contain results of respective rounding operations. </para>
		/// <para> Indices outside of the provided range will be copies of the respective indices within this Matrix. </para>
		/// <para> This does not provide a guarantee to be constexpr where possible. For such behaviour, use `TruncRangeConstexpr`. </para>
		/// </summary>
		/// <returns>Copy of this Matrix with its elements rounded toward 0.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> TruncRange() const
		{
			return EmuMath::Helpers::matrix_trunc_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> TruncRange() const
		{
			return EmuMath::Helpers::matrix_trunc_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> TruncRange() const
		{
			return EmuMath::Helpers::matrix_trunc_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		constexpr inline void TruncRange(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_) const
		{
			EmuMath::Helpers::matrix_trunc_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this);
		}

		/// <summary>
		/// <para> Returns a version of this Matrix with all of its elements rounded toward 0. </para>
		/// <para> Indices within the provided range will contain results of respective rounding operations. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// <para> This does not provide a guarantee to be constexpr where possible. For such behaviour, use `TruncRangeNoCopyConstexpr`. </para>
		/// </summary>
		/// <returns>Copy of this Matrix with its elements rounded toward 0.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> TruncRangeNoCopy() const
		{
			return EmuMath::Helpers::matrix_trunc_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> TruncRangeNoCopy() const
		{
			return EmuMath::Helpers::matrix_trunc_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> TruncRangeNoCopy() const
		{
			return EmuMath::Helpers::matrix_trunc_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this);
		}

		/// <summary>
		/// <para> Outputs a version of this Matrix with all of its elements rounded toward 0 via the provided out_matrix_. </para>
		/// <para> Indices within the provided range will contain results of respective rounding operations. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// <para> This does not provide a guarantee to be constexpr where possible. For such behaviour, use `TruncRangeNoCopyConstexpr`. </para>
		/// </summary>
		/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		constexpr inline void TruncRangeNoCopy(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_) const
		{
			EmuMath::Helpers::matrix_trunc_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this);
		}
#pragma endregion

#pragma region CONSTEXPR_ROUNDING_FUNCS
		/// <summary> 
		/// <para> Returns a version of this Matrix with all of its elements rounded toward negative infinity. </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <returns>Copy of this Matrix with its elements rounded toward negative infinity.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> FloorConstexpr() const
		{
			return EmuMath::Helpers::matrix_floor_constexpr<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> FloorConstexpr() const
		{
			return EmuMath::Helpers::matrix_floor_constexpr<num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}

		template<bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> FloorConstexpr() const
		{
			return EmuMath::Helpers::matrix_floor_constexpr<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this);
		}

		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		constexpr inline void FloorConstexpr(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_) const
		{
			EmuMath::Helpers::matrix_floor_constexpr(out_matrix_, *this);
		}

		/// <summary>
		/// <para> Returns a version of this Matrix with all of its elements rounded toward negative infinity. </para>
		/// <para> Indices within the provided range will contain results of respective rounding operations. </para>
		/// <para> Indices outside of the provided range will be copies of the respective indices within this Matrix. </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <returns>Copy of this Matrix with its elements rounded toward negative infinity.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> FloorRangeConstexpr() const
		{
			return EmuMath::Helpers::matrix_floor_range_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> FloorRangeConstexpr() const
		{
			return EmuMath::Helpers::matrix_floor_range_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> FloorRangeConstexpr() const
		{
			return EmuMath::Helpers::matrix_floor_range_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		constexpr inline void FloorRangeConstexpr(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_) const
		{
			EmuMath::Helpers::matrix_floor_range_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this);
		}

		/// <summary>
		/// <para> Returns a version of this Matrix with all of its elements rounded toward negative infinity. </para>
		/// <para> Indices within the provided range will contain results of respective rounding operations. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <returns>Copy of this Matrix with its elements rounded toward negative infinity.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> FloorRangeNoCopyConstexpr() const
		{
			return EmuMath::Helpers::matrix_floor_range_no_copy_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> FloorRangeNoCopyConstexpr() const
		{
			return EmuMath::Helpers::matrix_floor_range_no_copy_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> FloorRangeNoCopyConstexpr() const
		{
			return EmuMath::Helpers::matrix_floor_range_no_copy_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this);
		}

		/// <summary>
		/// <para> Outputs a version of this Matrix with all of its elements rounded toward negative infinity via the provided out_matrix_. </para>
		/// <para> Indices within the provided range will contain results of respective rounding operations. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		constexpr inline void FloorRangeNoCopyConstexpr(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_) const
		{
			EmuMath::Helpers::matrix_floor_range_no_copy_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this);
		}

		/// <summary> 
		/// <para> Returns a version of this Matrix with all of its elements rounded toward positive infinity. </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <returns>Copy of this Matrix with its elements rounded toward positive infinity.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> CeilConstexpr() const
		{
			return EmuMath::Helpers::matrix_ceil_constexpr<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> CeilConstexpr() const
		{
			return EmuMath::Helpers::matrix_ceil_constexpr<num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}

		template<bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> CeilConstexpr() const
		{
			return EmuMath::Helpers::matrix_ceil_constexpr<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this);
		}

		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		constexpr inline void CeilConstexpr(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_) const
		{
			EmuMath::Helpers::matrix_ceil_constexpr(out_matrix_, *this);
		}

		/// <summary>
		/// <para> Returns a version of this Matrix with all of its elements rounded toward positive infinity. </para>
		/// <para> Indices within the provided range will contain results of respective rounding operations. </para>
		/// <para> Indices outside of the provided range will be copies of the respective indices within this Matrix. </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <returns>Copy of this Matrix with its elements rounded toward positive infinity.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> CeilRangeConstexpr() const
		{
			return EmuMath::Helpers::matrix_ceil_range_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> CeilRangeConstexpr() const
		{
			return EmuMath::Helpers::matrix_ceil_range_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> CeilRangeConstexpr() const
		{
			return EmuMath::Helpers::matrix_ceil_range_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		constexpr inline void CeilRangeConstexpr(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_) const
		{
			EmuMath::Helpers::matrix_ceil_range_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this);
		}

		/// <summary>
		/// <para> Returns a version of this Matrix with all of its elements rounded toward positive infinity. </para>
		/// <para> Indices within the provided range will contain results of respective rounding operations. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <returns>Copy of this Matrix with its elements rounded toward positive infinity.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> CeilRangeNoCopyConstexpr() const
		{
			return EmuMath::Helpers::matrix_ceil_range_no_copy_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> CeilRangeNoCopyConstexpr() const
		{
			return EmuMath::Helpers::matrix_ceil_range_no_copy_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> CeilRangeNoCopyConstexpr() const
		{
			return EmuMath::Helpers::matrix_ceil_range_no_copy_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this);
		}

		/// <summary>
		/// <para> Outputs a version of this Matrix with all of its elements rounded toward positive infinity via the provided out_matrix_. </para>
		/// <para> Indices within the provided range will contain results of respective rounding operations. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		constexpr inline void CeilRangeNoCopyConstexpr(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_) const
		{
			EmuMath::Helpers::matrix_ceil_range_no_copy_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this);
		}

		/// <summary> 
		/// <para> Returns a version of this Matrix with all of its elements rounded toward 0. </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <returns>Copy of this Matrix with its elements rounded toward 0.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> TruncConstexpr() const
		{
			return EmuMath::Helpers::matrix_trunc_constexpr<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> TruncConstexpr() const
		{
			return EmuMath::Helpers::matrix_trunc_constexpr<num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}

		template<bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> TruncConstexpr() const
		{
			return EmuMath::Helpers::matrix_trunc_constexpr<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this);
		}

		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		constexpr inline void TruncConstexpr(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_) const
		{
			EmuMath::Helpers::matrix_trunc_constexpr(out_matrix_, *this);
		}

		/// <summary>
		/// <para> Returns a version of this Matrix with all of its elements rounded toward 0. </para>
		/// <para> Indices within the provided range will contain results of respective rounding operations. </para>
		/// <para> Indices outside of the provided range will be copies of the respective indices within this Matrix. </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <returns>Copy of this Matrix with its elements rounded toward 0.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> TruncRangeConstexpr() const
		{
			return EmuMath::Helpers::matrix_trunc_range_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> TruncRangeConstexpr() const
		{
			return EmuMath::Helpers::matrix_trunc_range_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> TruncRangeConstexpr() const
		{
			return EmuMath::Helpers::matrix_trunc_range_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		constexpr inline void TruncRangeConstexpr(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_) const
		{
			EmuMath::Helpers::matrix_trunc_range_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this);
		}

		/// <summary>
		/// <para> Returns a version of this Matrix with all of its elements rounded toward 0. </para>
		/// <para> Indices within the provided range will contain results of respective rounding operations. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <returns>Copy of this Matrix with its elements rounded toward 0.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> TruncRangeNoCopyConstexpr() const
		{
			return EmuMath::Helpers::matrix_trunc_range_no_copy_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> TruncRangeNoCopyConstexpr() const
		{
			return EmuMath::Helpers::matrix_trunc_range_no_copy_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> TruncRangeNoCopyConstexpr() const
		{
			return EmuMath::Helpers::matrix_trunc_range_no_copy_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this);
		}

		/// <summary>
		/// <para> Outputs a version of this Matrix with all of its elements rounded toward 0 via the provided out_matrix_. </para>
		/// <para> Indices within the provided range will contain results of respective rounding operations. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// <para>
		///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
		///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
		/// </para>
		/// </summary>
		/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		constexpr inline void TruncRangeNoCopyConstexpr(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_) const
		{
			EmuMath::Helpers::matrix_trunc_range_no_copy_constexpr<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this);
		}
#pragma endregion

#pragma region MISC_ARITHMETIC_FUNCS
	public:
		/// <summary>
		/// <para> Returns a version of this Matrix with its elements made absolute (e.g. x = x, -x = x). </para>
		/// </summary>
		/// <returns>Copy of the this Matrix with its elements made absolute.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> Abs() const
		{
			return EmuMath::Helpers::matrix_abs<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> Abs() const
		{
			return EmuMath::Helpers::matrix_abs<num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}

		template<bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> Abs() const
		{
			return EmuMath::Helpers::matrix_abs<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this);
		}

		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		constexpr inline void Abs(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_) const
		{
			EmuMath::Helpers::matrix_abs(out_matrix_, *this);
		}

		/// <summary>
		/// <para> Returns a version of this Matrix with its elements made absolute (e.g. x = x, -x = x). </para>
		/// <para> Indices within the provided range will contain results of respective absolute operations. </para>
		/// <para> Indices outside of the provided range will be copies of the respective indices within in_matrix_. </para>
		/// </summary>
		/// <returns>Copy of the this Matrix with elements within the provided range made absolute.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> AbsRange() const
		{
			return EmuMath::Helpers::matrix_abs_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> AbsRange() const
		{
			return EmuMath::Helpers::matrix_abs_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> AbsRange() const
		{
			return EmuMath::Helpers::matrix_abs_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
		>
		constexpr inline void AbsRange(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_) const
		{
			EmuMath::Helpers::matrix_abs_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this);
		}

		/// <summary>
		/// <para> Returns a version of this Matrix with its elements made absolute (e.g. x = x, -x = x). </para>
		/// <para> Indices within the provided range will contain results of respective absolute operations. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// </summary>
		/// <returns>EmuMath Matrix with elements with this Matrix's elements made absolute in the provided range, and default-constructed elements elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> AbsRangeNoCopy() const
		{
			return EmuMath::Helpers::matrix_abs_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> AbsRangeNoCopy() const
		{
			return EmuMath::Helpers::matrix_abs_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> AbsRangeNoCopy() const
		{
			return EmuMath::Helpers::matrix_abs_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this);
		}

		/// <summary>
		/// <para> Outputs a version of this Matrix with its elements made absolute (e.g. x = x, -x = x) via the provided out_matrix_. </para>
		/// <para> Indices within the provided range will contain results of respective absolute operations. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// </summary>
		/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
		>
		constexpr inline void AbsRangeNoCopy(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_) const
		{
			EmuMath::Helpers::matrix_abs_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this);
		}

		/// <summary>
		/// <para> Outputs the lowest element within this Matrix as the provided Out_ type, defaulting this Matrix's value_type_uq. </para>
		/// <para> Supports output of references if the reference type is compatible with const-qualification. </para>
		/// </summary>
		/// <returns>Lowest element of this Matrix, as the provided Out_ type.</returns>
		template<typename Out_ = value_type_uq>
		[[nodiscard]] constexpr inline Out_ Min() const
		{
			return EmuMath::Helpers::matrix_min<Out_>(*this);
		}

		template<typename Out_ = value_type_uq>
		[[nodiscard]] constexpr inline Out_ Min()
		{
			return EmuMath::Helpers::matrix_min<Out_>(*this);
		}

		/// <summary>
		/// <para> Outputs an EmuMath Matrix composed of the lowest elements out of this Matrix and b_. </para>
		/// <para>
		///		If B_ is an EmuMath Matrix: Comparisons will be performed with respective indices in this Matrix and b_. 
		///		Otherwise, all indices will be compared with b_ directly.
		/// </para>
		/// </summary>
		/// <param name="b_">: Scalar or EmuMath Matrix appearing as b in a min(a, b) operation.</param>
		/// <returns>EmuMath Matrix composed of min results in respective indices.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> Min(B_&& b_) const
		{
			return EmuMath::Helpers::matrix_min<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this, std::forward<B_>(b_));
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> Min(B_&& b_) const
		{
			return EmuMath::Helpers::matrix_min<num_columns, num_rows, OutT_, OutColumnMajor_>(*this, std::forward<B_>(b_));
		}

		template<bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> Min(B_&& b_) const
		{
			return EmuMath::Helpers::matrix_min<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this, std::forward<B_>(b_));
		}

		template<class B_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		constexpr inline void Min(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, B_&& b_) const
		{
			EmuMath::Helpers::matrix_min(out_matrix_, *this, std::forward<B_>(b_));
		}

		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> Min(B_&& b_)
		{
			return EmuMath::Helpers::matrix_min<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this, std::forward<B_>(b_));
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> Min(B_&& b_)
		{
			return EmuMath::Helpers::matrix_min<num_columns, num_rows, OutT_, OutColumnMajor_>(*this, std::forward<B_>(b_));
		}

		template<bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> Min(B_&& b_)
		{
			return EmuMath::Helpers::matrix_min<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this, std::forward<B_>(b_));
		}

		template<class B_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		constexpr inline void Min(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, B_&& b_)
		{
			EmuMath::Helpers::matrix_min(out_matrix_, *this, std::forward<B_>(b_));
		}

		/// <summary>
		/// <para> Outputs the lowest element within this Matrix as the provided Out_ type, defaulting to this Matrix's value_type_uq. </para>
		/// <para> Only elements within the provided range will be considered. </para>
		/// <para> Supports output of references if the reference type is compatible with const-qualification, and the provided range contains no theoretical indices. </para>
		/// </summary>
		/// <returns>Lowest element of this Matrix within the provided range, as the provided Out_ type.</returns>
		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename Out_ = value_type_uq>
		[[nodiscard]] constexpr inline Out_ MinRange() const
		{
			return EmuMath::Helpers::matrix_min_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, Out_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename Out_ = value_type_uq>
		[[nodiscard]] constexpr inline Out_ MinRange()
		{
			return EmuMath::Helpers::matrix_min_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, Out_>(*this);
		}

		/// <summary>
		/// <para> Outputs an EmuMath Matrix composed of the lowest elements out of this Matrix and b_. </para>
		/// <para>
		///		If B_ is an EmuMath Matrix: Comparisons will be performed with respective indices in this MAtrix and b_. 
		///		Otherwise, all indices will be compared with b_ directly.
		/// </para>
		/// <para> Indices within the provided range will be the respective minimum element out of this Matrix and b_. </para>
		/// <para> Indices outside of the provided range will be copies of the respective element within this Matrix. </para>
		/// </summary>
		/// <param name="b_">: Scalar or EmuMath Matrix appearing as b in a min(a, b) operation.</param>
		/// <returns>EmuMath Matrix composed of min results in respective indices within the provided range, and copies of respective indices within this Matrix elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class B_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> MinRange(B_&& b_) const
		{
			return EmuMath::Helpers::matrix_min_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			typename OutT_, bool OutColumnMajor_ = is_column_major, class B_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> MinRange(B_&& b_) const
		{
			return EmuMath::Helpers::matrix_min_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> MinRange(B_&& b_) const
		{
			return EmuMath::Helpers::matrix_min_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class B_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		constexpr inline void MinRange(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, B_&& b_) const
		{
			EmuMath::Helpers::matrix_min_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<B_>(b_));
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class B_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> MinRange(B_&& b_)
		{
			return EmuMath::Helpers::matrix_min_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			typename OutT_, bool OutColumnMajor_ = is_column_major, class B_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> MinRange(B_&& b_)
		{
			return EmuMath::Helpers::matrix_min_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> MinRange(B_&& b_)
		{
			return EmuMath::Helpers::matrix_min_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class B_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		constexpr inline void MinRange(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, B_&& b_)
		{
			EmuMath::Helpers::matrix_min_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<B_>(b_));
		}

		/// <summary>
		/// <para> Outputs an EmuMath Matrix composed of the lowest elements out of this Matrix and b_. </para>
		/// <para>
		///		If B_ is an EmuMath Matrix: Comparisons will be performed with respective indices in this Matrix and b_. 
		///		Otherwise, all of this Matrix's indices will be compared with b_ directly.
		/// </para>
		/// <para> Indices within the provided range will be the respective minimum element out of this Matrix and b_. </para>
		/// <para> Indices outside of the provided range will be default-constructed. </para>
		/// </summary>
		/// <param name="b_">: Scalar or EmuMath Matrix appearing as b in a min(a, b) operation.</param>
		/// <returns>EmuMath Matrix composed of min results in respective indices within the provided range, and default-constructed elements elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class B_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> MinRangeNoCopy(B_&& b_) const
		{
			return EmuMath::Helpers::matrix_min_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> MinRangeNoCopy(B_&& b_) const
		{
			return EmuMath::Helpers::matrix_min_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> MinRangeNoCopy(B_&& b_) const
		{
			return EmuMath::Helpers::matrix_min_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class B_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
		>
		constexpr inline void MinRangeNoCopy(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, B_&& b_) const
		{
			EmuMath::Helpers::matrix_min_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<B_>(b_));
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class B_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> MinRangeNoCopy(B_&& b_)
		{
			return EmuMath::Helpers::matrix_min_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> MinRangeNoCopy(B_&& b_)
		{
			return EmuMath::Helpers::matrix_min_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> MinRangeNoCopy(B_&& b_)
		{
			return EmuMath::Helpers::matrix_min_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class B_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
		>
		constexpr inline void MinRangeNoCopy(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, B_&& b_)
		{
			EmuMath::Helpers::matrix_min_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<B_>(b_));
		}
#pragma endregion

#pragma region TRANSPOSE_FUNCS
		/// <summary>
		/// <para> Outputs a transposed form of this Matrix. </para>
		/// <para> Supports output of a Matrix of references as long as only contained indices are required, and the reference type is compatible with this Matrix. </para>
		/// </summary>
		/// <returns>Transposed form of this Matrix.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> Transpose() &
		{
			return EmuMath::Helpers::matrix_transpose<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_rows, num_columns, OutT_, OutColumnMajor_> Transpose() &
		{
			return EmuMath::Helpers::matrix_transpose<num_rows, num_columns, OutT_, OutColumnMajor_>(*this);
		}

		template<bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_rows, num_columns, value_type_uq, OutColumnMajor_> Transpose() &
		{
			return EmuMath::Helpers::matrix_transpose<num_rows, num_columns, value_type_uq, OutColumnMajor_>(*this);
		}

		/// <summary>
		/// <para> Outputs a transposed form of this Matrix. </para>
		/// <para>
		///		Supports output of a Matrix of references as long as only contained indices are required, 
		///		and the reference type is compatible with this Matrix when it is in a const state.
		/// </para>
		/// </summary>
		/// <returns>Transposed form of this Matrix.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> Transpose() const &
		{
			return EmuMath::Helpers::matrix_transpose<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_rows, num_columns, OutT_, OutColumnMajor_> Transpose() const &
		{
			return EmuMath::Helpers::matrix_transpose<num_rows, num_columns, OutT_, OutColumnMajor_>(*this);
		}

		template<bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_rows, num_columns, value_type_uq, OutColumnMajor_> Transpose() const &
		{
			return EmuMath::Helpers::matrix_transpose<num_rows, num_columns, value_type_uq, OutColumnMajor_>(*this);
		}

		/// <summary>
		/// <para> Outputs a transposed form of this Matrix. </para>
		/// <para>
		///		Supports output of a Matrix of references as long as only contained indices are required, 
		///		and the reference type is compatible with this Matrix when it is in a const state. 
		///		It should be noted that this rvalue-specialisation is likely incompatible for references in most cases to prevent dangling references.
		/// </para>
		/// </summary>
		/// <returns>Transposed form of this Matrix.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> Transpose() &&
		{
			return EmuMath::Helpers::matrix_transpose<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(std::move(*this));
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_rows, num_columns, OutT_, OutColumnMajor_> Transpose() &&
		{
			return EmuMath::Helpers::matrix_transpose<num_rows, num_columns, OutT_, OutColumnMajor_>(std::move(*this));
		}

		template<bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_rows, num_columns, value_type_uq, OutColumnMajor_> Transpose() &&
		{
			return EmuMath::Helpers::matrix_transpose<num_rows, num_columns, value_type_uq, OutColumnMajor_>(std::move(*this));
		}
#pragma endregion

#pragma region STREAM_FUNCS
	public:
		/// <summary>
		/// <para> Appends this Matrix to the provided stream. </para>
		/// <para> Elements will be appended as a series of lines containing columns or lines, depending on AppendAsRows_. </para>
		/// <para> AppendAsRows_: If true, each appended line will be a row of this Matrix. Otherwise, each appended line will be a column of this Matrix. Defaults to true. </para>
		/// <para> NOTE: Appending as rows is recommended as this gives the best visual of how matrices are interpreted by EmuMath. </para>
		/// </summary>
		/// <param name="str_">Stream to append this Matrix to.</param>
		/// <returns>Reference to the provided stream.</returns>
		template<bool AppendAsRows_ = true>
		constexpr inline std::ostream& AppendToStream(std::ostream& str_) const
		{
			return EmuMath::Helpers::matrix_append_to_stream<AppendAsRows_>(str_, *this);
		}

		template<bool AppendAsRows_ = true>
		constexpr inline std::wostream& AppendToStream(std::wostream& wide_str_) const
		{
			return EmuMath::Helpers::matrix_append_to_stream<AppendAsRows_>(wide_str_, *this);
		}
#pragma endregion

	private:
		matrix_vector_type _data;


	};
}

#endif
