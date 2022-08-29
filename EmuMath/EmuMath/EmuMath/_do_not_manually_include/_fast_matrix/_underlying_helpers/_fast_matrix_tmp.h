#ifndef EMU_MATH_FAST_MATRIX_TMP_H_INC_
#define EMU_MATH_FAST_MATRIX_TMP_H_INC_ 1

#include "../../__common/_common_math_tmp.h"
#include "../../../FastVector.h"
#include "../../../Matrix.h"
#include "../../../../EmuCore/TMPHelpers/TypeConvertors.h"
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
}

namespace EmuConcepts
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
		template<bool Valid_>
		struct _type_finder
		{
			using type = void;
		};

		template<>
		struct _type_finder<true>
		{
		private:
			using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<Lhs_>::type;
			using _rhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;

		public:
			using type = EmuMath::FastMatrix
			<
				_rhs_fast_mat_uq::num_columns,
				_lhs_fast_mat_uq::num_rows,
				typename _lhs_fast_mat_uq::value_type,
				_lhs_fast_mat_uq::is_column_major,
				_lhs_fast_mat_uq::register_width
			>;
		};

	public:
		using type = typename _type_finder<EmuConcepts::EmuFastMatrixMultPair<Lhs_, Rhs_>>::type;
	};
	template<EmuConcepts::EmuFastMatrix Lhs_, EmuConcepts::EmuFastMatrix Rhs_>
	using fast_matrix_multiply_result_t = typename fast_matrix_multiply_result<Lhs_, Rhs_>::type;
}

#endif
