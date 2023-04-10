#ifndef EMU_MATH_FAST_QUATERNION_T_H_INC_
#define EMU_MATH_FAST_QUATERNION_T_H_INC_ 1

#include "_helpers/_all_fast_quaternion_helpers.h"
#include <array>

namespace EmuMath
{
	template<typename T_, std::size_t RegisterWidth_>
	struct FastQuaternion
	{
#pragma region STATIC_INFO
	public:
		static constexpr std::size_t register_width = RegisterWidth_ > 0 ? RegisterWidth_ : 1;
		using value_type = typename std::remove_cv<T_>::type;
		using this_type = EmuMath::FastQuaternion<T_, RegisterWidth_>;

		/// <summary> Alias to the type of SIMD register used for this Quaternion's data. </summary>
		using register_type = typename EmuSIMD::TMP::register_type<value_type, register_width>::type;
		/// <summary> Alias to the argument type used to pass an instance of this Quaternion's register_type. </summary>
		using register_arg_type = typename EmuSIMD::TMP::register_arg_type<value_type, register_width>::type;
		/// <summary> The preferred floating-point type for this Matrix, used for floating-point-based calculations using this Quaternion. </summary>
		using preferred_floating_point = typename std::conditional<(sizeof(value_type) >= 64), double, float>::type;

		/// <summary> Boolean indicating if this Quaternion's encapsulated type is integral. </summary>
		static constexpr bool is_integral = std::is_integral<value_type>::value;
		/// <summary> Boolean indicating if this Quaternion's encapsulated type is floating-point. </summary>
		static constexpr bool is_floating_point = std::is_floating_point<value_type>::value;
		/// <summary> Boolean indicating if this Quaternion's encapsulated type is signed. </summary>
		static constexpr bool is_signed = std::is_signed<value_type>::value;

		/// <summary> The number of bytes consumed by a single element in this Quaternion. </summary>
		static constexpr std::size_t per_element_byte_size = sizeof(value_type);
		/// <summary> The number of bits consumed by a single element in this Quaternion with 8-bit bytes, regardless of the value of CHAR_BIT. </summary>
		static constexpr std::size_t per_element_width = per_element_byte_size * 8;
		/// <summary> The total number of bits required for every element to be accounted for within this Quaternion. </summary>
		static constexpr std::size_t total_element_width = per_element_width * 4;
		/// <summary> The total number of elements accounted for within a single register. </summary>
		static constexpr std::size_t elements_per_register = register_width / per_element_width;
		/// <summary> 
		/// <para>
		///		Boolean indicating if a partial SIMD register is required to represent this full Quaternion 
		///		(for example, 192 bits are required while using 128-bit registers). 
		/// </para>
		/// </summary>
		static constexpr bool requires_partial_register = (total_element_width % register_width) != 0;
		/// <summary> The number of elements encapsulted by the partial end register if this Quaternion has one. If it does not have a partial register, this is 0. </summary>
		static constexpr std::size_t partial_register_length = requires_partial_register ? (4 % elements_per_register) : 0;
		/// <summary> The number of registers required to form this Quaternion. </summary>
		static constexpr std::size_t num_registers = (total_element_width / register_width) + requires_partial_register;
		/// <summary> Boolean indicating if the underlying implementation of this Quaternion makes use of multiple SIMD registers. </summary>
		static constexpr bool contains_multiple_registers = num_registers > 1;
		/// <summary> The total number of elements contained within this Quaternion's registers, including those exceeding its encapsulated range. </summary>
		static constexpr std::size_t full_width_size = elements_per_register * num_registers;

		/// <summary>
		/// <para> 
		///		The type used to store the register data in this Quaternion's `data` member. 
		///		An array of register_type if `contains_multiple_registers == true`. 
		///		Otherwise, aliases directly to `register_type`.
		/// </para>
		/// </summary>
		using data_type = std::conditional_t<contains_multiple_registers, std::array<register_type, num_registers>, register_type>;
		/// <summary> Standard index sequence that may be used to statically iterate over this Quaternion's encapsulated elements. </summary>
		using index_sequence = std::make_index_sequence<4>;
		/// <summary> 
		/// <para>
		///		Standard index sequence that may be used to statically iterate over every element of this Quaternion's registers, 
		///		including those exceeding its encapsulated range.
		/// </para>
		/// </summary>
		using full_width_index_sequence = std::make_index_sequence<full_width_size>;
		/// <summary> Standard index sequence that may be used to statically iterate over this Quaternion's registers if it contains multiple. </summary>
		using register_index_sequence = std::make_index_sequence<num_registers>;
#pragma endregion

#pragma region CONSTRUCTOR_VALIDITY_CHECKS
	private:
		template<typename Arg_>
		[[nodiscard]] static constexpr inline bool _valid_arg_for_construct_by_scalars() noexcept
		{
			return
			(
				std::is_same_v<typename EmuCore::TMP::remove_ref_cv<Arg_>::type, value_type> ||
				EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<Arg_>::type, value_type>
			);
		}

	public:
		/// <summary>
		/// <para> Check to determine if the passed argument types are valid for constructing this Quaternion type with per-element scalar arguments. </para>
		/// </summary>
		/// <returns>True if the provided types may be passed as respective arguments to this Quaternion's per-element constructor; otherwise false.</returns>
		template<typename X_, typename Y_, typename Z_, typename W_>
		[[nodiscard]] static constexpr inline bool valid_args_for_construct_by_scalars() noexcept
		{
			return EmuCore::TMP::variadic_and_v
			<
				_valid_arg_for_construct_by_scalars<X_>(),
				_valid_arg_for_construct_by_scalars<Y_>(),
				_valid_arg_for_construct_by_scalars<Z_>(),
				_valid_arg_for_construct_by_scalars<W_>()
			>;
		}

