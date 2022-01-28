#ifndef EMU_MATH_VECTOR_COMMON_HELPERS_H_INC_
#define EMU_MATH_VECTOR_COMMON_HELPERS_H_INC_ 1

#include "../_underlying_helpers/_vector_cast_underlying.h"
#include "../_underlying_helpers/_vector_cmp_underlying.h"
#include "../_underlying_helpers/_vector_copy_underlying.h"
#include "../_underlying_helpers/_vector_get_underlying.h"
#include "../_underlying_helpers/_vector_info.h"
#include "../_underlying_helpers/_vector_iterator_underlying.h"
#include "../_underlying_helpers/_vector_misc_arithmetic_underlying.h"
#include "../_underlying_helpers/_vector_mutation_underlying.h"
#include "../_underlying_helpers/_vector_special_operations_underlying.h"
#include "../_underlying_helpers/_vector_stream_append_underlying.h"
#include "../_underlying_helpers/_vector_tmp.h"

// CONTAINS:
// --- All underlying helper includes
// --- All macros used within this _helpers folder.
// ------ Macros to type an underlying vector helper with minimal whitespace to maintain readability and conciseness in "public" helper funcs
// --------- "public" in this context refers to global EmuMath Helper functions for Vectors that are not preceded with an underscore.

#ifdef EMU_MATH_VECTOR_MUTATION
#undef EMU_MATH_VECTOR_MUTATION
#endif
/// <summary>
/// <para> Macro for use with functions that perform an EmuMath Vector mutation without any suffix. </para>
/// <para> Note that this only types the function signature; you will need to append `(arguments);` yourself. </para>
/// </summary>
/// <param name="_func_type">Type of function to be invoked (this should typically be an EmuCore functor).</param>
/// <param name="_out_size">Constexpr Size_ arg for the output Vector.</param>
/// <param name="_out_t">T_ arg for the output Vector.</param>
/// <param name="_in_size">Constexpr Size_ arg for the input Vector.</param>
/// <param name="_in_t">T_ arg for the input Vector.</param>
/// <param name="_out_begin">Constexpr index at which mutations will start to be outputted (inclusive).</param>
/// <param name="_out_end">Constexpr index at which mutations will be stop being being outputted (exclusive).</param>
/// <param name="_read_begin">Constexpr index at which arguments will begin being read from. This is incremented every time it is used (but not when ignored).</param>
#define EMU_MATH_VECTOR_MUTATION(_func_type, _out_size, _out_t, _in_size, _in_t)\
EmuMath::Helpers::_vector_underlying::_vector_mutate_args_only\
<\
	_func_type,\
	EmuMath::Vector<(_out_size), _out_t>,\
	0,\
	EmuMath::Vector<(_out_size), _out_t>::size,\
	0\
>

#ifdef EMU_MATH_VECTOR_MUTATION_REF
#undef EMU_MATH_VECTOR_MUTATION_REF
#endif
/// <summary>
/// <para> Macro for use with functions that perform an EmuMath Vector mutation without any suffix, and output to a passed Vector ref. </para>
/// <para> Note that this only types the function signature; you will need to append `(arguments);` yourself. </para>
/// </summary>
/// <param name="_func_type">Type of function to be invoked (this should typically be an EmuCore functor).</param>
/// <param name="_out_size">Constexpr Size_ arg for the output Vector.</param>
/// <param name="_out_t">T_ arg for the output Vector.</param>
/// <param name="_in_size">Constexpr Size_ arg for the input Vector.</param>
/// <param name="_in_t">T_ arg for the input Vector.</param>
/// <param name="_out_begin">Constexpr index at which mutations will start to be outputted (inclusive).</param>
/// <param name="_out_end">Constexpr index at which mutations will be stop being being outputted (exclusive).</param>
/// <param name="_read_begin">Constexpr index at which arguments will begin being read from. This is incremented every time it is used (but not when ignored).</param>
#define EMU_MATH_VECTOR_MUTATION_REF(_func_type, _out_size, _out_t, _in_size, _in_t)\
EmuMath::Helpers::_vector_underlying::_vector_mutate_no_func_passed\
<\
	_func_type,\
	EmuMath::Vector<(_out_size), _out_t>,\
	0,\
	EmuMath::Vector<(_out_size), _out_t>::size,\
	0\
