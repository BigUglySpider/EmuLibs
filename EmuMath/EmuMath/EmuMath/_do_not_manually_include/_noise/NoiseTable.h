#ifndef EMU_MATH_NOISE_TABLE_H_INC_
#define EMU_MATH_NOISE_TABLE_H_INC_ 1

#include "NoiseFunctors.h"
#include "NoiseSampleProcessors.h"
#include "NoiseTableOptions.h"
#include "NoiseTMP.h"
#include "../../../EmuCore/TMPHelpers/TypeComparators.h"
#include "../../../EmuCore/TMPHelpers/TypeConvertors.h"
#include "../../../EmuCore/TMPHelpers/Values.h"
#include <ostream>
#include <sstream>
#include <vector>

namespace EmuMath
{
	/// <summary> Class used to generate and store X-dimensional noise with customisable parameters. </summary>
	template<std::size_t Dimensions_, typename SampleTypeFP_>
	class NoiseTable
	{
	public:
		static_assert(EmuMath::TMP::assert_valid_noise_dimensions<Dimensions_>(), "Provided invalid Dimensions_ value to instantiate an EmuMath::NoiseTable template.");
		static_assert(EmuMath::TMP::assert_valid_noise_table_sample_type<SampleTypeFP_>(), "Provided an invalid SampleTypeFP_ to instantiate an EmuMath::NoiseTable template.");

		/// <summary> Number of dimensions covered by this table. </summary>
		static constexpr std::size_t num_dimensions = Dimensions_;
		/// <summary> Type used to store individual samples within this table. </summary>
		using value_type = SampleTypeFP_;
		using this_type = NoiseTable<num_dimensions, value_type>;
		using options_type = EmuMath::NoiseTableOptions<num_dimensions, value_type>;

	private:
		/// <summary>table_storage will be a Dimensions_-dimensional vector of value_types.</summary>
		using table_storage = EmuMath::TMP::_full_noise_table_storage<num_dimensions, value_type>;

	public:
		/// <summary> Type returned when accessing this table via a single scalar index. </summary>
		using return_single_index = typename EmuMath::TMP::_noise_table_access<1, num_dimensions, value_type>::type;
		/// <summary> Type returned when accessing this table via 2 scalar indices. If void, 2-scalar index accesses are invalid on this table. </summary>
		using return_double_index = typename EmuMath::TMP::_noise_table_access<2, num_dimensions, value_type>::type;
		/// <summary> Type returned when accessing this table via 3 scalar indices. If void, 3-scalar index accesses are invalid on this table. </summary>
		using return_triple_index = typename EmuMath::TMP::_noise_table_access<3, num_dimensions, value_type>::type;

		/// <summary> Default constructor which creates an empty noise table. </summary>
		NoiseTable() : table_data(), table_size()
		{
		}
		/// <summary> Copy constructor which mimics the passed table without modifying it. </summary>
		/// <param name="to_copy_">Noise table to copy the data of.</param>
		NoiseTable(const this_type& to_copy_) : table_data(to_copy_.table_data), table_size(to_copy_.table_size)
		{
		}
		/// <summary> Move constructor which transfers data from one table to this. The moved-from table is left in a default-constructed state. </summary>
		/// <param name="to_move_">Modifiable noise table to move into this newly constructed table, which will additionally be left in a default-constructed state.</param>
		NoiseTable(this_type&& to_move_) noexcept : NoiseTable()
		{
			table_data.swap(to_move_.table_data);
			table_size = to_move_.table_size;
			to_move_.table_size = EmuMath::NewVector<num_dimensions, std::size_t>();
		}

#pragma region ASSIGNMENT
		this_type& operator=(const this_type& to_copy_)
		{
			table_data = to_copy_.table_data;
			table_size = to_copy_.table_size;
			return *this;
		}
		this_type& operator=(this_type&& to_move_) noexcept
		{
			swap(to_move_);
			return *this;
		}
#pragma endregion

#pragma region RANDOM_ACCESS
		/// <summary>
		/// <para> Accesses the first layer of this noise table. </para>
		/// <para> If this table is 1-dimensional, this will provide a copy of the provided index. Otherwise, it will provide constant access to the first layer. </para>
		/// </summary>
		/// <param name="index_x_">Index to use for accessing the x-layer of this table.</param>
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
		/// <param name="index_x_">Index to use for accessing the x-layer of this table.</param>
		/// <param name="index_y_">Index to use for accessing the y-layer of this table.</param>
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
		/// <param name="index_x_">Index to use for accessing the x-layer of this table.</param>
		/// <param name="index_y_">Index to use for accessing the y-layer of this table.</param>
		/// <param name="index_z_">Index to use for accessing the z-layer of this table.</param>
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
		[[nodiscard]] inline value_type at(const EmuMath::NewVector<Size_, std::size_t>& indices_) const
		{
			if constexpr (num_dimensions == 1)
			{
				return at(indices_.at<0>());
			}
			else if constexpr (num_dimensions == 2)
			{
				return at(indices_.at<0>(), EmuMath::Helpers::vector_get_theoretical<1>(indices_));
			}
			else if constexpr (num_dimensions == 3)
			{
				return at(indices_.at<0>(), EmuMath::Helpers::vector_get_theoretical<1>(indices_), EmuMath::Helpers::vector_get_theoretical<2>(indices_));
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<std::size_t, Size_>, "Attempted to retrieve an index of an impossibly-dimensioned EmuMath::NoiseTable.");
			}
		}

