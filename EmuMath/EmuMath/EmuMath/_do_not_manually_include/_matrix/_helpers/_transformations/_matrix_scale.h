#ifndef EMU_MATH_MATRIX_SCALE_TRANSFORMATIONS_H_INC_
#define EMU_MATH_MATRIX_SCALE_TRANSFORMATIONS_H_INC_ 1

#include "../_common_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
#pragma region EXPLICIT_SIZE_SCALAR_ARG_OR_MULTI_SCALARS_ARGS
	/// <summary>
	/// <para> Creates a scaling transformation Matrix of the specified size, type, and optional memory storage order (defaulting to column-major). </para>
	/// <para> Each argument will be considered a scale in a respective axis, starting from the X-axis. </para>
	/// <para>
	///		The maximum number of scale arguments is the number of items in the smallest direction of the matrix, minus 1. 
	///		For example, in a 4x4 matrix, a maximum of 3 arguments may be provided, but in a 4x3 or 3x4 matrix a maximum of 2 may be provided.
	/// </para>
	/// <para> Omitted dimension arguments will be considered as "no scaling", and will be treated as 1. </para>
	/// <para> If only one argument is provided, one of 3 possible outcomes will result: </para>
	/// <para> A: If the argument is an EmuMath Vector: Scales for each axis will use the respective index of the Vector. </para>
	/// <para> B: If the argument is a std::tuple: Scales for each axis will use the respective element of the tuple. </para>
	/// <para> C: If the argument is anything else: Scales for every axis will use the same scale, regardless of Matrix size. </para>
	/// </summary>
	/// <param name="scale_args_">Sequential scaling values for each axis, starting from X, or a std::tuple/EmuMath Vector of sequential scaling values for each axis.</param>
	/// <returns>
	///		EmuMath Matrix representing an X-dimensional scaling transformation, or as much as is possible in the output Matrix type,
	///		where X is the smallest specified size of the Matrix minus 1.
	/// </returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class...ScaleArgs_>
	[[nodiscard]] constexpr inline auto matrix_make_scale(ScaleArgs_&&...scale_args_)
		-> std::enable_if_t
		<
			(
				(
					sizeof...(ScaleArgs_) > 0 &&
					sizeof...(ScaleArgs_) < EmuCore::TMP::smallest_constant_v<std::size_t, OutNumColumns_, OutNumRows_>
				) &&
				(
					sizeof...(ScaleArgs_) != 1 ||
					!(
						EmuCore::TMP::is_tuple_v<typename EmuCore::TMP::remove_ref_cv<typename EmuCore::TMP::first_variadic_arg<ScaleArgs_...>::type>::type> ||
						EmuMath::TMP::is_emu_vector_v<typename EmuCore::TMP::first_variadic_arg<ScaleArgs_...>::type>
					)
				)
			),
			EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
		>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_scale<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(std::forward<ScaleArgs_>(scale_args_)...);
	}
#pragma endregion

