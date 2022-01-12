#ifndef EMU_CORE_COMPARATOR_FUNCTORS_H_INC_
#define EMU_CORE_COMPARATOR_FUNCTORS_H_INC_ 1

#include <functional>
#include "../TMPHelpers/OperatorChecks.h"

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

	template<typename A_, typename B_ = A_, typename Out_ = EmuCore::TMP::remove_ref_cv_t<A_>>
	struct do_min
	{
	private:
		using _cmp_less_equal = EmuCore::do_cmp_less_equal<A_, B_>;

	public:
		constexpr do_min()
		{
		}
		[[nodiscard]] constexpr inline Out_ operator()(const A_& a_, const B_& b_) const
		{
			if (_cmp_less_equal()(a_, b_))
			{
				// min: a_
				if constexpr (std::is_constructible_v<Out_, const A_&>)
				{
					return Out_(a_);
				}
				else if constexpr (EmuCore::TMP::is_static_castable_v<const A_&, Out_>)
				{
					return static_cast<Out_>(a_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Out_>(),
						"Attempted to get the minimum of two values via EmuCore::do_min, but the provided type A_ cannot be used to create the desired Out_ type."
					);
				}
			}
			else
			{
				// min: b_
				if constexpr (std::is_constructible_v<Out_, const B_&>)
				{
					return Out_(b_);
				}
				else if constexpr (EmuCore::TMP::is_static_castable_v<const B_&, Out_>)
				{
					return static_cast<Out_>(b_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Out_>(),
						"Attempted to get the minimum of two values via EmuCore::do_min, but the provided type B_ cannot be used to create the desired Out_ type."
					);
				}
			}
		}
	};
	template<>
	struct do_min<void, void, void>
	{
		constexpr do_min()
		{
		}
		template<typename A_, typename B_, typename Out_ = EmuCore::TMP::remove_ref_cv_t<A_>>
		[[nodiscard]] constexpr inline std::invoke_result_t<do_min<A_, B_, Out_>, const A_&, const B_&> operator()(const A_& a_, const B_& b_)
		{
			return do_min<A_, B_, Out_>()(a_, b_);
		}
	};
	template<typename Out_>
	struct do_min<void, void, Out_>
	{
		constexpr do_min()
		{
		}
		template<typename A_, typename B_>
		[[nodiscard]] constexpr inline std::invoke_result_t<do_min<A_, B_, Out_>, const A_&, const B_&> operator()(const A_& a_, const B_& b_)
		{
			return do_min<A_, B_, Out_>()(a_, b_);
		}
	};

	template<typename A_, typename B_ = A_, typename Out_ = EmuCore::TMP::remove_ref_cv_t<A_>>
	struct do_max
	{
	private:
		using _cmp_greater_equal = EmuCore::do_cmp_greater_equal<A_, B_>;

	public:
		constexpr do_max()
		{
		}
		[[nodiscard]] constexpr inline Out_ operator()(const A_& a_, const B_& b_) const
		{
			if (_cmp_greater_equal()(a_, b_))
			{
				// max: a_
				if constexpr (std::is_constructible_v<Out_, const A_&>)
				{
					return Out_(a_);
				}
				else if constexpr (EmuCore::TMP::is_static_castable_v<const A_&, Out_>)
				{
					return static_cast<Out_>(a_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Out_>(),
						"Attempted to get the maximum of two values via EmuCore::do_min, but the provided type A_ cannot be used to create the desired Out_ type."
					);
				}
			}
			else
			{
				// max: b_
				if constexpr (std::is_constructible_v<Out_, const B_&>)
				{
					return Out_(b_);
				}
				else if constexpr (EmuCore::TMP::is_static_castable_v<const B_&, Out_>)
				{
					return static_cast<Out_>(b_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Out_>(),
						"Attempted to get the maximum of two values via EmuCore::do_min, but the provided type B_ cannot be used to create the desired Out_ type."
					);
				}
			}
		}
	};
	template<>
	struct do_max<void, void, void>
	{
		constexpr do_max()
		{
		}
		template<typename A_, typename B_, typename Out_ = EmuCore::TMP::remove_ref_cv_t<A_>>
		[[nodiscard]] constexpr inline std::invoke_result_t<do_max<A_, B_, Out_>, const A_&, const B_&> operator()(const A_& a_, const B_& b_)
		{
			return do_max<A_, B_, Out_>()(a_, b_);
		}
	};
	template<typename Out_>
	struct do_max<void, void, Out_>
	{
		constexpr do_max()
		{
		}
		template<typename A_, typename B_>
		[[nodiscard]] constexpr inline std::invoke_result_t<do_max<A_, B_, Out_>, const A_&, const B_&> operator()(const A_& a_, const B_& b_)
		{
			return do_max<A_, B_, Out_>()(a_, b_);
		}
	};
}

#endif
