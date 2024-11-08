#ifndef EMU_CORE_COLLECTIONS_RANGE_HPP_INC_
#define EMU_CORE_COLLECTIONS_RANGE_HPP_INC_ 1

#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "../CommonPreprocessor/Warning.h"
#include "../Functors/Comparators.h"

namespace EmuCore
{
	template<class T>
	struct range_diff
	{
	private:
		[[nodiscard]] static constexpr auto _find_diff_type() noexcept
		{
			if constexpr (std::is_arithmetic_v<typename std::remove_cvref<T>::type> || std::is_enum_v<typename std::remove_cvref<T>::type>)
			{
				if constexpr (std::is_floating_point_v<typename std::remove_cvref<T>::type>)
				{
					return typename std::remove_cvref<T>::type{};
				}
				else
				{
					return typename std::make_signed<typename std::remove_cvref<T>::type>::type{};
				}
			}
			else
			{
				return std::ptrdiff_t{};
			}
		}

	public:
		using type = decltype(_find_diff_type());
	};

	template<typename T>
	class default_range_iterator
	{
	public:
		using difference_type = typename range_diff<T>::type;
		using value_type = typename std::remove_cvref<T>::type;
		using reference = value_type; // This iterator produces values on demand and so cannot provide references outside of operator*
		using iterator_category = std::random_access_iterator_tag;

		constexpr default_range_iterator() noexcept(std::is_nothrow_default_constructible_v<value_type>&& std::is_nothrow_default_constructible_v<difference_type>) :
			value{},
			increment{},
			forward_moving{ true }
		{
		}

		constexpr default_range_iterator(const default_range_iterator<T>& to_copy) noexcept(std::is_nothrow_copy_constructible_v<value_type>&& std::is_nothrow_copy_constructible_v<difference_type>) :
			value{ to_copy.value },
			increment{ to_copy.increment },
			forward_moving{ to_copy.forward_moving }
		{
		}

		constexpr default_range_iterator(default_range_iterator<T>&& to_move) noexcept(std::is_nothrow_move_constructible_v<value_type>&& std::is_nothrow_move_constructible_v<difference_type>) :
			value{ std::move(to_move.value) },
			increment{ std::move(to_move.increment) },
			forward_moving{ std::move(to_move.forward_moving) }
		{
		}

		constexpr default_range_iterator(const value_type& value_, const difference_type& increment_) noexcept(std::is_nothrow_copy_constructible_v<value_type>&& std::is_nothrow_copy_constructible_v<difference_type>) :
			value{ value_ },
			increment{ increment_ },
			forward_moving{ increment_ >= difference_type{} }
		{
		}

	private:
		constexpr default_range_iterator(const value_type& value_, const difference_type& increment_, const bool forward_moving_) noexcept(std::is_nothrow_copy_constructible_v<value_type>&& std::is_nothrow_copy_constructible_v<difference_type>) :
			value{ value_ },
			increment{ increment_ },
			forward_moving{ forward_moving_ }
		{
		}

		[[nodiscard]] constexpr bool _epsilon_eq(const value_type lhs, const value_type rhs) const noexcept
		requires(std::is_floating_point_v<typename std::remove_cvref<value_type>::type>)
		{
			value_type epsilon_multiplier = (increment < value_type{} ? -increment : increment) * value_type{ 0.5f };
			epsilon_multiplier /= std::numeric_limits<value_type>::epsilon();
			return EmuCore::do_cmp_near_equal<value_type>{}(lhs, rhs, std::numeric_limits<value_type>::epsilon() * epsilon_multiplier);
		}

	public:
		constexpr default_range_iterator<T>& operator++() noexcept
		{
			value += increment;
			return *this;
		}
		constexpr default_range_iterator<T> operator++(int) noexcept(std::is_nothrow_copy_constructible_v<value_type> && std::is_nothrow_copy_constructible_v<difference_type>)
		{
			default_range_iterator<T> copied{ *this };
			value += increment;
			return copied;
		}

