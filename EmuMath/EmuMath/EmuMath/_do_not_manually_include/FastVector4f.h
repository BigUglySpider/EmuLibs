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
		[[nodiscard]] inline float at() const
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
		[[nodiscard]] inline FastVector4f operator+(__m128 rhs_) const
		{
			return this->Add(rhs_);
		}
		[[nodiscard]] inline FastVector4f operator+(const FastVector4f& rhs_) const
		{
			return this->Add(rhs_.data_);
		}

		[[nodiscard]] inline FastVector4f operator-(__m128 rhs_) const
		{
			return this->Subtract(rhs_);
		}
		[[nodiscard]] inline FastVector4f operator-(const FastVector4f& rhs_) const
		{
			return this->Subtract(rhs_.data_);
		}
		[[nodiscard]] inline FastVector4f operator-() const
		{
			return this->Negate();
		}

		[[nodiscard]] inline FastVector4f operator*(__m128 rhs_) const
		{
			return this->Multiply(rhs_);
		}
		[[nodiscard]] inline FastVector4f operator*(const FastVector4f& rhs_) const
		{
			return this->Multiply(rhs_.data_);
		}
		[[nodiscard]] inline FastVector4f operator*(const float rhs_) const
		{
			return this->Multiply(_mm_broadcast_ss(&rhs_));
		}

		[[nodiscard]] inline FastVector4f operator/(__m128 rhs_) const
		{
			return this->Divide(rhs_);
		}
		[[nodiscard]] inline FastVector4f operator/(const FastVector4f& rhs_) const
		{
			return this->Divide(rhs_.data_);
		}
		[[nodiscard]] inline FastVector4f operator/(const float rhs_) const
		{
			return this->Divide(_mm_broadcast_ss(&rhs_));
		}

		[[nodiscard]] inline FastVector4f operator%(__m128 rhs_) const
		{
			return this->Mod(rhs_);
		}
		[[nodiscard]] inline FastVector4f operator%(const FastVector4f& rhs_) const
		{
			return this->Mod(rhs_.data_);
		}
		[[nodiscard]] inline FastVector4f operator%(const float rhs_) const
		{
			return this->Mod(_mm_broadcast_ss(&rhs_));
		}

		[[nodiscard]] inline bool operator==(__m128 rhs_) const
		{
			return this->CmpEqualTo(rhs_);
		}
		[[nodiscard]] inline bool operator==(const FastVector4f& rhs_) const
		{
			return this->CmpEqualTo(rhs_.data_);
		}
		[[nodiscard]] inline bool operator==(const float rhs_) const
		{
			return this->CmpEqualTo(rhs_);
		}

		[[nodiscard]] inline bool operator!=(__m128 rhs_) const
		{
			return this->CmpNotEqualTo(rhs_);
		}
		[[nodiscard]] inline bool operator!=(const FastVector4f& rhs_) const
		{
			return this->CmpNotEqualTo(rhs_.data_);
		}
		[[nodiscard]] inline bool operator!=(const float rhs_) const
		{
			return this->CmpNotEqualTo(rhs_);
		}

		[[nodiscard]] inline bool operator>(__m128 rhs_) const
		{
			return this->CmpGreater(rhs_);
		}
		[[nodiscard]] inline bool operator>(const FastVector4f& rhs_) const
		{
			return this->CmpGreater(rhs_.data_);
		}
		[[nodiscard]] inline bool operator>(const float rhs_) const
		{
			return this->CmpGreater(rhs_);
		}

		[[nodiscard]] inline bool operator<(__m128 rhs_) const
		{
			return this->CmpLess(rhs_);
		}
		[[nodiscard]] inline bool operator<(const FastVector4f& rhs_) const
		{
			return this->CmpLess(rhs_.data_);
		}
		[[nodiscard]] inline bool operator<(const float rhs_) const
		{
			return this->CmpLess(rhs_);
		}

		[[nodiscard]] inline bool operator>=(__m128 rhs_) const
		{
			return this->CmpGreaterEqual(rhs_);
		}
		[[nodiscard]] inline bool operator>=(const FastVector4f& rhs_) const
		{
			return this->CmpGreaterEqual(rhs_.data_);
		}
		[[nodiscard]] inline bool operator>=(const float rhs_) const
		{
			return this->CmpGreaterEqual(rhs_);
		}

		[[nodiscard]] inline bool operator<=(__m128 rhs_) const
		{
			return this->CmpLessEqual(rhs_);
		}
		[[nodiscard]] inline bool operator<=(const FastVector4f& rhs_) const
		{
			return this->CmpLessEqual(rhs_.data_);
		}
		[[nodiscard]] inline bool operator<=(const float rhs_) const
		{
			return this->CmpLessEqual(rhs_);
		}

		[[nodiscard]] inline FastVector4f operator&(__m128 rhs_) const
		{
			return this->And(rhs_);
		}
		[[nodiscard]] inline FastVector4f operator&(const FastVector4f& rhs_) const
		{
			return this->And(rhs_.data_);
		}
		[[nodiscard]] inline FastVector4f operator&(const float rhs_) const
		{
			return this->And(_mm_broadcast_ss(&rhs_));
		}

		[[nodiscard]] inline FastVector4f operator|(__m128 rhs_) const
		{
			return this->Or(rhs_);
		}
		[[nodiscard]] inline FastVector4f operator|(const FastVector4f& rhs_) const
		{
			return this->Or(rhs_.data_);
		}
		[[nodiscard]] inline FastVector4f operator|(const float rhs_) const
		{
			return this->Or(_mm_broadcast_ss(&rhs_));
		}

		[[nodiscard]] inline FastVector4f operator^(__m128 rhs_) const
		{
			return this->Xor(rhs_);
		}
		[[nodiscard]] inline FastVector4f operator^(const FastVector4f& rhs_) const
		{
			return this->Xor(rhs_.data_);
		}
		[[nodiscard]] inline FastVector4f operator^(const float rhs_) const
		{
			return this->Xor(_mm_broadcast_ss(&rhs_));
		}

		[[nodiscard]] inline FastVector4f operator<<(const std::size_t num_shifts_) const
		{
			return this->ShiftLeft(num_shifts_);
		}
		[[nodiscard]] inline FastVector4f operator<<(__m128i num_shifts_) const
		{
			return this->ShiftLeft(num_shifts_);
		}

		[[nodiscard]] inline FastVector4f operator>>(const std::size_t num_shifts_) const
		{
			return this->ShiftRight(num_shifts_);
		}
		[[nodiscard]] inline FastVector4f operator>>(__m128i num_shifts_) const
		{
			return this->ShiftRight(num_shifts_);
		}

		[[nodiscard]] inline FastVector4f operator~() const
		{
			return this->Not();
		}
#pragma endregion

