#ifndef EMU_MATH_FAST_QUATERNION_UNDERLYING_ARITHMETIC_H_INC_
#define EMU_MATH_FAST_QUATERNION_UNDERLYING_ARITHMETIC_H_INC_ 1

#include "_fast_quaternion_tmp.h"

namespace EmuMath::Helpers::_fast_quaternion_underlying
{
	template<bool OutQuat_, EmuConcepts::EmuFastQuaternion FastQuaternion_>
	[[nodiscard]] constexpr inline auto _multiply_quaternion(const FastQuaternion_& lhs_quat_, const FastQuaternion_& rhs_quat_)
		-> typename std::conditional
		<
			OutQuat_,
			typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type,
			typename EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::register_type
		>::type
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::register_type;
		constexpr std::size_t num_registers = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::num_registers;
		constexpr std::size_t width = EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::per_element_width;

		if constexpr (num_registers > 1)
		{
			if constexpr (!OutQuat_)
			{
				static_assert
				(
					EmuCore::TMP::get_false<num_registers>(),
					"Unable to output a register with `EmuMath::Helpers::_fast_quaternion_underlying::_multiply_quaternion` as the FastQuaternion type requires multiple registers."
				);
			}
			else
			{
				_register_type_uq lhs_xy = lhs_quat_.template GetRegister<0>();
				_register_type_uq lhs_zw = lhs_quat_.template GetRegister<1>();
				_register_type_uq rhs_xy = rhs_quat_.template GetRegister<0>();
				_register_type_uq rhs_zw = rhs_quat_.template GetRegister<1>();

				// Starting xy = fmsub(lhs.YZ, rhs.ZX, lhs.ZX * rhs.YZ)
				_register_type_uq xy = EmuSIMD::shuffle_full_width<0, 0>(lhs_zw, lhs_xy);
				xy = EmuSIMD::mul_all<width>(xy, EmuSIMD::shuffle_full_width<1, 0>(rhs_xy, rhs_zw));
				xy = EmuSIMD::fmsub<width>(EmuSIMD::shuffle_full_width<1, 0>(lhs_xy, lhs_zw), EmuSIMD::shuffle_full_width<0, 0>(rhs_zw, rhs_xy), xy);

				_register_type_uq temp_0 = EmuSIMD::set_all_to_index<1, width>(rhs_zw); // temp_0 = rhs.WW until stated otherwise
				xy = EmuSIMD::fmadd<width>(lhs_xy, temp_0, xy); // xy = fmadd(lhs.XY, rhs.WW, xy)
				_register_type_uq temp_1 = EmuSIMD::set_all_to_index<1, width>(lhs_zw); // temp_1 = lhs.WW until stated otherwise
				xy = EmuSIMD::fmadd<width>(temp_1, rhs_xy, xy); // xy = fmadd(lhs.WW, rhs.XY, xy)

				// Starting zw = fmsub(lhs.XW, rhs.YW, lhs.YX * rhs.XX)
				_register_type_uq zw = EmuSIMD::shuffle_full_width<1, 0>(lhs_xy);
				zw = EmuSIMD::mul_all<width>(zw, EmuSIMD::set_all_to_index<0, width>(rhs_xy));
				zw = EmuSIMD::fmsub<width>(EmuSIMD::shuffle_full_width<0, 1>(lhs_xy, lhs_zw), EmuSIMD::shuffle_full_width<1, 1>(rhs_xy, rhs_zw), zw);

				// temp_0 = result.Z
				temp_0 = EmuSIMD::fmadd<width>(lhs_zw, temp_0, zw);		// z = fmadd(lhs.Z, rhs.W, z)
				temp_0 = EmuSIMD::fmadd<width>(temp_1, rhs_zw, temp_0);	// z = fmadd(lhs.W, rhs.Z, z)

				// ZW used for calculating just W
				// temp_1 = (lhs.YZ * rhs.YZ)
				temp_1 = EmuSIMD::shuffle_full_width<1, 0>(lhs_xy, lhs_zw);
				temp_1 = EmuSIMD::mul_all<width>(temp_1, EmuSIMD::shuffle_full_width<1, 0>(rhs_xy, rhs_zw));

				// w = (w - (lhs.y * rhs.y)) - (lhs.z * rhs.z)
				temp_1 = EmuSIMD::add<width>(temp_1, EmuSIMD::shuffle_full_width<1, 0>(temp_1));
				zw = EmuSIMD::sub<width>(zw, temp_1);

				return typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type
				(
					std::move(xy),
					EmuSIMD::blend<0, 1>(temp_0, zw)
				);
			}
		}
		else
		{
			_register_type_uq lhs = lhs_quat_.template GetRegister<0>();
			_register_type_uq rhs = rhs_quat_.template GetRegister<0>();

			// Starting xyzw = fmsub(lhs.YZXW, rhs.ZXYW, lhs.ZXYX * rhs.YZXX)
			_register_type_uq xyzw = EmuSIMD::shuffle_full_width<2, 0, 1, 0>(lhs);
			xyzw = EmuSIMD::mul_all<width>(xyzw, EmuSIMD::shuffle_full_width<1, 2, 0, 0>(rhs));
			xyzw = EmuSIMD::fmsub<width>(EmuSIMD::shuffle_full_width<1, 2, 0, 3>(lhs), EmuSIMD::shuffle_full_width<2, 0, 1, 3>(rhs), xyzw);

			_register_type_uq xyz = EmuSIMD::fmadd<width>(lhs, EmuSIMD::set_all_to_index<3, width>(rhs), xyzw);	// xyz = fmadd(lhs.XYZ, rhs.WWW, xyz)
			xyz = EmuSIMD::fmadd<width>(EmuSIMD::set_all_to_index<3, width>(lhs), rhs, xyz);					// xyz = fmadd(lhs.WWW, rhs.XYZ, xyz)

			// XYZW used for calculating just W
			_register_type_uq lhs_mul_rhs = EmuSIMD::mul_all<width>(lhs, rhs);
			lhs_mul_rhs = EmuSIMD::add<width>(EmuSIMD::set_all_to_index<1, width>(lhs_mul_rhs), EmuSIMD::set_all_to_index<2, width>(lhs_mul_rhs));
			xyzw = EmuSIMD::sub<width>(xyzw, lhs_mul_rhs); // w = (w - (lhs.y * rhs.y)) - (lhs.z * rhs.z)

			if constexpr (OutQuat_)
			{
				return typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type(EmuSIMD::blend<0, 0, 0, 1>(xyz, xyzw));
			}
			else
			{
				return EmuSIMD::blend<0, 0, 0, 1>(xyz, xyzw);
			}
		}
	}
}

#endif
