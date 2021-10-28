#ifndef EMU_MATH_FAST_NOISE_GEN_FUNCTOR_3D_H_INC_
#define EMU_MATH_FAST_NOISE_GEN_FUNCTOR_3D_H_INC_ 1

#include "_common_noise_gen_functor_includes.h"
#include "../../../SIMDHelpers.h"

namespace EmuMath::Validity
{
	template<class Reg_>
	[[nodiscard]] static constexpr inline bool _assert_fast_noise_3d_valid_register()
	{
		if constexpr (std::is_same_v<__m128, Reg_>)
		{
			return true;
		}
		else
		{
			static_assert(false, "Provided an unsupported register for fast_noise_3d. There is only support for the following floating-point SIMD registers: __m128.");
			return false;
		}
	}
}

namespace EmuMath::Functors
{
	template<EmuMath::NoiseType NoiseType_, class Register_ = __m128>
	struct make_fast_noise_3d
	{
		static_assert(EmuMath::Validity::AssertValidNoiseType<NoiseType_>(), "Invalid NoiseType_ argument provided to EmuMath::Functors::make_fast_noise_3d.");
		static_assert(EmuMath::Validity::_assert_fast_noise_3d_valid_register<Register_>(), "Invalid Register_ type argument provided to EmuMath::Functors::make_fast_noise_3d.");
		constexpr make_fast_noise_3d()
		{
			static_assert(false, "Attempted to construct a make_fast_noise_3d instance for a NoiseType that has not been implemented.");
		}
	};

	template<>
	struct make_fast_noise_3d<EmuMath::NoiseType::PERLIN, __m128>
	{
	public:
		using gradient_type = EmuMath::Vector<3, float>;
		static constexpr std::size_t _num_gradients = 16;
		static constexpr gradient_type _gradients[_num_gradients] =
		{
			gradient_type(1, 1, 0),
			gradient_type(-1, 1, 0),
			gradient_type(1, -1, 0),
			gradient_type(-1, -1, 0),
			gradient_type(1, 0, 1),
			gradient_type(-1, 0, 1),
			gradient_type(1, 0, -1),
			gradient_type(-1, 0, -1),
			gradient_type(0, 1,  1),
			gradient_type(0, -1,  1),
			gradient_type(0, 1, -1),
			gradient_type(0, -1, -1),
			// Filler values for successful bit masking; specific values are used to introduce no directional bias as per Ken Perlin
			gradient_type(1, 1, 0),
			gradient_type(-1, 1, 0),
			gradient_type(0, -1, 1),
			gradient_type(0, -1, -1)
		};
		static constexpr EmuMath::NoisePermutationValue _gradient_mask = 15;

		make_fast_noise_3d() :
			ix_0(),
			ix_1(),
			iy_0(),
			iy_1(),
			iz_0(),
			iz_1(),
			six_128(_mm_set1_ps(6.0f)),
			ten_128(_mm_set1_ps(10.0f)),
			fifteen_128(_mm_set1_ps(15.0f))
		{
		}

