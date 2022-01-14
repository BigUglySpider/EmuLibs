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

		using matrix_vector_type = typename matrix_info::matrix_vector_type;
		using stored_type = typename matrix_info::stored_type;
		using value_type = typename matrix_info::value_type;
		using value_type_uq = typename matrix_info::value_type_uq;
		using preferred_floating_point = typename matrix_info::preferred_floating_point;

		using column_get_ref_type = typename matrix_info::column_get_ref_type;
		using column_get_const_ref_type = typename matrix_info::column_get_const_ref_type;
		using row_get_ref_type = typename matrix_info::row_get_ref_type;
		using row_get_const_ref_type = typename matrix_info::row_get_const_ref_type;
#pragma endregion

#pragma region HELPER_STATIC_FUNCS
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

		/// <summary>
		/// <para> Unflattens the provided index into a column index and a row index for this Matrix type. </para>
		/// <para> Output contained type may be modified, but is recommended to stick to std::size_t. </para>
		/// </summary>
		/// <param name="flattened_index_">
		///		Flattened index to unflatten. This will always be read in column-major order
		///		(i.e. index x+1 is the next item in a column immediately after x, or the next column if x is the end of a column).
		/// </param>
		/// <returns>Pair of std::size_t, containing the unflattened column index in first, and the unflattened row index in second.</returns>
		[[nodiscard]] static constexpr inline std::pair<std::size_t, std::size_t> unflatten_index(std::size_t flattened_index_)
		{
			if constexpr(size != 0)
			{
				return std::pair<std::size_t, std::size_t>
				(
					flattened_index_ / num_rows,
					flattened_index_ % num_rows
				);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<T_>(),
					"Attempted to unflatten an index for an EmuMath Matrix, but the size of the Matrix is 0, meaning a conversion cannot be made due to integral divide-by-0."
				);
			}
		}

		[[nodiscard]] static constexpr inline bool is_default_constructible()
		{
			return std::is_default_constructible_v<matrix_vector_type>;
		}

		template<typename...Args_>
		[[nodiscard]] static constexpr inline bool is_constructible()
		{
			return
			(
				sizeof...(Args_) == size &&
				size > 1 &&
				EmuCore::TMP::variadic_and_v<std::is_constructible_v<stored_type, decltype(std::forward<Args_>(std::declval<Args_>()))>...>
			);
		}

		[[nodiscard]] static constexpr inline bool is_const_copy_constructible()
		{
			return std::is_constructible_v<matrix_vector_type, const matrix_vector_type&>;
		}

		[[nodiscard]] static constexpr inline bool is_non_const_copy_constructible()
		{
			return std::is_constructible_v<matrix_vector_type, matrix_vector_type&>;
		}

		[[nodiscard]] static constexpr inline bool is_move_constructible()
		{
			return std::is_constructible_v<matrix_vector_type, matrix_vector_type&&>;
		}
#pragma endregion

