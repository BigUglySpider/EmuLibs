#ifndef EMU_MATH_FUNCTORS_MATRIX_ARITHMETIC_H_INC_
#define EMU_MATH_FUNCTORS_MATRIX_ARITHMETIC_H_INC_ 1

#include "../_helpers/_matrix_arithmetic.h"
#include "../../../../EmuCore/Functors/Arithmetic.h"

namespace EmuCore
{
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_, class Rhs_>
	struct do_add<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>, Rhs_>
	{
		constexpr do_add()
		{
		}
		constexpr inline auto operator()(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& lhs_, const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixAdd(lhs_, rhs_);
		}
	};

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_, class Rhs_>
	struct do_subtract<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>, Rhs_>
	{
		constexpr do_subtract()
		{
		}
		constexpr inline auto operator()(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& lhs_, const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixSubtract(lhs_, rhs_);
		}
	};

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_, class Rhs_>
	struct do_multiply<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>, Rhs_>
	{
		constexpr do_multiply()
		{
		}
		constexpr inline auto operator()(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& lhs_, const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixMultiply(lhs_, rhs_);
		}
	};

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_, class Rhs_>
	struct do_divide<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>, Rhs_>
	{
		constexpr do_divide()
		{
		}
		constexpr inline auto operator()(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& lhs_, const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixDivideBasic(lhs_, rhs_);
		}
	};

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_, class Rhs_>
	struct do_mod<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>, Rhs_>
	{
		constexpr do_mod()
		{
		}
		constexpr inline auto operator()(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& lhs_, const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixModBasic(lhs_, rhs_);
		}
	};

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	struct do_negate<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>
	{
		constexpr do_negate()
		{
		}
		constexpr inline auto operator()(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_) const
		{
			return EmuMath::Helpers::MatrixNegate(matrix_);
		}
	};

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	struct do_floor<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>
	{
		constexpr do_floor()
		{
		}
		constexpr inline auto operator()(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_) const
		{
			return EmuMath::Helpers::MatrixFloor(matrix_);
		}
	};

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	struct do_ceil<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>
	{
		constexpr do_ceil()
		{
		}
		constexpr inline auto operator()(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_) const
		{
			return EmuMath::Helpers::MatrixCeil(matrix_);
		}
	};

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	struct do_trunc<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>
	{
		constexpr do_trunc()
		{
		}
		constexpr inline auto operator()(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_) const
		{
			return EmuMath::Helpers::MatrixTrunc(matrix_);
		}
	};

	template<std::size_t NumColumns_, std::size_t NumRows_, typename ContainedT_, bool ColumnMajor_, class B_, class T_>
	struct do_lerp<EmuMath::Matrix<NumColumns_, NumRows_, ContainedT_, ColumnMajor_>, B_, T_>
	{
		constexpr do_lerp()
		{
		}
		constexpr inline auto operator()(const EmuMath::Matrix<NumColumns_, NumRows_, ContainedT_, ColumnMajor_>& a_, const B_& b_, const T_& t_) const
		{
			return EmuMath::Helpers::MatrixLerp(a_, b_, t_);
		}
	};
}

#endif
