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
		static constexpr std::size_t size()
		{
			return 4;
		}

		FastVector() : FastVector(0.0f, 0.0f, 0.0f, 0.0f)
		{
		}
		template<typename X_, typename Y_, typename Z_, typename W_>
		FastVector(const X_& x_, const Y_& y_, const Z_& z_, const W_& w_) :
			vectorData(_mm_setr_ps(static_cast<value_type>(x_), static_cast<value_type>(y_), static_cast<value_type>(z_), static_cast<value_type>(w_)))
		{
		}
		template<typename X_>
		FastVector(const X_& x_) :
			FastVector(x_, 0.0f, 0.0f, 0.0f)
		{
		}
		template<typename ToCopyT>
		FastVector(const EmuMath::Vector2<ToCopyT>& toCopy_) : FastVector(toCopy_.x, toCopy_.y, 0.0f, 0.0f)
		{
		}
		template<typename ToCopyT>
		FastVector(const EmuMath::Vector3<ToCopyT>& toCopy_) : FastVector(toCopy_.x, toCopy_.y, toCopy_.z, 0.0f)
		{
		}
		template<typename ToCopyT>
		FastVector(const EmuMath::Vector4<ToCopyT>& toCopy_) : FastVector(toCopy_.x, toCopy_.y, toCopy_.z, toCopy_.w)
		{
		}

		/// <summary> Outputs this Vector as an EmuMath Vector of the provided size with the provided contained type. </summary>
		/// <typeparam name="OutT_">Type for the output Vector to contain.</typeparam>
		/// <returns>This Vector represented as a more readily readable EmuMath Vector.</returns>
		template<std::size_t OutSize_, typename OutT_>
		typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type As() const
		{
			using OutVector_ = typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type;
			if constexpr (OutSize_ == 2)
			{
				return OutVector_(vectorData.m128_f32[0], vectorData.m128_f32[1]);
			}
			else if constexpr (OutSize_ == 3)
			{
				return OutVector_(vectorData.m128_f32[0], vectorData.m128_f32[1], vectorData.m128_f32[2]);
			}
			else if constexpr (OutSize_ == 4)
			{
				return OutVector_(vectorData.m128_f32[0], vectorData.m128_f32[1], vectorData.m128_f32[2], vectorData.m128_f32[3]);
			}
			else
			{
				static_assert(false, "Attempted to output an EmuMath FastVector as in invalidly sized EmuMath Vector.");
				return OutVector_();
			}
		}
		/// <summary> Outputs a shuffled version of this Vector as an EmuMath Vector of the contained type. </summary>
		/// <typeparam name="OutT_">Type for the output Vector to contain.</typeparam>
		/// <returns>Shuffled version of this Vector represented as a more readily readable EmuMath Vector.</returns>
		template<typename OutT_, std::size_t X_, std::size_t Y_>
		EmuMath::Vector2<OutT_> AsShuffled() const
		{
			return EmuMath::Vector2<OutT_>(this->_get_value<X_>(), this->_get_value<Y_>());
		}
		/// <summary> Outputs a shuffled version of this Vector as an EmuMath Vector of the contained type. </summary>
		/// <typeparam name="OutT_">Type for the output Vector to contain.</typeparam>
		/// <returns>Shuffled version of this Vector represented as a more readily readable EmuMath Vector.</returns>
		template<typename OutT_, std::size_t X_, std::size_t Y_, std::size_t Z_>
		EmuMath::Vector3<OutT_> AsShuffled() const
		{
			return EmuMath::Vector3<OutT_>(this->_get_value<X_>(), this->_get_value<Y_>(), this->_get_value<Z_>());
		}
		/// <summary> Outputs a shuffled version of this Vector as an EmuMath Vector of the contained type. </summary>
		/// <typeparam name="OutT_">Type for the output Vector to contain.</typeparam>
		/// <returns>Shuffled version of this Vector represented as a more readily readable EmuMath Vector.</returns>
		template<typename OutT_, std::size_t X_, std::size_t Y_, std::size_t Z_, std::size_t W_>
		EmuMath::Vector4<OutT_> AsShuffled() const
		{
			return EmuMath::Vector4<OutT_>(this->_get_value<X_>(), this->_get_value<Y_>(), this->_get_value<Z_>(), this->_get_value<W_>());
		}

	private:
		template<std::size_t Index_>
		float _get_value() const
		{
			if constexpr (Index_ < size())
			{
				return vectorData.m128_f32[Index_];
			}
			else
			{
				static_assert(false, "Attempted to get an invalid Index from an EmuMath FastVector.");
			}
		}

		__m128 vectorData;
	};
}

#endif