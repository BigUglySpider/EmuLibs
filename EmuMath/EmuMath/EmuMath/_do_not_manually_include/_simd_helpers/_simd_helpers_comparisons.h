#ifndef EMU_MATH_SIMD_HELPERS_COMPARISONS_H_INC_
#define EMU_MATH_SIMD_HELPERS_COMPARISONS_H_INC_ 1

#include "_common_simd_helpers_includes.h"
#include "_simd_helpers_masks.h"

namespace EmuMath::SIMD
{
	/// <summary> Performs an equality comparison of respective elements of the two passed SIMD vectors and returns the resultant 4-bit move mask. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>4-bit move mask resulting from the comparison. Each individual bit starting from the least-significant represents an element's comparison result.</returns>
	[[nodiscard]] inline int mask_equal(__m128 lhs, __m128 rhs)
	{
		__m128 result = _mm_cmpeq_ps(lhs, rhs);
		return _mm_movemask_ps(result);
	}
	/// <summary> Performs an inequality comparison of respective elements of the two passed SIMD vectors and returns the resultant 4-bit move mask. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>4-bit move mask resulting from the comparison. Each individual bit starting from the least-significant represents an element's comparison result.</returns>
	[[nodiscard]] inline int mask_not_equal(__m128 lhs, __m128 rhs)
	{
		__m128 result = _mm_cmpneq_ps(lhs, rhs);
		return _mm_movemask_ps(result);
	}
	/// <summary> Performs a less-than comparison of respective elements of the two passed SIMD vectors and returns the resultant 4-bit move mask. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>4-bit move mask resulting from the comparison. Each individual bit starting from the least-significant represents an element's comparison result.</returns>
	[[nodiscard]] inline int mask_less_than(__m128 lhs, __m128 rhs)
	{
		__m128 result = _mm_cmplt_ps(lhs, rhs);
		return _mm_movemask_ps(result);
	}
	/// <summary> Performs a greater-than comparison of respective elements of the two passed SIMD vectors and returns the resultant 4-bit move mask. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>4-bit move mask resulting from the comparison. Each individual bit starting from the least-significant represents an element's comparison result.</returns>
	[[nodiscard]] inline int mask_greater_than(__m128 lhs, __m128 rhs)
	{
		__m128 result = _mm_cmpgt_ps(lhs, rhs);
		return _mm_movemask_ps(result);
	}
	/// <summary> Performs a less-or-equal comparison of respective elements of the two passed SIMD vectors and returns the resultant 4-bit move mask. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>4-bit move mask resulting from the comparison. Each individual bit starting from the least-significant represents an element's comparison result.</returns>
	[[nodiscard]] inline int mask_less_equal(__m128 lhs, __m128 rhs)
	{
		__m128 result = _mm_cmple_ps(lhs, rhs);
		return _mm_movemask_ps(result);
	}
	/// <summary> Performs a greater-or-equal comparison of respective elements of the two passed SIMD vectors and returns the resultant 4-bit move mask. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>4-bit move mask resulting from the comparison. Each individual bit starting from the least-significant represents an element's comparison result.</returns>
	[[nodiscard]] inline int mask_greater_equal(__m128 lhs, __m128 rhs)
	{
		__m128 result = _mm_cmpge_ps(lhs, rhs);
		return _mm_movemask_ps(result);
	}

