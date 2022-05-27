#ifndef EMU_MATH_FAST_VECTOR_T_H_INC_
#define EMU_MATH_FAST_VECTOR_T_H_INC_ 1

#include "../../Vector.h"
#include "../../../EmuCore/TMPHelpers/TypeConvertors.h"
#include "../../../EmuCore/TMPHelpers/Values.h"
#include "../../../EmuSIMD/SIMDHelpers.h"

#include <array>

#include <iostream>

namespace EmuMath
{
	/// <summary>
	/// <para> Generic Vector that makes explicit use of SIMD registers to gain a speed boost. </para>
	/// <para> Only accepts value type arguments, and ignore const/volatile qualification. </para>
	/// <para> May select a specific bit-width of the encapsulated registers; defaults to 128-bit, but accepts 256-bit and 512-bit too. </para>
	/// </summary>
	template<std::size_t Size_, typename T_, std::size_t RegisterWidth_ = 128>
	struct FastVector
	{
	public:
		static constexpr std::size_t size = Size_;
		static constexpr std::size_t register_width = RegisterWidth_ > 0 ? RegisterWidth_ : 1;

		using this_type = FastVector<Size_, T_, RegisterWidth_>;
		using vector_type = EmuMath::Vector<Size_, T_>;
		using value_type = typename std::remove_cv<T_>::type;
		using register_type = typename EmuSIMD::TMP::register_type<value_type, register_width>::type;
		using index_sequence = std::make_index_sequence<size>;

		/// <summary> Boolean indicating if this Vector's encapsulated type is integral. </summary>
		static constexpr bool is_integral = std::is_integral<value_type>::value;
		/// <summary> Boolean indicating if this Vector's encapsulated type is floating-point. </summary>
		static constexpr bool is_floating_point = std::is_floating_point<value_type>::value;
		/// <summary> Boolean indicating if this Vector's encapsulated type is signed. </summary>
		static constexpr bool is_signed = std::is_signed<value_type>::value;

		/// <summary> The number of bytes consumed by a single element in this Vector. </summary>
		static constexpr std::size_t per_element_byte_size = sizeof(value_type);
		/// <summary> The number of bits consumed by a single element in this Vector with 8-bit bytes, regardless of the value of CHAR_BIT. </summary>
		static constexpr std::size_t per_element_width = per_element_byte_size * 8;
		/// <summary> The total number of bits required for every element to be accounted for within this Vector. </summary>
		static constexpr std::size_t total_element_width = per_element_width * size;
		/// <summary> The total number of elements accounted for within a single register. </summary>
		static constexpr std::size_t elements_per_register = register_width / per_element_width;
		/// <summary> 
		/// <para>
		///		Boolean indicating if a partial SIMD register is required to represent this full Vector 
		///		(for example, 192 bits are required while using 128-bit registers). 
		/// </para>
		/// </summary>
		static constexpr bool requires_partial_register = (total_element_width % register_width) != 0;
		/// <summary> The number of elements encapsulted by the partial end register if this Vector has one. If it does not have a partial register, this is 0. </summary>
		static constexpr std::size_t partial_register_length = requires_partial_register ? (size % elements_per_register) : 0;
		/// <summary> The number of registers required to form this Vector. </summary>
		static constexpr std::size_t num_registers = (total_element_width / register_width) + requires_partial_register;
		/// <summary> Boolean indicating if the underlying implementation of this Vector makes use of multiple SIMD registers. </summary>
		static constexpr bool contains_multiple_registers = num_registers > 1;

		/// <summary>
		/// <para> 
		///		The type used to store the register data in this Vector's `data` member. 
		///		An array of register_type if `contains_multiple_registers == true`. 
		///		Otherwise, aliases directly to `register_type`.
		/// </para>
		/// </summary>
		using data_type = std::conditional_t<contains_multiple_registers, std::array<register_type, num_registers>, register_type>;
		/// <summary> Index sequence that may be used to statically iterate over this Vector's registers if it contains multiple. </summary>
		using register_index_sequence = std::make_index_sequence<num_registers>;

#pragma region CONSTRUCTOR_VALIDATORS
	public:
		template<typename...Args_>
		[[nodiscard]] static constexpr inline bool valid_variadic_construction_args()
		{
			constexpr std::size_t num_args = sizeof...(Args_);
			if constexpr (num_args == 0)
			{
				// Reserved for default
				return false;
			}
			if constexpr (num_args == 1)
			{
				using single_arg = typename EmuCore::TMP::first_variadic_arg<Args_...>::type;
				using single_arg_uq = typename EmuCore::TMP::remove_ref_cv<single_arg>::type;
				if constexpr (std::is_same_v<this_type, single_arg_uq>)
				{
					// Reserved for copy/move construction
					return false;
				}
				else
				{
					// TODO: VALIDATE SINGLE ARG
					return false;
				}
			}
			else
			{
				// TODO: VALIDATE MULTI ARG
				return false;
			}
		}
#pragma endregion

#pragma region CONSTRUCTORS
	public:
		constexpr inline FastVector() : data()
		{
		}

