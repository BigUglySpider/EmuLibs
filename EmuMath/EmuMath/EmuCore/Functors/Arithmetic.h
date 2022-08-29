#ifndef EMU_CORE_ARITHMETIC_FUNCTORS_H_INC_
#define EMU_CORE_ARITHMETIC_FUNCTORS_H_INC_ 1

#include "../ArithmeticHelpers/CommonMath.h"
#include "../TMPHelpers/OperatorChecks.h"
#include "../TMPHelpers/StdFunctionChecks.h"
#include "../TMPHelpers/TypeComparators.h"
#include "../TMPHelpers/TypeConvertors.h"
#include "../TMPHelpers/Values.h"
#include "../TMPHelpers/VariadicHelpers.h"
#include <cstddef>
#include <functional>

#include <iostream>

namespace EmuCore
{
#pragma region SPECIAL_ARITHMETIC_FUNCTORS
	/// <summary>
	/// <para> Template square root functor, used to calculate the square root of a value of type T_. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para>
	///		If T_ is constexpr-evaluable, this functor provides a guarantee to perform a constexpr sqrt. Specialisations must follow this behaviour. 
	///		It should be noted that constexpr sqrts could potentially make performance sacrifices, and as such this should not be used for items that are guaranteed 
	///		to be executed at runtime.
	/// </para>
	/// </summary>
	template<typename T_>
	struct do_sqrt_constexpr
	{
		using Out_ = std::conditional_t<std::is_floating_point_v<T_>, T_, double>;

		constexpr do_sqrt_constexpr()
		{
		}
		[[nodiscard]] constexpr inline Out_ operator()(const T_& val_) const
		{
			return EmuCore::SqrtConstexpr<Out_, T_>(val_);
		}
	};
	template<>
	struct do_sqrt_constexpr<void>
	{
		constexpr do_sqrt_constexpr()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline std::invoke_result_t<do_sqrt_constexpr<T_>, const T_&> operator()(const T_& val_) const
		{
			return do_sqrt_constexpr<T_>()(val_);
		}
	};

	/// <summary>
	/// <para> Template square root functor, used to calculate the square root of a value of type T_. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para> May be constexpr, but does not provide constexpr guarantee; for such behaviour, use the `do_sqrt_constexpr` template. </para>
	/// </summary>
	template<typename T_>
	struct do_sqrt
	{
	private:
		using floating_point_ = std::conditional_t<std::is_floating_point_v<T_>, T_, double>;

	public:
		constexpr do_sqrt()
		{
		}
		[[nodiscard]] inline floating_point_ operator()(const T_& val_) const
		{
			if constexpr (std::is_same_v<T_, floating_point_>)
			{
				return DoMatchingStandardSqrt<T_>(val_);
			}
			else
			{
				return DoMatchingStandardSqrt<floating_point_>(static_cast<floating_point_>(val_));
			}
		}
	};
	template<>
	struct do_sqrt<void>
	{
		constexpr do_sqrt()
		{
		}
		template<typename T_>
		[[nodiscard]] inline std::invoke_result_t<do_sqrt<T_>, const T_&> operator()(const T_& val_) const
		{
			return do_sqrt<T_>()(val_);
		}
	};
#pragma endregion

#pragma region ROUNDING_FUNCTORS
	/// <summary>
	/// <para> Template floor-rounding functor, used to round a value of type T_ toward negative infinity. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para>
	///		If T_ is constexpr-evaluable, this functor provides a guarantee to perform a constexpr round. Specialisations must follow this behaviour. 
	///		It should be noted that constexpr rounds could potentially make performance sacrifices, and as such this should not be used for items that are guaranteed 
	///		to be executed at runtime.
	/// </para>
	/// </summary>
	template<typename T_>
	struct do_floor_constexpr
	{
		constexpr do_floor_constexpr()
		{
		}
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			if constexpr (std::is_integral_v<T_>)
			{
				return val_;
			}
			else
			{
				if (val_ < T_(0))
				{
					// If trunc is different, we will have done a ceil since negative trunc == negative ceil
					// --- As such, we need to subtract 1 from the truncated value if we do need to perform a round
					T_ truncated_ = static_cast<T_>(static_cast<std::int64_t>(val_));
					return (truncated_ == val_) ? val_ : (truncated_ - T_(1));
				}
				else
				{
					// Can take advantage of a higher range from an unsigned int if we know we're positive
					// --- Additionally, positive trunc == positive floor
					return static_cast<T_>(static_cast<std::uint64_t>(val_));
				}
			}
		}
	};
	template<>
	struct do_floor_constexpr<void>
	{
		constexpr do_floor_constexpr()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			return do_floor_constexpr<T_>()(val_);
		}
	};

	/// <summary>
	/// <para> Template ceil-rounding functor, used to round a value of type T_ toward positive infinity. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para>
	///		If T_ is constexpr-evaluable, this functor provides a guarantee to perform a constexpr round. Specialisations must follow this behaviour. 
	///		It should be noted that constexpr rounds could potentially make performance sacrifices, and as such this should not be used for items that are guaranteed 
	///		to be executed at runtime.
	/// </para>
	/// </summary>
	template<typename T_>
	struct do_ceil_constexpr
	{
		constexpr do_ceil_constexpr()
		{
		}
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			if constexpr (std::is_integral_v<T_>)
			{
				return val_;
			}
			else
			{
				if (val_ < T_(0))
				{
					// Negative trunc == negative ceil
					return static_cast<T_>(static_cast<std::int64_t>(val_));
				}
				else
				{
					// When truncated, a positive value is equal to its floored value
					// --- As such, when a truncation indicates a round should occur, we need to add 1 to the truncated value when positive
					T_ truncated_ = static_cast<T_>(static_cast<std::uint64_t>(val_));
					return (truncated_ == val_) ? val_ : (truncated_ + T_(1));
				}
			}
		}
	};
	template<>
	struct do_ceil_constexpr<void>
	{
		constexpr do_ceil_constexpr()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			return do_ceil_constexpr<T_>()(val_);
		}
	};

	/// <summary>
	/// <para> Template truncation functor, used to round a value of type T_ toward 0. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para>
	///		If T_ is constexpr-evaluable, this functor provides a guarantee to perform a constexpr round. Specialisations must follow this behaviour. 
	///		It should be noted that constexpr rounds could potentially make performance sacrifices, and as such this should not be used for items that are guaranteed 
	///		to be executed at runtime.
	/// </para>
	/// </summary>
	template<typename T_>
	struct do_trunc_constexpr
	{
		constexpr do_trunc_constexpr()
		{
		}
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			if constexpr (std::is_integral_v<T_>)
			{
				return val_;
			}
			else
			{
				return static_cast<T_>(static_cast<std::int64_t>(val_));
			}
		}
	};
	template<>
	struct do_trunc_constexpr<void>
	{
		constexpr do_trunc_constexpr()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			return do_trunc_constexpr<T_>()(val_);
		}
	};

	/// <summary>
	/// <para> Template floor-rounding functor, used to round a value of type T_ toward negative infinity. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para> May be constexpr, but does not provide constexpr guarantee; for such behaviour, use the `do_floor_constexpr` template. </para>
	/// </summary>
	template<typename T_>
	struct do_floor
	{
		constexpr do_floor()
		{
		}
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			return DoCorrectFloor<T_>(val_);
		}
	};
	template<>
	struct do_floor<void>
	{
		constexpr do_floor()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline std::invoke_result_t<do_floor<T_>, const T_&> operator()(const T_& val_) const
		{
			return do_floor<T_>()(val_);
		}
	};

	/// <summary>
	/// <para> Template ceil-rounding functor, used to round a value of type T_ toward positive infinity. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para> May be constexpr, but does not provide constexpr guarantee; for such behaviour, use the `do_ceil_constexpr` template. </para>
	/// </summary>
	template<typename T_>
	struct do_ceil
	{
		constexpr do_ceil()
		{
		}
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			return DoCorrectCeil<T_>(val_);
		}
	};
	template<>
	struct do_ceil<void>
	{
		constexpr do_ceil()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline std::invoke_result_t<do_ceil<T_>, const T_&> operator()(const T_& val_) const
		{
			return do_ceil<T_>()(val_);
		}
	};

	/// <summary>
	/// <para> Template truncation functor, used to round a value of type T_ toward 0. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para> May be constexpr, but does not provide constexpr guarantee; for such behaviour, use the `do_trunc_constexpr` template. </para>
	/// </summary>
	template<typename T_>
	struct do_trunc
	{
		constexpr do_trunc()
		{
		}
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			return DoCorrectTrunc<T_>(val_);
		}
	};
	template<>
	struct do_trunc<void>
	{
		constexpr do_trunc()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline std::invoke_result_t<do_trunc<T_>, const T_&> operator()(const T_& val_) const
		{
			return do_trunc<T_>()(val_);
		}
	};
#pragma endregion

