#ifndef EMU_MATH_FAST_MATRIX_SCALE_H_INC_
#define EMU_MATH_FAST_MATRIX_SCALE_H_INC_ 1

#include "_common_fast_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Creates an EmuMath FastMatrix which can be used to perform a scale by the specified amounts. </para>
	/// <para>
	///		The size of the output Matrix may be omitted, in which case a square Matrix will be output, 
	///		with dimensions of a size equal to the number of passed scale arguments + 1.
	/// </para>
	/// <para> If an axis is omitted for the output Matrix, it will be treated as 1 (i.e. no scale in that axis). </para>
	/// </summary>
	/// <param name="scales_">Sequential axis scales to use, starting from the X-axis.</param>
	/// <returns>EmuMath FastMatrix representing the specified scale.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		bool OutColumnMajor_ = true, std::size_t OutRegisterWidth_ = 128, EmuConcepts::Arithmetic...Scales_
	>
	[[nodiscard]] constexpr inline auto fast_matrix_make_scale(Scales_&&...scales_)
		-> EmuMath::FastMatrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, OutRegisterWidth_>
	{
		auto args_tuple = std::forward_as_tuple(std::forward<Scales_>(scales_)...);
		return _fast_matrix_underlying::_make_scale_matrix< EmuMath::FastMatrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, OutRegisterWidth_>>
		(
			args_tuple,
			std::make_index_sequence<EmuMath::FastMatrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, OutRegisterWidth_>::num_major_elements>(),
			std::make_index_sequence<EmuMath::FastMatrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, OutRegisterWidth_>::num_registers_per_major>()
		);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, std::size_t OutRegisterWidth_ = 128, EmuConcepts::Arithmetic...Scales_>
	[[nodiscard]] constexpr inline auto fast_matrix_make_scale(Scales_&&...scales_)
		-> EmuMath::FastMatrix<sizeof...(Scales_) + 1, sizeof...(Scales_) + 1, OutT_, OutColumnMajor_, OutRegisterWidth_>
	{
		constexpr std::size_t size = sizeof...(Scales_) + 1;
		auto args_tuple = std::forward_as_tuple(std::forward<Scales_>(scales_)...);
		return _fast_matrix_underlying::_make_scale_matrix<EmuMath::FastMatrix<size, size, OutT_, OutColumnMajor_, OutRegisterWidth_>>
		(
			args_tuple,
			std::make_index_sequence<EmuMath::FastMatrix<size, size, OutT_, OutColumnMajor_, OutRegisterWidth_>::num_major_elements>(),
			std::make_index_sequence<EmuMath::FastMatrix<size, size, OutT_, OutColumnMajor_, OutRegisterWidth_>::num_registers_per_major>()
		);
	}

	/// <summary>
	/// <para> Creates an EmuMath FastMatrix which can be used to perform a scale by the specified amounts. </para>
	/// <para>
	///		The size of the output Matrix may be omitted, in which case a square Matrix will be output, 
	///		with dimensions of a size equal to the number of elements in the passed tuple argument, + 1.
	/// </para>
	/// <para> If an axis is omitted for the output Matrix, it will be treated as 1 (i.e. no scale in that axis). </para>
	/// </summary>
	/// <param name="scales_">Tuple of sequential axis scales to use, starting from the X-axis.</param>
	/// <returns>EmuMath FastMatrix representing the specified scale.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		bool OutColumnMajor_ = true, std::size_t OutRegisterWidth_ = 128, EmuConcepts::StdTuple ScalesTuple_
	>
	[[nodiscard]] constexpr inline auto fast_matrix_make_scale(ScalesTuple_&& scales_)
		-> EmuMath::FastMatrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, OutRegisterWidth_>
	{
		return _fast_matrix_underlying::_make_scale_matrix< EmuMath::FastMatrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, OutRegisterWidth_>>
		(
			EmuCore::TMP::lval_ref_cast<ScalesTuple_>(std::forward<ScalesTuple_>(scales_)),
			std::make_index_sequence<EmuMath::FastMatrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, OutRegisterWidth_>::num_major_elements>(),
			std::make_index_sequence<EmuMath::FastMatrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, OutRegisterWidth_>::num_registers_per_major>()
		);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, std::size_t OutRegisterWidth_ = 128, EmuConcepts::StdTuple ScalesTuple_>
	[[nodiscard]] constexpr inline auto fast_matrix_make_scale(ScalesTuple_&& scales_)
		-> EmuMath::FastMatrix
		<
			std::tuple_size_v<typename EmuCore::TMP::remove_ref_cv<ScalesTuple_>::type> + 1,
			std::tuple_size_v<typename EmuCore::TMP::remove_ref_cv<ScalesTuple_>::type> + 1,
			OutT_,
			OutColumnMajor_,
			OutRegisterWidth_
		>
	{
		constexpr std::size_t size = std::tuple_size_v<typename EmuCore::TMP::remove_ref_cv<ScalesTuple_>::type> + 1;
		return _fast_matrix_underlying::_make_scale_matrix<EmuMath::FastMatrix<size, size, OutT_, OutColumnMajor_, OutRegisterWidth_>>
		(
			EmuCore::TMP::lval_ref_cast<ScalesTuple_>(std::forward<ScalesTuple_>(scales_)),
			std::make_index_sequence<EmuMath::FastMatrix<size, size, OutT_, OutColumnMajor_, OutRegisterWidth_>::num_major_elements>(),
			std::make_index_sequence<EmuMath::FastMatrix<size, size, OutT_, OutColumnMajor_, OutRegisterWidth_>::num_registers_per_major>()
		);
	}
}

#endif