		/// <summary>
		/// <para> Accesses the first layer of this noise table. </para>
		/// <para> If this table is 1-dimensional, this will provide a copy of the provided index. Otherwise, it will provide constant access to the first layer. </para>
		/// <para> Shorthand for `at` with the same argument. </para>
		/// </summary>
		/// <param name="index_x_">Index to use for accessing the x-layer of this table.</param>
		/// <returns>Copy of the sample at the provided index if 1D; otherwise, a constant reference to the first layer of the table.</returns>
		[[nodiscard]] inline return_single_index operator()(std::size_t index_x_) const
		{
			return at(index_x_);
		}
		/// <summary>
		/// <para> Accesses the second layer of this noise table. </para>
		/// <para> If this table is 2-dimensional, this will provide a copy of the provided index. If it is greater, it will provide constant access to the second layer. </para>
		/// <para> This method is not available for 1-dimensional tables. </para>
		/// <para> Shorthand for `at` with the same arguments. </para>
		/// </summary>
		/// <param name="index_x_">Index to use for accessing the x-layer of this table.</param>
		/// <param name="index_y_">Index to use for accessing the y-layer of this table.</param>
		/// <returns>Copy of the sample at the provided index if 2D; if greater than 2D, a constant reference to the second layer of the table; otherwise void.</returns>
		template<typename RequiresAtLeast2D_ = std::enable_if_t<num_dimensions >= 2>>
		[[nodiscard]] inline return_double_index operator()(std::size_t index_x_, std::size_t index_y_) const
		{
			if constexpr (num_dimensions >= 2)
			{
				return at(index_x_, index_y_);
			}
		}
		/// <summary>
		/// <para> Accesses the third layer of this noise table. </para>
		/// <para> If this table is 3-dimensional, this will provide a copy of the provided index. </para>
		/// <para> This method is not available for 1- and 2-dimensional tables. </para>
		/// <para> Shorthand for `at` with the same arguments. </para>
		/// </summary>
		/// <param name="index_x_">Index to use for accessing the x-layer of this table.</param>
		/// <param name="index_y_">Index to use for accessing the y-layer of this table.</param>
		/// <param name="index_z_">Index to use for accessing the z-layer of this table.</param>
		/// <returns>Copy of the sample at the provided index if 3D; otherwise void.</returns>
		template<typename RequiresAtLeast3D_ = std::enable_if_t<num_dimensions >= 3>>
		[[nodiscard]] inline return_triple_index operator()(std::size_t index_x_, std::size_t index_y_, std::size_t index_z_) const
		{
			if constexpr (num_dimensions >= 3)
			{
				return at(index_x_, index_y_, index_z_);
			}
		}
		/// <summary>
		/// <para> Returns a copy of the value at the index specified by the respective elements of the passed vector. </para>
		/// <para>
		///		For elements the vector does not contain, its theoretical value (typically 0) will be used instead. 
		///		To access a layer with only the vector's indices, use the form of this function taking scalar index arguments instead.
		/// </para>
		/// <para> Shorthand for `at` with the same argument. </para>
		/// </summary>
		/// <param name="indices_">EmuMath vector containing respective indices of the sample of this table to access.</param>
		/// <returns>Copy of this table's sample at the specified indices.</returns>
		template<std::size_t Size_>
		[[nodiscard]] inline value_type operator()(const EmuMath::NewVector<Size_, std::size_t>& indices_) const
		{
			return at(indices_);
		}

