#ifndef EMU_SIMD_UNDERLYING_ALIASES_H_INC_
#define EMU_SIMD_UNDERLYING_ALIASES_H_INC_ 1

#include "../../../../../EmuCore/CommonConcepts/Arithmetic.h"
#include "../../../../../EmuCore/CommonPreprocessor/Compiler.h"
#include "../../../../../EmuCore/TMPHelpers/Tuples.h"
#include "../../../../../EmuCore/TMPHelpers/TypeComparators.h"

#include <array>
#include <immintrin.h>

// Should make these defines actually determined based on architecture/compiler rather than hard-coded

/// <summary>
/// <para> Preprocessor flag indicating if EmuSIMD uses 128-bit SIMD registers. If this is false, 128-bit registers are emulated. </para>
/// <para> When emulating, 128-bit registers will be emulated as a collection of scalars of the matching type. </para>
/// </summary>
#define EMU_SIMD_USE_128_REGISTERS true
/// <summary>
/// <para> Preprocessor flag indicating if EmuSIMD uses 256-bit SIMD registers. If this is false, 256-bit registers are emulated. </para>
/// <para> If this is true, `EMU_SIMD_USE_128_REGISTERS` will also be true. </para>
/// <para> When emulating, 256-bit registers will be emulated as two 128-bit registers (this will also work when 128-bit registers are emulated). </para>
/// </summary>
#define EMU_SIMD_USE_256_REGISTERS true
/// <summary>
/// <para> Preprocessor flag indicating if EmuSIMD uses 512-bit SIMD registers. If this is false, 512-bit registers are emulated. </para>
/// <para> If this is true, `EMU_SIMD_USE_256_REGISTERS` and `EMU_SIMD_USE_128_REGISTERS` will also be true. </para>
/// <para> When emulating, 512-bit registers will be emulated as two 256-bit registers (this will also work when 256-bit registers are emulated). </para>
/// </summary>
#define EMU_SIMD_USE_512_REGISTERS true
#define EMU_SIMD_USES_ANY_SIMD_REGISTERS EMU_SIMD_USE_128_REGISTERS || EMU_SIMD_USE_256_REGISTERS || EMU_SIMD_USE_512_REGISTERS

/// <summary>
/// <para> Boolean preprocessor flag indicating if 128-bit registers use reference arguments. </para>
/// <para> This affects the`_arg` variants of all 128-bit register aliases. </para>
/// </summary>
#define EMU_SIMD_128_ARG_REFS !EMU_SIMD_USE_128_REGISTERS
/// <summary>
/// <para> Boolean preprocessor flag indicating if 256-bit registers use reference arguments. </para>
/// <para> This affects the`_arg` variants of all 256-bit register aliases. </para>
/// </summary>
#define EMU_SIMD_256_ARG_REFS !EMU_SIMD_USE_256_REGISTERS
/// <summary>
/// <para> Boolean preprocessor flag indicating if 512-bit registers use reference arguments. </para>
/// <para> This affects the`_arg` variants of all 512-bit register aliases. </para>
/// </summary>
#define EMU_SIMD_512_ARG_REFS EMU_SIMD_USE_512_REGISTERS

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
		template<std::size_t NumElements_, EmuConcepts::Arithmetic T_>
		struct is_dual_lane_simd_emulator<dual_lane_simd_emulator<NumElements_, T_>>
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
			template<std::size_t...Indices_>
			inline single_lane_simd_emulator(const T_* p_to_load_)
				: _data({ (*(p_to_load_ + Indices_))... })
			{
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
			static constexpr std::size_t emulated_width = EmulatedWidth_;

			inline dual_lane_simd_emulator() noexcept = default;
			inline dual_lane_simd_emulator(const dual_lane_simd_emulator<EmulatedWidth_, LaneT_>&) noexcept = default;
			inline dual_lane_simd_emulator(dual_lane_simd_emulator<EmulatedWidth_, LaneT_>&&) noexcept = default;

			inline dual_lane_simd_emulator<EmulatedWidth_, LaneT_>& operator=(const dual_lane_simd_emulator<EmulatedWidth_, LaneT_>&) = default;
			inline dual_lane_simd_emulator<EmulatedWidth_, LaneT_>& operator=(dual_lane_simd_emulator<EmulatedWidth_, LaneT_>&&) = default;

			LaneT_ _lane_0;
			LaneT_ _lane_1;
		};
#pragma endregion

