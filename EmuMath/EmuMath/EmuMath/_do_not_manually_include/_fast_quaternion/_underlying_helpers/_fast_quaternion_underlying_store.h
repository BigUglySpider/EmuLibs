#ifndef EMU_MATH_FAST_QUATERNION_UNDERLYING_STORE_H_INC_
#define EMU_MATH_FAST_QUATERNION_UNDERLYING_STORE_H_INC_ 1

#include "_fast_quaternion_tmp.h"

namespace EmuMath::Helpers::_fast_quaternion_underlying
{
	template<typename Out_, typename In_, std::size_t...Indices_>
	constexpr inline void _move_quaternion_data_dump_to_pointer(Out_* p_out_, In_* p_in_) noexcept
	{
		(
			(
				(*(p_out_ + Indices_)) = std::move(*(p_in_ + Indices_))
			), ...
		);
	}

	template<std::size_t OutputTotalWidth_, std::size_t RegisterIndex_, typename Out_, EmuConcepts::EmuFastQuaternion FastQuaternion_>
	constexpr inline void _store_quaternion_register_to_pointer(Out_* p_out_, FastQuaternion_&& fast_quaternion_) noexcept
	{
		if constexpr (!std::is_const_v<Out_>)
		{
			using _in_fast_quat_uq = typename EmuCore::TMP::remove_ref_cv<FastQuaternion_>::type;
			constexpr std::size_t required_width_for_full_store_this_index = (RegisterIndex_ * _in_fast_quat_uq::register_width);
			constexpr bool out_has_space_for_direct_store = OutputTotalWidth_ >= required_width_for_full_store_this_index;
			constexpr std::size_t elements_per_register = _in_fast_quat_uq::elements_per_register;
			constexpr std::size_t offset = RegisterIndex_ * elements_per_register;
			if constexpr (std::is_same_v<typename std::remove_cv<Out_>::type, typename _in_fast_quat_uq::value_type> && out_has_space_for_direct_store)
			{
				EmuSIMD::store
				(
					std::forward<FastQuaternion_>(fast_quaternion_).template GetRegister<RegisterIndex_>(),
					p_out_ + offset
				);
			}
			else
			{
				typename _in_fast_quat_uq::value_type data_dump[elements_per_register];
				EmuSIMD::store
				(
					std::forward<FastQuaternion_>(fast_quaternion_).template GetRegister<RegisterIndex_>(),
					data_dump
				);
				_move_quaternion_data_dump_to_pointer(p_out_ + offset, data_dump, std::make_index_sequence<elements_per_register>());
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Out_>(),
				"Failed to store a FastQuaternion register to a pointer as the provided output pointer is const-qualified."
			);
		}
	}

	template<std::size_t OutputTotalWidth_, typename Out_, EmuConcepts::EmuFastQuaternion FastQuaternion_, std::size_t...RegisterIndices_>
	constexpr inline void _store_quaternion_registers_to_pointer
	(
		Out_* p_out_,
		FastQuaternion_&& fast_quaternion_,
		std::index_sequence<RegisterIndices_...> register_indices_
	) noexcept
	{
EMU_CORE_MSVC_PUSH_WARNING_STACK
EMU_CORE_MSVC_DISABLE_WARNING(EMU_CORE_WARNING_BAD_MOVE)
		(
			_store_quaternion_register_to_pointer<OutputTotalWidth_, RegisterIndices_>
			(
				p_out_,
				std::forward<FastQuaternion_>(fast_quaternion_)
			), ...
		);
EMU_CORE_MSVC_POP_WARNING_STACK
	}
}

#endif