		/// <summary>
		/// <para> Check to determine if the passed argument types are valid for constructing this Quaternion type with variadic per-register arguments. </para>
		/// <para> This regards only the variadic constructor, so the following should be kept in mind: </para>
		/// <para> 
		///		--- 1: Where this Quaternion only contains 1 register, this will always be false as per-register construction 
		///		is handled by the explicit `data_type` copy/move constructors.
		/// </para>
		/// <para>
		///		--- 2: The passed types may have any const/volatile/reference qualification, 
		///		but ignoring qualifiers all arguments must be either this Quaternion's `register_type` or `register_arg_type`.
		/// </para>
		/// <para>
		///		--- 3: Any type may be provided to this check, but the constructor itself is constrained to the `EmuConcepts::KnownSIMD` concept. 
		///		This will, however, only return `true` where that constraint is met as the underlying register_type/register_arg_type meets the constraint.
		/// </para>
		/// </summary>
		/// <returns>
		///		True if the provided types may be passed as respective arguments to this Quaternion's per-register variadic constructor; otherwise false.
		/// </returns>
		template<class...Registers_>
		[[nodiscard]] static constexpr inline bool valid_args_for_variadic_register_constructor() noexcept
		{
			return
			(
				(sizeof...(Registers_) == num_registers) &&
				(num_registers > 1) &&
				(
					... && 
					(
						std::is_same_v<typename EmuCore::TMP::remove_ref_cv<Registers_>::type, register_type> ||
						std::is_same_v<typename EmuCore::TMP::remove_ref_cv<Registers_>::type, register_arg_type>
					)
				)
			);
		}
#pragma endregion

#pragma region CONSTRUCTION_HELPERS
	private:
		template<std::size_t RegisterIndex_, std::size_t...RegisterElementIndices_>
		[[nodiscard]] static constexpr inline register_type _make_non_zero_register_as_default
		(
			std::index_sequence<RegisterElementIndices_...> register_element_indices_
		) noexcept
		{
			constexpr std::size_t offset = RegisterIndex_ * elements_per_register;
			return EmuSIMD::setr<register_type, per_element_width>
			(
				EmuCore::TMP::conditional_value_v
				<
					(offset + RegisterElementIndices_) == 3,
					value_type,
					value_type(1),
					value_type(0)
				>...
			);
		}

		template<std::size_t RegisterIndex_>
		[[nodiscard]] static constexpr inline register_type _make_register_as_default() noexcept
		{
			constexpr std::size_t offset = RegisterIndex_ * elements_per_register;
			constexpr std::size_t register_end = offset + elements_per_register;
			if constexpr (register_end >= 4)
			{
				return _make_non_zero_register_as_default<RegisterIndex_>(std::make_index_sequence<elements_per_register>());
			}
			else
			{
				return EmuSIMD::setzero<register_type>();
			}
		}

		template<std::size_t...RegisterIndices_>
		[[nodiscard]] static constexpr inline data_type _make_data_array_as_default(std::index_sequence<RegisterIndices_...> register_indices_) noexcept
		{
			return data_type
			({
				_make_register_as_default<RegisterIndices_>()...
			});
		}

		[[nodiscard]] static constexpr inline data_type _make_data_as_default() noexcept
		{
			if constexpr (elements_per_register == 4)
			{
				return EmuSIMD::set<register_type, per_element_width>(1, 0, 0, 0);
			}
			else
			{
				if constexpr (num_registers > 1)
				{
					return _make_data_array_as_default(register_index_sequence());
				}
				else
				{
					return _make_non_zero_register_as_default<0>(std::make_index_sequence<elements_per_register>());
				}
			}
		}

		template<std::size_t Index_, typename X_, typename Y_, typename Z_, typename W_>
		[[nodiscard]] static constexpr inline decltype(auto) _get_scalar_argument(std::tuple<X_, Y_, Z_, W_>& xyzw_) noexcept
		{
			if constexpr (Index_ < 4)
			{
				using _get_result_type = decltype(std::get<Index_>(xyzw_));
				return std::forward<_get_result_type>(std::get<Index_>(xyzw_));
			}
			else
			{
				return value_type(0);
			}
		}

		template<std::size_t RegisterIndex_, typename X_, typename Y_, typename Z_, typename W_, std::size_t...RegisterElementIndices_>
		[[nodiscard]] static constexpr inline register_type _make_register_from_scalars
		(
			std::tuple<X_, Y_, Z_, W_>& xyzw_,
			std::index_sequence<RegisterElementIndices_...> register_element_indices_
		) noexcept
		{
			constexpr std::size_t index_offset = RegisterIndex_ * elements_per_register;
			return EmuSIMD::setr<register_type>
			(
				std::forward<decltype(_get_scalar_argument<index_offset + RegisterElementIndices_>(xyzw_))>
				(
					_get_scalar_argument<index_offset + RegisterElementIndices_>(xyzw_)
				)...
			);
		}

		template<typename X_, typename Y_, typename Z_, typename W_, std::size_t...RegisterIndices_>
		[[nodiscard]] static constexpr inline data_type _make_data_array_from_scalars
		(
			std::tuple<X_, Y_, Z_, W_>& xyzw_,
			std::index_sequence<RegisterIndices_...> register_indices_
		) noexcept
		{
			return data_type
			({
				_make_register_from_scalars<RegisterIndices_>
				(
					xyzw_,
					std::make_index_sequence<elements_per_register>()
				)...
			});
		}

		template<typename X_, typename Y_, typename Z_, typename W_>
		[[nodiscard]] static constexpr inline data_type _make_data_from_scalars(X_&& x_, Y_&& y_, Z_&& z_, W_&& w_) noexcept
		{
			if constexpr (elements_per_register == 4)
			{
				return EmuSIMD::set<register_type, per_element_width>
				(
					std::forward<W_>(w_),
					std::forward<Z_>(z_),
					std::forward<Y_>(y_),
					std::forward<X_>(x_)
				);
			}
			else
			{
				auto xyzw = std::forward_as_tuple(std::forward<X_>(x_), std::forward<Y_>(y_), std::forward<Z_>(z_), std::forward<W_>(w_));
				if constexpr (num_registers > 1)
				{
					return _make_data_array_from_scalars(xyzw, register_index_sequence());
				}
				else
				{
					return _make_register_from_scalars<0>(xyzw, std::make_index_sequence<elements_per_register>());
				}
			}
		}

		template<std::size_t RegisterIndex_>
		[[nodiscard]] static constexpr inline register_type _load_register_from_pointer(const value_type* p_to_load_)
		{
			constexpr std::size_t offset = RegisterIndex_ * elements_per_register;
			return EmuSIMD::load<register_type>(p_to_load_ + offset);
		}

		template<std::size_t...RegisterIndices_>
		[[nodiscard]] static constexpr inline data_type _load_data_array_from_pointer
		(
			const value_type* p_to_load_,
			std::index_sequence<RegisterIndices_...> register_indices_
		) noexcept
		{
			return data_type
			({
				_load_register_from_pointer<RegisterIndices_>
				(
					p_to_load_
				)...
			});
		}

		[[nodiscard]] static constexpr inline data_type _load_data_from_pointer(const value_type* p_to_load_) noexcept
		{
			if constexpr (num_registers > 1)
			{
				return _load_data_array_from_pointer(p_to_load_, register_index_sequence());
			}
			else
			{
				return EmuSIMD::load<register_type>(p_to_load_);
			}
		}

