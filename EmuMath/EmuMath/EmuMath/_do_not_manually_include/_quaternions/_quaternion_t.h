#ifndef EMU_MATH_QUATERNION_T_H_INC_
#define EMU_MATH_QUATERNION_T_H_INC_ 1

#include "_helpers/_all_helpers.h"
#include <ostream>

namespace EmuMath
{
	/// <summary>
	/// <para> Complex 4D number which has an imaginary 3D component, XYZ, and a real single component, W. </para>
	/// <para> Commonly used to represent rotations in 3D space whilst minimising gimbal lock. </para>
	/// </summary>
	template<typename T_>
	struct Quaternion
	{
#pragma region COMMON_ALIASES
	public:
		template<typename OtherT_> friend struct Quaternion;

		using this_type = Quaternion<T_>;
		/// <summary> The type used to represent this Quaternion exactly as a Vector. </summary>
		using vector_type = EmuMath::Vector<4, T_>;

		/// <summary> The type of values stored in this Quaternion. </summary>
		using stored_type = typename vector_type::stored_type;
		/// <summary> The qualified type used by this Quaternion's common interface. </summary>
		using value_type = typename vector_type::value_type;
		/// <summary> The unqualified form of the type used by this Quaternion's common interface. </summary>
		using value_type_uq = typename vector_type::value_type_uq;
		/// <summary> The preferred floating point for this Quaternion to prefer the use of based on its value type, should it not be integral. </summary>
		using preferred_floating_point = typename vector_type::preferred_floating_point;
#pragma endregion

#pragma region COMMON_INFO
	public:
		static constexpr std::size_t euler_cvt_default_read_offset = 0;
		static constexpr bool euler_cvt_default_prefer_multiplies = false;
		static constexpr bool euler_cvt_default_is_rads = true;
		static constexpr bool euler_cvt_default_normalise = true;
		static constexpr bool euler_cvt_default_fused = false;
		static constexpr bool euler_cvt_default_is_constexpr = false;

		static constexpr bool contains_ref = vector_type::contains_ref;
		static constexpr bool contains_const_ref = vector_type::contains_const_ref;
		static constexpr bool contains_non_const_ref = vector_type::contains_non_const_ref;
#pragma endregion

#pragma region DUMMY_TEMPLATE_FUNCS
	private:
		template<std::size_t Unused_>
		[[nodiscard]] static constexpr inline bool _can_scalar_multiply_assign()
		{
			return Unused_ >= 0 && EmuMath::Helpers::quaternion_can_scalar_multiply_assign<T_, const preferred_floating_point&, false>();
		}

		template<std::size_t Unused_>
		[[nodiscard]] static constexpr inline bool _can_negate_assign()
		{
			return Unused_ >= 0 && EmuMath::Helpers::quaternion_can_negate_assign<T_, false>();
		}

		template<std::size_t Unused_>
		[[nodiscard]] static constexpr inline bool _can_divide_assign()
		{
			return Unused_ >= 0 && EmuMath::Helpers::quaternion_can_divide_assign<T_, const preferred_floating_point&, true>();
		}
#pragma endregion

#pragma region CONSTRUCTOR_VALIDITY_CHECKS
	private:
		template<std::size_t VecSize_, typename VecT_, bool IsConst_>
		[[nodiscard]] static constexpr inline bool _valid_euler_vector_lvalue_conversion_constructor_arg()
		{
			if constexpr (VecSize_ <= 3)
			{
				return EmuMath::Helpers::_quaternion_underlying::_valid_euler_vector_lvalue_conversion_arg
				<
					true,
					T_,
					VecSize_,
					VecT_,
					euler_cvt_default_read_offset,
					IsConst_,
					euler_cvt_default_prefer_multiplies,
					euler_cvt_default_normalise,
					euler_cvt_default_is_rads,
					euler_cvt_default_fused,
					euler_cvt_default_is_constexpr,
					false
				>();
			}
			else
			{
				return false;
			}
		}

		template<std::size_t VecSize_, typename VecT_>
		[[nodiscard]] static constexpr inline bool _valid_euler_vector_rvalue_conversion_constructor_arg()
		{
			if constexpr (VecSize_ <= 3)
			{
				return EmuMath::Helpers::_quaternion_underlying::_valid_euler_vector_rvalue_conversion_arg
				<
					true,
					T_,
					VecSize_,
					VecT_,
					0,
					euler_cvt_default_prefer_multiplies,
					euler_cvt_default_normalise,
					euler_cvt_default_is_rads,
					euler_cvt_default_fused,
					euler_cvt_default_is_constexpr,
					false
				>();
			}
			else
			{
				return false;
			}
		}

	public:
		template<std::size_t Unused_ = 0>
		[[nodiscard]] static constexpr inline bool is_default_constructible()
		{
			using implied_zero = decltype(vector_type::get_implied_zero());
			return std::is_constructible_v<vector_type, implied_zero, implied_zero, implied_zero, value_type_uq&&>;
		}

		template<std::size_t Unused_ = 0>
		[[nodiscard]] static constexpr inline bool is_const_copy_constructible()
		{
			return std::is_constructible_v<vector_type, const vector_type&>;
		}

		template<std::size_t Unused_ = 0>
		[[nodiscard]] static constexpr inline bool is_non_const_copy_constructible()
		{
			return std::is_constructible_v<vector_type, vector_type&>;
		}

		template<std::size_t Unused_ = 0>
		[[nodiscard]] static constexpr inline bool is_move_constructible()
		{
			return std::is_constructible_v<vector_type, vector_type&&>;
		}

		template<typename X_, typename Y_, typename Z_, typename W_>
		[[nodiscard]] static constexpr inline bool is_custom_constructible()
		{
			return std::is_constructible_v
			<
				vector_type,
				typename EmuCore::TMP::forward_result<X_>::type,
				typename EmuCore::TMP::forward_result<Y_>::type,
				typename EmuCore::TMP::forward_result<Z_>::type,
				typename EmuCore::TMP::forward_result<W_>::type
			>;
		}

		template<std::size_t Unused_ = 0>
		[[nodiscard]] static constexpr inline bool is_vector_const_copy_constructible()
		{
			return std::is_constructible_v<vector_type, const vector_type&>;
		}

		template<std::size_t Unused_ = 0>
		[[nodiscard]] static constexpr inline bool is_vector_non_const_copy_constructible()
		{
			return std::is_constructible_v<vector_type, vector_type&>;
		}

		template<std::size_t Unused_ = 0>
		[[nodiscard]] static constexpr inline bool is_vector_move_constructible()
		{
			return std::is_constructible_v<vector_type, vector_type&&>;
		}

		template<std::size_t VecSize_, typename VecT_>
		[[nodiscard]] static constexpr inline bool valid_euler_vector_const_ref_conversion_constructor_arg()
		{
			if constexpr (is_vector_move_constructible())
			{
				return EmuMath::Helpers::_quaternion_underlying::_valid_euler_vector_lvalue_conversion_arg
				<
					true,
					T_,
					VecSize_,
					VecT_,
					euler_cvt_default_read_offset,
					true,
					euler_cvt_default_prefer_multiplies,
					euler_cvt_default_normalise,
					euler_cvt_default_is_rads,
					euler_cvt_default_fused,
					euler_cvt_default_is_constexpr,
					false
				>();
			}
			else
			{
				return false;
			}
		}

		template<std::size_t VecSize_, typename VecT_>
		[[nodiscard]] static constexpr inline bool valid_euler_vector_ref_conversion_constructor_arg()
		{
			if constexpr (is_vector_move_constructible() && VecSize_ <= 3)
			{
				return EmuMath::Helpers::_quaternion_underlying::_valid_euler_vector_lvalue_conversion_arg
				<
					true,
					T_,
					VecSize_,
					VecT_,
					euler_cvt_default_read_offset,
					false,
					euler_cvt_default_prefer_multiplies,
					euler_cvt_default_normalise,
					euler_cvt_default_is_rads,
					euler_cvt_default_fused,
					euler_cvt_default_is_constexpr,
					false
				>();
			}
			else
			{
				return false;
			}
		}

		template<std::size_t VecSize_, typename VecT_>
		[[nodiscard]] static constexpr inline bool valid_euler_vector_move_conversion_constructor_arg()
		{
			if constexpr (is_vector_move_constructible() && VecSize_ <= 3)
			{
				return EmuMath::Helpers::_quaternion_underlying::_valid_euler_vector_rvalue_conversion_arg
				<
					true,
					T_,
					VecSize_,
					VecT_,
					0,
					euler_cvt_default_prefer_multiplies,
					euler_cvt_default_normalise,
					euler_cvt_default_is_rads,
					euler_cvt_default_fused,
					euler_cvt_default_is_constexpr,
					false
				>();
			}
			else
			{
				return false;
			}
		}

		template<typename X_, typename Y_, typename Z_>
		[[nodiscard]] static constexpr inline bool valid_euler_conversion_construction_args()
		{
			if constexpr (is_vector_move_constructible())
			{
				return EmuMath::Helpers::_quaternion_underlying::_valid_euler_conversion_args
				<
					true,
					T_,
					X_,
					Y_,
					Z_,
					euler_cvt_default_prefer_multiplies,
					euler_cvt_default_normalise,
					euler_cvt_default_is_rads,
					euler_cvt_default_fused,
					euler_cvt_default_is_constexpr,
					false
				>();
			}
			else
			{
				return false;
			}
		}

		template<typename InT_>
		[[nodiscard]] static constexpr inline bool valid_quaternion_non_const_conversion_construction_typearg()
		{
			return std::is_constructible_v
			<
				vector_type,
				decltype(std::declval<EmuMath::Quaternion<InT_>&>().X()),
				decltype(std::declval<EmuMath::Quaternion<InT_>&>().Y()),
				decltype(std::declval<EmuMath::Quaternion<InT_>&>().Z()),
				decltype(std::declval<EmuMath::Quaternion<InT_>&>().W())
			> && !std::is_same_v<T_, InT_>;
		}

		template<typename InT_>
		[[nodiscard]] static constexpr inline bool valid_quaternion_const_conversion_construction_typearg()
		{
			return std::is_constructible_v
			<
				vector_type,
				decltype(std::declval<const EmuMath::Quaternion<InT_>&>().X()),
				decltype(std::declval<const EmuMath::Quaternion<InT_>&>().Y()),
				decltype(std::declval<const EmuMath::Quaternion<InT_>&>().Z()),
				decltype(std::declval<const EmuMath::Quaternion<InT_>&>().W())
			> && !std::is_same_v<T_, InT_>;
		}

