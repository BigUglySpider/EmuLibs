#ifndef EMU_MATH_FAST_QUATERNION_TO_EULER_H_INC_
#define EMU_MATH_FAST_QUATERNION_TO_EULER_H_INC_ 1

#include "_common_fast_quaternion_includes.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Converts the passed FastQuaternion to euler angles XYZ, returning the result as a scalar EmuMath Vector. </para>
	/// <para> The output Vector's contained type/size may be customised. By default, they are `void`/`3`, respectively. </para>
	/// <para> If the output Vector's contained type is `void`, it will instead use the `preferred_floating_point` of the input FastQuaternion. </para>
	/// </summary>
	/// <param name="in_quaternion_">FastQuaternion to convert to euler angles.</param>
	/// <param name="epsilon_">
	///		Arithmetic value indicating the epsilon to use for floating-point comparisons in conversions. 
	///		This may be omitted, in which case the function will use the default epsilon of the input Quaternion's `preferred_floating_point` type, 
	///		as determined by `EmuCore::epsilon`.
	/// </param>
	/// <returns>Scalar EmuMath Vector containing the results of converting the input Quaternion to euler angles.</returns>
	template
	<
		bool OutRads_ = true,
		typename OutT_ = void,
		std::size_t OutSize_ = 3,
		EmuConcepts::EmuFastQuaternion InFastQuaternion_,
		EmuConcepts::Arithmetic Epsilon_
	>
	[[nodiscard]] constexpr inline auto fast_quaternion_to_euler_scalar(InFastQuaternion_&& in_quaternion_, Epsilon_&& epsilon_)
		-> EmuMath::Vector
		<
			OutSize_,
			typename std::conditional
			<
				std::is_void_v<OutT_>,
				typename EmuCore::TMP::remove_ref_cv_t<InFastQuaternion_>::preferred_floating_point,
				OutT_
			>::type
		>
	{
		using _in_quat_uq = typename EmuCore::TMP::remove_ref_cv<InFastQuaternion_>::type;
		using _scalar_fp = typename _in_quat_uq::preferred_floating_point;
		using _out_vec_t = typename std::conditional<std::is_void_v<OutT_>, _scalar_fp, OutT_>::type;

		return _fast_quaternion_underlying::_make_euler_from_fast_quat<EmuMath::Vector<OutSize_, _out_vec_t>, _scalar_fp, OutRads_>
		(
			std::forward<InFastQuaternion_>(in_quaternion_),
			std::forward<Epsilon_>(epsilon_)
		);
	}

	template<bool OutRads_ = true, typename OutT_ = void, std::size_t OutSize_ = 3, EmuConcepts::EmuFastQuaternion InFastQuaternion_>
	[[nodiscard]] constexpr inline auto fast_quaternion_to_euler_scalar(InFastQuaternion_&& in_quaternion_)
		-> EmuMath::Vector
		<
			OutSize_,
			typename std::conditional
			<
				std::is_void_v<OutT_>,
				typename EmuCore::TMP::remove_ref_cv_t<InFastQuaternion_>::preferred_floating_point,
				OutT_
			>::type
		>
	{
		using _in_quat_uq = typename EmuCore::TMP::remove_ref_cv<InFastQuaternion_>::type;
		using _scalar_fp = typename _in_quat_uq::preferred_floating_point;
		using _out_vec_t = typename std::conditional<std::is_void_v<OutT_>, _scalar_fp, OutT_>::type;

		return _fast_quaternion_underlying::_make_euler_from_fast_quat<EmuMath::Vector<OutSize_, _out_vec_t>, _scalar_fp, OutRads_>
		(
			std::forward<InFastQuaternion_>(in_quaternion_),
			EmuCore::epsilon<_scalar_fp>::get()
		);
	}

	/// <summary>
	/// <para> Converts the passed FastQuaternion to euler angles XYZ, returning the result as an EmuMath FastVector. </para>
	/// <para> The output Vector's T_ argument will always be the `preferred_floating_point` of the input FastQuaternion. </para>
	/// <para> The output Vector's size may be customised. By default, it is 3. </para>
	/// <para> The output Vector's register width may be customised. By default, it is 0. </para>
	/// <para> If the output Vector's register width is 0, it will instead use the `register_width` of the input FastQuaternion. </para>
	/// </summary>
	/// <param name="in_quaternion_">FastQuaternion to convert to euler angles.</param>
	/// <param name="epsilon_">
	///		Arithmetic value indicating the epsilon to use for floating-point comparisons in conversions. 
	///		This may be omitted, in which case the function will use the default epsilon of the input Quaternion's `preferred_floating_point` type, 
	///		as determined by `EmuCore::epsilon`.
	/// </param>
	/// <returns>EmuMath Fast Vector containing the results of converting the input Quaternion to euler angles.</returns>
	template
	<
		bool OutRads_ = true,
		std::size_t OutSize_ = 3,
		std::size_t OutRegisterWidth_ = 0,
		EmuConcepts::EmuFastQuaternion InFastQuaternion_,
		EmuConcepts::Arithmetic Epsilon_
	>
	[[nodiscard]] constexpr inline auto fast_quaternion_to_euler(InFastQuaternion_&& in_quaternion_, Epsilon_&& epsilon_)
		-> EmuMath::FastVector
		<
			OutSize_,
			typename EmuCore::TMP::remove_ref_cv_t<InFastQuaternion_>::preferred_floating_point,
			OutRegisterWidth_ == 0 ? EmuCore::TMP::remove_ref_cv_t<InFastQuaternion_>::register_width : OutRegisterWidth_
		>
	{
		using _in_quat_uq = typename EmuCore::TMP::remove_ref_cv<InFastQuaternion_>::type;
		using _scalar_fp = typename _in_quat_uq::preferred_floating_point;
		constexpr std::size_t register_width = OutRegisterWidth_ == 0 ? _in_quat_uq::register_width : OutRegisterWidth_;

		// Potential optimisation: Convert to degrees (when OutRads_ = false) with a SIMD operation after initial store to register
		return _fast_quaternion_underlying::_make_euler_from_fast_quat<EmuMath::FastVector<OutSize_, _scalar_fp, register_width>, _scalar_fp, OutRads_>
		(
			std::forward<InFastQuaternion_>(in_quaternion_),
			std::forward<Epsilon_>(epsilon_)
		);	
	}

	template<bool OutRads_ = true, std::size_t OutSize_ = 3, std::size_t OutRegisterWidth_ = 0, EmuConcepts::EmuFastQuaternion InFastQuaternion_>
	[[nodiscard]] constexpr inline auto fast_quaternion_to_euler(InFastQuaternion_&& in_quaternion_)
		-> EmuMath::FastVector
		<
			OutSize_,
			typename EmuCore::TMP::remove_ref_cv_t<InFastQuaternion_>::preferred_floating_point,
			OutRegisterWidth_ == 0 ? EmuCore::TMP::remove_ref_cv_t<InFastQuaternion_>::register_width : OutRegisterWidth_
		>
	{
		using _in_quat_uq = typename EmuCore::TMP::remove_ref_cv<InFastQuaternion_>::type;
		using _scalar_fp = typename _in_quat_uq::preferred_floating_point;
		constexpr std::size_t register_width = OutRegisterWidth_ == 0 ? _in_quat_uq::register_width : OutRegisterWidth_;

		// Potential optimisation: Convert to degrees (when OutRads_ = false) with a SIMD operation after initial store to register
		return _fast_quaternion_underlying::_make_euler_from_fast_quat<EmuMath::FastVector<OutSize_, _scalar_fp, register_width>, _scalar_fp, OutRads_>
		(
			std::forward<InFastQuaternion_>(in_quaternion_),
			EmuCore::epsilon<_scalar_fp>::get()
		);	
	}
}

#endif
