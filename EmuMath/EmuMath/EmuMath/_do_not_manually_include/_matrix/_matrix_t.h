#ifndef EMU_MATH_MATRIX_T_H_INC_
#define EMU_MATH_MATRIX_T_H_INC_ 1

#include "_helpers/_all_matrix_helpers.h"
#include <exception>
#include <tuple>
#include <utility>

namespace EmuMath
{
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	struct Matrix
	{
#pragma region TMP_INFO
	public:
		using this_type = Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		using matrix_info = EmuMath::TMP::common_matrix_info<NumColumns_, NumRows_, T_, ColumnMajor_>;
		static constexpr std::size_t num_columns = matrix_info::num_columns;
		static constexpr std::size_t num_rows = matrix_info::num_rows;
		static constexpr std::size_t size = matrix_info::size;
		static constexpr std::size_t num_major_elements = matrix_info::num_major_elements;
		static constexpr std::size_t num_non_major_elements = matrix_info::num_non_major_elements;
		static constexpr bool is_column_major = matrix_info::is_column_major;
		static constexpr bool is_row_major = matrix_info::is_row_major;
		static constexpr bool contains_ref = matrix_info::contains_ref;
		static constexpr bool contains_const_ref = matrix_info::contains_const_ref;
		static constexpr bool contains_non_const_ref = matrix_info::contains_non_const_ref;
		static constexpr bool is_contiguous = matrix_info::is_contiguous;

		/// <summary> Representation of this Matrix type as an EmuMath Vector. </summary>
		using matrix_vector_type = typename matrix_info::matrix_vector_type;
		using stored_type = typename matrix_info::stored_type;
		using value_type = typename matrix_info::value_type;
		using value_type_uq = typename matrix_info::value_type_uq;
		using preferred_floating_point = typename matrix_info::preferred_floating_point;

		using column_get_ref_type = typename matrix_info::column_get_ref_type;
		using column_get_const_ref_type = typename matrix_info::column_get_const_ref_type;
		using row_get_ref_type = typename matrix_info::row_get_ref_type;
		using row_get_const_ref_type = typename matrix_info::row_get_const_ref_type;
		using major_get_ref_type = typename matrix_info::major_get_ref_type;
		using major_get_const_ref_type = typename matrix_info::major_get_const_ref_type;
		using non_major_get_ref_type = typename matrix_info::non_major_get_ref_type;
		using non_major_get_const_ref_type = typename matrix_info::non_major_get_const_ref_type;
#pragma endregion

#pragma region HELPER_STATIC_FUNCS
	public:
		/// <summary>
		/// <para> Outputs a copy of the major index of the two provided indices for this Matrix type. </para>
		/// </summary>
		/// <returns> column_index_ if this Matrix type is column-major, otherwise row_index_. </returns>
		[[nodiscard]] static constexpr inline std::size_t get_major_index(std::size_t column_index_, std::size_t row_index_)
		{
			if constexpr (is_column_major)
			{
				return column_index_;
			}
			else
			{
				return row_index_;
			}
		}

		/// <summary>
		/// <para> Outputs a copy of the non-major index of the two provided indices for this Matrix type. </para>
		/// </summary>
		/// <returns> row_index_ if this Matrix type is column-major, otherwise column_index_. </returns>
		[[nodiscard]] static constexpr inline std::size_t get_non_major_index(std::size_t column_index_, std::size_t row_index_)
		{
			if constexpr (is_column_major)
			{
				return row_index_;
			}
			else
			{
				return column_index_;
			}
		}

		/// <summary>
		/// <para> Unflattens the provided index into a column index and a row index for this Matrix type. </para>
		/// <para> Output contained type may be modified, but is recommended to stick to std::size_t. </para>
		/// </summary>
		/// <param name="flattened_index_">
		///		Flattened index to unflatten. This will always be read in column-major order
		///		(i.e. index x+1 is the next item in a column immediately after x, or the next column if x is the end of a column).
		/// </param>
		/// <returns>Pair of std::size_t, containing the unflattened column index in first, and the unflattened row index in second.</returns>
		[[nodiscard]] static constexpr inline std::pair<std::size_t, std::size_t> unflatten_index(std::size_t flattened_index_)
		{
			if constexpr(size != 0)
			{
				return std::pair<std::size_t, std::size_t>
				(
					flattened_index_ / num_rows,
					flattened_index_ % num_rows
				);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<T_>(),
					"Attempted to unflatten an index for an EmuMath Matrix, but the size of the Matrix is 0, meaning a conversion cannot be made due to integral divide-by-0."
				);
			}
		}
#pragma endregion

#pragma region CONSTRUCTION_CHECKS
	public:
		/// <summary> Returns true if this Matrix can be default-constructed, otherwise false. </summary>
		[[nodiscard]] static constexpr inline bool is_default_constructible()
		{
			return std::is_default_constructible_v<matrix_vector_type>;
		}

		/// <summary> Returns true if this Matrix can constructed by copying a const reference to another of its type, otherwise false. </summary>
		[[nodiscard]] static constexpr inline bool is_const_copy_constructible()
		{
			return std::is_constructible_v<matrix_vector_type, const matrix_vector_type&>;
		}

		/// <summary> Returns true if this Matrix can constructed by copying a non-const reference to another of its type, otherwise false. </summary>
		[[nodiscard]] static constexpr inline bool is_non_const_copy_constructible()
		{
			return std::is_constructible_v<matrix_vector_type, matrix_vector_type&>;
		}

		/// <summary> Returns true if this Matrix can be move-constructed with an rvalue reference to another of its type, otherwise false. </summary>
		[[nodiscard]] static constexpr inline bool is_move_constructible()
		{
			return std::is_constructible_v<matrix_vector_type, matrix_vector_type&&>;
		}

		/// <summary>
		/// <para> Returns true if this Matrix can be constructed from the provided selection of Vectors_. </para>
		/// <para> All arguments provided to Vectors_ must be EmuMath Vectors, and will be provided as major-elements for the constructed Matrix.. </para>
		/// <para> The provided Args_ will be interpreted as though they are references to be forwarded. </para>
		/// </summary>
		/// <typeparam name="Vectors_">All EmuMath Vectors to check for input validity.</typeparam>
		/// <returns>True if all provided EmuMath Vectors_ may be used to construct a Matrix of this type in terms of major-elements, otherwise false.</returns>
		template<class...Vectors_>
		[[nodiscard]] static constexpr inline bool is_constructible_from_major_vectors()
		{
			return
			(
				EmuCore::TMP::variadic_and_v<EmuMath::TMP::is_emu_vector_v<Vectors_>...> &&
				sizeof...(Vectors_) == num_major_elements &&
				(
					// This braced section is to prevent (unlikely, but not impossible) conflicts when constructing from a matrix_vector_type argument
					num_major_elements != 1 ||
					!std::is_same_v<matrix_vector_type, EmuCore::TMP::remove_ref_cv_t<EmuCore::TMP::first_variadic_arg_t<Vectors_...>>>
				) &&
				std::is_constructible_v<matrix_vector_type, EmuCore::TMP::forward_result_t<Vectors_>...>
			);
		}		

		/// <summary>
		/// <para> Returns true if this Matrix can be constructed with the provided Args_, interpreted as per-element scalars. </para>
		/// <para> The provided number of Args_ must be equal to the total number of elements within this Matrix type (i.e. its static `size` member). </para>
		/// <para> The provided Args_ will be interpreted as though they are references to be forwarded (e.g. an Arg_ of `int` will be treated as `int&amp;&amp;`). </para>
		/// </summary>
		/// <typeparam name="Args_">All argument types that will be forwarded for construction.</typeparam>
		/// <returns>True if scalar-argument construction is possible for this Matrix type with the provided arguments, otherwise false.</returns>
		template<typename...Args_>
		[[nodiscard]] static constexpr inline bool is_constructible_with_scalar_args()
		{
			return
			(
				sizeof...(Args_) == size &&
				(size != num_major_elements || !EmuCore::TMP::variadic_and_v<EmuMath::TMP::is_emu_vector_v<Args_>...>) &&
				EmuCore::TMP::variadic_and_v<std::is_constructible_v<stored_type, EmuCore::TMP::forward_result_t<Args_>>...>
			);
		}