		template<typename InT_>
		[[nodiscard]] static constexpr inline bool valid_quaternion_move_conversion_construction_typearg()
		{
			return std::is_constructible_v
			<
				vector_type,
				decltype(std::move(std::declval<EmuMath::Quaternion<InT_>&&>().X())),
				decltype(std::move(std::declval<EmuMath::Quaternion<InT_>&&>().Y())),
				decltype(std::move(std::declval<EmuMath::Quaternion<InT_>&&>().Z())),
				decltype(std::move(std::declval<EmuMath::Quaternion<InT_>&&>().W()))
			> && !std::is_same_v<T_, InT_>;
		}
#pragma endregion

#pragma region CONSTRUCTOR_HELPERS
	private:
		template<typename X_, typename Y_, typename Z_>
		[[nodiscard]] static constexpr inline vector_type _construct_vector_from_euler(X_&& euler_x_, Y_&& euler_y_, Z_&& euler_z_)
		{
			return EmuMath::Helpers::_quaternion_underlying::_make_from_euler
			<
				true,
				euler_cvt_default_is_rads,
				euler_cvt_default_prefer_multiplies,
				euler_cvt_default_normalise,
				euler_cvt_default_fused,
				euler_cvt_default_is_constexpr,
				T_
			>(std::forward<X_>(euler_x_), std::forward<Y_>(euler_y_), std::forward<Z_>(euler_z_));
		}

