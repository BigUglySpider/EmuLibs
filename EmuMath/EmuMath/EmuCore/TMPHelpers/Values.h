#ifndef EMU_CORE_TMP_HELPERS_VALUES_H_INC_
#define EMU_CORE_TMP_HELPERS_VALUES_H_INC_ 1

#include <array>
#include <limits>
#include <string>
#include "OperatorChecks.h"

namespace EmuCore::TMP
{
	/// <summary> 
	/// <para> Helper to avoid requiring a different branch while still forcing a condition to be checked at compile time to select a value. </para>
	/// <para>
	///		If the returned type should be a reference, it is recommended to use get_conditional_ref or get_conditional_const_ref, 
	///		instead of explicitly typing this function's T_ argument.
	/// </para>
	/// </summary>
	/// <typeparam name="T_">Type to return a conditional value for.</typeparam>
	/// <param name="val_if_true">Value that will be returned if Condition_ evaluates to true.</param>
	/// <param name="val_if_false">Value that will be returned if Condition_ evaluates to false.</param>
	/// <returns>val_if_true if Condition_ evaluates to true; val_if_false if Condition_ evaluates to false.</returns>
	template<bool Condition_, typename T_>
	static constexpr T_ get_conditional_value(T_ val_if_true, T_ val_if_false)
	{
		if constexpr (Condition_)
		{
			return val_if_true;
		}
		else
		{
			return val_if_false;
		}
	}
	/// <summary>
	/// <para> Helper to avoid requiring a different branch while still forcing a condition to be checked at compile time to select a reference. </para>
	/// <para>
	///		If the returned type should be constant, it is recommended to use get_conditional_const_ref, 
	///		instead of explicitly typing this function's T_ argument.
	/// </para>
	/// </summary>
	/// <typeparam name="T_">Type to return a conditional reference for.</typeparam>
	/// <param name="ref_if_true">Reference that will be returned if Condition_ evaluates to true.</param>
	/// <param name="ref_if_false">Reference that will be returned if Condition_ evaluates to false.</param>
	/// <returns>ref_if_true if Condition_ evaluates to true; ref_if_false if Condition_ evaluates to false.</returns>
	template<bool Condition_, typename T_>
	static constexpr T_& get_conditional_ref(T_& ref_if_true, T_& ref_if_false)
	{
		return get_conditional_value<Condition_, T_&>(ref_if_false, ref_if_false);
	}
	/// <summary>
	/// <para> Helper to avoid requiring a different branch while still forcing a condition to be checked at compile time to select a constant reference. </para>
	/// </summary>
	/// <typeparam name="T_">Type to return a conditional constant reference for.</typeparam>
	/// <param name="ref_if_true">Reference that will be returned if Condition_ evaluates to true.</param>
	/// <param name="ref_if_false">Reference that will be returned if Condition_ evaluates to false.</param>
	/// <returns>ref_if_true if Condition_ evaluates to true; ref_if_false if Condition_ evaluates to false.</returns>
	template<bool Condition_, typename T_>
	static constexpr const T_& get_conditional_const_ref(const T_& ref_if_true, const T_& ref_if_false)
	{
		return get_conditional_value<Condition_, const T_&>(ref_if_false, ref_if_false);
	}

	/// <summary>
	/// <para> Struct for ensuring all of get_conditional_value is executed at compile time. This may be useful to guarantee the avoidance of unneeded copies. </para>
	/// </summary>
	/// <typeparam name="T_">Type to provide a conditional constant for.</typeparam>
	template<bool Condition_, typename T_, T_ val_if_true, T_ val_if_false>
	struct conditional_value
	{
		constexpr conditional_value()
		{
		}
		static constexpr T_ value = get_conditional_value<Condition_, T_>(val_if_true, val_if_false);
		constexpr inline operator T_() const
		{
			return value;
		}
	};
	/// <summary> Shorthand for accessing the value of the conditional_value struct. </summary>
	/// <typeparam name="T_">Type to provide a conditional constant for.</typeparam>
	template<bool Condition_, typename T_, T_ val_if_true, T_ val_if_false>
	static constexpr T_ conditional_value_v = conditional_value<Condition_, T_, val_if_true, val_if_false>::value;

