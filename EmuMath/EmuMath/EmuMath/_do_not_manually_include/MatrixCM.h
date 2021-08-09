#ifndef EMU_MATH_MATRIX_T_H_INC_
#define EMU_MATH_MATRIX_T_H_INC_

#include "MatrixHelpers.h"
#include <array>
#include <ostream>
#include <sstream>

namespace EmuMath
{
	/// <summary> Arbitrarily-sized matrix, stored as Column-Major. </summary>
	/// <typeparam name="T_">The type used to represent an individual value within this matrix.</typeparam>
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_>
	struct MatrixCM
	{
	public:
		/// <summary> The type used to represent an individual value within this matrix. </summary>
		using value_type = T_;
		/// <summary> The type used to represent a column within this matrix. Used for storage due to this matrix's column-major nature. </summary>
		using column_type = typename EmuMath::Helpers::matrix_major_element<NumRows_, value_type>::type;
		/// <summary> The type used to represent a row within this matrix. Unused for actual storage due to this matrix's column-major nature. </summary>
		using row_type = typename EmuMath::Helpers::matrix_major_element<NumColumns_, value_type>::type;
		/// <summary> The type used to represent all of this matrix's data as a single item. </summary>
		using packed_data_type = std::array<column_type, NumColumns_>;

		/// <summary> The number of columns in this matrix (i.e. The number of values in the horizontal direction). </summary>
		static constexpr std::size_t num_columns = NumColumns_;
		/// <summary> The number of rows in this matrix (i.e. The number of values in the vertical direction). </summary>
		static constexpr std::size_t num_rows = NumRows_;
		/// <summary> Boolean indicating if the columns within this vector are stored as EmuMath vectors. </summary>
		static constexpr bool uses_vector_storage = NumRows_ >= 2 && NumRows_ <= 4;

		using this_type = MatrixCM<num_columns, num_rows, value_type>;

	private:
		template<typename...PassedColumns_>
		static constexpr bool _valid_template_constructor_args()
		{
			return (sizeof...(PassedColumns_) == num_columns) && EmuCore::TMPHelpers::are_all_comparisons_true<std::is_same, column_type, PassedColumns_...>::value;
		}

	public:
		/// <summary> Constructs this matrix with all data also default constructed. </summary>
		constexpr MatrixCM() : columns()
		{
		}
		/// <summary> Copies the passed packed column data to this matrix's column data upon construction. </summary>
		/// <param name="toCopy_">Packed data to copy to this matrix's column data.</param>
		constexpr MatrixCM(const packed_data_type& toCopy_) : columns(toCopy_)
		{
		}
		/// <summary> Copies the passed matrix's data to this matrix upon construction. </summary>
		/// <param name="toCopy_">Matrix to copy to this matrix.</param>
		constexpr MatrixCM(const this_type& toCopy_) : MatrixCM(toCopy_.columns)
		{
		}
		/// <summary> Creates this matrix with its data set via the passed nitializer list. </summary>
		/// <param name="dataInitList_">Initializer list to construct this matrix's data from.</param>
		constexpr MatrixCM(std::initializer_list<packed_data_type> dataInitList_) : columns(dataInitList_)
		{
		}
		/// <summary>
		/// <para> Constructs a matrix from the passed columns. </para>
		/// <para> The passed columns are required to be of this matrix's column_type, and a number of arguments equal to this matrix's num_columns is required. </para>
		/// </summary>
		/// <typeparam name="FirstColumn">Type of the first column. Must match this matrix's column_type.</typeparam>
		/// <typeparam name="...AdditionalColumns_">Types of all sequential columns after the first column. Must match this matrix's column_type.</typeparam>
		/// <typeparam name="RequiresMatchingColumns_">Dummy type used to perform the test to produce clear errors when providing invalid arguments.</typeparam>
		/// <param name="firstColumn_">The first column for the constructed matrix.</param>
		/// <param name="additionalColumns_">All sequential columns after the first column in the matrix. The total number of arguments should equate to this matrix's num_columns.</param>
		template
		<
			typename FirstColumn,
			typename...AdditionalColumns_,
			typename RequiresMatchingColumns_ = std::enable_if_t<_valid_template_constructor_args<FirstColumn, AdditionalColumns_...>()>
		>
		constexpr MatrixCM(const FirstColumn& firstColumn_, const AdditionalColumns_&...additionalColumns_) : columns({firstColumn_, additionalColumns_...})
		{
		}
		/// <summary> Copies the pointed-to column_types to this matrix's data contiguously for the provided number of bytes after default construction. </summary>
		/// <param name="pColumnsToCopy">Pointer to the column data that will be copied after default construction.</param>
		/// <param name="numBytes">The number of bytes to copy. Defaults to the full stride of this matrix's data.</param>
		MatrixCM(const column_type* pColumnsToCopy, std::size_t numBytes = sizeof(packed_data_type)) : MatrixCM()
		{
			memcpy(columns.data(), pColumnsToCopy, numBytes);
		}
		/// <summary> Copies the pointer-to value_types to this matrix's data contiguously for the provided number of bytes after default construction. </summary>
		/// <param name="pDataToCopy">Pointer to the value data that will be copied after default construction.</param>
		/// <param name="numBytes">The number of bytes to copy. Defaults to the full stride of this matrix's data.</param>
		MatrixCM(const value_type* pDataToCopy, std::size_t numBytes = sizeof(packed_data_type)) : MatrixCM()
		{
			memcpy(columns.data(), pDataToCopy, numBytes);
		}

