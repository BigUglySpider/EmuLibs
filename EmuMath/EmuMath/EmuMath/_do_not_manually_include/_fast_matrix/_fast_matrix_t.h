#ifndef EMU_MATH_FAST_MATRIX_T_H_INC_
#define EMU_MATH_FAST_MATRIX_T_H_INC_ 1

#include "_helpers/_all_fast_matrix_helpers.h"
#include "../../FastVector.h"
#include <array>

namespace EmuMath
{
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool IsColumnMajor_, std::size_t RegisterWidth_>
	struct FastMatrix
	{
#pragma region COMMON_STATIC_INFO
	public:
		static constexpr std::size_t num_columns = NumColumns_;
		static constexpr std::size_t num_rows = NumRows_;
		static constexpr bool is_column_major = IsColumnMajor_;
		static constexpr bool is_row_major = !is_column_major;
		static constexpr std::size_t num_major_elements = is_column_major ? num_columns : num_rows;
		static constexpr std::size_t num_non_major_elements = is_column_major ? num_rows : num_columns;
		/// <summary> The number of elements that this Vector behaves to encapsulate. </summary>
		static constexpr std::size_t size = num_columns * num_rows;
		/// <summary> The width provided for this Vector's registers to use, in bits. </summary>
		static constexpr std::size_t register_width = RegisterWidth_ > 0 ? RegisterWidth_ : 1;

		/// <summary> Alias to this Vector type. </summary>
		using this_type = EmuMath::FastMatrix<NumColumns_, NumRows_, T_, IsColumnMajor_, RegisterWidth_>;
		/// <summary> Alias to the type of values within this Vector. </summary>
		using value_type = typename std::remove_cv<T_>::type;
		/// <summary> Alias to the type of SIMD register used for this Vector's data. </summary>
		using register_type = typename EmuSIMD::TMP::register_type<value_type, register_width>::type;
		/// <summary> Alias to the argument type used to pass an instance of this Vector's register_type. </summary>
		using register_arg_type = typename EmuSIMD::TMP::register_arg_type<value_type, register_width>::type;
		/// <summary> Alias to the register type used as an argument for the number of shifts performed when a register argument is used instead of a constant. </summary>
		using shift_register_type = __m128i;
		/// <summary> The number of bits each element is interpreted to consume within this Vector's shift_register_type, with 8-bit bytes regardless of CHAR_BIT. </summary>
		static constexpr std::size_t shift_register_per_element_width = 64;
		/// <summary> The preferred floating-point type for this Vector, used for floating-point-based calculations using this Vector. </summary>
		using preferred_floating_point = typename std::conditional<(sizeof(value_type) >= 64), double, float>::type;

		/// <summary> Boolean indicating if this Vector's encapsulated type is integral. </summary>
		static constexpr bool is_integral = std::is_integral<value_type>::value;
		/// <summary> Boolean indicating if this Vector's encapsulated type is floating-point. </summary>
		static constexpr bool is_floating_point = std::is_floating_point<value_type>::value;
		/// <summary> Boolean indicating if this Vector's encapsulated type is signed. </summary>
		static constexpr bool is_signed = std::is_signed<value_type>::value;

		/// <summary> The number of bytes consumed by a single element in this Matrix. </summary>
		static constexpr std::size_t per_element_byte_size = sizeof(value_type);
		/// <summary> The number of bits consumed by a single element in this Matrix with 8-bit bytes, regardless of the value of CHAR_BIT. </summary>
		static constexpr std::size_t per_element_width = per_element_byte_size * 8;
		/// <summary> The number of bits required for each major chunk of this Matrix. </summary>
		static constexpr std::size_t per_major_width = num_non_major_elements * per_element_width;
		/// <summary> Boolean indicating if a major chunks of this Matrix require a partial register. </summary>
		static constexpr bool majors_require_partial_register = (per_major_width % register_width) != 0;
		/// <summary> The total number of registers required to store each major chunk of this Matrix, including the partial register if needed. </summary>
		static constexpr std::size_t num_registers_per_major = (per_major_width / register_width) + (majors_require_partial_register ? 1 : 0);
		/// <summary> The total nubmer of registers used to store this Matrix, including partial ones if needed. </summary>
		static constexpr std::size_t total_num_registers = num_registers_per_major * num_major_elements;
		static constexpr std::size_t num_elements_per_register = register_width / per_element_width;