#pragma region NON_CONST_OPERATORS
		inline FastVector4f& operator=(__m128 rhs_)
		{
			data_ = rhs_;
			return *this;
		}
		inline FastVector4f& operator=(const FastVector4f& rhs_)
		{
			data_ = rhs_.data_;
			return *this;
		}

		inline FastVector4f& operator+=(__m128 rhs_)
		{
			data_ = _mm_add_ps(data_, rhs_);
			return *this;
		}
		inline FastVector4f& operator+=(const FastVector4f& rhs_)
		{
			return this->operator+=(rhs_.data_);
		}

		inline FastVector4f& operator-=(__m128 rhs_)
		{
			data_ = _mm_sub_ps(data_, rhs_);
			return *this;
		}
		inline FastVector4f& operator-=(const FastVector4f& rhs_)
		{
			return this->operator-=(rhs_.data_);
		}

		inline FastVector4f& operator*=(__m128 rhs_)
		{
			data_ = _mm_mul_ps(data_, rhs_);
			return *this;
		}
		inline FastVector4f& operator*=(const FastVector4f& rhs_)
		{
			return this->operator*=(rhs_.data_);
		}
		inline FastVector4f& operator*=(const float rhs_)
		{
			return this->operator*=(_mm_broadcast_ss(&rhs_));
		}

		inline FastVector4f& operator/=(__m128 rhs_)
		{
			data_ = _mm_div_ps(data_, rhs_);
			return *this;
		}
		inline FastVector4f& operator/=(const FastVector4f& rhs_)
		{
			return this->operator/=(rhs_.data_);
		}
		inline FastVector4f& operator/=(const float rhs_)
		{
			return this->operator/=(_mm_broadcast_ss(&rhs_));
		}

		inline FastVector4f& operator&=(__m128 rhs_)
		{
			data_ = _mm_and_ps(data_, rhs_);
			return *this;
		}
		inline FastVector4f& operator&=(const FastVector4f& rhs_)
		{
			return this->operator&=(rhs_.data_);
		}
		inline FastVector4f& operator&=(const float rhs_)
		{
			return this->operator&=(_mm_broadcast_ss(&rhs_));
		}

		inline FastVector4f& operator|=(__m128 rhs_)
		{
			data_ = _mm_or_ps(data_, rhs_);
			return *this;
		}
		inline FastVector4f& operator|=(const FastVector4f& rhs_)
		{
			return this->operator|=(rhs_.data_);
		}
		inline FastVector4f& operator|=(const float rhs_)
		{
			return this->operator|=(_mm_broadcast_ss(&rhs_));
		}

		inline FastVector4f& operator^=(__m128 rhs_)
		{
			data_ = _mm_xor_ps(data_, rhs_);
			return *this;
		}
		inline FastVector4f& operator^=(const FastVector4f& rhs_)
		{
			return this->operator^=(rhs_.data_);
		}
		inline FastVector4f& operator^=(const float rhs_)
		{
			return this->operator^=(_mm_broadcast_ss(&rhs_));
		}

		inline FastVector4f& operator<<=(const std::size_t num_shifts_)
		{
			__m128i shifted_ = _mm_slli_epi32(*reinterpret_cast<__m128i*>(&data_), static_cast<int>(num_shifts_));
			data_ = *reinterpret_cast<__m128*>(&shifted_);
			return *this;
		}
		inline FastVector4f& operator<<=(__m128i num_shifts_)
		{
			__m128i shifted_ = _mm_sll_epi32(*reinterpret_cast<__m128i*>(&data_), num_shifts_);
			data_ = *reinterpret_cast<__m128*>(&shifted_);
			return *this;
		}

		inline FastVector4f& operator>>=(const std::size_t num_shifts_)
		{
			__m128i shifted_ = _mm_srli_epi32(*reinterpret_cast<__m128i*>(&data_), static_cast<int>(num_shifts_));
			data_ = *reinterpret_cast<__m128*>(&shifted_);
			return *this;
		}
		[[nodiscard]] inline FastVector4f& operator>>=(__m128i num_shifts_)
		{
			__m128i shifted_ = _mm_srl_epi32(*reinterpret_cast<__m128i*>(&data_), num_shifts_);
			data_ = *reinterpret_cast<__m128*>(&shifted_);
			return *this;
		}
#pragma endregion

#pragma region PERMUTATIONS
		template<std::size_t X_, std::size_t Y_, std::size_t Z_, std::size_t W_>
		[[nodiscard]] inline FastVector4f Shuffle() const
		{
			if constexpr (X_ < size && Y_ < size && Z_ < size && W_ < size)
			{
				return FastVector4f(EmuMath::SIMD::shuffle<X_, Y_, Z_, W_>(data_));
			}
			else
			{
				static_assert(false, "Attempted to shuffle an EmuMath FastVector4f, but provided an invalid index for one of the shuffled indices. Only 0-3 (inclusive) are valid indices.");
			}
		}
#pragma endregion

#pragma region ARITHMETIC
		[[nodiscard]] inline FastVector4f Add(__m128 rhs_) const
		{
			return FastVector4f(_mm_add_ps(data_, rhs_));
		}
		[[nodiscard]] inline FastVector4f Add(const FastVector4f& rhs_) const
		{
			return this->Add(rhs_.data_);
		}

		[[nodiscard]] inline FastVector4f Subtract(__m128 rhs_) const
		{
			return FastVector4f(_mm_sub_ps(data_, rhs_));
		}
		[[nodiscard]] inline FastVector4f Subtract(const FastVector4f& rhs_) const
		{
			return this->Subtract(rhs_.data_);
		}

		[[nodiscard]] inline FastVector4f Multiply(__m128 rhs_) const
		{
			return FastVector4f(_mm_mul_ps(data_, rhs_));
		}
		[[nodiscard]] inline FastVector4f Multiply(const FastVector4f& rhs_) const
		{
			return this->Multiply(rhs_.data_);
		}
		[[nodiscard]] inline FastVector4f Multiply(const float rhs_) const
		{
			return this->Multiply(_mm_broadcast_ss(&rhs_));
		}

		[[nodiscard]] inline FastVector4f Divide(__m128 rhs_) const
		{
			return FastVector4f(_mm_div_ps(data_, rhs_));
		}
		[[nodiscard]] inline FastVector4f Divide(const FastVector4f& rhs_) const
		{
			return this->Divide(rhs_.data_);
		}
		[[nodiscard]] inline FastVector4f Divide(const float rhs_) const
		{
			return this->Divide(_mm_broadcast_ss(&rhs_));
		}

		[[nodiscard]] inline FastVector4f Mod(__m128 rhs_) const
		{
			return FastVector4f(_mm_fmod_ps(data_, rhs_));
		}
		[[nodiscard]] inline FastVector4f Mod(const FastVector4f& rhs_) const
		{
			return this->Mod(rhs_.data_);
		}
		[[nodiscard]] inline FastVector4f Mod(const float rhs_) const
		{
			return this->Mod(_mm_broadcast_ss(&rhs_));
		}

		[[nodiscard]] inline FastVector4f Negate() const
		{
			return FastVector4f(_mm_sub_ps(_mm_setzero_ps(), data_));
		}
#pragma endregion

