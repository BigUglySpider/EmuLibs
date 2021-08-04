#ifndef EMU_MATH_FAST_VECTOR_F4_H_INC_
#define EMU_MATH_FAST_VECTOR_F4_H_INC_

#include "FastVectorBase.h"

namespace EmuMath
{
	template<>
	struct FastVector<4, float>
	{
	public:
		using info_type = EmuMath::_info::VectorInfo<float>;
		using value_type = float;
		static constexpr bool is_specialised = true;
		static constexpr std::size_t size = 4;
		using this_type = FastVector<size, value_type>;

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

		template<std::size_t X_, std::size_t Y_, std::size_t Z_, std::size_t W_>
		this_type Shuffle() const
		{
			return this_type(EmuMath::SIMD::shuffle<X_, Y_, Z_, W_>(vectorData));
		}

		this_type operator+(const this_type& rhs) const
		{
			return this_type(_mm_add_ps(vectorData, rhs.vectorData));
		}
		this_type operator+(const __m128 rhs) const
		{
			return this_type(_mm_add_ps(vectorData, rhs));
		}
		this_type operator-(const this_type& rhs) const
		{
			return this_type(_mm_sub_ps(vectorData, rhs.vectorData));
		}
		this_type operator-(const __m128 rhs) const
		{
			return this_type(_mm_sub_ps(vectorData, rhs));
		}
		this_type operator*(const this_type& rhs) const
		{
			return this_type(_mm_mul_ps(vectorData, rhs.vectorData));
		}
		this_type operator*(const __m128 rhs) const
		{
			return this_type(_mm_mul_ps(vectorData, rhs));
		}
		this_type operator*(const float rhs) const
		{
			return this_type(_mm_mul_ps(vectorData, _mm_broadcast_ss(&rhs)));
		}
		this_type operator/(const this_type& rhs) const
		{
			return this_type(_mm_div_ps(vectorData, rhs.vectorData));
		}
		this_type operator/(const __m128 rhs) const
		{
			return this_type(_mm_div_ps(vectorData, rhs));
		}

		this_type& operator=(const this_type& toCopy_)
		{
			vectorData = toCopy_.vectorData;
			return *this;
		}

		float DotProduct(const this_type& b_) const
		{
			return this->DotProduct(b_.vectorData);
		}
		float DotProduct(const __m128 b_) const
		{
			return _mm_dp_ps(vectorData, b_, 0xFF).m128_f32[0];
		}

		this_type Normalise() const
		{
			__m128 mag = _mm_mul_ps(vectorData, vectorData);
			mag = _mm_hadd_ps(mag, mag);
			mag = _mm_hadd_ps(mag, mag);
			mag = _mm_sqrt_ps(mag);
			return this_type(_mm_div_ps(vectorData, mag));
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

		this_type ClampMin(const this_type min_) const
		{
			return this->ClampMin(min_.vectorData);
		}
		this_type ClampMin(const float min_) const
		{
			return this->ClampMin(_mm_broadcast_ss(&min_));
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
			return this->ClampMax(_mm_broadcast_ss(&max_));
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
			return this->Clamp(min_.vectorData, _mm_broadcast_ss(&max_));
		}
		this_type Clamp(const float min_, const this_type max_) const
		{
			return this->Clamp(_mm_broadcast_ss(&min_), max_.vectorData);
		}
		this_type Clamp(const float min_, const __m128 max_) const
		{
			return this->Clamp(_mm_broadcast_ss(&min_), max_);
		}
		this_type Clamp(const __m128 min_, const float max_) const
		{
			return this->Clamp(min_, _mm_broadcast_ss(&max_));
		}
		this_type Clamp(const float min_, const float max_) const
		{
			return this->Clamp(_mm_broadcast_ss(&min_), _mm_broadcast_ss(&max_));
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

		template<std::size_t Size_ = size, typename T_ = value_type>
		typename EmuMath::TMPHelpers::emu_vector_from_size<Size_, T_>::type AsEmuVector() const
		{
			if constexpr (Size_ == 2)
			{
				return EmuMath::Vector2<T_>(vectorData.m128_f32[0], vectorData.m128_f32[1]);
			}
			else if constexpr (Size_ == 3)
			{
				return EmuMath::Vector3<T_>(vectorData.m128_f32[0], vectorData.m128_f32[1], vectorData.m128_f32[2]);
			}
			else if constexpr (Size_ == 4)
			{
				return EmuMath::Vector4<T_>(vectorData.m128_f32[0], vectorData.m128_f32[1], vectorData.m128_f32[2], vectorData.m128_f32[3]);
			}
			else if constexpr(Size_ > 4)
			{
				return EmuMath::TMPHelpers::emu_vector_from_size_t<Size_, T_>
				(
					EmuMath::Vector4<T_>(vectorData.m128_f32[0], vectorData.m128_f32[1], vectorData.m128_f32[2], vectorData.m128_f32[3])
				);
			}
			else
			{
				static_assert(false, "Attempted to output an EmuMath FastVector as an invalidly sized vector.");
			}
		}

		/// <summary> SIMD storage of this FastVector's data. Implementation defined, and should not be used directly unless you know exactly what you are doing. </summary>
		__m128 vectorData;

	private:
		template<std::size_t Index_>
		float _get_value() const
		{
			if constexpr (Index_ < size)
			{
				return vectorData.m128_f32[Index_];
			}
			else
			{
				static_assert(false, "Attempted to get an invalid Index from an EmuMath FastVector.");
			}
		}
	};
}

#endif