		template<std::size_t VecSize_, typename VecT_>
		[[nodiscard]] static constexpr inline vector_type _construct_vector_from_euler(const EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		{
			return EmuMath::Helpers::_quaternion_underlying::_make_from_euler_vector
			<
				true,
				euler_cvt_default_is_rads,
				euler_cvt_default_prefer_multiplies,
				euler_cvt_default_normalise,
				euler_cvt_default_fused,
				euler_cvt_default_is_constexpr,
				T_,
				euler_cvt_default_read_offset
			>(euler_vector_);
		}

		template<std::size_t VecSize_, typename VecT_>
		[[nodiscard]] static constexpr inline vector_type _construct_vector_from_euler(EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		{
			return EmuMath::Helpers::_quaternion_underlying::_make_from_euler_vector
			<
				true,
				euler_cvt_default_is_rads,
				euler_cvt_default_prefer_multiplies,
				euler_cvt_default_normalise,
				euler_cvt_default_fused,
				euler_cvt_default_is_constexpr,
				T_,
				euler_cvt_default_read_offset
			>(euler_vector_);
		}

		template<std::size_t VecSize_, typename VecT_>
		[[nodiscard]] static constexpr inline vector_type _construct_vector_from_euler(EmuMath::Vector<VecSize_, VecT_>&& euler_vector_)
		{
			using in_vector = EmuMath::Vector<VecSize_, VecT_>;
			return EmuMath::Helpers::_quaternion_underlying::_make_from_euler_vector
			<
				true,
				euler_cvt_default_is_rads,
				euler_cvt_default_prefer_multiplies,
				euler_cvt_default_normalise,
				euler_cvt_default_fused,
				euler_cvt_default_is_constexpr,
				T_,
				euler_cvt_default_read_offset
			>(std::forward<in_vector>(euler_vector_));
		}

		template<typename InT_>
		[[nodiscard]] static constexpr inline vector_type _construct_vector_from_conversion(EmuMath::Quaternion<InT_>& to_convert_)
		{
			return vector_type(to_convert_.X(), to_convert_.Y(), to_convert_.Z(), to_convert_.W());
		}

		template<typename InT_>
		[[nodiscard]] static constexpr inline vector_type _construct_vector_from_conversion(const EmuMath::Quaternion<InT_>& to_convert_)
		{
			return vector_type(to_convert_.X(), to_convert_.Y(), to_convert_.Z(), to_convert_.W());
		}

		template<typename InT_>
		[[nodiscard]] static constexpr inline vector_type _construct_vector_from_conversion(EmuMath::Quaternion<InT_>&& to_convert_)
		{
			return vector_type(std::move(to_convert_.X()), std::move(to_convert_.Y()), std::move(to_convert_.Z()), std::move(to_convert_.W()));
		}
#pragma endregion

#pragma region CONSTRUCTORS
	public:
		/// <summary>
		/// <para> Creates a default rotation quaternion, where x = y = z = 0, and w = 1. </para>
		/// </summary>
		template<std::size_t Unused_ = 0, typename = std::enable_if_t<is_default_constructible<Unused_>()>>
		constexpr inline Quaternion() : data(vector_type::get_implied_zero(), vector_type::get_implied_zero(), vector_type::get_implied_zero(), value_type_uq(1))
		{
		}

		/// <summary>
		/// <para> Creates a const-copy of the passed Quaternion. </para>
		/// </summary>
		/// <param name="to_copy_">Quaternion of the same type to copy.</param>
		template<std::size_t Unused_ = 0, typename = std::enable_if_t<is_const_copy_constructible<Unused_>()>>
		constexpr inline Quaternion(const Quaternion<T_>& to_copy_) : data(to_copy_.data)
		{
		}

		/// <summary>
		/// <para> Creates a copy of the passed Quaternion. </para>
		/// </summary>
		/// <param name="to_copy_">Quaternion of the same type to copy.</param>
		template<std::size_t Unused_ = 0, typename = std::enable_if_t<is_copy_constructible<Unused_>()>>
		constexpr inline Quaternion(Quaternion<T_>& to_copy_) : data(to_copy_.data)
		{
		}

		/// <summary>
		/// <para> Moves the data of the passed Quaternion of the same type into a new Quaternion. </para>
		/// </summary>
		/// <param name="to_mmove_">Quaternion of the same type to move.</param>
		template<std::size_t Unused_ = 0, typename = std::enable_if_t<is_move_constructible<Unused_>()>>
		constexpr inline Quaternion(Quaternion<T_>&& to_move_) noexcept : data(std::move(to_move_.data))
		{
		}

		/// <summary>
		/// <para> Creates a new Quaternion with custom X, Y, Z, and W components. Note that W is the real component of the Quaternion. </para>
		/// <para> This does not guarantee that the constructed Quaternion will be valid; this is the responsibility of the caller. </para>
		/// <para> If you do not well understand Quaternions, it is recommended to create one through a different approach. </para>
		/// </summary>
		/// <param name="x_">First imaginary component of the Quaternion.</param>
		/// <param name="y_">Second imaginary component of the Quaternion.</param>
		/// <param name="z_">Third imaginary component of the Quaternion.</param>
		/// <param name="w_">Real component of the Quaternion.</param>
		template<typename X_, typename Y_, typename Z_, typename W_, typename = std::enable_if_t<is_custom_constructible<X_, Y_, Z_, W_>()>>
		constexpr inline Quaternion(X_&& x_, Y_&& y_, Z_&& z_, W_&& w_) :
			data(std::forward<X_>(x_), std::forward<Y_>(y_), std::forward<Z_>(z_), std::forward<W_>(w_))
		{
		}

		/// <summary>
		/// <para> Const copies/converts the passed Quaternion to the newly constructed Quaternion type. </para>
		/// </summary>
		/// <param name="to_convert_">Quaternion of a different type to const-copy/convert.</param>
		template<typename InT_, typename = std::enable_if_t<valid_quaternion_const_conversion_construction_typearg<InT_>()>>
		explicit constexpr inline Quaternion(const EmuMath::Quaternion<InT_>& to_convert_) : data(_construct_vector_from_conversion(to_convert_))
		{
		}

		/// <summary>
		/// <para> Non-const copies/converts the passed Quaternion to the newly constructed Quaternion type. </para>
		/// </summary>
		/// <param name="to_convert_">Quaternion of a different type to non-const-copy/convert.</param>
		template<typename InT_, typename = std::enable_if_t<valid_quaternion_non_const_conversion_construction_typearg<InT_>()>>
		explicit constexpr inline Quaternion(EmuMath::Quaternion<InT_>& to_convert_) : data(_construct_vector_from_conversion(to_convert_))
		{
		}

		/// <summary>
		/// <para> Moves/converts the passed Quaternion to the newly constructed Quaternion type. </para>
		/// </summary>
		/// <param name="to_convert_">Quaternion of a different type to move/convert.</param>
		template<typename InT_, typename = std::enable_if_t<valid_quaternion_move_conversion_construction_typearg<InT_>()>>
		explicit constexpr inline Quaternion(EmuMath::Quaternion<InT_>&& to_convert_) : data(_construct_vector_from_conversion(std::move(to_convert_)))
		{
		}

		/// <summary>
		/// <para> Performs a const-copy of the passed Vector, treating it as a Quaternion. </para>
		/// </summary>
		/// <param name="quaternion_as_vector_">Vector representing a Quaternion to copy.</param>
		template<std::size_t Unused_ = 0, typename = std::enable_if_t<is_vector_const_copy_constructible<Unused_>()>>
		explicit constexpr inline Quaternion(const vector_type& quaternion_as_vector_) : data(quaternion_as_vector_)
		{
		}

		/// <summary>
		/// <para> Performs a copy of the passed Vector, treating it as a Quaternion. </para>
		/// </summary>
		/// <param name="quaternion_as_vector_">Vector representing a Quaternion to copy.</param>
		template<std::size_t Unused_ = 0, typename = std::enable_if_t<is_vector_non_const_copy_constructible<Unused_>()>>
		explicit constexpr inline Quaternion(vector_type& quaternion_as_vector_) : data(quaternion_as_vector_)
		{
		}

		/// <summary>
		/// <para> Performs a move of the passed Vector into a new Quaternion's underlying data, treating it as a Quaternion. </para>
		/// </summary>
		/// <param name="quaternion_as_vector_">Vector representing a Quaternion to move.</param>
		template<std::size_t Unused_ = 0, typename = std::enable_if_t<is_vector_move_constructible<Unused_>()>>
		explicit constexpr inline Quaternion(vector_type&& quaternion_as_vector_) noexcept : data(std::move(quaternion_as_vector_))
		{
		}

		/// <summary>
		/// <para> Creates a Quaternion representing the passed Euler Vector. </para>
		/// <para> Note that the passed Vector will be treated as a Quaternion if it is the same type as this Quaternion's `vector_type`. </para>
		/// </summary>
		/// <param name="euler_vector_">Const reference to a Vector to treat as a Euler representation of a rotation.</param>
		template<std::size_t VecSize_, typename VecT_, typename = std::enable_if_t<valid_euler_vector_const_ref_conversion_constructor_arg<VecSize_, VecT_>()>>
		explicit constexpr inline Quaternion(const EmuMath::Vector<VecSize_, VecT_>& euler_vector_) :
			data(_construct_vector_from_euler(euler_vector_))
		{
		}

		/// <summary>
		/// <para> Creates a Quaternion representing the passed Euler Vector. </para>
		/// <para> Note that the passed Vector will be treated as a Quaternion if it is the same type as this Quaternion's `vector_type`. </para>
		/// </summary>
		/// <param name="euler_vector_">Reference to a Vector to treat as a Euler representation of a rotation.</param>
		template<std::size_t VecSize_, typename VecT_, typename = std::enable_if_t<valid_euler_vector_ref_conversion_constructor_arg<VecSize_, VecT_>()>>
		explicit constexpr inline Quaternion(EmuMath::Vector<VecSize_, VecT_>& euler_vector_) :
			data(_construct_vector_from_euler(euler_vector_))
		{
		}

		/// <summary>
		/// <para> Creates a Quaternion representing the passed Euler Vector. </para>
		/// <para> Note that the passed Vector will be treated as a Quaternion if it is the same type as this Quaternion's `vector_type`. </para>
		/// </summary>
		/// <param name="euler_vector_">Vector to treat as a Euler representation of a rotation.</param>
		template<std::size_t VecSize_, typename VecT_, typename = std::enable_if_t<valid_euler_vector_ref_conversion_constructor_arg<VecSize_, VecT_>()>>
		explicit constexpr inline Quaternion(EmuMath::Vector<VecSize_, VecT_>&& euler_vector_) :
			data(_construct_vector_from_euler(std::move(euler_vector_)))
		{
		}

		/// <summary>
		/// <para> Creates a Quaternion representing a Euler rotation formed of the passed components. </para>
		/// </summary>
		/// <param name="euler_x_">First value within the Euler Vector.</param>
		/// <param name="euler_y_">Second value within the Euler Vector.</param>
		/// <param name="euler_z_">Third value within the Euler Vector.</param>
		template<typename X_, typename Y_, typename Z_, typename = std::enable_if_t<valid_euler_conversion_construction_args<X_, Y_, Z_>()>>
		explicit constexpr inline Quaternion(X_&& euler_x_, Y_&& euler_y_, Z_&& euler_z_) :
			data(_construct_vector_from_euler(std::forward<X_>(euler_x_), std::forward<Y_>(euler_y_), std::forward<Z_>(euler_z_)))
		{
		}
#pragma endregion

#pragma region ACCESS_OPERATORS
	public:
		/// <summary>
		/// <para> Retrieves a reference to the element at the provided index within this Quaternion. </para>
		/// <para> No bounds checks are performed with this operator. </para>
		/// <para> Valid indices are 0, 1, 2, and 3, which correlate to this Quaternion's X, Y, Z, and W components respectively. </para>
		/// </summary>
		/// <returns>Reference to the item at the specified index within this Quaternion.</returns>
		[[nodiscard]] constexpr inline value_type& operator[](const std::size_t index_)
		{
			return data[index_];
		}

		[[nodiscard]] constexpr inline const value_type& operator[](const std::size_t index_) const
		{
			return data[index_];
		}
#pragma endregion

#pragma region COMPARISON_OPERATORS
	public:
		/// <summary>
		/// <para> Compares this Quaternion to the right-hand-side Quaternion and returns true if they are equal. </para>
		/// <para> For comparisons where a margin of error may exist between otherwise identical Quaternions, it is recommended to use `CmpNear` instead. </para>
		/// </summary>
		/// <param name="rhs_">Quaternion to compare this one to.</param>
		/// <returns>True if this Quaternion is exactly equal to `rhs_`; otherwise false.</returns>
		template<typename RhsT_>
		[[nodiscard]] constexpr inline bool operator==(const Quaternion<RhsT_>& rhs_) const
		{
			return data.CmpAllEqual(rhs_.data);
		}

		/// <summary>
		/// <para> Compares this Quaternion to the right-hand-side Quaternion and returns true if any component is not equal. </para>
		/// <para> For comparisons where a margin of error may exist between otherwise identical Quaternions, it is recommended to use `CmpNotNear` instead. </para>
		/// </summary>
		/// <param name="rhs_">Quaternion to compare this one to.</param>
		/// <returns>True if this Quaternion is not exactly equal to `rhs_`; otherwise false.</returns>
		template<typename RhsT_>
		[[nodiscard]] constexpr inline bool operator!=(const Quaternion<RhsT_>& rhs_) const
		{
			return data.CmpAnyNotEqual(rhs_.data);
		}
#pragma endregion

#pragma region CONST_ARITHMETIC_OPERATORS
	public:
		template<typename OutT_ = preferred_floating_point, typename RhsT_>
		[[nodiscard]] constexpr inline auto operator+(const EmuMath::Quaternion<RhsT_>& rhs_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_add<T_, RhsT_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_add<OutT_>(*this, rhs_);
		}

		template<typename OutT_ = preferred_floating_point, typename RhsT_>
		[[nodiscard]] constexpr inline auto operator-(const EmuMath::Quaternion<RhsT_>& rhs_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_subtract<T_, RhsT_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_subtract<OutT_>(*this, rhs_);
		}

		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto operator-() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_negate<T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_negate<OutT_>(*this);
		}

		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto operator*(const preferred_floating_point& rhs_scalar_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_scalar_multiply<T_, const preferred_floating_point&, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_multiply_by_scalar<OutT_>(*this, rhs_scalar_);
		}

		template<typename OutT_ = preferred_floating_point, typename RhsT_>
		[[nodiscard]] constexpr inline auto operator*(const EmuMath::Quaternion<RhsT_>& rhs_quaternion_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_quaternion_multiply<T_, RhsT_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_multiply_by_quaternion<OutT_>(*this, rhs_quaternion_);
		}

		template<typename OutT_ = preferred_floating_point>
		constexpr inline auto operator/(const preferred_floating_point& rhs_scalar_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_divide<T_, const preferred_floating_point&, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_divide<OutT_>(*this, rhs_scalar_);
		}
#pragma endregion

#pragma region ASSIGNING_ARITHMETIC_OPERATORS
		template<typename RhsT_>
		constexpr inline auto operator+=(const EmuMath::Quaternion<RhsT_>& rhs_)
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_add_assign<T_, RhsT_, false>(), this_type&>
		{
			EmuMath::Helpers::quaternion_add_assign(*this, rhs_);
			return *this;
		}

		template<typename RhsT_>
		constexpr inline auto operator-=(const EmuMath::Quaternion<RhsT_>& rhs_)
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_subtract_assign<T_, RhsT_, false>(), this_type&>
		{
			EmuMath::Helpers::quaternion_subtract_assign(*this, rhs_);
			return *this;
		}

		template<std::size_t Unused_ = 0>
		constexpr inline auto operator*=(const preferred_floating_point& rhs_scalar_)
			-> std::enable_if_t<_can_scalar_multiply_assign<Unused_>(), this_type&>
		{
			EmuMath::Helpers::quaternion_multiply_assign_by_scalar(*this, rhs_scalar_);
			return *this;
		}

		template<typename RhsT_>
		constexpr inline auto operator*=(const EmuMath::Quaternion<RhsT_>& rhs_quaternion_)
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_quaternion_multiply_assign<T_, RhsT_, false>(), this_type&>
		{
			EmuMath::Helpers::quaternion_multiply_assign_by_quaternion(*this, rhs_quaternion_);
			return *this;
		}

		template<std::size_t Unused_ = 0>
		constexpr inline auto operator/=(const preferred_floating_point& rhs_scalar_)
		{
			EmuMath::Helpers::quaternion_divide_assign(*this, rhs_scalar_);
			return *this;
		}
#pragma endregion

#pragma region ASSIGNMENT_OPERATORS
		template<std::size_t Unused_ = 0>
		[[nodiscard]] static constexpr inline bool is_move_assignable()
		{
			return Unused_ >= 0 && std::is_assignable_v<vector_type&, vector_type&&>;
		}

		template<std::size_t Unused_ = 0>
		[[nodiscard]] static constexpr inline bool is_const_copy_assignable()
		{
			return Unused_ >= 0 && std::is_assignable_v<vector_type&, const vector_type&>;
		}

		template<std::size_t Unused_ = 0>
		[[nodiscard]] static constexpr inline bool is_non_const_copy_assignable()
		{
			return Unused_ >= 0 && std::is_assignable_v<vector_type&, vector_type&>;
		}

		template<std::size_t Unused_ = 0>
		constexpr inline auto operator=(EmuMath::Quaternion<T_>&& to_move_)
			-> std::enable_if_t<is_move_assignable<Unused_>(), this_type&>
		{
			data = std::move(to_move_.data);
			return *this;
		}

		template<std::size_t Unused_ = 0>
		constexpr inline auto operator=(EmuMath::Quaternion<T_>& to_copy_)
			-> std::enable_if_t<is_non_const_copy_assignable<Unused_>(), this_type&>
		{
			data = to_copy_.data;
			return *this;
		}

		template<std::size_t Unused_ = 0>
		constexpr inline auto operator=(const EmuMath::Quaternion<T_>& to_copy_)
			-> std::enable_if_t<is_const_copy_assignable<Unused_>(), this_type&>
		{
			data = to_copy_.data;
			return *this;
		}

		template<typename RhsT_>
		constexpr inline auto operator=(EmuMath::Quaternion<RhsT_>& to_convert_)
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_non_const_convert_assign<T_, RhsT_>() && !std::is_same_v<T_, RhsT_>, this_type&>
		{
			EmuMath::Helpers::quaternion_convert_assign(*this, to_convert_);
			return *this;
		}

		template<typename RhsT_>
		constexpr inline auto operator=(const EmuMath::Quaternion<RhsT_>& to_convert_)
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_const_convert_assign<T_, RhsT_>() && !std::is_same_v<T_, RhsT_>, this_type&>
		{
			EmuMath::Helpers::quaternion_convert_assign(*this, to_convert_);
			return *this;
		}

		template<typename RhsT_>
		constexpr inline auto operator=(EmuMath::Quaternion<RhsT_>&& to_convert_)
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_move_convert_assign<T_, RhsT_>() && !std::is_same_v<T_, RhsT_>, this_type&>
		{
			EmuMath::Helpers::quaternion_convert_assign(*this, std::forward<EmuMath::Quaternion<RhsT_>>(to_convert_));
			return *this;
		}
#pragma endregion

#pragma region GET_VALIDITY_CHECKS
	public:
		/// <summary>
		/// <para> Compile-time function to evaluate if a provided `OutT_` is valid when calling `ImaginaryVector` on an instance of this Quaternion type. </para>
		/// <para> `QuaternionIsConst_` identifies if the Quaternion is const-qualified at the time of calling `ImaginaryVector`. </para>
		/// </summary>
		/// <returns>True if a call to `ImaginaryVector` is valid with the given output type on a Quaternion in the given const state; otherwise false.</returns>
		template<typename OutT_, bool QuaternionIsConst_>
		[[nodiscard]] static constexpr inline bool valid_out_imaginary_vector_typearg()
		{
			using vector_ref_type = typename std::conditional<QuaternionIsConst_, const vector_type&, vector_type&>::type;
			return std::is_constructible_v
			<
				EmuMath::Vector<3, OutT_>,
				decltype(std::declval<vector_ref_type>().template at<0>()),
				decltype(std::declval<vector_ref_type>().template at<1>()),
				decltype(std::declval<vector_ref_type>().template at<2>())
			>;
		}

		/// <summary>
		/// <para> Compile-time function to evaluate if a provided `OutT_` is valid when calling `RealScalar` on an instance of this Quaternion type. </para>
		/// <para> `QuaternionIsConst_` identifies if the Quaternion is const-qualified at the time of calling `RealScalar`. </para>
		/// </summary>
		/// <returns>True if a call to `RealScalar` is valid with the given output type on a Quaternion in the given const state; otherwise false.</returns>
		template<typename Out_, bool QuaternionIsConst_>
		[[nodiscard]] static constexpr inline bool valid_out_real_scalar_typearg()
		{
			using vector_ref_type = typename std::conditional<QuaternionIsConst_, const vector_type&, vector_type&>::type;
			return std::is_constructible_v<Out_, decltype(std::declval<vector_ref_type>().template at<3>())>;
		}
#pragma endregion

#pragma region GETTERS
	public:
		/// <summary>
		/// <para> Retrieves a reference to the element at the provided index within this Quaternion. </para>
		/// <para> A compile-time bounds check is performed for this call, and a static assertion will be triggered if Index_ is invalid. </para>
		/// <para> Valid indices are 0, 1, 2, and 3, which correlate to this Quaternion's X, Y, Z, and W components respectively. </para>
		/// </summary>
		/// <returns>Reference to the item at the specified index within this Quaternion.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline value_type& at()
		{
			if constexpr (Index_ <= 3)
			{
				return data.template at<Index_>();
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Index_>(),
					"Attempted to access an index greater than 3 within a Quaternion. Only 0, 1, 2, and 3 are valid indices in a Quaternion, where 0, 1, 2 are the imaginary component X, Y, Z, and 3 is the real component W."
				);
			}
		}
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline const value_type& at() const
		{
			return const_cast<this_type*>(this)->template at<Index_>();
		}

