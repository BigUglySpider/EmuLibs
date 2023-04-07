#ifndef EMU_MATH_FAST_QUATERNION_UNDERLYING_QUATERNION_OPERATIONS_H_INC_
#define EMU_MATH_FAST_QUATERNION_UNDERLYING_QUATERNION_OPERATIONS_H_INC_ 1

#include "_fast_quaternion_tmp.h"
#include "_fast_quaternion_underlying_get.h"

namespace EmuMath::Helpers::_fast_quaternion_underlying
{
	template<bool OutScalar_, bool Squared_, typename OutIfScalar_ = void, EmuConcepts::EmuFastQuaternion FastQuaternion_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_quaternion_calculate_norm(FastQuaternion_&& fast_quaternion_)
	{
		using _fast_quat_uq = typename std::remove_cvref<FastQuaternion_>::type;
		using _register_type = typename _fast_quat_uq::register_type;
		using _value_type = typename _fast_quat_uq::value_type;
		constexpr std::size_t per_element_width = _fast_quat_uq::per_element_width;
		constexpr std::size_t elements_per_register = _fast_quat_uq::elements_per_register;
		constexpr bool is_signed = _fast_quat_uq::is_signed;

		_register_type norm = std::forward<FastQuaternion_>(fast_quaternion_).template GetRegister<0>();
		norm = EmuSIMD::mul_all<per_element_width>(norm, norm);

		// Append other register if needed.
		// --- Safe to assume registers are split into 2: [xy], [zw]
		if constexpr (_fast_quat_uq::num_registers > 1)
		{
			_register_type other_register = std::forward<FastQuaternion_>(fast_quaternion_).template GetRegister<1>();
			norm = EmuSIMD::fmadd<per_element_width>(other_register, other_register, norm);
		}

		// Mask out extra elements if a register contains more than just xyzw (e.g. 8-element registers), so we don't add junk
		// --- If < 4, assume using two registers of size 2 which have had their squares vertically added, so safe to skip
		// --- If == 4, safe to do a full-width horizontal sum, so safe to skip
		if constexpr (elements_per_register > 4)
		{
			_register_type xyzw_mask = EmuSIMD::make_index_mask_for_first_x_elements<_register_type, 4, per_element_width>();
			norm = EmuSIMD::bitwise_and(norm, xyzw_mask);
		}

		// Finish summing up values
		// --- If outputting a register, we need to guarantee that all elements will be the norm
		// --- If outputting a scalar, we can ignore this guarantee and gain a potential performance boost
		if constexpr (OutScalar_)
		{
			if constexpr (!std::is_void_v<OutIfScalar_>)
			{
				if constexpr (Squared_)
				{
					return EmuSIMD::horizontal_sum_scalar<OutIfScalar_, per_element_width>(norm);
				}
				else
				{
					// `horizontal_sum` is guaranteed to contain the result in index 0, but not necessarily any other indices
					norm = EmuSIMD::horizontal_sum<per_element_width>(norm);
					norm = EmuSIMD::sqrt<per_element_width, is_signed>(norm);
					return EmuSIMD::get_index<0, OutIfScalar_, per_element_width>(norm);
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<OutIfScalar_>(), "INTERNAL EMUMATH ERROR: `void` output type provided to underlying FastQuaternion Norm calculation when expecting to output as a named scalar type.");
			}
		}
		else
		{
			norm = EmuSIMD::horizontal_sum_fill<per_element_width>(norm);
			if constexpr (Squared_)
			{
				return norm;
			}
			else
			{
				return EmuSIMD::sqrt<per_element_width, is_signed>(norm);
			}
		}
	}

