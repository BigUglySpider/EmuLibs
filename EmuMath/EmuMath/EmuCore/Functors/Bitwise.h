#ifndef EMU_CORE_BITWISE_FUNCTORS_H_INC_
#define EMU_CORE_BITWISE_FUNCTORS_H_INC_ 1

#include "../TMPHelpers/OperatorChecks.h"
#include "../TMPHelpers/TypeConvertors.h"
#include "../TMPHelpers/Values.h"
#include "../CommonConcepts/CommonRequirements.h"
#include <cstddef>
#include <cstring>
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
		constexpr inline decltype(auto) operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_bitwise_and_operator_v<const Lhs_&, const Rhs_&>)
			{
				return lhs_ & rhs_;
			}
			else if constexpr (std::is_floating_point_v<Lhs_> && (sizeof(Lhs_) == sizeof(Rhs_)))
			{
				using uint_type = EmuCore::TMP::uint_of_size_t<sizeof(Lhs_)>;
				if constexpr (!std::is_same_v<uint_type, EmuCore::TMP::emu_tmp_err>)
				{
					uint_type as_uint = std::bit_cast<uint_type>(lhs_);
					as_uint &= as_uint & std::bit_cast<uint_type>(rhs_);
					return std::bit_cast<typename std::remove_cvref<Lhs_>::type>(as_uint);
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
		constexpr inline decltype(auto) operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_bitwise_and<typename std::remove_cvref<Lhs_>::type, typename std::remove_cvref<Rhs_>::type>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_bitwise_or
	{
		constexpr do_bitwise_or()
		{
		}
		constexpr inline decltype(auto) operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_bitwise_or_operator_v<const Lhs_&, const Rhs_&>)
			{
				return lhs_ | rhs_;
			}
			else if constexpr (std::is_floating_point_v<Lhs_> && (sizeof(Lhs_) == sizeof(Rhs_)))
			{
				using uint_type = EmuCore::TMP::uint_of_size_t<sizeof(Lhs_)>;
				if constexpr (!std::is_same_v<uint_type, std::false_type>)
				{
					uint_type as_uint = std::bit_cast<uint_type>(lhs_);
					as_uint |= std::bit_cast<uint_type>(rhs_);
					return std::bit_cast<typename std::remove_cvref<Lhs_>::type>(as_uint);
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
		[[nodiscard]] constexpr inline decltype(auto) operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_bitwise_or<typename std::remove_cvref<Lhs_>::type, typename std::remove_cvref<Rhs_>::type>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_bitwise_xor
	{
		constexpr do_bitwise_xor()
		{
		}
		constexpr inline decltype(auto) operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_bitwise_xor_operator_v<const Lhs_&, const Rhs_&>)
			{
				return lhs_ ^ rhs_;
			}
			else if constexpr (std::is_floating_point_v<Lhs_> && (sizeof(Lhs_) == sizeof(Rhs_)))
			{
				using uint_type = EmuCore::TMP::uint_of_size_t<sizeof(Lhs_)>;
				if constexpr (!std::is_same_v<uint_type, std::false_type>)
				{
					uint_type as_uint = std::bit_cast<uint_type>(lhs_);
					as_uint ^= std::bit_cast<uint_type>(rhs_);
					return std::bit_cast<typename std::remove_cvref<Lhs_>::type>(as_uint);
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
		constexpr inline decltype(auto) operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_bitwise_xor<typename std::remove_cvref<Lhs_>::type, typename std::remove_cvref<Rhs_>::type>()(lhs_, rhs_);
		}
	};

	template<typename T_>
	struct do_bitwise_not
	{
		constexpr do_bitwise_not()
		{
		}
		constexpr inline decltype(auto) operator()(const T_& val_) const
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
					uint_type as_uint = ~(std::bit_cast<uint_type>(val_));
					return std::bit_cast<typename std::remove_cvref<T_>::type>(as_uint);
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
		constexpr inline decltype(auto) operator()(const T_& val_) const
		{
			return do_bitwise_not<typename std::remove_cvref<T_>::type>()(val_);
		}
	};

	template<typename T_, typename Shifts_>
	struct do_left_shift
	{
		constexpr do_left_shift()
		{
		}
		constexpr inline decltype(auto) operator()(const T_& val_, const Shifts_& num_shifts_) const
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
					uint_type as_uint = (std::bit_cast<uint_type>(val_)) << num_shifts_;
					return std::bit_cast<typename std::remove_cvref<T_>::type>(as_uint);
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
		constexpr inline decltype(auto) operator()(const T_& val_, const Shifts_& num_shifts_) const
		{
			return do_left_shift<typename std::remove_cvref<T_>::type, typename std::remove_cvref<Shifts_>::type>()(val_, num_shifts_);
		}
	};

	template<typename T_, typename Shifts_>
	struct do_right_shift
	{
		constexpr do_right_shift()
		{
		}
		constexpr inline decltype(auto) operator()(const T_& val_, const Shifts_& num_shifts_) const
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
					uint_type as_uint = (std::bit_cast<uint_type>(val_)) << num_shifts_;
					return std::bit_cast<typename std::remove_cvref<T_>::type>(as_uint);
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
		constexpr inline decltype(auto) operator()(const T_& val_, const Shifts_& num_shifts_) const
		{
			return do_right_shift<typename std::remove_cvref<T_>::type, typename std::remove_cvref<Shifts_>::type>()(val_, num_shifts_);
		}
	};

	template<typename NotLhs_, typename Rhs_ = NotLhs_>
	struct do_bitwise_andnot
	{
		constexpr do_bitwise_andnot()
		{
		}
		constexpr inline decltype(auto) operator()(const NotLhs_& not_lhs_, const Rhs_& rhs_) const
		{
			using not_func = do_bitwise_not<NotLhs_>;
			using not_result = decltype(not_func()(not_lhs_));
			using and_func = do_bitwise_and<typename std::remove_cvref<not_result>::type, Rhs_>;
			return and_func()(not_func()(not_lhs_), rhs_);
		}
	};

	template<>
	struct do_bitwise_andnot<void, void>
	{
		constexpr do_bitwise_andnot()
		{
		}
		template<typename NotLhs_, typename Rhs_>
		constexpr inline decltype(auto) operator()(const NotLhs_& not_lhs_, const Rhs_& rhs_) const
		{
			return do_bitwise_andnot<typename std::remove_cvref<NotLhs_>::type, typename std::remove_cvref<Rhs_>::type>()(not_lhs_, rhs_);
		}
	};
#pragma endregion

#pragma region BITWISE_OP_ASSIGN_FUNCTORS
	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_bitwise_and_assign
	{
		constexpr do_bitwise_and_assign()
		{
		}
		constexpr inline decltype(auto) operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_bitwise_and_assign_operator_v<Lhs_&, const Rhs_&>)
			{
				return lhs_ &= rhs_;
			}
			else
			{
				using const_op = do_bitwise_and<Lhs_, Rhs_>;
				using const_op_result = decltype(const_op()(lhs_, rhs_));
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
		template<EmuConcepts::Writable Lhs_, typename Rhs_>
		constexpr inline decltype(auto) operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_bitwise_and_assign<typename std::remove_cvref<Lhs_>::type, typename std::remove_cvref<Rhs_>::type>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_bitwise_or_assign
	{
		constexpr do_bitwise_or_assign()
		{
		}
		constexpr inline decltype(auto) operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_bitwise_or_assign_operator_v<Lhs_&, const Rhs_&>)
			{
				return lhs_ |= rhs_;
			}
			else
			{
				using const_op = do_bitwise_or<Lhs_, Rhs_>;
				using const_op_result = decltype(const_op()(lhs_, rhs_));
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
		template<EmuConcepts::Writable Lhs_, typename Rhs_>
		constexpr inline decltype(auto) operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_bitwise_or_assign<typename std::remove_cvref<Lhs_>::type, typename std::remove_cvref<Rhs_>::type>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_bitwise_xor_assign
	{
		constexpr do_bitwise_xor_assign()
		{
		}
		constexpr inline decltype(auto) operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_bitwise_xor_assign_operator_v<Lhs_&, const Rhs_&>)
			{
				return lhs_ ^= rhs_;
			}
			else
			{
				using const_op = do_bitwise_xor<Lhs_, Rhs_>;
				using const_op_result = decltype(const_op()(lhs_, rhs_));
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
		template<EmuConcepts::Writable Lhs_, typename Rhs_>
		constexpr inline decltype(auto) operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_bitwise_xor_assign<typename std::remove_cvref<Lhs_>::type, typename std::remove_cvref<Rhs_>::type>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_left_shift_assign
	{
		constexpr do_left_shift_assign()
		{
		}
		constexpr inline decltype(auto) operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_left_shift_assign_operator_v<Lhs_&, const Rhs_&>)
			{
				return lhs_ <<= rhs_;
			}
			else
			{
				using const_op = do_left_shift<Lhs_, Rhs_>;
				using const_op_result = decltype(const_op()(lhs_, rhs_));
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
		template<EmuConcepts::Writable Lhs_, typename Rhs_>
		constexpr inline decltype(auto) operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_left_shift_assign<typename std::remove_cvref<Lhs_>::type, typename std::remove_cvref<Rhs_>::type>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_right_shift_assign
	{
		constexpr do_right_shift_assign()
		{
		}
		constexpr inline decltype(auto) operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			if constexpr (EmuCore::TMP::has_right_shift_assign_operator_v<Lhs_&, const Rhs_&>)
			{
				return lhs_ >>= rhs_;
			}
			else
			{
				using const_op = do_right_shift<Lhs_, Rhs_>;
				using const_op_result = decltype(const_op()(lhs_, rhs_));
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
		template<EmuConcepts::Writable Lhs_, typename Rhs_>
		constexpr inline decltype(auto) operator()(Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_right_shift_assign<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};
#pragma endregion
}

#endif
