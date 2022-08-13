#ifndef EMU_MATH_MATRIX_TMP_H_INC_
#define EMU_MATH_MATRIX_TMP_H_INC_ 1

#include "../../../../EmuCore/TMPHelpers/TypeConvertors.h"
#include "../../../Quaternion.h"
#include "../../../Vector.h"
#include <type_traits>

namespace EmuMath
{
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_ = true>
	struct Matrix;
}

namespace EmuMath::TMP
{
	/// <summary>
	/// <para> Type to determine if the passed T_ is a type of EmuMath Matrix. </para>
	/// <para> The value will be true if T_ is a reference to an EmuMath Matrix, and ignores const/ref qualifiers. </para>
	/// </summary>
	template<typename T_>
	struct is_emu_matrix
	{
		static constexpr bool value = std::conditional_t
		<
			std::is_same_v<T_, EmuCore::TMP::remove_ref_cv_t<T_>>,
			std::false_type,
			is_emu_matrix<EmuCore::TMP::remove_ref_cv_t<T_>>
		>::value;
	};
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	struct is_emu_matrix<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>
	{
		static constexpr bool value = true;
	};
	template<typename T_>
	static constexpr bool is_emu_matrix_v = is_emu_matrix<T_>::value;

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_>
	struct is_theoretical_matrix_index
	{
	private:
		template<class In_, bool IsMatrix_ = EmuMath::TMP::is_emu_matrix_v<In_>>
		struct _value_finder_template
		{
			static constexpr bool valid_column_index = false;
			static constexpr bool valid_row_index = false;
			static constexpr bool is_theoretical_index = false;
		};

		template<class In_>
		struct _value_finder_template<In_, true>
		{
		private:
			using _in_uq = EmuCore::TMP::remove_ref_cv_t<In_>;

		public:
			static constexpr bool valid_column_index = ColumnIndex_ < _in_uq::num_columns;
			static constexpr bool valid_row_index = RowIndex_ < _in_uq::num_rows;
			static constexpr bool is_theoretical_index = !(valid_column_index && valid_row_index);
		};

		using _value_finder = _value_finder_template<Matrix_>;

	public:
		static constexpr bool valid_column_index = _value_finder::valid_column_index;
		static constexpr bool valid_row_index = _value_finder::valid_row_index;
		static constexpr bool value = _value_finder::is_theoretical_index;
	};

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_>
	struct matrix_theoretical_get_result
	{
	private:
		template<class In_, bool IsMatrix_ = EmuMath::TMP::is_emu_matrix_v<In_>>
		struct _type_finder_template
		{
			static constexpr bool valid_column_index = false;
			static constexpr bool valid_row_index = false;
			static constexpr bool is_theoretical_index = false;
			using type = void;
		};

		template<class In_>
		struct _type_finder_template<In_, true>
		{
		private:
			using _in_uq = EmuCore::TMP::remove_ref_cv_t<In_>;
			using _is_theoretical = EmuMath::TMP::is_theoretical_matrix_index<ColumnIndex_, RowIndex_, _in_uq>;

		public:
			static constexpr bool valid_column_index = _is_theoretical::valid_column_index;
			static constexpr bool valid_row_index = _is_theoretical::valid_row_index;
			static constexpr bool is_theoretical_index = _is_theoretical::value;
			using type = typename std::conditional
			<
				is_theoretical_index,
				typename _in_uq::value_type_uq,
				typename EmuCore::TMP::conditional_const<std::is_const_v<std::remove_reference_t<In_>>, typename _in_uq::value_type&>::type
			>::type;
		};

		using _type_finder = _type_finder_template<Matrix_>;

	public:
		static constexpr bool valid_column_index = _type_finder::valid_column_index;
		static constexpr bool valid_row_index = _type_finder::valid_row_index;
		static constexpr bool is_theoretical_index = _type_finder::is_theoretical_index;

		using type = typename _type_finder::type;
	};

	template<std::size_t FlattenedIndex_, class Matrix_>
	struct is_theoretical_flattened_matrix_index
	{
	private:
		template<class In_, bool IsMatrix_ = EmuMath::TMP::is_emu_matrix_v<Matrix_>>
		struct _value_finder
		{
			static constexpr bool value = false;
		};

		template<class In_>
		struct _value_finder<In_, true>
		{
			static constexpr bool value = FlattenedIndex_ > EmuCore::TMP::remove_ref_cv_t<In_>::size;
		};

	public:
		static constexpr bool value = _value_finder<Matrix_>::value;
	};

	template<std::size_t FlattenedIndex_, class Matrix_>
	struct matrix_flattened_theoretical_get_result
	{
	private:
		template<class In_, bool = EmuMath::TMP::is_emu_matrix_v<In_>>
		struct _type_finder_template
		{
			static constexpr bool is_theoretical_index = false;
			using type = void;
		};

