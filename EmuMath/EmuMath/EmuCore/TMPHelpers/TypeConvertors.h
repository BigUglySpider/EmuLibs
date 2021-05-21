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
}

#endif