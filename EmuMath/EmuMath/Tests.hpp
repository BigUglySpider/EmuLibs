#ifndef EMU_TESTS_HPP_INC_
#define EMU_TESTS_HPP_INC_ 1

// REQUIRED INCLUDES
#include "EmuCore/TestingHelpers/LoopingTestHarness.h"
#include "EmuMath/Random.h"
#include <array>
#include <chrono>
#include <iostream>
#include <tuple>

// ADDITIONAL INCLUDES
#include "EmuMath/Vector.h"
#include "EmuMath/Random.h"
#include <bitset>
#include <DirectXMath.h>
#include <string_view>

namespace EmuCore::TestingHelpers
{
	static constexpr unsigned long long shared_fill_seed_ = 1337;
	static constexpr unsigned long long shared_select_seed_ = -25;

	template<std::size_t Size_, typename OutT_, class OutColl_, class RngFunc_>
	inline void emplace_back_vector(OutColl_& out_coll_, RngFunc_& func_)
	{
		out_coll_.emplace_back
		(
			EmuMath::Helpers::vector_mutate<Size_, OutT_, RngFunc_&>(func_, OutT_())
		);
	}

	template<class Vector_, class OutColl_, class RngFunc_>
	inline void emplace_back_old_vector(OutColl_& out_coll_, RngFunc_& func_)
	{
		Vector_ vec_ = Vector_();
		out_coll_.emplace_back(EmuMath::Helpers::vector_mutate(vec_, std::ref(func_)));
	}

	struct RngFunctor
	{
	private:
		template
		<
			typename T_,
			bool IsValidOut_ = 
			(
				std::is_integral_v<EmuCore::TMP::remove_ref_cv_t<T_>> ||
				std::is_floating_point_v<EmuCore::TMP::remove_ref_cv_t<T_>>
			)
	>
		struct _out_type
		{
			using type = float;
		};
		template<typename T_>
		struct _out_type<T_, true>
		{
			using type = EmuCore::TMP::remove_ref_cv_t<T_>;
		};

	public:
		using rng_type = EmuMath::RngWrapper<true>;
		using seed_type = rng_type::unsigned_int_type;

		RngFunctor() : _rng()
		{
		}
		template<class...ConstructionArgs_, typename = std::enable_if_t<std::is_constructible_v<rng_type, ConstructionArgs_&&...>>>
		RngFunctor(ConstructionArgs_&&...construction_args_) : _rng(std::forward<ConstructionArgs_>(construction_args_)...)
		{
		}

		template<typename T_>
		constexpr inline typename _out_type<T_>::type operator()(const T_& dummy_)
		{
			if constexpr (std::is_integral_v<typename _out_type<T_>::type>)
			{
				return _rng.NextInt<typename _out_type<T_>::type>();
			}
			else
			{
				return _rng.NextReal<typename _out_type<T_>::type>();
			}
		}

		rng_type _rng;
	};

	/// <summary> Example which only contains the required items for the test harness. </summary>
	struct ExampleTest
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 500000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "Example";

