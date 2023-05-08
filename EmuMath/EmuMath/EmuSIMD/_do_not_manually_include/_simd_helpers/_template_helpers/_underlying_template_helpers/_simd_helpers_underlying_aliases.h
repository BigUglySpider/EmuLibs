#ifndef EMU_SIMD_UNDERLYING_ALIASES_H_INC_
#define EMU_SIMD_UNDERLYING_ALIASES_H_INC_ 1

#include "_generic_funcs/_forward_declarations/_all_forward_declarations.h"
#include "../../../../../EmuCore/ArithmeticHelpers/BitHelpers.h"
#include "../../../../../EmuCore/CommonConcepts/Arithmetic.h"
#include "../../../../../EmuCore/CommonPreprocessor/Compiler.h"
#include "../../../../../EmuCore/TMPHelpers/Tuples.h"
#include "../../../../../EmuCore/TMPHelpers/TypeComparators.h"

#include <array>
#include <bit>
#include <immintrin.h>

// Should make these defines actually determined based on architecture/compiler rather than hard-coded

/// <summary>
/// <para> Preprocessor flag indicating if EmuSIMD uses 128-bit SIMD registers. If this is false, 128-bit registers are emulated. </para>
/// <para> When emulating, 128-bit registers will be emulated as a collection of scalars of the matching type. </para>
/// </summary>
#define EMU_SIMD_USE_128_REGISTERS (true)
/// <summary>
/// <para> Preprocessor flag indicating if EmuSIMD uses 256-bit SIMD registers. If this is false, 256-bit registers are emulated. </para>
/// <para> If this is true, `EMU_SIMD_USE_128_REGISTERS` will also be true. </para>
/// <para> When emulating, 256-bit registers will be emulated as two 128-bit registers (this will also work when 128-bit registers are emulated). </para>
/// </summary>
#define EMU_SIMD_USE_256_REGISTERS (true)
/// <summary>
/// <para> Preprocessor flag indicating if EmuSIMD uses 512-bit SIMD registers. If this is false, 512-bit registers are emulated. </para>
/// <para> If this is true, `EMU_SIMD_USE_256_REGISTERS` and `EMU_SIMD_USE_128_REGISTERS` will also be true. </para>
/// <para> When emulating, 512-bit registers will be emulated as two 256-bit registers (this will also work when 256-bit registers are emulated). </para>
/// </summary>
#define EMU_SIMD_USE_512_REGISTERS (true)
#define EMU_SIMD_USES_ANY_SIMD_REGISTERS (EMU_SIMD_USE_128_REGISTERS || EMU_SIMD_USE_256_REGISTERS || EMU_SIMD_USE_512_REGISTERS)

/// <summary>
/// <para> Boolean preprocessor flag indicating if 128-bit registers use reference arguments. </para>
/// <para> This affects the`_arg` variants of all 128-bit register aliases. </para>
/// </summary>
#define EMU_SIMD_128_ARG_REFS !(EMU_SIMD_USE_128_REGISTERS)
/// <summary>
/// <para> Boolean preprocessor flag indicating if 256-bit registers use reference arguments. </para>
/// <para> This affects the`_arg` variants of all 256-bit register aliases. </para>
/// </summary>
#define EMU_SIMD_256_ARG_REFS !(EMU_SIMD_USE_256_REGISTERS)
/// <summary>
/// <para> Boolean preprocessor flag indicating if 512-bit registers use reference arguments. </para>
/// <para> This affects the`_arg` variants of all 512-bit register aliases. </para>
/// </summary>
#define EMU_SIMD_512_ARG_REFS (EMU_SIMD_USE_512_REGISTERS)

#if EMU_SIMD_128_ARG_REFS
/// <summary> Helper macro for creating the 128-bit register arg types. `basic_type` is the base register alias (e.g. for `f32x4_arg`, `basic_type` is `f32x4`). </summary>
#define EMU_SIMD_128_MAKE_ARG_TYPE(basic_type) const basic_type&
#else
/// <summary> Helper macro for creating the 128-bit register arg types. `basic_type` is the base register alias (e.g. for `f32x4_arg`, `basic_type` is `f32x4`). </summary>
#define EMU_SIMD_128_MAKE_ARG_TYPE(basic_type) basic_type
#endif

#if EMU_SIMD_256_ARG_REFS
/// <summary> Helper macro for creating the 256-bit register arg types. `basic_type` is the base register alias (e.g. for `f32x8_arg`, `basic_type` is `f32x8`). </summary>
#define EMU_SIMD_256_MAKE_ARG_TYPE(basic_type) const basic_type&
#else
/// <summary> Helper macro for creating the 256-bit register arg types. `basic_type` is the base register alias (e.g. for `f32x8_arg`, `basic_type` is `f32x8`). </summary>
#define EMU_SIMD_256_MAKE_ARG_TYPE(basic_type) basic_type
#endif

#if EMU_SIMD_512_ARG_REFS
/// <summary> Helper macro for creating the 512-bit register arg types. `basic_type` is the base register alias (e.g. for `f32x16_arg`, `basic_type` is `f32x16`). </summary>
#define EMU_SIMD_512_MAKE_ARG_TYPE(basic_type) const basic_type&
#else
/// <summary> Helper macro for creating the 512-bit register arg types. `basic_type` is the base register alias (e.g. for `f32x16_arg`, `basic_type` is `f32x16`). </summary>
#define EMU_SIMD_512_MAKE_ARG_TYPE(basic_type) basic_type
#endif

/// <summary>
/// <para> Boolean preprocessor flag indicating if 128-bit, 256-bit, and 512-bit integral registers are generic (i.e. the same regardless of element width), as per x86/x64 intrinsics. </para>
/// <para> If true, tests such as `std::is_same_v&lt;i32x4, x16x8&gt;` will evaluate to true. </para>
/// <para> If false, tests such as `std::is_same_v&lt;i32x4, x16x8&gt;` will evaluate to false. </para>
/// </summary>
#define EMU_SIMD_USE_GENERIC_INT_REGISTERS ((EMU_SIMD_USE_128_REGISTERS) && (EMU_CORE_X86_X64))

namespace EmuSIMD
{
	namespace _underlying_impl
	{
#pragma region EMULATION_CONSTANTS
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//                                               COMMON ASSUMPTIONS                                              //     
		// - If a width of register is emulated, widths greater than it are also emulated								 //
		// - An emulation is always done with the width directly beneath it.											 //
		//    - 128-bit is emulated with an array of scalars															 //
		//    - 256-bit is emulated with two 128-bit lanes																 //
		//       - If 128-bit is emulated, this means 256-bit is emulated by two 128-bit emulators						 //
		//    - 512-bit is emulated with two 256-bit lanes																 //
		//       - If 256-bit is emulated, this means 512-bit is emulated by two 256-bit emulators						 //
		//          - If 128-bit is also emulated, these 256-bit emulators are in turn emulated by two 128-bit emulators //
		// - Members within any emulator will be public, but are ill-formed to access outside of emulator implementation //
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		template<std::size_t NumElements_, EmuConcepts::Arithmetic T_>
		struct single_lane_simd_emulator;
		template<std::size_t NumLanes_, class LaneT_>
		struct dual_lane_simd_emulator;

		template<class T_>
		struct is_simd_emulator : public EmuCore::TMP::type_check_ignore_ref_cv_base<is_simd_emulator, std::false_type, T_>
		{
		};
		template<std::size_t NumElements_, EmuConcepts::Arithmetic T_>
		struct is_simd_emulator<single_lane_simd_emulator<NumElements_, T_>>
		{
			static constexpr bool value = true;
		};
		template<std::size_t NumLanes_, class LaneT_>
		struct is_simd_emulator<dual_lane_simd_emulator<NumLanes_, LaneT_>>
		{
			static constexpr bool value = true;
		};

		template<class T_>
		struct is_single_lane_simd_emulator : public EmuCore::TMP::type_check_ignore_ref_cv_base<is_single_lane_simd_emulator, std::false_type, T_>
		{
		};
		template<std::size_t NumElements_, EmuConcepts::Arithmetic T_>
		struct is_single_lane_simd_emulator<single_lane_simd_emulator<NumElements_, T_>>
		{
			static constexpr bool value = true;
		};

		template<class T_>
		struct is_dual_lane_simd_emulator : public EmuCore::TMP::type_check_ignore_ref_cv_base<is_dual_lane_simd_emulator, std::false_type, T_>
		{
		};
		template<std::size_t EmulatedWidth_, class LaneT_>
		struct is_dual_lane_simd_emulator<dual_lane_simd_emulator<EmulatedWidth_, LaneT_>>
		{
			static constexpr bool value = true;
		};
#pragma endregion

#pragma region SINGLE_LANE_EMULATION
		template<std::size_t NumElements_, EmuConcepts::Arithmetic T_>
		struct single_lane_simd_emulator
		{
		public:
			static constexpr std::size_t _num_elements = NumElements_;
			using _value_type = T_;

		private:
			template<std::size_t Index_>
			[[nodiscard]] static constexpr inline const T_& _get_set1_arg(const T_& arg_) noexcept
			{
				return arg_;
			}

		public:
			/// <summary> Default constructor for an emulated SIMD register. This is safe to use. </summary>
			inline single_lane_simd_emulator() noexcept = default;
			/// <summary> Copy constructor for an emulated SIMD register. This is safe to use. </summary>
			inline single_lane_simd_emulator(const single_lane_simd_emulator<NumElements_, T_>&) noexcept = default;
			/// <summary> Move constructor for an emulated SIMD register. This is safe to use. </summary>
			inline single_lane_simd_emulator(single_lane_simd_emulator<NumElements_, T_>&&) noexcept = default;

			/// <summary>
			/// <para> `set1`-emulating constructor for an emulated SIMD register. </para>
			/// <para> This is non-standard and not safe to use; you should use the emulated-register's suitable `set1` function from the `EmuSIMD` namespace. </para>
			/// </summary>
			template<std::size_t...Indices_>
			inline single_lane_simd_emulator(const T_& set1_val_, std::index_sequence<Indices_...> index_sequence_) noexcept : 
				_data({ _get_set1_arg<Indices_>(set1_val_)... })
			{
			}