		constexpr inline FastVector(const EmuMath::FastVector<Size_, T_, RegisterWidth_>& to_copy_) : data(_make_copy(to_copy_))
		{
		}

		constexpr inline FastVector(EmuMath::FastVector<Size_, T_, RegisterWidth_>&& to_move_) : data(_do_move(std::move(to_move_)))
		{
		}

		constexpr inline FastVector(value_type to_set_all_to_) : data(_do_set_all_same(to_set_all_to_))
		{
		}

		template<typename...ConstructionArgs_, typename = std::enable_if_t<valid_variadic_construction_args<ConstructionArgs_...>()>>
		constexpr inline FastVector(ConstructionArgs_&&...args_) : data(_do_variadic_construction(std::forward<ConstructionArgs_>(args_...)))
		{
		}
#pragma endregion

#pragma region EXTRACTION
	public:
		/// <summary>
		/// <para> Extracts the data from this Vector's register(s) and stores it in a more clearly readable EmuMath::Vector in memory. </para>
		/// <para> The output Vector type may be customised, but by default it will use the same Size_ as this Vector and this Vector's value_type as its T_ argument. </para>
		/// <para>
		///		Note that this Vector may contain non-zero data in indices that are not within its encapsulated range, 
		///		but the output Vector will always have those indices initialised as default.
		/// </para>
		/// <para>References may not be used for the output Vector.</para>
		/// </summary>
		/// <returns>EmuMath Vector of the desired type containing data equivalent to that encapsulated by this Vector.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type, typename = std::enable_if_t<!std::is_reference_v<OutT_>>>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> Store() const
		{
			constexpr std::size_t required_register_count = (OutSize_ / elements_per_register) + (OutSize_ % elements_per_register != 0);
			value_type extracted[elements_per_register * required_register_count];
			_store_all<required_register_count>(extracted);
			return _make_normal_vector<OutSize_, OutT_, size>(extracted, std::make_index_sequence<OutSize_>());
		}

		template<typename OutT_ = value_type, typename = std::enable_if_t<!std::is_reference_v<OutT_>>>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, OutT_> Store() const
		{
			return Store<size, OutT_>();
		}

		/// <summary>
		/// <para> Extracts the data from this Vector's register(s) and stores it within the passed EmuMath Vector, starting from the provided offset in the output Vector. </para>
		/// <para> Where compatible, register data will be dumped directly into output indices. Where types are different, this will perform conversions for all indices. </para>
		/// </summary>
		/// <param name="out_">EmuMath Vector reference to output to.</param>
		template<std::size_t WriteOffset_ = 0, std::size_t OutSize_, typename OutT_>
		constexpr inline void Store(EmuMath::Vector<OutSize_, OutT_>& out_) const
		{
			// If write offset is greater than size, we of course do nothing
			if constexpr (WriteOffset_ < OutSize_)
			{
				using out_vector_type = EmuMath::Vector<OutSize_, OutT_>;
				constexpr std::size_t num_output_indices = OutSize_ - WriteOffset_;
				constexpr std::size_t out_partial_length = num_output_indices % elements_per_register;
				constexpr std::size_t required_register_count = (num_output_indices / elements_per_register) + (out_partial_length != 0);
				_store_to_non_uniform<required_register_count, out_partial_length>(out_.data<WriteOffset_>());
			}
		}

