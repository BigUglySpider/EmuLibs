#ifndef EMU_CORE_BITWISE_FUNCTORS_H_INC_
#define EMU_CORE_BITWISE_FUNCTORS_H_INC_ 1

#include "../TMPHelpers/OperatorChecks.h"
#include "../TMPHelpers/TypeConvertors.h"
#include "../TMPHelpers/Values.h"
#include <cstddef>
#include <functional>

namespace EmuCore
{
#pragma region CONST_BITWISE_FUNCTORS
	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_bitwise_and
	{
		constexpr do_bitwise_and()
		{
		}
		constexpr inline EmuCore::TMP::bitwise_and_operator_result_t<const Lhs_&, const Rhs_&> operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_bitwise_and_operator_v<const Lhs_&, const Rhs_&>)
			{
				return lhs_ & rhs_;
			}
			else if constexpr (std::is_floating_point_v<Lhs_>)
			{
				using uint_type = EmuCore::TMP::uint_of_size_t<sizeof(Lhs_)>;
				if constexpr (!std::is_same_v<uint_type, std::false_type>)
				{
					const uint_type as_uint_ = do_bitwise_and<uint_type, Rhs_>()(*reinterpret_cast<const uint_type*>(&lhs_), rhs_);
					return *reinterpret_cast<const Lhs_*>(&as_uint_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Lhs_>(), "Attempted to bitwise AND a floating-point type via default EmuCore::do_bitwise_and, but the provided Lhs_ type cannot be reliably reinterpreted as an integer to perform the operation.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Lhs_>(), "Attempted to bitwise AND via EmuCore::do_bitwise_and, but the provided Lhs_ type does not have a valid const & operator that takes a const Rhs_ arg.");
			}
		}
	};
	template<>
	struct do_bitwise_and<void, void>
	{
		constexpr do_bitwise_and()
		{
		}
		template<typename Lhs_, typename Rhs_>
		constexpr inline std::invoke_result_t<do_bitwise_and<Lhs_, Rhs_>, const Lhs_&, const Rhs_&> operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_bitwise_and<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_bitwise_or
	{
		constexpr do_bitwise_or()
		{
		}
		constexpr inline EmuCore::TMP::bitwise_or_operator_result_t<const Lhs_&, const Rhs_&> operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_bitwise_or_operator_v<const Lhs_&, const Rhs_&>)
			{
				return lhs_ | rhs_;
			}
			else if constexpr (std::is_floating_point_v<Lhs_>)
			{
				using uint_type = EmuCore::TMP::uint_of_size_t<sizeof(Lhs_)>;
				if constexpr (!std::is_same_v<uint_type, std::false_type>)
				{
					const uint_type as_uint_ = do_bitwise_or<uint_type, Rhs_>()(*reinterpret_cast<const uint_type*>(&lhs_), rhs_);
					return *reinterpret_cast<const Lhs_*>(&as_uint_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Lhs_>(), "Attempted to bitwise OR a floating-point type via default EmuCore::do_bitwise_or, but the provided Lhs_ type cannot be reliably reinterpreted as an integer to perform the operation.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Lhs_>(), "Attempted to bitwise OR via EmuCore::do_bitwise_or, but the provided Lhs_ type does not have a valid const | operator that takes a const Rhs_ arg.");
			}
		}
	};
	template<>
	struct do_bitwise_or<void, void>
	{
		constexpr do_bitwise_or()
		{
		}
		template<typename Lhs_, typename Rhs_>
		[[nodiscard]] constexpr inline std::invoke_result_t<do_bitwise_or<Lhs_, Rhs_>, const Lhs_&, const Rhs_&> operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_bitwise_or<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_bitwise_xor
	{
		constexpr do_bitwise_xor()
		{
		}
		constexpr inline EmuCore::TMP::bitwise_xor_operator_result_t<const Lhs_&, const Rhs_&> operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_bitwise_xor_operator_v<const Lhs_&, const Rhs_&>)
			{
				return lhs_ ^ rhs_;
			}
			else if constexpr (std::is_floating_point_v<Lhs_>)
			{
				using uint_type = EmuCore::TMP::uint_of_size_t<sizeof(Lhs_)>;
				if constexpr (!std::is_same_v<uint_type, std::false_type>)
				{
					const uint_type as_uint_ = do_bitwise_xor<uint_type, Rhs_>()(*reinterpret_cast<const uint_type*>(&lhs_), rhs_);
					return *reinterpret_cast<const Lhs_*>(&as_uint_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Lhs_>(), "Attempted to bitwise XOR a floating-point type via default EmuCore::do_bitwise_xor, but the provided Lhs_ type cannot be reliably reinterpreted as an integer to perform the operation.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Lhs_>(), "Attempted to bitwise XOR via EmuCore::do_bitwise_xor, but the provided Lhs_ type does not have a valid const ^ operator that takes a const Rhs_ arg.");
			}
		}
	};
	template<>
	struct do_bitwise_xor<void, void>
	{
		constexpr do_bitwise_xor()
		{
		}
		template<typename Lhs_, typename Rhs_>
		constexpr inline std::invoke_result_t<do_bitwise_xor<Lhs_, Rhs_>, const Lhs_&, const Rhs_&> operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_bitwise_xor<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename T_>
	struct do_bitwise_not
	{
		constexpr do_bitwise_not()
		{
		}
		constexpr inline EmuCore::TMP::bitwise_not_operator_result_t<const T_&> operator()(const T_& val_) const
		{
			if constexpr (EmuCore::TMP::has_bitwise_not_operator_v<const T_&>)
			{
				return ~val_;
			}
			else if constexpr (std::is_floating_point_v<T_>)
			{
				using uint_type = EmuCore::TMP::uint_of_size_t<sizeof(T_)>;
				if constexpr (!std::is_same_v<uint_type, std::false_type>)
				{
					const uint_type as_uint_ = do_bitwise_not<uint_type>()(*reinterpret_cast<const uint_type*>(&val_));
					return *reinterpret_cast<const T_*>(&as_uint_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<T_>(), "Attempted to bitwise NOT a floating-point type via default EmuCore::do_bitwise_not, but the provided T_ type cannot be reliably reinterpreted as an integer to perform the operation.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<T_>(), "Attempted to bitwise NOT via EmuCore::do_bitwise_not, but the provided T_ type does not have a valid const ~ operator.");
			}
		}
	};
	template<>
	struct do_bitwise_not<void>
	{
		constexpr do_bitwise_not()
		{
		}
		template<typename T_>
		constexpr inline std::invoke_result_t<do_bitwise_not<T_>, const T_&> operator()(const T_& val_) const
		{
			return do_bitwise_not<T_>()(val_);
		}
	};

	template<typename T_, typename Shifts_>
	struct do_left_shift
	{
		constexpr do_left_shift()
		{
		}
		constexpr inline EmuCore::TMP::left_shift_operator_result_t<const T_&, const Shifts_&> operator()(const T_& val_, const Shifts_& num_shifts_) const
		{
			if constexpr (EmuCore::TMP::has_left_shift_operator_v<const T_&, const Shifts_&>)
			{
				return val_ << num_shifts_;
			}
			else if constexpr (std::is_floating_point_v<T_>)
			{
				using uint_type = EmuCore::TMP::uint_of_size_t<sizeof(T_)>;
				if constexpr (!std::is_same_v<uint_type, std::false_type>)
				{
					const uint_type as_uint_ = do_left_shift<uint_type, Shifts_>()(*reinterpret_cast<const uint_type*>(&val_), num_shifts_);
					return *reinterpret_cast<const T_*>(&as_uint_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<T_>(), "Attempted to left-shift a floating-point type via default EmuCore::do_left_shift, but the provided T_ type cannot be reliably reinterpreted as an integer to perform the operation.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<T_>(), "Attempted to left-shift via EmuCore::do_left_shift, but the provided T_ type does not have a valid const << operator that takes a const Shifts_ arg.");
			}
		}
	};
	template<>
	struct do_left_shift<void, void>
	{
		constexpr do_left_shift()
		{
		}
		template<typename T_, typename Shifts_>
		constexpr inline std::invoke_result_t<do_left_shift<T_, Shifts_>, const T_&, const Shifts_&> operator()(const T_& val_, const Shifts_& num_shifts_) const
		{
			return do_left_shift<T_, Shifts_>()(val_, num_shifts_);
		}
	};

	template<typename T_, typename Shifts_>
	struct do_right_shift
	{
		constexpr do_right_shift()
		{
		}
		constexpr inline EmuCore::TMP::right_shift_operator_result_t<const T_&, const Shifts_&> operator()(const T_& val_, const Shifts_& num_shifts_) const
		{
			if constexpr (EmuCore::TMP::has_right_shift_operator_v<const T_&, const Shifts_&>)
			{
				return val_ >> num_shifts_;
			}
			else if constexpr (std::is_floating_point_v<T_>)
			{
				using uint_type = EmuCore::TMP::uint_of_size_t<sizeof(T_)>;
				if constexpr (!std::is_same_v<uint_type, std::false_type>)
				{
					const uint_type as_uint_ = do_right_shift<uint_type, Shifts_>()(*reinterpret_cast<const uint_type*>(&val_), num_shifts_);
					return *reinterpret_cast<const T_*>(&as_uint_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<T_>(), "Attempted to right-shift a floating-point type via default EmuCore::do_right_shift, but the provided T_ type cannot be reliably reinterpreted as an integer to perform the operation.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<T_>(), "Attempted to right-shift via EmuCore::do_right_shift, but the provided T_ type does not have a valid const >> operator that takes a const Shifts_ arg.");
			}
		}
	};
	template<>
	struct do_right_shift<void, void>
	{
		constexpr do_right_shift()
		{
		}
		template<typename T_, typename Shifts_>
		constexpr inline std::invoke_result_t<do_right_shift<T_, Shifts_>, const T_&, const Shifts_&> operator()(const T_& val_, const Shifts_& num_shifts_) const
		{
			return do_right_shift<T_, Shifts_>()(val_, num_shifts_);
		}
	};
#pragma endregion

#pragma region BITWISE_OP_ASSIGN_FUNCTORS
	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_bitwise_and_assign
	{
		using result_type = std::conditional_t
		<
			EmuCore::TMP::has_bitwise_and_assign_operator_v<Lhs_&, const Rhs_&>,
			EmuCore::TMP::bitwise_and_assign_operator_result_t<Lhs_&, const Rhs_&>,
			Lhs_&
		>;
		constexpr do_bitwise_and_assign()
		{
		}
		constexpr inline result_type operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_bitwise_and_assign_operator_v<Lhs_&, const Rhs_&>)
			{
				return lhs_ &= rhs_;
			}
			else
			{
				using const_op = do_bitwise_and<Lhs_, Rhs_>;
				using const_op_result = std::invoke_result_t<const_op, Lhs_&, const Rhs_&>;
				if constexpr (std::is_assignable_v<Lhs_&, const_op_result>)
				{
					lhs_ = const_op()(lhs_, rhs_);
					return lhs_;
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<const_op_result>(), "Unable to perform bitwise-AND-assign operation via EmuCore::do_bitwise_and_assign, as the provided Lhs_ type does not have a valid &= operator, and cannot be assigned via the result of do_bitwise_and in order to emulate such behaviour, when used with the provided Rhs_ argument.");
				}
			}
		}
	};
	template<>
	struct do_bitwise_and_assign<void, void>
	{
		constexpr do_bitwise_and_assign()
		{
		}
		template<typename Lhs_, typename Rhs_>
		constexpr inline std::invoke_result_t<do_bitwise_and_assign<Lhs_, Rhs_>, Lhs_&, const Rhs_&> operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_bitwise_and_assign<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_bitwise_or_assign
	{
		using result_type = std::conditional_t
		<
			EmuCore::TMP::has_bitwise_or_assign_operator_v<Lhs_&, const Rhs_&>,
			EmuCore::TMP::bitwise_or_assign_operator_result_t<Lhs_&, const Rhs_&>,
			Lhs_&
		>;
		constexpr do_bitwise_or_assign()
		{
		}
		constexpr inline result_type operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_bitwise_or_assign_operator_v<Lhs_&, const Rhs_&>)
			{
				return lhs_ |= rhs_;
			}
			else
			{
				using const_op = do_bitwise_or<Lhs_, Rhs_>;
				using const_op_result = std::invoke_result_t<const_op, Lhs_&, const Rhs_&>;
				if constexpr (std::is_assignable_v<Lhs_&, const_op_result>)
				{
					lhs_ = const_op()(lhs_, rhs_);
					return lhs_;
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<const_op_result>(), "Unable to perform bitwise-OR-assign operation via EmuCore::do_bitwise_or_assign, as the provided Lhs_ type does not have a valid |= operator, and cannot be assigned via the result of do_bitwise_or in order to emulate such behaviour, when used with the provided Rhs_ argument.");
				}
			}
		}
	};
	template<>
	struct do_bitwise_or_assign<void, void>
	{
		constexpr do_bitwise_or_assign()
		{
		}
		template<typename Lhs_, typename Rhs_>
		constexpr inline std::invoke_result_t<do_bitwise_or_assign<Lhs_, Rhs_>, Lhs_&, const Rhs_&> operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_bitwise_or_assign<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_bitwise_xor_assign
	{
		using result_type = std::conditional_t
		<
			EmuCore::TMP::has_bitwise_xor_assign_operator_v<Lhs_&, const Rhs_&>,
			EmuCore::TMP::bitwise_xor_assign_operator_result_t<Lhs_&, const Rhs_&>,
			Lhs_&
		>;
		constexpr do_bitwise_xor_assign()
		{
		}
		constexpr inline result_type operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_bitwise_xor_assign_operator_v<Lhs_&, const Rhs_&>)
			{
				return lhs_ ^= rhs_;
			}
			else
			{
				using const_op = do_bitwise_xor<Lhs_, Rhs_>;
				using const_op_result = std::invoke_result_t<const_op, Lhs_&, const Rhs_&>;
				if constexpr (std::is_assignable_v<Lhs_&, const_op_result>)
				{
					lhs_ = const_op()(lhs_, rhs_);
					return lhs_;
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<const_op_result>(), "Unable to perform bitwise-XOR-assign operation via EmuCore::do_bitwise_xor_assign, as the provided Lhs_ type does not have a valid ^= operator, and cannot be assigned via the result of do_bitwise_xor in order to emulate such behaviour, when used with the provided Rhs_ argument.");
				}
			}
		}
	};
	template<>
	struct do_bitwise_xor_assign<void, void>
	{
		constexpr do_bitwise_xor_assign()
		{
		}
		template<typename Lhs_, typename Rhs_>
		constexpr inline std::invoke_result_t<do_bitwise_xor_assign<Lhs_, Rhs_>, Lhs_&, const Rhs_&> operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_bitwise_xor_assign<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_left_shift_assign
	{
		using result_type = std::conditional_t
		<
			EmuCore::TMP::has_left_shift_assign_operator_v<Lhs_&, const Rhs_&>,
			EmuCore::TMP::left_shift_assign_operator_result_t<Lhs_&, const Rhs_&>,
			Lhs_&
		>;
		constexpr do_left_shift_assign()
		{
		}
		constexpr inline result_type operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_left_shift_assign_operator_v<Lhs_&, const Rhs_&>)
			{
				return lhs_ <<= rhs_;
			}
			else
			{
				using const_op = do_left_shift<Lhs_, Rhs_>;
				using const_op_result = std::invoke_result_t<const_op, Lhs_&, const Rhs_&>;
				if constexpr (std::is_assignable_v<Lhs_&, const_op_result>)
				{
					lhs_ = const_op()(lhs_, rhs_);
					return lhs_;
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<const_op_result>(), "Unable to perform left-shift-assign operation via EmuCore::do_left_shift_assign, as the provided Lhs_ type does not have a valid <<= operator, and cannot be assigned via the result of do_left_shift in order to emulate such behaviour, when used with the provided Rhs_ argument.");
				}
			}
		}
	};
	template<>
	struct do_left_shift_assign<void, void>
	{
		constexpr do_left_shift_assign()
		{
		}
		template<typename Lhs_, typename Rhs_>
		constexpr inline std::invoke_result_t<do_left_shift_assign<Lhs_, Rhs_>, Lhs_&, const Rhs_&> operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_left_shift_assign<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_right_shift_assign
	{
		using result_type = std::conditional_t
		<
			EmuCore::TMP::has_right_shift_assign_operator_v<Lhs_&, const Rhs_&>,
			EmuCore::TMP::right_shift_assign_operator_result_t<Lhs_&, const Rhs_&>,
			Lhs_&
		>;
		constexpr do_right_shift_assign()
		{
		}
		constexpr inline result_type operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_right_shift_assign_operator_v<Lhs_&, const Rhs_&>)
			{
				return lhs_ >>= rhs_;
			}
			else
			{
				using const_op = do_right_shift<Lhs_, Rhs_>;
				using const_op_result = std::invoke_result_t<const_op, Lhs_&, const Rhs_&>;
				if constexpr (std::is_assignable_v<Lhs_&, const_op_result>)
				{
					lhs_ = const_op()(lhs_, rhs_);
					return lhs_;
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<const_op_result>(), "Unable to perform right-shift-assign operation via EmuCore::do_right_shift_assign, as the provided Lhs_ type does not have a valid >>= operator, and cannot be assigned via the result of do_right_shift in order to emulate such behaviour, when used with the provided Rhs_ argument.");
				}
			}
		}
	};
	template<>
	struct do_right_shift_assign<void, void>
	{
		constexpr do_right_shift_assign()
		{
		}
		template<typename Lhs_, typename Rhs_>
		constexpr inline std::invoke_result_t<do_right_shift_assign<Lhs_, Rhs_>, Lhs_&, const Rhs_&> operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_right_shift_assign<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};
#pragma endregion
}

#endif
