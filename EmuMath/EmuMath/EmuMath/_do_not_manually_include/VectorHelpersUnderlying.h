#ifndef EMU_MATH_VECTOR_HELPERS_UNDERLYING_H_INC_
#define EMU_MATH_VECTOR_HELPERS_UNDERLYING_H_INC_

#include "EmuVectorTMPHelpers.h"
#include "../GeneralMath.h"
#include "../../EmuCore/TMPHelpers/Functors.h"
#include "../../EmuCore/TMPHelpers/TypeComparators.h"

namespace EmuMath
{
	template<typename T>
	struct Vector2;
	template<typename T>
	struct Vector3;
	template<typename T>
	struct Vector4;
}

/// <summary> Underlying functions used by EmuMath::Helper functions for vectors. These should not be used directly. </summary>
namespace EmuMath::Helpers::_underlying_vector_funcs
{
#pragma region ARITHMETIC
	/// <summary>
	/// <para> Performs an arithmetic operation using the provided Functor which takes two operands in its function operator. </para>
	/// <para> LhsVector elements will be cast to LhsElementAsScalar if it is different to the type that the LhsVector will provide. </para>
	/// <para> RhsVector will be treated as an EmuMath Vector. </para>
	/// </summary>
	/// <typeparam name="LhsVector">Type of Vector provided as the left-hand operand.</typeparam>
	/// <typeparam name="RhsVector">Type of Vector provided as the right-hand operand.</typeparam>
	/// <typeparam name="OutVector">Type of Vector that the result is to be output as.</typeparam>
	/// <typeparam name="LhsElementAsScalar">Scalar representation of a LhsVector element to be passed to the functor.</typeparam>
	/// <typeparam name="Func">Functor type to construct and execute the function operator of.</typeparam>
	/// <param name="lhs">Left-handed operand in the arithmetic operation.</param>
	/// <param name="rhs">Right-handed operand in the arithmetic operation.</param>
	/// <returns>Results of the arithmetic operation represented in an OutVector type.</returns>
	template<class OutVector, class LhsVector, class RhsVector, typename LhsElementAsScalar, class Func>
	inline OutVector _perform_vector_arithmetic_vector_rhs_with_types(const LhsVector& lhs, const RhsVector& rhs)
	{
		Func func = Func();
		if constexpr (OutVector::size() == 2)
		{
			if constexpr (std::is_same_v<typename LhsVector::nonref_value_type_without_qualifiers, LhsElementAsScalar>)
			{
				return OutVector
				(
					func(lhs.x, rhs.x),
					func(lhs.y, rhs.y)
				);
			}
			else
			{
				return OutVector
				(
					func(static_cast<LhsElementAsScalar>(lhs.x), rhs.x),
					func(static_cast<LhsElementAsScalar>(lhs.y), rhs.y)
				);
			}
		}
		else if constexpr (OutVector::size() == 3)
		{
			if constexpr (std::is_same_v<typename LhsVector::nonref_value_type_without_qualifiers, LhsElementAsScalar>)
			{
				return OutVector
				(
					func(lhs.x, rhs.x),
					func(lhs.y, rhs.y),
					func(EmuMath::TMPHelpers::emu_vector_z(lhs), EmuMath::TMPHelpers::emu_vector_z(rhs))
				);
			}
			else
			{
				return OutVector
				(
					func(static_cast<LhsElementAsScalar>(lhs.x), rhs.x),
					func(static_cast<LhsElementAsScalar>(lhs.y), rhs.y),
					func(static_cast<LhsElementAsScalar>(EmuMath::TMPHelpers::emu_vector_z(lhs)), EmuMath::TMPHelpers::emu_vector_z(rhs))
				);
			}
		}
		else if constexpr (OutVector::size() == 4)
		{
			if constexpr (std::is_same_v<typename LhsVector::nonref_value_type_without_qualifiers, LhsElementAsScalar>)
			{
				return OutVector
				(
					func(lhs.x, rhs.x),
					func(lhs.y, rhs.y),
					func(EmuMath::TMPHelpers::emu_vector_z(lhs), EmuMath::TMPHelpers::emu_vector_z(rhs)),
					func(EmuMath::TMPHelpers::emu_vector_w(lhs), EmuMath::TMPHelpers::emu_vector_w(rhs))
				);
			}
			else
			{
				return OutVector
				(
					func(static_cast<LhsElementAsScalar>(lhs.x), rhs.x),
					func(static_cast<LhsElementAsScalar>(lhs.y), rhs.y),
					func(static_cast<LhsElementAsScalar>(EmuMath::TMPHelpers::emu_vector_z(lhs)), EmuMath::TMPHelpers::emu_vector_z(rhs)),
					func(static_cast<LhsElementAsScalar>(EmuMath::TMPHelpers::emu_vector_w(lhs)), EmuMath::TMPHelpers::emu_vector_w(rhs))
				);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform arithmetic with EmuMath Vectors using an invalidly sized output Vector.");
			return OutVector();
		}
	}

	/// <summary>
	/// <para> Performs an arithmetic operation using the provided Functor which takes two operands in its function operator. </para>
	/// <para> LhsVector elements will be cast to LhsElementAsScalar if it is different to the type that the LhsVector will provide. </para>
	/// <para> Rhs will be treated as a scalar. </para>
	/// </summary>
	/// <typeparam name="LhsVector">Type of Vector provided as the left-hand operand.</typeparam>
	/// <typeparam name="RhsVector">Type of scalar provided as the right-hand operand.</typeparam>
	/// <typeparam name="OutVector">Type of Vector that the result is to be output as.</typeparam>
	/// <typeparam name="LhsElementAsScalar">Scalar representation of a LhsVector element to be passed to the functor.</typeparam>
	/// <typeparam name="Func">Functor type to construct and execute the function operator of.</typeparam>
	/// <param name="lhs">Left-handed operand in the arithmetic operation.</param>
	/// <param name="rhs">Right-handed operand in the arithmetic operation.</param>
	/// <returns>Results of the arithmetic operation represented in an OutVector type.</returns>
	template<class OutVector, class LhsVector, typename Rhs, typename LhsElementAsScalar, class Func>
	inline OutVector _perform_vector_arithmetic_scalar_rhs_with_types(const LhsVector& lhs, const Rhs& rhs)
	{
		Func func = Func();
		if constexpr (OutVector::size() == 2)
		{
			if constexpr (std::is_same_v<typename LhsVector::nonref_value_type_without_qualifiers, LhsElementAsScalar>)
			{
				return OutVector
				(
					func(lhs.x, rhs),
					func(lhs.y, rhs)
				);
			}
			else
			{
				return OutVector
				(
					func(static_cast<LhsElementAsScalar>(lhs.x), rhs),
					func(static_cast<LhsElementAsScalar>(lhs.y), rhs)
				);
			}
		}
		else if constexpr (OutVector::size() == 3)
		{
			if constexpr (std::is_same_v<typename LhsVector::nonref_value_type_without_qualifiers, LhsElementAsScalar>)
			{
				return OutVector
				(
					func(lhs.x, rhs),
					func(lhs.y, rhs),
					func(EmuMath::TMPHelpers::emu_vector_z(lhs), rhs)
				);
			}
			else
			{
				return OutVector
				(
					func(static_cast<LhsElementAsScalar>(lhs.x), rhs),
					func(static_cast<LhsElementAsScalar>(lhs.y), rhs),
					func(static_cast<LhsElementAsScalar>(EmuMath::TMPHelpers::emu_vector_z(lhs)), rhs)
				);
			}
		}
		else if constexpr (OutVector::size() == 4)
		{
			if constexpr (std::is_same_v<typename LhsVector::nonref_value_type_without_qualifiers, LhsElementAsScalar>)
			{
				return OutVector
				(
					func(lhs.x, rhs),
					func(lhs.y, rhs),
					func(EmuMath::TMPHelpers::emu_vector_z(lhs), rhs),
					func(EmuMath::TMPHelpers::emu_vector_w(lhs), rhs)
				);
			}
			else
			{
				return OutVector
				(
					func(static_cast<LhsElementAsScalar>(lhs.x), rhs),
					func(static_cast<LhsElementAsScalar>(lhs.y), rhs),
					func(static_cast<LhsElementAsScalar>(EmuMath::TMPHelpers::emu_vector_z(lhs)), rhs),
					func(static_cast<LhsElementAsScalar>(EmuMath::TMPHelpers::emu_vector_w(lhs)), rhs)
				);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform arithmetic with EmuMath Vector and scalar using an invalidly sized output Vector.");
			return OutVector();
		}
	}

	/// <summary>
	///		Executes an EmuMath Vector arithmetic operation with the provided Vector operands and Output Vector type,
	///		using a provided EmuCore arithmetic functor template to decide how arithmetic is performed.
	/// </summary>
	/// <typeparam name="LhsVector">Type of Vector provided as the left-hand operand.</typeparam>
	/// <typeparam name="RhsVector">Type of Vector provided as the right-hand operand.</typeparam>
	/// <typeparam name="OutVector">Type of Vector that the result is to be output as.</typeparam>
	/// <param name="lhs">Left-handed operand in the arithmetic operation.</param>
	/// <param name="rhs">Right-handed operand in the arithmetic operation.</param>
	/// <returns>Results of the arithmetic operation represented in an OutVector type.</returns>
	template<class OutVector, class LhsVector, class RhsVector, template<typename Lhs_, typename Rhs_, typename Out_> class Func_>
	inline OutVector _perform_vector_arithmetic_vector_rhs_emu(const LhsVector& lhs, const RhsVector& rhs)
	{
		using LhsNonref = typename LhsVector::nonref_value_type_without_qualifiers;
		using RhsNonref = typename RhsVector::nonref_value_type_without_qualifiers;
		using OutNonref = typename OutVector::nonref_value_type_without_qualifiers;
		if constexpr (EmuCore::TMPHelpers::is_any_floating_point_v<LhsNonref, RhsNonref, OutNonref>)
		{
			using LhsFP = EmuCore::TMPHelpers::best_floating_point_rep_t<LhsNonref>;
			using RhsFP = EmuCore::TMPHelpers::best_floating_point_rep_t<RhsNonref>;
			using OutFP = EmuCore::TMPHelpers::best_floating_point_rep_t<OutNonref>;
			using HighestFP = EmuCore::TMPHelpers::highest_byte_size_t<LhsFP, RhsFP, OutFP>;
			using Func = Func_<HighestFP, RhsFP, HighestFP>;
			return _perform_vector_arithmetic_vector_rhs_with_types<OutVector, LhsVector, RhsVector, HighestFP, Func>(lhs, rhs);
		}
		else
		{
			using HighestT = EmuCore::TMPHelpers::highest_byte_size_t<LhsNonref, RhsNonref, OutNonref>;
			using Func = Func_<HighestT, RhsNonref, HighestT>;
			return _perform_vector_arithmetic_vector_rhs_with_types<OutVector, LhsVector, RhsVector, HighestT, Func>(lhs, rhs);
		}
	}

	/// <summary>
	///		Executes an EmuMath Vector arithmetic operation with the provided left-hand Vector operand, right-hand scalar operand, and Output Vector type,
	///		using a provided EmuCore arithmetic functor template to decide how arithmetic is performed.
	/// </summary>
	/// <typeparam name="LhsVector">Type of Vector provided as the left-hand operand.</typeparam>
	/// <typeparam name="Rhs">Type of scalar provided as the right-hand operand.</typeparam>
	/// <typeparam name="OutVector">Type of Vector that the result is to be output as.</typeparam>
	/// <param name="lhs">Left-handed operand in the arithmetic operation.</param>
	/// <param name="rhs">Right-handed operand in the arithmetic operation.</param>
	/// <returns>Results of the arithmetic operation represented in an OutVector type.</returns>
	template<class OutVector, class LhsVector, class Rhs, template<typename Lhs_, typename Rhs_, typename Out_> class Func_>
	inline OutVector _perform_vector_arithmetic_scalar_rhs_emu(const LhsVector& lhs, const Rhs& rhs)
	{
		using LhsNonref = typename LhsVector::nonref_value_type_without_qualifiers;
		using RhsNonref = std::remove_cv_t<Rhs>;
		using OutNonref = typename OutVector::nonref_value_type_without_qualifiers;
		if constexpr (EmuCore::TMPHelpers::is_any_floating_point_v<LhsNonref, RhsNonref, OutNonref>)
		{
			using LhsFP = EmuCore::TMPHelpers::best_floating_point_rep_t<LhsNonref>;
			using RhsFP = EmuCore::TMPHelpers::best_floating_point_rep_t<RhsNonref>;
			using OutFP = EmuCore::TMPHelpers::best_floating_point_rep_t<OutNonref>;
			using HighestFP = EmuCore::TMPHelpers::highest_byte_size_t<LhsFP, RhsFP, OutFP>;
			using Func = Func_<HighestFP, RhsFP, HighestFP>;
			return _perform_vector_arithmetic_scalar_rhs_with_types<OutVector, LhsVector, Rhs, HighestFP, Func>(lhs, rhs);
		}
		else
		{
			using HighestT = EmuCore::TMPHelpers::highest_byte_size_t<LhsNonref, RhsNonref, OutNonref>;
			using Func = Func_<HighestT, RhsNonref, HighestT>;
			return _perform_vector_arithmetic_scalar_rhs_with_types<OutVector, LhsVector, Rhs, HighestT, Func>(lhs, rhs);
		}
	}

	template<typename OutT_, class InVector_, template<typename Lhs__, typename Rhs__, typename Out__> class FuncTemplate_>
	inline constexpr OutT_ _calculate_vector_total_emu(const InVector_& in_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<InVector_>)
		{
			using InScalar_ = typename InVector_::nonref_value_type_without_qualifiers;
			using HighestT_ = EmuCore::TMPHelpers::highest_byte_size_t<std::remove_cv_t<OutT_>, InScalar_>;
			using Func_ = FuncTemplate_<HighestT_, HighestT_, OutT_>;
			Func_ func = Func_();
			if constexpr (InVector_::size() == 2)
			{
				return func
				(
					static_cast<HighestT_>(in_.x),
					static_cast<HighestT_>(in_.y)
				);
			}
			else if constexpr (InVector_::size() == 3)
			{
				return func
				(
					func
					(
						static_cast<HighestT_>(in_.x),
						static_cast<HighestT_>(in_.y)
					),
					static_cast<HighestT_>(in_.z)
				);
			}
			else if constexpr (InVector_::size() == 4)
			{
				return func
				(
					func
					(
						func
						(
							static_cast<HighestT_>(in_.x),
							static_cast<HighestT_>(in_.y)
						),
						static_cast<HighestT_>(in_.z)
					),
					static_cast<HighestT_>(in_.w)
				);
			}
			else
			{
				static_assert(false, "Attempted to calculate a total of an invalidly sized EmuMath Vector.");
			}
		}
		else
		{
			static_assert(false, "Attempted to calculate a total of an EmuMath Vector, but passed a non-EmuMath-Vector operand.");
			return OutT_();
		}
	}
#pragma endregion

#pragma region BITWISE
	template<class OutVector, class LhsVector, class RhsVector, template<class LhsT_, class RhsT_, class OutT_> class Func_>
	inline OutVector _perform_vector_bitwise_op_vector_rhs_emu(const LhsVector& lhs, const RhsVector& rhs)
	{
		using Func = Func_
			<
			typename LhsVector::nonref_value_type_without_qualifiers,
			typename RhsVector::nonref_value_type_without_qualifiers,
			typename OutVector::value_type
			>;
		Func func = Func();

		if constexpr (OutVector::size() == 2)
		{
			return OutVector
			(
				func(lhs.x, rhs.x),
				func(lhs.y, rhs.y)
			);
		}
		else if constexpr (OutVector::size() == 3)
		{
			return OutVector
			(
				func(lhs.x, rhs.x),
				func(lhs.y, rhs.y),
				func(EmuMath::TMPHelpers::emu_vector_z(lhs), EmuMath::TMPHelpers::emu_vector_z(rhs))
			);
		}
		else if constexpr (OutVector::size() == 4)
		{
			return OutVector
			(
				func(lhs.x, rhs.x),
				func(lhs.y, rhs.y),
				func(EmuMath::TMPHelpers::emu_vector_z(lhs), EmuMath::TMPHelpers::emu_vector_z(rhs)),
				func(EmuMath::TMPHelpers::emu_vector_w(lhs), EmuMath::TMPHelpers::emu_vector_w(rhs))
			);
		}
		else
		{
			static_assert(false, "Attempted to perform bitwise operation with EmuMath Vector and another EmuMath Vector using an invalidly sized output Vector.");
		}
	}

	template<class OutVector, class LhsVector, typename Rhs, template<class LhsT_, class RhsT_, class OutT_> class Func_>
	inline OutVector _perform_vector_bitwise_op_scalar_rhs_emu(const LhsVector& lhs, const Rhs& rhs)
	{
		using Func = Func_
			<
			typename LhsVector::nonref_value_type_without_qualifiers,
			std::remove_cv_t<Rhs>,
			typename OutVector::value_type
			>;
		Func func = Func();

		if constexpr (OutVector::size() == 2)
		{
			return OutVector
			(
				func(lhs.x, rhs),
				func(lhs.y, rhs)
			);
		}
		else if constexpr (OutVector::size() == 3)
		{
			return OutVector
			(
				func(lhs.x, rhs),
				func(lhs.y, rhs),
				func(EmuMath::TMPHelpers::emu_vector_z(lhs), rhs)
			);
		}
		else if constexpr (OutVector::size() == 4)
		{
			return OutVector
			(
				func(lhs.x, rhs.x),
				func(lhs.y, rhs.y),
				func(EmuMath::TMPHelpers::emu_vector_z(lhs), rhs),
				func(EmuMath::TMPHelpers::emu_vector_w(lhs), rhs)
			);
		}
		else
		{
			static_assert(false, "Attempted to perform bitwise operation with EmuMath Vector and a scalar using an invalidly sized output Vector.");
		}
	}

	template<class OutVector_, class InVector_>
	inline constexpr OutVector_ _perform_vector_bitwise_not(const InVector_ in_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<OutVector_>)
		{
			if constexpr (OutVector_::size() == 2)
			{
				return OutVector_
				(
					~(in_.x),
					~(in_.y)
				);
			}
			else if constexpr (OutVector_::size() == 3)
			{
				return OutVector_
				(
					~(in_.x),
					~(in_.y),
					~(EmuMath::TMPHelpers::emu_vector_z(in_))
				);
			}
			else if constexpr (OutVector_::size() == 4)
			{
				return OutVector_
				(
					~(in_.x),
					~(in_.y),
					~(EmuMath::TMPHelpers::emu_vector_z(in_)),
					~(EmuMath::TMPHelpers::emu_vector_w(in_))
				);
			}
			else
			{
				static_assert(false, "Attempted to perform a bitwise not on an EmuMath Vector with an invalidly sized output Vector.");
				return OutVector_();
			}
		}
		else
		{
			static_assert(false, "Attempted to perform a bitwise not on an EmuMath Vector with a non-EmuMath-Vector output type.");
			return OutVector_();
		}
	}
#pragma endregion

#pragma region VECTORWISE SHIFTS
	template<class OutVector, class EmuVector_, class LeftShifter_, class RightShifter_>
	inline constexpr OutVector _perform_branching_vectorwise_left_shift(const EmuVector_& inVector, const std::size_t numShifts)
	{
		using Scalar = typename OutVector::value_type;
		constexpr std::size_t ScalarSize_ = sizeof(Scalar);
		constexpr std::size_t NumScalarBits = ScalarSize_ * CHAR_BIT;
		constexpr std::size_t NumScalarBitsX2 = NumScalarBits * 2;

		LeftShifter_ leftShifter = LeftShifter_();
		RightShifter_ rightShifter = RightShifter_();
		if constexpr (EmuVector_::size() == 2)
		{
			if (numShifts < NumScalarBits)
			{
				return OutVector
				(
					leftShifter(inVector.x, numShifts) | rightShifter(inVector.y, (NumScalarBits - numShifts)),
					leftShifter(inVector.y, numShifts)
				);
			}
			else if (numShifts < NumScalarBitsX2)
			{
				return OutVector
				(
					leftShifter(inVector.y, (numShifts - NumScalarBits)),
					0
				);
			}
			else
			{
				return OutVector(0, 0);
			}
		}
		else if constexpr (EmuVector_::size() == 3)
		{
			constexpr std::size_t NumScalarBitsX3 = NumScalarBits * 3;
			if (numShifts < NumScalarBits)
			{
				const std::size_t neighbourShiftsRight = (NumScalarBits - numShifts);
				return OutVector
				(
					leftShifter(inVector.x, numShifts) | rightShifter(inVector.y, neighbourShiftsRight),
					leftShifter(inVector.y, numShifts) | rightShifter(inVector.z, neighbourShiftsRight),
					leftShifter(inVector.z, numShifts)
				);
			}
			else if (numShifts < NumScalarBitsX2)
			{
				const std::size_t neighbourShiftsLeft = numShifts - NumScalarBits;
				return OutVector
				(
					leftShifter(inVector.y, neighbourShiftsLeft) | rightShifter(inVector.z, (NumScalarBitsX2 - numShifts)),
					leftShifter(inVector.z, neighbourShiftsLeft),
					0
				);
			}
			else if (numShifts < NumScalarBitsX3)
			{
				return OutVector
				(
					leftShifter(inVector.z, (numShifts - NumScalarBitsX2)),
					0,
					0
				);
			}
			else
			{
				return OutVector(0, 0, 0);
			}
		}
		else if constexpr (EmuVector_::size() == 4)
		{
			constexpr std::size_t NumScalarBitsX3 = NumScalarBits * 3;
			constexpr std::size_t NumScalarBitsX4 = NumScalarBits * 4;

			if (numShifts < NumScalarBits)
			{
				const std::size_t neighbourShiftsRight = NumScalarBits - numShifts;
				return OutVector
				(
					leftShifter(inVector.x, numShifts) | rightShifter(inVector.y, neighbourShiftsRight),
					leftShifter(inVector.y, numShifts) | rightShifter(inVector.z, neighbourShiftsRight),
					leftShifter(inVector.z, numShifts) | rightShifter(inVector.w, neighbourShiftsRight),
					leftShifter(inVector.w, numShifts)
				);
			}
			else if (numShifts < NumScalarBitsX2)
			{
				const std::size_t neighbourShiftsLeft = numShifts - NumScalarBits;
				const std::size_t secondNeighbourShiftsRight = NumScalarBitsX2 - numShifts;
				return OutVector
				(
					leftShifter(inVector.y, neighbourShiftsLeft) | rightShifter(inVector.z, secondNeighbourShiftsRight),
					leftShifter(inVector.z, neighbourShiftsLeft) | rightShifter(inVector.w, secondNeighbourShiftsRight),
					leftShifter(inVector.w, neighbourShiftsLeft),
					0
				);
			}
			else if (numShifts < NumScalarBitsX3)
			{
				const std::size_t secondNeighbourShiftsLeft = numShifts - NumScalarBitsX2;
				const std::size_t thirdNeighbourShiftsRight = NumScalarBitsX3 - numShifts;
				return OutVector
				(
					leftShifter(inVector.z, secondNeighbourShiftsLeft) | rightShifter(inVector.w, thirdNeighbourShiftsRight),
					leftShifter(inVector.w, secondNeighbourShiftsLeft),
					0,
					0
				);

			}
			else if (numShifts < NumScalarBitsX4)
			{
				const std::size_t thirdNeighbourShiftsLeft = numShifts - NumScalarBitsX3;
				return OutVector
				(
					leftShifter(inVector.w, thirdNeighbourShiftsLeft),
					0,
					0,
					0
				);
			}
			else
			{
				return OutVector(0, 0, 0, 0);
			}
		}
	}