#pragma region VECTOR_OPERATIONS
		/// <summary> Returns the dot product of this vector with the provided vector data. </summary>
		/// <typeparam name="OutT_">Type to output the dot product as.</typeparam>
		/// <param name="b_">Data to calculate the dot product of with this vector.</param>
		/// <returns>Dot product of this vector and the provided data b_.</returns>
		template<typename OutT_ = float>
		[[nodiscard]] inline OutT_ DotProduct(__m128 b_) const
		{
			return static_cast<OutT_>(_mm_cvtss_f32(EmuMath::SIMD::dot_product(data_, b_)));
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
			__m128 mag_reciprocal = EmuMath::SIMD::dot_product(data_, data_);
			mag_reciprocal = _mm_rsqrt_ps(mag_reciprocal);
			return _mm_cvtss_f32(mag_reciprocal);
		}

		/// <summary> Normalises the elements of this vector. </summary>
		/// <returns>Copy of this vector with its elements normalised to result in a magnitude of 1.</returns>
		[[nodiscard]] inline FastVector4f Normalise() const
		{
			__m128 mag_reciprocal = EmuMath::SIMD::dot_product_fill(data_, data_);
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
			__m128 a_sqr_mag_ = EmuMath::SIMD::dot_product(data_, data_);
			__m128 b_sqr_mag_ = EmuMath::SIMD::dot_product(b_, b_);
			__m128 out_ = _mm_rsqrt_ps(_mm_mul_ps(a_sqr_mag_, b_sqr_mag_));
			out_ = _mm_mul_ps(out_, EmuMath::SIMD::dot_product(data_, b_));
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
			__m128 out_ = _mm_rsqrt_ps(_mm_mul_ps(b_sqr_mag_, EmuMath::SIMD::dot_product(data_, data_)));
			out_ = _mm_mul_ps(out_, EmuMath::SIMD::dot_product(data_, b_));
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

		/// <summary> Outputs a new vector which contains the lowest element at each respective index within this vector and the passed vector data. </summary>
		/// <param name="b_">Vector data to compare this vector with when selecting the lowest elements.</param>
		/// <returns>Vector containing the lowest elements of respective indices between this vector and the passed vector.</returns>
		[[nodiscard]] inline FastVector4f MinVector(__m128 b_) const
		{
			return FastVector4f(_mm_min_ps(data_, b_));
		}
		[[nodiscard]] inline FastVector4f MinVector(const FastVector4f& b_) const
		{
			return this->MinVector(b_.data_);;
		}
		[[nodiscard]] inline FastVector4f MinVector(const float b_) const
		{
			return this->MinVector(_mm_broadcast_ss(&b_));
		}

		/// <summary> Outputs a new vector which contains the greatest element at each respective index within this vector and the passed vector data. </summary>
		/// <param name="b_">Vector data to compare this vector with when selecting the greatest elements.</param>
		/// <returns>Vector containing the greatest elements of respective indices between this vector and the passed vector.</returns>
		[[nodiscard]] inline FastVector4f MaxVector(__m128 b_) const
		{
			return FastVector4f(_mm_max_ps(data_, b_));
		}
		[[nodiscard]] inline FastVector4f MaxVector(const FastVector4f& b_) const
		{
			return this->MaxVector(b_.data_);;
		}
		[[nodiscard]] inline FastVector4f MaxVector(const float b_) const
		{
			return this->MaxVector(_mm_broadcast_ss(&b_));
		}

		/// <summary> 
		/// <para> Outputs a new vector which contains the greatest element at each respective index within this vector and the passed vector data. </para>
		/// <para> A boolean template argument is required for each index. If the argument is true, that index will be the min; if it is false, the index will be the max. </para>
		/// </summary>
		/// <param name="b_">Vector data to compare this vector with when selecting the lowest/greatest elements.</param>
		/// <returns>Vector containing the lowest/greatest elements of respective indices between this vector and the passed vector, depending on passed template args.</returns>
		template<bool XMin_, bool YMin_, bool ZMin_, bool WMin_>
		[[nodiscard]] inline FastVector4f MinMaxVector(__m128 b_) const
		{
			if constexpr (XMin_ == YMin_ && YMin_ == ZMin_ && ZMin_ == WMin_)
			{
				// Defer to min or max as that function would be faster due to avoiding non-required masks, since we are only doing one operation with these args
				if constexpr (XMin_ == true)
				{
					return this->MinVector(b_);
				}
				else
				{
					return this->MaxVector(b_);
				}
			}
			else
			{
				__m128 mask_ = EmuMath::SIMD::index_mask_m128<XMin_, YMin_, ZMin_, WMin_>();
				__m128 out_ = _mm_and_ps(mask_, _mm_min_ps(data_, b_));
				out_ = _mm_or_ps(out_, _mm_andnot_ps(mask_, _mm_max_ps(data_, b_)));
				return FastVector4f(out_);
			}
		}
		template<bool XMin_, bool YMin_, bool ZMin_, bool WMin_>
		[[nodiscard]] inline FastVector4f MinMaxVector(const FastVector4f& b_) const
		{
			return this->MinMaxVector<XMin_, YMin_, ZMin_, WMin_>(b_.data_);
		}
		template<bool XMin_, bool YMin_, bool ZMin_, bool WMin_>
		[[nodiscard]] inline FastVector4f MinMaxVector(const float b_) const
		{
			return this->template MinMaxVector<XMin_, YMin_, ZMin_, WMin_>(_mm_broadcast_ss(&b_));
		}

		/// <summary> Calculates the reciprocal to this vector, which may be multiplied by to achieve the same result as dividing by this vector. </summary>
		/// <returns>Vector that may be multiplied by to achieve the same result as dividing by this vector.</returns>
		[[nodiscard]] inline FastVector4f Reciprocal() const
		{
			return FastVector4f(_mm_div_ps(_mm_set_ps1(1.0f), data_));
		}
#pragma endregion

#pragma region COMPARISONS
		/// <summary> 
		/// <para> If rhs_ is a vector or vector data: returns true if all respective elements are equal. </para>
		/// <para> If rhs_ is a scalar: returns true if the magnitude of this vector is equal to the passed scalar. </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare respective elements to, or scalar to compare magnitude to.</param>
		/// <returns>True if all elements in rhs_ are equal to respective elements in this vector, or if the magnitude of this vector is equal to rhs_ if it is scalar.</returns>
		[[nodiscard]] inline bool CmpEqualTo(__m128 rhs_) const
		{
			return EmuMath::SIMD::all_equal<true, true, true, true>(data_, rhs_);
		}
		[[nodiscard]] inline bool CmpEqualTo(const FastVector4f& rhs_) const
		{
			return this->CmpEqualTo(rhs_.data_);
		}
		[[nodiscard]] inline bool CmpEqualTo(const float rhs_) const
		{
			return this->Magnitude() == rhs_;
		}

		/// <summary> 
		/// <para> If rhs_ is a vector or vector data: returns true if any respective elements are not equal. </para>
		/// <para> If rhs_ is a scalar: returns true if the magnitude of this vector is not equal to the passed scalar. </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare respective elements to, or scalar to compare magnitude to.</param>
		/// <returns>
		///		True if any elements in rhs_ are not equal to respective elements in this vector, or if the magnitude of this vector is equal to rhs_ if it is scalar.
		/// </returns>
		[[nodiscard]] inline bool CmpNotEqualTo(__m128 rhs_) const
		{
			return EmuMath::SIMD::any_not_equal(data_, rhs_);
		}
		[[nodiscard]] inline bool CmpNotEqualTo(const FastVector4f& rhs_) const
		{
			return this->CmpNotEqualTo(rhs_.data_);
		}
		[[nodiscard]] inline bool CmpNotEqualTo(const float rhs_) const
		{
			return this->Magnitude() != rhs_;
		}

		/// <summary> 
		/// <para> If rhs_ is a vector or vector data: returns true if the square magnitude of this vector is greater than that of the rhs_ vector. </para>
		/// <para> If rhs_ is a scalar: returns true if the magnitude of this vector is greater than the passed scalar. </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare square magnitude with, or scalar to compare magnitude to.</param>
		/// <returns>
		///		True if the square magnitude of this vector is greater than that of rhs_, or if the magnitude of this vector is greater than rhs_ if it is scalar.
		/// </returns>
		[[nodiscard]] inline bool CmpGreater(__m128 rhs_) const
		{
			return this->SquareMagnitude() > EmuMath::SIMD::dot_product_scalar(rhs_, rhs_);
		}
		[[nodiscard]] inline bool CmpGreater(const FastVector4f& rhs_) const
		{
			return this->CmpGreater(rhs_.data_);
		}
		[[nodiscard]] inline bool CmpGreater(const float rhs_) const
		{
			return this->Magnitude() > rhs_;
		}

		/// <summary> 
		/// <para> If rhs_ is a vector or vector data: returns true if the square magnitude of this vector is less than that of the rhs_ vector. </para>
		/// <para> If rhs_ is a scalar: returns true if the magnitude of this vector is less than the passed scalar. </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare square magnitude with, or scalar to compare magnitude to.</param>
		/// <returns>
		///		True if the square magnitude of this vector is less than that of rhs_, or if the magnitude of this vector is less than rhs_ if it is scalar.
		/// </returns>
		[[nodiscard]] inline bool CmpLess(__m128 rhs_) const
		{
			return this->SquareMagnitude() < EmuMath::SIMD::dot_product_scalar(rhs_, rhs_);
		}
		[[nodiscard]] inline bool CmpLess(const FastVector4f& rhs_) const
		{
			return this->CmpLess(rhs_.data_);
		}
		[[nodiscard]] inline bool CmpLess(const float rhs_) const
		{
			return this->Magnitude() < rhs_;
		}

		/// <summary> 
		/// <para> If rhs_ is a vector or vector data: returns true if the square magnitude of this vector is greater than or equal to that of the rhs_ vector. </para>
		/// <para> If rhs_ is a scalar: returns true if the magnitude of this vector is greater than or equal to the passed scalar. </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare square magnitude with, or scalar to compare magnitude to.</param>
		/// <returns>
		///		True if the square magnitude of this vector is greater than or equal to that of rhs_, 
		///		or if the magnitude of this vector is greater than or equal to rhs_ if it is scalar.
		/// </returns>
		[[nodiscard]] inline bool CmpGreaterEqual(__m128 rhs_) const
		{
			return this->SquareMagnitude() >= EmuMath::SIMD::dot_product_scalar(rhs_, rhs_);
		}
		[[nodiscard]] inline bool CmpGreaterEqual(const FastVector4f& rhs_) const
		{
			return this->CmpGreaterEqual(rhs_.data_);
		}
		[[nodiscard]] inline bool CmpGreaterEqual(const float rhs_) const
		{
			return this->Magnitude() >= rhs_;
		}

		/// <summary> 
		/// <para> If rhs_ is a vector or vector data: returns true if the square magnitude of this vector is less than or equal to that of the rhs_ vector. </para>
		/// <para> If rhs_ is a scalar: returns true if the magnitude of this vector is less than or equal to the passed scalar. </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare square magnitude with, or scalar to compare magnitude to.</param>
		/// <returns>
		///		True if the square magnitude of this vector is less than or equal to that of rhs_, 
		///		or if the magnitude of this vector is less than or equal to rhs_ if it is scalar.
		/// </returns>
		[[nodiscard]] inline bool CmpLessEqual(__m128 rhs_) const
		{
			return this->SquareMagnitude() <= EmuMath::SIMD::dot_product_scalar(rhs_, rhs_);
		}
		[[nodiscard]] inline bool CmpLessEqual(const FastVector4f& rhs_) const
		{
			return this->CmpLessEqual(rhs_.data_);
		}
		[[nodiscard]] inline bool CmpLessEqual(const float rhs_) const
		{
			return this->Magnitude() <= rhs_;
		}

		/// <summary>
		/// <para> Compares all elements within this vector to the passed vector data, and returns true if all desired elements are equal. </para>
		/// <para> By default this will test for all elements. To ignore an element's result, set its respective boolean template argument to false. </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare this vector's data to.</param>
		/// <returns>True if all desired elements' comparisons were true, otherwise false.</returns>
		template<bool TestX_ = true, bool TestY_ = true, bool TestZ_ = true, bool TestW_ = true>
		[[nodiscard]] inline bool CmpAllEqual(__m128 rhs_) const
		{
			return EmuMath::SIMD::all_equal<TestX_, TestY_, TestZ_, TestW_>(data_, rhs_);
		}
		template<bool TestX_ = true, bool TestY_ = true, bool TestZ_ = true, bool TestW_ = true>
		[[nodiscard]] inline bool CmpAllEqual(const FastVector4f& rhs_) const
		{
			return this->template CmpAllEqual<TestX_, TestY_, TestZ_, TestW_>(rhs_.data_);
		}
		template<bool TestX_ = true, bool TestY_ = true, bool TestZ_ = true, bool TestW_ = true>
		[[nodiscard]] inline bool CmpAllEqual(const float rhs_) const
		{
			return this->template CmpAllEqual<TestX_, TestY_, TestZ_, TestW_>(_mm_broadcast_ss(&rhs_));
		}

		/// <summary>
		/// <para> Compares all elements within this vector to the passed vector data, and returns true if all desired elements are not equal. </para>
		/// <para> By default this will test for all elements. To ignore an element's result, set its respective boolean template argument to false. </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare this vector's data to.</param>
		/// <returns>True if all desired elements' comparisons were true, otherwise false.</returns>
		template<bool TestX_ = true, bool TestY_ = true, bool TestZ_ = true, bool TestW_ = true>
		[[nodiscard]] inline bool CmpAllNotEqual(__m128 rhs_) const
		{
			return EmuMath::SIMD::all_not_equal<TestX_, TestY_, TestZ_, TestW_>(data_, rhs_);
		}
		template<bool TestX_ = true, bool TestY_ = true, bool TestZ_ = true, bool TestW_ = true>
		[[nodiscard]] inline bool CmpAllNotEqual(const FastVector4f& rhs_) const
		{
			return this->template CmpAllNotEqual<TestX_, TestY_, TestZ_, TestW_>(rhs_.data_);
		}
		template<bool TestX_ = true, bool TestY_ = true, bool TestZ_ = true, bool TestW_ = true>
		[[nodiscard]] inline bool CmpAllNotEqual(const float rhs_) const
		{
			return this->template CmpAllNotEqual<TestX_, TestY_, TestZ_, TestW_>(_mm_broadcast_ss(&rhs_));
		}

		/// <summary>
		/// <para>
		///		Compares all elements within this vector to the passed vector data, 
		///		and returns true if all desired elements in this vector are greater than rhs_. 
		/// </para>
		/// <para> By default this will test for all elements. To ignore an element's result, set its respective boolean template argument to false. </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare this vector's data to.</param>
		/// <returns>True if all desired elements' comparisons were true, otherwise false.</returns>
		template<bool TestX_ = true, bool TestY_ = true, bool TestZ_ = true, bool TestW_ = true>
		[[nodiscard]] inline bool CmpAllGreater(__m128 rhs_) const
		{
			return EmuMath::SIMD::all_greater_than<TestX_, TestY_, TestZ_, TestW_>(data_, rhs_);
		}
		template<bool TestX_ = true, bool TestY_ = true, bool TestZ_ = true, bool TestW_ = true>
		[[nodiscard]] inline bool CmpAllGreater(const FastVector4f& rhs_) const
		{
			return this->template CmpAllGreater<TestX_, TestY_, TestZ_, TestW_>(rhs_.data_);
		}
		template<bool TestX_ = true, bool TestY_ = true, bool TestZ_ = true, bool TestW_ = true>
		[[nodiscard]] inline bool CmpAllGreater(const float rhs_) const
		{
			return this->template CmpAllGreater<TestX_, TestY_, TestZ_, TestW_>(_mm_broadcast_ss(&rhs_));
		}

		/// <summary>
		/// <para>
		///		Compares all elements within this vector to the passed vector data, 
		///		and returns true if all desired elements in this vector are less than rhs_. 
		/// </para>
		/// <para> By default this will test for all elements. To ignore an element's result, set its respective boolean template argument to false. </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare this vector's data to.</param>
		/// <returns>True if all desired elements' comparisons were true, otherwise false.</returns>
		template<bool TestX_ = true, bool TestY_ = true, bool TestZ_ = true, bool TestW_ = true>
		[[nodiscard]] inline bool CmpAllLess(__m128 rhs_) const
		{
			return EmuMath::SIMD::all_less_than<TestX_, TestY_, TestZ_, TestW_>(data_, rhs_);
		}
		template<bool TestX_ = true, bool TestY_ = true, bool TestZ_ = true, bool TestW_ = true>
		[[nodiscard]] inline bool CmpAllLess(const FastVector4f& rhs_) const
		{
			return this->template CmpAllLess<TestX_, TestY_, TestZ_, TestW_>(rhs_.data_);
		}
		template<bool TestX_ = true, bool TestY_ = true, bool TestZ_ = true, bool TestW_ = true>
		[[nodiscard]] inline bool CmpAllLess(const float rhs_) const
		{
			return this->template CmpAllLess<TestX_, TestY_, TestZ_, TestW_>(_mm_broadcast_ss(&rhs_));
		}

		/// <summary>
		/// <para>
		///		Compares all elements within this vector to the passed vector data, 
		///		and returns true if all desired elements in this vector are greater than or equal to rhs_. 
		/// </para>
		/// <para> By default this will test for all elements. To ignore an element's result, set its respective boolean template argument to false. </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare this vector's data to.</param>
		/// <returns>True if all desired elements' comparisons were true, otherwise false.</returns>
		template<bool TestX_ = true, bool TestY_ = true, bool TestZ_ = true, bool TestW_ = true>
		[[nodiscard]] inline bool CmpAllGreaterEqual(__m128 rhs_) const
		{
			return EmuMath::SIMD::all_greater_equal<TestX_, TestY_, TestZ_, TestW_>(data_, rhs_);
		}
		template<bool TestX_ = true, bool TestY_ = true, bool TestZ_ = true, bool TestW_ = true>
		[[nodiscard]] inline bool CmpAllGreaterEqual(const FastVector4f& rhs_) const
		{
			return this->template CmpAllGreaterEqual<TestX_, TestY_, TestZ_, TestW_>(rhs_.data_);
		}
		template<bool TestX_ = true, bool TestY_ = true, bool TestZ_ = true, bool TestW_ = true>
		[[nodiscard]] inline bool CmpAllGreaterEqual(const float rhs_) const
		{
			return this->template CmpAllGreaterEqual<TestX_, TestY_, TestZ_, TestW_>(_mm_broadcast_ss(&rhs_));
		}

		/// <summary>
		/// <para>
		///		Compares all elements within this vector to the passed vector data, 
		///		and returns true if all desired elements in this vector are less than or equal to rhs_. 
		/// </para>
		/// <para> By default this will test for all elements. To ignore an element's result, set its respective boolean template argument to false. </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare this vector's data to.</param>
		/// <returns>True if all desired elements' comparisons were true, otherwise false.</returns>
		template<bool TestX_ = true, bool TestY_ = true, bool TestZ_ = true, bool TestW_ = true>
		[[nodiscard]] inline bool CmpAllLessEqual(__m128 rhs_) const
		{
			return EmuMath::SIMD::all_less_equal<TestX_, TestY_, TestZ_, TestW_>(data_, rhs_);
		}
		template<bool TestX_ = true, bool TestY_ = true, bool TestZ_ = true, bool TestW_ = true>
		[[nodiscard]] inline bool CmpAllLessEqual(const FastVector4f& rhs_) const
		{
			return this->template CmpAllLessEqual<TestX_, TestY_, TestZ_, TestW_>(rhs_.data_);
		}
		template<bool TestX_ = true, bool TestY_ = true, bool TestZ_ = true, bool TestW_ = true>
		[[nodiscard]] inline bool CmpAllLessEqual(const float rhs_) const
		{
			return this->template CmpAllLessEqual<TestX_, TestY_, TestZ_, TestW_>(_mm_broadcast_ss(&rhs_));
		}

		/// <summary>
		/// <para> Compares all elements within this vector to the passed vector data, and returns true if any elements are equal. </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare this vector's data to.</param>
		/// <returns>True if any elements' comparisons were true, otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyEqual(__m128 rhs_) const
		{
			return EmuMath::SIMD::any_equal(data_, rhs_);
		}
		[[nodiscard]] inline bool CmpAnyEqual(const FastVector4f& rhs_) const
		{
			return this->CmpAnyEqual(rhs_.data_);
		}
		[[nodiscard]] inline bool CmpAnyEqual(const float rhs_) const
		{
			return this->CmpAnyEqual(_mm_broadcast_ss(&rhs_));
		}

		/// <summary>
		/// <para> Compares all elements within this vector to the passed vector data, and returns true if any elements are not equal. </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare this vector's data to.</param>
		/// <returns>True if any elements' comparisons were true, otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyNotEqual(__m128 rhs_) const
		{
			return EmuMath::SIMD::any_not_equal(data_, rhs_);
		}
		[[nodiscard]] inline bool CmpAnyNotEqual(const FastVector4f& rhs_) const
		{
			return this->CmpAnyNotEqual(rhs_.data_);
		}
		[[nodiscard]] inline bool CmpAnyNotEqual(const float rhs_) const
		{
			return this->CmpAnyNotEqual(_mm_broadcast_ss(&rhs_));
		}

		/// <summary>
		/// <para>
		///		Compares all elements within this vector to the passed vector data, 
		///		and returns true if any elements of this vector are greater than rhs_.
		/// </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare this vector's data to.</param>
		/// <returns>True if any elements' comparisons were true, otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyGreater(__m128 rhs_) const
		{
			return EmuMath::SIMD::any_greater_than(data_, rhs_);
		}
		[[nodiscard]] inline bool CmpAnyGreater(const FastVector4f& rhs_) const
		{
			return this->CmpAnyGreater(rhs_.data_);
		}
		[[nodiscard]] inline bool CmpAnyGreater(const float rhs_) const
		{
			return this->CmpAnyGreater(_mm_broadcast_ss(&rhs_));
		}

		/// <summary>
		/// <para>
		///		Compares all elements within this vector to the passed vector data, 
		///		and returns true if any elements of this vector are less than rhs_.
		/// </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare this vector's data to.</param>
		/// <returns>True if any elements' comparisons were true, otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyLess(__m128 rhs_) const
		{
			return EmuMath::SIMD::any_less_than(data_, rhs_);
		}
		[[nodiscard]] inline bool CmpAnyLess(const FastVector4f& rhs_) const
		{
			return this->CmpAnyLess(rhs_.data_);
		}
		[[nodiscard]] inline bool CmpAnyLess(const float rhs_) const
		{
			return this->CmpAnyLess(_mm_broadcast_ss(&rhs_));
		}

		/// <summary>
		/// <para>
		///		Compares all elements within this vector to the passed vector data, 
		///		and returns true if any elements of this vector are greater than or equal to rhs_.
		/// </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare this vector's data to.</param>
		/// <returns>True if any elements' comparisons were true, otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyGreaterEqual(__m128 rhs_) const
		{
			return EmuMath::SIMD::any_greater_equal(data_, rhs_);
		}
		[[nodiscard]] inline bool CmpAnyGreaterEqual(const FastVector4f& rhs_) const
		{
			return this->CmpAnyGreaterEqual(rhs_.data_);
		}
		[[nodiscard]] inline bool CmpAnyGreaterEqual(const float rhs_) const
		{
			return this->CmpAnyGreaterEqual(_mm_broadcast_ss(&rhs_));
		}

		/// <summary>
		/// <para>
		///		Compares all elements within this vector to the passed vector data, 
		///		and returns true if any elements of this vector are less than or equal to rhs_.
		/// </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare this vector's data to.</param>
		/// <returns>True if any elements' comparisons were true, otherwise false.</returns>
		[[nodiscard]] inline bool CmpAnyLessEqual(__m128 rhs_) const
		{
			return EmuMath::SIMD::any_less_equal(data_, rhs_);
		}
		[[nodiscard]] inline bool CmpAnyLessEqual(const FastVector4f& rhs_) const
		{
			return this->CmpAnyLessEqual(rhs_.data_);
		}
		[[nodiscard]] inline bool CmpAnyLessEqual(const float rhs_) const
		{
			return this->CmpAnyLessEqual(_mm_broadcast_ss(&rhs_));
		}

		/// <summary>
		/// <para> Returns the mask resulting from comparing this vector to the passed rhs_ vector data. </para>
		/// <para> In the returned mask, elements which compared true will have all bits set to 1, otherwise all bits will be set to 0 for said element. </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare this vector to.</param>
		/// <returns>Mask vector resulting from the comparison of the this vector and the provided rhs_ vector data.</returns>
		[[nodiscard]] inline FastVector4f CmpMaskEqual(__m128 rhs_) const
		{
			return FastVector4f(_mm_cmpeq_ps(data_, rhs_));
		}
		[[nodiscard]] inline FastVector4f CmpMaskEqual(const FastVector4f& rhs_) const
		{
			return this->CmpMaskEqual(rhs_.data_);
		}
		[[nodiscard]] inline FastVector4f CmpMaskEqual(const float rhs_) const
		{
			return this->CmpMaskEqual(_mm_broadcast_ss(&rhs_));
		}

		/// <summary>
		/// <para> Returns the mask resulting from comparing this vector to the passed rhs_ vector data. </para>
		/// <para> In the returned mask, elements which compared true will have all bits set to 1, otherwise all bits will be set to 0 for said element. </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare this vector to.</param>
		/// <returns>Mask vector resulting from the comparison of the this vector and the provided rhs_ vector data.</returns>
		[[nodiscard]] inline FastVector4f CmpMaskNotEqual(__m128 rhs_) const
		{
			return FastVector4f(_mm_cmpneq_ps(data_, rhs_));
		}
		[[nodiscard]] inline FastVector4f CmpMaskNotEqual(const FastVector4f& rhs_) const
		{
			return this->CmpMaskNotEqual(rhs_.data_);
		}
		[[nodiscard]] inline FastVector4f CmpMaskNotEqual(const float rhs_) const
		{
			return this->CmpMaskNotEqual(_mm_broadcast_ss(&rhs_));
		}

		/// <summary>
		/// <para> Returns the mask resulting from comparing this vector to the passed rhs_ vector data. </para>
		/// <para> In the returned mask, elements which compared true will have all bits set to 1, otherwise all bits will be set to 0 for said element. </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare this vector to.</param>
		/// <returns>Mask vector resulting from the comparison of the this vector and the provided rhs_ vector data.</returns>
		[[nodiscard]] inline FastVector4f CmpMaskGreater(__m128 rhs_) const
		{
			return FastVector4f(_mm_cmpgt_ps(data_, rhs_));
		}
		[[nodiscard]] inline FastVector4f CmpMaskGreater(const FastVector4f& rhs_) const
		{
			return this->CmpMaskGreater(rhs_.data_);
		}
		[[nodiscard]] inline FastVector4f CmpMaskGreater(const float rhs_) const
		{
			return this->CmpMaskGreater(_mm_broadcast_ss(&rhs_));
		}

		/// <summary>
		/// <para> Returns the mask resulting from comparing this vector to the passed rhs_ vector data. </para>
		/// <para> In the returned mask, elements which compared true will have all bits set to 1, otherwise all bits will be set to 0 for said element. </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare this vector to.</param>
		/// <returns>Mask vector resulting from the comparison of the this vector and the provided rhs_ vector data.</returns>
		[[nodiscard]] inline FastVector4f CmpMaskLess(__m128 rhs_) const
		{
			return FastVector4f(_mm_cmplt_ps(data_, rhs_));
		}
		[[nodiscard]] inline FastVector4f CmpMaskLess(const FastVector4f& rhs_) const
		{
			return this->CmpMaskLess(rhs_.data_);
		}
		[[nodiscard]] inline FastVector4f CmpMaskLess(const float rhs_) const
		{
			return this->CmpMaskLess(_mm_broadcast_ss(&rhs_));
		}

		/// <summary>
		/// <para> Returns the mask resulting from comparing this vector to the passed rhs_ vector data. </para>
		/// <para> In the returned mask, elements which compared true will have all bits set to 1, otherwise all bits will be set to 0 for said element. </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare this vector to.</param>
		/// <returns>Mask vector resulting from the comparison of the this vector and the provided rhs_ vector data.</returns>
		[[nodiscard]] inline FastVector4f CmpMaskGreaterEqual(__m128 rhs_) const
		{
			return FastVector4f(_mm_cmpge_ps(data_, rhs_));
		}
		[[nodiscard]] inline FastVector4f CmpMaskGreaterEqual(const FastVector4f& rhs_) const
		{
			return this->CmpMaskGreaterEqual(rhs_.data_);
		}
		[[nodiscard]] inline FastVector4f CmpMaskGreaterEqual(const float rhs_) const
		{
			return this->CmpMaskGreaterEqual(_mm_broadcast_ss(&rhs_));
		}

		/// <summary>
		/// <para> Returns the mask resulting from comparing this vector to the passed rhs_ vector data. </para>
		/// <para> In the returned mask, elements which compared true will have all bits set to 1, otherwise all bits will be set to 0 for said element. </para>
		/// </summary>
		/// <param name="rhs_">Vector data to compare this vector to.</param>
		/// <returns>Mask vector resulting from the comparison of the this vector and the provided rhs_ vector data.</returns>
		[[nodiscard]] inline FastVector4f CmpMaskLessEqual(__m128 rhs_) const
		{
			return FastVector4f(_mm_cmple_ps(data_, rhs_));
		}
		[[nodiscard]] inline FastVector4f CmpMaskLessEqual(const FastVector4f& rhs_) const
		{
			return this->CmpMaskLessEqual(rhs_.data_);
		}
		[[nodiscard]] inline FastVector4f CmpMaskLessEqual(const float rhs_) const
		{
			return this->CmpMaskLessEqual(_mm_broadcast_ss(&rhs_));
		}

		/// <summary> Returns a vector of booleans indicating if respective elements in this vector are equal to the passed rhs_ vector data. </summary>
		/// <param name="rhs_">Vector data to compare this vector's data to.</param>
		/// <returns>Vector of 4 booleans which indicate the results of comparisons of the respective indices.</returns>
		[[nodiscard]] inline EmuMath::Vector<4, bool> CmpPerElementEqual(__m128 rhs_) const
		{
			return this->CmpMaskEqual(rhs_).Store<0, 4, bool>();
		}
		[[nodiscard]] inline EmuMath::Vector<4, bool> CmpPerElementEqual(const FastVector4f& rhs_) const
		{
			return this->CmpPerElementEqual(rhs_.data_);
		}
		[[nodiscard]] inline EmuMath::Vector<4, bool> CmpPerElementEqual(const float rhs_) const
		{
			return this->CmpPerElementEqual(_mm_broadcast_ss(&rhs_));
		}

		/// <summary> Returns a vector of booleans indicating if respective elements in this vector are not equal to the passed rhs_ vector data. </summary>
		/// <param name="rhs_">Vector data to compare this vector's data to.</param>
		/// <returns>Vector of 4 booleans which indicate the results of comparisons of the respective indices.</returns>
		[[nodiscard]] inline EmuMath::Vector<4, bool> CmpPerElementNotEqual(__m128 rhs_) const
		{
			return this->CmpMaskNotEqual(rhs_).Store<0, 4, bool>();
		}
		[[nodiscard]] inline EmuMath::Vector<4, bool> CmpPerElementNotEqual(const FastVector4f& rhs_) const
		{
			return this->CmpPerElementNotEqual(rhs_.data_);
		}
		[[nodiscard]] inline EmuMath::Vector<4, bool> CmpPerElementNotEqual(const float rhs_) const
		{
			return this->CmpPerElementNotEqual(_mm_broadcast_ss(&rhs_));
		}

		/// <summary> Returns a vector of booleans indicating if respective elements in this vector are greater than the passed rhs_ vector data. </summary>
		/// <param name="rhs_">Vector data to compare this vector's data to.</param>
		/// <returns>Vector of 4 booleans which indicate the results of comparisons of the respective indices.</returns>
		[[nodiscard]] inline EmuMath::Vector<4, bool> CmpPerElementGreater(__m128 rhs_) const
		{
			return this->CmpMaskGreater(rhs_).Store<0, 4, bool>();
		}
		[[nodiscard]] inline EmuMath::Vector<4, bool> CmpPerElementGreater(const FastVector4f& rhs_) const
		{
			return this->CmpPerElementGreater(rhs_.data_);
		}
		[[nodiscard]] inline EmuMath::Vector<4, bool> CmpPerElementGreater(const float rhs_) const
		{
			return this->CmpPerElementGreater(_mm_broadcast_ss(&rhs_));
		}

		/// <summary> Returns a vector of booleans indicating if respective elements in this vector are less than the passed rhs_ vector data. </summary>
		/// <param name="rhs_">Vector data to compare this vector's data to.</param>
		/// <returns>Vector of 4 booleans which indicate the results of comparisons of the respective indices.</returns>
		[[nodiscard]] inline EmuMath::Vector<4, bool> CmpPerElementLess(__m128 rhs_) const
		{
			return this->CmpMaskLess(rhs_).Store<0, 4, bool>();
		}
		[[nodiscard]] inline EmuMath::Vector<4, bool> CmpPerElementLess(const FastVector4f& rhs_) const
		{
			return this->CmpPerElementLess(rhs_.data_);
		}
		[[nodiscard]] inline EmuMath::Vector<4, bool> CmpPerElementLess(const float rhs_) const
		{
			return this->CmpPerElementLess(_mm_broadcast_ss(&rhs_));
		}

		/// <summary> Returns a vector of booleans indicating if respective elements in this vector are greater than or equal to the passed rhs_ vector data. </summary>
		/// <param name="rhs_">Vector data to compare this vector's data to.</param>
		/// <returns>Vector of 4 booleans which indicate the results of comparisons of the respective indices.</returns>
		[[nodiscard]] inline EmuMath::Vector<4, bool> CmpPerElementGreaterEqual(__m128 rhs_) const
		{
			return this->CmpMaskGreaterEqual(rhs_).Store<0, 4, bool>();
		}
		[[nodiscard]] inline EmuMath::Vector<4, bool> CmpPerElementGreaterEqual(const FastVector4f& rhs_) const
		{
			return this->CmpPerElementGreaterEqual(rhs_.data_);
		}
		[[nodiscard]] inline EmuMath::Vector<4, bool> CmpPerElementGreaterEqual(const float rhs_) const
		{
			return this->CmpPerElementGreaterEqual(_mm_broadcast_ss(&rhs_));
		}

		/// <summary> Returns a vector of booleans indicating if respective elements in this vector are less than or equal to the passed rhs_ vector data. </summary>
		/// <param name="rhs_">Vector data to compare this vector's data to.</param>
		/// <returns>Vector of 4 booleans which indicate the results of comparisons of the respective indices.</returns>
		[[nodiscard]] inline EmuMath::Vector<4, bool> CmpPerElementLessEqual(__m128 rhs_) const
		{
			return this->CmpMaskLessEqual(rhs_).Store<0, 4, bool>();
		}
		[[nodiscard]] inline EmuMath::Vector<4, bool> CmpPerElementLessEqual(const FastVector4f& rhs_) const
		{
			return this->CmpPerElementLessEqual(rhs_.data_);
		}
		[[nodiscard]] inline EmuMath::Vector<4, bool> CmpPerElementLessEqual(const float rhs_) const
		{
			return this->CmpPerElementLessEqual(_mm_broadcast_ss(&rhs_));
		}
#pragma endregion

#pragma region BITWISE
		/// <summary> Outputs the resulting vector from a bitwise AND with this vector's data and the passed vector data. </summary>
		/// <param name="rhs_">Vector data to perform the bitwise AND on this vector's data.</param>
		/// <returns>Vector resulting from a bitwise AND performed between this vector's data and the passed vector data.</returns>
		[[nodiscard]] inline FastVector4f And(__m128 rhs_) const
		{
			return FastVector4f(_mm_and_ps(data_, rhs_));
		}
		[[nodiscard]] inline FastVector4f And(const FastVector4f& rhs_) const
		{
			return this->And(rhs_.data_);
		}
		[[nodiscard]] inline FastVector4f And(const float rhs_) const
		{
			return this->And(_mm_broadcast_ss(&rhs_));
		}

		/// <summary> Outputs the resulting vector from a bitwise OR with this vector's data and the passed vector data. </summary>
		/// <param name="rhs_">Vector data to perform the bitwise OR on this vector's data.</param>
		/// <returns>Vector resulting from a bitwise OR performed between this vector's data and the passed vector data.</returns>
		[[nodiscard]] inline FastVector4f Or(__m128 rhs_) const
		{
			return FastVector4f(_mm_or_ps(data_, rhs_));
		}
		[[nodiscard]] inline FastVector4f Or(const FastVector4f& rhs_) const
		{
			return this->Or(rhs_.data_);
		}
		[[nodiscard]] inline FastVector4f Or(const float rhs_) const
		{
			return this->Or(_mm_broadcast_ss(&rhs_));
		}

		/// <summary> Outputs the resulting vector from a bitwise XOR with this vector's data and the passed vector data. </summary>
		/// <param name="rhs_">Vector data to perform the bitwise XOR on this vector's data.</param>
		/// <returns>Vector resulting from a bitwise XOR performed between this vector's data and the passed vector data.</returns>
		[[nodiscard]] inline FastVector4f Xor(__m128 rhs_) const
		{
			return FastVector4f(_mm_xor_ps(data_, rhs_));
		}
		[[nodiscard]] inline FastVector4f Xor(const FastVector4f& rhs_) const
		{
			return this->Xor(rhs_.data_);
		}
		[[nodiscard]] inline FastVector4f Xor(const float rhs_) const
		{
			return this->Xor(_mm_broadcast_ss(&rhs_));
		}

		/// <summary> Outputs the resulting vector from a bitwise logical shift left the provided number of times for all elements. </summary>
		/// <param name="rhs_">Scalar or integral vector data indicating the number of times each element should be shifted.</param>
		/// <returns>Vector resulting from a bitwise shift performed on this vector's data.</returns>
		[[nodiscard]] inline FastVector4f ShiftLeft(const std::size_t numShifts_) const
		{
			__m128i shifted_ = _mm_slli_epi32(*reinterpret_cast<const __m128i*>(&data_), static_cast<int>(numShifts_));
			return FastVector4f(*reinterpret_cast<const __m128*>(&shifted_));
		}
		[[nodiscard]] inline FastVector4f ShiftLeft(__m128i numShifts_) const
		{
			__m128i shifted_ = _mm_sll_epi32(*reinterpret_cast<const __m128i*>(&data_), numShifts_);
			return FastVector4f(*reinterpret_cast<const __m128*>(&shifted_));
		}

		/// <summary> Outputs the resulting vector from a bitwise logical shift right the provided number of times for all elements. </summary>
		/// <param name="rhs_">Scalar or integral vector data indicating the number of times each element should be shifted.</param>
		/// <returns>Vector resulting from a bitwise shift performed on this vector's data.</returns>
		[[nodiscard]] inline FastVector4f ShiftRight(const std::size_t numShifts_) const
		{
			__m128i shifted_ = _mm_srli_epi32(*reinterpret_cast<const __m128i*>(&data_), static_cast<int>(numShifts_));
			return FastVector4f(*reinterpret_cast<const __m128*>(&shifted_));
		}
		[[nodiscard]] inline FastVector4f ShiftRight(__m128i numShifts_) const
		{
			__m128i shifted_ = _mm_srl_epi32(*reinterpret_cast<const __m128i*>(&data_), numShifts_);
			return FastVector4f(*reinterpret_cast<const __m128*>(&shifted_));
		}

		/// <summary> Outputs the resulting vector from a bitwise arithmetic shift right the provided number of times for all elements. </summary>
		/// <param name="rhs_">Scalar or integral vector data indicating the number of times each element should be shifted.</param>
		/// <returns>Vector resulting from a bitwise shift performed on this vector's data.</returns>
		[[nodiscard]] inline FastVector4f ShiftRightArithmetic(const std::size_t numShifts_) const
		{
			__m128i shifted_ = _mm_srai_epi32(*reinterpret_cast<const __m128i*>(&data_), static_cast<int>(numShifts_));
			return FastVector4f(*reinterpret_cast<const __m128*>(&shifted_));
		}
		[[nodiscard]] inline FastVector4f ShiftRightArithmetic(__m128i numShifts_) const
		{
			__m128i shifted_ = _mm_sra_epi32(*reinterpret_cast<const __m128i*>(&data_), numShifts_);
			return FastVector4f(*reinterpret_cast<const __m128*>(&shifted_));
		}

		/// <summary> Outputs the resulting vector from performing a bitwise NOT on this vector. </summary>
		/// <returns>Inverted form of this vector resulting from a bitwise NOT.</returns>
		[[nodiscard]] inline FastVector4f Not() const
		{
			return _mm_andnot_ps(data_, EmuMath::SIMD::index_mask_m128<true, true, true, true>());
		}
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
		[[nodiscard]] inline EmuMath::Vector<OutSize_, out_contained_type> Store() const
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
		[[nodiscard]] inline EmuMath::Vector<OutSize_, out_contained_type> As() const
		{
			return this->template Store<0, OutSize_, out_contained_type>();
		}
		template<std::size_t OutSize_, typename out_contained_type>
		explicit inline operator EmuMath::Vector<OutSize_, out_contained_type>() const
		{
			return this->template As<OutSize_, out_contained_type>();
		}
		explicit inline operator bool() const
		{
			return EmuMath::SIMD::any_not_equal(data_, _mm_setzero_ps());
		}
		inline bool operator!() const
		{
			return !static_cast<bool>(*this);
		}
#pragma endregion

		/// <summary> SIMD register represeneting this vector's data. This should not be interacted with directly unless you know what you are doing. </summary>
		__m128 data_;
	};
}

