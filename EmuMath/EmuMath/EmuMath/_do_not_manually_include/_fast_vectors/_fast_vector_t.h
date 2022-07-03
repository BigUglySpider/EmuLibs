#ifndef EMU_MATH_FAST_VECTOR_T_H_INC_
#define EMU_MATH_FAST_VECTOR_T_H_INC_ 1

#include "_underlying_helpers/_fast_vector_tmp.h"
#include "../../Vector.h"
#include "../../../EmuCore/CommonTypes/ComparisonEnum.h"
#include "../../../EmuCore/TMPHelpers/TypeConvertors.h"
#include "../../../EmuCore/TMPHelpers/Values.h"
#include "../../../EmuSIMD/SIMDHelpers.h"

#include <array>

#include <iostream>

namespace EmuMath
{
	/// <summary>
	/// <para> Generic Vector that makes explicit use of SIMD registers to gain a speed boost. </para>
	/// <para> Only accepts value type arguments, and ignores const/volatile qualification. </para>
	/// <para> May select a specific bit-width of the encapsulated registers; defaults to 128-bit, but accepts 256-bit and 512-bit too. </para>
	/// <para>
	///		Automatic masking will be performed for operations where the result may otherwise be affected by non-contained indices. 
	///		As such, if it is certain that a Vector may not have values that interfere with output for such desired operations, 
	///		it is recommended to choose a size that does not leave any empty register space to avoid these masking operations. (e.g. `4, float` instead of `3, float`).
	/// </para>
	/// <para> Where possible, this type will provide named size alternative functions to mimic a size without requiring a conversion or mask. </para>
	/// </summary>
	template<std::size_t Size_, typename T_, std::size_t RegisterWidth_>
	struct FastVector
	{
#pragma region GENERAL_STATIC_INFO
	public:
		/// <summary> The number of elements that this Vector behaves to encapsulate. </summary>
		static constexpr std::size_t size = Size_;
		/// <summary> The width provided for this Vector's registers to use, in bits. </summary>
		static constexpr std::size_t register_width = RegisterWidth_ > 0 ? RegisterWidth_ : 1;

		/// <summary> Alias to this Vector type. </summary>
		using this_type = FastVector<Size_, T_, RegisterWidth_>;
		/// <summary> Alias to the type of values within this Vector. </summary>
		using value_type = typename std::remove_cv<T_>::type;
		/// <summary> Alias to the EmuMath::Vector type composed of this Vector's size and value_type. </summary>
		using vector_type = EmuMath::Vector<size, value_type>;
		/// <summary> Alias to the type of SIMD register used for this Vector's data. </summary>
		using register_type = typename EmuSIMD::TMP::register_type<value_type, register_width>::type;
		/// <summary> Alias to the argument type used to pass an instance of this Vector's register_type. </summary>
		using register_arg_type = typename EmuSIMD::TMP::register_arg_type<value_type, register_width>::type;
		/// <summary> Alias to the register type used as an argument for the number of shifts performed when a register argument is used instead of a constant. </summary>
		using shift_register_type = __m128i;
		/// <summary> The number of bits each element is interpreted to consume within this Vector's shift_register_type, with 8-bit bytes regardless of CHAR_BIT. </summary>
		static constexpr std::size_t shift_register_per_element_width = 64;
		/// <summary> The preferred floating-point type for this Vector, used for floating-point-based calculations using this Vector. </summary>
		using preferred_floating_point = typename std::conditional<(sizeof(value_type) >= 64), double, float>::type;

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
		/// <summary> The total number of elements contained within this Vector's regiseters, including those exceeding its encapsulated range. </summary>
		static constexpr std::size_t full_width_size = elements_per_register * num_registers;

		/// <summary>
		/// <para> 
		///		The type used to store the register data in this Vector's `data` member. 
		///		An array of register_type if `contains_multiple_registers == true`. 
		///		Otherwise, aliases directly to `register_type`.
		/// </para>
		/// </summary>
		using data_type = std::conditional_t<contains_multiple_registers, std::array<register_type, num_registers>, register_type>;

		/// <summary> Standard index sequence that may be used to statically iterate over this Vector's encapsulated elements. </summary>
		using index_sequence = std::make_index_sequence<size>;
		/// <summary> 
		/// <para>
		///		Standard index sequence that may be used to statically iterate over every element of this Vector's registers, 
		///		including those exceeding its encapsulated range.
		/// </para>
		/// </summary>
		using full_width_index_sequence = std::make_index_sequence<full_width_size>;
		/// <summary> Standard index sequence that may be used to statically iterate over this Vector's registers if it contains multiple. </summary>
		using register_index_sequence = std::make_index_sequence<num_registers>;
#pragma endregion

#pragma region HELPER_MASKS
	public:
		struct _make_partial_mask
		{
		public:
			template<bool Included_, typename IndexSequence_>
			struct _underlying_mask_generation_maker
			{
				using type = void;
			};
			template<std::size_t...Indices_>
			struct _underlying_mask_generation_maker<false, std::index_sequence<Indices_...>>
			{
				using type = typename EmuSIMD::index_mask<register_type, (Indices_ < size)...>;
			};
			template<std::size_t...Indices_>
			struct _underlying_mask_generation_maker<true, std::index_sequence<Indices_...>>
			{
				using type = typename EmuSIMD::index_mask<register_type, (Indices_ >= size)...>;
			};

			static constexpr std::size_t _offset = (num_registers - 1) * elements_per_register;
			using _partial_index_sequence = EmuCore::TMP::make_offset_reverse_index_sequence<_offset, elements_per_register>;
			
		public:
			using excluded_generator = typename _underlying_mask_generation_maker<false, _partial_index_sequence>::type;
			using included_generator = typename _underlying_mask_generation_maker<true, _partial_index_sequence>::type;
		};
#pragma endregion

#pragma region GENERAL_HELPER_TYPES
	private:
		template<std::size_t FullWidthIndex_, typename Vector_>
		struct _vector_get_index_for_load_result
		{
			using _vector_uq = typename EmuCore::TMP::remove_ref_cv<Vector_>::type;
			using _get_result = decltype(std::declval<_vector_uq>().AtTheoretical<FullWidthIndex_>());

			using type = typename std::conditional
				<
				(FullWidthIndex_ > _vector_uq::size) || std::is_lvalue_reference_v<Vector_>,
				_get_result,
				decltype(std::move(std::declval<_get_result>()))
			>::type;
		};
	
	public:
		/// <summary>
		/// <para> Helper type for determining what an output type will be when using `GetRegisterTheoretical()`. </para>
		/// <para> If `RegisterIndex_` is a contained register index, type will be a (const-qualified if `IsConst_` is true) reference to this Vector's `register_type`. </para>
		/// <para> If `RegisterIndex_` exceeds this Vector type's register range, `type` will be this Vector's `register_type`. </para>
		/// </summary>
		template<std::size_t RegisterIndex_, bool IsConst_>
		struct theoretical_register_get_result
		{
			using type = typename std::conditional
			<
				(RegisterIndex_ < num_registers),
				typename EmuCore::TMP::conditional_const<IsConst_, register_type&>::type,
				register_type
			>::type;
		};
#pragma endregion

#pragma region STATIC_GETS
	public:
		static constexpr inline register_type make_partial_end_exclude_mask_register()
		{
			return _make_partial_mask::excluded_generator::get();
		}

		static constexpr inline register_type make_partial_end_only_mask_register()
		{
			return _make_partial_mask::included_generator::get();
		}

		/// <summary> Makes a FastVector of this type with all register bits set to 0. </summary>
		/// <returns>A newly constructed FastVector of this type with all register bits set to 0.</returns>
		static constexpr inline this_type make_all_zero()
		{
			return this_type(EmuSIMD::setzero<register_type>());
		}

		/// <summary> Makes a FastVector of this type with all register bits set to 1. </summary>
		/// <returns>A newly constructed FastVector of this type with all register bits set to 1.</returns>
		static constexpr inline this_type make_all_one()
		{
			return this_type(EmuSIMD::setallone<register_type>());
		}

		/// <summary> Creates a new register of this Vector's register_type with all bits set to 0. </summary>
		/// <returns>A newly created register_type with all register bits set to 0.</returns>
		static constexpr inline register_type make_all_zero_register()
		{
			return EmuSIMD::setzero<register_type>();
		}

		/// <summary> Creates a new register of this Vector's register_type with all bits set to 1. </summary>
		/// <returns>A newly created register_type with all register bits set to 1.</returns>
		static constexpr inline register_type make_all_one_register()
		{
			return EmuSIMD::setallone<register_type>();
		}

		/// <summary> Helper to create one instance of this Vector's register_type with all elements set to the provided val_. </summary>
		/// <param name="val_">Value to set all elements within the output register to.</param>
		/// <returns>A newly created register_type with all elements set to match val_.</returns>
		static constexpr inline register_type make_all_same_register(value_type val_)
		{
			return EmuSIMD::set1<register_type, per_element_width>(val_);
		}
#pragma endregion

#pragma region CONSTRUCTOR_VALIDATORS
	private:
		template<typename Arg_>
		static constexpr inline bool _is_reserved_for_single_explicitly_typed_constructor()
		{
			using arg_uq = typename EmuCore::TMP::remove_ref_cv<Arg_>::type;
			return
			(
				std::is_same_v<this_type, arg_uq> ||	// Reserved for copy/move construction
				std::is_same_v<value_type, arg_uq> ||	// Reserved for all-as-one construction
				std::is_same_v<value_type*, arg_uq>	 ||	// Reserved for load construction
				std::is_same_v<register_type, arg_uq> || std::is_same_v<register_arg_type, arg_uq>	// Reserved for all-registers-as-one construction
			);
		}

		template<typename...Args_>
		static constexpr inline bool _is_reserved_for_explicitly_typed_constructor()
		{
			constexpr std::size_t num_args = sizeof...(Args_);
			if (num_args == 0)
			{
				return true; // Reserved for default
			}
			else if (num_args == 1)
			{
				return _is_reserved_for_single_explicitly_typed_constructor<typename EmuCore::TMP::first_variadic_arg<Args_...>::type>();
			}
			else
			{
				return false;
			}
		}

		template<class Vector_, std::size_t...FullWidthIndices_>
		[[nodiscard]] static constexpr inline bool _may_create_from_all_normal_vector_indices(std::index_sequence<FullWidthIndices_...> indices_)
		{
			return (... && EmuCore::TMP::is_static_castable_v<typename _vector_get_index_for_load_result<FullWidthIndices_, Vector_>::type, value_type>);
		}

	public:
		/// <summary>
		/// <para> Returns a boolean indicating if the provided Arg_ is a valid argument for converting a normal EmuMath vector to a FastVector of this type. </para>
		/// <para> Note that this refers purely to the variadic constructor; it may be that an explictly-typed constructor is available but this returns false. </para>
		/// </summary>
		/// <returns>True if Arg_ is valid for a normal->fast Vector conversion; otherwise false.</returns>
		template<typename Arg_>
		[[nodiscard]] static constexpr inline bool valid_arg_for_normal_vector_conversion_construction()
		{
			using in_uq = typename EmuCore::TMP::remove_ref_cv<Arg_>::type;
			if constexpr (!EmuMath::TMP::is_emu_vector_v<in_uq>)
			{
				return false;
			}
			else
			{
				return _may_create_from_all_normal_vector_indices<Arg_>(full_width_index_sequence());
			}
		}

		/// <summary>
		/// <para> Returns a boolean indicating if the provided Args_ are valid for creating a FastVector with one argument per register. </para>
		/// <para> Note that this refers purely to the variadic constructor; it may be that an explictly-typed constructor is available but this returns false. </para>
		/// </summary>
		/// <returns>True if this FastVector type's registers can all be constructed using respective passed Args_; otherwise false.</returns>
		template<typename...Args_>
		[[nodiscard]] static constexpr inline bool valid_args_for_per_register_construction()
		{
			if constexpr (_is_reserved_for_explicitly_typed_constructor<Args_...>())
			{
				return false;
			}
			else
			{
				constexpr std::size_t num_args = sizeof...(Args_);
				if constexpr (num_args != num_registers)
				{
					return false;
				}
				else
				{
					if constexpr (num_args == 1)
					{
						using single_arg = typename EmuCore::TMP::first_variadic_arg<Args_...>::type;
						return
						(
							!valid_arg_for_normal_vector_conversion_construction<single_arg>() &&
							EmuCore::TMP::is_any_same_v<typename EmuCore::TMP::remove_ref_cv<single_arg>::type, register_type, register_arg_type>
						);
					}
					else
					{
						return (... && EmuCore::TMP::is_any_same_v<typename EmuCore::TMP::remove_ref_cv<Args_>::type, register_type, register_arg_type>);
					}
				}
			}
		}

		/// <summary>
		/// <para> Returns a boolean indicating if the provided Args_ are valid for creating a FastVector with one argument per element. </para>
		/// <para> Note that this refers purely to the variadic constructor; it may be that an explictly-typed constructor is available but this returns false. </para>
		/// </summary>
		/// <returns>True if this FastVector type's indices can all be constructed using the provided set of Args_; otherwise false.</returns>
		template<typename...Args_>
		[[nodiscard]] static constexpr inline bool valid_args_for_per_element_construction()
		{
			if constexpr (_is_reserved_for_explicitly_typed_constructor<Args_...>())
			{
				return false;
			}
			else
			{
				constexpr std::size_t num_args = sizeof...(Args_);
				if constexpr (num_args != size)
				{
					return false;
				}
				else
				{
					if constexpr (num_args == 1)
					{
						using single_arg = typename EmuCore::TMP::first_variadic_arg<Args_...>::type;
						return
						(
								!valid_arg_for_normal_vector_conversion_construction<single_arg>() &&
								!valid_args_for_per_register_construction<Args_...>() &&
								EmuCore::TMP::is_static_castable<decltype(std::forward<single_arg>(std::declval<single_arg>())), value_type>::value
						);
					}
					else
					{
						return 
						(
							!valid_args_for_per_register_construction<Args_...>() &&
							(... && EmuCore::TMP::is_static_castable_v<decltype(std::forward<Args_>(std::declval<Args_>())), value_type>)
						);
					}
				}
			}
		}

		/// <summary>
		/// <para> Blanket check to determine if this FastVector's variadic constructor can be invoked with the provided Args_. </para>
		/// <para> Note that this refers purely to the variadic constructor; it may be that an explictly-typed constructor is available but this returns false. </para>
		/// </summary>
		/// <returns>True if the variadic constructor of this FastVector can be invoked with the provided Args_; otherwise false.</returns>
		template<typename...Args_>
		[[nodiscard]] static constexpr inline bool valid_variadic_construction_args()
		{
			if constexpr (_is_reserved_for_explicitly_typed_constructor<Args_...>())
			{
				return false;
			}
			else
			{
				constexpr std::size_t num_args = sizeof...(Args_);
				using first_arg = typename EmuCore::TMP::first_variadic_arg<Args_...>::type;
				return
				(
					(num_args == 1 && valid_arg_for_normal_vector_conversion_construction<first_arg>()) ||
					valid_args_for_per_register_construction<Args_...>() ||
					valid_args_for_per_element_construction<Args_...>()
				);
			}
		}
#pragma endregion

#pragma region CONSTRUCTORS
	public:
		/// <summary>
		/// <para> Default constructor for a Vector, which uses the default construction method of its underlying SIMD registers.. </para>
		/// </summary>
		constexpr inline FastVector() noexcept : data()
		{
		}

		/// <summary>
		/// <para> Copy constructor for a FastVector which copies all respective elements of the passed FastVector of the same type. </para>
		/// </summary>
		/// <param name="to_copy_">Emu FastVector of the same type to copy.</param>
		constexpr inline FastVector(const EmuMath::FastVector<Size_, T_, RegisterWidth_>& to_copy_) noexcept : data(_make_copy(to_copy_))
		{
		}

		/// <summary>
		/// <para> Move constructor for a FastVector which moves all respective elements of the passed FastVector of the same type. </para>
		/// <para> Likely to be barely - if at all - different to copy construction. </para>
		/// </summary>
		/// <param name="to_move_">Emu FastVector of the same type to move.</param>
		constexpr inline FastVector(EmuMath::FastVector<Size_, T_, RegisterWidth_>&& to_move_) noexcept : data(_do_move(std::move(to_move_)))
		{
		}

		/// <summary>
		/// <para> All-as-one constructor for a FastVector which has all elements initialised to the same starting value. </para>
		/// </summary>
		/// <param name="to_set_all_to_">Value to set every element within the Vector to.</param>
		explicit constexpr inline FastVector(value_type to_set_all_to_) noexcept : data(_do_set_all_same(to_set_all_to_))
		{
		}

		/// <summary>
		/// <para> Variant of all-as-one constructor which instead initialises all registers to match the passed register of this Vector's register_type. </para>
		/// </summary>
		/// <param name="to_set_all_registers_to_">SIMD register of this Vector's register_type to initialise all of this Vector's registers as.</param>
		explicit constexpr inline FastVector(register_arg_type to_set_all_registers_to_) noexcept : data(_do_set_all_same_register(to_set_all_registers_to_))
		{
		}

		/// <summary>
		/// <para> Loading constructor for a FastVector which loads data directly from bytes in memory. </para>
		/// <para> This is a full-width load which considers only the width of the underlying registers; the passed pointer must account for this. </para>
		/// </summary>
		/// <param name="p_to_load_">Pointer to data that is contiguous for at least (`elements_per_register * num_registers`) elements.</param>
		explicit constexpr inline FastVector(const value_type* p_to_load_) : data(_do_load(p_to_load_))
		{
		}

		/// <summary>
		/// <para> Variadic constructor which is used for per-element construction and conversion construction. If available, the first possible in the list will be chosen: </para>
		/// <para>
		///		EmuMath::Vector conversion: Constructs the Vector using respective indices in a passed EmuMath::Vector argument, performing necessary conversions. 
		///		This will attempt optimised loads instead of sets where possible.
		///		Available where `sizeof...(Args_) == 1`, the argument is an EmuMath Vector, and all of its required theoretical indices may be used as a `value_type`.
		/// </para>
		/// <para>
		///		Per-register construction: Constructs the Vector using respective arguments to construct each register. 
		///		Available where `sizeof...(Args_) == num_registers` and all arguments are of this Vector's register_type.
		/// </para>
		/// <para>
		///		Per-element construction: Constructs the Vector using respective arguments to construct indices as in the matching variadic constructor of EmuMath::Vector. 
		///		Available where `sizeof...(Args_) == size)` and all arguments may be used as a `value_type`.
		/// </para>
		/// </summary>
		/// <param name="args_">Variadic arguments to construct the Vector via, as per the listed potential paths.</param>
		template<typename...ConstructionArgs_, typename = std::enable_if_t<valid_variadic_construction_args<ConstructionArgs_...>()>>
		explicit constexpr inline FastVector(ConstructionArgs_&&...args_) : data(_do_variadic_construction(std::forward<ConstructionArgs_>(args_)...))
		{
		}

	private:
		/// <summary>
		/// <para> Private constructor for creating a new instance of this FastVector type with a newly created data_type. Disabled if this Vector has 1 register. </para>
		/// </summary>
		template<typename = std::enable_if_t<contains_multiple_registers>>
		explicit constexpr inline FastVector(data_type&& data_) : data(std::move(data_))
		{
		}
#pragma endregion

#pragma region CONST_BASIC_ARITHMETIC
	public:
		/// <summary>
		/// <para> Adds the passed register to all registers encapsulated by this Vector. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in add operations with all registers encapsulated by this Vector.</param>
		/// <returns>New FastVector of this type resulting from the addition operation.</returns>
		[[nodiscard]] constexpr inline this_type Add(register_arg_type rhs_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_add(data, rhs_for_all_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::add<per_element_width>(data, rhs_for_all_));
			}
		}

		/// <summary>
		/// <para> Adds the passed scalar value to all elements within this Vector. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to add to all elements within this Vector.</param>
		/// <returns>New FastVector of this type resulting from the addition operation.</returns>
		[[nodiscard]] constexpr inline this_type Add(value_type rhs_for_all_) const
		{
			return Add(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Adds this Vector and the passed rhs_ Vector of the same type.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to add to this Vector.</param>
		/// <returns>New FastVector of this type resulting from the addition operation.</returns>
		[[nodiscard]] constexpr inline this_type Add(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_add(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::add<per_element_width>(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Subtracts the passed register from all registers encapsulated by this Vector. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in subtract operations with all registers encapsulated by this Vector.</param>
		/// <returns>New FastVector of this type resulting from the subtraction operation.</returns>
		[[nodiscard]] constexpr inline this_type Subtract(register_arg_type rhs_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_subtract(data, rhs_for_all_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::sub<per_element_width>(data, rhs_for_all_));
			}
		}

		/// <summary>
		/// <para> Subtracts the passed scalar value to all elements within this Vector. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to subtract from all elements within this Vector.</param>
		/// <returns>New FastVector of this type resulting from the subtraction operation.</returns>
		[[nodiscard]] constexpr inline this_type Subtract(value_type rhs_for_all_) const
		{
			return Subtract(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Subtracts this Vector and the passed rhs_ Vector of the same type.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to subtract from this Vector.</param>
		/// <returns>New FastVector of this type resulting from the subtraction operation.</returns>
		[[nodiscard]] constexpr inline this_type Subtract(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_subtract(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::sub<per_element_width>(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Multiplies all registers encapsulated by this Vector by the passed register. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in multiplication operations with all registers encapsulated by this Vector.</param>
		/// <returns>New FastVector of this type resulting from the multiplication operation.</returns>
		[[nodiscard]] constexpr inline this_type Multiply(register_arg_type rhs_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_multiply(data, rhs_for_all_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::mul_all<per_element_width>(data, rhs_for_all_));
			}
		}

		/// <summary>
		/// <para> Multiplies all elements within this Vector by the passed scalar value. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to multiply all elements within this Vector by.</param>
		/// <returns>New FastVector of this type resulting from the multiplication operation.</returns>
		[[nodiscard]] constexpr inline this_type Multiply(value_type rhs_for_all_) const
		{
			return Multiply(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Multiplies this Vector and the passed rhs_ Vector of the same type.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to multiply this Vector by.</param>
		/// <returns>New FastVector of this type resulting from the multiplication operation.</returns>
		[[nodiscard]] constexpr inline this_type Multiply(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_multiply(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::mul_all<per_element_width>(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Divides all registers encapsulated by this Vector by the passed register. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in division operations with all registers encapsulated by this Vector.</param>
		/// <returns>New FastVector of this type resulting from the division operation.</returns>
		[[nodiscard]] constexpr inline this_type Divide(register_arg_type rhs_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_divide(data, rhs_for_all_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::div<per_element_width, is_signed>(data, rhs_for_all_));
			}
		}

		/// <summary>
		/// <para> Divides all elements within this Vector by the passed scalar value. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to divide all elements within this Vector by.</param>
		/// <returns>New FastVector of this type resulting from the division operation.</returns>
		[[nodiscard]] constexpr inline this_type Divide(value_type rhs_for_all_) const
		{
			return Divide(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Divides this Vector and the passed rhs_ Vector of the same type.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to divide this Vector by.</param>
		/// <returns>New FastVector of this type resulting from the division operation.</returns>
		[[nodiscard]] constexpr inline this_type Divide(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_divide(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::div<per_element_width, is_signed>(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Modulo-divides all registers encapsulated by this Vector by the passed register. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in modulo-division operations with all registers encapsulated by this Vector.</param>
		/// <returns>New FastVector of this type resulting from the modulo-division operation.</returns>
		[[nodiscard]] constexpr inline this_type Mod(register_arg_type rhs_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_mod(data, rhs_for_all_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::mod<per_element_width, is_signed>(data, rhs_for_all_));
			}
		}

		/// <summary>
		/// <para> Modulo-divides all elements within this Vector by the passed scalar value. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to modulo-divide all elements within this Vector by.</param>
		/// <returns>New FastVector of this type resulting from the modulo-division operation.</returns>
		[[nodiscard]] constexpr inline this_type Mod(value_type rhs_for_all_) const
		{
			return Mod(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Modulo-divides this Vector and the passed rhs_ Vector of the same type.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to modulo-divide this Vector by.</param>
		/// <returns>New FastVector of this type resulting from the modulo-division operation.</returns>
		[[nodiscard]] constexpr inline this_type Mod(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_divide(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::mod<per_element_width, is_signed>(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Creates a negated form of this Vector, where each element will be set to -element.</para>
		/// </summary>
		/// <returns>New FastVector of this type resulting from the negation.</returns>
		[[nodiscard]] constexpr inline this_type Negate() const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_negate(data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::negate<per_element_width>(data));
			}
		}

		/// <summary>
		/// <para>
		///		Performs a fused multiply-add operation on this Vector with the passed operands, 
		///		multiplying it by `multiplier_` and adding `to_add_` to the intermediate multiplication result.
		/// </para>
		/// <para> A fused operation will not perform a floating-point round until the addition has been performed; as such, this may help with performance and/or accuracy. </para>
		/// <para> If an argument is of this Vector type, respective elements will be used. </para>
		/// <para> If an argument is of this Vector's register_type, respective register elements will be used for all registers. </para>
		/// <para> If an argument is of this Vector's value_type, it will be used to create an intermediate register to use with all elements. </para>
		/// </summary>
		/// <param name="multiplier_">Multiplier to use with this Vector to create the intermediate result before addition.</param>
		/// <param name="to_add_">Value(s) to add to the intermediate multiplication result before a floating-point round.</param>
		/// <returns>Vector resulting from the fused arithmetic operation.</returns>
		[[nodiscard]] constexpr inline this_type Fmadd(const this_type& multiplier_, const this_type& to_add_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_fmadd(data, multiplier_.data, to_add_.data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::fmadd<per_element_width>(data, multiplier_.data, to_add_.data));
			}
		}

		[[nodiscard]] constexpr inline this_type Fmadd(const this_type& multiplier_, register_arg_type to_add_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_fmadd(data, multiplier_.data, to_add_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::fmadd<per_element_width>(data, multiplier_.data, to_add_));
			}
		}

		[[nodiscard]] constexpr inline this_type Fmadd(register_arg_type multiplier_, const this_type& to_add_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_fmadd(data, multiplier_, to_add_.data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::fmadd<per_element_width>(data, multiplier_, to_add_.data));
			}
		}

		[[nodiscard]] constexpr inline this_type Fmadd(register_arg_type multiplier_, register_arg_type to_add_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_fmadd(data, multiplier_, to_add_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::fmadd<per_element_width>(data, multiplier_, to_add_));
			}
		}

		[[nodiscard]] constexpr inline this_type Fmadd(const this_type& multiplier_, value_type to_add_to_all_) const
		{
			return Fmadd(multiplier_, EmuSIMD::set1<register_type, per_element_width>(to_add_to_all_));
		}

		[[nodiscard]] constexpr inline this_type Fmadd(value_type multiplier_for_all_, const this_type& to_add_) const
		{
			return Fmadd(EmuSIMD::set1<register_type, per_element_width>(multiplier_for_all_), to_add_);
		}

		[[nodiscard]] constexpr inline this_type Fmadd(register_arg_type multiplier_, value_type to_add_to_all_) const
		{
			return Fmadd(multiplier_, EmuSIMD::set1<register_type, per_element_width>(to_add_to_all_));
		}

		[[nodiscard]] constexpr inline this_type Fmadd(value_type multiplier_for_all_, register_arg_type to_add_) const
		{
			return Fmadd(EmuSIMD::set1<register_type, per_element_width>(multiplier_for_all_), to_add_);
		}

		[[nodiscard]] constexpr inline this_type Fmadd(value_type multiplier_for_all_, value_type to_add_to_all_) const
		{
			return Fmadd(EmuSIMD::set1<register_type, per_element_width>(multiplier_for_all_), EmuSIMD::set1<register_type, per_element_width>(to_add_to_all_));
		}

		/// <summary>
		/// <para>
		///		Performs a fused multiply-subtract operation on this Vector with the passed operands, 
		///		multiplying it by `multiplier_` and subtracting `to_subtract_` from the intermediate multiplication result.
		/// </para>
		/// <para> A fused operation will not perform a floating-point round until the subtraction has been performed; as such, this may help with performance and/or accuracy. </para>
		/// <para> If an argument is of this Vector type, respective elements will be used. </para>
		/// <para> If an argument is of this Vector's register_type, respective register elements will be used for all registers. </para>
		/// <para> If an argument is of this Vector's value_type, it will be used to create an intermediate register to use with all elements. </para>
		/// </summary>
		/// <param name="multiplier_">Multiplier to use with this Vector to create the intermediate result before subtraction.</param>
		/// <param name="to_subtract_">Value(s) to subtract from the intermediate multiplication result before a floating-point round.</param>
		/// <returns>Vector resulting from the fused arithmetic operation.</returns>
		[[nodiscard]] constexpr inline this_type Fmsub(const this_type& multiplier_, const this_type& to_subtract_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_fmsub(data, multiplier_.data, to_subtract_.data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::fmsub<per_element_width>(data, multiplier_.data, to_subtract_.data));
			}
		}

		[[nodiscard]] constexpr inline this_type Fmsub(const this_type& multiplier_, register_arg_type to_subtract_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_fmsub(data, multiplier_.data, to_subtract_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::fmsub<per_element_width>(data, multiplier_.data, to_subtract_));
			}
		}

		[[nodiscard]] constexpr inline this_type Fmsub(register_arg_type multiplier_, const this_type& to_subtract_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_fmsub(data, multiplier_, to_subtract_.data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::fmsub<per_element_width>(data, multiplier_, to_subtract_.data));
			}
		}

		[[nodiscard]] constexpr inline this_type Fmsub(register_arg_type multiplier_, register_arg_type to_subtract_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_fmsub(data, multiplier_, to_subtract_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::fmsub<per_element_width>(data, multiplier_, to_subtract_));
			}
		}

		[[nodiscard]] constexpr inline this_type Fmsub(const this_type& multiplier_, value_type to_subtract_from_all_) const
		{
			return Fmsub(multiplier_, EmuSIMD::set1<register_type, per_element_width>(to_subtract_from_all_));
		}

		[[nodiscard]] constexpr inline this_type Fmsub(value_type multiplier_for_all_, const this_type& to_subtract_) const
		{
			return Fmsub(EmuSIMD::set1<register_type, per_element_width>(multiplier_for_all_), to_subtract_);
		}

		[[nodiscard]] constexpr inline this_type Fmsub(register_arg_type multiplier_, value_type to_subtract_from_all_) const
		{
			return Fmsub(multiplier_, EmuSIMD::set1<register_type, per_element_width>(to_subtract_from_all_));
		}

		[[nodiscard]] constexpr inline this_type Fmsub(value_type multiplier_for_all_, register_arg_type to_subtract_) const
		{
			return Fmsub(EmuSIMD::set1<register_type, per_element_width>(multiplier_for_all_), to_subtract_);
		}

		[[nodiscard]] constexpr inline this_type Fmsub(value_type multiplier_for_all_, value_type to_subtract_from_all_) const
		{
			return Fmsub(EmuSIMD::set1<register_type, per_element_width>(multiplier_for_all_), EmuSIMD::set1<register_type, per_element_width>(to_subtract_from_all_));
		}
#pragma endregion

#pragma region CONST_MISC_ARITHMETIC
	public:
		/// <summary>
		/// <para> Calculates the square root of elements within this Vector.</para>
		/// </summary>
		/// <returns>New FastVector of this type containing the square roots of respective elements.</returns>
		[[nodiscard]] constexpr inline this_type Sqrt() const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_sqrt<false>(data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::sqrt<per_element_width, is_signed>(data));
			}
		}

		/// <summary>
		/// <para> Calculates the reciprocal of the square root of elements within this Vector.</para>
		/// </summary>
		/// <returns>New FastVector of this type containing the reciprocal of square roots of respective elements (1.0 / sqrt).</returns>
		[[nodiscard]] constexpr inline this_type Rsqrt() const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_sqrt<true>(data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::rsqrt<per_element_width, is_signed>(data));
			}
		}

		/// <summary>
		/// <para> Rounds all elements within this Vector toward negative infinity, outputting the results as a new Vector. </para>
		/// </summary>
		/// <returns>New FastVector of this type containing the results of rounding.</returns>
		[[nodiscard]] constexpr inline this_type Floor() const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_floor(data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::floor(data));
			}
		}

		/// <summary>
		/// <para> Rounds all elements within this Vector toward positive infinity, outputting the results as a new Vector. </para>
		/// </summary>
		/// <returns>New FastVector of this type containing the results of rounding.</returns>
		[[nodiscard]] constexpr inline this_type Ceil() const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_ceil(data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::ceil(data));
			}
		}

		/// <summary>
		/// <para> Rounds all elements within this Vector toward 0, outputting the results as a new Vector. </para>
		/// </summary>
		/// <returns>New FastVector of this type containing the results of rounding.</returns>
		[[nodiscard]] constexpr inline this_type Trunc() const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_trunc(data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::trunc(data));
			}
		}

		/// <summary>
		/// <para> Outputs the absolute form of this Vector, where (x => x, -x => x). </para>
		/// </summary>
		/// <returns>New FastVector of this type containing the absolute form of this Vector.</returns>
		[[nodiscard]] constexpr inline this_type Abs() const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_abs(data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::abs<per_element_width, is_signed>(data));
			}
		}

		/// <summary>
		/// <para> Clamps the elements of this Vector to a minimum of the values of respective elements in the passed Vector. </para>
		/// </summary>
		/// <param name="min_">Vector to clamp this Vector to a minimum of.</param>
		/// <returns>Copy of this Vector with elements clamped to a minimum of respective elements of min_.</returns>
		[[nodiscard]] constexpr inline this_type ClampMin(const this_type& min_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_clamp_min(data, min_.data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::clamp_min<per_element_width, is_signed>(data, min_.data));
			}
		}

		/// <summary>
		/// <para> Clamps the registers of this Vector to a minimum of respective elements within the passed register. </para>
		/// </summary>
		/// <param name="min_">Register to clamp this Vector's registers via.</param>
		/// <returns>Copy of this Vector with its registers clamped to a minimum of the passed min_ register.</returns>
		[[nodiscard]] constexpr inline this_type ClampMin(register_arg_type min_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_clamp_min(data, min_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::clamp_min<per_element_width, is_signed>(data, min_));
			}
		}

		/// <summary>
		/// <para> Clamps all elements of this Vector to a minimum of the passed value </para>
		/// <para>
		///		This will create an intermediate SIMD register to perform the clamp. 
		///		If multiple uses of this clamp are required, it is recommended to create the intermediate register and pass that instead.
		/// </para>
		/// </summary>
		/// <param name="min_">Value to clamp all of this Vector's elements to a minimum of.</param>
		/// <returns>Copy of this Vector with elements clamped to a minimum of min_for_all_.</returns>
		[[nodiscard]] constexpr inline this_type ClampMin(value_type min_for_all_) const
		{
			return ClampMin(EmuSIMD::set1<register_type, per_element_width>(min_for_all_));
		}

		/// <summary>
		/// <para> Clamps the elements of this Vector to a maximum of the values of respective elements in the passed Vector. </para>
		/// </summary>
		/// <param name="max_">Vector to clamp this Vector to a maximum of.</param>
		/// <returns>Copy of this Vector with elements clamped to a maximum of respective elements of max_.</returns>
		[[nodiscard]] constexpr inline this_type ClampMax(const this_type& max_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_clamp_max(data, max_.data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::clamp_max<per_element_width, is_signed>(data, max_.data));
			}
		}

		/// <summary>
		/// <para> Clamps the registers of this Vector to a minimum of respective elements within the passed register. </para>
		/// </summary>
		/// <param name="min_">Register to clamp this Vector's registers via.</param>
		/// <returns>Copy of this Vector with its registers clamped to a maximum of the passed max_ register.</returns>
		[[nodiscard]] constexpr inline this_type ClampMax(register_arg_type max_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_clamp_max(data, max_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::clamp_max<per_element_width, is_signed>(data, max_));
			}
		}

		/// <summary>
		/// <para> Clamps all elements of this Vector to a minimum of the passed value </para>
		/// <para>
		///		This will create an intermediate SIMD register to perform the clamp. 
		///		If multiple uses of this clamp are required, it is recommended to create the intermediate register and pass that instead.
		/// </para>
		/// </summary>
		/// <param name="max_for_all_">Value to clamp all of this Vector's elements to a maximum of.</param>
		/// <returns>Copy of this Vector with elements clamped to a maximum of max_for_all_.</returns>
		[[nodiscard]] constexpr inline this_type ClampMax(value_type max_for_all_) const
		{
			return ClampMax(EmuSIMD::set1<register_type, per_element_width>(max_for_all_));
		}

		/// <summary>
		/// <para> Clamps the elements of this Vector to the range of the values of respective elements in the passed arguments. </para>
		/// <para> If an argument is a Vector of this type, respective elements will be clamped to it. </para>
		/// <para> If an argument is of this Vector's register_type, it will be used to clamp respective elements of all registers. </para>
		/// <para> If an argument is of this Vector's value_type, it will be used to clamp all elements. </para>
		/// </summary>
		/// <param name="min_">Argument of this Vector type, its register_type, or its value_type to clamp to a minimum of.</param>
		/// <param name="max_">Argument of this Vector type, its register_type, or its value_type to clamp to a maximum of.</param>
		/// <returns>Copy of this Vector with elements clamped between min_ and max_ as described.</returns>
		[[nodiscard]] constexpr inline this_type Clamp(const this_type& min_, const this_type& max_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_clamp(data, min_.data, max_.data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::clamp<per_element_width, is_signed>(data, max_.data));
			}
		}

		[[nodiscard]] constexpr inline this_type Clamp(const this_type& min_, register_arg_type max_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_clamp(data, min_.data, max_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::clamp<per_element_width, is_signed>(data, min_.data, max_));
			}
		}

		[[nodiscard]] constexpr inline this_type Clamp(register_arg_type min_, const this_type& max_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_clamp(data, min_, max_.data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::clamp<per_element_width, is_signed>(data, min_, max_.data));
			}
		}

		[[nodiscard]] constexpr inline this_type Clamp(register_arg_type min_, register_arg_type max_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_clamp(data, min_, max_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::clamp<per_element_width, is_signed>(data, min_, max_));
			}
		}

		[[nodiscard]] constexpr inline this_type Clamp(const this_type& min_, value_type max_for_all_) const
		{
			return Clamp(min_, EmuSIMD::set1<register_type, per_element_width>(max_for_all_));
		}

		[[nodiscard]] constexpr inline this_type Clamp(value_type min_for_all_, const this_type& max_) const
		{
			return Clamp(EmuSIMD::set1<register_type, per_element_width>(min_for_all_), max_);
		}

		[[nodiscard]] constexpr inline this_type Clamp(register_arg_type min_, value_type max_for_all_) const
		{
			return Clamp(min_, EmuSIMD::set1<register_type, per_element_width>(max_for_all_));
		}

		[[nodiscard]] constexpr inline this_type Clamp(value_type min_for_all_, register_arg_type max_) const
		{
			return Clamp(EmuSIMD::set1<register_type, per_element_width>(min_for_all_), max_);
		}

		[[nodiscard]] constexpr inline this_type Clamp(value_type min_for_all_, value_type max_for_all_) const
		{
			return Clamp(EmuSIMD::set1<register_type, per_element_width>(min_for_all_), EmuSIMD::set1<register_type, per_element_width>(max_for_all_));
		}