>

#ifdef EMU_MATH_VECTOR_MUTATION_RANGE
#undef EMU_MATH_VECTOR_MUTATION_RANGE
#endif
/// <summary>
/// <para> Macro for use with functions that perform an EmuMath Vector mutation with the suffix `_range`. </para>
/// <para> Note that this only types the function signature; you will need to append `(arguments);` yourself. </para>
/// </summary>
/// <param name="_func_type">Type of function to be invoked (this should typically be an EmuCore functor).</param>
/// <param name="_out_size">Constexpr Size_ arg for the output Vector.</param>
/// <param name="_out_t">T_ arg for the output Vector.</param>
/// <param name="_in_size">Constexpr Size_ arg for the input Vector.</param>
/// <param name="_in_t">T_ arg for the input Vector.</param>
/// <param name="_out_begin">Constexpr index at which mutations will start to be outputted (inclusive).</param>
/// <param name="_out_end">Constexpr index at which mutations will be stop being being outputted (exclusive).</param>
/// <param name="_read_begin">Constexpr index at which arguments will begin being read from. This is incremented every time it is used (but not when ignored).</param>
#define EMU_MATH_VECTOR_MUTATION_RANGE(_func_type, _out_size, _out_t, _in_size, _in_t, _out_begin, _out_end)\
EmuMath::Helpers::_vector_underlying::_vector_partial_mutation_copy_args_only\
<\
	(_out_size),\
	_out_t,\
	_func_type,\
	const EmuMath::Vector<(_in_size), InT_>&,\
	(_out_begin),\
	(_out_end),\
	(_out_begin)\
>

#ifdef EMU_MATH_VECTOR_MUTATION_REF_RANGE
#undef EMU_MATH_VECTOR_MUTATION_REF_RANGE
#endif
/// <summary>
/// <para> Macro for use with functions that perform an EmuMath Vector mutation with the suffix `_range`, and output to a passed Vector ref. </para>
/// <para> Note that this only types the function signature; you will need to append `(arguments);` yourself. </para>
/// </summary>
/// <param name="_func_type">Type of function to be invoked (this should typically be an EmuCore functor).</param>
/// <param name="_out_size">Constexpr Size_ arg for the output Vector.</param>
/// <param name="_out_t">T_ arg for the output Vector.</param>
/// <param name="_in_size">Constexpr Size_ arg for the input Vector.</param>
/// <param name="_in_t">T_ arg for the input Vector.</param>
/// <param name="_out_begin">Constexpr index at which mutations will start to be outputted (inclusive).</param>
/// <param name="_out_end">Constexpr index at which mutations will be stop being being outputted (exclusive).</param>
/// <param name="_read_begin">Constexpr index at which arguments will begin being read from. This is incremented every time it is used (but not when ignored).</param>
#define EMU_MATH_VECTOR_MUTATION_REF_RANGE(_func_type, _out_size, _out_t, _in_size, _in_t, _out_begin, _out_end, _read_begin)\
EmuMath::Helpers::_vector_underlying::_vector_partial_mutation_copy_no_func_passed\
<\
	_func_type,\
	EmuMath::Vector<(_out_size), _out_t>,\
	const EmuMath::Vector<(_in_size), InT_>&,\
	(_out_begin),\
	(_out_end),\
	(_out_begin)\
>

