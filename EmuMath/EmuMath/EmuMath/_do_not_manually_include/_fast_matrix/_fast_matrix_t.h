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

		using major_chunk_type = typename std::conditional<(num_registers_per_major <= 1), register_type, std::array<register_type, num_registers_per_major>>::type;
		using data_type = std::array<major_chunk_type, num_major_elements>;
		using major_index_sequence = std::index_sequence<num_major_elements>;

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
			return data_type({ std::forward<FastMajorVectors_>(fast_major_vectors_).data... });
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
#pragma endregion

#pragma region ARITHMETIC
	public:
		template<EmuConcepts::EmuFastMatrix RhsFastMatrix_>
		requires EmuConcepts::EmuFastMatrixMultPair<this_type, RhsFastMatrix_>
		[[nodiscard]] constexpr inline auto Multiply(RhsFastMatrix_&& rhs_) const
		{
			this_type mResult;
			register_type vW = major_chunks[0];
			register_type vX = EmuSIMD::shuffle<0>(vW);
			register_type vY = EmuSIMD::shuffle<1>(vW);
			register_type vZ = EmuSIMD::shuffle<2>(vW);
			vW = EmuSIMD::shuffle<3>(vW);

			// Perform the operation on the first row
			vX = _mm_mul_ps(vX, rhs_.major_chunks[0]);
			vY = _mm_mul_ps(vY, rhs_.major_chunks[1]);
			vZ = _mm_mul_ps(vZ, rhs_.major_chunks[2]);
			vW = _mm_mul_ps(vW, rhs_.major_chunks[3]);
			// Perform a binary add to reduce cumulative errors
			vX = _mm_add_ps(vX, vZ);
			vY = _mm_add_ps(vY, vW);
			vX = _mm_add_ps(vX, vY);
			mResult.major_chunks[0] = vX;
			// Repeat for the other 3 rows

			vW = major_chunks[1];
			vX = EmuSIMD::shuffle<0>(vW);
			vY = EmuSIMD::shuffle<1>(vW);
			vZ = EmuSIMD::shuffle<2>(vW);
			vW = EmuSIMD::shuffle<3>(vW);

			vX = _mm_mul_ps(vX, rhs_.major_chunks[0]);
			vY = _mm_mul_ps(vY, rhs_.major_chunks[1]);
			vZ = _mm_mul_ps(vZ, rhs_.major_chunks[2]);
			vW = _mm_mul_ps(vW, rhs_.major_chunks[3]);
			vX = _mm_add_ps(vX, vZ);
			vY = _mm_add_ps(vY, vW);
			vX = _mm_add_ps(vX, vY);
			mResult.major_chunks[1] = vX;

			vW = major_chunks[2];
			vX = EmuSIMD::shuffle<0>(vW);
			vY = EmuSIMD::shuffle<1>(vW);
			vZ = EmuSIMD::shuffle<2>(vW);
			vW = EmuSIMD::shuffle<3>(vW);

			vX = _mm_mul_ps(vX, rhs_.major_chunks[0]);
			vY = _mm_mul_ps(vY, rhs_.major_chunks[1]);
			vZ = _mm_mul_ps(vZ, rhs_.major_chunks[2]);
			vW = _mm_mul_ps(vW, rhs_.major_chunks[3]);
			vX = _mm_add_ps(vX, vZ);
			vY = _mm_add_ps(vY, vW);
			vX = _mm_add_ps(vX, vY);
			mResult.major_chunks[2] = vX;

			vW = major_chunks[3];
			vX = EmuSIMD::shuffle<0>(vW);
			vY = EmuSIMD::shuffle<1>(vW);
			vZ = EmuSIMD::shuffle<2>(vW);
			vW = EmuSIMD::shuffle<3>(vW);

			vX = _mm_mul_ps(vX, rhs_.major_chunks[0]);
			vY = _mm_mul_ps(vY, rhs_.major_chunks[1]);
			vZ = _mm_mul_ps(vZ, rhs_.major_chunks[2]);
			vW = _mm_mul_ps(vW, rhs_.major_chunks[3]);
			vX = _mm_add_ps(vX, vZ);
			vY = _mm_add_ps(vY, vW);
			vX = _mm_add_ps(vX, vY);
			mResult.major_chunks[3] = vX;
			return mResult;
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
	//str_ << fast_matrix_.Store();
	return str_;
}

#endif
