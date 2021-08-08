#ifndef EMU_MATH_FAST_VECTOR_F4_H_INC_
#define EMU_MATH_FAST_VECTOR_F4_H_INC_

#include "FastVectorBase.h"

namespace EmuMath
{
	template<>
	struct FastVector<4, float>
	{
	public:
#pragma region ALIASES_AND_STATIC_CONSTANT_EXPRESSIONS
		using info_type = EmuMath::_info::VectorInfo<float>;
		using value_type = float;
		static constexpr bool is_specialised = true;
		static constexpr std::size_t size = 4;
		using this_type = FastVector<size, value_type>;
#pragma endregion

#pragma region CONSTRUCTORS
		FastVector() : FastVector(0.0f, 0.0f, 0.0f, 0.0f)
		{
		}
		FastVector(const this_type& toCopy_) : vectorData(toCopy_.vectorData)
		{
		}
		explicit FastVector(__m128 toCopy_) : vectorData(toCopy_)
		{
		}
		template<typename X_, typename Y_, typename Z_, typename W_>
		explicit FastVector(const X_& x_, const Y_& y_, const Z_& z_, const W_& w_) :
			vectorData(_mm_setr_ps(static_cast<value_type>(x_), static_cast<value_type>(y_), static_cast<value_type>(z_), static_cast<value_type>(w_)))
		{
		}
		template<typename ToCopyT>
		explicit FastVector(const EmuMath::Vector2<ToCopyT>& toCopy_) : FastVector(toCopy_.x, toCopy_.y, 0.0f, 0.0f)
		{
		}
		template<typename ToCopyT>
		explicit FastVector(const EmuMath::Vector3<ToCopyT>& toCopy_) : FastVector(toCopy_.x, toCopy_.y, toCopy_.z, 0.0f)
		{
		}
		template<typename ToCopyT>
		explicit FastVector(const EmuMath::Vector4<ToCopyT>& toCopy_) : FastVector(toCopy_.x, toCopy_.y, toCopy_.z, toCopy_.w)
		{
		}
#pragma endregion

#pragma region RANDOM_ACCESS
		/// <summary> Retrieves a copy of the data at the given index of this Vector. The at function cannot be used to obtain a reference. </summary>
		/// <returns>Copy of the value at the provided index.</returns>
		template<std::size_t Index_>
		float at() const
		{
			return EmuMath::SIMD::get_m128_index<Index_>(vectorData);
		}
		/// <summary>
		/// <para> Retrieves a copy of the data at the given index of this Vector. The at function cannot be used to obtain a reference. </para>
		/// <para> If the desired index_ is compile-time evaluable, it is recommended to provide it as a template argument instead of a function argument. </para>
		/// </summary>
		/// <returns>Copy of the value at the provided index.</returns>
		float at(std::size_t index_) const
		{
			return EmuMath::SIMD::get_m128_index(vectorData, index_);
		}
		float operator[](const std::size_t index_) const
		{
			return this->at(index_);
		}
#pragma endregion

#pragma region ARITHMETIC_CONST_OPERATORS
		this_type operator+(const this_type& rhs) const
		{
			return this->operator+(rhs.vectorData);
		}
		this_type operator+(const __m128 rhs) const
		{
			return this_type(_mm_add_ps(vectorData, rhs));
		}
		this_type operator-(const this_type& rhs) const
		{
			return this->operator-(rhs.vectorData);
		}
		this_type operator-(const __m128 rhs) const
		{
			return this_type(_mm_sub_ps(vectorData, rhs));
		}
		this_type operator*(const this_type& rhs) const
		{
			return this->operator*(rhs.vectorData);
		}
		this_type operator*(const float rhs) const
		{
			return this->operator*(_mm_set_ps1(rhs));
		}
		this_type operator*(const __m128 rhs) const
		{
			return this_type(_mm_mul_ps(vectorData, rhs));
		}
		this_type operator/(const this_type& rhs) const
		{
			return this->operator/(rhs.vectorData);
		}
		this_type operator/(const float rhs) const
		{
			return this->operator/(_mm_set_ps1(rhs));
		}
		this_type operator/(const __m128 rhs) const
		{
			return this_type(_mm_div_ps(vectorData, rhs));
		}
#pragma endregion

#pragma region BITWISE_CONST_OPERATORS
		this_type operator&(const this_type& rhs) const
		{
			return this->operator&(rhs.vectorData);
		}
		this_type operator&(const __m128 rhs) const
		{
			return this_type(_mm_and_ps(vectorData, rhs));
		}
		this_type operator|(const this_type& rhs) const
		{
			return this->operator|(rhs.vectorData);
		}
		this_type operator|(const __m128 rhs) const
		{
			return this_type(_mm_or_ps(vectorData, rhs));
		}
		this_type operator^(const this_type& rhs) const
		{
			return this->operator^(rhs.vectorData);
		}
		this_type operator^(const __m128 rhs) const
		{
			return this_type(_mm_xor_ps(vectorData, rhs));
		}
#pragma endregion

#pragma region ARITHMETIC_NONCONST_OPERATORS
		this_type& operator+=(const this_type& rhs)
		{
			return this->operator+=(rhs.vectorData);
		}
		this_type& operator+=(const __m128 rhs)
		{
			vectorData = _mm_add_ps(vectorData, rhs);
			return *this;
		}