		using major_chunk_type = typename std::conditional<(num_registers_per_major <= 1), register_type, std::array<register_type, num_registers_per_major>>::type;
		using data_type = std::array<major_chunk_type, num_major_elements>;
		using major_index_sequence = std::make_index_sequence<num_major_elements>;
		using major_register_sequence = std::make_index_sequence<num_registers_per_major>;

#pragma region CONSTRUCTION_HELPERS
	private:
		template<EmuConcepts::EmuMatrix ScalarMatrix_, std::size_t...MajorIndices_>
		[[nodiscard]] static constexpr inline data_type _make_data_from_scalar_matrix(ScalarMatrix_&& scalar_matrix_, std::index_sequence<MajorIndices_...> major_indices_)
		{
			using _in_scalar_mat_uq = typename EmuCore::TMP::remove_ref_cv<ScalarMatrix_>::type;
			if constexpr (_in_scalar_mat_uq::is_column_major == is_column_major)
			{
				if constexpr (num_registers_per_major == 1)
				{
					if constexpr (is_column_major)
					{
						return data_type
						({
							EmuSIMD::load<register_type>(std::forward<ScalarMatrix_>(scalar_matrix_).template data<MajorIndices_, 0>())...
						});
					}
					else
					{
						return data_type
						({
							EmuSIMD::load<register_type>(std::forward<ScalarMatrix_>(scalar_matrix_).template data<0, MajorIndices_>())...
						});
					}
				}
				else
				{
					// TODO: Sequential load of major chunks where > 1 register per chunk
				}
			}
			else
			{
				// TODO: Set only when loading mismatched major

			}
		}

		template<EmuConcepts::EmuFastVector...FastMajorVectors_, std::size_t...MajorIndices_>
		[[nodiscard]] static constexpr inline data_type _make_data_from_fast_vectors(std::index_sequence<MajorIndices_...> major_indices_, FastMajorVectors_&&...fast_major_vectors_)
		{
			// TODO: Better checks
			return data_type({ std::forward<FastMajorVectors_>(fast_major_vectors_).data... });
		}

		template<std::size_t MajorIndex_, EmuConcepts::KnownSIMD...Registers_, std::size_t...RegisterIndices_>
		[[nodiscard]] static constexpr inline major_chunk_type _make_major_chunk_array_from_registers
		(
			std::tuple<Registers_...>& registers_,
			std::index_sequence<RegisterIndices_...> register_indices_
		)
		{
			constexpr std::size_t offset = MajorIndex_ * num_registers_per_major;
			return major_chunk_type
			({
				std::forward<decltype(std::get<offset + RegisterIndices_>(registers_))>
				(
					std::get<offset + RegisterIndices_>(registers_)
				)...
			});
		}

		template<EmuConcepts::KnownSIMD...Registers_, std::size_t...MajorIndices_>
		[[nodiscard]] static constexpr inline data_type _make_data_from_registers(std::index_sequence<MajorIndices_...> major_indices_, Registers_&&...registers_)
		{
			if constexpr (num_registers_per_major == 1)
			{
				return data_type({ std::forward<Registers_>(registers_)... });
			}
			else
			{
				auto register_tuple = std::forward_as_tuple<Registers_...>(std::forward<Registers_>(registers_)...);
				return data_type
				({
					_make_major_chunk_array_from_registers<MajorIndices_>
					(
						register_tuple,
						major_register_sequence()
					)...
				});
			}
		}
#pragma endregion

#pragma region CONSTRUCTORS
	public:
		constexpr inline FastMatrix() noexcept = default;
		constexpr inline FastMatrix(this_type&&) noexcept = default;
		constexpr inline FastMatrix(const this_type&) noexcept = default;