			/// <summary>
			/// <para> `load`-emulating constructor for an emulated SIMD register. </para>
			/// <para> This is non-standard and not safe to use; you should use the emulated-register's suitable `load` function from the `EmuSIMD` namespace. </para>
			/// </summary>
			inline single_lane_simd_emulator(const void* p_to_load_)
				: _data()
			{
				constexpr std::size_t bytes_to_load = 128 / 8; // Guaranteed to be 128-bit as this template is only for emulating 128-bit registers
				memcpy(_data.data(), p_to_load_, bytes_to_load);
			}

			/// <summary>
			/// <para> `set`-emulating constructor for an emulated SIMD register. </para>
			/// <para> This is non-standard and not safe to use; you should use the emulated-register's suitable `set` or `setr` function from the `EmuSIMD` namespace. </para>
			/// </summary>
			template
			<
				EmuConcepts::Arithmetic...Args_,
				typename = std::enable_if_t
				<
					(sizeof...(Args_) == NumElements_) &&
					(... && std::is_same_v<typename std::remove_cvref<T_>::type, typename std::remove_cvref<Args_>::type>)
				>
			>
			inline single_lane_simd_emulator(Args_&&...args_) noexcept :
				_data({ std::forward<Args_>(args_)... })
			{
			}

			/// <summary> 
			/// <para> Copy assignment operator for an emulated SIMD register. </para>
			/// <para> This should only be used through the syntax `x = y`; the syntax `x.operator=(y)` is non-standard and not safe to use. </para>
			/// </summary>
			inline single_lane_simd_emulator<NumElements_, T_>& operator=(const single_lane_simd_emulator<NumElements_, T_>&) noexcept = default;
			/// <summary> 
			/// <para> Move assignment operator for an emulated SIMD register. </para>
			/// <para> This should only be used through the syntax `x = y`; the syntax `x.operator=(y)` is non-standard and not safe to use. </para>
			/// </summary>
			inline single_lane_simd_emulator<NumElements_, T_>& operator=(single_lane_simd_emulator<NumElements_, T_>&&) noexcept = default;

			/// <summary>
			/// <para> The data stored within this emulated register. </para>
			/// <para> This is non-standard and not safe to use; you should use the emulated-register's suitable `store` or `storea` function from the `EmuSIMD` namespace to look at its data as scalar. </para>
			/// </summary>
			std::array<T_, NumElements_> _data;
		};
#pragma endregion

#pragma region DUALLANE_EMULATION
		/// <summary>
		/// <para> 256- or 512-bit SIMD emulator, composed of two 128- or 256-bit lanes respectively. </para>
		/// <para> This allows larger SIMD vectors to be emulated by collections of smaller registers (e.g. implementing 512-bit registers through two 256-bit registers). </para>
		/// <para> 
		///		This is intended to work recursively through other emulators; for example, if 128-bit is not emulated but 256-bit is emulated, 
		///		then the above example will contain two 256-bit emulators, which each contain two 128-bit registers, in turn causing the 
		///		overall emulation to be performed by 4 128-bit registers.
		/// </para>
		/// </summary>
		template<std::size_t EmulatedWidth_, class LaneT_>
		struct dual_lane_simd_emulator
		{
		public:
			using lane_type = LaneT_;
			static constexpr std::size_t emulated_width = EmulatedWidth_;

			/// <summary> Default constructor for an emulated SIMD register. This is safe to use. </summary>
			inline dual_lane_simd_emulator() noexcept = default;
			/// <summary> Copy constructor for an emulated SIMD register. This is safe to use. </summary>
			inline dual_lane_simd_emulator(const dual_lane_simd_emulator<EmulatedWidth_, LaneT_>&) noexcept = default;
			/// <summary> Move constructor for an emulated SIMD register. This is safe to use. </summary>
			inline dual_lane_simd_emulator(dual_lane_simd_emulator<EmulatedWidth_, LaneT_>&&) noexcept = default;

			/// <summary>
			/// <para> Constructor to create an emulated dual-lane SIMD register by copying two separate lanes. </para>
			/// <para> This is non-standard and not safe to use. </para>
			/// </summary>
			inline dual_lane_simd_emulator(const LaneT_& _lane_0_, const LaneT_& _lane_1_) noexcept :
				_lane_0(_lane_0_),
				_lane_1(_lane_1_)
			{
			}
			/// <summary>
			/// <para> Constructor to create an emulated dual-lane SIMD register by moving in _lane_0 and copying _lane_1. </para>
			/// <para> This is non-standard and not safe to use. </para>
			/// </summary>
			inline dual_lane_simd_emulator(LaneT_&& _lane_0_, const LaneT_& _lane_1_) noexcept :
				_lane_0(std::move(_lane_0_)),
				_lane_1(_lane_1_)
			{
			}
			/// <summary>
			/// <para> Constructor to create an emulated dual-lane SIMD register by copying _lane_0 and moving in _lane_1. </para>
			/// <para> This is non-standard and not safe to use. </para>
			/// </summary>
			inline dual_lane_simd_emulator(const LaneT_& _lane_0_, LaneT_&& _lane_1_) noexcept :
				_lane_0(_lane_0_),
				_lane_1(std::move(_lane_1_))
			{
			}
			/// <summary>
			/// <para> Constructor to create an emulated dual-lane SIMD register by moving two separate lanes. </para>
			/// <para> This is non-standard and not safe to use. </para>
			/// </summary>
			inline dual_lane_simd_emulator(LaneT_&& _lane_0_, LaneT_&& _lane_1_) noexcept :
				_lane_0(std::move(_lane_0_)),
				_lane_1(std::move(_lane_1_))
			{
			}

			/// <summary>
			/// <para> Constructor to create an emulated dual-lane SIMD register by copying its lo lane and zeroing its hi lane. </para>
			/// <para> This is non-standard and not safe to use. </para>
			/// </summary>
			inline dual_lane_simd_emulator(const LaneT_& _lane_0_) noexcept :
				_lane_0(_lane_0_),
				_lane_1()
			{
			}
			/// <summary>
			/// <para> Constructor to create an emulated dual-lane SIMD register by moving in its lo lane and zeroing its hi lane. </para>
			/// <para> This is non-standard and not safe to use. </para>
			/// </summary>
			inline dual_lane_simd_emulator(LaneT_&& _lane_0_) noexcept :
				_lane_0(std::move(_lane_0_)),
				_lane_1()
			{
			}

			/// <summary> 
			/// <para> Copy assignment operator for an emulated SIMD register. </para>
			/// <para> This should only be used through the syntax `x = y`; the syntax `x.operator=(y)` is non-standard and not safe to use. </para>
			/// </summary>
			inline dual_lane_simd_emulator<EmulatedWidth_, LaneT_>& operator=(const dual_lane_simd_emulator<EmulatedWidth_, LaneT_>&) noexcept = default;
			/// <summary> 
			/// <para> Move assignment operator for an emulated SIMD register. </para>
			/// <para> This should only be used through the syntax `x = y`; the syntax `x.operator=(y)` is non-standard and not safe to use. </para>
			/// </summary>
			inline dual_lane_simd_emulator<EmulatedWidth_, LaneT_>& operator=(dual_lane_simd_emulator<EmulatedWidth_, LaneT_>&&) noexcept = default;

			/// <summary>
			/// <para> The lo half of this emulator. </para>
			/// <para> This is non-standard and not safe to use; you should use the emulated-register's suitable `store` or `storea` function from the `EmuSIMD` namespace to look at its data as scalar. </para>
			/// </summary>
			LaneT_ _lane_0;
			/// <summary>
			/// <para> The hi half of this emulator. </para>
			/// <para> This is non-standard and not safe to use; you should use the emulated-register's suitable `store` or `storea` function from the `EmuSIMD` namespace to look at its data as scalar. </para>
			/// </summary>
			LaneT_ _lane_1;
		};
#pragma endregion

#pragma region EMULATED_ELEMENT_GETS
		template<typename OutT_, std::size_t Index_, bool AllowTheoreticalIndices_, std::size_t NumElements_, typename T_>
		[[nodiscard]] constexpr inline auto retrieve_emulated_single_lane_simd_element(const single_lane_simd_emulator<NumElements_, T_>& simd_emulator_) noexcept
			-> typename std::remove_cvref<OutT_>::type
		{
			if constexpr (Index_ < NumElements_)
			{
				if constexpr (std::is_same_v<T_, typename std::remove_cvref<OutT_>::type>)
				{
					return simd_emulator_._data[Index_];
				}
				else
				{
					return static_cast<typename std::remove_cvref<OutT_>::type>(simd_emulator_._data[Index_]);
				}
			}
			else
			{
				if constexpr (AllowTheoreticalIndices_)
				{
					return typename std::remove_cvref<OutT_>::type();
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, Index_>(), "INTERNAL EMUSIMD ERROR: `retrieve_emulated_single_lane_simd_element` called with an out-of-range index, with theoretical indices disallowed.");
				}
			}
		}

		template<typename OutT_, std::size_t Index_, bool AllowTheoreticalIndices_, std::size_t ElementsPerLane_, std::size_t EmulatedWidth_, typename LaneT_>
		[[nodiscard]] constexpr inline auto retrieve_emulated_dual_lane_simd_element(const dual_lane_simd_emulator<EmulatedWidth_, LaneT_>& simd_emulator_) noexcept
			-> typename std::remove_cvref<OutT_>::type
		{
			constexpr std::size_t num_elements = ElementsPerLane_ * 2;
			constexpr std::size_t per_element_width = EmulatedWidth_ / num_elements;
			constexpr bool is_lo_lane = (Index_ < ElementsPerLane_);
			if constexpr (Index_ < num_elements)
			{
				if constexpr (is_dual_lane_simd_emulator<LaneT_>::value)
				{
					// Input: 512-bit emulator
					// Output: From one 256-bit lane which itself is emulated
					// --- Defer to this function for an underlying layer
					if constexpr (is_lo_lane)
					{
						return retrieve_emulated_dual_lane_simd_element<OutT_, Index_, false, ElementsPerLane_ / 2>(simd_emulator_._lane_0);
					}
					else
					{
						return retrieve_emulated_dual_lane_simd_element<OutT_, Index_ - ElementsPerLane_, false, ElementsPerLane_ / 2>(simd_emulator_._lane_0);
					}
				}
				else if constexpr (is_single_lane_simd_emulator<LaneT_>::value)
				{
					// Input: 256-bit emulator
					// Output: From one of the 128-bit lanes which are emulated
					// --- Defer to retrieve_emulated_single_lane_simd_element for the correct lane
					// --- `false` for allowing theoretical indices as they are already handled here, so using theoretical indices would be an invalid result
					if constexpr (is_lo_lane)
					{
						return retrieve_emulated_single_lane_simd_element<OutT_, Index_, false>(simd_emulator_._lane_0);
					}
					else
					{
						return retrieve_emulated_single_lane_simd_element<OutT_, Index_ - ElementsPerLane_, false>(simd_emulator_._lane_0);
					}
				}
				else
				{
					// Input: 512-bit or 256-bit emulator
					// Output: From 256-bit or 128-bit SIMD register
					// Output is from an actual SIMD register, so defer output to the templatised get_index with the correct lane
					if constexpr (is_lo_lane)
					{
						return EmuSIMD::get_index<Index_, typename std::remove_cvref<OutT_>::type, per_element_width>(simd_emulator_._lane_0);
					}
					else
					{
						return EmuSIMD::get_index<Index_ - ElementsPerLane_, typename std::remove_cvref<OutT_>::type, per_element_width>(simd_emulator_._lane_1);
					}
				}
			}
			else
			{
				if constexpr (AllowTheoreticalIndices_)
				{
					return typename std::remove_cvref<OutT_>::type(0);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, Index_>(), "INTERNAL EMUSIMD ERROR: `retrieve_emulated_dual_lane_simd_element` called with an out-of-range index, with theoretical indices disallowed.");
				}
			}
		}
