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
#include "EmuMath/FastVector.h"
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

	template<class OutVec_, typename T_, std::size_t...Indices_>
	[[nodiscard]] inline OutVec_ make_vec_from_data(const T_* p_data_, std::index_sequence<Indices_...> indices_)
	{
		return OutVec_((*(p_data_ + Indices_))...);
	}

	template<class OutVec_, typename T_, std::size_t Size_, bool Is64Bit_>
	[[nodiscard]] inline OutVec_ make_random_vec(EmuMath::RngWrapper<Is64Bit_>& rng_)
	{
		T_ out_[Size_];
		for (std::size_t i = 0; i < Size_; ++i)
		{
			if constexpr (std::is_floating_point_v<EmuCore::TMP::remove_ref_cv_t<T_>>)
			{
				out_[i] = rng_.NextReal<T_>();
			}
			else
			{
				out_[i] = rng_.NextInt<T_>();
			}
		}

		return make_vec_from_data<OutVec_>(out_, std::make_index_sequence<Size_>());
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

	struct EmuFastVectorTest
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 500000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "Emu FastVector";

		static constexpr std::size_t vec_size = 4;
		using vec_t_arg = float;
		using fast_vector_type = EmuMath::FastVector<vec_size, vec_t_arg>;
		using vector_type = typename fast_vector_type::vector_type;
		using lhs_type = fast_vector_type;
		using rhs_type = fast_vector_type;
		using output_type = fast_vector_type;

		EmuFastVectorTest()
		{
		}
		void Prepare()
		{
			// FILLS
			out_vecs.resize(NUM_LOOPS);

			// RESERVES
			lhs.reserve(NUM_LOOPS);
			rhs.reserve(NUM_LOOPS);

			// RESERVED FILLS
			EmuMath::RngWrapper<true> rng_(-100, 100, shared_fill_seed_);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				lhs.emplace_back(make_random_vec<lhs_type, vec_t_arg, vec_size>(rng_));
				rhs.emplace_back(make_random_vec<lhs_type, vec_t_arg, vec_size>(rng_));
			}
		}
		void operator()(std::size_t i_)
		{
			// ADD
			out_vecs[i_] = lhs[i_].Mod(rhs[i_]);
		}
		void OnTestsOver()
		{
			const std::size_t i_ = EmuMath::RngWrapper<true>(shared_select_seed_).NextInt<std::size_t>(0, NUM_LOOPS - 1);
			std::cout << lhs[i_] << " +\n" << rhs[i_] << " =\n" << out_vecs[i_] << "\n\n";
		}

		std::vector<lhs_type> lhs;
		std::vector<rhs_type> rhs;
		std::vector<output_type> out_vecs;
	};

	struct DirectXSimdTest
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 500000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "DirectX SIMD";

		static constexpr std::size_t vec_size = 4;
		using vec_t_arg = float;
		using fast_vector_type = DirectX::XMVECTOR;
		using vector_type = DirectX::XMFLOAT4;
		using lhs_type = fast_vector_type;
		using rhs_type = fast_vector_type;
		using output_type = fast_vector_type;

		DirectXSimdTest()
		{
		}
		void Prepare()
		{
			// FILLS
			out_vecs.resize(NUM_LOOPS);

			// RESERVES
			lhs.reserve(NUM_LOOPS);
			rhs.reserve(NUM_LOOPS);

			// RESERVED FILLS
			EmuMath::RngWrapper<true> rng_(-100, 100, shared_fill_seed_);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				lhs.emplace_back(make_vector(rng_));
				rhs.emplace_back(make_vector(rng_));
			}
		}
		void operator()(std::size_t i_)
		{
			out_vecs[i_] = DirectX::XMVectorMod(lhs[i_], rhs[i_]);
		}
		void OnTestsOver()
		{
			const std::size_t i_ = EmuMath::RngWrapper<true>(shared_select_seed_).NextInt<std::size_t>(0, NUM_LOOPS - 1);
			print_vector(lhs[i_]) << " +\n";
			print_vector(rhs[i_]) << " =\n";
			print_vector(out_vecs[i_]) << "\n\n";
		}

		template<bool Is64Bit_>
		static fast_vector_type make_vector(EmuMath::RngWrapper<Is64Bit_>& rng_)
		{
			vector_type vec = make_random_vec<vector_type, vec_t_arg, vec_size>(rng_);
			return DirectX::XMLoadFloat4(&vec);
		}

		static std::ostream& print_vector(DirectX::XMVECTOR vec)
		{
			vector_type floatx;
			DirectX::XMStoreFloat4(&floatx, vec);
			return print_floatx(floatx);
		}

		static std::ostream& print_floatx(DirectX::XMFLOAT4 floatx)
		{
			std::cout << "{ " << floatx.x << ", " << floatx.y << ", " << floatx.z << ", " << floatx.w << " }";
			return std::cout;
		}

		std::vector<lhs_type> lhs;
		std::vector<rhs_type> rhs;
		std::vector<output_type> out_vecs;
	};

	// ----------- TESTS SELECTION -----------
	using AllTests = std::tuple
	<
		EmuFastVectorTest,
		DirectXSimdTest
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