	/// <summary>
	/// <para> Compares the equality of respective elements of the two passed SIMD vectors. </para>
	/// <para> The output of this function will be true if the respective template arguments match the results of the comparison. Otherwise, it will be false. </para>
	/// </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Boolean indicating if the result of an equality comparison with the provided vectors matches all provided template arguments for respective elements.</returns>
	template<bool X_ = true, bool Y_ = true, bool Z_ = true, bool W_ = true>
	[[nodiscard]] inline bool all_equal(__m128 lhs, __m128 rhs)
	{
		return mask_equal(lhs, rhs) == move_mask_v<X_, Y_, Z_, W_>;
	}
	[[nodiscard]] inline bool all_equal(__m128 lhs, __m128 rhs, int mask_)
	{
		return mask_equal(lhs, rhs) == mask_;
	}
	[[nodiscard]] inline bool all_equal(__m128 lhs, __m128 rhs, bool x_, bool y_, bool z_, bool w_)
	{
		return all_equal(lhs, rhs, generate_move_mask(x_, y_, z_, w_));
	}
	/// <summary>
	/// <para> Compares the inequality of respective elements of the two passed SIMD vectors. </para>
	/// <para> The output of this function will be true if the respective template arguments match the results of the comparison. Otherwise, it will be false. </para>
	/// </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Boolean indicating if the result of an inequality comparison with the provided vectors matches all provided template arguments for respective elements.</returns>
	template<bool X_ = true, bool Y_ = true, bool Z_ = true, bool W_ = true>
	[[nodiscard]] inline bool all_not_equal(__m128 lhs, __m128 rhs)
	{
		return mask_not_equal(lhs, rhs) == move_mask_v<X_, Y_, Z_, W_>;
	}
	[[nodiscard]] inline bool all_not_equal(__m128 lhs, __m128 rhs, int mask_)
	{
		return mask_not_equal(lhs, rhs) == mask_;
	}
	[[nodiscard]] inline bool all_not_equal(__m128 lhs, __m128 rhs, bool x_, bool y_, bool z_, bool w_)
	{
		return all_not_equal(lhs, rhs, generate_move_mask(x_, y_, z_, w_));
	}
	/// <summary>
	/// <para> Performs a less-than (&lt;) comparison of respective elements of the two passed SIMD vectors. </para>
	/// <para> The output of this function will be true if the respective template arguments match the results of the comparison. Otherwise, it will be false. </para>
	/// </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Boolean indicating if the result of a less-than (&lt;) comparison with the provided vectors matches all provided template arguments for respective elements.</returns>
	template<bool X_ = true, bool Y_ = true, bool Z_ = true, bool W_ = true>
	[[nodiscard]] inline bool all_less_than(__m128 lhs, __m128 rhs)
	{
		return mask_less_than(lhs, rhs) == move_mask_v<X_, Y_, Z_, W_>;
	}
	[[nodiscard]] inline bool all_less_than(__m128 lhs, __m128 rhs, int mask_)
	{
		return mask_less_than(lhs, rhs) == mask_;
	}
	[[nodiscard]] inline bool all_less_than(__m128 lhs, __m128 rhs, bool x_, bool y_, bool z_, bool w_)
	{
		return all_less_than(lhs, rhs, generate_move_mask(x_, y_, z_, w_));
	}
	/// <summary>
	/// <para> Performs a greater-than (&gt;) comparison of respective elements of the two passed SIMD vectors. </para>
	/// <para> The output of this function will be true if the respective template arguments match the results of the comparison. Otherwise, it will be false. </para>
	/// </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Boolean indicating if the result of a greater-than (&gt;) comparison with the provided vectors matches all provided template arguments for respective elements.</returns>
	template<bool X_ = true, bool Y_ = true, bool Z_ = true, bool W_ = true>
	[[nodiscard]] inline bool all_greater_than(__m128 lhs, __m128 rhs)
	{
		return mask_greater_than(lhs, rhs) == move_mask_v<X_, Y_, Z_, W_>;
	}
	[[nodiscard]] inline bool all_greater_than(__m128 lhs, __m128 rhs, int mask_)
	{
		return mask_greater_than(lhs, rhs) == mask_;
	}
	[[nodiscard]] inline bool all_greater_than(__m128 lhs, __m128 rhs, bool x_, bool y_, bool z_, bool w_)
	{
		return all_greater_than(lhs, rhs, generate_move_mask(x_, y_, z_, w_));
	}
	/// <summary>
	/// <para> Performs a less-or-equal (&lt;=) comparison of respective elements of the two passed SIMD vectors. </para>
	/// <para> The output of this function will be true if the respective template arguments match the results of the comparison. Otherwise, it will be false. </para>
	/// </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Boolean indicating if the result of a less-or-equal (&lt;=) comparison with the provided vectors matches all provided template arguments for respective elements.</returns>
	template<bool X_ = true, bool Y_ = true, bool Z_ = true, bool W_ = true>
	[[nodiscard]] inline bool all_less_equal(__m128 lhs, __m128 rhs)
	{
		return mask_less_equal(lhs, rhs) == move_mask_v<X_, Y_, Z_, W_>;
	}
	[[nodiscard]] inline bool all_less_equal(__m128 lhs, __m128 rhs, int mask_)
	{
		return mask_less_equal(lhs, rhs) == mask_;
	}
	[[nodiscard]] inline bool all_less_equal(__m128 lhs, __m128 rhs, bool x_, bool y_, bool z_, bool w_)
	{
		return all_less_equal(lhs, rhs, generate_move_mask(x_, y_, z_, w_));
	}
	/// <summary>
	/// <para> Performs a greater-or-equal (&gt;=) comparison of respective elements of the two passed SIMD vectors. </para>
	/// <para> The output of this function will be true if the respective template arguments match the results of the comparison. Otherwise, it will be false. </para>
	/// </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Boolean indicating if the result of a greater-or-equal (&gt;=) comparison with the provided vectors matches all provided template arguments for respective elements.</returns>
	template<bool X_ = true, bool Y_ = true, bool Z_ = true, bool W_ = true>
	[[nodiscard]] inline bool all_greater_equal(__m128 lhs, __m128 rhs)
	{
		return mask_greater_equal(lhs, rhs) == move_mask_v<X_, Y_, Z_, W_>;
	}
	[[nodiscard]] inline bool all_greater_equal(__m128 lhs, __m128 rhs, int mask_)
	{
		return mask_greater_equal(lhs, rhs) == mask_;
	}
	[[nodiscard]] inline bool all_greater_equal(__m128 lhs, __m128 rhs, bool x_, bool y_, bool z_, bool w_)
	{
		return all_greater_equal(lhs, rhs, generate_move_mask(x_, y_, z_, w_));
	}

