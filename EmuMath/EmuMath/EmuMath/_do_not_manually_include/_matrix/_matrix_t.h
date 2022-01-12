#ifndef EMU_MATH_MATRIX_T_H_INC_
#define EMU_MATH_MATRIX_T_H_INC_ 1

#include "_helpers/_all_matrix_helpers.h"
#include <exception>

namespace EmuMath
{
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	struct Matrix
	{
#pragma region TMP_INFO
	public:
		using this_type = Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		using matrix_info = EmuMath::TMP::common_matrix_info<NumColumns_, NumRows_, T_, ColumnMajor_>;
		static constexpr std::size_t num_columns = matrix_info::num_columns;
		static constexpr std::size_t num_rows = matrix_info::num_rows;
		static constexpr bool is_column_major = matrix_info::is_column_major;
		static constexpr bool is_row_major = matrix_info::is_row_major;

		using matrix_vector_type = typename matrix_info::matrix_vector_type;
		using value_type = typename matrix_info::value_type;
#pragma endregion

#pragma region CONSTRUCTORS
	public:
		template<typename = std::enable_if_t<std::is_default_constructible_v<matrix_vector_type>>>
		constexpr inline Matrix() : _data()
		{
		}
#pragma endregion

#pragma region ACCESS
	public:
		/// <summary>
		/// <para> Accesses the element at the provided indices within this Matrix, with compile-time validity checks. </para>
		/// <para> If either ColumnIndex_ or RowIndex_, a static_assert will be triggered. </para>
		/// </summary>
		/// <returns>Reference to the element at the provided index within this Matrix.</returns>
		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		[[nodiscard]] constexpr inline value_type& at()
		{
			if constexpr (ColumnIndex_ < num_columns)
			{
				if constexpr (RowIndex_ < num_rows)
				{
					if constexpr (is_column_major)
					{
						return _data.template at<RowIndex_>().template at<ColumnIndex_>();
					}
					else
					{
						return _data.template at<ColumnIndex_>().template at<RowIndex_>();
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<std::size_t, RowIndex_>(),
						"Attempted to access an index of an EmuMath Matrix, but the provided RowIndex_ is invalid. The inclusive valid row index range is 0:(num_rows - 1)."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, RowIndex_>(),
					"Attempted to access an index of an EmuMath Matrix, but the provided ColumnIndex_ is invalid. The inclusive valid column index range is 0:(num_columns - 1)."
				);
			}
		}

		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		[[nodiscard]] constexpr inline const value_type& at() const
		{
			return const_cast<this_type*>(this)->template at<ColumnIndex_, RowIndex_>();
		}

		/// <summary>
		/// <para> Accesses the element at the provided indices within this Matrix, with runtime-time validity checks. </para>
		/// <para> If either column_index_ or row_index_, a std::out_of_range exception will be thrown. </para>
		/// </summary>
		/// <param name="column_index_">: Index of the column to access.</param>
		/// <param name="row_index_">: Index of the row to access.</param>
		/// <returns>Reference to the element at the provided index within this Matrix.</returns>
		[[nodiscard]] constexpr inline value_type& at(std::size_t column_index_, std::size_t row_index_)
		{
			if constexpr ((num_columns * num_rows) > 0)
			{
				constexpr bool constexpr_str_ = __cplusplus >= 201907L;
				if ((column_index_ < num_columns) && (row_index_ < num_rows))
				{
					if constexpr (is_column_major)
					{
						return _data[row_index_][column_index_];
					}
					else
					{
						return _data[column_index_][row_index_];
					}
				}
				else
				{
					// AT LEAST 1 BAD INDEX
					if constexpr (constexpr_str_)
					{
						// We can provide some extra information if we have access to constexpr strings
						// --- This is to allow `at(index_)` to still satisfy constexpr constraints in standards before C++20
						std::string out_str_;
						out_str_.reserve(170); // Reserves enough space for all literal chars, alongside some extra for range and index after conversion.
						out_str_ += "Attempted to access an invalid contained index of an EmuMath Matrix.\nProvided indices (Column, Row): (";
						out_str_ += std::to_string(column_index_);
						out_str_ += ", ";
						out_str_ += std::to_string(row_index_);
						out_str_ += ")\nInclusive valid Column Range: 0:";
						out_str_ += std::to_string(num_columns - 1);
						out_str_ += "\nInclusive valid Row Range: 0:";
						out_str_ += std::to_string(num_rows - 1);
						throw std::out_of_range(out_str_);
					}
					else
					{
						throw std::out_of_range("Attempted to access an invalid contained index of an EmuMath Matrix.");
					}
				}
			}
		}

		[[nodiscard]] constexpr inline const value_type& at(std::size_t column_index_, std::size_t row_index_) const
		{
			return const_cast<this_type*>(this)->at(column_index_, row_index_);
		}

		/// <summary>
		/// <para> Accesses the element at the provided indices within this Matrix, with no validity checks. </para>
		/// <para> If either ColumnIndex_ or RowIndex_, behaviour is undefined. </para>
		/// </summary>
		/// <returns>Reference to the element at the provided index within this Matrix.</returns>
		[[nodiscard]] constexpr inline value_type& operator()(std::size_t column_index_, std::size_t row_index_)
		{
			if constexpr (is_column_major)
			{
				return _data[row_index_][column_index_];
			}
			else
			{
				return _data[column_index_][row_index_];
			}
		}

		[[nodiscard]] constexpr inline const value_type& operator()(std::size_t column_index_, std::size_t row_index_) const
		{
			return const_cast<this_type*>(this)->operator()(column_index_, row_index_);
		}

		[[nodiscard]] constexpr inline value_type* data()
		{
			return _data.template at<0>().data();
		}

		[[nodiscard]] constexpr inline const value_type* data() const
		{
			return const_cast<this_type*>(this)->data();
		}
#pragma endregion

#pragma region STREAM_FUNCS
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