#pragma region CONST_OPERATOR_ARITHMETIC_FUNCTORS
	/// <summary>
	/// <para> Template addition functor which allows specialisation for separate left-hand and right-hand argument types. </para>
	/// <para> Rhs_ will default to Lhs_ unless an explicit argument for Rhs_ is provided. </para>
	/// <para> If Lhs_ and Rhs_ are void, the correct specialisation of this functor will be invoked based on arguments passed on invocation. </para>
	/// </summary>
	template<typename Lhs_ = void, typename Rhs_ = Lhs_>
	struct do_add
	{
		constexpr do_add()
		{
		}
		[[nodiscard]] constexpr inline EmuCore::TMP::plus_operator_result_t<const Lhs_&, const Rhs_&> operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_plus_operator_v<const Lhs_&, const Rhs_&>)
			{
				return lhs_ + rhs_;
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Lhs_>(), "Attempted to perform a add operation via EmuCore::do_add, but the provided Lhs_ type does not have a const + operator which takes a const Rhs_ ref argument.");
			}
		}
	};
	template<>
	struct do_add<void, void>
	{
	public:
		constexpr do_add()
		{
		}
		template<typename Lhs_, typename Rhs_>
		[[nodiscard]] constexpr inline std::invoke_result_t<do_add<Lhs_, Rhs_>, const Lhs_&, const Rhs_&> operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_add<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	/// <summary>
	/// <para> Template subtraction functor which allows specialisation for separate left-hand and right-hand argument types. </para>
	/// <para> Rhs_ will default to Lhs_ unless an explicit argument for Rhs_ is provided. </para>
	/// <para> If Lhs_ and Rhs_ are void, the correct specialisation of this functor will be invoked based on arguments passed on invocation. </para>
	/// </summary>
	template<typename Lhs_ = void, typename Rhs_ = Lhs_>
	struct do_subtract
	{
		constexpr do_subtract()
		{
		}
		[[nodiscard]] constexpr inline EmuCore::TMP::subtract_operator_result_t<const Lhs_&, const Rhs_&> operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_subtract_operator_v<const Lhs_&, const Rhs_&>)
			{
				return lhs_ - rhs_;
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Lhs_>(), "Attempted to perform a subtract operation via EmuCore::do_subtract, but the provided Lhs_ type does not have a const - operator which takes a const Rhs_ ref argument.");
			}
		}
	};
	template<>
	struct do_subtract<void, void>
	{
	public:
		constexpr do_subtract()
		{
		}
		template<typename Lhs_, typename Rhs_>
		constexpr inline std::invoke_result_t<do_subtract<Lhs_, Rhs_>, const Lhs_&, const Rhs_&> operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_subtract<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	/// <summary>
	/// <para> Template multiplication functor which allows specialisation for separate left-hand and right-hand argument types. </para>
	/// <para> Rhs_ will default to Lhs_ unless an explicit argument for Rhs_ is provided. </para>
	/// <para> If Lhs_ and Rhs_ are void, the correct specialisation of this functor will be invoked based on arguments passed on invocation. </para>
	/// </summary>
	template<typename Lhs_ = void, typename Rhs_ = Lhs_>
	struct do_multiply
	{
		constexpr do_multiply()
		{
		}
		constexpr inline EmuCore::TMP::multiply_operator_result_t<const Lhs_&, const Rhs_&> operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_multiply_operator_v<const Lhs_&, const Rhs_&>)
			{
				return lhs_ * rhs_;
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Lhs_>(), "Attempted to perform a multiply operation via EmuCore::do_multiply, but the provided Lhs_ type does not have a const * operator which takes a const Rhs_ ref argument.");
			}
		}
	};
	template<>
	struct do_multiply<void, void>
	{
	public:
		constexpr do_multiply()
		{
		}
		template<typename Lhs_, typename Rhs_>
		constexpr inline std::invoke_result_t<do_multiply<Lhs_, Rhs_>, const Lhs_&, const Rhs_&> operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_multiply<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	/// <summary>
	/// <para> Template division functor which allows specialisation for separate left-hand and right-hand argument types. </para>
	/// <para> Rhs_ will default to Lhs_ unless an explicit argument for Rhs_ is provided. </para>
	/// <para> If Lhs_ and Rhs_ are void, the correct specialisation of this functor will be invoked based on arguments passed on invocation. </para>
	/// </summary>
	template<typename Lhs_ = void, typename Rhs_ = Lhs_>
	struct do_divide
	{
		constexpr do_divide()
		{
		}
		constexpr inline EmuCore::TMP::divide_operator_result_t<const Lhs_&, const Rhs_&> operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_divide_operator_v<const Lhs_&, const Rhs_&>)
			{
				return lhs_ / rhs_;
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Lhs_>(), "Attempted to perform a divide operation via EmuCore::do_divide, but the provided Lhs_ type does not have a const / operator which takes a const Rhs_ ref argument.");
			}
		}
	};
	template<>
	struct do_divide<void, void>
	{
	public:
		constexpr do_divide()
		{
		}
		template<typename Lhs_, typename Rhs_>
		constexpr inline std::invoke_result_t<do_divide<Lhs_, Rhs_>, const Lhs_&, const Rhs_&> operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_divide<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	/// <summary>
	/// <para> Template modulo-division functor which allows specialisation for separate left-hand and right-hand argument types. </para>
	/// <para> Rhs_ will default to Lhs_ unless an explicit argument for Rhs_ is provided. </para>
	/// <para> If Lhs_ and Rhs_ are void, the correct specialisation of this functor will be invoked based on arguments passed on invocation. </para>
	/// <para> If either Lhs_ or Rhs_ is a floating-point type, this will output the results of an fmod operation by default. </para>
	/// </summary>
	template<typename Lhs_, typename Rhs_>
	struct do_mod
	{
	private:
		static constexpr bool is_floating_point_mod = std::is_floating_point_v<Lhs_> || std::is_floating_point_v<Rhs_>;
		template<typename InT_, bool IsFmod_ = is_floating_point_mod>
		struct _out_finder
		{
			using out_type = EmuCore::TMP::mod_operator_result_t<const InT_&, const Rhs_&>;
		};
		template<typename InT_>
		struct _out_finder<InT_, false>
		{
			using out_type = EmuCore::TMP::mod_operator_result_t<const InT_&, const Rhs_&>;
		};
		template<typename InT_>
		struct _out_finder<InT_, true>
		{
			using out_type = decltype(EmuCore::FmodConstexpr<InT_, Rhs_>(std::declval<InT_>(), std::declval<Rhs_>()));
		};

	public:
		using out_type = typename _out_finder<Lhs_>::out_type;

		constexpr do_mod()
		{
		}
		constexpr inline out_type operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (is_floating_point_mod)
			{
				return EmuCore::FmodConstexpr<Lhs_, Rhs_>(lhs_, rhs_);
			}
			else if constexpr (EmuCore::TMP::has_mod_operator_v<const Lhs_&, const Rhs_&>)
			{
				return lhs_ % rhs_;
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Lhs_>(), "Attempted to perform a mod operation via EmuCore::do_mod, but the provided Lhs_ type does not have a valid % operator which takes the provided const Rhs_ operand, and is not a fall back to an fmod call.");
			}
		}
	};
	template<>
	struct do_mod<void, void>
	{
		constexpr do_mod()
		{
		}
		template<typename Lhs_, typename Rhs_>
		constexpr inline std::invoke_result_t<do_mod<Lhs_, Rhs_>, const Lhs_&, const Rhs_&> operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_mod<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	/// <summary>
	/// <para> Template negation functor, which provides additional wrapping to provide better-expected results if T_ is unsigned. </para>
	/// <para> Note that the additional wrapping is performed at compile time, and is only within the default functor. </para>
	/// <para> 
	///		If T_ is unsigned, it will be cast to the next signed integral width before negation, if possible; otherwise it will be cast to a double before negation. 
	///		(e.g. T_ = uint32_t will be cast to int64_t, T_ = uint64_t will be cast to double). 
	///		It is most likely that the cast will result in a different output type to the passed type.
	/// </para>
	/// <para> Defaults to T_ = void, which may be invoked with any type argument and will invoke the do_negate for the type passed on invocation. </para>
	/// </summary>
	template<typename T_ = void>
	struct do_negate
	{
	private:
		template<typename InT_, bool IsUnsigned_ = std::is_unsigned_v<InT_>>
		struct _unsigned_helper
		{
			using out_type = EmuCore::TMP::unary_minus_operator_result_t<const InT_&>;
		};
		template<typename InT_>
		struct _unsigned_helper<InT_, true>
		{
			using signed_type = std::make_signed_t<InT_>;
			using next_size_type = EmuCore::TMP::next_size_up_t<signed_type>;
			using cast_type = std::conditional_t<(sizeof(next_size_type) > sizeof(InT_)), next_size_type, double>;
			using out_type = EmuCore::TMP::unary_minus_operator_result_t<cast_type>;
		};

		using _type_helper = _unsigned_helper<T_>;

	public:
		using out_type = typename _type_helper::out_type;

		constexpr do_negate()
		{
		}
		[[nodiscard]] constexpr inline out_type operator()(const T_& val_) const
		{
			if constexpr (std::is_unsigned_v<T_>)
			{
				return -static_cast<typename _type_helper::cast_type>(val_);
			}
			else
			{
				return -val_;
			}
		}
	};
	template<>
	struct do_negate<void>
	{
	public:
		constexpr do_negate()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline std::invoke_result_t<do_negate<T_>, const T_&> operator()(const T_& val_) const
		{
			return do_negate<T_>()(val_);
		}
	};

	template<class X_, class Y_ = X_, class Z_ = X_>
	struct do_fmadd
	{
	private:
		using _x_uq = typename EmuCore::TMP::remove_ref_cv<X_>::type;
		using _y_uq = typename EmuCore::TMP::remove_ref_cv<Y_>::type;
		using _z_uq = typename EmuCore::TMP::remove_ref_cv<Z_>::type;

		static constexpr bool _any_fp = EmuCore::TMP::is_any_floating_point_v<_x_uq, _y_uq, _z_uq>;

		template<bool AnyFp_>
		struct _out_type_finder_template
		{
			// This will never be used due to specialisations
			using type = void;
			static constexpr bool is_valid = false;
		};

		template<>
		struct _out_type_finder_template<false>
		{
		private:
			using _x_mul_y_safe_result = EmuCore::TMP::safe_invoke_result<EmuCore::do_multiply<_x_uq, _y_uq>, const X_&, const Y_&>;
			using _x_mul_y_result = typename _x_mul_y_safe_result::type;
			using _x_mul_y_result_uq = typename EmuCore::TMP::remove_ref_cv<_x_mul_y_result>::type;
			using _safe_result = EmuCore::TMP::safe_invoke_result<EmuCore::do_add<_x_mul_y_result_uq, _z_uq>, _x_mul_y_result, const Z_&>;

		public:
			using type = typename _safe_result::type;
			static constexpr bool is_valid = _x_mul_y_safe_result::value && _safe_result::value;
		};

		template<>
		struct _out_type_finder_template<true>
		{
		public:
			using type = typename EmuCore::TMP::fma_result<const X_&, const Y_&, const Z_&>::type;
			static constexpr bool is_valid = EmuCore::TMP::valid_fma_args_v<const X_&, const Y_&, const Z_&>;
		};

		using _out_type_finder = _out_type_finder_template<_any_fp>;

	public:
		constexpr do_fmadd()
		{
		}

		template<typename = std::enable_if_t<_out_type_finder::is_valid>>
		[[nodiscard]] constexpr inline typename _out_type_finder::type operator()(const X_& x_, const Y_& y_, const Z_& z_) const
		{
			if constexpr (!_any_fp)
			{
				// No need for fused arithmetic since this is only to prevent floating-point rounds before an add, and we have no FP vals
				using mul_xy = EmuCore::do_multiply<_x_uq, _y_uq>;
				using mul_xy_result = std::invoke_result_t<mul_xy, const X_&, const Y_&>;
				using add_xy_z = EmuCore::do_add<mul_xy_result, _z_uq>;
				return add_xy_z()(mul_xy()(x_, y_), z_);
			}
			else
			{
				using std::fma;
				return fma(x_, y_, z_);
			}
		}
	};

	template<>
	struct do_fmadd<void, void, void>
	{
	private:
		template<typename X_, typename Y_, typename Z_>
		struct _result_with_args
		{
		private:
			using _x_uq = EmuCore::TMP::remove_ref_cv_t<X_>;
			using _y_uq = EmuCore::TMP::remove_ref_cv_t<Y_>;
			using _z_uq = EmuCore::TMP::remove_ref_cv_t<Z_>;
			using _to_invoke = EmuCore::do_fmadd<_x_uq, _y_uq, _z_uq>;
			using _safe_invoke_result = EmuCore::TMP::safe_invoke_result<_to_invoke, const X_&, const Y_&, const Z_&>;

		public:
			using func_type = _to_invoke;
			using type = typename _safe_invoke_result::type;
			static constexpr bool is_valid = _safe_invoke_result::value;
		};

	public:
		constexpr do_fmadd()
		{
		}

		template
		<
			typename X_,
			typename Y_,
			typename Z_,
			typename = std::enable_if_t<_result_with_args<X_, Y_, Z_>::is_valid>
		>
		constexpr inline typename _result_with_args<X_, Y_, Z_>::type operator()(const X_& x_, const Y_& y_, const Z_& z_) const
		{
			return typename _result_with_args<X_, Y_, Z_>::func_type()(x_, y_, z_);
		}
	};

	template<class X_, class Y_ = X_, class Z_ = X_>
	struct do_fmsub
	{
	private:
		static constexpr bool _z_may_be_negated = EmuCore::TMP::has_unary_minus_operator_v<const Z_&>;
		using _z_negate_result = typename EmuCore::TMP::unary_minus_operator_result<const Z_&>::type;
		static_assert(_z_may_be_negated, "Attempted to use an EmuCore::do_fmsub functor instance, but the provided Z_ argument cannot be negated. As fmsub is emulated through fmadd, const Z_& must be possible to negate via the unary operator-.");

		using _x_uq = typename EmuCore::TMP::remove_ref_cv<X_>::type;
		using _y_uq = typename EmuCore::TMP::remove_ref_cv<Y_>::type;
		using _neg_z_uq = typename EmuCore::TMP::remove_ref_cv<_z_negate_result>::type;

		using _fmadd = do_fmadd<_x_uq, _y_uq, _neg_z_uq>;
		using _safe_fmadd_invoke_result = EmuCore::TMP::safe_invoke_result<_fmadd, const X_&, const Y_&, _z_negate_result>;

	public:
		template<typename = std::enable_if_t<_z_may_be_negated && _safe_fmadd_invoke_result::value>>
		[[nodiscard]] constexpr inline typename _safe_fmadd_invoke_result::type operator()(const X_& x_, const Y_& y_, const Z_& z_) const
		{
			return _fmadd()(x_, y_, -z_);
		}
	};

	template<>
	struct do_fmsub<void, void, void>
	{
		private:
		template<typename X_, typename Y_, typename Z_>
		struct _result_with_args
		{
		private:
			using _x_uq = EmuCore::TMP::remove_ref_cv_t<X_>;
			using _y_uq = EmuCore::TMP::remove_ref_cv_t<Y_>;
			using _z_uq = EmuCore::TMP::remove_ref_cv_t<Z_>;
			using _to_invoke = EmuCore::do_fmsub<_x_uq, _y_uq, _z_uq>;
			using _safe_invoke_result = EmuCore::TMP::safe_invoke_result<_to_invoke, const X_&, const Y_&, const Z_&>;

		public:
			using func_type = _to_invoke;
			using type = typename _safe_invoke_result::type;
			static constexpr bool is_valid = _safe_invoke_result::value;
		};

	public:
		constexpr do_fmsub()
		{
		}

		template
		<
			typename X_,
			typename Y_,
			typename Z_,
			typename = std::enable_if_t<_result_with_args<X_, Y_, Z_>::is_valid>
		>
		constexpr inline typename _result_with_args<X_, Y_, Z_>::type operator()(const X_& x_, const Y_& y_, const Z_& z_) const
		{
			return typename _result_with_args<X_, Y_, Z_>::func_type()(x_, y_, z_);
		}
	};
#pragma endregion

#pragma region ARITHMETIC_OPERATOR_ASSIGN_FUNCTORS
	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_add_assign
	{
		using result_type = std::conditional_t
		<
			EmuCore::TMP::has_plus_assign_operator_v<Lhs_&, const Rhs_&>,
			EmuCore::TMP::plus_assign_operator_result_t<Lhs_&, const Rhs_&>,
			Lhs_&
		>;
		constexpr do_add_assign()
		{
		}
		constexpr inline result_type operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_plus_assign_operator_v<Lhs_&, const Rhs_&>)
			{
				return lhs_ += rhs_;
			}
			else
			{
				using const_op = do_add<Lhs_, Rhs_>;
				using const_op_result = std::invoke_result_t<const_op, Lhs_&, const Rhs_&>;
				if constexpr (std::is_assignable_v<Lhs_&, const_op_result>)
				{
					lhs_ = const_op()(lhs_, rhs_);
					return lhs_;
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<const_op_result>(), "Unable to perform add-assign operation via EmuCore::do_add_assign, as the provided Lhs_ type does not have a valid += operator, and cannot be assigned via the result of do_add in order to emulate such behaviour, when used with the provided Rhs_ argument.");
				}
			}
		}
	};
	template<>
	struct do_add_assign<void, void>
	{
		constexpr do_add_assign()
		{
		}
		template<typename Lhs_, typename Rhs_>
		constexpr inline std::invoke_result_t<do_add_assign<Lhs_, Rhs_>, Lhs_&, const Rhs_&> operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_add_assign<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_subtract_assign
	{
		using result_type = std::conditional_t
		<
			EmuCore::TMP::has_subtract_assign_operator_v<Lhs_&, const Rhs_&>,
			EmuCore::TMP::subtract_assign_operator_result_t<Lhs_&, const Rhs_&>,
			Lhs_&
		>;
		constexpr do_subtract_assign()
		{
		}
		constexpr inline result_type operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_subtract_assign_operator_v<Lhs_&, const Rhs_&>)
			{
				return lhs_ -= rhs_;
			}
			else
			{
				using const_op = do_subtract<Lhs_, Rhs_>;
				using const_op_result = std::invoke_result_t<const_op, Lhs_&, const Rhs_&>;
				if constexpr (std::is_assignable_v<Lhs_&, const_op_result>)
				{
					lhs_ = const_op()(lhs_, rhs_);
					return lhs_;
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<const_op_result>(), "Unable to perform subtract-assign operation via EmuCore::do_subtract_assign, as the provided Lhs_ type does not have a valid -= operator, and cannot be assigned via the result of do_subtract in order to emulate such behaviour, when used with the provided Rhs_ argument.");
				}
			}
		}
	};
	template<>
	struct do_subtract_assign<void, void>
	{
		constexpr do_subtract_assign()
		{
		}
		template<typename Lhs_, typename Rhs_>
		constexpr inline std::invoke_result_t<do_subtract_assign<Lhs_, Rhs_>, Lhs_&, const Rhs_&> operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_subtract_assign<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_multiply_assign
	{
		using result_type = std::conditional_t
		<
			EmuCore::TMP::has_multiply_assign_operator_v<Lhs_&, const Rhs_&>,
			EmuCore::TMP::multiply_assign_operator_result_t<Lhs_&, const Rhs_&>,
			Lhs_&
		>;
		constexpr do_multiply_assign()
		{
		}
		constexpr inline result_type operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_multiply_assign_operator_v<Lhs_&, const Rhs_&>)
			{
				return lhs_ *= rhs_;
			}
			else
			{
				using const_op = do_multiply<Lhs_, Rhs_>;
				using const_op_result = std::invoke_result_t<const_op, Lhs_&, const Rhs_&>;
				if constexpr (std::is_assignable_v<Lhs_&, const_op_result>)
				{
					lhs_ = const_op()(lhs_, rhs_);
					return lhs_;
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<const_op_result>(), "Unable to perform multiply-assign operation via EmuCore::do_multiply_assign, as the provided Lhs_ type does not have a valid *= operator, and cannot be assigned via the result of do_multiply in order to emulate such behaviour, when used with the provided Rhs_ argument.");
				}
			}
		}
	};
	template<>
	struct do_multiply_assign<void, void>
	{
		constexpr do_multiply_assign()
		{
		}
		template<typename Lhs_, typename Rhs_>
		constexpr inline std::invoke_result_t<do_multiply_assign<Lhs_, Rhs_>, Lhs_&, const Rhs_&> operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_multiply_assign<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_divide_assign
	{
		using result_type = std::conditional_t
		<
			EmuCore::TMP::has_divide_assign_operator_v<Lhs_&, const Rhs_&>,
			EmuCore::TMP::divide_assign_operator_result_t<Lhs_&, const Rhs_&>,
			Lhs_&
		>;
		constexpr do_divide_assign()
		{
		}
		constexpr inline result_type operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_divide_assign_operator_v<Lhs_&, const Rhs_&>)
			{
				return lhs_ /= rhs_;
			}
			else
			{
				using const_op = do_divide<Lhs_, Rhs_>;
				using const_op_result = std::invoke_result_t<const_op, Lhs_&, const Rhs_&>;
				if constexpr (std::is_assignable_v<Lhs_&, const_op_result>)
				{
					lhs_ = const_op()(lhs_, rhs_);
					return lhs_;
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<const_op_result>(), "Unable to perform divide-assign operation via EmuCore::do_divide_assign, as the provided Lhs_ type does not have a valid /= operator, and cannot be assigned via the result of do_divide in order to emulate such behaviour, when used with the provided Rhs_ argument.");
				}
			}
		}
	};
	template<>
	struct do_divide_assign<void, void>
	{
		constexpr do_divide_assign()
		{
		}
		template<typename Lhs_, typename Rhs_>
		constexpr inline std::invoke_result_t<do_divide_assign<Lhs_, Rhs_>, Lhs_&, const Rhs_&> operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_divide_assign<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_mod_assign
	{
		using result_type = std::conditional_t
		<
			EmuCore::TMP::has_mod_assign_operator_v<Lhs_&, const Rhs_&>,
			EmuCore::TMP::mod_assign_operator_result_t<Lhs_&, const Rhs_&>,
			Lhs_&
		>;
		constexpr do_mod_assign()
		{
		}
		constexpr inline result_type operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_mod_assign_operator_v<Lhs_&, const Rhs_&>)
			{
				return lhs_ %= rhs_;
			}
			else
			{
				using const_op = do_mod<Lhs_, Rhs_>;
				using const_op_result = std::invoke_result_t<const_op, Lhs_&, const Rhs_&>;
				if constexpr (std::is_assignable_v<Lhs_&, const_op_result>)
				{
					lhs_ = static_cast<Lhs_>(const_op()(lhs_, rhs_));
					return lhs_;
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<const_op_result>(), "Unable to perform modulo-divide-assign operation via EmuCore::do_mod_assign, as the provided Lhs_ type does not have a valid %= operator, and cannot be assigned via the result of do_mod in order to emulate such behaviour, when used with the provided Rhs_ argument.");
				}
			}
		}
	};
	template<>
	struct do_mod_assign<void, void>
	{
		constexpr do_mod_assign()
		{
		}
		template<typename Lhs_, typename Rhs_>
		constexpr inline std::invoke_result_t<do_mod_assign<Lhs_, Rhs_>, Lhs_&, const Rhs_&> operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_mod_assign<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};