		/// <summary>
		/// <para> Accesses the first layer of this noise table. </para>
		/// <para> If this table is 1-dimensional, this will provide a copy of the provided index. Otherwise, it will provide constant access to the first layer. </para>
		/// <para> Shorthand for `at` with the same argument. </para>
		/// </summary>
		/// <param name="index_x_">Index to use for accessing the x-layer of this table.</param>
		/// <returns>Copy of the sample at the provided index if 1D; otherwise, a constant reference to the first layer of the table.</returns>
		[[nodiscard]] inline return_single_index operator[](std::size_t index_x_) const
		{
			return at(index_x_);
		}
		/// <summary>
		/// <para> Returns a copy of the value at the index specified by the respective elements of the passed vector. </para>
		/// <para>
		///		For elements the vector does not contain, its theoretical value (typically 0) will be used instead. 
		///		To access a layer with only the vector's indices, use the form of this function taking scalar index arguments instead.
		/// </para>
		/// <para> Shorthand for `at` with the same argument. </para>
		/// </summary>
		/// <param name="indices_">EmuMath vector containing respective indices of the sample of this table to access.</param>
		/// <returns>Copy of this table's sample at the specified indices.</returns>
		template<std::size_t Size_>
		[[nodiscard]] inline value_type operator[](const EmuMath::NewVector<Size_, std::size_t>& indices_) const
		{
			return at(indices_);
		}

		std::ostream& AppendToStream(std::ostream& str_) const
		{
			return _do_stream_append<false, std::ostream>(str_);
		}
		std::wostream& AppendToStream(std::wostream& wide_str_) const
		{
			return _do_stream_append<true, std::wostream>(wide_str_);
		}

#pragma region STREAM_APPEND_FORMATTING
		template<bool IsWide_, class Stream_>
		static inline void _stream_append_open_brace_with_space(Stream_& str_)
		{
			if constexpr (IsWide_)
			{
				str_ << L"{ ";
			}
			else
			{
				str_ << "{ ";
			}
		}
		template<bool IsWide_, class Stream_>
		static inline void _stream_append_space_and_close_brace(Stream_& str_)
		{
			if constexpr (IsWide_)
			{
				str_ << L" }";
			}
			else
			{
				str_ << " }";
			}
		}
		template<bool IsWide_, class Stream_>
		static inline void _stream_append_empty_object(Stream_& str_)
		{
			if constexpr (IsWide_)
			{
				str_ << L"{ }";
			}
			else
			{
				str_ << "{ }";
			}
		}
		template<bool IsWide_, class Stream_>
		static inline void _stream_append_z_end(Stream_& str_)
		{
			if constexpr (IsWide_)
			{
				str_ << L"\n---\n";
			}
			else
			{
				str_ << "\n---\n";
			}
		}
		template<bool IsWide_, class Stream_>
		static inline void _stream_append_new_line(Stream_& str_)
		{
			if constexpr (IsWide_)
			{
				str_ << L"\n";
			}
			else
			{
				str_ << "\n";
			}
		}
		template<bool IsWide_, class Stream_>
		static inline void _stream_append_per_element_separation(Stream_& str_)
		{
			if constexpr (IsWide_)
			{
				str_ << L", ";
			}
			else
			{
				str_ << ", ";
			}
		}
#pragma endregion

