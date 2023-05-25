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
#include "EmuMath/FastQuaternion.h"
#include "EmuMath/FastVector.h"
#include "EmuMath/Matrix.h"
#include "EmuMath/Vector.h"
#include "EmuMath/Random.h"
#include "EmuMath/Quaternion.h"
#include <bitset>
#include <string_view>

#if defined(WIN32) || defined(WIN64) || defined(_WIN32) || defined(_WIN64)
#define USE_DIRECTX_TESTS 1
#else
#define USE_DIRECTX_TESTS 0
#endif

#if USE_DIRECTX_TESTS
#include <DirectXMath.h>
#endif

inline bool get_yes_or_no(const std::string& message, std::istream& in_stream_, std::string&& overwriteable_buffer = std::string())
{
	std::cout << message << " (Y/N): ";
	while(true)
	{
		std::getline(in_stream_, overwriteable_buffer);
		std::transform
		(
			overwriteable_buffer.begin(),
			overwriteable_buffer.end(),
			overwriteable_buffer.begin(),
			[](const auto& char_){ return std::tolower(char_); }
		);
		if(overwriteable_buffer.length() > 0) // Redo if no answer
		{
			switch(overwriteable_buffer[0])
			{
				case 'a':
				{
					if(overwriteable_buffer == "affirm" || overwriteable_buffer == "accept" || overwriteable_buffer == "affirmative")
						return true;
					break;
				}
				case 'c':
				{
					if(overwriteable_buffer == "c" || overwriteable_buffer == "confirm" || overwriteable_buffer == "consent")
						return true;
					break;
				}
				case 'd':
				{
					if(overwriteable_buffer == "d" || overwriteable_buffer == "deny" || overwriteable_buffer == "decline")
						return false;
					break;
				}
				case 'n':
				{
					if(overwriteable_buffer == "n" || overwriteable_buffer == "no" || overwriteable_buffer == "nope" || overwriteable_buffer == "negative" || overwriteable_buffer == "nah" || overwriteable_buffer == "nay")
						return false;
					break;
				}
				case 'r':
				{
					if(overwriteable_buffer == "reject" || overwriteable_buffer == "refuse")
						return false;
					break;
				}
				case 'y':
				{
					if(overwriteable_buffer == "y" || overwriteable_buffer == "yes" || overwriteable_buffer == "yep" || overwriteable_buffer == "yeah" || overwriteable_buffer == "yea")
						return true;
					break;
				}
			}
		}
	}
}

inline bool get_yes_or_no(const std::string& message, std::string&& overwriteable_buffer = std::string())
{
	return get_yes_or_no(message, std::cin, std::forward<decltype(overwriteable_buffer)>(overwriteable_buffer));
}

namespace EmuCore::TestingHelpers
{
	static constexpr std::size_t shared_num_loops = 5000000;
	static constexpr unsigned long long shared_fill_seed_ = 1337;
	static constexpr unsigned long long shared_select_seed_ = -25;

	template<typename T_, auto...ToDiscard_, bool Is64Bit_>
	[[nodiscard]] inline T_ get_random_val(EmuMath::RngWrapper<Is64Bit_>& rng_)
	{
		if constexpr (std::is_integral_v<T_>)
		{
			return rng_.template NextInt<T_>();
		}
		else
		{
			return rng_.template NextReal<T_>();
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
				out_[i] = rng_.template NextReal<T_>();
			}
			else
			{
				out_[i] = rng_.template NextInt<T_>();
			}
		}

		return make_vec_from_data<OutVec_>(out_, std::make_index_sequence<Size_>());
	}

	/// <summary> Example which only contains the required items for the test harness. </summary>
	struct ExampleTest
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = shared_num_loops;
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

