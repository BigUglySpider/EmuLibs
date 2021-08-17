#ifndef EMU_CORE_COMPARATOR_FUNCTORS_H_INC_
#define EMU_CORE_COMPARATOR_FUNCTORS_H_INC_

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
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_)
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
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_)
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
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_)
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
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_)
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
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_)
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
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_)
		{
			return do_cmp_less_equal<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};
}

#endif
