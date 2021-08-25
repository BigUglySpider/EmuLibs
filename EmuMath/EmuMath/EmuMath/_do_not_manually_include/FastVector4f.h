#ifndef EMU_MATH_FAST_VECTOR_4_FLOAT_H_INC_
#define EMU_MATH_FAST_VECTOR_4_FLOAT_H_INC_

#include "../SIMDHelpers.h"
#include "../Vector.h"
#include <immintrin.h>
#include <ostream>

namespace EmuMath
{
	struct FastVector4f
	{
		using value_type = float;

		static constexpr std::size_t size = 4;
		static constexpr std::size_t contained_item_byte_size = sizeof(value_type);
		static constexpr std::size_t total_contained_bytes = contained_item_byte_size * size;

		FastVector4f() : data_()
		{
		}
		FastVector4f(__m128 dataToCopy_) : data_(dataToCopy_)
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

		template<std::size_t Index_, typename ToCopy_>
		inline void Set(ToCopy_&& toCopyAtIndex_)
		{
			if constexpr (Index_ < size)
			{
				__m128 mask_ = EmuMath::SIMD::index_mask_m128<Index_>();
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
		template<typename X_, typename Y_, typename Z_, typename W_>
		inline void Set(X_&& x_, Y_&& y_, Z_&& z_, W_&& w_)
		{
			data_ = _mm_set_ps
			(
				static_cast<value_type>(std::forward<W_>(w_)),
				static_cast<value_type>(std::forward<Z_>(z_)),
				static_cast<value_type>(std::forward<Y_>(y_)),
				static_cast<value_type>(std::forward<X_>(x_))
			);
		}

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

		inline void LoadContiguous(const float* pData_)
		{
			data_ = _mm_load_ps(pData_);
		}
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

		/// <summary> SIMD register represeneting this vector's data. </summary>
		__m128 data_;
	};
}

inline std::ostream& operator<<(std::ostream& stream_, const EmuMath::FastVector4f& v4f_)
{
	stream_ << "{ " << v4f_.at<0>() << ", " << v4f_.at<1>() << ", " << v4f_.at<2>() << ", " << v4f_.at<3>() << " }";
	return stream_;
}

#endif
