#ifndef EMU_MATH_VECTOR_COPY_H_INC_
#define EMU_MATH_VECTOR_COPY_H_INC_ 1

#include "_common_vector_helpers.h"

// CONTAINS:
// --- copy

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Assigns to the provided EmuMath Vector within the specified range using the provided in_ argument. </para>
	/// <para> If In_ is an EmuMath Vector: Written-to indices in out_vector_ will be assigned via the element at the respective index + ReadOffset_ within in_. </para>
	/// <para> If In_ is none of the above: Written-to indices in out_vector_ will all be assigned via in_. </para>
	/// <para> CopyBegin_: Inclusive index at which to start writing to out_vector_. Optional, but must be paired with CopyEnd_ if provided. Defaults to 0. </para>
	/// <para> CopyEnd_: Exclusive index at which to stop writing to out_vector_. Optional, but must be paired with CopyBegin_ if provided. Defaults to OutSize_. </para>
	/// <para> ReadOffset_: Offset to apply to indices to read EmuMath Vector input arguments. Optional. Unused if In_ is not an EmuMath Vector. Defaults to 0. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to assign to.</param>
	/// <param name="in_">: Scalar or EmuMath Vector to assign via.</param>
	template<std::size_t CopyBegin_, std::size_t CopyEnd_, std::size_t ReadOffset_ = 0, typename OutT_, std::size_t OutSize_, class In_>
	constexpr inline void vector_copy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, In_&& in_)
	{
		_vector_underlying::_vector_copy<CopyBegin_, CopyEnd_, ReadOffset_>(out_vector_, std::forward<In_>(in_));
	}

	template<std::size_t ReadOffset_ = 0, typename OutT_, std::size_t OutSize_, class In_>
	constexpr inline void vector_copy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, In_&& in_)
	{
		_vector_underlying::_vector_copy<0, OutSize_, ReadOffset_>(out_vector_, std::forward<In_>(in_));
	}

	/// <summary>
	/// <para> Constructs an EmuMath Vector of the specified type using the provided input argument. </para>
	/// </summary>
	/// <param name="in_">: Argument to construct the desired output Vector via.</param>
	/// <returns>EmuMath Vector constructed with the provided in_ argument.</returns>
	template<std::size_t OutSize_, typename OutT_, class In_, typename = std::enable_if_t<!EmuMath::TMP::is_emu_vector_v<In_>>>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_copy(In_&& in_)
	{
		return _vector_underlying::_vector_copy<EmuMath::Vector<OutSize_, OutT_>>(std::forward<In_>(in_));
	}

	/// <summary>
	/// <para> Constructs an EmuMath Vector of the specified type using the provided input EmuMath Vector argument. </para>
	/// </summary>
	/// <param name="in_vector_">: EmuMath Vector to copy.</param>
	/// <returns>EmuMath Vector constructed via the provided in_vector_ argument.</returns>
	template<std::size_t OutSize_, typename OutT_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_copy(EmuMath::Vector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_copy<EmuMath::Vector<OutSize_, OutT_>, EmuMath::Vector<InSize_, InT_>&>(in_vector_);
	}

	template<typename OutT_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::Vector<InSize_, OutT_> vector_copy(EmuMath::Vector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_copy<EmuMath::Vector<InSize_, OutT_>, EmuMath::Vector<InSize_, InT_>&>(in_vector_);
	}

	template<std::size_t OutSize_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<InSize_, InT_>::value_type_uq> vector_copy(EmuMath::Vector<InSize_, InT_>& in_vector_)
	{
		using in_value_uq = typename EmuMath::Vector<InSize_, InT_>::value_type_uq;
		return _vector_underlying::_vector_copy<EmuMath::Vector<OutSize_, in_value_uq>, EmuMath::Vector<InSize_, InT_>&>(in_vector_);
	}

	template<std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<InSize_, typename EmuMath::Vector<InSize_, InT_>::value_type_uq> vector_copy(EmuMath::Vector<InSize_, InT_>& in_vector_)
	{
		using in_value_uq = typename EmuMath::Vector<InSize_, InT_>::value_type_uq;
		return _vector_underlying::_vector_copy<EmuMath::Vector<InSize_, in_value_uq>, EmuMath::Vector<InSize_, InT_>&>(in_vector_);
	}

	/// <summary>
	/// <para> Constructs an EmuMath Vector of the specified type using the provided input EmuMath Vector argument. </para>
	/// </summary>
	/// <param name="in_vector_">: EmuMath Vector to copy.</param>
	/// <returns>EmuMath Vector constructed via the provided in_vector_ argument.</returns>
	template<std::size_t OutSize_, typename OutT_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_copy(const EmuMath::Vector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_copy<EmuMath::Vector<OutSize_, OutT_>, const EmuMath::Vector<InSize_, InT_>&>(in_vector_);
	}

	template<typename OutT_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::Vector<InSize_, OutT_> vector_copy(const EmuMath::Vector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_copy<EmuMath::Vector<InSize_, OutT_>, const EmuMath::Vector<InSize_, InT_>&>(in_vector_);
	}

	template<std::size_t OutSize_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<InSize_, InT_>::value_type_uq> vector_copy(const EmuMath::Vector<InSize_, InT_>& in_vector_)
	{
		using in_value_uq = typename EmuMath::Vector<InSize_, InT_>::value_type_uq;
		return _vector_underlying::_vector_copy<EmuMath::Vector<OutSize_, in_value_uq>, const EmuMath::Vector<InSize_, InT_>&>(in_vector_);
	}

	template<std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<InSize_, typename EmuMath::Vector<InSize_, InT_>::value_type_uq> vector_copy(const EmuMath::Vector<InSize_, InT_>& in_vector_)
	{
		using in_value_uq = typename EmuMath::Vector<InSize_, InT_>::value_type_uq;
		return _vector_underlying::_vector_copy<EmuMath::Vector<InSize_, in_value_uq>, const EmuMath::Vector<InSize_, InT_>&>(in_vector_);
	}

	/// <summary>
	/// <para> Constructs an EmuMath Vector of the specified type using the provided input EmuMath Vector argument. </para>
	/// </summary>
	/// <param name="in_vector_">: EmuMath Vector to copy.</param>
	/// <returns>EmuMath Vector constructed via the provided in_vector_ argument.</returns>
	template<std::size_t OutSize_, typename OutT_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_copy(EmuMath::Vector<InSize_, InT_>&& in_vector_)
	{
		using in_vec_type = EmuMath::Vector<InSize_, InT_>;
		return _vector_underlying::_vector_copy<EmuMath::Vector<OutSize_, OutT_>, in_vec_type>(std::forward<in_vec_type>(in_vector_));
	}

	template<typename OutT_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::Vector<InSize_, OutT_> vector_copy(EmuMath::Vector<InSize_, InT_>&& in_vector_)
	{
		using in_vec_type = EmuMath::Vector<InSize_, InT_>;
		return _vector_underlying::_vector_copy<EmuMath::Vector<InSize_, OutT_>, in_vec_type>(std::forward<in_vec_type>(in_vector_));
	}

	template<std::size_t OutSize_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<InSize_, InT_>::value_type_uq> vector_copy(EmuMath::Vector<InSize_, InT_>&& in_vector_)
	{
		using in_vec_type = EmuMath::Vector<InSize_, InT_>;
		using in_value_uq = typename in_vec_type::value_type_uq;
		return _vector_underlying::_vector_copy<EmuMath::Vector<OutSize_, in_value_uq>, in_vec_type>(std::forward<in_vec_type>(in_vector_));
	}

	template<std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<InSize_, typename EmuMath::Vector<InSize_, InT_>::value_type_uq> vector_copy(EmuMath::Vector<InSize_, InT_>&& in_vector_)
	{
		using in_vec_type = EmuMath::Vector<InSize_, InT_>;
		using in_value_uq = typename in_vec_type::value_type_uq;
		return _vector_underlying::_vector_copy<EmuMath::Vector<InSize_, in_value_uq>, in_vec_type>(std::forward<in_vec_type>(in_vector_));
	}
}

#endif