#pragma region CONSTRUCTORS
	public:
		template<typename = std::enable_if_t<is_default_constructible()>>
		constexpr inline Matrix() : _data()
		{
		}

		template<typename = std::enable_if_t<is_const_copy_constructible()>>
		constexpr inline Matrix(const this_type& to_copy_) : _data(to_copy_._data)
		{
		}

		template<typename = std::enable_if_t<is_non_const_copy_constructible()>>
		constexpr inline Matrix(this_type& to_copy_) : _data(to_copy_._data)
		{
		}

		template<typename = std::enable_if_t<is_move_constructible()>>
		constexpr inline Matrix(this_type&& to_move_) : _data(std::move(to_move_._data))
		{
		}

		template<typename...Args_, typename = std::enable_if_t<is_constructible<Args_...>()>>
		explicit constexpr inline Matrix(Args_&&...contiguous_args_) : _data(_make_data(std::make_index_sequence<num_major_elements>(), std::forward<Args_>(contiguous_args_)...))
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
					constexpr std::size_t major_index_ = get_major_index(ColumnIndex_, RowIndex_);
					constexpr std::size_t non_major_index_ = get_non_major_index(ColumnIndex_, RowIndex_);
					return _data.template at<major_index_>().template at<non_major_index_>();
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
		/// <para> Accesses the element at the provided FlattenedIndex_ within this Matrix, with compile-time validity checks. </para>
		/// <para> If the flattened index exceeds this Matrix's size, or the unflattened indices are deemed invalid, a static_assert will be triggered. </para>
		/// </summary>
		/// <returns>Reference to the element at the provided column-major index within this Matrix.</returns>
		template<std::size_t FlattenedIndex_>
		[[nodiscard]] constexpr inline value_type& at()
		{
			if constexpr (FlattenedIndex_ < size)
			{
				// Assuming we reach this point, all indices should be valid, but we want to maintain suitable static_assert messages in case of inaccurate calculations
				constexpr auto unflattened_indices_ = unflatten_index(FlattenedIndex_);
				constexpr std::size_t column_index_ = unflattened_indices_.first;

				if constexpr (column_index_ < num_columns)
				{
					constexpr std::size_t row_index_ = unflattened_indices_.second;
					if constexpr (row_index_ < num_rows)
					{
						constexpr std::size_t major_index_ = get_major_index(column_index_, row_index_);
						constexpr std::size_t non_major_index_ = get_non_major_index(column_index_, row_index_);
						return _data.template at<major_index_>().template at<non_major_index_>();
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<std::size_t, row_index_>(),
							"Attempted to access a flattened index within an EmuMath Matrix, but the determined row index is invalid."
						);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<std::size_t, column_index_>(),
						"Attempted to access a flattened index within an EmuMath Matrix, but the determined column index is invalid."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, FlattenedIndex_>(),
					"Attempted to access a flattened index within an EmuMath Matrix, but the provided FlattenedIndex_ exceeds the valid range. The inclusive valid flattened index range is 0:(size-1)."
				);
			}
		}

		template<std::size_t FlattenedIndex_>
		[[nodiscard]] constexpr inline const value_type& at() const
		{
			return const_cast<this_type*>(this)->template at<FlattenedIndex_>();
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
			if constexpr (size > 0)
			{
				constexpr bool constexpr_str_ = __cplusplus >= 201907L;
				if ((column_index_ < num_columns) && (row_index_ < num_rows))
				{
					return _data[get_major_index(column_index_, row_index_)][get_non_major_index(column_index_, row_index_)];
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
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<T_>(),
					"Attempted to access a non-theoretical index of a 0-sized EmuMath Matrix."
				);
			}
		}

		[[nodiscard]] constexpr inline const value_type& at(std::size_t column_index_, std::size_t row_index_) const
		{
			return const_cast<this_type*>(this)->at(column_index_, row_index_);
		}

		/// <summary>
		/// <para> Accesses the element at the provided flattened_index_ within this Matrix, with runtime-time validity checks. </para>
		/// <para> If the flattened index exceeds this Matrix's size, or the unflattened indices are deemed invalid, a runtime exception will be thrown. </para>
		/// </summary>
		/// <param name="flattened_index_">: Column-major flattened index of the element to retrieve.</param>
		/// <returns>Reference to the element at the provided column-major index within this Matrix.</returns>
		[[nodiscard]] constexpr inline value_type& at(std::size_t flattened_index_)
		{
			if constexpr (size > 0)
			{
				auto unflattened_indices_ = unflatten_index(flattened_index_);
				if ((unflattened_indices_.first < num_columns) && (unflattened_indices_.second < num_rows))
				{
					return operator()(unflattened_indices_.first, unflattened_indices_.second);
				}
				else
				{
					constexpr bool constexpr_str_ = __cplusplus >= 201907L;
					if constexpr (constexpr_str_)
					{
						// We can provide some extra information if we have access to constexpr strings
						// --- This is to allow `at(index_)` to still satisfy constexpr constraints in standards before C++20
						std::string out_str_;
						out_str_.reserve(160); // Reserves enough space for all literal chars, alongside some extra for range and index after conversion.
						out_str_ += "Attempted to access an invalid flattened index of an EmuMath Matrix.\nProvided index: ";
						out_str_ += std::to_string(flattened_index_);
						out_str_ += "\nInclusive valid flattened index range: 0:";
						out_str_ += std::to_string(size - 1);
						throw std::out_of_range(out_str_);
					}
					else
					{
						throw std::out_of_range("Attempted to access an invalid flattened index of an EmuMath Matrix.");
					}
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<T_>(),
					"Attempted to access a non-theoretical index of a 0-sized EmuMath Matrix."
				);
			}
		}

		[[nodiscard]] constexpr inline const value_type& at(std::size_t flattened_index_) const
		{
			return const_cast<this_type*>(this)->at(flattened_index_);
		}

		/// <summary>
		/// <para> Accesses the element at the provided indices within this Matrix, with no validity checks. </para>
		/// <para> If either ColumnIndex_ or RowIndex_, behaviour is undefined. </para>
		/// </summary>
		/// <returns>Reference to the element at the provided index within this Matrix.</returns>
		[[nodiscard]] constexpr inline value_type& operator()(std::size_t column_index_, std::size_t row_index_)
		{
			return _data[get_major_index(column_index_, row_index_)][get_non_major_index(column_index_, row_index_)];
		}

		[[nodiscard]] constexpr inline const value_type& operator()(std::size_t column_index_, std::size_t row_index_) const
		{
			return const_cast<this_type*>(this)->operator()(column_index_, row_index_);
		}

		/// <summary>
		/// <para> Accesses the element at the provided flattened_index_ within this Matrix. </para>
		/// <para> If the flattened index exceeds this Matrix's size, or the unflattened indices are deemed invalid, behaviour is undefined. </para>
		/// </summary>
		/// <param name="flattened_index_">: Column-major flattened index of the element to retrieve.</param>
		/// <returns>Reference to the element at the provided column-major index within this Matrix.</returns>
		[[nodiscard]] constexpr inline value_type& operator[](std::size_t flattened_index_)
		{
			auto unflattened_indices_ = unflatten_index(flattened_index_);
			return this->operator()(unflattened_indices_.first, unflattened_indices_.second);
		}

		[[nodiscard]] constexpr inline const value_type& operator[](std::size_t flattened_index_) const
		{
			return const_cast<this_type*>(this)->operator[](flattened_index_);
		}

		/// <summary>
		/// <para> Accesses a contiguous data pointer to the elements of this Matrix, starting from an element at the provided Offset_. </para>
		/// <para> Offset_: Index to retrieve a pointer to. Defaults to 0. </para>
		/// <para> This function is not available for reference-containing matrices. </para>
		/// </summary>
		/// <returns>Pointer to the value at the provided index.</returns>
		template<std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline value_type* data()
		{
			if constexpr(!contains_ref)
			{
				if constexpr (size != 0)
				{
					if constexpr (Offset_ < size)
					{
						if constexpr (Offset_ == 0)
						{
							return _data.template at<0>().data();
						}
						else
						{
							return (_data.template at<0>().data()) + Offset_;
						}
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<std::size_t, Offset_>(),
							"Attempted to access a pointer to the contiguous data of an EmuMath Matrix starting from a provided index Offset_, but the provided Offset_ was greater than the total number of elements within the Matrix."
						);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<T_>(),
						"Attempted to access a pointer to the contiguous data of an EmuMath Matrix, but the Matrix type contains no non-theoretical elements."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<T_>(),
					"Attempted to access a pointer to the contiguous data of an EmuMath Matrix which contains references. This behaviour is not allowed as references are not guaranteed to be contiguous."
				);
			}
		}

		template<std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline const value_type* data() const
		{
			return const_cast<this_type*>(this)->template data<Offset_>();
		}

		/// <summary>
		/// <para> Accesses the column at the provided ColumnIndex_ within this Matrix. </para>
		/// <para> If this Matrix is column-major: This will be a direct reference to the specified column. </para>
		/// <para> If this Matrix is not column-major: This will be an EmuMath Vector of reference to elements at respective points within the specified column. </para>
		/// </summary>
		/// <returns>EmuMath Vector referencing the specified column within this Matrix.</returns>
		template<std::size_t ColumnIndex_>
		[[nodiscard]] constexpr inline column_get_ref_type GetColumn()
		{
			if constexpr (ColumnIndex_ < num_columns)
			{
				if constexpr (is_column_major)
				{
					return _data.template at<ColumnIndex_>();
				}
				else
				{
					return _make_non_major_vector<ColumnIndex_, column_get_ref_type>(std::make_index_sequence<num_rows>());
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, ColumnIndex_>(),
					"Attempted to access a column within an EmuMath Matrix, but the provided ColumnIndex_ is invalid. The inclusive valid column index range is 0:(num_columns - 1)."
				);
			}
		}

		template<std::size_t ColumnIndex_>
		[[nodiscard]] constexpr inline column_get_const_ref_type GetColumn() const
		{
			if constexpr (ColumnIndex_ < num_columns)
			{
				if constexpr (is_column_major)
				{
					return _data.template at<ColumnIndex_>();
				}
				else
				{
					return _make_non_major_vector<ColumnIndex_, column_get_const_ref_type>(std::make_index_sequence<num_rows>());
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, ColumnIndex_>(),
					"Attempted to const-access a column within an EmuMath Matrix, but the provided ColumnIndex_ is invalid. The inclusive valid column index range is 0:(num_columns - 1)."
				);
			}
		}

		/// <summary>
		/// <para> Accesses the row at the provided RowIndex_ within this Matrix. </para>
		/// <para> If this Matrix is column-major: This will be an EmuMath Vector of reference to elements at respective points within the specified row. </para>
		/// <para> If this Matrix is not column-major: This will be a direct reference to the specified row. </para>
		/// </summary>
		/// <returns>EmuMath Vector referencing the specified row within this Matrix.</returns>
		template<std::size_t RowIndex_>
		[[nodiscard]] constexpr inline row_get_ref_type GetRow()
		{
			if constexpr (RowIndex_ < num_rows)
			{
				if constexpr (is_column_major)
				{
					return _make_non_major_vector<RowIndex_, row_get_ref_type>(std::make_index_sequence<num_columns>());
				}
				else
				{
					return _data.template at<RowIndex_>();
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, RowIndex_>(),
					"Attempted to access a row within an EmuMath Matrix, but the provided RowIndex_ is invalid. The inclusive valid row index range is 0:(num_rows - 1)."
				);
			}
		}

		template<std::size_t RowIndex_>
		[[nodiscard]] constexpr inline row_get_const_ref_type GetRow() const
		{
			if constexpr (RowIndex_ < num_rows)
			{
				if constexpr (is_column_major)
				{
					return _make_non_major_vector<RowIndex_, row_get_const_ref_type>(std::make_index_sequence<num_columns>());
				}
				else
				{
					return _data.template at<RowIndex_>();
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, RowIndex_>(),
					"Attempted to access a row within an EmuMath Matrix, but the provided RowIndex_ is invalid. The inclusive valid row index range is 0:(num_rows - 1)."
				);
			}
		}
