#ifndef EMU_CORE_TMP_HELPERS_TYPE_CONVERTORS_H_INC_
#define EMU_CORE_TMP_HELPERS_TYPE_CONVERTORS_H_INC_ 1

#include <type_traits>

namespace EmuCore::TMP
{
	template<typename T_>
	struct remove_ref_cv
	{
		using type = std::remove_cv_t<std::remove_reference_t<T_>>;
	};
	template<typename T_>
	using remove_ref_cv_t = typename remove_ref_cv<T_>::type;

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

	template<std::size_t NumBytes_>
	using int_of_size_t = std::conditional_t
	<
		NumBytes_ == sizeof(std::int8_t),
		std::int8_t,
		std::conditional_t
		<
			NumBytes_ == sizeof(std::int16_t),
			std::int16_t,
			std::conditional_t
			<
				NumBytes_ == sizeof(std::int32_t),
				std::int32_t,
				std::conditional_t
				<
					NumBytes_ == sizeof(std::int64_t),
					std::int64_t,
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
	using next_size_up_t = typename EmuCore::TMP::next_size_up<T>::type;

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

	/// <summary>
	/// <para> Determines the type a passed unsigned int may be converted to to maintain any of its values with a signed representation. </para>
	/// <para> For std::uint32_t and below, this will provide the std::int of the next size (e.g. std::uint32_t -> std::int64_t). </para>
	/// <para> For anything higher, this will provide the float type as no standard int will be able to store uint64 values above the max of std::int64_t. </para>
	/// <para> If the passed type is already signed, the same type will be provided. </para>
	/// </summary>
	/// <typeparam name="UintT_">Type to provide the lossless signed rep of. If it is already signed, the determined type will be the same as this.</typeparam>
	template<typename UintT_>
	struct uint_lossless_signed_rep
	{
		using type = std::conditional_t
		<
			std::is_signed_v<UintT_>,
			UintT_,
			std::conditional_t
			<
				std::is_same_v<std::uint8_t, UintT_>,
				std::int16_t,
				std::conditional_t
				<
					std::is_same_v<std::uint16_t, UintT_>,
					std::int32_t,
					std::conditional_t
					<
						std::is_same_v<std::uint32_t, UintT_>,
						std::int64_t,
						float
					>
				>
			>
		>;
	};
	/// <summary>
	/// <para> Type the passed unsigned int may be converted to to maintain any of its values with a signed representation. </para>
	/// <para> For std::uint32_t and below, this will provide the std::int of the next size (e.g. std::uint32_t -> std::int64_t). </para>
	/// <para> For anything higher, this will provide the float type as no standard int will be able to store uint64 values above the max of std::int64_t. </para>
	/// <para> If the passed type is already signed, the same type will be provided. </para>
	/// </summary>
	/// <typeparam name="UintT_">Type to provide the lossless signed rep of. If it is already signed, the determined type will be the same as this.</typeparam>
	template<typename UintT_>
	using uint_lossless_signed_rep_t = typename EmuCore::TMP::uint_lossless_signed_rep<UintT_>::type;

	template<typename T_>
	struct get_value_type
	{
		using type = std::remove_reference_t<std::remove_pointer_t<T_>>;
	};
	template<template<typename...Ts__> class Template_, typename...Ts_>
	struct get_value_type<Template_<Ts_...>>
	{
		using type = typename Template_<Ts_...>::value_type;
	};
	template<template<std::size_t Size__, typename Ts__> class Template_, std::size_t Size_, typename...Ts_>
	struct get_value_type<Template_<Size_, Ts_...>>
	{
		using type = typename Template_<Size_, Ts_...>::value_type;
	};
	template<template<std::size_t SizeX__, std::size_t SizeY__, typename Ts__> class Template_, std::size_t SizeX_, std::size_t SizeY_, typename...Ts_>
	struct get_value_type<Template_<SizeX_, SizeY_, Ts_...>>
	{
		using type = typename Template_<SizeX_, SizeY_, Ts_...>::value_type;
	};
	template<template<typename T__, std::size_t Size__> class Template_, typename T_, std::size_t Size_>
	struct get_value_type<Template_<T_, Size_>>
	{
		using type = typename Template_<T_, Size_>::value_type;
	};
	template<template<typename T__, std::size_t SizeX__, std::size_t SizeY__> class Template_, typename T_, std::size_t SizeX_, std::size_t SizeY_>
	struct get_value_type<Template_<T_, SizeX_, SizeY_>>
	{
		using type = typename Template_<T_, SizeX_, SizeY_>::value_type;
	};
	template<typename T_>
	struct get_value_type<std::reference_wrapper<T_>>
	{
		using type = typename std::reference_wrapper<T_>::type;
	};
	template<typename T_>
	using get_value_type_t = typename get_value_type<T_>::type;

