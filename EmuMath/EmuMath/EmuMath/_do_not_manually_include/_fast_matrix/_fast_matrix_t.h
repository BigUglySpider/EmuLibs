#ifndef EMU_MATH_FAST_MATRIX_T_H_INC_
#define EMU_MATH_FAST_MATRIX_T_H_INC_ 1

#include "_helpers/_all_fast_matrix_helpers.h"
#include "../../FastVector.h"
#include <array>

namespace EmuMath
{
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool IsColumnMajor_, std::size_t RegisterWidth_>
	struct FastMatrix
	{
#pragma region COMMON_STATIC_INFO
	public:
		static constexpr std::size_t num_columns = NumColumns_;
		static constexpr std::size_t num_rows = NumRows_;
		static constexpr bool is_column_major = IsColumnMajor_;
		static constexpr bool is_row_major = !is_column_major;
		static constexpr std::size_t num_major_elements = is_column_major ? num_columns : num_rows;
		static constexpr std::size_t num_non_major_elements = is_column_major ? num_rows : num_columns;
		/// <summary> The number of elements that this Matrix behaves to encapsulate. </summary>
		static constexpr std::size_t size = num_columns * num_rows;
		/// <summary> The width provided for this Matrix's registers to use, in bits. </summary>
		static constexpr std::size_t register_width = RegisterWidth_ > 0 ? RegisterWidth_ : 1;

		/// <summary> Alias to this Matrix type. </summary>
		using this_type = EmuMath::FastMatrix<NumColumns_, NumRows_, T_, IsColumnMajor_, RegisterWidth_>;
		/// <summary> Alias to the type of values within this Matrix. </summary>
		using value_type = typename std::remove_cv<T_>::type;
		/// <summary> Alias to the type of SIMD register used for this Matrix's data. </summary>
		using register_type = typename EmuSIMD::TMP::register_type<value_type, register_width>::type;
		/// <summary> Alias to the argument type used to pass an instance of this Matrix's register_type. </summary>
		using register_arg_type = typename EmuSIMD::TMP::register_arg_type<value_type, register_width>::type;
		/// <summary> Alias to the register type used as an argument for the number of shifts performed when a register argument is used instead of a constant. </summary>
		using shift_register_type = __m128i;
		/// <summary>The number of bits each element is interpreted to consume within this Matrix's shift_register_type, with 8-bit bytes regardless of CHAR_BIT. </summary>
		static constexpr std::size_t shift_register_per_element_width = 64;
		/// <summary> The preferred floating-point type for this Matrix, used for floating-point-based calculations using this Matrix. </summary>
		using preferred_floating_point = typename std::conditional<(sizeof(value_type) >= 64), double, float>::type;

		/// <summary> Boolean indicating if this Matrix's encapsulated type is integral. </summary>
		static constexpr bool is_integral = std::is_integral<value_type>::value;
		/// <summary> Boolean indicating if this Matrix's encapsulated type is floating-point. </summary>
		static constexpr bool is_floating_point = std::is_floating_point<value_type>::value;
		/// <summary> Boolean indicating if this Matrix's encapsulated type is signed. </summary>
		static constexpr bool is_signed = std::is_signed<value_type>::value;

		/// <summary> The number of bytes consumed by a single element in this Matrix. </summary>
		static constexpr std::size_t per_element_byte_size = sizeof(value_type);
		/// <summary> The number of bits consumed by a single element in this Matrix with 8-bit bytes, regardless of the value of CHAR_BIT. </summary>
		static constexpr std::size_t per_element_width = per_element_byte_size * 8;
		/// <summary> The number of bits required for each major chunk of this Matrix. </summary>
		static constexpr std::size_t per_major_width = num_non_major_elements * per_element_width;
		/// <summary> Boolean indicating if a major chunks of this Matrix require a partial register. </summary>
		static constexpr bool majors_require_partial_register = (per_major_width % register_width) != 0;
		/// <summary> The total number of registers required to store each major chunk of this Matrix, including the partial register if needed. </summary>
		static constexpr std::size_t num_registers_per_major = (per_major_width / register_width) + (majors_require_partial_register ? 1 : 0);
		/// <summary> The total nubmer of registers used to store this Matrix, including partial ones if needed. </summary>
		static constexpr std::size_t total_num_registers = num_registers_per_major * num_major_elements;
		static constexpr std::size_t num_elements_per_register = register_width / per_element_width;
		static constexpr std::size_t num_elements_in_partial_registers = majors_require_partial_register ? (num_non_major_elements % num_elements_per_register) : 0;
		static constexpr std::size_t full_width_major_size = num_elements_per_register * num_registers_per_major;
		static constexpr std::size_t full_width_size = full_width_major_size * num_major_elements;
		static constexpr std::size_t expected_count_for_default_load_pointer =
		(
			((num_major_elements - 1) * num_non_major_elements) + full_width_major_size
		);

