#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_ROUNDS_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_ROUNDS_H_INC_ 1

#include "_fast_matrix_tmp.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
	template<bool Assigning_, std::size_t MajorIndex_, std::size_t RegisterIndex_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_matrix_floor_register(FastMatrix_&& matrix_)
	{
		if constexpr (Assigning_)
		{
			if constexpr (!std::is_const_v<FastMatrix_> && std::is_lvalue_reference_v<FastMatrix_>)
			{
				auto& current_register = std::forward<FastMatrix_>(matrix_).template GetRegister<MajorIndex_, RegisterIndex_>();
				current_register = EmuSIMD::floor(current_register);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<FastMatrix_>(),
					"Failed to floor an EmuMath FastMatrix and assign the results as the passed FastMatrix is not a non-const lvalue reference."
				);
			}
		}
		else
		{
			return EmuSIMD::floor(std::forward<FastMatrix_>(matrix_).template GetRegister<MajorIndex_, RegisterIndex_>());
		}
	}
	
	template<bool Assigning_, std::size_t MajorIndex_, std::size_t RegisterIndex_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_matrix_ceil_register(FastMatrix_&& matrix_)
	{
		if constexpr (Assigning_)
		{
			if constexpr (!std::is_const_v<FastMatrix_> && std::is_lvalue_reference_v<FastMatrix_>)
			{
				auto& current_register = std::forward<FastMatrix_>(matrix_).template GetRegister<MajorIndex_, RegisterIndex_>();
				current_register = EmuSIMD::ceil(current_register);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<FastMatrix_>(),
					"Failed to ceil an EmuMath FastMatrix and assign the results as the passed FastMatrix is not a non-const lvalue reference."
				);
			}
		}
		else
		{
			return EmuSIMD::ceil(std::forward<FastMatrix_>(matrix_).template GetRegister<MajorIndex_, RegisterIndex_>());
		}
	}
	
	template<bool Assigning_, std::size_t MajorIndex_, std::size_t RegisterIndex_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_matrix_trunc_register(FastMatrix_&& matrix_)
	{
		if constexpr (Assigning_)
		{
			if constexpr (!std::is_const_v<FastMatrix_> && std::is_lvalue_reference_v<FastMatrix_>)
			{
				auto& current_register = std::forward<FastMatrix_>(matrix_).template GetRegister<MajorIndex_, RegisterIndex_>();
				current_register = EmuSIMD::trunc(current_register);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<FastMatrix_>(),
					"Failed to truncate an EmuMath FastMatrix and assign the results as the passed FastMatrix is not a non-const lvalue reference."
				);
			}
		}
		else
		{
			return EmuSIMD::trunc(std::forward<FastMatrix_>(matrix_).template GetRegister<MajorIndex_, RegisterIndex_>());
		}
	}

	template<bool Assigning_, EmuConcepts::EmuFastMatrix FastMatrix_, std::size_t...ContiguousMajorIndices_, std::size_t...ContiguousRegisterIndices_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_matrix_floor
	(
		FastMatrix_&& matrix_,
		std::index_sequence<ContiguousMajorIndices_...> contiguous_major_indices_,
		std::index_sequence<ContiguousRegisterIndices_...> contiguous_register_indices_
	)
	{
		if constexpr (Assigning_)
		{
			(
				_fast_matrix_floor_register<true, ContiguousMajorIndices_, ContiguousRegisterIndices_>
				(
					std::forward<FastMatrix_>(matrix_)
				), ...
			);
		}
		else
		{
			return typename std::remove_cvref<FastMatrix_>::type
			(
				_fast_matrix_floor_register<false, ContiguousMajorIndices_, ContiguousRegisterIndices_>
				(
					std::forward<FastMatrix_>(matrix_)
				)...
			);
		}
	}

	template<bool Assigning_, EmuConcepts::EmuFastMatrix FastMatrix_, std::size_t...ContiguousMajorIndices_, std::size_t...ContiguousRegisterIndices_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_matrix_ceil
	(
		FastMatrix_&& matrix_,
		std::index_sequence<ContiguousMajorIndices_...> contiguous_major_indices_,
		std::index_sequence<ContiguousRegisterIndices_...> contiguous_register_indices_
	)
	{
		if constexpr (Assigning_)
		{
			(
				_fast_matrix_ceil_register<true, ContiguousMajorIndices_, ContiguousRegisterIndices_>
				(
					std::forward<FastMatrix_>(matrix_)
				), ...
			);
		}
		else
		{
			return typename std::remove_cvref<FastMatrix_>::type
			(
				_fast_matrix_ceil_register<false, ContiguousMajorIndices_, ContiguousRegisterIndices_>
				(
					std::forward<FastMatrix_>(matrix_)
				)...
			);
		}
	}
	
	template<bool Assigning_, EmuConcepts::EmuFastMatrix FastMatrix_, std::size_t...ContiguousMajorIndices_, std::size_t...ContiguousRegisterIndices_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_matrix_trunc
	(
		FastMatrix_&& matrix_,
		std::index_sequence<ContiguousMajorIndices_...> contiguous_major_indices_,
		std::index_sequence<ContiguousRegisterIndices_...> contiguous_register_indices_
	)
	{
		if constexpr (Assigning_)
		{
			(
				_fast_matrix_trunc_register<true, ContiguousMajorIndices_, ContiguousRegisterIndices_>
				(
					std::forward<FastMatrix_>(matrix_)
				), ...
			);
		}
		else
		{
			return typename std::remove_cvref<FastMatrix_>::type
			(
				_fast_matrix_trunc_register<false, ContiguousMajorIndices_, ContiguousRegisterIndices_>
				(
					std::forward<FastMatrix_>(matrix_)
				)...
			);
		}
	}
}

#endif