#pragma endregion

#pragma region UNARY_ARITHMETIC_FUNCTORS
	/// <summary>
	/// <para> Functor to perform and output the result of a pre-increment on a value of type T_, with the format ++value. </para>
	/// <para> If a type does not implement the correct operator, this will attempt to emulate it by default with += operators if possible. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// </summary>
	template<typename T_>
	struct do_pre_increment
	{
		using result_type = std::conditional_t
		<
			EmuCore::TMP::has_pre_increment_operator_v<T_&>,
			EmuCore::TMP::pre_increment_operator_result_t<T_&>,
			T_&
		>;

		constexpr do_pre_increment()
		{
		}
		constexpr inline result_type operator()(T_& val_) const
		{
			if constexpr (EmuCore::TMP::has_pre_increment_operator_v<T_&>)
			{
				return ++val_;
			}
			else
			{
				EmuCore::do_add_assign<T_, decltype(1)>()(val_, 1);
				return val_;
			}
		}
	};
	template<>
	struct do_pre_increment<void>
	{
		constexpr do_pre_increment()
		{
		}
		template<typename T_>
		constexpr inline std::invoke_result_t<do_pre_increment<T_>, T_&> operator()(T_& val_) const
		{
			return do_pre_increment<T_>()(val_);
		}
	};

	/// <summary>
	/// <para> Functor to perform and output the result of a post-increment on a value of type T_, with the format value++. </para>
	/// <para> If a type does not implement the correct operator, this will attempt to emulate it by default with += operators if possible. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// </summary>
	template<typename T_>
	struct do_post_increment
	{
		using result_type = std::conditional_t
		<
			EmuCore::TMP::has_post_increment_operator_v<T_&>,
			EmuCore::TMP::post_increment_operator_result_t<T_&>,
			EmuCore::TMP::remove_ref_cv_t<T_>
		>;

		constexpr do_post_increment()
		{
		}
		constexpr inline result_type operator()(T_& val_) const
		{
			if constexpr (EmuCore::TMP::has_post_increment_operator_v<T_&>)
			{
				return val_++;
			}
			else
			{
				EmuCore::TMP::remove_ref_cv_t<T_> out_(val_);
				EmuCore::do_add_assign<T_, decltype(1)>()(val_, 1);
				return out_;
			}
		}
	};
	template<>
	struct do_post_increment<void>
	{
		constexpr do_post_increment()
		{
		}
		template<typename T_>
		constexpr inline std::invoke_result_t<do_post_increment<T_>, T_&> operator()(T_& val_) const
		{
			return do_post_increment<T_>()(val_);
		}
	};

	/// <summary>
	/// <para> Functor to perform and output the result of a pre-decrement on a value of type T_, with the format --value. </para>
	/// <para> If a type does not implement the correct operator, this will attempt to emulate it by default with -= operators if possible. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// </summary>
	template<typename T_>
	struct do_pre_decrement
	{
		using result_type = std::conditional_t
		<
			EmuCore::TMP::has_pre_decrement_operator_v<T_&>,
			EmuCore::TMP::pre_decrement_operator_result_t<T_&>,
			T_&
		>;

		constexpr do_pre_decrement()
		{
		}
		constexpr inline result_type operator()(T_& val_) const
		{
			if constexpr (EmuCore::TMP::has_pre_decrement_operator_v<T_&>)
			{
				return --val_;
			}
			else
			{
				EmuCore::do_subtract_assign<T_, decltype(1)>()(val_, 1);
				return val_;
			}
		}
	};
	template<>
	struct do_pre_decrement<void>
	{
		constexpr do_pre_decrement()
		{
		}
		template<typename T_>
		constexpr inline std::invoke_result_t<do_pre_decrement<T_>, T_&> operator()(T_& val_) const
		{
			return do_pre_decrement<T_>()(val_);
		}
	};

	/// <summary>
	/// <para> Functor to perform and output the result of a post-decrement on a value of type T_, with the format value--. </para>
	/// <para> If a type does not implement the correct operator, this will attempt to emulate it by default with -= operators if possible. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// </summary>
	template<typename T_>
	struct do_post_decrement
	{
		using result_type = std::conditional_t
		<
			EmuCore::TMP::has_post_decrement_operator_v<T_&>,
			EmuCore::TMP::post_decrement_operator_result_t<T_&>,
			EmuCore::TMP::remove_ref_cv_t<T_>
		>;

		constexpr do_post_decrement()
		{
		}
		constexpr inline result_type operator()(T_& val_) const
		{
			if constexpr (EmuCore::TMP::has_post_decrement_operator_v<T_&>)
			{
				return val_--;
			}
			else
			{
				EmuCore::TMP::remove_ref_cv_t<T_> out_(val_);
				EmuCore::do_subtract_assign<T_, decltype(1)>()(val_, 1);
				return out_;
			}
		}
	};
	template<>
	struct do_post_decrement<void>
	{
		constexpr do_post_decrement()
		{
		}
		template<typename T_>
		constexpr inline std::invoke_result_t<do_post_decrement<T_>, T_&> operator()(T_& val_) const
		{
			return do_post_decrement<T_>()(val_);
		}
	};
