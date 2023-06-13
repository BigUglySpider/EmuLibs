#ifndef EMU_MATH_MATRIX_UNDERLYING_MISC_ARITHMETIC_H_INC_
#define EMU_MATH_MATRIX_UNDERLYING_MISC_ARITHMETIC_H_INC_ 1

#include "_matrix_tmp.h"
#include "_matrix_underlying_get.h"
#include "_matrix_underlying_mutate.h"
#include "../../../../EmuCore/Functors/Comparators.h"

namespace EmuMath::Helpers::_matrix_underlying
{
	template<class InMatrix_, template<class...> class CmpTemplate_>
	struct _matrix_cmp_self_update_ptr_if_true
	{
	private:
		using _mat_uq = typename EmuCore::TMP::remove_ref_cv<InMatrix_>::type;
		using _mat_no_ref = std::remove_reference_t<InMatrix_>;

	public:
		using cmp_func_type = CmpTemplate_<typename _mat_uq::value_type_uq>;
		using value_type_cq = typename EmuCore::TMP::conditional_const<std::is_const_v<_mat_no_ref>, typename _mat_uq::value_type>::type;
		static constexpr bool is_valid = true;

		_matrix_cmp_self_update_ptr_if_true() = delete;
		constexpr inline _matrix_cmp_self_update_ptr_if_true(value_type_cq& starter_ref_) : _p_out(&starter_ref_)
		{
		}

		constexpr inline void operator()(value_type_cq& in_)
		{
			if (cmp_func_type()(in_, *_p_out))
			{
				_p_out = &in_;
			}
		}

		template<typename Out_>
		[[nodiscard]] constexpr inline Out_ Result()
		{
			using deref_type = const value_type_cq&;
			if constexpr (EmuCore::TMP::valid_construct_or_cast<Out_, deref_type>())
			{
				return EmuCore::TMP::construct_or_cast<Out_, deref_type>(*_p_out);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Out_>(),
					"Attempted to perform an EmuMath Matrix operation which updates a value when a comparison returns true, but a dereferenced pointer to one of the input Matrix's elements cannot be converted to the desired output type."
				);
			}
		}

