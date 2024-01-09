#ifndef EMU_CORE_COMPARATOR_FUNCTORS_H_INC_
#define EMU_CORE_COMPARATOR_FUNCTORS_H_INC_ 1

#include <functional>
#include "../TMPHelpers/OperatorChecks.h"
#include "../TMPHelpers/Values.h"

namespace EmuCore
{
	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_cmp_equal_to
	{
	private:
		using _cmp_type = std::equal_to<void>;
		static_assert
		(
			std::is_invocable_r_v<bool, _cmp_type, const Lhs_&, const Rhs_&>,
			"Invalid types for a default instantiation of EmuCore::do_cmp_equal_to: The types are not compatible when passed to std::equal_to<void> as const-reference arguments."
		);

	public:
		constexpr do_cmp_equal_to() noexcept
		{
		}
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_) const noexcept(std::is_nothrow_invocable_v<_cmp_type, const Lhs_&, const Rhs_&>)
		{
			return _cmp_type()(lhs_, rhs_);
		}
	};
	template<>
	struct do_cmp_equal_to<void, void>
	{
	private:
		template<class Lhs_, class Rhs_>
		using _cmp_template = EmuCore::do_cmp_equal_to<Lhs_, Rhs_>;

	public:
		constexpr do_cmp_equal_to() noexcept
		{
		}
		template<typename Lhs_, typename Rhs_>
		requires(std::is_default_constructible_v<_cmp_template<Lhs_, Rhs_>> && std::is_invocable_r_v<bool, _cmp_template<Lhs_, Rhs_>, const Lhs_&, const Rhs_&>)
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_) const noexcept(noexcept(_cmp_template<Lhs_, Rhs_>()(lhs_, rhs_)))
		{
			return _cmp_template<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_cmp_not_equal_to
	{
	private:
		using _cmp_type = std::not_equal_to<void>;
		static_assert
		(
			std::is_invocable_r_v<bool, _cmp_type, const Lhs_&, const Rhs_&>,
			"Invalid types for a default instantiation of EmuCore::do_cmp_not_equal_to: The types are not compatible when passed to std::not_equal_to<void> as const-reference arguments."
		);

	public:
		constexpr do_cmp_not_equal_to() noexcept
		{
		}
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_) const noexcept(std::is_nothrow_invocable_v<_cmp_type, const Lhs_&, const Rhs_&>)
		{
			return _cmp_type()(lhs_, rhs_);
		}
	};
	template<>
	struct do_cmp_not_equal_to<void, void>
	{
	private:
		template<class Lhs_, class Rhs_>
		using _cmp_template = EmuCore::do_cmp_not_equal_to<Lhs_, Rhs_>;

	public:
		constexpr do_cmp_not_equal_to() noexcept
		{
		}
		template<typename Lhs_, typename Rhs_>
		requires(std::is_default_constructible_v<_cmp_template<Lhs_, Rhs_>> && std::is_invocable_r_v<bool, _cmp_template<Lhs_, Rhs_>, const Lhs_&, const Rhs_&>)
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_) const noexcept(noexcept(_cmp_template<Lhs_, Rhs_>()(lhs_, rhs_)))
		{
			return _cmp_template<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_cmp_greater
	{
	private:
		using _cmp_type = std::greater<void>;
		static_assert
		(
			std::is_invocable_r_v<bool, _cmp_type, const Lhs_&, const Rhs_&>,
			"Invalid types for a default instantiation of EmuCore::do_cmp_greater: The types are not compatible when passed to std::greater<void> as const-reference arguments."
		);

	public:
		constexpr do_cmp_greater() noexcept
		{
		}
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_) const noexcept(std::is_nothrow_invocable_v<_cmp_type, const Lhs_&, const Rhs_&>)
		{
			return _cmp_type()(lhs_, rhs_);
		}
	};
	template<>
	struct do_cmp_greater<void, void>
	{
	private:
		template<class Lhs_, class Rhs_>
		using _cmp_template = EmuCore::do_cmp_greater<Lhs_, Rhs_>;

	public:
		constexpr do_cmp_greater() noexcept
		{
		}
		template<typename Lhs_, typename Rhs_>
		requires(std::is_default_constructible_v<_cmp_template<Lhs_, Rhs_>> && std::is_invocable_r_v<bool, _cmp_template<Lhs_, Rhs_>, const Lhs_&, const Rhs_&>)
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_) const noexcept(noexcept(_cmp_template<Lhs_, Rhs_>()(lhs_, rhs_)))
		{
			return _cmp_template<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_cmp_less
	{
	private:
		using _cmp_type = std::less<void>;
		static_assert
		(
			std::is_invocable_r_v<bool, _cmp_type, const Lhs_&, const Rhs_&>,
			"Invalid types for a default instantiation of EmuCore::do_cmp_less: The types are not compatible when passed to std::less<void> as const-reference arguments."
		);

	public:
		constexpr do_cmp_less() noexcept
		{
		}
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_) const noexcept(std::is_nothrow_invocable_v<_cmp_type, const Lhs_&, const Rhs_&>)
		{
			return _cmp_type()(lhs_, rhs_);
		}
	};
	template<>
	struct do_cmp_less<void, void>
	{
	private:
		template<class Lhs_, class Rhs_>
		using _cmp_template = EmuCore::do_cmp_less<Lhs_, Rhs_>;

	public:
		constexpr do_cmp_less() noexcept
		{
		}
		template<typename Lhs_, typename Rhs_>
		requires(std::is_default_constructible_v<_cmp_template<Lhs_, Rhs_>> && std::is_invocable_r_v<bool, _cmp_template<Lhs_, Rhs_>, const Lhs_&, const Rhs_&>)
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_) const noexcept(noexcept(_cmp_template<Lhs_, Rhs_>()(lhs_, rhs_)))
		{
			return _cmp_template<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_cmp_greater_equal
	{
	private:
		using _cmp_type = std::greater_equal<void>;
		static_assert
		(
			std::is_invocable_r_v<bool, _cmp_type, const Lhs_&, const Rhs_&>,
			"Invalid types for a default instantiation of EmuCore::do_cmp_greater_equal: The types are not compatible when passed to std::greater_equal<void> as const-reference arguments."
		);

	public:
		constexpr do_cmp_greater_equal() noexcept
		{
		}
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_) const noexcept(std::is_nothrow_invocable_v<_cmp_type, const Lhs_&, const Rhs_&>)
		{
			return _cmp_type()(lhs_, rhs_);
		}
	};
	template<>
	struct do_cmp_greater_equal<void, void>
	{
	private:
		template<class Lhs_, class Rhs_>
		using _cmp_template = EmuCore::do_cmp_greater_equal<Lhs_, Rhs_>;

	public:
		constexpr do_cmp_greater_equal() noexcept
		{
		}
		template<typename Lhs_, typename Rhs_>
		requires(std::is_default_constructible_v<_cmp_template<Lhs_, Rhs_>> && std::is_invocable_r_v<bool, _cmp_template<Lhs_, Rhs_>, const Lhs_&, const Rhs_&>)
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_) const noexcept(noexcept(_cmp_template<Lhs_, Rhs_>()(lhs_, rhs_)))
		{
			return _cmp_template<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_cmp_less_equal
	{
	private:
		using _cmp_type = std::less_equal<void>;
		static_assert
		(
			std::is_invocable_r_v<bool, _cmp_type, const Lhs_&, const Rhs_&>,
			"Invalid types for a default instantiation of EmuCore::do_cmp_less_equal: The types are not compatible when passed to std::less_equal<void> as const-reference arguments."
		);

	public:
		constexpr do_cmp_less_equal() noexcept
		{
		}
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_) const noexcept(std::is_nothrow_invocable_v<_cmp_type, const Lhs_&, const Rhs_&>)
		{
			return _cmp_type()(lhs_, rhs_);
		}
	};
	template<>
	struct do_cmp_less_equal<void, void>
	{
	private:
		template<class Lhs_, class Rhs_>
		using _cmp_template = EmuCore::do_cmp_less_equal<Lhs_, Rhs_>;

	public:
		constexpr do_cmp_less_equal() noexcept
		{
		}
		template<typename Lhs_, typename Rhs_>
		requires(std::is_default_constructible_v<_cmp_template<Lhs_, Rhs_>> && std::is_invocable_r_v<bool, _cmp_template<Lhs_, Rhs_>, const Lhs_&, const Rhs_&>)
		[[nodiscard]] constexpr inline bool operator()(const Lhs_& lhs_, const Rhs_& rhs_) const noexcept(noexcept(_cmp_template<Lhs_, Rhs_>()(lhs_, rhs_)))
		{
			return _cmp_template<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename A_, typename B_ = A_, typename Out_ = EmuCore::TMP::remove_ref_cv_t<A_>>
	struct do_min
	{
	private:
		using _cmp_less_equal = EmuCore::do_cmp_less_equal<A_, B_>;
		[[nodiscard]] static constexpr inline bool _is_noexcept() noexcept
		{
			return
			(
				(std::is_nothrow_invocable_v<_cmp_less_equal, const A_&, const B_&>) &&
				(
					(std::is_constructible_v<Out_, const A_&> && std::is_nothrow_constructible_v<Out_, const A_&>) ||
					(EmuCore::TMP::is_static_castable_v<const A_&, Out_> && std::is_nothrow_convertible_v<const A_&, Out_>)
				) &&
				(
					(std::is_constructible_v<Out_, const B_&> && std::is_nothrow_constructible_v<Out_, const B_&>) ||
					(EmuCore::TMP::is_static_castable_v<const B_&, Out_> && std::is_nothrow_convertible_v<const B_&, Out_>)
				)
			);
		}

	public:
		constexpr do_min() noexcept
		{
		}
		[[nodiscard]] constexpr inline Out_ operator()(const A_& a_, const B_& b_) const noexcept(_is_noexcept())
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
	private:
		template<class A_, class B_, class Out_>
		using _op_template = EmuCore::do_min<A_, B_, typename std::conditional<std::is_void_v<Out_>, A_, Out_>::type>;

	public:
		constexpr do_min() noexcept
		{
		}
		template<typename Out_ = void, typename A_, typename B_>
		requires(std::is_default_constructible_v<_op_template<A_, B_, Out_>> && std::is_invocable_v<_op_template<A_, B_, Out_>, const A_&, const B_&>)
		[[nodiscard]] constexpr inline decltype(auto) operator()(const A_& a_, const B_& b_) const noexcept(noexcept(_op_template<A_, B_, Out_>()(a_, b_)))
		{
			return _op_template<A_, B_, Out_>()(a_, b_);
		}
	};
	template<typename Out_>
	struct do_min<void, void, Out_>
	{
	private:
		template<class A_, class B_>
		using _op_template = EmuCore::do_min<A_, B_, Out_>;

	public:
		constexpr do_min() noexcept
		{
		}
		template<typename A_, typename B_>
		requires(std::is_default_constructible_v<_op_template<A_, B_>> && std::is_invocable_v<_op_template<A_, B_>, const A_&, const B_&>)
		[[nodiscard]] constexpr inline decltype(auto) operator()(const A_& a_, const B_& b_) const noexcept(noexcept(_op_template<A_, B_>()(a_, b_)))
		{
			return _op_template<A_, B_>()(a_, b_);
		}
	};

	template<typename A_, typename B_ = A_, typename Out_ = EmuCore::TMP::remove_ref_cv_t<A_>>
	struct do_max
	{
	private:
		using _cmp_greater_equal = EmuCore::do_cmp_greater_equal<A_, B_>;
		[[nodiscard]] static constexpr inline bool _is_noexcept() noexcept
		{
			return
			(
				(std::is_nothrow_invocable_v<_cmp_greater_equal, const A_&, const B_&>) &&
				(
					(std::is_constructible_v<Out_, const A_&> && std::is_nothrow_constructible_v<Out_, const A_&>) ||
					(EmuCore::TMP::is_static_castable_v<const A_&, Out_> && std::is_nothrow_convertible_v<const A_&, Out_>)
				) &&
				(
					(std::is_constructible_v<Out_, const B_&> && std::is_nothrow_constructible_v<Out_, const B_&>) ||
					(EmuCore::TMP::is_static_castable_v<const B_&, Out_> && std::is_nothrow_convertible_v<const B_&, Out_>)
				)
			);
		}

	public:
		constexpr do_max() noexcept
		{
		}
		[[nodiscard]] constexpr inline Out_ operator()(const A_& a_, const B_& b_) const noexcept(_is_noexcept())
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
	private:
		template<class A_, class B_, class Out_>
		using _op_template = EmuCore::do_max<A_, B_, typename std::conditional<std::is_void_v<Out_>, A_, Out_>::type>;

	public:
		constexpr do_max() noexcept
		{
		}
		template<typename Out_ = void, typename A_, typename B_>
		requires(std::is_default_constructible_v<_op_template<A_, B_, Out_>> && std::is_invocable_v<_op_template<A_, B_, Out_>, const A_&, const B_&>)
		[[nodiscard]] constexpr inline decltype(auto) operator()(const A_& a_, const B_& b_) const noexcept(noexcept(_op_template<A_, B_, Out_>()(a_, b_)))
		{
			return _op_template<A_, B_, Out_>()(a_, b_);
		}
	};
	template<typename Out_>
	struct do_max<void, void, Out_>
	{
	private:
		template<class A_, class B_>
		using _op_template = EmuCore::do_max<A_, B_, Out_>;

	public:
		constexpr do_max() noexcept
		{
		}
		template<typename A_, typename B_>
		requires(std::is_default_constructible_v<_op_template<A_, B_>> && std::is_invocable_v<_op_template<A_, B_>, const A_&, const B_&>)
		[[nodiscard]] constexpr inline decltype(auto) operator()(const A_& a_, const B_& b_) const noexcept(noexcept(_op_template<A_, B_>()(a_, b_)))
		{
			return _op_template<A_, B_>()(a_, b_);
		}
	};
}

#endif