	template<class OutVector, class EmuVector_, class RightShifter_, class LeftShifter_>
	inline constexpr OutVector _perform_branching_vectorwise_right_shift(const EmuVector_& inVector, const std::size_t numShifts)
	{
		using Scalar = typename OutVector::value_type;
		constexpr std::size_t ScalarSize_ = sizeof(Scalar);
		constexpr std::size_t NumScalarBits = ScalarSize_ * CHAR_BIT;
		constexpr std::size_t NumScalarBitsX2 = NumScalarBits * 2;

		RightShifter_ mainShifter = RightShifter_();
		LeftShifter_ oppositeShifter = LeftShifter_();
		if constexpr (EmuVector_::size() == 2)
		{
			if (numShifts < NumScalarBits)
			{
				return OutVector
				(
					mainShifter(inVector.x, numShifts),
					mainShifter(inVector.y, numShifts) | oppositeShifter(inVector.x, (NumScalarBits - numShifts))
				);
			}
			else if (numShifts < NumScalarBitsX2)
			{
				return OutVector
				(
					0,
					mainShifter(inVector.x, (numShifts - NumScalarBits))
				);
			}
			else
			{
				return OutVector(0, 0);
			}
		}
		else if constexpr (EmuVector_::size() == 3)
		{
			constexpr std::size_t NumScalarBitsX3 = NumScalarBits * 3;
			if (numShifts < NumScalarBits)
			{
				const std::size_t neighbourShiftsLeft = (NumScalarBits - numShifts);
				return OutVector
				(
					mainShifter(inVector.x, numShifts),
					mainShifter(inVector.y, numShifts) | oppositeShifter(inVector.x, neighbourShiftsLeft),
					mainShifter(inVector.z, numShifts) | oppositeShifter(inVector.y, neighbourShiftsLeft)
				);
			}
			else if (numShifts < NumScalarBitsX2)
			{
				const std::size_t neighbourShiftsRight = numShifts - NumScalarBits;
				return OutVector
				(
					0,
					mainShifter(inVector.x, neighbourShiftsRight),
					mainShifter(inVector.y, neighbourShiftsRight) | oppositeShifter(inVector.x, (NumScalarBitsX2 - numShifts))
				);
			}
			else if (numShifts < NumScalarBitsX3)
			{
				return OutVector
				(
					0,
					0,
					mainShifter(inVector.x, (numShifts - NumScalarBitsX2))
				);
			}
			else
			{
				return OutVector(0, 0, 0);
			}
		}
		else if constexpr (EmuVector_::size() == 4)
		{
			constexpr std::size_t NumScalarBitsX3 = NumScalarBits * 3;
			constexpr std::size_t NumScalarBitsX4 = NumScalarBits * 4;
			if (numShifts < NumScalarBits)
			{
				const std::size_t neighbourShiftsLeft = NumScalarBits - numShifts;
				return OutVector
				(
					mainShifter(inVector.x, numShifts),
					mainShifter(inVector.y, numShifts) | oppositeShifter(inVector.x, neighbourShiftsLeft),
					mainShifter(inVector.z, numShifts) | oppositeShifter(inVector.y, neighbourShiftsLeft),
					mainShifter(inVector.w, numShifts) | oppositeShifter(inVector.z, neighbourShiftsLeft)
				);
			}
			else if (numShifts < NumScalarBitsX2)
			{
				const std::size_t neighbourShiftsRight = numShifts - NumScalarBits;
				const std::size_t secondNeighbourShiftsLeft = NumScalarBitsX2 - numShifts;
				//system("pause");
				return OutVector
				(
					0,
					mainShifter(inVector.x, neighbourShiftsRight),
					mainShifter(inVector.y, neighbourShiftsRight) | oppositeShifter(inVector.x, secondNeighbourShiftsLeft),
					mainShifter(inVector.z, neighbourShiftsRight) | oppositeShifter(inVector.y, secondNeighbourShiftsLeft)
				);
			}
			else if (numShifts < NumScalarBitsX3)
			{
				const std::size_t secondNeighbourShiftsRight = numShifts - NumScalarBitsX2;
				const std::size_t thirdNeighbourShiftsLeft = NumScalarBitsX3 - numShifts;
				return OutVector
				(
					0,
					0,
					mainShifter(inVector.x, secondNeighbourShiftsRight),
					mainShifter(inVector.y, secondNeighbourShiftsRight) | oppositeShifter(inVector.x, thirdNeighbourShiftsLeft)
				);
			}
			else if (numShifts < NumScalarBitsX4)
			{
				const std::size_t thirdNeighbourShiftsRight = numShifts - NumScalarBitsX3;
				return OutVector
				(
					0,
					0,
					0,
					mainShifter(inVector.x, thirdNeighbourShiftsRight)
				);
			}
			else
			{
				return OutVector(0, 0, 0, 0);
			}
		}
	}

