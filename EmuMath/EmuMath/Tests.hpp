#ifndef EMU_TESTS_HPP_INC_
#define EMU_TESTS_HPP_INC_

// REQUIRED INCLUDES
#include "EmuCore/TestingHelpers/LoopingTestHarness.h"
#include <array>
#include <chrono>
#include <iostream>
#include <tuple>

// ADDITIONAL INCLUDES
#include "EmuMath/FastVector.h"
#include "EmuMath/GeneralMath.h"
#include "EmuMath/Vectors.h"
#include <bitset>

namespace EmuCore::TestingHelpers
{
	template<typename T>
	struct TestA
	{
		using ToAddT = T;

		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 5000000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr bool DO_TEST = false;

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

	template<typename T>
	struct VectorwiseShiftTest
	{
		using Vec = EmuMath::Vector4<T>;
		using CopyVec = EmuMath::TMPHelpers::emu_vector_copy_t<Vec>;

		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_BITS_T = sizeof(T) * 8;
		static constexpr std::size_t NUM_LOOPS = (Vec::size() * NUM_BITS_T) + 1;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr bool DO_TEST = false;

		using ScalarBits = std::bitset<NUM_BITS_T>;
		using BitVec = EmuMath::TMPHelpers::emu_vector_from_size_t<Vec::size(), ScalarBits>;

		VectorwiseShiftTest()
		{
		}

		T _select_random() const
		{
			return static_cast<T>(rand() % std::numeric_limits<T>::max());
		}
		void Prepare()
		{
			vec.x = _select_random();
			vec.y = _select_random();
			if constexpr (Vec::size() >= 3)
			{
				vec.z = _select_random();
				if constexpr (Vec::size() >= 4)
				{
					vec.w = _select_random();
				}
			}
			vecBits = vec;
			outLeftShift.resize(NUM_LOOPS);
			outRightShift.resize(NUM_LOOPS);
			outLeftBits.resize(NUM_LOOPS);
			outRightBits.resize(NUM_LOOPS);
		}
		void operator()(std::size_t i)
		{
			outLeftShift[i] = EmuMath::Helpers::VectorLeftShiftVectorwise(vec, i);
			//outRightShift[i] = EmuMath::Helpers::VectorRightShiftVectorwise(vec, i);

			outLeftBits[i] = outLeftShift[i];
			//outRightBits[i] = outRightShift[i];
		}

		Vec vec;
		BitVec vecBits;
		std::vector<CopyVec> outLeftShift;
		std::vector<CopyVec> outRightShift;
		std::vector<BitVec> outLeftBits;
		std::vector<BitVec> outRightBits;
	};

	template<typename T, bool UseEmuMath>
	struct SqrtTest
	{
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 500000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr bool DO_TEST = false;

		SqrtTest()
		{
		}

		T _select_random() const
		{
			return static_cast<T>(rand() % static_cast<std::int64_t>(std::numeric_limits<T>::max()));
		}
		void Prepare()
		{
			inData.resize(NUM_LOOPS);
			outData.resize(NUM_LOOPS);
			for (auto& val : inData)
			{
				val = _select_random();
			}
		}
		void operator()(std::size_t i)
		{
			if constexpr (UseEmuMath)
			{
				outData[i] = EmuMath::SqrtConstexpr<T, T>(inData[i]);
			}
			else
			{
				if constexpr (std::is_same_v<T, float>)
				{
					outData[i] = sqrtf(inData[i]);
				}
				else if constexpr (std::is_same_v<T, double>)
				{
					outData[i] = sqrt(inData[i]);
				}
				else
				{
					outData[i] = sqrt(inData[i]);
				}
			}
		}

		std::vector<T> inData;
		std::vector<T> outData;
	};

	struct NormalVector4fMultTest
	{
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 500000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr bool DO_TEST = true;

		NormalVector4fMultTest()
		{
		}
		void Prepare()
		{
			inData.resize(NUM_LOOPS);
			mults.resize(NUM_LOOPS);
			outData.resize(NUM_LOOPS);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				inData[i] = EmuMath::Vector4<float>(rand() % 100, rand() % 100, rand() % 100, rand() % 100) * 0.75f;
				mults[i] = EmuMath::Vector4<float>(rand() % 250, rand() % 250, rand() % 250, rand() % 250) * 0.75f;
				outData[i] = EmuMath::Vector4<float>(0.0f, 0.0f, 0.0f, 0.0f);
			}
		}
		void operator()(std::size_t i)
		{
			outData[i] = (inData[i] * mults[i]) * 0.5f;
		}

		std::vector<EmuMath::Vector4<float>> inData;
		std::vector<EmuMath::Vector4<float>> outData;
		std::vector<EmuMath::Vector4<float>> mults;
	};
	struct FastVector4fMultTest_WithLoad
	{
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 500000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr bool DO_TEST = true;

		FastVector4fMultTest_WithLoad()
		{
		}