#pragma region EMULATED_ELEMENT_GETS
		template<std::size_t Index_, bool AllowTheoreticalIndices_, std::size_t NumElements_, typename T_>
		[[nodiscard]] constexpr inline decltype(auto) retrieve_emulated_simd_element(const single_lane_simd_emulator<NumElements_, T_>& simd_emulator_) noexcept
		{
			if constexpr (Index_ < NumElements_)
			{
				return simd_emulator_._data[Index_];
			}
			else
			{
				if constexpr (AllowTheoreticalIndices_)
				{
					return T_(0);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, Index_>(), "INTERNAL EMUSIMD ERROR: `retrieve_emulated_simd_element` called with an out-of-range index, with theoretical indices disallowed.");
				}
			}
		}

		template<std::size_t Index_, bool AllowTheoreticalIndices_, std::size_t NumElements_, typename T_>
		[[nodiscard]] constexpr inline decltype(auto) retrieve_emulated_simd_element(single_lane_simd_emulator<NumElements_, T_>& simd_emulator_) noexcept
		{
			if constexpr (Index_ < NumElements_)
			{
				return simd_emulator_._data[Index_];
			}
			else
			{
				if constexpr (AllowTheoreticalIndices_)
				{
					return T_(0);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, Index_>(), "INTERNAL EMUSIMD ERROR: `retrieve_emulated_simd_element` called with an out-of-range index, with theoretical indices disallowed.");
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

		template<class OutSingleLaneEmulator_, std::size_t Offset_, EmuConcepts::Arithmetic...Args_, std::size_t...ElementIndices_>
		constexpr inline OutSingleLaneEmulator_ set_single_lane_simd_emulator_with_offset_tuple(std::tuple<Args_...> args_tuple_, std::index_sequence<ElementIndices_...> element_indices_)
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

		template<std::size_t EmulatedWidth_, class LaneT_, std::size_t Offset_, std::size_t Layer_, EmuConcepts::Arithmetic...Args_, std::size_t...LaneIndices_>
		constexpr inline dual_lane_simd_emulator<EmulatedWidth_, LaneT_> set_dual_lane_simd_emulator_with_offset_tuple(std::tuple<Args_...>& args_tuple_, std::index_sequence<LaneIndices_...> lane_indices_)
		{
			constexpr std::size_t num_args = sizeof...(Args_);
			if constexpr (is_dual_lane_simd_emulator<LaneT_>::value)
			{
				constexpr std::size_t args_per_lane = num_args / (2 << Layer_);
				return dual_lane_simd_emulator<EmulatedWidth_, LaneT_>
				(
					set_dual_lane_simd_emulator_with_offset_tuple<EmulatedWidth_ / 2, LaneT_, Offset_ + (LaneIndices_ * args_per_lane), Layer_ + 1>
					(
						args_tuple_,
						std::make_index_sequence<2>()
					)
				);
			}
			else if constexpr (is_single_lane_simd_emulator<LaneT_>::value)
			{
				constexpr std::size_t args_per_lane = num_args / (2 << Layer_);
				return dual_lane_simd_emulator<EmulatedWidth_, LaneT_>
				(
					set_single_lane_simd_emulator_with_offset_tuple<LaneT_, Offset_ + (LaneIndices_ * args_per_lane)>
					(
						args_tuple_,
						std::make_index_sequence<args_per_lane>()
					)
				);
			}
			else
			{
				// TODO: Find a way to set actual registers
				// --- May want some forward declarations for the template `set` and `setr` variants

			}
		}

		template<std::size_t EmulatedWidth_, class LaneT_, EmuConcepts::Arithmetic...Args_, std::size_t...LaneIndices_>
		constexpr inline dual_lane_simd_emulator<EmulatedWidth_, LaneT_> set_dual_lane_simd_emulator(std::tuple<Args_...>& args_tuple_, std::index_sequence<LaneIndices_...> lane_indices_)
		{
			constexpr std::size_t num_args = sizeof...(Args_);
			if constexpr (is_dual_lane_simd_emulator<LaneT_>::value)
			{
				// 2 dual-lane emulators (most probably constructing a 512-bit in this case)
				constexpr std::size_t args_per_lane = num_args / 2;
				return dual_lane_simd_emulator<EmulatedWidth_, LaneT_>
				(
					set_dual_lane_simd_emulator_with_offset_tuple<EmulatedWidth_ / 2, LaneT_, LaneIndices_ * args_per_lane, 1>
					(
						args_tuple_,
						std::make_index_sequence<2>()
					)...
				);
			}
			else if constexpr (is_single_lane_simd_emulator<LaneT_>::value)
			{
				// 2 single-lane emulators (most probably constructing a 256-bit in this case)
				constexpr std::size_t args_per_lane = num_args / 2;
				return dual_lane_simd_emulator<EmulatedWidth_, LaneT_>
				(
					set_single_lane_simd_emulator_with_offset_tuple<LaneT_, LaneIndices_ * args_per_lane>
					(
						args_tuple_,
						std::make_index_sequence<2>()
					)...
				);
			}
			else
			{
				// 2 actual SIMD registers
				// TODO: Find a way to set actual registers
				// --- May want some forward declarations for the template `set` and `setr` variants
				constexpr std::size_t per_element_width = EmulatedWidth_ / num_args;
				// ...
			}
		}

		template<std::size_t EmulatedWidth_, class LaneT_, EmuConcepts::Arithmetic...Args_, std::size_t...LaneIndices_>
		constexpr inline dual_lane_simd_emulator<EmulatedWidth_, LaneT_> set_dual_lane_simd_emulator(Args_&&...args_, std::index_sequence<LaneIndices_...> lane_indices_) noexcept
		{
			return set_dual_lane_simd_emulator<EmulatedWidth_, LaneT_>
			(
				std::forward_as_tuple(std::forward<Args_>(args_)...),
				std::index_sequence<LaneIndices_...>()
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
		constexpr inline single_lane_simd_emulator<NumElements_, T_> load_single_lane_simd_emulator(const T_* p_to_load_)
		{
			return single_lane_simd_emulator<NumElements_, T_>(p_to_load_);
		}
#pragma endregion

#pragma region EMULATED_STORES
		template<std::size_t NumElements_, EmuConcepts::Arithmetic T_>
		constexpr inline void emulate_simd_store(const single_lane_simd_emulator<NumElements_, T_>& simd_emulator_, T_* p_out_)
		{
			memcpy(p_out_, simd_emulator_._data.data(), NumElements_ * sizeof(T_));
		}

		template<std::size_t EmulatedWidth_, class LaneT_>
		constexpr inline void emulate_simd_store(const dual_lane_simd_emulator<EmulatedWidth_, LaneT_>& simd_emulator_, void* p_out_)
		{
			unsigned char* p_out_bytes = reinterpret_cast<unsigned char*>(p_out_);
			if constexpr (EmulatedWidth_ == 256)
			{
				constexpr std::size_t lane_bytes = 128 / 8;
				if constexpr (is_simd_emulator<LaneT_>::value)
				{
					// Storing two 128-bit emulators
					memcpy(p_out_bytes, simd_emulator_._lane_0._data.data(), lane_bytes);
					memcpy(p_out_bytes + lane_bytes, simd_emulator_._lane_1._data.data(), lane_bytes);
				}
				else
				{
					// Storing two 128-bit registers
					memcpy(p_out_bytes, simd_emulator_._lane_0, lane_bytes);
					memcpy(p_out_bytes + lane_bytes, simd_emulator_._lane_1, lane_bytes);
				}
			}
			else
			{
				if constexpr (is_simd_emulator<LaneT_>::value)
				{
					// Storing two 256-bit emulators, one 128-bit lane at a time
					constexpr std::size_t lane_bytes = 128 / 8;
					memcpy(p_out_bytes, simd_emulator_._lane_0._lane_0._data.data(), lane_bytes);
					p_out_bytes += lane_bytes;
					memcpy(p_out_bytes, simd_emulator_._lane_0._lane_1._data.data(), lane_bytes);
					p_out_bytes += lane_bytes;
					memcpy(p_out_bytes, simd_emulator_._lane_1._lane_0._data.data(), lane_bytes);
					p_out_bytes += lane_bytes;
					memcpy(p_out_bytes, simd_emulator_._lane_1._lane_1._data.data(), lane_bytes);
					p_out_bytes += lane_bytes;
				}
				else
				{
					// Storing two 256-bit registers
					constexpr std::size_t lane_bytes = 256 / 8;
					memcpy(p_out_bytes, simd_emulator_._lane_0, lane_bytes);
					memcpy(p_out_bytes + lane_bytes, simd_emulator_._lane_1, lane_bytes);
				}
			}
		}
#pragma endregion

#pragma region EMULATED_BASIC_GENERIC_OPS
		template<bool AllowTheoreticalIndices_, class Func_, std::size_t NumElements_, EmuConcepts::Arithmetic T_, std::size_t...OutIndices_>
		constexpr inline single_lane_simd_emulator<NumElements_, T_> emulate_simd_basic(const Func_& func_, const single_lane_simd_emulator<NumElements_, T_>& simd_emulator_, std::index_sequence<OutIndices_...> out_indices_)
		{
			static_assert(sizeof...(OutIndices_) == NumElements_, "INTERNAL EMUSIMD ERROR: `emulate_simd_basic` called with a number of indices not equal to the number of elements in the output emulated register.");
			return single_lane_simd_emulator<NumElements_, T_>
			(
				func_(retrieve_emulated_simd_element<OutIndices_, AllowTheoreticalIndices_>(simd_emulator_))...
			);
		}

		template<bool AllowTheoreticalIndices_, class Func_, std::size_t NumElements_, EmuConcepts::Arithmetic T_, std::size_t...OutIndices_>
		constexpr inline single_lane_simd_emulator<NumElements_, T_> emulate_simd_basic
		(
			const Func_& func_,
			const single_lane_simd_emulator<NumElements_, T_>& simd_emulator_a_,
			const single_lane_simd_emulator<NumElements_, T_>& simd_emulator_b_,
			std::index_sequence<OutIndices_...> out_indices_
		)
		{
			static_assert(sizeof...(OutIndices_) == NumElements_, "INTERNAL EMUSIMD ERROR: `emulate_simd_basic` called with a number of indices not equal to the number of elements in the output emulated register.");
			return single_lane_simd_emulator<NumElements_, T_>
			(
				func_
				(
					retrieve_emulated_simd_element<OutIndices_, AllowTheoreticalIndices_>(simd_emulator_a_),
					retrieve_emulated_simd_element<OutIndices_, AllowTheoreticalIndices_>(simd_emulator_b_)
				)...
			);
		}

		template<bool AllowTheoreticalIndices_, class Func_, std::size_t NumElements_, EmuConcepts::Arithmetic T_, std::size_t...OutIndices_>
		constexpr inline single_lane_simd_emulator<NumElements_, T_> emulate_simd_basic
		(
			const Func_& func_,
			const single_lane_simd_emulator<NumElements_, T_>& simd_emulator_a_,
			const single_lane_simd_emulator<NumElements_, T_>& simd_emulator_b_,
			const single_lane_simd_emulator<NumElements_, T_>& simd_emulator_c_,
			std::index_sequence<OutIndices_...> out_indices_
		)
		{
			static_assert(sizeof...(OutIndices_) == NumElements_, "INTERNAL EMUSIMD ERROR: `emulate_simd_basic` called with a number of indices not equal to the number of elements in the output emulated register.");
			return single_lane_simd_emulator<NumElements_, T_>
			(
				func_
				(
					retrieve_emulated_simd_element<OutIndices_, AllowTheoreticalIndices_>(simd_emulator_a_),
					retrieve_emulated_simd_element<OutIndices_, AllowTheoreticalIndices_>(simd_emulator_b_),
					retrieve_emulated_simd_element<OutIndices_, AllowTheoreticalIndices_>(simd_emulator_c_)
				)...
			);
		}
#pragma endregion

#pragma region EMULATED_NON_CONVERTING_CASTS
		template<std::size_t OutElements_, EmuConcepts::Arithmetic OutT_, std::size_t InElements_, EmuConcepts::Arithmetic InT_>
		[[nodiscard]] constexpr inline single_lane_simd_emulator<OutElements_, OutT_> emulate_simd_cast_same_width(const single_lane_simd_emulator<InElements_, InT_>& in_)
		{
			auto out_emulator = single_lane_simd_emulator<OutElements_, OutT_>();
			memcpy(out_emulator._data.data(), in_._data.data(), sizeof(InT_) * InElements_);
			return out_emulator;
		}

		template<class Out_, std::size_t InElements_, EmuConcepts::Arithmetic InT_>
		[[nodiscard]] constexpr inline Out_ emulate_simd_cast_greater_width(const single_lane_simd_emulator<InElements_, InT_>& in_)
		{
			constexpr std::size_t copy_bytes = 128 / 8;
			if constexpr (is_simd_emulator<Out_>::value)
			{
				// 128-bit emulator -> 256-bit or 512-bit emulator
				// Guaranteed to be emulators all the way up as the lowest-width register is being emulated (due to single_lane_simd_emulator being in use)
				// --- As such, we know we can safely use `_lane_X` and `_data` syntax
				Out_ out_emulator = Out_();
				if constexpr (Out_::emulated_width == 256)
				{
					memcpy(out_emulator._lane_0._data.data(), in_._data.data(), copy_bytes);
					return out_emulator;
				}
				else if constexpr(Out_::emulated_width == 512)
				{
					memcpy(out_emulator._lane_0._lane_0._data.data(), in_._data.data(), copy_bytes);
					return out_emulator;
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Out_>(), "EmuSIMD: Could not cast an emulated SIMD register to one of a greater width as the emulated width was neither 256- nor 512-bit.");
				}
			}
			else
			{
				// 128-bit emulator -> 256-bit or 512-bit register
				// --- Just copy the emulated register's 128-bits to the lo end of the output register and return that
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
				Out_ out_emulator = Out_();
				if constexpr (is_simd_emulator<_lane_type>::value)
				{
					// Emulators all the way down, so copy to-and-from the data chunks specifically
					memcpy(out_emulator._lane_0._lane_0._data.data(), in_._lane_0._data.data(), bytes_per_128_chunk);
					memcpy(out_emulator._lane_0._lane_1._data.data(), in_._lane_1._data.data(), bytes_per_128_chunk);
				}
				else
				{
					// 128-bit chunks are actual registers
					memcpy(&(out_emulator._lane_0._lane_0), &(in_._lane_0), bytes_per_128_chunk);
					memcpy(&(out_emulator._lane_0._lane_1), &(in_._lane_1), bytes_per_128_chunk);
				}
				return out_emulator;
			}
			else
			{
				// 256-bit emulator -> 512-bit register
				// --- Just copy the emulated register's 256-bits to the lo end of the output register and return that
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
			// We will always need lane_0 and will analyse its type on every path, so may as well prepare it here
			auto& lane_0 = in_._lane_0;
			using _lane_type = typename std::remove_cvref<decltype(lane_0)>::type;

			if constexpr (EmulatedWidth_ == 256)
			{
				// Guaranteed casting 256-bit -> 128-bit
				if constexpr (std::is_same_v<Out_, _lane_type>)
				{
					// Output is the same as a lane within the emulator, so just return a copy of the lo lane
					return Out_(lane_0);
				}
				else
				{
					// Need to copy the bytes to the new type to safely "reinterpret" (due to type aliasing rules)
					constexpr std::size_t bytes_to_copy = 128 / 8;
					Out_ cast_result = Out_();
					if constexpr (is_simd_emulator<Out_>::value)
					{
						// Casting to 128-bit emulator
						memcpy(&cast_result._data.data(), lane_0._data.data(), bytes_to_copy);
					}
					else
					{
						// Casting to 128-bit register
						memcpy(&cast_result, lane_0._data.data(), bytes_to_copy);
					}
					return cast_result;
				}
			}
			else
			{
				// 512-bit -> either 256-bit or 128-bit, need to test more
				if constexpr (std::is_same_v<Out_, _lane_type>)
				{
					// Output is the same as a lane within the emulator, so just return a copy of the lo lane
					return Out_(lane_0);
				}
				else
				{
					if constexpr (is_simd_emulator<Out_>::value)
					{
						// 512-bit -> 256-bit or 128-bit emulator
						if constexpr (is_single_lane_simd_emulator<Out_>::value)
						{
							// 512-bit -> 128-bit emulator
							// --- As output is an emulator, guaranteed we only have emulators until the end due to the guarnateed hierarchy
							auto& lane_0_lo = lane_0._lane_0;
							using _lane_lo_type = typename std::remove_cvref<decltype(lane_0_lo)>::type;
							if constexpr (std::is_same_v<Out_, _lane_lo_type>)
							{
								// Result is same type as the lo 128-bit lane of the lo 256-bit lane, so just return a direct copy
								return Out_(lane_0_lo);
							}
							else
							{
								// Need to copy the bytes to the new type to safely "reinterpret" (due to type aliasing rules)
								constexpr std::size_t bytes_to_copy = 128 / 8;
								Out_ cast_result = Out_();
								memcpy(cast_result._data.data(), lane_0_lo._data.data(), bytes_to_copy);
								return cast_result;
							}
						}
						else
						{
							// 512-bit -> 256-bit emulator, copying individual 128-bit lanes
							// --- Need to determine if a 128-bit lane is emulated in the output
							constexpr std::size_t bytes_to_copy_per_lane = 128 / 8;
							using _out_lo_lane_type = typename std::remove_cvref<decltype(std::declval<Out_>()._lane_0)>::type;
							Out_ cast_result = Out_();
							if constexpr (is_simd_emulator<_out_lo_lane_type>::value)
							{
								// Outputting a 256-bit lane as two 128-bit emulated lanes
								memcpy(cast_result._lane_0._data.data(), lane_0._lane_0._data.data(), bytes_to_copy_per_lane);
								memcpy(cast_result._lane_1._data.data(), lane_0._lane_1._data.data(), bytes_to_copy_per_lane);
							}
							else
							{
								// Outputting a 256-bit lane as two 128-bit register lanes
								memcpy(&(cast_result._lane_0), &(lane_0._lane_0), bytes_to_copy_per_lane);
								memcpy(&(cast_result._lane_1), &(lane_0._lane_1), bytes_to_copy_per_lane);
							}
							return cast_result;
						}
					}
					else
					{
						// 512-bit -> 256-bit or 128-bit register
						constexpr std::size_t min_bytes_for_256bit = 256 / 8;
						if constexpr (sizeof(Out_) < min_bytes_for_256bit)
						{
							// 512-bit -> 128-bit register
							if constexpr (is_simd_emulator<_lane_type>::value)
							{
								// lane_0 is an emulated 256-bit register, so we're outputting its lo lane
								auto& lane_0_lo = lane_0._lane_0;
								using _lane_lo_type = typename std::remove_cvref<decltype(lane_0_lo)>::type;
								if constexpr (std::is_same_v<_lane_lo_type, Out_>)
								{
									// lane_0's lo lane is the same as the output register, so just output a copy of that
									return Out_(lane_0_lo);
								}
								else
								{
									// lane_0's lo lane is a different type to the output
									constexpr std::size_t bytes_to_copy = 128 / 8;
									Out_ cast_result = Out_();
									memcpy(&cast_result, &lane_0_lo, bytes_to_copy);
									return cast_result;
								}
							}
							else
							{
								// lane_0 is a 256-bit register so we can't work with emulated lanes
								// --- This can be optimised but not presently due to EmuSIMD structure, unless we want to make this function a *lot* larger
								constexpr std::size_t bytes_to_copy = 128 / 8;
								Out_ cast_result = Out_();
								memcpy(&cast_result, lane_0, bytes_to_copy);
								return cast_result;
							}
						}
						else
						{
							// 512-bit -> 256-bit register
							constexpr std::size_t bytes_to_copy = 256 / 8;
							Out_ cast_result = Out_();
							memcpy(&cast_result, &lane_0, bytes_to_copy);
							return cast_result;
						}
					}
				}
			}
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

#if EMU_SIMD_USE_512_REGISTERS // TODO: TEMPORARY, REMOVE WHEN REWORK FOR EMULATION IS DONE (well, remove the !)
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

#if EMU_SIMD_USE_512_REGISTERS // TODO: TEMPORARY, REMOVE WHEN REWORK FOR EMULATION IS DONE (well, remove the !)
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

#if EMU_SIMD_USE_512_REGISTERS // TODO: TEMPORARY, REMOVE WHEN REWORK FOR EMULATION IS DONE (well, remove the !)
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

#if EMU_SIMD_USE_512_REGISTERS // TODO: TEMPORARY, REMOVE WHEN REWORK FOR EMULATION IS DONE (well, remove the !)
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

#if EMU_SIMD_USE_512_REGISTERS // TODO: TEMPORARY, REMOVE WHEN REWORK FOR EMULATION IS DONE (well, remove the !)
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

#if EMU_SIMD_USE_512_REGISTERS // TODO: TEMPORARY, REMOVE WHEN REWORK FOR EMULATION IS DONE (well, remove the !)
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

#if EMU_SIMD_USE_512_REGISTERS // TODO: TEMPORARY, REMOVE WHEN REWORK FOR EMULATION IS DONE (well, remove the !)
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

#if EMU_SIMD_USE_512_REGISTERS // TODO: TEMPORARY, REMOVE WHEN REWORK FOR EMULATION IS DONE (well, remove the !)
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

#if EMU_SIMD_USE_512_REGISTERS // TODO: TEMPORARY, REMOVE WHEN REWORK FOR EMULATION IS DONE (well, remove the !)
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

#if EMU_SIMD_USE_512_REGISTERS // TODO: TEMPORARY, REMOVE WHEN REWORK FOR EMULATION IS DONE (well, remove the !)
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
#if EMU_SIMD_USE_512_REGISTERS // TODO: TEMPORARY, REMOVE WHEN REWORK FOR EMULATION IS DONE
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