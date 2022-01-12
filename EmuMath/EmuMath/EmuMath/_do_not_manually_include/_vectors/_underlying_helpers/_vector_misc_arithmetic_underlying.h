#ifndef EMU_MATH_VECTOR_MISC_ARITHMETIC_UNDERLYING_H_INC_
#define EMU_MATH_VECTOR_MISC_ARITHMETIC_UNDERLYING_H_INC_ 1

#include "_vector_tmp.h"
#include "_vector_get_underlying.h"
#include "_vector_mutation_underlying.h"
#include "../../../../EmuCore/Functors/Comparators.h"
#include "../../../../EmuCore/TMPHelpers/OperatorChecks.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuMath::Helpers::_vector_underlying
{
	// Functor for easy updating of an output vector when performing an internal comparison within a vector
	// --- If Cmp(some_input_val, out_val) is true, out_val is set to some_input_val.
	template<class InVector_, template<class...> class CmpTemplate_ >
	struct _vector_cmp_self_update_if_true
	{
		using value_uq = typename EmuCore::TMP::remove_ref_cv_t<InVector_>::value_type_uq;
		using cmp_func = CmpTemplate_<value_uq, value_uq>;

		constexpr _vector_cmp_self_update_if_true() : out_val()
		{
		}
		constexpr _vector_cmp_self_update_if_true(const value_uq& start_value_) : out_val(start_value_)
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

	template<bool IsConst_, class InVector_, template<class...> class CmpTemplate_>
	struct _vector_cmp_self_update_if_true_ref_output
	{
		using value_uq = typename EmuCore::TMP::remove_ref_cv_t<InVector_>::value_type_uq;
		using value_type_cq = EmuCore::TMP::conditional_const_t<IsConst_, typename EmuCore::TMP::remove_ref_cv_t<InVector_>::value_type>;
		using cmp_func = CmpTemplate_<value_uq, value_uq>;
		using pointer_type = std::add_pointer_t<value_type_cq>;
		using ref_type = std::add_lvalue_reference_t<value_type_cq>;

		// Constructor taking a reference to a starting value to compare against
		// --- The reference must be a named lvalue, as the reference will be used
		constexpr _vector_cmp_self_update_if_true_ref_output(ref_type ref_starting_val_) : p_out(&ref_starting_val_)
		{
		}

		constexpr inline void operator()(ref_type val_)
		{
			if (cmp_func()(val_, *p_out))
			{
				p_out = &val_;
			}
		}

		pointer_type p_out;
	};

	template<template<class...> class CmpTemplate_, typename Out_, std::size_t BeginIndex_, std::size_t EndIndex_, class InVector_>
	[[nodiscard]] constexpr inline Out_ _vector_min_or_max_ref_output(InVector_& in_vector_)
	{
		constexpr std::size_t in_size = InVector_::size;
		if constexpr (in_size != 0)
		{
			constexpr std::size_t clamped_end_ = (EndIndex_ <= in_size) ? EndIndex_ : in_size;
			if constexpr (BeginIndex_ <= clamped_end_)
			{
				if constexpr ((clamped_end_ - BeginIndex_) > 1)
				{
					// Store current index first, and then start mutation defer from Begin_ + 1
					using Func_ = _vector_cmp_self_update_if_true_ref_output<std::is_const_v<InVector_>, InVector_, CmpTemplate_>;
					using ptr_deref_type = decltype(*(std::declval<Func_>().p_out));

					if constexpr (std::is_constructible_v<Out_, ptr_deref_type>)
					{
						Func_ func_ = Func_(_vector_get<BeginIndex_>(in_vector_));
						_vector_mutate_invoke_only<Func_&, BeginIndex_ + 1, EndIndex_>(func_, in_vector_);
						return Out_(*(func_.p_out));
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<InVector_>(),
							"Attempted to retrieve an EmuMath Vector's min/max value with reference output, but the provided Out_ reference cannot be formed from a dereferenced pointer to one of the input Vector's value_types. This may be related to the const-state of the Vector and/or its elements."
						);
					}
				}
				else
				{
					// Only 1 index in range, so just return that directly
					using get_result_type = decltype(_vector_get<BeginIndex_>(in_vector_));
					if constexpr (std::is_constructible_v<Out_, get_result_type>)
					{
						return Out_(_vector_get<BeginIndex_>(in_vector_));
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<InVector_>(),
							"Attempted to retrieve an EmuMath Vector's min/max value with reference output, but the provided Out_ reference cannot be formed from the result of getting a compile-time contained index from the input Vector. This may be related to the const-state of the Vector and/or its elements."
						);
					}
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<InVector_>(),
					"Attempted to retrieve an EmuMath Vector's min/max value with reference output, but the provided index range could not reference any values after clamping."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<InVector_>(),
				"Attempted to retrieve a zero-sized EmuMath Vector's min/max value with reference output. A zero-sized Vector does not contain any values that may be referenced."
			);
		}
	}

	template<template<class...> class CmpTemplate_, typename Out_, std::size_t BeginIndex_, std::size_t EndIndex_, class InVector_>
	[[nodiscard]] constexpr inline Out_ _vector_min_or_max(InVector_& in_vector_)
	{
		if constexpr (std::is_reference_v<Out_>)
		{
			// Defer elsewhere for ref output
			return _vector_min_or_max_ref_output<CmpTemplate_, Out_, BeginIndex_, EndIndex_, InVector_>(in_vector_);
		}
		else
		{
			// Function body for value output
			constexpr std::size_t in_size = InVector_::size;
			constexpr std::size_t clamped_end_ = (EndIndex_ <= in_size) ? EndIndex_ : in_size;
			if constexpr (BeginIndex_ <= clamped_end_)
			{
				if constexpr ((clamped_end_ - BeginIndex_) <= 1)
				{
					// Output theoretical BeginIndex_ since that is the only value covered in this range
					using get_type = EmuMath::TMP::emu_vector_theoretical_return_t<BeginIndex_, std::remove_reference_t<std::remove_volatile_t<InVector_>>>;
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
					// Store BeginIndex_ and start comparisons from BeginIndex_ + 1
					using Func_ = _vector_cmp_self_update_if_true<InVector_, CmpTemplate_>;
					Func_ func_ = Func_(_vector_get<BeginIndex_>(in_vector_));
					_vector_mutate_invoke_only<Func_&, BeginIndex_ + 1, EndIndex_>(func_, in_vector_);

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
	}

	template<class Out_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ _vector_min(const EmuMath::Vector<Size_, T_>& in_vector_)
	{
		return _vector_min_or_max<EmuCore::do_cmp_less, Out_, BeginIndex_, EndIndex_, const EmuMath::Vector<Size_, T_>>(in_vector_);
	}
	template<class Out_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ _vector_min(const EmuMath::Vector<Size_, T_>& in_vector_)
	{
		return _vector_min_or_max<EmuCore::do_cmp_less, Out_, 0, EmuMath::Vector<Size_, T_>::size, const EmuMath::Vector<Size_, T_>>(in_vector_);
	}

	template<class Out_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ _vector_min(EmuMath::Vector<Size_, T_>& in_vector_)
	{
		return _vector_min_or_max<EmuCore::do_cmp_less, Out_, BeginIndex_, EndIndex_, EmuMath::Vector<Size_, T_>>(in_vector_);
	}
	template<class Out_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ _vector_min(EmuMath::Vector<Size_, T_>& in_vector_)
	{
		return _vector_min_or_max<EmuCore::do_cmp_less, Out_, 0, EmuMath::Vector<Size_, T_>::size, EmuMath::Vector<Size_, T_>>(in_vector_);
	}

	template<class Out_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ _vector_max(const EmuMath::Vector<Size_, T_>& in_vector_)
	{
		return _vector_min_or_max<EmuCore::do_cmp_greater, Out_, BeginIndex_, EndIndex_, const EmuMath::Vector<Size_, T_>>(in_vector_);
	}
	template<class Out_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ _vector_max(const EmuMath::Vector<Size_, T_>& in_vector_)
	{
		return _vector_min_or_max<EmuCore::do_cmp_greater, Out_, 0, EmuMath::Vector<Size_, T_>::size, const EmuMath::Vector<Size_, T_>>(in_vector_);
	}

	template<class Out_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ _vector_max(EmuMath::Vector<Size_, T_>& in_vector_)
	{
		return _vector_min_or_max<EmuCore::do_cmp_greater, Out_, BeginIndex_, EndIndex_, EmuMath::Vector<Size_, T_>>(in_vector_);
	}
	template<class Out_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ _vector_max(EmuMath::Vector<Size_, T_>& in_vector_)
	{
		return _vector_min_or_max<EmuCore::do_cmp_greater, Out_, 0, EmuMath::Vector<Size_, T_>::size, EmuMath::Vector<Size_, T_>>(in_vector_);
	}
}

#endif
