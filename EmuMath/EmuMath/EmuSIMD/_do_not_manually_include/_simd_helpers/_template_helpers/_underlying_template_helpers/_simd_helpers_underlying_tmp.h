#ifndef EMU_SIMD_UNDERLYING_SIMD_HELPERS_TMP_H_INC_
#define EMU_SIMD_UNDERLYING_SIMD_HELPERS_TMP_H_INC_ 1

#include "_generic_funcs/_forward_declarations/_all_forward_declarations.h"
#include "_simd_helpers_underlying_aliases.h"
#include "_generic_funcs/_f32x4.h"
#include "_generic_funcs/_f32x8.h"
#include "_generic_funcs/_f32x16.h"
#include "_generic_funcs/_f64x2.h"
#include "_generic_funcs/_f64x4.h"
#include "_generic_funcs/_f64x8.h"
#include "_generic_funcs/_i8x16.h"
#include "_generic_funcs/_i8x32.h"
#include "_generic_funcs/_i8x64.h"
#include "_generic_funcs/_i16x8.h"
#include "_generic_funcs/_i16x16.h"
#include "_generic_funcs/_i16x32.h"
#include "_generic_funcs/_i32x4.h"
#include "_generic_funcs/_i32x8.h"
#include "_generic_funcs/_i32x16.h"
#include "_generic_funcs/_i64x2.h"
#include "_generic_funcs/_i64x4.h"
#include "_generic_funcs/_i64x8.h"
#include "_generic_funcs/_u8x16.h"
#include "_generic_funcs/_u8x32.h"
#include "_generic_funcs/_u8x64.h"
#include "_generic_funcs/_u16x8.h"
#include "_generic_funcs/_u16x16.h"
#include "_generic_funcs/_u16x32.h"
#include "_generic_funcs/_u32x4.h"
#include "_generic_funcs/_u32x8.h"
#include "_generic_funcs/_u32x16.h"
#include "_generic_funcs/_u64x2.h"
#include "_generic_funcs/_u64x4.h"
#include "_generic_funcs/_u64x8.h"
#include "../../../../../EmuCore/ArithmeticHelpers/BitHelpers.h"
#include "../../../../../EmuCore/TMPHelpers/TypeComparators.h"
#include "../../../../../EmuCore/TMPHelpers/TypeConvertors.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"
#include <cstdlib>
#include <stdexcept>

namespace EmuSIMD::TMP
{
#pragma region SIMD_REGISTER_WIDTH
	template<>
	struct simd_register_width<EmuSIMD::f32x4>
	{
		static constexpr std::size_t value = 128;
	};
	template<>
	struct simd_register_width<EmuSIMD::f64x2>
	{
		static constexpr std::size_t value = 128;
	};
	template<>
	struct simd_register_width<EmuSIMD::f32x8>
	{
		static constexpr std::size_t value = 256;
	};
	template<>
	struct simd_register_width<EmuSIMD::f64x4>
	{
		static constexpr std::size_t value = 256;
	};
	template<>
	struct simd_register_width<EmuSIMD::f32x16>
	{
		static constexpr std::size_t value = 512;
	};
	template<>
	struct simd_register_width<EmuSIMD::f64x8>
	{
		static constexpr std::size_t value = 512;
	};
#if EMU_SIMD_USE_GENERIC_INT_REGISTERS
	template<>
	struct simd_register_width<EmuSIMD::i128_generic>
	{
		static constexpr std::size_t value = 128;
	};

	template<>
	struct simd_register_width<EmuSIMD::i256_generic>
	{
		static constexpr std::size_t value = 256;
	};

