#ifndef EMU_MATH_COMMON_MATRIX_HELPER_INCLUDES_H_INC_
#define EMU_MATH_COMMON_MATRIX_HELPER_INCLUDES_H_INC_ 1

#include "../_underlying_helpers/_matrix.info.h"
#include "../_underlying_helpers/_matrix_tmp.h"
#include "../_underlying_helpers/_matrix_underlying_copy.h"
#include "../_underlying_helpers/_matrix_underlying_get.h"
#include "../_underlying_helpers/_matrix_underlying_mutate.h"
#include "../_underlying_helpers/_matrix_underlying_stream_append.h"

// CONTAINS:
// --- Includes for all underlying helpers
// --- Macros for functions that are effectively wrapped mutations

#ifdef EMU_MATH_MATRIX_MUTATE_TEMPLATE
#undef EMU_MATH_MATRIX_MUTATE_TEMPLATE
#endif

/// <summary>
/// <para> Macro for EmuMath implementations of functions that are mutations under the hood. This macro should NOT be used outside of EmuMath-provided definitios. </para>
/// <para> This boils down to a cleaner way of typing EmuMath::Helpers::_matrix_underlying::_matrix_mutate_return_out_func_template with the provided template arguments. </para>
/// <para> Function call and arguments still needs to be provided, e.g: EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(...)(to_copy_, args_...). </para>
/// </summary>
/// <param name="_func_template">: Template functor to be instantiated and invoked for each iteration. Template typename WITHOUT any parameters.</param>
/// <param name="_out_num_columns">: Number of columns contained within the output Matrix. Consteval integral value that may be implicitly interpreted as std::size_t.</param>
/// <param name="_out_num_rows">: Number of rows contained within the output Matrix. Consteval integral value that may be implicitly interpreted as std::size_t.</param>
/// <param name="_out_t">: Type contained within the output Matrix. Type provided as the T_ arg in an instantion of EmuMath::Matrix.</param>
/// <param name="_out_column_major">: Boolean indicating if the output Matrix is column-major. Consteval value that may be implicitly interpreted as bool.</param>
/// <param name="_begin_column">: Index of the column at which to begin mutations. Consteval integral value that may be implicitly interpreted as std::size_t.</param>
/// <param name="_end_column">: Index of the column at which to end mutations. Consteval integral value that may be implicitly interpreted as std::size_t.</param>
/// <param name="_begin_row">: Index of the row at which to begin mutations. Consteval integral value that may be implicitly interpreted as std::size_t.</param>
/// <param name="_end_row">: Index of the row at which to end mutations. Consteval integral value that may be implicitly interpreted as std::size_t.</param>
#define EMU_MATH_MATRIX_MUTATE_TEMPLATE(_func_template, _out_num_columns, _out_num_rows, _out_t, _out_column_major, _begin_column, _end_column, _begin_row, _end_row)\
EmuMath::Helpers::_matrix_underlying::_matrix_mutate_return_out_func_template\
<\
	_func_template,\
	(_out_num_columns),\
	(_out_num_rows),\
	_out_t,\
	(_out_column_major),\
	(_begin_column),\
	(_end_column),\
	(_begin_row),\
	(_end_row)\
>

#ifdef EMU_MATH_MATRIX_MUTATE_ASSIGN_TEMPLATE
#undef EMU_MATH_MATRIX_MUTATE_ASSIGN_TEMPLATE
#endif

