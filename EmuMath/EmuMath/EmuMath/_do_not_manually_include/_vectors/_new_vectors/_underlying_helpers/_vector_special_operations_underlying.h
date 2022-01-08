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

	template
	<
		template<class...> class SubTemplate_,
		template<class...> class AddAssignTemplate_,
		template<class...> class MulTemplate_,
		std::size_t FromSize_,
		typename FromT_,
		std::size_t ToSize_,
		typename ToT_
	>
	struct _vector_dist_square_calculator
	{
	public:
		using from_vector = EmuMath::NewVector<FromSize_, FromT_>;
		using to_vector = EmuMath::NewVector<ToSize_, ToT_>;
		using from_value = typename from_vector::value_type;
		using to_value = typename to_vector::value_type;
		using from_value_uq = EmuCore::TMP::remove_ref_cv_t<from_value>;
		using to_value_uq = EmuCore::TMP::remove_ref_cv_t<to_value>;

		using sub_instantiator = EmuCore::TMP::safe_template_instantiate<SubTemplate_, to_value_uq, from_value_uq>;
		using Sub_ = typename sub_instantiator::type;
		using sub_result_checker = EmuCore::TMP::safe_invoke_result<Sub_, const to_value&, const from_value&>;
		using sub_result = typename sub_result_checker::type;
		using sub_result_uq = EmuCore::TMP::remove_ref_cv_t<sub_result>;

		using mul_instantiator = EmuCore::TMP::safe_template_instantiate<MulTemplate_, sub_result_uq, sub_result_uq>;
		using Mul_ = typename mul_instantiator::type;
		using mul_result_checker = EmuCore::TMP::safe_invoke_result<Mul_, sub_result, sub_result>;
		using mul_result = typename mul_result_checker::type;

		using result_type = std::conditional_t<std::is_void_v<mul_result>, char, mul_result>;

		constexpr _vector_dist_square_calculator() : square_distance()
		{
		}

		constexpr inline void operator()(const from_value& from_, const to_value& to_)
		{
			if constexpr (sub_instantiator::value)
			{
				if constexpr (sub_result_checker::value)
				{
					if constexpr (mul_instantiator::value)
					{
						if constexpr (mul_result_checker::value)
						{
							if constexpr (EmuCore::TMP::valid_template_args_v<AddAssignTemplate_, result_type, mul_result>)
							{
								using AddAssign_ = AddAssignTemplate_<result_type, mul_result>;
								if constexpr (std::is_invocable_v<AddAssign_, result_type&, mul_result>)
								{
									sub_result to_sub_from_ = Sub_()(to_, from_);
									AddAssign_()(square_distance, Mul_()(to_sub_from_, to_sub_from_));
								}
								else
								{
									static_assert
									(
										EmuCore::TMP::get_false<AddAssign_>(),
										"Attempted to calculate the square distance between two EmuMath Vectors, but the instantiated add-assign functor could not be invoked with a reference to the result type and a value of the multiplication result type as arguments."
									);
								}
							}
							else
							{
								static_assert
								(
									EmuCore::TMP::get_false<result_type>(),
									"Attempted to calculate the square distance between two EmuMath Vectors, but an add-assign functor could not be successfully instantiated with the result type and multiplication result type as type arguments."
								);
							}
						}
						else
						{
							static_assert
							(
								EmuCore::TMP::get_false<mul_result_checker>(),
								"Attempted to calculate the square distance between two EmuMath Vectors, but the instantiated multiplication functor could not be invoked with two subtraction results as arguments."
							);
						}
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<mul_instantiator>(),
							"Attempted to calculate the square distance between two EmuMath Vectors, but a multiplication functor could not be successfully instantiated with the result of subtraction used twice as type arguments."
						);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<sub_result_checker>(),
						"Attempted to calculate the square distance between two EmuMath Vectors, but the instaniated subtraction functor could not be invoked with a const reference to each Vector's value_type as arguments."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<sub_instantiator>(),
					"Attempted to calculate the square distance between two EmuMath Vectors, but a subtraction functor could not be successfully instantiated with the unqualified value_type of both Vectors as type arguments."
				);
			}
		}

		result_type square_distance;
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

	template
	<
		template<class...> class MulTemplate_,
		template<class...> class SubTemplate_,
		typename Out_,
		std::size_t LhsA_,
		std::size_t RhsA_,
		std::size_t LhsB_,
		std::size_t RhsB_,
		typename TA_,
		std::size_t SizeA_,
		typename TB_,
		std::size_t SizeB_
	>
	[[nodiscard]] constexpr inline Out_ _vector_cross_3d_calculate_value(const EmuMath::NewVector<SizeA_, TA_>& a_, const EmuMath::NewVector<SizeB_, TB_>& b_)
	{
		using get_a_lhs_t = decltype(_vector_get_theoretical<LhsA_>(a_));
		using get_b_lhs_t = decltype(_vector_get_theoretical<LhsB_>(b_));
		using a_lhs_t_uq = EmuCore::TMP::remove_ref_cv_t<get_a_lhs_t>;
		using b_lhs_t_uq = EmuCore::TMP::remove_ref_cv_t<get_b_lhs_t>;
		if constexpr (EmuCore::TMP::valid_template_args_v<MulTemplate_, a_lhs_t_uq, b_lhs_t_uq>)
		{
			using MulLhs_ = MulTemplate_<a_lhs_t_uq, b_lhs_t_uq>;

			using get_a_rhs_t = decltype(_vector_get_theoretical<RhsA_>(a_));
			using get_b_rhs_t = decltype(_vector_get_theoretical<RhsB_>(b_));
			using a_rhs_t_uq = EmuCore::TMP::remove_ref_cv_t<get_a_rhs_t>;
			using b_rhs_t_uq = EmuCore::TMP::remove_ref_cv_t<get_b_rhs_t>;

			if constexpr (EmuCore::TMP::valid_template_args_v<MulTemplate_, a_rhs_t_uq, b_rhs_t_uq>)
			{
				using MulRhs_ = MulTemplate_<a_rhs_t_uq, b_rhs_t_uq>;
				constexpr bool lhs_mul_invocable = std::is_invocable_v<MulLhs_, get_a_lhs_t, get_b_lhs_t>;
				constexpr bool rhs_mul_invocable = std::is_invocable_v<MulRhs_, get_a_rhs_t, get_b_rhs_t>;

				if constexpr (lhs_mul_invocable && rhs_mul_invocable)
				{
					using lhs_mul_result = std::invoke_result_t<MulLhs_, get_a_lhs_t, get_b_lhs_t>;
					using rhs_mul_result = std::invoke_result_t<MulRhs_, get_a_rhs_t, get_b_rhs_t>;
					using lhs_mul_result_uq = EmuCore::TMP::remove_ref_cv_t<lhs_mul_result>;
					using rhs_mul_result_uq = EmuCore::TMP::remove_ref_cv_t<rhs_mul_result>;

					if constexpr (EmuCore::TMP::valid_template_args_v<SubTemplate_, lhs_mul_result_uq, rhs_mul_result_uq>)
					{
						using Sub_ = SubTemplate_<lhs_mul_result_uq, rhs_mul_result_uq>;

						if constexpr (std::is_invocable_v<Sub_, lhs_mul_result, rhs_mul_result>)
						{
							using sub_result = std::invoke_result_t<Sub_, lhs_mul_result, rhs_mul_result>;

							// After all the safety metaprogramming we can finally output a single index
							// --- Returns (a[LhsA] * b[LhsB]) - (a[RhsA] * b[RhsB]); provided indices are expected to be meaningful for a cross product
							if constexpr (std::is_constructible_v<Out_, sub_result>)
							{
								return Out_
								(
									Sub_()
									(
										MulLhs_()(_vector_get_theoretical<LhsA_>(a_), _vector_get_theoretical<LhsB_>(b_)),
										MulRhs_()(_vector_get_theoretical<RhsA_>(a_), _vector_get_theoretical<RhsB_>(b_))
									)
								);
							}
							else if constexpr (EmuCore::TMP::is_static_castable_v<sub_result, Out_>)
							{
								return static_cast<Out_>
								(
									Sub_()
									(
										MulLhs_()(_vector_get_theoretical<LhsA_>(a_), _vector_get_theoretical<LhsB_>(b_)),
										MulRhs_()(_vector_get_theoretical<RhsA_>(a_), _vector_get_theoretical<RhsB_>(b_))
									)
								);
							}
							else
							{
								static_assert
								(
									EmuCore::TMP::get_false<Out_>(),
									"Attempted to calculate the 3D cross product of two EmuMath Vectors, but the result for at least one index could not be used to form the stored_type of the output Vector."
								);
							}
						}
						else
						{
							static_assert
							(
								EmuCore::TMP::get_false<Out_>(),
								"Attempted to calculate the 3D cross product of two EmuMath Vectors, but the determined subtraction functor cannot be invoked with the results from invoking the two multiplication functors."
							);
						}
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<Out_>(),
							"Attempted to calculate the 3D cross product of two EmuMath Vectors, but the unqualified results of invoking both multiplication functors are not valid when provided as two typeargs for the provided Subtraction template."
						);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Out_>(),
						"Attempted to calculate the 3D cross product of two EmuMath Vectors, but at least one of the determined Multiplication functors could not be invoked with the results of getting an index from both Vectors."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Out_>(),
					"Attempted to calculate the 3D cross product of two EmuMath Vectors, but the used MulTemplate_ cannot be instantiated with the unqualified results of getting at least one index from both Vectors."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Out_>(),
				"Attempted to calculate the 3D cross product of two EmuMath Vectors, but the used MulTemplate_ cannot be instantiated with the unqualified results of getting at least one index from both Vectors."
			);
		}
	}

	template
	<
		std::size_t Index_,
		template<class...> class MulTemplate_,
		template<class...> class SubTemplate_,
		std::size_t OutSize_,
		typename OutT_,
		std::size_t A0_,
		std::size_t A1_,
		std::size_t A2_,
		std::size_t B0_,
		std::size_t B1_,
		std::size_t B2_,
		typename TA_,
		std::size_t SizeA_,
		typename TB_,
		std::size_t SizeB_
	>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<OutSize_, OutT_>::stored_type _vector_cross_3d_output_index
	(
		const EmuMath::NewVector<SizeA_, TA_>& a_,
		const EmuMath::NewVector<SizeB_, TB_>& b_
	)
	{
		using out_stored_type = typename EmuMath::NewVector<OutSize_, OutT_>::stored_type;
		if constexpr (Index_ == 0)
		{
			// (a[1] * b[2]) - (a[2] * b[1])
			return _vector_cross_3d_calculate_value<MulTemplate_, SubTemplate_, out_stored_type, A1_, A2_, B2_, B1_>(a_, b_);
		}
		else if constexpr (Index_ == 1)
		{
			// (a[2] * b[0]) - (a[0] * b[2])
			return _vector_cross_3d_calculate_value<MulTemplate_, SubTemplate_, out_stored_type, A2_, A0_, B0_, B2_>(a_, b_);
		}
		else if constexpr (Index_ == 2)
		{
			// (a[0] * b[1]) - (a[1] * b[0])
			return _vector_cross_3d_calculate_value<MulTemplate_, SubTemplate_, out_stored_type, A0_, A1_, B1_, B0_>(a_, b_);
		}
		else
		{
			if constexpr (std::is_default_constructible_v<out_stored_type>)
			{
				return out_stored_type();
			}
			else
			{
				using implied_zero_type = decltype(_vector_get_non_contained_value<EmuMath::NewVector<OutSize_, OutT_>>());
				if constexpr (std::is_constructible_v<out_stored_type, implied_zero_type>)
				{
					return out_stored_type(_vector_get_non_contained_value<EmuMath::NewVector<OutSize_, OutT_>>());
				}
				else if constexpr(EmuCore::TMP::is_static_castable_v<implied_zero_type, out_stored_type>)
				{
					return static_cast<out_stored_type>(_vector_get_non_contained_value<EmuMath::NewVector<OutSize_, OutT_>>());
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutT_>(),
						"Attempted to calculate the 3D cross product of two EmuMath Vectors with an output type containing more than 3 indices. However, the output Vector's stored_type can neither be default-constructed nor constructed from a non-contained implied zero for the Vector type. Output as a 3D Vector is recommended for this case."
					);
				}
			}

		}
	}

	template
	<
		template<class...> class MulTemplate_,
		template<class...> class SubTemplate_,
		std::size_t OutSize_,
		typename OutT_,
		std::size_t A0_,
		std::size_t A1_,
		std::size_t A2_,
		std::size_t B0_,
		std::size_t B1_,
		std::size_t B2_,
		typename TA_,
		std::size_t SizeA_,
		typename TB_,
		std::size_t SizeB_,
		std::size_t...OutIndices_
	>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> _vector_cross_3d_build_out
	(
		const EmuMath::NewVector<SizeA_, TA_>& a_,
		const EmuMath::NewVector<SizeB_, TB_>& b_,
		std::index_sequence<OutIndices_...> out_indices_
	)
	{
		if constexpr(OutSize_ != 0)
		{
			if constexpr (!EmuMath::NewVector<OutSize_, OutT_>::contains_ref)
			{
				return EmuMath::NewVector<OutSize_, OutT_>
				(
					_vector_cross_3d_output_index<OutIndices_, MulTemplate_, SubTemplate_, OutSize_, OutT_, A0_, A1_, A2_, B0_, B1_, B2_>
					(
						a_,
						b_
					)...
				);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutT_>(),
					"Attempted to form a 3D cross product of two EmuMath Vectors, but the provided output Vector is a reference containing Vector. As the output results are temporary values, this would result in dangling references and thus has been prohibited."
				);
			}
		}
		else
		{
			return EmuMath::NewVector<OutSize_, OutT_>();
		}
	}

	template
	<
		template<class...> class MulTemplate_,
		template<class...> class SubTemplate_,
		std::size_t OutSize_,
		typename OutT_,
		std::size_t A0_,
		std::size_t A1_,
		std::size_t A2_,
		std::size_t B0_,
		std::size_t B1_,
		std::size_t B2_,
		typename TA_,
		std::size_t SizeA_,
		typename TB_,
		std::size_t SizeB_
	>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> _vector_cross_3d(const EmuMath::NewVector<SizeA_, TA_>& a_, const EmuMath::NewVector<SizeB_, TB_>& b_)
	{
		using index_sequence_ = std::make_index_sequence<EmuMath::NewVector<OutSize_, OutT_>::size>;
		return _vector_cross_3d_build_out<MulTemplate_, SubTemplate_, OutSize_, OutT_, A0_, A1_, A2_, B0_, B1_, B2_>(a_, b_, index_sequence_());
	}

	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Out_, std::size_t FromSize_, typename FromT_, std::size_t ToSize_, typename ToT_>
	[[nodiscard]] constexpr inline Out_ _vector_square_distance(const EmuMath::NewVector<FromSize_, FromT_>& from_, const EmuMath::NewVector<ToSize_, ToT_>& to_)
	{
		if constexpr (BeginIndex_ < EndIndex_)
		{
			using Func_ = _vector_dist_square_calculator<EmuCore::do_subtract, EmuCore::do_add_assign, EmuCore::do_multiply, FromSize_, FromT_, ToSize_, ToT_>;
			Func_ func_ = Func_();
			_vector_mutate_invoke_only<Func_&, BeginIndex_, EndIndex_>(func_, from_, to_);

			using result_moved = decltype(std::move(func_.square_distance));
			if constexpr (std::is_constructible_v<Out_, result_moved>)
			{
				return Out_(std::move(func_.square_distance));
			}
			else if constexpr (EmuCore::TMP::is_static_castable_v<result_moved, Out_>)
			{
				return static_cast<Out_>(std::move(func_.square_distance));
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Out_>(),
					"Attempted to calculate the square distance between two EmuMath Vectors, but the type used for calculation cannot be used to form the provided Out_ type."
				);
			}
		}
		else
		{
			if constexpr (std::is_default_constructible_v<Out_>())
			{
				return Out_();
			}
			else if constexpr(std::is_constructible_v<Out_, decltype(0)>)
			{
				return Out_(0);
			}
			else if constexpr (std::is_constructible_v<Out_, decltype(0.0f)>)
			{
				return Out_(0.0f);
			}
			else if constexpr (EmuCore::TMP::is_static_castable_v<decltype(0), Out_>)
			{
				return static_cast<Out_>(0);
			}
			else if constexpr (EmuCore::TMP::is_static_castable_v<decltype(0.0f), Out_>)
			{
				return static_cast<Out_>(0.0f);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Out_>(),
					"Attempted to calculate the square distance between two EmuMath Vectors, but the provided index range would result in no axes to compare. This is okay, but results in output of default-or-zero, which is not possible with the provided Out_ type."
				);
			}
		}
	}

	template<bool IncludeNonContained_, typename Out_, std::size_t FromSize_, typename FromT_, std::size_t ToSize_, typename ToT_>
	[[nodiscard]] constexpr inline Out_ _vector_square_distance(const EmuMath::NewVector<FromSize_, FromT_>& from_, const EmuMath::NewVector<ToSize_, ToT_>& to_)
	{
		constexpr std::size_t from_size_ = EmuMath::NewVector<FromSize_, FromT_>::size;
		constexpr std::size_t to_size_ = EmuMath::NewVector<ToSize_, ToT_>::size;
		constexpr std::size_t smallest_size_ = (from_size_ <= to_size_) ? from_size_ : to_size_;
		constexpr std::size_t greatest_size_ = (from_size_ >= to_size_) ? from_size_ : to_size_;

		return _vector_square_distance<0, IncludeNonContained_ ? greatest_size_ : smallest_size_, Out_>(from_, to_);
	}

	template
	<
		template<class...> class SqrtTemplate_,
		std::size_t BeginIndex_,
		std::size_t EndIndex_,
		typename Out_,
		std::size_t FromSize_,
		typename FromT_,
		std::size_t ToSize_,
		typename ToT_
	>
	[[nodiscard]] constexpr inline Out_ _vector_distance(const EmuMath::NewVector<FromSize_, FromT_>& from_, const EmuMath::NewVector<ToSize_, ToT_>& to_)
	{
		if constexpr (BeginIndex_ < EndIndex_)
		{
			using Func_ = _vector_dist_square_calculator<EmuCore::do_subtract, EmuCore::do_add_assign, EmuCore::do_multiply, FromSize_, FromT_, ToSize_, ToT_>;
			Func_ func_ = Func_();
			_vector_mutate_invoke_only<Func_&, BeginIndex_, EndIndex_>(func_, from_, to_);

			using square_mag_type = typename Func_::result_type;
			using square_mag_type_uq = EmuCore::TMP::remove_ref_cv_t<square_mag_type>;
			if constexpr (EmuCore::TMP::valid_template_args_v<SqrtTemplate_, square_mag_type_uq>)
			{
				using Sqrt_ = SqrtTemplate_<square_mag_type_uq>;
				if constexpr (std::is_invocable_v<Sqrt_, std::add_lvalue_reference_t<square_mag_type>>)
				{
					using sqrt_result = std::invoke_result_t<Sqrt_, std::add_lvalue_reference_t<square_mag_type>>;
					if constexpr (std::is_constructible_v<Out_, sqrt_result>)
					{
						return Out_(Sqrt_()(func_.square_distance));
					}
					else if constexpr (EmuCore::TMP::is_static_castable_v<sqrt_result, Out_>)
					{
						return static_cast<Out_>(Sqrt_()(func_.square_distance));
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<Sqrt_>(),
							"Attempted to calculate the distance between two EmuMath Vectors, but the provided Out_ type could not be formed from the result of obtaining the square root of the squared distance."
						);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Sqrt_>(),
						"Attempted to calculate the distance between two EmuMath Vectors, but the square-root functor could not be invoked with a reference to the squared distance."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<square_mag_type>(),
					"Attempted to calculate distance between two EmuMath Vectors, but the square-root template could not be instantiated with the result type for calculating the squared distance."
				);
			}
		}
		else
		{
			if constexpr (std::is_default_constructible_v<Out_>())
			{
				return Out_();
			}
			else if constexpr(std::is_constructible_v<Out_, decltype(0)>)
			{
				return Out_(0);
			}
			else if constexpr (std::is_constructible_v<Out_, decltype(0.0f)>)
			{
				return Out_(0.0f);
			}
			else if constexpr (EmuCore::TMP::is_static_castable_v<decltype(0), Out_>)
			{
				return static_cast<Out_>(0);
			}
			else if constexpr (EmuCore::TMP::is_static_castable_v<decltype(0.0f), Out_>)
			{
				return static_cast<Out_>(0.0f);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Out_>(),
					"Attempted to calculate the distance between two EmuMath Vectors, but the provided index range would result in no axes to compare. This is okay, but results in output of default-or-zero, which is not possible with the provided Out_ type."
				);
			}
		}
	}

	template
	<
		template<class...> class SqrtTemplate_,
		bool IncludeNonContained_,
		typename Out_,
		std::size_t FromSize_,
		typename FromT_,
		std::size_t ToSize_,
		typename ToT_
	>
	[[nodiscard]] constexpr inline Out_ _vector_distance(const EmuMath::NewVector<FromSize_, FromT_>& from_, const EmuMath::NewVector<ToSize_, ToT_>& to_)
	{
		constexpr std::size_t from_size_ = EmuMath::NewVector<FromSize_, FromT_>::size;
		constexpr std::size_t to_size_ = EmuMath::NewVector<ToSize_, ToT_>::size;
		constexpr std::size_t smallest_size_ = (from_size_ <= to_size_) ? from_size_ : to_size_;
		constexpr std::size_t greatest_size_ = (from_size_ >= to_size_) ? from_size_ : to_size_;

		return _vector_distance<SqrtTemplate_, 0, IncludeNonContained_ ? greatest_size_ : smallest_size_, Out_>(from_, to_);
	}


	template
	<
		template<class...> class SubTemplate_,
		template<class...> class MulTemplate_,
		std::size_t BeginIndex_,
		std::size_t EndIndex_,
		std::size_t OutSize_,
		typename OutT_,
		std::size_t RaySize_,
		typename RayT_,
		std::size_t NormSize_,
		typename NormT_
	>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> _vector_reflect_normal
	(
		const EmuMath::NewVector<RaySize_, RayT_>& ray_,
		const EmuMath::NewVector<NormSize_, NormT_>& normal_
	)
	{
		using ray_fp = typename EmuMath::NewVector<RaySize_, RayT_>::preferred_floating_point;
		if constexpr (EmuCore::TMP::valid_template_args_v<MulTemplate_, ray_fp, ray_fp>)
		{
			// MulDot_: Used for 2 * dot(ray_, normal_)
			using MulDot_ = MulTemplate_<ray_fp, ray_fp>;
			if constexpr (std::is_invocable_v<MulDot_, ray_fp, ray_fp>)
			{
				using mul_dot_result = std::invoke_result_t<MulDot_, ray_fp, ray_fp>;
				using make_two = EmuCore::TMP::try_make_constant<ray_fp, 2>;
				if constexpr (make_two::is_valid)
				{
					// Select the smallest size for calculations since we don't want to be constructing unused indices
					constexpr std::size_t norm_calc_size_ = OutSize_ <= NormSize_ ? OutSize_ : NormSize_;
					using norm_fp = typename EmuMath::NewVector<NormSize_, NormT_>::preferred_floating_point;

					// Calculates normal_ * (2 * dot(ray_, normal_))
					EmuMath::NewVector<norm_calc_size_, norm_fp> norm_mult_ = _vector_mutate_with_func_template_args_only
					<
						MulTemplate_,
						EmuMath::NewVector<norm_calc_size_, norm_fp>,
						BeginIndex_,
						EndIndex_,
						BeginIndex_
					>(normal_, MulDot_()(make_two::get(), _vector_dot<BeginIndex_, EndIndex_, ray_fp>(ray_, normal_)));

					// Return the calculation of ray_ - (normal_ * (2 * dot(ray_, normal_)))
					return _vector_mutate_with_func_template_args_only
					<
						SubTemplate_,
						EmuMath::NewVector<OutSize_, OutT_>,
						BeginIndex_,
						EndIndex_,
						BeginIndex_
					>(ray_, norm_mult_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<ray_fp>(),
						"Attempted to calculate an EmuMath Vector reflection based on a ray Vector and a normal Vector, but the constant 2 could not be formed with the ray Vector's preferred_floating_point type."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<ray_fp>(),
					"Attempted to calculate an EmuMath Vector reflection based on a ray Vector and a normal Vector, but the determined multiplication functor could not be invoked with two arguments of the ray Vector's preferred_floating_point type."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<ray_fp>(),
				"Attempted to calculate an EmuMath Vector reflection based on a ray Vector and a normal Vector, but a multiplication template could not be instantiated with the ray Vector's preferred_floating_point type as two type arguments."
			);
		}
	}

	template
	<
		template<class...> class SubTemplate_,
		template<class...> class MulTemplate_,
		std::size_t OutSize_,
		typename OutT_,
		std::size_t RaySize_,
		typename RayT_,
		std::size_t NormSize_,
		typename NormT_
	>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> _vector_reflect_normal
	(
		const EmuMath::NewVector<RaySize_, RayT_>& ray_,
		const EmuMath::NewVector<NormSize_, NormT_>& normal_
	)
	{
		return _vector_reflect_normal
		<
			SubTemplate_,
			MulTemplate_,
			0,
			EmuMath::NewVector<OutSize_, OutT_>::size,
			OutSize_,
			OutT_
		>(ray_, normal_);
	}

	template
	<
		template<class...> class MulTemplate_,
		template<class...> class SubTemplate_,
		std::size_t OutSize_,
		typename OutT_,
		std::size_t ReadOffset_,
		std::size_t SizeA_,
		typename TA_,
		std::size_t SizeB_,
		typename TB_,
		std::size_t SizeC_,
		typename TC_
	>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> _vector_normal_to_plane_3d_no_norm
	(
		const EmuMath::NewVector<SizeA_, TA_>& a_,
		const EmuMath::NewVector<SizeB_, TB_>& b_,
		const EmuMath::NewVector<SizeC_, TC_>& c_
	)
	{
		using out_fp = typename EmuMath::NewVector<OutSize_, OutT_>::preferred_floating_point;
		using calc_vector = EmuMath::NewVector<3, out_fp>;
		return _vector_cross_3d<MulTemplate_, SubTemplate_, OutSize_, OutT_, 0, 1, 2, 0, 1, 2>
		(
			_vector_mutate_with_func_template_args_only<SubTemplate_, calc_vector, 0, 3, ReadOffset_>(b_, a_),
			_vector_mutate_with_func_template_args_only<SubTemplate_, calc_vector, 0, 3, ReadOffset_>(c_, a_)
		);
	}

	template
	<
		template<class...> class MulTemplate_,
		template<class...> class SubTemplate_,
		template<class...> class SqrtTemplate_,
		std::size_t OutSize_,
		typename OutT_,
		std::size_t ReadOffset_,
		std::size_t SizeA_,
		typename TA_,
		std::size_t SizeB_,
		typename TB_,
		std::size_t SizeC_,
		typename TC_
	>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> _vector_normal_to_plane_3d
	(
		const EmuMath::NewVector<SizeA_, TA_>& a_,
		const EmuMath::NewVector<SizeB_, TB_>& b_,
		const EmuMath::NewVector<SizeC_, TC_>& c_
	)
	{
		using out_fp = typename EmuMath::NewVector<OutSize_, OutT_>::preferred_floating_point;
		using calc_vector = EmuMath::NewVector<3, out_fp>;
		return _vector_normalise<SqrtTemplate_, OutSize_, OutT_, 0, 3>
		(
			_vector_cross_3d<MulTemplate_, SubTemplate_, 3, out_fp, 0, 1, 2, 0, 1, 2>
			(
				_vector_mutate_with_func_template_args_only<SubTemplate_, calc_vector, 0, 3, ReadOffset_>(b_, a_),
				_vector_mutate_with_func_template_args_only<SubTemplate_, calc_vector, 0, 3, ReadOffset_>(c_, a_)
			)
		);
	}

	template
	<
		template<class...> class MulTemplate_,
		template<class...> class ReciprocalTemplate_,
		std::size_t OutSize_,
		typename OutT_,
		std::size_t BeginIndex_,
		std::size_t EndIndex_,
		std::size_t SizeA_,
		typename TA_,
		std::size_t SizeB_,
		typename TB_
	>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> _vector_project
	(
		const EmuMath::NewVector<SizeA_, TA_>& a_,
		const EmuMath::NewVector<SizeB_, TB_>& b_
	)
	{
		using out_fp = typename EmuMath::NewVector<OutSize_, OutT_>::preferred_floating_point;
		if constexpr (EmuCore::TMP::valid_template_args_v<ReciprocalTemplate_, out_fp>)
		{
			using Reciprocal_ = ReciprocalTemplate_<out_fp>;
			if constexpr (std::is_invocable_v<Reciprocal_, out_fp>)
			{
				if constexpr (EmuCore::TMP::valid_template_args_v<MulTemplate_, out_fp, out_fp>)
				{
					using Mul_ = MulTemplate_<out_fp, out_fp>;
					if constexpr (std::is_invocable_v<Mul_, out_fp, out_fp>)
					{
						return _vector_mutate_with_func_template_args_only<MulTemplate_, EmuMath::NewVector<OutSize_, OutT_>, BeginIndex_, EndIndex_, BeginIndex_>
						(
							b_,
							Mul_()
							(
								_vector_dot<BeginIndex_, EndIndex_, out_fp>(a_, b_),
								Reciprocal_()(_vector_square_mag<BeginIndex_, EndIndex_, out_fp>(b_))
							)
						);
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<out_fp>(),
							"Attempted to project an EmuMath Vector a onto an EmuMath Vector b, but the multiplication functor cannot be invoked with two arguments of the output Vector's preferred_floating_point type."
						);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<out_fp>(),
						"Attempted to project an EmuMath Vector a onto an EmuMath Vector b, but the provided multiplication template could not be instantiated with two typeargs of the output Vector's preferred_floating_point type."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<out_fp>(),
					"Attempted to project an EmuMath Vector a onto an EmuMath Vector b, but the reciprocal functor cannot be invoked with an argument of the output Vector's preferred_floating_point type."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<out_fp>(),
				"Attempted to project an EmuMath Vector a onto an EmuMath Vector b, but the provided reciprocal template could not be instantiated with a typearg of the output Vector's preferred_floating_point type."
			);
		}
	}

	template
	<
		template<class...> class MulTemplate_,
		template<class...> class ReciprocalTemplate_,
		std::size_t OutSize_,
		typename OutT_,
		std::size_t SizeA_,
		typename TA_,
		std::size_t SizeB_,
		typename TB_
	>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> _vector_project
	(
		const EmuMath::NewVector<SizeA_, TA_>& a_,
		const EmuMath::NewVector<SizeB_, TB_>& b_
	)
	{
		return _vector_project<MulTemplate_, ReciprocalTemplate_, OutSize_, OutT_, 0, EmuMath::NewVector<OutSize_, OutT_>::size>(a_, b_);
	}
}

#endif
