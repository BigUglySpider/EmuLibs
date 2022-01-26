#ifndef EMU_MATH_VECTOR_HELPERS_H_INC_
#define EMU_MATH_VECTOR_HELPERS_H_INC_ 1

// CONTAINS:
// --- Includes for all EmuMath Vector Helpers
// --- make_vector

#include "_common_vector_helpers.h"
#include "_vector_basic_arithmetic.h"
#include "_vector_basic_arithmetic_assign.h"
#include "_vector_bitwise.h"
#include "_vector_bitwise_assign.h"
#include "_vector_cast.h"
#include "_vector_cmp.h"
#include "_vector_copy.h"
#include "_vector_get.h"
#include "_vector_misc_arithmetic.h"
#include "_vector_mutation.h"
#include "_vector_rounds.h"
#include "_vector_rounds_constexpr.h"
#include "_vector_special_operations.h"
#include "_vector_stream_append.h"
#include "_vector_unary_arithmetic.h"

namespace EmuMath
{
	template
	<
		typename OutT_,
		typename...Args_,
		typename = std::enable_if_t<std::is_constructible_v<EmuMath::Vector<sizeof...(Args_), OutT_>, decltype(std::forward<Args_>(std::declval<Args_>()))...>>
	>
	[[nodiscard]] constexpr inline EmuMath::Vector<sizeof...(Args_), OutT_> make_vector(Args_&&...args_)
	{
		return EmuMath::Vector<sizeof...(Args_), OutT_>(std::forward<Args_>(args_)...);
	}
}

#endif