	private:
		value_type_cq* _p_out;
	};

	template<class InMatrix_, template<class...> class CmpTemplate_>
	struct _matrix_cmp_self_update_val_if_true
	{
	private:
		using _mat_uq = typename EmuCore::TMP::remove_ref_cv<InMatrix_>::type;
		using _mat_no_ref = std::remove_reference_t<InMatrix_>;

	public:
		using cmp_func_type = CmpTemplate_<typename _mat_uq::value_type_uq>;
		using value_cq = typename EmuCore::TMP::conditional_const<std::is_const_v<_mat_no_ref>, typename _mat_uq::value_type>::type;
		using value_uq = typename _mat_uq::value_type_uq;

		// Two modes of construction, but move is conditionally disabled and is only for non-contained starter indices, so prefer a most-likely "good" execution
		static constexpr bool is_valid = std::is_constructible_v<value_uq, const value_uq&> && std::is_assignable_v<value_uq&, value_cq&>;

		_matrix_cmp_self_update_val_if_true() = delete;

		constexpr inline _matrix_cmp_self_update_val_if_true(value_cq& starter_val_) : _out_val(starter_val_)
		{
		}

		template<typename = std::enable_if_t<std::is_move_constructible_v<value_uq>>>
		constexpr inline _matrix_cmp_self_update_val_if_true(value_uq&& starter_val_) : _out_val(std::forward<value_uq>(starter_val_))
		{
		}

		constexpr inline void operator()(value_cq& in_)
		{
			if constexpr (is_valid)
			{
				if (cmp_func_type()(in_, _out_val))
				{
					_out_val = in_;
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<InMatrix_>(),
					"Attempted to perform an EmuMath Matrix operation which will update a value when a comparison returns true, but the input Matrix's value_type_uq cannot be constructed and/or assigned via a value_type reference with its provided const-qualified state."
				);
			}
		}

		template<typename Out_>
		[[nodiscard]] constexpr inline Out_ Result()
		{
			using move_result = decltype(std::move(_out_val));
			if constexpr (EmuCore::TMP::valid_construct_or_cast<Out_, move_result>())
			{
				return Out_(std::move(_out_val));
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Out_>(),
					"Attempted to perform an EmuMath Matrix operation which updates a value when a comparison returns true, but the input Matrix's value_type_uq cannot be converted to the desired output type."
				);
			}
		}

	private:
		value_uq _out_val;
	};

	template<class InMatrix_, template<class...> class CmpTemplate_, std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_>
	struct _matrix_cmp_self_update_if_true_find_best_fit
	{
	private:
		using _mat_uq = typename EmuCore::TMP::remove_ref_cv<InMatrix_>::type;

		template<class Mat_, bool ValidRange_ = _matrix_index_range_is_valid_and_contained<BeginColumn_, EndColumn_, BeginRow_, EndRow_, InMatrix_>()>
		struct _func_finder
		{
			using type = _matrix_cmp_self_update_val_if_true<InMatrix_, CmpTemplate_>;
		};

		template<class Mat_>
		struct _func_finder<Mat_, true>
		{
			using type = _matrix_cmp_self_update_ptr_if_true<InMatrix_, CmpTemplate_>;
		};

	public:
		using type = typename _func_finder<InMatrix_>::type;
	};

	template<template<class...> class CmpTemplate_, class Out_, std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class Matrix_>
	[[nodiscard]] constexpr inline Out_ _matrix_min_or_max(Matrix_&& matrix_)
	{
		using Func_ = typename _matrix_cmp_self_update_if_true_find_best_fit<Matrix_, CmpTemplate_, BeginColumn_, EndColumn_, BeginRow_, EndRow_>::type;
		if constexpr (_matrix_index_range_is_valid<BeginColumn_, EndColumn_, BeginRow_, EndRow_>())
		{
			if constexpr (Func_::is_valid)
			{
				constexpr bool is_column_major_ = EmuCore::TMP::remove_ref_cv_t<Matrix_>::is_column_major;
				Func_ func_(_matrix_get_theoretical<BeginColumn_, BeginRow_>(EmuCore::TMP::lval_ref_cast<Matrix_>(std::forward<Matrix_>(matrix_))));

				// Prioritise checks executing in correct major order for cache locality
				if constexpr (is_column_major_)
				{
					// Follows the pattern (in a 4x4, 0:4, 0:4 scenario), where 0 = unchecked, 1 = checked, from left to right:
					// 1 0 0 0 | 1 1 1 1 | 1 1 1 1
					// 0 0 0 0 | 0 1 1 1 | 1 1 1 1
					// 0 0 0 0 | 0 1 1 1 | 1 1 1 1
					// 0 0 0 0 | 0 1 1 1 | 1 1 1 1
					if constexpr ((BeginColumn_ + 1) < EndColumn_)
					{
						_matrix_mutate_invoke_only<BeginColumn_ + 1, EndColumn_, BeginRow_, EndRow_, is_column_major_, Func_&>(func_, std::forward<Matrix_>(matrix_));
					}
					if constexpr ((BeginRow_ + 1) < EndRow_)
					{
						_matrix_mutate_invoke_only<BeginColumn_, BeginColumn_ + 1, BeginRow_ + 1, EndRow_, is_column_major_, Func_&>(func_, std::forward<Matrix_>(matrix_));
					}
				}
				else
				{
					// Follows the pattern (in a 4x4, 0:4, 0:4 scenario), where 0 = unchecked, 1 = checked, from left to right:
					// 1 0 0 0 | 1 0 0 0 | 1 1 1 1
					// 0 0 0 0 | 1 1 1 1 | 1 1 1 1
					// 0 0 0 0 | 1 1 1 1 | 1 1 1 1
					// 0 0 0 0 | 1 1 1 1 | 1 1 1 1
					if constexpr ((BeginRow_ + 1) < EndRow_)
					{
						_matrix_mutate_invoke_only<BeginColumn_, EndColumn_, BeginRow_ + 1, EndRow_, is_column_major_, Func_&>(func_, std::forward<Matrix_>(matrix_));
					}
					if constexpr ((BeginColumn_ + 1) < EndColumn_)
					{
						_matrix_mutate_invoke_only<BeginColumn_ + 1, EndColumn_, BeginRow_, BeginRow_ + 1, is_column_major_, Func_&>(func_, std::forward<Matrix_>(matrix_));
					}
				}

				return func_.template Result<Out_>();
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Func_>(),
					"Attempted to perform a Min or Max operation on an EmuMath MAtrix's internal elements, but the determined function to invoke for finding the correct result was in an invalid state. This may be a result of bad construction ability, or if the function uses value_type_uq updates it may be a result of an inability to assign existing values."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Matrix_>(),
				"Attempted to perform a Min or Max operation on an EmuMath Matrix's internal elements, but the provided range was invalid. This will be a result of a End index being less than or equal to its respective Begin index (e.g. EndColumn_ <= BeginColumn_)."
			);
		}
	}
}

#endif
