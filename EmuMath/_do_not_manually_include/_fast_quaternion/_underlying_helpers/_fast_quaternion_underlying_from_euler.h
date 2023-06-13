#ifndef EMU_MATH_FAST_QUATERNION_UNDERLYING_FROM_EULER_H_INC_
#define EMU_MATH_FAST_QUATERNION_UNDERLYING_FROM_EULER_H_INC_ 1

#include "_fast_quaternion_tmp.h"
#include <array>

namespace EmuMath::Helpers::_fast_quaternion_underlying
{
	template<std::size_t Index_, typename X_, typename Y_, typename Z_>
	[[nodiscard]] constexpr inline decltype(auto) _get_euler_register_arg(std::tuple<X_, Y_, Z_>& euler_xyz_) noexcept
	{
		if constexpr(Index_ < 3)
		{
			using _euler_xyz_get_result = decltype(std::get<Index_>(euler_xyz_));
			return std::forward<_euler_xyz_get_result>
			(
				std::get<Index_>(euler_xyz_)
			);
		}
		else
		{
			return 1;
		}
	}

	template
	<
		std::size_t RegisterIndex_, EmuConcepts::EmuFastQuaternion FastQuaternion_,
		typename X_, typename Y_, typename Z_, std::size_t...RegisterElementIndices_
	>
	[[nodiscard]] constexpr inline auto _make_euler_register(std::tuple<X_, Y_, Z_>& euler_xyz_) noexcept
	{
		using _fast_quat_uq = typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type;
		constexpr std::size_t element_offset = RegisterIndex_ * _fast_quat_uq::elements_per_register;
		return EmuSIMD::setr<typename _fast_quat_uq::register_type, _fast_quat_uq::per_element_width>
		(
			std::forward<decltype(_get_euler_register_arg<element_offset + RegisterElementIndices_>(euler_xyz_))>
			(
				_get_euler_register_arg<element_offset + RegisterElementIndices_>(euler_xyz_)
			)...
		);
	}

	template<EmuConcepts::EmuFastQuaternion FastQuaternion_, typename X_, typename Y_, typename Z_, std::size_t...RegisterIndices_>
	[[nodiscard]] constexpr inline auto _make_array_of_euler_registers
	(
		std::tuple<X_, Y_, Z_>& euler_xyz_,
		std::index_sequence<RegisterIndices_...> register_indices_
	) noexcept -> std::array<typename EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::register_type, sizeof...(RegisterIndices_)>
	{
		using _fast_quat_uq = typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type;
		return std::array<typename _fast_quat_uq::register_type, sizeof...(RegisterIndices_)>
		({
			_make_euler_register<RegisterIndices_, FastQuaternion_, X_, Y_, Z_, 0, 1>
			(
				euler_xyz_
			)...
		});
	}

	template<EmuConcepts::EmuFastQuaternion FastQuaternion_, typename X_, typename Y_, typename Z_>
	[[nodiscard]] constexpr inline decltype(auto) _make_euler_registers(X_&& x_, Y_&& y_, Z_&& z_) noexcept
	{
		using _fast_quat_uq = typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type;
		if constexpr (_fast_quat_uq::elements_per_register == 4)
		{
			return EmuSIMD::set<typename _fast_quat_uq::register_type, _fast_quat_uq::per_element_width>
			(
				0,
				std::forward<Z_>(z_),
				std::forward<Y_>(y_),
				std::forward<X_>(x_)
			);
		}
		else
		{
			auto euler_xyz = std::forward_as_tuple(std::forward<X_>(x_), std::forward<Y_>(y_), std::forward<Z_>(z_));
			if constexpr (_fast_quat_uq::elements_per_register >= 3)
			{
				return _make_euler_register<0, FastQuaternion_>(euler_xyz);
			}
			else
			{
				constexpr bool requires_partial_register = (3 % _fast_quat_uq::elements_per_register) != 0;
				constexpr std::size_t required_register_count = (3 / _fast_quat_uq::elements_per_register) + static_cast<std::size_t>(requires_partial_register);
				using register_index_sequence = std::make_index_sequence<required_register_count>;
				return _make_array_of_euler_registers<FastQuaternion_>(euler_xyz, register_index_sequence());
			}
		}
	}

