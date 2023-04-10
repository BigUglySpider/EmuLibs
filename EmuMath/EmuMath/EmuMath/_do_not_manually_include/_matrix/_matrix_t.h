#ifndef EMU_MATH_MATRIX_T_H_INC_
#define EMU_MATH_MATRIX_T_H_INC_ 1

#include "_helpers/_all_matrix_helpers.h"
#include <exception>
#include <tuple>
#include <utility>

namespace EmuMath
{
	/// <summary>
	/// <para> Template that may be instantiated to create an arbitrarily sized Matrix type with data stored contiguously. </para>
	/// <para> May specify if contiguous data is stored in column-major or row-major order. By default, column-major storage is used. </para>
	/// <para>
	///		Provides a column-major common interface and implementation, regardless of the ColumnMajor_ argument. 
	///		This common interface is nulled when using the Matrix via STL iterators or flattened indices (i.e. only a single, scalar index argument), 
	///		in which case the specified contiguous storage order will be used.
	/// </para>
	/// <para>
	///		--- NOTATION: Where cx = column x, rx = row x, columns and rows are referred to as the following for this Matrix type:
	///		<para> --- | c0r0, c1r0, ..., cNumColumns_r0					  </para>
	///		<para> --- | c0r1, c1r1, ..., cNumColumns_r1					  </para>
	///		<para> --- | ...												  </para>
	///		<para> --- | c0rNumRows_, c1rNumRows_, ..., cNumColumns_rNumRows_ </para>
	/// </para>
	/// </summary>
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	struct Matrix
	{
#pragma region TMP_INFO
	public:
		template<std::size_t, std::size_t, typename, bool> friend struct Matrix;

		/// <summary> The type of Matrix that this is an instance of. Primarily for clearer typing in the implementation, and of little use. </summary>
		using this_type = Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		/// <summary> Type providing info regarding this Matrix, which may have been specialised to some degree to encourage new behaviours in the default implementation. </summary>
		using matrix_info = EmuMath::TMP::common_matrix_info<NumColumns_, NumRows_, T_, ColumnMajor_>;
		/// <summary> The number of columns containined within this Matrix type. </summary>
		static constexpr std::size_t num_columns = matrix_info::num_columns;
		/// <summary> The number of rows containined within this Matrix type. </summary>
		static constexpr std::size_t num_rows = matrix_info::num_rows;
		/// <summary> The total number of elements contained within this Matrix type. </summary>
		static constexpr std::size_t size = matrix_info::size;
		/// <summary> The total number of major elements contained within this Matrix type. Equal to num_columns if column-major, otherwise equal to num_rows. </summary>
		static constexpr std::size_t num_major_elements = matrix_info::num_major_elements;
		/// <summary> The total number of non-major elements contained within this Matrix type. Equal to num_rows if column-major, otherwise equal to num_columns. </summary>
		static constexpr std::size_t num_non_major_elements = matrix_info::num_non_major_elements;
		/// <summary> The number of columns or rows that this Matrix contains, whichever of the two is lower. </summary>
		static constexpr std::size_t smallest_direction_size = matrix_info::smallest_direction_size;
		/// <summary> The number of columns or rows that this Matrix contains, whichever of the two is higher. </summary>
		static constexpr std::size_t greatest_direction_size = matrix_info::greatest_direction_size;
		/// <summary> If true, this Matrix type is contiguously stored in column order - that is, a full column appears in memory before moving to the immediate next column. </summary>
		static constexpr bool is_column_major = matrix_info::is_column_major;
		/// <summary> If true, this Matrix type is contiguously stored in row order - that is, a full row appears in memory before moving to the immediate next row. </summary>
		static constexpr bool is_row_major = matrix_info::is_row_major;
		/// <summary> True if this Matrix type contains any form of reference, regardless of qualification. </summary>
		static constexpr bool contains_ref = matrix_info::contains_ref;
		/// <summary> True if this Matrix type contains const-qualified (aka readonly) references. </summary>
		static constexpr bool contains_const_ref = matrix_info::contains_const_ref;
		/// <summary> True if this Matrix type contains non-const-qualified (aka writable) references. </summary>
		static constexpr bool contains_non_const_ref = matrix_info::contains_non_const_ref;
		/// <summary> True if this is a square Matrix type, meaning that it contains an equal number of columns and rows. </summary>
		static constexpr bool is_square = num_columns == num_rows;

		/// <summary> Representation of this Matrix type flattened as an EmuMath Vector. </summary>
		using matrix_vector_type = typename matrix_info::matrix_vector_type;
		/// <summary> The underlying type stored within this Matrix type. </summary>
		using stored_type = typename matrix_info::stored_type;
		/// <summary> The qualified type used when interacting with this Matrix type's common interface. </summary>
		using value_type = typename matrix_info::value_type;
		/// <summary> The unqualified form of the type used when interacting with this Matrix type's common interface. </summary>
		using value_type_uq = typename matrix_info::value_type_uq;
		/// <summary> The floating-point type preferred for use with this Matrix type in operations which benefit/require floating-points. </summary>
		using preferred_floating_point = typename matrix_info::preferred_floating_point;

		/// <summary> STL-compliant random-access iterator for accessing this Matrix type in a flattened, contiguous approach. </summary>
		using iterator = typename matrix_vector_type::iterator;
		/// <summary> STL-compliant random-access constant iterator for accessing this Matrix type in a flattened, contiguous approach. </summary>
		using const_iterator = typename matrix_vector_type::const_iterator;
		/// <summary> STL-compliant random-access reverse iterator for accessing this Matrix type in a flattened, contiguous approach. </summary>
		using reverse_iterator = typename matrix_vector_type::reverse_iterator;
		/// <summary> STL-compliant random-access constant reverse iterator for accessing this Matrix type in a flattened, contiguous approach. </summary>
		using const_reverse_iterator = typename matrix_vector_type::const_reverse_iterator;
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

		/// <summary>
		/// <para> Calculates the index for the provided index in this Matrix type to be used when accessing it as a flattened, contiguous array. </para>
		/// </summary>
		/// <returns> Flattened index of the provided column/row index within this Matrix type. </returns>
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

		/// <summary>
		/// <para> Calculates the index for the provided index in this Matrix type to be used when accessing it as a flattened, contiguous array. </para>
		/// </summary>
		/// <param name="column_row_index_pair_">Pair containing the column index in its first element (0), and the row index in its second element (1).</param>
		/// <returns> Flattened index of the provided column/row index within this Matrix type. </returns>
		[[nodiscard]] static constexpr inline std::size_t get_flattened_index(const std::pair<std::size_t, std::size_t>& column_row_index_pair_)
		{
			using std::get;
			return get_flattened_index(get<0>(column_row_index_pair_), get<1>(column_row_index_pair_));
		}

		/// <summary>
		/// <para> Unflattens the provided flattened index and calculates the index of the column it matches to. </para>
		/// </summary>
		/// <param name="flattened_index_">Index when accessing this Matrix type as a flattened, contiguous array.</param>
		/// <returns> The index of the column that the provided `flattened_index_` would equate to. </returns>
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

		/// <summary>
		/// <para> Unflattens the provided flattened index and calculates the index of the row it matches to. </para>
		/// </summary>
		/// <param name="flattened_index_">Index when accessing this Matrix type as a flattened, contiguous array.</param>
		/// <returns> The index of the row that the provided `flattened_index_` would equate to. </returns>
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

		/// <summary>
		/// <para> Unflattens the provided flattened index and calculates the index of the column and row indices it matches to. </para>
		/// </summary>
		/// <param name="flattened_index_">Index when accessing this Matrix type as a flattened, contiguous array.</param>
		/// <returns>
		///		A pair containing unflattened indices of the provided `flattened_index_`, 
		///		with the column index in the first element (0), and the row index in the second element (1).
		/// </returns>
		[[nodiscard]] static constexpr inline std::pair<std::size_t, std::size_t> get_unflattened_index(std::size_t flattened_index_)
		{
			return std::pair<std::size_t, std::size_t>(get_unflattened_column_index(flattened_index_), get_unflattened_row_index(flattened_index_));
		}
#pragma endregion

#pragma region CONSTRUCTION_CHECKS
	private:		
		template<class VectorTuple_, std::size_t ColumnIndex_, std::size_t RowIndex_>
		struct _variadic_construction_from_major_vector_arg_at_index
		{
		private:
			static constexpr std::size_t _non_major_index = get_non_major_index(ColumnIndex_, RowIndex_);
			using _vector_tuple_no_ref = std::remove_reference_t<VectorTuple_>;
			using _vector_type_raw = std::tuple_element_t<get_major_index(ColumnIndex_, RowIndex_), _vector_tuple_no_ref>;
			using _vector_type_lval = decltype(EmuCore::TMP::lval_ref_cast<_vector_type_raw>(std::declval<_vector_type_raw>()));
			using _vector_uq = typename EmuCore::TMP::remove_ref_cv<_vector_type_raw>::type;

			static constexpr bool _is_valid_arg =
			(
				std::is_lvalue_reference_v<_vector_type_raw> ||
				!contains_ref ||
				(
					_vector_uq::contains_ref &&
					(contains_const_ref || _vector_uq::contains_non_const_ref) &&
					_non_major_index < _vector_uq::size
				)
			);

			static constexpr bool _should_move = 
			(
				!contains_ref &&
				!std::is_lvalue_reference_v<_vector_type_raw> &&
				_non_major_index < _vector_uq::size
			);
			using get_result = decltype(std::declval<_vector_type_lval>().template AtTheoretical<_non_major_index>());

		public:
			using type = typename std::conditional
			<
				!_is_valid_arg,
				void,
				typename std::conditional
				<
					_should_move,
					decltype(std::move(std::declval<get_result>())),
					get_result
				>::type
			>::type;
		};

		

		template<class ToConvert_, std::size_t ColumnIndex_, std::size_t RowIndex_>
		struct _matrix_convert_construct_index_arg
		{
		private:
			using _to_convert_uq = typename EmuCore::TMP::remove_ref_cv<ToConvert_>::type;
			using _to_convert_lval = decltype(EmuCore::TMP::lval_ref_cast<ToConvert_>(std::declval<ToConvert_>()));
			static constexpr bool _index_is_contained = EmuMath::Helpers::_matrix_underlying::_matrix_index_is_contained<ColumnIndex_, RowIndex_, _to_convert_uq>();

			static constexpr bool _is_valid_arg =
			(
				std::is_lvalue_reference_v<ToConvert_> ||
				!contains_ref ||
				(
					_to_convert_uq::contains_ref &&
					(contains_const_ref || _to_convert_uq::contains_non_const_ref) &&
					_index_is_contained
				)
			);

			static constexpr bool _should_move =
			(
				!std::is_lvalue_reference_v<ToConvert_> &&
				!contains_ref &&
				_index_is_contained
			);

			using _get_result = decltype(std::declval<_to_convert_lval>().template AtTheoretical<ColumnIndex_, RowIndex_>());
			using _out_result = typename std::conditional
			<
				_index_is_contained,
				_get_result,
				decltype(EmuMath::Helpers::matrix_get_non_contained<this_type>())
			>::type;

		public:
			using type = typename std::conditional
			<
				!_is_valid_arg,
				void,
				typename std::conditional
				<
					_should_move,
					decltype(std::move(std::declval<_get_result>())),
					_out_result
				>::type
			>::type;
		};

		template<class ToConvert_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
		[[nodiscard]] static constexpr inline bool _is_valid_matrix_to_convert_construct
		(
			std::index_sequence<ColumnIndices_...> column_indices_,
			std::index_sequence<RowIndices_...> row_indices_
		)
		{
			return std::is_constructible_v<matrix_vector_type, typename _matrix_convert_construct_index_arg<ToConvert_, ColumnIndices_, RowIndices_>::type...>;
		}

		template<class ForwardedVectorTuple_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
		[[nodiscard]] static constexpr inline bool _valid_variadic_construction_args_from_major_vectors
		(
			std::index_sequence<ColumnIndices_...> column_indices_,
			std::index_sequence<RowIndices_...> row_indices_
		)
		{
			return std::is_constructible_v
			<
				matrix_vector_type,
				typename _variadic_construction_from_major_vector_arg_at_index<ForwardedVectorTuple_&, ColumnIndices_, RowIndices_>::type...
			>;
		}

		template<std::size_t ArgCount_, class...Args_>
		[[nodiscard]] static constexpr inline bool _valid_variadic_construction_args_from_major_vectors()
		{
			if constexpr (ArgCount_ == num_major_elements)
			{
				if constexpr ((... && EmuMath::TMP::is_emu_vector_v<Args_>))
				{
					using forward_tuple = decltype(std::forward_as_tuple(std::forward<Args_>(std::declval<Args_>())...));
					using indices = EmuMath::TMP::make_full_matrix_index_sequences<this_type>;
					using column_indices = typename indices::column_index_sequence;
					using row_indices = typename indices::row_index_sequence;
					return _valid_variadic_construction_args_from_major_vectors<forward_tuple>(column_indices(), row_indices());
				}
				else
				{
					return false; // Must only be EmuMath Vectors
				}
			}
			else
			{
				return false; // Must be 1 argument per major segment
			}
		}

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

		template<std::size_t ArgCount_, class...Args_>
		static constexpr inline bool _valid_variadic_single_scalar_construction_arg()
		{
			if constexpr (ArgCount_ == 1)
			{
				using arg_type = EmuCore::TMP::first_variadic_arg_t<Args_...>;
				return
				(
					!EmuMath::TMP::is_emu_matrix_v<arg_type> && // Reserved for conversion/copy/move
					!EmuMath::TMP::is_emu_vector_v<arg_type> && // Don't allow instantiation via a flattened Vector; leave this to Matrix construction
					std::is_constructible_v<matrix_vector_type, decltype(std::forward<arg_type>(std::declval<arg_type>()))>
				);
			}
			else
			{
				return false; // More than 1 arg, immediately invalid since this is a "construct all via X" situation
			}
		}

	public:
		template<std::size_t Unused_ = 0>
		static constexpr inline bool is_default_constructible()
		{
			return Unused_ >= 0 && std::is_default_constructible_v<matrix_vector_type>;
		}

		template<std::size_t Unused_ = 0>
		static constexpr inline bool is_const_copy_constructible()
		{
			return Unused_ >= 0 && std::is_constructible_v<matrix_vector_type, const matrix_vector_type&>;
		}

		template<std::size_t Unused_ = 0>
		static constexpr inline bool is_non_const_copy_constructible()
		{
			return Unused_ >= 0 && std::is_constructible_v<matrix_vector_type, matrix_vector_type&>;
		}

		template<std::size_t Unused_ = 0>
		static constexpr inline bool is_move_constructible()
		{
			return Unused_ >= 0 && std::is_constructible_v<matrix_vector_type, matrix_vector_type&&>;
		}

		template<class ToConvert_>
		[[nodiscard]] static constexpr inline bool is_conversion_constructible()
		{
			if constexpr (EmuMath::TMP::is_emu_matrix_v<ToConvert_>)
			{
				if constexpr (!std::is_same_v<this_type, EmuCore::TMP::remove_ref_cv_t<ToConvert_>>)
				{
					using indices = EmuMath::TMP::make_full_matrix_index_sequences<this_type>;
					using column_indices = typename indices::column_index_sequence;
					using row_indices = typename indices::row_index_sequence;
					return _is_valid_matrix_to_convert_construct<ToConvert_>(column_indices(), row_indices());
				}
				else
				{
					return false; // this_type reserved for own move/copy constructors
				}
			}
			else
			{
				return false; // Can only convert another Matrix
			}
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
						_valid_variadic_single_scalar_construction_arg<num_args_, Args_...>() ||
						_valid_variadic_construction_args_from_major_vectors<num_args_, Args_...>()
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
#pragma endregion

#pragma region TRANSFORMATION_FUNC_VALIDITY_CHECK_HELPERS
	protected:
		/// <summary>
		/// <para> Common underlying function template used for compile-time checks if a linear transformation is valid. </para>
		/// <para>
		///		In this context, "linear" refers to functionalities which scale linearly with the dimensions of a (theoretically square) Matrix, 
		///		where the represented transformation is in a number of dimensions equal to the Matrix's smallest direction size - 1 (e.g. 3D for a 4x4, 4x3, or 3x4 Matrix).
		/// </para>
		/// </summary>
		/// <param name="post_check_func_">Additional funtion to be invoked for checks. This should preferably be a lambda or functor.</param>
		/// <returns>True if the passed arguments are valid for a linear transformation, otherwise false.</returns>
		template<std::size_t MaxArgCount_, class...SequentialArgs_, class Func_>
		[[nodiscard]] static constexpr inline auto _valid_linear_transform_args(Func_ post_check_func_)
			-> std::enable_if_t<std::is_invocable_r_v<bool, Func_>, bool>
		{
			constexpr std::size_t num_args = sizeof...(SequentialArgs_);
			if constexpr (num_args == 0)
			{
				return false;
			}
			else if constexpr(num_args > MaxArgCount_)
			{
				return false;
			}
			else
			{
				return post_check_func_();
			}
		}
#pragma endregion

#pragma region VALID_FUNCTION_ARG_CHECKS
		template<std::size_t RhsSize_>
		[[nodiscard]] static constexpr inline bool valid_vector_multiply_arg_size()
		{
			return RhsSize_ == num_rows || (RhsSize_ == num_rows - 1);
		}

		template<std::size_t RhsNumColumns_, std::size_t RhsNumRows_, std::size_t Unused_ = 0>
		[[nodiscard]] static constexpr inline bool valid_matrix_multiply_arg_size()
		{
			return Unused_ >= 0 && num_columns == RhsNumRows_;
		}
#pragma endregion

#pragma region UNDERLYING_CONSTRUCTORS
	private:
		template<std::size_t ColumnIndex_, std::size_t RowIndex_, class ToConvert_>
		[[nodiscard]] static constexpr inline typename _matrix_convert_construct_index_arg<ToConvert_, ColumnIndex_, RowIndex_>::type _get_conversion_construct_index_arg
		(
			ToConvert_&& to_convert_
		)
		{
			if constexpr (!std::is_void_v<typename _matrix_convert_construct_index_arg<ToConvert_, ColumnIndex_, RowIndex_>::type>)
			{
				if constexpr (EmuMath::Helpers::_matrix_underlying::_matrix_index_is_contained<ColumnIndex_, RowIndex_, ToConvert_>())
				{
					constexpr bool should_move_ =
					(
						!std::is_lvalue_reference_v<ToConvert_> &&
						!contains_ref
					);
					auto& to_convert_lval_ = EmuCore::TMP::lval_ref_cast<ToConvert_>(std::forward<ToConvert_>(to_convert_));

					if constexpr (should_move_)
					{
						return std::move(to_convert_lval_.template AtTheoretical<ColumnIndex_, RowIndex_>());
					}
					else
					{
						return to_convert_lval_.template AtTheoretical<ColumnIndex_, RowIndex_>();
					}
				}
				else
				{
					return EmuMath::Helpers::matrix_get_non_contained<this_type>();
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<ToConvert_>(),
					"False-positive to conversion construction for an EmuMath Matrix. The output Matrix type cannot use elements from the input Matrix to construct its underlying data at all respective indices, or with its own implied-zero in indices that the input Matrix does not contain."
				);
			}
		}

		template<class ToConvert_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
		[[nodiscard]] static constexpr inline matrix_vector_type _do_conversion_construction
		(
			ToConvert_&& to_convert_,
			std::index_sequence<ColumnIndices_...> column_indices_,
			std::index_sequence<RowIndices_...> row_indices_
		)
		{
			using column_index_sequence = std::index_sequence<ColumnIndices_...>;
			using row_index_sequence = std::index_sequence<RowIndices_...>;
			if constexpr (_is_valid_matrix_to_convert_construct<ToConvert_>(column_index_sequence(), row_index_sequence()))
			{
				// We'll never access the same index twice, so silence false-positives
				// --- This is a slight disadvantage since there are scenarios where different references to the same object may be moved,
				// --- but silencing this has been chosen since VS is not showing any compromise
EMU_CORE_MSVC_PUSH_WARNING_STACK
EMU_CORE_MSVC_DISABLE_WARNING(EMU_CORE_WARNING_BAD_MOVE)
				return matrix_vector_type
				(
					_get_conversion_construct_index_arg<ColumnIndices_, RowIndices_>(std::forward<ToConvert_>(to_convert_))...
				);
EMU_CORE_MSVC_POP_WARNING_STACK
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<ToConvert_>(),
					"False-positive to conversion construction for an EmuMath Matrix. The output Matrix's underlying data cannot be constructed from the results extracted from the Matrix to convert."
				);
			}
		}

		template<class ToConvert_>
		[[nodiscard]] static constexpr inline matrix_vector_type _do_conversion_construction(ToConvert_&& to_convert_)
		{
			using indices = EmuMath::TMP::make_full_matrix_index_sequences<this_type>;
			using column_indices = typename indices::column_index_sequence;
			using row_indices = typename indices::row_index_sequence;
			return _do_conversion_construction(std::forward<ToConvert_>(to_convert_), column_indices(), row_indices());
		}

		template<std::size_t ColumnIndex_, std::size_t RowIndex_, class VectorTuple_>
		[[nodiscard]] static constexpr inline typename _variadic_construction_from_major_vector_arg_at_index<VectorTuple_&, ColumnIndex_, RowIndex_>::type
		_do_variadic_major_vector_construction_get_arg_for_index(VectorTuple_& vectors_tuple_)
		{
			if constexpr (!std::is_void_v<typename _variadic_construction_from_major_vector_arg_at_index<VectorTuple_&, ColumnIndex_, RowIndex_>::type>)
			{
				using std::get;
				constexpr std::size_t major_index_ = get_major_index(ColumnIndex_, RowIndex_);
				constexpr std::size_t non_major_index_ = get_non_major_index(ColumnIndex_, RowIndex_);
				using vector_type_raw = std::tuple_element_t<major_index_, VectorTuple_>;
				using vector_uq = typename EmuCore::TMP::remove_ref_cv<vector_type_raw>::type;
				auto& vector_lval_cast_ = EmuCore::TMP::lval_ref_cast<vector_type_raw>(std::forward<vector_type_raw>(get<major_index_>(vectors_tuple_)));
				constexpr bool should_move_ = 
				(
					!contains_ref &&
					!std::is_lvalue_reference_v<vector_type_raw> &&
					get_non_major_index(ColumnIndex_, RowIndex_) < vector_uq::size
				);

				if constexpr (should_move_)
				{
					return std::move(vector_lval_cast_.template at<non_major_index_>());
				}
				else
				{
					return vector_lval_cast_.template AtTheoretical<non_major_index_>();
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<VectorTuple_>(),
					"False-positive access to variadic construction of an EmuMath Matrix via a selection of EmuMath Vectors (1 per major segment). One index could not form a successful argument for creating the output Matrix's underlying data."
				);
			}
		}

		template<class ForwardedVectorTuple_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
		[[nodiscard]] static constexpr inline matrix_vector_type _do_variadic_major_vector_construction
		(
			ForwardedVectorTuple_ vector_tuple_,
			std::index_sequence<ColumnIndices_...> column_indices_,
			std::index_sequence<RowIndices_...> row_indices_
		)
		{
			using column_index_sequence = std::index_sequence<ColumnIndices_...>;
			using row_index_sequence = std::index_sequence<RowIndices_...>;
			if constexpr (_valid_variadic_construction_args_from_major_vectors<ForwardedVectorTuple_>(column_index_sequence(), row_index_sequence()))
			{
				return matrix_vector_type
				(
					_do_variadic_major_vector_construction_get_arg_for_index<ColumnIndices_, RowIndices_>(vector_tuple_)...
				);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<ForwardedVectorTuple_>(),
					"False-positive access to variadic construction of an EmuMath Matrix via a selection of EmuMath Vectors (1 per major segment). The output Matrix's underlying data could not be constructed from respective accesses to Vector elements at the determined indices."
				);
			}
		}

