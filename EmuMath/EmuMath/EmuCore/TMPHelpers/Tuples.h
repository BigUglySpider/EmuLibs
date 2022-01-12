#ifndef EMU_CORE_TMP_TUPLES_H_INC_
#define EMU_CORE_TMP_TUPLES_H_INC_ 1

#include <tuple>

namespace EmuCore::TMP
{
	template<class Left_, class Right_>
	struct join_tuples
	{
		using type = std::tuple<Left_, Right_>;
	};
	template<class...LeftTupleArgs_, class Right_>
	struct join_tuples<std::tuple<LeftTupleArgs_...>, Right_>
	{
		using type = std::tuple<LeftTupleArgs_..., Right_>;
	};
	template<class Left_, class...RightTupleArgs_>
	struct join_tuples<Left_, std::tuple<RightTupleArgs_...>>
	{
		using type = std::tuple<Left_, RightTupleArgs_...>;
	};
	template<>
	struct join_tuples<std::tuple<>, std::tuple<>>
	{
		using type = std::tuple<>;
	};
	template<class...LeftTupleArgs_, class...RightTupleArgs_>
	struct join_tuples<std::tuple<LeftTupleArgs_...>, std::tuple<RightTupleArgs_...>>
	{
		using type = std::tuple<LeftTupleArgs_..., RightTupleArgs_...>;
	};
	template<class Left_, class Right_>
	using join_tuples_t = typename join_tuples<Left_, Right_>::type;

	template<std::size_t N_, typename T_>
	struct tuple_n
	{
	private:
		template<std::size_t N__>
		struct create_tuple_n
		{
			using left = typename create_tuple_n<N__ / 2>::type;
			using right = typename create_tuple_n<N__ / 2 + N__ % 2>::type;
			using type = typename join_tuples<left, right>::type;
		};
		template<>
		struct create_tuple_n<0>
		{
			using type = std::tuple<>;
		};
		template<>
		struct create_tuple_n<1>
		{
			using type = std::tuple<T_>;
		};

	public:
		using type = typename create_tuple_n<N_>::type;
	};
}

#endif
