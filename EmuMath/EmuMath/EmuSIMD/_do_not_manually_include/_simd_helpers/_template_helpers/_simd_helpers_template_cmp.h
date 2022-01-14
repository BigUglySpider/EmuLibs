#ifndef EMU_SIMD_HELPERS_TEMPLATE_CMP_H_INC_
#define EMU_SIMD_HELPERS_TEMPLATE_CMP_H_INC_ 1

#include "_underlying_template_helpers/_common_underlying_simd_template_helper_includes.h"
#include "_underlying_template_helpers/_simd_helpers_underlying_cmp.h"
#include "_underlying_template_helpers/_simd_helpers_underlying_movemasks.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD
{
	template<class Register_>
	[[nodiscard]] inline auto movemask(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_movemask(register_);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::movemask, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline Register_ cmpeq(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_cmp_eq<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmpeq, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline Register_ cmpneq(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_cmp_neq<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmpneq, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline Register_ cmplt(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_cmp_lt<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmplt, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline Register_ cmpgt(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_cmp_gt<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmpgt, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline Register_ cmple(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_cmp_le<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmple, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline Register_ cmpge(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_cmp_ge<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmpge, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<int CmpFlags_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline Register_ cmp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_cmp<CmpFlags_, PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_any_eq(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_movemask
			(
				_underlying_simd_helpers::_cmp_eq<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_)
			) != 0;
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_any_eq, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_any_neq(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_movemask
			(
				_underlying_simd_helpers::_cmp_neq<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_)
			) != 0;
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_any_neq, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_any_lt(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_movemask
			(
				_underlying_simd_helpers::_cmp_lt<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_)
			) != 0;
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_any_lt, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_any_gt(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_movemask
			(
				_underlying_simd_helpers::_cmp_gt<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_)
			) != 0;
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_any_gt, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_any_le(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_movemask
			(
				_underlying_simd_helpers::_cmp_le<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_)
			) != 0;
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_any_le, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_any_ge(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_movemask
			(
				_underlying_simd_helpers::_cmp_ge<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_)
			) != 0;
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_any_ge, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<int CmpFlags_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_any(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_movemask
			(
				_underlying_simd_helpers::_cmp<CmpFlags_, PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_)
			) != 0;
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_any, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<bool SignedIfInt_, bool...IndexMustBeTrue_, class Register_>
	[[nodiscard]] inline bool cmp_all_eq(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using movemask_generator = _underlying_simd_helpers::_make_movemask<register_type_uq, IndexMustBeTrue_...>;
			if constexpr (_underlying_simd_helpers::_is_valid_make_movemask_instance<movemask_generator>::value)
			{
				constexpr std::size_t num_index_args_ = sizeof...(IndexMustBeTrue_);
				// Int width is assumed as 8 for a guaranteed full movemask comparison if arg count <= 1
				// --- Otherwise, we get The number of bits in the register divided by the number of arguments 
				// ------ (e.g. 2 args for 128-bit register means we've got arguments for 2 64-bit elements)
				constexpr std::size_t int_width_ = num_index_args_ > 1 ? EmuSIMD::TMP::simd_register_width_v<register_type_uq> / num_index_args_ : 8;

				return _underlying_simd_helpers::_movemask
				(
					_underlying_simd_helpers::_cmp_eq<int_width_, SignedIfInt_>(lhs_, rhs_)
				) == movemask_generator::value;
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_all_eq, but the passed IndexMustBeTrue_ arguments could not be used with the provided SIMD register to form a valid movemask. The number of boolean arguments must be equal to 1 or the number of elements contained within the register. If the register is integral, the number of arguments can be 1, register_width/64, register_width/32, register_width/16, or register_width/8, where the bit-width per element is determined as the denominator in these fractions.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_all_eq, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}
	template<bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_all_eq(Register_ lhs_, Register_ rhs_)
	{
		return cmp_all_eq<SignedIfInt_, true>(lhs_, rhs_);
	}

	template<bool SignedIfInt_, bool...ResultAtIndex_, class Register_>
	[[nodiscard]] inline bool cmp_all_neq(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using movemask_generator = _underlying_simd_helpers::_make_movemask<register_type_uq, ResultAtIndex_...>;
			if constexpr (_underlying_simd_helpers::_is_valid_make_movemask_instance<movemask_generator>::value)
			{
				constexpr std::size_t num_index_args_ = sizeof...(ResultAtIndex_);
				constexpr std::size_t int_width_ = num_index_args_ > 1 ? EmuSIMD::TMP::simd_register_width_v<register_type_uq> / num_index_args_ : 8;

				return _underlying_simd_helpers::_movemask
				(
					_underlying_simd_helpers::_cmp_neq<int_width_, SignedIfInt_>(lhs_, rhs_)
				) == movemask_generator::value;
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_all_neq, but the passed IndexMustBeTrue_ arguments could not be used with the provided SIMD register to form a valid movemask. The number of boolean arguments must be equal to 1 or the number of elements contained within the register. If the register is integral, the number of arguments can be 1, register_width/64, register_width/32, register_width/16, or register_width/8, where the bit-width per element is determined as the denominator in these fractions.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_all_neq, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}
	template<bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_all_neq(Register_ lhs_, Register_ rhs_)
	{
		return cmp_all_neq<SignedIfInt_, true>(lhs_, rhs_);
	}

	template<bool SignedIfInt_, bool...ResultAtIndex_, class Register_>
	[[nodiscard]] inline bool cmp_all_lt(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using movemask_generator = _underlying_simd_helpers::_make_movemask<register_type_uq, ResultAtIndex_...>;
			if constexpr (_underlying_simd_helpers::_is_valid_make_movemask_instance<movemask_generator>::value)
			{
				constexpr std::size_t num_index_args_ = sizeof...(ResultAtIndex_);
				constexpr std::size_t int_width_ = num_index_args_ > 1 ? EmuSIMD::TMP::simd_register_width_v<register_type_uq> / num_index_args_ : 8;

				return _underlying_simd_helpers::_movemask
				(
					_underlying_simd_helpers::_cmp_lt<int_width_, SignedIfInt_>(lhs_, rhs_)
				) == movemask_generator::value;
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_all_lt, but the passed IndexMustBeTrue_ arguments could not be used with the provided SIMD register to form a valid movemask. The number of boolean arguments must be equal to 1 or the number of elements contained within the register. If the register is integral, the number of arguments can be 1, register_width/64, register_width/32, register_width/16, or register_width/8, where the bit-width per element is determined as the denominator in these fractions.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_all_lt, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}
	template<bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_all_lt(Register_ lhs_, Register_ rhs_)
	{
		return cmp_all_lt<SignedIfInt_, true>(lhs_, rhs_);
	}

	template<bool SignedIfInt_, bool...ResultAtIndex_, class Register_>
	[[nodiscard]] inline bool cmp_all_gt(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using movemask_generator = _underlying_simd_helpers::_make_movemask<register_type_uq, ResultAtIndex_...>;
			if constexpr (_underlying_simd_helpers::_is_valid_make_movemask_instance<movemask_generator>::value)
			{
				constexpr std::size_t num_index_args_ = sizeof...(ResultAtIndex_);
				constexpr std::size_t int_width_ = num_index_args_ > 1 ? EmuSIMD::TMP::simd_register_width_v<register_type_uq> / num_index_args_ : 8;

				return _underlying_simd_helpers::_movemask
				(
					_underlying_simd_helpers::_cmp_gt<int_width_, SignedIfInt_>(lhs_, rhs_)
				) == movemask_generator::value;
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_all_gt, but the passed IndexMustBeTrue_ arguments could not be used with the provided SIMD register to form a valid movemask. The number of boolean arguments must be equal to 1 or the number of elements contained within the register. If the register is integral, the number of arguments can be 1, register_width/64, register_width/32, register_width/16, or register_width/8, where the bit-width per element is determined as the denominator in these fractions.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_all_gt, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}
	template<bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_all_gt(Register_ lhs_, Register_ rhs_)
	{
		return cmp_all_gt<SignedIfInt_, true>(lhs_, rhs_);
	}

	template<bool SignedIfInt_, bool...ResultAtIndex_, class Register_>
	[[nodiscard]] inline bool cmp_all_le(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using movemask_generator = _underlying_simd_helpers::_make_movemask<register_type_uq, ResultAtIndex_...>;
			if constexpr (_underlying_simd_helpers::_is_valid_make_movemask_instance<movemask_generator>::value)
			{
				constexpr std::size_t num_index_args_ = sizeof...(ResultAtIndex_);
				constexpr std::size_t int_width_ = num_index_args_ > 1 ? EmuSIMD::TMP::simd_register_width_v<register_type_uq> / num_index_args_ : 8;

				return _underlying_simd_helpers::_movemask
				(
					_underlying_simd_helpers::_cmp_le<int_width_, SignedIfInt_>(lhs_, rhs_)
				) == movemask_generator::value;
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_all_le, but the passed IndexMustBeTrue_ arguments could not be used with the provided SIMD register to form a valid movemask. The number of boolean arguments must be equal to 1 or the number of elements contained within the register. If the register is integral, the number of arguments can be 1, register_width/64, register_width/32, register_width/16, or register_width/8, where the bit-width per element is determined as the denominator in these fractions.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_all_le, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}
	template<bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_all_le(Register_ lhs_, Register_ rhs_)
	{
		return cmp_all_le<SignedIfInt_, true>(lhs_, rhs_);
	}

	template<bool SignedIfInt_, bool...ResultAtIndex_, class Register_>
	[[nodiscard]] inline bool cmp_all_ge(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using movemask_generator = _underlying_simd_helpers::_make_movemask<register_type_uq, ResultAtIndex_...>;
			if constexpr (_underlying_simd_helpers::_is_valid_make_movemask_instance<movemask_generator>::value)
			{
				constexpr std::size_t num_index_args_ = sizeof...(ResultAtIndex_);
				constexpr std::size_t int_width_ = num_index_args_ > 1 ? EmuSIMD::TMP::simd_register_width_v<register_type_uq> / num_index_args_ : 8;

				return _underlying_simd_helpers::_movemask
				(
					_underlying_simd_helpers::_cmp_ge<int_width_, SignedIfInt_>(lhs_, rhs_)
				) == movemask_generator::value;
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_all_ge, but the passed IndexMustBeTrue_ arguments could not be used with the provided SIMD register to form a valid movemask. The number of boolean arguments must be equal to 1 or the number of elements contained within the register. If the register is integral, the number of arguments can be 1, register_width/64, register_width/32, register_width/16, or register_width/8, where the bit-width per element is determined as the denominator in these fractions.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_all_ge, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}
	template<bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_all_ge(Register_ lhs_, Register_ rhs_)
	{
		return cmp_all_ge<SignedIfInt_, true>(lhs_, rhs_);
	}

	template<int CmpFlags_, bool SignedIfInt_, bool...ResultAtIndex_, class Register_>
	[[nodiscard]] inline bool cmp_all(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using movemask_generator = _underlying_simd_helpers::_make_movemask<register_type_uq, ResultAtIndex_...>;
			if constexpr (_underlying_simd_helpers::_is_valid_make_movemask_instance<movemask_generator>::value)
			{
				constexpr std::size_t num_index_args_ = sizeof...(ResultAtIndex_);
				constexpr std::size_t int_width_ = num_index_args_ > 1 ? EmuSIMD::TMP::simd_register_width_v<register_type_uq> / num_index_args_ : 8;

				return _underlying_simd_helpers::_movemask
				(
					_underlying_simd_helpers::_cmp<CmpFlags_, int_width_, SignedIfInt_>(lhs_, rhs_)
				) == movemask_generator::value;
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_all, but the passed IndexMustBeTrue_ arguments could not be used with the provided SIMD register to form a valid movemask. The number of boolean arguments must be equal to 1 or the number of elements contained within the register. If the register is integral, the number of arguments can be 1, register_width/64, register_width/32, register_width/16, or register_width/8, where the bit-width per element is determined as the denominator in these fractions.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_all, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}
	template<int CmpFlags_, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_all(Register_ lhs_, Register_ rhs_)
	{
		return cmp_all<CmpFlags_, SignedIfInt_, true>(lhs_, rhs_);
	}
}

#endif
