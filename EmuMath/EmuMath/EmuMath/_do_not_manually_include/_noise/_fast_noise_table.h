#ifndef EMU_MATH_FAST_NOISE_TABLE_H_INC_
#define EMU_MATH_FAST_NOISE_TABLE_H_INC_ 1

#include "_fast_noise_sample_processors.h"
#include "_fast_noise_functors.h"
#include "_noise_table_options.h"
#include "_noise_tmp.h"
#include "../../../EmuSIMD/SIMDHelpers.h"
#include "../../../EmuCore/TMPHelpers/TypeComparators.h"
#include "../../../EmuCore/TMPHelpers/TypeConvertors.h"
#include "../../../EmuCore/TMPHelpers/Values.h"
#include <ostream>
#include <sstream>
#include <vector>

namespace EmuMath
{
	/// <summary>
	/// <para> Noise table that makes use of SIMD-optimised sample generation methods. </para>
	/// <para> The MajorDimensionIndex_ must be a valid dimension index, where 0 is X, 1 is Y, and 2 is Z. </para>
	/// <para> 
	///		The MajorDimensionIndex_ identifies the dimension in which samples will be contiguously stored 
	///		(as they will be separated to allow better access to large tables). 
	/// </para>
	/// <para> It is recommended to use a MajorDimensionIndex_ that best suits the largest dimension in which noise will be generated (e.g. Y (1) for a 256x2048 table). </para>
	/// </summary>
	template<std::size_t NumDimensions_, std::size_t MajorDimensionIndex_ = NumDimensions_ - 1>
	class FastNoiseTable
	{
	public:
		static_assert(EmuMath::TMP::assert_valid_noise_dimensions<NumDimensions_>(), "Provided invalid NumDimensions_ value to instantiate an EmuMath::FastNoiseTable template.");
		static_assert
		(
			MajorDimensionIndex_ < NumDimensions_,
			"Provided an invalid MajorDimensionIndex_ value to instantiate an EmuMath::FastNoiseTable template. The provided value must be less than NumDimensions_."
		);

		static constexpr std::size_t num_dimensions = NumDimensions_;
		static constexpr std::size_t major_dimension = MajorDimensionIndex_;
		static constexpr std::size_t default_register_width = 128;
		using value_type = float;
		using this_type = FastNoiseTable<NumDimensions_, MajorDimensionIndex_>;
		using options_type = EmuMath::NoiseTableOptions<NumDimensions_, value_type>;
		using coordinate_type = EmuMath::Vector<num_dimensions, std::size_t>;

		template<std::size_t Size_, typename T_>
		[[nodiscard]] static inline coordinate_type make_coords_from_vector(const EmuMath::Vector<Size_, T_>& vector_)
		{
			if constexpr (num_dimensions == 1)
			{
				return coordinate_type(EmuMath::Helpers::vector_get_theoretical<0>(vector_));
			}
			else if constexpr (num_dimensions == 2)
			{
				return coordinate_type
				(
					EmuMath::Helpers::vector_get_theoretical<0>(vector_),
					EmuMath::Helpers::vector_get_theoretical<1>(vector_)
				);
			}
			else if constexpr (num_dimensions == 3)
			{
				return coordinate_type
				(
					EmuMath::Helpers::vector_get_theoretical<0>(vector_),
					EmuMath::Helpers::vector_get_theoretical<1>(vector_),
					EmuMath::Helpers::vector_get_theoretical<2>(vector_)
				);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<T_>(), "Attempted to make coordinates from a vector for an EmuMath::FastNoiseTable with prohibited dimensions.");
			}
		}

		/// <summary>
		/// <para> Helper to construct options for generating noise for this table with the provided arguments. </para>
		/// <para> Provided arguments are the respective arguments (including order) for the full custom constructor of this table's options. </para>
		/// </summary>
		[[nodiscard]] static inline options_type make_options
		(
			const EmuMath::Vector<num_dimensions, std::size_t>& table_resolution_,
			const EmuMath::Vector<num_dimensions, value_type>& start_point_,
			const EmuMath::Vector<num_dimensions, value_type>& end_point_or_step_,
			value_type freq_,
			bool step_mode_,
			bool use_fractal_noise_,
			const EmuMath::Info::NoisePermutationInfo& permutation_info_,
			const typename options_type::fractal_info_type& fractal_noise_info_
		)
		{
			return options_type
			(
				table_resolution_,
				start_point_,
				end_point_or_step_,
				freq_,
				step_mode_,
				use_fractal_noise_,
				permutation_info_,
				fractal_noise_info_
			);
		}

