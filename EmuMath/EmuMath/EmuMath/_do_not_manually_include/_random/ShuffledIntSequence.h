#ifndef EMU_MATH_SEQUENTIAL_PERMUTATIONS_H_INC_
#define EMU_MATH_SEQUENTIAL_PERMUTATIONS_H_INC_ 1

#include "../../../EmuCore/ArithmeticHelpers/BitHelpers.h"
#include "RngWrapper.h"
#include <ostream>
#include <vector>

namespace EmuMath
{
	/// <summary> 
	/// <para> Class to produce a shuffled sequence of integers. Defaults to storing signed 32-bit integers. </para>
	/// <para> Created sequences will contain values within the range of 0 (inclusive) : size (exclusive). </para>
	/// </summary>
	template<typename T_>
	class ShuffledIntSequence
	{
	public:
		using value_type = T_;
		using seed_32_type = EmuMath::RngWrapper<false>::unsigned_int_type;
		using seed_64_type = EmuMath::RngWrapper<true>::unsigned_int_type;
		static seed_32_type default_seed_32() { return EmuMath::RngWrapper<false>::default_seed(); };
		static seed_64_type default_seed_64() { return EmuMath::RngWrapper<true>::default_seed(); };

	private:
		using item_storage = std::vector<value_type>;
		explicit ShuffledIntSequence(std::size_t size_) : items(size_), max_contained_value(static_cast<value_type>(size_) - 1)
		{
			_fill_items_pre_shuffle();
		}
		explicit ShuffledIntSequence(const item_storage& items_to_copy_) : items(items_to_copy_), max_contained_value(static_cast<value_type>(items_to_copy_.size()) - 1)
		{
		}

	public:
		using const_iterator = typename item_storage::const_iterator;
		using const_reverse_iterator = typename item_storage::const_reverse_iterator;

		ShuffledIntSequence() = delete;
		ShuffledIntSequence(const ShuffledIntSequence<value_type>& to_copy_) : items(to_copy_.items), max_contained_value(to_copy_.max_contained_value)
		{
		}
		ShuffledIntSequence(std::size_t size_, bool do_64_bit_shuffle_) : ShuffledIntSequence(size_)
		{
			Shuffle(do_64_bit_shuffle_);
		}
		ShuffledIntSequence(std::size_t size_, seed_32_type shuffle_seed_32_) : ShuffledIntSequence(size_)
		{
			Shuffle(shuffle_seed_32_);
		}
		ShuffledIntSequence(std::size_t size_, seed_64_type shuffle_seed_64_) : ShuffledIntSequence(size_)
		{
			Shuffle(shuffle_seed_64_);
		}
		ShuffledIntSequence(ShuffledIntSequence<value_type>&& to_move_) noexcept : ShuffledIntSequence()
		{
			items.swap(to_move_.items);
			max_contained_value = to_move_.max_contained_value;
			to_move_.max_contained_value = value_type(0);
		}

		inline ShuffledIntSequence<value_type>& operator=(const ShuffledIntSequence<value_type>& to_copy_)
		{
			items = to_copy_.items;
			max_contained_value = to_copy_.max_contained_value;
		}

		[[nodiscard]] inline bool operator!() const
		{
			return items.size() == 0;
		}

		[[nodiscard]] inline ShuffledIntSequence<value_type> operator<<(std::size_t num_shifts_) const
		{
			const std::size_t size_ = size();
			if (size_ >= 2)
			{
				num_shifts_ = num_shifts_ % size_;
				if (num_shifts_ != 0)
				{
					item_storage out_(size_);
					std::size_t end_ = size_ - num_shifts_;
					for (std::size_t i = 0; i < end_; ++i)
					{
						out_[i] = items[i + num_shifts_];
					}
					for (std::size_t i = end_, offset_ = 0; i < size_; ++i, ++offset_)
					{
						out_[i] = items[offset_];
					}
					return ShuffledIntSequence<value_type>(out_);
				}
				else
				{
					return ShuffledIntSequence<value_type>(items);
				}
			}
			else
			{
				return ShuffledIntSequence(items);
			}
		}

		[[nodiscard]] inline ShuffledIntSequence<value_type> operator>>(std::size_t num_shifts_) const
		{
			const std::size_t size_ = size();
			if (size_ >= 2)
			{
				num_shifts_ = num_shifts_ % size_;
				if (num_shifts_ != 0)
				{
					item_storage out_(size_);
					std::size_t offset_ = size_ - num_shifts_;
					std::size_t i = 0;
					for (; offset_ != size_; ++i, ++offset_)
					{
						out_[i] = items[offset_];
					}
					for (; i < size_; ++i)
					{
						out_[i] = items[i - num_shifts_];
					}

					return ShuffledIntSequence<value_type>(out_);
				}
				else
				{
					return ShuffledIntSequence<value_type>(items);
				}
			}
			else
			{
				return ShuffledIntSequence(items);
			}
		}

