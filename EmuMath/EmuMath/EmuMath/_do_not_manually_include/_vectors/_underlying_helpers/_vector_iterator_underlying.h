#ifndef EMU_MATH_VECTOR_ITERATOR_UNDERLYING_H_INC_
#define EMU_MATH_VECTOR_ITERATOR_UNDERLYING_H_INC_ 1

#include "_vector_tmp.h"
#include "../../../../EmuCore/TMPHelpers/TypeComparators.h"
#include <cstddef>

namespace EmuMath::Helpers::_vector_underlying
{
	template<class Vector_, bool Reverse_ = false>
	struct _vector_iterator_underlying
	{
	private:
		static_assert(EmuMath::TMP::is_emu_vector_v<Vector_>, "Attempted to create an EmuMath vector_iterator with a non-EmuMath-Vector argument type.");
		using _vector_type = EmuCore::TMP::remove_ref_cv_t<Vector_>;
		friend typename _vector_type;

		static constexpr bool _is_const = std::is_const_v<Vector_>;
		using _stored_type = typename EmuCore::TMP::conditional_const<_is_const, typename _vector_type::stored_type>::type;

	public:
		using this_type = EmuMath::Helpers::_vector_underlying::_vector_iterator_underlying<Vector_, Reverse_>;

		using iterator_category = std::random_access_iterator_tag;
		using value_type = typename _vector_type::value_type;
		using pointer = typename EmuCore::TMP::conditional_const<_is_const, value_type*>::type;
		using reference = typename EmuCore::TMP::conditional_const<_is_const, value_type&>::type;
		using difference_type = std::ptrdiff_t;

#pragma region CONSTRUCTORS
	private:
		/// <summary> Constructor that may only be invoked by the Vector that this iterator is for. </summary>
		/// <param name="val_pointer_">: Pointer to the item that this iterator points to.</param>
		/// <param name="index_">: Index of the pointed-to element. If this is for end, it should be size. If it is for reverse end, it should be -1.</param>
		constexpr inline _vector_iterator_underlying(_stored_type* val_pointer_, difference_type index_) noexcept : _p_item(val_pointer_), _index(index_)
		{
		}

	public:
		/// <summary> Default constructor which creates an invalid iterator. </summary>
		_vector_iterator_underlying() : _p_item(nullptr), _index(std::numeric_limits<difference_type>::lowest())
		{
		};

		constexpr inline _vector_iterator_underlying(const this_type& to_copy_) noexcept : _p_item(to_copy_._p_item), _index(to_copy_._index)
		{
		}

		constexpr inline _vector_iterator_underlying(this_type&& to_move_) noexcept : _p_item(to_move_._p_item), _index(to_move_._index)
		{
		}
#pragma endregion

#pragma region ACCESS
		[[nodiscard]] constexpr inline reference operator*()
		{
			return _dereference_pointer();
		}

		[[nodiscard]] constexpr inline const reference operator*() const
		{
			return _dereference_pointer();
		}

		[[nodiscard]] constexpr inline pointer operator->()
		{
			return _value_address();
		}

		[[nodiscard]] constexpr inline const pointer operator->() const
		{
			return _value_address();
		}

		[[nodiscard]] constexpr inline reference operator[](difference_type offset_)
		{
			return _dereference_pointer(offset_);
		}

		[[nodiscard]] constexpr inline const reference operator[](difference_type offset_) const
		{
			return _dereference_pointer(offset_);
		}
#pragma endregion

#pragma region COMPARISON
		[[nodiscard]] constexpr inline bool operator==(const this_type& rhs_) const noexcept
		{
			return _p_item == rhs_._p_item;
		}

		[[nodiscard]] constexpr inline bool operator!=(const this_type& rhs_) const noexcept
		{
			return _p_item != rhs_._p_item;
		}

		[[nodiscard]] constexpr inline bool operator>(const this_type& rhs_) const noexcept
		{
			if constexpr (Reverse_)
			{
				return rhs_._index > _index;
			}
			else
			{
				return _index > rhs_._index;
			}
		}

		[[nodiscard]] constexpr inline bool operator<(const this_type& rhs_) const noexcept
		{
			if constexpr (Reverse_)
			{
				return rhs_._index < _index;
			}
			else
			{
				return _index < rhs_._index;
			}
		}

		[[nodiscard]] constexpr inline bool operator>=(const this_type& rhs_) const noexcept
		{
			if constexpr (Reverse_)
			{
				return rhs_._index >= _index;
			}
			else
			{
				return _index >= rhs_._index;
			}
		}

		[[nodiscard]] constexpr inline bool operator<=(const this_type& rhs_) const noexcept
		{
			if constexpr (Reverse_)
			{
				return rhs_._index <= _index;
			}
			else
			{
				return _p_item <= rhs_._p_item;
			}
		}
#pragma endregion

#pragma region ASSIGNMENT
		constexpr inline this_type& operator=(const this_type& to_copy_) noexcept
		{
			_p_item = to_copy_._p_item;
			_index = to_copy_._index;
			return *this;
		}

