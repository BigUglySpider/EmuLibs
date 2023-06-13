#ifndef EMU_SIMD_HELPERS_FORWARD_TEMPLATE_SHUFFLES_H_INC_
#define EMU_SIMD_HELPERS_FORWARD_TEMPLATE_SHUFFLES_H_INC_ 1

#include "_forward_tmp.h"
#include "../../../../../../../EmuCore/CommonConcepts/CommonRequirements.h"

namespace EmuSIMD
{
	template<std::size_t...Indices_, EmuConcepts::KnownSIMD Register_>
	[[nodiscard]] inline auto shuffle(Register_&& ab_)
		-> typename std::remove_cvref<Register_>::type;

	template<std::size_t...Indices_, EmuConcepts::KnownSIMD RegisterA_, EmuConcepts::UnqualifiedMatch<RegisterA_> RegisterB_>
	[[nodiscard]] inline auto shuffle(RegisterA_&& a_, RegisterB_&& b_)
		-> typename std::remove_cvref<RegisterA_>::type;

	template<std::uint64_t ShuffleMask_, std::size_t PerElementWidthIfGenericInt_ = 32, EmuConcepts::KnownSIMD Register_>
	[[nodiscard]] inline auto shuffle_with_mask(Register_&& ab_)
		-> typename std::remove_cvref<Register_>::type;

	template<std::uint64_t ShuffleMask_, std::size_t PerElementWidthIfGenericInt_ = 32, EmuConcepts::KnownSIMD RegisterA_, EmuConcepts::UnqualifiedMatch<RegisterA_> RegisterB_>
	[[nodiscard]] inline auto shuffle_with_mask(RegisterA_&& a_, RegisterB_&& b_)
		-> typename std::remove_cvref<RegisterA_>::type;
#pragma region FULL_WIDTH_SHUFFLES
	/// <summary>
	/// <para> Performs a full-width shuffle of the passed SIMD register's indices. </para>
	/// <para> For 128-bit registers, this is the same as a normal shuffle. </para>
	/// </summary>
	/// <param name="a_">128-bit register to shuffle for the lo bytes of the output register.</param>
	/// <param name="b_">128-bit register to shuffle for the hi bytes of the output register.</param>
	/// <returns>Result of shuffling the passed Registers with the provided indices.</returns>
	template<std::size_t...Indices_, EmuConcepts::KnownSIMD RegisterA_, EmuConcepts::UnqualifiedMatch<RegisterA_> RegisterB_>
	requires (EmuSIMD::TMP::simd_register_width_v<RegisterA_> == 128)
	[[nodiscard]] constexpr inline auto shuffle_full_width(RegisterA_&& a_, RegisterB_&& b_)
		-> typename std::remove_cvref<RegisterA_>::type;

	/// <summary>
	/// <para> Performs a full-width shuffle of the passed SIMD register's indices. </para>
	/// <para> For 128-bit registers, this is the same as a normal shuffle. </para>
	/// </summary>
	/// <param name="ab_">128-bit register to shuffle.</param>
	/// <returns>Result of shuffling the passed Register with the provided indices.</returns>
	template<std::size_t...Indices_, EmuConcepts::KnownSIMD Register_>
	requires (EmuSIMD::TMP::simd_register_width_v<Register_> == 128)
	[[nodiscard]] constexpr inline auto shuffle_full_width(Register_&& ab_)
		-> typename std::remove_cvref<Register_>::type;

	/// <summary>
	/// <para> Performs a full-width shuffle of the passed SIMD register's indices, allowing shuffles between lanes unlike a normal shuffle. </para>
	/// </summary>
	/// <param name="a_">256-bit register to shuffle for the lo 128-bit lane of the output register.</param>
	/// <param name="b_">256-bit register to shuffle for the hi 128-bit lane of the output register.</param>
	/// <returns>Result of full-width-shuffling the passed Registers with the provided indices.</returns>
	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_, EmuConcepts::KnownSIMD RegisterA_, EmuConcepts::UnqualifiedMatch<RegisterA_> RegisterB_>
	requires (EmuSIMD::TMP::simd_register_width_v<RegisterA_> == 256 && EmuSIMD::TMP::register_element_count_v<RegisterA_, 64> == 4)
	[[nodiscard]] constexpr inline auto shuffle_full_width(RegisterA_&& a_, RegisterB_&& b_)
		-> typename std::remove_cvref<RegisterA_>::type;

	/// <summary>
	/// <para> Performs a full-width shuffle of the passed SIMD register's indices, allowing shuffles between lanes unlike a normal shuffle. </para>
	/// </summary>
	/// <param name="ab_">256-bit register to shuffle.</param>
	/// <returns>Result of full-width-shuffling the passed Register with the provided indices.</returns>
	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_, EmuConcepts::KnownSIMD Register_>
	requires (EmuSIMD::TMP::simd_register_width_v<Register_> == 256 && EmuSIMD::TMP::register_element_count_v<Register_> == 4)
	[[nodiscard]] constexpr inline auto shuffle_full_width(Register_&& ab_)
		-> typename std::remove_cvref<Register_>::type;
#pragma endregion
}

#endif