#pragma endregion

#pragma region NON_CONST_BASIC_ARITHMETIC
	public:
		/// <summary>
		/// <para> Adds the passed register to all registers encapsulated by this Vector, assigning the results to this Vector. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in add operations with all registers encapsulated by this Vector.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& AddAssign(register_arg_type rhs_for_all_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_add_assign(data, rhs_for_all_);
			}
			else
			{
				data = EmuSIMD::add<per_element_width>(data, rhs_for_all_);
			}
			return *this;
		}

		/// <summary>
		/// <para> Adds the passed scalar value to all elements within this Vector, assigning the results to this Vector. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to add to all elements within this Vector.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& AddAssign(value_type rhs_for_all_)
		{
			return AddAssign(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Adds this Vector and the passed rhs_ Vector of the same type, assigning the results to this Vector.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to add to this Vector.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& AddAssign(const this_type& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_add_assign(data, rhs_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::add<per_element_width>(data, rhs_.data);
			}
			return *this;
		}

		/// <summary>
		/// <para> Subtracts the passed register to all registers encapsulated by this Vector, assigning the results to this Vector. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in subtraction operations with all registers encapsulated by this Vector.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& SubtractAssign(register_arg_type rhs_for_all_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_subtract_assign(data, rhs_for_all_);
			}
			else
			{
				data = EmuSIMD::sub<per_element_width>(data, rhs_for_all_);
			}
			return *this;
		}

		/// <summary>
		/// <para> Subtracts the passed scalar value to all elements within this Vector, assigning the results to this Vector. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to subtract from all elements within this Vector.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& SubtractAssign(value_type rhs_for_all_)
		{
			return SubtractAssign(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Subtracts this Vector and the passed rhs_ Vector of the same type, assigning the results to this Vector.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to subtract from this Vector.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& SubtractAssign(const this_type& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_subtract_assign(data, rhs_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::sub<per_element_width>(data, rhs_.data);
			}
			return *this;
		}

		/// <summary>
		/// <para> Multiplies all registers encapsulated by this Vector by the passed register, assigning the results to this Vector. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in multiplication operations with all registers encapsulated by this Vector.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& MultiplyAssign(register_arg_type rhs_for_all_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_multiply_assign(data, rhs_for_all_);
			}
			else
			{
				data = EmuSIMD::mul_all<per_element_width>(data, rhs_for_all_);
			}
			return *this;
		}

		/// <summary>
		/// <para> Multiplies all elements within this Vector by the passed scalar value, assigning the results to this Vector. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to multiply all elements within this Vector by.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& MultiplyAssign(value_type rhs_for_all_)
		{
			return MultiplyAssign(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Multiplies this Vector by the passed rhs_ Vector of the same type, assigning the results to this Vector.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to multiply this Vector by.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& MultiplyAssign(const this_type& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_multiply_assign(data, rhs_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::mul_all<per_element_width>(data, rhs_.data);
			}
			return *this;
		}

		/// <summary>
		/// <para> Divides all registers encapsulated by this Vector by the passed register, assigning the results to this Vector. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in division operations with all registers encapsulated by this Vector.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& DivideAssign(register_arg_type rhs_for_all_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_divide_assign(data, rhs_for_all_);
			}
			else
			{
				data = EmuSIMD::div<per_element_width, is_signed>(data, rhs_for_all_);
			}
			return *this;
		}

		/// <summary>
		/// <para> Divides all elements within this Vector by the passed scalar value, assigning the results to this Vector. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to divide all elements within this Vector by.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& DivideAssign(value_type rhs_for_all_)
		{
			return DivideAssign(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Divides this Vector by the passed rhs_ Vector of the same type, assigning the results to this Vector.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to divide this Vector by.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& DivideAssign(const this_type& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_divide_assign(data, rhs_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::div<per_element_width, is_signed>(data, rhs_.data);
			}
			return *this;
		}

		/// <summary>
		/// <para> Divides all registers encapsulated by this Vector by the passed register, assigning the results to this Vector. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in division operations with all registers encapsulated by this Vector.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& ModAssign(register_arg_type rhs_for_all_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_mod_assign(data, rhs_for_all_);
			}
			else
			{
				data = EmuSIMD::mod<per_element_width, is_signed>(data, rhs_for_all_);
			}
			return *this;
		}

		/// <summary>
		/// <para> Divides all elements within this Vector by the passed scalar value, assigning the results to this Vector. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to divide all elements within this Vector by.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& ModAssign(value_type rhs_for_all_)
		{
			return ModAssign(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Divides this Vector by the passed rhs_ Vector of the same type, assigning the results to this Vector.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to divide this Vector by.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& ModAssign(const this_type& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_mod_assign(data, rhs_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::mod<per_element_width, is_signed>(data, rhs_.data);
			}
			return *this;
		}

		/// <summary>
		/// <para> Negates all elements within this Vector and assigns the results to this Vector. </para>
		/// </summary>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& NegateAssign()
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_negate_assign(data, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::negate<per_element_width>(data);
			}
			return *this;
		}
#pragma endregion

#pragma region CONST_BITWISE_ARITHMETIC
	public:
		/// <summary>
		/// <para> Bitwise ANDs all registers encapsulated by this Vector with the passed register. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in AND operations with all registers encapsulated by this Vector.</param>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type And(register_arg_type rhs_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_and(data, rhs_for_all_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::bitwise_and(data, rhs_for_all_));
			}
		}

		/// <summary>
		/// <para> Bitwise ANDs all elements within this Vector with the passed scalar value. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to use in AND operations with all elements within this Vector.</param>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type And(value_type rhs_for_all_) const
		{
			return And(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Bitwise ANDs this Vector with the passed rhs_ Vector of the same type.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to AND this Vector with.</param>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type And(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_and(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::bitwise_and(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Bitwise ORs all registers encapsulated by this Vector with the passed register. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in OR operations with all registers encapsulated by this Vector.</param>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type Or(register_arg_type rhs_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_or(data, rhs_for_all_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::bitwise_or(data, rhs_for_all_));
			}
		}

		/// <summary>
		/// <para> Bitwise ORs all elements within this Vector with the passed scalar value. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to use in OR operations with all elements within this Vector.</param>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type Or(value_type rhs_for_all_) const
		{
			return Or(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Bitwise ORs this Vector with the passed rhs_ Vector of the same type.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to OR this Vector with.</param>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type Or(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_or(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::bitwise_or(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Bitwise XORs all registers encapsulated by this Vector with the passed register. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in XOR operations with all registers encapsulated by this Vector.</param>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type Xor(register_arg_type rhs_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_xor(data, rhs_for_all_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::bitwise_xor(data, rhs_for_all_));
			}
		}

		/// <summary>
		/// <para> Bitwise XORs all elements within this Vector with the passed scalar value. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to use in XOR operations with all elements within this Vector.</param>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type Xor(value_type rhs_for_all_) const
		{
			return Xor(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Bitwise XORs this Vector with the passed rhs_ Vector of the same type.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to XOR this Vector with.</param>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type Xor(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_xor(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::bitwise_xor(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Bitwise ANDS the NOT of all registers encapsulated by this Vector with the passed register. </para>
		/// <para> The passed argument will be used as-is; only the NOT of this Vector is used. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in AND operations with the NOT of all registers encapsulated by this Vector.</param>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type AndNot(register_arg_type rhs_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_andnot(data, rhs_for_all_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::bitwise_andnot(data, rhs_for_all_));
			}
		}

		/// <summary>
		/// <para> Bitwise ANDS the NOT of all elements within this Vector with the passed scalar value. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// <para> The passed argument will be used as-is; only the NOT of this Vector is used. </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to use in AND operations with the NOT of all elements within this Vector.</param>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type AndNot(value_type rhs_for_all_) const
		{
			return AndNot(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Bitwise ANDS the NOT of this Vector with the passed rhs_ Vector of the same type.</para>
		/// <para> The passed argument will be used as-is; only the NOT of this Vector is used. </para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to AND the NOT this Vector with.</param>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type AndNot(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_andnot(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::bitwise_andnot(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Logically left-shifts all registers encapsulated by this Vector using the passed argument as the shifts for each register. </para>
		/// </summary>
		/// <param name="num_shifts_">SIMD register of this Vector's `shift_register_type` which indicates the number of shifts to execute.</param>
		/// <returns>New FastVector of this type resulting from the shift operation.</returns>
		[[nodiscard]] constexpr inline this_type ShiftLeft(shift_register_type num_shifts_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_shift_left(data, num_shifts_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::shift_left<per_element_width>(data, num_shifts_));
			}
		}

		/// <summary>
		/// <para> Logically left-shifts all elements within this Vector using the passed scalar value as the number of shifts for each element. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// <para> If num_shifts_ is a compile-time constant, it is recommended to use the form of this function which takes a NumShifts_ template argument instead. </para>
		/// </summary>
		/// <param name="num_shifts_">Scalar to shift all elements within this Vector by.</param>
		/// <returns>New FastVector of this type resulting from the shift operation.</returns>
		[[nodiscard]] constexpr inline this_type ShiftLeft(std::size_t num_shifts_) const
		{
			return ShiftLeft(EmuSIMD::set1<shift_register_type, shift_register_per_element_width>(num_shifts_));
		}

		/// <summary>
		/// <para> Logically left-shifts all elements within this Vector using the passed template scalar value as the number of shifts for each element. </para>
		/// </summary>
		/// <returns>New FastVector of this type resulting from the shift operation.</returns>
		template<std::size_t NumShifts_>
		constexpr inline this_type ShiftLeft() const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_shift_left<NumShifts_>(data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::shift_left<NumShifts_, per_element_width>(data));
			}
		}

		/// <summary>
		/// <para> Logically right-shifts all registers encapsulated by this Vector using the passed argument as the shifts for each register. </para>
		/// </summary>
		/// <param name="num_shifts_">SIMD register of this Vector's `shift_register_type` which indicates the number of shifts to execute.</param>
		/// <returns>New FastVector of this type resulting from the shift operation.</returns>
		[[nodiscard]] constexpr inline this_type ShiftRight(shift_register_type num_shifts_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_shift_right_logical(data, num_shifts_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::shift_right_logical<per_element_width>(data, num_shifts_));
			}
		}

		/// <summary>
		/// <para> Logically right-shifts all elements within this Vector using the passed scalar value as the number of shifts for each element. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// <para> If num_shifts_ is a compile-time constant, it is recommended to use the form of this function which takes a NumShifts_ template argument instead. </para>
		/// </summary>
		/// <param name="num_shifts_">Scalar to shift all elements within this Vector by.</param>
		/// <returns>New FastVector of this type resulting from the shift operation.</returns>
		[[nodiscard]] constexpr inline this_type ShiftRight(std::size_t num_shifts_) const
		{
			return ShiftRight(EmuSIMD::set1<shift_register_type, shift_register_per_element_width>(num_shifts_));
		}

		/// <summary>
		/// <para> Logically right-shifts all elements within this Vector using the passed template scalar value as the number of shifts for each element. </para>
		/// </summary>
		/// <returns>New FastVector of this type resulting from the shift operation.</returns>
		template<std::size_t NumShifts_>
		constexpr inline this_type ShiftRight() const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_shift_right_logical<NumShifts_>(data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::shift_right_logical<NumShifts_, per_element_width>(data));
			}
		}

		/// <summary>
		/// <para> Arithmetically right-shifts all registers encapsulated by this Vector using the passed argument as the shifts for each register. </para>
		/// <para> Arithmetic shifts differentiate from logical shifts in that they preserve the sign bit. </para>
		/// </summary>
		/// <param name="num_shifts_">SIMD register of this Vector's `shift_register_type` which indicates the number of shifts to execute.</param>
		/// <returns>New FastVector of this type resulting from the shift operation.</returns>
		[[nodiscard]] constexpr inline this_type ShiftRightArithmetic(shift_register_type num_shifts_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_shift_right_arithmetic(data, num_shifts_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::shift_right_arithmetic<per_element_width>(data, num_shifts_));
			}
		}

		/// <summary>
		/// <para> Arithmetically right-shifts all elements within this Vector using the passed scalar value as the number of shifts for each element. </para>
		/// <para> Arithmetic shifts differentiate from logical shifts in that they preserve the sign bit. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// <para> If num_shifts_ is a compile-time constant, it is recommended to use the form of this function which takes a NumShifts_ template argument instead. </para>
		/// </summary>
		/// <param name="num_shifts_">Scalar to shift all elements within this Vector by.</param>
		/// <returns>New FastVector of this type resulting from the shift operation.</returns>
		[[nodiscard]] constexpr inline this_type ShiftRightArithmetic(std::size_t num_shifts_) const
		{
			return ShiftRightArithmetic(EmuSIMD::set1<shift_register_type, shift_register_per_element_width>(num_shifts_));
		}

		/// <summary>
		/// <para> Arithmetically right-shifts all elements within this Vector using the passed template scalar value as the number of shifts for each element. </para>
		/// <para> Arithmetic shifts differentiate from logical shifts in that they preserve the sign bit. </para>
		/// </summary>
		/// <returns>New FastVector of this type resulting from the shift operation.</returns>
		template<std::size_t NumShifts_>
		constexpr inline this_type ShiftRightArithmetic() const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_shift_right_arithmetic<NumShifts_>(data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::shift_right_arithmetic<NumShifts_, per_element_width>(data));
			}
		}

		/// <summary>
		/// <para>Creates the NOT form of this Vector, with 0-bits flipped to 1 and 1-bits flipped to 0.</para>
		/// </summary>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type Not() const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_not(data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::bitwise_not(data));
			}
		}
#pragma endregion

#pragma region NON_CONST_BITWISE_ARITHMETIC
	public:
		/// <summary>
		/// <para> Bitwise ANDs all registers encapsulated by this Vector with the passed register, and assigns results to this Vector. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in AND operations with all registers encapsulated by this Vector.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& AndAssign(register_arg_type rhs_for_all_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_and_assign(data, rhs_for_all_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::bitwise_and(data, rhs_for_all_);
			}
			return *this;
		}

		/// <summary>
		/// <para> Bitwise ANDs all elements within this Vector with the passed scalar value, and assigns results to this Vector. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to use in AND operations with all elements within this Vector, assigning the results to this Vector.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& AndAssign(value_type rhs_for_all_)
		{
			return AndAssign(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Bitwise ANDs this Vector with the passed rhs_ Vector of the same type, and assigns results to this Vector.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to AND this Vector with.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& AndAssign(const this_type& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_and_assign(data, rhs_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::bitwise_and(data, rhs_.data);
			}
			return *this;
		}

		/// <summary>
		/// <para> Bitwise ORs all registers encapsulated by this Vector with the passed register, and assigns results to this Vector. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in OR operations with all registers encapsulated by this Vector.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& OrAssign(register_arg_type rhs_for_all_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_or_assign(data, rhs_for_all_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::bitwise_or(data, rhs_for_all_);
			}
			return *this;
		}

		/// <summary>
		/// <para> Bitwise ORs all elements within this Vector with the passed scalar value, and assigns results to this Vector. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to use in OR operations with all elements within this Vector, assigning the results to this Vector.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& OrAssign(value_type rhs_for_all_)
		{
			return OrAssign(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Bitwise ORs this Vector with the passed rhs_ Vector of the same type, and assigns results to this Vector.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to OR this Vector with.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& OrAssign(const this_type& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_or_assign(data, rhs_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::bitwise_or(data, rhs_.data);
			}
			return *this;
		}

		/// <summary>
		/// <para> Bitwise XORs all registers encapsulated by this Vector with the passed register, and assigns results to this Vector. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in XOR operations with all registers encapsulated by this Vector.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& XorAssign(register_arg_type rhs_for_all_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_xor_assign(data, rhs_for_all_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::bitwise_xor(data, rhs_for_all_);
			}
			return *this;
		}

		/// <summary>
		/// <para> Bitwise XORs all elements within this Vector with the passed scalar value, and assigns results to this Vector. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to use in XOR operations with all elements within this Vector, assigning the results to this Vector.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& XorAssign(value_type rhs_for_all_)
		{
			return XorAssign(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Bitwise XORs this Vector with the passed rhs_ Vector of the same type, and assigns results to this Vector.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to XOR this Vector with.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& XorAssign(const this_type& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_xor_assign(data, rhs_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::bitwise_xor(data, rhs_.data);
			}
			return *this;
		}

		/// <summary>
		/// <para> Bitwise ANDS the NOT of all registers encapsulated by this Vector with the passed register, and assigns results to this Vector. </para>
		/// <para> The passed argument will be used as-is; only the NOT of this Vector is used. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in AND operations with the NOT of all registers encapsulated by this Vector.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& AndNotAssign(register_arg_type rhs_for_all_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_andnot_assign(data, rhs_for_all_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::bitwise_andnot(data, rhs_for_all_);
			}
			return *this;
		}

		/// <summary>
		/// <para> Bitwise ANDS the NOT of all elements within this Vector with the passed scalar value, and assigns results to this Vector. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// <para> The passed argument will be used as-is; only the NOT of this Vector is used. </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to use in AND operations with the NOT of all elements within this Vector.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& AndNotAssign(value_type rhs_for_all_)
		{
			return AndNotAssign(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para> Bitwise ANDS the NOT of this Vector with the passed rhs_ Vector of the same type, and assigns results to this Vector. </para>
		/// <para> The passed argument will be used as-is; only the NOT of this Vector is used. </para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to AND the NOT this Vector with.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& AndNotAssign(const this_type& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_andnot_assign(data, rhs_.data, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::bitwise_andnot(data, rhs_.data);
			}
			return *this;
		}

		/// <summary>
		/// <para>
		///		Logically left-shifts all registers encapsulated by this Vector using the passed argument as the shifts for each register, 
		///		and assigns results to this Vector.
		/// </para>
		/// </summary>
		/// <param name="num_shifts_">SIMD register of this Vector's `shift_register_type` which indicates the number of shifts to execute.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& ShiftLeftAssign(shift_register_type num_shifts_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_shift_left_assign(data, num_shifts_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::shift_left<per_element_width>(data, num_shifts_);
			}
			return *this;
		}

		/// <summary>
		/// <para>
		///		Logically left-shifts all elements within this Vector using the passed scalar value as the number of shifts for each element, 
		///		and assigns results to this Vector.
		/// </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// <para> If num_shifts_ is a compile-time constant, it is recommended to use the form of this function which takes a NumShifts_ template argument instead. </para>
		/// </summary>
		/// <param name="num_shifts_">Scalar to shift all elements within this Vector by.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& ShiftLeftAssign(std::size_t num_shifts_)
		{
			return ShiftLeftAssign(EmuSIMD::set1<shift_register_type, shift_register_per_element_width>(num_shifts_));
		}

		/// <summary>
		/// <para>
		///		Logically left-shifts all elements within this Vector using the passed template scalar value as the number of shifts for each element, 
		///		and assigns results to this Vector.
		/// </para>
		/// </summary>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		template<std::size_t NumShifts_>
		constexpr inline this_type& ShiftLeftAssign()
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_shift_left_assign<NumShifts_>(data, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::shift_left<NumShifts_, per_element_width>(data);
			}
			return *this;
		}

		/// <summary>
		/// <para>
		///		Logically left-shifts all registers encapsulated by this Vector using the passed argument as the shifts for each register, 
		///		and assigns results to this Vector.
		/// </para>
		/// </summary>
		/// <param name="num_shifts_">SIMD register of this Vector's `shift_register_type` which indicates the number of shifts to execute.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& ShiftRightAssign(shift_register_type num_shifts_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_shift_right_logical_assign(data, num_shifts_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::shift_right_logical<per_element_width>(data, num_shifts_);
			}
			return *this;
		}

		/// <summary>
		/// <para>
		///		Logically left-shifts all elements within this Vector using the passed scalar value as the number of shifts for each element, 
		///		and assigns results to this Vector.
		/// </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// <para> If num_shifts_ is a compile-time constant, it is recommended to use the form of this function which takes a NumShifts_ template argument instead. </para>
		/// </summary>
		/// <param name="num_shifts_">Scalar to shift all elements within this Vector by.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& ShiftRightAssign(std::size_t num_shifts_)
		{
			return ShiftRightAssign(EmuSIMD::set1<shift_register_type, shift_register_per_element_width>(num_shifts_));
		}

		/// <summary>
		/// <para>
		///		Logically left-shifts all elements within this Vector using the passed template scalar value as the number of shifts for each element, 
		///		and assigns results to this Vector.
		/// </para>
		/// </summary>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		template<std::size_t NumShifts_>
		constexpr inline this_type& ShiftRightAssign()
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_shift_right_logical_assign<NumShifts_>(data, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::shift_right_logical<NumShifts_, per_element_width>(data);
			}
			return *this;
		}

		/// <summary>
		/// <para>
		///		Arithmetically left-shifts all registers encapsulated by this Vector using the passed argument as the shifts for each register, 
		///		and assigns results to this Vector.
		/// </para>
		/// <para> Arithmetic shifts differentiate from logical shifts in that they preserve the sign bit. </para>
		/// </summary>
		/// <param name="num_shifts_">SIMD register of this Vector's `shift_register_type` which indicates the number of shifts to execute.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& ShiftRightArithmeticAssign(shift_register_type num_shifts_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_shift_right_arithmetic_assign(data, num_shifts_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::shift_right_arithmetic<per_element_width>(data, num_shifts_);
			}
			return *this;
		}

		/// <summary>
		/// <para>
		///		Arithmetically left-shifts all elements within this Vector using the passed scalar value as the number of shifts for each element, 
		///		and assigns results to this Vector.
		/// </para>
		/// <para> Arithmetic shifts differentiate from logical shifts in that they preserve the sign bit. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// <para> If num_shifts_ is a compile-time constant, it is recommended to use the form of this function which takes a NumShifts_ template argument instead. </para>
		/// </summary>
		/// <param name="num_shifts_">Scalar to shift all elements within this Vector by.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& ShiftRightArithmeticAssign(std::size_t num_shifts_)
		{
			return ShiftRightArithmeticAssign(EmuSIMD::set1<shift_register_type, shift_register_per_element_width>(num_shifts_));
		}

		/// <summary>
		/// <para>
		///		Arithmetically left-shifts all elements within this Vector using the passed template scalar value as the number of shifts for each element, 
		///		and assigns results to this Vector.
		/// </para>
		/// <para> Arithmetic shifts differentiate from logical shifts in that they preserve the sign bit. </para>
		/// </summary>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		template<std::size_t NumShifts_>
		constexpr inline this_type& ShiftRightArithmeticAssign()
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_shift_right_arithmetic_assign<NumShifts_>(data, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::shift_right_arithmetic<NumShifts_, per_element_width>(data);
			}
			return *this;
		}

		/// <summary>
		/// <para>Creates the NOT form of this Vector, with 0-bits flipped to 1 and 1-bits flipped to 0., and assigns the results to this Vector.</para>
		/// </summary>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& NotAssign()
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_not_assign(data, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::bitwise_not(data);
			}
			return *this;
		}
