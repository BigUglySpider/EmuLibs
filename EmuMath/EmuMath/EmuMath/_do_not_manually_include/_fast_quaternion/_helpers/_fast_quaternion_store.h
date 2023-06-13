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
		constexpr std::size_t full_width_size = _in_fast_quat_uq::full_width_size;
		typename _in_fast_quat_uq::value_type data_dump[full_width_size];
		if constexpr (_in_fast_quat_uq::num_registers > 1)
		{
			constexpr std::size_t full_width_to_store = _in_fast_quat_uq::register_width * _in_fast_quat_uq::num_registers;
			_fast_quaternion_underlying::_store_quaternion_registers_to_pointer<full_width_to_store>
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

	template<typename Out_, std::size_t OutDataElementCount_ = (std::numeric_limits<std::size_t>::max()), EmuConcepts::EmuFastQuaternion FastQuaternion_>
	requires (!std::is_const_v<Out_>)
	constexpr inline void fast_quaternion_store(FastQuaternion_&& fast_quaternion_, Out_* p_out_)
	{
		using _in_fast_quat_uq = typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type;
		constexpr std::size_t full_width_size = _in_fast_quat_uq::full_width_size;
		constexpr std::size_t output_size = OutDataElementCount_ >= full_width_size ? full_width_size : OutDataElementCount_;
		constexpr std::size_t output_total_width = sizeof(Out_) * output_size * 8;
		if constexpr (_in_fast_quat_uq::num_registers > 1)
		{
			_fast_quaternion_underlying::_store_quaternion_registers_to_pointer<output_total_width>
			(
				p_out_,
				std::forward<FastQuaternion_>(fast_quaternion_),
				std::make_index_sequence<_in_fast_quat_uq::num_registers>()
			);
		}
		else
		{
			_fast_quaternion_underlying::_store_quaternion_register_to_pointer<output_total_width, 0>
			(
				p_out_,
				std::forward<FastQuaternion_>(fast_quaternion_)
			);
		}
	}

	template<typename OutT_, EmuConcepts::EmuFastQuaternion FastQuaternion_>
	constexpr inline void fast_quaternion_store(FastQuaternion_&& fast_quaternion_, EmuMath::Quaternion<OutT_>& out_quaternion_)
	{
		// TODO: FIX, ALLOWS BAD STORES TO OCCUR
		// --- E.g. storing 256-bit input straight into 128-bit
		using _in_fast_quat_uq = typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type;
		constexpr std::size_t out_num_elements = 4;
		constexpr std::size_t output_total_width = sizeof(OutT_) * out_num_elements * 8;
		if constexpr (_in_fast_quat_uq::num_registers > 1)
		{
			_fast_quaternion_underlying::_store_quaternion_registers_to_pointer<output_total_width>
			(
				out_quaternion_.DataPointer(),
				std::forward<FastQuaternion_>(fast_quaternion_),
				std::make_index_sequence<_in_fast_quat_uq::num_registers>()
			);
		}
		else
		{
			_fast_quaternion_underlying::_store_quaternion_register_to_pointer<output_total_width, 0>
			(
				out_quaternion_.DataPointer(),
				std::forward<FastQuaternion_>(fast_quaternion_)
			);
		}
	}
}

#endif
