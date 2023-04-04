#ifndef EMU_MATH_MATRIX_UNDERLYING_ROTATE_3D_H_INC_
#define EMU_MATH_MATRIX_UNDERLYING_ROTATE_3D_H_INC_ 1

#include "../_matrix_tmp.h"
#include "../../../../Quaternion.h"

namespace EmuMath::Helpers::_matrix_underlying
{
#pragma region GETS
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class OutMatrix_, typename SinAndCos_>
	[[nodiscard]] constexpr inline decltype(auto) _matrix_rotate_3_x_get_for_index(const SinAndCos_& sin_, const SinAndCos_& cos_)
	{
		using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		if constexpr(ColumnIndex_ == 1)
		{
			// c1r1 = cos, c1r2 = sin, remainder of c1 = 0
			if constexpr (RowIndex_ == 1)
			{
				return EmuCore::TMP::construct_or_cast<typename out_mat_uq::value_type_uq>(cos_);
			}
			else if constexpr (RowIndex_ == 2)
			{
				return EmuCore::TMP::construct_or_cast<typename out_mat_uq::value_type_uq>(sin_);
			}
			else
			{
				return out_mat_uq::get_implied_zero();
			}
		}
		else if constexpr(ColumnIndex_ == 2)
		{
			// c2r1 = -sin, c2r2 = cos, remainder of c2 = 0
			if constexpr (RowIndex_ == 1)
			{
				using sin_and_cos_uq = typename EmuCore::TMP::remove_ref_cv<SinAndCos_>::type;
				return EmuCore::TMP::construct_or_cast<typename out_mat_uq::value_type_uq>(EmuCore::do_negate<sin_and_cos_uq>()(sin_));
			}
			else if constexpr (RowIndex_ == 2)
			{
				return EmuCore::TMP::construct_or_cast<typename out_mat_uq::value_type_uq>(cos_);
			}
			else
			{
				return out_mat_uq::get_implied_zero();
			}
		}
		else
		{
			// Set remaining main diagonal to 1, and others to 0
			if constexpr (ColumnIndex_ == RowIndex_)
			{
				return EmuCore::TMP::construct_or_cast<typename out_mat_uq::value_type_uq>(1);
			}
			else
			{
				return out_mat_uq::get_implied_zero();
			}
		}
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class OutMatrix_, typename SinAndCos_>
	[[nodiscard]] constexpr inline decltype(auto) _matrix_rotate_3_y_get_for_index(const SinAndCos_& sin_, const SinAndCos_& cos_)
	{
		using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		if constexpr (ColumnIndex_ == 0)
		{
			// c0r0 = cos, c0r2 = -sin, remainder of c0 = 0
			if constexpr (RowIndex_ == 0)
			{
				return EmuCore::TMP::construct_or_cast<typename out_mat_uq::value_type_uq>(cos_);
			}
			else if constexpr (RowIndex_ == 2)
			{
				using sin_and_cos_uq = typename EmuCore::TMP::remove_ref_cv<SinAndCos_>::type;
				return EmuCore::TMP::construct_or_cast<typename out_mat_uq::value_type_uq>(EmuCore::do_negate<sin_and_cos_uq>()(sin_));
			}
			else
			{
				return out_mat_uq::get_implied_zero();
			}
		}
		else if constexpr (ColumnIndex_ == 2)
		{
			// c2r0 = sin, c2r2 = cos, remainder of c2 = 0
			if constexpr (RowIndex_ == 0)
			{
				return EmuCore::TMP::construct_or_cast<typename out_mat_uq::value_type_uq>(sin_);
			}
			else if constexpr (RowIndex_ == 2)
			{
				return EmuCore::TMP::construct_or_cast<typename out_mat_uq::value_type_uq>(cos_);
			}
			else
			{
				return out_mat_uq::get_implied_zero();
			}
		}
		else
		{
			// Set remaining main diagonal to 1, and others to 0
			if constexpr (ColumnIndex_ == RowIndex_)
			{
				return EmuCore::TMP::construct_or_cast<typename out_mat_uq::value_type_uq>(1);
			}
			else
			{
				return out_mat_uq::get_implied_zero();
			}
		}
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class OutMatrix_, typename SinAndCos_>
	[[nodiscard]] constexpr inline decltype(auto) _matrix_rotate_3_z_get_for_index(const SinAndCos_& sin_, const SinAndCos_& cos_)
	{
		using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		if constexpr (ColumnIndex_ == 0)
		{
			// c0r0 = cos, c0r1 = sin, remainder of c0 = 0
			if constexpr (RowIndex_ == 0)
			{
				return EmuCore::TMP::construct_or_cast<typename out_mat_uq::value_type_uq>(cos_);
			}
			else if constexpr (RowIndex_ == 1)
			{
				return EmuCore::TMP::construct_or_cast<typename out_mat_uq::value_type_uq>(sin_);
			}
			else
			{
				return out_mat_uq::get_implied_zero();
			}
		}
		else if constexpr (ColumnIndex_ == 1)
		{
			// c1r0 = -sin, c1r1 = cos, remainder of c1 = 0
			if constexpr (RowIndex_ == 0)
			{
				using sin_and_cos_uq = typename EmuCore::TMP::remove_ref_cv<SinAndCos_>::type;
				return EmuCore::TMP::construct_or_cast<typename out_mat_uq::value_type_uq>(EmuCore::do_negate<sin_and_cos_uq>()(sin_));
			}
			else if constexpr (RowIndex_ == 1)
			{
				return EmuCore::TMP::construct_or_cast<typename out_mat_uq::value_type_uq>(cos_);
			}
			else
			{
				return out_mat_uq::get_implied_zero();
			}
		}
		else
		{
			// Set remaining main diagonal to 1, and others to 0
			if constexpr (ColumnIndex_ == RowIndex_)
			{
				return EmuCore::TMP::construct_or_cast<typename out_mat_uq::value_type_uq>(1);
			}
			else
			{
				return out_mat_uq::get_implied_zero();
			}
		}
	}
#pragma endregion

#pragma region VALIDITY_CHECKS
	template<class OutMatrix_, class SinAndCos_, bool Assigning_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	[[nodiscard]] constexpr inline bool _matrix_rotate_3_x_is_valid(std::index_sequence<ColumnIndices_...> column_indices_, std::index_sequence<RowIndices_...> row_indices_)
	{
		if constexpr (Assigning_)
		{
			using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			using out_value_uq = typename out_mat_uq::value_type_uq;
			// 6287 silenced here as there is a warning for function calls due to potential side-effects
			// --- In this context, side-effects are not expected. If there are any, it will be due to an ill-formed specialisation
EMU_CORE_MSVC_PUSH_WARNING_STACK
EMU_CORE_MSVC_DISABLE_WARNING(6287)
			return
			(
				... &&
				EmuCore::TMP::valid_assign_direct_or_cast
				<
					out_value_uq,
					decltype(_matrix_rotate_3_x_get_for_index<ColumnIndices_, RowIndices_, OutMatrix_>(std::declval<SinAndCos_>(), std::declval<SinAndCos_>())),
					decltype(std::declval<OutMatrix_>().template at<ColumnIndices_, RowIndices_>())
				>()
			);
EMU_CORE_MSVC_POP_WARNING_STACK
		}
		else
		{
			return std::is_constructible_v
			<
				OutMatrix_,
				decltype(_matrix_rotate_3_x_get_for_index<ColumnIndices_, RowIndices_, OutMatrix_>(std::declval<SinAndCos_>(), std::declval<SinAndCos_>()))...
			>;
		}
	}

	template<class OutMatrix_, class SinAndCos_, bool Assigning_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	[[nodiscard]] constexpr inline bool _matrix_rotate_3_y_is_valid(std::index_sequence<ColumnIndices_...> column_indices_, std::index_sequence<RowIndices_...> row_indices_)
	{
		if constexpr (Assigning_)
		{
			using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			using out_value_uq = typename out_mat_uq::value_type_uq;
			// 6287 silenced here as there is a warning for function calls due to potential side-effects
			// --- In this context, side-effects are not expected. If there are any, it will be due to an ill-formed specialisation
EMU_CORE_MSVC_PUSH_WARNING_STACK
EMU_CORE_MSVC_DISABLE_WARNING(6287)
			return
			(
				... &&
				EmuCore::TMP::valid_assign_direct_or_cast
				<
					out_value_uq,
					decltype(_matrix_rotate_3_y_get_for_index<ColumnIndices_, RowIndices_, OutMatrix_>(std::declval<SinAndCos_>(), std::declval<SinAndCos_>())),
					decltype(std::declval<OutMatrix_>().template at<ColumnIndices_, RowIndices_>())
				>()
			);
EMU_CORE_MSVC_POP_WARNING_STACK
		}
		else
		{
			return std::is_constructible_v
			<
				OutMatrix_,
				decltype(_matrix_rotate_3_y_get_for_index<ColumnIndices_, RowIndices_, OutMatrix_>(std::declval<SinAndCos_>(), std::declval<SinAndCos_>()))...
			>;
		}
	}

	template<class OutMatrix_, class SinAndCos_, bool Assigning_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	[[nodiscard]] constexpr inline bool _matrix_rotate_3_z_is_valid(std::index_sequence<ColumnIndices_...> column_indices_, std::index_sequence<RowIndices_...> row_indices_)
	{
		if constexpr (Assigning_)
		{
			using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			using out_value_uq = typename out_mat_uq::value_type_uq;
			// 6287 silenced here as there is a warning for function calls due to potential side-effects
			// --- In this context, side-effects are not expected. If there are any, it will be due to an ill-formed specialisation
EMU_CORE_MSVC_PUSH_WARNING_STACK
EMU_CORE_MSVC_DISABLE_WARNING(6287)
			return
			(
				... &&
				EmuCore::TMP::valid_assign_direct_or_cast
				<
					out_value_uq,
					decltype(_matrix_rotate_3_z_get_for_index<ColumnIndices_, RowIndices_, OutMatrix_>(std::declval<SinAndCos_>(), std::declval<SinAndCos_>())),
					decltype(std::declval<OutMatrix_>().template at<ColumnIndices_, RowIndices_>())
				>()
			);
EMU_CORE_MSVC_POP_WARNING_STACK
		}
		else
		{
			return std::is_constructible_v
			<
				OutMatrix_,
				decltype(_matrix_rotate_3_z_get_for_index<ColumnIndices_, RowIndices_, OutMatrix_>(std::declval<SinAndCos_>(), std::declval<SinAndCos_>()))...
			>;
		}
	}

	template<class OutMatrix_, class SinAndCos_, bool Assigning_, std::size_t AxisIndex_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _matrix_rotate_3_valid_for_axis()
	{
		using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type>;
		using column_indices = typename out_indices::column_index_sequence;
		using row_indices = typename out_indices::row_index_sequence;
		if constexpr (AxisIndex_ == 0)
		{
			if constexpr (_matrix_rotate_3_x_is_valid<OutMatrix_, SinAndCos_, Assigning_>(column_indices(), row_indices()))
			{
				return true;
			}
			else
			{
				if constexpr (Assigning_)
				{
					static_assert(!StaticAssert_, "Invalid Matrix rotation (X) arguments provided for the desired OutMatrix_, as not all indices can be successfully assigned.");
				}
				else
				{
					static_assert(!StaticAssert_, "Invalid Matrix rotation (X) arguments provided for the desired OutMatrix_, as not all elements can be successfully constructed.");
				}
				return false;
			}
		}
		else if constexpr (AxisIndex_ == 1)
		{
			if constexpr (_matrix_rotate_3_y_is_valid<OutMatrix_, SinAndCos_, Assigning_>(column_indices(), row_indices()))
			{
				return true;
			}
			else
			{
				if constexpr (Assigning_)
				{
					static_assert(!StaticAssert_, "Invalid Matrix rotation (Y) arguments provided for the desired OutMatrix_, as not all indices can be successfully assigned.");
				}
				else
				{
					static_assert(!StaticAssert_, "Invalid Matrix rotation (Y) arguments provided for the desired OutMatrix_, as not all elements can be successfully constructed.");
				}
				return false;
			}
		}
		else if constexpr (AxisIndex_ == 2)
		{
			if constexpr (_matrix_rotate_3_z_is_valid<OutMatrix_, SinAndCos_, Assigning_>(column_indices(), row_indices()))
			{
				return true;
			}
			else
			{
				if constexpr (Assigning_)
				{
					static_assert(!StaticAssert_, "Invalid Matrix rotation (Z) arguments provided for the desired OutMatrix_, as not all indices can be successfully assigned.");
				}
				else
				{
					static_assert(!StaticAssert_, "Invalid Matrix rotation (Z) arguments provided for the desired OutMatrix_, as not all elements can be successfully constructed.");
				}
				return false;
			}
		}
		else
		{
			static_assert(!StaticAssert_, "Invalid Matrix rotation validity check: Invalid AxisIndex_. Valid AxisIndex_ arguments are 0, 1, and 2, for the x-, y-, and z-axes respectively.");
			return false;
		}
	}

	template<class OutMatrix_, class Angle_, bool Assigning_, bool IsRads_, std::size_t AxisIndex_, std::size_t ConstexprIterations_, bool ConstexprMod_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _matrix_rotate_3_is_valid()
	{
		using angle_uq = typename EmuCore::TMP::remove_ref_cv<Angle_>::type;
		using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;

		constexpr bool angle_is_fp = std::is_floating_point_v<angle_uq>;
		using angle_fp = typename std::conditional<angle_is_fp, angle_uq, typename out_mat_uq::preferred_floating_point>::type;
		constexpr bool can_convert_type_if_needed = angle_is_fp || EmuCore::TMP::is_static_castable_v<decltype(std::forward<Angle_>(std::declval<Angle_>())), angle_fp>;
		if constexpr (!can_convert_type_if_needed)
		{
			static_assert(!StaticAssert_, "Invalid Matrix rotation arguments provided, preventing a successful conversion from the provided angle argument to a usable floating-point alternative for the output Matrix type.");
			return false;
		}
		else
		{
			constexpr bool can_convert_to_rads_if_needed = IsRads_ || std::is_invocable_r_v<angle_fp, decltype(EmuCore::Pi::DegsToRads<angle_fp>), angle_fp>;
			if constexpr (!can_convert_to_rads_if_needed)
			{
				static_assert(!StaticAssert_, "Invalid Matrix rotation arguments provided with input of degrees, as a successful conversion from degrees to radians cannot be performed.");
				return false;
			}
			else
			{
				constexpr bool is_constexpr = ConstexprIterations_ > 0;
				using cos_func = typename std::conditional<is_constexpr, EmuCore::do_cos_constexpr<angle_fp, ConstexprIterations_, ConstexprMod_>, EmuCore::do_cos<angle_fp>>::type;
				using sin_func = typename std::conditional<is_constexpr, EmuCore::do_sin_constexpr<angle_fp, ConstexprIterations_, ConstexprMod_>, EmuCore::do_sin<angle_fp>>::type;
				constexpr bool cos_valid = std::is_invocable_r_v<angle_fp, cos_func, angle_fp>;
				constexpr bool sin_valid = std::is_invocable_r_v<angle_fp, cos_func, angle_fp>;

				if constexpr (!(cos_valid && sin_valid))
				{
					static_assert(!StaticAssert_, "Invalid Matrix rotation arguments provided, preventing a valid instantiation of the cos and/or sin calculation functor(s).");
					return false;
				}
				else
				{
					return _matrix_rotate_3_valid_for_axis<OutMatrix_, angle_fp, Assigning_, AxisIndex_, StaticAssert_>();
				}
			}
		}
	}
#pragma endregion

#pragma region MAKERS
	template<class OutMatrix_, class SinAndCos_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_make_rotate_3_x
	(
		const SinAndCos_& sin_,
		const SinAndCos_& cos_,
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_
	)
	{
		if constexpr (_matrix_rotate_3_x_is_valid<OutMatrix_, SinAndCos_, false>(std::index_sequence<ColumnIndices_...>(), std::index_sequence<RowIndices_...>()))
		{
			return OutMatrix_
			(
				_matrix_rotate_3_x_get_for_index<ColumnIndices_, RowIndices_, OutMatrix_>(sin_, cos_)...
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutMatrix_>(),
				"Attempted to make an EmuMath rotation Matrix about the x-axis, but the output Matrix could not be constructed."
			);
		}
	}
	
	template<class OutMatrix_, class SinAndCos_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_make_rotate_3_y
	(
		const SinAndCos_& sin_,
		const SinAndCos_& cos_,
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_
	)
	{
		if constexpr (_matrix_rotate_3_y_is_valid<OutMatrix_, SinAndCos_, false>(std::index_sequence<ColumnIndices_...>(), std::index_sequence<RowIndices_...>()))
		{
			return OutMatrix_
			(
				_matrix_rotate_3_y_get_for_index<ColumnIndices_, RowIndices_, OutMatrix_>(sin_, cos_)...
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutMatrix_>(),
				"Attempted to make an EmuMath rotation Matrix about the y-axis, but the output Matrix could not be constructed."
			);
		}
	}
	
	template<class OutMatrix_, class SinAndCos_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_make_rotate_3_z
	(
		const SinAndCos_& sin_,
		const SinAndCos_& cos_,
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_
	)
	{
		if constexpr (_matrix_rotate_3_z_is_valid<OutMatrix_, SinAndCos_, false>(std::index_sequence<ColumnIndices_...>(), std::index_sequence<RowIndices_...>()))
		{
			return OutMatrix_
			(
				_matrix_rotate_3_z_get_for_index<ColumnIndices_, RowIndices_, OutMatrix_>(sin_, cos_)...
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutMatrix_>(),
				"Attempted to make an EmuMath rotation Matrix about the z-axis, but the output Matrix could not be constructed."
			);
		}
	}

	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		bool IsRads_, std::size_t AxisIndex_, std::size_t ConstexprIterations_, bool ConstexprMod_, bool StaticAssert_, class Angle_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> _matrix_make_rotate_3_in_axis(Angle_&& angle_)
	{
		using out_matrix = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>;
		if constexpr (_matrix_rotate_3_is_valid<out_matrix, Angle_, false, IsRads_, AxisIndex_, ConstexprIterations_, ConstexprMod_, true>())
		{
			using angle_uq = typename EmuCore::TMP::remove_ref_cv<Angle_>::type;

			// Get correct fp type for angle
			constexpr bool angle_is_fp = std::is_floating_point_v<angle_uq>;
			using angle_fp = typename std::conditional<angle_is_fp, angle_uq, typename out_matrix::preferred_floating_point>::type;
			angle_fp angle_as_fp = static_cast<angle_fp>(std::forward<Angle_>(angle_));

			// Convert to radians if needed
			if constexpr (!IsRads_)
			{
				angle_as_fp = EmuCore::Pi::DegsToRads(angle_as_fp);
			}

			// Select trig funcs
			constexpr bool is_constexpr = ConstexprIterations_ > 0;
			using cos_func = typename std::conditional<is_constexpr, EmuCore::do_cos_constexpr<angle_fp, ConstexprIterations_, ConstexprMod_>, EmuCore::do_cos<angle_fp>>::type;
			using sin_func = typename std::conditional<is_constexpr, EmuCore::do_sin_constexpr<angle_fp, ConstexprIterations_, ConstexprMod_>, EmuCore::do_sin<angle_fp>>::type;
			
			// Execute correct maker for axis
			using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<typename EmuCore::TMP::remove_ref_cv<out_matrix>::type>;
			using column_indices = typename out_indices::column_index_sequence;
			using row_indices = typename out_indices::row_index_sequence;
			if constexpr (AxisIndex_ == 0)
			{
				return _matrix_make_rotate_3_x<out_matrix>(sin_func()(angle_as_fp), cos_func()(angle_as_fp), column_indices(), row_indices());
			}
			else if constexpr (AxisIndex_ == 1)
			{
				return _matrix_make_rotate_3_y<out_matrix>(sin_func()(angle_as_fp), cos_func()(angle_as_fp), column_indices(), row_indices());
			}
			else if constexpr (AxisIndex_ == 2)
			{
				return _matrix_make_rotate_3_z<out_matrix>(sin_func()(angle_as_fp), cos_func()(angle_as_fp), column_indices(), row_indices());
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<AxisIndex_>(),
					"Attempted to create an EmuMath 3D rotation Matrix, but the provided AxisIndex_ is not a valid axis. Only 0, 1, 2 are valid indices, for the x-, y-, and z-axes respectively."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<out_matrix>(),
				"Attempted to create an EmuMath 3D rotation Matrix, but at least one step could not be performed. See other static assertion messages for more information."
			);
		}
	}
#pragma endregion

#pragma region ASSIGNERS
	template<class OutMatrix_, class SinAndCos_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	constexpr inline void _matrix_assign_rotate_3_x
	(
		OutMatrix_& out_matrix_,
		const SinAndCos_& sin_,
		const SinAndCos_& cos_,
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_
	)
	{
		if constexpr (_matrix_rotate_3_x_is_valid<OutMatrix_, SinAndCos_, true>(std::index_sequence<ColumnIndices_...>(), std::index_sequence<RowIndices_...>()))
		{
			using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			using out_value_uq = typename out_mat_uq::value_type_uq;
			(
				(
					EmuCore::TMP::assign_direct_or_cast<out_value_uq>
					(
						out_matrix_.template at<ColumnIndices_, RowIndices_>(),
						_matrix_rotate_3_x_get_for_index<ColumnIndices_, RowIndices_, OutMatrix_>(sin_, cos_)
					)
				), ...
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutMatrix_>(),
				"Attempted to assign a rotation Matrix about the x-axis to an existing EmuMath Matrix, but at least one index of the output Matrix could not successfully be assigned."
			);
		}
	}

	template<class OutMatrix_, class SinAndCos_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	constexpr inline void _matrix_assign_rotate_3_y
	(
		OutMatrix_& out_matrix_,
		const SinAndCos_& sin_,
		const SinAndCos_& cos_,
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_
	)
	{
		if constexpr (_matrix_rotate_3_y_is_valid<OutMatrix_, SinAndCos_, true>(std::index_sequence<ColumnIndices_...>(), std::index_sequence<RowIndices_...>()))
		{
			using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			using out_value_uq = typename out_mat_uq::value_type_uq;
			(
				(
					EmuCore::TMP::assign_direct_or_cast<out_value_uq>
					(
						out_matrix_.template at<ColumnIndices_, RowIndices_>(),
						_matrix_rotate_3_y_get_for_index<ColumnIndices_, RowIndices_, OutMatrix_>(sin_, cos_)
					)
				), ...
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutMatrix_>(),
				"Attempted to assign a rotation Matrix about the y-axis to an existing EmuMath Matrix, but at least one index of the output Matrix could not successfully be assigned."
			);
		}
	}

	template<class OutMatrix_, class SinAndCos_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	constexpr inline void _matrix_assign_rotate_3_z
	(
		OutMatrix_& out_matrix_,
		const SinAndCos_& sin_,
		const SinAndCos_& cos_,
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_
	)
	{
		if constexpr (_matrix_rotate_3_z_is_valid<OutMatrix_, SinAndCos_, true>(std::index_sequence<ColumnIndices_...>(), std::index_sequence<RowIndices_...>()))
		{
			using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			using out_value_uq = typename out_mat_uq::value_type_uq;
			(
				(
					EmuCore::TMP::assign_direct_or_cast<out_value_uq>
					(
						out_matrix_.template at<ColumnIndices_, RowIndices_>(),
						_matrix_rotate_3_z_get_for_index<ColumnIndices_, RowIndices_, OutMatrix_>(sin_, cos_)
					)
				), ...
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutMatrix_>(),
				"Attempted to assign a rotation Matrix about the z-axis to an existing EmuMath Matrix, but at least one index of the output Matrix could not successfully be assigned."
			);
		}
	}

	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		bool IsRads_, std::size_t AxisIndex_, std::size_t ConstexprIterations_, bool ConstexprMod_, bool StaticAssert_, class Angle_
	>
	constexpr inline void _matrix_assign_rotate_3_in_axis(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Angle_&& angle_)
	{
		using out_matrix = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>&;
		using out_matrix_uq = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>;
		if constexpr (_matrix_rotate_3_is_valid<out_matrix, Angle_, true, IsRads_, AxisIndex_, ConstexprIterations_, ConstexprMod_, true>())
		{
			using angle_uq = typename EmuCore::TMP::remove_ref_cv<Angle_>::type;

			// Get correct fp type for angle
			constexpr bool angle_is_fp = std::is_floating_point_v<angle_uq>;
			using angle_fp = typename std::conditional<angle_is_fp, angle_uq, typename out_matrix_uq::preferred_floating_point>::type;
			angle_fp angle_as_fp = static_cast<angle_fp>(std::forward<Angle_>(angle_));

			// Convert to radians if needed
			if constexpr (!IsRads_)
			{
				angle_as_fp = EmuCore::Pi::DegsToRads(angle_as_fp);
			}

			// Select trig funcs
			constexpr bool is_constexpr = ConstexprIterations_ > 0;
			using cos_func = typename std::conditional<is_constexpr, EmuCore::do_cos_constexpr<angle_fp, ConstexprIterations_, ConstexprMod_>, EmuCore::do_cos<angle_fp>>::type;
			using sin_func = typename std::conditional<is_constexpr, EmuCore::do_sin_constexpr<angle_fp, ConstexprIterations_, ConstexprMod_>, EmuCore::do_sin<angle_fp>>::type;
			
			// Execute correct maker for axis
			using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<out_matrix_uq>;
			using column_indices = typename out_indices::column_index_sequence;
			using row_indices = typename out_indices::row_index_sequence;
			if constexpr (AxisIndex_ == 0)
			{
				_matrix_assign_rotate_3_x<out_matrix>(out_matrix_, sin_func()(angle_as_fp), cos_func()(angle_as_fp), column_indices(), row_indices());
			}
			else if constexpr (AxisIndex_ == 1)
			{
				_matrix_assign_rotate_3_y<out_matrix>(out_matrix_, sin_func()(angle_as_fp), cos_func()(angle_as_fp), column_indices(), row_indices());
			}
			else if constexpr (AxisIndex_ == 2)
			{
				_matrix_assign_rotate_3_z<out_matrix>(out_matrix_, sin_func()(angle_as_fp), cos_func()(angle_as_fp), column_indices(), row_indices());
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<AxisIndex_>(),
					"Attempted to assign a 3D rotation Matrix to an existing EmuMath Matrix, but the provided AxisIndex_ is not a valid axis. Only 0, 1, 2 are valid indices, for the x-, y-, and z-axes respectively."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<out_matrix>(),
				"Attempted to assign a 3D rotation Matrix to an existing EmuMath Matrix, but at least one step could not be performed. See other static assertion messages for more information."
			);
		}
	}
#pragma endregion

#pragma region QUATERNION_GETTERS
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class OutMatrixUQ_, typename CalcFP_>
	[[nodiscard]] constexpr inline decltype(auto) _matrix_rotate_3_from_quaternion_get_arg(CalcFP_* p_results_3x3_column_major_)
	{
		// Indices [0:2, 0:2] are all formed in the created 3x3 "matrix", so always move from there first
		if constexpr (ColumnIndex_ <= 2 && RowIndex_ <= 2)
		{
			constexpr std::size_t index = (ColumnIndex_ * 3) + RowIndex_;
			return std::move(p_results_3x3_column_major_[index]);
		}
		else if constexpr (ColumnIndex_ == RowIndex_)
		{
			return EmuCore::TMP::construct_or_cast<typename OutMatrixUQ_::value_type_uq>(1);
		}
		else
		{
			return OutMatrixUQ_::get_implied_zero();
		}
	}
#pragma endregion

#pragma region QUATERNION_VALIDITY_CHECKS
	template<typename OutMatrix_, typename CalcFP_, bool StaticAssert_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	[[nodiscard]] constexpr inline bool _matrix_can_finalise_construction_from_quaternions
	(
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_
	)
	{
		using mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		constexpr bool is_valid = std::is_constructible_v
		<
			OutMatrix_,
			typename EmuCore::TMP::forward_result
			<
				decltype(_matrix_rotate_3_from_quaternion_get_arg<ColumnIndices_, RowIndices_, mat_uq, CalcFP_>(std::declval<CalcFP_*>()))
			>::type...
		>;
		if constexpr (is_valid)
		{
			return true;
		}
		else
		{
			static_assert(!StaticAssert_, "Unable to construct an EmuMath 3D rotation transformation Matrix from Quaternions via the results of the conversion and/or 1s and/or 0s in relevant indices. The results of conversion are moved values of the determined calculation type for conversion, which is typically the largest `preferred_floating_point` of input/output items.");
			return false;
		}
	}

	template<class OutMatrix_, typename QuaternionT_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _matrix_can_calculate_quaternion_conversion()
	{
		using mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		using mat_fp = typename mat_uq::preferred_floating_point;
		using quat_fp = typename EmuMath::Quaternion<QuaternionT_>::preferred_floating_point;
		using quat_ref = const EmuMath::Quaternion<QuaternionT_>&;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<mat_fp, quat_fp>::type;

		if constexpr (!EmuCore::TMP::is_static_castable_v<calc_fp, decltype(std::declval<quat_ref>().X())>)
		{
			static_assert(!StaticAssert_, "Unable to perform an EmuMath Quaternion -> Matrix conversion as the imaginary X component of the Quaternion cannot be converted to the determined calculation type.");
			return false;
		}
		else if constexpr (!EmuCore::TMP::is_static_castable_v<calc_fp, decltype(std::declval<quat_ref>().Y())>)
		{
			static_assert(!StaticAssert_, "Unable to perform an EmuMath Quaternion -> Matrix conversion as the imaginary Y component of the Quaternion cannot be converted to the determined calculation type.");
			return false;
		}
		else if constexpr (!EmuCore::TMP::is_static_castable_v<calc_fp, decltype(std::declval<quat_ref>().Z())>)
		{
			static_assert(!StaticAssert_, "Unable to perform an EmuMath Quaternion -> Matrix conversion as the imaginary Z component of the Quaternion cannot be converted to the determined calculation type.");
			return false;
		}
		else if constexpr (!EmuCore::TMP::is_static_castable_v<calc_fp, decltype(std::declval<quat_ref>().W())>)
		{
			static_assert(!StaticAssert_, "Unable to perform an EmuMath Quaternion -> Matrix conversion as the real W component of the Quaternion cannot be converted to the determined calculation type.");
			return false;
		}
		else
		{
			using add_func = EmuCore::do_add<calc_fp, calc_fp>;
			using sub_func = EmuCore::do_subtract<calc_fp, calc_fp>;
			using mul_func = EmuCore::do_multiply<calc_fp, calc_fp>;
			if constexpr (!std::is_invocable_r_v<calc_fp, add_func, calc_fp, calc_fp>)
			{
				static_assert(!StaticAssert_, "Unable to perform an EmuMath Quaternion -> Matrix conversion as the determined addition function cannot be invoked with two arguments of the determined calculation type to result in a returned result of the same type.");
				return false;
			}
			else if constexpr (!std::is_invocable_r_v<calc_fp, sub_func, calc_fp, calc_fp>)
			{
				static_assert(!StaticAssert_, "Unable to perform an EmuMath Quaternion -> Matrix conversion as the determined subtraction function cannot be invoked with two arguments of the determined calculation type to result in a returned result of the same type.");
				return false;
			}
			else if constexpr (!std::is_invocable_r_v<calc_fp, mul_func, calc_fp, calc_fp>)
			{
				static_assert(!StaticAssert_, "Unable to perform an EmuMath Quaternion -> Matrix conversion as the determined multiplication function cannot be invoked with two arguments of the determined calculation type to result in a returned result of the same type.");
				return false;
			}
			else
			{
				return true;
			}
		}
	}

	// Takes `SecondQuaternionT_` as a type argument, with intention of only taking `OtherQuaternionTs_...` at said argument point so that it can be skipped
	// This is a component of `_matrix_can_make_from_quaternions`, and calling it directly from anywhere else is invalid
	template<bool StaticAssert_, bool Fused_, class OutMatrix_, typename CalcFP_, typename SecondQuaternionT_, typename...QuaternionTs_>
	[[nodiscard]] constexpr inline bool _matrix_can_combine_quaternions_after_initial_multiply()
	{
		if constexpr (sizeof...(QuaternionTs_) != 0)
		{
			if constexpr (Fused_)
			{
				if constexpr (!(... && EmuMath::Helpers::quaternion_can_fused_quaternion_multiply_assign<CalcFP_, QuaternionTs_, StaticAssert_>()))
				{
					static_assert(!StaticAssert_, "Unable to sequence multiple Quaternions (WITH fused operations) to form a single 3D rotation Matrix as a fused multiply assign operation cannot be performed with a left-hand Quaternion of the determined calculation type and at least one of the Quaternions after the first two passed Quaternions.");
					return false;
				}
				else
				{
					return true;
				}
			}
			else
			{
				if constexpr (!(... && EmuMath::Helpers::quaternion_can_quaternion_multiply_assign<CalcFP_, QuaternionTs_, StaticAssert_>()))
				{
					static_assert(!StaticAssert_, "Unable to sequence multiple Quaternions (WITHOUT fused operations) to form a single 3D rotation Matrix as a multiply assign operation cannot be performed with a left-hand Quaternion of the determined calculation type and at least one of the Quaternions after the first two passed Quaternions.");
					return false;
				}
				else
				{
					return true;
				}
			}
		}
		else
		{
			return true; // No args after initial, so return true as we wouldn't reach this point otherwise
		}
	}

	template<bool StaticAssert_, bool Fused_, class OutMatrix_, typename FirstQuaternionT_, typename...OtherQuaternionTs_>
	[[nodiscard]] constexpr inline bool _matrix_can_make_from_quaternions()
	{
		constexpr std::size_t num_other_quaternions = sizeof...(OtherQuaternionTs_);
		if constexpr (num_other_quaternions == 0)
		{
			// Static asserts in this area already handled
			if constexpr (!_matrix_can_calculate_quaternion_conversion<OutMatrix_, FirstQuaternionT_, StaticAssert_>())
			{
				return false;
			}
			else
			{
				using mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
				using mat_fp = typename mat_uq::preferred_floating_point;
				using quat_fp = typename EmuMath::Quaternion<FirstQuaternionT_>::preferred_floating_point;
				using calc_fp = typename EmuCore::TMP::largest_floating_point<mat_fp, quat_fp>::type;

				using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type>;
				using column_indices = typename out_indices::column_index_sequence;
				using row_indices = typename out_indices::row_index_sequence;
				return _matrix_can_finalise_construction_from_quaternions<OutMatrix_, calc_fp, StaticAssert_>(column_indices(), row_indices());
			}
		}
		else
		{
			using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			using calc_fp = typename EmuCore::TMP::largest_floating_point
			<
				typename out_mat_uq::preferred_floating_point,
				typename EmuMath::Quaternion<FirstQuaternionT_>::preferred_floating_point,
				typename EmuMath::Quaternion<OtherQuaternionTs_>::preferred_floating_point...
			>::type;
			using second_quat_typearg = typename EmuCore::TMP::first_variadic_arg<OtherQuaternionTs_...>::type;

			if constexpr (Fused_)
			{
				if constexpr (!EmuMath::Helpers::quaternion_can_fused_quaternion_multiply<FirstQuaternionT_, second_quat_typearg, calc_fp, StaticAssert_>())
				{
					static_assert(!StaticAssert_, "Unable to sequence multiple Quaternions (WITH fused operations) to form a single 3D rotation Matrix as a fused multiply operation cannot be formed with the first two passed Quaternion types with an output Quaternion type containing the determined calculation type.");
					return false;
				}
				else
				{
					if constexpr (_matrix_can_combine_quaternions_after_initial_multiply<StaticAssert_, Fused_, OutMatrix_, calc_fp, OtherQuaternionTs_...>())
					{
						return _matrix_can_make_from_quaternions<StaticAssert_, Fused_, OutMatrix_, calc_fp>();
					}
					else
					{
						return false;
					}
				}
			}
			else
			{
				if constexpr (!EmuMath::Helpers::quaternion_can_quaternion_multiply<FirstQuaternionT_, second_quat_typearg, calc_fp, StaticAssert_>())
				{
					static_assert(!StaticAssert_, "Unable to sequence multiple Quaternions (WITHOUT fused operations) to form a single 3D rotation Matrix as a multiply operation cannot be formed with the first two passed Quaternion types with an output Quaternion type containing the determined calculation type.");
					return false;
				}
				else
				{
					if constexpr (_matrix_can_combine_quaternions_after_initial_multiply<StaticAssert_, Fused_, OutMatrix_, calc_fp, OtherQuaternionTs_...>())
					{
						return _matrix_can_make_from_quaternions<StaticAssert_, Fused_, OutMatrix_, calc_fp>();
					}
					else
					{
						return false;
					}
				}
			}
		}
	}
#pragma endregion

#pragma region QUATERNION_MAKERS
	template<class OutMatrix_, typename CalcFP_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_rotate_3_make_from_quaternion_results
	(
		CalcFP_* p_results_3x3_column_major_,
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_
	)
	{
		using mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		using column_indices = std::index_sequence<ColumnIndices_...>;
		using row_indices = std::index_sequence<RowIndices_...>;
		if constexpr(_matrix_can_finalise_construction_from_quaternions<OutMatrix_, CalcFP_, true>(column_indices(), row_indices()))
		{
			return OutMatrix_
			(
				std::forward<decltype(_matrix_rotate_3_from_quaternion_get_arg<ColumnIndices_, RowIndices_, mat_uq, CalcFP_>(p_results_3x3_column_major_))>
				(
					_matrix_rotate_3_from_quaternion_get_arg<ColumnIndices_, RowIndices_, mat_uq, CalcFP_>(p_results_3x3_column_major_)
				)...
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutMatrix_>(),
				"Failed to construct an EmuMath 3D rotation transformation Matrix from Quaternion conversion results. See other static assert messages for more info."
			);
		}
	}

	template<class OutMatrix_, typename QuaternionT_>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_rotate_3_from_quaternion(const EmuMath::Quaternion<QuaternionT_>& quaternion_)
	{
		if constexpr(_matrix_can_calculate_quaternion_conversion<OutMatrix_, QuaternionT_, true>())
		{
			// Note: this function calculates everything regardless of Matrix size, since chances are that the output is at least 3x3 in this context
			// --- The extra layer of abstraction would be either difficult to maintain or a potential performance sacrifice with little gain
			using mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			using mat_fp = typename mat_uq::preferred_floating_point;
			using quat_fp = typename EmuMath::Quaternion<QuaternionT_>::preferred_floating_point;
			using calc_fp = typename EmuCore::TMP::largest_floating_point<mat_fp, quat_fp>::type;

			calc_fp x = static_cast<calc_fp>(quaternion_.X());
			calc_fp y = static_cast<calc_fp>(quaternion_.Y());
			calc_fp z = static_cast<calc_fp>(quaternion_.Z());
			calc_fp w = static_cast<calc_fp>(quaternion_.W());

			using add_func = EmuCore::do_add<calc_fp, calc_fp>;
			using sub_func = EmuCore::do_subtract<calc_fp, calc_fp>;
			using mul_func = EmuCore::do_multiply<calc_fp, calc_fp>;

			// Common calculation values
			calc_fp x_MUL_2 = mul_func()(x, calc_fp(2));
			calc_fp y_MUL_2 = mul_func()(y, calc_fp(2));
			calc_fp z_MUL_2 = mul_func()(z, calc_fp(2));

			calc_fp one_SUB_x_MUL_2_MUL_x = sub_func()(calc_fp(1), mul_func()(x_MUL_2, x));
			calc_fp x_MUL_2_MUL_y = mul_func()(x_MUL_2, y);
			calc_fp x_MUL_2_MUL_z = mul_func()(x_MUL_2, z);
			calc_fp x_MUL_2_MUL_w = mul_func()(x_MUL_2, w);

			calc_fp y_MUL_2_MUL_y = mul_func()(y_MUL_2, y);
			calc_fp y_MUL_2_MUL_z = mul_func()(y_MUL_2, z);
			calc_fp y_MUL_2_MUL_w = mul_func()(y_MUL_2, w);

			calc_fp z_MUL_2_MUL_z = mul_func()(z_MUL_2, z);
			calc_fp z_MUL_2_MUL_w = mul_func()(z_MUL_2, w);

			// Calculate 3x3 rotation matrix in column-major order; remaining indices are 0 (except 1s on main diagonal)
			// --- This is rather ugly to read, but we skip duplicate calculations this way
			calc_fp cm_results[9] =
			{
				// Column 0
				sub_func()(sub_func()(calc_fp(1), y_MUL_2_MUL_y), z_MUL_2_MUL_z), // c0r0
				add_func()(x_MUL_2_MUL_y, z_MUL_2_MUL_w), // c0r1
				sub_func()(x_MUL_2_MUL_z, y_MUL_2_MUL_w), // c0r2

				// Column 1
				sub_func()(x_MUL_2_MUL_y, z_MUL_2_MUL_w), // c1r0
				sub_func()(one_SUB_x_MUL_2_MUL_x, z_MUL_2_MUL_z), // c1r1
				add_func()(y_MUL_2_MUL_z, x_MUL_2_MUL_w), // c1r2

				// Column 2
				add_func()(x_MUL_2_MUL_z, y_MUL_2_MUL_w), // c2r0
				sub_func()(y_MUL_2_MUL_z, x_MUL_2_MUL_w), // c2r1
				sub_func()(one_SUB_x_MUL_2_MUL_x, y_MUL_2_MUL_y) // c2r2
			};

			using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type>;
			using column_indices = typename out_indices::column_index_sequence;
			using row_indices = typename out_indices::row_index_sequence;
			return _matrix_rotate_3_make_from_quaternion_results<OutMatrix_, calc_fp>(cm_results, column_indices(), row_indices());
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<QuaternionT_>(),
				"Failed to convert an EmuMath Quaternion to a Matrix. See other static assert messages for more info."
			);
		}
	}

	template<bool Fused_, typename OutQuaternionT_, typename FinalQuaternionT_>
	constexpr inline void _complete_quaternion_sequence
	(
		EmuMath::Quaternion<OutQuaternionT_>& out_quaternion_,
		const EmuMath::Quaternion<FinalQuaternionT_>& final_quaternion_
	)
	{
		if constexpr (Fused_)
		{
			out_quaternion_.FusedMultiplyAssign(final_quaternion_);
		}
		else
		{
			out_quaternion_.MultiplyAssign(final_quaternion_);
		}
	}

	template<bool Fused_, typename OutQuaternionT_, typename NextQuaternionT_, typename...RemainingQuaternionTs_>
	constexpr inline auto _complete_quaternion_sequence
	(
		EmuMath::Quaternion<OutQuaternionT_>& out_quaternion_,
		const EmuMath::Quaternion<NextQuaternionT_>& next_quaternion_,
		const EmuMath::Quaternion<RemainingQuaternionTs_>&...remaining_quaternions_
	) -> std::enable_if_t<sizeof...(RemainingQuaternionTs_) != 0, void>
	{
		if constexpr (Fused_)
		{
			out_quaternion_.FusedMultiplyAssign(next_quaternion_);
		}
		else
		{
			out_quaternion_.MultiplyAssign(next_quaternion_);
		}
		_complete_quaternion_sequence<Fused_>(out_quaternion_, remaining_quaternions_...);
	}

	template<class OutMatrix_, bool Fused_, typename FirstQuaternionT_, typename SecondQuaternionT_, typename...RemainingQuaternionTs_>
	[[nodiscard]] constexpr inline auto _matrix_rotate_3_from_quaternion_sequence
	(
		const EmuMath::Quaternion<FirstQuaternionT_>& first_quaternion_,
		const EmuMath::Quaternion<SecondQuaternionT_>& second_quaternion_,
		const EmuMath::Quaternion<RemainingQuaternionTs_>&...remaining_quaternions_
	)
		-> std::enable_if_t<sizeof...(RemainingQuaternionTs_) != 0, OutMatrix_>
	{
		if constexpr(_matrix_can_make_from_quaternions<true, Fused_, OutMatrix_, FirstQuaternionT_, SecondQuaternionT_, RemainingQuaternionTs_...>())
		{
			using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			using calc_fp = typename EmuCore::TMP::largest_floating_point
			<
				typename out_mat_uq::preferred_floating_point,
				typename EmuMath::Quaternion<FirstQuaternionT_>::preferred_floating_point,
				typename EmuMath::Quaternion<SecondQuaternionT_>::preferred_floating_point,
				typename EmuMath::Quaternion<RemainingQuaternionTs_>::preferred_floating_point...
			>::type;
			if constexpr (Fused_)
			{
				EmuMath::Quaternion<calc_fp> combined_quaternion = first_quaternion_.template FusedMultiply<calc_fp>(second_quaternion_);
				_complete_quaternion_sequence<Fused_>(combined_quaternion, remaining_quaternions_...);
				return _matrix_rotate_3_from_quaternion<OutMatrix_>(combined_quaternion);

			}
			else
			{
				EmuMath::Quaternion<calc_fp> combined_quaternion = first_quaternion_.template Multiply<calc_fp>(second_quaternion_);
				_complete_quaternion_sequence<Fused_>(combined_quaternion, remaining_quaternions_...);
				return _matrix_rotate_3_from_quaternion<OutMatrix_>(combined_quaternion);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<RemainingQuaternionTs_...>(),
				"Failed to sequence 3 or more EmuMath Quaternions and convert the result to a Matrix. See other static assert messages for more info."
			);
		}
	}

	template<class OutMatrix_, bool Fused_, typename FirstQuaternionT_, typename SecondQuaternionT_>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_rotate_3_from_quaternion_sequence
	(
		const EmuMath::Quaternion<FirstQuaternionT_>& first_quaternion_,
		const EmuMath::Quaternion<SecondQuaternionT_>& second_quaternion_
	)
	{
		if constexpr(_matrix_can_make_from_quaternions<true, Fused_, OutMatrix_, FirstQuaternionT_, SecondQuaternionT_>())
		{
			using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			using calc_fp = typename EmuCore::TMP::largest_floating_point
			<
				typename out_mat_uq::preferred_floating_point,
				typename EmuMath::Quaternion<FirstQuaternionT_>::preferred_floating_point,
				typename EmuMath::Quaternion<SecondQuaternionT_>::preferred_floating_point
			>::type;
			if constexpr (Fused_)
			{
				return _matrix_rotate_3_from_quaternion<OutMatrix_>(first_quaternion_.template FusedMultiply<calc_fp>(second_quaternion_));
			}
			else
			{
				return _matrix_rotate_3_from_quaternion<OutMatrix_>(first_quaternion_.template Multiply<calc_fp>(second_quaternion_));
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<FirstQuaternionT_, SecondQuaternionT_, OutMatrix_>(),
				"Failed to sequence 2 EmuMath Quaternions and convert the result to a Matrix. See other static assert messages for more info."
			);
		}
	}
#pragma endregion
}

#endif