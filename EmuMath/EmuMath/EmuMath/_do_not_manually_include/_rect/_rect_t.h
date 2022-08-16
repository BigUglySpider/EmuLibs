#ifndef EMU_MATH_RECT_T_H_INC_
#define EMU_MATH_RECT_T_H_INC_ 1

#include "../../Vector.h"

namespace EmuMath
{
	/// <summary>
	/// <para> Type used to store and retrieve basic information regarding a rectangle, with the origin point (0, 0) at a theoretical top-left. </para>
	/// </summary>
	template<typename T_>
	struct Rect
	{
	private:
		using _underlying_vector = EmuMath::Vector<4, T_>;
		static constexpr std::size_t _left_index = 0;
		static constexpr std::size_t _top_index = 1;
		static constexpr std::size_t _right_index = 2;
		static constexpr std::size_t _bottom_index = 3;

	public:
		using this_type = Rect<T_>;
		using stored_type = typename _underlying_vector::stored_type;
		using value_type = typename _underlying_vector::value_type;
		using value_type_uq = typename _underlying_vector::value_type_uq;
		using preferred_floating_point = typename _underlying_vector::preferred_floating_point;

		[[nodiscard]] static constexpr inline value_type_uq get_implied_zero()
		{
			return _underlying_vector::get_implied_zero();
		}

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

#pragma region CONSTRUCTORS
	public:
		constexpr inline Rect() : _left_top_right_bottom()
		{
		}

		constexpr inline Rect(const Rect& to_copy_) :
			_left_top_right_bottom(to_copy_._left_top_right_bottom)
		{
		}

		constexpr inline Rect(Rect&& to_move_) noexcept : 
			_left_top_right_bottom(std::move(to_move_._left_top_right_bottom))
		{
		}

		/// <summary>
		/// <para> Creates a Rect as a square of the specified size, with its top-left corner at point (0, 0). </para>
		/// </summary>
		/// <param name="size_">Size of the square to create the Rect as.</param>
		template<typename Size_>
		constexpr inline Rect(Size_&& size_) :
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
		constexpr inline Rect(const EmuMath::Rect<ToCopyT_>& to_copy_) :
			_left_top_right_bottom(_make_data(to_copy_.Left(), to_copy_.Top(), to_copy_.Right(), to_copy_.Bottom()))
		{
		}

		/// <summary>
		/// <para> Converts the input Rect into the newly constructed type of Rect. </para>
		/// </summary>
		/// <param name="to_copy_">Rect of a different type to copy/convert.</param>
		template<typename ToCopyT_, typename = std::enable_if_t<!std::is_same_v<T_, ToCopyT_>>>
		constexpr inline Rect(EmuMath::Rect<ToCopyT_>& to_copy_) :
			_left_top_right_bottom(_make_data(to_copy_.Left(), to_copy_.Top(), to_copy_.Right(), to_copy_.Bottom()))
		{
		}
			
		/// <summary>
		/// <para> Moves and converts the input Rect into the newly constructed type of Rect. </para>
		/// </summary>
		/// <param name="to_move_">Rect of a different type to move/convert.</param>
		template<typename ToCopyT_, typename = std::enable_if_t<!std::is_same_v<T_, ToCopyT_>>>
		constexpr inline Rect(EmuMath::Rect<ToCopyT_>&& to_move_) :
			_left_top_right_bottom(_make_data(std::move(to_move_.Left()), std::move(to_move_.Top()), std::move(to_move_.Right()), std::move(to_move_.Bottom())))
		{
		}
#pragma endregion

#pragma region ASSIGNMENT_OPERATORS
	public:
		constexpr inline this_type& operator=(const Rect<T_>& to_copy_)
		{
			_left_top_right_bottom = to_copy_._left_top_right_bottom;
			return *this;
		}

		constexpr inline this_type& operator=(Rect<T_>&& to_move_) noexcept
		{
			_left_top_right_bottom = std::move(to_move_._left_top_right_bottom);
			return *this;
		}
#pragma endregion

#pragma region CONST_ARITHMETIC_OPERATORS
	public:
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> operator*(const preferred_floating_point& rhs_scale_) const
		{
			return Scale<OutT_>(rhs_scale_, rhs_scale_);
		}