		/// <summary>
		/// <para> Retrieves a reference to the element at the provided index within this Quaternion. </para>
		/// <para> A runtime bounds check is performed for this call, and a std::out_of_range exception will be thrown if index_ is invalid. </para>
		/// <para> Valid indices are 0, 1, 2, and 3, which correlate to this Quaternion's X, Y, Z, and W components respectively. </para>
		/// </summary>
		/// <returns>Reference to the item at the specified index within this Quaternion.</returns>
		[[nodiscard]] constexpr inline value_type& at(const std::size_t index_)
		{
			if (index_ <= 3)
			{
				return data[index_];
			}
			else
			{
				if constexpr (EmuCore::TMP::feature_constexpr_dynamic_memory())
				{
					// We can provide some extra information if we have access to constexpr strings
					// --- This is to allow `at(index_)` to still satisfy constexpr constraints in standards before C++20
					std::string out_str_;
					out_str_.reserve(150); // Reserves enough space for all literal chars, alongside some extra for index_ after conversion.
					out_str_ += "Attempted to access an invalid contained index of an EmuMath Quaternion.\nProvided index: ";
					out_str_ += std::to_string(index_);
					out_str_ += "\nInclusive valid index range: 0:3";
					throw std::out_of_range(out_str_);
				}
				else
				{
					throw std::out_of_range("Attempted to access an invalid contained index of an EmuMath Quaternion.\nInclusive valid index range: 0:3");
				}
			}
		}

		[[nodiscard]] constexpr inline const value_type& at(const std::size_t index_) const
		{
			return const_cast<this_type*>(this)->at(index_);
		}

		/// <summary>
		/// <para> Outputs a Vector representing the imaginary component (i.e. XYZ) of this Quaternion. </para>
		/// <para> The output Vector may contain any valid conversion type, including references, and defaults to this Quaternion's `value_type_uq`. </para>
		/// </summary>
		/// <returns>3D EmuMath Vector containing the imaginary component of this Quaternion, with X, Y, and Z at indices 0, 1, and 2 respectively.</returns>
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline auto ImaginaryVector()
			-> std::enable_if_t<valid_out_imaginary_vector_typearg<OutT_, false>(), EmuMath::Vector<3, OutT_>>
		{
			return EmuMath::Vector<3, OutT_>(data.at<0>(), data.at<1>(), data.at<2>());
		}

		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline auto ImaginaryVector() const
			-> std::enable_if_t<valid_out_imaginary_vector_typearg<OutT_, true>(), EmuMath::Vector<3, OutT_>>
		{
			return EmuMath::Vector<3, OutT_>(data.at<0>(), data.at<1>(), data.at<2>());
		}

		/// <summary>
		/// <para> Retrieves a reference to the X component of this Quaternion (i.e. its first imaginary component). </para>
		/// </summary>
		/// <returns> Reference to this Quaternion's X component. </returns>
		[[nodiscard]] constexpr inline value_type& X()
		{
			return data.at<0>();
		}

		[[nodiscard]] constexpr inline const value_type& X() const
		{
			return data.at<0>();
		}

		/// <summary>
		/// <para> Retrieves a reference to the Y component of this Quaternion (i.e. its second imaginary component). </para>
		/// </summary>
		/// <returns> Reference to this Quaternion's Y component. </returns>
		[[nodiscard]] constexpr inline value_type& Y()
		{
			return data.at<1>();
		}

		[[nodiscard]] constexpr inline const value_type& Y() const
		{
			return data.at<1>();
		}

		/// <summary>
		/// <para> Retrieves a reference to the Z component of this Quaternion (i.e. its third imaginary component). </para>
		/// </summary>
		/// <returns> Reference to this Quaternion's Z component. </returns>
		[[nodiscard]] constexpr inline value_type& Z()
		{
			return data.at<2>();
		}

		[[nodiscard]] constexpr inline const value_type& Z() const
		{
			return data.at<2>();
		}

		/// <summary>
		/// <para> Retrieves a reference to the W component of this Quaternion (i.e. its real component). </para>
		/// </summary>
		/// <returns> Reference to this Quaternion's W component. </returns>
		[[nodiscard]] constexpr inline value_type& W()
		{
			return data.at<3>();
		}

		[[nodiscard]] constexpr inline const value_type& W() const
		{
			return data.at<3>();
		}
#pragma endregion

#pragma region COMPARISON_FUNCS
	public:
		/// <summary>
		/// <para> Compares this Quaternion to the right-hand-side Quaternion and returns true if they are equal. </para>
		/// <para> For comparisons where a margin of error may exist between otherwise identical Quaternions, it is recommended to use `CmpNear` instead. </para>
		/// </summary>
		/// <param name="rhs_">Quaternion to compare this one to.</param>
		/// <returns>True if this Quaternion is exactly equal to `rhs_`; otherwise false.</returns>
		template<typename RhsT_>
		[[nodiscard]] constexpr inline bool CmpEqual(const Quaternion<RhsT_>& rhs_) const
		{
			return data.CmpAllEqual(rhs_.data);
		}

		/// <summary>
		/// <para> Compares this Quaternion to the right-hand-side Quaternion and returns true if any component is not equal. </para>
		/// <para> For comparisons where a margin of error may exist between otherwise identical Quaternions, it is recommended to use `CmpNotNear` instead. </para>
		/// </summary>
		/// <param name="rhs_">Quaternion to compare this one to.</param>
		/// <returns>True if this Quaternion is not exactly equal to `rhs_`; otherwise false.</returns>
		template<typename RhsT_>
		[[nodiscard]] constexpr inline bool CmpNotEqual(const Quaternion<RhsT_>& rhs_) const
		{
			return data.CmpAnyNotEqual(rhs_.data);
		}

		/// <summary>
		/// <para> Compares this Quaternion to the right-hand-side Quaternion and returns true if they are near-equal. </para>
		/// <para> This comparison considers a potential margin of error due to floating-point precision errors. </para>
		/// </summary>
		/// <param name="rhs_">Quaternion to compare this one to.</param>
		/// <returns>True if this Quaternion is near-equal to `rhs_`; otherwise false.</returns>
		template<typename RhsT_>
		[[nodiscard]] constexpr inline bool CmpNear(const Quaternion<RhsT_>& rhs_) const
		{
			return data.CmpAllNear(rhs_.data);
		}

		/// <summary>
		/// <para> Compares this Quaternion to the right-hand-side Quaternion and returns true if they are near-equal. </para>
		/// <para> This comparison considers a potential margin of error due to floating-point precision errors. </para>
		/// </summary>
		/// <param name="rhs_">Quaternion to compare this one to.</param>
		/// <returns>True if this Quaternion is not near-equal to `rhs_`; otherwise false.</returns>
		template<typename RhsT_>
		[[nodiscard]] constexpr inline bool CmpNotNear(const Quaternion<RhsT_>& rhs_) const
		{
			return data.CmpAnyNotNear(rhs_.data);
		}
#pragma endregion

#pragma region CONVERSIONS_FROM_EULER
	public:
		/// <summary>
		/// <para> Creates a Quaternion form of the passed Euler angles. </para>
		/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
		/// </summary>
		/// <param name="x_">Euler angle rotation in the X-axis, as either radians or degrees (depending on IsRads_).</param>
		/// <param name="y_">Euler angle rotation in the Y-axis, as either radians or degrees (depending on IsRads_).</param>
		/// <param name="z_">Euler angle rotation in the Z-axis, as either radians or degrees (depending on IsRads_).</param>
		/// <returns>Quaternion resulting from a conversion of the passed Euler angles.</returns>
		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, bool Normalise_ = euler_cvt_default_normalise, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies,
			typename X_, typename Y_, typename Z_
		>
		[[nodiscard]] static constexpr inline auto from_euler(X_&& euler_x_, Y_&& euler_y_, Z_&& euler_z_)
			-> std::enable_if_t
			<
				EmuMath::Helpers::quaternion_can_convert_from_euler<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point, X_, Y_, Z_, false>(),
				EmuMath::Quaternion<preferred_floating_point>
			>
		{
			return EmuMath::Helpers::quaternion_from_euler<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point>
			(
				std::forward<X_>(euler_x_),
				std::forward<Y_>(euler_y_),
				std::forward<Z_>(euler_z_)
			);
		}

