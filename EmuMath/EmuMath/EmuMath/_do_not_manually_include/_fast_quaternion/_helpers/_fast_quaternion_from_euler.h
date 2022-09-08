#ifndef EMU_MATH_FAST_QUATERNION_FROM_EULER_H_INC_
#define EMU_MATH_FAST_QUATERNION_FROM_EULER_H_INC_ 1

#include "_common_fast_quaternion_includes.h"

namespace EmuMath::Helpers
{
	template
	<
		EmuConcepts::EmuFastQuaternion OutQuaternion_, bool InRads_ = true, bool Normalise_ = true,
		EmuConcepts::Arithmetic X_, EmuConcepts::Arithmetic Y_, EmuConcepts::Arithmetic Z_
	>
	[[nodiscard]] constexpr inline auto fast_quaternion_from_euler(X_&& x_, Y_&& y_, Z_&& z_)
		-> typename EmuCore::TMP::remove_ref_cv<OutQuaternion_>::type
	{
		using _out_fast_quat_uq = typename EmuCore::TMP::remove_ref_cv<OutQuaternion_>::type;
		auto euler_simd_xyz = _fast_quaternion_underlying::_make_euler_registers<OutQuaternion_>
		(
			std::forward<X_>(x_),
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);

		if constexpr (_out_fast_quat_uq::num_registers > 1)
		{
			// TODO: > 1 register
		}
		else
		{
			using _register_type = typename _out_fast_quat_uq::register_type;
			constexpr std::size_t width = _out_fast_quat_uq::per_element_width;
			constexpr bool is_signed = _out_fast_quat_uq::is_signed;

			if constexpr (!InRads_)
			{
				euler_simd_xyz = EmuSIMD::mul_all<width>
				(
					euler_simd_xyz,
					EmuSIMD::set1<_register_type>(EmuCore::Pi::PI_DIV_180<typename _out_fast_quat_uq::value_type>)
				);
			}

			// Store euler / 2 at first as it's needed for both trig ops
			// --- May be better to multiply by 0.5, but set to /2 to avoid lossy halving and for weird cases such as integral input
			// --- May be reasonable to give a `PreferMultiplies_` option as per normal Quaternions, should be put into consideration first
			//_register_type sin_xyz = EmuSIMD::mul_all<width>(euler_simd_xyz, EmuSIMD::set1<_register_type, width>(0.5));
			_register_type sin_xyz = EmuSIMD::div<width, is_signed>(euler_simd_xyz, EmuSIMD::set1<_register_type, width>(2));
			_register_type cos_xyz = EmuSIMD::cos<width, is_signed>(sin_xyz);
			sin_xyz = EmuSIMD::sin<width, is_signed>(sin_xyz);

			// NEEDS GENERALISING STILL: ONLY SUPPORTS 4-ELEMENT REGISTERS
			_register_type sin_and_cos_xy = EmuSIMD::shuffle_full_width<0, 1, 0, 1>(sin_xyz, cos_xyz);	// sin(x), sin(y), cos(x), cos(y)
			_register_type sin_and_cos_z = EmuSIMD::shuffle_full_width<2, 2, 2, 2>(sin_xyz, cos_xyz);	// sin(z), sin(z), cos(z), cos(z)

			// Calculate the product of the sines and cosines of x and z.
			_register_type temp_0 = EmuSIMD::shuffle_full_width<0, 2, 0, 2>(sin_and_cos_xy);	// sin(x), cos(x), sin(x), cos(x)
			_register_type x_MUL_z = EmuSIMD::mul_all<width>(temp_0, sin_and_cos_z);			// sin(x) * sin(z), cos(x) * sin(z), sin(x) * cos(z), cos(x) * cos(z)

			// Initial multiplication
			temp_0 = EmuSIMD::shuffle_full_width<1, 0, 2, 0>(x_MUL_z);
			_register_type temp_1 = EmuSIMD::shuffle_full_width<1, 3, 1, 1>(sin_and_cos_xy);	// sin(y), cos(y), sin(y), sin(y)
			_register_type xyzw = EmuSIMD::mul_all<width>(temp_0, temp_1);


			// Final multiplication with interchanging subtract/add ops
			temp_0 = EmuSIMD::shuffle_full_width<2, 3, 1, 3>(x_MUL_z);
			temp_1 = EmuSIMD::shuffle_full_width<3, 1, 3, 3>(sin_and_cos_xy);
			xyzw = EmuSIMD::fmaddsub<width>(temp_0, temp_1, xyzw);

			// Only normalise when the user wants it
			if constexpr (Normalise_)
			{
				temp_0 = EmuSIMD::dot_fill<width>(xyzw, xyzw);
				temp_0 = EmuSIMD::rsqrt<width, is_signed>(temp_0);
				xyzw = EmuSIMD::mul_all<width>(xyzw, temp_0);
			}

			return _out_fast_quat_uq(std::move(xyzw));
		}
	}
}

#endif
