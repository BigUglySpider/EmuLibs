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
#include "EmuMath/Matrix.h"
#include "EmuMath/Vector.h"
#include "EmuMath/Random.h"
#include <bitset>
#include <DirectXMath.h>
#include <string_view>

namespace EmuCore::TestingHelpers
{
	static constexpr unsigned long long shared_fill_seed_ = 1337;
	static constexpr unsigned long long shared_select_seed_ = -25;

	template<typename T_, auto...ToDiscard_, bool Is64Bit_>
	[[nodiscard]] inline T_ get_random_val(EmuMath::RngWrapper<Is64Bit_>& rng_)
	{
		if constexpr (std::is_integral_v<T_>)
		{
			return rng_.NextInt<T_>();
		}
		else
		{
			return rng_.NextReal<T_>();
		}
	}

	template<class OutMat_, bool Is64Bit_>
	[[nodiscard]] inline OutMat_ make_random_mat(EmuMath::RngWrapper<Is64Bit_>& rng_)
	{
		OutMat_ out_ = OutMat_();
		for (std::size_t column = 0; column < OutMat_::num_columns; ++column)
		{
			for (std::size_t row = 0; row < OutMat_::num_rows; ++row)
			{
				out_(column, row) = get_random_val<typename OutMat_::value_type_uq>(rng_);
			}
		}
		return out_;
	}

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
		void operator()(std::size_t i_)
		{

		}
		void OnTestsOver()
		{
		}
	};

	template<bool Fused_>
	struct MultiplyAddMatTest
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 500000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = Fused_ ? "Multiply-Add (Fused)" : "Multiply-Add (Manual)";

		using a_mat_type = EmuMath::Matrix<4, 4, float, true>;
		using b_type = EmuMath::Matrix<4, 4, float, true>;
		using c_type = float;
		static constexpr std::size_t out_num_columns = a_mat_type::num_columns;
		static constexpr std::size_t out_num_rows = a_mat_type::num_rows;
		static constexpr bool out_column_major = a_mat_type::is_column_major;
		using out_t = a_mat_type::value_type_uq;

		MultiplyAddMatTest()
		{
		}
		void Prepare()
		{
			// FILLS
			out_mats.resize(NUM_LOOPS);

			// RESERVES
			args_a.reserve(NUM_LOOPS);
			args_b.reserve(NUM_LOOPS);
			args_c.reserve(NUM_LOOPS);

			// RESERVED FILLS
			EmuMath::RngWrapper<true> rng_(-100, 100, shared_fill_seed_);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				args_a.emplace_back(make_random_mat<a_mat_type>(rng_));
				args_b.emplace_back(make_random_mat<b_type>(rng_));
				args_c.emplace_back(rng_.NextReal<c_type>());
			}
		}
		void operator()(std::size_t i_)
		{
			if constexpr (Fused_)
			{
				args_a[i_].Fmadd(out_mats[i_], args_b[i_], args_c[i_]);
			}
			else
			{
				out_mats[i_] = args_a[i_].MultiplyBasic(args_b[i_]).Add(args_c[i_]);
			}
		}
		void OnTestsOver()
		{
			const std::size_t i_ = EmuMath::RngWrapper<true>(shared_select_seed_).NextInt<std::size_t>(0, NUM_LOOPS - 1);
			std::cout << args_a[i_] << "\n*\n" << args_b[i_] << "\n+\n" << args_c[i_] << "\n=\n" << out_mats[i_] << "\n\n";
		}

		std::vector<a_mat_type> args_a;
		std::vector<b_type> args_b;
		std::vector<c_type> args_c;
		std::vector<EmuMath::Matrix<out_num_columns, out_num_rows, out_t, out_column_major>> out_mats;
	};

	// ----------- TESTS SELECTION -----------
	using AllTests = std::tuple
	<
		MultiplyAddMatTest<false>,
		MultiplyAddMatTest<true>
	>;

	// ----------- TESTS BEGIN -----------
	template<std::size_t Index_>
	void PrepareAllTests(AllTests& tests)
	{
		if constexpr (Index_ < std::tuple_size_v<AllTests>)
		{
			using std::get;
			auto& test_ = get<Index_>(tests);
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
				using std::get;
				std::cout << "Test " << Index_ << " (" << Test_::NAME << ")\n";
				get<Index_>(tests).OnTestsOver();
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
			using std::get;
			using Test = std::tuple_element_t<TestIndex, Tuple>;
			Test& test = get<TestIndex>(tests);
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