	/// <summary>
	/// <para> Function used to return a false bool based on a provided type. This is to allow static_assert(false) statements without compilation failure. </para>
	/// <para> Specialisations of this function to return true are ill-formed, and ultimately make a program's Emu library static_assertion diagnoses ill-formed. </para>
	/// </summary>
	/// <param name="dummy_">Dummy argument to use if a typename is not especially easily available. Note that this should be template-based.</param>
	/// <returns>False.</returns>
	template<typename...T_, typename = std::enable_if_t<(sizeof...(T_) != 0)>>
	[[nodiscard]] constexpr inline bool get_false(T_&&...dummy_)
	{
		return false;
	}
	/// <summary>
	/// <para> Function used to return a false bool based on a provided type. This is to allow static_assert(false) statements without compilation failure. </para>
	/// <para> Specialisations of this function to return true are ill-formed, and ultimately make a program's Emu library static_assertion diagnoses ill-formed. </para>
	/// </summary>
	/// <returns>False.</returns>
	template<typename...T_>
	[[nodiscard]] constexpr inline bool get_false()
	{
		return false;
	}
	/// <summary>
	/// <para> Function used to return a false bool based on a provided type. This is to allow static_assert(false) statements without compilation failure. </para>
	/// <para> Specialisations of this function to return true are ill-formed, and ultimately make a program's Emu library static_assertion diagnoses ill-formed. </para>
	/// </summary>
	/// <returns>False.</returns>
	template<typename T_, T_ Dummy_>
	[[nodiscard]] constexpr inline bool get_false()
	{
		return false;
	}
	/// <summary>
	/// <para> Function used to return a false bool based on a provided type. This is to allow static_assert(false) statements without compilation failure. </para>
	/// <para> Specialisations of this function to return true are ill-formed, and ultimately make a program's Emu library static_assertion diagnoses ill-formed. </para>
	/// </summary>
	/// <returns>False.</returns>
	template<auto Dummy_>
	[[nodiscard]] constexpr inline bool get_false()
	{
		return false;
	}

	/// <summary> 
	/// <para> Struct for retrieving the lowest value that may be stored in a type T_. </para>
	/// <para> Defaults to shorhand for std::numeric_limits::lowest() for T_, but may be specialised for types that do not fit having a std::numeric_limits specialisation. </para>
	/// </summary>
	template<class T_>
	struct lowest_value
	{
		[[nodiscard]] static constexpr inline T_ get()
		{
			return std::numeric_limits<T_>::lowest();
		}
	};

	/// <summary> 
	/// <para> Struct for retrieving the highest value that may be stored in a type T_. </para>
	/// <para> Defaults to shorhand for std::numeric_limits::max() for T_, but may be specialised for types that do not fit having a std::numeric_limits specialisation. </para>
	/// </summary>
	template<class T_>
	struct highest_value
	{
		[[nodiscard]] static constexpr inline T_ get()
		{
			return std::numeric_limits<T_>::max();
		}
	};