#pragma endregion

#pragma region RECIPROCAL_FUNCTORS
	template<typename In_>
	struct do_reciprocal
	{
	private:
		using _fp_type = EmuCore::TMP::remove_ref_cv_t<EmuCore::TMP::floating_point_equivalent_t<In_>>;
		using _in_uq = EmuCore::TMP::remove_ref_cv_t<In_>;
		using _make_div = EmuCore::TMP::safe_template_instantiate<EmuCore::do_divide, _fp_type, _in_uq>;
		using _make_one = EmuCore::TMP::try_make_constant<_fp_type, 1>;
		using _div = typename _make_div::type;
		using _make_div_result = EmuCore::TMP::safe_invoke_result<_div, _fp_type, const In_&>;

	public:
		using out_type = typename _make_div_result::type;

		constexpr do_reciprocal()
		{
		}

		[[nodiscard]] constexpr inline out_type operator()(const In_& in_) const
		{
			if constexpr(!std::is_void_v<_fp_type>)
			{
				if constexpr (_make_div::value)
				{
					if constexpr (_make_div_result::value)
					{
						if constexpr (_make_one::is_valid)
						{
							return _div()(_make_one::get(), in_);
						}
						else
						{
							static_assert
							(
								EmuCore::TMP::get_false<_make_one>(),
								"Attempted to calculate a reciprocal via EmuCore::do_reciprocal, but the unqualified floating-point equivalent to In_ could not be used to generate a constant of 1 via EmuCore::TMP::try_make_constant."
							);
						}
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<_make_div_result>(),
							"Attempted to calculate a reciprocal via EmuCore::do_reciprocal, but the generated instance of EmuCore::do_divide could not be invoked with a value of the unqualified floating-point equivalent to In_ and a const reference to In_ as arguments."
						);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<_make_div>(),
						"Attempted to calculate a reciprocal via EmuCore::do_reciprocal, but an instance of EmuCore::do_divide could not be instantiated with the unqualified floating-point equivalent of In_ and the unqualified form of In_ as type arguments."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<_fp_type>(),
					"Attempted to calculate a reciprocal via EmuCore::do_reciprocal, but the provided In_ type does not have a floating-point equivalent defined by EmuCore::TMP::floating_point_equivalent."
				);
			}
		}
	};

	template<>
	struct do_reciprocal<void>
	{
		constexpr do_reciprocal()
		{
		}

		template<typename In_>
		constexpr inline std::invoke_result_t<do_reciprocal<In_>, const In_&> operator()(const In_& in_) const
		{
			return do_reciprocal<In_>()(in_);
		}
	};
