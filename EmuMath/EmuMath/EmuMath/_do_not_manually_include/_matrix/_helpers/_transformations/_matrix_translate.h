#ifndef EMU_MATH_MATRIX_TRANSLATION_TRANSFORMATIONS_H_INC_
#define EMU_MATH_MATRIX_TRANSLATION_TRANSFORMATIONS_H_INC_ 1

#include "../_common_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
#pragma region EXPLICIT_SIZE_SCALAR_ARG_OR_MULTI_SCALARS_ARGS
	/// <summary>
	/// <para> Creates a translation transformation Matrix of the specified size, type, and optional memory storage order (defaulting to column-major). </para>
	/// <para> Each argument will be considered a translation in a respective axis, starting from the X-axis. </para>
	/// <para>
	///		The maximum number of translation arguments is the number of rows in the matrix, minus 1. 
	///		For example, in a 4x4 or 3x4 matrix, a maximum of 3 arguments may be provided, but in a 4x3 matrix a maximum of 2 may be provided.
	/// </para>
	/// <para> Omitted dimension arguments will be considered as "no translation", and will be treated as 0. </para>
	/// <para> If only one argument is provided, one of 3 possible outcomes will result: </para>
	/// <para> A: If the argument is an EmuMath Vector: Translations for each axis will use the respective index of the Vector. </para>
	/// <para> B: If the argument is a std::tuple: Translations for each axis will use the respective element of the tuple. </para>
	/// <para> C: If the argument is anything else: Translations for every axis will use the same value, regardless of Matrix size. </para>
	/// </summary>
	/// <param name="translation_args_">
	///		Sequential translation values for each axis, starting from X, 
	///		or a std::tuple/EmuMath Vector of sequential translations for each axis.
	/// </param>
	/// <returns>
	///		EmuMath Matrix representing an X-dimensional translation transformation, or as much as is possible in the output Matrix type,
	///		where X is the number of rows in the Matrix minus 1.
	/// </returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class...TranslationArgs_>
	[[nodiscard]] constexpr inline auto matrix_make_translation(TranslationArgs_&&...translation_args_)
		->std::enable_if_t
		<
			(
				(
					sizeof...(TranslationArgs_) > 0 &&
					sizeof...(TranslationArgs_) < OutNumRows_
				) &&
				(
					sizeof...(TranslationArgs_) != 1 ||
					!(
						EmuCore::TMP::is_tuple_v<typename EmuCore::TMP::remove_ref_cv<typename EmuCore::TMP::first_variadic_arg<TranslationArgs_...>::type>::type> ||
						EmuMath::TMP::is_emu_vector_v<typename EmuCore::TMP::first_variadic_arg<TranslationArgs_...>::type>
					)
				)
			),
			EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
		>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_translate<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
		(
			std::forward<TranslationArgs_>(translation_args_)...
		);
	}
#pragma endregion