#ifdef EMU_MATH_VECTOR_MUTATION_RANGE_NO_COPY
#undef EMU_MATH_VECTOR_MUTATION_RANGE_NO_COPY
#endif
/// <summary>
/// <para> Macro for use with functions that perform an EmuMath Vector mutation with the suffix `_range_no_copy`. </para>
/// <para> Note that this only types the function signature; you will need to append `(arguments);` yourself. </para>
/// </summary>
/// <param name="_func_type">Type of function to be invoked (this should typically be an EmuCore functor).</param>
/// <param name="_out_size">Constexpr Size_ arg for the output Vector.</param>
/// <param name="_out_t">T_ arg for the output Vector.</param>
/// <param name="_in_size">Constexpr Size_ arg for the input Vector.</param>
/// <param name="_in_t">T_ arg for the input Vector.</param>
/// <param name="_out_begin">Constexpr index at which mutations will start to be outputted (inclusive).</param>
/// <param name="_out_end">Constexpr index at which mutations will be stop being being outputted (exclusive).</param>
/// <param name="_read_begin">Constexpr index at which arguments will begin being read from. This is incremented every time it is used (but not when ignored).</param>
#define EMU_MATH_VECTOR_MUTATION_RANGE_NO_COPY(_func_type, _out_size, _out_t, _in_size, _in_t, _out_begin, _out_end, _read_begin)\
EmuMath::Helpers::_vector_underlying::_vector_mutate_args_only\
<\
	_func_type,\
	EmuMath::Vector<(_out_size), _out_t>,\
	(_out_begin),\
	(_out_end),\
	(_read_begin)\
>

#ifdef EMU_MATH_VECTOR_MUTATION_REF_RANGE_NO_COPY
#undef EMU_MATH_VECTOR_MUTATION_REF_RANGE_NO_COPY
#endif
/// <summary>
/// <para> Macro for use with functions that perform an EmuMath Vector mutation with the suffix `_range_no_copy`, and output to a passed Vector ref. </para>
/// <para> Note that this only types the function signature; you will need to append `(arguments);` yourself. </para>
/// </summary>
/// <param name="_func_type">Type of function to be invoked (this should typically be an EmuCore functor).</param>
/// <param name="_out_size">Constexpr Size_ arg for the output Vector.</param>
/// <param name="_out_t">T_ arg for the output Vector.</param>
/// <param name="_in_size">Constexpr Size_ arg for the input Vector.</param>
/// <param name="_in_t">T_ arg for the input Vector.</param>
/// <param name="_out_begin">Constexpr index at which mutations will start to be outputted (inclusive).</param>
/// <param name="_out_end">Constexpr index at which mutations will be stop being being outputted (exclusive).</param>
/// <param name="_read_begin">Constexpr index at which arguments will begin being read from. This is incremented every time it is used (but not when ignored).</param>
#define EMU_MATH_VECTOR_MUTATION_REF_RANGE_NO_COPY(_func_type, _out_size, _out_t, _in_size, _in_t, _out_begin, _out_end, _read_begin)\
EmuMath::Helpers::_vector_underlying::_vector_mutate_no_func_passed\
<\
	_func_type,\
	EmuMath::Vector<(_out_size), _out_t>,\
	(_out_begin),\
	(_out_end),\
	(_read_begin)\
>

#ifdef EMU_MATH_VECTOR_MUTATE_TEMPLATE
#undef EMU_MATH_VECTOR_MUTATE_TEMPLATE
#endif
#define EMU_MATH_VECTOR_MUTATE_TEMPLATE(_func_template, _out_size, _out_t)\
EmuMath::Helpers::_vector_underlying::_vector_mutate_with_func_template_args_only\
<\
	_func_template,\
	EmuMath::Vector<(_out_size), _out_t>,\
	0,\
	EmuMath::Vector<(_out_size), _out_t>::size,\
	0\
>