	template<>
	struct simd_register_width<EmuSIMD::i512_generic>
	{
		static constexpr std::size_t value = 512;
	};
#else
	template<>
	struct simd_register_width<EmuSIMD::i8x16>
	{
		static constexpr std::size_t value = 128;
	};
	template<>
	struct simd_register_width<EmuSIMD::i16x8>
	{
		static constexpr std::size_t value = 128;
	};
	template<>
	struct simd_register_width<EmuSIMD::i32x4>
	{
		static constexpr std::size_t value = 128;
	};
	template<>
	struct simd_register_width<EmuSIMD::i64x2>
	{
		static constexpr std::size_t value = 128;
	};

	template<>
	struct simd_register_width<EmuSIMD::i8x32>
	{
		static constexpr std::size_t value = 256;
	};
	template<>
	struct simd_register_width<EmuSIMD::i16x16>
	{
		static constexpr std::size_t value = 256;
	};
	template<>
	struct simd_register_width<EmuSIMD::i32x8>
	{
		static constexpr std::size_t value = 256;
	};
	template<>
	struct simd_register_width<EmuSIMD::i64x4>
	{
		static constexpr std::size_t value = 256;
	};

	template<>
	struct simd_register_width<EmuSIMD::i8x64>
	{
		static constexpr std::size_t value = 512;
	};
	template<>
	struct simd_register_width<EmuSIMD::i16x32>
	{
		static constexpr std::size_t value = 512;
	};
	template<>
	struct simd_register_width<EmuSIMD::i32x16>
	{
		static constexpr std::size_t value = 512;
	};
	template<>
	struct simd_register_width<EmuSIMD::i64x8>
	{
		static constexpr std::size_t value = 512;
	};

	template<>
	struct simd_register_width<EmuSIMD::u8x16>
	{
		static constexpr std::size_t value = 128;
	};
	template<>
	struct simd_register_width<EmuSIMD::u16x8>
	{
		static constexpr std::size_t value = 128;
	};
	template<>
	struct simd_register_width<EmuSIMD::u32x4>
	{
		static constexpr std::size_t value = 128;
	};
	template<>
	struct simd_register_width<EmuSIMD::u64x2>
	{
		static constexpr std::size_t value = 128;
	};

	template<>
	struct simd_register_width<EmuSIMD::u8x32>
	{
		static constexpr std::size_t value = 256;
	};
	template<>
	struct simd_register_width<EmuSIMD::u16x16>
	{
		static constexpr std::size_t value = 256;
	};
	template<>
	struct simd_register_width<EmuSIMD::u32x8>
	{
		static constexpr std::size_t value = 256;
	};
	template<>
	struct simd_register_width<EmuSIMD::u64x4>
	{
		static constexpr std::size_t value = 256;
	};

	template<>
	struct simd_register_width<EmuSIMD::u8x64>
	{
		static constexpr std::size_t value = 512;
	};
	template<>
	struct simd_register_width<EmuSIMD::u16x32>
	{
		static constexpr std::size_t value = 512;
	};
	template<>
	struct simd_register_width<EmuSIMD::u32x16>
	{
		static constexpr std::size_t value = 512;
	};
	template<>
	struct simd_register_width<EmuSIMD::u64x8>
	{
		static constexpr std::size_t value = 512;
	};
#endif
#pragma endregion

#pragma region IS_INTEGRAL_SIMD_REGISTER
	template<>
	struct is_integral_simd_register<EmuSIMD::f32x4>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::f64x2>
	{
		static constexpr bool value = false;
	};

	template<>
	struct is_integral_simd_register<EmuSIMD::f32x8>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::f64x4>
	{
		static constexpr bool value = false;
	};

	template<>
	struct is_integral_simd_register<EmuSIMD::f32x16>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::f64x8>
	{
		static constexpr bool value = false;
	};

#if EMU_SIMD_USE_GENERIC_INT_REGISTERS
	template<>
	struct is_integral_simd_register<EmuSIMD::i128_generic>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::i256_generic>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::i512_generic>
	{
		static constexpr bool value = true;
	};
#else
	template<>
	struct is_integral_simd_register<EmuSIMD::i8x16>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::i16x8>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::i32x4>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::i64x2>
	{
		static constexpr bool value = true;
	};