		constexpr default_range_iterator<T>& operator--() noexcept
		{
			value -= increment;
			return *this;
		}
		constexpr default_range_iterator<T> operator--(int) noexcept(std::is_nothrow_copy_constructible_v<value_type>&& std::is_nothrow_copy_constructible_v<difference_type>)
		{
			default_range_iterator<T> copied{ *this };
			value -= increment;
			return copied;
		}

		constexpr default_range_iterator<T>& operator+=(const difference_type& num_increments) noexcept
		{
			value += (increment * num_increments);
			return *this;
		}

		[[nodiscard]] constexpr default_range_iterator<T> operator+(const difference_type& num_increments) const noexcept
		{
			return default_range_iterator{ value + (increment * num_increments), increment, forward_moving };
		}
		friend default_range_iterator<T> operator+(const difference_type& num_increments, const default_range_iterator<T>& it) noexcept;

		constexpr default_range_iterator<T>& operator-=(const difference_type& num_increments) noexcept
		{
			value -= (increment * num_increments);
			return *this;
		}

		[[nodiscard]] constexpr default_range_iterator<T> operator-(const difference_type& num_increments) const noexcept
		{
			return default_range_iterator{ value - (increment * num_increments), increment, forward_moving };
		}
		friend default_range_iterator<T> operator-(const difference_type& num_increments, const default_range_iterator<T>& it) noexcept;

		[[nodiscard]] constexpr difference_type operator-(const default_range_iterator<T>& rhs_iterator) const noexcept
		{
			return (rhs_iterator.value - value) / increment;
		}

		[[nodiscard]] constexpr bool operator==(const default_range_iterator<T>& rhs_iterator) const noexcept
		{
			if constexpr (std::is_floating_point_v<typename std::remove_cvref<value_type>::type>)
			{
				return value == rhs_iterator.value || _epsilon_eq(value, rhs_iterator.value);
			}
			else
			{
				return value == rhs_iterator.value;
			}
		}

		[[nodiscard]] constexpr bool operator!=(const default_range_iterator<T>& rhs_iterator) const noexcept
		{
			if constexpr (std::is_floating_point_v<typename std::remove_cvref<value_type>::type>)
			{
				return !(this->operator==(rhs_iterator));
			}
			else
			{
				return value != rhs_iterator.value;
			}
		}

		[[nodiscard]] constexpr bool operator<(const default_range_iterator<T>& rhs_iterator) const noexcept
		{
			return (forward_moving && value < rhs_iterator.value) || (!forward_moving && value > rhs_iterator.value);
		}

		[[nodiscard]] constexpr bool operator>(const default_range_iterator<T>& rhs_iterator) const noexcept
		{
			return (forward_moving && value > rhs_iterator.value) || (!forward_moving && value < rhs_iterator.value);
		}

		[[nodiscard]] constexpr bool operator<=(const default_range_iterator<T>& rhs_iterator) const noexcept
		{
			if constexpr (std::is_floating_point_v<typename std::remove_cvref<value_type>::type>)
			{
				// FP will divert to operator== if everything else fails to ensure an epsilon margin of error is accounted for
				return (forward_moving && value <= rhs_iterator.value) || (!forward_moving && value >= rhs_iterator.value) || this->operator==(rhs_iterator);
			}
			else
			{
				return (forward_moving && value <= rhs_iterator.value) || (!forward_moving && value >= rhs_iterator.value);
			}
		}

		[[nodiscard]] constexpr bool operator>=(const default_range_iterator<T>& rhs_iterator) const noexcept
		{
			if constexpr (std::is_floating_point_v<typename std::remove_cvref<value_type>::type>)
			{
				// FP will divert to operator== if everything else fails to ensure an epsilon margin of error is accounted for
				return (forward_moving && value >= rhs_iterator.value) || (!forward_moving && value <= rhs_iterator.value) || this->operator==(rhs_iterator);
			}
			else
			{
				return (forward_moving && value >= rhs_iterator.value) || (!forward_moving && value <= rhs_iterator.value);
			}
		}

		[[nodiscard]] constexpr value_type operator[](const difference_type& num_increments) const noexcept
		{
			return value + (num_increments * increment);
		}

