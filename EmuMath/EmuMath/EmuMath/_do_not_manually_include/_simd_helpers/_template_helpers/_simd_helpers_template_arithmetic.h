#ifndef EMU_MATH_SIMD_HELPERS_TEMPLATE_ARITHMETIC_H_INC_
#define EMU_MATH_SIMD_HELPERS_TEMPLATE_ARITHMETIC_H_INC_ 1

#include "_underlying_template_helpers/_common_underlying_simd_template_helper_includes.h"
#include "_underlying_template_helpers/_simd_helpers_underlying_arithmetic.h"

namespace EmuMath::SIMD
{
	/// <summary>
	/// <para> Performs the correct _add_ operation for the provided SIMD Register_ type. </para>
	/// <para> 
	///		The provided PerElementWidthIfIntegral_ is used to determine how wide contained integer elements should be considered as for selecting the correct addition. 
	///		This is not used when a floating-point register is provided, and defaults to 32-bit elements.
	/// </para>
	/// </summary>
	/// <typeparam name="Register_">Register type to perform an addition operation via.</typeparam>
	/// <param name="lhs_">Register of values appearing on the left-hand side of addition.</param>
	/// <param name="rhs_">Register of values appearing on the right-hand side of addition.</param>
	/// <returns>Result of adding the two passed SIMD registers with their relevant _add_ operation (e.g. _mm_add_ps with __m128 registers).</returns>
	template<std::size_t PerElementWidthIfIntegral_ = 32, class Register_>
	[[nodiscard]] inline Register_ add(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuMath::SIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_add_fp(lhs_, rhs_);
			}
			else
			{
				return _underlying_simd_helpers::_add_int<PerElementWidthIfIntegral_>(lhs_, rhs_);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::add with an unsupported type as the passed Register_.");
		}
	}

	/// <summary>
	/// <para> Performs the correct _sub_ operation for the provided SIMD Register_ type. </para>
	/// <para> 
	///		The provided PerElementWidthIfIntegral_ is used to determine how wide contained integer elements should be considered as for selecting the correct addition. 
	///		This is not used when a floating-point register is provided, and defaults to 32-bit elements.
	/// </para>
	/// </summary>
	/// <typeparam name="Register_">Register type to perform a subtraction operation via.</typeparam>
	/// <param name="lhs_">Register of values appearing on the left-hand side of subtraction.</param>
	/// <param name="rhs_">Register of values appearing on the right-hand side of subtraction.</param>
	/// <returns>Result of subtracting the two passed SIMD registers with their relevant _sub_ operation (e.g. _mm_sub_ps with __m128 registers).</returns>
	template<std::size_t PerElementWidthIfIntegral_ = 32, class Register_>
	[[nodiscard]] inline Register_ sub(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuMath::SIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_sub_fp(lhs_, rhs_);
			}
			else
			{
				return _underlying_simd_helpers::_sub_int<PerElementWidthIfIntegral_>(lhs_, rhs_);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::sub with an unsupported type as the passed Register_.");
		}
	}

	/// <summary>
	/// <para> Performs the correct _mul_ operation for the provided SIMD Register_ type. </para>
	/// <para> 
	///		The provided SignedIfIntegral_ is used to determine if multiplied integers should be considered signed or unsigned, if integer registers are provided.
	///		This is not used when a floating-point register is provided, and defaults to true.
	/// </para>
	/// <para> 
	///		Note that integral _mul_ operations do not provide a full multiplication, and instead multiply the lo 32 bits of 64-bit lanes and provide 64-bit integer results. 
	///		To instead multiply all elements and store results in the desired width, use mul_all instead.
	/// </para>
	/// </summary>
	/// <typeparam name="Register_">Register type to perform a multiplication operation via.</typeparam>
	/// <param name="lhs_">Register of values appearing on the left-hand side of multiplication.</param>
	/// <param name="rhs_">Register of values appearing on the right-hand side of multiplication.</param>
	/// <returns>Result of multiplying the two passed SIMD registers with their relevant _mul_ operation (e.g. _mm_mul_ps with __m128 registers).</returns>
	template<bool SignedIfIntegral_ = true, class Register_>
	[[nodiscard]] inline Register_ mul(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuMath::SIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_mul_fp(lhs_, rhs_);
			}
			else
			{
				return _underlying_simd_helpers::_mul_int<SignedIfIntegral_>(lhs_, rhs_);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::mul with an unsupported type as the passed Register_.");
		}
	}

	/// <summary>
	/// <para> 
	///		Performs the correct _mul_ operation for the provided SIMD Register_ type, 
	///		where results will be that of multiplying each adjacent element. 
	/// </para>
	/// <para> 
	///		The provided PerElementWidthIfIntegral_ is used to determine how wide contained integer elements should be considered as for selecting the correct addition. 
	///		This is not used when a floating-point register is provided, and defaults to 32-bit elements.
	/// </para>
	/// <para> When providing floating-point registers, this is the same as their _mul_ operation. </para>
	/// <para> Unlike normal integral _mul_ operations, this multiplies adjacent elements and stores the result as their interpreted width. </para>
	/// </summary>
	/// <typeparam name="Register_">Register type to perform a multiplication operation via.</typeparam>
	/// <param name="lhs_">Register of values appearing on the left-hand side of multiplication.</param>
	/// <param name="rhs_">Register of values appearing on the right-hand side of multiplication.</param>
	/// <returns>
	///		Result of multiplying the two passed SIMD registers with their relevant _mul_ operation (e.g. _mm_mul_ps with __m128 registers), where
	///		all operations and resulting elements are of the same width of the input elements.
	/// </returns>
	template<std::size_t PerElementWidthIfIntegral_ = 32, class Register_>
	[[nodiscard]] inline Register_ mul_all(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuMath::SIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_mul_fp(lhs_, rhs_);
			}
			else
			{
				return _underlying_simd_helpers::_mul_all_int<PerElementWidthIfIntegral_>(lhs_, rhs_);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::mul_all with an unsupported type as the passed Register_.");
		}
	}

	/// <summary>
	/// <para> 
	///		Multiplies PerElementWidth_-bit integers in the passed register to form (PerElementWidth_ * 2)-bit intermediate integers, 
	///		and sets the values of the output register to the lo PerElementWidth_ bits of the resulting intermediates. 
	///		This is performed using the correct _mullo_ operation for the provided register and specified element bit width.
	/// </para>
	/// <para> PerElementWidth_ is used to determine how many bits should be used to interpret each element within the passed registers. </para>
	/// <para> Although there are no 8-bit functionalities built in, this will also emulate 8-bit width _mullo_ operations. </para>
	/// <para> Only integral SIMD registers may be provided to form this function, as such operations do not exist for floating-point registers. </para>
	/// </summary>
	/// <typeparam name="IntegralRegister_">Integral register type to perform a multiplication operation via.</typeparam>
	/// <param name="lhs_">Integral register of values appearing on the left-hand side of multiplication.</param>
	/// <param name="rhs_">Integral register of values appearing on the right-hand side of multiplication.</param>
	/// <returns></returns>
	template<std::size_t PerElementWidth_ = 32, class IntegralRegister_>
	[[nodiscard]] inline IntegralRegister_ mullo(IntegralRegister_ lhs_, IntegralRegister_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<IntegralRegister_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuMath::SIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_mullo_int<PerElementWidth_>(lhs_, rhs_);
			}
			else
			{
				static_assert(false, "Attempted to perform EmuMath::SIMD::mullo with a non-integral SIMD register. Integral registers are required for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::mullo with an unsupported type as the passed IntegralRegister_.");
		}
	}

	/// <summary>
	/// <para> Performs the correct _div_ operation for the provided SIMD Register_ type. </para>
	/// <para> 
	///		The provided PerElementWidthIfIntegral_ is used to determine how wide contained integer elements should be considered as for selecting the correct division.
	/// </para>
	/// <para>
	///		The provided SignedIfIntegral_ bool determines if contained integer elements should be considered as signed or unsigned for selecting the correct division. 
	/// </para>
	/// <para> The provided PErElementWidthIfIntegral_ and SignedIfIntegral_ arguments are not used if the provided register contains floating-point elements. </para>
	/// </summary>
	/// <typeparam name="Register_">Register type to perform a division operation via.</typeparam>
	/// <param name="lhs_">Register of values appearing on the left-hand side of division.</param>
	/// <param name="rhs_">Register of values appearing on the right-hand side of division.</param>
	/// <returns>Result of subtracting the two passed SIMD registers with their relevant _div_ operation (e.g. _mm_div_ps with __m128 registers).</returns>
	template<std::size_t PerElementWidthIfIntegral_ = 32, bool SignedIfIntegral_ = true, class Register_>
	[[nodiscard]] inline Register_ div(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuMath::SIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_div_fp(lhs_, rhs_);
			}
			else
			{
				return _underlying_simd_helpers::_div_int<PerElementWidthIfIntegral_, SignedIfIntegral_>(lhs_, rhs_);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::sub with an unsupported type as the passed Register_.");
		}
	}
}

#endif