#pragma endregion

#pragma region EMULATED_SETS_AND_LOADS
		template<std::size_t NumElements_, EmuConcepts::Arithmetic T_>
		constexpr inline single_lane_simd_emulator<NumElements_, T_> set_single_lane_simd_emulator() noexcept
		{
			return single_lane_simd_emulator<NumElements_, T_>();
		}

		template<std::size_t EmulatedWidth_, class LaneT_>
		constexpr inline dual_lane_simd_emulator<EmulatedWidth_, LaneT_> set_dual_lane_simd_emulator() noexcept
		{
			return dual_lane_simd_emulator<EmulatedWidth_, LaneT_>();
		}

		template<std::size_t NumElements_, EmuConcepts::Arithmetic T_, EmuConcepts::Arithmetic...Args_>
		constexpr inline single_lane_simd_emulator<NumElements_, T_> set_single_lane_simd_emulator(Args_&&...args_) noexcept
		{
			return single_lane_simd_emulator<NumElements_, T_>(std::forward<Args_>(args_)...);
		}

		template<class OutSIMDRegister_, std::size_t PerElementWidthIfGenericInt_, std::size_t Offset_, EmuConcepts::Arithmetic...Args_, std::size_t...ElementIndices_>
		constexpr inline OutSIMDRegister_ set_simd_register_with_offset_tuple(std::tuple<Args_...>& args_tuple_, std::index_sequence<ElementIndices_...> element_indices_)
		{
			return EmuSIMD::setr<OutSIMDRegister_, PerElementWidthIfGenericInt_>
			(
				EmuCore::TMP::forward_tuple_index<Offset_ + ElementIndices_>(args_tuple_)...
			);
		}

		template<class OutSingleLaneEmulator_, std::size_t Offset_, EmuConcepts::Arithmetic...Args_, std::size_t...ElementIndices_>
		constexpr inline OutSingleLaneEmulator_ set_single_lane_simd_emulator_with_offset_tuple(std::tuple<Args_...>& args_tuple_, std::index_sequence<ElementIndices_...> element_indices_)
		{
			using _out_t = typename OutSingleLaneEmulator_::_value_type;
			return OutSingleLaneEmulator_
			(
				static_cast<_out_t>
				(
					EmuCore::TMP::forward_tuple_index<Offset_ + ElementIndices_>(args_tuple_)
				)...
			);
		}

		template<bool IsSetr_, std::size_t EmulatedWidth_, class LaneT_, std::size_t Offset_, std::size_t Layer_, EmuConcepts::Arithmetic...Args_, std::size_t...LaneIndices_>
		constexpr inline dual_lane_simd_emulator<EmulatedWidth_, LaneT_> set_dual_lane_simd_emulator_with_offset_tuple(std::tuple<Args_...>& args_tuple_, std::index_sequence<LaneIndices_...> lane_indices_)
		{
			constexpr std::size_t num_args = sizeof...(Args_);
			constexpr std::size_t args_per_lane = num_args / (2 << Layer_);
			if constexpr (is_dual_lane_simd_emulator<LaneT_>::value)
			{
				// Contains two dual-lane emulators
				using lane_lane_type = typename LaneT_::lane_type;
				using lanes_index_sequence = typename std::conditional<IsSetr_, std::make_index_sequence<2>, EmuCore::TMP::make_reverse_index_sequence<2>>::type;
				return dual_lane_simd_emulator<EmulatedWidth_, LaneT_>
				(
					set_dual_lane_simd_emulator_with_offset_tuple<EmulatedWidth_ / 2, lane_lane_type, Offset_ + (LaneIndices_ * args_per_lane), Layer_ + 1>
					(
						args_tuple_,
						lanes_index_sequence()
					)...
				);
			}
			else if constexpr (is_single_lane_simd_emulator<LaneT_>::value)
			{
				// Contains two single-lane emulators
				using per_lane_index_sequence = typename std::conditional<IsSetr_, std::make_index_sequence<args_per_lane>, EmuCore::TMP::make_reverse_index_sequence<args_per_lane>>::type;
				return dual_lane_simd_emulator<EmulatedWidth_, LaneT_>
				(
					set_single_lane_simd_emulator_with_offset_tuple<LaneT_, Offset_ + (LaneIndices_ * args_per_lane)>
					(
						args_tuple_,
						per_lane_index_sequence()
					)...
				);
			}
			else
			{
				// Contains two SIMD registers
				constexpr std::size_t total_width_including_parent = (EmulatedWidth_ << Layer_);
				constexpr std::size_t per_element_width = total_width_including_parent / num_args;
				if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<per_element_width>())
				{
					using per_lane_index_sequence = typename std::conditional<IsSetr_, std::make_index_sequence<args_per_lane>, EmuCore::TMP::make_reverse_index_sequence<args_per_lane>>::type;
					return dual_lane_simd_emulator<EmulatedWidth_, LaneT_>
					(
						set_simd_register_with_offset_tuple<LaneT_, per_element_width, Offset_ + (LaneIndices_ * args_per_lane)>
						(
							args_tuple_,
							per_lane_index_sequence()
						)...
					);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<std::size_t, per_element_width>(),
						"INTERNAL EMUSIMD ERROR: Invalid per_element_width calculated from arguments whilst trying to execute set_dual_lane_simd_emulator_with_offset_tuple."
					);
				}
			}
		}

		template<bool IsSetr_, std::size_t EmulatedWidth_, class LaneT_, EmuConcepts::Arithmetic...Args_, std::size_t...LaneIndices_>
		constexpr inline dual_lane_simd_emulator<EmulatedWidth_, LaneT_> set_dual_lane_simd_emulator(std::tuple<Args_...>& args_tuple_, std::index_sequence<LaneIndices_...> lane_indices_)
		{
			constexpr std::size_t num_args = sizeof...(Args_);
			constexpr std::size_t args_per_lane = num_args / 2;
			if constexpr (is_dual_lane_simd_emulator<LaneT_>::value)
			{
				// 2 dual-lane emulators (most probably constructing a 512-bit in this case)
				using lanes_index_sequence = typename std::conditional<IsSetr_, std::make_index_sequence<2>, EmuCore::TMP::make_reverse_index_sequence<2>>::type;
				using lane_lane_type = typename LaneT_::lane_type;
				return dual_lane_simd_emulator<EmulatedWidth_, LaneT_>
				(
					set_dual_lane_simd_emulator_with_offset_tuple<IsSetr_, EmulatedWidth_ / 2, lane_lane_type, LaneIndices_ * args_per_lane, 1>
					(
						args_tuple_,
						lanes_index_sequence()
					)...
				);
			}
			else if constexpr (is_single_lane_simd_emulator<LaneT_>::value)
			{
				// 2 single-lane emulators (most probably constructing a 256-bit in this case)
				using per_lane_index_sequence = typename std::conditional<IsSetr_, std::make_index_sequence<args_per_lane>, EmuCore::TMP::make_reverse_index_sequence<args_per_lane>>::type;
				return dual_lane_simd_emulator<EmulatedWidth_, LaneT_>
				(
					set_single_lane_simd_emulator_with_offset_tuple<LaneT_, LaneIndices_ * args_per_lane>
					(
						args_tuple_,
						per_lane_index_sequence()
					)...
				);
			}
			else
			{
				// 2 actual SIMD registers
				constexpr std::size_t per_element_width = EmulatedWidth_ / num_args;
				using per_lane_index_sequence = typename std::conditional<IsSetr_, std::make_index_sequence<args_per_lane>, EmuCore::TMP::make_reverse_index_sequence<args_per_lane>>::type;
				if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<per_element_width>())
				{
					return dual_lane_simd_emulator<EmulatedWidth_, LaneT_>
					(
						set_simd_register_with_offset_tuple<LaneT_, per_element_width, (LaneIndices_ * args_per_lane)>
						(
							args_tuple_,
							per_lane_index_sequence()
						)...
					);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<std::size_t, per_element_width>(),
						"INTERNAL EMUSIMD ERROR: Invalid per_element_width calculated from arguments whilst trying to execute set_dual_lane_simd_emulator_with_offset_tuple."
					);
				}
			}
		}

		template<bool IsSetr_, std::size_t EmulatedWidth_, class LaneT_, EmuConcepts::Arithmetic...Args_>
		constexpr inline dual_lane_simd_emulator<EmulatedWidth_, LaneT_> set_dual_lane_simd_emulator(Args_&&...args_) noexcept
		{
			using lanes_index_sequence = typename std::conditional<IsSetr_, std::make_index_sequence<2>, EmuCore::TMP::make_reverse_index_sequence<2>>::type;
			auto args_tuple = std::forward_as_tuple(std::forward<Args_>(args_)...);
			return set_dual_lane_simd_emulator<IsSetr_, EmulatedWidth_, LaneT_>
			(
				args_tuple,
				lanes_index_sequence()
			);
		}

		template<std::size_t NumElements_, EmuConcepts::Arithmetic T_>
		constexpr inline single_lane_simd_emulator<NumElements_, T_> set1_single_lane_simd_emulator(const T_& set1_val_) noexcept
		{
			return single_lane_simd_emulator<NumElements_, T_>(set1_val_, std::make_index_sequence<NumElements_>());
		}

		template<std::size_t NumElements_, EmuConcepts::Arithmetic T_, EmuConcepts::Arithmetic BitMaskT_, EmuConcepts::Arithmetic WidthInt_, std::size_t...ReverseIndices_>
		constexpr inline single_lane_simd_emulator<NumElements_, T_> setmasked_single_lane_simd_emulator(const BitMaskT_& bit_mask_, const WidthInt_& all_bits_, std::index_sequence<ReverseIndices_...> reverse_indices_) noexcept
		{
			return single_lane_simd_emulator<NumElements_, T_>
			(
				std::bit_cast<T_>(((bit_mask_ & (1 << ReverseIndices_)) >> ReverseIndices_) * all_bits_)...
			);
		}

		template<std::size_t NumElements_, EmuConcepts::Arithmetic T_, EmuConcepts::Arithmetic BitMaskT_>
		constexpr inline single_lane_simd_emulator<NumElements_, T_> setmasked_single_lane_simd_emulator(const BitMaskT_& bit_mask_)
		{
			constexpr std::size_t element_byte_width = sizeof(T_);
			using _width_uint = EmuCore::TMP::uint_of_size_t<element_byte_width>;
			if constexpr (!EmuCore::TMP::is_emu_tmp_err<_width_uint>::value)
			{
				constexpr _width_uint all_bits = std::numeric_limits<_width_uint>::max();
				return setmasked_single_lane_simd_emulator<NumElements_, T_>
				(
					bit_mask_,
					all_bits,
					EmuCore::TMP::make_reverse_index_sequence<NumElements_>()
				);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<T_, _width_uint>(),
					"INTERNAL EMUSIMD ERROR: A `setmasked` call cannot be implemented by the emulator as it cannot determine an unsigned integer representing all 1s for the correct width in the output register."
				);
			}
		}

		template<std::size_t NumElements_, EmuConcepts::Arithmetic T_>
		constexpr inline single_lane_simd_emulator<NumElements_, T_> load_single_lane_simd_emulator(const void* p_to_load_)
		{
			return single_lane_simd_emulator<NumElements_, T_>(p_to_load_);
		}

		template<std::size_t EmulatedWidth_, class LaneT_>
		constexpr inline dual_lane_simd_emulator<EmulatedWidth_, LaneT_> load_dual_lane_simd_emulator(const void* p_to_load_)
		{
			constexpr std::size_t bytes_per_lane = (EmulatedWidth_ / 2) / 8;
			const unsigned char* p_in_bytes = reinterpret_cast<const unsigned char*>(p_to_load_);
			if constexpr (is_dual_lane_simd_emulator<LaneT_>::value)
			{
				// Loading two 256-bit emulator lanes
				using _lane_lane_type = typename LaneT_::lane_type;
				constexpr std::size_t half_width = EmulatedWidth_ / 2;
				return dual_lane_simd_emulator<EmulatedWidth_, LaneT_>
				(
					load_dual_lane_simd_emulator<half_width, _lane_lane_type>(p_in_bytes),
					load_dual_lane_simd_emulator<half_width, _lane_lane_type>(p_in_bytes + bytes_per_lane)
				);

			}
			else if constexpr (is_single_lane_simd_emulator<LaneT_>::value)
			{
				// Loading two 128-bit emulator lanes
				using _value_type = typename LaneT_::_value_type;
				constexpr std::size_t lane_element_count = LaneT_::_num_elements;
				return dual_lane_simd_emulator<EmulatedWidth_, LaneT_>
				(
					load_single_lane_simd_emulator<lane_element_count, _value_type>(p_in_bytes),
					load_single_lane_simd_emulator<lane_element_count, _value_type>(p_in_bytes + bytes_per_lane)
				);
			}
			else
			{
				// Loading into register lanes
				return dual_lane_simd_emulator<EmulatedWidth_, LaneT_>
				(
					EmuSIMD::load<LaneT_>(p_in_bytes),
					EmuSIMD::load<LaneT_>(p_in_bytes + bytes_per_lane)
				);
			}
		}
