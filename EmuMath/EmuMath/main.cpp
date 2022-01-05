#include "EmuCore/Functors/Analytics.h"
#include "EmuMath/Noise.h"
#include "EmuMath/Random.h"

#include "EmuMath/Colour.h"

#include "Tests.hpp"

#include "EmuMath/FastNoise.h"

#include "EmuThreads/ThreadPool.h"
#include "EmuThreads/Functors/prioritised_work_allocator.h"
#include "EmuThreads/ThreadSafeHelpers.h"
#include "EmuThreads/ParallelFor.h"

#include <chrono>
#include <thread>

#include "EmuCore/CommonTypes/Timer.h"
#include "EmuCore/CommonTypes/Stopwatch.h"

#include "EmuMath/NewVector.h"

#include "EmuCore/TMPHelpers/TypeObfuscation.h"
#include "EmuCore/TMPHelpers/VariadicHelpers.h"

using namespace EmuCore::TestingHelpers;

template<typename T_>
using simple_bitset = std::bitset<sizeof(T_) * CHAR_BIT>;

template<typename T_, std::size_t Size_>
inline std::ostream& operator<<(std::ostream& stream_, const std::array<T_, Size_>& arr_)
{
	std::ostringstream str;
	str << "{ ";
	str << arr_[0];
	for (std::size_t i = 1; i < Size_; ++i)
	{
		str << ", " << arr_[i];
	}
	str << " }";
	stream_ << str.str();
	return stream_;
}

template<typename T_>
void _any_type_test(T_&& t_)
{
}

void some_test(int& yo_)
{
	std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(rand() % 1000));
	EmuThreads::stream_append_all_in_one(std::cout, ++yo_, " : ", &yo_, "\n");
}

struct IncrementingFunc
{
	constexpr IncrementingFunc() : _val(0)
	{
	}

	[[nodiscard]] constexpr inline std::int32_t operator()()
	{
		return _val++;
	}
	template<typename T_>
	[[nodiscard]] constexpr inline std::int32_t operator()(T_&& dummy_)
	{
		return operator()();
	}

	std::int32_t _val;
};

template<typename T_, int Max_ = std::numeric_limits<int>::max()>
struct SettyBoi
{
	SettyBoi() : SettyBoi(static_cast<unsigned int>(time(0)))
	{
	}
	SettyBoi(unsigned int seed_)
	{
		srand(seed_);
	}

	T_ operator()() const
	{
		return T_(rand() % Max_);
	}
	T_ operator()(const std::size_t x_, const std::size_t y_) const
	{
		return T_(rand() % (x_ + y_ + 1));
	}
};

struct FunctorThisTime
{
	inline void operator()() const
	{
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(3000ms);
	}
};

bool boolfunc(bool bool_)
{
	return bool(bool_);
}

template<std::size_t X_, std::size_t Y_, typename Type_, bool ColumnMajor_>
void TestFunc(const EmuMath::Matrix<X_, Y_, Type_, ColumnMajor_>& matrix_)
{
	std::cout << matrix_ << "\n";
}
template<std::size_t X_, std::size_t Y_, typename Type_, bool ColumnMajor_>
void TestFunc(EmuMath::Matrix<X_, Y_, Type_, ColumnMajor_>&& matrix_)
{
	TestFunc(std::forward<EmuMath::Matrix<X_, Y_, Type_, ColumnMajor_>>(matrix_));
}
template<std::size_t FirstX_, std::size_t FirstY_, typename FirstType_, bool FirstColumnMajor_, std::size_t...X_, std::size_t...Y_, typename...Types_, bool...ColumnMajors_>
void TestFunc(const EmuMath::Matrix<FirstX_, FirstY_, FirstType_, FirstColumnMajor_>& first_, const EmuMath::Matrix<X_, Y_, Types_, ColumnMajors_>&...matrices_)
{
	TestFunc(first_);
	TestFunc(matrices_...);
}

void _up(int val_)
{
	std::cout << val_ << "\n";
}
void _down(int val_)
{
	std::cout << -val_ << "\n";
}
float _upf(int val_)
{
	_up(val_);
	return static_cast<float>(val_);
}

struct SafeOutputter
{
	SafeOutputter() : mutex_(), count_(0), total(0.0)
	{
	}
	SafeOutputter(SafeOutputter&&) noexcept : SafeOutputter()
	{
	}
	SafeOutputter(const SafeOutputter&) : SafeOutputter()
	{
	}

	inline void _action(std::size_t x_, std::size_t y_)
	{
		for (std::size_t i = 0; i < 255; ++i)
		{
			srand(static_cast<unsigned int>(i));
			std::size_t val_ = (x_ << ((rand() % 32) + (rand() % 33)));
			val_ <<= (y_ % 4);
			x_ *= 3;
			x_ |= std::size_t(-1);
			y_ &= ~x_;
			x_ -= y_ * y_;
			total += x_ % 64;
		}
	}

	inline void operator()(std::size_t index_)
	{
		using namespace std::chrono_literals;
		std::lock_guard lock_(mutex_);
		_action(index_, 0);
		++count_;
	}
	inline void operator()(std::size_t x_, std::size_t y_)
	{
		using namespace std::chrono_literals;
		std::lock_guard lock_(mutex_);
		_action(x_, y_);
		++count_;
	}
	inline void operator()(std::tuple<std::size_t, std::size_t> xy_)
	{
		operator()(std::get<0>(xy_), std::get<1>(xy_));
	}

	std::mutex mutex_;
	std::size_t count_;
	double total;
};

struct SomeStructForTestingEdges
{
	template<typename Fov_, typename Near_, typename AspectRatio_>
	constexpr SomeStructForTestingEdges(const Fov_& in_fov_angle_y_, const Near_& in_near_, const AspectRatio_& in_aspect_ratio_) :
		left_(0.0f), right_(0.0f), bottom_(0.0f), top_(0.0f)
	{
		EmuMath::Helpers::matrix_perspective_frustum_edges<false>(in_fov_angle_y_, in_near_, in_aspect_ratio_, left_, right_, bottom_, top_);
	}

	float left_;
	float right_;
	float bottom_;
	float top_;
};

template<class NoiseTable_>
inline void WriteNoiseTableToPPM(const NoiseTable_& noise_table_, const std::string& out_name_ = "test_noise")
{
	using FP_ = typename NoiseTable_::value_type;
	constexpr std::size_t num_dimensions = NoiseTable_::num_dimensions;
	EmuMath::Vector3<FP_> white_(255.0f, 255.0f, 255.0f);

	if constexpr (num_dimensions == 3)
	{
		EmuMath::Vector3<std::size_t> resolution_ = noise_table_.size();
		for (std::size_t z = 0; z < resolution_.z; ++z)
		{
			std::cout << "\nOutputting image layer #" << z << "...\n";

			std::ostringstream name_;
			name_ << "./" << out_name_ << "_" << z << ".ppm";
			std::ofstream out_ppm_(name_.str(), std::ios_base::out | std::ios_base::binary);
			out_ppm_ << "P6" << std::endl << resolution_.x << ' ' << resolution_.y << std::endl << "255" << std::endl;

			for (std::size_t y = 0; y < resolution_.y; ++y)
			{
				for (std::size_t x = 0; x < resolution_.x; ++x)
				{
					// Clamp is merely to cancel out fp-rounding errors
					EmuMath::Vector<3, std::uint8_t> colour_byte_(white_.Multiply(noise_table_.at(x, y, z)).Clamp(0.0f, 255.0f));
					out_ppm_ << (char)colour_byte_.x << (char)colour_byte_.y << (char)colour_byte_.z;
				}
			}
			out_ppm_.close();
		}
		std::cout << "Finished outputting all 3D noise layers.\n";
	}
	else if constexpr (num_dimensions == 2)
	{
		std::cout << "\nOutputting image...\n";

		std::ostringstream name_;
		name_ << "./2d_test_noise_.ppm";
		std::ofstream out_ppm_(name_.str(), std::ios_base::out | std::ios_base::binary);
		out_ppm_ << "P6" << std::endl << noise_table_.size<0>() << ' ' << noise_table_.size<1>() << std::endl << "255" << std::endl;

		for (std::size_t y = 0, end_y = noise_table_.size<1>(); y < end_y; ++y)
		{
			for (std::size_t x = 0, end_x = noise_table_.size<0>(); x < end_x; ++x)
			{
				// Clamp is merely to cancel out fp-rounding errors
				EmuMath::Vector<3, std::uint8_t> colour_byte_(white_.Multiply(noise_table_.at(x, y)).Clamp(0.0f, 255.0f));
				out_ppm_ << (char)colour_byte_.x << (char)colour_byte_.y << (char)colour_byte_.z;
			}
		}
		out_ppm_.close();
		std::cout << "Finished outputting 2D noise layer.\n";
	}
}

template<class NoiseTable_, class GradientChannel_>
inline void WriteNoiseTableToPPM
(
	const std::vector<NoiseTable_>& noise_table_vector_,
	const EmuMath::Gradient<GradientChannel_>& gradient_,
	const std::string& out_name_ = "test_noise"
)
{
	constexpr std::size_t num_dimensions = NoiseTable_::num_dimensions;
	if (noise_table_vector_.size() != 0)
	{
		if constexpr (num_dimensions == 3)
		{
			const auto& noise_table_ = noise_table_vector_[0];
			EmuMath::Vector3<std::size_t> resolution_ = noise_table_.size();
			for (std::size_t z = 0; z < resolution_.z; ++z)
			{
				std::cout << "\nOutputting image layer #" << z << "...\n";

				std::ostringstream name_;
				name_ << "./" << out_name_ << "_" << z << ".ppm";
				std::ofstream out_ppm_(name_.str(), std::ios_base::out | std::ios_base::binary);
				out_ppm_ << "P6" << std::endl << resolution_.x << ' ' << resolution_.y << std::endl << "255" << std::endl;

				for (std::size_t y = 0; y < resolution_.y; ++y)
				{
					for (std::size_t x = 0; x < resolution_.x; ++x)
					{
						EmuMath::ColourRGB<std::uint8_t> colour_byte_ = gradient_.GetColour<std::uint8_t>(noise_table_.at(x, y, z));
						out_ppm_ << (char)colour_byte_.R() << (char)colour_byte_.G() << (char)colour_byte_.B();
					}
				}
				out_ppm_.close();
			}
			std::cout << "Finished outputting all 3D noise layers.\n";
		}
		else if constexpr (num_dimensions == 2)
		{
			const auto& noise_table_ = noise_table_vector_[0];
			EmuMath::Vector2<std::size_t> resolution_ = noise_table_.size();
			std::cout << "\nOutputting 2D noise image layer...\n";

			std::ostringstream name_;
			name_ << "./" << out_name_ << ".ppm";
			std::ofstream out_ppm_(name_.str(), std::ios_base::out | std::ios_base::binary);
			out_ppm_ << "P6" << std::endl << resolution_.x << ' ' << resolution_.y << std::endl << "255" << std::endl;

			for (std::size_t y = 0; y < resolution_.y; ++y)
			{
				for (std::size_t x = 0; x < resolution_.x; ++x)
				{
					EmuMath::ColourRGB<std::uint8_t> colour_byte_ = gradient_.GetColour<std::uint8_t>(noise_table_.at(x, y));
					out_ppm_ << (char)colour_byte_.R() << (char)colour_byte_.G() << (char)colour_byte_.B();
				}
			}
			out_ppm_.close();
			std::cout << "Finished outputting all 2D noise.\n";
		}
		else
		{
			EmuMath::Vector2<std::size_t> resolution_ = { noise_table_vector_[0].size<0>(), noise_table_vector_.size() };
			std::cout << "\nOutputting 1D noise image layer from full vector...\n";

			std::ostringstream name_;
			name_ << "./" << out_name_ << ".ppm";
			std::ofstream out_ppm_(name_.str(), std::ios_base::out | std::ios_base::binary);
			out_ppm_ << "P6" << std::endl << resolution_.x << ' ' << resolution_.y << std::endl << "255" << std::endl;

			for (std::size_t y = 0; y < resolution_.y; ++y)
			{
				auto& noise_table_ = noise_table_vector_[y];
				for (std::size_t x = 0; x < resolution_.x; ++x)
				{
					EmuMath::ColourRGB<std::uint8_t> colour_byte_ = gradient_.GetColour<std::uint8_t>(noise_table_.at(x));
					out_ppm_ << (char)colour_byte_.R() << (char)colour_byte_.G() << (char)colour_byte_.B();
				}
			}
			out_ppm_.close();
			std::cout << "Finished outputting all 1D noise.\n";
		}
	}
}