		template<typename OutT_ = preferred_floating_point, std::size_t VecSize_, typename VecT_>
		[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> operator*(const EmuMath::Vector<VecSize_, VecT_>& scale_vector_2d_) const
		{
			return Scale<OutT_>(scale_vector_2d_.template AtTheoretical<0>(), scale_vector_2d_.template AtTheoretical<1>());
		}
#pragma endregion

#pragma region ARITHMETIC_ASSIGN_OPERATORS
	public:
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline this_type& operator*=(const preferred_floating_point& rhs_scale_)
		{
			return this->operator=(Scale<OutT_>(rhs_scale_, rhs_scale_));
		}

		template<typename OutT_ = preferred_floating_point, std::size_t VecSize_, typename VecT_>
		[[nodiscard]] constexpr inline this_type& operator*=(const EmuMath::Vector<VecSize_, VecT_>& scale_vector_2d_)
		{
			return this->operator=(Scale<OutT_>(scale_vector_2d_.template AtTheoretical<0>(), scale_vector_2d_.template AtTheoretical<1>()));
		}
#pragma endregion

#pragma region ACCESSORS
	private:
		template<std::size_t Index_, std::size_t Left_, std::size_t Top_, std::size_t Right_, std::size_t Bottom_>
		[[nodiscard]] constexpr inline decltype(auto) _get_item_for_vector()
		{
			if constexpr (Index_ == Left_)
			{
				return Left();
			}
			else if constexpr (Index_ == Top_)
			{
				return Top();
			}
			else if constexpr (Index_ == Right_)
			{
				return Right();
			}
			else if constexpr (Index_ == Bottom_)
			{
				return Bottom();
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Left_>(),
					"Failed to shuffle an EmuMath Rect into a 4D EmuMath Vector: At least one of the provided directional indices is invalid."
				);
			}
		}

		template<std::size_t Left_, std::size_t Top_, std::size_t Right_, std::size_t Bottom_>
		[[nodiscard]] static constexpr inline bool _valid_convert_to_vector_indices()
		{
			return
			(
				(Left_ != 0 && Top_ != 0 && Right_ != 0 && Bottom_ != 0) &&
				(Left_ >= 0 && Left_ <= 3 && Top_ >= 0 && Top_ <= 3 && Right_ >= 0 && Right_ <= 3 && Bottom_ >= 0 && Bottom_ <= 3)
			);
		}

	public:
		template<std::size_t Left_, std::size_t Top_, std::size_t Right_, std::size_t Bottom_, typename OutT_ = value_type_uq>
		[[nodiscard]] static constexpr inline bool can_convert_to_vector()
		{
			return
			(
				_valid_convert_to_vector_indices<Left_, Top_, Right_, Bottom_>() &&
				std::is_constructible_v<EmuMath::Vector<4, OutT_>, value_type&, value_type&, value_type&, value_type&>
			);
		}

		template<std::size_t Left_, std::size_t Top_, std::size_t Right_, std::size_t Bottom_, typename OutT_ = value_type_uq>
		[[nodiscard]] static constexpr inline bool can_const_convert_to_vector()
		{
			return
			(
				_valid_convert_to_vector_indices<Left_, Top_, Right_, Bottom_>() &&
				std::is_constructible_v<EmuMath::Vector<4, OutT_>, const value_type&, const value_type&, const value_type&, const value_type&>
			);
		}

		/// <summary>
		/// <para> Retrieves a reference to the value indicating the X coordinate of corners on the left of this Rectangle. </para>
		/// </summary>
		/// <returns>Reference to the X coordinate of left corners in this Rectangle.</returns>
		[[nodiscard]] constexpr inline value_type& Left()
		{
			return _left_top_right_bottom.template at<_left_index>();
		}

		[[nodiscard]] constexpr inline const value_type& Left() const
		{
			return _left_top_right_bottom.template at<_left_index>();
		}

		/// <summary>
		/// <para> Retrieves a reference to the value indicating the X coordinate of corners on the right of this Rectangle. </para>
		/// </summary>
		/// <returns>Reference to the X coordinate of right corners in this Rectangle.</returns>
		[[nodiscard]] constexpr inline value_type& Right()
		{
			return _left_top_right_bottom.template at<_right_index>();
		}

