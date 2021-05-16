#ifndef EMU_CORE_TMP_HELPER_FUNCTORS_H_INC_
#define EMU_CORE_TMP_HELPER_FUNCTORS_H_INC_

#include "TypeComparators.h"
#include "TypeConvertors.h"
#include <type_traits>

namespace EmuCore::TMPHelpers
{
	template<typename Lhs_, typename Rhs_, typename Out_>
	struct _common_arithmetic_functor_info
	{
		static constexpr bool any_fp = EmuCore::TMPHelpers::is_any_floating_point_v<Lhs_, Rhs_, Out_>;
		static constexpr bool lhs_rhs_same = std::is_same_v<Lhs_, Rhs_>;
		static constexpr bool lhs_output_same = std::is_same_v<Lhs_, Out_>;
		static constexpr bool rhs_output_same = std::is_same_v<Rhs_, Out_>;
		static constexpr bool all_same = lhs_rhs_same && lhs_output_same;

		using result_type = std::conditional_t
		<
			all_same,
			Lhs_,
			std::conditional_t
			<
				any_fp,
				EmuCore::TMPHelpers::highest_byte_size_t
				<
					EmuCore::TMPHelpers::best_floating_point_rep_t<Lhs_>,
					EmuCore::TMPHelpers::best_floating_point_rep_t<Rhs_>,
					EmuCore::TMPHelpers::best_floating_point_rep_t<Out_>
				>,
				EmuCore::TMPHelpers::highest_byte_size_t<Lhs_, Rhs_, Out_>
			>
		>;
		static constexpr bool cast_result = std::is_same_v<result_type, Out_>;
	};

	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct plus_diff_types
	{
		using _info_type = _common_arithmetic_functor_info<Lhs_, Rhs_, Out_>;

		Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
		{
			if constexpr (_info_type::all_same)
			{
				return lhs + rhs;
			}
			else
			{
				if constexpr (_info_type::cast_result)
				{
					return static_cast<Out_>(static_cast<typename _info_type::result_type>(lhs) + rhs);
				}
				else
				{
					return static_cast<typename _info_type::result_type>(lhs) + rhs;
				}
			}
		}
	};
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct minus_diff_types
	{
		using _info_type = _common_arithmetic_functor_info<Lhs_, Rhs_, Out_>;

		Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
		{
			if constexpr (_info_type::all_same)
			{
				return lhs - rhs;
			}
			else
			{
				if constexpr (_info_type::cast_result)
				{
					return static_cast<Out_>(static_cast<typename _info_type::result_type>(lhs) - rhs);
				}
				else
				{
					return static_cast<typename _info_type::result_type>(lhs) - rhs;
				}
			}
		}
	};
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct multiplies_diff_types
	{
		using _info_type = _common_arithmetic_functor_info<Lhs_, Rhs_, Out_>;

		Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
		{
			if constexpr (_info_type::all_same)
			{
				return lhs * rhs;
			}
			else
			{
				if constexpr (_info_type::cast_result)
				{
					return static_cast<Out_>(static_cast<typename _info_type::result_type>(lhs) * rhs);
				}
				else
				{
					return static_cast<typename _info_type::result_type>(lhs) * rhs;
				}
			}
		}
	};
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct divides_diff_types
	{
		using _info_type = _common_arithmetic_functor_info<Lhs_, Rhs_, Out_>;

		Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
		{
			if constexpr (_info_type::all_same)
			{
				return lhs / rhs;
			}
			else
			{
				if constexpr (_info_type::cast_result)
				{
					return static_cast<Out_>(static_cast<typename _info_type::result_type>(lhs) / rhs);
				}
				else
				{
					return static_cast<typename _info_type::result_type>(lhs) / rhs;
				}
			}
		}
	};
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct modulus_diff_types
	{
		using _info_type = _common_arithmetic_functor_info<Lhs_, Rhs_, Out_>;

		Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
		{
			if constexpr (_info_type::all_same)
			{
				return lhs % rhs;
			}
			else
			{
				if constexpr (_info_type::cast_result)
				{
					return static_cast<Out_>(static_cast<typename _info_type::result_type>(lhs) % rhs);
				}
				else
				{
					return static_cast<typename _info_type::result_type>(lhs) % rhs;
				}
			}
		}
	};

	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct _common_logical_functor_info
	{
		static constexpr bool lhs_or_rhs_fp = EmuCore::TMPHelpers::is_any_floating_point_v<Lhs_, Rhs_>;
		static constexpr bool lhs_rhs_same = std::is_same_v<Lhs_, Rhs_>;
		static constexpr bool lhs_output_same = std::is_same_v<Lhs_, Out_>;
		static constexpr bool all_same = lhs_rhs_same && lhs_output_same;
	};

	template<std::size_t NumIterations>
	struct iterative_and_on_byte_pointers
	{
		using _byte = unsigned char;
		using byte_ptr = _byte*;
		using const_byte_ptr = const _byte*;

		void operator()(byte_ptr pOutBytes, const_byte_ptr pLeftBytes, const_byte_ptr pRightBytes)
		{
			if constexpr (NumIterations > 0)
			{
				constexpr std::size_t offset = NumIterations - 1;
				*(pOutBytes + offset) = ((*(pLeftBytes + offset)) & (*(pRightBytes + offset)));
				iterative_and_on_byte_pointers<offset>()(pOutBytes, pLeftBytes, pRightBytes);
			}
		}
	};
	template<std::size_t NumIterations>
	struct iterative_or_on_byte_pointers
	{
		using _byte = unsigned char;
		using byte_ptr = _byte*;
		using const_byte_ptr = const _byte*;

