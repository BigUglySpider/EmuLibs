#ifndef EMU_MATH_MATRIX_TMP_H_INC_
#define EMU_MATH_MATRIX_TMP_H_INC_ 1

#include "../../../../EmuCore/TMPHelpers/TypeConvertors.h"
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

	/// <summary>
	/// <para> Type to determine the transposed type of an EmuMath Matrix. </para>
	/// <para> If Matrix_ is not an EmuMath Matrix: type will be void. </para>
	/// <para> If OutT_ is void, the T_ argument for type will be the value_type_uq of the input Matrix_. </para>
	/// <para> The column-major memory order of type is determined by OutColumnMajor_. </para>
	/// <para>
	///		Where successful, type will be an EmuMath Matrix with a number of columns equal to Matrix_::num_rows, 
	///		and a number of rows equal to Matrix_::num_columns.
	/// </para>
	/// </summary>
	template<class Matrix_, typename OutT_, bool OutColumnMajor_>
	struct emu_matrix_transpose
	{
	private:
		template<typename In_, bool IsMatrix_ = EmuMath::TMP::is_emu_matrix_v<In_>>
		struct _transposer
		{
			using type = void;
		};
		template<typename In_>
		struct _transposer<In_, true>
		{
		private:
			using in_uq = EmuCore::TMP::remove_ref_cv_t<In_>;
			using out_t = std::conditional_t<std::is_void_v<OutT_>, typename in_uq::value_type_uq, OutT_>;

		public:
			using type = EmuMath::Matrix<in_uq::num_rows, in_uq::num_columns, OutT_, OutColumnMajor_>;
		};

	public:
		using type = typename _transposer<Matrix_>::type;
	};
	template<class Matrix_, typename OutT_, bool OutColumnMajor_>
	using emu_matrix_transpose_t = typename emu_matrix_transpose<Matrix_, OutT_, OutColumnMajor_>::type;

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

	template<class Matrix_>
	struct matrix_non_contained_column
	{
	private:
		template<class In_, bool IsMatrix_ = EmuMath::TMP::is_emu_matrix_v<In_>>
		struct _type_finder
		{
			using type = void;
		};

		template<class In_>
		struct _type_finder<In_, true>
		{
			using type = EmuMath::Vector
			<
				EmuCore::TMP::remove_ref_cv_t<In_>::num_rows,
				typename EmuCore::TMP::remove_ref_cv_t<In_>::value_type_uq
			>;
		};

	public:
		using type = typename _type_finder<Matrix_>::type;
	};

	template<class Matrix_>
	struct matrix_non_contained_row
	{
	private:
		template<class In_, bool IsMatrix_ = EmuMath::TMP::is_emu_matrix_v<In_>>
		struct _type_finder
		{
			using type = void;
		};

		template<class In_>
		struct _type_finder<In_, true>
		{
			using type = EmuMath::Vector
			<
				EmuCore::TMP::remove_ref_cv_t<In_>::num_columns,
				typename EmuCore::TMP::remove_ref_cv_t<In_>::value_type_uq
			>;
		};

	public:
		using type = typename _type_finder<Matrix_>::type;
	};

	template<std::size_t ColumnIndex_, class Matrix_>
	struct is_theoretical_matrix_column_index
	{
	private:
		template<class In_, bool IsMatrix_ = EmuMath::TMP::is_emu_matrix_v<In_>>
		struct _value_finder
		{
			static constexpr bool value = true;
		};

		template<class In_>
		struct _value_finder<In_, true>
		{
			static constexpr bool value = ColumnIndex_ >= EmuCore::TMP::remove_ref_cv_t<In_>::num_columns;
		};

	public:
		static constexpr bool value = _value_finder<Matrix_>::value;
	};

	template<std::size_t RowIndex_, class Matrix_>
	struct is_theoretical_matrix_row_index
	{
	private:
		template<class In_, bool IsMatrix_ = EmuMath::TMP::is_emu_matrix_v<In_>>
		struct _value_finder
		{
			static constexpr bool value = true;
		};

		template<class In_>
		struct _value_finder<In_, true>
		{
			static constexpr bool value = RowIndex_ >= EmuCore::TMP::remove_ref_cv_t<In_>::num_rows;
		};

	public:
		static constexpr bool value = _value_finder<Matrix_>::value;
	};

	template<std::size_t ColumnIndex_, class Matrix_>
	struct matrix_column_theoretical_get_result
	{
	private:
		template<class In_, bool IsMatrix_ = EmuMath::TMP::is_emu_matrix_v<In_>>
		struct _type_finder_template
		{
			static constexpr bool is_theoretical = false;
			using type = void;
		};

		template<class In_>
		struct _type_finder_template<In_, true>
		{
		private:
			using _in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;

		public:
			static constexpr bool is_theoretical = EmuMath::TMP::is_theoretical_matrix_column_index<ColumnIndex_, In_>::value;
			using type = std::conditional_t
			<
				is_theoretical,
				typename matrix_non_contained_column<_in_uq>::type,
				std::conditional_t
				<
					std::is_const_v<std::remove_reference_t<In_>>,
					typename _in_uq::column_get_const_ref_type,
					typename _in_uq::column_get_ref_type
				>
			>;
		};

		using _type_finder = _type_finder_template<Matrix_>;

	public:
		static constexpr bool is_theoretical = _type_finder::is_theoretical;
		using type = typename _type_finder::type;
	};

	template<std::size_t RowIndex_, class Matrix_>
	struct matrix_row_theoretical_get_result
	{
	private:
		template<class In_, bool IsMatrix_ = EmuMath::TMP::is_emu_matrix_v<In_>>
		struct _type_finder_template
		{
			static constexpr bool is_theoretical = false;
			using type = void;
		};

		template<class In_>
		struct _type_finder_template<In_, true>
		{
		private:
			using _in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;

		public:
			static constexpr bool is_theoretical = EmuMath::TMP::is_theoretical_matrix_row_index<RowIndex_, _in_uq>::value;
			using type = std::conditional_t
			<
				is_theoretical,
				typename matrix_non_contained_row<_in_uq>::type,
				std::conditional_t
				<
					std::is_const_v<std::remove_reference_t<In_>>,
					typename _in_uq::row_get_const_ref_type,
					typename _in_uq::row_get_ref_type
				>
			>;
		};

		using _type_finder = _type_finder_template<Matrix_>;

	public:
		static constexpr bool is_theoretical = _type_finder::is_theoretical;
		using type = typename _type_finder::type;
	};

	template<std::size_t MajorIndex_, class Matrix_>
	struct is_theoretical_matrix_major_index
	{
	private:
		template<class In_, bool IsMatrix_ = EmuMath::TMP::is_emu_matrix_v<In_>>
		struct _value_finder
		{
			static constexpr bool value = false;
		};

		template<class In_>
		struct _value_finder<In_, true>
		{
		private:
			using _underlying_check = typename std::conditional
			<
				EmuCore::TMP::remove_ref_cv_t<In_>::is_column_major,
				EmuMath::TMP::is_theoretical_matrix_column_index<MajorIndex_, In_>,
				EmuMath::TMP::is_theoretical_matrix_row_index<MajorIndex_, In_>
			>::type;

		public:
			static constexpr bool value = _underlying_check::value;
		};

	public:
		static constexpr bool value = _value_finder<Matrix_>::value;
	};

	template<std::size_t NonMajorIndex_, class Matrix_>
	struct is_theoretical_matrix_non_major_index
	{
	private:
		template<class In_, bool IsMatrix_ = EmuMath::TMP::is_emu_matrix_v<In_>>
		struct _value_finder
		{
			static constexpr bool value = false;
		};

		template<class In_>
		struct _value_finder<In_, true>
		{
		private:
			using _underlying_check = typename std::conditional
			<
				EmuCore::TMP::remove_ref_cv_t<In_>::is_column_major,
				EmuMath::TMP::is_theoretical_matrix_row_index<NonMajorIndex_, In_>,
				EmuMath::TMP::is_theoretical_matrix_column_index<NonMajorIndex_, In_>
			>::type;

		public:
			static constexpr bool value = _underlying_check::value;
		};

	public:
		static constexpr bool value = _value_finder<Matrix_>::value;
	};

	template<std::size_t MajorIndex_, class Matrix_>
	struct matrix_major_theoretical_get_result
	{
	private:
		template<class In_, bool IsMatrix_ = EmuMath::TMP::is_emu_matrix_v<In_>>
		struct _type_finder_template
		{
			static constexpr bool is_theoretical = false;
			using type = void;
		};

		template<class In_>
		struct _type_finder_template<In_, true>
		{
		private:
			using _underlying_check = typename std::conditional
			<
				EmuCore::TMP::remove_ref_cv_t<In_>::is_column_major,
				EmuMath::TMP::matrix_column_theoretical_get_result<MajorIndex_, Matrix_>,
				EmuMath::TMP::matrix_row_theoretical_get_result<MajorIndex_, Matrix_>
			>::type;

		public:
			static constexpr bool is_theoretical = _underlying_check::is_theoretical;
			using type = typename _underlying_check::type;
		};

		using _type_finder = _type_finder_template<Matrix_>;

	public:
		static constexpr bool is_theoretical = _type_finder::is_theoretical;
		using type = typename _type_finder::type;
	};

	template<std::size_t NonMajorIndex_, class Matrix_>
	struct matrix_non_major_theoretical_get_result
	{
	private:
		template<class In_, bool IsMatrix_ = EmuMath::TMP::is_emu_matrix_v<In_>>
		struct _type_finder_template
		{
			static constexpr bool is_theoretical = false;
			using type = void;
		};

		template<class In_>
		struct _type_finder_template<In_, true>
		{
		private:
			using _underlying_check = typename std::conditional
			<
				EmuCore::TMP::remove_ref_cv_t<In_>::is_column_major,
				EmuMath::TMP::matrix_row_theoretical_get_result<NonMajorIndex_, Matrix_>,
				EmuMath::TMP::matrix_column_theoretical_get_result<NonMajorIndex_, Matrix_>
			>::type;

		public:
			static constexpr bool is_theoretical = _underlying_check::is_theoretical;
			using type = typename _underlying_check::type;
		};

		using _type_finder = _type_finder_template<Matrix_>;

	public:
		static constexpr bool is_theoretical = _type_finder::is_theoretical;
		using type = typename _type_finder::type;
	};

	template<class Matrix_>
	struct matrix_largest_axis
	{
	private:
		template<class In_, bool = EmuMath::TMP::is_emu_matrix_v<In_>>
		struct _value_finder
		{
			static constexpr std::size_t value = 0;
		};

		template<class In_>
		struct _value_finder<In_, true>
		{
			using _in_uq = EmuCore::TMP::remove_ref_cv_t<In_>;
			static constexpr std::size_t value = EmuCore::TMP::greatest_constant_v<std::size_t, _in_uq::num_columns, _in_uq::num_rows>;
		};

	public:
		static constexpr std::size_t value = _value_finder<Matrix_>::value;
	};
	template<class Matrix_>
	static constexpr std::size_t matrix_largest_axis_v = matrix_largest_axis<Matrix_>::value;

	template<class Matrix_>
	struct matrix_smallest_axis
	{
	private:
		template<class In_, bool = EmuMath::TMP::is_emu_matrix_v<In_>>
		struct _value_finder
		{
			static constexpr std::size_t value = 0;
		};

		template<class In_>
		struct _value_finder<In_, true>
		{
			using _in_uq = EmuCore::TMP::remove_ref_cv_t<In_>;
			static constexpr std::size_t value = EmuCore::TMP::smallest_constant_v<std::size_t, _in_uq::num_columns, _in_uq::num_rows>;
		};

	public:
		static constexpr std::size_t value = _value_finder<Matrix_>::value;
	};
	template<class Matrix_>
	static constexpr std::size_t matrix_smallest_axis_v = matrix_smallest_axis<Matrix_>::value;

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
}

#endif