#pragma endregion

#pragma region EMULATED_STORES
		template<EmuConcepts::Arithmetic OutMask_, std::size_t NumElements_, EmuConcepts::Arithmetic T_, std::size_t...Indices_>
		[[nodiscard]] constexpr inline auto emulate_simd_movemask(const single_lane_simd_emulator<NumElements_, T_>& simd_emulator_, std::index_sequence<Indices_...> indices_) noexcept
			-> typename std::remove_cvref<OutMask_>::type
		{
			return 
			(
				(
					EmuCore::ArithmeticHelpers::get_most_significant_bit<OutMask_>
					(
						retrieve_emulated_single_lane_simd_element<T_, Indices_, false>(simd_emulator_)
					) << Indices_
				) | ...
			);
		}

		template<EmuConcepts::Arithmetic OutMask_, std::size_t NumIndices_, std::size_t EmulatedWidth_, class LaneT_>
		[[nodiscard]] constexpr inline auto emulate_simd_movemask(const dual_lane_simd_emulator<EmulatedWidth_, LaneT_>& simd_emulator_) noexcept
			-> typename std::remove_cvref<OutMask_>::type
		{
			constexpr std::size_t half_count = NumIndices_ / 2;
			if constexpr (is_single_lane_simd_emulator<LaneT_>::value)
			{
				using _half_index_sequence = std::make_index_sequence<half_count>;
				return
				(
					(emulate_simd_movemask<OutMask_>(simd_emulator_._lane_1, _half_index_sequence()) << half_count) |
					emulate_simd_movemask<OutMask_>(simd_emulator_._lane_0, _half_index_sequence())
				);
			}
			else if constexpr (is_dual_lane_simd_emulator<LaneT_>::value)
			{
				return
				(
					(emulate_simd_movemask<OutMask_, half_count>(simd_emulator_._lane_1) << half_count) |
					emulate_simd_movemask<OutMask_, half_count>(simd_emulator_._lane_0)
				);
			}
			else
			{
				constexpr std::size_t per_element_width = EmulatedWidth_ / NumIndices_;
				return
				(
					(static_cast<OutMask_>(EmuSIMD::movemask<per_element_width>(simd_emulator_._lane_1)) << half_count) |
					static_cast<OutMask_>(EmuSIMD::movemask<per_element_width>(simd_emulator_._lane_0))
				);
			}
		}

		template<std::size_t NumElements_, EmuConcepts::Arithmetic T_>
		constexpr inline void emulate_simd_store(const single_lane_simd_emulator<NumElements_, T_>& simd_emulator_, void* p_out_)
		{
			constexpr std::size_t num_bytes = 128 / 8; // Guaranteed to be 128-bit as we only use single_lane_simd_emulator for 128-bit
			memcpy(p_out_, simd_emulator_._data.data(), num_bytes);
		}

		template<std::size_t EmulatedWidth_, class LaneT_>
		constexpr inline void emulate_simd_store(const dual_lane_simd_emulator<EmulatedWidth_, LaneT_>& simd_emulator_, void* p_out_)
		{
			unsigned char* p_out_bytes = reinterpret_cast<unsigned char*>(p_out_);
			if constexpr (EmulatedWidth_ == 256)
			{
				// Storing 256-bit emulator
				constexpr std::size_t lane_bytes = 128 / 8;
				if constexpr (is_simd_emulator<LaneT_>::value)
				{
					// Storing two 128-bit emulators
					emulate_simd_store(simd_emulator_._lane_0, p_out_bytes);
					emulate_simd_store(simd_emulator_._lane_1, p_out_bytes + lane_bytes);
				}
				else
				{
					// Storing two 128-bit registers
					EmuSIMD::store(simd_emulator_._lane_0, p_out_bytes);
					EmuSIMD::store(simd_emulator_._lane_1, p_out_bytes + lane_bytes);
				}
			}
			else
			{
				// Storing 512-bit emulator
				if constexpr (is_simd_emulator<LaneT_>::value)
				{
					// Storing two 256-bit emulators
					using _lane_lane_type = typename LaneT_::lane_type;
					constexpr std::size_t lane_bytes_128 = 128 / 8;
					if constexpr (is_simd_emulator<_lane_lane_type>::value)
					{
						// Storing four 128-bit emulators
						emulate_simd_store(simd_emulator_._lane_0._lane_0, p_out_bytes);
						emulate_simd_store(simd_emulator_._lane_0._lane_1, p_out_bytes += lane_bytes_128);
						emulate_simd_store(simd_emulator_._lane_1._lane_0, p_out_bytes += lane_bytes_128);
						emulate_simd_store(simd_emulator_._lane_1._lane_1, p_out_bytes + lane_bytes_128);
					}
					else
					{
						// Storing 4 128-bit registers
						EmuSIMD::store(simd_emulator_._lane_0._lane_0, p_out_bytes);
						EmuSIMD::store(simd_emulator_._lane_0._lane_1, p_out_bytes += lane_bytes_128);
						EmuSIMD::store(simd_emulator_._lane_1._lane_0, p_out_bytes += lane_bytes_128);
						EmuSIMD::store(simd_emulator_._lane_1._lane_1, p_out_bytes + lane_bytes_128);
					}
				}
				else
				{
					// Storing two 256-bit registers
					constexpr std::size_t lane_bytes = 256 / 8;
					EmuSIMD::store(simd_emulator_._lane_0, p_out_bytes);
					EmuSIMD::store(simd_emulator_._lane_1, p_out_bytes + lane_bytes);
				}
			}
		}
#pragma endregion

