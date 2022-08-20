#ifndef EMU_MATH_RECT_T_H_INC_
#define EMU_MATH_RECT_T_H_INC_ 1

#include "_helpers/_all_rect_helpers.h"
#include "../../Vector.h"

namespace EmuMath
{
	/// <summary>
	/// <para> Type used to store and retrieve basic information regarding a rectangle, with the origin point (0, 0) at a theoretical top-left. </para>
	/// </summary>
	template<typename T_>
	struct Rect
	{
#pragma region NON_STD_IMPLEMENTATION_DETAILS
	private:
		using _underlying_vector = EmuMath::Vector<4, T_>;
		static constexpr std::size_t _left_index = 0;
		static constexpr std::size_t _top_index = 1;
		static constexpr std::size_t _right_index = 2;
		static constexpr std::size_t _bottom_index = 3;
#pragma endregion

#pragma region STD_IMPLEMENTATION_DETAILS
	public:
		using this_type = Rect<T_>;
		using stored_type = typename _underlying_vector::stored_type;
		using value_type = typename _underlying_vector::value_type;
		using value_type_uq = typename _underlying_vector::value_type_uq;
		using preferred_floating_point = typename _underlying_vector::preferred_floating_point;
#pragma endregion

#pragma region STD_IMPLEMENTATION_FUNCS
	public:
		[[nodiscard]] static constexpr inline value_type_uq get_implied_zero()
		{
			return _underlying_vector::get_implied_zero();
		}
#pragma endregion

#pragma region NON_STD_IMPLEMENTATION_FUNCS
	private:
		template<typename Left_, typename Top_, typename Right_, typename Bottom_>
		[[nodiscard]] static constexpr inline _underlying_vector _make_data(Left_&& left_, Top_&& top_, Right_&& right_, Bottom_&& bottom_)
		{
			return _underlying_vector(std::forward<Left_>(left_), std::forward<Top_>(top_), std::forward<Right_>(right_), std::forward<Bottom_>(bottom_));
		}

		template<typename Width_, typename Height_>
		[[nodiscard]] static constexpr inline _underlying_vector _make_data(Width_&& width_, Height_&& height_)
		{
			return _underlying_vector(get_implied_zero(), get_implied_zero(), std::forward<Width_>(width_), std::forward<Height_>(height_));
		}

		template<typename Size_>
		[[nodiscard]] static constexpr inline _underlying_vector _make_data(Size_&& size_)
		{
			auto& size = EmuCore::TMP::lval_ref_cast<Size_>(std::forward<Size_>(size_));
			return _underlying_vector(get_implied_zero(), get_implied_zero(), static_cast<value_type>(size), static_cast<value_type>(size));
		}
#pragma endregion

#pragma region CONSTRUCTORS
	public:
		constexpr inline Rect() : _left_top_right_bottom()
		{
		}

		constexpr inline Rect(const Rect<T_>& to_copy_) :
			_left_top_right_bottom(to_copy_._left_top_right_bottom)
		{
		}

		constexpr inline Rect(Rect<T_>&& to_move_) noexcept : 
			_left_top_right_bottom(std::move(to_move_._left_top_right_bottom))
		{
		}

		/// <summary>
		/// <para> Creates a Rect as a square of the specified size, with its top-left corner at point (0, 0). </para>
		/// </summary>
		/// <param name="size_">Size of the square to create the Rect as.</param>
		template<typename Size_>
		explicit constexpr inline Rect(Size_&& size_) :
			_left_top_right_bottom(_make_data(std::forward<Size_>(size_)))
		{
		}

		/// <summary>
		/// <para> Creates a Rect of the specified size, with its top-left corner at the point (0, 0). </para>
		/// </summary>
		/// <param name="width_">Size of the Rect in the X-axis.</param>
		/// <param name="height_">Size of the Rect in the Y-axis.</param>
		template<typename Width_, typename Height_>
		constexpr inline Rect(Width_&& width_, Height_&& height_) : 
			_left_top_right_bottom(_make_data(std::forward<Width_>(width_), std::forward<Height_>(height_)))
		{
		}

		/// <summary>
		/// <para> Creates a Rect with the axes of its borders defined by the respective passed values. </para>
		/// </summary>
		/// <param name="left_">X-coordinate of the Rect's left boundary. This should be the smallest value in the X-axis to be considered well-formed.</param>
		/// <param name="top_">Y-coordinate of the Rect's top boundary. This should be the smallest value in the Y-axis to be considered well-formed.</param>
		/// <param name="right_">X-coordinate of the Rect's right boundary. This should be the highest value in the X-axis to be considered well-formed.</param>
		/// <param name="bottom_">Y-coordinate of the Rect's bottom boundary. This should be the highest value in the Y-axis to be considered well-formed.</param>
		template<typename Left_, typename Top_, typename Right_, typename Bottom_>
		constexpr inline Rect(Left_&& left_, Top_&& top_, Right_&& right_, Bottom_&& bottom_) :
			_left_top_right_bottom(_make_data(std::forward<Left_>(left_), std::forward<Top_>(top_), std::forward<Right_>(right_), std::forward<Bottom_>(bottom_)))
		{
		}

		/// <summary>
		/// <para> Converts the input Rect into the newly constructed type of Rect. </para>
		/// </summary>
		/// <param name="to_copy_">Rect of a different type to copy/convert.</param>
		template<typename ToCopyT_, typename = std::enable_if_t<!std::is_same_v<T_, ToCopyT_>>>
		explicit constexpr inline Rect(const EmuMath::Rect<ToCopyT_>& to_copy_) :
			_left_top_right_bottom(_make_data(to_copy_.Left(), to_copy_.Top(), to_copy_.Right(), to_copy_.Bottom()))
		{
		}