#pragma region EMU_CORE_FUNCTOR_SPECIALISATIONS
namespace EmuCore
{
	template<typename B_, typename T_>
	struct do_lerp<EmuMath::FastVector4f, B_, T_>
	{
		constexpr do_lerp()
		{
		}
		inline EmuMath::FastVector4f operator()(const EmuMath::FastVector4f& a_, B_&& b_, T_&& t_) const
		{
			return a_.Lerp(std::forward<B_>(b_), std::forward<T_>(t_));
		}
	};

	template<>
	struct do_sqrt<EmuMath::FastVector4f>
	{
		constexpr do_sqrt()
		{
		}
		inline EmuMath::FastVector4f operator()(const EmuMath::FastVector4f& val_) const
		{
			return val_.Sqrt();
		}
	};

	template<>
	struct do_floor<EmuMath::FastVector4f>
	{
		constexpr do_floor()
		{
		}
		inline EmuMath::FastVector4f operator()(const EmuMath::FastVector4f& val_) const
		{
			return val_.Floor();
		}
	};

	template<>
	struct do_ceil<EmuMath::FastVector4f>
	{
		constexpr do_ceil()
		{
		}
		inline EmuMath::FastVector4f operator()(const EmuMath::FastVector4f& val_) const
		{
			return val_.Ceil();
		}
	};