		inline ShuffledIntSequence<value_type>& operator<<=(std::size_t num_shifts_)
		{
			this->operator=(this->operator<<(num_shifts_));
			return *this;
		}

		inline ShuffledIntSequence<value_type>& operator>>=(std::size_t num_shifts_)
		{
			this->operator=(this->operator>>(num_shifts_));
			return *this;
		}

		[[nodiscard]] inline const value_type& operator[](std::size_t index_) const
		{
			return at(index_);
		}

		[[nodiscard]] inline const value_type& at(std::size_t index_) const
		{
			return items[index_];
		}

		[[nodiscard]] inline std::size_t size() const
		{
			return items.size();
		}

		inline void swap(ShuffledIntSequence& to_swap_with_)
		{
			items.swap(to_swap_with_.items);
			value_type temp_ = max_contained_value;
			max_contained_value = to_swap_with_.max_contained_value;
			to_swap_with_.max_contained_value = temp_;
		}

		[[nodiscard]] inline const_iterator cbegin() const
		{
			return items.cbegin();
		}
		[[nodiscard]] inline const_iterator cend() const
		{
			return items.cend();
		}

		[[nodiscard]] inline const_reverse_iterator crbegin() const
		{
			return items.crbegin();
		}
		[[nodiscard]] inline const_reverse_iterator crend() const
		{
			return items.crend();
		}

		/// <summary> Resizes this sequence to contain the specified number of items. </summary>
		/// <param name="size_">Number of items to be contained in this sequence after the resize.</param>
		inline void resize(std::size_t size_, bool do_64_bit_shuffle_ = false)
		{
			_do_resize<bool>(size_, do_64_bit_shuffle_);
		}
		inline void resize(std::size_t size_, seed_32_type seed_32_)
		{
			_do_resize<seed_32_type>(size_, seed_32_);
		}
		inline void resize(std::size_t size_, seed_64_type seed_64_)
		{
			_do_resize<seed_64_type>(size_, seed_64_);
		}

		inline void shrink_to_fit()
		{
			items.resize();
		}

		/// <summary> Shuffles the items contained within this sequence. </summary>
		inline void Shuffle(const bool& do_64_bit_shuffle_)
		{
			if (do_64_bit_shuffle_)
			{
				_do_shuffle<EmuMath::RngWrapper<true>, seed_64_type>(default_seed_64());
			}
			else
			{
				_do_shuffle<EmuMath::RngWrapper<false>, seed_32_type>(default_seed_32());
			}
		}
		inline void Shuffle(const seed_32_type& seed_32_)
		{
			_do_shuffle<EmuMath::RngWrapper<false>, seed_32_type>(seed_32_);
		}
		inline void Shuffle(const seed_64_type& seed_64_)
		{
			_do_shuffle<EmuMath::RngWrapper<true>, seed_64_type>(seed_64_);
		}

		/// <summary> Reverses the storage of elements within this sequence. </summary>
		inline void Reverse()
		{
			item_storage reversed_(size());
			std::copy(items.rbegin(), items.rend(), reversed_.begin());
			reversed_.swap(items);
		}

		/// <summary> Provides a reversed form of this sequence without modifying this instance. </summary>
		/// <returns>Copy of this instance with its contained elements reversed.</returns>
		[[nodiscard]] inline ShuffledIntSequence<value_type> AsReversed() const
		{
			item_storage out_(size());
			std::copy(items.rbegin(), items.rend(), out_.begin());
			return ShuffledIntSequence(out_);
		}

		/// <summary> The highest value in this sequence. Effectively shorthand for size() - 1. </summary>
		[[nodiscard]] inline value_type HighestStoredValue() const
		{
			return max_contained_value;
		}

		/// <summary>
		/// <para> Returns a boolean indicating if this sequence contains a number of items equal to a power of 2. </para>
		/// <para> Sequences where this value is true have the special attribute of a HighestContainedValue which may be used to mask all bits of all contained values. </para>
		/// </summary>
		/// <returns>True if this sequence's size is a power of 2; otherwise false.</returns>
		[[nodiscard]] inline bool ContainsPowerOf2() const
		{
			return EmuCore::ArithmeticHelpers::is_integral_power_of_2<std::size_t>(size());
		}

		/// <summary>
		/// <para> Changes the storage of this sequence to store a power of 2, prioritising the previous power of 2. </para>
		/// <para> If this sequence already contains a power of 2, no changes will occur. </para>
		/// <para> If this sequence is below the minimum power of 2, it will instead increase to the first possible power of 2. </para>
		/// </summary>
		inline void TryShortenToPowerOf2(bool do_64_bit_shuffle_)
		{
			_try_do_shorten_to_power_of_2<bool>(do_64_bit_shuffle_);
		}
		inline void TryShortenToPowerOf2(seed_32_type seed_32_)
		{
			_try_do_shorten_to_power_of_2<seed_32_type>(seed_32_);
		}
		inline void TryShortenToPowerOf2(seed_64_type seed_64_)
		{
			_try_do_shorten_to_power_of_2<seed_64_type>(seed_64_);
		}

