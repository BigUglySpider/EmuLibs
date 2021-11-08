#ifndef EMU_MATH_FAST_MATRIX_4X4_H_INC_
#define EMU_MATH_FAST_MATRIX_4X4_H_INC_ 1

#include "../../Matrix.h"
#include "../../../EmuSIMD/SIMDHelpers.h"
#include "../../FastVector.h"

namespace EmuMath
{
	/// <summary> 4x4 matrix of floating points which makes use of SIMD intrinsics. Uses column-major storage. </summary>
	struct FastMatrix4x4f_CM
	{
	public:
#pragma region CONSTRUCTORS
		/// <summary> Creates a 4x4 column-major matrix with default-constructed registers. </summary>
		FastMatrix4x4f_CM() : column0(), column1(), column2(), column3()
		{
		}
		/// <summary> Creates a 4x4 column-major matrix which has columns matching the respective input registers. </summary>
		/// <param name="column_0_">Register to copy to this matrix's 0th column.</param>
		/// <param name="column_1_">Register to copy to this matrix's 1st column.</param>
		/// <param name="column_2_">Register to copy to this matrix's 2nd column.</param>
		/// <param name="column_3_">Register to copy to this matrix's 3rd column.</param>
		FastMatrix4x4f_CM(__m128 column_0_, __m128 column_1_, __m128 column_2_, __m128 column_3_) :
			column0(column_0_),
			column1(column_1_),
			column2(column_2_),
			column3(column_3_)
		{
		}
		/// <summary> Creates a 4x4 column-major matrix which copies the respective columns of the passed matrix. </summary>
		/// <param name="to_copy_">Matrix to copy the columns of.</param>
		FastMatrix4x4f_CM(const FastMatrix4x4f_CM& to_copy_) :
			column0(to_copy_.column0),
			column1(to_copy_.column1),
			column2(to_copy_.column2),
			column3(to_copy_.column3)
		{
		}
		/// <summary>
		/// <para> Creates a 4x4 column-major matrix which loads the passed pointed-to floats directly into their respective column registers. </para>
		/// <para> Behaviour is undefined if any of the passed pointers are not contiguous for at least 4 floats. </para>
		/// </summary>
		/// <param name="p_column_0_contiguous_4_floats_">Pointer to 4 contiguous floats to load into this matrix's 0th column.</param>
		/// <param name="p_column_1_contiguous_4_floats_">Pointer to 4 contiguous floats to load into this matrix's 1st column.</param>
		/// <param name="p_column_2_contiguous_4_floats_">Pointer to 4 contiguous floats to load into this matrix's 2nd column.</param>
		/// <param name="p_column_3_contiguous_4_floats_">Pointer to 4 contiguous floats to load into this matrix's 3rd column.</param>
		FastMatrix4x4f_CM
		(
			const float* p_column_0_contiguous_4_floats_,
			const float* p_column_1_contiguous_4_floats_,
			const float* p_column_2_contiguous_4_floats_,
			const float* p_column_3_contiguous_4_floats_
		) :
			column0(_mm_load_ps(p_column_0_contiguous_4_floats_)),
			column1(_mm_load_ps(p_column_1_contiguous_4_floats_)),
			column2(_mm_load_ps(p_column_2_contiguous_4_floats_)),
			column3(_mm_load_ps(p_column_3_contiguous_4_floats_))
		{
		}
		/// <summary>
		/// <para>
		///		Creates a 4x4 column-major matrix which loads the pointed-to floats directly into its registers contiguously,
		///		where 4 sequential floats represent one column.
		/// </para>
		/// <para> Behaviour is undefined if the passed pointer is not contiguous for at least 16 floats. </para>
		/// </summary>
		/// <param name="p_16_contiguous_floats">Pointer to 16 contiguous floats to load into this matrix's data, starting from the 0th column.</param>
		explicit FastMatrix4x4f_CM(const float* p_16_contiguous_floats) :
			column0(_mm_load_ps(p_16_contiguous_floats)),
			column1(_mm_load_ps(p_16_contiguous_floats + 4)),
			column2(_mm_load_ps(p_16_contiguous_floats + 8)),
			column3(_mm_load_ps(p_16_contiguous_floats + 12))
		{
		}
		/// <summary> Creates a 4x4 column-major matrix from the theoretical data of the passed EmuMath matrix. </summary>
		/// <typeparam name="in_contained_type">Type contained within the provided matrix. Must be convertible to a float.</typeparam>
		/// <param name="to_copy_">EmuMath matrix to copy into this matrix's column registers.</param>
		template
		<
			typename std::size_t InColumns_,
			std::size_t InRows_,
			typename in_contained_type,
			bool InColumnMajor_,
			typename RequiresInContainedTypeCastableToFloat = std::enable_if_t<std::is_convertible_v<in_contained_type, float>>
		>
		explicit FastMatrix4x4f_CM(const EmuMath::Matrix<InColumns_, InRows_, in_contained_type, InColumnMajor_>& to_copy_) :
			column0
			(
				_mm_set_ps
				(
					EmuMath::Helpers::MatrixGetTheoretical<0, 3>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<0, 2>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<0, 1>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<0, 0>(to_copy_)
				)
			),
			column1
			(
				_mm_set_ps
				(
					EmuMath::Helpers::MatrixGetTheoretical<1, 3>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<1, 2>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<1, 1>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<1, 0>(to_copy_)
				)
			),
			column2
			(
				_mm_set_ps
				(
					EmuMath::Helpers::MatrixGetTheoretical<2, 3>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<2, 2>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<2, 1>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<2, 0>(to_copy_)
				)
			),
			column3
			(
				_mm_set_ps
				(
					EmuMath::Helpers::MatrixGetTheoretical<3, 3>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<3, 2>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<3, 1>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<3, 0>(to_copy_)
				)
			)
		{
		}
		/// <summary> Creates a 4x4 column-major matrix from the data of the passed 4x4 column-major EmuMath matrix, loading its data directly into column registers. </summary>
		/// <param name="to_load_">4x4 column-major EmuMath matrix containing floats to load the data of.</param>
		template<>
		explicit FastMatrix4x4f_CM(const EmuMath::Matrix<4, 4, float, true>& to_load_) :
			column0(_mm_load_ps(to_load_.at<0>().data())),
			column1(_mm_load_ps(to_load_.at<1>().data())),
			column2(_mm_load_ps(to_load_.at<2>().data())),
			column3(_mm_load_ps(to_load_.at<3>().data()))
		{
		}
		/// <summary> Creates a 4x4 column-major matrix using EmuMath vectors to create each respective column's data. </summary>
		/// <typeparam name="contained_type_0">Type contained in the vector used to create column 0.</typeparam>
		/// <typeparam name="contained_type_1">Type contained in the vector used to create column 1.</typeparam>
		/// <typeparam name="contained_type_2">Type contained in the vector used to create column 2.</typeparam>
		/// <typeparam name="contained_type_3">Type contained in the vector used to create column 3.</typeparam>
		/// <param name="column_0_">EmuMath vector used to create this matrix's 0th column.</param>
		/// <param name="column_1_">EmuMath vector used to create this matrix's 1st column.</param>
		/// <param name="column_2_">EmuMath vector used to create this matrix's 2nd column.</param>
		/// <param name="column_3_">EmuMath vector used to create this matrix's 3rd column.</param>
		template
		<
			std::size_t Size0_, typename contained_type_0,
			std::size_t Size1_, typename contained_type_1,
			std::size_t Size2_, typename contained_type_2,
			std::size_t Size3_, typename contained_type_3
		>
		FastMatrix4x4f_CM
		(
			const EmuMath::Vector<Size0_, contained_type_0>& column_0_,
			const EmuMath::Vector<Size1_, contained_type_1>& column_1_,
			const EmuMath::Vector<Size2_, contained_type_2>& column_2_,
			const EmuMath::Vector<Size3_, contained_type_3>& column_3_
		) : 
			column0(EmuSIMD::m128_from_emu_math_vector(column_0_)),
			column1(EmuSIMD::m128_from_emu_math_vector(column_1_)),
			column2(EmuSIMD::m128_from_emu_math_vector(column_2_)),
			column3(EmuSIMD::m128_from_emu_math_vector(column_3_))
		{
		}
		/// <summary> Creates a 4x4 column-major matrix using the registers of the passed vectors to create each respective column's data. </summary>
		/// <typeparam name="contained_type_0">Type contained in the vector used to create column 0.</typeparam>
		/// <typeparam name="contained_type_1">Type contained in the vector used to create column 1.</typeparam>
		/// <typeparam name="contained_type_2">Type contained in the vector used to create column 2.</typeparam>
		/// <typeparam name="contained_type_3">Type contained in the vector used to create column 3.</typeparam>
		/// <param name="column_0_">Vector used to create this matrix's 0th column.</param>
		/// <param name="column_1_">Vector used to create this matrix's 1st column.</param>
		/// <param name="column_2_">Vector used to create this matrix's 2nd column.</param>
		/// <param name="column_3_">Vector used to create this matrix's 3rd column.</param>
		FastMatrix4x4f_CM
		(
			const EmuMath::FastVector4f& column_0_,
			const EmuMath::FastVector4f& column_1_,
			const EmuMath::FastVector4f& column_2_,
			const EmuMath::FastVector4f& column_3_
		) :
			column0(column_0_.data_),
			column1(column_1_.data_),
			column2(column_2_.data_),
			column3(column_3_.data_)
		{
		}
		/// <summary>
		///		Creates a 4x4 column-major matrix using the passed data as contiguous initialisation values for its columns.
		///		Arguments are taken in column-major order.
		/// </summary>
		/// <typeparam name="C0R0_">Type used to provide this matrix's 0th column's 0th element.</typeparam>
		/// <typeparam name="C0R1_">Type used to provide this matrix's 0th column's 1st element.</typeparam>
		/// <typeparam name="C0R2_">Type used to provide this matrix's 0th column's 2nd element.</typeparam>
		/// <typeparam name="C0R3_">Type used to provide this matrix's 0th column's 3rd element.</typeparam>
		/// <typeparam name="C1R0_">Type used to provide this matrix's 1st column's 0th element.</typeparam>
		/// <typeparam name="C1R1_">Type used to provide this matrix's 1st column's 1st element.</typeparam>
		/// <typeparam name="C1R2_">Type used to provide this matrix's 1st column's 2nd element.</typeparam>
		/// <typeparam name="C1R3_">Type used to provide this matrix's 1st column's 3rd element.</typeparam>
		/// <typeparam name="C2R0_">Type used to provide this matrix's 2nd column's 0th element.</typeparam>
		/// <typeparam name="C2R1_">Type used to provide this matrix's 2nd column's 1st element.</typeparam>
		/// <typeparam name="C2R2_">Type used to provide this matrix's 2nd column's 2nd element.</typeparam>
		/// <typeparam name="C2R3_">Type used to provide this matrix's 2nd column's 3rd element.</typeparam>
		/// <typeparam name="C3R0_">Type used to provide this matrix's 3rd column's 0th element.</typeparam>
		/// <typeparam name="C3R1_">Type used to provide this matrix's 3rd column's 1st element.</typeparam>
		/// <typeparam name="C3R2_">Type used to provide this matrix's 3rd column's 2nd element.</typeparam>
		/// <typeparam name="C3R3_">Type used to provide this matrix's 3rd column's 3rd element.</typeparam>
		/// <param name="c0r0_">Value used to initialise this matrix's 0th column's 0th element.</param>
		/// <param name="c0r1_">Value used to initialise this matrix's 0th column's 1st element.</param>
		/// <param name="c0r2_">Value used to initialise this matrix's 0th column's 2nd element.</param>
		/// <param name="c0r3_">Value used to initialise this matrix's 0th column's 3rd element.</param>
		/// <param name="c1r0_">Value used to initialise this matrix's 1st column's 0th element.</param>
		/// <param name="c1r1_">Value used to initialise this matrix's 1st column's 1st element.</param>
		/// <param name="c1r2_">Value used to initialise this matrix's 1st column's 2nd element.</param>
		/// <param name="c1r3_">Value used to initialise this matrix's 1st column's 3rd element.</param>
		/// <param name="c2r0_">Value used to initialise this matrix's 2nd column's 0th element.</param>
		/// <param name="c2r1_">Value used to initialise this matrix's 2nd column's 1st element.</param>
		/// <param name="c2r2_">Value used to initialise this matrix's 2nd column's 2nd element.</param>
		/// <param name="c2r3_">Value used to initialise this matrix's 2nd column's 3rd element.</param>
		/// <param name="c3r0_">Value used to initialise this matrix's 3rd column's 0th element.</param>
		/// <param name="c3r1_">Value used to initialise this matrix's 3rd column's 1st element.</param>
		/// <param name="c3r2_">Value used to initialise this matrix's 3rd column's 2nd element.</param>
		/// <param name="c3r3_">Value used to initialise this matrix's 3rd column's 3rd element.</param>
		template
		<
			typename C0R0_, typename C0R1_, typename C0R2_, typename C0R3_,
			typename C1R0_, typename C1R1_, typename C1R2_, typename C1R3_,
			typename C2R0_, typename C2R1_, typename C2R2_, typename C2R3_,
			typename C3R0_, typename C3R1_, typename C3R2_, typename C3R3_
		>
		FastMatrix4x4f_CM
		(
			const C0R0_& c0r0_, const C0R1_& c0r1_, const C0R2_& c0r2_, const C0R3_& c0r3_,
			const C1R0_& c1r0_, const C1R1_& c1r1_, const C1R2_& c1r2_, const C1R3_& c1r3_,
			const C2R0_& c2r0_, const C2R1_& c2r1_, const C2R2_& c2r2_, const C2R3_& c2r3_,
			const C3R0_& c3r0_, const C3R1_& c3r1_, const C3R2_& c3r2_, const C3R3_& c3r3_
		) :
			column0(_mm_set_ps(static_cast<float>(c0r3_), static_cast<float>(c0r2_), static_cast<float>(c0r1_), static_cast<float>(c0r0_))),
			column1(_mm_set_ps(static_cast<float>(c1r3_), static_cast<float>(c1r2_), static_cast<float>(c1r1_), static_cast<float>(c1r0_))),
			column2(_mm_set_ps(static_cast<float>(c2r3_), static_cast<float>(c2r2_), static_cast<float>(c2r1_), static_cast<float>(c2r0_))),
			column3(_mm_set_ps(static_cast<float>(c3r3_), static_cast<float>(c3r2_), static_cast<float>(c3r1_), static_cast<float>(c3r0_)))
		{
		}
#pragma endregion

#pragma region EXTRACTION
		/// <summary> Returns a copy of the value at the provided column and row index. </summary>
		/// <returns>Copy of the element at the provided column and row index.</returns>
		template<std::size_t ColumnIndex_, std::size_t RowIndex_, typename Out_ = float>
		[[nodiscard]] inline Out_ at() const
		{
			if constexpr (_assert_valid_index<ColumnIndex_, RowIndex_>())
			{
				if constexpr (_assert_valid_cast_to<Out_>())
				{
					return EmuSIMD::get_index<RowIndex_, Out_>(GetColumn<ColumnIndex_>());
				}
				else
				{
					static_assert(false, "Invalid Out_ type provided to EmuMath::FastMatrix4x4f_CM::at.");
				}
			}
			else
			{
				static_assert(false, "Invalid indices provided to EmuMath::FastMatrix4x4f_CM::at<ColumnIndex_, RowIndex_>.");
			}
		}
		/// <summary> Returns a copy of the major register at the provided major index. </summary>
		/// <returns>Register copy of the major register at the provided major index.</returns>
		template<std::size_t MajorIndex_>
		[[nodiscard]] inline __m128 at() const
		{
			if constexpr (_assert_valid_major_index<MajorIndex_>())
			{
				return GetColumn<MajorIndex_>();
			}
			else
			{
				static_assert(false, "Invalid Major Index provided to EmuMath::FastMatrix4x4f_CM::at<MajorIndex_>.");
			}
		}

		/// <summary>
		///	<para> Stores this matrix as an easily-readable 4x4 EmuMath matrix, with customisable contained types and major-order (defaults to the same as this matrix). </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output EmuMath matrix.</typeparam>
		/// <param name="out_">4x4 EmuMath matrix to output to. This may be omitted to return a value, but it is recommended to pass a matrix to output to.</param>
		/// <returns>4x4 EmuMath matrix that may be easily read</returns>
		template<typename out_contained_type = float, bool OutColumnMajor_ = true>
		[[nodiscard]] inline void Store(EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>& out_) const
		{
			if constexpr (std::is_same_v<out_contained_type, float> && OutColumnMajor_)
			{
				// Load data straight into output matrix since we can easily do so knowing major-order and type match.
				_mm_store_ps(out_.at<0>().data(), column0);
				_mm_store_ps(out_.at<1>().data(), column1);
				_mm_store_ps(out_.at<2>().data(), column2);
				_mm_store_ps(out_.at<3>().data(), column3);
			}
			else
			{
				if constexpr (_assert_valid_cast_to<out_contained_type>())
				{
					if constexpr (OutColumnMajor_)
					{
						// Copy each individual column into the output matrix, deferring conversions of one vector to another to EmuMath::Vector using readable columns.
						out_.at<0>() = GetColumnReadable<0>();
						out_.at<1>() = GetColumnReadable<1>();
						out_.at<2>() = GetColumnReadable<2>();
						out_.at<3>() = GetColumnReadable<3>();
					}
					else
					{
						// Same as above, but uses this matrix's transpose as we need to be feeding rows into major elements to produce the same matrix.
						// --- Using transpose columns instead of GetRowReadable allows us to avoid some unneeded shuffles
						// ------ Additionally, allows an optimised store if the output matrix contains floats
						FastMatrix4x4f_CM transpose_ = Transpose();
						if constexpr (std::is_same_v<float, out_contained_type>)
						{
							_mm_store_ps(out_.at<0>().data(), transpose_.column0);
							_mm_store_ps(out_.at<1>().data(), transpose_.column1);
							_mm_store_ps(out_.at<2>().data(), transpose_.column2);
							_mm_store_ps(out_.at<3>().data(), transpose_.column3);
						}
						else
						{
							out_.at<0>() = transpose_.GetColumnReadable<0>();
							out_.at<1>() = transpose_.GetColumnReadable<1>();
							out_.at<2>() = transpose_.GetColumnReadable<2>();
							out_.at<3>() = transpose_.GetColumnReadable<3>();
						}
					}
				}
				else
				{
					static_assert(false, "Invalid out_contained_type provided to EmuMath::FastMatrix4x4f_CM::Store.");
				}
			}
		}
		template<typename out_contained_type = float, bool OutColumnMajor_ = true>
		[[nodiscard]] inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> Store() const
		{
			EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> out_;
			Store(out_);
			return out_;
		}