		[[nodiscard]] constexpr const value_type& operator*() const noexcept
		{
			return value;
		}

	private:
		value_type value;
		difference_type increment;
		bool forward_moving;
	};
	template<class T>
	[[nodiscard]] default_range_iterator<T> operator+(const typename default_range_iterator<T>::difference_type& num_increments, default_range_iterator<T>& it) noexcept
	{
		return default_range_iterator<T>{ (it.increment * num_increments) + it.value, it.increment, it.forward_moving };
	}
	template<class T>
	[[nodiscard]] default_range_iterator<T> operator-(const typename default_range_iterator<T>::difference_type& num_increments, default_range_iterator<T>& it) noexcept
	{
		return default_range_iterator<T>{ (it.increment * num_increments) - it.value, it.increment, it.forward_moving };
	}

	/// <summary>
	/// <para> Template representing an on-demand range of values moving either forwards or backwards. </para>
	/// <para> Designed to be used like any STL collection for iteration, without the need for memory consumption of each value within the entire range. </para>
	/// <para>
	///		Note that behaviour may be erratic for floating-point ranges due to floating-point rounding errors.
	///		Do not assume any values within a floating-point range are guaranteed,
	///		and do not expect identical values to appear when traversing the same floating-point range in reverse. 
	///		Due to this erratic behaviour, `size()` is not available for floating-point ranges.
	///		These limitations do not apply to integer ranges.
	/// </para>
	/// </summary>
	/// <param name="T">Type - preferably arithmetic - to represent a range of.</param>
	template<typename T>
	class Range
	{
#pragma region TYPES
	private:		
		using diff_type = typename range_diff<T>::type;

	public:
		using iterator = default_range_iterator<T>; // Iterator to allow this range to be consistently iterated as any STL collection would
		using const_iterator = iterator; // `iterator` is immutable, so exactly the same type
		using reverse_iterator = iterator; // `iterator` is simply constructed differently for reverse iteration, so exactly the same type
		using const_reverse_iterator = reverse_iterator; // `reverse_iterator` is immutable, so exactly the same type
#pragma endregion

#pragma region STATIC_VALIDITY_CHECKS
	private:
		template<bool References, template<class To, class From> class Check, class BeginIn, class EndIn, class IncrementIn>
		[[nodiscard]] static constexpr bool _static_validity_check() noexcept
		{
			if constexpr (References)
			{
				return
				(
					Check<T&, BeginIn>::value &&
					Check<T&, EndIn>::value &&
					Check<diff_type&, IncrementIn>::value
				);
			}
			else
			{
				return
				(
					Check<T&, BeginIn>::value &&
					Check<T&, EndIn>::value &&
					Check<diff_type&, IncrementIn>::value
				);
			}
		}

		template<bool Noexcept>
		[[nodiscard]] static constexpr bool is_copy_constructible() noexcept
		{
			if constexpr (Noexcept)
			{
				return _static_validity_check<false, std::is_constructible, const T&, const T&, const diff_type&>();
			}
			else
			{
				return _static_validity_check<false, std::is_nothrow_constructible, const T&, const T&, const diff_type&>();
			}
		}

		template<bool Noexcept>
		[[nodiscard]] static constexpr bool is_move_constructible() noexcept
		{
			if constexpr (Noexcept)
			{
				return _static_validity_check<false, std::is_constructible, T&&, T&&, diff_type&&>();
			}
			else
			{
				return _static_validity_check<false, std::is_nothrow_constructible, T&&, T&&, diff_type&&>();
			}
		}

		template<bool Noexcept>
		[[nodiscard]] static constexpr bool is_copy_assignable() noexcept
		{
			if constexpr (Noexcept)
			{
				return _static_validity_check<true, std::is_assignable, const T&, const T&, const diff_type&>();
			}
			else
			{
				return _static_validity_check<true, std::is_nothrow_assignable, const T&, const T&, const diff_type&>();
			}
		}