#pragma endregion

#pragma region STREAM_FUNCS
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

		template<std::size_t NonMajorIndex_, class Out_, std::size_t...MajorIndices_>
		[[nodiscard]] constexpr inline Out_ _make_non_major_vector(std::index_sequence<MajorIndices_...> major_indices_)
		{
			if constexpr (is_column_major)
			{
				return Out_(this->template at<MajorIndices_, NonMajorIndex_>()...);
			}
			else
			{
				return Out_(this->template at<NonMajorIndex_, MajorIndices_>()...);
			}
		}

		template<std::size_t MajorIndex_, typename...Args_, std::size_t...NonMajorIndices_>
		[[nodiscard]] static constexpr inline typename matrix_vector_type::stored_type _make_major_index
		(
			std::index_sequence<NonMajorIndices_...> non_major_indices_,
			std::tuple<Args_...>& tuple_of_args_
		)
		{
			constexpr std::size_t major_offset_ = MajorIndex_ * num_non_major_elements;
			return typename matrix_vector_type::stored_type
			(
				std::get<major_offset_ + NonMajorIndices_>(tuple_of_args_)...
			);
		}

		template<typename...Args_, std::size_t...MajorIndices_>
		[[nodiscard]] static constexpr inline matrix_vector_type _make_data(std::index_sequence<MajorIndices_...> major_indices_, Args_&&...args_)
		{
			auto tuple_of_args_ = std::forward_as_tuple(std::forward<Args_>(args_)...);
			return matrix_vector_type
			(
				_make_major_index<MajorIndices_>
				(
					std::make_index_sequence<num_non_major_elements>(),
					tuple_of_args_
				)...
			);
		}
	};
}

#endif
