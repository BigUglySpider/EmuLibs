#ifndef EMU_MATH_VECTOR_MISC_ARITHMETIC_UNDERLYING_H_INC_
#define EMU_MATH_VECTOR_MISC_ARITHMETIC_UNDERLYING_H_INC_ 1

#include "_vector_tmp.h"
#include "_vector_get_underlying.h"
#include "_vector_mutation_underlying.h"
#include "../../../../../EmuCore/Functors/Comparators.h"
#include "../../../../../EmuCore/TMPHelpers/OperatorChecks.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuMath::Helpers::_vector_underlying
{
	// Functor for easy updating of an output vector when performing an internal comparison within a vector
	// --- If Cmp(some_input_val, out_val) is true, out_val is set to some_input_val.
	template<std::size_t Size_, typename T_, template<class...> class CmpTemplate_>
	struct _vector_cmp_self_update_if_true
	{
		using value_uq = typename EmuMath::NewVector<Size_, T_>::value_type_uq;
		using cmp_func = CmpTemplate_<value_uq, value_uq>;

		constexpr _vector_cmp_self_update_if_true() : out_val()
		{
		}
		constexpr _vector_cmp_self_update_if_true(value_uq&& start_value_) : out_val(std::forward<value_uq>(start_value_))
		{
		}

		constexpr inline void operator()(const value_uq& val_)
		{
			if (cmp_func()(val_, out_val))
			{
				out_val = val_;
			}
		}

		value_uq out_val;
	};

	template<template<class...> class CmpTemplate_, class StartVal_, typename Out_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ _vector_min_or_max(const EmuMath::NewVector<Size_, T_>& in_vector_)
	{
		constexpr std::size_t clamped_end_ = (EndIndex_ <= Size_) ? EndIndex_ : Size_;
		if constexpr (BeginIndex_ <= clamped_end_)
		{
			if constexpr ((clamped_end_ - BeginIndex_) <= 1)
			{
				using get_type = EmuMath::TMP::emu_vector_theoretical_return_t<BeginIndex_, const EmuMath::NewVector<Size_, T_>>;
				if constexpr (std::is_constructible_v<Out_, get_type>)
				{
					return Out_(_vector_get_theoretical<BeginIndex_>(in_vector_));
				}
				else if constexpr (EmuCore::TMP::is_static_castable_v<get_type, Out_>)
				{
					return static_cast<Out_>(_vector_get_theoretical<BeginIndex_>(in_vector_));
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Out_>(),
						"Attempted to find the minimum or maximum value within an EmuMath Vector, but the provided Out_ type cannot be formed from the result of getting the theoretical element at BeginIndex_ within the passed Vector."
					);
				}
			}
			else
			{
				using Func_ = _vector_cmp_self_update_if_true<Size_, T_, CmpTemplate_>;
				Func_ func_ = Func_(StartVal_::get());
				_vector_mutate_invoke_only<Func_&, BeginIndex_, EndIndex_>(func_, in_vector_);

				using moved_out_type = decltype(std::move(func_.out_val));
				if constexpr (std::is_constructible_v<Out_, moved_out_type>)
				{
					return Out_(std::move(func_.out_val));
				}
				else if constexpr (EmuCore::TMP::is_static_castable_v<moved_out_type, Out_>)
				{
					return static_cast<Out_>(std::move(func_.out_val));
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Out_>(),
						"Attempted to find the minimum or maximum value within an EmuMath Vector, but the provided Out_ type cannot be formed from the Vector's value_type_uq."
					);
				}
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Out_>(),
				"Attempted to find the minimum or maximum value within an EmuMath Vector, but the provided BeginIndex_ was greater than the provided EndIndex_"
			);
		}
	}

	template<class Out_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ _vector_min(const EmuMath::NewVector<Size_, T_>& in_vector_)
	{
		using start_value = EmuCore::TMP::highest_value<typename EmuMath::NewVector<Size_, T_>::value_type_uq>;
		return _vector_min_or_max<EmuCore::do_cmp_less, start_value, Out_, BeginIndex_, EndIndex_>(in_vector_);
	}
	template<class Out_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ _vector_min(const EmuMath::NewVector<Size_, T_>& in_vector_)
	{
		return _vector_min<Out_, 0, EmuMath::NewVector<Size_, T_>::size>(in_vector_);
	}

	template<class Out_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ _vector_max(const EmuMath::NewVector<Size_, T_>& in_vector_)
	{
		using start_value = EmuCore::TMP::lowest_value<typename EmuMath::NewVector<Size_, T_>::value_type_uq>;
		return _vector_min_or_max<EmuCore::do_cmp_greater, start_value, Out_, BeginIndex_, EndIndex_>(in_vector_);
	}
	template<class Out_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ _vector_max(const EmuMath::NewVector<Size_, T_>& in_vector_)
	{
		return _vector_max<Out_, 0, EmuMath::NewVector<Size_, T_>::size>(in_vector_);
	}
}

#endif
