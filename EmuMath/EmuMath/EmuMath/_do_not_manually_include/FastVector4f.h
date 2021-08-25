#ifndef EMU_MATH_FAST_VECTOR_4_FLOAT_H_INC_
#define EMU_MATH_FAST_VECTOR_4_FLOAT_H_INC_

#include "../SIMDHelpers.h"
#include "../Vector.h"
#include <immintrin.h>
#include <ostream>

namespace EmuMath
{
	/// <summary>
	/// <para> Vector of 4 floating points designed to make full use of SIMD intrinsics. </para>
	/// </summary>
	struct FastVector4f
	{
		/// <summary> The number of items contained within this vector. </summary>
		static constexpr std::size_t size = 4;
		/// <summary> The size of an individual item within this vector in bytes. </summary>
		static constexpr std::size_t contained_item_byte_size = sizeof(float);
		/// <summary> The total size of contained items within this vector in bytes. </summary>
		static constexpr std::size_t total_contained_bytes = contained_item_byte_size * size;
		/// <summary> The number of bits consumed by a single element within this vector in terms of 8-bit bytes. This is not guaranteed to match up to CHAR_BIT. </summary>
		static constexpr std::size_t register_element_8bit_num_bits = contained_item_byte_size * 8;

#pragma region CONSTRUCTORS
		FastVector4f() : data_()
		{
		}
		/// <summary> Constructs this vector with its associated register initialised as a copy of the passed register. </summary>
		/// <param name="dataToCopy_">Register to copy to this vector's register.</param>
		FastVector4f(__m128 dataToCopy_) : data_(dataToCopy_)
		{
		}
		/// <summary> Constructs this vector as a copy of the passed vector. </summary>
		/// <param name="toCopy_">EmuMath FastVector of the same type to copy.</param>
		FastVector4f(const FastVector4f& toCopy_) : data_(toCopy_.data_)
		{
		}
		/// <summary> Constructs this vector by loading the data of the passed EmuMath vector into its associated register. </summary>
		/// <param name="toLoad_">EmuMath vector to load the data of.</param>
		FastVector4f(const EmuMath::Vector<4, float>& toLoad_) : data_(_mm_load_ps(toLoad_.data()))
		{
		}
		/// <summary>
		/// <para> Constructs this vector with its associated register initialised as a copy of the passed EmuMath vector. </para>
		/// <para> If the vector is not at least 4 elements in size, non-existent elements will be assumed as 0. </para>
		/// </summary>
		/// <param name="toCopy_">EmuMath vector to copy the data of.</param>
		template<std::size_t ToCopySize_, typename to_copy_contained_type>
		FastVector4f(const EmuMath::Vector<ToCopySize_, to_copy_contained_type>& toCopy_) : 
			FastVector4f
			(
				EmuMath::Helpers::VectorGetTheoretical<0, float>(toCopy_),
				EmuMath::Helpers::VectorGetTheoretical<1, float>(toCopy_),
				EmuMath::Helpers::VectorGetTheoretical<2, float>(toCopy_),
				EmuMath::Helpers::VectorGetTheoretical<3, float>(toCopy_)
			)
		{
		}
		/// <summary> Constructs this vector with its associated register initialised as a copy of the passed respective elements. </summary>
		/// <typeparam name="X_">Type used for argument x_, which is copied to element 0.</typeparam>
		/// <typeparam name="Y_">Type used for argument y_, which is copied to element 1.</typeparam>
		/// <typeparam name="Z_">Type used for argument z_, which is copied to element 2.</typeparam>
		/// <typeparam name="W_">Type used for argument w_, which is copied to element 3.</typeparam>
		/// <param name="x_">Value to copy to element 0. Must be convertible to this vector's float.</param>
		/// <param name="y_">Value to copy to element 1. Must be convertible to this vector's float.</param>
		/// <param name="z_">Value to copy to element 2. Must be convertible to this vector's float.</param>
		/// <param name="w_">Value to copy to element 3. Must be convertible to this vector's float.</param>
		template<typename X_, typename Y_, typename Z_, typename W_>
		FastVector4f(X_&& x_, Y_&& y_, Z_&& z_, W_&& w_) : 
			data_
			(
				_mm_set_ps
				(
					static_cast<float>(std::forward<W_>(w_)),
					static_cast<float>(std::forward<Z_>(z_)),
					static_cast<float>(std::forward<Y_>(y_)),
					static_cast<float>(std::forward<X_>(x_))
				)
			)
		{
		}
#pragma endregion

#pragma region RANDOM_ACCESS
		/// <summary>
		/// <para> Returns a copy of the element at the provided index, where 0 is X, 1 Y, 2 Z, and 3 W. </para>
		/// <para> This may not be used to reference an index value directly. For such behaviours, one should use a normal EmuMath::Vector type. </para>
		/// </summary>
		/// <returns>Copy of the value at the provided index.</returns>
		template<std::size_t Index_>
		inline float at() const
		{
			if constexpr (Index_ < size)
			{
				if constexpr (Index_ == 0)
				{
					return _mm_cvtss_f32(data_);
				}
				else
				{
					return _mm_cvtss_f32(EmuMath::SIMD::shuffle<Index_, 1, 2, 3>(data_));
				}
			}
			else
			{
				static_assert(false, "Attempted to retrieve an invalid index from an EmuMath::FastVector4f.");
			}
		}
#pragma endregion

#pragma region SETS
		/// <summary>
		/// <para> Sets the data at the provided index to copy the passed data, which must be convertible to this vector's float. </para>
		/// <para> This is increasingly inefficient with more sets, and is seldom recommended with a FastVector. </para>
		/// </summary>
		/// <typeparam name="ToCopy_">Type to be copying.</typeparam>
		/// <param name="toCopyAtIndex_">Value to copy to the provided index.</param>
		template<std::size_t Index_, typename ToCopy_>
		inline void Set(ToCopy_&& toCopyAtIndex_)
		{
			if constexpr (std::is_convertible_v<ToCopy_, float>)
			{
				if constexpr (Index_ < size)
				{
					__m128 mask_ = EmuMath::SIMD::index_mask<__m128, Index_, register_element_8bit_num_bits>();
					data_ = _mm_or_ps
					(
						_mm_andnot_ps(mask_, data_),
						_mm_and_ps
						(
							mask_,
							_mm_set_ps1(static_cast<float>(std::forward<ToCopy_>(toCopyAtIndex_)))
						)
					);
				}
				else
				{
					static_assert(false, "Attempted to set an invalid index within an EmuMath::FastVector4f.");
				}
			}
			else
			{
				static_assert(false, "Attempted to set an index of an EmuMath::FastVector4f via a type that cannot be converted to its contained float.");
			}
		}
		template<typename ToCopy_>
		inline void Set(ToCopy_&& toCopy_)
		{
			if constexpr (EmuMath::TMP::is_emu_vector_v<ToCopy_>)
			{
				// Defer to set (x, y, z, w) since passing an EmuMath vector is assumed to mean "copy the data of this vector"
				this->Set
				(
					EmuMath::Helpers::VectorGetTheoretical<0, float>(toCopy_),
					EmuMath::Helpers::VectorGetTheoretical<1, float>(toCopy_),
					EmuMath::Helpers::VectorGetTheoretical<2, float>(toCopy_),
					EmuMath::Helpers::VectorGetTheoretical<3, float>(toCopy_)
				);
			}
			else
			{
				if constexpr (std::is_same_v<ToCopy_, FastVector4f>)
				{
					// Simple register copy
					data_ = std::forward<ToCopy_>(toCopy_).data_;
				}
				else if constexpr (std::is_convertible_v<ToCopy_, float>)
				{
					data_ = _mm_set_ps1(static_cast<float>(std::forward<ToCopy_>(toCopy_)));
				}
				else
				{
					static_assert(false, "Attempted to set an EmuMath::FastVector4f via an invalid type.");
				}
			}
		}
		/// <summary>
		/// <para> Sets the data of this vector to copies of the provided respective values. </para>
		/// <para> All provided values must be convertible to this vector's float. </para>
		/// </summary>
		/// <typeparam name="X_">Type of the provided x_ argument.</typeparam>
		/// <typeparam name="Y_">Type of the provided y_ argument.</typeparam>
		/// <typeparam name="Z_">Type of the provided z_ argument.</typeparam>
		/// <typeparam name="W_">Type of the provided w_ argument.</typeparam>
		/// <param name="x_">Value to copy to this vector's 0th component.</param>
		/// <param name="y_">Value to copy to this vector's 1st component.</param>
		/// <param name="z_">Value to copy to this vector's 2nd component.</param>
		/// <param name="w_">Value to copy to this vector's 3rd component.</param>
		template<typename X_, typename Y_, typename Z_, typename W_>
		inline void Set(X_&& x_, Y_&& y_, Z_&& z_, W_&& w_)
		{
			data_ = _mm_set_ps
			(
				static_cast<float>(std::forward<W_>(w_)),
				static_cast<float>(std::forward<Z_>(z_)),
				static_cast<float>(std::forward<Y_>(y_)),
				static_cast<float>(std::forward<X_>(x_))
			);
		}

