#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_LOAD_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_LOAD_H_INC_ 1

#include "_fast_matrix_tmp.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
	template<EmuConcepts::EmuFastMatrix OutFastMatrix_, std::size_t RegisterIndex_, EmuConcepts::EmuMatrix ScalarMatrix_, std::size_t...ElementIndices_>
	[[nodiscard]] constexpr inline auto _set_register_from_scalar_matrix(ScalarMatrix_&& scalar_matrix_)
		-> typename EmuMath::TMP::fast_matrix_register_type<OutFastMatrix_>::type
	{
		using _out_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type;
		using _in_scalar_mat_uq = typename EmuCore::TMP::remove_ref_cv<ScalarMatrix_>::type;

		constexpr std::size_t major_index = RegisterIndex_ / _out_fast_mat_uq::num_registers_per_major;
		constexpr std::size_t non_major_index = (RegisterIndex_ % _out_fast_mat_uq::num_registers_per_major) * _out_fast_mat_uq::num_elements_per_register;
		constexpr std::size_t column_index = _out_fast_mat_uq::is_column_major ? major_index : non_major_index;
		constexpr std::size_t row_index = _out_fast_mat_uq::is_column_major ? non_major_index : major_index;

		if constexpr (_out_fast_mat_uq::is_column_major)
		{
			return EmuSIMD::setr<typename _out_fast_mat_uq::register_type, _out_fast_mat_uq::per_element_width>
			(
				std::forward<ScalarMatrix_>(scalar_matrix_).template AtTheoretical<column_index, row_index + ElementIndices_>()...
			);
		}
		else
		{
			return EmuSIMD::setr<typename _out_fast_mat_uq::register_type, _out_fast_mat_uq::per_element_width>
			(
				std::forward<ScalarMatrix_>(scalar_matrix_).template AtTheoretical<column_index + ElementIndices_, row_index>()...
			);
		}
	}

	template<EmuConcepts::EmuFastMatrix OutFastMatrix_, std::size_t RegisterIndex_, EmuConcepts::EmuMatrix ScalarMatrix_, std::size_t...ElementIndices_>
	[[nodiscard]] constexpr inline auto _load_register_from_scalar_matrix(ScalarMatrix_&& scalar_matrix_)
		-> typename EmuMath::TMP::fast_matrix_register_type<OutFastMatrix_>::type
	{
		using _out_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type;
		using _in_scalar_mat_uq = typename EmuCore::TMP::remove_ref_cv<ScalarMatrix_>::type;
		constexpr bool compatible_types = std::is_same_v<typename _out_fast_mat_uq::value_type, typename _in_scalar_mat_uq::stored_type>;
		if constexpr (compatible_types && _out_fast_mat_uq::is_column_major == _in_scalar_mat_uq::is_column_major)
		{
			constexpr std::size_t major_index = RegisterIndex_ / _out_fast_mat_uq::num_registers_per_major;
			constexpr std::size_t register_in_chunk_index = (RegisterIndex_ % _out_fast_mat_uq::num_registers_per_major);
			constexpr std::size_t non_major_index = register_in_chunk_index * _out_fast_mat_uq::num_elements_per_register;
			constexpr std::size_t column_index = _out_fast_mat_uq::is_column_major ? major_index : non_major_index;
			constexpr std::size_t row_index = _out_fast_mat_uq::is_column_major ? non_major_index : major_index;
			constexpr std::size_t flattened_index = (major_index * _in_scalar_mat_uq::num_non_major_elements) + non_major_index;
			constexpr std::size_t required_size_to_load = flattened_index + sizeof...(ElementIndices_) + 1;
			constexpr bool on_final_register_in_chunk = register_in_chunk_index == (_out_fast_mat_uq::num_registers_per_major - 1);
			constexpr std::size_t required_size_in_chunk = 
			(
				non_major_index + 
				(
					on_final_register_in_chunk ?
					_out_fast_mat_uq::num_elements_in_partial_registers :
					_out_fast_mat_uq::num_elements_per_register
				)
			);
				
			if constexpr (_in_scalar_mat_uq::size >= required_size_to_load && _in_scalar_mat_uq::num_non_major_elements >= required_size_in_chunk)
			{
				return EmuSIMD::load<typename _out_fast_mat_uq::register_type>
				(
					std::forward<ScalarMatrix_>(scalar_matrix_).template data<column_index, row_index>()
				);
			}
			else
			{
				return _set_register_from_scalar_matrix<OutFastMatrix_, RegisterIndex_, ScalarMatrix_, ElementIndices_...>
				(
					std::forward<ScalarMatrix_>(scalar_matrix_)
				);
			}
		}
		else
		{
			return _set_register_from_scalar_matrix<OutFastMatrix_, RegisterIndex_, ScalarMatrix_, ElementIndices_...>
			(
				std::forward<ScalarMatrix_>(scalar_matrix_)
			);
		}
	}

	template
	<
		std::size_t MajorIndex_, EmuConcepts::EmuFastMatrix OutFastMatrix_, EmuConcepts::EmuMatrix ScalarMatrix_,
		std::size_t...RegisterElementIndices_, std::size_t...MajorRegisterIndices_
	>
	[[nodiscard]] constexpr inline auto _load_major_chunk_from_scalar_matrix
	(
		ScalarMatrix_&& scalar_matrix_,
		std::index_sequence<RegisterElementIndices_...> register_element_indices_,
		std::index_sequence<MajorRegisterIndices_...> major_register_indices_
	) -> typename EmuCore::TMP::remove_ref_cv_t<OutFastMatrix_>::major_chunk_type
	{
		using _out_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type;
		constexpr std::size_t major_offset = MajorIndex_ * _out_fast_mat_uq::num_registers_per_major;
		return typename EmuCore::TMP::remove_ref_cv_t<OutFastMatrix_>::major_chunk_type
		({
			_load_register_from_scalar_matrix<OutFastMatrix_, major_offset + MajorRegisterIndices_, ScalarMatrix_, RegisterElementIndices_...>
			(
				std::forward<ScalarMatrix_>(scalar_matrix_)
			)...
		});
	}

	template
	<
		EmuConcepts::EmuFastMatrix OutFastMatrix_, EmuConcepts::EmuMatrix ScalarMatrix_,
		std::size_t...RegisterElementIndices_, std::size_t...MajorIndices_, std::size_t...MajorRegisterIndices_
	>
	[[nodiscard]] constexpr inline auto _load_major_chunks_from_scalar_matrix
	(
		ScalarMatrix_&& scalar_matrix_,
		std::index_sequence<RegisterElementIndices_...> register_element_indices_,
		std::index_sequence<MajorIndices_...> major_indices_,
		std::index_sequence<MajorRegisterIndices_...> major_register_indices_
	) -> typename EmuCore::TMP::remove_ref_cv_t<OutFastMatrix_>::data_type
	{
		using _out_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type;
		if constexpr (_out_fast_mat_uq::num_registers_per_major > 1)
		{
			return typename _out_fast_mat_uq::data_type
			({
				_load_major_chunk_from_scalar_matrix<MajorIndices_, OutFastMatrix_>
				(
					std::forward<ScalarMatrix_>(scalar_matrix_),
					std::index_sequence<RegisterElementIndices_...>(),
					std::index_sequence<MajorRegisterIndices_...>()
				)...
			});
		}
		else
		{
			// No need for array layer, so make the data_type directly
			return typename _out_fast_mat_uq::data_type
			({
				_load_register_from_scalar_matrix<OutFastMatrix_, MajorIndices_, ScalarMatrix_, RegisterElementIndices_...>
				(
					std::forward<ScalarMatrix_>(scalar_matrix_)
				)...
			});
		}
	}

	template<EmuConcepts::EmuFastMatrix OutFastMatrix_, EmuConcepts::EmuMatrix ScalarMatrix_, std::size_t...RegisterIndices_, std::size_t...RegisterElementIndices_>
	[[nodiscard]] constexpr inline auto _load_from_scalar_matrix
	(
		ScalarMatrix_&& scalar_matrix_,
		std::index_sequence<RegisterIndices_...> register_indices_,
		std::index_sequence<RegisterElementIndices_...> register_element_indices_
	) -> OutFastMatrix_
	{
		using _out_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type;
		return OutFastMatrix_
		(
			_load_register_from_scalar_matrix<OutFastMatrix_, RegisterIndices_, ScalarMatrix_, RegisterElementIndices_...>
			(
				std::forward<ScalarMatrix_>(scalar_matrix_)
			)...
		);
	}
}

#endif