		template<std::size_t Index_, EmuConcepts::EmuQuaternion Quaternion_>
		[[nodiscard]] static constexpr inline decltype(auto) _get_arg_for_register_from_scalar_quaternion(Quaternion_&& in_quaternion_)
		{
			if constexpr (Index_ == 0)
			{
				return std::forward<Quaternion_>(in_quaternion_).X();
			}
			else if constexpr (Index_ == 1)
			{
				return std::forward<Quaternion_>(in_quaternion_).Y();
			}
			else if constexpr (Index_ == 2)
			{
				return std::forward<Quaternion_>(in_quaternion_).Z();
			}
			else if constexpr (Index_ == 3)
			{
				return std::forward<Quaternion_>(in_quaternion_).W();
			}
			else
			{
				return value_type(0);
			}
		}

		template<std::size_t RegisterIndex_, EmuConcepts::EmuQuaternion Quaternion_, std::size_t...RegisterElementIndices_>
		[[nodiscard]] static constexpr inline register_type _make_register_from_scalar_quaternion
		(
			Quaternion_&& in_quaternion_,
			std::index_sequence<RegisterElementIndices_...> register_element_indices_
		) noexcept
		{
			constexpr std::size_t offset = RegisterIndex_ * elements_per_register;
			return EmuSIMD::setr<register_type, per_element_width>
			(
				_get_arg_for_register_from_scalar_quaternion<offset + RegisterElementIndices_>
				(
					std::forward<Quaternion_>(in_quaternion_)
				)...
			);
		}

		template<EmuConcepts::EmuQuaternion Quaternion_, std::size_t...RegisterIndices_>
		[[nodiscard]] static constexpr inline data_type _make_data_array_from_scalar_quaternion
		(
			Quaternion_&& in_quaternion_,
			std::index_sequence<RegisterIndices_...> register_indices_
		) noexcept
		{
			return data_type
			({
				_make_register_from_scalar_quaternion<RegisterIndices_>
				(
					std::forward<Quaternion_>(in_quaternion_),
					std::make_index_sequence<elements_per_register>()
				)...
			});
		}

		template<EmuConcepts::EmuQuaternion Quaternion_>
		[[nodiscard]] static constexpr inline data_type _make_data_from_scalar_quaternion(Quaternion_&& in_quaternion_) noexcept
		{
			using _in_scalar_quat_uq = typename EmuCore::TMP::remove_ref_cv<Quaternion_>::type;
			using _in_scalar_stored_no_cv = typename std::remove_cv<typename _in_scalar_quat_uq::stored_type>::type;
			constexpr bool valid_width_for_load = (elements_per_register == 4) || (elements_per_register == 2);
			if constexpr (valid_width_for_load && std::is_same_v<value_type, _in_scalar_stored_no_cv>)
			{
				return _load_data_from_pointer(std::forward<Quaternion_>(in_quaternion_).DataPointer());
			}
			else
			{
EMU_CORE_MSVC_PUSH_WARNING_STACK
EMU_CORE_MSVC_DISABLE_WARNING(EMU_CORE_WARNING_BAD_MOVE)
				if constexpr (elements_per_register == 4)
				{
					return EmuSIMD::set<register_type>
					(
						std::forward<Quaternion_>(in_quaternion_).W(),
						std::forward<Quaternion_>(in_quaternion_).Z(),
						std::forward<Quaternion_>(in_quaternion_).Y(),
						std::forward<Quaternion_>(in_quaternion_).X()
					);
				}
				else
				{
					if constexpr (num_registers > 1)
					{
						return _make_data_array_from_scalar_quaternion
						(
							std::forward<Quaternion_>(in_quaternion_),
							register_index_sequence()
						);
					}
					else
					{
						return _make_register_from_scalar_quaternion<0>
						(
							std::forward<Quaternion_>(in_quaternion_),
							std::make_index_sequence<elements_per_register>()
						);
					}
				}
EMU_CORE_MSVC_POP_WARNING_STACK
			}
		}
#pragma endregion

#pragma region CONSTRUCTORS
	public:
		constexpr inline FastQuaternion() noexcept
			: data(_make_data_as_default())
		{
		}
		constexpr inline FastQuaternion(const this_type&) noexcept = default;
		constexpr inline FastQuaternion(this_type&&) noexcept = default;

		explicit constexpr inline FastQuaternion(const data_type& data_to_copy_) noexcept
			: data(data_to_copy_)
		{
		}

		explicit constexpr inline FastQuaternion(data_type&& data_to_move_) noexcept
			: data(std::move(data_to_move_))
		{
		}

		explicit constexpr inline FastQuaternion(const value_type* p_to_load_) noexcept
			: data(_load_data_from_pointer(p_to_load_))
		{
		}

		template<typename X_, typename Y_, typename Z_, typename W_, typename = std::enable_if_t<valid_args_for_construct_by_scalars<X_, Y_, Z_, W_>()>>
		constexpr inline FastQuaternion(X_&& x_, Y_&& y_, Z_&& z_, W_&& w_) noexcept
			: data(_make_data_from_scalars(std::forward<X_>(x_), std::forward<Y_>(y_), std::forward<Z_>(z_), std::forward<W_>(w_)))
		{
		}

		template<EmuConcepts::KnownSIMD...Registers_, typename = std::enable_if_t<valid_args_for_variadic_register_constructor<Registers_...>()>>
		constexpr inline FastQuaternion(Registers_&&...registers_) noexcept
			: data({ std::forward<Registers_>(registers_)... })
		{
		}

		template<EmuConcepts::EmuQuaternion Quaternion_>
		explicit constexpr inline FastQuaternion(Quaternion_&& in_quaternion_) noexcept
			: data(_make_data_from_scalar_quaternion(std::forward<Quaternion_>(in_quaternion_)))
		{
		}
#pragma endregion

#pragma region GETTERS
	public:
		template<std::size_t RegisterIndex_>
		[[nodiscard]] constexpr inline register_type& GetRegister() noexcept
		{
			if constexpr (RegisterIndex_ < num_registers)
			{
				if constexpr (num_registers > 1)
				{
					return data[RegisterIndex_];
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
					EmuCore::TMP::get_false<RegisterIndex_>(),
					"Attempted to retrieve a register from an EmuMath FastQuaternion, but the provided index exceeds the highest register index within the Quaternion."
				);
			}
		}

		template<std::size_t RegisterIndex_>
		[[nodiscard]] constexpr inline const register_type& GetRegister() const noexcept
		{
			return const_cast<this_type*>(this)->template GetRegister<RegisterIndex_>();
		}