		/// <summary>
		/// <para> Converts the input Rect into the newly constructed type of Rect. </para>
		/// </summary>
		/// <param name="to_copy_">Rect of a different type to copy/convert.</param>
		template<typename ToCopyT_, typename = std::enable_if_t<!std::is_same_v<T_, ToCopyT_>>>
		explicit constexpr inline Rect(EmuMath::Rect<ToCopyT_>& to_copy_) :
			_left_top_right_bottom(_make_data(to_copy_.Left(), to_copy_.Top(), to_copy_.Right(), to_copy_.Bottom()))
		{
		}
			
		/// <summary>
		/// <para> Moves and converts the input Rect into the newly constructed type of Rect. </para>
		/// </summary>
		/// <param name="to_move_">Rect of a different type to move/convert.</param>
		template<typename ToCopyT_, typename = std::enable_if_t<!std::is_same_v<T_, ToCopyT_>>>
		explicit constexpr inline Rect(EmuMath::Rect<ToCopyT_>&& to_move_) :
			_left_top_right_bottom(_make_data(std::move(to_move_.Left()), std::move(to_move_.Top()), std::move(to_move_.Right()), std::move(to_move_.Bottom())))
		{
		}
#pragma endregion

#pragma region ASSIGNMENT_FUNCS
	public:
		/// <summary>
		/// <para> Sets this Rectangle's boundaries to the respective passed values. </para>
		/// <para> If `left_` is greater than `right_`, or `top_` is greater than `bottom_`, this makes the Rect ill-formed. </para>
		/// <para> Rectangles exist in a space where the origin point (0, 0) is in the top-left corner. </para>
		/// </summary>
		/// <param name="left_">X-coordinate of the leftmost boundary of the Rectangle.</param>
		/// <param name="top_">Y-coordinate of the topmost boundary of the Rectangle.</param>
		/// <param name="right_">X-coordinate of the rightmost boundary of the Rectangle.</param>
		/// <param name="bottom_">Y-coordinate of the bottommost boundary of the Rectangle.</param>
		template<typename Left_, typename Top_, typename Right_, typename Bottom_>
		constexpr inline void Set(Left_&& left_, Top_&& top_, Right_&& right_, Bottom_&& bottom_)
		{
			EmuCore::TMP::assign_direct_or_cast<value_type_uq>(Left(), std::forward<Left_>(left_));
			EmuCore::TMP::assign_direct_or_cast<value_type_uq>(Top(), std::forward<Top_>(top_));
			EmuCore::TMP::assign_direct_or_cast<value_type_uq>(Right(), std::forward<Right_>(right_));
			EmuCore::TMP::assign_direct_or_cast<value_type_uq>(Bottom(), std::forward<Bottom_>(bottom_));
		}
#pragma endregion

#pragma region ASSIGNMENT_OPERATORS
	public:
		constexpr inline this_type& operator=(const Rect<T_>& to_copy_)
		{
			_left_top_right_bottom = to_copy_._left_top_right_bottom;
			return *this;
		}

		constexpr inline this_type& operator=(Rect<T_>& to_copy_)
		{
			_left_top_right_bottom = to_copy_._left_top_right_bottom;
			return *this;
		}

		constexpr inline this_type& operator=(Rect<T_>&& to_move_) noexcept
		{
			_left_top_right_bottom = std::move(to_move_._left_top_right_bottom);
			return *this;
		}

		template<typename RhsT_>
		constexpr inline this_type& operator=(const Rect<RhsT_>& rhs_)
		{
			EmuMath::Helpers::rect_cast(*this, rhs_);
			return *this;
		}

		template<typename RhsT_>
		constexpr inline this_type& operator=(Rect<RhsT_>& rhs_)
		{
			EmuMath::Helpers::rect_cast(*this, rhs_);
			return *this;
		}

