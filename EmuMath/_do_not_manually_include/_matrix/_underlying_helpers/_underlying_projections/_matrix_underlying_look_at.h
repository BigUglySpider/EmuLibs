#ifndef EMU_MATH_MATRIX_UNDERLYING_LOOK_AT_H_INC_
#define EMU_MATH_MATRIX_UNDERLYING_LOOK_AT_H_INC_ 1

#include "../_matrix_tmp.h"

namespace EmuMath::Helpers::_matrix_underlying
{
#pragma region GENERATION_COMPONENTS_VK_LOOK_AT
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, EmuConcepts::EmuMatrix OutMatrix_, bool LeftHanded_, typename CalcFP_, std::size_t FromSize_, typename FromT_>
	[[nodiscard]] constexpr inline decltype(auto) _make_look_at_vk_arg_for_index
	(
		const EmuMath::Vector<3, CalcFP_>& forward_,
		const EmuMath::Vector<3, CalcFP_>& right_,
		const EmuMath::Vector<3, CalcFP_>& new_up_,
		const EmuMath::Vector<FromSize_, FromT_>& from_
	)
	{
		if constexpr (ColumnIndex_ > 3 || RowIndex_ > 3)
		{
			// All zero outside of first 4x4
			using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			return out_mat_uq::get_implied_zero();
		}
		else
		{
			if constexpr (ColumnIndex_ < 3 && RowIndex_ < 3)
			{
				// First 3x3 just uses components of right_, new_up_, forward_*, based on the column and row index
				// --- x, y, or z is decided by column index
				// --- right_, new_up_, or forward_, is decided by row index
				if constexpr (RowIndex_ == 0)
				{
					return right_.template at<ColumnIndex_>();
				}
				else if constexpr (RowIndex_ == 1)
				{
					return new_up_.template at<ColumnIndex_>();
				}
				else
				{
					// Can only be 2 in this branch
					// --- *Forward negated for right-handed coordinates
					if constexpr (LeftHanded_)
					{
						return forward_.template at<ColumnIndex_>();
					}
					else
					{
						return -(forward_.template at<ColumnIndex_>());
					}
				}
			}
			else
			{
				if constexpr (ColumnIndex_ == 3)
				{
					// Final column is negated dots for first 2 rows, dot for third row, and 1.0 for fourth row
					if constexpr (RowIndex_ == 0)
					{
						return -(right_.Dot(from_));
					}
					else if constexpr (RowIndex_ == 1)
					{
						return -(new_up_.Dot(from_));
					}
					else if constexpr (RowIndex_ == 2)
					{
						// Forward negated for left-handed coordinates only
						if constexpr (LeftHanded_)
						{
							return -(forward_.Dot(from_));
						}
						else
						{
							return forward_.Dot(from_);
						}
					}
					else if constexpr(RowIndex_ == 3)
					{
						using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
						return typename out_mat_uq::value_type(1.0);
					}
					else
					{
						// Outside 4x4 range so just 0
						using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
						return out_mat_uq::get_implied_zero();
					}
				}
				else
				{
					// Final row (but not final column) is all 0
					// --- Don't need to worry about [3, 3] being 1.0 as that index is handled above
					using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
					return out_mat_uq::get_implied_zero();
				}
			}
		}
	}

