#ifndef EMU_MATH_COMMON_FAST_NOISE_GEN_FUNCTOR_INCLUDES_H_INC_
#define EMU_MATH_COMMON_FAST_NOISE_GEN_FUNCTOR_INCLUDES_H_INC_ 1

#include "_common_noise_gen_functor_includes.h"
#include "../../../../EmuSIMD/SIMDHelpers.h"

namespace EmuMath::Functors::_underlying_noise_gen
{
	template<class Register_>
	struct _fast_smooth_t
	{
		using register_type = Register_;

		inline _fast_smooth_t() :
			fifteen(EmuSIMD::set1<register_type>(15.0f)),
			six(EmuSIMD::set1<register_type>(6.0f)),
			ten(EmuSIMD::set1<register_type>(10.0f))
		{
		}

		[[nodiscard]] inline register_type operator()(register_type t_) const
		{
			register_type six_fifteen_ten_ = EmuSIMD::set<register_type>(0.0f, 10.0f, 15.0f, 6.0f);
			register_type result_ = EmuSIMD::fmsub(t_, six, fifteen);
			result_ = EmuSIMD::fmadd(t_, result_, ten);

			register_type t_squared_ = EmuSIMD::mul_all(t_, t_);
			return EmuSIMD::mul_all(EmuSIMD::mul_all(t_squared_, t_), result_);
		}

		register_type fifteen;
		register_type six;
		register_type ten;
	};
}

#endif
