#ifndef EMU_MATH_MATRIX_UNDERLYING_ROTATE_3D_H_INC_
#define EMU_MATH_MATRIX_UNDERLYING_ROTATE_3D_H_INC_ 1

#include "../_matrix_tmp.h"

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
#pragma warning(push)
#pragma warning(disable: 6287)
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
#pragma warning(pop)
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
#pragma warning(push)
#pragma warning(disable: 6287)
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
#pragma warning(pop)
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
#pragma warning(push)
#pragma warning(disable: 6287)
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
#pragma warning(pop)
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
	[[nodiscard]] constexpr inline void _matrix_assign_rotate_3_in_axis(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Angle_&& angle_)
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

#pragma region QUATERNION_VALIDITY_CHECKS
	// TODO
#pragma endregion

#pragma region QUATERNION_MAKERS
	// TODO
#pragma endregion
}

#endif