		constexpr inline this_type& operator=(this_type&& to_move_) noexcept
		{
			_p_item = to_move_._p_item;
			_index = to_move_._index;
			return *this;
		}
#pragma endregion

#pragma region ARITHMETIC
		constexpr inline this_type& operator++() noexcept
		{
			if constexpr (Reverse_)
			{
				--_p_item;
				--_index;
			}
			else
			{
				++_p_item;
				++_index;
			}
			return *this;
		}

		constexpr inline this_type operator++(int) noexcept
		{
			this_type out_(_p_item);
			operator++();
			return out_;
		}

		constexpr inline this_type& operator--() noexcept
		{
			if constexpr (Reverse_)
			{
				++_p_item;
				++_index;
			}
			else
			{
				--_p_item;
				--_index;
			}
			return *this;
		}

		constexpr inline this_type operator--(int) noexcept
		{
			this_type out_(_p_item);
			operator--();
			return out_;
		}

		[[nodiscard]] constexpr inline difference_type operator-(const this_type& rhs_) const noexcept
		{
			if constexpr (Reverse_)
			{
				return rhs_._index - _index;
			}
			else
			{
				return _index - rhs_._index;
			}
		}

		[[nodiscard]] constexpr inline this_type operator+(difference_type increment_count_) const noexcept
		{
			if constexpr (Reverse_)
			{
				return this_type(_p_item - increment_count_, _index - increment_count_);
			}
			else
			{
				return this_type(_p_item + increment_count_, _index + increment_count_);
			}
		}

		[[nodiscard]] constexpr inline this_type operator-(difference_type decrement_count_) const noexcept
		{
			if constexpr (Reverse_)
			{
				return this_type(_p_item + decrement_count_, _index + decrement_count_);
			}
			else
			{
				return this_type(_p_item - decrement_count_, _index - decrement_count_);
			}
		}

		constexpr inline this_type& operator+=(difference_type increment_count_) noexcept
		{
			if constexpr (Reverse_)
			{
				_p_item -= increment_count_;
				_index -= increment_count_;
			}
			else
			{
				_p_item += increment_count_;
				_index += increment_count_;
			}
			return *this;
		}

		constexpr inline this_type& operator-=(difference_type decrement_count_) noexcept
		{
			if constexpr (Reverse_)
			{
				_p_item += decrement_count_;
				_index += decrement_count_;
			}
			else
			{
				_p_item -= decrement_count_;
				_index -= decrement_count_;
			}
			return *this;
		}
#pragma endregion

	private:
		[[nodiscard]] constexpr inline reference _dereference_pointer()
		{
			if constexpr (_vector_type::contains_ref)
			{
				return (*_p_item).get();
			}
			else
			{
				return *_p_item;
			}
		}

		[[nodiscard]] constexpr inline const reference _dereference_pointer() const
		{
			if constexpr (_vector_type::contains_ref)
			{
				return (*_p_item).get();
			}
			else
			{
				return *_p_item;
			}
		}

		[[nodiscard]] constexpr inline _stored_type* _offset_stored_pointer(difference_type offset_)
		{
			if constexpr (Reverse_)
			{
				return _p_item - offset_;
			}
			else
			{
				return _p_item + offset_;
			}
		}

		[[nodiscard]] constexpr inline const _stored_type* _offset_stored_pointer(difference_type offset_) const
		{
			if constexpr (Reverse_)
			{
				return _p_item - offset_;
			}
			else
			{
				return _p_item + offset_;
			}
		}

		[[nodiscard]] constexpr inline reference _dereference_pointer(difference_type offset_)
		{
			if constexpr (_vector_type::contains_ref)
			{
				return (*_offset_stored_pointer(offset_)).get();
			}
			else
			{
				return *_offset_stored_pointer(offset_);
			}
		}

		[[nodiscard]] constexpr inline reference _dereference_pointer(difference_type offset_) const
		{
			if constexpr (_vector_type::contains_ref)
			{
				return (*_offset_stored_pointer(offset_)).get();
			}
			else
			{
				return *_offset_stored_pointer(offset_);
			}
		}

		[[nodiscard]] constexpr inline pointer _value_address()
		{
			if constexpr (_vector_type::contains_ref)
			{
				return &(*_p_item).get();
			}
			else
			{
				return _p_item;
			}
		}

		[[nodiscard]] constexpr inline const pointer _value_address() const
		{
			if constexpr (_vector_type::contains_ref)
			{
				return &(*_p_item).get();
			}
			else
			{
				return _p_item;
			}
		}

		_stored_type* _p_item;
		difference_type _index;
	};
}

template<class Vector_, bool Reverse_>
[[nodiscard]] constexpr inline EmuMath::Helpers::_vector_underlying::_vector_iterator_underlying<Vector_, Reverse_> operator+
(
	typename EmuMath::Helpers::_vector_underlying::_vector_iterator_underlying<Vector_, Reverse_>::difference_type offset_,
	const EmuMath::Helpers::_vector_underlying::_vector_iterator_underlying<Vector_, Reverse_>& iterator_
)
{
	return (iterator_ + offset_);
}

#endif
