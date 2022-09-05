#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_INVERSE_AND_RELATED_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_INVERSE_AND_RELATED_H_INC_ 1

#include "_fast_matrix_tmp.h"
#include "_fast_matrix_underlying_identity.h"
#include "_fast_matrix_underlying_transpose.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
	/// <summary>
	/// <para> 
	///		Helper type to allow the compiler to easily perform unnamed return value optimisations, 
	///		while also outputting to a reference via a SIMD register index.
	/// </para>
	/// <para> 
	///		This is for cases such as inverse, where a reference to an output determinant may be provided, 
	///		but the user may want arithmetic scalar output.
	/// </para>
	/// </summary>
	template<typename Register_, typename Out_, std::size_t IndexInRegister_, std::size_t PerElementWidth_>
	struct _register_to_scalar_offloader final
	{
		using this_type = _register_to_scalar_offloader<Register_, Out_, IndexInRegister_, PerElementWidth_>;
		_register_to_scalar_offloader() = delete;
		_register_to_scalar_offloader(const this_type&) = delete;
		_register_to_scalar_offloader(this_type&&) = delete;

		constexpr inline _register_to_scalar_offloader(Out_& out_ref_) noexcept : outRef(out_ref_), registerToOffload()
		{
		}

		inline ~_register_to_scalar_offloader() noexcept
		{
			outRef = EmuSIMD::get_index<IndexInRegister_, typename EmuCore::TMP::remove_ref_cv<Out_>::type, PerElementWidth_>(registerToOffload);
		}

		Out_& outRef;
		Register_ registerToOffload;
	};

	enum class _inverse_stage_flag : std::uint8_t
	{
		EMPTY = 0x00,
		COFACTOR_BIT = 0x01,
		ADJUGATE_BIT = 0x02,
		INVERSE_BIT = 0x04,

		MINORS = 0x00, // Always do minors, so no need for a bit
		COFACTORS = MINORS | COFACTOR_BIT,
		ADJUGATE = COFACTORS | ADJUGATE_BIT,
		INVERSE = ADJUGATE | INVERSE_BIT
	};

	template<EmuConcepts::EmuFastMatrix FastMatUq_>
	[[nodiscard]] constexpr inline bool _valid_for_4x4_square_inverse_32bit()
	{
		return
		(
			FastMatUq_::num_major_elements == 4 &&
			FastMatUq_::num_registers_per_major == 1 &&
			FastMatUq_::register_width == 128 &&
			FastMatUq_::num_columns == FastMatUq_::num_rows &&
			FastMatUq_::per_element_width == 32 &&
			std::is_floating_point_v<typename FastMatUq_::value_type>
		);
	}

	template<bool DoCofactors_, EmuConcepts::KnownSIMD Register_>
	[[nodiscard]] constexpr inline auto _make_register_of_1s_for_det_4x4_32bit()
		-> typename EmuCore::TMP::remove_ref_cv<Register_>::type
	{
		using _in_out_register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (DoCofactors_)
		{
			return EmuSIMD::set<_in_out_register_uq, EmuSIMD::TMP::simd_register_width_v<_in_out_register_uq>>(1, -1, -1, 1);
		}
		else
		{
			return EmuSIMD::set1<_in_out_register_uq>(1);
		}
	}

	template<_inverse_stage_flag StageFlags_, EmuConcepts::EmuFastMatrix FastMatrix_, EmuConcepts::KnownSIMD Register_>
	constexpr inline auto _make_inverse_to_stage_4x4_32bit(const FastMatrix_& in_matrix_, Register_& out_determinant_)
		-> typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type
	{
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		using _register_type = typename _fast_mat_uq::register_type;
		constexpr std::size_t width = _fast_mat_uq::per_element_width;
		constexpr bool do_cofactors = EmuCore::TMP::safe_enum_and(StageFlags_, _inverse_stage_flag::COFACTOR_BIT) != _inverse_stage_flag::EMPTY;
		constexpr bool do_adjugate = EmuCore::TMP::safe_enum_and(StageFlags_, _inverse_stage_flag::ADJUGATE_BIT) != _inverse_stage_flag::EMPTY;
		constexpr bool do_inverse = EmuCore::TMP::safe_enum_and(StageFlags_, _inverse_stage_flag::INVERSE_BIT) != _inverse_stage_flag::EMPTY;

		_register_type det_sub = EmuSIMD::mul_all<width>
		(
			EmuSIMD::shuffle<1, 3, 1, 3>(in_matrix_.major_chunks[0], in_matrix_.major_chunks[2]),
			EmuSIMD::shuffle<0, 2, 0, 2>(in_matrix_.major_chunks[1], in_matrix_.major_chunks[3])
		);
		det_sub = EmuSIMD::fmsub<width>
		(
			EmuSIMD::shuffle<0, 2, 0, 2>(in_matrix_.major_chunks[0], in_matrix_.major_chunks[2]),
			EmuSIMD::shuffle<1, 3, 1, 3>(in_matrix_.major_chunks[1], in_matrix_.major_chunks[3]),
			det_sub
		);

		_register_type temp_det_0 = EmuSIMD::shuffle<0>(det_sub);
		_register_type temp_det_1 = EmuSIMD::shuffle<3>(det_sub);
		_register_type a = EmuSIMD::shuffle<0, 1, 0, 1>(in_matrix_.major_chunks[0], in_matrix_.major_chunks[1]);
		_register_type b = EmuSIMD::shuffle<2, 3, 2, 3>(in_matrix_.major_chunks[0], in_matrix_.major_chunks[1]);
		_register_type c = EmuSIMD::shuffle<0, 1, 0, 1>(in_matrix_.major_chunks[2], in_matrix_.major_chunks[3]);
		_register_type d = EmuSIMD::shuffle<2, 3, 2, 3>(in_matrix_.major_chunks[2], in_matrix_.major_chunks[3]);

		_register_type adj_d_MUL_c = EmuSIMD::matrix_2x2_multiply_adj_norm_rm<width>(d, c);
		_register_type adj_a_MUL_b = EmuSIMD::matrix_2x2_multiply_adj_norm_rm<width>(a, b);
		_register_type x = EmuSIMD::sub<width>(EmuSIMD::mul_all<width>(temp_det_1, a), EmuSIMD::matrix_2x2_multiply_rm<width>(b, adj_d_MUL_c));
		_register_type w = EmuSIMD::sub<width>(EmuSIMD::mul_all<width>(temp_det_0, d), EmuSIMD::matrix_2x2_multiply_rm<width>(c, adj_a_MUL_b));

		out_determinant_ = EmuSIMD::mul_all<width>(temp_det_0, temp_det_1);
		temp_det_1 = EmuSIMD::shuffle<2>(det_sub);
		temp_det_0 = EmuSIMD::shuffle<1>(det_sub);
		out_determinant_ = EmuSIMD::fmadd<width>(temp_det_0, temp_det_1, out_determinant_);

		_register_type y = EmuSIMD::sub<width>(EmuSIMD::mul_all<width>(temp_det_0, c), EmuSIMD::matrix_2x2_multiply_norm_adj_rm<width>(d, adj_a_MUL_b));
		_register_type z = EmuSIMD::sub<width>(EmuSIMD::mul_all<width>(temp_det_1, b), EmuSIMD::matrix_2x2_multiply_norm_adj_rm<width>(a, adj_d_MUL_c));

		if constexpr (do_inverse)
		{
			_register_type trace_of_submat_product = EmuSIMD::mul_all<width>(adj_a_MUL_b, EmuSIMD::shuffle<0, 2, 1, 3>(adj_d_MUL_c));
			trace_of_submat_product = EmuSIMD::horizontal_sum_fill<width>(trace_of_submat_product);
			out_determinant_ = EmuSIMD::sub<width>(out_determinant_, trace_of_submat_product);

			_register_type det_reciprocal = EmuSIMD::div
			(
				_make_register_of_1s_for_det_4x4_32bit<do_cofactors, _register_type>(),
				out_determinant_
			);
			x = EmuSIMD::mul_all(x, det_reciprocal);
			y = EmuSIMD::mul_all(y, det_reciprocal);
			z = EmuSIMD::mul_all(z, det_reciprocal);
			w = EmuSIMD::mul_all(w, det_reciprocal);
		}
		else if constexpr(do_cofactors)
		{
			// No inverse, but we need interchanging signs
			auto sign_mask = EmuSIMD::sign_mask<width, _register_type, 0, 1, 1, 0>();
			x = EmuSIMD::bitwise_or(x, sign_mask);
			y = EmuSIMD::bitwise_or(y, sign_mask);
			z = EmuSIMD::bitwise_or(z, sign_mask);
			w = EmuSIMD::bitwise_or(w, sign_mask);
		}

		if constexpr (do_adjugate)
		{
			return typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type
			(
				EmuSIMD::shuffle<3, 1, 3, 1>(x, y),
				EmuSIMD::shuffle<2, 0, 2, 0>(x, y),
				EmuSIMD::shuffle<3, 1, 3, 1>(z, w),
				EmuSIMD::shuffle<2, 0, 2, 0>(z, w)
			);
		}
		else
		{
			return typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type
			(
				EmuSIMD::shuffle<3, 2, 3, 2>(x, z),
				EmuSIMD::shuffle<1, 0, 1, 0>(x, z),
				EmuSIMD::shuffle<3, 2, 3, 2>(y, w),
				EmuSIMD::shuffle<1, 0, 1, 0>(y, w)
			);
		}
	}

	template<_inverse_stage_flag StageFlags_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto _make_inverse_to_stage_4x4_32bit(const FastMatrix_& in_matrix_)
		-> typename EmuMath::TMP::fast_matrix_transpose_result<FastMatrix_>::type
	{
		typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_type determinant_dummy;
		return _make_inverse_to_stage_4x4_32bit<StageFlags_>(in_matrix_, determinant_dummy);
	}

	template<EmuConcepts::EmuFastMatrix FastMatrix_, std::size_t RowIndex_, std::size_t RegisterIndex_, class Determinant_>
	constexpr inline void _gaussian_scale_result_register
	(
		FastMatrix_& row_echelon_matrix_rm_,
		typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_type pivot_,
		typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_type* p_out_registers_,
		Determinant_ p_out_determinant_
	)
	{
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		constexpr std::size_t offset = (RowIndex_ * _fast_mat_uq::num_registers_per_major) + RegisterIndex_;
		auto* p_out = (p_out_registers_ + offset);
		(*p_out) = EmuSIMD::div<_fast_mat_uq::per_element_width, _fast_mat_uq::is_signed>(*p_out, pivot_);
	}

	template<EmuConcepts::EmuFastMatrix FastMatrix_, std::size_t RowIndex_, std::size_t...MajorRegisterIndices_, class Determinant_>
	constexpr inline void _gaussian_scale_results
	(
		FastMatrix_& row_echelon_matrix_rm_,
		typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_type* p_out_registers_,
		Determinant_ p_out_determinant_
	)
	{
		auto pivot = row_echelon_matrix_rm_.template GetRegisterOfIndex<RowIndex_, RowIndex_>();
		if constexpr (!std::is_null_pointer_v<Determinant_>)
		{
			(*p_out_determinant_) = EmuSIMD::mul_all<EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::per_element_width>(*p_out_determinant_, pivot);
		}

		(
			_gaussian_scale_result_register<FastMatrix_, RowIndex_, MajorRegisterIndices_>
			(
				row_echelon_matrix_rm_,
				pivot,
				p_out_registers_,
				p_out_determinant_
			), ...
		);
	}

	template<std::size_t EliminatingRowIndex_, std::size_t RegisterIndex_, std::size_t SegmentIndex_, EmuConcepts::EmuFastMatrix FastMatrix_>
	constexpr inline void _gaussian_eliminate_row_register_segment
	(
		FastMatrix_& row_echelon_matrix_rm_,
		typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_type* p_out_registers_,
		typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_arg_type multipliers
	)
	{
		// Pivot index is ignored
		if constexpr (EliminatingRowIndex_ != SegmentIndex_)
		{
			using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
			using _register_type = typename _fast_mat_uq::register_type;
			constexpr std::size_t width = _fast_mat_uq::per_element_width;
			constexpr std::size_t out_offset = (SegmentIndex_ * _fast_mat_uq::num_registers_per_major) + RegisterIndex_;
			constexpr std::size_t out_eliminated_offset = (EliminatingRowIndex_ * _fast_mat_uq::num_registers_per_major) + RegisterIndex_;
			
			_register_type current_multiplier = EmuSIMD::set_all_to_index<SegmentIndex_ % _fast_mat_uq::num_elements_per_register, _fast_mat_uq::per_element_width>
			(
				multipliers
			);
			
			row_echelon_matrix_rm_.template GetRegister<SegmentIndex_, RegisterIndex_>() = EmuSIMD::fmadd<width>
			(
				row_echelon_matrix_rm_.template GetRegister<EliminatingRowIndex_, RegisterIndex_>(),
				current_multiplier,
				row_echelon_matrix_rm_.template GetRegister<SegmentIndex_, RegisterIndex_>()
			);
			
			auto* p_out = p_out_registers_ + out_offset;
			(*p_out) = EmuSIMD::fmadd<width>
			(
				*(p_out_registers_ + out_eliminated_offset),
				current_multiplier,
				*p_out
			);
		}
	}

	template<std::size_t EliminatingRowIndex_, std::size_t RegisterIndex_, EmuConcepts::EmuFastMatrix FastMatrix_, std::size_t...AllRowIndices_>
	constexpr inline void _gaussian_eliminate_row_register
	(
		FastMatrix_& row_echelon_matrix_rm_,
		typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_type* p_out_registers_,
		typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_arg_type neg_pivot_
	)
	{
		// The way we access columns to create multipliers can likely be improved
		// --- As it stands, this method is quite inefficient, although it is the fallback for unspecialised cases
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		using _register_type = typename _fast_mat_uq::register_type;
		auto row_echelon_transpose = row_echelon_matrix_rm_.Transpose();
		_register_type multipliers = EmuSIMD::div<_fast_mat_uq::per_element_width, _fast_mat_uq::is_signed>
		(
			row_echelon_transpose.template GetRegister<EliminatingRowIndex_, RegisterIndex_>(),
			neg_pivot_
		);
		
		(
			_gaussian_eliminate_row_register_segment<EliminatingRowIndex_, RegisterIndex_, AllRowIndices_>
			(
				row_echelon_matrix_rm_,
				p_out_registers_,
				multipliers
			), ...
		);
	}

	template<std::size_t RowIndex_, EmuConcepts::EmuFastMatrix FastMatrix_, std::size_t...AllRowIndices_, std::size_t...MajorRegisterIndices_>
	constexpr inline void _gaussian_eliminate_row
	(
		FastMatrix_& row_echelon_matrix_rm_,
		typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_type* p_out_registers_,
		std::index_sequence<AllRowIndices_...> all_row_indices_,
		std::index_sequence<MajorRegisterIndices_...> major_register_indices_
	)
	{
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		using _register_type = typename _fast_mat_uq::register_type;
		constexpr std::size_t width = _fast_mat_uq::per_element_width;
		_register_type neg_pivot = EmuSIMD::negate<width>(row_echelon_matrix_rm_.template GetRegisterOfIndex<RowIndex_, RowIndex_>());

		(
			_gaussian_eliminate_row_register<RowIndex_, MajorRegisterIndices_, FastMatrix_, AllRowIndices_...>
			(
				row_echelon_matrix_rm_,
				p_out_registers_,
				neg_pivot
			), ...
		);
	}

	template<EmuConcepts::EmuFastMatrix FastMatrix_, class Determinant_, std::size_t...RowIndices_, std::size_t...MajorRegisterIndices_>
	constexpr inline void _gaussian_elimnation_inverse
	(
		FastMatrix_& row_echelon_matrix_rm_,
		typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_type* p_out_registers_,
		std::index_sequence<RowIndices_...> row_indices_,
		std::index_sequence<MajorRegisterIndices_...> major_register_indices_,
		Determinant_ p_out_determinant_
	)
	{
		if constexpr (!std::is_null_pointer_v<Determinant_>)
		{
			using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
			(*p_out_determinant_) = EmuSIMD::set1<typename _fast_mat_uq::register_type, _fast_mat_uq::per_element_width>(1);
		}

		(
			_gaussian_eliminate_row<RowIndices_>
			(
				row_echelon_matrix_rm_,
				p_out_registers_,
				std::index_sequence<RowIndices_...>(),
				std::index_sequence<MajorRegisterIndices_...>()
			), ...
		);

		(
			_gaussian_scale_results<FastMatrix_, RowIndices_, MajorRegisterIndices_...>
			(
				row_echelon_matrix_rm_,
				p_out_registers_,
				p_out_determinant_
			), ...
		);
	}

	template
	<
		EmuConcepts::EmuFastMatrix FastMatrix_, class Determinant_, 
		std::size_t...RowIndices_, std::size_t...MajorRegisterIndices_, std::size_t...TotalRegisterIndices_
	>
	[[nodiscard]] constexpr inline auto _make_inverse_gaussian
	(
		FastMatrix_&& in_matrix_,
		std::index_sequence<RowIndices_...> row_indices_,
		std::index_sequence<MajorRegisterIndices_...> major_register_indices_,
		std::index_sequence<TotalRegisterIndices_...> total_register_indices_,
		Determinant_ p_out_determinant_ = std::nullptr_t()
	)
	{
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		using _register_type = typename _fast_mat_uq::register_type;
		using major_index_sequence = std::make_index_sequence<_fast_mat_uq::num_major_elements>;
		using row_index_sequence = std::index_sequence<RowIndices_...>;
		using major_register_index_sequence = std::index_sequence<MajorRegisterIndices_...>;
		_register_type out_registers[sizeof...(TotalRegisterIndices_)];
		_assign_identity_matrix<FastMatrix_>(out_registers, major_index_sequence(), major_register_index_sequence());

		if constexpr (_fast_mat_uq::is_column_major)
		{
			// We're manipulating rows, so we need to transpose a column-major Matrix
			auto in_matrix_row_echelon = _make_transpose_same_major(std::forward<FastMatrix_>(in_matrix_));
			_gaussian_elimnation_inverse(in_matrix_row_echelon, out_registers, row_index_sequence(), major_register_index_sequence(), p_out_determinant_);
		}
		else
		{
			if constexpr (std::is_lvalue_reference_v<FastMatrix_> || std::is_const_v<FastMatrix_>)
			{
				// We can't use the passed item as side-effects may be undesirable, so we have to copy it for modifications
				auto in_matrix_row_echelon = _fast_mat_uq(std::forward<FastMatrix_>(in_matrix_));
				_gaussian_elimnation_inverse(in_matrix_row_echelon, out_registers, row_index_sequence(), major_register_index_sequence(), p_out_determinant_);
			}
			else
			{
				// As register is supposedly a temporary, we can use it directly
				auto& in_matrix_row_echelon = EmuCore::TMP::lval_ref_cast<FastMatrix_>(std::forward<FastMatrix_>(in_matrix_));
				_gaussian_elimnation_inverse(in_matrix_row_echelon, out_registers, row_index_sequence(), major_register_index_sequence(), p_out_determinant_);
			}
		}

		return typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type
		(
			std::move
			(
				out_registers[TotalRegisterIndices_]
			)...
		);
	}

	template<_inverse_stage_flag StageFlags_, bool OutputDeterminant_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto _make_inverse_to_stage
	(
		FastMatrix_&& in_matrix_,
		typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_type& out_determinant_
	)
		-> typename EmuMath::TMP::fast_matrix_transpose_result<FastMatrix_>::type
	{
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		if constexpr (_valid_for_4x4_square_inverse_32bit<_fast_mat_uq>())
		{
			return _make_inverse_to_stage_4x4_32bit<StageFlags_>
			(
				EmuCore::TMP::const_lval_ref_cast<FastMatrix_>(std::forward<FastMatrix_>(in_matrix_)),
				out_determinant_
			);
		}
		else
		{
			// Generic case; gaussian elimination
			// --- Relatively inefficient

			if constexpr(StageFlags_ == _inverse_stage_flag::INVERSE)
			{
				if constexpr (OutputDeterminant_)
				{
					static_assert
					(
						_fast_mat_uq::num_registers_per_major == 1,
						"Internal EmuMath Error: There is currently an issue with generic FastMatrix inverses with more than 1 register per major."
					);

					return _make_inverse_gaussian
					(
						std::forward<FastMatrix_>(in_matrix_),
						std::make_index_sequence<_fast_mat_uq::num_rows>(),
						std::make_index_sequence<_fast_mat_uq::num_registers_per_major>(),
						std::make_index_sequence<_fast_mat_uq::total_num_registers>(),
						&out_determinant_
					);
				}
				else
				{
					return _make_inverse_gaussian
					(
						std::forward<FastMatrix_>(in_matrix_),
						std::make_index_sequence<_fast_mat_uq::num_rows>(),
						std::make_index_sequence<_fast_mat_uq::num_registers_per_major>(),
						std::make_index_sequence<_fast_mat_uq::total_num_registers>(),
						std::nullptr_t()
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<StageFlags_>(),
					"Unable to perform a partial inverse operation (e.g. Matrix of Minors) for a fast matrix as the generic implementation is not available. Such actions are currently only available for 4x4 matrices with 32-bit elements and 128-bit registers."
				);
			}
		}
	}
}

#endif