		/// <summary>
		/// <para> Loads the provided EmuMath vector into this vector using the provided indices. </para>
		/// <para> If a provided index is out of the passed vector's valid range, it will be assumed as 0. </para>
		/// </summary>
		/// <param name="toLoad_">EmuMath vector to load into this vector, using the provided indices.</param>
		template<std::size_t X_, std::size_t Y_, std::size_t Z_, std::size_t W_, std::size_t ToLoadSize_, typename to_load_contained_type>
		inline void LoadIndices(const EmuMath::Vector<ToLoadSize_, to_load_contained_type>& toLoad_)
		{
			this->Set
			(
				EmuMath::Helpers::VectorGetTheoretical<X_, float>(toLoad_),
				EmuMath::Helpers::VectorGetTheoretical<Y_, float>(toLoad_),
				EmuMath::Helpers::VectorGetTheoretical<Z_, float>(toLoad_),
				EmuMath::Helpers::VectorGetTheoretical<W_, float>(toLoad_)
			);
		}

		/// <summary>
		/// <para> Loads the passed pointed-to data contiguously into this vector. </para>
		/// <para> This function assumes the passed pointer is safe to load into the width of this vector. </para>
		/// </summary>
		/// <param name="pData_">Pointer to contiguous data to load into this vector.</param>
		inline void LoadContiguous(const float* pData_)
		{
			data_ = _mm_load_ps(pData_);
		}
		/// <summary>
		/// <para> Loads the passed EmuMath vector contiguously into this vector, with an optional offset of the starting index to load from. </para>
		/// <para>
		///		By default, respective indices are loaded into this vector. 
		///		To perform a fully bitwise contiguous load, set the Bitwise_ template argument to true.
		/// </para>
		/// <para> Note that Bitwise_ may not be true if passing a vector which contains reference wrappers. </para>
		/// </summary>
		/// <param name="toLoad_">EmuMath vector to load into this vector.</param>
		template<bool Bitwise_ = false, std::size_t IndexOffset_ = 0, std::size_t ToLoadSize_, typename to_load_contained_type>
		inline void LoadContiguous(const EmuMath::Vector<ToLoadSize_, to_load_contained_type>& toLoad_)
		{
			if constexpr (Bitwise_)
			{
				using vec_info = typename EmuMath::Vector<ToLoadSize_, to_load_contained_type>::vector_info;

				// Only allow well-defined loads of reference wrappers when copying, rather than copying contiguous bits
				if constexpr (!vec_info::contains_reference_wrappers)
				{
					constexpr std::size_t bytes_to_copy = (vec_info::total_contained_bytes - (IndexOffset_ * vec_info::contained_item_byte_size));
					if constexpr (bytes_to_copy >= total_contained_bytes)
					{
						this->LoadContiguous(reinterpret_cast<const float*>(toLoad_.data() + IndexOffset_));
					}
					else
					{
						float copyData[4] = { 0.0f };
						memcpy(copyData, toLoad_.data() + IndexOffset_, bytes_to_copy);
						this->LoadContiguous(copyData);
					}
				}
				else
				{
					static_assert
					(
						false,
						"Attempted to perform a bitwise contiguous load of an EmuMath vector which contains references. Contiguous loads of reference-containing vectors may only be performed with the Bitwise_ argument set to false."
					);
				}
			}
			else
			{
				this->Set
				(
					EmuMath::Helpers::VectorGetTheoretical<IndexOffset_ + 0, float>(toLoad_),
					EmuMath::Helpers::VectorGetTheoretical<IndexOffset_ + 1, float>(toLoad_),
					EmuMath::Helpers::VectorGetTheoretical<IndexOffset_ + 2, float>(toLoad_),
					EmuMath::Helpers::VectorGetTheoretical<IndexOffset_ + 3, float>(toLoad_)
				);
			}
		}
#pragma endregion

#pragma region CONST_OPERATORS
		[[nodiscard]] inline bool operator==(__m128 rhs_) const
		{
			return EmuMath::SIMD::all_equal(data_, rhs_);
		}
		[[nodiscard]] inline bool operator==(const FastVector4f& rhs_) const
		{
			return this->operator==(rhs_.data_);
		}

