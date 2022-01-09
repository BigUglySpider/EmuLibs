#ifndef EMU_MATH_vector_CAST_H_INC_
#define EMU_MATH_vector_CAST_H_INC_ 1

#include "_common_vector_helpers.h"

// Contains:
// --- cast_is_valid
// --- cast
// --- EmuCore::TMP::is_static_castable specialisations for EmuMath Vector From_ -> To_ args

namespace EmuMath::Helpers
{
#pragma region VALIDITY_CHECKS
	/// <summary>
	/// <para> Compile-time validity check to ensure an EmuMath Vector of InSize_ and InT_ can be cast to an EmuMath Vector of OutSize_ and OutT_. </para>
	/// <para> InSize_: The Size_ argument of the input Vector. </para>
	/// <para> InT_: The T_ argument of the input Vector. </para>
	/// <para> OutSize_: The Size_ argument of the output Vector. </para>
	/// <para> OutT_: The T_ argument of the output Vector. </para>
	/// <para> InIsConst_: True if the input Vector should be treated as const-qualified. </para>
	/// <para> InIsLvalRef_: True if the input Vector should be treated as a named value. Otherwise, it will be treated as a temporary rvalue. </para>
	/// <para> Offset_: Inclusive index at which to start reading from the input Vector. Defaults to 0. </para>
	/// </summary>
	/// <returns>True if an EmuMath Vector cast to the provided output Vector is valid given the provided input Vector and its state descriptors.</returns>
	template<std::size_t InSize_, typename InT_, std::size_t OutSize_, typename OutT_, bool InIsConst_, bool InIsLvalRef_, std::size_t Offset_ = 0>
	[[nodiscard]] constexpr inline bool vector_cast_is_valid()
	{
		using in_vector_raw = EmuMath::NewVector<InSize_, InT_>;
		using in_ref_qualified = std::conditional_t<InIsLvalRef_, std::add_lvalue_reference_t<in_vector_raw>, in_vector_raw>;
		using in_fully_qualified = EmuCore::TMP::conditional_const_t<InIsConst_, in_ref_qualified>;
		return _vector_underlying::_vector_cast_valid<in_fully_qualified, OutSize_, OutT_, Offset_>;
	}

	/// <summary>
	/// <para> Compile-time validity check to ensure an EmuMath Vector of InSize_ and InT_ can be cast to an EmuMath Vector of OutSize_ and OutT_. </para>
	/// <para> InSize_: The Size_ argument of the input Vector. </para>
	/// <para> InT_: The T_ argument of the input Vector. </para>
	/// <para> OutVector_: EmuMath Vector to cast to. Any qualifiers, including reference, are ignored (e.g. const T_&amp; will be treated as T_) </para>
	/// <para> InIsConst_: True if the input Vector should be treated as const-qualified. </para>
	/// <para> InIsLvalRef_: True if the input Vector should be treated as a named value. Otherwise, it will be treated as a temporary rvalue. </para>
	/// <para> Offset_: Inclusive index at which to start reading from the input Vector. Defaults to 0. </para>
	/// </summary>
	/// <returns>True if an EmuMath Vector cast to the provided OutVector_ (unqualified) is valid given the provided input Vector and its state descriptors.</returns>
	template<std::size_t InSize_, typename InT_, class OutVector_, bool InIsConst_, bool InIsLvalRef_, std::size_t Offset_ = 0>
	[[nodiscard]] constexpr inline bool vector_cast_is_valid()
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<OutVector_>)
		{
			using out_args = EmuMath::TMP::emu_vector_template_args<OutVector_>;
			return vector_cast_is_valid<InSize_, InT_, out_args::Size_, typename out_args::T_, InIsConst_, InIsLvalRef_, Offset_>();
		}
		else
		{
			return false;
		}
	}

	/// <summary>
	/// <para> Compile-time validity check to ensure an EmuMath Vector of InSize_ and InT_ can be cast to an EmuMath Vector of OutSize_ and OutT_. </para>
	/// <para>
	///		InVector_: EmuMath Vector type used as input. Const and reference qualifiers are recognised and responded to correctly. 
	///		If InVector_ is has no reference qualifiers, it will be treated as a temporary rvalue.
	/// </para>
	/// <para> OutSize_: The Size_ argument of the output Vector. </para>
	/// <para> OutT_: The T_ argument of the output Vector. </para>
	/// <para> Offset_: Inclusive index at which to start reading from the input Vector. Defaults to 0. </para>
	/// </summary>
	/// <returns>True if an EmuMath Vector cast to the provided output Vector is valid given the provided input Vector.</returns>
	template<class InVector_, std::size_t OutSize_, typename OutT_, std::size_t Offset_ = 0>
	[[nodiscard]] constexpr inline bool vector_cast_is_valid()
	{
		return _vector_underlying::_vector_cast_valid<InVector_, OutSize_, OutT_, Offset_>();
	}

	/// <summary>
	/// <para> Compile-time validity check to ensure an EmuMath Vector of InSize_ and InT_ can be cast to an EmuMath Vector of OutSize_ and OutT_. </para>
	/// <para>
	///		InVector_: EmuMath Vector type used as input. Const and reference qualifiers are recognised and responded to correctly. 
	///		If InVector_ is has no reference qualifiers, it will be treated as a temporary rvalue.
	/// </para>
	/// <para> OutVector_: EmuMath Vector to cast to. Any qualifiers, including reference, are ignored (e.g. const T_&amp; will be treated as T_) </para>
	/// <para> Offset_: Inclusive index at which to start reading from the input Vector. Defaults to 0. </para>
	/// </summary>
	/// <returns>True if an EmuMath Vector cast to the provided OutVector_ (unqualified) is valid given the provided input Vector.</returns>
	template<class InVector_, class OutVector_, std::size_t Offset_ = 0>
	[[nodiscard]] constexpr inline bool vector_cast_is_valid()
	{
		if constexpr (EmuCore::TMP::are_all_check<EmuMath::TMP::is_emu_vector, InVector_, OutVector_>::value)
		{
			using out_args = EmuMath::TMP::emu_vector_template_args<OutVector_>;
			return _vector_underlying::_vector_cast_valid<InVector_, out_args::Size_, typename out_args::T_, Offset_>();
		}
		else
		{
			return false;
		}
	}