		using major_chunk_type = typename std::conditional<(num_registers_per_major <= 1), register_type, std::array<register_type, num_registers_per_major>>::type;
		using data_type = std::array<major_chunk_type, num_major_elements>;
		using major_index_sequence = std::make_index_sequence<num_major_elements>;
		using major_register_sequence = std::make_index_sequence<num_registers_per_major>;

#pragma region CONSTRUCTOR_VALIDITY_CHECKS
	private:
		template<std::size_t Unused_, EmuConcepts::EmuFastVector...MajorFastVectors_>
		[[nodiscard]] static constexpr inline bool _valid_major_fast_vector_construction()
		{
			return
			(
				Unused_ >= 0 &&
				sizeof...(MajorFastVectors_) == num_major_elements &&
				(... && std::is_same_v<typename EmuCore::TMP::remove_ref_cv_t<MajorFastVectors_>::register_type, register_type>)
			);
		}

		template<std::size_t Unused_, EmuConcepts::KnownSIMD...MajorRegisters_>
		[[nodiscard]] static constexpr inline bool _valid_major_fast_vector_construction()
		{
			return
			(
				Unused_ >= 0 &&
				sizeof...(MajorRegisters_) == total_num_registers &&
				(... && std::is_same_v<typename EmuCore::TMP::remove_ref_cv<MajorRegisters_>::type, register_type>)
			);
		}

		template<std::size_t Unused_, class...MajorChunks_>
		[[nodiscard]] static constexpr inline bool _valid_major_chunk_construction()
		{
			return
			(
				Unused_ >= 0 &&
				num_registers_per_major != 1 &&
				sizeof...(MajorChunks_) == num_major_elements &&
				(... && std::is_same_v<typename EmuCore::TMP::remove_ref_cv<MajorChunks_>::type, major_chunk_type>)
			);
		}

		template<std::size_t Unused_, typename...Args_>
		[[nodiscard]] static constexpr inline bool _valid_per_element_construction_args()
		{
			return
			(
				Unused_ >= 0 &&
				sizeof...(Args_) == size &&
				(... && EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<Args_>::type, value_type>)
			);
		}

		template<std::size_t Unused_, typename...Args_>
		[[nodiscard]] static constexpr inline bool _valid_variadic_construction_args()
		{
			return
			(
				_valid_per_element_construction_args<Unused_, Args_...>() ||
				_valid_major_chunk_construction<Unused_, Args_...>()
			);
		}

	public:
		template<EmuConcepts::EmuFastVector...MajorFastVectors_>
		[[nodiscard]] static constexpr inline bool valid_major_fast_vector_construction()
		{
			return _valid_major_fast_vector_construction<0, MajorFastVectors_...>();
		}

		template<EmuConcepts::KnownSIMD...MajorRegisters_>
		[[nodiscard]] static constexpr inline bool valid_major_register_construction()
		{
			return _valid_major_register_construction<0, MajorRegisters_...>();
		}

		template<class...MajorChunks_>
		[[nodiscard]] static constexpr inline bool valid_major_chunk_construction()
		{
			return _valid_major_chunk_construction<0, MajorChunks_...>();
		}

		template<typename...Args_>
		[[nodiscard]] static constexpr inline bool valid_per_element_construction_args()
		{
			return _valid_per_element_construction_args<0, Args_...>();
		}

