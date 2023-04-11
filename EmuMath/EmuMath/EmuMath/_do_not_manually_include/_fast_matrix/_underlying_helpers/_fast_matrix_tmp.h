#ifndef EMU_MATH_FAST_MATRIX_TMP_H_INC_
#define EMU_MATH_FAST_MATRIX_TMP_H_INC_ 1

#include "../../__common/_common_math_tmp.h"
#include "../../../FastVector.h"
#include "../../../Matrix.h"
#include "../../../../EmuCore/TMPHelpers/TypeConvertors.h"
#include "../../../../EmuCore/TMPHelpers/VariadicHelpers.h"
#include <functional>
#include <type_traits>

namespace EmuMath
{
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool IsColumnMajor_ = true, std::size_t RegisterWidth_ = 128>
	struct FastMatrix;
}

namespace EmuMath::TMP
{
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool IsColumnMajor_, std::size_t RegisterWidth_>
	struct is_emu_fast_matrix<EmuMath::FastMatrix<NumColumns_, NumRows_, T_, IsColumnMajor_, RegisterWidth_>>
	{
		static constexpr bool value = true;
	};

	/// <summary>
	/// <para> Helper type to retrieve the `register_type` of an input EmuMath FastMatrix type. </para>
	/// </summary>
	template<EmuConcepts::EmuFastMatrix FastMatrix_>
	struct fast_matrix_register_type
	{
	private:
		using _in_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;

	public:
		using type = typename _in_fast_mat_uq::register_type;
	};

	/// <summary>
	/// <para> Helper type to retrieve the index sequences to contiguously iterate over an EmuMath FastMatrix via compile-time iteration. </para>
	/// </summary>
	template<EmuConcepts::EmuFastMatrix FastMatrix_>
	struct fast_matrix_full_register_sequences
	{
	private:
		using _fast_mat_uq = typename std::remove_cvref<FastMatrix_>::type;
		template<std::size_t...MajorIndices_, std::size_t...NonMajorIndices_>
		static constexpr inline auto _determine_types_pair(std::index_sequence<MajorIndices_...> major_indices_, std::index_sequence<NonMajorIndices_...> non_major_indices_)
		{
			constexpr std::size_t num_major_elements = _fast_mat_uq::num_major_elements;
			constexpr std::size_t num_registers_per_major = _fast_mat_uq::num_registers_per_major;

			using major_index_sequence = typename EmuCore::TMP::variadic_splice_integer_sequences
			<
				EmuCore::TMP::make_duplicated_index_sequence<MajorIndices_, num_registers_per_major>...
			>::type;

			using register_index_sequence = typename EmuCore::TMP::looped_integer_sequence
			<
				std::index_sequence<NonMajorIndices_...>,
				num_major_elements - 1
			>::type;

			return std::pair<major_index_sequence, register_index_sequence>();
		}

		using _major_and_register_sequences_pair = decltype
		(
			_determine_types_pair
			(
				std::make_index_sequence<_fast_mat_uq::num_major_elements>(),
				std::make_index_sequence<_fast_mat_uq::num_registers_per_major>()
			)
		);

	public:
		using major_index_sequence = typename _major_and_register_sequences_pair::first_type;
		using register_index_sequence = typename _major_and_register_sequences_pair::second_type;
	};
}

namespace EmuMath::Concepts
{
	/// <summary>
	/// <para> Concept representing a pair of types meeting the `EmuFastMatrix` concept which can additionally be multiplied in the given order. </para>
	/// <para> Multiplication order is important; `Lhs_ * Rhs_` may not be a valid multiplication, while `Rhs_ * Lhs_` may be valid, for example. </para>
	/// <para> If Lhs_ is column-major, Rhs_ may have any major-order. Otherwise, Lhs_ and Rhs_ must have the same major-order. </para>
	/// </summary>
	template<class Lhs_, class Rhs_>
	concept EmuFastMatrixMultPair =
	(
		(EmuConcepts::EmuFastMatrix<Lhs_>) &&
		(EmuConcepts::EmuFastMatrix<Rhs_>) &&
		(EmuCore::TMP::remove_ref_cv_t<Lhs_>::num_columns == EmuCore::TMP::remove_ref_cv_t<Rhs_>::num_rows) &&
		(EmuCore::TMP::remove_ref_cv_t<Lhs_>::register_width == EmuCore::TMP::remove_ref_cv_t<Rhs_>::register_width) &&
		(std::is_same_v<typename EmuCore::TMP::remove_ref_cv_t<Lhs_>::value_type, typename EmuCore::TMP::remove_ref_cv_t<Rhs_>::value_type>) &&
		(
			(EmuCore::TMP::remove_ref_cv_t<Lhs_>::is_column_major) ||
			(EmuCore::TMP::remove_ref_cv_t<Lhs_>::is_column_major == EmuCore::TMP::remove_ref_cv_t<Rhs_>::is_column_major)
		)
	);