		void operator()(byte_ptr pOutBytes, const_byte_ptr pLeftBytes, const_byte_ptr pRightBytes)
		{
			if constexpr (NumIterations > 0)
			{
				constexpr std::size_t offset = NumIterations - 1;
				*(pOutBytes + offset) = ((*(pLeftBytes + offset)) | (*(pRightBytes + offset)));
				iterative_and_on_byte_pointers<offset>()(pOutBytes, pLeftBytes, pRightBytes);
			}
		}
	};
	template<std::size_t NumIterations>
	struct iterative_xor_on_byte_pointers
	{
		using _byte = unsigned char;
		using byte_ptr = _byte*;
		using const_byte_ptr = const _byte*;

		void operator()(byte_ptr pOutBytes, const_byte_ptr pLeftBytes, const_byte_ptr pRightBytes)
		{
			if constexpr (NumIterations > 0)
			{
				constexpr std::size_t offset = NumIterations - 1;
				*(pOutBytes + offset) = ((*(pLeftBytes + offset)) ^ (*(pRightBytes + offset)));
				iterative_and_on_byte_pointers<offset>()(pOutBytes, pLeftBytes, pRightBytes);
			}
		}
	};

	template<template<std::size_t NumBytes_> typename _iterative_template>
	struct _perform_iterative_bitwise_op_execution
	{
		template<typename Lhs_, typename Rhs_, typename Out_>
		Out_ Execute(const Lhs_& lhs, const Rhs_& rhs) const
		{
			using HighestT = EmuCore::TMPHelpers::highest_byte_size_t<Lhs_, Rhs_>;
			HighestT lhsHighest = HighestT();
			HighestT rhsHighest = HighestT();
			memcpy(&lhsHighest, &lhs, sizeof(Lhs_));
			memcpy(&rhsHighest, &rhs, sizeof(Rhs_));
			HighestT out = HighestT();

			using final_iterative_type = _iterative_template<sizeof(HighestT)>;
			final_iterative_type()
			(
				reinterpret_cast<typename final_iterative_type::byte_ptr>(&out),
				reinterpret_cast<typename final_iterative_type::const_byte_ptr>(&lhsHighest),
				reinterpret_cast<typename final_iterative_type::const_byte_ptr>(&rhsHighest)
			);
			return static_cast<Out_>(out);
		}
	};
	enum class _bitwise_op_flag : std::uint8_t
	{
		AND = 0x01,
		OR = 0x02,
		XOR = 0x04
	};
	template<_bitwise_op_flag Flag_>
	using _perform_iterative_bitwise_op_execution_based_on_flag = std::conditional_t
	<
		Flag_ == _bitwise_op_flag::AND,
		_perform_iterative_bitwise_op_execution<iterative_and_on_byte_pointers>,
		std::conditional_t
		<
			Flag_ == _bitwise_op_flag::OR,
			_perform_iterative_bitwise_op_execution<iterative_or_on_byte_pointers>,
			std::conditional_t
			<
				Flag_ == _bitwise_op_flag::XOR,
				_perform_iterative_bitwise_op_execution<iterative_xor_on_byte_pointers>,
				std::false_type
			>
		>
	>;

	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct logical_and_diff_types
	{
		using _info_type = _common_logical_functor_info<Lhs_, Rhs_, Out_>;

		Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
		{
			if constexpr (_info_type::lhs_or_rhs_fp)
			{
				return _perform_iterative_bitwise_op_execution_based_on_flag<_bitwise_op_flag::AND>().Execute<Lhs_, Rhs_, Out_>(lhs, rhs);
			}
			else if constexpr (_info_type::all_same)
			{
				return lhs & rhs;
			}
			else
			{
				using HighestT = EmuCore::TMPHelpers::highest_byte_size_t<Lhs_, Rhs_, Out_>;
				if constexpr (std::is_same_v<HighestT, Out_>)
				{
					return static_cast<Out_>(lhs) & rhs;
				}
				else
				{
					return static_cast<Out_>(static_cast<HighestT>(lhs) & rhs);
				}
			}
		}
	};
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct logical_or_diff_types
	{
		using _info_type = _common_logical_functor_info<Lhs_, Rhs_, Out_>;

		Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
		{
			if constexpr (_info_type::lhs_or_rhs_fp)
			{
				return _perform_iterative_bitwise_op_execution_based_on_flag<_bitwise_op_flag::OR>().Execute<Lhs_, Rhs_, Out_>(lhs, rhs);
			}
			else if constexpr (_info_type::all_same)
			{
				return lhs | rhs;
			}
			else
			{
				using HighestT = EmuCore::TMPHelpers::highest_byte_size_t<Lhs_, Rhs_, Out_>;
				if constexpr (std::is_same_v<HighestT, Out_>)
				{
					return static_cast<Out_>(lhs) | rhs;
				}
				else
				{
					return static_cast<Out_>(static_cast<HighestT>(lhs) | rhs);
				}
			}
		}
	};
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct logical_xor_diff_types
	{
		using _info_type = _common_logical_functor_info<Lhs_, Rhs_, Out_>;

		Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
		{
			if constexpr (_info_type::lhs_or_rhs_fp)
			{
				return _perform_iterative_bitwise_op_execution_based_on_flag<_bitwise_op_flag::XOR>().Execute<Lhs_, Rhs_, Out_>(lhs, rhs);
			}
			else if constexpr (_info_type::all_same)
			{
				return lhs ^ rhs;
			}
			else
			{
				using HighestT = EmuCore::TMPHelpers::highest_byte_size_t<Lhs_, Rhs_, Out_>;
				if constexpr (std::is_same_v<HighestT, Out_>)
				{
					return static_cast<Out_>(lhs) ^ rhs;
				}
				else
				{
					return static_cast<Out_>(static_cast<HighestT>(lhs) ^ rhs);
				}
			}
		}
	};
}

#endif