	template<class Item_>
	struct item_info
	{
		using type = Item_;
	};

	template<class T_>
	struct get_reference_wrapper_contained_type
	{
		using type = T_;
	};
	template<class T_>
	struct get_reference_wrapper_contained_type<std::reference_wrapper<T_>>
	{
		using type = typename std::reference_wrapper<T_>::type;
	};

	template<class T_>
	struct remove_all_pointers
	{
		using type = T_;
	};
	template<class T_>
	struct remove_all_pointers<T_*>
	{
		using type = typename remove_all_pointers<std::remove_pointer_t<T_>>::type;
	};

	template<typename...PackedArgs_>
	struct first_packed_arg
	{
		using type = void;
	};
	template<typename FirstPackedArg_, typename...FurtherArgs_>
	struct first_packed_arg<FirstPackedArg_, FurtherArgs_...>
	{
		using type = FirstPackedArg_;
	};
	template<typename OnlyPackedArg_>
	struct first_packed_arg<OnlyPackedArg_>
	{
		using type = OnlyPackedArg_;
	};
	template<>
	struct first_packed_arg<>
	{
		using type = void;
	};
	template<typename...PackedArgs_>
	using first_packed_arg_t = typename first_packed_arg<PackedArgs_...>::type;

	template<std::size_t N_, typename...PackedArgs_>
	struct nth_packed_arg
	{
		using type = void;
	};
	template<std::size_t N_, typename FirstPackedArg_, typename...FurtherArgs_>
	struct nth_packed_arg<N_, FirstPackedArg_, FurtherArgs_...>
	{
		using type = std::conditional_t<N_ == 0, FirstPackedArg_, typename nth_packed_arg<N_ - 1, FurtherArgs_...>::type>;
	};
	template<std::size_t N_, typename OnlyPackedArg_>
	struct nth_packed_arg<N_, OnlyPackedArg_>
	{
		using type = std::conditional_t<N_ == 0, OnlyPackedArg_, void>;
	};
	template<std::size_t N_, typename...PackedArgs_>
	using nth_packed_arg_t = typename nth_packed_arg<N_, PackedArgs_...>::type;

	/// <summary>
	/// <para> Casts a reference to an lvalue-reference. </para>
	/// <para> This can effectively be considered an `unmove` cast, treating lvalues as lvalues and casting rvalues to lvalues. </para>
	/// <para>
	///		WARNING: This is for casting pre-existing, named rvalues.
	///		Passing a new rvalue (such as `my_type(5)) will result in output of a dangling reference. 
	/// </para>
	/// </summary>
	/// <param name="ref_">Reference to cast to an lvalue reference.</param>
	/// <returns>The passed ref_ cast to an lvalue reference.</returns>
	template<typename T_>
	[[nodiscard]] constexpr inline std::remove_reference_t<T_>& lval_ref_cast(std::remove_reference_t<T_>& ref_)
	{
		return ref_;
	}
	template<typename T_>
	[[nodiscard]] constexpr inline std::remove_reference_t<T_>& lval_ref_cast(std::remove_reference_t<T_>&& ref_)
	{
		return static_cast<std::remove_reference_t<T_>&>(ref_);
	}
}

#endif
