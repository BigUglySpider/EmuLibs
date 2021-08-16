#ifndef EMU_CORE_TMP_HELPER_FUNCTORS_H_INC_
#define EMU_CORE_TMP_HELPER_FUNCTORS_H_INC_ 1

#include "TypeComparators.h"
#include "TypeConvertors.h"
#include <functional>
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

	/// <summary> Common info used by bitwise (non-shifting) bitwise functors. </summary>
	/// <typeparam name="Lhs_">Left-handed argument type in the bitwise operation.</typeparam>
	/// <typeparam name="Rhs_">Right-handed argument type in the bitwise operation.</typeparam>
	/// <typeparam name="Out_">Type to output the result as. Defaults to the same as Lhs_.</typeparam>
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct _common_bitwise_functor_info
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

	/// <summary> Functor for performing a bitwise AND via the &amp; operator taking two possibly different types, with an optionally customisable output type. </summary>
	/// <typeparam name="Lhs_">Left-handed argument type in the AND operation.</typeparam>
	/// <typeparam name="Rhs_">Right-handed argument type in the AND operation.</typeparam>
	/// <typeparam name="Out_">Type to output the result as. Defaults to the same as Lhs_.</typeparam>
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct bitwise_and_diff_types
	{
		using _info_type = _common_bitwise_functor_info<Lhs_, Rhs_, Out_>;

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
	/// <summary> Functor for performing a bitwise OR via the | operator taking two possibly different types, with an optionally customisable output type. </summary>
	/// <typeparam name="Lhs_">Left-handed argument type in the OR operation.</typeparam>
	/// <typeparam name="Rhs_">Right-handed argument type in the OR operation.</typeparam>
	/// <typeparam name="Out_">Type to output the result as. Defaults to the same as Lhs_.</typeparam>
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct bitwise_or_diff_types
	{
		using _info_type = _common_bitwise_functor_info<Lhs_, Rhs_, Out_>;

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
	/// <summary> Functor for performing a bitwise XOR via the ^ operator taking two possibly different types, with an optionally customisable output type. </summary>
	/// <typeparam name="Lhs_">Left-handed argument type in the XOR operation.</typeparam>
	/// <typeparam name="Rhs_">Right-handed argument type in the XOR operation.</typeparam>
	/// <typeparam name="Out_">Type to output the result as. Defaults to the same as Lhs_.</typeparam>
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct bitwise_xor_diff_types
	{
		using _info_type = _common_bitwise_functor_info<Lhs_, Rhs_, Out_>;

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
		static constexpr bool lhs_integral = std::is_integral_v<Lhs_>;
		static constexpr bool rhs_integral = std::is_integral_v<Rhs_>;
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
		constexpr Out_ operator()(const Lhs_& lhs, const Rhs_& numShifts) const
		{
			if constexpr (_info_type::lhs_integral)
			{
				if constexpr (_info_type::rhs_integral)
				{
					if constexpr (_info_type::lhs_matches_out)
					{
						return lhs << numShifts;
					}
					else
					{
						const Lhs_ shifted = lhs << numShifts;
						Out_ out = Out_();
						memcpy(&out, &shifted, EmuCore::TMPHelpers::lowest_byte_size_v<Lhs_, Out_>);
						return out;
					}
				}
				else
				{
					return bitwise_shift_left_diff_types<Lhs_, std::size_t, Out_>()(lhs, static_cast<std::size_t>(numShifts));
				}
			}
			else
			{
				using LhsInt = EmuCore::TMPHelpers::uint_of_size_t<sizeof(Lhs_)>;
				if constexpr (!std::is_same_v<LhsInt, std::false_type>)
				{
					LhsInt lhsInt = 0;
					LhsInt* pLhsInt = &lhsInt;
					memcpy(pLhsInt, &lhs, sizeof(Lhs_));
					lhsInt = bitwise_shift_left_diff_types<LhsInt, Rhs_, LhsInt>()(lhsInt, numShifts);
					Out_ out = Out_();
					memcpy(&out, pLhsInt, EmuCore::TMPHelpers::lowest_byte_size_v<LhsInt, Out_>);
					return out;
				}
				else
				{
					static_assert(false, "Attempted to perform a bitwise left shift via bitwise_shift_left_diff_types using a type that cannot be accurately reinterpreted.");
					return Out_();
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
		constexpr Out_ operator()(const Lhs_& lhs, const Rhs_& numShifts) const
		{
			if constexpr (_info_type::lhs_integral)
			{
				if constexpr (_info_type::rhs_integral)
				{
					if constexpr (_info_type::lhs_matches_out)
					{
						return lhs >> numShifts;
					}
					else
					{
						const Lhs_ shifted = lhs >> numShifts;
						Out_ out = Out_();
						memcpy(&out, &shifted, EmuCore::TMPHelpers::lowest_byte_size_v<Lhs_, Out_>);
						return out;
					}
				}
				else
				{
					return bitwise_shift_right_diff_types<Lhs_, std::size_t, Out_>()(lhs, static_cast<std::size_t>(numShifts));
				}
			}
			else
			{
				using LhsInt = EmuCore::TMPHelpers::uint_of_size_t<sizeof(Lhs_)>;
				if constexpr (!std::is_same_v<LhsInt, std::false_type>)
				{
					LhsInt lhsInt = 0;
					LhsInt* pLhsInt = &lhsInt;
					memcpy(pLhsInt, &lhs, sizeof(Lhs_));
					lhsInt = bitwise_shift_right_diff_types<LhsInt, Rhs_, LhsInt>()(lhsInt, numShifts);
					Out_ out = Out_();
					memcpy(&out, pLhsInt, EmuCore::TMPHelpers::lowest_byte_size_v<LhsInt, Out_>);
					return out;
				}
				else
				{
					static_assert(false, "Attempted to perform a bitwise right shift via bitwise_shift_left_diff_types using a type that cannot be accurately reinterpreted.");
					return Out_();
				}
			}
		}
	};

	template<typename T>
	struct reverse_bits
	{
	public:
		static constexpr std::size_t NumBytes_ = sizeof(T);
		constexpr reverse_bits()
		{
		}
		constexpr T operator()(const T& in_) const
		{
			T out = T();
			this->_reverse_bytes<0>
			(
				reinterpret_cast<const std::uint8_t*>(&(in_)) + (NumBytes_ - 1),
				reinterpret_cast<std::uint8_t*>(&out)
			);
			return out;
		}

	private:
		/// <summary> Iteratively reverses the pointed to in bytes and stores the results in the pointed to out bytes. </summary>
		/// <param name="pInBytes">The final input byte. This pointer will be iterated through in reverse (from end to start).</param>
		/// <param name="pOutBytes">The first output byte. This pointer will be iterated through in normal order (from start to end).</param>
		template<std::size_t Iteration_>
		constexpr void _reverse_bytes(const std::uint8_t* pInBytes, std::uint8_t* pOutBytes) const
		{
			if constexpr (Iteration_ < NumBytes_)
			{
				std::uint8_t& outByte = *(pOutBytes + Iteration_);
				outByte = *(pInBytes - Iteration_);
				outByte = (outByte & 0xF0) >> 4 | (outByte & 0x0F) << 4; // Swap HI and LO
				outByte = (outByte & 0xCC) >> 2 | (outByte & 0x33) << 2; // Swap adjacent bits
				outByte = (outByte & 0xAA) >> 1 | (outByte & 0x55) << 1; // Swap adjacent single bits
				this->_reverse_bytes<Iteration_ + 1>(pInBytes, pOutBytes);
			}
		}
	};

	template<typename T>
	struct create_mask
	{
	private:
		template<std::size_t NumBits_>
		static constexpr T _compile_time_mask_creation_iteration(T mask_)
		{
			static_assert(NumBits_ <= (sizeof(T) * CHAR_BIT), "Requested the construction of a CompileTimeMask through create_mask<T> with more bits than in the type T.");
			if constexpr (NumBits_ > 0)
			{
				if constexpr (NumBits_ == 1)
				{
					return mask_ | 1;
				}
				else
				{
					constexpr std::size_t Offset_ = NumBits_ - 1;
					return _compile_time_mask_creation_iteration<Offset_>(mask_ | (1 << Offset_));
				}
			}
			else
			{
				return mask_;
			}
		}

	public:
		static constexpr std::size_t NumBits_ = sizeof(T) * CHAR_BIT;
		static constexpr std::size_t FinalBitOffset_ = NumBits_ - 1;
		constexpr create_mask()
		{
		}
		constexpr T operator()(const std::size_t numBits) const
		{
			T out = T();
			for (std::size_t i = 0, end = numBits <= NumBits_ ? numBits : NumBits_; i < end; ++i)
			{
				out |= (1 << (NumBits_ - i));
			}
			return out;
		}

		template<std::size_t NumBits_>
		static constexpr T MaskN = _compile_time_mask_creation_iteration<NumBits_>(T());
	};

	/// <summary>
	/// <para> Functor for performing truncation via the function operator(). Includes a constexpr variation for compile time rounding. </para>
	/// <para> Truncation rounds a value toward zero. </para>
	/// </summary>
	/// <typeparam name="In_">Type being input for truncation.</typeparam>
	/// <typeparam name="Out_">Type to output the truncated result as.</typeparam>
	template<typename In_, typename Out_>
	struct trunc_diff_types
	{
		constexpr trunc_diff_types()
		{
		}

		Out_ operator()(const In_& in_) const
		{
			if constexpr (std::is_integral_v<In_>)
			{
				return static_cast<Out_>(in_);
			}
			else
			{
				using StrippedIn_ = std::remove_cv_t<In_>;
				if constexpr (std::is_same_v<float, StrippedIn_>)
				{
					return static_cast<Out_>(truncf(in_));
				}
				else if constexpr (std::is_same_v<double, StrippedIn_>)
				{
					return static_cast<Out_>(trunc(in_));
				}
				else if constexpr (std::is_same_v<long double, StrippedIn_>)
				{
					return static_cast<Out_>(truncl(in_));
				}
				else
				{
					// Unknown type response
					return static_cast<Out_>(trunc(in_));
				}
			}
		}

		/// <summary> Constexpr variation of this rounding function. Note that this may have some inaccuracies in comparison to operator(). </summary>
		/// <param name="in_">Value to round.</param>
		/// <returns>The passed value rounded without use of the standard rounding functions.</returns>
		static constexpr Out_ ConstexprRound(const In_& in_)
		{
			if constexpr (std::is_integral_v<In_>)
			{
				// No need to round since already an integer
				return static_cast<Out_>(in_);
			}
			else
			{
				// Cast to an integer to truncate (faster than standard trunc funcs).
				using BestIntCast_ = EmuCore::TMPHelpers::best_int_rep_t<In_>;
				if constexpr (std::is_same_v<Out_, BestIntCast_>)
				{
					return static_cast<Out_>(in_);
				}
				else
				{
					return static_cast<Out_>(static_cast<BestIntCast_>(in_));
				}
			}
		}
	};

	/// <summary>
	/// <para> Functor for performing flooring via the function operator(). Includes a constexpr variation for compile time rounding. </para>
	/// <para> Flooring rounds a value toward negative infinity. </para>
	/// </summary>
	/// <typeparam name="In_">Type being input for flooring.</typeparam>
	/// <typeparam name="Out_">Type to output the floored result as.</typeparam>
	template<typename In_, typename Out_>
	struct floor_diff_types
	{
		constexpr floor_diff_types()
		{
		}

		Out_ operator()(const In_& in_) const
		{
			if constexpr (std::is_integral_v<In_>)
			{
				return static_cast<Out_>(in_);
			}
			else
			{
				using StrippedIn_ = std::remove_cv_t<In_>;
				if constexpr (std::is_same_v<float, StrippedIn_>)
				{
					return static_cast<Out_>(floorf(in_));
				}
				else if constexpr (std::is_same_v<double, StrippedIn_>)
				{
					return static_cast<Out_>(floor(in_));
				}
				else if constexpr (std::is_same_v<long double, StrippedIn_>)
				{
					return static_cast<Out_>(floorl(in_));
				}
				else
				{
					// Unknown type response
					return static_cast<Out_>(floor(in_));
				}
			}
		}

		/// <summary> Constexpr variation of this rounding function. Note that this may have some inaccuracies in comparison to operator(). </summary>
		/// <param name="in_">Value to round.</param>
		/// <returns>The passed value rounded without use of the standard rounding functions.</returns>
		static constexpr Out_ ConstexprRound(const In_ in_)
		{
			if constexpr (std::is_integral_v<In_>)
			{
				// No need to round since already an integer
				return static_cast<Out_>(in_);
			}
			else
			{
				using BestIntCast_ = EmuCore::TMPHelpers::best_int_rep_t<In_>;
				const BestIntCast_ cast_in_ = static_cast<BestIntCast_>(in_);
				
				// Cast truncation is enough to floor when positive.
				// When negative, the truncation will give a ceil value instead, so subtract 1 if it ends up greater (if equal, already rounded).
				return static_cast<Out_>(cast_in_ - (cast_in_ > in_));
			}
		}
	};

	/// <summary>
	/// <para> Functor for performing ceiling via the function operator(). Includes a constexpr variation for compile time rounding. </para>
	/// <para> Flooring rounds a value toward positive infinity. </para>
	/// </summary>
	/// <typeparam name="In_">Type being input for ceiling.</typeparam>
	/// <typeparam name="Out_">Type to output the ceiled result as.</typeparam>
	template<typename In_, typename Out_>
	struct ceil_diff_types
	{
		constexpr ceil_diff_types()
		{
		}

		Out_ operator()(const In_& in_) const
		{
			if constexpr (std::is_integral_v<In_>)
			{
				return static_cast<Out_>(in_);
			}
			else
			{
				using StrippedIn_ = std::remove_cv_t<In_>;
				if constexpr (std::is_same_v<float, StrippedIn_>)
				{
					return static_cast<Out_>(ceilf(in_));
				}
				else if constexpr (std::is_same_v<double, StrippedIn_>)
				{
					return static_cast<Out_>(ceil(in_));
				}
				else if constexpr (std::is_same_v<long double, StrippedIn_>)
				{
					return static_cast<Out_>(ceill(in_));
				}
				else
				{
					// Unknown type response
					return static_cast<Out_>(ceil(in_));
				}
			}
		}

		/// <summary> Constexpr variation of this rounding function. Note that this may have some inaccuracies in comparison to operator(). </summary>
		/// <param name="in_">Value to round.</param>
		/// <returns>The passed value rounded without use of the standard rounding functions.</returns>
		static constexpr Out_ ConstexprRound(const In_& in_)
		{
			if constexpr (std::is_integral_v<In_>)
			{
				// No need to round since already an integer
				return static_cast<Out_>(in_);
			}
			else
			{
				using BestIntCast_ = EmuCore::TMPHelpers::best_int_rep_t<In_>;
				const BestIntCast_ cast_in_ = static_cast<BestIntCast_>(in_);

				// Cast truncation is enough to ceil when negative.
				// When positive, the truncation will give a floor value instead, so add 1 if it ends up less (if equal, already rounded).
				return static_cast<Out_>(cast_in_ + (cast_in_ < in_));
			}
		}
	};
}

#endif
