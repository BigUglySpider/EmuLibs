#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_MUTATION_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_MUTATION_H_INC_ 1

#include "_fast_matrix_tmp.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
	template<bool Assigning_, std::size_t MajorIndex_, std::size_t RegisterIndex_, class Func_, EmuConcepts::EmuFastMatrix FastMatrix_>
	constexpr inline decltype(auto) _fast_matrix_mutate_register(FastMatrix_&& matrix_, Func_&& func_)
	{
		using _fast_mat_uq = typename std::remove_cvref<FastMatrix_>::type;
		using _register_type = typename _fast_mat_uq::register_type;
		using _get_register_result = decltype(std::forward<FastMatrix_>(matrix_).template GetRegister<MajorIndex_, RegisterIndex_>());
		using invocation_info = EmuCore::TMP::safe_invoke_result<decltype(std::forward<Func_>(func_)), _get_register_result>;

		if constexpr(invocation_info::value)
		{
			using _invoke_result = typename invocation_info::type;

			_get_register_result current_register = std::forward<FastMatrix_>(matrix_).template GetRegister<MajorIndex_, RegisterIndex_>();
			if constexpr (Assigning_)
			{
				if constexpr (!std::is_const_v<FastMatrix_> && std::is_lvalue_reference_v<FastMatrix_>)
				{
					if constexpr (std::is_assignable_v<_get_register_result, _invoke_result>)
					{
						current_register = std::forward<Func_>(func_)(current_register);
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<Func_>(),
							"Failed to mutate an EmuMath FastMatrix and assign the results as at least one register could not be assigned to by the result of invoking the provided function with the same register."
						);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<FastMatrix_>(),
						"Failed to mutate an EmuMath FastMatrix and assign the results as the passed FastMatrix is not a non-const lvalue reference."
					);
				}
			}
			else
			{
				return std::forward<Func_>(func_)(current_register);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Func_>(),
				"Failed to perform a mutation invocation on an EmuMath FastMatrix as the input function cannot be invoked with a register acquired from the FastMatrix via `GetRegister`."
			);
		}
	}

	template<bool Assigning_, std::size_t...MajorIndices_, std::size_t...RegisterIndices_, class Func_, EmuConcepts::EmuFastMatrix FastMatrix_>
	constexpr inline decltype(auto) _fast_matrix_mutate
	(
		FastMatrix_&& matrix_,
		Func_&& func_,
		std::index_sequence<MajorIndices_...> major_indices_,
		std::index_sequence<RegisterIndices_...> register_indices_
	)
	{
		if constexpr (Assigning_)
		{
			(
				_fast_matrix_mutate_register<Assigning_, MajorIndices_, RegisterIndices_>
				(
					std::forward<FastMatrix_>(matrix_),
					std::forward<Func_>(func_)
				), ...
			);
		}
		else
		{
			return typename std::remove_cvref<FastMatrix_>::type
			(
				_fast_matrix_mutate_register<Assigning_, MajorIndices_, RegisterIndices_>
				(
					std::forward<FastMatrix_>(matrix_),
					std::forward<Func_>(func_)
				)...
			);
		}
	}

	template<bool Assigning_, class Func_, EmuConcepts::EmuFastMatrix FastMatrix_>
	constexpr inline decltype(auto) _fast_matrix_mutate(FastMatrix_&& fast_matrix_, Func_&& func_)
	{
		using index_sequences = EmuMath::TMP::fast_matrix_full_register_sequences<FastMatrix_>;
		using major_indices = typename index_sequences::major_index_sequence;
		using register_indices = typename index_sequences::register_index_sequence;
		return _fast_matrix_mutate<Assigning_>
		(
			std::forward<FastMatrix_>(fast_matrix_),
			std::forward<Func_>(func_),
			major_indices(),
			register_indices()
		);
	}

	template<bool Assigning_, class Func_, EmuConcepts::EmuFastMatrix FastMatrix_>
	constexpr inline decltype(auto) _fast_matrix_mutate(FastMatrix_&& fast_matrix_)
	{
		if constexpr(std::is_default_constructible_v<Func_>)
		{
			using index_sequences = EmuMath::TMP::fast_matrix_full_register_sequences<FastMatrix_>;
			using major_indices = typename index_sequences::major_index_sequence;
			using register_indices = typename index_sequences::register_index_sequence;
			Func_ func_ = Func_();
			return _fast_matrix_mutate<Assigning_>
			(
				std::forward<FastMatrix_>(fast_matrix_),
				func_,
				major_indices(),
				register_indices()
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Func_>(),
				"Failed to perform mutation of an EmuMath FastMatrix as the provided function type cannot be default-constructed, but no function object was passed to invoke. This behaviour is only supported for default-constructible function objects."
			);
		}
	}
}

#endif
