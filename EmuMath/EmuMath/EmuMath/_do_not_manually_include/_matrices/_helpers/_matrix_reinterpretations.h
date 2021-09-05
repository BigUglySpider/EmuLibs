#ifndef EMU_MATH_MATRIX_HELPERS_REINTERPRETATIONS_H_INC_
#define EMU_MATH_MATRIX_HELPERS_REINTERPRETATIONS_H_INC_ 1

#include "_common_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
// These reinterpretations are specifically those related to matrices, that would only act as pointless noise if included without matrices.
#pragma region VECTOR_REINTERPRETATIONS
	/// <summary>
	/// <para> Converts the passed EmuMath vector to an EmuMath matrix as though it represents a single column. </para>
	/// <para>
	///		The vector data will be stored as columns regardless of the ColumnMajor_ argument. 
	///		To store the vector as a row matrix instead, use VectorToRowMatrix.
	/// </para>
	/// </summary>
	/// <typeparam name="Vector_">Type of EmuMath vector to convert to a column matrix.</typeparam>
	/// <typeparam name="out_contained_type">Type to be contained within the output matrix.</typeparam>
	/// <param name="vector_">EmuMath vector to convert to a column matrix.</param>
	/// <returns>Column matrix containing a copy of the passed vector's data. The matrix will be a single column which contains the full data of the passed vector.</returns>
	template<typename out_contained_type, bool ColumnMajor_ = true, class Vector_>
	constexpr inline EmuMath::Matrix<1, Vector_::size, out_contained_type, ColumnMajor_> VectorToColumnMatrix(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return _underlying_matrix_funcs::_vector_to_matrix<Vector_, EmuMath::Matrix<1, Vector_::size, out_contained_type, ColumnMajor_>>
			(
				vector_
			);
		}
		else
		{
			static_assert(false, "Attempted to convert a vector to a column matrix, but the provided argument was not an EmuMath vector.");
		}
	}
	template<bool ColumnMajor_ = true, class Vector_>
	constexpr inline EmuMath::Matrix<1, Vector_::size, typename Vector_::value_type, ColumnMajor_> VectorToColumnMatrix(const Vector_& vector_)
	{
		return VectorToColumnMatrix<typename Vector_::value_type, ColumnMajor_, Vector_>(vector_);
	}

	/// <summary>
	/// <para> Converts the passed EmuMath vector to an EmuMath matrix as though it represents a single row. </para>
	/// <para>
	///		The vector data will be stored as rows regardless of the ColumnMajor_ argument. 
	///		To store the vector as a column matrix instead, use VectorToColumnMatrix.
	/// </para>
	/// </summary>
	/// <typeparam name="Vector_">Type of EmuMath vector to convert to a row matrix.</typeparam>
	/// <typeparam name="out_contained_type">Type to be contained within the output matrix.</typeparam>
	/// <param name="vector_">EmuMath vector to convert to a row matrix.</param>
	/// <returns>Row matrix containing a copy of the passed vector's data. The matrix will be a single row which contains the full data of the passed vector.</returns>
	template<typename out_contained_type, bool ColumnMajor_ = true, class Vector_>
	constexpr inline EmuMath::Matrix<Vector_::size, 1, out_contained_type, ColumnMajor_> VectorToRowMatrix(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return _underlying_matrix_funcs::_vector_to_matrix<Vector_, EmuMath::Matrix<Vector_::size, 1, out_contained_type, ColumnMajor_>>
			(
				vector_
			);
		}
		else
		{
			static_assert(false, "Attempted to convert a vector to a row matrix, but the provided argument was not an EmuMath vector.");
		}
	}
	template<bool ColumnMajor_ = true, class Vector_>
	constexpr inline EmuMath::Matrix<Vector_::size, 1, typename Vector_::value_type, ColumnMajor_> VectorToRowMatrix(const Vector_& vector_)
	{
		return VectorToRowMatrix<typename Vector_::value_type, ColumnMajor_, Vector_>(vector_);
	}

	/// <summary>
	/// <para> Creates an EmuMath vector one item larger than the passed vector, containing a copy of the passed vector_ in existing indices and 1 in the new index. </para>
	/// <para> This process allows an X-dimensional vector to be transformed by an (X+1)x(X+1) transformation matrix. </para>
	/// <para> Note that if the vector's dimension is equal to the square transformation matrix's dimension (e.g. 4D vector and 4x4 matrix), this is not required. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the output vector.</typeparam>
	/// <typeparam name="Vector_">Type of EmuMath vector to prepare for transformation.</typeparam>
	/// <param name="vector_">EmuMath vector to prepare for transformation.</param>
	/// <returns>Copy of the provided vector_, with one additional element appended to the end set to 1.</returns>
	template<typename out_contained_type, class Vector_>
	constexpr inline EmuMath::Vector<Vector_::size + 1, out_contained_type> VectorPrepareToTransform(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			EmuMath::Vector<Vector_::size + 1, out_contained_type> out_(vector_);
			out_.at<Vector_::size>() = out_contained_type(1.0);
			return out_;
		}
		else
		{
			static_assert(false, "Attempted to prepare a vector to be transformed by a matrix, but the provided argument was not an EmuMath vector.");
		}
	}
	template<class Vector_>
	constexpr inline EmuMath::Vector<Vector_::size + 1, typename Vector_::value_type> VectorPrepareToTransform(const Vector_& vector_)
	{
		return VectorPrepareToTransform<typename Vector_::value_type, Vector_>(vector_);
	}
#pragma endregion
}

#endif
