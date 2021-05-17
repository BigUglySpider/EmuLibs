#ifndef EMU_CORE_TMP_HELPER_FUNCTORS_H_INC_
#define EMU_CORE_TMP_HELPER_FUNCTORS_H_INC_

#include "TypeComparators.h"
#include "TypeConvertors.h"
#include <type_traits>

namespace EmuCore::TMPHelpers
{
	/// <summary> Common info used by general arithmetic functors. </summary>
	/// <typeparam name="Lhs_">Left-handed argument type in the arithmetic operation.</typeparam>
	/// <typeparam name="Rhs_">Right-handed argument type in the arithmetic operation.</typeparam>
	/// <typeparam name="Out_">Output type for the result of the arithmetic operation.</typeparam>
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

	/// <summary> Functor for performing addition via the + operator taking two possibly different types, with an optionally customisable output type. </summary>
	/// <typeparam name="Lhs_">Left-handed argument type in the addition.</typeparam>
	/// <typeparam name="Rhs_">Right-handed argument type in the addition.</typeparam>
	/// <typeparam name="Out_">Type to output the result as. Defaults to the same as Lhs_.</typeparam>
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct plus_diff_types
	{
		using _info_type = _common_arithmetic_functor_info<Lhs_, Rhs_, Out_>;

		constexpr plus_diff_types()
		{
		}
		constexpr Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
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
	/// <summary> Functor for performing subtraction via the - operator taking two possibly different types, with an optionally customisable output type. </summary>
	/// <typeparam name="Lhs_">Left-handed argument type in the subtraction.</typeparam>
	/// <typeparam name="Rhs_">Right-handed argument type in the subtraction.</typeparam>
	/// <typeparam name="Out_">Type to output the result as. Defaults to the same as Lhs_.</typeparam>
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct minus_diff_types
	{
		using _info_type = _common_arithmetic_functor_info<Lhs_, Rhs_, Out_>;

		constexpr minus_diff_types()
		{
		}
		constexpr Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
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
	/// <summary> Functor for performing multiplication via the * operator taking two possibly different types, with an optionally customisable output type. </summary>
	/// <typeparam name="Lhs_">Left-handed argument type in the multiplication.</typeparam>
	/// <typeparam name="Rhs_">Right-handed argument type in the multiplication.</typeparam>
	/// <typeparam name="Out_">Type to output the result as. Defaults to the same as Lhs_.</typeparam>
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct multiplies_diff_types
	{
		using _info_type = _common_arithmetic_functor_info<Lhs_, Rhs_, Out_>;

		constexpr multiplies_diff_types()
		{
		}
		constexpr Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
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
	/// <summary> Functor for performing division via the / operator taking two possibly different types, with an optionally customisable output type. </summary>
	/// <typeparam name="Lhs_">Left-handed argument type in the division.</typeparam>
	/// <typeparam name="Rhs_">Right-handed argument type in the division.</typeparam>
	/// <typeparam name="Out_">Type to output the result as. Defaults to the same as Lhs_.</typeparam>
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct divides_diff_types
	{
		using _info_type = _common_arithmetic_functor_info<Lhs_, Rhs_, Out_>;

		constexpr divides_diff_types()
		{
		}
		constexpr Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
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
	/// <summary> Functor for performing modulo division via the % operator taking two possibly different types, with an optionally customisable output type. </summary>
	/// <typeparam name="Lhs_">Left-handed argument type in the modulo division.</typeparam>
	/// <typeparam name="Rhs_">Right-handed argument type in the modulo division.</typeparam>
	/// <typeparam name="Out_">Type to output the result as. Defaults to the same as Lhs_.</typeparam>
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct modulus_diff_types
	{
		using _info_type = _common_arithmetic_functor_info<Lhs_, Rhs_, Out_>;

		constexpr modulus_diff_types()
		{
		}
		constexpr Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
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

	/// <summary> Common info used by logical (non-shifting) bitwise functors. </summary>
	/// <typeparam name="Lhs_">Left-handed argument type in the bitwise operation.</typeparam>
	/// <typeparam name="Rhs_">Right-handed argument type in the bitwise operation.</typeparam>
	/// <typeparam name="Out_">Type to output the result as. Defaults to the same as Lhs_.</typeparam>
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct _common_logical_functor_info
	{
		static constexpr bool any_fp = EmuCore::TMPHelpers::is_any_floating_point_v<Lhs_, Rhs_, Out_>;
		static constexpr bool lhs_rhs_same = std::is_same_v<Lhs_, Rhs_>;
		static constexpr bool lhs_output_same = std::is_same_v<Lhs_, Out_>;
		static constexpr bool all_same = lhs_rhs_same && lhs_output_same;
	};

	/// <summary>
	/// <para> Functor for iteratively performing a bitwise AND (via the &amp; operator) on the data pointed to by the passed byte pointers. </para>
	/// <para> Iterations will be performed from final byte to first byte, with NumBytes_ iterations being performed. </para>
	/// </summary>
	template<std::size_t NumBytes_>
	struct iterative_and_on_byte_pointers
	{
		/// <summary> Type used to represent a byte. </summary>
		using _byte = unsigned char;
		/// <summary> Pointer to modifiable bytes. </summary>
		using byte_ptr = _byte*;
		/// <summary> Pointer to readonly bytes. </summary>
		using const_byte_ptr = const _byte*;

		void operator()(byte_ptr pOutBytes, const_byte_ptr pLeftBytes, const_byte_ptr pRightBytes) const
		{
			if constexpr (NumBytes_ > 0)
			{
				constexpr std::size_t offset = NumBytes_ - 1;
				*(pOutBytes + offset) = ((*(pLeftBytes + offset)) & (*(pRightBytes + offset)));
				iterative_and_on_byte_pointers<offset>()(pOutBytes, pLeftBytes, pRightBytes);
			}
		}
	};
	/// <summary>
	/// <para> Functor for iteratively performing a bitwise OR (via the | operator) on the data pointed to by the passed byte pointers. </para>
	/// <para> Iterations will be performed from final byte to first byte, with NumBytes_ iterations being performed. </para>
	/// </summary>
	template<std::size_t NumBytes_>
	struct iterative_or_on_byte_pointers
	{
		/// <summary> Type used to represent a byte. </summary>
		using _byte = unsigned char;
		/// <summary> Pointer to modifiable bytes. </summary>
		using byte_ptr = _byte*;
		/// <summary> Pointer to readonly bytes. </summary>
		using const_byte_ptr = const _byte*;

		void operator()(byte_ptr pOutBytes, const_byte_ptr pLeftBytes, const_byte_ptr pRightBytes) const
		{
			if constexpr (NumBytes_ > 0)
			{
				constexpr std::size_t offset = NumBytes_ - 1;
				*(pOutBytes + offset) = ((*(pLeftBytes + offset)) | (*(pRightBytes + offset)));
				iterative_or_on_byte_pointers<offset>()(pOutBytes, pLeftBytes, pRightBytes);
			}
		}
	};
	/// <summary>
	/// <para> Functor for iteratively performing a bitwise XOR (via the ^ operator) on the data pointed to by the passed byte pointers. </para>
	/// <para> Iterations will be performed from final byte to first byte, with NumBytes_ iterations being performed. </para>
	/// </summary>
	template<std::size_t NumBytes_>
	struct iterative_xor_on_byte_pointers
	{
		/// <summary> Type used to represent a byte. </summary>
		using _byte = unsigned char;
		/// <summary> Pointer to modifiable bytes. </summary>
		using byte_ptr = _byte*;
		/// <summary> Pointer to readonly bytes. </summary>
		using const_byte_ptr = const _byte*;

		void operator()(byte_ptr pOutBytes, const_byte_ptr pLeftBytes, const_byte_ptr pRightBytes) const
		{
			if constexpr (NumBytes_ > 0)
			{
				constexpr std::size_t offset = NumBytes_ - 1;
				*(pOutBytes + offset) = ((*(pLeftBytes + offset)) ^ (*(pRightBytes + offset)));
				iterative_xor_on_byte_pointers<offset>()(pOutBytes, pLeftBytes, pRightBytes);
			}
		}
	};

	/// <summary> Underlying functor for performing all iterative bitwise operation executions. </summary>
	template<template<std::size_t NumBytes_> typename _iterative_template>
	struct _perform_iterative_bitwise_op_execution
	{
		template<typename Lhs_, typename Rhs_, typename Out_>
		Out_ Execute(const Lhs_& lhs, const Rhs_& rhs) const
		{
			using HighestT = EmuCore::TMPHelpers::highest_byte_size_t<Lhs_, Rhs_, Out_>;
			HighestT lhsHighest = HighestT();
			HighestT rhsHighest = HighestT();
			memcpy(&lhsHighest, &lhs, sizeof(Lhs_));
			memcpy(&rhsHighest, &rhs, sizeof(Rhs_));
			Out_ out = Out_();

			using final_iterative_type = _iterative_template<sizeof(Out_)>;
			final_iterative_type()
			(
				reinterpret_cast<typename final_iterative_type::byte_ptr>(&out),
				reinterpret_cast<typename final_iterative_type::const_byte_ptr>(&lhsHighest),
				reinterpret_cast<typename final_iterative_type::const_byte_ptr>(&rhsHighest)
			);
			return out;
		}
	};
	/// <summary> Flags indicating certain bitwise operations. </summary>
	enum class _bitwise_op_flag : std::uint8_t
	{
		AND = 0x01,
		OR = 0x02,
		XOR = 0x04
	};
	/// <summary> Functor for performing an iterative bitwise operation based on a named flag. </summary>
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

	/// <summary> Functor for performing a logical AND via the &amp; operator taking two possibly different types, with an optionally customisable output type. </summary>
	/// <typeparam name="Lhs_">Left-handed argument type in the AND operation.</typeparam>
	/// <typeparam name="Rhs_">Right-handed argument type in the AND operation.</typeparam>
	/// <typeparam name="Out_">Type to output the result as. Defaults to the same as Lhs_.</typeparam>
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct logical_and_diff_types
	{
		using _info_type = _common_logical_functor_info<Lhs_, Rhs_, Out_>;

		Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
		{
			if constexpr (_info_type::any_fp)
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
	/// <summary> Functor for performing a logical OR via the | operator taking two possibly different types, with an optionally customisable output type. </summary>
	/// <typeparam name="Lhs_">Left-handed argument type in the OR operation.</typeparam>
	/// <typeparam name="Rhs_">Right-handed argument type in the OR operation.</typeparam>
	/// <typeparam name="Out_">Type to output the result as. Defaults to the same as Lhs_.</typeparam>
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct logical_or_diff_types
	{
		using _info_type = _common_logical_functor_info<Lhs_, Rhs_, Out_>;

		Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
		{
			if constexpr (_info_type::any_fp)
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
	/// <summary> Functor for performing a logical XOR via the ^ operator taking two possibly different types, with an optionally customisable output type. </summary>
	/// <typeparam name="Lhs_">Left-handed argument type in the XOR operation.</typeparam>
	/// <typeparam name="Rhs_">Right-handed argument type in the XOR operation.</typeparam>
	/// <typeparam name="Out_">Type to output the result as. Defaults to the same as Lhs_.</typeparam>
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct logical_xor_diff_types
	{
		using _info_type = _common_logical_functor_info<Lhs_, Rhs_, Out_>;

		Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
		{
			if constexpr (_info_type::any_fp)
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

	/// <summary> Common info used by bitwise shift functors. </summary>
	/// <typeparam name="Lhs_">Left-handed argument type in the shift operation.</typeparam>
	/// <typeparam name="Rhs_">Right-handed argument type in the shift operation.</typeparam>
	/// <typeparam name="Out_">Type to output the result as. Defaults to the same as Lhs_.</typeparam>
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct _common_bitwise_shift_info
	{
		static constexpr bool lhs_matches_out = std::is_same_v<Lhs_, Out_>;
		using RhsT = std::conditional_t
		<
			std::is_unsigned_v<Rhs_> && std::is_integral_v<Rhs_>,
			Rhs_,
			std::size_t
		>;
		static constexpr bool rhs_matches_template = std::is_same_v<RhsT, Rhs_>;
	};
	/// <summary> Functor for performing a bitwise left shift via the &lt;&lt; operator taking two possibly different types, with an optionally customisable output type. </summary>
	/// <typeparam name="Lhs_">Left-handed argument type in the left shift operation.</typeparam>
	/// <typeparam name="Rhs_">Right-handed argument type in the left shift operation.</typeparam>
	/// <typeparam name="Out_">Type to output the result as. Defaults to the same as Lhs_.</typeparam>
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct bitwise_shift_left_diff_types
	{
		using _info_type = _common_bitwise_shift_info<Lhs_, Rhs_, Out_>;

		constexpr bitwise_shift_left_diff_types()
		{
		}
		constexpr Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
		{
			if constexpr (_info_type::rhs_matches_template)
			{
				if constexpr (_info_type::lhs_integral)
				{
					if constexpr (_info_type::lhs_matches_input)
					{
						return lhs << rhs;
					}
					else
					{
						return static_cast<Out_>(lhs << rhs);
					}
				}
			}
			else
			{
				typename _info_type::RhsT finalRhs = static_cast<typename _info_type::RhsT>(rhs);
				if constexpr (_info_type::lhs_integral)
				{
					if constexpr (_info_type::lhs_matches_input)
					{
						return lhs << finalRhs;
					}
					else
					{
						return static_cast<Out_>(lhs << finalRhs);
					}
				}
			}
		}
	};
	/// <summary> Functor for performing a bitwise right shift via the &gt;&gt; operator taking two possibly different types, with an optionally customisable output type. </summary>
	/// <typeparam name="Lhs_">Left-handed argument type in the right shift operation.</typeparam>
	/// <typeparam name="Rhs_">Right-handed argument type in the right shift operation.</typeparam>
	/// <typeparam name="Out_">Type to output the result as. Defaults to the same as Lhs_.</typeparam>
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct bitwise_shift_right_diff_types
	{
		using _info_type = _common_bitwise_shift_info<Lhs_, Rhs_, Out_>;

		constexpr bitwise_shift_right_diff_types()
		{
		}
		constexpr Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
		{
			if constexpr (_info_type::rhs_matches_template)
			{
				if constexpr (_info_type::lhs_integral)
				{
					if constexpr (_info_type::lhs_matches_input)
					{
						return lhs >> rhs;
					}
					else
					{
						return static_cast<Out_>(lhs >> rhs);
					}
				}
			}
			else
			{
				typename _info_type::RhsT finalRhs = static_cast<typename _info_type::RhsT>(rhs);
				if constexpr (_info_type::lhs_integral)
				{
					if constexpr (_info_type::lhs_matches_input)
					{
						return lhs >> finalRhs;
					}
					else
					{
						return static_cast<Out_>(lhs >> finalRhs);
					}
				}
			}
		}
	};

	template<std::size_t NumBytes_>
	struct iterative_bit_inversion_on_byte_pointers
	{
		/// <summary> Type used to represent a byte. </summary>
		using _byte = unsigned char;
		/// <summary> Pointer to modifiable bytes. </summary>
		using byte_ptr = _byte*;
		/// <summary> Pointer to readonly bytes. </summary>
		using const_byte_ptr = const _byte*;

		constexpr void operator()(byte_ptr pOutBytes, const_byte_ptr pInBytes) const
		{
			if constexpr (NumBytes_ > 0)
			{
				constexpr std::size_t offset = NumBytes_ - 1;
				*(pOutBytes + offset) = ~(*(pInBytes + offset));
				iterative_bit_inversion_on_byte_pointers<offset>()(pOutBytes, pInBytes);
			}
		}
	};
	template<typename In_, typename Out_>
	struct bit_inversion_diff_types
	{
		constexpr bit_inversion_diff_types()
		{
		}
		constexpr Out_ operator()(const In_ in_) const
		{
			if constexpr (std::is_integral_v<In_> && std::is_same_v<In_, Out_>)
			{
				return ~in_;
			}
			else
			{
				Out_ out = EmuCore::ArithmeticHelpers::ZeroT<Out_>;
				memcpy(&out, &in_, EmuCore::TMPHelpers::lowest_byte_size_v<In_, Out_>);

				constexpr std::size_t OutSize_ = sizeof(Out_);
				iterative_bit_inversion_on_byte_pointers<OutSize_>()
				(
					reinterpret_cast<typename iterative_bit_inversion_on_byte_pointers<OutSize_>::byte_ptr>(&out),
					reinterpret_cast<typename iterative_bit_inversion_on_byte_pointers<OutSize_>::const_byte_ptr>(&out)
				);
				return out;
			}
		}
	};
}

#endif