		this_type& operator-=(const this_type& rhs)
		{
			return this->operator-=(rhs.vectorData);
		}
		this_type& operator-=(const __m128 rhs)
		{
			vectorData = _mm_sub_ps(vectorData, rhs);
			return *this;
		}

		this_type& operator*=(const this_type& rhs)
		{
			return this->operator*=(rhs.vectorData);
		}
		this_type& operator*=(const float rhs)
		{
			return this->operator*=(_mm_set_ps1(rhs));
		}
		this_type& operator*=(const __m128 rhs)
		{
			vectorData = _mm_mul_ps(vectorData, rhs);
			return *this;
		}

		this_type& operator/=(const this_type& rhs)
		{
			return this->operator/=(rhs.vectorData);
		}
		this_type& operator/=(const float rhs)
		{
			return this->operator/=(_mm_set_ps1(rhs));
		}
		this_type& operator/=(const __m128 rhs)
		{
			vectorData = _mm_div_ps(vectorData, rhs);
			return *this;
		}
#pragma endregion

#pragma region BITWISE_NONCONST_OPERATORS
		this_type& operator&=(const this_type& rhs)
		{
			return this->operator&=(rhs.vectorData);
		}
		this_type& operator&=(const __m128 rhs)
		{
			vectorData = _mm_and_ps(vectorData, rhs);
			return *this;
		}

		this_type& operator|=(const this_type& rhs)
		{
			return this->operator|=(rhs.vectorData);
		}
		this_type& operator|=(const __m128 rhs)
		{
			vectorData = _mm_or_ps(vectorData, rhs);
			return *this;
		}

		this_type& operator^=(const this_type& rhs)
		{
			return this->operator^=(rhs.vectorData);
		}
		this_type& operator^=(const __m128 rhs)
		{
			vectorData = _mm_xor_ps(vectorData, rhs);
			return *this;
		}
#pragma endregion

#pragma region BOOLEAN_COMPARISON_OPERATORS
		bool operator==(const this_type& rhs) const
		{
			return this->operator==(rhs.vectorData);
		}
		bool operator==(const __m128 rhs) const
		{
			return EmuMath::SIMD::all_equal<true, true, true, true>(vectorData, rhs);
		}
		bool operator!=(const this_type& rhs) const
		{
			return this->operator!=(rhs.vectorData);
		}
		bool operator!=(const __m128 rhs) const
		{
			return !EmuMath::SIMD::all_equal<true, true, true, true>(vectorData, rhs);
		}
		bool operator>(const this_type& rhs) const
		{
			return this->SquareMagnitude() > rhs.SquareMagnitude();
		}
		bool operator<(const this_type& rhs) const
		{
			return this->SquareMagnitude() < rhs.SquareMagnitude();
		}
		bool operator>=(const this_type& rhs) const
		{
			return this->SquareMagnitude() >= rhs.SquareMagnitude();
		}
		bool operator<=(const this_type& rhs) const
		{
			return this->SquareMagnitude() <= rhs.SquareMagnitude();
		}
#pragma endregion

#pragma region ASSIGNMENT_OPERATORS
		this_type& operator=(const this_type& toCopy_)
		{
			vectorData = toCopy_.vectorData;
			return *this;
		}
#pragma endregion

#pragma region SHUFFLES
		template<std::size_t X_, std::size_t Y_, std::size_t Z_, std::size_t W_>
		this_type Shuffle() const
		{
			return this_type(EmuMath::SIMD::shuffle<X_, Y_, Z_, W_>(vectorData));
		}
#pragma endregion

#pragma region SETS
		template<class Rhs_>
		this_type& Set(const Rhs_ toSetAllTo_)
		{
			vectorData = _mm_set_ps1(static_cast<float>(toSetAllTo_));
			return *this;
		}
		template<class X_, class Y_, class Z_, class W_>
		this_type& Set(const X_ x_, const Y_ y_, const Z_ z_, const W_ w_)
		{
			vectorData = _mm_set_ps(static_cast<float>(w_), static_cast<float>(z_), static_cast<float>(y_), static_cast<float>(x_));
			return *this;
		}
#pragma endregion

#pragma region OVERALL_OPERATIONS
		this_type Reciprocal() const
		{
			return this_type(_mm_div_ps(_mm_set_ps1(1.0f), vectorData));
		}