#pragma region EXPLICIT_SIZE_TUPLE_ARG
	/// <summary>
	/// <para> Creates a scaling transformation Matrix of the specified size, type, and optional memory storage order (defaulting to column-major). </para>
	/// <para> Each item in the tuple will be used in order for each sequential dimension to be scaled. Items outside of the required range are ignored. </para>
	/// <para> Omitted dimension arguments will be considered as "no scaling", and will be treated as 1. </para>
	/// </summary>
	/// <param name="scale_args_tuple_">Tuple of sequential scaling values for each axis, starting from X</param>
	/// <returns>
	///		EmuMath Matrix representing an X-dimensional scaling transformation, or as much as is possible in the output Matrix type,
	///		where X is the smallest specified size of the Matrix minus 1.
	/// </returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class...ScaleArgs_>
	[[nodiscard]] constexpr inline auto matrix_make_scale(std::tuple<ScaleArgs_...>&& scale_args_tuple_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		using tuple_type = std::tuple<ScaleArgs_...>;
		return EmuMath::Helpers::_matrix_underlying::_matrix_scale<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(std::forward<tuple_type>(scale_args_tuple_));
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class...ScaleArgs_>
	[[nodiscard]] constexpr inline auto matrix_make_scale(std::tuple<ScaleArgs_...>& scale_args_tuple_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_scale<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(scale_args_tuple_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class...ScaleArgs_>
	[[nodiscard]] constexpr inline auto matrix_make_scale(const std::tuple<ScaleArgs_...>& scale_args_tuple_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_scale<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(scale_args_tuple_);
	}
#pragma endregion

#pragma region EXPLICIT_SIZE_VECTOR_ARG
	/// <summary>
	/// <para> Creates a scaling transformation Matrix of the specified size, type, and optional memory storage order (defaulting to column-major). </para>
	/// <para> Each element in the Vector will be used in order for each sequential dimension to be scaled. Elements outside of the required range are ignored. </para>
	/// <para> Omitted dimension arguments will be considered as "no scaling", and will be treated as 1. </para>
	/// <para> The `OutT_` type argument may be omitted, in which case the `value_type_uq` of the passed Vector will be used instead. </para>
	/// </summary>
	/// <param name="scale_args_vector_">Vector of sequential scaling values for each axis, starting from X</param>
	/// <returns>
	///		EmuMath Matrix representing an X-dimensional scaling transformation, or as much as is possible in the output Matrix type,
	///		where X is the smallest specified size of the Matrix minus 1.
	/// </returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_scale(EmuMath::Vector<VecSize_, VecT_>&& scale_args_vector_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		using vec_type = EmuMath::Vector<VecSize_, VecT_>;
		return EmuMath::Helpers::_matrix_underlying::_matrix_scale<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(std::forward<vec_type>(scale_args_vector_));
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_scale(EmuMath::Vector<VecSize_, VecT_>& scale_args_vector_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_scale<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(scale_args_vector_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_scale(const EmuMath::Vector<VecSize_, VecT_>& scale_args_vector_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_scale<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(scale_args_vector_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_scale(EmuMath::Vector<VecSize_, VecT_>&& scale_args_vector_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq, OutColumnMajor_>
	{
		using vec_type = EmuMath::Vector<VecSize_, VecT_>;
		return EmuMath::Helpers::_matrix_underlying::_matrix_scale
		<
			OutNumColumns_,
			OutNumRows_,
			typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq,
			OutColumnMajor_
		>(std::forward<vec_type>(scale_args_vector_));
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_scale(EmuMath::Vector<VecSize_, VecT_>& scale_args_vector_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq, OutColumnMajor_>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_scale
		<
			OutNumColumns_,
			OutNumRows_,
			typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq,
			OutColumnMajor_
		>(scale_args_vector_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_scale(const EmuMath::Vector<VecSize_, VecT_>& scale_args_vector_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq, OutColumnMajor_>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_scale
		<
			OutNumColumns_,
			OutNumRows_,
			typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq,
			OutColumnMajor_
		>(scale_args_vector_);
	}
#pragma endregion

#pragma region DYNAMIC_SIZE_SCALAR_ARG_OR_MULTI_SCALARS_ARGS
	/// <summary>
	/// <para> Creates a scaling transformation Matrix of the specified type and optional memory storage order (defaulting to column-major). </para>
	/// <para> The number of dimensions that the scaling executes on depends on the passed arguments: </para>
	/// <para> A: Where there is one argument, which is also a std::tuple, the number of dimensions scaled will be equal to the number of items in the tuple. </para>
	/// <para> B: Where there is one argument, which is also an EmuMath::Vector, the number of dimensions scaled will be equal to the size of the Vector. </para>
	/// <para> C: Where none of the above conditions are met, the number of dimensions scaled will be equal to the number of passed arguments. </para>
	/// <para> The size of the output Matrix will be the number of dimensions scaled plus 1, in both directions (i.e. it will be a square Matrix). </para>
	/// </summary>
	/// <param name="scale_args_">Sequential scaling values for each axis, starting from X, or a std::tuple/EmuMath Vector of sequential scaling values for each axis.</param>
	/// <returns>
	///		EmuMath Matrix representing an X-dimensional scaling transformation, or as much as is possible in the output Matrix type,
	///		where X is the number of passed scalar arguments or the size of the single passed tuple/Vector.
	/// </returns>
	template<typename OutT_, bool OutColumnMajor_ = true, class...ScaleArgs_>
	[[nodiscard]] constexpr inline auto matrix_make_scale(ScaleArgs_&&...scale_args_)
		-> std::enable_if_t
		<
			(
				sizeof...(ScaleArgs_) > 0 &&
				(
					sizeof...(ScaleArgs_) != 1 ||
					!(
						EmuCore::TMP::is_tuple_v<typename EmuCore::TMP::remove_ref_cv<typename EmuCore::TMP::first_variadic_arg<ScaleArgs_...>::type>::type> ||
						EmuMath::TMP::is_emu_vector_v<typename EmuCore::TMP::first_variadic_arg<ScaleArgs_...>::type>
					)
				)
			),
			EmuMath::Matrix<sizeof...(ScaleArgs_) + 1, sizeof...(ScaleArgs_) + 1, OutT_, OutColumnMajor_>
		>
	{
		constexpr std::size_t out_square_size = sizeof...(ScaleArgs_) + 1;
		return EmuMath::Helpers::_matrix_underlying::_matrix_scale<out_square_size, out_square_size, OutT_, OutColumnMajor_>(std::forward<ScaleArgs_>(scale_args_)...);
	}
#pragma endregion

#pragma region DYNAMIC_SIZE_TUPLE_ARG
	/// <summary>
	/// <para> Creates a scaling transformation Matrix of the specified type and optional memory storage order (defaulting to column-major). </para>
	/// <para> The number of dimensions scaled will be equal to the number of items stored within the passed tuple. </para>
	/// <para> The size of the output Matrix will be the number of dimensions scaled plus 1, in both directions (i.e. it will be a square Matrix). </para>
	/// </summary>
	/// <param name="scale_args_">Tuple of sequential scaling values for each axis, starting from X.</param>
	/// <returns>
	///		EmuMath Matrix representing an X-dimensional scaling transformation, or as much as is possible in the output Matrix type,
	///		where X is the number of elements in the passed tuple.
	/// </returns>
	template<typename OutT_, bool OutColumnMajor_ = true, class...ScaleArgs_>
	[[nodiscard]] constexpr inline auto matrix_make_scale(std::tuple<ScaleArgs_...>&& scale_args_tuple_) ->
		EmuMath::Matrix<sizeof...(ScaleArgs_) + 1, sizeof...(ScaleArgs_) + 1, OutT_, OutColumnMajor_>
	{
		constexpr std::size_t out_square_size = sizeof...(ScaleArgs_) + 1;
		using tuple_type = std::tuple<ScaleArgs_...>;
		return EmuMath::Helpers::_matrix_underlying::_matrix_scale<out_square_size, out_square_size, OutT_, OutColumnMajor_>(std::forward<tuple_type>(scale_args_tuple_));
	}

	template<typename OutT_, bool OutColumnMajor_ = true, class...ScaleArgs_>
	[[nodiscard]] constexpr inline auto matrix_make_scale(std::tuple<ScaleArgs_...>& scale_args_tuple_) ->
		EmuMath::Matrix<sizeof...(ScaleArgs_) + 1, sizeof...(ScaleArgs_) + 1, OutT_, OutColumnMajor_>
	{
		constexpr std::size_t out_square_size = sizeof...(ScaleArgs_) + 1;
		return EmuMath::Helpers::_matrix_underlying::_matrix_scale<out_square_size, out_square_size, OutT_, OutColumnMajor_>(scale_args_tuple_);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, class...ScaleArgs_>
	[[nodiscard]] constexpr inline auto matrix_make_scale(const std::tuple<ScaleArgs_...>& scale_args_tuple_) ->
		EmuMath::Matrix<sizeof...(ScaleArgs_) + 1, sizeof...(ScaleArgs_) + 1, OutT_, OutColumnMajor_>
	{
		constexpr std::size_t out_square_size = sizeof...(ScaleArgs_) + 1;
		return EmuMath::Helpers::_matrix_underlying::_matrix_scale<out_square_size, out_square_size, OutT_, OutColumnMajor_>(scale_args_tuple_);
	}
#pragma endregion

#pragma region DYNAMIC_SIZE_VECTOR_ARG
	/// <summary>
	/// <para> Creates a scaling transformation Matrix of the specified type and optional memory storage order (defaulting to column-major). </para>
	/// <para> The number of dimensions scaled will be equal to the size of the passed Vector. </para>
	/// <para> The size of the output Matrix will be the number of dimensions scaled plus 1, in both directions (i.e. it will be a square Matrix). </para>
	/// </summary>
	/// <param name="scale_args_vector_">EmuMath Vector of sequential scaling values for each axis.</param>
	/// <returns>
	///		EmuMath Matrix representing an X-dimensional scaling transformation, or as much as is possible in the output Matrix type,
	///		where X is the size of the passed Vector.
	/// </returns>
	template<typename OutT_, bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_scale(EmuMath::Vector<VecSize_, VecT_>&& scale_args_vector_)
		-> EmuMath::Matrix<VecSize_ + 1, VecSize_ + 1, OutT_, OutColumnMajor_>
	{
		constexpr std::size_t out_square_size = VecSize_ + 1;
		using vec_type = EmuMath::Vector<VecSize_, VecT_>;
		return EmuMath::Helpers::_matrix_underlying::_matrix_scale<out_square_size, out_square_size, OutT_, OutColumnMajor_>(std::forward<vec_type>(scale_args_vector_));
	}

	template<typename OutT_, bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_scale(EmuMath::Vector<VecSize_, VecT_>& scale_args_vector_)
		-> EmuMath::Matrix<VecSize_ + 1, VecSize_ + 1, OutT_, OutColumnMajor_>
	{
		constexpr std::size_t out_square_size = VecSize_ + 1;
		return EmuMath::Helpers::_matrix_underlying::_matrix_scale<out_square_size, out_square_size, OutT_, OutColumnMajor_>(scale_args_vector_);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_scale(const EmuMath::Vector<VecSize_, VecT_>& scale_args_vector_)
		-> EmuMath::Matrix<VecSize_ + 1, VecSize_ + 1, OutT_, OutColumnMajor_>
	{
		constexpr std::size_t out_square_size = VecSize_ + 1;
		return EmuMath::Helpers::_matrix_underlying::_matrix_scale<out_square_size, out_square_size, OutT_, OutColumnMajor_>(scale_args_vector_);
	}

	template<bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_scale(EmuMath::Vector<VecSize_, VecT_>&& scale_args_vector_)
		-> EmuMath::Matrix<VecSize_ + 1, VecSize_ + 1, typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq, OutColumnMajor_>
	{
		constexpr std::size_t out_square_size = VecSize_ + 1;
		using vec_type = EmuMath::Vector<VecSize_, VecT_>;
		return EmuMath::Helpers::_matrix_underlying::_matrix_scale
		<
			out_square_size,
			out_square_size,
			typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq,
			OutColumnMajor_
		>(std::forward<vec_type>(scale_args_vector_));
	}

	template<bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_scale(EmuMath::Vector<VecSize_, VecT_>& scale_args_vector_)
		-> EmuMath::Matrix<VecSize_ + 1, VecSize_ + 1, typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq, OutColumnMajor_>
	{
		constexpr std::size_t out_square_size = VecSize_ + 1;
		return EmuMath::Helpers::_matrix_underlying::_matrix_scale
		<
			out_square_size,
			out_square_size,
			typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq,
			OutColumnMajor_
		>(scale_args_vector_);
	}

	template<bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_scale(const EmuMath::Vector<VecSize_, VecT_>& scale_args_vector_)
		-> EmuMath::Matrix<VecSize_ + 1, VecSize_ + 1, typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq, OutColumnMajor_>
	{
		constexpr std::size_t out_square_size = VecSize_ + 1;
		return EmuMath::Helpers::_matrix_underlying::_matrix_scale
		<
			out_square_size,
			out_square_size,
			typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq,
			OutColumnMajor_
		>(scale_args_vector_);
	}
#pragma endregion

#pragma region ASSIGNING_SCALE_FUNCS
	/// <summary>
	/// <para> Assigns a scaling transformation Matrix to the passed `out_matrix_`. </para>
	/// <para> 
	///		The scale will be for as many dimensions as the Matrix can cover, which will be the size of its smallest direction minus 1.
	///		For example, in a 4x4 matrix, a 3D scale will be assigned, but in a 4x3 or 3x4 a 2D scale will be assigned.
	/// </para>
	/// <para> This may be given a maximum number of arguments equal to the number of dimensions that the scale is for. </para>
	/// <para> Omitted dimension arguments will be considered as "no scaling", and will be treated as 1. </para>
	/// <para> If given a single argument, which is also a std::tuple, respective items in the tuple will be used for each dimension. </para>
	/// <para> If given a single argument, which is also an EmuMath Vector, respective items in the tuple will be used for each dimension. </para>
	/// </summary>
	/// <param name="out_matrix_">EmuMath Matrix to output the scaling transformation Matrix to.</param>
	/// <param name="scale_args_">Sequential arguments for each axis's scaling, starting from X; or a std::tuple/EmuMath Vector containing sequential arguments.</param>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, typename...ScaleArgs_>
	constexpr inline auto matrix_assign_scale(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, ScaleArgs_&&...scale_args_) ->
		std::enable_if_t
		<
			(
				sizeof...(ScaleArgs_) > 0 &&
				sizeof...(ScaleArgs_) < EmuCore::TMP::smallest_constant_v<std::size_t, OutNumColumns_, OutNumRows_>
			),
			void
		>
	{
		EmuMath::Helpers::_matrix_underlying::_matrix_scale_assign(out_matrix_, std::forward<ScaleArgs_>(scale_args_)...);
	}
#pragma endregion
}

#endif
