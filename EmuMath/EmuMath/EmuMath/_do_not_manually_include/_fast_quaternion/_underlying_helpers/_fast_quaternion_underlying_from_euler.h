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
			_make_euler_register<RegisterIndices_, FastQuaternion_>
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
}

#endif