#pragma endregion

#pragma region CONST_CASTS
	/// <summary>
	/// <para> Casts the passed EmuMath Vector to an EmuMath Vector of the specified OutSize_ and OutT_. </para>
	/// <para> OutSize_: Size of the output Vector. If not provided, this will default to the input Vector's Size_ arg. </para>
	/// <para> OutT_: Typearg for the output Vector. If not provided, this will default to the input Vector's value_type_uq. </para>
	/// <para> At least 1 of OutSize_ or OutT_ must be provided. </para>
	/// <para> Offset_: Optional offset at which to start reading the input Vector for forming the output cast. Defaults to 0. </para>
	/// </summary>
	/// <param name="in_vector_">Constant reference to an EmuMath Vector to cast.</param>
	/// <returns>The passed EmuMath Vector cast to the desired output Vector.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t Offset_ = 0, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> vector_cast(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_cast<OutSize_, OutT_, const EmuMath::NewVector<InSize_, InT_>&, Offset_>(in_vector_);
	}

	template<typename OutT_, std::size_t Offset_ = 0, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, OutT_> vector_cast(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_cast<InSize_, OutT_, const EmuMath::NewVector<InSize_, InT_>&, Offset_>(in_vector_);
	}

	template<std::size_t OutSize_, std::size_t Offset_ = 0, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq> vector_cast
	(
		const EmuMath::NewVector<InSize_, InT_>& in_vector_
	)
	{
		return _vector_underlying::_vector_cast
		<
			OutSize_,
			typename EmuMath::NewVector<InSize_, InT_>::value_type_uq,
			const EmuMath::NewVector<InSize_, InT_>&,
			Offset_
		>(in_vector_);
	}
#pragma endregion

#pragma region NON_CONST_CASTS
	/// <summary>
	/// <para> Casts the passed EmuMath Vector to an EmuMath Vector of the specified OutSize_ and OutT_. </para>
	/// <para> OutSize_: Size of the output Vector. If not provided, this will default to the input Vector's Size_ arg. </para>
	/// <para> OutT_: Typearg for the output Vector. If not provided, this will default to the input Vector's value_type_uq. </para>
	/// <para> At least 1 of OutSize_ or OutT_ must be provided. </para>
	/// <para> Offset_: Optional offset at which to start reading the input Vector for forming the output cast. Defaults to 0. </para>
	/// </summary>
	/// <param name="in_vector_">Reference to an EmuMath Vector to cast.</param>
	/// <returns>The passed EmuMath Vector cast to the desired output Vector.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t Offset_ = 0, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> vector_cast(EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_cast<OutSize_, OutT_, EmuMath::NewVector<InSize_, InT_>&, Offset_>(in_vector_);
	}

	template<typename OutT_, std::size_t Offset_ = 0, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, OutT_> vector_cast(EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_cast<InSize_, OutT_, EmuMath::NewVector<InSize_, InT_>&, Offset_>(in_vector_);
	}

	template<std::size_t OutSize_, std::size_t Offset_ = 0, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq> vector_cast
	(
		EmuMath::NewVector<InSize_, InT_>& in_vector_
	)
	{
		return _vector_underlying::_vector_cast
		<
			OutSize_,
			typename EmuMath::NewVector<InSize_, InT_>::value_type_uq,
			EmuMath::NewVector<InSize_, InT_>&,
			Offset_
		>(in_vector_);
	}