#pragma region EXPLICIT_SIZE_TUPLE_ARG
	/// <summary>
	/// <para> Creates a translation transformation Matrix of the specified size, type, and optional memory storage order (defaulting to column-major). </para>
	/// <para> Each item in the tuple will be used in order for each sequential dimension to be translated. Items outside of the required range are ignored. </para>
	/// <para> Omitted dimension arguments will be considered as "no translation", and will be treated as 0. </para>
	/// </summary>
	/// <param name="translation_args_tuple_">Tuple of sequential translations for each axis, starting from X</param>
	/// <returns>
	///		EmuMath Matrix representing an X-dimensional translation transformation, or as much as is possible in the output Matrix type,
	///		where X is the number of rows in the Matrix minus 1.
	/// </returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class...TranslationArgs_>
	[[nodiscard]] constexpr inline auto matrix_make_translation(std::tuple<TranslationArgs_...>&& translation_args_tuple_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		using tuple_type = std::tuple<TranslationArgs_...>;
		return EmuMath::Helpers::_matrix_underlying::_matrix_translate<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(std::forward<tuple_type>(translation_args_tuple_));
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class...TranslationArgs_>
	[[nodiscard]] constexpr inline auto matrix_make_translation(std::tuple<TranslationArgs_...>& translation_args_tuple_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_translate<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(translation_args_tuple_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class...TranslationArgs_>
	[[nodiscard]] constexpr inline auto matrix_make_translation(const std::tuple<TranslationArgs_...>& translation_args_tuple_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_translate<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(translation_args_tuple_);
	}
#pragma endregion

#pragma region EXPLICIT_SIZE_VECTOR_ARG
	/// <summary>
	/// <para> Creates a translation transformation Matrix of the specified size, type, and optional memory storage order (defaulting to column-major). </para>
	/// <para> Each element in the Vector will be used in order for each sequential dimension to be translated. Elements outside of the required range are ignored. </para>
	/// <para> Omitted dimension arguments will be considered as "no translation", and will be treated as 0. </para>
	/// <para> The `OutT_` type argument may be omitted, in which case the `value_type_uq` of the passed Vector will be used instead. </para>
	/// </summary>
	/// <param name="translation_args_vector_">Vector of sequential translations for each axis, starting from X</param>
	/// <returns>
	///		EmuMath Matrix representing an X-dimensional translation transformation, or as much as is possible in the output Matrix type,
	///		where X is the number of rows in the Matrix minus 1.
	/// </returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_translation(EmuMath::Vector<VecSize_, VecT_>&& translation_args_vector_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		using vec_type = EmuMath::Vector<VecSize_, VecT_>;
		return EmuMath::Helpers::_matrix_underlying::_matrix_translate<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(std::forward<vec_type>(translation_args_vector_));
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_translation(EmuMath::Vector<VecSize_, VecT_>& translation_args_vector_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_translate<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(translation_args_vector_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_translation(const EmuMath::Vector<VecSize_, VecT_>& translation_args_vector_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_translate<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(translation_args_vector_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_translation(EmuMath::Vector<VecSize_, VecT_>&& translation_args_vector_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq, OutColumnMajor_>
	{
		using vec_type = EmuMath::Vector<VecSize_, VecT_>;
		return EmuMath::Helpers::_matrix_underlying::_matrix_translate
		<
			OutNumColumns_,
			OutNumRows_,
			typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq,
			OutColumnMajor_
		>(std::forward<vec_type>(translation_args_vector_));
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_translation(EmuMath::Vector<VecSize_, VecT_>& translation_args_vector_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq, OutColumnMajor_>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_translate
		<
			OutNumColumns_,
			OutNumRows_,
			typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq,
			OutColumnMajor_
		>(translation_args_vector_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_translation(const EmuMath::Vector<VecSize_, VecT_>& translation_args_vector_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq, OutColumnMajor_>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_translate
		<
			OutNumColumns_,
			OutNumRows_,
			typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq,
			OutColumnMajor_
		>(translation_args_vector_);
	}
#pragma endregion

#pragma region DYNAMIC_SIZE_SCALAR_ARG_OR_MULTI_SCALARS_ARGS
	/// <summary>
	/// <para> Creates a translation transformation Matrix of the specified type and optional memory storage order (defaulting to column-major). </para>
	/// <para> The number of dimensions that the translation executes on depends on the passed arguments: </para>
	/// <para> A: Where there is one argument, which is also a std::tuple, the number of dimensions translated will be equal to the number of items in the tuple. </para>
	/// <para> B: Where there is one argument, which is also an EmuMath::Vector, the number of dimensions translated will be equal to the size of the Vector. </para>
	/// <para> C: Where none of the above conditions are met, the number of dimensions translated will be equal to the number of passed arguments. </para>
	/// <para> The size of the output Matrix will be the number of dimensions translated plus 1, in both directions (i.e. it will be a square Matrix). </para>
	/// </summary>
	/// <param name="translation_args_">sequential translations for each axis, starting from X, or a std::tuple/EmuMath Vector of sequential translations for each axis.</param>
	/// <returns>
	///		EmuMath Matrix representing an X-dimensional translation transformation, or as much as is possible in the output Matrix type,
	///		where X is the number of passed scalar arguments or the size of the single passed tuple/Vector.
	/// </returns>
	template<typename OutT_, bool OutColumnMajor_ = true, class...TranslationArgs_>
	[[nodiscard]] constexpr inline auto matrix_make_translation(TranslationArgs_&&...translation_args_)
		->std::enable_if_t
		<
			(
				sizeof...(TranslationArgs_) > 0 &&
				(
					sizeof...(TranslationArgs_) != 1 ||
					!(
						EmuCore::TMP::is_tuple_v<typename EmuCore::TMP::remove_ref_cv<typename EmuCore::TMP::first_variadic_arg<TranslationArgs_...>::type>::type> ||
						EmuMath::TMP::is_emu_vector_v<typename EmuCore::TMP::first_variadic_arg<TranslationArgs_...>::type>
					)
				)
			),
			EmuMath::Matrix<sizeof...(TranslationArgs_) + 1, sizeof...(TranslationArgs_) + 1, OutT_, OutColumnMajor_>
		>
	{
		constexpr std::size_t out_square_size = sizeof...(TranslationArgs_) + 1;
		return EmuMath::Helpers::_matrix_underlying::_matrix_translate<out_square_size, out_square_size, OutT_, OutColumnMajor_>
		(
			std::forward<TranslationArgs_>(translation_args_)...
		);
	}
#pragma endregion

#pragma region DYNAMIC_SIZE_TUPLE_ARG
	/// <summary>
	/// <para> Creates a translation transformation Matrix of the specified type and optional memory storage order (defaulting to column-major). </para>
	/// <para> The number of dimensions translated will be equal to the number of items stored within the passed tuple. </para>
	/// <para> The size of the output Matrix will be the number of dimensions translated plus 1, in both directions (i.e. it will be a square Matrix). </para>
	/// </summary>
	/// <param name="translation_args_">Tuple of sequential translations for each axis, starting from X.</param>
	/// <returns>
	///		EmuMath Matrix representing an X-dimensional translation transformation, or as much as is possible in the output Matrix type,
	///		where X is the number of elements in the passed tuple.
	/// </returns>
	template<typename OutT_, bool OutColumnMajor_ = true, class...TranslationArgs_>
	[[nodiscard]] constexpr inline auto matrix_make_translation(std::tuple<TranslationArgs_...>&& translation_args_tuple_) ->
		EmuMath::Matrix<sizeof...(TranslationArgs_) + 1, sizeof...(TranslationArgs_) + 1, OutT_, OutColumnMajor_>
	{
		constexpr std::size_t out_square_size = sizeof...(TranslationArgs_) + 1;
		using tuple_type = std::tuple<TranslationArgs_...>;
		return EmuMath::Helpers::_matrix_underlying::_matrix_translate<out_square_size, out_square_size, OutT_, OutColumnMajor_>
		(
			std::forward<tuple_type>(translation_args_tuple_)
		);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, class...TranslationArgs_>
	[[nodiscard]] constexpr inline auto matrix_make_translation(std::tuple<TranslationArgs_...>& translation_args_tuple_) ->
		EmuMath::Matrix<sizeof...(TranslationArgs_) + 1, sizeof...(TranslationArgs_) + 1, OutT_, OutColumnMajor_>
	{
		constexpr std::size_t out_square_size = sizeof...(TranslationArgs_) + 1;
		return EmuMath::Helpers::_matrix_underlying::_matrix_translate<out_square_size, out_square_size, OutT_, OutColumnMajor_>(translation_args_tuple_);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, class...TranslationArgs_>
	[[nodiscard]] constexpr inline auto matrix_make_translation(const std::tuple<TranslationArgs_...>& translation_args_tuple_) ->
		EmuMath::Matrix<sizeof...(TranslationArgs_) + 1, sizeof...(TranslationArgs_) + 1, OutT_, OutColumnMajor_>
	{
		constexpr std::size_t out_square_size = sizeof...(TranslationArgs_) + 1;
		return EmuMath::Helpers::_matrix_underlying::_matrix_translate<out_square_size, out_square_size, OutT_, OutColumnMajor_>(translation_args_tuple_);
	}
#pragma endregion

#pragma region DYNAMIC_SIZE_VECTOR_ARG
	/// <summary>
	/// <para> Creates a translation transformation Matrix of the specified type and optional memory storage order (defaulting to column-major). </para>
	/// <para> The number of dimensions translated will be equal to the size of the passed Vector. </para>
	/// <para> The size of the output Matrix will be the number of dimensions translated plus 1, in both directions (i.e. it will be a square Matrix). </para>
	/// </summary>
	/// <param name="translation_args_vector_">EmuMath Vector of sequential translations for each axis.</param>
	/// <returns>
	///		EmuMath Matrix representing an X-dimensional translation transformation, or as much as is possible in the output Matrix type,
	///		where X is the size of the passed Vector.
	/// </returns>
	template<typename OutT_, bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_translation(EmuMath::Vector<VecSize_, VecT_>&& translation_args_vector_)
		-> EmuMath::Matrix<VecSize_ + 1, VecSize_ + 1, OutT_, OutColumnMajor_>
	{
		constexpr std::size_t out_square_size = VecSize_ + 1;
		using vec_type = EmuMath::Vector<VecSize_, VecT_>;
		return EmuMath::Helpers::_matrix_underlying::_matrix_translate<out_square_size, out_square_size, OutT_, OutColumnMajor_>
		(
			std::forward<vec_type>(translation_args_vector_)
		);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_translation(EmuMath::Vector<VecSize_, VecT_>& translation_args_vector_)
		-> EmuMath::Matrix<VecSize_ + 1, VecSize_ + 1, OutT_, OutColumnMajor_>
	{
		constexpr std::size_t out_square_size = VecSize_ + 1;
		return EmuMath::Helpers::_matrix_underlying::_matrix_translate<out_square_size, out_square_size, OutT_, OutColumnMajor_>(translation_args_vector_);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_translation(const EmuMath::Vector<VecSize_, VecT_>& translation_args_vector_)
		-> EmuMath::Matrix<VecSize_ + 1, VecSize_ + 1, OutT_, OutColumnMajor_>
	{
		constexpr std::size_t out_square_size = VecSize_ + 1;
		return EmuMath::Helpers::_matrix_underlying::_matrix_translate<out_square_size, out_square_size, OutT_, OutColumnMajor_>(translation_args_vector_);
	}

	template<bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_translation(EmuMath::Vector<VecSize_, VecT_>&& translation_args_vector_)
		-> EmuMath::Matrix<VecSize_ + 1, VecSize_ + 1, typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq, OutColumnMajor_>
	{
		constexpr std::size_t out_square_size = VecSize_ + 1;
		using vec_type = EmuMath::Vector<VecSize_, VecT_>;
		return EmuMath::Helpers::_matrix_underlying::_matrix_translate
		<
			out_square_size,
			out_square_size,
			typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq,
			OutColumnMajor_
		>(std::forward<vec_type>(translation_args_vector_));
	}

	template<bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_translation(EmuMath::Vector<VecSize_, VecT_>& translation_args_vector_)
		-> EmuMath::Matrix<VecSize_ + 1, VecSize_ + 1, typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq, OutColumnMajor_>
	{
		constexpr std::size_t out_square_size = VecSize_ + 1;
		return EmuMath::Helpers::_matrix_underlying::_matrix_translate
		<
			out_square_size,
			out_square_size,
			typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq,
			OutColumnMajor_
		>(translation_args_vector_);
	}

	template<bool OutColumnMajor_ = true, typename VecT_, std::size_t VecSize_>
	[[nodiscard]] constexpr inline auto matrix_make_translation(const EmuMath::Vector<VecSize_, VecT_>& translation_args_vector_)
		-> EmuMath::Matrix<VecSize_ + 1, VecSize_ + 1, typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq, OutColumnMajor_>
	{
		constexpr std::size_t out_square_size = VecSize_ + 1;
		return EmuMath::Helpers::_matrix_underlying::_matrix_translate
		<
			out_square_size,
			out_square_size,
			typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq,
			OutColumnMajor_
		>(translation_args_vector_);
	}
#pragma endregion

#pragma region ASSIGNING_TRANSLATION_FUNCS
	/// <summary>
	/// <para> Assigns a translation transformation Matrix to the passed `out_matrix_`. </para>
	/// <para> 
	///		The translation will be for as many dimensions as the Matrix can cover, which will be the number of rows it contains minus 1
	///		For example, in a 4x4 or 3x4 matrix, a 3D translation will be assigned, but in a 4x3 Matrix a 2D translation will be assigned.
	/// </para>
	/// <para> This may be given a maximum number of arguments equal to the number of dimensions that the translation is for. </para>
	/// <para> Omitted dimension arguments will be considered as "no translation", and will be treated as 0. </para>
	/// <para> If given a single argument, which is also a std::tuple, respective items in the tuple will be used for each dimension. </para>
	/// <para> If given a single argument, which is also an EmuMath Vector, respective elements in the Vector will be used for each dimension. </para>
	/// </summary>
	/// <param name="out_matrix_">EmuMath Matrix to output the translation transformation Matrix to.</param>
	/// <param name="translation_args_">Sequential arguments for each axis's translation, starting from X; or a std::tuple/EmuMath Vector containing sequential arguments.</param>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, typename...TranslationArgs_>
	constexpr inline auto matrix_assign_translation(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, TranslationArgs_&&...translation_args_) ->
		std::enable_if_t
		<
			(
				sizeof...(TranslationArgs_) > 0 &&
				sizeof...(TranslationArgs_) < OutNumRows_
			),
			void
		>
	{
		EmuMath::Helpers::_matrix_underlying::_matrix_translate_assign(out_matrix_, std::forward<TranslationArgs_>(translation_args_)...);
	}
#pragma endregion

#pragma region VALIDITY_CHECKS
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, typename...TranslationArgs_>
	[[nodiscard]] constexpr inline bool matrix_make_translation_is_valid()
	{
		constexpr std::size_t num_args = sizeof...(TranslationArgs_);
		if constexpr (num_args == 0)
		{
			return false;
		}
		else if constexpr (num_args >= OutNumRows_)
		{
			return false;
		}
		else
		{
			return _matrix_underlying::_matrix_translate_is_valid<EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>, false, TranslationArgs_...>();
		}
	}

	template<std::size_t VecSize_, typename VecT_, typename OutT_, bool VecIsRef_, bool VecIsConst_, bool OutColumnMajor_ = true>
	[[nodiscard]] constexpr inline bool matrix_make_translation_is_valid()
	{
		using out_matrix = EmuMath::Matrix<VecSize_ + 1, VecSize_ + 1, OutT_, OutColumnMajor_>;
		using vec_type = EmuMath::Vector<VecSize_, VecT_>;
		using vec_type_cq = typename std::conditional<VecIsConst_, const vec_type, vec_type>::type;
		using vec_fully_qualified = typename std::conditional<VecIsRef_, vec_type_cq&, vec_type_cq&&>::type;
		return _matrix_underlying::_matrix_translate_is_valid<out_matrix, true, vec_fully_qualified>();
	}

	template<std::size_t VecSize_, typename VecT_, bool VecIsRef_, bool VecIsConst_, bool OutColumnMajor_ = true >
	[[nodiscard]] constexpr inline bool matrix_make_translation_is_valid()
	{
		return matrix_make_translation_is_valid<VecSize_, VecT_, typename EmuMath::Vector<VecSize_, VecT_>::value_type_uq, OutColumnMajor_>();
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, typename...TranslationArgs_>
	[[nodiscard]] constexpr inline bool matrix_assign_translation_is_valid()
	{
		constexpr std::size_t num_args = sizeof...(TranslationArgs_);
		if constexpr (num_args == 0)
		{
			return false;
		}
		else if constexpr (num_args >= OutNumRows_)
		{
			return false;
		}
		else
		{
			return _matrix_underlying::_matrix_translate_is_valid<EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>&, true, TranslationArgs_...>();
		}
	}
#pragma region
}

#endif
