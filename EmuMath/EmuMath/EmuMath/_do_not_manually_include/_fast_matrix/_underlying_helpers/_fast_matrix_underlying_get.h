#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_GET_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_GET_H_INC_ 1

#include "_fast_matrix_tmp.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
	/// <summary>
	/// <para>
	///		TMP type returned by `_get_matrix_arg_register` when a desired register is out of the contained range 
	///		(if `ReturnRegisterOutOfRange_` is `true`).
	/// </para>
	/// </summary>
	struct _register_out_of_range
	{
		constexpr inline _register_out_of_range() = default;
	};

	template<typename T_>
	struct _is_register_out_of_range_type : public EmuCore::TMP::type_check_ignore_ref_cv_base<_is_register_out_of_range_type, std::false_type, T_>
	{
	};
	template<>
	struct _is_register_out_of_range_type<_register_out_of_range>
	{
		static constexpr bool value = true;
	};
	template<typename T_>
	static constexpr bool _is_register_out_of_range_type_v = _is_register_out_of_range_type<T_>::value;

	/// <summary>
	/// <para> Helper to retrieve a generic argument register for a FastMatrix operation. </para>
	/// <para> Supports input for FastMatrix, FastVector, EmuSIMD-recognised SIMD registers, and 1D/2D std::arrays of EmuSIMD-recognised SIMD registers. </para>
	/// <para>
	///		If `ReturnRegisterOutOfRange_` is `true`, this will return an item of type `_register_out_of_range` if a register is not contained 
	///		in a multi-register construct. 
	///		If it is `false`, this will instead return a zeroed register associated with the item.
	/// </para>
	/// </summary>
	template<std::size_t MajorIndex_, std::size_t RegisterIndex_, bool ReturnRegisterOutOfRange_, class Arg_>
	[[nodiscard]] constexpr inline decltype(auto) _get_matrix_arg_register(Arg_&& arg_)
	{
		using _arg_unqualified_type = typename EmuCore::TMP::remove_ref_cv<Arg_>::type;
		if constexpr (EmuMath::TMP::is_emu_fast_matrix_v<_arg_unqualified_type>)
		{
			// Respective element in matrix
			if constexpr (MajorIndex_ < _arg_unqualified_type::num_major_elements && RegisterIndex_ < _arg_unqualified_type::num_registers_per_major)
			{
				return std::forward<Arg_>(arg_).template GetRegister<MajorIndex_, RegisterIndex_>();
			}
			else
			{
				if constexpr (ReturnRegisterOutOfRange_)
				{
					return _register_out_of_range();
				}
				else
				{
					return EmuSIMD::setzero<typename _arg_unqualified_type::register_type>();
				}
			}
		}
		else if constexpr (EmuMath::TMP::is_emu_fast_vector_v<_arg_unqualified_type>)
		{
			// Vector treated as a major chunk arg to apply to all majors
			if constexpr (RegisterIndex_ < _arg_unqualified_type::num_registers)
			{
				return std::forward<Arg_>(arg_).template GetRegister<RegisterIndex_>();
			}
			else
			{
				if constexpr (ReturnRegisterOutOfRange_)
				{
					return _register_out_of_range();
				}
				else
				{
					return EmuSIMD::setzero<typename _arg_unqualified_type::register_type>();
				}
			}
		}
		else if constexpr (EmuSIMD::TMP::is_simd_register_v<_arg_unqualified_type>)
		{
			return std::forward<Arg_>(arg_);
		}
		else if constexpr (EmuCore::TMP::is_std_array_v<_arg_unqualified_type>)
		{
			using _arg_array_value_type = typename _arg_unqualified_type::value_type;
			if constexpr (EmuSIMD::TMP::is_simd_register_v<_arg_array_value_type>)
			{
				// Array of registers, treated like a FastVector (i.e. unique to each respective register, but used for every major)
				if constexpr (RegisterIndex_ < _arg_unqualified_type::size())
				{
					return std::get<RegisterIndex_>(std::forward<Arg_>(arg_));
				}
				else
				{
					if constexpr (ReturnRegisterOutOfRange_)
					{
						return _register_out_of_range();
					}
					else
					{
						return EmuSIMD::setzero<_arg_array_value_type>();
					}
				}
			}
			else if constexpr(EmuCore::TMP::is_std_array_v<_arg_array_value_type>)
			{
				using _second_arg_array_value_type = typename _arg_array_value_type::value_type;
				if constexpr (EmuSIMD::TMP::is_simd_register_v<_second_arg_array_value_type>)
				{
					// Array of arrays of registers, treated like a FastMatrix (i.e. use respective indices)
					// --- Array storage is treated as the same major order as FastMatrix default impl., which is arr[Major][Register]
					if constexpr (MajorIndex_ < _arg_unqualified_type::size() && RegisterIndex_ < _arg_array_value_type::size())
					{
						using _major_get_result = decltype(std::get<MajorIndex_>(std::forward<Arg_>(arg_)));
						return std::get<RegisterIndex_>
						(
							std::forward<_major_get_result>(std::get<MajorIndex_>(std::forward<Arg_>(arg_)))
						);
					}
					else
					{
						if constexpr (ReturnRegisterOutOfRange_)
						{
							return _register_out_of_range();
						}
						else
						{
							return EmuSIMD::setzero<_second_arg_array_value_type>();
						}
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Arg_>(),
						"Invalid argument provided for an EmuMath FastMatrix operation requiring a register: The argument was identified as a 2D (at least) std::array, but the `value_type` of the second array's elements is not recognised as a SIMD register by EmuSIMD. Only 1D/2D std::arrays of SIMD registers are valid for this use."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Arg_>(),
					"Invalid argument provided for an EmuMath FastMatrix operation requiring a register: The argument was identified as a 1D std::array, but the `value_type` of the array's elements is not recognised as a SIMD register by EmuSIMD, or a second std::array. Only 1D/2D std::arrays of SIMD registers are valid for this use."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Arg_>(),
				"Invalid argument provided for an EmuMath FastMatrix operation requiring a register: The argument is required to be one of the following: An EmuMath FastMatrix; An EmuMath FastVector; A SIMD register recognised by EmuSIMD; A 1D std::array of SIMD registers recognised by EmuSIMD; A 2D std::array of SIMD registers recognised by EmuSIMD."
			);
		}
	}
}

#endif