		[[nodiscard]] inline __m128 operator()
		(
			__m128 points_x_,
			__m128 points_y_,
			__m128 points_z_,
			__m128 freq_,
			__m128i permutations_mask_128_,
			const EmuMath::NoisePermutations& permutations_
		)
		{
			points_x_ = _mm_mul_ps(points_x_, freq_);
			points_y_ = _mm_mul_ps(points_y_, freq_);
			points_z_ = _mm_mul_ps(points_z_, freq_);

			// temp_0: floor(x)...
			__m128 temp_0_128_ = _mm_floor_ps(points_x_);
			__m128 tx_0_128_ = _mm_sub_ps(points_x_, temp_0_128_);
			__m128i ix_0_128_ = _mm_cvtps_epi32(temp_0_128_);

			// temp_0: floor(y)...
			temp_0_128_ = _mm_floor_ps(points_y_);
			__m128 ty_0_128_ = _mm_sub_ps(points_y_, temp_0_128_);
			__m128i iy_0_128_ = _mm_cvtps_epi32(temp_0_128_);

			// temp_0: floor(z)...
			temp_0_128_ = _mm_floor_ps(points_z_);
			__m128 tz_0_128_ = _mm_sub_ps(points_z_, temp_0_128_);
			__m128i iz_0_128_ = _mm_cvtps_epi32(temp_0_128_);

			// Get secondary lerp weightings
			// --- temp_0: { 1, 1, 1, 1 }
			temp_0_128_ = _mm_set1_ps(1.0f);
			__m128 tx_1_128_ = _mm_sub_ps(tx_0_128_, temp_0_128_);
			__m128 ty_1_128_ = _mm_sub_ps(ty_0_128_, temp_0_128_);
			__m128 tz_1_128_ = _mm_sub_ps(tz_0_128_, temp_0_128_);

			// Mask and find secondaries to permutation indices
			ix_0_128_ = _mm_and_si128(permutations_mask_128_, ix_0_128_);
			iy_0_128_ = _mm_and_si128(permutations_mask_128_, iy_0_128_);
			iz_0_128_ = _mm_and_si128(permutations_mask_128_, iz_0_128_);
			__m128i one_128i_ = _mm_set1_epi32(1);
			__m128i ix_1_128_ = _mm_and_si128(permutations_mask_128_, _mm_add_epi32(ix_0_128_, one_128i_));
			__m128i iy_1_128_ = _mm_and_si128(permutations_mask_128_, _mm_add_epi32(iy_0_128_, one_128i_));
			__m128i iz_1_128_ = _mm_and_si128(permutations_mask_128_, _mm_add_epi32(iz_0_128_, one_128i_));

			// Store last calculated values first for best chance at a cache hit
			_mm_store_si128(reinterpret_cast<__m128i*>(iz_1.data()), iz_1_128_);
			_mm_store_si128(reinterpret_cast<__m128i*>(iz_0.data()), iz_0_128_);

			_mm_store_si128(reinterpret_cast<__m128i*>(iy_1.data()), iy_1_128_);
			_mm_store_si128(reinterpret_cast<__m128i*>(iy_0.data()), iy_0_128_);

			_mm_store_si128(reinterpret_cast<__m128i*>(ix_1.data()), ix_1_128_);
			_mm_store_si128(reinterpret_cast<__m128i*>(ix_0.data()), ix_0_128_);

			// Find the gradients we'll be making use of in interpolations
			__m128 vals_000_, vals_001_, vals_010_, vals_011_, vals_100_, vals_101_, vals_110_, vals_111_;
			_calculate_values_to_lerp
			(
				permutations_,
				tx_0_128_,
				ty_0_128_,
				tz_0_128_,
				tx_1_128_,
				ty_1_128_,
				tz_1_128_,
				vals_000_,
				vals_001_,
				vals_010_,
				vals_011_,
				vals_100_,
				vals_101_,
				vals_110_,
				vals_111_
			);
			
			tx_0_128_ = _smooth_t(tx_0_128_);
			ty_0_128_ = _smooth_t(ty_0_128_);
			tz_0_128_ = _smooth_t(tz_0_128_);


			// Primary lerps
			__m128 lerp_0_ = EmuMath::SIMD::vector_lerp(vals_000_, vals_100_, tx_0_128_);
			__m128 lerp_1_ = EmuMath::SIMD::vector_lerp(vals_010_, vals_110_, tx_0_128_);
			__m128 lerp_2_ = EmuMath::SIMD::vector_lerp(vals_001_, vals_101_, tx_0_128_);
			__m128 lerp_3_ = EmuMath::SIMD::vector_lerp(vals_011_, vals_111_, tx_0_128_);

			// Secondary lerps
			lerp_0_ = EmuMath::SIMD::vector_lerp(lerp_0_, lerp_1_, ty_0_128_);
			lerp_2_ = EmuMath::SIMD::vector_lerp(lerp_2_, lerp_3_, ty_0_128_);

			// Final tertiary lerp
			return EmuMath::SIMD::vector_lerp(lerp_0_, lerp_2_, tz_0_128_);
		}