#pragma endregion

#pragma region RVALUE_CASTS
	/// <summary>
	/// <para> Casts the passed EmuMath Vector to an EmuMath Vector of the specified OutSize_ and OutT_. </para>
	/// <para> OutSize_: Size of the output Vector. If not provided, this will default to the input Vector's Size_ arg. </para>
	/// <para> OutT_: Typearg for the output Vector. If not provided, this will default to the input Vector's value_type_uq. </para>
	/// <para> At least 1 of OutSize_ or OutT_ must be provided. </para>
	/// <para> Offset_: Optional offset at which to start reading the input Vector for forming the output cast. Defaults to 0. </para>
	/// </summary>
	/// <param name="in_vector_">Rvalue-reference to an EmuMath Vector to cast.</param>
	/// <returns>The passed EmuMath Vector cast to the desired output Vector.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t Offset_ = 0, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> vector_cast(EmuMath::NewVector<InSize_, InT_>&& in_vector_)
	{
		return _vector_underlying::_vector_cast<OutSize_, OutT_, EmuMath::NewVector<InSize_, InT_>, Offset_>
		(
			std::forward<EmuMath::NewVector<InSize_, InT_>>(in_vector_)
		);
	}

	template<typename OutT_, std::size_t Offset_ = 0, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, OutT_> vector_cast(EmuMath::NewVector<InSize_, InT_>&& in_vector_)
	{
		return _vector_underlying::_vector_cast<InSize_, OutT_, EmuMath::NewVector<InSize_, InT_>, Offset_>
		(
			std::forward<EmuMath::NewVector<InSize_, InT_>>(in_vector_)
		);
	}

	template<std::size_t OutSize_, std::size_t Offset_ = 0, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq> vector_cast
	(
		EmuMath::NewVector<InSize_, InT_>&& in_vector_
	)
	{
		return _vector_underlying::_vector_cast
		<
			OutSize_,
			typename EmuMath::NewVector<InSize_, InT_>::value_type_uq,
			EmuMath::NewVector<InSize_, InT_>,
			Offset_
		>(std::forward<EmuMath::NewVector<InSize_, InT_>>(in_vector_));
	}
#pragma endregion
}

namespace EmuCore::TMP
{
#pragma region IS_STATIC_CASTABLE_SPECIALISATIONS
	// EmuMath Vector static_cast check specialisations: VALUE
	template<std::size_t FromSize_, typename FromT_, std::size_t ToSize_, typename ToT_>
	struct is_static_castable<EmuMath::NewVector<FromSize_, FromT_>, EmuMath::NewVector<ToSize_, ToT_>>
	{
		static constexpr bool value = EmuMath::Helpers::vector_cast_is_valid
		<
			EmuMath::NewVector<FromSize_, FromT_>,
			ToSize_,
			ToT_,
			0
		>();
	};
	template<std::size_t FromSize_, typename FromT_, std::size_t ToSize_, typename ToT_>
	struct is_static_castable<const EmuMath::NewVector<FromSize_, FromT_>, EmuMath::NewVector<ToSize_, ToT_>>
	{
		static constexpr bool value = EmuMath::Helpers::vector_cast_is_valid
		<
			const EmuMath::NewVector<FromSize_, FromT_>,
			ToSize_,
			ToT_,
			0
		>();
	};
	template<std::size_t FromSize_, typename FromT_, std::size_t ToSize_, typename ToT_>
	struct is_static_castable<volatile EmuMath::NewVector<FromSize_, FromT_>, EmuMath::NewVector<ToSize_, ToT_>>
	{
		static constexpr bool value = EmuMath::Helpers::vector_cast_is_valid
		<
			volatile EmuMath::NewVector<FromSize_, FromT_>,
			ToSize_,
			ToT_,
			0
		>();
	};
	template<std::size_t FromSize_, typename FromT_, std::size_t ToSize_, typename ToT_>
	struct is_static_castable<const volatile EmuMath::NewVector<FromSize_, FromT_>, EmuMath::NewVector<ToSize_, ToT_>>
	{
		static constexpr bool value = EmuMath::Helpers::vector_cast_is_valid
		<
			const volatile EmuMath::NewVector<FromSize_, FromT_>,
			ToSize_,
			ToT_,
			0
		>();
	};

