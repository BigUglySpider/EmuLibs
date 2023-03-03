#ifndef EMU_SIMD_UNDERLYING_ALIASES_H_INC_
#define EMU_SIMD_UNDERLYING_ALIASES_H_INC_ 1

// GCC Diagnistics - Should be temporary, but no estimate on when
#pragma GCC diagnostic ignored "-Wignored-attributes"

#include <immintrin.h>

namespace EmuSIMD
{
#pragma region REGISTER_ALIASES
	/// <summary> Alias to a 128-bit register of 4 32-bit floating-point values. </summary>
	using f32x4 = __m128;
	/// <summary> Alias to a 256-bit register of 8 32-bit floating-point values. </summary>
	using f32x8 = __m256;
	/// <summary> Alias to a 512-bit register of 16 32-bit floating-point values. </summary>
	using f32x16 = __m512;


	/// <summary> Alias to a 128-bit register of 2 64-bit floating-point values. </summary>
	using f64x2 = __m128d;
	/// <summary> Alias to a 256-bit register of 4 64-bit floating-point values. </summary>
	using f64x4 = __m256d;
	/// <summary> Alias to a 512-bit register of 8 64-bit floating-point values. </summary>
	using f64x8 = __m512d;

	/// <summary> Alias to a 128-bit register of 16 8-bit signed integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using i8x16 = __m128i;
	/// <summary> Alias to a 256-bit register of 32 8-bit signed integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using i8x32 = __m256i;
	/// <summary> Alias to a 512-bit register of 64 8-bit signed integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using i8x64 = __m512i;

	/// <summary> Alias to a 128-bit register of 8 16-bit signed integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using i16x8 = __m128i;
	/// <summary> Alias to a 256-bit register of 16 16-bit signed integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using i16x16 = __m256i;
	/// <summary> Alias to a 512-bit register of 32 16-bit signed integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using i16x32 = __m512i;

	/// <summary> Alias to a 128-bit register of 4 32-bit signed integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using i32x4 = __m128i;
	/// <summary> Alias to a 256-bit register of 8 32-bit signed integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using i32x8 = __m256i;
	/// <summary> Alias to a 512-bit register of 16 32-bit signed integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using i32x16 = __m512i;

	/// <summary> Alias to a 128-bit register of 2 64-bit signed integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using i64x2 = __m128i;
	/// <summary> Alias to a 256-bit register of 4 64-bit signed integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using i64x4 = __m256i;
	/// <summary> Alias to a 512-bit register of 8 64-bit signed integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using i64x8 = __m512i;

	/// <summary> Alias to a 128-bit register of 16 8-bit unsigned integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using u8x16 = __m128i;
	/// <summary> Alias to a 256-bit register of 32 8-bit unsigned integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using u8x32 = __m256i;
	/// <summary> Alias to a 512-bit register of 64 8-bit unsigned integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using u8x64 = __m512i;

	/// <summary> Alias to a 128-bit register of 8 16-bit unsigned integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using u16x8 = __m128i;
	/// <summary> Alias to a 256-bit register of 16 16-bit unsigned integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using u16x16 = __m256i;
	/// <summary> Alias to a 512-bit register of 32 16-bit unsigned integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using u16x32 = __m512i;

	/// <summary> Alias to a 128-bit register of 4 32-bit unsigned integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using u32x4 = __m128i;
	/// <summary> Alias to a 256-bit register of 8 32-bit unsigned integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using u32x8 = __m256i;
	/// <summary> Alias to a 512-bit register of 16 32-bit unsigned integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using u32x16 = __m512i;

	/// <summary> Alias to a 128-bit register of 2 64-bit unsigned integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using u64x2 = __m128i;
	/// <summary> Alias to a 256-bit register of 4 64-bit unsigned integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using u64x4 = __m256i;
	/// <summary> Alias to a 512-bit register of 8 64-bit unsigned integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using u64x8 = __m512i;

	/// <summary> Alias to a generic 128-bit integral register, which is per-element-width-and-signedness-agnostic. If there is no generic register, this will be `void`. </summary>
	using i128_generic = __m128i;
	/// <summary> Alias to a generic 256-bit integral register, which is per-element-width-and-signedness-agnostic. If there is no generic register, this will be `void`. </summary>
	using i256_generic = __m256i;
	/// <summary> Alias to a generic 512-bit integral register, which is per-element-width-and-signedness-agnostic. If there is no generic register, this will be `void`. </summary>
	using i512_generic = __m512i;
#pragma endregion

#pragma region ARG_ALIASES
	/// <summary> Alias to the expected argument type for a 128-bit register of 32-bit floating points. This will either be f32x4, or a constant reference to it. </summary>
	using f32x4_arg = f32x4;
	/// <summary> Alias to the expected argument type for a 256-bit register of 32-bit floating points. This will either be f32x8, or a constant reference to it. </summary>
	using f32x8_arg = f32x8;
	/// <summary> Alias to the expected argument type for a 512-bit register of 32-bit floating points. This will either be f32x16, or a constant reference to it. </summary>
	using f32x16_arg = f32x16;

	/// <summary> Alias to the expected argument type for a 128-bit register of 64-bit floating points. This will either be f64x2, or a constant reference to it. </summary>
	using f64x2_arg = f64x2;
	/// <summary> Alias to the expected argument type for a 256-bit register of 64-bit floating points. This will either be f64x4, or a constant reference to it. </summary>
	using f64x4_arg = f64x4;
	/// <summary> Alias to the expected argument type for a 512-bit register of 64-bit floating points. This will either be f64x8, or a constant reference to it. </summary>
	using f64x8_arg = f64x8;

