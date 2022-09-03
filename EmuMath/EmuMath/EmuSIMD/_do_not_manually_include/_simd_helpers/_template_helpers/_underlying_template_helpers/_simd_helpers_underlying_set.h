#ifndef EMU_SIMD_TEMPLATE_HELPERS_UNDERLYING_SET_H_INC_
#define EMU_SIMD_TEMPLATE_HELPERS_UNDERLYING_SET_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD::_underlying_simd_helpers
{
	template<class Register_, std::size_t ElementWidth_, bool Reverse_, typename...Args_>
	[[nodiscard]] inline Register_ _set_int(Args_&&...args_)
	{
		static_assert
		(
			EmuSIMD::TMP::_assert_valid_simd_int_element_width<ElementWidth_>(),
			"Invalid ElementWidth_ provided when setting an integral SIMD register via EmuSIMD helpers."
		);
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_args_ = sizeof...(Args_);
		constexpr std::size_t register_width_ = EmuSIMD::TMP::simd_register_width_v<register_type_uq>;
		constexpr std::size_t expected_num_args_ = register_width_ / ElementWidth_;
		using width_int = EmuCore::TMP::int_of_size_t<ElementWidth_ / 8>;

		if constexpr (!std::is_same_v<width_int, std::false_type>)
		{
			if constexpr (num_args_ == expected_num_args_)
			{
				if constexpr (EmuCore::TMP::are_all_static_castable_v<width_int, Args_...>)
				{
					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
					{
						// 128-bit
						if constexpr (ElementWidth_ == 8)
						{
							if constexpr (Reverse_)
							{
								return EmuSIMD::Funcs::setr_i8x16(static_cast<width_int>(args_)...);
							}
							else
							{
								return EmuSIMD::Funcs::set_i8x16(static_cast<width_int>(args_)...);
							}
						}
						else if constexpr (ElementWidth_ == 16)
						{
							if constexpr (Reverse_)
							{
								return EmuSIMD::Funcs::setr_i16x8(static_cast<width_int>(args_)...);
							}
							else
							{
								return EmuSIMD::Funcs::set_i16x8(static_cast<width_int>(args_)...);
							}
						}
						else if constexpr (ElementWidth_ == 32)
						{
							if constexpr (Reverse_)
							{
								return EmuSIMD::Funcs::setr_i32x4(static_cast<width_int>(args_)...);
							}
							else
							{
								return EmuSIMD::Funcs::set_i32x4(static_cast<width_int>(args_)...);
							}
						}
						else
						{
							if constexpr (Reverse_)
							{
								return EmuSIMD::Funcs::setr_i64x2(static_cast<width_int>(args_)...);
							}
							else
							{
								return EmuSIMD::Funcs::set_i64x2(static_cast<width_int>(args_)...);
							}
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
					{
						// 256-bit
						if constexpr (ElementWidth_ == 8)
						{
							if constexpr (Reverse_)
							{
								return EmuSIMD::Funcs::setr_i8x32(static_cast<width_int>(args_)...);
							}
							else
							{
								return EmuSIMD::Funcs::set_i8x32(static_cast<width_int>(args_)...);
							}
						}
						else if constexpr (ElementWidth_ == 16)
						{
							if constexpr (Reverse_)
							{
								return EmuSIMD::Funcs::setr_i16x16(static_cast<width_int>(args_)...);
							}
							else
							{
								return EmuSIMD::Funcs::set_i16x16(static_cast<width_int>(args_)...);
							}
						}
						else if constexpr (ElementWidth_ == 32)
						{
							if constexpr (Reverse_)
							{
								return EmuSIMD::Funcs::setr_i32x8(static_cast<width_int>(args_)...);
							}
							else
							{
								return EmuSIMD::Funcs::set_i32x8(static_cast<width_int>(args_)...);
							}
						}
						else
						{
							if constexpr (Reverse_)
							{
								return EmuSIMD::Funcs::setr_i64x4(static_cast<width_int>(args_)...);
							}
							else
							{
								return EmuSIMD::Funcs::set_i64x4(static_cast<width_int>(args_)...);
							}
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
					{
						// 512-bit
						if constexpr (ElementWidth_ == 8)
						{
							if constexpr (Reverse_)
							{
								return EmuSIMD::Funcs::setr_i8x64(static_cast<width_int>(args_)...);
							}
							else
							{
								return EmuSIMD::Funcs::set_i8x64(static_cast<width_int>(args_)...);
							}
						}
						else if constexpr (ElementWidth_ == 16)
						{
							if constexpr (Reverse_)
							{
								return EmuSIMD::Funcs::setr_i16x32(static_cast<width_int>(args_)...);
							}
							else
							{
								return EmuSIMD::Funcs::set_i16x32(static_cast<width_int>(args_)...);
							}
						}
						else if constexpr (ElementWidth_ == 32)
						{
							if constexpr (Reverse_)
							{
								return EmuSIMD::Funcs::setr_i32x16(static_cast<width_int>(args_)...);
							}
							else
							{
								return EmuSIMD::Funcs::set_i32x16(static_cast<width_int>(args_)...);
							}
						}
						else
						{
							if constexpr (Reverse_)
							{
								return EmuSIMD::Funcs::setr_i64x8(static_cast<width_int>(args_)...);
							}
							else
							{
								return EmuSIMD::Funcs::set_i64x8(static_cast<width_int>(args_)...);
							}
						}
					}
					else
					{
						// UNSUPPORTED
						static_assert
						(
							EmuCore::TMP::get_false<Register_>(),
							"Attempted to set an integral SIMD register via EmuSIMD helpers, but the provided Register_ type was not a supported integral SIMD register."
						);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to set an integral SIMD register via EmuSIMD helpers, but at least one provided argument could not be converted to the type being used to set the register.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to set an integral SIMD register via EmuSIMD helpers, but an invalid number of arguments was provided. The following argument counts are required, with element bit-widths contained in square parantheses []: (EmuSIMD::i128_generic[8]: 16), (EmuSIMD::i128_generic[16]: 8), (EmuSIMD::i128_generic[32]: 4), (EmuSIMD::i128_generic[64]: 2), (EmuSIMD::i256_generic[8]: 32), (EmuSIMD::i256_generic[16]: 16), (EmuSIMD::i256_generic[32]: 8), (EmuSIMD::i256_generic[64]: 4), (EmuSIMD::i512_generic[8]: 64), (EmuSIMD::i512_generic[16]: 32), (EmuSIMD::i512_generic[32] : 16), (EmuSIMD::i512_generic[64]: 8).");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to set an integral SIMD register via EmuSIMD helpers, but a valid integral scalar type for set casts could not be determined.");
		}
	}

	template<class Register_, bool Reverse_, typename...Args_>
	[[nodiscard]] inline Register_ _set_fp(Args_&&...args_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;

		if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::f32x4, EmuSIMD::f32x8, EmuSIMD::f32x16>::value)
		{
			// FLOAT
			constexpr std::size_t register_width_ = EmuSIMD::TMP::simd_register_width_v<register_type_uq>;
			constexpr std::size_t num_args_ = sizeof...(Args_);
			constexpr std::size_t expected_num_args_ = register_width_ / 32;

			if constexpr (num_args_ == expected_num_args_)
			{
				if constexpr (EmuCore::TMP::are_all_static_castable_v<float, Args_...>)
				{
					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
					{
						if constexpr (Reverse_)
						{
							return EmuSIMD::Funcs::setr_f32x4(static_cast<float>(args_)...);
						}
						else
						{
							return EmuSIMD::Funcs::set_f32x4(static_cast<float>(args_)...);
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
					{
						if constexpr (Reverse_)
						{
							return EmuSIMD::Funcs::setr_f32x8(static_cast<float>(args_)...);
						}
						else
						{
							return EmuSIMD::Funcs::set_f32x8(static_cast<float>(args_)...);
						}
					}
					else
					{
						if constexpr (Reverse_)
						{
							return EmuSIMD::Funcs::setr_f32x16(static_cast<float>(args_)...);
						}
						else
						{
							return EmuSIMD::Funcs::set_f32x16(static_cast<float>(args_)...);
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to set a SIMD float register via EmuSIMD helpers, but at least one provided argument was not convertible to `float`.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to set a SIMD float register via EmuSIMD helpers, but an invalid number of arguments was provided. The following argument counts are required: (EmuSIMD::f32x4: 4), (EmuSIMD::f32x8: 8), (EmuSIMD::f32x16: 16).");
			}
		}
		else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::f64x2, EmuSIMD::f64x4, EmuSIMD::f64x8>::value)
		{
			// DOUBLE
			constexpr std::size_t register_width_ = EmuSIMD::TMP::simd_register_width_v<register_type_uq>;
			constexpr std::size_t num_args_ = sizeof...(Args_);
			constexpr std::size_t expected_num_args_ = register_width_ / 64;

			if constexpr (num_args_ == expected_num_args_)
			{
				if constexpr (EmuCore::TMP::are_all_static_castable_v<double, Args_...>)
				{
					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
					{
						if constexpr (Reverse_)
						{
							return EmuSIMD::Funcs::setr_f64x2(static_cast<double>(args_)...);
						}
						else
						{
							return EmuSIMD::Funcs::set_f64x2(static_cast<double>(args_)...);
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
					{
						if constexpr (Reverse_)
						{
							return EmuSIMD::Funcs::setr_f64x4(static_cast<double>(args_)...);
						}
						else
						{
							return EmuSIMD::Funcs::set_f64x2(static_cast<double>(args_)...);
						}
					}
					else
					{
						if constexpr (Reverse_)
						{
							return EmuSIMD::Funcs::setr_f64x8(static_cast<double>(args_)...);
						}
						else
						{
							return EmuSIMD::Funcs::set_f64x2(static_cast<double>(args_)...);
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to set a SIMD double register via EmuSIMD helpers, but at least one provided argument was not convertible to `double`.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to set a SIMD double register via EmuSIMD helpers, but an invalid number of arguments was provided. The following argument counts are required: (EmuSIMD::f64x2: 2), (EmuSIMD::f64x4: 4), (EmuSIMD::f64x8: 8).");
			}
		}
		else
		{
			// UNSUPPORTED
			static_assert
			(
				EmuCore::TMP::get_false<Register_>(),
				"Attempted to set a floating-point SIMD register via EmuSIMD helpers, but the provided Register_ type was not a supported floating-point SIMD register."
			);
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _setzero()
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::setzero_f32x4();
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::setzero_f32x8();
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::setzero_f32x16();
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::setzero_f64x2();
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::setzero_f64x4();
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::setzero_f64x8();
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				return _mm_setzero_si128();
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				return _mm256_setzero_si256();
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				return _mm512_setzero_si512();
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to set a SIMD register to zero via EmuSIMD helpers, but the provided SIMD register is not supported for this feature.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to set a SIMD register to zero via EmuSIMD helpers, but the provided type was not a SIMD register type, or was not a supported SIMD type.");
		}
	}

	template<class Register_, std::size_t PerElementWidthIfInt_ = 32, typename Val_>
	[[nodiscard]] inline Register_ _set1(const Val_& val_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::f32x4, EmuSIMD::f32x8, EmuSIMD::f32x16>::value)
			{
				if constexpr (EmuCore::TMP::is_static_castable_v<Val_, float>)
				{
					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
					{
						return EmuSIMD::Funcs::set1_f32x4(static_cast<float>(val_));
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
					{
						return EmuSIMD::Funcs::set1_f32x8(static_cast<float>(val_));
					}
					else
					{
						return EmuSIMD::Funcs::set1_f32x16(static_cast<float>(val_));
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to set a SIMD register of floats to the same value, but the provided Val_ was a type that cannot be converted to float.");
				}
			}
			else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::f64x2, EmuSIMD::f64x4, EmuSIMD::f64x8>::value)
			{
				if constexpr (std::is_constructible_v<Val_, double>)
				{
					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
					{
						return EmuSIMD::Funcs::set1_f64x2(static_cast<double>(val_));
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
					{
						return EmuSIMD::Funcs::set1_f64x4(static_cast<double>(val_));
					}
					else
					{
						return EmuSIMD::Funcs::set1_f64x8(static_cast<double>(val_));
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to set a SIMD register of doubles to the same value, but the provided Val_ was a type that cannot be converted to double.");
				}
			}
			else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::i128_generic, EmuSIMD::i256_generic, EmuSIMD::i512_generic>::value)
			{
				if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidthIfInt_>())
				{
					using int_type = EmuCore::TMP::int_of_size_t<PerElementWidthIfInt_ / 8>;
					if constexpr (EmuCore::TMP::is_static_castable_v<Val_, int_type>)
					{
						if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
						{
							if constexpr (PerElementWidthIfInt_ == 8)
							{
								return EmuSIMD::Funcs::set1_i8x16(static_cast<int_type>(val_));
							}
							else if constexpr (PerElementWidthIfInt_ == 16)
							{
								return EmuSIMD::Funcs::set1_i16x8(static_cast<int_type>(val_));
							}
							else if constexpr (PerElementWidthIfInt_ == 32)
							{
								return EmuSIMD::Funcs::set1_i32x4(static_cast<int_type>(val_));
							}
							else
							{
								return EmuSIMD::Funcs::set1_i64x2(static_cast<int_type>(val_));
							}
						}
						else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
						{
							if constexpr (PerElementWidthIfInt_ == 8)
							{
								return EmuSIMD::Funcs::set1_i8x32(static_cast<int_type>(val_));
							}
							else if constexpr (PerElementWidthIfInt_ == 16)
							{
								return EmuSIMD::Funcs::set1_i16x16(static_cast<int_type>(val_));
							}
							else if constexpr (PerElementWidthIfInt_ == 32)
							{
								return EmuSIMD::Funcs::set1_i32x8(static_cast<int_type>(val_));
							}
							else
							{
								return EmuSIMD::Funcs::set1_i64x4(static_cast<int_type>(val_));
							}
						}
						else
						{
							if constexpr (PerElementWidthIfInt_ == 8)
							{
								return EmuSIMD::Funcs::set1_i8x64(static_cast<int_type>(val_));
							}
							else if constexpr (PerElementWidthIfInt_ == 16)
							{
								return EmuSIMD::Funcs::set1_i16x32(static_cast<int_type>(val_));
							}
							else if constexpr (PerElementWidthIfInt_ == 32)
							{
								return EmuSIMD::Funcs::set1_i32x16(static_cast<int_type>(val_));
							}
							else
							{
								return EmuSIMD::Funcs::set1_i64x8(static_cast<int_type>(val_));
							}
						}
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to set an integral SIMD register with all elements at the same value via EmuSIMD helpers, but the provided value cannot be converted to an integer of the specified bit width.");
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to set an integral SIMD register with all elements at the same value via EmuSIMD helpers, but the provided per-element width is invalid.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to set a SIMD register with all elements at the same value via EmuSIMD helpers, but the provided SIMD register is not supported for this feature.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to set a SIMD register with all elements at the same value via EmuSIMD helpers, but the provided type was not a SIMD register type, or was not a supported SIMD type.");
		}
	}

	template<class Register_, std::int64_t StartingVal_, template<class Lhs__, class Rhs__> class PerItemFuncTemplate_, bool Reverse_, std::size_t PerElementWidthIfInt_ = 32>
	[[nodiscard]] inline Register_ _set_from_starting_value()
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using PerItemFunc_ = PerItemFuncTemplate_<std::int64_t, std::int64_t>;
			constexpr PerItemFunc_ func_ = PerItemFunc_();

			if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::f32x4, EmuSIMD::f32x8, EmuSIMD::f32x16>::value)
			{
				constexpr float val_0_ = static_cast<float>(StartingVal_);
				constexpr float val_1_ = static_cast<float>(func_(StartingVal_, 1));
				constexpr float val_2_ = static_cast<float>(func_(StartingVal_, 2));
				constexpr float val_3_ = static_cast<float>(func_(StartingVal_, 3));

				if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
				{
					if constexpr (Reverse_)
					{
						return EmuSIMD::Funcs::setr_f32x4(val_0_, val_1_, val_2_, val_3_);
					}
					else
					{
						return EmuSIMD::Funcs::set_f32x4(val_0_, val_1_, val_2_, val_3_);
					}

				}
				else
				{
					constexpr float val_4_ = static_cast<float>(func_(StartingVal_, 4));
					constexpr float val_5_ = static_cast<float>(func_(StartingVal_, 5));
					constexpr float val_6_ = static_cast<float>(func_(StartingVal_, 6));
					constexpr float val_7_ = static_cast<float>(func_(StartingVal_, 7));

					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
					{
						if constexpr (Reverse_)
						{
							return EmuSIMD::Funcs::setr_f32x8(val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_);
						}
						else
						{
							return EmuSIMD::Funcs::set_f32x8(val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_);
						}
					}
					else
					{
						constexpr float val_8_ = static_cast<float>(func_(StartingVal_, 8));
						constexpr float val_9_ = static_cast<float>(func_(StartingVal_, 9));
						constexpr float val_10_ = static_cast<float>(func_(StartingVal_, 10));
						constexpr float val_11_ = static_cast<float>(func_(StartingVal_, 11));
						constexpr float val_12_ = static_cast<float>(func_(StartingVal_, 12));
						constexpr float val_13_ = static_cast<float>(func_(StartingVal_, 13));
						constexpr float val_14_ = static_cast<float>(func_(StartingVal_, 14));
						constexpr float val_15_ = static_cast<float>(func_(StartingVal_, 15));

						if constexpr (Reverse_)
						{
							return EmuSIMD::Funcs::setr_f32x16
							(
								val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
								val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_
							);
						}
						else
						{
							return EmuSIMD::Funcs::set_f32x16
							(
								val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
								val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_
							);
						}
					}
				}
			}
			else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::f64x2, EmuSIMD::f64x4, EmuSIMD::f64x8>::value)
			{
				constexpr double val_0_ = static_cast<double>(StartingVal_);
				constexpr double val_1_ = static_cast<double>(func_(StartingVal_, 1));

				if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
				{
					if constexpr (Reverse_)
					{
						return EmuSIMD::Funcs::setr_f64x2(val_0_, val_1_);
					}
					else
					{
						return EmuSIMD::Funcs::set_f64x2(val_0_, val_1_);
					}
				}
				else
				{
					constexpr double val_2_ = static_cast<double>(func_(StartingVal_, 2));
					constexpr double val_3_ = static_cast<double>(func_(StartingVal_, 3));

					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
					{
						if constexpr (Reverse_)
						{
							return EmuSIMD::Funcs::setr_f64x4(val_0_, val_1_, val_2_, val_3_);
						}
						else
						{
							return EmuSIMD::Funcs::set_f64x4(val_0_, val_1_, val_2_, val_3_);
						}
					}
					else
					{
						constexpr double val_4_ = static_cast<double>(func_(StartingVal_, 4));
						constexpr double val_5_ = static_cast<double>(func_(StartingVal_, 5));
						constexpr double val_6_ = static_cast<double>(func_(StartingVal_, 6));
						constexpr double val_7_ = static_cast<double>(func_(StartingVal_, 7));

						if constexpr (Reverse_)
						{
							return EmuSIMD::Funcs::setr_f64x8(val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_);
						}
						else
						{
							return EmuSIMD::Funcs::set_f64x8(val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_);
						}
					}
				}
			}
			else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::i128_generic, EmuSIMD::i256_generic, EmuSIMD::i512_generic>::value)
			{
				if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidthIfInt_>())
				{
					if constexpr (PerElementWidthIfInt_ == 8)
					{
						constexpr std::int8_t val_0_ = static_cast<std::int8_t>(StartingVal_);
						constexpr std::int8_t val_1_ = static_cast<std::int8_t>(func_(StartingVal_, 1));
						constexpr std::int8_t val_2_ = static_cast<std::int8_t>(func_(StartingVal_, 2));
						constexpr std::int8_t val_3_ = static_cast<std::int8_t>(func_(StartingVal_, 3));
						constexpr std::int8_t val_4_ = static_cast<std::int8_t>(func_(StartingVal_, 4));
						constexpr std::int8_t val_5_ = static_cast<std::int8_t>(func_(StartingVal_, 5));
						constexpr std::int8_t val_6_ = static_cast<std::int8_t>(func_(StartingVal_, 6));
						constexpr std::int8_t val_7_ = static_cast<std::int8_t>(func_(StartingVal_, 7));
						constexpr std::int8_t val_8_ = static_cast<std::int8_t>(func_(StartingVal_, 8));
						constexpr std::int8_t val_9_ = static_cast<std::int8_t>(func_(StartingVal_, 9));
						constexpr std::int8_t val_10_ = static_cast<std::int8_t>(func_(StartingVal_, 10));
						constexpr std::int8_t val_11_ = static_cast<std::int8_t>(func_(StartingVal_, 11));
						constexpr std::int8_t val_12_ = static_cast<std::int8_t>(func_(StartingVal_, 12));
						constexpr std::int8_t val_13_ = static_cast<std::int8_t>(func_(StartingVal_, 13));
						constexpr std::int8_t val_14_ = static_cast<std::int8_t>(func_(StartingVal_, 14));
						constexpr std::int8_t val_15_ = static_cast<std::int8_t>(func_(StartingVal_, 15));

						if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
						{
							if constexpr (Reverse_)
							{
								return EmuSIMD::Funcs::setr_i8x16
								(
									val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
									val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_
								);
							}
							else
							{
								return EmuSIMD::Funcs::set_i8x16
								(
									val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
									val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_
								);
							}
						}
						else
						{
							constexpr std::int8_t val_16_ = static_cast<std::int8_t>(func_(StartingVal_, 16));
							constexpr std::int8_t val_17_ = static_cast<std::int8_t>(func_(StartingVal_, 17));
							constexpr std::int8_t val_18_ = static_cast<std::int8_t>(func_(StartingVal_, 18));
							constexpr std::int8_t val_19_ = static_cast<std::int8_t>(func_(StartingVal_, 19));
							constexpr std::int8_t val_20_ = static_cast<std::int8_t>(func_(StartingVal_, 20));
							constexpr std::int8_t val_21_ = static_cast<std::int8_t>(func_(StartingVal_, 21));
							constexpr std::int8_t val_22_ = static_cast<std::int8_t>(func_(StartingVal_, 22));
							constexpr std::int8_t val_23_ = static_cast<std::int8_t>(func_(StartingVal_, 23));
							constexpr std::int8_t val_24_ = static_cast<std::int8_t>(func_(StartingVal_, 24));
							constexpr std::int8_t val_25_ = static_cast<std::int8_t>(func_(StartingVal_, 25));
							constexpr std::int8_t val_26_ = static_cast<std::int8_t>(func_(StartingVal_, 26));
							constexpr std::int8_t val_27_ = static_cast<std::int8_t>(func_(StartingVal_, 27));
							constexpr std::int8_t val_28_ = static_cast<std::int8_t>(func_(StartingVal_, 28));
							constexpr std::int8_t val_29_ = static_cast<std::int8_t>(func_(StartingVal_, 29));
							constexpr std::int8_t val_30_ = static_cast<std::int8_t>(func_(StartingVal_, 30));
							constexpr std::int8_t val_31_ = static_cast<std::int8_t>(func_(StartingVal_, 31));

							if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
							{
								if constexpr (Reverse_)
								{
									return EmuSIMD::Funcs::setr_i8x32
									(
										val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
										val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_,
										val_16_, val_17_, val_18_, val_19_, val_20_, val_21_, val_22_, val_23_,
										val_24_, val_25_, val_26_, val_27_, val_28_, val_29_, val_30_, val_31_
									);
								}
								else
								{
									return EmuSIMD::Funcs::set_i8x32
									(
										val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
										val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_,
										val_16_, val_17_, val_18_, val_19_, val_20_, val_21_, val_22_, val_23_,
										val_24_, val_25_, val_26_, val_27_, val_28_, val_29_, val_30_, val_31_
									);
								}
							}
							else
							{
								constexpr std::int8_t val_32_ = static_cast<std::int8_t>(func_(StartingVal_, 32));
								constexpr std::int8_t val_33_ = static_cast<std::int8_t>(func_(StartingVal_, 33));
								constexpr std::int8_t val_34_ = static_cast<std::int8_t>(func_(StartingVal_, 34));
								constexpr std::int8_t val_35_ = static_cast<std::int8_t>(func_(StartingVal_, 35));
								constexpr std::int8_t val_36_ = static_cast<std::int8_t>(func_(StartingVal_, 36));
								constexpr std::int8_t val_37_ = static_cast<std::int8_t>(func_(StartingVal_, 37));
								constexpr std::int8_t val_38_ = static_cast<std::int8_t>(func_(StartingVal_, 38));
								constexpr std::int8_t val_39_ = static_cast<std::int8_t>(func_(StartingVal_, 39));
								constexpr std::int8_t val_40_ = static_cast<std::int8_t>(func_(StartingVal_, 40));
								constexpr std::int8_t val_41_ = static_cast<std::int8_t>(func_(StartingVal_, 41));
								constexpr std::int8_t val_42_ = static_cast<std::int8_t>(func_(StartingVal_, 42));
								constexpr std::int8_t val_43_ = static_cast<std::int8_t>(func_(StartingVal_, 43));
								constexpr std::int8_t val_44_ = static_cast<std::int8_t>(func_(StartingVal_, 44));
								constexpr std::int8_t val_45_ = static_cast<std::int8_t>(func_(StartingVal_, 45));
								constexpr std::int8_t val_46_ = static_cast<std::int8_t>(func_(StartingVal_, 46));
								constexpr std::int8_t val_47_ = static_cast<std::int8_t>(func_(StartingVal_, 47));
								constexpr std::int8_t val_48_ = static_cast<std::int8_t>(func_(StartingVal_, 48));
								constexpr std::int8_t val_49_ = static_cast<std::int8_t>(func_(StartingVal_, 49));
								constexpr std::int8_t val_50_ = static_cast<std::int8_t>(func_(StartingVal_, 50));
								constexpr std::int8_t val_51_ = static_cast<std::int8_t>(func_(StartingVal_, 51));
								constexpr std::int8_t val_52_ = static_cast<std::int8_t>(func_(StartingVal_, 52));
								constexpr std::int8_t val_53_ = static_cast<std::int8_t>(func_(StartingVal_, 53));
								constexpr std::int8_t val_54_ = static_cast<std::int8_t>(func_(StartingVal_, 54));
								constexpr std::int8_t val_55_ = static_cast<std::int8_t>(func_(StartingVal_, 55));
								constexpr std::int8_t val_56_ = static_cast<std::int8_t>(func_(StartingVal_, 56));
								constexpr std::int8_t val_57_ = static_cast<std::int8_t>(func_(StartingVal_, 57));
								constexpr std::int8_t val_58_ = static_cast<std::int8_t>(func_(StartingVal_, 58));
								constexpr std::int8_t val_59_ = static_cast<std::int8_t>(func_(StartingVal_, 59));
								constexpr std::int8_t val_60_ = static_cast<std::int8_t>(func_(StartingVal_, 60));
								constexpr std::int8_t val_61_ = static_cast<std::int8_t>(func_(StartingVal_, 61));
								constexpr std::int8_t val_62_ = static_cast<std::int8_t>(func_(StartingVal_, 62));
								constexpr std::int8_t val_63_ = static_cast<std::int8_t>(func_(StartingVal_, 63));

								if constexpr (Reverse_)
								{
									return EmuSIMD::Funcs::setr_i8x64
									(
										val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
										val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_,
										val_16_, val_17_, val_18_, val_19_, val_20_, val_21_, val_22_, val_23_,
										val_24_, val_25_, val_26_, val_27_, val_28_, val_29_, val_30_, val_31_,
										val_32_, val_33_, val_34_, val_35_, val_36_, val_37_, val_38_, val_39_,
										val_40_, val_41_, val_42_, val_43_, val_44_, val_45_, val_46_, val_47_,
										val_48_, val_49_, val_50_, val_51_, val_52_, val_53_, val_54_, val_55_,
										val_56_, val_57_, val_58_, val_59_, val_60_, val_61_, val_62_, val_63_
									);
								}
								else
								{
									return EmuSIMD::Funcs::set_i8x64
									(
										val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
										val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_,
										val_16_, val_17_, val_18_, val_19_, val_20_, val_21_, val_22_, val_23_,
										val_24_, val_25_, val_26_, val_27_, val_28_, val_29_, val_30_, val_31_,
										val_32_, val_33_, val_34_, val_35_, val_36_, val_37_, val_38_, val_39_,
										val_40_, val_41_, val_42_, val_43_, val_44_, val_45_, val_46_, val_47_,
										val_48_, val_49_, val_50_, val_51_, val_52_, val_53_, val_54_, val_55_,
										val_56_, val_57_, val_58_, val_59_, val_60_, val_61_, val_62_, val_63_
									);
								}
							}
						}
					}
					else if constexpr (PerElementWidthIfInt_ == 16)
					{
						constexpr std::int16_t val_0_ = static_cast<std::int16_t>(StartingVal_);
						constexpr std::int16_t val_1_ = static_cast<std::int16_t>(func_(StartingVal_, 1));
						constexpr std::int16_t val_2_ = static_cast<std::int16_t>(func_(StartingVal_, 2));
						constexpr std::int16_t val_3_ = static_cast<std::int16_t>(func_(StartingVal_, 3));
						constexpr std::int16_t val_4_ = static_cast<std::int16_t>(func_(StartingVal_, 4));
						constexpr std::int16_t val_5_ = static_cast<std::int16_t>(func_(StartingVal_, 5));
						constexpr std::int16_t val_6_ = static_cast<std::int16_t>(func_(StartingVal_, 6));
						constexpr std::int16_t val_7_ = static_cast<std::int16_t>(func_(StartingVal_, 7));

						if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
						{
							if constexpr (Reverse_)
							{
								return EmuSIMD::Funcs::setr_i16x8(val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_);
							}
							else
							{
								return EmuSIMD::Funcs::set_i16x8(val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_);
							}
						}
						else
						{
							constexpr std::int16_t val_8_ = static_cast<std::int16_t>(func_(StartingVal_, 8));
							constexpr std::int16_t val_9_ = static_cast<std::int16_t>(func_(StartingVal_, 9));
							constexpr std::int16_t val_10_ = static_cast<std::int16_t>(func_(StartingVal_, 10));
							constexpr std::int16_t val_11_ = static_cast<std::int16_t>(func_(StartingVal_, 11));
							constexpr std::int16_t val_12_ = static_cast<std::int16_t>(func_(StartingVal_, 12));
							constexpr std::int16_t val_13_ = static_cast<std::int16_t>(func_(StartingVal_, 13));
							constexpr std::int16_t val_14_ = static_cast<std::int16_t>(func_(StartingVal_, 14));
							constexpr std::int16_t val_15_ = static_cast<std::int16_t>(func_(StartingVal_, 15));

							if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
							{
								if constexpr (Reverse_)
								{
									return EmuSIMD::Funcs::setr_i16x16
									(
										val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
										val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_
									);
								}
								else
								{
									return EmuSIMD::Funcs::set_i16x16
									(
										val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
										val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_
									);
								}
							}
							else
							{
								constexpr std::int16_t val_16_ = static_cast<std::int16_t>(func_(StartingVal_, 16));
								constexpr std::int16_t val_17_ = static_cast<std::int16_t>(func_(StartingVal_, 17));
								constexpr std::int16_t val_18_ = static_cast<std::int16_t>(func_(StartingVal_, 18));
								constexpr std::int16_t val_19_ = static_cast<std::int16_t>(func_(StartingVal_, 19));
								constexpr std::int16_t val_20_ = static_cast<std::int16_t>(func_(StartingVal_, 20));
								constexpr std::int16_t val_21_ = static_cast<std::int16_t>(func_(StartingVal_, 21));
								constexpr std::int16_t val_22_ = static_cast<std::int16_t>(func_(StartingVal_, 22));
								constexpr std::int16_t val_23_ = static_cast<std::int16_t>(func_(StartingVal_, 23));
								constexpr std::int16_t val_24_ = static_cast<std::int16_t>(func_(StartingVal_, 24));
								constexpr std::int16_t val_25_ = static_cast<std::int16_t>(func_(StartingVal_, 25));
								constexpr std::int16_t val_26_ = static_cast<std::int16_t>(func_(StartingVal_, 26));
								constexpr std::int16_t val_27_ = static_cast<std::int16_t>(func_(StartingVal_, 27));
								constexpr std::int16_t val_28_ = static_cast<std::int16_t>(func_(StartingVal_, 28));
								constexpr std::int16_t val_29_ = static_cast<std::int16_t>(func_(StartingVal_, 29));
								constexpr std::int16_t val_30_ = static_cast<std::int16_t>(func_(StartingVal_, 30));
								constexpr std::int16_t val_31_ = static_cast<std::int16_t>(func_(StartingVal_, 31));

								if constexpr (Reverse_)
								{
									return EmuSIMD::Funcs::setr_i16x32
									(
										val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
										val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_,
										val_16_, val_17_, val_18_, val_19_, val_20_, val_21_, val_22_, val_23_,
										val_24_, val_25_, val_26_, val_27_, val_28_, val_29_, val_30_, val_31_
									);
								}
								else
								{
									return EmuSIMD::Funcs::set_i16x32
									(
										val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
										val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_,
										val_16_, val_17_, val_18_, val_19_, val_20_, val_21_, val_22_, val_23_,
										val_24_, val_25_, val_26_, val_27_, val_28_, val_29_, val_30_, val_31_
									);
								}
							}
						}
					}
					else if constexpr (PerElementWidthIfInt_ == 32)
					{
						constexpr std::int32_t val_0_ = static_cast<std::int32_t>(StartingVal_);
						constexpr std::int32_t val_1_ = static_cast<std::int32_t>(func_(StartingVal_, 1));
						constexpr std::int32_t val_2_ = static_cast<std::int32_t>(func_(StartingVal_, 2));
						constexpr std::int32_t val_3_ = static_cast<std::int32_t>(func_(StartingVal_, 3));

						if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
						{
							if constexpr (Reverse_)
							{
								return EmuSIMD::Funcs::setr_i32x4(val_0_, val_1_, val_2_, val_3_);
							}
							else
							{
								return EmuSIMD::Funcs::set_i32x4(val_0_, val_1_, val_2_, val_3_);
							}
						}
						else
						{
							constexpr std::int32_t val_4_ = static_cast<std::int32_t>(func_(StartingVal_, 4));
							constexpr std::int32_t val_5_ = static_cast<std::int32_t>(func_(StartingVal_, 5));
							constexpr std::int32_t val_6_ = static_cast<std::int32_t>(func_(StartingVal_, 6));
							constexpr std::int32_t val_7_ = static_cast<std::int32_t>(func_(StartingVal_, 7));

							if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
							{
								if constexpr (Reverse_)
								{
									return EmuSIMD::Funcs::setr_i32x8(val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_);
								}
								else
								{
									return EmuSIMD::Funcs::set_i32x8(val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_);
								}
							}
							else
							{
								constexpr std::int32_t val_8_ = static_cast<std::int32_t>(func_(StartingVal_, 8));
								constexpr std::int32_t val_9_ = static_cast<std::int32_t>(func_(StartingVal_, 9));
								constexpr std::int32_t val_10_ = static_cast<std::int32_t>(func_(StartingVal_, 10));
								constexpr std::int32_t val_11_ = static_cast<std::int32_t>(func_(StartingVal_, 11));
								constexpr std::int32_t val_12_ = static_cast<std::int32_t>(func_(StartingVal_, 12));
								constexpr std::int32_t val_13_ = static_cast<std::int32_t>(func_(StartingVal_, 13));
								constexpr std::int32_t val_14_ = static_cast<std::int32_t>(func_(StartingVal_, 14));
								constexpr std::int32_t val_15_ = static_cast<std::int32_t>(func_(StartingVal_, 15));

								if constexpr (Reverse_)
								{
									return EmuSIMD::Funcs::setr_i32x16
									(
										val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
										val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_
									);
								}
								else
								{
									return EmuSIMD::Funcs::set_i32x16
									(
										val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
										val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_
									);
								}
							}
						}
					}
					else
					{
						constexpr std::int64_t val_0_ = static_cast<std::int64_t>(StartingVal_);
						constexpr std::int64_t val_1_ = static_cast<std::int64_t>(func_(StartingVal_, 1));

						if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
						{
							if constexpr (Reverse_)
							{
								return EmuSIMD::Funcs::setr_i64x2(val_0_, val_1_);
							}
							else
							{
								return EmuSIMD::Funcs::set_i64x2(val_0_, val_1_);
							}
						}
						else
						{
							constexpr std::int64_t val_2_ = static_cast<std::int64_t>(func_(StartingVal_, 2));
							constexpr std::int64_t val_3_ = static_cast<std::int64_t>(func_(StartingVal_, 3));

							if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
							{
								if constexpr (Reverse_)
								{
									return EmuSIMD::Funcs::setr_i64x4(val_0_, val_1_, val_2_, val_3_);
								}
								else
								{
									return EmuSIMD::Funcs::set_i64x4(val_0_, val_1_, val_2_, val_3_);
								}
							}
							else
							{
								constexpr std::int64_t val_4_ = static_cast<std::int64_t>(func_(StartingVal_, 4));
								constexpr std::int64_t val_5_ = static_cast<std::int64_t>(func_(StartingVal_, 5));
								constexpr std::int64_t val_6_ = static_cast<std::int64_t>(func_(StartingVal_, 6));
								constexpr std::int64_t val_7_ = static_cast<std::int64_t>(func_(StartingVal_, 7));

								if constexpr (Reverse_)
								{
									return EmuSIMD::Funcs::setr_i64x8(val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_);
								}
								else
								{
									return EmuSIMD::Funcs::set_i64x8(val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_);
								}
							}
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to set an integral SIMD register with a progressively modified value via EmuSIMD helpers, but the provided bit-width per element is invalid.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to set a SIMD register with a progressively modified value via EmuSIMD helpers, but the provided SIMD register is not supported for this feature.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to set a SIMD register with a progressively modified value via EmuSIMD helpers, but the provided type was not a SIMD register type, or was not a supported SIMD type.");
		}
	}

	template<class Register_, typename In_>
	[[nodiscard]] inline Register_ _load(const In_* p_to_load_)
	{
		using register_type_uq = EmuCore::TMP::remove_ref_cv_t<Register_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::load_f32x4(reinterpret_cast<const float*>(p_to_load_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::load_f32x8(reinterpret_cast<const float*>(p_to_load_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::load_f32x16(p_to_load_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::load_f64x2(reinterpret_cast<const double*>(p_to_load_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::load_f64x4(reinterpret_cast<const double*>(p_to_load_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::load_f64x8(p_to_load_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				return _mm_load_si128(reinterpret_cast<const EmuSIMD::i128_generic*>(p_to_load_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				return _mm256_load_si256(reinterpret_cast<const EmuSIMD::i256_generic*>(p_to_load_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				return _mm512_load_si512(p_to_load_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to load a SIMD register from memory via EmuSIMD helpers, but the provided SIMD register type is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to load a SIMD register from memory via EmuSIMD helpers, but the provided Register_ type was not recognised as a supported SIMD register.");
		}
	}

	template<class Register_, std::size_t PerElementWidthIfInt_, bool Reverse_, bool...SignAtIndex_>
	[[nodiscard]] inline Register_ _make_sign_mask()
	{
		using register_type_uq = EmuCore::TMP::remove_ref_cv_t<Register_>;
		if constexpr (EmuSIMD::TMP::register_element_count_v< register_type_uq, PerElementWidthIfInt_> == sizeof...(SignAtIndex_))
		{
			if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				using int_type = EmuCore::TMP::int_of_size_t<PerElementWidthIfInt_ / CHAR_BIT>;
				constexpr int_type sign_bit = std::numeric_limits<int_type>::min();
				constexpr int_type no_bit = int_type(0);
				return _set_int<Register_, PerElementWidthIfInt_, Reverse_>
				(
					EmuCore::TMP::conditional_value_v<SignAtIndex_, int_type, sign_bit, no_bit>...
				);
			}
			else
			{
				using fp_type = typename std::conditional
				<
					(EmuSIMD::TMP::simd_register_width_v<register_type_uq> / EmuSIMD::TMP::register_element_count_v<register_type_uq, PerElementWidthIfInt_>) == 4,
					float,
					double
				>::type;
				constexpr fp_type sign_bit = fp_type(-0.0);
				constexpr fp_type no_bit = fp_type(0.0);
				return _set_fp<Register_, Reverse_>
				(
					EmuCore::TMP::conditional_value_v<SignAtIndex_, fp_type, sign_bit, no_bit>...
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Register_>(),
				"Attempted to set a sign mask SIMD register via EmuSIMD Helpers, but the provided booleans for respective indices did not match the number of elements in the resulting register."
			);
		}
	}

	template<class Register_, std::size_t PerElementWidthIfInt_, bool OddSign_, bool Reverse_, std::size_t...Indices_>
	[[nodiscard]] inline Register_ _make_alternating_sign_mask(std::index_sequence<Indices_...> indices_)
	{
		return _make_sign_mask<Register_, PerElementWidthIfInt_, OddSign_, ((Indices_ % 2) == 1)...>();
	}
}

#endif
