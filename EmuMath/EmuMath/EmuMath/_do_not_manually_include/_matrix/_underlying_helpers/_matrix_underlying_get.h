#ifndef EMU_MATH_MATRIX_UNDERLYING_GET_H_INC_
#define EMU_MATH_MATRIX_UNDERLYING_GET_H_INC_ 1

#include "_matrix_tmp.h"

namespace EmuMath::Helpers::_matrix_underlying
{
	// NON-CONTAINED GET
	template<class Matrix_, typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<Matrix_>>>
	[[nodiscard]] constexpr inline typename EmuCore::TMP::remove_ref_cv_t<Matrix_>::value_type_uq _matrix_get_non_contained()
	{
		if constexpr (std::is_default_constructible_v<typename Matrix_::value_type_uq>)
		{
			return typename Matrix_::value_type_uq();
		}
		else if constexpr (EmuCore::TMP::is_valid_make_constant_call<typename Matrix_::value_type_uq, 0, float>())
		{
			return EmuCore::TMP::make_constant<typename Matrix_::value_type_uq, 0, float>();
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Matrix_>(),
				"Attempted to create a non-contained element of an EmuMath Matrix, but the provided Matrix_ type cannot have its unqualified value type default-constructed or constructed with a constant of either 0 or 0.0f."
			);
		}
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq _matrix_get_non_contained()
	{
		return _matrix_get_non_contained<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>();
	}

	// NON-CONTAINED COLUMN GET
	template<class Matrix_, typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<Matrix_>>>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_non_contained_column<Matrix_>::type _matrix_get_column_non_contained()
	{
		using out_type = typename EmuMath::TMP::matrix_non_contained_column<Matrix_>::type;
		if constexpr (std::is_default_constructible_v<out_type>)
		{
			return out_type();
		}
		else if constexpr (EmuCore::TMP::is_valid_make_constant_call<out_type, 0, float>())
		{
			return EmuCore::TMP::make_constant<out_type, 0, float>();
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Matrix_>(),
				"Attempted to create a non-contained column of an EmuMath Matrix, but the determined output type cannot be default-constructed or constructed with an argument of 0 or 0.0f."
			);
		}
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_non_contained_column<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>::type
	_matrix_get_column_non_contained()
	{
		return _matrix_get_column_non_contained<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>();
	}

	// NON-CONTAINED ROW GET
	template<class Matrix_, typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<Matrix_>>>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_non_contained_row<Matrix_>::type _matrix_get_row_non_contained()
	{
		using out_type = typename EmuMath::TMP::matrix_non_contained_row<Matrix_>::type;
		if constexpr (std::is_default_constructible_v<out_type>)
		{
			return out_type();
		}
		else if constexpr (EmuCore::TMP::is_valid_make_constant_call<out_type, 0, float>())
		{
			return EmuCore::TMP::make_constant<out_type, 0, float>();
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Matrix_>(),
				"Attempted to create a non-contained row of an EmuMath Matrix, but the determined output type cannot be default-constructed or constructed with an argument of 0 or 0.0f."
			);
		}
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_non_contained_row<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>::type
	_matrix_get_row_non_contained()
	{
		return _matrix_get_row_non_contained<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>();
	}

	// NON-CONTAINED MAJOR GET
	template<class Matrix_, typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<Matrix_>>>
	[[nodiscard]] constexpr inline typename std::conditional
	<
		EmuCore::TMP::remove_ref_cv_t<Matrix_>::is_column_major,
		decltype(_matrix_get_column_non_contained<Matrix_>()),
		decltype(_matrix_get_row_non_contained<Matrix_>())
	>::type _matrix_get_major_non_contained()
	{
		if constexpr (EmuCore::TMP::remove_ref_cv_t<Matrix_>::is_column_major)
		{
			return _matrix_get_column_non_contained<Matrix_>();
		}
		else
		{
			return _matrix_get_row_non_contained<Matrix_>();
		}
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline decltype(_matrix_get_major_non_contained<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>())
	_matrix_get_major_non_contained()
	{
		return _matrix_get_major_non_contained<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>();
	}

	// NON-CONTAINED NON-MAJOR GET
	template<class Matrix_, typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<Matrix_>>>
	[[nodiscard]] constexpr inline typename std::conditional
	<
		EmuCore::TMP::remove_ref_cv_t<Matrix_>::is_column_major,
		decltype(_matrix_get_row_non_contained<Matrix_>()),
		decltype(_matrix_get_column_non_contained<Matrix_>())
	>::type _matrix_get_non_major_non_contained()
	{
		if constexpr (EmuCore::TMP::remove_ref_cv_t<Matrix_>::is_column_major)
		{
			return _matrix_get_row_non_contained<Matrix_>();
		}
		else
		{
			return _matrix_get_column_non_contained<Matrix_>();
		}
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline decltype(_matrix_get_non_major_non_contained<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>())
	_matrix_get_non_major_non_contained()
	{
		return _matrix_get_non_major_non_contained<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>();
	}

	// FLATTENED GETS
	template<std::size_t FlattenedIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type& _matrix_get
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template at<FlattenedIndex_>();
	}

	template<std::size_t FlattenedIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline const typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type& _matrix_get
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template at<FlattenedIndex_>();
	}