#pragma region EMULATED_BASIC_GENERIC_OPS
		template<class Func_, std::size_t NumElements_, EmuConcepts::Arithmetic T_, std::size_t...OutIndices_>
		constexpr inline single_lane_simd_emulator<NumElements_, T_> emulate_simd_basic(Func_&& func_, const single_lane_simd_emulator<NumElements_, T_>& simd_emulator_, std::index_sequence<OutIndices_...> out_indices_)
		{
			static_assert(sizeof...(OutIndices_) == NumElements_, "INTERNAL EMUSIMD ERROR: `emulate_simd_basic` called with a number of indices not equal to the number of elements in the output emulated register.");
			if constexpr(std::is_lvalue_reference_v<Func_>)
			{
				return single_lane_simd_emulator<NumElements_, T_>
				(
					func_(retrieve_emulated_single_lane_simd_element<T_, OutIndices_, false>(simd_emulator_))...
				);
			}
			else
			{
				auto& func_ref = EmuCore::TMP::lval_ref_cast<Func_>(std::forward<Func_>(func_));
				return single_lane_simd_emulator<NumElements_, T_>
				(
					func_ref(retrieve_emulated_single_lane_simd_element<T_, OutIndices_, false>(simd_emulator_))...
				);
			}
		}

		template<class Func_, std::size_t NumElements_, EmuConcepts::Arithmetic T_, std::size_t...OutIndices_>
		constexpr inline single_lane_simd_emulator<NumElements_, T_> emulate_simd_basic
		(
			Func_&& func_,
			const single_lane_simd_emulator<NumElements_, T_>& simd_emulator_a_,
			const single_lane_simd_emulator<NumElements_, T_>& simd_emulator_b_,
			std::index_sequence<OutIndices_...> out_indices_
		)
		{
			static_assert(sizeof...(OutIndices_) == NumElements_, "INTERNAL EMUSIMD ERROR: `emulate_simd_basic` called with a number of indices not equal to the number of elements in the output emulated register.");
			if constexpr(std::is_lvalue_reference_v<Func_>)
			{
				return single_lane_simd_emulator<NumElements_, T_>
				(
					func_
					(
						retrieve_emulated_single_lane_simd_element<T_, OutIndices_, false>(simd_emulator_a_),
						retrieve_emulated_single_lane_simd_element<T_, OutIndices_, false>(simd_emulator_b_)
					)...
				);
			}
			else
			{
				auto& func_ref = EmuCore::TMP::lval_ref_cast<Func_>(std::forward<Func_>(func_));
				return single_lane_simd_emulator<NumElements_, T_>
				(
					func_ref
					(
						retrieve_emulated_single_lane_simd_element<T_, OutIndices_, false>(simd_emulator_a_),
						retrieve_emulated_single_lane_simd_element<T_, OutIndices_, false>(simd_emulator_b_)
					)...
				);
			}
		}

		template<class Func_, std::size_t NumElements_, EmuConcepts::Arithmetic T_, std::size_t...OutIndices_>
		constexpr inline single_lane_simd_emulator<NumElements_, T_> emulate_simd_basic
		(
			Func_&& func_,
			const single_lane_simd_emulator<NumElements_, T_>& simd_emulator_a_,
			const single_lane_simd_emulator<NumElements_, T_>& simd_emulator_b_,
			const single_lane_simd_emulator<NumElements_, T_>& simd_emulator_c_,
			std::index_sequence<OutIndices_...> out_indices_
		)
		{
			static_assert(sizeof...(OutIndices_) == NumElements_, "INTERNAL EMUSIMD ERROR: `emulate_simd_basic` called with a number of indices not equal to the number of elements in the output emulated register.");
			if constexpr(std::is_lvalue_reference_v<Func_>)
			{
				return single_lane_simd_emulator<NumElements_, T_>
				(
					func_
					(
						retrieve_emulated_single_lane_simd_element<T_, OutIndices_, false>(simd_emulator_a_),
						retrieve_emulated_single_lane_simd_element<T_, OutIndices_, false>(simd_emulator_b_),
						retrieve_emulated_single_lane_simd_element<T_, OutIndices_, false>(simd_emulator_c_)
					)...
				);
			}
			else
			{
				auto& func_ref = EmuCore::TMP::lval_ref_cast<Func_>(std::forward<Func_>(func_));
				return single_lane_simd_emulator<NumElements_, T_>
				(
					func_ref
					(
						retrieve_emulated_single_lane_simd_element<T_, OutIndices_, false>(simd_emulator_a_),
						retrieve_emulated_single_lane_simd_element<T_, OutIndices_, false>(simd_emulator_b_),
						retrieve_emulated_single_lane_simd_element<T_, OutIndices_, false>(simd_emulator_c_)
					)...
				);
			}
		}

		template<class LaneFunc_, std::size_t EmulatedWidth_, class LaneT_>
		constexpr inline dual_lane_simd_emulator<EmulatedWidth_, LaneT_> emulate_simd_basic(const LaneFunc_& lane_func_, const dual_lane_simd_emulator<EmulatedWidth_, LaneT_>& simd_emulator_)
		{
			return dual_lane_simd_emulator<EmulatedWidth_, LaneT_>
			(
				lane_func_(simd_emulator_._lane_0),
				lane_func_(simd_emulator_._lane_1)
			);
		}

		template<class LaneFunc_, std::size_t EmulatedWidth_, class LaneT_>
		constexpr inline dual_lane_simd_emulator<EmulatedWidth_, LaneT_> emulate_simd_basic
		(
			const LaneFunc_& lane_func_,
			const dual_lane_simd_emulator<EmulatedWidth_, LaneT_>& simd_emulator_a_,
			const dual_lane_simd_emulator<EmulatedWidth_, LaneT_>& simd_emulator_b_
		)
		{
			return dual_lane_simd_emulator<EmulatedWidth_, LaneT_>
			(
				lane_func_(simd_emulator_a_._lane_0, simd_emulator_b_._lane_0),
				lane_func_(simd_emulator_a_._lane_1, simd_emulator_b_._lane_1)
			);
		}

		template<class LaneFunc_, std::size_t EmulatedWidth_, class LaneT_>
		constexpr inline dual_lane_simd_emulator<EmulatedWidth_, LaneT_> emulate_simd_basic
		(
			const LaneFunc_& lane_func_,
			const dual_lane_simd_emulator<EmulatedWidth_, LaneT_>& simd_emulator_a_,
			const dual_lane_simd_emulator<EmulatedWidth_, LaneT_>& simd_emulator_b_,
			const dual_lane_simd_emulator<EmulatedWidth_, LaneT_>& simd_emulator_c_
		)
		{
			return dual_lane_simd_emulator<EmulatedWidth_, LaneT_>
			(
				lane_func_(simd_emulator_a_._lane_0, simd_emulator_b_._lane_0, simd_emulator_c_._lane_0),
				lane_func_(simd_emulator_a_._lane_1, simd_emulator_b_._lane_1, simd_emulator_c_._lane_1)
			);
		}
#pragma endregion

#pragma region EMULATED_NON_CONVERTING_CASTS
		template<std::size_t OutElements_, EmuConcepts::Arithmetic OutT_, std::size_t InElements_, EmuConcepts::Arithmetic InT_>
		[[nodiscard]] constexpr inline single_lane_simd_emulator<OutElements_, OutT_> emulate_simd_cast_same_width(const single_lane_simd_emulator<InElements_, InT_>& in_)
		{
			if constexpr (OutElements_ == InElements_ && std::is_same_v<OutT_, InT_>)
			{
				// Same type so just return immediately
				return in_;
			}
			else
			{
				auto out_emulator = single_lane_simd_emulator<OutElements_, OutT_>();
				memcpy(out_emulator._data.data(), in_._data.data(), sizeof(InT_) * InElements_);
				return out_emulator;
			}
		}

		template<EmuConcepts::Arithmetic OutLaneT_, std::size_t EmulatedWidth_, EmuConcepts::Arithmetic InLaneT_>
		[[nodiscard]] constexpr inline dual_lane_simd_emulator<EmulatedWidth_, OutLaneT_> emulate_simd_cast_same_width(const dual_lane_simd_emulator<EmulatedWidth_, InLaneT_>& in_)
		{
			if constexpr (std::is_same_v<OutLaneT_, InLaneT_>)
			{
				// Same type so just return immediately
				return in_;
			}
			else
			{
				return dual_lane_simd_emulator<EmulatedWidth_, OutLaneT_>
				(
					EmuSIMD::cast<OutLaneT_>(in_._lane_0),
					EmuSIMD::cast<OutLaneT_>(in_._lane_1)
				);
			}
		}

		template<class Out_, std::size_t InElements_, EmuConcepts::Arithmetic InT_>
		[[nodiscard]] constexpr inline Out_ emulate_simd_cast_greater_width(const single_lane_simd_emulator<InElements_, InT_>& in_)
		{
			if constexpr (is_simd_emulator<Out_>::value)
			{
				// 128-bit emulator -> 256-bit or 512-bit emulator
				// --- This will only be used for the lo-lane (and perhaps even only the lo-half of that), so just cast this to lo-lane and default hi-lane
				return Out_(EmuSIMD::cast<typename Out_::lane_type>(in_));
			}
			else
			{
				// 128-bit emulator -> 256-bit or 512-bit register
				// --- Just copy the emulated register's 128-bits to the lo end of the output register and return that
				// --- This should never really be possible
				constexpr std::size_t copy_bytes = 128 / 8;
				Out_ out_register = Out_();
				memcpy(&out_register, in_._data.data(), copy_bytes);
				return out_register;
			}
		}

		template<class Out_, std::size_t EmulatedWidth_, typename LaneT_>
		[[nodiscard]] constexpr inline Out_ emulate_simd_cast_greater_width(const dual_lane_simd_emulator<EmulatedWidth_, LaneT_>& in_)
		{
			// Guaranteed 256-bit -> 512-bit as possible values are 128, 256, 512, and 128-bit is guaranteed to never be `dual_lane_simd_emulator`
			constexpr std::size_t bytes_per_128_chunk = 128 / 8;
			using _lane_type = typename std::remove_cvref<decltype(in_._lane_0)>::type;

			if constexpr (is_simd_emulator<Out_>::value)
			{
				// 256-bit emulator -> 512-bit emulator
				// --- Cast input emulator to the lo-lane and default the hi-lane
				return Out_(EmuSIMD::cast<typename Out_::lane_type>(in_));
			}
			else
			{
				// 256-bit emulator -> 512-bit register
				// --- Just copy the emulated register's 256-bits to the lo end of the output register and return that
				// --- This should never really be possible
				Out_ out_register = Out_();
				if constexpr (is_simd_emulator<_lane_type>::value)
				{
					// 128-bit lanes are emulated, so copy the data chunks of the emulator to the register
					memcpy(&out_register, in_._lane_0._data.data(), bytes_per_128_chunk);
					memcpy(reinterpret_cast<std::byte*>(&out_register) + bytes_per_128_chunk, in_._lane_1._data.data(), bytes_per_128_chunk);
				}
				else
				{
					// 128-bit lanes are actual registers, so copy 128 bits them directly
					memcpy(&out_register, &(in_._lane_0), bytes_per_128_chunk);
					memcpy(reinterpret_cast<std::byte*>(&out_register) + bytes_per_128_chunk, &(in_._lane_1), bytes_per_128_chunk);
				}
				return out_register;
			}
		}

		template<class Out_, std::size_t EmulatedWidth_, class LaneT_>
		[[nodiscard]] constexpr inline Out_ emulate_simd_cast_lesser_width(const dual_lane_simd_emulator<EmulatedWidth_, LaneT_>& in_)
		{
			// When becoming a lesser width, we're guaranteed to only need the lo-lane, so just defer to the cast template for that
			return EmuSIMD::cast<Out_>(in_._lane_0);
		}