		template<class...Args_>
		static constexpr inline matrix_vector_type _do_variadic_construction(Args_&&...args_)
		{
			// Visual studio does not play nice with constexpr std::size_t val = sizeof...(Args_); thanks for that :)
			if constexpr (_valid_variadic_scalar_construction_args<sizeof...(Args_), Args_...>())
			{
				return matrix_vector_type(std::forward<Args_>(args_)...);
			}
			else if constexpr (_valid_variadic_single_scalar_construction_arg<sizeof...(Args_), Args_...>())
			{
				return matrix_vector_type(std::forward<Args_>(args_)...);
			}
			else if constexpr (_valid_variadic_construction_args_from_major_vectors<sizeof...(Args_), Args_...>())
			{
				using indices = EmuMath::TMP::make_full_matrix_index_sequences<this_type>;
				using column_indices = typename indices::column_index_sequence;
				using row_indices = typename indices::row_index_sequence;
				return _do_variadic_major_vector_construction(std::forward_as_tuple(std::forward<Args_>(args_)...), column_indices(), row_indices());
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
#pragma endregion

#pragma region CONSTRUCTORS
	public:
		/// <summary>
		/// <para> Default constructs this Matrix. Only available if this Matrix type's contained data is also default-constructible. </para>
		/// </summary>
		template<typename = std::enable_if_t<is_default_constructible()>>
		constexpr Matrix() :
			_data()
		{
		}

		/// <summary>
		/// <para> Performs a const-copy of the passed Matrix. Only available if this Matrix type's contained data can be const-copy-constructed. </para>
		/// </summary>
		/// <param name="to_copy_">: EmuMath Matrix of the same type to const-copy.</param>
		constexpr Matrix(const Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& to_const_copy) :
			_data(to_const_copy._data)
		{
			static_assert(is_const_copy_constructible(), "Attempted to const-copy-construct an EmuMath Matrix that cannot be const-copy-constructed.");
		}

		/// <summary>
		/// <para> Performs a non-const-copy of the passed Matrix. Only available if this Matrix type's contained data can be non-const-copy-constructed. </para>
		/// </summary>
		/// <param name="to_copy_">: EmuMath Matrix of the same type to copy.</param>
		template<std::size_t Unused_ = 0, typename = std::enable_if_t<is_non_const_copy_constructible<Unused_>()>>
		constexpr Matrix(Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& to_copy_) :
			_data(to_copy_._data)
		{
			static_assert(is_non_const_copy_constructible(), "Attempted to non-const-copy-construct an EmuMath Matrix that cannot be non-const-copy-constructed.");
		}

		/// <summary> Moves the passed Matrix data into a newly constructed Matrix. Only available if this Matrix type's contained data may be move-constructed. </summary>
		/// <param name="to_move_">: EmuMath Matrix of the same type to move.</param>
		constexpr Matrix(Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&& to_move_) noexcept :
			_data(std::move(to_move_._data))
		{
			static_assert(is_move_constructible(), "Attempted to non-const-copy-construct an EmuMath Vector that cannot be non-const-copy-constructed.");
		}
		

		/// <summary>
		/// <para> Constructs a Matrix of this type by converting respective Column+Row indices within the passed Matrix. </para>
		/// <para> Non-contained indices are interpreted as implied-zeroes. </para>
		/// <para>
		///		Only available if this Matrix type's contained data may be constructed from non-const lvalue references to respective indices in to_convert_, or an implied-zero.
		/// </para>
		/// </summary>
		/// <param name="to_convert_">: EmuMath Matrix of a different type to convert.</param>
		template
		<
			std::size_t OtherNumColumns_, std::size_t OtherNumRows_, typename OtherT_, bool OtherColumnMajor_,
			typename = std::enable_if_t<is_conversion_constructible<EmuMath::Matrix<OtherNumColumns_, OtherNumRows_, OtherT_, OtherColumnMajor_>&>()>
		>
		constexpr Matrix(EmuMath::Matrix<OtherNumColumns_, OtherNumRows_, OtherT_, OtherColumnMajor_>& to_convert_) :
			_data(_do_conversion_construction(to_convert_))
		{
		}

		/// <summary>
		/// <para> Constructs a Matrix of this type by converting respective Column+Row indices within the passed Matrix. </para>
		/// <para> Non-contained indices are interpreted as implied-zeroes. </para>
		/// <para>
		///		Only available if this Matrix type's contained data may be constructed from const lvalue references to respective indices in to_convert_, or an implied-zero.
		/// </para>
		/// </summary>
		/// <param name="to_convert_">: EmuMath Matrix of a different type to convert.</param>
		template
		<
			std::size_t OtherNumColumns_, std::size_t OtherNumRows_, typename OtherT_, bool OtherColumnMajor_,
			typename = std::enable_if_t<is_conversion_constructible<const EmuMath::Matrix<OtherNumColumns_, OtherNumRows_, OtherT_, OtherColumnMajor_>&>()>
		>
		constexpr Matrix(const EmuMath::Matrix<OtherNumColumns_, OtherNumRows_, OtherT_, OtherColumnMajor_>& to_convert_) :
			_data(_do_conversion_construction(to_convert_))
		{
		}

		/// <summary>
		/// <para> Constructs a Matrix of this type by converting respective Column+Row indices within the passed Matrix. </para>
		/// <para> Non-contained indices are interpreted as implied-zeroes. </para>
		/// <para> 
		///		Only available if this Matrix type's contained data may be constructed from rvalue references to respective indices in to_convert_, or an implied-zero. 
		///		The rvalue references are viewed as lvalue references when both this Matrix and to_convert_ contain recognised references.
		/// </para>
		/// </summary>
		/// <param name="to_convert_">: EmuMath Matrix of a different type to convert.</param>
		template
		<
			std::size_t OtherNumColumns_, std::size_t OtherNumRows_, typename OtherT_, bool OtherColumnMajor_,
			typename = std::enable_if_t<is_conversion_constructible<EmuMath::Matrix<OtherNumColumns_, OtherNumRows_, OtherT_, OtherColumnMajor_>&&>()>
		>
		constexpr Matrix(EmuMath::Matrix<OtherNumColumns_, OtherNumRows_, OtherT_, OtherColumnMajor_>&& to_convert_) :
			_data(_do_conversion_construction(std::forward<EmuMath::Matrix<OtherNumColumns_, OtherNumRows_, OtherT_, OtherColumnMajor_>>(to_convert_)))
		{
		}

		/// <summary>
		/// <para> Variadic construction which adapts based on the provided arguments, and will perform one of the following: </para>
		/// <para> 1: Where sizeof...(Args_) == size, arguments will be seen as contiguous element arguments and used directly in constructing the element they represent. </para>
		/// <para> 2: Where sizeof...(Args_) == 1, the one argument will be seen as a value to copy to all elements within the newly created Matrix. </para>
		/// <para>
		///		3: Where sizeof...(Args_) == num_major_elements and all arguments are EmuMath Vectors,
		///		the arguments will be seen as arguments for each major segment of this Matrix (i.e. columns if this Matrix is column-major, otherwise rows).
		/// </para>
		/// <para>
		///		All listed outcomes are not used if a non-variadic constructor would make use of that argument, 
		///		and are additionally subject to compatibility with this Matrix type's contained data. </para>
		/// <para> Where multiple potential outcomes are possible, the earliest listed will be prioritised. </para>
		/// </summary>
		/// <param name="args_">: Arguments for variadic construction, meeting at least 1 of the above constraints.</param>
		template<class...Args_, typename = std::enable_if_t<is_variadic_constructible<Args_...>()>>
		constexpr Matrix(Args_&&...args_) :
			_data(_do_variadic_construction(std::forward<Args_>(args_)...))
		{
		}
#pragma endregion

#pragma region ACCESS_FUNCS
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
					std::string str_;
					str_.reserve(180); // Reserves enough space for literals, + padding for index -> string conversions
					str_ += "Attempted to access an invalid Column + Row Index within an EmuMath Matrix.\nColumn: ";
					str_ += std::to_string(column_index_);
					str_ += ", Valid Column Range (Inclusive): 0:";
					str_ += std::to_string(num_columns - 1);
					str_ += "\nRow: ";
					str_ += std::to_string(row_index_);
					str_ += ", Valid Row Range (Inclusive): 0:";
					str_ += std::to_string(num_rows - 1);
					throw std::out_of_range(str_);
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
					std::string str_;
					str_.reserve(140); // Enough space for literals + some extra padding for converted index -> string appends
					str_ += "Attempted to access an invalid Flattened Index within an EmuMath Matrix.\nIndex:";
					str_ += std::to_string(flattened_index_);
					str_ += ", Valid Flattened Index Range (Inclusive): 0:";
					str_ += std::to_string(size - 1);
					throw std::out_of_range(str_);
				}
				else
				{
					throw std::out_of_range("Attempted to access an invalid Flattened Index within an EmuMath Matrix.");
				}
			}
			return _data[flattened_index_];
		}

		[[nodiscard]] constexpr inline const value_type& at(std::size_t flattened_index_) const
		{
			return const_cast<this_type*>(this)->at(flattened_index_);
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
					EmuCore::TMP::get_false<std::size_t, Offset_>(),
					"Attempted to access a contiguous data pointer for an EmuMath Matrix which contains references. As referenced data is not guaranteed to be contiguous, this behaviour is prohibited."
				);
			}
		}

		template<std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline const stored_type* data() const
		{
			return const_cast<this_type*>(this)->template data<Offset_>();
		}

		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		[[nodiscard]] constexpr inline stored_type* data()
		{
			if constexpr (ColumnIndex_ < num_columns)
			{
				if constexpr (RowIndex_ < num_rows)
				{
					constexpr std::size_t flattened_offset = get_flattened_index(ColumnIndex_, RowIndex_);
					return _data.data() + flattened_offset;
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<ColumnIndex_>(),
						"Attempted to access a contiguous data pointer for an EmuMath Matrix using a Column and Row offset, but the provided Row offset exceeds the Matrix's contained range."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<ColumnIndex_>(),
					"Attempted to access a contiguous data pointer for an EmuMath Matrix using a Column and Row offset, but the provided Column offset exceeds the Matrix's contained range."
				);
			}
		}

		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		[[nodiscard]] constexpr inline stored_type* data() const
		{
			return const_cast<this_type*>(this)->template data<ColumnIndex_, RowIndex_>();
		}

		/// <summary>
		/// <para> Outputs an EmuMath Vector of elements in the specified Column within this Matrix. </para>
		/// <para> May output a Vector of references to the elements of the Column, as long as all required indices are contained within this Matrix. </para>
		/// <para> Offset_: Index of the Row at which to start reading the Column at the provided ColumnIndex_. Defaults to 0. </para>
		/// </summary>
		/// <returns>EmuMath Vector of the specified Column within this Matrix.</returns>
		template<std::size_t ColumnIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Column() const
		{
			return _make_column_vector<ColumnIndex_, OutSize_, OutT_>(EmuCore::TMP::make_offset_index_sequence<Offset_, OutSize_>());
		}

		template<std::size_t ColumnIndex_, typename OutT_ = value_type_uq, std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<num_rows, OutT_> Column() const
		{
			return _make_column_vector<ColumnIndex_, num_rows, OutT_>(EmuCore::TMP::make_offset_index_sequence<Offset_, num_rows>());
		}

		template<std::size_t ColumnIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Column()
		{
			return _make_column_vector<ColumnIndex_, OutSize_, OutT_>(EmuCore::TMP::make_offset_index_sequence<Offset_, OutSize_>());
		}

		template<std::size_t ColumnIndex_, typename OutT_ = value_type_uq, std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<num_rows, OutT_> Column()
		{
			return _make_column_vector<ColumnIndex_, num_rows, OutT_>(EmuCore::TMP::make_offset_index_sequence<Offset_, num_rows>());
		}

		/// <summary>
		/// <para> Outputs an EmuMath Vector of elements in the specified Row within this Matrix. </para>
		/// <para> May output a Vector of references to the elements of the Row, as long as all required indices are contained within this Matrix. </para>
		/// <para> Offset_: Index of the Column at which to start reading the Row at the provided RowIndex_. Defaults to 0. </para>
		/// </summary>
		/// <returns>EmuMath Vector of the specified Row within this Matrix.</returns>
		template<std::size_t RowIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Row() const
		{
			return _make_row_vector<RowIndex_, OutSize_, OutT_>(EmuCore::TMP::make_offset_index_sequence<Offset_, OutSize_>());
		}

		template<std::size_t RowIndex_, typename OutT_ = value_type_uq, std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<num_columns, OutT_> Row() const
		{
			return _make_row_vector<RowIndex_, num_columns, OutT_>(EmuCore::TMP::make_offset_index_sequence<Offset_, num_columns>());
		}

		template<std::size_t RowIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Row()
		{
			return _make_row_vector<RowIndex_, OutSize_, OutT_>(EmuCore::TMP::make_offset_index_sequence<Offset_, OutSize_>());
		}

		template<std::size_t RowIndex_, typename OutT_ = value_type_uq, std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<num_columns, OutT_> Row()
		{
			return _make_row_vector<RowIndex_, num_columns, OutT_>(EmuCore::TMP::make_offset_index_sequence<Offset_, num_columns>());
		}

		/// <summary>
		/// <para> Outputs an EmuMath Vector of elements in the specified Major Segment within this Matrix. </para>
		/// <para> May output a Vector of references to the elements of the Major Segment, as long as all required indices are contained within this Matrix. </para>
		/// <para> If this Matrix is Column Major, this is equivalent to `Column`. Otherwise, it is equivalent to `Row`. </para>
		/// <para> Offset_: Non-Major index at which to start reading the Major Segment at the provided MajorIndex_. Defaults to 0. </para>
		/// </summary>
		/// <returns>EmuMath Vector of the specified Major Segment within this Matrix.</returns>
		template<std::size_t MajorIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Major() const
		{
			return _make_major_vector<MajorIndex_, OutSize_, OutT_>(EmuCore::TMP::make_offset_index_sequence<Offset_, OutSize_>());
		}

		template<std::size_t MajorIndex_, typename OutT_ = value_type_uq, std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<num_non_major_elements, OutT_> Major() const
		{
			return _make_major_vector<MajorIndex_, num_non_major_elements, OutT_>(EmuCore::TMP::make_offset_index_sequence<Offset_, num_non_major_elements>());
		}

		template<std::size_t MajorIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Major()
		{
			return _make_major_vector<MajorIndex_, OutSize_, OutT_>(EmuCore::TMP::make_offset_index_sequence<Offset_, OutSize_>());
		}

		template<std::size_t MajorIndex_, typename OutT_ = value_type_uq, std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<num_non_major_elements, OutT_> Major()
		{
			return _make_major_vector<MajorIndex_, num_non_major_elements, OutT_>(EmuCore::TMP::make_offset_index_sequence<Offset_, num_non_major_elements>());
		}

		/// <summary>
		/// <para> Outputs an EmuMath Vector of elements in the specified Non-Major Segment within this Matrix. </para>
		/// <para> May output a Vector of references to the elements of the Non-Major Segment, as long as all required indices are contained within this Matrix. </para>
		/// <para> If this Matrix is Column Major, this is equivalent to `Row`. Otherwise, it is equivalent to `Column`. </para>
		/// <para> Offset_: Major index at which to start reading the Non-Major Segment at the provided NonMajorIndex_. Defaults to 0. </para>
		/// </summary>
		/// <returns>EmuMath Vector of the specified Non-Major Segment within this Matrix.</returns>
		template<std::size_t NonMajorIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> NonMajor() const
		{
			return _make_non_major_vector<NonMajorIndex_, OutSize_, OutT_>(EmuCore::TMP::make_offset_index_sequence<Offset_, OutSize_>());
		}

		template<std::size_t NonMajorIndex_, typename OutT_ = value_type_uq, std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<num_major_elements, OutT_> NonMajor() const
		{
			return _make_non_major_vector<NonMajorIndex_, num_major_elements, OutT_>(EmuCore::TMP::make_offset_index_sequence<Offset_, num_major_elements>());
		}

		template<std::size_t NonMajorIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> NonMajor()
		{
			return _make_non_major_vector<NonMajorIndex_, OutSize_, OutT_>(EmuCore::TMP::make_offset_index_sequence<Offset_, OutSize_>());
		}

		template<std::size_t NonMajorIndex_, typename OutT_ = value_type_uq, std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<num_major_elements, OutT_> NonMajor()
		{
			return _make_non_major_vector<NonMajorIndex_, num_major_elements, OutT_>(EmuCore::TMP::make_offset_index_sequence<Offset_, num_major_elements>());
		}

		/// <summary>
		/// <para> Outputs an EmuMath Vector of elements within the specified Diagonal Segment within this Matrix, defaulting to its main diagonal. </para>
		/// <para> ColumnOffset_: Index of the first Column to access. This will increment by 1 for each progressive element in the output Vector. Defaults to 0. </para>
		/// <para> RowOffset_: Index of the first Row to access. This will increment by 1 for each progressive element in the output Vector. Defaults to ColumnOffset_. </para>
		/// <para> May output a Vector of references to the elements of the Diagonal Segment, as long as all required indices are contained within this Matrix. </para>
		/// </summary>
		/// <returns>EmuMath Vector of the specified Diagonal Segment within this Matrix.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type_uq, std::size_t ColumnOffset_ = 0, std::size_t RowOffset_ = ColumnOffset_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Diagonal() const
		{
			return _make_diagonal_vector<OutSize_, OutT_, ColumnOffset_, RowOffset_>(std::make_index_sequence<OutSize_>());
		}

		template<typename OutT_ = value_type_uq, std::size_t ColumnOffset_ = 0, std::size_t RowOffset_ = ColumnOffset_>
		[[nodiscard]] constexpr inline EmuMath::Vector<smallest_direction_size, OutT_> Diagonal() const
		{
			return _make_diagonal_vector<smallest_direction_size, OutT_, ColumnOffset_, RowOffset_>(std::make_index_sequence<smallest_direction_size>());
		}

		template<std::size_t OutSize_, typename OutT_ = value_type_uq, std::size_t ColumnOffset_ = 0, std::size_t RowOffset_ = ColumnOffset_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Diagonal()
		{
			return _make_diagonal_vector<OutSize_, OutT_, ColumnOffset_, RowOffset_>(std::make_index_sequence<OutSize_>());
		}

		template<typename OutT_ = value_type_uq, std::size_t ColumnOffset_ = 0, std::size_t RowOffset_ = ColumnOffset_>
		[[nodiscard]] constexpr inline EmuMath::Vector<smallest_direction_size, OutT_> Diagonal()
		{
			return _make_diagonal_vector<smallest_direction_size, OutT_, ColumnOffset_, RowOffset_>(std::make_index_sequence<smallest_direction_size>());
		}

		/// <summary>
		/// <para> Outputs an EmuMath Vector representing a flattened form of this Matrix. </para>
		/// <para> The output Vector may be either column-major or row-major, and will follow the major-order of this Matrix if not explicitly specified. </para>
		/// <para> May be used to output a flattened Vector of references. </para>
		/// </summary>
		/// <returns>EmuMath Vector representation of a flattened form of this Matrix.</returns>
		template<typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Flatten() const
		{
			using indices = EmuMath::TMP::make_ranged_matrix_index_sequences<0, num_columns, 0, num_rows, OutColumnMajor_>;
			return _make_flattened_vector<size, OutT_>(typename indices::column_index_sequence(), typename indices::row_index_sequence());
		}

		template<bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, value_type_uq> Flatten() const
		{
			using indices = EmuMath::TMP::make_ranged_matrix_index_sequences<0, num_columns, 0, num_rows, OutColumnMajor_>;
			return _make_flattened_vector<size, value_type_uq>(typename indices::column_index_sequence(), typename indices::row_index_sequence());
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Flatten()
		{
			using indices = EmuMath::TMP::make_ranged_matrix_index_sequences<0, num_columns, 0, num_rows, OutColumnMajor_>;
			return _make_flattened_vector<size, OutT_>(typename indices::column_index_sequence(), typename indices::row_index_sequence());
		}

		template<bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, value_type_uq> Flatten()
		{
			using indices = EmuMath::TMP::make_ranged_matrix_index_sequences<0, num_columns, 0, num_rows, OutColumnMajor_>;
			return _make_flattened_vector<size, value_type_uq>(typename indices::column_index_sequence(), typename indices::row_index_sequence());
		}
#pragma endregion

#pragma region ACCESS_OPERATORS
	public:
		/// <summary>
		/// <para> Accesses the element at the provided contiguous flattened index within this Matrix. </para>
		/// <para> Performs no validity checks, and behaviour when flattened_index_ is not in the valid range (0:size-1) is undefined. </para>
		/// </summary>
		/// <param name="flattened_index_">: Contiguous flattened index of the element to access.</param>
		/// <returns>Reference to the element at the provided contiguous flattened index within this Matrix.</returns>
		[[nodiscard]] constexpr inline const value_type& operator[](std::size_t flattened_index_) const
		{
			return _data[flattened_index_];
		}

		[[nodiscard]] constexpr inline value_type& operator[](std::size_t flattened_index_)
		{
			return _data[flattened_index_];
		}

		/// <summary>
		/// <para> Accesses the element at the provided Column + Row Index within this Matrix. </para>
		/// <para> Performs no validity checks, and behaviour when either index is in invalid is undefined. </para>
		/// </summary>
		/// <param name="column_row_index_pair_">: Pair of indices to use as Column + Row Index arguments; first is the column index, second is the row index. </param>
		/// <returns>Reference to the element at the provided Column + Row Index within this Matrix.</returns>
		[[nodiscard]] constexpr inline const value_type& operator[](const std::pair<std::size_t, std::size_t>& column_row_index_pair_) const
		{
			return _data[get_flattened_index(column_row_index_pair_)];
		}

		[[nodiscard]] constexpr inline value_type& operator[](const std::pair<std::size_t, std::size_t>& column_row_index_pair_)
		{
			return _data[get_flattened_index(column_row_index_pair_)];
		}

		/// <summary>
		/// <para> Accesses the element at the provided contiguous flattened index within this Matrix. </para>
		/// <para> Performs no validity checks, and behaviour when flattened_index_ is not in the valid range (0:size-1) is undefined. </para>
		/// </summary>
		/// <param name="flattened_index_">: Contiguous flattened index of the element to access.</param>
		/// <returns>Reference to the element at the provided contiguous flattened index within this Matrix.</returns>
		[[nodiscard]] constexpr inline const value_type& operator()(std::size_t flattened_index_) const
		{
			return _data[flattened_index_];
		}

		[[nodiscard]] constexpr inline value_type& operator()(std::size_t flattened_index_)
		{
			return _data[flattened_index_];
		}

		/// <summary>
		/// <para> Accesses the element at the provided Column + Row Index within this Matrix. </para>
		/// <para> Performs no validity checks, and behaviour when either index is in invalid is undefined. </para>
		/// </summary>
		/// <param name="column_index_">: Index of the Column to access.</param>
		/// <param name="row_index_">: Index of the Row to access.</param>
		/// <returns>Reference to the element at the provided Column + Row Index within this Matrix.</returns>
		[[nodiscard]] constexpr inline const value_type& operator()(std::size_t column_index_, std::size_t row_index_) const
		{
			return _data[get_flattened_index(column_index_, row_index_)];
		}

		[[nodiscard]] constexpr inline value_type& operator()(std::size_t column_index_, std::size_t row_index_)
		{
			return _data[get_flattened_index(column_index_, row_index_)];
		}

		/// <summary>
		/// <para> Accesses the element at the provided Column + Row Index within this Matrix. </para>
		/// <para> Performs no validity checks, and behaviour when either index is in invalid is undefined. </para>
		/// </summary>
		/// <param name="column_row_index_pair_">: Pair of indices to use as Column + Row Index arguments; first is the column index, second is the row index. </param>
		/// <returns>Reference to the element at the provided Column + Row Index within this Matrix.</returns>
		[[nodiscard]] constexpr inline const value_type& operator()(const std::pair<std::size_t, std::size_t>& column_row_index_pair_) const
		{
			return _data[get_flattened_index(column_row_index_pair_)];
		}

		[[nodiscard]] constexpr inline value_type& operator()(const std::pair<std::size_t, std::size_t>& column_row_index_pair_)
		{
			return _data[get_flattened_index(column_row_index_pair_)];
		}
#pragma endregion

#pragma region STL_ACCESS
		[[nodiscard]] constexpr inline const_iterator cbegin() const
		{
			return _data.cbegin();
		}

		[[nodiscard]] constexpr inline const_iterator cend() const
		{
			return _data.cend();
		}

		[[nodiscard]] constexpr inline const_reverse_iterator crbegin() const
		{
			return _data.crbegin();
		}

		[[nodiscard]] constexpr inline const_reverse_iterator crend() const
		{
			return _data.crend();
		}

		[[nodiscard]] constexpr inline iterator begin()
		{
			return _data.begin();
		}

		[[nodiscard]] constexpr inline const_iterator begin() const
		{
			return _data.cbegin();
		}

		[[nodiscard]] constexpr inline iterator end()
		{
			return _data.end();
		}

		[[nodiscard]] constexpr inline const_iterator end() const
		{
			return _data.cend();
		}

		[[nodiscard]] constexpr inline reverse_iterator rbegin()
		{
			return _data.rbegin();
		}

		[[nodiscard]] constexpr inline const_reverse_iterator rbegin() const
		{
			return _data.crbegin();
		}

		[[nodiscard]] constexpr inline reverse_iterator rend()
		{
			return _data.rend();
		}

		[[nodiscard]] constexpr inline const_reverse_iterator rend() const
		{
			return _data.crend();
		}
#pragma endregion

#pragma region ASSIGNMENT_OPERATORS
	public:
		constexpr inline this_type& operator=(const this_type& to_move_)
		{
			EmuMath::Helpers::matrix_copy(*this, std::forward<this_type>(to_move_));
			return *this;
		}

		constexpr inline this_type& operator=(this_type&& to_move_) noexcept
		{
			EmuMath::Helpers::matrix_copy(*this, std::forward<this_type>(to_move_));
			return *this;
		}

		template<std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_>
		constexpr inline auto operator=(EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& to_copy_)
			-> std::enable_if_t
			<
				EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&>(),
				this_type&
			>
		{
			EmuMath::Helpers::matrix_copy(*this, to_copy_);
			return *this;
		}

		template<std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_>
		constexpr inline auto operator=(const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& to_copy_)
			-> std::enable_if_t
			<
				EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&>() &&
				!std::is_same_v<this_type, EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>,
				this_type&
			>
		{
			EmuMath::Helpers::matrix_copy(*this, to_copy_);
			return *this;
		}

		template<std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_>
		constexpr inline auto operator=(EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&& to_move_copy_)
			-> std::enable_if_t
			<
				EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>() &&
				!std::is_same_v<this_type, EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>,
				this_type&
			>
		{
			EmuMath::Helpers::matrix_copy
			(
				*this,
				std::forward<EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>(to_move_copy_)
			);
			return *this;
		}

		template<std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_>
		constexpr inline auto operator=(const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&& to_move_copy_)
			-> std::enable_if_t
			<
				EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>(),
				this_type&
			>
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
		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline auto operator*(Rhs_&& rhs_) const
			-> std::enable_if_t<!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>(), EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_>>
		{
			return EmuMath::Helpers::matrix_multiply<OutT_, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline auto operator*(Rhs_&& rhs_) const
			-> std::enable_if_t<!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>(), EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_>>
		{
			return EmuMath::Helpers::matrix_multiply<value_type_uq, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		// ADAPTIVE ARITHMETIC OPERATOR*: SPECIALISED VECTOR MULTIPLY
		template<typename OutT_, bool OutColumnMajor_ = is_column_major, typename RhsT_, std::size_t RhsSize_>
		[[nodiscard]] constexpr inline auto operator*(const EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_) const
			-> std::enable_if_t<valid_vector_multiply_arg_size<RhsSize_>(), EmuMath::Vector<RhsSize_, OutT_>>
		{
			return EmuMath::Helpers::matrix_multiply<OutT_, OutColumnMajor_>(*this, rhs_vector_);
		}

		template<bool OutColumnMajor_ = is_column_major, typename RhsT_, std::size_t RhsSize_>
		[[nodiscard]] constexpr inline auto operator*(const EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_) const
			-> std::enable_if_t
			<
				valid_vector_multiply_arg_size<RhsSize_>(),
				EmuMath::Vector<RhsSize_, typename EmuMath::Vector<RhsSize_, RhsT_>::preferred_floating_point>
			>
		{
			using rhs_fp = typename EmuMath::Vector<RhsSize_, RhsT_>::preferred_floating_point;
			return EmuMath::Helpers::matrix_multiply<rhs_fp, OutColumnMajor_>(*this, rhs_vector_);
		}

		// ADAPTIVE ARITHMETIC OPERATOR*: SPECIALISED MATRIX MULTIPLY
		template<typename OutT_, bool OutColumnMajor_ = is_column_major, typename RhsT_, std::size_t RhsNumColumns_, std::size_t RhsNumRows_, bool RhsColumnMajor_>
		[[nodiscard]] constexpr inline auto operator*(const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_) const
			-> std::enable_if_t<valid_matrix_multiply_arg_size<RhsNumColumns_, RhsNumRows_>(), EmuMath::Matrix<RhsNumColumns_, num_rows, OutT_, OutColumnMajor_>>
		{
			return EmuMath::Helpers::matrix_multiply<OutT_, OutColumnMajor_>(*this, rhs_matrix_);
		}

		template<bool OutColumnMajor_ = is_column_major, typename RhsT_, std::size_t RhsNumColumns_, std::size_t RhsNumRows_, bool RhsColumnMajor_>
		[[nodiscard]] constexpr inline auto operator*(const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_) const
			-> std::enable_if_t
			<
				valid_matrix_multiply_arg_size<RhsNumColumns_, RhsNumRows_>(),
				EmuMath::Matrix<RhsNumColumns_, num_rows, preferred_floating_point, OutColumnMajor_>
			>
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

		template<bool ColumnMajorOrder_ = is_column_major, class Rhs_>
		constexpr inline auto operator*=(Rhs_&& rhs_)
			-> std::enable_if_t<!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>(), this_type&>
		{
			EmuMath::Helpers::matrix_multiply_assign<ColumnMajorOrder_>(*this, std::forward<Rhs_>(rhs_));
			return *this;
		}

		template<bool ColumnMajorOrder_ = is_column_major, std::size_t RhsSize_, typename RhsT_>
		constexpr inline auto operator*=(EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_) const
			-> std::enable_if_t
			<
				EmuMath::Helpers::is_valid_matrix_multiply_assign_rhs_vector<NumColumns_, NumRows_, T_, ColumnMajor_, RhsSize_, RhsT_>(),
				EmuMath::Vector<RhsSize_, RhsT_>&
			>
		{
			EmuMath::Helpers::matrix_multiply_assign<ColumnMajorOrder_>(*this, rhs_vector_);
			return rhs_vector_;
		}

		template<bool ColumnMajorOrder_ = is_column_major, std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_>
		constexpr inline auto operator*=(const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_)
			-> std::enable_if_t
			<
				valid_matrix_multiply_arg_size<RhsNumColumns_, RhsNumRows_>() && is_square&& RhsNumColumns_ == num_columns && RhsNumRows_ == num_rows,
				this_type&
			>
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
		template<std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_>
		constexpr inline auto Copy(EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& to_copy_)
			-> std::enable_if_t
			<
				EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&>(),
				void
			>
		{
			EmuMath::Helpers::matrix_copy(*this, to_copy_);
		}

		template<std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_>
		constexpr inline auto Copy(const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& to_copy_)
			-> std::enable_if_t
			<
				EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&>(),
				void
			>
		{
			EmuMath::Helpers::matrix_copy(*this, to_copy_);
		}

		template<std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_>
		constexpr inline auto Copy(EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&& to_move_copy_)
			-> std::enable_if_t
			<
				EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>(),
				void
			>
		{
			EmuMath::Helpers::matrix_copy
			(
				*this,
				std::forward<EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>(to_move_copy_)
			);
		}

		template<std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_>
		constexpr inline auto Copy(const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&& to_move_copy_)
			-> std::enable_if_t
			<
				EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>(),
				void
			>
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
		/// <para> Indices outside of the provided range will be defaulted. </para>
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
		/// <para> Indices outside of the provided range will be defaulted. </para>
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
		/// <para> Indices outside of the provided range will be defaulted. </para>
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
		/// <para> Indices outside of the provided range will be defaulted. </para>
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
		/// <para> Indices outside of the provided range will be defaulted. </para>
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
		/// <para> Indices outside of the provided range will be defaulted. </para>
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
		/// <para> Indices outside of the provided range will be defaulted. </para>
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
		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline auto Multiply(Rhs_&& rhs_) const
			-> std::enable_if_t<!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>(), EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_>>
		{
			return EmuMath::Helpers::matrix_multiply<OutT_, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<bool OutColumnMajor_ = is_column_major, class Rhs_>
		[[nodiscard]] constexpr inline auto Multiply(Rhs_&& rhs_) const
			-> std::enable_if_t<!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>(), EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_>>
		{
			return EmuMath::Helpers::matrix_multiply<value_type_uq, OutColumnMajor_>(*this, std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		constexpr inline auto Multiply(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Rhs_&& rhs_) const
			-> std::enable_if_t<!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>(), void>
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
		template<bool ColumnMajorOrder_ = is_column_major, class Rhs_>
		constexpr inline auto MultiplyAssign(Rhs_&& rhs_)
			-> std::enable_if_t<!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>(), void>
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
		template<bool ColumnMajorOrder_ = is_column_major, std::size_t Unused_ = 0>
		constexpr inline auto SquareAssign()
			-> std::enable_if_t<valid_matrix_multiply_arg_size<NumColumns_, NumRows_, Unused_>(), this_type&>
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
		/// <para> Indices outside of the provided range will be defaulted. </para>
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
		/// <para> Indices outside of the provided range will be defaulted. </para>
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
		/// <para> Indices outside of the provided range will be defaulted. </para>
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
		/// <para> Indices outside of the provided range will be defaulted. </para>
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
		/// <para> Indices outside of the provided range will be defaulted. </para>
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
		/// <para> Indices outside of the provided range will be defaulted. </para>
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
		/// <para> Indices outside of the provided range will be defaulted. </para>
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
		///		If B_ is an EmuMath Matrix: Comparisons will be performed with respective indices in this Matrix and b_. 
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
		/// <para> Indices outside of the provided range will be defaulted. </para>
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

		/// <summary>
		/// <para> Outputs the greatest element within this Matrix as the provided Out_ type, defaulting to this Matrix's value_type_uq. </para>
		/// <para> Supports output of references if the reference type is compatible with const-qualification. </para>
		/// </summary>
		/// <returns>Greaetst element of this Matrix, as the provided Out_ type.</returns>
		template<typename Out_ = value_type_uq>
		[[nodiscard]] constexpr inline Out_ Max() const
		{
			return EmuMath::Helpers::matrix_max<Out_>(*this);
		}

		template<typename Out_ = value_type_uq>
		[[nodiscard]] constexpr inline Out_ Max()
		{
			return EmuMath::Helpers::matrix_max<Out_>(*this);
		}

		/// <summary>
		/// <para> Outputs an EmuMath Matrix composed of the greatest elements out of this Matrix and b_. </para>
		/// <para>
		///		If B_ is an EmuMath Matrix: Comparisons will be performed with respective indices in this Matrix and b_. 
		///		Otherwise, all indices will be compared with b_ directly.
		/// </para>
		/// </summary>
		/// <param name="b_">: Scalar or EmuMath Matrix appearing as b in a max(a, b) operation.</param>
		/// <returns>EmuMath Matrix composed of max results in respective indices.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> Max(B_&& b_) const
		{
			return EmuMath::Helpers::matrix_min<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this, std::forward<B_>(b_));
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> Max(B_&& b_) const
		{
			return EmuMath::Helpers::matrix_max<num_columns, num_rows, OutT_, OutColumnMajor_>(*this, std::forward<B_>(b_));
		}

		template<bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> Max(B_&& b_) const
		{
			return EmuMath::Helpers::matrix_max<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this, std::forward<B_>(b_));
		}

		template<class B_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		constexpr inline void Max(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, B_&& b_) const
		{
			EmuMath::Helpers::matrix_max(out_matrix_, *this, std::forward<B_>(b_));
		}

		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> Max(B_&& b_)
		{
			return EmuMath::Helpers::matrix_max<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this, std::forward<B_>(b_));
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> Max(B_&& b_)
		{
			return EmuMath::Helpers::matrix_max<num_columns, num_rows, OutT_, OutColumnMajor_>(*this, std::forward<B_>(b_));
		}

		template<bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> Max(B_&& b_)
		{
			return EmuMath::Helpers::matrix_max<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this, std::forward<B_>(b_));
		}

		template<class B_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		constexpr inline void Max(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, B_&& b_)
		{
			EmuMath::Helpers::matrix_max(out_matrix_, *this, std::forward<B_>(b_));
		}

		/// <summary>
		/// <para> Outputs the greatest element within this Matrix as the provided Out_ type, defaulting to this Matrix's value_type_uq. </para>
		/// <para> Only elements within the provided range will be considered. </para>
		/// <para> Supports output of references if the reference type is compatible with const-qualification, and the provided range contains no theoretical indices. </para>
		/// </summary>
		/// <returns>Greatest element of this Matrix within the provided range, as the provided Out_ type.</returns>
		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename Out_ = value_type_uq>
		[[nodiscard]] constexpr inline Out_ MaxRange() const
		{
			return EmuMath::Helpers::matrix_max_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, Out_>(*this);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename Out_ = value_type_uq>
		[[nodiscard]] constexpr inline Out_ MaxRange()
		{
			return EmuMath::Helpers::matrix_max_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, Out_>(*this);
		}

		/// <summary>
		/// <para> Outputs an EmuMath Matrix composed of the greatest elements out of this Matrix and b_. </para>
		/// <para>
		///		If B_ is an EmuMath Matrix: Comparisons will be performed with respective indices in this Matrix and b_. 
		///		Otherwise, all indices will be compared with b_ directly.
		/// </para>
		/// <para> Indices within the provided range will be the respective maximum element out of this Matrix and b_. </para>
		/// <para> Indices outside of the provided range will be copies of the respective element within this Matrix. </para>
		/// </summary>
		/// <param name="b_">: Scalar or EmuMath Matrix appearing as b in a max(a, b) operation.</param>
		/// <returns>EmuMath Matrix composed of max results in respective indices within the provided range, and copies of respective indices within this Matrix elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class B_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> MaxRange(B_&& b_) const
		{
			return EmuMath::Helpers::matrix_max_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
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
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> MaxRange(B_&& b_) const
		{
			return EmuMath::Helpers::matrix_max_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> MaxRange(B_&& b_) const
		{
			return EmuMath::Helpers::matrix_max_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
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
		constexpr inline void MaxRange(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, B_&& b_) const
		{
			EmuMath::Helpers::matrix_max_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<B_>(b_));
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class B_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> MaxRange(B_&& b_)
		{
			return EmuMath::Helpers::matrix_max_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
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
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> MaxRange(B_&& b_)
		{
			return EmuMath::Helpers::matrix_max_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> MaxRange(B_&& b_)
		{
			return EmuMath::Helpers::matrix_max_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
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
		constexpr inline void MaxRange(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, B_&& b_)
		{
			EmuMath::Helpers::matrix_max_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<B_>(b_));
		}

		/// <summary>
		/// <para> Outputs an EmuMath Matrix composed of the greatest elements out of this Matrix and b_. </para>
		/// <para>
		///		If B_ is an EmuMath Matrix: Comparisons will be performed with respective indices in this Matrix and b_. 
		///		Otherwise, all of this Matrix's indices will be compared with b_ directly.
		/// </para>
		/// <para> Indices within the provided range will be the respective maximum element out of this Matrix and b_. </para>
		/// <para> Indices outside of the provided range will be defaulted. </para>
		/// </summary>
		/// <param name="b_">: Scalar or EmuMath Matrix appearing as b in a max(a, b) operation.</param>
		/// <returns>EmuMath Matrix composed of max results in respective indices within the provided range, and default-constructed elements elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class B_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> MaxRangeNoCopy(B_&& b_) const
		{
			return EmuMath::Helpers::matrix_max_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> MaxRangeNoCopy(B_&& b_) const
		{
			return EmuMath::Helpers::matrix_max_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> MaxRangeNoCopy(B_&& b_) const
		{
			return EmuMath::Helpers::matrix_max_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
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
		constexpr inline void MaxRangeNoCopy(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, B_&& b_) const
		{
			EmuMath::Helpers::matrix_max_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<B_>(b_));
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class B_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> MaxRangeNoCopy(B_&& b_)
		{
			return EmuMath::Helpers::matrix_max_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> MaxRangeNoCopy(B_&& b_)
		{
			return EmuMath::Helpers::matrix_max_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class B_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> MaxRangeNoCopy(B_&& b_)
		{
			return EmuMath::Helpers::matrix_max_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
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
		constexpr inline void MaxRangeNoCopy(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, B_&& b_)
		{
			EmuMath::Helpers::matrix_max_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<B_>(b_));
		}

		/// <summary>
		/// <para> Outputs a version of this Matrix with its elements linearly interpolated with b_ using a weighting of t_. </para>
		/// <para> If B_ is an EmuMath Matrix: Elements will be interpolated with respective elements of b_. Otherwise, all will be interpolated with b_ directly. </para>
		/// <para> If ArgT_ is an EmuMath Matrix: Linear interpolations will use respective elements in t_ as weightings. Otherwise, all interpolations will use t_ directly. </para>
		/// </summary>
		/// <param name="b_">: Scalar or EmuMath Matrix to use as the target point for linear interpolation.</param>
		/// <param name="t_">: Scalar or EmuMath Matrix to use as weighting for linear interpolations, where lerp(a, b, 0) = a, lerp(a, b, 1) = b.</param>
		/// <returns>Copy of this Matrix with its elements linearly interpolated, summarised as `out = a + ((b - a) * t)`.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = preferred_floating_point, bool OutColumnMajor_ = is_column_major, class B_, class ArgT_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> Lerp(B_&& b_, ArgT_&& t_) const
		{
			return EmuMath::Helpers::matrix_lerp<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this, std::forward<B_>(b_), std::forward<ArgT_>(t_));
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class B_, class ArgT_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> Lerp(B_&& b_, ArgT_&& t_) const
		{
			return EmuMath::Helpers::matrix_lerp<num_columns, num_rows, OutT_, OutColumnMajor_>(*this, std::forward<B_>(b_), std::forward<ArgT_>(t_));
		}

		template<bool OutColumnMajor_ = is_column_major, class B_, class ArgT_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, preferred_floating_point, OutColumnMajor_> Lerp(B_&& b_, ArgT_&& t_) const
		{
			return EmuMath::Helpers::matrix_lerp<num_columns, num_rows, preferred_floating_point, OutColumnMajor_>(*this, std::forward<B_>(b_), std::forward<ArgT_>(t_));
		}

		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, class B_, class ArgT_>
		constexpr inline void Lerp(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, B_&& b_, ArgT_&& t_) const
		{
			EmuMath::Helpers::matrix_lerp(out_matrix_, *this, std::forward<B_>(b_), std::forward<ArgT_>(t_));
		}
				
		/// <summary>
		/// <para> Outputs a version of this Matrix with its elements linearly interpolated with b_ using a weighting of t_. </para>
		/// <para> If B_ is an EmuMath Matrix: Elements will be interpolated with respective elements of b_. Otherwise, all will be interpolated with b_ directly. </para>
		/// <para> If ArgT_ is an EmuMath Matrix: Linear interpolations will use respective elements in t_ as weightings. Otherwise, all interpolations will use t_ directly. </para>
		/// <para> Indices within the provided range will contain respective linear interpolation results. </para>
		/// <para> Indices outside of the provided range will be copies of respective indices in this Matrix. </para>
		/// </summary>
		/// <param name="b_">: Scalar or EmuMath Matrix to use as the target point for linear interpolation.</param>
		/// <param name="t_">: Scalar or EmuMath Matrix to use as weighting for linear interpolations, where lerp(a, b, 0) = a, lerp(a, b, 1) = b.</param>
		/// <returns>Copy of this Matrix with elements in the provided range linearly interpolated, summarised as `out = a + ((b - a) * t)`, and copied elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = preferred_floating_point, bool OutColumnMajor_ = is_column_major, class B_, class ArgT_
		>
			[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> LerpRange(B_&& b_, ArgT_&& t_) const
		{
			return EmuMath::Helpers::matrix_lerp_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
				(
					*this,
					std::forward<B_>(b_),
					std::forward<ArgT_>(t_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			typename OutT_, bool OutColumnMajor_ = is_column_major, class B_, class ArgT_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> LerpRange(B_&& b_, ArgT_&& t_) const
		{
			return EmuMath::Helpers::matrix_lerp_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_),
				std::forward<ArgT_>(t_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class B_, class ArgT_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, preferred_floating_point, OutColumnMajor_> LerpRange(B_&& b_, ArgT_&& t_) const
		{
			return EmuMath::Helpers::matrix_lerp_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, preferred_floating_point, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_),
				std::forward<ArgT_>(t_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, class B_, class ArgT_
		>
		constexpr inline void LerpRange(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, B_&& b_, ArgT_&& t_) const
		{
			EmuMath::Helpers::matrix_lerp_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<B_>(b_), std::forward<ArgT_>(t_));
		}

		/// <summary>
		/// <para> Outputs a version of this Matrix with its elements linearly interpolated with b_ using a weighting of t_. </para>
		/// <para> If B_ is an EmuMath Matrix: Elements will be interpolated with respective elements of b_. Otherwise, all will be interpolated with b_ directly. </para>
		/// <para> If ArgT_ is an EmuMath Matrix: Linear interpolations will use respective elements in t_ as weightings. Otherwise, all interpolations will use t_ directly. </para>
		/// <para> Indices within the provided range will contain respective linear interpolation results. </para>
		/// <para> Indices outside of the provided range will be defaulted. </para>
		/// </summary>
		/// <param name="b_">: Scalar or EmuMath Matrix to use as the target point for linear interpolation.</param>
		/// <param name="t_">: Scalar or EmuMath Matrix to use as weighting for linear interpolations, where lerp(a, b, 0) = a, lerp(a, b, 1) = b.</param>
		/// <returns>Copy of this Matrix with elements in the provided range linearly interpolated, summarised as `out = a + ((b - a) * t)`, and default elements elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = preferred_floating_point, bool OutColumnMajor_ = is_column_major, class B_, class ArgT_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> LerpRangeNoCopy(B_&& b_, ArgT_&& t_) const
		{
			return EmuMath::Helpers::matrix_lerp_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_),
				std::forward<ArgT_>(t_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			typename OutT_, bool OutColumnMajor_ = is_column_major, class B_, class ArgT_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> LerpRangeNoCopy(B_&& b_, ArgT_&& t_) const
		{
			return EmuMath::Helpers::matrix_lerp_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_),
				std::forward<ArgT_>(t_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class B_, class ArgT_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, preferred_floating_point, OutColumnMajor_> LerpRangeNoCopy(B_&& b_, ArgT_&& t_) const
		{
			return EmuMath::Helpers::matrix_lerp_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, preferred_floating_point, OutColumnMajor_>
			(
				*this,
				std::forward<B_>(b_),
				std::forward<ArgT_>(t_)
			);
		}

		/// <summary>
		/// <para> Outputs a version of this Matrix with its elements linearly interpolated with b_ using a weighting of t_, via the provided out_matrix_. </para>
		/// <para> If B_ is an EmuMath Matrix: Elements will be interpolated with respective elements of b_. Otherwise, all will be interpolated with b_ directly. </para>
		/// <para> If ArgT_ is an EmuMath Matrix: Linear interpolations will use respective elements in t_ as weightings. Otherwise, all interpolations will use t_ directly. </para>
		/// <para> Indices within the provided range will contain respective linear interpolation results. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// </summary>
		/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
		/// <param name="b_">: Scalar or EmuMath Matrix to use as the target point for linear interpolation.</param>
		/// <param name="t_">: Scalar or EmuMath Matrix to use as weighting for linear interpolations, where lerp(a, b, 0) = a, lerp(a, b, 1) = b.</param>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, class B_, class ArgT_
		>
		constexpr inline void LerpRangeNoCopy(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, B_&& b_, ArgT_&& t_) const
		{
			EmuMath::Helpers::matrix_lerp_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<B_>(b_), std::forward<ArgT_>(t_));
		}

		/// <summary>
		/// <para> Outputs a version of this Matrix with its elements clamped to a minimum value indicated by min_. </para>
		/// <para> If Min_ is an EmuMath Matrix: Elements will be clamped to a minimum of the respective element of min_. Otherwise, all will be clamped to min_ directly. </para>
		/// </summary>
		/// <param name="min_">: Scalar or EmuMath Matrix to use as the minimum to clamp this Matrix's values to.</param>
		/// <returns>Copy of this Matrix with its elements clamped to the provided minimum.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Min_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> ClampMin(Min_&& min_) const
		{
			return EmuMath::Helpers::matrix_clamp_min<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this, std::forward<Min_>(min_));
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class Min_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> ClampMin(Min_&& min_) const
		{
			return EmuMath::Helpers::matrix_clamp_min<num_columns, num_rows, OutT_, OutColumnMajor_>(*this, std::forward<Min_>(min_));
		}

		template<bool OutColumnMajor_ = is_column_major, class Min_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> ClampMin(Min_&& min_) const
		{
			return EmuMath::Helpers::matrix_clamp_min<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this, std::forward<Min_>(min_));
		}

		template<class Min_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		constexpr inline void ClampMin(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Min_&& min_) const
		{
			EmuMath::Helpers::matrix_clamp_min(out_matrix_, *this, std::forward<Min_>(min_));
		}

		/// <summary>
		/// <para> Outputs a version of this Matrix with its elements clamped to a minimum value indicated by min_. </para>
		/// <para> If Min_ is an EmuMath Matrix: Elements will be clamped to a minimum of the respective element of min_. Otherwise, all will be clamped to min_ directly. </para>
		/// <para> Indices within the provided range will contain respective clamping results. </para>
		/// <para> Indices outside of the provided range will be copies of respective indices in this Matrix. </para>
		/// </summary>
		/// <param name="min_">: Scalar or EmuMath Matrix to use as the minimum to clamp this Matrix's values to.</param>
		/// <returns>Copy of this Matrix with elements in the provided range clamped to the provided minimum, and copied elements elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Min_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> ClampMinRange(Min_&& min_) const
		{
			return EmuMath::Helpers::matrix_clamp_min_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Min_>(min_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			typename OutT_, bool OutColumnMajor_ = is_column_major, class Min_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> ClampMinRange(Min_&& min_) const
		{
			return EmuMath::Helpers::matrix_clamp_min_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Min_>(min_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class Min_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> ClampMinRange(Min_&& min_) const
		{
			return EmuMath::Helpers::matrix_clamp_min_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
			(
				*this,
				std::forward<Min_>(min_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class Min_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		constexpr inline void ClampMinRange(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Min_&& min_) const
		{
			EmuMath::Helpers::matrix_clamp_min_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<Min_>(min_));
		}

		/// <summary>
		/// <para> Outputs a version of this Matrix with its elements clamped to a minimum value indicated by min_. </para>
		/// <para> If Min_ is an EmuMath Matrix: Elements will be clamped to a minimum of the respective element of min_. Otherwise, all will be clamped to min_ directly. </para>
		/// <para> Indices within the provided range will contain respective clamping results. </para>
		/// <para> Indices outside of the provided range will be defaulted. </para>
		/// </summary>
		/// <param name="min_">: Scalar or EmuMath Matrix to use as the minimum to clamp this Matrix's values to.</param>
		/// <returns>Copy of this Matrix with elements in the provided range clamped to the provided minimum, and default elements elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Min_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> ClampMinRangeNoCopy(Min_&& min_) const
		{
			return EmuMath::Helpers::matrix_clamp_min_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Min_>(min_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major, class Min_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> ClampMinRangeNoCopy(Min_&& min_) const
		{
			return EmuMath::Helpers::matrix_clamp_min_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Min_>(min_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class Min_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> ClampMinRangeNoCopy(Min_&& min_) const
		{
			return EmuMath::Helpers::matrix_clamp_min_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
			(
				*this,
				std::forward<Min_>(min_)
			);
		}

		/// <summary>
		/// <para> Outputs a version of this Matrix with its elements clamped to a minimum value indicated by min_, via the provided `out_matrix_`. </para>
		/// <para> If Min_ is an EmuMath Matrix: Elements will be clamped to a minimum of the respective element of min_. Otherwise, all will be clamped to min_ directly. </para>
		/// <para> Indices within the provided range will contain respective clamping results. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// </summary>
		/// <param name="min_">: Scalar or EmuMath Matrix to use as the maximum to clamp this Matrix's values to.</param>
		/// <returns>Copy of this Matrix with elements in the provided range clamped to the provided minimum, and default elements elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class Min_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
		>
		constexpr inline void ClampMinRangeNoCopy(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Min_&& min_) const
		{
			EmuMath::Helpers::matrix_clamp_min_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<Min_>(min_));
		}

		/// <summary>
		/// <para> Outputs a version of this Matrix with its elements clamped to a maximum value indicated by max_. </para>
		/// <para> If Max_ is an EmuMath Matrix: Elements will be clamped to a maximum of the respective element of max_. Otherwise, all will be clamped to max_ directly. </para>
		/// </summary>
		/// <param name="max_">: Scalar or EmuMath Matrix to use as the maximum to clamp this Matrix's values to.</param>
		/// <returns>Copy of this Matrix with its elements clamped to the provided maximum.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Max_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> ClampMax(Max_&& max_) const
		{
			return EmuMath::Helpers::matrix_clamp_max<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this, std::forward<Max_>(max_));
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class Max_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> ClampMax(Max_&& max_) const
		{
			return EmuMath::Helpers::matrix_clamp_max<num_columns, num_rows, OutT_, OutColumnMajor_>(*this, std::forward<Max_>(max_));
		}

		template<bool OutColumnMajor_ = is_column_major, class Max_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> ClampMax(Max_&& max_) const
		{
			return EmuMath::Helpers::matrix_clamp_max<num_columns, num_rows, value_type_uq, OutColumnMajor_>(*this, std::forward<Max_>(max_));
		}

		template<class Max_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		constexpr inline void ClampMax(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Max_&& max_) const
		{
			EmuMath::Helpers::matrix_clamp_max(out_matrix_, *this, std::forward<Max_>(max_));
		}

		/// <summary>
		/// <para> Outputs a version of this Matrix with its elements clamped to a maximum value indicated by max_. </para>
		/// <para> If Max_ is an EmuMath Matrix: Elements will be clamped to a maximum of the respective element of max_. Otherwise, all will be clamped to max_ directly. </para>
		/// <para> Indices within the provided range will contain respective clamping results. </para>
		/// <para> Indices outside of the provided range will be copies of respective indices in this Matrix. </para>
		/// </summary>
		/// <param name="max_">: Scalar or EmuMath Matrix to use as the maximum to clamp this Matrix's values to.</param>
		/// <returns>Copy of this Matrix with elements in the provided range clamped to the provided maximum, and copied elements elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Max_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> ClampMaxRange(Max_&& max_) const
		{
			return EmuMath::Helpers::matrix_clamp_max_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Max_>(max_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			typename OutT_, bool OutColumnMajor_ = is_column_major, class Max_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> ClampMaxRange(Max_&& max_) const
		{
			return EmuMath::Helpers::matrix_clamp_max_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Max_>(max_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class Max_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> ClampMaxRange(Max_&& max_) const
		{
			return EmuMath::Helpers::matrix_clamp_max_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
			(
				*this,
				std::forward<Max_>(max_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class Max_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major
		>
		constexpr inline void ClampMaxRange(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Max_&& max_) const
		{
			EmuMath::Helpers::matrix_clamp_max_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<Max_>(max_));
		}

		/// <summary>
		/// <para> Outputs a version of this Matrix with its elements clamped to a maximum value indicated by max_. </para>
		/// <para> If Max_ is an EmuMath Matrix: Elements will be clamped to a maximum of the respective element of max_. Otherwise, all will be clamped to max_ directly. </para>
		/// <para> Indices within the provided range will contain respective clamping results. </para>
		/// <para> Indices outside of the provided range will be defaulted. </para>
		/// </summary>
		/// <param name="max_">: Scalar or EmuMath Matrix to use as the maximum to clamp this Matrix's values to.</param>
		/// <returns>Copy of this Matrix with elements in the provided range clamped to the provided maximum, and default elements elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major, class Max_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> ClampMaxRangeNoCopy(Max_&& b_) const
		{
			return EmuMath::Helpers::matrix_clamp_max_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Max_>(b_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_ = is_column_major, class Max_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> ClampMaxRangeNoCopy(Max_&& b_) const
		{
			return EmuMath::Helpers::matrix_clamp_max_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Max_>(b_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class Max_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> ClampMaxRangeNoCopy(Max_&& b_) const
		{
			return EmuMath::Helpers::matrix_clamp_max_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, value_type_uq, OutColumnMajor_>
			(
				*this,
				std::forward<Max_>(b_)
			);
		}

		/// <summary>
		/// <para> Outputs a version of this Matrix with its elements clamped to a maximum value indicated by max_, via the provided `out_matrix_`. </para>
		/// <para> If Max_ is an EmuMath Matrix: Elements will be clamped to a maximum of the respective element of max_. Otherwise, all will be clamped to max_ directly. </para>
		/// <para> Indices within the provided range will contain respective clamping results. </para>
		/// <para> Indices outside of the provided range will not be modified. </para>
		/// </summary>
		/// <param name="max_">: Scalar or EmuMath Matrix to use as the maximum to clamp this Matrix's values to.</param>
		/// <returns>Copy of this Matrix with elements in the provided range clamped to the provided maximum, and default elements elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class Max_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
		>
		constexpr inline void ClampMaxRangeNoCopy(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Max_&& b_) const
		{
			EmuMath::Helpers::matrix_clamp_min_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<Max_>(b_));
		}

		/// <summary>
		/// <para> Outputs a version of this Matrix with its elements clamped to a minimum value indicated by min_ and a maximum value indicated by max_. </para>
		/// <para> If Min_ is an EmuMath Matrix: Elements will be clamped to a minimum of the respective element of min_. Otherwise, all will be clamped to min_ directly. </para>
		/// <para> If Max_ is an EmuMath Matrix: Elements will be clamped to a maximum of the respective element of max_. Otherwise, all will be clamped to max_ directly. </para>
		/// </summary>
		/// <param name="min_">: Scalar or EmuMath Matrix to use as the mimimum to clamp this Matrix's values to.</param>
		/// <param name="max_">: Scalar or EmuMath Matrix to use as the maximum to clamp this Matrix's values to.</param>
		/// <returns>Copy of this Matrix with all of its elements to the provided minimum and maximum.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = preferred_floating_point, bool OutColumnMajor_ = is_column_major, class Min_, class Max_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> Clamp(Min_&& min_, Max_&& max_) const
		{
			return EmuMath::Helpers::matrix_clamp<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this, std::forward<Min_>(min_), std::forward<Max_>(max_));
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major, class Min_, class Max_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> Clamp(Min_&& min_, Max_&& max_) const
		{
			return EmuMath::Helpers::matrix_clamp<num_columns, num_rows, OutT_, OutColumnMajor_>(*this, std::forward<Min_>(min_), std::forward<Max_>(max_));
		}

		template<bool OutColumnMajor_ = is_column_major, class Min_, class Max_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, preferred_floating_point, OutColumnMajor_> Clamp(Min_&& min_, Max_&& max_) const
		{
			return EmuMath::Helpers::matrix_clamp<num_columns, num_rows, preferred_floating_point, OutColumnMajor_>(*this, std::forward<Min_>(min_), std::forward<Max_>(max_));
		}

		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, class Min_, class Max_>
		constexpr inline void Clamp(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Min_&& min_, Max_&& max_) const
		{
			EmuMath::Helpers::matrix_clamp(out_matrix_, *this, std::forward<Min_>(min_), std::forward<Max_>(max_));
		}
				
		/// <summary>
		/// <para> Outputs a version of this Matrix with its elements clamped to a minimum value indicated by min_ and a maximum value indicated by max_. </para>
		/// <para> If Min_ is an EmuMath Matrix: Elements will be clamped to a minimum of the respective element of min_. Otherwise, all will be clamped to min_ directly. </para>
		/// <para> If Max_ is an EmuMath Matrix: Elements will be clamped to a maximum of the respective element of max_. Otherwise, all will be clamped to max_ directly. </para>
		/// <para> Indices within the provided range will contain respective clamping results. </para>
		/// <para> Indices outside of the provided range will be copies of respective indices in this Matrix. </para>
		/// </summary>
		/// <param name="min_">: Scalar or EmuMath Matrix to use as the mimimum to clamp this Matrix's values to.</param>
		/// <param name="max_">: Scalar or EmuMath Matrix to use as the maximum to clamp this Matrix's values to.</param>
		/// <returns>Copy of this Matrix with elements in the provided range clamped to the provided minimum and maximum, and copied elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = preferred_floating_point, bool OutColumnMajor_ = is_column_major, class Min_, class Max_
		>
			[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> ClampRange(Min_&& min_, Max_&& max_) const
		{
			return EmuMath::Helpers::matrix_clamp_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
				(
					*this,
					std::forward<Min_>(min_),
					std::forward<Max_>(max_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			typename OutT_, bool OutColumnMajor_ = is_column_major, class Min_, class Max_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> ClampRange(Min_&& min_, Max_&& max_) const
		{
			return EmuMath::Helpers::matrix_clamp_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Min_>(min_),
				std::forward<Max_>(max_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class Min_, class Max_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, preferred_floating_point, OutColumnMajor_> ClampRange(Min_&& min_, Max_&& max_) const
		{
			return EmuMath::Helpers::matrix_clamp_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, preferred_floating_point, OutColumnMajor_>
			(
				*this,
				std::forward<Min_>(min_),
				std::forward<Max_>(max_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, class Min_, class Max_
		>
		constexpr inline void ClampRange(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Min_&& min_, Max_&& max_) const
		{
			EmuMath::Helpers::matrix_clamp_range<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<Min_>(min_), std::forward<Max_>(max_));
		}

		/// <summary>
		/// <para> Outputs a version of this Matrix with its elements clamped to a minimum value indicated by min_ and a maximum value indicated by max_. </para>
		/// <para> If Min_ is an EmuMath Matrix: Elements will be clamped to a minimum of the respective element of min_. Otherwise, all will be clamped to min_ directly. </para>
		/// <para> If Max_ is an EmuMath Matrix: Elements will be clamped to a maximum of the respective element of max_. Otherwise, all will be clamped to max_ directly. </para>
		/// <para> Indices within the provided range will contain respective clamping results. </para>
		/// <para> Indices outside of the provided range will be defaulted. </para>
		/// </summary>
		/// <param name="min_">: Scalar or EmuMath Matrix to use as the mimimum to clamp this Matrix's values to.</param>
		/// <param name="max_">: Scalar or EmuMath Matrix to use as the maximum to clamp this Matrix's values to.</param>
		/// <returns>Copy of this Matrix with elements in the provided range clamped to the provided minimum and maximum, and defaulted elsewhere.</returns>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = preferred_floating_point, bool OutColumnMajor_ = is_column_major, class Min_, class Max_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> ClampRangeNoCopy(Min_&& min_, Max_&& max_) const
		{
			return EmuMath::Helpers::matrix_clamp_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Min_>(min_),
				std::forward<Max_>(max_)
			);
		}

		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			typename OutT_, bool OutColumnMajor_ = is_column_major, class Min_, class Max_
		>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> ClampRangeNoCopy(Min_&& min_, Max_&& max_) const
		{
			return EmuMath::Helpers::matrix_clamp_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, OutT_, OutColumnMajor_>
			(
				*this,
				std::forward<Min_>(min_),
				std::forward<Max_>(max_)
			);
		}

		template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_ = is_column_major, class Min_, class Max_>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, preferred_floating_point, OutColumnMajor_> ClampRangeNoCopy(Min_&& min_, Max_&& max_) const
		{
			return EmuMath::Helpers::matrix_clamp_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_, num_columns, num_rows, preferred_floating_point, OutColumnMajor_>
			(
				*this,
				std::forward<Min_>(min_),
				std::forward<Max_>(max_)
			);
		}

		/// <summary>
		/// <para> Outputs a version of this Matrix with its elements clamped to a minimum value indicated by min_ and a maximum value indicated by max_, via `out_matrix_`. </para>
		/// <para> If Min_ is an EmuMath Matrix: Elements will be clamped to a minimum of the respective element of min_. Otherwise, all will be clamped to min_ directly. </para>
		/// <para> If Max_ is an EmuMath Matrix: Elements will be clamped to a maximum of the respective element of max_. Otherwise, all will be clamped to max_ directly. </para>
		/// <para> Indices within the provided range will contain respective clamping results. </para>
		/// <para> Indices outside of the provided range will be not be modified. </para>
		/// </summary>
		/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
		/// <param name="min_">: Scalar or EmuMath Matrix to use as the mimimum to clamp this Matrix's values to.</param>
		/// <param name="max_">: Scalar or EmuMath Matrix to use as the maximum to clamp this Matrix's values to.</param>
		template
		<
			std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
			std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, class Min_, class Max_
		>
		constexpr inline void ClampRangeNoCopy(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Min_&& min_, Max_&& max_) const
		{
			EmuMath::Helpers::matrix_clamp_range_no_copy<BeginColumn_, EndColumn_, BeginRow_, EndRow_>(out_matrix_, *this, std::forward<Min_>(min_), std::forward<Max_>(max_));
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

#pragma region SCALE_TRANSFORMATIONS
	public:
		/// <summary>
		/// <para> Static check if `AssignScale` can be called on this Matrix type with the provided argument types, including qualifications. </para>
		/// </summary>
		/// <returns>True if a call to `AssignScale` is valid on this Matrix type given the provided argument types, otherwise false.</returns>
		template<class...ScaleArgs_>
		[[nodiscard]] static constexpr inline bool valid_assign_scale_args()
		{
			return _valid_linear_transform_args<smallest_direction_size - 1, ScaleArgs_...>
			(
				[]() { return EmuMath::Helpers::matrix_assign_scale_is_valid<num_columns, num_rows, value_type_uq, is_column_major, ScaleArgs_...>(); }
			);
		}

		/// <summary>
		/// <para> Static check if `make_scale` can be called on this Matrix type with the provided argument types, including qualifications. </para>
		/// </summary>
		/// <returns>True if a call to `make_scale` is valid on this Matrix type given the provided argument types, otherwise false.</returns>
		template<class...ScaleArgs_>
		[[nodiscard]] static constexpr inline bool valid_make_scale_args()
		{
			return _valid_linear_transform_args<smallest_direction_size - 1, ScaleArgs_...>
			(
				[]() { return EmuMath::Helpers::matrix_make_scale_is_valid<num_columns, num_rows, value_type_uq, is_column_major, ScaleArgs_...>(); }
			);
		}

		/// <summary>
		/// <para> Creates a new Matrix of this Matrix's size, major-storage order, and value_type_uq, representing a scaling transformation based on the passed arguments. </para>
		/// <para>
		///		The maximum number of scale arguments is the number of items in the smallest direction of this Matrix type, minus 1. 
		///		For example, in a 4x4 matrix, a maximum of 3 arguments may be provided, but in a 4x3 or 3x4 matrix a maximum of 2 may be provided.
		/// </para>
		/// <para> Omitted dimension arguments will be considered as "no scaling", and will be treated as 1. </para>
		/// <para> If only one argument is provided, one of 3 possible outcomes will result: </para>
		/// <para> A: If the argument is an EmuMath Vector: Scales for each axis will use the respective index of the Vector. </para>
		/// <para> B: If the argument is a std::tuple: Scales for each axis will use the respective element of the tuple. </para>
		/// <para> C: If the argument is anything else: Scales for every axis will use the same scale, regardless of Matrix size. </para>
		/// </summary>
		/// <param name="scale_args_">Sequential scaling values for each axis, starting from X, or a std::tuple/EmuMath Vector of sequential scaling values for each axis.</param>
		/// <returns>
		///		EmuMath Matrix representing an X-dimensional scaling transformation, or as much as is possible in the output Matrix type,
		///		where X is the smallest size of this Matrix type minus 1.
		/// </returns>
		template<class...ScaleArgs_>
		[[nodiscard]] static constexpr inline auto make_scale(ScaleArgs_&&...scale_args_)
			-> std::enable_if_t<valid_make_scale_args<ScaleArgs_...>(), EmuMath::Matrix<num_columns, num_rows, value_type_uq, is_column_major>>
		{
			return EmuMath::Helpers::matrix_make_scale<num_columns, num_rows, value_type_uq, is_column_major>(std::forward<ScaleArgs_>(scale_args_)...);
		}

		/// <summary>
		/// <para> Assigns a scaling transformation Matrix to this Matrix. </para>
		/// <para> 
		///		The scale will be for as many dimensions as this Matrix can cover, which will be the size of its smallest direction minus 1.
		///		For example, in a 4x4 matrix, a 3D scale will be assigned, but in a 4x3 or 3x4 a 2D scale will be assigned.
		/// </para>
		/// <para> This may be given a maximum number of arguments equal to the number of dimensions that the scale is for. </para>
		/// <para> Omitted dimension arguments will be considered as "no scaling", and will be treated as 1. </para>
		/// <para> If given a single argument, which is also a std::tuple, respective items in the tuple will be used for each dimension. </para>
		/// <para> If given a single argument, which is also an EmuMath Vector, respective elements in the Vector will be used for each dimension. </para>
		/// </summary>
		/// <param name="scale_args_">Sequential arguments for each axis's scaling, starting from X; or a std::tuple/EmuMath Vector containing sequential arguments.</param>
		template<class...ScaleArgs_>
		constexpr inline auto AssignScale(ScaleArgs_&&...scale_args_) &
			-> std::enable_if_t<valid_assign_scale_args<ScaleArgs_...>(), void>
		{
			EmuMath::Helpers::matrix_assign_scale(*this, std::forward<ScaleArgs_>(scale_args_)...);
		}
#pragma endregion

#pragma region TRANSLATE_TRANSFORMATIONS
	public:
		/// <summary>
		/// <para> Static check if `AssignTranslation` can be called on this Matrix type with the provided argument types, including qualifications. </para>
		/// </summary>
		/// <returns>True if a call to `AssignTranslation` is valid on this Matrix type given the provided argument types, otherwise false.</returns>
		template<class...ScaleArgs_>
		[[nodiscard]] static constexpr inline bool valid_assign_translation_args()
		{
			return _valid_linear_transform_args<num_rows - 1, ScaleArgs_...>
			(
				[]() { return EmuMath::Helpers::matrix_assign_translation_is_valid<num_columns, num_rows, value_type_uq, is_column_major, ScaleArgs_...>(); }
			);
		}

		/// <summary>
		/// <para> Static check if `make_translation` can be called on this Matrix type with the provided argument types, including qualifications. </para>
		/// </summary>
		/// <returns>True if a call to `make_translation` is valid on this Matrix type given the provided argument types, otherwise false.</returns>
		template<class...ScaleArgs_>
		[[nodiscard]] static constexpr inline bool valid_make_translation_args()
		{
			return _valid_linear_transform_args<num_rows - 1, ScaleArgs_...>
			(
				[]() { return EmuMath::Helpers::matrix_make_translation_is_valid<num_columns, num_rows, value_type_uq, is_column_major, ScaleArgs_...>(); }
			);
		}

		/// <summary>
		/// <para> Creates a new Matrix of this Matrix's size, major-storage order, and value_type_uq, representing a trasnlation transformation based on the passed arguments. </para>
		/// <para>
		///		The maximum number of translation arguments is the number of rows in this Matrix type, minus 1. 
		///		For example, in a 4x4 or 3x4 matrix, a maximum of 3 arguments may be provided, but in a 4x3 Matrix a maximum of 2 may be provided.
		/// </para>
		/// <para> Omitted dimension arguments will be considered as "no translation", and will be treated as 0. </para>
		/// <para> If only one argument is provided, one of 3 possible outcomes will result: </para>
		/// <para> A: If the argument is an EmuMath Vector: Translations for each axis will use the respective index of the Vector. </para>
		/// <para> B: If the argument is a std::tuple: Translations for each axis will use the respective element of the tuple. </para>
		/// <para> C: If the argument is anything else: Translations for every axis will use the same value, regardless of Matrix size. </para>
		/// </summary>
		/// <param name="translation_args_">
		///		Sequential translation values for each axis, starting from X, 
		///		or a std::tuple/EmuMath Vector of sequential translation values for each axis.
		/// </param>
		/// <returns>
		///		EmuMath Matrix representing an X-dimensional translation transformation, or as much as is possible in the output Matrix type,
		///		where X is the number of rows in this Matrix type minus 1.
		/// </returns>
		template<class...TranslationArgs_>
		[[nodiscard]] static constexpr inline auto make_translation(TranslationArgs_&&...translation_args_)
			-> std::enable_if_t<valid_make_scale_args<TranslationArgs_...>(), EmuMath::Matrix<num_columns, num_rows, value_type_uq, is_column_major>>
		{
			return EmuMath::Helpers::matrix_make_translation<num_columns, num_rows, value_type_uq, is_column_major>(std::forward<TranslationArgs_>(translation_args_)...);
		}

		/// <summary>
		/// <para> Assigns a translation transformation Matrix to this Matrix. </para>
		/// <para> 
		///		The translation will be for as many dimensions as the Matrix can cover, which will be the number of rows it contains minus 1
		///		For example, in a 4x4 or 3x4 matrix, a 3D translation will be assigned, but in a 4x3 Matrix a 2D translation will be assigned.
		/// </para>
		/// <para> This may be given a maximum number of arguments equal to the number of dimensions that the translation is for. </para>
		/// <para> Omitted dimension arguments will be considered as "no translation", and will be treated as 0. </para>
		/// <para> If given a single argument, which is also a std::tuple, respective items in the tuple will be used for each dimension. </para>
		/// <para> If given a single argument, which is also an EmuMath Vector, respective elements in the Vector will be used for each dimension. </para>
		/// </summary>
		/// <param name="translation_args_">Sequential arguments for each axis's translation, starting from X; or a std::tuple/EmuMath Vector containing sequential arguments.</param>
		template<class...TranslationArgs_>
		constexpr inline auto AssignTranslation(TranslationArgs_&&...translation_args_) &
			-> std::enable_if_t<valid_assign_scale_args<TranslationArgs_...>(), void>
		{
			EmuMath::Helpers::matrix_assign_translation(*this, std::forward<TranslationArgs_>(translation_args_)...);
		}
#pragma endregion

#pragma region ROTATION_3D_TRANSFORMATION_VALIDITY
	private:
		template<class Angle_, bool AngleIsRads_, std::size_t AxisIndex_, bool Assigning_>
		[[nodiscard]] static constexpr inline bool valid_rotation_3d_arg()
		{
			using out_mat = typename std::conditional
			<
				Assigning_,
				EmuMath::Matrix<num_columns, num_rows, value_type_uq, is_column_major>&,
				EmuMath::Matrix<num_columns, num_rows, value_type_uq, is_column_major>
			>::type;
			return EmuMath::Helpers::_matrix_underlying::_matrix_rotate_3_is_valid<out_mat, Angle_, Assigning_, AngleIsRads_, AxisIndex_, 0, false, false>();
		}

		template<class Angle_, bool AngleIsRads_, std::size_t AxisIndex_, bool Assigning_, std::size_t NumTrigIterations_, bool TrigMod_>
		[[nodiscard]] static constexpr inline bool valid_rotation_3d_constexpr_arg()
		{
			if constexpr (NumTrigIterations_ == 0)
			{
				return false;
			}
			else
			{
				using out_mat = typename std::conditional
				<
					Assigning_,
					EmuMath::Matrix<num_columns, num_rows, value_type_uq, is_column_major>&,
					EmuMath::Matrix<num_columns, num_rows, value_type_uq, is_column_major>
				>::type;
				return EmuMath::Helpers::_matrix_underlying::_matrix_rotate_3_is_valid<out_mat, Angle_, Assigning_, AngleIsRads_, AxisIndex_, NumTrigIterations_, TrigMod_, false>();
			}
		}

	public:
		template<class Angle_, bool AngleIsRads_>
		[[nodiscard]] static constexpr inline bool valid_make_rotation_3d_x_arg()
		{
			return valid_rotation_3d_arg<Angle_, AngleIsRads_, 0, false>();
		}

		template<class Angle_, bool AngleIsRads_>
		[[nodiscard]] static constexpr inline bool valid_make_rotation_3d_y_arg()
		{
			return valid_rotation_3d_arg<Angle_, AngleIsRads_, 1, false>();
		}

		template<class Angle_, bool AngleIsRads_>
		[[nodiscard]] static constexpr inline bool valid_make_rotation_3d_z_arg()
		{
			return valid_rotation_3d_arg<Angle_, AngleIsRads_, 2, false>();
		}

		template<class Angle_, bool AngleIsRads_, std::size_t NumTrigIterations_, bool TrigMod_>
		[[nodiscard]] static constexpr inline bool valid_make_rotation_3d_x_constexpr_arg()
		{
			return valid_rotation_3d_constexpr_arg<Angle_, AngleIsRads_, 0, false, NumTrigIterations_, TrigMod_>();
		}

		template<class Angle_, bool AngleIsRads_, std::size_t NumTrigIterations_, bool TrigMod_>
		[[nodiscard]] static constexpr inline bool valid_make_rotation_3d_y_constexpr_arg()
		{
			return valid_rotation_3d_constexpr_arg<Angle_, AngleIsRads_, 1, false, NumTrigIterations_, TrigMod_>();
		}

		template<class Angle_, bool AngleIsRads_, std::size_t NumTrigIterations_, bool TrigMod_>
		[[nodiscard]] static constexpr inline bool valid_make_rotation_3d_z_constexpr_arg()
		{
			return valid_rotation_3d_constexpr_arg<Angle_, AngleIsRads_, 2, false, NumTrigIterations_, TrigMod_>();
		}
		
		template<class Angle_, bool AngleIsRads_>
		[[nodiscard]] static constexpr inline bool valid_assign_rotation_3d_x_arg()
		{
			return valid_rotation_3d_arg<Angle_, AngleIsRads_, 0, true>();
		}

		template<class Angle_, bool AngleIsRads_>
		[[nodiscard]] static constexpr inline bool valid_assign_rotation_3d_y_arg()
		{
			return valid_rotation_3d_arg<Angle_, AngleIsRads_, 1, true>();
		}

		template<class Angle_, bool AngleIsRads_>
		[[nodiscard]] static constexpr inline bool valid_assign_rotation_3d_z_arg()
		{
			return valid_rotation_3d_arg<Angle_, AngleIsRads_, 2, true>();
		}

		template<class Angle_, bool AngleIsRads_, std::size_t NumTrigIterations_, bool TrigMod_>
		[[nodiscard]] static constexpr inline bool valid_assign_rotation_3d_x_constexpr_arg()
		{
			return valid_rotation_3d_constexpr_arg<Angle_, AngleIsRads_, 0, true, NumTrigIterations_, TrigMod_>();
		}

		template<class Angle_, bool AngleIsRads_, std::size_t NumTrigIterations_, bool TrigMod_>
		[[nodiscard]] static constexpr inline bool valid_assign_rotation_3d_y_constexpr_arg()
		{
			return valid_rotation_3d_constexpr_arg<Angle_, AngleIsRads_, 1, true, NumTrigIterations_, TrigMod_>();
		}

		template<class Angle_, bool AngleIsRads_, std::size_t NumTrigIterations_, bool TrigMod_>
		[[nodiscard]] static constexpr inline bool valid_assign_rotation_3d_z_constexpr_arg()
		{
			return valid_rotation_3d_constexpr_arg<Angle_, AngleIsRads_, 2, true, NumTrigIterations_, TrigMod_>();
		}		
#pragma endregion

#pragma region ROTATION_3D_TRANSFORMATION
	public:
		/// <summary>
		/// <para> 
		///		Creates a 3D rotation transformation of `angle_` radians or degrees about the X-axis, 
		///		output as a Matrix of this Matrix's size, memory major order, and value_type_uq.
		/// </para>
		/// <para> If `AngleIsRads_` is true, `angle_` will be interpreted as radians. If it is false, `angle_` will be interpreted as degrees. </para>
		/// <para> If the output Matrix cannot fit the full rotation Matrix, as much as can be filled in will be provided. </para>
		/// <para> `AngleIsRads_` may be omitted in some cases. If it is omitted, `angle_` will be interpreted as radians. </para>
		/// </summary>
		/// <param name="angle_">Angle of rotation in either radians or degrees.</param>
		/// <returns>EmuMath Matrix representing a 3D rotation transformation about the X-axis based on the provided `angle_` argument.</returns>
		template<bool AngleIsRads_ = true, class Angle_>
		[[nodiscard]] static constexpr inline auto make_rotation_3d_x(Angle_&& angle_)
			-> std::enable_if_t<valid_make_rotation_3d_x_arg<Angle_, AngleIsRads_>(), EmuMath::Matrix<num_columns, num_rows, value_type_uq, is_column_major>>
		{
			return EmuMath::Helpers::matrix_make_rotation_3d_x<AngleIsRads_, num_columns, num_rows, value_type_uq, is_column_major>(std::forward<Angle_>(angle_));
		}

		/// <summary>
		/// <para> 
		///		Creates a 3D rotation transformation of `angle_` radians or degrees about the X-axis, 
		///		output as a Matrix of this Matrix's size, memory major order, and value_type_uq.
		/// </para>
		/// <para> Calculation will aim to be constexpr-evaluable if possible. </para>
		/// <para> `NumTrigIterations_` is the number of iterations to perform for executing trigonometric functions such as cos and sin. It must be greater than 0. </para>
		/// <para> 
		///		`TrigMod_` is a boolean indicating if a safety modulo calculation should be performed. 
		///		If it is known that `angle_` is not greater than 6.28319 radians (or the degree equivalent after conversion), this modulo has no effect and can be safely skipped.
		/// </para>
		/// <para> If `AngleIsRads_` is true, `angle_` will be interpreted as radians. If it is false, `angle_` will be interpreted as degrees. </para>
		/// <para> If the output Matrix cannot fit the full rotation Matrix, as much as can be filled in will be provided. </para>
		/// <para> `AngleIsRads_` may be omitted in some cases. If it is omitted, `angle_` will be interpreted as radians. </para>
		/// </summary>
		/// <param name="angle_">Angle of rotation in either radians or degrees.</param>
		/// <returns>EmuMath Matrix representing a 3D rotation transformation about the Z-axis based on the provided `angle_` argument.</returns>
		template<std::size_t NumTrigIterations_, bool TrigMod_, bool AngleIsRads_ = true, class Angle_>
		[[nodiscard]] static constexpr inline auto make_rotation_3d_x_constexpr(Angle_&& angle_)
			-> std::enable_if_t
			<
				valid_make_rotation_3d_x_constexpr_arg<Angle_, AngleIsRads_, NumTrigIterations_, TrigMod_>(),
				EmuMath::Matrix<num_columns, num_rows, value_type_uq, is_column_major>
			>
		{
			return EmuMath::Helpers::matrix_make_rotation_3d_x_constexpr
			<
				NumTrigIterations_,
				TrigMod_,
				AngleIsRads_,
				num_columns,
				num_rows,
				value_type_uq,
				is_column_major
			>(std::forward<Angle_>(angle_));
		}

		/// <summary>
		/// <para> 
		///		Creates a 3D rotation transformation of `angle_` radians or degrees about the Y-axis, 
		///		output as a Matrix of this Matrix's size, memory major order, and value_type_uq.
		/// </para>
		/// <para> If `AngleIsRads_` is true, `angle_` will be interpreted as radians. If it is false, `angle_` will be interpreted as degrees. </para>
		/// <para> If the output Matrix cannot fit the full rotation Matrix, as much as can be filled in will be provided. </para>
		/// <para> `AngleIsRads_` may be omitted in some cases. If it is omitted, `angle_` will be interpreted as radians. </para>
		/// </summary>
		/// <param name="angle_">Angle of rotation in either radians or degrees.</param>
		/// <returns>EmuMath Matrix representing a 3D rotation transformation about the Y-axis based on the provided `angle_` argument.</returns>
		template<bool AngleIsRads_ = true, class Angle_>
		[[nodiscard]] static constexpr inline auto make_rotation_3d_y(Angle_&& angle_)
			-> std::enable_if_t<valid_make_rotation_3d_y_arg<Angle_, AngleIsRads_>(), EmuMath::Matrix<num_columns, num_rows, value_type_uq, is_column_major>>
		{
			return EmuMath::Helpers::matrix_make_rotation_3d_y<AngleIsRads_, num_columns, num_rows, value_type_uq, is_column_major>(std::forward<Angle_>(angle_));
		}

		/// <summary>
		/// <para> 
		///		Creates a 3D rotation transformation of `angle_` radians or degrees about the Y-axis, 
		///		output as a Matrix of this Matrix's size, memory major order, and value_type_uq.
		/// </para>
		/// <para> Calculation will aim to be constexpr-evaluable if possible. </para>
		/// <para> `NumTrigIterations_` is the number of iterations to perform for executing trigonometric functions such as cos and sin. It must be greater than 0. </para>
		/// <para> 
		///		`TrigMod_` is a boolean indicating if a safety modulo calculation should be performed. 
		///		If it is known that `angle_` is not greater than 6.28319 radians (or the degree equivalent after conversion), this modulo has no effect and can be safely skipped.
		/// </para>
		/// <para> If `AngleIsRads_` is true, `angle_` will be interpreted as radians. If it is false, `angle_` will be interpreted as degrees. </para>
		/// <para> If the output Matrix cannot fit the full rotation Matrix, as much as can be filled in will be provided. </para>
		/// <para> `AngleIsRads_` may be omitted in some cases. If it is omitted, `angle_` will be interpreted as radians. </para>
		/// </summary>
		/// <param name="angle_">Angle of rotation in either radians or degrees.</param>
		/// <returns>EmuMath Matrix representing a 3D rotation transformation about the Y-axis based on the provided `angle_` argument.</returns>
		template<std::size_t NumTrigIterations_, bool TrigMod_, bool AngleIsRads_ = true, class Angle_>
		[[nodiscard]] static constexpr inline auto make_rotation_3d_y_constexpr(Angle_&& angle_)
			-> std::enable_if_t
			<
				valid_make_rotation_3d_y_constexpr_arg<Angle_, AngleIsRads_, NumTrigIterations_, TrigMod_>(),
				EmuMath::Matrix<num_columns, num_rows, value_type_uq, is_column_major>
			>
		{
			return EmuMath::Helpers::matrix_make_rotation_3d_y_constexpr
			<
				NumTrigIterations_,
				TrigMod_,
				AngleIsRads_,
				num_columns,
				num_rows,
				value_type_uq,
				is_column_major
			>(std::forward<Angle_>(angle_));
		}

		/// <summary>
		/// <para> 
		///		Creates a 3D rotation transformation of `angle_` radians or degrees about the Y-axis, 
		///		output as a Matrix of this Matrix's size, memory major order, and value_type_uq.
		/// </para>
		/// <para> If `AngleIsRads_` is true, `angle_` will be interpreted as radians. If it is false, `angle_` will be interpreted as degrees. </para>
		/// <para> If the output Matrix cannot fit the full rotation Matrix, as much as can be filled in will be provided. </para>
		/// <para> `AngleIsRads_` may be omitted in some cases. If it is omitted, `angle_` will be interpreted as radians. </para>
		/// </summary>
		/// <param name="angle_">Angle of rotation in either radians or degrees.</param>
		/// <returns>EmuMath Matrix representing a 3D rotation transformation about the Y-axis based on the provided `angle_` argument.</returns>
		template<bool AngleIsRads_ = true, class Angle_>
		[[nodiscard]] static constexpr inline auto make_rotation_3d_z(Angle_&& angle_)
			-> std::enable_if_t<valid_make_rotation_3d_z_arg<Angle_, AngleIsRads_>(), EmuMath::Matrix<num_columns, num_rows, value_type_uq, is_column_major>>
		{
			return EmuMath::Helpers::matrix_make_rotation_3d_z<AngleIsRads_, num_columns, num_rows, value_type_uq, is_column_major>(std::forward<Angle_>(angle_));
		}

		/// <summary>
		/// <para> 
		///		Creates a 3D rotation transformation of `angle_` radians or degrees about the Y-axis, 
		///		output as a Matrix of this Matrix's size, memory major order, and value_type_uq.
		/// </para>
		/// <para> Calculation will aim to be constexpr-evaluable if possible. </para>
		/// <para> `NumTrigIterations_` is the number of iterations to perform for executing trigonometric functions such as cos and sin. It must be greater than 0. </para>
		/// <para> 
		///		`TrigMod_` is a boolean indicating if a safety modulo calculation should be performed. 
		///		If it is known that `angle_` is not greater than 6.28319 radians (or the degree equivalent after conversion), this modulo has no effect and can be safely skipped.
		/// </para>
		/// <para> If `AngleIsRads_` is true, `angle_` will be interpreted as radians. If it is false, `angle_` will be interpreted as degrees. </para>
		/// <para> If the output Matrix cannot fit the full rotation Matrix, as much as can be filled in will be provided. </para>
		/// <para> `AngleIsRads_` may be omitted in some cases. If it is omitted, `angle_` will be interpreted as radians. </para>
		/// </summary>
		/// <param name="angle_">Angle of rotation in either radians or degrees.</param>
		/// <returns>EmuMath Matrix representing a 3D rotation transformation about the Y-axis based on the provided `angle_` argument.</returns>
		template<std::size_t NumTrigIterations_, bool TrigMod_, bool AngleIsRads_ = true, class Angle_>
		[[nodiscard]] static constexpr inline auto make_rotation_3d_z_constexpr(Angle_&& angle_)
			-> std::enable_if_t
			<
				valid_make_rotation_3d_z_constexpr_arg<Angle_, AngleIsRads_, NumTrigIterations_, TrigMod_>(),
				EmuMath::Matrix<num_columns, num_rows, value_type_uq, is_column_major>
			>
		{
			return EmuMath::Helpers::matrix_make_rotation_3d_z_constexpr
			<
				NumTrigIterations_,
				TrigMod_,
				AngleIsRads_,
				num_columns,
				num_rows,
				value_type_uq,
				is_column_major
			>(std::forward<Angle_>(angle_));
		}

		/// <summary>
		/// <para> Assigns this Matrix to represent a 3D rotation transformation of `angle_` radians or degrees about the X-axis. </para>
		/// <para> If `AngleIsRads_` is true, `angle_` will be interpreted as radians. If it is false, `angle_` will be interpreted as degrees. </para>
		/// <para> If this Matrix cannot fit the full rotation Matrix, as much as can be filled in will be provided. </para>
		/// <para> `AngleIsRads_` may be omitted in some cases. If it is omitted, `angle_` will be interpreted as radians. </para>
		/// </summary>
		/// <param name="angle_">Angle of rotation in either radians or degrees.</param>
		template<bool AngleIsRads_ = true, class Angle_>
		constexpr inline auto AssignRotation3DX(Angle_&& angle_) &
			-> std::enable_if_t<valid_assign_rotation_3d_x_arg<Angle_, AngleIsRads_>(), void>
		{
			EmuMath::Helpers::matrix_assign_rotation_3d_x<AngleIsRads_>(*this, std::forward<Angle_>(angle_));
		}

		/// <summary>
		/// <para> Assigns this Matrix to represent a 3D rotation transformation of `angle_` radians or degrees about the X-axis. </para>
		/// <para> Calculation will aim to be constexpr-evaluable if possible. </para>
		/// <para> `NumIterations_` is the number of iterations to perform for executing trigonometric functions such as cos and sin. It must be greater than 0. </para>
		/// <para> 
		///		`TrigMod_` is a boolean indicating if a safety modulo calculation should be performed. 
		///		If it is known that `angle_` is not greater than 6.28319 radians (or the degree equivalent after conversion), this modulo has no effect and can be safely skipped.
		/// </para>
		/// <para> If `AngleIsRads_` is true, `angle_` will be interpreted as radians. If it is false, `angle_` will be interpreted as degrees. </para>
		/// <para> If this Matrix cannot fit the full rotation Matrix, as much as can be filled in will be provided. </para>
		/// <para> `AngleIsRads_` may be omitted in some cases. If it is omitted, `angle_` will be interpreted as radians. </para>
		/// </summary>
		/// <param name="angle_">Angle of rotation in either radians or degrees.</param>
		template<std::size_t NumTrigIterations_, bool TrigMod_, bool AngleIsRads_ = true, class Angle_>
		constexpr inline auto AssignRotation3DXConstexpr(Angle_&& angle_) &
			-> std::enable_if_t<valid_assign_rotation_3d_x_constexpr_arg<Angle_, AngleIsRads_, NumTrigIterations_, TrigMod_>(), void>
		{
			EmuMath::Helpers::matrix_assign_rotation_3d_x_constexpr<NumTrigIterations_, TrigMod_, AngleIsRads_>(*this, std::forward<Angle_>(angle_));
		}		

		/// <summary>
		/// <para> Assigns this Matrix to represent a 3D rotation transformation of `angle_` radians or degrees about the Y-axis. </para>
		/// <para> If `AngleIsRads_` is true, `angle_` will be interpreted as radians. If it is false, `angle_` will be interpreted as degrees. </para>
		/// <para> If this Matrix cannot fit the full rotation Matrix, as much as can be filled in will be provided. </para>
		/// <para> `AngleIsRads_` may be omitted in some cases. If it is omitted, `angle_` will be interpreted as radians. </para>
		/// </summary>
		/// <param name="angle_">Angle of rotation in either radians or degrees.</param>
		template<bool AngleIsRads_ = true, class Angle_>
		constexpr inline auto AssignRotation3DY(Angle_&& angle_) &
			-> std::enable_if_t<valid_assign_rotation_3d_y_arg<Angle_, AngleIsRads_>(), void>
		{
			EmuMath::Helpers::matrix_assign_rotation_3d_y<AngleIsRads_>(*this, std::forward<Angle_>(angle_));
		}

		/// <summary>
		/// <para> Assigns this Matrix to represent a 3D rotation transformation of `angle_` radians or degrees about the Y-axis. </para>
		/// <para> Calculation will aim to be constexpr-evaluable if possible. </para>
		/// <para> `NumIterations_` is the number of iterations to perform for executing trigonometric functions such as cos and sin. It must be greater than 0. </para>
		/// <para> 
		///		`TrigMod_` is a boolean indicating if a safety modulo calculation should be performed. 
		///		If it is known that `angle_` is not greater than 6.28319 radians (or the degree equivalent after conversion), this modulo has no effect and can be safely skipped.
		/// </para>
		/// <para> If `AngleIsRads_` is true, `angle_` will be interpreted as radians. If it is false, `angle_` will be interpreted as degrees. </para>
		/// <para> If this Matrix cannot fit the full rotation Matrix, as much as can be filled in will be provided. </para>
		/// <para> `AngleIsRads_` may be omitted in some cases. If it is omitted, `angle_` will be interpreted as radians. </para>
		/// </summary>
		/// <param name="angle_">Angle of rotation in either radians or degrees.</param>
		template<std::size_t NumTrigIterations_, bool TrigMod_, bool AngleIsRads_ = true, class Angle_>
		constexpr inline auto AssignRotation3DYConstexpr(Angle_&& angle_) &
			-> std::enable_if_t<valid_assign_rotation_3d_y_constexpr_arg<Angle_, AngleIsRads_, NumTrigIterations_, TrigMod_>(), void>
		{
			EmuMath::Helpers::matrix_assign_rotation_3d_y_constexpr<NumTrigIterations_, TrigMod_, AngleIsRads_>(*this, std::forward<Angle_>(angle_));
		}		

		/// <summary>
		/// <para> Assigns this Matrix to represent a 3D rotation transformation of `angle_` radians or degrees about the Z-axis. </para>
		/// <para> If `AngleIsRads_` is true, `angle_` will be interpreted as radians. If it is false, `angle_` will be interpreted as degrees. </para>
		/// <para> If this Matrix cannot fit the full rotation Matrix, as much as can be filled in will be provided. </para>
		/// <para> `AngleIsRads_` may be omitted in some cases. If it is omitted, `angle_` will be interpreted as radians. </para>
		/// </summary>
		/// <param name="angle_">Angle of rotation in either radians or degrees.</param>
		template<bool AngleIsRads_ = true, class Angle_>
		constexpr inline auto AssignRotation3DZ(Angle_&& angle_) &
			-> std::enable_if_t<valid_assign_rotation_3d_z_arg<Angle_, AngleIsRads_>(), void>
		{
			EmuMath::Helpers::matrix_assign_rotation_3d_z<AngleIsRads_>(*this, std::forward<Angle_>(angle_));
		}

		/// <summary>
		/// <para> Assigns this Matrix to represent a 3D rotation transformation of `angle_` radians or degrees about the Z-axis. </para>
		/// <para> Calculation will aim to be constexpr-evaluable if possible. </para>
		/// <para> `NumIterations_` is the number of iterations to perform for executing trigonometric functions such as cos and sin. It must be greater than 0. </para>
		/// <para> 
		///		`TrigMod_` is a boolean indicating if a safety modulo calculation should be performed. 
		///		If it is known that `angle_` is not greater than 6.28319 radians (or the degree equivalent after conversion), this modulo has no effect and can be safely skipped.
		/// </para>
		/// <para> If `AngleIsRads_` is true, `angle_` will be interpreted as radians. If it is false, `angle_` will be interpreted as degrees. </para>
		/// <para> If this Matrix cannot fit the full rotation Matrix, as much as can be filled in will be provided. </para>
		/// <para> `AngleIsRads_` may be omitted in some cases. If it is omitted, `angle_` will be interpreted as radians. </para>
		/// </summary>
		/// <param name="angle_">Angle of rotation in either radians or degrees.</param>
		template<std::size_t NumTrigIterations_, bool TrigMod_, bool AngleIsRads_ = true, class Angle_>
		constexpr inline auto AssignRotation3DZConstexpr(Angle_&& angle_) &
			-> std::enable_if_t<valid_assign_rotation_3d_z_constexpr_arg<Angle_, AngleIsRads_, NumTrigIterations_, TrigMod_>(), void>
		{
			EmuMath::Helpers::matrix_assign_rotation_3d_z_constexpr<NumTrigIterations_, TrigMod_, AngleIsRads_>(*this, std::forward<Angle_>(angle_));
		}
#pragma endregion

#pragma region ROTATION_3D_TRANSFORMATION_FROM_QUATERNION_VALIDITY
	public:
		template<typename OutT_, typename FirstQuaternionT_, typename...OtherQuaternionTs_>
		[[nodiscard]] static constexpr inline bool valid_make_rotation_3d_from_quaternion_args()
		{
			return EmuMath::Helpers::matrix_can_make_from_quaternion<num_columns, num_rows, OutT_, is_column_major, FirstQuaternionT_, OtherQuaternionTs_...>();
		}

		template<typename OutT_, typename FirstQuaternionT_, typename...OtherQuaternionTs_>
		[[nodiscard]] static constexpr inline bool valid_make_rotation_3d_from_quaternion_args_fused()
		{
			return EmuMath::Helpers::matrix_can_fused_make_from_quaternion<num_columns, num_rows, OutT_, is_column_major, FirstQuaternionT_, OtherQuaternionTs_...>();
		}
#pragma endregion

#pragma region ROTATION_3D_TRANSFORMATION_FROM_QUATERNION_FUNCS
	public:
		/// <summary>
		/// <para> Converts the passed Quaternion into a 3D rotation transformation Matrix. </para>
		/// <para> The type stored in the output Matrix may be omitted, and defaults to this Matrix type's `preferred_floating_point`. </para>
		/// <para> If more than one Quaternion is passed, they will be combined in sequence from left-to-right and the result will be converted. </para>
		/// </summary>
		/// <param name="quaternion_">EmuMath Quaternion(s) to convert to a 3D rotation transformation Matrix.</param>
		/// <returns>
		///		3D transformation Matrix of the specified type (with size and major order matching those of this Matrix type),
		///		representing the same rotation as the passed Quaternion (or the Quaternion resulting from sequencing all passed Quaternions).
		/// </returns>
		template<typename OutT_ = preferred_floating_point, typename...SequentialQuaternionTs_>
		[[nodiscard]] static constexpr inline auto make_rotation_3d(const EmuMath::Quaternion<SequentialQuaternionTs_>&...sequential_quaternions_)
			-> std::enable_if_t
			<
				valid_make_rotation_3d_from_quaternion_args<OutT_, SequentialQuaternionTs_...>(),
				EmuMath::Matrix<num_columns, num_rows, OutT_, is_column_major>
			>
		{
			return EmuMath::Helpers::matrix_make_rotation_3d<num_columns, num_rows, OutT_, is_column_major>(sequential_quaternions_...);
		}

		/// <summary>
		/// <para> Converts the passed Quaternion into a 3D rotation transformation Matrix. </para>
		/// <para> The type stored in the output Matrix may be omitted, and defaults to this Matrix type's `preferred_floating_point`. </para>
		/// <para> If more than one Quaternion is passed, they will be combined in sequence from left-to-right and the result will be converted. </para>
		/// <para>
		///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
		///		Use of such instructions may improve accuracy and/or performance.
		/// </para>
		/// </summary>
		/// <param name="quaternion_">EmuMath Quaternion(s) to convert to a 3D rotation transformation Matrix.</param>
		/// <returns>
		///		3D transformation Matrix of the specified type (with size and major order matching those of this Matrix type),
		///		representing the same rotation as the passed Quaternion (or the Quaternion resulting from sequencing all passed Quaternions).
		/// </returns>
		template<typename OutT_ = preferred_floating_point, typename...SequentialQuaternionTs_>
		[[nodiscard]] static constexpr inline auto make_rotation_3d_fused(const EmuMath::Quaternion<SequentialQuaternionTs_>&...sequential_quaternions_)
			-> std::enable_if_t
			<
				valid_make_rotation_3d_from_quaternion_args_fused<OutT_, SequentialQuaternionTs_...>(),
				EmuMath::Matrix<num_columns, num_rows, OutT_, is_column_major>
			>
		{
			return EmuMath::Helpers::matrix_make_rotation_3d_fused<num_columns, num_rows, OutT_, is_column_major>(sequential_quaternions_...);
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

#pragma region STATIC_MATRIX_MAKERS
		/// <summary>
		/// <para> Outputs the Identity Matrix as the desired output Matrix, defaulting to the same as this Matrix (except for T_, which will be this Matrix's value_type_uq). </para>
		/// <para> The Identity Matrix is composed of all 1 along the main diagonal, and all 0 elsewhere. </para>
		/// <para> Although this may be used to create an Identity of any size, it mainly has useful meaning within a square Matrix (where num_columns == num_rows). </para>
		/// </summary>
		/// <returns>EmuMath Matrix of the specified type, constructed as its Identity Matrix (all 1 along the main diagonal, all 0 elsewhere).</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_ = value_type_uq, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] static constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> identity()
		{
			return EmuMath::Helpers::matrix_identity<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>();
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] static constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> identity()
		{
			return EmuMath::Helpers::matrix_identity<num_columns, num_rows, OutT_, OutColumnMajor_>();
		}

		template<bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] static constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type_uq, OutColumnMajor_> identity()
		{
			return EmuMath::Helpers::matrix_identity<num_columns, num_rows, value_type_uq, OutColumnMajor_>();
		}

		/// <summary>
		/// <para> Assigns the Identity Matrix of the passed EmuMath Matrix's type to said matrix_. </para>
		/// <para> Although this may be used to assign an Identity of any size, it mainly has useful meaning within a square Matrix (where num_columns == num_rows). </para>
		/// </summary>
		/// <param name="matrix_">: EmuMath Matrix to assign the Identity to (all 1 along the main diagonal, all 0 elsewhere).</param>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_>
		static constexpr inline void identity(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& matrix_)
		{
			EmuMath::Helpers::matrix_identity(matrix_);
		}
#pragma endregion

	private:
		matrix_vector_type _data;

#pragma region UNDERLYING_VECTOR_CREATION
	private:
		template<std::size_t ColumnIndex_, std::size_t OutSize_, typename OutT_, std::size_t...RowIndices_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _make_column_vector(std::index_sequence<RowIndices_...> row_indices_)
		{
			using out_vector = EmuMath::Vector<OutSize_, OutT_>;
			if constexpr (std::is_constructible_v<out_vector, decltype(AtTheoretical<ColumnIndex_, RowIndices_>())...>)
			{
				return out_vector(AtTheoretical<ColumnIndex_, RowIndices_>()...);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<out_vector>(),
					"Attempted to retrieve a Column Vector within an EmuMath Matrix, but the desired output Vector cannot be constructed from the provided column within the Matrix."
				);
			}
		}

		template<std::size_t ColumnIndex_, std::size_t OutSize_, typename OutT_, std::size_t...RowIndices_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _make_column_vector(std::index_sequence<RowIndices_...> row_indices_) const
		{
			// Unfortunate code duplication due to different behaviour when outputting reference Vectors
			using out_vector = EmuMath::Vector<OutSize_, OutT_>;
			if constexpr (std::is_constructible_v<out_vector, decltype(AtTheoretical<ColumnIndex_, RowIndices_>())...>)
			{
				return out_vector(AtTheoretical<ColumnIndex_, RowIndices_>()...);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<out_vector>(),
					"Attempted to retrieve a Column Vector within a const-qualified EmuMath Matrix, but the desired output Vector cannot be constructed from the provided column within the Matrix."
				);
			}
		}

		template<std::size_t RowIndex_, std::size_t OutSize_, typename OutT_, std::size_t...ColumnIndices_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _make_row_vector(std::index_sequence<ColumnIndices_...> column_indices_)
		{
			using out_vector = EmuMath::Vector<OutSize_, OutT_>;
			if constexpr (std::is_constructible_v<out_vector, decltype(AtTheoretical<ColumnIndices_, RowIndex_>())...>)
			{
				return out_vector(AtTheoretical<ColumnIndices_, RowIndex_>()...);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<out_vector>(),
					"Attempted to retrieve a Row Vector within an EmuMath Matrix, but the desired output Vector cannot be constructed from the provided row within the Matrix."
				);
			}
		}

		template<std::size_t RowIndex_, std::size_t OutSize_, typename OutT_, std::size_t...ColumnIndices_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _make_row_vector(std::index_sequence<ColumnIndices_...> column_indices_) const
		{
			// Unfortunate code duplication due to different behaviour when outputting reference Vectors
			using out_vector = EmuMath::Vector<OutSize_, OutT_>;
			if constexpr (std::is_constructible_v<out_vector, decltype(AtTheoretical<ColumnIndices_, RowIndex_>())...>)
			{
				return out_vector(AtTheoretical<ColumnIndices_, RowIndex_>()...);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<out_vector>(),
					"Attempted to retrieve a Row Vector within a const-qualified EmuMath Matrix, but the desired output Vector cannot be constructed from the provided row within the Matrix."
				);
			}
		}

		template<std::size_t MajorIndex_, std::size_t OutSize_, typename OutT_, std::size_t...NonMajorIndices_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _make_major_vector(std::index_sequence<NonMajorIndices_...> non_major_indices_)
		{
			if constexpr (is_column_major)
			{
				return _make_column_vector<MajorIndex_, OutSize_, OutT_>(std::index_sequence<NonMajorIndices_...>());
			}
			else
			{
				return _make_row_vector<MajorIndex_, OutSize_, OutT_>(std::index_sequence<NonMajorIndices_...>());
			}
		}

		template<std::size_t MajorIndex_, std::size_t OutSize_, typename OutT_, std::size_t...NonMajorIndices_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _make_major_vector(std::index_sequence<NonMajorIndices_...> non_major_indices_) const
		{
			if constexpr (is_column_major)
			{
				return _make_column_vector<MajorIndex_, OutSize_, OutT_>(std::index_sequence<NonMajorIndices_...>());
			}
			else
			{
				return _make_row_vector<MajorIndex_, OutSize_, OutT_>(std::index_sequence<NonMajorIndices_...>());
			}
		}

		template<std::size_t NonMajorIndex_, std::size_t OutSize_, typename OutT_, std::size_t...MajorIndices_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _make_non_major_vector(std::index_sequence<MajorIndices_...> major_indices_)
		{
			if constexpr (is_column_major)
			{
				return _make_row_vector<NonMajorIndex_, OutSize_, OutT_>(std::index_sequence<MajorIndices_...>());
			}
			else
			{
				return _make_column_vector<NonMajorIndex_, OutSize_, OutT_>(std::index_sequence<MajorIndices_...>());
			}
		}

		template<std::size_t NonMajorIndex_, std::size_t OutSize_, typename OutT_, std::size_t...MajorIndices_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _make_non_major_vector(std::index_sequence<MajorIndices_...> major_indices_) const
		{
			if constexpr (is_column_major)
			{
				return _make_row_vector<NonMajorIndex_, OutSize_, OutT_>(std::index_sequence<MajorIndices_...>());
			}
			else
			{
				return _make_column_vector<NonMajorIndex_, OutSize_, OutT_>(std::index_sequence<MajorIndices_...>());
			}
		}

		template<std::size_t OutSize_, typename OutT_, std::size_t ColumnOffset_, std::size_t RowOffset_, std::size_t...Indices_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _make_diagonal_vector(std::index_sequence<Indices_...> indices_)
		{
			using out_vector = EmuMath::Vector<OutSize_, OutT_>;
			if constexpr (std::is_constructible_v<out_vector, decltype(AtTheoretical<Indices_ + ColumnOffset_, Indices_ + RowOffset_>())...>)
			{
				return out_vector(AtTheoretical<Indices_ + ColumnOffset_, Indices_ + RowOffset_>()...);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<out_vector>(),
					"Attempted to retrieve a Diagonal Vector within an EmuMath Matrix, but the desired output Vector cannot be constructed from all accessed diagonal indices within the Matrix."
				);
			}
		}

		template<std::size_t OutSize_, typename OutT_, std::size_t ColumnOffset_, std::size_t RowOffset_, std::size_t...Indices_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _make_diagonal_vector(std::index_sequence<Indices_...> indices_) const
		{
			// Even more unfortunate code duplication for the sake of safe and successfuly ref-vector output
			using out_vector = EmuMath::Vector<OutSize_, OutT_>;
			if constexpr (std::is_constructible_v<out_vector, decltype(AtTheoretical<Indices_ + ColumnOffset_, Indices_ + RowOffset_>())...>)
			{
				return out_vector(AtTheoretical<Indices_ + ColumnOffset_, Indices_ + RowOffset_>()...);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<out_vector>(),
					"Attempted to retrieve a Diagonal Vector within a const-qualified EmuMath Matrix, but the desired output Vector cannot be constructed from all accessed diagonal indices within the Matrix."
				);
			}
		}

		template<std::size_t OutSize_, typename OutT_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _make_flattened_vector(std::index_sequence<ColumnIndices_...>, std::index_sequence<RowIndices_...>)
		{
			using out_vector = EmuMath::Vector<OutSize_, OutT_>;
			if constexpr (std::is_constructible_v<out_vector, decltype(AtTheoretical<ColumnIndices_, RowIndices_>())...>)
			{
				return out_vector(at<ColumnIndices_, RowIndices_>()...);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<out_vector>(),
					"Attempted to retrieve a Flattened Vector version of an EmuMath Matrix, but the desired output Vector could not be constructed from all indices within the Matrix."
				);
			}
		}

		template<std::size_t OutSize_, typename OutT_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _make_flattened_vector(std::index_sequence<ColumnIndices_...>, std::index_sequence<RowIndices_...>) const
		{
			using out_vector = EmuMath::Vector<OutSize_, OutT_>;
			if constexpr (std::is_constructible_v<out_vector, decltype(AtTheoretical<ColumnIndices_, RowIndices_>())...>)
			{
				return out_vector(at<ColumnIndices_, RowIndices_>()...);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<out_vector>(),
					"Attempted to retrieve a Flattened Vector version of a const-qualified EmuMath Matrix, but the desired output Vector could not be constructed from all indices within the Matrix."
				);
			}
		}
#pragma endregion
	};

	/// <summary>
	/// <para> Get function for use with EmuMath Matrices using ADL. Equivalent to matrix_.at with the provided FlattenedIndex_. Does not allow theoretical output. </para>
	/// <para> One may note that there is no alternative that uses Column+Row indices. This is due to this functions provision for ADL, with no intent for other uses. </para>
	/// </summary>
	/// <param name="matrix_">: EmuMath Matrix to retrieve the specified contained contiguous flattened index of.</param>
	/// <returns>Reference to the element contained at the specified contiguous flattened index of the passed EmuMath Matrix.</returns>
	template<std::size_t FlattenedIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline const typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type& get
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template at<FlattenedIndex_>();
	}

	template<std::size_t FlattenedIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type& get
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template at<FlattenedIndex_>();
	}
}

#endif