	/// <summary>
	/// <para> Function which may be used to form a constant of type T_ using the provided Constant_ argument. </para>
	/// <para> 
	///		If Constant_ is an arithmetic type, and T_ cannot be formed from it, 
	///		T_ will attempt to be formed from a static_cast of Constant_ to the provided AltConstantType_ (with ref/cv qualifiers).
	/// </para>
	/// <para>
	///		AltConstantType_: Optional conversion type for casting when Constant_ is an arithmetic type that may not be used with T_. 
	///		Defaults to a floating-point conversion if Constant_ is integral, or an integral conversion otherwise.
	/// </para>
	/// </summary>
	/// <returns>
	///		T_ constructed or static_cast to from the provided Constant_,
	///		or from a static_cast of Constant_ to the (unqualified) AltConstantType_ if Constant_ is an arithmetic type that cannot be used.
	/// </returns>
	template
	<
		typename T_,
		auto Constant_,
		typename AltConstantType_ = std::conditional_t<std::is_integral_v<EmuCore::TMP::remove_ref_cv_t<decltype(Constant_)>>, double, std::int64_t>
	>
	[[nodiscard]] constexpr inline T_ make_constant()
	{
		using constant_type = decltype(Constant_);
		using constant_uq = EmuCore::TMP::remove_ref_cv_t<constant_type>;
		if constexpr (std::is_arithmetic_v<constant_uq>)
		{
			// Arithmetic should always be true as of writing, but this is provided in case non-arithmetic non-type arguments are standardised
			if constexpr (std::is_constructible_v<T_, constant_type>)
			{
				return T_(Constant_);
			}
			else if constexpr (EmuCore::TMP::is_static_castable_v<constant_type, T_>)
			{
				return static_cast<T_>(Constant_);
			}
			else
			{
				using alt_constant_type_uq = EmuCore::TMP::remove_ref_cv_t<AltConstantType_>;
				if constexpr (EmuCore::TMP::is_static_castable_v<constant_type, alt_constant_type_uq>)
				{
					if constexpr (std::is_constructible_v<T_, alt_constant_type_uq>)
					{
						return T_(static_cast<alt_constant_type_uq>(Constant_));
					}
					else if constexpr (EmuCore::TMP::is_static_castable_v<alt_constant_type_uq, T_>)
					{
						return static_cast<T_>
						(
							static_cast<alt_constant_type_uq>(Constant_)
						);
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<T_>(),
							"Attempted to form a constant of type T_ with an arithmetic constant, but the provided type T_ cannot be constructed with the passed Constant_ or its static_cast to the provided (unqualified) AltConstantType_."
						);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<T_>(),
						"Attempted to form a constant of type T_ with an arithmetic constant, but the provided type T_ cannot be constructed with the passed Constant_ and the Constant_ cannot be static_cast to its provided (unqualified) AltConstantType_."
					);
				}
			}
		}
		else
		{
			if constexpr (std::is_constructible_v<T_, constant_type>)
			{
				return T_(Constant_);
			}
			else if constexpr(EmuCore::TMP::is_static_castable_v<constant_type, T_>)
			{
				return static_cast<T_>(Constant_);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<T_>(),
					"Attempted to form a constant of type T_, but the provided type T_ cannot be constructed or static-cast to from the passed non-arithmetic Constant_."
				);
			}
		}
	}

	template
	<
		typename T_,
		auto Constant_,
		typename AltConstantType_ = std::conditional_t<std::is_integral_v<EmuCore::TMP::remove_ref_cv_t<decltype(Constant_)>>, double, std::int64_t>
	>
	[[nodiscard]] constexpr inline bool is_valid_make_constant_call()
	{
		using constant_type = decltype(Constant_);
		using constant_uq = EmuCore::TMP::remove_ref_cv_t<constant_type>;
		constexpr bool constant_is_arithmetic_ = std::is_arithmetic_v<constant_uq>;
		if constexpr (constant_is_arithmetic_)
		{
			if constexpr (std::is_constructible_v<T_, constant_type> || EmuCore::TMP::is_static_castable_v<constant_type, T_>)
			{
				return true;
			}
			else
			{
				using alt_constant_type_uq = EmuCore::TMP::remove_ref_cv_t<AltConstantType_>;
				return
				(
					EmuCore::TMP::is_static_castable_v<constant_type, alt_constant_type_uq> &&
					(std::is_constructible_v<T_, alt_constant_type_uq> || EmuCore::TMP::is_static_castable_v<alt_constant_type_uq, T_>)
				);
			}
		}
		else
		{
			return std::is_constructible_v<T_, constant_type> || EmuCore::TMP::is_static_castable_v<constant_type, T_>;
		}
	}

	/// <summary>
	/// <para> Helper type to safely form a constant via make_constant if possible, and not call it if not valid. </para>
	/// <para> The contained bool is_valid can be used to determine success (true if successful, otherwise false). </para>
	/// <para>
	///		The get() static function may be called to retrieve the result constant. 
	///		If is_valid is true, this will be the result of EmuCore::TMP::make_constant with the same arguments. 
	///		Otherwise, it will be the result of std::declval with the provided T_.
	/// </para>
	/// </summary>
	template
	<
		typename T_,
		auto Constant_,
		typename AltConstantType_ = std::conditional_t<std::is_integral_v<EmuCore::TMP::remove_ref_cv_t<decltype(Constant_)>>, double, std::int64_t>
	>
	struct try_make_constant
	{
		static constexpr bool is_valid = EmuCore::TMP::is_valid_make_constant_call<T_, Constant_, AltConstantType_>();
		static constexpr std::conditional_t<is_valid, T_, decltype(std::declval<T_>())> get()
		{
			if constexpr (is_valid)
			{
				return EmuCore::TMP::make_constant<T_, Constant_, AltConstantType_>();
			}
			else
			{
				return std::declval<T_>();
			}
		}
	};

	template<class Out_, class In_>
	[[nodiscard]] constexpr inline Out_ construct_or_cast(In_&& in_)
	{
		using forward_result_type = decltype(std::forward<In_>(in_));
		if constexpr (std::is_constructible_v<Out_, forward_result_type>)
		{
			return Out_(std::forward<In_>(in_));
		}
		else if constexpr (EmuCore::TMP::is_static_castable_v<forward_result_type, Out_>)
		{
			return static_cast<Out_>(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<In_>(),
				"Attempted to construct-or-cast an Out_ value from a provided In_ value via EmuCore::TMP::construct_or_cast, but the provided In_ type could not be used to construct or static_cast to the desired output type after forwarding."
			);
		}
	}

	template<class Out_, class In_>
	[[nodiscard]] constexpr inline bool valid_construct_or_cast()
	{
		using forward_result_type = decltype(std::forward<In_>(std::declval<In_>()));
		return 
		(
			std::is_constructible_v<Out_, forward_result_type> ||
			EmuCore::TMP::is_static_castable_v<forward_result_type, Out_>
		);
	}

	/// <summary>
	/// <para> Assigns the provided out_ reference via forwarding in_, or creates a CastType_ from in_ if direct assignment is decided against and assigns out_ via that. </para>
	/// <para> 
	///		Direct Assignment: Occurs when out_ is assignable via forwarding in_, 
	///		and their unqualified types are either the same, or at least 1 of them is not an arithmetic type. 
	///		This is to force an explicit cast when using differing arithmetic types, so no implicit conversions are performed.
	/// </para>
	/// <para>
	///		Cast Assignment: Occurs when Direct Assignment is NOT allowed to occur, and out_ is assignable via a newly created CastType_.
	/// </para>
	/// </summary>
	/// <param name="out_">: Reference to assign to.</param>
	/// <param name="in_">: Value to assign out_ via if Direct Assignment may occur, or used to create a CastType_ if Cast Assignment is performed.</param>
	template<class CastType_, class In_, class Out_>
	constexpr inline void assign_direct_or_cast(Out_& out_, In_&& in_)
	{
		using in_uq = EmuCore::TMP::remove_ref_cv_t<In_>;
		using out_uq = EmuCore::TMP::remove_ref_cv_t<Out_>;
		using in_forward_result = decltype(std::forward<In_>(in_));
		constexpr bool both_arithmetic_ = std::is_arithmetic_v<in_uq> && std::is_arithmetic_v<out_uq>;
		constexpr bool same_type_ = std::is_same_v<in_uq, out_uq>;
		constexpr bool allow_direct_assign_if_possible_ = (!both_arithmetic_ || same_type_);

		if constexpr (std::is_assignable_v<Out_&, in_forward_result> && allow_direct_assign_if_possible_)
		{
			out_ = std::forward<In_>(in_);
		}
		else if constexpr(std::is_assignable_v<Out_&, CastType_>)
		{
			if constexpr (valid_construct_or_cast<CastType_, In_>())
			{
				out_ = construct_or_cast<CastType_, In_>(std::forward<In_>(in_));
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<In_>(),
					"Attempted to assign either directly or via a cast depending on constraints based on the passed types, but the provided In_ type could not be used to directly assign to the output value, and it could not be used to construct or static_cast to the provided CastType_."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<In_, CastType_>(),
				"Attempted to assign either directly or via a cast depending on constraints based on the passed types, but the provided In_ type could not be used to directly assign to the output value, and the CastType_ also could not be used to assign to the output value."
			);
		}
	}

	template<class CastType_, class In_, class Out_>
	[[nodiscard]] constexpr inline bool valid_assign_direct_or_cast()
	{
		using in_uq = EmuCore::TMP::remove_ref_cv_t<In_>;
		using out_uq = EmuCore::TMP::remove_ref_cv_t<Out_>;
		using in_forward_result = decltype(std::forward<In_>(std::declval<In_>()));
		constexpr bool both_arithmetic_ = std::is_arithmetic_v<in_uq> && std::is_arithmetic_v<out_uq>;
		constexpr bool same_type_ = std::is_same_v<in_uq, out_uq>;
		constexpr bool allow_direct_assign_if_possible_ = (!both_arithmetic_ || same_type_);

		if constexpr (std::is_assignable_v<Out_&, in_forward_result> && allow_direct_assign_if_possible_)
		{
			return true;
		}
		else if constexpr(std::is_assignable_v<Out_&, CastType_>)
		{
			return valid_construct_or_cast<CastType_, In_>();
		}
		else
		{
			return false;
		}
	}
}

#endif