		[[nodiscard]] inline bool operator!=(__m128 rhs_) const
		{
			return EmuMath::SIMD::any_not_equal(data_, rhs_);
		}
		[[nodiscard]] inline bool operator!=(const FastVector4f& rhs_) const
		{
			return this->operator==(rhs_.data_);
		}
#pragma endregion

#pragma region NON_CONST_OPERATORS

#pragma endregion

#pragma region PERMUTATIONS

#pragma endregion

#pragma region ARITHMETIC

#pragma endregion

#pragma region VECTOR_OPERATIONS
		/// <summary> Returns the dot product of this vector with the provided vector data. </summary>
		/// <typeparam name="OutT_">Type to output the dot product as.</typeparam>
		/// <param name="b_">Data to calculate the dot product of with this vector.</param>
		/// <returns>Dot product of this vector and the provided data b_.</returns>
		template<typename OutT_ = float>
		[[nodiscard]] inline OutT_ DotProduct(__m128 b_) const
		{
			return static_cast<OutT_>(_mm_cvtss_f32(_calculate_dot_single(b_)));
		}
		template<typename OutT_ = float>
		[[nodiscard]] inline OutT_ DotProduct(const FastVector4f& b_) const
		{
			return DotProduct(b_.data_);
		}

		/// <summary> Calculates the squared magnitude of this vector. </summary>
		/// <typeparam name="OutT_">Type to output the square magnitude as.</typeparam>
		/// <returns>Square magnitude of this vector (i.e. its magnitude before a sqrt operation is performed).</returns>
		template<typename OutT_ = float>
		[[nodiscard]] inline OutT_ SquareMagnitude() const
		{
			return this->template DotProduct<OutT_>(data_);
		}