		/// <summary>
		/// <para> Creates a Quaternion form of the passed Euler angles. </para>
		/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
		/// <para>
		///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
		///		Use of such instructions may improve accuracy and/or performance.
		/// </para>
		/// </summary>
		/// <param name="x_">Euler angle rotation in the X-axis, as either radians or degrees (depending on IsRads_).</param>
		/// <param name="y_">Euler angle rotation in the Y-axis, as either radians or degrees (depending on IsRads_).</param>
		/// <param name="z_">Euler angle rotation in the Z-axis, as either radians or degrees (depending on IsRads_).</param>
		/// <returns>Quaternion resulting from a conversion of the passed Euler angles.</returns>
		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, bool Normalise_ = euler_cvt_default_normalise, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies,
			typename X_, typename Y_, typename Z_
		>
		[[nodiscard]] static constexpr inline auto from_euler_fused(X_&& euler_x_, Y_&& euler_y_, Z_&& euler_z_)
			-> std::enable_if_t
			<
				EmuMath::Helpers::quaternion_can_convert_from_euler_fused<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point, X_, Y_, Z_, false>(),
				EmuMath::Quaternion<preferred_floating_point>
			>
		{
			return EmuMath::Helpers::quaternion_from_euler_fused<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point>
			(
				std::forward<X_>(euler_x_),
				std::forward<Y_>(euler_y_),
				std::forward<Z_>(euler_z_)
			);
		}

		/// <summary>
		/// <para> Creates a Quaternion form of the passed Euler angles. </para>
		/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
		/// <para> This function will attempt to be constexpr-evaluable, which may have an effect on accuracy and/or performance. </para>
		/// </summary>
		/// <param name="x_">Euler angle rotation in the X-axis, as either radians or degrees (depending on IsRads_).</param>
		/// <param name="y_">Euler angle rotation in the Y-axis, as either radians or degrees (depending on IsRads_).</param>
		/// <param name="z_">Euler angle rotation in the Z-axis, as either radians or degrees (depending on IsRads_).</param>
		/// <returns>Quaternion resulting from a conversion of the passed Euler angles.</returns>
		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, bool Normalise_ = euler_cvt_default_normalise, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies,
			typename X_, typename Y_, typename Z_
		>
		[[nodiscard]] static constexpr inline auto from_euler_constexpr(X_&& euler_x_, Y_&& euler_y_, Z_&& euler_z_)
			-> std::enable_if_t
			<
				EmuMath::Helpers::quaternion_can_convert_from_euler_constexpr<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point, X_, Y_, Z_, false>(),
				EmuMath::Quaternion<preferred_floating_point>
			>
		{
			return EmuMath::Helpers::quaternion_from_euler_constexpr<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point>
			(
				std::forward<X_>(euler_x_),
				std::forward<Y_>(euler_y_),
				std::forward<Z_>(euler_z_)
			);
		}

		/// <summary>
		/// <para> Creates a Quaternion form of the passed Euler Vector (interpreted as a 3D Vector). </para>
		/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
		/// </summary>
		/// <param name="euler_vector_">EmuMath Vector to be interpreted as a 3D Vector of Euler angles to convert.</param>
		/// <returns>Quaternion resulting from a conversion of the passed Euler Vector.</returns>
		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, bool Normalise_ = euler_cvt_default_normalise, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies,
			std::size_t ReadOffset_ = 0, typename VecT_, std::size_t VecSize_
		>
		[[nodiscard]] static constexpr inline auto from_euler(const EmuMath::Vector<VecSize_, VecT_>& euler_xyz_)
			-> std::enable_if_t
			<
				EmuMath::Helpers::quaternion_can_convert_from_const_euler_vector<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point, VecSize_, VecT_, ReadOffset_, false>(),
				EmuMath::Quaternion<preferred_floating_point>
			>
		{
			return EmuMath::Helpers::quaternion_from_euler<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point, ReadOffset_>(euler_xyz_);
		}

		/// <summary>
		/// <para> Creates a Quaternion form of the passed Euler Vector (interpreted as a 3D Vector). </para>
		/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
		/// <para>
		///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
		///		Use of such instructions may improve accuracy and/or performance.
		/// </para>
		/// </summary>
		/// <param name="euler_vector_">EmuMath Vector to be interpreted as a 3D Vector of Euler angles to convert.</param>
		/// <returns>Quaternion resulting from a conversion of the passed Euler Vector.</returns>
		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, bool Normalise_ = euler_cvt_default_normalise, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies,
			std::size_t ReadOffset_ = 0, typename VecT_, std::size_t VecSize_
		>
		[[nodiscard]] static constexpr inline auto from_euler_fused(const EmuMath::Vector<VecSize_, VecT_>& euler_xyz_)
			-> std::enable_if_t
			<
				EmuMath::Helpers::quaternion_can_convert_from_const_euler_vector_fused<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point, VecSize_, VecT_, ReadOffset_, false>(),
				EmuMath::Quaternion<preferred_floating_point>
			>
		{
			return EmuMath::Helpers::quaternion_from_euler_fused<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point, ReadOffset_>(euler_xyz_);
		}

		/// <summary>
		/// <para> Creates a Quaternion form of the passed Euler Vector (interpreted as a 3D Vector). </para>
		/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
		/// <para> This function will attempt to be constexpr-evaluable, which may have an effect on accuracy and/or performance. </para>
		/// </summary>
		/// <param name="euler_vector_">EmuMath Vector to be interpreted as a 3D Vector of Euler angles to convert.</param>
		/// <returns>Quaternion resulting from a conversion of the passed Euler Vector.</returns>
		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, bool Normalise_ = euler_cvt_default_normalise, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies,
			std::size_t ReadOffset_ = 0, typename VecT_, std::size_t VecSize_
		>
		[[nodiscard]] static constexpr inline auto from_euler_constexpr(const EmuMath::Vector<VecSize_, VecT_>& euler_xyz_)
			-> std::enable_if_t
			<
				EmuMath::Helpers::quaternion_can_convert_from_const_euler_vector_constexpr<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point, VecSize_, VecT_, ReadOffset_, false>(),
				EmuMath::Quaternion<preferred_floating_point>
			>
		{
			return EmuMath::Helpers::quaternion_from_euler_constexpr<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point, ReadOffset_>(euler_xyz_);
		}

		/// <summary>
		/// <para> Creates a Quaternion form of the passed Euler Vector (interpreted as a 3D Vector). </para>
		/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
		/// </summary>
		/// <param name="euler_vector_">EmuMath Vector to be interpreted as a 3D Vector of Euler angles to convert.</param>
		/// <returns>Quaternion resulting from a conversion of the passed Euler Vector.</returns>
		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, bool Normalise_ = euler_cvt_default_normalise, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies,
			std::size_t ReadOffset_ = 0, typename VecT_, std::size_t VecSize_
		>
		[[nodiscard]] static constexpr inline auto from_euler(EmuMath::Vector<VecSize_, VecT_>& euler_xyz_)
			-> std::enable_if_t
			<
				EmuMath::Helpers::quaternion_can_convert_from_euler_vector<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point, VecSize_, VecT_, ReadOffset_, false>(),
				EmuMath::Quaternion<preferred_floating_point>
			>
		{
			return EmuMath::Helpers::quaternion_from_euler<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point, ReadOffset_>(euler_xyz_);
		}

		/// <summary>
		/// <para> Creates a Quaternion form of the passed Euler Vector (interpreted as a 3D Vector). </para>
		/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
		/// <para>
		///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
		///		Use of such instructions may improve accuracy and/or performance.
		/// </para>
		/// </summary>
		/// <param name="euler_vector_">EmuMath Vector to be interpreted as a 3D Vector of Euler angles to convert.</param>
		/// <returns>Quaternion resulting from a conversion of the passed Euler Vector.</returns>
		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, bool Normalise_ = euler_cvt_default_normalise, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies,
			std::size_t ReadOffset_ = 0, typename VecT_, std::size_t VecSize_
		>
		[[nodiscard]] static constexpr inline auto from_euler_fused(EmuMath::Vector<VecSize_, VecT_>& euler_xyz_)
			-> std::enable_if_t
			<
				EmuMath::Helpers::quaternion_can_convert_from_euler_vector_fused<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point, VecSize_, VecT_, ReadOffset_, false>(),
				EmuMath::Quaternion<preferred_floating_point>
			>
		{
			return EmuMath::Helpers::quaternion_from_euler_fused<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point, ReadOffset_>(euler_xyz_);
		}

		/// <summary>
		/// <para> Creates a Quaternion form of the passed Euler Vector (interpreted as a 3D Vector). </para>
		/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
		/// <para> This function will attempt to be constexpr-evaluable, which may have an effect on accuracy and/or performance. </para>
		/// </summary>
		/// <param name="euler_vector_">EmuMath Vector to be interpreted as a 3D Vector of Euler angles to convert.</param>
		/// <returns>Quaternion resulting from a conversion of the passed Euler Vector.</returns>
		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, bool Normalise_ = euler_cvt_default_normalise, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies,
			std::size_t ReadOffset_ = 0, typename VecT_, std::size_t VecSize_
		>
		[[nodiscard]] static constexpr inline auto from_euler_constexpr(EmuMath::Vector<VecSize_, VecT_>& euler_xyz_)
			-> std::enable_if_t
			<
				EmuMath::Helpers::quaternion_can_convert_from_euler_vector_constexpr<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point, VecSize_, VecT_, ReadOffset_, false>(),
				EmuMath::Quaternion<preferred_floating_point>
			>
		{
			return EmuMath::Helpers::quaternion_from_euler_constexpr<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point, ReadOffset_>(euler_xyz_);
		}

		/// <summary>
		/// <para> Creates a Quaternion form of the passed Euler Vector (interpreted as a 3D Vector). </para>
		/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
		/// </summary>
		/// <param name="euler_vector_">EmuMath Vector to be interpreted as a 3D Vector of Euler angles to convert.</param>
		/// <returns>Quaternion resulting from a conversion of the passed Euler Vector.</returns>
		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, bool Normalise_ = euler_cvt_default_normalise, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies,
			std::size_t ReadOffset_ = 0, typename VecT_, std::size_t VecSize_
		>
		[[nodiscard]] static constexpr inline auto from_euler(EmuMath::Vector<VecSize_, VecT_>&& euler_xyz_)
			-> std::enable_if_t
			<
				EmuMath::Helpers::quaternion_can_convert_from_rvalue_euler_vector<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point, VecSize_, VecT_, ReadOffset_, false>(),
				EmuMath::Quaternion<preferred_floating_point>
			>
		{
			using in_vector = EmuMath::Vector<VecSize_, VecT_>;
			return EmuMath::Helpers::quaternion_from_euler<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point, ReadOffset_>(std::forward<in_vector>(euler_xyz_));
		}