#pragma endregion

#pragma region CONST_BASIC_ARITHMETIC_OPERATORS
	public:
		/// <summary>
		/// <para> Adds the passed register to all registers encapsulated by this Vector. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in add operations with all registers encapsulated by this Vector.</param>
		/// <returns>New FastVector of this type resulting from the addition operation.</returns>
		[[nodiscard]] constexpr inline this_type operator+(register_arg_type rhs_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_add(data, rhs_for_all_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::add<per_element_width>(data, rhs_for_all_));
			}
		}

		/// <summary>
		/// <para> Adds the passed scalar value to all elements within this Vector. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to add to all elements within this Vector.</param>
		/// <returns>New FastVector of this type resulting from the addition operation.</returns>
		[[nodiscard]] constexpr inline this_type operator+(value_type rhs_for_all_) const
		{
			return operator+(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Adds this Vector and the passed rhs_ Vector of the same type.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to add to this Vector.</param>
		/// <returns>New FastVector of this type resulting from the addition operation.</returns>
		[[nodiscard]] constexpr inline this_type operator+(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_add(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::add<per_element_width>(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Subtracts the passed register from all registers encapsulated by this Vector. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in subtract operations with all registers encapsulated by this Vector.</param>
		/// <returns>New FastVector of this type resulting from the subtraction operation.</returns>
		[[nodiscard]] constexpr inline this_type operator-(register_arg_type rhs_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_subtract(data, rhs_for_all_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::sub<per_element_width>(data, rhs_for_all_));
			}
		}

		/// <summary>
		/// <para> Subtracts the passed scalar value to all elements within this Vector. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to subtract from all elements within this Vector.</param>
		/// <returns>New FastVector of this type resulting from the subtraction operation.</returns>
		[[nodiscard]] constexpr inline this_type operator-(value_type rhs_for_all_) const
		{
			return operator-(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Subtracts this Vector and the passed rhs_ Vector of the same type.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to subtract from this Vector.</param>
		/// <returns>New FastVector of this type resulting from the subtraction operation.</returns>
		[[nodiscard]] constexpr inline this_type operator-(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_subtract(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::sub<per_element_width>(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Multiplies all registers encapsulated by this Vector by the passed register. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in multiplication operations with all registers encapsulated by this Vector.</param>
		/// <returns>New FastVector of this type resulting from the multiplication operation.</returns>
		[[nodiscard]] constexpr inline this_type operator*(register_arg_type rhs_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_multiply(data, rhs_for_all_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::mul_all<per_element_width>(data, rhs_for_all_));
			}
		}

		/// <summary>
		/// <para> Multiplies all elements within this Vector by the passed scalar value. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to multiply all elements within this Vector by.</param>
		/// <returns>New FastVector of this type resulting from the multiplication operation.</returns>
		[[nodiscard]] constexpr inline this_type operator*(value_type rhs_for_all_) const
		{
			return operator*(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Multiplies this Vector and the passed rhs_ Vector of the same type.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to multiply this Vector by.</param>
		/// <returns>New FastVector of this type resulting from the multiplication operation.</returns>
		[[nodiscard]] constexpr inline this_type operator*(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_multiply(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::mul_all<per_element_width>(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Divides all registers encapsulated by this Vector by the passed register. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in division operations with all registers encapsulated by this Vector.</param>
		/// <returns>New FastVector of this type resulting from the division operation.</returns>
		[[nodiscard]] constexpr inline this_type operator/(register_arg_type rhs_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_divide(data, rhs_for_all_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::div<per_element_width, is_signed>(data, rhs_for_all_));
			}
		}

		/// <summary>
		/// <para> Divides all elements within this Vector by the passed scalar value. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to divide all elements within this Vector by.</param>
		/// <returns>New FastVector of this type resulting from the division operation.</returns>
		[[nodiscard]] constexpr inline this_type operator/(value_type rhs_for_all_) const
		{
			return operator/(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Divides this Vector and the passed rhs_ Vector of the same type.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to divide this Vector by.</param>
		/// <returns>New FastVector of this type resulting from the division operation.</returns>
		[[nodiscard]] constexpr inline this_type operator/(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_divide(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::div<per_element_width, is_signed>(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Modulo-divides all registers encapsulated by this Vector by the passed register. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in modulo-division operations with all registers encapsulated by this Vector.</param>
		/// <returns>New FastVector of this type resulting from the modulo-division operation.</returns>
		[[nodiscard]] constexpr inline this_type operator%(register_arg_type rhs_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_mod(data, rhs_for_all_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::mod<per_element_width, is_signed>(data, rhs_for_all_));
			}
		}

		/// <summary>
		/// <para> Modulo-divides all elements within this Vector by the passed scalar value. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to modulo-divide all elements within this Vector by.</param>
		/// <returns>New FastVector of this type resulting from the modulo-division operation.</returns>
		[[nodiscard]] constexpr inline this_type operator%(value_type rhs_for_all_) const
		{
			return operator%(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Modulo-divides this Vector and the passed rhs_ Vector of the same type.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to modulo-divide this Vector by.</param>
		/// <returns>New FastVector of this type resulting from the modulo-division operation.</returns>
		[[nodiscard]] constexpr inline this_type operator%(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_divide(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::mod<per_element_width, is_signed>(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Creates a negated form of this Vector, where each element will be set to -element.</para>
		/// </summary>
		/// <returns>New FastVector of this type resulting from the negation.</returns>
		[[nodiscard]] constexpr inline this_type operator-() const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_negate(data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::negate<per_element_width>(data));
			}
		}
#pragma endregion

#pragma region NON_CONST_BASIC_ARITHMETIC_OPERATORS
	public:
		/// <summary>
		/// <para> Adds the passed register to all registers encapsulated by this Vector, assigning the results to this Vector. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in add operations with all registers encapsulated by this Vector.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& operator+=(register_arg_type rhs_for_all_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_add_assign(data, rhs_for_all_);
			}
			else
			{
				data = EmuSIMD::add<per_element_width>(data, rhs_for_all_);
			}
			return *this;
		}

		/// <summary>
		/// <para> Adds the passed scalar value to all elements within this Vector, assigning the results to this Vector. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to add to all elements within this Vector.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& operator+=(value_type rhs_for_all_)
		{
			return operator+=(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Adds this Vector and the passed rhs_ Vector of the same type, assigning the results to this Vector.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to add to this Vector.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& operator+=(const this_type& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_add_assign(data, rhs_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::add<per_element_width>(data, rhs_.data);
			}
			return *this;
		}

		/// <summary>
		/// <para> Subtracts the passed register to all registers encapsulated by this Vector, assigning the results to this Vector. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in subtraction operations with all registers encapsulated by this Vector.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& operator-=(register_arg_type rhs_for_all_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_subtract_assign(data, rhs_for_all_);
			}
			else
			{
				data = EmuSIMD::sub<per_element_width>(data, rhs_for_all_);
			}
			return *this;
		}

		/// <summary>
		/// <para> Subtracts the passed scalar value to all elements within this Vector, assigning the results to this Vector. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to subtract from all elements within this Vector.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& operator-=(value_type rhs_for_all_)
		{
			return operator-=(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Subtracts this Vector and the passed rhs_ Vector of the same type, assigning the results to this Vector.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to subtract from this Vector.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& operator-=(const this_type& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_subtract_assign(data, rhs_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::sub<per_element_width>(data, rhs_.data);
			}
			return *this;
		}

		/// <summary>
		/// <para> Multiplies all registers encapsulated by this Vector by the passed register, assigning the results to this Vector. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in multiplication operations with all registers encapsulated by this Vector.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& operator*=(register_arg_type rhs_for_all_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_multiply_assign(data, rhs_for_all_);
			}
			else
			{
				data = EmuSIMD::mul_all<per_element_width>(data, rhs_for_all_);
			}
			return *this;
		}

		/// <summary>
		/// <para> Multiplies all elements within this Vector by the passed scalar value, assigning the results to this Vector. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to multiply all elements within this Vector by.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& operator*=(value_type rhs_for_all_)
		{
			return operator*=(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Multiplies this Vector by the passed rhs_ Vector of the same type, assigning the results to this Vector.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to multiply this Vector by.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& operator*=(const this_type& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_multiply_assign(data, rhs_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::mul_all<per_element_width>(data, rhs_.data);
			}
			return *this;
		}

		/// <summary>
		/// <para> Divides all registers encapsulated by this Vector by the passed register, assigning the results to this Vector. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in division operations with all registers encapsulated by this Vector.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& operator/=(register_arg_type rhs_for_all_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_divide_assign(data, rhs_for_all_);
			}
			else
			{
				data = EmuSIMD::div<per_element_width, is_signed>(data, rhs_for_all_);
			}
			return *this;
		}

		/// <summary>
		/// <para> Divides all elements within this Vector by the passed scalar value, assigning the results to this Vector. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to divide all elements within this Vector by.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& operator/=(value_type rhs_for_all_)
		{
			return operator/=(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Divides this Vector by the passed rhs_ Vector of the same type, assigning the results to this Vector.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to divide this Vector by.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& operator/=(const this_type& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_divide_assign(data, rhs_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::div<per_element_width, is_signed>(data, rhs_.data);
			}
			return *this;
		}

		/// <summary>
		/// <para> Divides all registers encapsulated by this Vector by the passed register, assigning the results to this Vector. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in division operations with all registers encapsulated by this Vector.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& operator%=(register_arg_type rhs_for_all_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_mod_assign(data, rhs_for_all_);
			}
			else
			{
				data = EmuSIMD::mod<per_element_width, is_signed>(data, rhs_for_all_);
			}
			return *this;
		}

		/// <summary>
		/// <para> Divides all elements within this Vector by the passed scalar value, assigning the results to this Vector. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to divide all elements within this Vector by.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& operator%=(value_type rhs_for_all_)
		{
			return operator%=(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Divides this Vector by the passed rhs_ Vector of the same type, assigning the results to this Vector.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to divide this Vector by.</param>
		/// <returns>Reference to this Vector after the results are assigned.</returns>
		constexpr inline this_type& operator%=(const this_type& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_mod_assign(data, rhs_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::mod<per_element_width, is_signed>(data, rhs_.data);
			}
			return *this;
		}
#pragma endregion

#pragma region CONST_BITWISE_ARITHMETIC_OPERATORS
	public:
		/// <summary>
		/// <para> Bitwise ANDs all registers encapsulated by this Vector with the passed register. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in AND operations with all registers encapsulated by this Vector.</param>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type operator&(register_arg_type rhs_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_and(data, rhs_for_all_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::bitwise_and(data, rhs_for_all_));
			}
		}

		/// <summary>
		/// <para> Bitwise ANDs all elements within this Vector with the passed scalar value. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to use in AND operations with all elements within this Vector.</param>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type operator&(value_type rhs_for_all_) const
		{
			return operator&(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Bitwise ANDs this Vector with the passed rhs_ Vector of the same type.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to AND this Vector with.</param>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type operator&(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_and(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::bitwise_and(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Bitwise ORs all registers encapsulated by this Vector with the passed register. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in OR operations with all registers encapsulated by this Vector.</param>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type operator|(register_arg_type rhs_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_or(data, rhs_for_all_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::bitwise_or(data, rhs_for_all_));
			}
		}

		/// <summary>
		/// <para> Bitwise ORs all elements within this Vector with the passed scalar value. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to use in OR operations with all elements within this Vector.</param>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type operator|(value_type rhs_for_all_) const
		{
			return operator|(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Bitwise ORs this Vector with the passed rhs_ Vector of the same type.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to OR this Vector with.</param>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type operator|(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_or(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::bitwise_or(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Bitwise XORs all registers encapsulated by this Vector with the passed register. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in XOR operations with all registers encapsulated by this Vector.</param>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type operator^(register_arg_type rhs_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_xor(data, rhs_for_all_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::bitwise_xor(data, rhs_for_all_));
			}
		}

		/// <summary>
		/// <para> Bitwise XORs all elements within this Vector with the passed scalar value. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to use in XOR operations with all elements within this Vector.</param>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type operator^(value_type rhs_for_all_) const
		{
			return operator^(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Bitwise XORs this Vector with the passed rhs_ Vector of the same type.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to XOR this Vector with.</param>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type operator^(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_xor(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::bitwise_xor(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Logically left-shifts all registers encapsulated by this Vector using the passed argument as the shifts for each register. </para>
		/// </summary>
		/// <param name="num_shifts_">SIMD register of this Vector's `shift_register_type` which indicates the number of shifts to execute.</param>
		/// <returns>New FastVector of this type resulting from the shift operation.</returns>
		[[nodiscard]] constexpr inline this_type operator<<(shift_register_type num_shifts_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_shift_left(data, num_shifts_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::shift_left<per_element_width>(data, num_shifts_));
			}
		}

		/// <summary>
		/// <para> Logically left-shifts all elements within this Vector using the passed scalar value as the number of shifts for each element. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// <para> If num_shifts_ is a compile-time constant, it is recommended to use the ShiftLeft function which takes a NumShifts_ template argument instead. </para>
		/// </summary>
		/// <param name="num_shifts_">Scalar to shift all elements within this Vector by.</param>
		/// <returns>New FastVector of this type resulting from the shift operation.</returns>
		[[nodiscard]] constexpr inline this_type operator<<(std::size_t num_shifts_) const
		{
			return operator<<(EmuSIMD::set1<shift_register_type, shift_register_per_element_width>(num_shifts_));
		}

		/// <summary>
		/// <para> Logically right-shifts all registers encapsulated by this Vector using the passed argument as the shifts for each register. </para>
		/// </summary>
		/// <param name="num_shifts_">SIMD register of this Vector's `shift_register_type` which indicates the number of shifts to execute.</param>
		/// <returns>New FastVector of this type resulting from the shift operation.</returns>
		[[nodiscard]] constexpr inline this_type operator>>(shift_register_type num_shifts_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_shift_right_logical(data, num_shifts_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::shift_right_logical<per_element_width>(data, num_shifts_));
			}
		}

		/// <summary>
		/// <para> Logically right-shifts all elements within this Vector using the passed scalar value as the number of shifts for each element. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// <para> If num_shifts_ is a compile-time constant, it is recommended to use ShiftRight function which takes a NumShifts_ template argument instead. </para>
		/// </summary>
		/// <param name="num_shifts_">Scalar to shift all elements within this Vector by.</param>
		/// <returns>New FastVector of this type resulting from the shift operation.</returns>
		[[nodiscard]] constexpr inline this_type operator>>(std::size_t num_shifts_) const
		{
			return operator>>(EmuSIMD::set1<shift_register_type, shift_register_per_element_width>(num_shifts_));
		}

		/// <summary>
		/// <para>Creates the NOT form of this Vector, with 0-bits flipped to 1 and 1-bits flipped to 0.</para>
		/// </summary>
		/// <returns>New FastVector of this type resulting from the bitwise operation.</returns>
		[[nodiscard]] constexpr inline this_type operator~() const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_not(data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::bitwise_not(data));
			}
		}
#pragma endregion

#pragma region NON_CONST_BITWISE_ARITHMETIC_OPERATORS
	public:
		/// <summary>
		/// <para> Bitwise ANDs all registers encapsulated by this Vector with the passed register, and assigns results to this Vector. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in AND operations with all registers encapsulated by this Vector.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& operator&=(register_arg_type rhs_for_all_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_and_assign(data, rhs_for_all_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::bitwise_and(data, rhs_for_all_);
			}
			return *this;
		}

		/// <summary>
		/// <para> Bitwise ANDs all elements within this Vector with the passed scalar value, and assigns results to this Vector. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to use in AND operations with all elements within this Vector, assigning the results to this Vector.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& operator&=(value_type rhs_for_all_)
		{
			return operator&=(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Bitwise ANDs this Vector with the passed rhs_ Vector of the same type, and assigns results to this Vector.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to AND this Vector with.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& operator&=(const this_type& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_and_assign(data, rhs_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::bitwise_and(data, rhs_.data);
			}
			return *this;
		}

		/// <summary>
		/// <para> Bitwise ORs all registers encapsulated by this Vector with the passed register, and assigns results to this Vector. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in OR operations with all registers encapsulated by this Vector.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& operator|=(register_arg_type rhs_for_all_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_or_assign(data, rhs_for_all_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::bitwise_or(data, rhs_for_all_);
			}
			return *this;
		}

		/// <summary>
		/// <para> Bitwise ORs all elements within this Vector with the passed scalar value, and assigns results to this Vector. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to use in OR operations with all elements within this Vector, assigning the results to this Vector.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& operator|=(value_type rhs_for_all_)
		{
			return operator|=(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Bitwise ORs this Vector with the passed rhs_ Vector of the same type, and assigns results to this Vector.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to OR this Vector with.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& operator|=(const this_type& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_or_assign(data, rhs_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::bitwise_or(data, rhs_.data);
			}
			return *this;
		}

		/// <summary>
		/// <para> Bitwise XORs all registers encapsulated by this Vector with the passed register, and assigns results to this Vector. </para>
		/// </summary>
		/// <param name="rhs_for_all_">SIMD register to use in XOR operations with all registers encapsulated by this Vector.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& operator^=(register_arg_type rhs_for_all_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_xor_assign(data, rhs_for_all_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::bitwise_xor(data, rhs_for_all_);
			}
			return *this;
		}

		/// <summary>
		/// <para> Bitwise XORs all elements within this Vector with the passed scalar value, and assigns results to this Vector. </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// </summary>
		/// <param name="rhs_for_all_">Scalar to use in XOR operations with all elements within this Vector, assigning the results to this Vector.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& operator^=(value_type rhs_for_all_)
		{
			return operator^=(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para>Bitwise XORs this Vector with the passed rhs_ Vector of the same type, and assigns results to this Vector.</para>
		/// </summary>
		/// <param name="rhs_">Vector of the same type to XOR this Vector with.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& operator^=(const this_type& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_xor_assign(data, rhs_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::bitwise_xor(data, rhs_.data);
			}
			return *this;
		}

		/// <summary>
		/// <para>
		///		Logically left-shifts all registers encapsulated by this Vector using the passed argument as the shifts for each register, 
		///		and assigns results to this Vector.
		/// </para>
		/// </summary>
		/// <param name="num_shifts_">SIMD register of this Vector's `shift_register_type` which indicates the number of shifts to execute.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& operator<<=(shift_register_type num_shifts_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_shift_left_assign(data, num_shifts_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::shift_left<per_element_width>(data, num_shifts_);
			}
			return *this;
		}

		/// <summary>
		/// <para>
		///		Logically left-shifts all elements within this Vector using the passed scalar value as the number of shifts for each element, 
		///		and assigns results to this Vector.
		/// </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// <para> If num_shifts_ is a compile-time constant, it is recommended to use the ShiftLeftAssign function which takes a NumShifts_ template argument instead. </para>
		/// </summary>
		/// <param name="num_shifts_">Scalar to shift all elements within this Vector by.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& operator<<=(std::size_t num_shifts_)
		{
			return operator<<=(EmuSIMD::set1<shift_register_type, shift_register_per_element_width>(num_shifts_));
		}

		/// <summary>
		/// <para>
		///		Logically left-shifts all registers encapsulated by this Vector using the passed argument as the shifts for each register, 
		///		and assigns results to this Vector.
		/// </para>
		/// </summary>
		/// <param name="num_shifts_">SIMD register of this Vector's `shift_register_type` which indicates the number of shifts to execute.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& operator>>=(shift_register_type num_shifts_)
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_shift_right_logical_assign(data, num_shifts_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::shift_right_logical<per_element_width>(data, num_shifts_);
			}
			return *this;
		}

		/// <summary>
		/// <para>
		///		Logically left-shifts all elements within this Vector using the passed scalar value as the number of shifts for each element, 
		///		and assigns results to this Vector.
		/// </para>
		/// <para> 
		///		This will create an intermediate for SIMD register interactions; 
		///		it is recommended if the scalar is known to be reused in this context to instead create the intermediate register yourself via this Vector's 
		///		make_all_same_register function.
		/// </para>
		/// <para> If num_shifts_ is a compile-time constant, it is recommended to use the ShiftRightAssign function which takes a NumShifts_ template argument instead. </para>
		/// </summary>
		/// <param name="num_shifts_">Scalar to shift all elements within this Vector by.</param>
		/// <returns>Reference to this Vector after results have been assigned.</returns>
		[[nodiscard]] constexpr inline this_type& operator>>=(std::size_t num_shifts_)
		{
			return operator>>=(EmuSIMD::set1<shift_register_type, shift_register_per_element_width>(num_shifts_));
		}
#pragma endregion

#pragma region COMPARISON_OPERATORS
	public:
		/// <summary>
		/// <para> Adaptive equality check. </para>
		/// <para> If the passed argument is of this FastVector type or its register_arg_type: Identical to CmpAllEqual. </para>
		/// <para> If the passed argument is of this FastVector's value_type: Identical to MagnitudeScalar() == arg. </para>
		/// </summary>
		[[nodiscard]] constexpr inline bool operator==(const this_type& rhs_) const
		{
			return _do_cmp_equal_bool_out<true>(data, rhs_.data);
		}

		[[nodiscard]] constexpr inline bool operator==(register_arg_type rhs_) const
		{
			return _do_cmp_equal_bool_out<true>(data, rhs_);
		}

		[[nodiscard]] constexpr inline bool operator==(value_type rhs_magnitude_) const
		{
			return MagnitudeScalar<value_type>() == rhs_magnitude_;
		}

		/// <summary>
		/// <para> Adaptive inequality check. </para>
		/// <para> If the passed argument is of this FastVector type or its register_arg_type: Identical to CmpAnyNotEqual. </para>
		/// <para> If the passed argument is of this FastVector's value_type: Identical to MagnitudeScalar() != arg. </para>
		/// </summary>
		[[nodiscard]] constexpr inline bool operator!=(const this_type& rhs_) const
		{
			return _do_cmp_not_equal_bool_out<false>(data, rhs_.data);
		}

		[[nodiscard]] constexpr inline bool operator!=(register_arg_type rhs_) const
		{
			return _do_cmp_not_equal_bool_out<false>(data, rhs_);
		}

		[[nodiscard]] constexpr inline bool operator!=(value_type rhs_magnitude_) const
		{
			return MagnitudeScalar<value_type>() != rhs_magnitude_;
		}

		/// <summary>
		/// <para> Adaptive greater-than magnitude comparison. </para>
		/// <para> If the passed argument is of this FastVector type: Identical to MagnitudeScalar() &gt; arg.MagnitudeScalar(). </para>
		/// <para> If the passed argument is of this FastVector type: Identical to MagnitudeScalar() &gt; arg. </para>
		/// </summary>
		[[nodiscard]] constexpr inline bool operator>(const this_type& rhs_) const
		{
			return MagnitudeScalar<value_type>() > rhs_.MagnitudeScalar<value_type>();
		}

		[[nodiscard]] constexpr inline bool operator>(value_type rhs_magnitude_) const
		{
			return MagnitudeScalar<value_type>() > rhs_magnitude_;
		}

		/// <summary>
		/// <para> Adaptive less-than magnitude comparison. </para>
		/// <para> If the passed argument is of this FastVector type: Identical to MagnitudeScalar() &lt; arg.MagnitudeScalar(). </para>
		/// <para> If the passed argument is of this FastVector type: Identical to MagnitudeScalar() &lt; arg. </para>
		/// </summary>
		[[nodiscard]] constexpr inline bool operator<(const this_type& rhs_) const
		{
			return MagnitudeScalar<value_type>() < rhs_.MagnitudeScalar<value_type>();
		}

		[[nodiscard]] constexpr inline bool operator<(value_type rhs_magnitude_) const
		{
			return MagnitudeScalar<value_type>() < rhs_magnitude_;
		}

		/// <summary>
		/// <para> Adaptive greater-equal magnitude comparison. </para>
		/// <para> If the passed argument is of this FastVector type: Identical to MagnitudeScalar() &gt;= arg.MagnitudeScalar(). </para>
		/// <para> If the passed argument is of this FastVector type: Identical to MagnitudeScalar() &gt;= arg. </para>
		/// </summary>
		[[nodiscard]] constexpr inline bool operator>=(const this_type& rhs_) const
		{
			return MagnitudeScalar<value_type>() >= rhs_.MagnitudeScalar<value_type>();
		}

		[[nodiscard]] constexpr inline bool operator>=(value_type rhs_magnitude_) const
		{
			return MagnitudeScalar<value_type>() >= rhs_magnitude_;
		}

		/// <summary>
		/// <para> Adaptive less-equal magnitude comparison. </para>
		/// <para> If the passed argument is of this FastVector type: Identical to MagnitudeScalar() &lt;= arg.MagnitudeScalar(). </para>
		/// <para> If the passed argument is of this FastVector type: Identical to MagnitudeScalar() &lt;= arg. </para>
		/// </summary>
		[[nodiscard]] constexpr inline bool operator<=(const this_type& rhs_) const
		{
			return MagnitudeScalar<value_type>() <= rhs_.MagnitudeScalar<value_type>();
		}

		[[nodiscard]] constexpr inline bool operator<=(value_type rhs_magnitude_) const
		{
			return MagnitudeScalar<value_type>() <= rhs_magnitude_;
		}
#pragma endregion

#pragma region ASSIGNMENT_OPERATORS
	public:
		constexpr inline this_type& operator=(const this_type& rhs_) noexcept
		{
			if constexpr (contains_multiple_registers)
			{
				_do_array_assign(rhs_, register_index_sequence());
			}
			else
			{
				data = rhs_.data;
			}
			return *this;
		}

		constexpr inline this_type& operator=(this_type&& rhs_) noexcept
		{
			data = std::move(rhs_.data);
			return *this;
		}

	private:
		template<std::size_t...RegisterIndices_>
		constexpr inline void _do_array_assign(const this_type& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			((data[RegisterIndices_] = rhs_.data[RegisterIndices_]), ...);
		}
#pragma endregion

#pragma region GETTERS
	public:
		/// <summary>
		/// <para> Retrieves a copy of the value at the specified index within this Vector. </para>
		/// <para> Performs a compile-time bounds check to ensure that the index is contained. If the check fails, this triggers a static_assert. </para>
		/// <para>
		///		The bounds check may either be for this Vector's encapsulated range or for the full range of its underlying indices. 
		///		By default only the encapsulated range is used, but the full-width range may be used by setting `IncludeNonEncapsulated_` to true in the template arguments.
		/// </para>
		/// <para> This may not be used to retrieve references. </para>
		/// <para>
		///		This operation can become expensive after multiple calls, and in general is not very efficient compared to normal Vector access. 
		///		As such, if multiple accesses are required it is highly recommended to instead store this Vector to a normal EmuMath Vector first and read from that.
		/// </para>
		/// </summary>
		/// <returns>Copy of the value at the specified index within this Vector's registers.</returns>
		template<std::size_t Index_, bool IncludeNonEncapsulated_ = false>
		[[nodiscard]] constexpr inline value_type at() const
		{
			constexpr std::size_t max_index = IncludeNonEncapsulated_ ? full_width_size : size;
			if constexpr (Index_ < max_index)
			{
				if constexpr (contains_multiple_registers)
				{
					constexpr std::size_t register_index = Index_ / elements_per_register;
					constexpr std::size_t index_in_register = Index_ % elements_per_register;
					return EmuSIMD::get_index<index_in_register, value_type>(GetRegister<register_index>());
				}
				else
				{
					return EmuSIMD::get_index<Index_, value_type>(data);
				}
			}
			else
			{
				if constexpr (IncludeNonEncapsulated_)
				{
					static_assert
					(
						EmuCore::TMP::get_false<Index_>(),
						"Attempted to retrieve a value from an EmuMath::FastVector (including non-encapsulated indices), but provided an Index_ exceeding the range of the Vector's full width size."
					);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Index_>(),
						"Attempted to retrieve a value from an EmuMath::FastVector (excluding non-encapsulated indices), but provided an Index_ exceeding the range of the Vector's encapsulated size."
					);
				}
			}
		}

		/// <summary>
		/// <para> Retrieves a copy of the value at the specified theoretical index within this Vector. </para>
		/// <para> Performs a compile-time bounds check to ensure that the index is contained. If the check fails, this returns a newly constructed implied-zero. </para>
		/// <para>
		///		The bounds check may either be for this Vector's encapsulated range or for the full range of its underlying indices. 
		///		By default only the encapsulated range is used, but the full-width range may be used by setting `IncludeNonEncapsulated_` to true in the template arguments.
		/// </para>
		/// <para> This may not be used to retrieve references. </para>
		/// <para>
		///		This operation can become expensive after multiple calls, and in general is not very efficient compared to normal Vector access. 
		///		As such, if multiple accesses are required it is highly recommended to instead store this Vector to a normal EmuMath Vector first and read from that.
		/// </para>
		/// </summary>
		/// <returns>
		///		Copy of the value at the specified theoretical index within this Vector's registers, 
		///		which will be this Vector's implied-zero if the index is not contained.
		/// </returns>
		template<std::size_t Index_, bool IncludeNonEncapsulated_ = false>
		[[nodiscard]] constexpr inline value_type AtTheoretical() const
		{
			constexpr std::size_t max_index = IncludeNonEncapsulated_ ? full_width_size : size;
			if constexpr (Index_ < max_index)
			{
				return at<Index_, IncludeNonEncapsulated_>();
			}
			else
			{
				return vector_type::get_implied_zero();
			}
		}

		/// <summary>
		/// <para> Retrieves a reference to the SIMD register at the provided index within this Vector's underlying registers. </para>
		/// <para> Performs a compile-time bounds check to ensure that the register is contained. If the check fails, this triggers a static_assert. </para>
		/// <para> If this Vector only contains one register, this will return a reference to `data` directly if Index_ is correctly 0. </para>
		/// </summary>
		/// <returns>Reference to the register at the provided index of this Vector's underlying registers.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline register_type& GetRegister()
		{
			if constexpr (Index_ < num_registers)
			{
				if constexpr (contains_multiple_registers)
				{
					return data[Index_];
				}
				else
				{
					return data;
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Index_>(),
					"Attempted to retrieve a register from an EmuMath::FastVector, but provided an Index_ exceeding the range of the Vector's registers."
				);
			}
		}

		/// <summary>
		/// <para> Retrieves a const-qualified to the SIMD register at the provided Index_ within this Vector's underlying registers. </para>
		/// <para> Performs a compile-time bounds check to ensure that the register is contained. If the check fails, this triggers a static_assert. </para>
		/// <para> If this Vector only contains one register, this will return a const-qualified reference to `data` directly if Index_ is correctly 0. </para>
		/// </summary>
		/// <returns>Const-qualified reference to the register at the provided index of this Vector's underlying registers.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline const register_type& GetRegister() const
		{
			return const_cast<this_type*>(this)->GetRegister<Index_>();
		}

		/// <summary>
		/// <para> 
		///		Retrieves a reference to the SIMD register at the provided Index_ within this Vector's underlying registers, 
		///		or a newly-created zeroed register if it is not contained. </para>
		/// <para> If this Vector only contains one register and the provided Index_ is 0, this will return a reference to data directly. </para>
		/// </summary>
		/// <returns>Reference to the register at the provided Index_ if it is contained; otherwise a newly created zeroed register.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline typename theoretical_register_get_result<Index_, false>::type GetRegisterTheoretical()
		{
			if constexpr (Index_ < num_registers)
			{
				return GetRegister<Index_>();
			}
			else
			{
				return EmuSIMD::setzero<register_type>();
			}
		}

		/// <summary>
		/// <para> 
		///		Retrieves a const-qualified reference to the SIMD register at the provided Index_ within this Vector's underlying registers, 
		///		or a newly-created zeroed register if it is not contained.
		/// </para>
		/// <para> If this Vector only contains one register and the provided Index_ is 0, this will return a reference to data directly. </para>
		/// </summary>
		/// <returns>Const-qualified reference to the register at the provided Index_ if it is contained; otherwise a newly created zeroed register.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline typename theoretical_register_get_result<Index_, true>::type GetRegisterTheoretical() const
		{
			return const_cast<this_type*>(this)->GetRegisterTheoretical<Index_>();
		}
#pragma endregion

#pragma region SETTERS
	public:
		/// <summary>
		/// <para> Sets all register bits in this Vector to 0. </para>
		/// </summary>
		inline void SetAllZero()
		{
			if constexpr (contains_multiple_registers)
			{
				_set_zero_array(register_index_sequence());
			}
			else
			{
				data = EmuSIMD::setzero<register_type>();
			}
		}

		/// <summary>
		/// <para> Sets all register bits in this Vector to 1. </para>
		/// </summary>
		inline void SetAllOne()
		{
			if constexpr (contains_multiple_registers)
			{
				_set_one_array(register_index_sequence());
			}
			else
			{
				data = EmuSIMD::setallone<register_type>();
			}
		}

		/// <summary>
		/// <para> Sets all elements in this Vector to match the passed val_. </para>
		/// </summary>
		/// <param name="val_">Value to set all elements to.</param>
		inline void Set1(value_type val_)
		{
			if constexpr (contains_multiple_registers)
			{
				_set_all_same_array(val_, register_index_sequence());
			}
			else
			{
				data = EmuSIMD::set1<register_type, per_element_width>(val_);
			}
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
		/// <param name="p_out_">
		///		<para> Pointer to contiguous memory to output to. </para>
		///		<para> If FullWidth_ is true or this Vector does not require a partial register, this must point to at least full_width_size items. </para>
		///		<para> 
		///			If FullWidth_ is false and this Vector and this Vector requires a partial register,
		///			this must point to at least ((num_registers - 1) * elements_per_register) + partial_register_length) items.
		///		</para>
		///		<para> If size requirements are not met, the behaviour of this function is undefined as it will write to unknown memory. </para>
		/// </param>
		template<bool FullWidth_ = false, typename Out_>
		constexpr inline void Store(Out_* p_out_) const
		{
			_store_to_non_uniform<num_registers, FullWidth_ ? 0 : partial_register_length>(p_out_);
		}
#pragma endregion

#pragma region CONST_VECTOR_ARITHMETIC
	public:
		/// <summary>
		/// <para> Calculates the 3D cross product of this Vector and b_. </para>
		/// <para> This is primarily designed for 128-bit registers of 32-bit components, and will perform automatic conversions if this Vector type does not match that. </para>
		/// <para> If this calculation is likely to be common with this Vector, it is recommended to convert it to match the design of this function. </para>
		/// </summary>
		[[nodiscard]] constexpr inline this_type Cross3(const this_type& b_) const
		{
			if constexpr (register_width == 128 && per_element_width == 32)
			{
				register_type a0 = GetRegister<0>();
				register_type b0 = b_.GetRegister<0>();

				// Mask out non-contained elements as they are implied zero for mathematical purposes
				// --- Unfortunately, we can't get away with only masking one register since they multiply with non-respective elements
				if constexpr (size < 3)
				{
					register_type mask = make_partial_end_exclude_mask_register();
					a0 = EmuSIMD::bitwise_and(a0, mask);
					b0 = EmuSIMD::bitwise_and(b0, mask);
				}

				register_type a0_1203 = EmuSIMD::shuffle<1, 2, 0, 3>(a0);
				register_type a1203_mul_b0123 = EmuSIMD::mul_all<per_element_width>(a0_1203, b0);
				return this_type
				(
					EmuSIMD::fmsub<per_element_width>
					(
						a0_1203,
						EmuSIMD::shuffle<2, 0, 1, 3>(b0),
						EmuSIMD::shuffle<1, 2, 0, 3>(a1203_mul_b0123)
					)
				);
			}
			else
			{
				constexpr std::size_t cast_size = 4;
				constexpr std::size_t cast_register_width = 128;
				using cast_type = typename std::conditional<is_integral, std::int32_t, float>::type;
				using cast_vector_type = EmuMath::FastVector<cast_size, cast_type, cast_register_width>;
				cast_vector_type cast_a = Convert<cast_size, cast_type, cast_register_width>();
				cast_vector_type cast_b = b_.Convert<cast_size, cast_type, cast_register_width>();
				return cast_a.Cross3(cast_b).Convert<Size_, T_, RegisterWidth_>();
			}
		}

		/// <summary>
		/// <para> Calculates the dot product of this Vector with another Vector of the same type. </para>
		/// <para> The result will remain as a Vector, and is guaranteed to at least be stored within the first element in the output Vector. </para>
		/// <para> If a Vector full of the result is required, use `DotFill` instead. </para>
		/// <para> If only a scalar result is required, use `DotScalar` instead. </para>
		/// </summary>
		/// <returns>FastVector containing the result of the dot product in at least its very first element.</returns>
		[[nodiscard]] constexpr inline this_type Dot(const this_type& b_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_dot<false>(data, b_.data, register_index_sequence()));
			}
			else if constexpr (requires_partial_register)
			{
				// Need extra work to make sure we dot correctly
				register_type mask = make_partial_end_exclude_mask_register();
				return this_type(EmuSIMD::dot<per_element_width>(EmuSIMD::bitwise_and(data, mask), b_.data));
			}
			else
			{
				// Safe to do a simple dot
				return this_type(EmuSIMD::dot<per_element_width>(data, b_.data));
			}
		}

		[[nodiscard]] constexpr inline this_type Dot(register_arg_type b_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_dot<false>(data, b_for_all_, register_index_sequence()));
			}
			else if constexpr (requires_partial_register)
			{
				// Need extra work to make sure we dot correctly
				register_type mask = make_partial_end_exclude_mask_register();
				return this_type(EmuSIMD::dot<per_element_width>(EmuSIMD::bitwise_and(data, mask), b_for_all_));
			}
			else
			{
				// Safe to do a simple dot
				return this_type(EmuSIMD::dot<per_element_width>(data, b_for_all_));
			}
		}

		/// <summary>
		/// <para> Calculates the dot product of this Vector with another Vector of the same type. </para>
		/// <para> The result will remain as a Vector, and is guaranteed to be stored in all elements of the output Vector. </para>
		/// <para> If only a scalar result is required, use `DotScalar` instead. </para>
		/// </summary>
		/// <returns>FastVector containing the result of the dot product in every element.</returns>
		[[nodiscard]] constexpr inline this_type DotFill(const this_type& b_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_dot<false>(data, b_.data, register_index_sequence()));
			}
			else if constexpr (requires_partial_register)
			{
				// Need extra work to make sure we dot correctly
				register_type mask = make_partial_end_exclude_mask_register();
				return this_type(EmuSIMD::dot_fill<per_element_width>(EmuSIMD::bitwise_and(data, mask), b_.data));
			}
			else
			{
				// Safe to do a simple dot
				return this_type(EmuSIMD::dot_fill<per_element_width>(data, b_.data));
			}
		}

		[[nodiscard]] constexpr inline this_type DotFill(register_arg_type b_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_dot<true>(data, b_for_all_, register_index_sequence()));
			}
			else if constexpr (requires_partial_register)
			{
				// Need extra work to make sure we dot correctly
				register_type mask = make_partial_end_exclude_mask_register();
				return this_type(EmuSIMD::dot_fill<per_element_width>(EmuSIMD::bitwise_and(data, mask), b_for_all_));
			}
			else
			{
				// Safe to do a simple dot
				return this_type(EmuSIMD::dot_fill<per_element_width>(data, b_for_all_));
			}
		}

		/// <summary>
		/// <para> Calculates the dot product of this Vector with another Vector of the same type. </para>
		/// <para> The result will be a scalar extracted from a resulting intermediate Vector. </para>
		/// <para> The output type may be customised, but may be omitted in which case it will default to value_type. </para>
		/// <para> If a Vector full of the result is required, use `DotFill` instead. </para>
		/// </summary>
		/// <returns>Scalar of the provided output type, containing the result of the dot product calculation.</returns>
		template<typename Out_ = value_type>
		[[nodiscard]] constexpr inline Out_ DotScalar(const this_type& b_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return _do_array_dot_scalar<Out_>(data, b_.data, register_index_sequence());
			}
			else if constexpr (requires_partial_register)
			{
				// Need extra work to make sure we dot correctly
				register_type mask = make_partial_end_exclude_mask_register();
				return EmuSIMD::dot_scalar<Out_, per_element_width>(EmuSIMD::bitwise_and(data, mask), b_.data);
			}
			else
			{
				// Safe to do a simple dot
				return EmuSIMD::dot_scalar<Out_, per_element_width>(data, b_.data);
			}
		}

		template<typename Out_ = value_type>
		[[nodiscard]] constexpr inline Out_ DotScalar(register_arg_type b_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return _do_array_dot_scalar<Out_>(data, b_for_all_, register_index_sequence());
			}
			else if constexpr (requires_partial_register)
			{
				// Need extra work to make sure we dot correctly
				register_type mask = make_partial_end_exclude_mask_register();
				return EmuSIMD::dot_scalar<Out_, per_element_width>(EmuSIMD::bitwise_and(data, mask), b_for_all_);
			}
			else
			{
				// Safe to do a simple dot
				return EmuSIMD::dot_scalar<Out_, per_element_width>(data, b_for_all_);
			}
		}

		/// <summary>
		/// <para> Calculates the dot product of this Vector with another Vector of the same type, treating them as 2-element Vectors. </para>
		/// <para> The result will remain as a Vector, and is guaranteed to at least be stored within the first element in the output Vector. </para>
		/// <para> If a Vector full of the result is required, use `Dot2Fill` instead. </para>
		/// <para> If only a scalar result is required, use `Dot2Scalar` instead. </para>
		/// </summary>
		/// <returns>FastVector containing the result of the 2-element dot product in at least its very first element.</returns>
		[[nodiscard]] constexpr inline this_type Dot2(const this_type& b_) const
		{
			return this_type(_calculate_dot_2(data, b_.data));
		}

		[[nodiscard]] constexpr inline this_type Dot2(register_arg_type b_) const
		{
			return this_type(_calculate_dot_2(data, b_));
		}

		/// <summary>
		/// <para> Calculates the dot product of this Vector with another Vector of the same type, treating them as 2-element Vectors. </para>
		/// <para> The result will remain as a Vector, and is guaranteed to be stored within every element in the output Vector. </para>
		/// <para> If only a scalar result is required, use `Dot2Scalar` instead. </para>
		/// </summary>
		/// <returns>FastVector containing the result of the 2-element dot product in at least its very first element.</returns>
		[[nodiscard]] constexpr inline this_type Dot2Fill(const this_type& b_) const
		{
			return this_type(_calculate_dot_2_fill(data, b_.data));
		}

		[[nodiscard]] constexpr inline this_type Dot2Fill(register_arg_type b_) const
		{
			return this_type(_calculate_dot_2_fill(data, b_));
		}

		template<typename Out_ = value_type>
		[[nodiscard]] constexpr inline Out_ Dot2Scalar(const this_type& b_) const
		{
			return EmuSIMD::get_index<0, Out_, per_element_width>(_calculate_dot_2(data, b_.data));
		}

		template<typename Out_ = value_type>
		[[nodiscard]] constexpr inline Out_ Dot2Scalar(register_arg_type b_) const
		{
			return EmuSIMD::get_index<0, Out_, per_element_width>(_calculate_dot_2(data, b_));
		}

		/// <summary>
		/// <para> Calculates the squared magnitude of this Vector, which is equivalent to its dot product with itself. </para>
		/// <para> The result will remain as a Vector, and is guaranteed to at least be stored within the first element in the output Vector. </para>
		/// <para> If a Vector full of the result is required, use `SquareMagnitudeFill` instead. </para>
		/// <para> If only a scalar result is required, use `SquareMagnitudeScalar` instead. </para>
		/// </summary>
		/// <returns>FastVector containing the square magnitude of this Vector in at least its very first element.</returns>
		[[nodiscard]] constexpr inline this_type SquareMagnitude() const
		{
			return Dot(*this);
		}
		
		/// <summary>
		/// <para> Calculates the squared magnitude of this Vector, which is equivalent to its dot product with itself. </para>
		/// <para> The result will remain as a Vector, and is guaranteed to be stored in all elements of the output Vector. </para>
		/// <para> If only a scalar result is required, use `SquareMagnitudeScalar` instead. </para>
		/// </summary>
		/// <returns>FastVector containing the square magnitude of this Vector in every element.</returns>
		[[nodiscard]] constexpr inline this_type SquareMagnitudeFill() const
		{
			return DotFill(*this);
		}

		/// <summary>
		/// <para> Calculates the squared magnitude of this Vector, which is equivalent to its dot product with itself. </para>
		/// <para> The result will be a scalar extracted from a resulting intermediate Vector. </para>
		/// <para> The output type may be customised, but may be omitted in which case it will default to value_type. </para>
		/// <para> If a Vector full of the result is required, use `SquareMagnitudeFill` instead. </para>
		/// </summary>
		/// <returns>Scalar of the provided output type, containing the squared magnitude of this Vector.</returns>
		template<typename Out_>
		[[nodiscard]] constexpr inline Out_ SquareMagnitudeScalar() const
		{
			return DotScalar<Out_>(*this);
		}

		/// <summary>
		/// <para> Calculates the magnitude of this Vector. </para>
		/// <para> The result will remain as a Vector, and is guaranteed to at least be stored within the first element in the output Vector. </para>
		/// <para> If a Vector full of the result is required, use `MagnitudeFill` instead. </para>
		/// <para> If only a scalar result is required, use `MagnitudeScalar` instead. </para>
		/// </summary>
		/// <returns>FastVector containing the magnitude of this Vector in at least its very first element.</returns>
		[[nodiscard]] constexpr inline this_type Magnitude() const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_mag<false>(data, register_index_sequence()));
			}
			else if constexpr (requires_partial_register)
			{
				register_type mag = make_partial_end_exclude_mask_register();
				mag = EmuSIMD::dot<per_element_width>(EmuSIMD::bitwise_and(data, mag), data);
				return this_type(EmuSIMD::sqrt<per_element_width, is_signed>(mag));
			}
			else
			{
				register_type mag = EmuSIMD::dot<per_element_width>(data, data);
				return this_type(EmuSIMD::sqrt<per_element_width, is_signed>(mag));
			}
		}

		/// <summary>
		/// <para> Calculates the magnitude of this Vector. </para>
		/// <para> The result will remain as a Vector, and is guaranteed to be stored in all elements of the output Vector. </para>
		/// <para> If only a scalar result is required, use `MagnitudeScalar` instead. </para>
		/// </summary>
		/// <returns>FastVector containing the magnitude of this Vector in every element.</returns>
		[[nodiscard]] constexpr inline this_type MagnitudeFill() const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_mag<true>(data, register_index_sequence()));
			}
			else if constexpr (requires_partial_register)
			{
				register_type mag = make_partial_end_exclude_mask_register();
				mag = EmuSIMD::dot_fill<per_element_width>(EmuSIMD::bitwise_and(data, mag), data);
				return this_type(EmuSIMD::sqrt<per_element_width, is_signed>(mag));
			}
			else
			{
				register_type mag = EmuSIMD::dot_fill<per_element_width>(data, data);
				return this_type(EmuSIMD::sqrt<per_element_width, is_signed>(mag));
			}
		}

		/// <summary>
		/// <para> Calculates the magnitude of this Vector. </para>
		/// <para> The result will be a scalar extracted from a resulting intermediate Vector. </para>
		/// <para> The output type may be customised, but may be omitted in which case it will default to value_type. </para>
		/// <para> If a Vector full of the result is required, use `MagnitudeFill` instead. </para>
		/// </summary>
		/// <returns>Scalar of the provided output type, containing the magnitude of this Vector.</returns>
		template<typename Out_ = value_type>
		[[nodiscard]] constexpr inline Out_ MagnitudeScalar() const
		{
			if constexpr (contains_multiple_registers)
			{
				return _do_array_mag_scalar<Out_>(data, register_index_sequence());
			}
			else if constexpr (requires_partial_register)
			{
				// Need extra work to make sure we dot correctly
				register_type mask = make_partial_end_exclude_mask_register();

				if constexpr (per_element_byte_size <= 4)
				{
					return static_cast<Out_>(sqrtf(EmuSIMD::dot_scalar<float, per_element_width>(EmuSIMD::bitwise_and(data, mask), data)));
				}
				else
				{
					return static_cast<Out_>(sqrt(EmuSIMD::dot_scalar<double, per_element_width>(EmuSIMD::bitwise_and(data, mask), data)));
				}
			}
			else
			{
				// Safe to do a simple dot
				if constexpr (per_element_byte_size <= 4)
				{
					return static_cast<Out_>(sqrtf(EmuSIMD::dot_scalar<float, per_element_width>(data, data)));
				}
				else
				{
					return static_cast<Out_>(sqrt(EmuSIMD::dot_scalar<double, per_element_width>(data, data)));
				}
			}
		}

		/// <summary>
		/// <para> Calculates the distance between this Vector and target_, which is equivalent to the magnitude of the Vector resulting from `target_ - this_vector`. </para>
		/// <para> The result will remain as a Vector, and is guaranteed to at least be stored within the first element in the output Vector. </para>
		/// <para> If a Vector full of the result is required, use `DistanceFill` instead. </para>
		/// <para> If only a scalar result is required, use `DistanceScalar` instead. </para>
		/// </summary>
		/// <returns>Scalar of the provided output type containing the distance between this Vector and the target_ Vector in at least its very first element.</returns>
		[[nodiscard]] constexpr inline this_type Distance(const this_type& target_) const
		{
			return target_.Subtract(*this).Magnitude();
		}

		/// <summary>
		/// <para> Calculates the distance between this Vector and target_, which is equivalent to the magnitude of the Vector resulting from `target_ - this_vector`. </para>
		/// <para> The result will remain as a Vector, and is guaranteed to be stored in all elements of the output Vector. </para>
		/// <para> If only a scalar result is required, use `DistanceScalar` instead. </para>
		/// </summary>
		/// <returns>FastVector containing the distance between this Vector and the target_ Vector in every element.</returns>
		[[nodiscard]] constexpr inline this_type DistanceFill(const this_type& target_) const
		{
			return target_.Subtract(*this).MagnitudeFill();
		}

		/// <summary>
		/// <para> Calculates the distance between this Vector and target_, which is equivalent to the magnitude of the Vector resulting from `target_ - this_vector`. </para>
		/// <para> The result will be a scalar extracted from a resulting intermediate Vector. </para>
		/// <para> If a Vector full of the result is required, use `DistanceFill` instead. </para>
		/// </summary>
		/// <returns>Scalar of the provided output type, containing the distance between this Vector and the target_ Vector in every element.</returns>
		template<typename Out_ = value_type>
		[[nodiscard]] constexpr inline Out_ DistanceScalar(const this_type& target_) const
		{
			return target_.Subtract(*this).MagnitudeScalar<Out_>();
		}

		/// <summary>
		/// <para> 
		///		Calculates the squared distance between this Vector and target_, 
		///		which is equivalent to the squared magnitude of the Vector resulting from `target_ - this_vector`.
		/// </para>
		/// <para> The result will remain as a Vector, and is guaranteed to at least be stored within the first element in the output Vector. </para>
		/// <para> If a Vector full of the result is required, use `SquareDistanceFill` instead. </para>
		/// <para> If only a scalar result is required, use `SquareDistanceScalar` instead. </para>
		/// </summary>
		/// <returns>FastVector containing the squared distance between this Vector and the target_ Vector in at least its very first element.</returns>
		[[nodiscard]] constexpr inline this_type SquareDistance(const this_type& target_) const
		{
			return target_.Subtract(*this).SquareMagnitude();
		}

		/// <summary>
		/// <para> 
		///		Calculates the squared distance between this Vector and target_, 
		///		which is equivalent to the squared magnitude of the Vector resulting from `target_ - this_vector`.
		/// </para>
		/// <para> The result will remain as a Vector, and is guaranteed to be stored in all elements of the output Vector. </para>
		/// <para> If only a scalar result is required, use `SquareDistanceScalar` instead. </para>
		/// </summary>
		/// <returns>FastVector containing the squared distance between this Vector and the target_ Vector in every element.</returns>
		[[nodiscard]] constexpr inline this_type SquareDistanceFill(const this_type& target_) const
		{
			return target_.Subtract(*this).SquareMagnitudeFill();
		}

		/// <summary>
		/// <para> 
		///		Calculates the squared distance between this Vector and target_, 
		///		which is equivalent to the squared magnitude of the Vector resulting from `target_ - this_vector`.
		/// </para>
		/// <para> The result will be a scalar extracted from a resulting intermediate Vector. </para>
		/// <para> If a Vector full of the result is required, use `SquareDistanceFill` instead. </para>
		/// </summary>
		/// <returns>Scalar of the provided output type, containing the squared distance between this Vector and the target_ Vector in every element.</returns>
		template<typename Out_ = value_type>
		[[nodiscard]] constexpr inline Out_ SquareDistanceScalar(const this_type& target_) const
		{
			return target_.Subtract(*this).SquareMagnitudeScalar<Out_>();
		}

		/// <summary>
		/// <para> Linearly interpolates this Vector with the provided b_ and t_ arguments. </para>
		/// <para> If an argument is a FastVector, all registers and elements will be used respectively. </para>
		/// <para> If an argument is this Vector's register_type, each respective element of it will be used for all registers. </para>
		/// <para> If an argument is a scalar value, it will be used for all elements. </para>
		/// </summary>
		/// <param name="b_">Target to interpolate this Vector with.</param>
		/// <param name="t_">Threshold to use for interpolations, interpreted as percentages where 0 = 0%, 1 = 100%.</param>
		/// <returns>Vector resulting from the linear interpolation operation.</returns>
		[[nodiscard]] constexpr inline this_type Lerp(const this_type& b_, const this_type& t_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_lerp(data, b_.data, t_.data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::lerp<per_element_width>(data, b_.data, t_.data));
			}
		}

		[[nodiscard]] constexpr inline this_type Lerp(register_arg_type b_for_all_, const this_type& t_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_lerp(data, b_for_all_, t_.data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::lerp<per_element_width>(data, b_for_all_, t_.data));
			}
		}

		[[nodiscard]] constexpr inline this_type Lerp(const this_type& b_, register_arg_type t_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_lerp(data, b_.data, t_for_all_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::lerp<per_element_width>(data, b_.data, t_for_all_));
			}
		}

		[[nodiscard]] constexpr inline this_type Lerp(register_arg_type b_for_all_, register_arg_type t_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_lerp(data, b_for_all_, t_for_all_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::lerp<per_element_width>(data, b_for_all_, t_for_all_));
			}
		}

		[[nodiscard]] constexpr inline this_type Lerp(register_arg_type b_for_all_, value_type t_) const
		{
			return Lerp(b_for_all_, EmuSIMD::set1<register_type, per_element_width>(t_));
		}

		[[nodiscard]] constexpr inline this_type Lerp(value_type b_, register_arg_type t_for_all_) const
		{
			return Lerp(EmuSIMD::set1<register_type, per_element_width>(b_), t_for_all_);
		}

		[[nodiscard]] constexpr inline this_type Lerp(const this_type& b_, value_type t_) const
		{
			return Lerp(b_, EmuSIMD::set1<register_type, per_element_width>(t_));
		}

		[[nodiscard]] constexpr inline this_type Lerp(value_type b_, const this_type& t_) const
		{
			return Lerp(EmuSIMD::set1<register_type, per_element_width>(b_), t_);
		}

		[[nodiscard]] constexpr inline this_type Lerp(value_type b_, value_type t_) const
		{
			return Lerp(EmuSIMD::set1<register_type, per_element_width>(b_), EmuSIMD::set1<register_type, per_element_width>(t_));
		}

		/// <summary>
		/// <para> Linearly interpolates this Vector with the provided b_ and t_ arguments. </para>
		/// <para> A fused lerp differentiates from a normal lerp in that multiplication and addition operations will be fused to reduce floating-point rounds. </para>
		/// <para> If an argument is a FastVector, all registers and elements will be used respectively. </para>
		/// <para> If an argument is this Vector's register_type, each respective element of it will be used for all registers. </para>
		/// <para> If an argument is a scalar value, it will be used for all elements. </para>
		/// </summary>
		/// <param name="b_">Target to interpolate this Vector with.</param>
		/// <param name="t_">Threshold to use for interpolations, interpreted as percentages where 0 = 0%, 1 = 100%.</param>
		/// <returns>Vector resulting from the linear interpolation operation.</returns>
		[[nodiscard]] constexpr inline this_type FusedLerp(const this_type& b_, const this_type& t_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_fused_lerp(data, b_.data, t_.data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::fused_lerp<per_element_width>(data, b_.data, t_.data));
			}
		}

		[[nodiscard]] constexpr inline this_type FusedLerp(register_arg_type b_for_all_, const this_type& t_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_fused_lerp(data, b_for_all_, t_.data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::fused_lerp<per_element_width>(data, b_for_all_, t_.data));
			}
		}

		[[nodiscard]] constexpr inline this_type FusedLerp(const this_type& b_, register_arg_type t_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_fused_lerp(data, b_.data, t_for_all_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::fused_lerp<per_element_width>(data, b_.data, t_for_all_));
			}
		}

		[[nodiscard]] constexpr inline this_type FusedLerp(register_arg_type b_for_all_, register_arg_type t_for_all_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_fused_lerp(data, b_for_all_, t_for_all_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::fused_lerp<per_element_width>(data, b_for_all_, t_for_all_));
			}
		}

		[[nodiscard]] constexpr inline this_type FusedLerp(register_arg_type b_for_all_, value_type t_) const
		{
			return FusedLerp(b_for_all_, EmuSIMD::set1<register_type, per_element_width>(t_));
		}

		[[nodiscard]] constexpr inline this_type FusedLerp(value_type b_, register_arg_type t_for_all_) const
		{
			return FusedLerp(EmuSIMD::set1<register_type, per_element_width>(b_), t_for_all_);
		}

		[[nodiscard]] constexpr inline this_type FusedLerp(const this_type& b_, value_type t_) const
		{
			return FusedLerp(b_, EmuSIMD::set1<register_type, per_element_width>(t_));
		}

		[[nodiscard]] constexpr inline this_type FusedLerp(value_type b_, const this_type& t_) const
		{
			return FusedLerp(EmuSIMD::set1<register_type, per_element_width>(b_), t_);
		}

		[[nodiscard]] constexpr inline this_type FusedLerp(value_type b_, value_type t_) const
		{
			return FusedLerp(EmuSIMD::set1<register_type, per_element_width>(b_), EmuSIMD::set1<register_type, per_element_width>(t_));
		}

		/// <summary>
		/// <para> Calculates and outputs the normalised form of this Vector. </para>
		/// <para> 
		///		The output element type may be modified with the `OutFP_` argument for this function. It is not enforced, but recommended to use a floating-point type. 
		///		This defaults to the Vector's preferred_floating_point type.
		/// </para>
		/// <para> Conversions for floating-point calculations will be performed automatically; these conversions will be minimised where possible. </para>
		/// </summary>
		/// <returns>Normalised form of this Vector.</returns>
		template<typename OutFP_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::FastVector<Size_, OutFP_, RegisterWidth_> Normalise() const
		{
			using out_vector = EmuMath::FastVector<Size_, OutFP_, RegisterWidth_>;
			constexpr bool out_is_fp = out_vector::is_floating_point;
			constexpr bool output_same = std::is_same_v<this_type, out_vector>;

			if constexpr (output_same && is_floating_point)
			{
				return _do_normalise(*this);
			}
			else if constexpr (is_floating_point)
			{
				return _do_normalise(*this).Convert<OutFP_>();
			}
			else if constexpr (out_is_fp)
			{
				return _do_normalise(this->Convert<OutFP_>());
			}
			else
			{
				return _do_normalise(this->Convert<preferred_floating_point>()).Convert<OutFP_>();
			}
		}
