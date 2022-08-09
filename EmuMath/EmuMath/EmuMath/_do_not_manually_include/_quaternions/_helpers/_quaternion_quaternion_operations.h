#ifndef EMU_MATH_QUATERNION_QUATERNION_OPERATIONS_H_INC_
#define EMU_MATH_QUATERNION_QUATERNION_OPERATIONS_H_INC_ 1

#include "_common_quaternion_helper_includes.h"

namespace EmuMath::Helpers
{
#pragma region VALIDITY_CHECKS
	/// <summary>
	/// <para> Check to see if an EmuMath Quaternion with the typearg T_ can have its Conjugate calculated and output as an EmuMath Quaternion with the typearg OutT_. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if the Conjugate of a Quaternion with typearg T_  can be calculated and output as a Quaternion with typearg OutT_.</returns>
	template<typename T_, typename OutT_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_make_conjugate()
	{
		return _quaternion_underlying::_valid_conjugate_args<false, T_, OutT_, StaticAssert_>();
	}

	/// <summary>
	/// <para> Check to see if an EmuMath Quaternion with the typearg T_ can have its Squared Norm calculated and output as the type Out_. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if the Squared Norm of a Quaternion with typearg T_  can be calculated and output as type Out_.</returns>
	template<typename T_, typename Out_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_make_square_norm()
	{
		return _quaternion_underlying::_valid_square_norm_args<false, T_, Out_, StaticAssert_>();
	}

	/// <summary>
	/// <para>
	///		Check to see if an EmuMath Quaternion with the typearg T_ can have its Squared Norm calculated and output as the type Out_,
	///		using fused operations where possible.
	/// </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if the Squared Norm of a Quaternion with typearg T_  can be calculated and output as type Out_.</returns>
	template<typename T_, typename Out_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_make_fused_square_norm()
	{
		return _quaternion_underlying::_valid_square_norm_args<true, T_, Out_, StaticAssert_>();
	}

	/// <summary>
	/// <para> Check to see if an EmuMath Quaternion with the typearg T_ can have its Norm calculated and output as the type Out_. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if the Norm of a Quaternion with typearg T_  can be calculated and output as type Out_.</returns>
	template<typename T_, typename Out_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_make_norm()
	{
		return _quaternion_underlying::_valid_norm_args<false, false, T_, Out_, StaticAssert_>();
	}

	/// <summary>
	/// <para> Check to see if an EmuMath Quaternion with the typearg T_ can have its Norm calculated and output as the type Out_, using fused operations where possible. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if the Norm of a Quaternion with typearg T_  can be calculated and output as type Out_.</returns>
	template<typename T_, typename Out_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_make_fused_norm()
	{
		return _quaternion_underlying::_valid_norm_args<false, false, T_, Out_, StaticAssert_>();
	}

	/// <summary>
	/// <para>
	///		Check to see if an EmuMath Quaternion with the typearg T_ can have its Norm calculated and output as the type Out_ 
	///		(in a context aiming to be constexpr-evaluable).
	/// </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if the Norm of a Quaternion with typearg T_  can be calculated and output as type Out_.</returns>
	template<typename T_, typename Out_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_make_norm_constexpr()
	{
		return _quaternion_underlying::_valid_norm_args<false, true, T_, Out_, StaticAssert_>();
	}

	/// <summary>
	/// <para> Check to see if an EmuMath Quaternion with the typearg T_ can have its Inverse calculated and output as an EmuMath Quaternion with the typearg OutT_. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if the Inverse of a Quaternion with typearg T_  can be calculated and output as a Quaternion with typearg OutT_.</returns>
	template<bool PreferMultiplies_, typename T_, typename OutT_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_make_inverse()
	{
		return _quaternion_underlying::_valid_inverse_args<false, PreferMultiplies_, false, false, T_, OutT_, StaticAssert_>();
	}

	template<typename T_, typename OutT_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_make_inverse()
	{
		return _quaternion_underlying::_valid_inverse_args<false, false, false, false, T_, OutT_, StaticAssert_>();
	}

	/// <summary>
	/// <para> 
	///		Check to see if an EmuMath Quaternion with the typearg T_ can have its Inverse calculated and output as an EmuMath Quaternion with the typearg OutT_, 
	///		using fused operations where possible.
	/// </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if the Inverse of a Quaternion with typearg T_  can be calculated and output as a Quaternion with typearg OutT_.</returns>
	template<bool PreferMultiplies_, typename T_, typename OutT_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_make_fused_inverse()
	{
		return _quaternion_underlying::_valid_inverse_args<false, PreferMultiplies_, true, false, T_, OutT_, StaticAssert_>();
	}

