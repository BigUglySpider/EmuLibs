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
		[[nodiscard]] static constexpr inline auto _type_finder()
		{
			if constexpr (N_ == 0)
			{
				return std::tuple<>();
			}
			else if constexpr (N_ == 1)
			{
				return std::tuple<T_>();
			}
			else
			{
				constexpr std::size_t half_n = N_ / 2;
				using left = typename tuple_n<half_n, T_>::type;
				using right = typename tuple_n<half_n + N_ % 2, T_>::type;
				return typename join_tuples<left, right>::type();
			}
		}

	public:
		using type = decltype(_type_finder());
	};
	template<std::size_t N_, typename T_>
	using tuple_n_t = typename tuple_n<N_, T_>::type;
}

#endif