/// <summary>
/// <para> Macro for EmuMath implementations of functions that are mutations under the hood. This macro should NOT be used outside of EmuMath-provided definitios. </para>
/// <para> This boils down to a cleaner way of typing EmuMath::Helpers::_matrix_underlying::_matrix_mutate_assign_func_template with the provided template arguments. </para>
/// <para> Function call and arguments still needs to be provided, e.g: EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(...)(to_copy_, args_...). </para>
/// </summary>
/// <param name="_func_template">: Template functor to be instantiated and invoked for each iteration. Template typename WITHOUT any parameters.</param>
/// <param name="_begin_column">: Index of the column at which to begin mutations. Consteval integral value that may be implicitly interpreted as std::size_t.</param>
/// <param name="_end_column">: Index of the column at which to end mutations. Consteval integral value that may be implicitly interpreted as std::size_t.</param>
/// <param name="_begin_row">: Index of the row at which to begin mutations. Consteval integral value that may be implicitly interpreted as std::size_t.</param>
/// <param name="_end_row">: Index of the row at which to end mutations. Consteval integral value that may be implicitly interpreted as std::size_t.</param>
/// <param name="_arg_column_offset">
///		: Column offset for reading arguments for performing the mutation function. Consteval integral value that may be implicitly interpreted as std::size_t.
/// </param>
/// <param name="_arg_row_offset">
///		: Row offset for reading arguments for performing the mutation function. Consteval integral value that may be implicitly interpreted as std::size_t.
/// </param>
#define EMU_MATH_MATRIX_MUTATE_ASSIGN_TEMPLATE(_func_template, _begin_column, _end_column, _begin_row, _end_row, _arg_column_offset, _arg_row_offset)\
EmuMath::Helpers::_matrix_underlying::_matrix_mutate_assign_func_template\
<\
	_func_template,\
	(_begin_column),\
	(_end_column),\
	(_begin_row),\
	(_end_row),\
	(_arg_column_offset),\
	(_arg_row_offset)\
>

#ifdef EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE
#undef EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE
#endif

/// <summary>
/// <para> Macro for EmuMath implementations of functions that are mutations under the hood. This macro should NOT be used outside of EmuMath-provided definitios. </para>
/// <para> This boils down to a cleaner way of typing EmuMath::Helpers::_matrix_underlying::_matrix_mutate_copy_func_template with the provided template arguments. </para>
/// <para> Function call and arguments still needs to be provided, e.g: EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(...)(to_copy_, args_...). </para>
/// </summary>
/// <param name="_func_template">: Template functor to be instantiated and invoked for each iteration. Template typename WITHOUT any parameters.</param>
/// <param name="_out_num_columns">: Number of columns contained within the output Matrix. Consteval integral value that may be implicitly interpreted as std::size_t.</param>
/// <param name="_out_num_rows">: Number of rows contained within the output Matrix. Consteval integral value that may be implicitly interpreted as std::size_t.</param>
/// <param name="_out_t">: Type contained within the output Matrix. Type provided as the T_ arg in an instantion of EmuMath::Matrix.</param>
/// <param name="_out_column_major">: Boolean indicating if the output Matrix is column-major. Consteval value that may be implicitly interpreted as bool.</param>
/// <param name="_copy_ref_t">: The exact reference type of the item being copied. For example, when copying a Matrix, this should be:  const input_matrix&amp;.</param>
/// <param name="_arg_column_offset">
///		: Column offset for reading arguments for performing the mutation function. Consteval integral value that may be implicitly interpreted as std::size_t.
/// </param>
/// <param name="_arg_row_offset">
///		: Row offset for reading arguments for performing the mutation function. Consteval integral value that may be implicitly interpreted as std::size_t.
/// </param>
#define EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(_func_template, _out_num_columns, _out_num_rows, _out_t, _out_column_major, _copy_ref_t, _arg_column_offset, _arg_row_offset)\
EmuMath::Helpers::_matrix_underlying::_matrix_mutate_copy_func_template\
<\
	_func_template,\
	_copy_ref_t,\
	(0),\
	(_out_num_columns),\
	(0),\
	(_out_num_rows),\
	(_arg_column_offset),\
	(_arg_row_offset),\
	_out_t,\
	(_out_num_columns),\
	(_out_num_rows),\
	(_out_column_major)\
>

#ifdef EMU_MATH_MATRIX_MUTATE_COPY_ASSIGN_TEMPLATE
#undef EMU_MATH_MATRIX_MUTATE_COPY_ASSIGN_TEMPLATE
#endif

