#ifndef EMU_SIMD_HELPERS_TEMPLATE_BASIC_ARITHMETIC_H_INC_
#define EMU_SIMD_HELPERS_TEMPLATE_BASIC_ARITHMETIC_H_INC_ 1

#include "_underlying_template_helpers/_common_underlying_simd_template_helper_includes.h"
#include "_underlying_template_helpers/_simd_helpers_underlying_basic_arithmetic.h"

namespace EmuSIMD
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
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
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
			static_assert(false, "Attempted to perform EmuSIMD::add with an unsupported type as the passed Register_.");
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
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
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
			static_assert(false, "Attempted to perform EmuSIMD::sub with an unsupported type as the passed Register_.");
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
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
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
			static_assert(false, "Attempted to perform EmuSIMD::mul with an unsupported type as the passed Register_.");
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
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
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
			static_assert(false, "Attempted to perform EmuSIMD::mul_all with an unsupported type as the passed Register_.");
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
	/// <returns>Result of multiplying respective elements in the passed two SIMD registers, read and written as their interpreted PerElementWidth_ bit size.</returns>
	template<std::size_t PerElementWidth_ = 32, class IntegralRegister_>
	[[nodiscard]] inline IntegralRegister_ mullo(IntegralRegister_ lhs_, IntegralRegister_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<IntegralRegister_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_mullo_int<PerElementWidth_>(lhs_, rhs_);
			}
			else
			{
				static_assert(false, "Attempted to perform EmuSIMD::mullo with a non-integral SIMD register. Integral registers are required for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuSIMD::mullo with an unsupported type as the passed IntegralRegister_.");
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
	/// <para> The provided PerElementWidthIfIntegral_ and SignedIfIntegral_ arguments are not used if the provided register contains floating-point elements. </para>
	/// </summary>
	/// <typeparam name="Register_">Register type to perform a division operation via.</typeparam>
	/// <param name="lhs_">Register of values appearing on the left-hand side of division.</param>
	/// <param name="rhs_">Register of values appearing on the right-hand side of division.</param>
	/// <returns>Result of division with the two passed SIMD registers with their relevant _div_ operation (e.g. _mm_div_ps with __m128 registers).</returns>
	template<std::size_t PerElementWidthIfIntegral_ = 32, bool SignedIfIntegral_ = true, class Register_>
	[[nodiscard]] inline Register_ div(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
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
			static_assert(false, "Attempted to perform EmuSIMD::sub with an unsupported type as the passed Register_.");
		}
	}

	/// <summary>
	/// <para> Performs the correct modulo division operation for the provided SIMD Register_ type. </para>
	/// <para> 
	///		The provided PerElementWidthIfIntegral_ is used to determine how wide contained integer elements should be considered as for selecting the correct division.
	/// </para>
	/// <para>
	///		The provided SignedIfIntegral_ bool determines if contained integer elements should be considered as signed or unsigned for selecting the correct division. 
	/// </para>
	/// <para> The provided PerElementWidthIfIntegral_ and SignedIfIntegral_ arguments are not used if the provided register contains floating-point elements. </para>
	/// </summary>
	/// <typeparam name="Register_">Register type to perform a modulo division operation via.</typeparam>
	/// <param name="lhs_">Register of values appearing on the left-hand side of modulo division.</param>
	/// <param name="rhs_">Register of values appearing on the right-hand side of modulo division.</param>
	/// <returns>Result of modulo division with the two passed SIMD registers with their relevant mod operation (e.g. _mm_fmod_ps with __m128 registers).</returns>
	template<std::size_t PerElementWidthIfIntegral_ = 32, bool SignedIfIntegral_ = true, class Register_>
	[[nodiscard]] inline Register_ mod(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_mod_fp(lhs_, rhs_);
			}
			else
			{
				return _underlying_simd_helpers::_mod_int<PerElementWidthIfIntegral_, SignedIfIntegral_>(lhs_, rhs_);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuSIMD::mod with an unsupported type as the passed Register_.");
		}
	}

	/// <summary>
	/// <para> 
	///		Negates the passed SIMD register with the correct operations, 
	///		forming a register where each element is the negative of the respective passed register element.
	/// </para>
	/// <para> 
	///		The provided PerElementWidthIfIntegral_ is used to determine how wide contained integer elements should be considered as for selecting the correct division.
	/// </para>
	/// </summary>
	/// <typeparam name="Register_">Register type to perform a negation via.</typeparam>
	/// <param name="register_">SIMD register to negate.</param>
	/// <returns>Negated form of the passed SIMD register.</returns>
	template<std::size_t PerElementWidthIfIntegral_ = 32, class Register_>
	[[nodiscard]] inline Register_ negate(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_negate(register_);
		}
		else
		{
			static_assert(false, "Attempted to perform EmuSIMD::negate with an unsupported type as the passed Register_.");
		}
	}

	/// <summary>
	/// <para> Performs a fused multiply-add of the passed SIMD registers via the correct _fmadd_ operation for the register type. </para>
	/// <para> If the passed register type is integral, this will emulate the operation, but it will make no difference compared to normal operations. </para>
	/// <para> 
	///		The provided PerElementWidthIfInt_ is used to determine how wide contained integer elements should be considered as 
	///		for selecting the correct operations for emulation if an integral register is provided.
	/// </para>
	/// <para> The provided PerElementWidthIfInt_ argument is not used if the provided register contains floating-point elements. </para>
	/// </summary>
	/// <typeparam name="Register_">Register type to perform the fused operation via.</typeparam>
	/// <param name="to_mult_lhs_">Register appearing on the left-hand side of multiplication.</param>
	/// <param name="to_mult_rhs_">Register appearing on the right-hand side of multiplication.</param>
	/// <param name="to_add_after_mult_">Register to add to the intermediate value resulting from the initial multiplication before a floating-point round.</param>
	/// <returns>Result of a fused multiply-add operation with the provided operands, or an emulation of such if the registers are integral.</returns>
	template<std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Register_ fmadd(Register_ to_mult_lhs_, Register_ to_mult_rhs_, Register_ to_add_after_mult_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_fmadd_fp(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_fmadd_int<PerElementWidthIfInt_>(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
			}
			else
			{
				static_assert(false, "Attempted to perform EmuSIMD::fmadd with SIMD register that is not supported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuSIMD::fmadd with an unsupported type as the passed Register_.");
		}
	}

	/// <summary>
	/// <para> Performs a fused multiply-subtract of the passed SIMD registers via the correct _fmsub_ operation for the register type. </para>
	/// <para> If the passed register type is integral, this will emulate the operation, but it will make no difference compared to normal operations. </para>
	/// <para> 
	///		The provided PerElementWidthIfInt_ is used to determine how wide contained integer elements should be considered as 
	///		for selecting the correct operations for emulation if an integral register is provided.
	/// </para>
	/// <para> The provided PerElementWidthIfInt_ argument is not used if the provided register contains floating-point elements. </para>
	/// </summary>
	/// <typeparam name="Register_">Register type to perform the fused operation via.</typeparam>
	/// <param name="to_mult_lhs_">Register appearing on the left-hand side of multiplication.</param>
	/// <param name="to_mult_rhs_">Register appearing on the right-hand side of multiplication.</param>
	/// <param name="to_add_after_mult_">Register to subtract from the intermediate value resulting from the initial multiplication before a floating-point round.</param>
	/// <returns>Result of a fused multiply-subtract operation with the provided operands, or an emulation of such if the registers are integral.</returns>
	template<std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Register_ fmsub(Register_ to_mult_lhs_, Register_ to_mult_rhs_, Register_ to_add_after_mult_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_fmsub_fp(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_fmsub_int<PerElementWidthIfInt_>(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
			}
			else
			{
				static_assert(false, "Attempted to perform EmuSIMD::fmsub with SIMD register that is not supported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuSIMD::fmsub with an unsupported type as the passed Register_.");
		}
	}

	/// <summary>
	/// <para> Performs a fused multiply-add/subtract of the passed SIMD registers via the correct _fmaddsub_ operation for the register type. </para>
	/// <para> Items in to_add_sub_after_mult_ will be sequentially used for addition, subtraction, addition, subtraction, etc... </para>
	/// <para> If the passed register type is integral, this will emulate the operation, but it will make no difference compared to normal operations. </para>
	/// <para> 
	///		The provided PerElementWidthIfInt_ is used to determine how wide contained integer elements should be considered as 
	///		for selecting the correct operations for emulation if an integral register is provided.
	/// </para>
	/// <para> The provided PerElementWidthIfInt_ argument is not used if the provided register contains floating-point elements. </para>
	/// </summary>
	/// <typeparam name="Register_">Register type to perform the fused operation via.</typeparam>
	/// <param name="to_mult_lhs_">Register appearing on the left-hand side of multiplication.</param>
	/// <param name="to_mult_rhs_">Register appearing on the right-hand side of multiplication.</param>
	/// <param name="to_add_sub_after_mult_">
	///		Register to sequentially add to/subtract from the intermediate value resulting from the initial multiplication before a floating-point round.
	/// </param>
	/// <returns>Result of a fused multiply-add/subtract operation with the provided operands, or an emulation of such if the registers are integral.</returns>
	template<std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Register_ fmaddsub(Register_ to_mult_lhs_, Register_ to_mult_rhs_, Register_ to_add_sub_after_mult_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_fmaddsub_fp(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_fmaddsub_int<PerElementWidthIfInt_>(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
			}
			else
			{
				static_assert(false, "Attempted to perform EmuSIMD::fmaddsub with SIMD register that is not supported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuSIMD::fmaddsub with an unsupported type as the passed Register_.");
		}
	}

	/// <summary>
	/// <para> Performs a fused multiply-subtract/add of the passed SIMD registers via the correct _fmsubadd_ operation for the register type. </para>
	/// <para> Items in to_sub_add_after_mult_ will be sequentially used for subtraction, addition, subtraction, addition, etc... </para>
	/// <para> If the passed register type is integral, this will emulate the operation, but it will make no difference compared to normal operations. </para>
	/// <para> 
	///		The provided PerElementWidthIfInt_ is used to determine how wide contained integer elements should be considered as 
	///		for selecting the correct operations for emulation if an integral register is provided.
	/// </para>
	/// <para> The provided PerElementWidthIfInt_ argument is not used if the provided register contains floating-point elements. </para>
	/// </summary>
	/// <typeparam name="Register_">Register type to perform the fused operation via.</typeparam>
	/// <param name="to_mult_lhs_">Register appearing on the left-hand side of multiplication.</param>
	/// <param name="to_mult_rhs_">Register appearing on the right-hand side of multiplication.</param>
	/// <param name="to_sub_add_after_mult_">
	///		Register to sequentially subtract from/add to the intermediate value resulting from the initial multiplication before a floating-point round.
	/// </param>
	/// <returns>Result of a fused multiply-subtract/add operation with the provided operands, or an emulation of such if the registers are integral.</returns>
	template<std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Register_ fmsubadd(Register_ to_mult_lhs_, Register_ to_mult_rhs_, Register_ to_sub_add_after_mult_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_fmsubadd_fp(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_fmsubadd_int<PerElementWidthIfInt_>(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
			}
			else
			{
				static_assert(false, "Attempted to perform EmuSIMD::fmsubadd with SIMD register that is not supported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuSIMD::fmsubadd with an unsupported type as the passed Register_.");
		}
	}

	/// <summary>
	/// <para> Performs a sequential add/subtract operation with the provided registers via the correct _addsub_ operation. </para>
	/// <para> Items in rhs_ will be sequentially used for addition, subtraction, addition, subtraction, etc... </para>
	/// <para> This operation will be emulated for register types that do not have built in intrinsics for addsub. </para>
	/// <para> 
	///		The provided PerElementWidthIfInt_ is used to determine how wide contained integer elements should be considered as 
	///		for selecting the correct operations for emulation if an integral register is provided.
	/// </para>
	/// <para> The provided PerElementWidthIfInt_ argument is not used if the provided register contains floating-point elements. </para>
	/// </summary>
	/// <typeparam name="Register_">Type of register to perform the sequential operation via.</typeparam>
	/// <param name="lhs_">Register to add to/subtract from.</param>
	/// <param name="rhs_">Register to sequentially add/subtract the values of.</param>
	/// <returns>Result of sequential addition to/subtraction from the passed lhs_ register via the passed rhs_ register.</returns>
	template<std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Register_ addsub(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_addsub_fp(lhs_, rhs_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_addsub_int<PerElementWidthIfInt_>(lhs_, rhs_);
			}
			else
			{
				static_assert(false, "Attempted to perform EmuSIMD::addsub with SIMD register that is not supported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuSIMD::addsub with an unsupported type as the passed Register_.");
		}
	}

	/// <summary>
	/// <para> Emulates a sequential add/subtract operation with the provided registers. </para>
	/// <para> Items in rhs_ will be sequentially used for subtraction, addition, subtraction, addition, etc... </para>
	/// <para> 
	///		The provided PerElementWidthIfInt_ is used to determine how wide contained integer elements should be considered as 
	///		for selecting the correct operations for emulation if an integral register is provided.
	/// </para>
	/// <para> The provided PerElementWidthIfInt_ argument is not used if the provided register contains floating-point elements. </para>
	/// </summary>
	/// <typeparam name="Register_">Type of register to perform the sequential operation via.</typeparam>
	/// <param name="lhs_">Register to subtract from/add to.</param>
	/// <param name="rhs_">Register to sequentially subtract/add the values of.</param>
	/// <returns>Result of sequential subtraction from/addition to the passed lhs_ register via the passed rhs_ register.</returns>
	template<std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Register_ subadd(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_subadd_fp(lhs_, rhs_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_subadd_int<PerElementWidthIfInt_>(lhs_, rhs_);
			}
			else
			{
				static_assert(false, "Attempted to perform EmuSIMD::subadd with SIMD register that is not supported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuSIMD::subadd with an unsupported type as the passed Register_.");
		}
	}

	template<int RoundingMode_, class Register_>
	[[nodiscard]] inline Register_ round(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_round<RoundingMode_>(register_);
		}
		else
		{
			static_assert(false, "Attempted to perform EmuSIMD::round with an unsupported type as the passed Register_.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ floor(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_floor(register_);
		}
		else
		{
			static_assert(false, "Attempted to perform EmuSIMD::floor with an unsupported type as the passed Register_.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ ceil(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_ceil(register_);
		}
		else
		{
			static_assert(false, "Attempted to perform EmuSIMD::ceil with an unsupported type as the passed Register_.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ trunc(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_trunc(register_);
		}
		else
		{
			static_assert(false, "Attempted to perform EmuSIMD::trunc with an unsupported type as the passed Register_.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline Register_ vector_min(Register_ a_, Register_ b_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_min<PerElementWidthIfInt_, SignedIfInt_>(a_, b_);
		}
		else
		{
			static_assert(false, "Attempted to perform EmuSIMD::vector_min with an unsupported type as the passed Register_.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline Register_ vector_max(Register_ a_, Register_ b_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_max<PerElementWidthIfInt_, SignedIfInt_>(a_, b_);
		}
		else
		{
			static_assert(false, "Attempted to perform EmuSIMD::vector_max with an unsupported type as the passed Register_.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline Register_ clamp_min(Register_ register_, Register_ min_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_clamp_min<PerElementWidthIfInt_, SignedIfInt_>(register_, min_);
		}
		else
		{
			static_assert(false, "Attempted to perform EmuSIMD::clamp_min with an unsupported type as the passed Register_.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline Register_ clamp_max(Register_ register_, Register_ max_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_clamp_max<PerElementWidthIfInt_, SignedIfInt_>(register_, max_);
		}
		else
		{
			static_assert(false, "Attempted to perform EmuSIMD::clamp_max with an unsupported type as the passed Register_.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline Register_ clamp(Register_ register_, Register_ min_, Register_ max_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_clamp<PerElementWidthIfInt_, SignedIfInt_>(register_, min_, max_);
		}
		else
		{
			static_assert(false, "Attempted to perform EmuSIMD::clamp with an unsupported type as the passed Register_.");
		}
	}
}

#endif
