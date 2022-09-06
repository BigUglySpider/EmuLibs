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
		/// <summary> The total number of registers used to store this Matrix, including partial ones if needed. </summary>
		static constexpr std::size_t total_num_registers = num_registers_per_major * num_major_elements;
		/// <summary> The number of elements contained in a single one of this Matrix type's registers. </summary>
		static constexpr std::size_t num_elements_per_register = register_width / per_element_width;
		/// <summary> The number of encapsulated elements accounted for by individual partial registers of this Matrix type. </summary>
		static constexpr std::size_t num_elements_in_partial_registers = majors_require_partial_register ? (num_non_major_elements % num_elements_per_register) : 0;
		/// <summary> The total number of elements included in each major chunk of this Matrix type, including non-encapsulated padding. </summary>
		static constexpr std::size_t full_width_major_size = num_elements_per_register * num_registers_per_major;
		/// <summary> The total number of elements included in this Matrix type, including non-encapsulated padding. </summary>
		static constexpr std::size_t full_width_size = full_width_major_size * num_major_elements;
		/// <summary> The number of elements that pointers are expected to point to when using default loads with this Matrix type. </summary>
		static constexpr std::size_t expected_count_for_default_load_pointer =
		(
			((num_major_elements - 1) * num_non_major_elements) + full_width_major_size
		);

		using major_chunk_type = typename std::conditional<(num_registers_per_major <= 1), register_type, std::array<register_type, num_registers_per_major>>::type;
		using data_type = std::array<major_chunk_type, num_major_elements>;
		using major_index_sequence = std::make_index_sequence<num_major_elements>;
		using major_register_sequence = std::make_index_sequence<num_registers_per_major>;
#pragma endregion

#pragma region STATIC_HELPER_FUNCTIONS
	public:
		static constexpr inline register_type make_zero_register()
		{
			return EmuSIMD::setzero<register_type>();
		}
#pragma endregion

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
			constexpr std::size_t per_major_offset = FullWidthOffset_ ? full_width_major_size : num_non_major_elements;
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
				constexpr std::size_t per_major_offset = IncludeNonEncapsulated_ ? full_width_major_size : num_non_major_elements;
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

#pragma region STATIC_CHECK_WRAPPERS
	private:
		template<std::size_t Unused_>
		[[nodiscard]] static constexpr inline bool _is_square()
		{
			return Unused_ >= 0 && (num_columns == num_rows);
		}
#pragma endregion

#pragma region CONSTRUCTORS
	public:
		constexpr inline FastMatrix() noexcept = default;
		constexpr inline FastMatrix(this_type&&) noexcept = default;
		constexpr inline FastMatrix(const this_type&) noexcept = default;

		explicit constexpr inline FastMatrix(data_type&& data_to_move_) noexcept
			: major_chunks(std::move(data_to_move_))
		{
		}

		explicit constexpr inline FastMatrix(const data_type& data_to_copy_) noexcept
			: major_chunks(data_to_copy_)
		{
		}

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
		/// <para>
		///		If padding is required for pointed-to data to meet the constraints, it should be padded at the tail-end
		///		(e.g. for a 2x2 Matrix: [1, 2, 3, 4, padding...]
		/// </para>
		/// </summary>
		/// <param name="p_data_to_load_">Pointer to at least `expected_count_for_default_load_pointer` items of this Matrix's `value_type`.</param>
		explicit constexpr inline FastMatrix(const value_type* p_data_to_load_) noexcept
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
		explicit constexpr inline FastMatrix(ScalarMatrix_&& scalar_matrix_to_load_) noexcept
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
		explicit(num_major_elements == 1) constexpr inline FastMatrix(MajorFastVectors_&&...major_vectors_) noexcept
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
		explicit(num_major_elements == 1) constexpr inline FastMatrix(MajorRegisters_&&...major_order_registers_) noexcept
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
		explicit(sizeof...(Args_) == 1) constexpr inline FastMatrix(Args_&&...args_)
			: major_chunks(_make_data_from_variadic_args(std::forward<Args_>(args_)...))
		{
		}