	template<class OutVector, class EmuVector_, class TargetShifter_, class OppositeShifter_, bool IsLeft_>
	inline constexpr OutVector _perform_branching_vectorwise_shift(const EmuVector_& inVector, const std::size_t numShifts)
	{
		if constexpr (IsLeft_)
		{
			return _perform_branching_vectorwise_left_shift<OutVector, EmuVector_, TargetShifter_, OppositeShifter_>(inVector, numShifts);
		}
		else
		{
			return _perform_branching_vectorwise_right_shift<OutVector, EmuVector_, TargetShifter_, OppositeShifter_>(inVector, numShifts);
		}
	}

	template
		<
		class OutVector,
		class EmuVector_,
		template<class Lhs__, class Rhs__, class Out__> class TargetShiftTemplate_,
		template<class Lhs__, class Rhs__, class Out__> class OppositeShiftTemplate_,
		bool IsLeft_
		>
		inline constexpr OutVector _perform_vectorwise_shift_emu(const EmuVector_& inVector, const std::size_t numShifts)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<EmuVector_>)
		{
			using Scalar = typename OutVector::value_type;
			constexpr std::size_t ScalarSize_ = sizeof(Scalar);
			constexpr std::size_t NumScalarBits = ScalarSize_ * CHAR_BIT;
			constexpr std::size_t NumScalarBitsX2 = NumScalarBits * 2;

			if constexpr (std::is_unsigned_v<Scalar>)
			{
				if constexpr (EmuVector_::size() >= 2 && EmuVector_::size() <= 4)
				{
					using TargetShift = TargetShiftTemplate_<Scalar, std::size_t, Scalar>;
					using OppositeShift = OppositeShiftTemplate_<Scalar, std::size_t, Scalar>;
					return _perform_branching_vectorwise_shift<OutVector, EmuVector_, TargetShift, OppositeShift, IsLeft_>(inVector, numShifts);
				}
				else
				{
					static_assert(false, "Attempted to perform a vectorwise left shift on an invalidly sized EmuMath Vector type.");
					return OutVector();
				}
			}
			else
			{
				using UintReinterpretation = EmuCore::TMPHelpers::uint_of_size_t<ScalarSize_>;
				if constexpr (!std::is_same_v<UintReinterpretation, std::false_type>)
				{
					using TargetShift = TargetShiftTemplate_<UintReinterpretation, std::size_t, UintReinterpretation>;
					using OppositeShift = OppositeShiftTemplate_<UintReinterpretation, std::size_t, UintReinterpretation>;
					using UintVec_ = EmuMath::TMPHelpers::emu_vector_from_size_t<EmuVector_::size(), UintReinterpretation>;
					UintVec_ reinterpretedVec = UintVec_();
					memcpy(&reinterpretedVec.x, &inVector.x, ScalarSize_);
					memcpy(&reinterpretedVec.y, &inVector.y, ScalarSize_);
					if constexpr (UintVec_::size() >= 3)
					{
						memcpy(&reinterpretedVec.z, &inVector.z, ScalarSize_);
						if constexpr (UintVec_::size() >= 4)
						{
							memcpy(&reinterpretedVec.w, &inVector.w, ScalarSize_);
						}
					}
					reinterpretedVec = _perform_branching_vectorwise_shift<UintVec_, UintVec_, TargetShift, OppositeShift, IsLeft_>(reinterpretedVec, numShifts);

					OutVector out = OutVector();
					memcpy(&out.x, &reinterpretedVec.x, ScalarSize_);
					memcpy(&out.y, &reinterpretedVec.y, ScalarSize_);
					if constexpr (UintVec_::size() >= 3)
					{
						memcpy(&out.z, &reinterpretedVec.z, ScalarSize_);
						if constexpr (UintVec_::size() >= 4)
						{
							memcpy(&out.w, &reinterpretedVec.w, ScalarSize_);
						}
					}
					return out;
				}
				else
				{
					static_assert(false, "Attempted to perform a vectorwise shift on an EmuMath Vector whose contained types cannot be accurately reinterpreted.");
				}
			}
		}
		else
		{
			static_assert(false, "Attempted to perform a vectorwise shift on non-EmuMath-Vector type.");
			return EmuVector_();
		}
	}