		template<typename...Args_>
		[[nodiscard]] static constexpr inline bool is_constructible_with_single_scalar_arg()
		{
			// Requires 1 arg, which is not a Matrix, not valid for construction via major Vectors, is not the matrix_vector_type, and matrix_vector_type is constructible via it
			return
			(
				sizeof...(Args_) == 1 &&
				!EmuCore::TMP::variadic_or_v<EmuMath::TMP::is_emu_matrix_v<Args_>...> &&
				!is_constructible_from_major_vectors<Args_...>() &&
				!EmuCore::TMP::variadic_or_v<std::is_same_v<matrix_vector_type, EmuCore::TMP::remove_ref_cv_t<Args_>>...> &&
				EmuCore::TMP::variadic_and_v<std::is_constructible_v<matrix_vector_type, EmuCore::TMP::forward_result_t<Args_>>...>
			);
		}

		/// <summary>
		/// <para> Returns true if this Matrix can be constructed via its variadic argument constructor. </para>
		/// <para> Effectively translates to `is_constructible_with_scalar_args || is_constructible_from_major_vectors`. </para>
		/// <para> Note that, when true, this does not determine which construction method is used, but major-vector construction will take priority when both are true. </para>
		/// </summary>
		/// <returns>True if this Matrix's variadic constructor may be used with the provided arguments, otherwise false.</returns>
		template<class...Args_>
		[[nodiscard]] static constexpr inline bool is_constructible_via_variadic_constructor()
		{
			return 
			(
				is_constructible_with_scalar_args<Args_...>() || 
				is_constructible_from_major_vectors<Args_...>() ||
				is_constructible_with_single_scalar_arg<Args_...>()
			);
		}

		/// <summary>
		/// <para> Returns true if this Matrix can be constructed via the provided other Matrix_ type. </para>
		/// <para> Matrix_ is expected to be another Matrix type, and thus this will return false if the unqualified Matrix_ is the same as this_type. </para>
		/// </summary>
		/// <returns>True if this Matrix may be conversion-constructed via the provided Matrix_ type.</returns>
		template<class Matrix_>
		[[nodiscard]] static constexpr inline bool is_constructible_via_other_matrix_type()
		{
			constexpr bool is_other_matrix_type_ = EmuCore::TMP::variadic_and_v
			<
				EmuMath::TMP::is_emu_matrix_v<Matrix_>,
				!std::is_same_v<this_type, EmuCore::TMP::remove_ref_cv_t<Matrix_>>
			>;
			if constexpr (is_other_matrix_type_)
			{
				return EmuMath::Helpers::matrix_copy_is_valid<NumColumns_, NumRows_, T_, ColumnMajor_, Matrix_>();
			}
			else
			{
				return false;
			}
		}
#pragma endregion

#pragma region GENERAL_STATIC_FUNCS
	public:
		[[nodiscard]] static constexpr inline value_type_uq get_implied_zero()
		{
			return EmuMath::Helpers::matrix_get_non_contained<this_type>();
		}

		[[nodiscard]] static constexpr inline typename EmuMath::TMP::matrix_non_contained_column<this_type>::type get_implied_zero_column()
		{
			return EmuMath::Helpers::matrix_get_column_non_contained<this_type>();
		}

		[[nodiscard]] static constexpr inline typename EmuMath::TMP::matrix_non_contained_row<this_type>::type get_implied_zero_row()
		{
			return EmuMath::Helpers::matrix_get_row_non_contained<this_type>();
		}

		[[nodiscard]] static constexpr inline decltype(EmuMath::Helpers::matrix_get_major_non_contained<this_type>()) get_implied_zero_major()
		{
			return EmuMath::Helpers::matrix_get_major_non_contained<this_type>();
		}

		[[nodiscard]] static constexpr inline decltype(EmuMath::Helpers::matrix_get_non_major_non_contained<this_type>()) get_implied_zero_non_major()
		{
			return EmuMath::Helpers::matrix_get_non_major_non_contained<this_type>();
		}
#pragma endregion

#pragma region CONSTRUCTORS
	public:
		/// <summary> Default constructor for this Matrix. Only available if its underlying elements may be default-constructed. </summary>
		template<typename = std::enable_if_t<is_default_constructible()>>
		constexpr inline Matrix() : _data()
		{
		}

		/// <summary> Constructs a copy of the const-referenced EmuMath Matrix of this type. Only available if a const-copy is valid for the Matrix's underlying elements. </summary>
		/// <param name="to_copy_">Const reference to an EmuMath Matrix of this type to copy.</param>
		template<typename = std::enable_if_t<is_const_copy_constructible()>>
		constexpr inline Matrix(const this_type& to_copy_) : _data(to_copy_._data)
		{
		}

		/// <summary> Constructs a copy of the referenced EmuMath Matrix of this type. Only available if a non-const-copy is valid for the Matrix's underlying elements. </summary>
		/// <param name="to_copy_">Non-const reference to an EmuMath Matrix of this type to copy.</param>
		template<typename = std::enable_if_t<is_non_const_copy_constructible()>>
		constexpr inline Matrix(this_type& to_copy_) : _data(to_copy_._data)
		{
		}

		/// <summary>
		///		Moves the passed EmuMath Matrix of this type into a newly constructed Matrix of the same type. 
		///		Only available if this Matrix's underlying elements may be moved.
		/// </summary>
		/// <param name="to_move_">EmuMath Matrix to move into the newly constructed Matrix of the same type.</param>
		template<typename = std::enable_if_t<is_move_constructible()>>
		constexpr inline Matrix(this_type&& to_move_) : _data(std::move(to_move_._data))
		{
		}

		/// <summary>
		/// <para> 
		///		Copies the data of the const-referenced matrix_vector_type into a newly constructed Matrix's data. 
		///		Only available if this Matrix's underlying data may be const-copy constructed.
		/// </para>
		/// </summary>
		/// <param name="matrix_vector_to_copy_">Constant reference to an EmuMath Vector of this Matrix's matrix_vector_type to copy.</param>
		template<typename = std::enable_if_t<is_const_copy_constructible()>>
		[[nodiscard]] constexpr inline Matrix(const matrix_vector_type& matrix_vector_to_copy_) : _data(matrix_vector_to_copy_)
		{
		}

		/// <summary>
		/// <para> 
		///		Copies the data of the referenced matrix_vector_type into a newly constructed Matrix's data. 
		///		Only available if this Matrix's underlying data may be non-const-copy constructed.
		/// </para>
		/// </summary>
		/// <param name="matrix_vector_to_copy_">Non-constant reference to an EmuMath Vector of this Matrix's matrix_vector_type to copy.</param>
		template<typename = std::enable_if_t<is_non_const_copy_constructible()>>
		[[nodiscard]] constexpr inline Matrix(matrix_vector_type& matrix_vector_to_copy_) : _data(matrix_vector_to_copy_)
		{
		}

		/// <summary>
		/// <para>
		///		Moves the data of the passed matrix_vector_type into a newly constructed Matrix's data. 
		///		Only available if this Matrix's underlying data may be move constructed.
		/// </para>
		/// </summary>
		/// <param name="matrix_vector_to_move_">Rvalue reference to an EmuMath Vector of this Matrix's matrix_vector_type to move.</param>
		template<typename = std::enable_if_t<is_move_constructible()>>
		[[nodiscard]] constexpr inline Matrix(matrix_vector_type&& matrix_vector_to_move_) : _data(std::forward<matrix_vector_type>(matrix_vector_to_move_))
		{
		}

		/// <summary>
		/// <para> Explicit conversion constructor to create this Matrix type as a converted copy of the provided Matrix. </para>
		/// <para> Indices not contained in this Matrix will be ignored. </para>
		/// <para> Indices not contained in the passed Matrix, but contained within this Matrix, will be interpreted as implied zero. </para>
		/// </summary>
		/// <param name="matrix_to_convert_">Non-const reference to an EmuMath Matrix of a different type to convert into this Matrix type.</param>
		template
		<
			std::size_t InNumColumns_, std::size_t InNumRows_, typename InT_, bool InColumnMajor_,
			typename = std::enable_if_t<is_constructible_via_other_matrix_type<EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&>()>
		>
		explicit constexpr inline Matrix(EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& matrix_to_convert_) :
			_data
			(
				EmuMath::Helpers::matrix_copy<NumColumns_, NumRows_, T_, ColumnMajor_, InT_, InNumColumns_, InNumRows_, InColumnMajor_>(matrix_to_convert_)._data
			)
		{
		}

