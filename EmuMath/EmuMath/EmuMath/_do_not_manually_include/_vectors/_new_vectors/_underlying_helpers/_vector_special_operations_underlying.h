#ifndef EMU_MATH_NEW_VECTOR_SPECIAL_OPERATIONS_UNDERLYING_H_INC_
#define EMU_MATH_NEW_VECTOR_SPECIAL_OPERATIONS_UNDERLYING_H_INC_ 1

#include "_vector_tmp.h"
#include "_vector_get_underlying.h"
#include "_vector_mutation_underlying.h"
#include "../../../../../EmuCore/Functors/Arithmetic.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuMath::Helpers::_vector_underlying
{
#pragma region HELPER_FUNCTORS
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

	template<class Mag_>
	struct _vector_norm_element
	{
	private:
		// Types used as dummy args to choose a constructor which initialises mag as the passed arg, or the reciprocal of said arg
		struct _dummy_arg_for_reciprocal {};
		struct _dummy_arg_for_division {};

		static constexpr bool _uses_reciprocal_mult = std::is_floating_point_v<Mag_>;
		using _dummy_construction_arg = std::conditional_t<_uses_reciprocal_mult, _dummy_arg_for_reciprocal, _dummy_arg_for_division>;

	public:
		_vector_norm_element() = delete;
		template<typename MagArg_>
		constexpr _vector_norm_element(MagArg_&& mag_) : 
			_vector_norm_element(std::forward<MagArg_>(mag_), _dummy_construction_arg())
		{
		}

		template<typename In_>
		[[nodiscard]] constexpr inline auto operator()(const In_& in_value_) const
		{
			if constexpr (_uses_reciprocal_mult)
			{
				return EmuCore::do_multiply<In_, Mag_>()(in_value_, _mag);
			}
			else
			{
				return EmuCore::do_divide<In_, Mag_>()(in_value_, _mag);
			}
		}

	private:
		template<typename MagArg_>
		constexpr _vector_norm_element(MagArg_&& mag_, _dummy_arg_for_reciprocal dummy_) :
			_mag(EmuCore::do_divide<Mag_, MagArg_>()(Mag_(1), std::forward<MagArg_>(mag_)))
		{
		}
		template<typename MagArg_>
		constexpr _vector_norm_element(MagArg_&& mag_, _dummy_arg_for_division dummy_) :
			_mag(std::forward<MagArg_>(mag_))
		{
		}

		const Mag_ _mag;
	};

	template<bool OutputRads_>
	struct _conditional_rad_converter
	{
		constexpr _conditional_rad_converter()
		{
		}

		template<typename Rads_>
		[[nodiscard]] constexpr inline auto operator()(const Rads_& rads_) const
		{
			if constexpr (OutputRads_)
			{
				return rads_;
			}
			else
			{
				if constexpr (std::is_invocable_v<EmuCore::do_rads_to_degs<Rads_>, const Rads_&>)
				{
					return EmuCore::do_rads_to_degs<Rads_>()(rads_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Rads_>(),
						"Attempted to convert from radians to degrees for an EmuMath Vector operation, but the provided input Rads_ type cannot be used to invoke a `do_rads_to_degs<Rads_>` instance."
					);
				}
			}
		}
	};
#pragma endregion

#pragma region TYPE_HELPERS
	template<std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_, typename Out_>
	struct _types_vector_dot
	{
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
	};
#pragma endregion

	// DOT
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

	// SQUARE MAG
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Out_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ _vector_square_mag(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_dot<BeginIndex_, EndIndex_, Out_>(vector_, vector_);
	}
	template<typename Out_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ _vector_square_mag(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_dot<Out_>(vector_, vector_);
	}

	// MAG
	template<class Sqrt_, std::size_t BeginIndex_, std::size_t EndIndex_, typename Out_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ _vector_mag(Sqrt_ sqrt_, const EmuMath::NewVector<Size_, T_>& vector_)
	{
		using out_processing = typename _types_vector_dot<Size_, T_, Size_, T_, Out_>::out_processing;
		if constexpr (std::is_invocable_v<Sqrt_&, out_processing>)
		{
			using sqrt_result = std::invoke_result_t<Sqrt_, out_processing>;
			if constexpr (std::is_constructible_v<Out_, sqrt_result>)
			{
				return Out_(Sqrt_()(_vector_square_mag<BeginIndex_, EndIndex_, out_processing>(vector_)));
			}
			else if constexpr (EmuCore::TMP::is_static_castable_v<sqrt_result, Out_>)
			{
				return static_cast<Out_>(Sqrt_()(_vector_square_mag<BeginIndex_, EndIndex_, out_processing>(vector_)));
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Out_>(),
					"Attempted to calculate the magnitude of an EmuMath Vector, but the result of the invoked Sqrt_ func cannot be used to construct or convert-to the desired Out_ type."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Out_>(),
				"Attempted to calculate the magnitude of an EmuMath Vector, but the provided Sqrt_ func cannot be invoked with the determined processing type."
			);
		}
	}
	template<template<class> class SqrtTemplate_, std::size_t BeginIndex_, std::size_t EndIndex_, typename Out_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ _vector_mag(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		using out_processing = typename _types_vector_dot<Size_, T_, Size_, T_, Out_>::out_processing;
		using Sqrt_ = SqrtTemplate_<out_processing>;
		return _vector_mag<Sqrt_, BeginIndex_, EndIndex_, Out_>(Sqrt_(), vector_);
	}

	template<class Sqrt_, typename Out_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ _vector_mag(Sqrt_ sqrt_, const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_mag<Sqrt_&, 0, EmuMath::NewVector<Size_, T_>::size, Out_>(sqrt_, vector_);
	}
	template<template<class> class SqrtTemplate_, typename Out_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ _vector_mag(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_mag<SqrtTemplate_, 0, EmuMath::NewVector<Size_, T_>::size, Out_>(vector_);
	}

	// NORMALISE W/ RETURNED OUT
	template<class Sqrt_, std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> _vector_normalise(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using out_processing = typename _types_vector_dot<InSize_, InT_, InSize_, InT_, OutT_>::out_processing;
		using norm_func = _vector_norm_element<out_processing>;
		return _vector_partial_mutation_copy_return_result<OutSize_, OutT_, norm_func, const EmuMath::NewVector<InSize_, InT_>&, BeginIndex_, EndIndex_, BeginIndex_>
		(
			norm_func(_vector_mag<Sqrt_, out_processing>(in_vector_)),
			in_vector_,
			in_vector_
		);
	}
	template<template<class...> class SqrtTemplate_, std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> _vector_normalise(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using out_processing = typename _types_vector_dot<InSize_, InT_, InSize_, InT_, OutT_>::out_processing;
		using norm_func = _vector_norm_element<out_processing>;
		return _vector_partial_mutation_copy_return_result<OutSize_, OutT_, norm_func, const EmuMath::NewVector<InSize_, InT_>&, BeginIndex_, EndIndex_, BeginIndex_>
		(
			norm_func(_vector_mag<SqrtTemplate_, out_processing>(in_vector_)),
			in_vector_,
			in_vector_
		);
	}

	template<class Sqrt_, std::size_t OutSize_, typename OutT_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> _vector_normalise(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using out_processing = typename _types_vector_dot<InSize_, InT_, InSize_, InT_, OutT_>::out_processing;
		using norm_func = _vector_norm_element<out_processing>;
		return _vector_partial_mutation_copy_return_result<OutSize_, OutT_, norm_func, const EmuMath::NewVector<InSize_, InT_>&, 0, OutSize_, 0>
		(
			norm_func(_vector_mag<Sqrt_, out_processing>(in_vector_)),
			in_vector_,
			in_vector_
		);
	}
	template<template<class...> class SqrtTemplate_, std::size_t OutSize_, typename OutT_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> _vector_normalise(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using out_processing = typename _types_vector_dot<InSize_, InT_, InSize_, InT_, OutT_>::out_processing;
		using norm_func = _vector_norm_element<out_processing>;
		return _vector_partial_mutation_copy_return_result<OutSize_, OutT_, norm_func, const EmuMath::NewVector<InSize_, InT_>&, 0, OutSize_, 0>
		(
			norm_func(_vector_mag<SqrtTemplate_, out_processing>(in_vector_)),
			in_vector_,
			in_vector_
		);
	}

	// NORMALISE W/ REF OUT
	template<class Sqrt_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_, typename InT_, std::size_t InSize_>
	constexpr inline void _vector_normalise(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using out_processing = typename _types_vector_dot<InSize_, InT_, InSize_, InT_, OutT_>::out_processing;
		using norm_func = _vector_norm_element<out_processing>;
		_vector_partial_mutation_copy<norm_func, EmuMath::NewVector<OutSize_, OutT_>, const EmuMath::NewVector<InSize_, InT_>&, 0, OutSize_, 0>
		(
			norm_func(_vector_mag<Sqrt_, out_processing>(in_vector_)),
			out_vector_,
			in_vector_,
			in_vector_
		);
	}
	template<template<class...> class SqrtTemplate_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_, typename InT_, std::size_t InSize_>
	constexpr inline void _vector_normalise(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using out_processing = typename _types_vector_dot<InSize_, InT_, InSize_, InT_, OutT_>::out_processing;
		using norm_func = _vector_norm_element<out_processing>;
		_vector_partial_mutation_copy<norm_func, EmuMath::NewVector<OutSize_, OutT_>, const EmuMath::NewVector<InSize_, InT_>&, 0, OutSize_, 0>
		(
			norm_func(_vector_mag<SqrtTemplate_, out_processing>(in_vector_)),
			out_vector_,
			in_vector_,
			in_vector_
		);
	}

	template<class Sqrt_, std::size_t OutSize_, typename OutT_, typename InT_, std::size_t InSize_>
	constexpr inline void _vector_normalise(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using out_processing = typename _types_vector_dot<InSize_, InT_, InSize_, InT_, OutT_>::out_processing;
		using norm_func = _vector_norm_element<out_processing>;
		_vector_partial_mutation_copy<norm_func, EmuMath::NewVector<OutSize_, OutT_>, const EmuMath::NewVector<InSize_, InT_>&, 0, OutSize_, 0>
		(
			norm_func(_vector_mag<Sqrt_, out_processing>(in_vector_)),
			out_vector_,
			in_vector_,
			in_vector_
		);
	}
	template<template<class...> class SqrtTemplate_, std::size_t OutSize_, typename OutT_, typename InT_, std::size_t InSize_>
	constexpr inline void _vector_normalise(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using out_processing = typename _types_vector_dot<InSize_, InT_, InSize_, InT_, OutT_>::out_processing;
		using norm_func = _vector_norm_element<out_processing>;
		_vector_partial_mutation_copy<norm_func, EmuMath::NewVector<OutSize_, OutT_>, const EmuMath::NewVector<InSize_, InT_>&, 0, OutSize_, 0>
		(
			norm_func(_vector_mag<SqrtTemplate_, out_processing>(in_vector_)),
			out_vector_,
			in_vector_,
			in_vector_
		);
	}

	// ANGLES
	template<template<class> class SqrtTemplate_, class Out_, bool Radians_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline Out_ _vector_angle_cos(const EmuMath::NewVector<SizeA_, TA_>& a_, const EmuMath::NewVector<SizeB_, TB_>& b_)
	{
		using calc_type = typename _types_vector_dot<SizeA_, TA_, SizeB_, TB_, Out_>::out_processing;
		using mul_ = EmuCore::do_multiply<calc_type, calc_type>;
		using unit_converter = _conditional_rad_converter<Radians_>;

		if constexpr (std::is_invocable_v<mul_, calc_type, calc_type>)
		{
			using mul_result = std::invoke_result_t<mul_, calc_type, calc_type>;
			using sqrt_ = SqrtTemplate_<mul_result>;
			if constexpr (std::is_invocable_v<sqrt_, mul_result>)
			{
				using sqrt_result = std::invoke_result_t<sqrt_, mul_result>;
				using div_ = EmuCore::do_divide<calc_type, sqrt_result>;
				if constexpr (std::is_invocable_v<div_, calc_type, sqrt_result>)
				{
					using div_result = std::invoke_result_t<div_, calc_type, sqrt_result>;
					using rad_conversion_result = std::invoke_result_t<unit_converter, div_result>;

					if constexpr (std::is_constructible_v<Out_, rad_conversion_result>)
					{
						return Out_
						(
							unit_converter()
							(
								div_()
								(
									_vector_dot<calc_type>(a_, b_),
									sqrt_()(mul_()(_vector_square_mag<calc_type>(a_), _vector_square_mag<calc_type>(b_)))
								)
							)
						);
					}
					else if constexpr (std::is_convertible_v<Out_, rad_conversion_result>)
					{
						return static_cast<Out_>
						(
							unit_converter()
							(
								div_()
								(
									_vector_dot<calc_type>(a_, b_),
									sqrt_()(mul_()(_vector_square_mag<calc_type>(a_), _vector_square_mag<calc_type>(b_)))
								)
							)
						);
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<Out_>(),
							"Attempted to calculate the cosine of the angle between two EmuMath Vectors, but the provided Out_ type cannot be formed from the type resulting from calculations."
						);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Out_>(),
						"Attempted to calculate the cosine of the angle between two EmuMath Vectors, but a division operation could not successfully be invoked."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Out_>(),
					"Attempted to calculate the cosine of the angle between two EmuMath Vectors, but a square-root operation could not successfully be invoked."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Out_>(),
				"Attempted to calculate the cosine of the angle between two EmuMath Vectors, but a multiplication operation could not successfully be invoked."
			);
		}
	}

	template<template<class> class SqrtTempate_, class Acos_, class Out_, bool Radians_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline Out_ _vector_angle(Acos_ acos_, const EmuMath::NewVector<SizeA_, TA_>& a_, const EmuMath::NewVector<SizeB_, TB_>& b_)
	{
		using calc_type = typename _types_vector_dot<SizeA_, TA_, SizeB_, TB_, Out_>::out_processing;
		using unit_converter = _conditional_rad_converter<Radians_>;
		if constexpr (std::is_invocable_v<Acos_&, calc_type>)
		{
			using acos_result = std::invoke_result_t<Acos_&, calc_type>;
			using unit_conversion_result = std::invoke_result_t<unit_converter, acos_result>;
			
			if constexpr (std::is_constructible_v<Out_, unit_conversion_result>)
			{
				return Out_(unit_converter()(acos_(_vector_angle_cos<SqrtTempate_, calc_type, true>(a_, b_))));
			}
			else if constexpr (EmuCore::TMP::is_static_castable_v<unit_conversion_result, Out_>)
			{
				return static_cast<Out_>(unit_converter()(acos_(_vector_angle_cos<SqrtTempate_, calc_type, true>(a_, b_))));
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Out_>(),
					"Attempted to calculate the angle between two EmuMath Vectors, but the provided Out_ type cannot be invoked with the result of invoking the provided Acos_ functor."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Out_>(),
				"Attempted to calculate the angle between two EmuMath Vectors, but the provided Acos_ functor cannot be invoked with the result of finding the angle cosine."
			);
		}
	}

	template<template<class> class SqrtTemplate_, template<class> class AcosTemplate_, class Out_, bool Radians_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline Out_ _vector_angle(const EmuMath::NewVector<SizeA_, TA_>& a_, const EmuMath::NewVector<SizeB_, TB_>& b_)
	{
		using Acos_ = AcosTemplate_<typename _types_vector_dot<SizeA_, TA_, SizeB_, TB_, Out_>::out_processing>;
		return _vector_angle<SqrtTemplate_, Acos_, Out_, Radians_>(Acos_(), a_, b_);
	}
}

#endif