		template<bool Noexcept>
		[[nodiscard]] static constexpr bool is_move_assignable() noexcept
		{
			if constexpr (Noexcept)
			{
				return _static_validity_check<true, std::is_assignable, T&&, T&&, diff_type&&>();
			}
			else
			{
				return _static_validity_check<true, std::is_nothrow_assignable, T&&, T&&, diff_type&&>();
			}
		}

		template<bool Noexcept, class Pair>
		[[nodiscard]] static constexpr bool is_pair_assignable() noexcept
		{
			using std::get;
			return
			(
				std::is_assignable_v<T&, decltype(get<0>(std::declval<Pair>()))> &&
				std::is_assignable_v<T&, decltype(get<1>(std::declval<Pair>()))>
			);
		}
#pragma endregion

#pragma region CONSTRUCTORS
	private:
		struct _no_validation_needed {};

		/// <summary>
		/// <para> Private constructor used to create a new range without validation when it is guaranteed that validation is not required. </para>
		/// </summary>
		constexpr Range(const T& begin_, const T& end_, const diff_type& increment_, [[maybe_unused]] _no_validation_needed) :
			range_begin{ begin_ },
			range_end{ end_ },
			increment{ increment_ }
		{
		}

	public:
		Range() = delete;

		constexpr Range(const Range<T>& to_copy) noexcept(is_copy_constructible<true>())
		requires(is_copy_constructible<false>()) :
			range_begin(to_copy.range_begin),
			range_end(to_copy.range_end),
			increment(to_copy.increment)
		{
		}

		constexpr Range(Range<T>&& to_move) noexcept(is_move_constructible<true>())
		requires(is_move_constructible<false>()) :
			range_begin(std::move(to_move.range_begin)),
			range_end(std::move(to_move.range_end)),
			increment(std::move(to_move.increment))
		{
		}

		/// <summary>
		/// <para> Constructs a range that starts at 0 (represented by `T{}`) and increments one value at a time. </para>
		/// <para> If `end_` is below the default value provided by `T{}` (likely 0), the constructed range will represent a reverse range. </para>
		/// </summary>
		/// <param name="end_">The exclusive value that marks the end of the range.</param>
		constexpr Range(const T& end_) noexcept(std::is_nothrow_default_constructible_v<T> && std::is_nothrow_copy_constructible_v<T>)
		requires(std::is_default_constructible_v<T> && std::is_copy_constructible_v<T>) :
			range_begin{},
			range_end{ end_ }
		{
			_set_range_info<false>();
		}

		/// <summary>
		/// <para> Constructs a range that increments one value at a time. </para>
		/// <para> If `begin_` is greater than `end_`, the constructed range will represent a reverse range. </para>
		/// </summary>
		/// <param name="begin_">The inclusive value at which the range begins.</param>
		/// <param name="end_">The exclusive value that marks the end of the range.</param>
		constexpr Range(const T& begin_, const T& end_) noexcept(std::is_nothrow_copy_constructible_v<T>)
		requires(std::is_copy_constructible_v<T>) :
			range_begin{ begin_ },
			range_end{ end_ }
		{
			_set_range_info<false>();
		}

		/// <summary>
		/// <para> Constructs a fully custom range. </para>
		/// <para> If `begin_` is greater than `end_`, the constructed range will represent a reverse range. </para>
		/// </summary>
		/// <param name="begin_">The inclusive value at which the range begins.</param>
		/// <param name="end_">The exclusive value that marks the end of the range.</param>
		/// <param name="increment_">
		///		The amount that each iteration increments by.
		///		If `begin_` is less-than-or-equal to `end_`, this must be positive.
		///		If `begin_` is greater than `end_`, this must be negative.
		///     Cannot be 0 (represented by `diff_type{}`).
		/// </param>
		constexpr Range(const T& begin_, const T& end_, const diff_type& increment_)
		requires(std::is_copy_constructible_v<T> && std::is_copy_constructible_v<diff_type>) :
			range_begin{ begin_ },
			range_end{ end_ },
			increment{ increment_ }
		{
			_set_range_info<true>();
		}
#pragma endregion

#pragma region ASSIGNMENT_OPERATORS
	public:
		constexpr Range<T>& operator=(const Range<T>& rhs) noexcept(is_copy_assignable<true>())
		requires(is_copy_assignable<false>())
		{
			range_begin = rhs.range_begin;
			range_end   = rhs.range_end;
			increment   = rhs.increment;
			return *this;
		}