		template<typename Out_>
		requires (!std::is_const_v<Out_>)
		constexpr inline void Store(Out_* p_out_) const noexcept
		{
			EmuMath::Helpers::fast_quaternion_store(*this, p_out_);
		}

		template<typename OutT_>
		constexpr inline void Store(EmuMath::Quaternion<OutT_>& out_quaternion_) const noexcept
		{
			EmuMath::Helpers::fast_quaternion_store(*this, out_quaternion_);
		}

		template<typename OutT_ = value_type>
		[[nodiscard]] constexpr inline auto Store() const noexcept
			-> std::enable_if_t
			<
				std::is_constructible_v<EmuMath::Quaternion<OutT_>, value_type&&, value_type&&, value_type&&, value_type&&>,
				EmuMath::Quaternion<OutT_>
			>
		{
			return EmuMath::Helpers::fast_quaternion_store<OutT_>(*this);
		}
#pragma endregion

#pragma region ASSIGNMENT_OPERATORS
	public:
		constexpr inline this_type& operator=(const this_type&) noexcept = default;
		constexpr inline this_type& operator=(this_type&&) noexcept = default;
#pragma endregion

#pragma region CONST_ARITHMETIC_FUNCS
	public:
		/// <summary>
		/// <para> Adds this Quaternion and the passed `rhs_` Quaternion. </para>
		/// </summary>
		/// <returns>FastQuaternion of the same type containing the results of the addition operation.</returns>
		[[nodiscard]] constexpr inline auto Add(const EmuMath::FastQuaternion<T_, RegisterWidth_>& rhs_) const
			-> EmuMath::FastQuaternion<T_, RegisterWidth_>
		{
			return EmuMath::Helpers::fast_quaternion_add(*this, rhs_);
		}

		/// <summary>
		/// <para> Subtracts the passed `rhs_` Quaternion from this Quaternion. </para>
		/// </summary>
		/// <returns>FastQuaternion of the same type containing the results of the subtraction operation.</returns>
		[[nodiscard]] constexpr inline auto Subtract(const EmuMath::FastQuaternion<T_, RegisterWidth_>& rhs_) const
			-> EmuMath::FastQuaternion<T_, RegisterWidth_>
		{
			return EmuMath::Helpers::fast_quaternion_subtract(*this, rhs_);
		}

		/// <summary>
		/// <para> Divides this Quaternion's underlying register(s) by the passed `rhs_scalar_register_` register. </para>
		/// <para> The passed register should contain the same value in all respective lanes for most cases of standard Quaternion division. </para>
		/// </summary>
		/// <returns>FastQuaternion of the same type containing the results of the division operation.</returns>
		[[nodiscard]] constexpr inline auto Divide(register_arg_type rhs_scalar_register_) const
			-> EmuMath::FastQuaternion<T_, RegisterWidth_>
		{
			return EmuMath::Helpers::fast_quaternion_divide(*this, rhs_scalar_register_);
		}

		/// <summary>
		/// <para> Divides this Quaternion by the passed `rhs_scalar_` value. </para>
		/// <para> An intermediate register will be created to perform this operation. </para>
		/// </summary>
		/// <returns>FastQuaternion of the same type containing the results of the division operation.</returns>
		template<EmuConcepts::Arithmetic RhsScalar_>
		[[nodiscard]] constexpr inline auto Divide(RhsScalar_&& rhs_scalar_) const
			-> EmuMath::FastQuaternion<T_, RegisterWidth_>
		{
			return EmuMath::Helpers::fast_quaternion_divide(*this, std::forward<RhsScalar_>(rhs_scalar_));
		}

		/// <summary>
		/// <para> Multiplies this Quaternion with the passed `rhs_` Quaternion. </para>
		/// </summary>
		/// <returns>FastQuaternion of the same type containing the results of the Quaternion multiplication operation.</returns>
		[[nodiscard]] constexpr inline auto MultiplyQuaternion(const EmuMath::FastQuaternion<T_, RegisterWidth_>& rhs_) const
			-> EmuMath::FastQuaternion<T_, RegisterWidth_>
		{
			return EmuMath::Helpers::fast_quaternion_multiply_quaternion(*this, rhs_);
		}

		/// <summary>
		/// <para> Multiplies this Quaternion's underlying register(s) by the passed `rhs_scalar_register_` register. </para>
		/// <para> The passed register should contain the same value in all respective lanes for most cases of standard Quaternion x Scalar multiplication. </para>
		/// </summary>
		/// <returns>FastQuaternion of the same type containing the results of the multiplication operation.</returns>
		[[nodiscard]] constexpr inline auto MultiplyScalar(register_arg_type rhs_scalar_register_) const
			-> EmuMath::FastQuaternion<T_, RegisterWidth_>
		{
			return EmuMath::Helpers::fast_quaternion_multiply_scalar(*this, rhs_scalar_register_);
		}

		/// <summary>
		/// <para> Multiplies this Quaternion's underlying register(s) by the passed `rhs_scalar_register_` register. </para>
		/// <para> An intermediate register will be created to perform this operation. </para>
		/// </summary>
		/// <returns>FastQuaternion of the same type containing the results of the multiplication operation.</returns>
		template<EmuConcepts::Arithmetic RhsScalar_>
		[[nodiscard]] constexpr inline auto MultiplyScalar(RhsScalar_&& rhs_scalar_) const
			-> EmuMath::FastQuaternion<T_, RegisterWidth_>
		{
			return EmuMath::Helpers::fast_quaternion_multiply_scalar(*this, std::forward<RhsScalar_>(rhs_scalar_));
		}
#pragma endregion

#pragma region ARITHMETIC_ASSIGN_FUNCS
	public:
		/// <summary>
		/// <para> Adds this Quaternion and the passed `rhs_` Quaternion. </para>
		/// <para> Results of the operation are assigned to this FastQuaternion. </para>
		/// </summary>
		constexpr inline void AddAssign(const EmuMath::FastQuaternion<T_, RegisterWidth_>& rhs_)
		{
			EmuMath::Helpers::fast_quaternion_add_assign(*this, rhs_);
		}

		/// <summary>
		/// <para> Subtracts the passed `rhs_` Quaternion from this Quaternion. </para>
		/// <para> Results of the operation are assigned to this FastQuaternion. </para>
		/// </summary>
		constexpr inline void SubtractAssign(const EmuMath::FastQuaternion<T_, RegisterWidth_>& rhs_)
		{
			EmuMath::Helpers::fast_quaternion_subtract_assign(*this, rhs_);
		}