		/// <summary>
		/// <para> Explicit conversion constructor to create this Matrix type as a converted copy of the provided Matrix. </para>
		/// <para> Indices not contained in this Matrix will be ignored. </para>
		/// <para> Indices not contained in the passed Matrix, but contained within this Matrix, will be interpreted as implied zero. </para>
		/// </summary>
		/// <param name="matrix_to_convert_">Const reference to an EmuMath Matrix of a different type to convert into this Matrix type.</param>
		template
		<
			std::size_t InNumColumns_, std::size_t InNumRows_, typename InT_, bool InColumnMajor_,
			typename = std::enable_if_t<is_constructible_via_other_matrix_type<const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&>()>
		>
		explicit constexpr inline Matrix(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& matrix_to_convert_) :
			_data
			(
				EmuMath::Helpers::matrix_copy<NumColumns_, NumRows_, T_, ColumnMajor_, InT_, InNumColumns_, InNumRows_, InColumnMajor_>(matrix_to_convert_)._data
			)
		{
		}

		/// <summary>
		/// <para> Explicit conversion constructor to create this Matrix type as a converted move-or-copy of the provided Matrix. </para>
		/// <para> Indices not contained in this Matrix will be ignored. </para>
		/// <para> Indices not contained in the passed Matrix, but contained within this Matrix, will be interpreted as implied zero. </para>
		/// <para>
		///		NOTE: This constructor allows false positive results in checks for if this type is constructible with the provided argument. 
		///		This is to prevent invalid implicit casting to an lvalue-reference to provide safety from constructing with dangling references.
		/// </para>
		/// </summary>
		/// <param name="matrix_to_convert_">Non-const rvalue reference to an EmuMath Matrix of a different type to convert into this Matrix type via move-or-copy.</param>
		template
		<
			std::size_t InNumColumns_, std::size_t InNumRows_, typename InT_, bool InColumnMajor_,
			typename = std::enable_if_t<!std::is_same_v<this_type, EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>>>
		>
		explicit constexpr inline Matrix(EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& matrix_to_convert_) :
			_data
			(
				EmuMath::Helpers::matrix_copy<NumColumns_, NumRows_, T_, ColumnMajor_, InT_, InNumColumns_, InNumRows_, InColumnMajor_>
				(
					std::forward<EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>>(matrix_to_convert_)
				)._data
			)
		{
			static_assert
			(
				is_constructible_via_other_matrix_type<EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&&>(),
				"Attempted to perform invalid move-construction of an EmuMath Matrix. This may have been performed due to a removed std::enable_if_t trigger. This is a side-effect of an intentional change to prevent construction of reference-containing Matrices via temporary non-reference-containing Matrices (which would result in dangling references), and is likely what is occurring in this situation. Note that move-construction falls back to copy construction if not possible, so the alternative of copy-construction if this is not a reference-containing Matrix type is likely also not possible."
			);
		}

		/// <summary>
		/// <para> Explicit conversion constructor to create this Matrix type as a converted move-or-copy of the provided Matrix. </para>
		/// <para> Indices not contained in this Matrix will be ignored. </para>
		/// <para> Indices not contained in the passed Matrix, but contained within this Matrix, will be interpreted as implied zero. </para>
		/// <para>
		///		NOTE: This constructor allows false positive results in checks for if this type is constructible with the provided argument. 
		///		This is to prevent invalid implicit casting to an lvalue-reference to provide safety from constructing with dangling references.
		/// </para>
		/// </summary>
		/// <param name="matrix_to_convert_">Const rvalue reference to an EmuMath Matrix of a different type to convert into this Matrix type via move-or-copy.</param>
		template
		<
			std::size_t InNumColumns_, std::size_t InNumRows_, typename InT_, bool InColumnMajor_,
			typename = std::enable_if_t<!std::is_same_v<this_type, EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>>>
		>
		explicit constexpr inline Matrix(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& matrix_to_convert_) :
			_data
			(
				EmuMath::Helpers::matrix_copy<NumColumns_, NumRows_, T_, ColumnMajor_, InT_, InNumColumns_, InNumRows_, InColumnMajor_>
				(
					std::forward<const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>>(matrix_to_convert_)
				)._data
			)
		{
			static_assert
			(
				is_constructible_via_other_matrix_type<const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&&>(),
				"Attempted to perform invalid const-move-construction of an EmuMath Matrix. This may have been performed due to a removed std::enable_if_t trigger. This is a side-effect of an intentional change to prevent construction of reference-containing Matrices via temporary non-reference-containing Matrices (which would result in dangling references), which is likely what is occurring in this situation. Note that move-construction falls back to copy construction if not possible, so the alternative of copy-construction if this is not a reference-containing Matrix type is likely also not possible."
			);
		}

		/// <summary>
		/// <para> Constructs an EmuMath Matrix from either a selection of major EmuMath Vectors or a selection of per-element scalars. </para>
		/// <para>
		///		To construct via scalars: The number of provided Args_ must be equal to the total number of elements within this Matrix type (i.e. its `size`). 
		///		Additionally, this Matrix's stored_type must be constructible via all Args_ as single arguments. 
		///		It should be noted that the placement of these indices is contiguous in memory, and thus is modified by this Matrix's major-order.
		/// </para>
		/// <para>
		///		To construct via major EmuMath Vectors: The number of provided Args_ must be equal to the number of major elements within this Matrix type. 
		///		Additionally, all Args_ must be EmuMath Vectors, and when forwarded must be valid construction arguments for constructing this Matrix's matrix_vector_type.
		/// </para>
		/// <para>
		///		To construct via a single non-Matrix Arg: The number of provided Args_ must be equal to 1. 
		///		Additionally, the Arg_ must be valid to construct matrix_vector_type, is not matrix_vector_type, is not valid for construction via major Vectors, 
		///		and is not an EmuMath Matrix.
		/// </para>
		/// <para> Where both are valid, construction via major EmuMath Vectors takes priority. </para>
		/// </summary>
		/// <param name="contiguous_args_">Contiguous scalar arguments, or contiguous major-vector EmuMath Vector arguments.</param>
		template<typename...Args_, typename = std::enable_if_t<is_constructible_via_variadic_constructor<Args_...>()>>
		explicit constexpr inline Matrix(Args_&&...contiguous_args_) :
			_data
			(
				_make_data(std::make_index_sequence<num_major_elements>(), std::forward<Args_>(contiguous_args_)...)
			)
		{
		}
#pragma endregion

#pragma region ACCESS
	public:
		/// <summary>
		/// <para> Accesses the element at the provided indices within this Matrix, with compile-time validity checks. </para>
		/// <para> If either ColumnIndex_ or RowIndex_ is not contained, a static_assert will be triggered. </para>
		/// </summary>
		/// <returns>Reference to the element at the provided index within this Matrix.</returns>
		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		[[nodiscard]] constexpr inline value_type& at()
		{
			if constexpr (ColumnIndex_ < num_columns)
			{
				if constexpr (RowIndex_ < num_rows)
				{
					constexpr std::size_t major_index_ = get_major_index(ColumnIndex_, RowIndex_);
					constexpr std::size_t non_major_index_ = get_non_major_index(ColumnIndex_, RowIndex_);
					return _data.template at<major_index_>().template at<non_major_index_>();
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<std::size_t, RowIndex_>(),
						"Attempted to access an index of an EmuMath Matrix, but the provided RowIndex_ is invalid. The inclusive valid row index range is 0:(num_rows - 1)."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, RowIndex_>(),
					"Attempted to access an index of an EmuMath Matrix, but the provided ColumnIndex_ is invalid. The inclusive valid column index range is 0:(num_columns - 1)."
				);
			}
		}

		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		[[nodiscard]] constexpr inline const value_type& at() const
		{
			return const_cast<this_type*>(this)->template at<ColumnIndex_, RowIndex_>();
		}

		/// <summary>
		/// <para> Accesses the element at the provided indices within this Matrix, with compile-time validity checks. </para>
		/// <para> If the provided idnex is contained, this will return a reference to the specified element. </para>
		/// <para> If either ColumnIndex_ or RowIndex_ is not contained, this will return a newly constructed value_type_uq. </para>
		/// </summary>
		/// <returns>Reference to the element at the provided index within this Matrix if the index is contained, otherwise a newly constructed value_type_uq.</returns>
		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_theoretical_get_result<ColumnIndex_, RowIndex_, this_type&>::type AtTheoretical()
		{
			return EmuMath::Helpers::matrix_get_theoretical<ColumnIndex_, RowIndex_>(*this);
		}

		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_theoretical_get_result<ColumnIndex_, RowIndex_, const this_type&>::type AtTheoretical() const
		{
			return EmuMath::Helpers::matrix_get_theoretical<ColumnIndex_, RowIndex_>(*this);
		}

