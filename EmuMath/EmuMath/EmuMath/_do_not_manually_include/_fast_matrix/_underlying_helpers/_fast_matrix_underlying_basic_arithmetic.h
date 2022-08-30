#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_BASIC_ARITHMETIC_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_BASIC_ARITHMETIC_H_INC_ 1

#include "_fast_matrix_tmp.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
	template<EmuConcepts::EmuFastMatrix ForFastMatrix_>
	struct _basic_add_func
	{
		template<class LhsRegister_, class RhsRegister_>
		[[nodiscard]] constexpr inline decltype(auto) operator()(LhsRegister_&& lhs_, RhsRegister_&& rhs_) const
		{
			using _for_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<ForFastMatrix_>::type;
			if constexpr(!_is_register_out_of_range_type_v<LhsRegister_>)
			{
				if constexpr(!_is_register_out_of_range_type_v<RhsRegister_>)
				{
					return EmuSIMD::add<_for_fast_mat_uq::per_element_width>
					(
						std::forward<LhsRegister_>(lhs_),
						std::forward<RhsRegister_>(rhs_)
					);
				}
				else
				{
					return std::forward<LhsRegister_>(lhs_);
				}
			}
			else if constexpr (!_is_register_out_of_range_type_v<RhsRegister_>)
			{
				return std::forward<RhsRegister_>(rhs_);
			}
			else
			{
				return EmuSIMD::setzero<typename _for_fast_mat_uq::register_type>();
			}
		}
	};

	template<EmuConcepts::EmuFastMatrix ForFastMatrix_>
	struct _basic_sub_func
	{
		template<class LhsRegister_, class RhsRegister_>
		[[nodiscard]] constexpr inline decltype(auto) operator()(LhsRegister_&& lhs_, RhsRegister_&& rhs_) const
		{
			using _for_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<ForFastMatrix_>::type;
			if constexpr(!_is_register_out_of_range_type_v<LhsRegister_>)
			{
				if constexpr(!_is_register_out_of_range_type_v<RhsRegister_>)
				{
					return EmuSIMD::sub<_for_fast_mat_uq::per_element_width>
					(
						std::forward<LhsRegister_>(lhs_),
						std::forward<RhsRegister_>(rhs_)
					);
				}
				else
				{
					return std::forward<LhsRegister_>(lhs_);
				}
			}
			else if constexpr (!_is_register_out_of_range_type_v<RhsRegister_>)
			{
				return EmuSIMD::negate<_for_fast_mat_uq::per_element_width>(std::forward<RhsRegister_>(rhs_));
			}
			else
			{
				return EmuSIMD::setzero<typename _for_fast_mat_uq::register_type>();
			}
		}
	};

	template<EmuConcepts::EmuFastMatrix ForFastMatrix_>
	struct _basic_mul_func
	{
		template<class LhsRegister_, class RhsRegister_>
		[[nodiscard]] constexpr inline decltype(auto) operator()(LhsRegister_&& lhs_, RhsRegister_&& rhs_) const
		{
			using _for_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<ForFastMatrix_>::type;
			if constexpr(!_is_register_out_of_range_type_v<LhsRegister_> && !_is_register_out_of_range_type_v<RhsRegister_>)
			{
				return EmuSIMD::mul_all<_for_fast_mat_uq::per_element_width>
				(
					std::forward<LhsRegister_>(lhs_),
					std::forward<RhsRegister_>(rhs_)
				);
			}
			else
			{
				return EmuSIMD::setzero<typename _for_fast_mat_uq::register_type>();
			}
		}
	};

	template<EmuConcepts::EmuFastMatrix ForFastMatrix_>
	struct _basic_div_func
	{
		template<class LhsRegister_, class RhsRegister_>
		[[nodiscard]] constexpr inline decltype(auto) operator()(LhsRegister_&& lhs_, RhsRegister_&& rhs_) const
		{
			using _for_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<ForFastMatrix_>::type;
			if constexpr(!_is_register_out_of_range_type_v<LhsRegister_>)
			{
				if constexpr(!_is_register_out_of_range_type_v<RhsRegister_>)
				{
					return EmuSIMD::div<_for_fast_mat_uq::per_element_width, _for_fast_mat_uq::is_signed>
					(
						std::forward<LhsRegister_>(lhs_),
						std::forward<RhsRegister_>(rhs_)
					);
				}
				else
				{
					// Div is special in that it won't divide non-contained rhs indices, as this is likely a case of "don't want it" rather than "NaN please"
					return std::forward<LhsRegister_>(lhs_);
				}
			}
			else
			{
				return EmuSIMD::setzero<typename _for_fast_mat_uq::register_type>();
			}
		}
	};

	template<EmuConcepts::EmuFastMatrix ForFastMatrix_>
	struct _basic_mod_func
	{
		template<class LhsRegister_, class RhsRegister_>
		[[nodiscard]] constexpr inline decltype(auto) operator()(LhsRegister_&& lhs_, RhsRegister_&& rhs_) const
		{
			using _for_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<ForFastMatrix_>::type;
			if constexpr(!_is_register_out_of_range_type_v<LhsRegister_>)
			{
				if constexpr(!_is_register_out_of_range_type_v<RhsRegister_>)
				{
					return EmuSIMD::mod<_for_fast_mat_uq::per_element_width, _for_fast_mat_uq::is_signed>
					(
						std::forward<LhsRegister_>(lhs_),
						std::forward<RhsRegister_>(rhs_)
					);
				}
				else
				{
					// Mod is special in that it won't divide non-contained rhs indices, as this is likely a case of "don't want it" rather than "NaN please"
					return std::forward<LhsRegister_>(lhs_);
				}
			}
			else
			{
				return EmuSIMD::setzero<typename _for_fast_mat_uq::register_type>();
			}
		}
	};

	template<EmuConcepts::EmuFastMatrix ForFastMatrix_>
	struct _basic_fmadd_func
	{
		template<class LhsRegister_, class RhsRegister_, class ToAddRegister_>
		[[nodiscard]] constexpr inline decltype(auto) operator()(LhsRegister_&& lhs_, RhsRegister_&& rhs_, ToAddRegister_&& to_add_) const
		{
			using _for_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<ForFastMatrix_>::type;
			if constexpr (!_is_register_out_of_range_type_v<LhsRegister_> && !_is_register_out_of_range_type_v<RhsRegister_>)
			{
				if constexpr (!_is_register_out_of_range_type_v<ToAddRegister_>)
				{
					return EmuSIMD::fmadd<_for_fast_mat_uq::per_element_width>
					(
						std::forward<LhsRegister_>(lhs_),
						std::forward<RhsRegister_>(rhs_),
						std::forward<ToAddRegister_>(to_add_)
					);
				}
				else
				{
					return EmuSIMD::mul_all<_for_fast_mat_uq::per_element_width>
					(
						std::forward<LhsRegister_>(lhs_),
						std::forward<RhsRegister_>(rhs_)
					);
				}
			}
			else
			{
				if constexpr (!_is_register_out_of_range_type_v<ToAddRegister_>)
				{
					return std::forward<ToAddRegister_>(to_add_);
				}
				else
				{
					return EmuSIMD::setzero<typename _for_fast_mat_uq::register_type>();
				}
			}
		}
	};

	template<EmuConcepts::EmuFastMatrix ForFastMatrix_>
	struct _basic_fmsub_func
	{
		template<class LhsRegister_, class RhsRegister_, class ToSubRegister_>
		[[nodiscard]] constexpr inline decltype(auto) operator()(LhsRegister_&& lhs_, RhsRegister_&& rhs_, ToSubRegister_&& to_sub_) const
		{
			using _for_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<ForFastMatrix_>::type;
			if constexpr (!_is_register_out_of_range_type_v<LhsRegister_> && !_is_register_out_of_range_type_v<RhsRegister_>)
			{
				if constexpr (!_is_register_out_of_range_type_v<ToSubRegister_>)
				{
					return EmuSIMD::fmsub<_for_fast_mat_uq::per_element_width>
					(
						std::forward<LhsRegister_>(lhs_),
						std::forward<RhsRegister_>(rhs_),
						std::forward<ToSubRegister_>(to_sub_)
					);
				}
				else
				{
					return EmuSIMD::mul_all<_for_fast_mat_uq::per_element_width>
					(
						std::forward<LhsRegister_>(lhs_),
						std::forward<RhsRegister_>(rhs_)
					);
				}
			}
			else
			{
				if constexpr (!_is_register_out_of_range_type_v<ToSubRegister_>)
				{
					return EmuSIMD::negate<_for_fast_mat_uq::per_element_width>(std::forward<ToSubRegister_>(to_sub_));
				}
				else
				{
					return EmuSIMD::setzero<typename _for_fast_mat_uq::register_type>();
				}
			}
		}
	};
}

#endif