		template<typename...Args_>
		[[nodiscard]] static constexpr inline bool valid_variadic_construction_args()
		{
			return _valid_variadic_construction_args<0, Args_...>();
		}
#pragma endregion

#pragma region CONSTRUCTION_HELPERS
	private:
		template<bool FullWidthOffset_, std::size_t MajorIndex_, std::size_t RegisterIndex_>
		[[nodiscard]] static constexpr inline register_type _load_major_chunk_register_from_pointer(const value_type* p_to_load_)
		{
			constexpr std::size_t per_major_offset = FullWidthOffset_ ? (num_elements_per_register * num_registers_per_major) : num_non_major_elements;
			constexpr std::size_t major_offset = MajorIndex_ * per_major_offset;
			constexpr std::size_t register_offset = RegisterIndex_ * num_elements_per_register;
			constexpr std::size_t offset = major_offset + register_offset;
			return EmuSIMD::load<register_type>(p_to_load_ + offset);
		}

		template<bool FullWidthOffset_, std::size_t MajorIndex_, std::size_t...MajorRegisterIndices_>
		[[nodiscard]] static constexpr inline major_chunk_type _load_major_chunk_from_pointer(const value_type* p_to_load_)
		{
			if constexpr (num_registers_per_major > 1)
			{
				return major_chunk_type
				({
					_load_major_chunk_register_from_pointer<FullWidthOffset_, MajorIndex_, MajorRegisterIndices_>
					(
						p_to_load_
					)...
				});
			}
			else
			{
				return _load_major_chunk_register_from_pointer<FullWidthOffset_, MajorIndex_, 0>(p_to_load_);
			}
		}

		template<bool FullWidthOffset_, std::size_t...MajorIndices_, std::size_t...MajorRegisterIndices_>
		[[nodiscard]] static constexpr inline data_type _load_data_from_pointer
		(
			const value_type* p_to_load_,
			std::index_sequence<MajorIndices_...> major_indices_,
			std::index_sequence<MajorRegisterIndices_...> major_register_indices_
		)
		{
			return data_type
			({
				_load_major_chunk_from_pointer<FullWidthOffset_, MajorIndices_, MajorRegisterIndices_...>
				(
					p_to_load_
				)...
			});
		}

		template<std::size_t RegisterIndex_, EmuConcepts::EmuFastVector FastMajorVector_>
		[[nodiscard]] static constexpr inline register_type _retrieve_register_from_fast_vector(FastMajorVector_&& fast_major_vector_)
		{
			using _fast_major_vector_uq = typename EmuCore::TMP::remove_ref_cv<FastMajorVector_>::type;
			if constexpr (RegisterIndex_ < _fast_major_vector_uq::num_registers)
			{
				if constexpr (_fast_major_vector_uq::num_registers > 1)
				{
					return std::forward<FastMajorVector_>(fast_major_vector_).data[RegisterIndex_];
				}
				else
				{
					return std::forward<FastMajorVector_>(fast_major_vector_).data;
				}
			}
			else
			{
				return EmuSIMD::setzero<register_type>();
			}
		}

		template<EmuConcepts::EmuFastVector FastMajorVector_, std::size_t...PerMajorRegisterIndices_>
		[[nodiscard]] static constexpr inline major_chunk_type _make_major_chunk_from_fast_vector(FastMajorVector_&& fast_major_vector_)
		{
			return major_chunk_type
			({
				_retrieve_register_from_fast_vector<PerMajorRegisterIndices_>(std::forward<FastMajorVector_>(fast_major_vector_))...
			});
		}

		template<EmuConcepts::EmuFastVector...FastMajorVectors_, std::size_t...MajorIndices_, std::size_t...PerMajorRegisterIndices_>
		[[nodiscard]] static constexpr inline data_type _make_data_from_fast_vectors
		(
			std::index_sequence<MajorIndices_...> major_indices_,
			std::index_sequence<PerMajorRegisterIndices_...> per_major_register_indices_,
			FastMajorVectors_&&...fast_major_vectors_
		)
		{
			if constexpr (sizeof...(PerMajorRegisterIndices_) > 1)
			{
				return data_type
				({
					_make_major_chunk_from_fast_vector<FastMajorVectors_, PerMajorRegisterIndices_...>
					(
						std::forward<FastMajorVectors_>(fast_major_vectors_)
					)...
				});
			}
			else
			{
				return data_type({ std::forward<FastMajorVectors_>(fast_major_vectors_).data... });
			}
		}