		/// <summary>
		/// <para> Accesses the element at the provided FlattenedIndex_ within this Matrix, with compile-time validity checks. </para>
		/// <para> If the flattened index exceeds this Matrix's size, or the unflattened indices are deemed invalid, a static_assert will be triggered. </para>
		/// </summary>
		/// <returns>Reference to the element at the provided column-major index within this Matrix.</returns>
		template<std::size_t FlattenedIndex_>
		[[nodiscard]] constexpr inline value_type& at()
		{
			if constexpr (FlattenedIndex_ < size)
			{
				// Assuming we reach this point, all indices should be valid, but we want to maintain suitable static_assert messages in case of inaccurate calculations
				constexpr auto unflattened_indices_ = unflatten_index(FlattenedIndex_);
				constexpr std::size_t column_index_ = unflattened_indices_.first;

				if constexpr (column_index_ < num_columns)
				{
					constexpr std::size_t row_index_ = unflattened_indices_.second;
					if constexpr (row_index_ < num_rows)
					{
						constexpr std::size_t major_index_ = get_major_index(column_index_, row_index_);
						constexpr std::size_t non_major_index_ = get_non_major_index(column_index_, row_index_);
						return _data.template at<major_index_>().template at<non_major_index_>();
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<std::size_t, row_index_>(),
							"Attempted to access a flattened index within an EmuMath Matrix, but the determined row index is invalid."
						);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<std::size_t, column_index_>(),
						"Attempted to access a flattened index within an EmuMath Matrix, but the determined column index is invalid."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, FlattenedIndex_>(),
					"Attempted to access a flattened index within an EmuMath Matrix, but the provided FlattenedIndex_ exceeds the valid range. The inclusive valid flattened index range is 0:(size-1)."
				);
			}
		}

		template<std::size_t FlattenedIndex_>
		[[nodiscard]] constexpr inline const value_type& at() const
		{
			return const_cast<this_type*>(this)->template at<FlattenedIndex_>();
		}

		/// <summary>
		/// <para> Accesses the element at the provided indices within this Matrix, with compile-time validity checks. </para>
		/// <para> If the provided idnex is contained, this will return a reference to the specified element. </para>
		/// <para> If either ColumnIndex_ or RowIndex_ is not contained, this will return a newly constructed value_type_uq. </para>
		/// </summary>
		/// <returns>Reference to the element at the provided index within this Matrix if the index is contained, otherwise a newly constructed value_type_uq.</returns>
		template<std::size_t FlattenedIndex_>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_flattened_theoretical_get_result<FlattenedIndex_, this_type&>::type AtTheoretical()
		{
			return EmuMath::Helpers::matrix_get_theoretical<FlattenedIndex_>(*this);
		}

		template<std::size_t FlattenedIndex_>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_flattened_theoretical_get_result<FlattenedIndex_, const this_type&>::type AtTheoretical() const
		{
			return EmuMath::Helpers::matrix_get_theoretical<FlattenedIndex_>(*this);
		}

		/// <summary>
		/// <para> Accesses the element at the provided indices within this Matrix, with runtime-time validity checks. </para>
		/// <para> If either column_index_ or row_index_, a std::out_of_range exception will be thrown. </para>
		/// </summary>
		/// <param name="column_index_">: Index of the column to access.</param>
		/// <param name="row_index_">: Index of the row to access.</param>
		/// <returns>Reference to the element at the provided index within this Matrix.</returns>
		[[nodiscard]] constexpr inline value_type& at(std::size_t column_index_, std::size_t row_index_)
		{
			if constexpr (size > 0)
			{
				constexpr bool constexpr_str_ = __cplusplus >= 201907L;
				if ((column_index_ < num_columns) && (row_index_ < num_rows))
				{
					return _data[get_major_index(column_index_, row_index_)][get_non_major_index(column_index_, row_index_)];
				}
				else
				{
					// AT LEAST 1 BAD INDEX
					if constexpr (constexpr_str_)
					{
						// We can provide some extra information if we have access to constexpr strings
						// --- This is to allow `at(index_)` to still satisfy constexpr constraints in standards before C++20
						std::string out_str_;
						out_str_.reserve(170); // Reserves enough space for all literal chars, alongside some extra for range and index after conversion.
						out_str_ += "Attempted to access an invalid contained index of an EmuMath Matrix.\nProvided indices (Column, Row): (";
						out_str_ += std::to_string(column_index_);
						out_str_ += ", ";
						out_str_ += std::to_string(row_index_);
						out_str_ += ")\nInclusive valid Column Range: 0:";
						out_str_ += std::to_string(num_columns - 1);
						out_str_ += "\nInclusive valid Row Range: 0:";
						out_str_ += std::to_string(num_rows - 1);
						throw std::out_of_range(out_str_);
					}
					else
					{
						throw std::out_of_range("Attempted to access an invalid contained index of an EmuMath Matrix.");
					}
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<T_>(),
					"Attempted to access a non-theoretical index of a 0-sized EmuMath Matrix."
				);
			}
		}

		[[nodiscard]] constexpr inline const value_type& at(std::size_t column_index_, std::size_t row_index_) const
		{
			return const_cast<this_type*>(this)->at(column_index_, row_index_);
		}

		/// <summary>
		/// <para> Accesses the element at the provided flattened_index_ within this Matrix, with runtime-time validity checks. </para>
		/// <para> If the flattened index exceeds this Matrix's size, or the unflattened indices are deemed invalid, a runtime exception will be thrown. </para>
		/// </summary>
		/// <param name="flattened_index_">: Column-major flattened index of the element to retrieve.</param>
		/// <returns>Reference to the element at the provided column-major index within this Matrix.</returns>
		[[nodiscard]] constexpr inline value_type& at(std::size_t flattened_index_)
		{
			if constexpr (size > 0)
			{
				auto unflattened_indices_ = unflatten_index(flattened_index_);
				if ((unflattened_indices_.first < num_columns) && (unflattened_indices_.second < num_rows))
				{
					return operator()(unflattened_indices_.first, unflattened_indices_.second);
				}
				else
				{
					constexpr bool constexpr_str_ = __cplusplus >= 201907L;
					if constexpr (constexpr_str_)
					{
						// We can provide some extra information if we have access to constexpr strings
						// --- This is to allow `at(index_)` to still satisfy constexpr constraints in standards before C++20
						std::string out_str_;
						out_str_.reserve(160); // Reserves enough space for all literal chars, alongside some extra for range and index after conversion.
						out_str_ += "Attempted to access an invalid flattened index of an EmuMath Matrix.\nProvided index: ";
						out_str_ += std::to_string(flattened_index_);
						out_str_ += "\nInclusive valid flattened index range: 0:";
						out_str_ += std::to_string(size - 1);
						throw std::out_of_range(out_str_);
					}
					else
					{
						throw std::out_of_range("Attempted to access an invalid flattened index of an EmuMath Matrix.");
					}
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<T_>(),
					"Attempted to access a non-theoretical index of a 0-sized EmuMath Matrix."
				);
			}
		}

		[[nodiscard]] constexpr inline const value_type& at(std::size_t flattened_index_) const
		{
			return const_cast<this_type*>(this)->at(flattened_index_);
		}

		/// <summary>
		/// <para> Accesses the element at the provided indices within this Matrix, with no validity checks. </para>
		/// <para> If either ColumnIndex_ or RowIndex_, behaviour is undefined. </para>
		/// </summary>
		/// <returns>Reference to the element at the provided index within this Matrix.</returns>
		[[nodiscard]] constexpr inline value_type& operator()(std::size_t column_index_, std::size_t row_index_)
		{
			return _data[get_major_index(column_index_, row_index_)][get_non_major_index(column_index_, row_index_)];
		}

		[[nodiscard]] constexpr inline const value_type& operator()(std::size_t column_index_, std::size_t row_index_) const
		{
			return const_cast<this_type*>(this)->operator()(column_index_, row_index_);
		}