	private:
		/// <summary>table_storage will be a Dimensions_-dimensional vector of value_types.</summary>
		using table_storage = EmuMath::TMP::_full_noise_table_storage<num_dimensions, value_type>;

	public:
#pragma region CONSTRUCTORS
		FastNoiseTable() : samples(), table_size()
		{
		}

		FastNoiseTable(const this_type& to_copy_) : samples(to_copy_.samples), table_size(to_copy_.table_size)
		{
		}

		FastNoiseTable(this_type&& to_move_) noexcept : samples(std::move(to_move_.samples)), table_size(std::move(to_move_.table_size))
		{
		}
#pragma endregion

#pragma region RANDOM_ACCESS
		template<typename OnlyAvailableFor1Dimensional_ = std::enable_if_t<num_dimensions == 1>>
		[[nodiscard]] inline value_type at(std::size_t x_) const
		{
			return _get_index(coordinate_type(x_));
		}
		template<typename OnlyAvailableFor2Dimensional_ = std::enable_if_t<num_dimensions == 2>>
		[[nodiscard]] inline value_type at(std::size_t x_, std::size_t y_) const
		{
			return _get_index(coordinate_type(x_, y_));
		}
		template<typename OnlyAvailableFor3Dimensional_ = std::enable_if_t<num_dimensions == 3>>
		[[nodiscard]] inline value_type at(std::size_t x_, std::size_t y_, std::size_t z_) const
		{
			return _get_index(coordinate_type(x_, y_, z_));
		}

		template<std::size_t Size_>
		[[nodiscard]] inline value_type at(const EmuMath::Vector<Size_, std::size_t> coords_) const
		{
			if constexpr (Size_ == num_dimensions)
			{
				return _get_index(coords_);
			}
			else
			{
				return _get_index(make_coords_from_vector(coords_));
			}
		}

		template<typename OnlyAvailableFor1Dimensional_ = std::enable_if_t<num_dimensions == 1>>
		[[nodiscard]] inline value_type operator[](std::size_t x_) const
		{
			return at(x_);
		}
		template<std::size_t Size_>
		[[nodiscard]] inline value_type operator[](const EmuMath::Vector<Size_, std::size_t> coords_) const
		{
			return at(coords_);
		}

		template<typename OnlyAvailableFor1Dimensional_ = std::enable_if_t<num_dimensions == 1>>
		[[nodiscard]] inline value_type operator()(std::size_t x_) const
		{
			return at(x_);
		}
		template<typename OnlyAvailableFor2Dimensional_ = std::enable_if_t<num_dimensions == 2>>
		[[nodiscard]] inline value_type operator()(std::size_t x_, std::size_t y_) const
		{
			return at(x_, y_);
		}
		template<typename OnlyAvailableFor3Dimensional_ = std::enable_if_t<num_dimensions == 3>>
		[[nodiscard]] inline value_type operator()(std::size_t x_, std::size_t y_, std::size_t z_) const
		{
			return at(x_, y_, z_);
		}
		template<std::size_t Size_>
		[[nodiscard]] inline value_type operator()(const EmuMath::Vector<Size_, std::size_t> coords_) const
		{
			return at(coords_);
		}

		[[nodiscard]] inline this_type& operator=(const this_type&) = default;
#pragma endregion

		[[nodiscard]] inline coordinate_type size() const
		{
			return table_size;
		}
		template<std::size_t Index_>
		[[nodiscard]] inline std::size_t size() const
		{
			if constexpr (Index_ < num_dimensions)
			{
				return table_size.template at<Index_>();
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<std::size_t, Index_>(), "Provided an invalid index to EmuMath::FastNoiseTable::size. The provided Index_ must be less than the number of dimensions the table covers.");
			}
		}