		constexpr Range<T>& operator=(Range<T>&& rhs) noexcept(is_move_assignable<true>())
		requires(is_move_assignable<false>())
		{
			range_begin = std::move(rhs.range_begin);
			range_end   = std::move(rhs.range_end);
			increment   = std::move(rhs.increment);
			return *this;
		}

		template<class Begin, class End>
		requires(is_pair_assignable<false, const std::pair<Begin, End>&>())
		constexpr Range<T>& operator=(const std::pair<Begin, End>& new_range) noexcept(is_pair_assignable<true, const std::pair<Begin, End>&>())
		{
			using std::get;
			range_begin = get<0>(new_range);
			range_end = get<1>(new_range);
			_set_range_info<false>();
		}

		template<class Begin, class End>
		requires(is_pair_assignable<false, std::pair<Begin, End>&>())
		constexpr Range<T>& operator=(std::pair<Begin, End>& new_range) noexcept(is_pair_assignable<true, std::pair<Begin, End>&>())
		{
			using std::get;
			range_begin = get<0>(new_range);
			range_end = get<1>(new_range);
			_set_range_info<false>();
		}

		template<class Begin, class End>
		requires(is_pair_assignable<false, std::pair<Begin, End>&&>())
		constexpr Range<T>& operator=(std::pair<Begin, End>&& new_range) noexcept(is_pair_assignable<true, std::pair<Begin, End>&&>())
		{
			EMU_CORE_MSVC_PUSH_WARNING_STACK;
			EMU_CORE_MSVC_DISABLE_WARNING(EMU_CORE_WARNING_BAD_MOVE);
			using std::get;
			range_begin = get<0>(std::move(new_range));
			range_end = get<1>(std::move(new_range));
			EMU_CORE_MSVC_POP_WARNING_STACK;
			_set_range_info<false>();
		}
#pragma endregion

#pragma region SETTERS
	private:
		template<bool CustomIncrement>
		constexpr void _set_range_info() noexcept(!CustomIncrement)
		{
			if (range_begin <= range_end)
			{
				// Forward range
				if constexpr (CustomIncrement)
				{
					if (increment <= diff_type{})
					{
						throw std::invalid_argument{ "Invalid increment provided to a range: The range is forward-moving, but the custom increment is negative or 0. Forward-moving ranges require positive non-zero increments" };
					}
				}
				else
				{
					increment = diff_type{ 1 };
				}
			}
			else
			{
				// Backward range
				if constexpr (CustomIncrement)
				{
					if (increment >= diff_type{})
					{
						throw std::invalid_argument{ "Invalid increment provided to a range: The range is backward-moving, but the custom increment is positive or 0. Backward-moving ranges require negative non-zero increments" };
					}
				}
				else
				{
					increment = diff_type{ -1 };
				}
			}
		}

	public:
		/// <summary>
		/// <para> Sets this range as if newly constructed with the provided arguments. </para>
		/// <para> See the matching constructor for further details. </para>
		/// </summary>
		constexpr void Set(const T& end_) noexcept(std::is_nothrow_copy_assignable_v<T&> && std::is_nothrow_move_assignable_v<T&> && std::is_nothrow_default_constructible_v<T>)
		requires(std::is_copy_assignable_v<T&> && std::is_move_assignable_v<T&> && std::is_default_constructible_v<T>)
		{
			range_begin = T{};
			range_end = end_;
			_set_range_info<false>();
		}

		/// <summary>
		/// <para> Sets this range as if newly constructed with the provided arguments. </para>
		/// <para> See the matching constructor for further details. </para>
		/// </summary>
		constexpr void Set(const T& begin_, const T& end_) noexcept(std::is_nothrow_copy_assignable_v<T&>)
		requires(std::is_copy_assignable_v<T&>)
		{
			range_begin = begin_;
			range_end = end_;
			_set_range_info<false>();
		}

