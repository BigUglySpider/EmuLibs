#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_SCALE_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_SCALE_H_INC_ 1

#include "_fast_matrix_tmp.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
	template
	<
		std::size_t MajorIndex_, std::size_t RegisterIndex_, std::size_t ElementInRegisterIndex_,
		EmuConcepts::EmuFastMatrix OutFastMatrix_, EmuConcepts::StdTuple Translations_
	>
	[[nodiscard]] constexpr inline decltype(auto) _get_element_arg_for_scale_register(Translations_& scales_)
	{
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type;
		constexpr std::size_t full_element_index = (RegisterIndex_ * _fast_mat_uq::num_elements_per_register) + ElementInRegisterIndex_;
		if constexpr (full_element_index == MajorIndex_ )
		{
			constexpr std::size_t num_scales = std::tuple_size_v<typename EmuCore::TMP::remove_ref_cv<Translations_>::type>;
			if constexpr(full_element_index < num_scales)
			{
				using _tuple_get_result = decltype(std::get<full_element_index>(scales_));
				return std::forward<_tuple_get_result>
				(
					std::get<full_element_index>(scales_)
				);
			}
			else
			{
				return typename _fast_mat_uq::value_type(1);
			}
		}
		else
		{
			return typename _fast_mat_uq::value_type(0);
		}
	}

	template
	<
		EmuConcepts::EmuFastMatrix OutFastMatrix_, std::size_t MajorIndex_, std::size_t RegisterIndex_, 
		std::size_t...RegisterElementIndices_, EmuConcepts::StdTuple Translations_
	>
	[[nodiscard]] constexpr inline auto _make_scale_register
	(
		Translations_& scales_,
		std::index_sequence<RegisterElementIndices_...> register_element_indices_
	) -> typename EmuCore::TMP::remove_ref_cv_t<OutFastMatrix_>::register_type
	{
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type;
		return EmuSIMD::setr<typename _fast_mat_uq::register_type, _fast_mat_uq::per_element_width>
		(
			_get_element_arg_for_scale_register<MajorIndex_, RegisterIndex_, RegisterElementIndices_, OutFastMatrix_>
			(
				scales_
			)...
		);
	}

	template<EmuConcepts::EmuFastMatrix OutFastMatrix_, std::size_t MajorIndex_, std::size_t...RegisterIndices_, EmuConcepts::StdTuple Translations_>
	[[nodiscard]] constexpr inline auto _make_scale_major_chunk(Translations_& scales_)
		-> typename EmuCore::TMP::remove_ref_cv_t<OutFastMatrix_>::major_chunk_type
	{
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type;
		using per_register_element_sequence = std::make_index_sequence<_fast_mat_uq::num_elements_per_register>;
		if constexpr (sizeof...(RegisterIndices_) > 1)
		{
			return typename _fast_mat_uq::major_chunk_type
			({
				_make_scale_register<OutFastMatrix_, MajorIndex_, RegisterIndices_>
				(
					scales_,
					per_register_element_sequence()
				)...
			});
		}
		else
		{
			return _make_scale_register<OutFastMatrix_, MajorIndex_, 0>(scales_, per_register_element_sequence());
		}
	}

	template<EmuConcepts::EmuFastMatrix OutFastMatrix_, std::size_t...MajorIndices_, std::size_t...RegisterIndices_, EmuConcepts::StdTuple Translations_>
	[[nodiscard]] constexpr inline auto _make_scale_matrix
	(
		Translations_& scales_,
		std::index_sequence<MajorIndices_...> major_indices_,
		std::index_sequence<RegisterIndices_...> register_indices_
	) -> typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type
	{
		return typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type
		(
			_make_scale_major_chunk<OutFastMatrix_, MajorIndices_, RegisterIndices_...>
			(
				scales_
			)...
		);
	}
}

#endif
