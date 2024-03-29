#ifndef EMU_MATH_VECTOR_GET_UNDERLYING_H_INC_
#define EMU_MATH_VECTOR_GET_UNDERLYING_H_INC_ 1

#include "_vector_tmp.h"

namespace EmuMath::Helpers::_vector_underlying
{
	template<class Vector_, typename = std::enable_if_t<EmuMath::TMP::is_emu_vector_v<Vector_>>>
	[[nodiscard]] constexpr inline typename Vector_::value_type_uq _vector_get_non_contained_value()
	{
		using out_type = typename Vector_::value_type_uq;
		if constexpr (std::is_default_constructible_v<out_type>)
		{
			return out_type();
		}
		else if constexpr (std::is_constructible_v<out_type, decltype(0)>)
		{
			return out_type(0);
		}
		else if constexpr (std::is_constructible_v<out_type, decltype(0.0f)>)
		{
			return out_type(0.0f);
		}
		else if constexpr (EmuCore::TMP::is_static_castable_v<decltype(0), out_type>)
		{
			return static_cast<out_type>(0);
		}
		else if constexpr (EmuCore::TMP::is_static_castable_v<decltype(0.0f), out_type>)
		{
			return static_cast<out_type>(0.0f);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Vector_>(),
				"Attempted to safely retrieve a non-contained value from an EmuMath Vector, but the contained type cannot be default-constructed or constructed/static_cast to with an argument of either `0` or `0.0f`. As non-contained elements are implied default/zero, this behaviour is required to safely retrieve a non-contained element."
			);
		}
	}
	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::Vector<Size_, T_>::value_type_uq _vector_get_non_contained_value()
	{
		return _vector_get_non_contained_value<EmuMath::Vector<Size_, T_>>();
	}

	template<std::size_t Index_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::Vector<Size_, T_>::value_type& _vector_get(EmuMath::Vector<Size_, T_>& vector_)
	{
		return vector_.template at<Index_>();
	}
	template<std::size_t Index_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline const typename EmuMath::Vector<Size_, T_>::value_type& _vector_get(const EmuMath::Vector<Size_, T_>& vector_)
	{
		return vector_.template at<Index_>();
	}

	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::Vector<Size_, T_>::value_type& _vector_get
	(
		EmuMath::Vector<Size_, T_>& vector_,
		std::size_t index_
	)
	{
		return vector_.at(index_);
	}
	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline const typename EmuMath::Vector<Size_, T_>::value_type& _vector_get
	(
		const EmuMath::Vector<Size_, T_>& vector_,
		std::size_t index_
	)
	{
		return vector_.at(index_);
	}

	template<std::size_t Index_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline const EmuMath::TMP::emu_vector_from_args_theoretical_return_t<Index_, Size_, T_> _vector_get_theoretical
	(
		EmuMath::Vector<Size_, T_>& vector_
	)
	{
		if constexpr (Index_ < EmuMath::Vector<Size_, T_>::size)
		{
			return vector_.template at<Index_>();
		}
		else
		{
			return _vector_get_non_contained_value<Size_, T_>();
		}
	}
	template<std::size_t Index_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline const EmuMath::TMP::emu_const_vector_from_args_theoretical_return_t<Index_, Size_, T_> _vector_get_theoretical
	(
		const EmuMath::Vector<Size_, T_>& vector_
	)
	{
		if constexpr (Index_ < EmuMath::Vector<Size_, T_>::size)
		{
			return vector_.template at<Index_>();
		}
		else
		{
			return _vector_get_non_contained_value<Size_, T_>();
		}
	}

	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::Vector<Size_, T_>::stored_type* _vector_data(EmuMath::Vector<Size_, T_>& vector_)
	{
		return vector_.data();
	}
	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline const typename EmuMath::Vector<Size_, T_>::stored_type* _vector_data(const EmuMath::Vector<Size_, T_>& vector_)
	{
		return vector_.data();
	}

	template<class Out_, std::size_t Size_, typename T_, typename = std::enable_if_t<EmuMath::Vector<Size_, T_>::template is_valid_try_get_output_ref<Out_, false>()>>
	[[nodiscard]] constexpr inline bool _vector_try_get(EmuMath::Vector<Size_, T_>& vector_, std::size_t index_, Out_& out_)
	{
		using vector_type = EmuMath::Vector<Size_, T_>;
		using value_type = typename vector_type::value_type;

		if constexpr (EmuCore::TMP::valid_assign_direct_or_cast<Out_, value_type&, Out_&>())
		{
			if (index_ < vector_type::size)
			{
				EmuCore::TMP::assign_direct_or_cast<Out_>(out_, vector_[index_]);
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<T_>(),
				"Attempted to retrieve an element within an EmuMath Vector via try_get (non-const), but the provided out_ type cannot be assigned to from a value in the Vector either directly or as a cast."
			);
		}
	}

	template<class Out_, std::size_t Size_, typename T_, typename = std::enable_if_t<EmuMath::Vector<Size_, T_>::template is_valid_try_get_output_ref<Out_, true>()>>
	[[nodiscard]] constexpr inline bool _vector_try_get(const EmuMath::Vector<Size_, T_>& vector_, std::size_t index_, Out_& out_)
	{
		// We repeat this function definition as the provided Out_ type may interact differently with const/non-const value_type references.
		using vector_type = EmuMath::Vector<Size_, T_>;
		using value_type = typename vector_type::value_type;

		if constexpr (EmuCore::TMP::valid_assign_direct_or_cast<Out_, const value_type&, Out_&>())
		{
			if (index_ < vector_type::size)
			{
				EmuCore::TMP::assign_direct_or_cast<Out_>(out_, vector_[index_]);
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<T_>(),
				"Attempted to retrieve an element within a const-qualified EmuMath Vector via try_get (non-const), but the provided out_ type cannot be assigned to from a value in the Vector either directly or as a cast."
			);
		}
	}

	template<bool NullptrIfFailed_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline bool _vector_try_get
	(
		EmuMath::Vector<Size_, T_>& vector_,
		std::size_t index_,
		typename EmuMath::Vector<Size_, T_>::value_type** pp_out_
	)
	{

		if (index_ < EmuMath::Vector<Size_, T_>::size)
		{
			(*pp_out_) = &(vector_[index_]);
			return true;
		}
		else
		{
			if constexpr (NullptrIfFailed_)
			{
				(*pp_out_) = nullptr;
			}
			return false;
		}
	}

	template<bool NullptrIfFailed_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline bool _vector_try_get
	(
		EmuMath::Vector<Size_, T_>& vector_,
		std::size_t index_,
		const typename EmuMath::Vector<Size_, T_>::value_type** pp_out_
	)
	{

		if (index_ < EmuMath::Vector<Size_, T_>::size)
		{
			(*pp_out_) = &(vector_[index_]);
			return true;
		}
		else
		{
			if constexpr (NullptrIfFailed_)
			{
				(*pp_out_) = nullptr;
			}
			return false;
		}
	}

	template<bool NullptrIfFailed_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline bool _vector_try_get
	(
		const EmuMath::Vector<Size_, T_>& vector_,
		std::size_t index_,
		const typename EmuMath::Vector<Size_, T_>::value_type** pp_const_out_
	)
	{
		if (index_ < EmuMath::Vector<Size_, T_>::size)
		{
			(*pp_const_out_) = &(vector_[index_]);
			return true;
		}
		else
		{
			if constexpr (NullptrIfFailed_)
			{
				(*pp_const_out_) = nullptr;
			}
			return false;
		}
	}
}

#endif