		/// <summary> Returns a copy of the element at the provided point in this matrix, where Column_ is the horizontal index and Row_ is the vertical index. </summary>
		/// <returns>Copy of the value at the specified point in this matrix.</returns>
		template<std::size_t Column_, std::size_t Row_>
		constexpr value_type at() const
		{
			if constexpr (Column_ < NumColumns_)
			{
				if constexpr (Row_ < NumRows_)
				{
					if constexpr (uses_vector_storage)
					{
						return columns[Column_].template at<Row_>();
					}
					else
					{
						return std::get<Row_>(columns[Column_]);
					}
				}
				else
				{
					static_assert(false, "Provided an invalid row index to EmuMath::MatrixCM::at.");
				}
			}
			else
			{
				static_assert(false, "Provided an invalid column index to EmuMath::MatrixCM::at.");
			}
		}
		/// <summary> Returns a reference to the element at the provided point in this matrix, where Column_ is the horizontal index and Row_ is the vertical index. </summary>
		/// <returns>Non-const reference to the element at the specified point in this matrix.</returns>
		template<std::size_t Column_, std::size_t Row_>
		constexpr value_type& at()
		{
			if constexpr (Column_ < NumColumns_)
			{
				if constexpr (Row_ < NumRows_)
				{
					if constexpr (uses_vector_storage)
					{
						return columns[Column_].template at<Row_>();
					}
					else
					{
						return std::get<Row_>(columns[Column_]);
					}
				}
				else
				{
					static_assert(false, "Provided an invalid row index to EmuMath::MatrixCM::at.");
				}
			}
			else
			{
				static_assert(false, "Provided an invalid column index to EmuMath::MatrixCM::at.");
			}
		}

#pragma region CONST_OPERATORS
		constexpr inline this_type operator+(const this_type& rhs) const
		{
			return EmuMath::Helpers::MatrixAddition(*this, rhs);
		}
		constexpr inline this_type operator-(const this_type& rhs) const
		{
			return EmuMath::Helpers::MatrixSubtraction(*this, rhs);
		}
		constexpr inline this_type operator-() const
		{
			return EmuMath::Helpers::MatrixNegation(*this);
		}
		template<typename ScalarMultiplier>
		constexpr inline this_type operator*(ScalarMultiplier rhs) const
		{
			return EmuMath::Helpers::MatrixMultiplication(*this, rhs);
		}
#pragma endregion

#pragma region MATRIX_OPERATIONS
		/// <summary> Returns the transpose of this matrix. The dimensions of the returned matrix will be the reverse of this matrix (e.g. a 4x3 transpose will be 3x4). </summary>
		/// <returns>Transpose matrix to this matrix.</returns>
		MatrixCM<num_rows, num_columns, value_type> Transpose() const
		{
			return EmuMath::Helpers::MatrixTranspose(*this);
		}

