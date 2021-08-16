#ifndef EMU_TESTS_HPP_INC_
#define EMU_TESTS_HPP_INC_

// REQUIRED INCLUDES
#include "EmuCore/TestingHelpers/LoopingTestHarness.h"
#include <array>
#include <chrono>
#include <iostream>
#include <tuple>

// ADDITIONAL INCLUDES
#include "EmuMath/GeneralMath.h"
#include "EmuMath/Vector.h"
#include <bitset>
#include <string_view>

namespace EmuCore::TestingHelpers
{
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

	struct VectorClampMinMaxSequential
	{
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 5000000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr bool DO_TEST = true;
		static constexpr std::string_view NAME = "Vector Clamp Min Max | SEQUENTIAL";

		using vector_value_type = float;
		using VectorType = EmuMath::Vector<3, vector_value_type>;
		using MinType = VectorType;
		using MaxType = VectorType;

		VectorClampMinMaxSequential()
		{
		}
		template<typename T>
		static void AssignRandomValueToItem(T& item_)
		{
			item_ = static_cast<T>(rand() * 0.5f);
		}
		template<std::size_t Index_, typename V>
		static void RandAssignVector(V& vec_)
		{
			if constexpr (Index_ < V::size)
			{
				AssignRandomValueToItem(EmuMath::Helpers::VectorGet<Index_>(vec_));
				RandAssignVector<Index_ + 1>(vec_);
			}
		}
		template<typename T>
		static void RandAssignItem(T& item_)
		{
			if constexpr (EmuMath::TMP::is_emu_vector_v<VectorType>)
			{
				RandAssignVector<0>(item_);
			}
			else
			{
				AssignRandomValueToItem(item_);
			}
		}
		template<std::size_t Index_, class Min_, class Max_>
		static void EnsureMinLessThanMax_vv(Min_& min_, Max_& max_)
		{
			if constexpr (Index_ < Min_::size || Index_ < Max_::size)
			{
				using min_value = typename Min_::value_type;
				using max_value = typename Max_::value_type;
				if constexpr (Index_ < Min_::size)
				{
					if constexpr (Index_ < Max_::size)
					{
						EnsureMinLessThanMax<min_value, max_value>(EmuMath::Helpers::VectorGet<Index_>(min_), EmuMath::Helpers::VectorGet<Index_>(max_));
					}
					else
					{
						max_value max_val_ = max_value();
						EnsureMinLessThanMax<min_value, max_value>(EmuMath::Helpers::VectorGet<Index_>(min_), max_val_);
					}
				}
				else
				{
					// Will only get here if in Max_ range but not Min_
					min_value min_val_ = min_value();
					EnsureMinLessThanMax<min_value, max_value>(min_val_, EmuMath::Helpers::VectorGet<Index_>(max_));
				}
				EnsureMinLessThanMax_vv<Index_ + 1, Min_, Max_>(min_, max_);
			}
		}
		template<std::size_t Index_, class Min_, class Max_>
		static void EnsureMinLessThanMax_vs(Min_& min_, Max_& max_)
		{
			if constexpr (Index_ < Min_::size)
			{
				EnsureMinLessThanMax<typename Min_::value_type, Max_>(EmuMath::Helpers::VectorGet<Index_>(min_), max_);
				EnsureMinLessThanMax_vs<Index_ + 1, Min_, Max_>(min_, max_);
			}
		}
		template<std::size_t Index_, class Min_, class Max_>
		static void EnsureMinLessThanMax_sv(Min_& min_, Max_& max_)
		{
			if constexpr (Index_ < Max_::size)
			{
				EnsureMinLessThanMax<Min_, typename Max_::value_type>(min_, EmuMath::Helpers::VectorGet<Index_>(max_));
				EnsureMinLessThanMax_sv<Index_ + 1, Min_, Max_>(min_, max_);
			}
		}
		template<class Min_, class Max_>
		static void EnsureMinLessThanMax(Min_& min_, Max_& max_)
		{
			if constexpr (EmuMath::TMP::is_emu_vector_v<Min_>)
			{
				if constexpr (EmuMath::TMP::is_emu_vector_v<Max_>)
				{
					EnsureMinLessThanMax_vv<0, Min_, Max_>(min_, max_);
				}
				else
				{
					EnsureMinLessThanMax_vs<0, Min_, Max_>(min_, max_);
				}
			}
			else
			{
				if constexpr (EmuMath::TMP::is_emu_vector_v<Max_>)
				{
					EnsureMinLessThanMax_sv<0, Min_, Max_>(min_, max_);
				}
				else
				{
					if (min_ > max_)
					{
						const Max_ tempMax = max_;
						max_ = static_cast<Max_>(min_);
						min_ = static_cast<Min_>(tempMax);
					}
				}
			}
		}
		void Prepare()
		{
			in_.resize(NUM_LOOPS);
			min_.resize(NUM_LOOPS);
			max_.resize(NUM_LOOPS);
			out_.resize(NUM_LOOPS);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				RandAssignItem(in_[i]);
				RandAssignItem(min_[i]);
				RandAssignItem(max_[i]);
				EnsureMinLessThanMax(min_[i], max_[i]);
			}
		}
		void operator()(std::size_t i)
		{
			out_[i] = EmuMath::Helpers::VectorClampMin(in_[i], min_[i]);
			out_[i] = EmuMath::Helpers::VectorClampMax(out_[i], max_[i]);
		}
		void OutputRand()
		{
			std::size_t i = static_cast<std::size_t>(rand() % NUM_LOOPS);
			std::cout << "Clamp(" << in_[i] << ", " << min_[i] << ", " << max_[i] << "): " << out_[i] << "\n";
		}
		void OnTestsOver()
		{
			OutputRand();
		}

		std::vector<VectorType> in_, out_;
		std::vector<MinType> min_;
		std::vector<MaxType> max_;
	};

	struct VectorClampMinMaxSimultaneous
	{
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 5000000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr bool DO_TEST = true;
		static constexpr std::string_view NAME = "Vector Clamp Min Max | SIMULTANEOUS";

		using vector_value_type = float;
		using VectorType = EmuMath::Vector<3, vector_value_type>;
		using MinType = VectorType;
		using MaxType = VectorType;

		VectorClampMinMaxSimultaneous()
		{
		}
		
		void Prepare()
		{
			in_.resize(NUM_LOOPS);
			min_.resize(NUM_LOOPS);
			max_.resize(NUM_LOOPS);
			out_.resize(NUM_LOOPS);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				VectorClampMinMaxSequential::RandAssignItem(in_[i]);
				VectorClampMinMaxSequential::RandAssignItem(min_[i]);
				VectorClampMinMaxSequential::RandAssignItem(max_[i]);
				VectorClampMinMaxSequential::EnsureMinLessThanMax(min_[i], max_[i]);
			}
		}
		void operator()(std::size_t i)
		{
			out_[i] = EmuMath::Helpers::VectorClamp(in_[i], min_[i], max_[i]);
		}
		void OutputRand()
		{
			std::size_t i = static_cast<std::size_t>(rand() % NUM_LOOPS);
			std::cout << "Clamp(" << in_[i] << ", " << min_[i] << ", " << max_[i] << "): " << out_[i] << "\n";
		}
		void OnTestsOver()
		{
			OutputRand();
		}

		std::vector<VectorType> in_, out_;
		std::vector<MinType> min_;
		std::vector<MaxType> max_;
	};

	using SqrtTestFP = float;

	using AllTests = std::tuple
	<
		VectorClampMinMaxSequential,
		VectorClampMinMaxSimultaneous
	>;

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