		/// <summary>
		/// <para> Sets this range as if newly constructed with the provided arguments. </para>
		/// <para> See the matching constructor for further details. </para>
		/// </summary>
		constexpr void Set(const T& begin_, const T& end_, const diff_type& increment_)
		requires(std::is_copy_assignable_v<T&> && std::is_copy_assignable_v<diff_type&>)
		{
			range_begin = begin_;
			range_end = end_;
			increment = increment_;
			_set_range_info<true>();
		}
#pragma endregion

#pragma region MUTATIONS
	public:
		/// <summary>
		/// <para> Creates a range representing the reversed form of this range. </para>
		/// <para> Note that floating-point ranges may deteriorate slightly due to rounding errors. </para>
		/// <para> Note that if only iterators are required and only once, the same results can be achieved with `rbegin` and `rend` without needing a new range. </para>
		/// </summary>
		/// <returns>A new range representing the reversed form of this range.</returns>
		[[nodiscard]] constexpr Range<T> Reverse() const
		noexcept(std::is_nothrow_copy_constructible_v<T> && std::is_nothrow_copy_constructible_v<diff_type> && noexcept(std::declval<const T&>() - std::declval<const diff_type&>()) && noexcept(-std::declval<const diff_type&>()))
		requires(std::is_copy_constructible_v<T> && std::is_copy_constructible_v<diff_type>)
		{
			return Range<T>{range_end - increment, range_begin - increment, -increment, _no_validation_needed{}};
		}

		/// <summary>
		/// <para> Update this range to be the representation of its reversed self. </para>
		/// <para>
		///		Although this may be used repeatedly to switch between reversed forms,
		///     note that floating-point ranges may deteriorate slightly due to rounding errors.
		/// </para>
		/// <para> Note that if only iterators are required and only once, the same results can be achieved with `rbegin` and `rend` without needing to update this range. </para>
		/// </summary>
		/// <returns>Reference to this range.</returns>
		constexpr Range<T>& AssignReversal()
		noexcept(std::is_nothrow_copy_assignable_v<T&> && std::is_nothrow_move_assignable_v<T&> && noexcept(std::declval<T&>() - std::declval<diff_type&>()) && noexcept(-std::declval<diff_type&>()))
		requires(std::is_copy_assignable_v<T&> && std::is_move_assignable_v<T&>)
		{
			typename std::remove_cvref<T>::type old_begin = std::move(range_begin);
			range_begin = range_end - increment;
			range_end = old_begin - increment;
			increment = -increment;
			return *this;
		}
#pragma endregion

#pragma region GETTERS
	public:
		/// <summary>
		/// <para> Retrieves the inclusive value at which this range begins. </para>
		/// <para> The retrieved value will be included in iteration of the range. </para>
		/// </summary>
		/// <returns>Inclusive value used at the very start of this range..</returns>
		[[nodiscard]] constexpr const typename std::remove_reference<T>::type& GetBeginValue() const noexcept
		{
			return range_begin;
		}

		/// <summary>
		/// <para> Retrieves the exclusive value at which this range ends. </para>
		/// <para> The retrieved value will not be included in iteration of the range. </para>
		/// </summary>
		/// <returns>Exclusive value used to mark the end of this range.</returns>
		[[nodiscard]] constexpr const typename std::remove_reference<T>::type& GetEndValue() const noexcept
		{
			return range_end;
		}

		/// <summary>
		/// <para> Retrieves the value added to progress to the next iteration within this range. </para>
		/// </summary>
		/// <returns>The increment used by this range's iterations.</returns>
		[[nodiscard]] constexpr const typename std::remove_reference<diff_type>::type& GetIncrement() const noexcept
		{
			return increment;
		}

