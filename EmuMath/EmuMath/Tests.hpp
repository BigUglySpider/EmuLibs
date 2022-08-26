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
#include "EmuMath/FastMatrix.h"
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

	struct EmuNormalMatrixTest
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 5000000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "Emu Matrix Mult";

		static constexpr std::size_t vec_size = 4;
		using t_arg = float;
		using mat_type = EmuMath::Matrix<4, 4, t_arg, false>;
		using vec_type = EmuMath::Vector<4, t_arg>;

		EmuNormalMatrixTest()
		{
		}
		void Prepare()
		{
			// FILLS
			out_mats.resize(NUM_LOOPS);

			// RESERVES
			lhs.reserve(NUM_LOOPS);
			rhs.reserve(NUM_LOOPS);

			// RESERVED FILLS
			EmuMath::RngWrapper<true> rng_(-100, 100, shared_fill_seed_);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				vec_type vecs[4];
				vecs[0] = make_random_vec<vec_type, t_arg, 4>(rng_);
				vecs[1] = make_random_vec<vec_type, t_arg, 4>(rng_);
				vecs[2] = make_random_vec<vec_type, t_arg, 4>(rng_);
				vecs[3] = make_random_vec<vec_type, t_arg, 4>(rng_);
				lhs.emplace_back(mat_type(vecs[0], vecs[1], vecs[2], vecs[3]));

				vecs[0] = make_random_vec<vec_type, t_arg, 4>(rng_);
				vecs[1] = make_random_vec<vec_type, t_arg, 4>(rng_);
				vecs[2] = make_random_vec<vec_type, t_arg, 4>(rng_);
				vecs[3] = make_random_vec<vec_type, t_arg, 4>(rng_);
				rhs.emplace_back(mat_type(vecs[0], vecs[1], vecs[2], vecs[3]));
			}
		}
		void operator()(std::size_t i_)
		{
			out_mats[i_] = lhs[i_].Multiply(rhs[i_]);
		}
		void OnTestsOver()
		{
			const std::size_t i_ = EmuMath::RngWrapper<true>(shared_select_seed_).NextInt<std::size_t>(0, NUM_LOOPS - 1);
			std::cout << lhs[i_] << "\nMUL\n" << rhs[i_] << "\n=\n" << out_mats[i_] << "\n\n";
		}

		std::vector<mat_type> out_mats;
		std::vector<mat_type> lhs;
		std::vector<mat_type> rhs;
	};

	struct EmuFastMatrixTest
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 5000000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "Emu FastMatrix Mult";

		static constexpr std::size_t vec_size = 4;
		using t_arg = float;
		using mat_type = EmuMath::FastMatrix<4, 4, t_arg, false, 128>;
		using vec_type = EmuMath::FastVector<4, t_arg, 128>;

		EmuFastMatrixTest()
		{
		}
		void Prepare()
		{
			// FILLS
			out_mats.resize(NUM_LOOPS);

			// RESERVES
			lhs.reserve(NUM_LOOPS);
			rhs.reserve(NUM_LOOPS);

			// RESERVED FILLS
			EmuMath::RngWrapper<true> rng_(-100, 100, shared_fill_seed_);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				vec_type vecs[4];
				vecs[0] = make_random_vec<vec_type, t_arg, 4>(rng_);
				vecs[1] = make_random_vec<vec_type, t_arg, 4>(rng_);
				vecs[2] = make_random_vec<vec_type, t_arg, 4>(rng_);
				vecs[3] = make_random_vec<vec_type, t_arg, 4>(rng_);
				lhs.emplace_back(mat_type(vecs[0], vecs[1], vecs[2], vecs[3]));

				vecs[0] = make_random_vec<vec_type, t_arg, 4>(rng_);
				vecs[1] = make_random_vec<vec_type, t_arg, 4>(rng_);
				vecs[2] = make_random_vec<vec_type, t_arg, 4>(rng_);
				vecs[3] = make_random_vec<vec_type, t_arg, 4>(rng_);
				rhs.emplace_back(mat_type(vecs[0], vecs[1], vecs[2], vecs[3]));
			}
		}
		void operator()(std::size_t i_)
		{
			out_mats[i_] = lhs[i_].Multiply(rhs[i_]);
		}
		void OnTestsOver()
		{
			const std::size_t i_ = EmuMath::RngWrapper<true>(shared_select_seed_).NextInt<std::size_t>(0, NUM_LOOPS - 1);
			std::cout << lhs[i_] << "\nMUL\n" << rhs[i_] << "\n=\n" << out_mats[i_] << "\n\n";
		}

		std::vector<mat_type> out_mats;
		std::vector<mat_type> lhs;
		std::vector<mat_type> rhs;
	};

	struct DirectXSimdTest
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 5000000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "DirectX Mat Mult";

		static constexpr std::size_t vec_size = 4;
		using t_arg = float;
		using mat_type = DirectX::XMMATRIX;
		using vec_type = DirectX::XMFLOAT4;

		DirectXSimdTest()
		{
		}
		void Prepare()
		{
			// FILLS
			out_mats.resize(NUM_LOOPS);

			// RESERVES
			lhs.reserve(NUM_LOOPS);
			rhs.reserve(NUM_LOOPS);

			// RESERVED FILLS
			EmuMath::RngWrapper<true> rng_(-100, 100, shared_fill_seed_);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				vec_type vecs[4];
				vecs[0] = make_random_vec<vec_type, t_arg, 4>(rng_);
				vecs[1] = make_random_vec<vec_type, t_arg, 4>(rng_);
				vecs[2] = make_random_vec<vec_type, t_arg, 4>(rng_);
				vecs[3] = make_random_vec<vec_type, t_arg, 4>(rng_);
				lhs.emplace_back(make_mat(vecs[0], vecs[1], vecs[2], vecs[3]));

				vecs[0] = make_random_vec<vec_type, t_arg, 4>(rng_);
				vecs[1] = make_random_vec<vec_type, t_arg, 4>(rng_);
				vecs[2] = make_random_vec<vec_type, t_arg, 4>(rng_);
				vecs[3] = make_random_vec<vec_type, t_arg, 4>(rng_);
				rhs.emplace_back(make_mat(vecs[0], vecs[1], vecs[2], vecs[3]));
			}
		}
		void operator()(std::size_t i_)
		{
			out_mats[i_] = DirectX::XMMatrixMultiply(lhs[i_], rhs[i_]);
		}
		void OnTestsOver()
		{
			const std::size_t i_ = EmuMath::RngWrapper<true>(shared_select_seed_).NextInt<std::size_t>(0, NUM_LOOPS - 1);
			print_mat(lhs[i_]) << "\nMUL\n";
			print_mat(rhs[i_]) << " =\n";
			print_mat(out_mats[i_]) << "\n\n";
		}

		template<bool Is64Bit_>
		static vec_type make_vector(EmuMath::RngWrapper<Is64Bit_>& rng_)
		{
			vec_type vec = make_random_vec<vec_type, float, 4>(rng_);
			return DirectX::XMLoadFloat4(&vec);
		}

		static std::ostream& print_vector(DirectX::XMVECTOR vec)
		{
			vec_type floatx;
			DirectX::XMStoreFloat4(&floatx, vec);
			return print_floatx(floatx);
		}

		static std::ostream& print_floatx(DirectX::XMFLOAT4 floatx)
		{
			std::cout << "{ " << floatx.x << ", " << floatx.y << ", " << floatx.z << ", " << floatx.w << " }";
			return std::cout;
		}

		static std::ostream& print_mat(DirectX::XMMATRIX mat)
		{
			DirectX::XMFLOAT4X4 mat4x4;
			DirectX::XMStoreFloat4x4(&mat4x4, mat);
			return print_mat4x4(mat4x4);
		}

		static std::ostream& print_mat4x4(DirectX::XMFLOAT4X4 mat4x4)
		{
			for (auto i = 0; i < 4; ++i)
			{
				std::cout << "{ ";
				for (auto j = 0; j < 4; ++j)
				{
					std::cout << mat4x4(i, j) << ", ";
				}
				std::cout << " }\n";
			}
			return std::cout;
		}

		static mat_type make_mat(const vec_type& a, const vec_type& b, const vec_type& c, const vec_type& d)
		{
			return mat_type
			(
				DirectX::XMLoadFloat4(&a),
				DirectX::XMLoadFloat4(&b),
				DirectX::XMLoadFloat4(&c),
				DirectX::XMLoadFloat4(&d)
			);
		}

		std::vector<mat_type> out_mats;
		std::vector<mat_type> lhs;
		std::vector<mat_type> rhs;
	};

	// ----------- TESTS SELECTION -----------
	using AllTests = std::tuple
	<
		EmuNormalMatrixTest,
		EmuFastMatrixTest,
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
