#ifndef EMU_MATH_FAST_QUATERNION_FROM_EULER_H_INC_
#define EMU_MATH_FAST_QUATERNION_FROM_EULER_H_INC_ 1

#include "_common_fast_quaternion_includes.h"

namespace EmuMath::Helpers
{
#pragma region VALIDITY_CHECKS
	template<EmuConcepts::EmuFastQuaternion OutQuaternion_, class Arg_>
	[[nodiscard]] constexpr inline bool valid_single_arg_for_fast_quaternion_from_euler() noexcept
	{
		using _arg_uq = typename EmuCore::TMP::remove_ref_cv<Arg_>::type;
		using _out_register = typename EmuCore::TMP::remove_ref_cv_t<OutQuaternion_>::register_type;

		if constexpr (EmuSIMD::TMP::is_simd_register_v<_arg_uq>)
		{
			return std::is_same_v<_arg_uq, _out_register>;
		}
		else if constexpr (EmuConcepts::EmuVector<_arg_uq>)
		{
			return true;
		}
		else if constexpr (EmuConcepts::EmuFastVector<_arg_uq>)
		{
			using _in_register = typename _arg_uq::register_type;
			return (_arg_uq::size >= 3) && std::is_same_v<_in_register, _out_register>;
		}
		else if constexpr (EmuConcepts::StdArray<_arg_uq>)
		{
			using _in_value_type = typename _arg_uq::value_type;
			using _in_value_type_uq = typename EmuCore::TMP::remove_ref_cv<_in_value_type>::type;
			return std::is_same_v<_in_value_type, _out_register>;
		}
		else
		{
			return false;
		}
	}
#pragma endregion

#pragma region FROM_EULER_FUNCS
	template
	<
		EmuConcepts::EmuFastQuaternion OutQuaternion_, bool InRads_ = true, bool Normalise_ = true,
		EmuConcepts::Arithmetic X_, EmuConcepts::Arithmetic Y_, EmuConcepts::Arithmetic Z_
	>
	[[nodiscard]] constexpr inline auto fast_quaternion_from_euler(X_&& euler_x_, Y_&& euler_y_, Z_&& euler_z_)
		-> typename EmuCore::TMP::remove_ref_cv<OutQuaternion_>::type
	{
		return _fast_quaternion_underlying::_make_fast_quat_from_euler<OutQuaternion_, InRads_, Normalise_>
		(
			_fast_quaternion_underlying::_make_euler_registers<OutQuaternion_>
			(
				std::forward<X_>(euler_x_),
				std::forward<Y_>(euler_y_),
				std::forward<Z_>(euler_z_)
			)
		);
	}

	template<EmuConcepts::EmuFastQuaternion OutQuaternion_, bool InRads_ = true, bool Normalise_ = true, EmuConcepts::EmuFastVector EulerFastVector_>
	requires (valid_single_arg_for_fast_quaternion_from_euler<OutQuaternion_, EulerFastVector_>())
	[[nodiscard]] constexpr inline auto fast_quaternion_from_euler(EulerFastVector_&& euler_xyz_)
		-> typename EmuCore::TMP::remove_ref_cv<OutQuaternion_>::type
	{
		return _fast_quaternion_underlying::_make_fast_quat_from_euler<OutQuaternion_, InRads_, Normalise_>
		(
			std::forward<EulerFastVector_>(euler_xyz_)
		);
	}

	template<EmuConcepts::EmuFastQuaternion OutQuaternion_, bool InRads_ = true, bool Normalise_ = true, EmuConcepts::KnownSIMD EulerSIMD_>
	requires (valid_single_arg_for_fast_quaternion_from_euler<OutQuaternion_, EulerSIMD_>())
	[[nodiscard]] constexpr inline auto fast_quaternion_from_euler(EulerSIMD_&& euler_xyz_simd_)
		-> typename EmuCore::TMP::remove_ref_cv<OutQuaternion_>::type
	{
		return _fast_quaternion_underlying::_make_fast_quat_from_euler<OutQuaternion_, InRads_, Normalise_>
		(
			std::forward<EulerSIMD_>(euler_xyz_simd_)
		);
	}

	template<EmuConcepts::EmuFastQuaternion OutQuaternion_, bool InRads_ = true, bool Normalise_ = true, EmuConcepts::StdArray EulerSIMDArray_>
	requires (valid_single_arg_for_fast_quaternion_from_euler<OutQuaternion_, EulerSIMDArray_>())
	[[nodiscard]] constexpr inline auto fast_quaternion_from_euler(EulerSIMDArray_&& euler_xyz_simd_array_)
		-> typename EmuCore::TMP::remove_ref_cv<OutQuaternion_>::type
	{
		return _fast_quaternion_underlying::_make_fast_quat_from_euler<OutQuaternion_, InRads_, Normalise_>
		(
			std::forward<EulerSIMDArray_>(euler_xyz_simd_array_)
		);
	}

	template<EmuConcepts::EmuFastQuaternion OutQuaternion_, bool InRads_ = true, bool Normalise_ = true, EmuConcepts::EmuVector EulerVector_>
	requires (valid_single_arg_for_fast_quaternion_from_euler<OutQuaternion_, EulerVector_>())
	[[nodiscard]] constexpr inline auto fast_quaternion_from_euler(EulerVector_&& euler_vector_)
	{
		return _fast_quaternion_underlying::_make_fast_quat_from_euler<OutQuaternion_, InRads_, Normalise_>
		(
			std::forward<EulerVector_>(euler_vector_)
		);
	}
#pragma endregion
}

#endif
