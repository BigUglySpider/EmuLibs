#ifndef EMU_MATH_NOISE_TABLE_H_INC_
#define EMU_MATH_NOISE_TABLE_H_INC_ 1

#include "NoiseFunctors.h"
#include "NoiseSampleProcessors.h"
#include "NoiseTableOptions.h"
#include "NoiseTMP.h"
#include "../../../EmuCore/TMPHelpers/TypeComparators.h"
#include "../../../EmuCore/TMPHelpers/TypeConvertors.h"
#include <ostream>
#include <sstream>
#include <vector>

#include <iostream>

namespace EmuMath
{
	template<std::size_t Dimensions_>
	class NoiseTable
	{
	public:
		static_assert(EmuMath::TMP::assert_valid_noise_dimensions<Dimensions_>(), "Provided invalid Dimensions_ value to instantiate an EmuMath::NoiseTable template.");
		static constexpr std::size_t num_dimensions = Dimensions_;
		using value_type = float;

	private:
		/// <summary>table_storage will be a Dimensions_-dimensional vector of value_types.</summary>
		using table_storage = typename EmuMath::TMP::_noise_table_dimension_conditional
		<
			num_dimensions,
			EmuMath::TMP::noise_table_internal_layer<value_type>,
			EmuMath::TMP::noise_table_internal_layer<EmuMath::TMP::noise_table_internal_layer<value_type>>,
			EmuMath::TMP::noise_table_internal_layer<EmuMath::TMP::noise_table_internal_layer<EmuMath::TMP::noise_table_internal_layer<value_type>>>
		>::type;

	public:
		using return_single_index = typename EmuMath::TMP::_noise_table_access<1, num_dimensions, value_type>::type;
		using return_double_index = typename EmuMath::TMP::_noise_table_access<2, num_dimensions, value_type>::type;
		using return_triple_index = typename EmuMath::TMP::_noise_table_access<3, num_dimensions, value_type>::type;

		NoiseTable() : table_data(), table_size()
		{
		}

#pragma region RANDOM_ACCESS
		/// <summary>
		/// <para> Accesses the first layer of this noise table. </para>
		/// <para> If this table is 1-dimensional, this will provide a copy of the provided index. Otherwise, it will provide constant access to the first layer. </para>
		/// </summary>
		/// <returns>Copy of the sample at the provided index if 1D; otherwise, a constant reference to the first layer of the table.</returns>
		[[nodiscard]] inline return_single_index at(std::size_t index_x_) const
		{
			return table_data[index_x_];
		}
		/// <summary>
		/// <para> Accesses the second layer of this noise table. </para>
		/// <para> If this table is 2-dimensional, this will provide a copy of the provided index. If it is greater, it will provide constant access to the second layer. </para>
		/// <para> This method is not available for 1-dimensional tables. </para>
		/// </summary>
		/// <returns>Copy of the sample at the provided index if 2D; if greater than 2D, a constant reference to the second layer of the table; otherwise void.</returns>
		template<typename RequiresAtLeast2D_ = std::enable_if_t<num_dimensions >= 2>>
		[[nodiscard]] inline return_double_index at(std::size_t index_x_, std::size_t index_y_) const
		{
			if constexpr (num_dimensions >= 2)
			{
				return table_data[index_x_][index_y_];
			}
		}
		/// <summary>
		/// <para> Accesses the third layer of this noise table. </para>
		/// <para> If this table is 3-dimensional, this will provide a copy of the provided index. </para>
		/// <para> This method is not available for 1- and 2-dimensional tables. </para>
		/// </summary>
		/// <returns>Copy of the sample at the provided index if 3D; otherwise void.</returns>
		template<typename RequiresAtLeast3D_ = std::enable_if_t<num_dimensions >= 3>>
		[[nodiscard]] inline return_triple_index at(std::size_t index_x_, std::size_t index_y_, std::size_t index_z_) const
		{
			if constexpr (num_dimensions >= 3)
			{
				return table_data[index_x_][index_y_][index_z_];
			}
		}