	template<>
	struct is_integral_simd_register<EmuSIMD::i8x32>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::i16x16>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::i32x8>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::i64x4>
	{
		static constexpr bool value = true;
	};

	template<>
	struct is_integral_simd_register<EmuSIMD::i8x64>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::i16x32>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::i32x16>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::i64x8>
	{
		static constexpr bool value = true;
	};

	template<>
	struct is_integral_simd_register<EmuSIMD::u8x16>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::u16x8>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::u32x4>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::u64x2>
	{
		static constexpr bool value = true;
	};

	template<>
	struct is_integral_simd_register<EmuSIMD::u8x32>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::u16x16>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::u32x8>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::u64x4>
	{
		static constexpr bool value = true;
	};

	template<>
	struct is_integral_simd_register<EmuSIMD::u8x64>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::u16x32>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::u32x16>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_integral_simd_register<EmuSIMD::u64x8>
	{
		static constexpr bool value = true;
	};
#endif
#pragma endregion

#pragma region IS_GENERIC_INTEGER_SIMD_REGISTER
	template<class Register_>
	struct is_generic_integer_simd_register
	{
	private:
		using register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;

	public:
		static constexpr bool value =
		(
			!std::is_void_v<register_uq> &&
			(std::is_same_v<register_uq, EmuSIMD::i128_generic> || std::is_same_v<register_uq, EmuSIMD::i256_generic> || std::is_same_v<register_uq, EmuSIMD::i512_generic>)
		);
	};
	template<class Register_>
	static constexpr bool is_generic_integer_simd_register_v = is_generic_integer_simd_register<Register_>::value;
#pragma endregion

#pragma region IS_FLOATING_POINT_SIMD_REGISTER
	template<>
	struct is_floating_point_simd_register<EmuSIMD::f32x4>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::f64x2>
	{
		static constexpr bool value = true;
	};

	template<>
	struct is_floating_point_simd_register<EmuSIMD::f32x8>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::f64x4>
	{
		static constexpr bool value = true;
	};

	template<>
	struct is_floating_point_simd_register<EmuSIMD::f32x16>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::f64x8>
	{
		static constexpr bool value = true;
	};

#if EMU_SIMD_USE_GENERIC_INT_REGISTERS
	template<>
	struct is_floating_point_simd_register<EmuSIMD::i128_generic>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::i256_generic>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::i512_generic>
	{
		static constexpr bool value = false;
	};
#else
	template<>
	struct is_floating_point_simd_register<EmuSIMD::i8x16>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::i16x8>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::i32x4>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::i64x2>
	{
		static constexpr bool value = false;
	};

	template<>
	struct is_floating_point_simd_register<EmuSIMD::i8x32>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::i16x16>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::i32x8>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::i64x4>
	{
		static constexpr bool value = false;
	};

	template<>
	struct is_floating_point_simd_register<EmuSIMD::i8x64>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::i16x32>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::i32x16>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::i64x8>
	{
		static constexpr bool value = false;
	};

	template<>
	struct is_floating_point_simd_register<EmuSIMD::u8x16>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::u16x8>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::u32x4>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::u64x2>
	{
		static constexpr bool value = false;
	};

	template<>
	struct is_floating_point_simd_register<EmuSIMD::u8x32>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::u16x16>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::u32x8>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::u64x4>
	{
		static constexpr bool value = false;
	};

