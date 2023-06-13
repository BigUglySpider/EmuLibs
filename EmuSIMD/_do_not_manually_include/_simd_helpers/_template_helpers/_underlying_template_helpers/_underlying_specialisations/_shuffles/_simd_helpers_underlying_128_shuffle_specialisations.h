#ifndef EMU_SIMD_HELPERS_UNDERLYING_SHUFFLE_SPECIALISATIONS_128_H_INC_
#define EMU_SIMD_HELPERS_UNDERLYING_SHUFFLE_SPECIALISATIONS_128_H_INC_ 1

#include "../../_simd_helpers_underlying_shuffle.h"

namespace EmuSIMD::_underlying_simd_helpers
{
#if EMU_CORE_X86_X64 // TODO: standardise the used functions in the EmuSIMD::Funcs namespace
	template<>
	struct _permuter<EmuSIMD::f32x4, 0, 0, 2, 2>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::f32x4> AB_>
		[[nodiscard]] static inline EmuSIMD::f32x4 execute(AB_&& ab_)
		{
			return _mm_moveldup_ps(std::forward<AB_>(ab_));
		}
	};

	template<>
	struct _permuter<EmuSIMD::f32x4, 1, 1, 3, 3>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::f32x4> AB_>
		[[nodiscard]] static inline EmuSIMD::f32x4 execute(AB_&& ab_)
		{
			return _mm_movehdup_ps(std::forward<AB_>(ab_));
		}
	};
#endif

	template<>
	struct _permuter<EmuSIMD::f32x4, 0, 1, 0, 1>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::f32x4> AB_>
		[[nodiscard]] static inline EmuSIMD::f32x4 execute(AB_&& ab_)
		{
			const auto& ab_ref = std::forward<AB_>(ab_);
			return EmuSIMD::Funcs::movelh_f32x4(ab_ref, ab_ref);
		}
	};

	template<>
	struct _shuffler<EmuSIMD::f32x4, EmuSIMD::f32x4, 0, 0, 2, 2>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::f32x4> A_, EmuConcepts::UnqualifiedMatch<A_> B_>
		[[nodiscard]] static inline EmuSIMD::f32x4 execute(A_&& a_,B_&& b_)
		{
			return EmuSIMD::Funcs::movelh_f32x4(std::forward<A_>(a_), std::forward<B_>(b_));
		}
	};

	template<>
	struct _permuter<EmuSIMD::i32x4, 0, 1, 0, 1>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::i32x4> AB_>
		[[nodiscard]] static inline EmuSIMD::i32x4 execute(AB_&& ab_)
		{
			const auto& ab_ref = std::forward<AB_>(ab_);
			return EmuSIMD::Funcs::movelh_f32x4(ab_ref, ab_ref);
		}
	};
	
	template<>
	struct _shuffler<EmuSIMD::i32x4, EmuSIMD::i32x4, 0, 0, 2, 2>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::i32x4> A_, EmuConcepts::UnqualifiedMatch<A_> B_>
		[[nodiscard]] static inline EmuSIMD::i32x4 execute(A_&& a_, B_&& b_)
		{
			return EmuSIMD::Funcs::movelh_i32x4(std::forward<A_>(a_), std::forward<B_>(b_));
		}
	};
#if !EMU_SIMD_USE_GENERIC_INT_REGISTERS
	template<>
	struct _permuter<EmuSIMD::u32x4, 0, 1, 0, 1>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::u32x4> AB_>
		[[nodiscard]] static inline EmuSIMD::u32x4 execute(AB_&& ab_)
		{
			const auto& ab_ref = std::forward<AB_>(ab_);
			return EmuSIMD::Funcs::movelh_u32x4(ab_ref, ab_ref);
		}
	};

	template<>
	struct _shuffler<EmuSIMD::u32x4, EmuSIMD::u32x4, 0, 0, 2, 2>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::u32x4> A_, EmuConcepts::UnqualifiedMatch<A_> B_>
		[[nodiscard]] static inline EmuSIMD::u32x4 execute(A_&& a_, B_&& b_)
		{
			return EmuSIMD::Funcs::movelh_u32x4(std::forward<A_>(a_), std::forward<B_>(b_));
		}
	};
#endif

	template<>
	struct _permuter<EmuSIMD::f32x4, 2, 3, 2, 3>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::f32x4> AB_>
		[[nodiscard]] static inline EmuSIMD::f32x4 execute(AB_&& ab_)
		{
			const auto& ab_ref = std::forward<AB_>(ab_);
			return EmuSIMD::Funcs::movehl_f32x4(ab_ref, ab_ref);
		}
	};

	template<>
	struct _shuffler<EmuSIMD::f32x4, EmuSIMD::f32x4, 2, 3, 2, 3>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::f32x4> A_, EmuConcepts::UnqualifiedMatch<A_> B_>
		[[nodiscard]] static inline EmuSIMD::f32x4 execute(A_&& a_, B_&& b_)
		{
			return EmuSIMD::Funcs::movehl_f32x4(std::forward<B_>(b_), std::forward<A_>(a_));
		}
	};

	template<>
	struct _permuter<EmuSIMD::i32x4, 2, 3, 2, 3>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::i32x4> AB_>
		[[nodiscard]] static inline EmuSIMD::i32x4 execute(AB_&& ab_)
		{
			const auto& ab_ref = std::forward<AB_>(ab_);
			return EmuSIMD::Funcs::movehl_i32x4(ab_ref, ab_ref);
		}
	};

	template<>
	struct _shuffler<EmuSIMD::i32x4, EmuSIMD::i32x4, 2, 3, 2, 3>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::i32x4> A_, EmuConcepts::UnqualifiedMatch<A_> B_>
		[[nodiscard]] static inline EmuSIMD::i32x4 execute(A_&& a_, B_&& b_)
		{
			return EmuSIMD::Funcs::movehl_i32x4(std::forward<B_>(b_), std::forward<A_>(a_));
		}
	};
