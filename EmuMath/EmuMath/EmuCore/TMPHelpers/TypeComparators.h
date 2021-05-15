#ifndef EMU_CORE_TMP_HELPERS_TYPE_COMPARATORS_H_INC_
#define EMU_CORE_TMP_HELPERS_TYPE_COMPARATORS_H_INC_

#include <type_traits>

namespace EmuCore::TMPHelpers
{
	/// <summary> Finds the largest byte-sized type of the passed options. For matching type sizes, the leftmost type receives priority. </summary>
	/// <typeparam name="X_">First type to compare. Required.</typeparam>
	/// <typeparam name="Y_">Second type to compare. Required.</typeparam>
	/// <typeparam name="Others_">All additional types to compare. Optional.</typeparam>
	template<typename X_, typename Y_, typename...Others_>
	struct highest_byte_size
	{
		using type = typename highest_byte_size<X_, typename highest_byte_size<Y_, Others_...>::type>::type;
	};
	/// <summary> Finds the largest byte-sized type of the passed options. For matching type sizes, X_ receives priority. </summary>
	/// <typeparam name="X_">First type to compare.</typeparam>
	/// <typeparam name="Y_">Second type to compare.</typeparam>
	template<typename X_, typename Y_>
	struct highest_byte_size<X_, Y_>
	{
		using type = std::conditional_t<(sizeof(X_) >= sizeof(Y_)), X_, Y_>;
	};
	/// <summary> The largest byte-sized type of the passed options. For matching type sizes, the leftmost type receives priority. </summary>
	/// <typeparam name="X_">First type to compare. Required.</typeparam>
	/// <typeparam name="Y_">Second type to compare. Required.</typeparam>
	/// <typeparam name="Others_">All additional types to compare. Optional.</typeparam>
	template<typename X_, typename Y_, typename...Others_>
	using highest_byte_size_t = typename highest_byte_size<X_, Y_, Others_...>::type;

	/// <summary> Finds the smallest byte-sized type of the passed options. For matching type sizes, the leftmost type receives priority. </summary>
	/// <typeparam name="X_">First type to compare. Required.</typeparam>
	/// <typeparam name="Y_">Second type to compare. Required.</typeparam>
	/// <typeparam name="Others_">All additional types to compare. Optional.</typeparam>
	template<typename X_, typename Y_, typename...Others_>
	struct lowest_byte_size
	{
		using type = typename lowest_byte_size<X_, typename lowest_byte_size<Y_, Others_...>::type>::type;
	};
	/// <summary> Finds the smallest byte-sized type of the passed options. For matching type sizes, X_ receives priority. </summary>
	/// <typeparam name="X_">First type to compare.</typeparam>
	/// <typeparam name="Y_">Second type to compare.</typeparam>
	template<typename X_, typename Y_>
	struct lowest_byte_size<X_, Y_>
	{
		using type = std::conditional_t<(sizeof(X_) <= sizeof(Y_)), X_, Y_>;
	};
	/// <summary> The smallest byte-sized type of the passed options. For matching type sizes, the leftmost type receives priority. </summary>
	/// <typeparam name="X_">First type to compare. Required.</typeparam>
	/// <typeparam name="Y_">Second type to compare. Required.</typeparam>
	/// <typeparam name="Others_">All additional types to compare. Optional.</typeparam>
	template<typename X_, typename Y_, typename...Others_>
	using lowest_byte_size_t = typename lowest_byte_size<X_, Y_, Others_...>::type;

	/// <summary> The floating-point type best suited to representing the passed type based on byte size. </summary>
	/// <typeparam name="T">Type to provide the best suited floating point representing type of.</typeparam>
	template<typename T>
	using best_floating_point_rep_t = std::conditional_t
	<
		std::is_floating_point_v<T>,
		T,
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
		>
	>;

	/// <summary>
	/// <para> The signed integer type best suited to representing the passed type based on byte size. Sign bit is taken into consideration. </para>
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
			// FLOATING POINT REPS
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
			>,
			// INTEGER REPS
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
}

#endif