		/// <summary> Calculates the magnitude of this vector. </summary>
		/// <typeparam name="OutT_">Type to output the magnitude as.</typeparam>
		/// <returns>Magnitude of this vector.</returns>
		template<typename OutT_ = float>
		[[nodiscard]] inline OutT_ Magnitude() const
		{
			return static_cast<OutT_>(sqrtf(this->template SquareMagnitude<float>()));
		}

		/// <summary> Calculates the reciprocal to the magnitude of this vector. </summary>
		/// <typeparam name="OutT_">Type to output the magnitude reciprocal as.</typeparam>
		/// <returns>Reciprocal to this vector's magnitude.</returns>
		template<typename OutT_ = float>
		[[nodiscard]] inline OutT_ MagnitudeReciprocal() const
		{
			__m128 mag_reciprocal = _calculate_dot_single(data_);
			mag_reciprocal = _mm_rsqrt_ps(mag_reciprocal);
			return _mm_cvtss_f32(mag_reciprocal);
		}

		/// <summary> Normalises the elements of this vector. </summary>
		/// <returns>Copy of this vector with its elements normalised to result in a magnitude of 1.</returns>
		[[nodiscard]] inline FastVector4f Normalise() const
		{
			__m128 mag_reciprocal = _calculate_dot_fill(data_);
			mag_reciprocal = _mm_rsqrt_ps(mag_reciprocal);
			return FastVector4f(_mm_mul_ps(data_, mag_reciprocal));
		}

		/// <summary>
		/// <para> Linearly interpolates the elements of this vector with respective elements in the data of b_, using respective elements in t_ as weighting. </para>
		/// <para> A scalar may be provided for t_. When it is, all elements of t_ in the lerp equation will be considered the same. </para>
		/// <para> This vector acts as a in the equation a + ((b - a) * t). </para>
		/// </summary>
		/// <param name="b_">Vector data to linearly interpolate this vector with. b in the equation a + ((b - a) * t).</param>
		/// <param name="t_">Scalar or vector weighting to use for each linear interpolation. t in the equation a + ((b - a) * t).</param>
		[[nodiscard]] inline FastVector4f Lerp(__m128 b_, __m128 t_) const
		{
			b_ = _mm_sub_ps(b_, data_);
			return FastVector4f(_mm_fmadd_ps(b_, t_, data_));
		}
		[[nodiscard]] inline FastVector4f Lerp(__m128 b_, const FastVector4f& t_) const
		{
			return this->Lerp(b_, t_.data_);
		}
		[[nodiscard]] inline FastVector4f Lerp(__m128 b_, const float t_) const
		{
			return this->Lerp(b_, _mm_broadcast_ss(&t_));
		}
		[[nodiscard]] inline FastVector4f Lerp(const FastVector4f& b_, __m128 t_) const
		{
			return this->Lerp(b_.data_, t_);
		}
		[[nodiscard]] inline FastVector4f Lerp(const FastVector4f& b_, const FastVector4f& t_) const
		{
			return this->Lerp(b_.data_, t_.data_);
		}
		[[nodiscard]] inline FastVector4f Lerp(const FastVector4f& b_, const float t_) const
		{
			return this->Lerp(b_.data_, _mm_broadcast_ss(&t_));
		}

		/// <summary> Calculates the cosine of the angle between this vector and the vector data of b_. </summary>
		/// <typeparam name="OutCosine_">Type to output the cosine as.</typeparam>
		/// <param name="b_">Vector data to find the cosine of the angle residing between itself and this vector.</param>
		/// <returns>Cosine of the angle between this vector and b_.</returns>
		template<typename OutCosine_ = float>
		[[nodiscard]] inline OutCosine_ AngleCosine(__m128 b_) const
		{
			__m128 b_sqr_mag_ = _mm_mul_ps(b_, b_);
			b_sqr_mag_ = EmuMath::SIMD::horizontal_vector_sum(b_sqr_mag_);
			__m128 out_ = _mm_rsqrt_ps(_mm_mul_ps(b_sqr_mag_, _calculate_dot_single(data_)));
			out_ = _mm_mul_ps(out_, _calculate_dot_single(b_));
			return _mm_cvtss_f32(out_);
		}
		template<typename OutCosine_ = float>
		[[nodiscard]] inline OutCosine_ AngleCosine(const FastVector4f& b_) const
		{
			return this->template AngleCosine<OutCosine_>(b_.data_);
		}