		template<std::size_t MajorIndex_, EmuConcepts::KnownSIMD...Registers_, std::size_t...RegisterIndices_>
		[[nodiscard]] static constexpr inline major_chunk_type _make_major_chunk_array_from_registers
		(
			std::tuple<Registers_...>& registers_,
			std::index_sequence<RegisterIndices_...> register_indices_
		)
		{
			constexpr std::size_t offset = MajorIndex_ * num_registers_per_major;
			return major_chunk_type
			({
				std::forward<decltype(std::get<offset + RegisterIndices_>(registers_))>
				(
					std::get<offset + RegisterIndices_>(registers_)
				)...
			});
		}

		template<EmuConcepts::KnownSIMD...Registers_, std::size_t...MajorIndices_>
		[[nodiscard]] static constexpr inline data_type _make_data_from_registers(std::index_sequence<MajorIndices_...> major_indices_, Registers_&&...registers_)
		{
			if constexpr (num_registers_per_major == 1)
			{
				return data_type({ std::forward<Registers_>(registers_)... });
			}
			else
			{
				auto register_tuple = std::forward_as_tuple<Registers_...>(std::forward<Registers_>(registers_)...);
				return data_type
				({
					_make_major_chunk_array_from_registers<MajorIndices_>
					(
						register_tuple,
						major_register_sequence()
					)...
				});
			}
		}

		template<bool IncludeNonEncapsulated_, std::size_t MajorIndex_, std::size_t NonMajorIndex_, typename...Args_>
		[[nodiscard]] static constexpr inline decltype(auto) _get_per_element_arg(std::tuple<Args_...>& args_)
		{
			if constexpr (IncludeNonEncapsulated_ || (MajorIndex_ < num_major_elements && NonMajorIndex_ < num_non_major_elements))
			{
				constexpr std::size_t per_major_offset = IncludeNonEncapsulated_ ? (num_elements_per_register * num_registers_per_major) : num_non_major_elements;
				constexpr std::size_t flattened_major_offset = MajorIndex_ * per_major_offset;
				return std::forward<decltype(std::get<flattened_major_offset + NonMajorIndex_>(args_))>
				(
					std::get<flattened_major_offset + NonMajorIndex_>(args_)
				);
			}
			else
			{
				return 0;
			}
		}

		template<bool IncludeNonEncapsulated_, std::size_t MajorIndex_, std::size_t RegisterIndex_, std::size_t...NonMajorIndices_, typename...Args_>
		[[nodiscard]] static constexpr inline register_type _make_register_from_per_element_args(std::tuple<Args_...>& args_)
		{
			constexpr std::size_t non_major_offset = RegisterIndex_ * num_elements_per_register;
			return EmuSIMD::setr<register_type, per_element_width>
			(
				std::forward<decltype(_get_per_element_arg<IncludeNonEncapsulated_, MajorIndex_, non_major_offset + NonMajorIndices_>(args_))>
				(
					_get_per_element_arg<IncludeNonEncapsulated_, MajorIndex_, non_major_offset + NonMajorIndices_>(args_)
				)...
			);
		}

		template<bool IncludeNonEncapsulated_, std::size_t MajorIndex_, std::size_t...MajorRegisterIndices_, std::size_t...NonMajorIndices_, typename...Args_>
		[[nodiscard]] static constexpr inline major_chunk_type _make_major_chunk_from_per_element_args
		(
			std::tuple<Args_...>& args_,
			std::index_sequence<MajorRegisterIndices_...> major_register_indices_,
			std::index_sequence<NonMajorIndices_...> non_major_indices_
		)
		{
			if constexpr (num_registers_per_major > 1)
			{
				return major_chunk_type
				({
					_make_register_from_per_element_args<IncludeNonEncapsulated_, MajorIndex_, MajorRegisterIndices_, NonMajorIndices_...>
					(
						args_
					)...
				});
			}
			else
			{
				return _make_register_from_per_element_args<IncludeNonEncapsulated_, MajorIndex_, 0, NonMajorIndices_...>(args_);
			}
		}