#pragma endregion

#pragma region EMULATED_CONVERSIONS
		template<std::size_t Index_, std::size_t InvalidBegin_, bool CanMove_, class DefaultT_, class T_>
		[[nodiscard]] constexpr inline decltype(auto) _retrieve_data_or_default(T_* p_data_)
		{
			if constexpr (Index_ < InvalidBegin_)
			{
				if constexpr (CanMove_)
				{
					return std::move(*(p_data_ + Index_));
				}
				else
				{
					return *(p_data_ + Index_);
				}
			}
			else
			{
				return DefaultT_();
			}
		}

		template<class Out_, typename OutT_, std::size_t OutPerElementWidth_, EmuConcepts::Arithmetic InT_, std::size_t InSize_, std::size_t...OutIndices_>
		[[nodiscard]] constexpr inline auto emulate_cvt(const single_lane_simd_emulator<InSize_, InT_>& in_emulator_, std::index_sequence<OutIndices_...> out_indices_)
			-> typename std::remove_cvref<Out_>::type
		{
			return EmuSIMD::setr<typename std::remove_cvref<Out_>::type, OutPerElementWidth_>
			(
				retrieve_emulated_single_lane_simd_element<OutT_, OutIndices_, true>(in_emulator_)...
			);
		}

		template<class Out_, typename OutT_, std::size_t OutPerElementWidth_, bool OutSigned_, std::size_t InElementCount_, bool InSigned_, typename InT_, class LaneT_, std::size_t EmulatedWidth_, std::size_t...OutIndices_>
		[[nodiscard]] constexpr inline auto emulate_cvt(const dual_lane_simd_emulator<EmulatedWidth_, LaneT_>& in_emulator_, std::index_sequence<OutIndices_...> out_indices_)
			-> typename std::remove_cvref<Out_>::type
		{
			if constexpr (std::is_same_v<typename std::remove_cvref<Out_>::type, LaneT_>)
			{
				// Guaranteed that we're converting to half-width of this emulator, so just return the lo half directly
				return in_emulator_._lane_0;
			}
			else if constexpr (std::is_same_v<OutT_, InT_>)
			{
				// Can just do a simple cast since memory representation is guaranteed to be the same
				return EmuSIMD::cast<typename std::remove_cvref<Out_>::type>(in_emulator_);
			}
			else
			{
				constexpr std::size_t output_count = sizeof...(OutIndices_);
				constexpr std::size_t in_half_count = InElementCount_ / 2;
				if constexpr (in_half_count >= output_count)
				{
					// Can perform entire conversion with just the lo-lane, so defer to that
					constexpr std::size_t per_element_width = EmulatedWidth_ / InElementCount_;
					return EmuSIMD::convert<typename std::remove_cvref<Out_>::type, per_element_width, InSigned_, OutPerElementWidth_, OutSigned_>
					(
						in_emulator_._lane_0
					);
				}
				else
				{
					// Outputting 128-bit emulator
					InT_ data_dump[InElementCount_];
					emulate_simd_store(in_emulator_, data_dump);
					return EmuSIMD::setr<typename std::remove_cvref<Out_>::type, OutPerElementWidth_>
					(
						_retrieve_data_or_default<OutIndices_, InElementCount_, true, OutT_>(data_dump)...
					);
				}
			}
		}
#pragma endregion

#pragma region CMPS
		template<std::size_t NumElements_, typename T_, class Cmp_, std::size_t...Indices_>
		[[nodiscard]] constexpr inline auto emulate_single_lane_cmp
		(
			const Cmp_& cmp_,
			const single_lane_simd_emulator<NumElements_, T_>& lhs_,
			const single_lane_simd_emulator<NumElements_, T_>& rhs_,
			std::index_sequence<Indices_...> indices_
		)
		{
			if constexpr (EmuConcepts::Integer<T_>)
			{
				constexpr auto all_bits_one = EmuCore::ArithmeticHelpers::set_all_bits_one<T_>();
				return set_single_lane_simd_emulator<NumElements_, T_>
				(
					(
						cmp_
						(
							retrieve_emulated_single_lane_simd_element<T_, Indices_, false>(lhs_),
							retrieve_emulated_single_lane_simd_element<T_, Indices_, false>(rhs_)
						) * all_bits_one
					)...
				);
			}
			else
			{
				using _uint_type = EmuCore::TMP::uint_of_size_t<sizeof(T_)>;
				constexpr auto all_bits_one = EmuCore::ArithmeticHelpers::set_all_bits_one<_uint_type>();
				return set_single_lane_simd_emulator<NumElements_, T_>
				(
					std::bit_cast<T_>
					(
						cmp_
						(
							retrieve_emulated_single_lane_simd_element<T_, Indices_, false>(lhs_),
							retrieve_emulated_single_lane_simd_element<T_, Indices_, false>(rhs_)
						) * all_bits_one
					)...
				);
			}
		}
#pragma endregion

#pragma region FUNCTORS
		template<typename T_>
		struct blendv_emulator_func
		{
			[[nodiscard]] constexpr inline decltype(auto) operator()(const T_& a_, const T_& b_, const T_& mask_) const
			{
				return EmuCore::ArithmeticHelpers::get_most_significant_bit<bool>(mask_) ? b_ : a_;
			}
		};

		template<typename T_, bool AddFirst_, class Adder_, class Subtractor_>
		struct alternating_add_subtract_func
		{
		private:
			using _counter_type = typename std::conditional
			<
				(EmuConcepts::Integer<T_>),
				T_,
				EmuCore::TMP::int_of_size_t<sizeof(T_)>
			>::type;

			[[nodiscard]] static constexpr inline _counter_type _counter_starting_val() noexcept
			{
				if constexpr ((EmuConcepts::UnsignedArithmetic<T_>))
				{
					return _counter_type(0);
				}
				else
				{
					if constexpr (AddFirst_)
					{
						return _counter_type(1);
					}
					else
					{
						return _counter_type(-1);
					}
				}
			}

			_counter_type _counter;

		public:
			constexpr inline alternating_add_subtract_func() : _counter(_counter_starting_val())
			{
			}

			[[nodiscard]] constexpr inline decltype(auto) operator()(const T_& a_, const T_& b_)
			{
				if constexpr ((EmuConcepts::UnsignedArithmetic<T_>))
				{
					if ((_counter ^= 1))
					{
						// Even invocation [0, 2, 4, etc...]
						if constexpr (AddFirst_)
						{
							return Subtractor_()(a_, b_);
						}
						else
						{
							return Adder_()(a_, b_);
						}
					}
					else
					{
						// Odd invocation [1, 3, 5, etc...]
						if constexpr (AddFirst_)
						{
							return Adder_()(a_, b_);
						}
						else
						{
							return Subtractor_()(a_, b_);
						}
					}
				}
				else
				{
					// Counter is used as a +/-1 multiplier here, flip its signedness to multiply `b_` value to switch between add/subtract using just adder
					// --- This approach avoids any branching unlike the unsigned variant
					constexpr _counter_type sign_mask = EmuCore::ArithmeticHelpers::set_all_bits_one<_counter_type>() & ~_counter_type(1);
					return Adder_()(a_, b_ * (_counter ^= sign_mask));
				}
			}
		};
#pragma endregion

#pragma region EMULATED_SHUFFLES
		template<std::size_t Index_, std::size_t NumElements_, typename T_>
		[[nodiscard]] constexpr inline decltype(auto) _select_emulated_movehl_value(const single_lane_simd_emulator<NumElements_, T_>& a_, const single_lane_simd_emulator<NumElements_, T_>& b_)
		{
			constexpr std::size_t half_elements = NumElements_ / 2;
			if constexpr (Index_ < half_elements)
			{
				constexpr std::size_t offset_index = Index_ + half_elements; // Offset the index so that we select the hi-half of b
				return retrieve_emulated_single_lane_simd_element<T_, offset_index, false>(b_);
			}
			else
			{
				return retrieve_emulated_single_lane_simd_element<T_, Index_, false>(a_); // Already hi indices, so no need for an offset
			}
		}

		template<std::size_t NumElements_, typename T_, std::size_t...Indices_>
		[[nodiscard]] constexpr inline auto emulated_movehl(const single_lane_simd_emulator<NumElements_, T_>& a_, const single_lane_simd_emulator<NumElements_, T_>& b_, std::index_sequence<Indices_...> indices_)
		{
			return single_lane_simd_emulator<NumElements_, T_>(_select_emulated_movehl_value<Indices_>(a_, b_)...);
		}

		template<std::size_t Index_, std::size_t NumElements_, typename T_>
		[[nodiscard]] constexpr inline decltype(auto) _select_emulated_movelh_value(const single_lane_simd_emulator<NumElements_, T_>& a_, const single_lane_simd_emulator<NumElements_, T_>& b_)
		{
			constexpr std::size_t half_elements = NumElements_ / 2;
			if constexpr (Index_ < half_elements)
			{
				return retrieve_emulated_single_lane_simd_element<T_, Index_, false>(a_); // Already lo indices, so no need for an offset
			}
			else
			{
				constexpr std::size_t offset_index = Index_ - half_elements; // Offset the index so that we select the lo-half of b
				return retrieve_emulated_single_lane_simd_element<T_, offset_index, false>(b_);
			}
		}

		template<std::size_t NumElements_, typename T_, std::size_t...Indices_>
		[[nodiscard]] constexpr inline auto emulated_movelh(const single_lane_simd_emulator<NumElements_, T_>& a_, const single_lane_simd_emulator<NumElements_, T_>& b_, std::index_sequence<Indices_...> indices_)
		{
			return single_lane_simd_emulator<NumElements_, T_>(_select_emulated_movelh_value<Indices_>(a_, b_)...);
		}
#pragma endregion