		/// <summary>
		/// <para> Accesses the element at the provided flattened_index_ within this Matrix. </para>
		/// <para> If the flattened index exceeds this Matrix's size, or the unflattened indices are deemed invalid, behaviour is undefined. </para>
		/// </summary>
		/// <param name="flattened_index_">: Column-major flattened index of the element to retrieve.</param>
		/// <returns>Reference to the element at the provided column-major index within this Matrix.</returns>
		[[nodiscard]] constexpr inline value_type& operator[](std::size_t flattened_index_)
		{
			auto unflattened_indices_ = unflatten_index(flattened_index_);
			return this->operator()(unflattened_indices_.first, unflattened_indices_.second);
		}

		[[nodiscard]] constexpr inline const value_type& operator[](std::size_t flattened_index_) const
		{
			return const_cast<this_type*>(this)->operator[](flattened_index_);
		}

		/// <summary>
		/// <para> Accesses a contiguous data pointer to the elements of this Matrix, starting from an element at the provided Offset_. </para>
		/// <para> Offset_: Index to retrieve a pointer to. Defaults to 0. </para>
		/// <para> This function is not available for reference-containing matrices, or matrices whose elements are not fully contiguous. </para>
		/// </summary>
		/// <returns>Pointer to the value at the provided index.</returns>
		template<std::size_t Offset_ = 0, typename = std::enable_if_t<is_contiguous>>
		[[nodiscard]] constexpr inline value_type* data()
		{
			if constexpr(!contains_ref)
			{
				if constexpr (size != 0)
				{
					if constexpr (Offset_ < size)
					{
						if constexpr (Offset_ == 0)
						{
							return _data.template at<0>().data();
						}
						else
						{
							return (_data.template at<0>().data()) + Offset_;
						}
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<std::size_t, Offset_>(),
							"Attempted to access a pointer to the contiguous data of an EmuMath Matrix starting from a provided index Offset_, but the provided Offset_ was greater than the total number of elements within the Matrix."
						);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<T_>(),
						"Attempted to access a pointer to the contiguous data of an EmuMath Matrix, but the Matrix type contains no non-theoretical elements."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<T_>(),
					"Attempted to access a pointer to the contiguous data of an EmuMath Matrix which contains references. This behaviour is not allowed as references are not guaranteed to be contiguous."
				);
			}
		}

		template<std::size_t Offset_ = 0, typename = std::enable_if_t<is_contiguous>>
		[[nodiscard]] constexpr inline const value_type* data() const
		{
			return const_cast<this_type*>(this)->template data<Offset_>();
		}

		/// <summary>
		/// <para> Accesses the column at the provided ColumnIndex_ within this Matrix. </para>
		/// <para> If this Matrix is column-major: This will be a direct reference to the specified column. </para>
		/// <para> If this Matrix is not column-major: This will be an EmuMath Vector of references to elements at respective points within the specified column. </para>
		/// </summary>
		/// <returns>EmuMath Vector referencing the specified column within this Matrix.</returns>
		template<std::size_t ColumnIndex_>
		[[nodiscard]] constexpr inline column_get_ref_type ColumnAt()
		{
			if constexpr (ColumnIndex_ < num_columns)
			{
				if constexpr (is_column_major)
				{
					return _data.template at<ColumnIndex_>();
				}
				else
				{
					return _make_non_major_vector<ColumnIndex_, column_get_ref_type>(std::make_index_sequence<num_rows>());
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, ColumnIndex_>(),
					"Attempted to access a column within an EmuMath Matrix, but the provided ColumnIndex_ is invalid. The inclusive valid column index range is 0:(num_columns - 1)."
				);
			}
		}

		template<std::size_t ColumnIndex_>
		[[nodiscard]] constexpr inline column_get_const_ref_type ColumnAt() const
		{
			if constexpr (ColumnIndex_ < num_columns)
			{
				if constexpr (is_column_major)
				{
					return _data.template at<ColumnIndex_>();
				}
				else
				{
					return _make_non_major_vector<ColumnIndex_, column_get_const_ref_type>(std::make_index_sequence<num_rows>());
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, ColumnIndex_>(),
					"Attempted to const-access a column within an EmuMath Matrix, but the provided ColumnIndex_ is invalid. The inclusive valid column index range is 0:(num_columns - 1)."
				);
			}
		}

		/// <summary>
		/// <para> Accesses the theoretical column at the provided ColumnIndex_ within this Matrix. </para>
		/// <para> If this Matrix is column-major and the index is contained: This will be a direct reference to the specified column. </para>
		/// <para> 
		///		If this Matrix is not column-major and the index is contained: 
		///		This will be an EmuMath Vector of references to elements at respective points within the specified column. 
		/// </para>
		/// <para> If the index is not contained: This will be an implied-zero column for this Matrix type. </para>
		/// </summary>
		/// <returns>EmuMath Vector referencing the specified column within this Matrix, or an implied-zero column if the index is not contained.</returns>
		template<std::size_t ColumnIndex_>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_column_theoretical_get_result<ColumnIndex_, this_type&>::type ColumnAtTheoretical()
		{
			return EmuMath::Helpers::matrix_get_column_theoretical<ColumnIndex_>(*this);
		}

		template<std::size_t ColumnIndex_>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_column_theoretical_get_result<ColumnIndex_, const this_type&>::type ColumnAtTheoretical() const
		{
			return EmuMath::Helpers::matrix_get_column_theoretical<ColumnIndex_>(*this);
		}

		/// <summary>
		/// <para> Accesses the row at the provided RowIndex_ within this Matrix. </para>
		/// <para> If this Matrix is column-major: This will be an EmuMath Vector of references to elements at respective points within the specified row. </para>
		/// <para> If this Matrix is not column-major: This will be a direct reference to the specified row. </para>
		/// </summary>
		/// <returns>EmuMath Vector referencing the specified row within this Matrix.</returns>
		template<std::size_t RowIndex_>
		[[nodiscard]] constexpr inline row_get_ref_type RowAt()
		{
			if constexpr (RowIndex_ < num_rows)
			{
				if constexpr (is_column_major)
				{
					return _make_non_major_vector<RowIndex_, row_get_ref_type>(std::make_index_sequence<num_columns>());
				}
				else
				{
					return _data.template at<RowIndex_>();
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, RowIndex_>(),
					"Attempted to access a row within an EmuMath Matrix, but the provided RowIndex_ is invalid. The inclusive valid row index range is 0:(num_rows - 1)."
				);
			}
		}

		template<std::size_t RowIndex_>
		[[nodiscard]] constexpr inline row_get_const_ref_type RowAt() const
		{
			if constexpr (RowIndex_ < num_rows)
			{
				if constexpr (is_column_major)
				{
					return _make_non_major_vector<RowIndex_, row_get_const_ref_type>(std::make_index_sequence<num_columns>());
				}
				else
				{
					return _data.template at<RowIndex_>();
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, RowIndex_>(),
					"Attempted to access a row within an EmuMath Matrix, but the provided RowIndex_ is invalid. The inclusive valid row index range is 0:(num_rows - 1)."
				);
			}
		}

		/// <summary>
		/// <para> Accesses the theoretical row at the provided RowIndex_ within this Matrix. </para>
		/// <para> 
		///		If this Matrix is column-major and the index is contained: 
		///		This will be an EmuMath Vector of references to elements at respective points within the specified row. 
		/// </para>
		/// <para> If this Matrix is not column-major and the index is contained: This will be a direct reference to the specified row. </para>
		/// <para> If the index is not contained: This will be an implied-zero row for this Matrix type. </para>
		/// </summary>
		/// <returns>EmuMath Vector referencing the specified row within this Matrix, or an implied-zero row if the index is not contained.</returns>
		template<std::size_t RowIndex_>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_row_theoretical_get_result<RowIndex_, this_type&>::type RowAtTheoretical()
		{
			return EmuMath::Helpers::matrix_get_row_theoretical<RowIndex_>(*this);
		}

		template<std::size_t RowIndex_>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_row_theoretical_get_result<RowIndex_, const this_type&>::type RowAtTheoretical() const
		{
			return EmuMath::Helpers::matrix_get_row_theoretical<RowIndex_>(*this);
		}

