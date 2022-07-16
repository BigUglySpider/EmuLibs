#ifndef EMU_SIMD_HELPERS_TEMPLATE_SETS_H_INC_
#define EMU_SIMD_HELPERS_TEMPLATE_SETS_H_INC_ 1

#include "_underlying_template_helpers/_common_underlying_simd_template_helper_includes.h"
#include "_underlying_template_helpers/_simd_helpers_underlying_set.h"
#include "_simd_helpers_template_shuffles.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD
{
	/// <summary>
	/// <para> Sets the provided register type via the correct _set_ operation using the provided arguments, performing casts where necessary. </para>
	/// <para> A number of arguments equal to the number of elements within the desired register is required. </para>
	/// <para> 
	///		If the requested register is integral, ElementWidthIfInt_ will be used to determine how many bits each element should be interpreted as. 
	///		This in turn affects the expected number of arguments, which will be equal to (integral_register_size_in_bits / ElementWidthIfInt_). 
	/// </para>
	///	<para> ElementWidthIfInt_ will not be used if the output register is a floating-point register. </para>
	/// </summary>
	/// <param name="args_">Sequential arguments to pass to the desired register's _set_ function.</param>
	/// <returns>Register of the provided type, set via its _set_ function with the provided arguments.</returns>
	template<class Register_, std::size_t ElementWidthIfInt_ = 32, typename...Args_>
	[[nodiscard]] inline Register_ set(Args_&&...args_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			constexpr std::size_t num_args_ = sizeof...(Args_);
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_set_fp<Register_, false>(args_...);
			}
			else
			{
				return _underlying_simd_helpers::_set_int<Register_, ElementWidthIfInt_, false>(args_...);
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::set with an unsupported type as the passed Register_.");
		}
	}

	/// <summary>
	/// <para> Sets the provided register type via the correct _setr_ operation using the provided arguments, performing casts where necessary. </para>
	/// <para> A number of arguments equal to the number of elements within the desired register is required. </para>
	/// <para> 
	///		If the requested register is integral, ElementWidthIfInt_ will be used to determine how many bits each element should be interpreted as. 
	///		This in turn affects the expected number of arguments, which will be equal to (integral_register_size_in_bits / ElementWidthIfInt_). 
	/// </para>
	///	<para> ElementWidthIfInt_ will not be used if the output register is a floating-point register. </para>
	/// </summary>
	/// <param name="args_">Sequential arguments to pass to the desired register's _setr_ function.</param>
	/// <returns>Register of the provided type, set via its _setr_ function with the provided arguments.</returns>
	template<class Register_, std::size_t ElementWidthIfInt_ = 32, typename...Args_>
	[[nodiscard]] inline Register_ setr(Args_&&...args_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			constexpr std::size_t num_args_ = sizeof...(Args_);
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_set_fp<Register_, true>(args_...);
			}
			else
			{
				return _underlying_simd_helpers::_set_int<Register_, ElementWidthIfInt_, true>(args_...);
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::set with an unsupported type as the passed Register_.");
		}
	}

	/// <summary>
	/// <para> Sets a SIMD register with all values set to the one provided value, performing a cast if necessary. </para>
	/// <para> If the requested register is integral, ElementWidthIfInt_ will be used to determine how many bits each element should be interpreted as. </para>
	///	<para> ElementWidthIfInt_ will not be used if the output register is a floating-point register. </para>
	/// </summary>
	/// <param name="val_">Value to set all values within the output register to.</param>
	/// <returns>Register of the provided type, set via its _set1_ function with the provided val_.</returns>
	template<class Register_, std::size_t ElementWidthIfInt_ = 32, typename Val_>
	[[nodiscard]] inline Register_ set1(const Val_& val_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_set1<Register_, ElementWidthIfInt_>(val_);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::set1 with an unsupported type as the passed Register_.");
		}
	}

	/// <summary>
	/// <para> Sets a SIMD register with all bits set to 0, using the provided register's matching _setzero_ function. </para>
	/// </summary>
	/// <returns>Register of the provided type with all bits set to 0.</returns>
	template<class Register_>
	[[nodiscard]] inline Register_ setzero()
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_setzero<Register_>();
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::setzero with an unsupported type as the passed Register_.");
		}
	}

	/// <summary>
	/// <para> Sets a SIMD register with all bits set to 1. </para>
	/// </summary>
	/// <returns>Register of the provided type with all bits set to 1.</returns>
	template<class Register_>
	[[nodiscard]] inline Register_ setallone()
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using mask_generator_instance = _underlying_simd_helpers::_per_index_mask<register_type_uq, true>;
			if constexpr (EmuSIMD::_underlying_simd_helpers::_is_valid_per_index_mask_instance<mask_generator_instance>::value)
			{
				return mask_generator_instance::get();
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::setallone, but a successful mask generation could not be performed.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::setallone with an unsupported type as the passed Register_.");
		}
	}

	/// <summary> 
	/// <para> Sets a SIMD register via decrementing values within its relevant _set_ function, starting at StartingVal_. </para>
	/// <para> E.g. when setting EmuSIMD::f32x4 where StartingVal_ == 4, this will generate the equivalent of _mm_set_ps(4.0f, 3.0f, 2.0f, 1.0f). </para>
	/// </summary>
	/// <returns>SIMD register of the specified type with elements set via _set_ with a consistently decrementing value from StartingVal_.</returns>
	template<class Register_, std::int64_t StartingVal_, std::size_t ElementWidthIfInt_ = 32>
	[[nodiscard]] inline Register_ set_decrementing()
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_set_from_starting_value<register_type_uq, StartingVal_, EmuCore::do_subtract, false, ElementWidthIfInt_>();
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::set_decrementing with an unsupported type as the passed Register_.");
		}
	}
	/// <summary> 
	/// <para> Sets a SIMD register via decrementing values within its relevant _setr_ function, starting at StartingVal_. </para>
	/// <para> E.g. when setting EmuSIMD::f32x4 where StartingVal_ == 4, this will generate the equivalent of _mm_setr_ps(4.0f, 3.0f, 2.0f, 1.0f). </para>
	/// </summary>
	/// <returns>SIMD register of the specified type with elements set via _setr_ with a consistently decrementing value from StartingVal_.</returns>
	template<class Register_, std::int64_t StartingVal_, std::size_t ElementWidthIfInt_ = 32>
	[[nodiscard]] inline Register_ setr_decrementing()
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_set_from_starting_value<register_type_uq, StartingVal_, EmuCore::do_subtract, true, ElementWidthIfInt_>();
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::setr_decrementing with an unsupported type as the passed Register_.");
		}
	}

	/// <summary> 
	/// <para> Sets a SIMD register via incrementing values within its relevant _set_ function, starting at StartingVal_. </para>
	/// <para> E.g. when setting EmuSIMD::f32x4 where StartingVal_ == 4, this will generate the equivalent of _mm_set_ps(4.0f, 5.0f, 6.0f, 7.0f). </para>
	/// </summary>
	/// <returns>SIMD register of the specified type with elements set via _set_ with a consistently incrementing value from StartingVal_.</returns>
	template<class Register_, std::int64_t StartingVal_, std::size_t ElementWidthIfInt_ = 32>
	[[nodiscard]] inline Register_ set_incrementing()
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_set_from_starting_value<register_type_uq, StartingVal_, EmuCore::do_add, false, ElementWidthIfInt_>();
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::set_incrementing with an unsupported type as the passed Register_.");
		}
	}
	/// <summary> 
	/// <para> Sets a SIMD register via incrementing values within its relevant _setr_ function, starting at StartingVal_. </para>
	/// <para> E.g. when setting EmuSIMD::f32x4 where StartingVal_ == 4, this will generate the equivalent of _mm_setr_ps(4.0f, 5.0f, 6.0f, 7.0f). </para>
	/// </summary>
	/// <returns>SIMD register of the specified type with elements set via _setr_ with a consistently incrementing value from StartingVal_.</returns>
	template<class Register_, std::int64_t StartingVal_, std::size_t ElementWidthIfInt_ = 32>
	[[nodiscard]] inline Register_ setr_incrementing()
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_set_from_starting_value<register_type_uq, StartingVal_, EmuCore::do_add, true, ElementWidthIfInt_>();
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::setr_incrementing with an unsupported type as the passed Register_.");
		}
	}

	/// <summary>
	/// <para> Loads a SIMD register of the specified type from the provided data pointed to by p_to_load_. </para>
	/// <para> Bits of pointed-to data are loaded directly; conversions between different representations (such as IEEE-754 -> 2's complement) are NOT performed. </para>
	/// <para> 
	///		It is the caller's responsibility to ensure that the pointed-to location contains enough contiguously safe memory 
	///		(e.g. 256 bits for EmuSIMD::f32x8 registers) for the register to read from. 
	/// </para>
	/// </summary>
	/// <typeparam name="Register_">Type of SIMD register to create from loaded data.</typeparam>
	/// <typeparam name="In_">Type pointed to by the input pointer.</typeparam>
	/// <param name="p_to_load_">Constant pointer to data to be loaded into the output register.</param>
	/// <returns>SIMD register of the specified type, with data initialised from loading the data pointed to by the provided p_to_load_ pointer.</returns>
	template<class Register_, typename In_>
	[[nodiscard]] inline Register_ load(const In_* p_to_load_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_load<Register_>(p_to_load_);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::load with an unsupported type as the passed Register_.");
		}
	}

	template<std::size_t Index_, std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] constexpr inline Register_ set_all_to_index(Register_ in_)
	{
		using register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_uq>)
		{
			constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<Register_, PerElementWidthIfInt_>;
			if constexpr (Index_ < num_elements)
			{
				if constexpr (std::is_same_v<register_uq, EmuSIMD::f32x4>)
				{
					return EmuSIMD::shuffle<Index_, Index_, Index_, Index_>(in_);
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::f32x8>)
				{
					constexpr std::size_t lane_index = Index_ >= 4 ? 1 : 0;
					constexpr std::size_t mask = (lane_index << 4) | lane_index;
					register_uq matching_lanes = _mm256_permute2f128_ps(in_, in_, mask);
					matching_lanes = _mm256_permute2f128_ps(matching_lanes, matching_lanes, mask);
					return EmuSIMD::shuffle<Index_, Index_, Index_, Index_>(matching_lanes);
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::f32x16>)
				{
					return EmuSIMD::set1<Register_, PerElementWidthIfInt_>(EmuSIMD::get_index<Index_, float, PerElementWidthIfInt_>(in_));
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::f64x2>)
				{
					return EmuSIMD::shuffle<Index_, Index_>(in_);
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::f64x4>)
				{
					constexpr std::size_t lane_index = Index_ >= 2 ? 1 : 0;
					constexpr std::size_t mask = (lane_index << 4) | lane_index;
					register_uq matching_lanes = _mm256_permute2f128_pd(in_, in_, mask);
					return EmuSIMD::shuffle<Index_, Index_>(matching_lanes);
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::f64x8>)
				{
					return EmuSIMD::set1<Register_, PerElementWidthIfInt_>(EmuSIMD::get_index<Index_, double, PerElementWidthIfInt_>(in_));
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::i128_generic>)
				{
					if constexpr (PerElementWidthIfInt_ == 8)
					{
						return EmuSIMD::shuffle<Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_>(in_);
					}
					else if constexpr (PerElementWidthIfInt_ == 16)
					{
						return EmuSIMD::shuffle<Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_>(in_);
					}
					else if constexpr (PerElementWidthIfInt_ == 32)
					{
						return EmuSIMD::shuffle<Index_, Index_, Index_, Index_>(in_);
					}
					else if constexpr (PerElementWidthIfInt_ == 64)
					{
						return EmuSIMD::shuffle<Index_, Index_>(in_);
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
							"Attempted to set all elements in a generic 128-bit integral SIMD register to match a specific index via EmuSIMD::set_all_to_index, but the provided PerElementWidthIfInt_ is invalid. Valid values are: 8, 16, 32, 64."
						);
					}
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::i256_generic>)
				{
					constexpr std::size_t half_elements = num_elements / 2;
					constexpr std::size_t lane_index = Index_ >= half_elements ? 1 : 0;
					constexpr std::size_t mask = (lane_index << 4) | lane_index;
					register_uq matching_lanes = _mm256_permute2f128_si256(in_, in_, mask);

					if constexpr (PerElementWidthIfInt_ == 8)
					{
						return EmuSIMD::shuffle<Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_>
						(
							matching_lanes
						);
					}
					else if constexpr (PerElementWidthIfInt_ == 16)
					{
						return EmuSIMD::shuffle<Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_>(matching_lanes);
					}
					else if constexpr (PerElementWidthIfInt_ == 32)
					{
						return EmuSIMD::shuffle<Index_, Index_, Index_, Index_>(matching_lanes);
					}
					else if constexpr (PerElementWidthIfInt_ == 64)
					{
						return EmuSIMD::shuffle<Index_, Index_>(matching_lanes);
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
							"Attempted to set all elements in a generic 256-bit integral SIMD register to match a specific index via EmuSIMD::set_all_to_index, but the provided PerElementWidthIfInt_ is invalid. Valid values are: 8, 16, 32, 64."
						);
					}
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::i512_generic>)
				{
					if constexpr (PerElementWidthIfInt_ == 8 || PerElementWidthIfInt_ == 16 || PerElementWidthIfInt_ == 32 || PerElementWidthIfInt_ == 64)
					{
						using sized_int = EmuCore::TMP::int_of_size_t<PerElementWidthIfInt_ / 8>;
						return EmuSIMD::set1<Register_, PerElementWidthIfInt_>(EmuSIMD::get_index<Index_, sized_int, PerElementWidthIfInt_>(in_));
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
							"Attempted to set all elements in a generic 512-bit integral SIMD register to match a specific index via EmuSIMD::set_all_to_index, but the provided PerElementWidthIfInt_ is invalid. Valid values are: 8, 16, 32, 64."
						);
					}
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::i8x16> || std::is_same_v<register_uq, EmuSIMD::u8x16>)
				{
					return EmuSIMD::shuffle<Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_>(in_);
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::i16x8> || std::is_same_v<register_uq, EmuSIMD::u16x8>)
				{
					return EmuSIMD::shuffle<Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_>(in_);
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::i32x4> || std::is_same_v<register_uq, EmuSIMD::u32x4>)
				{
					return EmuSIMD::shuffle<Index_, Index_, Index_, Index_>(in_);
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::i64x2> || std::is_same_v<register_uq, EmuSIMD::u64x2>)
				{
					return EmuSIMD::shuffle<Index_, Index_>(in_);
				}
				else if constexpr (EmuCore::TMP::is_any_same_v<register_uq, EmuSIMD::i8x32, EmuSIMD::i16x16, EmuSIMD::i32x8, EmuSIMD::i64x4, EmuSIMD::u8x32, EmuSIMD::u16x16, EmuSIMD::u32x8, EmuSIMD::u64x4>)
				{
					constexpr std::size_t half_elements = num_elements / 2;
					constexpr std::size_t lane_index = Index_ >= half_elements ? 1 : 0;
					constexpr std::size_t mask = (lane_index << 4) | lane_index;
					register_uq matching_lanes = _mm256_permute2f128_si256(in_, in_, mask);;

					if constexpr (std::is_same_v<register_uq, EmuSIMD::i8x32> || std::is_same_v<register_uq, EmuSIMD::u8x32>)
					{
						return EmuSIMD::shuffle<Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_>
						(
							matching_lanes
						);

					}
					else if constexpr (std::is_same_v<register_uq, EmuSIMD::i16x16> || std::is_same_v<register_uq, EmuSIMD::u16x16>)
					{
						return EmuSIMD::shuffle<Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_>(matching_lanes);
					}
					else if constexpr (std::is_same_v<register_uq, EmuSIMD::i32x8> || std::is_same_v<register_uq, EmuSIMD::u32x8>)
					{
						return EmuSIMD::shuffle<Index_, Index_, Index_, Index_>(matching_lanes);
					}
					else if constexpr(std::is_same_v<register_uq, EmuSIMD::i64x4> || std::is_same_v<register_uq, EmuSIMD::u64x4>)
					{
						return EmuSIMD::shuffle<Index_, Index_>(matching_lanes);
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<Register_>(),
							"Internal EmuSIMD error @EmuSIMD::set_all_to_index, with register_uq recognised as one of: i8x32, i16x16, i32x8, i64x4, u8x32, u16x16, u32x8, or u64x4 in initial check, but not in further checks."
						);
					}
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::i8x64> || std::is_same_v<register_uq, EmuSIMD::u8x64>)
				{
					return EmuSIMD::set1<Register_, 8>(EmuSIMD::get_index<Index_, std::int8_t, 8>(in_));
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::i16x32> || std::is_same_v<register_uq, EmuSIMD::u16x32>)
				{
					return EmuSIMD::set1<Register_, 16>(EmuSIMD::get_index<Index_, std::int16_t, 16>(in_));
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::i32x16> || std::is_same_v<register_uq, EmuSIMD::u32x16>)
				{
					return EmuSIMD::set1<Register_, 32>(EmuSIMD::get_index<Index_, std::int32_t, 32>(in_));
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::i8x64> || std::is_same_v<register_uq, EmuSIMD::u8x64>)
				{
					return EmuSIMD::set1<Register_, 64>(EmuSIMD::get_index<Index_, std::int64_t, 64>(in_));
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Register_>(),
						"Attempted to perform EmuSIMD::set_all_to_index, but the provided Register_ type is not supported for this operation."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Index_>(),
					"Attempted to perform EmuSIMD::set_all_to_index with an index outside of the range of the passed SIMD register."
				);
			}

		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Register_>(),
				"Attempted to perform EmuSIMD::set_all_to_index with a passed Register_ type which is not recognised as a SIMD register."
			);
		}
	}
}

#endif
