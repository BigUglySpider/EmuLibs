#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_STORE_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_STORE_H_INC_ 1

#include "_fast_matrix_tmp.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
#pragma region GENERAL_HELPERS
	template<EmuConcepts::EmuMatrix OutMatrix_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	constexpr inline void _zero_scalar_range
	(
		OutMatrix_& out_matrix_,
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_
	)
	{
		using _out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		if constexpr (!std::is_const_v<OutMatrix_>)
		{
			(
				EmuCore::TMP::assign_direct_or_cast<typename _out_mat_uq::value_type>
				(
					out_matrix_.template at<ColumnIndices_, RowIndices_>(),
					0
				), ...
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutMatrix_>(),
				"Unable to zero indices in an EmuMath Matrix as the passed Matrix reference is const-qualified."
			);
		}		
	}
#pragma endregion

#pragma region ASSIGN_TO_SCALAR_MATRIX
	template<bool InColumnMajor_, std::size_t MajorIndex_, EmuConcepts::EmuMatrix OutMatrix_, typename Data_, std::size_t...NonMajorIndices_>
	constexpr inline void _move_data_to_scalar_matrix(OutMatrix_& out_matrix_, Data_* p_data_, std::index_sequence<NonMajorIndices_...> non_major_indices_)
	{
		using _out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		if constexpr (InColumnMajor_)
		{
			(
				EmuCore::TMP::assign_direct_or_cast<typename _out_mat_uq::value_type_uq>
				(
					out_matrix_.template at<MajorIndex_, NonMajorIndices_>(),
					std::move(*(p_data_ + NonMajorIndices_))
				), ...
			);
		}
		else
		{
			(
				EmuCore::TMP::assign_direct_or_cast<typename _out_mat_uq::value_type_uq>
				(
					out_matrix_.template at<NonMajorIndices_, MajorIndex_>(),
					std::move(*(p_data_ + NonMajorIndices_))
				), ...
			);
		}
	}

	template<std::size_t MajorIndex_, std::size_t RegisterIndex_, EmuConcepts::EmuMatrix OutMatrix_, EmuConcepts::EmuFastMatrix FastMatrix_>
	constexpr inline void _move_register_to_scalar_matrix(OutMatrix_& out_matrix_, FastMatrix_&& fast_matrix_)
	{
		if constexpr (!std::is_const_v<OutMatrix_>)
		{
			using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
			constexpr std::size_t per_major_offset = _fast_mat_uq::num_non_major_elements;
			constexpr std::size_t major_offset = MajorIndex_ * per_major_offset;
			constexpr std::size_t non_major_offset = RegisterIndex_ * _fast_mat_uq::num_elements_per_register;
			constexpr std::size_t offset = major_offset + non_major_offset;
			constexpr std::size_t column_index = _fast_mat_uq::is_column_major ? MajorIndex_ : non_major_offset;
			constexpr std::size_t row_index = _fast_mat_uq::is_column_major ? non_major_offset : MajorIndex_;

			// Do nothing if not contained in output Matrix
			using _out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			if constexpr (column_index < _out_mat_uq::num_columns && row_index < _out_mat_uq::num_rows)
			{
				constexpr std::size_t out_matching_major_size = _fast_mat_uq::is_column_major ? _out_mat_uq::num_rows : _out_mat_uq::num_columns;
				constexpr std::size_t out_remaining_space_in_matching_major = out_matching_major_size - non_major_offset;
				constexpr std::size_t register_size = _fast_mat_uq::num_elements_per_register;
				constexpr std::size_t index_sequence_size = EmuCore::TMP::smallest_constant_v<std::size_t, out_remaining_space_in_matching_major, register_size>;
				using out_index_sequence = EmuCore::TMP::make_offset_index_sequence<non_major_offset, index_sequence_size>;

				typename _out_mat_uq::value_type batch_dump[register_size];
				EmuSIMD::store(std::forward<FastMatrix_>(fast_matrix_).template GetRegister<MajorIndex_, RegisterIndex_>(), batch_dump);
				_move_data_to_scalar_matrix<_fast_mat_uq::is_column_major, MajorIndex_>(out_matrix_, batch_dump, out_index_sequence());
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutMatrix_>(),
				"Unable to store a register from an EmuMath `FastMatrix` as the passed output scalar Matrix is const-qualified."
			);
		}
	}

	template<std::size_t MajorIndex_, std::size_t RegisterIndex_, EmuConcepts::EmuMatrix OutMatrix_, EmuConcepts::EmuFastMatrix FastMatrix_>
	constexpr inline void _store_register_to_scalar_matrix(OutMatrix_& out_matrix_, FastMatrix_&& fast_matrix_)
	{
		if constexpr (!std::is_const_v<OutMatrix_>)
		{
			using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
			constexpr std::size_t register_size = _fast_mat_uq::num_elements_per_register;
			constexpr std::size_t per_major_offset = _fast_mat_uq::num_non_major_elements;
			constexpr std::size_t major_offset = MajorIndex_ * per_major_offset;
			constexpr std::size_t non_major_offset = RegisterIndex_ * register_size;
			constexpr std::size_t offset = major_offset + non_major_offset;
			constexpr std::size_t column_index = _fast_mat_uq::is_column_major ? MajorIndex_ : non_major_offset;
			constexpr std::size_t row_index = _fast_mat_uq::is_column_major ? non_major_offset : MajorIndex_;

			// Do nothing if not contained in output Matrix
			using _out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			if constexpr (column_index < _out_mat_uq::num_columns && row_index < _out_mat_uq::num_rows)
			{
				if constexpr (_out_mat_uq::is_column_major == _fast_mat_uq::is_column_major)
				{
					constexpr std::size_t out_flattened_major_offset = _out_mat_uq::num_non_major_elements * MajorIndex_;
					constexpr std::size_t out_flattened_offset = out_flattened_major_offset + non_major_offset;
					constexpr std::size_t out_required_size_to_direct_store = out_flattened_offset + register_size;
					constexpr bool same_type_stored = std::is_same_v<typename _out_mat_uq::stored_type, typename _fast_mat_uq::value_type>;
					if constexpr (_out_mat_uq::size >= out_required_size_to_direct_store && same_type_stored)
					{
						EmuSIMD::store
						(
							std::forward<FastMatrix_>(fast_matrix_).template GetRegister<MajorIndex_, RegisterIndex_>(),
							out_matrix_.template data<column_index, row_index>()
						);
					}
					else
					{
						// No space to safely load, or different types
						_move_register_to_scalar_matrix<MajorIndex_, RegisterIndex_>(out_matrix_, std::forward<FastMatrix_>(fast_matrix_));
					}
				}
				else
				{
					// Loads not possible as conflicting major orders
					_move_register_to_scalar_matrix<MajorIndex_, RegisterIndex_>(out_matrix_, std::forward<FastMatrix_>(fast_matrix_));
				}
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutMatrix_>(),
				"Unable to store a register from an EmuMath `FastMatrix` as the passed output scalar Matrix is const-qualified."
			);
		}
	}

	template<std::size_t MajorIndex_, EmuConcepts::EmuMatrix OutMatrix_, EmuConcepts::EmuFastMatrix FastMatrix_, std::size_t...RegisterIndices_>
	constexpr inline void _store_major_to_scalar_matrix(OutMatrix_& out_matrix_, FastMatrix_&& fast_matrix_)
	{
		(
			_store_register_to_scalar_matrix<MajorIndex_, RegisterIndices_>
			(
				out_matrix_,
				std::forward<FastMatrix_>(fast_matrix_)
			), ...
		);
	}

	template<EmuConcepts::EmuMatrix OutMatrix_, EmuConcepts::EmuFastMatrix FastMatrix_, std::size_t...MajorIndices_, std::size_t...RegisterIndices_>
	constexpr inline void _store_to_scalar_matrix
	(
		OutMatrix_& out_matrix_,
		FastMatrix_&& fast_matrix_,
		std::index_sequence<MajorIndices_...> major_indices_,
		std::index_sequence<RegisterIndices_...> register_indices_
	)
	{
#pragma warning(push)
#pragma warning(disable: 26800)
		(
			_store_major_to_scalar_matrix<MajorIndices_, OutMatrix_, FastMatrix_, RegisterIndices_...>
			(
				out_matrix_,
				std::forward<FastMatrix_>(fast_matrix_)
			), ...
		);
#pragma warning(pop)
	}