		/// <summary>
		/// <para> Divides this Quaternion's underlying register(s) by the passed `rhs_scalar_register_` register. </para>
		/// <para> The passed register should contain the same value in all respective lanes for most cases of standard Quaternion division. </para>
		/// <para> Results of the operation are assigned to this FastQuaternion. </para>
		/// </summary>
		constexpr inline void DivideAssign(register_arg_type rhs_scalar_register_)
		{
			EmuMath::Helpers::fast_quaternion_divide_assign(*this, rhs_scalar_register_);
		}

		/// <summary>
		/// <para> Divides this Quaternion by the passed `rhs_scalar_` value. </para>
		/// <para> An intermediate register will be created to perform this operation. </para>
		/// <para> Results of the operation are assigned to this FastQuaternion. </para>
		/// </summary>
		template<EmuConcepts::Arithmetic RhsScalar_>
		constexpr inline void DivideAssign(RhsScalar_&& rhs_scalar_)
		{
			EmuMath::Helpers::fast_quaternion_divide_assign(*this, std::forward<RhsScalar_>(rhs_scalar_));
		}

		/// <summary>
		/// <para> Multiplies this Quaternion with the passed `rhs_` Quaternion. </para>
		/// <para> Results of the operation are assigned to this FastQuaternion. </para>
		/// </summary>
		constexpr inline void MultiplyAssignQuaternion(const EmuMath::FastQuaternion<T_, RegisterWidth_>& rhs_)
		{
			EmuMath::Helpers::fast_quaternion_multiply_assign_quaternion(*this, rhs_);
		}

		/// <summary>
		/// <para> Multiplies this Quaternion's underlying register(s) by the passed `rhs_scalar_register_` register. </para>
		/// <para> The passed register should contain the same value in all respective lanes for most cases of standard Quaternion x Scalar multiplication. </para>
		/// <para> Results of the operation are assigned to this FastQuaternion. </para>
		/// </summary>
		constexpr inline void MultiplyAssignScalar(register_arg_type rhs_scalar_register_)
		{
			EmuMath::Helpers::fast_quaternion_multiply_assign_scalar(*this, rhs_scalar_register_);
		}

		/// <summary>
		/// <para> Multiplies this Quaternion by the passed `rhs_scalar_` value. </para>
		/// <para> An intermediate register will be created to perform this operation. </para>
		/// <para> Results of the operation are assigned to this FastQuaternion. </para>
		/// </summary>
		template<EmuConcepts::Arithmetic RhsScalar_>
		constexpr inline void MultiplyAssignScalar(RhsScalar_&& rhs_scalar_)
		{
			EmuMath::Helpers::fast_quaternion_multiply_assign_scalar(*this, std::forward<RhsScalar_>(rhs_scalar_));
		}
#pragma endregion

#pragma region COMPARISON_FUNCS
		[[nodiscard]] constexpr inline bool CmpEqual(const EmuMath::FastQuaternion<T_, RegisterWidth_>& rhs_) const noexcept
		{
			return EmuMath::Helpers::fast_quaternion_cmp_equal(*this, rhs_);
		}

		[[nodiscard]] constexpr inline bool CmpNotEqual(const EmuMath::FastQuaternion<T_, RegisterWidth_>& rhs_) const noexcept
		{
			return EmuMath::Helpers::fast_quaternion_cmp_not_equal(*this, rhs_);
		}

		[[nodiscard]] constexpr inline bool CmpNear(const EmuMath::FastQuaternion<T_, RegisterWidth_>& rhs_) const noexcept
		{
			return EmuMath::Helpers::fast_quaternion_cmp_near(*this, rhs_);
		}

		[[nodiscard]] constexpr inline bool CmpNear(const EmuMath::FastQuaternion<T_, RegisterWidth_>& rhs_, register_arg_type epsilon_) const noexcept
		{
			return EmuMath::Helpers::fast_quaternion_cmp_near(*this, rhs_, epsilon_);
		}

		[[nodiscard]] constexpr inline bool CmpNear
		(
			const EmuMath::FastQuaternion<T_, RegisterWidth_>& rhs_,
			const EmuMath::FastQuaternion<T_, RegisterWidth_>& epsilon_
		) const noexcept
		{
			return EmuMath::Helpers::fast_quaternion_cmp_near(*this, rhs_, epsilon_);
		}
#pragma endregion

#pragma region TO_EULER_FUNCTIONS
	public:
		/// <summary>
		/// <para> Converts this Quaternion to euler angles XYZ, returning the result as a scalar EmuMath Vector. </para>
		/// <para> The output Vector's contained type/size may be customised. By default, they are `preferred_floating_point`/`3`, respectively. </para>
		/// <para> If the output Vector's contained type is `void`, it will instead use this Quaternion's `preferred_floating_point`. </para>
		/// </summary>
		/// <param name="epsilon_">
		///		Arithmetic value indicating the epsilon to use for floating-point comparisons in conversions. 
		///		This may be omitted, in which case the function will use the default epsilon of this Quaternion's `preferred_floating_point` type, 
		///		as determined by `EmuCore::epsilon`.
		/// </param>
		/// <returns>Scalar EmuMath Vector containing the results of converting this Quaternion to euler angles.</returns>
		template<bool OutRads_ = true, typename OutT_ = preferred_floating_point, std::size_t OutSize_ = 3, EmuConcepts::Arithmetic Epsilon_>
		[[nodiscard]] constexpr inline auto ToEulerScalar(Epsilon_&& epsilon_) const noexcept
		{
			return EmuMath::Helpers::fast_quaternion_to_euler_scalar<OutRads_, OutT_, OutSize_>(*this, std::forward<Epsilon_>(epsilon_));
		}

		template<bool OutRads_ = true, typename OutT_ = preferred_floating_point, std::size_t OutSize_ = 3>
		[[nodiscard]] constexpr inline auto ToEulerScalar() const noexcept
		{
			return EmuMath::Helpers::fast_quaternion_to_euler_scalar<OutRads_, OutT_, OutSize_>(*this);
		}