	template<>
	struct do_trunc<EmuMath::FastVector4f>
	{
		constexpr do_trunc()
		{
		}
		inline EmuMath::FastVector4f operator()(const EmuMath::FastVector4f& val_) const
		{
			return val_.Trunc();
		}
	};

	template<typename Rhs_>
	struct do_add<EmuMath::FastVector4f, Rhs_>
	{
		constexpr do_add()
		{
		}
		inline EmuMath::FastVector4f operator()(const EmuMath::FastVector4f& lhs_, Rhs_&& rhs_) const
		{
			return lhs_.Add(std::forward<Rhs_>(rhs_));
		}
	};

	template<typename Rhs_>
	struct do_subtract<EmuMath::FastVector4f, Rhs_>
	{
		constexpr do_subtract()
		{
		}
		inline EmuMath::FastVector4f operator()(const EmuMath::FastVector4f& lhs_, Rhs_&& rhs_) const
		{
			return lhs_.Subtract(std::forward<Rhs_>(rhs_));
		}
	};

	template<typename Rhs_>
	struct do_multiply<EmuMath::FastVector4f, Rhs_>
	{
		constexpr do_multiply()
		{
		}
		inline EmuMath::FastVector4f operator()(const EmuMath::FastVector4f& lhs_, Rhs_&& rhs_) const
		{
			return lhs_.Multiply(std::forward<Rhs_>(rhs_));
		}
	};