	template<>
	struct is_floating_point_simd_register<EmuSIMD::u8x64>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::u16x32>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::u32x16>
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_floating_point_simd_register<EmuSIMD::u64x8>
	{
		static constexpr bool value = false;
	};
#endif
#pragma endregion

#pragma region FLOATING_POINT_REGISTER_ELEMENT_COUNT
	template<>
	struct floating_point_register_element_count<EmuSIMD::f32x4>
	{
		static constexpr std::size_t value = 4;
	};
	template<>
	struct floating_point_register_element_count<EmuSIMD::f64x2>
	{
		static constexpr std::size_t value = 2;
	};
	template<>
	struct floating_point_register_element_count<EmuSIMD::f32x8>
	{
		static constexpr std::size_t value = 8;
	};
	template<>
	struct floating_point_register_element_count<EmuSIMD::f64x4>
	{
		static constexpr std::size_t value = 4;
	};
	template<>
	struct floating_point_register_element_count<EmuSIMD::f32x16>
	{
		static constexpr std::size_t value = 16;
	};
	template<>
	struct floating_point_register_element_count<EmuSIMD::f64x8>
	{
		static constexpr std::size_t value = 8;
	};
#pragma endregion

#pragma region FLOATING_POINT_REGISTER_ELEMENT_WIDTH
	template<>
	struct floating_point_register_element_width<EmuSIMD::f32x4>
	{
		static constexpr std::size_t value = 32;
	};
	template<>
	struct floating_point_register_element_width<EmuSIMD::f32x8>
	{
		static constexpr std::size_t value = 32;
	};
	template<>
	struct floating_point_register_element_width<EmuSIMD::f32x16>
	{
		static constexpr std::size_t value = 32;
	};
	template<>
	struct floating_point_register_element_width<EmuSIMD::f64x2>
	{
		static constexpr std::size_t value = 64;
	};
	template<>
	struct floating_point_register_element_width<EmuSIMD::f64x4>
	{
		static constexpr std::size_t value = 64;
	};
	template<>
	struct floating_point_register_element_width<EmuSIMD::f64x8>
	{
		static constexpr std::size_t value = 64;
	};
#pragma endregion

#pragma region REGISTER_ELEMENT_COUNT
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::f32x4, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 4;
	};
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::f64x2, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 2;
	};

	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::f32x8, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 8;
	};
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::f64x4, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 4;
	};

	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::f32x16, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 16;
	};
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::f64x8, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 8;
	};

#if EMU_SIMD_USE_GENERIC_INT_REGISTERS
	template<>
	struct register_element_count<EmuSIMD::i128_generic, 8>
	{
		static constexpr std::size_t value = 16;
	};
	template<>
	struct register_element_count<EmuSIMD::i128_generic, 16>
	{
		static constexpr std::size_t value = 8;
	};
	template<>
	struct register_element_count<EmuSIMD::i128_generic, 32>
	{
		static constexpr std::size_t value = 4;
	};
	template<>
	struct register_element_count<EmuSIMD::i128_generic, 64>
	{
		static constexpr std::size_t value = 2;
	};

	template<>
	struct register_element_count<EmuSIMD::i256_generic, 8>
	{
		static constexpr std::size_t value = 32;
	};
	template<>
	struct register_element_count<EmuSIMD::i256_generic, 16>
	{
		static constexpr std::size_t value = 16;
	};
	template<>
	struct register_element_count<EmuSIMD::i256_generic, 32>
	{
		static constexpr std::size_t value = 8;
	};
	template<>
	struct register_element_count<EmuSIMD::i256_generic, 64>
	{
		static constexpr std::size_t value = 4;
	};

	template<>
	struct register_element_count<EmuSIMD::i512_generic, 8>
	{
		static constexpr std::size_t value = 64;
	};
	template<>
	struct register_element_count<EmuSIMD::i512_generic, 16>
	{
		static constexpr std::size_t value = 32;
	};
	template<>
	struct register_element_count<EmuSIMD::i512_generic, 32>
	{
		static constexpr std::size_t value = 16;
	};
	template<>
	struct register_element_count<EmuSIMD::i512_generic, 64>
	{
		static constexpr std::size_t value = 8;
	};