	/// <summary> Alias to the expected argument type for a 128-bit register of 8-bit signed integers. This will either be i8x16, or a constant reference to it. </summary>
	using i8x16_arg = i8x16;
	/// <summary> Alias to the expected argument type for a 256-bit register of 8-bit signed integers. This will either be i8x32, or a constant reference to it. </summary>
	using i8x32_arg = i8x32;
	/// <summary> Alias to the expected argument type for a 512-bit register of 8-bit signed integers. This will either be i8x64, or a constant reference to it. </summary>
	using i8x64_arg = i8x64;

	/// <summary> Alias to the expected argument type for a 128-bit register of 16-bit signed integers. This will either be i16x8, or a constant reference to it. </summary>
	using i16x8_arg = i16x8;
	/// <summary> Alias to the expected argument type for a 256-bit register of 16-bit signed integers. This will either be i16x16, or a constant reference to it. </summary>
	using i16x16_arg = i16x16;
	/// <summary> Alias to the expected argument type for a 512-bit register of 16-bit signed integers. This will either be i16x32, or a constant reference to it. </summary>
	using i16x32_arg = i16x32;

	/// <summary> Alias to the expected argument type for a 128-bit register of 32-bit signed integers. This will either be i32x4, or a constant reference to it. </summary>
	using i32x4_arg = i32x4;
	/// <summary> Alias to the expected argument type for a 256-bit register of 32-bit signed integers. This will either be i32x8, or a constant reference to it. </summary>
	using i32x8_arg = i32x8;
	/// <summary> Alias to the expected argument type for a 512-bit register of 32-bit signed integers. This will either be i32x16, or a constant reference to it. </summary>
	using i32x16_arg = i32x16;

	/// <summary> Alias to the expected argument type for a 128-bit register of 64-bit signed integers. This will either be i64x2, or a constant reference to it. </summary>
	using i64x2_arg = i64x2;
	/// <summary> Alias to the expected argument type for a 256-bit register of 64-bit signed integers. This will either be i64x4, or a constant reference to it. </summary>
	using i64x4_arg = i64x4;
	/// <summary> Alias to the expected argument type for a 512-bit register of 64-bit signed integers. This will either be i64x8, or a constant reference to it. </summary>
	using i64x8_arg = i64x8;

	/// <summary> Alias to the expected argument type for a 128-bit register of 8-bit signed integers. This will either be i8x16, or a constant reference to it. </summary>
	using u8x16_arg = u8x16;
	/// <summary> Alias to the expected argument type for a 256-bit register of 8-bit signed integers. This will either be i8x32, or a constant reference to it. </summary>
	using u8x32_arg = u8x32;
	/// <summary> Alias to the expected argument type for a 512-bit register of 8-bit signed integers. This will either be i8x64, or a constant reference to it. </summary>
	using u8x64_arg = u8x64;

	/// <summary> Alias to the expected argument type for a 128-bit register of 16-bit signed integers. This will either be i16x8, or a constant reference to it. </summary>
	using u16x8_arg = u16x8;
	/// <summary> Alias to the expected argument type for a 256-bit register of 16-bit signed integers. This will either be i16x16, or a constant reference to it. </summary>
	using u16x16_arg = u16x16;
	/// <summary> Alias to the expected argument type for a 512-bit register of 16-bit signed integers. This will either be i16x32, or a constant reference to it. </summary>
	using u16x32_arg = u16x32;

	/// <summary> Alias to the expected argument type for a 128-bit register of 32-bit signed integers. This will either be i32x4, or a constant reference to it. </summary>
	using u32x4_arg = u32x4;
	/// <summary> Alias to the expected argument type for a 256-bit register of 32-bit signed integers. This will either be i32x8, or a constant reference to it. </summary>
	using u32x8_arg = u32x8;
	/// <summary> Alias to the expected argument type for a 512-bit register of 32-bit signed integers. This will either be i32x16, or a constant reference to it. </summary>
	using u32x16_arg = u32x16;

	/// <summary> Alias to the expected argument type for a 128-bit register of 64-bit signed integers. This will either be i64x2, or a constant reference to it. </summary>
	using u64x2_arg = u64x2;
	/// <summary> Alias to the expected argument type for a 256-bit register of 64-bit signed integers. This will either be i64x4, or a constant reference to it. </summary>
	using u64x4_arg = u64x4;
	/// <summary> Alias to the expected argument type for a 512-bit register of 64-bit signed integers. This will either be i64x8, or a constant reference to it. </summary>
	using u64x8_arg = u64x8;

	/// <summary>
	/// <para> Alias to the expected argument type for a 128-bit register of integers, which is per-element-width-and-signedness-agnostic. </para>
	/// <para> This will be void if i128_generic is void (which indicates that there is no generic register). </para>
	/// <para> If not void, this will either be i128_generic or a constant reference to it. </para>
	/// </summary>
	using i128_generic_arg = i128_generic;
	/// <summary>
	/// <para> Alias to the expected argument type for a 256-bit register of integers, which is per-element-width-and-signedness-agnostic. </para>
	/// <para> This will be void if i256_generic is void (which indicates that there is no generic register). </para>
	/// <para> If not void, this will either be i256_generic or a constant reference to it. </para>
	/// </summary>
	using i256_generic_arg = i256_generic;
	/// <summary>
	/// <para> Alias to the expected argument type for a 512-bit register of integers, which is per-element-width-and-signedness-agnostic. </para>
	/// <para> This will be void if i512_generic is void (which indicates that there is no generic register). </para>
	/// <para> If not void, this will either be i512_generic or a constant reference to it. </para>
	/// </summary>
	using i512_generic_arg = i512_generic;
#pragma region
}

#endif