#pragma endregion

#pragma region ROUNDING
	template<class OutVector_, class InVector_, template<typename In__, typename Out__> class Rounder_>
	inline OutVector_ _perform_vector_round_emu(const InVector_& in_)
	{
		using Rounder = Rounder_<typename InVector_::nonref_value_type, typename OutVector_::nonref_value_type>;
		Rounder rounder = Rounder();
		if constexpr (OutVector_::size() == 2)
		{
			return OutVector_
			(
				rounder(in_.x),
				rounder(in_.y)
			);
		}
		else if constexpr (OutVector_::size() == 3)
		{
			if constexpr (OutVector_::size() >= 3)
			{
				return OutVector_
				(
					rounder(in_.x),
					rounder(in_.y),
					rounder(in_.z)
				);
			}
			else
			{
				using OutT = typename OutVector_::value_type;
				return OutVector_
				(
					rounder(in_.x),
					rounder(in_.y),
					OutT()
				);
			}
		}
		else if constexpr (OutVector_::size() == 4)
		{
			using OutT = typename OutVector_::value_type;
			if constexpr (OutVector_::size() >= 4)
			{
				return OutVector_
				(
					rounder(in_.x),
					rounder(in_.y),
					rounder(in_.z),
					rounder(in_.w)
				);
			}
			else if constexpr (OutVector_::size() >= 3)
			{
				return OutVector_
				(
					rounder(in_.x),
					rounder(in_.y),
					rounder(in_.z),
					OutT()
				);
			}
			else
			{
				using OutT = typename OutVector_::value_type;
				const OutT zero_ = OutT();
				return OutVector_
				(
					rounder(in_.x),
					rounder(in_.y),
					zero_,
					zero_
				);
			}
		}
		else
		{
			static_assert(false, "Attempted to round an EmuMath Vector with an invalidly sized output Vector.");
		}
	}

	template<class OutVector_, class InVector_, template<typename In__, typename Out__> class Rounder_>
	inline constexpr OutVector_ _perform_vector_constexpr_round_emu(const InVector_& in_)
	{
		using InScalar_ = typename InVector_::nonref_value_type_without_qualifiers;
		using OutScalar_ = typename OutVector_::nonref_value_type_without_qualifiers;
		using Rounder = Rounder_<InScalar_, OutScalar_>;
		Rounder rounder = Rounder();
		if constexpr (OutVector_::size() == 2)
		{
			return OutVector_
			(
				rounder.ConstexprRound(in_.x),
				rounder.ConstexprRound(in_.y)
			);
		}
		else if constexpr (OutVector_::size() == 3)
		{
			if constexpr (OutVector_::size() >= 3)
			{
				return OutVector_
				(
					rounder.ConstexprRound(in_.x),
					rounder.ConstexprRound(in_.y),
					rounder.ConstexprRound(in_.z)
				);
			}
			else
			{
				return OutVector_
				(
					rounder.ConstexprRound(in_.x),
					rounder.ConstexprRound(in_.y),
					OutScalar_()
				);
			}
		}
		else if constexpr (OutVector_::size() == 4)
		{
			if constexpr (OutVector_::size() >= 4)
			{
				return OutVector_
				(
					rounder.ConstexprRound(in_.x),
					rounder.ConstexprRound(in_.y),
					rounder.ConstexprRound(in_.z),
					rounder.ConstexprRound(in_.w)
				);
			}
			else if constexpr (OutVector_::size() >= 3)
			{
				return OutVector_
				(
					rounder.ConstexprRound(in_.x),
					rounder.ConstexprRound(in_.y),
					rounder.ConstexprRound(in_.z),
					OutScalar_()
				);
			}
			else
			{
				const OutScalar_ zero_ = OutScalar_();
				return OutVector_
				(
					rounder.ConstexprRound(in_.x),
					rounder.ConstexprRound(in_.y),
					zero_,
					zero_
				);
			}
		}
		else
		{
			static_assert(false, "Attempted to round an EmuMath Vector with an invalidly sized output Vector.");
		}
	}
#pragma endregion