#pragma region EMULATED_MIN_MAX
		template<bool IsMax_, std::size_t NumElements_, typename T_, std::size_t...IndicesExcept0_>
		[[nodiscard]] constexpr inline auto emulate_horizontal_min_or_max(const single_lane_simd_emulator<NumElements_, T_>& a_, std::index_sequence<IndicesExcept0_...> indices_except_0_)
			-> single_lane_simd_emulator<NumElements_, T_>
		{
			T_ result = retrieve_emulated_single_lane_simd_element<T_, 0, false>(a_);
			auto update_result = [&result](const T_& val_)
			{
				using _cmp_func = typename std::conditional<IsMax_, std::greater_equal<T_>, std::less_equal<T_>>::type;
				if (_cmp_func()(val_, result))
				{
					result = val_;
				}
			};
			(update_result(retrieve_emulated_single_lane_simd_element<T_, IndicesExcept0_, false>(a_)), ...);
			return set1_single_lane_simd_emulator<NumElements_, T_>(result);
		}
#pragma endregion
	}

#pragma region REGISTER_ALIASES
#if EMU_SIMD_USE_128_REGISTERS
	/// <summary> Alias to a 128-bit register of 4 32-bit floating-point values. </summary>
	using f32x4 = __m128;
#else
	/// <summary> Alias to a 128-bit register of 4 32-bit floating-point values. </summary>
	using f32x4 = _underlying_impl::single_lane_simd_emulator<4, float>;
#endif

#if EMU_SIMD_USE_256_REGISTERS
	/// <summary> Alias to a 256-bit register of 8 32-bit floating-point values. </summary>
	using f32x8 = __m256;
#else
	/// <summary> Alias to a 256-bit register of 8 32-bit floating-point values. </summary>
	using f32x8 = _underlying_impl::dual_lane_simd_emulator<256, f32x4>;
#endif

#if EMU_SIMD_USE_512_REGISTERS
	/// <summary> Alias to a 512-bit register of 16 32-bit floating-point values. </summary>
	using f32x16 = __m512;
#else
	/// <summary> Alias to a 512-bit register of 16 32-bit floating-point values. </summary>
	using f32x16 = _underlying_impl::dual_lane_simd_emulator<512, f32x8>;
#endif


#if EMU_SIMD_USE_128_REGISTERS
	/// <summary> Alias to a 128-bit register of 2 64-bit floating-point values. </summary>
	using f64x2 = __m128d;
#else
	/// <summary> Alias to a 128-bit register of 2 64-bit floating-point values. </summary>
	using f64x2 = _underlying_impl::single_lane_simd_emulator<2, double>;
#endif

#if EMU_SIMD_USE_256_REGISTERS
	/// <summary> Alias to a 256-bit register of 4 64-bit floating-point values. </summary>
	using f64x4 = __m256d;
#else
	using f64x4 = _underlying_impl::dual_lane_simd_emulator<256, f64x2>;
#endif

#if EMU_SIMD_USE_512_REGISTERS
	/// <summary> Alias to a 512-bit register of 8 64-bit floating-point values. </summary>
	using f64x8 = __m512d;
#else
	/// <summary> Alias to a 512-bit register of 8 64-bit floating-point values. </summary>
	using f64x8 = _underlying_impl::dual_lane_simd_emulator<512, f64x4>;
#endif

#if EMU_SIMD_USE_128_REGISTERS
	/// <summary> Alias to a 128-bit register of 16 8-bit signed integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using i8x16 = __m128i;
#else
	/// <summary> Alias to a 128-bit register of 16 8-bit signed integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using i8x16 = _underlying_impl::single_lane_simd_emulator<16, std::int8_t>;
#endif

#if EMU_SIMD_USE_256_REGISTERS
	/// <summary> Alias to a 256-bit register of 32 8-bit signed integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using i8x32 = __m256i;
#else
	/// <summary> Alias to a 256-bit register of 32 8-bit signed integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using i8x32 = _underlying_impl::dual_lane_simd_emulator<256, i8x16>;
#endif

#if EMU_SIMD_USE_512_REGISTERS
	/// <summary> Alias to a 512-bit register of 64 8-bit signed integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using i8x64 = __m512i;
#else
	/// <summary> Alias to a 512-bit register of 64 8-bit signed integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using i8x64 = _underlying_impl::dual_lane_simd_emulator<512, i8x32>;
#endif

#if EMU_SIMD_USE_128_REGISTERS
	/// <summary> Alias to a 128-bit register of 8 16-bit signed integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using i16x8 = __m128i;
#else
	/// <summary> Alias to a 128-bit register of 8 16-bit signed integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using i16x8 = _underlying_impl::single_lane_simd_emulator<8, std::int16_t>;
#endif

#if EMU_SIMD_USE_256_REGISTERS
	/// <summary> Alias to a 256-bit register of 16 16-bit signed integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using i16x16 = __m256i;
#else
	/// <summary> Alias to a 256-bit register of 16 16-bit signed integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using i16x16 = _underlying_impl::dual_lane_simd_emulator<256, i16x8>;
#endif

#if EMU_SIMD_USE_512_REGISTERS
	/// <summary> Alias to a 512-bit register of 32 16-bit signed integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using i16x32 = __m512i;
#else
	/// <summary> Alias to a 512-bit register of 32 16-bit signed integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using i16x32 = _underlying_impl::dual_lane_simd_emulator<512, i16x16>;
#endif

#if EMU_SIMD_USE_128_REGISTERS
	/// <summary> Alias to a 128-bit register of 4 32-bit signed integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using i32x4 = __m128i;
#else
	/// <summary> Alias to a 128-bit register of 4 32-bit signed integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using i32x4 = _underlying_impl::single_lane_simd_emulator<4, std::int32_t>;
#endif

#if EMU_SIMD_USE_256_REGISTERS
	/// <summary> Alias to a 256-bit register of 8 32-bit signed integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using i32x8 = __m256i;
#else
	/// <summary> Alias to a 256-bit register of 8 32-bit signed integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using i32x8 = _underlying_impl::dual_lane_simd_emulator<256, i32x4>;
#endif

#if EMU_SIMD_USE_512_REGISTERS
	/// <summary> Alias to a 512-bit register of 16 32-bit signed integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using i32x16 = __m512i;
#else
	/// <summary> Alias to a 512-bit register of 16 32-bit signed integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using i32x16 = _underlying_impl::dual_lane_simd_emulator<512, i32x8>;
#endif

#if EMU_SIMD_USE_128_REGISTERS
	/// <summary> Alias to a 128-bit register of 2 64-bit signed integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using i64x2 = __m128i;
#else
	/// <summary> Alias to a 128-bit register of 2 64-bit signed integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using i64x2 = _underlying_impl::single_lane_simd_emulator<2, std::int64_t>;
#endif

#if EMU_SIMD_USE_256_REGISTERS
	/// <summary> Alias to a 256-bit register of 4 64-bit signed integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using i64x4 = __m256i;
#else
	/// <summary> Alias to a 256-bit register of 4 64-bit signed integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using i64x4 = _underlying_impl::dual_lane_simd_emulator<256, i64x2>;
#endif

#if EMU_SIMD_USE_512_REGISTERS
	/// <summary> Alias to a 512-bit register of 8 64-bit signed integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using i64x8 = __m512i;
#else
	/// <summary> Alias to a 512-bit register of 8 64-bit signed integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using i64x8 = _underlying_impl::dual_lane_simd_emulator<512, i64x4>;
#endif

#if EMU_SIMD_USE_128_REGISTERS
	/// <summary> Alias to a 128-bit register of 16 8-bit unsigned integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using u8x16 = __m128i;
#else
	/// <summary> Alias to a 128-bit register of 16 8-bit unsigned integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using u8x16 = _underlying_impl::single_lane_simd_emulator<16, std::uint8_t>;
#endif

#if EMU_SIMD_USE_256_REGISTERS
	/// <summary> Alias to a 256-bit register of 32 8-bit unsigned integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using u8x32 = __m256i;
#else
	/// <summary> Alias to a 256-bit register of 32 8-bit unsigned integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using u8x32 = _underlying_impl::dual_lane_simd_emulator<256, u8x16>;
#endif

#if EMU_SIMD_USE_512_REGISTERS
	/// <summary> Alias to a 512-bit register of 64 8-bit unsigned integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using u8x64 = __m512i;
#else
	/// <summary> Alias to a 512-bit register of 64 8-bit unsigned integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using u8x64 = _underlying_impl::dual_lane_simd_emulator<512, u8x32>;
#endif

#if EMU_SIMD_USE_128_REGISTERS
	/// <summary> Alias to a 128-bit register of 8 16-bit unsigned integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using u16x8 = __m128i;
#else
	/// <summary> Alias to a 128-bit register of 8 16-bit unsigned integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using u16x8 = _underlying_impl::single_lane_simd_emulator<8, std::uint16_t>;
#endif

#if EMU_SIMD_USE_256_REGISTERS
	/// <summary> Alias to a 256-bit register of 16 16-bit unsigned integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using u16x16 = __m256i;
#else
	/// <summary> Alias to a 256-bit register of 16 16-bit unsigned integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using u16x16 = _underlying_impl::dual_lane_simd_emulator<256, u16x8>;
#endif

#if EMU_SIMD_USE_512_REGISTERS
	/// <summary> Alias to a 512-bit register of 32 16-bit unsigned integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using u16x32 = __m512i;
#else
	/// <summary> Alias to a 512-bit register of 32 16-bit unsigned integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using u16x32 = _underlying_impl::dual_lane_simd_emulator<512, u16x16>;
#endif

#if EMU_SIMD_USE_128_REGISTERS
	/// <summary> Alias to a 128-bit register of 4 32-bit unsigned integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using u32x4 = __m128i;
#else
	/// <summary> Alias to a 128-bit register of 4 32-bit unsigned integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using u32x4 = _underlying_impl::single_lane_simd_emulator<4, std::uint32_t>;
#endif

#if EMU_SIMD_USE_256_REGISTERS
	/// <summary> Alias to a 256-bit register of 8 32-bit unsigned integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using u32x8 = __m256i;
#else
	/// <summary> Alias to a 256-bit register of 8 32-bit unsigned integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using u32x8 = _underlying_impl::dual_lane_simd_emulator<256, u32x4>;
#endif

#if EMU_SIMD_USE_512_REGISTERS
	/// <summary> Alias to a 512-bit register of 16 32-bit unsigned integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using u32x16 = __m512i;
