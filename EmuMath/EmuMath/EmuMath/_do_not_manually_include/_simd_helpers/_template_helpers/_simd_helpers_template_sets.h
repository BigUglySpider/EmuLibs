#ifndef EMU_MATH_SIMD_HELPERS_TEMPLATE_SETS_H_INC_
#define EMU_MATH_SIMD_HELPERS_TEMPLATE_SETS_H_INC_ 1

#include "_underlying_template_helpers/_common_underlying_simd_template_helper_includes.h"
#include "_underlying_template_helpers/_simd_helpers_underlying_set.h"

namespace EmuMath::SIMD
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
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			constexpr std::size_t num_args_ = sizeof...(Args_);
			if constexpr (EmuMath::SIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_set_fp<Register_>(args_...);
			}
			else
			{
				return _underlying_simd_helpers::_set_int<Register_, ElementWidthIfInt_>(args_...);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::set with an unsupported type as the passed Register_.");
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
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_set1<Register_, ElementWidthIfInt_>(val_);
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::set1 with an unsupported type as the passed Register_.");
		}
	}

	/// <summary>
	/// <para> Sets a SIMD register with all bits set to 0, using the provided register's matching _setzero_ function. </para>
	/// </summary>
	/// <returns>Register of the provided type with all bits set to 0.</returns>
	template<class Register_>
	[[nodiscard]] inline Register_ setzero()
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_setzero<Register_>();
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::setzero with an unsupported type as the passed Register_.");
		}
	}

	/// <summary>
	/// <para> Sets a SIMD register with all bits set to 1. </para>
	/// </summary>
	/// <returns>Register of the provided type with all bits set to 1.</returns>
	template<class Register_>
	[[nodiscard]] inline Register_ setallone()
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using mask_generator_instance = _underlying_simd_helpers::_per_index_mask<register_type_uq, true>;
			if constexpr (EmuMath::SIMD::_underlying_simd_helpers::_is_valid_per_index_mask_instance<mask_generator_instance>::value)
			{
				return mask_generator_instance::get();
			}
			else
			{
				static_assert(false, "Attempted to perform EmuMath::SIMD::setallone, but a successful mask generation could not be performed.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::setallone with an unsupported type as the passed Register_.");
		}
	}

	/// <summary> 
	/// <para> Sets a SIMD register via decrementing values within its relevant _set_ function, starting at StartingVal_. </para>
	/// <para> E.g. when setting __m128 where StartingVal_ == 4, this will generate the equivalent of _mm_set_ps(4.0f, 3.0f, 2.0f, 1.0f). </para>
	/// </summary>
	/// <returns>SIMD register of the specified type with elements set via _set_ with a consistently decrementing value from StartingVal_.</returns>
	template<class Register_, std::int64_t StartingVal_, std::size_t ElementWidthIfInt_ = 32>
	[[nodiscard]] inline Register_ set_decrementing()
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_set_from_starting_value<register_type_uq, StartingVal_, EmuCore::do_subtract, false, ElementWidthIfInt_>();
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::set_decrementing with an unsupported type as the passed Register_.");
		}
	}
	/// <summary> 
	/// <para> Sets a SIMD register via decrementing values within its relevant _setr_ function, starting at StartingVal_. </para>
	/// <para> E.g. when setting __m128 where StartingVal_ == 4, this will generate the equivalent of _mm_setr_ps(4.0f, 3.0f, 2.0f, 1.0f). </para>
	/// </summary>
	/// <returns>SIMD register of the specified type with elements set via _setr_ with a consistently decrementing value from StartingVal_.</returns>
	template<class Register_, std::int64_t StartingVal_, std::size_t ElementWidthIfInt_ = 32>
	[[nodiscard]] inline Register_ setr_decrementing()
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_set_from_starting_value<register_type_uq, StartingVal_, EmuCore::do_subtract, true, ElementWidthIfInt_>();
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::setr_decrementing with an unsupported type as the passed Register_.");
		}
	}

	/// <summary> 
	/// <para> Sets a SIMD register via incrementing values within its relevant _set_ function, starting at StartingVal_. </para>
	/// <para> E.g. when setting __m128 where StartingVal_ == 4, this will generate the equivalent of _mm_set_ps(4.0f, 5.0f, 6.0f, 7.0f). </para>
	/// </summary>
	/// <returns>SIMD register of the specified type with elements set via _set_ with a consistently incrementing value from StartingVal_.</returns>
	template<class Register_, std::int64_t StartingVal_, std::size_t ElementWidthIfInt_ = 32>
	[[nodiscard]] inline Register_ set_incrementing()
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_set_from_starting_value<register_type_uq, StartingVal_, EmuCore::do_add, false, ElementWidthIfInt_>();
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::set_incrementing with an unsupported type as the passed Register_.");
		}
	}
	/// <summary> 
	/// <para> Sets a SIMD register via incrementing values within its relevant _setr_ function, starting at StartingVal_. </para>
	/// <para> E.g. when setting __m128 where StartingVal_ == 4, this will generate the equivalent of _mm_setr_ps(4.0f, 5.0f, 6.0f, 7.0f). </para>
	/// </summary>
	/// <returns>SIMD register of the specified type with elements set via _setr_ with a consistently incrementing value from StartingVal_.</returns>
	template<class Register_, std::int64_t StartingVal_, std::size_t ElementWidthIfInt_ = 32>
	[[nodiscard]] inline Register_ setr_incrementing()
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_set_from_starting_value<register_type_uq, StartingVal_, EmuCore::do_add, true, ElementWidthIfInt_>();
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::setr_incrementing with an unsupported type as the passed Register_.");
		}
	}
}

#endif
