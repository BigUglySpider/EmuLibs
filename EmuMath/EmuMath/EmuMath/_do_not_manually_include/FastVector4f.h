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
		using value_type = float;
		using this_type = FastVector4f;
		using data_type = __m128;

		/// <summary> The number of items contained within this vector. </summary>
		static constexpr std::size_t size = 4;
		/// <summary> The size of an individual item within this vector in bytes. </summary>
		static constexpr std::size_t contained_item_byte_size = sizeof(value_type);
		/// <summary> The total size of contained items within this vector in bytes. </summary>
		static constexpr std::size_t total_contained_bytes = contained_item_byte_size * size;
		/// <summary> The number of bits consumed by a single element within this vector in terms of 8-bit bytes. This is not guaranteed to match up to CHAR_BIT. </summary>
		static constexpr std::size_t register_element_8bit_num_bits = contained_item_byte_size * 8;

		FastVector4f() : data_()
		{
		}
		FastVector4f(data_type dataToCopy_) : data_(dataToCopy_)
		{
		}
		FastVector4f(const FastVector4f& toCopy_) : data_(toCopy_.data_)
		{
		}
		template<std::size_t ToCopySize_, typename to_copy_contained_type>
		FastVector4f(const EmuMath::Vector<ToCopySize_, to_copy_contained_type>& toCopy_) : 
			FastVector4f
			(
				EmuMath::Helpers::VectorGetTheoretical<0, value_type>(toCopy_),
				EmuMath::Helpers::VectorGetTheoretical<1, value_type>(toCopy_),
				EmuMath::Helpers::VectorGetTheoretical<2, value_type>(toCopy_),
				EmuMath::Helpers::VectorGetTheoretical<3, value_type>(toCopy_)
			)
		{
		}
		template<typename X_, typename Y_, typename Z_, typename W_>
		FastVector4f(X_&& x_, Y_&& y_, Z_&& z_, W_&& w_) : 
			data_
			(
				_mm_set_ps
				(
					static_cast<value_type>(std::forward<W_>(w_)),
					static_cast<value_type>(std::forward<Z_>(z_)),
					static_cast<value_type>(std::forward<Y_>(y_)),
					static_cast<value_type>(std::forward<X_>(x_))
				)
			)
		{
		}

