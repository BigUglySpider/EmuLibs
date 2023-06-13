#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_BASIC_OPS_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_BASIC_OPS_H_INC_ 1

#include "_fast_matrix_tmp.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
#pragma region BASIC_OP_RETURN_OUT
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

	template<class ExpectedRegisterType_, class Arg_>
	[[nodiscard]] constexpr inline decltype(auto) _forward_or_make_register(Arg_&& arg_)
	{
		if constexpr (EmuConcepts::Arithmetic<Arg_>)
		{
			return EmuSIMD::set1<ExpectedRegisterType_>(std::forward<Arg_>(arg_));
		}
		else
		{
			return std::forward<Arg_>(arg_);
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
		if constexpr ((... || (EmuConcepts::Arithmetic<Args_>)))
		{
			// If we have any args that require an intermediate register to be made, make the registers before initiating the static loop
			// --- We recursively call back on this function with the registers; this will result in the `else` branch being taken on said call
			return _basic_func_for_matrix<UseRegisterOutOfRangeSpecialisations_, Func_, OutFastMatrix_>
			(
				std::index_sequence<MajorIndices_...>(),
				std::index_sequence<RegisterIndices_...>(),
				_forward_or_make_register<typename _out_fast_mat_uq::register_type, Args_>(std::forward<Args_>(args_))...
			);
		}
		else
		{
EMU_CORE_MSVC_PUSH_WARNING_STACK
EMU_CORE_MSVC_DISABLE_WARNING(EMU_CORE_WARNING_BAD_MOVE)
			return OutFastMatrix_
			(
				_basic_func_for_major_chunk<UseRegisterOutOfRangeSpecialisations_, Func_, typename _out_fast_mat_uq::major_chunk_type, MajorIndices_, RegisterIndices_...>
				(
					std::forward<Args_>(args_)...
				)...
			);
EMU_CORE_MSVC_POP_WARNING_STACK
		}
	}
#pragma endregion

#pragma region BASIC_OP_ASSIGN_OUT
	template<bool UseRegisterOutOfRangeSpecialisations_, class Func_, std::size_t MajorIndex_, std::size_t RegisterIndex_, class OutFastMatrix_, class...Args_>
	constexpr inline void _basic_assign_func_for_register(OutFastMatrix_& out_fast_matrix_, Args_&&...args_)
	{
		if constexpr(!std::is_const_v<OutFastMatrix_>)
		{
			out_fast_matrix_.template GetRegister<MajorIndex_, RegisterIndex_>() = Func_()
			(
				_get_matrix_arg_register<MajorIndex_, RegisterIndex_, UseRegisterOutOfRangeSpecialisations_>
				(
					std::forward<Args_>(args_)
				)...
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutFastMatrix_>(),
				"Unable to perform a basic operation on a FastMatrix with assigned results as the FastMatrix to assign results to is const-qualified."
			);
		}
	}

	template<bool UseRegisterOutOfRangeSpecialisations_, class Func_, std::size_t MajorIndex_, std::size_t...RegisterIndices_, class OutFastMatrix_, class...Args_>
	constexpr inline void _basic_func_assign_for_major_chunk(OutFastMatrix_& out_fast_matrix_, Args_&&...args_)
	{
		if constexpr (sizeof...(RegisterIndices_) > 1)
		{
			(
				_basic_assign_func_for_register<UseRegisterOutOfRangeSpecialisations_, Func_, MajorIndex_, RegisterIndices_>
				(
					out_fast_matrix_,
					std::forward<Args_>(args_)...
				), ...
			);
		}
		else
		{
			_basic_assign_func_for_register<UseRegisterOutOfRangeSpecialisations_, Func_, MajorIndex_, 0>
			(
				out_fast_matrix_,
				std::forward<Args_>(args_)...
			);
		}
	}

	template
	<
		bool UseRegisterOutOfRangeSpecialisations_, class Func_, EmuConcepts::EmuFastMatrix OutFastMatrix_,
		class...Args_, std::size_t...MajorIndices_, std::size_t...RegisterIndices_
	>
	constexpr inline void _basic_func_assign_for_matrix
	(
		OutFastMatrix_& out_fast_matrix_,
		std::index_sequence<MajorIndices_...> major_indices_,
		std::index_sequence<RegisterIndices_...> register_indices_,
		Args_&&...args_
	)
	{
		using _out_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type;
		if constexpr ((... || (EmuConcepts::Arithmetic<Args_>)))
		{
			// If we have any args that require an intermediate register to be made, make the registers before initiating the static loop
			// --- We recursively call back on this function with the registers; this will result in the `else` branch being taken on said call
			_basic_func_assign_for_matrix<UseRegisterOutOfRangeSpecialisations_, Func_>
			(
				out_fast_matrix_,
				std::index_sequence<MajorIndices_...>(),
				std::index_sequence<RegisterIndices_...>(),
				_forward_or_make_register<typename _out_fast_mat_uq::register_type, Args_>(std::forward<Args_>(args_))...
			);
		}
		else
		{
EMU_CORE_MSVC_PUSH_WARNING_STACK
EMU_CORE_MSVC_DISABLE_WARNING(EMU_CORE_WARNING_BAD_MOVE)
			(
				_basic_func_assign_for_major_chunk<UseRegisterOutOfRangeSpecialisations_, Func_, MajorIndices_, RegisterIndices_...>
				(
					out_fast_matrix_,
					std::forward<Args_>(args_)...
				), ...
			);
EMU_CORE_MSVC_POP_WARNING_STACK
		}
	}
#pragma endregion
}

#endif