template<std::size_t...IndexArgs_, std::size_t OutSize_, typename OutT_, class...Args_>
[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> _some_new_vec_func_test_helper(const EmuMath::NewVector<OutSize_, OutT_>& starting_out_, Args_&&...args_)
{
	EmuMath::NewVector<OutSize_, OutT_> out_(starting_out_);
	EmuMath::Helpers::new_vector_negate_range_no_copy<IndexArgs_...>(out_, std::forward<Args_>(args_)...);
	return out_;
}
template<std::size_t OutSize_, typename OutT_, class...Args_>
[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> _some_new_vec_func_test_helper(const EmuMath::NewVector<OutSize_, OutT_>& starting_out_, Args_&&...args_)
{
	EmuMath::NewVector<OutSize_, OutT_> out_(starting_out_);
	EmuMath::Helpers::new_vector_negate_range_no_copy<2, 3>(out_, std::forward<Args_>(args_)...);
	return out_;
}

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	EmuCore::Timer<std::milli> timer_;

	EmuMath::Vector<5, float> aaaaa;
	EmuMath::Matrix<1, 27, int> bbbbb;

	constexpr EmuMath::NewVector<4, float> newvector_a_(1, 2, 3, 4);
	constexpr bool hoigjheor = EmuMath::NewVector<4, float>().valid_template_construction_args<int, int, int, int>();
	constexpr auto val_0_ = newvector_a_.at<0>();
	constexpr auto val_1_ = newvector_a_.at<1>();
	constexpr auto val_2_ = newvector_a_.at<2>();
	constexpr auto val_3_ = newvector_a_.at<3>();
	EmuMath::NewVector<4, const float&> newvector_b_(val_0_, val_1_, val_2_, val_3_);
	EmuMath::NewVector<4, EmuMath::vector_internal_ref<const float>> newvector_c_(newvector_b_);

	constexpr auto ct_theoretical_0_ = EmuMath::Helpers::new_vector_get_theoretical<0>(newvector_a_);
	constexpr auto ct_theoretical_1_ = EmuMath::Helpers::new_vector_get_theoretical<1>(newvector_a_);
	constexpr auto ct_theoretical_2_ = EmuMath::Helpers::new_vector_get_theoretical<2>(newvector_a_);
	constexpr auto ct_theoretical_3_ = EmuMath::Helpers::new_vector_get_theoretical<3>(newvector_a_);
	constexpr auto ct_theoretical_4_ = EmuMath::Helpers::new_vector_get_theoretical<4>(newvector_a_);

	auto& rt_theoretical_0_ = EmuMath::Helpers::new_vector_get_theoretical<0>(newvector_b_);
	auto& rt_theoretical_1_ = EmuMath::Helpers::new_vector_get_theoretical<1>(newvector_b_);
	auto& rt_theoretical_2_ = EmuMath::Helpers::new_vector_get_theoretical<2>(newvector_b_);
	auto& rt_theoretical_3_ = EmuMath::Helpers::new_vector_get_theoretical<3>(newvector_b_);
	auto  rt_theoretical_4_ = EmuMath::Helpers::new_vector_get_theoretical<4>(newvector_b_);
	
	std::cout << newvector_b_ << "\n";
	std::cout << newvector_c_ << "\n";
	std::cout << EmuMath::NewVector<4, const float&>(newvector_c_) << "\n";
	std::cout << EmuMath::NewVector<4, const float&>(const_cast<const decltype(newvector_c_)&>(newvector_c_)) << "\n";
	//std::cout << EmuMath::NewVector<4, const float&>(std::move(newvector_c_)) << "\n";

	float new_num_ = 45;
	int blombo = 2;
	newvector_b_.Set<0>(new_num_);
	std::cout << newvector_b_ << "\n";
	newvector_b_.Set<2>(new_num_);
	newvector_b_.Set<3>(newvector_a_.at<2>());
	new_num_ = 12;
	std::cout << newvector_b_ << "\n";

	std::cout << "---\n";
	//EmuMath::Helpers::new_vector_set(newvector_c_, newvector_b_);
	newvector_c_ = decltype(newvector_c_)(newvector_b_);
	std::cout << newvector_a_ << " | " << newvector_b_ << " | " << newvector_c_ << "\n";
	//EmuMath::Helpers::new_vector_set(newvector_c_, newvector_a_);
	newvector_c_.Set(newvector_a_);
	std::cout << newvector_a_ << " | " << newvector_b_ << " | " << newvector_c_ << "\n";
	//EmuMath::Helpers::new_vector_set(newvector_b_, newvector_a_);
	newvector_b_.Set(newvector_a_);
	std::cout << newvector_a_ << " | " << newvector_b_ << " | " << newvector_c_ << "\n";
	EmuMath::NewVector<5, float> some_new_vector_(1.0f, 10.0f, 100.0f, 1000.0f, 6.0f);

	newvector_b_.Set(some_new_vector_);
	std::cout << newvector_a_ << " | " << newvector_b_ << " | " << newvector_c_ << " | " << some_new_vector_ << "\n";
	some_new_vector_.at<2>() = 3.0f;
	std::cout << newvector_a_ << " | " << newvector_b_ << " | " << newvector_c_ << " | " << some_new_vector_ << "\n";
	some_new_vector_.Set(newvector_a_);
	//EmuMath::Helpers::new_vector_set(some_new_vector_, newvector_a_);
	std::cout << newvector_a_ << " | " << newvector_b_ << " | " << newvector_c_ << " | " << some_new_vector_ << "\n";
	some_new_vector_.at<1>() = 1.234f;
	std::cout << newvector_a_ << " | " << newvector_b_ << " | " << newvector_c_ << " | " << some_new_vector_ << "\n";
	//EmuMath::Helpers::new_vector_set(some_new_vector_, std::move(newvector_b_));
	//some_new_vector_.Set(std::move(newvector_b_));
	newvector_b_ = decltype(newvector_b_)(some_new_vector_);
	std::cout << newvector_a_ << " | " << newvector_b_ << " | " << newvector_c_ << " | " << some_new_vector_ << "\n";
	new_num_ = 33.5f;
	//EmuMath::Helpers::new_vector_set_all(newvector_b_, new_num_);
	newvector_b_.SetAll(new_num_);
	std::cout << newvector_a_ << " | " << newvector_b_ << " | " << newvector_c_ << " | " << some_new_vector_ << "\n";
	//EmuMath::Helpers::new_vector_set_all<1, 3>(some_new_vector_, new_num_);
	some_new_vector_.SetAll(new_num_);
	std::cout << newvector_a_ << " | " << newvector_b_ << " | " << newvector_c_ << " | " << some_new_vector_ << "\n";
	new_num_ = 1337.0f;
	std::cout << newvector_a_ << " | " << newvector_b_ << " | " << newvector_c_ << " | " << some_new_vector_ << "\n";

	std::cout << "---\n";
	std::array<float, 4> some_random_arr_ = std::array<float, 4>();
	std::cout << "Arr: " << some_random_arr_ << "\n";
	memcpy(some_random_arr_.data(), EmuMath::Helpers::new_vector_data(some_new_vector_), sizeof(float) * 4);
	std::cout << "Arr: " << some_random_arr_ << "\n";
	memcpy(EmuMath::Helpers::new_vector_data(some_new_vector_) + 2, some_random_arr_.data(), sizeof(float) * 3);
	std::cout << newvector_a_ << " | " << newvector_b_ << " | " << newvector_c_ << " | " << some_new_vector_ << "\n";

	std::cout << "---\n";
	decltype(newvector_b_) c_alt_rep_ = newvector_c_;
	EmuMath::NewVector<2, const EmuMath::NewVector<4, const float&>> vector_of_ref_vectors_(newvector_b_, newvector_c_.AsAlternativeRep());
	EmuMath::NewVector<2, const EmuMath::NewVector<4, const float&>&> ref_vector_of_ref_vectors_(newvector_b_, c_alt_rep_);
	std::cout << "Vector of refs: " << vector_of_ref_vectors_ << "\nRef vector of refs: " << ref_vector_of_ref_vectors_ << "\n|\n";
	float bloobledy_ = 13.37f;
	newvector_b_.Set<3>(bloobledy_);
	float gongo_ = -42.0f;
	c_alt_rep_.Set<2>(gongo_);
	std::cout << "Vector of refs: " << vector_of_ref_vectors_ << "\nRef vector of refs: " << ref_vector_of_ref_vectors_ << "\n|\n";
	ref_vector_of_ref_vectors_.SetAll(EmuMath::NewVector<4, const float&>(newvector_c_));
	std::cout << "Vector of refs: " << vector_of_ref_vectors_ << "\nRef vector of refs: " << ref_vector_of_ref_vectors_ << "\n|\n";
	ref_vector_of_ref_vectors_.Set<1>(newvector_b_);
	std::cout << "Vector of refs: " << vector_of_ref_vectors_ << "\nRef vector of refs: " << ref_vector_of_ref_vectors_ << "\n|\n";

	std::cout << "---\n";
	EmuMath::NewVector<1, EmuMath::NewVector<4, float>> new_mat_1x4f_;
	EmuMath::NewVector<4, EmuMath::NewVector<1, float>> new_mat_4x1f_;
	EmuMath::NewVector<4, EmuMath::NewVector<4, float>> new_mat_4x4f_;
	std::cout << "Mat<1, 4>: " << new_mat_1x4f_ << "\nMat<4, 1>: " << new_mat_4x1f_ << "\nMat<4, 4>: " << new_mat_4x4f_ << "\n|\n";
	new_mat_1x4f_ = decltype(new_mat_1x4f_)(decltype(new_mat_1x4f_)::value_type(1.0f, 2.0f, 3.0f, 4.0f));
	std::cout << "Mat<1, 4>: " << new_mat_1x4f_ << "\nMat<4, 1>: " << new_mat_4x1f_ << "\nMat<4, 4>: " << new_mat_4x4f_ << "\n|\n";
	new_mat_4x1f_ = decltype(new_mat_4x1f_)(5.0f, 6.0f, 7.0f, 8.0f);
	std::cout << "Mat<1, 4>: " << new_mat_1x4f_ << "\nMat<4, 1>: " << new_mat_4x1f_ << "\nMat<4, 4>: " << new_mat_4x4f_ << "\n|\n";
	new_mat_4x4f_ = decltype(new_mat_4x4f_)
	(
		decltype(new_mat_4x4f_)::value_type(1, 2, 3, 4),
		decltype(new_mat_4x4f_)::value_type(5, 6, 7, 8),
		decltype(new_mat_4x4f_)::value_type(9, 10, 11, 12),
		decltype(new_mat_4x4f_)::value_type(13, 14, 15, 16)
	);
	std::cout << "Mat<1, 4>: " << new_mat_1x4f_ << "\nMat<4, 1>: " << new_mat_4x1f_ << "\nMat<4, 4>: " << new_mat_4x4f_ << "\n|\n";
	using new_vec_4i32 = EmuMath::NewVector<4, std::int32_t>;
	new_mat_4x4f_ = decltype(new_mat_4x4f_)
	(
		new_vec_4i32(17, 18, 19, 20),
		new_vec_4i32(21, 22, 23, 24),
		new_vec_4i32(25, 26, 27, 28),
		new_vec_4i32(29, 30, 31, 32)
	);
	std::cout << "Mat<1, 4>: " << new_mat_1x4f_ << "\nMat<4, 1>: " << new_mat_4x1f_ << "\nMat<4, 4>: " << new_mat_4x4f_ << "\n|\n";
	new_mat_1x4f_ = decltype(new_mat_1x4f_)(EmuMath::NewVector<4, float>(11, 22, 33, 44));
	std::cout << "Mat<1, 4>: " << new_mat_1x4f_ << "\nMat<4, 1>: " << new_mat_4x1f_ << "\nMat<4, 4>: " << new_mat_4x4f_ << "\n|\n";
	new_mat_4x1f_ = decltype(new_mat_4x1f_)
	(
		EmuMath::NewVector<1, float>(55), EmuMath::NewVector<1, float>(66), EmuMath::NewVector<1, float>(77), EmuMath::NewVector<1, float>(88)
	);
	std::cout << "Mat<1, 4>: " << new_mat_1x4f_ << "\nMat<4, 1>: " << new_mat_4x1f_ << "\nMat<4, 4>: " << new_mat_4x4f_ << "\n|\n";

	EmuMath::NewVector<4, float> reeeeeeeeeeeeeeeee(1, 2, 3, 4);
	EmuMath::NewVector<4, const float&> ree_ref_(const_cast<const decltype(reeeeeeeeeeeeeeeee)&>(reeeeeeeeeeeeeeeee));

	std::cout << "---\n";
	// Some tests to make sure TryGet works nicely
	float some_value_to_ref_ = 2.0f;
	EmuCore::DeferrableReferenceWrapper<float> test_refwrapper_;
	test_refwrapper_.Set(some_value_to_ref_);
	float* p_out_;
	if (test_refwrapper_.TryGet(&p_out_))
	{
		std::cout << *(p_out_) << "\n";
	}
	some_value_to_ref_ = 5.0f;
	const float* p_const_out_;
	if (test_refwrapper_.TryGet(&p_const_out_))
	{
		std::cout << *p_const_out_ << "\n";
	}

	test_refwrapper_ = decltype(test_refwrapper_)();
	if (test_refwrapper_.TryGet<true>(&p_out_))
	{
		std::cout << "This shouldn't be printed: " << *p_out_ << "\n";
	}
	else
	{
		std::cout << "No reference held in DeferrableReferenceWrapper instance when TryGet was used.\n";
	}

	std::cout << "---\n";
	EmuMath::NewVector<5, const float> some_other_ref_vector_target_(1, 2, 3, 4, 5);
	EmuMath::NewVector<4, const float&> some_other_ref_vector_ = decltype(some_other_ref_vector_)(some_other_ref_vector_target_);
	std::cout << some_other_ref_vector_ << "\n";

	EmuMath::NewVector<4, float> bloobongo_(1, 2, 3, 4);
	EmuCore::DeferrableReferenceWrapper<float> ref_wrapper_;
	if (bloobongo_(0, ref_wrapper_))
	{
		ref_wrapper_.get() = 1337.0f;
		std::cout << bloobongo_ << "[0]: " << ref_wrapper_ << "\n";
	}
	if (bloobongo_(1, ref_wrapper_))
	{
		std::cout << bloobongo_ << "[1]: " << ref_wrapper_ << "\n";
	}
	if (bloobongo_(2, ref_wrapper_))
	{
		std::cout << bloobongo_ << "[2]: " << ref_wrapper_ << "\n";
	}
	if (bloobongo_(3, ref_wrapper_))
	{
		std::cout << bloobongo_ << "[3]: " << ref_wrapper_ << "\n";
	}
	if (bloobongo_(4, ref_wrapper_))
	{
		std::cout << bloobongo_ << "[4]: " << ref_wrapper_ << "\n";
	}
	else
	{
		std::cout << bloobongo_ << "[4]: Not found\n";
	}

	float* p_out_float_;
	if (bloobongo_(0, &p_out_float_))
	{
		std::cout << bloobongo_ << "[0]: " << *p_out_float_ << "\n";
	}
	if (bloobongo_(1, &p_out_float_))
	{
		*p_out_float_ = -5.0f;
		std::cout << bloobongo_ << "[1]: " << *p_out_float_ << "\n";
	}
	if (bloobongo_(2, &p_out_float_))
	{
		std::cout << bloobongo_ << "[2]: " << *p_out_float_ << "\n";
	}
	if (bloobongo_(3, &p_out_float_))
	{
		std::cout << bloobongo_ << "[3]: " << *p_out_float_ << "\n";
	}
	if (bloobongo_(4, &p_out_float_))
	{
		std::cout << bloobongo_ << "[4]: " << *p_out_float_ << "\n";
	}
	else
	{
		std::cout << bloobongo_ << "[4]: Not found\n";
	}

	const float* p_out_const_float_;
	if (bloobongo_(0, &p_out_const_float_))
	{
		std::cout << bloobongo_ << "[0]: " << *p_out_const_float_ << "\n";
	}
	if (bloobongo_(1, &p_out_const_float_))
	{
		std::cout << bloobongo_ << "[1]: " << *p_out_const_float_ << "\n";
	}
	if (bloobongo_(2, &p_out_const_float_))
	{
		std::cout << bloobongo_ << "[2]: " << *p_out_const_float_ << "\n";
	}
	if (bloobongo_(3, &p_out_const_float_))
	{
		std::cout << bloobongo_ << "[3]: " << *p_out_const_float_ << "\n";
	}
	if (bloobongo_(4, &p_out_const_float_))
	{
		std::cout << bloobongo_ << "[4]: " << *p_out_const_float_ << "\n";
	}
	else
	{
		std::cout << bloobongo_ << "[4]: Not found\n";
	}

	std::cout << "---\n";
	EmuMath::NewVector<3, float> some_newvec3f_(1.0f, 1.25f, 1.5f);
	std::cout << some_newvec3f_ << "\n";
	std::cout << "Memory locations:\n";
	std::cout << "[0]: " << some_newvec3f_.data<0>() << "\n";
	std::cout << "[1]: " << some_newvec3f_.data<1>() << "\n";
	std::cout << "[2]: " << some_newvec3f_.data<2>() << "\n";
	EmuMath::NewVector<4, float> some_newvec4f_(10.0f, 20.0f, 30.0f, 40.0f);
	std::cout << some_newvec4f_ << "\n";
	some_newvec4f_.Set(some_newvec3f_);
	std::cout << some_newvec4f_ << "\n";
	some_newvec4f_ = decltype(some_newvec4f_)(10.0f, 20.0f, 30.0f, 40.0f);
	std::cout << some_newvec4f_ << "\n";
	some_newvec4f_.SetContainedOnly(some_newvec3f_);
	std::cout << some_newvec4f_ << "\n";
	std::cout << EmuMath::NewVector<20, float>(0.5) << "\n";
	//EmuMath::Helpers::new_vector_copy(some_newvec4f_, 15.0f);
	some_newvec4f_.Copy(15.0f);
	std::cout << some_newvec4f_ << "\n";
	//EmuMath::Helpers::new_vector_copy(some_newvec4f_, some_newvec3f_);
	some_newvec4f_.Copy(some_newvec3f_);
	some_newvec4f_.at<3>() = 25.0f;
	std::cout << some_newvec4f_ << "\n";
	EmuMath::NewVector<2, float> some_newvec2f_(-77.7f, +77.7f);
	//EmuMath::Helpers::new_vector_copy<1, 3>(some_newvec4f_, some_newvec2f_);
	some_newvec4f_.Copy<1, 3>(some_newvec2f_);
	std::cout << some_newvec4f_ << "\n";
	//EmuMath::Helpers::new_vector_copy<false>(some_newvec4f_, some_newvec3f_);
	some_newvec4f_.Copy<false>(some_newvec3f_);
	std::cout << some_newvec4f_ << "\n";
	//EmuMath::Helpers::new_vector_copy<true>(some_newvec4f_, some_newvec2f_);
	some_newvec4f_.Copy<true>(some_newvec2f_);
	std::cout << some_newvec4f_ << "\n";
	some_newvec4f_ = decltype(some_newvec4f_)(5, 10, 15, 20);
	std::cout << some_newvec4f_ << "\n";
	//EmuMath::Helpers::new_vector_copy_from_start<1>(some_newvec4f_, some_newvec2f_);
	some_newvec4f_.CopyFromStart<1>(some_newvec2f_);
	std::cout << some_newvec4f_ << "\n";
	some_newvec4f_ = decltype(some_newvec4f_)(5, 10, 15, 20);
	std::cout << some_newvec4f_ << "\n";
	//EmuMath::Helpers::new_vector_copy_from_start_contained_only<1>(some_newvec4f_, some_newvec2f_);
	some_newvec4f_.CopyFromStartContainedOnly<1>(some_newvec2f_);
	std::cout << some_newvec4f_ << "\n";

	std::cout << "---\n";
	EmuMath::NewVector<4, EmuMath::NewVector<4, float>> some_newmat4x4f_a_
	(
		EmuMath::NewVector<4, float>(1, 2, 3, 4),
		EmuMath::NewVector<4, float>(5, 6, 7, 8),
		EmuMath::NewVector<4, float>(9, 10, 11, 12),
		EmuMath::NewVector<4, float>(13, 14, 15, 16)
	);
	EmuMath::NewVector<4, EmuMath::NewVector<4, float>> some_newmat4x4f_b_
	(
		EmuMath::NewVector<4, float>(17, 18, 19, 20),
		EmuMath::NewVector<4, float>(21, 22, 23, 24),
		EmuMath::NewVector<4, float>(25, 26, 27, 28),
		EmuMath::NewVector<4, float>(29, 30, 31, 32)
	);
	std::cout << some_newmat4x4f_a_ << "\n";
	std::cout << some_newmat4x4f_b_ << "\n";
	some_newmat4x4f_a_.Copy(some_newmat4x4f_b_);
	std::cout << some_newmat4x4f_a_ << "\n";
	std::cout << some_newmat4x4f_b_ << "\n";
	some_newmat4x4f_a_.Copy(EmuMath::NewVector<4, float>(33, 34, 35, 36));
	std::cout << some_newmat4x4f_a_ << "\n";
	std::cout << some_newmat4x4f_b_ << "\n";
	some_newmat4x4f_a_.Copy(some_newvec4f_);
	std::cout << some_newmat4x4f_a_ << "\n";
	std::cout << some_newmat4x4f_b_ << "\n";
	//some_newmat4x4f_b_.Copy
	//(
	//	EmuMath::NewVector<4, EmuMath::NewVector<4, long double>>
	//	(
	//		EmuMath::NewVector<4, long double>(6, 12, 18, 24),
	//		EmuMath::NewVector<4, long double>(-6, -12, -18, -24),
	//		EmuMath::NewVector<4, long double>(66, 112, 118, 224),
	//		EmuMath::NewVector<4, long double>(-66, -112, -118, -224)
	//	)
	//);
	some_newmat4x4f_b_ = EmuMath::NewVector<4, EmuMath::NewVector<4, long double>>
	(
		EmuMath::NewVector<4, long double>(6, 12, 18, 24),
		EmuMath::NewVector<4, long double>(-6, -12, -18, -24),
		EmuMath::NewVector<4, long double>(66, 112, 118, 224),
		EmuMath::NewVector<4, long double>(-66, -112, -118, -224)
	);
	std::cout << some_newmat4x4f_a_ << "\n";
	std::cout << some_newmat4x4f_b_ << "\n";
	some_newmat4x4f_b_.Copy(2);
	std::cout << some_newmat4x4f_a_ << "\n";
	std::cout << some_newmat4x4f_b_ << "\n";

	std::cout << "---\n";
	constexpr EmuMath::NewVector<4, float> another_newvec4f_(1, 2, 3, 4);
	//constexpr auto shuffled_newvec4f_ = EmuMath::Helpers::new_vector_shuffle<3, 2, 1, 0>(another_newvec4f_);
	constexpr auto shuffled_newvec4f_ = another_newvec4f_.Shuffle<3, 2, 1, 0>();
	//constexpr auto shuffled_newvec8d_ = EmuMath::Helpers::new_vector_shuffle<double, 0, 2, 1, 3, 1, 1, 0, 0>(another_newvec4f_);
	constexpr auto shuffled_newvec8d_ = another_newvec4f_.Shuffle<double, 0, 2, 1, 3, 1, 1, 0, 0>();

	EmuMath::NewVector<4, float> runtime_other_newvec4f_(1, 2, 3, 4);
	//auto shuffled_newvec7f_ref_ = EmuMath::Helpers::new_vector_shuffle_theoretical<float&, 0, 1, 2, 3, 2, 1, 0>(runtime_other_newvec4f_);
	auto shuffled_newvec7f_ref_ = runtime_other_newvec4f_.ShuffleTheoretical<float&, 0, 1, 2, 3, 2, 1, 0>();
	std::cout << runtime_other_newvec4f_ << "\n";
	std::cout << shuffled_newvec7f_ref_ << "\n";
	runtime_other_newvec4f_.at<0>() = 25.0f;
	shuffled_newvec7f_ref_.at<1>() = 50.0f;
	std::cout << runtime_other_newvec4f_ << "\n";
	std::cout << shuffled_newvec7f_ref_ << "\n";
	//EmuMath::NewVector<12, long double> some_newvec12ld_(EmuMath::Helpers::new_vector_shuffle_theoretical<float, 0, 1, 2, 3, 4, 5, 6, 7>(shuffled_newvec7f_ref_));
	EmuMath::NewVector<12, long double> some_newvec12ld_(shuffled_newvec7f_ref_.ShuffleTheoretical<float, 0, 1, 2, 3, 4, 5, 6, 7>());
	//std::cout << EmuMath::Helpers::new_vector_shuffle_theoretical<0, 1, 2, 3, 4, 5, 6, 7>(shuffled_newvec7f_ref_) << "\n";
	std::cout << shuffled_newvec7f_ref_.ShuffleTheoretical<0, 1, 2, 3, 4, 5, 6, 7>() << "\n";
	std::cout << some_newvec12ld_ << "\n";

	EmuMath::NewVector<4, float> yet_another_newvec4f_ = EmuMath::NewVector<4, float>(10, 20, 30, 40);
	EmuMath::NewVector<4, float&> another_ref_ = yet_another_newvec4f_.Shuffle<float&, 3, 2, 1, 0>();

	auto some_arbitrarily_sized_newvector_ = EmuMath::Helpers::new_vector_make<const float&>(another_ref_.at<2>(), (another_ref_.at<0>()));
	std::cout << some_arbitrarily_sized_newvector_ << "\n";

	std::cout << "---\n";
	constexpr EmuMath::NewVector<12, float> new_vec_to_round_(0.1, 0.2, -0.3, 0.4, 0.5, 0.6, -0.7, 0.8, 0.9, 1.0, -2.4, 2.5);
	constexpr auto new_vec_floored_ = EmuMath::Helpers::new_vector_floor_constexpr(new_vec_to_round_);
	constexpr auto new_vec_ceiled_ = EmuMath::Helpers::new_vector_ceil_constexpr(new_vec_to_round_);
	constexpr auto new_vec_trunced_ = EmuMath::Helpers::new_vector_trunc_constexpr(new_vec_to_round_);
	constexpr auto new_vec_abs_ = EmuMath::Helpers::new_vector_abs(new_vec_to_round_);



	std::cout << "---\n";
	constexpr auto pre_negate_vec_ = EmuMath::Helpers::new_vector_make<float>(-5.0f, 0.0f, 12.0f, -66.66f);
	constexpr auto full_negate_vec_ = EmuMath::Helpers::new_vector_negate(pre_negate_vec_);
	constexpr auto partial_negate_vec_ = EmuMath::Helpers::new_vector_negate_range<27, long double, 3, 4>(pre_negate_vec_);

	constexpr auto some_other_negation_ = EmuMath::Helpers::new_vector_mutate<4, long double>(EmuCore::do_negate<void>(), EmuMath::Helpers::new_vector_make<float>(1, -2, 3, -4));
	constexpr auto negated_negation_ = some_other_negation_.Negate();
	constexpr auto negated_negation_full_range_ = EmuMath::Helpers::new_vector_negate_range<0, 10>(some_other_negation_);
	constexpr auto negated_negation_full_range_mut_ = EmuMath::Helpers::new_vector_mutate_range<4, float, 0, 10>(EmuCore::do_negate<void>(), some_other_negation_);
	constexpr auto negated_negated_negation_full_range_mut_ = EmuMath::Helpers::new_vector_mutate_range<4, float, 0, 10, 1>(EmuCore::do_negate<void>(), negated_negation_full_range_mut_);
	constexpr auto another_negation_again_ = EmuMath::Helpers::new_vector_negate_range_no_copy<4, float, 2, 4, 0>(some_other_negation_);

	EmuCore::TMP::variadic_or_v<false, false, false, false, false, false, false>;
	EmuCore::TMP::variadic_xor_v<false, false, true, false, false, false, true>;
	EmuCore::TMP::variadic_and_v<false, false, true, false, false, false, true>;

	std::cout << "---\n";
	// NOTE: Test done this way to allow an easily readable constexpr
	constexpr auto partial_test_to_negate_ = EmuMath::Helpers::new_vector_make<float>(1, -2, -3, -4, -5, 6, -7, 8, 9, 10);
	constexpr auto partial_test_to_not_negate_ = EmuMath::Helpers::new_vector_make<float>(10, 20, 30, 40, 50, 60, 70, 80, 90, 100);
	constexpr auto partial_test_negation_result_ = _some_new_vec_func_test_helper<2, 5, 4>(partial_test_to_not_negate_, partial_test_to_negate_);

	constexpr EmuMath::NewVector<4, float> a_mess_ = EmuMath::NewVector<4, float>
	(
		EmuCore::TMP::deobfuscate(EmuCore::TMP::obfuscate(EmuMath::NewVector<6, float>(2, -17.1, 25.2, 0, 255.812L, -12.7f)))
	);
	constexpr auto a_mess_trunced_ = EmuMath::Helpers::new_vector_trunc_range_no_copy_constexpr<2, 4, 1>(a_mess_);
	constexpr auto a_mess_ceiled_ = EmuMath::Helpers::new_vector_ceil_range_no_copy_constexpr<2, 4, 1>(a_mess_);
	constexpr auto a_mess_floored_ = EmuMath::Helpers::new_vector_floor_range_no_copy_constexpr<2, 4, 1>(a_mess_);
	constexpr auto a_mess_absed_ = EmuMath::Helpers::new_vector_abs_range_no_copy<2, 4, 1>(a_mess_);

	std::is_constructible_v<EmuMath::NewVector<4, float>, EmuMath::NewVector<1, std::uint8_t>>;
	constexpr auto tru432t = EmuMath::NewVector<4, float>(  EmuMath::Helpers::new_vector_make<float>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
	constexpr auto oij =  EmuMath::NewVector<4, float>::valid_template_vector_move_construct_arg<16, EmuMath::NewVector<4, float>>();

	std::cout << "---\n";
	EmuMath::NewVector<4, float> runtime_unary_vec_test_(10, -20, 30.0L, 40.5f);
	std::cout << "BEFORE MODS: " << runtime_unary_vec_test_ << "\n";
	std::cout << "PRE-INC RESULT: " << ++runtime_unary_vec_test_ << "\n";
	std::cout << "POST-INC RESULT: " << runtime_unary_vec_test_.PostIncrement<10, float>() << "\n";
	std::cout << "AFTER FIRST MODS: " << runtime_unary_vec_test_ << "\n";
	std::cout << "POST-INC REF RESULT: " << runtime_unary_vec_test_.operator++<4, float&>(int()) << "\n";
	std::cout << "AFTER SECOND MODS: " << runtime_unary_vec_test_ << "\n";

	std::cout << "\n!BATCH 2!\n";
	std::cout << "BEFORE MODS: " << runtime_unary_vec_test_ << "\n";
	std::cout << "PRE-DEC RESULT: " << --runtime_unary_vec_test_ << "\n";
	std::cout << "POST-DEC RESULT: " << runtime_unary_vec_test_.PostDecrement<10, float>() << "\n";
	std::cout << "AFTER FIRST MODS: " << runtime_unary_vec_test_ << "\n";
	std::cout << "POST-DEC REF RESULT: " << runtime_unary_vec_test_.operator--<4, float&>(int()) << "\n";
	std::cout << "AFTER SECOND MODS: " << runtime_unary_vec_test_ << "\n";

	constexpr auto multi_test_ = EmuMath::NewVector<4, EmuMath::NewVector<4, float>>(EmuMath::NewVector<4, float>(1, 2, 3, 4));

	constexpr auto ceiled_test_a_ = EmuMath::Helpers::new_vector_make<float>(-1.1, -1, 1, 1, 1, -1.5, 1.5, 1.7, 2.7, -3.759, 4.90005f).CeilConstexpr();
	constexpr auto ceiled_test_b_ = EmuMath::Helpers::new_vector_make<float>(-1.1, -1, 1, 1, 1, -1.5, 1.5, 1.7, 2.7, -3.759, 4.90005f).CeilRangeConstexpr<5, 10>();
	constexpr auto ceiled_test_c_ = EmuMath::Helpers::new_vector_make<float>(-1.1, -1, 1, 1, 1, -1.5, 1.5, 1.7, 2.7, -3.759, 4.90005f).CeilRangeNoCopyConstexpr<5, 10, 5>();

	constexpr auto floored_test_a_ = EmuMath::Helpers::new_vector_make<float>(-1.1, -1, 1, 1, 1, -1.5, 1.5, 1.7, 2.7, -3.759, 4.90005f).FloorConstexpr();
	constexpr auto floored_test_b_ = EmuMath::Helpers::new_vector_make<float>(-1.1, -1, 1, 1, 1, -1.5, 1.5, 1.7, 2.7, -3.759, 4.90005f).FloorRangeConstexpr<5, 10>();
	constexpr auto floored_test_c_ = EmuMath::Helpers::new_vector_make<float>(-1.1, -1, 1, 1, 1, -1.5, 1.5, 1.7, 2.7, -3.759, 4.90005f).FloorRangeNoCopyConstexpr<5, 10, 5>();

	constexpr auto trunced_test_a_ = EmuMath::Helpers::new_vector_make<float>(-1.1, -1, 1, 1, 1, -1.5, 1.5, 1.7, 2.7, -3.759, 4.90005f).TruncConstexpr();
	constexpr auto trunced_test_b_ = EmuMath::Helpers::new_vector_make<float>(-1.1, -1, 1, 1, 1, -1.5, 1.5, 1.7, 2.7, -3.759, 4.90005f).TruncRangeConstexpr<5, 10>();
	constexpr auto trunced_test_c_ = EmuMath::Helpers::new_vector_make<float>(-1.1, -1, 1, 1, 1, -1.5, 1.5, 1.7, 2.7, -3.759, 4.90005f).TruncRangeNoCopyConstexpr<5, 10, 5>();

	constexpr auto trj439 = EmuMath::NewVector<4, double>(0, 1, 2, 3).Shuffle<1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1>();
	float reeeeeeeeeeeeeeeeeeeeeeeeee_ = 0.5f;
	auto yet_another_ref_vec_ = EmuMath::Helpers::new_vector_make<float&>(reeeeeeeeeeeeeeeeeeeeeeeeee_, reeeeeeeeeeeeeeeeeeeeeeeeee_);
	std::cout << yet_another_ref_vec_ << " | " << reeeeeeeeeeeeeeeeeeeeeeeeee_ << "\n";
	reeeeeeeeeeeeeeeeeeeeeeeeee_ = 5.0f;
	std::cout << yet_another_ref_vec_ << " | " << reeeeeeeeeeeeeeeeeeeeeeeeee_ << "\n";
	++yet_another_ref_vec_;
	std::cout << yet_another_ref_vec_ << " | " << reeeeeeeeeeeeeeeeeeeeeeeeee_ << "\n";
	float bobobobo_ = 13.37f;
	yet_another_ref_vec_.Set<1>(bobobobo_);
	std::cout << yet_another_ref_vec_ << " | " << reeeeeeeeeeeeeeeeeeeeeeeeee_ << "\n";
	bobobobo_ = 8008135.0f;
	std::cout << yet_another_ref_vec_ << " | " << reeeeeeeeeeeeeeeeeeeeeeeeee_ << "\n";
	reeeeeeeeeeeeeeeeeeeeeeeeee_ = 0.0f;
	std::cout << yet_another_ref_vec_ << " | " << reeeeeeeeeeeeeeeeeeeeeeeeee_ << "\n";
	yet_another_ref_vec_.at<0>() = bobobobo_;
	bobobobo_ *= yet_another_ref_vec_.at<0>() * 0.0001f;
	std::cout << yet_another_ref_vec_ << " | " << reeeeeeeeeeeeeeeeeeeeeeeeee_ << "\n";
	yet_another_ref_vec_ = EmuMath::NewVector<4, float>(10, 20, 30, 40);
	std::cout << yet_another_ref_vec_ << " | " << reeeeeeeeeeeeeeeeeeeeeeeeee_ << "\n";
	yet_another_ref_vec_.Set<0>(yet_another_ref_vec_.at<1>());

	std::cout << "--\n\n";
	constexpr auto some_multi_test_ = EmuMath::Helpers::new_vector_make<float>(15, 30, 45, 60).Lerp
	(
		char(30),
		0.5L
	);

	constexpr auto new_lerp_test_b_ = EmuMath::Helpers::new_vector_make<float>(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f).LerpRange<1, 5>
	(
		10.0f,
		EmuMath::Helpers::new_vector_make<double>(1.0f, 0.5f, 1.0f, -0.5f, 0.75f, -1.0f, 25.0f)
	);

	constexpr auto new_lerp_test_c_ = EmuMath::Helpers::new_vector_make<float>(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f).LerpRangeNoCopy<1, 5, 8>
	(
		10.0f,
		EmuMath::Helpers::new_vector_make<double>(1.0f, 0.5f, 1.0f, -0.5f, 0.75f, -1.0f, 25.0f)
	);

	EmuMath::NewVector<4, double> another_new_vec_4d_(1, 1, 1, 1);
	std::cout << another_new_vec_4d_ << "\n";
	//EmuMath::Helpers::new_vector_lerp(another_new_vec_4d_, another_new_vec_4d_, EmuMath::NewVector<4, float>(10, 20, 30, 40), 0.5);
	another_new_vec_4d_.Lerp(another_new_vec_4d_, EmuMath::NewVector<4, float>(10, 20, 30, 40), 0.5);
	std::cout << another_new_vec_4d_ << "\n";

	std::cout << "\n\n";
	//constexpr auto new_add_res_a_ = EmuMath::Helpers::new_vector_add(EmuMath::Helpers::new_vector_make<float>(1.5f, 0.0, 3.9f, -2.5f, -5.0f, 2.5f), 2.5L);
	constexpr auto new_add_res_a_ = EmuMath::Helpers::new_vector_make<float>(1.5, 0.0, 3.9, -2.5, -5, 2.5) + 2.5;
	//constexpr auto new_add_res_b_ = EmuMath::Helpers::new_vector_add_range<1, 5>(EmuMath::Helpers::new_vector_make<float>(1.5, 0.0, 3.9, -2.5, -5, 2.5), 2.5);
	constexpr auto new_add_res_b_ = EmuMath::Helpers::new_vector_make<float>(1.5, 0.0, 3.9, -2.5, -5, 2.5).AddRange<1, 5>(2.5);
	//constexpr auto new_add_res_c_ = EmuMath::Helpers::new_vector_add_range_no_copy<1, 5, 0>(EmuMath::Helpers::new_vector_make<float>(1.5, 0, 3.9, -2.5, -5, 2.5), 2.5);
	constexpr auto new_add_res_c_ = EmuMath::Helpers::new_vector_make<float>(1.5, 0.0, 3.9, -2.5, -5, 2.5).AddRangeNoCopy<1, 5, 0>(2.5);

	//constexpr auto new_sub_res_a_ = EmuMath::Helpers::new_vector_subtract(EmuMath::Helpers::new_vector_make<float>(1.5f, 0.0, 3.9f, -2.5f, -5.0f, 2.5f), 2.5L);
	constexpr auto new_sub_res_a_ = EmuMath::Helpers::new_vector_make<float>(1.5, 0.0, 3.9, -2.5, -5, 2.5) - 2.5L;
	//constexpr auto new_sub_res_b_ = EmuMath::Helpers::new_vector_subtract_range<1, 5>(EmuMath::Helpers::new_vector_make<float>(1.5, 0.0, 3.9, -2.5, -5, 2.5), 2.5);
	constexpr auto new_sub_res_b_ = EmuMath::Helpers::new_vector_make<float>(1.5, 0.0, 3.9, -2.5, -5, 2.5).SubtractRange<1, 5>(2.5);
	//constexpr auto new_sub_res_c_ = EmuMath::Helpers::new_vector_subtract_range_no_copy<1, 5, 0>(EmuMath::Helpers::new_vector_make<float>(1.5, 0, 3.9, -2.5, -5, 2.5), 2.5);
	constexpr auto new_sub_res_c_ = EmuMath::Helpers::new_vector_make<float>(1.5, 0.0, 3.9, -2.5, -5, 2.5).SubtractRangeNoCopy<1, 5, 0>(2.5);

	//constexpr auto new_mul_res_a_ = EmuMath::Helpers::new_vector_multiply(EmuMath::Helpers::new_vector_make<float>(1.5f, 0.0, 3.9f, -2.5f, -5.0f, 2.5f), 2.5L);
	constexpr auto new_mul_res_a_ = EmuMath::Helpers::new_vector_make<float>(1.5f, 0.0, 3.9f, -2.5f, -5.0f, 2.5f) * 2.5L;
	//constexpr auto new_mul_res_b_ = EmuMath::Helpers::new_vector_multiply_range<1, 5>(EmuMath::Helpers::new_vector_make<float>(1.5, 0.0, 3.9, -2.5, -5, 2.5), 2.5);
	constexpr auto new_mul_res_b_ = EmuMath::Helpers::new_vector_make<float>(1.5, 0.0, 3.9, -2.5, -5, 2.5).MultiplyRange<1, 5>(2.5);
	//constexpr auto new_mul_res_c_ = EmuMath::Helpers::new_vector_multiply_range_no_copy<1, 5, 0>(EmuMath::Helpers::new_vector_make<float>(1.5, 0, 3.9, -2.5, -5, 2.5), 2.5);
	constexpr auto new_mul_res_c_ = EmuMath::Helpers::new_vector_make<float>(1.5, 0.0, 3.9, -2.5, -5, 2.5).MultiplyRangeNoCopy<1, 5, 0>(2.5);

	//constexpr auto new_div_res_a_ = EmuMath::Helpers::new_vector_divide(EmuMath::Helpers::new_vector_make<float>(1.5f, 0.0, 3.9f, -2.5f, -5.0f, 2.5f), 2.5L);
	constexpr auto new_div_res_a_ = EmuMath::Helpers::new_vector_make<float>(1.5f, 0.0, 3.9f, -2.5f, -5.0f, 2.5f) / 2.5L;
	//constexpr auto new_div_res_b_ = EmuMath::Helpers::new_vector_divide_range<1, 5>(EmuMath::Helpers::new_vector_make<float>(1.5, 0.0, 3.9, -2.5, -5, 2.5), 2.5);
	constexpr auto new_div_res_b_ = EmuMath::Helpers::new_vector_make<float>(1.5, 0.0, 3.9, -2.5, -5, 2.5).DivideRange<1, 5>(2.5);
	//constexpr auto new_div_res_c_ = EmuMath::Helpers::new_vector_divide_range_no_copy<1, 5, 0>(EmuMath::Helpers::new_vector_make<float>(1.5, 0, 3.9, -2.5, -5, 2.5), 2.5);
	constexpr auto new_div_res_c_ = EmuMath::Helpers::new_vector_make<float>(1.5, 0.0, 3.9, -2.5, -5, 2.5).DivideRangeNoCopy<1, 5, 0>(2.5);

	//constexpr auto new_mod_res_a_ = EmuMath::Helpers::new_vector_mod(EmuMath::Helpers::new_vector_make<float>(1.5f, 0.0, 3.9f, -2.5f, -5.0f, 2.5f), 2.5L);
	constexpr auto new_mod_res_a_ = EmuMath::Helpers::new_vector_make<float>(1.5f, 0.0, 3.9f, -2.5f, -5.0f, 2.5f) % 2.5L;
	//constexpr auto new_mod_res_b_ = EmuMath::Helpers::new_vector_mod_range<1, 5>(EmuMath::Helpers::new_vector_make<float>(1.5, 0.0, 3.9, -2.5, -5, 2.5), 2.5);
	constexpr auto new_mod_res_b_ = EmuMath::Helpers::new_vector_make<float>(1.5, 0.0, 3.9, -2.5, -5, 2.5).ModRange<1, 5>(2.5);
	//constexpr auto new_mod_res_c_ = EmuMath::Helpers::new_vector_mod_range_no_copy<1, 5, 0>(EmuMath::Helpers::new_vector_make<float>(1.5, 0, 3.9, -2.5, -5, 2.5), 2.5);
	constexpr auto new_mod_res_c_ = EmuMath::Helpers::new_vector_make<float>(1.5, 0.0, 3.9, -2.5, -5, 2.5).ModRangeNoCopy<1, 5, 0>(2.5);


	constexpr auto new_bitwise_test_ = EmuMath::Helpers::new_vector_make<int>(0, 2, 4, 3, 9, 10);

	//constexpr auto new_and_res_a_ = EmuMath::Helpers::new_vector_bitwise_and(new_bitwise_test_, 3);
	constexpr auto new_and_res_a_ = new_bitwise_test_ & 3;

	//constexpr auto new_or_res_a_ = EmuMath::Helpers::new_vector_bitwise_or(new_bitwise_test_, 3);
	constexpr auto new_or_res_a_ = new_bitwise_test_ | 3;

	//constexpr auto new_xor_res_a_ = EmuMath::Helpers::new_vector_bitwise_xor(new_bitwise_test_, 3);
	constexpr auto new_xor_res_a_ = new_bitwise_test_ ^ 3;

	//constexpr auto new_lshift_res_a_ = EmuMath::Helpers::new_vector_shift_left(new_bitwise_test_, 2);
	constexpr auto new_lshift_res_a_ = new_bitwise_test_ << 2;

	//constexpr auto new_rshift_res_a_ = EmuMath::Helpers::new_vector_shift_right(new_bitwise_test_, 2);
	constexpr auto new_rshift_res_a_ = new_bitwise_test_ >> 2;

	//constexpr auto new_not_res_a_ = EmuMath::Helpers::new_vector_bitwise_not(EmuMath::Helpers::new_vector_make<std::uint16_t>(0xFFFF, 0xFFFE, 0));
	constexpr auto new_not_res_a_ = ~EmuMath::Helpers::new_vector_make<std::uint16_t>(0xFFFF, 0xFFFE, 0);

	std::cout << new_rshift_res_a_ << " --- And extra\n";

	std::cout << "---\n\n";
	EmuMath::NewVector<4, double> assign_op_test_(1, 2, 3, 4);
	std::cout << assign_op_test_ << "\n";
	assign_op_test_ += 5;
	std::cout << "+ 5: " << assign_op_test_ << "\n";
	assign_op_test_ -= 2.3f;
	std::cout << "- 2.3f: " << assign_op_test_ << "\n";
	assign_op_test_ *= 10ULL;
	std::cout << "* 10ULL: " << assign_op_test_ << "\n";
	assign_op_test_ /= std::uint8_t(2);
	std::cout << "/ uint8_t(2): " << assign_op_test_ << "\n";
	assign_op_test_ %= 2;
	std::cout << "% 2: " << assign_op_test_ << "\n";
	auto to_add_ = assign_op_test_.Shuffle<3, 1, 0, 2>();
	assign_op_test_ += to_add_;
	std::cout << "+ " << to_add_ << ": " << assign_op_test_ << "\n";
	assign_op_test_ *= 3;
	std::cout << "* 3: " << assign_op_test_ << "\n";
	assign_op_test_ += EmuMath::Helpers::new_vector_make<long double>(1, 2, 3, 4, 5);
	std::cout << "+ " << EmuMath::Helpers::new_vector_make<long double>(1, 2, 3, 4, 5) << ": " << assign_op_test_ << "\n";

	std::cout << "---\n\n";
	EmuMath::NewVector<4, std::uint16_t> bitwise_assign_op_test_(1, 2, 3, 10);
	using vec_elem_bits = simple_bitset<decltype(bitwise_assign_op_test_)::value_type_uq>;
	std::cout << bitwise_assign_op_test_ << " (" << EmuMath::NewVector<4, vec_elem_bits>(bitwise_assign_op_test_) << ")\n";
	bitwise_assign_op_test_ ^= 2;
	std::cout << bitwise_assign_op_test_ << " (" << EmuMath::NewVector<4, vec_elem_bits>(bitwise_assign_op_test_) << ")\n";
	bitwise_assign_op_test_ &= ~2;
	std::cout << bitwise_assign_op_test_ << " (" << EmuMath::NewVector<4, vec_elem_bits>(bitwise_assign_op_test_) << ")\n";
	bitwise_assign_op_test_ |= 2048;
	std::cout << bitwise_assign_op_test_ << " (" << EmuMath::NewVector<4, vec_elem_bits>(bitwise_assign_op_test_) << ")\n";
	bitwise_assign_op_test_ ^= EmuMath::Helpers::new_vector_make<int>(0xFFFFFFFF, 0xFFFFFFFE, 0x1, 0x7);
	std::cout << bitwise_assign_op_test_ << " (" << EmuMath::NewVector<4, vec_elem_bits>(bitwise_assign_op_test_) << ")\n";

	std::cout << "---\n\n";
	constexpr auto some_dp_ = EmuMath::Helpers::new_vector_make<float>(1.9f, 2.0f, 2.5f).Dot<int>(EmuMath::Helpers::new_vector_make<double>(2.0, 0.5, 1, 25));

	constexpr auto another_dp_ = EmuMath::NewVector<4, EmuMath::NewVector<4, float>>
	(
		EmuMath::NewVector<4, float>(1.0f, 0.5f, 2.5f, 0.0f),
		EmuMath::NewVector<4, float>(1.0f, 0.5f, 2.5f, 0.0f),
		EmuMath::NewVector<4, float>(1.0f, 0.5f, 2.5f, 0.0f),
		EmuMath::NewVector<4, float>()
	).Dot(EmuMath::Helpers::new_vector_make<int>(1, 2, 3));

	constexpr auto ranged_dp_ = EmuMath::Helpers::new_vector_make<int>(0, 25, 50, 10000).Dot<0, 3>(EmuMath::Helpers::new_vector_make<int>(5, 10, 2, 6));

	constexpr auto vector_for_mag_ = EmuMath::Helpers::new_vector_make<float>(2, 4, 6);
	constexpr auto some_sqr_mag_ = vector_for_mag_.SquareMagnitude();
	constexpr auto some_mag_ = vector_for_mag_.MagnitudeConstexpr();

	constexpr auto some_norm_vec_ = EmuMath::Helpers::new_vector_make<float>(1, 2, 3).NormaliseConstexpr();

	constexpr auto vec_left_ = EmuMath::Helpers::new_vector_make<float>(-1, 0, 0);
	constexpr auto vec_up_ = EmuMath::Helpers::new_vector_make<int>(0, 1, 0);
	constexpr auto vec_up_left_ = EmuMath::Helpers::new_vector_lerp(vec_left_, vec_up_, 0.5f);
	constexpr auto vec_angle_cos_a_ = EmuMath::Helpers::new_vector_angle_cos_constexpr(vector_for_mag_, vector_for_mag_);
	constexpr auto vec_angle_cos_b_ = EmuMath::Helpers::new_vector_angle_cos_constexpr(vec_left_, vec_up_);
	constexpr auto vec_angle_cos_c_ = EmuMath::Helpers::new_vector_angle_cos_constexpr(vec_up_left_, vec_up_);

	std::cout << vec_up_left_.AngleCosConstexpr<true>(vec_up_) << "\n";
	std::cout << vec_up_left_.AngleCos<true>(vec_up_) << "\n";
	std::cout << vec_up_left_.Angle<true>(vec_up_) << "\n";
	std::cout << vec_up_left_.AngleCosConstexpr<double, false>(vec_up_) << "\n";
	std::cout << vec_up_left_.AngleCos<double, false>(vec_up_) << "\n";
	std::cout << vec_up_left_.Angle<double, false>(vec_up_) << "\n";

	std::cout << "---\n\n";
	constexpr auto vec_for_min_a_ = EmuMath::Helpers::new_vector_make<float>(1, 2, 3, 4);
	constexpr auto vec_for_min_b_ = EmuMath::Helpers::new_vector_make<float>(-1, -2, 5, 27);
	
	//constexpr auto min_a_ = EmuMath::Helpers::new_vector_min(vec_for_min_a_, -1);
	constexpr auto min_a_ = vec_for_min_a_.Min(-1);
	//constexpr auto min_b_ = EmuMath::Helpers::new_vector_min(vec_for_min_b_, -1.5L);
	constexpr auto min_b_ = vec_for_min_b_.Min(-1.5L);
	//constexpr auto min_c_ = EmuMath::Helpers::new_vector_min(vec_for_min_a_, vec_for_min_b_);
	constexpr auto min_c_ = vec_for_min_a_.Min(vec_for_min_b_);

	//constexpr auto min_range_a_ = EmuMath::Helpers::new_vector_min_range<1, 3>(vec_for_min_a_, vec_for_min_b_);
	constexpr auto min_range_a_ = vec_for_min_a_.MinRange<1, 3>(vec_for_min_b_);
	//constexpr auto min_range_b_ = EmuMath::Helpers::new_vector_min_range<1, 3>(vec_for_min_b_, vec_for_min_a_);
	constexpr auto min_range_b_ = vec_for_min_b_.MinRange<1, 3>(vec_for_min_a_);

	//constexpr auto min_range_no_copy_a_ = EmuMath::Helpers::new_vector_min_range_no_copy<1, 3, 0>(vec_for_min_a_, vec_for_min_b_);
	constexpr auto min_range_no_copy_a_ = vec_for_min_a_.MinRangeNoCopy<1, 3, 0>(vec_for_min_b_);
	//constexpr auto min_range_no_copy_b_ = EmuMath::Helpers::new_vector_min_range_no_copy<1, 3, 0>(vec_for_min_b_, vec_for_min_a_);
	constexpr auto min_range_no_copy_b_ = vec_for_min_b_.MinRangeNoCopy<1, 3, 0>(vec_for_min_a_);


	constexpr auto max_a_ = EmuMath::Helpers::new_vector_max(vec_for_min_a_, -1);
	constexpr auto max_b_ = EmuMath::Helpers::new_vector_max(vec_for_min_b_, -1.5L);
	constexpr auto max_c_ = EmuMath::Helpers::new_vector_max(vec_for_min_a_, vec_for_min_b_);

	constexpr auto max_range_a_ = EmuMath::Helpers::new_vector_max_range<1, 3>(vec_for_min_a_, vec_for_min_b_);
	constexpr auto max_range_b_ = EmuMath::Helpers::new_vector_max_range<1, 3>(vec_for_min_b_, vec_for_min_a_);

	constexpr auto max_range_no_copy_a_ = EmuMath::Helpers::new_vector_max_range_no_copy<1, 3, 0>(vec_for_min_a_, vec_for_min_b_);
	constexpr auto max_range_no_copy_b_ = EmuMath::Helpers::new_vector_max_range_no_copy<1, 3, 0>(vec_for_min_b_, vec_for_min_a_);

	constexpr auto concat_result_ab_ = vec_for_min_a_.Concat(vec_for_min_b_);
	constexpr auto concat_result_ba_ = vec_for_min_b_.Concat(vec_for_min_a_);

	constexpr auto min_val_a_ = vec_for_min_a_.Min();
	constexpr auto min_val_b_ = vec_for_min_b_.Min();
	constexpr auto min_val_ab_ = vec_for_min_a_.Concat(vec_for_min_b_).Min();

	constexpr auto max_val_a_ = vec_for_min_a_.Max();
	constexpr auto max_val_b_ = vec_for_min_b_.Max();
	constexpr auto max_val_ab_ = vec_for_min_a_.Concat(vec_for_min_b_).Max();

	constexpr auto chain_result_ = concat_result_ab_.Shuffle<0, 4, 1, 5, 7, 2, 2, 2>().Concat(EmuMath::NewVector<4, float>()).Concat(EmuMath::NewVector<12, int>(1337));

	std::cout << "---\n";
	auto test_run_vec_a_ = EmuMath::Helpers::new_vector_make<float>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
	auto test_run_vec_b_ = EmuMath::Helpers::new_vector_make<float>(-10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1);
	auto test_run_vec_ab_ = test_run_vec_a_.Concat<float&>(test_run_vec_b_);
	auto test_run_vec_ba_ = test_run_vec_b_.Concat<const float&>(test_run_vec_a_);
	std::cout << test_run_vec_a_ << "\n";
	std::cout << test_run_vec_b_ << "\n";
	std::cout << test_run_vec_ab_ << "\n";
	std::cout << test_run_vec_ba_ << "\n\n";
	test_run_vec_ab_.at<0>() = 23.0f;
	test_run_vec_ab_.at<20>() = -1337.0f;
	std::cout << test_run_vec_a_ << "\n";
	std::cout << test_run_vec_b_ << "\n";
	std::cout << test_run_vec_ab_ << "\n";
	std::cout << test_run_vec_ba_ << "\n\n";

	constexpr auto gjerjgioer = concat_result_ab_.at(4);

	try
	{
		std::cout << concat_result_ab_.at(255) << "\n";
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << "\n";
	}

	system("pause");

	// GRADIENTS START
	//std::cout << "\n\n";
	//system("pause");
	//std::cout << "\n---\n\n\n";
	//constexpr EmuMath::ColourRGB<float> colour_(-0.2f, 2.5, 2.0f);
	//constexpr auto wrapped_ = colour_.Wrapped<std::uint8_t, true>();
	//constexpr auto clamped_ = colour_.Clamped<std::uint8_t, true>();
	//
	//constexpr EmuMath::ColourRGB<float> white_(1.0f, 1.0f, 1.0f);
	//constexpr EmuMath::ColourRGB<float> black_(0.0f, 0.0f, 0.0f);
	//constexpr auto white_lerp_black_ = white_.Lerp(black_, 0.5f);
	//
	//constexpr auto colour_a_ = EmuMath::ColourRGBA<double>(0.8, 1.0, 0.5, 1.0);
	//constexpr auto colour_b_ = EmuMath::ColourRGBA<std::uint8_t>(0, 255 / 2, 255 / 4, 255);
	//constexpr auto colour_c_ = EmuMath::ColourRGBA<std::uint8_t>(255, 0, 255 / 2, 255 / 4);
	//constexpr auto vector_a_ = EmuMath::Vector<2, double>(0.5, 0.25);
	//constexpr auto lerp_a_ = colour_a_.Lerp(colour_b_, 0.5f);
	//constexpr auto lerp_b_ = colour_a_.Lerp(colour_b_, colour_c_);
	//constexpr auto lerp_c_ = colour_a_.Lerp(colour_b_, vector_a_);
	//constexpr auto lerp_c_min_false_ = lerp_c_.Min<false>();
	//constexpr auto lerp_c_min_true_ = lerp_c_.Min<true>();
	//constexpr auto lerp_c_max_false_ = lerp_c_.Max<false>();
	//constexpr auto lerp_c_max_true_ = lerp_c_.Max<true>();
	//
	//EmuMath::ColourRGBA<float> runtime_rgba_f_(0.1f, -0.1f, 1.0f, 1.5f);
	//std::cout << runtime_rgba_f_ << "\n";
	//runtime_rgba_f_.Wrap();
	//std::cout << runtime_rgba_f_ << "\n";
	//runtime_rgba_f_ *= 0.5f;
	//std::cout << runtime_rgba_f_ << "\n";
	//runtime_rgba_f_ += 0.1;
	//std::cout << runtime_rgba_f_ << "\n";
	//runtime_rgba_f_ -= 0.1;
	//std::cout << runtime_rgba_f_ << "\n";
	//runtime_rgba_f_ /= 2;
	//std::cout << runtime_rgba_f_ << "\n";
	//std::cout << (runtime_rgba_f_ == runtime_rgba_f_) << "\n";
	//std::cout << (runtime_rgba_f_ != runtime_rgba_f_) << "\n";
	//runtime_rgba_f_.Set(0.1, 0.2f, 0.53L, 1);
	//std::cout << runtime_rgba_f_ << "\n";
	//std::cout << "---Grey---\n";
	//std::cout << "Basic Average: " << runtime_rgba_f_.GreyscaleBasic() << "\n";
	//std::cout << "Luminance Average: " << runtime_rgba_f_.GreyscaleLuminance() << "\n";
	//std::cout << "Desaturated: " << runtime_rgba_f_.GreyscaleDesaturate() << "\n";
	//std::cout << "Decomposed (Min): " << runtime_rgba_f_.GreyscaleMin() << "\n";
	//std::cout << "Decomposed (Max): " << runtime_rgba_f_.GreyscaleMax() << "\n";
	//
	//constexpr EmuMath::ColourRGB<float> from_rgba_ = EmuMath::ColourRGBA<float>(1, 2, 3, 4);
	//
	//constexpr auto some_vec_ = EmuMath::Vector<1, long double>(colour_a_.AsVector());
	//
	//auto bloob = EmuMath::ColourRGB<float>().AsVectorRGB();
	//auto bloob_ = EmuMath::ColourRGBA<float>().AsVectorRGB();
	//auto bloob__ = EmuMath::ColourRGB<float>().AsVectorRGBA();
	//auto bloob___ = EmuMath::ColourRGBA<float>().AsVectorRGBA();
	//
	//
	//constexpr EmuMath::WrappedColour<float, true> wrapped_colour_(-0.2, 0.2, 0.5, 1.1);
	//
	//std::cout << "\n\n";
	//auto wrapped_runtime_ = wrapped_colour_;
	//std::cout << wrapped_runtime_ << "\n";
	//wrapped_runtime_.G(25);
	//std::cout << wrapped_runtime_ << "\n";
	//std::cout << (wrapped_runtime_ * 2) << "\n";
	//std::cout << (wrapped_runtime_ * EmuMath::WrappedColour<std::uint8_t, true>(255, 0, 255)) << "\n";
	//
	//EmuMath::WrappedColourRGBA<float> some_wrapped_colour_(2, 3.2, -4.6, 1.0);
	//EmuMath::ColourRGB<float> some_colour_again_( some_wrapped_colour_ );
	//
	//std::cout << "\n\n";
	//std::cout << some_wrapped_colour_ << "\n";
	//EmuMath::WrappedColourRGBA<float> wee = some_wrapped_colour_.Add(2.1);
	//std::cout << wee << "\n";
	//std::cout << wee.Lerp<false>(EmuMath::ColourRGBA<double>(1, 2, 3, 1), 0.5f) << "\n";
	//std::cout << wee.Lerp<true>(EmuMath::ColourRGBA<double>(1, 2, 3, 1), 0.5f) << "\n";
	//
	//decltype(wee)::underlying_colour wee_unwrapped_(wee);
	//
	//constexpr auto wrapped_colour_greyscale_basic_ = wrapped_colour_.GreyscaleBasic();
	//constexpr auto wrapped_colour_greyscale_luminance_ = wrapped_colour_.GreyscaleLuminance();
	//constexpr auto wrapped_colour_greyscale_desaturate_ = wrapped_colour_.GreyscaleDesaturate();
	//constexpr auto wrapped_colour_greyscale_decompose_min_ = wrapped_colour_.GreyscaleMin();
	//constexpr auto wrapped_colour_greyscale_decompose_max_ = wrapped_colour_.GreyscaleMax();
	//
	//constexpr EmuMath::ClampedColourRGBA<float> some_clamped_colour_(-0.1, 0.0, 0.8, 1.5);
	//std::cout << "\n\n\n";
	//using grad_type = EmuMath::Gradient<float>;
	//grad_type gradient_;
	//gradient_.AddClampedColourAnchor(1.0f, EmuMath::ColourRGB<float>(0.75f, 0.1f, 0.0f));
	//gradient_.AddClampedColourAnchor(0.5f, EmuMath::ColourRGB<float>(0.5f, 0.5f, 0.5f));
	//gradient_.AddClampedColourAnchor(123.5f, EmuMath::ColourRGB<float>(0.2f, 1.0f, 1.0f));
	//gradient_.AddClampedAlphaAnchor(1.0f, 0.0f);
	//gradient_.AddClampedColourAnchor(0.9f, EmuMath::ColourRGB<std::uint8_t>(255 / 4, 255 / 2, 255));
	//std::size_t dummy_index_ = gradient_.AddWrappedColourAnchor_GetIndex(0.3f, EmuMath::ColourRGBA<std::int8_t>(-1, -2, -3));
	//std::cout << gradient_ << "\n";
	//gradient_.EraseColourIndex(dummy_index_);
	//gradient_.EraseColourAnchor(0.9f);
	//std::cout << "---\n" << gradient_ << "\n";
	//std::cout << "---\n" << EmuMath::Gradient<std::uint8_t>(gradient_) << "\n";
	//std::cout << "---\n";
	//std::cout << "at(0.0): " << gradient_.GetColour(0.0f) << "\n";
	//std::cout << "at(1.0): " << gradient_.GetColour(1.0f) << "\n";
	//std::cout << "at(0.5): " << gradient_.GetColour(0.5f) << "\n";
	//std::cout << "at(0.75): " << gradient_.GetColour(0.75f) << "\n";
	//std::cout << "at(0.25): " << gradient_.GetColour(0.25f) << "\n";
	//std::cout << "---\n";
	//std::cout << "at(0.0): " << gradient_.GetAlpha(0.0f) << "\n";
	//std::cout << "at(1.0): " << gradient_.GetAlpha(1.0f) << "\n";
	//std::cout << "at(0.5): " << gradient_.GetAlpha(0.5f) << "\n";
	//std::cout << "at(0.75): " << gradient_.GetAlpha(0.75f) << "\n";
	//std::cout << "at(0.25): " << gradient_.GetAlpha(0.25f) << "\n";
	//std::cout << "---\n";
	//std::cout << "at(0.0): " << gradient_.Get(0.0f) << "\n";
	//std::cout << "at(1.0): " << gradient_.Get(1.0f) << "\n";
	//std::cout << "at(0.5): " << gradient_.Get(0.5f) << "\n";
	//std::cout << "at(0.75): " << gradient_.Get(0.75f) << "\n";
	//std::cout << "at(0.25): " << gradient_.Get(0.25f) << "\n";
	//std::cout << "---\n";
	//std::cout << (gradient_ == gradient_) << "\n";
	//std::cout << (EmuMath::Gradient<std::int8_t>(gradient_) == EmuMath::Gradient<std::uint8_t>(gradient_)) << "\n";
	//std::cout << (gradient_ == grad_type()) << "\n";
	//std::cout << "---\n";
	//std::cout << (gradient_ != gradient_) << "\n";
	//std::cout << (EmuMath::Gradient<std::int8_t>(gradient_) != EmuMath::Gradient<std::uint8_t>(gradient_)) << "\n";
	//std::cout << (gradient_ != grad_type()) << "\n";
	//std::cout << "---\n";
	//std::cout << gradient_.HasMatchingAlphaAnchors(gradient_) << "\n";
	//std::cout << EmuMath::Gradient<std::int8_t>(gradient_).HasMatchingAlphaAnchors(EmuMath::Gradient<std::uint8_t>(gradient_)) << "\n";
	//std::cout << gradient_.HasMatchingAlphaAnchors(grad_type()) << "\n";
	//std::cout << "---\n";
	//std::cout << gradient_.HasMatchingColourAnchors(gradient_) << "\n";
	//std::cout << EmuMath::Gradient<std::int8_t>(gradient_).HasMatchingColourAnchors(EmuMath::Gradient<std::uint8_t>(gradient_)) << "\n";
	//std::cout << gradient_.HasMatchingColourAnchors(grad_type()) << "\n";
	//std::cout << "---\n";
	//grad_type ______;
	//______.AddClampedColourAnchor<float, true>(0.5f, {});
	//std::cout << (______ == grad_type()) << "\n";
	//std::cout << (______ != grad_type()) << "\n";
	//std::cout << ______.HasMatchingAlphaAnchors(grad_type()) << "\n";
	//std::cout << ______.HasMatchingColourAnchors(grad_type()) << "\n";
	//std::cout << "---\n";
	//
	//constexpr auto wrap_test_ = grad_type::wrap_anchor(-0.3f);
	//
	//constexpr auto red_ = EmuMath::Colours::Lime();
	//
	//grad_type::anchor_type anchor_ = 0.0f;
	//
	//
	//grad_type gradient_colours_;
	//gradient_colours_.AddClampedColourAnchor(0.0f, EmuMath::Colours::Blue());
	//gradient_colours_.AddClampedColourAnchor(0.35f, EmuMath::Colours::Blue());
	//gradient_colours_.AddClampedColourAnchor(0.45f, EmuMath::Colours::White());
	//gradient_colours_.AddClampedColourAnchor(0.5f, EmuMath::Colours::Black());
	//gradient_colours_.AddClampedColourAnchor(0.65f, EmuMath::Colours::Yellow());
	//gradient_colours_.AddClampedColourAnchor(0.85f, EmuMath::Colours::Green());
	//gradient_colours_.AddClampedColourAnchor(1.0f, EmuMath::Colours::Red());
	//
	//grad_type gradient_greyscale_;
	//gradient_greyscale_.AddClampedColourAnchor(0.0f, EmuMath::Colours::White());
	//gradient_greyscale_.AddClampedColourAnchor(1.0f, EmuMath::Colours::Black());
	//
	//grad_type& noise_gradient_ = gradient_colours_;
	//std::cout << "\nNoise Gradient:\n";
	//std::cout << noise_gradient_ << "\n";
	//std::cout << "\nNoise Gradient Reversed:\n";
	//noise_gradient_.ReverseColours();
	//std::cout << noise_gradient_ << "\n";
	//
	//__m128 some_a_128_ = _mm_set_ps(3.0f, 2.0f, 1.0f, 0.0f);
	//__m128 some_b_128_ = _mm_set_ps(7.0f, 6.0f, 5.0f, 4.0f);
	//std::cout << EmuMath::FastVector4f(EmuSIMD::_underlying_simd_helpers::_execute_shuffle<1, 1, 3, 3>(some_a_128_, some_b_128_)) << "\n";
	//
	//EmuSIMD::append_simd_vector_to_stream<8>
	//(
	//	std::cout,
	//	_mm256_set_epi8(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31)
	//) << "\n";
	//
	//
	//__m256i _8_bit_256_ = _mm256_setr_epi8    (1,  2,  3,  4,  5,  6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);
	//__m256i _8_bit_mul_256_ = _mm256_setr_epi8(32, 31, 30, 29, 28, 1, 2, 3, 4, 10, 5,  2,  1,  3,  4,  4,  5,  2,  6,  5,  4,  3,  2,  1,  1,  0,  3,  4,  5,  1,  2,  3);
	//EmuSIMD::append_simd_vector_to_stream<8, false>
	//(
	//	std::cout,
	//	EmuSIMD::_underlying_simd_helpers::_mul_all_int<8>(_8_bit_256_, _8_bit_mul_256_)
	//) << "\n";
	//
	//__m256 cmp_a_ = _mm256_set_ps(2.0f, 1.0f, 3.0f, 4.0f, 0.0f, 2.0f, 3.0f, 3.0f);
	//__m256 cmp_b_ = _mm256_set_ps(2.0f, 5.0f, 6.6f, 4.0f, 3.0f, 1.0f, 2.0f, 3.0f);
	//EmuSIMD::append_simd_vector_to_stream
	//(
	//	std::cout,
	//	EmuSIMD::_underlying_simd_helpers::_make_register_from_movemask_fp<__m256>(_mm256_movemask_ps(_mm256_cmp_ps(cmp_a_, cmp_b_, _CMP_EQ_OS)))
	//) << "\n";
	//
	//__m128i mod_a_256_ = _mm_setr_epi32(10, 3, -4, 4);
	//__m128i mod_b_256_ = _mm_setr_epi32(1,  2,  3, 4);
	//EmuSIMD::append_simd_vector_to_stream
	//(
	//	std::cout,
	//	EmuSIMD::_underlying_simd_helpers::_mod_int<32, true>(mod_a_256_, mod_b_256_)
	//) << "\n";
	//EmuSIMD::append_simd_vector_to_stream
	//(
	//	std::cout,
	//	EmuSIMD::_underlying_simd_helpers::_rem_int<32, true>(mod_a_256_, mod_b_256_)
	//) << "\n";
	//EmuSIMD::append_simd_vector_to_stream(std::cout, EmuSIMD::setallone<__m256>()) << "\n";
	//
	//
	//std::cout << "---\n\n";
	//
	//
	//using testing_register = __m256i;
	//constexpr std::size_t testing_element_width = 8;
	//testing_register a_simd_ = EmuSIMD::set_incrementing<testing_register, 1, testing_element_width>();
	//testing_register b_simd_ = EmuSIMD::set_incrementing<testing_register, 33, testing_element_width>();
	//testing_register mask_simd_ = EmuSIMD::index_mask<testing_register, true, false, false, false, false, true, false, false>::get();
	//EmuSIMD::append_simd_vector_to_stream<testing_element_width, false>(std::cout, a_simd_) << " BLEND\n";
	//EmuSIMD::append_simd_vector_to_stream<testing_element_width, false>(std::cout, b_simd_) << " WITH MASK\n";
	//EmuSIMD::append_simd_vector_to_stream<testing_element_width, false>(std::cout, mask_simd_) << ":\n";
	//EmuSIMD::append_simd_vector_to_stream<testing_element_width, false>(std::cout, EmuSIMD::blendv(a_simd_, b_simd_, mask_simd_)) << "\n";
	//EmuSIMD::append_simd_vector_to_stream<testing_element_width, false>
	//(
	//	std::cout,
	//	EmuSIMD::blend
	//	<
	//		false, false, true, true, true, false, true, false, false, false, false, true, true, true, true, false,
	//		true, true, true, true, true, false, true, false, false, false, false, true, true, true, true, true
	//	>(a_simd_, b_simd_)
	//) << "\n";
	//
	//__m256 lhs_ = EmuSIMD::set<__m256>(1, 2, 3, 4, 5, 6, 7, 8);
	//__m256 rhs_ = EmuSIMD::set<__m256>(9, 10, 11, 12, 13, 14, 15, 16);
	//EmuSIMD::append_simd_vector_to_stream(std::cout, lhs_) << "\n";
	//EmuSIMD::append_simd_vector_to_stream(std::cout, rhs_) << "\n";
	//EmuSIMD::append_simd_vector_to_stream(std::cout, _mm256_permute2f128_ps(lhs_, rhs_, 0b00110001)) << "\n";
	//
	//__m256i lhs_int_ = _mm256_set_epi32(1, 2, 3, 4, 5, 6, 7, 8);
	//__m256i rhs_int_ = _mm256_set_epi32(1, 4, 3, 2, 5, 6, 7, 8);
	//std::cout << std::bitset<32>(_mm256_movemask_epi8(_mm256_cmpeq_epi32(lhs_int_, rhs_int_))) << "\n";
	//std::cout << EmuSIMD::cmp_all_eq<true, true, true, true, true, false, true, false, true>(lhs_int_, rhs_int_) << "\n";
	//EmuSIMD::append_simd_vector_to_stream(std::cout, EmuSIMD::horizontal_sum_fill(lhs_)) << "\n";
	//
	//
	//constexpr EmuMath::NoiseType test_noise_type_flag = EmuMath::NoiseType::PERLIN;
	//constexpr std::size_t test_noise_dimensions = 3;
	//constexpr auto sample_count = EmuMath::Vector<3, std::size_t>(1024, 1024, 1);
	//constexpr bool use_fractal = true;
	//using scalar_test_noise_processor = EmuMath::Functors::noise_sample_processor_perlin_normalise<test_noise_dimensions>;
	//using fast_test_noise_processor = EmuMath::Functors::fast_noise_sample_processor_perlin_normalise<test_noise_dimensions>;
	//
	//constexpr std::size_t num_iterations = 1;
	//std::vector<EmuMath::NoiseTable<test_noise_dimensions, float>> noise_;
	//std::vector<EmuMath::FastNoiseTable<test_noise_dimensions, 0>> fast_noise_;
	//noise_.resize(num_iterations, decltype(noise_)::value_type());
	//fast_noise_.resize(num_iterations, decltype(fast_noise_)::value_type());
	//
	//system("pause");
	//for (std::size_t i = 0; i < num_iterations; ++i)
	//{
	//	std::cout << "\nNOISE BATCH " << i << "\n";
	//	timer_.Restart();
	//	noise_[i].GenerateNoise<test_noise_type_flag, scalar_test_noise_processor>
	//	(
	//		decltype(noise_)::value_type::MakeOptions
	//		(
	//			sample_count,
	//			EmuMath::Vector<3, float>(0.0f, 0.0f, 0.0f),
	//			EmuMath::Vector<3, float>(1.0f / 1024.0f, 1.0f / 1024.0f, 1.0f / 1024.0f),
	//			3.0f,
	//			true,
	//			use_fractal,
	//			EmuMath::Info::NoisePermutationInfo(4096, EmuMath::Info::NoisePermutationShuffleMode::SEED_32, true, 1337, 1337),
	//			EmuMath::Info::FractalNoiseInfo<float>(6, 2.0f, 0.5f)
	//		)
	//	);
	//	timer_.Pause();
	//	std::cout << "FINISHED SCALAR NOISE IN: " << timer_.GetMilli() << "ms\n";
	//
	//
	//	timer_.Restart();
	//	fast_noise_[i].GenerateNoise<test_noise_type_flag, fast_test_noise_processor>
	//	(
	//		decltype(fast_noise_)::value_type::make_options
	//		(
	//			sample_count,
	//			EmuMath::Vector<3, float>(0.0f, 0.0f, 0.0f),
	//			EmuMath::Vector<3, float>(1.0f / 1024.0f, 1.0f / 1024.0f, 1.0f / 1024.0f),
	//			3.0f,
	//			true,
	//			use_fractal,
	//			EmuMath::Info::NoisePermutationInfo(4096, EmuMath::Info::NoisePermutationShuffleMode::SEED_32, true, 1337, 1337),
	//			EmuMath::Info::FractalNoiseInfo<float>(6, 2.0f, 0.5f)
	//		)
	//	);
	//	timer_.Pause();
	//	std::cout << "FINISHED FAST NOISE IN: " << timer_.GetMilli() << "ms\n";
	//}
	//WriteNoiseTableToPPM(noise_, noise_gradient_, "test_noise_scalar");
	//WriteNoiseTableToPPM(fast_noise_, noise_gradient_, "test_noise_simd");

	// #### THREADED_NOISE_EXAMPLE ####
	//std::cout << "GENERATING FAST NOISE VIA THREAD POOL...\n";
	//timer_.Restart();
	//EmuThreads::DefaultThreadPool thread_pool_(6);
	//using fast_noise_array_type = std::vector<std::vector<EmuMath::FastNoiseTable<3, 1>>>;
	//fast_noise_array_type fast_noise_array_(8, fast_noise_array_type::value_type(8, EmuMath::FastNoiseTable<3, 1>()));
	//for (std::size_t x = 0, end_x_ = fast_noise_array_.size(); x < end_x_; ++x)
	//{
	//	auto& array_ = fast_noise_array_[x];
	//	for (std::size_t y = 0, end_y_ = fast_noise_array_.size(); y < end_y_; ++y)
	//	{
	//		auto* p_table_ = &(array_[y]);
	//		auto options_ = EmuMath::FastNoiseTable<3, 1>::make_options
	//		(
	//			EmuMath::Vector<3, std::size_t>(128, 128, 1),
	//			EmuMath::Vector<3, float>((1.0f / 1024.0f) * (x * 128), (1.0f / 1024.0f) * (y * 128), 0.0f),
	//			EmuMath::Vector<3, float>(1.0f / 1024.0f, 1.0f / 1024.0f, 1.0f / 1024.0f),
	//			3.0f,
	//			true,
	//			true,
	//			EmuMath::Info::NoisePermutationInfo(4096, EmuMath::Info::NoisePermutationShuffleMode::SEED_32, true, 1337, 1337),
	//			EmuMath::Info::FractalNoiseInfo<float>(6, 2.0f, 0.5f)
	//		);
	//
	//		using func_type = bool(EmuMath::FastNoiseTable<3, 1>::*)(const EmuMath::FastNoiseTable<3, 1>::options_type&);
	//
	//		thread_pool_.AllocateTask
	//		(
	//			std::bind<func_type>
	//			(
	//				&EmuMath::FastNoiseTable<3, 1>::GenerateNoise<test_noise_type_flag, test_noise_processor>,
	//				p_table_,
	//				options_
	//			)
	//		);
	//	}
	//}
	//thread_pool_.ViewWorkAllocator().WaitForAllTasksToComplete();
	//timer_.Pause();
	//std::cout << "FINISHED FAST NOISE VIA THREAD POOL IN: " << timer_.GetMilli() << "ms\n";
	//EmuMath::Vector3<std::size_t> resolution_ = fast_noise_.size();
	//for (std::size_t z = 0; z < resolution_.z; ++z)
	//{
	//	std::cout << "\nOutputting threaded image layer #" << z << "...\n";
	//
	//	std::ostringstream name_;
	//	name_ << "./test_noise_threaded_" << z << ".ppm";
	//	std::ofstream out_ppm_(name_.str(), std::ios_base::out | std::ios_base::binary);
	//	out_ppm_ << "P6" << std::endl << resolution_.x << ' ' << resolution_.y << std::endl << "255" << std::endl;
	//
	//	for (std::size_t y = 0; y < resolution_.y; ++y)
	//	{
	//		for (std::size_t x = 0; x < resolution_.x; ++x)
	//		{
	//			auto& array_ = fast_noise_array_[x / 128];
	//			auto& noise_table_ = array_[y / 128];
	//			EmuMath::ColourRGB<std::uint8_t> colour_byte_ = noise_gradient_.GetColour<std::uint8_t>(noise_table_.at(x % 128, y % 128, z % 1));
	//			out_ppm_ << (char)colour_byte_.R() << (char)colour_byte_.G() << (char)colour_byte_.B();
	//		}
	//	}
	//	out_ppm_.close();
	//}
	//std::cout << "Finished outputting all 3D noise layers from array.\n";



	//EmuSIMD::append_simd_vector_to_stream(std::cout, EmuSIMD::cast<__m256>(_mm_set_ps(1.0f, 2.0f, 3.0f, 4.0f))) << "\n";
	//EmuMath::Functors::make_fast_noise_3d<EmuMath::NoiseType::PERLIN, __m128> fast_generator_;
	//__m128 test_128_ = fast_generator_(_mm_set1_ps(0.4f), _mm_set1_ps(0.0f), _mm_set1_ps(1.0f), _mm_set1_ps(16.0f), _mm_set1_epi32(1023), EmuMath::NoisePermutations(1024, 0U));
	//std::cout << "\n\n";
	//std::cout << EmuMath::FastVector4f(test_128_) << "\n";
	//std::cout << EmuMath::Functors::make_noise_3d<EmuMath::NoiseType::PERLIN, float>()({ 0.4f, 0.0f, 1.0f }, 16.0f, EmuMath::NoisePermutations(1024, 0U)) << "\n";
	//
	//__m128 some_float_ = _mm_set_ps(1.0f, 2.0f, 3.0f, 4.0f);
	//std::cout << EmuMath::FastVector4f(some_float_) << "\n";
	//__m128i some_ints_ = _mm_cvtps_epi32(some_float_);
	//std::cout << EmuMath::FastVector4f(_mm_cvtepi32_ps(some_ints_)) << "\n";

#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}