		/// <summary>
		/// <para> Converts this Quaternion to euler angles XYZ, returning the result as an EmuMath FastVector. </para>
		/// <para> The output Vector's T_ argument will always be the `preferred_floating_point` of this Quaternion. </para>
		/// <para> The output Vector's size may be customised. By default, it is 3. </para>
		/// <para> The output Vector's register width may be customised. By default, it is the `register_width` of this Quaternion. </para>
		/// <para> If the output Vector's register width is 0, it will instead use the `register_width` of this Quaternion. </para>
		/// </summary>
		/// <param name="epsilon_">
		///		Arithmetic value indicating the epsilon to use for floating-point comparisons in conversions. 
		///		This may be omitted, in which case the function will use the default epsilon of the input Quaternion's `preferred_floating_point` type, 
		///		as determined by `EmuCore::epsilon`.
		/// </param>
		/// <returns>EmuMath Fast Vector containing the results of converting this Quaternion to euler angles.</returns>
		template<bool OutRads_ = true, std::size_t OutSize_ = 3, std::size_t OutRegisterWidth_ = register_width, EmuConcepts::Arithmetic Epsilon_>
		[[nodiscard]] constexpr inline auto ToEuler(Epsilon_&& epsilon_) const noexcept
		{
			return EmuMath::Helpers::fast_quaternion_to_euler<OutRads_, OutSize_, OutRegisterWidth_>(*this, std::forward<Epsilon_>(epsilon_));
		}

		template<bool OutRads_ = true, std::size_t OutSize_ = 3, std::size_t OutRegisterWidth_ = register_width>
		[[nodiscard]] constexpr inline auto ToEuler() const noexcept
		{
			return EmuMath::Helpers::fast_quaternion_to_euler<OutRads_, OutSize_, OutRegisterWidth_>(*this);
		}
#pragma endregion

#pragma region FROM_EULER_FUNCTIONS
	public:
		/// <summary>
		/// <para> Creates a FastQuaternion from euler angles, using SIMD operations to perform the conversion. </para>
		/// <para> If `InRads_` is `true`, euler angles will be interpreted in radians; otherwise, they will be interpreted as degrees. Defaults to `true`. </para>
		/// <para> If `Normalise_` is `true`, a normalisation operation will be performed before returning. Defaults to `true`. </para>
		/// </summary>
		/// <param name="euler_x_">Euler angle in radians or degrees (based on `InRads_` template argument) in the X-axis to convert to a Quaternion.</param>
		/// <param name="euler_y_">Euler angle in radians or degrees (based on `InRads_` template argument) in the Y-axis to convert to a Quaternion.</param>
		/// <param name="euler_z_">Euler angle in radians or degrees (based on `InRads_` template argument) in the Z-axis to convert to a Quaternion.</param>
		/// <returns>FastQuaternion of this type representing the provided Euler rotation in Quaternion form.</returns>
		template<bool InRads_ = true, bool Normalise_ = true, EmuConcepts::Arithmetic X_, EmuConcepts::Arithmetic Y_, EmuConcepts::Arithmetic Z_>
		[[nodiscard]] static constexpr inline auto from_euler(X_&& euler_x_, Y_&& euler_y_, Z_&& euler_z_) noexcept
			-> EmuMath::FastQuaternion<T_, RegisterWidth_>
		{
			return EmuMath::Helpers::fast_quaternion_from_euler<EmuMath::FastQuaternion<T_, RegisterWidth_>, InRads_, Normalise_>
			(
				std::forward<X_>(euler_x_),
				std::forward<Y_>(euler_y_),
				std::forward<Z_>(euler_z_)
			);
		}

		/// <summary>
		/// <para> Creates a FastQuaternion from euler angles, using SIMD operations to perform the conversion. </para>
		/// <para> If `InRads_` is `true`, euler angles will be interpreted in radians; otherwise, they will be interpreted as degrees. Defaults to `true`. </para>
		/// <para> If `Normalise_` is `true`, a normalisation operation will be performed before returning. Defaults to `true`. </para>
		/// </summary>
		/// <param name="euler_xyz_">
		///		Vector of Euler angles in radians or degrees (based on `InRads_` template argument) in the X-axis to convert to a Quaternion. 
		///		If a required index is not contained, it will be interpreted as 0 (i.e. no rotation in that axis).
		/// </param>
		/// <returns>FastQuaternion of this type representing the provided Euler rotation in Quaternion form.</returns>
		template<bool InRads_ = true, bool Normalise_ = true, EmuConcepts::EmuVector EulerVector_>
		requires (EmuMath::Helpers::valid_single_arg_for_fast_quaternion_from_euler<EmuMath::FastQuaternion<T_, RegisterWidth_>, EulerVector_>())
		[[nodiscard]] static constexpr inline auto from_euler(EulerVector_&& euler_xyz_) noexcept
		{
			return EmuMath::Helpers::fast_quaternion_from_euler<EmuMath::FastQuaternion<T_, RegisterWidth_>, InRads_, Normalise_>
			(
				std::forward<EulerVector_>(euler_xyz_)
			);
		}

		/// <summary>
		/// <para> Creates a FastQuaternion from euler angles, using SIMD operations to perform the conversion. </para>
		/// <para>
		///		The passed `EulerFastVector_` must be an EmuMath FastVector which contains at least 3 elements, 
		///		and shares the same `register_type` as this FastQuaternion.
		/// </para>
		/// <para> If `InRads_` is `true`, euler angles will be interpreted in radians; otherwise, they will be interpreted as degrees. Defaults to `true`. </para>
		/// <para> If `Normalise_` is `true`, a normalisation operation will be performed before returning. Defaults to `true`. </para>
		/// </summary>
		/// <param name="euler_xyz_">
		///		EmuMath FastVector of Euler angles in radians or degrees (based on `InRads_` template argument) in the X-axis to convert to a Quaternion.
		/// </param>
		/// <returns>FastQuaternion of this type representing the provided Euler rotation in Quaternion form.</returns>
		template<bool InRads_ = true, bool Normalise_ = true, EmuConcepts::EmuFastVector EulerFastVector_>
		requires (EmuMath::Helpers::valid_single_arg_for_fast_quaternion_from_euler<EmuMath::FastQuaternion<T_, RegisterWidth_>, EulerFastVector_>())
		[[nodiscard]] static constexpr inline auto from_euler(EulerFastVector_&& euler_xyz_) noexcept
		{
			return EmuMath::Helpers::fast_quaternion_from_euler<EmuMath::FastQuaternion<T_, RegisterWidth_>, InRads_, Normalise_>
			(
				std::forward<EulerFastVector_>(euler_xyz_)
			);
		}