		/// <summary>
		/// <para> Calculates the angle between this vector and the vector data of b_. </para>
		/// <para> This angle will be output in radians. To output as degrees, change the Rads_ template argument to false. </para>
		/// </summary>
		/// <typeparam name="OutAngle_">Type to output the angle as.</typeparam>
		/// <param name="b_">Vector data to find the angle residing between itself and this vector.</param>
		/// <returns>Angle between this vector and b_, measured in radian units if Rads_ is true, otherwise measured in degree units.</returns>
		template<bool Rads_ = true, typename OutAngle_ = float>
		[[nodiscard]] inline OutAngle_ Angle(__m128 b_) const
		{
			__m128 b_sqr_mag_ = _mm_mul_ps(b_, b_);
			b_sqr_mag_ = EmuMath::SIMD::horizontal_vector_sum(b_sqr_mag_);
			__m128 out_ = _mm_rsqrt_ps(_mm_mul_ps(b_sqr_mag_, _calculate_dot_single(data_)));
			out_ = _mm_mul_ps(out_, _calculate_dot_single(b_));
			out_ = _mm_acos_ps(out_);
			if constexpr (!Rads_)
			{
				out_ = _mm_mul_ps(out_, _mm_set_ps1(EmuCore::Pi::HUNDRED80_DIV_PI<float>));
			}
			return _mm_cvtss_f32(out_);
		}
		template<bool Rads_ = true, typename OutAngle_ = float>
		[[nodiscard]] inline OutAngle_ Angle(FastVector4f b_) const
		{
			return this->template Angle<Rads_, OutAngle_>(b_.data_);
		}

		/// <summary> Calculates the distance that may be added to this vector to reach the target_ vector. </summary>
		/// <param name="target_">Vector data of the point to calculate the distance from this vector.</param>
		/// <returns>Vector which may be added to this vector to reach the provided target_.</returns>
		[[nodiscard]] inline FastVector4f Distance(__m128 target_) const
		{
			return FastVector4f(_mm_sub_ps(target_, data_));
		}
		[[nodiscard]] inline FastVector4f Distance(FastVector4f target_) const
		{
			return this->Distance(target_.data_);
		}

		/// <summary>
		/// <para> Calculates the cross product of this vector and vector b_ (a_ x b_, where this vector is a_). </para>
		/// </summary>
		/// <param name="b_">Vector data to calculate the cross product of with this vector. b_ in the equation a_ x b_.</param>
		/// <returns>Vector of the 3D cross product between this vector and the provided vector data in b_.</returns>
		[[nodiscard]] inline FastVector4f CrossProduct(__m128 b_) const
		{
			__m128 a_1203_ = EmuMath::SIMD::shuffle<1, 2, 0, 3>(data_);
			__m128 to_subract_ = EmuMath::SIMD::shuffle<1, 2, 0, 3>(_mm_mul_ps(a_1203_, b_));
			return FastVector4f(_mm_fmsub_ps(a_1203_, EmuMath::SIMD::shuffle<2, 0, 1, 3>(b_), to_subract_));
		}
		[[nodiscard]] inline FastVector4f CrossProduct(FastVector4f b_) const
		{
			return this->CrossProduct(b_.data_);
		}

		/// <summary> Calculates the square root of all elements within this vector. </summary>
		/// <returns>Copy of this vector with all elements set to their square roots.</returns>
		[[nodiscard]] inline FastVector4f Sqrt() const
		{
			return FastVector4f(_mm_sqrt_ps(data_));
		}

		/// <summary> Rounds all elements within this vector toward negative infinity. </summary>
		/// <returns>Copy of this vector with all elements floored.</returns>
		[[nodiscard]] inline FastVector4f Floor() const
		{
			return FastVector4f(_mm_round_ps(data_, _MM_FROUND_FLOOR));
		}
		
		/// <summary> Rounds all elements within this vector toward positive infinity. </summary>
		/// <returns>Copy of this vector with all elements ceiled.</returns>
		[[nodiscard]] inline FastVector4f Ceil() const
		{
			return FastVector4f(_mm_round_ps(data_, _MM_FROUND_CEIL));
		}

		/// <summary> Rounds all elements within this vector toward 0. </summary>
		/// <returns>Copy of this vector with all elements trunced.</returns>
		[[nodiscard]] inline FastVector4f Trunc() const
		{
			return FastVector4f(_mm_round_ps(data_, _MM_FROUND_TRUNC));
		}