#pragma region EMU_VS_DXM
	struct EmuNormalMatrixTest
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = shared_num_loops;
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
		static constexpr std::size_t NUM_LOOPS = shared_num_loops;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "Emu FastMatrix Mult";

		static constexpr std::size_t vec_size = 4;
		using t_arg = float;
		using mat_type = EmuMath::Matrix<4, 4, t_arg, false>;
		using fast_mat_type = EmuMath::FastMatrix<4, 4, t_arg, false, 128>;
		using vec_type = EmuMath::Vector<4, t_arg>;

		EmuFastMatrixTest()
		{
		}
		void Prepare()
		{
			// FILLS
			out_mats.resize(NUM_LOOPS);
			determinants.resize(NUM_LOOPS);

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
			//out_mats[i_] = lhs[i_].Multiply(rhs[i_]);
			//EmuMath::Helpers::fast_matrix_store
			//(
			//	EmuMath::Helpers::fast_matrix_multiply
			//	(
			//		fast_mat_type(lhs[i_]),
			//		fast_mat_type(rhs[i_])
			//	),
			//	out_mats[i_]
			//);
			//(fast_mat_type(lhs[i_]) * fast_mat_type(rhs[i_])).Store(out_mats[i_]);
			EmuMath::Helpers::fast_matrix_store
			(
				//EmuMath::Helpers::fast_matrix_add(fast_mat_type(lhs[i_]), fast_mat_type(rhs[i_])),
				EmuMath::Helpers::fast_matrix_inverse(fast_mat_type(lhs[i_]), determinants[i_]),
				out_mats[i_]
			);
		}
		void OnTestsOver()
		{
			const std::size_t i = EmuMath::RngWrapper<true>(shared_select_seed_).NextInt<std::size_t>(0, NUM_LOOPS - 1);
			//std::cout << lhs[i] << "\nMUL\n" << rhs[i] << "\n=\n" << out_mats[i] << "\n\n";
			std::cout << lhs[i] << "\nINVERSE:\n" << out_mats[i] << "\n(Determinant: " << determinants[i] << ")\n\n";
		}

		std::vector<mat_type> out_mats;
		std::vector<mat_type> lhs;
		std::vector<mat_type> rhs;
		std::vector<t_arg> determinants;
	};

#if USE_DIRECTX_TESTS
	struct DirectXSimdTest
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = shared_num_loops;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "DirectX Mat Mult";

		static constexpr std::size_t vec_size = 4;
		using t_arg = float;
		using mat_type = DirectX::XMFLOAT4X4;
		using fast_mat_type = DirectX::XMMATRIX;
		using vec_type = DirectX::XMFLOAT4;

		DirectXSimdTest()
		{
		}
		void Prepare()
		{
			// FILLS
			out_mats.resize(NUM_LOOPS);
			determinants.resize(NUM_LOOPS);

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
			//out_mats[i_] = DirectX::XMMatrixMultiply(lhs[i_], rhs[i_]);
			DirectX::XMVECTOR det_vec;
			DirectX::XMStoreFloat4x4
			(
				&(out_mats[i_]),
				DirectX::XMMatrixInverse
				(
					&det_vec,
					DirectX::XMLoadFloat4x4(&(lhs[i_]))
				)
			);
			DirectX::XMStoreFloat(&(determinants[i_]), det_vec);

#pragma region PER_VECTOR
			//DirectX::XMStoreFloat4
			//(
			//	reinterpret_cast<DirectX::XMFLOAT4*>(&(out_mats[i_](0, 0))),
			//	DirectX::XMVectorAdd
			//	(
			//		DirectX::XMLoadFloat4(reinterpret_cast<DirectX::XMFLOAT4*>(&lhs[i_](0, 0))),
			//		DirectX::XMLoadFloat4(reinterpret_cast<DirectX::XMFLOAT4*>(&rhs[i_](0, 0)))
			//	)
			//);
			//
			//DirectX::XMStoreFloat4
			//(
			//	reinterpret_cast<DirectX::XMFLOAT4*>(&(out_mats[i_](1, 0))),
			//	DirectX::XMVectorAdd
			//	(
			//		DirectX::XMLoadFloat4(reinterpret_cast<DirectX::XMFLOAT4*>(&lhs[i_](1, 0))),
			//		DirectX::XMLoadFloat4(reinterpret_cast<DirectX::XMFLOAT4*>(&rhs[i_](1, 0)))
			//	)
			//);
			//
			//DirectX::XMStoreFloat4
			//(
			//	reinterpret_cast<DirectX::XMFLOAT4*>(&(out_mats[i_](2, 0))),
			//	DirectX::XMVectorAdd
			//	(
			//		DirectX::XMLoadFloat4(reinterpret_cast<DirectX::XMFLOAT4*>(&lhs[i_](2, 0))),
			//		DirectX::XMLoadFloat4(reinterpret_cast<DirectX::XMFLOAT4*>(&rhs[i_](2, 0)))
			//	)
			//);
			//
			//DirectX::XMStoreFloat4
			//(
			//	reinterpret_cast<DirectX::XMFLOAT4*>(&(out_mats[i_](3, 0))),
			//	DirectX::XMVectorAdd
			//	(
			//		DirectX::XMLoadFloat4(reinterpret_cast<DirectX::XMFLOAT4*>(&lhs[i_](3, 0))),
			//		DirectX::XMLoadFloat4(reinterpret_cast<DirectX::XMFLOAT4*>(&rhs[i_](3, 0)))
			//	)
			//);
#pragma endregion
		}
		void OnTestsOver()
		{
			const std::size_t i = EmuMath::RngWrapper<true>(shared_select_seed_).NextInt<std::size_t>(0, NUM_LOOPS - 1);
			//print_mat(lhs[i]) << "\nMUL\n";
			//print_mat(rhs[i]) << " =\n";
			//print_mat(out_mats[i]) << "\n\n";

			print_mat(lhs[i]) << "\nINVERSE:\n";
			print_mat(out_mats[i]) << "(Determinant: " << determinants[i] << ")\n\n";
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
			return print_mat(mat4x4);
		}

		static std::ostream& print_mat(DirectX::XMFLOAT4X4 mat4x4)
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
			//return mat_type
			//(
			//	DirectX::XMLoadFloat4(&a),
			//	DirectX::XMLoadFloat4(&b),
			//	DirectX::XMLoadFloat4(&c),
			//	DirectX::XMLoadFloat4(&d)
			//);
			return mat_type
			(
				a.x, a.y, a.z, a.w,
				b.x, b.y, b.z, b.w,
				c.x, c.y, c.z, c.w,
				d.x, d.y, d.z, d.w
			);
		}

		std::vector<mat_type> out_mats;
		std::vector<mat_type> lhs;
		std::vector<mat_type> rhs;
		std::vector<float> determinants;
	};