		/// <summary>
		/// <para> Accesses the major element at the provided MajorIndex_ within this Matrix. </para>
		/// <para> If this Matrix is column-major: This will be a reference to the column at the specified MajorIndex_. </para>
		/// <para> If this Matrix is not column-major: This will be a reference to the row at the specified MajorIndex_. </para>
		/// </summary>
		/// <returns>EmuMath Vector referencing the specified major element within this Matrix.</returns>
		template<std::size_t MajorIndex_>
		[[nodiscard]] constexpr inline major_get_ref_type MajorAt()
		{
			if constexpr (MajorIndex_ < num_major_elements)
			{
				return _data.template at<MajorIndex_>();
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, MajorIndex_>(),
					"Attempted to access a major element within an EmuMath Matrix, but the provided MajorIndex_ is invalid. The inclusive valid major index range is 0:(num_major_elements - 1)."
				);
			}
		}

		template<std::size_t MajorIndex_>
		[[nodiscard]] constexpr inline major_get_const_ref_type MajorAt() const
		{
			// Although currently implementation is identical, this ignores DRY standards in case major_get_const_ref_type is not just const-qualified major_get_ref_type.
			if constexpr (MajorIndex_ < num_major_elements)
			{
				return _data.template at<MajorIndex_>();
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, MajorIndex_>(),
					"Attempted to access a major element within an EmuMath Matrix, but the provided MajorIndex_ is invalid. The inclusive valid major index range is 0:(num_major_elements - 1)."
				);
			}
		}

		/// <summary>
		/// <para> Accesses the theoretical major element at the provided MajorIndex_ within this Matrix. </para>
		/// <para> If this Matrix is column-major and the index is contained: This will be a reference to the column at the specified MajorIndex_. </para>
		/// <para> If this Matrix is not column-major and the index is contained: This will be a reference to the row at the specified MajorIndex_. </para>
		/// <para> If this Matrix is column-major and the index is not contained: This will be an implied-zero column for this Matrix type. </para>
		/// <para> If this Matrix is not column-major and the index is not contained: This will be an implied-zero row for this Matrix type. </para>
		/// </summary>
		/// <returns>EmuMath Vector referencing the specified major element within the passed matrix_, or an implied-zero non-major element if it is not contained.</returns>
		template<std::size_t MajorIndex_>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_major_theoretical_get_result<MajorIndex_, this_type&>::type MajorAtTheoretical()
		{
			return EmuMath::Helpers::matrix_get_major_theoretical<MajorIndex_>(*this);
		}

		template<std::size_t MajorIndex_>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_major_theoretical_get_result<MajorIndex_, const this_type&>::type MajorAtTheoretical() const
		{
			return EmuMath::Helpers::matrix_get_major_theoretical<MajorIndex_>(*this);
		}

		/// <summary>
		/// <para> Accesses the major eement at the provided MajorIndex_ within this Matrix. </para>
		/// <para> If this Matrix is column-major: This will be an EmuMath Vector of references to respective elements in the row at the specified MajorIndex_. </para>
		/// <para> If this Matrix is not column-major: This will be an EmuMath Vector of references to respective elements in the column at the specified MajorIndex_. </para>
		/// </summary>
		/// <returns>EmuMath Vector of references to elements within the specified non-major element within this Matrix.</returns>
		template<std::size_t NonMajorIndex_>
		[[nodiscard]] constexpr inline non_major_get_ref_type NonMajorAt()
		{
			if constexpr (NonMajorIndex_ < num_non_major_elements)
			{
				return _make_non_major_vector<NonMajorIndex_, non_major_get_ref_type>(std::make_index_sequence<num_major_elements>());
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, NonMajorIndex_>(),
					"Attempted to access a non-major element within an EmuMath Matrix, but the provided NonMajorIndex_ is invalid. The inclusive valid non-major index range is 0:(num_non_major_elements - 1)."
				);
			}
		}

		template<std::size_t NonMajorIndex_>
		[[nodiscard]] constexpr inline non_major_get_const_ref_type NonMajorAt() const
		{
			if constexpr (NonMajorIndex_ < num_non_major_elements)
			{
				return _make_non_major_vector<NonMajorIndex_, non_major_get_const_ref_type>(std::make_index_sequence<num_major_elements>());
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, NonMajorIndex_>(),
					"Attempted to access a non-major element within an EmuMath Matrix, but the provided NonMajorIndex_ is invalid. The inclusive valid non-major index range is 0:(num_non_major_elements - 1)."
				);
			}
		}

		/// <summary>
		/// <para> Accesses the theoretical non-major element at the provided NonMajorIndex_ within this Matrix. </para>
		/// <para> If this Matrix is column-major and the index is contained: This will be a reference to the row at the specified MajorIndex_. </para>
		/// <para> If this Matrix is not column-major and the index is contained: This will be a reference to the column at the specified MajorIndex_. </para>
		/// <para> If this Matrix is column-major and the index is not contained: This will be an implied-zero row for this Matrix type. </para>
		/// <para> If this Matrix is not column-major and the index is not contained: This will be an implied-zero column for this Matrix type. </para>
		/// </summary>
		/// <returns>
		///		EmuMath Vector of references to elements within the specified non-major element within this Matrix, 
		///		or an implied-zero non-major element if it is not contained.
		/// </returns>
		template<std::size_t NonMajorIndex_>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_non_major_theoretical_get_result<NonMajorIndex_, this_type&>::type NonMajorAtTheoretical()
		{
			return EmuMath::Helpers::matrix_get_non_major_theoretical<NonMajorIndex_>(*this);
		}

		template<std::size_t NonMajorIndex_>
		[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_non_major_theoretical_get_result<NonMajorIndex_, const this_type&>::type NonMajorAtTheoretical() const
		{
			return EmuMath::Helpers::matrix_get_non_major_theoretical<NonMajorIndex_>(*this);
		}

		/// <summary>
		/// <para>
		///		Outputs an EmuMath Vector representing the main-diagonal of the this Matrix, 
		///		starting from the provided Offset_ for as many indices as the output Vector holds.
		/// </para>
		/// <para> If no OutSize_ is provided, the output size will default to that of this Matrix's smallest axis. </para>
		/// <para> Offset_: Inclusive index from which to start reading main diagonal elements. This is used as both a column index and a row index. Defaults to 0. </para>
		/// </summary>
		/// <returns>EmuMath Vector representing the main diagonal within this Matrix for as many elements as it contains, and starting from the provided Offset_.</returns>
		template<std::size_t OutSize_, typename OutT_, std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> MainDiagonal()
		{
			return EmuMath::Helpers::matrix_get_main_diagonal<OutSize_, OutT_, Offset_>(*this);
		}

		template<std::size_t OutSize_, std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, value_type_uq> MainDiagonal()
		{
			return EmuMath::Helpers::matrix_get_main_diagonal<OutSize_, value_type_uq, Offset_>(*this);
		}

		template<typename OutT_ = value_type_uq, std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<EmuMath::TMP::matrix_smallest_axis_v<this_type>, OutT_> MainDiagonal()
		{
			return EmuMath::Helpers::matrix_get_main_diagonal<EmuMath::TMP::matrix_smallest_axis_v<this_type>, OutT_, Offset_>(*this);
		}

		/// <summary>
		/// <para>
		///		Outputs an EmuMath Vector representing the main-diagonal of the this Matrix, 
		///		starting from the provided Offset_ for as many indices as the output Vector holds.
		/// </para>
		/// <para> If no OutSize_ is provided, the output size will default to that of this Matrix's smallest axis. </para>
		/// <para> Offset_: Inclusive index from which to start reading main diagonal elements. This is used as both a column index and a row index. Defaults to 0. </para>
		/// </summary>
		/// <returns>EmuMath Vector representing the main diagonal within this Matrix for as many elements as it contains, and starting from the provided Offset_.</returns>
		template<std::size_t OutSize_, typename OutT_, std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> MainDiagonal() const
		{
			return EmuMath::Helpers::matrix_get_main_diagonal<OutSize_, OutT_, Offset_>(*this);
		}

		template<std::size_t OutSize_, std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, value_type_uq> MainDiagonal() const
		{
			return EmuMath::Helpers::matrix_get_main_diagonal<OutSize_, value_type_uq, Offset_>(*this);
		}

		template<typename OutT_ = value_type_uq, std::size_t Offset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<EmuMath::TMP::matrix_smallest_axis_v<this_type>, OutT_> MainDiagonal() const
		{
			return EmuMath::Helpers::matrix_get_main_diagonal<EmuMath::TMP::matrix_smallest_axis_v<this_type>, OutT_, Offset_>(*this);
		}

		/// <summary>
		/// <para> Outputs an EmuMath Vector copy of the column at the provided theoretical index within this Matrix. </para>
		/// <para> ReadOffset_: Inclusive index at which to start copying from the specified column. Defaults to 0. </para>
		/// </summary>
		/// <returns>EmuMath Vector constructed from this Matrix's column at the provided index, copying said column from the provided ReadOffset_.</returns>
		template<std::size_t ColumnIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, std::size_t ReadOffset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> ColumnCopy()
		{
			if constexpr (EmuMath::Helpers::vector_cast_is_valid<column_get_ref_type, OutSize_, OutT_, ReadOffset_>())
			{
				return EmuMath::Helpers::vector_cast<OutSize_, OutT_, ReadOffset_>(ColumnAtTheoretical<ColumnIndex_>());
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutT_>(),
					"Attempted to retrieve a copy of a column within an EmuMath Matrix, but the provided output Vector type could not be cast to from the provided offset within one of the Matrix's non-const columns."
				);
			}
		}

		template<std::size_t ColumnIndex_, typename OutT_ = value_type_uq, std::size_t ReadOffset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<num_rows, OutT_> ColumnCopy()
		{
			return ColumnCopy<ColumnIndex_, num_rows, OutT_, ReadOffset_>();
		}

		template<std::size_t ColumnIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, std::size_t ReadOffset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> ColumnCopy() const
		{
			if constexpr (EmuMath::Helpers::vector_cast_is_valid<column_get_const_ref_type, OutSize_, OutT_, ReadOffset_>())
			{
				return EmuMath::Helpers::vector_cast<OutSize_, OutT_, ReadOffset_>(ColumnAtTheoretical<ColumnIndex_>());
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutT_>(),
					"Attempted to retrieve a copy of a column within an EmuMath Matrix, but the provided output Vector type could not be cast to from the provided offset within one of the Matrix's const columns."
				);
			}
		}

		template<std::size_t ColumnIndex_, typename OutT_ = value_type_uq, std::size_t ReadOffset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<num_rows, OutT_> ColumnCopy() const
		{
			return ColumnCopy<ColumnIndex_, num_rows, OutT_, ReadOffset_>();
		}

		/// <summary>
		/// <para> Outputs an EmuMath Vector copy of the row at the provided theoretical index within this Matrix. </para>
		/// <para> ReadOffset_: Inclusive index at which to start copying from the specified row. Defaults to 0. </para>
		/// </summary>
		/// <returns>EmuMath Vector constructed from this Matrix's row at the provided index, copying said row from the provided ReadOffset_.</returns>
		template<std::size_t RowIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, std::size_t ReadOffset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> RowCopy()
		{
			if constexpr (EmuMath::Helpers::vector_cast_is_valid<row_get_ref_type, OutSize_, OutT_, ReadOffset_>())
			{
				return EmuMath::Helpers::vector_cast<OutSize_, OutT_, ReadOffset_>(RowAtTheoretical<RowIndex_>());
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutT_>(),
					"Attempted to retrieve a copy of a row within an EmuMath Matrix, but the provided output Vector type could not be cast to from the provided offset within one of the Matrix's non-const rows."
				);
			}
		}

		template<std::size_t RowIndex_, typename OutT_ = value_type_uq, std::size_t ReadOffset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<num_columns, OutT_> RowCopy()
		{
			return RowCopy<RowIndex_, num_columns, OutT_, ReadOffset_>();
		}

		template<std::size_t RowIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, std::size_t ReadOffset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> RowCopy() const
		{
			if constexpr (EmuMath::Helpers::vector_cast_is_valid<row_get_const_ref_type, OutSize_, OutT_, ReadOffset_>())
			{
				return EmuMath::Helpers::vector_cast<OutSize_, OutT_, ReadOffset_>(RowAtTheoretical<RowIndex_>());
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutT_>(),
					"Attempted to retrieve a copy of a row within an EmuMath Matrix, but the provided output Vector type could not be cast to from the provided offset within one of the Matrix's const rows."
				);
			}
		}

		template<std::size_t RowIndex_, typename OutT_ = value_type_uq, std::size_t ReadOffset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<num_columns, OutT_> RowCopy() const
		{
			return RowCopy<RowIndex_, num_columns, OutT_, ReadOffset_>();
		}

		/// <summary>
		/// <para> Outputs an EmuMath Vector copy of the major element at the provided theoretical index within this Matrix. </para>
		/// <para> ReadOffset_: Inclusive index at which to start copying from the specified major element. Defaults to 0. </para>
		/// <para> If this Matrix is column major: Results should be expected to be identical to ColumnCopy. </para>
		/// <para> If this Matrix is not column major: Results should be expected to be identical to RowCopy. </para>
		/// </summary>
		/// <returns>EmuMath Vector constructed from this Matrix's major element at the provided index, copying said element from the provided ReadOffset_.</returns>
		template<std::size_t MajorIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, std::size_t ReadOffset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> MajorCopy()
		{
			if constexpr (EmuMath::Helpers::vector_cast_is_valid<major_get_ref_type, OutSize_, OutT_, ReadOffset_>())
			{
				return EmuMath::Helpers::vector_cast<OutSize_, OutT_, ReadOffset_>(MajorAtTheoretical<MajorIndex_>());
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutT_>(),
					"Attempted to retrieve a copy of a major element within an EmuMath Matrix, but the provided output Vector type could not be cast to from the provided offset within one of the Matrix's non-const major elements."
				);
			}
		}

		template<std::size_t MajorIndex_, typename OutT_ = value_type_uq, std::size_t ReadOffset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<num_non_major_elements, OutT_> MajorCopy()
		{
			return MajorCopy<MajorIndex_, num_non_major_elements, OutT_, ReadOffset_>();
		}

		template<std::size_t MajorIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, std::size_t ReadOffset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> MajorCopy() const
		{
			if constexpr (EmuMath::Helpers::vector_cast_is_valid<major_get_const_ref_type, OutSize_, OutT_, ReadOffset_>())
			{
				return EmuMath::Helpers::vector_cast<OutSize_, OutT_, ReadOffset_>(MajorAtTheoretical<MajorIndex_>());
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutT_>(),
					"Attempted to retrieve a copy of a major element within an EmuMath Matrix, but the provided output Vector type could not be cast to from the provided offset within one of the Matrix's const major elements."
				);
			}
		}

		template<std::size_t MajorIndex_, typename OutT_ = value_type_uq, std::size_t ReadOffset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<num_non_major_elements, OutT_> MajorCopy() const
		{
			return MajorCopy<MajorIndex_, num_non_major_elements, OutT_, ReadOffset_>();
		}

		/// <summary>
		/// <para> Outputs an EmuMath Vector copy of the non-major element at the provided theoretical index within this Matrix. </para>
		/// <para> ReadOffset_: Inclusive index at which to start copying from the specified non-major element. Defaults to 0. </para>
		/// <para> If this Matrix is column major: Results should be expected to be identical to RowCopy. </para>
		/// <para> If this Matrix is not column major: Results should be expected to be identical to ColumnCopy. </para>
		/// </summary>
		/// <returns>EmuMath Vector constructed from this Matrix's non-major element at the provided index, copying said element from the provided ReadOffset_.</returns>
		template<std::size_t NonMajorIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, std::size_t ReadOffset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> NonMajorCopy()
		{
			if constexpr (EmuMath::Helpers::vector_cast_is_valid<non_major_get_ref_type, OutSize_, OutT_, ReadOffset_>())
			{
				return EmuMath::Helpers::vector_cast<OutSize_, OutT_, ReadOffset_>(NonMajorAtTheoretical<NonMajorIndex_>());
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutT_>(),
					"Attempted to retrieve a copy of a non-major element within an EmuMath Matrix, but the provided output Vector type could not be cast to from the provided offset within one of the Matrix's non-const non-major elements."
				);
			}
		}

		template<std::size_t NonMajorIndex_, typename OutT_ = value_type_uq, std::size_t ReadOffset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<num_major_elements, OutT_> NonMajorCopy()
		{
			return NonMajorCopy<NonMajorIndex_, num_major_elements, OutT_, ReadOffset_>();
		}

		template<std::size_t NonMajorIndex_, std::size_t OutSize_, typename OutT_ = value_type_uq, std::size_t ReadOffset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> NonMajorCopy() const
		{
			if constexpr (EmuMath::Helpers::vector_cast_is_valid<non_major_get_const_ref_type, OutSize_, OutT_, ReadOffset_>())
			{
				return EmuMath::Helpers::vector_cast<OutSize_, OutT_, ReadOffset_>(NonMajorAtTheoretical<NonMajorIndex_>());
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutT_>(),
					"Attempted to retrieve a copy of a non-major element within an EmuMath Matrix, but the provided output Vector type could not be cast to from the provided offset within one of the Matrix's const non-major elements."
				);
			}
		}

		template<std::size_t NonMajorIndex_, typename OutT_ = value_type_uq, std::size_t ReadOffset_ = 0>
		[[nodiscard]] constexpr inline EmuMath::Vector<num_major_elements, OutT_> NonMajorCopy() const
		{
			return NonMajorCopy<NonMajorIndex_, num_major_elements, OutT_, ReadOffset_>();
		}