		ExampleTest()
		{
		}
		void Prepare()
		{
		}
		void operator()(std::size_t i)
		{
		}
		void OnTestsOver()
		{
		}
	};

	struct reflect_test_emu
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 500000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "Vector Reflect (Emu)";

		static constexpr std::size_t vec_size = 3;
		using vector_type_arg = float;
		using vector_type = EmuMath::Vector<vec_size, vector_type_arg>;
		using float_type = typename vector_type::preferred_floating_point;
		using vector_type_fp = EmuMath::Vector<vec_size, float_type>;

		reflect_test_emu()
		{
		}
		void Prepare()
		{
			// RESIZES
			out_reflection.resize(NUM_LOOPS);

			// RESERVES
			in_ray.reserve(NUM_LOOPS);
			in_norm.reserve(NUM_LOOPS);

			// FILL RESERVES
			RngFunctor rng_ = RngFunctor(shared_fill_seed_);
			rng_._rng.SetMinMax(-1000, 1000);

			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				emplace_back_vector<vec_size, vector_type_arg>(in_ray, rng_);
				emplace_back_vector<vec_size, float_type>(in_norm, rng_);
				in_norm[i] = in_norm[i].Normalise();
			}
		}
		void operator()(std::size_t i)
		{
			out_reflection[i] = in_ray[i].Reflect(in_norm[i]);
		}
		void OnTestsOver()
		{
			const std::size_t i_ = RngFunctor(shared_select_seed_)._rng.NextInt<std::size_t>() % NUM_LOOPS;
			std::cout << "REFLECT\n(\n\t" << in_ray[i_] << "\n\t" << in_norm[i_] << "\n" << "): " << out_reflection[i_] << "\n\n";
		}

		std::vector<vector_type> in_ray;
		std::vector<vector_type_fp> in_norm;
		std::vector<vector_type_fp> out_reflection;
	};

	struct reflect_test_dxm
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 500000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "Vector Reflect (DXM)";

		reflect_test_dxm()
		{
		}
		void Prepare()
		{
			// RESIZES
			out_reflection.resize(NUM_LOOPS);

			// RESERVES
			in_ray.reserve(NUM_LOOPS);
			in_norm.reserve(NUM_LOOPS);

			// FILL RESERVES
			RngFunctor rng_ = RngFunctor(shared_fill_seed_);
			rng_._rng.SetMinMax(-1000, 1000);

			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				in_ray.emplace_back
				(
					rng_(0.0f), rng_(0.0f), rng_(0.0f)
				);
				in_norm.emplace_back
				(
					rng_(0.0f), rng_(0.0f), rng_(0.0f)
				);
				DirectX::XMStoreFloat3
				(
					&(in_norm[i]), 
					DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&(in_norm[i])))
				);
			}
		}
		void operator()(std::size_t i)
		{
			DirectX::XMStoreFloat3
			(
				&(out_reflection[i]),
				DirectX::XMVector3Reflect
				(
					DirectX::XMLoadFloat3(&(in_ray[i])),
					DirectX::XMLoadFloat3(&(in_norm[i]))
				)
			);
		}
		void OnTestsOver()
		{
			const std::size_t i_ = RngFunctor(shared_select_seed_)._rng.NextInt<std::size_t>() % NUM_LOOPS;
			std::cout << "REFLECT\n(\n\t";
			Print(in_ray[i_]);
			std::cout << "\n\t";
			Print(in_norm[i_]);
			std::cout << "\n" << "): ";
			Print(out_reflection[i_]);
			std::cout << "\n\n";
		}
		void Print(const DirectX::XMFLOAT3& vector_)
		{
			std::cout << "{ " << vector_.x << ", " << vector_.y << ", " << vector_.z << " }";
		}

		std::vector<DirectX::XMFLOAT3> in_ray;
		std::vector<DirectX::XMFLOAT3> in_norm;
		std::vector<DirectX::XMFLOAT3> out_reflection;
	};


	// ----------- TESTS SELECTION -----------
	using AllTests = std::tuple
	<
		reflect_test_emu,
		reflect_test_dxm
	>;

	// ----------- TESTS BEGIN -----------

	template<std::size_t Index_>
	void PrepareAllTests(AllTests& tests)
	{
		if constexpr (Index_ < std::tuple_size_v<AllTests>)
		{
			auto& test_ = std::get<Index_>(tests);
			if (test_.DO_TEST)
			{
				test_.Prepare();
			}
			PrepareAllTests<Index_ + 1>(tests);
		}
	}

	void PrepareForTests(AllTests& outTests)
	{
		PrepareAllTests<0>(outTests);
	}

	template<std::size_t Index_>
	void OnAllTestsOver(AllTests& tests)
	{
		if constexpr (Index_ < std::tuple_size_v<AllTests>)
		{
			using Test_ = std::tuple_element_t<Index_, AllTests>;
			if constexpr (Test_::DO_TEST)
			{
				std::cout << "Test " << Index_ << " (" << Test_::NAME << ")\n";
				std::get<Index_>(tests).OnTestsOver();
				std::cout << std::endl;
			}
			OnAllTestsOver<Index_ + 1>(tests);
		}
	}

#pragma region NO_EDIT
	template<std::size_t TestIndex, typename...Tests_>
	void ExecuteTests(std::tuple<Tests_...>& tests)
	{
		using Tuple = std::tuple<Tests_...>;
		constexpr std::size_t numTests = sizeof...(Tests_);
		constexpr bool Finished = TestIndex >= numTests;

		if constexpr (!Finished)
		{
			using Test = std::tuple_element_t<TestIndex, Tuple>;
			Test& test = std::get<TestIndex>(tests);
			LoopingTestHarness<Test> harness;
			std::cout << "!!!Test " << TestIndex << " (" << Test::NAME << ") Results!!!\n";
			if (test.DO_TEST)
			{
				std::cout << harness.ExecuteAndOutputAsString<Test::PASS_LOOP_NUM>(Test::NUM_LOOPS, test, test.WRITE_ALL_TIMES_TO_STREAM) << "\n\n";
			}
			else
			{
				std::cout << "Test " << TestIndex << " (" << Test::NAME << ") skipped through DO_TEST member being false.\n\n";
			}
			ExecuteTests<TestIndex + 1, Tests_...>(tests);
		}
	}

	void PerformTests()
	{
		bool shouldRepeat = false;
		std::string str;
		do
		{
			{
				constexpr std::size_t numTests = std::tuple_size_v<AllTests>;
				const std::string testCorrectPlural = numTests == 1 ? "test" : "tests";
				const std::string harnessCorrectPlural = numTests == 1 ? "harness" : "harnesses";

				AllTests tests = AllTests();
				std::cout << "\n-----Beginning preparation of " << numTests << " " << testCorrectPlural << "-----\n";
				PrepareForTests(tests);

				std::cout << "\n-----Beginning execution of " << numTests << " test " << harnessCorrectPlural << "-----\n";
				auto begin = std::chrono::steady_clock::now();
				ExecuteTests<0>(tests);
				auto end = std::chrono::steady_clock::now();

				auto duration = std::chrono::duration<double>(end - begin).count();
				std::cout << "\n-----Finished execution and output of " << numTests << " test " << harnessCorrectPlural << " in " << duration << " seconds-----\n";

				std::cout << "\n\nExecute additinal OnAllTestsOver branch? [Y - Yes]: ";
				std::getline(std::cin, str);
				if (str.size() != 0)
				{
					if (str[0] == 'y' || str[0] == 'Y')
					{
						OnAllTestsOver<0>(tests);
					}
				}
			}

			std::cout << "\n\nRepeat all tests? [Y - Yes]: ";
			std::getline(std::cin, str);
			if (str.size() != 0)
			{
				shouldRepeat = str[0] == 'Y' || str[0] == 'y';
			}
			else
			{
				shouldRepeat = false;
			}
		} while (shouldRepeat);
	}
#pragma endregion
}

#endif
