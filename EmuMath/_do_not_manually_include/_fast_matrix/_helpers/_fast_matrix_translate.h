#ifndef EMU_MATH_FAST_MATRIX_TRANSLATE_H_INC_
#define EMU_MATH_FAST_MATRIX_TRANSLATE_H_INC_ 1

#include "_common_fast_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Creates an EmuMath FastMatrix which can be used to perform a translation by the specified amounts. </para>
	/// <para>
	///		The size of the output Matrix may be omitted, in which case a square Matrix will be output, 
	///		with dimensions of a size equal to the number of passed translation arguments + 1.
	/// </para>
	/// <para> If an axis is omitted for the output Matrix, it will be treated as 0 (i.e. no translation in that axis). </para>
	/// </summary>
	/// <param name="translations_">Sequential axis translations to use, starting from the X-axis.</param>
	/// <returns>EmuMath FastMatrix representing the specified translation.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		bool OutColumnMajor_ = true, std::size_t OutRegisterWidth_ = 128, EmuConcepts::Arithmetic...Translations_
	>
	[[nodiscard]] constexpr inline auto fast_matrix_make_translation(Translations_&&...translations_)
		-> EmuMath::FastMatrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, OutRegisterWidth_>
	{
		auto args_tuple = std::forward_as_tuple(std::forward<Translations_>(translations_)...);
		return _fast_matrix_underlying::_make_translation_matrix< EmuMath::FastMatrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, OutRegisterWidth_>>
		(
			args_tuple,
			std::make_index_sequence<EmuMath::FastMatrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, OutRegisterWidth_>::num_major_elements>(),
			std::make_index_sequence<EmuMath::FastMatrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, OutRegisterWidth_>::num_registers_per_major>()
		);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, std::size_t OutRegisterWidth_ = 128, EmuConcepts::Arithmetic...Translations_>
	[[nodiscard]] constexpr inline auto fast_matrix_make_translation(Translations_&&...translations_)
		-> EmuMath::FastMatrix<sizeof...(Translations_) + 1, sizeof...(Translations_) + 1, OutT_, OutColumnMajor_, OutRegisterWidth_>
	{
		constexpr std::size_t size = sizeof...(Translations_) + 1;
		auto args_tuple = std::forward_as_tuple(std::forward<Translations_>(translations_)...);
		return _fast_matrix_underlying::_make_translation_matrix<EmuMath::FastMatrix<size, size, OutT_, OutColumnMajor_, OutRegisterWidth_>>
		(
			args_tuple,
			std::make_index_sequence<EmuMath::FastMatrix<size, size, OutT_, OutColumnMajor_, OutRegisterWidth_>::num_major_elements>(),
			std::make_index_sequence<EmuMath::FastMatrix<size, size, OutT_, OutColumnMajor_, OutRegisterWidth_>::num_registers_per_major>()
		);
	}

	/// <summary>
	/// <para> Creates an EmuMath FastMatrix which can be used to perform a translation by the specified amounts. </para>
	/// <para>
	///		The size of the output Matrix may be omitted, in which case a square Matrix will be output, 
	///		with dimensions of a size equal to the number of elements in the passed tuple argument, + 1.
	/// </para>
	/// <para> If an axis is omitted for the output Matrix, it will be treated as 0 (i.e. no translation in that axis). </para>
	/// </summary>
	/// <param name="translations_">Tuple of sequential axis translations to use, starting from the X-axis.</param>
	/// <returns>EmuMath FastMatrix representing the specified translation.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		bool OutColumnMajor_ = true, std::size_t OutRegisterWidth_ = 128, EmuConcepts::StdTuple TranslationsTuple_
	>
	[[nodiscard]] constexpr inline auto fast_matrix_make_translation(TranslationsTuple_&& translations_)
		-> EmuMath::FastMatrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, OutRegisterWidth_>
	{
		return _fast_matrix_underlying::_make_translation_matrix< EmuMath::FastMatrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, OutRegisterWidth_>>
		(
			EmuCore::TMP::lval_ref_cast<TranslationsTuple_>(std::forward<TranslationsTuple_>(translations_)),
			std::make_index_sequence<EmuMath::FastMatrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, OutRegisterWidth_>::num_major_elements>(),
			std::make_index_sequence<EmuMath::FastMatrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, OutRegisterWidth_>::num_registers_per_major>()
		);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, std::size_t OutRegisterWidth_ = 128, EmuConcepts::StdTuple TranslationsTuple_>
	[[nodiscard]] constexpr inline auto fast_matrix_make_translation(TranslationsTuple_&& translations_)
		-> EmuMath::FastMatrix
		<
			std::tuple_size_v<typename EmuCore::TMP::remove_ref_cv<TranslationsTuple_>::type> + 1,
			std::tuple_size_v<typename EmuCore::TMP::remove_ref_cv<TranslationsTuple_>::type> + 1,
			OutT_,
			OutColumnMajor_,
			OutRegisterWidth_
		>
	{
		constexpr std::size_t size = std::tuple_size_v<typename EmuCore::TMP::remove_ref_cv<TranslationsTuple_>::type> + 1;
		return _fast_matrix_underlying::_make_translation_matrix<EmuMath::FastMatrix<size, size, OutT_, OutColumnMajor_, OutRegisterWidth_>>
		(
			EmuCore::TMP::lval_ref_cast<TranslationsTuple_>(std::forward<TranslationsTuple_>(translations_)),
			std::make_index_sequence<EmuMath::FastMatrix<size, size, OutT_, OutColumnMajor_, OutRegisterWidth_>::num_major_elements>(),
			std::make_index_sequence<EmuMath::FastMatrix<size, size, OutT_, OutColumnMajor_, OutRegisterWidth_>::num_registers_per_major>()
		);
	}
}

#endif
