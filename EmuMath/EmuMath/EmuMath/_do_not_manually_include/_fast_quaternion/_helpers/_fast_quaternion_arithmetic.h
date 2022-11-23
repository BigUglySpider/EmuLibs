#ifndef EMU_MATH_FAST_QUATERNION_ARITHMETIC_H_INC_
#define EMU_MATH_FAST_QUATERNION_ARITHMETIC_H_INC_ 1

#include "_common_fast_quaternion_includes.h"

namespace EmuMath::Helpers
{
#pragma region ADDITION_FUNCS
	template<EmuConcepts::EmuFastQuaternion FastQuaternion_>
	[[nodiscard]] constexpr inline auto fast_quaternion_add(const FastQuaternion_& lhs_, const FastQuaternion_& rhs_)
		-> typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type
	{
		constexpr std::size_t num_registers = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::num_registers;
		constexpr std::size_t per_element_width = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::per_element_width;
		if constexpr (num_registers == 1)
		{
			return typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type
			(
				EmuSIMD::add<per_element_width>
				(
					lhs_.template GetRegister<0>(),
					rhs_.template GetRegister<0>()
				)
			);
		}
		else
		{
			return typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type
			(
				EmuSIMD::add<per_element_width>
				(
					lhs_.template GetRegister<0>(),
					rhs_.template GetRegister<0>()
				),
				EmuSIMD::add<per_element_width>
				(
					lhs_.template GetRegister<1>(),
					rhs_.template GetRegister<1>()
				)
			);
		}
	}

	template<EmuConcepts::EmuFastQuaternion FastQuaternion_>
	requires (!std::is_const_v<FastQuaternion_>)
	constexpr inline void fast_quaternion_add_assign(FastQuaternion_& lhs_and_out_, const FastQuaternion_& rhs_)
	{
		constexpr std::size_t num_registers = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::num_registers;
		constexpr std::size_t per_element_width = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::per_element_width;
		lhs_and_out_.template GetRegister<0>() = EmuSIMD::add<per_element_width>
		(
			lhs_and_out_.template GetRegister<0>(), 
			rhs_.template GetRegister<0>()
		);

		if constexpr (num_registers > 1)
		{
			lhs_and_out_.template GetRegister<1>() = EmuSIMD::add<per_element_width>
			(
				lhs_and_out_.template GetRegister<1>(), 
				rhs_.template GetRegister<1>()
			);
		}
	}
#pragma endregion

#pragma region SUBTRACTION_FUNCS
	template<EmuConcepts::EmuFastQuaternion FastQuaternion_>
	[[nodiscard]] constexpr inline auto fast_quaternion_subtract(const FastQuaternion_& lhs_, const FastQuaternion_& rhs_)
		-> typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type
	{
		constexpr std::size_t num_registers = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::num_registers;
		constexpr std::size_t per_element_width = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::per_element_width;
		if constexpr (num_registers == 1)
		{
			return typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type
			(
				EmuSIMD::sub<per_element_width>
				(
					lhs_.template GetRegister<0>(),
					rhs_.template GetRegister<0>()
				)
			);
		}
		else
		{
			return typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type
			(
				EmuSIMD::sub<per_element_width>
				(
					lhs_.template GetRegister<0>(),
					rhs_.template GetRegister<0>()
				),
				EmuSIMD::sub<per_element_width>
				(
					lhs_.template GetRegister<1>(),
					rhs_.template GetRegister<1>()
				)
			);
		}
	}