		[[nodiscard]] constexpr inline const value_type& Right() const
		{
			return _left_top_right_bottom.template at<_right_index>();
		}

		/// <summary>
		/// <para> Retrieves a reference to the value indicating the Y coordinate of corners on the top of this Rectangle. </para>
		/// </summary>
		/// <returns>Reference to the Y coordinate of top corners in this Rectangle.</returns>
		[[nodiscard]] constexpr inline value_type& Top()
		{
			return _left_top_right_bottom.template at<_top_index>();
		}

		[[nodiscard]] constexpr inline const value_type& Top() const
		{
			return _left_top_right_bottom.template at<_top_index>();
		}

		/// <summary>
		/// <para> Retrieves a reference to the value indicating the Y coordinate of corners on the bottom of this Rectangle. </para>
		/// </summary>
		/// <returns>Reference to the Y coordinate of bottom corners in this Rectangle.</returns>
		[[nodiscard]] constexpr inline value_type& Bottom()
		{
			return _left_top_right_bottom.template at<_bottom_index>();
		}

		[[nodiscard]] constexpr inline const value_type& Bottom() const
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
			return static_cast<Out_>(EmuCore::do_subtract<value_type_uq, value_type_uq>()(Right(), Left()));
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
			return static_cast<Out_>(EmuCore::do_subtract<value_type_uq, value_type_uq>()(Bottom(), Top()));
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
			return EmuMath::Vector<2, OutT_>(Width(), Height());
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
			return EmuMath::Helpers::vector_square_magnitude<Out_>(Size<Out_>());
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
			return EmuMath::Helpers::vector_magnitude_constexpr<Out_>(Size<Out_>());
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
			return EmuMath::Helpers::vector_magnitude<Out_>(Size<Out_>());
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
			return EmuCore::do_add<Out_, Out_>()
			(
				static_cast<Out_>(Left()),
				EmuCore::do_divide<Out_, Out_>()(Width<Out_>(), Out_(2))
			);
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
			return EmuCore::do_add<Out_, Out_>()
			(
				static_cast<Out_>(Top()),
				EmuCore::do_divide<Out_, Out_>()(Height<Out_>(), Out_(2))
			);
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
			return EmuMath::Vector<2, OutT_>(CentralX<OutT_>(), CentralY<OutT_>());
		}

		/// <summary>
		/// <para> Outputs a 4D Vector containing this Rect's Left, Top, Right, and Bottom values in indices 0, 1, 2, and 3 respectively. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `value_type_uq`. </para>
		/// <para> This function supports output of references. </para>
		/// </summary>
		/// <returns>4D EmuMath Vector containing this Rect's Left, Top, Right, and Bottom values in indices 0, 1, 2, and 3 respectively.</returns>
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<4, OutT_> AsVector()
		{
			return EmuMath::Vector<4, OutT_>(Left(), Top(), Right(), Bottom());
		}

		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline EmuMath::Vector<4, OutT_> AsVector() const
		{
			return EmuMath::Vector<4, OutT_>(Left(), Top(), Right(), Bottom());
		}

		/// <summary>
		/// <para> Outputs a 4D Vector containing this Rect's Left, Top, Right, and Bottom values in the respective specified indices. </para>
		/// <para> The valid inclusive index range is 0:3, and the same index may not be repeated. Specified indices relate to the output Vector. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `value_type_uq`. </para>
		/// <para> This function supports output of references. </para>
		/// </summary>
		/// <returns>4D EmuMath Vector containing this Rect's Left, Top, Right, and Bottom values in the respective specified indices..</returns>
		template<std::size_t Left_, std::size_t Top_, std::size_t Right_, std::size_t Bottom_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline auto AsVector()
			-> std::enable_if_t<can_convert_to_vector<Left_, Top_, Right_, Bottom_, OutT_>(), EmuMath::Vector<4, OutT_>>
		{
			return EmuMath::Vector<4, OutT_>
			(
				_get_item_for_vector<0, Left_, Top_, Right_, Bottom_>(),
				_get_item_for_vector<1, Left_, Top_, Right_, Bottom_>(),
				_get_item_for_vector<2, Left_, Top_, Right_, Bottom_>(),
				_get_item_for_vector<3, Left_, Top_, Right_, Bottom_>()
			);
		}