	template<typename Rhs_>
	struct do_divide<EmuMath::FastVector4f, Rhs_>
	{
		constexpr do_divide()
		{
		}
		inline EmuMath::FastVector4f operator()(const EmuMath::FastVector4f& lhs_, Rhs_&& rhs_) const
		{
			return lhs_.Divide(std::forward<Rhs_>(rhs_));
		}
	};

	template<typename Rhs_>
	struct do_mod<EmuMath::FastVector4f, Rhs_>
	{
		constexpr do_mod()
		{
		}
		inline EmuMath::FastVector4f operator()(const EmuMath::FastVector4f& lhs_, Rhs_&& rhs_) const
		{
			return lhs_.Mod(std::forward<Rhs_>(rhs_));
		}
	};

	template<>
	struct do_negate<EmuMath::FastVector4f>
	{
		constexpr do_negate()
		{
		}
		inline EmuMath::FastVector4f operator()(const EmuMath::FastVector4f& val_) const
		{
			return val_.Negate();
		}
	};

	template<>
	struct do_rads_to_degs<EmuMath::FastVector4f>
	{
		constexpr do_rads_to_degs()
		{
		}
		inline EmuMath::FastVector4f operator()(const EmuMath::FastVector4f& val_) const
		{
			return val_.Multiply(_mm_set_ps1(EmuCore::Pi::HUNDRED80_DIV_PI<float>));
		}
	};