#pragma endregion

#pragma region RADIAN_AND_DEGREE_ARITHMETIC_FUNCTORS
	/// <summary>
	/// <para> Template functor for converting a value of type T_ from radians to degrees. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// </summary>
	template<typename T_>
	struct do_rads_to_degs
	{
		constexpr do_rads_to_degs()
		{
		}
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			return EmuCore::Pi::RadsToDegs<T_>(val_);
		}
	};
	template<>
	struct do_rads_to_degs<void>
	{
		constexpr do_rads_to_degs()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			return do_rads_to_degs<T_>()(val_);
		}
	};

	/// <summary>
	/// <para> Template functor for converting a value of type T_ from degrees to radians. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// </summary>
	template<typename T_>
	struct do_degs_to_rads
	{
		constexpr do_degs_to_rads()
		{
		}
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			return EmuCore::Pi::DegsToRads<T_>(val_);
		}
	};
	template<>
	struct do_degs_to_rads<void>
	{
		constexpr do_degs_to_rads()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			return do_degs_to_rads<T_>()(val_);
		}
	};
#pragma endregion

#pragma region TRIG_ARITHMETIC_FUNCTORS
	/// <summary>
	/// <para> Template cos functor, used to perform the cos(value) function on a value of type T_. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para> May be constexpr, but does not provide constexpr guarantee; for such behaviour, use the `do_cos_constexpr` template. </para>
	/// </summary>
	template<typename T_>
	struct do_cos
	{
		using out_t = typename EmuCore::TMP::first_floating_point<T_, float>::type;
		constexpr do_cos()
		{
		}
		[[nodiscard]] constexpr inline out_t operator()(const T_& t_) const
		{
			return EmuCore::DoMatchingCos<out_t, T_>(t_);
		}
	};
	template<>
	struct do_cos<void>
	{
		constexpr do_cos()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline std::invoke_result_t<do_cos<T_>, const T_&> operator()(const T_& t_) const
		{
			return do_cos<T_>()(t_);
		}
	};

	/// <summary>
	/// <para> Template acos functor, used to perform the acos(value) function on a value of type T_. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para> May be constexpr, but does not provide constexpr guarantee; for such behaviour, use the `do_acos_constexpr` template. </para>
	/// </summary>
	template<typename T_>
	struct do_acos
	{
		using out_t = typename EmuCore::TMP::first_floating_point<T_, float>::type;
		constexpr do_acos()
		{
		}
		[[nodiscard]] constexpr inline out_t operator()(const T_& t_) const
		{
			return EmuCore::DoMatchingAcos<out_t, T_>(t_);
		}
	};
	template<>
	struct do_acos<void>
	{
		constexpr do_acos()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline std::invoke_result_t<do_acos<T_>, const T_&> operator()(const T_& t_) const
		{
			return do_acos<T_>()(t_);
		}
	};

	/// <summary>
	/// <para> Template sin functor, used to perform the sin(value) function on a value of type T_. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para> May be constexpr, but does not provide constexpr guarantee; for such behaviour, use the `do_sin_constexpr` template. </para>
	/// </summary>
	template<typename T_>
	struct do_sin
	{
		using out_t = typename EmuCore::TMP::first_floating_point<T_, float>::type;
		constexpr do_sin()
		{
		}
		[[nodiscard]] constexpr inline out_t operator()(const T_& t_) const
		{
			return EmuCore::DoMatchingSin<out_t, T_>(t_);
		}
	};
	template<>
	struct do_sin<void>
	{
		constexpr do_sin()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline std::invoke_result_t<do_sin<T_>, const T_&> operator()(const T_& t_) const
		{
			return do_sin<T_>()(t_);
		}
	};

	/// <summary>
	/// <para> Template asin functor, used to perform the asin(value) function on a value of type T_. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para> May be constexpr, but does not provide constexpr guarantee; for such behaviour, use the `do_asin_constexpr` template. </para>
	/// </summary>
	template<typename T_>
	struct do_asin
	{
		using out_t = typename EmuCore::TMP::first_floating_point<T_, float>::type;
		constexpr do_asin()
		{
		}
		[[nodiscard]] constexpr inline out_t operator()(const T_& t_) const
		{
			return EmuCore::DoMatchingAsin<out_t, T_>(t_);
		}
	};
	template<>
	struct do_asin<void>
	{
		constexpr do_asin()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline std::invoke_result_t<do_asin<T_>, const T_&> operator()(const T_& t_) const
		{
			return do_asin<T_>()(t_);
		}
	};

	/// <summary>
	/// <para> Template tan functor, used to perform the tan(value) function on a value of type T_. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para> May be constexpr, but does not provide constexpr guarantee; for such behaviour, use the `do_tan_constexpr` template. </para>
	/// </summary>
	template<typename T_>
	struct do_tan
	{
		using out_t = typename EmuCore::TMP::first_floating_point<T_, float>::type;
		constexpr do_tan()
		{
		}
		[[nodiscard]] constexpr inline out_t operator()(const T_& t_) const
		{
			return EmuCore::DoMatchingTan<out_t, T_>(t_);
		}
	};
	template<>
	struct do_tan<void>
	{
		constexpr do_tan()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline std::invoke_result_t<do_tan<T_>, const T_&> operator()(const T_& t_) const
		{
			return do_tan<T_>()(t_);
		}
	};

	/// <summary>
	/// <para> Template atan functor, used to perform the atan(value) function on a value of type T_. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para> May be constexpr, but does not provide constexpr guarantee; for such behaviour, use the `do_atan_constexpr` template. </para>
	/// </summary>
	template<typename T_>
	struct do_atan
	{
		using out_t = typename EmuCore::TMP::first_floating_point<T_, float>::type;
		constexpr do_atan()
		{
		}
		[[nodiscard]] constexpr inline out_t operator()(const T_& t_) const
		{
			return EmuCore::DoMatchingAtan<out_t, T_>(t_);
		}
	};
	template<>
	struct do_atan<void>
	{
		constexpr do_atan()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline std::invoke_result_t<do_atan<T_>, const T_&> operator()(const T_& t_) const
		{
			return do_atan<T_>()(t_);
		}
	};

	/// <summary>
	/// <para> Template atan2 functor, used to perform the atan(y, x) function on a value of type T_. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para> May be constexpr, but does not provide constexpr guarantee; for such behaviour, use the `do_atan2_constexpr` template. </para>
	/// </summary>
	template<typename T_>
	struct do_atan2
	{
		using out_t = typename EmuCore::TMP::first_floating_point<T_, float>::type;
		constexpr do_atan2()
		{
		}
		[[nodiscard]] constexpr inline out_t operator()(const T_& y_, const T_& x_) const
		{
			return EmuCore::DoMatchingAtan2<out_t, T_>(y_, x_);
		}
	};
	template<>
	struct do_atan2<void>
	{
		constexpr do_atan2()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline std::invoke_result_t<do_atan2<T_>, const T_&, const T_&> operator()(const T_& y_, const T_& x_) const
		{
			return do_atan2<T_>()(y_, x_);
		}
	};
#pragma endregion