		template<typename OutT_ = value_type, typename RequiresSquareMatrix = std::enable_if_t<num_columns == num_rows>>
		OutT_ Trace() const
		{
			return EmuMath::Helpers::MatrixTrace<OutT_>(*this);
		}
#pragma endregion

		/// <summary> Appends a row of this matrix to the passed out stream. </summary>
		/// <param name="stream_">Reference to the stream to append to.</param>
		/// <returns>Reference to the passed output stream.</returns>
		template<std::size_t Row_>
		std::ostream& AppendRowToStream(std::ostream& stream_) const
		{
			if constexpr (Row_ < NumRows_)
			{
				stream_ << "{ ";
				this->_append_row_to_stream_from_column<0, Row_>(stream_);
				stream_ << " }";
			}
			else
			{
				static_assert(false, "Provided an invalid row index to EmuMath::MatrixCM::AppendRowToStream.");
			}
			return stream_;
		}

		/// <summary> Returns a collection of data representing a copy of an individual row within this matrix. </summary>
		/// <returns>Specified row of this matrix. If inclusively between 2-4 dimensions, the row will be an EmuMath Vector, otherwise a std::array.</returns>
		template<std::size_t Row_>
		row_type GetRow() const
		{
			return EmuMath::Helpers::MatrixGetRow<Row_>(*this);
		}
		/// <summary> Returns a copy of an individual column of this matrix. Identical to copying ThisMatrix.columns[Column_]. </summary>
		/// <returns>Copy of the column at the specified index.</returns>
		template<std::size_t Column_>
		column_type GetColumn() const
		{
			return EmuMath::Helpers::MatrixGetColumn<Column_>(*this);
		}

		/// <summary>
		/// <para>
		///		The data within this matrix, stored contiguously as columns 
		///		(i.e. all rows in column 0 will appear in order in memory immediately before the rows of column 1).
		/// </para>
		/// </summary>
		packed_data_type columns;

	private:
		/// <summary> Appends a row to a stream from the passed column. Uses recursion to go through all columns within the row, appending each to the stream. </summary>
		/// <param name="stream_">Stream to append to.</param>
		template<std::size_t Column_, std::size_t Row_>
		void _append_row_to_stream_from_column(std::ostream& stream_) const
		{
			stream_ << this->at<Column_, Row_>();
			if constexpr ((Column_ + 1) < NumColumns_)
			{
				stream_ << ", ";
				this->_append_row_to_stream_from_column<Column_ + 1, Row_>(stream_);
			}
		}
	};
}

template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool CreateInSStream = true, std::size_t CurrentRow_ = 0>
inline std::ostream& operator<<(std::ostream& stream_, const EmuMath::MatrixCM<NumColumns_, NumRows_, T_>& matrix_)
{
	if constexpr (CurrentRow_ < NumRows_)
	{
		if constexpr (CreateInSStream)
		{
			std::ostringstream str;
			operator<<<NumColumns_, NumRows_, T_, false, CurrentRow_>(str, matrix_);
			stream_ << str.str();
		}
		else
		{
			matrix_.AppendRowToStream<CurrentRow_>(stream_);
			if constexpr ((CurrentRow_ + 1) < NumRows_)
			{
				stream_ << "\n";
				operator<<<NumColumns_, NumRows_, T_, false, CurrentRow_ + 1>(stream_, matrix_);
			}
		}
	}
	return stream_;
}

#endif