#ifdef EMU_MATH_VECTOR_MUTATE_REF_TEMPLATE
#undef EMU_MATH_VECTOR_MUTATE_REF_TEMPLATE
#endif
#define EMU_MATH_VECTOR_MUTATE_REF_TEMPLATE(_func_template, _out_size, _out_t)\
EmuMath::Helpers::_vector_underlying::_vector_mutate_with_func_template_no_func_passed\
<\
	_func_template,\
	EmuMath::Vector<(_out_size), _out_t>,\
	0,\
	EmuMath::Vector<(_out_size), _out_t>::size,\
	0\
>

#ifdef EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE
#undef EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE
#endif
#define EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(_func_template, _out_size, _out_t, _in_size, _in_t, _begin_index, _end_index)\
EmuMath::Helpers::_vector_underlying::_vector_partial_mutation_copy_with_func_template_args_only\
<\
	_func_template,\
	(_out_size),\
	_out_t,\
	const EmuMath::Vector<(_in_size), _in_t>&,\
	(_begin_index),\
	(_end_index),\
	(_begin_index)\
>

#ifdef EMU_MATH_VECTOR_MUTATE_REF_RANGE_TEMPLATE
#undef EMU_MATH_VECTOR_MUTATE_REF_RANGE_TEMPLATE
#endif
#define EMU_MATH_VECTOR_MUTATE_REF_RANGE_TEMPLATE(_func_template, _out_size, _out_t, _in_size, _in_t, _begin_index, _end_index)\
EmuMath::Helpers::_vector_underlying::_vector_partial_mutation_copy_with_func_template_no_func_passed\
<\
	_func_template,\
	EmuMath::Vector<(_out_size), _out_t>,\
	const EmuMath::Vector<(_in_size), _in_t>&,\
	(_begin_index),\
	(_end_index),\
	(_begin_index)\
>

#ifdef EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE
#undef EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE
#endif
#define EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(_func_template, _out_size, _out_t, _begin_index, _end_index, _arg_index)\
EmuMath::Helpers::_vector_underlying::_vector_mutate_with_func_template_args_only\
<\
	_func_template,\
	EmuMath::Vector<(_out_size), _out_t>,\
	(_begin_index),\
	(_end_index),\
	(_arg_index)\
>

#ifdef EMU_MATH_VECTOR_MUTATE_REF_RANGE_NO_COPY_TEMPLATE
#undef EMU_MATH_VECTOR_MUTATE_REF_RANGE_NO_COPY_TEMPLATE
#endif
#define EMU_MATH_VECTOR_MUTATE_REF_RANGE_NO_COPY_TEMPLATE(_func_template, _out_size, _out_t, _begin_index, _end_index, _arg_index)\
EmuMath::Helpers::_vector_underlying::_vector_mutate_with_func_template_no_func_passed\
<\
	_func_template,\
	EmuMath::Vector<(_out_size), _out_t>,\
	(_begin_index),\
	(_end_index),\
	(_arg_index)\
>

#ifdef EMU_MATH_VECTOR_MUTATE_TEMPLATE_APPEND_OUT
#undef EMU_MATH_VECTOR_MUTATE_TEMPLATE_APPEND_OUT
#endif
// Macro for providing a template for an underlying functions to determine the arguments for, with the value_type_uq of the out vector appended as the 0th or final argument.
#define EMU_MATH_VECTOR_MUTATE_TEMPLATE_APPEND_OUT(_func_template, _custom_args_at_start, _out_size, _out_t)\
EmuMath::Helpers::_vector_underlying::_vector_mutate_with_func_template_extra_args_args_only\
<\
	_func_template,\
	EmuMath::Vector<(_out_size), _out_t>,\
	std::tuple<EmuMath::Vector<(_out_size), _out_t>>,\
	(_custom_args_at_start),\
	0,\
	EmuMath::Vector<(_out_size), _out_t>::size,\
	0\
>