		/// <summary>
		/// <para> Extracts all data from this Vector's register(s) and stores it within contiguous memory via the passed pointer. </para>
		/// <para> Where compatible, register data will be dumped directly into output memory. Where types are different, this will perform conversions. </para>
		/// <para> 
		///		By default, extra data contained within the Vector will be ignored and only this Vector's size worth of elements will be output. 
		///		To include indices that are technically not contained by the Vector, pass true as a template argument for FullWidth_.
		/// </para>
		/// </summary>
		/// <typeparam name="Out_"></typeparam>
		/// <param name="p_out_"></param>
		template<bool FullWidth_ = false, typename Out_>
		constexpr inline void Store(Out_* p_out_) const
		{
			_store_to_non_uniform<num_registers, FullWidth_ ? 0 : partial_register_length>(out_);
		}
#pragma endregion

#pragma region VECTOR_DATA
	public:
		/// <summary>
		/// <para> Underlying SIMD component of this Vector. </para>
		/// <para> If this Vector requires only 1 register, this will be that register. </para>
		/// <para> If this Vector requires multiple registers, this will be an array of registers. </para>
		/// <para> It is recommended to avoid using this unless you know what you are doing. </para>
		/// </summary>
		data_type data;
#pragma endregion

	private:
		static constexpr bool _do_static_assert()
		{
			if constexpr (Size_ == 0)
			{
				static_assert(EmuCore::TMP::get_false<T_>(), "Passed 0 as the Size_ for an EmuMath::FastVector. The Vector must account for at least 1 element.");
				return false;
			}
			else if constexpr (RegisterWidth_ != 128 && RegisterWidth_ != 256 && RegisterWidth_ != 512)
			{
				static_assert(EmuCore::TMP::get_false<T_>(), "Invalid RegisterWidth_ provided to an EmuMath::FastVector. Valid values are 128, 256, 512.");
				return false;
			}
			else if constexpr (std::is_reference_v<T_>)
			{
				static_assert(EmuCore::TMP::get_false<T_>(), "Passed a reference type T_ to an EmuMath::FastVector. Reference types are not allowed for these templates.");
				return false;
			}
			else if constexpr (std::is_same_v<register_type, void>)
			{
				static_assert
				(
					EmuCore::TMP::get_false<T_>(),
					"Unable to successfully form a register_type for an EmuMath::FastVector. This is likely due to the provided T_ argument."
				);
				return false;
			}
			else
			{
				return true;
			}
		}

		template<typename...Args_>
		static constexpr inline data_type _do_variadic_construction(Args_&&...args_)
		{
			return {};
		}

		template<std::size_t OutSize_, typename OutT_, std::size_t SrcSize_, std::size_t...OutIndices_>
		static constexpr inline EmuMath::Vector<OutSize_, OutT_> _make_normal_vector(value_type* p_src_, std::index_sequence<OutIndices_...> out_indices_)
		{
			return EmuMath::Vector<OutSize_, OutT_>(_move_src_or_default<OutIndices_, SrcSize_>(p_src_)...);
		}

		template<std::size_t Index_, std::size_t SrcSize_>
		static constexpr inline typename std::conditional<(Index_ < SrcSize_), value_type&&, value_type>::type _move_src_or_default(value_type* p_src_)
		{
			if constexpr (Index_ < SrcSize_)
			{
				return std::move(*(p_src_ + Index_));
			}
			else
			{
				return value_type();
			}
		}

		template<std::size_t NumRegisters_>
		constexpr inline void _store_all(value_type* p_out_) const
		{
			if constexpr (contains_multiple_registers)
			{
				_store_all_multiple_registers(p_out_, std::make_index_sequence<NumRegisters_>());
			}
			else
			{
				EmuSIMD::store(data, p_out_);
			}
		}

		template<std::size_t...RegisterIndices_>
		constexpr inline void _store_all_multiple_registers(value_type* p_out_, std::index_sequence<RegisterIndices_...> indices_) const
		{
			(EmuSIMD::store(data[RegisterIndices_], p_out_ + (RegisterIndices_ * elements_per_register)), ...);
		}

		template<std::size_t NumRegisters_, std::size_t PartialLength_, typename Out_>
		constexpr inline void _store_to_non_uniform(Out_* p_out_) const
		{
			if constexpr (PartialLength_ != 0)
			{
				constexpr std::size_t NumFullRegisters_ = NumRegisters_ - 1;
				if constexpr (NumFullRegisters_ == 0)
				{
					_store_partial<0, PartialLength_>(p_out_);
				}
				else
				{
					constexpr std::size_t TotalFullRegistersLength_ = NumFullRegisters_ * elements_per_register;

					if constexpr (std::is_same_v<typename EmuCore::TMP::remove_ref_cv<Out_>::type, value_type>)
					{
						// No intermediate conversion needed, so we can just store straight to the output
						_store_all<NumFullRegisters_>(p_out_);
					}
					else
					{
						value_type dumped[TotalFullRegistersLength_];
						_store_all<NumFullRegisters_>(dumped);
						_store_range_non_uniform<0>(p_out_, dumped, std::make_index_sequence<TotalFullRegistersLength_>());
					}

					_store_partial<TotalFullRegistersLength_, TotalFullRegistersLength_ + PartialLength_>(p_out_);
				}
			}
			else
			{
				_store_all<NumRegisters_>(p_out_);
			}
		}

