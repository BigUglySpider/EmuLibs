#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_BASIC_OPS_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_BASIC_OPS_H_INC_ 1

#include "_fast_matrix_tmp.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
	template<bool UseRegisterOutOfRangeSpecialisations_, class Func_, std::size_t MajorIndex_, std::size_t RegisterIndex_, class...Args_>
	[[nodiscard]] constexpr inline decltype(auto) _basic_func_for_register(Args_&&...args_)
	{
		return Func_()
		(
			_get_matrix_arg_register<MajorIndex_, RegisterIndex_, UseRegisterOutOfRangeSpecialisations_>
			(
				std::forward<Args_>(args_)
			)...
		);
	}

	template<bool UseRegisterOutOfRangeSpecialisations_, class Func_, class ChunkType_, std::size_t MajorIndex_, std::size_t...RegisterIndices_, class...Args_>
	[[nodiscard]] constexpr inline ChunkType_ _basic_func_for_major_chunk(Args_&&...args_)
	{
		if constexpr (sizeof...(RegisterIndices_) > 1)
		{
			return ChunkType_
			({
				_basic_func_for_register<UseRegisterOutOfRangeSpecialisations_, Func_, MajorIndex_, RegisterIndices_>
				(
					std::forward<Args_>(args_)...
				)...
			});
		}
		else
		{
			return _basic_func_for_register<UseRegisterOutOfRangeSpecialisations_, Func_, MajorIndex_, 0>
			(
				std::forward<Args_>(args_)...
			);
		}
	}

	template
	<
		bool UseRegisterOutOfRangeSpecialisations_, class Func_, EmuConcepts::EmuFastMatrix OutFastMatrix_,
		class...Args_, std::size_t...MajorIndices_, std::size_t...RegisterIndices_
	>
	[[nodiscard]] constexpr inline OutFastMatrix_ _basic_func_for_matrix
	(
		std::index_sequence<MajorIndices_...> major_indices_,
		std::index_sequence<RegisterIndices_...> register_indices_,
		Args_&&...args_
	)
	{
		using _out_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type;
		return OutFastMatrix_
		(
			_basic_func_for_major_chunk<UseRegisterOutOfRangeSpecialisations_, Func_, typename _out_fast_mat_uq::major_chunk_type, MajorIndices_, RegisterIndices_...>
			(
				std::forward<Args_>(args_)...
			)...
		);
	}
}

#endif