#pragma region CONSTEXPR_TRIG_ARITHMETIC_FUNCTORS
	/// <summary>
	/// <para> Template cos functor, used to perform the cos(value) function on a value of type T_. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para>
	///		If T_ is constexpr-evaluable, this provides a guarantee to perform a constexpr implementation of cos if possible. 
	///		Specialisations are expected to follow this guarantee.
	/// </para>
	/// <para> By default, uses Taylor Series implmentation for the specified number of iterations specified by NumIterations_, which defaults to 3. </para>
	/// <para>
	///		DoMod_ is true by default, and will only have an effect on values greater than 6.28319. 
	///		In cases where input ranges are unknown, it is recommended to keep it as true.
	///		In cases where you know inputs will not exceed the provided range, it will do nothing and thus setting the argument to false will avoid a useless fmod operation.
	/// </para>
	/// </summary>
	template<typename T_, std::size_t NumIterations_ = 3, bool DoMod_ = true>
	struct do_cos_constexpr
	{
	public:
		static_assert(NumIterations_ != 0, "Attempted to create an EmuCore::do_cos_constexpr instance with 0 iterations. At least 1 iteration is required.");

		using out_t = std::conditional_t
		<
			std::is_arithmetic_v<T_>,
			EmuCore::TMP::first_floating_point_t<T_, float>,
			T_
		>;
		static constexpr out_t full_circle = EmuCore::Pi::DegsToRads_v<out_t, int, 360>;

		constexpr do_cos_constexpr() : add_(), sub_(), mul_(), div_(), mod_()
		{
		}
		constexpr inline out_t operator()(T_ val_) const
		{
			if constexpr (DoMod_)
			{
				out_t rounded_ = static_cast<out_t>(mod_(static_cast<out_t>(val_), full_circle));
				return _calculate_taylor_series<NumIterations_>(rounded_);
			}
			else
			{
				if constexpr (std::is_same_v<T_, out_t>)
				{
					return _calculate_taylor_series<NumIterations_>(val_);
				}
				else
				{
					out_t val_as_out_t_ = static_cast<out_t>(val_);
					return _calculate_taylor_series<NumIterations_>(val_as_out_t_);
				}
			}
		}
	private:
		using Add_ = EmuCore::do_add<out_t, out_t>;
		using Sub_ = EmuCore::do_subtract<out_t, out_t>;
		using Mul_ = EmuCore::do_multiply<out_t, out_t>;
		using Div_ = EmuCore::do_divide<out_t, out_t>;
		using Mod_ = EmuCore::do_mod<out_t, out_t>;
		Add_ add_;
		Sub_ sub_;
		Mul_ mul_;
		Div_ div_;
		Mod_ mod_;

		template<std::size_t NumIterations_>
		constexpr inline out_t _calculate_taylor_series(const out_t& in_) const
		{
			out_t out_ = out_t(1);
			out_t pow_ = out_t(1);
			out_t in_sqr_ = mul_(in_, in_);
			_calculate_taylor_series<0, NumIterations_, 2>(in_sqr_, out_, pow_);
			return out_;
		}
		template<std::size_t Iteration_, std::size_t End_, std::size_t PowExponent_>
		constexpr inline void _calculate_taylor_series(const out_t& in_sqr_, out_t& out_, out_t& pow_) const
		{
			if constexpr (Iteration_ < End_)
			{
				pow_ = mul_(in_sqr_, pow_);
				const out_t derivative_ = div_(pow_, EmuCore::factorial_v<PowExponent_, out_t>);
				if constexpr (Iteration_ & 1)
				{
					out_ = add_(out_, derivative_);
				}
				else
				{
					out_ = sub_(out_, derivative_);
				}
				_calculate_taylor_series<Iteration_ + 1, End_, PowExponent_ + 2>(in_sqr_, out_, pow_);
			}
		}
	};
	template<std::size_t NumIterations_, bool DoMod_>
	struct do_cos_constexpr<void, NumIterations_, DoMod_>
	{
		constexpr do_cos_constexpr()
		{
		}
		template<bool DoMod_ = true, typename T_>
		constexpr inline std::invoke_result_t<do_cos_constexpr<T_, NumIterations_, DoMod_>, const T_&> operator()(const T_& val_) const
		{
			return do_cos_constexpr<T_, NumIterations_, DoMod_>()(val_);
		}
	};

	/// <summary>
	/// <para> Template sin functor, used to perform the sin(value) function on a value of type T_. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para>
	///		If T_ is constexpr-evaluable, this provides a guarantee to perform a constexpr implementation of sin if possible. 
	///		Specialisations are expected to follow this guarantee.
	/// </para>
	/// <para> By default, uses Taylor Series implmentation for the specified number of iterations specified by NumIterations_, which defaults to 3. </para>
	/// <para>
	///		DoMod_ is true by default, and will only have an effect on values greater than 6.28319. 
	///		In cases where input ranges are unknown, it is recommended to keep it as true.
	///		In cases where you know inputs will not exceed the provided range, it will do nothing and thus setting the argument to false will avoid a useless fmod operation.
	/// </para>
	/// </summary>
	template<typename T_, std::size_t NumIterations_ = 3, bool DoMod_ = true>
	struct do_sin_constexpr
	{
		static_assert(NumIterations_ != 0, "Attempted to create an EmuCore::do_sin_constexpr instance with 0 iterations. At least 1 iteration is required.");

		using out_t = std::conditional_t
		<
			std::is_arithmetic_v<T_>,
			EmuCore::TMP::first_floating_point_t<T_, float>,
			T_
		>;
		static constexpr out_t full_circle = EmuCore::Pi::DegsToRads_v<float, int, 360>;

		constexpr do_sin_constexpr() : add_(), sub_(), mul_(), div_(), mod_()
		{
		}
		constexpr inline out_t operator()(T_ val_) const
		{
			if constexpr (DoMod_)
			{
				out_t rounded_ = mod_(static_cast<out_t>(val_), full_circle);
				return _calculate_taylor_series<NumIterations_>(rounded_);
			}
			else
			{
				if constexpr (std::is_same_v<T_, out_t>)
				{
					return _calculate_taylor_series<NumIterations_>(val_);
				}
				else
				{
					out_t val_as_out_t_ = static_cast<out_t>(val_);
					return _calculate_taylor_series<NumIterations_>(val_as_out_t_);
				}
			}
		}

	private:
		using Add_ = EmuCore::do_add<out_t, out_t>;
		using Sub_ = EmuCore::do_subtract<out_t, out_t>;
		using Mul_ = EmuCore::do_multiply<out_t, out_t>;
		using Div_ = EmuCore::do_divide<out_t, out_t>;
		using Mod_ = EmuCore::do_mod<out_t, out_t>;
		Add_ add_;
		Sub_ sub_;
		Mul_ mul_;
		Div_ div_;
		Mod_ mod_;

		template<std::size_t NumIterations_>
		constexpr inline out_t _calculate_taylor_series(const out_t& in_) const
		{
			out_t out_ = in_;
			out_t pow_ = in_;
			out_t in_sqr_ = mul_(in_, in_);
			_calculate_taylor_series<0, NumIterations_, 3>(in_sqr_, out_, pow_);
			return out_;
		}
		template<std::size_t Iteration_, std::size_t End_, std::size_t PowExponent_>
		constexpr inline void _calculate_taylor_series(const out_t& in_sqr_, out_t& out_, out_t& pow_) const
		{
			if constexpr (Iteration_ < End_)
			{
				pow_ = mul_(in_sqr_, pow_);
				const out_t derivative_ = div_(pow_, EmuCore::factorial_v<PowExponent_, out_t>);
				if constexpr (Iteration_ & 1)
				{
					out_ = add_(out_, derivative_);
				}
				else
				{
					out_ = sub_(out_, derivative_);
				}
				_calculate_taylor_series<Iteration_ + 1, End_, PowExponent_ + 2>(in_sqr_, out_, pow_);
			}
		}
	};
	template<std::size_t NumIterations_, bool DoMod_>
	struct do_sin_constexpr<void, NumIterations_, DoMod_>
	{
		constexpr do_sin_constexpr()
		{
		}
		template<typename T_>
		constexpr inline std::invoke_result_t<do_sin_constexpr<T_, NumIterations_, DoMod_>, const T_&> operator()(const T_& val_) const
		{
			return do_sin_constexpr<T_, NumIterations_, DoMod_>()(val_);
		}
	};
	/// <summary>
	/// <para> Template sin functor, used to perform the sin(value) function on a value of type T_. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para>
	///		If T_ is constexpr-evaluable, this provides a guarantee to perform a constexpr implementation of sin if possible. 
	///		Specialisations are expected to follow this guarantee.
	/// </para>
	/// <para> By default, uses the results of cos and sin to create the result of tan. </para>
	/// <para>
	///		DoMod_ is true by default, and will only have an effect on values greater than 6.28319. 
	///		In cases where input ranges are unknown, it is recommended to keep it as true.
	///		In cases where you know inputs will not exceed the provided range, it will do nothing and thus setting the argument to false will avoid a useless fmod operation.
	/// </para>
	/// </summary>
	template<typename T_, std::size_t NumIterations_ = 3, bool DoMod_ = true>
	struct do_tan_constexpr
	{
	public:
		static_assert(NumIterations_ != 0, "Attempted to create an EmuCore::do_tan_constexpr instance with 0 iterations. At least 1 iteration is required.");

		using out_t = std::conditional_t
		<
			std::is_arithmetic_v<T_>,
			EmuCore::TMP::first_floating_point_t<T_, float>,
			T_
		>;
		static constexpr out_t full_circle = EmuCore::Pi::DegsToRads_v<out_t, int, 360>;

		constexpr do_tan_constexpr() : cos_(), sin_(), div_(), mod_()
		{
		}
		constexpr inline out_t operator()(const T_& val_) const
		{
			if constexpr (DoMod_)
			{
				out_t rounded_ = mod_(static_cast<out_t>(val_), full_circle);
				cos_t cosine_ = cos_(val_);
				sin_t sine_ = sin_(val_);
				return static_cast<out_t>(div_(sine_, cosine_));
			}
			else
			{
				cos_t cosine_ = cos_(val_);
				sin_t sine_ = sin_(val_);
				return static_cast<out_t>(div_(sine_, cosine_));
			}
		}

	private:
		using cos_sin_passed_type = std::conditional_t<DoMod_, out_t, T_>;
		using cos_calc = do_cos_constexpr<cos_sin_passed_type, NumIterations_, false>;
		using sin_calc = do_sin_constexpr<cos_sin_passed_type, NumIterations_, false>;
		using cos_t = typename cos_calc::out_t;
		using sin_t = typename sin_calc::out_t;
		using divider = do_divide<sin_t, cos_t>;
		using modder = do_mod<out_t, out_t>;

		cos_calc cos_;
		sin_calc sin_;
		divider div_;
		modder mod_;

	};
	template<std::size_t NumIterations_, bool DoMod_>
	struct do_tan_constexpr<void, NumIterations_, DoMod_>
	{
		constexpr do_tan_constexpr()
		{
		}
		template<typename T_>
		constexpr inline std::invoke_result_t<do_tan_constexpr<T_, NumIterations_, DoMod_>, const T_&> operator()(const T_& val_) const
		{
			return do_tan_constexpr<T_, NumIterations_, DoMod_>()(val_);
		}
	};
