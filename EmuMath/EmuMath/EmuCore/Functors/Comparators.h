#ifndef EMU_CORE_COMPARATOR_FUNCTORS_H_INC_
#define EMU_CORE_COMPARATOR_FUNCTORS_H_INC_ 1

#include <functional>

namespace EmuCore
{
	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_cmp_equal_to
	{
	private:
		std::equal_to<void> comparator_;

	public:
		constexpr do_cmp_equal_to()
		{
		}
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return comparator_(lhs_, rhs_);
		}
	};
	template<>
	struct do_cmp_equal_to<void, void>
	{
		constexpr do_cmp_equal_to()
		{
		}
		template<typename Lhs_, typename Rhs_>
		[[nodiscard]] constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_)
		{
			return do_cmp_equal_to<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_cmp_not_equal_to
	{
	private:
		std::not_equal_to<void> comparator_;

	public:
		constexpr do_cmp_not_equal_to()
		{
		}
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return comparator_(lhs_, rhs_);
		}
	};
	template<>
	struct do_cmp_not_equal_to<void, void>
	{
		constexpr do_cmp_not_equal_to()
		{
		}
		template<typename Lhs_, typename Rhs_>
		[[nodiscard]] constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_)
		{
			return do_cmp_not_equal_to<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_cmp_greater
	{
	private:
		std::greater<void> comparator_;

	public:
		constexpr do_cmp_greater()
		{
		}
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return comparator_(lhs_, rhs_);
		}
	};
	template<>
	struct do_cmp_greater<void, void>
	{
		constexpr do_cmp_greater()
		{
		}
		template<typename Lhs_, typename Rhs_>
		[[nodiscard]] constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_)
		{
			return do_cmp_greater<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_cmp_less
	{
	private:
		std::less<void> comparator_;

	public:
		constexpr do_cmp_less()
		{
		}
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return comparator_(lhs_, rhs_);
		}
	};
	template<>
	struct do_cmp_less<void, void>
	{
		constexpr do_cmp_less()
		{
		}
		template<typename Lhs_, typename Rhs_>
		[[nodiscard]] constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_)
		{
			return do_cmp_less<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_cmp_greater_equal
	{
	private:
		std::greater_equal<void> comparator_;

	public:
		constexpr do_cmp_greater_equal()
		{
		}
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return comparator_(lhs_, rhs_);
		}
	};
	template<>
	struct do_cmp_greater_equal<void, void>
	{
		constexpr do_cmp_greater_equal()
		{
		}
		template<typename Lhs_, typename Rhs_>
		[[nodiscard]] constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_)
		{
			return do_cmp_greater_equal<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_cmp_less_equal
	{
	private:
		std::less_equal<void> comparator_;

	public:
		constexpr do_cmp_less_equal()
		{
		}
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return comparator_(lhs_, rhs_);
		}
	};
	template<>
	struct do_cmp_less_equal<void, void>
	{
		constexpr do_cmp_less_equal()
		{
		}
		template<typename Lhs_, typename Rhs_>
		[[nodiscard]] constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_)
		{
			return do_cmp_less_equal<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename A_, typename B_ = A_>
	struct do_min
	{
		const do_cmp_less<A_, B_> cmp_;
		constexpr do_min() : cmp_()
		{
		}
		[[nodiscard]] constexpr inline A_ operator()(const A_& a_, const B_& b_) const
		{
			return cmp_(a_, b_) ? a_ : static_cast<A_>(b_);
		}
	};
	template<>
	struct do_min<void, void>
	{
		constexpr do_min()
		{
		}
		template<typename A_, typename B_>
		[[nodiscard]] constexpr inline auto operator()(A_&& a_, B_&& b_)
		{
			return do_min<A_, B_>()(std::forward<A_>(a_), std::forward<B_>(b_));
		}
	};

	template<typename A_, typename B_ = A_>
	struct do_max
	{
		const do_cmp_greater<A_, B_> cmp_;
		constexpr do_max() : cmp_()
		{
		}
		[[nodiscard]] constexpr inline A_ operator()(const A_& a_, const B_& b_) const
		{
			return cmp_(a_, b_) ? a_ : static_cast<A_>(b_);
		}
	};
	template<>
	struct do_max<void, void>
	{
		constexpr do_max()
		{
		}
		template<typename A_, typename B_>
		[[nodiscard]] constexpr inline auto operator()(A_&& a_, B_&& b_) const
		{
			return do_max<A_, B_>()(std::forward<A_>(a_), std::forward<B_>(b_));
		}
	};
}

#endif