		template<bool IsWide_, class Stream_>
		inline Stream_& _do_stream_append(Stream_& str_) const
		{
			if constexpr (num_dimensions == 1)
			{
				std::size_t size_x_ = table_size.at<0>();
				if (size_x_ != 0)
				{
					_stream_append_open_brace_with_space<IsWide_>(str_);
					str_ << at(0);
					for (std::size_t x = 1; x < size_x_; ++x)
					{
						_stream_append_per_element_separation<IsWide_>(str_);
						str_ << at(x);
					}
					_stream_append_space_and_close_brace<IsWide_>(str_);
				}
				else
				{
					_stream_append_empty_object<IsWide_>(str_);
				}
			}
			else if constexpr (num_dimensions == 2)
			{
				std::size_t size_x_ = table_size.at<0>();
				std::size_t size_y_ = table_size.at<1>();
				if (size_x_ != 0 && size_y_ != 0)
				{
					for (std::size_t y = 0; y < size_y_; ++y)
					{
						_stream_append_open_brace_with_space<IsWide_>(str_);
						str_ << at(0, y);
						for (std::size_t x = 1; x < size_x_; ++x)
						{
							_stream_append_per_element_separation<IsWide_>(str_);
							str_ << at(x, y);
						}
						_stream_append_space_and_close_brace<IsWide_>(str_);
						if ((y + 1) < size_y_)
						{
							_stream_append_new_line<IsWide_>(str_);
						}
					}
				}
				else
				{
					_stream_append_empty_object<IsWide_>(str_);
				}
			}
			else if constexpr (num_dimensions == 3)
			{
				std::size_t size_x_ = table_size.at<0>();
				std::size_t size_y_ = table_size.at<1>();
				std::size_t size_z_ = table_size.at<2>();
				if (size_x_ != 0 && size_y_ != 0 && size_z_ != 0)
				{
					for (std::size_t z = 0; z < size_z_; ++z)
					{
						for (std::size_t y = 0; y < size_y_; ++y)
						{
							_stream_append_open_brace_with_space<IsWide_>(str_);
							str_ << at(0, y, z);
							for (std::size_t x = 1; x < size_x_; ++x)
							{
								_stream_append_per_element_separation<IsWide_>(str_);
								str_ << at(x, y, z);
							}
							_stream_append_space_and_close_brace<IsWide_>(str_);
							if ((y + 1) < size_y_)
							{
								_stream_append_new_line<IsWide_>(str_);
							}
						}
						if ((z + 1) < size_z_)
						{
							_stream_append_z_end<IsWide_>(str_);
						}
					}
				}
				else
				{
					_stream_append_empty_object<IsWide_>(str_);
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Stream_>(), "Stream append of EmuMath::NoiseTable not available for any dimensions other than: 1, 2, 3.");
			}
			return str_;
		}
#pragma endregion

#pragma region STL_MIMICS
		/// <summary> Returns a vector showing this table's size in each of its stored layers. </summary>
		/// <returns>Vector with this table's size in each respective dimension.</returns>
		[[nodiscard]] inline EmuMath::NewVector<Dimensions_, std::size_t> size() const
		{
			return table_size;
		}
		/// <summary> Returns the size of this table on the specified layer, where 0 is the x layer, 1 the y layer, etc. </summary>
		/// <returns>Size of this table in the specified dimensional Layer_.</returns>
		template<std::size_t Layer_>
		[[nodiscard]] inline std::size_t size() const
		{
			if constexpr (Layer_ < num_dimensions)
			{
				return table_size.at<Layer_>();
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<std::size_t, Layer_>(), "Attempted to get the size of an EmuMath NoiseTable in a specific dimension, but the provided dimension index exceeded the table's dimensions.");
			}
		}

		/// <summary> Swaps the data of this table with that of the passed table. </summary>
		/// <param name="to_swap_with_">Table of equal dimensions with which to swap data.</param>
		inline void swap(this_type& to_swap_with_)
		{
			table_data.swap(to_swap_with_.table_data);
			decltype(table_size) temp_(table_size);
			table_size = to_swap_with_.table_size;
			to_swap_with_.table_size = temp_;
		}

		/// <summary> Clears all data within this table. Heap deallocation is not guaranteed; for such behaviour, use Release instead. </summary>
		inline void clear()
		{
			table_data.clear();
		}

		/// <summary> Shrinks all layers within this table to fit their content. </summary>
		inline void shrink_to_fit()
		{
			table_data.shrink_to_fit();
			if constexpr (num_dimensions >= 2)
			{
				for (std::size_t x = 0, end_x_ = table_size.at<0>(); x < end_x_; ++x)
				{
					auto& layer_x_ = table_data[x];
					layer_x_.shrink_to_fit();
					if constexpr (num_dimensions >= 3)
					{
						for (std::size_t y = 0, end_y_ = table_data.at<1>(); y < end_y_; ++y)
						{
							auto& layer_y_ = layer_x_[y];
							layer_y_.shrink_to_fit();
						}
					}
				}
			}
		}
#pragma endregion

		/// <summary> Clears this table, and provides a guarantee to deallocate the used heap memory (unlike clear). </summary>
		inline void Release()
		{
			table_storage().swap(table_data);
		}

