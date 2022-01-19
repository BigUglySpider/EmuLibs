#ifndef EMU_MATH_MATRIX_UNDERLYING_COPY_H_INC_
#define EMU_MATH_MATRIX_UNDERLYING_COPY_H_INC_ 1

#include "_matrix_tmp.h"
#include "_matrix_underlying_get.h"

namespace EmuMath::Helpers::_matrix_underlying
{
	template<class OutMatrix_, class InMatrix_, bool DoAssertions_>
	struct _matrix_compatible_contained_ref_check
	{
	private:
		[[nodiscard]] static constexpr inline bool _get()
		{
			using out_uq = EmuCore::TMP::remove_ref_cv_t<OutMatrix_>;
			using in_uq = EmuCore::TMP::remove_ref_cv_t<InMatrix_>;
			if constexpr (out_uq::contains_ref)
			{
				if constexpr (std::is_lvalue_reference_v<InMatrix_>)
				{
					// Lvalue-ref, so we assume we're not working with temp input
					if constexpr (out_uq::contains_non_const_ref)
					{
						// Check for const-compatibility
						if constexpr (!std::is_const_v<InMatrix_>)
						{
							if constexpr (!std::is_const_v<typename in_uq::value_type>)
							{
								return true;
							}
							else
							{
								static_assert(!DoAssertions_, "Invalid ref-compatibility between two EmuMath Matrices: The output Matrix contains non-const references, but the input Matrix (lvalue reference) has a const value_type.");
								return false;
							}
						}
						else
						{
							static_assert(!DoAssertions_, "Invalid ref-compatibility between two EmuMath Matrices: The output Matrix contains non-const references, but the input Matrix (lvalue reference) is const-qualified.");
							return false;
						}
					}
					else
					{
						// No const-safety checks needed
						return true;
					}
				}
				else if constexpr (in_uq::contains_ref)
				{
					// Rvalue-ref or temp value, so we assume we're working with temp input
					// --- Temp input matrix will be invalid due to dangling references unless it contains references itself, thus we have this else-if branch
					if constexpr (out_uq::contains_non_const_ref)
					{
						if constexpr(std::is_const_v<in_uq>)
						{
							if constexpr (in_uq::contains_non_const_ref)
							{
								return true;
							}
							else
							{
								static_assert(!DoAssertions_, "Invalid ref-compatibility between two EmuMath Matrices: The output Matrix contains non-const references, but the input Matrix (value or rvalue-reference) contains const references.");
								return false;
							}
						}
						else
						{
							static_assert(!DoAssertions_, "Invalid ref-compatibility between two EmuMath Matrices: The output Matrix contains non-const references, but the input Matrix (value or rvalue-reference) is const-qualified.");
							return false;
						}
					}
					else
					{
						// No const-safety checks needed
						return true;
					}
				}
				else
				{
					static_assert(!DoAssertions_, "Invalid ref compatibility between two EmuMath Matrices: The output Matrix contains references, but the input Matrix is a value or rvalue reference which suggests that it is temporary, and does not contain references. This is deemed as incompatible to prevent dangling references.");
					return false;
				}
			}
			else
			{
				// No need for compatible references since we're outputting values
				return true;
			}
		}

	public:
		static constexpr bool value = _get();
	};