#pragma endregion

#pragma region CONSTEXPR_INVERSE_TRIG_FUNCTORS
	/// <summary>
	/// <para> Template arctangent functor, used to perform the atan(y / x) function on a value of type T_. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para>
	///		If T_ is constexpr-evaluable, this provides a guarantee to perform a constexpr implementation of atan2 if possible. 
	///		Specialisations are expected to follow this guarantee.
	/// </para>
	/// </summary>
	template<typename T_>
	struct do_atan2_constexpr
	{
	public:
		using out_t = std::conditional_t
		<
			std::is_arithmetic_v<T_>,
			EmuCore::TMP::first_floating_point_t<T_, float>,
			T_
		>;

	private:
		using add_func = EmuCore::do_add<out_t, out_t>;
		using sub_func = EmuCore::do_subtract<out_t, out_t>;
		using mul_func = EmuCore::do_multiply<out_t, out_t>;
		using div_func = EmuCore::do_divide<out_t, out_t>;

	public:
		constexpr do_atan2_constexpr()
		{
		}
		constexpr inline out_t operator()(T_ y_, T_ x_) const
		{
			// Approxiation adapted from NVIDIA reference @ https://developer.download.nvidia.com/cg/atan2.html
			out_t abs_x = static_cast<out_t>(x_);
			out_t abs_y = static_cast<out_t>(y_);
			bool x_neg = EmuCore::do_cmp_less<out_t, out_t>()(abs_x, out_t(0));
			bool y_neg = EmuCore::do_cmp_less<out_t, out_t>()(abs_y, out_t(0));
			abs_x = _abs(abs_x, x_neg);
			abs_y = _abs(abs_y, y_neg);
			bool abs_y_greater = abs_y > abs_x;

			out_t t3 = abs_x;
			out_t t1 = abs_y;
			out_t t0 = _min_or_max<true>(abs_x, abs_y);	// t0 = max(abs_x, abs_y)
			t1 = _min_or_max<false>(abs_x, abs_y);	// t1 = min(abs_x, abs_y)
			t3 = div_func()(out_t(1), t0);
			t3 = mul_func()(t1, t3);

			out_t t4 = mul_func()(t3, t3);
			t0 = out_t(-0.013480470);
			t0 = add_func()(mul_func()(t0, t4), out_t(0.057477314));
			t0 = sub_func()(mul_func()(t0, t4), out_t(0.121239071));
			t0 = add_func()(mul_func()(t0, t4), out_t(0.195635925));
			t0 = sub_func()(mul_func()(t0, t4), out_t(0.332994597));
			t0 = add_func()(mul_func()(t0, t4), out_t(0.999995630));
			t3 = mul_func()(t0, t3);

			t3 = add_func() // t3 = abs_y_greater ? ((pi / 2) - t3) : t3
			(
				mul_func()(static_cast<out_t>(abs_y_greater), sub_func()(EmuCore::Pi::HALF_PI<out_t>, t3)),
				mul_func()(static_cast<out_t>(!abs_y_greater), t3)
			);
			t3 = add_func() // t3 = x_neg ? (pi - t3) : t3
			(
				mul_func()(static_cast<out_t>(x_neg), sub_func()(EmuCore::Pi::PI<out_t>, t3)),
				mul_func()(static_cast<out_t>(!x_neg), t3)
			);
			return _abs(t3, y_neg);
		}

	private:
		[[nodiscard]] static constexpr inline auto _abs(const out_t& in_, bool is_negative_)
		{
			// Branchless absolute operation
			return mul_func()
			(
				in_,
				add_func()
				(
					out_t(!is_negative_),
					mul_func()(out_t(-1), out_t(is_negative_))
				)
			);
		}

		template<bool IsMax_>
		[[nodiscard]] static constexpr inline decltype(auto) _min_or_max(const out_t& a_, const out_t& b_)
		{
			// Branchless min/max operation, typically faster (if not matching speed) on test hardware
			using comparator = typename std::conditional<IsMax_, EmuCore::do_cmp_greater<out_t, out_t>, EmuCore::do_cmp_less<out_t, out_t>>::type;
			bool cmp_result = comparator()(a_, b_);
			return add_func()
			(
				mul_func()(static_cast<out_t>(cmp_result), a_),
				mul_func()(static_cast<out_t>(!cmp_result), b_)
			);
		}
	};

	template<>
	struct do_atan2_constexpr<void>
	{
		constexpr do_atan2_constexpr()
		{
		}
		template<typename T_>
		constexpr inline std::invoke_result_t<do_atan2_constexpr<T_>, const T_&, const T_&> operator()(const T_& y_, const T_& x_) const
		{
			return do_atan2_constexpr<T_>()(y_, x_);
		}
	};


	/// <summary>
	/// <para> Template arctangent functor, used to perform the atan(value) function on a value of type T_. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para>
	///		If T_ is constexpr-evaluable, this provides a guarantee to perform a constexpr implementation of atan if possible. 
	///		Specialisations are expected to follow this guarantee.
	/// </para>
	/// </summary>
	template<typename T_>
	struct do_atan_constexpr
	{
		using out_t = std::conditional_t
		<
			std::is_arithmetic_v<T_>,
			EmuCore::TMP::first_floating_point_t<T_, float>,
			T_
		>;
		using atan2_func = EmuCore::do_atan2_constexpr<out_t>;

		constexpr do_atan_constexpr()
		{
		}
		constexpr inline out_t operator()(T_ val_) const
		{
			if constexpr (std::is_same_v<T_, out_t>)
			{
				return atan2_func()(val_, out_t(1));
			}
			else
			{
				return atan2_func()(static_cast<out_t>(val_), out_t(1));
			}
		}
	};

	template<>
	struct do_atan_constexpr<void>
	{
		constexpr do_atan_constexpr()
		{
		}
		template<typename T_>
		constexpr inline std::invoke_result_t<do_atan_constexpr<T_>, const T_&> operator()(const T_& val_) const
		{
			return do_atan_constexpr<T_>()(val_);
		}
	};

	/// <summary>
	/// <para> Template arcsin functor, used to perform the asin(value) function on a value of type T_. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para>
	///		If T_ is constexpr-evaluable, this provides a guarantee to perform a constexpr implementation of asin if possible. 
	///		Specialisations are expected to follow this guarantee.
	/// </para>
	/// </summary>
	template<typename T_>
	struct do_asin_constexpr
	{
		using out_t = std::conditional_t
		<
			std::is_arithmetic_v<T_>,
			EmuCore::TMP::first_floating_point_t<T_, float>,
			T_
		>;

		constexpr do_asin_constexpr() : add_(), mul_(), sub_()
		{
		}
		constexpr inline out_t operator()(T_ val_) const
		{
			if constexpr (std::is_same_v<T_, out_t>)
			{
				return _calculate_asin(val_);
			}
			else
			{
				out_t val_as_out_t_ = static_cast<out_t>(val_);
				return _calculate_asin(val_as_out_t_);
			}
		}

	private:
		using Add_ = EmuCore::do_add<out_t, out_t>;
		using Mul_ = EmuCore::do_multiply<out_t, out_t>;
		using Sub_ = EmuCore::do_subtract<out_t, out_t>;
		Add_ add_;
		Mul_ mul_;
		Sub_ sub_;

		constexpr inline out_t _calculate_asin(const out_t& in_) const
		{
			// Approxiation adapted from NVIDIA reference @ https://developer.download.nvidia.com/cg/asin.html
			out_t one = out_t(1);
			bool is_neg = in_ < 0;
			out_t abs_in = mul_(in_, static_cast<out_t>(!is_neg) + (static_cast<out_t>(-1) * is_neg)); // abs_in = is_neg ? -in_ : in_
			out_t result = out_t(-0.0187293);
			result = mul_(result, abs_in);
			result = add_(result, out_t(0.0742610));
			result = mul_(result, abs_in);
			result = sub_(result, out_t(0.2121144));
			result = mul_(result, abs_in);
			result = add_(result, out_t(1.5707288));
			result = sub_(EmuCore::Pi::HALF_PI<out_t>, mul_(EmuCore::do_sqrt_constexpr<out_t>()(sub_(one, abs_in)), result));
			return sub_(result, mul_(out_t(2), mul_(is_neg, result)));
		}
	};
	template<>
	struct do_asin_constexpr<void>
	{
		constexpr do_asin_constexpr()
		{
		}
		template<typename T_>
		constexpr inline std::invoke_result_t<do_asin_constexpr<T_>, const T_&> operator()(const T_& val_) const
		{
			return do_asin_constexpr<T_>()(val_);
		}
	};

	/// <summary>
	/// <para> Template arccosine functor, used to perform the acos(value) function on a value of type T_. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para>
	///		If T_ is constexpr-evaluable, this provides a guarantee to perform a constexpr implementation of acos if possible. 
	///		Specialisations are expected to follow this guarantee.
	/// </para>
	/// </summary>
	template<typename T_>
	struct do_acos_constexpr
	{
		using out_t = std::conditional_t
		<
			std::is_arithmetic_v<T_>,
			EmuCore::TMP::first_floating_point_t<T_, float>,
			T_
		>;

		constexpr do_acos_constexpr() : add_(), sub_(), mul_(), div_()
		{
		}
		constexpr inline out_t operator()(T_ val_) const
		{
			constexpr out_t pi_div_2 = EmuCore::Pi::PI<out_t> / 2;

			if constexpr (std::is_same_v<T_, out_t>)
			{
				return _calculate_acos(val_);
			}
			else
			{
				out_t val_as_out_t_ = static_cast<out_t>(val_);
				return _calculate_acos(val_as_out_t_);
			}
		}

	private:
		using Add_ = EmuCore::do_add<out_t, out_t>;
		using Sub_ = EmuCore::do_subtract<out_t, out_t>;
		using Mul_ = EmuCore::do_multiply<out_t, out_t>;
		using Div_ = EmuCore::do_divide<out_t, out_t>;
		Add_ add_;
		Sub_ sub_;
		Mul_ mul_;
		Div_ div_;

		constexpr inline out_t _calculate_acos(const out_t& in_) const
		{
			// Approximation adapted from NVIDIA reference @ https://developer.download.nvidia.com/cg/acos.html
			bool is_neg = EmuCore::do_cmp_less<out_t, out_t>()(in_, out_t(0));
			out_t abs_in = mul_(in_, add_(static_cast<out_t>(!is_neg), (static_cast<out_t>(-1) * is_neg))); // abs_in = is_neg ? -in_ : in_
			out_t result = out_t(-0.0187293);
			result = mul_(result, abs_in);
			result = add_(result, out_t(0.0742610));
			result = mul_(result, abs_in);
			result = sub_(result, out_t(0.2121144));
			result = mul_(result, abs_in);
			result = add_(result, out_t(1.5707288));
			result = mul_(result, EmuCore::do_sqrt_constexpr<out_t>()(sub_(out_t(1), abs_in)));
			result = result - out_t(2) * static_cast<out_t>(is_neg) * result;
			return add_(result, mul_(is_neg, EmuCore::Pi::PI<out_t>));
		}
	};
	template<>
	struct do_acos_constexpr<void>
	{
		constexpr do_acos_constexpr()
		{
		}
		template<typename T_>
		constexpr inline std::invoke_result_t<do_acos_constexpr<T_>, const T_&> operator()(const T_& val_) const
		{
			return do_acos_constexpr<T_>()(val_);
		}
	};
