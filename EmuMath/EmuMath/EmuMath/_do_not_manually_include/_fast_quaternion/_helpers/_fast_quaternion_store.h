#ifndef EMU_MATH_FAST_QUATERNION_STORE_H_INC_
#define EMU_MATH_FAST_QUATERNION_STORE_H_INC_ 1

#include "_common_fast_quaternion_includes.h"

namespace EmuMath::Helpers
{
	template<typename OutT_, EmuConcepts::EmuFastQuaternion FastQuaternion_>
	[[nodiscard]] constexpr inline auto fast_quaternion_store(FastQuaternion_&& fast_quaternion_) noexcept
		-> std::enable_if_t
		<
			std::is_constructible_v
			<
				EmuMath::Quaternion<OutT_>,
				typename EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::value_type&&,
				typename EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::value_type&&,
				typename EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::value_type&&,
				typename EmuCore::TMP::remove_ref_cv_t<FastQuaternion_>::value_type&&
			>,
			EmuMath::Quaternion<OutT_>
		>
	{
		using _in_fast_quat_uq = typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type;
		typename _in_fast_quat_uq::value_type data_dump[_in_fast_quat_uq::full_width_size];
		if constexpr (_in_fast_quat_uq::num_registers > 1)
		{
			_fast_quaternion_underlying::_store_quaternion_registers_to_pointer
			(
				data_dump,
				std::forward<FastQuaternion_>(fast_quaternion_),
				std::make_index_sequence<_in_fast_quat_uq::num_registers>()
			);
		}
		else
		{
			EmuSIMD::store(std::forward<FastQuaternion_>(fast_quaternion_).data, data_dump);
		}

		return EmuMath::Quaternion<OutT_>
		(
			std::move(data_dump[0]),
			std::move(data_dump[1]),
			std::move(data_dump[2]),
			std::move(data_dump[3])
		);
	}

	template<typename Out_, EmuConcepts::EmuFastQuaternion FastQuaternion_>
	requires (!std::is_const_v<Out_>)
	constexpr inline void fast_quaternion_store(FastQuaternion_&& fast_quaternion_, Out_* p_out_)
	{
		using _in_fast_quat_uq = typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type;
		if constexpr (_in_fast_quat_uq::num_registers > 1)
		{
			_fast_quaternion_underlying::_store_quaternion_registers_to_pointer
			(
				p_out_,
				std::forward<FastQuaternion_>(fast_quaternion_),
				std::make_index_sequence<_in_fast_quat_uq::num_registers>()
			);
		}
		else
		{
			_fast_quaternion_underlying::_store_quaternion_register_to_pointer<0>
			(
				p_out_,
				std::forward<FastQuaternion_>(fast_quaternion_)
			);
		}
	}

	template<typename OutT_, EmuConcepts::EmuFastQuaternion FastQuaternion_>
	constexpr inline void fast_quaternion_store(FastQuaternion_&& fast_quaternion_, EmuMath::Quaternion<OutT_>& out_quaternion_)
	{
		using _in_fast_quat_uq = typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type;
		if constexpr (_in_fast_quat_uq::num_registers > 1)
		{
			_fast_quaternion_underlying::_store_quaternion_registers_to_pointer
			(
				out_quaternion_.DataPointer(),
				std::forward<FastQuaternion_>(fast_quaternion_),
				std::make_index_sequence<_in_fast_quat_uq::num_registers>()
			);
		}
		else
		{
			_fast_quaternion_underlying::_store_quaternion_register_to_pointer<0>
			(
				out_quaternion_.DataPointer(),
				std::forward<FastQuaternion_>(fast_quaternion_)
			);
		}
	}
}

#endif
