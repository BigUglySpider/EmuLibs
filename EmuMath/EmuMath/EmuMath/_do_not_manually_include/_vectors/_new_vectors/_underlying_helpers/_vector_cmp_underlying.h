#ifndef EMU_MATH_VECTOR_CMP_UNDERLYING_H_INC_
#define EMU_MATH_VECTOR_CMP_UNDERLYING_H_INC_ 1

#include "_vector_tmp.h"
#include "_vector_get_underlying.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuMath::Helpers::_vector_underlying
{
	template<bool NoCmpReturn_, std::size_t Index_, std::size_t EndIndex_, class Cmp_, class Joiner_, std::size_t LhsSize_, typename LhsT_, class RhsVector_>
	[[nodiscard]] constexpr inline bool _vector_cmp_rhs_vector(Cmp_& cmp_, Joiner_& joiner_, const EmuMath::NewVector<LhsSize_, LhsT_>& lhs_, RhsVector_&& rhs_)
	{
		if constexpr (Index_ < EndIndex_)
		{
			using lhs_get_result = decltype(_vector_get_theoretical<Index_>(lhs_));
			using rhs_get_result = decltype(_vector_get_theoretical<Index_>(std::forward<RhsVector_>(rhs_)));

			if constexpr (std::is_invocable_r_v<bool, Cmp_&, lhs_get_result, rhs_get_result>)
			{
				// Performs a logical operation defined by joiner_ using the result of this cmp and the next cmp
				// --- Relies on short-circuiting to optimise runtime results when a statement is guaranteed true/false
				return joiner_
				(
					cmp_(_vector_get_theoretical<Index_>(lhs_), _vector_get_theoretical<Index_>(std::forward<RhsVector_>(rhs_))),
					_vector_cmp_rhs_vector<NoCmpReturn_, Index_ + 1, EndIndex_, Cmp_, Joiner_, LhsSize_, LhsT_, RhsVector_>
					(
						cmp_,
						joiner_,
						lhs_,
						std::forward<RhsVector_>(rhs_)
					)
				);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Cmp_>(),
					"Attempted to perform a comparison of two EmuMath Vectors, but the provided comparison functor could not be invoked with a boolean return value using the result of getting at least one index within the lhs and rhs Vectors used as arguments."
				);
			}
		}
		else
		{
			return NoCmpReturn_;
		}
	}

	template<bool NoCmpReturn_, std::size_t Index_, std::size_t EndIndex_, class Cmp_, class Joiner_, std::size_t LhsSize_, typename LhsT_, class RhsScalar_>
	[[nodiscard]] constexpr inline bool _vector_cmp_rhs_scalar
	(
		Cmp_& cmp_,
		Joiner_& joiner_,
		const EmuMath::NewVector<LhsSize_, LhsT_>& lhs_,
		std::add_lvalue_reference_t<RhsScalar_> rhs_
	)
	{
		if constexpr (Index_ < EndIndex_)
		{
			using lhs_get_result = decltype(_vector_get_theoretical<Index_>(lhs_));
			if constexpr (std::is_invocable_r_v<bool, Cmp_&, lhs_get_result, std::add_lvalue_reference_t<RhsScalar_>>)
			{
				// Performs a logical operation defined by joiner_ using the result of this cmp and the next cmp
				// --- Relies on short-circuiting to optimise runtime results when a statement is guaranteed true/false
				return joiner_
				(
					cmp_(_vector_get_theoretical<Index_>(lhs_), rhs_),
					_vector_cmp_rhs_scalar<NoCmpReturn_, Index_ + 1, EndIndex_, Cmp_, Joiner_, LhsSize_, LhsT_, RhsScalar_>
					(
						cmp_,
						joiner_,
						lhs_,
						rhs_
					)
				);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Cmp_>(),
					"Attempted to perform a comparison of an EmuMath Vector and a scalar rhs argument, but the provided comparison functor could not be invoked with a boolean return value, with the result of getting at least one index of the lhs Vector alongside the rhs argument used as arguments."
				);
			}
		}
		else
		{
			return NoCmpReturn_;
		}
	}

	template<bool NoCmpReturn_, std::size_t BeginIndex_, std::size_t EndIndex_, class Cmp_, class Joiner_, std::size_t LhsSize_, typename LhsT_, class Rhs_>
	[[nodiscard]] constexpr inline bool _vector_cmp(Cmp_ cmp_, Joiner_ joiner_, const EmuMath::NewVector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_new_vector_v<Rhs_>)
		{
			return _vector_cmp_rhs_vector<NoCmpReturn_, BeginIndex_, EndIndex_, Cmp_, Joiner_, LhsSize_, LhsT_, Rhs_>
			(
				cmp_,
				joiner_,
				lhs_vector_,
				std::forward<Rhs_>(rhs_)
			);
		}
		else
		{
			return _vector_cmp_rhs_scalar<NoCmpReturn_, BeginIndex_, EndIndex_, Cmp_, Joiner_, LhsSize_, LhsT_, Rhs_>
			(
				cmp_,
				joiner_,
				lhs_vector_,
				EmuCore::TMP::lval_ref_cast<Rhs_>(rhs_)
			);
		}
	}

	template<bool NoCmpReturn_, std::size_t BeginIndex_, std::size_t EndIndex_, template<class...> class CmpTemplate_, class Joiner_, std::size_t LhsSize_, typename LhsT_, class Rhs_>
	[[nodiscard]] constexpr inline bool _vector_cmp(Joiner_ joiner_, const EmuMath::NewVector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		using rhs_value_uq = EmuMath::TMP::emu_vector_value_type_uq<Rhs_>;
		if constexpr (EmuCore::TMP::valid_template_args_v<CmpTemplate_, lhs_value_uq, rhs_value_uq>)
		{
			using Cmp_ = CmpTemplate_<lhs_value_uq, rhs_value_uq>;
			Cmp_ cmp_ = Cmp_();
			return _vector_cmp<NoCmpReturn_, BeginIndex_, EndIndex_, Cmp_&, std::add_lvalue_reference_t<Joiner_>, LhsSize_, LhsT_, Rhs_>
			(
				joiner_,
				lhs_vector_,
				std::forward<Rhs_>(rhs_)
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Rhs_>(),
				"Attempted to perform a comparison with an EmuMath Vector, but the provided comparison template cannot be instantiated with the value_type_uq of the lhs_vector_ and rhs_."
			);
		}
	}

	template<bool NoCmpReturn_, bool IncludeNonContained_, class Cmp_, class Joiner_, std::size_t LhsSize_, typename LhsT_, class Rhs_>
	[[nodiscard]] constexpr inline bool _vector_cmp(Cmp_ cmp_, Joiner_ joiner_, const EmuMath::NewVector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		constexpr std::size_t lhs_size_ = EmuMath::NewVector<LhsSize_, LhsT_>::size;
		if constexpr (EmuMath::TMP::is_emu_new_vector_v<Rhs_>)
		{
			constexpr std::size_t rhs_size_ = EmuMath::NewVector<LhsSize_, LhsT_>::size;
			constexpr std::size_t smallest_size_ = (lhs_size_ <= rhs_size_) ? lhs_size_ : rhs_size_;
			constexpr std::size_t largest_size_ = (lhs_size_ >= rhs_size_) ? lhs_size_ : rhs_size_;
			constexpr std::size_t end_index_ = IncludeNonContained_ ? largest_size_ : smallest_size_;
			
			// 0:smallest if we don't want to include non-contained indices, otherwise cover all indices even if not contained
			return _vector_cmp<NoCmpReturn_, 0, end_index_, std::add_lvalue_reference_t<Cmp_>, std::add_lvalue_reference_t<Joiner_>>
			(
				cmp_,
				joiner_,
				lhs_vector_,
				std::forward<Rhs_>(rhs_)
			);
		}
		else
		{
			// Only lhs is a Vector, so we're always covering the full range of lhs
			return _vector_cmp<NoCmpReturn_, 0, lhs_size_, std::add_lvalue_reference_t<Cmp_>, std::add_lvalue_reference_t<Joiner_>>
			(
				cmp_,
				joiner_,
				lhs_vector_,
				std::forward<Rhs_>(rhs_)
			);
		}
	}

	template<bool NoCmpReturn_, bool IncludeNonContained_, template<class...> class CmpTemplate_, class Joiner_, std::size_t LhsSize_, typename LhsT_, class Rhs_>
	[[nodiscard]] constexpr inline bool _vector_cmp(Joiner_ joiner_, const EmuMath::NewVector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		using rhs_value_uq = EmuMath::TMP::emu_vector_value_type_uq<Rhs_>;
		if constexpr (EmuCore::TMP::valid_template_args_v<CmpTemplate_, lhs_value_uq, rhs_value_uq>)
		{
			using Cmp_ = CmpTemplate_<lhs_value_uq, rhs_value_uq>;
			Cmp_ cmp_ = Cmp_();
			return _vector_cmp<NoCmpReturn_, IncludeNonContained_, Cmp_&, std::add_lvalue_reference_t<Joiner_>>
			(
				cmp_,
				joiner_,
				lhs_vector_,
				std::forward<Rhs_>(rhs_)
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Rhs_>(),
				"Attempted to perform a comparison with an EmuMath Vector, but the provided comparison template cannot be instantiated with the value_type_uq of the lhs_vector_ and rhs_."
			);
		}
	}
}

#endif