#pragma region GENERATION
		template<EmuMath::NoiseType NoiseType_, class SampleProcessor_>
		inline bool GenerateNoise(const options_type& options_, SampleProcessor_ sample_processor_)
		{
			using register_type = __m128;
			using underlying_noise_gen_functor = EmuMath::fast_noise_gen_functor<num_dimensions, NoiseType_, register_type>;

			if (_valid_resolution(options_.table_resolution))
			{
				_do_resize(options_.table_resolution);

				// TODO: OTHER RESOLUTIONS
				if (options_.use_fractal_noise)
				{
					using fractal_generator = EmuMath::Functors::fractal_noise_wrapper<underlying_noise_gen_functor, register_type>;
					_do_generation<register_type, fractal_generator, SampleProcessor_&>
					(
						fractal_generator
						(
							options_.freq,
							options_.permutation_info.MakePermutations(),
							options_.fractal_noise_info
						),
						sample_processor_,
						options_.start_point,
						options_.MakeStep()
					);
				}
				else
				{
					using no_fractal_generator = EmuMath::Functors::no_fractal_noise_wrapper<underlying_noise_gen_functor, register_type>;
					_do_generation<register_type, no_fractal_generator, SampleProcessor_&>
					(
						no_fractal_generator
						(
							options_.freq,
							options_.permutation_info.MakePermutations()
						),
						sample_processor_,
						options_.start_point,
						options_.MakeStep()
					);
				}
				return true;
			}
			else
			{
				return false;
			}
		}
		template<EmuMath::NoiseType NoiseType_, class SampleProcessor_ = EmuMath::Functors::fast_noise_sample_processor_default>
		inline bool GenerateNoise(const options_type& options_)
		{
			return GenerateNoise<NoiseType_, SampleProcessor_>(options_, SampleProcessor_());
		}