		template<std::size_t Left_, std::size_t Top_, std::size_t Right_, std::size_t Bottom_, typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline auto AsVector() const
			-> std::enable_if_t<can_const_convert_to_vector<Left_, Top_, Right_, Bottom_, OutT_>(), EmuMath::Vector<4, OutT_>>
		{
			return EmuMath::Vector<4, OutT_>
			(
				_get_item_for_vector<0, Left_, Top_, Right_, Bottom_>(),
				_get_item_for_vector<1, Left_, Top_, Right_, Bottom_>(),
				_get_item_for_vector<2, Left_, Top_, Right_, Bottom_>(),
				_get_item_for_vector<3, Left_, Top_, Right_, Bottom_>()
			);
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
			return EmuCore::do_cmp_less_equal<value_type_uq, value_type_uq>()(Left(), Right());
		}

		/// <summary>
		/// <para> Checks if the current state of this Rect has a well-formed Y axis. </para>
		/// <para> A well-formed Y-axis will have a Top value less than or equal to its Bottom value. </para>
		/// </summary>
		/// <returns>True if this Rect's Y-axis is well-formed; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool WellFormedY() const
		{
			return EmuCore::do_cmp_less_equal<value_type_uq, value_type_uq>()(Top(), Bottom());
		}

		/// <summary>
		/// <para> Checks if the current state of this Rect is well-formed.</para>
		/// <para> A well-formed Rect will have a Left value less than or equal to its Right value, and a Top value less than or equal to its Bottom value. </para>
		/// </summary>
		/// <returns>True if this Rect's X- and Y-axes are both well-formed; otherwise false.</returns>
		[[nodiscard]] constexpr inline bool WellFormed() const
		{
			return WellFormedX() && WellFormedY();
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
			OutT_ width_div_2 = EmuCore::do_divide<OutT_, OutT_>()(Width<OutT_>(), OutT_(2));
			OutT_ height_div_2 = EmuCore::do_divide<OutT_, OutT_>()(Height<OutT_>(), OutT_(2));
			OutT_ x = static_cast<OutT_>(std::forward<X_>(x_));
			OutT_ y = static_cast<OutT_>(std::forward<Y_>(y_));
			return Rect<OutT_>
			(
				EmuCore::do_subtract<OutT_, OutT_>()(x, width_div_2),
				EmuCore::do_subtract<OutT_, OutT_>()(y, height_div_2),
				EmuCore::do_add<OutT_, OutT_>()(x, width_div_2),
				EmuCore::do_add<OutT_, OutT_>()(y, height_div_2)
			);
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
		template<typename OutT_ = preferred_floating_point, std::size_t VecSize_, typename VecT_>
		[[nodiscard]] constexpr inline Rect<OutT_> MakeCentred(const EmuMath::Vector<VecSize_, VecT_>& x_and_y_vector_) const
		{
			return MakeCentred(x_and_y_vector_.template AtTheoretical<0>(), x_and_y_vector_.template AtTheoretical<1>());
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
			OutT_ width_div_2 = EmuCore::do_divide<OutT_, OutT_>()(Width<OutT_>(), OutT_(2));
			OutT_ height_div_2 = EmuCore::do_divide<OutT_, OutT_>()(Height<OutT_>(), OutT_(2));
			OutT_ x_and_y = static_cast<OutT_>(std::forward<SharedPoint_>(x_and_y_));
			return Rect<OutT_>
			(
				EmuCore::do_subtract<OutT_, OutT_>()(x_and_y, width_div_2),
				EmuCore::do_subtract<OutT_, OutT_>()(x_and_y, height_div_2),
				EmuCore::do_add<OutT_, OutT_>()(x_and_y, width_div_2),
				EmuCore::do_add<OutT_, OutT_>()(x_and_y, height_div_2)
			);
		}
#pragma endregion

#pragma region CONTAINS_CHECKS
	public:
		/// <summary>
		/// <para> Determines if a given point is contained within this Rect based on its current Left, Top, Right, and Bottom boundaries </para>
		/// <para> This assumes that the Rect is well-formed. </para>
		/// </summary>
		/// <param name="x_">X coordinate to check for.</param>
		/// <param name="y_">Y coordinate to check for.</param>
		/// <returns>True if the provided X and Y coordinates are contained within this Rect's boundaries.</returns>
		template<typename X_, typename Y_>
		[[nodiscard]] constexpr inline bool ContainsPoint(X_&& x_, Y_&& y_) const
		{
			using cmp_less_equal = EmuCore::do_cmp_less_equal<value_type_uq, value_type_uq>;
			using cmp_greater_equal = EmuCore::do_cmp_greater_equal<value_type_uq, value_type_uq>;
			value_type_uq x = static_cast<value_type_uq>(std::forward<X_>(x_));
			value_type_uq y = static_cast<value_type_uq>(std::forward<Y_>(y_));
			return
			(
				(cmp_less_equal()(Top(), y) && cmp_greater_equal()(Bottom(), y)) &&
				(cmp_less_equal()(Left(), x) && cmp_greater_equal()(Right(), x))
			);
		}

		/// <summary>
		/// <para> Determines if a given point is contained within this Rect based on its current Left, Top, Right, and Bottom boundaries </para>
		/// <para> This assumes that the Rect is well-formed. </para>
		/// </summary>
		/// <param name="point_vec_2d_">EmuMath Vector with coordinates to search for in the X- and Y-axes in theoretical indices 0 and 1 respectively..</param>
		/// <returns>True if the provided coordinates are contained within this Rect's boundaries.</returns>
		template<std::size_t VecSize_, typename VecT_>
		[[nodiscard]] constexpr inline bool ContainsPoint(const EmuMath::Vector<VecSize_, VecT_>& point_vec_2d_) const
		{
			return ContainsPoint(point_vec_2d_.template AtTheoretical<0>(), point_vec_2d_.template AtTheoretical<1>());
		}
#pragma endregion

#pragma region CONST_ARITHMETIC_FUNCS
	private:
		template<std::int32_t Direction_>
		[[nodiscard]] constexpr inline decltype(auto) _get_reflected_left() const
		{
			if constexpr (Direction_ == 0)
			{
				return Left();
			}
			else if constexpr (Direction_ < 0)
			{
				return EmuCore::do_subtract<value_type_uq, value_type_uq>()(Left(), Width<value_type_uq>());
			}
			else
			{
				return Right();
			}
		}

		template<std::int32_t Direction_>
		[[nodiscard]] constexpr inline decltype(auto) _get_reflected_right() const
		{
			if constexpr (Direction_ == 0)
			{
				return Right();
			}
			else if constexpr (Direction_ < 0)
			{
				return Left();
			}
			else
			{
				return EmuCore::do_add<value_type_uq, value_type_uq>()(Right(), Width<value_type_uq>());
			}
		}

		template<std::int32_t Direction_>
		[[nodiscard]] constexpr inline decltype(auto) _get_reflected_top() const
		{
			if constexpr (Direction_ == 0)
			{
				return Top();
			}
			else if constexpr (Direction_ < 0)
			{
				return EmuCore::do_subtract<value_type_uq, value_type_uq>()(Top(), Height<value_type_uq>());
			}
			else
			{
				return Bottom();
			}
		}

		template<std::int32_t Direction_>
		[[nodiscard]] constexpr inline decltype(auto) _get_reflected_bottom() const
		{
			if constexpr (Direction_ == 0)
			{
				return Bottom();
			}
			else if constexpr (Direction_ < 0)
			{
				return Top();
			}
			else
			{
				return EmuCore::do_add<value_type_uq, value_type_uq>()(Bottom(), Height<value_type_uq>());
			}
		}

		[[nodiscard]] constexpr inline std::pair<value_type_uq, value_type_uq> _get_reflected_x(std::int32_t direction_) const
		{
			using add_func = EmuCore::do_add<value_type_uq, value_type_uq>;
			using sub_func = EmuCore::do_subtract<value_type_uq, value_type_uq>;

			if (direction_ == 0)
			{
				return std::pair<value_type_uq, value_type_uq>(Left(), Right());
			}
			else if (direction_ < 0)
			{
				return std::pair<value_type_uq, value_type_uq>(sub_func()(Left(), Width<value_type_uq>()), Left());
			}
			else
			{
				return std::pair<value_type_uq, value_type_uq>(Right(), add_func()(Right(), Width<value_type_uq>()));
			}
		}

		[[nodiscard]] constexpr inline std::pair<value_type_uq, value_type_uq> _get_reflected_y(std::int32_t direction_) const
		{
			using add_func = EmuCore::do_add<value_type_uq, value_type_uq>;
			using sub_func = EmuCore::do_subtract<value_type_uq, value_type_uq>;

			if (direction_ == 0)
			{
				return std::pair<value_type_uq, value_type_uq>(Top(), Bottom());
			}
			else if (direction_ < 0)
			{
				return std::pair<value_type_uq, value_type_uq>(sub_func()(Top(), Height<value_type_uq>()), Top());
			}
			else
			{
				return std::pair<value_type_uq, value_type_uq>(Bottom(), add_func()(Bottom(), Height<value_type_uq>()));
			}
		}

	public:
		/// <summary>
		/// <para>
		///		Creates a copy of this Rect scaled about its centre, 
		///		changing all boundaries to scale its size in respective axes whilst maintaining the same central point.
		/// </para>
		/// <para> This assumes that the Rect is well-formed. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `value_type_uq`. </para>
		/// </summary>
		/// <param name="scale_x_">Scale to apply to this Rect's width.</param>
		/// <param name="scale_y_">Scale to apply to this Rect's height.</param>
		/// <returns>This Rect scaled by the provided factors in respective axes, with the same central point.</returns>
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> Scale(const preferred_floating_point& scale_x_, const preferred_floating_point& scale_y_) const
		{
			using add_func = EmuCore::do_add<preferred_floating_point, preferred_floating_point>;
			using sub_func = EmuCore::do_subtract<preferred_floating_point, preferred_floating_point>;
			using mul_func = EmuCore::do_multiply<preferred_floating_point, preferred_floating_point>;
			using div_func = EmuCore::do_divide<preferred_floating_point, preferred_floating_point>;

			preferred_floating_point width = Width<preferred_floating_point>();
			preferred_floating_point height = Height<preferred_floating_point>();

			preferred_floating_point centre_y = add_func()(Top(), div_func()(height, preferred_floating_point(2)));
			preferred_floating_point centre_x = add_func()(Left(), div_func()(width, preferred_floating_point(2)));

			// Set width and height to half of new width and height; these are subtracted/added from centres to form begin/end boundaries
			width = div_func()(mul_func()(width, scale_x_), preferred_floating_point(2));
			height = div_func()(mul_func()(height, scale_y_), preferred_floating_point(2));

			return EmuMath::Rect<OutT_>
			(
				sub_func()(centre_x, width),
				sub_func()(centre_y, height),
				add_func()(centre_x, width),
				add_func()(centre_y, height)
			);
		}

		/// <summary>
		/// <para>
		///		Creates a copy of this Rect scaled about its centre, 
		///		changing all boundaries to scale its size in all axes whilst maintaining the same central point.
		/// </para>
		/// <para> This assumes that the Rect is well-formed. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `value_type_uq`. </para>
		/// </summary>
		/// <param name="shared_scale_">Scale to apply to this Rect's width and height.</param>
		/// <returns>This Rect scaled by the provided factor in all axes, with the same central point.</returns>
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> Scale(const preferred_floating_point& shared_scale_) const
		{
			return Scale(shared_scale_, shared_scale_);
		}

		/// <summary>
		/// <para>
		///		Creates a copy of this Rect scaled about its centre, 
		///		changing all boundaries to scale its size in respective axes whilst maintaining the same central point.
		/// </para>
		/// <para> This assumes that the Rect is well-formed. </para>
		/// <para> The output type may be customised, but if omitted will default to this Rect's `value_type_uq`. </para>
		/// </summary>
		/// <param name="scale_vector_2d_">EmuMath Vector of scales to apply to this Rect, with X and Y at theoretical indices 0 and 1 respectively.</param>
		/// <returns>This Rect scaled by the provided factors in respective axes, with the same central point.</returns>
		template<typename OutT_ = preferred_floating_point, std::size_t VecSize_, typename VecT_>
		[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> Scale(const EmuMath::Vector<VecSize_, VecT_>& scale_vector_2d_) const
		{
			return Scale(scale_vector_2d_.template AtTheoretical<0>(), scale_vector_2d_.template AtTheoretical<1>());
		}

		/// <summary>
		/// <para> Creates a copy of this Rect moved by the specified amounts in respective axes. </para>
		/// <para> This effectively adds the `x_` translation to `Left` and `Right`, and adds `y_` to `Top` and `Bottom`. </para>
		/// </summary>
		/// <param name="x_">Amount to move this Rectangle by in the X-axis.</param>
		/// <param name="y_">Amount to move this Rectangle by in the Y-axis.</param>
		/// <returns>This Rect translated by the specified amounts in respective axes.</returns>
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> Translate(const preferred_floating_point& x_, const preferred_floating_point& y_) const
		{
			using add_func = EmuCore::do_add<preferred_floating_point, preferred_floating_point>;
			return EmuMath::Rect<OutT_>
			(
				add_func()(Left(), x_),
				add_func()(Top(), y_),
				add_func()(Right(), x_),
				add_func()(Bottom(), y_)
			);
		}

		/// <summary>
		/// <para> Creates a copy of this Rect moved by the specified amounts in respective axes. </para>
		/// <para> This effectively adds the `x_` translation to `Left` and `Right`, and adds `y_` to `Top` and `Bottom`. </para>
		/// </summary>
		/// <param name="translation_vector_2d_">
		///		EmuMath Vector of translations to apply to this Rect, with X and Y at theoretical indices 0 and 1 respectively.
		/// </param>
		/// <returns>This Rect translated by the specified amounts in respective axes.</returns>
		template<typename OutT_ = preferred_floating_point, std::size_t VecSize_, typename VecT_>
		[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> Translate(const EmuMath::Vector<VecSize_, VecT_>& translation_vector_2d_) const
		{
			return Translate(translation_vector_2d_.template AtTheoretical<0>(), translation_vector_2d_.template AtTheoretical<1>());
		}

		/// <summary>
		/// <para> Creates a reflected copy of this Rect in the specified X- and Y-directions </para>
		/// <para> XDirection_: 0: No X-axis reflection; Positive: Reflect against Right boundary; Negative: Reflect against Left boundary. </para>
		/// <para> YDirection_: 0: No Y-axis reflection; Positive: Reflect against Bottom boundary; Negative: Reflect against Top boundary. </para>
		/// </summary>
		/// <returns>This Rect reflected as specified by the passed template arguments.</returns>
		template<std::int32_t XDirection_, std::int32_t YDirection_, typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> Reflect() const
		{
			return EmuMath::Rect<OutT_>
			(
				_get_reflected_left<XDirection_>(),
				_get_reflected_top<YDirection_>(),
				_get_reflected_right<XDirection_>(),
				_get_reflected_bottom<YDirection_>()
			);
		}

		/// <summary>
		/// <para> Creates a reflected copy of this Rect in the specified X- and Y-directions </para>
		/// <para> If `x_direction_` and `y_direction_` are known compile-time constants, it is recommended to pass them as template arguments instead. </para>
		/// </summary>
		/// <param name="x_direction_">0: No X-axis reflection; Positive: Reflect against Right boundary; Negative: Reflect against Left boundary.</param>
		/// <param name="y_direction_">0: No Y-axis reflection; Positive: Reflect against Bottom boundary; Negative: Reflect against Top boundary.</param>
		/// <returns>This Rect reflected as specified by the passed arguments.</returns>
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> Reflect(std::int32_t x_direction_, std::int32_t y_direction_) const
		{
			auto left_right = _get_reflected_x(x_direction_);
			auto top_bottom = _get_reflected_y(y_direction_);

			using std::get;
			return EmuMath::Rect<OutT_>
			(
				std::move(get<0>(left_right)),
				std::move(get<0>(top_bottom)),
				std::move(get<1>(left_right)),
				std::move(get<1>(top_bottom))
			);
		}
#pragma endregion

	private:
		_underlying_vector _left_top_right_bottom;
	};
}

#endif