	/// <summary> Performs an equality comparison of respective elements of the two passed SIMD vectors. Returns true if at least one element comparison was true. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>True if any respective-element comparison is true, otherwise false.</returns>
	[[nodiscard]] inline bool any_equal(__m128 lhs, __m128 rhs)
	{
		return mask_equal(lhs, rhs) != 0;
	}
	/// <summary> Performs an inequality comparison of respective elements of the two passed SIMD vectors. Returns true if at least one element comparison was true. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>True if any respective-element comparison is true, otherwise false.</returns>
	[[nodiscard]] inline bool any_not_equal(__m128 lhs, __m128 rhs)
	{
		return mask_not_equal(lhs, rhs) != 0;
	}
	/// <summary> Performs a less-than comparison of respective elements of the two passed SIMD vectors. Returns true if at least one element comparison was true. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>True if any respective-element comparison is true, otherwise false.</returns>
	[[nodiscard]] inline bool any_less_than(__m128 lhs, __m128 rhs)
	{
		return mask_less_than(lhs, rhs) != 0;
	}
	/// <summary> Performs a greater-than comparison of respective elements of the two passed SIMD vectors. Returns true if at least one element comparison was true. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>True if any respective-element comparison is true, otherwise false.</returns>
	[[nodiscard]] inline bool any_greater_than(__m128 lhs, __m128 rhs)
	{
		return mask_greater_than(lhs, rhs) != 0;
	}
	/// <summary> Performs a less-or-equal comparison of respective elements of the two passed SIMD vectors. Returns true if at least one element comparison was true. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>True if any respective-element comparison is true, otherwise false.</returns>
	[[nodiscard]] inline bool any_less_equal(__m128 lhs, __m128 rhs)
	{
		return mask_less_equal(lhs, rhs) != 0;
	}
	/// <summary> Performs a greater-or-equal comparison of respective elements of the two passed SIMD vectors. Returns true if at least one element comparison was true. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>True if any respective-element comparison is true, otherwise false.</returns>
	[[nodiscard]] inline bool any_greater_equal(__m128 lhs, __m128 rhs)
	{
		return mask_greater_equal(lhs, rhs) != 0;
	}

	/// <summary> Performs an equality comparison of respective elements of the two passed SIMD vectors and returns the number of true results. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Number of comparisons within the vectors which returned true. Any integer in the inclusve range 0-4.</returns>
	[[nodiscard]] inline std::size_t count_equal(__m128 lhs, __m128 rhs)
	{
		return EmuCore::ArithmeticHelpers::num_active_bits(mask_equal(lhs, rhs));
	}
	/// <summary> Performs an inequality comparison of respective elements of the two passed SIMD vectors and returns the number of true results. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Number of comparisons within the vectors which returned true. Any integer in the inclusve range 0-4.</returns>
	[[nodiscard]] inline std::size_t count_not_equal(__m128 lhs, __m128 rhs)
	{
		return EmuCore::ArithmeticHelpers::num_active_bits(mask_not_equal(lhs, rhs));
	}
	/// <summary> Performs a less-than comparison of respective elements of the two passed SIMD vectors and returns the number of true results. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Number of comparisons within the vectors which returned true. Any integer in the inclusve range 0-4.</returns>
	[[nodiscard]] inline std::size_t count_less_than(__m128 lhs, __m128 rhs)
	{
		return EmuCore::ArithmeticHelpers::num_active_bits(mask_less_than(lhs, rhs));
	}
	/// <summary> Performs a greater-than comparison of respective elements of the two passed SIMD vectors and returns the number of true results. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Number of comparisons within the vectors which returned true. Any integer in the inclusve range 0-4.</returns>
	[[nodiscard]] inline std::size_t count_greater_than(__m128 lhs, __m128 rhs)
	{
		return EmuCore::ArithmeticHelpers::num_active_bits(mask_greater_than(lhs, rhs));
	}
	/// <summary> Performs a less-or-equal comparison of respective elements of the two passed SIMD vectors and returns the number of true results. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Number of comparisons within the vectors which returned true. Any integer in the inclusve range 0-4.</returns>
	[[nodiscard]] inline std::size_t count_less_equal(__m128 lhs, __m128 rhs)
	{
		return EmuCore::ArithmeticHelpers::num_active_bits(mask_less_equal(lhs, rhs));
	}
	/// <summary> Performs a greater-or-equal comparison of respective elements of the two passed SIMD vectors and returns the number of true results. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Number of comparisons within the vectors which returned true. Any integer in the inclusve range 0-4.</returns>
	[[nodiscard]] inline std::size_t count_greater_equal(__m128 lhs, __m128 rhs)
	{
		return EmuCore::ArithmeticHelpers::num_active_bits(mask_greater_equal(lhs, rhs));
	}
}

#endif