		template<std::size_t From_, std::size_t To_, typename Out_>
		constexpr inline void _store_partial(Out_* p_out_) const
		{
			constexpr std::size_t out_range = To_ - From_;
			if constexpr (contains_multiple_registers)
			{
				constexpr std::size_t register_index = From_ / elements_per_register;
				if constexpr (out_range == 1 && register_width == 128)
				{
					*p_out_ = static_cast<Out_>(EmuSIMD::get_index<0, value_type, per_element_width>(data[register_index]));
				}
				else
				{
					value_type dumped[elements_per_register];
					EmuSIMD::store(data[register_index], dumped);
					_store_range_non_uniform<From_>(p_out_, dumped, std::make_index_sequence<out_range>());
				}
			}
			else
			{
				if constexpr (out_range == 1 && register_width == 128)
				{
					// Prefer this approach here as it is typically faster in this scenario
					*p_out_ = static_cast<Out_>(EmuSIMD::get_index<0, value_type, per_element_width>(data));
				}
				else
				{
					value_type dumped[elements_per_register];
					EmuSIMD::store(data, dumped);
					_store_range_non_uniform<From_>(p_out_, dumped, std::make_index_sequence<out_range>());
				}
			}
		}

		template<std::size_t OutOffset_, typename Out_, std::size_t...Indices_>
		static constexpr inline void _store_range_non_uniform(Out_* p_out_, value_type* p_src_, std::index_sequence<Indices_...> indices_)
		{
			(
				(*(p_out_ + OutOffset_ + Indices_) = static_cast<Out_>(*(p_src_ + Indices_))), 
				...
			);
		}

		static constexpr inline data_type _make_copy(const this_type& to_copy_)
		{
			if constexpr (contains_multiple_registers)
			{
				return _make_array_copy(to_copy_, index_sequence());
			}
			else
			{
				return to_copy_.data;
			}
		}

		static constexpr inline data_type _do_move(this_type&& to_move_)
		{
			if constexpr (contains_multiple_registers)
			{
				return _do_array_move(std::move(to_move_), index_sequence());
			}
			else
			{
				return data_type(std::move(to_move_.data));
			}
		}

		template<std::size_t...Indices_>
		static constexpr inline data_type _make_array_copy(const this_type& to_copy_, std::index_sequence<Indices_...> indices_)
		{
			return data_type({ register_type(to_copy_.data[Indices_])... });
		}

		template<std::size_t...Indices_>
		static constexpr inline data_type _do_array_move(this_type&& to_move_, std::index_sequence<Indices_...> indices_)
		{
			return data_type({ register_type(std::move(to_move_.data[Indices_]))... });
		}

		static constexpr inline data_type _do_set_all_same(const value_type& to_set_all_to_)
		{
			if constexpr (contains_multiple_registers)
			{
				return _do_array_set_all_same(to_set_all_to_, register_index_sequence());
			}
			else
			{
				return EmuSIMD::set1<data_type, per_element_width>(to_set_all_to_);
			}
		}

		template<std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_set_all_same(const value_type& to_set_all_to_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type({ _set_all_same_discard_index<RegisterIndices_>(to_set_all_to_)... });
		}

		template<std::size_t ToDiscard_>
		static constexpr inline register_type _set_all_same_discard_index(const value_type& to_set_all_to_)
		{
			return EmuSIMD::set1<register_type, per_element_width>(to_set_all_to_);
		}

	public:
		static_assert(_do_static_assert(), "Unable to successfully form an EmuMath::FastVector instance.");
				
	};
}

template<std::size_t Size_, typename T_, std::size_t RegisterWidth_>
inline std::ostream& operator<<(std::ostream& str_, const EmuMath::FastVector<Size_, T_, RegisterWidth_>& vector_)
{
	str_ << vector_.Store();
	return str_;
}

template<std::size_t Size_, typename T_, std::size_t RegisterWidth_>
inline std::wostream& operator<<(std::wostream& w_str_, const EmuMath::FastVector<Size_, T_, RegisterWidth_>& vector_)
{
	w_str_ << vector_.Store();
	return w_str_;
}

#endif