		/// <summary>
		/// <para> Returns a boolean indicating if this range moves forwards. </para>
		/// </summary>
		/// <returns>`true` if this is a forward-moving range; otherwise false.</returns>
		[[nodiscard]] constexpr bool IsForwardMoving() const noexcept
		{
			return increment >= diff_type{};
		}

		/// <summary>
		/// <para> Returns a boolean indicating if this range moves backwards.</para>
		/// </summary>
		/// <returns>`true` if this is a backward-moving range; otherwise false.</returns>
		[[nodiscard]] constexpr bool IsBackwardMoving() const noexcept
		{
			return increment < diff_type{};
		}

		/// <summary>
		/// <para> Access a value offset from this range's inclusive start. </para>
		/// <para> This can safely exceed the bounds of the range; the bounds exist for iteration purposes only. </para>
		/// <para> Values may not be entirely accurate to what would be retrieved on a certain iteration if using floating-point types due to floating-point rounding errors. </para>
		/// </summary>
		/// <param name="iteration">Theoretical iteration number to retrieve the value for.</param>
		/// <returns>Value that would be retrieved on the specified iteration, or an approximation of such if using floating-point types.</returns>
		[[nodiscard]] constexpr typename std::remove_cvref<T>::type operator[](const diff_type iteration) const noexcept
		{
			return range_begin + (increment * iteration);
		}

		/// <summary>
		/// <para> Returns the number of values appearing in this range. </para>
		/// <para> Not available to floating-point ranges. </para>
		/// </summary>
		/// <returns>Number of values represented within this range.</returns>
		[[nodiscard]] constexpr size_t size() const noexcept
		requires(!std::is_floating_point_v<typename std::remove_cvref<T>::type>)
		{
			if (increment < diff_type{})
			{
				// Backward-moving, guaranteed begin > end
				return static_cast<size_t>((range_begin - range_end) / -increment);
			}
			else
			{
				// Forward-moving, guaranteed begin <= end
				return static_cast<size_t>((range_end - range_begin) / increment);
			}
		}
#pragma endregion

#pragma region STL_ITERATION
	public:
		/// <summary>
		/// <para> Iterator to the inclusive start of this collection in its present state. </para>
		/// <para> Will remain safe to use if this range is updated, but will not reflect the updated form of this range. </para>
		/// <para> Note that the values represented by iterators are immutable, and an iterator can only be used to traverse a range - NOT modify it. </para>
		/// </summary>
		[[nodiscard]] constexpr iterator begin() noexcept
		{
			return iterator{ range_begin, increment };
		}

		/// <summary>
		/// <para> Iterator to the inclusive start of this collection in its present state. </para>
		/// <para> Will remain safe to use if this range is updated, but will not reflect the updated form of this range. </para>
		/// <para> Note that the values represented by iterators are immutable, and an iterator can only be used to traverse a range - NOT modify it. </para>
		/// </summary>
		[[nodiscard]] constexpr const_iterator begin() const noexcept
		{
			return const_iterator{ range_begin, increment };
		}

		/// <summary>
		/// <para> Iterator to the exclusive end of this collection in its present state. </para>
		/// <para> Will remain safe to use if this range is updated, but will not match the updated form of this range. </para>
		/// <para> Note that the values represented by iterators are immutable, and an iterator can only be used to traverse a range - NOT modify it. </para>
		/// </summary>
		[[nodiscard]] constexpr iterator end() noexcept
		{
			return iterator{ range_end, increment };
		}

		/// <summary>
		/// <para> Iterator to the exclusive end of this collection in its present state. </para>
		/// <para> Will remain safe to use if this range is updated, but will not match the updated form of this range. </para>
		/// <para> Note that the values represented by iterators are immutable, and an iterator can only be used to traverse a range - NOT modify it. </para>
		/// </summary>
		[[nodiscard]] constexpr const_iterator end() const noexcept
		{
			return const_iterator{ range_end, increment };
		}

		/// <summary>
		/// <para> Iterator to the inclusive start of this collection in its present state. </para>
		/// <para> Will remain safe to use if this range is updated, but will not match the updated form of this range. </para>
		/// <para> Note that the values represented by iterators are immutable, and an iterator can only be used to traverse a range - NOT modify it. </para>
		/// </summary>
		[[nodiscard]] constexpr const_iterator cbegin() const noexcept
		{
			return const_iterator{ range_begin, increment };
		}