#pragma endregion

#pragma region GETS
	public:
		[[nodiscard]] constexpr inline register_type* RegistersPointer()
		{
			if constexpr (num_registers_per_major == 1)
			{
				return major_chunks.data();
			}
			else
			{
				return major_chunks[0].data();
			}
		}

		[[nodiscard]] constexpr inline const register_type* RegistersPointer() const
		{
			return const_cast<this_type*>(this)->RegistersPointer();
		}

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

		/// <summary>
		/// <para> Stores this Matrix to the output scalar Matrix. </para>
		/// <para>
		///		Where the `stored_type` of the output Matrix matches this Matrix's `value_type`
		///		shares the same major storage order,
		///		and contiguous storage remaining in the output Matrix allows, optimised stores will be used. 
		///		Otherwise, intermediate data will be stored and then assigned to respective output indices, with conversions performed if necessary.
		/// </para>
		/// <para> 
		///		If `ZeroNonEncapsulated_` is `true`, indices in the output Matrix that are not encapsulated by this Matrix 
		///		will be set to 0 after storing. Otherwise, data will be stored while leaving unaffected indices as-is.
		///		By default, this is `true`.
		/// </para>
		/// <para>
		///		Note that where `ZeroNonEncapsualted_ == false`, the output Matrix will contain non-encapsulated, potentially invalid data, in cases
		///		where the output Matrix is larger than an input Matrix with partial registers (for example, outputting a 3x3 FastMatrix to a 4x4 scalar Matrix).
		/// </para>
		/// </summary>
		/// <param name="out_scalar_matrix_">Scalar Matrix to output to.</param>
		template<bool ZeroNonEncapsulated_ = true, EmuConcepts::EmuMatrix OutMatrix_>
		constexpr inline void Store(OutMatrix_& out_matrix_) const
		{
			EmuMath::Helpers::fast_matrix_store<ZeroNonEncapsulated_>(*this, out_matrix_);
		}

		/// <summary>
		/// <para> Stores this Matrix's data contiguously into the pointed-to memory location. </para>
		/// <para> 
		///		If the pointed-to data is of the same type as this Matrix's `value_type`, it will be stored directly. 
		///		Otherwise, intermediate conversions will be performed on a per-element basis. 
		/// </para>
		/// <para> 
		///		May optionally output the full width of the Matrix's registers instead of only its encapsulated data. 
		///		This can be enabled by setting `FullWidth_` to `true`, which itself defaults to `false`.
		/// </para>
		/// <para>
		///		Where `FullWidth_ == false`: The pointed-to data should have a number of contiguous elements 
		///		equal to at least expected_count_for_default_load_pointer`, which equates to 
		///		`((num_major_elements - 1) * num_non_major_elements) + full_width_major_size`.
		/// </para>
		/// <para>
		///		Where `FullWidth_ == true`, the pointed-to data should have a number of contiguous elements
		///		equal to at least `full_width_size`.
		/// </para>
		/// <para> Failing to meet size constraints is likely to result in illegal memory reads/writes and/or undefined behaviour. </para>
		/// </summary>
		/// <param name="p_out_data_">Pointer to memory meeting described constraints, where the data of this Matrix will be contiguously stored.</param>
		template<bool FullWidth_ = false, typename OutData_>
		requires (!std::is_const_v<OutData_>)
		constexpr inline void Store(OutData_* p_out_data_) const
		{
			EmuMath::Helpers::fast_matrix_store<FullWidth_>(*this, p_out_data_);
		}

		/// <summary>
		/// <para> Stores this Matrix's data into a newly constructed scalar Matrix of the specified type. </para>
		/// <para> Arguments for the output Matrix are all optional, and given in sequential order as per `EmuMath::Matrix` arguments. </para>
		/// <para> 
		///		Omitted arguments will default to the same argument as used to instantiate this FastMatrix, 
		///		except for `OutT_` which will default to this FastMatrix's `value_type`.
		/// </para>
		/// <para> 
		///		If this is being used to assign to an existing scalar Matrix, consider passing a reference to that Matrix instead to 
		///		take advantage of optimised direct-stores and remove potential constructor overhead.
		/// </para>
		/// </summary>
		/// <returns>Scalar EmuMath Matrix of the specified type containing data mimicking this Matrix.</returns>
		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> Store() const
		{
			return EmuMath::Helpers::fast_matrix_store<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(*this);
		}

		template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_> Store() const
		{
			return EmuMath::Helpers::fast_matrix_store<OutNumColumns_, OutNumRows_, value_type, OutColumnMajor_>(*this);
		}

		template<typename OutT_, bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, OutT_, OutColumnMajor_> Store() const
		{
			return EmuMath::Helpers::fast_matrix_store<num_columns, num_rows, OutT_, OutColumnMajor_>(*this);
		}

		template<bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline EmuMath::Matrix<num_columns, num_rows, value_type, OutColumnMajor_> Store() const
		{
			return EmuMath::Helpers::fast_matrix_store<num_columns, num_rows, value_type, OutColumnMajor_>(*this);
		}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	public:
		/// <summary>
		/// <para> Performs a basic addition operation on this Matrix using the passed right-hand operand. </para>
		/// <para> `Rhs_` will be treated in one of the following ways: </para>
		/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
		/// <para> 
		///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
		///		and registers in all major chunks will be used with the respective register of the FastVector.
		/// </para>
		/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
		/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
		/// </summary>
		/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic addition.</param>
		/// <returns>FastMatrix of this type containing the result of a basic addition operation with the passed right-hand-side operand.</returns>
		template<class Rhs_>
		requires EmuConcepts::EmuFastMatrixBasicOpCompatible<this_type, Rhs_>
		[[nodiscard]] constexpr inline this_type Add(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::fast_matrix_add(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs a basic subtraction operation on this Matrix using the passed right-hand operand. </para>
		/// <para> `Rhs_` will be treated in one of the following ways: </para>
		/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
		/// <para> 
		///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
		///		and registers in all major chunks will be used with the respective register of the FastVector.
		/// </para>
		/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
		/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
		/// </summary>
		/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic subtraction.</param>
		/// <returns>FastMatrix of this type containing the result of a basic subtraction operation with the passed right-hand-side operand.</returns>
		template<class Rhs_>
		requires EmuConcepts::EmuFastMatrixBasicOpCompatible<this_type, Rhs_>
		[[nodiscard]] constexpr inline this_type Subtract(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::fast_matrix_subtract(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs a basic multiplication operation on this Matrix using the passed right-hand operand. </para>
		/// <para> This cannot be used to perform a standard multiplication by a Matrix. Use `Multiply` to allow such behaviour. </para>
		/// <para> `Rhs_` will be treated in one of the following ways: </para>
		/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
		/// <para> 
		///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
		///		and registers in all major chunks will be used with the respective register of the FastVector.
		/// </para>
		/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
		/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
		/// </summary>
		/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic multiplication.</param>
		/// <returns>FastMatrix of this type containing the result of a basic multiplication operation with the passed right-hand-side operand.</returns>
		template<class Rhs_>
		requires EmuConcepts::EmuFastMatrixBasicOpCompatible<this_type, Rhs_>
		[[nodiscard]] constexpr inline this_type BasicMultiply(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::fast_matrix_basic_multiply(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs a basic division operation on this Matrix using the passed right-hand operand. </para>
		/// <para> `Rhs_` will be treated in one of the following ways: </para>
		/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
		/// <para> 
		///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
		///		and registers in all major chunks will be used with the respective register of the FastVector.
		/// </para>
		/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
		/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
		/// </summary>
		/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic division.</param>
		/// <returns>FastMatrix of this type containing the result of a basic division operation with the passed right-hand-side operand.</returns>
		template<class Rhs_>
		requires EmuConcepts::EmuFastMatrixBasicOpCompatible<this_type, Rhs_>
		[[nodiscard]] constexpr inline this_type BasicDivide(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::fast_matrix_basic_divide(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs a basic modulo division operation on this Matrix using the passed right-hand operand. </para>
		/// <para> `Rhs_` will be treated in one of the following ways: </para>
		/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
		/// <para> 
		///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
		///		and registers in all major chunks will be used with the respective register of the FastVector.
		/// </para>
		/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
		/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
		/// </summary>
		/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic modulo division.</param>
		/// <returns>FastMatrix of this type containing the result of a basic modulo division operation with the passed right-hand-side operand.</returns>
		template<class Rhs_>
		requires EmuConcepts::EmuFastMatrixBasicOpCompatible<this_type, Rhs_>
		[[nodiscard]] constexpr inline this_type BasicMod(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::fast_matrix_basic_mod(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Performs a basic fused-multiply-add operation on this Matrix, 
		///		multiplying it by `rhs_` and adding `to_add_` to the intermediate multiplication result.
		/// </para>
		/// <para> `Rhs_` and `ToAdd_` will be treated in one of the following ways: </para>
		/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
		/// <para> 
		///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
		///		and registers in all major chunks will be used with the respective register of the FastVector.
		/// </para>
		/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
		/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
		/// </summary>
		/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic multiplication.</param>
		/// <param name="to_add_">One of the several described argument types, which will be added to intermediate multiplication results.</param>
		/// <returns>FastMatrix of this type containing the result of a basic fused-multiply-add operation with the passed right-hand-side operand.</returns>
		template<class Rhs_, class ToAdd_>
		requires EmuConcepts::EmuFastMatrixBasicOpCompatible<this_type, Rhs_, ToAdd_>
		[[nodiscard]] constexpr inline this_type BasicFmadd(Rhs_&& rhs_, ToAdd_&& to_add_) const
		{
			return EmuMath::Helpers::fast_matrix_basic_fmadd(*this, std::forward<Rhs_>(rhs_), std::forward<ToAdd_>(to_add_));
		}

		/// <summary>
		/// <para>
		///		Performs a basic fused-multiply-subtract operation on this Matrix, 
		///		multiplying it by `rhs_` and adding `to_add_` to the intermediate multiplication result.
		/// </para>
		/// <para> `Rhs_` and `ToSubtract_` will be treated in one of the following ways: </para>
		/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
		/// <para> 
		///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
		///		and registers in all major chunks will be used with the respective register of the FastVector.
		/// </para>
		/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
		/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
		/// </summary>
		/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic multiplication.</param>
		/// <param name="to_subtract_">One of the several described argument types, which will be subtracted from intermediate multiplication results.</param>
		/// <returns>FastMatrix of this type containing the result of a basic fused-multiply-subtract operation with the passed right-hand-side operand.</returns>
		template<class Rhs_, class ToSubtract_>
		requires EmuConcepts::EmuFastMatrixBasicOpCompatible<this_type, Rhs_, ToSubtract_>
		[[nodiscard]] constexpr inline this_type BasicFmsub(Rhs_&& rhs_, ToSubtract_&& to_subtract_) const
		{
			return EmuMath::Helpers::fast_matrix_basic_fmsub(*this, std::forward<Rhs_>(rhs_), std::forward<ToSubtract_>(to_subtract_));
		}
#pragma endregion

#pragma region STD_ARITHMETIC
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

		/// <summary>
		/// <para> Performs a basic multiplication operation on this Matrix using the passed right-hand, non-Matrix operand. </para>
		/// <para> This cannot be used to perform a basic, non-standard multiplication by a Matrix. Use `BasicMultiply` to allow such behaviour. </para>
		/// <para> `Rhs_` will be treated in one of the following ways: </para>
		/// <para> 
		///		--- 1: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
		///		and registers in all major chunks will be used with the respective register of the FastVector.
		/// </para>
		/// <para> --- 2: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
		/// <para> --- 3: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
		/// </summary>
		/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic multiplication.</param>
		/// <returns>FastMatrix of this type containing the result of a basic multiplication operation with the passed right-hand-side operand.</returns>
		template<class Rhs_>
		requires (!(EmuConcepts::EmuFastMatrix<Rhs_>) && EmuConcepts::EmuFastMatrixBasicOpCompatible<this_type, Rhs_>)
		[[nodiscard]] constexpr inline this_type Multiply(Rhs_&& rhs_) const
		{
			return EmuMath::Helpers::fast_matrix_basic_multiply(*this, std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region BASIC_ARITHMETIC_ASSIGN
	public:
		/// <summary>
		/// <para> Performs a basic addition operation on this Matrix using the passed right-hand operand. </para>
		/// <para> Results are assigned to this Matrix. </para>
		/// <para> `Rhs_` will be treated in one of the following ways: </para>
		/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
		/// <para> 
		///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
		///		and registers in all major chunks will be used with the respective register of the FastVector.
		/// </para>
		/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
		/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
		/// </summary>
		/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic addition.</param>
		template<class Rhs_>
		requires EmuConcepts::EmuFastMatrixBasicOpCompatible<this_type, Rhs_>
		constexpr inline void AddAssign(Rhs_&& rhs_)
		{
			EmuMath::Helpers::fast_matrix_add_assign(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs a basic subtraction operation on this Matrix using the passed right-hand operand. </para>
		/// <para> Results are assigned to this Matrix. </para>
		/// <para> `Rhs_` will be treated in one of the following ways: </para>
		/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
		/// <para> 
		///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
		///		and registers in all major chunks will be used with the respective register of the FastVector.
		/// </para>
		/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
		/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
		/// </summary>
		/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic subtraction.</param>
		template<class Rhs_>
		requires EmuConcepts::EmuFastMatrixBasicOpCompatible<this_type, Rhs_>
		constexpr inline void SubtractAssign(Rhs_&& rhs_)
		{
			EmuMath::Helpers::fast_matrix_subtract_assign(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs a basic multiplication operation on this Matrix using the passed right-hand operand. </para>
		/// <para> Results are assigned to this Matrix. </para>
		/// <para> This cannot be used to perform a standard multiplication by a Matrix. Use `Multiply` to allow such behaviour. </para>
		/// <para> `Rhs_` will be treated in one of the following ways: </para>
		/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
		/// <para> 
		///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
		///		and registers in all major chunks will be used with the respective register of the FastVector.
		/// </para>
		/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
		/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
		/// </summary>
		/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic multiplication.</param>
		template<class Rhs_>
		requires EmuConcepts::EmuFastMatrixBasicOpCompatible<this_type, Rhs_>
		constexpr inline void BasicMultiplyAssign(Rhs_&& rhs_)
		{
			EmuMath::Helpers::fast_matrix_basic_multiply_assign(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs a basic division operation on this Matrix using the passed right-hand operand. </para>
		/// <para> Results are assigned to this Matrix. </para>
		/// <para> `Rhs_` will be treated in one of the following ways: </para>
		/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
		/// <para> 
		///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
		///		and registers in all major chunks will be used with the respective register of the FastVector.
		/// </para>
		/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
		/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
		/// </summary>
		/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic division.</param>
		template<class Rhs_>
		requires EmuConcepts::EmuFastMatrixBasicOpCompatible<this_type, Rhs_>
		constexpr inline void BasicDivideAssign(Rhs_&& rhs_)
		{
			EmuMath::Helpers::fast_matrix_basic_divide_assign(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para> Performs a basic modulo division operation on this Matrix using the passed right-hand operand. </para>
		/// <para> Results are assigned to this Matrix. </para>
		/// <para> `Rhs_` will be treated in one of the following ways: </para>
		/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
		/// <para> 
		///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
		///		and registers in all major chunks will be used with the respective register of the FastVector.
		/// </para>
		/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
		/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
		/// </summary>
		/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic modulo division.</param>
		template<class Rhs_>
		requires EmuConcepts::EmuFastMatrixBasicOpCompatible<this_type, Rhs_>
		constexpr inline void BasicModAssign(Rhs_&& rhs_)
		{
			EmuMath::Helpers::fast_matrix_basic_mod_assign(*this, std::forward<Rhs_>(rhs_));
		}

		/// <summary>
		/// <para>
		///		Performs a basic fused-multiply-add operation on this Matrix, 
		///		multiplying it by `rhs_` and adding `to_add_` to the intermediate multiplication result.
		/// </para>
		/// <para> Results are assigned to this Matrix. </para>
		/// <para> `Rhs_` and `ToAdd_` will be treated in one of the following ways: </para>
		/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
		/// <para> 
		///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
		///		and registers in all major chunks will be used with the respective register of the FastVector.
		/// </para>
		/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
		/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
		/// </summary>
		/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic multiplication.</param>
		/// <param name="to_add_">One of the several described argument types, which will be added to intermediate multiplication results.</param>
		template<class Rhs_, class ToAdd_>
		requires EmuConcepts::EmuFastMatrixBasicOpCompatible<this_type, Rhs_, ToAdd_>
		constexpr inline void BasicFmaddAssign(Rhs_&& rhs_, ToAdd_&& to_add_)
		{
			EmuMath::Helpers::fast_matrix_basic_fmadd_assign(*this, std::forward<Rhs_>(rhs_), std::forward<ToAdd_>(to_add_));
		}

		/// <summary>
		/// <para>
		///		Performs a basic fused-multiply-subtract operation on this Matrix, 
		///		multiplying it by `rhs_` and adding `to_add_` to the intermediate multiplication result.
		/// </para>
		/// <para> Results are assigned to this Matrix. </para>
		/// <para> `Rhs_` and `ToSubtract_` will be treated in one of the following ways: </para>
		/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
		/// <para> 
		///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
		///		and registers in all major chunks will be used with the respective register of the FastVector.
		/// </para>
		/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
		/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
		/// </summary>
		/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic multiplication.</param>
		/// <param name="to_subtract_">One of the several described argument types, which will be subtracted from intermediate multiplication results.</param>
		template<class Rhs_, class ToSubtract_>
		requires EmuConcepts::EmuFastMatrixBasicOpCompatible<this_type, Rhs_, ToSubtract_>
		constexpr inline void BasicFmsubAssign(Rhs_&& rhs_, ToSubtract_&& to_subtract_)
		{
			EmuMath::Helpers::fast_matrix_basic_fmsub_assign(*this, std::forward<Rhs_>(rhs_), std::forward<ToSubtract_>(to_subtract_));
		}
#pragma endregion

#pragma region STD_ARITHMETIC_ASSIGN
	public:
		/// <summary>
		/// <para> Standard Matrix * Matrix multiplication function for use with instances of EmuMath::FastMatrix. </para>
		/// <para> This is only available where the two passed Matrices encapsulate data that is exactly valid for a standard Matrix multiplication. </para>
		/// <para> Furthermore, the resulting Matrix type of the given multiplication must be the same type as the `lhs_` Matrix. </para>
		/// </summary>
		/// <param name="lhs_fast_matrix_">FastMatrix appearing on the left-hand side of standard Matrix multiplication. Results will be assigned to this.</param>
		/// <param name="rhs_fast_matrix_">FastMatrix appearing on the right-hand side of standard Matrix multiplication.</param>
		template<EmuConcepts::EmuFastMatrix RhsFastMatrix_>
		requires
		(
			(EmuConcepts::EmuFastMatrixMultPair<this_type, RhsFastMatrix_>) &&
			std::is_same_v<this_type, typename EmuMath::TMP::fast_matrix_multiply_result<this_type, RhsFastMatrix_>::type>
		)
		constexpr inline void MultiplyAssign(RhsFastMatrix_&& rhs_fast_matrix_)
		{
			EmuMath::Helpers::fast_matrix_multiply_assign(*this, std::forward<RhsFastMatrix_>(rhs_fast_matrix_));
		}

		/// <summary>
		/// <para> Performs a basic multiplication operation on this Matrix using the passed right-hand operand. </para>
		/// <para> Results are assigned to this Matrix. </para>
		/// <para> 
		///		This cannot be used to perform a basic, non-standard multiplication by a Matrix. 
		///		Use `fast_matrix_basic_multiply_assign` to allow such behaviour.
		/// </para>
		/// <para> `Rhs_` will be treated in one of the following ways: </para>
		/// <para> 
		///		--- 1: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
		///		and registers in all major chunks will be used with the respective register of the FastVector.
		/// </para>
		/// <para> --- 2: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
		/// <para> --- 3: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
		/// </summary>
		/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic multiplication.</param>
		template<class Rhs_>
		requires (!(EmuConcepts::EmuFastMatrix<Rhs_>) && (EmuConcepts::EmuFastMatrixBasicOpCompatible<this_type, Rhs_>))
		constexpr inline void MultiplyAssign(Rhs_&& rhs_)
		{
			EmuMath::Helpers::fast_matrix_multiply_assign(*this, std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region ASSIGNMENT_OPERATORS
	public:
		constexpr inline this_type& operator=(const this_type&) = default;
		constexpr inline this_type& operator=(this_type&&) = default;
#pragma endregion

#pragma region TRANSPOSITION
	public:
		/// <summary>
		/// <para> Outputs the transposed form of this FastMatrix. </para>
		/// <para>
		///		Where the output major order is opposite to this Matrix type's major order, this will create a copy of this Matrix's data 
		///		with the opposite major order instead of performing a transposition operation. 
		///		Such cases are effectively a reinterpretation of this Matrix.
		/// </para>
		/// <para>
		///		Where the output major order is the same as this Matrix type, 
		///		transposition operations will attempt to remain in a SIMD context such as via shuffles. 
		///		If there are no specialised behaviours available, this will fall back to a basic store-then-set operation.
		/// </para>
		/// </summary>
		/// <returns>Transposed form of this FastMatrix.</returns>
		template<bool OutColumnMajor_ = is_column_major>
		[[nodiscard]] constexpr inline auto Transpose() const
			-> typename EmuMath::TMP::fast_matrix_transpose_result<this_type, OutColumnMajor_>::type
		{
			return EmuMath::Helpers::fast_matrix_transpose<OutColumnMajor_>(*this);
		}
#pragma endregion

#pragma region IDENTITY
	public:
		[[nodiscard]] static constexpr inline this_type make_identity()
		{
			return EmuMath::Helpers::fast_matrix_identity<this_type>();
		}

		constexpr inline void AssignIdentity()
		{
			EmuMath::Helpers::fast_matrix_assign_identity(*this);
		}
#pragma endregion

#pragma region INVERSE_AND_RELATED
	public:
		/// <summary>
		/// <para> Calculates the inverse of this Matrix. </para>
		/// <para> This can only be used if this Matrix has square dimensions (i.e. it has the same number of columns as it does rows). </para>
		/// <para> This assumes that this Matrix has a valid inverse (i.e. it has a non-0 determinant). </para>
		/// <para> May optionally provide a reference to a scalar or this Matrix's `register_type` to output the determinant to. </para>
		/// </summary>
		/// <returns>Inverse of the passed Matrix.</returns>
		template<std::size_t Unused_ = 0>
		[[nodiscard]] constexpr inline auto Inverse() const
			-> std::enable_if_t<_is_square<Unused_>(), this_type>
		{
			return EmuMath::Helpers::fast_matrix_inverse(*this);
		}

		template<std::size_t Unused_ = 0>
		[[nodiscard]] constexpr inline auto Inverse(register_type& out_determinant_) const
			-> std::enable_if_t<_is_square<Unused_>(), this_type>
		{
			return EmuMath::Helpers::fast_matrix_inverse(*this, out_determinant_);
		}

		template<std::size_t Unused_ = 0, EmuConcepts::Arithmetic DeterminantScalar_>
		requires (!std::is_const_v<DeterminantScalar_>)
		[[nodiscard]] constexpr inline auto Inverse(DeterminantScalar_& out_determinant_) const
			-> std::enable_if_t<_is_square<Unused_>(), this_type>
		{
			return EmuMath::Helpers::fast_matrix_inverse(*this, out_determinant_);
		}
#pragma endregion

#pragma region TRANSLATION
	public:
		/// <summary>
		/// <para> Creates a FastMatrix of this type which can be used to perform a translation by the specified amounts. </para>
		/// <para> May only provide a maximum number of arguments that is less than the number of rows in this Matrix type. </para>
		/// <para> If an axis is omitted, it will be treated as 0 (i.e. no translation in that axis). </para>
		/// </summary>
		/// <param name="translations_">Sequential axis translations to use, starting from the X-axis.</param>
		/// <returns>FastMatrix of this type representing the specified translation.</returns>
		template<EmuConcepts::Arithmetic...Translations_>
		[[nodiscard]] static constexpr inline auto make_translation(Translations_&&...translations_)
			-> std::enable_if_t<(sizeof...(Translations_) < num_rows), this_type>
		{
			return EmuMath::Helpers::fast_matrix_make_translation<this_type>(std::forward<Translations_>(translations_)...);
		}

		/// <summary>
		/// <para> Creates a FastMatrix of this type which can be used to perform a translation by the specified amounts. </para>
		/// <para> If an axis is omitted, it will be treated as 0 (i.e. no translation in that axis). Extra axis arguments will be ignored. </para>
		/// </summary>
		/// <param name="translations_">Tuple of sequential axis translations to use, starting from the X-axis.</param>
		/// <returns>FastMatrix of this type representing the specified translation.</returns>
		template<EmuConcepts::StdTuple TranslationsTuple_>
		[[nodiscard]] static constexpr inline auto make_translation(TranslationsTuple_&& translations_tuple_)
			-> this_type
		{
			return EmuMath::Helpers::fast_matrix_make_translation<this_type>(std::forward<TranslationsTuple_>(translations_tuple_));
		}
#pragma endregion

#pragma region SCALE
	public:
		/// <summary>
		/// <para> Creates a FastMatrix of this type which can be used to perform a scale by the specified amounts. </para>
		/// <para> May only provide a maximum number of arguments that is less than the number of rows in this Matrix type. </para>
		/// <para> If an axis is omitted, it will be treated as 1 (i.e. no scale in that axis). </para>
		/// </summary>
		/// <param name="translations_">Sequential axis scales to use, starting from the X-axis.</param>
		/// <returns>FastMatrix of this type representing the specified scale.</returns>
		template<EmuConcepts::Arithmetic...Translations_>
		[[nodiscard]] static constexpr inline auto make_scale(Translations_&&...translations_)
			-> std::enable_if_t<(sizeof...(Translations_) < num_rows), this_type>
		{
			return EmuMath::Helpers::fast_matrix_make_scale<this_type>(std::forward<Translations_>(translations_)...);
		}

		/// <summary>
		/// <para> Creates a FastMatrix of this type which can be used to perform a scale by the specified amounts. </para>
		/// <para> If an axis is omitted, it will be treated as 1 (i.e. no scale in that axis). Extra axis arguments will be ignored. </para>
		/// </summary>
		/// <param name="translations_">Tuple of sequential axis translations to use, starting from the X-axis.</param>
		/// <returns>FastMatrix of this type representing the specified scale.</returns>
		template<EmuConcepts::StdTuple TranslationsTuple_>
		[[nodiscard]] static constexpr inline auto make_scale(TranslationsTuple_&& translations_tuple_)
			-> this_type
		{
			return EmuMath::Helpers::fast_matrix_make_scale<this_type>(std::forward<TranslationsTuple_>(translations_tuple_));
		}
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
	str_ << EmuMath::Helpers::fast_matrix_store(fast_matrix_);
	return str_;
}

#endif
