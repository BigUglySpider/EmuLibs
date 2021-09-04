#ifndef EMU_TESTS_HPP_INC_
#define EMU_TESTS_HPP_INC_ 1

// REQUIRED INCLUDES
#include "EmuCore/TestingHelpers/LoopingTestHarness.h"
#include <array>
#include <chrono>
#include <iostream>
#include <tuple>

// ADDITIONAL INCLUDES
#include "EmuMath/Vector.h"
#include "EmuMath/FastVector.h"
#include <bitset>
#include <string_view>

namespace EmuCore::TestingHelpers
{
	struct VectorFiller
	{
		constexpr VectorFiller()
		{
		}
		template<typename T_>
		constexpr inline T_ operator()(const T_& dummy_) const
		{
			if constexpr (std::numeric_limits<T_>::max() < std::numeric_limits<int>::max())
			{
				return static_cast<T_>((rand() % static_cast<int>(std::numeric_limits<T_>::max())) * 0.33f);
			}
			else
			{
				return static_cast<T_>(rand() * 0.33f);
			}
		}
	};

	/// <summary> Example which only contains the required items for the test harness. </summary>
	struct ExampleTest
	{
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 5000000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr bool DO_TEST = false;
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

	struct MatrixRotConstexprTest
	{
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 5000000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr bool DO_TEST = true;
		static constexpr std::string_view NAME = "Rotation Constexpr";

		MatrixRotConstexprTest()
		{
		}
		void Prepare()
		{
			srand(5);
			in_.resize(NUM_LOOPS);
			out_.resize(NUM_LOOPS);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				in_[i] = 0.99f * (rand() % 360);
			}
		}
		void operator()(std::size_t i)
		{
			out_[i] = EmuMath::Helpers::MatrixRotationXDegsConstexpr(in_[i]);
		}
		void OnTestsOver()
		{
			srand(7);
			std::size_t i = static_cast<std::size_t>(rand() % NUM_LOOPS);
			std::cout << "ROTX(" << in_[i] << "):\n" << out_[i] << "\n";
		}

		std::vector<float> in_;
		std::vector<EmuMath::Matrix<4, 4, float, true>> out_;
	};
	struct MatrixRotTest
	{
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 5000000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr bool DO_TEST = true;
		static constexpr std::string_view NAME = "Rotation Normal";

		MatrixRotTest()
		{
		}
		void Prepare()
		{
			srand(5);
			in_.resize(NUM_LOOPS);
			out_.resize(NUM_LOOPS);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				in_[i] = 0.99f * (rand() % 360);
			}
		}
		void operator()(std::size_t i)
		{
			out_[i] = EmuMath::Helpers::MatrixRotationXDegs(in_[i]);
		}
		void OnTestsOver()
		{
			srand(7);
			std::size_t i = static_cast<std::size_t>(rand() % NUM_LOOPS);
			std::cout << "ROTX(" << in_[i] << "):\n" << out_[i] << "\n";
		}

		std::vector<float> in_;
		std::vector<EmuMath::Matrix<4, 4, float, true>> out_;
	};

	using AllTests = std::tuple
	<
		MatrixRotConstexprTest,
		MatrixRotTest
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
