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

		using register_type = typename EmuSIMD::TMP::register_type<value_type, register_width>::type;
		using register_arg_type = typename EmuSIMD::TMP::register_arg_type<value_type, register_width>::type;
		using shift_register_type = __m128i;
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
			return
			(
				_valid_arg_for_construct_by_scalars<X_>() &&
				_valid_arg_for_construct_by_scalars<Y_>() &&
				_valid_arg_for_construct_by_scalars<Z_>() &&
				_valid_arg_for_construct_by_scalars<W_>()
			);
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
		[[nodiscard]] static constexpr inline register_type _load_register_from_pointer(value_type* p_to_load_)
		{
			constexpr std::size_t offset = RegisterIndex_ * elements_per_register;
			return EmuSIMD::load<register_type>(p_to_load_ + offset);
		}

		template<std::size_t...RegisterIndices_>
		[[nodiscard]] static constexpr inline data_type _load_data_array_from_pointer
		(
			value_type* p_to_load_,
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

		[[nodiscard]] static constexpr inline data_type _load_data_from_pointer(value_type* p_to_load_) noexcept
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