	private:
		[[nodiscard]] inline __m128 _smooth_t(__m128 t_) const
		{
			__m128 result_ = _mm_mul_ps(t_, six_128);
			result_ = _mm_sub_ps(result_, fifteen_128);

			result_ = _mm_mul_ps(t_, result_);
			result_ = _mm_add_ps(result_, ten_128);

			__m128 t_cubed_ = _mm_mul_ps(t_, t_);
			t_cubed_ = _mm_mul_ps(t_cubed_, t_);
			return _mm_mul_ps(t_cubed_, result_);
		}

		inline void _calculate_values_to_lerp
		(
			const EmuMath::NoisePermutations& permutations_,
			__m128 tx_0_,
			__m128 ty_0_,
			__m128 tz_0_,
			__m128 tx_1_,
			__m128 ty_1_,
			__m128 tz_1_,
			__m128& vals_000_,
			__m128& vals_001_,
			__m128& vals_010_,
			__m128& vals_011_,
			__m128& vals_100_,
			__m128& vals_101_,
			__m128& vals_110_,
			__m128& vals_111_
		)
		{
			std::size_t perm_000_[4];
			std::size_t perm_001_[4];
			std::size_t perm_010_[4];
			std::size_t perm_011_[4];
			std::size_t perm_100_[4];
			std::size_t perm_101_[4];
			std::size_t perm_110_[4];
			std::size_t perm_111_[4];
			_find_permutations_indices(permutations_, perm_000_, perm_001_, perm_010_, perm_011_, perm_100_, perm_101_, perm_110_, perm_111_);

			// 000
			const std::size_t* perms_ = perm_000_;
			__m128 gradient_ = _make_gradient<0>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_000_ = _mm_mul_ps(gradient_, tx_0_);

			gradient_ = _make_gradient<1>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_000_ = _mm_add_ps(vals_000_, _mm_mul_ps(gradient_, ty_0_));

			gradient_ = _make_gradient<2>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_000_ = _mm_add_ps(vals_000_, _mm_mul_ps(gradient_, tz_0_));

			// 001
			perms_ = perm_001_;
			gradient_ = _make_gradient<0>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_001_ = _mm_mul_ps(gradient_, tx_0_);

			gradient_ = _make_gradient<1>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_001_ = _mm_add_ps(vals_001_, _mm_mul_ps(gradient_, ty_0_));

			gradient_ = _make_gradient<2>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_001_ = _mm_add_ps(vals_001_, _mm_mul_ps(gradient_, tz_1_));

			// 010
			perms_ = perm_010_;
			gradient_ = _make_gradient<0>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_010_ = _mm_mul_ps(gradient_, tx_0_);

			gradient_ = _make_gradient<1>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_010_ = _mm_add_ps(vals_010_, _mm_mul_ps(gradient_, ty_1_));

			gradient_ = _make_gradient<2>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_010_ = _mm_add_ps(vals_010_, _mm_mul_ps(gradient_, tz_0_));

			// 011
			perms_ = perm_011_;
			gradient_ = _make_gradient<0>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_011_ = _mm_mul_ps(gradient_, tx_0_);

			gradient_ = _make_gradient<1>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_011_ = _mm_add_ps(vals_011_, _mm_mul_ps(gradient_, ty_1_));

			gradient_ = _make_gradient<2>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_011_ = _mm_add_ps(vals_011_, _mm_mul_ps(gradient_, tz_1_));

			// 100
			perms_ = perm_100_;
			gradient_ = _make_gradient<0>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_100_ = _mm_mul_ps(gradient_, tx_1_);

			gradient_ = _make_gradient<1>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_100_ = _mm_add_ps(vals_100_, _mm_mul_ps(gradient_, ty_0_));

			gradient_ = _make_gradient<2>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_100_ = _mm_add_ps(vals_100_, _mm_mul_ps(gradient_, tz_0_));

			// 101
			perms_ = perm_101_;
			gradient_ = _make_gradient<0>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_101_ = _mm_mul_ps(gradient_, tx_1_);

			gradient_ = _make_gradient<1>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_101_ = _mm_add_ps(vals_101_, _mm_mul_ps(gradient_, ty_0_));

			gradient_ = _make_gradient<2>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_101_ = _mm_add_ps(vals_101_, _mm_mul_ps(gradient_, tz_1_));

			// 110
			perms_ = perm_110_;
			gradient_ = _make_gradient<0>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_110_ = _mm_mul_ps(gradient_, tx_1_);

			gradient_ = _make_gradient<1>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_110_ = _mm_add_ps(vals_110_, _mm_mul_ps(gradient_, ty_1_));

			gradient_ = _make_gradient<2>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_110_ = _mm_add_ps(vals_110_, _mm_mul_ps(gradient_, tz_0_));

			// 111
			perms_ = perm_111_;
			gradient_ = _make_gradient<0>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_111_ = _mm_mul_ps(gradient_, tx_1_);

			gradient_ = _make_gradient<1>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_111_ = _mm_add_ps(vals_111_, _mm_mul_ps(gradient_, ty_1_));

			gradient_ = _make_gradient<2>(perms_[0], perms_[1], perms_[2], perms_[3]);
			vals_111_ = _mm_add_ps(vals_111_, _mm_mul_ps(gradient_, tz_1_));
		}