#endif
#pragma endregion

#pragma region EMU_VS_EMU
	struct ScalarQuaternionTest
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = shared_num_loops;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "Scalar Quaternion";

		using quat_t = double;
		using euler_type = EmuMath::Vector<3, quat_t>;
		using quaternion_type = EmuMath::Quaternion<quat_t>;
		static constexpr bool in_rads = false;
		static constexpr bool norm_out = false;

		ScalarQuaternionTest()
		{
		}
		void Prepare()
		{
			// FILLS
			res.resize(NUM_LOOPS);

			// RESERVES
			lhs.reserve(NUM_LOOPS);
			rhs.reserve(NUM_LOOPS);
			EmuMath::RngWrapper<true> rng(-90, 90, shared_fill_seed_);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				auto euler = make_random_vec<euler_type, quat_t, 3>(rng);
				lhs.emplace_back(quaternion_type::from_euler(std::move(euler)));
				
				euler = make_random_vec<euler_type, quat_t, 3>(rng);
				rhs.emplace_back(quaternion_type::from_euler(std::move(euler)));
			}
		}
		void operator()(std::size_t i_)
		{
			res[i_] = lhs[i_] * rhs[i_];
		}
		void OnTestsOver()
		{
			const std::size_t i = EmuMath::RngWrapper<true>(shared_select_seed_).NextInt<std::size_t>(0, NUM_LOOPS - 1);
			std::cout << lhs[i] << " * " << rhs[i] << " = " << res[i] << "\n\n";
		}

		std::vector<quaternion_type> lhs;
		std::vector<quaternion_type> rhs;
		std::vector<quaternion_type> res;
	};

	struct FastQuaternionTest
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = shared_num_loops;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "Fast Quaternion";

		using quat_t = double;
		using euler_type = EmuMath::Vector<3, quat_t>;
		using quaternion_type = EmuMath::FastQuaternion<quat_t, 128>;
		using scalar_quaternion_type = EmuMath::Quaternion<quat_t>;
		static constexpr bool in_rads = false;
		static constexpr bool norm_out = false;

		FastQuaternionTest()
		{
		}
		void Prepare()
		{
			// FILLS
			res.resize(NUM_LOOPS);

			// RESERVES
			lhs.reserve(NUM_LOOPS);
			rhs.reserve(NUM_LOOPS);
			EmuMath::RngWrapper<true> rng(-90, 90, shared_fill_seed_);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				auto euler = make_random_vec<euler_type, quat_t, 3>(rng);
				lhs.emplace_back(quaternion_type(scalar_quaternion_type::from_euler(std::move(euler))));

				euler = make_random_vec<euler_type, quat_t, 3>(rng);
				rhs.emplace_back(quaternion_type(scalar_quaternion_type::from_euler(std::move(euler))));
			}
		}
		void operator()(std::size_t i_)
		{
			res[i_] = lhs[i_] * rhs[i_];
		}
		void OnTestsOver()
		{
			const std::size_t i = EmuMath::RngWrapper<true>(shared_select_seed_).NextInt<std::size_t>(0, NUM_LOOPS - 1);
			std::cout << lhs[i] << " * " << rhs[i] << " = " << res[i] << "\n\n";
		}

		std::vector<quaternion_type> lhs;
		std::vector<quaternion_type> rhs;
		std::vector<quaternion_type> res;
	};

	template<class T_>
	decltype(auto) do_print(const T_* p_data_, std::size_t length_)
	{
		if (length_ == 0)
		{
			std::cout << "{ }";
		}
		else if (length_ == 1)
		{
			std::cout << "{ " << (*p_data_) << " }";
		}
		else
		{
			std::cout << "{ " << (*p_data_);
			for (std::size_t i = 1; i < length_; ++i)
			{
				std::cout << ", " << (*(p_data_ + i));
			}
			std::cout << " }";
		}
	}

	struct ScalarTan
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t BASE_NUM_LOOPS = 64000000;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "(Scalar)";

		using scalar_type = float;
		static constexpr std::size_t NUM_LOOPS = BASE_NUM_LOOPS / 1;
		static constexpr std::size_t total_scalars = NUM_LOOPS * 1;
		static constexpr std::size_t print_max_size = 20;

		ScalarTan()
		{
		}
		void Prepare()
		{
			out.resize(total_scalars);

			in.reserve(total_scalars);
			rhs.reserve(total_scalars);
			EmuMath::RngWrapper<true> rng(-90, 90, shared_fill_seed_);
			for (std::size_t i = 0; i < total_scalars; ++i)
			{
				in.emplace_back(rng.NextReal<scalar_type>());
				rhs.emplace_back(rng.NextReal<scalar_type>());
			}
		}
		void operator()(std::size_t i_)
		{
			//out[i_] = tan(in[i_]);
			out[i_] = in[i_] + rhs[i_];
		}
		void OnTestsOver()
		{
			const std::size_t i = EmuMath::RngWrapper<true>(shared_select_seed_).NextInt<std::size_t>(0, total_scalars - 1);
			std::size_t used_print_size;
			if ((i + print_max_size) <= total_scalars)
			{
				used_print_size = print_max_size;
			}
			else
			{
				used_print_size = total_scalars - i;
			}
			do_print(out.data() + i, used_print_size);
			std::cout << "\n\n";
		}

		std::vector<scalar_type> in;
		std::vector<scalar_type> rhs;
		std::vector<scalar_type> out;
	};

	struct SIMDTan128
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t BASE_NUM_LOOPS = ScalarTan::BASE_NUM_LOOPS;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "(SIMD 128)";

		using scalar_type = float;
		static constexpr std::size_t register_width = 128;
		static constexpr std::size_t scalar_width = sizeof(scalar_type) * 8;
		static constexpr bool scalar_signed = std::is_signed_v<scalar_type>;
		static constexpr std::size_t elements_per_register = register_width / scalar_width;
		static constexpr std::size_t NUM_LOOPS = BASE_NUM_LOOPS / elements_per_register;
		static constexpr std::size_t total_scalars = NUM_LOOPS * elements_per_register;
		static constexpr std::size_t print_max_size = ScalarTan::print_max_size;
		using register_type = EmuSIMD::TMP::register_type<scalar_type, register_width>::type;

		SIMDTan128()
		{
		}
		void Prepare()
		{
			out.resize(total_scalars);

			in.reserve(total_scalars);
			rhs.reserve(total_scalars);
			EmuMath::RngWrapper<true> rng(-90, 90, shared_fill_seed_);
			for (std::size_t i = 0; i < total_scalars; ++i)
			{
				in.emplace_back(rng.NextReal<scalar_type>());
				rhs.emplace_back(rng.NextReal<scalar_type>());
			}
		}
		void operator()(std::size_t i_)
		{
			std::size_t offset = i_ * elements_per_register;
			auto reg = EmuSIMD::load<register_type>(in.data() + offset);
			//reg = EmuSIMD::tan<scalar_width, scalar_signed>(reg);
			reg = EmuSIMD::add<scalar_width>(reg, EmuSIMD::load<register_type>(rhs.data() + offset));
			EmuSIMD::store(std::move(reg), out.data() + offset);
		}
		void OnTestsOver()
		{
			const std::size_t i = EmuMath::RngWrapper<true>(shared_select_seed_).NextInt<std::size_t>(0, total_scalars - 1);
			std::size_t used_print_size;
			if ((i + print_max_size) <= total_scalars)
			{
				used_print_size = print_max_size;
			}
			else
			{
				used_print_size = total_scalars - i;
			}
			do_print(out.data() + i, used_print_size);
			std::cout << "\n\n";
		}

		std::vector<scalar_type> in;
		std::vector<scalar_type> rhs;
		std::vector<scalar_type> out;
	};

	struct SIMDTan256
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t BASE_NUM_LOOPS = ScalarTan::BASE_NUM_LOOPS;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "(SIMD 256)";

		using scalar_type = float;
		static constexpr std::size_t register_width = 256;
		static constexpr std::size_t scalar_width = sizeof(scalar_type) * 8;
		static constexpr bool scalar_signed = std::is_signed_v<scalar_type>;
		static constexpr std::size_t elements_per_register = register_width / scalar_width;
		static constexpr std::size_t NUM_LOOPS = BASE_NUM_LOOPS / elements_per_register;
		static constexpr std::size_t total_scalars = NUM_LOOPS * elements_per_register;
		static constexpr std::size_t print_max_size = ScalarTan::print_max_size;
		using register_type = EmuSIMD::TMP::register_type<scalar_type, register_width>::type;

		SIMDTan256()
		{
		}
		void Prepare()
		{
			out.resize(total_scalars);

			in.reserve(total_scalars);
			rhs.reserve(total_scalars);
			EmuMath::RngWrapper<true> rng(-90, 90, shared_fill_seed_);
			for (std::size_t i = 0; i < total_scalars; ++i)
			{
				in.emplace_back(rng.NextReal<scalar_type>());
				rhs.emplace_back(rng.NextReal<scalar_type>());
			}
		}
		void operator()(std::size_t i_)
		{
			std::size_t offset = i_ * elements_per_register;
			auto reg = EmuSIMD::load<register_type>(in.data() + offset);
			//reg = EmuSIMD::tan<scalar_width, scalar_signed>(reg);
			reg = EmuSIMD::add<scalar_width>(reg, EmuSIMD::load<register_type>(rhs.data() + offset));
			EmuSIMD::store(std::move(reg), out.data() + offset);
		}
		void OnTestsOver()
		{
			const std::size_t i = EmuMath::RngWrapper<true>(shared_select_seed_).NextInt<std::size_t>(0, total_scalars - 1);
			std::size_t used_print_size;
			if ((i + print_max_size) <= total_scalars)
			{
				used_print_size = print_max_size;
			}
			else
			{
				used_print_size = total_scalars - i;
			}
			do_print(out.data() + i, used_print_size);
			std::cout << "\n\n";
		}

		std::vector<scalar_type> in;
		std::vector<scalar_type> rhs;
		std::vector<scalar_type> out;
	};

	struct SIMDTan512
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t BASE_NUM_LOOPS = ScalarTan::BASE_NUM_LOOPS;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "(SIMD 512)";

		using scalar_type = float;
		static constexpr std::size_t register_width = 512;
		static constexpr std::size_t scalar_width = sizeof(scalar_type) * 8;
		static constexpr bool scalar_signed = std::is_signed_v<scalar_type>;
		static constexpr std::size_t elements_per_register = register_width / scalar_width;
		static constexpr std::size_t NUM_LOOPS = BASE_NUM_LOOPS / elements_per_register;
		static constexpr std::size_t total_scalars = NUM_LOOPS * elements_per_register;
		static constexpr std::size_t print_max_size = ScalarTan::print_max_size;
		using register_type = EmuSIMD::TMP::register_type<scalar_type, register_width>::type;

		SIMDTan512()
		{
		}
		void Prepare()
		{
			out.resize(total_scalars);

			in.reserve(total_scalars);
			rhs.reserve(total_scalars);
			EmuMath::RngWrapper<true> rng(-90, 90, shared_fill_seed_);
			for (std::size_t i = 0; i < total_scalars; ++i)
			{
				in.emplace_back(rng.NextReal<scalar_type>());
				rhs.emplace_back(rng.NextReal<scalar_type>());
			}
		}
		void operator()(std::size_t i_)
		{
			std::size_t offset = i_ * elements_per_register;
			auto reg = EmuSIMD::load<register_type>(in.data() + offset);
			//reg = EmuSIMD::tan<scalar_width, scalar_signed>(reg);
			reg = EmuSIMD::add<scalar_width>(reg, EmuSIMD::load<register_type>(rhs.data() + offset));
			EmuSIMD::store(std::move(reg), out.data() + offset);
		}
		void OnTestsOver()
		{
			const std::size_t i = EmuMath::RngWrapper<true>(shared_select_seed_).NextInt<std::size_t>(0, total_scalars - 1);
			std::size_t used_print_size;
			if ((i + print_max_size) <= total_scalars)
			{
				used_print_size = print_max_size;
			}
			else
			{
				used_print_size = total_scalars - i;
			}
			do_print(out.data() + i, used_print_size);
			std::cout << "\n\n";
		}

		std::vector<scalar_type> in;
		std::vector<scalar_type> rhs;
		std::vector<scalar_type> out;
	};

	struct FastMatFromScalarQuaternionTest
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = shared_num_loops;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "Rotation FastMatrix from Quaternion (scalar)";

		using value_type = double;
		static constexpr std::size_t matrix_columns = 4;
		static constexpr std::size_t matrix_rows = 4;
		static constexpr bool matrix_column_major = true;
		static constexpr std::size_t register_width = 128;

		using euler_type = EmuMath::Vector<3, value_type>;
		using quaternion_type = EmuMath::Quaternion<value_type>;
		using matrix_type = EmuMath::FastMatrix<matrix_columns, matrix_rows, value_type, matrix_column_major, register_width>;
		static constexpr bool in_rads = false;
		static constexpr bool norm_out = false;

		FastMatFromScalarQuaternionTest()
		{
		}
		void Prepare()
		{
			// FILLS
			rot_matrices.resize(NUM_LOOPS);

			// RESERVES
			rot_quaternions.reserve(NUM_LOOPS);
			EmuMath::RngWrapper<true> rng(-90, 90, shared_fill_seed_);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				auto euler = make_random_vec<euler_type, value_type, 3>(rng);
				rot_quaternions.emplace_back(quaternion_type::from_euler<false, true>(std::move(euler)));
			}
		}
		void operator()(std::size_t i_)
		{
			rot_matrices[i_] = matrix_type::make_rotation_3d(rot_quaternions[i_]);
		}
		void OnTestsOver()
		{
			const std::size_t i = EmuMath::RngWrapper<true>(shared_select_seed_).NextInt<std::size_t>(0, NUM_LOOPS - 1);
			std::cout << rot_quaternions[i] << ":\n" << rot_matrices[i] << "\n\n";
		}

		std::vector<quaternion_type> rot_quaternions;
		std::vector<matrix_type> rot_matrices;
	};

	struct FastMatFromFastQuaternionTest
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = shared_num_loops;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "Rotation FastMatrix from Quaternion (SIMD)";

		using value_type = double;
		static constexpr std::size_t matrix_columns = 4;
		static constexpr std::size_t matrix_rows = 4;
		static constexpr bool matrix_column_major = true;
		static constexpr std::size_t matrix_register_width = 128;
		static constexpr std::size_t quaternion_register_width = matrix_register_width;

		using euler_type = EmuMath::Vector<3, value_type>;
		using quaternion_type = EmuMath::FastQuaternion<value_type, quaternion_register_width>;
		using matrix_type = EmuMath::FastMatrix<matrix_columns, matrix_rows, value_type, matrix_column_major, matrix_register_width>;
		static constexpr bool in_rads = false;
		static constexpr bool norm_out = false;

		FastMatFromFastQuaternionTest()
		{
		}
		void Prepare()
		{
			// FILLS
			rot_matrices.resize(NUM_LOOPS);

			// RESERVES
			rot_quaternions.reserve(NUM_LOOPS);
			EmuMath::RngWrapper<true> rng(-90, 90, shared_fill_seed_);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				auto euler = make_random_vec<euler_type, value_type, 3>(rng);
				rot_quaternions.emplace_back(quaternion_type::from_euler<false, true>(std::move(euler)));
			}
		}
		void operator()(std::size_t i_)
		{
			rot_matrices[i_] = matrix_type::make_rotation_3d(rot_quaternions[i_]);
		}
		void OnTestsOver()
		{
			const std::size_t i = EmuMath::RngWrapper<true>(shared_select_seed_).NextInt<std::size_t>(0, NUM_LOOPS - 1);
			std::cout << rot_quaternions[i] << ":\n" << rot_matrices[i] << "\n\n";
		}

		std::vector<quaternion_type> rot_quaternions;
		std::vector<matrix_type> rot_matrices;
	};

	

	struct ScalarMatFromScalarQuaternionTest
	{
		static constexpr bool DO_TEST = true;
		static constexpr bool PASS_LOOP_NUM = true;
		static constexpr std::size_t NUM_LOOPS = shared_num_loops;
		static constexpr bool WRITE_ALL_TIMES_TO_STREAM = false;
		static constexpr std::string_view NAME = "Rotation Scalar Matrix from Quaternion (scalar)";

		using value_type = float;
		static constexpr std::size_t matrix_columns = 4;
		static constexpr std::size_t matrix_rows = 4;
		static constexpr bool matrix_column_major = true;

		using euler_type = EmuMath::Vector<3, value_type>;
		using quaternion_type = EmuMath::Quaternion<value_type>;
		using matrix_type = EmuMath::Matrix<matrix_columns, matrix_rows, value_type, matrix_column_major>;
		static constexpr bool in_rads = false;
		static constexpr bool norm_out = false;

		ScalarMatFromScalarQuaternionTest()
		{
		}
		void Prepare()
		{
			// FILLS
			rot_matrices.resize(NUM_LOOPS);

			// RESERVES
			rot_quaternions.reserve(NUM_LOOPS);
			EmuMath::RngWrapper<true> rng(-90, 90, shared_fill_seed_);
			for (std::size_t i = 0; i < NUM_LOOPS; ++i)
			{
				auto euler = make_random_vec<euler_type, value_type, 3>(rng);
				rot_quaternions.emplace_back(quaternion_type::from_euler<false, true>(std::move(euler)));
			}
		}
		void operator()(std::size_t i_)
		{
			rot_matrices[i_] = matrix_type::make_rotation_3d(rot_quaternions[i_]);
		}
		void OnTestsOver()
		{
			const std::size_t i = EmuMath::RngWrapper<true>(shared_select_seed_).NextInt<std::size_t>(0, NUM_LOOPS - 1);
			std::cout << rot_quaternions[i] << ":\n" << rot_matrices[i] << "\n\n";
		}

		std::vector<quaternion_type> rot_quaternions;
		std::vector<matrix_type> rot_matrices;
	};
#pragma endregion

	// ----------- TESTS SELECTION -----------
	using AllTests = std::tuple
	<
		//EmuNormalMatrixTest,
		//EmuFastMatrixTest,
		//DirectXSimdTest
		//ScalarQuaternionTest,
		//FastQuaternionTest,
		ScalarTan,
		SIMDTan128,
		SIMDTan256,
		SIMDTan512
		//FastMatFromScalarQuaternionTest,
		//FastMatFromFastQuaternionTest,
		//ScalarMatFromScalarQuaternionTest
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
				std::cout << harness.template ExecuteAndOutputAsString<Test::PASS_LOOP_NUM>(Test::NUM_LOOPS, test, test.WRITE_ALL_TIMES_TO_STREAM) << "\n\n";
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

				if(get_yes_or_no("\n\nExecute additinal OnAllTestsOver branch?"))
				{
					OnAllTestsOver<0>(tests);
				}
			}

			shouldRepeat = get_yes_or_no("\n\nRepeat all tests?");
		} while (shouldRepeat);
	}
#pragma endregion
}

#endif
