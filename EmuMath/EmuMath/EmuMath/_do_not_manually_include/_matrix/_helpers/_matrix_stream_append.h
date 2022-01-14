#ifndef EMU_MATH_MATRIX_STREAM_APPEND_H_INC_
#define EMU_MATH_MATRIX_STREAM_APPEND_H_INC_ 1

#include "_common_matrix_helper_includes.h"
#include <iostream>

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Appends the passed EmuMath Matrix to the provided ostream. </para>
	/// <para> AppendAsRows_: If true, each appended line will be a row; otherwise, each appended line will be a column. </para>
	/// </summary>
	/// <typeparam name="T_"></typeparam>
	/// <param name="str_"></param>
	/// <param name="matrix_"></param>
	/// <returns></returns>
	template<bool AppendAsRows_ = true, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	inline std::ostream& matrix_append_to_stream(std::ostream& str_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_append_to_stream<false, AppendAsRows_>(str_, matrix_);
	}

	template<bool AppendAsRows_ = true, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	inline std::wostream& matrix_append_to_stream(std::wostream& wide_str_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_append_to_stream<true, AppendAsRows_>(wide_str_, matrix_);
	}
}

template<bool AppendAsRows_ = true, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
inline std::ostream& operator<<(std::ostream& str_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
{
	return EmuMath::Helpers::matrix_append_to_stream<AppendAsRows_>(str_, matrix_);
}

template<bool AppendAsRows_ = true, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
inline std::wostream& operator<<(std::wostream& wide_str_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
{
	return EmuMath::Helpers::matrix_append_to_stream<AppendAsRows_>(wide_str_, matrix_);
}

#endif