		/// <summary>
		/// <para> Iterator to the exclusive end of this collection in its present state. </para>
		/// <para> Will remain safe to use if this range is updated, but will not match the updated form of this range. </para>
		/// <para> Note that the values represented by iterators are immutable, and an iterator can only be used to traverse a range - NOT modify it. </para>
		/// </summary>
		[[nodiscard]] constexpr const_iterator cend() const noexcept
		{
			return const_iterator{ range_end, increment };
		}

		/// <summary>
		/// <para> Iterator to the inclusive start of this collection as if its current state has been reversed. </para>
		/// <para> Will remain safe to use if this range is updated, but will not reflect the updated form of this range. </para>
		/// <para> Note that the values represented by iterators are immutable, and an iterator can only be used to traverse a range - NOT modify it. </para>
		/// </summary>
		[[nodiscard]] constexpr reverse_iterator rbegin() noexcept
		{
			return reverse_iterator{ range_end - increment, -increment };
		}

		/// <summary>
		/// <para> Iterator to the inclusive start of this collection as if its current state has been reversed. </para>
		/// <para> Will remain safe to use if this range is updated, but will not reflect the updated form of this range. </para>
		/// <para> Note that the values represented by iterators are immutable, and an iterator can only be used to traverse a range - NOT modify it. </para>
		/// </summary>
		[[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept
		{
			return const_reverse_iterator{ range_end - increment, -increment };
		}

		/// <summary>
		/// <para> Iterator to the exclusive end of this collection as if its current state has been reversed. </para>
		/// <para> Will remain safe to use if this range is updated, but will not reflect the updated form of this range. </para>
		/// <para> Note that the values represented by iterators are immutable, and an iterator can only be used to traverse a range - NOT modify it. </para>
		/// </summary>
		[[nodiscard]] constexpr reverse_iterator rend() noexcept
		{
			return reverse_iterator{ range_begin - increment, -increment };
		}

		/// <summary>
		/// <para> Iterator to the exclusive end of this collection as if its current state has been reversed. </para>
		/// <para> Will remain safe to use if this range is updated, but will not reflect the updated form of this range. </para>
		/// <para> Note that the values represented by iterators are immutable, and an iterator can only be used to traverse a range - NOT modify it. </para>
		/// </summary>
		[[nodiscard]] constexpr const_reverse_iterator rend() const noexcept
		{
			return const_reverse_iterator{ range_begin - increment, -increment };
		}

		/// <summary>
		/// <para> Iterator to the inclusive start of this collection as if its current state has been reversed. </para>
		/// <para> Will remain safe to use if this range is updated, but will not reflect the updated form of this range. </para>
		/// <para> Note that the values represented by iterators are immutable, and an iterator can only be used to traverse a range - NOT modify it. </para>
		/// </summary>
		[[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept
		{
			return const_reverse_iterator{ range_end - increment, -increment };
		}

		/// <summary>
		/// <para> Iterator to the exclusive end of this collection as if its current state has been reversed. </para>
		/// <para> Will remain safe to use if this range is updated, but will not reflect the updated form of this range. </para>
		/// <para> Note that the values represented by iterators are immutable, and an iterator can only be used to traverse a range - NOT modify it. </para>
		/// </summary>
		[[nodiscard]] constexpr const_reverse_iterator crend() const noexcept
		{
			return const_reverse_iterator{ range_begin - increment, -increment };
		}
#pragma endregion

	private:
		T range_begin;
		T range_end;
		diff_type increment;
	};
	template<class T>
	Range(const T& end) -> EmuCore::Range<T>;
	template<class T>
	Range(const T& begin, const T& end) -> EmuCore::Range<T>;
	template<class T>
	Range(const T& begin, const T& end, const typename EmuCore::Range<T>::diff_type& increment) -> EmuCore::Range<T>;
}

#endif
