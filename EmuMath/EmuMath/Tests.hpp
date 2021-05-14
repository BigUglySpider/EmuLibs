#ifndef EMU_TESTS_HPP_INC_
#define EMU_TESTS_HPP_INC_

// REQUIRED INCLUDES
#include "EmuCore/TestingHelpers/LoopingTestHarness.h"
#include <chrono>
#include <iostream>
#include <tuple>

// ADDITIONAL INCLUDES
#include "EmuMath/EmuVector.h"

namespace EmuCore::TestingHelpers
{
	template<typename T>
	struct TestA
	{
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 500000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;

		TestA()
		{
		}
		void Prepare()
		{
			outData.resize(NUM_LOOPS);
			for (auto& vec : outData)
			{
				vec = { static_cast<T>((rand() % 30 - 15) * 0.75f), static_cast<T>((rand() % 30 - 15) * 0.75f) };
			}
		}
		void operator()(std::size_t i)
		{
			outData[i] = outData[i].AsTrunced();
		}
		std::vector<EmuMath::Vector2<T>> outData;
	};

	using AllTests = std::tuple<TestA<float>>;

	void PrepareForTests(AllTests& outTests)
	{
		std::get<0>(outTests).Prepare();
	}

	void OnAllTestsOver(AllTests& tests)
	{
		std::cout << "\n\n\n\n-----DUMP-----";
		for (auto& data_ : std::get<0>(tests).outData)
		{
			std::cout << data_ << "\n";
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
			std::cout << "!!!Test " << TestIndex << " Results!!!\n";
			std::cout << harness.ExecuteAndOutputAsString<Test::PASS_LOOP_NUM>(Test::NUM_LOOPS, test, test.WRITE_ALL_TIMES_TO_STREAM) << "\n\n";
			ExecuteTests<TestIndex + 1, Tests_...>(tests);
		}
	}

	void PerformTests()
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
		system("pause");
		OnAllTestsOver(tests);
	}
#pragma endregion
}

#endif