		template<bool IncludeNonEncapsulated_, typename...Args_, std::size_t...MajorIndices_>
		[[nodiscard]] static constexpr inline data_type _make_data_from_per_element_args
		(
			std::index_sequence<MajorIndices_...> major_indices_,
			std::tuple<Args_...> args_
		)
		{
			return data_type
			({
				_make_major_chunk_from_per_element_args<IncludeNonEncapsulated_, MajorIndices_>
				(
					args_,
					std::make_index_sequence<num_registers_per_major>(),
					std::make_index_sequence<num_elements_per_register>()
				)...
			});
		}

		template<typename...Args_>
		[[nodiscard]] static constexpr inline data_type _make_data_from_variadic_args(Args_&&...args_)
		{
			if constexpr (valid_per_element_construction_args<Args_...>())
			{
				// Per encapsulated value (but ignore contained outside of encapsulated range)
				return _make_data_from_per_element_args<false>
				(
					major_index_sequence(),
					std::forward_as_tuple<Args_...>(std::forward<Args_>(args_)...)
				);
			}
			else if constexpr (valid_major_chunk_construction<Args_...>())
			{
				return data_type({ std::forward<Args_>(args_)... });
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Args_...>(),
					"Internal EmuMath Error: False-positive allowance to invoke variadic FastMatrix constructor as the provided arguments do not match any valid construction method."
				);
			}
		}
#pragma endregion

#pragma region CONSTRUCTORS
	public:
		constexpr inline FastMatrix() noexcept = default;
		constexpr inline FastMatrix(this_type&&) noexcept = default;
		constexpr inline FastMatrix(const this_type&) noexcept = default;

		/// <summary>
		/// <para> Loads the passed contiguous data pointer directly into a newly constructed Matrix. </para>
		/// <para> 
		///		The pointed-to data must contain a number of values equal to at least `expected_count_for_default_load_pointer`,
		///		which itself is equal to `((num_major_elements - 1) * num_non_major_elements) + full_width_major_size`.
		/// </para>
		/// <para> If the pointed-to data count does not meet this constraint, unsafe memory may be loaded and undefined behaviour becomes likely. </para>
		/// <para>
		///		If loading data from an EmuMath `Matrix` of the same major-order, it is recommended to pass the `Matrix` directly. 
		///		Said constructor will perform adaptive loads regardless of size, where possible.
		/// </para>
		/// </summary>
		/// <param name="p_data_to_load_">Pointer to at least `expected_count_for_default_load_pointer` items of this Matrix's `value_type`.</param>
		constexpr inline FastMatrix(const value_type* p_data_to_load_)
			: major_chunks(_load_data_from_pointer<false>(p_data_to_load_, major_index_sequence(), major_register_sequence()))
		{
		}

		/// <summary>
		/// <para> Constructs a FastMatrix loaded from the passed scalar EmuMath Matrix. </para>
		/// <para>
		///		Optimised loads will be prioritised over sets where possible. 
		///		Loads are only possible with matching major storage order, 
		///		and where there are enough elements available to perform a contiguous load for a register.
		/// </para>
		/// </summary>
		/// <param name="scalar_matrix_to_load_">EmuMath Matrix to load into the newly-constructed FastMatrix.</param>
		template<EmuConcepts::EmuMatrix ScalarMatrix_>
		constexpr inline FastMatrix(ScalarMatrix_&& scalar_matrix_to_load_) noexcept
			: major_chunks(EmuMath::Helpers::fast_matrix_load_data_type<this_type>(std::forward<ScalarMatrix_>(scalar_matrix_to_load_)))
		{
		}

		/// <summary>
		/// <para> Constructs a FastMatrix using the registers of the passed FastVectors to create respective major chunks. </para>
		/// </summary>
		/// <param name="major_vectors_">
		///		<para>
		///			EmuMath `FastVectors`, each representing a major chunk of the result Matrix in order from 0 to last. 
		///			The number of arguments should be equal to this Matrix type's `num_major_elements`.
		///		</para>
		///		<para> The passed `FastVectors` may be any size, but their `register_type` must be the same as this Matrix type's `register_type`. </para>
		/// </param>
		template
		<
			std::size_t Unused_ = 0,
			EmuConcepts::EmuFastVector...MajorFastVectors_,
			typename = std::enable_if_t<_valid_major_fast_vector_construction<Unused_, MajorFastVectors_...>()>
		>
		constexpr inline FastMatrix(MajorFastVectors_&&...major_vectors_) noexcept
			: major_chunks(_make_data_from_fast_vectors(major_index_sequence(), major_register_sequence(), std::forward<MajorFastVectors_>(major_vectors_)...))
		{
		}

