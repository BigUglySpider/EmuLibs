#ifndef EMU_SIMD_UNDERLYING_FORWARD_TEMPLATE_SETS_H_INC_
#define EMU_SIMD_UNDERLYING_FORWARD_TEMPLATE_SETS_H_INC_ 1

#include "_forward_tmp.h"

// DECLARES:
// EmuSIMD::
// --- set
// --- setr
// --- set1
// --- setzero
// --- setallone
// --- set_decrementing
// --- setr_decrementing
// --- set_incrementing
// --- setr_incrementing

namespace EmuSIMD
{
	/// <summary>
	/// <para> Sets the provided register type via the correct _set_ operation using the provided arguments, performing casts where necessary. </para>
	/// <para> A number of arguments equal to the number of elements within the desired register is required. </para>
	/// <para> 
	///		If the requested register is generic integral register, ElementWidthIfGenericInt_ will be used to determine how many bits each element should be interpreted as. 
	///		This in turn affects the expected number of arguments, which will be equal to (integral_register_size_in_bits / ElementWidthIfGenericInt_). 
	/// </para>
	///	<para> ElementWidthIfGenericInt_ is unused if not requesting a generic integral register. </para>
	/// </summary>
	/// <param name="args_">Sequential arguments to pass to the desired register's _set_ function.</param>
	/// <returns>Register of the provided type, set via its _set_ function with the provided arguments.</returns>
	template<EmuConcepts::KnownSIMD SIMDRegister_, std::size_t ElementWidthIfGenericInt_ = 32, typename...SetArgs_>
	[[nodiscard]] inline auto set(SetArgs_&&...set_args_) noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type;

	/// <summary>
	/// <para> Sets the provided register type via the correct _setr_ operation using the provided arguments, performing casts where necessary. </para>
	/// <para> A number of arguments equal to the number of elements within the desired register is required. </para>
	/// <para> 
	///		If the requested register is a generic integral register, ElementWidthIfGenericInt_ will be used to determine how many bits each element should be interpreted as. 
	///		This in turn affects the expected number of arguments, which will be equal to (integral_register_size_in_bits / ElementWidthIfGenericInt_). 
	/// </para>
	///	<para> ElementWidthIfGenericInt_ is unused if not requesting a generic integral register. </para>
	/// </summary>
	/// <param name="args_">Sequential arguments to pass to the desired register's _setr_ function.</param>
	/// <returns>Register of the provided type, set via its _setr_ function with the provided arguments.</returns>
	template<EmuConcepts::KnownSIMD SIMDRegister_, std::size_t ElementWidthIfGenericInt_ = 32, typename...SetArgs_>
	[[nodiscard]] inline auto setr(SetArgs_&&...set_args_) noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type;

	/// <summary>
	/// <para> Sets a SIMD register with all values set to the one provided value, performing a cast if necessary. </para>
	/// <para> If the requested register is a generic integral register, ElementWidthIfGenericInt_ will be used to determine how many bits each element should be interpreted as. </para>
	///	<para> ElementWidthIfGenericInt_ is unused if not requesting a generic integral register. </para>
	/// </summary>
	/// <param name="val_">Value to set all values within the output register to.</param>
	/// <returns>Register of the provided type, set via its _set1_ function with the provided val_.</returns>
	template<EmuConcepts::KnownSIMD SIMDRegister_, std::size_t ElementWidthIfGenericInt_ = 32, typename Val_>
	[[nodiscard]] inline auto set1(const Val_& val_) noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type;

	/// <summary>
	/// <para> Sets a SIMD register with all bits set to 0, using the provided register's matching _setzero_ function. </para>
	/// </summary>
	/// <returns>Register of the provided type with all bits set to 0.</returns>
	template<EmuConcepts::KnownSIMD SIMDRegister_>
	[[nodiscard]] inline auto setzero() noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type;

	/// <summary>
	/// <para> Sets a SIMD register with all bits set to 1. </para>
	/// </summary>
	/// <returns>Register of the provided type with all bits set to 1.</returns>
	template<EmuConcepts::KnownSIMD SIMDRegister_>
	[[nodiscard]] inline auto setallone() noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type;

	/// <summary> 
	/// <para> Sets a SIMD register via decrementing values within its relevant _set_ function, starting at StartingVal_. </para>
	/// <para> E.g. when setting EmuSIMD::f32x4 where StartingVal_ == 4, this will generate the equivalent of EmuSIMD::set_f32x4(4.0f, 3.0f, 2.0f, 1.0f). </para>
	/// </summary>
	/// <returns>SIMD register of the specified type with elements set via _set_ with a consistently decrementing value from StartingVal_.</returns>
	template<EmuConcepts::KnownSIMD SIMDRegister_, std::int64_t StartingVal_, std::size_t ElementWidthIfGenericInt_ = 32>
	[[nodiscard]] inline auto set_decrementing() noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type;