		/// <summary>
		/// <para> Creates a Quaternion form of the passed Euler Vector (interpreted as a 3D Vector). </para>
		/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
		/// <para>
		///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
		///		Use of such instructions may improve accuracy and/or performance.
		/// </para>
		/// </summary>
		/// <param name="euler_vector_">EmuMath Vector to be interpreted as a 3D Vector of Euler angles to convert.</param>
		/// <returns>Quaternion resulting from a conversion of the passed Euler Vector.</returns>
		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, bool Normalise_ = euler_cvt_default_normalise, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies,
			std::size_t ReadOffset_ = 0, typename VecT_, std::size_t VecSize_
		>
		[[nodiscard]] static constexpr inline auto from_euler_fused(EmuMath::Vector<VecSize_, VecT_>&& euler_xyz_)
			-> std::enable_if_t
			<
				EmuMath::Helpers::quaternion_can_convert_from_rvalue_euler_vector_fused<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point, VecSize_, VecT_, ReadOffset_, false>(),
				EmuMath::Quaternion<preferred_floating_point>
			>
		{
			using in_vector = EmuMath::Vector<VecSize_, VecT_>;
			return EmuMath::Helpers::quaternion_from_euler_fused<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point, ReadOffset_>(std::forward<in_vector>(euler_xyz_));
		}

