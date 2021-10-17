#ifndef EMU_MATH_NOISE_PERMUTATION_INFO_H_INC_
#define EMU_MATH_NOISE_PERMUTATION_INFO_H_INC_ 1

#include "../NoiseFunctors.h"

namespace EmuMath::Info
{
	struct NoisePermutationInfo
	{
	public:
		enum class ShuffleMode : std::uint8_t
		{
			BOOL_INPUT = 0x01,
			SEED_32 = 0x02,
			SEED_64 = 0x04
		};
		static constexpr inline bool valid_shuffle_mode(const ShuffleMode& in_shuffle_mode_)
		{
			return 
			(
				in_shuffle_mode_ == ShuffleMode::BOOL_INPUT ||
				in_shuffle_mode_ == ShuffleMode::SEED_32 ||
				in_shuffle_mode_ == ShuffleMode::SEED_64
			);
		}

		using seed_32_type = EmuMath::NoisePermutations::seed_32_type;
		using seed_64_type = EmuMath::NoisePermutations::seed_64_type;

		static constexpr std::size_t _default_permutation_count = 512;
		static constexpr ShuffleMode _default_shuffle_mode = ShuffleMode::BOOL_INPUT;
		static constexpr bool _default_bool_input = true;
		static seed_32_type _default_seed_32() { return EmuMath::NoisePermutations::default_seed_32(); }
		static seed_64_type _default_seed_64() { return EmuMath::NoisePermutations::default_seed_64(); }

		NoisePermutationInfo() :
			NoisePermutationInfo
			(
				_default_permutation_count,
				_default_shuffle_mode,
				_default_bool_input,
				_default_seed_32(),
				_default_seed_64()
			)
		{
		}
		constexpr NoisePermutationInfo
		(
			std::size_t target_num_permutations_,
			ShuffleMode shuffle_mode_,
			bool bool_input_,
			seed_32_type seed_32_,
			seed_64_type seed_64_
		) :
			target_num_permutations(target_num_permutations_),
			shuffle_mode(shuffle_mode_),
			bool_input(bool_input_),
			seed_32(seed_32_),
			seed_64(seed_64_)
		{
		}
		constexpr NoisePermutationInfo(const NoisePermutationInfo& to_copy_) :
			NoisePermutationInfo
			(
				to_copy_.target_num_permutations,
				to_copy_.shuffle_mode,
				to_copy_.bool_input,
				to_copy_.seed_32,
				to_copy_.seed_64
			)
		{
		}

		std::size_t TargetCountToPowerOf2() const
		{
			if (target_num_permutations == 0)
			{
				return 1;
			}
			else
			{
				if (EmuCore::ArithmeticHelpers::is_integral_power_of_2<std::size_t>(target_num_permutations))
				{
					return target_num_permutations;
				}
				else
				{
					std::size_t next_ = EmuCore::ArithmeticHelpers::next_unsigned_power_of_2<std::size_t>(target_num_permutations);
					if (next_ > target_num_permutations)
					{
						return next_;
					}
					else
					{
						return EmuCore::ArithmeticHelpers::previous_unsigned_power_of_2<std::size_t>(target_num_permutations);
					}
				}
			}
		}
		void MakeTargetCountPowerOf2()
		{
			target_num_permutations = TargetCountToPowerOf2();
		}

		EmuMath::NoisePermutations MakePermutations() const
		{
			ShuffleMode using_shuffle_mode = valid_shuffle_mode(shuffle_mode) ? shuffle_mode : _default_shuffle_mode;
			if (using_shuffle_mode == ShuffleMode::BOOL_INPUT)
			{
				return EmuMath::NoisePermutations(TargetCountToPowerOf2(), bool_input);
			}
			else if (using_shuffle_mode == ShuffleMode::SEED_32)
			{
				return EmuMath::NoisePermutations(TargetCountToPowerOf2(), seed_32);
			}
			else if (using_shuffle_mode == ShuffleMode::SEED_64)
			{
				return EmuMath::NoisePermutations(TargetCountToPowerOf2(), seed_64);
			}
			else
			{
				return EmuMath::NoisePermutations(TargetCountToPowerOf2(), bool_input);
			}
		}

		std::size_t target_num_permutations;
		ShuffleMode shuffle_mode;
		bool bool_input;
		seed_32_type seed_32;
		seed_64_type seed_64;
	};
}

#endif
