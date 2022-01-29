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

	template<std::size_t Size_, typename OutT_, class OutColl_, class RngFunc_>
	inline void emplace_back_vector(OutColl_& out_coll_, RngFunc_& func_)
	{
		out_coll_.emplace_back
		(
			EmuMath::Helpers::vector_mutate<Size_, OutT_, RngFunc_&>(func_, OutT_())
		);
	}

	template<class Vector_, class OutColl_, class RngFunc_>
	inline void emplace_back_old_vector(OutColl_& out_coll_, RngFunc_& func_)
	{
		Vector_ vec_ = Vector_();
		out_coll_.emplace_back(EmuMath::Helpers::vector_mutate(vec_, std::ref(func_)));
	}

	struct RngFunctor
	{
	private:
		template
		<
			typename T_,
			bool IsValidOut_ = 
			(
				std::is_integral_v<EmuCore::TMP::remove_ref_cv_t<T_>> ||
				std::is_floating_point_v<EmuCore::TMP::remove_ref_cv_t<T_>>
			)
	>
		struct _out_type
		{
			using type = float;
		};
		template<typename T_>
		struct _out_type<T_, true>
		{
			using type = EmuCore::TMP::remove_ref_cv_t<T_>;
		};

	public:
		using rng_type = EmuMath::RngWrapper<true>;
		using seed_type = rng_type::unsigned_int_type;

		RngFunctor() : _rng()
		{
		}
		template<class...ConstructionArgs_, typename = std::enable_if_t<std::is_constructible_v<rng_type, ConstructionArgs_&&...>>>
		RngFunctor(ConstructionArgs_&&...construction_args_) : _rng(std::forward<ConstructionArgs_>(construction_args_)...)
		{
		}

		template<typename T_>
		constexpr inline typename _out_type<T_>::type operator()(const T_& dummy_)
		{
			if constexpr (std::is_integral_v<typename _out_type<T_>::type>)
			{
				return _rng.NextInt<typename _out_type<T_>::type>();
			}
			else
			{
				return _rng.NextReal<typename _out_type<T_>::type>();
			}
		}

		rng_type _rng;
	};

	template<class Matrix_, class Arr_, std::size_t...FlattenedIndices_>
	[[nodiscard]] inline Matrix_ make_mat_from_arr(Arr_& arr_, std::index_sequence<FlattenedIndices_...>)
	{
		return Matrix_(arr_[FlattenedIndices_]...);
	}

	template<class Matrix_, class Rng_>
	[[nodiscard]] inline Matrix_ make_random_matrix(Rng_& rng_)
	{
		using indices = EmuMath::TMP::make_full_matrix_index_sequences<Matrix_>;
		std::array<typename Matrix_::stored_type, Matrix_::size> out_array_;
		for (std::size_t i = 0; i < Matrix_::size; ++i)
		{
			out_array_[i] = rng_(typename Matrix_::stored_type());
		}
		return make_mat_from_arr<Matrix_>(out_array_, std::make_index_sequence<Matrix_::size>());
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
		void operator()(std::size_t i)
		{
		}
		void OnTestsOver()
		{
		}
	};

	struct reflect_test_emu
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 500000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "Vector Reflect (Emu)";

		static constexpr std::size_t vec_size = 3;
		using vector_type_arg = float;
		using vector_type = EmuMath::Vector<vec_size, vector_type_arg>;
		using float_type = typename vector_type::preferred_floating_point;
		using vector_type_fp = EmuMath::Vector<vec_size, float_type>;

		reflect_test_emu()
		{
		}
		void Prepare()
		{
			// RESIZES
			out_reflection.resize(NUM_LOOPS);

			// RESERVES
			in_ray.reserve(NUM_LOOPS);
			in_norm.reserve(NUM_LOOPS);

			// FILL RESERVES
			RngFunctor rng_ = RngFunctor(shared_fill_seed_);
			rng_._rng.SetMinMax(-1000, 1000);

			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				emplace_back_vector<vec_size, vector_type_arg>(in_ray, rng_);
				emplace_back_vector<vec_size, float_type>(in_norm, rng_);
				in_norm[i] = in_norm[i].Normalise();
			}
		}
		void operator()(std::size_t i)
		{
			out_reflection[i] = in_ray[i].Reflect(in_norm[i]);
		}
		void OnTestsOver()
		{
			const std::size_t i_ = RngFunctor(shared_select_seed_)._rng.NextInt<std::size_t>() % NUM_LOOPS;
			std::cout << "REFLECT\n(\n\t" << in_ray[i_] << "\n\t" << in_norm[i_] << "\n" << "): " << out_reflection[i_] << "\n\n";
		}

		std::vector<vector_type> in_ray;
		std::vector<vector_type_fp> in_norm;
		std::vector<vector_type_fp> out_reflection;
	};

	struct reflect_test_dxm
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 500000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "Vector Reflect (DXM)";

		reflect_test_dxm()
		{
		}
		void Prepare()
		{
			// RESIZES
			out_reflection.resize(NUM_LOOPS);

			// RESERVES
			in_ray.reserve(NUM_LOOPS);
			in_norm.reserve(NUM_LOOPS);

			// FILL RESERVES
			RngFunctor rng_ = RngFunctor(shared_fill_seed_);
			rng_._rng.SetMinMax(-1000, 1000);

			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				in_ray.emplace_back
				(
					rng_(0.0f), rng_(0.0f), rng_(0.0f)
				);
				in_norm.emplace_back
				(
					rng_(0.0f), rng_(0.0f), rng_(0.0f)
				);
				DirectX::XMStoreFloat3
				(
					&(in_norm[i]), 
					DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&(in_norm[i])))
				);
			}
		}
		void operator()(std::size_t i)
		{
			DirectX::XMStoreFloat3
			(
				&(out_reflection[i]),
				DirectX::XMVector3Reflect
				(
					DirectX::XMLoadFloat3(&(in_ray[i])),
					DirectX::XMLoadFloat3(&(in_norm[i]))
				)
			);
		}
		void OnTestsOver()
		{
			const std::size_t i_ = RngFunctor(shared_select_seed_)._rng.NextInt<std::size_t>() % NUM_LOOPS;
			std::cout << "REFLECT\n(\n\t";
			Print(in_ray[i_]);
			std::cout << "\n\t";
			Print(in_norm[i_]);
			std::cout << "\n" << "): ";
			Print(out_reflection[i_]);
			std::cout << "\n\n";
		}
		void Print(const DirectX::XMFLOAT3& vector_)
		{
			std::cout << "{ " << vector_.x << ", " << vector_.y << ", " << vector_.z << " }";
		}

		std::vector<DirectX::XMFLOAT3> in_ray;
		std::vector<DirectX::XMFLOAT3> in_norm;
		std::vector<DirectX::XMFLOAT3> out_reflection;
	};

	struct matrix_test_dxm
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 500000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "Matrix Mutate (DXM)";

		static constexpr std::size_t num_columns = 4;
		static constexpr std::size_t num_rows = 4;
		static constexpr bool column_major = true;
		using t_arg = float;
		using out_type = DirectX::XMFLOAT4X4;
		using in_a_type = out_type;
		using in_b_type = float;

		matrix_test_dxm()
		{
		}
		void Prepare()
		{
			// RESIZES
			out.resize(NUM_LOOPS);
			in_a.resize(NUM_LOOPS);
			in_b.resize(NUM_LOOPS);

			// RESERVED FILLS
			RngFunctor rng_(shared_fill_seed_);
			rng_._rng.SetMinMax(0, 25);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				make_dxm_mat(in_a[i], rng_);
				make_dxm_mat_all_same(in_b[i], rng_);
			}
		}
		void operator()(std::size_t i)
		{
			out[i]._11 = in_a[i]._11 + in_b[i]._11;
			out[i]._12 = in_a[i]._12 + in_b[i]._12;
			out[i]._13 = in_a[i]._13 + in_b[i]._13;
			out[i]._14 = in_a[i]._14 + in_b[i]._14;
			
			out[i]._21 = in_a[i]._21 + in_b[i]._21;
			out[i]._22 = in_a[i]._22 + in_b[i]._22;
			out[i]._23 = in_a[i]._23 + in_b[i]._23;
			out[i]._24 = in_a[i]._24 + in_b[i]._24;
			
			out[i]._31 = in_a[i]._31 + in_b[i]._31;
			out[i]._32 = in_a[i]._32 + in_b[i]._32;
			out[i]._33 = in_a[i]._33 + in_b[i]._33;
			out[i]._34 = in_a[i]._34 + in_b[i]._34;
			
			out[i]._41 = in_a[i]._41 + in_b[i]._41;
			out[i]._42 = in_a[i]._42 + in_b[i]._42;
			out[i]._43 = in_a[i]._43 + in_b[i]._43;
			out[i]._44 = in_a[i]._44 + in_b[i]._44;

			//DirectX::XMStoreFloat4
			//(
			//	reinterpret_cast<DirectX::XMFLOAT4*>(out[i].m[0]),
			//	DirectX::XMVectorAdd
			//	(
			//		DirectX::XMLoadFloat4(reinterpret_cast<const DirectX::XMFLOAT4*>(in_a[i].m[0])),
			//		DirectX::XMLoadFloat4(reinterpret_cast<const DirectX::XMFLOAT4*>(in_b[i].m[0]))
			//	)
			//);
			//
			//DirectX::XMStoreFloat4
			//(
			//	reinterpret_cast<DirectX::XMFLOAT4*>(out[i].m[1]),
			//	DirectX::XMVectorAdd
			//	(
			//		DirectX::XMLoadFloat4(reinterpret_cast<const DirectX::XMFLOAT4*>(in_a[i].m[1])),
			//		DirectX::XMLoadFloat4(reinterpret_cast<const DirectX::XMFLOAT4*>(in_b[i].m[1]))
			//	)
			//);
			//
			//DirectX::XMStoreFloat4
			//(
			//	reinterpret_cast<DirectX::XMFLOAT4*>(out[i].m[2]),
			//	DirectX::XMVectorAdd
			//	(
			//		DirectX::XMLoadFloat4(reinterpret_cast<const DirectX::XMFLOAT4*>(in_a[i].m[2])),
			//		DirectX::XMLoadFloat4(reinterpret_cast<const DirectX::XMFLOAT4*>(in_b[i].m[2]))
			//	)
			//);
			//
			//DirectX::XMStoreFloat4
			//(
			//	reinterpret_cast<DirectX::XMFLOAT4*>(out[i].m[3]),
			//	DirectX::XMVectorAdd
			//	(
			//		DirectX::XMLoadFloat4(reinterpret_cast<const DirectX::XMFLOAT4*>(in_a[i].m[3])),
			//		DirectX::XMLoadFloat4(reinterpret_cast<const DirectX::XMFLOAT4*>(in_b[i].m[3]))
			//	)
			//);
		}
		void OnTestsOver()
		{
			const std::size_t i_ = RngFunctor(shared_select_seed_)._rng.NextInt<std::size_t>() % NUM_LOOPS;
			print_dxm_mat(in_a[i_]);
			std::cout << "\n\n";
		}

		static inline void make_dxm_mat(DirectX::XMFLOAT4X4& out_, RngFunctor& rng_)
		{
			float _00 = rng_._rng.NextReal<float>();
			float _01 = rng_._rng.NextReal<float>();
			float _02 = rng_._rng.NextReal<float>();
			float _03 = rng_._rng.NextReal<float>();
			float _10 = rng_._rng.NextReal<float>();
			float _11 = rng_._rng.NextReal<float>();
			float _12 = rng_._rng.NextReal<float>();
			float _13 = rng_._rng.NextReal<float>();
			float _20 = rng_._rng.NextReal<float>();
			float _21 = rng_._rng.NextReal<float>();
			float _22 = rng_._rng.NextReal<float>();
			float _23 = rng_._rng.NextReal<float>();
			float _30 = rng_._rng.NextReal<float>();
			float _31 = rng_._rng.NextReal<float>();
			float _32 = rng_._rng.NextReal<float>();
			float _33 = rng_._rng.NextReal<float>();
			//float _00 = 1;
			//float _01 = 2;
			//float _02 = 3;
			//float _03 = 4;
			//float _10 = 5;
			//float _11 = 6;
			//float _12 = 7;
			//float _13 = 8;
			//float _20 = 9;
			//float _21 = 10;
			//float _22 = 11;
			//float _23 = 12;
			//float _30 = 13;
			//float _31 = 14;
			//float _32 = 15;
			//float _33 = 16;
			out_ = DirectX::XMFLOAT4X4(_00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33);
		}

		static inline void make_dxm_mat_all_same(DirectX::XMFLOAT4X4& out_, RngFunctor& rng_)
		{
			const float val_ = rng_._rng.NextReal<float>();
			out_ = DirectX::XMFLOAT4X4(val_, val_, val_, val_, val_, val_, val_, val_, val_, val_, val_, val_, val_, val_, val_, val_);
		}

		static inline void print_dxm_mat(const DirectX::XMFLOAT4X4& mat_)
		{
			for (std::size_t x = 0; x < 4; ++x)
			{
				std::cout << "{ " << mat_(x, 0);
				for (std::size_t y = 1; y < 4; ++y)
				{
					std::cout << ", " << mat_(x, y);
				}
				std::cout << " }\n";
			}

			const float* data_ = reinterpret_cast<const float*>(&mat_);
			std::cout << "{ ";
			std::cout << *data_;
			for (std::size_t i = 1; i < 16; ++i)
			{
				std::cout << ", " << *(data_ + i);
			}
			std::cout << " }\n\n";
		}

		std::vector<DirectX::XMFLOAT4X4> in_a;
		std::vector<DirectX::XMFLOAT4X4> in_b;
		std::vector<DirectX::XMFLOAT4X4> out;
	};

	struct matrix_test_void_template
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = 500000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "Matrix Mutate (Void Template Args)";

		static constexpr std::size_t num_columns = 4;
		static constexpr std::size_t num_rows = 4;
		static constexpr bool column_major = false; // Just to appear identically to dxm in terms of where our random args are
		using t_arg = float;
		using out_type = EmuMath::Matrix<num_columns, num_rows, t_arg, column_major>;
		using in_a_type = out_type;
		using in_a_type_column_major = EmuMath::Matrix<in_a_type::num_columns, in_a_type::num_rows, in_a_type::stored_type, true>;
		using in_b_type = float;

		matrix_test_void_template()
		{
		}
		void Prepare()
		{
			// RESIZES
			out.resize(NUM_LOOPS);

			// RESERVES
			in_a.reserve(NUM_LOOPS);
			in_b.reserve(NUM_LOOPS);

			// RESERVED FILLS
			RngFunctor rng_(shared_fill_seed_);
			rng_._rng.SetMinMax(0, 25);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				//in_a.push_back(in_a_type(in_a_type_column_major(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)));
				in_a.push_back(make_random_matrix<in_a_type>(rng_));
				in_b.push_back(in_b_type(rng_._rng.NextReal<float>()));
			}
		}
		void operator()(std::size_t i)
		{
			//EmuMath::Helpers::matrix_mutate_to(out[i], EmuCore::do_add<void>(), in_a[i], in_b[i]);
			out[i] = in_a[i] + in_b[i];
		}
		void OnTestsOver()
		{
			const std::size_t i_ = RngFunctor(shared_select_seed_)._rng.NextInt<std::size_t>() % NUM_LOOPS;
			std::cout << in_a[i_] << "\n";
			
			const float* data_ = reinterpret_cast<const float*>(&in_a[i_]);
			std::cout << "{ ";
			std::cout << *data_;
			for (std::size_t i = 1; i < 16; ++i)
			{
				std::cout << ", " << *(data_ + i);
			}
			std::cout << " }\n\n";
		}

		std::vector<in_a_type> in_a;
		std::vector<in_b_type> in_b;
		std::vector<out_type> out;
	};

	// ----------- TESTS SELECTION -----------
	using AllTests = std::tuple
	<
		matrix_test_void_template,
		matrix_test_dxm
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
