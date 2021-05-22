#ifndef EMU_CORE_TMP_HELPERS_TYPE_CONVERTORS_H_INC_
#define EMU_CORE_TMP_HELPERS_TYPE_CONVERTORS_H_INC_

#include <type_traits>

namespace EmuCore::TMPHelpers
{
	/// <summary> The floating-point type best suited to representing the passed type based on byte size. </summary>
	/// <typeparam name="T">Type to provide the best suited floating point representing type of.</typeparam>
	template<typename T>
	using best_floating_point_rep_t = std::conditional_t
	<
		std::is_floating_point_v<T>,
		T,
		std::conditional_t
		<
			std::is_signed_v<T>,
			std::conditional_t
			<
				(sizeof(T) <= sizeof(float)),
				float,
				std::conditional_t
				<
					(sizeof(T) <= sizeof(double)),
					double,
					long double
				>
			>,
			std::conditional_t
			<
				(sizeof(T) < sizeof(float)),
				float,
				std::conditional_t
				<
					(sizeof(T) < sizeof(double)),
					double,
					long double
				>
			>
		>
	>;

	/// <summary>
	/// <para> The signed integer type best suited to representing the passed type based on byte size. Sign bit is taken into consideration. </para>
	/// <para> Not to be confused with best_signed_rep_t. </para>
	/// </summary>
	/// <typeparam name="T">Type to provide the best suited signed value representing type of.</typeparam>
	template<typename T>
	using best_signed_int_rep_t = std::conditional_t
	<
		std::is_signed_v<T> && std::is_integral_v<T>,
		T,
		std::conditional_t
		<
			(sizeof(T) < sizeof(std::int8_t)),
			std::int8_t,
			std::conditional_t
			<
				(sizeof(T) < sizeof(std::int16_t)),
				std::int16_t,
				std::conditional_t
				<
					(sizeof(T) < sizeof(std::int32_t)),
					std::int32_t,
					std::int64_t
				>
			>
		>
	>;

	/// <summary>
	/// <para> The signed type best suited to representing the passed type based on byte size. Sign bit is taken into consideration. </para>
	/// <para> Not to be confused with best_signed_int_rep_t. </para>
	/// </summary>
	/// <typeparam name="T">Type to provide the best suited signed value representing type of.</typeparam>
	template<typename T>
	using best_signed_rep_t = std::conditional_t
	<
		std::is_signed_v<T>,
		T,
		std::conditional_t
		<
			std::is_floating_point_v<T>,
			best_floating_point_rep_t<T>,
			best_signed_int_rep_t<T>
		>
	>;

	/// <summary>
	/// <para> The unsigned integer type best suited to representing the passed type based on byte size. </para>
	/// <para> This is only suitable with floating point types when they are planned to be used like integers. </para>
	/// <para> Similarly, this is only suitable with signed types when they are planned to be used only in positive ranges. </para>
	/// </summary>
	/// <typeparam name="T">Type to provide the best suited unsigned integer representing type of.</typeparam>
	template<typename T>
	using best_unsigned_int_rep_t = std::conditional_t
	<
		std::is_unsigned_v<T>,
		T,
		std::conditional_t
		<
			(sizeof(T) <= sizeof(std::uint8_t)),
			std::uint8_t,
			std::conditional_t
			<
				(sizeof(T) <= sizeof(std::uint16_t)),
				std::uint16_t,
				std::conditional_t
				<
					(sizeof(T) <= sizeof(std::uint32_t)),
					std::uint32_t,
					std::uint64_t
				>
			>
		>
	>;

	template<typename T>
	using best_int_rep_t = std::conditional_t
	<
		std::is_signed_v<T>,
		best_signed_int_rep_t<T>,
		best_unsigned_int_rep_t<T>
	>;

	template<std::size_t NumBytes_>
	using uint_of_size_t = std::conditional_t
	<
		NumBytes_ == sizeof(std::uint8_t),
		std::uint8_t,
		std::conditional_t
		<
			NumBytes_ == sizeof(std::uint16_t),
			std::uint16_t,
			std::conditional_t
			<
				NumBytes_ == sizeof(std::uint32_t),
				std::uint32_t,
				std::conditional_t
				<
					NumBytes_ == sizeof(std::uint64_t),
					std::uint64_t,
					std::false_type
				>
			>
		>
	>;

	template<typename T>
	struct next_size_up
	{
		static constexpr std::size_t original_size = sizeof(T);
		
		using type = std::conditional_t
		<
			std::is_integral_v<T>,
			std::conditional_t
			<
				std::is_signed_v<T>,
				std::conditional_t
				<
					original_size == sizeof(std::int8_t),
					std::int16_t,
					std::conditional_t
					<
						original_size == sizeof(std::int16_t),
						std::int32_t,
						std::int64_t
					>
				>,
				std::conditional_t
				<
					original_size == sizeof(std::uint8_t),
					std::uint16_t,
					std::conditional_t
					<
						original_size == sizeof(std::uint16_t),
						std::uint32_t,
						std::uint64_t
					>
				>
			>,
			std::conditional_t
			<
				original_size == sizeof(float),
				double,
				long double
			>
		>;

		static constexpr std::size_t next_size = sizeof(type);
		static constexpr bool is_new_size = original_size != next_size;
		static constexpr bool is_new_type = !std::is_same_v<T, type>;
	};
	template<typename T>
	using next_size_up_t = typename EmuCore::TMPHelpers::next_size_up<T>::type;

	template<typename T>
	struct unsigned_if_int
	{
		using type = std::conditional_t<std::is_integral_v<T>, std::make_unsigned_t<T>, T>;
	};
	template<>
	struct unsigned_if_int<float>
	{
		using type = float;
	};
	template<>
	struct unsigned_if_int<double>
	{
		using type = double;
	};
	template<>
	struct unsigned_if_int<long double>
	{
		using type = long double;
	};
	template<typename T>
	using unsigned_if_int_t = typename unsigned_if_int<T>::type;

	template<typename T>
	struct signed_if_int
	{
		using type = std::conditional_t<std::is_integral_v<T>, std::make_signed_t<T>, T>;
	};
	template<>
	struct signed_if_int<float>
	{
		using type = float;
	};
	template<>
	struct signed_if_int<double>
	{
		using type = double;
	};
	template<>
	struct signed_if_int<long double>
	{
		using type = long double;
	};
	template<typename T>
	using signed_if_int_t = typename signed_if_int<T>::type;
}

#endif
