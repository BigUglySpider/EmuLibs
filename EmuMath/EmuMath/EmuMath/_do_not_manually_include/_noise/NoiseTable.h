#ifndef EMU_MATH_NOISE_TABLE_H_INC_
#define EMU_MATH_NOISE_TABLE_H_INC_ 1

#include "NoiseFunctors.h"
#include "NoiseSampleProcessors.h"
#include "../../../EmuCore/TMPHelpers/TypeComparators.h"
#include "../../../EmuCore/TMPHelpers/TypeConvertors.h"
#include <vector>

namespace EmuMath
{
	template<typename T_>
	class NoiseTable
	{
	public:
		using value_type = T_;
		using calc_type = typename EmuCore::TMPHelpers::first_floating_point_t<value_type, float>;

	private:
		using sample_storage = std::vector<std::vector<value_type>>;

	public:
		NoiseTable() : samples(), size_x(0), size_y(0)
		{
		}
		template<typename RhsT_>
		NoiseTable(const NoiseTable<RhsT_>& to_copy_) : samples(), size_x(to_copy_.size_x), size_y(to_copy_.size_y)
		{
			_do_copy(to_copy_);
		}
		template<>
		NoiseTable(const NoiseTable<value_type>& to_copy_) : samples(to_copy_.samples), size_x(to_copy_.size_x), size_y(to_copy_.size_y)
		{
		}

#pragma region RANDOM_ACCESS
		inline const value_type& operator()(const std::size_t x_, const std::size_t y_) const
		{
			return at(x_, y_);
		}
		inline const value_type& operator[](const std::size_t index_) const
		{
			return at(index_);
		}

		inline const value_type& at(const std::size_t x_, const std::size_t y_) const
		{
			return samples[y_][x_];
		}
		inline const value_type& at(const std::size_t index_) const
		{
			return at(index_ % size_x, index_ / size_y);
		}
#pragma endregion

#pragma region STL_MIMICS
		inline void clear()
		{
			samples.clear();
		}

		inline void shrink_to_fit()
		{
			samples.shrink_to_fit();
		}

		inline std::size_t size() const
		{
			return size_x * size_y;
		}

		inline void swap(NoiseTable<value_type>& table_to_swap_with_)
		{
			table_to_swap_with_.samples.swap(samples);
			_swap_sizes(table_to_swap_with_);
		}
#pragma endregion

#pragma region STL_EXTENSIONS
		inline void ClearAndShrink()
		{
			sample_storage().swap(samples);
		}

		inline std::size_t SizeX() const
		{
			return size_x;
		}
		inline std::size_t SizeY() const
		{
			return size_y;
		}
#pragma endregion

	private:
		sample_storage samples;
		std::size_t size_x;
		std::size_t size_y;

		template<typename RhsT_>
		inline void _swap_sizes(NoiseTable<RhsT_>& table_to_swap_with_)
		{
			std::size_t temp_ = size_x;
			size_x = table_to_swap_with_.size_x;
			table_to_swap_with_.size_x = temp_;

			temp_ = size_y;
			size_y = table_to_swap_with_.size_y;
			table_to_swap_with_.size_y = temp_;
		}

		template<typename RhsT_>
		inline void _do_copy(const NoiseTable<RhsT_>& table_to_copy_)
		{
			samples.resize(size_y);
			for (std::size_t y_ = 0; y_ < size_y; ++y_)
			{
				const auto& in_row_ = table_to_copy_.samples[y_];
				auto& row_ = samples[y_];
				row_.resize(size_x);
				for (std::size_t x_ = 0; x_ < size_x; ++x_)
				{
					row_[x_] = static_cast<value_type>(in_row_[x_]);
				}
			}
		}
		template<>
		inline void _do_copy(const NoiseTable<value_type>& table_to_copy_)
		{
			samples = table_to_copy_.samples;
		}
	};
}

#endif