		/// <summary>
		/// <para> Creates a Quaternion form of the passed Euler Vector (interpreted as a 3D Vector). </para>
		/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
		/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
		/// <para> This function will attempt to be constexpr-evaluable, which may have an effect on accuracy and/or performance. </para>
		/// </summary>
		/// <param name="euler_vector_">EmuMath Vector to be interpreted as a 3D Vector of Euler angles to convert.</param>
		/// <returns>Quaternion resulting from a conversion of the passed Euler Vector.</returns>
		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, bool Normalise_ = euler_cvt_default_normalise, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies,
			std::size_t ReadOffset_ = 0, typename VecT_, std::size_t VecSize_
		>
		[[nodiscard]] static constexpr inline auto from_euler_constexpr(EmuMath::Vector<VecSize_, VecT_>&& euler_xyz_)
			-> std::enable_if_t
			<
				EmuMath::Helpers::quaternion_can_convert_from_rvalue_euler_vector_constexpr<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point, VecSize_, VecT_, ReadOffset_, false>(),
				EmuMath::Quaternion<preferred_floating_point>
			>
		{
			using in_vector = EmuMath::Vector<VecSize_, VecT_>;
			return EmuMath::Helpers::quaternion_from_euler_constexpr<IsRads_, Normalise_, PreferMultiplies_, preferred_floating_point, ReadOffset_>(std::forward<in_vector>(euler_xyz_));
		}
#pragma endregion

#pragma region MEMBER_CONVERSIONS
	public:
		/// <summary>
		/// <para> Converts this Quaternion to a 3D EmuMath Vector of Euler angles. </para>
		/// <para> May optionally output as either radians or degrees. If `OutRads_` is omitted, it will be treated as `true` and thus output will be in radians. </para>
		/// <para> May provide an optional Epsilon value for floating-point near-equality checks. If not passed, a default epsilon based on calculation type will be chosen. </para>
		/// <para> 
		///		Note that the same Quaternion can be represented by multiple Euler rotations; 
		///		as such, it is not uncommon for a Quaternion created from Euler angles to output a different set of angles compared to what it received as input.
		/// </para>
		/// </summary>
		/// <param name="epsilon_">Optional epsilon value to use for floating-point near-equal comparisons. Will default to a suitable epsilon for calculations if omitted.</param>
		/// <returns>3D EmuMath Vector of Euler angles X, Y, Z represented by this Quaternion.</returns>
		template<bool OutRads_, typename OutT_ = preferred_floating_point, typename Epsilon_>
		[[nodiscard]] constexpr inline auto ToEuler(Epsilon_&& epsilon_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_convert_to_euler<OutRads_, OutT_, T_, Epsilon_, false>(), EmuMath::Vector<3, OutT_>>
		{
			return EmuMath::Helpers::quaternion_to_euler<OutRads_, OutT_>(*this, std::forward<Epsilon_>(epsilon_));
		}

		template<bool OutRads_, typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto ToEuler() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_convert_to_euler<OutRads_, OutT_, T_, false>(), EmuMath::Vector<3, OutT_>>
		{
			return EmuMath::Helpers::quaternion_to_euler<OutRads_, OutT_>(*this);
		}

		template<typename OutT_ = preferred_floating_point, typename Epsilon_>
		[[nodiscard]] constexpr inline auto ToEuler(Epsilon_&& epsilon_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_convert_to_euler<true, OutT_, T_, Epsilon_, false>(), EmuMath::Vector<3, OutT_>>
		{
			return EmuMath::Helpers::quaternion_to_euler<true, OutT_>(*this, std::forward<Epsilon_>(epsilon_));
		}

		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto ToEuler() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_convert_to_euler<true, OutT_, T_, false>(), EmuMath::Vector<3, OutT_>>
		{
			return EmuMath::Helpers::quaternion_to_euler<true, OutT_>(*this);
		}

		/// <summary>
		/// <para> Converts this Quaternion to a 3D EmuMath Vector of Euler angles. </para>
		/// <para> May optionally output as either radians or degrees. If `OutRads_` is omitted, it will be treated as `true` and thus output will be in radians. </para>
		/// <para> May provide an optional Epsilon value for floating-point near-equality checks. If not passed, a default epsilon based on calculation type will be chosen. </para>
		/// <para> 
		///		Note that the same Quaternion can be represented by multiple Euler rotations; 
		///		as such, it is not uncommon for a Quaternion created from Euler angles to output a different set of angles compared to what it received as input.
		/// </para>
		/// <para>
		///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
		///		Use of such instructions may improve accuracy and/or performance.
		/// </para>
		/// </summary>
		/// <param name="epsilon_">Optional epsilon value to use for floating-point near-equal comparisons. Will default to a suitable epsilon for calculations if omitted.</param>
		/// <returns>3D EmuMath Vector of Euler angles X, Y, Z represented by this Quaternion.</returns>
		template<bool OutRads_, typename OutT_ = preferred_floating_point, typename Epsilon_>
		[[nodiscard]] constexpr inline auto ToEulerFused(Epsilon_&& epsilon_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_convert_to_euler_fused<OutRads_, OutT_, T_, Epsilon_, false>(), EmuMath::Vector<3, OutT_>>
		{
			return EmuMath::Helpers::quaternion_to_euler_fused<OutRads_, OutT_>(*this, std::forward<Epsilon_>(epsilon_));
		}

		template<bool OutRads_, typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto ToEulerFused() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_convert_to_euler_fused<OutRads_, OutT_, T_, false>(), EmuMath::Vector<3, OutT_>>
		{
			return EmuMath::Helpers::quaternion_to_euler_fused<OutRads_, OutT_>(*this);
		}

		template<typename OutT_ = preferred_floating_point, typename Epsilon_>
		[[nodiscard]] constexpr inline auto ToEulerFused(Epsilon_&& epsilon_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_convert_to_euler_fused<true, OutT_, T_, Epsilon_, false>(), EmuMath::Vector<3, OutT_>>
		{
			return EmuMath::Helpers::quaternion_to_euler_fused<true, OutT_>(*this, std::forward<Epsilon_>(epsilon_));
		}

		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto ToEulerFused() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_convert_to_euler_fused<true, OutT_, T_, false>(), EmuMath::Vector<3, OutT_>>
		{
			return EmuMath::Helpers::quaternion_to_euler_fused<true, OutT_>(*this);
		}

		/// <summary>
		/// <para> Converts this Quaternion to a 3D EmuMath Vector of Euler angles. </para>
		/// <para> May optionally output as either radians or degrees. If `OutRads_` is omitted, it will be treated as `true` and thus output will be in radians. </para>
		/// <para> May provide an optional Epsilon value for floating-point near-equality checks. If not passed, a default epsilon based on calculation type will be chosen. </para>
		/// <para> 
		///		Note that the same Quaternion can be represented by multiple Euler rotations; 
		///		as such, it is not uncommon for a Quaternion created from Euler angles to output a different set of angles compared to what it received as input.
		/// </para>
		/// <para> This function will attempt to be constexpr-evaluable, which may have an effect on accuracy and/or performance. </para>
		/// </summary>
		/// <param name="epsilon_">Optional epsilon value to use for floating-point near-equal comparisons. Will default to a suitable epsilon for calculations if omitted.</param>
		/// <returns>3D EmuMath Vector of Euler angles X, Y, Z represented by this Quaternion.</returns>
		template<bool OutRads_, typename OutT_ = preferred_floating_point, typename Epsilon_>
		[[nodiscard]] constexpr inline auto ToEulerConstexpr(Epsilon_&& epsilon_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_convert_to_euler_constexpr<OutRads_, OutT_, T_, Epsilon_, false>(), EmuMath::Vector<3, OutT_>>
		{
			return EmuMath::Helpers::quaternion_to_euler_constexpr<OutRads_, OutT_>(*this, std::forward<Epsilon_>(epsilon_));
		}

		template<bool OutRads_, typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto ToEulerConstexpr() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_convert_to_euler_constexpr<OutRads_, OutT_, T_, false>(), EmuMath::Vector<3, OutT_>>
		{
			return EmuMath::Helpers::quaternion_to_euler_constexpr<OutRads_, OutT_>(*this);
		}

		template<typename OutT_ = preferred_floating_point, typename Epsilon_>
		[[nodiscard]] constexpr inline auto ToEulerConstexpr(Epsilon_&& epsilon_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_convert_to_euler_constexpr<true, OutT_, T_, Epsilon_, false>(), EmuMath::Vector<3, OutT_>>
		{
			return EmuMath::Helpers::quaternion_to_euler_constexpr<true, OutT_>(*this, std::forward<Epsilon_>(epsilon_));
		}

		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto ToEulerConstexpr() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_convert_to_euler_constexpr<true, OutT_, T_, false>(), EmuMath::Vector<3, OutT_>>
		{
			return EmuMath::Helpers::quaternion_to_euler_constexpr<true, OutT_>(*this);
		}
#pragma endregion

#pragma region QUATERNION_OPERATIONS
	public:		
		/// <summary>
		/// <para> Outputs the squared Norm (aka: Length) of this Quaternion as the specified type (defaulting to this Quaternion's `preferred_floating_point`). </para>
		/// </summary>
		/// <returns>The squared Norm of this Quaternion.</returns>
		template<typename Out_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto SquareNorm() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_square_norm<T_, Out_, false>(), Out_>
		{
			return EmuMath::Helpers::quaternion_square_norm<Out_>(*this);
		}

		/// <summary>
		/// <para> Outputs the squared Norm (aka: Length) of this Quaternion as the specified type (defaulting to this Quaternion's `preferred_floating_point`). </para>
		/// <para>
		///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
		///		Use of such instructions may improve accuracy and/or performance.
		/// </para>
		/// </summary>
		/// <returns>The squared Norm of this Quaternion.</returns>
		template<typename Out_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto FusedSquareNorm() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_fused_square_norm<T_, Out_, false>(), Out_>
		{
			return EmuMath::Helpers::quaternion_fused_square_norm<Out_>(*this);
		}

		/// <summary>
		/// <para> Outputs the Norm (aka: Length) of this Quaternion as the specified type (defaulting to this Quaternion's `preferred_floating_point`). </para>
		/// </summary>
		/// <returns>The Norm of this Quaternion.</returns>
		template<typename Out_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto Norm() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_norm<T_, Out_, false>(), Out_>
		{
			return EmuMath::Helpers::quaternion_norm<Out_>(*this);
		}

		/// <summary>
		/// <para> Outputs the Norm (aka: Length) of this Quaternion as the specified type (defaulting to this Quaternion's `preferred_floating_point`). </para>
		/// <para>
		///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
		///		Use of such instructions may improve accuracy and/or performance.
		/// </para>
		/// </summary>
		/// <returns>The Norm of this Quaternion.</returns>
		template<typename Out_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto FusedNorm() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_fused_norm<T_, Out_, false>(), Out_>
		{
			return EmuMath::Helpers::quaternion_fused_norm<Out_>(*this);
		}

		/// <summary>
		/// <para> Outputs the Norm (aka: Length) of this Quaternion as the specified type (defaulting to this Quaternion's `preferred_floating_point`). </para>
		/// <para> This function will attempt to be constexpr-evaluable, which may have an effect on accuracy and/or performance. </para>
		/// </summary>
		/// <returns>The Norm of this Quaternion.</returns>
		template<typename Out_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto NormConstexpr() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_norm_constexpr<T_, Out_, true>(), Out_>
		{
			return EmuMath::Helpers::quaternion_norm_constexpr<Out_>(*this);
		}

		/// <summary>
		/// <para> Outputs a new Quaternion that is the result of linearly interpolating this Quaternion with Quaternion b_ and a weighting of t_. </para>
		/// <para> Typically, Slerp (Spherical linear interpolation) is likely to be preferred for smoother interpolations. </para>
		/// <para> The resulting Quaternion is not automatically normalised, so arguments that may result in a non-unit Quaternion should be considered. </para>
		/// </summary>
		/// <param name="b_">Quaternion to linearly interpolate this Quaternion with.</param>
		/// <param name="t_">Weighting for interpolation, which may be either this Quternion's `preferred_floating_point` or an EmuMath Vector of respective weightings.</param>
		/// <returns>Quaternion resulting from the linear interpolation.</returns>
		template<typename OutT_ = preferred_floating_point, typename BT_>
		[[nodiscard]] constexpr inline auto Lerp(const EmuMath::Quaternion<BT_>& b_, const preferred_floating_point& t_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_lerp_valid_args<T_, BT_, const preferred_floating_point&, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_lerp<OutT_>(*this, b_, t_);
		}

		template<typename OutT_ = preferred_floating_point, typename BT_, std::size_t TArgSize_, typename TArgT_>
		[[nodiscard]] constexpr inline auto Lerp(const EmuMath::Quaternion<BT_>& b_, const EmuMath::Vector<TArgSize_, TArgT_>& t_) const
			-> std::enable_if_t
			<
				EmuMath::Helpers::quaternion_lerp_valid_args<T_, BT_, const EmuMath::Vector<TArgSize_, TArgT_>&, OutT_, false>(),
				EmuMath::Quaternion<OutT_>
			>
		{
			return EmuMath::Helpers::quaternion_lerp<OutT_>(*this, b_, t_);
		}
		
		/// <summary>
		/// <para> Outputs a new Quaternion that is the result of linearly interpolating this Quaternion with Quaternion b_ and a weighting of t_. </para>
		/// <para> Typically, Slerp (Spherical linear interpolation) is likely to be preferred for smoother interpolations. </para>
		/// <para> The resulting Quaternion is not automatically normalised, so arguments that may result in a non-unit Quaternion should be considered. </para>
		/// <para>
		///		This function will take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
		///		Use of such instructions may improve accuracy and/or performance.
		/// </para>
		/// </summary>
		/// <param name="b_">Quaternion to linearly interpolate this Quaternion with.</param>
		/// <param name="t_">Weighting for interpolation, which may be either this Quternion's `preferred_floating_point` or an EmuMath Vector of respective weightings.</param>
		/// <returns>Quaternion resulting from the linear interpolation.</returns>
		template<typename OutT_ = preferred_floating_point, typename BT_>
		[[nodiscard]] constexpr inline auto FusedLerp(const EmuMath::Quaternion<BT_>& b_, const preferred_floating_point& t_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_fused_lerp_valid_args<T_, BT_, const preferred_floating_point&, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_fused_lerp<OutT_>(*this, b_, t_);
		}

		template<typename OutT_ = preferred_floating_point, typename BT_, std::size_t TArgSize_, typename TArgT_>
		[[nodiscard]] constexpr inline auto FusedLerp(const EmuMath::Quaternion<BT_>& b_, const EmuMath::Vector<TArgSize_, TArgT_>& t_) const
			-> std::enable_if_t
			<
				EmuMath::Helpers::quaternion_fused_lerp_valid_args<T_, BT_, const EmuMath::Vector<TArgSize_, TArgT_>&, OutT_, false>(),
				EmuMath::Quaternion<OutT_>
			>
		{
			return EmuMath::Helpers::quaternion_fused_lerp<OutT_>(*this, b_, t_);
		}

		/// <summary>
		/// <para> Outputs a new Quaternion that is the result of a spherical linear interpolation of this Quaternion with Quaternion b_ and a weighting of t_. </para>
		/// <para> Typically, this is likely to be preferred over a plain Lerp for smoother interpolations. </para>
		/// <para> The resulting Quaternion is not automatically normalised, so arguments that may result in a non-unit Quaternion should be considered. </para>
		/// </summary>
		/// <param name="b_">Quaternion to spherically linearly interpolate this Quaternion with.</param>
		/// <param name="t_">Weighting for interpolation.</param>
		/// <returns>Quaternion resulting from the spherical linear interpolation.</returns>
		template<typename OutT_ = preferred_floating_point, typename BT_>
		[[nodiscard]] constexpr inline auto Slerp(const EmuMath::Quaternion<BT_>& b_, const preferred_floating_point& t_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_slerp_valid_args<T_, BT_, const preferred_floating_point&, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_slerp<OutT_>(*this, b_, t_);
		}

		/// <summary>
		/// <para> Outputs a new Quaternion that is the result of a spherical linear interpolation of this Quaternion with Quaternion b_ and a weighting of t_. </para>
		/// <para> Typically, this is likely to be preferred over a plain Lerp for smoother interpolations. </para>
		/// <para> The resulting Quaternion is not automatically normalised, so arguments that may result in a non-unit Quaternion should be considered. </para>
		/// <para> Relevant functions will aim to be constexpr-evaluable if possible. </para>
		/// </summary>
		/// <param name="b_">Quaternion to spherically linearly interpolate this Quaternion with.</param>
		/// <param name="t_">Weighting for interpolation.</param>
		/// <returns>Quaternion resulting from the spherical linear interpolation.</returns>
		template<typename OutT_ = preferred_floating_point, typename BT_>
		[[nodiscard]] constexpr inline auto SlerpConstexpr(const EmuMath::Quaternion<BT_>& b_, const preferred_floating_point& t_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_slerp_constexpr_valid_args<T_, BT_, preferred_floating_point, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_slerp_constexpr<OutT_>(*this, b_, t_);
		}

		/// <summary>
		/// <para> Outputs a new Quaternion that is the result of a spherical linear interpolation of this Quaternion with Quaternion b_ and a weighting of t_. </para>
		/// <para> Typically, this is likely to be preferred over a plain Lerp for smoother interpolations. </para>
		/// <para> The resulting Quaternion is not automatically normalised, so arguments that may result in a non-unit Quaternion should be considered. </para>
		/// <para>
		///		This function will take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
		///		Use of such instructions may improve accuracy and/or performance.
		/// </para>
		/// </summary>
		/// <param name="b_">Quaternion to spherically linearly interpolate this Quaternion with.</param>
		/// <param name="t_">Weighting for interpolation.</param>
		/// <returns>Quaternion resulting from the spherical linear interpolation.</returns>
		template<typename OutT_ = preferred_floating_point, typename BT_>
		[[nodiscard]] constexpr inline auto FusedSlerp(const EmuMath::Quaternion<BT_>& b_, const preferred_floating_point& t_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_fused_slerp_valid_args<T_, BT_, preferred_floating_point, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_fused_slerp<OutT_>(*this, b_, t_);
		}

		/// <summary>
		/// <para> Returns the form of this Quaternion with its imaginary component (i.e. X, Y, Z) negated. </para>
		/// <para> The type of the output Quaternion may be customised, and defaults to this Quaternion's `preferred_floating_point`. </para>
		/// </summary>
		/// <returns>Quaternion representing this Quaternion's conjugate.</returns>
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto Conjugate() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_conjugate<T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_conjugate<OutT_>(*this);
		}

		/// <summary>
		/// <para> Returns the inverse form of this Quaternion, which is equivalent to its Conjugate normalised. </para>
		/// <para>
		///		If this Quaternion is known to have a length of 1, this is mathematically identical to `Conjugate`, 
		///		although floating-point errors may produce different results.
		/// </para>
		/// <para> May optionally choose reciprocal multiplication instead of division for normalisation. If `PreferMultiplies_` is omitted, it will be considered `false`. </para>
		/// </summary>
		/// <returns>Quaternion representing the inverse of this Quaternion.</returns>
		template<bool PreferMultiplies_, typename OutT_ = preferred_floating_point >
		[[nodiscard]] constexpr inline auto Inverse() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_inverse<PreferMultiplies_, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_inverse<PreferMultiplies_, OutT_>(*this);
		}

		template<typename OutT_ = preferred_floating_point >
		[[nodiscard]] constexpr inline auto Inverse() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_inverse<false, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_inverse<false, OutT_>(*this);
		}

		/// <summary>
		/// <para> Returns the inverse form of this Quaternion, which is equivalent to its Conjugate normalised. </para>
		/// <para>
		///		If this Quaternion is known to have a length of 1, this is mathematically identical to `Conjugate`, 
		///		although floating-point errors may produce different results.
		/// </para>
		/// <para> May optionally choose reciprocal multiplication instead of division for normalisation. If `PreferMultiplies_` is omitted, it will be considered `false`. </para>
		/// <para>
		///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
		///		Use of such instructions may improve accuracy and/or performance.
		/// </para>
		/// </summary>
		/// <returns>Quaternion representing the inverse of this Quaternion.</returns>
		template<bool PreferMultiplies_, typename OutT_ = preferred_floating_point >
		[[nodiscard]] constexpr inline auto FusedInverse() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_fused_inverse<PreferMultiplies_, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_fused_inverse<PreferMultiplies_, OutT_>(*this);
		}

		template<typename OutT_ = preferred_floating_point >
		[[nodiscard]] constexpr inline auto FusedInverse() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_fused_inverse<false, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_fused_inverse<false, OutT_>(*this);
		}

		/// <summary>
		/// <para> Returns the inverse form of this Quaternion, which is equivalent to its Conjugate normalised. </para>
		/// <para>
		///		If this Quaternion is known to have a length of 1, this is mathematically identical to `Conjugate`, 
		///		although floating-point errors may produce different results.
		/// </para>
		/// <para> May optionally choose reciprocal multiplication instead of division for normalisation. If `PreferMultiplies_` is omitted, it will be considered `false`. </para>
		/// <para> If possible, this expression will aim to be constexpr-evaluable. This may affect accuracy and/or performance. </para>
		/// </summary>
		/// <returns>Quaternion representing the inverse of this Quaternion.</returns>
		template<bool PreferMultiplies_, typename OutT_ = preferred_floating_point >
		[[nodiscard]] constexpr inline auto InverseConstexpr() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_inverse_constexpr<PreferMultiplies_, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_inverse_constexpr<PreferMultiplies_, OutT_>(*this);
		}

