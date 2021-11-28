#ifndef EMU_MATH_COMMON_FAST_NOISE_GEN_FUNCTOR_INCLUDES_H_INC_
#define EMU_MATH_COMMON_FAST_NOISE_GEN_FUNCTOR_INCLUDES_H_INC_ 1

#include "_common_noise_gen_functor_includes.h"
#include "../../../../EmuSIMD/SIMDHelpers.h"
#include <array>

namespace EmuMath::Functors::_underlying_noise_gen
{
	template<>
	struct perlin_gradients<3, __m128>
	{
	public:
		using underlying_gradients_instance = perlin_gradients<3, float>;
		using gradient_type = typename underlying_gradients_instance::gradient_type;

		static constexpr std::size_t num_gradients = underlying_gradients_instance::num_gradients;
		static constexpr std::size_t mask = underlying_gradients_instance::mask;

		using register_array = std::array<const __m128, num_gradients>;

		/// <summary>
		/// <para> Constructs an array of SIMD 128f registers representing this selection of perlin gradients. </para>
		/// <para> 4D registers are provided, but the gradients are 3D; one index may be duplicated, which defaults to Z but may be customised via the template arg. </para>
		/// <para> SpareIndex_ args: 0 = X, 1 = Y, 2 = Z. </para>
		/// </summary>
		/// <returns>Array of registers representing this selection of perlin gradients.</returns>
		template<std::size_t SpareIndex_ = 2>
		[[nodiscard]] static inline register_array init_registers()
		{
			if constexpr (SpareIndex_ <= 2)
			{
				return
				{
					_set_register<0, 1, 2, SpareIndex_>(underlying_gradients_instance::values[0]),
					_set_register<0, 1, 2, SpareIndex_>(underlying_gradients_instance::values[1]),
					_set_register<0, 1, 2, SpareIndex_>(underlying_gradients_instance::values[2]),
					_set_register<0, 1, 2, SpareIndex_>(underlying_gradients_instance::values[3]),
					_set_register<0, 1, 2, SpareIndex_>(underlying_gradients_instance::values[4]),
					_set_register<0, 1, 2, SpareIndex_>(underlying_gradients_instance::values[5]),
					_set_register<0, 1, 2, SpareIndex_>(underlying_gradients_instance::values[6]),
					_set_register<0, 1, 2, SpareIndex_>(underlying_gradients_instance::values[7]),
					_set_register<0, 1, 2, SpareIndex_>(underlying_gradients_instance::values[8]),
					_set_register<0, 1, 2, SpareIndex_>(underlying_gradients_instance::values[9]),
					_set_register<0, 1, 2, SpareIndex_>(underlying_gradients_instance::values[10]),
					_set_register<0, 1, 2, SpareIndex_>(underlying_gradients_instance::values[11]),
					_set_register<0, 1, 2, SpareIndex_>(underlying_gradients_instance::values[12]),
					_set_register<0, 1, 2, SpareIndex_>(underlying_gradients_instance::values[13]),
					_set_register<0, 1, 2, SpareIndex_>(underlying_gradients_instance::values[14]),
					_set_register<0, 1, 2, SpareIndex_>(underlying_gradients_instance::values[15])
				};
			}
			else
			{
				static_assert(false, "Provided an invalid Index_ arg to perlin_gradients<3, __m128>::init_registers. Valid indices are: 0, 1, 2.");
				return register_array();
			}
		}

	private:
		template<std::size_t X_, std::size_t Y_, std::size_t Z_, std::size_t W_>
		[[nodiscard]] static inline __m128 _set_register(const gradient_type& scalar_)
		{
			return EmuSIMD::set<__m128>(scalar_.at<W_>(), scalar_.at<Z_>(), scalar_.at<Y_>(), scalar_.at<X_>());
		}
	};

	template<>
	struct perlin_gradients<2, __m128>
	{
	public:
		using underlying_gradients_instance = perlin_gradients<2, float>;
		using gradient_type = typename underlying_gradients_instance::gradient_type;

		static constexpr std::size_t num_gradients = underlying_gradients_instance::num_gradients;
		static constexpr std::size_t mask = underlying_gradients_instance::mask;