#pragma endregion

#pragma region ASSIGNMENT_OPERATORS
	public:
		template
		<
			std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
			typename = std::enable_if_t<EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&>()>
		>
		constexpr inline this_type& operator=(EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& to_copy_)
		{
			EmuMath::Helpers::matrix_copy(*this, to_copy_);
			return *this;
		}

		template
		<
			std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
			typename = std::enable_if_t<EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&>()>
		>
		constexpr inline this_type& operator=(const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& to_copy_)
		{
			EmuMath::Helpers::matrix_copy(*this, to_copy_);
			return *this;
		}

		template
		<
			std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
			typename = std::enable_if_t<EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>()>
		>
		constexpr inline this_type& operator=(EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&& to_move_copy_)
		{
			EmuMath::Helpers::matrix_copy
			(
				*this,
				std::forward<EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>(to_move_copy_)
			);
			return *this;
		}

		template
		<
			std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
			typename = std::enable_if_t<EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>()>
		>
		constexpr inline this_type& operator=(const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&& to_move_copy_)
		{
			EmuMath::Helpers::matrix_copy
			(
				*this,
				std::forward<EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>(to_move_copy_)
			);
			return *this;
		}
#pragma endregion

#pragma region COPY_FUNCS
	public:
		/// <summary>
		/// <para> Copies the theoretical indices of the provided input Matrix to respective indices within this Matrix. </para>
		/// </summary>
		/// <param name="to_copy_">: EmuMath Matrix to copy to this Matrix.</param>
		template
		<
			std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
			typename = std::enable_if_t<EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&>()>
		>
		constexpr inline void Copy(EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& to_copy_)
		{
			EmuMath::Helpers::matrix_copy(*this, to_copy_);
		}

		template
		<
			std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
			typename = std::enable_if_t<EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&>()>
		>
		constexpr inline void Copy(const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& to_copy_)
		{
			EmuMath::Helpers::matrix_copy(*this, to_copy_);
		}

		template
		<
			std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
			typename = std::enable_if_t<EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>()>
		>
		constexpr inline void Copy(EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&& to_move_copy_)
		{
			EmuMath::Helpers::matrix_copy
			(
				*this,
				std::forward<EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>(to_move_copy_)
			);
		}

		template
		<
			std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
			typename = std::enable_if_t<EmuMath::Helpers::matrix_assign_copy_is_valid<this_type, const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>()>
		>
		constexpr inline void Copy(const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>&& to_move_copy_)
		{
			EmuMath::Helpers::matrix_copy
			(
				*this,
				std::forward<EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>>(to_move_copy_)
			);
		}
