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
			if constexpr (std::numeric_limits<T_>::max() < std::numeric_limits<int>::max())
			{
				return static_cast<T_>((rand() % static_cast<int>(std::numeric_limits<T_>::max())) * 0.9f);
			}
			else
			{
				return static_cast<T_>(rand() * 0.9f);
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

	struct ProjMatEmu
	{
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 5000000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr bool DO_TEST = false;
		static constexpr std::string_view NAME = "Projection Creation (EmuMath)";

		ProjMatEmu()
		{
		}
		void Prepare()
		{
			srand(shared_seed_);
			near_.resize(NUM_LOOPS);
			far_.resize(NUM_LOOPS);
			fov_.resize(NUM_LOOPS);
			aspect_ratio_.resize(NUM_LOOPS);
			out_.resize(NUM_LOOPS);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				near_[i] = static_cast<float>((rand() % 10) + 1) * 0.1f;
				far_[i] = static_cast<float>(rand() % 1000 + 2);
				fov_[i] = EmuCore::Pi::DegsToRads(45.0f + static_cast<float>(rand() % 46));
				aspect_ratio_[i] = 1920.0f / 1080.0f;
			}
		}
		void operator()(std::size_t i)
		{
			out_[i] = EmuMath::Helpers::MatrixPerspectiveVK<true, float, true, 10, true>(fov_[i], near_[i], far_[i], aspect_ratio_[i]);
			//out_[i] = EmuMath::Helpers::MatrixOrthographicVK(1920, 1080, near_[i], far_[i]);
		}
		void OnTestsOver()
		{
			srand(shared_seed_b_);
			std::size_t i = static_cast<std::size_t>(rand() % NUM_LOOPS);
			std::cout << "Perspective(Near: " << near_[i] << ", Far: " << far_[i] << ", FOV: " << fov_[i] << ", Aspect Ratio: " << aspect_ratio_[i] << "):\n";
			//std::cout << "Orthographic(width: 1920, height: 1080, near: " << near_[i] << ", far: " << far_[i] << "):\n";
			std::cout << out_[i] << "\n";

			EmuMath::Vector3<float> vector_ = EmuMath::Vector3<float>(1.0f, 2.0f, 182154.3f);
			std::cout << "Vector: " << vector_ << "\nTransformed: " << EmuMath::Helpers::MatrixMultiplyVector(out_[i], vector_) << "\n";
		}

		std::vector<float> near_;
		std::vector<float> far_;
		std::vector<float> fov_;
		std::vector<float> aspect_ratio_;
		std::vector<EmuMath::Matrix<4, 4, float, true>> out_;
	};
	struct ProjMatDXM
	{
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 5000000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr bool DO_TEST = false;
		static constexpr std::string_view NAME = "Projection Creation (DirectXMath)";

		ProjMatDXM()
		{
		}
		void Prepare()
		{
			srand(shared_seed_);
			near_.resize(NUM_LOOPS);
			far_.resize(NUM_LOOPS);
			fov_.resize(NUM_LOOPS);
			aspect_ratio_.resize(NUM_LOOPS);
			out_.resize(NUM_LOOPS, DirectX::XMFLOAT4X4(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f));
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				near_[i] = static_cast<float>((rand() % 10) + 1) * 0.1f;
				far_[i] = static_cast<float>(rand() % 1000 + 2);
				fov_[i] = EmuCore::Pi::DegsToRads(45.0f + static_cast<float>(rand() % 46));
				aspect_ratio_[i] = 1920.0f / 1080.0f;
			}
		}
		void operator()(std::size_t i)
		{
			DirectX::XMMATRIX mat_ = DirectX::XMMatrixPerspectiveFovRH(fov_[i], aspect_ratio_[i], near_[i], far_[i]);
			//DirectX::XMMATRIX mat_ = DirectX::XMMatrixOrthographicRH(1920.0f, 1080.0f, near_[i], far_[i]);
			DirectX::XMStoreFloat4x4(&out_[i], mat_);
		}
		void OnTestsOver()
		{
			srand(shared_seed_b_);
			std::size_t i = static_cast<std::size_t>(rand() % NUM_LOOPS);
			std::cout << "Perspective(Near: " << near_[i] << ", Far: " << far_[i] << ", FOV: " << fov_[i] << ", Aspect Ratio: " << aspect_ratio_[i] << "):\n";
			//std::cout << "Orthographic(width: 1920, height: 1080, near: " << near_[i] << ", far: " << far_[i] << "):\n";
			for (std::size_t x = 0; x < 4; ++x)
			{
				std::cout << "{ ";
				for (std::size_t y = 0; y < 4; ++y)
				{
					std::cout << out_[i](y, x);
					if (y != 3)
					{
						std::cout << ", ";
					}
				}
				std::cout << " }\n";
			}
			DirectX::XMFLOAT3 vector_(1.0f, 2.0f, 182154.3f);
			DirectX::XMVECTOR transf_ = DirectX::XMLoadFloat3(&vector_);
			transf_ = DirectX::XMVector3Transform(transf_, DirectX::XMLoadFloat4x4(&out_[i]));
			DirectX::XMFLOAT3 result_;
			DirectX::XMStoreFloat3(&result_, transf_);
			std::cout << "Vector: { " << vector_.x << ", " << vector_.y << ", " << vector_.z << " }\n";
			std::cout << "Transformed: { " << result_.x << ", " << result_.y << ", " << result_.z << " }\n";
		}

		std::vector<float> near_;
		std::vector<float> far_;
		std::vector<float> fov_;
		std::vector<float> aspect_ratio_;
		std::vector<DirectX::XMFLOAT4X4> out_;
	};

	struct SomeSpeedTest
	{
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 5000000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr bool DO_TEST = true;
		static constexpr std::string_view NAME = "Example";

		using MinMax_ = EmuMath::Matrix<4, 4, float, true>;

		template<std::size_t ColumnIndex_ = 0, std::size_t RowIndex_ = 0>
		static constexpr inline void _set_min_max(MinMax_& out_min_, MinMax_& out_max_)
		{
			if constexpr (EmuMath::TMP::is_emu_matrix_v<MinMax_>)
			{
				if constexpr (ColumnIndex_ < MinMax_::num_columns)
				{
					if constexpr (RowIndex_ < MinMax_::num_rows)
					{
						MinMax_::raw_value_type& current_min = EmuMath::Helpers::MatrixGet<ColumnIndex_, RowIndex_>(out_min_);
						MinMax_::raw_value_type& current_max = EmuMath::Helpers::MatrixGet<ColumnIndex_, RowIndex_>(out_max_);
						current_min = rand() * 0.9f;
						current_max = rand() * 0.9f;
						if (current_min > current_max)
						{
							MinMax_::value_type temp_ = current_min;
							current_min = current_max;
							current_max = temp_;
						}
						_set_min_max<ColumnIndex_, RowIndex_ + 1>(out_min_, out_max_);
					}
					else
					{
						_set_min_max<ColumnIndex_ + 1, 0>(out_min_, out_max_);
					}
				}
			}
			else
			{
				//out_min_ = rand() * 0.9f;
				//out_max_ = rand() * 0.9f;
				//if (out_min_ > out_max_)
				//{
				//	MinMax_ temp_ = out_min_;
				//	out_min_ = out_max_;
				//	out_max_ = temp_;
				//}
			}
		}

		SomeSpeedTest()
		{
		}
		void Prepare()
		{
			in_.resize(NUM_LOOPS);
			out_.resize(NUM_LOOPS);
			min_.resize(NUM_LOOPS);
			max_.resize(NUM_LOOPS);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				EmuMath::Helpers::MatrixMutate(in_[i], in_[i], VectorFiller());
				_set_min_max<0, 0>(min_[i], max_[i]);
				//min_[i] = in_[i] + 1;
				//max_[i] = in_[i] + 2;
			}
		}
		void operator()(std::size_t i)
		{
			out_[i] = EmuMath::Helpers::MatrixClamp<4, 4, float, true>(in_[i], min_[i], max_[i]);
		}
		void OnTestsOver()
		{
			std::size_t i = static_cast<std::size_t>(rand() % NUM_LOOPS);
			std::cout << "ORIGINAL:\n" << in_[i] << "\nMIN:\n" << min_[i] << "\nMAX:\n" << max_[i] << "\nCLAMPED:\n" << out_[i] << "\n\n";
		}

		std::vector<EmuMath::Matrix<4, 4, float, true>> in_;
		std::vector<EmuMath::Matrix<4, 4, float, true>> out_;
		std::vector<MinMax_> min_;
		std::vector<MinMax_> max_;
	};

	using AllTests = std::tuple
	<
		SomeSpeedTest
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