		using register_array = std::array<const __m128, num_gradients>;

		/// <summary>
		/// <para> Constructs an array of SIMD 128f registers representing this selection of perlin gradients. </para>
		/// <para> 4D registers are provided, but the gradients are 2D; two indices may be duplicated, which default to XY but may be customised via the template args. </para>
		/// <para> SpareZ_ and SpareW_ args: 0 = X, 1 = Y </para>
		/// </summary>
		/// <returns>Array of registers representing this selection of perlin gradients.</returns>
		template<std::size_t SpareZ_ = 0, std::size_t SpareW_ = 1>
		[[nodiscard]] static inline register_array init_registers()
		{
			if constexpr (SpareZ_ <= 1)
			{
				if constexpr (SpareW_ <= 1)
				{
					return
					{
						_set_register<0, 1, SpareZ_, SpareW_>(underlying_gradients_instance::values[0]),
						_set_register<0, 1, SpareZ_, SpareW_>(underlying_gradients_instance::values[1]),
						_set_register<0, 1, SpareZ_, SpareW_>(underlying_gradients_instance::values[2]),
						_set_register<0, 1, SpareZ_, SpareW_>(underlying_gradients_instance::values[3]),
						_set_register<0, 1, SpareZ_, SpareW_>(underlying_gradients_instance::values[4]),
						_set_register<0, 1, SpareZ_, SpareW_>(underlying_gradients_instance::values[5]),
						_set_register<0, 1, SpareZ_, SpareW_>(underlying_gradients_instance::values[6]),
						_set_register<0, 1, SpareZ_, SpareW_>(underlying_gradients_instance::values[7])
					};
				}
				else
				{
					static_assert(false, "Provided an invalid SpareW_ arg to perlin_gradients<2, __m128>::init_registers. Valid indices are: 0, 1.");
				}
			}
			else
			{
				static_assert(false, "Provided an invalid SpareZ_ arg to perlin_gradients<2, __m128>::init_registers. Valid indices are: 0, 1.");
				return register_array();
			}
		}

	private:
		template<std::size_t X_, std::size_t Y_, std::size_t Z_, std::size_t W_>
		[[nodiscard]] static inline __m128 _set_register(const gradient_type& scalar_)
		{
			return EmuSIMD::set<__m128>(scalar_.at<W_>(), scalar_.at<Z_>(), scalar_.at<Y_>(), scalar_.at<X_>());
		}
	};

	template<>
	struct perlin_gradients<1, __m128>
	{
	public:
		using underlying_gradients_instance = perlin_gradients<1, float>;
		using gradient_type = typename underlying_gradients_instance::gradient_type;

		static constexpr std::size_t num_gradients = underlying_gradients_instance::num_gradients;
		static constexpr std::size_t mask = underlying_gradients_instance::mask;

		using register_array = std::array<const __m128, num_gradients>;

		/// <summary>
		/// <para> Constructs an array of SIMD 128f registers representing this selection of perlin gradients. </para>
		/// <para> 4D registers are provided, but the gradients are 1D; two indices may be duplicated, all indices will be the same. </para>
		/// <para> May alternatively provide 4 index arguments to form a register formed from the respective gradients. </para>
		/// </summary>
		/// <returns>Array of registers representing this selection of perlin gradients.</returns>
		[[nodiscard]] static inline register_array init_registers()
		{
			return
			{
				EmuSIMD::set1<__m128>(underlying_gradients_instance::values[0].at<0>()),
				EmuSIMD::set1<__m128>(underlying_gradients_instance::values[1].at<0>()),
			};
		}
		[[nodiscard]] static inline __m128 init_registers(std::size_t x_, std::size_t y_, std::size_t z_, std::size_t w_)
		{
			return EmuSIMD::set<__m128>
			(
				underlying_gradients_instance::values[w_].at<0>(),
				underlying_gradients_instance::values[z_].at<0>(),
				underlying_gradients_instance::values[y_].at<0>(),
				underlying_gradients_instance::values[x_].at<0>()
			);
		}
	};

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