		float TotalSum() const
		{
			return EmuMath::SIMD::horizontal_vector_sum_scalar(vectorData);
		}

		float Min() const
		{
			__m128 result = _mm_min_ps(vectorData, EmuMath::SIMD::shuffle<3, 0, 1, 2>(vectorData));
			result = _mm_min_ps(result, EmuMath::SIMD::shuffle<2, 3, 1, 0>(result));
			result = _mm_min_ps(result, EmuMath::SIMD::shuffle<1, 2, 3, 0>(result));
			return _mm_cvtss_f32(result);
		}
		float Max() const
		{
			__m128 result = _mm_max_ps(vectorData, EmuMath::SIMD::shuffle<3, 0, 1, 2>(vectorData));
			result = _mm_max_ps(result, EmuMath::SIMD::shuffle<2, 3, 1, 0>(result));
			result = _mm_max_ps(result, EmuMath::SIMD::shuffle<1, 2, 3, 0>(result));
			return _mm_cvtss_f32(result);
		}
		float Mean() const
		{
			// No advantage from SIMD due to the required horizontal addition
			float scalarData[4];
			_mm_store_ps(scalarData, vectorData);
			return (scalarData[0] + scalarData[1] + scalarData[2] + scalarData[3]) * 0.25f;
		}

		this_type ClampMin(const this_type min_) const
		{
			return this->ClampMin(min_.vectorData);
		}
		this_type ClampMin(const float min_) const
		{
			return this->ClampMin(_mm_set_ps1(min_));
		}
		this_type ClampMin(const __m128 min_) const
		{
			__m128 ignoreFlags = _mm_cmpge_ps(vectorData, min_);
			__m128 result = _mm_and_ps(ignoreFlags, vectorData);
			result = _mm_or_ps(result, _mm_andnot_ps(ignoreFlags, min_));
			return this_type(result);
		}
		this_type ClampMax(const this_type max_) const
		{
			return this->ClampMax(max_.vectorData);
		}
		this_type ClampMax(const float max_) const
		{
			return this->ClampMax(_mm_set_ps1(max_));
		}
		this_type ClampMax(__m128 max_) const
		{
			__m128 ignoreFlags = _mm_cmple_ps(vectorData, max_);
			__m128 result = _mm_and_ps(ignoreFlags, vectorData);
			result = _mm_or_ps(result, _mm_andnot_ps(ignoreFlags, max_));
			return this_type(result);
		}
		this_type Clamp(const this_type min_, const this_type max_) const
		{
			return this->Clamp(min_.vectorData, max_.vectorData);
		}
		this_type Clamp(const this_type min_, const __m128 max_) const
		{
			return this->Clamp(min_.vectorData, max_);
		}
		this_type Clamp(const __m128 min_, const this_type max_) const
		{
			return this->Clamp(min_, max_.vectorData);
		}
		this_type Clamp(const this_type min_, const float max_) const
		{
			return this->Clamp(min_.vectorData, _mm_set_ps1(max_));
		}
		this_type Clamp(const float min_, const this_type max_) const
		{
			return this->Clamp(_mm_set_ps1(min_), max_.vectorData);
		}
		this_type Clamp(const float min_, const __m128 max_) const
		{
			return this->Clamp(_mm_set_ps1(min_), max_);
		}
		this_type Clamp(const __m128 min_, const float max_) const
		{
			return this->Clamp(min_, _mm_set_ps1(max_));
		}
		this_type Clamp(const float min_, const float max_) const
		{
			return this->Clamp(_mm_set_ps1(min_), _mm_set_ps1(max_));
		}
		this_type Clamp(const __m128 min_, const __m128 max_) const
		{
			__m128 clampMinFlags = _mm_cmplt_ps(vectorData, min_);
			__m128 clampMaxFlags = _mm_cmpgt_ps(vectorData, max_);
			__m128 clampFlags = _mm_or_ps(clampMinFlags, clampMaxFlags);

			__m128 result = _mm_andnot_ps(clampFlags, vectorData);
			result = _mm_or_ps(result, _mm_and_ps(clampMinFlags, min_));
			result = _mm_or_ps(result, _mm_and_ps(clampMaxFlags, max_));
			return this_type(result);
		}