#pragma endregion

#pragma region OUTPUT_TO_POINTER
	template<typename In_, typename Out_, std::size_t...Indices_>
	constexpr inline void _move_data_to_pointer_data(In_* p_to_move_, Out_* p_out_, std::index_sequence<Indices_...> indices_)
	{
		(
			EmuCore::TMP::assign_direct_or_cast<typename EmuCore::TMP::remove_ref_cv<Out_>::type>
			(
				*(p_out_ + Indices_),
				std::move(*(p_to_move_ + Indices_))
			), ...
		);
	}

	template<bool FullWidth_, std::size_t MajorIndex_, std::size_t RegisterIndex_, EmuConcepts::EmuFastMatrix FastMatrix_, typename Data_>
	constexpr inline void _store_register_to_pointer(FastMatrix_&& fast_matrix_, Data_* p_out_)
	{
		if constexpr (!std::is_const_v<Data_>)
		{
			using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
			constexpr std::size_t per_major_offset = FullWidth_ ? _fast_mat_uq::full_width_major_size : _fast_mat_uq::num_non_major_elements;
			constexpr std::size_t major_offset = MajorIndex_ * per_major_offset;
			constexpr std::size_t non_major_offset = RegisterIndex_ * _fast_mat_uq::num_elements_per_register;
			constexpr std::size_t offset = major_offset + non_major_offset;

			if constexpr (std::is_same_v<typename EmuCore::TMP::remove_ref_cv<Data_>::type, typename _fast_mat_uq::value_type>)
			{
				EmuSIMD::store(std::forward<FastMatrix_>(fast_matrix_).template GetRegister<MajorIndex_, RegisterIndex_>(), p_out_ + offset);
			}
			else
			{
				typename _fast_mat_uq::value_type batch_dump[_fast_mat_uq::num_elements_per_register];
				EmuSIMD::store(std::forward<FastMatrix_>(fast_matrix_).template GetRegister<MajorIndex_, RegisterIndex_>(), batch_dump);
				_move_data_to_pointer_data(batch_dump, p_out_ + offset);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Data_>(),
				"Unable to store a register from an EmuMath `FastMatrix` as the passed output pointer is const-qualified."
			);
		}
	}

	template<bool FullWidth_, std::size_t MajorIndex_, EmuConcepts::EmuFastMatrix FastMatrix_, typename OutData_, std::size_t...RegisterIndices_>
	constexpr inline void _store_major_to_data_pointer(FastMatrix_&& fast_matrix_, OutData_* p_out_data_)
	{
		(
			_store_register_to_pointer<FullWidth_, MajorIndex_, RegisterIndices_>
			(
				std::forward<FastMatrix_>(fast_matrix_),
				p_out_data_
			), ...
		);
	}

	template<bool FullWidth_, typename OutData_, EmuConcepts::EmuFastMatrix FastMatrix_, std::size_t...MajorIndices_, std::size_t...RegisterIndices_>
	constexpr inline void _store_to_data_pointer
	(
		FastMatrix_&& fast_matrix_,
		OutData_* p_out_data_,
		std::index_sequence<MajorIndices_...> major_indices_,
		std::index_sequence<RegisterIndices_...> register_indices_
	)
	{
#pragma warning(push)
#pragma warning(disable: 26800)
		(
			_store_major_to_data_pointer<FullWidth_, MajorIndices_, FastMatrix_, OutData_, RegisterIndices_...>
			(
				std::forward<FastMatrix_>(fast_matrix_),
				p_out_data_
			), ...
		);
#pragma warning(pop)
	}
#pragma endregion
}

#endif