		template<typename OutT_ = preferred_floating_point >
		[[nodiscard]] constexpr inline auto InverseConstexpr() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_inverse_constexpr<false, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_inverse_constexpr<false, OutT_>(*this);
		}

		/// <summary>
		/// <para> Outputs the Unit form of this Quaternion (aka: its normalised form). </para>
		/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
		/// </summary>
		/// <returns>A normalised copy of this Quaternion.</returns>
		template<bool PreferMultiplies_, typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto Unit() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_unit<PreferMultiplies_, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_unit<PreferMultiplies_, OutT_>(*this);
		}

		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto Unit() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_unit<false, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_unit<false, OutT_>(*this);
		}

		/// <summary>
		/// <para> Outputs the Unit form of this Quaternion (aka: its normalised form). </para>
		/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
		/// <para>
		///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
		///		Use of such instructions may improve accuracy and/or performance.
		/// </para>
		/// </summary>
		/// <returns>A normalised copy of this Quaternion.</returns>
		template<bool PreferMultiplies_, typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto FusedUnit() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_fused_unit<PreferMultiplies_, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_fused_unit<PreferMultiplies_, OutT_>(*this);
		}

		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto FusedUnit() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_fused_unit<false, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_fused_unit<false, OutT_>(*this);
		}

		/// <summary>
		/// <para> Outputs the Unit form of this Quaternion (aka: its normalised form). </para>
		/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
		/// <para> This function will attempt to be constexpr-evaluable, which may have an effect on accuracy and/or performance. </para>
		/// </summary>
		/// <returns>A normalised copy of this Quaternion.</returns>
		template<bool PreferMultiplies_, typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto UnitConstexpr() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_unit_constexpr<PreferMultiplies_, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_unit_constexpr<PreferMultiplies_, OutT_>(*this);
		}

		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto UnitConstexpr() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_unit_constexpr<false, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_unit_constexpr<false, OutT_>(*this);
		}

		/// <summary>
		/// <para> Normalises and assigns this Quaternion into its Unit form. </para>
		/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be default to `false`. </para>
		/// </summary>
		template<bool PreferMultiplies_ = false>
		constexpr inline auto AssignUnit()
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_assign_unit<PreferMultiplies_, T_, false>(), void>
		{
			EmuMath::Helpers::quaternion_assign_unit<PreferMultiplies_>(*this);
		}

		/// <summary>
		/// <para> Normalises and assigns this Quaternion into its Unit form. </para>
		/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be default to `false`. </para>
		/// <para>
		///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
		///		Use of such instructions may improve accuracy and/or performance.
		/// </para>
		/// </summary>
		template<bool PreferMultiplies_ = false>
		constexpr inline auto AssignFusedUnit()
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_assign_fused_unit<PreferMultiplies_, T_, false>(), void>
		{
			EmuMath::Helpers::quaternion_assign_fused_unit<PreferMultiplies_>(*this);
		}

		/// <summary>
		/// <para> Normalises and assigns this Quaternion into its Unit form. </para>
		/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be default to `false`. </para>
		/// <para> This function will attempt to be constexpr-evaluable, which may have an effect on accuracy and/or performance. </para>
		/// </summary>
		template<bool PreferMultiplies_ = false>
		constexpr inline auto AssignUnitConstexpr()
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_assign_unit_constexpr<PreferMultiplies_, T_, false>(), void>
		{
			EmuMath::Helpers::quaternion_assign_unit_constexpr<PreferMultiplies_>(*this);
		}
#pragma endregion

#pragma region CONST_ARITHMETIC
	public:
		template<typename OutT_ = preferred_floating_point, typename RhsT_>
		[[nodiscard]] constexpr inline auto Add(const EmuMath::Quaternion<RhsT_>& rhs_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_add<T_, RhsT_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_add<OutT_>(*this, rhs_);
		}

		template<typename OutT_ = preferred_floating_point, typename RhsT_>
		[[nodiscard]] constexpr inline auto Subtract(const EmuMath::Quaternion<RhsT_>& rhs_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_subtract<T_, RhsT_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_subtract<OutT_>(*this, rhs_);
		}

		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto Negate() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_negate<T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_negate<OutT_>(*this);
		}

		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto Multiply(const preferred_floating_point& rhs_scalar_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_scalar_multiply<T_, const preferred_floating_point&, OutT_, false>, EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_multiply_by_scalar<OutT_>(*this, rhs_scalar_);
		}

		template<typename OutT_ = preferred_floating_point, typename RhsT_>
		[[nodiscard]] constexpr inline auto Multiply(const EmuMath::Quaternion<RhsT_>& rhs_quaternion_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_quaternion_multiply<T_, RhsT_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_multiply_by_quaternion<OutT_>(*this, rhs_quaternion_);
		}

		template<typename OutT_ = preferred_floating_point, typename RhsT_>
		[[nodiscard]] constexpr inline auto FusedMultiply(const EmuMath::Quaternion<RhsT_>& rhs_quaternion_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_fused_quaternion_multiply<T_, RhsT_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_multiply_by_quaternion<OutT_>(*this, rhs_quaternion_);
		}

		template<typename OutT_ = preferred_floating_point>
		constexpr inline auto Divide(const preferred_floating_point& rhs_scalar_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_divide<T_, const preferred_floating_point&, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_divide<OutT_>(*this, rhs_scalar_);
		}
#pragma endregion

#pragma region ASSIGNING_ARITHMETIC
	public:
		template<typename RhsT_>
		constexpr inline auto AddAssign(const EmuMath::Quaternion<RhsT_>& rhs_)
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_add_assign<T_, RhsT_, false>(), this_type&>
		{
			EmuMath::Helpers::quaternion_add_assign(*this, rhs_);
			return *this;
		}

		template<typename RhsT_>
		constexpr inline auto SubtractAssign(const EmuMath::Quaternion<RhsT_>& rhs_)
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_subtract_assign<T_, RhsT_, false>(), this_type&>
		{
			EmuMath::Helpers::quaternion_subtract_assign(*this, rhs_);
			return *this;
		}

		template<std::size_t Unused_ = 0>
		constexpr inline auto NegateAssign()
			-> std::enable_if_t<_can_negate_assign<Unused_>(), this_type&>
		{
			EmuMath::Helpers::quaternion_negate_assign(*this);
			return *this;
		}

		template<std::size_t Unused_ = 0>
		constexpr inline auto MultiplyAssign(const preferred_floating_point& rhs_scalar_)
			-> std::enable_if_t<_can_scalar_multiply_assign<Unused_>(), this_type&>
		{
			EmuMath::Helpers::quaternion_multiply_assign_by_scalar(*this, rhs_scalar_);
			return *this;
		}

		template<typename RhsT_>
		constexpr inline auto MultiplyAssign(const EmuMath::Quaternion<RhsT_>& rhs_quaternion_)
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_quaternion_multiply_assign<T_, RhsT_, false>(), this_type&>
		{
			EmuMath::Helpers::quaternion_multiply_assign_by_quaternion(*this, rhs_quaternion_);
			return *this;
		}

		template<typename RhsT_>
		constexpr inline auto FusedMultiplyAssign(const EmuMath::Quaternion<RhsT_>& rhs_quaternion_)
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_fused_quaternion_multiply_assign<T_, RhsT_, false>(), this_type&>
		{
			EmuMath::Helpers::quaternion_fused_multiply_assign_by_quaternion(*this, rhs_quaternion_);
			return *this;
		}

		template<std::size_t Unused_>
		constexpr inline auto DivideAssign(const preferred_floating_point& rhs_scalar_)
			-> std::enable_if_t<_can_divide_assign<Unused_>(), this_type&>
		{
			EmuMath::Helpers::quaternion_divide_assign(*this, rhs_scalar_);
			return *this;
		}
#pragma endregion

#pragma region UNDERLYING_DATA
	public:
		/// <summary>
		/// <para> The underlying data of this Quaternion, represented as a Vector. </para>
		/// <para> This should not be modified directly unless you are sure that you know what you're doing. </para>
		/// </summary>
		vector_type data;
#pragma endregion
	};
}

template<typename T_>
inline std::ostream& operator<<(std::ostream& str_, const EmuMath::Quaternion<T_>& quaternion_)
{
	str_ << quaternion_.data;
	return str_;
}

template<typename T_>
inline std::wostream& operator<<(std::wostream& w_str_, const EmuMath::Quaternion<T_>& quaternion_)
{
	w_str_ << quaternion_.data;
	return w_str_;
}

#endif