		/// <summary> Clamps the values within this vector so they are not less than the respective data within min_. </summary>
		/// <returns>Copy of this vector with all elements clamped to not be less than min_.</returns>
		[[nodiscard]] inline FastVector4f ClampMin(__m128 min_) const
		{
			__m128 keep_mask_ = _mm_cmpge_ps(data_, min_);
			return FastVector4f(_mm_or_ps(_mm_and_ps(keep_mask_, data_), _mm_andnot_ps(keep_mask_, min_)));
		}
		[[nodiscard]] inline FastVector4f ClampMin(const FastVector4f& min_) const
		{
			return this->ClampMin(min_.data_);
		}
		[[nodiscard]] inline FastVector4f ClampMin(const float min_) const
		{
			return this->ClampMin(_mm_broadcast_ss(&min_));
		}

		/// <summary> Clamps the values within this vector so they are not greater than the respective data within max_. </summary>
		/// <returns>Copy of this vector with all elements clamped to not be greater than max_.</returns>
		[[nodiscard]] inline FastVector4f ClampMax(__m128 max_) const
		{
			__m128 keep_mask_ = _mm_cmple_ps(data_, max_);
			return FastVector4f(_mm_or_ps(_mm_and_ps(keep_mask_, data_), _mm_andnot_ps(keep_mask_, max_)));
		}
		[[nodiscard]] inline FastVector4f ClampMax(const FastVector4f& max_) const
		{
			return this->ClampMax(max_.data_);
		}
		[[nodiscard]] inline FastVector4f ClampMax(const float max_) const
		{
			return this->ClampMax(_mm_broadcast_ss(&max_));
		}

		/// <summary> 
		/// <para> Clamps the values within this vector so they are neither less than the respective data in min_, nor greater than the respective data within max_. </para>
		/// <para> The provided min_ and max_ values are assumed to be fully logically correct (i.e. min_ &lt;= max_ in all scenarios). </para>
		/// <para> If min_ and max_ are not logically correct, output may potentially appear as nonsense. </para>
		/// </summary>
		/// <returns>Copy of this vector with all elements clamped to not be greater than max_.</returns>
		[[nodiscard]] inline FastVector4f Clamp(__m128 min_, __m128 max_) const
		{
			__m128 replace_min_mask_ = _mm_cmplt_ps(data_, min_);
			__m128 replace_max_mask_ = _mm_cmpgt_ps(data_, max_);
			__m128 out_ = _mm_andnot_ps(_mm_or_ps(replace_min_mask_, replace_max_mask_), data_);
			out_ = _mm_or_ps(out_, _mm_and_ps(replace_min_mask_, min_));
			return FastVector4f(_mm_or_ps(out_, _mm_and_ps(replace_max_mask_, max_)));
		}
		[[nodiscard]] inline FastVector4f Clamp(const FastVector4f& min_, __m128 max_) const
		{
			return this->Clamp(min_.data_, max_);
		}
		[[nodiscard]] inline FastVector4f Clamp(const float min_, __m128 max_) const
		{
			return this->Clamp(_mm_broadcast_ss(&min_), max_);
		}
		[[nodiscard]] inline FastVector4f Clamp(__m128 min_, const FastVector4f& max_) const
		{
			return this->Clamp(min_, max_.data_);
		}
		[[nodiscard]] inline FastVector4f Clamp(const FastVector4f& min_, const FastVector4f& max_) const
		{
			return this->Clamp(min_.data_, max_.data_);
		}
		[[nodiscard]] inline FastVector4f Clamp(const float min_, const FastVector4f& max_) const
		{
			return this->Clamp(_mm_broadcast_ss(&min_), max_.data_);
		}
		[[nodiscard]] inline FastVector4f Clamp(__m128 min_, const float max_) const
		{
			return this->Clamp(min_, _mm_broadcast_ss(&max_));
		}
		[[nodiscard]] inline FastVector4f Clamp(const FastVector4f& min_, const float max_) const
		{
			return this->Clamp(min_.data_, _mm_broadcast_ss(&max_));
		}
		[[nodiscard]] inline FastVector4f Clamp(const float min_, const float max_) const
		{
			return this->Clamp(_mm_broadcast_ss(&min_), _mm_broadcast_ss(&max_));
		}

		/// <summary> Calculates the total of adding all elements within this vector together. </summary>
		/// <typeparam name="OutT_">Type to output the total sum as.</typeparam>
		/// <returns>Total sum of all elements within this vector.</returns>
		template<typename OutT_ = float>
		[[nodiscard]] inline OutT_ HorizontalSum() const
		{
			return static_cast<OutT_>(EmuMath::SIMD::horizontal_vector_sum_scalar(data_));
		}