#pragma region MIN_MAX
	template<std::size_t Index_, class OutScalar_, class In_, class Min_, class Max_>
	inline constexpr OutScalar_ _perform_vector_min_and_max_comparison(const In_& in_, const Min_& min_, const Max_& max_)
	{
		using InScalar_ = std::conditional_t<(Index_ < In_::size()), typename In_::const_ref_value_type, typename In_::nonref_value_type_without_qualifiers>;
		const InScalar_ in_n_ = EmuMath::TMPHelpers::emu_vector_element_n<Index_>(in_);
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<Min_>)
		{
			if constexpr (Index_ < Min_::size())
			{
				typename Min_::const_ref_value_type min_n_ = EmuMath::TMPHelpers::emu_vector_element_n<Index_>(min_);
				if constexpr (Index_ < Max_::size())
				{
					typename Max_::const_ref_value_type max_n_ = EmuMath::TMPHelpers::emu_vector_element_n<Index_>(max_);
					return
						(
							(in_n_ < min_n_) ? static_cast<OutScalar_>(min_n_) :
							(in_n_ > max_n_) ? static_cast<OutScalar_>(max_n_) : static_cast<OutScalar_>(in_n_)
							);
				}
				else
				{
					return
						(
							(in_n_ < min_n_) ? static_cast<OutScalar_>(min_n_) : static_cast<OutScalar_>(in_n_)
							);
				}
			}
			else
			{
				if constexpr (Index_ < Max_::size())
				{
					typename Max_::const_ref_value_type max_n_ = EmuMath::TMPHelpers::emu_vector_element_n<Index_>(max_);
					return
						(
							(in_n_ > max_n_) ? static_cast<OutScalar_>(max_n_) : static_cast<OutScalar_>(in_n_)
							);
				}
				else
				{
					return static_cast<OutScalar_>(in_n_);
				}
			}
		}
		else
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<Max_>)
			{
				if constexpr (Index_ < Max_::size())
				{
					typename Max_::const_ref_value_type max_n_ = EmuMath::TMPHelpers::emu_vector_element_n<Index_>(max_);
					return
						(
							(in_n_ < min_) ? static_cast<OutScalar_>(min_) :
							(in_n_ > max_n_) ? static_cast<OutScalar_>(max_n_) : static_cast<OutScalar_>(in_n_)
							);
				}
				else
				{
					return
						(
							(in_n_ < min_) ? static_cast<OutScalar_>(min_) : static_cast<OutScalar_>(in_n_)
							);
				}
			}
			else
			{
				return
					(
						(in_n_ < min_) ? static_cast<OutScalar_>(min_) :
						(in_n_ > max_) ? static_cast<OutScalar_>(max_) : static_cast<OutScalar_>(in_n_)
						);
			}
		}
	}

	template<typename OutT, class InVector_, class Func_>
	inline constexpr OutT _perform_vector_min_or_max_get(const InVector_& in_)
	{
		Func_ cmp_ = Func_();
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<InVector_>)
		{
			if constexpr (InVector_::size() == 2)
			{
				return static_cast<OutT>(cmp_(in_.x, in_.y) ? in_.x : in_.y);
			}
			else if constexpr (InVector_::size() == 3)
			{
				if (cmp_(in_.x, in_.y))
				{
					return static_cast<OutT>(cmp_(in_.x, in_.z) ? in_.x : in_.z);
				}
				else
				{
					return static_cast<OutT>(cmp_(in_.y, in_.z) ? in_.y : in_.z);
				}
			}
			else if constexpr (InVector_::size() == 4)
			{
				if (cmp_(in_.x, in_.y))
				{
					if (cmp_(in_.x, in_.z))
					{
						return static_cast<OutT>(cmp_(in_.x, in_.w) ? in_.x : in_.w);
					}
					else
					{
						return static_cast<OutT>(cmp_(in_.z, in_.w) ? in_.z : in_.w);
					}
				}
				else
				{
					if (cmp_(in_.y, in_.z))
					{
						return static_cast<OutT>(cmp_(in_.y, in_.w) ? in_.y : in_.w);
					}
					else
					{
						return static_cast<OutT>(cmp_(in_.z, in_.w) ? in_.z : in_.w);
					}
				}
			}
			else
			{
				static_assert(false, "Attempted to get the min/max value of an invalidly sized EmuMath Vector.");
			}
		}
		else
		{
			static_assert(false, "Attempted to get the min/max value of an EmuMath Vector, but the passed operand was not an EmuMath Vector.");
			return OutT();
		}
	}
#pragma endregion

#pragma region CLAMPING
	template<class OutVector_, class InVector_, class MinOrMaxVector_, class CmpFunc_>
	inline constexpr OutVector_ _perform_vector_clamp_min_or_max_with_vector(const InVector_& in_, const MinOrMaxVector_& minOrMax_)
	{
		using OutScalar_ = typename OutVector_::value_type;
		CmpFunc_ cmp_ = CmpFunc_();
		if constexpr (OutVector_::size() == 2)
		{
			return OutVector_
			(
				cmp_(in_.x, minOrMax_.x) ? static_cast<OutScalar_>(minOrMax_.x) : static_cast<OutScalar_>(in_.x),
				cmp_(in_.y, minOrMax_.y) ? static_cast<OutScalar_>(minOrMax_.y) : static_cast<OutScalar_>(in_.y)
			);
		}
		else if constexpr (OutVector_::size() == 3)
		{
			if constexpr (MinOrMaxVector_::size() >= 3)
			{
				const auto inZ_ = EmuMath::TMPHelpers::emu_vector_z(in_);
				return OutVector_
				(
					cmp_(in_.x, minOrMax_.x) ? static_cast<OutScalar_>(minOrMax_.x) : static_cast<OutScalar_>(in_.x),
					cmp_(in_.y, minOrMax_.y) ? static_cast<OutScalar_>(minOrMax_.y) : static_cast<OutScalar_>(in_.y),
					cmp_(inZ_, minOrMax_.z) ? static_cast<OutScalar_>(minOrMax_.z) : static_cast<OutScalar_>(inZ_)
				);
			}
			else
			{
				return OutVector_
				(
					cmp_(in_.x, minOrMax_.x) ? static_cast<OutScalar_>(minOrMax_.x) : static_cast<OutScalar_>(in_.x),
					cmp_(in_.y, minOrMax_.y) ? static_cast<OutScalar_>(minOrMax_.y) : static_cast<OutScalar_>(in_.y),
					EmuMath::TMPHelpers::emu_vector_z(in_)
				);
			}
		}
		else if constexpr (OutVector_::size() == 4)
		{
			if constexpr (MinOrMaxVector_::size() >= 3)
			{
				const auto inZ_ = EmuMath::TMPHelpers::emu_vector_z(in_);
				if constexpr (MinOrMaxVector_::size() >= 4)
				{
					const auto inW_ = EmuMath::TMPHelpers::emu_vector_w(in_);
					return OutVector_
					(
						cmp_(in_.x, minOrMax_.x) ? static_cast<OutScalar_>(minOrMax_.x) : static_cast<OutScalar_>(in_.x),
						cmp_(in_.y, minOrMax_.y) ? static_cast<OutScalar_>(minOrMax_.y) : static_cast<OutScalar_>(in_.y),
						cmp_(inZ_, minOrMax_.z) ? static_cast<OutScalar_>(minOrMax_.z) : static_cast<OutScalar_>(inZ_),
						cmp_(inW_, minOrMax_.w) ? static_cast<OutScalar_>(minOrMax_.w) : static_cast<OutScalar_>(inW_)
					);
				}
				else
				{
					return OutVector_
					(
						cmp_(in_.x, minOrMax_.x) ? static_cast<OutScalar_>(minOrMax_.x) : static_cast<OutScalar_>(in_.x),
						cmp_(in_.y, minOrMax_.y) ? static_cast<OutScalar_>(minOrMax_.y) : static_cast<OutScalar_>(in_.y),
						cmp_(inZ_, minOrMax_.z) ? static_cast<OutScalar_>(minOrMax_.z) : static_cast<OutScalar_>(inZ_),
						EmuMath::TMPHelpers::emu_vector_w(in_)
					);
				}
			}
			else
			{
				return OutVector_
				(
					cmp_(in_.x, minOrMax_.x) ? static_cast<OutScalar_>(minOrMax_.x) : static_cast<OutScalar_>(in_.x),
					cmp_(in_.y, minOrMax_.y) ? static_cast<OutScalar_>(minOrMax_.y) : static_cast<OutScalar_>(in_.y),
					EmuMath::TMPHelpers::emu_vector_z(in_),
					EmuMath::TMPHelpers::emu_vector_w(in_)
				);
			}
		}
		else
		{
			static_assert(false, "Attempted to clamp an EmuMath Vector to minimum or maximum values with an invalidly sized output Vector.");
			return OutVector_();
		}
	}

	template<class OutVector_, class InVector_, typename MinOrMaxScalar_, class CmpFunc_>
	inline constexpr OutVector_ _perform_vector_clamp_min_or_max_with_scalar(const InVector_& in_, const MinOrMaxScalar_& minOrMax_)
	{
		using OutScalar_ = typename OutVector_::value_type;
		CmpFunc_ cmp_ = CmpFunc_();
		if constexpr (OutVector_::size() == 2)
		{
			return OutVector_
			(
				cmp_(in_.x, minOrMax_) ? static_cast<OutScalar_>(minOrMax_) : static_cast<OutScalar_>(in_.x),
				cmp_(in_.y, minOrMax_) ? static_cast<OutScalar_>(minOrMax_) : static_cast<OutScalar_>(in_.y)
			);
		}
		else if constexpr (OutVector_::size() == 3)
		{
			const auto inZ_ = EmuMath::TMPHelpers::emu_vector_z(in_);
			return OutVector_
			(
				cmp_(in_.x, minOrMax_) ? static_cast<OutScalar_>(minOrMax_) : static_cast<OutScalar_>(in_.x),
				cmp_(in_.y, minOrMax_) ? static_cast<OutScalar_>(minOrMax_) : static_cast<OutScalar_>(in_.y),
				cmp_(inZ_, minOrMax_) ? static_cast<OutScalar_>(minOrMax_) : static_cast<OutScalar_>(inZ_)
			);
		}
		else if constexpr (OutVector_::size() == 4)
		{
			const auto inZ_ = EmuMath::TMPHelpers::emu_vector_z(in_);
			const auto inW_ = EmuMath::TMPHelpers::emu_vector_w(in_);
			return OutVector_
			(
				cmp_(in_.x, minOrMax_) ? static_cast<OutScalar_>(minOrMax_) : static_cast<OutScalar_>(in_.x),
				cmp_(in_.y, minOrMax_) ? static_cast<OutScalar_>(minOrMax_) : static_cast<OutScalar_>(in_.y),
				cmp_(inZ_, minOrMax_) ? static_cast<OutScalar_>(minOrMax_) : static_cast<OutScalar_>(inZ_),
				cmp_(inW_, minOrMax_) ? static_cast<OutScalar_>(minOrMax_) : static_cast<OutScalar_>(inW_)
			);
		}
		else
		{
			static_assert(false, "Attempted to clamp an EmuMath Vector to minimum or maximum values with an invalidly sized output Vector.");
		}
	}

	template<class OutVector_, class InVector_, class MinT_, class CmpFunc_>
	inline constexpr OutVector_ _perform_vector_min_or_max_clamp(const InVector_& in_, const MinT_& minOrMax_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<OutVector_>)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<InVector_>)
			{
				if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<MinT_>)
				{
					return _perform_vector_clamp_min_or_max_with_vector<OutVector_, InVector_, MinT_, CmpFunc_>(in_, minOrMax_);
				}
				else
				{
					return _perform_vector_clamp_min_or_max_with_scalar<OutVector_, InVector_, MinT_, CmpFunc_>(in_, minOrMax_);
				}
			}
			else
			{
				static_assert(false, "Attempted to perform an EmuMath Vector clamp, but passed a non-EmuMath-Vector input operand.");
				return OutVector_();
			}
		}
		else
		{
			static_assert(false, "Attempted to clamp an EmuMath Vector clamp with an invalid output Vector.");
			return OutVector_();
		}
	}

	template<class OutVector_, class InVector_, typename MinScalar_, typename MaxScalar_>
	inline constexpr OutVector_ _perform_vector_clamp_min_and_max(const InVector_& in_, const MinScalar_& min_, const MaxScalar_& max_)
	{
		using OutScalar_ = typename OutVector_::value_type;

		if constexpr (OutVector_::size() == 2)
		{
			return OutVector_
			(
				_perform_vector_min_and_max_comparison<0, OutScalar_>(in_, min_, max_),
				_perform_vector_min_and_max_comparison<1, OutScalar_>(in_, min_, max_)
			);
		}
		else if constexpr (OutVector_::size() == 3)
		{
			return OutVector_
			(
				_perform_vector_min_and_max_comparison<0, OutScalar_>(in_, min_, max_),
				_perform_vector_min_and_max_comparison<1, OutScalar_>(in_, min_, max_),
				_perform_vector_min_and_max_comparison<2, OutScalar_>(in_, min_, max_)
			);
		}
		else if constexpr (OutVector_::size() == 4)
		{
			return OutVector_
			(
				_perform_vector_min_and_max_comparison<0, OutScalar_>(in_, min_, max_),
				_perform_vector_min_and_max_comparison<1, OutScalar_>(in_, min_, max_),
				_perform_vector_min_and_max_comparison<2, OutScalar_>(in_, min_, max_),
				_perform_vector_min_and_max_comparison<3, OutScalar_>(in_, min_, max_)
			);

		}
		else
		{
			static_assert(false, "Attempted to clamp an EmuMath Vector to minimum or maximum values with an invalidly sized output Vector.");
			return OutVector_();
		}
	}
