#ifndef EMU_CORE_COMPARISON_ENUM_H_INC_
#define EMU_CORE_COMPARISON_ENUM_H_INC_ 1

#include "../TMPHelpers/SafeEnumFuncs.h"
#include <cstdint>

namespace EmuCore
{
	/// <summary>
	/// <para> Enum flag used to represent one of the basic comparisons (Equal, Not-Equal, Greater, Less, Greater-Equal, Less-Equal, and Near-Equal). </para>
	/// <para> Greater-Equal is guaranteed to use all bits used by Equal and all bits used by Greater combined. </para>
	/// <para> Less-Equal is guaranteed to use all bits used by Equal and all bits used by Less combined. </para>
	/// <para> Near-Equal is guaranteed to contain all bits used by Equal as part of its value. </para>
	/// </summary>
	enum class BasicCmp : std::uint8_t
	{
		EQUAL =			0x01,
		NOT_EQUAL =		0x02,
		GREATER =		0x04,
		LESS =			0x08,
		GREATER_EQUAL =	GREATER | EQUAL,
		LESS_EQUAL =	LESS | EQUAL,
		NEAR_EQUAL =    0x10 | EQUAL
	};
}

[[nodiscard]] constexpr inline EmuCore::BasicCmp operator&(EmuCore::BasicCmp lhs_, EmuCore::BasicCmp rhs_)
{
	return EmuCore::TMP::safe_enum_and<EmuCore::BasicCmp>(lhs_, rhs_);
}

[[nodiscard]] constexpr inline EmuCore::BasicCmp operator|(EmuCore::BasicCmp lhs_, EmuCore::BasicCmp rhs_)
{
	return EmuCore::TMP::safe_enum_or<EmuCore::BasicCmp>(lhs_, rhs_);
}

[[nodiscard]] constexpr inline EmuCore::BasicCmp operator^(EmuCore::BasicCmp lhs_, EmuCore::BasicCmp rhs_)
{
	return EmuCore::TMP::safe_enum_xor<EmuCore::BasicCmp>(lhs_, rhs_);
}

[[nodiscard]] constexpr inline EmuCore::BasicCmp operator~(EmuCore::BasicCmp to_not_)
{
	return EmuCore::TMP::safe_enum_not<EmuCore::BasicCmp>(to_not_);
}

constexpr inline EmuCore::BasicCmp& operator&=(EmuCore::BasicCmp& lhs_, EmuCore::BasicCmp rhs_)
{
	return EmuCore::TMP::safe_enum_and_equals<EmuCore::BasicCmp>(lhs_, rhs_);
}

constexpr inline EmuCore::BasicCmp& operator|=(EmuCore::BasicCmp& lhs_, EmuCore::BasicCmp rhs_)
{
	return EmuCore::TMP::safe_enum_or_equals<EmuCore::BasicCmp>(lhs_, rhs_);
}

constexpr inline EmuCore::BasicCmp& operator^=(EmuCore::BasicCmp& lhs_, EmuCore::BasicCmp rhs_)
{
	return EmuCore::TMP::safe_enum_xor_equals<EmuCore::BasicCmp>(lhs_, rhs_);
}

#endif
