#ifndef EMU_MATH_NOISE_TMP_H_INC_
#define EMU_MATH_NOISE_TMP_H_INC_ 1

#include <type_traits>
#include <vector>

namespace EmuMath::TMP
{
	static constexpr std::size_t min_noise_dimensions = 1;
	static constexpr std::size_t max_noise_dimensions = 3;

	template<typename value_type>
	using noise_table_internal_layer = std::vector<value_type>;

	template<std::size_t Dimensions_>
	constexpr inline bool valid_noise_dimensions()
	{
		return Dimensions_ >= min_noise_dimensions && Dimensions_ <= max_noise_dimensions;
	}
	template<std::size_t Dimensions_>
	constexpr inline bool assert_valid_noise_dimensions()
	{
		if constexpr (Dimensions_ < min_noise_dimensions)
		{
			static_assert(false, "Invalid EmuMath noise dimensions: exceeded the maximum value, which is 1.");
			return false;
		}
		else if constexpr (Dimensions_ > max_noise_dimensions)
		{
			static_assert(false, "Invalid EmuMath noise dimensions: exceeded the maximum value, which is 3.");
			return false;
		}
		else
		{
			return true;
		}
	}

	template<typename T_>
	constexpr inline bool assert_valid_noise_table_sample_type()
	{
		if constexpr (std::is_floating_point_v<T_>)
		{
			return true;
		}
		else
		{
			static_assert(false, "Invalid EmuMath::NoiseTable sample type provided. Only floating-point types may be provided.");
			return false;
		}
	}

	template<std::size_t Dimensions_, class If1_, class If2_, class If3_>
	struct _noise_table_dimension_conditional
	{
		static_assert(assert_valid_noise_dimensions<Dimensions_>(), "Provided an invalid Dimensions_ value to _noise_table_dimension_conditional.");
		using type = std::conditional_t
		<
			Dimensions_ == 1,
			If1_,
			std::conditional_t
			<
				Dimensions_ == 2,
				If2_,
				std::conditional_t
				<
					Dimensions_ == 3,
					If3_,
					std::false_type
				>
			>
		>;
	};

	template<std::size_t TargetDimension_, std::size_t ActualDimensions_, typename value_type>
	struct _noise_table_access
	{
		static_assert(assert_valid_noise_dimensions<TargetDimension_>(), "Provided an invalid TargetDimension_ value t- _noise_table_access.");

		static_assert(assert_valid_noise_dimensions<ActualDimensions_>(), "Provided an invalid ActualDimensions_ value to _noise_table_access.");
		using type = value_type;
	};
	template<std::size_t ActualDimensions_, typename value_type>
	struct _noise_table_access<1, ActualDimensions_, value_type>
	{
		using type = typename _noise_table_dimension_conditional
		<
			ActualDimensions_,
			value_type,
			const noise_table_internal_layer<value_type>&,
			const noise_table_internal_layer<noise_table_internal_layer<value_type>>&
		>::type;
	};
	template<std::size_t ActualDimensions_, typename value_type>
	struct _noise_table_access<2, ActualDimensions_, value_type>
	{
		using type = typename _noise_table_dimension_conditional
		<
			ActualDimensions_,
			void,
			value_type,
			const noise_table_internal_layer<value_type>&
		>::type;
	};
	template<std::size_t ActualDimensions_, typename value_type>
	struct _noise_table_access<3, ActualDimensions_, value_type>
	{
		using type = typename _noise_table_dimension_conditional
		<
			ActualDimensions_,
			void,
			void,
			value_type
		>::type;
	};

	template<std::size_t NumDimensions_, typename value_type>
	using _full_noise_table_storage = typename EmuMath::TMP::_noise_table_dimension_conditional
	<
		NumDimensions_,
		EmuMath::TMP::noise_table_internal_layer<value_type>,
		EmuMath::TMP::noise_table_internal_layer<EmuMath::TMP::noise_table_internal_layer<value_type>>,
		EmuMath::TMP::noise_table_internal_layer<EmuMath::TMP::noise_table_internal_layer<EmuMath::TMP::noise_table_internal_layer<value_type>>>
	>::type;
}

#endif