#pragma endregion

	private:
		table_storage samples;
		coordinate_type table_size;

		template<class Generator_, class SampleProcessor_, class OutLayer_, class Register_>
		inline void _finish_major_segment_partial
		(
			Generator_& generator_,
			SampleProcessor_& sample_processor_,
			OutLayer_& out_layer_,
			Register_ points_x_,
			Register_ points_y_,
			Register_ points_z_,
			std::size_t i_,
			const std::size_t end_
		)
		{
			if (i_ < end_)
			{
				Register_ sample_batch_ = sample_processor_(generator_(points_x_, points_y_, points_z_));
				if ((i_ + 1) == end_)
				{
					out_layer_[i_] = EmuSIMD::get_index<0, value_type>(sample_batch_);
				}
				else
				{
					value_type calculated_values_[EmuSIMD::TMP::simd_register_width_v<Register_> / (sizeof(value_type) * 8)] = {};
					EmuSIMD::store(sample_batch_, calculated_values_);
					for (std::size_t index_ = 0; i_ < end_; ++i_, ++index_)
					{
						out_layer_[i_] = calculated_values_[index_];
					}
				}
			}
		}
		template<class Generator_, class SampleProcessor_, class OutLayer_, class Register_>
		inline void _finish_major_segment_partial
		(
			Generator_& generator_,
			SampleProcessor_& sample_processor_,
			OutLayer_& out_layer_,
			Register_ points_x_,
			Register_ points_y_,
			std::size_t i_,
			const std::size_t end_
		)
		{
			if (i_ < end_)
			{
				Register_ sample_batch_ = sample_processor_(generator_(points_x_, points_y_));
				if ((i_ + 1) == end_)
				{
					out_layer_[i_] = EmuSIMD::get_index<0, value_type>(sample_batch_);
				}
				else
				{
					value_type calculated_values_[EmuSIMD::TMP::simd_register_width_v<Register_> / (sizeof(value_type) * 8)] = {};
					EmuSIMD::store(sample_batch_, calculated_values_);
					for (std::size_t index_ = 0; i_ < end_; ++i_, ++index_)
					{
						out_layer_[i_] = calculated_values_[index_];
					}
				}
			}
		}
		template<class Generator_, class SampleProcessor_, class OutLayer_, class Register_>
		inline void _finish_major_segment_partial
		(
			Generator_& generator_,
			SampleProcessor_& sample_processor_,
			OutLayer_& out_layer_,
			Register_ points_x_,
			std::size_t i_,
			const std::size_t end_
		)
		{
			if (i_ < end_)
			{
				Register_ sample_batch_ = sample_processor_(generator_(points_x_));
				if ((i_ + 1) == end_)
				{
					out_layer_[i_] = EmuSIMD::get_index<0, value_type>(sample_batch_);
				}
				else
				{
					value_type calculated_values_[EmuSIMD::TMP::simd_register_width_v<Register_> / (sizeof(value_type) * 8)] = {};
					EmuSIMD::store(sample_batch_, calculated_values_);
					for (std::size_t index_ = 0; i_ < end_; ++i_, ++index_)
					{
						out_layer_[i_] = calculated_values_[index_];
					}
				}
			}
		}

		template<class Register_, class Generator_, class SampleProcessor_>
		inline void _do_generation
		(
			Generator_ generator_,
			SampleProcessor_ sample_processor_,
			const EmuMath::Vector<num_dimensions, value_type> start_,
			const EmuMath::Vector<num_dimensions, value_type> step_
		)
		{
			constexpr std::size_t num_elements_per_batch = EmuSIMD::TMP::simd_register_width_v<Register_> / (sizeof(value_type) * 8);
			constexpr value_type num_elements_per_batch_value_cast = static_cast<value_type>(num_elements_per_batch);

			if constexpr (num_dimensions == 3)
			{
				std::size_t end_x_ = table_size.template at<0>();
				std::size_t end_y_ = table_size.template at<1>();
				std::size_t end_z_ = table_size.template at<2>();
				std::size_t end_store_batch_ = table_size.template at<major_dimension>();
				end_store_batch_ -= end_store_batch_ % num_elements_per_batch;


				Register_ points_x_ = EmuSIMD::set1<Register_>(start_.template at<0>());
				Register_ points_y_ = EmuSIMD::set1<Register_>(start_.template at<1>());
				Register_ points_z_ = EmuSIMD::set1<Register_>(start_.template at<2>());
				Register_ step_x_ = EmuSIMD::set1<Register_>(step_.template at<0>());
				Register_ step_y_ = EmuSIMD::set1<Register_>(step_.template at<1>());
				Register_ step_z_ = EmuSIMD::set1<Register_>(step_.template at<2>());

				if constexpr (major_dimension == 0)
				{
					Register_ start_x_ = EmuSIMD::add(points_x_, EmuSIMD::mul_all(step_x_, EmuSIMD::setr_incrementing<Register_, 0>()));
					Register_ start_z_ = points_z_;
					step_x_ = EmuSIMD::mul_all(step_x_, EmuSIMD::set1<Register_>(num_elements_per_batch_value_cast));

					for (std::size_t y = 0; y < end_y_; ++y)
					{
						auto& layer_0_ = samples[y];
						points_z_ = start_z_;

						for (std::size_t z = 0; z < end_z_; ++z)
						{
							auto& layer_1_ = layer_0_[z];
							std::size_t x = 0;
							points_x_ = start_x_;

							for (; x < end_store_batch_; x += num_elements_per_batch)
							{
								EmuSIMD::store(sample_processor_(generator_(points_x_, points_y_, points_z_)), &(layer_1_[x]));
								points_x_ = EmuSIMD::add(points_x_, step_x_);
							}
							_finish_major_segment_partial(generator_, sample_processor_, layer_1_, points_x_, points_y_, points_z_, x, end_x_);
							points_z_ = EmuSIMD::add(points_z_, step_z_);
						}
						points_y_ = EmuSIMD::add(points_y_, step_y_);
					}
				}
				else if constexpr (major_dimension == 1)
				{
					Register_ start_y_ = EmuSIMD::add(points_y_, EmuSIMD::mul_all(step_y_, EmuSIMD::setr_incrementing<Register_, 0>()));
					Register_ start_z_ = points_z_;
					step_y_ = EmuSIMD::mul_all(step_y_, EmuSIMD::set1<Register_>(num_elements_per_batch_value_cast));

					for (std::size_t x = 0; x < end_x_; ++x)
					{
						auto& layer_0_ = samples[x];
						points_z_ = start_z_;

						for (std::size_t z = 0; z < end_z_; ++z)
						{
							auto& layer_1_ = layer_0_[z];
							std::size_t y = 0;
							points_y_ = start_y_;

							for (; y < end_store_batch_; y += num_elements_per_batch)
							{
								EmuSIMD::store(sample_processor_(generator_(points_x_, points_y_, points_z_)), &(layer_1_[y]));
								points_y_ = EmuSIMD::add(points_y_, step_y_);
							}
							_finish_major_segment_partial(generator_, sample_processor_, layer_1_, points_x_, points_y_, points_z_, y, end_y_);
							points_z_ = EmuSIMD::add(points_z_, step_z_);
						}
						points_x_ = EmuSIMD::add(points_x_, step_x_);
					}
				}
				else
				{
					Register_ start_y_ = points_y_;
					Register_ start_z_ = EmuSIMD::add(points_z_, EmuSIMD::mul_all(step_z_, EmuSIMD::setr_incrementing<Register_, 0>()));
					step_z_ = EmuSIMD::mul_all(step_z_, EmuSIMD::set1<Register_>(num_elements_per_batch_value_cast));

					for (std::size_t x = 0; x < end_x_; ++x)
					{
						auto& layer_0_ = samples[x];
						points_y_ = start_y_;

						for (std::size_t y = 0; y < end_y_; ++y)
						{
							auto& layer_1_ = layer_0_[y];
							std::size_t z = 0;
							points_z_ = start_z_;

							for (; z < end_store_batch_; z += num_elements_per_batch)
							{
								EmuSIMD::store(sample_processor_(generator_(points_x_, points_y_, points_z_)), &(layer_1_[z]));
								points_z_ = EmuSIMD::add(points_z_, step_z_);
							}
							_finish_major_segment_partial(generator_, sample_processor_, layer_1_, points_x_, points_y_, points_z_, z, end_z_);
							points_y_ = EmuSIMD::add(points_y_, step_y_);
						}
						points_x_ = EmuSIMD::add(points_x_, step_x_);
					}
				}
			}
			else if constexpr (num_dimensions == 2)
			{
				std::size_t end_x_ = table_size.template at<0>();
				std::size_t end_y_ = table_size.template at<1>();
				std::size_t end_store_batch_ = table_size.template at<major_dimension>();
				end_store_batch_ -= end_store_batch_ % num_elements_per_batch;


				Register_ points_x_ = EmuSIMD::set1<Register_>(start_.template at<0>());
				Register_ points_y_ = EmuSIMD::set1<Register_>(start_.template at<1>());
				Register_ step_x_ = EmuSIMD::set1<Register_>(step_.template at<0>());
				Register_ step_y_ = EmuSIMD::set1<Register_>(step_.template at<1>());

				if constexpr (major_dimension == 0)
				{
					Register_ start_x_ = EmuSIMD::add(points_x_, EmuSIMD::mul_all(step_x_, EmuSIMD::setr_incrementing<Register_, 0>()));
					step_x_ = EmuSIMD::mul_all(step_x_, EmuSIMD::set1<Register_>(num_elements_per_batch_value_cast));
					for (std::size_t y = 0; y < end_y_; ++y)
					{
						auto& layer_ = samples[y];
						std::size_t x = 0;
						points_x_ = start_x_;
						for (; x < end_store_batch_; x += num_elements_per_batch)
						{
							EmuSIMD::store(sample_processor_(generator_(points_x_, points_y_)), &(layer_[x]));
							points_x_ = EmuSIMD::add(points_x_, step_x_);
						}
						_finish_major_segment_partial(generator_, sample_processor_, layer_, points_x_, points_y_, x, end_x_);
						points_y_ = EmuSIMD::add(points_y_, step_y_);
					}
				}
				else
				{
					Register_ start_y_ = EmuSIMD::add(points_y_, EmuSIMD::mul_all(step_y_, EmuSIMD::setr_incrementing<Register_, 0>()));
					step_y_ = EmuSIMD::mul_all(step_y_, EmuSIMD::set1<Register_>(num_elements_per_batch_value_cast));
					for (std::size_t x = 0; x < end_x_; ++x)
					{
						auto& layer_ = samples[x];
						std::size_t y = 0;
						points_y_ = start_y_;
						for (; y < end_store_batch_; y += num_elements_per_batch)
						{
							EmuSIMD::store(sample_processor_(generator_(points_x_, points_y_)), &(layer_[y]));
							points_y_ = EmuSIMD::add(points_y_, step_y_);
						}
						_finish_major_segment_partial(generator_, sample_processor_, layer_, points_x_, points_y_, y, end_y_);
						points_x_ = EmuSIMD::add(points_x_, step_x_);
					}
				}
			}
			else if constexpr (num_dimensions == 1)
			{
				std::size_t end_ = table_size.template at<0>();
				std::size_t end_store_batch_ = table_size.template at<0>();
				end_store_batch_ -= end_store_batch_ % num_elements_per_batch;


				Register_ points_simd_ = EmuSIMD::set1<Register_>(start_.template at<0>());
				Register_ step_simd_ = EmuSIMD::set1<Register_>(step_.template at<0>());
				points_simd_ = EmuSIMD::add(points_simd_, EmuSIMD::mul_all(step_simd_, EmuSIMD::setr_incrementing<Register_, 0>()));
				step_simd_ = EmuSIMD::mul_all(step_simd_, EmuSIMD::set1<Register_>(num_elements_per_batch_value_cast));

				std::size_t i = 0;
				for (; i < end_store_batch_; i += num_elements_per_batch)
				{
					EmuSIMD::store(sample_processor_(generator_(points_simd_)), &(samples[i]));
					points_simd_ = EmuSIMD::add(points_simd_, step_simd_);
				}
				_finish_major_segment_partial(generator_, sample_processor_, samples, points_simd_, i, end_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to generate an impossibly-dimensioned EmuMath::FastNoiseTable.");
			}
		}

		[[nodiscard]] static constexpr inline bool _valid_resolution(const EmuMath::Vector<num_dimensions, std::size_t>& new_size_)
		{
			return !new_size_.CmpAnyEqual(std::size_t(0));
		}

		void _do_resize(const coordinate_type& new_size_)
		{
			// We only do a resize if the new size is greater than what we currently have
			// --- This avoids a clear when resizing to something smaller, unlike the normal NoiseTable
			// --- This pertains to the "fast" aims of this noise table
			if (new_size_.CmpAnyGreater(table_size))
			{
				if constexpr (num_dimensions == 1)
				{
					// simple resize for 1 dimension.
					samples.resize(new_size_.template at<0>());
				}
				else if constexpr (num_dimensions == 2)
				{
					samples.clear();
					using layer_0_type = typename table_storage::value_type;

					// Simple resize for 2-dimensions, since major_dimension differences are a simple swap
					if constexpr (major_dimension == 0)
					{
						samples.resize(new_size_.template at<1>(), layer_0_type(new_size_.template at<0>()));
					}
					else
					{
						samples.resize(new_size_.template at<0>(), layer_0_type(new_size_.template at<1>()));
					}
				}
				else if constexpr (num_dimensions == 3)
				{
					samples.clear();
					using layer_0_type = typename table_storage::value_type;
					using layer_1_type = typename layer_0_type::value_type;

					// More complex for 3-dimensions as multiple layers change with major storage
					// --- Major item is always contiguous for its length
					// --- Always stored in alphabetical order excluding major (i.e. X-major will be stored YZX, Y-major stored XZY, Z-major stored XYZ)
					if constexpr (major_dimension == 0)
					{
						samples.resize
						(
							new_size_.template at<1>(),
							layer_0_type
							(
								new_size_.template at<2>(),
								layer_1_type(new_size_.template at<0>())
							)
						);
					}
					else if constexpr (major_dimension == 1)
					{
						samples.resize
						(
							new_size_.template at<0>(),
							layer_0_type
							(
								new_size_.template at<2>(),
								layer_1_type(new_size_.template at<1>())
							)
						);
					}
					else
					{
						samples.resize
						(
							new_size_.template at<0>(),
							layer_0_type
							(
								new_size_.template at<1>(),
								layer_1_type(new_size_.template at<2>())
							)
						);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_dimensions>(), "Attempted to resize an EmuMath::FastNoiseTable with a prohibited number of dimensions.");
				}
			}
			table_size = new_size_;
		}

		[[nodiscard]] value_type& _get_index(const coordinate_type& coords_)
		{
			if constexpr (NumDimensions_ == 1)
			{
				// Only 1 dimension, so only 1 major.
				return samples[coords_.template at<0>()];
			}
			else if constexpr (NumDimensions_ == 2)
			{
				if constexpr (MajorDimensionIndex_ == 0)
				{
					// X coords stored contiguously per row
					return samples[coords_.template at<1>()][coords_.template at<0>()];
				}
				else
				{
					// Y coords stored contiguously per column
					return samples[coords_.template at<0>()][coords_.template at<1>()];
				}
			}
			else if constexpr (NumDimensions_ == 3)
			{
				// We store in alphabetical order before the major (i.e. X-major will be stored YZX, Y-major stored XZY, Z-major stored XYZ)
				if constexpr (MajorDimensionIndex_ == 0)
				{
					return samples[coords_.template at<1>()][coords_.template at<2>()][coords_.template at<0>()];
				}
				else if constexpr (MajorDimensionIndex_ == 1)
				{
					return samples[coords_.template at<0>()][coords_.template at<2>()][coords_.template at<1>()];
				}
				else
				{
					return samples[coords_.template at<0>()][coords_.template at<1>()][coords_.template at<2>()];
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<std::size_t, MajorDimensionIndex_>, "Attempted to get an index of an EmuMath::FastNoiseTable with a prohibited number of dimensions.");
			}
		}
		[[nodiscard]] const value_type& _get_index(const coordinate_type& coords_) const
		{
			return const_cast<this_type*>(this)->_get_index(coords_);
		}
	};
}

#endif
