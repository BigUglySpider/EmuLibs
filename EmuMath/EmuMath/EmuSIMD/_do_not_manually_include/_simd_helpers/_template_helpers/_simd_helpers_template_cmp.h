#ifndef EMU_SIMD_HELPERS_TEMPLATE_CMP_H_INC_
#define EMU_SIMD_HELPERS_TEMPLATE_CMP_H_INC_ 1

#include "_underlying_template_helpers/_all_underlying_templates.h"
#include "_simd_helpers_template_bitwise.h"
#include "_simd_helpers_template_index_masks.h"
#include "_simd_helpers_template_movemask.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"
#include "../../../../EmuCore/TMPHelpers/VariadicHelpers.h"

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

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline Register_ cmpnear(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_cmp_near_equal<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmpnear, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline Register_ cmpnear(Register_ lhs_, Register_ rhs_, Register_ epsilon_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_cmp_near_equal<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_, epsilon_);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmpnear, but the passed Register_ type is not recognised as a supported SIMD register.");
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
	[[nodiscard]] inline bool cmp_any_near(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_movemask
			(
				_underlying_simd_helpers::_cmp_near_equal<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_)
			) != 0;
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_any_near, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_any_near(Register_ lhs_, Register_ rhs_, Register_ epsilon)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_movemask
			(
				_underlying_simd_helpers::_cmp_near_equal<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_, epsilon)
			) != 0;
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_any_near, but the passed Register_ type is not recognised as a supported SIMD register.");
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
	[[nodiscard]] inline bool cmp_selected_eq(Register_ lhs_, Register_ rhs_)
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
				static_assert
				(
					EmuCore::TMP::get_false<Register_>(),
					"Attempted to perform EmuSIMD::cmp_selected_eq, but the passed IndexMustBeTrue_ arguments could not be used with the provided SIMD register to form a valid movemask. The number of boolean arguments must be equal to 1 or the number of elements contained within the register. If the register is integral, the number of arguments can be 1, register_width/64, register_width/32, register_width/16, or register_width/8, where the bit-width per element is determined as the denominator in these fractions."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Register_>(),
				"Attempted to perform EmuSIMD::cmp_selected_eq, but the passed Register_ type is not recognised as a supported SIMD register."
			);
		}
	}
	template<bool SignedIfInt_, bool...IndexMustBeTrue_, class Register_>
	[[nodiscard]] inline bool cmp_selected_eq(Register_ lhs_, Register_ rhs_, EmuCore::TMP::bool_sequence<IndexMustBeTrue_...> indices_must_be_true)
	{
		return cmp_selected_eq<SignedIfInt_, IndexMustBeTrue_...>(lhs_, rhs_);
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_all_eq(Register_ lhs_, Register_ rhs_)
	{
		constexpr std::size_t count = EmuSIMD::TMP::register_element_count_v<Register_, PerElementWidthIfInt_>;
		return cmp_selected_eq<SignedIfInt_>(lhs_, rhs_, EmuCore::TMP::make_true_bool_sequence<count>());
	}

	template<bool SignedIfInt_, bool...ResultAtIndex_, class Register_>
	[[nodiscard]] inline bool cmp_selected_neq(Register_ lhs_, Register_ rhs_)
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
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_selected_neq, but the passed IndexMustBeTrue_ arguments could not be used with the provided SIMD register to form a valid movemask. The number of boolean arguments must be equal to 1 or the number of elements contained within the register. If the register is integral, the number of arguments can be 1, register_width/64, register_width/32, register_width/16, or register_width/8, where the bit-width per element is determined as the denominator in these fractions.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_selected_neq, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}
	template<bool SignedIfInt_, bool...IndexMustBeTrue_, class Register_>
	[[nodiscard]] inline bool cmp_selected_neq(Register_ lhs_, Register_ rhs_, EmuCore::TMP::bool_sequence<IndexMustBeTrue_...> indices_must_be_true)
	{
		return cmp_selected_neq<SignedIfInt_, IndexMustBeTrue_...>(lhs_, rhs_);
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_all_neq(Register_ lhs_, Register_ rhs_)
	{
		constexpr std::size_t count = EmuSIMD::TMP::register_element_count_v<Register_, PerElementWidthIfInt_>;
		return cmp_selected_neq<SignedIfInt_>(lhs_, rhs_, EmuCore::TMP::make_true_bool_sequence<count>());
	}

	template<bool SignedIfInt_, bool...ResultAtIndex_, class Register_>
	[[nodiscard]] inline bool cmp_selected_lt(Register_ lhs_, Register_ rhs_)
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
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_selected_lt, but the passed IndexMustBeTrue_ arguments could not be used with the provided SIMD register to form a valid movemask. The number of boolean arguments must be equal to 1 or the number of elements contained within the register. If the register is integral, the number of arguments can be 1, register_width/64, register_width/32, register_width/16, or register_width/8, where the bit-width per element is determined as the denominator in these fractions.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_selected_lt, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}
	template<bool SignedIfInt_, bool...IndexMustBeTrue_, class Register_>
	[[nodiscard]] inline bool cmp_selected_lt(Register_ lhs_, Register_ rhs_, EmuCore::TMP::bool_sequence<IndexMustBeTrue_...> indices_must_be_true)
	{
		return cmp_selected_lt<SignedIfInt_, IndexMustBeTrue_...>(lhs_, rhs_);
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_all_lt(Register_ lhs_, Register_ rhs_)
	{
		constexpr std::size_t count = EmuSIMD::TMP::register_element_count_v<Register_, PerElementWidthIfInt_>;
		return cmp_selected_lt<SignedIfInt_>(lhs_, rhs_, EmuCore::TMP::make_true_bool_sequence<count>());
	}


	template<bool SignedIfInt_, bool...ResultAtIndex_, class Register_>
	[[nodiscard]] inline bool cmp_selected_gt(Register_ lhs_, Register_ rhs_)
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
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_selected_gt, but the passed IndexMustBeTrue_ arguments could not be used with the provided SIMD register to form a valid movemask. The number of boolean arguments must be equal to 1 or the number of elements contained within the register. If the register is integral, the number of arguments can be 1, register_width/64, register_width/32, register_width/16, or register_width/8, where the bit-width per element is determined as the denominator in these fractions.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_selected_gt, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}
	template<bool SignedIfInt_, bool...IndexMustBeTrue_, class Register_>
	[[nodiscard]] inline bool cmp_selected_gt(Register_ lhs_, Register_ rhs_, EmuCore::TMP::bool_sequence<IndexMustBeTrue_...> indices_must_be_true)
	{
		return cmp_selected_gt<SignedIfInt_, IndexMustBeTrue_...>(lhs_, rhs_);
	}
	
	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_all_gt(Register_ lhs_, Register_ rhs_)
	{
		constexpr std::size_t count = EmuSIMD::TMP::register_element_count_v<Register_, PerElementWidthIfInt_>;
		return cmp_selected_gt<SignedIfInt_>(lhs_, rhs_, EmuCore::TMP::make_true_bool_sequence<count>());
	}

	template<bool SignedIfInt_, bool...ResultAtIndex_, class Register_>
	[[nodiscard]] inline bool cmp_selected_le(Register_ lhs_, Register_ rhs_)
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
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_selected_le, but the passed IndexMustBeTrue_ arguments could not be used with the provided SIMD register to form a valid movemask. The number of boolean arguments must be equal to 1 or the number of elements contained within the register. If the register is integral, the number of arguments can be 1, register_width/64, register_width/32, register_width/16, or register_width/8, where the bit-width per element is determined as the denominator in these fractions.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_selected_le, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}
	template<bool SignedIfInt_, bool...IndexMustBeTrue_, class Register_>
	[[nodiscard]] inline bool cmp_selected_le(Register_ lhs_, Register_ rhs_, EmuCore::TMP::bool_sequence<IndexMustBeTrue_...> indices_must_be_true)
	{
		return cmp_selected_le<SignedIfInt_, IndexMustBeTrue_...>(lhs_, rhs_);
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_all_le(Register_ lhs_, Register_ rhs_)
	{
		constexpr std::size_t count = EmuSIMD::TMP::register_element_count_v<Register_, PerElementWidthIfInt_>;
		return cmp_selected_le<SignedIfInt_>(lhs_, rhs_, EmuCore::TMP::make_true_bool_sequence<count>());
	}

	template<bool SignedIfInt_, bool...ResultAtIndex_, class Register_>
	[[nodiscard]] inline bool cmp_selected_ge(Register_ lhs_, Register_ rhs_)
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
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_selected_ge, but the passed IndexMustBeTrue_ arguments could not be used with the provided SIMD register to form a valid movemask. The number of boolean arguments must be equal to 1 or the number of elements contained within the register. If the register is integral, the number of arguments can be 1, register_width/64, register_width/32, register_width/16, or register_width/8, where the bit-width per element is determined as the denominator in these fractions.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_selected_ge, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}
	template<bool SignedIfInt_, bool...IndexMustBeTrue_, class Register_>
	[[nodiscard]] inline bool cmp_selected_ge(Register_ lhs_, Register_ rhs_, EmuCore::TMP::bool_sequence<IndexMustBeTrue_...> indices_must_be_true)
	{
		return cmp_selected_eq<SignedIfInt_, IndexMustBeTrue_...>(lhs_, rhs_);
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_all_ge(Register_ lhs_, Register_ rhs_)
	{
		constexpr std::size_t count = EmuSIMD::TMP::register_element_count_v<Register_, PerElementWidthIfInt_>;
		return cmp_selected_ge<SignedIfInt_>(lhs_, rhs_, EmuCore::TMP::make_true_bool_sequence<count>());
	}

	template<bool SignedIfInt_, bool...ResultAtIndex_, class Register_>
	[[nodiscard]] inline bool cmp_selected_near(Register_ lhs_, Register_ rhs_)
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
					_underlying_simd_helpers::_cmp_near_equal<int_width_, SignedIfInt_>(lhs_, rhs_)
				) == movemask_generator::value;
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_selected_near, but the passed IndexMustBeTrue_ arguments could not be used with the provided SIMD register to form a valid movemask. The number of boolean arguments must be equal to 1 or the number of elements contained within the register. If the register is integral, the number of arguments can be 1, register_width/64, register_width/32, register_width/16, or register_width/8, where the bit-width per element is determined as the denominator in these fractions.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_selected_near, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}
	template<bool SignedIfInt_, bool...IndexMustBeTrue_, class Register_>
	[[nodiscard]] inline bool cmp_selected_near(Register_ lhs_, Register_ rhs_, EmuCore::TMP::bool_sequence<IndexMustBeTrue_...> indices_must_be_true)
	{
		return cmp_selected_near<SignedIfInt_, IndexMustBeTrue_...>(lhs_, rhs_);
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_all_near(Register_ lhs_, Register_ rhs_)
	{
		constexpr std::size_t count = EmuSIMD::TMP::register_element_count_v<Register_, PerElementWidthIfInt_>;
		return cmp_selected_near<SignedIfInt_>(lhs_, rhs_, EmuCore::TMP::make_true_bool_sequence<count>());
	}

	template<bool SignedIfInt_, bool...ResultAtIndex_, class Register_>
	[[nodiscard]] inline bool cmp_selected_near(Register_ lhs_, Register_ rhs_, Register_ epsilon)
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
					_underlying_simd_helpers::_cmp_near_equal<int_width_, SignedIfInt_>(lhs_, rhs_, epsilon)
				) == movemask_generator::value;
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_selected_near, but the passed IndexMustBeTrue_ arguments could not be used with the provided SIMD register to form a valid movemask. The number of boolean arguments must be equal to 1 or the number of elements contained within the register. If the register is integral, the number of arguments can be 1, register_width/64, register_width/32, register_width/16, or register_width/8, where the bit-width per element is determined as the denominator in these fractions.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_selected_near, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}
	template<bool SignedIfInt_, bool...IndexMustBeTrue_, class Register_>
	[[nodiscard]] inline bool cmp_selected_near(Register_ lhs_, Register_ rhs_, Register_ epsilon, EmuCore::TMP::bool_sequence<IndexMustBeTrue_...> indices_must_be_true)
	{
		return cmp_selected_near<SignedIfInt_, IndexMustBeTrue_...>(lhs_, rhs_, epsilon);
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_all_near(Register_ lhs_, Register_ rhs_, Register_ epsilon)
	{
		constexpr std::size_t count = EmuSIMD::TMP::register_element_count_v<Register_, PerElementWidthIfInt_>;
		return cmp_selected_near<SignedIfInt_>(lhs_, rhs_, epsilon, EmuCore::TMP::make_true_bool_sequence<count>());
	}

	template<int CmpFlags_, bool SignedIfInt_, bool...ResultAtIndex_, class Register_>
	[[nodiscard]] inline bool cmp_selected(Register_ lhs_, Register_ rhs_)
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
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_selected, but the passed IndexMustBeTrue_ arguments could not be used with the provided SIMD register to form a valid movemask. The number of boolean arguments must be equal to 1 or the number of elements contained within the register. If the register is integral, the number of arguments can be 1, register_width/64, register_width/32, register_width/16, or register_width/8, where the bit-width per element is determined as the denominator in these fractions.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::cmp_selected, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}
	template<int CmpFlags_, bool SignedIfInt_, bool...IndexMustBeTrue_, class Register_>
	[[nodiscard]] inline bool cmp_selected(Register_ lhs_, Register_ rhs_, EmuCore::TMP::bool_sequence<IndexMustBeTrue_...> indices_must_be_true)
	{
		return cmp_selected<CmpFlags_, SignedIfInt_, IndexMustBeTrue_...>(lhs_, rhs_);
	}

	template<int CmpFlags_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline bool cmp_all(Register_ lhs_, Register_ rhs_)
	{
		constexpr std::size_t count = EmuSIMD::TMP::register_element_count_v<Register_, PerElementWidthIfInt_>;
		return cmp_selected<CmpFlags_, SignedIfInt_>(lhs_, rhs_, EmuCore::TMP::make_true_bool_sequence<count>());
	}