		/// <summary>
		/// <para> Creates a FastQuaternion from euler angles, using SIMD operations to perform the conversion. </para>
		/// <para> If `InRads_` is `true`, euler angles will be interpreted in radians; otherwise, they will be interpreted as degrees. Defaults to `true`. </para>
		/// <para> If `Normalise_` is `true`, a normalisation operation will be performed before returning. Defaults to `true`. </para>
		/// </summary>
		/// <param name="euler_xyz_">
		///		SIMD register of this FastQuaternion's `register_type`, 
		///		containing Euler angles in radians or degrees (based on `InRads_` template argument) in the X-axis to convert to a Quaternion.
		/// </param>
		/// <returns>FastQuaternion of this type representing the provided Euler rotation in Quaternion form.</returns>
		template<bool InRads_ = true, bool Normalise_ = true>
		requires (EmuMath::Helpers::valid_single_arg_for_fast_quaternion_from_euler<EmuMath::FastQuaternion<T_, RegisterWidth_>, register_arg_type>())
		[[nodiscard]] static constexpr inline auto from_euler(register_arg_type euler_xyz_simd_) noexcept
		{
			return EmuMath::Helpers::fast_quaternion_from_euler<EmuMath::FastQuaternion<T_, RegisterWidth_>, InRads_, Normalise_>
			(
				std::forward<register_arg_type>(euler_xyz_simd_)
			);
		}

		/// <summary>
		/// <para> Creates a FastQuaternion from euler angles, using SIMD operations to perform the conversion. </para>
		/// <para> If `InRads_` is `true`, euler angles will be interpreted in radians; otherwise, they will be interpreted as degrees. Defaults to `true`. </para>
		/// <para> If `Normalise_` is `true`, a normalisation operation will be performed before returning. Defaults to `true`. </para>
		/// </summary>
		/// <param name="euler_xyz_">
		///		Standard array populated with any number of SIMD registers of this FastQuaternion's `register_type`, 
		///		containing Euler angles in radians or degrees (based on `InRads_` template argument) in the X-axis to convert to a Quaternion.
		/// </param>
		/// <returns>FastQuaternion of this type representing the provided Euler rotation in Quaternion form.</returns>
		template<bool InRads_ = true, bool Normalise_ = true, std::size_t ArraySize_>
		requires
		(
			EmuMath::Helpers::valid_single_arg_for_fast_quaternion_from_euler
			<
				EmuMath::FastQuaternion<T_, RegisterWidth_>,
				std::array<register_type, ArraySize_>
			>()
		)
		[[nodiscard]] static constexpr inline auto from_euler(const std::array<register_type, ArraySize_>& euler_xyz_simd_array_) noexcept
		{
			return EmuMath::Helpers::fast_quaternion_from_euler<EmuMath::FastQuaternion<T_, RegisterWidth_>, InRads_, Normalise_>
			(
				euler_xyz_simd_array_
			);
		}
#pragma endregion

#pragma region QUATERNION_OPERATIONS
	public:
		/// <summary>
		/// <para> Outputs the squared Norm (aka: Length) of this Quaternion as the specified scalar type (defaulting to this Quaternion's `preferred_floating_point`). </para>
		/// </summary>
		/// <returns>The squared Norm of this Quaternion, represented as a scalar value.</returns>
		template<EmuConcepts::Arithmetic OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto SquareNormScalar() const
			-> OutT_
		{
			return EmuMath::Helpers::fast_quaternion_square_norm_scalar<OutT_>(*this);
		}

		/// <summary>
		/// <para> Outputs the squared Norm (aka: Length) of this Quaternion within all elements of a SIMD register. </para>
		/// </summary>
		/// <returns>The squared Norm of this Quaternion, represented as a SIMD register of this Quaternion's `register_type`.</returns>
		[[nodiscard]] constexpr inline auto SquareNorm() const
			-> register_type
		{
			return EmuMath::Helpers::fast_quaternion_square_norm(*this);
		}

		/// <summary>
		/// <para> Outputs the Norm (aka: Length) of this Quaternion as the specified scalar type (defaulting to this Quaternion's `preferred_floating_point`). </para>
		/// </summary>
		/// <returns>The Norm of this Quaternion, represented as a scalar value.</returns>
		template<EmuConcepts::Arithmetic OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto NormScalar() const
			-> OutT_
		{
			return EmuMath::Helpers::fast_quaternion_norm_scalar<OutT_>(*this);
		}


		/// <summary>
		/// <para> Outputs the Norm (aka: Length) of this Quaternion within all elements of a SIMD register. </para>
		/// </summary>
		/// <returns>The Norm of this Quaternion, represented as a SIMD register of this Quaternion's `register_type`.</returns>
		[[nodiscard]] constexpr inline auto Norm() const
			-> register_type
		{
			return EmuMath::Helpers::fast_quaternion_norm(*this);
		}

		/// <summary>
		/// <para> Outputs a new FastQuaternion that is the result of linearly interpolating this Quaternion with Quaternion b_ and a weighting of t_. </para>
		/// <para> Typically, Slerp (Spherical linear interpolation) is likely to be preferred for smoother interpolations. </para>
		/// <para> The resulting Quaternion is not automatically normalised, so arguments that may result in a non-unit Quaternion should be considered. </para>
		/// </summary>
		/// <param name="b_">Target to linearly interpolate respective elements of this Quaternion to. May be a FastQuaternion of the same type, this FastQuaternion's `register_type`, or a scalar arithmetic type.</param>
		/// <param name="t_">Weighting for interpolation of respective elements. May be a FastQuaternion of the same type, this FastQuaternion's `register_type`, or a scalar arithmetic type.</param>
		/// <returns>Quaternion resulting from the linear interpolation.</returns>
		template<EmuConcepts::EmuFastQuaternionLerpArg<this_type> B_, EmuConcepts::EmuFastQuaternionLerpArg<this_type> Weighting_>
		[[nodiscard]] constexpr inline auto Lerp(B_&& b_, Weighting_&& t_) const
			-> EmuMath::FastQuaternion<T_, RegisterWidth_>
		{
			return EmuMath::Helpers::fast_quaternion_lerp(*this, std::forward<B_>(b_), std::forward<Weighting_>(t_));
		}