#pragma endregion

#pragma region COMPARISONS_ANY
	public:
		/// <summary>
		/// <para> Returns true if any respective elements are equal between this Vector and the passed Vector. </para>
		/// </summary>
		/// <param name="rhs_">Vector to compare respective values of this Vector with.</param>
		/// <returns>True if at least one element of this Vector matches the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAnyEqual(const this_type& rhs_) const
		{
			return _do_cmp_equal_bool_out<false>(data, rhs_.data);
		}

		/// <summary>
		/// <para> Returns true if any respective elements are equal between this Vector's register(s) and the passed register. </para>
		/// </summary>
		/// <param name="rhs_">Register to compare the registers of this Vector with.</param>
		/// <returns>True if at least one element of any of this Vector's registers matches the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAnyEqual(register_arg_type rhs_) const
		{
			return _do_cmp_equal_bool_out<false>(data, rhs_);
		}

		/// <summary>
		/// <para> Returns true if any elements in this Vector are equal to the passed value. </para>
		/// <para> This will create an intermediate register for SIMD comparisons. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare the elements of this Vector with.</param>
		/// <returns>True if at least one element of this Vector matches `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAnyEqual(value_type rhs_) const
		{
			return _do_cmp_equal_bool_out<false>(data, EmuSIMD::set1<register_type, per_element_width>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if any respective elements are not equal between this Vector and the passed Vector. </para>
		/// </summary>
		/// <param name="rhs_">Vector to compare respective values of this Vector with.</param>
		/// <returns>True if at least one element of this Vector does not match the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAnyNotEqual(const this_type& rhs_) const
		{
			return _do_cmp_not_equal_bool_out<false>(data, rhs_.data);
		}

		/// <summary>
		/// <para> Returns true if any respective elements are not equal between this Vector's register(s) and the passed register. </para>
		/// </summary>
		/// <param name="rhs_">Register to compare the registers of this Vector with.</param>
		/// <returns>True if at least one element of any of this Vector's registers does not match the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAnyNotEqual(register_arg_type rhs_) const
		{
			return _do_cmp_not_equal_bool_out<false>(data, rhs_);
		}

		/// <summary>
		/// <para> Returns true if any elements in this Vector are not equal to the passed value. </para>
		/// <para> This will create an intermediate register for SIMD comparisons. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare the elements of this Vector with.</param>
		/// <returns>True if at least one element of this Vector does not match `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAnyNotEqual(value_type rhs_) const
		{
			return _do_cmp_not_equal_bool_out<false>(data, EmuSIMD::set1<register_type, per_element_width>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if any respective elements are near-equal between this Vector and the passed Vector. </para>
		/// <para> This is intended as a floating-point equality comparison function to avoid potentially inaccurate results due to floating-point rounding losses. </para>
		/// </summary>
		/// <param name="rhs_">Vector to compare respective values of this Vector with.</param>
		/// <returns>True if at least one element of this Vector near-matches the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAnyNear(const this_type& rhs_) const
		{
			return _do_cmp_near_equal_bool_out<false>(data, rhs_.data);
		}

		/// <summary>
		/// <para> Returns true if any respective elements are near-equal between this Vector's register(s) and the passed register. </para>
		/// <para> This is intended as a floating-point equality comparison function to avoid potentially inaccurate results due to floating-point rounding losses. </para>
		/// </summary>
		/// <param name="rhs_">Register to compare the registers of this Vector with.</param>
		/// <returns>True if at least one element of any of this Vector's registers near-matches the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAnyNear(register_arg_type rhs_) const
		{
			return _do_cmp_near_equal_bool_out<false>(data, rhs_);
		}

		/// <summary>
		/// <para> Returns true if any elements in this Vector are near-equal to the passed value. </para>
		/// <para> This is intended as a floating-point equality comparison function to avoid potentially inaccurate results due to floating-point rounding losses. </para>
		/// <para> This will create an intermediate register for SIMD comparisons. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare the elements of this Vector with.</param>
		/// <returns>True if at least one element of this Vector near-matches `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAnyNear(value_type rhs_) const
		{
			return _do_cmp_near_equal_bool_out<false>(data, EmuSIMD::set1<register_type, per_element_width>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if any elements in this Vector are near-equal to the passed value, based on the provided Epsilon. </para>
		/// <para> This is intended as a floating-point equality comparison function to avoid potentially inaccurate results due to floating-point rounding losses. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare the elements of this Vector with.</param>
		/// <param name="epsilon_">Epsilon denoting the maximum magnitude of the difference between two values to be considered near-equal.</param>
		/// <returns>True if at least one element of this Vector near-matches the respective element of `rhs_` based on `epsilon_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAnyNear(const this_type& rhs_, const this_type& epsilon_) const
		{
			return _do_cmp_near_equal_bool_out<false>(data, rhs_.data, epsilon_.data);
		}

		[[nodiscard]] constexpr inline bool CmpAnyNear(const this_type& rhs_, register_arg_type epsilon_) const
		{
			return _do_cmp_near_equal_bool_out<false>(data, rhs_.data, epsilon_);
		}

		[[nodiscard]] constexpr inline bool CmpAnyNear(register_arg_type rhs_, const this_type& epsilon_) const
		{
			return _do_cmp_near_equal_bool_out<false>(data, rhs_, epsilon_.data);
		}

		[[nodiscard]] constexpr inline bool CmpAnyNear(register_arg_type rhs_, register_arg_type epsilon_) const
		{
			return _do_cmp_near_equal_bool_out<false>(data, rhs_, epsilon_.data);
		}

		[[nodiscard]] constexpr inline bool CmpAnyNear(const this_type& rhs_, value_type epsilon_) const
		{
			return CmpAnyNear(rhs_, EmuSIMD::set1<register_type, per_element_width>(epsilon_));
		}

		[[nodiscard]] constexpr inline bool CmpAnyNear(register_arg_type rhs_, value_type epsilon_) const
		{
			return CmpAnyNear(rhs_, EmuSIMD::set1<register_type, per_element_width>(epsilon_));
		}

		[[nodiscard]] constexpr inline bool CmpAnyNear(value_type rhs_, const this_type& epsilon_) const
		{
			return CmpAnyNear(EmuSIMD::set1<register_type, per_element_width>(rhs_), epsilon_);
		}

		[[nodiscard]] constexpr inline bool CmpAnyNear(value_type rhs_, register_arg_type epsilon_) const
		{
			return CmpAnyNear(EmuSIMD::set1<register_type, per_element_width>(rhs_), epsilon_);
		}

		[[nodiscard]] constexpr inline bool CmpAnyNear(value_type rhs_, value_type epsilon_) const
		{
			return CmpAnyNear(EmuSIMD::set1<register_type, per_element_width>(rhs_), EmuSIMD::set1<register_type, per_element_width>(epsilon_));
		}

		/// <summary>
		/// <para> Returns true if any respective elements are greater than those of the passed Vector. </para>
		/// </summary>
		/// <param name="rhs_">Vector to compare respective values of this Vector with.</param>
		/// <returns>True if at least one element of this Vector is greater than the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAnyGreater(const this_type& rhs_) const
		{
			return _do_cmp_greater_bool_out<false>(data, rhs_.data);
		}

		/// <summary>
		/// <para> Returns true if any respective elements in this Vector's register(s) are greater than those of the passed register. </para>
		/// </summary>
		/// <param name="rhs_">Register to compare the registers of this Vector with.</param>
		/// <returns>True if at least one element of any of this Vector's registers is greater than the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAnyGreater(register_arg_type rhs_) const
		{
			return _do_cmp_greater_bool_out<false>(data, rhs_);
		}

		/// <summary>
		/// <para> Returns true if any elements in this Vector are greater than the passed value. </para>
		/// <para> This will create an intermediate register for SIMD comparisons. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare the elements of this Vector with.</param>
		/// <returns>True if at least one element of this Vector is greater than `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAnyGreater(value_type rhs_) const
		{
			return _do_cmp_greater_bool_out<false>(data, EmuSIMD::set1<register_type, per_element_width>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if any respective elements are less than those of the passed Vector. </para>
		/// </summary>
		/// <param name="rhs_">Vector to compare respective values of this Vector with.</param>
		/// <returns>True if at least one element of this Vector is less than the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAnyLess(const this_type& rhs_) const
		{
			return _do_cmp_less_bool_out<false>(data, rhs_.data);
		}

		/// <summary>
		/// <para> Returns true if any respective elements in this Vector's register(s) are less than those of the passed register. </para>
		/// </summary>
		/// <param name="rhs_">Register to compare the registers of this Vector with.</param>
		/// <returns>True if at least one element of any of this Vector's registers is less than the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAnyLess(register_arg_type rhs_) const
		{
			return _do_cmp_less_bool_out<false>(data, rhs_);
		}

		/// <summary>
		/// <para> Returns true if any elements in this Vector are less than the passed value. </para>
		/// <para> This will create an intermediate register for SIMD comparisons. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare the elements of this Vector with.</param>
		/// <returns>True if at least one element of this Vector is less than `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAnyLess(value_type rhs_) const
		{
			return _do_cmp_less_bool_out<false>(data, EmuSIMD::set1<register_type, per_element_width>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if any respective elements are greater than or equal to those of the passed Vector. </para>
		/// </summary>
		/// <param name="rhs_">Vector to compare respective values of this Vector with.</param>
		/// <returns>True if at least one element of this Vector is greater than or equal to the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAnyGreaterEqual(const this_type& rhs_) const
		{
			return _do_cmp_greater_equal_bool_out<false>(data, rhs_.data);
		}

		/// <summary>
		/// <para> Returns true if any respective elements in this Vector's register(s) are greater than or equal to those of the passed register. </para>
		/// </summary>
		/// <param name="rhs_">Register to compare the registers of this Vector with.</param>
		/// <returns>True if at least one element of any of this Vector's registers is greater than or equal to the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAnyGreaterEqual(register_arg_type rhs_) const
		{
			return _do_cmp_greater_equal_bool_out<false>(data, rhs_);
		}

		/// <summary>
		/// <para> Returns true if any elements in this Vector are greater than or equal to the passed value. </para>
		/// <para> This will create an intermediate register for SIMD comparisons. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare the elements of this Vector with.</param>
		/// <returns>True if at least one element of this Vector is greater than or equal to `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAnyGreaterEqual(value_type rhs_) const
		{
			return _do_cmp_greater_equal_bool_out<false>(data, EmuSIMD::set1<register_type, per_element_width>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if any respective elements are less than or equal to those of the passed Vector. </para>
		/// </summary>
		/// <param name="rhs_">Vector to compare respective values of this Vector with.</param>
		/// <returns>True if at least one element of this Vector is less than or equal to the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAnyLessEqual(const this_type& rhs_) const
		{
			return _do_cmp_less_equal_bool_out<false>(data, rhs_.data);
		}

		/// <summary>
		/// <para> Returns true if any respective elements in this Vector's register(s) are less than or equal to those of the passed register. </para>
		/// </summary>
		/// <param name="rhs_">Register to compare the registers of this Vector with.</param>
		/// <returns>True if at least one element of any of this Vector's registers is less than or equal to the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAnyLessEqual(register_arg_type rhs_) const
		{
			return _do_cmp_less_equal_bool_out<false>(data, rhs_);
		}

		/// <summary>
		/// <para> Returns true if any elements in this Vector are less than or equal to the passed value. </para>
		/// <para> This will create an intermediate register for SIMD comparisons. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare the elements of this Vector with.</param>
		/// <returns>True if at least one element of this Vector is less than or equal to `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAnyLessEqual(value_type rhs_) const
		{
			return _do_cmp_less_equal_bool_out<false>(data, EmuSIMD::set1<register_type, per_element_width>(rhs_));
		}
#pragma endregion

#pragma region COMPARISONS_ALL
	public:
		/// <summary>
		/// <para> Returns true if all respective elements are equal between this Vector and the passed Vector. </para>
		/// </summary>
		/// <param name="rhs_">Vector to compare respective values of this Vector with.</param>
		/// <returns>True if every element of this Vector matches the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAllEqual(const this_type& rhs_) const
		{
			return _do_cmp_equal_bool_out<true>(data, rhs_.data);
		}

		/// <summary>
		/// <para> Returns true if all respective elements are equal between this Vector's register(s) and the passed register. </para>
		/// </summary>
		/// <param name="rhs_">Register to compare the registers of this Vector with.</param>
		/// <returns>True if every element of all of this Vector's registers matches the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAllEqual(register_arg_type rhs_) const
		{
			return _do_cmp_equal_bool_out<true>(data, rhs_);
		}

		/// <summary>
		/// <para> Returns true if all elements in this Vector are equal to the passed value. </para>
		/// <para> This will create an intermediate register for SIMD comparisons. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare the elements of this Vector with.</param>
		/// <returns>True if every element of this Vector matches `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAllEqual(value_type rhs_) const
		{
			return _do_cmp_not_equal_bool_out<true>(data, EmuSIMD::set1<register_type, per_element_width>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if all respective elements are equal between this Vector and the passed Vector. </para>
		/// </summary>
		/// <param name="rhs_">Vector to compare respective values of this Vector with.</param>
		/// <returns>True if every element of this Vector does not match the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAllNotEqual(const this_type& rhs_) const
		{
			return _do_cmp_equal_bool_out<true>(data, rhs_.data);
		}

		/// <summary>
		/// <para> Returns true if all respective elements are equal between this Vector's register(s) and the passed register. </para>
		/// </summary>
		/// <param name="rhs_">Register to compare the registers of this Vector with.</param>
		/// <returns>True if every element of all of this Vector's registers does not match the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAllNotEqual(register_arg_type rhs_) const
		{
			return _do_cmp_equal_bool_out<true>(data, rhs_);
		}

		/// <summary>
		/// <para> Returns true if all elements in this Vector are equal to the passed value. </para>
		/// <para> This will create an intermediate register for SIMD comparisons. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare the elements of this Vector with.</param>
		/// <returns>True if every element of this Vector does not match `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAllNotEqual(value_type rhs_) const
		{
			return _do_cmp_not_equal_bool_out<true>(data, EmuSIMD::set1<register_type, per_element_width>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if all respective elements are near-equal between this Vector and the passed Vector. </para>
		/// <para> This is intended as a floating-point equality comparison function to avoid potentially inaccurate results due to floating-point rounding losses. </para>
		/// </summary>
		/// <param name="rhs_">Vector to compare respective values of this Vector with.</param>
		/// <returns>True if every element of this Vector near-matches the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAllNear(const this_type& rhs_) const
		{
			return _do_cmp_near_equal_bool_out<true>(data, rhs_.data);
		}

		/// <summary>
		/// <para> Returns true if all respective elements are near-equal between this Vector's register(s) and the passed register. </para>
		/// <para> This is intended as a floating-point equality comparison function to avoid potentially inaccurate results due to floating-point rounding losses. </para>
		/// </summary>
		/// <param name="rhs_">Register to compare the registers of this Vector with.</param>
		/// <returns>True if every element of all of this Vector's registers near-matches the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAllNear(register_arg_type rhs_) const
		{
			return _do_cmp_near_equal_bool_out<true>(data, rhs_);
		}

		/// <summary>
		/// <para> Returns true if all elements in this Vector are near-equal to the passed value. </para>
		/// <para> This is intended as a floating-point equality comparison function to avoid potentially inaccurate results due to floating-point rounding losses. </para>
		/// <para> This will create an intermediate register for SIMD comparisons. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare the elements of this Vector with.</param>
		/// <returns>True if every element of this Vector near-matches `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAllNear(value_type rhs_) const
		{
			return _do_cmp_near_equal_bool_out<true>(data, EmuSIMD::set1<register_type, per_element_width>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if all elements in this Vector are near-equal to the passed value, based on the provided Epsilon. </para>
		/// <para> This is intended as a floating-point equality comparison function to avoid potentially inaccurate results due to floating-point rounding losses. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare the elements of this Vector with.</param>
		/// <param name="epsilon_">Epsilon denoting the maximum magnitude of the difference between two values to be considered near-equal.</param>
		/// <returns>True if every element of this Vector near-matches the respective element of `rhs_` based on `epsilon_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAllNear(const this_type& rhs_, const this_type& epsilon_) const
		{
			return _do_cmp_near_equal_bool_out<true>(data, rhs_.data, epsilon_.data);
		}

		[[nodiscard]] constexpr inline bool CmpAllNear(const this_type& rhs_, register_arg_type epsilon_) const
		{
			return _do_cmp_near_equal_bool_out<true>(data, rhs_.data, epsilon_);
		}

		[[nodiscard]] constexpr inline bool CmpAllNear(register_arg_type rhs_, const this_type& epsilon_) const
		{
			return _do_cmp_near_equal_bool_out<true>(data, rhs_, epsilon_.data);
		}

		[[nodiscard]] constexpr inline bool CmpAllNear(register_arg_type rhs_, register_arg_type epsilon_) const
		{
			return _do_cmp_near_equal_bool_out<true>(data, rhs_, epsilon_.data);
		}

		[[nodiscard]] constexpr inline bool CmpAllNear(const this_type& rhs_, value_type epsilon_) const
		{
			return CmpAllNear(rhs_, EmuSIMD::set1<register_type, per_element_width>(epsilon_));
		}

		[[nodiscard]] constexpr inline bool CmpAllNear(register_arg_type rhs_, value_type epsilon_) const
		{
			return CmpAllNear(rhs_, EmuSIMD::set1<register_type, per_element_width>(epsilon_));
		}

		[[nodiscard]] constexpr inline bool CmpAllNear(value_type rhs_, const this_type& epsilon_) const
		{
			return CmpAllNear(EmuSIMD::set1<register_type, per_element_width>(rhs_), epsilon_);
		}

		[[nodiscard]] constexpr inline bool CmpAllNear(value_type rhs_, register_arg_type epsilon_) const
		{
			return CmpAllNear(EmuSIMD::set1<register_type, per_element_width>(rhs_), epsilon_);
		}

		[[nodiscard]] constexpr inline bool CmpAllNear(value_type rhs_, value_type epsilon_) const
		{
			return CmpAllNear(EmuSIMD::set1<register_type, per_element_width>(rhs_), EmuSIMD::set1<register_type, per_element_width>(epsilon_));
		}

		/// <summary>
		/// <para> Returns true if all respective elements are greater than those of the passed Vector. </para>
		/// </summary>
		/// <param name="rhs_">Vector to compare respective values of this Vector with.</param>
		/// <returns>True if every element of this Vector is greater than the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAllGreater(const this_type& rhs_) const
		{
			return _do_cmp_greater_bool_out<true>(data, rhs_.data);
		}

		/// <summary>
		/// <para> Returns true if all respective elements in this Vector's register(s) are greater than those of the passed register. </para>
		/// </summary>
		/// <param name="rhs_">Register to compare the registers of this Vector with.</param>
		/// <returns>True if every element of all of this Vector's registers is greater than the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAllGreater(register_arg_type rhs_) const
		{
			return _do_cmp_greater_bool_out<true>(data, rhs_);
		}

		/// <summary>
		/// <para> Returns true if all elements in this Vector are greater than the passed value. </para>
		/// <para> This will create an intermediate register for SIMD comparisons. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare the elements of this Vector with.</param>
		/// <returns>True if every element of this Vector is greater than `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAllGreater(value_type rhs_) const
		{
			return _do_cmp_greater_bool_out<true>(data, EmuSIMD::set1<register_type, per_element_width>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if all respective elements are less than those of the passed Vector. </para>
		/// </summary>
		/// <param name="rhs_">Vector to compare respective values of this Vector with.</param>
		/// <returns>True if every element of this Vector is less than the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAllLess(const this_type& rhs_) const
		{
			return _do_cmp_less_bool_out<true>(data, rhs_.data);
		}

		/// <summary>
		/// <para> Returns true if all respective elements in this Vector's register(s) are less than those of the passed register. </para>
		/// </summary>
		/// <param name="rhs_">Register to compare the registers of this Vector with.</param>
		/// <returns>True if every element of all of this Vector's registers is less than the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAllLess(register_arg_type rhs_) const
		{
			return _do_cmp_less_bool_out<true>(data, rhs_);
		}

		/// <summary>
		/// <para> Returns true if all elements in this Vector are less than the passed value. </para>
		/// <para> This will create an intermediate register for SIMD comparisons. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare the elements of this Vector with.</param>
		/// <returns>True if every element of this Vector is less than `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAllLess(value_type rhs_) const
		{
			return _do_cmp_less_bool_out<true>(data, EmuSIMD::set1<register_type, per_element_width>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if all respective elements are greater than or equal to those of the passed Vector. </para>
		/// </summary>
		/// <param name="rhs_">Vector to compare respective values of this Vector with.</param>
		/// <returns>True if every element of this Vector is greater than or equal to the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAllGreaterEqual(const this_type& rhs_) const
		{
			return _do_cmp_greater_equal_bool_out<true>(data, rhs_.data);
		}

		/// <summary>
		/// <para> Returns true if all respective elements in this Vector's register(s) are greater than or equal to those of the passed register. </para>
		/// </summary>
		/// <param name="rhs_">Register to compare the registers of this Vector with.</param>
		/// <returns>True if every element of all of this Vector's registers is greater than or equal to the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAllGreaterEqual(register_arg_type rhs_) const
		{
			return _do_cmp_greater_equal_bool_out<true>(data, rhs_);
		}

		/// <summary>
		/// <para> Returns true if all elements in this Vector are greater than or equal to the passed value. </para>
		/// <para> This will create an intermediate register for SIMD comparisons. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare the elements of this Vector with.</param>
		/// <returns>True if every element of this Vector is greater than or equal to `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAllGreaterEqual(value_type rhs_) const
		{
			return _do_cmp_greater_equal_bool_out<true>(data, EmuSIMD::set1<register_type, per_element_width>(rhs_));
		}

		/// <summary>
		/// <para> Returns true if all respective elements are less than or equal to those of the passed Vector. </para>
		/// </summary>
		/// <param name="rhs_">Vector to compare respective values of this Vector with.</param>
		/// <returns>True if every element of this Vector is less than or equal to the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAllLessEqual(const this_type& rhs_) const
		{
			return _do_cmp_less_equal_bool_out<true>(data, rhs_.data);
		}

		/// <summary>
		/// <para> Returns true if all respective elements in this Vector's register(s) are less than or equal to those of the passed register. </para>
		/// </summary>
		/// <param name="rhs_">Register to compare the registers of this Vector with.</param>
		/// <returns>True if every element of all of this Vector's registers is less than or equal to the respective element of `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAllLessEqual(register_arg_type rhs_) const
		{
			return _do_cmp_less_equal_bool_out<true>(data, rhs_);
		}

		/// <summary>
		/// <para> Returns true if all elements in this Vector are less than or equal to the passed value. </para>
		/// <para> This will create an intermediate register for SIMD comparisons. </para>
		/// </summary>
		/// <param name="rhs_">Value to compare the elements of this Vector with.</param>
		/// <returns>True if every element of this Vector is less than or equal to `rhs_`; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool CmpAllLessEqual(value_type rhs_) const
		{
			return _do_cmp_less_equal_bool_out<true>(data, EmuSIMD::set1<register_type, per_element_width>(rhs_));
		}
#pragma endregion

#pragma region COMPARISONS_PER_ELEMENT
	public:
		/// <summary>
		/// <para> Returns another Vector of this type that acts as a mask indicating if respective elements in this Vector and rhs_ are equal. </para>
		/// <para> In the returned mask, indices that returned true will have all bits set to 1; indices that returned false will have all bits set to 0. </para>
		/// </summary>
		/// <param name="rhs_">Vector to compare this Vector with, appearing on the right-hand side of comparison.</param>
		/// <returns>Vector of the same type representing a mask of comparison results.</returns>
		[[nodiscard]] constexpr inline this_type CmpPerElementEqual(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_cmp_per_element_equal(data, rhs_.data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::cmpeq<per_element_width, is_signed>(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Returns another Vector of this type that acts as a mask indicating if respective elements in this Vector's registers and rhs_ are equal. </para>
		/// <para> In the returned mask, indices that returned true will have all bits set to 1; indices that returned false will have all bits set to 0. </para>
		/// </summary>
		/// <param name="rhs_">Register to compare all of this Vector's registers with, appearing on the right-hand side of comparison(s).</param>
		/// <returns>Vector of the same type representing a mask of comparison results.</returns>
		[[nodiscard]] constexpr inline this_type CmpPerElementEqual(register_arg_type rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_cmp_per_element_equal(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::cmpeq<per_element_width, is_signed>(data, rhs_));
			}
		}

		/// <summary>
		/// <para> Returns another Vector of this type that acts as a mask indicating if respective elements in this Vector are equal to the passed value. </para>
		/// <para> In the returned mask, indices that returned true will have all bits set to 1; indices that returned false will have all bits set to 0. </para>
		/// </summary>
		/// <param name="rhs_for_all_">Value to compare all of this Vector's elements with, appearing on the right-hand side of comparison.</param>
		/// <returns>Vector of the same type representing a mask of comparison results.</returns>
		[[nodiscard]] constexpr inline this_type CmpPerElementEqual(value_type rhs_for_all_) const
		{
			return CmpPerElementEqual(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para> Returns another Vector of this type that acts as a mask indicating if respective elements in this Vector and rhs_ are not equal. </para>
		/// <para> In the returned mask, indices that returned true will have all bits set to 1; indices that returned false will have all bits set to 0. </para>
		/// </summary>
		/// <param name="rhs_">Vector to compare this Vector with, appearing on the right-hand side of comparison.</param>
		/// <returns>Vector of the same type representing a mask of comparison results.</returns>
		[[nodiscard]] constexpr inline this_type CmpPerElementNotEqual(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_cmp_per_element_not_equal(data, rhs_.data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::cmpneq<per_element_width, is_signed>(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Returns another Vector of this type that acts as a mask indicating if respective elements in this Vector's registers and rhs_ are not equal. </para>
		/// <para> In the returned mask, indices that returned true will have all bits set to 1; indices that returned false will have all bits set to 0. </para>
		/// </summary>
		/// <param name="rhs_">Register to compare all of this Vector's registers with, appearing on the right-hand side of comparison(s).</param>
		/// <returns>Vector of the same type representing a mask of comparison results.</returns>
		[[nodiscard]] constexpr inline this_type CmpPerElementNotEqual(register_arg_type rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_cmp_per_element_not_equal(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::cmpneq<per_element_width, is_signed>(data, rhs_));
			}
		}

		/// <summary>
		/// <para> Returns another Vector of this type that acts as a mask indicating if respective elements in this Vector are not equal to the passed value. </para>
		/// <para> In the returned mask, indices that returned true will have all bits set to 1; indices that returned false will have all bits set to 0. </para>
		/// </summary>
		/// <param name="rhs_for_all_">Value to compare all of this Vector's elements with, appearing on the right-hand side of comparison.</param>
		/// <returns>Vector of the same type representing a mask of comparison results.</returns>
		[[nodiscard]] constexpr inline this_type CmpPerElementNotEqual(value_type rhs_for_all_) const
		{
			return CmpPerElementNotEqual(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para> Returns another Vector of this type that acts as a mask indicating if respective elements in this Vector and rhs_ are near-equal. </para>
		/// <para> In the returned mask, indices that returned true will have all bits set to 1; indices that returned false will have all bits set to 0. </para>
		/// <para> This is intended as a floating-point equality comparison function to avoid potentially inaccurate results due to floating-point rounding losses. </para>
		/// </summary>
		/// <param name="rhs_">Vector to compare this Vector with, appearing on the right-hand side of comparison.</param>
		/// <returns>Vector of the same type representing a mask of comparison results.</returns>
		[[nodiscard]] constexpr inline this_type CmpPerElementNear(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_cmp_per_element_near_equal(data, rhs_.data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::cmpnear<per_element_width, is_signed>(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Returns another Vector of this type that acts as a mask indicating if respective elements in this Vector's registers and rhs_ are near-equal. </para>
		/// <para> In the returned mask, indices that returned true will have all bits set to 1; indices that returned false will have all bits set to 0. </para>
		/// <para> This is intended as a floating-point equality comparison function to avoid potentially inaccurate results due to floating-point rounding losses. </para>
		/// </summary>
		/// <param name="rhs_">Register to compare all of this Vector's registers with, appearing on the right-hand side of comparison(s).</param>
		/// <returns>Vector of the same type representing a mask of comparison results.</returns>
		[[nodiscard]] constexpr inline this_type CmpPerElementNear(register_arg_type rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_cmp_per_element_not_equal(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::cmpnear<per_element_width, is_signed>(data, rhs_));
			}
		}

		/// <summary>
		/// <para> Returns another Vector of this type that acts as a mask indicating if respective elements in this Vector are near-equal to the passed value. </para>
		/// <para> In the returned mask, indices that returned true will have all bits set to 1; indices that returned false will have all bits set to 0. </para>
		/// <para> This is intended as a floating-point equality comparison function to avoid potentially inaccurate results due to floating-point rounding losses. </para>
		/// </summary>
		/// <param name="rhs_for_all_">Value to compare all of this Vector's elements with, appearing on the right-hand side of comparison.</param>
		/// <returns>Vector of the same type representing a mask of comparison results.</returns>
		[[nodiscard]] constexpr inline this_type CmpPerElementNear(value_type rhs_for_all_) const
		{
			return CmpPerElementNear(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para> Returns another Vector of this type that acts as a mask indicating if respective elements in this Vector are near-equal to rhs_, based on epsilon_. </para>
		/// <para> In the returned mask, indices that returned true will have all bits set to 1; indices that returned false will have all bits set to 0. </para>
		/// <para> This is intended as a floating-point equality comparison function to avoid potentially inaccurate results due to floating-point rounding losses. </para>
		/// </summary>
		/// <param name="rhs_">Vector, register, or value to compare this Vector with, appearing on the right-hand side of comparison.</param>
		/// <param name="epsilon_">Vector, register, or value to use as the epsilon to determine the valid "near" range for comparisons.</param>
		/// <returns>
		///		Vector of the same type representing a mask of comparison results, 
		///		where true results are where this Vector's respective values are within the inclusive range of epsilon_ to reach rhs_.
		/// </returns>
		[[nodiscard]] constexpr inline this_type CmpPerElementNear(const this_type& rhs_, const this_type& epsilon_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_cmp_per_element_near_equal(data, rhs_.data, epsilon_.data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::cmpnear<per_element_width, is_signed>(data, rhs_.data, epsilon_));
			}
		}

		[[nodiscard]] constexpr inline this_type CmpPerElementNear(const this_type& rhs_, register_arg_type epsilon_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_cmp_per_element_near_equal(data, rhs_.data, epsilon_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::cmpnear<per_element_width, is_signed>(data, rhs_.data, epsilon_));
			}
		}

		[[nodiscard]] constexpr inline this_type CmpPerElementNear(register_arg_type rhs_, const this_type& epsilon_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_cmp_per_element_near_equal(data, rhs_, epsilon_.data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::cmpnear<per_element_width, is_signed>(data, rhs_, epsilon_.data));
			}
		}

		[[nodiscard]] constexpr inline this_type CmpPerElementNear(register_arg_type rhs_, register_arg_type epsilon_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_cmp_per_element_near_equal(data, rhs_, epsilon_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::cmpnear<per_element_width, is_signed>(data, rhs_, epsilon_));
			}
		}

		[[nodiscard]] constexpr inline this_type CmpPerElementNear(const this_type& rhs_, value_type epsilon_) const
		{
			return CmpPerElementNear(rhs_, EmuSIMD::set1<register_type, per_element_width>(epsilon_));
		}

		[[nodiscard]] constexpr inline this_type CmpPerElementNear(register_arg_type rhs_, value_type epsilon_) const
		{
			return CmpPerElementNear(rhs_, EmuSIMD::set1<register_type, per_element_width>(epsilon_));
		}

		[[nodiscard]] constexpr inline this_type CmpPerElementNear(value_type rhs_, const this_type& epsilon_) const
		{
			return CmpPerElementNear(EmuSIMD::set1<register_type, per_element_width>(rhs_), epsilon_);
		}

		[[nodiscard]] constexpr inline this_type CmpPerElementNear(value_type rhs_, register_arg_type epsilon_) const
		{
			return CmpPerElementNear(EmuSIMD::set1<register_type, per_element_width>(rhs_), epsilon_);
		}

		[[nodiscard]] constexpr inline this_type CmpPerElementNear(value_type rhs_, value_type epsilon_) const
		{
			return CmpPerElementNear(EmuSIMD::set1<register_type, per_element_width>(rhs_), EmuSIMD::set1<register_type, per_element_width>(epsilon_));
		}

		/// <summary>
		/// <para> Returns another Vector of this type that acts as a mask indicating if respective elements in this Vector are greater than those of rhs_. </para>
		/// <para> In the returned mask, indices that returned true will have all bits set to 1; indices that returned false will have all bits set to 0. </para>
		/// </summary>
		/// <param name="rhs_">Vector to compare this Vector with, appearing on the right-hand side of comparison.</param>
		/// <returns>Vector of the same type representing a mask of comparison results.</returns>
		[[nodiscard]] constexpr inline this_type CmpPerElementGreater(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_cmp_per_element_greater(data, rhs_.data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::cmpgt<per_element_width, is_signed>(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Returns another Vector of this type that acts as a mask indicating if respective elements in this Vector's registers are greater than those of rhs_. </para>
		/// <para> In the returned mask, indices that returned true will have all bits set to 1; indices that returned false will have all bits set to 0. </para>
		/// </summary>
		/// <param name="rhs_">Register to compare all of this Vector's registers with, appearing on the right-hand side of comparison(s).</param>
		/// <returns>Vector of the same type representing a mask of comparison results.</returns>
		[[nodiscard]] constexpr inline this_type CmpPerElementGreater(register_arg_type rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_cmp_per_element_greater(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::cmpgt<per_element_width, is_signed>(data, rhs_));
			}
		}

		/// <summary>
		/// <para> Returns another Vector of this type that acts as a mask indicating if respective elements in this Vector are greater than the passed value. </para>
		/// <para> In the returned mask, indices that returned true will have all bits set to 1; indices that returned false will have all bits set to 0. </para>
		/// </summary>
		/// <param name="rhs_for_all_">Value to compare all of this Vector's elements with, appearing on the right-hand side of comparison.</param>
		/// <returns>Vector of the same type representing a mask of comparison results.</returns>
		[[nodiscard]] constexpr inline this_type CmpPerElementGreater(value_type rhs_for_all_) const
		{
			return CmpPerElementGreater(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para> Returns another Vector of this type that acts as a mask indicating if respective elements in this Vector are less than those of rhs_. </para>
		/// <para> In the returned mask, indices that returned true will have all bits set to 1; indices that returned false will have all bits set to 0. </para>
		/// </summary>
		/// <param name="rhs_">Vector to compare this Vector with, appearing on the right-hand side of comparison.</param>
		/// <returns>Vector of the same type representing a mask of comparison results.</returns>
		[[nodiscard]] constexpr inline this_type CmpPerElementLess(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_cmp_per_element_less(data, rhs_.data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::cmplt<per_element_width, is_signed>(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Returns another Vector of this type that acts as a mask indicating if respective elements in this Vector's registers are less than those of rhs_. </para>
		/// <para> In the returned mask, indices that returned true will have all bits set to 1; indices that returned false will have all bits set to 0. </para>
		/// </summary>
		/// <param name="rhs_">Register to compare all of this Vector's registers with, appearing on the right-hand side of comparison(s).</param>
		/// <returns>Vector of the same type representing a mask of comparison results.</returns>
		[[nodiscard]] constexpr inline this_type CmpPerElementLess(register_arg_type rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_cmp_per_element_less(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::cmplt<per_element_width, is_signed>(data, rhs_));
			}
		}

		/// <summary>
		/// <para> Returns another Vector of this type that acts as a mask indicating if respective elements in this Vector are less than the passed value. </para>
		/// <para> In the returned mask, indices that returned true will have all bits set to 1; indices that returned false will have all bits set to 0. </para>
		/// </summary>
		/// <param name="rhs_for_all_">Value to compare all of this Vector's elements with, appearing on the right-hand side of comparison.</param>
		/// <returns>Vector of the same type representing a mask of comparison results.</returns>
		[[nodiscard]] constexpr inline this_type CmpPerElementLess(value_type rhs_for_all_) const
		{
			return CmpPerElementLess(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para> Returns another Vector of this type that acts as a mask indicating if respective elements in this Vector are greater than or equal to those of rhs_. </para>
		/// <para> In the returned mask, indices that returned true will have all bits set to 1; indices that returned false will have all bits set to 0. </para>
		/// </summary>
		/// <param name="rhs_">Vector to compare this Vector with, appearing on the right-hand side of comparison.</param>
		/// <returns>Vector of the same type representing a mask of comparison results.</returns>
		[[nodiscard]] constexpr inline this_type CmpPerElementGreaterEqual(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_cmp_per_element_greater_equal(data, rhs_.data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::cmpge<per_element_width, is_signed>(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Returns another Vector of this type that acts as a mask indicating if respective elements in this Vector's registers are greater than or equal to those of rhs_. </para>
		/// <para> In the returned mask, indices that returned true will have all bits set to 1; indices that returned false will have all bits set to 0. </para>
		/// </summary>
		/// <param name="rhs_">Register to compare all of this Vector's registers with, appearing on the right-hand side of comparison(s).</param>
		/// <returns>Vector of the same type representing a mask of comparison results.</returns>
		[[nodiscard]] constexpr inline this_type CmpPerElementGreaterEqual(register_arg_type rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_cmp_per_element_greater_equal(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::cmpge<per_element_width, is_signed>(data, rhs_));
			}
		}

		/// <summary>
		/// <para> Returns another Vector of this type that acts as a mask indicating if respective elements in this Vector are greater than or equal to the passed value. </para>
		/// <para> In the returned mask, indices that returned true will have all bits set to 1; indices that returned false will have all bits set to 0. </para>
		/// </summary>
		/// <param name="rhs_for_all_">Value to compare all of this Vector's elements with, appearing on the right-hand side of comparison.</param>
		/// <returns>Vector of the same type representing a mask of comparison results.</returns>
		[[nodiscard]] constexpr inline this_type CmpPerElementGreaterEqual(value_type rhs_for_all_) const
		{
			return CmpPerElementGreaterEqual(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}

		/// <summary>
		/// <para> Returns another Vector of this type that acts as a mask indicating if respective elements in this Vector are less than or equal to those of rhs_. </para>
		/// <para> In the returned mask, indices that returned true will have all bits set to 1; indices that returned false will have all bits set to 0. </para>
		/// </summary>
		/// <param name="rhs_">Vector to compare this Vector with, appearing on the right-hand side of comparison.</param>
		/// <returns>Vector of the same type representing a mask of comparison results.</returns>
		[[nodiscard]] constexpr inline this_type CmpPerElementLessEqual(const this_type& rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_cmp_per_element_less_equal(data, rhs_.data, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::cmple<per_element_width, is_signed>(data, rhs_.data));
			}
		}

		/// <summary>
		/// <para> Returns another Vector of this type that acts as a mask indicating if respective elements in this Vector's registers are less than or equal to those of rhs_. </para>
		/// <para> In the returned mask, indices that returned true will have all bits set to 1; indices that returned false will have all bits set to 0. </para>
		/// </summary>
		/// <param name="rhs_">Register to compare all of this Vector's registers with, appearing on the right-hand side of comparison(s).</param>
		/// <returns>Vector of the same type representing a mask of comparison results.</returns>
		[[nodiscard]] constexpr inline this_type CmpPerElementLessEqual(register_arg_type rhs_) const
		{
			if constexpr (contains_multiple_registers)
			{
				return this_type(_do_array_cmp_per_element_less_equal(data, rhs_, register_index_sequence()));
			}
			else
			{
				return this_type(EmuSIMD::cmple<per_element_width, is_signed>(data, rhs_));
			}
		}

		/// <summary>
		/// <para> Returns another Vector of this type that acts as a mask indicating if respective elements in this Vector are less than or equal to the passed value. </para>
		/// <para> In the returned mask, indices that returned true will have all bits set to 1; indices that returned false will have all bits set to 0. </para>
		/// </summary>
		/// <param name="rhs_for_all_">Value to compare all of this Vector's elements with, appearing on the right-hand side of comparison.</param>
		/// <returns>Vector of the same type representing a mask of comparison results.</returns>
		[[nodiscard]] constexpr inline this_type CmpPerElementLessEqual(value_type rhs_for_all_) const
		{
			return CmpPerElementLessEqual(EmuSIMD::set1<register_type, per_element_width>(rhs_for_all_));
		}
#pragma endregion

#pragma region COMPARISONS_ADAPTIVE
	public:
		/// <summary>
		/// <para> Adaptive equality check. </para>
		/// <para> If the passed argument is of this FastVector type or its register_arg_type: Identical to CmpAllEqual. </para>
		/// <para> If the passed argument is of this FastVector's value_type: Identical to MagnitudeScalar() == arg. </para>
		/// </summary>
		[[nodiscard]] constexpr inline bool CmpEqual(const this_type& rhs_) const
		{
			return _do_cmp_equal_bool_out<true>(data, rhs_.data);
		}

		[[nodiscard]] constexpr inline bool CmpEqual(register_arg_type rhs_) const
		{
			return _do_cmp_equal_bool_out<true>(data, rhs_);
		}

		[[nodiscard]] constexpr inline bool CmpEqual(value_type rhs_magnitude_) const
		{
			return MagnitudeScalar<value_type>() == rhs_magnitude_;
		}

		/// <summary>
		/// <para> Adaptive inequality check. </para>
		/// <para> If the passed argument is of this FastVector type or its register_arg_type: Identical to CmpAnyNotEqual. </para>
		/// <para> If the passed argument is of this FastVector's value_type: Identical to MagnitudeScalar() != arg. </para>
		/// </summary>
		[[nodiscard]] constexpr inline bool CmpNotEqual(const this_type& rhs_) const
		{
			return _do_cmp_not_equal_bool_out<false>(data, rhs_.data);
		}

		[[nodiscard]] constexpr inline bool CmpNotEqual(register_arg_type rhs_) const
		{
			return _do_cmp_not_equal_bool_out<false>(data, rhs_);
		}

		[[nodiscard]] constexpr inline bool CmpNotEqual(value_type rhs_magnitude_) const
		{
			return MagnitudeScalar<value_type>() != rhs_magnitude_;
		}

		/// <summary>
		/// <para> Adaptive near-equality check. </para>
		/// <para> If the passed argument is of this FastVector type or its register_arg_type: Identical to CmpAllNear. </para>
		/// <para> 
		///		If the passed argument is of this FastVector's value_type: 
		///		Identical to EmuCore::do_near&lt;value_type, value_type, value_type&gt;()(MagnitudeScalar(), first_arg, [epsilon]). </para>
		/// <para>
		///		May optionally provide a custom epsilon for determining if values are near-equal. 
		///		If the first argument is this FastVector's value_type, the type of the passed epsilon may only be a value_type.
		/// </para>
		/// </summary>
		[[nodiscard]] constexpr inline bool CmpNear(const this_type& rhs_) const
		{
			return _do_cmp_near_equal_bool_out<true>(data, rhs_.data);
		}

		[[nodiscard]] constexpr inline bool CmpNear(register_arg_type rhs_) const
		{
			return _do_cmp_near_equal_bool_out<true>(data, rhs_);
		}

		[[nodiscard]] constexpr inline bool CmpNear(const this_type& rhs_, const this_type& epsilon_) const
		{
			return _do_cmp_near_equal_bool_out<true>(data, rhs_.data, epsilon_.data);
		}

		[[nodiscard]] constexpr inline bool CmpNear(const this_type& rhs_, register_arg_type epsilon_) const
		{
			return _do_cmp_near_equal_bool_out<true>(data, rhs_.data, epsilon_.data);
		}

		[[nodiscard]] constexpr inline bool CmpNear(const this_type& rhs_, value_type epsilon_) const
		{
			return _do_cmp_near_equal_bool_out<true>(data, rhs_.data, EmuSIMD::set1<per_element_width>(epsilon_));
		}

		[[nodiscard]] constexpr inline bool CmpNear(register_arg_type rhs_, const this_type& epsilon_) const
		{
			return _do_cmp_near_equal_bool_out<true>(data, rhs_, epsilon_.data);
		}

		[[nodiscard]] constexpr inline bool CmpNear(register_arg_type rhs_, register_arg_type epsilon_) const
		{
			return _do_cmp_near_equal_bool_out<true>(data, rhs_, epsilon_.data);
		}

		[[nodiscard]] constexpr inline bool CmpNear(register_arg_type rhs_, value_type epsilon_) const
		{
			return _do_cmp_near_equal_bool_out<true>(data, rhs_, EmuSIMD::set1<per_element_width>(epsilon_));
		}

		[[nodiscard]] constexpr inline bool CmpNear(value_type rhs_magnitude_) const
		{
			return EmuCore::do_cmp_near_equal<value_type, value_type, value_type>()(MagnitudeScalar<value_type>(), rhs_magnitude_);
		}

		[[nodiscard]] constexpr inline bool CmpNear(value_type rhs_magnitude_, value_type epsilon_) const
		{
			return EmuCore::do_cmp_near_equal<value_type, value_type, value_type>()(MagnitudeScalar<value_type>(), rhs_magnitude_, epsilon_);
		}

		/// <summary>
		/// <para> Adaptive greater-than magnitude comparison. </para>
		/// <para> If the passed argument is of this FastVector type: Identical to MagnitudeScalar() &gt; arg.MagnitudeScalar(). </para>
		/// <para> If the passed argument is of this FastVector type: Identical to MagnitudeScalar() &gt; arg. </para>
		/// </summary>
		[[nodiscard]] constexpr inline bool CmpGreater(const this_type& rhs_) const
		{
			return MagnitudeScalar<value_type>() > rhs_.MagnitudeScalar<value_type>();
		}

		[[nodiscard]] constexpr inline bool CmpGreater(value_type rhs_magnitude_) const
		{
			return MagnitudeScalar<value_type>() > rhs_magnitude_;
		}

		/// <summary>
		/// <para> Adaptive less-than magnitude comparison. </para>
		/// <para> If the passed argument is of this FastVector type: Identical to MagnitudeScalar() &lt; arg.MagnitudeScalar(). </para>
		/// <para> If the passed argument is of this FastVector type: Identical to MagnitudeScalar() &lt; arg. </para>
		/// </summary>
		[[nodiscard]] constexpr inline bool CmpLess(const this_type& rhs_) const
		{
			return MagnitudeScalar<value_type>() < rhs_.MagnitudeScalar<value_type>();
		}

		[[nodiscard]] constexpr inline bool CmpLess(value_type rhs_magnitude_) const
		{
			return MagnitudeScalar<value_type>() < rhs_magnitude_;
		}

		/// <summary>
		/// <para> Adaptive greater-equal magnitude comparison. </para>
		/// <para> If the passed argument is of this FastVector type: Identical to MagnitudeScalar() &gt;= arg.MagnitudeScalar(). </para>
		/// <para> If the passed argument is of this FastVector type: Identical to MagnitudeScalar() &gt;= arg. </para>
		/// </summary>
		[[nodiscard]] constexpr inline bool CmpGreaterEqual(const this_type& rhs_) const
		{
			return MagnitudeScalar<value_type>() >= rhs_.MagnitudeScalar<value_type>();
		}

		[[nodiscard]] constexpr inline bool CmpGreaterEqual(value_type rhs_magnitude_) const
		{
			return MagnitudeScalar<value_type>() >= rhs_magnitude_;
		}

		/// <summary>
		/// <para> Adaptive less-equal magnitude comparison. </para>
		/// <para> If the passed argument is of this FastVector type: Identical to MagnitudeScalar() &lt;= arg.MagnitudeScalar(). </para>
		/// <para> If the passed argument is of this FastVector type: Identical to MagnitudeScalar() &lt;= arg. </para>
		/// </summary>
		[[nodiscard]] constexpr inline bool CmpLessEqual(const this_type& rhs_) const
		{
			return MagnitudeScalar<value_type>() <= rhs_.MagnitudeScalar<value_type>();
		}

		[[nodiscard]] constexpr inline bool CmpLessEqual(value_type rhs_magnitude_) const
		{
			return MagnitudeScalar<value_type>() <= rhs_magnitude_;
		}
#pragma endregion

#pragma region CASTS
	public:
		/// <summary>
		/// <para> Converts this Vector to a different kind of FastVector. </para>
		/// <para> The output Vector will be of the provided OutSize_, OutT_, and OutRegisterWidth_. </para>
		/// <para> OutSize_ may be omitted if OutT_ is provided, and defaults to this Vector's size. </para>
		/// <para> OutT_ may be omitted if OutSize_ is provided, and defaults to this Vector's size. </para>
		/// <para> OutRegisterWidth_ may always be omitted, but must be provided after OutT_ if not omitted. It defaults to this Vector's register_width. </para>
		/// <para> Non-encapsulated values may also be converted if a vectorwise conversion is possible, as a result of using only SIMD operations for such conversions. </para>
		/// </summary>
		/// <returns>New FastVector of the provided output type resulting from a conversion of this FastVector.</returns>
		template<std::size_t OutSize_, typename OutT_ = value_type, std::size_t OutRegisterWidth_ = register_width>
		[[nodiscard]] constexpr inline EmuMath::FastVector<OutSize_, OutT_, OutRegisterWidth_> Convert() const
		{
			using out_vector = EmuMath::FastVector<OutSize_, OutT_, OutRegisterWidth_>;
			constexpr bool matching_element_width = out_vector::per_element_width == per_element_width;
			constexpr bool matching_register = std::is_same_v<typename out_vector::register_type, register_type>;
			constexpr bool same_element_type = std::is_same_v<value_type, typename out_vector::value_type>;

			if constexpr (matching_element_width && matching_register&& same_element_type)
			{
				return _do_conversion_matching_element_type_and_register<out_vector>(data);
			}
			else
			{
				constexpr bool matching_count_per_register = elements_per_register == out_vector::elements_per_register;
				if constexpr (matching_count_per_register)
				{
					// We can safely trivialise this as conversions as each register is 1:1.
					return _do_conversion_all_widths_equal<out_vector>(data, std::make_index_sequence<out_vector::num_registers>());
				}
				else
				{
					// NOTE: This *can* be optimised a bit more to do vectorwise conversions in some cases other than above, 
					//       but isn't much of a priority right now due to complexity
					return _do_basic_store_and_load_conversion<out_vector>(std::make_index_sequence<OutSize_>());
				}
			}
		}

		template<typename OutT_, std::size_t OutRegisterWidth_ = register_width>
		[[nodiscard]] constexpr inline EmuMath::FastVector<size, OutT_, OutRegisterWidth_> Convert() const
		{
			return Convert<size, OutT_, OutRegisterWidth_>();
		}
#pragma endregion

#pragma region VECTOR_DATA
	public:
		/// <summary>
		/// <para> Underlying SIMD component of this Vector. </para>
		/// <para> If this Vector requires only 1 register, this will be that register. </para>
		/// <para> If this Vector requires multiple registers, this will be an array of registers. </para>
		/// <para> It is recommended to avoid using this unless you know what you are doing. </para>
		/// <para> For a generic approach to accessing this, consider GetRegister() or GetRegisterTheoretical(). </para>
		/// </summary>
		data_type data;
#pragma endregion

		// SIGNIFICANT PORTION OF UNDERLYING IMPLEMENTATION STARTS HERE
#pragma region GENERAL_HELPERS
	private:
		template<std::size_t FullWidthIndex_, typename Vector_>
		[[nodiscard]] static constexpr inline typename _vector_get_index_for_load_result<FullWidthIndex_, Vector_>::type _get_index_from_normal_vector(Vector_&& arg_)
		{
			using vector_uq = typename EmuCore::TMP::remove_ref_cv<Vector_>::type;
			if constexpr (FullWidthIndex_ > vector_uq::size || std::is_lvalue_reference_v<Vector_>)
			{
				return arg_.AtTheoretical<FullWidthIndex_>();
			}
			else
			{
				return std::move(arg_.AtTheoretical<FullWidthIndex_>());
			}
		}

		template<std::size_t Index_, typename Arg_>
		[[nodiscard]] static constexpr inline const register_type& _retrieve_register_from_arg(Arg_&& arg_)
		{
			using arg_uq = typename EmuCore::TMP::remove_ref_cv<Arg_>::type;
			if constexpr (std::is_same_v<this_type, arg_uq>)
			{
				return arg_.data[Index_];
			}
			else if constexpr (std::is_same_v<register_type, arg_uq>)
			{
				return arg_;
			}
			else if constexpr (std::is_same_v<data_type, arg_uq>)
			{
				return arg_[Index_];
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Arg_>(),
					"Unable to retrieve a register argument from a provided argument for interacting with an EmuMath::FastVector."
				);
			}
		}

		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline register_type _generic_fill_from_register_index(register_arg_type register_)
		{
			if constexpr (elements_per_register == 2)
			{
				return EmuSIMD::shuffle<Index_, Index_>(register_);
			}
			else if constexpr (elements_per_register == 4)
			{
				return EmuSIMD::shuffle<Index_, Index_, Index_, Index_>(register_);
			}
			else if constexpr (elements_per_register == 8)
			{
				return EmuSIMD::shuffle<Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_>(register_);
			}
			else if constexpr (elements_per_register == 16)
			{
				return EmuSIMD::shuffle<Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_>(register_);
			}
			else if constexpr (elements_per_register == 32)
			{
				return EmuSIMD::shuffle
				<
					Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_,
					Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_
				>(register_);
			}
			else if constexpr (elements_per_register == 64)
			{
				return EmuSIMD::shuffle
				<
					Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_,
					Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_,
					Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_,
					Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_
				>(register_);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<this_type>(),
					"Unable to perform a generic register-fill operation from an existing register on an EmuMath::FastVector instance as it cannot be reliably shuffled due to its elements_per_register size."
				);
			}
		}
#pragma endregion

#pragma region EXTRACTION_HELPERS
	private:
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
#pragma endregion

#pragma region COPY_CONSTRUCTION_HELPERS
	private:
		template<std::size_t...Indices_>
		static constexpr inline data_type _make_array_copy(const this_type& to_copy_, std::index_sequence<Indices_...> indices_) noexcept
		{
			return data_type({ register_type(to_copy_.data[Indices_])... });
		}

		static constexpr inline data_type _make_copy(const this_type& to_copy_) noexcept
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
#pragma endregion

#pragma region MOVE_CONSTRUCTION_HELPERS
	private:
		template<std::size_t...Indices_>
		static constexpr inline data_type _do_array_move(this_type&& to_move_, std::index_sequence<Indices_...> indices_) noexcept
		{
			return data_type({ register_type(std::move(to_move_.data[Indices_]))... });
		}

		static constexpr inline data_type _do_move(this_type&& to_move_) noexcept
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
#pragma endregion

#pragma region ALL_SAME_CONSTRUCTION_HELPERS
	private:
		template<std::size_t ToDiscard_>
		static constexpr inline register_type _set_all_same_discard_index(const value_type& to_set_all_to_) noexcept
		{
			return EmuSIMD::set1<register_type, per_element_width>(to_set_all_to_);
		}

		template<std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_set_all_same(const value_type& to_set_all_to_, std::index_sequence<RegisterIndices_...> indices_) noexcept
		{
			return data_type({ _set_all_same_discard_index<RegisterIndices_>(to_set_all_to_)... });
		}

		static constexpr inline data_type _do_set_all_same(const value_type& to_set_all_to_) noexcept
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

		template<std::size_t Index_, typename Arg_>
		static constexpr inline register_type _construct_register_discard_index(Arg_&& arg_) noexcept
		{
			return register_type(std::forward<Arg_>(arg_));
		}

		template<std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_set_all_same_register(register_type to_set_all_registers_to_, std::index_sequence<RegisterIndices_...> indices_) noexcept
		{
			return data_type({ _construct_register_discard_index<RegisterIndices_>(to_set_all_registers_to_)... });
		}

		static constexpr inline data_type _do_set_all_same_register(register_type to_set_all_registers_to_) noexcept
		{
			if constexpr (contains_multiple_registers)
			{
				return _do_array_set_all_same_register(to_set_all_registers_to_, register_index_sequence());
			}
			else
			{
				return to_set_all_registers_to_;
			}
		}
#pragma endregion

#pragma region LOAD_CONSTRUCTION_HELPERS
	private:
		template<std::size_t RegisterIndex_>
		static constexpr inline register_type _do_load_for_register_index(const value_type* p_to_load_)
		{
			constexpr std::size_t offset = RegisterIndex_ * elements_per_register;
			return EmuSIMD::load<register_type>(p_to_load_ + offset);
		}

		template<std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_load(const value_type* p_to_load_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type({ _do_load_for_register_index<RegisterIndices_>(p_to_load_)... });
		}

		static constexpr inline data_type _do_load(const value_type* p_to_load_)
		{
			if constexpr (contains_multiple_registers)
			{
				return _do_array_load(p_to_load_, register_index_sequence());
			}
			else
			{
				return EmuSIMD::load<register_type>(p_to_load_);
			}
		}
#pragma endregion

#pragma region VARIADIC_CONSTRUCTION_HELPERS
	private:
		template<typename...Args_>
		static constexpr inline data_type _do_variadic_construction(Args_&&...args_)
		{
			constexpr std::size_t num_args = sizeof...(Args_);
			using first_arg = typename std::conditional<num_args != 0, typename EmuCore::TMP::first_variadic_arg<Args_...>::type, void>::type;
			if constexpr (num_args == 1 && valid_arg_for_normal_vector_conversion_construction<first_arg>())
			{
				return _make_as_normal_vector_conversion(std::forward<Args_>(args_)...);
			}
			else if constexpr (valid_args_for_per_register_construction<Args_...>())
			{
				return _make_with_arg_per_register(std::forward<Args_>(args_)...);
			}
			else if constexpr (valid_args_for_per_element_construction<Args_...>())
			{
				return _make_with_arg_per_element(std::forward<Args_>(args_)...);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Args_...>(),
					"False-positive allowed for variadic construction of an EmuMath::FastVector; no variadic construction method is available."
				);
			}
		}

		template<class Vector_, std::size_t...FullWidthIndices_>
		static constexpr inline register_type _make_register_from_normal_vector(Vector_&& vector_, std::index_sequence<FullWidthIndices_...> indices_)
		{
			using vector_uq = typename EmuCore::TMP::remove_ref_cv<Vector_>::type;
			using vector_stored_uq = typename std::remove_cv<typename vector_uq::stored_type>::type;
			constexpr std::size_t num_indices = sizeof...(FullWidthIndices_);
			constexpr bool all_indices_in_range = (... && (FullWidthIndices_ < vector_uq::size));
			if constexpr (all_indices_in_range && std::is_same_v<value_type, vector_stored_uq>)
			{
				constexpr std::size_t first_index = EmuCore::TMP::first_variadic_value_v<FullWidthIndices_...>;
				return EmuSIMD::load<register_type>(vector_.data<first_index>());
			}
			else
			{
				return EmuSIMD::setr<register_type, per_element_byte_size>(_get_index_from_normal_vector<FullWidthIndices_>(std::forward<Vector_>(vector_))...);
			}
		}

		template<class Vector_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _make_array_as_normal_vector_conversion(Vector_&& vector_, std::index_sequence<RegisterIndices_...> register_indices_)
		{
			return data_type
			({ 
				_make_register_from_normal_vector
				(
					std::forward<Vector_>(vector_),
					EmuCore::TMP::make_offset_index_sequence<RegisterIndices_ * elements_per_register, elements_per_register>()
				)...
			});
		}

		template<class Vector_>
		static constexpr inline data_type _make_as_normal_vector_conversion(Vector_&& vector_)
		{
			if constexpr (contains_multiple_registers)
			{
				return _make_array_as_normal_vector_conversion(std::forward<Vector_>(vector_), register_index_sequence());
			}
			else
			{
				return _make_register_from_normal_vector(std::forward<Vector_>(vector_), full_width_index_sequence());
			}
		}

		template<typename...Args_>
		static constexpr inline data_type _make_with_arg_per_register(Args_&&...args_) noexcept
		{
			if constexpr (contains_multiple_registers)
			{
				return data_type({ register_type(std::forward<Args_>(args_))... });
			}
			else
			{
				// Realistically this shouldn't be called since the explicitly-typed constructor will cover it, but here as a safe fallback
				return data_type(std::forward<Args_>(args_)...);
			}
		}

		template<typename...Args_>
		static constexpr inline data_type _make_with_arg_per_element(Args_&&...args_) noexcept
		{
			if constexpr (contains_multiple_registers || requires_partial_register)
			{
				auto args_tuple = std::forward_as_tuple<Args_...>(std::forward<Args_>(args_)...);
				return _make_all_registers_from_tuple(args_tuple, register_index_sequence());
			}
			else
			{
				return EmuSIMD::setr<register_type, per_element_width>(std::forward<Args_>(args_)...);
			}
		}

		template<std::size_t Index_, typename...Args_>
		static constexpr inline value_type _make_value_type_from_tuple_index(std::tuple<Args_...>& args_) noexcept
		{
			if constexpr (Index_ < sizeof...(Args_))
			{
				using tuple_type = std::tuple<Args_...>;
				using arg_type = typename std::tuple_element<Index_, tuple_type>;
				return static_cast<value_type>(std::get<Index_>(args_));
			}
			else
			{
				return value_type();
			}
		}

		template<std::size_t...Indices, typename...Args_>
		static constexpr inline register_type _make_register_from_tuple(std::tuple<Args_...>& args_, std::index_sequence<Indices...> indices_) noexcept
		{
			return EmuSIMD::setr<register_type, per_element_width>(_make_value_type_from_tuple_index<Indices>(args_)...);
		}

		template<std::size_t...RegisterIndices_, typename...Args_>
		static constexpr inline data_type _make_all_registers_from_tuple(std::tuple<Args_...>& args_, std::index_sequence<RegisterIndices_...> indices_) noexcept
		{
			if constexpr (sizeof...(RegisterIndices_) == 1)
			{
				return data_type(_make_register_from_tuple(args_, EmuCore::TMP::make_offset_index_sequence<RegisterIndices_ * elements_per_register, elements_per_register>())...);
			}
			else
			{
				return data_type
				(
					{ _make_register_from_tuple(args_, EmuCore::TMP::make_offset_index_sequence<RegisterIndices_ * elements_per_register, elements_per_register>())... }
				);
			}
		}
#pragma endregion

#pragma region CONST_BASIC_ARITHMETIC_HELPERS
	private:
		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_add(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			using rhs_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
			return data_type
			({
				EmuSIMD::add<per_element_width>(lhs_[RegisterIndices_], _retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_)))...
			});
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_subtract(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			using rhs_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
			return data_type
			({
				EmuSIMD::sub<per_element_width>(lhs_[RegisterIndices_], _retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_)))...
			});
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_multiply(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			using rhs_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
			return data_type
			({
				EmuSIMD::mul_all<per_element_width>(lhs_[RegisterIndices_], _retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_)))...
			});
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_divide(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			using rhs_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
			return data_type
			({
				EmuSIMD::div<per_element_width, is_signed>(lhs_[RegisterIndices_], _retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_)))...
			});
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_mod(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			using rhs_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
			return data_type
			({
				EmuSIMD::mod<per_element_width, is_signed>(lhs_[RegisterIndices_], _retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_)))...
			});
		}

		template<std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_negate(const data_type& lhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type({ EmuSIMD::negate<per_element_width>(lhs_[RegisterIndices_])... });
		}

		template<class Mul_, class Add_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_fmadd(const data_type& a_, Mul_&& mul_, Add_&& add_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type
			({
				EmuSIMD::fmadd<per_element_width>
				(
					a_[RegisterIndices_],
					_retrieve_register_from_arg<RegisterIndices_>(std::forward<Mul_>(mul_)),
					_retrieve_register_from_arg<RegisterIndices_>(std::forward<Add_>(add_))
				)...
			});
		}

		template<class Mul_, class Sub_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_fmsub(const data_type& a_, Mul_&& mul_, Sub_&& sub_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type
			({
				EmuSIMD::fmsub<per_element_width>
				(
					a_[RegisterIndices_],
					_retrieve_register_from_arg<RegisterIndices_>(std::forward<Mul_>(mul_)),
					_retrieve_register_from_arg<RegisterIndices_>(std::forward<Sub_>(sub_))
				)...
			});
		}
#pragma endregion

#pragma region CONST_MISC_ARITHMETIC_HELPERS
	private:
		template<bool Inverse_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_sqrt(const data_type& in_, std::index_sequence<RegisterIndices_...> indices_)
		{
			if constexpr (Inverse_)
			{
				return data_type({ EmuSIMD::rsqrt<per_element_width, is_signed>(in_[RegisterIndices_])... });
			}
			else
			{
				return data_type({ EmuSIMD::sqrt<per_element_width, is_signed>(in_[RegisterIndices_])... });
			}
		}

		template<std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_floor(const data_type& in_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type({ EmuSIMD::floor(in_[RegisterIndices_])... });
		}

		template<std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_ceil(const data_type& in_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type({ EmuSIMD::ceil(in_[RegisterIndices_])... });
		}

		template<std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_trunc(const data_type& in_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type({ EmuSIMD::trunc(in_[RegisterIndices_])... });
		}

		template<std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_abs(const data_type& in_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type({ EmuSIMD::abs<per_element_width, is_signed>(in_[RegisterIndices_])... });
		}

		template<class Min_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_clamp_min(const data_type& a_, Min_&& min_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type
			({
				EmuSIMD::clamp_min<per_element_width, is_signed>
				(
					a_[RegisterIndices_],
					_retrieve_register_from_arg<RegisterIndices_>(std::forward<Min_>(min_))
				)...
			});
		}

		template<class Max_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_clamp_max(const data_type& a_, Max_&& max_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type
			({
				EmuSIMD::clamp_max<per_element_width, is_signed>
				(
					a_[RegisterIndices_],
					_retrieve_register_from_arg<RegisterIndices_>(std::forward<Max_>(max_))
				)...
			});
		}

		template<class Min_, class Max_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_clamp(const data_type& a_, Min_&& min_, Max_&& max_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type
			({
				EmuSIMD::clamp<per_element_width, is_signed>
				(
					a_[RegisterIndices_],
					_retrieve_register_from_arg<RegisterIndices_>(std::forward<Min_>(min_)),
					_retrieve_register_from_arg<RegisterIndices_>(std::forward<Max_>(max_))
				)...
			});
		}
#pragma endregion

#pragma region NON_CONST_BASIC_ARITHMETIC_HELPERS
	private:
		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline void _do_array_add_assign(data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			(
				(
					lhs_[RegisterIndices_] = EmuSIMD::add<per_element_width>
					(
						lhs_[RegisterIndices_],
						_retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_))
					)
				), ...
			);
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline void _do_array_subtract_assign(data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			(
				(
					lhs_[RegisterIndices_] = EmuSIMD::sub<per_element_width>
					(
						lhs_[RegisterIndices_],
						_retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_))
					)
				), ...
			);
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline void _do_array_multiply_assign(data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			(
				(
					lhs_[RegisterIndices_] = EmuSIMD::mul_all<per_element_width>
					(
						lhs_[RegisterIndices_],
						_retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_))
					)
				), ...
			);
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline void _do_array_divide_assign(data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			(
				(
					lhs_[RegisterIndices_] = EmuSIMD::div<per_element_width, is_signed>
					(
						lhs_[RegisterIndices_],
						_retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_))
					)
				), ...
			);
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline void _do_array_mod_assign(data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			(
				(
					lhs_[RegisterIndices_] = EmuSIMD::mod<per_element_width, is_signed>
					(
						lhs_[RegisterIndices_],
						_retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_))
					)
				), ...
			);
		}

		template<std::size_t...RegisterIndices_>
		static constexpr inline void _do_array_negate_assign(data_type& lhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			((lhs_[RegisterIndices_] = EmuSIMD::negate<per_element_width>(lhs_[RegisterIndices_])), ...);
		}
#pragma endregion

#pragma region CONST_BITWISE_ARITHMETIC_HELPERS
	private:
		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_and(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			using rhs_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
			return data_type
			({
				EmuSIMD::bitwise_and(lhs_[RegisterIndices_], _retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_)))...
			});
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_or(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			using rhs_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
			return data_type
			({
				EmuSIMD::bitwise_or(lhs_[RegisterIndices_], _retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_)))...
			});
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_xor(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			using rhs_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
			return data_type
			({
				EmuSIMD::bitwise_xor(lhs_[RegisterIndices_], _retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_)))...
			});
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_andnot(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			using rhs_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
			return data_type
			({
				EmuSIMD::bitwise_andnot(lhs_[RegisterIndices_], _retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_)))...
			});
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_shift_left(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			using rhs_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
			return data_type
			({
				EmuSIMD::shift_left<per_element_width>(lhs_[RegisterIndices_], _retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_)))...
			});
		}

		template<std::size_t NumShifts_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_shift_left(const data_type& lhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type({ EmuSIMD::shift_left<NumShifts_, per_element_width>(lhs_[RegisterIndices_])... });
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_shift_right_arithmetic(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			using rhs_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
			return data_type
			({
				EmuSIMD::shift_right_arithmetic<per_element_width>(lhs_[RegisterIndices_], _retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_)))...
			});
		}

		template<std::size_t NumShifts_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_shift_right_arithmetic(const data_type& lhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type({ EmuSIMD::shift_right_arithmetic<NumShifts_, per_element_width>(lhs_[RegisterIndices_])... });
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_shift_right_logical(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			using rhs_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
			return data_type
			({
				EmuSIMD::shift_right_logical<per_element_width>(lhs_[RegisterIndices_], _retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_)))...
			});
		}

		template<std::size_t NumShifts_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_shift_right_logical(const data_type& lhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type({ EmuSIMD::shift_right_logical<NumShifts_, per_element_width>(lhs_[RegisterIndices_])... });
		}

		template<std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_not(const data_type& lhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type({ EmuSIMD::bitwise_not(lhs_[RegisterIndices_])... });
		}

		template<class A_, class B_>
		[[nodiscard]] static constexpr inline register_type _calculate_dot_2_fill(A_&& a_, B_&& b_)
		{
			return _generic_fill_from_register_index<0>(_calculate_dot_2(std::forward<A_>(a_), std::forward<B_>(b_)));
		}

		template<class A_, class B_>
		[[nodiscard]] static constexpr inline register_type _calculate_dot_2(A_&& a_, B_&& b_)
		{
			if constexpr (size >= 2)
			{
				register_type dot2 = EmuSIMD::mul_all<per_element_width>(_retrieve_register_from_arg<0>(a_), _retrieve_register_from_arg<0>(b_));

				if constexpr (elements_per_register == 2)
				{
					return EmuSIMD::add<per_element_width>(dot2, EmuSIMD::shuffle<1, 0>(dot2));
				}
				else if constexpr (elements_per_register == 4)
				{
					return EmuSIMD::add<per_element_width>(dot2, EmuSIMD::shuffle<1, 0, 1, 0>(dot2));
				}
				else if constexpr (elements_per_register == 8)
				{
					return EmuSIMD::add<per_element_width>(dot2, EmuSIMD::shuffle<1, 0, 1, 0, 1, 0, 1, 0>(dot2));
				}
				else if constexpr (elements_per_register == 16)
				{
					return EmuSIMD::add<per_element_width>(dot2, EmuSIMD::shuffle<1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0>(dot2));
				}
				else if constexpr (elements_per_register == 32)
				{
					return EmuSIMD::add<per_element_width>
					(
						dot2,
						EmuSIMD::shuffle<1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0>(dot2)
					);
				}
				else if constexpr (elements_per_register == 64)
				{
					return EmuSIMD::add<per_element_width>
					(
						dot2,
						EmuSIMD::shuffle
						<
							1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
							1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0
						>(dot2)
					);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<this_type>(),
						"Unable to perform a Dot2 operation on an EmuMath::FastVector instance as it cannot be reliably shuffled due to its elements_per_register size."
					);
				}
			}
			else
			{
				return EmuSIMD::mul_all<per_element_width>(_retrieve_register_from_arg<0>(a_), _retrieve_register_from_arg<0>(b_));
			}
		}
#pragma endregion

#pragma region NON_CONST_BITWISE_ARITHMETIC_HELPERS
	private:
		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline void _do_array_and_assign(data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			(
				(
					lhs_[RegisterIndices_] = EmuSIMD::bitwise_and
					(
						lhs_[RegisterIndices_],
						_retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_))
					)
				), ...
			);
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline void _do_array_or_assign(data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			(
				(
					lhs_[RegisterIndices_] = EmuSIMD::bitwise_or
					(
						lhs_[RegisterIndices_],
						_retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_))
					)
				), ...
			);
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline void _do_array_xor_assign(data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			(
				(
					lhs_[RegisterIndices_] = EmuSIMD::bitwise_xor
					(
						lhs_[RegisterIndices_],
						_retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_))
					)
				), ...
			);
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline void _do_array_andnot_assign(data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			(
				(
					lhs_[RegisterIndices_] = EmuSIMD::bitwise_andnot
					(
						lhs_[RegisterIndices_],
						_retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_))
					)
				), ...
			);
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline void _do_array_shift_left_assign(data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			(
				(
					lhs_[RegisterIndices_] = EmuSIMD::shift_left<per_element_width>
					(
						lhs_[RegisterIndices_],
						_retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_))
					)
				), ...
			);
		}

		template<std::size_t NumShifts_, std::size_t...RegisterIndices_>
		static constexpr inline void _do_array_shift_left_assign(data_type& lhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			((lhs_[RegisterIndices_] = EmuSIMD::shift_left<NumShifts_, per_element_width>(lhs_[RegisterIndices_])), ...);
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline void _do_array_shift_right_arithmetic_assign(data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			(
				(
					lhs_[RegisterIndices_] = EmuSIMD::shift_right_arithmetic<per_element_width>
					(
						lhs_[RegisterIndices_],
						_retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_))
					)
				), ...
			);
		}

		template<std::size_t NumShifts_, std::size_t...RegisterIndices_>
		static constexpr inline void _do_array_shift_right_arithmetic_assign(data_type& lhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			((lhs_[RegisterIndices_] = EmuSIMD::shift_right_arithmetic<NumShifts_, per_element_width>(lhs_[RegisterIndices_])), ...);
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline void _do_array_shift_right_logical_assign(data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			(
				(
					lhs_[RegisterIndices_] = EmuSIMD::shift_right_logical<per_element_width>
					(
						lhs_[RegisterIndices_],
						_retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_))
					)
				), ...
			);
		}

		template<std::size_t NumShifts_, std::size_t...RegisterIndices_>
		static constexpr inline void _do_array_shift_right_logical_assign(data_type& lhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			((lhs_[RegisterIndices_] = EmuSIMD::shift_right_logical<NumShifts_, per_element_width>(lhs_[RegisterIndices_])), ...);
		}

		template<std::size_t...RegisterIndices_>
		static constexpr inline void _do_array_not_assign(data_type& lhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			((lhs_[RegisterIndices_] = EmuSIMD::bitwise_not(lhs_[RegisterIndices_])), ...);
		}
#pragma endregion

#pragma region CONST_VECTOR_ARITHMETIC_HELPERS
	private:
		template<bool Fill_, typename B_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_dot(const data_type& a_, B_&& b_, std::index_sequence<RegisterIndices_...> indices_)
		{
			register_type result = _calculate_array_dot_pre_hadd(a_, std::forward<B_>(b_), indices_);

			if constexpr (Fill_)
			{
				return _do_set_all_same_register(EmuSIMD::horizontal_sum_fill<per_element_width>(result));
			}
			else
			{
				return _do_set_all_same_register(EmuSIMD::horizontal_sum<per_element_width>(result));
			}
		}

		template<typename Out_, typename B_, std::size_t...RegisterIndices_>
		static constexpr inline Out_ _do_array_dot_scalar(const data_type& a_, B_&& b_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return EmuSIMD::horizontal_sum_scalar<Out_, per_element_width>(_calculate_array_dot_pre_hadd(a_, std::forward<B_>(b_), indices_));
		}

		template<bool Fill_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_mag(const data_type& vec_, std::index_sequence<RegisterIndices_...> indices_)
		{
			register_type result = _calculate_array_dot_pre_hadd(vec_, vec_);

			if constexpr (Fill_)
			{
				result = EmuSIMD::horizontal_sum_fill<per_element_width>(result);
			}
			else
			{
				result = EmuSIMD::horizontal_sum<per_element_width>(result);
			}

			return _do_set_all_same_register(EmuSIMD::sqrt<per_element_width, is_signed>(result));
		}

		template<typename Out_, std::size_t...RegisterIndices_>
		static constexpr inline Out_ _do_array_mag_scalar(const data_type& vec_, std::index_sequence<RegisterIndices_...> indices_)
		{
			Out_ squared_magnitude = EmuSIMD::horizontal_sum_scalar<Out_, per_element_width>(_calculate_array_dot_pre_hadd(vec_, vec_, indices_));
			if constexpr (per_element_byte_size <= 4)
			{
				return static_cast<Out_>(sqrtf(EmuSIMD::horizontal_sum_scalar<float, per_element_width>(_calculate_array_dot_pre_hadd(vec_, vec_, indices_))));
			}
			else
			{
				return static_cast<Out_>(sqrt(EmuSIMD::horizontal_sum_scalar<double, per_element_width>(_calculate_array_dot_pre_hadd(vec_, vec_, indices_))));
			}
		}

		template<class Vector_>
		static constexpr inline Vector_ _do_normalise(const Vector_& in_)
		{
			if constexpr (Vector_::contains_multiple_registers)
			{
				return _do_array_normalise<Vector_>(in_, typename Vector_::register_index_sequence());
			}
			else
			{
				using out_register = typename Vector_::register_type;
				out_register mag_reciprocal = EmuSIMD::dot_fill(in_.data, in_.data);
				mag_reciprocal = EmuSIMD::rsqrt<Vector_::per_element_width, Vector_::is_signed>(mag_reciprocal);
				return Vector_(EmuSIMD::mul_all<Vector_::per_element_width>(in_.data, mag_reciprocal));
			}
		}

		template<class Vector_, std::size_t...RegisterIndices_>
		static constexpr inline Vector_ _do_array_normalise(const Vector_& in_, std::index_sequence<RegisterIndices_...> register_indices_)
		{
			using out_register = typename Vector_::register_type;
			out_register mag = Vector_::make_all_zero_register();

			(
				(
					mag = EmuSIMD::add<Vector_::per_element_width>
					(
						mag,
						_do_generic_dot_mult<RegisterIndices_, Vector_>
						(
							in_.data[RegisterIndices_],
							in_.data[RegisterIndices_]
						)
					)
				), ...
			);
			mag = EmuSIMD::horizontal_sum_fill<Vector_::per_element_width>(mag);

			return in_ * EmuSIMD::rsqrt<Vector_::per_element_width, Vector_::is_signed>(mag);
		}

		template<std::size_t RegisterIndex_, class Vector_>
		static constexpr inline typename Vector_::register_type _do_generic_dot_mult(typename Vector_::register_arg_type a_, typename Vector_::register_arg_type b_)
		{
			constexpr std::size_t final_index = Vector_::num_registers - 1;
			if constexpr (!Vector_::requires_partial_register || RegisterIndex_ != final_index)
			{
				return EmuSIMD::mul_all<Vector_::per_element_width>(a_, b_);
			}
			else
			{
				return EmuSIMD::mul_all<Vector_::per_element_width>(EmuSIMD::bitwise_and(a_, Vector_::make_partial_end_exclude_mask_register()), b_);
			}
		}

		template<class B_, std::size_t...RegisterIndices_>
		static constexpr inline register_type _calculate_array_dot_pre_hadd(const data_type& a_, B_&& b_, std::index_sequence<RegisterIndices_...> indices_)
		{
			register_type result = make_all_zero_register();

			(
				(
					result = EmuSIMD::add<per_element_width>
					(
						result,
						_do_array_dot_mult<RegisterIndices_>
						(
							a_[RegisterIndices_],
							_retrieve_register_from_arg<RegisterIndices_>(std::forward<B_>(b_))
						)
					)
				), ...
			);

			return result;
		}

		template<std::size_t RegisterIndex_>
		static constexpr inline register_type _do_array_dot_mult(register_arg_type a_, register_arg_type b_)
		{
			constexpr std::size_t final_index = num_registers - 1;
			if constexpr (!requires_partial_register || RegisterIndex_ != final_index)
			{
				return EmuSIMD::mul_all<per_element_width>(a_, b_);
			}
			else
			{
				return EmuSIMD::mul_all<per_element_width>(EmuSIMD::bitwise_and(a_, make_partial_end_exclude_mask_register()), b_);
			}
		}

		template<typename B_, typename T_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_lerp(const data_type& lhs_, B_&& b_, T_&& t_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type
			({
				EmuSIMD::lerp<per_element_width>
				(
					lhs_[RegisterIndices_],
					_retrieve_register_from_arg<RegisterIndices_>(std::forward<B_>(b_)),
					_retrieve_register_from_arg<RegisterIndices_>(std::forward<T_>(t_))
				)...
			});
		}

		template<typename B_, typename T_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_fused_lerp(const data_type& lhs_, B_&& b_, T_&& t_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type
			({
				EmuSIMD::fused_lerp<per_element_width>
				(
					lhs_[RegisterIndices_],
					_retrieve_register_from_arg<RegisterIndices_>(std::forward<B_>(b_)),
					_retrieve_register_from_arg<RegisterIndices_>(std::forward<T_>(t_))
				)...
			});
		}
#pragma endregion

#pragma region COMPARISON_BOOL_OUT_HELPERS
	private:
		template<bool TakeLhs_, EmuCore::BasicCmp CmpType_>
		static constexpr inline register_type _mask_register_for_cmp_all(register_arg_type lhs_, register_arg_type rhs_)
		{
			if constexpr (CmpType_ == EmuCore::BasicCmp::EQUAL || CmpType_ == EmuCore::BasicCmp::GREATER_EQUAL || CmpType_ == EmuCore::BasicCmp::LESS_EQUAL)
			{
				// Lhs = 0 in non-contained indices
				// Rhs = 0 in non-contained indices
				register_type mask = make_partial_end_exclude_mask_register();
				if constexpr (TakeLhs_)
				{
					return EmuSIMD::bitwise_and(mask, lhs_);
				}
				else
				{
					return EmuSIMD::bitwise_and(mask, rhs_);
				}
			}
			else if constexpr (CmpType_ == EmuCore::BasicCmp::NOT_EQUAL)
			{
				// Lhs = Lhs
				// Rhs = ~Lhs in non-contained indices
				if constexpr (TakeLhs_)
				{
					return lhs_;
				}
				else
				{
					register_type mask = make_partial_end_exclude_mask_register();
					return EmuSIMD::bitwise_or
					(
						EmuSIMD::bitwise_and(mask, rhs_),
						EmuSIMD::bitwise_andnot(mask, EmuSIMD::bitwise_not(lhs_))
					);
				}
			}
			else if constexpr(CmpType_ == EmuCore::BasicCmp::GREATER)
			{
				// Lhs = 1 in non-contained indices
				// Rhs = 0 in non-contained indices
				if constexpr (TakeLhs_)
				{
					register_type mask = make_partial_end_exclude_mask_register();
					return EmuSIMD::bitwise_or
					(
						EmuSIMD::bitwise_and(mask, lhs_),
						EmuSIMD::bitwise_andnot(mask, EmuSIMD::set1<register_type, per_element_width>(1))
					);
				}
				else
				{
					register_type mask = make_partial_end_exclude_mask_register();
					return EmuSIMD::bitwise_and(mask, rhs_);
				}
			}
			else if constexpr(CmpType_ == EmuCore::BasicCmp::LESS)
			{
				// Lhs = 0 in non-contained indices
				// Rhs = 1 in non-contained indices
				if constexpr (TakeLhs_)
				{
					register_type mask = make_partial_end_exclude_mask_register();
					return EmuSIMD::bitwise_and(mask, lhs_);
				}
				else
				{
					register_type mask = make_partial_end_exclude_mask_register();
					return EmuSIMD::bitwise_or
					(
						EmuSIMD::bitwise_and(mask, rhs_),
						EmuSIMD::bitwise_andnot(mask, EmuSIMD::set1<register_type, per_element_width>(1))
					);
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<CmpType_>(), "Internal EmuMath Error: Called _mask_register_for_cmp_all with an invalid CmpType_.");
			}
		}

		template<bool TakeLhs_, EmuCore::BasicCmp CmpType_>
		static constexpr inline register_type _mask_register_for_cmp_any(register_arg_type lhs_, register_arg_type rhs_)
		{
			if constexpr (CmpType_ == EmuCore::BasicCmp::NOT_EQUAL)
			{
				// Lhs = 0 in non-contained indices
				// Rhs = 0 in non-contained indices
				register_type mask = make_partial_end_exclude_mask_register();
				if constexpr (TakeLhs_)
				{
					return EmuSIMD::bitwise_and(mask, lhs_);
				}
				else
				{
					return EmuSIMD::bitwise_and(mask, rhs_);
				}
			}
			else if constexpr (CmpType_ == EmuCore::BasicCmp::EQUAL || CmpType_ == EmuCore::BasicCmp::GREATER || CmpType_ == EmuCore::BasicCmp::GREATER_EQUAL)
			{
				// Lhs = 0 in non-contained indices
				// Rhs = 1 in non-contained indices
				if constexpr (TakeLhs_)
				{
					register_type mask = make_partial_end_exclude_mask_register();
					return EmuSIMD::bitwise_and(mask, lhs_);
				}
				else
				{
					register_type mask = make_partial_end_exclude_mask_register();
					return EmuSIMD::bitwise_or
					(
						EmuSIMD::bitwise_and(mask, rhs_),
						EmuSIMD::bitwise_andnot(mask, EmuSIMD::set1<register_type, per_element_width>(1))
					);
				}
			}
			else if constexpr (CmpType_ == EmuCore::BasicCmp::LESS || CmpType_ == EmuCore::BasicCmp::LESS_EQUAL)
			{
				// Lhs = 1 in non-contained indices
				// Rhs = 0 in non-contained indices
				if constexpr (TakeLhs_)
				{
					register_type mask = make_partial_end_exclude_mask_register();
					return EmuSIMD::bitwise_or
					(
						EmuSIMD::bitwise_and(mask, lhs_),
						EmuSIMD::bitwise_andnot(mask, EmuSIMD::set1<register_type, per_element_width>(1))
					);
				}
				else
				{
					register_type mask = make_partial_end_exclude_mask_register();
					return EmuSIMD::bitwise_and(mask, rhs_);
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<CmpType_>(), "Internal EmuMath Error: Called _mask_register_for_cmp_any with an invalid CmpType_.");
			}
		}

		template<std::size_t RegisterIndex_, EmuCore::BasicCmp CmpType_, bool TakeLhs_, bool All_, class Lhs_, class Rhs_>
		[[nodiscard]] static constexpr inline register_type _retrieve_register_for_bool_out_cmp(Lhs_&& lhs_, Rhs_&& rhs_)
		{
			using in_type = std::conditional_t<TakeLhs_, Lhs_, Rhs_>;
			using in_uq = typename EmuCore::TMP::remove_ref_cv<in_type>::type;
			constexpr bool is_final_index = (num_registers - 1) == RegisterIndex_;

			if constexpr (is_final_index && requires_partial_register)
			{
				if constexpr (All_)
				{
					return _mask_register_for_cmp_all<TakeLhs_, CmpType_>
					(
						_retrieve_register_from_arg<RegisterIndex_>(std::forward<Lhs_>(lhs_)),
						_retrieve_register_from_arg<RegisterIndex_>(std::forward<Rhs_>(rhs_))
					);
				}
				else
				{
					return _mask_register_for_cmp_any<TakeLhs_, CmpType_>
					(
						_retrieve_register_from_arg<RegisterIndex_>(std::forward<Lhs_>(lhs_)),
						_retrieve_register_from_arg<RegisterIndex_>(std::forward<Rhs_>(rhs_))
					);
				}
			}
			else
			{
				if constexpr (TakeLhs_)
				{
					return _retrieve_register_from_arg<RegisterIndex_>(std::forward<Lhs_>(lhs_));
				}
				else
				{
					return _retrieve_register_from_arg<RegisterIndex_>(std::forward<Rhs_>(rhs_));
				}
			}
		}

		template<std::size_t RegisterIndex_, bool TakeLhs_, bool All_, bool CustomEpsilon_, class Lhs_, class Rhs_>
		[[nodiscard]] static constexpr inline register_type _retrieve_register_for_bool_out_cmp_near(Lhs_&& lhs_, Rhs_&& rhs_)
		{
			constexpr bool is_final_index = (num_registers - 1) == RegisterIndex_;
			if constexpr (is_final_index && requires_partial_register)
			{
				if constexpr (All_)
				{
					register_type mask = make_partial_end_exclude_mask_register();
					// Lhs and Rhs both set to 0 in non-contained indices
					if constexpr (TakeLhs_)
					{
						return EmuSIMD::bitwise_and(mask, _retrieve_register_from_arg<RegisterIndex_>(std::forward<Lhs_>(lhs_)));
					}
					else
					{
						return EmuSIMD::bitwise_and(mask, _retrieve_register_from_arg<RegisterIndex_>(std::forward<Rhs_>(rhs_)));
					}
				}
				else
				{
					if constexpr (is_floating_point)
					{
						if constexpr (CustomEpsilon_)
						{
							// Nothing to worry about when floating-point as non-contained indices will be NaN in epsilon, which will always result in false comparison results @IEEE-754
							if constexpr (TakeLhs_)
							{
								return _retrieve_register_from_arg<RegisterIndex_>(std::forward<Lhs_>(lhs_));
							}
							else
							{
								return _retrieve_register_from_arg<RegisterIndex_>(std::forward<Rhs_>(rhs_));
							}
						}
						else
						{
							// No Custom Epsilon, but any arithmetic with NaN will result in NaN, and a comparison with NaN will always be false (a la IEEE-754)
							if constexpr (TakeLhs_)
							{
								return _retrieve_register_from_arg<RegisterIndex_>(std::forward<Lhs_>(lhs_));
							}
							else
							{
								register_type mask = make_partial_end_exclude_mask_register();
								return EmuSIMD::bitwise_or
								(
									EmuSIMD::bitwise_and(mask, _retrieve_register_from_arg<RegisterIndex_>(std::forward<Rhs_>(rhs_))),
									EmuSIMD::bitwise_andnot(mask, EmuSIMD::set1<register_type, per_element_width>(std::numeric_limits<value_type>::quiet_NaN()))
								);
							}
						}
					}
					else
					{
						register_type mask = make_partial_end_exclude_mask_register();
						// Make non-contained rhs not equal to lhs; default epsilon for integers is 0, and if a custom epsilon is provided it will be masked to zero in said indices
						if constexpr (TakeLhs_)
						{
							// Lhs is 0 in non-contained indices
							return EmuSIMD::bitwise_and(mask, _retrieve_register_from_arg<RegisterIndex_>(std::forward<Lhs_>(lhs_)));
						}
						else
						{
							return EmuSIMD::bitwise_or
							(
								EmuSIMD::bitwise_and(mask, _retrieve_register_from_arg<RegisterIndex_>(std::forward<Rhs_>(rhs_))),
								EmuSIMD::set1<register_type, per_element_width>(1)
							);
						}
					}
				}
			}
			else
			{
				if constexpr (TakeLhs_)
				{
					return _retrieve_register_from_arg<RegisterIndex_>(std::forward<Lhs_>(lhs_));
				}
				else
				{
					return _retrieve_register_from_arg<RegisterIndex_>(std::forward<Rhs_>(rhs_));
				}
			}
		}

		template<std::size_t RegisterIndex_, bool All_, class Epsilon_>
		[[nodiscard]] static constexpr inline register_type _retrieve_epsilon_register_for_bool_out_cmp_near(Epsilon_&& epsilon_)
		{
			constexpr bool is_final_index = (num_registers - 1) == RegisterIndex_;
			if constexpr (is_final_index && requires_partial_register)
			{
				register_type mask = make_partial_end_exclude_mask_register();
				if constexpr (All_)
				{
					if constexpr (is_floating_point || is_signed)
					{
						// Everything is set to 0 in non-contained indices (this is to prevent bad NaNs and negative epsilons)
						return EmuSIMD::bitwise_and(mask, _retrieve_register_from_arg<RegisterIndex_>(std::forward<Epsilon_>(epsilon_)));
					}
					else
					{
						// No problems if an unsigned integer; (0 - 0) will always be less than or equal to whatever is here
						return _retrieve_register_from_arg<RegisterIndex_>(std::forward<Epsilon_>(epsilon_));
					}
				}
				else
				{
					if constexpr (is_floating_point)
					{
						// Epsilon is (non-signalling) NaN for non-contained indices; resulting checks will be NaN, and `NaN >= NaN` is false (a la IEEE-754).
						return EmuSIMD::bitwise_or
						(
							EmuSIMD::bitwise_and(mask, _retrieve_register_from_arg<RegisterIndex_>(std::forward<Epsilon_>(epsilon_))),
							EmuSIMD::bitwise_andnot(mask, EmuSIMD::set1<register_type>(std::numeric_limits<value_type>::quiet_NaN()))
						);
					}
					else
					{
						// Epsilon is 0 for non-contained indices; rhs will be retrieved as a non-lhs value for non-contained indices
						return EmuSIMD::bitwise_and(mask, _retrieve_register_from_arg<RegisterIndex_>(std::forward<Epsilon_>(epsilon_)));
					}
				}
			}
			else
			{
				return _retrieve_register_from_arg<RegisterIndex_>(std::forward<Epsilon_>(epsilon_));
			}
		}

		template<bool All_, class Rhs_, std::size_t...RegisterIndices_ >
		[[nodiscard]] static constexpr inline bool _do_array_cmp_equal_bool_out(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			if constexpr (All_)
			{
				return 
				(
					... && EmuSIMD::cmp_all_eq<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::EQUAL, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::EQUAL, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					)
				);
			}
			else
			{
				return 
				(
					... || EmuSIMD::cmp_any_eq<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::EQUAL, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::EQUAL, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					)
				);
			}
		}

		template<bool All_, class Rhs_>
		[[nodiscard]] static constexpr inline bool _do_cmp_equal_bool_out(const data_type& lhs_, Rhs_&& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				return _do_array_cmp_equal_bool_out<All_>(lhs_, std::forward<Rhs_>(rhs_), register_index_sequence());
			}
			else if constexpr (requires_partial_register)
			{
				if constexpr (All_)
				{
					return EmuSIMD::cmp_all_eq<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::EQUAL, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::EQUAL, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					);
				}
				else
				{
					return EmuSIMD::cmp_any_eq<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::EQUAL, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::EQUAL, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					);
				}
			}
			else
			{
				if constexpr (All_)
				{
					return EmuSIMD::cmp_all_eq<per_element_width, is_signed>(lhs_, _retrieve_register_from_arg<0>(std::forward<Rhs_>(rhs_)));
				}
				else
				{
					return EmuSIMD::cmp_any_eq<per_element_width, is_signed>(lhs_, _retrieve_register_from_arg<0>(std::forward<Rhs_>(rhs_)));
				}
			}
		}

		template<bool All_, class Rhs_, std::size_t...RegisterIndices_ >
		[[nodiscard]] static constexpr inline bool _do_array_cmp_not_equal_bool_out(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			if constexpr (All_)
			{
				return 
				(
					... && EmuSIMD::cmp_all_neq<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::NOT_EQUAL, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::NOT_EQUAL, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					)
				);
			}
			else
			{
				return 
				(
					... || EmuSIMD::cmp_any_neq<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::NOT_EQUAL, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::NOT_EQUAL, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					)
				);
			}
		}

		template<bool All_, class Rhs_>
		[[nodiscard]] static constexpr inline bool _do_cmp_not_equal_bool_out(const data_type& lhs_, Rhs_&& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				return _do_array_cmp_not_equal_bool_out<All_>(lhs_, std::forward<Rhs_>(rhs_), register_index_sequence());
			}
			else if constexpr (requires_partial_register)
			{
				if constexpr (All_)
				{
					return EmuSIMD::cmp_all_neq<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::NOT_EQUAL, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::NOT_EQUAL, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					);
				}
				else
				{
					return EmuSIMD::cmp_any_neq<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::NOT_EQUAL, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::NOT_EQUAL, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					);
				}
			}
			else
			{
				if constexpr (All_)
				{
					return EmuSIMD::cmp_all_neq<per_element_width, is_signed>(lhs_, _retrieve_register_from_arg<0>(std::forward<Rhs_>(rhs_)));
				}
				else
				{
					return EmuSIMD::cmp_any_neq<per_element_width, is_signed>(lhs_, _retrieve_register_from_arg<0>(std::forward<Rhs_>(rhs_)));
				}
			}
		}

		template<bool All_, class Rhs_, std::size_t...RegisterIndices_ >
		[[nodiscard]] static constexpr inline bool _do_array_cmp_near_equal_bool_out(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			if constexpr (All_)
			{
				return 
				(
					... && EmuSIMD::cmp_all_near<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp_near<RegisterIndices_, true, All_, false>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp_near<RegisterIndices_, false, All_, false>(lhs_, std::forward<Rhs_>(rhs_))
					)
				);
			}
			else
			{
				return 
				(
					... || EmuSIMD::cmp_any_near<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp_near<RegisterIndices_, true, All_, false>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp_near<RegisterIndices_, false, All_, false>(lhs_, std::forward<Rhs_>(rhs_))
					)
				);
			}
		}

		template<bool All_, class Rhs_, class Epsilon_, std::size_t...RegisterIndices_ >
		[[nodiscard]] static constexpr inline bool _do_array_cmp_near_equal_bool_out
		(
			const data_type& lhs_,
			Rhs_&& rhs_,
			Epsilon_&& epsilon_,
			std::index_sequence<RegisterIndices_...> indices_
		)
		{
			if constexpr (All_)
			{
				return 
				(
					... && EmuSIMD::cmp_all_near<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp_near<RegisterIndices_, true, All_, true>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp_near<RegisterIndices_, false, All_, true>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_epsilon_register_for_bool_out_cmp_near<RegisterIndices_, All_>(std::forward<Epsilon_>(epsilon_))
					)
				);
			}
			else
			{
				return 
				(
					... || EmuSIMD::cmp_any_near<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp_near<RegisterIndices_, true, All_, true>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp_near<RegisterIndices_, false, All_, true>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_epsilon_register_for_bool_out_cmp_near<RegisterIndices_, All_>(std::forward<Epsilon_>(epsilon_))
					)
				);
			}
		}

		template<bool All_, class Rhs_>
		[[nodiscard]] static constexpr inline bool _do_cmp_near_equal_bool_out(const data_type& lhs_, Rhs_&& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				return _do_array_cmp_near_equal_bool_out<All_>(lhs_, std::forward<Rhs_>(rhs_), register_index_sequence());
			}
			else if constexpr (requires_partial_register)
			{
				if constexpr (All_)
				{
					return EmuSIMD::cmp_all_near<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp_near<0, true, All_, false>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp_near<0, false, All_, false>(lhs_, std::forward<Rhs_>(rhs_))
					);
				}
				else
				{
					return EmuSIMD::cmp_any_near<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp_near<0, true, All_, false>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp_near<0, false, All_, false>(lhs_, std::forward<Rhs_>(rhs_))
					);
				}
			}
			else
			{
				if constexpr (All_)
				{
					return EmuSIMD::cmp_all_near<per_element_width, is_signed>(lhs_, _retrieve_register_from_arg<0>(std::forward<Rhs_>(rhs_)));
				}
				else
				{
					return EmuSIMD::cmp_any_near<per_element_width, is_signed>(lhs_, _retrieve_register_from_arg<0>(std::forward<Rhs_>(rhs_)));
				}
			}
		}

		template<bool All_, class Rhs_, class Epsilon_>
		[[nodiscard]] static constexpr inline bool _do_cmp_near_equal_bool_out(const data_type& lhs_, Rhs_&& rhs_, Epsilon_&& epsilon_)
		{
			if constexpr (contains_multiple_registers)
			{
				return _do_array_cmp_near_equal_bool_out<All_>(lhs_, std::forward<Rhs_>(rhs_), std::forward<Epsilon_>(epsilon_), register_index_sequence());
			}
			else if constexpr (requires_partial_register)
			{
				if constexpr (All_)
				{
					return EmuSIMD::cmp_all_near<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp_near<0, true, All_, true>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp_near<0, false, All_, true>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_epsilon_register_for_bool_out_cmp_near<0, All_>(std::forward<Epsilon_>(epsilon_))
					);
				}
				else
				{
					return EmuSIMD::cmp_any_near<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp_near<0, true, All_, true>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp_near<0, false, All_, true>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_epsilon_register_for_bool_out_cmp_near<0, All_>(std::forward<Epsilon_>(epsilon_))
					);
				}
			}
			else
			{
				if constexpr (All_)
				{
					return EmuSIMD::cmp_all_near<per_element_width, is_signed>
					(
						lhs_,
						_retrieve_register_from_arg<0>(std::forward<Rhs_>(rhs_)),
						_retrieve_register_from_arg<0>(std::forward<Epsilon_>(epsilon_))
					);
				}
				else
				{
					return EmuSIMD::cmp_any_near<per_element_width, is_signed>
					(
						lhs_,
						_retrieve_register_from_arg<0>(std::forward<Rhs_>(rhs_)),
						_retrieve_register_from_arg<0>(std::forward<Epsilon_>(epsilon_))
					);
				}
			}
		}		

		template<bool All_, class Rhs_, std::size_t...RegisterIndices_ >
		[[nodiscard]] static constexpr inline bool _do_array_cmp_greater_bool_out(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			if constexpr (All_)
			{
				return 
				(
					... && EmuSIMD::cmp_all_gt<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::GREATER, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::GREATER, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					)					
				);
			}
			else
			{
				return 
				(
					... || EmuSIMD::cmp_any_gt<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::GREATER, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::GREATER, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					)
				);
			}
		}

		template<bool All_, class Rhs_>
		[[nodiscard]] static constexpr inline bool _do_cmp_greater_bool_out(const data_type& lhs_, Rhs_&& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				return _do_array_cmp_greater_bool_out<All_>(lhs_, std::forward<Rhs_>(rhs_), register_index_sequence());
			}
			else if constexpr (requires_partial_register)
			{
				if constexpr (All_)
				{
					return EmuSIMD::cmp_all_gt<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::GREATER, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::GREATER, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					);
				}
				else
				{
					return EmuSIMD::cmp_any_gt<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::GREATER, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::GREATER, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					);
				}
			}
			else
			{
				if constexpr (All_)
				{
					return EmuSIMD::cmp_all_gt<per_element_width, is_signed>(lhs_, _retrieve_register_from_arg<0>(std::forward<Rhs_>(rhs_)));
				}
				else
				{
					return EmuSIMD::cmp_any_gt<per_element_width, is_signed>(lhs_, _retrieve_register_from_arg<0>(std::forward<Rhs_>(rhs_)));
				}
			}
		}

		template<bool All_, class Rhs_, std::size_t...RegisterIndices_ >
		[[nodiscard]] static constexpr inline bool _do_array_cmp_less_bool_out(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			if constexpr (All_)
			{
				return 
				(
					... && EmuSIMD::cmp_all_lt<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::LESS, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::LESS, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					)					
				);
			}
			else
			{
				return 
				(
					... || EmuSIMD::cmp_any_lt<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::LESS, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::LESS, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					)
				);
			}
		}

		template<bool All_, class Rhs_>
		[[nodiscard]] static constexpr inline bool _do_cmp_less_bool_out(const data_type& lhs_, Rhs_&& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				return _do_array_cmp_less_bool_out<All_>(lhs_, std::forward<Rhs_>(rhs_), register_index_sequence());
			}
			else if constexpr (requires_partial_register)
			{
				if constexpr (All_)
				{
					return EmuSIMD::cmp_all_lt<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::LESS, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::LESS, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					);
				}
				else
				{
					return EmuSIMD::cmp_any_lt<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::LESS, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::LESS, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					);
				}
			}
			else
			{
				if constexpr (All_)
				{
					return EmuSIMD::cmp_all_lt<per_element_width, is_signed>(lhs_, _retrieve_register_from_arg<0>(std::forward<Rhs_>(rhs_)));
				}
				else
				{
					return EmuSIMD::cmp_any_lt<per_element_width, is_signed>(lhs_, _retrieve_register_from_arg<0>(std::forward<Rhs_>(rhs_)));
				}
			}
		}

		template<bool All_, class Rhs_, std::size_t...RegisterIndices_ >
		[[nodiscard]] static constexpr inline bool _do_array_cmp_greater_equal_bool_out(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			if constexpr (All_)
			{
				return 
				(
					... && EmuSIMD::cmp_all_ge<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::GREATER_EQUAL, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::GREATER_EQUAL, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					)					
				);
			}
			else
			{
				return 
				(
					... || EmuSIMD::cmp_any_ge<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::GREATER_EQUAL, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::GREATER_EQUAL, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					)
				);
			}
		}

		template<bool All_, class Rhs_>
		[[nodiscard]] static constexpr inline bool _do_cmp_greater_equal_bool_out(const data_type& lhs_, Rhs_&& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				return _do_array_cmp_greater_equal_bool_out<All_>(lhs_, std::forward<Rhs_>(rhs_), register_index_sequence());
			}
			else if constexpr (requires_partial_register)
			{
				if constexpr (All_)
				{
					return EmuSIMD::cmp_all_ge<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::GREATER_EQUAL, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::GREATER_EQUAL, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					);
				}
				else
				{
					return EmuSIMD::cmp_any_ge<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::GREATER_EQUAL, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::GREATER_EQUAL, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					);
				}
			}
			else
			{
				if constexpr (All_)
				{
					return EmuSIMD::cmp_all_ge<per_element_width, is_signed>(lhs_, _retrieve_register_from_arg<0>(std::forward<Rhs_>(rhs_)));
				}
				else
				{
					return EmuSIMD::cmp_any_ge<per_element_width, is_signed>(lhs_, _retrieve_register_from_arg<0>(std::forward<Rhs_>(rhs_)));
				}
			}
		}

		template<bool All_, class Rhs_, std::size_t...RegisterIndices_ >
		[[nodiscard]] static constexpr inline bool _do_array_cmp_less_equal_bool_out(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			if constexpr (All_)
			{
				return 
				(
					... && EmuSIMD::cmp_all_le<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::LESS_EQUAL, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::LESS_EQUAL, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					)					
				);
			}
			else
			{
				return 
				(
					... || EmuSIMD::cmp_any_le<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::LESS_EQUAL, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<RegisterIndices_, EmuCore::BasicCmp::LESS_EQUAL, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					)
				);
			}
		}

		template<bool All_, class Rhs_>
		[[nodiscard]] static constexpr inline bool _do_cmp_less_equal_bool_out(const data_type& lhs_, Rhs_&& rhs_)
		{
			if constexpr (contains_multiple_registers)
			{
				return _do_array_cmp_greater_equal_bool_out<All_>(lhs_, std::forward<Rhs_>(rhs_), register_index_sequence());
			}
			else if constexpr (requires_partial_register)
			{
				if constexpr (All_)
				{
					return EmuSIMD::cmp_all_le<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::LESS_EQUAL, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::LESS_EQUAL, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					);
				}
				else
				{
					return EmuSIMD::cmp_any_le<per_element_width, is_signed>
					(
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::LESS_EQUAL, true, All_>(lhs_, std::forward<Rhs_>(rhs_)),
						_retrieve_register_for_bool_out_cmp<0, EmuCore::BasicCmp::LESS_EQUAL, false, All_>(lhs_, std::forward<Rhs_>(rhs_))
					);
				}
			}
			else
			{
				if constexpr (All_)
				{
					return EmuSIMD::cmp_all_le<per_element_width, is_signed>(lhs_, _retrieve_register_from_arg<0>(std::forward<Rhs_>(rhs_)));
				}
				else
				{
					return EmuSIMD::cmp_any_le<per_element_width, is_signed>(lhs_, _retrieve_register_from_arg<0>(std::forward<Rhs_>(rhs_)));
				}
			}
		}