		/// <summary> Calculates the total of multiplying all elements within this vector together. </summary>
		/// <typeparam name="OutT_">Type to output the total product as.</typeparam>
		/// <returns>Total product of all elements within this vector.</returns>
		template<typename OutT_ = float>
		[[nodiscard]] inline OutT_ HorizontalProduct() const
		{
			__m128 out_ = _mm_mul_ps(data_, EmuMath::SIMD::shuffle<3, 2, 1, 0>(data_));
			out_ = _mm_mul_ps(out_, EmuMath::SIMD::shuffle<1, 0, 2, 3>(out_));
			return static_cast<OutT_>(_mm_cvtss_f32(out_));
		}

		/// <summary> Finds the lowest stored value within this vector. </summary>
		/// <typeparam name="OutT_">Type to output the lowest value as.</typeparam>
		/// <returns>Copy of the lowest value within this vector.</returns>
		template<typename OutT_ = float>
		[[nodiscard]] inline OutT_ Min() const
		{
			__m128 out_ = _mm_min_ps(data_, EmuMath::SIMD::shuffle<3, 2, 1, 0>(data_));
			out_ = _mm_min_ps(out_, EmuMath::SIMD::shuffle<1, 0, 2, 3>(out_));
			return static_cast<OutT_>(_mm_cvtss_f32(out_));
		}

		/// <summary> Finds the highest stored value within this vector. </summary>
		/// <typeparam name="OutT_">Type to output the highest value as.</typeparam>
		/// <returns>Copy of the highest value within this vector.</returns>
		template<typename OutT_ = float>
		[[nodiscard]] inline OutT_ Max() const
		{
			__m128 out_ = _mm_max_ps(data_, EmuMath::SIMD::shuffle<3, 2, 1, 0>(data_));
			out_ = _mm_max_ps(out_, EmuMath::SIMD::shuffle<1, 0, 2, 3>(out_));
			return static_cast<OutT_>(_mm_cvtss_f32(out_));
		}

		/// <summary> Outputs the lowest and highest values stored within this vector via the passed outMin_ and outMax_ references, respectively. </summary>
		/// <typeparam name="OutMin_">Type to output the lowest value as.</typeparam>
		/// <typeparam name="OutMax_">Type to output the highest value as.</typeparam>
		/// <param name="outMin_">Reference to which the lowest value will be output.</param>
		/// <param name="outMax_">Reference to which the highest value will be output.</param>
		template<typename OutMin_, typename OutMax_>
		inline void MinMax(OutMin_& outMin_, OutMax_& outMax_)
		{
			// Main advantage of MinMax over two separate Min() and Max() calls is avoiding duplicating this shuffle
			__m128 reversed_data_ = EmuMath::SIMD::shuffle<3, 2, 1, 0>(data_);

			// Find min
			__m128 out_ = _mm_min_ps(data_, reversed_data_);
			out_ = _mm_min_ps(out_, EmuMath::SIMD::shuffle<1, 0, 2, 3>(out_));
			outMin_ = static_cast<OutMin_>(_mm_cvtss_f32(out_));

			// Find max
			out_ = _mm_max_ps(data_, reversed_data_);
			out_ = _mm_max_ps(out_, EmuMath::SIMD::shuffle<1, 0, 2, 3>(out_));
			outMax_ = static_cast<OutMax_>(_mm_cvtss_f32(out_));
		}
#pragma endregion

#pragma region COMPARISONS

#pragma endregion

#pragma region BITWISE

#pragma endregion

#pragma region CONVERSIONS
		/// <summary>
		/// <para> Stores this vector into the passed EmuMath vector reference. </para>
		/// <para> This function is optimised to store into a 128-bit wide range of this vector's float. If possible, it will store its data by these means. </para>
		/// <para> May provide an additional index offset to start contiguously outputting this vector's data from. </para>
		/// </summary>
		/// <param name="out_">EmuMath vector to store this vector's data in.</param>
		template<std::size_t OutOffset_ = 0, std::size_t OutSize_, typename out_contained_type>
		inline void Store(EmuMath::Vector<OutSize_, out_contained_type>& out_) const
		{
			if constexpr (OutOffset_ < OutSize_)
			{
				constexpr std::size_t num_to_copy = OutSize_ - OutOffset_;
				if constexpr (num_to_copy == 1)
				{
					out_.Set<OutOffset_ + 0, const float>(at<0>());
				}
				else if constexpr (num_to_copy == 2)
				{
					out_.Set<OutOffset_ + 0, const float>(at<0>());
					out_.Set<OutOffset_ + 1, const float>(at<1>());
				}
				else if constexpr (num_to_copy == 3)
				{
					out_.Set<OutOffset_ + 0, const float>(at<0>());
					out_.Set<OutOffset_ + 1, const float>(at<1>());
					out_.Set<OutOffset_ + 2, const float>(at<2>());
				}
				else
				{
					if constexpr (std::is_same_v<float, out_contained_type>)
					{
						_mm_store_ps(out_.data() + OutOffset_, data_);
					}
					else
					{
						out_.Set<OutOffset_ + 0, const float>(at<0>());
						out_.Set<OutOffset_ + 1, const float>(at<1>());
						out_.Set<OutOffset_ + 2, const float>(at<2>());
						out_.Set<OutOffset_ + 3, const float>(at<3>());
					}
				}
			}
			else
			{
				static_assert(false, "Attempted to store an EmuMath::FastVector4f to a normal EmuMath vector, but provided a starting OutOffset_ which is out of the range of the output vector.");
			}
		}
		// <summary>
		/// <para> Stores this vector into an EmuMath vector of the provided OutSize_, containing the provided out_contained_type. </para>
		/// <para> The output EmuMath vector defaults to the EmuMath vector that mirrors this vector in terms of size and float. </para>
		/// <para> This function is optimised to store into a 128-bit wide range of this vector's float. If possible, it will store its data by these means. </para>
		/// <para> May provide an additional index offset to start contiguously outputting this vector's data from. </para>
		/// </summary>
		template<std::size_t OutOffset_ = 0, std::size_t OutSize_ = 4, typename out_contained_type = float>
		inline EmuMath::Vector<OutSize_, out_contained_type> Store() const
		{
			if constexpr (OutOffset_ == 0)
			{
				// For the following branches, simple copy as we have no offset.
				if constexpr (OutSize_ == 1)
				{
					return EmuMath::Vector<OutSize_, out_contained_type>(at<0>());
				}
				else if constexpr (OutSize_ == 2)
				{
					return EmuMath::Vector<OutSize_, out_contained_type>(at<0>(), at<1>());
				}
				else if constexpr (OutSize_ == 3)
				{
					return EmuMath::Vector<OutSize_, out_contained_type>(at<0>(), at<1>(), at<2>());
				}
				else if constexpr (OutSize_ == 4)
				{
					if constexpr (std::is_same_v<float, std::remove_const_t<out_contained_type>>)
					{
						// Faster to load to some dummy floats and then copy the contiguous memory than perform suboptimal at commands several times.
						float to_copy_[4];
						_mm_store_ps(to_copy_, data_);
						return EmuMath::Vector<OutSize_, out_contained_type>(to_copy_, total_contained_bytes);
					}
					else
					{
						return EmuMath::Vector<OutSize_, out_contained_type>(at<0>(), at<1>(), at<2>(), at<3>());
					}
				}
				else
				{
					EmuMath::Vector<OutSize_, out_contained_type> out_ = EmuMath::Vector<OutSize_, out_contained_type>();
					out_.Set<0, const float>(at<0>());
					out_.Set<1, const float>(at<1>());
					out_.Set<2, const float>(at<2>());
					out_.Set<3, const float>(at<3>());
					return out_;
				}
			}
			else
			{
				// Defer call to the alternate Store func since we need to construct a dummy out_ to set anyway.
				EmuMath::Vector<OutSize_, out_contained_type> out_ = EmuMath::Vector<OutSize_, out_contained_type>();
				this->template Store<OutOffset_, OutSize_, out_contained_type>(out_);
				return out_;
			}
		}