	template<typename T_, typename OutT_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_make_fused_inverse()
	{
		return _quaternion_underlying::_valid_inverse_args<false, false, true, false, T_, OutT_, StaticAssert_>();
	}

	/// <summary>
	/// <para> 
	///		Check to see if an EmuMath Quaternion with the typearg T_ can have its Inverse calculated and output as an EmuMath Quaternion with the typearg OutT_ 
	///		(in a context aiming to be constexpr-evaluable).
	/// </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if the Inverse of a Quaternion with typearg T_  can be calculated and output as a Quaternion with typearg OutT_.</returns>
	template<bool PreferMultiplies_, typename T_, typename OutT_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_make_inverse_constexpr()
	{
		return _quaternion_underlying::_valid_inverse_args<false, PreferMultiplies_, false, true, T_, OutT_, StaticAssert_>();
	}

	template<typename T_, typename OutT_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_make_inverse_constexpr()
	{
		return _quaternion_underlying::_valid_inverse_args<false, false, false, true, T_, OutT_, StaticAssert_>();
	}

	/// <summary>
	/// <para> Check to see if an EmuMath Quaternion with the typearg T_ can have its Unit form calculated and output as an EmuMath Quaternion with the typearg OutT_. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if the Unity form of a Quaternion with typearg T_  can be calculated and output as a Quaternion with typearg OutT_.</returns>
	template<bool PreferMultiplies_, typename T_, typename OutT_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_make_unit()
	{
		return _quaternion_underlying::_valid_unit_args<false, false, false, false, PreferMultiplies_, OutT_, T_, StaticAssert_>();
	}

	template<typename T_, typename OutT_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_make_unit()
	{
		return _quaternion_underlying::_valid_unit_args<false, false, false, false, false, OutT_, T_, StaticAssert_>();
	}

	/// <summary>
	/// <para> 
	///		Check to see if an EmuMath Quaternion with the typearg T_ can have its Unit form calculated and output as an EmuMath Quaternion with the typearg OutT_,
	///		using fused operations where possible.
	/// </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if the Unity form of a Quaternion with typearg T_  can be calculated and output as a Quaternion with typearg OutT_.</returns>
	template<bool PreferMultiplies_, typename T_, typename OutT_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_make_fused_unit()
	{
		return _quaternion_underlying::_valid_unit_args<false, false, true, false, PreferMultiplies_, OutT_, T_, StaticAssert_>();
	}

	template<typename T_, typename OutT_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_make_fused_unit()
	{
		return _quaternion_underlying::_valid_unit_args<false, false, true, false, false, OutT_, T_, StaticAssert_>();
	}

	/// <summary>
	/// <para>
	///		Check to see if an EmuMath Quaternion with the typearg T_ can have its Unit form calculated and output as an EmuMath Quaternion with the typearg OutT_ 
	///		(in a context aiming to be constexpr-evaluable).
	/// </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if the Unity form of a Quaternion with typearg T_  can be calculated and output as a Quaternion with typearg OutT_.</returns>
	template<bool PreferMultiplies_, typename T_, typename OutT_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_make_unit_constexpr()
	{
		return _quaternion_underlying::_valid_unit_args<false, false, false, true, PreferMultiplies_, OutT_, T_, StaticAssert_>();
	}

	template<typename T_, typename OutT_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_make_unit_constexpr()
	{
		return _quaternion_underlying::_valid_unit_args<false, false, false, true, false, OutT_, T_, StaticAssert_>();
	}

	/// <summary>
	/// <para> Check to see if an EmuMath Quaternion with the typearg T_ can have its Unit form calculated and assigned to itself. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if the Unity form of a Quaternion with typearg T_  can be calculated and output as a Quaternion with typearg OutT_.</returns>
	template<bool PreferMultiplies_, typename T_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_assign_unit()
	{
		return _quaternion_underlying::_valid_unit_args<true, false, false, false, PreferMultiplies_, T_, T_, StaticAssert_>();
	}

	template<typename T_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_assign_unit()
	{
		return _quaternion_underlying::_valid_unit_args<true, false, false, false, false, T_, T_, StaticAssert_>();
	}