#pragma endregion

#pragma region COMPARISON_PER_ELEMENT_HELPERS
	private:
		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_cmp_per_element_equal(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type({ EmuSIMD::cmpeq<per_element_width, is_signed>(lhs_[RegisterIndices_], _retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_)))... });
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_cmp_per_element_not_equal(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type({ EmuSIMD::cmpneq<per_element_width, is_signed>(lhs_[RegisterIndices_], _retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_)))... });
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_cmp_per_element_near_equal(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type({ EmuSIMD::cmpnear<per_element_width, is_signed>(lhs_[RegisterIndices_], _retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_)))... });
		}

		template<typename Rhs_, typename Epsilon_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_cmp_per_element_near_equal
		(
			const data_type& lhs_,
			Rhs_&& rhs_,
			Epsilon_&& epsilon_,
			std::index_sequence<RegisterIndices_...> indices_
		)
		{
			return data_type
			({
				EmuSIMD::cmpnear<per_element_width, is_signed>
				(
					lhs_[RegisterIndices_],
					_retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_)),
					_retrieve_register_from_arg<RegisterIndices_>(std::forward<Epsilon_>(epsilon_))
				)...
			});
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_cmp_per_element_greater(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type({ EmuSIMD::cmpgt<per_element_width, is_signed>(lhs_[RegisterIndices_], _retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_)))... });
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_cmp_per_element_less(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type({ EmuSIMD::cmplt<per_element_width, is_signed>(lhs_[RegisterIndices_], _retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_)))... });
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_cmp_per_element_greater_equal(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type({ EmuSIMD::cmpge<per_element_width, is_signed>(lhs_[RegisterIndices_], _retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_)))... });
		}

		template<typename Rhs_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_cmp_per_element_less_equal(const data_type& lhs_, Rhs_&& rhs_, std::index_sequence<RegisterIndices_...> indices_)
		{
			return data_type({ EmuSIMD::cmple<per_element_width, is_signed>(lhs_[RegisterIndices_], _retrieve_register_from_arg<RegisterIndices_>(std::forward<Rhs_>(rhs_)))... });
		}
