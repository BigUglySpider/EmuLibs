#ifndef EMU_MATH_VECTOR_HELPERS_H_INC_
#define EMU_MATH_VECTOR_HELPERS_H_INC_

#include "EmuVectorTMPHelpers.h"
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
#pragma endregion

#pragma region VECTORWISE SHIFTS
		template<class OutVector, class EmuVector_, class LeftShifter_, class RightShifter_>
		inline constexpr OutVector _perform_branching_vectorwise_left_shift(const EmuVector_& inVector, const std::size_t numShifts)
		{
			using Scalar = typename OutVector::value_type;
			constexpr std::size_t ScalarSize_ = sizeof(Scalar);
			constexpr std::size_t NumScalarBits = ScalarSize_ * 8;
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
						tagetShifter(inVector.z, (numShifts - NumScalarBitsX2)),
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
			constexpr std::size_t NumScalarBits = ScalarSize_ * 8;
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
				constexpr std::size_t NumScalarBits = ScalarSize_ * 8;
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
				return _underlying_vector_funcs::_perform_vector_bitwise_op_vector_rhs_emu<OutVector, LhsVector, Rhs, EmuCore::TMPHelpers::logical_and_diff_types>(lhs, rhs);
			}
			else
			{
				return _underlying_vector_funcs::_perform_vector_bitwise_op_scalar_rhs_emu<OutVector, LhsVector, Rhs, EmuCore::TMPHelpers::logical_and_diff_types>(lhs, rhs);
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
				return _underlying_vector_funcs::_perform_vector_bitwise_op_vector_rhs_emu<OutVector, LhsVector, Rhs, EmuCore::TMPHelpers::logical_or_diff_types>(lhs, rhs);
			}
			else
			{
				return _underlying_vector_funcs::_perform_vector_bitwise_op_scalar_rhs_emu<OutVector, LhsVector, Rhs, EmuCore::TMPHelpers::logical_or_diff_types>(lhs, rhs);
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
				return _underlying_vector_funcs::_perform_vector_bitwise_op_vector_rhs_emu<OutVector, LhsVector, Rhs, EmuCore::TMPHelpers::logical_xor_diff_types>(lhs, rhs);
			}
			else
			{
				return _underlying_vector_funcs::_perform_vector_bitwise_op_scalar_rhs_emu<OutVector, LhsVector, Rhs, EmuCore::TMPHelpers::logical_xor_diff_types>(lhs, rhs);
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
	inline typename EmuMath::TMPHelpers::emu_vector_copy<EmuVector_>::type VectorLeftShiftVectorwise(const EmuVector_& inVector, const std::size_t numShifts)
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
	inline typename EmuMath::TMPHelpers::emu_vector_copy<EmuVector_>::type VectorRightShiftVectorwise(const EmuVector_& inVector, const std::size_t numShifts)
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
}

#endif