#pragma endregion

#pragma region STREAM_FUNCS
	public:
		/// <summary>
		/// <para> Appends this Matrix to the provided stream. </para>
		/// <para> Elements will be appended as a series of lines containing columns or lines, depending on AppendAsRows_. </para>
		/// <para> AppendAsRows_: If true, each appended line will be a row of this Matrix. Otherwise, each appended line will be a column of this Matrix. Defaults to true. </para>
		/// <para> NOTE: Appending as rows is recommended as this gives the best visual of how matrices are interpreted by EmuMath. </para>
		/// </summary>
		/// <param name="str_">Stream to append this Matrix to.</param>
		/// <returns>Reference to the provided stream.</returns>
		template<bool AppendAsRows_ = true>
		constexpr inline std::ostream& AppendToStream(std::ostream& str_) const
		{
			return EmuMath::Helpers::matrix_append_to_stream<AppendAsRows_>(str_, *this);
		}

		template<bool AppendAsRows_ = true>
		constexpr inline std::wostream& AppendToStream(std::wostream& wide_str_) const
		{
			return EmuMath::Helpers::matrix_append_to_stream<AppendAsRows_>(wide_str_, *this);
		}
#pragma endregion

	private:
		matrix_vector_type _data;

		template<std::size_t NonMajorIndex_, class Out_, std::size_t...MajorIndices_>
		[[nodiscard]] constexpr inline Out_ _make_non_major_vector(std::index_sequence<MajorIndices_...> major_indices_)
		{
			if constexpr (is_column_major)
			{
				return Out_(this->template at<MajorIndices_, NonMajorIndex_>()...);
			}
			else
			{
				return Out_(this->template at<NonMajorIndex_, MajorIndices_>()...);
			}
		}

		template<std::size_t NonMajorIndex_, class Out_, std::size_t...MajorIndices_>
		[[nodiscard]] constexpr inline Out_ _make_non_major_vector(std::index_sequence<MajorIndices_...> major_indices_) const
		{
			if constexpr (is_column_major)
			{
				return Out_(this->template at<MajorIndices_, NonMajorIndex_>()...);
			}
			else
			{
				return Out_(this->template at<NonMajorIndex_, MajorIndices_>()...);
			}
		}

		template<std::size_t MajorIndex_, typename...Args_, std::size_t...NonMajorIndices_>
		[[nodiscard]] static constexpr inline typename matrix_vector_type::stored_type _make_major_index
		(
			std::index_sequence<NonMajorIndices_...> non_major_indices_,
			std::tuple<Args_...>& tuple_of_args_
		)
		{
			constexpr std::size_t major_offset_ = MajorIndex_ * num_non_major_elements;
			return typename matrix_vector_type::stored_type
			(
				std::get<major_offset_ + NonMajorIndices_>(tuple_of_args_)...
			);
		}

		template<typename...Args_, std::size_t...MajorIndices_>
		[[nodiscard]] static constexpr inline matrix_vector_type _make_data_from_major_vectors(std::index_sequence<MajorIndices_...> major_indices_, Args_&&...args_)
		{
			return matrix_vector_type(std::forward<Args_>(args_)...);
		}

		template<typename...Args_, std::size_t...MajorIndices_>
		[[nodiscard]] static constexpr inline matrix_vector_type _make_data_from_multiple_scalar_args(std::index_sequence<MajorIndices_...> major_indices_, Args_&&...args_)
		{
			auto tuple_of_args_ = std::forward_as_tuple(std::forward<Args_>(args_)...);
			return matrix_vector_type
			(
				_make_major_index<MajorIndices_>
				(
					std::make_index_sequence<num_non_major_elements>(),
					tuple_of_args_
				)...
			);
		}

		template<typename Arg_>
		[[nodiscard]] static constexpr inline matrix_vector_type _make_data_from_single_scalar_arg(Arg_&& arg_)
		{
			return matrix_vector_type(std::forward<Arg_>(arg_));
		}

		template<typename...Args_, std::size_t...MajorIndices_>
		[[nodiscard]] static constexpr inline matrix_vector_type _make_data(std::index_sequence<MajorIndices_...> major_indices_, Args_&&...args_)
		{
			if constexpr (is_constructible_from_major_vectors<Args_...>())
			{
				return _make_data_from_major_vectors(major_indices_, std::forward<Args_>(args_)...);
			}
			else if constexpr (is_constructible_with_scalar_args<Args_...>())
			{
				return _make_data_from_multiple_scalar_args(major_indices_, std::forward<Args_>(args_)...);
			}
			else if constexpr (is_constructible_with_single_scalar_arg<Args_...>())
			{
				return _make_data_from_single_scalar_arg(std::forward<Args_>(args_)...);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Args_...>(),
					"Attempted to construct the data Vector of an EmuMath Matrix, but the provided Args_ are incompatible for construct the matrix_vector_type."
				);
			}
		}
	};
}

#endif