#pragma endregion

#pragma region MISC_ARITHMETIC_FUNCTORS
	/// <summary>
	/// <para> Functor which may be used to perform linear interpolations. </para>
	/// <para> Takes 3 type arguments, however only one or two may be passed. B_ will be the same type as A_ if omitted. T_ will be float if omitted. </para>
	/// <para> Types should be considered for the equation A_ + ((B_ - A_) * T_). </para>
	/// <para> do_lerp&lt;void&gt;, do_lerp&lt;void, void&gt;, and do_lerp&lt;void, void, void&gt; are reserved for a generic specialisation of do_lerp. </para>
	/// </summary>
	/// <typeparam name="A_">Type used to represent a in the equation a + ((b - a) * t).</typeparam>
	/// <typeparam name="B_">Type used to represent b in the equation a + ((b - a) * t).</typeparam>
	/// <typeparam name="T_">Type used to represent t in the equation a + ((b - a) * t).</typeparam>
	template<class A_, class B_ = A_, class T_ = float>
	struct do_lerp
	{
		constexpr do_lerp()
		{
		}
		[[nodiscard]] constexpr inline auto operator()(const A_& a_, const B_& b_, const T_& t_) const
		{
			if constexpr
			(
				EmuCore::TMP::is_any_floating_point_v<A_, B_, T_> &&
				!EmuCore::TMP::are_all_comparisons_true<std::is_same, A_, B_, T_>::value
			)
			{
				using floating_point = typename EmuCore::TMP::largest_floating_point<A_, B_, T_>::type;
				floating_point a_cast_ = static_cast<floating_point>(a_);
				return a_cast_ + ((static_cast<floating_point>(b_) - a_cast_) * static_cast<floating_point>(t_));
			}
			else
			{
				return (a_ + ((b_ - a_) * t_));
			}
		}
	};
	/// <summary>
	/// <para> Reserved generic specialisation of do_lerp. </para>
	/// <para> Determines the specialisation to make use of when the function operator() is called, based on the 3 arguments when called. </para>
	/// </summary>
	template<>
	struct do_lerp<void, void, void>
	{
		constexpr do_lerp()
		{
		}
		template<class A_, class B_, class T_>
		[[nodiscard]] constexpr inline std::invoke_result_t<do_lerp<A_, B_, T_>, const A_&, const B_&, const T_&> operator()(const A_& a_, const B_& b_, const T_& t_) const
		{
			return do_lerp<A_, B_, T_>()(a_, b_, t_);
		}
	};	

	/// <summary>
	/// <para> Functor which may be used to perform linear interpolations, while also taking advantage of fused instructions where possible. </para>
	/// <para> Takes 3 type arguments, however only one or two may be passed. B_ will be the same type as A_ if omitted. T_ will be float if omitted. </para>
	/// <para> Types should be considered for the equation FMADD(t, b - a, a). </para>
	/// <para> do_lerp&lt;void&gt;, do_lerp&lt;void, void&gt;, and do_lerp&lt;void, void, void&gt; are reserved for a generic specialisation of do_lerp. </para>
	/// </summary>
	/// <typeparam name="A_">Type used to represent a in the equation FMADD(t, b - a, a).</typeparam>
	/// <typeparam name="B_">Type used to represent b in the equation FMADD(t, b - a, a).</typeparam>
	/// <typeparam name="T_">Type used to represent t in the equation FMADD(t, b - a, a).</typeparam>
	template<class A_, class B_ = A_, class T_ = float>
	struct do_fused_lerp
	{
		constexpr do_fused_lerp()
		{
		}
		[[nodiscard]] constexpr inline auto operator()(const A_& a_, const B_& b_, const T_& t_) const
		{
			using sub_func = EmuCore::do_subtract<B_, A_>;
			using sub_result = typename std::invoke_result<sub_func, const B_&, const A_&>::type;
			using fmadd_func = EmuCore::do_fmadd<T_, sub_result, A_>;
			return fmadd_func()(t_, sub_func()(b_, a_), a_);
		}
	};
	/// <summary>
	/// <para> Reserved generic specialisation of do_fused_lerp. </para>
	/// <para> Determines the specialisation to make use of when the function operator() is called, based on the 3 arguments when called. </para>
	/// </summary>
	template<>
	struct do_fused_lerp<void, void, void>
	{
		constexpr do_fused_lerp()
		{
		}
		template<class A_, class B_, class T_>
		[[nodiscard]] constexpr inline std::invoke_result_t<do_fused_lerp<A_, B_, T_>, const A_&, const B_&, const T_&> operator()(const A_& a_, const B_& b_, const T_& t_) const
		{
			return do_fused_lerp<A_, B_, T_>()(a_, b_, t_);
		}
	};

	/// <summary>
	/// <para> Template functor for finding the absolute value of a value of type T_. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// </summary>
	template<typename T_>
	struct do_abs
	{
		constexpr do_abs()
		{
		}

		constexpr inline T_ operator()(const T_& val_) const
		{
			return EmuCore::AbsConstexpr<T_>(val_);
		}
	};
	template<>
	struct do_abs<void>
	{
		constexpr do_abs()
		{
		}

		template<typename T_>
		constexpr inline std::invoke_result_t<do_abs<T_>, const T_&> operator()(const T_& val_) const
		{
			return do_abs<T_>()(val_);
		}
	};

	/// <summary> 
	/// <para> Functor for wrapping values that are assumed to lie in a normalised range 0:1, where -0.1 is wrapped to 0.9, and 1.1 wrapped to 0.1. </para>
	/// <para> If T_ is void, the correct specialisation of this functor will be invoked based on the argument passed on invocation. </para>
	/// <para> Default, non-specialised forms of this functor are presented in a branchless manner. </para>
	/// <para> If WrapToOne_ is TRUE: non-zero whole numbers will be wrapped to 1. </para>
	/// <para> If WrapToOne_ is FALSE: non-zero whole numbers will be wrapped to 0. </para>
	/// </summary>
	template<typename T_, bool WrapToOne_>
	struct do_normalised_wrap
	{
		constexpr do_normalised_wrap()
		{
		}

		[[nodiscard]] constexpr inline T_ operator()(T_ val_) const
		{
			constexpr T_ zero_ = T_(0);
			if constexpr (std::is_integral_v<T_>)
			{
				// Any non-zero integer will wrap to 1, so we just return whatever any non-zero would wrap to in that case
				if constexpr (WrapToOne_)
				{
					return static_cast<T_>(val_ != zero_);
				}
				else
				{
					return zero_;
				}
			}
			else
			{
				// More complex with non-integral types as we need to invert magnitude and direction of the fractions
				// --- E.g. -0.8 would wrap around to +0.2, so we need to perform that transformation
				constexpr T_ one_ = T_(1);
				if constexpr (!WrapToOne_)
				{
					// Subtraction of a trunc brings us into the non-inclusive range -1:1
					val_ = val_ - EmuCore::do_trunc_constexpr<T_>()(val_);

					// Value will be wrapped if positive, but we need to invert the magnitude if negative
					// --- This can be done by adding 1 (i.e. -0.9 -> 0.1)
					return val_ + (one_ * (val_ < zero_));
				}
				else
				{
					// Same as above, but addition of 1 is done if result is negative OR 0
					// --- This OR 0 only applies to the wrapped variant if it did not start at 0
					bool started_not_zero_ = val_ != zero_;
					val_ = val_ - EmuCore::do_trunc_constexpr<T_>()(val_);
					return val_ + (one_ * ((val_ <= zero_) && started_not_zero_));
				}
			}
		}
	};
	template<bool WrapToOne_>
	struct do_normalised_wrap<void, WrapToOne_>
	{
		constexpr do_normalised_wrap()
		{
		}

		template<typename T_>
		[[nodiscard]] constexpr inline std::invoke_result_t<do_normalised_wrap<T_, WrapToOne_>, T_&&> operator()(T_&& val_) const
		{
			return do_normalised_wrap<EmuCore::TMP::remove_ref_cv_t<T_>, WrapToOne_>()(std::forward<T_>(val_));
		}
	};
#pragma endregion
}

#endif