	template<bool Fused_, EmuConcepts::EmuFastQuaternion QuaternionA_, class B_, class T_>
	[[nodiscard]] constexpr inline auto _fast_quaternion_lerp(QuaternionA_&& a_, B_&& b_, T_&& t_)
	{
		using _fast_quat_uq = typename std::remove_cvref<QuaternionA_>::type;
		using _register_type = typename _fast_quat_uq::register_type;
		constexpr std::size_t per_element_width = _fast_quat_uq::per_element_width;

		// Recursive call to convert scalar arguments to registers if we have any scalars
		if constexpr (EmuConcepts::Arithmetic<B_>)
		{
			if constexpr (EmuConcepts::Arithmetic<T_>)
			{
				return _fast_quaternion_lerp<Fused_>
				(
					std::forward<QuaternionA_>(a_),
					EmuSIMD::set1<_register_type, per_element_width>(std::forward<B_>(b_)),
					EmuSIMD::set1<_register_type, per_element_width>(std::forward<T_>(t_))
				);
			}
			else
			{
				return _fast_quaternion_lerp<Fused_>
				(
					std::forward<QuaternionA_>(a_),
					EmuSIMD::set1<_register_type, per_element_width>(std::forward<B_>(b_)),
					std::forward<T_>(t_)
				);
			}
		}
		else if constexpr (EmuConcepts::Arithmetic<T_>)
		{
			return _fast_quaternion_lerp<Fused_>
			(
				std::forward<QuaternionA_>(a_),
				std::forward<B_>(b_),
				EmuSIMD::set1<_register_type, per_element_width>(std::forward<T_>(t_))
			);
		}
		else
		{
			// Actual calculation, guaranteed registers or quaternions by this point if well-formed
			using _b_uq = typename std::remove_cvref<B_>::type;
			using _t_uq = typename std::remove_cvref<T_>::type;
			using _value_type = typename _fast_quat_uq::value_type;
			constexpr std::size_t elements_per_register = _fast_quat_uq::elements_per_register;
			constexpr std::size_t num_registers = _fast_quat_uq::num_registers;

			// All calculations are a + ((b - a) * t)
			if constexpr (num_registers <= 1)
			{
				const _register_type& a_register = std::forward<QuaternionA_>(a_).template GetRegister<0>();
				_register_type xyzw = EmuSIMD::sub<per_element_width>(_fast_quaternion_get_register_arg_for_index<0>(std::forward<B_>(b_)), a_register);
				if constexpr (Fused_)
				{
					xyzw = EmuSIMD::fmadd<per_element_width>(xyzw, _fast_quaternion_get_register_arg_for_index<0>(std::forward<T_>(t_)), a_register);
				}
				else
				{
					xyzw = EmuSIMD::mul_all<per_element_width>(xyzw, _fast_quaternion_get_register_arg_for_index<0>(std::forward<T_>(t_)));
					xyzw = EmuSIMD::add<per_element_width>(xyzw, a_register);
				}
				return _fast_quat_uq(std::move(xyzw));
			}
			else
			{
				const _fast_quat_uq & a_ref = std::forward<QuaternionA_>(a_);
				const _b_uq& b_ref = std::forward<B_>(b_);
				const _t_uq& t_ref = std::forward<T_>(t_);

				const _register_type& a_register_0 = a_ref.template GetRegister<0>();
				_register_type xy = EmuSIMD::sub<per_element_width>(_fast_quaternion_get_register_arg_for_index<0>(b_ref), a_register_0);
				const _register_type& a_register_1 = a_ref.template GetRegister<1>();
				_register_type zw = EmuSIMD::sub<per_element_width>(_fast_quaternion_get_register_arg_for_index<1>(b_ref), a_register_1);

				if constexpr (Fused_)
				{
					xy = EmuSIMD::fmadd<per_element_width>(xy, _fast_quaternion_get_register_arg_for_index<0>(t_ref), a_register_0);
					zw = EmuSIMD::fmadd<per_element_width>(zw, _fast_quaternion_get_register_arg_for_index<1>(t_ref), a_register_1);
				}
				else
				{
					xy = EmuSIMD::mul_all<per_element_width>(xy, _fast_quaternion_get_register_arg_for_index<0>(t_ref));
					xy = EmuSIMD::add<per_element_width>(xy, a_register_0);
					zw = EmuSIMD::mul_all<per_element_width>(zw, _fast_quaternion_get_register_arg_for_index<1>(t_ref));
					zw = EmuSIMD::add<per_element_width>(zw, a_register_1);
				}
				return _fast_quat_uq(std::move(xy), std::move(zw));
			}
		}
	}
}

#endif