		template<std::size_t DimensionIndex_>
		[[nodiscard]] inline __m128 _make_gradient(std::size_t i0_, std::size_t i1_, std::size_t i2_, std::size_t i3_)
		{
			return _mm_set_ps
			(
				_gradients[i3_ & _gradient_mask].at<DimensionIndex_>(),
				_gradients[i2_ & _gradient_mask].at<DimensionIndex_>(),
				_gradients[i1_ & _gradient_mask].at<DimensionIndex_>(),
				_gradients[i0_ & _gradient_mask].at<DimensionIndex_>()
			);
		}

		inline void _find_permutations_indices
		(
			const EmuMath::NoisePermutations& permutations_,
			std::size_t* perm_000_,
			std::size_t* perm_001_,
			std::size_t* perm_010_,
			std::size_t* perm_011_,
			std::size_t* perm_100_,
			std::size_t* perm_101_,
			std::size_t* perm_110_,
			std::size_t* perm_111_
		) const
		{
			std::size_t perm_0_, perm_1_, perm_00_, perm_01_, perm_10_, perm_11_;
			std::size_t mask_ = static_cast<std::size_t>(permutations_.MaxValue());
			for (std::size_t i = 0; i < 4; ++i)
			{
				perm_0_ = static_cast<std::size_t>(permutations_[ix_0[i]]);
				perm_1_ = static_cast<std::size_t>(permutations_[ix_1[i]]);

				perm_00_ = static_cast<std::size_t>(permutations_[(perm_0_ + iy_0[i]) & mask_]);
				perm_01_ = static_cast<std::size_t>(permutations_[(perm_0_ + iy_1[i]) & mask_]);
				perm_10_ = static_cast<std::size_t>(permutations_[(perm_1_ + iy_0[i]) & mask_]);
				perm_11_ = static_cast<std::size_t>(permutations_[(perm_1_ + iy_1[i]) & mask_]);

				*(perm_000_ + i) = static_cast<std::size_t>(permutations_[(perm_00_ + iz_0[i]) & mask_]);
				*(perm_001_ + i) = static_cast<std::size_t>(permutations_[(perm_00_ + iz_1[i]) & mask_]);
				*(perm_010_ + i) = static_cast<std::size_t>(permutations_[(perm_01_ + iz_0[i]) & mask_]);
				*(perm_011_ + i) = static_cast<std::size_t>(permutations_[(perm_01_ + iz_1[i]) & mask_]);
				*(perm_100_ + i) = static_cast<std::size_t>(permutations_[(perm_10_ + iz_0[i]) & mask_]);
				*(perm_101_ + i) = static_cast<std::size_t>(permutations_[(perm_10_ + iz_1[i]) & mask_]);
				*(perm_110_ + i) = static_cast<std::size_t>(permutations_[(perm_11_ + iz_0[i]) & mask_]);
				*(perm_111_ + i) = static_cast<std::size_t>(permutations_[(perm_11_ + iz_1[i]) & mask_]);
			}
		}

		std::array<int, 4> ix_0;
		std::array<int, 4> ix_1;
		std::array<int, 4> iy_0;
		std::array<int, 4> iy_1;
		std::array<int, 4> iz_0;
		std::array<int, 4> iz_1;
		__m128 six_128;
		__m128 ten_128;
		__m128 fifteen_128;
	};
}

#endif