	template<EmuConcepts::EmuFastQuaternion OutQuaternion_, bool InRads_, bool Normalise_, class EulerXYZ_>
	[[nodiscard]] constexpr inline auto _make_fast_quat_from_euler(EulerXYZ_&& euler_xyz_)
		-> typename EmuCore::TMP::remove_ref_cv<OutQuaternion_>::type
	{
		using euler_xyz_uq = typename EmuCore::TMP::remove_ref_cv<EulerXYZ_>::type;
		if constexpr (EmuMath::TMP::is_emu_vector_v<euler_xyz_uq>)
		{
			// Convert EmuMath vector to register(s) and call back on this with said register(s)
			EMU_CORE_MSVC_PUSH_WARNING_STACK
			EMU_CORE_MSVC_DISABLE_WARNING(EMU_CORE_WARNING_BAD_MOVE)
			return _make_fast_quat_from_euler<OutQuaternion_, InRads_, Normalise_>
			(
				_make_euler_registers<OutQuaternion_>
				(
					std::forward<EulerXYZ_>(euler_xyz_).template AtTheoretical<0>(),
					std::forward<EulerXYZ_>(euler_xyz_).template AtTheoretical<1>(),
					std::forward<EulerXYZ_>(euler_xyz_).template AtTheoretical<2>()
				)
			);
			EMU_CORE_MSVC_POP_WARNING_STACK
		}
		else if constexpr(EmuMath::TMP::is_emu_fast_vector_v<euler_xyz_uq>)
		{
			// Call back on this with the register(s) of the passed FastVector
			return _make_fast_quat_from_euler<OutQuaternion_, InRads_, Normalise_>
			(
				std::forward<EulerXYZ_>(euler_xyz_).data
			);
		}
		else if constexpr (EmuCore::TMP::is_std_array_v<euler_xyz_uq>)
		{
			constexpr bool is_simd_array = (EmuConcepts::KnownSIMD<typename euler_xyz_uq::value_type>);
			if constexpr (!is_simd_array)
			{
				// Convert scalar array to simd register(s) and call back on this with said register(s)
				EMU_CORE_MSVC_PUSH_WARNING_STACK
				EMU_CORE_MSVC_DISABLE_WARNING(EMU_CORE_WARNING_BAD_MOVE)
				constexpr std::size_t array_size = euler_xyz_uq::size();
				if constexpr (array_size >= 3)
				{
					return _make_fast_quat_from_euler<OutQuaternion_, InRads_, Normalise_>
					(
						_make_euler_registers<OutQuaternion_>
						(
							std::get<0>(std::forward<EulerXYZ_>(euler_xyz_)),
							std::get<1>(std::forward<EulerXYZ_>(euler_xyz_)),
							std::get<2>(std::forward<EulerXYZ_>(euler_xyz_))
						)
					);
				}
				else if constexpr (array_size >= 2)
				{
					return _make_fast_quat_from_euler<OutQuaternion_, InRads_, Normalise_>
					(
						_make_euler_registers<OutQuaternion_>
						(
							std::get<0>(std::forward<EulerXYZ_>(euler_xyz_)),
							std::get<1>(std::forward<EulerXYZ_>(euler_xyz_)),
							0
						)
					);
				}
				else if constexpr (array_size >= 1)
				{
					return _make_fast_quat_from_euler<OutQuaternion_, InRads_, Normalise_>
					(
						_make_euler_registers<OutQuaternion_>
						(
							std::get<0>(std::forward<EulerXYZ_>(euler_xyz_)),
							0,
							0
						)
					);
				}
				else
				{
					return _make_fast_quat_from_euler<OutQuaternion_, InRads_, Normalise_>
					(
						_make_euler_registers<OutQuaternion_>(0, 0, 0)
					);
				}
				EMU_CORE_MSVC_POP_WARNING_STACK
			}
			else
			{
				// Array of registers collectively representing XYZ
				using _out_fast_quat = typename EmuCore::TMP::remove_ref_cv<OutQuaternion_>::type;
				if constexpr (EmuSIMD::TMP::register_element_count_v<typename euler_xyz_uq::value_type, _out_fast_quat::per_element_width> >= 3)
				{
					// Call back on this with just the first register, no need to iterate over arrays
					return _make_fast_quat_from_euler<OutQuaternion_, InRads_, Normalise_>
					(
						std::get<0>(std::forward<EulerXYZ_>(euler_xyz_))
					);
				}
				else
				{
					// Since we are SIMD, we know this is a case of 2 elements per register, as > 2 covered by single-register branch and < 2 is not SIMD
					// --- This is likely quite inefficient based on speed comparisons
					using _register_type = typename _out_fast_quat::register_type;
					constexpr std::size_t width = _out_fast_quat::per_element_width;
					constexpr bool is_signed = _out_fast_quat::is_signed;

EMU_CORE_MSVC_PUSH_WARNING_STACK
EMU_CORE_MSVC_DISABLE_WARNING(EMU_CORE_WARNING_BAD_MOVE)
					_register_type sin_xy = std::get<0>(std::forward<EulerXYZ_>(euler_xyz_));
					_register_type sin_z = std::get<1>(std::forward<EulerXYZ_>(euler_xyz_));
					sin_z = EmuSIMD::shuffle<0>(sin_z);
EMU_CORE_MSVC_POP_WARNING_STACK

					if constexpr (!InRads_)
					{
						_register_type pi_div_180 = EmuSIMD::set1<_register_type>(EmuCore::Pi::PI_DIV_180<typename _out_fast_quat::value_type>);
						sin_xy = EmuSIMD::mul_all<width>(sin_xy, pi_div_180);
						sin_z = EmuSIMD::mul_all<width>(sin_z, pi_div_180);
					}

					_register_type temp_0 = EmuSIMD::set1<_register_type, width>(typename _out_fast_quat::value_type(0.5));
					sin_xy = EmuSIMD::mul_all<width>(sin_xy, temp_0);
					sin_z = EmuSIMD::mul_all<width>(sin_z, temp_0);
					_register_type cos_xy = EmuSIMD::cos<width, is_signed>(sin_xy);
					sin_xy = EmuSIMD::sin<width, is_signed>(sin_xy);
					_register_type cos_z = EmuSIMD::cos<width, is_signed>(sin_z);
					sin_z = EmuSIMD::sin<width, is_signed>(sin_z);

					// lo
					_register_type sinz_MUL_cosandsin_x = EmuSIMD::mul_all<width>(sin_z, EmuSIMD::shuffle<0, 0>(cos_xy, sin_xy));
					_register_type cosz_MUL_sinandcos_x = EmuSIMD::mul_all<width>(cos_z, EmuSIMD::shuffle<0, 0>(sin_xy, cos_xy));
					_register_type xy = EmuSIMD::mul_all<width>(sinz_MUL_cosandsin_x, EmuSIMD::shuffle<1, 1>(sin_xy, cos_xy));
					xy = EmuSIMD::fmaddsub<width>(cosz_MUL_sinandcos_x, EmuSIMD::shuffle<1, 1>(cos_xy, sin_xy), xy);

					// hi
					_register_type zw = EmuSIMD::shuffle<0, 1>(cosz_MUL_sinandcos_x, sinz_MUL_cosandsin_x);
					zw = EmuSIMD::mul_all<width>(zw, EmuSIMD::set_all_to_index<1>(sin_xy));
					zw = EmuSIMD::fmaddsub<width>
					(
						EmuSIMD::shuffle<0, 1>(sinz_MUL_cosandsin_x, cosz_MUL_sinandcos_x),
						EmuSIMD::shuffle<1, 1>(cos_xy),
						zw
					);

					if constexpr (Normalise_)
					{
						temp_0 = EmuSIMD::mul_all<width>(xy, xy);
						temp_0 = EmuSIMD::fmadd<width>(zw, zw, temp_0);
						temp_0 = EmuSIMD::horizontal_sum_fill<width>(temp_0);

						if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<_register_type>)
						{
							temp_0 = EmuSIMD::sqrt<width, is_signed>(temp_0);
							xy = EmuSIMD::div<width, is_signed>(xy, temp_0);
							zw = EmuSIMD::div<width, is_signed>(zw, temp_0);
						}
						else
						{
							temp_0 = EmuSIMD::rsqrt<width, is_signed>(temp_0);
							xy = EmuSIMD::mul_all<width>(xy, temp_0);
							zw = EmuSIMD::mul_all<width>(zw, temp_0);
						}
					}

					return _out_fast_quat(std::move(xy), std::move(zw));
				}
			}
		}
		else if constexpr (EmuSIMD::TMP::is_simd_register_v<euler_xyz_uq>)
		{
			// Single register representing XYZ
			using _out_fast_quat = typename EmuCore::TMP::remove_ref_cv<OutQuaternion_>::type;
			using _register_type = typename _out_fast_quat::register_type;
			constexpr std::size_t width = _out_fast_quat::per_element_width;
			constexpr bool is_signed = _out_fast_quat::is_signed;
			_register_type euler_simd_xyz = std::forward<EulerXYZ_>(euler_xyz_);

			if constexpr (!InRads_)
			{
				euler_simd_xyz = EmuSIMD::mul_all<width>
				(
					euler_simd_xyz,
					EmuSIMD::set1<_register_type>(EmuCore::Pi::PI_DIV_180<typename _out_fast_quat::value_type>)
				);
			}

			// Store euler / 2 at first as it's needed for both trig ops
			// --- May be better to multiply by 0.5, but set to /2 to avoid lossy halving and for weird cases such as integral input
			// --- May be reasonable to give a `PreferMultiplies_` option as per normal Quaternions, should be put into consideration first
			//_register_type sin_xyz = EmuSIMD::mul_all<width>(euler_simd_xyz, EmuSIMD::set1<_register_type, width>(0.5));
			_register_type sin_xyz = EmuSIMD::div<width, is_signed>(euler_simd_xyz, EmuSIMD::set1<_register_type, width>(2));
			_register_type cos_xyz = EmuSIMD::cos<width, is_signed>(sin_xyz);
			sin_xyz = EmuSIMD::sin<width, is_signed>(sin_xyz);

			// TODO: NEEDS GENERALISING STILL: ONLY SUPPORTS 4-ELEMENT REGISTERS
			// --- Currently considered low priority due to the very low likelihood of choosing a Vector with > 4 elements
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

				if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<_register_type>)
				{
					temp_0 = EmuSIMD::sqrt<width, is_signed>(temp_0);
					xyzw = EmuSIMD::div<width, is_signed>(xyzw, temp_0);
				}
				else
				{
					temp_0 = EmuSIMD::rsqrt<width, is_signed>(temp_0);
					xyzw = EmuSIMD::mul_all<width>(xyzw, temp_0);
				}
			}

			return _out_fast_quat(std::move(xyzw));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<EulerXYZ_>(),
				"Unable to make an EmuMath FastQuaternion from euler angles as the input type is not supported. Supported argument types: EmuMath Vectors, EmuMath FastVectors, arrays of scalars, arrays of EmuSIMD-supported SIMD registers, or a single EmuSIMD-supported SIMD register."
			);
		}
	}
}

#endif
