#ifndef EMU_MATH_SIMD_HELPER_TEMPLATE_MOVEMASK_H_INC_
#define EMU_MATH_SIMD_HELPER_TEMPLATE_MOVEMASK_H_INC_ 1

#include "_underlying_template_helpers/_simd_helpers_underlying_movemasks.h"

namespace EmuMath::SIMD
{
	/// <summary>
	/// <para> Type used to create a compile-time SIMD movemask with the provided active/inactive bits for respective elements. </para>
	/// </summary>
	/// <typeparam name="Register_">Type of SIMD register to form a movemask for.</typeparam>
	template<class Register_, bool...IndexBits_>
	struct make_movemask
	{
	private:
		using _mask_generator = EmuMath::SIMD::_underlying_simd_helpers::_make_movemask<Register_, IndexBits_...>;
		[[nodiscard]] static constexpr inline bool _is_valid()
		{
			return EmuMath::SIMD::_underlying_simd_helpers::_is_valid_make_movemask_instance<_mask_generator>::value;
		}
		[[nodiscard]] static constexpr inline auto _get_value()
		{
			if constexpr (_is_valid())
			{
				return _mask_generator::value;
			}
			else
			{
				return int(0);
			}
		}
		static_assert
		(
			_is_valid(),
			"Attempted to form a SIMD movemask via EmuMath::SIMD::make_movemask, but the provided number of IndexBits_ was not supported by the provided register. If the provided register is a floating-point register, the number of index bits provided must be equal to 1 or the number of elements within the register. If the provided register is an integral register, the number of index bits provided must be equal to 1, register_width/8, register_width/16, register_width/32, or register_width/64 (where register_width is the bit-width of the register, e.g. 128 for __m128 registers)."
		);


	public:
		/// <summary>
		/// <para> Movemask generated with the provided parameters. </para>
		/// <para> If this item is invalid, the value is guaranteed to be 0; however, a value of 0 does not guarantee an invalid movemask. </para>
		/// <para> Invalid instances of this template will always trigger a static assertion, so this value is always safe to use. </para>
		/// </summary>
		static constexpr auto value = _get_value();
	};
}

#endif