		/// <summary>
		/// <para> Returns a copy of the value at the index specified by the respective elements of the passed vector. </para>
		/// <para>
		///		For elements the vector does not contain, its theoretical value (typically 0) will be used instead. 
		///		To access a layer with only the vector's indices, use the form of this function taking scalar index arguments instead.
		/// </para>
		/// </summary>
		/// <param name="indices_">EmuMath vector containing respective indices of the sample of this table to access.</param>
		/// <returns>Copy of this table's sample at the specified indices.</returns>
		template<std::size_t Size_>
		[[nodiscard]] inline value_type at(const EmuMath::Vector<Size_, std::size_t>& indices_) const
		{
			if constexpr (num_dimensions == 1)
			{
				return at(indices_.at<0>());
			}
			else if constexpr (num_dimensions == 2)
			{
				return at(indices_.at<0>(), EmuMath::Helpers::VectorGetTheoretical<1>(indices_));
			}
			else if constexpr (num_dimensions == 3)
			{
				return at(indices_.at<0>(), EmuMath::Helpers::VectorGetTheoretical<1>(indices_), EmuMath::Helpers::VectorGetTheoretical<2>(indices_));
			}
			else
			{
				static_assert(false, "Attempted to retrieve an index of an impossibly-dimensioned EmuMath::NoiseTable.");
			}
		}

		[[nodiscard]] inline return_single_index operator()(std::size_t index_x_) const
		{
			return at(index_x_);
		}
		template<typename RequiresAtLeast2D_ = std::enable_if_t<num_dimensions >= 2>>
		[[nodiscard]] inline return_double_index operator()(std::size_t index_x_, std::size_t index_y_) const
		{
			if constexpr (num_dimensions >= 2)
			{
				return at(index_x_, index_y_);
			}
		}
		template<typename RequiresAtLeast3D_ = std::enable_if_t<num_dimensions >= 3>>
		[[nodiscard]] inline return_triple_index operator()(std::size_t index_x_, std::size_t index_y_, std::size_t index_z_) const
		{
			if constexpr (num_dimensions >= 3)
			{
				return at(index_x_, index_y_, index_z_);
			}
		}
		template<std::size_t Size_>
		[[nodiscard]] inline value_type operator()(const EmuMath::Vector<Size_, std::size_t>& indices_) const
		{
			return at(indices_);
		}

		[[nodiscard]] inline return_single_index operator[](std::size_t index_x_) const
		{
			return at(index_x_);
		}
		template<std::size_t Size_>
		[[nodiscard]] inline value_type operator[](const EmuMath::Vector<Size_, std::size_t>& indices_) const
		{
			return at(indices_);
		}
#pragma endregion

#pragma region INFO
		[[nodiscard]] inline EmuMath::Vector<Dimensions_, std::size_t> size() const
		{
			return table_size;
		}
#pragma endregion

#pragma region GENERATION
		template<EmuMath::NoiseType NoiseType_, class SampleProcessor_ = EmuMath::Functors::noise_sample_processor_default>
		inline bool GenerateNoise(const EmuMath::NoiseTableOptions<num_dimensions>& options_)
		{
			if (_valid_resolution(options_.table_resolution))
			{
				_do_resize(options_.table_resolution);
				_do_generation
				<
					EmuMath::NoiseGenFunctor<num_dimensions, NoiseType_>,
					SampleProcessor_
				>(options_.start_point, options_.MakeStep(), options_.freq, options_.permutation_info.MakePermutations());
				return true;
			}
			else
			{
				return false;
			}
		}
#pragma endregion

	private:
		table_storage table_data;
		EmuMath::Vector<num_dimensions, std::size_t> table_size;

		static constexpr inline bool _valid_resolution(const EmuMath::Vector<num_dimensions, std::size_t>& res_)
		{
			return !res_.CmpAnyEqualTo<true, std::size_t>(0);
		}

		inline void _do_resize(const EmuMath::Vector<num_dimensions, std::size_t>& res_)
		{
			if constexpr (num_dimensions == 1)
			{
				table_data.resize(res_.at<0>(), value_type());
			}
			else if constexpr (num_dimensions == 2)
			{
				table_data.resize
				(
					res_.at<0>(),
					EmuMath::TMP::noise_table_internal_layer<value_type>(res_.at<1>(), value_type())
				);
			}
			else if constexpr (num_dimensions == 3)
			{
				table_data.resize
				(
					res_.at<0>(),
					EmuMath::TMP::noise_table_internal_layer<EmuMath::TMP::noise_table_internal_layer<value_type>>
					(
						res_.at<1>(), 
						EmuMath::TMP::noise_table_internal_layer<value_type>(res_.at<2>(), value_type())
					)
				);
			}
			table_size = res_;
		}

