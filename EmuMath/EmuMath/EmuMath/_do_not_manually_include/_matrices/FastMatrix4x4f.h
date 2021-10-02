#ifndef EMU_MATH_FAST_MATRIX_4X4_H_INC_
#define EMU_MATH_FAST_MATRIX_4X4_H_INC_ 1

#include "../../Matrix.h"
#include "../../SIMDHelpers.h"
#include "../../FastVector.h"

namespace EmuMath
{
	/// <summary> 4x4 matrix of floating points which makes use of SIMD intrinsics. Uses column-major storage. </summary>
	struct FastMatrix4x4f_CM
	{
	public:
#pragma region CONSTRUCTORS
		FastMatrix4x4f_CM() : column0(), column1(), column2(), column3()
		{
		}
		FastMatrix4x4f_CM(__m128 column_0_, __m128 column_1_, __m128 column_2_, __m128 column_3_) :
			column0(column_0_),
			column1(column_1_),
			column2(column_2_),
			column3(column_3_)
		{
		}
		FastMatrix4x4f_CM(const FastMatrix4x4f_CM& to_copy_) :
			column0(to_copy_.column0),
			column1(to_copy_.column1),
			column2(to_copy_.column2),
			column3(to_copy_.column3)
		{
		}
		template<typename std::size_t InColumns_, std::size_t InRows_, typename in_contained_type, bool InColumnMajor_>
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
			column0(EmuMath::SIMD::m128_from_emu_math_vector(column_0_)),
			column1(EmuMath::SIMD::m128_from_emu_math_vector(column_1_)),
			column2(EmuMath::SIMD::m128_from_emu_math_vector(column_2_)),
			column3(EmuMath::SIMD::m128_from_emu_math_vector(column_3_))
		{
		}
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
		/// <returns></returns>
		template<std::size_t ColumnIndex_, std::size_t RowIndex_, typename Out_ = float>
		[[nodiscard]] Out_ at() const
		{
			if constexpr (_assert_valid_index<ColumnIndex_, RowIndex_>())
			{
				if constexpr (_assert_valid_cast_to<Out_>())
				{
					return static_cast<Out_>(EmuMath::SIMD::get_m128_index<RowIndex_>(GetColumn<ColumnIndex_>()));
				}
				else
				{
					static_assert(false, "Invalid Out_ type provided to EmuMath::FastMatrix4x4f_CM::at.");
				}
			}
			else
			{
				static_assert(false, "Invalid indices provided to EmuMath::FastMatrix4x4f_CM::at.");
			}
		}

		/// <summary>
		///	<para> Stores this matrix as an easily-readable 4x4 EmuMath matrix, with customisable contained types and major-order (defaults to the same as this matrix). </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output EmuMath matrix.</typeparam>
		/// <returns>4x4 EmuMath matrix that may be easily read</returns>
		template<typename out_contained_type = float, bool OutColumnMajor_ = true>
		[[nodiscard]] EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> Store() const
		{
			if constexpr (std::is_same_v<out_contained_type, float> && OutColumnMajor_)
			{
				// Load data straight into output matrix since we can easily do so knowing major-order and type match.
				EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> out_;
				_mm_store_ps(out_.at<0>().data(), column0);
				_mm_store_ps(out_.at<1>().data(), column1);
				_mm_store_ps(out_.at<2>().data(), column2);
				_mm_store_ps(out_.at<3>().data(), column3);
				return out_;
			}
			else
			{
				if constexpr (_assert_valid_cast_to<out_contained_type>())
				{
					EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> out_;
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
						FastMatrix4x4f_CM transpose_ = Transpose();
						out_.at<0>() = transpose_.GetColumnReadable<0>();
						out_.at<1>() = transpose_.GetColumnReadable<1>();
						out_.at<2>() = transpose_.GetColumnReadable<2>();
						out_.at<3>() = transpose_.GetColumnReadable<3>();
					}
					return out_;
				}
				else
				{
					static_assert(false, "Invalid out_contained_type provided to EmuMath::FastMatrix4x4f_CM::Store.");
				}
			}
		}

		/// <summary> Provides a 128-bit register copy of the column at the specified index. </summary>
		/// <returns>128-bit float register copy of the requested column within this matrix.</returns>
		template<std::size_t Column_>
		[[nodiscard]] __m128 GetColumn() const
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
		[[nodiscard]] EmuMath::Vector<4, float> GetColumnReadable() const
		{
			EmuMath::Vector4<float> out_;
			_mm_store_ps(out_.data(), GetColumn<Column_>());
			return out_;
		}

