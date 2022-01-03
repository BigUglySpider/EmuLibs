#ifndef EMU_MATH_NEW_VECTOR_SPECIAL_OPERATIONS_UNDERLYING_H_INC_
#define EMU_MATH_NEW_VECTOR_SPECIAL_OPERATIONS_UNDERLYING_H_INC_ 1

#include "_vector_tmp.h"
#include "_vector_get_underlying.h"
#include "_vector_mutation_underlying.h"
#include "../../../../../EmuCore/Functors/Arithmetic.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuMath::Helpers::_vector_underlying
{
	template<class A_, class B_, typename Out_>
	struct _func_vector_dot
	{
		using _do_multiply = EmuCore::do_multiply<A_, B_>;
		using _mul_result = std::invoke_result_t<_do_multiply, const A_&, const B_&>;
		using _do_add = EmuCore::do_add<Out_, _mul_result>;
		using _add_result = std::invoke_result_t<_do_add, Out_&, _mul_result>;

		constexpr _func_vector_dot() : dot_product(), _add(), _mul()
		{
		}

		constexpr inline void operator()(const A_& a_, const B_& b_)
		{
			if constexpr (std::is_assignable_v<Out_, _add_result>)
			{
				dot_product = _add(dot_product, _mul(a_, b_));
			}
			else if constexpr (EmuCore::TMP::is_static_castable_v<_add_result, Out_>)
			{
				dot_product = static_cast<Out_>(_add(dot_product, _mul(a_, b_)));
			}
			else if constexpr (std::is_constructible_v<Out_, _add_result>)
			{
				dot_product = Out_(_add(dot_product, _mul(a_, b_)));
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Out_>(),
					"Attempted to calculate the dot product of two EmuMath Vectors, but the provided Out_ type cannot be assigned to, converted-to, or constructed-from the result of an index iteration."
				);
			}
		}

		Out_ dot_product;

	private:
		_do_add _add;
		_do_multiply _mul;
	};

	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Out_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline Out_ _vector_dot(const EmuMath::NewVector<SizeA_, TA_>& a_, const EmuMath::NewVector<SizeB_, TB_>& b_)
	{
		if constexpr(BeginIndex_ <= EndIndex_)
		{
			if constexpr (!std::is_reference_v<Out_>)
			{
				// Types for calculation
				using a_value_uq = typename EmuMath::NewVector<SizeA_, TA_>::value_type_uq;
				using b_value_uq = typename EmuMath::NewVector<SizeB_, TB_>::value_type_uq;
				using a_b_fp = EmuCore::TMP::largest_floating_point_t<a_value_uq, b_value_uq, float>;

				using out_uq = EmuCore::TMP::remove_ref_cv_t<Out_>;
				using out_processing = std::conditional_t
				<
					std::is_arithmetic_v<Out_>,
					EmuCore::TMP::first_floating_point_t<out_uq, a_b_fp>,
					out_uq
				>;

				// Calculate dot product
				using Func_ = _func_vector_dot<a_value_uq, b_value_uq, out_processing>;
				Func_ func_ = Func_();
				_vector_mutate_invoke_only<Func_&, BeginIndex_, EndIndex_>(func_, a_, b_);

				// Convert processed dot to Out_
				if constexpr (std::is_constructible_v<Out_, out_processing&&>)
				{
					return Out_(std::move(func_.dot_product));
				}
				else if constexpr (EmuCore::TMP::is_static_castable_v<out_processing&&, Out_>)
				{
					return static_cast<Out_>(std::move(func_.dot_product));
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Out_>(),
						"Attempted to calculate the dot product of two EmuMath Vectors, but the provided Out_ type cannot be created from the processed result."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Out_>(),
					"Attempted to calculate the dot product of two EmuMath Vectors, but the provided Out_ type is a reference; as this will result in a dangling reference, such behaviour is prohibited."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Out_>(),
				"Attempted to calculate the dot product of two EmuMath Vectors, but the provided BeginIndex_ is greater than the provided EndIndex_."
			);
		}
	}

	template<typename Out_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline Out_ _vector_dot(const EmuMath::NewVector<SizeA_, TA_>& a_, const EmuMath::NewVector<SizeB_, TB_>& b_)
	{
		return _vector_dot<0, (SizeA_ <= SizeB_) ? SizeA_ : SizeB_, Out_>(a_, b_);
	}
}

#endif