	/// <summary> 
	/// <para> Sets a SIMD register via decrementing values within its relevant _setr_ function, starting at StartingVal_. </para>
	/// <para> E.g. when setting EmuSIMD::f32x4 where StartingVal_ == 4, this will generate the equivalent of EmuSIMD::setr_f32x4(4.0f, 3.0f, 2.0f, 1.0f). </para>
	/// </summary>
	/// <returns>SIMD register of the specified type with elements set via _setr_ with a consistently decrementing value from StartingVal_.</returns>
	template<EmuConcepts::KnownSIMD SIMDRegister_, std::int64_t StartingVal_, std::size_t ElementWidthIfGenericInt_ = 32>
	[[nodiscard]] inline auto setr_decrementing() noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type;

	/// <summary> 
	/// <para> Sets a SIMD register via incrementing values within its relevant _set_ function, starting at StartingVal_. </para>
	/// <para> E.g. when setting EmuSIMD::f32x4 where StartingVal_ == 4, this will generate the equivalent of EmuSIMD::set_f32x4(4.0f, 5.0f, 6.0f, 7.0f). </para>
	/// </summary>
	/// <returns>SIMD register of the specified type with elements set via _set_ with a consistently incrementing value from StartingVal_.</returns>
	template<EmuConcepts::KnownSIMD SIMDRegister_, std::int64_t StartingVal_, std::size_t ElementWidthIfGenericInt_ = 32>
	[[nodiscard]] inline auto set_incrementing() noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type;
	
	/// <summary> 
	/// <para> Sets a SIMD register via incrementing values within its relevant _setr_ function, starting at StartingVal_. </para>
	/// <para> E.g. when setting EmuSIMD::f32x4 where StartingVal_ == 4, this will generate the equivalent of EmuSIMD::setr_f32x4(4.0f, 5.0f, 6.0f, 7.0f). </para>
	/// </summary>
	/// <returns>SIMD register of the specified type with elements set via _setr_ with a consistently incrementing value from StartingVal_.</returns>
	template<EmuConcepts::KnownSIMD SIMDRegister_, std::int64_t StartingVal_, std::size_t ElementWidthIfGenericInt_ = 32>
	[[nodiscard]] inline auto setr_incrementing() noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type;

	/// <summary>
	/// <para> Loads a SIMD register of the specified type from the provided data pointed to by p_to_load_. </para>
	/// <para> Bits of pointed-to data are loaded directly; conversions between different representations (such as IEEE-754 -> 2's complement) are NOT performed. </para>
	/// <para> 
	///		It is the caller's responsibility to ensure that the pointed-to location contains enough contiguously safe memory 
	///		(e.g. 256 bits for EmuSIMD::f32x8 registers) for the register to read from. 
	/// </para>
	/// </summary>
	/// <param name="p_to_load_">Constant pointer to data to be loaded into the output register.</param>
	/// <returns>SIMD register of the specified type, with data initialised from loading the data pointed to by the provided p_to_load_ pointer.</returns>
	template<EmuConcepts::KnownSIMD SIMDRegister_, typename In_>
	[[nodiscard]] inline auto load(const In_* p_to_load_)
		-> typename std::remove_cvref<SIMDRegister_>::type;

	/// <summary>
	/// <para> Outputs a new SIMD register of the input type with all elements set to match the element at the specified index within the input SIMD register. </para>
	/// <para> If the input register is a generic integral register, ElementWidthIfGenericInt_ will be used to determine how many bits each element should be interpreted as. </para>
	///	<para> ElementWidthIfGenericInt_ is unused if not setting a generic integral register. </para>
	/// </summary>
	/// <param name="in_">Register to copy the specified index of.</param>
	/// <returns>SIMD Register of the input type with data set to match the element at the specified index of the input SIMD register.</returns>
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_ = 32, EmuConcepts::KnownSIMD SIMDRegister_>
	[[nodiscard]] inline auto set_all_to_index(SIMDRegister_&& in_) noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type;

	template<EmuConcepts::KnownSIMD SIMDRegister_, std::size_t PerElementWidthIfGenericInt_ = 32, bool OddSign_ = false>
	[[nodiscard]] inline auto alternating_sign_mask() noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type;

	template<EmuConcepts::KnownSIMD SIMDRegister_, std::size_t PerElementWidthIfGenericInt_ = 32, bool OddSign_ = false>
	[[nodiscard]] constexpr inline auto alternating_sign_mask_reverse() noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type;

	template<std::size_t PerElementWidthIfGenericInt_, EmuConcepts::KnownSIMD SIMDRegister_, bool...SignAtIndex_>
	[[nodiscard]] constexpr inline auto sign_mask() noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type;

	template<std::size_t PerElementWidthIfInt_, EmuConcepts::KnownSIMD SIMDRegister_, bool...SignAtIndex_>
	[[nodiscard]] constexpr inline auto sign_mask_reverse() noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type;
}

#endif