	template<EmuConcepts::EmuFastQuaternion FastQuaternion_>
	requires (!std::is_const_v<FastQuaternion_>)
	constexpr inline void fast_quaternion_subtract_assign(FastQuaternion_& lhs_and_out_, const FastQuaternion_& rhs_)
	{
		constexpr std::size_t num_registers = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::num_registers;
		constexpr std::size_t per_element_width = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::per_element_width;
		lhs_and_out_.template GetRegister<0>() = EmuSIMD::sub<per_element_width>
		(
			lhs_and_out_.template GetRegister<0>(), 
			rhs_.template GetRegister<0>()
		);

		if constexpr (num_registers > 1)
		{
			lhs_and_out_.template GetRegister<1>() = EmuSIMD::sub<per_element_width>
			(
				lhs_and_out_.template GetRegister<1>(), 
				rhs_.template GetRegister<1>()
			);
		}
	}
#pragma endregion

#pragma region DIVISION_FUNCS
	template<EmuConcepts::EmuFastQuaternion FastQuaternion_>
	[[nodiscard]] constexpr inline auto fast_quaternion_divide
	(
		const FastQuaternion_& lhs_,
		typename EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::register_arg_type rhs_scalar_register_
	)
		-> typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type
	{
		constexpr std::size_t num_registers = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::num_registers;
		constexpr bool is_signed = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::is_signed;
		constexpr std::size_t per_element_width = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::per_element_width;
		if constexpr (num_registers <= 1)
		{
			return typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type
			(
				EmuSIMD::div<per_element_width, is_signed>
				(
					lhs_.template GetRegister<0>(),
					rhs_scalar_register_
				)
			);
		}
		else
		{
			return typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type
			(
				EmuSIMD::div<per_element_width, is_signed>
				(
					lhs_.template GetRegister<0>(),
					rhs_scalar_register_
				),
				EmuSIMD::div<per_element_width, is_signed>
				(
					lhs_.template GetRegister<1>(),
					rhs_scalar_register_
				)
			);
		}
	}
	
	template<EmuConcepts::EmuFastQuaternion FastQuaternion_, EmuConcepts::Arithmetic RhsScalar_>
	[[nodiscard]] constexpr inline auto fast_quaternion_divide
	(
		const FastQuaternion_& lhs_,
		RhsScalar_&& rhs_scalar_
	)
		-> typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type
	{
		constexpr std::size_t per_element_width = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::per_element_width;
		using _required_register_type = typename EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::register_type;
		return EmuMath::Helpers::fast_quaternion_divide
		(
			lhs_,
			EmuSIMD::set1<_required_register_type, per_element_width>(std::forward<RhsScalar_>(rhs_scalar_))
		);
	}
#pragma endregion

#pragma region DIVIDE_ASSIGN_FUNCS
	template<EmuConcepts::EmuFastQuaternion FastQuaternion_>
	requires (!std::is_const_v<FastQuaternion_>)
	constexpr inline void fast_quaternion_divide_assign
	(
		FastQuaternion_& lhs_and_out_,
		typename EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::register_arg_type rhs_scalar_register_
	)
	{
		constexpr std::size_t num_registers = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::num_registers;
		constexpr bool is_signed = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::is_signed;
		constexpr std::size_t per_element_width = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::per_element_width;
		lhs_and_out_.template GetRegister<0>() = EmuSIMD::div<per_element_width, is_signed>
		(
			lhs_and_out_.template GetRegister<0>(), 
			rhs_scalar_register_
		);

		if constexpr (num_registers > 1)
		{
			lhs_and_out_.template GetRegister<1>() = EmuSIMD::div<per_element_width, is_signed>
			(
				lhs_and_out_.template GetRegister<1>(), 
				rhs_scalar_register_
			);
		}
	}

	template<EmuConcepts::EmuFastQuaternion FastQuaternion_, EmuConcepts::Arithmetic RhsScalar_>
	requires (!std::is_const_v<FastQuaternion_>)
	[[nodiscard]] constexpr inline void fast_quaternion_divide_assign(FastQuaternion_& lhs_and_out_, RhsScalar_&& rhs_scalar_)
	{
		constexpr std::size_t per_element_width = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::per_element_width;
		using _required_register_type = typename EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::register_type;
		EmuMath::Helpers::fast_quaternion_divide_assign
		(
			lhs_and_out_,
			EmuSIMD::set1<_required_register_type, per_element_width>(std::forward<RhsScalar_>(rhs_scalar_))
		);
	}
#pragma endregion

#pragma region MULTIPLY_SCALAR_FUNCS
	template<EmuConcepts::EmuFastQuaternion FastQuaternion_>
	[[nodiscard]] constexpr inline auto fast_quaternion_multiply_scalar
	(
		const FastQuaternion_& lhs_,
		typename EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::register_arg_type rhs_scalar_register_
	)
		-> typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type
	{
		constexpr std::size_t num_registers = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::num_registers;
		constexpr std::size_t per_element_width = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::per_element_width;
		if constexpr (num_registers <= 1)
		{
			return typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type
			(
				EmuSIMD::mul_all<per_element_width>
				(
					lhs_.template GetRegister<0>(),
					rhs_scalar_register_
				)
			);
		}
		else
		{
			return typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type
			(
				EmuSIMD::mul_all<per_element_width>
				(
					lhs_.template GetRegister<0>(),
					rhs_scalar_register_
				),
				EmuSIMD::mul_all<per_element_width>
				(
					lhs_.template GetRegister<1>(),
					rhs_scalar_register_
				)
			);
		}
	}
	