		template<typename Generator_, typename SampleProcessor_>
		inline void _do_generation
		(
			EmuMath::Vector<num_dimensions, value_type> start_,
			EmuMath::Vector3<value_type> step_,
			float freq_,
			const EmuMath::NoisePermutations& permutations_
		)
		{
			Generator_ generator_ = Generator_();
			SampleProcessor_ sample_processor_ = SampleProcessor_();

			EmuMath::Vector<num_dimensions, value_type> point_(start_);
			if constexpr (num_dimensions == 1)
			{
				for (std::size_t x_ = 0, end_x_ = table_data.size(); x_ < end_x_; ++x_)
				{
					table_data[x_] = sample_processor_(generator_(point_, freq_, permutations_));
					point_.at<0>() += step_.at<0>();
				}
			}
			else if constexpr (num_dimensions == 2)
			{
				for (std::size_t x_ = 0, end_x_ = table_data.size(); x_ < end_x_; ++x_)
				{
					auto& layer_x_ = table_data[x_];
					point_.at<1>() = start_.at<1>();
					for (std::size_t y_ = 0, end_y_ = layer_x_.size(); y_ < end_y_; ++y_)
					{
						layer_x_[y_] = sample_processor_(generator_(point_, freq_, permutations_));
						point_.at<1>() += step_.at<1>();
					}
					point_.at<0>() += step_.at<0>();
				}
			}
			else if constexpr (num_dimensions == 3)
			{
				for (std::size_t x_ = 0, end_x_ = table_size.at<0>(); x_ < end_x_; ++x_)
				{
					auto& layer_x_ = table_data[x_];
					point_.at<1>() = start_.at<1>();
					for (std::size_t y_ = 0, end_y_ = table_size.at<1>(); y_ < end_y_; ++y_)
					{
						auto& layer_y_ = layer_x_[y_];
						point_.at<2>() = start_.at<2>();
						for (std::size_t z_ = 0, end_z_ = table_size.at<2>(); z_ < end_z_; ++z_)
						{
							value_type sample_ = generator_(point_, freq_, permutations_);
							sample_ = sample_processor_(sample_);
							//std::cout << "SAMPLE: " << sample_ << "\n";
							layer_y_[z_] = sample_;
							point_.at<2>() += step_.at<2>();
						}
						point_.at<1>() += step_.at<1>();
					}
					point_.at<0>() += step_.at<0>();
				}
			}
			else
			{
				static_assert(false, "Attempted to generate an impossibly-dimensioned EmuMath::NoiseTable.");
			}
		}
	};
}

template<std::size_t num_dimensions>
std::ostream& operator<<(std::ostream& str_, const EmuMath::NoiseTable<num_dimensions>& noise_table_)
{
	auto size_ = noise_table_.size();
	if constexpr (num_dimensions == 1)
	{
		str_ << "{";
		std::size_t size_x_ = size_.at<0>();
		if (size_x_ != 0)
		{
			str_ << " " << noise_table_.at(0);
			for (std::size_t x = 1; x < size_x_; ++x)
			{
				str_ << ", " << noise_table_.at(x);
			}
		}
		str_ << " }";
	}
	else if constexpr (num_dimensions == 2)
	{
		std::size_t size_x_ = size_.at<0>();
		std::size_t size_y_ = size_.at<1>();
		if (size_x_ != 0 && size_y_ != 0)
		{
			for (std::size_t y = 0; y < size_y_; ++y)
			{
				str_ << "{ " << noise_table_.at(0, y);
				for (std::size_t x = 1; x < size_x_; ++x)
				{
					str_ << ", " << noise_table_.at(x, y);
				}
				str_ << " }";
				if ((y + 1) < size_y_)
				{
					str_ << "\n";
				}
			}
		}
		else
		{
			str_ << "{ }";
		}
	}
	else if constexpr (num_dimensions == 3)
	{
		std::size_t size_x_ = size_.at<0>();
		std::size_t size_y_ = size_.at<1>();
		std::size_t size_z_ = size_.at<2>();
		if (size_x_ != 0 && size_y_ != 0 && size_z_ != 0)
		{
			for (std::size_t z = 0; z < size_z_; ++z)
			{
				for (std::size_t y = 0; y < size_y_; ++y)
				{
					str_ << "{ " << noise_table_.at(0, y, z);
					for (std::size_t x = 1; x < size_x_; ++x)
					{
						str_ << ", " << noise_table_.at(x, y, z);
					}
					str_ << " }";
					if ((y + 1) < size_y_)
					{
						str_ << "\n";
					}
				}
				if ((z + 1) < size_z_)
				{
					str_ << "\n---\n";
				}
			}
		}
		else
		{
			str_ << "{ }";
		}
	}
	else
	{
		static_assert(false, "ostream append of EmuMath::NoiseTable not available for higher any dimensions other than: 1, 2, 3.");
	}
	return str_;
}

#endif