		template<class In_>
		struct _type_finder_template<In_, true>
		{
		private:
			using _in_uq = EmuCore::TMP::remove_ref_cv_t<In_>;

		public:
			static constexpr bool is_theoretical_index = is_theoretical_flattened_matrix_index<FlattenedIndex_, In_>::value;
			using type = typename std::conditional
			<
				is_theoretical_index,
				typename _in_uq::value_type_uq,
				typename EmuCore::TMP::conditional_const<std::is_const_v<std::remove_reference_t<In_>>, typename _in_uq::value_type&>::type
			>::type;
		};

		using _type_finder = _type_finder_template<Matrix_>;

	public:
		static constexpr bool is_theoretical_index = _type_finder::is_theoretical_index;
		using type = typename _type_finder::type;
	};

	/// <summary>
	/// <para> Helper type to determine Column and Row index sequences to fully access the provided Matrix_ type contiguously within the provided indices range. </para>
	/// <para> Will trigger a static_assert if ColumnIndices_ or RowIndices_ is not a std::index_sequence. </para>
	/// <para> column_index_sequence will display all determined column indices. </para>
	/// <para> row_index_sequence will display all determined row indices. </para>
	/// <para>
	///		If Matrix_ is column-major, row_index_sequence will be iterated and reset to its starting point in a loop for every column. 
	///		For all indices in a single loop, columns will be the same value before iterating.
	/// </para>
	/// <para>
	///		If Matrix_ is not column-major, column_index_sequence will be iterated and reset to its starting point in a loop for every row. 
	///		For all indices in a single loop, rows will be the same value before iterating.
	/// </para>
	/// </summary>
	template<class Matrix_, class ColumnIndices_, class RowIndices_, typename = void>
	struct make_matrix_index_sequences
	{
		static_assert
		(
			EmuCore::TMP::is_index_sequence_v<ColumnIndices_> && EmuCore::TMP::is_index_sequence_v<RowIndices_>,
			"Passed a non-index sequence to an indices argument for make_full_matrix_index_sequences for an EmuMath Matrix."
		);
		using column_index_sequence = std::index_sequence<>;
		using row_index_sequence = std::index_sequence<>;
	};

	template<class Matrix_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	struct make_matrix_index_sequences
	<
		Matrix_,
		std::index_sequence<ColumnIndices_...>,
		std::index_sequence<RowIndices_...>,
		std::enable_if_t<Matrix_::is_column_major>
	>
	{
		// Output matrix will have to read the input Matrix in its contiguous order to correctly construct
		// --- In this case, we are column-major, so we iterate rows before iterating columns
		static constexpr std::size_t num_columns = sizeof...(ColumnIndices_);
		static constexpr std::size_t num_rows = sizeof...(RowIndices_);

		using column_index_sequence = typename EmuCore::TMP::variadic_splice_integer_sequences
		<
			EmuCore::TMP::make_duplicated_index_sequence<ColumnIndices_, num_rows>...
		>::type;

		using row_index_sequence = typename EmuCore::TMP::looped_integer_sequence<std::index_sequence<RowIndices_...>, num_columns - 1>::type;
	};

	template<class Matrix_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	struct make_matrix_index_sequences
	<
		Matrix_,
		std::index_sequence<ColumnIndices_...>,
		std::index_sequence<RowIndices_...>,
		std::enable_if_t<!Matrix_::is_column_major>
	>
	{
		// Output matrix will have to read the input Matrix in its contiguous order to correctly construct
		// --- In this case, we are row-major, so we iterate columns before iterating rows
		static constexpr std::size_t num_columns = sizeof...(ColumnIndices_);
		static constexpr std::size_t num_rows = sizeof...(RowIndices_);

		using column_index_sequence = typename EmuCore::TMP::looped_integer_sequence<std::index_sequence<ColumnIndices_...>, num_rows - 1>::type;
		using row_index_sequence = typename EmuCore::TMP::variadic_splice_integer_sequences
		<
			EmuCore::TMP::make_duplicated_index_sequence<RowIndices_, num_columns>...
		>::type;
	};

	template<class Matrix_>
	struct make_full_matrix_index_sequences
	{
	private:
		template<class In_, bool IsMatrix_ = EmuMath::TMP::is_emu_matrix_v<In_>>
		struct _maker_template
		{
			using column_index_sequence = std::index_sequence<>;
			using row_index_sequence = std::index_sequence<>;
		};