		/// <summary>
		/// <para> Changes the storage of this sequence to store a power of 2, prioritising the next power of 2. </para>
		/// <para> If this sequence already contains a power of 2, no changes will occur. </para>
		/// <para> If this sequence is above the maximum power of 2, it will instead decrease to the final possible power of 2. </para>
		/// </summary>
		inline void TryIncreaseToPowerOf2(bool do_64_bit_shuffle_)
		{
			_try_do_increase_to_power_of_2<bool>(do_64_bit_shuffle_);
		}
		inline void TryIncreaseToPowerOf2(seed_32_type seed_32_)
		{
			_try_do_increase_to_power_of_2<seed_32_type>(seed_32_);
		}
		inline void TryIncreaseToPowerOf2(seed_64_type seed_64_)
		{
			_try_do_increase_to_power_of_2<seed_64_type>(seed_64_);
		}

	private:
		item_storage items;
		value_type max_contained_value;

		template<typename SeedOrBool_>
		inline void _do_resize(std::size_t new_size_, SeedOrBool_ seed_or_do_64_bit_shuffle_bool_)
		{
			if (new_size_ < size())
			{
				items.resize(new_size_);
			}
			else
			{
				items.resize(new_size_);
				_fill_items_pre_shuffle();
			}
			max_contained_value = static_cast<value_type>(new_size_) - 1;
			Shuffle(seed_or_do_64_bit_shuffle_bool_);
		}

		template<typename SeedOrBool_>
		inline void _try_do_shorten_to_power_of_2(SeedOrBool_ seed_or_do_64_bit_shuffle_bool_)
		{
			if (!ContainsPowerOf2())
			{
				std::size_t power_ = EmuCore::ArithmeticHelpers::highest_set_uint_bit<std::size_t>(size());
				if (power_ == 0)
				{
					power_ = 1;
				}
				items.resize(power_);
				max_contained_value = static_cast<value_type>(power_) - 1;
				Shuffle(seed_or_do_64_bit_shuffle_bool_);
			}
		}

		template<typename SeedOrBool_>
		inline void _try_do_increase_to_power_of_2(SeedOrBool_ seed_or_do_64_bit_shuffle_bool_)
		{
			if (!ContainsPowerOf2())
			{
				std::size_t power_ = EmuCore::ArithmeticHelpers::next_unsigned_power_of_2<std::size_t>(size());
				if (power_ > size())
				{
					items.resize(power_);
					max_contained_value = static_cast<value_type>(power_) - 1;
					_fill_items_pre_shuffle();
					Shuffle(seed_or_do_64_bit_shuffle_bool_);
				}
				else
				{
					_try_do_shorten_to_power_of_2<SeedOrBool_>(seed_or_do_64_bit_shuffle_bool_);
				}
			}
		}

		template<class Rng_, typename Seed_>
		inline void _do_shuffle(Seed_ seed_)
		{
			std::size_t n_ = items.size();
			if (n_ > 1)
			{
				Rng_ rng_(seed_);
				do
				{
					std::size_t k_ = rng_.NextInt<std::size_t>(0, --n_);
					value_type temp_ = items[k_];
					items[k_] = items[n_];
					items[n_] = temp_;

				} while (n_ > 1);
			}
		}

		inline void _fill_items_pre_shuffle()
		{
			for (std::size_t i = 0, end = items.size(); i < end; ++i)
			{
				items[i] = static_cast<value_type>(i);
			}
			max_contained_value = static_cast<value_type>(items.size()) - 1;
		}
	};
}

template<typename T_>
inline std::ostream& operator<<(std::ostream& str_, const EmuMath::ShuffledIntSequence<T_>& permutations_)
{
	str_ << "{";
	std::size_t size_ = permutations_.size();
	if (size_ != 0)
	{
		str_ << " " << permutations_[0];
		for (std::size_t i = 1; i < size_; ++i)
		{
			str_ << ", " << permutations_[i];
		}
	}
	str_ << " }";
	return str_;
}
template<typename T_>
inline std::wostream& operator<<(std::wostream& str_, const EmuMath::ShuffledIntSequence<T_>& permutations_)
{
	str_ << L"{";
	std::size_t size_ = permutations_.size();
	if (size_ != 0)
	{
		str_ << L" " << permutations_[0];
		for (std::size_t i = 1; i < size_; ++i)
		{
			str_ << L", " << permutations_[i];
		}
	}
	str_ << L" }";
	return str_;
}

#endif
