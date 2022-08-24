#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_SET_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_SET_H_INC_ 1

#include "_fast_matrix_tmp.h"
#include "../../../Matrix.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
	/// <summary>
	/// <para> Returns the left-hand arg if Matrix_ is column-major, otherwise returns the right-hand arg. </para>
	/// </summary>
	template<class Matrix_, class A_, class B_>
	[[nodiscard]] constexpr inline decltype(auto) _select_arg_based_on_major(A_&& if_column_major_, B_&& if_row_major_)
	{
		using _mat_uq = typename EmuCore::TMP::remove_ref_cv<Matrix_>::type;
		if constexpr (_mat_uq::is_column_major)
		{
			return std::forward<A_>(if_column_major_);
		}
		else
		{
			return std::forward<B_>(if_row_major_);
		}
	}

	template<std::size_t MajorIndex_, EmuConcepts::EmuFastMatrix OutMatrix_, EmuConcepts::EmuMatrix ScalarMatrix_, std::size_t...NonMajorIndices_>
	[[nodiscard]] constexpr inline decltype(auto) _make_major_vector_from_scalar_matrix
	(
		ScalarMatrix_&& scalar_matrix_,
		std::index_sequence<NonMajorIndices_...> non_major_indices_
	)
	{
		using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		using in_scalar_mat_uq = typename EmuCore::TMP::remove_ref_cv<ScalarMatrix_>::type;

		// Disabled as we should only be ever accessing the same index exactly once in well-formed implementations, but false positives are given
#pragma warning(push)
#pragma warning(disable: 26800)
		return typename out_mat_uq::major_vector_type
		(
			std::forward<ScalarMatrix_>(scalar_matrix_).template AtTheoretical
			<
				_select_arg_based_on_major<OutMatrix_>(MajorIndex_, NonMajorIndices_),
				_select_arg_based_on_major<OutMatrix_>(NonMajorIndices_, MajorIndex_)
			>()...
		);
#pragma warning(pop)
	}

	template<std::size_t MajorIndex_, EmuConcepts::EmuFastMatrix OutMatrix_, EmuConcepts::EmuMatrix ScalarMatrix_, std::size_t...NonMajorIndices_>
	[[nodiscard]] constexpr inline decltype(auto) _set_register_from_scalar_matrix
	(
		ScalarMatrix_&& scalar_matrix_,
		std::index_sequence<NonMajorIndices_...> non_major_indices_
	)
	{
		using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		return EmuSIMD::setr<typename out_mat_uq::register_type, out_mat_uq::per_element_width>
		(
			std::forward<ScalarMatrix_>(scalar_matrix_).template AtTheoretical
			<
				_select_arg_based_on_major<OutMatrix_>(MajorIndex_, NonMajorIndices_),
				_select_arg_based_on_major<OutMatrix_>(NonMajorIndices_, MajorIndex_)
			>()...
		);
	}

	template<std::size_t MajorIndex_, std::size_t MajorRegisterIndex_, EmuConcepts::EmuFastMatrix OutMatrix_, EmuConcepts::EmuMatrix ScalarMatrix_>
	[[nodiscard]] constexpr inline decltype(auto) _unsafe_partial_load_register_from_scalar_matrix(ScalarMatrix_&& scalar_matrix_)
	{
		using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		using in_scalar_mat_uq = typename EmuCore::TMP::remove_ref_cv<ScalarMatrix_>::type;

		constexpr std::size_t non_major_index_offset = MajorRegisterIndex_ * out_mat_uq::elements_per_register;
		constexpr std::size_t in_offset = (MajorIndex_ * in_scalar_mat_uq::num_non_major_elements) + non_major_index_offset;
		constexpr std::size_t in_required_size_for_load = in_offset + out_mat_uq::elements_per_register;

		if constexpr (in_scalar_mat_uq::size >= in_required_size_for_load)
		{
			return EmuSIMD::load<typename out_mat_uq::register_type>
			(
				std::forward<ScalarMatrix_>(scalar_matrix_).template data
				<
					_select_arg_based_on_major<OutMatrix_>(MajorIndex_, non_major_index_offset),
					_select_arg_based_on_major<OutMatrix_>(non_major_index_offset, MajorIndex_)
				>()
			);
		}
		else
		{
			using non_major_indices = EmuCore::TMP::make_offset_index_sequence<non_major_index_offset, out_mat_uq::elements_per_register>;
			return _set_register_from_scalar_matrix<MajorIndex_, OutMatrix_>
			(
				std::forward<ScalarMatrix_>(scalar_matrix_),
				non_major_indices()
			);
		}
	}

	template<EmuConcepts::EmuFastMatrix OutMatrix_, EmuConcepts::EmuMatrix ScalarMatrix_, std::size_t MajorIndex_, std::size_t...MajorRegisterIndices_>
	[[nodiscard]] constexpr inline decltype(auto) _unsafe_load_major_vector_from_scalar_matrix(ScalarMatrix_&& scalar_matrix_)
	{
		using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		using in_scalar_mat_uq = typename EmuCore::TMP::remove_ref_cv<ScalarMatrix_>::type;

		constexpr std::size_t in_offset = MajorIndex_ * in_scalar_mat_uq::num_non_major_elements;
		constexpr std::size_t in_required_size_for_full_load = in_offset + out_mat_uq::full_width_size_per_major;

		if constexpr (in_scalar_mat_uq::size >= in_required_size_for_full_load)
		{
			// We can safely load into all registers without accessing memory outside of input bounds
			// --- In this case, we don't care about MajorRegisterIndices_ as we can just safely load contiguously from a set pointer anyway
			return typename out_mat_uq::major_vector_type
			(
				std::forward<ScalarMatrix_>(scalar_matrix_).template data
				<
					_select_arg_based_on_major<OutMatrix_>(MajorIndex_, 0),
					_select_arg_based_on_major<OutMatrix_>(0, MajorIndex_)
				>()
			);
		}
		else
		{
			// Can't do a full load without unsafely accessing memory outside of input bounds
			return typename out_mat_uq::major_vector_type
			(
				_unsafe_partial_load_register_from_scalar_matrix<MajorIndex_, MajorRegisterIndices_, OutMatrix_>
				(
					std::forward<ScalarMatrix_>(scalar_matrix_)
				)...
			);
		}
	}

	/// <summary>
	/// <para> Unsafe to call directly; this should only be called by `_load_from_scalar_matrix`. </para>
	/// </summary>
	template<EmuConcepts::EmuFastMatrix OutMatrix_, EmuConcepts::EmuMatrix ScalarMatrix_, std::size_t...MajorIndices_, std::size_t...MajorRegisterIndices_>
	[[nodiscard]] constexpr inline auto _unsafe_load_from_scalar_matrix
	(
		ScalarMatrix_&& scalar_matrix_,
		std::index_sequence<MajorRegisterIndices_...> major_register_indices_
	) -> typename EmuCore::TMP::remove_ref_cv_t<OutMatrix_>::data_type
	{
		using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		return typename out_mat_uq::data_type
		({
			_unsafe_load_major_vector_from_scalar_matrix<OutMatrix_, ScalarMatrix_, MajorIndices_, MajorRegisterIndices_...>
			(
				std::forward<ScalarMatrix_>(scalar_matrix_)
			)...
		});
	}

	template<EmuConcepts::EmuFastMatrix OutMatrix_, EmuConcepts::EmuMatrix ScalarMatrix_, std::size_t...MajorIndices_>
	[[nodiscard]] constexpr inline auto _load_from_scalar_matrix(ScalarMatrix_&& scalar_matrix_) 
		-> typename EmuCore::TMP::remove_ref_cv_t<OutMatrix_>::data_type
	{
		using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		using in_scalar_mat_uq = typename EmuCore::TMP::remove_ref_cv<ScalarMatrix_>::type;

		if constexpr (in_scalar_mat_uq::size >= out_mat_uq::elements_per_register)
		{
			using major_register_indices = typename out_mat_uq::major_register_index_sequence;
			return _unsafe_load_from_scalar_matrix<OutMatrix_, ScalarMatrix_, MajorIndices_...>
			(
				std::forward<ScalarMatrix_>(scalar_matrix_),
				major_register_indices()
			);
		}
		else
		{
			// Can't do loads as input does not have enough contiguous data, so fallback to a basic set
			using non_major_index_sequence = std::make_index_sequence<out_mat_uq::num_non_major_elements>;
#pragma warning(push)
#pragma warning(disable: 26800)
			return typename out_mat_uq::data_type
			({
				_fast_matrix_underlying::_make_major_vector_from_scalar_matrix<MajorIndices_, OutMatrix_>
				(
					std::forward<ScalarMatrix_>(scalar_matrix_),
					non_major_index_sequence()
				)...
			});
#pragma warning(pop)
		}
	}
}

#endif