		/// <summary> Provides a 128-bit register copy of the column at the specified index. </summary>
		/// <returns>128-bit float register copy of the requested column within this matrix.</returns>
		template<std::size_t Column_>
		[[nodiscard]] inline __m128 GetColumn() const
		{
			if constexpr (Column_ == 0)
			{
				return column0;
			}
			else if constexpr (Column_ == 1)
			{
				return column1;
			}
			else if constexpr (Column_ == 2)
			{
				return column2;
			}
			else if constexpr (Column_ == 3)
			{
				return column3;
			}
			else
			{
				static_assert(false, "Attempted to get a column with an invalid index from an EmuMath::FastMatrix4x4f_CM.");
			}
		}
		/// <summary> Provides an easily-readable EmuMath vector representing the column at the provided index. </summary>
		/// <returns>EmuMath vector representing the requested column within this matrix.</returns>
		template<std::size_t Column_>
		[[nodiscard]] inline EmuMath::Vector<4, float> GetColumnReadable() const
		{
			EmuMath::Vector<4, float> out_;
			_mm_store_ps(out_.data(), GetColumn<Column_>());
			return out_;
		}

		/// <summary> Provides a 128-bit register copy of the row at the specified index. As this matrix is column-major, this will require several shuffles. </summary>
		/// <returns>128-bit float register copy of the requested row within this matrix.</returns>
		template<std::size_t Row_>
		[[nodiscard]] inline __m128 GetRow() const
		{
			if constexpr (Row_ <= 3)
			{
				__m128 out_0_1 = EmuSIMD::shuffle<Row_, 0, Row_, 0>(column0, column1);
				__m128 out_2_3 = EmuSIMD::shuffle<Row_, 0, Row_, 0>(column2, column3);
				return EmuSIMD::shuffle<0, 2, 0, 2>(out_0_1, out_2_3);
			}
			else
			{
				static_assert(false, "Attempted to get a column with an invalid index from an EmuMath::FastMatrix4x4f_CM.");
			}
		}
		/// <summary>
		///		Provides an easily-readable EmuMath vector representing the row at the provided index. 
		///		As this matrix is column-major, this will require several shuffles.
		/// </summary>
		/// <returns>EmuMath vector representing the requested row within this matrix.</returns>
		template<std::size_t Row_>
		[[nodiscard]] inline EmuMath::Vector<4, float> GetRowReadable() const
		{
			EmuMath::Vector<4, float> out_;
			_mm_store_ps(out_.data(), GetRow<Row_>());
			return out_;
		}
#pragma endregion

#pragma region ARITHMETIC_FUNCS
		/// <summary>
		/// <para> Performs an addition operation between this matrix's columns and the provided column registers. </para>
		/// <para> The provided column registers are treated as the respective columns of a matrix. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Column 0 of a matrix to add to this matrix.</param>
		/// <param name="rhs_column_1_">Column 1 of a matrix to add to this matrix.</param>
		/// <param name="rhs_column_2_">Column 2 of a matrix to add to this matrix.</param>
		/// <param name="rhs_column_3_">Column 3 of a matrix to add to this matrix.</param>
		/// <returns>Matrix containing the results of addition.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Add(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_add_ps(column0, rhs_column_0_),
				_mm_add_ps(column1, rhs_column_1_),
				_mm_add_ps(column2, rhs_column_2_),
				_mm_add_ps(column3, rhs_column_3_)
			);
		}
		/// <summary> Adds the passed matrix to this matrix. </summary>
		/// <param name="rhs_">Matrix to add to this matrix.</param>
		/// <returns>Matrix containing the results of addition.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Add(const FastMatrix4x4f_CM& rhs_) const
		{
			return Add(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}

		/// <summary>
		/// <para> Performs a subtraction operation between this matrix's columns and the provided column registers. </para>
		/// <para> The provided column registers are treated as the respective columns of a matrix. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Column 0 of a matrix to subtract from this matrix.</param>
		/// <param name="rhs_column_1_">Column 1 of a matrix to subtract from this matrix.</param>
		/// <param name="rhs_column_2_">Column 2 of a matrix to subtract from this matrix.</param>
		/// <param name="rhs_column_3_">Column 3 of a matrix to subtract from this matrix.</param>
		/// <returns>Matrix containing the results of subtraction.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Subtract(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_sub_ps(column0, rhs_column_0_),
				_mm_sub_ps(column1, rhs_column_1_),
				_mm_sub_ps(column2, rhs_column_2_),
				_mm_sub_ps(column3, rhs_column_3_)
			);
		}
		/// <summary> Subtracts the passed matrix from this matrix. </summary>
		/// <param name="rhs_">Matrix to subtract from this matrix.</param>
		/// <returns>Matrix containing the results of subtraction.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Subtract(const FastMatrix4x4f_CM& rhs_) const
		{
			return Subtract(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}

		/// <summary>
		/// <para> Performs a basic multiplication where respective columns in this matrix are multiplied by the passed column registers. </para>
		/// <para> This is not a standard matrix multiplication. For such behaviour, use Multiply instead. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to multiply this matrix's column0 by.</param>
		/// <param name="rhs_column_1_">Register to multiply this matrix's column1 by.</param>
		/// <param name="rhs_column_2_">Register to multiply this matrix's column2 by.</param>
		/// <param name="rhs_column_3_">Register to multiply this matrix's column3 by.</param>
		/// <returns>Resulting matrix after this matrix's columns are multiplied by the respective passed column registers.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM MultiplyBasic(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_mul_ps(column0, rhs_column_0_),
				_mm_mul_ps(column1, rhs_column_1_),
				_mm_mul_ps(column2, rhs_column_2_),
				_mm_mul_ps(column3, rhs_column_3_)
			);
		}
		/// <summary> Multiplies all columns in this matrix by the passed register. Useful for providing a blanket multiplication to each element on certain rows. </summary>
		/// <param name="mult_for_all_columns_">Register to multiply every column of this matrix via.</param>
		/// <returns>Resulting matrix after this matrix's columns are all multiplied by the passed register.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM MultiplyBasic(__m128 mult_for_all_columns_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_mul_ps(column0, mult_for_all_columns_),
				_mm_mul_ps(column1, mult_for_all_columns_),
				_mm_mul_ps(column2, mult_for_all_columns_),
				_mm_mul_ps(column3, mult_for_all_columns_)
			);
		}
		/// <summary>
		/// <para> Performs a basic multiplication where respective columns in this matrix are multiplied by those in the passed matrix. </para>
		/// <para> This is not a standard matrix multiplication. For such behaviour, use Multiply instead. </para>
		/// </summary>
		/// <param name="rhs_">Matrix to multiply respective columns of this matrix by.</param>
		/// <returns>Resulting matrix after this matrix's columns are multiplied by the respective columns of the passed matrix.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM MultiplyBasic(const FastMatrix4x4f_CM& rhs_) const
		{
			return MultiplyBasic(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary> Multiplies all elements within this matrix by the provided val_. The provided val_ must be castable to a float. </summary>
		/// <typeparam name="T_">Type to multiply by.</typeparam>
		/// <param name="val_">Value to multiply all elements of this matrix by.</param>
		/// <returns>Resulting matrix after multiply all of this matrix's elements by the passed val_.</returns>
		template<typename T_, typename RequiresTConvertibleToFloat = std::enable_if_t<std::is_convertible_v<T_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM MultiplyBasic(const T_& val_) const
		{
			return MultiplyBasic(_mm_set1_ps(static_cast<float>(val_)));
		}

		/// <summary>
		/// <para> Performs a standard matrix multiplication with the provided registers, which are interpreted as respective columns within a 4x4 matrix. </para>
		/// <para> This is a standard matrix multiplication. To perform a basic multiplication of respective columns, use MultiplyBasic. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Column 0 of the matrix to multiply this matrix by.</param>
		/// <param name="rhs_column_1_">Column 1 of the matrix to multiply this matrix by.</param>
		/// <param name="rhs_column_2_">Column 2 of the matrix to multiply this matrix by.</param>
		/// <param name="rhs_column_3_">Column 3 of the matrix to multiply this matrix by.</param>
		/// <returns>Matrix result from multiplying this matrix by a matrix comprised of respective passed columns.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Multiply(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			return FastMatrix4x4f_CM
			(
				_std_mult_calculate_column(rhs_column_0_),
				_std_mult_calculate_column(rhs_column_1_),
				_std_mult_calculate_column(rhs_column_2_),
				_std_mult_calculate_column(rhs_column_3_)
			);
		}

		/// <summary> Multiplies the passed rhs_vector_ register with this matrix, treating it as a single column matrix. </summary>
		/// <param name="rhs_vector_">Vector to multiply. Used as-is.</param>
		/// <returns>Resulting vector from multiplying the passed vector by this matrix, interpreted as defined above.</returns>
		[[nodiscard]] inline EmuMath::FastVector4f MultiplyVector4(__m128 rhs_vector_) const
		{
			return FastVector4f(_std_mult_calculate_column(rhs_vector_));
		}
		[[nodiscard]] inline EmuMath::FastVector4f MultiplyVector4(const EmuMath::FastVector4f& rhs_vector_) const
		{
			return MultiplyVector4(rhs_vector_.data_);
		}
		/// <summary>
		/// <para> Multiplies the passed rhs_vector_ register with this matrix, treating it as a single column matrix. </para>
		/// <para> The rhs_vector_ is assumed to have a w value of 1, as per homogeneous coordinates. </para>
		/// </summary>
		/// <param name="rhs_vector_">Vector to multiply. The x, y, and z values of this vector will be used, and w will be interpreted as 1.</param>
		/// <returns>Resulting vector from multiplying the passed vector by this matrix, interpreted as defined above.</returns>
		[[nodiscard]] inline EmuMath::FastVector4f MultiplyVector3(__m128 rhs_vector_) const
		{
			__m128 out_ = _mm_mul_ps(column0, EmuSIMD::shuffle<0, 0, 0, 0>(rhs_vector_));
			out_ = _mm_add_ps(out_, _mm_mul_ps(column1, EmuSIMD::shuffle<1, 1, 1, 1>(rhs_vector_)));
			out_ = _mm_add_ps(out_, _mm_mul_ps(column2, EmuSIMD::shuffle<2, 2, 2, 2>(rhs_vector_)));

			// Add column3 to end result as we interpret the missing value to be 1 as per homogeneous coordinates default to
			return FastVector4f(_mm_add_ps(out_, column3));
		}
		[[nodiscard]] inline EmuMath::FastVector4f MultiplyVector3(const EmuMath::FastVector4f& rhs_vector_) const
		{
			return MultiplyVector3(rhs_vector_.data_);
		}
		/// <summary>
		/// <para> Multiplies the passed rhs_vector_ register with this matrix, treating it as a single column matrix. </para>
		/// <para> The rhs_vector_ is assumed to have a z value of 0, as 2D space can be considered to have an implicit Z-coordinate of 0. </para>
		/// <para> The rhs_vector_ is assumed to have a w value of 1, as per homogeneous coordinates. </para>
		/// </summary>
		/// <param name="rhs_vector_">Vector to multiply. The x and y values of this vector will be used, z will be interpreted as 0, and w will be interpreted as 1.</param>
		/// <returns>Resulting vector from multiplying the passed vector by this matrix, interpreted as defined above. The output z will always be 0.</returns>
		[[nodiscard]] inline EmuMath::FastVector4f MultiplyVector2(__m128 rhs_vector_) const
		{
			// Add column3 as we interpret the missing w value to be 1 as per homogeneous coordinates default to, 
			// and z is interpreted to be 0 since 2D space is implicitly at Z 0, so the resulting Z should always be 0.
			__m128 out_ = _mm_mul_ps(column0, EmuSIMD::shuffle<0, 0, 0, 0>(rhs_vector_));
			out_ = _mm_add_ps(out_, _mm_mul_ps(column1, EmuSIMD::shuffle<1, 1, 1, 1>(rhs_vector_)));
			out_ = _mm_add_ps(out_, column3);

			// AND out the z coord to maintain implicit Z 0, and continue to add homogeneous 
			return FastVector4f(_mm_and_ps(EmuSIMD::index_mask_m128<true, true, false, true>(), out_));
		}
		[[nodiscard]] inline EmuMath::FastVector4f MultiplyVector2(const EmuMath::FastVector4f& rhs_vector_) const
		{
			return MultiplyVector2(rhs_vector_.data_);
		}

		/// <summary>
		/// <para> Performs a standard matrix multiplication with the provided rhs_ matrix. </para>
		/// <para> This is a standard matrix multiplication. To perform a basic multiplication of respective columns, use MultiplyBasic. </para>
		/// </summary>
		/// <param name="rhs_">Matrix to multiply this matrix by.</param>
		/// <returns>Matrix result from multiplying this matrix by a matrix comprised of respective passed columns.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Multiply(const FastMatrix4x4f_CM& rhs_) const
		{
			return Multiply(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary>
		/// <para> Multiplies all columns in this matrix by the passed register. Useful for providing a blanket multiplication to each element on certain rows. </para>
		/// <para> This is the same as calling MultiplyBasic with the same argument. </para>
		/// <para> If the register is to be interpreted as a vector, use MultiplyVector. </para>
		/// </summary>
		/// <param name="mult_for_all_columns_">Register to multiply every column of this matrix via.</param>
		/// <returns>Resulting matrix after this matrix's columns are all multiplied by the passed register.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Multiply(__m128 mult_for_all_columns_) const
		{
			return MultiplyBasic(mult_for_all_columns_);
		}
		/// <summary>
		/// <para> Multiplies all elements within this matrix by the provided val_. The provided val_ must be castable to a float. </para>
		/// <para> This is the same as calling MultiplyBasic with the same argument. </para>
		/// </summary>
		/// <typeparam name="T_">Type to multiply by.</typeparam>
		/// <param name="val_">Value to multiply all elements of this matrix by.</param>
		/// <returns>Resulting matrix after multiply all of this matrix's elements by the passed val_.</returns>
		template<typename T_, typename RequiresTConvertibleToFloat = std::enable_if_t<std::is_convertible_v<T_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM Multiply(const T_& val_) const
		{
			return MultiplyBasic<T_>(val_);
		}

		/// <summary>
		/// <para> Performs a basic division where respective columns in this matrix are divided by the passed column registers. </para>
		/// <para> This is not a standard matrix division. Such behaviour is mathematically undefined. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to divide this matrix's column0 by.</param>
		/// <param name="rhs_column_1_">Register to divide this matrix's column1 by.</param>
		/// <param name="rhs_column_2_">Register to divide this matrix's column2 by.</param>
		/// <param name="rhs_column_3_">Register to divide this matrix's column3 by.</param>
		/// <returns>Resulting matrix after this matrix's columns are divided by the respective passed column registers.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM DivideBasic(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_div_ps(column0, rhs_column_0_),
				_mm_div_ps(column1, rhs_column_1_),
				_mm_div_ps(column2, rhs_column_2_),
				_mm_div_ps(column3, rhs_column_3_)
			);
		}
		/// <summary>
		/// <para> Performs a basic division where each column in this matrix is divided via the passed divisor register. </para>
		/// <para> This is not a standard matrix division. Such behaviour is mathematically undefined. </para>
		/// </summary>
		/// <param name="divisor_for_all_columns_">Register to divide each of this matrix's columns by.</param>
		/// <returns>Resulting matrix after this matrix's columns are divided by the passed column register.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM DivideBasic(__m128 divisor_for_all_columns_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_div_ps(column0, divisor_for_all_columns_),
				_mm_div_ps(column1, divisor_for_all_columns_),
				_mm_div_ps(column2, divisor_for_all_columns_),
				_mm_div_ps(column3, divisor_for_all_columns_)
			);
		}
		/// <summary>
		/// <para> Divides each value in this matrix by the respective value in the passed matrix. </para>
		/// <para> This is not a standard matrix division. Such behaviour is mathematically undefined. </para>
		/// </summary>
		/// <param name="rhs_">Matrix to divide each respective value of this matrix by.</param>
		/// <returns>Resulting matrix after this matrix's elements are divided by respective elements in the passed rhs_ matrix.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM DivideBasic(const FastMatrix4x4f_CM& rhs_) const
		{
			return DivideBasic(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary>
		/// <para> Divides each value in this matrix by the passed scalar. </para>
		/// <para> This is not a standard matrix division. Such behaviour is mathematically undefined. </para>
		/// </summary>
		/// <param name="divisor_">Scalar to divide each respective value of this matrix by.</param>
		/// <returns>Resulting matrix after this matrix's elements are divided by the passed scalar divisor_.</returns>
		template<typename T_, typename RequiresTConvertibleToFloat = std::enable_if_t<std::is_convertible_v<T_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM DivideBasic(const T_& divisor_) const
		{
			return DivideBasic(_mm_set1_ps(static_cast<float>(divisor_)));
		}

		/// <summary>
		/// <para> Performs a basic floating-point modulo division where respective columns in this matrix are divided by the passed column registers. </para>
		/// <para> This is not a standard matrix modulo division. Such behaviour is mathematically undefined. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to divide this matrix's column0 by.</param>
		/// <param name="rhs_column_1_">Register to divide this matrix's column1 by.</param>
		/// <param name="rhs_column_2_">Register to divide this matrix's column2 by.</param>
		/// <param name="rhs_column_3_">Register to divide this matrix's column3 by.</param>
		/// <returns>Resulting matrix after floating-point modulo division between this matrix's columns and the respective passed column registers.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM ModBasic(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_fmod_ps(column0, rhs_column_0_),
				_mm_fmod_ps(column1, rhs_column_1_),
				_mm_fmod_ps(column2, rhs_column_2_),
				_mm_fmod_ps(column3, rhs_column_3_)
			);
		}
		/// <summary>
		/// <para> Performs a basic floating-point modulo division where each column in this matrix is divided via the passed divisor register. </para>
		/// <para> This is not a standard matrix modulo division. Such behaviour is mathematically undefined. </para>
		/// </summary>
		/// <param name="divisor_for_all_columns_">Register to divide each of this matrix's columns by.</param>
		/// <returns>Resulting matrix after floating-point modulo division between this matrix's columns and the passed column register.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM ModBasic(__m128 divisor_for_all_columns_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_fmod_ps(column0, divisor_for_all_columns_),
				_mm_fmod_ps(column1, divisor_for_all_columns_),
				_mm_fmod_ps(column2, divisor_for_all_columns_),
				_mm_fmod_ps(column3, divisor_for_all_columns_)
			);
		}
		/// <summary>
		/// <para> Performs a floating-point modulo division on each value in this matrix by the respective value in the passed matrix. </para>
		/// <para> This is not a standard matrix modulo division. Such behaviour is mathematically undefined. </para>
		/// </summary>
		/// <param name="rhs_">Matrix to divide each respective value of this matrix by.</param>
		/// <returns>Resulting matrix after floating-point modulo division between this matrix's and the passed matrix's respective elements.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM ModBasic(const FastMatrix4x4f_CM& rhs_) const
		{
			return ModBasic(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary>
		/// <para> Performs a floating-point modulo division on each value in this matrix by the passed scalar divisor_. </para>
		/// <para> This is not a standard matrix modulo division. Such behaviour is mathematically undefined. </para>
		/// </summary>
		/// <param name="rhs_">Scalar to divide each respective value of this matrix by.</param>
		/// <returns>Resulting matrix after floating-point modulo division between this matrix's elements and the passed scalar divisor_.</returns>
		template<typename T_, typename RequiresTConvertibleToFloat = std::enable_if_t<std::is_convertible_v<T_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM ModBasic(const T_& divisor_) const
		{
			return ModBasic(_mm_set1_ps(static_cast<float>(divisor_)));
		}

		/// <summary> Negates this matrix, setting every element to its negative form (e.g. [0][0] = -[0][0]). </summary>
		/// <returns>Negated form of this matrix.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Negate() const
		{
			__m128 zero_ = _mm_setzero_ps();
			return FastMatrix4x4f_CM
			(
				_mm_sub_ps(zero_, column0),
				_mm_sub_ps(zero_, column1),
				_mm_sub_ps(zero_, column2),
				_mm_sub_ps(zero_, column3)
			);
		}

		/// <summary> Floors all elements in this matrix, rounding them toward negative infinity. </summary>
		/// <returns>Copy of this matrix with all elements rounded toward negative infinity.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Floor() const
		{
			return FastMatrix4x4f_CM
			(
				_mm_round_ps(column0, _MM_FROUND_FLOOR),
				_mm_round_ps(column1, _MM_FROUND_FLOOR),
				_mm_round_ps(column2, _MM_FROUND_FLOOR),
				_mm_round_ps(column3, _MM_FROUND_FLOOR)
			);
		}

		/// <summary> Ceils all elements in this matrix, rounding them toward positive infinity. </summary>
		/// <returns>Copy of this matrix with all elements rounded toward positive infinity.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Ceil() const
		{
			return FastMatrix4x4f_CM
			(
				_mm_round_ps(column0, _MM_FROUND_CEIL),
				_mm_round_ps(column1, _MM_FROUND_CEIL),
				_mm_round_ps(column2, _MM_FROUND_CEIL),
				_mm_round_ps(column3, _MM_FROUND_CEIL)
			);
		}

		/// <summary> Truncates all elements in this matrix, rounding them toward 0. </summary>
		/// <returns>Copy of this matrix with all elements rounded toward 0.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Trunc() const
		{
			return FastMatrix4x4f_CM
			(
				_mm_round_ps(column0, _MM_FROUND_TRUNC),
				_mm_round_ps(column1, _MM_FROUND_TRUNC),
				_mm_round_ps(column2, _MM_FROUND_TRUNC),
				_mm_round_ps(column3, _MM_FROUND_TRUNC)
			);
		}

		[[nodiscard]] inline FastMatrix4x4f_CM Lerp(__m128 b_0_, __m128 b_1_, __m128 b_2_, __m128 b_3_, __m128 t_0_, __m128 t_1_, __m128 t_2_, __m128 t_3_) const
		{
			return FastMatrix4x4f_CM
			(
				EmuSIMD::fused_lerp(column0, b_0_, t_0_),
				EmuSIMD::fused_lerp(column1, b_1_, t_1_),
				EmuSIMD::fused_lerp(column2, b_2_, t_2_),
				EmuSIMD::fused_lerp(column3, b_3_, t_3_)
			);
		}
		[[nodiscard]] inline FastMatrix4x4f_CM Lerp(__m128 b_, __m128 t_) const
		{
			return FastMatrix4x4f_CM
			(
				EmuSIMD::fused_lerp(column0, b_, t_),
				EmuSIMD::fused_lerp(column1, b_, t_),
				EmuSIMD::fused_lerp(column2, b_, t_),
				EmuSIMD::fused_lerp(column3, b_, t_)
			);
		}
		[[nodiscard]] inline FastMatrix4x4f_CM Lerp(const FastMatrix4x4f_CM& b_, __m128 t_) const
		{
			return FastMatrix4x4f_CM
			(
				EmuSIMD::fused_lerp(column0, b_.column0, t_),
				EmuSIMD::fused_lerp(column1, b_.column1, t_),
				EmuSIMD::fused_lerp(column2, b_.column2, t_),
				EmuSIMD::fused_lerp(column3, b_.column3, t_)
			);
		}
		[[nodiscard]] inline FastMatrix4x4f_CM Lerp(__m128 b_, const FastMatrix4x4f_CM& t_) const
		{
			return FastMatrix4x4f_CM
			(
				EmuSIMD::fused_lerp(column0, b_, t_.column0),
				EmuSIMD::fused_lerp(column1, b_, t_.column1),
				EmuSIMD::fused_lerp(column2, b_, t_.column2),
				EmuSIMD::fused_lerp(column3, b_, t_.column3)
			);
		}
		[[nodiscard]] inline FastMatrix4x4f_CM Lerp(const FastMatrix4x4f_CM& b_, const FastMatrix4x4f_CM& t_) const
		{
			return Lerp(b_.column0, b_.column1, b_.column2, b_.column3, t_.column0, t_.column1, t_.column2, t_.column3);
		}
		template<typename B_, typename RequiresBConvertibleToFloat_ = std::enable_if_t<std::is_convertible_v<B_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM Lerp(const B_& b_, __m128 t_) const
		{
			return Lerp(_mm_set1_ps(static_cast<float>(b_)), t_);
		}
		template<typename T_, typename RequiresTConvertibleToFloat_ = std::enable_if_t<std::is_convertible_v<T_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM Lerp(__m128 b_, const T_& t_) const
		{
			return Lerp(b_, _mm_set1_ps(static_cast<float>(t_)));
		}
		template<typename B_, typename RequiresBConvertibleToFloat_ = std::enable_if_t<std::is_convertible_v<B_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM Lerp(const B_& b_, const FastMatrix4x4f_CM& t_) const
		{
			return Lerp(_mm_set1_ps(static_cast<float>(b_)), t_);
		}
		template<typename T_, typename RequiresTConvertibleToFloat_ = std::enable_if_t<std::is_convertible_v<T_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM Lerp(const FastMatrix4x4f_CM& b_, const T_& t_) const
		{
			return Lerp(b_, _mm_set1_ps(static_cast<float>(t_)));
		}
		template<typename B_, typename T_, typename RequiresArgsConvertibleToFloat = std::enable_if_t<std::is_convertible_v<T_, float> && std::is_convertible_v<B_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM Lerp(const B_& b_, const T_& t_) const
		{
			return Lerp(_mm_set1_ps(static_cast<float>(b_)), _mm_set1_ps(static_cast<float>(t_)));
		}






		[[nodiscard]] inline FastMatrix4x4f_CM Clamp(__m128 min_0_, __m128 min_1_, __m128 min_2_, __m128 min_3_, __m128 max_0_, __m128 max_1_, __m128 max_2_, __m128 max_3_) const
		{
			return FastMatrix4x4f_CM
			(
				EmuSIMD::clamp(column0, min_0_, max_0_),
				EmuSIMD::clamp(column1, min_1_, max_1_),
				EmuSIMD::clamp(column2, min_2_, max_2_),
				EmuSIMD::clamp(column3, min_3_, max_3_)
			);
		}
		[[nodiscard]] inline FastMatrix4x4f_CM Clamp(__m128 min_, __m128 max_) const
		{
			return FastMatrix4x4f_CM
			(
				EmuSIMD::clamp(column0, min_, max_),
				EmuSIMD::clamp(column1, min_, max_),
				EmuSIMD::clamp(column2, min_, max_),
				EmuSIMD::clamp(column3, min_, max_)
			);
		}
		[[nodiscard]] inline FastMatrix4x4f_CM Clamp(const FastMatrix4x4f_CM& min_, __m128 max_) const
		{
			return FastMatrix4x4f_CM
			(
				EmuSIMD::clamp(column0, min_.column0, max_),
				EmuSIMD::clamp(column1, min_.column1, max_),
				EmuSIMD::clamp(column2, min_.column2, max_),
				EmuSIMD::clamp(column3, min_.column3, max_)
			);
		}
		[[nodiscard]] inline FastMatrix4x4f_CM Clamp(__m128 min_, const FastMatrix4x4f_CM& max_) const
		{
			return FastMatrix4x4f_CM
			(
				EmuSIMD::clamp(column0, min_, max_.column0),
				EmuSIMD::clamp(column1, min_, max_.column1),
				EmuSIMD::clamp(column2, min_, max_.column2),
				EmuSIMD::clamp(column3, min_, max_.column3)
			);
		}
		[[nodiscard]] inline FastMatrix4x4f_CM Clamp(const FastMatrix4x4f_CM& min_, const FastMatrix4x4f_CM& max_) const
		{
			return Clamp(min_.column0, min_.column1, min_.column2, min_.column3, max_.column0, max_.column1, max_.column2, max_.column3);
		}
		template<typename Min_, typename RequiresMinConvertibleToFloat_ = std::enable_if_t<std::is_convertible_v<Min_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM Clamp(const Min_& min_, __m128 max_) const
		{
			return Clamp(_mm_set1_ps(static_cast<float>(min_)), max_);
		}
		template<typename Max_, typename RequiresMaxConvertibleToFloat_ = std::enable_if_t<std::is_convertible_v<Max_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM Clamp(__m128 min_, const Max_& max_) const
		{
			return Clamp(min_, _mm_set1_ps(static_cast<float>(max_)));
		}
		template<typename Min_, typename RequiresMinConvertibleToFloat_ = std::enable_if_t<std::is_convertible_v<Min_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM Clamp(const Min_& min_, const FastMatrix4x4f_CM& max_) const
		{
			return Clamp(_mm_set1_ps(static_cast<float>(min_)), max_);
		}
		template<typename Min_, typename RequiresMinConvertibleToFloat_ = std::enable_if_t<std::is_convertible_v<Min_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM Clamp(const FastMatrix4x4f_CM& min_, const Min_& max_) const
		{
			return Clamp(min_, _mm_set1_ps(static_cast<float>(max_)));
		}
		template
		<
			typename Min_,
			typename Max_,
			typename RequiresArgsConvertibleToFloat = std::enable_if_t<std::is_convertible_v<Max_, float>&& std::is_convertible_v<Min_, float>>
		>
		[[nodiscard]] inline FastMatrix4x4f_CM Clamp(const Min_& min_, const Max_& max_) const
		{
			return Clamp(_mm_set1_ps(static_cast<float>(min_)), _mm_set1_ps(static_cast<float>(max_)));
		}

		[[nodiscard]] inline FastMatrix4x4f_CM ClampMin(__m128 min_0_, __m128 min_1_, __m128 min_2_, __m128 min_3_) const
		{
			return FastMatrix4x4f_CM
			(
				EmuSIMD::clamp_min(column0, min_0_),
				EmuSIMD::clamp_min(column1, min_1_),
				EmuSIMD::clamp_min(column2, min_2_),
				EmuSIMD::clamp_min(column3, min_3_)
			);
		}
		[[nodiscard]] inline FastMatrix4x4f_CM ClampMin(__m128 min_) const
		{
			return FastMatrix4x4f_CM
			(
				EmuSIMD::clamp_min(column0, min_),
				EmuSIMD::clamp_min(column1, min_),
				EmuSIMD::clamp_min(column2, min_),
				EmuSIMD::clamp_min(column3, min_)
			);
		}
		[[nodiscard]] inline FastMatrix4x4f_CM ClampMin(const FastMatrix4x4f_CM& min_) const
		{
			return ClampMin(min_.column0, min_.column1, min_.column2, min_.column3);
		}
		template<typename Min_, typename RequiresMinConvertibleToFloat_ = std::enable_if_t<std::is_convertible_v<Min_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM ClampMin(const Min_& min_) const
		{
			return ClampMin(_mm_set1_ps(static_cast<float>(min_)));
		}

		[[nodiscard]] inline FastMatrix4x4f_CM ClampMax(__m128 max_0_, __m128 max_1_, __m128 max_2_, __m128 max_3_) const
		{
			return FastMatrix4x4f_CM
			(
				EmuSIMD::clamp_max(column0, max_0_),
				EmuSIMD::clamp_max(column1, max_1_),
				EmuSIMD::clamp_max(column2, max_2_),
				EmuSIMD::clamp_max(column3, max_3_)
			);
		}
		[[nodiscard]] inline FastMatrix4x4f_CM ClampMax(__m128 max_) const
		{
			return FastMatrix4x4f_CM
			(
				EmuSIMD::clamp_max(column0, max_),
				EmuSIMD::clamp_max(column1, max_),
				EmuSIMD::clamp_max(column2, max_),
				EmuSIMD::clamp_max(column3, max_)
			);
		}
		[[nodiscard]] inline FastMatrix4x4f_CM ClampMax(const FastMatrix4x4f_CM& max_) const
		{
			return ClampMax(max_.column0, max_.column1, max_.column2, max_.column3);
		}
		template<typename Max_, typename RequiresMaxConvertibleToFloat_ = std::enable_if_t<std::is_convertible_v<Max_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM ClampMax(const Max_& max_) const
		{
			return ClampMax(_mm_set1_ps(static_cast<float>(max_)));
		}

		/// <summary> Finds the smallest value within this matrix. </summary>
		/// <typeparam name="Out_">Type to output the value as.</typeparam>
		/// <returns>Copy of the smallest value within this matrix.</returns>
		template<typename Out_ = float>
		[[nodiscard]] inline Out_ Min() const
		{
			if constexpr (_assert_valid_cast_to<Out_>())
			{
				__m128 min_ = _mm_min_ps(column0, column1);
				min_ = _mm_min_ps(min_, column2);
				return static_cast<Out_>(EmuSIMD::vector_min_scalar(_mm_min_ps(min_, column3)));
			}
			else
			{
				static_assert(false, "Attempted to retrieve an EmuMath::FastMatrix4x4f_CM's Min value using an output type that cannot be converted to from float.");
			}
		}

		/// <summary> Finds the largest value within this matrix. </summary>
		/// <typeparam name="Out_">Type to output the value as.</typeparam>
		/// <returns>Copy of the largest value within this matrix.</returns>
		template<typename Out_ = float>
		[[nodiscard]] inline Out_ Max() const
		{
			if constexpr (_assert_valid_cast_to<Out_>())
			{
				__m128 max_ = _mm_max_ps(column0, column1);
				max_ = _mm_max_ps(max_, column2);
				return static_cast<Out_>(EmuSIMD::vector_max_scalar(_mm_max_ps(max_, column3)));
			}
			else
			{
				static_assert(false, "Attempted to retrieve an EmuMath::FastMatrix4x4f_CM's Max value using an output type that cannot be converted to from float.");
			}
		}

		template<typename Out_ = float>
		[[nodiscard]] inline Out_ TotalSum() const
		{
			__m128 sum_ = _mm_add_ps(column0, column1);
			sum_ = _mm_add_ps(sum_, column2);
			sum_ = _mm_add_ps(sum_, column3);
			return EmuSIMD::horizontal_sum_scalar<Out_>(sum_);
		}
#pragma endregion

#pragma region BITWISE_FUNCS
		/// <summary>
		/// <para> Performs a bitwise AND operation between this matrix and the passed column registers. </para>
		/// <para> Passed registers represent the respective column within a 4x4 column-major matrix. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to AND with this matrix's 0th column.</param>
		/// <param name="rhs_column_1_">Register to AND with this matrix's 1st column.</param>
		/// <param name="rhs_column_2_">Register to AND with this matrix's 2nd column.</param>
		/// <param name="rhs_column_3_">Register to AND with this matrix's 3rd column.</param>
		/// <returns>Result of a bitwise AND between this matrix and the matrix represented by the passed column registers.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM And(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_and_ps(column0, rhs_column_0_),
				_mm_and_ps(column1, rhs_column_1_),
				_mm_and_ps(column2, rhs_column_2_),
				_mm_and_ps(column3, rhs_column_3_)
			);
		}
		/// <summary>
		/// <para> Performs a bitwise AND operation between all of this matrix's columns and the passed rhs_ register. </para>
		/// </summary>
		/// <param name="rhs_">Register to AND with each of this matrix's columns.</param>
		/// <returns>Result of a bitwise AND between this matrix's columns and the passed rhs_ register.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM And(__m128 rhs_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_and_ps(column0, rhs_),
				_mm_and_ps(column1, rhs_),
				_mm_and_ps(column2, rhs_),
				_mm_and_ps(column3, rhs_)
			);
		}
		/// <summary>
		/// <para> Performs a bitwise AND operation between all of this matrix's elements and the respective elements of the passed matrix. </para>
		/// </summary>
		/// <param name="rhs_">4x4 column-major matrix to AND the elements of this matrix with.</param>
		/// <returns>Result of a bitwise AND between this matrix and the passed matrix.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM And(const FastMatrix4x4f_CM& rhs_) const
		{
			return And(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary>
		/// <para> Performs a bitwise AND operation between all of this matrix's elements and the passed scalar. </para>
		/// </summary>
		/// <param name="rhs_">Scalar to AND every element of this matrix with.</param>
		/// <returns>Result of a bitwise AND between this matrix and the passed scalar.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM And(float rhs_) const
		{
			return And(_mm_broadcast_ss(&rhs_));
		}

		/// <summary>
		/// <para> Performs a bitwise OR operation between this matrix and the passed column registers. </para>
		/// <para> Passed registers represent the respective column within a 4x4 column-major matrix. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to OR with this matrix's 0th column.</param>
		/// <param name="rhs_column_1_">Register to OR with this matrix's 1st column.</param>
		/// <param name="rhs_column_2_">Register to OR with this matrix's 2nd column.</param>
		/// <param name="rhs_column_3_">Register to OR with this matrix's 3rd column.</param>
		/// <returns>Result of a bitwise OR between this matrix and the matrix represented by the passed column registers.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Or(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_or_ps(column0, rhs_column_0_),
				_mm_or_ps(column1, rhs_column_1_),
				_mm_or_ps(column2, rhs_column_2_),
				_mm_or_ps(column3, rhs_column_3_)
			);
		}
		/// <summary>
		/// <para> Performs a bitwise OR operation between all of this matrix's columns and the passed rhs_ register. </para>
		/// </summary>
		/// <param name="rhs_">Register to OR with each of this matrix's columns.</param>
		/// <returns>Result of a bitwise OR between this matrix's columns and the passed rhs_ register.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Or(__m128 rhs_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_or_ps(column0, rhs_),
				_mm_or_ps(column1, rhs_),
				_mm_or_ps(column2, rhs_),
				_mm_or_ps(column3, rhs_)
			);
		}
		/// <summary>
		/// <para> Performs a bitwise OR operation between all of this matrix's elements and the respective elements of the passed matrix. </para>
		/// </summary>
		/// <param name="rhs_">4x4 column-major matrix to OR the elements of this matrix with.</param>
		/// <returns>Result of a bitwise OR between this matrix and the passed matrix.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Or(const FastMatrix4x4f_CM& rhs_) const
		{
			return Or(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary>
		/// <para> Performs a bitwise OR operation between all of this matrix's elements and the passed scalar. </para>
		/// </summary>
		/// <param name="rhs_">Scalar to OR every element of this matrix with.</param>
		/// <returns>Result of a bitwise OR between this matrix and the passed scalar.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Or(float rhs_) const
		{
			return Or(_mm_broadcast_ss(&rhs_));
		}

		/// <summary>
		/// <para> Performs a bitwise XOR operation between this matrix and the passed column registers. </para>
		/// <para> Passed registers represent the respective column within a 4x4 column-major matrix. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to XOR with this matrix's 0th column.</param>
		/// <param name="rhs_column_1_">Register to XOR with this matrix's 1st column.</param>
		/// <param name="rhs_column_2_">Register to XOR with this matrix's 2nd column.</param>
		/// <param name="rhs_column_3_">Register to XOR with this matrix's 3rd column.</param>
		/// <returns>Result of a bitwise XOR between this matrix and the matrix represented by the passed column registers.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Xor(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_xor_ps(column0, rhs_column_0_),
				_mm_xor_ps(column1, rhs_column_1_),
				_mm_xor_ps(column2, rhs_column_2_),
				_mm_xor_ps(column3, rhs_column_3_)
			);
		}
		/// <summary>
		/// <para> Performs a bitwise XOR operation between all of this matrix's columns and the passed rhs_ register. </para>
		/// </summary>
		/// <param name="rhs_">Register to XOR with each of this matrix's columns.</param>
		/// <returns>Result of a bitwise XOR between this matrix's columns and the passed rhs_ register.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Xor(__m128 rhs_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_xor_ps(column0, rhs_),
				_mm_xor_ps(column1, rhs_),
				_mm_xor_ps(column2, rhs_),
				_mm_xor_ps(column3, rhs_)
			);
		}
		/// <summary>
		/// <para> Performs a bitwise XOR operation between all of this matrix's elements and the respective elements of the passed matrix. </para>
		/// </summary>
		/// <param name="rhs_">4x4 column-major matrix to OR the elements of this matrix with.</param>
		/// <returns>Result of a bitwise XOR between this matrix and the passed matrix.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Xor(const FastMatrix4x4f_CM& rhs_) const
		{
			return Xor(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary>
		/// <para> Performs a bitwise XOR operation between all of this matrix's elements and the passed scalar. </para>
		/// </summary>
		/// <param name="rhs_">Scalar to XOR every element of this matrix with.</param>
		/// <returns>Result of a bitwise XOR between this matrix and the passed scalar.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Xor(float rhs_) const
		{
			return Xor(_mm_broadcast_ss(&rhs_));
		}

		/// <summary> Flips the bits of this matrix's columns. </summary>
		/// <returns>Resulting matrix from flipping the bits of this matrix.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Not() const
		{
			return FastMatrix4x4f_CM
			(
				EmuSIMD::bitwise_not(column0),
				EmuSIMD::bitwise_not(column1),
				EmuSIMD::bitwise_not(column2),
				EmuSIMD::bitwise_not(column3)
			);
		}
#pragma endregion

#pragma region COMPARISON_FUNCS_PER_ELEMENT
		/// <summary> 
		/// <para> Compares this matrix's columns to the respective passed column registers, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was equal to that of the respective passed columns; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare this matrix's 0th column with.</param>
		/// <param name="rhs_column_1_">Register to compare this matrix's 1st column with.</param>
		/// <param name="rhs_column_2_">Register to compare this matrix's 2nd column with.</param>
		/// <param name="rhs_column_3_">Register to compare this matrix's 3rd column with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementEqual(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_cmpeq_ps(column0, rhs_column_0_),
				_mm_cmpeq_ps(column1, rhs_column_1_),
				_mm_cmpeq_ps(column2, rhs_column_2_),
				_mm_cmpeq_ps(column3, rhs_column_3_)
			);
		}
		/// <summary> 
		/// <para> Compares this matrix's columns to the passed column register, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was equal to that of the passed column; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_all_columns_">Register to compare all of this matrix's columns with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementEqual(__m128 rhs_all_columns_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_cmpeq_ps(column0, rhs_all_columns_),
				_mm_cmpeq_ps(column1, rhs_all_columns_),
				_mm_cmpeq_ps(column2, rhs_all_columns_),
				_mm_cmpeq_ps(column3, rhs_all_columns_)
			);
		}
		/// <summary> 
		/// <para> Compares this matrix's columns to those of the passed matrix, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was equal to that of the passed matrix; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_">Matrix to compare this matrix's elements with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementEqual(const FastMatrix4x4f_CM& rhs_) const
		{
			return CmpPerElementEqual(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary> 
		/// <para> Compares this matrix's columns to those of the passed value, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was equal to the passed value; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_">Value to compare all of this matrix's elements with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		template<typename Rhs_, typename RequiresRhsConvertibleToFloat = std::enable_if_t<std::is_convertible_v<Rhs_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementEqual(const Rhs_& rhs_) const
		{
			return CmpPerElementEqual(_mm_set1_ps(static_cast<float>(rhs_)));
		}

		/// <summary> 
		/// <para> Compares this matrix's columns to the respective passed column registers, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was not equal to that of the respective passed columns; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare this matrix's 0th column with.</param>
		/// <param name="rhs_column_1_">Register to compare this matrix's 1st column with.</param>
		/// <param name="rhs_column_2_">Register to compare this matrix's 2nd column with.</param>
		/// <param name="rhs_column_3_">Register to compare this matrix's 3rd column with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementNotEqual(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_cmpneq_ps(column0, rhs_column_0_),
				_mm_cmpneq_ps(column1, rhs_column_1_),
				_mm_cmpneq_ps(column2, rhs_column_2_),
				_mm_cmpneq_ps(column3, rhs_column_3_)
			);
		}
		/// <summary> 
		/// <para> Compares this matrix's columns to the passed column register, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was not equal to that of the passed column; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_all_columns_">Register to compare all of this matrix's columns with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementNotEqual(__m128 rhs_all_columns_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_cmpneq_ps(column0, rhs_all_columns_),
				_mm_cmpneq_ps(column1, rhs_all_columns_),
				_mm_cmpneq_ps(column2, rhs_all_columns_),
				_mm_cmpneq_ps(column3, rhs_all_columns_)
			);
		}
		/// <summary> 
		/// <para> Compares this matrix's columns to those of the passed matrix, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was not equal to that of the passed matrix; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_">Matrix to compare this matrix's elements with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementNotEqual(const FastMatrix4x4f_CM& rhs_) const
		{
			return CmpPerElementNotEqual(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary> 
		/// <para> Compares this matrix's columns to those of the passed value, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was not equal to the passed value; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_">Value to compare all of this matrix's elements with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		template<typename Rhs_, typename RequiresRhsConvertibleToFloat = std::enable_if_t<std::is_convertible_v<Rhs_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementNotEqual(const Rhs_& rhs_) const
		{
			return CmpPerElementNotEqual(_mm_set1_ps(static_cast<float>(rhs_)));
		}

		/// <summary> 
		/// <para> Compares this matrix's columns to the respective passed column registers, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was greater than that of the respective passed columns; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare this matrix's 0th column with.</param>
		/// <param name="rhs_column_1_">Register to compare this matrix's 1st column with.</param>
		/// <param name="rhs_column_2_">Register to compare this matrix's 2nd column with.</param>
		/// <param name="rhs_column_3_">Register to compare this matrix's 3rd column with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementGreater(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_cmpgt_ps(column0, rhs_column_0_),
				_mm_cmpgt_ps(column1, rhs_column_1_),
				_mm_cmpgt_ps(column2, rhs_column_2_),
				_mm_cmpgt_ps(column3, rhs_column_3_)
			);
		}
		/// <summary> 
		/// <para> Compares this matrix's columns to the passed column register, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was greater than that of the passed column; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_all_columns_">Register to compare all of this matrix's columns with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementGreater(__m128 rhs_all_columns_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_cmpgt_ps(column0, rhs_all_columns_),
				_mm_cmpgt_ps(column1, rhs_all_columns_),
				_mm_cmpgt_ps(column2, rhs_all_columns_),
				_mm_cmpgt_ps(column3, rhs_all_columns_)
			);
		}
		/// <summary> 
		/// <para> Compares this matrix's columns to those of the passed matrix, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was greater than that of the passed matrix; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_">Matrix to compare this matrix's elements with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementGreater(const FastMatrix4x4f_CM& rhs_) const
		{
			return CmpPerElementGreater(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary> 
		/// <para> Compares this matrix's columns to those of the passed value, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was greater than the passed value; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_">Value to compare all of this matrix's elements with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		template<typename Rhs_, typename RequiresRhsConvertibleToFloat = std::enable_if_t<std::is_convertible_v<Rhs_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementGreater(const Rhs_& rhs_) const
		{
			return CmpPerElementGreater(_mm_set1_ps(static_cast<float>(rhs_)));
		}

		/// <summary> 
		/// <para> Compares this matrix's columns to the respective passed column registers, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was less than that of the respective passed columns; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare this matrix's 0th column with.</param>
		/// <param name="rhs_column_1_">Register to compare this matrix's 1st column with.</param>
		/// <param name="rhs_column_2_">Register to compare this matrix's 2nd column with.</param>
		/// <param name="rhs_column_3_">Register to compare this matrix's 3rd column with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementLess(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_cmplt_ps(column0, rhs_column_0_),
				_mm_cmplt_ps(column1, rhs_column_1_),
				_mm_cmplt_ps(column2, rhs_column_2_),
				_mm_cmplt_ps(column3, rhs_column_3_)
			);
		}
		/// <summary> 
		/// <para> Compares this matrix's columns to the passed column register, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was less than that of the passed column; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_all_columns_">Register to compare all of this matrix's columns with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementLess(__m128 rhs_all_columns_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_cmplt_ps(column0, rhs_all_columns_),
				_mm_cmplt_ps(column1, rhs_all_columns_),
				_mm_cmplt_ps(column2, rhs_all_columns_),
				_mm_cmplt_ps(column3, rhs_all_columns_)
			);
		}
		/// <summary> 
		/// <para> Compares this matrix's columns to those of the passed matrix, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was less than that of the passed matrix; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_">Matrix to compare this matrix's elements with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementLess(const FastMatrix4x4f_CM& rhs_) const
		{
			return CmpPerElementLess(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary> 
		/// <para> Compares this matrix's columns to those of the passed value, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was less than the passed value; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_">Value to compare all of this matrix's elements with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		template<typename Rhs_, typename RequiresRhsConvertibleToFloat = std::enable_if_t<std::is_convertible_v<Rhs_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementLess(const Rhs_& rhs_) const
		{
			return CmpPerElementLess(_mm_set1_ps(static_cast<float>(rhs_)));
		}

		/// <summary> 
		/// <para> Compares this matrix's columns to the respective passed column registers, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was 
		///		greater than or equal tothat of the respective passed columns; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare this matrix's 0th column with.</param>
		/// <param name="rhs_column_1_">Register to compare this matrix's 1st column with.</param>
		/// <param name="rhs_column_2_">Register to compare this matrix's 2nd column with.</param>
		/// <param name="rhs_column_3_">Register to compare this matrix's 3rd column with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementGreaterEqual(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_cmpge_ps(column0, rhs_column_0_),
				_mm_cmpge_ps(column1, rhs_column_1_),
				_mm_cmpge_ps(column2, rhs_column_2_),
				_mm_cmpge_ps(column3, rhs_column_3_)
			);
		}
		/// <summary> 
		/// <para> Compares this matrix's columns to the passed column register, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was greater than or equal to that of the passed column; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_all_columns_">Register to compare all of this matrix's columns with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementGreaterEqual(__m128 rhs_all_columns_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_cmpge_ps(column0, rhs_all_columns_),
				_mm_cmpge_ps(column1, rhs_all_columns_),
				_mm_cmpge_ps(column2, rhs_all_columns_),
				_mm_cmpge_ps(column3, rhs_all_columns_)
			);
		}
		/// <summary> 
		/// <para> Compares this matrix's columns to those of the passed matrix, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was greater than or equal to that of the passed matrix; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_">Matrix to compare this matrix's elements with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementGreaterEqual(const FastMatrix4x4f_CM& rhs_) const
		{
			return CmpPerElementGreaterEqual(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary> 
		/// <para> Compares this matrix's columns to those of the passed value, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was greater than or equal to the passed value; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_">Value to compare all of this matrix's elements with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		template<typename Rhs_, typename RequiresRhsConvertibleToFloat = std::enable_if_t<std::is_convertible_v<Rhs_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementGreaterEqual(const Rhs_& rhs_) const
		{
			return CmpPerElementGreaterEqual(_mm_set1_ps(static_cast<float>(rhs_)));
		}

		/// <summary> 
		/// <para> Compares this matrix's columns to the respective passed column registers, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was 
		///		less than or equal to that of the respective passed columns; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare this matrix's 0th column with.</param>
		/// <param name="rhs_column_1_">Register to compare this matrix's 1st column with.</param>
		/// <param name="rhs_column_2_">Register to compare this matrix's 2nd column with.</param>
		/// <param name="rhs_column_3_">Register to compare this matrix's 3rd column with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementLessEqual(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_cmple_ps(column0, rhs_column_0_),
				_mm_cmple_ps(column1, rhs_column_1_),
				_mm_cmple_ps(column2, rhs_column_2_),
				_mm_cmple_ps(column3, rhs_column_3_)
			);
		}
		/// <summary> 
		/// <para> Compares this matrix's columns to the passed column register, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was less than or equal to that of the passed column; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_all_columns_">Register to compare all of this matrix's columns with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementLessEqual(__m128 rhs_all_columns_) const
		{
			return FastMatrix4x4f_CM
			(
				_mm_cmple_ps(column0, rhs_all_columns_),
				_mm_cmple_ps(column1, rhs_all_columns_),
				_mm_cmple_ps(column2, rhs_all_columns_),
				_mm_cmple_ps(column3, rhs_all_columns_)
			);
		}
		/// <summary> 
		/// <para> Compares this matrix's columns to those of the passed matrix, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was less than or equal to that of the passed matrix; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_">Matrix to compare this matrix's elements with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementLessEqual(const FastMatrix4x4f_CM& rhs_) const
		{
			return CmpPerElementLessEqual(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary> 
		/// <para> Compares this matrix's columns to those of the passed value, creating a matrix of vectorwise masks. </para>
		/// <para>
		///		Elements in the output matrix will be have all bits set to 1 if this matrix's respective element was less than or equal to the passed value; 
		///		otherwise all bits will be set to 0 for that element.
		/// </para>
		/// </summary>
		/// <param name="rhs_">Value to compare all of this matrix's elements with.</param>
		/// <returns>Matrix containing the results of comparisons for respective elements, with bits set to all 1s if true, and all 0s if false.</returns>
		template<typename Rhs_, typename RequiresRhsConvertibleToFloat = std::enable_if_t<std::is_convertible_v<Rhs_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM CmpPerElementLessEqual(const Rhs_& rhs_) const
		{
			return CmpPerElementLessEqual(_mm_set1_ps(static_cast<float>(rhs_)));
		}
#pragma endregion

#pragma region COMPARISON_FUNCS_ANY
		/// <summary>
		/// <para> Compares all columns of this matrix to the respective passed column registers. </para>
		/// <para> If at least one element is equal to that of the respective rhs, this funcion will return true; if all comparisons are false, it will return false. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare this matrix's 0th column with.</param>
		/// <param name="rhs_column_1_">Register to compare this matrix's 1st column with.</param>
		/// <param name="rhs_column_2_">Register to compare this matrix's 2nd column with.</param>
		/// <param name="rhs_column_3_">Register to compare this matrix's 3rd column with.</param>
		/// <returns>True if at least one comparison between this matrix's elements and those of the respective passed columns returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyEqual(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			// NOTE FOR ALL ANYCOMPARISON FUNCS
			// --- We bitwise OR vector masks together and then extract a scalar movemask at the end
			// --- This is chosen instead of a logical OR of all masks due to instruction latency
			// --- _mm_or_ps = 1 cycle latency, _mm_movemask_ps = 2 cycle latency
			// --- Although there is potential for short-circuits with scalar bool checks, the latency adds up quickly
			// ------ e.g. 2 checks == as much latency as a full check with bitwise ORed masks
			// --- This results in a consistent instruction latency of 5, versus the worst cases of 6 or 8 when attempting to allow short-circuit optimisations
			__m128 cmp_mask_ = _mm_cmpeq_ps(column0, rhs_column_0_);
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpeq_ps(column1, rhs_column_1_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpeq_ps(column2, rhs_column_2_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpeq_ps(column3, rhs_column_3_));
			return _mm_movemask_ps(cmp_mask_);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed column register. </para>
		/// <para> If at least one element is equal to that of the rhs, this funcion will return true; if all comparisons are false, it will return false. </para>
		/// </summary>
		/// <param name="rhs_all_columns_">Register to compare all of this matrix's columns with.</param>
		/// <returns>True if at least one comparison between this matrix's elements and those of the passed register returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyEqual(__m128 rhs_all_columns_) const
		{
			__m128 cmp_mask_ = _mm_cmpeq_ps(column0, rhs_all_columns_);
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpeq_ps(column1, rhs_all_columns_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpeq_ps(column2, rhs_all_columns_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpeq_ps(column3, rhs_all_columns_));
			return _mm_movemask_ps(cmp_mask_);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to those of the passed matrix. </para>
		/// <para> If at least one element is equal to that of the rhs, this funcion will return true; if all comparisons are false, it will return false. </para>
		/// </summary>
		/// <param name="rhs_">Matrix to compare all of this matrix's respective elements with.</param>
		/// <returns>True if at least one comparison between this matrix's elements and those of the passed matrix returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyEqual(const FastMatrix4x4f_CM& rhs_) const
		{
			return CmpAnyEqual(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed value. </para>
		/// <para> If at least one element is equal to rhs_, this funcion will return true; if all comparisons are false, it will return false. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare all of this matrix's elements with. Must be convertible to float.</param>
		/// <returns>True if at least one comparison between this matrix's elements and the passed value returned true; otherwise false.</returns>
		template<typename Rhs_, typename RequiresRhsConvertibleToFloat = std::enable_if_t<std::is_convertible_v<Rhs_, float>>>
		[[nodiscard]] inline bool CmpAnyEqual(const Rhs_& rhs_) const
		{
			return CmpAnyEqual(_mm_set1_ps(static_cast<float>(rhs_)));
		}

		/// <summary>
		/// <para> Compares all columns of this matrix to the respective passed column registers. </para>
		/// <para> If at least one element is not equal to that of the respective rhs, this funcion will return true; if all comparisons are false, it will return false. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare this matrix's 0th column with.</param>
		/// <param name="rhs_column_1_">Register to compare this matrix's 1st column with.</param>
		/// <param name="rhs_column_2_">Register to compare this matrix's 2nd column with.</param>
		/// <param name="rhs_column_3_">Register to compare this matrix's 3rd column with.</param>
		/// <returns>True if at least one comparison between this matrix's elements and those of the respective passed columns returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyNotEqual(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			__m128 cmp_mask_ = _mm_cmpneq_ps(column0, rhs_column_0_);
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpneq_ps(column1, rhs_column_1_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpneq_ps(column2, rhs_column_2_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpneq_ps(column3, rhs_column_3_));
			return _mm_movemask_ps(cmp_mask_);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed column register. </para>
		/// <para> If at least one element is not equal to that of the rhs, this funcion will return true; if all comparisons are false, it will return false. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare all of this matrix's columns with.</param>
		/// <returns>True if at least one comparison between this matrix's elements and those of the passed register returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyNotEqual(__m128 rhs_all_columns_) const
		{
			__m128 cmp_mask_ = _mm_cmpneq_ps(column0, rhs_all_columns_);
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpneq_ps(column1, rhs_all_columns_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpneq_ps(column2, rhs_all_columns_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpneq_ps(column3, rhs_all_columns_));
			return _mm_movemask_ps(cmp_mask_);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to those of the passed matrix. </para>
		/// <para> If at least one element is not equal to that of the rhs, this funcion will return true; if all comparisons are false, it will return false. </para>
		/// </summary>
		/// <param name="rhs_">Matrix to compare all of this matrix's respective elements with.</param>
		/// <returns>True if at least one comparison between this matrix's elements and those of the passed matrix returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyNotEqual(const FastMatrix4x4f_CM& rhs_) const
		{
			return CmpAnyNotEqual(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed value. </para>
		/// <para> If at least one element is equal to rhs_, this funcion will return true; if all comparisons are false, it will return false. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare all of this matrix's elements with. Must be convertible to float.</param>
		/// <returns>True if at least one comparison between this matrix's elements and the passed value returned true; otherwise false.</returns>
		template<typename Rhs_, typename RequiresRhsConvertibleToFloat = std::enable_if_t<std::is_convertible_v<Rhs_, float>>>
		[[nodiscard]] inline bool CmpAnyNotEqual(const Rhs_& rhs_) const
		{
			return CmpAnyNotEqual(_mm_set1_ps(static_cast<float>(rhs_)));
		}

		/// <summary>
		/// <para> Compares all columns of this matrix to the respective passed column registers. </para>
		/// <para> If at least one element is greater than that of the respective rhs, this funcion will return true; if all comparisons are false, it will return false. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare this matrix's 0th column with.</param>
		/// <param name="rhs_column_1_">Register to compare this matrix's 1st column with.</param>
		/// <param name="rhs_column_2_">Register to compare this matrix's 2nd column with.</param>
		/// <param name="rhs_column_3_">Register to compare this matrix's 3rd column with.</param>
		/// <returns>True if at least one comparison between this matrix's elements and those of the respective passed columns returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyGreater(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			__m128 cmp_mask_ = _mm_cmpgt_ps(column0, rhs_column_0_);
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpgt_ps(column1, rhs_column_1_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpgt_ps(column2, rhs_column_2_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpgt_ps(column3, rhs_column_3_));
			return _mm_movemask_ps(cmp_mask_);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed column register. </para>
		/// <para> If at least one element is greater than that of the rhs, this funcion will return true; if all comparisons are false, it will return false. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare all of this matrix's columns with.</param>
		/// <returns>True if at least one comparison between this matrix's elements and those of the passed register returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyGreater(__m128 rhs_all_columns_) const
		{
			__m128 cmp_mask_ = _mm_cmpgt_ps(column0, rhs_all_columns_);
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpgt_ps(column1, rhs_all_columns_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpgt_ps(column2, rhs_all_columns_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpgt_ps(column3, rhs_all_columns_));
			return _mm_movemask_ps(cmp_mask_);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to those of the passed matrix. </para>
		/// <para> If at least one element is greater than that of the rhs, this funcion will return true; if all comparisons are false, it will return false. </para>
		/// </summary>
		/// <param name="rhs_">Matrix to compare all of this matrix's respective elements with.</param>
		/// <returns>True if at least one comparison between this matrix's elements and those of the passed matrix returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyGreater(const FastMatrix4x4f_CM& rhs_) const
		{
			return CmpAnyGreater(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed value. </para>
		/// <para> If at least one element is greater than rhs_, this funcion will return true; if all comparisons are false, it will return false. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare all of this matrix's elements with. Must be convertible to float.</param>
		/// <returns>True if at least one comparison between this matrix's elements and the passed value returned true; otherwise false.</returns>
		template<typename Rhs_, typename RequiresRhsConvertibleToFloat = std::enable_if_t<std::is_convertible_v<Rhs_, float>>>
		[[nodiscard]] inline bool CmpAnyGreater(const Rhs_& rhs_) const
		{
			return CmpAnyGreater(_mm_set1_ps(static_cast<float>(rhs_)));
		}

		/// <summary>
		/// <para> Compares all columns of this matrix to the respective passed column registers. </para>
		/// <para> If at least one element is less than that of the respective rhs, this funcion will return true; if all comparisons are false, it will return false. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare this matrix's 0th column with.</param>
		/// <param name="rhs_column_1_">Register to compare this matrix's 1st column with.</param>
		/// <param name="rhs_column_2_">Register to compare this matrix's 2nd column with.</param>
		/// <param name="rhs_column_3_">Register to compare this matrix's 3rd column with.</param>
		/// <returns>True if at least one comparison between this matrix's elements and those of the respective passed columns returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyLess(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			__m128 cmp_mask_ = _mm_cmplt_ps(column0, rhs_column_0_);
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmplt_ps(column1, rhs_column_1_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmplt_ps(column2, rhs_column_2_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmplt_ps(column3, rhs_column_3_));
			return _mm_movemask_ps(cmp_mask_);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed column register. </para>
		/// <para> If at least one element is less than that of the rhs, this funcion will return true; if all comparisons are false, it will return false. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare all of this matrix's columns with.</param>
		/// <returns>True if at least one comparison between this matrix's elements and those of the passed register returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyLess(__m128 rhs_all_columns_) const
		{
			__m128 cmp_mask_ = _mm_cmplt_ps(column0, rhs_all_columns_);
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmplt_ps(column1, rhs_all_columns_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmplt_ps(column2, rhs_all_columns_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmplt_ps(column3, rhs_all_columns_));
			return _mm_movemask_ps(cmp_mask_);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to those of the passed matrix. </para>
		/// <para> If at least one element is less than that of the rhs, this funcion will return true; if all comparisons are false, it will return false. </para>
		/// </summary>
		/// <param name="rhs_">Matrix to compare all of this matrix's respective elements with.</param>
		/// <returns>True if at least one comparison between this matrix's elements and those of the passed matrix returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyLess(const FastMatrix4x4f_CM& rhs_) const
		{
			return CmpAnyLess(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed value. </para>
		/// <para> If at least one element is less than rhs_, this funcion will return true; if all comparisons are false, it will return false. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare all of this matrix's elements with. Must be convertible to float.</param>
		/// <returns>True if at least one comparison between this matrix's elements and the passed value returned true; otherwise false.</returns>
		template<typename Rhs_, typename RequiresRhsConvertibleToFloat = std::enable_if_t<std::is_convertible_v<Rhs_, float>>>
		[[nodiscard]] inline bool CmpAnyLess(const Rhs_& rhs_) const
		{
			return CmpAnyLess(_mm_set1_ps(static_cast<float>(rhs_)));
		}

		/// <summary>
		/// <para> Compares all columns of this matrix to the respective passed column registers. </para>
		/// <para>
		///		If at least one element is greater than or equal to that of the respective rhs, this funcion will return true; 
		///		if all comparisons are false, it will return false.
		/// </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare this matrix's 0th column with.</param>
		/// <param name="rhs_column_1_">Register to compare this matrix's 1st column with.</param>
		/// <param name="rhs_column_2_">Register to compare this matrix's 2nd column with.</param>
		/// <param name="rhs_column_3_">Register to compare this matrix's 3rd column with.</param>
		/// <returns>True if at least one comparison between this matrix's elements and those of the respective passed columns returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyGreaterEqual(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			__m128 cmp_mask_ = _mm_cmpge_ps(column0, rhs_column_0_);
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpge_ps(column1, rhs_column_1_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpge_ps(column2, rhs_column_2_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpge_ps(column3, rhs_column_3_));
			return _mm_movemask_ps(cmp_mask_);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed column register. </para>
		/// <para> If at least one element is greater than or equal to that of the rhs, this funcion will return true; if all comparisons are false, it will return false. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare all of this matrix's columns with.</param>
		/// <returns>True if at least one comparison between this matrix's elements and those of the passed register returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyGreaterEqual(__m128 rhs_all_columns_) const
		{
			__m128 cmp_mask_ = _mm_cmpge_ps(column0, rhs_all_columns_);
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpge_ps(column1, rhs_all_columns_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpge_ps(column2, rhs_all_columns_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmpge_ps(column3, rhs_all_columns_));
			return _mm_movemask_ps(cmp_mask_);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to those of the passed matrix. </para>
		/// <para> If at least one element is greater than or equal to that of the rhs, this funcion will return true; if all comparisons are false, it will return false. </para>
		/// </summary>
		/// <param name="rhs_">Matrix to compare all of this matrix's respective elements with.</param>
		/// <returns>True if at least one comparison between this matrix's elements and those of the passed matrix returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyGreaterEqual(const FastMatrix4x4f_CM& rhs_) const
		{
			return CmpAnyGreaterEqual(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed value. </para>
		/// <para> If at least one element is greater than or equal to rhs_, this funcion will return true; if all comparisons are false, it will return false. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare all of this matrix's elements with. Must be convertible to float.</param>
		/// <returns>True if at least one comparison between this matrix's elements and the passed value returned true; otherwise false.</returns>
		template<typename Rhs_, typename RequiresRhsConvertibleToFloat = std::enable_if_t<std::is_convertible_v<Rhs_, float>>>
		[[nodiscard]] inline bool CmpAnyGreaterEqual(const Rhs_& rhs_) const
		{
			return CmpAnyGreaterEqual(_mm_set1_ps(static_cast<float>(rhs_)));
		}

		/// <summary>
		/// <para> Compares all columns of this matrix to the respective passed column registers. </para>
		/// <para>
		///		If at least one element is less than or equal to that of the respective rhs, this funcion will return true; 
		///		if all comparisons are false, it will return false. 
		/// </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare this matrix's 0th column with.</param>
		/// <param name="rhs_column_1_">Register to compare this matrix's 1st column with.</param>
		/// <param name="rhs_column_2_">Register to compare this matrix's 2nd column with.</param>
		/// <param name="rhs_column_3_">Register to compare this matrix's 3rd column with.</param>
		/// <returns>True if at least one comparison between this matrix's elements and those of the respective passed columns returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyLessEqual(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			__m128 cmp_mask_ = _mm_cmple_ps(column0, rhs_column_0_);
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmple_ps(column1, rhs_column_1_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmple_ps(column2, rhs_column_2_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmple_ps(column3, rhs_column_3_));
			return _mm_movemask_ps(cmp_mask_);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed column register. </para>
		/// <para> If at least one element is less than or equal to that of the rhs, this funcion will return true; if all comparisons are false, it will return false. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare all of this matrix's columns with.</param>
		/// <returns>True if at least one comparison between this matrix's elements and those of the passed register returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyLessEqual(__m128 rhs_all_columns_) const
		{
			__m128 cmp_mask_ = _mm_cmple_ps(column0, rhs_all_columns_);
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmple_ps(column1, rhs_all_columns_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmple_ps(column2, rhs_all_columns_));
			cmp_mask_ = _mm_or_ps(cmp_mask_, _mm_cmple_ps(column3, rhs_all_columns_));
			return _mm_movemask_ps(cmp_mask_);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to those of the passed matrix. </para>
		/// <para> If at least one element is less than or equal to that of the rhs, this funcion will return true; if all comparisons are false, it will return false. </para>
		/// </summary>
		/// <param name="rhs_">Matrix to compare all of this matrix's respective elements with.</param>
		/// <returns>True if at least one comparison between this matrix's elements and those of the passed matrix returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyLessEqual(const FastMatrix4x4f_CM& rhs_) const
		{
			return CmpAnyLessEqual(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed value. </para>
		/// <para> If at least one element is less than or equal to rhs_, this funcion will return true; if all comparisons are false, it will return false. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare all of this matrix's elements with. Must be convertible to float.</param>
		/// <returns>True if at least one comparison between this matrix's elements and the passed value returned true; otherwise false.</returns>
		template<typename Rhs_, typename RequiresRhsConvertibleToFloat = std::enable_if_t<std::is_convertible_v<Rhs_, float>>>
		[[nodiscard]] inline bool CmpAnyLessEqual(const Rhs_& rhs_) const
		{
			return CmpAnyLessEqual(_mm_set1_ps(static_cast<float>(rhs_)));
		}
#pragma endregion

#pragma region COMPARISON_FUNCS_ALL
		/// <summary>
		/// <para> Compares all columns of this matrix to the respective passed column registers. </para>
		/// <para> If all elements are equal to their respective rhs values, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare this matrix's 0th column with.</param>
		/// <param name="rhs_column_1_">Register to compare this matrix's 1st column with.</param>
		/// <param name="rhs_column_2_">Register to compare this matrix's 2nd column with.</param>
		/// <param name="rhs_column_3_">Register to compare this matrix's 3rd column with.</param>
		/// <returns>True if all comparisons between this matrix's elements and those of the respective passed columns returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAllEqual(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			__m128 cmp_mask_ = _mm_cmpeq_ps(column0, rhs_column_0_);
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpeq_ps(column1, rhs_column_1_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpeq_ps(column2, rhs_column_2_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpeq_ps(column3, rhs_column_3_));
			return _mm_movemask_ps(cmp_mask_) == EmuSIMD::make_movemask<__m128, true, true, true, true>::value;
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed column register. </para>
		/// <para> If all elements are equal to their respective rhs values, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_all_columns_">Register to compare all of this matrix's columns with.</param>
		/// <returns>True if all comparisons between this matrix's elements and those of the passed register returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAllEqual(__m128 rhs_all_columns_) const
		{
			__m128 cmp_mask_ = _mm_cmpeq_ps(column0, rhs_all_columns_);
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpeq_ps(column1, rhs_all_columns_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpeq_ps(column2, rhs_all_columns_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpeq_ps(column3, rhs_all_columns_));
			return _mm_movemask_ps(cmp_mask_) == EmuSIMD::make_movemask<__m128, true, true, true, true>::value;
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to those of the passed matrix. </para>
		/// <para> If all elements are equal to their respective rhs values, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_">Matrix to compare all of this matrix's respective elements with.</param>
		/// <returns>True if all comparisons between this matrix's elements and those of the passed matrix returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAllEqual(const FastMatrix4x4f_CM& rhs_) const
		{
			return CmpAllEqual(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed value. </para>
		/// <para> If all elements are equal to the rhs value, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare all of this matrix's elements with. Must be convertible to float.</param>
		/// <returns>True if all comparisons between this matrix's elements and the passed value; otherwise false.</returns>
		template<typename Rhs_, typename RequiresRhsConvertibleToFloat = std::enable_if_t<std::is_convertible_v<Rhs_, float>>>
		[[nodiscard]] inline bool CmpAllEqual(const Rhs_& rhs_) const
		{
			return CmpAllEqual(_mm_set1_ps(static_cast<float>(rhs_)));
		}

		/// <summary>
		/// <para> Compares all columns of this matrix to the respective passed column registers. </para>
		/// <para> If all elements are not equal to their respective rhs values, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare this matrix's 0th column with.</param>
		/// <param name="rhs_column_1_">Register to compare this matrix's 1st column with.</param>
		/// <param name="rhs_column_2_">Register to compare this matrix's 2nd column with.</param>
		/// <param name="rhs_column_3_">Register to compare this matrix's 3rd column with.</param>
		/// <returns>True if all comparisons between this matrix's elements and those of the respective passed columns returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAllNotEqual(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			__m128 cmp_mask_ = _mm_cmpneq_ps(column0, rhs_column_0_);
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpneq_ps(column1, rhs_column_1_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpneq_ps(column2, rhs_column_2_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpneq_ps(column3, rhs_column_3_));
			return _mm_movemask_ps(cmp_mask_) == EmuSIMD::make_movemask<__m128, true, true, true, true>::value;
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed column register. </para>
		/// <para> If all elements are not equal to their respective rhs values, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_all_columns_">Register to compare all of this matrix's columns with.</param>
		/// <returns>True if all comparisons between this matrix's elements and those of the passed register returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAllNotEqual(__m128 rhs_all_columns_) const
		{
			__m128 cmp_mask_ = _mm_cmpneq_ps(column0, rhs_all_columns_);
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpneq_ps(column1, rhs_all_columns_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpneq_ps(column2, rhs_all_columns_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpneq_ps(column3, rhs_all_columns_));
			return _mm_movemask_ps(cmp_mask_) == EmuSIMD::make_movemask<__m128, true, true, true, true>::value;
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to those of the passed matrix. </para>
		/// <para> If all elements are not equal to their respective rhs values, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_">Matrix to compare all of this matrix's respective elements with.</param>
		/// <returns>True if all comparisons between this matrix's elements and those of the passed matrix returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAllNotEqual(const FastMatrix4x4f_CM& rhs_) const
		{
			return CmpAllNotEqual(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed value. </para>
		/// <para> If all elements are not equal to the rhs value, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare all of this matrix's elements with. Must be convertible to float.</param>
		/// <returns>True if all comparisons between this matrix's elements and the passed value; otherwise false.</returns>
		template<typename Rhs_, typename RequiresRhsConvertibleToFloat = std::enable_if_t<std::is_convertible_v<Rhs_, float>>>
		[[nodiscard]] inline bool CmpAllNotEqual(const Rhs_& rhs_) const
		{
			return CmpAllNotEqual(_mm_set1_ps(static_cast<float>(rhs_)));
		}

		/// <summary>
		/// <para> Compares all columns of this matrix to the respective passed column registers. </para>
		/// <para> If all elements are greater than their respective rhs values, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare this matrix's 0th column with.</param>
		/// <param name="rhs_column_1_">Register to compare this matrix's 1st column with.</param>
		/// <param name="rhs_column_2_">Register to compare this matrix's 2nd column with.</param>
		/// <param name="rhs_column_3_">Register to compare this matrix's 3rd column with.</param>
		/// <returns>True if all comparisons between this matrix's elements and those of the respective passed columns returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAllGreater(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			__m128 cmp_mask_ = _mm_cmpgt_ps(column0, rhs_column_0_);
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpgt_ps(column1, rhs_column_1_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpgt_ps(column2, rhs_column_2_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpgt_ps(column3, rhs_column_3_));
			return _mm_movemask_ps(cmp_mask_) == EmuSIMD::make_movemask<__m128, true, true, true, true>::value;
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed column register. </para>
		/// <para> If all elements are greater than their respective rhs values, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_all_columns_">Register to compare all of this matrix's columns with.</param>
		/// <returns>True if all comparisons between this matrix's elements and those of the passed register returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAllGreater(__m128 rhs_all_columns_) const
		{
			__m128 cmp_mask_ = _mm_cmpgt_ps(column0, rhs_all_columns_);
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpgt_ps(column1, rhs_all_columns_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpgt_ps(column2, rhs_all_columns_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpgt_ps(column3, rhs_all_columns_));
			return _mm_movemask_ps(cmp_mask_) == EmuSIMD::make_movemask<__m128, true, true, true, true>::value;
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to those of the passed matrix. </para>
		/// <para> If all elements are greater than their respective rhs values, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_">Matrix to compare all of this matrix's respective elements with.</param>
		/// <returns>True if all comparisons between this matrix's elements and those of the passed matrix returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAllGreater(const FastMatrix4x4f_CM& rhs_) const
		{
			return CmpAllGreater(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed value. </para>
		/// <para> If all elements are greater than the rhs value, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare all of this matrix's elements with. Must be convertible to float.</param>
		/// <returns>True if all comparisons between this matrix's elements and the passed value; otherwise false.</returns>
		template<typename Rhs_, typename RequiresRhsConvertibleToFloat = std::enable_if_t<std::is_convertible_v<Rhs_, float>>>
		[[nodiscard]] inline bool CmpAllGreater(const Rhs_& rhs_) const
		{
			return CmpAllGreater(_mm_set1_ps(static_cast<float>(rhs_)));
		}

		/// <summary>
		/// <para> Compares all columns of this matrix to the respective passed column registers. </para>
		/// <para> If all elements are less than their respective rhs values, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare this matrix's 0th column with.</param>
		/// <param name="rhs_column_1_">Register to compare this matrix's 1st column with.</param>
		/// <param name="rhs_column_2_">Register to compare this matrix's 2nd column with.</param>
		/// <param name="rhs_column_3_">Register to compare this matrix's 3rd column with.</param>
		/// <returns>True if all comparisons between this matrix's elements and those of the respective passed columns returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAllLess(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			__m128 cmp_mask_ = _mm_cmplt_ps(column0, rhs_column_0_);
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmplt_ps(column1, rhs_column_1_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmplt_ps(column2, rhs_column_2_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmplt_ps(column3, rhs_column_3_));
			return _mm_movemask_ps(cmp_mask_) == EmuSIMD::make_movemask<__m128, true, true, true, true>::value;
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed column register. </para>
		/// <para> If all elements are less than their respective rhs values, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_all_columns_">Register to compare all of this matrix's columns with.</param>
		/// <returns>True if all comparisons between this matrix's elements and those of the passed register returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAllLess(__m128 rhs_all_columns_) const
		{
			__m128 cmp_mask_ = _mm_cmplt_ps(column0, rhs_all_columns_);
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmplt_ps(column1, rhs_all_columns_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmplt_ps(column2, rhs_all_columns_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmplt_ps(column3, rhs_all_columns_));
			return _mm_movemask_ps(cmp_mask_) == EmuSIMD::make_movemask<__m128, true, true, true, true>::value;
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to those of the passed matrix. </para>
		/// <para> If all elements are less than their respective rhs values, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_">Matrix to compare all of this matrix's respective elements with.</param>
		/// <returns>True if all comparisons between this matrix's elements and those of the passed matrix returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAllLess(const FastMatrix4x4f_CM& rhs_) const
		{
			return CmpAllLess(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed value. </para>
		/// <para> If all elements are less than the rhs value, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare all of this matrix's elements with. Must be convertible to float.</param>
		/// <returns>True if all comparisons between this matrix's elements and the passed value; otherwise false.</returns>
		template<typename Rhs_, typename RequiresRhsConvertibleToFloat = std::enable_if_t<std::is_convertible_v<Rhs_, float>>>
		[[nodiscard]] inline bool CmpAllLess(const Rhs_& rhs_) const
		{
			return CmpAllLess(_mm_set1_ps(static_cast<float>(rhs_)));
		}

		/// <summary>
		/// <para> Compares all columns of this matrix to the respective passed column registers. </para>
		/// <para> If all elements are greater than or equal to their respective rhs values, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare this matrix's 0th column with.</param>
		/// <param name="rhs_column_1_">Register to compare this matrix's 1st column with.</param>
		/// <param name="rhs_column_2_">Register to compare this matrix's 2nd column with.</param>
		/// <param name="rhs_column_3_">Register to compare this matrix's 3rd column with.</param>
		/// <returns>True if all comparisons between this matrix's elements and those of the respective passed columns returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAllGreaterEqual(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			__m128 cmp_mask_ = _mm_cmpge_ps(column0, rhs_column_0_);
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpge_ps(column1, rhs_column_1_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpge_ps(column2, rhs_column_2_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpge_ps(column3, rhs_column_3_));
			return _mm_movemask_ps(cmp_mask_) == EmuSIMD::make_movemask<__m128, true, true, true, true>::value;
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed column register. </para>
		/// <para> If all elements are greater than or equal to their respective rhs values, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_all_columns_">Register to compare all of this matrix's columns with.</param>
		/// <returns>True if all comparisons between this matrix's elements and those of the passed register returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAllGreaterEqual(__m128 rhs_all_columns_) const
		{
			__m128 cmp_mask_ = _mm_cmpge_ps(column0, rhs_all_columns_);
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpge_ps(column1, rhs_all_columns_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpge_ps(column2, rhs_all_columns_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmpge_ps(column3, rhs_all_columns_));
			return _mm_movemask_ps(cmp_mask_) == EmuSIMD::make_movemask<__m128, true, true, true, true>::value;
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to those of the passed matrix. </para>
		/// <para> If all elements are greater than or equal to their respective rhs values, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_">Matrix to compare all of this matrix's respective elements with.</param>
		/// <returns>True if all comparisons between this matrix's elements and those of the passed matrix returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAllGreaterEqual(const FastMatrix4x4f_CM& rhs_) const
		{
			return CmpAllGreaterEqual(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed value. </para>
		/// <para> If all elements are greater than or equal to the rhs value, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare all of this matrix's elements with. Must be convertible to float.</param>
		/// <returns>True if all comparisons between this matrix's elements and the passed value; otherwise false.</returns>
		template<typename Rhs_, typename RequiresRhsConvertibleToFloat = std::enable_if_t<std::is_convertible_v<Rhs_, float>>>
		[[nodiscard]] inline bool CmpAllGreaterEqual(const Rhs_& rhs_) const
		{
			return CmpAllGreaterEqual(_mm_set1_ps(static_cast<float>(rhs_)));
		}

		/// <summary>
		/// <para> Compares all columns of this matrix to the respective passed column registers. </para>
		/// <para> If all elements are less than or equal to their respective rhs values, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_column_0_">Register to compare this matrix's 0th column with.</param>
		/// <param name="rhs_column_1_">Register to compare this matrix's 1st column with.</param>
		/// <param name="rhs_column_2_">Register to compare this matrix's 2nd column with.</param>
		/// <param name="rhs_column_3_">Register to compare this matrix's 3rd column with.</param>
		/// <returns>True if all comparisons between this matrix's elements and those of the respective passed columns returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAllLessEqual(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			__m128 cmp_mask_ = _mm_cmple_ps(column0, rhs_column_0_);
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmple_ps(column1, rhs_column_1_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmple_ps(column2, rhs_column_2_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmple_ps(column3, rhs_column_3_));
			return _mm_movemask_ps(cmp_mask_) == EmuSIMD::make_movemask<__m128, true, true, true, true>::value;
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed column register. </para>
		/// <para> If all elements are less than or equal to their respective rhs values, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_all_columns_">Register to compare all of this matrix's columns with.</param>
		/// <returns>True if all comparisons between this matrix's elements and those of the passed register returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAllLessEqual(__m128 rhs_all_columns_) const
		{
			__m128 cmp_mask_ = _mm_cmple_ps(column0, rhs_all_columns_);
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmple_ps(column1, rhs_all_columns_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmple_ps(column2, rhs_all_columns_));
			cmp_mask_ = _mm_and_ps(cmp_mask_, _mm_cmple_ps(column3, rhs_all_columns_));
			return _mm_movemask_ps(cmp_mask_) == EmuSIMD::make_movemask<__m128, true, true, true, true>::value;
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to those of the passed matrix. </para>
		/// <para> If all elements are less than or equal to their respective rhs values, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_">Matrix to compare all of this matrix's respective elements with.</param>
		/// <returns>True if all comparisons between this matrix's elements and those of the passed matrix returned true; otherwise false.</returns>
		[[nodiscard]] inline bool CmpAllLessEqual(const FastMatrix4x4f_CM& rhs_) const
		{
			return CmpAllLessEqual(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary>
		/// <para> Compares all columns of this matrix to the passed value. </para>
		/// <para> If all elements are less than or equal to the rhs value, this function will return true; otherwise, it will be false. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare all of this matrix's elements with. Must be convertible to float.</param>
		/// <returns>True if all comparisons between this matrix's elements and the passed value; otherwise false.</returns>
		template<typename Rhs_, typename RequiresRhsConvertibleToFloat = std::enable_if_t<std::is_convertible_v<Rhs_, float>>>
		[[nodiscard]] inline bool CmpAllLessEqual(const Rhs_& rhs_) const
		{
			return CmpAllLessEqual(_mm_set1_ps(static_cast<float>(rhs_)));
		}
#pragma endregion

#pragma region CONST_OPERATORS
		[[nodiscard]] inline bool operator==(const FastMatrix4x4f_CM& rhs_) const
		{
			return CmpAllEqual(rhs_);
		}

		[[nodiscard]] inline bool operator!=(const FastMatrix4x4f_CM& rhs_) const
		{
			return CmpAnyNotEqual(rhs_);
		}

		[[nodiscard]] inline FastMatrix4x4f_CM operator+(const FastMatrix4x4f_CM& rhs_) const
		{
			return Add(rhs_);
		}

		[[nodiscard]] inline FastMatrix4x4f_CM operator-(const FastMatrix4x4f_CM& rhs_) const
		{
			return Subtract(rhs_);
		}
		[[nodiscard]] inline FastMatrix4x4f_CM operator-() const
		{
			return Negate();
		}

		[[nodiscard]] inline FastMatrix4x4f_CM operator*(const FastMatrix4x4f_CM& rhs_) const
		{
			return Multiply(rhs_);
		}
		template<typename T_, typename RequiresTConvertibleToFloat = std::enable_if_t<std::is_convertible_v<T_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM operator*(const T_& rhs_) const
		{
			return MultiplyBasic<T_>(rhs_);
		}

		[[nodiscard]] inline FastMatrix4x4f_CM operator/(const FastMatrix4x4f_CM& rhs_) const
		{
			return DivideBasic(rhs_);
		}
		template<typename T_, typename RequiresTConvertibleToFloat = std::enable_if_t<std::is_convertible_v<T_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM operator/(const T_& rhs_) const
		{
			return DivideBasic<T_>(rhs_);
		}

		[[nodiscard]] inline FastMatrix4x4f_CM operator%(const FastMatrix4x4f_CM& rhs_) const
		{
			return ModBasic(rhs_);
		}
		template<typename T_, typename RequiresTConvertibleToFloat = std::enable_if_t<std::is_convertible_v<T_, float>>>
		[[nodiscard]] inline FastMatrix4x4f_CM operator%(const T_& rhs_) const
		{
			return ModBasic<T_>(rhs_);
		}

		[[nodiscard]] inline FastMatrix4x4f_CM operator&(float rhs_) const
		{
			return And(rhs_);
		}
		[[nodiscard]] inline FastMatrix4x4f_CM operator&(const FastMatrix4x4f_CM& rhs_) const
		{
			return And(rhs_);
		}

		[[nodiscard]] inline FastMatrix4x4f_CM operator|(float rhs_) const
		{
			return Or(rhs_);
		}
		[[nodiscard]] inline FastMatrix4x4f_CM operator|(const FastMatrix4x4f_CM& rhs_) const
		{
			return Or(rhs_);
		}

		[[nodiscard]] inline FastMatrix4x4f_CM operator^(float rhs_) const
		{
			return Xor(rhs_);
		}
		[[nodiscard]] inline FastMatrix4x4f_CM operator^(const FastMatrix4x4f_CM& rhs_) const
		{
			return Xor(rhs_);
		}

		[[nodiscard]] inline FastMatrix4x4f_CM operator~() const
		{
			return Not();
		}

		[[nodiscard]] inline bool operator!() const
		{
			return
			(
				_mm_movemask_ps(column0) == 0 &&
				_mm_movemask_ps(column1) == 0 &&
				_mm_movemask_ps(column2) == 0 &&
				_mm_movemask_ps(column3) == 0
			);
		}
#pragma endregion

#pragma region NON_CONST_OPERATORS
		inline FastMatrix4x4f_CM& operator=(const FastMatrix4x4f_CM& rhs_)
		{
			column0 = rhs_.column0;
			column1 = rhs_.column1;
			column2 = rhs_.column2;
			column3 = rhs_.column3;
			return *this;
		}
		template<std::size_t NumColumns_, std::size_t NumRows_, typename in_contained_type, bool InColumnMajor_>
		inline FastMatrix4x4f_CM& operator=(const EmuMath::Matrix<NumColumns_, NumRows_, in_contained_type, InColumnMajor_>& rhs_)
		{
			column0 = _mm_set_ps
			(
				EmuMath::Helpers::MatrixGetTheoretical<0, 0>(rhs_),
				EmuMath::Helpers::MatrixGetTheoretical<0, 1>(rhs_),
				EmuMath::Helpers::MatrixGetTheoretical<0, 2>(rhs_),
				EmuMath::Helpers::MatrixGetTheoretical<0, 3>(rhs_)
			);
			column1 = _mm_set_ps
			(
				EmuMath::Helpers::MatrixGetTheoretical<1, 0>(rhs_),
				EmuMath::Helpers::MatrixGetTheoretical<1, 1>(rhs_),
				EmuMath::Helpers::MatrixGetTheoretical<1, 2>(rhs_),
				EmuMath::Helpers::MatrixGetTheoretical<1, 3>(rhs_)
			);
			column2 = _mm_set_ps
			(
				EmuMath::Helpers::MatrixGetTheoretical<2, 0>(rhs_),
				EmuMath::Helpers::MatrixGetTheoretical<2, 1>(rhs_),
				EmuMath::Helpers::MatrixGetTheoretical<2, 2>(rhs_),
				EmuMath::Helpers::MatrixGetTheoretical<2, 3>(rhs_)
			);
			column3 = _mm_set_ps
			(
				EmuMath::Helpers::MatrixGetTheoretical<3, 0>(rhs_),
				EmuMath::Helpers::MatrixGetTheoretical<3, 1>(rhs_),
				EmuMath::Helpers::MatrixGetTheoretical<3, 2>(rhs_),
				EmuMath::Helpers::MatrixGetTheoretical<3, 3>(rhs_)
			);
			return *this;
		}
		template<>
		inline FastMatrix4x4f_CM& operator=(const EmuMath::Matrix<4, 4, float, true>& rhs_)
		{
			column0 = _mm_load_ps(rhs_.at<0>().data());
			column1 = _mm_load_ps(rhs_.at<1>().data());
			column2 = _mm_load_ps(rhs_.at<2>().data());
			column3 = _mm_load_ps(rhs_.at<3>().data());
			return *this;
		}

		inline FastMatrix4x4f_CM& operator+=(const FastMatrix4x4f_CM& rhs_)
		{
			return operator=(Add(rhs_));
		}

		inline FastMatrix4x4f_CM& operator-=(const FastMatrix4x4f_CM& rhs_)
		{
			return operator=(Subtract(rhs_));
		}

		inline FastMatrix4x4f_CM& operator*=(const FastMatrix4x4f_CM& rhs_)
		{
			return operator=(Multiply(rhs_));
		}
		template<typename T_, typename RequiresTConvertibleToFloat = std::enable_if_t<std::is_convertible_v<T_, float>>>
		inline FastMatrix4x4f_CM& operator*=(const T_& rhs_)
		{
			return operator=(MultiplyBasic<T_>(rhs_));
		}

		inline FastMatrix4x4f_CM& operator/=(const FastMatrix4x4f_CM& rhs_)
		{
			return operator=(DivideBasic(rhs_));
		}
		template<typename T_, typename RequiresTConvertibleToFloat = std::enable_if_t<std::is_convertible_v<T_, float>>>
		inline FastMatrix4x4f_CM& operator/=(const T_& rhs_)
		{
			return operator=(DivideBasic<T_>(rhs_));
		}

		inline FastMatrix4x4f_CM& operator%=(const FastMatrix4x4f_CM& rhs_)
		{
			return operator=(ModBasic(rhs_));
		}
		template<typename T_, typename RequiresTConvertibleToFloat = std::enable_if_t<std::is_convertible_v<T_, float>>>
		inline FastMatrix4x4f_CM& operator%=(const T_& rhs_)
		{
			return operator=(ModBasic<T_>(rhs_));
		}

		inline FastMatrix4x4f_CM& operator&=(float rhs_)
		{
			return operator=(And(rhs_));
		}
		inline FastMatrix4x4f_CM& operator&=(const FastMatrix4x4f_CM& rhs_)
		{
			return operator=(And(rhs_));
		}

		inline FastMatrix4x4f_CM& operator|=(float rhs_)
		{
			return operator=(Or(rhs_));
		}
		inline FastMatrix4x4f_CM& operator|=(const FastMatrix4x4f_CM& rhs_)
		{
			return operator=(Or(rhs_));
		}

		inline FastMatrix4x4f_CM& operator^=(float rhs_)
		{
			return operator=(Xor(rhs_));
		}
		inline FastMatrix4x4f_CM& operator^=(const FastMatrix4x4f_CM& rhs_)
		{
			return operator=(Xor(rhs_));
		}
#pragma endregion

#pragma region MATRIX_OPERATIONS
		/// <summary> Transposes this matrix, effectively turning columns into rows and vice versa. </summary>
		/// <returns>Transposed form of this matrix.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Transpose() const
		{
			// Preliminary shuffles to allow all resulting transposed rows to be created
			// --- We do this instead of 4 calls to GetRow to complete the operation in 8 shuffles instead of 12.
			__m128 c0r0_c0r1_c1r0_c1r1_ = EmuSIMD::shuffle<0, 1, 0, 1>(column0, column1);
			__m128 c2r0_c2r1_c3r0_c3r1_ = EmuSIMD::shuffle<0, 1, 0, 1>(column2, column3);
			__m128 c0r2_c0r3_c1r2_c1r3_ = EmuSIMD::shuffle<2, 3, 2, 3>(column0, column1);
			__m128 c2r2_c2r3_c3r2_c3r3_ = EmuSIMD::shuffle<2, 3, 2, 3>(column2, column3);
			
			return FastMatrix4x4f_CM
			(
				EmuSIMD::shuffle<0, 2, 0, 2>(c0r0_c0r1_c1r0_c1r1_, c2r0_c2r1_c3r0_c3r1_),
				EmuSIMD::shuffle<1, 3, 1, 3>(c0r0_c0r1_c1r0_c1r1_, c2r0_c2r1_c3r0_c3r1_),
				EmuSIMD::shuffle<0, 2, 0, 2>(c0r2_c0r3_c1r2_c1r3_, c2r2_c2r3_c3r2_c3r3_),
				EmuSIMD::shuffle<1, 3, 1, 3>(c0r2_c0r3_c1r2_c1r3_, c2r2_c2r3_c3r2_c3r3_)
			);
		}

		/// <summary> Provides a fast vector containing the main diagonal of this matrix within its data. </summary>
		/// <returns>Main diagonal of this matrix represented as a FastVector4f.</returns>
		[[nodiscard]] inline EmuMath::FastVector4f MainDiagonal() const
		{
			__m128 out_01_ = EmuSIMD::shuffle<0, 0, 1, 1>(column0, column1);
			__m128 out_23_ = EmuSIMD::shuffle<2, 2, 3, 3>(column2, column3);
			return EmuMath::FastVector4f(EmuSIMD::shuffle<0, 2, 0, 2>(out_01_, out_23_));
		}

		/// <summary> Calculates the trace of this matrix (the sum of all elements along its main diagonal). </summary>
		/// <returns>Trace of this matrix represented as a scalar.</returns>
		[[nodiscard]] inline float Trace() const
		{
			return MainDiagonal().HorizontalSum();
		}

		[[nodiscard]] inline float Determinant() const
		{
			return EmuSIMD::horizontal_sum_scalar<float>(_mm_mul_ps(GetRow<0>(), Cofactors<true>().column0));
		}

		/// <summary> 
		/// <para> Returns a copy of a submatrix within this matrix, excluding the column and row at the provided respective indices. </para>
		/// <para> The submatrix will be contained in the output's first 3x3 segment. The final column and the final row of the output matrix will be all 0s. </para>
		/// </summary>
		/// <returns>Submatrix excluding the provided column and row within this matrix, with the final column and final row all set to 0.</returns>
		template<std::size_t ExcludeColumn_, std::size_t ExcludeRow_>
		[[nodiscard]] inline FastMatrix4x4f_CM ExclusiveSubmatrix() const
		{
			if constexpr (_assert_valid_index<ExcludeColumn_, ExcludeRow_>())
			{
				__m128 mask_ = EmuSIMD::index_mask_m128<true, true, true, false>();
				if constexpr (ExcludeColumn_ == 0)
				{
					return FastMatrix4x4f_CM
					(
						_mm_and_ps(mask_, _index_excluding_shuffle<ExcludeRow_>(column1)),
						_mm_and_ps(mask_, _index_excluding_shuffle<ExcludeRow_>(column2)),
						_mm_and_ps(mask_, _index_excluding_shuffle<ExcludeRow_>(column3)),
						_mm_setzero_ps()
					);
				}
				else if constexpr (ExcludeColumn_ == 1)
				{
					return FastMatrix4x4f_CM
					(
						_mm_and_ps(mask_, _index_excluding_shuffle<ExcludeRow_>(column0)),
						_mm_and_ps(mask_, _index_excluding_shuffle<ExcludeRow_>(column2)),
						_mm_and_ps(mask_, _index_excluding_shuffle<ExcludeRow_>(column3)),
						_mm_setzero_ps()
					);
				}
				else if constexpr (ExcludeColumn_ == 2)
				{
					return FastMatrix4x4f_CM
					(
						_mm_and_ps(mask_, _index_excluding_shuffle<ExcludeRow_>(column0)),
						_mm_and_ps(mask_, _index_excluding_shuffle<ExcludeRow_>(column1)),
						_mm_and_ps(mask_, _index_excluding_shuffle<ExcludeRow_>(column3)),
						_mm_setzero_ps()
					);
				}
				else
				{
					return FastMatrix4x4f_CM
					(
						_mm_and_ps(mask_, _index_excluding_shuffle<ExcludeRow_>(column0)),
						_mm_and_ps(mask_, _index_excluding_shuffle<ExcludeRow_>(column1)),
						_mm_and_ps(mask_, _index_excluding_shuffle<ExcludeRow_>(column2)),
						_mm_setzero_ps()
					);
				}
			}
			else
			{
				static_assert(false, "Invalid column and/or row index passed to EmuMath::FastMatrix4x4f_CM::ExclusiveSubmatrix.");
			}
		}

		/// <summary> 
		/// <para> Calculates the matrix of minors to this matrix. </para>
		/// <para> Automatically applies a transpose without any extra operations if TransposeOutput_ is true, defaulting to false. </para>
		/// </summary>
		/// <returns>Matrix of minors to this matrix, which can be summarised as a matrix of determinants to all respective exclusive submatrices within this matrix.</returns>
		template<bool TransposeOutput_ = false>
		[[nodiscard]] inline FastMatrix4x4f_CM Minors() const
		{
			// Shuffled columns to store 2x2 submatrices within singular SIMD registers
			__m128 submat_c01_r01_ = EmuSIMD::shuffle<0, 1, 0, 1>(column0, column1);
			__m128 submat_c01_r23_ = EmuSIMD::shuffle<2, 3, 2, 3>(column0, column1);
			__m128 submat_c23_r01_ = EmuSIMD::shuffle<0, 1, 0, 1>(column2, column3);
			__m128 submat_c23_r23_ = EmuSIMD::shuffle<2, 3, 2, 3>(column2, column3);

			// Calculate determinants based on this matrix's columns with remaining 2x2 submatrices
			// --- Each determinant will need to be used for a blanket mult, so each value populates a full register
			__m128 determinants_ = _mm_sub_ps
			(
				_mm_mul_ps(EmuSIMD::shuffle<0, 2, 0, 2>(column0, column2), EmuSIMD::shuffle<1, 3, 1, 3>(column1, column3)),
				_mm_mul_ps(EmuSIMD::shuffle<1, 3, 1, 3>(column0, column2), EmuSIMD::shuffle<0, 2, 0, 2>(column1, column3))
			);

			// Multiply adjugates of the lhs submatrices by the rhs submatrices (non-adjugate)
			__m128 c23r23_mult_c01r23_ = EmuSIMD::matrix_2x2_multiply_adj_norm_cm(submat_c23_r23_, submat_c01_r23_);
			__m128 c01r01_mult_c23r01_ = EmuSIMD::matrix_2x2_multiply_adj_norm_cm(submat_c01_r01_, submat_c23_r01_);

			// Calculate registers for output
			// --- Registers with matching cxxyy names are shuffled together to form individual output columns if not transposed
			// --- Registers with matching rxxyy names are shuffled together to form individual output columns if transposed
			__m128 out_c1100_r1010_ = _mm_sub_ps
			(
				_mm_mul_ps(EmuSIMD::shuffle<3>(determinants_), submat_c01_r01_),
				EmuSIMD::matrix_2x2_multiply_cm(submat_c23_r01_, c23r23_mult_c01r23_)
			);
			__m128 out_c1100_r3232_ = _mm_sub_ps
			(
				_mm_mul_ps(EmuSIMD::shuffle<2>(determinants_), submat_c01_r23_),
				EmuSIMD::matrix_2x2_multiply_norm_adj_cm(submat_c23_r23_, c01r01_mult_c23r01_)
			);
			__m128 out_c3322_r1010_ = _mm_sub_ps
			(
				_mm_mul_ps(EmuSIMD::shuffle<1>(determinants_), submat_c23_r01_),
				EmuSIMD::matrix_2x2_multiply_norm_adj_cm(submat_c01_r01_, c23r23_mult_c01r23_)
			);
			__m128 out_c3322_r3232_ = _mm_sub_ps
			(
				_mm_mul_ps(EmuSIMD::shuffle<0>(determinants_), submat_c23_r23_),
				EmuSIMD::matrix_2x2_multiply_cm(submat_c01_r23_, c01r01_mult_c23r01_)
			);

			// Output final shuffles, performing transpose with output shuffles if desired
			if constexpr (TransposeOutput_)
			{
				return FastMatrix4x4f_CM
				(
					EmuSIMD::shuffle<3, 1, 3, 1>(out_c1100_r1010_, out_c3322_r1010_),
					EmuSIMD::shuffle<2, 0, 2, 0>(out_c1100_r1010_, out_c3322_r1010_),
					EmuSIMD::shuffle<3, 1, 3, 1>(out_c1100_r3232_, out_c3322_r3232_),
					EmuSIMD::shuffle<2, 0, 2, 0>(out_c1100_r3232_, out_c3322_r3232_)
				);
			}
			else
			{
				return FastMatrix4x4f_CM
				(
					EmuSIMD::shuffle<3, 2, 3, 2>(out_c1100_r1010_, out_c1100_r3232_),
					EmuSIMD::shuffle<1, 0, 1, 0>(out_c1100_r1010_, out_c1100_r3232_),
					EmuSIMD::shuffle<3, 2, 3, 2>(out_c3322_r1010_, out_c3322_r3232_),
					EmuSIMD::shuffle<1, 0, 1, 0>(out_c3322_r1010_, out_c3322_r3232_)
				);
			}
		}

		/// <summary> 
		/// <para> Calculates the matrix of cofactors to this matrix. </para>
		/// <para> Automatically applies a transpose without any extra operations if TransposeOutput_ is true, defaulting to false. </para>
		/// </summary>
		/// <returns>Matrix of cofactors to this matrix.</returns>
		template<bool TransposeOutput_ = false>
		[[nodiscard]] inline FastMatrix4x4f_CM Cofactors() const
		{
			const FastMatrix4x4f_CM minors_ = Minors<TransposeOutput_>();
			__m128 mults_odd_column_ = _mm_set_ps(1.0f, -1.0f, 1.0f, -1.0f);
			__m128 mults_even_column_ = EmuSIMD::shuffle<1, 0, 1, 0>(mults_odd_column_);
			return FastMatrix4x4f_CM
			(
				_mm_mul_ps(minors_.column0, mults_even_column_),
				_mm_mul_ps(minors_.column1, mults_odd_column_),
				_mm_mul_ps(minors_.column2, mults_even_column_),
				_mm_mul_ps(minors_.column3, mults_odd_column_)
			);
		}

		/// <summary> 
		/// <para> Calculates the adjugate of this matrix. </para>
		/// <para> Effectively shorthand and clearer semantics for Cofactors&lt;true&gt;. </para>
		/// </summary>
		/// <returns>Adjugate of this matrix, which can be summarised as the tranpose of its matrix of cofactors.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Adjugate() const
		{
			return Cofactors<true>();
		}

		/// <summary> 
		/// <para> Calculates the inverse to this matrix. </para>
		/// <para> This function assumes that this matrix does have an inverse. If it is uncertain that this matrix has an inverse, use TryInverse instead.</para>
		/// </summary>
		/// <param name="out_determinant_">Optional reference to output this matrix's determinant via.</param>
		/// <returns>The inverse to this matrix, as long as this matrix satisfies the above assumptions.</returns>
		[[nodiscard]] inline FastMatrix4x4f_CM Inverse() const
		{
			FastMatrix4x4f_CM adjugate_ = Cofactors<true>();
			__m128 determinant_reciprocal_ = _mm_set1_ps(1.0f / EmuSIMD::horizontal_sum_scalar<float>(_mm_mul_ps(adjugate_.column0, GetRow<0>())));
			return FastMatrix4x4f_CM
			(
				_mm_mul_ps(adjugate_.column0, determinant_reciprocal_),
				_mm_mul_ps(adjugate_.column1, determinant_reciprocal_),
				_mm_mul_ps(adjugate_.column2, determinant_reciprocal_),
				_mm_mul_ps(adjugate_.column3, determinant_reciprocal_)
			);
		}
		[[nodiscard]] inline FastMatrix4x4f_CM Inverse(float& out_determinant_) const
		{
			FastMatrix4x4f_CM adjugate_ = Cofactors<true>();
			out_determinant_ = EmuSIMD::horizontal_sum_scalar<float>(_mm_mul_ps(adjugate_.column0, GetRow<0>()));
			__m128 determinant_reciprocal_ = _mm_set1_ps(1.0f / out_determinant_);
			return FastMatrix4x4f_CM
			(
				_mm_mul_ps(adjugate_.column0, determinant_reciprocal_),
				_mm_mul_ps(adjugate_.column1, determinant_reciprocal_),
				_mm_mul_ps(adjugate_.column2, determinant_reciprocal_),
				_mm_mul_ps(adjugate_.column3, determinant_reciprocal_)
			);
		}

		/// <summary>
		/// <para> Calculates the inverse of this matrix if it has an inverse, returning a boolean to indicate success. </para>
		/// <para>
		///		If it is unknown whether or not this matrix has an inverse it is recommended to use this function, as a non-try inverse call 
		///		does not have safety checks, resulting in an inaccurate output matrix where the matrix does not have an inverse.
		/// </para>
		/// </summary>
		/// <param name="out_inverse_">Reference to a matrix to output the inverse to if this matrix has an inverse. Only used if this function returns true.</param>
		/// <param name="out_determinant_">Reference to output this matrix's determinant to. Always output to, even when this function returns false.</param>
		/// <returns>Boolean indicating if this matrix has an inverse and that said inverse was calculated.</returns>
		inline bool TryInverse(FastMatrix4x4f_CM& out_inverse_) const
		{
			float dummy_float_;
			return TryInverse(out_inverse_, dummy_float_);
		}
		inline bool TryInverse(FastMatrix4x4f_CM& out_inverse_, float& out_determinant_) const
		{
			FastMatrix4x4f_CM adjugate_ = Cofactors<true>();
			out_determinant_ = EmuSIMD::horizontal_sum_scalar<float>(_mm_mul_ps(adjugate_.column0, GetRow<0>()));
			if (out_determinant_ != 0.0f)
			{
				__m128 determinant_reciprocal_ = _mm_set1_ps(1.0f / out_determinant_);
				out_inverse_.column0 = _mm_mul_ps(adjugate_.column0, determinant_reciprocal_);
				out_inverse_.column1 = _mm_mul_ps(adjugate_.column1, determinant_reciprocal_);
				out_inverse_.column2 = _mm_mul_ps(adjugate_.column2, determinant_reciprocal_);
				out_inverse_.column3 = _mm_mul_ps(adjugate_.column3, determinant_reciprocal_);
				return true;
			}
			else
			{
				return false;
			}
		}
#pragma endregion

#pragma region STATIC_CONSTANTS
		/// <summary> Creates a 4x4 column-major identity matrix, which is all 0 except for its main diagonal (top left to bottom right), which is all 1. </summary>
		/// <returns>4x4 column-major identity matrix.</returns>
		[[nodiscard]] static inline FastMatrix4x4f_CM Identity()
		{
			return FastMatrix4x4f_CM
			(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			);
		}
#pragma endregion

#pragma region STATIC_TRANSFORMATIONS
		/// <summary>
		///		Creates a 4x4 column-major matrix which may be used to perform a translation of x_ in the X-direction, y_ in the Y-direction, and z_ in the Z-direction.
		/// </summary>
		/// <typeparam name="X_">Type used for the passed translation in the X-direction.</typeparam>
		/// <typeparam name="Y_">Type used for the passed translation in the Y-direction.</typeparam>
		/// <typeparam name="Z_">Type used for the passed translation in the Z-direction.</typeparam>
		/// <param name="x_">Translation in the X-direction.</param>
		/// <param name="y_">Translation in the Y-direction.</param>
		/// <param name="z_">Translation in the Z-direction.</param>
		/// <returns>4x4 column-major SIMD matrix that may be used to translate by the specified amounts in respective dimensions.</returns>
		template<typename X_, typename Y_, typename Z_>
		[[nodiscard]] static inline FastMatrix4x4f_CM Translation(const X_& x_, const Y_& y_, const Z_& z_)
		{
			return FastMatrix4x4f_CM
			(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				x_,   y_,   z_,   1.0f
			);
		}

		/// <summary>
		///		Creates a 4x4 column-major matrix which may be used to perform a scale of x_ in the X-dimension, y_ in the Y-dimension, and z_ in the Z-dimension.
		/// </summary>
		/// <typeparam name="X_">Type used for the passed scale in the X-dimension.</typeparam>
		/// <typeparam name="Y_">Type used for the passed scale in the Y-dimension.</typeparam>
		/// <typeparam name="Z_">Type used for the passed scale in the Z-dimension.</typeparam>
		/// <param name="x_">Scale in the X-dimension.</param>
		/// <param name="y_">Scale in the Y-dimension.</param>
		/// <param name="z_">Scale in the Z-dimension.</param>
		/// <returns>4x4 column-major SIMD matrix that may be used to scale by the specified amounts in respective dimensions.</returns>
		template<typename X_, typename Y_, typename Z_>
		[[nodiscard]] static inline FastMatrix4x4f_CM Scale(const X_& x_, const Y_& y_, const Z_& z_)
		{
			return FastMatrix4x4f_CM
			(
				x_,   0.0f, 0.0f, 0.0f,
				0.0f, y_,   0.0f, 0.0f,
				0.0f, 0.0f, z_,   0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			);
		}

		/// <summary>
		/// <para> Creates a 4x4 column-major matrix which may used to perform about the X-axis by an angle of rot_x_. </para>
		/// <para> If the template argument RotIsRads_ is true, rot_x_ will be interpreted as radians; otherwise, rot_x_ will be interpreted as degrees. </para>
		/// </summary>
		/// <typeparam name="RotX_">Type used to provide the angle to rotate.</typeparam>
		/// <param name="rot_x_">Angle to rotate in either radians or degrees, depending on the RotIsRads_ template argument.</param>
		/// <returns>
		///		4x4 column-major SIMD matrix that may be used to rotate about the X-axis by rot_x_ radians or degrees, depending on the RotIsRads_ template argument.
		/// </returns>
		template<bool RotIsRads_ = true, typename RotX_>
		[[nodiscard]] static inline FastMatrix4x4f_CM RotationX(const RotX_& rot_x_)
		{
			if constexpr(RotIsRads_)
			{
				float cos_x_ = static_cast<float>(EmuCore::do_cos<RotX_>()(rot_x_));
				float sin_x_ = static_cast<float>(EmuCore::do_sin<RotX_>()(rot_x_));
				return FastMatrix4x4f_CM
				(
					1.0f, 0.0f,   0.0f,    0.0f,
					0.0f, cos_x_, -sin_x_, 0.0f,
					0.0f, sin_x_, cos_x_,  0.0f,
					0.0f, 0.0f,   0.0f,    1.0f
				);
			}
			else
			{
				using rot_x_fp = typename EmuCore::TMPHelpers::first_floating_point_t<RotX_, float>;
				return RotationX<true>(EmuCore::Pi::DegsToRads(static_cast<rot_x_fp>(rot_x_)));
			}
		}

		/// <summary>
		/// <para> Creates a 4x4 column-major matrix which may used to perform about the Y-axis by an angle of rot_y_. </para>
		/// <para> If the template argument RotIsRads_ is true, rot_y_ will be interpreted as radians; otherwise, rot_y_ will be interpreted as degrees. </para>
		/// </summary>
		/// <typeparam name="RotY_">Type used to provide the angle to rotate.</typeparam>
		/// <param name="rot_y_">Angle to rotate in either radians or degrees, depending on the RotIsRads_ template argument.</param>
		/// <returns>
		///		4x4 column-major SIMD matrix that may be used to rotate about the Y-axis by rot_y_ radians or degrees, depending on the RotIsRads_ template argument.
		/// </returns>
		template<bool RotIsRads_ = true, typename RotY_>
		[[nodiscard]] static inline FastMatrix4x4f_CM RotationY(const RotY_& rot_y_)
		{
			if constexpr(RotIsRads_)
			{
				float cos_y_ = static_cast<float>(EmuCore::do_cos<RotY_>()(rot_y_));
				float sin_y_ = static_cast<float>(EmuCore::do_sin<RotY_>()(rot_y_));
				return FastMatrix4x4f_CM
				(
					cos_y_,  0.0f, sin_y_, 0.0f,
					0.0f,    1.0f, 0.0f,   0.0f,
					-sin_y_, 0.0f, cos_y_, 0.0f,
					0.0f,    0.0f, 0.0f,   1.0f
				);
			}
			else
			{
				using rot_y_fp = typename EmuCore::TMPHelpers::first_floating_point_t<RotY_, float>;
				return RotationY<true>(EmuCore::Pi::DegsToRads(static_cast<rot_y_fp>(rot_y_)));
			}
		}

		/// <summary>
		/// <para> Creates a 4x4 column-major matrix which may used to perform about the Z-axis by an angle of rot_z_. </para>
		/// <para> If the template argument RotIsRads_ is true, rot_z_ will be interpreted as radians; otherwise, rot_z_ will be interpreted as degrees. </para>
		/// </summary>
		/// <typeparam name="RotZ_">Type used to provide the angle to rotate.</typeparam>
		/// <param name="rot_z_">Angle to rotate in either radians or degrees, depending on the RotIsRads_ template argument.</param>
		/// <returns>
		///		4x4 column-major SIMD matrix that may be used to rotate about the Z-axis by rot_z_ radians or degrees, depending on the RotIsRads_ template argument.
		/// </returns>
		template<bool RotIsRads_ = true, typename RotZ_>
		[[nodiscard]] static inline FastMatrix4x4f_CM RotationZ(const RotZ_& rot_z_)
		{
			if constexpr(RotIsRads_)
			{
				float cos_z_ = static_cast<float>(EmuCore::do_cos<RotZ_>()(rot_z_));
				float sin_z_ = static_cast<float>(EmuCore::do_sin<RotZ_>()(rot_z_));
				return FastMatrix4x4f_CM
				(
					cos_z_,  sin_z_, 0.0f, 0.0f,
					-sin_z_, cos_z_, 0.0f, 0.0f,
					0.0f,    0.0f,   1.0f, 0.0f,
					0.0f,    0.0f,   0.0f, 1.0f
				);
			}
			else
			{
				using rot_z_fp = typename EmuCore::TMPHelpers::first_floating_point_t<RotZ_, float>;
				return RotationZ<true>(EmuCore::Pi::DegsToRads(static_cast<rot_z_fp>(rot_z_)));
			}
		}
#pragma endregion

#pragma region STATIC_PROJECTIONS
		/// <summary>
		/// <para> Creates a 4x4 column-major perspective projection matrix for right-handed coordinate systems, formed for Vulkan clipping space. </para>
		/// <para>
		///		Unless you know exactly what you are doing, it is recommended to use the 
		///		overload of this function which takes (fov_y_angle_, near_, far_, aspect_ratio_) arguments to calculate the clipping area edges for you.
		/// </para>
		/// </summary>
		/// <typeparam name="Near_">Type used to provide the near plane value.</typeparam>
		/// <typeparam name="Far_">Type used to provide the far plane value.</typeparam>
		/// <typeparam name="Left_">Type used to provide the left (low horizontal) edge value.</typeparam>
		/// <typeparam name="Right_">Type used to provide the right (high horizontal) edge value.</typeparam>
		/// <typeparam name="Bottom_">Type used to provide the bottom (low vertical) edge value.</typeparam>
		/// <typeparam name="Top_">Type used to provide the top (high vertical) edge value.</typeparam>
		/// <param name="near_">Near clipping plane to project items to. For correct behaviour, this should be greater than far_.</param>
		/// <param name="far_">Near clipping plane to project items to. For correct behaviour, this should be less than near_.</param>
		/// <param name="left_">Left (low horizontal) edge value for the projection area.</param>
		/// <param name="right_">Left (low horizontal) edge value for the projection area.</param>
		/// <param name="bottom_">Left (low horizontal) edge value for the projection area.</param>
		/// <param name="top_">Left (low horizontal) edge value for the projection area.</param>
		/// <returns>Right-handed perspective projection matrix formed for Vulkan clipping space.</returns>
		template<typename Near_, typename Far_, typename Left_, typename Right_, typename Bottom_, typename Top_>
		[[nodiscard]] static inline FastMatrix4x4f_CM PerspectiveRhVK
		(
			const Near_& near_,
			const Far_& far_,
			const Left_& left_,
			const Right_& right_,
			const Bottom_& bottom_,
			const Top_& top_
		)
		{
			// Process isn't particularly too vectorisable without adding a good few undesirable shuffles
			// --- Additionally, this way is generally 15-25% faster than DirectXMath's equivalent in tests in release with optimisations
			float right_plus_left_ = static_cast<float>(right_) + static_cast<float>(left_);
			float top_plus_bottom_ = static_cast<float>(top_) + static_cast<float>(bottom_);
			float right_minus_left_reciprocal_ = 1.0f / (static_cast<float>(right_) - static_cast<float>(left_));
			float top_minus_bottom_reciprocal_ = 1.0f / (static_cast<float>(top_) - static_cast<float>(bottom_));
			float near_double_ = static_cast<float>(near_); // Start as near_ copy so we can use the cast float
			float neg_far_minus_near_reciprocal_ = -(1.0f / (static_cast<float>(far_) - near_));
			float far_mult_near_ = static_cast<float>(far_) * near_;
			near_double_ *= 2.0f; // Apply deferred double

			float out_00_ = near_double_ * right_minus_left_reciprocal_; // (2 * near) / (right - left)
			float out_11_ = near_double_ * top_minus_bottom_reciprocal_; // (2 * near) / (top - bottom)
			float out_20_ = right_plus_left_ * right_minus_left_reciprocal_; // (right + left) / (right - left)
			float out_21_ = top_plus_bottom_ * top_minus_bottom_reciprocal_; // (top + bottom) / (top - bottom)
			float out_22_ = static_cast<float>(far_) * neg_far_minus_near_reciprocal_; // far / -(far - near)
			float out_32_ = far_mult_near_ * neg_far_minus_near_reciprocal_; // (far * near) / -(far - near)

			return FastMatrix4x4f_CM
			(
				out_00_, 0.0f,    0.0f,    0.0f,
				0.0f,    out_11_, 0.0f,    0.0f,
				out_20_, out_21_, out_22_, -1.0f,
				0.0f,    0.0f,    out_32_, 0.0f
			);
		}
		/// <summary>
		/// <para> Creates a 4x4 column-major perspective projection matrix for right-handed coordinate systems, formed for Vulkan clipping space. </para>
		/// </summary>
		/// <typeparam name="FovY_">Type used to provide the FOV y angle.</typeparam>
		/// <typeparam name="Near_">Type used to provide the near plane value.</typeparam>
		/// <typeparam name="Far_">Type used to provide the far plane value.</typeparam>
		/// <typeparam name="AspectRatio_">Type used to provide the aspect ratio.</typeparam>
		/// <param name="fov_y_angle_">
		///		Angle of the field-of-view in the y-axis. 
		///		May be in radians or degrees, and by default is interpreted as radians. To provide degrees, set the template argument FovIsRads_ to false.
		/// </param>
		/// <param name="near_">Near clipping plane to project items to. For correct behaviour, this should be greater than far_.</param>
		/// <param name="far_">Near clipping plane to project items to. For correct behaviour, this should be less than near_.</param>
		/// <param name="aspect_ratio_">Aspect ratio for the view represented as a scalar. Ratio is commonly (target_width / target_height).</param>
		/// <returns>Right-handed perspective projection matrix formed for Vulkan clipping space.</returns>
		template<bool FovIsRads_ = true, typename FovY_, typename Near_, typename Far_, typename AspectRatio_>
		[[nodiscard]] static inline FastMatrix4x4f_CM PerspectiveRhVK(const FovY_& fov_y_angle_, const Near_& near_, const Far_& far_, const AspectRatio_& aspect_ratio_)
		{
			using fov_y_fp = typename EmuCore::TMPHelpers::first_floating_point<FovY_, float>::type;
			if constexpr (!FovIsRads_)
			{
				return PerspectiveRhVK<true, fov_y_fp, Near_, Far_, AspectRatio_>
				(
					EmuCore::Pi::DegsToRads(static_cast<fov_y_fp>(fov_y_angle_)),
					near_,
					far_,
					aspect_ratio_
				);
			}
			else
			{
				float left_ = 0.0f, right_ = 0.0f, bottom_ = 0.0f, top_ = 0.0f;
				float scale_ = static_cast<float>(EmuCore::do_tan<fov_y_fp>()(static_cast<fov_y_fp>(fov_y_angle_) * fov_y_fp(0.5f)));
				scale_ *= static_cast<float>(near_);
				EmuMath::Helpers::_underlying_matrix_funcs::_calculate_matrix_perspective_edges_rads<AspectRatio_, float, float, float, float, float, float>
				(
					aspect_ratio_,
					scale_,
					left_,
					right_,
					bottom_,
					top_
				);
				return PerspectiveRhVK<Near_, Far_, float, float, float, float>(near_, far_, left_, right_, bottom_, top_);
			}
		}

		/// <summary>
		/// <para> Creates a 4x4 column-major orthographic projection matrix for right-handed coordinate systems, formed for Vulkan clipping space. </para>
		/// </summary>
		/// <typeparam name="Near_">Type used to provide the near plane value.</typeparam>
		/// <typeparam name="Far_">Type used to provide the far plane value.</typeparam>
		/// <typeparam name="Left_">Type used to provide the left (low horizontal) edge value.</typeparam>
		/// <typeparam name="Right_">Type used to provide the right (high horizontal) edge value.</typeparam>
		/// <typeparam name="Bottom_">Type used to provide the bottom (low vertical) edge value.</typeparam>
		/// <typeparam name="Top_">Type used to provide the top (high vertical) edge value.</typeparam>
		/// <param name="near_">Near clipping plane to project items to. For correct behaviour, this should be greater than far_.</param>
		/// <param name="far_">Near clipping plane to project items to. For correct behaviour, this should be less than near_.</param>
		/// <param name="left_">Left (low horizontal) edge value for the projection area.</param>
		/// <param name="right_">Left (low horizontal) edge value for the projection area.</param>
		/// <param name="bottom_">Left (low horizontal) edge value for the projection area.</param>
		/// <param name="top_">Left (low horizontal) edge value for the projection area.</param>
		/// <returns>Right-handed orthographic projection matrix formed for Vulkan clipping space.</returns>
		template<typename Left_, typename Right_, typename Bottom_, typename Top_, typename Near_, typename Far_>
		[[nodiscard]] static inline FastMatrix4x4f_CM OrthographicRhVK
		(
			const Left_& left_,
			const Right_& right_,
			const Bottom_& bottom_,
			const Top_& top_,
			const Near_& near_,
			const Far_& far_
		)
		{
			// Faster to calculate via scalars since we aren't actually doing too many operations compared to the amount of stores and shuffles we'd need
			float right_minus_left = static_cast<float>(right_) - static_cast<float>(left_);
			float top_minus_bottom = static_cast<float>(top_) - static_cast<float>(bottom_);
			float neg_far_minus_near_reciprocal = -(1.0f / (static_cast<float>(far_) - static_cast<float>(near_)));
			float out_00_ = 2 / right_minus_left;
			float out_11_ = 2 / top_minus_bottom;
			float out_22_ = neg_far_minus_near_reciprocal;
			float out_32_ = near_ * neg_far_minus_near_reciprocal;
			return FastMatrix4x4f_CM
			(
				out_00_, 0.0f,    0.0f,    0.0f,
				0.0f,    out_11_, 0.0f,    0.0f,
				0.0f,    0.0f,    out_22_, 0.0f,
				0.0f,    0.0f,    out_32_, 1.0f
			);
		}
		/// <summary>
		/// <para> Creates a 4x4 column-major orthographic projection matrix for right-handed coordinate systems, formed for Vulkan clipping space. </para>
		/// <para>
		///		This is effectively shorthand for calling the overload of this function taking specific edges, 
		///		where left and bottom will be set to 0, and right and top will be set to width and height respectively.
		/// </para>
		/// </summary>
		/// <typeparam name="Width_">Type used to provided the view space's horizontal size.</typeparam>
		/// <typeparam name="Width_">Type used to provided the view space's vertical size.</typeparam>
		/// <typeparam name="Near_">Type used to provide the near plane value.</typeparam>
		/// <typeparam name="Far_">Type used to provide the far plane value.</typeparam>
		/// <param name="width_">Target view space's horizontal size.</param>
		/// <param name="height_">Target view space's vertical size.</param>
		/// <param name="near_">Near clipping plane to project items to. For correct behaviour, this should be greater than far_.</param>
		/// <param name="far_">Near clipping plane to project items to. For correct behaviour, this should be less than near_.</param>
		/// <returns>Right-handed orthographic projection matrix formed for Vulkan clipping space.</returns>
		template<typename Width_, typename Height_, typename Near_, typename Far_>
		[[nodiscard]] static inline FastMatrix4x4f_CM OrthographicRhVK(const Width_& width_, const Height_& height_, const Near_& near_, const Far_& far_)
		{
			return OrthographicRhVK<float, Width_, float, Height_, Near_, Far_>(0.0f, width_, 0.0f, height_, near_, far_);
		}
#pragma endregion

		__m128 column0;
		__m128 column1;
		__m128 column2;
		__m128 column3;

	private:
#pragma region ASSERTIONS
		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		static constexpr inline bool _assert_valid_index()
		{
			if constexpr (ColumnIndex_ < 4)
			{
				if constexpr (RowIndex_ < 4)
				{
					return true;
				}
				else
				{
					static_assert(false, "Provided an invalid Row Index for accessing an EmuMath::FastMatrix4x4f_CM. 0-3 (inclusive) is the valid Row Index range.");
					return false;
				}
			}
			else
			{
				if constexpr (RowIndex_ < 4)
				{
					static_assert(false, "Provided an invalid Column Index for accessing an EmuMath::FastMatrix4x4f_CM. 0-3 (inclusive) is the valid Column Index range.");
				}
				else
				{
					static_assert(false, "Provided invalid Column and Row indices for accessing an EmuMath::FastMAtrix4x4f_CM. 0-3 (inclusive) is the valid index range for both Columns and Rows.");
				}
				return false;
			}
		}

		template<typename To_>
		static constexpr inline bool _assert_valid_cast_to()
		{
			if constexpr (std::is_convertible_v<float, To_>)
			{
				return true;
			}
			else
			{
				static_assert(false, "Provided an invalid type to cast a value from an EmuMath::FastMatrix4x4f_CM to. The provided type must be possible to convert to from float.");
				return false;
			}
		}

		template<typename From_>
		static constexpr inline bool _assert_valid_cast_from()
		{
			if constexpr (std::is_convertible_v<From_, float>)
			{
				return true;
			}
			else
			{
				static_assert(false, "Provided an invalid type to cast to a value within an EmuMath::FastMatrix4x4f_CM. The provided type must be possible to convert to a float.");
				return false;
			}
		}

		template<std::size_t MajorIndex_>
		static constexpr inline bool _assert_valid_major_index()
		{
			if constexpr (MajorIndex_ < 4)
			{
				return true;
			}
			else
			{
				return false;
				static_assert(false, "Provided an invalid Major Index for accessing an EmuMath::FastMatrix4x4f_CM. 0-3 (inclusive) is the valid Major Index range, the same as its Column range.");
			}
		}
#pragma endregion

#pragma region UNDERLYING_HELPERS
		[[nodiscard]] inline __m128 _std_mult_calculate_column(__m128 rhs_column_) const
		{
			// We use a shuffle instead of dumping values and broadcasting as it tends to be better optimised by the compiler
			// --- NOTE: this is slower in debug compared to the broadcasting of dumped values, but faster in release
			__m128 rhs_shuffled_ = EmuSIMD::shuffle<0, 0, 0, 0>(rhs_column_);
			__m128 out_ = _mm_mul_ps(column0, rhs_shuffled_);

			// Repeat above for each individual column index, performing dot product additions with each step
			// --- We use separate add and mul operations instead of fmadd since it appears to be faster in most reasonable use cases
			rhs_shuffled_ = EmuSIMD::shuffle<1, 1, 1, 1>(rhs_column_);
			out_ = _mm_add_ps(out_, _mm_mul_ps(column1, rhs_shuffled_));

			rhs_shuffled_ = EmuSIMD::shuffle<2, 2, 2, 2>(rhs_column_);
			out_ = _mm_add_ps(out_, _mm_mul_ps(column2, rhs_shuffled_));

			rhs_shuffled_ = EmuSIMD::shuffle<3, 3, 3, 3>(rhs_column_);
			return _mm_add_ps(out_, _mm_mul_ps(column3, rhs_shuffled_));
		}

		template<std::size_t ExcludeRow_>
		[[nodiscard]] static inline __m128 _index_excluding_shuffle(__m128 val_)
		{
			if constexpr (ExcludeRow_ == 0)
			{
				return EmuSIMD::shuffle<1, 2, 3, 0>(val_);
			}
			else if constexpr (ExcludeRow_ == 1)
			{
				return EmuSIMD::shuffle<0, 2, 3, 1>(val_);
			}
			else if constexpr (ExcludeRow_ == 2)
			{
				return EmuSIMD::shuffle<0, 1, 3, 2>(val_);
			}
			else if constexpr (ExcludeRow_ == 3)
			{
				return val_;
			}
			else
			{
				static_assert(false, "Attempted to pass an invalid ExcludeRow_ index to EmuMath::FastMatrix4x4f_CM::_index_excluding_shuffle.");
			}
		}
#pragma endregion
	};
}

#pragma region STREAM_OPERATORS
std::ostream& operator<<(std::ostream& stream_, const EmuMath::FastMatrix4x4f_CM& matrix_)
{
	stream_ << matrix_.Store<float, true>();
	return stream_;
}

std::wostream& operator<<(std::wostream& stream_, const EmuMath::FastMatrix4x4f_CM& matrix_)
{
	stream_ << matrix_.Store<float, true>();
	return stream_;
}
#pragma endregion

#endif