		template<std::size_t OutSize_, typename out_contained_type>
		explicit inline operator EmuMath::Vector<OutSize_, out_contained_type>() const
		{
			return this->template Store<0, OutSize_, out_contained_type>();
		}
		explicit inline operator bool() const
		{
			return _mm_movemask_ps(_mm_cmpneq_ps(data_, _mm_setzero_ps()));
		}
		inline bool operator!() const
		{
			return !static_cast<bool>(*this);
		}
#pragma endregion

		/// <summary> SIMD register represeneting this vector's data. This should not be interacted with directly unless you know what you are doing. </summary>
		__m128 data_;

	private:
		/// <summary> Calculates data_ DOT b_, storing the result in the output __m128's first element. </summary>
		inline __m128 _calculate_dot_single(__m128 b_) const
		{
			return EmuMath::SIMD::horizontal_vector_sum(_mm_mul_ps(data_, b_));
		}
		/// <summary> Calculates data_ DOT b_, storing the result in every element of the output __m128. </summary>
		inline __m128 _calculate_dot_fill(__m128 b_) const
		{
			return EmuMath::SIMD::horizontal_vector_sum_fill(_mm_mul_ps(data_, b_));
		}
	};
}

inline std::ostream& operator<<(std::ostream& stream_, const EmuMath::FastVector4f& v4f_)
{
	stream_ << "{ " << v4f_.at<0>() << ", " << v4f_.at<1>() << ", " << v4f_.at<2>() << ", " << v4f_.at<3>() << " }";
	return stream_;
}
inline std::wostream& operator<<(std::wostream& stream_, const EmuMath::FastVector4f& v4f_)
{
	stream_ << L"{ " << v4f_.at<0>() << L", " << v4f_.at<1>() << L", " << v4f_.at<2>() << L", " << v4f_.at<3>() << L" }";
	return stream_;
}

#endif