#pragma region NAMED_INDICES_CMPS
	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are equal to those of rhs_, masks out unneeded indices as per `check_respective_indices_`, 
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <param name="check_respective_indices_">
	///		EmuCore bool_sequence, with `true` values indicating that the element in the respective index should be considered when determining the result. 
	///		A boolean is expected for every element. 
	///		When working with generic registers whose contents may be of variable length (such as x86 integral registers), 
	///		the width of an individual element is determined by the number of index arguments relative to the full width of the passed registers.		
	/// </param>
	/// <returns>True if all identified indices compared true, otherwise false.</returns>
	template<bool SignedIfInt_ = true, bool...CheckRespectiveIndex_, class Register_>
	[[nodiscard]] constexpr inline bool cmp_all_named_indices_eq
	(
		Register_ lhs_,
		Register_ rhs_,
		EmuCore::TMP::bool_sequence<CheckRespectiveIndex_...> check_respective_indices_
	) noexcept
	{
		using _register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t per_element_width = EmuSIMD::TMP::simd_register_width_v<_register_uq> / sizeof...(CheckRespectiveIndex_);
		if constexpr (per_element_width == 8 || per_element_width == 16 || per_element_width == 32 || per_element_width == 64)
		{
			using movemask_generator = make_movemask<_register_uq, CheckRespectiveIndex_...>;

			auto result = _underlying_simd_helpers::_cmp_eq<per_element_width, SignedIfInt_>(lhs_, rhs_);
			result = EmuSIMD::bitwise_and(result, EmuSIMD::make_index_mask_reverse<_register_uq, CheckRespectiveIndex_...>());
			return _underlying_simd_helpers::_movemask(result) == movemask_generator::value;
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<decltype(check_respective_indices_)>(),
				"Unable to perform `EmuSIMD::cmp_all_named_indices_eq` as the provided indices in the `check_respective_indices_` sequence does not result in a valid per-element width. A per-element width of 8, 16, 32, or 64 is expected."
			);
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are equal to those of rhs_, masks out unneeded indices as per `check_respective_indices_`, 
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <param name="check_respective_indices_">
	///		EmuCore bool_sequence, with `true` values indicating that the element in the respective index should be considered when determining the result. 
	///		A boolean is expected for every element. 
	///		When working with generic registers whose contents may be of variable length (such as x86 integral registers), 
	///		the width of an individual element is determined by the number of index arguments relative to the full width of the passed registers.		
	/// </param>
	/// <returns>True if any identified indices compared true, otherwise false.</returns>
	template<bool SignedIfInt_ = true, bool...CheckRespectiveIndex_, class Register_>
	[[nodiscard]] constexpr inline bool cmp_any_named_indices_eq
	(
		Register_ lhs_,
		Register_ rhs_,
		EmuCore::TMP::bool_sequence<CheckRespectiveIndex_...> check_respective_indices_
	) noexcept
	{
		using _register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t per_element_width = EmuSIMD::TMP::simd_register_width_v<_register_uq> / sizeof...(CheckRespectiveIndex_);
		if constexpr (per_element_width == 8 || per_element_width == 16 || per_element_width == 32 || per_element_width == 64)
		{
			auto result = _underlying_simd_helpers::_cmp_eq<per_element_width, SignedIfInt_>(lhs_, rhs_);
			result = EmuSIMD::bitwise_and(result, EmuSIMD::make_index_mask_reverse<_register_uq, CheckRespectiveIndex_...>());
			return _underlying_simd_helpers::_movemask(result) != 0;
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<decltype(check_respective_indices_)>(),
				"Unable to perform `EmuSIMD::cmp_any_named_indices_eq` as the provided indices in the `check_respective_indices_` sequence does not result in a valid per-element width. A per-element width of 8, 16, 32, or 64 is expected."
			);
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are near-equal to those of rhs_, masks out unneeded indices as per `check_respective_indices_`, 
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// <para> May optionally provide a third register to act as a custom epsilon before the index bool sequence. </para>
	/// <para> This is intended for floating-point comparisons where an equality check should take floating-point rounding inaccuracies into account. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <param name="check_respective_indices_">
	///		EmuCore bool_sequence, with `true` values indicating that the element in the respective index should be considered when determining the result. 
	///		A boolean is expected for every element. 
	///		When working with generic registers whose contents may be of variable length (such as x86 integral registers), 
	///		the width of an individual element is determined by the number of index arguments relative to the full width of the passed registers.		
	/// </param>
	/// <returns>True if all identified indices compared true, otherwise false.</returns>
	template<bool SignedIfInt_ = true, bool...CheckRespectiveIndex_, class Register_>
	[[nodiscard]] constexpr inline bool cmp_all_named_indices_near
	(
		Register_ lhs_,
		Register_ rhs_,
		EmuCore::TMP::bool_sequence<CheckRespectiveIndex_...> check_respective_indices_
	) noexcept
	{
		using _register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t per_element_width = EmuSIMD::TMP::simd_register_width_v<_register_uq> / sizeof...(CheckRespectiveIndex_);
		if constexpr (per_element_width == 8 || per_element_width == 16 || per_element_width == 32 || per_element_width == 64)
		{
			using movemask_generator = make_movemask<_register_uq, CheckRespectiveIndex_...>;

			auto result = _underlying_simd_helpers::_cmp_near_equal<per_element_width, SignedIfInt_>(lhs_, rhs_);
			result = EmuSIMD::bitwise_and(result, EmuSIMD::make_index_mask_reverse<_register_uq, CheckRespectiveIndex_...>());
			return _underlying_simd_helpers::_movemask(result) == movemask_generator::value;
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<decltype(check_respective_indices_)>(),
				"Unable to perform `EmuSIMD::cmp_all_named_indices_near` as the provided indices in the `check_respective_indices_` sequence does not result in a valid per-element width. A per-element width of 8, 16, 32, or 64 is expected."
			);
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are near-equal to those of rhs_, masks out unneeded indices as per `check_respective_indices_`, 
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// <para> May optionally provide a third register to act as a custom epsilon before the index bool sequence. </para>
	/// <para> This is intended for floating-point comparisons where an equality check should take floating-point rounding inaccuracies into account. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <param name="check_respective_indices_">
	///		EmuCore bool_sequence, with `true` values indicating that the element in the respective index should be considered when determining the result. 
	///		A boolean is expected for every element. 
	///		When working with generic registers whose contents may be of variable length (such as x86 integral registers), 
	///		the width of an individual element is determined by the number of index arguments relative to the full width of the passed registers.		
	/// </param>
	/// <returns>True if any identified indices compared true, otherwise false.</returns>
	template<bool SignedIfInt_ = true, bool...CheckRespectiveIndex_, class Register_>
	[[nodiscard]] constexpr inline bool cmp_any_named_indices_near
	(
		Register_ lhs_,
		Register_ rhs_,
		EmuCore::TMP::bool_sequence<CheckRespectiveIndex_...> check_respective_indices_
	) noexcept
	{
		using _register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t per_element_width = EmuSIMD::TMP::simd_register_width_v<_register_uq> / sizeof...(CheckRespectiveIndex_);
		if constexpr (per_element_width == 8 || per_element_width == 16 || per_element_width == 32 || per_element_width == 64)
		{
			auto result = _underlying_simd_helpers::_cmp_near_equal<per_element_width, SignedIfInt_>(lhs_, rhs_);
			result = EmuSIMD::bitwise_and(result, EmuSIMD::make_index_mask_reverse<_register_uq, CheckRespectiveIndex_...>());
			return _underlying_simd_helpers::_movemask(result) != 0;
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<decltype(check_respective_indices_)>(),
				"Unable to perform `EmuSIMD::cmp_any_named_indices_near` as the provided indices in the `check_respective_indices_` sequence does not result in a valid per-element width. A per-element width of 8, 16, 32, or 64 is expected."
			);
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are near-equal to those of rhs_, masks out unneeded indices as per `check_respective_indices_`, 
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// <para> May optionally provide a third register to act as a custom epsilon before the index bool sequence. </para>
	/// <para> This is intended for floating-point comparisons where an equality check should take floating-point rounding inaccuracies into account. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <param name="epsilon_">
	///		Optional EmuSIMD-supported register used as the maximum difference between respective values for a comparison to be considered equal. 
	///		If omitted, will default to the most sensible epsilon based on the determined element type within the registers.
	/// </param>
	/// <param name="check_respective_indices_">
	///		EmuCore bool_sequence, with `true` values indicating that the element in the respective index should be considered when determining the result. 
	///		A boolean is expected for every element. 
	///		When working with generic registers whose contents may be of variable length (such as x86 integral registers), 
	///		the width of an individual element is determined by the number of index arguments relative to the full width of the passed registers.		
	/// </param>
	/// <returns>True if all identified indices compared true, otherwise false.</returns>
	template<bool SignedIfInt_ = true, bool...CheckRespectiveIndex_, class Register_>
	[[nodiscard]] constexpr inline bool cmp_all_named_indices_near
	(
		Register_ lhs_,
		Register_ rhs_,
		Register_ epsilon_,
		EmuCore::TMP::bool_sequence<CheckRespectiveIndex_...> check_respective_indices_
	) noexcept
	{
		using _register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t per_element_width = EmuSIMD::TMP::simd_register_width_v<_register_uq> / sizeof...(CheckRespectiveIndex_);
		if constexpr (per_element_width == 8 || per_element_width == 16 || per_element_width == 32 || per_element_width == 64)
		{
			using movemask_generator = make_movemask<_register_uq, CheckRespectiveIndex_...>;

			auto result = _underlying_simd_helpers::_cmp_near_equal<per_element_width, SignedIfInt_>(lhs_, rhs_, epsilon_);
			result = EmuSIMD::bitwise_and(result, EmuSIMD::make_index_mask_reverse<_register_uq, CheckRespectiveIndex_...>());
			return _underlying_simd_helpers::_movemask(result) == movemask_generator::value;
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<decltype(check_respective_indices_)>(),
				"Unable to perform `EmuSIMD::cmp_all_named_indices_near` as the provided indices in the `check_respective_indices_` sequence does not result in a valid per-element width. A per-element width of 8, 16, 32, or 64 is expected."
			);
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are near-equal to those of rhs_, masks out unneeded indices as per `check_respective_indices_`, 
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// <para> May optionally provide a third register to act as a custom epsilon before the index bool sequence. </para>
	/// <para> This is intended for floating-point comparisons where an equality check should take floating-point rounding inaccuracies into account. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <param name="epsilon_">
	///		Optional EmuSIMD-supported register used as the maximum difference between respective values for a comparison to be considered equal. 
	///		If omitted, will default to the most sensible epsilon based on the determined element type within the registers.
	/// </param>
	/// <param name="check_respective_indices_">
	///		EmuCore bool_sequence, with `true` values indicating that the element in the respective index should be considered when determining the result. 
	///		A boolean is expected for every element. 
	///		When working with generic registers whose contents may be of variable length (such as x86 integral registers), 
	///		the width of an individual element is determined by the number of index arguments relative to the full width of the passed registers.		
	/// </param>
	/// <returns>True if any identified indices compared true, otherwise false.</returns>
	template<bool SignedIfInt_ = true, bool...CheckRespectiveIndex_, class Register_>
	[[nodiscard]] constexpr inline bool cmp_any_named_indices_near
	(
		Register_ lhs_,
		Register_ rhs_,
		Register_ epsilon_,
		EmuCore::TMP::bool_sequence<CheckRespectiveIndex_...> check_respective_indices_
	) noexcept
	{
		using _register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t per_element_width = EmuSIMD::TMP::simd_register_width_v<_register_uq> / sizeof...(CheckRespectiveIndex_);
		if constexpr (per_element_width == 8 || per_element_width == 16 || per_element_width == 32 || per_element_width == 64)
		{
			auto result = _underlying_simd_helpers::_cmp_near_equal<per_element_width, SignedIfInt_>(lhs_, rhs_, epsilon_);
			result = EmuSIMD::bitwise_and(result, EmuSIMD::make_index_mask_reverse<_register_uq, CheckRespectiveIndex_...>());
			return _underlying_simd_helpers::_movemask(result) != 0;
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<decltype(check_respective_indices_)>(),
				"Unable to perform `EmuSIMD::cmp_any_named_indices_near` as the provided indices in the `check_respective_indices_` sequence does not result in a valid per-element width. A per-element width of 8, 16, 32, or 64 is expected."
			);
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are not equal to those of rhs_, masks out unneeded indices as per `check_respective_indices_`, 
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <param name="check_respective_indices_">
	///		EmuCore bool_sequence, with `true` values indicating that the element in the respective index should be considered when determining the result. 
	///		A boolean is expected for every element. 
	///		When working with generic registers whose contents may be of variable length (such as x86 integral registers), 
	///		the width of an individual element is determined by the number of index arguments relative to the full width of the passed registers.		
	/// </param>
	/// <returns>True if all identified indices compared true, otherwise false.</returns>
	template<bool SignedIfInt_ = true, bool...CheckRespectiveIndex_, class Register_>
	[[nodiscard]] constexpr inline bool cmp_all_named_indices_neq
	(
		Register_ lhs_,
		Register_ rhs_,
		EmuCore::TMP::bool_sequence<CheckRespectiveIndex_...> check_respective_indices_
	) noexcept
	{
		using _register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t per_element_width = EmuSIMD::TMP::simd_register_width_v<_register_uq> / sizeof...(CheckRespectiveIndex_);
		if constexpr (per_element_width == 8 || per_element_width == 16 || per_element_width == 32 || per_element_width == 64)
		{
			using movemask_generator = make_movemask<_register_uq, CheckRespectiveIndex_...>;

			auto result = _underlying_simd_helpers::_cmp_neq<per_element_width, SignedIfInt_>(lhs_, rhs_);
			result = EmuSIMD::bitwise_and(result, make_index_mask_reverse<_register_uq, CheckRespectiveIndex_...>());
			return _underlying_simd_helpers::_movemask(result) == movemask_generator::value;
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<decltype(check_respective_indices_)>(),
				"Unable to perform `EmuSIMD::cmp_all_named_indices_neq` as the provided indices in the `check_respective_indices_` sequence does not result in a valid per-element width. A per-element width of 8, 16, 32, or 64 is expected."
			);
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are not equal to those of rhs_, masks out unneeded indices as per `check_respective_indices_`, 
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <param name="check_respective_indices_">
	///		EmuCore bool_sequence, with `true` values indicating that the element in the respective index should be considered when determining the result. 
	///		A boolean is expected for every element. 
	///		When working with generic registers whose contents may be of variable length (such as x86 integral registers), 
	///		the width of an individual element is determined by the number of index arguments relative to the full width of the passed registers.		
	/// </param>
	/// <returns>True if any identified indices compared true, otherwise false.</returns>
	template<bool SignedIfInt_ = true, bool...CheckRespectiveIndex_, class Register_>
	[[nodiscard]] constexpr inline bool cmp_any_named_indices_neq
	(
		Register_ lhs_,
		Register_ rhs_,
		EmuCore::TMP::bool_sequence<CheckRespectiveIndex_...> check_respective_indices_
	) noexcept
	{
		using _register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t per_element_width = EmuSIMD::TMP::simd_register_width_v<_register_uq> / sizeof...(CheckRespectiveIndex_);
		if constexpr (per_element_width == 8 || per_element_width == 16 || per_element_width == 32 || per_element_width == 64)
		{
			auto result = _underlying_simd_helpers::_cmp_neq<per_element_width, SignedIfInt_>(lhs_, rhs_);
			result = EmuSIMD::bitwise_and(result, EmuSIMD::make_index_mask_reverse<_register_uq, CheckRespectiveIndex_...>());
			return _underlying_simd_helpers::_movemask(result) != 0;
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<decltype(check_respective_indices_)>(),
				"Unable to perform `EmuSIMD::cmp_any_named_indices_neq` as the provided indices in the `check_respective_indices_` sequence does not result in a valid per-element width. A per-element width of 8, 16, 32, or 64 is expected."
			);
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are greater than those of rhs_, masks out unneeded indices as per `check_respective_indices_`, 
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <param name="check_respective_indices_">
	///		EmuCore bool_sequence, with `true` values indicating that the element in the respective index should be considered when determining the result. 
	///		A boolean is expected for every element. 
	///		When working with generic registers whose contents may be of variable length (such as x86 integral registers), 
	///		the width of an individual element is determined by the number of index arguments relative to the full width of the passed registers.		
	/// </param>
	/// <returns>True if all identified indices compared true, otherwise false.</returns>
	template<bool SignedIfInt_ = true, bool...CheckRespectiveIndex_, class Register_>
	[[nodiscard]] constexpr inline bool cmp_all_named_indices_gt
	(
		Register_ lhs_,
		Register_ rhs_,
		EmuCore::TMP::bool_sequence<CheckRespectiveIndex_...> check_respective_indices_
	) noexcept
	{
		using _register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t per_element_width = EmuSIMD::TMP::simd_register_width_v<_register_uq> / sizeof...(CheckRespectiveIndex_);
		if constexpr (per_element_width == 8 || per_element_width == 16 || per_element_width == 32 || per_element_width == 64)
		{
			using movemask_generator = make_movemask<_register_uq, CheckRespectiveIndex_...>;

			auto result = _underlying_simd_helpers::_cmp_gt<per_element_width, SignedIfInt_>(lhs_, rhs_);
			result = EmuSIMD::bitwise_and(result, EmuSIMD::make_index_mask_reverse<_register_uq, CheckRespectiveIndex_...>());
			return _underlying_simd_helpers::_movemask(result) == movemask_generator::value;
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<decltype(check_respective_indices_)>(),
				"Unable to perform `EmuSIMD::cmp_all_named_indices_gt` as the provided indices in the `check_respective_indices_` sequence does not result in a valid per-element width. A per-element width of 8, 16, 32, or 64 is expected."
			);
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are greater than those of rhs_, masks out unneeded indices as per `check_respective_indices_`, 
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <param name="check_respective_indices_">
	///		EmuCore bool_sequence, with `true` values indicating that the element in the respective index should be considered when determining the result. 
	///		A boolean is expected for every element. 
	///		When working with generic registers whose contents may be of variable length (such as x86 integral registers), 
	///		the width of an individual element is determined by the number of index arguments relative to the full width of the passed registers.		
	/// </param>
	/// <returns>True if any identified indices compared true, otherwise false.</returns>
	template<bool SignedIfInt_ = true, bool...CheckRespectiveIndex_, class Register_>
	[[nodiscard]] constexpr inline bool cmp_any_named_indices_gt
	(
		Register_ lhs_,
		Register_ rhs_,
		EmuCore::TMP::bool_sequence<CheckRespectiveIndex_...> check_respective_indices_
	) noexcept
	{
		using _register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t per_element_width = EmuSIMD::TMP::simd_register_width_v<_register_uq> / sizeof...(CheckRespectiveIndex_);
		if constexpr (per_element_width == 8 || per_element_width == 16 || per_element_width == 32 || per_element_width == 64)
		{
			auto result = _underlying_simd_helpers::_cmp_gt<per_element_width, SignedIfInt_>(lhs_, rhs_);
			result = EmuSIMD::bitwise_and(result, EmuSIMD::make_index_mask_reverse<_register_uq, CheckRespectiveIndex_...>());
			return _underlying_simd_helpers::_movemask(result) != 0;
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<decltype(check_respective_indices_)>(),
				"Unable to perform `EmuSIMD::cmp_any_named_indices_gt` as the provided indices in the `check_respective_indices_` sequence does not result in a valid per-element width. A per-element width of 8, 16, 32, or 64 is expected."
			);
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are less than those of rhs_, masks out unneeded indices as per `check_respective_indices_`, 
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <param name="check_respective_indices_">
	///		EmuCore bool_sequence, with `true` values indicating that the element in the respective index should be considered when determining the result. 
	///		A boolean is expected for every element. 
	///		When working with generic registers whose contents may be of variable length (such as x86 integral registers), 
	///		the width of an individual element is determined by the number of index arguments relative to the full width of the passed registers.		
	/// </param>
	/// <returns>True if all identified indices compared true, otherwise false.</returns>
	template<bool SignedIfInt_ = true, bool...CheckRespectiveIndex_, class Register_>
	[[nodiscard]] constexpr inline bool cmp_all_named_indices_lt
	(
		Register_ lhs_,
		Register_ rhs_,
		EmuCore::TMP::bool_sequence<CheckRespectiveIndex_...> check_respective_indices_
	) noexcept
	{
		using _register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t per_element_width = EmuSIMD::TMP::simd_register_width_v<_register_uq> / sizeof...(CheckRespectiveIndex_);
		if constexpr (per_element_width == 8 || per_element_width == 16 || per_element_width == 32 || per_element_width == 64)
		{
			using movemask_generator = make_movemask<_register_uq, CheckRespectiveIndex_...>;

			auto result = _underlying_simd_helpers::_cmp_lt<per_element_width, SignedIfInt_>(lhs_, rhs_);
			result = EmuSIMD::bitwise_and(result, EmuSIMD::make_index_mask_reverse<_register_uq, CheckRespectiveIndex_...>());
			return _underlying_simd_helpers::_movemask(result) == movemask_generator::value;
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<decltype(check_respective_indices_)>(),
				"Unable to perform `EmuSIMD::cmp_all_named_indices_lt` as the provided indices in the `check_respective_indices_` sequence does not result in a valid per-element width. A per-element width of 8, 16, 32, or 64 is expected."
			);
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are less than those of rhs_, masks out unneeded indices as per `check_respective_indices_`, 
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <param name="check_respective_indices_">
	///		EmuCore bool_sequence, with `true` values indicating that the element in the respective index should be considered when determining the result. 
	///		A boolean is expected for every element. 
	///		When working with generic registers whose contents may be of variable length (such as x86 integral registers), 
	///		the width of an individual element is determined by the number of index arguments relative to the full width of the passed registers.		
	/// </param>
	/// <returns>True if any identified indices compared true, otherwise false.</returns>
	template<bool SignedIfInt_ = true, bool...CheckRespectiveIndex_, class Register_>
	[[nodiscard]] constexpr inline bool cmp_any_named_indices_lt
	(
		Register_ lhs_,
		Register_ rhs_,
		EmuCore::TMP::bool_sequence<CheckRespectiveIndex_...> check_respective_indices_
	) noexcept
	{
		using _register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t per_element_width = EmuSIMD::TMP::simd_register_width_v<_register_uq> / sizeof...(CheckRespectiveIndex_);
		if constexpr (per_element_width == 8 || per_element_width == 16 || per_element_width == 32 || per_element_width == 64)
		{
			auto result = _underlying_simd_helpers::_cmp_lt<per_element_width, SignedIfInt_>(lhs_, rhs_);
			result = EmuSIMD::bitwise_and(result, EmuSIMD::make_index_mask_reverse<_register_uq, CheckRespectiveIndex_...>());
			return _underlying_simd_helpers::_movemask(result) != 0;
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<decltype(check_respective_indices_)>(),
				"Unable to perform `EmuSIMD::cmp_any_named_indices_lt` as the provided indices in the `check_respective_indices_` sequence does not result in a valid per-element width. A per-element width of 8, 16, 32, or 64 is expected."
			);
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are greater than or equal to those of rhs_, masks out unneeded indices as per `check_respective_indices_`, 
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <param name="check_respective_indices_">
	///		EmuCore bool_sequence, with `true` values indicating that the element in the respective index should be considered when determining the result. 
	///		A boolean is expected for every element. 
	///		When working with generic registers whose contents may be of variable length (such as x86 integral registers), 
	///		the width of an individual element is determined by the number of index arguments relative to the full width of the passed registers.		
	/// </param>
	/// <returns>True if all identified indices compared true, otherwise false.</returns>
	template<bool SignedIfInt_ = true, bool...CheckRespectiveIndex_, class Register_>
	[[nodiscard]] constexpr inline bool cmp_all_named_indices_ge
	(
		Register_ lhs_,
		Register_ rhs_,
		EmuCore::TMP::bool_sequence<CheckRespectiveIndex_...> check_respective_indices_
	) noexcept
	{
		using _register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t per_element_width = EmuSIMD::TMP::simd_register_width_v<_register_uq> / sizeof...(CheckRespectiveIndex_);
		if constexpr (per_element_width == 8 || per_element_width == 16 || per_element_width == 32 || per_element_width == 64)
		{
			using movemask_generator = make_movemask<_register_uq, CheckRespectiveIndex_...>;

			auto result = _underlying_simd_helpers::_cmp_ge<per_element_width, SignedIfInt_>(lhs_, rhs_);
			result = EmuSIMD::bitwise_and(result, EmuSIMD::make_index_mask_reverse<_register_uq, CheckRespectiveIndex_...>());
			return _underlying_simd_helpers::_movemask(result) == movemask_generator::value;
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<decltype(check_respective_indices_)>(),
				"Unable to perform `EmuSIMD::cmp_all_named_indices_ge` as the provided indices in the `check_respective_indices_` sequence does not result in a valid per-element width. A per-element width of 8, 16, 32, or 64 is expected."
			);
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are greater than or equal to those of rhs_, masks out unneeded indices as per `check_respective_indices_`, 
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <param name="check_respective_indices_">
	///		EmuCore bool_sequence, with `true` values indicating that the element in the respective index should be considered when determining the result. 
	///		A boolean is expected for every element. 
	///		When working with generic registers whose contents may be of variable length (such as x86 integral registers), 
	///		the width of an individual element is determined by the number of index arguments relative to the full width of the passed registers.		
	/// </param>
	/// <returns>True if any identified indices compared true, otherwise false.</returns>
	template<bool SignedIfInt_ = true, bool...CheckRespectiveIndex_, class Register_>
	[[nodiscard]] constexpr inline bool cmp_any_named_indices_ge
	(
		Register_ lhs_,
		Register_ rhs_,
		EmuCore::TMP::bool_sequence<CheckRespectiveIndex_...> check_respective_indices_
	) noexcept
	{
		using _register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t per_element_width = EmuSIMD::TMP::simd_register_width_v<_register_uq> / sizeof...(CheckRespectiveIndex_);
		if constexpr (per_element_width == 8 || per_element_width == 16 || per_element_width == 32 || per_element_width == 64)
		{
			auto result = _underlying_simd_helpers::_cmp_ge<per_element_width, SignedIfInt_>(lhs_, rhs_);
			result = EmuSIMD::bitwise_and(result, EmuSIMD::make_index_mask_reverse<_register_uq, CheckRespectiveIndex_...>());
			return _underlying_simd_helpers::_movemask(result) != 0;
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<decltype(check_respective_indices_)>(),
				"Unable to perform `EmuSIMD::cmp_any_named_indices_ge` as the provided indices in the `check_respective_indices_` sequence does not result in a valid per-element width. A per-element width of 8, 16, 32, or 64 is expected."
			);
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are less than or equal to those of rhs_, masks out unneeded indices as per `check_respective_indices_`, 
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <param name="check_respective_indices_">
	///		EmuCore bool_sequence, with `true` values indicating that the element in the respective index should be considered when determining the result. 
	///		A boolean is expected for every element. 
	///		When working with generic registers whose contents may be of variable length (such as x86 integral registers), 
	///		the width of an individual element is determined by the number of index arguments relative to the full width of the passed registers.		
	/// </param>
	/// <returns>True if all identified indices compared true, otherwise false.</returns>
	template<bool SignedIfInt_ = true, bool...CheckRespectiveIndex_, class Register_>
	[[nodiscard]] constexpr inline bool cmp_all_named_indices_le
	(
		Register_ lhs_,
		Register_ rhs_,
		EmuCore::TMP::bool_sequence<CheckRespectiveIndex_...> check_respective_indices_
	) noexcept
	{
		using _register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t per_element_width = EmuSIMD::TMP::simd_register_width_v<_register_uq> / sizeof...(CheckRespectiveIndex_);
		if constexpr (per_element_width == 8 || per_element_width == 16 || per_element_width == 32 || per_element_width == 64)
		{
			using movemask_generator = make_movemask<_register_uq, CheckRespectiveIndex_...>;

			auto result = _underlying_simd_helpers::_cmp_le<per_element_width, SignedIfInt_>(lhs_, rhs_);
			result = EmuSIMD::bitwise_and(result, EmuSIMD::make_index_mask_reverse<_register_uq, CheckRespectiveIndex_...>());
			return _underlying_simd_helpers::_movemask(result) == movemask_generator::value;
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<decltype(check_respective_indices_)>(),
				"Unable to perform `EmuSIMD::cmp_all_named_indices_le` as the provided indices in the `check_respective_indices_` sequence does not result in a valid per-element width. A per-element width of 8, 16, 32, or 64 is expected."
			);
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are less than or equal to those of rhs_, masks out unneeded indices as per `check_respective_indices_`, 
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <param name="check_respective_indices_">
	///		EmuCore bool_sequence, with `true` values indicating that the element in the respective index should be considered when determining the result. 
	///		A boolean is expected for every element. 
	///		When working with generic registers whose contents may be of variable length (such as x86 integral registers), 
	///		the width of an individual element is determined by the number of index arguments relative to the full width of the passed registers.		
	/// </param>
	/// <returns>True if any identified indices compared true, otherwise false.</returns>
	template<bool SignedIfInt_ = true, bool...CheckRespectiveIndex_, class Register_>
	[[nodiscard]] constexpr inline bool cmp_any_named_indices_le
	(
		Register_ lhs_,
		Register_ rhs_,
		EmuCore::TMP::bool_sequence<CheckRespectiveIndex_...> check_respective_indices_
	) noexcept
	{
		using _register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t per_element_width = EmuSIMD::TMP::simd_register_width_v<_register_uq> / sizeof...(CheckRespectiveIndex_);
		if constexpr (per_element_width == 8 || per_element_width == 16 || per_element_width == 32 || per_element_width == 64)
		{
			auto result = _underlying_simd_helpers::_cmp_le<per_element_width, SignedIfInt_>(lhs_, rhs_);
			result = EmuSIMD::bitwise_and(result, EmuSIMD::make_index_mask_reverse<_register_uq, CheckRespectiveIndex_...>());
			return _underlying_simd_helpers::_movemask(result) != 0;
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<decltype(check_respective_indices_)>(),
				"Unable to perform `EmuSIMD::cmp_any_named_indices_le` as the provided indices in the `check_respective_indices_` sequence does not result in a valid per-element width. A per-element width of 8, 16, 32, or 64 is expected."
			);
		}
	}
#pragma endregion

#pragma region X_INDICES_CMPS
	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are equal to those of rhs_, masks out indices starting from index X_,
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if all of the first X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_firstx_all_eq(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_all_eq<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, false>;
			return EmuSIMD::cmp_all_named_indices_eq<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are equal to those of rhs_, masks out indices starting from index X_,
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if any of the first X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_firstx_any_eq(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_any_eq<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, false>;
			return EmuSIMD::cmp_any_named_indices_eq<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are equal to those of rhs_, masks out indices 0 to (X_ - 1) (inclusive),
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if all of the last X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_lastx_all_eq(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_all_eq<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, true>;
			return EmuSIMD::cmp_all_named_indices_eq<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are equal to those of rhs_, masks out indices 0 to (X_ - 1) (inclusive),
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if any of the last X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_lastx_any_eq(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_any_eq<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, true>;
			return EmuSIMD::cmp_any_named_indices_eq<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are near-equal to those of rhs_, masks out indices starting from index X_,
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// <para> May optionally provide a third register to act as a custom epsilon before the index bool sequence. </para>
	/// <para> This is intended for floating-point comparisons where an equality check should take floating-point rounding inaccuracies into account. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if all of the first X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_firstx_all_near(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_all_near<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, false>;
			return EmuSIMD::cmp_all_named_indices_near<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are near-equal to those of rhs_, masks out indices starting from index X_,
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// <para> May optionally provide a third register to act as a custom epsilon before the index bool sequence. </para>
	/// <para> This is intended for floating-point comparisons where an equality check should take floating-point rounding inaccuracies into account. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if any of the first X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_firstx_any_near(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_any_near<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, false>;
			return EmuSIMD::cmp_any_named_indices_near<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are near-equal to those of rhs_, masks out indices 0 to (X_ - 1) (inclusive),
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// <para> May optionally provide a third register to act as a custom epsilon before the index bool sequence. </para>
	/// <para> This is intended for floating-point comparisons where an equality check should take floating-point rounding inaccuracies into account. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if all of the last X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_lastx_all_near(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_all_near<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, true>;
			return EmuSIMD::cmp_all_named_indices_near<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are near-equal to those of rhs_, masks out indices 0 to (X_ - 1) (inclusive),
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// <para> May optionally provide a third register to act as a custom epsilon before the index bool sequence. </para>
	/// <para> This is intended for floating-point comparisons where an equality check should take floating-point rounding inaccuracies into account. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if any of the last X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_lastx_any_near(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_any_near<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, true>;
			return EmuSIMD::cmp_any_named_indices_near<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are near-equal to those of rhs_, masks out indices starting from index X_,
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// <para> May optionally provide a third register to act as a custom epsilon before the index bool sequence. </para>
	/// <para> This is intended for floating-point comparisons where an equality check should take floating-point rounding inaccuracies into account. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <param name="epsilon_">
	///		Optional EmuSIMD-supported register used as the maximum difference between respective values for a comparison to be considered equal. 
	///		If omitted, will default to the most sensible epsilon based on the determined element type within the registers.
	/// </param>
	/// <returns>True if all of the first X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_firstx_all_near(Register_ lhs_, Register_ rhs_, Register_ epsilon_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_all_near<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_, epsilon_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, false>;
			return EmuSIMD::cmp_all_named_indices_near<SignedIfInt_>(lhs_, rhs_, epsilon_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are near-equal to those of rhs_, masks out indices starting from index X_,
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// <para> May optionally provide a third register to act as a custom epsilon before the index bool sequence. </para>
	/// <para> This is intended for floating-point comparisons where an equality check should take floating-point rounding inaccuracies into account. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <param name="epsilon_">
	///		Optional EmuSIMD-supported register used as the maximum difference between respective values for a comparison to be considered equal. 
	///		If omitted, will default to the most sensible epsilon based on the determined element type within the registers.
	/// </param>
	/// <returns>True if any of the first X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_firstx_any_near(Register_ lhs_, Register_ rhs_, Register_ epsilon_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_any_near<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_, epsilon_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, false>;
			return EmuSIMD::cmp_any_named_indices_near<SignedIfInt_>(lhs_, rhs_, epsilon_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are near-equal to those of rhs_, masks out indices 0 to (X_ - 1) (inclusive),
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// <para> May optionally provide a third register to act as a custom epsilon before the index bool sequence. </para>
	/// <para> This is intended for floating-point comparisons where an equality check should take floating-point rounding inaccuracies into account. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <param name="epsilon_">
	///		Optional EmuSIMD-supported register used as the maximum difference between respective values for a comparison to be considered equal. 
	///		If omitted, will default to the most sensible epsilon based on the determined element type within the registers.
	/// </param>
	/// <returns>True if all of the last X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_lastx_all_near(Register_ lhs_, Register_ rhs_, Register_ epsilon_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_all_near<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_, epsilon_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, true>;
			return EmuSIMD::cmp_all_named_indices_near<SignedIfInt_>(lhs_, rhs_, epsilon_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are near-equal to those of rhs_, masks out indices 0 to (X_ - 1) (inclusive),
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// <para> May optionally provide a third register to act as a custom epsilon before the index bool sequence. </para>
	/// <para> This is intended for floating-point comparisons where an equality check should take floating-point rounding inaccuracies into account. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <param name="epsilon_">
	///		Optional EmuSIMD-supported register used as the maximum difference between respective values for a comparison to be considered equal. 
	///		If omitted, will default to the most sensible epsilon based on the determined element type within the registers.
	/// </param>
	/// <returns>True if any of the last X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_lastx_any_near(Register_ lhs_, Register_ rhs_, Register_ epsilon_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_any_near<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_, epsilon_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, true>;
			return EmuSIMD::cmp_any_named_indices_near<SignedIfInt_>(lhs_, rhs_, epsilon_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are not equal to those of rhs_, masks out indices starting from index X_,
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if all of the first X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_firstx_all_neq(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_all_neq<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, false>;
			return EmuSIMD::cmp_all_named_indices_neq<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are not equal to those of rhs_, masks out indices starting from index X_,
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if any of the first X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_firstx_any_neq(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_any_neq<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, false>;
			return EmuSIMD::cmp_any_named_indices_neq<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are not equal to those of rhs_, masks out indices 0 to (X_ - 1) (inclusive),
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if all of the last X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_lastx_all_neq(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_all_neq<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, true>;
			return EmuSIMD::cmp_all_named_indices_neq<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are not equal to those of rhs_, masks out indices 0 to (X_ - 1) (inclusive),
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if any of the last X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_lastx_any_neq(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_any_neq<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, true>;
			return EmuSIMD::cmp_any_named_indices_neq<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are greater than those of rhs_, masks out indices starting from index X_,
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if all of the first X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_firstx_all_gt(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_all_gt<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, false>;
			return EmuSIMD::cmp_all_named_indices_gt<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are greater than those of rhs_, masks out indices starting from index X_,
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if any of the first X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_firstx_any_gt(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_any_gt<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, false>;
			return EmuSIMD::cmp_any_named_indices_gt<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are greater than those of rhs_, masks out indices 0 to (X_ - 1) (inclusive),
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if all of the last X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_lastx_all_gt(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_all_gt<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, true>;
			return EmuSIMD::cmp_all_named_indices_gt<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are greater than those of rhs_, masks out indices 0 to (X_ - 1) (inclusive),
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if any of the last X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_lastx_any_gt(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_any_gt<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, true>;
			return EmuSIMD::cmp_any_named_indices_gt<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are less than those of rhs_, masks out indices starting from index X_,
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if all of the first X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_firstx_all_lt(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_all_lt<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, false>;
			return EmuSIMD::cmp_all_named_indices_lt<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are less than those of rhs_, masks out indices starting from index X_,
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if any of the first X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_firstx_any_lt(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_any_lt<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, false>;
			return EmuSIMD::cmp_any_named_indices_lt<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are less than those of rhs_, masks out indices 0 to (X_ - 1) (inclusive),
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if all of the last X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_lastx_all_lt(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_all_lt<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, true>;
			return EmuSIMD::cmp_all_named_indices_lt<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are less than those of rhs_, masks out indices 0 to (X_ - 1) (inclusive),
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if any of the last X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_lastx_any_lt(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_any_lt<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, true>;
			return EmuSIMD::cmp_any_named_indices_lt<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are greater than or equal to those of rhs_, masks out indices starting from index X_,
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if all of the first X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_firstx_all_ge(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_all_ge<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, false>;
			return EmuSIMD::cmp_all_named_indices_ge<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are greater than or equal to those of rhs_, masks out indices starting from index X_,
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if any of the first X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_firstx_any_ge(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_any_ge<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, false>;
			return EmuSIMD::cmp_any_named_indices_ge<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are greater than or equal to those of rhs_, masks out indices 0 to (X_ - 1) (inclusive),
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if all of the last X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_lastx_all_ge(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_all_ge<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, true>;
			return EmuSIMD::cmp_all_named_indices_ge<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are greater than or equal to those of rhs_, masks out indices 0 to (X_ - 1) (inclusive),
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if any of the last X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_lastx_any_ge(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_any_ge<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, true>;
			return EmuSIMD::cmp_any_named_indices_ge<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are less than or equal to those of rhs_, masks out indices starting from index X_,
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if all of the first X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_firstx_all_le(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_all_le<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, false>;
			return EmuSIMD::cmp_all_named_indices_le<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are less than or equal to those of rhs_, masks out indices starting from index X_,
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if any of the first X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_firstx_any_le(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_any_le<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, false>;
			return EmuSIMD::cmp_any_named_indices_le<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are less than or equal to those of rhs_, masks out indices 0 to (X_ - 1) (inclusive),
	///		and returns a boolean indicating if all remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if all of the last X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_lastx_all_le(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_all_le<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, true>;
			return EmuSIMD::cmp_all_named_indices_le<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}

	/// <summary>
	/// <para>
	///		Compares if elements in lhs_ are less than or equal to those of rhs_, masks out indices 0 to (X_ - 1) (inclusive),
	///		and returns a boolean indicating if any remaining indices compared true.
	/// </para>
	/// <para> X_ is the first template argument provided to this function. </para>
	/// </summary>
	/// <param name="lhs_">EmuSIMD-supported register appearing on the left-hand side of comparison.</param>
	/// <param name="rhs_">EmuSIMD-supported register appearing on the right-hand side of comparison.</param>
	/// <returns>True if any of the last X_ indices compared true, otherwise false.</returns>
	template<std::size_t X_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline bool cmp_lastx_any_le(Register_ lhs_, Register_ rhs_) noexcept
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<_register_type_uq, PerElementWidthIfInt_>;
		if constexpr (X_ >= num_elements)
		{
			return EmuSIMD::cmp_any_le<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
		}
		else
		{
			using _checked_indices = EmuCore::TMP::make_chunked_true_false_bool_sequence<X_, num_elements - X_, true>;
			return EmuSIMD::cmp_any_named_indices_le<SignedIfInt_>(lhs_, rhs_, _checked_indices());
		}
	}
#pragma endregion
}

#endif