#pragma endregion

#pragma region INTERPOLATION
	template<std::size_t Index_, class OutScalar_, class VectorA_, class B_, class OutT_>
	inline constexpr OutScalar_ _calculate_vector_lerp_val(const VectorA_& a_, const B_& b_, const OutT_& t_)
	{
		const auto a_n_ = EmuMath::TMPHelpers::emu_vector_element_n<Index_>(a_);
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<B_>)
		{
			if constexpr (Index_ < B_::size())
			{
				if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<OutT_>)
				{
					if constexpr (Index_ < OutT_::size())
					{
						return static_cast<OutScalar_>
							(
								a_n_ +
								(EmuMath::TMPHelpers::emu_vector_element_n<Index_>(b_) - a_n_) *
								EmuMath::TMPHelpers::emu_vector_element_n<Index_>(t_)
								);
					}
					else
					{
						return static_cast<OutScalar_>(a_n_);
					}
				}
				else
				{
					return static_cast<OutScalar_>(a_n_ + (EmuMath::TMPHelpers::emu_vector_element_n<Index_>(b_) - a_n_) * t_);
				}
			}
			else
			{
				if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<OutT_>)
				{
					if constexpr (Index_ < OutT_::size())
					{
						return static_cast<OutScalar_>(a_n_ - (a_n_ * EmuMath::TMPHelpers::emu_vector_element_n<Index_>(t_)));
					}
					else
					{
						return static_cast<OutScalar_>(a_n_);
					}
				}
				else
				{
					return static_cast<OutScalar_>(a_n_ - (a_n_ * t_));
				}
			}
		}
		else
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<OutT_>)
			{
				if constexpr (Index_ < OutT_::size())
				{
					return static_cast<OutScalar_>(a_n_ + (b_ - a_n_) * EmuMath::TMPHelpers::emu_vector_element_n<Index_>(t_));
				}
				else
				{
					return static_cast<OutScalar_>(a_n_);
				}
			}
			else
			{
				return static_cast<OutScalar_>(a_n_ + (b_ - a_n_) * t_);
			}
		}
	}

	template<class OutVector_, class VectorA_, class B_, class OutT_>
	inline constexpr OutVector_ _perform_vector_lerp(const VectorA_& a_, const B_& b_, const OutT_& t_)
	{
		using OutScalar_ = typename OutVector_::value_type;
		if constexpr (OutVector_::size() == 2)
		{
			return OutVector_
			(
				_calculate_vector_lerp_val<0, OutScalar_>(a_, b_, t_),
				_calculate_vector_lerp_val<1, OutScalar_>(a_, b_, t_)
			);
		}
		else if constexpr (OutVector_::size() == 3)
		{
			return OutVector_
			(
				_calculate_vector_lerp_val<0, OutScalar_>(a_, b_, t_),
				_calculate_vector_lerp_val<1, OutScalar_>(a_, b_, t_),
				_calculate_vector_lerp_val<2, OutScalar_>(a_, b_, t_)
			);
		}
		else if constexpr (OutVector_::size() == 4)
		{
			return OutVector_
			(
				_calculate_vector_lerp_val<0, OutScalar_>(a_, b_, t_),
				_calculate_vector_lerp_val<1, OutScalar_>(a_, b_, t_),
				_calculate_vector_lerp_val<2, OutScalar_>(a_, b_, t_),
				_calculate_vector_lerp_val<3, OutScalar_>(a_, b_, t_)
			);
		}
		else
		{
			static_assert(false, "Attempted to perform linear interpolation (lerp) with EmuMath Vector using an invalidly sized output Vector.");
			return OutVector_();
		}
	}
#pragma endregion

#pragma region MAGNITUDE
	template<typename OutT, class EmuVector_>
	inline constexpr OutT _calculate_square_magnitude(const EmuVector_& vector_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<EmuVector_>)
		{
			using Scalar = typename EmuVector_::nonref_value_type_without_qualifiers;
			using HighestT = EmuCore::TMPHelpers::highest_byte_size_t<OutT, Scalar>;
			using CastT = std::conditional_t
				<
				EmuCore::TMPHelpers::is_any_floating_point_v<OutT, Scalar>,
				EmuCore::TMPHelpers::best_floating_point_rep_t<HighestT>,
				std::conditional_t
				<
				EmuCore::TMPHelpers::is_any_signed_v<OutT, Scalar>,
				EmuCore::TMPHelpers::best_signed_int_rep_t<HighestT>,
				EmuCore::TMPHelpers::best_unsigned_int_rep_t<HighestT>
				>
				>;
			if constexpr (EmuVector_::size() == 2)
			{
				if constexpr (std::is_same_v<Scalar, CastT>)
				{
					if constexpr (std::is_same_v<OutT, CastT>)
					{
						return
							(
								(vector_.x * vector_.x) +
								(vector_.y * vector_.y)
								);
					}
					else
					{
						return static_cast<OutT>
							(
								(vector_.x * vector_.x) +
								(vector_.y * vector_.y)
								);
					}
				}
				else
				{
					if constexpr (std::is_same_v<OutT, CastT>)
					{
						return
							(
								(static_cast<CastT>(vector_.x) * vector_.x) +
								(static_cast<CastT>(vector_.y) * vector_.y)
								);
					}
					else
					{
						return static_cast<OutT>
							(
								(static_cast<CastT>(vector_.x) * vector_.x) +
								(static_cast<CastT>(vector_.y) * vector_.y)
								);
					}
				}
			}
			else if constexpr (EmuVector_::size() == 3)
			{
				if constexpr (std::is_same_v<Scalar, CastT>)
				{
					if constexpr (std::is_same_v<OutT, CastT>)
					{
						return
							(
								(vector_.x * vector_.x) +
								(vector_.y * vector_.y) +
								(vector_.z * vector_.z)
								);
					}
					else
					{
						return static_cast<OutT>
							(
								(vector_.x * vector_.x) +
								(vector_.y * vector_.y) +
								(vector_.z * vector_.z)
								);
					}
				}
				else
				{
					if constexpr (std::is_same_v<OutT, CastT>)
					{
						return
							(
								(static_cast<CastT>(vector_.x) * vector_.x) +
								(static_cast<CastT>(vector_.y) * vector_.y) +
								(static_cast<CastT>(vector_.z) * vector_.z)
								);
					}
					else
					{
						return static_cast<OutT>
							(
								(static_cast<CastT>(vector_.x) * vector_.x) +
								(static_cast<CastT>(vector_.y) * vector_.y) +
								(static_cast<CastT>(vector_.z) * vector_.z)
								);
					}
				}
			}
			else if constexpr (EmuVector_::size() == 4)
			{
				if constexpr (std::is_same_v<Scalar, CastT>)
				{
					if constexpr (std::is_same_v<OutT, CastT>)
					{
						return
							(
								(vector_.x * vector_.x) +
								(vector_.y * vector_.y) +
								(vector_.z * vector_.z) +
								(vector_.w * vector_.w)
								);
					}
					else
					{
						return static_cast<OutT>
							(
								(vector_.x * vector_.x) +
								(vector_.y * vector_.y) +
								(vector_.z * vector_.z) +
								(vector_.w * vector_.w)
								);
					}
				}
				else
				{
					if constexpr (std::is_same_v<OutT, CastT>)
					{
						return
							(
								(static_cast<CastT>(vector_.x) * vector_.x) +
								(static_cast<CastT>(vector_.y) * vector_.y) +
								(static_cast<CastT>(vector_.z) * vector_.z) +
								(static_cast<CastT>(vector_.w) * vector_.w)
								);
					}
					else
					{
						return static_cast<OutT>
							(
								(static_cast<CastT>(vector_.x) * vector_.x) +
								(static_cast<CastT>(vector_.y) * vector_.y) +
								(static_cast<CastT>(vector_.z) * vector_.z) +
								(static_cast<CastT>(vector_.w) * vector_.w)
								);
					}
				}
			}
			else
			{
				static_assert(false, "Attempted to get the Square Magnitude of an EmuMath Vector of an invalid size.");
			}
		}
		else
		{
			static_assert(false, "Attempted to get the Square Magnitude of an EmuMath Vector, but passed a type that is not an EmuMath Vector.");
			return OutT();
		}
	}

	template<typename OutFP_, class EmuVector_>
	inline constexpr OutFP_ _calculate_magnitude_constexpr(const EmuVector_& vector_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<EmuVector_>)
		{
			using VecInfo_ = typename EmuVector_::info_type;
			if constexpr (VecInfo_::has_floating_point_values)
			{
				return EmuMath::SqrtConstexpr<OutFP_, long double>(_calculate_square_magnitude<long double>(vector_));
			}
			else
			{
				return EmuMath::SqrtConstexpr<OutFP_, std::uint64_t>(_calculate_square_magnitude<std::uint64_t>(vector_));
			}
		}
		else
		{
			static_assert(false, "Attempted to get the magnitude of an EmuMath Vector, but passed a type that is not an EmuMath Vector.");
			return OutFP_();
		}
	}

	template<typename Out_, class EmuVector_>
	inline Out_ _calculate_magnitude(const EmuVector_& vector_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<EmuVector_>)
		{
			using StrippedOut_ = std::remove_cv_t<Out_>;
			using VecInfo_ = typename EmuVector_::info_type;
			using SqrMag = std::conditional_t<VecInfo_::has_floating_point_values, long double, std::uint64_t>;
			const SqrMag sqrMag_ = _calculate_square_magnitude<SqrMag>(vector_);
			if constexpr (std::is_same_v<StrippedOut_, SqrMag>)
			{
				return sqrtl(static_cast<long double>(sqrMag_));
			}
			else
			{
				return static_cast<Out_>(sqrtl(static_cast<long double>(sqrMag_)));
			}
		}
		else
		{
			static_assert(false, "Attempted to get the magnitude of an EmuMath Vector, but passed a type that is not an EmuMath Vector.");
			return Out_();
		}
	}