		template<class In_>
		struct _maker_template<In_, true>
		{
		private:
			using _in_uq = EmuCore::TMP::remove_ref_cv_t<In_>;
			using _underlying_maker = EmuMath::TMP::make_matrix_index_sequences
			<
				_in_uq,
				std::make_index_sequence<_in_uq::num_columns>,
				std::make_index_sequence<_in_uq::num_rows>
			>;

		public:
			using column_index_sequence = typename _underlying_maker::column_index_sequence;
			using row_index_sequence = typename _underlying_maker::row_index_sequence;
		};

		using _maker = _maker_template<Matrix_>;

	public:
		using column_index_sequence = typename _maker::column_index_sequence;
		using row_index_sequence = typename _maker::row_index_sequence;
	};

	template<std::size_t ColumnBeginIndex_, std::size_t ColumnEndIndex_, std::size_t RowBeginIndex_, std::size_t RowEndIndex_, bool ColumnMajor_>
	struct make_ranged_matrix_index_sequences
	{
	private:
		template<std::size_t ColumnBegin_, std::size_t ColumnEnd_, std::size_t RowBegin_, std::size_t RowEnd_>
		[[nodiscard]] static constexpr inline bool _valid_index_range()
		{
			return (ColumnBegin_ < ColumnEnd_) && (RowBegin_ < RowEnd_);
		}

		template
		<
			std::size_t ColumnBegin_,
			std::size_t ColumnEnd_,
			std::size_t RowBegin_,
			std::size_t RowEnd_,
			bool Valid_ = _valid_index_range<ColumnBegin_, ColumnEnd_, RowBegin_, RowEnd_>()
		>
		struct _maker_template
		{
			static constexpr bool is_valid = false;
			using column_index_sequence = std::index_sequence<>;
			using row_index_sequence = std::index_sequence<>;
		};

		template<std::size_t ColumnBegin_, std::size_t ColumnEnd_, std::size_t RowBegin_, std::size_t RowEnd_>
		struct _maker_template<ColumnBegin_, ColumnEnd_, RowBegin_, RowEnd_, true>
		{
		private:
			template<class ColumnIndices_, class RowIndices_, bool IsColumnMajor_>
			struct _underlying_maker_template
			{
				using column_index_sequence = std::index_sequence<>;
				using row_index_sequence = std::index_sequence<>;
			};

			template<std::size_t...ColumnIndices_, std::size_t...RowIndices_>
			struct _underlying_maker_template<std::index_sequence<ColumnIndices_...>, std::index_sequence<RowIndices_...>, true>
			{
				using column_index_sequence = typename EmuCore::TMP::variadic_splice_integer_sequences
				<
					EmuCore::TMP::make_duplicated_index_sequence<ColumnIndices_, sizeof...(RowIndices_)>...
				>::type;
				using row_index_sequence = typename EmuCore::TMP::looped_integer_sequence<std::index_sequence<RowIndices_...>, sizeof...(ColumnIndices_) - 1>::type;
			};

			template<std::size_t...ColumnIndices_, std::size_t...RowIndices_>
			struct _underlying_maker_template<std::index_sequence<ColumnIndices_...>, std::index_sequence<RowIndices_...>, false>
			{
				using column_index_sequence = typename EmuCore::TMP::looped_integer_sequence<std::index_sequence<ColumnIndices_...>, sizeof...(RowIndices_) - 1>::type;
				using row_index_sequence = typename EmuCore::TMP::variadic_splice_integer_sequences
				<
					EmuCore::TMP::make_duplicated_index_sequence<RowIndices_, sizeof...(ColumnIndices_)>...
				>::type;
			};

			using _base_column_indices = EmuCore::TMP::make_offset_index_sequence<ColumnBegin_, ColumnEnd_ - ColumnBegin_>;
			using _base_row_indices = EmuCore::TMP::make_offset_index_sequence<RowBegin_, RowEnd_ - RowBegin_>;

			using _underlying_maker = _underlying_maker_template<_base_column_indices, _base_row_indices, ColumnMajor_>;

		public:
			static constexpr bool is_valid = true;
			using column_index_sequence = typename _underlying_maker::column_index_sequence;
			using row_index_sequence = typename _underlying_maker::row_index_sequence;
		};

		using _maker = _maker_template<ColumnBeginIndex_, ColumnEndIndex_, RowBeginIndex_, RowEndIndex_>;

	public:
		using column_index_sequence = typename _maker::column_index_sequence;
		using row_index_sequence = typename _maker::row_index_sequence;
	};

	template<class Arg_>
	[[nodiscard]] constexpr inline bool is_specialised_matrix_multiply_arg()
	{
		return
		(
			EmuMath::TMP::is_emu_matrix_v<Arg_> ||
			EmuMath::TMP::is_emu_vector_v<Arg_>
		);
	}
}

#endif