		template<EmuConcepts::EmuMatrix ScalarMatrix_>
		constexpr inline FastMatrix(ScalarMatrix_&& scalar_matrix_to_load_) :
			major_chunks(_make_data_from_scalar_matrix(std::forward<ScalarMatrix_>(scalar_matrix_to_load_), major_index_sequence()))
		{
		}

		template
		<
			EmuConcepts::EmuFastVector...MajorFastVectors_,
			typename = std::enable_if_t<sizeof...(MajorFastVectors_) == num_major_elements>
		>
		constexpr inline FastMatrix(MajorFastVectors_&&...major_vectors_) :
			major_chunks(_make_data_from_fast_vectors(major_index_sequence(), std::forward<MajorFastVectors_>(major_vectors_)...))
		{
		}

		template
		<
			EmuConcepts::KnownSIMD...Registers_,
			typename = std::enable_if_t
			<
				sizeof...(Registers_) == total_num_registers
			>
		>
		constexpr inline FastMatrix(Registers_&&...major_order_registers_)
			: major_chunks(_make_data_from_registers(major_index_sequence(), std::forward<Registers_>(major_order_registers_)...))
		{
		}

		template
		<
			class...MajorChunks_,
			typename = std::enable_if_t
			<
				sizeof...(MajorChunks_) == num_major_elements &&
				num_registers_per_major != 1
			>
		>
		constexpr inline FastMatrix(MajorChunks_&&...major_chunks_)
			: major_chunks({std::forward<MajorChunks_>(major_chunks_)...})
		{
		}
#pragma endregion

#pragma region GETS
	public:
		template<std::size_t MajorIndex_, std::size_t RegisterIndex_ = 0>
		[[nodiscard]] constexpr inline register_type& GetRegister()
		{
			if constexpr (MajorIndex_ < num_major_elements)
			{
				if constexpr (RegisterIndex_ < num_registers_per_major)
				{
					if constexpr (num_registers_per_major > 1)
					{
						return major_chunks[MajorIndex_][RegisterIndex_];
					}
					else
					{
						return major_chunks[MajorIndex_];
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<RegisterIndex_>(),
						"Attempted to retrieve a register from an EmuMath FastMatrix, but the provided Register Index exceeds the maximum register index for a major within the Matrix."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<MajorIndex_>(),
					"Attempted to retrieve a register from an EmuMath FastMatrix, but the provided Major index exceeds the maximum major index of the Matrix."
				);
			}
		}

		template<std::size_t MajorIndex_, std::size_t RegisterIndex_ = 0>
		[[nodiscard]] constexpr inline const register_type& GetRegister() const
		{
			return const_cast<this_type*>(this)->template GetRegister<MajorIndex_, RegisterIndex_>();
		}

		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		[[nodiscard]] constexpr inline register_type GetRegisterOfIndex() const
		{
			constexpr std::size_t major_index = is_column_major ? ColumnIndex_ : RowIndex_;
			constexpr std::size_t non_major_index = is_column_major ? RowIndex_ : ColumnIndex_;
			constexpr std::size_t register_index = non_major_index / num_elements_per_register;
			constexpr std::size_t element_index = non_major_index % num_elements_per_register;
			return EmuSIMD::set_all_to_index<element_index, per_element_width>(GetRegister<major_index, register_index>());
		}
#pragma endregion

#pragma region ARITHMETIC
	private:
		template
		<
			EmuConcepts::EmuFastMatrix Lhs_, EmuConcepts::EmuFastMatrix Rhs_,
			std::size_t RegisterIndex_, std::size_t LhsRowIndex_, std::size_t...RhsRowIndicesExcept0_
		>
		[[nodiscard]] static constexpr inline register_type _multiply_squares_chunk_lhsrm_rhsrm(Lhs_&& lhs_, Rhs_&& rhs_)
		{
			using _lhs_uq = typename EmuCore::TMP::remove_ref_cv<Lhs_>::type;
			constexpr std::size_t calc_per_element_per_width = _lhs_uq::per_element_width;
			if constexpr (sizeof...(RhsRowIndicesExcept0_) == 0)
			{
				return EmuSIMD::mul_all<calc_per_element_per_width>
				(
					std::forward<Lhs_>(lhs_).template GetRegisterOfIndex<0, LhsRowIndex_>(),
					std::forward<Rhs_>(rhs_).template GetRegister<0, RegisterIndex_>()
				);
			}
			else
			{
				register_type lhs_major = std::forward<Lhs_>(lhs_).template GetRegister<LhsRowIndex_, RegisterIndex_>();
				register_type result = EmuSIMD::mul_all<calc_per_element_per_width>
				(
					std::forward<Lhs_>(lhs_).template GetRegisterOfIndex<0, LhsRowIndex_>(),
					std::forward<Rhs_>(rhs_).template GetRegister<0, RegisterIndex_>()
				);

				(
					(
						result = EmuSIMD::fmadd<calc_per_element_per_width>
						(
							std::forward<Lhs_>(lhs_).template GetRegisterOfIndex<RhsRowIndicesExcept0_, LhsRowIndex_>(),
							std::forward<Rhs_>(rhs_).template GetRegister<RhsRowIndicesExcept0_, RegisterIndex_>(),
							result
						)
					), ...
				);
				return result;
			}
		}

		template
		<
			std::size_t LhsRowIndex_, EmuConcepts::EmuFastMatrix Lhs_, EmuConcepts::EmuFastMatrix Rhs_,
			std::size_t...LhsRowIndices_, std::size_t...RhsRowIndicesExcept0_, std::size_t...RegisterIndices_
		>
		[[nodiscard]] static constexpr inline auto _do_squares_multiply_multi_registers_for_chunk_lhsrm_rhsrm
		(
			Lhs_&& lhs_,
			Rhs_&& rhs_,
			std::index_sequence<RhsRowIndicesExcept0_...> rhs_row_indices_except_0_,
			std::index_sequence<RegisterIndices_...> register_indices_
		)
		{
			using _lhs_uq = typename EmuCore::TMP::remove_ref_cv<Lhs_>::type;
			using _rhs_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
			using _out_mat = FastMatrix<_rhs_uq::num_columns, _lhs_uq::num_rows, typename _lhs_uq::value_type, _lhs_uq::is_column_major, _lhs_uq::register_width>;
			return typename _out_mat::major_chunk_type
			({
				_multiply_squares_chunk_lhsrm_rhsrm<Lhs_, Rhs_, RegisterIndices_, LhsRowIndex_, RhsRowIndicesExcept0_...>
				(
					std::forward<Lhs_>(lhs_),
					std::forward<Rhs_>(rhs_)
				)...
			});
		}

		template
		<
			EmuConcepts::EmuFastMatrix Lhs_, EmuConcepts::EmuFastMatrix Rhs_,
			std::size_t...LhsRowIndices_, std::size_t...RhsRowIndicesExcept0_, std::size_t...RegisterIndices_
		>
		[[nodiscard]] static constexpr inline auto _do_squares_multiply_multi_registers_lhsrm_rhsrm
		(
			Lhs_&& lhs_,
			Rhs_&& rhs_,
			std::index_sequence<LhsRowIndices_...> lhs_row_indices_,
			std::index_sequence<RhsRowIndicesExcept0_...> rhs_row_indices_except_0_,
			std::index_sequence<RegisterIndices_...> register_indices_
		)
		{
			using _lhs_uq = typename EmuCore::TMP::remove_ref_cv<Lhs_>::type;
			using _rhs_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
			using _out_mat = FastMatrix<_rhs_uq::num_columns, _lhs_uq::num_rows, typename _lhs_uq::value_type, _lhs_uq::is_column_major, _lhs_uq::register_width>;
			return _out_mat
			(
				_do_squares_multiply_multi_registers_for_chunk_lhsrm_rhsrm<LhsRowIndices_>
				(
					std::forward<Lhs_>(lhs_),
					std::forward<Rhs_>(rhs_),
					std::index_sequence<RhsRowIndicesExcept0_...>(),
					std::index_sequence<RegisterIndices_...>()
				)...
			);
		}

		template<EmuConcepts::EmuFastMatrix Lhs_, EmuConcepts::EmuFastMatrix Rhs_, std::size_t...LhsRowIndices_, std::size_t...RhsRowIndicesExcept0_>
		[[nodiscard]] static constexpr inline auto _do_multiply_lhsrm_rhsrm
		(
			Lhs_&& lhs_,
			Rhs_&& rhs_,
			std::index_sequence<LhsRowIndices_...> lhs_row_indices_,
			std::index_sequence<RhsRowIndicesExcept0_...> rhs_row_indices_except_0_
		) -> EmuMath::FastMatrix
			<
				EmuCore::TMP::remove_ref_cv_t<Rhs_>::num_columns,
				EmuCore::TMP::remove_ref_cv_t<Lhs_>::num_rows,
				typename EmuCore::TMP::remove_ref_cv_t<Lhs_>::value_type,
				EmuCore::TMP::remove_ref_cv_t<Lhs_>::is_column_major,
				EmuCore::TMP::remove_ref_cv_t<Lhs_>::register_width
			>
		{
			// TODO: BETTER GENERALISE
			using _lhs_uq = typename EmuCore::TMP::remove_ref_cv<Lhs_>::type;
			using _rhs_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
			using _out_mat = FastMatrix<_rhs_uq::num_columns, _lhs_uq::num_rows, typename _lhs_uq::value_type, _lhs_uq::is_column_major, _lhs_uq::register_width>;
			constexpr bool both_square = _lhs_uq::num_columns == _lhs_uq::num_rows && _rhs_uq::num_columns == _rhs_uq::num_rows;

			if constexpr(both_square)
			{
				if constexpr(_lhs_uq::num_registers_per_major == 1)
				{
					return _out_mat
					(
						_multiply_squares_chunk_lhsrm_rhsrm<Lhs_, Rhs_, 0, LhsRowIndices_, RhsRowIndicesExcept0_...>
						(
							std::forward<Lhs_>(lhs_),
							std::forward<Rhs_>(rhs_)
						)...
					);
				}
				else
				{
					return _do_squares_multiply_multi_registers_lhsrm_rhsrm
					(
						std::forward<Lhs_>(lhs_),
						std::forward<Rhs_>(rhs_),
						std::index_sequence<LhsRowIndices_...>(),
						std::index_sequence<RhsRowIndicesExcept0_...>(),
						std::make_index_sequence<_lhs_uq::num_registers_per_major>()
					);
				}
			}
			else
			{
				// TODO: NON-SQUARE MULT
				if constexpr (_lhs_uq::num_registers_per_major == 1 && _rhs_uq::num_registers_per_major == 1 && _out_mat::num_registers_per_major == 1)
				{
					// We can fallback to the basic square implementation here
					return _do_squares_multiply_multi_registers_lhsrm_rhsrm
					(
						std::forward<Lhs_>(lhs_),
						std::forward<Rhs_>(rhs_),
						std::index_sequence<LhsRowIndices_...>(),
						std::index_sequence<RhsRowIndicesExcept0_...>(),
						std::make_index_sequence<_lhs_uq::num_registers_per_major>()
					);
				}
				else
				{
					return {};
				}
			}
		}

	public:
		template<EmuConcepts::EmuFastMatrix RhsFastMatrix_>
		requires EmuConcepts::EmuFastMatrixMultPair<this_type, RhsFastMatrix_>
		[[nodiscard]] constexpr inline auto Multiply(RhsFastMatrix_&& rhs_) const
			-> EmuMath::FastMatrix<EmuCore::TMP::remove_ref_cv_t<RhsFastMatrix_>::num_columns, num_rows, value_type, is_column_major, register_width>
		{
			if constexpr (is_column_major)
			{
				// TODO: Support for more than RM*RM
			}
			else
			{
				using _rhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<RhsFastMatrix_>::type;
				using lhs_row_indices = std::make_index_sequence<num_rows>;
				constexpr std::size_t rhs_used_size =
				(
					_rhs_fast_mat_uq::num_columns < _rhs_fast_mat_uq::num_rows ?
					_rhs_fast_mat_uq::num_columns :
					_rhs_fast_mat_uq::num_rows
				);
				using rhs_row_indices_except_0 = EmuCore::TMP::make_offset_index_sequence<1, rhs_used_size - 1>;
				return _do_multiply_lhsrm_rhsrm(*this, std::forward<RhsFastMatrix_>(rhs_), lhs_row_indices(), rhs_row_indices_except_0());
			}
		}
#pragma endregion

#pragma region ASSIGNMENT_OPERATORS
	public:
		constexpr inline this_type& operator=(const this_type&) = default;
		constexpr inline this_type& operator=(this_type&&) = default;
#pragma endregion

#pragma region DATA
	public:
		data_type major_chunks;
#pragma endregion
	};
}

template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool IsColumnMajor_, std::size_t RegisterWidth_>
inline std::ostream& operator<<(std::ostream& str_, const EmuMath::FastMatrix<NumColumns_, NumRows_, T_, IsColumnMajor_, RegisterWidth_>& fast_matrix_)
{
	// TODO: GENERALISE FOR ANY SIZE, NOT JUST 4x4 RM
	if constexpr (NumColumns_ == NumRows_)
	{
		constexpr std::size_t OutSize_ = NumColumns_ <= 4 ? 4 : 8;
		EmuMath::Matrix<OutSize_, OutSize_, float, false> mat;
		if constexpr (NumColumns_ <= 4)
		{
			_mm_store_ps(mat.data<0, 0>(), fast_matrix_.major_chunks[0]);
			_mm_store_ps(mat.data<0, 1>(), fast_matrix_.major_chunks[1]);
			_mm_store_ps(mat.data<0, 2>(), fast_matrix_.major_chunks[2]);
			_mm_store_ps(mat.data<0, 3>(), fast_matrix_.major_chunks[3]);
		}
		else if constexpr (NumColumns_ <= 8)
		{
			_mm_store_ps(mat.data<0, 0>(), fast_matrix_.major_chunks[0][0]);
			_mm_store_ps(mat.data<0, 1>(), fast_matrix_.major_chunks[1][0]);
			_mm_store_ps(mat.data<0, 2>(), fast_matrix_.major_chunks[2][0]);
			_mm_store_ps(mat.data<0, 3>(), fast_matrix_.major_chunks[3][0]);
			_mm_store_ps(mat.data<0, 4>(), fast_matrix_.major_chunks[4][0]);
			_mm_store_ps(mat.data<0, 5>(), fast_matrix_.major_chunks[5][0]);
			_mm_store_ps(mat.data<0, 6>(), fast_matrix_.major_chunks[6][0]);
			_mm_store_ps(mat.data<0, 7>(), fast_matrix_.major_chunks[7][0]);

			_mm_store_ps(mat.data<4, 0>(), fast_matrix_.major_chunks[0][1]);
			_mm_store_ps(mat.data<4, 1>(), fast_matrix_.major_chunks[1][1]);
			_mm_store_ps(mat.data<4, 2>(), fast_matrix_.major_chunks[2][1]);
			_mm_store_ps(mat.data<4, 3>(), fast_matrix_.major_chunks[3][1]);
			_mm_store_ps(mat.data<4, 4>(), fast_matrix_.major_chunks[4][1]);
			_mm_store_ps(mat.data<4, 5>(), fast_matrix_.major_chunks[5][1]);
			_mm_store_ps(mat.data<4, 6>(), fast_matrix_.major_chunks[6][1]);
			_mm_store_ps(mat.data<4, 7>(), fast_matrix_.major_chunks[7][1]);
		}

		str_ << mat;
	}
	else
	{
		str_ << "oops, not done non-square 4x4-8x8 output yet";
	}
	return str_;
}

#endif