#pragma region MODIFYING_FUNCS
		/// <summary>
		/// <para> Normalises this noise table's values to the range 0:1, as though they are currently stored in the range min_:max_. </para>
		/// <para> To track the min_ and max_ of a table when it is generating to normalise straight after, consider using the noise_sample_processor_with_analytics functor. </para>
		/// </summary>
		/// <param name="min_">Low-bound value for perceived range to normalise</param>
		/// <param name="max_">High-bound value for perceived range to normalise</param>
		inline void NormaliseForRange(value_type min_, value_type max_)
		{
			if (min_ > max_)
			{
				NormaliseForRange(max_, min_);
			}
			else
			{
				value_type max_minus_min_ = max_ - min_;
				if (EmuCore::do_cmp_near_equal<value_type>()(max_minus_min_, value_type(0)))
				{
					// In this scenario, max and min are very likely the same (and if not, different only by epsilon which is likely a fp rounding error)
					_set_all(max_);
				}
				else
				{
					_do_normalise(value_type(1) / max_minus_min_, min_);
				}
			}
		}
#pragma endregion

#pragma region GENERATION
		/// <summary>
		/// <para> Resizes and fills this table with noise samples created via the passed options. </para>
		/// <para> The returned boolean indicates success. If this function returns false, the generation operation did not fully complete. </para>
		/// </summary>
		/// <typeparam name="SampleProcessor_">Functor to process noise samples further after generation. The default argument for this makes no change to samples.</typeparam>
		/// <param name="options_">Options to create this table's samples via.</param>
		/// <param name="SampleProcessor_">Functor to process final samples via. May be omitted to use the default construction of this functor.</param>
		/// <returns>Boolean indicating the success of this generation operation; true only when generation is not cancelled.</returns>
		template<EmuMath::NoiseType NoiseType_, class SampleProcessor_ = EmuMath::Functors::noise_sample_processor_default>
		inline bool GenerateNoise(const options_type& options_, SampleProcessor_ sample_processor_)
		{
			using underlying_noise_gen_functor = EmuMath::noise_gen_functor<num_dimensions, NoiseType_, value_type>;
			if (_valid_resolution(options_.table_resolution))
			{
				_do_resize(options_.table_resolution);
				if (options_.use_fractal_noise)
				{
					using FractalGenerator_ = EmuMath::Functors::fractal_noise_wrapper<underlying_noise_gen_functor, value_type>;
					_do_generation<FractalGenerator_, SampleProcessor_&>
					(
						FractalGenerator_(options_.freq, std::move(options_.permutation_info.MakePermutations()), options_.fractal_noise_info),
						sample_processor_,
						options_.start_point,
						options_.MakeStep()
					);
				}
				else
				{
					using Generator_ = EmuMath::Functors::no_fractal_noise_wrapper<underlying_noise_gen_functor, value_type>;
					_do_generation<Generator_, SampleProcessor_&>
					(
						Generator_(options_.freq, std::move(options_.permutation_info.MakePermutations())),
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
		template<EmuMath::NoiseType NoiseType_, class SampleProcessor_ = EmuMath::Functors::noise_sample_processor_default>
		inline bool GenerateNoise(const options_type& options_)
		{
			SampleProcessor_ sample_processor_ = SampleProcessor_();
			return GenerateNoise<NoiseType_, SampleProcessor_&>(options_, sample_processor_);
		}

		/// <summary>
		/// <para> Helper to construct options for generating noise for this table with the provided arguments. </para>
		/// <para> Provided arguments are the respective arguments (including order) for the full custom constructor of this table's options. </para>
		/// </summary>
		[[nodiscard]] static inline options_type MakeOptions
		(
			const EmuMath::NewVector<num_dimensions, std::size_t>& table_resolution_,
			const EmuMath::NewVector<num_dimensions, value_type>& start_point_,
			const EmuMath::NewVector<num_dimensions, value_type>& end_point_or_step_,
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
#pragma endregion

	private:
		table_storage table_data;
		EmuMath::NewVector<num_dimensions, std::size_t> table_size;

		static constexpr inline bool _valid_resolution(const EmuMath::NewVector<num_dimensions, std::size_t>& res_)
		{
			return !res_.CmpAnyEqual(std::size_t(0));
		}

		inline void _do_resize(const EmuMath::NewVector<num_dimensions, std::size_t>& res_)
		{
			// No need to resize if we're the same
			// --- Not particularly necessary for 1D, but avoids a potentially large construction that won't even be used for greater dimensions
			if (res_.CmpAnyNotEqual(table_size))
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
		}

		template<typename Generator_, typename SampleProcessor_>
		inline void _do_generation
		(
			Generator_ generator_,
			SampleProcessor_ sample_processor_,
			EmuMath::NewVector<num_dimensions, value_type> start_,
			EmuMath::NewVector<num_dimensions, value_type> step_
		)
		{
			EmuMath::NewVector<num_dimensions, value_type> point_(start_);
			if constexpr (num_dimensions == 1)
			{
				for (std::size_t x_ = 0, end_x_ = table_data.size(); x_ < end_x_; ++x_)
				{
					table_data[x_] = sample_processor_(generator_(point_));
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
						layer_x_[y_] = sample_processor_(generator_(point_));
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
							layer_y_[z_] = sample_processor_(generator_(point_));
							point_.at<2>() += step_.at<2>();
						}
						point_.at<1>() += step_.at<1>();
					}
					point_.at<0>() += step_.at<0>();
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Generator_>(), "Attempted to generate an impossibly-dimensioned EmuMath::NoiseTable.");
			}
		}

		inline void _set_all(value_type val_)
		{
			if constexpr (num_dimensions == 1)
			{
				for (std::size_t x_ = 0, x_end_ = size<0>(); x_ < x_end_; ++x_)
				{
					table_data[x_] = val_;
				}
			}
			else if constexpr (num_dimensions == 2)
			{
				for (std::size_t x_ = 0, x_end_ = size<0>(); x_ < x_end_; ++x_)
				{
					auto& layer_x_ = table_data[x_];
					for (std::size_t y_ = 0, y_end_ = size<1>(); y_ < y_end_; ++y_)
					{
						layer_x_[y_] = val_;
					}
				}
			}
			else if constexpr (num_dimensions == 3)
			{
				for (std::size_t x_ = 0, x_end_ = size<0>(); x_ < x_end_; ++x_)
				{
					auto& layer_x_ = table_data[x_];
					for (std::size_t y_ = 0, y_end_ = size<1>(); y_ < y_end_; ++y_)
					{
						auto& layer_y_ = layer_x_[y_];
						for (std::size_t z_ = 0, z_end_ = size<2>(); z_ < z_end_; ++z_)
						{
							layer_y_[z_] = val_;
						}
					}
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<std::size_t, num_dimensions>(), "NoiseTable::_multiply_all not implemented for instance dimensions.");
			}
		}

		inline void _do_normalise(value_type reciprocal_multiplier_, value_type min_)
		{
			if constexpr (num_dimensions == 1)
			{
				for (std::size_t x_ = 0, x_end_ = size<0>(); x_ < x_end_; ++x_)
				{
					auto& val_ = table_data[x_];
					val_ = (val_ - min_) * reciprocal_multiplier_;
				}
			}
			else if constexpr (num_dimensions == 2)
			{
				for (std::size_t x_ = 0, x_end_ = size<0>(); x_ < x_end_; ++x_)
				{
					auto& layer_x_ = table_data[x_];
					for (std::size_t y_ = 0, y_end_ = size<1>(); y_ < y_end_; ++y_)
					{
						auto& val_ = layer_x_[y_];
						val_ = (val_ - min_) * reciprocal_multiplier_;
					}
				}
			}
			else if constexpr (num_dimensions == 3)
			{
				for (std::size_t x_ = 0, x_end_ = size<0>(); x_ < x_end_; ++x_)
				{
					auto& layer_x_ = table_data[x_];
					for (std::size_t y_ = 0, y_end_ = size<1>(); y_ < y_end_; ++y_)
					{
						auto& layer_y_ = layer_x_[y_];
						for (std::size_t z_ = 0, z_end_ = size<2>(); z_ < z_end_; ++z_)
						{
							auto& val_ = layer_y_[z_];
							val_ = (val_ - min_) * reciprocal_multiplier_;
						}
					}
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<std::size_t, num_dimensions>(), "NoiseTable::_set_all not implemented for instance dimensions.");
			}
		}
	};
}

template<std::size_t num_dimensions, typename FP_>
std::ostream& operator<<(std::ostream& str_, const EmuMath::NoiseTable<num_dimensions, FP_>& noise_table_)
{
	noise_table_.AppendToStream(str_);
	return str_;
}

template<std::size_t num_dimensions, typename FP_>
std::wostream& operator<<(std::wostream& str_, const EmuMath::NoiseTable<num_dimensions, FP_>& noise_table_)
{
	noise_table_.AppendToStream(str_);
	return str_;
}

#endif