		/// <summary> Provides a 128-bit register copy of the row at the specified index. As this matrix is column-major, this will require several shuffles. </summary>
		/// <returns>128-bit float register copy of the requested row within this matrix.</returns>
		template<std::size_t Row_>
		[[nodiscard]] __m128 GetRow() const
		{
			if constexpr (Row_ <= 3)
			{
				__m128 out_0_1 = EmuMath::SIMD::shuffle<Row_, 0, Row_, 0>(column0, column1);
				__m128 out_2_3 = EmuMath::SIMD::shuffle<Row_, 0, Row_, 0>(column2, column3);
				return EmuMath::SIMD::shuffle<0, 2, 0, 2>(out_0_1, out_2_3);
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
		[[nodiscard]] EmuMath::Vector<4, float> GetRowReadable() const
		{
			EmuMath::Vector4<float> out_;
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
		inline FastMatrix4x4f_CM Add(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
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
		inline FastMatrix4x4f_CM Add(const FastMatrix4x4f_CM& rhs_) const
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
		inline FastMatrix4x4f_CM Subtract(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
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
		inline FastMatrix4x4f_CM Subtract(const FastMatrix4x4f_CM& rhs_) const
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
		inline FastMatrix4x4f_CM MultiplyBasic(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
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
		inline FastMatrix4x4f_CM MultiplyBasic(__m128 mult_for_all_columns_) const
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
		inline FastMatrix4x4f_CM MultiplyBasic(const FastMatrix4x4f_CM& rhs_) const
		{
			return MultiplyBasic(rhs_.column0, rhs_.column1, rhs_.column2, rhs_.column3);
		}
		/// <summary> Multiplies all elements within this matrix by the provided val_. The provided val_ must be castable to a float. </summary>
		/// <typeparam name="T_">Type to multiply by.</typeparam>
		/// <param name="val_">Value to multiply all elements of this matrix by.</param>
		/// <returns>Resulting matrix after multiply all of this matrix's elements by the passed val_.</returns>
		template<typename T_, typename RequiresTConvertibleToFloat = std::enable_if_t<std::is_convertible_v<T_, float>>>
		inline FastMatrix4x4f_CM MultiplyBasic(const T_& val_) const
		{
			return MultiplyBasic(_mm_set_ps1(static_cast<float>(val_)));
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
		inline FastMatrix4x4f_CM Multiply(__m128 rhs_column_0_, __m128 rhs_column_1_, __m128 rhs_column_2_, __m128 rhs_column_3_) const
		{
			return FastMatrix4x4f_CM
			(
				_std_mult_calculate_column(rhs_column_0_),
				_std_mult_calculate_column(rhs_column_1_),
				_std_mult_calculate_column(rhs_column_2_),
				_std_mult_calculate_column(rhs_column_3_)
			);
		}

		inline EmuMath::FastVector4f MultiplyVector4(__m128 rhs_vector_) const
		{
			__m128 out_x_ = _mm_mul_ps(column0, EmuMath::SIMD::shuffle<0, 0, 0, 0>(rhs_vector_));
			__m128 out_y_ = _mm_mul_ps(column1, EmuMath::SIMD::shuffle<1, 1, 1, 1>(rhs_vector_));
			__m128 out_z_ = _mm_mul_ps(column2, EmuMath::SIMD::shuffle<2, 2, 2, 2>(rhs_vector_));
			__m128 out_w_ = _mm_mul_ps(column3, EmuMath::SIMD::shuffle<3, 3, 3, 3>(rhs_vector_));
			return FastVector4f(_mm_add_ps(_mm_add_ps(out_x_, out_y_), _mm_add_ps(out_z_, out_w_)));
		}
		inline EmuMath::FastVector4f MultiplyVector3(__m128 rhs_vector_) const
		{
			__m128 out_x_ = _mm_mul_ps(column0, EmuMath::SIMD::shuffle<0, 0, 0, 0>(rhs_vector_));
			__m128 out_y_ = _mm_mul_ps(column1, EmuMath::SIMD::shuffle<1, 1, 1, 1>(rhs_vector_));
			__m128 out_z_ = _mm_mul_ps(column2, EmuMath::SIMD::shuffle<2, 2, 2, 2>(rhs_vector_));

			// Add column3 as we interpret the missing value to be 1 as per homogeneous coordinates default to
			return FastVector4f(_mm_add_ps(_mm_add_ps(out_x_, out_y_), _mm_add_ps(out_z_, column3)));
		}
		inline EmuMath::FastVector4f MultiplyVector2(__m128 rhs_vector_) const
		{
			__m128 out_x_ = _mm_mul_ps(column0, EmuMath::SIMD::shuffle<0, 0, 0, 0>(rhs_vector_));
			__m128 out_y_ = _mm_mul_ps(column1, EmuMath::SIMD::shuffle<1, 1, 1, 1>(rhs_vector_));

			// Add column3 as we interpret the missing w value to be 1 as per homogeneous coordinates default to, 
			// and z is interpreted to be 0 since 2D space is implicitly at Z 0.
			return FastVector4f(_mm_add_ps(_mm_add_ps(out_x_, out_y_), column3));
		}

		/// <summary>
		/// <para> Performs a standard matrix multiplication with the provided rhs_ matrix. </para>
		/// <para> This is a standard matrix multiplication. To perform a basic multiplication of respective columns, use MultiplyBasic. </para>
		/// </summary>
		/// <param name="rhs_">Matrix to multiply this matrix by.</param>
		/// <returns>Matrix result from multiplying this matrix by a matrix comprised of respective passed columns.</returns>
		inline FastMatrix4x4f_CM Multiply(const FastMatrix4x4f_CM& rhs_) const
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
		inline FastMatrix4x4f_CM Multiply(__m128 mult_for_all_columns_) const
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
		inline FastMatrix4x4f_CM Multiply(const T_& val_) const
		{
			return MultiplyBasic<T_>(val_);
		}

		inline FastMatrix4x4f_CM Negate() const
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
#pragma endregion

#pragma region CONST_OPERATORS
		inline bool operator==(const FastMatrix4x4f_CM& rhs_) const
		{
			return
			(
				EmuMath::SIMD::all_equal(column0, rhs_.column0) &&
				EmuMath::SIMD::all_equal(column1, rhs_.column1) &&
				EmuMath::SIMD::all_equal(column2, rhs_.column2) &&
				EmuMath::SIMD::all_equal(column3, rhs_.column3)
			);
		}

		inline bool operator!=(const FastMatrix4x4f_CM& rhs_) const
		{
			return
			(
				EmuMath::SIMD::any_not_equal(column0, rhs_.column0) ||
				EmuMath::SIMD::any_not_equal(column1, rhs_.column1) ||
				EmuMath::SIMD::any_not_equal(column2, rhs_.column2) ||
				EmuMath::SIMD::any_not_equal(column3, rhs_.column3)
			);
		}

		inline FastMatrix4x4f_CM operator+(const FastMatrix4x4f_CM& rhs_) const
		{
			return Add(rhs_);
		}

		inline FastMatrix4x4f_CM operator-(const FastMatrix4x4f_CM& rhs_) const
		{
			return Subtract(rhs_);
		}
		inline FastMatrix4x4f_CM operator-() const
		{
			return Negate();
		}

		template<typename T_, typename RequiresTConvertibleToFloat = std::enable_if_t<std::is_convertible_v<T_, float>>>
		inline FastMatrix4x4f_CM operator*(const T_& rhs_) const
		{
			return MultiplyBasic<T_>(rhs_);
		}
#pragma endregion

#pragma region MATRIX_OPERATIONS
		inline FastMatrix4x4f_CM Transpose() const
		{
			return FastMatrix4x4f_CM(GetRow<0>(), GetRow<1>(), GetRow<2>(), GetRow<3>());
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
				static_assert(false, "Provided an invalid Column Index for accessing an EmuMath::FastMatrix4x4f_CM. 0-3 (inclusive) is the valid Column Index range.");
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
#pragma endregion

#pragma region UNDERLYING_HELPERS
		inline __m128 _std_mult_calculate_column(__m128 rhs_column_) const
		{
			// We use a shuffle instead of dumping values and broadcasting as it tends to be better optimised by the compiler
			// --- NOTE: this is slower in debug compared to the broadcasting of dumped values, but faster in release
			__m128 rhs_shuffled_ = EmuMath::SIMD::shuffle<0, 0, 0, 0>(rhs_column_);
			__m128 out_ = _mm_mul_ps(column0, rhs_shuffled_);

			// Repeat above for each individual column index, performing dot product additions with each step
			rhs_shuffled_ = EmuMath::SIMD::shuffle<1, 1, 1, 1>(rhs_column_);
			out_ = _mm_add_ps(out_, _mm_mul_ps(column1, rhs_shuffled_));

			rhs_shuffled_ = EmuMath::SIMD::shuffle<2, 2, 2, 2>(rhs_column_);
			out_ = _mm_add_ps(out_, _mm_mul_ps(column2, rhs_shuffled_));

			rhs_shuffled_ = EmuMath::SIMD::shuffle<3, 3, 3, 3>(rhs_column_);
			return _mm_add_ps(out_, _mm_mul_ps(column3, rhs_shuffled_));
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
