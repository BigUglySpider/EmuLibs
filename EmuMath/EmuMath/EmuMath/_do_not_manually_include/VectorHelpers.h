#ifndef EMU_MATH_VECTOR_HELPERS_H_INC_
#define EMU_MATH_VECTOR_HELPERS_H_INC_

#include "VectorHelpersUnderlying.h"

namespace EmuMath::Helpers
{
	template<class OutVector, class LhsVector, class RhsVector>
	inline OutVector VectorAddition(const LhsVector& lhs, const RhsVector& rhs)
	{
		if constexpr (EmuCore::TMPHelpers::are_all_check<EmuMath::TMPHelpers::is_emu_vector, LhsVector, RhsVector, OutVector>::value)
		{
			return _underlying_vector_funcs::_perform_vector_arithmetic_vector_rhs_emu<OutVector, LhsVector, RhsVector, EmuCore::TMPHelpers::plus_diff_types>(lhs, rhs);
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath Vector addition (+) via non-EmuMath Vector types. Non-Vectors may not be used with addition.");
			return OutVector();
		}
	}
	template<class OutVector, class LhsVector, class RhsVector>
	inline OutVector VectorSubtraction(const LhsVector& lhs, const RhsVector& rhs)
	{
		if constexpr (EmuCore::TMPHelpers::are_all_check<EmuMath::TMPHelpers::is_emu_vector, LhsVector, RhsVector, OutVector>::value)
		{
			return _underlying_vector_funcs::_perform_vector_arithmetic_vector_rhs_emu<OutVector, LhsVector, RhsVector, EmuCore::TMPHelpers::minus_diff_types>(lhs, rhs);
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath Vector subtraction (-) via non-EmuMath Vector types. Non-Vectors may not be used with subtraction.");
			return OutVector();
		}
	}
	template<class OutVector, class LhsVector, class Rhs>
	inline OutVector VectorMultiplication(const LhsVector& lhs, const Rhs& rhs)
	{
		if constexpr (EmuCore::TMPHelpers::are_all_check<EmuMath::TMPHelpers::is_emu_vector, LhsVector, OutVector>::value)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<Rhs>)
			{
				return _underlying_vector_funcs::_perform_vector_arithmetic_vector_rhs_emu<OutVector, LhsVector, Rhs, EmuCore::TMPHelpers::multiplies_diff_types>(lhs, rhs);
			}
			else
			{
				return _underlying_vector_funcs::_perform_vector_arithmetic_scalar_rhs_emu<OutVector, LhsVector, Rhs, EmuCore::TMPHelpers::multiplies_diff_types>(lhs, rhs);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath Vector multiplication (*) with non-EmuMath Vector left-handed operand or output type.");
			return OutVector();
		}
	}
	template<class OutVector, class LhsVector, class Rhs>
	inline OutVector VectorDivision(const LhsVector& lhs, const Rhs& rhs)
	{
		if constexpr (EmuCore::TMPHelpers::are_all_check<EmuMath::TMPHelpers::is_emu_vector, LhsVector, OutVector>::value)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<Rhs>)
			{
				return _underlying_vector_funcs::_perform_vector_arithmetic_vector_rhs_emu<OutVector, LhsVector, Rhs, EmuCore::TMPHelpers::divides_diff_types>(lhs, rhs);
			}
			else
			{
				return _underlying_vector_funcs::_perform_vector_arithmetic_scalar_rhs_emu<OutVector, LhsVector, Rhs, EmuCore::TMPHelpers::divides_diff_types>(lhs, rhs);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath Vector division (/) with non-EmuMath Vector left-handed operand or output type.");
			return OutVector();
		}
	}
	template<class OutVector, class LhsVector, class Rhs>
	inline OutVector VectorMod(const LhsVector& lhs, const Rhs& rhs)
	{
		if constexpr (EmuCore::TMPHelpers::are_all_check<EmuMath::TMPHelpers::is_emu_vector, LhsVector, OutVector>::value)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<Rhs>)
			{
				return _underlying_vector_funcs::_perform_vector_arithmetic_vector_rhs_emu<OutVector, LhsVector, Rhs, EmuCore::TMPHelpers::modulus_diff_types>(lhs, rhs);
			}
			else
			{
				return _underlying_vector_funcs::_perform_vector_arithmetic_scalar_rhs_emu<OutVector, LhsVector, Rhs, EmuCore::TMPHelpers::modulus_diff_types>(lhs, rhs);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath Vector modulo division (%) with non-EmuMath Vector left-handed operand or output type.");
			return OutVector();
		}
	}

	template<class OutVector, class LhsVector, class Rhs>
	inline OutVector VectorBitwiseAnd(const LhsVector& lhs, const Rhs& rhs)
	{
		if constexpr (EmuCore::TMPHelpers::are_all_check<EmuMath::TMPHelpers::is_emu_vector, LhsVector, OutVector>::value)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<Rhs>)
			{
				return _underlying_vector_funcs::_perform_vector_bitwise_op_vector_rhs_emu<OutVector, LhsVector, Rhs, EmuCore::TMPHelpers::bitwise_and_diff_types>(lhs, rhs);
			}
			else
			{
				return _underlying_vector_funcs::_perform_vector_bitwise_op_scalar_rhs_emu<OutVector, LhsVector, Rhs, EmuCore::TMPHelpers::bitwise_and_diff_types>(lhs, rhs);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath Vector bitwise AND (&) with non-EmuMath Vector left-handed operand or output type.");
			return OutVector();
		}
	}
	template<class OutVector, class LhsVector, class Rhs>
	inline OutVector VectorBitwiseOr(const LhsVector& lhs, const Rhs& rhs)
	{
		if constexpr (EmuCore::TMPHelpers::are_all_check<EmuMath::TMPHelpers::is_emu_vector, LhsVector, OutVector>::value)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<Rhs>)
			{
				return _underlying_vector_funcs::_perform_vector_bitwise_op_vector_rhs_emu<OutVector, LhsVector, Rhs, EmuCore::TMPHelpers::bitwise_or_diff_types>(lhs, rhs);
			}
			else
			{
				return _underlying_vector_funcs::_perform_vector_bitwise_op_scalar_rhs_emu<OutVector, LhsVector, Rhs, EmuCore::TMPHelpers::bitwise_or_diff_types>(lhs, rhs);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath Vector bitwise OR (|) with non-EmuMath Vector left-handed operand or output type.");
			return OutVector();
		}
	}
	template<class OutVector, class LhsVector, class Rhs>
	inline OutVector VectorBitwiseXor(const LhsVector& lhs, const Rhs& rhs)
	{
		if constexpr (EmuCore::TMPHelpers::are_all_check<EmuMath::TMPHelpers::is_emu_vector, LhsVector, OutVector>::value)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<Rhs>)
			{
				return _underlying_vector_funcs::_perform_vector_bitwise_op_vector_rhs_emu<OutVector, LhsVector, Rhs, EmuCore::TMPHelpers::bitwise_xor_diff_types>(lhs, rhs);
			}
			else
			{
				return _underlying_vector_funcs::_perform_vector_bitwise_op_scalar_rhs_emu<OutVector, LhsVector, Rhs, EmuCore::TMPHelpers::bitwise_xor_diff_types>(lhs, rhs);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath Vector bitwise XOR (^) with non-EmuMath Vector left-handed operand or output type.");
			return OutVector();
		}
	}

	template<class OutVector, class LhsVector, class Rhs>
	inline OutVector VectorLeftShiftPerElement(const LhsVector& lhs, const Rhs& rhs)
	{
		if constexpr (EmuCore::TMPHelpers::are_all_check<EmuMath::TMPHelpers::is_emu_vector, LhsVector, OutVector>::value)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<Rhs>)
			{
				return _underlying_vector_funcs::_perform_vector_bitwise_op_vector_rhs_emu<OutVector, LhsVector, Rhs, EmuCore::TMPHelpers::bitwise_shift_left_diff_types>(lhs, rhs);
			}
			else
			{
				return _underlying_vector_funcs::_perform_vector_bitwise_op_scalar_rhs_emu<OutVector, LhsVector, Rhs, EmuCore::TMPHelpers::bitwise_shift_left_diff_types>(lhs, rhs);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath Vector bitwise left shift (<<) per-element with non-EmuMath Vector left-handed operand or output type.");
			return OutVector();
		}
	}
	template<class OutVector, class LhsVector, class Rhs>
	inline OutVector VectorRightShiftPerElement(const LhsVector& lhs, const Rhs& rhs)
	{
		if constexpr (EmuCore::TMPHelpers::are_all_check<EmuMath::TMPHelpers::is_emu_vector, LhsVector, OutVector>::value)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<Rhs>)
			{
				return _underlying_vector_funcs::_perform_vector_bitwise_op_vector_rhs_emu<OutVector, LhsVector, Rhs, EmuCore::TMPHelpers::bitwise_shift_right_diff_types>(lhs, rhs);
			}
			else
			{
				return _underlying_vector_funcs::_perform_vector_bitwise_op_scalar_rhs_emu<OutVector, LhsVector, Rhs, EmuCore::TMPHelpers::bitwise_shift_right_diff_types>(lhs, rhs);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath Vector right shift (>>) per-element with non-EmuMath Vector left-handed operand or output type.");
			return OutVector();
		}
	}

	template<class EmuVector_>
	inline constexpr typename EmuMath::TMPHelpers::emu_vector_copy<EmuVector_>::type VectorLeftShiftVectorwise(const EmuVector_& inVector, const std::size_t numShifts)
	{
		using OutVector = EmuMath::TMPHelpers::emu_vector_copy_t<EmuVector_>;
		if constexpr (!std::is_same_v<OutVector, std::false_type>)
		{
			return _underlying_vector_funcs::_perform_vectorwise_shift_emu
			<
				OutVector,
				EmuVector_,
				EmuCore::TMPHelpers::bitwise_shift_left_diff_types,
				EmuCore::TMPHelpers::bitwise_shift_right_diff_types,
				true
			>(inVector, numShifts);
		}
		else
		{
			static_assert(false, "Attempted to perform a vectorwise left-shift for EmuMath Vectors using a non-EmuMath-Vector type.");
			return std::false_type();
		}
	}
	template<class EmuVector_>
	inline constexpr typename EmuMath::TMPHelpers::emu_vector_copy<EmuVector_>::type VectorRightShiftVectorwise(const EmuVector_& inVector, const std::size_t numShifts)
	{
		using OutVector = EmuMath::TMPHelpers::emu_vector_copy_t<EmuVector_>;
		if constexpr (!std::is_same_v<OutVector, std::false_type>)
		{
			return _underlying_vector_funcs::_perform_vectorwise_shift_emu
			<
				OutVector,
				EmuVector_,
				EmuCore::TMPHelpers::bitwise_shift_right_diff_types,
				EmuCore::TMPHelpers::bitwise_shift_left_diff_types,
				false
			>(inVector, numShifts);
		}
		else
		{
			static_assert(false, "Attempted to perform a vectorwise right-shift for EmuMath Vectors using a non-EmuMath-Vector type.");
			return std::false_type();
		}
	}

	template<std::size_t OutSize_, typename OutT, class InVector_>
	inline constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT>::type VectorBitwiseNot(const InVector_& in_)
	{
		using OutVector = typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT>::type;
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<InVector_>)
		{
			return _underlying_vector_funcs::_perform_vector_bitwise_not<OutVector, InVector_>(in_);
		}
		else
		{
			static_assert(false, "Attempted to perform a bitwise not on an EmuMath Vector with a non-EmuMath-Vector operand.");
			return OutVector();
		}
	}

	template<typename OutT, class EmuVector_>
	inline constexpr OutT VectorSquareMagnitude(const EmuVector_& vector_)
	{
		return _underlying_vector_funcs::_calculate_square_magnitude<OutT, EmuVector_>(vector_);
	}

	/// <summary>
	/// <para> Returns the magnitude of the passed EmuMath Vector, represented as the passed floating point OutFP_ type. </para>
	/// <para> It is recommended to only use this for compile time constants, and instead use VectorMagnitude for code that will execute at runtime. </para>
	/// </summary>
	/// <typeparam name="OutFP_">Type to return, representing the magnitude of the passed Vector. Must be a floating point type.</typeparam>
	/// <typeparam name="EmuVector_">Type of EmuMath Vector being passed.</typeparam>
	/// <param name="vector_">EmuMath Vector to return the magnitude of.</param>
	/// <returns>Magnitude of the passed vector, represented as the passed OutFP_ type (first and only required template parameter).</returns>
	template<typename OutFP_, class EmuVector_>
	inline constexpr OutFP_ VectorMagnitudeConstexpr(const EmuVector_& vector_)
	{
		return _underlying_vector_funcs::_calculate_magnitude_constexpr<OutFP_, EmuVector_>(vector_);
	}

	/// <summary>
	/// <para> Returns the magnitude of the passed EmuMath Vector, represented as the passed Out_ type. </para>
	/// <para> It is recommended to use this instead of VectorMagnitudeConstexpr for runtime-executed code. </para>
	/// </summary>
	/// <typeparam name="Out_">Type to return, representing the magnitude of the passed Vector.</typeparam>
	/// <typeparam name="EmuVector_">Type of EmuMath Vector being passed.</typeparam>
	/// <param name="vector_">EmuMath Vector to return the magnitude of.</param>
	/// <returns>Magnitude of the passed vector, represented as the passed Out_ type (first and only required template parameter).</returns>
	template<typename Out_, class EmuVector_>
	inline Out_ VectorMagnitude(const EmuVector_& vector_)
	{
		return _underlying_vector_funcs::_calculate_magnitude<Out_, EmuVector_>(vector_);
	}

	template<typename OutFP_, typename InT_>
	inline EmuMath::Vector2<OutFP_> VectorNormalise(const EmuMath::Vector2<InT_>& inVector)
	{
		using OutVector = EmuMath::Vector2<OutFP_>;
		using StrippedOut = std::remove_cv_t<OutFP_>;
		if constexpr (std::is_floating_point_v<StrippedOut>)
		{
			using Mag_ = long double;
			const Mag_ reciprocal = 1.0L / VectorMagnitude<Mag_>(inVector);
			return OutVector
			(
				static_cast<OutFP_>(inVector.x) * reciprocal,
				static_cast<OutFP_>(inVector.y) * reciprocal
			);
		}
		else
		{
			static_assert(false, "Attempted to normalise a EmuMath Vector and output it as a non-floating-point-containing EmuMath Vector.");
		}
	}
	template<typename OutFP_, typename InT_>
	inline EmuMath::Vector3<OutFP_> VectorNormalise(const EmuMath::Vector3<InT_>& inVector)
	{
		using OutVector = EmuMath::Vector3<OutFP_>;
		using StrippedOut = std::remove_cv_t<OutFP_>;
		if constexpr (std::is_floating_point_v<StrippedOut>)
		{
			using Mag_ = long double;
			const Mag_ reciprocal = 1.0f / VectorMagnitude<Mag_>(inVector);
			return OutVector
			(
				static_cast<OutFP_>(inVector.x) * reciprocal,
				static_cast<OutFP_>(inVector.y) * reciprocal,
				static_cast<OutFP_>(inVector.z) * reciprocal
			);
		}
		else
		{
			static_assert(false, "Attempted to normalise a EmuMath Vector and output it as a non-floating-point-containing EmuMath Vector.");
		}
	}
	template<typename OutFP_, typename InT_>
	inline EmuMath::Vector4<OutFP_> VectorNormalise(const EmuMath::Vector4<InT_>& inVector)
	{
		using OutVector = EmuMath::Vector4<OutFP_>;
		using StrippedOut = std::remove_cv_t<OutFP_>;
		if constexpr (std::is_floating_point_v<StrippedOut>)
		{
			using Mag_ = long double;
			const Mag_ reciprocal = 1.0f / VectorMagnitude<Mag_>(inVector);
			return OutVector
			(
				static_cast<OutFP_>(inVector.x) * reciprocal,
				static_cast<OutFP_>(inVector.y) * reciprocal,
				static_cast<OutFP_>(inVector.z) * reciprocal,
				static_cast<OutFP_>(inVector.w) * reciprocal
			);
		}
		else
		{
			static_assert(false, "Attempted to normalise a EmuMath Vector and output it as a non-floating-point-containing EmuMath Vector.");
		}
	}

	template<typename OutFP_, typename InT_>
	inline constexpr EmuMath::Vector2<OutFP_> VectorNormaliseConstexpr(const EmuMath::Vector2<InT_>& inVector)
	{
		using OutVector = EmuMath::Vector2<OutFP_>;
		using StrippedOut = std::remove_cv_t<OutFP_>;
		if constexpr (std::is_floating_point_v<StrippedOut>)
		{
			using Mag_ = long double;
			const Mag_ reciprocal = 1.0f / VectorMagnitudeConstexpr<Mag_>(inVector);
			return OutVector
			(
				static_cast<OutFP_>(inVector.x) * reciprocal,
				static_cast<OutFP_>(inVector.y) * reciprocal
			);
		}
		else
		{
			static_assert(false, "Attempted to normalise a EmuMath Vector and output it as a non-floating-point-containing EmuMath Vector.");
		}
	}
	template<typename OutFP_, typename InT_>
	inline constexpr EmuMath::Vector3<OutFP_> VectorNormaliseConstexpr(const EmuMath::Vector3<InT_>& inVector)
	{
		using OutVector = EmuMath::Vector3<OutFP_>;
		using StrippedOut = std::remove_cv_t<OutFP_>;
		if constexpr (std::is_floating_point_v<StrippedOut>)
		{
			using Mag_ = long double;
			const Mag_ reciprocal = 1.0f / VectorMagnitudeConstexpr<Mag_>(inVector);
			return OutVector
			(
				static_cast<OutFP_>(inVector.x) * reciprocal,
				static_cast<OutFP_>(inVector.y) * reciprocal,
				static_cast<OutFP_>(inVector.z) * reciprocal
			);
		}
		else
		{
			static_assert(false, "Attempted to normalise a EmuMath Vector and output it as a non-floating-point-containing EmuMath Vector.");
		}
	}
	template<typename OutFP_, typename InT_>
	inline constexpr EmuMath::Vector4<OutFP_> VectorNormaliseConstexpr(const EmuMath::Vector4<InT_>& inVector)
	{
		using OutVector = EmuMath::Vector4<OutFP_>;
		using StrippedOut = std::remove_cv_t<OutFP_>;
		if constexpr (std::is_floating_point_v<StrippedOut>)
		{
			using Mag_ = long double;
			const Mag_ reciprocal = 1.0f / VectorMagnitudeConstexpr<Mag_>(inVector);
			return OutVector
			(
				static_cast<OutFP_>(inVector.x) * reciprocal,
				static_cast<OutFP_>(inVector.y) * reciprocal,
				static_cast<OutFP_>(inVector.z) * reciprocal,
				static_cast<OutFP_>(inVector.w) * reciprocal
			);
		}
		else
		{
			static_assert(false, "Attempted to normalise a EmuMath Vector and output it as a non-floating-point-containing EmuMath Vector.");
		}
	}

	template<class LhsVector_, class RhsT_>
	inline constexpr bool VectorComparisonEqual(const LhsVector_& lhs, const Vector2<RhsT_>& rhs)
	{
		return _underlying_vector_funcs::_perform_vector_comparison_equal<LhsVector_, RhsT_, 2>(lhs, rhs);
	}
	template<class LhsVector_, class RhsT_>
	inline constexpr bool VectorComparisonEqual(const LhsVector_& lhs, const Vector3<RhsT_>& rhs)
	{
		return _underlying_vector_funcs::_perform_vector_comparison_equal<LhsVector_, RhsT_, 3>(lhs, rhs);
	}
	template<class LhsVector_, class RhsT_>
	inline constexpr bool VectorComparisonEqual(const LhsVector_& lhs, const Vector4<RhsT_>& rhs)
	{
		return _underlying_vector_funcs::_perform_vector_comparison_equal<LhsVector_, RhsT_, 4>(lhs, rhs);
	}

	template<class LhsVector_, class RhsT_>
	inline constexpr bool VectorComparisonNotEqual(const LhsVector_& lhs, const EmuMath::Vector2<RhsT_>& rhs)
	{
		return _underlying_vector_funcs::_perform_vector_comparison_not_equal<LhsVector_, RhsT_, 2>(lhs, rhs);
	}
	template<class LhsVector_, class RhsT_>
	inline constexpr bool VectorComparisonNotEqual(const LhsVector_& lhs, const EmuMath::Vector3<RhsT_>& rhs)
	{
		return _underlying_vector_funcs::_perform_vector_comparison_not_equal<LhsVector_, RhsT_, 3>(lhs, rhs);
	}
	template<class LhsVector_, class RhsT_>
	inline constexpr bool VectorComparisonNotEqual(const LhsVector_& lhs, const EmuMath::Vector4<RhsT_>& rhs)
	{
		return _underlying_vector_funcs::_perform_vector_comparison_not_equal<LhsVector_, RhsT_, 4>(lhs, rhs);
	}

	template<class LhsVector_, class Rhs_>
	inline constexpr bool VectorComparisonGreater(const LhsVector_& lhs, const Rhs_& rhs)
	{
		return _underlying_vector_funcs::_perform_vector_magnitude_comparison_std<LhsVector_, Rhs_, std::greater<void>>(lhs, rhs);
	}
	template<class LhsVector_, class Rhs_>
	inline constexpr bool VectorComparisonLess(const LhsVector_& lhs, const Rhs_& rhs)
	{
		return _underlying_vector_funcs::_perform_vector_magnitude_comparison_std<LhsVector_, Rhs_, std::less<void>>(lhs, rhs);
	}
	template<class LhsVector_, class Rhs_>
	inline constexpr bool VectorComparisonGreaterEqual(const LhsVector_& lhs, const Rhs_& rhs)
	{
		return _underlying_vector_funcs::_perform_vector_magnitude_comparison_std<LhsVector_, Rhs_, std::greater_equal<void>>(lhs, rhs);
	}
	template<class LhsVector_, class Rhs_>
	inline constexpr bool VectorComparisonLessEqual(const LhsVector_& lhs, const Rhs_& rhs)
	{
		return _underlying_vector_funcs::_perform_vector_magnitude_comparison_std<LhsVector_, Rhs_, std::less_equal<void>>(lhs, rhs);
	}

	template<std::size_t OutSize_, typename OutContainedT_, class InVector_>
	inline typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutContainedT_>::type VectorCeil(const InVector_& in_)
	{
		using OutVector_ = typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutContainedT_>::type;
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<OutVector_>)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<InVector_>)
			{
				return _underlying_vector_funcs::_perform_vector_round_emu<OutVector_, InVector_, EmuCore::TMPHelpers::ceil_diff_types>(in_);
			}
			else
			{
				static_assert(false, "Provided a non-EmuMath Vector input type when attempted to perform a Vector Ceil.");
				return OutVector_();
			}
		}
		else
		{
			static_assert(false, "Provided an invalid output EmuMath Vector size when attempting to Ceil an EmuMath Vector.");
			return OutVector_();
		}
	}
	template<std::size_t OutSize_, typename OutContainedT_, class InVector_>
	inline constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutContainedT_>::type VectorCeilConstexpr(const InVector_& in_)
	{
		using OutVector_ = typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutContainedT_>::type;
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<OutVector_>)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<InVector_>)
			{
				return _underlying_vector_funcs::_perform_vector_constexpr_round_emu<OutVector_, InVector_, EmuCore::TMPHelpers::ceil_diff_types>(in_);
			}
			else
			{
				static_assert(false, "Provided a non-EmuMath Vector input type when attempted to perform a Vector Ceil.");
				return OutVector_();
			}
		}
		else
		{
			static_assert(false, "Provided an invalid output EmuMath Vector size when attempting to Ceil an EmuMath Vector.");
			return OutVector_();
		}
	}

	template<std::size_t OutSize_, typename OutContainedT_, class InVector_>
	inline typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutContainedT_>::type VectorFloor(const InVector_& in_)
	{
		using OutVector_ = typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutContainedT_>::type;
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<OutVector_>)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<InVector_>)
			{
				return _underlying_vector_funcs::_perform_vector_round_emu<OutVector_, InVector_, EmuCore::TMPHelpers::floor_diff_types>(in_);
			}
			else
			{
				static_assert(false, "Provided a non-EmuMath Vector input type when attempted to perform a Vector Floor.");
				return OutVector_();
			}
		}
		else
		{
			static_assert(false, "Provided an invalid output EmuMath Vector size when attempting to Floor an EmuMath Vector.");
			return OutVector_();
		}
	}
	template<std::size_t OutSize_, typename OutContainedT_, class InVector_>
	inline constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutContainedT_>::type VectorFloorConstexpr(const InVector_& in_)
	{
		using OutVector_ = typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutContainedT_>::type;
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<OutVector_>)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<InVector_>)
			{
				return _underlying_vector_funcs::_perform_vector_constexpr_round_emu<OutVector_, InVector_, EmuCore::TMPHelpers::floor_diff_types>(in_);
			}
			else
			{
				static_assert(false, "Provided a non-EmuMath Vector input type when attempted to perform a Vector Floor.");
				return OutVector_();
			}
		}
		else
		{
			static_assert(false, "Provided an invalid output EmuMath Vector size when attempting to Floor an EmuMath Vector.");
			return OutVector_();
		}
	}

	template<std::size_t OutSize_, typename OutContainedT_, class InVector_>
	inline typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutContainedT_>::type VectorTrunc(const InVector_& in_)
	{
		using OutVector_ = typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutContainedT_>::type;
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<OutVector_>)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<InVector_>)
			{
				return _underlying_vector_funcs::_perform_vector_round_emu<OutVector_, InVector_, EmuCore::TMPHelpers::trunc_diff_types>(in_);
			}
			else
			{
				static_assert(false, "Provided a non-EmuMath Vector input type when attempted to perform a Vector Floor.");
				return OutVector_();
			}
		}
		else
		{
			static_assert(false, "Provided an invalid output EmuMath Vector size when attempting to Floor an EmuMath Vector.");
			return OutVector_();
		}
	}
	template<std::size_t OutSize_, typename OutContainedT_, class InVector_>
	inline constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutContainedT_>::type VectorTruncConstexpr(const InVector_& in_)
	{
		using OutVector_ = typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutContainedT_>::type;
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<OutVector_>)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<InVector_>)
			{
				return _underlying_vector_funcs::_perform_vector_constexpr_round_emu<OutVector_, InVector_, EmuCore::TMPHelpers::trunc_diff_types>(in_);
			}
			else
			{
				static_assert(false, "Provided a non-EmuMath Vector input type when attempted to perform a Vector Floor.");
				return OutVector_();
			}
		}
		else
		{
			static_assert(false, "Provided an invalid output EmuMath Vector size when attempting to Floor an EmuMath Vector.");
			return OutVector_();
		}
	}

	template<typename OutT, class LhsVector_, class RhsVector_>
	inline constexpr OutT VectorDotProduct(const LhsVector_& lhs, const RhsVector_& rhs)
	{
		if constexpr (EmuCore::TMPHelpers::is_any_check<EmuMath::TMPHelpers::is_emu_vector, LhsVector_, RhsVector_>::value)
		{
			constexpr std::size_t SmallestVecSize_ = (LhsVector_::size() < RhsVector_::size()) ? LhsVector_::size() : RhsVector_::size();
			if constexpr (SmallestVecSize_ == 2)
			{
				return
				(
					(static_cast<OutT>(lhs.x) * rhs.x) +
					(static_cast<OutT>(lhs.y) * rhs.y)
				);
			}
			else if constexpr (SmallestVecSize_ == 3)
			{
				return
				(
					(static_cast<OutT>(lhs.x) * rhs.x) +
					(static_cast<OutT>(lhs.y) * rhs.y) +
					(static_cast<OutT>(lhs.z) * rhs.z)
				);
			}
			else if constexpr (SmallestVecSize_ == 4)
			{
				return
				(
					(static_cast<OutT>(lhs.x) * rhs.x) +
					(static_cast<OutT>(lhs.y) * rhs.y) +
					(static_cast<OutT>(lhs.z) * rhs.z) +
					(static_cast<OutT>(lhs.w) * rhs.w)
				);
			}
			else
			{
				static_assert(false, "Attempted to get the dot product of two invalidly sized EmuMath Vectors.");
				return OutT();
			}
		}
		else
		{
			static_assert(false, "Attempted to get the dot product of two EmuMath Vectors with at least one non-EmuMath-Vector operand.");
			return OutT();
		}
	}

	template<typename OutT, class InVector_>
	inline constexpr OutT VectorMin(const InVector_& in_)
	{
		return _underlying_vector_funcs::_perform_vector_min_or_max_get<OutT, InVector_, std::less_equal<void>>(in_);
	}
	template<typename OutT, class InVector_>
	inline constexpr OutT VectorMax(const InVector_& in_)
	{
		return _underlying_vector_funcs::_perform_vector_min_or_max_get<OutT, InVector_, std::greater_equal<void>>(in_);
	}

	template<std::size_t OutSize_, typename OutT_, class InVector_, class MinT_>
	inline constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type VectorClampMin(const InVector_& in_, const MinT_& min_)
	{
		return _underlying_vector_funcs::_perform_vector_min_or_max_clamp
		<
			typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type,
			InVector_,
			MinT_,
			std::less<void>
		>(in_, min_);
	}
	template<std::size_t OutSize_, typename OutT_, class InVector_, class MinT_>
	inline constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type VectorClampMax(const InVector_& in_, const MinT_& min_)
	{
		return _underlying_vector_funcs::_perform_vector_min_or_max_clamp
		<
			typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type,
			InVector_,
			MinT_,
			std::greater<void>
		>(in_, min_);
	}
	template<std::size_t OutSize_, typename OutT_, class InVector_, class MinT_, class MaxT_>
	inline constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type VectorClamp(const InVector_& in_, const MinT_& min_, const MaxT_& max_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type>)
		{
			return _underlying_vector_funcs::_perform_vector_clamp_min_and_max
			<
				typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type,
				InVector_,
				MinT_,
				MaxT_
			>(in_, min_, max_);
		}
		else
		{
			static_assert(false, "Attempted to clamp an EmuMath Vector to minimum and maximum values with an invalid output Vector.");
			using OutVec_ = typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type;
			return OutVec_();
		}
	}

	/// <summary>
	/// <para> Linearly interpolates the values of the passed EmuMath Vector a_ with the values of b_, using the passed t_ as the weighting. </para>
	/// <para> b_ and t_ may be scalar values instead of Vectors. In the case of providing scalar values, they will be applied to all values in the Vector. </para>
	/// <para>
	///		If b_ is a Vector, the respective values will be used for each interpolation (e.g. b_.x will be used to lerp a_.x). 
	///		If b_ does not have a value for an interpolation to form (e.g. only has x and y but a z element is outputted), it will be treated as 0.
	/// </para>
	/// <para>
	///		If t_ is a Vector, the respective values will be used for each interpolation (e.g. t_.x will be used to lerp a_.x). 
	///		If t_ does not have a value for an interpolation, it will be treated as 0 and thus no interpolation will be performed.
	/// </para>
	/// </summary>
	/// <typeparam name="OutT_">Type to contain within the returned Vector.</typeparam>
	/// <typeparam name="VectorA_">The EmuMath Vector type that represents argument a_. Must be an EmuMath Vector.</typeparam>
	/// <typeparam name="B_">Scalar or EmuMath Vector type representing argument b_.</typeparam>
	/// <typeparam name="T_">Type of the provided t_ argument.</typeparam>
	/// <param name="a_">EmuMath Vector to perform interpolation with.</param>
	/// <param name="b_">Scalar value or EmuMath Vector to interpolate elements of a_ with.</param>
	/// <param name="t_">Scalar value or EmuMath Vector to use as the weighting for the interpolation (where 0.0 is completely a_, and 1.0 is completely b_).</param>
	/// <returns>EmuMath Vector of the provided size and contained type, containing the results of the linear interpolation (a_ + (b_ - a_) * t_).</returns>
	template<std::size_t OutSize_, typename OutT_, class VectorA_, class B_, typename T_>
	inline constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type VectorLerp(const VectorA_& a_, const B_& b_, const OutT_& t_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type>)
		{
			return _underlying_vector_funcs::_perform_vector_lerp<typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type, VectorA_, B_, OutT_>(a_, b_, t_);
		}
		else
		{
			static_assert(false, "Attempted to perform linear interpolation (lerp) with EmuMath Vector using invalid output params.");
			using Out_ = typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type;
			return Out_();
		}
	}

	template<std::size_t OutSize_, class LhsEmuVector_, class Rhs_>
	inline constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, bool>::type VectorComparisonPerElement_Equal(const LhsEmuVector_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_vector_funcs::_perform_per_element_comparison
		<
			typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, bool>::type,
			LhsEmuVector_,
			Rhs_,
			std::equal_to<void>
		>(lhs_, rhs_);
	}
	template<std::size_t OutSize_, class LhsEmuVector_, class Rhs_>
	inline constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, bool>::type VectorComparisonPerElement_NotEqual(const LhsEmuVector_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_vector_funcs::_perform_per_element_comparison
		<
			typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, bool>::type,
			LhsEmuVector_,
			Rhs_,
			std::not_equal_to<void>
		>(lhs_, rhs_);
	}

	template<std::size_t OutSize_, class LhsEmuVector_, class Rhs_>
	inline constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, bool>::type VectorComparisonPerElement_Less(const LhsEmuVector_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_vector_funcs::_perform_per_element_comparison
		<
			typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, bool>::type,
			LhsEmuVector_,
			Rhs_,
			std::less<void>
		>(lhs_, rhs_);
	}
	template<std::size_t OutSize_, class LhsEmuVector_, class Rhs_>
	inline constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, bool>::type VectorComparisonPerElement_LessEqual(const LhsEmuVector_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_vector_funcs::_perform_per_element_comparison
		<
			typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, bool>::type,
			LhsEmuVector_,
			Rhs_,
			std::less_equal<void>
		>(lhs_, rhs_);
	}

	template<std::size_t OutSize_, class LhsEmuVector_, class Rhs_>
	inline constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, bool>::type VectorComparisonPerElement_Greater(const LhsEmuVector_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_vector_funcs::_perform_per_element_comparison
		<
			typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, bool>::type,
			LhsEmuVector_,
			Rhs_,
			std::greater<void>
		>(lhs_, rhs_);
	}
	template<std::size_t OutSize_, class LhsEmuVector_, class Rhs_>
	inline constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, bool>::type VectorComparisonPerElement_GreaterEqual(const LhsEmuVector_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_vector_funcs::_perform_per_element_comparison
		<
			typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, bool>::type,
			LhsEmuVector_,
			Rhs_,
			std::greater_equal<void>
		>(lhs_, rhs_);
	}

	template<bool IncludeNonContained_, class LhsVector_, class Rhs_>
	inline constexpr bool VectorComparisonAll_Equal(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_vector_funcs::_perform_vector_comparison_all
		<
			IncludeNonContained_,
			LhsVector_,
			Rhs_,
			std::equal_to<void>
		>(lhs_, rhs_);
	}
	template<bool IncludeNonContained_, class LhsVector_, class Rhs_>
	inline constexpr bool VectorComparisonAll_NotEqual(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_vector_funcs::_perform_vector_comparison_all
		<
			IncludeNonContained_,
			LhsVector_,
			Rhs_,
			std::not_equal_to<void>
		>(lhs_, rhs_);
	}

	template<bool IncludeNonContained_, class LhsVector_, class Rhs_>
	inline constexpr bool VectorComparisonAll_Less(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_vector_funcs::_perform_vector_comparison_all
		<
			IncludeNonContained_,
			LhsVector_,
			Rhs_,
			std::less<void>
		>(lhs_, rhs_);
	}
	template<bool IncludeNonContained_, class LhsVector_, class Rhs_>
	inline constexpr bool VectorComparisonAll_LessEqual(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_vector_funcs::_perform_vector_comparison_all
		<
			IncludeNonContained_,
			LhsVector_,
			Rhs_,
			std::less_equal<void>
		>(lhs_, rhs_);
	}

	template<bool IncludeNonContained_, class LhsVector_, class Rhs_>
	inline constexpr bool VectorComparisonAll_Greater(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_vector_funcs::_perform_vector_comparison_all
		<
			IncludeNonContained_,
			LhsVector_,
			Rhs_,
			std::greater<void>
		>(lhs_, rhs_);
	}
	template<bool IncludeNonContained_, class LhsVector_, class Rhs_>
	inline constexpr bool VectorComparisonAll_GreaterEqual(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_vector_funcs::_perform_vector_comparison_all
		<
			IncludeNonContained_,
			LhsVector_,
			Rhs_,
			std::greater_equal<void>
		>(lhs_, rhs_);
	}

	template<bool IncludeNonContained_, class LhsVector_, class Rhs_>
	inline constexpr bool VectorComparisonAny_Equal(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_vector_funcs::_perform_vector_comparison_any
		<
			IncludeNonContained_,
			LhsVector_,
			Rhs_,
			std::equal_to<void>
		>(lhs_, rhs_);
	}
	template<bool IncludeNonContained_, class LhsVector_, class Rhs_>
	inline constexpr bool VectorComparisonAny_NotEqual(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_vector_funcs::_perform_vector_comparison_any
		<
			IncludeNonContained_,
			LhsVector_,
			Rhs_,
			std::not_equal_to<void>
		>(lhs_, rhs_);
	}

	template<bool IncludeNonContained_, class LhsVector_, class Rhs_>
	inline constexpr bool VectorComparisonAny_Less(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_vector_funcs::_perform_vector_comparison_any
		<
			IncludeNonContained_,
			LhsVector_,
			Rhs_,
			std::less<void>
		>(lhs_, rhs_);
	}
	template<bool IncludeNonContained_, class LhsVector_, class Rhs_>
	inline constexpr bool VectorComparisonAny_LessEqual(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_vector_funcs::_perform_vector_comparison_any
		<
			IncludeNonContained_,
			LhsVector_,
			Rhs_,
			std::less_equal<void>
		>(lhs_, rhs_);
	}

	template<bool IncludeNonContained_, class LhsVector_, class Rhs_>
	inline constexpr bool VectorComparisonAny_Greater(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_vector_funcs::_perform_vector_comparison_any
		<
			IncludeNonContained_,
			LhsVector_,
			Rhs_,
			std::greater<void>
		>(lhs_, rhs_);
	}
	template<bool IncludeNonContained_, class LhsVector_, class Rhs_>
	inline constexpr bool VectorComparisonAny_GreaterEqual(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return _underlying_vector_funcs::_perform_vector_comparison_any
		<
			IncludeNonContained_,
			LhsVector_,
			Rhs_,
			std::greater_equal<void>
		>(lhs_, rhs_);
	}

	template<std::size_t X_, std::size_t Y_, typename OutT_, class In_>
	inline constexpr EmuMath::Vector2<OutT_> VectorShuffle(const In_& in_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<In_>)
		{
			return Vector2<OutT_>
			(
				EmuMath::TMPHelpers::emu_vector_element_n<X_>(in_),
				EmuMath::TMPHelpers::emu_vector_element_n<Y_>(in_)
			);
		}
		else
		{
			static_assert(false, "Attempted to perform an EmuMath Vector shuffle while providing a non-EmuMath-Vector operand.");
			return Vector2<OutT_>();
		}
	}
	template<std::size_t X_, std::size_t Y_, std::size_t Z_, typename OutT_, class In_>
	inline constexpr EmuMath::Vector3<OutT_> VectorShuffle(const In_& in_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<In_>)
		{
			return Vector3<OutT_>
			(
				EmuMath::TMPHelpers::emu_vector_element_n<X_>(in_),
				EmuMath::TMPHelpers::emu_vector_element_n<Y_>(in_),
				EmuMath::TMPHelpers::emu_vector_element_n<Z_>(in_)
			);
		}
		else
		{
			static_assert(false, "Attempted to perform an EmuMath Vector shuffle while providing a non-EmuMath-Vector operand.");
			return Vector3<OutT_>();
		}
	}
	template<std::size_t X_, std::size_t Y_, std::size_t Z_, std::size_t W_, typename OutT_, class In_>
	inline constexpr EmuMath::Vector4<OutT_> VectorShuffle(const In_& in_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<In_>)
		{
			return Vector4<OutT_>
			(
				EmuMath::TMPHelpers::emu_vector_element_n<X_>(in_),
				EmuMath::TMPHelpers::emu_vector_element_n<Y_>(in_),
				EmuMath::TMPHelpers::emu_vector_element_n<Z_>(in_),
				EmuMath::TMPHelpers::emu_vector_element_n<W_>(in_)
			);
		}
		else
		{
			static_assert(false, "Attempted to perform an EmuMath Vector shuffle while providing a non-EmuMath-Vector operand.");
			return Vector4<OutT_>();
		}
	}

	template<std::size_t X_, std::size_t Y_, class In_>
	inline EmuMath::Vector2<typename In_::const_ref_value_type> VectorShuffledReference(const In_& in_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<In_>)
		{
			if constexpr (X_ < In_::size() && Y_ < In_::size())
			{
				return Vector2<typename In_::const_ref_value_type>
				(
					EmuMath::TMPHelpers::emu_vector_element_n<X_>(in_),
					EmuMath::TMPHelpers::emu_vector_element_n<Y_>(in_)
				);
			}
			else
			{
				static_assert
				(
					false,
					"Attemped to perform an EmuMath Vector shuffle reference with at least one invalid shuffle index. You can only reference indices contained in the passed Vector."
				);
				return Vector2<typename In_::const_ref_value_type>();
			}
		}
		else
		{
			static_assert(false, "Attempted to perform an EmuMath Vector shuffle reference while providing a non-EmuMath-Vector operand.");
			return Vector2<typename In_::const_ref_value_type>();
		}
	}
	template<std::size_t X_, std::size_t Y_, class In_>
	inline EmuMath::Vector2<typename In_::ref_value_type> VectorShuffledReference(In_& in_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<In_>)
		{
			if constexpr (X_ < In_::size() && Y_ < In_::size())
			{
				return Vector2<typename In_::ref_value_type>
				(
					EmuMath::TMPHelpers::emu_vector_element_n<X_>(in_),
					EmuMath::TMPHelpers::emu_vector_element_n<Y_>(in_)
				);
			}
			else
			{
				static_assert
				(
					false,
					"Attemped to perform an EmuMath Vector shuffle reference with at least one invalid shuffle index. You can only reference indices contained in the passed Vector."
				);
				return Vector2<typename In_::ref_value_type>();
			}
		}
		else
		{
			static_assert(false, "Attempted to perform an EmuMath Vector shuffle reference while providing a non-EmuMath-Vector operand.");
			return Vector2<typename In_::ref_value_type>();
		}
	}

	template<std::size_t X_, std::size_t Y_, std::size_t Z_, class In_>
	inline EmuMath::Vector3<typename In_::const_ref_value_type> VectorShuffledReference(const In_& in_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<In_>)
		{
			if constexpr (X_ < In_::size() && Y_ < In_::size() && Z_ < In_::size())
			{
				return Vector3<typename In_::const_ref_value_type>
				(
					EmuMath::TMPHelpers::emu_vector_element_n<X_>(in_),
					EmuMath::TMPHelpers::emu_vector_element_n<Y_>(in_),
					EmuMath::TMPHelpers::emu_vector_element_n<Z_>(in_)
				);
			}
			else
			{
				static_assert
				(
					false,
					"Attemped to perform an EmuMath Vector shuffle reference with at least one invalid shuffle index. You can only reference indices contained in the passed Vector."
				);
				return Vector3<typename In_::const_ref_value_type>();
			}
		}
		else
		{
			static_assert(false, "Attempted to perform an EmuMath Vector shuffle reference while providing a non-EmuMath-Vector operand.");
			return Vector3<typename In_::const_ref_value_type>();
		}
	}
	template<std::size_t X_, std::size_t Y_, std::size_t Z_, class In_>
	inline EmuMath::Vector3<typename In_::ref_value_type> VectorShuffledReference(In_& in_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<In_>)
		{
			if constexpr (X_ < In_::size() && Y_ < In_::size() && Z_ < In_::size())
			{
				return Vector3<typename In_::ref_value_type>
				(
					EmuMath::TMPHelpers::emu_vector_element_n<X_>(in_),
					EmuMath::TMPHelpers::emu_vector_element_n<Y_>(in_),
					EmuMath::TMPHelpers::emu_vector_element_n<Z_>(in_)
				);
			}
			else
			{
				static_assert
				(
					false,
					"Attemped to perform an EmuMath Vector shuffle reference with at least one invalid shuffle index. You can only reference indices contained in the passed Vector."
				);
				return Vector3<typename In_::ref_value_type>();
			}
		}
		else
		{
			static_assert(false, "Attempted to perform an EmuMath Vector shuffle reference while providing a non-EmuMath-Vector operand.");
			return Vector3<typename In_::ref_value_type>();
		}
	}

	template<std::size_t X_, std::size_t Y_, std::size_t Z_, std::size_t W_, class In_>
	inline EmuMath::Vector4<typename In_::const_ref_value_type> VectorShuffledReference(const In_& in_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<In_>)
		{
			if constexpr (X_ < In_::size() && Y_ < In_::size() && Z_ < In_::size() && W_ < In_::size())
			{
				return Vector4<typename In_::const_ref_value_type>
				(
					EmuMath::TMPHelpers::emu_vector_element_n<X_>(in_),
					EmuMath::TMPHelpers::emu_vector_element_n<Y_>(in_),
					EmuMath::TMPHelpers::emu_vector_element_n<Z_>(in_),
					EmuMath::TMPHelpers::emu_vector_element_n<W_>(in_)
				);
			}
			else
			{
				static_assert
				(
					false,
					"Attemped to perform an EmuMath Vector shuffle reference with at least one invalid shuffle index. You can only reference indices contained in the passed Vector."
				);
				return Vector4<typename In_::const_ref_value_type>();
			}
		}
		else
		{
			static_assert(false, "Attempted to perform an EmuMath Vector shuffle reference while providing a non-EmuMath-Vector operand.");
			return Vector4<typename In_::const_ref_value_type>();
		}
	}
	template<std::size_t X_, std::size_t Y_, std::size_t Z_, std::size_t W_, class In_>
	inline EmuMath::Vector4<typename In_::ref_value_type> VectorShuffledReference(In_& in_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<In_>)
		{
			if constexpr (X_ < In_::size() && Y_ < In_::size() && Z_ < In_::size() && W_ < In_::size())
			{
				return Vector4<typename In_::ref_value_type>
				(
					EmuMath::TMPHelpers::emu_vector_element_n<X_>(in_),
					EmuMath::TMPHelpers::emu_vector_element_n<Y_>(in_),
					EmuMath::TMPHelpers::emu_vector_element_n<Z_>(in_),
					EmuMath::TMPHelpers::emu_vector_element_n<W_>(in_)
				);
			}
			else
			{
				static_assert
				(
					false,
					"Attemped to perform an EmuMath Vector shuffle reference with at least one invalid shuffle index. You can only reference indices contained in the passed Vector."
				);
				return Vector4<typename In_::ref_value_type>();
			}
		}
		else
		{
			static_assert(false, "Attempted to perform an EmuMath Vector shuffle reference while providing a non-EmuMath-Vector operand.");
			return Vector4<typename In_::ref_value_type>();
		}
	}

	template<class LhsVector_, class Rhs_>
	inline LhsVector_& VectorSet(LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<LhsVector_>)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<Rhs_>)
			{
				using LhsScalar_ = typename LhsVector_::nonref_value_type_without_qualifiers;
				using RhsScalar_ = typename Rhs_::nonref_value_type_without_qualifiers;
				constexpr std::size_t SetSize_ = LhsVector_::size() <= Rhs_::size() ? LhsVector_::size() : Rhs_::size();

				if constexpr (std::is_same_v<LhsScalar_, RhsScalar_>)
				{
					if constexpr (SetSize_ >= 2 && SetSize_ <= 4)
					{
						lhs_.x = rhs_.x;
						lhs_.y = rhs_.y;
						if constexpr (SetSize_ >= 3)
						{
							lhs_.z = rhs_.z;
							if constexpr (SetSize_ >= 4)
							{
								lhs_.w = rhs_.w;
							}
						}
					}
					else
					{
						static_assert(false, "Attempted to set an EmuMath Vector with at least one invalidly sized EmuMath Vector operand.");
					}
				}
				else
				{
					lhs_.x = static_cast<LhsScalar_>(rhs_.x);
					lhs_.y = static_cast<LhsScalar_>(rhs_.y);
					if constexpr (SetSize_ >= 3)
					{
						lhs_.z = static_cast<LhsScalar_>(rhs_.z);
						if constexpr (SetSize_ >= 4)
						{
							lhs_.w = static_cast<LhsScalar_>(rhs_.w);
						}
					}
				}
			}
			else
			{
				constexpr std::size_t LhsSize_ = LhsVector_::size();
				if constexpr (LhsSize_ >= 2 && LhsSize_ <= 4)
				{
					using LhsScalar_ = typename LhsVector_::nonref_value_type_without_qualifiers;
					if constexpr (std::is_same_v<LhsScalar_, std::remove_cv_t<Rhs_>>)
					{
						lhs_.x = rhs_;
						lhs_.y = rhs_;
						if constexpr (LhsSize_ >= 3)
						{
							lhs_.z = rhs_;
							if constexpr (LhsSize_ >= 4)
							{
								lhs_.w = rhs_;
							}
						}
					}
					else
					{
						const LhsScalar_ cast_rhs_ = static_cast<LhsScalar_>(rhs_);
						lhs_.x = cast_rhs_;
						rhs_.y = cast_rhs_;
						if constexpr (LhsSize_ >= 3)
						{
							lhs_.z = cast_rhs_;
							if constexpr (LhsSize_ >= 4)
							{
								lhs_.w = cast_rhs_;
							}
						}
					}
				}
				else
				{
					static_assert(false, "Attempted to set an invalidly sized EmuMath Vector.");
				}
			}
		}
		else
		{
			static_assert(false, "Attempted to set an EmuMath Vector with a non-EmuMath-Vector left-hand operand.");
		}
		return lhs_;
	}

	template<class LhsVector_, typename RhsScalarX_, typename RhsScalarY_>
	inline LhsVector_& VectorSet(LhsVector_& lhs_, const RhsScalarX_& x_, const RhsScalarY_& y_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<LhsVector_>)
		{
			using LhsScalar_ = typename LhsVector_::nonref_value_type_without_qualifiers;
			if constexpr (std::is_same_v<LhsScalar_, std::remove_cv_t<RhsScalarX_>>)
			{
				lhs_.x = x_;
			}
			else
			{
				lhs_.x = static_cast<LhsScalar_>(x_);
			}

			if constexpr (std::is_same_v<LhsScalar_, std::remove_cv_t<RhsScalarY_>>)
			{
				lhs_.y = y_;
			}
			else
			{
				lhs_.y = static_cast<LhsScalar_>(y_);
			}
		}
		else
		{
			static_assert(false, "Attempted to set an EmuMath Vector with multiple scalar values, but provided a non-EmuMath-Vector left-hand operand.");
		}
		return lhs_;
	}
	template<class LhsVector_, typename RhsScalarX_, typename RhsScalarY_, typename RhsScalarZ_>
	inline LhsVector_& VectorSet(LhsVector_& lhs_, const RhsScalarX_& x_, const RhsScalarY_& y_, const RhsScalarZ_& z_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<LhsVector_>)
		{
			if constexpr (LhsVector_::size() >= 3)
			{
				using LhsScalar_ = typename LhsVector_::nonref_value_type_without_qualifiers;
				if constexpr (std::is_same_v<LhsScalar_, std::remove_cv_t<RhsScalarX_>>)
				{
					lhs_.x = x_;
				}
				else
				{
					lhs_.x = static_cast<LhsScalar_>(x_);
				}

				if constexpr (std::is_same_v<LhsScalar_, std::remove_cv_t<RhsScalarY_>>)
				{
					lhs_.y = y_;
				}
				else
				{
					lhs_.y = static_cast<LhsScalar_>(y_);
				}

				if constexpr (std::is_same_v<LhsScalar_, std::remove_cv_t<RhsScalarZ_>>)
				{
					lhs_.z = z_;
				}
				else
				{
					lhs_.z = static_cast<LhsScalar_>(z_);
				}
			}
			else
			{
				static_assert(false, "Attempted to set an EmuMath Vector using 3 scalar values, but the provided EmuMath Vector contains less than 3 values.");
			}
		}
		else
		{
			static_assert(false, "Attempted to set an EmuMath Vector with multiple scalar values, but provided a non-EmuMath-Vector left-hand operand.");
		}
		return lhs_;
	}
	template<class LhsVector_, typename RhsScalarX_, typename RhsScalarY_, typename RhsScalarZ_, typename RhsScalarW_>
	inline LhsVector_& VectorSet(LhsVector_& lhs_, const RhsScalarX_& x_, const RhsScalarY_& y_, const RhsScalarZ_& z_, const RhsScalarW_& w_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<LhsVector_>)
		{
			if constexpr (LhsVector_::size() >= 4)
			{
				using LhsScalar_ = typename LhsVector_::nonref_value_type_without_qualifiers;
				if constexpr (std::is_same_v<LhsScalar_, std::remove_cv_t<RhsScalarX_>>)
				{
					lhs_.x = x_;
				}
				else
				{
					lhs_.x = static_cast<LhsScalar_>(x_);
				}

				if constexpr (std::is_same_v<LhsScalar_, std::remove_cv_t<RhsScalarY_>>)
				{
					lhs_.y = y_;
				}
				else
				{
					lhs_.y = static_cast<LhsScalar_>(y_);
				}

				if constexpr (std::is_same_v<LhsScalar_, std::remove_cv_t<RhsScalarZ_>>)
				{
					lhs_.z = z_;
				}
				else
				{
					lhs_.z = static_cast<LhsScalar_>(z_);
				}

				if constexpr (std::is_same_v<LhsScalar_, std::remove_cv_t<RhsScalarZ_>>)
				{
					lhs_.z = z_;
				}
				else
				{
					lhs_.z = static_cast<LhsScalar_>(w_);
				}
			}
			else
			{
				static_assert(false, "Attempted to set an EmuMath Vector using 4 scalar values, but the provided EmuMath Vector contains less than 4 values.");
			}
		}
		else
		{
			static_assert(false, "Attempted to set an EmuMath Vector with multiple scalar values, but provided a non-EmuMath-Vector left-hand operand.");
		}
		return lhs_;
	}

	template<std::size_t OutSize_, typename OutFP_, class InVector_>
	inline constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutFP_>::type VectorReciprocal(const InVector_& in_)
	{
		using OutVector_ = typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutFP_>::type;
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<InVector_>)
		{
			if constexpr (std::is_floating_point_v<std::remove_cv_t<OutFP_>>)
			{
				constexpr OutFP_ fp_one_ = OutFP_(1);
				if constexpr (OutSize_ == 2)
				{
					return OutVector_
					(
						fp_one_ / in_.x,
						fp_one_ / in_.y
					);
				}
				else if constexpr (OutSize_ == 3)
				{
					if constexpr (InVector_::size() >= 3)
					{
						return OutVector_
						(
							fp_one_ / in_.x,
							fp_one_ / in_.y,
							fp_one_ / in_.z
						);
					}
					else
					{
						return OutVector_
						(
							fp_one_ / in_.x,
							fp_one_ / in_.y,
							OutFP_()
						);
					}
				}
				else if constexpr (OutSize_ == 4)
				{
					if constexpr (InVector_::size() >= 3)
					{
						if constexpr (InVector_::size() >= 4)
						{
							return OutVector_
							(
								fp_one_ / in_.x,
								fp_one_ / in_.y,
								fp_one_ / in_.z,
								fp_one_ / in_.w
							);
						}
						else
						{
							return OutVector_
							(
								fp_one_ / in_.x,
								fp_one_ / in_.y,
								fp_one_ / in_.z,
								OutFP_()
							);
						}
					}
					else
					{
						return OutVector_
						(
							fp_one_ / in_.x,
							fp_one_ / in_.y,
							OutFP_(),
							OutFP_()
						);
					}
				}
				else
				{
					static_assert(false, "Attempted to get the reciprocal of an EmuMath Vector with an invalidly sized output Vector.");
				}
			}
			else
			{
				static_assert(false, "Attempted to output the reciprocal of an EmuMath Vector as a Vector not containing floating points, which is required.");
				return OutVector_();
			}
		}
		else
		{
			static_assert(false, "Attempted to get the reciprocal of an EmuMath Vector while passing a non-EmuMath-Vector operand.");
			return OutVector_();
		}
	}

	template<typename OutT_, class InVector_>
	inline constexpr OutT_ VectorTotalSum(const InVector_& in_)
	{
		return _underlying_vector_funcs::_calculate_vector_total_emu<OutT_, InVector_, EmuCore::TMPHelpers::plus_diff_types>(in_);
	}
	template<typename OutT_, class InVector_>
	inline constexpr OutT_ VectorTotalProduct(const InVector_& in_)
	{
		return _underlying_vector_funcs::_calculate_vector_total_emu<OutT_, InVector_, EmuCore::TMPHelpers::multiplies_diff_types>(in_);
	}

	template<std::size_t OutSize_, typename OutT_, class InVector_>
	inline constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type VectorReverse(const InVector_& in_)
	{
		using OutVector_ = typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type;
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<OutVector_>)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<InVector_>)
			{
				if constexpr (OutVector_::size() == 2)
				{
					return OutVector_
					(
						-static_cast<OutT_>(in_.x),
						-static_cast<OutT_>(in_.y)
					);
				}
				else if constexpr (OutVector_::size() == 3)
				{
					return OutVector_
					(
						-static_cast<OutT_>(in_.x),
						-static_cast<OutT_>(in_.y),
						-static_cast<OutT_>(EmuMath::TMPHelpers::emu_vector_z(in_))
					);
				}
				else if constexpr (OutVector_::size() == 4)
				{
					return OutVector_
					(
						-static_cast<OutT_>(in_.x),
						-static_cast<OutT_>(in_.y),
						-static_cast<OutT_>(EmuMath::TMPHelpers::emu_vector_z(in_)),
						-static_cast<OutT_>(EmuMath::TMPHelpers::emu_vector_w(in_))
					);
				}
				else
				{
					static_assert(false, "Attempted to reverse an EmuMath Vector with an invalidly sized output Vector.");
					return OutVector_();
				}
			}
			else
			{
				static_assert(false, "Attempted to get the reverse of an EmuMath Vector with a non-EmuMath-Vector operand.");
				return OutVector_();
			}
		}
		else
		{
			static_assert(false, "Attempted to get the reverse of an EmuMath Vector with an invalid output Vector.");
			return OutVector_();
		}
	}

	template<typename OutT_, typename AT_, class BT_>
	inline constexpr EmuMath::Vector3<OutT_> VectorCrossProductV3(const EmuMath::Vector3<AT_>& a_, const EmuMath::Vector3<BT_>& b_)
	{
		return EmuMath::Vector3<OutT_>
		(
			(static_cast<OutT_>(a_.y) * b_.z) - (static_cast<OutT_>(a_.z) * b_.y),
			(static_cast<OutT_>(a_.z) * b_.x) - (static_cast<OutT_>(a_.x) * b_.z),
			(static_cast<OutT_>(a_.x) * b_.y) - (static_cast<OutT_>(a_.y) * b_.x)
		);
	}
	template<typename OutT_, typename AT_, class BT_>
	inline constexpr EmuMath::Vector3<OutT_> VectorCrossProductV3(const EmuMath::Vector3<AT_>& a_, const EmuMath::Vector4<BT_>& b_)
	{
		return EmuMath::Vector3<OutT_>
		(
			(static_cast<OutT_>(a_.y) * b_.z) - (static_cast<OutT_>(a_.z) * b_.y),
			(static_cast<OutT_>(a_.z) * b_.x) - (static_cast<OutT_>(a_.x) * b_.z),
			(static_cast<OutT_>(a_.x) * b_.y) - (static_cast<OutT_>(a_.y) * b_.x)
		);
	}

	template<typename OutT_, typename AT_, class BT_>
	inline constexpr EmuMath::Vector3<OutT_> VectorCrossProductV3(const EmuMath::Vector4<AT_>& a_, const EmuMath::Vector3<BT_>& b_)
	{
		return EmuMath::Vector3<OutT_>
		(
			(static_cast<OutT_>(a_.y) * b_.z) - (static_cast<OutT_>(a_.z) * b_.y),
			(static_cast<OutT_>(a_.z) * b_.x) - (static_cast<OutT_>(a_.x) * b_.z),
			(static_cast<OutT_>(a_.x) * b_.y) - (static_cast<OutT_>(a_.y) * b_.x)
		);
	}
	template<typename OutT_, typename AT_, class BT_>
	inline constexpr EmuMath::Vector3<OutT_> VectorCrossProductV3(const EmuMath::Vector4<AT_>& a_, const EmuMath::Vector4<BT_>& b_)
	{
		return EmuMath::Vector3<OutT_>
		(
			(static_cast<OutT_>(a_.y) * b_.z) - (static_cast<OutT_>(a_.z) * b_.y),
			(static_cast<OutT_>(a_.z) * b_.x) - (static_cast<OutT_>(a_.x) * b_.z),
			(static_cast<OutT_>(a_.x) * b_.y) - (static_cast<OutT_>(a_.y) * b_.x)
		);
	}
}

#endif