	template<>
	struct do_degs_to_rads<EmuMath::FastVector4f>
	{
		constexpr do_degs_to_rads()
		{
		}
		inline EmuMath::FastVector4f operator()(const EmuMath::FastVector4f& val_) const
		{
			return val_.Multiply(_mm_set_ps1(EmuCore::Pi::PI_DIV_180<float>));
		}
	};

	template<typename Rhs_>
	struct do_bitwise_and<EmuMath::FastVector4f, Rhs_>
	{
		constexpr do_bitwise_and()
		{
		}
		inline EmuMath::FastVector4f operator()(const EmuMath::FastVector4f& lhs_, Rhs_&& rhs_) const
		{
			return lhs_.And(std::forward<Rhs_>(rhs_));
		}
	};

	template<typename Rhs_>
	struct do_bitwise_or<EmuMath::FastVector4f, Rhs_>
	{
		constexpr do_bitwise_or()
		{
		}
		inline EmuMath::FastVector4f operator()(const EmuMath::FastVector4f& lhs_, Rhs_&& rhs_) const
		{
			return lhs_.Or(std::forward<Rhs_>(rhs_));
		}
	};

	template<typename Rhs_>
	struct do_bitwise_xor<EmuMath::FastVector4f, Rhs_>
	{
		constexpr do_bitwise_xor()
		{
		}
		inline EmuMath::FastVector4f operator()(const EmuMath::FastVector4f& lhs_, Rhs_&& rhs_) const
		{
			return lhs_.Xor(std::forward<Rhs_>(rhs_));
		}
	};