	/// <summary>
	/// <para> Check to see if an EmuMath Quaternion with the typearg T_ can have its Unit form calculated and assigned to itself, using fused operations where possible. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if the Unity form of a Quaternion with typearg T_  can be calculated and output as a Quaternion with typearg OutT_.</returns>
	template<bool PreferMultiplies_, typename T_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_assign_fused_unit()
	{
		return _quaternion_underlying::_valid_unit_args<true, false, true, false, PreferMultiplies_, T_, T_, StaticAssert_>();
	}

	template<typename T_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_assign_fused_unit()
	{
		return _quaternion_underlying::_valid_unit_args<true, false, true, false, false, T_, T_, StaticAssert_>();
	}

	/// <summary>
	/// <para>
	///		Check to see if an EmuMath Quaternion with the typearg T_ can have its Unit form calculated and assigned to itself 
	///		(in a context aiming to be constexpr-evaluable).
	/// </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if the Unity form of a Quaternion with typearg T_  can be calculated and output as a Quaternion with typearg OutT_.</returns>
	template<bool PreferMultiplies_, typename T_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_assign_unit_constexpr()
	{
		return _quaternion_underlying::_valid_unit_args<true, false, false, true, PreferMultiplies_, T_, T_, StaticAssert_>();
	}

	template<typename T_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_assign_unit_constexpr()
	{
		return _quaternion_underlying::_valid_unit_args<true, false, false, true, false, T_, T_, StaticAssert_>();
	}
#pragma endregion

#pragma region CONJUGATE_FUNCS
	/// <summary>
	/// <para> Calculates the Conjugate of the input Quaternion, which is equal to the Quaternion with its imaginary XYZ negated and the same, unmodified W value. </para>
	/// </summary>
	/// <param name="quaternion_">EmuMath Quaternion to calculate the Conjugate of.</param>
	/// <returns>Conjugate of the passed Quaternion.</returns>
	template<typename OutT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_conjugate(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_make_conjugate<T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_conjugate<false, OutT_>(quaternion_);
	}
#pragma endregion

#pragma region SQUARE_NORM_FUNCS
	/// <summary>
	/// <para> Calculates the Squared Norm of the input Quaternion (i.e. its Norm before a final square root operation). </para>
	/// </summary>
	/// <param name="quaternion_">EmuMath Quaternion to calculate the Squared Norm of.</param>
	/// <returns>Squared Norm of the passed Quaternion.</returns>
	template<typename Out_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_square_norm(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_make_square_norm<T_, Out_, false>(), Out_>
	{
		return _quaternion_underlying::_make_square_norm<false, Out_>(quaternion_);
	}

	/// <summary>
	/// <para> Calculates the Squared Norm of the input Quaternion (i.e. its Norm before a final square root operation). </para>
	/// <para>
	///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
	///		Use of such instructions may improve accuracy and/or performance.
	/// </para>
	/// </summary>
	/// <param name="quaternion_">EmuMath Quaternion to calculate the Squared Norm of.</param>
	/// <returns>Squared Norm of the passed Quaternion.</returns>
	template<typename Out_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_fused_square_norm(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_make_fused_square_norm<T_, Out_, false>(), Out_>
	{
		return _quaternion_underlying::_make_square_norm<true, Out_>(quaternion_);
	}
#pragma endregion

#pragma region NORM_FUNCS
	/// <summary>
	/// <para> Calculates the Norm of the input Quaternion. </para>
	/// </summary>
	/// <param name="quaternion_">EmuMath Quaternion to calculate the Squared Norm of.</param>
	/// <returns>Norm of the passed Quaternion.</returns>
	template<typename Out_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_norm(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_make_norm<T_, Out_, false>(), Out_>
	{
		return _quaternion_underlying::_make_norm<false, false, Out_>(quaternion_);
	}

	/// <summary>
	/// <para> Calculates the Norm of the input Quaternion. </para>
	/// <para>
	///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
	///		Use of such instructions may improve accuracy and/or performance.
	/// </para>
	/// </summary>
	/// <param name="quaternion_">EmuMath Quaternion to calculate the Squared Norm of.</param>
	/// <returns>Norm of the passed Quaternion.</returns>
	template<typename Out_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_fused_norm(const EmuMath::Quaternion<T_>& quaternion_)
	{
		return _quaternion_underlying::_make_norm<true, false, Out_>(quaternion_);
	}

	/// <summary>
	/// <para> Calculates the Norm of the input Quaternion. </para>
	/// <para> This function will attempt to be constexpr-evaluable, which may have an effect on accuracy and/or performance. </para>
	/// </summary>
	/// <param name="quaternion_">EmuMath Quaternion to calculate the Squared Norm of.</param>
	/// <returns>Norm of the passed Quaternion.</returns>
	template<typename Out_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_norm_constexpr(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_make_norm_constexpr<T_, Out_, false>(), Out_>
	{
		return _quaternion_underlying::_make_norm<false, true, Out_>(quaternion_);
	}
#pragma endregion

#pragma region INVERSE_FUNCS
	/// <summary>
	/// <para> Calculates the normalised Inverse of the input Quaternion, which is equal to the Conjugate of its Unit form. </para>
	/// <para> If it is known that `quaternion_` is normalised, it may be preferable to use `quaternion_conjugate` as the result will be identical for lower performance costs. </para>
	/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
	/// </summary>
	/// <param name="quaternion_">EmuMath Quaternion to calculate the normalised inverse of.</param>
	/// <returns>Normalised Inverse of the passed Quaternion.</returns>
	template<bool PreferMultiplies_, typename OutT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_inverse(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_make_inverse<PreferMultiplies_, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_inverse<false, PreferMultiplies_, false, false, OutT_>(quaternion_);
	}

	template<typename OutT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_inverse(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_make_inverse<false, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_inverse<false, false, false, false, OutT_>(quaternion_);
	}

	/// <summary>
	/// <para> Calculates the normalised Inverse of the input Quaternion, which is equal to the Conjugate of its Unit form. </para>
	/// <para> If it is known that `quaternion_` is normalised, it may be preferable to use `quaternion_conjugate` as the result will be identical for lower performance costs. </para>
	/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
	/// <para>
	///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
	///		Use of such instructions may improve accuracy and/or performance.
	/// </para>
	/// </summary>
	/// <param name="quaternion_">EmuMath Quaternion to calculate the normalised inverse of.</param>
	/// <returns>Normalised Inverse of the passed Quaternion.</returns>
	template<bool PreferMultiplies_, typename OutT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_fused_inverse(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_make_fused_inverse<PreferMultiplies_, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_inverse<false, PreferMultiplies_, true, false, OutT_>(quaternion_);
	}

	template<typename OutT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_fused_inverse(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_make_fused_inverse<false, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_inverse<false, false, true, false, OutT_>(quaternion_);
	}

	/// <summary>
	/// <para> Calculates the normalised Inverse of the input Quaternion, which is equal to the Conjugate of its Unit form. </para>
	/// <para> If it is known that `quaternion_` is normalised, it may be preferable to use `quaternion_conjugate` as the result will be identical for lower performance costs. </para>
	/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
	/// <para> This function will attempt to be constexpr-evaluable, which may have an effect on accuracy and/or performance. </para>
	/// </summary>
	/// <param name="quaternion_">EmuMath Quaternion to calculate the normalised inverse of.</param>
	/// <returns>Normalised Inverse of the passed Quaternion.</returns>
	template<bool PreferMultiplies_, typename OutT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_inverse_constexpr(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_make_inverse_constexpr<PreferMultiplies_, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_inverse<false, PreferMultiplies_, false, true, OutT_>(quaternion_);
	}

	template<typename OutT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_inverse_constexpr(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_make_inverse_constexpr<false, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_inverse<false, false, false, true, OutT_>(quaternion_);
	}
#pragma endregion

#pragma region UNIT_FUNCS
	/// <summary>
	/// <para> Calculates the Unit form (aka the Normalised form) of the input Quaternion. </para>
	/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
	/// </summary>
	/// <param name="quaternion_">Quaternion to calculate the Unit form of.</param>
	/// <returns>Unit form of the passed Quaternion.</returns>
	template<bool PreferMultiplies_, typename OutT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_unit(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_make_unit<PreferMultiplies_, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_unit<false, false, false, PreferMultiplies_, OutT_>(quaternion_);
	}

	template<typename OutT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_unit(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_make_unit<false, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_unit<false, false, false, false, OutT_>(quaternion_);
	}

	/// <summary>
	/// <para> Calculates the Unit form (aka the Normalised form) of the input Quaternion. </para>
	/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
	/// <para>
	///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
	///		Use of such instructions may improve accuracy and/or performance.
	/// </para>
	/// </summary>
	/// <param name="quaternion_">Quaternion to calculate the Unit form of.</param>
	/// <returns>Unit form of the passed Quaternion.</returns>
	template<bool PreferMultiplies_, typename OutT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_fused_unit(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_make_unit<PreferMultiplies_, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_unit<false, true, false, PreferMultiplies_, OutT_>(quaternion_);
	}

	template<typename OutT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_fused_unit(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_make_unit<false, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_unit<false, true, false, false, OutT_>(quaternion_);
	}

	/// <summary>
	/// <para> Calculates the Unit form (aka the Normalised form) of the input Quaternion. </para>
	/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
	/// <para> This function will attempt to be constexpr-evaluable, which may have an effect on accuracy and/or performance. </para>
	/// </summary>
	/// <param name="quaternion_">Quaternion to calculate the Unit form of.</param>
	/// <returns>Unit form of the passed Quaternion.</returns>
	template<bool PreferMultiplies_, typename OutT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_unit_constexpr(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_make_unit<PreferMultiplies_, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_unit<false, false, true, PreferMultiplies_, OutT_>(quaternion_);
	}

	template<typename OutT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_unit_constexpr(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_make_unit<false, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_unit<false, false, true, false, OutT_>(quaternion_);
	}

	/// <summary>
	/// <para> Calculates the Unit form (aka the Normalised form) of the input Quaternion and assigns the result to itself. </para>
	/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
	/// </summary>
	/// <param name="in_out_quaternion_">Quaternion to calculate the Unit form of and assign the results to.</param>
	template<bool PreferMultiplies_, typename T_>
	constexpr inline auto quaternion_assign_unit(EmuMath::Quaternion<T_>& in_out_quaternion_)
		-> std::enable_if_t<quaternion_can_assign_unit<PreferMultiplies_, T_, false>(), void>
	{
		_quaternion_underlying::_assign_unit<false, false, PreferMultiplies_>(in_out_quaternion_);
	}

	template<typename T_>
	constexpr inline auto quaternion_assign_unit(EmuMath::Quaternion<T_>& in_out_quaternion_)
		-> std::enable_if_t<quaternion_can_assign_unit<false, T_, false>(), void>
	{
		_quaternion_underlying::_assign_unit<false, false, false>(in_out_quaternion_);
	}

	/// <summary>
	/// <para> Calculates the Unit form (aka the Normalised form) of the input Quaternion and assigns the result to itself. </para>
	/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
	/// <para>
	///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
	///		Use of such instructions may improve accuracy and/or performance.
	/// </para>
	/// </summary>
	/// <param name="in_out_quaternion_">Quaternion to calculate the Unit form of and assign the results to.</param>
	template<bool PreferMultiplies_, typename T_>
	constexpr inline auto quaternion_assign_fused_unit(EmuMath::Quaternion<T_>& in_out_quaternion_)
		-> std::enable_if_t<quaternion_can_assign_fused_unit<PreferMultiplies_, T_, false>(), void>
	{
		_quaternion_underlying::_assign_unit<true, false, PreferMultiplies_>(in_out_quaternion_);
	}

	template<typename T_>
	constexpr inline auto quaternion_assign_fused_unit(EmuMath::Quaternion<T_>& in_out_quaternion_)
		-> std::enable_if_t<quaternion_can_assign_fused_unit<false, T_, false>(), void>
	{
		_quaternion_underlying::_assign_unit<true, false, false>(in_out_quaternion_);
	}

	/// <summary>
	/// <para> Calculates the Unit form (aka the Normalised form) of the input Quaternion and assigns the result to itself. </para>
	/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
	/// <para> This function will attempt to be constexpr-evaluable, which may have an effect on accuracy and/or performance. </para>
	/// </summary>
	/// <param name="in_out_quaternion_">Quaternion to calculate the Unit form of and assign the results to.</param>
	template<bool PreferMultiplies_, typename T_>
	constexpr inline auto quaternion_assign_unit_constexpr(EmuMath::Quaternion<T_>& in_out_quaternion_)
		-> std::enable_if_t<quaternion_can_assign_unit_constexpr<PreferMultiplies_, T_, false>(), void>
	{
		_quaternion_underlying::_assign_unit<false, true, PreferMultiplies_>(in_out_quaternion_);
	}

	template<typename T_>
	constexpr inline auto quaternion_assign_unit_constexpr(EmuMath::Quaternion<T_>& in_out_quaternion_)
		-> std::enable_if_t<quaternion_can_assign_unit_constexpr<false, T_, false>(), void>
	{
		_quaternion_underlying::_assign_unit<false, true, false>(in_out_quaternion_);
	}
#pragma endregion
}

#endif