#else
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::i8x16, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 16;
	};
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::i16x8, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 8;
	};
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::i32x4, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 4;
	};
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::i64x2, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 2;
	};

	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::i8x32, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 32;
	};
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::i16x16, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 16;
	};
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::i32x8, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 8;
	};
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::i64x4, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 4;
	};
	
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::i8x64, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 64;
	};
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::i16x32, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 32;
	};
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::i32x16, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 16;
	};
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::i64x8, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 8;
	};

	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::u8x16, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 16;
	};
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::u16x8, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 8;
	};
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::u32x4, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 4;
	};
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::u64x2, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 2;
	};

	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::u8x32, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 32;
	};
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::u16x16, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 16;
	};
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::u32x8, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 8;
	};
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::u64x4, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 4;
	};

	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::u8x64, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 64;
	};
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::u16x32, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 32;
	};
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::u32x16, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 16;
	};
	template<std::size_t PerElementWidthIfGenericInt_>
	struct register_element_count<EmuSIMD::u64x8, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t value = 8;
	};
#endif
#pragma endregion

#pragma region VALID_REGISTER_INDEX
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::f32x4, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = std::size_t(3);
		static constexpr bool value = Index_ <= max_index;
	};
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::f32x8, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = std::size_t(7);
		static constexpr bool value = Index_ <= max_index;
	};
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::f32x16, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = std::size_t(15);
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::f64x2, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = std::size_t(1);
		static constexpr bool value = Index_ <= max_index;
	};
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::f64x4, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = std::size_t(3);
		static constexpr bool value = Index_ <= max_index;
	};
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::f64x8, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = std::size_t(7);
		static constexpr bool value = Index_ <= max_index;
	};