#else
	/// <summary> Alias to a 512-bit register of 16 32-bit unsigned integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using u32x16 = _underlying_impl::dual_lane_simd_emulator<512, u32x8>;
#endif

#if EMU_SIMD_USE_128_REGISTERS
	/// <summary> Alias to a 128-bit register of 2 64-bit unsigned integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using u64x2 = __m128i;
#else
	/// <summary> Alias to a 128-bit register of 2 64-bit unsigned integer values. This may be a generic 128-bit integral register, such as if using x86 intrinsics. </summary>
	using u64x2 = _underlying_impl::single_lane_simd_emulator<2, std::uint64_t>;
#endif

#if EMU_SIMD_USE_256_REGISTERS
	/// <summary> Alias to a 256-bit register of 4 64-bit unsigned integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using u64x4 = __m256i;
#else
	/// <summary> Alias to a 256-bit register of 4 64-bit unsigned integer values. This may be a generic 256-bit integral register, such as if using x86 intrinsics. </summary>
	using u64x4 = _underlying_impl::dual_lane_simd_emulator<256, u64x2>;
#endif

#if EMU_SIMD_USE_512_REGISTERS
	/// <summary> Alias to a 512-bit register of 8 64-bit unsigned integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using u64x8 = __m512i;
#else
	/// <summary> Alias to a 512-bit register of 8 64-bit unsigned integer values. This may be a generic 512-bit integral register, such as if using x86 intrinsics. </summary>
	using u64x8 = _underlying_impl::dual_lane_simd_emulator<512, u64x4>;
#endif

#if EMU_SIMD_USE_128_REGISTERS
	/// <summary> Alias to a generic 128-bit integral register, which is per-element-width-and-signedness-agnostic. If there is no generic register, this will be `void`. </summary>
	using i128_generic = __m128i;
#else
	/// <summary> Alias to a generic 128-bit integral register, which is per-element-width-and-signedness-agnostic. If there is no generic register, this will be `void`. </summary>
	using i128_generic = void;
#endif

#if EMU_SIMD_USE_256_REGISTERS
	/// <summary> Alias to a generic 256-bit integral register, which is per-element-width-and-signedness-agnostic. If there is no generic register, this will be `void`. </summary>
	using i256_generic = __m256i;
#else
	/// <summary> Alias to a generic 256-bit integral register, which is per-element-width-and-signedness-agnostic. If there is no generic register, this will be `void`. </summary>
	using i256_generic = void;
#endif

	/// <summary> Alias to a generic 512-bit integral register, which is per-element-width-and-signedness-agnostic. If there is no generic register, this will be `void`. </summary>
#if EMU_SIMD_USE_512_REGISTERS
	using i512_generic = __m512i;
#else
	/// <summary> Alias to a generic 512-bit integral register, which is per-element-width-and-signedness-agnostic. If there is no generic register, this will be `void`. </summary>
	using i512_generic = void;
#endif
#pragma endregion

#pragma region ARG_ALIASES
	/// <summary> Alias to the expected argument type for a 128-bit register of 32-bit floating points. This will either be f32x4, or a constant reference to it. </summary>
	using f32x4_arg = EMU_SIMD_128_MAKE_ARG_TYPE(f32x4);
	/// <summary> Alias to the expected argument type for a 256-bit register of 32-bit floating points. This will either be f32x8, or a constant reference to it. </summary>
	using f32x8_arg = EMU_SIMD_256_MAKE_ARG_TYPE(f32x8);
	/// <summary> Alias to the expected argument type for a 512-bit register of 32-bit floating points. This will either be f32x16, or a constant reference to it. </summary>
	using f32x16_arg = EMU_SIMD_512_MAKE_ARG_TYPE(f32x16);

	/// <summary> Alias to the expected argument type for a 128-bit register of 64-bit floating points. This will either be f64x2, or a constant reference to it. </summary>
	using f64x2_arg = EMU_SIMD_128_MAKE_ARG_TYPE(f64x2);
	/// <summary> Alias to the expected argument type for a 256-bit register of 64-bit floating points. This will either be f64x4, or a constant reference to it. </summary>
	using f64x4_arg = EMU_SIMD_256_MAKE_ARG_TYPE(f64x4);
	/// <summary> Alias to the expected argument type for a 512-bit register of 64-bit floating points. This will either be f64x8, or a constant reference to it. </summary>
	using f64x8_arg = EMU_SIMD_512_MAKE_ARG_TYPE(f64x8);

	/// <summary> Alias to the expected argument type for a 128-bit register of 8-bit signed integers. This will either be i8x16, or a constant reference to it. </summary>
	using i8x16_arg = EMU_SIMD_128_MAKE_ARG_TYPE(i8x16);
	/// <summary> Alias to the expected argument type for a 256-bit register of 8-bit signed integers. This will either be i8x32, or a constant reference to it. </summary>
	using i8x32_arg = EMU_SIMD_256_MAKE_ARG_TYPE(i8x32);
	/// <summary> Alias to the expected argument type for a 512-bit register of 8-bit signed integers. This will either be i8x64, or a constant reference to it. </summary>
	using i8x64_arg = EMU_SIMD_512_MAKE_ARG_TYPE(i8x64);

	/// <summary> Alias to the expected argument type for a 128-bit register of 16-bit signed integers. This will either be i16x8, or a constant reference to it. </summary>
	using i16x8_arg = EMU_SIMD_128_MAKE_ARG_TYPE(i16x8);
	/// <summary> Alias to the expected argument type for a 256-bit register of 16-bit signed integers. This will either be i16x16, or a constant reference to it. </summary>
	using i16x16_arg = EMU_SIMD_256_MAKE_ARG_TYPE(i16x16);
	/// <summary> Alias to the expected argument type for a 512-bit register of 16-bit signed integers. This will either be i16x32, or a constant reference to it. </summary>
	using i16x32_arg = EMU_SIMD_512_MAKE_ARG_TYPE(i16x32);

	/// <summary> Alias to the expected argument type for a 128-bit register of 32-bit signed integers. This will either be i32x4, or a constant reference to it. </summary>
	using i32x4_arg = EMU_SIMD_128_MAKE_ARG_TYPE(i32x4);
	/// <summary> Alias to the expected argument type for a 256-bit register of 32-bit signed integers. This will either be i32x8, or a constant reference to it. </summary>
	using i32x8_arg = EMU_SIMD_256_MAKE_ARG_TYPE(i32x8);
	/// <summary> Alias to the expected argument type for a 512-bit register of 32-bit signed integers. This will either be i32x16, or a constant reference to it. </summary>
	using i32x16_arg = EMU_SIMD_512_MAKE_ARG_TYPE(i32x16);

	/// <summary> Alias to the expected argument type for a 128-bit register of 64-bit signed integers. This will either be i64x2, or a constant reference to it. </summary>
	using i64x2_arg = EMU_SIMD_128_MAKE_ARG_TYPE(i64x2);
	/// <summary> Alias to the expected argument type for a 256-bit register of 64-bit signed integers. This will either be i64x4, or a constant reference to it. </summary>
	using i64x4_arg = EMU_SIMD_256_MAKE_ARG_TYPE(i64x4);
	/// <summary> Alias to the expected argument type for a 512-bit register of 64-bit signed integers. This will either be i64x8, or a constant reference to it. </summary>
	using i64x8_arg = EMU_SIMD_512_MAKE_ARG_TYPE(i64x8);

	/// <summary> Alias to the expected argument type for a 128-bit register of 8-bit unsigned integers. This will either be u8x16, or a constant reference to it. </summary>
	using u8x16_arg = EMU_SIMD_128_MAKE_ARG_TYPE(u8x16);
	/// <summary> Alias to the expected argument type for a 256-bit register of 8-bit unsigned integers. This will either be u8x32, or a constant reference to it. </summary>
	using u8x32_arg = EMU_SIMD_256_MAKE_ARG_TYPE(u8x32);
	/// <summary> Alias to the expected argument type for a 512-bit register of 8-bit unsigned integers. This will either be u8x64, or a constant reference to it. </summary>
	using u8x64_arg = EMU_SIMD_512_MAKE_ARG_TYPE(u8x64);

	/// <summary> Alias to the expected argument type for a 128-bit register of 16-bit unsigned integers. This will either be u16x8, or a constant reference to it. </summary>
	using u16x8_arg = EMU_SIMD_128_MAKE_ARG_TYPE(u16x8);
	/// <summary> Alias to the expected argument type for a 256-bit register of 16-bit unsigned integers. This will either be u16x16, or a constant reference to it. </summary>
	using u16x16_arg = EMU_SIMD_256_MAKE_ARG_TYPE(u16x16);
	/// <summary> Alias to the expected argument type for a 512-bit register of 16-bit unsigned integers. This will either be u16x32, or a constant reference to it. </summary>
	using u16x32_arg = EMU_SIMD_512_MAKE_ARG_TYPE(u16x32);

	/// <summary> Alias to the expected argument type for a 128-bit register of 32-bit unsigned integers. This will either be u32x4, or a constant reference to it. </summary>
	using u32x4_arg = EMU_SIMD_128_MAKE_ARG_TYPE(u32x4);
	/// <summary> Alias to the expected argument type for a 256-bit register of 32-bit unsigned integers. This will either be u32x8, or a constant reference to it. </summary>
	using u32x8_arg = EMU_SIMD_256_MAKE_ARG_TYPE(u32x8);
	/// <summary> Alias to the expected argument type for a 512-bit register of 32-bit unsigned integers. This will either be u32x16, or a constant reference to it. </summary>
	using u32x16_arg = EMU_SIMD_512_MAKE_ARG_TYPE(u32x16);

	/// <summary> Alias to the expected argument type for a 128-bit register of 64-bit unsigned integers. This will either be u64x2, or a constant reference to it. </summary>
	using u64x2_arg = EMU_SIMD_128_MAKE_ARG_TYPE(u64x2);
	/// <summary> Alias to the expected argument type for a 256-bit register of 64-bit unsigned integers. This will either be u64x4, or a constant reference to it. </summary>
	using u64x4_arg = EMU_SIMD_256_MAKE_ARG_TYPE(u64x4);
	/// <summary> Alias to the expected argument type for a 512-bit register of 64-bit unsigned integers. This will either be u64x8, or a constant reference to it. </summary>
	using u64x8_arg = EMU_SIMD_512_MAKE_ARG_TYPE(u64x8);

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