		/// <summary>
		/// <para> Constructs a FastMatrix using the passed registers exactly as they are when passed. </para>
		/// <para> Registers are used in this Matrix type's major storage order; a full major-element of registers will be used before moving to the next. </para>
		/// </summary>
		/// <param name="major_order_registers_">
		///		<para> EmuSIMD-recognised SIMD registers representing each register used by this Matrix, in its major-storage order. </para>
		///		<para>
		///			The passed registers must be the same as this Matrix type's `register_type`, 
		///			and the amount of arguments must be equal to this Matrix type's `total_num_registers`. 
		///		</para>
		/// </param>
		template
		<
			std::size_t Unused_ = 0,
			EmuConcepts::KnownSIMD...MajorRegisters_,
			typename = std::enable_if_t<_valid_major_fast_vector_construction<Unused_, MajorRegisters_...>()>
		>
		constexpr inline FastMatrix(MajorRegisters_&&...major_order_registers_) noexcept
			: major_chunks(_make_data_from_registers(major_index_sequence(), std::forward<MajorRegisters_>(major_order_registers_)...))
		{
		}

		/// <summary>
		/// <para> Variadic constructor which may be used to create this FastMatrix type in one of multiple ways: </para>
		/// <para> 
		///		1: Per-element construction, where 1 argument will be taken for each encapsulated element in contiguous order. 
		///		This is available where the number of passed Args_ is equal to this Matrix type's `size`, and they are all usable as its `value_type`.
		/// </para>
		/// <para>
		///		2: Per-major-chunk construction, where 1 argument will be taken for each major chunk in contiguous order. 
		///		This is available where the number of passed Args_ is equal to this Matrix type's `num_major_elements`, and they are all its `major_chunk_type`.
		/// </para>
		/// <para> Where multiple of these constraints are met, the first appearing in the above list will be used. </para>
		/// </summary>
		/// <param name="args_">Variadic arguments meeting at least one of the described constraints.</param>
		template<std::size_t Unused_ = 0, typename...Args_, typename = std::enable_if_t<_valid_variadic_construction_args<Unused_, Args_...>() >>
		constexpr inline FastMatrix(Args_&&...args_)
			: major_chunks(_make_data_from_variadic_args(std::forward<Args_>(args_)...))
		{
		}
#pragma endregion

#pragma region GETS
	public:
		/// <summary>
		/// <para> Retrieves the register at the provided `MajorIndex_` of this Matrix's major chunks. </para>
		/// <para> By default, the first register in the chunk will be selected. To choose a different register index, provide a second template argument. </para>
		/// </summary>
		/// <returns>Reference to the register at the given point within this Matrix.</returns>
		template<std::size_t MajorIndex_, std::size_t RegisterIndex_ = 0>
		[[nodiscard]] constexpr inline register_type& GetRegister()
		{
			if constexpr (MajorIndex_ < num_major_elements)
			{
				if constexpr (RegisterIndex_ < num_registers_per_major)
				{
					if constexpr (num_registers_per_major > 1)
					{
						return major_chunks[MajorIndex_][RegisterIndex_];
					}
					else
					{
						return major_chunks[MajorIndex_];
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<RegisterIndex_>(),
						"Attempted to retrieve a register from an EmuMath FastMatrix, but the provided Register Index exceeds the maximum register index for a major within the Matrix."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<MajorIndex_>(),
					"Attempted to retrieve a register from an EmuMath FastMatrix, but the provided Major index exceeds the maximum major index of the Matrix."
				);
			}
		}

		template<std::size_t MajorIndex_, std::size_t RegisterIndex_ = 0>
		[[nodiscard]] constexpr inline const register_type& GetRegister() const
		{
			return const_cast<this_type*>(this)->template GetRegister<MajorIndex_, RegisterIndex_>();
		}

		/// <summary>
		/// <para> Makes a register of this Matrix's `register_type` with all elements set to match the element at the given index of this Matrix. </para>
		/// </summary>
		/// <returns>Register filled with the value at the given index of this Matrix.</returns>
		template<std::size_t ColumnIndex_, std::size_t RowIndex_>
		[[nodiscard]] constexpr inline register_type GetRegisterOfIndex() const
		{
			constexpr std::size_t major_index = is_column_major ? ColumnIndex_ : RowIndex_;
			if constexpr (major_index < num_major_elements)
			{
				constexpr std::size_t non_major_index = is_column_major ? RowIndex_ : ColumnIndex_;
				constexpr std::size_t register_index = non_major_index / num_elements_per_register;
				if constexpr (register_index < num_registers_per_major)
				{
					constexpr std::size_t element_index = non_major_index % num_elements_per_register;
					return EmuSIMD::set_all_to_index<element_index, per_element_width>(GetRegister<major_index, register_index>());
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<register_index>(),
						"Attempted to make a register from a single index within an EmuMath FastMatrix, but the provided non-major index requires a register outside of the contained range of the Matrix."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<major_index>(),
					"Attempted to make a register from a single index within an EmuMath FastMatrix, but the provided Major index exceeds the maximum major index of the Matrix."
				);
			}
		}
#pragma endregion

#pragma region ARITHMETIC
	public:
		/// <summary>
		/// <para> Standard MAT*MAT multiplication, treating this Matrix as the left-hand operand and the passed Matrix as the right-hand operand. </para>
		/// <para> This is not available where `this_matrix * rhs` is an invalid matrix multiplication operation. </para>
		/// </summary>
		/// <param name="rhs_fast_matrix_">FastMatrix appearing on the right-hand side of Matrix multiplication.</param>
		/// <returns>EmuMath FastMatrix containing resulting from multiply this Matrix with the passed right-hand Matrix.</returns>
		template<EmuConcepts::EmuFastMatrix RhsFastMatrix_>
		requires EmuConcepts::EmuFastMatrixMultPair<this_type, RhsFastMatrix_>
		[[nodiscard]] constexpr inline auto Multiply(RhsFastMatrix_&& rhs_) const
			-> EmuMath::FastMatrix<EmuCore::TMP::remove_ref_cv_t<RhsFastMatrix_>::num_columns, num_rows, value_type, is_column_major, register_width>
		{
			return EmuMath::Helpers::fast_matrix_multiply(*this, std::forward<RhsFastMatrix_>(rhs_));
		}
#pragma endregion

#pragma region ASSIGNMENT_OPERATORS
	public:
		constexpr inline this_type& operator=(const this_type&) = default;
		constexpr inline this_type& operator=(this_type&&) = default;
#pragma endregion

#pragma region DATA
	public:
		/// <summary>
		/// <para> Major-order collection of register chunks used by this Matrix. </para>
		/// <para> If this Matrix is column-major, this is a collection of columns. Otherwise, it is a collection of rows. </para>
		/// <para> 
		///		If a major chunk can be stored with just one register, this will be a collection of registers. 
		///		Otherwise, it will be a collection of collections of registers.
		/// </para>
		/// </summary>
		data_type major_chunks;
#pragma endregion
	};
}