		this_type Floor() const
		{
			return this_type(_mm_round_ps(vectorData, _MM_FROUND_FLOOR));
		}
		this_type Ceil() const
		{
			return this_type(_mm_round_ps(vectorData, _MM_FROUND_CEIL));
		}
		this_type Trunc() const
		{
			return this_type(_mm_round_ps(vectorData, _MM_FROUND_TRUNC));
		}

		this_type Lerp(const this_type& b_, const float t_)
		{
			return this->Lerp(b_.vectorData, _mm_set_ps1(t_));
		}
		this_type Lerp(const this_type& b_, const this_type& t_)
		{
			return this->Lerp(b_.vectorData, t_.vectorData);
		}
		this_type Lerp(const this_type& b_, const __m128 t_)
		{
			return this->Lerp(b_.vectorData, t_);
		}
		this_type Lerp(const __m128 b_, const float t_)
		{
			return this->Lerp(b_, _mm_set_ps1(t_));
		}
		this_type Lerp(const __m128 b_, const this_type& t_)
		{
			return this->Lerp(b_, t_.vectorData);
		}
		this_type Lerp(const __m128 b_, const __m128 t_)
		{
			// Follows approximation of "lerped = a + (b - a) * t"
			__m128 result = _mm_sub_ps(b_, vectorData);
			_mm_mul_ps(result, t_);
			result = _mm_add_ps(vectorData, result);
			return this_type(result);
		}
#pragma endregion

#pragma region VECTOR_OPERATIONS
		float SquareMagnitude() const
		{
			return _calculate_square_mag_128().m128_f32[0];
		}
		float Magnitude() const
		{
			return _calculate_mag_128().m128_f32[0];
		}

		this_type Normalise() const
		{
			return this_type(_mm_div_ps(vectorData, _calculate_mag_128()));
		}

		float DotProduct(const this_type& b_) const
		{
			return this->DotProduct(b_.vectorData);
		}
		float DotProduct(const __m128 b_) const
		{
			return _mm_dp_ps(vectorData, b_, 0xFF).m128_f32[0];
		}

		this_type Reverse() const
		{
			return this_type(_mm_mul_ps(vectorData, _mm_set_ps1(-1.0f)));
		}
#pragma endregion

#pragma region CONVERSION_FUNCTIONS
		template<std::size_t OutSize_ = size, typename OutT_ = value_type>
		typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type AsEmuVector() const
		{
			float scalarData[4];
			_mm_store_ps(scalarData, vectorData);
			if constexpr (OutSize_ == 2)
			{
				return EmuMath::Vector2<OutT_>(scalarData[0], scalarData[1]);
			}
			else if constexpr (OutSize_ == 3)
			{
				return EmuMath::Vector3<OutT_>(scalarData[0], scalarData[1], scalarData[2]);
			}
			else if constexpr (OutSize_ == 4)
			{
				return EmuMath::Vector4<OutT_>(scalarData[0], scalarData[1], scalarData[2], scalarData[3]);
			}
			else
			{
				static_assert(false, "Attempted to output an EmuMath FastVector as an invalidly sized vector.");
			}
		}
#pragma endregion

		/// <summary> SIMD storage of this FastVector's data. Implementation defined, and should not be used directly unless you know exactly what you are doing. </summary>
		__m128 vectorData;

	private:
		__m128 _calculate_square_mag_128() const
		{
			__m128 result = _mm_mul_ps(vectorData, vectorData);
			return EmuMath::SIMD::horizontal_vector_sum_fill(result);
		}

		__m128 _calculate_mag_128() const
		{
			return _mm_sqrt_ps(_calculate_square_mag_128());
		}
	};
}

#endif
