#ifndef EMU_MATH_FAST_MATRIX_STORE_H_INC_
#define EMU_MATH_FAST_MATRIX_STORE_H_INC_ 1

#include "_common_fast_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Stores the input FastMatrix to the output scalar Matrix. </para>
	/// <para>
	///		Where the `stored_type` of the output Matrix matches the `value_type` of the input Matrix, 
	///		both Matrices share the same major storage order,
	///		and contiguous storage remaining in the output Matrix allows, optimised stores will be used. 
	///		Otherwise, intermediate data will be stored and then assigned to respective output indices, with conversions performed if necessary.
	/// </para>
	/// <para> 
	///		If `ZeroNonEncapsulated_` is `true`, indices in the output Matrix that are not encapsulated by the input Matrix 
	///		will be set to 0 after storing. Otherwise, data will be stored while leaving unaffected indices as-is.
	///		By default, this is `true`.
	/// </para>
	/// <para>
	///		Note that where `ZeroNonEncapsualted_ == false`, the output Matrix will contain non-encapsulated, potentially invalid data, in cases
	///		where the output Matrix is larger than an input Matrix with partial registers (for example, outputting a 3x3 FastMatrix to a 4x4 scalar Matrix).
	/// </para>
	/// </summary>
	/// <param name="in_fast_matrix_">FastMatrix to output the data of.</param>
	/// <param name="out_scalar_matrix_">Scalar Matrix to output to.</param>
	template<bool ZeroNonEncapsulated_ = true, EmuConcepts::EmuFastMatrix FastMatrix_, EmuConcepts::EmuMatrix OutMatrix_>
	requires (!std::is_const_v<OutMatrix_>)
	constexpr inline void fast_matrix_store(FastMatrix_&& in_fast_matrix_, OutMatrix_& out_scalar_matrix_)
	{
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		using _out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		constexpr std::size_t out_matching_major_count = _fast_mat_uq::is_column_major ? _out_mat_uq::num_columns : _out_mat_uq::num_rows;
		constexpr std::size_t majors_to_store = EmuCore::TMP::smallest_constant_v<std::size_t, _fast_mat_uq::num_major_elements, out_matching_major_count>;
		constexpr std::size_t register_size = _fast_mat_uq::num_elements_per_register;
		constexpr std::size_t out_register_fill_count =
		(
			(_out_mat_uq::num_non_major_elements / register_size) +
			((_out_mat_uq::num_non_major_elements % register_size) == 0 ? 0 : 1)
		);
		constexpr std::size_t registers_per_major = _fast_mat_uq::num_registers_per_major;
		constexpr std::size_t registers_to_store_per_major = EmuCore::TMP::smallest_constant_v<std::size_t, registers_per_major, out_register_fill_count>;

		using major_index_sequence = std::make_index_sequence<majors_to_store>;
		using register_index_sequence = std::make_index_sequence<registers_to_store_per_major>;
		_fast_matrix_underlying::_store_to_scalar_matrix
		(
			out_scalar_matrix_,
			std::forward<FastMatrix_>(in_fast_matrix_),
			major_index_sequence(),
			register_index_sequence()
		);

		if constexpr (ZeroNonEncapsulated_)
		{
			// Separate branch if we have both columns and rows instead of merging both branches
			// --- This avoids a duplicate index
			if constexpr (_out_mat_uq::num_columns > _fast_mat_uq::num_columns && _out_mat_uq::num_rows > _fast_mat_uq::num_rows)
			{
				using column_index_sequences = EmuMath::TMP::make_ranged_matrix_index_sequences
				<
					_fast_mat_uq::num_columns,
					_out_mat_uq::num_columns,
					0,
					_out_mat_uq::num_rows,
					_out_mat_uq::is_column_major
				>;
				using columns_column_sequence = typename column_index_sequences::column_index_sequence;
				using columns_row_sequence = typename column_index_sequences::row_index_sequence;
				_fast_matrix_underlying::_zero_scalar_range(out_scalar_matrix_, columns_column_sequence(), columns_row_sequence());

				using row_index_sequences = EmuMath::TMP::make_ranged_matrix_index_sequences
				<
					0,
					_out_mat_uq::num_columns - 1,
					_fast_mat_uq::num_rows,
					_out_mat_uq::num_rows,
					_out_mat_uq::is_column_major
				>;
				using rows_column_sequence = typename row_index_sequences::column_index_sequence;
				using rows_row_sequence = typename row_index_sequences::row_index_sequence;
				_fast_matrix_underlying::_zero_scalar_range(out_scalar_matrix_, rows_column_sequence(), rows_row_sequence());
			}
			else if constexpr (_out_mat_uq::num_columns > _fast_mat_uq::num_columns)
			{
				using index_sequences = EmuMath::TMP::make_ranged_matrix_index_sequences
				<
					_fast_mat_uq::num_columns,
					_out_mat_uq::num_columns,
					0,
					_out_mat_uq::num_rows,
					_out_mat_uq::is_column_major
				>;
				using column_sequence = typename index_sequences::column_index_sequence;
				using row_sequence = typename index_sequences::row_index_sequence;
				_fast_matrix_underlying::_zero_scalar_range(out_scalar_matrix_, column_sequence(), row_sequence());
			}
			else if constexpr (_out_mat_uq::num_rows > _fast_mat_uq::num_rows)
			{
				using index_sequences = EmuMath::TMP::make_ranged_matrix_index_sequences
				<
					0,
					_out_mat_uq::num_columns,
					_fast_mat_uq::num_rows,
					_out_mat_uq::num_rows,
					_out_mat_uq::is_column_major
				>;
				using column_sequence = typename index_sequences::column_index_sequence;
				using row_sequence = typename index_sequences::row_index_sequence;
				_fast_matrix_underlying::_zero_scalar_range(out_scalar_matrix_, column_sequence(), row_sequence());
			}
		}
	}

	/// <summary>
	/// <para> Stores the data of the input `FastMatrix` contiguously into the pointed-to memory location. </para>
	/// <para> 
	///		If the pointed-to data is of the same type as the Matrix's `value_type`, it will be stored directly. 
	///		Otherwise, intermediate conversions will be performed on a per-element basis. 
	/// </para>
	/// <para> 
	///		May optionally output the full width of the Matrix's registers instead of only its encapsulated data. 
	///		This can be enabled by setting `FullWidth_` to `true`, which itself defaults to `false`.
	/// </para>
	/// <para>
	///		Where `FullWidth_ == false`: The pointed-to data should have a number of contiguous elements 
	///		equal to at least the Matrix's `expected_count_for_default_load_pointer`, which equates to its
	///		`((num_major_elements - 1) * num_non_major_elements) + full_width_major_size`.
	/// </para>
	/// <para>
	///		Where `FullWidth_ == true`, the pointed-to data should have a number of contiguous elements
	///		equal to at least the Matrix's `full_width_size`.
	/// </para>
	/// <para> Failing to meet size constraints is likely to result in illegal memory reads/writes and/or undefined behaviour. </para>
	/// </summary>
	/// <param name="in_fast_matrix_">FastMatrix to store to memory.</param>
	/// <param name="p_out_data_">Pointer to memory meeting described constraints, where the data of the input Matrix will be contiguously stored.</param>
	template<bool FullWidth_ = false, EmuConcepts::EmuFastMatrix FastMatrix_, typename OutData_>
	requires (!std::is_const_v<OutData_>)
	constexpr inline void fast_matrix_store(FastMatrix_&& in_fast_matrix_, OutData_* p_out_data_)
	{
		using _in_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		using major_index_sequence = std::make_index_sequence<_in_fast_mat_uq::num_major_elements>;
		using register_index_sequence = std::make_index_sequence<_in_fast_mat_uq::num_registers_per_major>;

		_fast_matrix_underlying::_store_to_data_pointer<FullWidth_>
		(
			std::forward<FastMatrix_>(in_fast_matrix_),
			p_out_data_,
			major_index_sequence(),
			register_index_sequence()
		);
	}

	/// <summary>
	/// <para> Stores the passed Matrix's data into a newly constructed scalar Matrix of the specified type. </para>
	/// <para> Arguments for the output Matrix are all optional, and given in sequential order as per `EmuMath::Matrix` arguments. </para>
	/// <para> 
	///		Omitted arguments will default to the same argument as used to instantiate the passed FastMatrix, 
	///		except for `OutT_` which will default to the passed FastMatrix's `value_type`.
	/// </para>
	/// <para> 
	///		If this is being used to assign to an existing scalar Matrix, consider passing a reference to that Matrix instead to 
	///		take advantage of optimised direct-stores and remove potential constructor overhead.
	/// </para>
	/// </summary>
	/// <returns>Scalar EmuMath Matrix of the specified type containing data mimicking the passed FastMatrix.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_store(FastMatrix_&& fast_matrix_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		using _in_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		constexpr std::size_t out_matching_major_size = _in_fast_mat_uq::is_column_major ? OutNumColumns_ : OutNumRows_;
		constexpr std::size_t num_majors_to_store = EmuCore::TMP::smallest_constant_v<std::size_t, out_matching_major_size, _in_fast_mat_uq::num_major_elements>;

		constexpr std::size_t out_matching_non_major_size = _in_fast_mat_uq::is_column_major ? OutNumRows_ : OutNumColumns_;
		constexpr std::size_t register_size = _in_fast_mat_uq::num_elements_per_register;
		constexpr std::size_t registers_per_major = _in_fast_mat_uq::num_registers_per_major;
		constexpr std::size_t out_required_registers = 
		(
			(out_matching_non_major_size / register_size) + ((out_matching_non_major_size % register_size) == 0 ? 0 : 1)
		);
		constexpr std::size_t num_registers_to_store = EmuCore::TMP::smallest_constant_v<std::size_t, out_required_registers, registers_per_major>;

		using out_indices = EmuMath::TMP::make_ranged_matrix_index_sequences<0, OutNumColumns_, 0, OutNumRows_, OutColumnMajor_>;
		using column_indices = typename out_indices::column_index_sequence;
		using row_indices = typename out_indices::row_index_sequence;
		return _fast_matrix_underlying::_store_to_new_scalar_matrix
		<
			num_majors_to_store,
			num_registers_to_store,
			EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
		>(std::forward<FastMatrix_>(fast_matrix_), column_indices(), row_indices());
	}

	template<typename OutT_, bool OutColumnMajor_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_store(FastMatrix_&& fast_matrix_)
	{
		using _in_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		return fast_matrix_store<_in_fast_mat_uq::num_columns, _in_fast_mat_uq::num_rows, OutT_, OutColumnMajor_>
		(
			std::forward<FastMatrix_>(fast_matrix_)
		);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_store(FastMatrix_&& fast_matrix_)
	{
		using _in_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		return fast_matrix_store<OutNumColumns_, OutNumRows_, typename _in_fast_mat_uq::value_type, OutColumnMajor_>
		(
			std::forward<FastMatrix_>(fast_matrix_)
		);
	}

	template<bool OutColumnMajor_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_store(FastMatrix_&& fast_matrix_)
	{
		using _in_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		return fast_matrix_store<_in_fast_mat_uq::num_columns, _in_fast_mat_uq::num_rows, typename _in_fast_mat_uq::value_type, OutColumnMajor_>
		(
			std::forward<FastMatrix_>(fast_matrix_)
		);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_store(FastMatrix_&& fast_matrix_)
	{
		using _in_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		return fast_matrix_store<OutNumColumns_, OutNumRows_, OutT_, _in_fast_mat_uq::is_column_major>
		(
			std::forward<FastMatrix_>(fast_matrix_)
		);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_store(FastMatrix_&& fast_matrix_)
	{
		using _in_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		return fast_matrix_store<OutNumColumns_, OutNumRows_, typename _in_fast_mat_uq::value_type, _in_fast_mat_uq::is_column_major>
		(
			std::forward<FastMatrix_>(fast_matrix_)
		);
	}

	template<EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_store(FastMatrix_&& fast_matrix_)
	{
		using _in_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		return fast_matrix_store<_in_fast_mat_uq::num_columns, _in_fast_mat_uq::num_rows, typename _in_fast_mat_uq::value_type, _in_fast_mat_uq::is_column_major>
		(
			std::forward<FastMatrix_>(fast_matrix_)
		);
	}
}

#endif
