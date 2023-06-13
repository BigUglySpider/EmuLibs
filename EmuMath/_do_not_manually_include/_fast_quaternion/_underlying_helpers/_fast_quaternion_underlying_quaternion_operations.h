#ifndef EMU_MATH_FAST_QUATERNION_UNDERLYING_QUATERNION_OPERATIONS_H_INC_
#define EMU_MATH_FAST_QUATERNION_UNDERLYING_QUATERNION_OPERATIONS_H_INC_ 1

#include "_fast_quaternion_tmp.h"
#include "_fast_quaternion_underlying_get.h"

namespace EmuMath::Helpers::_fast_quaternion_underlying
{
	template<bool OutScalar_, bool OutRegister_, bool Squared_, typename OutIfScalar_ = void, EmuConcepts::EmuFastQuaternion FastQuaternion_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_quaternion_calculate_norm(FastQuaternion_&& fast_quaternion_)
	{
		static_assert(!(OutScalar_ && OutRegister_), "INTERNAL EMUMATH ERROR: Underlying `_fast_quaternion_calculate_norm` function told that output is both scalar and a (SIMD) register; these are mutually exclusive and should never both be true.");

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
				if constexpr (OutRegister_)
				{
					return norm;
				}
				else
				{
					return _fast_quat_uq(std::move(norm));
				}
			}
			else
			{
				if constexpr (OutRegister_)
				{
					return EmuSIMD::sqrt<per_element_width, is_signed>(norm);
				}
				else
				{
					return _fast_quat_uq(EmuSIMD::sqrt<per_element_width, is_signed>(norm));
				}
			}
		}
	}

	template<bool Fused_, EmuConcepts::EmuFastQuaternion QuaternionA_, class B_, class T_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_quaternion_lerp(QuaternionA_&& a_, B_&& b_, T_&& t_)
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

	template<bool Fused_, EmuConcepts::EmuFastQuaternion QuaternionA_, class B_, class T_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_quaternion_slerp(QuaternionA_&& a_, B_&& b_, T_&& t_)
	{
		using _fast_quat_uq = typename std::remove_cvref<QuaternionA_>::type;
		using _register_type = typename _fast_quat_uq::register_type;
		constexpr std::size_t per_element_width = _fast_quat_uq::per_element_width;

		// Recursive call to convert scalar arguments to registers if we have any scalars
		if constexpr (EmuConcepts::Arithmetic<B_>)
		{
			if constexpr (EmuConcepts::Arithmetic<T_>)
			{
				return _fast_quaternion_slerp<Fused_>
				(
					std::forward<QuaternionA_>(a_),
					EmuSIMD::set1<_register_type, per_element_width>(std::forward<B_>(b_)),
					EmuSIMD::set1<_register_type, per_element_width>(std::forward<T_>(t_))
				);
			}
			else
			{
				return _fast_quaternion_slerp<Fused_>
				(
					std::forward<QuaternionA_>(a_),
					EmuSIMD::set1<_register_type, per_element_width>(std::forward<B_>(b_)),
					std::forward<T_>(t_)
				);
			}
		}
		else if constexpr (EmuConcepts::Arithmetic<T_>)
		{
			return _fast_quaternion_slerp<Fused_>
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
			constexpr bool is_signed = _fast_quat_uq::is_signed;

			// Common data
			const _fast_quat_uq& a_ref = std::forward<QuaternionA_>(a_);
			const _b_uq& b_ref = std::forward<B_>(b_);
			const _t_uq& t_ref = std::forward<T_>(t_);
			_register_type one = EmuSIMD::set1<_register_type, per_element_width>(1);

			// Calculate dot(a, b) for omega
			_register_type omega;
			if constexpr (num_registers <= 1)
			{
				omega = a_ref.template GetRegister<0>();
				if constexpr (elements_per_register > 4)
				{
					// Zero junk data to avoid including bits we don't want
					_register_type xyzw_mask = EmuSIMD::make_index_mask_for_first_x_elements<_register_type, 4, per_element_width>();
					omega = EmuSIMD::bitwise_and(omega, xyzw_mask);
				}
				omega = EmuSIMD::dot_fill<per_element_width>(omega, _fast_quaternion_get_register_arg_for_index<0>(b_ref));
			}
			else
			{
				const _register_type& a0 = a_ref.template GetRegister<0>();
				const _register_type& a1 = a_ref.template GetRegister<1>();

				// Perform a hand-written dot as an optimisation opportunity
				// --- Can even take advantage of fused operations if allowed
				if constexpr (Fused_)
				{
					omega = EmuSIMD::mul_all<per_element_width>(a0, _fast_quaternion_get_register_arg_for_index<0>(b_ref));
					omega = EmuSIMD::fmadd<per_element_width>
					(
						a1,
						_fast_quaternion_get_register_arg_for_index<1>(b_ref),
						omega
					);
				}
				else
				{
					omega = EmuSIMD::mul_all<per_element_width>(a0, _fast_quaternion_get_register_arg_for_index<0>(b_ref));
					omega = EmuSIMD::add<per_element_width>
					(
						omega,
						EmuSIMD::mul_all<per_element_width>(a1, _fast_quaternion_get_register_arg_for_index<1>(b_ref))
					);
				}
				omega = EmuSIMD::horizontal_sum_fill<per_element_width>(omega);
			}

			// Saturate omega to range -1:+1, and then calculate acos
			omega = EmuSIMD::clamp<per_element_width, is_signed>
			(
				omega,
				EmuSIMD::set1<_register_type, per_element_width>(-1),
				one
			);
			omega = EmuSIMD::acos<per_element_width, is_signed>(omega);

			// Calculate weightings and output results
			_register_type weighting_divisor = EmuSIMD::sin<per_element_width, is_signed>(omega);
			if constexpr (num_registers <= 1)
			{
				// ta = sin((1 - t) * omega) / weighting_divisor
				_register_type ta = EmuSIMD::sub<per_element_width>(one, _fast_quaternion_get_register_arg_for_index<0>(t_ref));
				ta = EmuSIMD::mul_all<per_element_width>(ta, omega);
				ta = EmuSIMD::sin<per_element_width, is_signed>(ta);
				ta = EmuSIMD::div<per_element_width, is_signed>(ta, weighting_divisor);

				// tb = sin(t * omega) / weighting_divisor
				_register_type tb = EmuSIMD::mul_all<per_element_width>(_fast_quaternion_get_register_arg_for_index<0>(t_ref), omega);
				tb = EmuSIMD::sin<per_element_width, is_signed>(tb);
				tb = EmuSIMD::div<per_element_width, is_signed>(tb, weighting_divisor);

				// Apply weighting to a and b values, and then add them
				_register_type weighted_b = EmuSIMD::mul_all<per_element_width>(_fast_quaternion_get_register_arg_for_index<0>(b_ref), tb);
				if constexpr (Fused_)
				{
					return _fast_quat_uq(EmuSIMD::fmadd<per_element_width>(a_ref.template GetRegister<0>(), ta, weighted_b));
				}
				else
				{
					_register_type weighted_a = EmuSIMD::mul_all<per_element_width>(a_ref.template GetRegister<0>(), ta);
					return _fast_quat_uq(EmuSIMD::add<per_element_width>(weighted_a, weighted_b));
				}
			}
			else
			{
				// Reuse t registers (while maintaining clean-ish) code to avoid potential inefficiencies when compiled
				// t0={x, y}, t1={z, w} weightings
				// tb = sin(t * omega) / weighting_divisor
				_register_type t0 = EmuSIMD::mul_all<per_element_width>(_fast_quaternion_get_register_arg_for_index<0>(t_ref), omega);
				t0 = EmuSIMD::sin<per_element_width, is_signed>(t0);
				t0 = EmuSIMD::div<per_element_width, is_signed>(t0, weighting_divisor);

				_register_type t1 = EmuSIMD::mul_all<per_element_width>(_fast_quaternion_get_register_arg_for_index<1>(t_ref), omega);
				t1 = EmuSIMD::sin<per_element_width, is_signed>(t1);
				t1 = EmuSIMD::div<per_element_width, is_signed>(t1, weighting_divisor);

				// Apply weighting to b values
				_register_type xy = EmuSIMD::mul_all<per_element_width>(_fast_quaternion_get_register_arg_for_index<0>(b_ref), t0);
				_register_type zw = EmuSIMD::mul_all<per_element_width>(_fast_quaternion_get_register_arg_for_index<1>(b_ref), t1);

				// Calculate a weightings
				// ta = sin((1 - t) * omega) / weighting_divisor
				t0 = EmuSIMD::sub<per_element_width>(one, _fast_quaternion_get_register_arg_for_index<0>(t_ref));
				t0 = EmuSIMD::mul_all<per_element_width>(t0, omega);
				t0 = EmuSIMD::sin<per_element_width, is_signed>(t0);
				t0 = EmuSIMD::div<per_element_width, is_signed>(t0, weighting_divisor);

				t1 = EmuSIMD::sub<per_element_width>(one, _fast_quaternion_get_register_arg_for_index<1>(t_ref));
				t1 = EmuSIMD::mul_all<per_element_width>(t1, omega);
				t1 = EmuSIMD::sin<per_element_width, is_signed>(t1);
				t1 = EmuSIMD::div<per_element_width, is_signed>(t1, weighting_divisor);

				// Apply weighting to a values and then add them with weighted b values
				if constexpr (Fused_)
				{
					xy = EmuSIMD::fmadd<per_element_width>(a_ref.template GetRegister<0>(), t0, xy);
					zw = EmuSIMD::fmadd<per_element_width>(a_ref.template GetRegister<1>(), t1, zw);
				}
				else
				{
					_register_type a_chunk = EmuSIMD::mul_all<per_element_width>(a_ref.template GetRegister<0>(), t0);
					xy = EmuSIMD::add<per_element_width>(xy, a_chunk);

					a_chunk = EmuSIMD::mul_all<per_element_width>(a_ref.template GetRegister<1>(), t1);
					zw = EmuSIMD::add<per_element_width>(zw, a_chunk);
				}
				return _fast_quat_uq(std::move(xy), std::move(zw));
			}
		}
	}

	template<EmuConcepts::EmuFastQuaternion FastQuaternion_>
	[[nodiscard]] constexpr inline auto _fast_quaternion_conjugate(FastQuaternion_&& in_)
		-> typename std::remove_cvref<FastQuaternion_>::type
	{
		using _fast_quat_uq = typename std::remove_cvref<FastQuaternion_>::type;
		using _register_type = typename _fast_quat_uq::register_type;
		constexpr std::size_t per_element_width = _fast_quat_uq::per_element_width;

		if constexpr (_fast_quat_uq::num_registers <= 1)
		{
			_register_type initial_chunk = std::forward<FastQuaternion_>(in_).template GetRegister<0>();
			_register_type negated_chunk = EmuSIMD::negate<per_element_width>(initial_chunk);
			_register_type xyz_mask = EmuSIMD::make_index_mask_for_first_x_elements<_register_type, 3, per_element_width>();
			negated_chunk = EmuSIMD::bitwise_and(xyz_mask, negated_chunk);
			initial_chunk = EmuSIMD::bitwise_andnot(xyz_mask, initial_chunk);
			return _fast_quat_uq(EmuSIMD::bitwise_or(negated_chunk, initial_chunk));
		}
		else
		{
			_register_type xy = std::forward<FastQuaternion_>(in_).template GetRegister<0>();
			_register_type initial_zw = std::forward<FastQuaternion_>(in_).template GetRegister<1>();
			xy = EmuSIMD::negate<per_element_width>(xy);

			// TODO: REPLACE WITH EMUSIMD EQUIVALENT OF E.G. _mm_sub_sd WHEN IMPLEMENTED
			// --- Can be shortened to `return _fast_quat_uq(std::move(xy), EmuSIMD::negate_first<per_element_width>(initial_zw));` when implemented (example name in `negate_first`)
			_register_type negated_zw = EmuSIMD::negate<per_element_width>(initial_zw);
			_register_type mask_z = EmuSIMD::make_index_mask_for_first_x_elements<_register_type, 1, per_element_width>();
			negated_zw = EmuSIMD::bitwise_and(mask_z, negated_zw);
			initial_zw = EmuSIMD::bitwise_andnot(mask_z, initial_zw);
			return _fast_quat_uq(std::move(xy), EmuSIMD::bitwise_or(negated_zw, initial_zw));
		}
	}

	template<bool PreferMultiplies_, EmuConcepts::EmuFastQuaternion FastQuaternion_>
	[[nodiscard]] constexpr inline auto _fast_quaternion_unit(FastQuaternion_&& in_conjugate_)
		-> typename std::remove_cvref<FastQuaternion_>::type
	{
		using _fast_quat_uq = typename std::remove_cvref<FastQuaternion_>::type;
		using _register_type = typename _fast_quat_uq::register_type;
		constexpr std::size_t per_element_width = _fast_quat_uq::per_element_width;
		constexpr bool is_signed = _fast_quat_uq::is_signed;
		constexpr std::size_t num_registers = _fast_quat_uq::num_registers;

		if constexpr (PreferMultiplies_ && _fast_quat_uq::is_floating_point)
		{
			_register_type length_reciprocal = _fast_quaternion_calculate_norm<false, true, true>(std::forward<FastQuaternion_>(in_conjugate_));
			length_reciprocal = EmuSIMD::rsqrt<per_element_width, is_signed>(length_reciprocal);
			_register_type normalised_0 = EmuSIMD::mul_all<per_element_width>
			(
				std::forward<FastQuaternion_>(in_conjugate_).template GetRegister<0>(),
				length_reciprocal
			);
			if constexpr (num_registers <= 1)
			{
				return _fast_quat_uq(std::move(normalised_0));
			}
			else
			{
				return _fast_quat_uq
				(
					std::move(normalised_0),
					EmuSIMD::mul_all<per_element_width>
					(
						std::forward<FastQuaternion_>(in_conjugate_).template GetRegister<1>(),
						length_reciprocal
					)
				);
			}
		}
		else
		{
			_register_type length = _fast_quaternion_calculate_norm<false, true, false>(std::forward<FastQuaternion_>(in_conjugate_));
			_register_type normalised_0 = EmuSIMD::div<per_element_width, is_signed>
			(
				std::forward<FastQuaternion_>(in_conjugate_).template GetRegister<0>(),
				length
			);
			if constexpr (num_registers <= 1)
			{
				return _fast_quat_uq(std::move(normalised_0));
			}
			else
			{
				return _fast_quat_uq
				(
					std::move(normalised_0),
					EmuSIMD::div<per_element_width, is_signed>
					(
						std::forward<FastQuaternion_>(in_conjugate_).template GetRegister<1>(),
						length
					)
				);
			}
		}
	}
	
	template<bool PreferMultiplies_, EmuConcepts::EmuFastQuaternion FastQuaternion_>
	[[nodiscard]] constexpr inline auto _fast_quaternion_inverse(FastQuaternion_&& in_)
		-> typename std::remove_cvref<FastQuaternion_>::type
	{
		return _fast_quaternion_unit<PreferMultiplies_>
		(
			_fast_quaternion_conjugate(std::forward<FastQuaternion_>(in_))
		);
	}
}

#endif
