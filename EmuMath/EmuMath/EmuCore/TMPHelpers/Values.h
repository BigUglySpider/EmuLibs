#ifndef EMU_CORE_TMP_HELPERS_VALUES_H_INC_
#define EMU_CORE_TMP_HELPERS_VALUES_H_INC_ 1

namespace EmuCore::TMPHelpers
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
	static constexpr T_ get_conditional_ref(T_& ref_if_true, T_& ref_if_false)
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
	static constexpr T_ get_conditional_const_ref(const T_& ref_if_true, const T_& ref_if_false)
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
}

#endif