		void Prepare()
		{
			inData.resize(NUM_LOOPS);
			mults.resize(NUM_LOOPS);
			outData.resize(NUM_LOOPS);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				inData[i] = EmuMath::FastVector<4, float>(rand() % 100, rand() % 100, rand() % 100, rand() % 100);
				mults[i] = EmuMath::Vector4<float>(rand() % 250, rand() % 250, rand() % 250, rand() % 250) * 0.75f;
				outData[i] = EmuMath::FastVector<4, float>(0.0f, 0.0f, 0.0f, 0.0f);
			}
		}
		void operator()(std::size_t i)
		{
			outData[i] = (inData[i] * EmuMath::FastVector<4, float>(mults[i])) * 0.5f;
		}

		std::vector<EmuMath::FastVector<4, float>> inData;
		std::vector<EmuMath::FastVector<4, float>> outData;
		std::vector<EmuMath::Vector4<float>> mults;
	};
	struct FastVector4fMultTest_WithoutLoad
	{
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 500000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr bool DO_TEST = true;

		FastVector4fMultTest_WithoutLoad()
		{
		}

		void Prepare()
		{
			inData.resize(NUM_LOOPS);
			mults.resize(NUM_LOOPS);
			outData.resize(NUM_LOOPS);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				inData[i] = EmuMath::FastVector<4, float>(rand() % 100, rand() % 100, rand() % 100, rand() % 100);
				mults[i] = EmuMath::FastVector<4, float>(rand() % 250, rand() % 250, rand() % 250, rand() % 250) * 0.75f;
				outData[i] = EmuMath::FastVector<4, float>(0.0f, 0.0f, 0.0f, 0.0f);
			}
		}
		void operator()(std::size_t i)
		{
			outData[i] = (inData[i] * mults[i]) * 0.5f;
		}

		std::vector<EmuMath::FastVector<4, float>> inData;
		std::vector<EmuMath::FastVector<4, float>> outData;
		std::vector<EmuMath::FastVector<4, float>> mults;
	};

	using SqrtTestFP = float;

	using AllTests = std::tuple
	<
		TestA<float>,
		VectorwiseShiftTest<std::int16_t>,
		SqrtTest<SqrtTestFP, true>,
		SqrtTest<SqrtTestFP, false>,
		NormalVector4fMultTest,
		FastVector4fMultTest_WithLoad,
		FastVector4fMultTest_WithoutLoad
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

	void OnAllTestsOver(AllTests& tests)
	{
		std::string inputStr;
		if (std::get<0>(tests).DO_TEST)
		{
			std::cout << "Dump Test 0 output? [Y- Yes]: ";
			std::getline(std::cin, inputStr);

			if (inputStr.size() != 0)
			{
				if (inputStr[0] == 'Y' || inputStr[0] == 'y')
				{
					std::cout << "\n\n\n\n-----DUMP-----";
					for (auto& data_ : std::get<0>(tests).outData)
					{
						std::cout << data_ << "\n";
					}
					std::cout << "-----END OF DUMP-----\n\n\n";
				}
			}
			std::cout << "\n";
		}

		if (std::get<1>(tests).DO_TEST)
		{
			using _TestBT_ = std::tuple_element_t<1, AllTests>;
			_TestBT_& _testB = std::get<1>(tests);
			std::ostringstream str;
			str << "Decimal:\n";
			for (std::size_t i = 0; i < _TestBT_::NUM_LOOPS; ++i)
			{
				str << "Left Shift [" << i << "]: " << _testB.outLeftShift[i] << "\n";
				str << "Right Shift [" << i << "]: " << _testB.outRightShift[i] << "\n\n";
			}
			str << "Binary:\n";
			for (std::size_t i = 0; i < _TestBT_::NUM_LOOPS; ++i)
			{
				str << "Left Shift [" << i << "]:  " << _testB.outLeftBits[i] << "\n";
				str << "Right Shift [" << i << "]: " << _testB.outRightBits[i] << "\n\n";
			}
			std::cout << str.str();
		}

		if (std::get<4>(tests).DO_TEST)
		{
			std::cout << std::get<4>(tests).outData[rand() % std::get<4>(tests).NUM_LOOPS] << "\n";
		}
		if (std::get<5>(tests).DO_TEST)
		{
			std::cout << std::get<5>(tests).outData[rand() % std::get<5>(tests).NUM_LOOPS] << "\n";
		}
		if (std::get<6>(tests).DO_TEST)
		{
			std::cout << std::get<6>(tests).outData[rand() % std::get<6>(tests).NUM_LOOPS] << "\n";
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
			if (test.DO_TEST)
			{
				std::cout << harness.ExecuteAndOutputAsString<Test::PASS_LOOP_NUM>(Test::NUM_LOOPS, test, test.WRITE_ALL_TIMES_TO_STREAM) << "\n\n";
			}
			else
			{
				std::cout << "Test skipped through DO_TEST member being false.\n\n";
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