#pragma region RANDOM_ACCESS
		/// <summary>
		/// <para> Returns a copy of the element at the provided index, where 0 is X, 1 Y, 2 Z, and 3 W. </para>
		/// <para> This may not be used to reference an index value directly. For such behaviours, one should use a normal EmuMath::Vector type. </para>
		/// </summary>
		/// <returns>Copy of the value at the provided index.</returns>
		template<std::size_t Index_>
		inline value_type at() const
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
		/// <para> Sets the data at the provided index to copy the passed data, which must be convertible to this vector's value_type. </para>
		/// <para> This is increasingly inefficient with more sets, and is seldom recommended with a FastVector. </para>
		/// </summary>
		/// <typeparam name="ToCopy_">Type to be copying.</typeparam>
		/// <param name="toCopyAtIndex_">Value to copy to the provided index.</param>
		template<std::size_t Index_, typename ToCopy_>
		inline void Set(ToCopy_&& toCopyAtIndex_)
		{
			if constexpr (std::is_convertible_v<ToCopy_, value_type>)
			{
				if constexpr (Index_ < size)
				{
					data_type mask_ = EmuMath::SIMD::index_mask<data_type, Index_, register_element_8bit_num_bits>();
					data_ = _mm_or_ps
					(
						_mm_andnot_ps(mask_, data_),
						_mm_and_ps
						(
							mask_,
							_mm_set_ps1(static_cast<value_type>(std::forward<ToCopy_>(toCopyAtIndex_)))
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
				static_assert(false, "Attempted to set an index of an EmuMath::FastVector4f via a type that cannot be converted to its contained value_type.");
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
					EmuMath::Helpers::VectorGetTheoretical<0, value_type>(toCopy_),
					EmuMath::Helpers::VectorGetTheoretical<1, value_type>(toCopy_),
					EmuMath::Helpers::VectorGetTheoretical<2, value_type>(toCopy_),
					EmuMath::Helpers::VectorGetTheoretical<3, value_type>(toCopy_)
				);
			}
			else
			{
				if constexpr (std::is_same_v<ToCopy_, this_type>)
				{
					// Simple register copy
					data_ = std::forward<ToCopy_>(toCopy_).data_;
				}
				else if constexpr (std::is_convertible_v<ToCopy_, value_type>)
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
		/// <para> All provided values must be convertible to this vector's value_type. </para>
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
			if constexpr (EmuCore::TMPHelpers::are_all_comparisons_true<std::is_convertible_v, value_type, X_, Y_, Z_, W_>::value)
			{
				data_ = _mm_set_ps
				(
					static_cast<value_type>(std::forward<W_>(w_)),
					static_cast<value_type>(std::forward<Z_>(z_)),
					static_cast<value_type>(std::forward<Y_>(y_)),
					static_cast<value_type>(std::forward<X_>(x_))
				);
			}
			else
			{
				static_assert(false, "Attempted to set the data of an EmuMath::FastVector4f with at least one value that cannot be converted to its contained value_type.");
			}
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
				EmuMath::Helpers::VectorGetTheoretical<X_, value_type>(toLoad_),
				EmuMath::Helpers::VectorGetTheoretical<Y_, value_type>(toLoad_),
				EmuMath::Helpers::VectorGetTheoretical<Z_, value_type>(toLoad_),
				EmuMath::Helpers::VectorGetTheoretical<W_, value_type>(toLoad_)
			);
		}

		/// <summary>
		/// <para> Loads the passed pointed-to data contiguously into this vector. </para>
		/// <para> This function assumes the passed pointer is safe to load into the width of this vector. </para>
		/// </summary>
		/// <param name="pData_">Pointer to contiguous data to load into this vector.</param>
		inline void LoadContiguous(const value_type* pData_)
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
						this->LoadContiguous(reinterpret_cast<const value_type*>(toLoad_.data() + IndexOffset_));
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
					EmuMath::Helpers::VectorGetTheoretical<IndexOffset_ + 0, value_type>(toLoad_),
					EmuMath::Helpers::VectorGetTheoretical<IndexOffset_ + 1, value_type>(toLoad_),
					EmuMath::Helpers::VectorGetTheoretical<IndexOffset_ + 2, value_type>(toLoad_),
					EmuMath::Helpers::VectorGetTheoretical<IndexOffset_ + 3, value_type>(toLoad_)
				);
			}
		}
#pragma endregion

#pragma region CONVERSIONS
		/// <summary>
		/// <para> Stores this vector into the passed EmuMath vector reference. </para>
		/// <para> This function is optimised to store into a 128-bit wide range of this vector's value_type. If possible, it will store its data by these means. </para>
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
					out_.Set<OutOffset_ + 0, const value_type>(at<0>());
				}
				else if constexpr (num_to_copy == 2)
				{
					out_.Set<OutOffset_ + 0, const value_type>(at<0>());
					out_.Set<OutOffset_ + 1, const value_type>(at<1>());
				}
				else if constexpr (num_to_copy == 3)
				{
					out_.Set<OutOffset_ + 0, const value_type>(at<0>());
					out_.Set<OutOffset_ + 1, const value_type>(at<1>());
					out_.Set<OutOffset_ + 2, const value_type>(at<2>());
				}
				else
				{
					if constexpr (std::is_same_v<value_type, out_contained_type>)
					{
						_mm_store_ps(out_.data() + OutOffset_, data_);
					}
					else
					{
						out_.Set<OutOffset_ + 0, const value_type>(at<0>());
						out_.Set<OutOffset_ + 1, const value_type>(at<1>());
						out_.Set<OutOffset_ + 2, const value_type>(at<2>());
						out_.Set<OutOffset_ + 3, const value_type>(at<3>());
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
		/// <para> The output EmuMath vector defaults to the EmuMath vector that mirrors this vector in terms of size and value_type. </para>
		/// <para> This function is optimised to store into a 128-bit wide range of this vector's value_type. If possible, it will store its data by these means. </para>
		/// <para> May provide an additional index offset to start contiguously outputting this vector's data from. </para>
		/// </summary>
		template<std::size_t OutOffset_ = 0, std::size_t OutSize_ = 4, typename out_contained_type = value_type>
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
					if constexpr (std::is_same_v<value_type, std::remove_const_t<out_contained_type>>)
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
					out_.Set<0, const value_type>(at<0>());
					out_.Set<1, const value_type>(at<1>());
					out_.Set<2, const value_type>(at<2>());
					out_.Set<3, const value_type>(at<3>());
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
		data_type data_;
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
