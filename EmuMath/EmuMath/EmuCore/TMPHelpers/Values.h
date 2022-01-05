#ifndef EMU_CORE_TMP_HELPERS_VALUES_H_INC_
#define EMU_CORE_TMP_HELPERS_VALUES_H_INC_ 1

#include <array>
#include <limits>
#include <string>

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
	/// <para> Type for converting a provided Val_ to a string in the provided Base_, represented using the provided Char_ type. </para>
	/// <para> Conversion may be performed at compile time. To guarantee this, assign a newly constructed item of this type to a constexpr value. </para>
	/// <para>
	///		Upper_ is only used by bases higher than 10, and determines if alphabetical characters appear in upper or lower case. 
	///		For example, when converting 30 to a base16 string, output will be 1E if Upper_ is true, or 1e if Upper_ is false.
	/// </para>
	/// </summary>
	template<auto Val_, std::size_t Base_ = 10, typename Char_ = char, bool Upper_ = true>
	struct constexpr_to_str
	{
	private:
		static_assert
		(
			Base_ >= 2 && Base_ <= 36,
			"Invalid Base_ argument provided to EmuCore::TMP::constexpr_to_str. Only bases in the inclusive range 2:36 may be used."
		);

		using _val_type = decltype(Val_);

		// As digit list uses purely numeric and alphabetic ASCII chars, we just store as such since UTF-encoding uses the same values in this range
		[[nodiscard]] static constexpr inline const char* _make_digit_list()
		{
			if constexpr (Upper_)
			{
				return "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			}
			else
			{
				return "0123456789abcdefghijklmnopqrstuvwxyz";
			}
		}
		static constexpr const char* const _digit_list = _make_digit_list();

		// Type to easily construct the correct character literal for CharType_.
		template<typename CharType_>
		[[nodiscard]] constexpr inline CharType_ _make_minus()
		{
			return CharType_('-');
		}
		template<>
		[[nodiscard]] constexpr inline char _make_minus<char>()
		{
			return '-';
		}
		template<>
		[[nodiscard]] constexpr inline unsigned char _make_minus<unsigned char>()
		{
			return '-';
		}
		template<>
		[[nodiscard]] constexpr inline char16_t _make_minus<char16_t>()
		{
			return u'-';
		}
		template<>
		[[nodiscard]] constexpr inline char32_t _make_minus<char32_t>()
		{
			return U'-';
		}
		template<>
		[[nodiscard]] constexpr inline wchar_t _make_minus<wchar_t>()
		{
			return L'-';
		}

		constexpr inline void _invalid_val_type_assertion()
		{
			static_assert
			(
				EmuCore::TMP::get_false<_val_type>(),
				"Attempted to perform a constexpr_to_str operation, but the provided Val_ type is not supported for the operation. Only integral types are currently supported."
			);
		}

		[[nodiscard]] static constexpr inline _val_type _zero_val()
		{
			if constexpr (std::is_constructible_v<_val_type, decltype(0)>)
			{
				return _val_type(0);
			}
			else if constexpr (std::is_constructible_v<_val_type, decltype(0.0f)>)
			{
				return _val_type(0.0f);
			}
			else
			{
				return _val_type();
			}
		}

		[[nodiscard]] static constexpr inline _val_type _abs_val()
		{
			if constexpr (Val_ < _val_type(0))
			{
				return -Val_;
			}
			else
			{
				return Val_;
			}
		}

		[[nodiscard]] static constexpr inline std::size_t _buffer_size()
		{
			// 2 guaranteed chars if Val_ < 0 (-, and terminator), otherwise just 1 guaranteed char (terminator)
			constexpr std::size_t additional_char_count_ = (Val_ < 0) ? 2 : 1;
			std::size_t char_count_ = additional_char_count_;

			if constexpr (std::is_integral_v<_val_type>)
			{
				constexpr _val_type zero_ = _zero_val();
			
				if constexpr (Val_ != 0)
				{
					for (_val_type val_ = _abs_val(); val_ != zero_; val_ /= Base_)
					{
						++char_count_;
					}
				}
				else
				{
					++char_count_;
				}
			}
			else
			{
				_invalid_val_type_assertion();
			}

			return char_count_;
		}

		constexpr inline void _set()
		{
			// Build the string from end-begin, starting with the null-terminator
			std::size_t index_ = _buffer_size() - 1;
			_buffer[index_] = Char_(0);

			if constexpr (std::is_integral_v<_val_type>)
			{
				constexpr _val_type zero_ = _zero_val();
				
				if constexpr (Val_ != zero_)
				{
					for (_val_type val_ = _abs_val(); val_ != zero_; val_ /= Base_)
					{
						_buffer[--index_] = Char_(_digit_list[std::size_t(val_) % Base_]);
					}
					if constexpr (Val_ < 0)
					{
						_buffer[--index_] = _make_minus<Char_>();
					}
				}
				else
				{
					_buffer[--index_] = _digit_list[0];
				}
			}
			else
			{
				_invalid_val_type_assertion();
			}
		}

		std::array<Char_, _buffer_size()> _buffer;

	public:
		constexpr inline constexpr_to_str() : _buffer({ 0 })
		{
			_set();
		}

		constexpr inline operator const Char_* () const
		{
			return get();
		}

		constexpr inline operator std::basic_string<Char_> () const
		{
			return get_basic_str();
		}

		constexpr inline const Char_* get() const
		{
			return _buffer.data();
		}

		constexpr inline std::basic_string<Char_> get_basic_str() const
		{
			constexpr std::size_t _buffer_size_without_terminator = _buffer_size() - 1;
			return std::basic_string<Char_>(get(), _buffer_size_without_terminator);
		}
	};
}

#endif
