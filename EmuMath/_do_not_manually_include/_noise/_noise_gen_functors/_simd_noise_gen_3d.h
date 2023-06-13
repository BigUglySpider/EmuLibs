#ifndef EMU_MATH_FAST_NOISE_GEN_FUNCTOR_3D_H_INC_
#define EMU_MATH_FAST_NOISE_GEN_FUNCTOR_3D_H_INC_ 1

#include "_common_fast_noise_gen_functors_includes.h"
#include "../../../../EmuSIMD/SIMDHelpers.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

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
			static_assert(EmuCore::TMP::get_false<Reg_>(), "Provided an unsupported register for fast_noise_3d. There is only support for the following floating-point SIMD registers: __m128.");
			return false;
		}
	}
}

namespace EmuMath::Functors
{
	template<EmuMath::NoiseType NoiseType_, class Register_ = __m128>
	struct make_fast_noise_3d
	{
		static_assert(EmuMath::Validity::assert_valid_noise_type<NoiseType_>(), "Invalid NoiseType_ argument provided to EmuMath::Functors::make_fast_noise_3d.");
		static_assert(EmuMath::Validity::_assert_fast_noise_3d_valid_register<Register_>(), "Invalid Register_ type argument provided to EmuMath::Functors::make_fast_noise_3d.");
		constexpr make_fast_noise_3d()
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to construct a make_fast_noise_3d instance for a NoiseType that has not been implemented.");
		}
	};

	template<EmuConcepts::KnownSIMD SIMDRegister_>
	requires((EmuSIMD::TMP::is_floating_point_simd_register_v<SIMDRegister_>))
	struct make_fast_noise_3d<EmuMath::NoiseType::VALUE, SIMDRegister_>
	{
		using register_type = typename std::remove_cvref<SIMDRegister_>::type;
		using int_register_type = typename EmuSIMD::TMP::register_as_integral<register_type>::type;
		using scalar_fp = typename std::conditional
		<
			EmuCore::TMP::is_any_comparison_true<std::is_same, register_type, EmuSIMD::f32x4, EmuSIMD::f32x8, EmuSIMD::f32x16>::value,
			float,
			double
		>::type;
		using scalar_int = typename std::conditional
		<
			EmuCore::TMP::is_any_comparison_true<std::is_same, register_type, EmuSIMD::f32x4, EmuSIMD::f32x8, EmuSIMD::f32x16>::value,
			std::int32_t,
			std::int64_t
		>::type;
		static constexpr std::size_t num_elements_per_register = EmuSIMD::TMP::determine_register_element_count<register_type>();
		static constexpr std::size_t per_element_width = EmuSIMD::TMP::determine_register_per_element_width<register_type>();
		static constexpr bool is_signed = true;

		inline make_fast_noise_3d() : ix(), iy(), iz(), perms_fp()
		{
		}

		[[nodiscard]] inline auto operator()
		(
			register_type points_x_,
			register_type points_y_,
			register_type points_z_,
			typename EmuSIMD::TMP::register_to_arg_type<register_type>::type freq_,
			typename EmuSIMD::TMP::register_to_arg_type<int_register_type>::type permutations_mask_128_,
			const EmuMath::NoisePermutations& permutations_
		) -> register_type
		{
			points_x_ = EmuSIMD::floor(EmuSIMD::mul_all(points_x_, freq_));
			points_y_ = EmuSIMD::floor(EmuSIMD::mul_all(points_y_, freq_));
			points_z_ = EmuSIMD::floor(EmuSIMD::mul_all(points_z_, freq_));

			int_register_type ix_128i_ = EmuSIMD::bitwise_and(EmuSIMD::convert<int_register_type, per_element_width, is_signed, per_element_width, is_signed>(points_x_), permutations_mask_128_);
			int_register_type iy_128i_ = EmuSIMD::bitwise_and(EmuSIMD::convert<int_register_type, per_element_width, is_signed, per_element_width, is_signed>(points_y_), permutations_mask_128_);
			int_register_type iz_128i_ = EmuSIMD::bitwise_and(EmuSIMD::convert<int_register_type, per_element_width, is_signed, per_element_width, is_signed>(points_z_), permutations_mask_128_);

			EmuSIMD::store(iz_128i_, iz.data());
			EmuSIMD::store(iy_128i_, iy.data());
			EmuSIMD::store(ix_128i_, ix.data());

			std::size_t mask_ = static_cast<std::size_t>(permutations_.HighestStoredValue());
			for (std::size_t i = 0; i < num_elements_per_register; ++i)
			{
				std::size_t perm_x_ = static_cast<std::size_t>(permutations_[ix[i]]);
				std::size_t perm_xyz_ = (static_cast<std::size_t>(permutations_[(perm_x_ + iy[i]) & mask_]) + iz[i]) & mask_;
				perms_fp[i] = static_cast<scalar_fp>(permutations_[perm_xyz_]);
			}

			return EmuSIMD::div(EmuSIMD::load<register_type>(perms_fp.data()), EmuSIMD::convert<register_type, per_element_width, is_signed, per_element_width, is_signed>(permutations_mask_128_));
		}

	private:
		std::array<scalar_int, num_elements_per_register> ix;
		std::array<scalar_int, num_elements_per_register> iy;
		std::array<scalar_int, num_elements_per_register> iz;
		std::array<scalar_fp, num_elements_per_register> perms_fp;
	};
	
	template<EmuConcepts::KnownSIMD SIMDRegister_>
	requires((EmuSIMD::TMP::is_floating_point_simd_register_v<SIMDRegister_>))
	struct make_fast_noise_3d<EmuMath::NoiseType::VALUE_SMOOTH, SIMDRegister_>
	{
		using register_type = typename std::remove_cvref<SIMDRegister_>::type;
		using int_register_type = typename EmuSIMD::TMP::register_as_integral<register_type>::type;
		using scalar_fp = typename std::conditional
		<
			EmuCore::TMP::is_any_comparison_true<std::is_same, register_type, EmuSIMD::f32x4, EmuSIMD::f32x8, EmuSIMD::f32x16>::value,
			float,
			double
		>::type;
		using scalar_int = typename std::conditional
		<
			EmuCore::TMP::is_any_comparison_true<std::is_same, register_type, EmuSIMD::f32x4, EmuSIMD::f32x8, EmuSIMD::f32x16>::value,
			std::int32_t,
			std::int64_t
		>::type;
		static constexpr std::size_t num_elements_per_register = EmuSIMD::TMP::determine_register_element_count<register_type>();
		static constexpr std::size_t per_element_width = EmuSIMD::TMP::determine_register_per_element_width<register_type>();
		static constexpr bool is_signed = true;

		inline make_fast_noise_3d() : smooth_t()
		{
		}

		[[nodiscard]] inline auto operator()
		(
			register_type points_x_,
			register_type points_y_,
			register_type points_z_,
			typename EmuSIMD::TMP::register_to_arg_type<register_type>::type freq_,
			typename EmuSIMD::TMP::register_to_arg_type<int_register_type>::type permutations_mask_128_,
			const EmuMath::NoisePermutations& permutations_
		) -> register_type
		{
			points_x_ = EmuSIMD::mul_all(points_x_, freq_);
			points_y_ = EmuSIMD::mul_all(points_y_, freq_);
			points_z_ = EmuSIMD::mul_all(points_z_, freq_);

			// Weightings and start of indices
			register_type tx_ = EmuSIMD::floor(points_x_);
			int_register_type ix_0_128i_ = EmuSIMD::convert<int_register_type, per_element_width, is_signed, per_element_width, is_signed>(tx_);
			tx_ = smooth_t(EmuSIMD::sub(points_x_, tx_));

			register_type ty_ = EmuSIMD::floor(points_y_);
			int_register_type iy_0_128i_ = EmuSIMD::convert<int_register_type, per_element_width, is_signed, per_element_width, is_signed>(ty_);
			ty_ = smooth_t(EmuSIMD::sub(points_y_, ty_));

			register_type tz_ = EmuSIMD::floor(points_z_);
			int_register_type iz_0_128i_ = EmuSIMD::convert<int_register_type, per_element_width, is_signed, per_element_width, is_signed>(tz_);
			tz_ = smooth_t(EmuSIMD::sub(points_z_, tz_));

			// Mask indices and get alternatives to lerp
			ix_0_128i_ = EmuSIMD::bitwise_and(ix_0_128i_, permutations_mask_128_);
			iy_0_128i_ = EmuSIMD::bitwise_and(iy_0_128i_, permutations_mask_128_);
			iz_0_128i_ = EmuSIMD::bitwise_and(iz_0_128i_, permutations_mask_128_);
			int_register_type one_128i_ = EmuSIMD::set1<int_register_type, per_element_width>(1);
			int_register_type iz_1_128i_ = EmuSIMD::bitwise_and(EmuSIMD::add<per_element_width>(iz_0_128i_, one_128i_), permutations_mask_128_);
			int_register_type iy_1_128i_ = EmuSIMD::bitwise_and(EmuSIMD::add<per_element_width>(iy_0_128i_, one_128i_), permutations_mask_128_);
			int_register_type ix_1_128i_ = EmuSIMD::bitwise_and(EmuSIMD::add<per_element_width>(ix_0_128i_, one_128i_), permutations_mask_128_);

			// Store 0 indices
			scalar_int ix_0_[num_elements_per_register];
			scalar_int iy_0_[num_elements_per_register];
			scalar_int iz_0_[num_elements_per_register];
			EmuSIMD::store(ix_0_128i_, ix_0_);
			EmuSIMD::store(iy_0_128i_, iy_0_);
			EmuSIMD::store(iz_0_128i_, iz_0_);

			// Store 1 indices
			scalar_int ix_1_[num_elements_per_register];
			scalar_int iy_1_[num_elements_per_register];
			scalar_int iz_1_[num_elements_per_register];
			EmuSIMD::store(ix_1_128i_, ix_1_);
			EmuSIMD::store(iy_1_128i_, iy_1_);
			EmuSIMD::store(iz_1_128i_, iz_1_);

			scalar_fp perms_000_[num_elements_per_register];
			scalar_fp perms_001_[num_elements_per_register];
			scalar_fp perms_010_[num_elements_per_register];
			scalar_fp perms_011_[num_elements_per_register];
			scalar_fp perms_100_[num_elements_per_register];
			scalar_fp perms_101_[num_elements_per_register];
			scalar_fp perms_110_[num_elements_per_register];
			scalar_fp perms_111_[num_elements_per_register];
			std::size_t mask_ = permutations_.HighestStoredValue();

			for (std::size_t i = 0; i < num_elements_per_register; ++i)
			{
				// Forced store as size_t so we can handle width changes if EmuMath::NoisePermutationValue is not size_t width
				std::size_t perm_0_ = static_cast<std::size_t>(permutations_[ix_0_[i]]);
				std::size_t perm_1_ = static_cast<std::size_t>(permutations_[ix_1_[i]]);

				std::size_t perm_00_ = static_cast<std::size_t>(permutations_[(perm_0_ + iy_0_[i]) & mask_]);
				std::size_t perm_01_ = static_cast<std::size_t>(permutations_[(perm_0_ + iy_1_[i]) & mask_]);
				std::size_t perm_10_ = static_cast<std::size_t>(permutations_[(perm_1_ + iy_0_[i]) & mask_]);
				std::size_t perm_11_ = static_cast<std::size_t>(permutations_[(perm_1_ + iy_1_[i]) & mask_]);

				perms_000_[i] = static_cast<scalar_fp>(permutations_[(perm_00_ + iz_0_[i]) & mask_]);
				perms_001_[i] = static_cast<scalar_fp>(permutations_[(perm_00_ + iz_1_[i]) & mask_]);
				perms_010_[i] = static_cast<scalar_fp>(permutations_[(perm_01_ + iz_0_[i]) & mask_]);
				perms_011_[i] = static_cast<scalar_fp>(permutations_[(perm_01_ + iz_1_[i]) & mask_]);
				perms_100_[i] = static_cast<scalar_fp>(permutations_[(perm_10_ + iz_0_[i]) & mask_]);
				perms_101_[i] = static_cast<scalar_fp>(permutations_[(perm_10_ + iz_1_[i]) & mask_]);
				perms_110_[i] = static_cast<scalar_fp>(permutations_[(perm_11_ + iz_0_[i]) & mask_]);
				perms_111_[i] = static_cast<scalar_fp>(permutations_[(perm_11_ + iz_1_[i]) & mask_]);
			}

			// X-lerps
			register_type lerp_0_ = EmuSIMD::fused_lerp(EmuSIMD::load<register_type>(perms_000_), EmuSIMD::load<register_type>(perms_100_), tx_);
			register_type lerp_1_ = EmuSIMD::fused_lerp(EmuSIMD::load<register_type>(perms_010_), EmuSIMD::load<register_type>(perms_110_), tx_);
			register_type lerp_2_ = EmuSIMD::fused_lerp(EmuSIMD::load<register_type>(perms_001_), EmuSIMD::load<register_type>(perms_101_), tx_);
			register_type lerp_3_ = EmuSIMD::fused_lerp(EmuSIMD::load<register_type>(perms_011_), EmuSIMD::load<register_type>(perms_111_), tx_);

			// Y-lerps
			lerp_0_ = EmuSIMD::fused_lerp(lerp_0_, lerp_1_, ty_);
			lerp_2_ = EmuSIMD::fused_lerp(lerp_2_, lerp_3_, ty_);

			// Final Z-lerp and normalise
			return EmuSIMD::div(EmuSIMD::fused_lerp(lerp_0_, lerp_2_, tz_), EmuSIMD::convert<register_type, per_element_width, is_signed, per_element_width, is_signed>(permutations_mask_128_));
		}

		EmuMath::Functors::_underlying_noise_gen::_fast_smooth_t<register_type> smooth_t;
	};

	//*
	template<EmuConcepts::UnqualifiedMatch<EmuSIMD::f32x4> EmuF32x4>
	struct make_fast_noise_3d<EmuMath::NoiseType::PERLIN, EmuF32x4>
	{
	private:
		using register_type = EmuSIMD::f32x4;
		using int_register_type = EmuSIMD::i32x4;

	public:
		using gradients = EmuMath::Functors::_underlying_noise_gen::perlin_gradients<3, register_type>;

		/// <summary> Gradients for calculation. W index contains a duplicate of the Z index. </summary>
		const typename gradients::register_array _gradients_128;
		static constexpr std::size_t _duplicate_gradient_index = 2;
		static constexpr std::size_t per_element_width = 32;
		static constexpr bool is_signed = true;
		static constexpr std::size_t num_elements_in_register = 4;

		make_fast_noise_3d() :
			smooth_t(),
			ix_0(),
			ix_1(),
			iy_0(),
			iy_1(),
			iz_0(),
			iz_1(),
			_gradients_128(gradients::template init_registers<_duplicate_gradient_index>())
		{
		}

		[[nodiscard]] inline auto operator()
		(
			register_type points_x_,
			register_type points_y_,
			register_type points_z_,
			typename EmuSIMD::TMP::register_as_arg_type<register_type>::type freq_,
			typename EmuSIMD::TMP::register_as_arg_type<int_register_type>::type permutations_mask_128_,
			const EmuMath::NoisePermutations& permutations_
		) -> register_type
		{

			points_x_ = EmuSIMD::mul_all(points_x_, freq_);
			points_y_ = EmuSIMD::mul_all(points_y_, freq_);
			points_z_ = EmuSIMD::mul_all(points_z_, freq_);

			// temp_0: floor(x)...
			register_type temp_0_128_ = EmuSIMD::floor(points_x_);
			register_type tx_0_128_ = EmuSIMD::sub(points_x_, temp_0_128_);
			int_register_type ix_0_128_ = EmuSIMD::convert<int_register_type, per_element_width, is_signed, per_element_width, is_signed>(temp_0_128_); // TODO

			// temp_0: floor(y)...
			temp_0_128_ = EmuSIMD::floor(points_y_);
			register_type ty_0_128_ = EmuSIMD::sub(points_y_, temp_0_128_);
			int_register_type iy_0_128_ = EmuSIMD::convert<int_register_type, per_element_width, is_signed, per_element_width, is_signed>(temp_0_128_);

			// temp_0: floor(z)...
			temp_0_128_ = EmuSIMD::floor(points_z_);
			register_type tz_0_128_ = EmuSIMD::sub(points_z_, temp_0_128_);
			int_register_type iz_0_128_ = EmuSIMD::convert<int_register_type, per_element_width, is_signed, per_element_width, is_signed>(temp_0_128_);

			// Get secondary lerp weightings
			// --- temp_0: { 1, 1, 1, 1 }
			temp_0_128_ = EmuSIMD::set1<register_type>(1.0f);
			register_type tx_1_128_ = EmuSIMD::sub(tx_0_128_, temp_0_128_);
			register_type ty_1_128_ = EmuSIMD::sub(ty_0_128_, temp_0_128_);
			register_type tz_1_128_ = EmuSIMD::sub(tz_0_128_, temp_0_128_);

			// Mask and find secondaries to permutation indices
			ix_0_128_ = EmuSIMD::bitwise_and(permutations_mask_128_, ix_0_128_);
			iy_0_128_ = EmuSIMD::bitwise_and(permutations_mask_128_, iy_0_128_);
			iz_0_128_ = EmuSIMD::bitwise_and(permutations_mask_128_, iz_0_128_);
			int_register_type one_128i_ = EmuSIMD::convert<int_register_type, per_element_width, is_signed, per_element_width, is_signed>(temp_0_128_);
			int_register_type ix_1_128_ = EmuSIMD::bitwise_and(permutations_mask_128_, EmuSIMD::add<per_element_width>(ix_0_128_, one_128i_));
			int_register_type iy_1_128_ = EmuSIMD::bitwise_and(permutations_mask_128_, EmuSIMD::add<per_element_width>(iy_0_128_, one_128i_));
			int_register_type iz_1_128_ = EmuSIMD::bitwise_and(permutations_mask_128_, EmuSIMD::add<per_element_width>(iz_0_128_, one_128i_));

			// Store last calculated values first for best chance at a cache hit
			EmuSIMD::store(iz_1_128_, iz_1.data());
			EmuSIMD::store(iz_0_128_, iz_0.data());

			EmuSIMD::store(iy_1_128_, iy_1.data());
			EmuSIMD::store(iy_0_128_, iy_0.data());

			EmuSIMD::store(ix_1_128_, ix_1.data());
			EmuSIMD::store(ix_0_128_, ix_0.data());

			// Find the gradients we'll be making use of in interpolations
			// --- No benefit from manually inlining this part within the function in release, so best to just keep this function cleaner
			register_type vals_000_, vals_001_, vals_010_, vals_011_, vals_100_, vals_101_, vals_110_, vals_111_;
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
			
			// Apply smooth (or fade) function to our weightings
			tx_0_128_ = smooth_t(tx_0_128_);
			ty_0_128_ = smooth_t(ty_0_128_);
			tz_0_128_ = smooth_t(tz_0_128_);

			// Primary lerps
			// --- Use fused lerps to skip 7 floating-point rounding operations
			register_type lerp_0_ = EmuSIMD::fused_lerp(vals_000_, vals_100_, tx_0_128_);
			register_type lerp_1_ = EmuSIMD::fused_lerp(vals_010_, vals_110_, tx_0_128_);
			register_type lerp_2_ = EmuSIMD::fused_lerp(vals_001_, vals_101_, tx_0_128_);
			register_type lerp_3_ = EmuSIMD::fused_lerp(vals_011_, vals_111_, tx_0_128_);

			// Secondary lerps
			lerp_0_ = EmuSIMD::fused_lerp(lerp_0_, lerp_1_, ty_0_128_);
			lerp_2_ = EmuSIMD::fused_lerp(lerp_2_, lerp_3_, ty_0_128_);

			// Final tertiary lerp
			return EmuSIMD::fused_lerp(lerp_0_, lerp_2_, tz_0_128_);
		}

	private:
		inline void _calculate_values_to_lerp
		(
			const EmuMath::NoisePermutations& permutations_,
			typename EmuSIMD::TMP::register_as_arg_type<register_type>::type tx_0_,
			typename EmuSIMD::TMP::register_as_arg_type<register_type>::type ty_0_,
			typename EmuSIMD::TMP::register_as_arg_type<register_type>::type tz_0_,
			typename EmuSIMD::TMP::register_as_arg_type<register_type>::type tx_1_,
			typename EmuSIMD::TMP::register_as_arg_type<register_type>::type ty_1_,
			typename EmuSIMD::TMP::register_as_arg_type<register_type>::type tz_1_,
			register_type& vals_000_,
			register_type& vals_001_,
			register_type& vals_010_,
			register_type& vals_011_,
			register_type& vals_100_,
			register_type& vals_101_,
			register_type& vals_110_,
			register_type& vals_111_
		)
		{
			// Find our permutation values; all will be initialised in the upcoming loop
			std::size_t perm_000_[num_elements_in_register];
			std::size_t perm_001_[num_elements_in_register];
			std::size_t perm_010_[num_elements_in_register];
			std::size_t perm_011_[num_elements_in_register];
			std::size_t perm_100_[num_elements_in_register];
			std::size_t perm_101_[num_elements_in_register];
			std::size_t perm_110_[num_elements_in_register];
			std::size_t perm_111_[num_elements_in_register];
			std::size_t perm_0_, perm_1_, perm_00_, perm_01_, perm_10_, perm_11_;
			std::size_t mask_ = static_cast<std::size_t>(permutations_.HighestStoredValue());

			// One permutation per value per item; since we're working with 4 outputs, this means we need to loop 4 times
			for (std::size_t i = 0; i < num_elements_in_register; ++i)
			{
				perm_0_ = static_cast<std::size_t>(permutations_[ix_0[i]]);
				perm_1_ = static_cast<std::size_t>(permutations_[ix_1[i]]);

				perm_00_ = static_cast<std::size_t>(permutations_[(perm_0_ + iy_0[i]) & mask_]);
				perm_01_ = static_cast<std::size_t>(permutations_[(perm_0_ + iy_1[i]) & mask_]);
				perm_10_ = static_cast<std::size_t>(permutations_[(perm_1_ + iy_0[i]) & mask_]);
				perm_11_ = static_cast<std::size_t>(permutations_[(perm_1_ + iy_1[i]) & mask_]);

				perm_000_[i] = static_cast<std::size_t>(permutations_[(perm_00_ + iz_0[i]) & mask_]) & gradients::mask;
				perm_001_[i] = static_cast<std::size_t>(permutations_[(perm_00_ + iz_1[i]) & mask_]) & gradients::mask;
				perm_010_[i] = static_cast<std::size_t>(permutations_[(perm_01_ + iz_0[i]) & mask_]) & gradients::mask;
				perm_011_[i] = static_cast<std::size_t>(permutations_[(perm_01_ + iz_1[i]) & mask_]) & gradients::mask;
				perm_100_[i] = static_cast<std::size_t>(permutations_[(perm_10_ + iz_0[i]) & mask_]) & gradients::mask;
				perm_101_[i] = static_cast<std::size_t>(permutations_[(perm_10_ + iz_1[i]) & mask_]) & gradients::mask;
				perm_110_[i] = static_cast<std::size_t>(permutations_[(perm_11_ + iz_0[i]) & mask_]) & gradients::mask;
				perm_111_[i] = static_cast<std::size_t>(permutations_[(perm_11_ + iz_1[i]) & mask_]) & gradients::mask;
			}

			// Use discovered permutations to form gradient dot products for our output values
			// 000
			register_type gradient_0_ = _gradients_128[perm_000_[0]];
			register_type gradient_1_ = _gradients_128[perm_000_[1]];
			register_type gradient_2_ = _gradients_128[perm_000_[2]];
			register_type gradient_3_ = _gradients_128[perm_000_[3]];
			
			// X - Pre-store the Y components in the indices [1] and [3] from each temp shuffle
			register_type temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			register_type temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			register_type row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_000_ = EmuSIMD::mul_all(row_, tx_0_);
			
			// Y - Already prestored Y in previous two shuffles, so we can form row straight away
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_000_ = EmuSIMD::add(vals_000_, EmuSIMD::mul_all(row_, ty_0_));
			
			// Z - One more batch of shuffles to extract the Z-coordinates of the gradients
			// --- We can, however, take advantage of the duplicate Z in the W-element to use blends and a shuffle
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_000_ = EmuSIMD::add(vals_000_, EmuSIMD::mul_all(row_, tz_0_));
			
			// ABOVE COMMENTS APPLY TO SUBSEQUENT OUTPUTS
			// 001
			gradient_0_ = _gradients_128[perm_001_[0]];
			gradient_1_ = _gradients_128[perm_001_[1]];
			gradient_2_ = _gradients_128[perm_001_[2]];
			gradient_3_ = _gradients_128[perm_001_[3]];
			
			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_001_ = EmuSIMD::mul_all(row_, tx_0_);
			
			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_001_ = EmuSIMD::add(vals_001_, EmuSIMD::mul_all(row_, ty_0_));
			
			// Z
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_001_ = EmuSIMD::add(vals_001_, EmuSIMD::mul_all(row_, tz_1_));
			
			// 010
			gradient_0_ = _gradients_128[perm_010_[0]];
			gradient_1_ = _gradients_128[perm_010_[1]];
			gradient_2_ = _gradients_128[perm_010_[2]];
			gradient_3_ = _gradients_128[perm_010_[3]];
			
			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_010_ = EmuSIMD::mul_all(row_, tx_0_);
			
			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_010_ = EmuSIMD::add(vals_010_, EmuSIMD::mul_all(row_, ty_1_));
			
			// Z
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_010_ = EmuSIMD::add(vals_010_, EmuSIMD::mul_all(row_, tz_0_));
			
			// 011
			gradient_0_ = _gradients_128[perm_011_[0]];
			gradient_1_ = _gradients_128[perm_011_[1]];
			gradient_2_ = _gradients_128[perm_011_[2]];
			gradient_3_ = _gradients_128[perm_011_[3]];
			
			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_011_ = EmuSIMD::mul_all(row_, tx_0_);
			
			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_011_ = EmuSIMD::add(vals_011_, EmuSIMD::mul_all(row_, ty_1_));
			
			// Z
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_011_ = EmuSIMD::add(vals_011_, EmuSIMD::mul_all(row_, tz_1_));
			
			// 100
			gradient_0_ = _gradients_128[perm_100_[0]];
			gradient_1_ = _gradients_128[perm_100_[1]];
			gradient_2_ = _gradients_128[perm_100_[2]];
			gradient_3_ = _gradients_128[perm_100_[3]];
			
			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_100_ = EmuSIMD::mul_all(row_, tx_1_);
			
			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_100_ = EmuSIMD::add(vals_100_, EmuSIMD::mul_all(row_, ty_0_));
			
			// Z
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_100_ = EmuSIMD::add(vals_100_, EmuSIMD::mul_all(row_, tz_0_));
			
			// 101
			gradient_0_ = _gradients_128[perm_101_[0]];
			gradient_1_ = _gradients_128[perm_101_[1]];
			gradient_2_ = _gradients_128[perm_101_[2]];
			gradient_3_ = _gradients_128[perm_101_[3]];
			
			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_101_ = EmuSIMD::mul_all(row_, tx_1_);
			
			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_101_ = EmuSIMD::add(vals_101_, EmuSIMD::mul_all(row_, ty_0_));
			
			// Z
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_101_ = EmuSIMD::add(vals_101_, EmuSIMD::mul_all(row_, tz_1_));
			
			// 110
			gradient_0_ = _gradients_128[perm_110_[0]];
			gradient_1_ = _gradients_128[perm_110_[1]];
			gradient_2_ = _gradients_128[perm_110_[2]];
			gradient_3_ = _gradients_128[perm_110_[3]];
			
			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_110_ = EmuSIMD::mul_all(row_, tx_1_);
			
			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_110_ = EmuSIMD::add(vals_110_, EmuSIMD::mul_all(row_, ty_1_));
			
			// Z
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_110_ = EmuSIMD::add(vals_110_, EmuSIMD::mul_all(row_, tz_0_));
			
			// 111
			gradient_0_ = _gradients_128[perm_111_[0]];
			gradient_1_ = _gradients_128[perm_111_[1]];
			gradient_2_ = _gradients_128[perm_111_[2]];
			gradient_3_ = _gradients_128[perm_111_[3]];
			
			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_111_ = EmuSIMD::mul_all(row_, tx_1_);
			
			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_111_ = EmuSIMD::add(vals_111_, EmuSIMD::mul_all(row_, ty_1_));
			
			// Z
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_111_ = EmuSIMD::add(vals_111_, EmuSIMD::mul_all(row_, tz_1_));
		}


		std::array<int, num_elements_in_register> ix_0;
		std::array<int, num_elements_in_register> ix_1;
		std::array<int, num_elements_in_register> iy_0;
		std::array<int, num_elements_in_register> iy_1;
		std::array<int, num_elements_in_register> iz_0;
		std::array<int, num_elements_in_register> iz_1;
		EmuMath::Functors::_underlying_noise_gen::_fast_smooth_t<register_type> smooth_t;
	};

	template<EmuConcepts::UnqualifiedMatch<EmuSIMD::f32x8> EmuF32x8>
	struct make_fast_noise_3d<EmuMath::NoiseType::PERLIN, EmuF32x8>
	{
	private:
		using register_type = EmuSIMD::f32x8;
		using int_register_type = EmuSIMD::i32x8;
		using half_register_type = EmuSIMD::f32x4;

	public:
		using gradients = EmuMath::Functors::_underlying_noise_gen::perlin_gradients<3, half_register_type>;

		/// <summary> Gradients for calculation. W index contains a duplicate of the Z index. </summary>
		const typename gradients::register_array _gradients_128;
		static constexpr std::size_t _duplicate_gradient_index = 2;
		static constexpr std::size_t per_element_width = 32;
		static constexpr bool is_signed = true;
		static constexpr std::size_t num_elements_in_register = 8;

		make_fast_noise_3d() :
			smooth_t(),
			ix_0(),
			ix_1(),
			iy_0(),
			iy_1(),
			iz_0(),
			iz_1(),
			_gradients_128(gradients::template init_registers<_duplicate_gradient_index>())
		{
		}

		[[nodiscard]] inline auto operator()
		(
			register_type points_x_,
			register_type points_y_,
			register_type points_z_,
			typename EmuSIMD::TMP::register_as_arg_type<register_type>::type freq_,
			typename EmuSIMD::TMP::register_as_arg_type<int_register_type>::type permutations_mask_128_,
			const EmuMath::NoisePermutations& permutations_
		) -> register_type
		{

			points_x_ = EmuSIMD::mul_all(points_x_, freq_);
			points_y_ = EmuSIMD::mul_all(points_y_, freq_);
			points_z_ = EmuSIMD::mul_all(points_z_, freq_);

			// temp_0: floor(x)...
			register_type temp_0_128_ = EmuSIMD::floor(points_x_);
			register_type tx_0_128_ = EmuSIMD::sub(points_x_, temp_0_128_);
			int_register_type ix_0_128_ = EmuSIMD::convert<int_register_type, per_element_width, is_signed, per_element_width, is_signed>(temp_0_128_); // TODO

			// temp_0: floor(y)...
			temp_0_128_ = EmuSIMD::floor(points_y_);
			register_type ty_0_128_ = EmuSIMD::sub(points_y_, temp_0_128_);
			int_register_type iy_0_128_ = EmuSIMD::convert<int_register_type, per_element_width, is_signed, per_element_width, is_signed>(temp_0_128_);

			// temp_0: floor(z)...
			temp_0_128_ = EmuSIMD::floor(points_z_);
			register_type tz_0_128_ = EmuSIMD::sub(points_z_, temp_0_128_);
			int_register_type iz_0_128_ = EmuSIMD::convert<int_register_type, per_element_width, is_signed, per_element_width, is_signed>(temp_0_128_);

			// Get secondary lerp weightings
			// --- temp_0: { 1, 1, 1, 1 }
			temp_0_128_ = EmuSIMD::set1<register_type>(1.0f);
			register_type tx_1_128_ = EmuSIMD::sub(tx_0_128_, temp_0_128_);
			register_type ty_1_128_ = EmuSIMD::sub(ty_0_128_, temp_0_128_);
			register_type tz_1_128_ = EmuSIMD::sub(tz_0_128_, temp_0_128_);

			// Mask and find secondaries to permutation indices
			ix_0_128_ = EmuSIMD::bitwise_and(permutations_mask_128_, ix_0_128_);
			iy_0_128_ = EmuSIMD::bitwise_and(permutations_mask_128_, iy_0_128_);
			iz_0_128_ = EmuSIMD::bitwise_and(permutations_mask_128_, iz_0_128_);
			int_register_type one_128i_ = EmuSIMD::convert<int_register_type, per_element_width, is_signed, per_element_width, is_signed>(temp_0_128_);
			int_register_type ix_1_128_ = EmuSIMD::bitwise_and(permutations_mask_128_, EmuSIMD::add<per_element_width>(ix_0_128_, one_128i_));
			int_register_type iy_1_128_ = EmuSIMD::bitwise_and(permutations_mask_128_, EmuSIMD::add<per_element_width>(iy_0_128_, one_128i_));
			int_register_type iz_1_128_ = EmuSIMD::bitwise_and(permutations_mask_128_, EmuSIMD::add<per_element_width>(iz_0_128_, one_128i_));

			// Store last calculated values first for best chance at a cache hit
			EmuSIMD::store(iz_1_128_, iz_1.data());
			EmuSIMD::store(iz_0_128_, iz_0.data());

			EmuSIMD::store(iy_1_128_, iy_1.data());
			EmuSIMD::store(iy_0_128_, iy_0.data());

			EmuSIMD::store(ix_1_128_, ix_1.data());
			EmuSIMD::store(ix_0_128_, ix_0.data());

			// Find the gradients we'll be making use of in interpolations
			// --- No benefit from manually inlining this part within the function in release, so best to just keep this function cleaner
			register_type vals_000_, vals_001_, vals_010_, vals_011_, vals_100_, vals_101_, vals_110_, vals_111_;
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
			
			// Apply smooth (or fade) function to our weightings
			tx_0_128_ = smooth_t(tx_0_128_);
			ty_0_128_ = smooth_t(ty_0_128_);
			tz_0_128_ = smooth_t(tz_0_128_);

			// Primary lerps
			// --- Use fused lerps to skip 7 floating-point rounding operations
			register_type lerp_0_ = EmuSIMD::fused_lerp(vals_000_, vals_100_, tx_0_128_);
			register_type lerp_1_ = EmuSIMD::fused_lerp(vals_010_, vals_110_, tx_0_128_);
			register_type lerp_2_ = EmuSIMD::fused_lerp(vals_001_, vals_101_, tx_0_128_);
			register_type lerp_3_ = EmuSIMD::fused_lerp(vals_011_, vals_111_, tx_0_128_);

			// Secondary lerps
			lerp_0_ = EmuSIMD::fused_lerp(lerp_0_, lerp_1_, ty_0_128_);
			lerp_2_ = EmuSIMD::fused_lerp(lerp_2_, lerp_3_, ty_0_128_);

			// Final tertiary lerp
			return EmuSIMD::fused_lerp(lerp_0_, lerp_2_, tz_0_128_);
		}

	private:
		inline void _calculate_values_to_lerp
		(
			const EmuMath::NoisePermutations& permutations_,
			typename EmuSIMD::TMP::register_as_arg_type<register_type>::type tx_0_,
			typename EmuSIMD::TMP::register_as_arg_type<register_type>::type ty_0_,
			typename EmuSIMD::TMP::register_as_arg_type<register_type>::type tz_0_,
			typename EmuSIMD::TMP::register_as_arg_type<register_type>::type tx_1_,
			typename EmuSIMD::TMP::register_as_arg_type<register_type>::type ty_1_,
			typename EmuSIMD::TMP::register_as_arg_type<register_type>::type tz_1_,
			register_type& vals_000_,
			register_type& vals_001_,
			register_type& vals_010_,
			register_type& vals_011_,
			register_type& vals_100_,
			register_type& vals_101_,
			register_type& vals_110_,
			register_type& vals_111_
		)
		{
			// Find our permutation values; all will be initialised in the upcoming loop
			std::size_t perm_000_[num_elements_in_register];
			std::size_t perm_001_[num_elements_in_register];
			std::size_t perm_010_[num_elements_in_register];
			std::size_t perm_011_[num_elements_in_register];
			std::size_t perm_100_[num_elements_in_register];
			std::size_t perm_101_[num_elements_in_register];
			std::size_t perm_110_[num_elements_in_register];
			std::size_t perm_111_[num_elements_in_register];
			std::size_t perm_0_, perm_1_, perm_00_, perm_01_, perm_10_, perm_11_;
			std::size_t mask_ = static_cast<std::size_t>(permutations_.HighestStoredValue());

			// One permutation per value per item; since we're working with 4 outputs, this means we need to loop 4 times
			for (std::size_t i = 0; i < num_elements_in_register; ++i)
			{
				perm_0_ = static_cast<std::size_t>(permutations_[ix_0[i]]);
				perm_1_ = static_cast<std::size_t>(permutations_[ix_1[i]]);

				perm_00_ = static_cast<std::size_t>(permutations_[(perm_0_ + iy_0[i]) & mask_]);
				perm_01_ = static_cast<std::size_t>(permutations_[(perm_0_ + iy_1[i]) & mask_]);
				perm_10_ = static_cast<std::size_t>(permutations_[(perm_1_ + iy_0[i]) & mask_]);
				perm_11_ = static_cast<std::size_t>(permutations_[(perm_1_ + iy_1[i]) & mask_]);

				perm_000_[i] = static_cast<std::size_t>(permutations_[(perm_00_ + iz_0[i]) & mask_]) & gradients::mask;
				perm_001_[i] = static_cast<std::size_t>(permutations_[(perm_00_ + iz_1[i]) & mask_]) & gradients::mask;
				perm_010_[i] = static_cast<std::size_t>(permutations_[(perm_01_ + iz_0[i]) & mask_]) & gradients::mask;
				perm_011_[i] = static_cast<std::size_t>(permutations_[(perm_01_ + iz_1[i]) & mask_]) & gradients::mask;
				perm_100_[i] = static_cast<std::size_t>(permutations_[(perm_10_ + iz_0[i]) & mask_]) & gradients::mask;
				perm_101_[i] = static_cast<std::size_t>(permutations_[(perm_10_ + iz_1[i]) & mask_]) & gradients::mask;
				perm_110_[i] = static_cast<std::size_t>(permutations_[(perm_11_ + iz_0[i]) & mask_]) & gradients::mask;
				perm_111_[i] = static_cast<std::size_t>(permutations_[(perm_11_ + iz_1[i]) & mask_]) & gradients::mask;
			}

			// Use discovered permutations to form gradient dot products for our output values
			// 000
			register_type gradient_0_ = EmuSIMD::cast<register_type>(_gradients_128[perm_000_[0]]);
			register_type gradient_1_ = EmuSIMD::cast<register_type>(_gradients_128[perm_000_[1]]);
			register_type gradient_2_ = EmuSIMD::cast<register_type>(_gradients_128[perm_000_[2]]);
			register_type gradient_3_ = EmuSIMD::cast<register_type>(_gradients_128[perm_000_[3]]);
			gradient_0_ = _mm256_insertf128_ps(gradient_0_, _gradients_128[perm_000_[4]], 1);
			gradient_1_ = _mm256_insertf128_ps(gradient_1_, _gradients_128[perm_000_[5]], 1);
			gradient_2_ = _mm256_insertf128_ps(gradient_2_, _gradients_128[perm_000_[6]], 1);
			gradient_3_ = _mm256_insertf128_ps(gradient_3_, _gradients_128[perm_000_[7]], 1);
			
			// X - Pre-store the Y components in the indices [1] and [3] from each temp shuffle
			register_type temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			register_type temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			register_type row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_000_ = EmuSIMD::mul_all(row_, tx_0_);
			
			// Y - Already prestored Y in previous two shuffles, so we can form row straight away
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_000_ = EmuSIMD::add(vals_000_, EmuSIMD::mul_all(row_, ty_0_));
			
			// Z - One more batch of shuffles to extract the Z-coordinates of the gradients
			// --- We can, however, take advantage of the duplicate Z in the W-element to use blends and a shuffle
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1, 0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1, 0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_000_ = EmuSIMD::add(vals_000_, EmuSIMD::mul_all(row_, tz_0_));
			
			// ABOVE COMMENTS APPLY TO SUBSEQUENT OUTPUTS
			// 001
			gradient_0_ = EmuSIMD::cast<register_type>(_gradients_128[perm_001_[0]]);
			gradient_1_ = EmuSIMD::cast<register_type>(_gradients_128[perm_001_[1]]);
			gradient_2_ = EmuSIMD::cast<register_type>(_gradients_128[perm_001_[2]]);
			gradient_3_ = EmuSIMD::cast<register_type>(_gradients_128[perm_001_[3]]);
			gradient_0_ = _mm256_insertf128_ps(gradient_0_, _gradients_128[perm_001_[4]], 1);
			gradient_1_ = _mm256_insertf128_ps(gradient_1_, _gradients_128[perm_001_[5]], 1);
			gradient_2_ = _mm256_insertf128_ps(gradient_2_, _gradients_128[perm_001_[6]], 1);
			gradient_3_ = _mm256_insertf128_ps(gradient_3_, _gradients_128[perm_001_[7]], 1);
			
			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_001_ = EmuSIMD::mul_all(row_, tx_0_);
			
			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_001_ = EmuSIMD::add(vals_001_, EmuSIMD::mul_all(row_, ty_0_));
			
			// Z
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1, 0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1, 0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_001_ = EmuSIMD::add(vals_001_, EmuSIMD::mul_all(row_, tz_1_));
			
			// 010
			gradient_0_ = EmuSIMD::cast<register_type>(_gradients_128[perm_010_[0]]);
			gradient_1_ = EmuSIMD::cast<register_type>(_gradients_128[perm_010_[1]]);
			gradient_2_ = EmuSIMD::cast<register_type>(_gradients_128[perm_010_[2]]);
			gradient_3_ = EmuSIMD::cast<register_type>(_gradients_128[perm_010_[3]]);
			gradient_0_ = _mm256_insertf128_ps(gradient_0_, _gradients_128[perm_010_[4]], 1);
			gradient_1_ = _mm256_insertf128_ps(gradient_1_, _gradients_128[perm_010_[5]], 1);
			gradient_2_ = _mm256_insertf128_ps(gradient_2_, _gradients_128[perm_010_[6]], 1);
			gradient_3_ = _mm256_insertf128_ps(gradient_3_, _gradients_128[perm_010_[7]], 1);
			
			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_010_ = EmuSIMD::mul_all(row_, tx_0_);
			
			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_010_ = EmuSIMD::add(vals_010_, EmuSIMD::mul_all(row_, ty_1_));
			
			// Z
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1, 0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1, 0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_010_ = EmuSIMD::add(vals_010_, EmuSIMD::mul_all(row_, tz_0_));
			
			// 011
			gradient_0_ = EmuSIMD::cast<register_type>(_gradients_128[perm_011_[0]]);
			gradient_1_ = EmuSIMD::cast<register_type>(_gradients_128[perm_011_[1]]);
			gradient_2_ = EmuSIMD::cast<register_type>(_gradients_128[perm_011_[2]]);
			gradient_3_ = EmuSIMD::cast<register_type>(_gradients_128[perm_011_[3]]);
			gradient_0_ = _mm256_insertf128_ps(gradient_0_, _gradients_128[perm_011_[4]], 1);
			gradient_1_ = _mm256_insertf128_ps(gradient_1_, _gradients_128[perm_011_[5]], 1);
			gradient_2_ = _mm256_insertf128_ps(gradient_2_, _gradients_128[perm_011_[6]], 1);
			gradient_3_ = _mm256_insertf128_ps(gradient_3_, _gradients_128[perm_011_[7]], 1);

			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_011_ = EmuSIMD::mul_all(row_, tx_0_);

			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_011_ = EmuSIMD::add(vals_011_, EmuSIMD::mul_all(row_, ty_1_));

			// Z
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1, 0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1, 0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_011_ = EmuSIMD::add(vals_011_, EmuSIMD::mul_all(row_, tz_1_));

			// 100
			gradient_0_ = EmuSIMD::cast<register_type>(_gradients_128[perm_100_[0]]);
			gradient_1_ = EmuSIMD::cast<register_type>(_gradients_128[perm_100_[1]]);
			gradient_2_ = EmuSIMD::cast<register_type>(_gradients_128[perm_100_[2]]);
			gradient_3_ = EmuSIMD::cast<register_type>(_gradients_128[perm_100_[3]]);
			gradient_0_ = _mm256_insertf128_ps(gradient_0_, _gradients_128[perm_100_[4]], 1);
			gradient_1_ = _mm256_insertf128_ps(gradient_1_, _gradients_128[perm_100_[5]], 1);
			gradient_2_ = _mm256_insertf128_ps(gradient_2_, _gradients_128[perm_100_[6]], 1);
			gradient_3_ = _mm256_insertf128_ps(gradient_3_, _gradients_128[perm_100_[7]], 1);

			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_100_ = EmuSIMD::mul_all(row_, tx_1_);

			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_100_ = EmuSIMD::add(vals_100_, EmuSIMD::mul_all(row_, ty_0_));

			// Z
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1, 0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1, 0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_100_ = EmuSIMD::add(vals_100_, EmuSIMD::mul_all(row_, tz_0_));

			// 101
			gradient_0_ = EmuSIMD::cast<register_type>(_gradients_128[perm_101_[0]]);
			gradient_1_ = EmuSIMD::cast<register_type>(_gradients_128[perm_101_[1]]);
			gradient_2_ = EmuSIMD::cast<register_type>(_gradients_128[perm_101_[2]]);
			gradient_3_ = EmuSIMD::cast<register_type>(_gradients_128[perm_101_[3]]);
			gradient_0_ = _mm256_insertf128_ps(gradient_0_, _gradients_128[perm_101_[4]], 1);
			gradient_1_ = _mm256_insertf128_ps(gradient_1_, _gradients_128[perm_101_[5]], 1);
			gradient_2_ = _mm256_insertf128_ps(gradient_2_, _gradients_128[perm_101_[6]], 1);
			gradient_3_ = _mm256_insertf128_ps(gradient_3_, _gradients_128[perm_101_[7]], 1);

			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_101_ = EmuSIMD::mul_all(row_, tx_1_);

			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_101_ = EmuSIMD::add(vals_101_, EmuSIMD::mul_all(row_, ty_0_));

			// Z
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1, 0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1, 0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_101_ = EmuSIMD::add(vals_101_, EmuSIMD::mul_all(row_, tz_1_));

			// 110
			gradient_0_ = EmuSIMD::cast<register_type>(_gradients_128[perm_110_[0]]);
			gradient_1_ = EmuSIMD::cast<register_type>(_gradients_128[perm_110_[1]]);
			gradient_2_ = EmuSIMD::cast<register_type>(_gradients_128[perm_110_[2]]);
			gradient_3_ = EmuSIMD::cast<register_type>(_gradients_128[perm_110_[3]]);
			gradient_0_ = _mm256_insertf128_ps(gradient_0_, _gradients_128[perm_110_[4]], 1);
			gradient_1_ = _mm256_insertf128_ps(gradient_1_, _gradients_128[perm_110_[5]], 1);
			gradient_2_ = _mm256_insertf128_ps(gradient_2_, _gradients_128[perm_110_[6]], 1);
			gradient_3_ = _mm256_insertf128_ps(gradient_3_, _gradients_128[perm_110_[7]], 1);

			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_110_ = EmuSIMD::mul_all(row_, tx_1_);

			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_110_ = EmuSIMD::add(vals_110_, EmuSIMD::mul_all(row_, ty_1_));

			// Z
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1, 0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1, 0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_110_ = EmuSIMD::add(vals_110_, EmuSIMD::mul_all(row_, tz_0_));

			// 111
			gradient_0_ = EmuSIMD::cast<register_type>(_gradients_128[perm_111_[0]]);
			gradient_1_ = EmuSIMD::cast<register_type>(_gradients_128[perm_111_[1]]);
			gradient_2_ = EmuSIMD::cast<register_type>(_gradients_128[perm_111_[2]]);
			gradient_3_ = EmuSIMD::cast<register_type>(_gradients_128[perm_111_[3]]);
			gradient_0_ = _mm256_insertf128_ps(gradient_0_, _gradients_128[perm_111_[4]], 1);
			gradient_1_ = _mm256_insertf128_ps(gradient_1_, _gradients_128[perm_111_[5]], 1);
			gradient_2_ = _mm256_insertf128_ps(gradient_2_, _gradients_128[perm_111_[6]], 1);
			gradient_3_ = _mm256_insertf128_ps(gradient_3_, _gradients_128[perm_111_[7]], 1);
			
			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			vals_111_ = EmuSIMD::mul_all(row_, tx_1_);
			
			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_111_ = EmuSIMD::add(vals_111_, EmuSIMD::mul_all(row_, ty_1_));
			
			// Z
			temp_0_ = EmuSIMD::blend<0, 0, 0, 1, 0, 0, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::blend<0, 0, 0, 1, 0, 0, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<2, 3, 2, 3>(temp_0_, temp_1_);
			vals_111_ = EmuSIMD::add(vals_111_, EmuSIMD::mul_all(row_, tz_1_));
		}


		std::array<int, num_elements_in_register> ix_0;
		std::array<int, num_elements_in_register> ix_1;
		std::array<int, num_elements_in_register> iy_0;
		std::array<int, num_elements_in_register> iy_1;
		std::array<int, num_elements_in_register> iz_0;
		std::array<int, num_elements_in_register> iz_1;
		EmuMath::Functors::_underlying_noise_gen::_fast_smooth_t<register_type> smooth_t;
	};
}

#endif
