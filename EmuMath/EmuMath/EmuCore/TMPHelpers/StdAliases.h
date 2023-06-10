#ifndef EMU_CORE_STD_ALIASES_H_INC_
#define EMU_CORE_STD_ALIASES_H_INC_ 1

#include <bitset>
#include <climits>

namespace EmuCore
{
	/// <summary>
	/// <para> Type for determining a std::bitset from a provided type. </para>
	/// <para>
	///		By default, type will be a std::bitset for a number of bits equal to the number of bytes in type T_ multiplied by CHAR_BIT. 
	///		This is always equal to the number of bits with type T_ including alignment padding added to it by the compiler.
	/// </para>
	/// </summary>
	template<typename T_>
	struct bitset_for_type
	{
		using type = std::bitset<sizeof(T_) * CHAR_BIT>;
	};

	template<typename T_>
	using bitset_for_type_t = typename bitset_for_type<T_>::type;
}

#endif