		template<typename RhsT_>
		constexpr inline this_type& operator=(Rect<RhsT_>&& rhs_)
		{
			EmuMath::Helpers::rect_cast(*this, std::move(rhs_));
			return *this;
		}
#pragma endregion

#pragma region CONST_ARITHMETIC_OPERATORS
	public:
		/// <summary>
		/// <para>
		///		Creates a copy of this Rect scaled about its centre, 
		///		changing all boundaries to scale its size in respective axes whilst maintaining the same central point.
		/// </para>
		/// <para> This assumes that the Rect is well-formed. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `preferred_floating_point`. </para>
		/// </summary>
		/// <param name="scale_vector_2d_">EmuMath Vector of scales to apply to this Rect, with X and Y at theoretical indices 0 and 1 respectively.</param>
		/// <returns>This Rect scaled by the provided factors in respective axes, with the same central point.</returns>
		template<typename OutT_ = preferred_floating_point, EmuConcepts::EmuVector ScaleVector_>
		[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> operator*(ScaleVector_&& scale_vector_2d_) const
		{
			return EmuMath::Helpers::rect_scale<OutT_>(*this, std::forward<ScaleVector_>(scale_vector_2d_));
		}

		/// <summary>
		/// <para>
		///		Creates a copy of this Rect scaled about its centre, 
		///		changing all boundaries to scale its size in all axes whilst maintaining the same central point.
		/// </para>
		/// <para> This assumes that the Rect is well-formed. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `preferred_floating_point`. </para>
		/// </summary>
		/// <param name="scale_x_and_y_">Scale to apply to this Rect's width and height.</param>
		/// <returns>This Rect scaled by the provided factor in all axes, with the same central point.</returns>
		template<typename OutT_ = preferred_floating_point, typename ScaleScalar_>
		[[nodiscard]] constexpr inline auto operator*(ScaleScalar_&& scale_x_and_y_) const
			-> std::enable_if_t<!EmuMath::TMP::is_emu_vector_v<ScaleScalar_>, EmuMath::Rect<OutT_>>
		{
			return EmuMath::Helpers::rect_scale<OutT_>(*this, std::forward<ScaleScalar_>(scale_x_and_y_));
		}
#pragma endregion

#pragma region ARITHMETIC_ASSIGN_OPERATORS
	public:
		/// <summary>
		/// <para>
		///		Creates a copy of this Rect scaled about its centre, 
		///		changing all boundaries to scale its size in respective axes whilst maintaining the same central point.
		/// </para>
		/// <para> This assumes that the Rect is well-formed. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `preferred_floating_point`. </para>
		/// </summary>
		/// <param name="scale_vector_2d_">EmuMath Vector of scales to apply to this Rect, with X and Y at theoretical indices 0 and 1 respectively.</param>
		/// <returns>This Rect scaled by the provided factors in respective axes, with the same central point.</returns>
		template<EmuConcepts::EmuVector ScaleVector_>
		constexpr inline this_type& operator*=(ScaleVector_&& scale_vector_2d_)
		{
			return this->operator=(EmuMath::Helpers::rect_scale<value_type_uq>(*this, std::forward<ScaleVector_>(scale_vector_2d_)));
		}

		/// <summary>
		/// <para>
		///		Creates a copy of this Rect scaled about its centre, 
		///		changing all boundaries to scale its size in all axes whilst maintaining the same central point.
		/// </para>
		/// <para> This assumes that the Rect is well-formed. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `preferred_floating_point`. </para>
		/// </summary>
		/// <param name="scale_x_and_y_">Scale to apply to this Rect's width and height.</param>
		/// <returns>This Rect scaled by the provided factor in all axes, with the same central point.</returns>
		template<typename ScaleScalar_>
		constexpr inline auto operator*=(ScaleScalar_&& scale_x_and_y_)
			-> std::enable_if_t<!EmuMath::TMP::is_emu_vector_v<ScaleScalar_>, this_type&>
		{
			return this->operator=(EmuMath::Helpers::rect_scale<value_type_uq>(*this, std::forward<ScaleScalar_>(scale_x_and_y_)));
		}
#pragma endregion

#pragma region ACCESSORS
	public:
		/// <summary>
		/// <para> Retrieves a reference to the value indicating the X coordinate of corners on the left of this Rectangle. </para>
		/// </summary>
		/// <returns>Reference to the X coordinate of left corners in this Rectangle.</returns>
		[[nodiscard]] constexpr inline value_type& Left() &
		{
			return _left_top_right_bottom.template at<_left_index>();
		}

		[[nodiscard]] constexpr inline const value_type& Left() const&
		{
			return _left_top_right_bottom.template at<_left_index>();
		}

		[[nodiscard]] constexpr inline value_type&& Left() &&
		{
			return std::move(_left_top_right_bottom.template at<_left_index>());
		}

		/// <summary>
		/// <para> Retrieves a reference to the value indicating the X coordinate of corners on the right of this Rectangle. </para>
		/// </summary>
		/// <returns>Reference to the X coordinate of right corners in this Rectangle.</returns>
		[[nodiscard]] constexpr inline value_type& Right() &
		{
			return _left_top_right_bottom.template at<_right_index>();
		}

		[[nodiscard]] constexpr inline const value_type& Right() const&
		{
			return _left_top_right_bottom.template at<_right_index>();
		}

		/// <summary>
		/// <para> Retrieves a reference to the value indicating the Y coordinate of corners on the top of this Rectangle. </para>
		/// </summary>
		/// <returns>Reference to the Y coordinate of top corners in this Rectangle.</returns>
		[[nodiscard]] constexpr inline value_type& Top() &
		{
			return _left_top_right_bottom.template at<_top_index>();
		}

		[[nodiscard]] constexpr inline const value_type& Top() const&
		{
			return _left_top_right_bottom.template at<_top_index>();
		}

		/// <summary>
		/// <para> Retrieves a reference to the value indicating the Y coordinate of corners on the bottom of this Rectangle. </para>
		/// </summary>
		/// <returns>Reference to the Y coordinate of bottom corners in this Rectangle.</returns>
		[[nodiscard]] constexpr inline value_type& Bottom() &
		{
			return _left_top_right_bottom.template at<_bottom_index>();
		}

		[[nodiscard]] constexpr inline const value_type& Bottom() const&
		{
			return _left_top_right_bottom.template at<_bottom_index>();
		}

		/// <summary>
		/// <para> Calculates the width of this Rectangle based on the distance between its left and right points. </para>
		/// <para> This assumes that the Rect is well-formed. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `value_type_uq`. </para>
		/// </summary>
		/// <returns>The width of this Rectangle, based on `Right - Left`.</returns>
		template<typename Out_ = value_type_uq>
		[[nodiscard]] constexpr inline Out_ Width() const
		{
			return EmuMath::Helpers::rect_get_width<Out_>(*this);
		}

		/// <summary>
		/// <para> Calculates the height of this Rectangle based on the distance between its top and bottom points. </para>
		/// <para> This assumes that the Rect is well-formed. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `value_type_uq`. </para>
		/// </summary>
		/// <returns>The width of this Rectangle, based on `Bottom - Top`.</returns>
		template<typename Out_ = value_type_uq>
		[[nodiscard]] constexpr inline Out_ Height() const
		{
			return EmuMath::Helpers::rect_get_height<Out_>(*this);
		}

		/// <summary>
		/// <para> Calculates the size of this Rectangle in both axes and outputs the results as a 2D Vector. </para>
		/// <para> The width (X) will be stored in index 0; the height (Y) will be stored in index 1. </para>
		/// <para> This assumes that the Rect is well-formed. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `value_type_uq`. </para>
		/// </summary>
		/// <returns>The width and height of this Rectangle, based on `Right - Left` and `Bottom - Top` respectively.</returns>
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<2, OutT_> Size() const
		{
			return EmuMath::Helpers::rect_get_size<OutT_>(*this);
		}

		/// <summary>
		/// <para> Calculates the squared length of this Rectangle's diagonal. </para>
		/// <para> This assumes that the Rect is well-formed, and is based on the `Size` of this Rectangle. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `value_type_uq`. </para>
		/// </summary>
		/// <returns>The squared length of this Rectangle.</returns>
		template<typename Out_ = value_type_uq>
		[[nodiscard]] constexpr inline Out_ DiagonalSquaredLength() const
		{
			return EmuMath::Helpers::rect_get_diagonal_length_squared<Out_>(*this);
		}

		/// <summary>
		/// <para> Calculates the length of this Rectangle's diagonal. </para>
		/// <para> This assumes that the Rect is well-formed, and is based on the `Size` of this Rectangle. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `preferred_floating_point`. </para>
		/// <para> Calculation will aim to be constexpr-evaluable if possible, which may affect accuracy and/or performance. </para>
		/// </summary>
		/// <returns>The length of this Rectangle.</returns>
		template<typename Out_ = preferred_floating_point>
		[[nodiscard]] constexpr inline Out_ DiagonalLengthConstexpr() const
		{
			return EmuMath::Helpers::rect_get_diagonal_length_constexpr<Out_>(*this);
		}

		/// <summary>
		/// <para> Calculates the length of this Rectangle's diagonal. </para>
		/// <para> This assumes that the Rect is well-formed, and is based on the `Size` of this Rectangle. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `preferred_floating_point`. </para>
		/// </summary>
		/// <returns>The length of this Rectangle.</returns>
		template<typename Out_ = preferred_floating_point>
		[[nodiscard]] constexpr inline Out_ DiagonalLength() const
		{
			return EmuMath::Helpers::rect_get_diagonal_length<Out_>(*this);
		}

		/// <summary>
		/// <para> Calculates the central point of this Rectangle in the X-axis. </para>
		/// <para> This assumes that the Rect is well-formed, and is based on the `Width` of this Rectangle. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `preferred_floating_point`. </para>
		/// </summary>
		/// <returns>Central point of this Rectangle in the X-axis.</returns>
		template<typename Out_ = preferred_floating_point>
		[[nodiscard]] constexpr inline Out_ CentralX() const
		{
			return EmuMath::Helpers::rect_get_centre_x<Out_>(*this);
		}

		/// <summary>
		/// <para> Calculates the central point of this Rectangle in the Y-axis. </para>
		/// <para> This assumes that the Rect is well-formed, and is based on the `Height` of this Rectangle. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `preferred_floating_point`. </para>
		/// </summary>
		/// <returns>Central point of this Rectangle in the Y-axis.</returns>
		template<typename Out_ = preferred_floating_point>
		[[nodiscard]] constexpr inline Out_ CentralY() const
		{
			return EmuMath::Helpers::rect_get_centre_y<Out_>(*this);
		}

		/// <summary>
		/// <para> Calculates the central point of this Rectangle, and outputs the X- and Y-axes' points as indices 0 and 1 (respectively) of a 2D Vector. </para>
		/// <para> This assumes that the Rect is well-formed, and is based on the `Width` and `Height` of this Rectangle. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `preferred_floating_point`. </para>
		/// </summary>
		/// <returns>2D EmuMath Vector containing this Rect's central X and Y points in indices 0 and 1 respectively.</returns>
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::Vector<2, OutT_> Centre() const
		{
			return EmuMath::Helpers::rect_get_centre<OutT_>(*this);
		}
#pragma endregion

#pragma region VALIDITY_CHECKS
	public:
		/// <summary>
		/// <para> Checks if the current state of this Rect has a well-formed X axis. </para>
		/// <para> A well-formed X-axis will have a Left value less than or equal to its Right value. </para>
		/// </summary>
		/// <returns>True if this Rect's X-axis is well-formed; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool WellFormedX() const
		{
			return EmuMath::Helpers::rect_has_well_formed_x(*this);
		}

		/// <summary>
		/// <para> Checks if the current state of this Rect has a well-formed Y axis. </para>
		/// <para> A well-formed Y-axis will have a Top value less than or equal to its Bottom value. </para>
		/// </summary>
		/// <returns>True if this Rect's Y-axis is well-formed; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool WellFormedY() const
		{
			return EmuMath::Helpers::rect_has_well_formed_y(*this);
		}

		/// <summary>
		/// <para> Checks if the current state of this Rect is well-formed.</para>
		/// <para> A well-formed Rect will have a Left value less than or equal to its Right value, and a Top value less than or equal to its Bottom value. </para>
		/// </summary>
		/// <returns>True if this Rect's X- and Y-axes are both well-formed; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool WellFormed() const
		{
			return EmuMath::Helpers::rect_is_well_formed(*this);
		}
#pragma endregion

#pragma region MUTATIONS
	public:
		/// <summary>
		/// <para> Creates an adjusted form of this Rect which is centred on the provided points in the X- and Y-axes respectively. </para>
		/// <para> One should be wary of potential inaccuracies when outputting integral types. This issue can be avoided by outputting floating-point types. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `preferred_floating_point`. </para>
		/// </summary>
		/// <param name="x_">Point in the X-axis to centre the new Rect on.</param>
		/// <param name="y_">Point in the Y-axis to centre the new Rect on.</param>
		/// <returns>Copy of this Rect adjusted to be centred on the provided coordinates in respective axes.</returns>
		template<typename OutT_ = preferred_floating_point, typename X_, typename Y_>
		[[nodiscard]] constexpr inline Rect<OutT_> MakeCentred(X_&& x_, Y_&& y_) const
		{
			return EmuMath::Helpers::rect_make_centred<OutT_>(*this, std::forward<X_>(x_), std::forward<Y_>(y_));
		}

		/// <summary>
		/// <para> Creates an adjusted form of this Rect which is centred on the provided points in the X- and Y-axes respectively. </para>
		/// <para> One should be wary of potential inaccuracies when outputting integral types. This issue can be avoided by outputting floating-point types. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `preferred_floating_point`. </para>
		/// </summary>
		/// <param name="x_and_y_vector_">
		///		EmuMath Vector containing the points to centre the new Rect on in the X- and Y-axes in theoretical indices 0 and 1, respectively.
		/// </param>
		/// <returns>Copy of this Rect adjusted to be centred on the provided coordinates in respective axes.</returns>
		template<typename OutT_ = preferred_floating_point, EmuConcepts::EmuVector CentreVector_>
		[[nodiscard]] constexpr inline Rect<OutT_> MakeCentred(CentreVector_&& x_and_y_vector_) const
		{
			return EmuMath::Helpers::rect_make_centred<OutT_>(*this, std::forward<CentreVector_>(x_and_y_vector_));
		}

		/// <summary>
		/// <para> Creates an adjusted form of this Rect which is centred on the provided point in both the X- and Y-axes. </para>
		/// <para> One should be wary of potential inaccuracies when outputting integral types. This issue can be avoided by outputting floating-point types. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `preferred_floating_point`. </para>
		/// </summary>
		/// <param name="x_and_y_">Scalar point in both the X- and Y-axes to centre the new Rect on.</param>
		/// <returns>Copy of this Rect adjusted to be centred on the provided coordinate in both axes.</returns>
		template<typename OutT_ = preferred_floating_point, typename SharedPoint_>
		[[nodiscard]] constexpr inline auto MakeCentred(SharedPoint_&& x_and_y_) const
			-> std::enable_if_t<!EmuMath::TMP::is_emu_vector_v<typename EmuCore::TMP::remove_ref_cv<SharedPoint_>::type>, Rect<OutT_>>
		{
			return EmuMath::Helpers::rect_make_centred<OutT_>(std::forward<SharedPoint_>(x_and_y_));
		}
		
		/// <summary>
		/// <para>
		///		Creates a copy of this Rect scaled about its centre, 
		///		changing all boundaries to scale its size in respective axes whilst maintaining the same central point.
		/// </para>
		/// <para> This assumes that the Rect is well-formed. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `preferred_floating_point`. </para>
		/// </summary>
		/// <param name="scale_x_">Scale to apply to this Rect's width.</param>
		/// <param name="scale_y_">Scale to apply to this Rect's height.</param>
		/// <returns>This Rect scaled by the provided factors in respective axes, with the same central point.</returns>
		template<typename OutT_ = preferred_floating_point, typename X_, typename Y_>
		[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> Scale(X_&& scale_x_, Y_&& scale_y_) const
		{
			return EmuMath::Helpers::rect_scale<OutT_>(*this, std::forward<X_>(scale_x_), std::forward<Y_>(scale_y_));
		}

		/// <summary>
		/// <para>
		///		Creates a copy of this Rect scaled about its centre, 
		///		changing all boundaries to scale its size in respective axes whilst maintaining the same central point.
		/// </para>
		/// <para> This assumes that the Rect is well-formed. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `preferred_floating_point`. </para>
		/// </summary>
		/// <param name="scale_vector_2d_">EmuMath Vector of scales to apply to this Rect, with X and Y at theoretical indices 0 and 1 respectively.</param>
		/// <returns>This Rect scaled by the provided factors in respective axes, with the same central point.</returns>
		template<typename OutT_ = preferred_floating_point, EmuConcepts::EmuVector ScaleVector_>
		[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> Scale(ScaleVector_&& scale_vector_2d_) const
		{
			return EmuMath::Helpers::rect_scale<OutT_>(*this, std::forward<ScaleVector_>(scale_vector_2d_));
		}

		/// <summary>
		/// <para>
		///		Creates a copy of this Rect scaled about its centre, 
		///		changing all boundaries to scale its size in all axes whilst maintaining the same central point.
		/// </para>
		/// <para> This assumes that the Rect is well-formed. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `preferred_floating_point`. </para>
		/// </summary>
		/// <param name="scale_x_and_y_">Scale to apply to this Rect's width and height.</param>
		/// <returns>This Rect scaled by the provided factor in all axes, with the same central point.</returns>
		template<typename OutT_ = preferred_floating_point, typename ScaleScalar_>
		[[nodiscard]] constexpr inline auto Scale(ScaleScalar_&& scale_x_and_y_) const
			-> std::enable_if_t<!EmuMath::TMP::is_emu_vector_v<ScaleScalar_>, EmuMath::Rect<OutT_>>
		{
			return EmuMath::Helpers::rect_scale<OutT_>(*this, std::forward<ScaleScalar_>(scale_x_and_y_));
		}

		/// <summary>
		/// <para> Creates a copy of this Rect scaled about the specified anchor. </para>
		/// <para> XAnchorDirection_: 0: Centre of the X-axis; Negative: Left boundary of the X-axis; Positive non-0: Right boundary of the X-axis. </para>
		/// <para> YAnchorDirection_: 0: Centre of the Y-axis; Negative: Top boundary of the Y-axis; Positive non-0: Bottom boundary of the Y-axis. </para>
		/// <para> When anchored to a boundary, that boundary will not be modified and the opposite boundary will receive the full effect of the scale. </para>
		/// <para> When anchored to a central point, both of that axis's boundaries scaled by half the amount to maintain the same central point. </para>
		/// <para> This assumes that the Rect is well-formed. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `preferred_floating_point`. </para>
		/// </summary>
		/// <param name="scale_x_">Scale to apply to this Rect's width.</param>
		/// <param name="scale_y_">Scale to apply to this Rect's height.</param>
		/// <returns>This Rect scaled by the provided factor in all axes, with points of specified anchors maintained as the same value.</returns>
		template<signed int XAnchorDirection_, signed int YAnchorDirection_, typename OutT_ = preferred_floating_point, typename X_, typename Y_>
		[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> ScaleAnchored(X_&& scale_x_, Y_&& scale_y_) const
		{
			return EmuMath::Helpers::rect_scale_anchored<XAnchorDirection_, YAnchorDirection_, OutT_>
			(
				*this,
				std::forward<X_>(scale_x_),
				std::forward<Y_>(scale_y_)
			);
		}

		/// <summary>
		/// <para> Creates a copy of this Rect scaled about the specified anchor. </para>
		/// <para> XAnchorDirection_: 0: Centre of the X-axis; Negative: Left boundary of the X-axis; Positive non-0: Right boundary of the X-axis. </para>
		/// <para> YAnchorDirection_: 0: Centre of the Y-axis; Negative: Top boundary of the Y-axis; Positive non-0: Bottom boundary of the Y-axis. </para>
		/// <para> When anchored to a boundary, that boundary will not be modified and the opposite boundary will receive the full effect of the scale. </para>
		/// <para> When anchored to a central point, both of that axis's boundaries scaled by half the amount to maintain the same central point. </para>
		/// <para> This assumes that the Rect is well-formed. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `preferred_floating_point`. </para>
		/// </summary>
		/// <param name="rect_">EmuMath Rect to create a scaled form of.</param>
		/// <param name="scale_vector_2d_">EmuMath Vector of scales to apply to this Rect, with X and Y at theoretical indices 0 and 1 respectively.</param>
		/// <returns>This Rect scaled by the provided factor in respective axes, with points of specified anchors maintained as the same value.</returns>
		template<signed int XAnchorDirection_, signed int YAnchorDirection_, typename OutT_ = preferred_floating_point, EmuConcepts::EmuVector ScaleVector_>
		[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> ScaleAnchored(ScaleVector_&& scale_vector_2d_) const
		{
			return EmuMath::Helpers::rect_scale_anchored<XAnchorDirection_, YAnchorDirection_, OutT_>(*this, std::forward<ScaleVector_>(scale_vector_2d_));
		}

		/// <summary>
		/// <para> Creates a copy of this Rect scaled about the specified anchor. </para>
		/// <para> XAnchorDirection_: 0: Centre of the X-axis; Negative: Left boundary of the X-axis; Positive non-0: Right boundary of the X-axis. </para>
		/// <para> YAnchorDirection_: 0: Centre of the Y-axis; Negative: Top boundary of the Y-axis; Positive non-0: Bottom boundary of the Y-axis. </para>
		/// <para> When anchored to a boundary, that boundary will not be modified and the opposite boundary will receive the full effect of the scale. </para>
		/// <para> When anchored to a central point, both of that axis's boundaries scaled by half the amount to maintain the same central point. </para>
		/// <para> This assumes that the Rect is well-formed. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `preferred_floating_point`. </para>
		/// </summary>
		/// <param name="scale_x_and_y_">Scale to apply to this Rect's width and height.</param>
		/// <returns>This Rect scaled by the provided factor in all axes, with points of specified anchors maintained as the same value.</returns>
		template<signed int XAnchorDirection_, signed int YAnchorDirection_, typename OutT_ = preferred_floating_point, typename ScaleScalar_>
		[[nodiscard]] constexpr inline auto ScaleAnchored(ScaleScalar_&& scale_x_and_y_)
			-> std::enable_if_t<!EmuMath::TMP::is_emu_vector_v<ScaleScalar_>, EmuMath::Rect<OutT_>>
		{
			return EmuMath::Helpers::rect_scale_anchored<XAnchorDirection_, YAnchorDirection_, OutT_>(*this, std::forward<ScaleScalar_>(scale_x_and_y_));
		}

		/// <summary>
		/// <para> Creates a copy of this Rect moved by the specified amounts in respective axes. </para>
		/// <para> This effectively adds the `x_` translation to `Left` and `Right`, and adds `y_` to `Top` and `Bottom`. </para>
		/// </summary>
		/// <param name="x_">Amount to move this Rectangle by in the X-axis.</param>
		/// <param name="y_">Amount to move this Rectangle by in the Y-axis.</param>
		/// <returns>This Rect translated by the specified amounts in respective axes.</returns>
		template<typename OutT_ = preferred_floating_point, typename X_, typename Y_>
		[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> Translate(X_&& x_, Y_&& y_) const
		{
			return EmuMath::Helpers::rect_translate<OutT_>(*this, std::forward<X_>(x_), std::forward<Y_>(y_));
		}

		/// <summary>
		/// <para> Creates a copy of this Rect moved by the specified amounts in respective axes. </para>
		/// <para> This effectively adds the `x_` translation to `Left` and `Right`, and adds `y_` to `Top` and `Bottom`. </para>
		/// </summary>
		/// <param name="translation_vector_2d_">
		///		EmuMath Vector of translations to apply to this Rect, with X and Y at theoretical indices 0 and 1 respectively.
		/// </param>
		/// <returns>This Rect translated by the specified amounts in respective axes.</returns>
		template<typename OutT_ = preferred_floating_point, EmuConcepts::EmuVector TranslationVector_>
		[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> Translate(TranslationVector_&& translation_vector_2d_) const
		{
			return EmuMath::Helpers::rect_translate<OutT_>(*this, std::forward<TranslationVector_>(translation_vector_2d_));
		}

		/// <summary>
		/// <para> Creates a reflected copy of this Rect in the specified X- and Y-directions </para>
		/// <para> XDirection_: 0: No X-axis reflection; Positive: Reflect against Right boundary; Negative: Reflect against Left boundary. </para>
		/// <para> YDirection_: 0: No Y-axis reflection; Positive: Reflect against Bottom boundary; Negative: Reflect against Top boundary. </para>
		/// <para> This assumes that the Rect is well-formed. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `value_type_uq`. </para>
		/// </summary>
		/// <returns>This Rect reflected as specified by the passed template arguments.</returns>
		template<std::int32_t XDirection_, std::int32_t YDirection_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> Reflect() const
		{
			return EmuMath::Helpers::rect_reflect<XDirection_, YDirection_, OutT_>(*this);
		}

		/// <summary>
		/// <para> Creates a reflected copy of this Rect in the specified X- and Y-directions </para>
		/// <para> If `x_direction_` and `y_direction_` are known compile-time constants, it is recommended to pass them as template arguments instead. </para>
		/// <para> This assumes that the Rect is well-formed. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `value_type_uq`. </para>
		/// </summary>
		/// <param name="x_direction_">0: No X-axis reflection; Positive: Reflect against Right boundary; Negative: Reflect against Left boundary.</param>
		/// <param name="y_direction_">0: No Y-axis reflection; Positive: Reflect against Bottom boundary; Negative: Reflect against Top boundary.</param>
		/// <returns>This Rect reflected as specified by the passed arguments.</returns>
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> Reflect(signed int x_direction_, signed int y_direction_) const
		{
			return EmuMath::Helpers::rect_reflect<OutT_>(*this, x_direction_, y_direction_);
		}
#pragma endregion

#pragma region CONTAINMENT_AND_COLLISION_CHECKS
	public:
		/// <summary>
		/// <para> Determines if a given point is contained within this Rect based on its current Left, Top, Right, and Bottom boundaries </para>
		/// <para> This assumes that the Rect is well-formed. </para>
		/// <para> May customise whether the point is classed as outside if on the boundaries of the Rect via IgnoreEqual_. If omitted, this defaults to `true`. </para>
		/// </summary>
		/// <param name="x_">X coordinate to check for.</param>
		/// <param name="y_">Y coordinate to check for.</param>
		/// <returns>True if the provided X and Y coordinates are contained within this Rect's boundaries.</returns>
		template<bool IgnoreEqual_ = true, typename X_, typename Y_>
		[[nodiscard]] constexpr inline bool ContainsPoint(X_&& x_, Y_&& y_) const
		{
			return EmuMath::Helpers::rect_contains_point<IgnoreEqual_>(*this, std::forward<X_>(x_), std::forward<Y_>(y_));
		}

		/// <summary>
		/// <para> Determines if a given point is contained within this Rect based on its current Left, Top, Right, and Bottom boundaries </para>
		/// <para> This assumes that the Rect is well-formed. </para>
		/// <para> May customise whether the point is classed as outside if on the boundaries of the Rect via IgnoreEqual_. If omitted, this defaults to `true`. </para>
		/// </summary>
		/// <param name="point_vec_2d_">EmuMath Vector with coordinates to search for in the X- and Y-axes in theoretical indices 0 and 1 respectively..</param>
		/// <returns>True if the provided coordinates are contained within this Rect's boundaries.</returns>
		template<bool IgnoreEqual_ = true, EmuConcepts::EmuVector PointVector_>
		[[nodiscard]] constexpr inline bool ContainsPoint(PointVector_&& point_vector_2d_) const
		{
			return EmuMath::Helpers::rect_contains_point<IgnoreEqual_>(*this, std::forward<PointVector_>(point_vector_2d_));
		}

		/// <summary>
		/// <para> 
		///		Checks if this Rect and the passed Rect are colliding in an axis-aligned context 
		///		(i.e. they are considered not rotated or warped in any way).
		/// </para>
		/// <para> This assumes that both Rects are well-formed. </para>
		/// <para> May customise whether a point is classed as outside if on the boundaries of a Rect via IgnoreEqual_. If omitted, this defaults to `true`. </para>
		/// </summary>
		/// <param name="rect_b_">Second Rect involved in the collision check.</param>
		/// <returns>If the this Rect and the passed Rect are colliding, `true`; otherwise `false`.</returns>
		template<bool IgnoreEqual_ = true, EmuConcepts::EmuRect RectB_>
		[[nodiscard]] constexpr inline bool CollidingAxisAligned(RectB_&& rect_b_) const
		{
			return EmuMath::Helpers::rect_colliding_axis_aligned<IgnoreEqual_>(*this, std::forward<RectB_>(rect_b_));
		}
#pragma endregion

#pragma region CONVERSIONS
	public:
		template<std::size_t Left_, std::size_t Top_, std::size_t Right_, std::size_t Bottom_, typename OutT_ = value_type_uq>
		[[nodiscard]] static constexpr inline bool can_convert_to_vector()
		{
			return
			(
				EmuMath::Helpers::rect_valid_index_args_for_vector_conversion<Left_, Top_, Right_, Bottom_>() &&
				std::is_constructible_v<EmuMath::Vector<4, OutT_>, value_type&, value_type&, value_type&, value_type&>
			);
		}

		template<std::size_t Left_, std::size_t Top_, std::size_t Right_, std::size_t Bottom_, typename OutT_ = value_type_uq>
		[[nodiscard]] static constexpr inline bool can_const_convert_to_vector()
		{
			return
			(
				EmuMath::Helpers::rect_valid_index_args_for_vector_conversion<Left_, Top_, Right_, Bottom_>() &&
				std::is_constructible_v<EmuMath::Vector<4, OutT_>, const value_type&, const value_type&, const value_type&, const value_type&>
			);
		}

		/// <summary>
		/// <para> Casts this Rect to an EmuMath Rect of the specified type. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `value_type_uq`. </para>
		/// </summary>
		/// <returns>Converted form of this Rect.</returns>
		template<typename OutT_>
		[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> Cast()
		{
			return EmuMath::Helpers::rect_cast<OutT_>(*this);
		}

		template<typename OutT_>
		[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> Cast() const
		{
			return EmuMath::Helpers::rect_cast<OutT_>(*this);
		}

		/// <summary>
		/// <para> Casts this Rect to an EmuMath Rect of the specified type. </para>
		/// <para> Functionally identical to `Cast`, and is present for `static_cast` syntactic sugar. </para>
		/// </summary>
		/// <returns>Converted form of this Rect.</returns>
		template<typename OutT_>
		explicit constexpr inline operator EmuMath::Rect<OutT_>()
		{
			return EmuMath::Helpers::rect_cast<OutT_>(*this);
		}

		template<typename OutT_>
		explicit constexpr inline operator EmuMath::Rect<OutT_>() const
		{
			return EmuMath::Helpers::rect_cast<OutT_>(*this);
		}

		/// <summary>
		/// <para> Converts this Rect to a 4D Vector of its 4 boundaries as specified. </para>
		/// <para>
		///		Input indices indicate which Vector index to assign the named boundary to. 
		///		These may only be non-repeating values in the inclusive range 0:3.
		/// </para>
		/// <para> Input indices may be omitted, in which case they will default to 0, 1, 2, 3. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `value_type_uq`. </para>
		/// </summary>
		/// <returns>4D EmuMath Vector containing the 4 boundaries of this Rect in specified indices.</returns>
		template<std::size_t LeftIndex_, std::size_t TopIndex_, std::size_t RightIndex_, std::size_t BottomIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline auto AsVector()
			-> std::enable_if_t
			<
				EmuMath::Helpers::rect_valid_index_args_for_vector_conversion<LeftIndex_, TopIndex_, RightIndex_, BottomIndex_>(),
				EmuMath::Vector<4, OutT_>
			>
		{
			return EmuMath::Helpers::rect_as_vector<LeftIndex_, TopIndex_, RightIndex_, BottomIndex_, OutT_>(*this);
		}

		template<std::size_t LeftIndex_, std::size_t TopIndex_, std::size_t RightIndex_, std::size_t BottomIndex_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline auto AsVector() const
			-> std::enable_if_t
			<
				EmuMath::Helpers::rect_valid_index_args_for_vector_conversion<LeftIndex_, TopIndex_, RightIndex_, BottomIndex_>(),
				EmuMath::Vector<4, OutT_>
			>
		{
			return EmuMath::Helpers::rect_as_vector<LeftIndex_, TopIndex_, RightIndex_, BottomIndex_, OutT_>(*this);
		}

		/// <summary>
		/// <para> Converts this Rect to a 4D Vector of its Left, Top, Right, and Bottom boundaries at indices 0, 1, 2, and 3 respectively. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `value_type_uq`. </para>
		/// </summary>
		/// <returns>4D EmuMath Vector containing the 4 Left, Top, Right, and Bottom boundaries of this Rect at indices 0, 1, 2, and 3 respectively..</returns>
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<4, OutT_> AsVector()
		{
			return EmuMath::Helpers::rect_as_vector<OutT_>(*this);
		}

		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<4, OutT_> AsVector() const
		{
			return EmuMath::Helpers::rect_as_vector<OutT_>(*this);
		}

		/// <summary>
		/// <para> Converts this Rect to a 4D Vector of its Left, Top, Right, and Bottom boundaries at indices 0, 1, 2, and 3 respectively. </para>
		/// <para> Functionally identical to `AsVector` (without index arguments), and is present for `static_cast` syntactic sugar. </para>
		/// </summary>
		/// <returns>4D EmuMath Vector containing the 4 Left, Top, Right, and Bottom boundaries of this Rect at indices 0, 1, 2, and 3 respectively..</returns>
		template<typename OutT_>
		[[nodiscard]] explicit constexpr inline operator EmuMath::Vector<4, OutT_>()
		{
			return EmuMath::Helpers::rect_as_vector<OutT_>(*this);
		}

		template<typename OutT_>
		[[nodiscard]] explicit constexpr inline operator EmuMath::Vector<4, OutT_>() const
		{
			return EmuMath::Helpers::rect_as_vector<OutT_>(*this);
		}
#pragma endregion

	private:
		_underlying_vector _left_top_right_bottom;
	};
}

#endif