#pragma endregion

#pragma region COMPARISON
	template<class LhsVector_, class Rhs_, class Func_>
	inline constexpr bool _perform_vector_magnitude_comparison_std(const LhsVector_& lhs, const Rhs_& rhs)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<LhsVector_>)
		{
			Func_ func = Func_();
			using LhsInfo = typename LhsVector_::info_type;
			using LhsScalar = typename LhsVector_::nonref_value_type_without_qualifiers;
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<Rhs_>)
			{
				using RhsInfo = typename Rhs_::info_Type;
				if constexpr (LhsInfo::has_floating_point_values || RhsInfo::has_floating_point_values)
				{
					return func(_calculate_square_magnitude<long double>(lhs), _calculate_square_magnitude<long double>(rhs));
				}
				else
				{
					return func(_calculate_square_magnitude<std::uint64_t>(lhs), _calculate_square_magnitude<std::uint64_t>(rhs));
				}
			}
			else
			{
				if constexpr (LhsInfo::has_floating_point_values)
				{
					return func(_calculate_square_magnitude<long double>(lhs), rhs);
				}
				else
				{
					return func(_calculate_square_magnitude<std::uint64_t>(lhs), rhs);
				}
			}
		}
		else
		{
			static_assert(false, "Attempted to perform an EmuMath magnitude comparison using a non-EmuMath-Vector operand.");
			return false;
		}
	}

	template<class LhsVector_, class RhsVector_, class Func>
	inline constexpr bool _perform_vector_overall_comparison_with_vector(const LhsVector_& lhs, const RhsVector_& rhs)
	{
		using LhsInfo = typename LhsVector_::info_type;
		using RhsInfo = typename RhsVector_::info_type;
		Func func = Func();
		if constexpr (LhsVector_::size() == 2)
		{
			if constexpr (RhsVector_::size() == 2)
			{
				return func(lhs.x, rhs.x) && func(lhs.y, rhs.y);
			}
			else if constexpr (RhsVector_::size() == 3)
			{
				return func(lhs.x, rhs.x) && func(lhs.y, rhs.y) && func(LhsInfo::value_zero, rhs.z);
			}
			else if constexpr (RhsVector_::size() == 4)
			{
				return func(lhs.x, rhs.x) && func(lhs.y, rhs.y) && func(LhsInfo::value_zero, rhs.z) && func(LhsInfo::value_zero, rhs.w);
			}
			else
			{
				static_assert(false, "Attempted to perform a Vector comparison with EmuMath Vectors using an invalidly sized right-hand EmuMath Vector operand.");
			}
		}
		else if constexpr (LhsVector_::size() == 3)
		{
			if constexpr (RhsVector_::size() == 2)
			{
				return func(lhs.x, rhs.x) && func(lhs.y, rhs.y) && func(lhs.z, RhsInfo::value_zero);
			}
			else if constexpr (RhsVector_::size() == 3)
			{
				return func(lhs.x, rhs.x) && func(lhs.y, rhs.y) && func(lhs.z, rhs.z);
			}
			else if constexpr (RhsVector_::size() == 4)
			{
				return func(lhs.x, rhs.x) && func(lhs.y, rhs.y) && func(lhs.z, rhs.z) && func(LhsInfo::value_zero, rhs.w);
			}
			else
			{
				static_assert(false, "Attempted to perform a Vector comparison with EmuMath Vectors using an invalidly sized right-hand EmuMath Vector operand.");
			}
		}
		else if constexpr (LhsVector_::size() == 4)
		{
			if constexpr (RhsVector_::size() == 2)
			{
				return func(lhs.x, rhs.x) && func(lhs.y, rhs.y) && func(lhs.z, RhsInfo::value_zero) && func(lhs.w, RhsInfo::value_zero);
			}
			else if constexpr (RhsVector_::size() == 3)
			{
				return func(lhs.x, rhs.x) && func(lhs.y, rhs.y) && func(lhs.z, rhs.z) && func(lhs.w, RhsInfo::value_zero);
			}
			else if constexpr (RhsVector_::size() == 4)
			{
				return func(lhs.x, rhs.x) && func(lhs.y, rhs.y) && func(lhs.z, rhs.z) && func(lhs.w, rhs.w);
			}
			else
			{
				static_assert(false, "Attempted to perform a Vector comparison with EmuMath Vectors using an invalidly sized right-hand EmuMath Vector operand.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform a Vector comparison with EmuMath Vectors using an invalidly sized left-hand EmuMath Vector operand.");
		}
	}

	template<class LhsVector_, class RhsVector_, class Func>
	inline constexpr bool _perform_vector_overall_comparison_with_scalar(const LhsVector_& lhs, const RhsVector_& rhs)
	{
		using LhsInfo = typename LhsVector_::info_type;
		Func func = Func();
		if constexpr (LhsVector_::size() == 2)
		{
			return func(lhs.x, rhs) && func(lhs.y, rhs);
		}
		else if constexpr (LhsVector_::size() == 3)
		{
			return func(lhs.x, rhs) && func(lhs.y, rhs) && func(lhs.z, rhs);
		}
		else if constexpr (LhsVector_::size() == 4)
		{
			return func(lhs.x, rhs) && func(lhs.y, rhs) && func(lhs.z, rhs) && func(lhs.w, rhs);
		}
		else
		{
			static_assert(false, "Attempted to perform a Vector comparison with an EmuMath Vector and a scalar using an invalidly sized left-hand EmuMath Vector operand.");
		}
	}

	template<std::size_t NumComparisons, class LhsVector_, class RhsVector_, class Func>
	inline constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<NumComparisons, bool>::type _perform_vector_per_element_comparison_with_vector
	(
		const LhsVector_& lhs,
		const RhsVector_& rhs
	)
	{
		if constexpr (NumComparisons >= 2 && NumComparisons <= 4)
		{
			using OutVector = EmuMath::TMPHelpers::emu_vector_from_size_t<NumComparisons, bool>;
			if constexpr (EmuCore::TMPHelpers::are_all_check<EmuMath::TMPHelpers::is_emu_vector, LhsVector_, RhsVector_>::value)
			{
				Func func = Func();
				if constexpr (NumComparisons == 2)
				{
					return OutVector
					(
						func(lhs.x, rhs.x),
						func(lhs.y, rhs.y)
					);
				}
				else if constexpr (NumComparisons == 3)
				{
					return OutVector
					(
						func(lhs.x, rhs.x),
						func(lhs.y, rhs.y),
						func(EmuMath::TMPHelpers::emu_vector_z(lhs), EmuMath::TMPHelpers::emu_vector_z(rhs))
					);
				}
				else
				{
					return OutVector
					(
						func(lhs.x, rhs.x),
						func(lhs.y, rhs.y),
						func(EmuMath::TMPHelpers::emu_vector_z(lhs), EmuMath::TMPHelpers::emu_vector_z(rhs)),
						func(EmuMath::TMPHelpers::emu_vector_w(lhs), EmuMath::TMPHelpers::emu_vector_w(rhs))
					);
				}
			}
			else
			{
				static_assert(false, "Attempted to perform a per-element comparison of EmuMath Vectors using a non-EmuMath-Vector operand.");
				return OutVector();
			}
		}
		else
		{
			static_assert(false, "Attempted to perform a comparison of EmuMath Vectors with an invalid number of comparisons; only 2, 3, or 4 comparisons are valid.");
			return {};
		}
	}

	template<class LhsVector_, class RhsT_, std::size_t RhsVectorSize_>
	inline constexpr bool _perform_vector_comparison_equal(const LhsVector_& lhs, const EmuMath::TMPHelpers::emu_vector_from_size_t<RhsVectorSize_, RhsT_>& rhs)
	{
		using RhsVector_ = EmuMath::TMPHelpers::emu_vector_from_size_t<RhsVectorSize_, RhsT_>;
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<LhsVector_>)
		{
			return _perform_vector_overall_comparison_with_vector<LhsVector_, RhsVector_, std::equal_to<void>>(lhs, rhs);
		}
		else
		{
			static_assert(false, "Attempted to perform an EmuMath Vector comparison (Equal) using a non-EmuMath-Vector operand.");
			return false;
		}
	}

	template<class LhsVector_, class RhsT_, std::size_t RhsVectorSize_>
	inline constexpr bool _perform_vector_comparison_not_equal(const LhsVector_& lhs, const EmuMath::TMPHelpers::emu_vector_from_size_t<RhsVectorSize_, RhsT_>& rhs)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<LhsVector_>)
		{
			return !_perform_vector_overall_comparison_with_vector<LhsVector_, Vector2<RhsT_>, std::equal_to<void>>(lhs, rhs);
		}
		else
		{
			static_assert(false, "Attempted to perform an EmuMath Vector comparison (Not Equal) using a non-EmuMath-Vector operand.");
			return false;
		}
	}

	template<class OutVector_, class LhsEmuVector_, class Rhs_, class Func_>
	inline constexpr OutVector_ _perform_per_element_comparison(const LhsEmuVector_& lhs_, const Rhs_& rhs_)
	{
		Func_ cmp_ = Func_();
		if constexpr (OutVector_::size() == 2)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<Rhs_>)
			{
				return OutVector_
				(
					cmp_(lhs_.x, rhs_.x),
					cmp_(lhs_.y, rhs_.y)
				);
			}
			else
			{
				return OutVector_
				(
					cmp_(lhs_.x, rhs_),
					cmp_(lhs_.y, rhs_)
				);
			}
		}
		else if constexpr (OutVector_::size() == 3)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<Rhs_>)
			{
				return OutVector_
				(
					cmp_(lhs_.x, rhs_.x),
					cmp_(lhs_.y, rhs_.y),
					cmp_(EmuMath::TMPHelpers::emu_vector_z(lhs_), EmuMath::TMPHelpers::emu_vector_z(rhs_))
				);
			}
			else
			{
				return OutVector_
				(
					cmp_(lhs_.x, rhs_),
					cmp_(lhs_.y, rhs_),
					cmp_(EmuMath::TMPHelpers::emu_vector_z(lhs_), rhs_)
				);
			}
		}
		else if constexpr (OutVector_::size() == 4)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<Rhs_>)
			{
				return OutVector_
				(
					cmp_(lhs_.x, rhs_.x),
					cmp_(lhs_.y, rhs_.y),
					cmp_(EmuMath::TMPHelpers::emu_vector_z(lhs_), EmuMath::TMPHelpers::emu_vector_z(rhs_)),
					cmp_(EmuMath::TMPHelpers::emu_vector_w(lhs_), EmuMath::TMPHelpers::emu_vector_w(rhs_))
				);
			}
			else
			{
				return OutVector_
				(
					cmp_(lhs_.x, rhs_),
					cmp_(lhs_.y, rhs_),
					cmp_(EmuMath::TMPHelpers::emu_vector_z(lhs_), rhs_),
					cmp_(EmuMath::TMPHelpers::emu_vector_w(lhs_), rhs_)
				);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform a per-element EmuMath Vector comparison with an invalidly sized output Vector.");
		}
	}

	template<bool IncludeNonContained_, class LhsVector_, class Rhs_, class Func_>
	inline constexpr bool _perform_vector_comparison_all(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<LhsVector_>)
		{
			Func_ cmp_ = Func_();
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<Rhs_>)
			{
				constexpr std::size_t used_size_ =
					(
						(IncludeNonContained_) ?
						(LhsVector_::size() >= Rhs_::size()) ? LhsVector_::size() : Rhs_::size() :
						(LhsVector_::size() <= Rhs_::size()) ? LhsVector_::size() : Rhs_::size()
						);
				if constexpr (used_size_ == 2)
				{
					return cmp_(lhs_.x, rhs_.x) && cmp_(lhs_.y, rhs_.y);
				}
				else if constexpr (used_size_ == 3)
				{
					return
						(
							cmp_(lhs_.x, rhs_.x) &&
							cmp_(lhs_.y, rhs_.y) &&
							cmp_(EmuMath::TMPHelpers::emu_vector_z(lhs_), EmuMath::TMPHelpers::emu_vector_z(rhs_))
							);
				}
				else if constexpr (used_size_ == 4)
				{
					return
						(
							cmp_(lhs_.x, rhs_.x) &&
							cmp_(lhs_.y, rhs_.y) &&
							cmp_(EmuMath::TMPHelpers::emu_vector_z(lhs_), EmuMath::TMPHelpers::emu_vector_z(rhs_)) &&
							cmp_(EmuMath::TMPHelpers::emu_vector_w(lhs_), EmuMath::TMPHelpers::emu_vector_w(rhs_))
							);
				}
				else
				{
					static_assert(false, "Attempted to perform an all-element comparison of EmuMath Vectors with at least one invalidly sized EmuMath Vector.");
				}
			}
			else
			{
				if constexpr (LhsVector_::size() == 2)
				{
					return cmp_(lhs_.x, rhs_) && cmp_(lhs_.y, rhs_);
				}
				else if constexpr (LhsVector_::size() == 3)
				{
					return cmp_(lhs_.x, rhs_) && cmp_(lhs_.y, rhs_) && cmp_(lhs_.z, rhs_);
				}
				else if constexpr (LhsVector_::size() == 4)
				{
					return cmp_(lhs_.x, rhs_) && cmp_(lhs_.y, rhs_) && cmp_(lhs_.z, rhs_) && cmp_(lhs_.w, rhs_);
				}
				else
				{
					static_assert(false, "Attempted to perform an all-element comparison with an invalidly sized EmuMath Vector.");
				}
			}
		}
		else
		{
			static_assert(false, "Attempted to perform an all-element comparison with an EmuMath Vector with a non-EmuMath Vector left-hand operand.");
			return false;
		}
	}

	template<bool IncludeNonContained_, class LhsVector_, class Rhs_, class Func_>
	inline constexpr bool _perform_vector_comparison_any(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<LhsVector_>)
		{
			Func_ cmp_ = Func_();
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<Rhs_>)
			{
				constexpr std::size_t used_size_ =
					(
						(IncludeNonContained_) ?
						(LhsVector_::size() >= Rhs_::size()) ? LhsVector_::size() : Rhs_::size() :
						(LhsVector_::size() <= Rhs_::size()) ? LhsVector_::size() : Rhs_::size()
						);
				if constexpr (used_size_ == 2)
				{
					return cmp_(lhs_.x, rhs_.x) && cmp_(lhs_.y, rhs_.y);
				}
				else if constexpr (used_size_ == 3)
				{
					return
						(
							cmp_(lhs_.x, rhs_.x) ||
							cmp_(lhs_.y, rhs_.y) ||
							cmp_(EmuMath::TMPHelpers::emu_vector_z(lhs_), EmuMath::TMPHelpers::emu_vector_z(rhs_))
							);
				}
				else if constexpr (used_size_ == 4)
				{
					return
						(
							cmp_(lhs_.x, rhs_.x) ||
							cmp_(lhs_.y, rhs_.y) ||
							cmp_(EmuMath::TMPHelpers::emu_vector_z(lhs_), EmuMath::TMPHelpers::emu_vector_z(rhs_)) ||
							cmp_(EmuMath::TMPHelpers::emu_vector_w(lhs_), EmuMath::TMPHelpers::emu_vector_w(rhs_))
							);
				}
				else
				{
					static_assert(false, "Attempted to perform an any-element comparison of EmuMath Vectors with at least one invalidly sized EmuMath Vector.");
				}
			}
			else
			{
				if constexpr (LhsVector_::size() == 2)
				{
					return cmp_(lhs_.x, rhs_) || cmp_(lhs_.y, rhs_);
				}
				else if constexpr (LhsVector_::size() == 3)
				{
					return cmp_(lhs_.x, rhs_) || cmp_(lhs_.y, rhs_) || cmp_(lhs_.z, rhs_);
				}
				else if constexpr (LhsVector_::size() == 4)
				{
					return cmp_(lhs_.x, rhs_) || cmp_(lhs_.y, rhs_) || cmp_(lhs_.z, rhs_) && cmp_(lhs_.w, rhs_);
				}
				else
				{
					static_assert(false, "Attempted to perform an any-element comparison with an invalidly sized EmuMath Vector.");
				}
			}
		}
		else
		{
			static_assert(false, "Attempted to perform an any-element comparison with an EmuMath Vector with a non-EmuMath Vector left-hand operand.");
			return false;
		}
	}
#pragma endregion
}

#endif