	template<EmuConcepts::EmuFastQuaternion FastQuaternion_, EmuConcepts::Arithmetic RhsScalar_>
	[[nodiscard]] constexpr inline auto fast_quaternion_multiply_scalar
	(
		const FastQuaternion_& lhs_,
		RhsScalar_&& rhs_scalar_
	)
		-> typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type
	{
		constexpr std::size_t per_element_width = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::per_element_width;
		using _required_register_type = typename EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::register_type;
		return EmuMath::Helpers::fast_quaternion_multiply_scalar
		(
			lhs_,
			EmuSIMD::set1<_required_register_type, per_element_width>(std::forward<RhsScalar_>(rhs_scalar_))
		);
	}
#pragma endregion

#pragma region MULTIPLY_ASSIGN_SCALAR_FUNCS
	template<EmuConcepts::EmuFastQuaternion FastQuaternion_>
	requires (!std::is_const_v<FastQuaternion_>)
	constexpr inline void fast_quaternion_multiply_assign_scalar
	(
		FastQuaternion_& lhs_and_out_,
		typename EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::register_arg_type rhs_scalar_register_
	)
	{
		constexpr std::size_t num_registers = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::num_registers;
		constexpr std::size_t per_element_width = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::per_element_width;
		lhs_and_out_.template GetRegister<0>() = EmuSIMD::mul_all<per_element_width>
		(
			lhs_and_out_.template GetRegister<0>(), 
			rhs_scalar_register_
		);

		if constexpr (num_registers > 1)
		{
			lhs_and_out_.template GetRegister<1>() = EmuSIMD::mul_all<per_element_width>
			(
				lhs_and_out_.template GetRegister<1>(), 
				rhs_scalar_register_
			);
		}
	}

	template<EmuConcepts::EmuFastQuaternion FastQuaternion_, EmuConcepts::Arithmetic RhsScalar_>
	[[nodiscard]] constexpr inline void fast_quaternion_multiply_assign_scalar(FastQuaternion_& lhs_and_out_, RhsScalar_&& rhs_scalar_)
	{
		constexpr std::size_t per_element_width = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::per_element_width;
		using _required_register_type = typename EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::register_type;
		return EmuMath::Helpers::fast_quaternion_multiply_assign_scalar
		(
			lhs_and_out_,
			EmuSIMD::set1<_required_register_type, per_element_width>(std::forward<RhsScalar_>(rhs_scalar_))
		);
	}
#pragma endregion

#pragma region MULTIPLY_QUATERNION_FUNCS
	template<EmuConcepts::EmuFastQuaternion FastQuaternion_>
	[[nodiscard]] constexpr inline auto fast_quaternion_multiply_quaternion(const FastQuaternion_& lhs_quat_, const FastQuaternion_& rhs_quat_)
		-> typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type
	{
		return EmuMath::Helpers::_fast_quaternion_underlying::_multiply_quaternion<true>
		(
			lhs_quat_,
			rhs_quat_
		);
	}

	template<EmuConcepts::EmuFastQuaternion FastQuaternion_>
	requires (!std::is_const_v<FastQuaternion_>)
	[[nodiscard]] constexpr inline void fast_quaternion_multiply_assign_quaternion(FastQuaternion_& lhs_and_out_quat_, const FastQuaternion_& rhs_quat_)
	{
		if constexpr (EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::num_registers > 1)
		{
			lhs_and_out_quat_ = EmuMath::Helpers::_fast_quaternion_underlying::_multiply_quaternion<true>
			(
				lhs_and_out_quat_,
				rhs_quat_
			);
		}
		else
		{
			lhs_and_out_quat_.template GetRegister<0>() = EmuMath::Helpers::_fast_quaternion_underlying::_multiply_quaternion<false>
			(
				lhs_and_out_quat_,
				rhs_quat_
			);
		}
	}
#pragma endregion
}

#endif
