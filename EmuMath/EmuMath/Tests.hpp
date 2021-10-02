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
#include "EmuMath/FastMatrix.h"
#include <bitset>
#include <DirectXMath.h>
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
			static constexpr typename EmuCore::TMPHelpers::first_floating_point<T_, float>::type MULT_ = 
			static_cast<typename EmuCore::TMPHelpers::first_floating_point<T_, float>::type>(0.001f);

			if constexpr (std::numeric_limits<T_>::max() < std::numeric_limits<int>::max())
			{
				return static_cast<T_>
				(
					static_cast<T_>(rand() % static_cast<int>(std::numeric_limits<T_>::max())) * MULT_
				);
			}
			else
			{
				return static_cast<T_>(static_cast<T_>(rand()) * MULT_);
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

	constexpr unsigned int shared_seed_ = 6166;
	constexpr unsigned int shared_seed_b_ = 6;

	struct MatEmu
	{
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 500000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr bool DO_TEST = true;
		static constexpr std::string_view NAME = "Matrix (EmuMath SIMD)";

		MatEmu()
		{
		}
		void Prepare()
		{
			srand(shared_seed_);
			//lhs_.resize(NUM_LOOPS);
			//rhs_.resize(NUM_LOOPS);
			out_.resize(NUM_LOOPS);
			angles_.resize(NUM_LOOPS);
			EmuMath::Matrix4x4<float, true> temp_;
			VectorFiller filler_ = VectorFiller();

			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				//temp_ = temp_.Mutate(filler_);
				//lhs_[i] = EmuMath::FastMatrix4x4f_CM(temp_);
				//temp_ = temp_.Mutate(filler_);
				//rhs_[i] = EmuMath::FastMatrix4x4f_CM(temp_);

				angles_[i] = filler_(angles_[i]);
			}
		}
		void operator()(std::size_t i)
		{
			//out_[i] = lhs_[i].Multiply(rhs_[i]);
			out_[i] = EmuMath::FastMatrix4x4f_CM::RotationX<false>(angles_[i]);
		}
		void OnTestsOver()
		{
			srand(shared_seed_b_);
			std::size_t i = static_cast<std::size_t>(rand()) % NUM_LOOPS;
			//std::cout << lhs_[i] << "\nMULT\n" << rhs_[i] << "\n:\n" << out_[i] << "\n\n";
			std::cout << "RotX(" << angles_[i] << "):\n" << out_[i] << "\n\n";
		}

		//std::vector<EmuMath::FastMatrix4x4f_CM> lhs_;
		//std::vector<EmuMath::FastMatrix4x4f_CM> rhs_;
		std::vector<EmuMath::FastMatrix4x4f_CM> out_;
		std::vector<float> angles_;
	};
	struct MatEmuSISD
	{
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 500000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr bool DO_TEST = true;
		static constexpr std::string_view NAME = "Matrix (EmuMath SISD)";

		MatEmuSISD()
		{
		}
		void Prepare()
		{
			srand(shared_seed_);
			lhs_.resize(NUM_LOOPS);
			rhs_.resize(NUM_LOOPS);
			out_.resize(NUM_LOOPS);
			EmuMath::Matrix4x4<float, true> temp_;
			VectorFiller filler_ = VectorFiller();
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				temp_ = temp_.Mutate(filler_);
				lhs_[i] = temp_;
				temp_ = temp_.Mutate(filler_);
				rhs_[i] = temp_;
			}
		}
		void operator()(std::size_t i)
		{
			out_[i] = lhs_[i].Multiply(rhs_[i]);
		}
		void OnTestsOver()
		{
			srand(shared_seed_b_);
			std::size_t i = static_cast<std::size_t>(rand()) % NUM_LOOPS;
			std::cout << lhs_[i] << "\nMULT\n" << rhs_[i] << "\n:\n" << out_[i] << "\n\n";
		}

		std::vector<EmuMath::Matrix4x4<float>> lhs_;
		std::vector<EmuMath::Matrix4x4<float>> rhs_;
		std::vector<EmuMath::Matrix4x4<float>> out_;
	};
	struct MatDXM
	{
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 500000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr bool DO_TEST = true;
		static constexpr std::string_view NAME = "Matrix (DirectXMath)";

		MatDXM()
		{
		}
		void Prepare()
		{
			srand(shared_seed_);
			//lhs_.resize(NUM_LOOPS);
			//rhs_.resize(NUM_LOOPS);
			out_.resize(NUM_LOOPS);
			angles_.resize(NUM_LOOPS);

			EmuMath::Matrix4x4<float, true> temp_;
			VectorFiller filler_ = VectorFiller();
			//DirectX::XMFLOAT4X4 to_load_;
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				//temp_ = temp_.Mutate(filler_);
				//to_load_ = MakeXMFromEmu(temp_);
				//lhs_[i] = DirectX::XMLoadFloat4x4(&to_load_);
				//temp_ = temp_.Mutate(filler_);
				//to_load_ = MakeXMFromEmu(temp_);
				//rhs_[i] = DirectX::XMLoadFloat4x4(&to_load_);

				angles_[i] = filler_(angles_[i]);
			}
		}
		void operator()(std::size_t i)
		{
			//out_[i] = DirectX::XMMatrixMultiply(lhs_[i], rhs_[i]);
			out_[i] = DirectX::XMMatrixRotationX(EmuCore::Pi::DegsToRads(angles_[i]));
		}

		DirectX::XMFLOAT4X4 MakeXMFromEmu(const EmuMath::Matrix4x4<float, true>& mat_) const
		{
			//return DirectX::XMFLOAT4X4
			//(
			//	mat_.at<0, 0>(), mat_.at<0, 1>(), mat_.at<0, 2>(), mat_.at<0, 3>(),
			//	mat_.at<1, 0>(), mat_.at<1, 1>(), mat_.at<1, 2>(), mat_.at<1, 3>(),
			//	mat_.at<2, 0>(), mat_.at<2, 1>(), mat_.at<2, 2>(), mat_.at<2, 3>(),
			//	mat_.at<3, 0>(), mat_.at<3, 1>(), mat_.at<3, 2>(), mat_.at<3, 3>()
			//);

			return DirectX::XMFLOAT4X4
			(
				mat_.at<0, 0>(), mat_.at<1, 0>(), mat_.at<2, 0>(), mat_.at<3, 0>(),
				mat_.at<0, 1>(), mat_.at<1, 1>(), mat_.at<2, 1>(), mat_.at<3, 1>(),
				mat_.at<0, 2>(), mat_.at<1, 2>(), mat_.at<2, 2>(), mat_.at<3, 2>(),
				mat_.at<0, 3>(), mat_.at<1, 3>(), mat_.at<2, 3>(), mat_.at<3, 3>()
			);
		}
		void OnTestsOver()
		{
			srand(shared_seed_b_);
			std::size_t i = static_cast<std::size_t>(rand() % NUM_LOOPS);
			//PrintMatrix(lhs_[i]);
			//std::cout << "\nMULT\n";
			//PrintMatrix(rhs_[i]);
			//std::cout << "\n:\n";
			//PrintMatrix(out_[i]);
			//std::cout << "\n\n";
			std::cout << "RotX(" << angles_[i] << "):\n";
			PrintMatrix(out_[i]);
			std::cout << "\n\n";
		}

		void PrintMatrix(const DirectX::XMMATRIX& mat_) const
		{
			DirectX::XMFLOAT4X4 readable_mat_;
			DirectX::XMStoreFloat4x4(&readable_mat_, mat_);
			for (std::size_t x = 0; x < 4; ++x)
			{
				std::cout << "{ ";
				for (std::size_t y = 0; y < 4; ++y)
				{
					std::cout << readable_mat_(x, y);
					if (y != 3)
					{
						std::cout << ", ";
					}
				}
				std::cout << " }\n";
			}
		}


		//std::vector<DirectX::XMMATRIX> lhs_;
		//std::vector<DirectX::XMMATRIX> rhs_;
		std::vector<float> angles_;
		std::vector<DirectX::XMMATRIX> out_;
	};

	using AllTests = std::tuple
	<
		MatEmu,
		MatDXM
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
