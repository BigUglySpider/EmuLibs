#ifndef EMU_MATH_VECTOR_HELPERS_H_INC_
#define EMU_MATH_VECTOR_HELPERS_H_INC_

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

namespace EmuMath::Helpers
{
	/// <summary> Underlying functions used for performing Vector helpers. These are not recommended for manual use. </summary>
	namespace _underlying_vector_funcs
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
	}

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

	template<typename OutT, class EmuVector_>
	inline constexpr OutT VectorSquareMagnitude(const EmuVector_& vector_)
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
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<EmuVector_>)
		{
			using VecInfo_ = typename EmuVector_::info_type;
			if constexpr (VecInfo_::has_floating_point_values)
			{
				return EmuMath::SqrtConstexpr<OutFP_, long double>(VectorSquareMagnitude<long double>(vector_));
			}
			else
			{
				return EmuMath::SqrtConstexpr<OutFP_, std::uint64_t>(VectorSquareMagnitude<std::uint64_t>(vector_));
			}
		}
		else
		{
			static_assert(false, "Attempted to get the magnitude of an EmuMath Vector, but passed a type that is not an EmuMath Vector.");
			return OutFP_();
		}
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
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<EmuVector_>)
		{
			using StrippedOut_ = std::remove_cv_t<Out_>;
			using VecInfo_ = typename EmuVector_::info_type;
			using SqrMag = std::conditional_t<VecInfo_::has_floating_point_values, long double, std::uint64_t>;
			const SqrMag sqrMag_ = VectorSquareMagnitude<SqrMag>(vector_);
			if constexpr (std::is_same_v<StrippedOut_, SqrMag>)
			{
				return sqrtl(sqrMag_);
			}
			else
			{
				return static_cast<Out_>(sqrtl(sqrMag_));
			}
		}
		else
		{
			static_assert(false, "Attempted to get the magnitude of an EmuMath Vector, but passed a type that is not an EmuMath Vector.");
			return Out_();
		}
	}

	template<typename OutFP_, typename InT_>
	inline EmuMath::Vector2<OutFP_> VectorNormalise(const EmuMath::Vector2<InT_>& inVector)
	{
		using OutVector = EmuMath::Vector2<OutFP_>;
		using StrippedOut = std::remove_cv_t<OutFP_>;
		if constexpr (std::is_floating_point_v<StrippedOut>)
		{
			using Mag_ = long double;
			const Mag_ reciprocal = 1.0f / VectorMagnitude<Mag_>(inVector);
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
					return func(VectorSquareMagnitude<long double>(lhs), VectorSquareMagnitude<long double>(rhs));
				}
				else
				{
					return func(VectorSquareMagnitude<std::uint64_t>(lhs), VectorSquareMagnitude<std::uint64_t>(rhs));
				}
			}
			else
			{
				if constexpr (LhsInfo::has_floating_point_values)
				{
					return func(VectorSquareMagnitude<long double>(lhs), rhs);
				}
				else
				{
					return func(VectorSquareMagnitude<std::uint64_t>(lhs), rhs);
				}
			}
		}
		else
		{
			static_assert(false, "Attempted to perform an EmuMath magnitude comparison using a non-EmuMath-Vector operand.");
			return false;
		}
	}

	template<class LhsVector_, class RhsT_>
	inline constexpr bool VectorComparisonEqual(const LhsVector_& lhs, const Vector2<RhsT_>& rhs)
	{
		return _perform_vector_comparison_equal<LhsVector_, RhsT_, 2>(lhs, rhs);
	}
	template<class LhsVector_, class RhsT_>
	inline constexpr bool VectorComparisonEqual(const LhsVector_& lhs, const Vector3<RhsT_>& rhs)
	{
		return _perform_vector_comparison_equal<LhsVector_, RhsT_, 3>(lhs, rhs);
	}
	template<class LhsVector_, class RhsT_>
	inline constexpr bool VectorComparisonEqual(const LhsVector_& lhs, const Vector4<RhsT_>& rhs)
	{
		return _perform_vector_comparison_equal<LhsVector_, RhsT_, 4>(lhs, rhs);
	}

	template<class LhsVector_, class RhsT_>
	inline constexpr bool VectorComparisonNotEqual(const LhsVector_& lhs, const EmuMath::Vector2<RhsT_>& rhs)
	{
		return _perform_vector_comparison_not_equal<LhsVector_, RhsT_, 2>(lhs, rhs);
	}
	template<class LhsVector_, class RhsT_>
	inline constexpr bool VectorComparisonNotEqual(const LhsVector_& lhs, const EmuMath::Vector3<RhsT_>& rhs)
	{
		return _perform_vector_comparison_not_equal<LhsVector_, RhsT_, 3>(lhs, rhs);
	}
	template<class LhsVector_, class RhsT_>
	inline constexpr bool VectorComparisonNotEqual(const LhsVector_& lhs, const EmuMath::Vector4<RhsT_>& rhs)
	{
		return _perform_vector_comparison_not_equal<LhsVector_, RhsT_, 4>(lhs, rhs);
	}

	template<class LhsVector_, class Rhs_>
	inline constexpr bool VectorComparisonGreater(const LhsVector_& lhs, const Rhs_& rhs)
	{
		return _perform_vector_magnitude_comparison_std<LhsVector_, Rhs_, std::greater<void>>(lhs, rhs);
	}
	template<class LhsVector_, class Rhs_>
	inline constexpr bool VectorComparisonLess(const LhsVector_& lhs, const Rhs_& rhs)
	{
		return _perform_vector_magnitude_comparison_std<LhsVector_, Rhs_, std::less<void>>(lhs, rhs);
	}
	template<class LhsVector_, class Rhs_>
	inline constexpr bool VectorComparisonGreaterEqual(const LhsVector_& lhs, const Rhs_& rhs)
	{
		return _perform_vector_magnitude_comparison_std<LhsVector_, Rhs_, std::greater_equal<void>>(lhs, rhs);
	}
	template<class LhsVector_, class Rhs_>
	inline constexpr bool VectorComparisonLessEqual(const LhsVector_& lhs, const Rhs_& rhs)
	{
		return _perform_vector_magnitude_comparison_std<LhsVector_, Rhs_, std::less_equal<void>>(lhs, rhs);
	}

	template<class OutVector_, class InVector_, template<typename In__, typename Out__> class Rounder_>
	inline OutVector_ _perform_vector_round_emu(const InVector_& in_)
	{
		using Rounder = Rounder_<InVector_, OutVector_>;
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

	template<std::size_t OutSize_, typename OutContainedT_, class InVector_>
	inline typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutContainedT_>::type VectorCeil(const InVector_& in_)
	{
		using OutVector_ = typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutContainedT_>::type;
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<OutVector_>)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<InVector_>)
			{
				return _perform_vector_round_emu<OutVector_, InVector_, EmuCore::TMPHelpers::ceil_diff_types>(in_);
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
				return _perform_vector_constexpr_round_emu<OutVector_, InVector_, EmuCore::TMPHelpers::ceil_diff_types>(in_);
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
				return _perform_vector_round_emu<OutVector_, InVector_, EmuCore::TMPHelpers::floor_diff_types>(in_);
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
				return _perform_vector_constexpr_round_emu<OutVector_, InVector_, EmuCore::TMPHelpers::floor_diff_types>(in_);
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
				return _perform_vector_round_emu<OutVector_, InVector_, EmuCore::TMPHelpers::trunc_diff_types>(in_);
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
				return _perform_vector_constexpr_round_emu<OutVector_, InVector_, EmuCore::TMPHelpers::trunc_diff_types>(in_);
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

	template<typename OutT, class InVector_, class Func_>
	inline constexpr OutT _perform_vector_min_or_max(const InVector_& in_)
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

	template<typename OutT, class InVector_>
	inline constexpr OutT VectorMin(const InVector_& in_)
	{
		return _perform_vector_min_or_max<OutT, InVector_, std::less_equal<void>>(in_);
	}
	template<typename OutT, class InVector_>
	inline constexpr OutT VectorMax(const InVector_& in_)
	{
		return _perform_vector_min_or_max<OutT, InVector_, std::greater_equal<void>>(in_);
	}

	template<class OutVector_, class InVector_, class MinOrMaxVector_, class CmpFunc_>
	inline constexpr OutVector_ _perform_vector_clamp_min_or_max_with_vector(const InVector_& in_, const MinOrMaxVector_& minOrMax_)
	{
		CmpFunc_ cmp_ = CmpFunc_();
		if constexpr (OutVector_::size() == 2)
		{
			return OutVector_
			(
				cmp_(in_.x, minOrMax_.x) ? minOrMax_.x : in_.x,
				cmp_(in_.y, minOrMax_.y) ? minOrMax_.y : in_.y
			);
		}
		else if constexpr (OutVector_::size() == 3)
		{
			if constexpr (MinOrMaxVector_::size() >= 3)
			{
				const auto inZ_ = EmuMath::TMPHelpers::emu_vector_z(in_);
				return OutVector_
				(
					cmp_(in_.x, minOrMax_.x) ? minOrMax_.x : in_.x,
					cmp_(in_.y, minOrMax_.y) ? minOrMax_.y : in_.y,
					cmp_(inZ_, minOrMax_.z) ? minOrMax_.z : inZ_;
				);
			}
			else
			{
				return OutVector_
				(
					cmp_(in_.x, minOrMax_.x) ? minOrMax_.x : in_.x,
					cmp_(in_.y, minOrMax_.y) ? minOrMax_.y : in_.y,
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
						cmp_(in_.x, minOrMax_.x) ? minOrMax_.x : in_.x,
						cmp_(in_.y, minOrMax_.y) ? minOrMax_.y : in_.y,
						cmp_(inZ_, minOrMax_.z) ? minOrMax_.z : inZ_,
						cmp_(inW_, minOrMax_.w) ? minOrMax_.w : inW_
					);
				}
				else
				{
					return OutVector_
					(
						cmp_(in_.x, minOrMax_.x) ? minOrMax_.x : in_.x,
						cmp_(in_.y, minOrMax_.y) ? minOrMax_.y : in_.y,
						cmp_(inZ_, minOrMax_.z) ? minOrMax_.z : inZ_,
						EmuMath::TMPHelpers::emu_vector_w(in_)
					);
				}
			}
			else
			{
				return OutVector_
				(
					cmp_(in_.x, minOrMax_.x) ? minOrMax_.x : in_.x,
					cmp_(in_.y, minOrMax_.y) ? minOrMax_.y : in_.y,
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
		CmpFunc_ cmp_ = CmpFunc_();
		if constexpr (OutVector_::size() == 2)
		{
			return OutVector_
			(
				cmp_(in_.x, minOrMax_) ? minOrMax_ : in_.x,
				cmp_(in_.y, minOrMax_) ? minOrMax_ : in_.y
			);
		}
		else if constexpr (OutVector_::size() == 3)
		{
			const auto inZ_ = EmuMath::TMPHelpers::emu_vector_z(in_);
			return OutVector_
			(
				cmp_(in_.x, minOrMax_) ? minOrMax_ : in_.x,
				cmp_(in_.y, minOrMax_) ? minOrMax_ : in_.y,
				cmp_(inZ_, minOrMax_) ? minOrMax_ : inZ_
			);
		}
		else if constexpr (OutVector_::size() == 4)
		{
			const auto inZ_ = EmuMath::TMPHelpers::emu_vector_z(in_);
			const auto inW_ = EmuMath::TMPHelpers::emu_vector_w(in_);
			return OutVector_
			(
				cmp_(in_.x, minOrMax_) ? minOrMax_ : in_.x,
				cmp_(in_.y, minOrMax_) ? minOrMax_ : in_.y,
				cmp_(inZ_, minOrMax_) ? minOrMax_ : inZ_,
				cmp_(inW_, minOrMax_) ? minOrMax_ : inW_
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

	template<std::size_t OutSize_, typename OutT_, class InVector_, class MinT_>
	inline constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type VectorClampMin(const InVector_& in_, const MinT_& min_)
	{
		using OutVector_ = typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type;
		return _perform_vector_min_or_max_clamp<OutVector_, InVector_, MinT_, std::less<void>>(in_, min_);
	}
	template<std::size_t OutSize_, typename OutT_, class InVector_, class MinT_>
	inline constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type VectorClampMax(const InVector_& in_, const MinT_& min_)
	{
		using OutVector_ = typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type;
		return _perform_vector_min_or_max_clamp<OutVector_, InVector_, MinT_, std::greater<void>>(in_, min_);
	}
}

#endif