	// FLATTENED THEORETICAL GETS
	template<std::size_t FlattenedIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_flattened_theoretical_get_result<FlattenedIndex_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	_matrix_get_theoretical(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		using matrix_type = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		if constexpr (EmuMath::TMP::is_theoretical_flattened_matrix_index<FlattenedIndex_, matrix_type>::value)
		{
			return _matrix_get_non_contained<matrix_type>();
		}
		else
		{
			return matrix_.template at<FlattenedIndex_>();
		}
	}

	template<std::size_t FlattenedIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_flattened_theoretical_get_result<FlattenedIndex_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	_matrix_get_theoretical(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		using matrix_type = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		if constexpr (EmuMath::TMP::is_theoretical_flattened_matrix_index<FlattenedIndex_, matrix_type>::value)
		{
			return _matrix_get_non_contained<matrix_type>();
		}
		else
		{
			return matrix_.template at<FlattenedIndex_>();
		}
	}

	// COLUMN-ROW GETS
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type& _matrix_get
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template at<ColumnIndex_, RowIndex_>();
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline const typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type& _matrix_get
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template at<ColumnIndex_, RowIndex_>();
	}

	// COLUMN-ROW THEORETICAL GETS
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_theoretical_get_result<ColumnIndex_, RowIndex_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	_matrix_get_theoretical(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		using matrix_type = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		if constexpr (EmuMath::TMP::is_theoretical_matrix_index<ColumnIndex_, RowIndex_, matrix_type>::value)
		{
			return _matrix_get_non_contained<matrix_type>();
		}
		else
		{
			return matrix_.template at<ColumnIndex_, RowIndex_>();
		}
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_theoretical_get_result<ColumnIndex_, RowIndex_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	_matrix_get_theoretical(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		using matrix_type = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		if constexpr (EmuMath::TMP::is_theoretical_matrix_index<ColumnIndex_, RowIndex_, matrix_type>::value)
		{
			return _matrix_get_non_contained<matrix_type>();
		}
		else
		{
			return matrix_.template at<ColumnIndex_, RowIndex_>();
		}
	}

	// COLUMN GETS
	template<std::size_t ColumnIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::column_get_ref_type _matrix_get_column
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template GetColumn<ColumnIndex_>();
	}

	template<std::size_t ColumnIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::column_get_const_ref_type _matrix_get_column
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template GetColumn<ColumnIndex_>();
	}

	// COLUMN THEORETICAL GETS
	template<std::size_t ColumnIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_column_theoretical_get_result<ColumnIndex_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	_matrix_get_column_theoretical(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		using matrix_type = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		if constexpr (EmuMath::TMP::is_theoretical_matrix_column_index<ColumnIndex_, matrix_type>::value)
		{
			return _matrix_get_column_non_contained<matrix_type>();
		}
		else
		{
			return matrix_.template GetColumn<ColumnIndex_>();
		}
	}

	template<std::size_t ColumnIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_column_theoretical_get_result<ColumnIndex_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	_matrix_get_column_theoretical(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		using matrix_type = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		if constexpr (EmuMath::TMP::is_theoretical_matrix_column_index<ColumnIndex_, matrix_type>::value)
		{
			return _matrix_get_column_non_contained<matrix_type>();
		}
		else
		{
			return matrix_.template GetColumn<ColumnIndex_>();
		}
	}

	// ROW GETS
	template<std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::row_get_ref_type _matrix_get_row
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template GetRow<RowIndex_>();
	}

	template<std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::row_get_const_ref_type _matrix_get_row
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template GetRow<RowIndex_>();
	}

	// ROW THEORETICAL GETS
	template<std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_row_theoretical_get_result<RowIndex_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	_matrix_get_row_theoretical(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		using matrix_type = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		if constexpr (EmuMath::TMP::is_theoretical_matrix_row_index<RowIndex_, matrix_type>::value)
		{
			return _matrix_get_row_non_contained<matrix_type>();
		}
		else
		{
			return matrix_.template GetRow<RowIndex_>();
		}
	}

	template<std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_row_theoretical_get_result<RowIndex_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	_matrix_get_row_theoretical(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		using matrix_type = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		if constexpr (EmuMath::TMP::is_theoretical_matrix_row_index<RowIndex_, matrix_type>::value)
		{
			return _matrix_get_row_non_contained<matrix_type>();
		}
		else
		{
			return matrix_.template GetRow<RowIndex_>();
		}
	}

	// MAJOR GETS
	template<std::size_t MajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::major_get_ref_type _matrix_get_major
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template GetMajor<MajorIndex_>();
	}

	template<std::size_t MajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::major_get_const_ref_type _matrix_get_major
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template GetMajor<MajorIndex_>();
	}

	template<std::size_t MajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_major_theoretical_get_result<MajorIndex_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	_matrix_get_major_theoretical(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		using matrix_type = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		if constexpr (EmuMath::TMP::is_theoretical_matrix_major_index<MajorIndex_, matrix_type>::value)
		{
			return _matrix_get_major_non_contained<matrix_type>();
		}
		else
		{
			return matrix_.template GetMajor<MajorIndex_>();
		}
	}

	template<std::size_t MajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_major_theoretical_get_result<MajorIndex_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	_matrix_get_major_theoretical(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		using matrix_type = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		if constexpr (EmuMath::TMP::is_theoretical_matrix_major_index<MajorIndex_, matrix_type>::value)
		{
			return _matrix_get_major_non_contained<matrix_type>();
		}
		else
		{
			return matrix_.template GetMajor<MajorIndex_>();
		}
	}

	// NON-MAJOR GETS
	template<std::size_t NonMajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::non_major_get_ref_type _matrix_get_non_major
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template GetNonMajor<NonMajorIndex_>();
	}

	template<std::size_t NonMajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::non_major_get_const_ref_type _matrix_get_non_major
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template GetNonMajor<NonMajorIndex_>();
	}

	// NON-MAJOR THEORETICAL GETS
	template<std::size_t NonMajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_non_major_theoretical_get_result<NonMajorIndex_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	_matrix_get_non_major_theoretical(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		using matrix_type = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		if constexpr (EmuMath::TMP::is_theoretical_matrix_non_major_index<NonMajorIndex_, matrix_type>::value)
		{
			return _matrix_get_non_major_non_contained<matrix_type>();
		}
		else
		{
			return matrix_.template GetNonMajor<NonMajorIndex_>();
		}
	}

	template<std::size_t NonMajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_non_major_theoretical_get_result<NonMajorIndex_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	_matrix_get_non_major_theoretical(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		using matrix_type = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		if constexpr (EmuMath::TMP::is_theoretical_matrix_non_major_index<NonMajorIndex_, matrix_type>::value)
		{
			return _matrix_get_non_major_non_contained<matrix_type>();
		}
		else
		{
			return matrix_.template GetNonMajor<NonMajorIndex_>();
		}
	}

	template<class OutVector_, class Matrix_, std::size_t...Indices_>
	[[nodiscard]] constexpr inline OutVector_ _matrix_make_main_diagonal_vector(Matrix_& matrix_ref_, std::index_sequence<Indices_...> indices_)
	{
		if constexpr (std::is_constructible_v<OutVector_, decltype(_matrix_get_theoretical<Indices_, Indices_>(matrix_ref_))...>)
		{
			return OutVector_(_matrix_get_theoretical<Indices_, Indices_>(matrix_ref_)...);
		}
		else
		{
			using out_stored_type = typename EmuCore::TMP::remove_ref_cv_t<OutVector_>::stored_type;
			constexpr bool constructible_from_stored_type = std::is_constructible_v<OutVector_, EmuCore::TMP::type_and_discard_val_t<out_stored_type, Indices_>...>;
			if constexpr (constructible_from_stored_type)
			{
				constexpr bool valid_for_stored_type_construction_ = EmuCore::TMP::variadic_and_v
				<
					std::is_constructible_v<out_stored_type, decltype(_matrix_get_theoretical<Indices_, Indices_>(matrix_ref_))>...
				>;

				if constexpr (valid_for_stored_type_construction_)
				{
					return OutVector_
					(
						out_stored_type(_matrix_get_theoretical<Indices_, Indices_>(matrix_ref_))...
					);
				}
				else
				{
					constexpr bool valid_for_stored_type_static_cast_ = EmuCore::TMP::variadic_and_v
					<
						EmuCore::TMP::is_static_castable_v<decltype(_matrix_get_theoretical<Indices_, Indices_>(matrix_ref_)), out_stored_type>...
					>;

					if constexpr (valid_for_stored_type_static_cast_)
					{
						return OutVector_
						(
							static_cast<out_stored_type>(_matrix_get_theoretical<Indices_, Indices_>(matrix_ref_))...
						);
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<OutVector_>(),
							"Attempted to retrieve an EmuMath Vector of the main diagonal within an EmuMath Matrix, but neither the provided output Vector nor its stored_type could not be formed from accessing respective main-diagonal indices within the Matrix."
						);
					}
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutVector_>(),
					"Attempted to retrieve an EmuMath Vector of the main diagonal within an EmuMath Matrix, but the provided output Vector could not be formed from accessing respective main-diagonal indices within the Matrix, and cannot be constructed from its stored_type."
				);
			}
		}
	}

	template<std::size_t Offset_, std::size_t OutSize_, typename OutT_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _matrix_get_main_diagonal(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		using index_sequence = EmuCore::TMP::make_offset_index_sequence<Offset_, OutSize_>;
		return _matrix_make_main_diagonal_vector<EmuMath::Vector<OutSize_, OutT_>, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>(matrix_, index_sequence());
	}

	template<std::size_t Offset_, std::size_t OutSize_, typename OutT_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _matrix_get_main_diagonal(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		using index_sequence = EmuCore::TMP::make_offset_index_sequence<Offset_, OutSize_>;
		return _matrix_make_main_diagonal_vector<EmuMath::Vector<OutSize_, OutT_>, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>(matrix_, index_sequence());
	}
}

#endif