/// <summary>
/// <para> Macro for EmuMath implementations of functions that are assigning mutations under the hood. This macro should NOT be used outside of EmuMath-provided definitios. </para>
/// <para> This boils down to a cleaner way of typing EmuMath::Helpers::_matrix_underlying::_matrix_mutate_copy_assign_func_template with the provided template arguments. </para>
/// <para> Function call and arguments still needs to be provided, e.g: EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(...)(to_copy_, args_...). </para>
/// </summary>
/// <param name="_func_template">: Template functor to be instantiated and invoked for each iteration. Template typename WITHOUT any parameters.</param>
/// <param name="_copy_ref_t">: The exact reference type of the item being copied. For example, when copying a Matrix, this should be:  const input_matrix&amp;.</param>
/// <param name="_mut_begin_column">: Output column at which to begin performing mutations. Consteval integral value that may be implicitly interpreted as std::size_t. </param>
/// <param name="_mut_end_column">: Output column at which to stop performing mutations. Consteval integral value that may be implicitly interpreted as std::size_t. </param>
/// <param name="_mut_begin_row">: Output row at which to begin performing mutations. Consteval integral value that may be implicitly interpreted as std::size_t. </param>
/// <param name="_mut_end_row">: Output row at which to stop performing mutations. Consteval integral value that may be implicitly interpreted as std::size_t. </param>
/// <param name="_arg_column_offset">
///		: Column offset for reading arguments for performing the mutation function. Consteval integral value that may be implicitly interpreted as std::size_t.
/// </param>
/// <param name="_arg_row_offset">
///		: Row offset for reading arguments for performing the mutation function. Consteval integral value that may be implicitly interpreted as std::size_t.
/// </param>
#define EMU_MATH_MATRIX_MUTATE_COPY_ASSIGN_TEMPLATE(_func_template, _copy_ref_t, _mut_begin_column, _mut_end_column, _mut_begin_row, _mut_end_row, _arg_column_offset, _arg_row_offset)\
EmuMath::Helpers::_matrix_underlying::_matrix_mutate_copy_assign_func_template\
<\
	_func_template,\
	_copy_ref_t,\
	_mut_begin_column,\
	_mut_end_column,\
	_mut_begin_row,\
	_mut_end_row,\
	_arg_column_offset,\
	_arg_row_offset\
>

#ifdef EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE
#undef EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE
#endif

/// <summary>
/// <para> Macro for EmuMath implementations of functions that are assigning mutations under the hood. This macro should NOT be used outside of EmuMath-provided definitios. </para>
/// <para> This boils down to a cleaner way of typing EmuMath::Helpers::_matrix_underlying::_matrix_mutate_invoke_only_func_template with the provided template arguments. </para>
/// <para> Function call and arguments still needs to be provided, e.g: EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(...)(to_copy_, args_...). </para>
/// </summary>
#define EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(_func_template, _begin_column, _end_column, _begin_row, _end_row, _column_major)\
EmuMath::Helpers::_matrix_underlying::_matrix_mutate_invoke_only_func_template\
<\
	_func_template,\
	(_begin_column),\
	(_end_column),\
	(_begin_column),\
	(_end_row),\
	(_column_major)\
>

#ifdef EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
#undef EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
#endif

#define EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE\
(\
	_func_template, _out_num_columns, _out_num_rows, _out_t, _out_column_major, _copy_ref_t, _begin_column, _end_column, _begin_row, _end_row, _arg_column_offset, _arg_row_offset\
)\
EmuMath::Helpers::_matrix_underlying::_matrix_mutate_copy_func_template\
<\
	_func_template,\
	_copy_ref_t,\
	(_begin_column),\
	(_end_column),\
	(_begin_row),\
	(_end_row),\
	(_arg_column_offset),\
	(_arg_row_offset),\
	_out_t,\
	(_out_num_columns),\
	(_out_num_rows),\
	(_out_column_major)\
>

#ifdef EMU_MATH_MATRIX_MUTATE_COPY_ASSIGN_RANGE_TEMPLATE
#undef EMU_MATH_MATRIX_MUTATE_COPY_ASSIGN_RANGE_TEMPLATE
#endif

#define EMU_MATH_MATRIX_MUTATE_COPY_ASSIGN_RANGE_TEMPLATE(_func_template, _copy_ref_t, _begin_column, _end_column, _begin_row, _end_row, _arg_column_offset, _arg_row_offset)\
EmuMath::Helpers::_matrix_underlying::_matrix_mutate_copy_assign_func_template\
<\
	_func_template,\
	_copy_ref_t,\
	(_begin_column),\
	(_end_column),\
	(_begin_row),\
	(_end_row),\
	(_arg_column_offset),\
	(_arg_row_offset)\
>

#endif