#pragma endregion

#pragma region NON_CONST_VECTOR_ARITHMETIC_HELPERS
	private:
		template<typename B_, typename T_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_lerp_assign(const data_type& lhs_, B_&& b_, T_&& t_, std::index_sequence<RegisterIndices_...> indices_)
		{
			(
				(
					lhs_[RegisterIndices_] = EmuSIMD::lerp<per_element_width>
					(
						lhs_[RegisterIndices_],
						_retrieve_register_from_arg<RegisterIndices_>(std::forward<B_>(b_)),
						_retrieve_register_from_arg<RegisterIndices_>(std::forward<T_>(t_))
					)
				), ...
			);
		}

		template<typename B_, typename T_, std::size_t...RegisterIndices_>
		static constexpr inline data_type _do_array_fused_lerp_assign(const data_type& lhs_, B_&& b_, T_&& t_, std::index_sequence<RegisterIndices_...> indices_)
		{
			(
				(
					lhs_[RegisterIndices_] = EmuSIMD::fused_lerp<per_element_width>
					(
						lhs_[RegisterIndices_],
						_retrieve_register_from_arg<RegisterIndices_>(std::forward<B_>(b_)),
						_retrieve_register_from_arg<RegisterIndices_>(std::forward<T_>(t_))
					)
				), ...
			);
		}