	// EmuMath Vector static_cast check specialisations: LVAL REF
	template<std::size_t FromSize_, typename FromT_, std::size_t ToSize_, typename ToT_>
	struct is_static_castable<EmuMath::NewVector<FromSize_, FromT_>&, EmuMath::NewVector<ToSize_, ToT_>>
	{
		static constexpr bool value = EmuMath::Helpers::vector_cast_is_valid
		<
			EmuMath::NewVector<FromSize_, FromT_>&,
			ToSize_,
			ToT_,
			0
		>();
	};
	template<std::size_t FromSize_, typename FromT_, std::size_t ToSize_, typename ToT_>
	struct is_static_castable<const EmuMath::NewVector<FromSize_, FromT_>&, EmuMath::NewVector<ToSize_, ToT_>>
	{
		static constexpr bool value = EmuMath::Helpers::vector_cast_is_valid
		<
			const EmuMath::NewVector<FromSize_, FromT_>&,
			ToSize_,
			ToT_,
			0
		>();
	};
	template<std::size_t FromSize_, typename FromT_, std::size_t ToSize_, typename ToT_>
	struct is_static_castable<volatile EmuMath::NewVector<FromSize_, FromT_>&, EmuMath::NewVector<ToSize_, ToT_>>
	{
		static constexpr bool value = EmuMath::Helpers::vector_cast_is_valid
		<
			volatile EmuMath::NewVector<FromSize_, FromT_>&,
			ToSize_,
			ToT_,
			0
		>();
	};
	template<std::size_t FromSize_, typename FromT_, std::size_t ToSize_, typename ToT_>
	struct is_static_castable<const volatile EmuMath::NewVector<FromSize_, FromT_>&, EmuMath::NewVector<ToSize_, ToT_>>
	{
		static constexpr bool value = EmuMath::Helpers::vector_cast_is_valid
		<
			const volatile EmuMath::NewVector<FromSize_, FromT_>&,
			ToSize_,
			ToT_,
			0
		>();
	};

	// EmuMath Vector static_cast check specialisations: RVAL REF
	template<std::size_t FromSize_, typename FromT_, std::size_t ToSize_, typename ToT_>
	struct is_static_castable<EmuMath::NewVector<FromSize_, FromT_>&&, EmuMath::NewVector<ToSize_, ToT_>>
	{
		static constexpr bool value = EmuMath::Helpers::vector_cast_is_valid
		<
			EmuMath::NewVector<FromSize_, FromT_>&&,
			ToSize_,
			ToT_,
			0
		>();
	};
	template<std::size_t FromSize_, typename FromT_, std::size_t ToSize_, typename ToT_>
	struct is_static_castable<const EmuMath::NewVector<FromSize_, FromT_>&&, EmuMath::NewVector<ToSize_, ToT_>>
	{
		static constexpr bool value = EmuMath::Helpers::vector_cast_is_valid
		<
			const EmuMath::NewVector<FromSize_, FromT_>&&,
			ToSize_,
			ToT_,
			0
		>();
	};
	template<std::size_t FromSize_, typename FromT_, std::size_t ToSize_, typename ToT_>
	struct is_static_castable<volatile EmuMath::NewVector<FromSize_, FromT_>&&, EmuMath::NewVector<ToSize_, ToT_>>
	{
		static constexpr bool value = EmuMath::Helpers::vector_cast_is_valid
		<
			volatile EmuMath::NewVector<FromSize_, FromT_>&&,
			ToSize_,
			ToT_,
			0
		>();
	};
	template<std::size_t FromSize_, typename FromT_, std::size_t ToSize_, typename ToT_>
	struct is_static_castable<const volatile EmuMath::NewVector<FromSize_, FromT_>&&, EmuMath::NewVector<ToSize_, ToT_>>
	{
		static constexpr bool value = EmuMath::Helpers::vector_cast_is_valid
		<
			const volatile EmuMath::NewVector<FromSize_, FromT_>&&,
			ToSize_,
			ToT_,
			0
		>();
	};
#pragma endregion
}

#endif