#if EMU_SIMD_USE_GENERIC_INT_REGISTERS
	template<std::size_t Index_>
	struct valid_register_index<EmuSIMD::i128_generic, Index_, 8>
	{
		static constexpr std::size_t max_index = 15;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_>
	struct valid_register_index<EmuSIMD::i128_generic, Index_, 16>
	{
		static constexpr std::size_t max_index = 7;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_>
	struct valid_register_index<EmuSIMD::i128_generic, Index_, 32>
	{
		static constexpr std::size_t max_index = 3;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_>
	struct valid_register_index<EmuSIMD::i128_generic, Index_, 64>
	{
		static constexpr std::size_t max_index = 1;
		static constexpr bool value = Index_ <= max_index;
	};
	
	template<std::size_t Index_>
	struct valid_register_index<EmuSIMD::i256_generic, Index_, 8>
	{
		static constexpr std::size_t max_index = 31;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_>
	struct valid_register_index<EmuSIMD::i256_generic, Index_, 16>
	{
		static constexpr std::size_t max_index = 15;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_>
	struct valid_register_index<EmuSIMD::i256_generic, Index_, 32>
	{
		static constexpr std::size_t max_index = 7;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_>
	struct valid_register_index<EmuSIMD::i256_generic, Index_, 64>
	{
		static constexpr std::size_t max_index = 3;
		static constexpr bool value = Index_ <= max_index;
	};
	
	template<std::size_t Index_>
	struct valid_register_index<EmuSIMD::i512_generic, Index_, 8>
	{
		static constexpr std::size_t max_index = 63;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_>
	struct valid_register_index<EmuSIMD::i512_generic, Index_, 16>
	{
		static constexpr std::size_t max_index = 31;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_>
	struct valid_register_index<EmuSIMD::i512_generic, Index_, 32>
	{
		static constexpr std::size_t max_index = 15;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_>
	struct valid_register_index<EmuSIMD::i512_generic, Index_, 64>
	{
		static constexpr std::size_t max_index = 7;
		static constexpr bool value = Index_ <= max_index;
	};
#else
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::i8x16, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 15;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::i16x8, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 7;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::i32x4, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 3;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::i64x2, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 1;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::i8x32, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 31;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::i16x16, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 15;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::i32x8, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 7;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::i64x4, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 3;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::i8x64, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 63;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::i16x32, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 31;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::i32x16, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 15;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::i64x8, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 7;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::u8x16, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 15;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::u16x8, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 7;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::u32x4, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 3;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::u64x2, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 1;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::u8x32, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 31;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::u16x16, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 15;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::u32x8, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 7;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::u64x4, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 3;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::u8x64, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 63;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::u16x32, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 31;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::u32x16, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 15;
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct valid_register_index<EmuSIMD::u64x8, Index_, PerElementWidthIfGenericInt_>
	{
		static constexpr std::size_t max_index = 7;
		static constexpr bool value = Index_ <= max_index;
	};
#endif
#pragma endregion

#pragma region HALF_WIDTH
	template<>
	struct half_width<EmuSIMD::f32x4>
	{
		using type = void;
	};
	template<>
	struct half_width<EmuSIMD::f32x8>
	{
		using type = EmuSIMD::f32x4;
	};
	template<>
	struct half_width<EmuSIMD::f32x16>
	{
		using type = EmuSIMD::f32x8;
	};

	template<>
	struct half_width<EmuSIMD::f64x2>
	{
		using type = void;
	};
	template<>
	struct half_width<EmuSIMD::f64x4>
	{
		using type = EmuSIMD::f64x2;
	};
	template<>
	struct half_width<EmuSIMD::f64x8>
	{
		using type = EmuSIMD::f64x4;
	};

#if EMU_SIMD_USE_GENERIC_INT_REGISTERS
	template<>
	struct half_width<EmuSIMD::i128_generic>
	{
		using type = void;
	};
	template<>
	struct half_width<EmuSIMD::i256_generic>
	{
		using type = EmuSIMD::i128_generic;
	};
	template<>
	struct half_width<EmuSIMD::i512_generic>
	{
		using type = EmuSIMD::i256_generic;
	};
#else
	template<>
	struct half_width<EmuSIMD::i8x16>
	{
		using type = void;
	};
	template<>
	struct half_width<EmuSIMD::i8x32>
	{
		using type = EmuSIMD::i8x16;
	};
	template<>
	struct half_width<EmuSIMD::i8x64>
	{
		using type = EmuSIMD::i8x32;
	};

	template<>
	struct half_width<EmuSIMD::i16x8>
	{
		using type = void;
	};
	template<>
	struct half_width<EmuSIMD::i16x16>
	{
		using type = EmuSIMD::i16x8;
	};
	template<>
	struct half_width<EmuSIMD::i16x32>
	{
		using type = EmuSIMD::i16x16;
	};

	template<>
	struct half_width<EmuSIMD::i32x4>
	{
		using type = void;
	};
	template<>
	struct half_width<EmuSIMD::i32x8>
	{
		using type = EmuSIMD::i32x4;
	};
	template<>
	struct half_width<EmuSIMD::i32x16>
	{
		using type = EmuSIMD::i32x8;
	};

	template<>
	struct half_width<EmuSIMD::i64x2>
	{
		using type = void;
	};
	template<>
	struct half_width<EmuSIMD::i64x4>
	{
		using type = EmuSIMD::i64x2;
	};
	template<>
	struct half_width<EmuSIMD::i64x8>
	{
		using type = EmuSIMD::i64x4;
	};

	template<>
	struct half_width<EmuSIMD::u8x16>
	{
		using type = void;
	};
	template<>
	struct half_width<EmuSIMD::u8x32>
	{
		using type = EmuSIMD::u8x16;
	};
	template<>
	struct half_width<EmuSIMD::u8x64>
	{
		using type = EmuSIMD::u8x32;
	};

	template<>
	struct half_width<EmuSIMD::u16x8>
	{
		using type = void;
	};
	template<>
	struct half_width<EmuSIMD::u16x16>
	{
		using type = EmuSIMD::u16x8;
	};
	template<>
	struct half_width<EmuSIMD::u16x32>
	{
		using type = EmuSIMD::u16x16;
	};

	template<>
	struct half_width<EmuSIMD::u32x4>
	{
		using type = void;
	};
	template<>
	struct half_width<EmuSIMD::u32x8>
	{
		using type = EmuSIMD::u32x4;
	};
	template<>
	struct half_width<EmuSIMD::u32x16>
	{
		using type = EmuSIMD::u32x8;
	};

	template<>
	struct half_width<EmuSIMD::u64x2>
	{
		using type = void;
	};
	template<>
	struct half_width<EmuSIMD::u64x4>
	{
		using type = EmuSIMD::u64x2;
	};
	template<>
	struct half_width<EmuSIMD::u64x8>
	{
		using type = EmuSIMD::u64x4;
	};
#endif
#pragma endregion

#pragma region REGISTER_TO_ARG_TYPE
	template<>
	struct register_to_arg_type<EmuSIMD::f32x4>
	{
		using type = EmuSIMD::f32x4_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::f32x8>
	{
		using type = EmuSIMD::f32x8_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::f32x16>
	{
		using type = EmuSIMD::f32x16_arg;
	};

	template<>
	struct register_to_arg_type<EmuSIMD::f64x2>
	{
		using type = EmuSIMD::f64x2_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::f64x4>
	{
		using type = EmuSIMD::f64x4_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::f64x8>
	{
		using type = EmuSIMD::f64x8_arg;
	};

#if EMU_SIMD_USE_GENERIC_INT_REGISTERS
	template<>
	struct register_to_arg_type<EmuSIMD::i128_generic>
	{
		using type = EmuSIMD::i128_generic_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::i256_generic>
	{
		using type = EmuSIMD::i256_generic_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::i512_generic>
	{
		using type = EmuSIMD::i512_generic_arg;
	};
#else
	template<>
	struct register_to_arg_type<EmuSIMD::i8x16>
	{
		using type = EmuSIMD::i8x16_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::i16x8>
	{
		using type = EmuSIMD::i16x8_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::i32x4>
	{
		using type = EmuSIMD::i32x4_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::i64x2>
	{
		using type = EmuSIMD::i64x2_arg;
	};

	template<>
	struct register_to_arg_type<EmuSIMD::i8x32>
	{
		using type = EmuSIMD::i8x32_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::i16x16>
	{
		using type = EmuSIMD::i16x16_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::i32x8>
	{
		using type = EmuSIMD::i32x8_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::i64x4>
	{
		using type = EmuSIMD::i64x4_arg;
	};

	template<>
	struct register_to_arg_type<EmuSIMD::i8x64>
	{
		using type = EmuSIMD::i8x64_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::i16x32>
	{
		using type = EmuSIMD::i16x32_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::i32x16>
	{
		using type = EmuSIMD::i32x16_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::i64x8>
	{
		using type = EmuSIMD::i64x8_arg;
	};

	template<>
	struct register_to_arg_type<EmuSIMD::u8x16>
	{
		using type = EmuSIMD::u8x16_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::u16x8>
	{
		using type = EmuSIMD::u16x8_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::u32x4>
	{
		using type = EmuSIMD::u32x4_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::u64x2>
	{
		using type = EmuSIMD::u64x2_arg;
	};

	template<>
	struct register_to_arg_type<EmuSIMD::u8x32>
	{
		using type = EmuSIMD::u8x32_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::u16x16>
	{
		using type = EmuSIMD::u16x16_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::u32x8>
	{
		using type = EmuSIMD::u32x8_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::u64x4>
	{
		using type = EmuSIMD::u64x4_arg;
	};

	template<>
	struct register_to_arg_type<EmuSIMD::u8x64>
	{
		using type = EmuSIMD::u8x64_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::u16x32>
	{
		using type = EmuSIMD::u16x32_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::u32x16>
	{
		using type = EmuSIMD::u32x16_arg;
	};
	template<>
	struct register_to_arg_type<EmuSIMD::u64x8>
	{
		using type = EmuSIMD::u64x8_arg;
	};
#endif
#pragma endregion

#pragma region DETERMINE_REGISTER_ELEMENT_COUNT
	template<Concepts::KnownSIMD Register_, std::size_t PerElementWidthIfGenericInt_ = 32>
	[[nodiscard]] constexpr inline std::size_t determine_register_element_count()
	{
		using _register_uq = typename std::remove_cvref<Register_>::type;
		if constexpr (EmuCore::TMP::is_any_same_v<_register_uq, EmuSIMD::i128_generic, EmuSIMD::i256_generic, EmuSIMD::i512_generic>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidthIfGenericInt_>())
			{
				return EmuSIMD::TMP::simd_register_width_v<_register_uq> / PerElementWidthIfGenericInt_;
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(), "Invalid `PerElementWidthIfGenericInt_` passed when calling `EmuSIMD::TMP::determine_register_element_count` with a generic integral SIMD register.");
			}
		}
		else
		{
			if constexpr (EmuCore::TMP::is_any_same_v<_register_uq, EmuSIMD::f64x2, EmuSIMD::i64x2, EmuSIMD::u64x2>)
			{
				return 2;
			}
			else if constexpr (EmuCore::TMP::is_any_same_v<_register_uq, EmuSIMD::f32x4, EmuSIMD::f64x4, EmuSIMD::i32x4, EmuSIMD::u32x4, EmuSIMD::i64x4, EmuSIMD::u64x4>)
			{
				return 4;
			}
			else if constexpr (EmuCore::TMP::is_any_same_v<_register_uq, EmuSIMD::f32x8, EmuSIMD::f64x8, EmuSIMD::i16x8, EmuSIMD::u16x8, EmuSIMD::i32x8, EmuSIMD::u32x8, EmuSIMD::i64x8, EmuSIMD::u64x8>)
			{
				return 8;
			}
			else if constexpr (EmuCore::TMP::is_any_same_v<_register_uq, EmuSIMD::f32x16, EmuSIMD::i8x16, EmuSIMD::u8x16, EmuSIMD::i16x16, EmuSIMD::u16x16, EmuSIMD::i32x16, EmuSIMD::u32x16>)
			{
				return 16;
			}
			else if constexpr (EmuCore::TMP::is_any_same_v<_register_uq, EmuSIMD::i8x32, EmuSIMD::u8x32, EmuSIMD::i16x32, EmuSIMD::u16x32>)
			{
				return 32;
			}
			else if constexpr (EmuCore::TMP::is_any_same_v<_register_uq, EmuSIMD::i8x64, EmuSIMD::u8x64>)
			{
				return 64;
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<_register_uq>(), "Invalid `Register_` type passed to `EmuSIMD::TMP::determine_register_element_count`: The register is not supported for this operation.");
			}
		}
	}

	template<Concepts::KnownSIMD SIMDRegister_, std::size_t PerElementWidthIfGenericInt_ = 32>
	[[nodiscard]] constexpr inline std::size_t determine_register_per_element_width()
	{
		if constexpr (EmuSIMD::TMP::is_generic_integer_simd_register_v<SIMDRegister_>)
		{
			static_assert
			(
				EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidthIfGenericInt_>(),
				"Invalid `PerElementWidthIfGenericInt_` passed to `EmuSIMD::TMP::determine_register_per_element_width` when determining the per-element-width of a generic integral register."
			);
			return PerElementWidthIfGenericInt_;
		}
		else
		{
			constexpr std::size_t num_elements = determine_register_element_count<SIMDRegister_, PerElementWidthIfGenericInt_>();
			constexpr std::size_t register_width = EmuSIMD::TMP::simd_register_width_v<SIMDRegister_>;
			return register_width / num_elements;
		}
	}
#pragma endregion
}

#endif
