#ifndef EMU_TESTS_HPP_INC_
#define EMU_TESTS_HPP_INC_

// REQUIRED INCLUDES
#include "EmuCore/TestingHelpers/LoopingTestHarness.h"
#include <chrono>
#include <iostream>
#include <tuple>

// ADDITIONAL INCLUDES
#include "EmuMath/Vectors.h"

namespace EmuCore::TestingHelpers
{
	template<typename T>
	struct TestA
	{
		using ToAddT = T;

		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 5000000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;

		TestA()
		{
		}
		void Prepare()
		{
			outData.resize(NUM_LOOPS);
			toAdd.resize(NUM_LOOPS);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				outData[i] = { static_cast<T>((rand() % 30 - 15) * 0.75f), static_cast<T>((rand() % 30 - 15) * 0.75f) };
				toAdd[i] = { static_cast<ToAddT>((rand() % 30 - 15) * 0.75f), static_cast<ToAddT>((rand() % 30 - 15) * 0.75f) };
			}
		}
		void operator()(std::size_t i)
		{
			outData[i] = outData[i] + (toAdd[i] * static_cast<T>((rand() % (sizeof(T) * 8)) + 1));
			//outData[i] = EmuMath::Helpers::VectorRightShiftVectorwise(outData[i], (rand() % (sizeof(T) * 8)) + 1);
		}
		std::vector<EmuMath::Vector2<T>> outData;
		std::vector<EmuMath::Vector2<ToAddT>> toAdd;
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
						OnAllTestsOver(tests);
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
