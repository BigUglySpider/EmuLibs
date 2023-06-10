#ifndef EMU_MATH_FAST_QUATERNION_UNDERLYING_TO_EULER_H_INC_
#define EMU_MATH_FAST_QUATERNION_UNDERLYING_TO_EULER_H_INC_ 1

#include "_fast_quaternion_tmp.h"
#include "../../_quaternions/_helpers/_all_helpers.h"

namespace EmuMath::Helpers::_fast_quaternion_underlying
{
	template<class OutVector_, typename EulerT_, bool OutRads_, EmuConcepts::EmuFastQuaternion InFastQuaternion_, EmuConcepts::Arithmetic Epsilon_>
	[[nodiscard]] constexpr inline auto _make_euler_from_fast_quat(InFastQuaternion_&& in_quaternion_, Epsilon_&& epsilon_)
		-> OutVector_
	{
		// General types
		using _in_quat_uq = typename EmuCore::TMP::remove_ref_cv<InFastQuaternion_>::type;
		using _scalar_fp = typename _in_quat_uq::preferred_floating_point;

		// Dump xyzw to calculate as scalar
		// --- A large amount of shuffles and operations not making full use of register width would be required to stick to SIMD, 
		// --- which itself is slower than scalar
		_scalar_fp scalar_xyzw[_in_quat_uq::full_width_size];
		EmuSIMD::store(std::forward<InFastQuaternion_>(in_quaternion_).template GetRegister<0>(), scalar_xyzw);
		if constexpr (_in_quat_uq::num_registers > 1)
		{
			EmuSIMD::store
			(
				std::forward<InFastQuaternion_>(in_quaternion_).template GetRegister<1>(),
				scalar_xyzw + _in_quat_uq::elements_per_register
			);
		}

		constexpr bool valid_call = EmuMath::Helpers::_quaternion_underlying::_valid_convert_to_euler_args
		<
			true,
			_scalar_fp,
			false,
			OutRads_,
			_scalar_fp,
			_scalar_fp,
			_scalar_fp,
			_scalar_fp,
			Epsilon_,
			true
		>();

		if constexpr (valid_call)
		{
			using euler_result_type = decltype
			(
				EmuMath::Helpers::_quaternion_underlying::_convert_to_euler_vector<true, EulerT_, false, OutRads_>
				(
					std::move(scalar_xyzw[0]),
					std::move(scalar_xyzw[1]),
					std::move(scalar_xyzw[2]),
					std::move(scalar_xyzw[3]),
					std::forward<Epsilon_>(epsilon_)
				)
			);

			if constexpr (std::is_same_v<OutVector_, euler_result_type>)
			{
				return EmuMath::Helpers::_quaternion_underlying::_convert_to_euler_vector<true, EulerT_, false, OutRads_>
				(
					std::move(scalar_xyzw[0]),
					std::move(scalar_xyzw[1]),
					std::move(scalar_xyzw[2]),
					std::move(scalar_xyzw[3]),
					std::forward<Epsilon_>(epsilon_)
				);
			}
			else
			{
				if constexpr(std::is_constructible_v<OutVector_, euler_result_type>)
				{
					return OutVector_
					(
						EmuMath::Helpers::_quaternion_underlying::_convert_to_euler_vector<true, EulerT_, false, OutRads_>
						(
							std::move(scalar_xyzw[0]),
							std::move(scalar_xyzw[1]),
							std::move(scalar_xyzw[2]),
							std::move(scalar_xyzw[3]),
							std::forward<Epsilon_>(epsilon_)
						)
					);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutVector_>(),
						"Unable to convert an EmuMath FastQuaternion to euler angles as the desired output Vector type cannot be constructed from the intermediate scalar results."
					);
				}
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<InFastQuaternion_>(),
				"Unable to convert an EmuMath FastQuaternion to euler angles as the underlying scalar conversion cannot be called with the passed Quaternion's scalar data."
			);
		}
	}
}

#endif