	template<class OutMatrix_, class InMatrix_, bool DoAssertions_, std::size_t ColumnIndex_, std::size_t RowIndex_>
	[[nodiscard]] constexpr inline bool _matrix_create_from_matrix_index_is_valid()
	{
		using in_declval = decltype(std::declval<InMatrix_>());
		using get_return_type = decltype
		(
			_matrix_get_theoretical<ColumnIndex_, RowIndex_>
			(
				EmuCore::TMP::lval_ref_cast<in_declval>(std::declval<InMatrix_>())
			)
		);
		using out_stored_type = typename OutMatrix_::stored_type;
		if constexpr (std::is_lvalue_reference_v<InMatrix_>)
		{
			// Copy only
			if constexpr (std::is_constructible_v<out_stored_type, get_return_type> || EmuCore::TMP::is_static_castable_v<get_return_type, out_stored_type>)
			{
				return true;
			}
			else
			{
				static_assert(!DoAssertions_, "Attempted to copy an item from an index of an EmuMath Matrix to the stored_type of another EmuMath Matrix, but the desired output type could not be constructed or static_cast to from the result of getting said index from the Matrix.");
				return false;
			}
		}
		else
		{
			// Move-allowed, fallback to copy
			if constexpr (_matrix_index_is_contained<ColumnIndex_, RowIndex_, InMatrix_>())
			{
				// Move-or-copy
				if constexpr (_matrix_compatible_contained_ref_check<OutMatrix_, InMatrix_, DoAssertions_>::value)
				{
					using move_result = decltype
					(
						std::move
						(
							_matrix_get_theoretical<ColumnIndex_, RowIndex_>
							(
								EmuCore::TMP::lval_ref_cast<in_declval>(std::declval<InMatrix_>())
							)
						)
					);
					constexpr bool may_move_ = std::is_constructible_v<out_stored_type, move_result> || EmuCore::TMP::is_static_castable_v<move_result, out_stored_type>;
					constexpr bool may_copy_ = std::is_constructible_v<out_stored_type, get_return_type> || EmuCore::TMP::is_static_castable_v<get_return_type, out_stored_type>;

					// Do not allow moves for reference-containing outputs
					if constexpr ((may_move_ && !OutMatrix_::contains_ref) || may_copy_)
					{
						return true;
					}
					else
					{
						static_assert(!DoAssertions_, "Attempted to copy-or-move an item from an index of an EmuMath Matrix to the stored_type of another EmuMath Matrix, but the stored_type of the output Matrix cannot be constructed from a std::move or direct copy of the result of getting at least one of the provided indices.");
						return false;
					}
				}
				else
				{
					static_assert(!DoAssertions_, "Attempted to copy-or-move an item from an index of an EmuMath Matrix to the stored_type of another EmuMath Matrix, but the desired output Matrix has a reference incompatibility with the input Matrix.");
					return false;
				}
			}
			else
			{
				// Theoretical, therefore return is value type, so no manual std::move and no reference output
				if constexpr (!OutMatrix_::contains_ref)
				{
					if constexpr (std::is_constructible_v<out_stored_type, get_return_type> || EmuCore::TMP::is_static_castable_v<get_return_type, out_stored_type>)
					{
						return true;
					}
					else
					{
						static_assert(!DoAssertions_, "Attempted to copy an item from an index of an EmuMath Matrix to the stored_type of another EmuMath Matrix, but at least one accessed index is non-contained and the output Matrix's stored_type cannot be constructed or static_cast to from the result of getting a non-contained index of the input Matrix.");
						return false;
					}
				}
				else
				{
					static_assert(!DoAssertions_, "Attempted to copy an item from an index of an EmuMath Matrix to the stored_type of a reference-containing EmuMath Matrix, but at least one accessed index is not-contained within the input Matrix, and would result in a dangling reference.");
					return false;
				}
			}
		}
	}

	template<typename...Args_>
	[[nodiscard]] constexpr inline bool _halp_me(Args_...args_)
	{
		return (... && args_);
	}

	template<class OutMatrix_, class InMatrix_, bool DoAssertions_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	[[nodiscard]] constexpr inline bool _matrix_create_from_matrix_is_valid
	(
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_
	)
	{
		constexpr bool is_valid_ = EmuCore::TMP::variadic_and_v
		<
			_matrix_create_from_matrix_index_is_valid<OutMatrix_, InMatrix_, DoAssertions_, ColumnIndices_, RowIndices_>()...
		>;
		if constexpr (is_valid_)
		{
			return true;
		}
		else
		{
			static_assert(!DoAssertions_, "Matrix validity check for creation from another Matrix type has failed for at least one of the provided indices.");
			return false;
		}
	}