		/// <summary>
		/// <para> Outputs a new FastQuaternion that is the result of linearly interpolating this Quaternion with Quaternion b_ and a weighting of t_. </para>
		/// <para> Typically, Slerp (Spherical linear interpolation) is likely to be preferred for smoother interpolations. </para>
		/// <para> The resulting Quaternion is not automatically normalised, so arguments that may result in a non-unit Quaternion should be considered. </para>
		/// <para> This function is allowed to use fused operations (such as `fmadd`) to potentially increase efficiency and/or accuracy. </para>
		/// </summary>
		/// <param name="b_">Target to linearly interpolate respective elements of this Quaternion to. May be a FastQuaternion of the same type, this FastQuaternion's `register_type`, or a scalar arithmetic type.</param>
		/// <param name="t_">Weighting for interpolation of respective elements. May be a FastQuaternion of the same type, this FastQuaternion's `register_type`, or a scalar arithmetic type.</param>
		/// <returns>Quaternion resulting from the linear interpolation.</returns>
		template<EmuConcepts::EmuFastQuaternionLerpArg<this_type> B_, EmuConcepts::EmuFastQuaternionLerpArg<this_type> Weighting_>
		[[nodiscard]] constexpr inline auto FusedLerp(B_&& b_, Weighting_&& t_) const
			-> EmuMath::FastQuaternion<T_, RegisterWidth_>
		{
			return EmuMath::Helpers::fast_quaternion_fused_lerp(*this, std::forward<B_>(b_), std::forward<Weighting_>(t_));
		}

		/// <summary>
		/// <para> Outputs a new FastQuaternion that is the result of a spherical linear interpolation of this Quaternion with Quaternion b_ and a weighting of t_. </para>
		/// <para> Typically, this is likely to be preferred over a plain Lerp for smoother interpolations, however it will only work correctly with Unit Quaternions. </para>
		/// <para> The resulting Quaternion is not automatically normalised, so arguments that may result in a non-unit Quaternion should be considered. </para>
		/// </summary>
		/// <param name="b_">FastQuaternion of the same type to spherically linearly interpolate this Quaternion with.</param>
		/// <param name="t_">
		///		Weighting for interpolation. May be a FastQuaternion of the same type, this FastQuaternion's `register_type`, or a scalar arithmetic type. 
		///		If providing any argument other than a scalar arithmetic type, it is recommended that respective index values within this are identical.
		/// </param>
		/// <returns>Quaternion resulting from the spherical linear interpolation.</returns>
		template<EmuConcepts::EmuFastQuaternionLerpArg<this_type> Weighting_>
		[[nodiscard]] constexpr inline auto Slerp(const EmuMath::FastQuaternion<T_, RegisterWidth_>& b_, Weighting_&& t_) const
		{
			return EmuMath::Helpers::fast_quaternion_slerp(*this, b_, std::forward<Weighting_>(t_));
		}

		/// <summary>
		/// <para> Outputs a new FastQuaternion that is the result of a spherical linear interpolation of this Quaternion with Quaternion b_ and a weighting of t_. </para>
		/// <para> Typically, this is likely to be preferred over a plain Lerp for smoother interpolations, however it will only work correctly with Unit Quaternions. </para>
		/// <para> The resulting Quaternion is not automatically normalised, so arguments that may result in a non-unit Quaternion should be considered. </para>
		/// <para> This function is allowed to use fused operations (such as `fmadd`) to potentially increase efficiency and/or accuracy. </para>
		/// </summary>
		/// <param name="b_">FastQuaternion of the same type to spherically linearly interpolate this Quaternion with.</param>
		/// <param name="t_">
		///		Weighting for interpolation. May be a FastQuaternion of the same type, this FastQuaternion's `register_type`, or a scalar arithmetic type. 
		///		If providing any argument other than a scalar arithmetic type, it is recommended that respective index values within this are identical.
		/// </param>
		/// <returns>Quaternion resulting from the spherical linear interpolation.</returns>
		template<EmuConcepts::EmuFastQuaternionLerpArg<this_type> Weighting_>
		[[nodiscard]] constexpr inline auto FusedSlerp(const EmuMath::FastQuaternion<T_, RegisterWidth_>& b_, Weighting_&& t_) const
		{
			return EmuMath::Helpers::fast_quaternion_fused_slerp(*this, b_, std::forward<Weighting_>(t_));
		}

		/// <summary>
		/// <para> Returns the form of this Quaternion with its imaginary component (i.e. X, Y, Z) negated. </para>
		/// </summary>
		/// <returns>Quaternion representing this Quaternion's conjugate.</returns>
		[[nodiscard]] constexpr inline auto Conjugate() const
		{
			return EmuMath::Helpers::fast_quaternion_conjugate(*this);
		}

		/// <summary>
		/// <para> Returns the inverse form of this Quaternion, which is equivalent to its Conjugate normalised. </para>
		/// <para>
		///		If this Quaternion is known to have a norm (or length) of 1, this is mathematically identical to `Conjugate`, 
		///		although floating-point errors may produce different results.
		/// </para>
		/// <para> May optionally choose reciprocal multiplication instead of division for normalisation. If `PreferMultiplies_` is omitted, it will be considered `false`. </para>
		/// </summary>
		/// <returns>Quaternion representing the inverse of this Quaternion.</returns>
		template<bool PreferMultiplies_ = false>
		[[nodiscard]] constexpr inline auto Inverse() const
		{
			return EmuMath::Helpers::fast_quaternion_inverse<PreferMultiplies_>(*this);
		}

		/// <summary>
		/// <para> Outputs the Unit form of this Quaternion (aka: its normalised form). </para>
		/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
		/// </summary>
		/// <returns>A normalised copy of this Quaternion.</returns>
		template<bool PreferMultiplies_ = false>
		[[nodiscard]] constexpr inline auto Unit() const
		{
			return EmuMath::Helpers::fast_quaternion_unit<PreferMultiplies_>(*this);
		}

		/// <summary>
		/// <para> Sets this Quaternion to its unit (aka: normalised) form. </para>
		/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
		/// </summary>
		template<bool PreferMultiplies_ = false>
		constexpr inline void AssignUnit()
		{
			EmuMath::Helpers::fast_quaternion_assign_unit<PreferMultiplies_>(*this);
		}
#pragma endregion

#pragma region DATA
	public:
		/// <summary>
		/// <para> Register (or collection of registers if `contains_multiple_registers == true`) used for operations with this Quaternion. </para>
		/// <para>
		///		Although this may be interacted with directly, 
		///		it is recommended to only touch it if you know what you are doing with Quaternions as well as SIMD intrinsic types/functions. 
		/// </para>
		/// </summary>
		data_type data;
#pragma endregion
	};
}

template<typename T_, std::size_t RegisterWidth_>
inline std::ostream& operator<<(std::ostream& str_, const EmuMath::FastQuaternion<T_, RegisterWidth_>& quaternion_)
{
	str_ << quaternion_.Store();
	return str_;
}

template<typename T_, std::size_t RegisterWidth_>
inline std::wostream& operator<<(std::wostream& w_str_, const EmuMath::FastQuaternion<T_, RegisterWidth_>& quaternion_)
{
	w_str_ << quaternion_.Store();
	return w_str_;
}

#endif