	template<class Lhs_, class...Others_>
	concept EmuFastMatricesBasicOpCompatible =
	(
		(EmuConcepts::EmuFastMatrix<Lhs_>) &&
		(... && EmuConcepts::EmuFastMatrix<Others_>) &&
		(... && std::is_same_v<typename EmuCore::TMP::remove_ref_cv_t<Lhs_>::register_type, typename EmuCore::TMP::remove_ref_cv_t<Others_>::register_type>) &&
		(... && std::is_same_v<typename EmuCore::TMP::remove_ref_cv_t<Lhs_>::value_type, typename EmuCore::TMP::remove_ref_cv_t<Others_>::value_type>) &&
		(... && (EmuCore::TMP::remove_ref_cv_t<Lhs_>::is_column_major == EmuCore::TMP::remove_ref_cv_t<Others_>::is_column_major))
	);

	template<class Lhs_, class...FastVectors_>
	concept EmuFastMatrixAndVectorsBasicOpCompatible =
	(
		(EmuConcepts::EmuFastMatrix<Lhs_>) &&
		(... && EmuConcepts::EmuFastVector<FastVectors_>) &&
		(... && std::is_same_v<typename EmuCore::TMP::remove_ref_cv_t<Lhs_>::register_type, typename EmuCore::TMP::remove_ref_cv_t<FastVectors_>::register_type>) &&
		(... && std::is_same_v<typename EmuCore::TMP::remove_ref_cv_t<Lhs_>::value_type, typename EmuCore::TMP::remove_ref_cv_t<FastVectors_>::value_type>)
	);

	template<class Lhs_, class...Registers_>
	concept EmuFastMatrixAndRegistersBasicOpCompatible =
	(
		(EmuConcepts::EmuFastMatrix<Lhs_>) &&
		(... && EmuConcepts::KnownSIMD<Registers_>) &&
		(... && std::is_same_v<typename EmuCore::TMP::remove_ref_cv_t<Lhs_>::register_type, typename EmuCore::TMP::remove_ref_cv<Registers_>::type>)
	);

	template<class Lhs_, class...Scalars_>
	concept EmuFastMatrixAndScalarsBasicOpCompatible =
	(
		(EmuConcepts::EmuFastMatrix<Lhs_>) &&
		(... && EmuConcepts::Arithmetic<Scalars_>) &&
		(
			... && 
			(
				std::is_same_v
				<
					typename EmuCore::TMP::remove_ref_cv<typename EmuCore::TMP::remove_ref_cv_t<Lhs_>::value_type>::type,
					typename EmuCore::TMP::remove_ref_cv<Scalars_>::type
				> ||
				EmuCore::TMP::is_static_castable_v
				<
					Scalars_,
					typename EmuCore::TMP::remove_ref_cv<typename EmuCore::TMP::remove_ref_cv_t<Lhs_>::value_type>::type
				>
			)
		)
	);

	namespace _fast_matrix_underlying
	{
		template<class Lhs_, class Rhs_>
		concept _any_basic_op_compatible_single_lhs =
		(
			EmuConcepts::EmuFastMatricesBasicOpCompatible<Lhs_, Rhs_> ||
			EmuConcepts::EmuFastMatrixAndVectorsBasicOpCompatible<Lhs_, Rhs_> ||
			EmuConcepts::EmuFastMatrixAndRegistersBasicOpCompatible<Lhs_, Rhs_> ||
			EmuConcepts::EmuFastMatrixAndScalarsBasicOpCompatible<Lhs_, Rhs_>
		);
	}

	template<class Lhs_, class...Others_>
	concept EmuFastMatrixBasicOpCompatible =
	(
		(... && EmuConcepts::_fast_matrix_underlying::_any_basic_op_compatible_single_lhs<Lhs_, Others_>)
	);
}

namespace EmuMath::TMP
{
	/// <summary>
	/// <para> Helper type to determine the resulting FastMatrix from multiplying two EmuMath FastMatrix instances. </para>
	/// <para> If the two operands are invalid for standard Matrix multiplication, `type` will be `void`. </para>
	/// </summary>
	template<EmuConcepts::EmuFastMatrix Lhs_, EmuConcepts::EmuFastMatrix Rhs_>
	struct fast_matrix_multiply_result
	{
	private:
		static constexpr inline auto _type_finder()
		{
			if constexpr (EmuConcepts::EmuFastMatrixMultPair<Lhs_, Rhs_>)
			{
				using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<Lhs_>::type;
				using _rhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
				return EmuMath::FastMatrix
				<
					_rhs_fast_mat_uq::num_columns,
					_lhs_fast_mat_uq::num_rows,
					typename _lhs_fast_mat_uq::value_type,
					_lhs_fast_mat_uq::is_column_major,
					_lhs_fast_mat_uq::register_width
				>();
			}
		}

	public:
		using type = decltype(_type_finder());
	};
	template<EmuConcepts::EmuFastMatrix Lhs_, EmuConcepts::EmuFastMatrix Rhs_>
	using fast_matrix_multiply_result_t = typename fast_matrix_multiply_result<Lhs_, Rhs_>::type;

	template<EmuConcepts::EmuFastMatrix FastMatrix_, bool ColumnMajor_ = EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::is_column_major>
	struct fast_matrix_transpose_result
	{
	private:
		using _in_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;

	public:
		using type = EmuMath::FastMatrix
		<
			_in_fast_mat_uq::num_rows,
			_in_fast_mat_uq::num_columns,
			typename _in_fast_mat_uq::value_type,
			ColumnMajor_,
			_in_fast_mat_uq::register_width
		>;
	};
}

#endif