#if !EMU_SIMD_USE_GENERIC_INT_REGISTERS
	template<>
	struct _permuter<EmuSIMD::u32x4, 2, 3, 2, 3>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::u32x4> AB_>
		[[nodiscard]] static inline EmuSIMD::u32x4 execute(AB_&& ab_)
		{
			const auto& ab_ref = std::forward<AB_>(ab_);
			return EmuSIMD::Funcs::movehl_u32x4(ab_ref, ab_ref);
		}
	};
	
	template<>
	struct _shuffler<EmuSIMD::u32x4, EmuSIMD::u32x4, 2, 3, 2, 3>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::u32x4> A_, EmuConcepts::UnqualifiedMatch<A_> B_>
		[[nodiscard]] static inline EmuSIMD::u32x4 execute(A_&& a_, B_&& b_)
		{
			return EmuSIMD::Funcs::movehl_u32x4(std::forward<B_>(b_), std::forward<A_>(a_));
		}
	};
#endif

	template<>
	struct _permuter<EmuSIMD::f32x4, 0, 1, 2, 3>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::f32x4> AB_>
		[[nodiscard]] static inline EmuSIMD::f32x4 execute(AB_&& ab_)
		{
			return std::forward<AB_>(ab_);
		}
	};
	template<>
	struct _permuter<EmuSIMD::f64x2, 0, 1>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::f64x2> AB_>
		[[nodiscard]] static inline EmuSIMD::f64x2 execute(AB_&& ab_)
		{
			return std::forward<AB_>(ab_);
		}
	};

	template<>
	struct _permuter<EmuSIMD::i8x16, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::i8x16> AB_>
		[[nodiscard]] static inline EmuSIMD::i8x16 execute(AB_&& ab_)
		{
			return std::forward<AB_>(ab_);
		}
	};
	template<>
	struct _permuter<EmuSIMD::i16x8, 0, 1, 2, 3, 4, 5, 6, 7>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::i16x8> AB_>
		[[nodiscard]] static inline EmuSIMD::i16x8 execute(AB_&& ab_)
		{
			return std::forward<AB_>(ab_);
		}
	};
	template<>
	struct _permuter<EmuSIMD::i32x4, 0, 1, 2, 3>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::i32x4> AB_>
		[[nodiscard]] static inline EmuSIMD::i32x4 execute(AB_&& ab_)
		{
			return std::forward<AB_>(ab_);
		}
	};
	template<>
	struct _permuter<EmuSIMD::i64x2, 0, 1>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::i64x2> AB_>
		[[nodiscard]] static inline EmuSIMD::i64x2 execute(AB_&& ab_)
		{
			return std::forward<AB_>(ab_);
		}
	};
#if !EMU_SIMD_USE_GENERIC_INT_REGISTERS
	template<>
	struct _permuter<EmuSIMD::u8x16, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::u8x16> AB_>
		[[nodiscard]] static inline EmuSIMD::u8x16 execute(AB_&& ab_)
		{
			return std::forward<AB_>(ab_);
		}
	};
	template<>
	struct _permuter<EmuSIMD::u16x8, 0, 1, 2, 3, 4, 5, 6, 7>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::u16x8> AB_>
		[[nodiscard]] static inline EmuSIMD::u16x8 execute(AB_&& ab_)
		{
			return std::forward<AB_>(ab_);
		}
	};
	template<>
	struct _permuter<EmuSIMD::u32x4, 0, 1, 2, 3>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::u32x4> AB_>
		[[nodiscard]] static inline EmuSIMD::u32x4 execute(AB_&& ab_)
		{
			return std::forward<AB_>(ab_);
		}
	};
	template<>
	struct _permuter<EmuSIMD::u64x2, 0, 1>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::u64x2> AB_>
		[[nodiscard]] static inline EmuSIMD::u64x2 execute(AB_&& ab_)
		{
			return std::forward<AB_>(ab_);
		}
	};
#endif

#if EMU_CORE_X86_X64 // TODO: standardise the used functions in the EmuSIMD::Funcs namespace
	template<>
	struct _permuter<EmuSIMD::f64x2, 0, 0>
	{
		template<EmuConcepts::UnqualifiedMatch<EmuSIMD::f64x2> AB_>
		[[nodiscard]] static inline EmuSIMD::f64x2 execute(AB_&& ab_)
		{
			return _mm_movedup_pd(std::forward<AB_>(ab_));
		}
	};
#endif
}
#endif