#pragma endregion

#pragma region SETTER_HELPERS
	private:
		template<std::size_t...RegisterIndices_>
		constexpr inline void _set_zero_array(std::index_sequence<RegisterIndices_...> indices_) noexcept
		{
			((data[RegisterIndices_] = EmuSIMD::setzero<register_type>()), ...);
		}

		template<std::size_t...RegisterIndices_>
		constexpr inline void _set_one_array(std::index_sequence<RegisterIndices_...> indices_) noexcept
		{
			((data[RegisterIndices_] = EmuSIMD::setallone<register_type>()), ...);
		}

		template<std::size_t...RegisterIndices_>
		constexpr inline void _set1_array(const value_type& val_, std::index_sequence<RegisterIndices_...> indices_) noexcept
		{
			((data[RegisterIndices_] = EmuSIMD::set1<register_type, per_element_width>(val_)), ...);
		}
#pragma endregion

#pragma region CONVERSION_HELPERS
	private:
		template<class Out_, std::size_t...OutIndices_>
		[[nodiscard]] constexpr inline Out_ _do_basic_store_and_load_conversion(std::index_sequence<OutIndices_...> out_indices_) const
		{
			using out_uq = typename EmuCore::TMP::remove_ref_cv<Out_>::type;
			using out_value_type = typename out_uq::value_type;
			constexpr std::size_t required_index_count = sizeof...(OutIndices_);
			constexpr bool requires_partial_register = (required_index_count % elements_per_register) != 0;
			constexpr std::size_t required_register_count = (required_index_count / elements_per_register) + requires_partial_register;
			constexpr std::size_t total_stored_register_count = required_register_count > num_registers ? num_registers : required_register_count;
			constexpr std::size_t stored_data_size = total_stored_register_count * elements_per_register;
			constexpr std::size_t end_read_index = stored_data_size > size ? size : stored_data_size;

			value_type stored_data[stored_data_size];
			_store_all<total_stored_register_count>(stored_data);
			return Out_(_make_basic_store_and_load_output_value<out_value_type, OutIndices_, end_read_index>(stored_data)...);
		}

		template<class OutValue_, std::size_t OutIndex_, std::size_t DataEnd_>
		[[nodiscard]] static constexpr inline OutValue_ _make_basic_store_and_load_output_value(value_type* p_data_)
		{
			if constexpr (OutIndex_ < DataEnd_)
			{
				using move_result = decltype(std::move(std::declval<value_type&>()));
				if constexpr (EmuCore::TMP::is_static_castable_v<move_result, OutValue_>)
				{
					return static_cast<OutValue_>(std::move(*(p_data_ + OutIndex_)));
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutValue_>(),
						"Attempted to perform a basic store-and-load conversion between two EmuMath::FastVector types, but the value_type of the destination Vector cannot be static_cast to from a moved reference of the Vector's value_type."
					);
				}
			}
			else
			{
				return OutValue_();
			}
		}

		template<class Out_>
		[[nodiscard]] static constexpr inline Out_ _do_conversion_matching_element_type_and_register(const data_type& in_data_)
		{
			using out_uq = typename EmuCore::TMP::remove_ref_cv<Out_>::type;
			if constexpr (out_uq::contains_multiple_registers)
			{
				return _do_array_conversion_matching_element_type_and_register<Out_>(in_data_, std::make_index_sequence<out_uq::num_registers>());
			}
			else
			{
				if constexpr (contains_multiple_registers)
				{
					return Out_(in_data_[0]);
				}
				else
				{
					return Out_(in_data_);
				}
			}
		}

		template<class Out_, std::size_t...OutRegisterIndices_>
		[[nodiscard]] static constexpr inline Out_ _do_array_conversion_matching_element_type_and_register
		(
			const data_type& in_data_,
			std::index_sequence<OutRegisterIndices_...> out_indices_
		)
		{
			using out_uq = typename EmuCore::TMP::remove_ref_cv<Out_>::type;
			using out_register = typename out_uq::register_type;
			return Out_(_convert_index_matching_width_and_register<out_register, OutRegisterIndices_>(in_data_)...);
		}

		template<class OutRegister_, std::size_t RegisterIndex_>
		[[nodiscard]] static constexpr inline OutRegister_ _convert_index_matching_width_and_register(const data_type& in_data_)
		{
			if constexpr (RegisterIndex_ < num_registers)
			{
				if constexpr (contains_multiple_registers)
				{
					return in_data_[RegisterIndex_];
				}
				else
				{
					return in_data_;
				}
			}
			else
			{
				return EmuSIMD::setzero<OutRegister_>();
			}
		}

		template<class Out_, std::size_t...OutRegisterIndices_>
		[[nodiscard]] static constexpr inline Out_ _do_conversion_all_widths_equal(const data_type& in_data_, std::index_sequence<OutRegisterIndices_...> out_indices_)
		{
			using out_vector = typename EmuCore::TMP::remove_ref_cv<Out_>::type;
			using out_register_type = typename out_vector::register_type;
			constexpr std::size_t out_per_element_width = out_vector::per_element_width;
			constexpr bool out_signed = out_vector::is_signed;
			return Out_(_convert_index_all_widths_equal<out_register_type, out_per_element_width, out_signed, OutRegisterIndices_>(in_data_)...);
		}

		template<class OutRegister_, std::size_t OutPerElementWidth_, bool OutSigned_, std::size_t RegisterIndex_>
		[[nodiscard]] static constexpr inline OutRegister_ _convert_index_all_widths_equal(const data_type& in_data_)
		{
			if constexpr (RegisterIndex_ < num_registers)
			{
				if constexpr (contains_multiple_registers)
				{
					return EmuSIMD::convert<OutRegister_, per_element_width, is_signed, OutPerElementWidth_, OutSigned_>(in_data_[RegisterIndex_]);
				}
				else
				{
					return EmuSIMD::convert<OutRegister_, per_element_width, is_signed, OutPerElementWidth_, OutSigned_>(in_data_);
				}
			}
			else
			{
				return EmuSIMD::setzero<OutRegister_>();
			}
		}
#pragma endregion

#pragma region STATIC_ASSERTION_HELPERS
	private:
		static constexpr inline bool _do_static_assert() noexcept
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
			else if constexpr (std::is_same_v<register_arg_type, void>)
			{
				static_assert
				(
					EmuCore::TMP::get_false<T_>(),
					"Unable to successfully form a register_arg_type for an EmuMath::FastVector. This is likely due to the provided T_ argument."
				);
				return false;
			}
			else
			{
				return true;
			}
		}

	public:
		static_assert(_do_static_assert(), "Unable to successfully form an EmuMath::FastVector instance.");
#pragma endregion
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