	template<>
	struct do_bitwise_not<EmuMath::FastVector4f>
	{
		constexpr do_bitwise_not()
		{
		}
		inline EmuMath::FastVector4f operator()(const EmuMath::FastVector4f& val_) const
		{
			return val_.Not();
		}
	};

	template<typename Shifts_>
	struct do_left_shift<EmuMath::FastVector4f, Shifts_>
	{
		constexpr do_left_shift()
		{
		}
		inline EmuMath::FastVector4f operator()(const EmuMath::FastVector4f& val_, Shifts_&& num_shifts_) const
		{
			return val_.ShiftLeft(std::forward<Shifts_>(num_shifts_));
		}
	};

	template<typename Shifts_>
	struct do_right_shift<EmuMath::FastVector4f, Shifts_>
	{
		constexpr do_right_shift()
		{
		}
		inline EmuMath::FastVector4f operator()(const EmuMath::FastVector4f& val_, Shifts_&& num_shifts_) const
		{
			return val_.ShiftRight(std::forward<Shifts_>(num_shifts_));
		}
	};

	template<typename Rhs_>
	struct do_cmp_equal_to<EmuMath::FastVector4f, Rhs_>
	{
		constexpr do_cmp_equal_to()
		{
		}
		inline bool operator()(const EmuMath::FastVector4f& lhs_, Rhs_&& rhs_) const
		{
			return lhs_.CmpEqualTo(std::forward<Rhs_>(rhs_));
		}
	};

	template<typename Rhs_>
	struct do_cmp_not_equal_to<EmuMath::FastVector4f, Rhs_>
	{
		constexpr do_cmp_not_equal_to()
		{
		}
		inline bool operator()(const EmuMath::FastVector4f& lhs_, Rhs_&& rhs_) const
		{
			return lhs_.CmpNotEqualTo(std::forward<Rhs_>(rhs_));
		}
	};

	template<typename Rhs_>
	struct do_cmp_greater<EmuMath::FastVector4f, Rhs_>
	{
		constexpr do_cmp_greater()
		{
		}
		inline bool operator()(const EmuMath::FastVector4f& lhs_, Rhs_&& rhs_) const
		{
			return lhs_.CmpGreater(std::forward<Rhs_>(rhs_));
		}
	};

	template<typename Rhs_>
	struct do_cmp_less<EmuMath::FastVector4f, Rhs_>
	{
		constexpr do_cmp_less()
		{
		}
		inline bool operator()(const EmuMath::FastVector4f& lhs_, Rhs_&& rhs_) const
		{
			return lhs_.CmpLess(std::forward<Rhs_>(rhs_));
		}
	};

	template<typename Rhs_>
	struct do_cmp_greater_equal<EmuMath::FastVector4f, Rhs_>
	{
		constexpr do_cmp_greater_equal()
		{
		}
		inline bool operator()(const EmuMath::FastVector4f& lhs_, Rhs_&& rhs_) const
		{
			return lhs_.CmpGreaterEqual(std::forward<Rhs_>(rhs_));
		}
	};

	template<typename Rhs_>
	struct do_cmp_less_equal<EmuMath::FastVector4f, Rhs_>
	{
		constexpr do_cmp_less_equal()
		{
		}
		inline bool operator()(const EmuMath::FastVector4f& lhs_, Rhs_&& rhs_) const
		{
			return lhs_.CmpLessEqual(std::forward<Rhs_>(rhs_));
		}
	};

	template<typename B_>
	struct do_min<EmuMath::FastVector4f, B_>
	{
		constexpr do_min()
		{
		}
		inline EmuMath::FastVector4f operator()(const EmuMath::FastVector4f& a_, B_&& b_) const
		{
			return a_.MinVector(std::forward<B_>(b_));
		}
	};

	template<typename B_>
	struct do_max<EmuMath::FastVector4f, B_>
	{
		constexpr do_max()
		{
		}
		inline EmuMath::FastVector4f operator()(const EmuMath::FastVector4f& a_, B_&& b_) const
		{
			return a_.MaxVector(std::forward<B_>(b_));
		}
	};
}
#pragma endregion

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
