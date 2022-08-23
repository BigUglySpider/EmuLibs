#ifndef EMU_MATH_RECT_CONVERSIONS_H_INC_
#define EMU_MATH_RECT_CONVERSIONS_H_INC_ 1

#include "_common_rect_helper_includes.h"
#include "_rect_get.h"

namespace EmuMath::Helpers
{
	namespace _rect_underlying
	{
		template<std::size_t ForIndex_, std::size_t LeftIndex_, std::size_t TopIndex_, std::size_t RightIndex_, std::size_t BottomIndex_, EmuConcepts::EmuRect Rect_>
		[[nodiscard]] constexpr inline decltype(auto) _get_for_vector_index(Rect_&& rect_)
		{
			if constexpr (ForIndex_ == LeftIndex_)
			{
				using get_left_result = decltype(rect_get_left(std::forward<Rect_>(rect_)));
				return std::forward<get_left_result>(rect_get_left(std::forward<Rect_>(rect_)));
			}
			else if constexpr (ForIndex_ == TopIndex_)
			{
				using get_top_result = decltype(rect_get_top(std::forward<Rect_>(rect_)));
				return std::forward<get_top_result>(rect_get_top(std::forward<Rect_>(rect_)));
			}
			else if constexpr (ForIndex_ == RightIndex_)
			{
				using get_right_result = decltype(rect_get_right(std::forward<Rect_>(rect_)));
				return std::forward<get_right_result>(rect_get_right(std::forward<Rect_>(rect_)));
			}
			else if constexpr (ForIndex_ == BottomIndex_)
			{
				using get_bottom_result = decltype(rect_get_bottom(std::forward<Rect_>(rect_)));
				return std::forward<get_bottom_result>(rect_get_bottom(std::forward<Rect_>(rect_)));
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<ForIndex_>(),
					"Attempted to convert an EmuMath Rect to an EmuMath Vector, but input index data provided an out-of-range index."
				);
			}
		}
	}

	/// <summary>
	/// <para> Checks if the passed indices are valid for creating an EmuMath Vector from a Rect. </para>
	/// </summary>
	/// <returns>If all indices are in the inclusive range 0:3 and none are duplicated, returns `true`; otherwise returns `false`.</returns>
	template<std::size_t LeftIndex_, std::size_t TopIndex_, std::size_t RightIndex_, std::size_t BottomIndex_>
	[[nodiscard]] constexpr inline bool rect_valid_index_args_for_vector_conversion()
	{
		return
		(
			(LeftIndex_ <= 3 && TopIndex_ <= 3 && RightIndex_ <= 3 && BottomIndex_ <= 3) &&
			EmuCore::TMP::all_consts_unique<LeftIndex_, TopIndex_, RightIndex_, BottomIndex_>::value
		);
	}

	/// <summary>
	/// <para> Casts the input Rect to an EmuMath Rect of the specified type. </para>
	/// </summary>
	/// <param name="rect_">Rect to convert.</param>
	/// <returns>Converted form of the input Rect.</returns>
	template<typename OutT_, EmuConcepts::EmuRect Rect_>
	[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> rect_cast(Rect_&& rect_)
	{
		using out_value_uq = typename EmuMath::Rect<OutT_>::value_type_uq;
		using get_left_result = decltype(rect_get_left(std::forward<Rect_>(rect_)));
		using get_top_result = decltype(rect_get_top(std::forward<Rect_>(rect_)));
		using get_right_result = decltype(rect_get_right(std::forward<Rect_>(rect_)));
		using get_bottom_result = decltype(rect_get_bottom(std::forward<Rect_>(rect_)));

#pragma warning(push)
#pragma warning(disable: 26800)
		return EmuMath::Rect<OutT_>
		(
			static_cast<out_value_uq>(std::forward<get_left_result>(rect_get_left(std::forward<Rect_>(rect_)))),
			static_cast<out_value_uq>(std::forward<get_top_result>(rect_get_top(std::forward<Rect_>(rect_)))),
			static_cast<out_value_uq>(std::forward<get_right_result>(rect_get_right(std::forward<Rect_>(rect_)))),
			static_cast<out_value_uq>(std::forward<get_bottom_result>(rect_get_bottom(std::forward<Rect_>(rect_))))
		);
#pragma warning(pop)
	}

	/// <summary>
	/// <para> Casts the input Rect and assigns the results to the passed output Rect. </para>
	/// </summary>
	/// <param name="out_rect_">EmuMath Rect to assign conversion results to.</param>
	/// <param name="rect_">Rect to convert.</param>
	template<typename OutT_, EmuConcepts::EmuRect Rect_>
	[[nodiscard]] constexpr inline void rect_cast(EmuMath::Rect<OutT_>& out_rect_, Rect_&& rect_)
	{
		using out_value_uq = typename EmuMath::Rect<OutT_>::value_type_uq;
		using get_left_result = decltype(rect_get_left(std::forward<Rect_>(rect_)));
		using get_top_result = decltype(rect_get_top(std::forward<Rect_>(rect_)));
		using get_right_result = decltype(rect_get_right(std::forward<Rect_>(rect_)));
		using get_bottom_result = decltype(rect_get_bottom(std::forward<Rect_>(rect_)));

#pragma warning(push)
#pragma warning(disable: 26800)
		EmuCore::TMP::assign_direct_or_cast<out_value_uq>(rect_get_left(out_rect_), std::forward<get_left_result>(rect_get_left(std::forward<Rect_>(rect_))));
		EmuCore::TMP::assign_direct_or_cast<out_value_uq>(rect_get_top(out_rect_), std::forward<get_left_result>(rect_get_top(std::forward<Rect_>(rect_))));
		EmuCore::TMP::assign_direct_or_cast<out_value_uq>(rect_get_right(out_rect_), std::forward<get_left_result>(rect_get_right(std::forward<Rect_>(rect_))));
		EmuCore::TMP::assign_direct_or_cast<out_value_uq>(rect_get_bottom(out_rect_), std::forward<get_left_result>(rect_get_bottom(std::forward<Rect_>(rect_))));
#pragma warning(pop)
	}

	/// <summary>
	/// <para> Converts the input Rect to a 4D Vector of its 4 boundaries as specified. </para>
	/// <para> Input indices indicate which Vector index to assign the named boundary to. These may only be non-repeating values in the inclusive range 0:3. </para>
	/// <para> Input indices may be omitted, in which case they will default to 0, 1, 2, 3. </para>
	/// </summary>
	/// <param name="rect_">Rect to convert to a Vector.</param>
	/// <returns>4D EmuMath Vector containing the 4 boundaries of the input Rect in specified indices.</returns>
	template<std::size_t LeftIndex_, std::size_t TopIndex_, std::size_t RightIndex_, std::size_t BottomIndex_, typename OutT_, EmuConcepts::EmuRect Rect_>
	[[nodiscard]] constexpr inline auto rect_as_vector(Rect_&& rect_)
		-> std::enable_if_t<rect_valid_index_args_for_vector_conversion<LeftIndex_, TopIndex_, RightIndex_, BottomIndex_>(), EmuMath::Vector<4, OutT_>>
	{
#pragma warning(push)
#pragma warning(disable: 26800)
		return EmuMath::Vector<4, OutT_>
		(
			_rect_underlying::_get_for_vector_index<0, LeftIndex_, TopIndex_, RightIndex_, BottomIndex_>(std::forward<Rect_>(rect_)),
			_rect_underlying::_get_for_vector_index<1, LeftIndex_, TopIndex_, RightIndex_, BottomIndex_>(std::forward<Rect_>(rect_)),
			_rect_underlying::_get_for_vector_index<2, LeftIndex_, TopIndex_, RightIndex_, BottomIndex_>(std::forward<Rect_>(rect_)),
			_rect_underlying::_get_for_vector_index<3, LeftIndex_, TopIndex_, RightIndex_, BottomIndex_>(std::forward<Rect_>(rect_))
		);
#pragma warning(pop)
	}

	template<typename OutT_, EmuConcepts::EmuRect Rect_>
	[[nodiscard]] constexpr inline EmuMath::Vector<4, OutT_> rect_as_vector(Rect_&& rect_)
	{
		return rect_as_vector<0, 1, 2, 3>(std::forward<Rect_>(rect_));
	}
}

#endif
