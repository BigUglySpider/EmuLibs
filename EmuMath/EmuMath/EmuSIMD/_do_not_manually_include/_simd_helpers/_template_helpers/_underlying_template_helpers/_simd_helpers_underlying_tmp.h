#ifndef EMU_SIMD_UNDERLYING_SIMD_HELPERS_TMP_H_INC_
#define EMU_SIMD_UNDERLYING_SIMD_HELPERS_TMP_H_INC_ 1

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
	[[nodiscard]] constexpr inline bool _valid_simd_int_element_width(std::size_t width_)
	{
		return width_ == 8 || width_ == 16 || width_ == 32 || width_ == 64;
	}
	template<std::size_t Width_>
	constexpr inline bool _assert_valid_simd_int_element_width()
	{
		if constexpr (_valid_simd_int_element_width(Width_))
		{
			return true;
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<std::size_t, Width_>(), "Invalid element width for a SIMD register provided. Valid per-element widths for integral SIMD registers are: 8, 16, 32, 64.");
			return false;
		}
	}

	template<class RegisterType_>
	struct is_simd_register
	{
		static constexpr bool value = std::conditional_t
		<
			std::is_same_v<RegisterType_, typename EmuCore::TMP::remove_ref_cv<RegisterType_>::type>,
			std::false_type,
			is_simd_register<typename EmuCore::TMP::remove_ref_cv<RegisterType_>::type>
		>::value;
	};
	template<>
	struct is_simd_register<EmuSIMD::f32x4>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_simd_register<EmuSIMD::f64x2>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_simd_register<EmuSIMD::i128_generic>
	{
		static constexpr bool value = !std::is_void_v<EmuSIMD::i128_generic>;
	};

	template<>
	struct is_simd_register<EmuSIMD::f32x8>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_simd_register<EmuSIMD::f64x4>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_simd_register<EmuSIMD::i256_generic>
	{
		static constexpr bool value = !std::is_void_v<EmuSIMD::i256_generic>;
	};

	template<>
	struct is_simd_register<EmuSIMD::f32x16>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_simd_register<EmuSIMD::f64x8>
	{
		static constexpr bool value = true;
	};
	template<>
	struct is_simd_register<EmuSIMD::i512_generic>
	{
		static constexpr bool value = !std::is_void_v<EmuSIMD::i512_generic>;
	};
	template<class Register_>
	static constexpr bool is_simd_register_v = is_simd_register<Register_>::value;

	template<class Register_>
	struct simd_register_width
	{
		// Formed as a recursive call on itself if the passed type is a SIMD register, since unqualified specialisations are used for value sets.

		static constexpr std::size_t value = std::conditional_t
		<
			is_simd_register_v<Register_>,
			simd_register_width<typename EmuCore::TMP::remove_ref_cv<Register_>::type>,
			std::integral_constant<std::size_t, 0>
		>::value;
	};
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
	struct simd_register_width<EmuSIMD::i128_generic>
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
	struct simd_register_width<EmuSIMD::i256_generic>
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
	template<>
	struct simd_register_width<EmuSIMD::i512_generic>
	{
		static constexpr std::size_t value = 512;
	};
	template<class Register_>
	static constexpr std::size_t simd_register_width_v = simd_register_width<Register_>::value;

	template<class Register_>
	struct is_integral_simd_register
	{
		// Formed as a recursive call on itself if the passed type is a SIMD register, since unqualified specialisations are used for value sets.

		static constexpr bool value = std::conditional_t
		<
			is_simd_register_v<Register_>,
			is_integral_simd_register<typename EmuCore::TMP::remove_ref_cv<Register_>::type>,
			std::false_type
		>::value;
	};
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
	struct is_integral_simd_register<EmuSIMD::i128_generic>
	{
		static constexpr bool value = !std::is_void_v<EmuSIMD::i128_generic>;
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
	struct is_integral_simd_register<EmuSIMD::i256_generic>
	{
		static constexpr bool value = !std::is_void_v<EmuSIMD::i256_generic>;
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
	template<>
	struct is_integral_simd_register<EmuSIMD::i512_generic>
	{
		static constexpr bool value = !std::is_void_v<EmuSIMD::i512_generic>;
	};
	template<class Register_>
	static constexpr bool is_integral_simd_register_v = is_integral_simd_register<Register_>::value;

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

	template<class Register_>
	struct is_floating_point_simd_register
	{
		// Solved via an inversion of a deferred call to is_integral_simd_register if we know this is a simd register.
		// --- Otherwise, we invert the value of true_type, which is equal to false.

		static constexpr bool value = !std::conditional_t
		<
			is_simd_register_v<Register_>,
			is_integral_simd_register<Register_>,
			std::true_type
		>::value;
	};
	template<class Register_>
	static constexpr bool is_floating_point_simd_register_v = is_floating_point_simd_register<Register_>::value;

	template<class Register_>
	struct floating_point_register_element_count
	{
		// Formed as a recursive call on itself if the passed type is a FP SIMD register, since unqualified specialisations are used for value sets.

		static constexpr std::size_t value = std::conditional_t
		<
			is_floating_point_simd_register_v<Register_>,
			floating_point_register_element_count<typename EmuCore::TMP::remove_ref_cv<Register_>::type>,
			std::integral_constant<std::size_t, 0>
		>::value;
	};
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
	template<class Register_>
	static constexpr std::size_t floating_point_register_element_count_v = floating_point_register_element_count<Register_>::value;

	template<class Register_>
	struct floating_point_register_element_width : EmuCore::TMP::type_check_ignore_ref_cv_base<floating_point_register_element_width, std::integral_constant<std::size_t, 0>, Register_>
	{
	};
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
	template<class Register_>
	static constexpr std::size_t floating_point_register_element_width_v = floating_point_register_element_width<Register_>::value;

	template<class Register_, std::size_t PerElementWidthIfInt_ = 32>
	struct register_element_count
	{
	private:
		static constexpr std::size_t _calculate_count()
		{
			using register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_uq>)
			{
				return EmuSIMD::TMP::floating_point_register_element_count_v<register_uq>;
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_uq>)
			{
				if constexpr (EmuSIMD::TMP::is_generic_integer_simd_register_v<register_uq>)
				{
					if constexpr (PerElementWidthIfInt_ == 8 || PerElementWidthIfInt_ == 16 || PerElementWidthIfInt_ == 32 || PerElementWidthIfInt_ == 64)
					{
						return EmuSIMD::TMP::simd_register_width_v<register_uq> / PerElementWidthIfInt_;
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<Register_>(),
							"Attempted to determine the element count of a generic integral SIMD register using EmuSIMD::TMP::register_element_count, but the provided PerElementWidthIfInt_ is invalid; only 8, 16, 32, and 64 are valid."
						);
					}
				}
				else
				{
					if constexpr (EmuCore::TMP::is_any_same_v<register_uq, EmuSIMD::i64x2, EmuSIMD::u64x2>)
					{
						return 2;
					}
					else if constexpr (EmuCore::TMP::is_any_same_v<register_uq, EmuSIMD::i32x4, EmuSIMD::u32x4, EmuSIMD::i64x4, EmuSIMD::u64x4>)
					{
						return 4;
					}
					else if constexpr (EmuCore::TMP::is_any_same_v<register_uq, EmuSIMD::i16x8, EmuSIMD::u16x8, EmuSIMD::i32x8, EmuSIMD::u32x8, EmuSIMD::i64x8, EmuSIMD::u64x8>)
					{
						return 8;
					}
					else if constexpr (EmuCore::TMP::is_any_same_v<register_uq, EmuSIMD::i8x16, EmuSIMD::u8x16, EmuSIMD::i16x16, EmuSIMD::u16x16, EmuSIMD::i32x16, EmuSIMD::u32x16>)
					{
						return 16;
					}
					else if constexpr (EmuCore::TMP::is_any_same_v<register_uq, EmuSIMD::i8x32, EmuSIMD::u8x32, EmuSIMD::i16x32, EmuSIMD::u16x32>)
					{
						return 32;
					}
					else if constexpr (EmuCore::TMP::is_any_same_v<register_uq, EmuSIMD::i8x64, EmuSIMD::u8x64>)
					{
						return 64;
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<Register_>(),
							"Attempted to determine the element count of a SIMD register using `EmuSIMD::TMP::register_element_count`, but the provided non-generic integral register type was not recognised."
						);
					}
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Register_>(),
					"Attempted to determine the element count of a SIMD register using EmuSIMD::TMP::register_element_count, but the provided type is not recognised as a floating-point or integral SIMD register."
				);
			}
		}

	public:
		static constexpr std::size_t value = _calculate_count();
	};
	template<class Register_, std::size_t PerElementWidthIfInt_ = 32>
	static constexpr std::size_t register_element_count_v = register_element_count<Register_, PerElementWidthIfInt_>::value;

	template<class Register_, std::size_t Index_, std::size_t PerElementWidthIfIntegral_ = 32>
	struct valid_register_index
	{
		// Formed as a recursive call on itself if the passed type is a SIMD register, since unqualified specialisations are used for value sets.

		static constexpr bool value = std::conditional_t
		<
			is_simd_register_v<Register_> && !std::is_same_v<Register_, typename EmuCore::TMP::remove_ref_cv<Register_>::type>,
			valid_register_index<typename EmuCore::TMP::remove_ref_cv<Register_>::type, Index_, PerElementWidthIfIntegral_>,
			std::false_type
		>::value;
	};
	template<std::size_t Index_, std::size_t PerElementWidthIfIntegral_>
	struct valid_register_index<EmuSIMD::f32x4, Index_, PerElementWidthIfIntegral_>
	{
		static constexpr std::size_t max_index = std::size_t(3);
		static constexpr bool value = Index_ <= max_index;
	};
	template<std::size_t Index_, std::size_t PerElementWidthIfIntegral_>
	struct valid_register_index<EmuSIMD::f32x8, Index_, PerElementWidthIfIntegral_>
	{
		static constexpr std::size_t max_index = std::size_t(7);
		static constexpr bool value = Index_ <= max_index;
	};
	template<std::size_t Index_, std::size_t PerElementWidthIfIntegral_>
	struct valid_register_index<EmuSIMD::f32x16, Index_, PerElementWidthIfIntegral_>
	{
		static constexpr std::size_t max_index = std::size_t(15);
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfIntegral_>
	struct valid_register_index<EmuSIMD::f64x2, Index_, PerElementWidthIfIntegral_>
	{
		static constexpr std::size_t max_index = std::size_t(1);
		static constexpr bool value = Index_ <= max_index;
	};
	template<std::size_t Index_, std::size_t PerElementWidthIfIntegral_>
	struct valid_register_index<EmuSIMD::f64x4, Index_, PerElementWidthIfIntegral_>
	{
		static constexpr std::size_t max_index = std::size_t(3);
		static constexpr bool value = Index_ <= max_index;
	};
	template<std::size_t Index_, std::size_t PerElementWidthIfIntegral_>
	struct valid_register_index<EmuSIMD::f64x8, Index_, PerElementWidthIfIntegral_>
	{
		static constexpr std::size_t max_index = std::size_t(7);
		static constexpr bool value = Index_ <= max_index;
	};

	template<std::size_t Index_, std::size_t PerElementWidth_>
	struct valid_register_index<EmuSIMD::i128_generic, Index_, PerElementWidth_>
	{
		static constexpr bool valid_element_width = _assert_valid_simd_int_element_width<PerElementWidth_>();
		static_assert(valid_element_width, "Invalid per-element width provided when checking for a valid integral SIMD register index via valid_register_index.");

		static constexpr std::size_t max_index = (simd_register_width_v<EmuSIMD::i128_generic> / PerElementWidth_) - std::size_t(1);
		static constexpr bool value = Index_ <= max_index;
	};
	template<std::size_t Index_, std::size_t PerElementWidth_>
	struct valid_register_index<EmuSIMD::i256_generic, Index_, PerElementWidth_>
	{
		static constexpr bool valid_element_width = _assert_valid_simd_int_element_width<PerElementWidth_>();
		static_assert(valid_element_width, "Invalid per-element width provided when checking for a valid integral SIMD register index via valid_register_index.");

		static constexpr std::size_t max_index = (simd_register_width_v<EmuSIMD::i256_generic> / PerElementWidth_) - std::size_t(1);
		static constexpr bool value = Index_ <= max_index;
	};
	template<std::size_t Index_, std::size_t PerElementWidth_>
	struct valid_register_index<EmuSIMD::i512_generic, Index_, PerElementWidth_>
	{
		static constexpr bool valid_element_width = _assert_valid_simd_int_element_width<PerElementWidth_>();
		static_assert(valid_element_width, "Invalid per-element width provided when checking for a valid integral SIMD register index via valid_register_index.");

		static constexpr std::size_t max_index = (simd_register_width_v<EmuSIMD::i512_generic> / PerElementWidth_) - std::size_t(1);
		static constexpr bool value = Index_ <= max_index;
	};
	template<class Register_, std::size_t Index_, std::size_t PerElementWidthIfIntegral_ = 32>
	static constexpr bool valid_register_index_v = valid_register_index<Register_, Index_, PerElementWidthIfIntegral_>::value;

	template<class Register_>
	struct half_width
	{
	private:
		[[nodiscard]] static constexpr inline auto _get()
		{
			using _register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
			if constexpr (std::is_same_v<_register_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::f32x4();
			}
			else if constexpr (std::is_same_v<_register_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::f32x8();
			}
			else if constexpr (std::is_same_v<_register_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::f64x2();
			}
			else if constexpr (std::is_same_v<_register_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::f64x4();
			}
			else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::i128_generic();
			}
			else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::i256_generic();
			}
			else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::i8x16();
			}
			else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::u8x16();
			}
			else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::i8x32();
			}
			else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::u8x32();
			}
			else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::i16x8();
			}
			else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::u16x8();
			}
			else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::i16x16();
			}
			else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::u16x16();
			}
			else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::i32x4();
			}
			else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::u32x4();
			}
			else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::i32x8();
			}
			else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::u32x8();
			}
			else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::i64x2();
			}
			else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::u64x2();
			}
			else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::i64x4();
			}
			else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::u64x4();
			}

			// Returns `void` if not a register or register width is the smallest supported
		}

	public:
		using type = typename EmuCore::TMP::remove_ref_cv<decltype(_get())>::type;
	};

	namespace Concepts
	{
		template<typename T_>
		concept KnownSIMD = EmuSIMD::TMP::is_simd_register_v<T_>;
	}

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
}

namespace EmuConcepts
{
	using namespace EmuSIMD::TMP::Concepts;
}

#endif