template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool IsColumnMajor_, std::size_t RegisterWidth_>
inline std::ostream& operator<<(std::ostream& str_, const EmuMath::FastMatrix<NumColumns_, NumRows_, T_, IsColumnMajor_, RegisterWidth_>& fast_matrix_)
{
	// TODO: GENERALISE FOR ANY SIZE, NOT JUST 4x4/8x8
	if constexpr (NumColumns_ == NumRows_)
	{
		if constexpr (IsColumnMajor_)
		{
			constexpr std::size_t OutSize_ = NumColumns_ <= 4 ? 4 : 8;
			EmuMath::Matrix<OutSize_, OutSize_, float, true> mat;
			if constexpr (NumColumns_ <= 4)
			{
				_mm_store_ps(mat.data<0, 0>(), fast_matrix_.major_chunks[0]);
				_mm_store_ps(mat.data<1, 0>(), fast_matrix_.major_chunks[1]);
				_mm_store_ps(mat.data<2, 0>(), fast_matrix_.major_chunks[2]);
				_mm_store_ps(mat.data<3, 0>(), fast_matrix_.major_chunks[3]);
			}
			else if constexpr (NumColumns_ <= 8)
			{
				_mm_store_ps(mat.data<0, 0>(), fast_matrix_.major_chunks[0][0]);
				_mm_store_ps(mat.data<1, 0>(), fast_matrix_.major_chunks[1][0]);
				_mm_store_ps(mat.data<2, 0>(), fast_matrix_.major_chunks[2][0]);
				_mm_store_ps(mat.data<3, 0>(), fast_matrix_.major_chunks[3][0]);
				_mm_store_ps(mat.data<4, 0>(), fast_matrix_.major_chunks[4][0]);
				_mm_store_ps(mat.data<5, 0>(), fast_matrix_.major_chunks[5][0]);
				_mm_store_ps(mat.data<6, 0>(), fast_matrix_.major_chunks[6][0]);
				_mm_store_ps(mat.data<7, 0>(), fast_matrix_.major_chunks[7][0]);

				_mm_store_ps(mat.data<0, 4>(), fast_matrix_.major_chunks[0][1]);
				_mm_store_ps(mat.data<1, 4>(), fast_matrix_.major_chunks[1][1]);
				_mm_store_ps(mat.data<2, 4>(), fast_matrix_.major_chunks[2][1]);
				_mm_store_ps(mat.data<3, 4>(), fast_matrix_.major_chunks[3][1]);
				_mm_store_ps(mat.data<4, 4>(), fast_matrix_.major_chunks[4][1]);
				_mm_store_ps(mat.data<5, 4>(), fast_matrix_.major_chunks[5][1]);
				_mm_store_ps(mat.data<6, 4>(), fast_matrix_.major_chunks[6][1]);
				_mm_store_ps(mat.data<7, 4>(), fast_matrix_.major_chunks[7][1]);
			}

			str_ << mat;
		}
		else
		{
			constexpr std::size_t OutSize_ = NumColumns_ <= 4 ? 4 : 8;
			EmuMath::Matrix<OutSize_, OutSize_, float, false> mat;
			if constexpr (NumColumns_ <= 4)
			{
				_mm_store_ps(mat.data<0, 0>(), fast_matrix_.major_chunks[0]);
				_mm_store_ps(mat.data<0, 1>(), fast_matrix_.major_chunks[1]);
				_mm_store_ps(mat.data<0, 2>(), fast_matrix_.major_chunks[2]);
				_mm_store_ps(mat.data<0, 3>(), fast_matrix_.major_chunks[3]);
			}
			else if constexpr (NumColumns_ <= 8)
			{
				_mm_store_ps(mat.data<0, 0>(), fast_matrix_.major_chunks[0][0]);
				_mm_store_ps(mat.data<0, 1>(), fast_matrix_.major_chunks[1][0]);
				_mm_store_ps(mat.data<0, 2>(), fast_matrix_.major_chunks[2][0]);
				_mm_store_ps(mat.data<0, 3>(), fast_matrix_.major_chunks[3][0]);
				_mm_store_ps(mat.data<0, 4>(), fast_matrix_.major_chunks[4][0]);
				_mm_store_ps(mat.data<0, 5>(), fast_matrix_.major_chunks[5][0]);
				_mm_store_ps(mat.data<0, 6>(), fast_matrix_.major_chunks[6][0]);
				_mm_store_ps(mat.data<0, 7>(), fast_matrix_.major_chunks[7][0]);

				_mm_store_ps(mat.data<4, 0>(), fast_matrix_.major_chunks[0][1]);
				_mm_store_ps(mat.data<4, 1>(), fast_matrix_.major_chunks[1][1]);
				_mm_store_ps(mat.data<4, 2>(), fast_matrix_.major_chunks[2][1]);
				_mm_store_ps(mat.data<4, 3>(), fast_matrix_.major_chunks[3][1]);
				_mm_store_ps(mat.data<4, 4>(), fast_matrix_.major_chunks[4][1]);
				_mm_store_ps(mat.data<4, 5>(), fast_matrix_.major_chunks[5][1]);
				_mm_store_ps(mat.data<4, 6>(), fast_matrix_.major_chunks[6][1]);
				_mm_store_ps(mat.data<4, 7>(), fast_matrix_.major_chunks[7][1]);
			}

			str_ << mat;
		}
	}
	else
	{
		str_ << "oops, not done non-square 4x4-8x8 output yet";
	}
	return str_;
}

#endif