	template<class OutMatrix_, class InMatrix_, std::size_t ColumnIndex_, std::size_t RowIndex_>
	[[nodiscard]] constexpr inline typename OutMatrix_::stored_type _matrix_create_out_from_index(InMatrix_&& in_matrix_)
	{
		using get_return_type = decltype(_matrix_get_theoretical<ColumnIndex_, RowIndex_>(EmuCore::TMP::lval_ref_cast<InMatrix_>(in_matrix_)));
		using out_stored_type = typename OutMatrix_::stored_type;
		if constexpr (_matrix_create_from_matrix_index_is_valid<OutMatrix_, InMatrix_, true, ColumnIndex_, RowIndex_>())
		{
			constexpr bool move_allowed_ = EmuCore::TMP::variadic_and_v
			<
				_matrix_index_is_contained<ColumnIndex_, RowIndex_, InMatrix_>(),
				!OutMatrix_::contains_ref,
				!std::is_lvalue_reference_v<InMatrix_>,
				_matrix_compatible_contained_ref_check<OutMatrix_, InMatrix_, false>::value
			>;

			if constexpr (move_allowed_)
			{
				// Move allowed, fallback to copy
				using move_result = decltype(std::move(_matrix_get_theoretical<ColumnIndex_, RowIndex_>(EmuCore::TMP::lval_ref_cast<InMatrix_>(std::declval<InMatrix_>()))));
				if constexpr (std::is_constructible_v<out_stored_type, move_result>)
				{
					get_return_type intermediate_ = _matrix_get_theoretical<ColumnIndex_, RowIndex_>(EmuCore::TMP::lval_ref_cast<InMatrix_>(in_matrix_));
					return out_stored_type(std::move(intermediate_));
				}
				else if constexpr (EmuCore::TMP::is_static_castable_v<move_result, out_stored_type>)
				{
					get_return_type intermediate_ = _matrix_get_theoretical<ColumnIndex_, RowIndex_>(EmuCore::TMP::lval_ref_cast<InMatrix_>(in_matrix_));
					return static_cast<out_stored_type>(std::move(intermediate_));
				}
				else if constexpr (std::is_constructible_v<out_stored_type, get_return_type>)
				{
					return out_stored_type
					(
						_matrix_get_theoretical<ColumnIndex_, RowIndex_>(EmuCore::TMP::lval_ref_cast<InMatrix_>(in_matrix_))
					);
				}
				else if constexpr (EmuCore::TMP::is_static_castable_v<get_return_type, out_stored_type>)
				{
					return static_cast<out_stored_type>
					(
						_matrix_get_theoretical<ColumnIndex_, RowIndex_>(EmuCore::TMP::lval_ref_cast<InMatrix_>(in_matrix_))
					);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutMatrix_>(),
						"Attempted to copy-or-move an index from an EmuMath Matrix into a new EmuMath Matrix, but neither the type resulting from moving a get result nor the get result itself could be used to create the required output type."
					);
				}
			}
			else
			{
				// Copy only
				if constexpr (std::is_constructible_v<out_stored_type, get_return_type>)
				{
					return out_stored_type
					(
						_matrix_get_theoretical<ColumnIndex_, RowIndex_>(EmuCore::TMP::lval_ref_cast<InMatrix_>(in_matrix_))
					);
				}
				else if constexpr (EmuCore::TMP::is_static_castable_v<get_return_type, out_stored_type>)
				{
					return static_cast<out_stored_type>
					(
						_matrix_get_theoretical<ColumnIndex_, RowIndex_>(EmuCore::TMP::lval_ref_cast<InMatrix_>(in_matrix_))
					);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutMatrix_>(),
						"Attempted to copy an index from an EmuMath Matrix into a new EmuMath Matrix, but the type resulting from a get of an index could be used to create the required output type."
					);
				}
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutMatrix_>(),
				"Attempted to copy an index from an EmuMath Matrix into a new EmuMath Matrix, but the operation could not complete successfully for at least 1 element."
			);
		}
	}

	template<class OutMatrix_, class InMatrix_, std::size_t...FullColumnIndices_, std::size_t...FullRowIndices_>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_copy_execution
	(
		InMatrix_&& in_matrix_,
		std::index_sequence<FullColumnIndices_...> full_column_indices_,
		std::index_sequence<FullRowIndices_...> full_row_indices_
	)
	{
		// Disable Visual Studio warning about using moved-from object, as we aren't accessing anything after it is moved
#pragma warning(push)
#pragma warning(disable: 26800)
		return OutMatrix_
		(
			_matrix_create_out_from_index<OutMatrix_, InMatrix_, FullColumnIndices_, FullRowIndices_>
			(
				std::forward<InMatrix_>(in_matrix_)
			)...
		);
#pragma warning(pop)
	}

	template
	<
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		typename OutT_,
		bool OutColumnMajor_,
		class InMatrix_,
		typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<InMatrix_>>
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> _matrix_copy(InMatrix_&& in_matrix_)
	{
		using out_matrix = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>;
		if constexpr (out_matrix::size != 0)
		{
			using index_sequences = EmuMath::TMP::make_full_matrix_index_sequences<out_matrix>;

			return _matrix_copy_execution<out_matrix>
			(
				std::forward<InMatrix_>(in_matrix_),
				typename index_sequences::column_index_sequence(),
				typename index_sequences::row_index_sequence()
			);
		}
		else
		{
			if constexpr (std::is_default_constructible_v<out_matrix>)
			{
				return out_matrix();
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<out_matrix>(),
					"Attempted to copy an EmuMath Matrix to an empty EmuMath Matrix. This behaviour is allowed, and will simply result in default-construction of the empty Matrix, however the provided output Matrix type cannot be default-constructed."
				);
			}
		}
	}
}

#endif