#ifdef EMU_MATH_VECTOR_MUTATE_REF_TEMPLATE_APPEND_OUT
#undef EMU_MATH_VECTOR_MUTATE_REF_TEMPLATE_APPEND_OUT
#endif
#define EMU_MATH_VECTOR_MUTATE_REF_TEMPLATE_APPEND_OUT(_func_template, _custom_args_at_start, _out_size, _out_t)\
EmuMath::Helpers::_vector_underlying::_vector_mutate_with_func_template_extra_args_no_func_passed\
<\
	_func_template,\
	EmuMath::Vector<(_out_size), _out_t>,\
	std::tuple<EmuMath::Vector<(_out_size), _out_t>>,\
	(_custom_args_at_start),\
	0,\
	EmuMath::Vector<(_out_size), _out_t>::size,\
	0\
>

#ifdef EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE_APPEND_OUT
#undef EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE_APPEND_OUT
#endif
#define EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE_APPEND_OUT(_func_template, _custom_args_at_start, _out_size, _out_t, _in_size, _in_t, _begin_index, _end_index)\
EmuMath::Helpers::_vector_underlying::_vector_partial_mutation_copy_with_func_template_extra_args_args_only\
<\
	_func_template,\
	(_out_size),\
	_out_t,\
	const EmuMath::Vector<(_in_size), _in_t>&,\
	std::tuple<EmuMath::Vector<(_out_size), _out_t>>,\
	(_custom_args_at_start),\
	(_begin_index),\
	(_end_index),\
	(_begin_index)\
>

#ifdef EMU_MATH_VECTOR_MUTATE_REF_RANGE_TEMPLATE_APPEND_OUT
#undef EMU_MATH_VECTOR_MUTATE_REF_RANGE_TEMPLATE_APPEND_OUT
#endif
#define EMU_MATH_VECTOR_MUTATE_REF_RANGE_TEMPLATE_APPEND_OUT(_func_template, _custom_args_at_start, _out_size, _out_t, _in_size, _in_t, _begin_index, _end_index)\
EmuMath::Helpers::_vector_underlying::_vector_partial_mutation_copy_with_func_template_extra_args_no_func_passed\
<\
	_func_template,\
	EmuMath::Vector<(_out_size), _out_t>,\
	const EmuMath::Vector<(_in_size), _in_t>&,\
	std::tuple<EmuMath::Vector<(_out_size), _out_t>>,\
	_custom_args_at_start,\
	(_begin_index),\
	(_end_index),\
	(_begin_index)\
>

#ifdef EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE_APPEND_OUT
#undef EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE_APPEND_OUT
#endif
#define EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE_APPEND_OUT(_func_template, _custom_args_at_start, _out_size, _out_t, _begin_index, _end_index, _arg_index)\
EmuMath::Helpers::_vector_underlying::_vector_mutate_with_func_template_extra_args_args_only\
<\
	_func_template,\
	EmuMath::Vector<(_out_size), _out_t>,\
	std::tuple<EmuMath::Vector<(_out_size), _out_t>>,\
	(_custom_args_at_start),\
	(_begin_index),\
	(_end_index),\
	(_arg_index)\
>

#ifdef EMU_MATH_VECTOR_MUTATE_REF_RANGE_NO_COPY_TEMPLATE_APPEND_OUT
#undef EMU_MATH_VECTOR_MUTATE_REF_RANGE_NO_COPY_TEMPLATE_APPEND_OUT
#endif
#define EMU_MATH_VECTOR_MUTATE_REF_RANGE_NO_COPY_TEMPLATE_APPEND_OUT(_func_template, _custom_args_at_start, _out_size, _out_t, _begin_index, _end_index, _arg_index)\
EmuMath::Helpers::_vector_underlying::_vector_mutate_with_func_template_extra_args_no_func_passed\
<\
	_func_template,\
	EmuMath::Vector<(_out_size), _out_t>,\
	std::tuple<EmuMath::Vector<(_out_size), _out_t>>,\
	(_custom_args_at_start),\
	(_begin_index),\
	(_end_index),\
	(_arg_index)\
>

#endif