	template
	<
		EmuConcepts::EmuMatrix OutMatrix_, bool IsConstexpr_, bool LeftHanded_, std::size_t FromSize_, typename FromT_,
		std::size_t ToSize_, typename ToT_,std::size_t UpSize_, typename UpT_, std::size_t...ColumnIndices_, std::size_t...RowIndices_
	>
	[[nodiscard]] constexpr inline auto _make_look_at_vk
	(
		const EmuMath::Vector<FromSize_, FromT_>& from_,
		const EmuMath::Vector<ToSize_, ToT_>& to_,
		const EmuMath::Vector<UpSize_, UpT_>& up_,
		std::index_sequence<ColumnIndices_...> out_column_indices_,
		std::index_sequence<RowIndices_...> out_row_indices_
	)
	{
		using calc_fp = typename EmuCore::TMP::largest_floating_point
		<
			typename std::remove_cvref_t<OutMatrix_>::preferred_floating_point,
			typename EmuMath::Vector<FromSize_, FromT_>::preferred_floating_point,
			typename EmuMath::Vector<ToSize_, ToT_>::preferred_floating_point,
			typename EmuMath::Vector<UpSize_, UpT_>::preferred_floating_point,
			float
		>::type;

		if constexpr (IsConstexpr_)
		{
			auto forward = to_.template Subtract<3, calc_fp>(from_).NormaliseConstexpr();
			if constexpr (LeftHanded_)
			{
				auto right = up_.template Cross3<3, calc_fp>(forward).NormaliseConstexpr();
				auto new_up = forward.template Cross3<3, calc_fp>(right);
				return typename std::remove_cvref<OutMatrix_>::type
				(
					_make_look_at_vk_arg_for_index<ColumnIndices_, RowIndices_, typename std::remove_cvref<OutMatrix_>::type, LeftHanded_>
					(
						forward,
						right,
						new_up,
						from_
					)...
				);
			}
			else
			{
				auto right = forward.template Cross3<3, calc_fp>(up_).NormaliseConstexpr();
				auto new_up = right.template Cross3<3, calc_fp>(forward);
				return typename std::remove_cvref<OutMatrix_>::type
				(
					_make_look_at_vk_arg_for_index<ColumnIndices_, RowIndices_, typename std::remove_cvref<OutMatrix_>::type, LeftHanded_>
					(
						forward,
						right,
						new_up,
						from_
					)...
				);
			}
		}
		else
		{
			auto forward = to_.template Subtract<3, calc_fp>(from_).Normalise();
			if constexpr (LeftHanded_)
			{
				auto right = up_.template Cross3<3, calc_fp>(forward).Normalise();
				auto new_up = forward.template Cross3<3, calc_fp>(right);
				return typename std::remove_cvref<OutMatrix_>::type
				(
					_make_look_at_vk_arg_for_index<ColumnIndices_, RowIndices_, typename std::remove_cvref<OutMatrix_>::type, LeftHanded_>
					(
						forward,
						right,
						new_up,
						from_
					)...
				);
			}
			else
			{
				auto right = forward.template Cross3<3, calc_fp>(up_).Normalise();
				auto new_up = right.template Cross3<3, calc_fp>(forward);
				return typename std::remove_cvref<OutMatrix_>::type
				(
					_make_look_at_vk_arg_for_index<ColumnIndices_, RowIndices_, typename std::remove_cvref<OutMatrix_>::type, LeftHanded_>
					(
						forward,
						right,
						new_up,
						from_
					)...
				);
			}
		}
	}

	template<EmuConcepts::EmuMatrix OutMatrix_, bool IsConstexpr_, bool LeftHanded_, std::size_t FromSize_, typename FromT_, std::size_t ToSize_, typename ToT_,std::size_t UpSize_, typename UpT_>
	[[nodiscard]] constexpr inline auto _make_look_at_vk
	(
		const EmuMath::Vector<FromSize_, FromT_>& from_,
		const EmuMath::Vector<ToSize_, ToT_>& to_,
		const EmuMath::Vector<UpSize_, UpT_>& up_
	)
	{
		using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<typename std::remove_cvref<OutMatrix_>::type>;
		using out_column_indices = typename out_indices::column_index_sequence;
		using out_row_indices = typename out_indices::row_index_sequence;
		return _make_look_at_vk<typename std::remove_cvref<OutMatrix_>::type, IsConstexpr_, LeftHanded_>
		(
			from_,
			to_,
			up_,
			out_column_indices(),
			out_row_indices()
		);
	}
#pragma endregion
}

#endif
