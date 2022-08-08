#ifndef EMU_MATH_QUATERNION_UNDERLYING_GET_H_INC_
#define EMU_MATH_QUATERNION_UNDERLYING_GET_H_INC_ 1

#include "_quaternion_tmp.h"
#include "../../../Vector.h"

namespace EmuMath::Helpers::_quaternion_underlying
{
#pragma region CUSTOM_INDEX_GETS
	template<std::size_t Index_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::Quaternion<T_>::value_type& _get_index(EmuMath::Quaternion<T_>& quaternion)
	{
		return quaternion.template at<Index_>();
	}

	template<std::size_t Index_, typename T_>
	[[nodiscard]] constexpr inline const typename EmuMath::Quaternion<T_>::value_type& _get_index(const EmuMath::Quaternion<T_>& quaternion)
	{
		return quaternion.template at<Index_>();
	}

	template<std::size_t Index_, typename T_>
	[[nodiscard]] constexpr inline auto _get_index(EmuMath::Quaternion<T_>&& quaternion)
		-> typename std::conditional<EmuMath::Quaternion<T_>::contains_ref, const typename EmuMath::Quaternion<T_>::value_type&, typename EmuMath::Quaternion<T_>::value_type&&>::type
	{
		if constexpr (EmuMath::Quaternion<T_>::contains_ref)
		{
			return quaternion.template at<Index_>();
		}
		else
		{
			return std::move(quaternion.template at<Index_>());
		}
	}
#pragma endregion

#pragma region SPECIFIC_INDEX_GETS
	template<typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::Quaternion<T_>::value_type& _get_x(EmuMath::Quaternion<T_>& quaternion)
	{
		return _get_index<0>(quaternion);
	}

	template<typename T_>
	[[nodiscard]] constexpr inline const typename EmuMath::Quaternion<T_>::value_type& _get_x(const EmuMath::Quaternion<T_>& quaternion)
	{
		return _get_index<0>(quaternion);
	}

	template<typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::Quaternion<T_>::value_type& _get_x(EmuMath::Quaternion<T_>&& quaternion)
	{
		return _get_index<0>(std::forward<EmuMath::Quaternion<T_>>(quaternion));
	}

	template<typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::Quaternion<T_>::value_type& _get_y(EmuMath::Quaternion<T_>& quaternion)
	{
		return _get_index<1>(quaternion);
	}

	template<typename T_>
	[[nodiscard]] constexpr inline const typename EmuMath::Quaternion<T_>::value_type& _get_y(const EmuMath::Quaternion<T_>& quaternion)
	{
		return _get_index<1>(quaternion);
	}

	template<typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::Quaternion<T_>::value_type& _get_y(EmuMath::Quaternion<T_>&& quaternion)
	{
		return _get_index<1>(std::forward<EmuMath::Quaternion<T_>>(quaternion));
	}

	template<typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::Quaternion<T_>::value_type& _get_z(EmuMath::Quaternion<T_>& quaternion)
	{
		return _get_index<2>(quaternion);
	}

	template<typename T_>
	[[nodiscard]] constexpr inline const typename EmuMath::Quaternion<T_>::value_type& _get_z(const EmuMath::Quaternion<T_>& quaternion)
	{
		return _get_index<2>(quaternion);
	}

	template<typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::Quaternion<T_>::value_type& _get_z(EmuMath::Quaternion<T_>&& quaternion)
	{
		return _get_index<2>(std::forward<EmuMath::Quaternion<T_>>(quaternion));
	}

	template<typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::Quaternion<T_>::value_type& _get_w(EmuMath::Quaternion<T_>& quaternion)
	{
		return _get_index<3>(quaternion);
	}

	template<typename T_>
	[[nodiscard]] constexpr inline const typename EmuMath::Quaternion<T_>::value_type& _get_w(const EmuMath::Quaternion<T_>& quaternion)
	{
		return _get_index<3>(quaternion);
	}

	template<typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::Quaternion<T_>::value_type& _get_w(EmuMath::Quaternion<T_>&& quaternion)
	{
		return _get_index<3>(std::forward<EmuMath::Quaternion<T_>>(quaternion));
	}
#pragma endregion

#pragma region ARGUMENT_GETS
	template<std::size_t Index_, class Arg_>
	[[nodiscard]] constexpr inline decltype(auto) _get_generic_quaternion_arg(Arg_&& arg_)
	{
		using arg_uq = typename EmuCore::TMP::remove_ref_cv<Arg_>::type;
		if constexpr (EmuMath::TMP::is_emu_quaternion_v<arg_uq>)
		{
			return _get_index<Index_>(std::forward<Arg_>(arg_));
		}
		else if constexpr(EmuMath::TMP::is_emu_vector_v<arg_uq>)
		{
			if constexpr (!std::is_lvalue_reference_v<Arg_> && Index_ < arg_uq::size && !arg_uq::contains_ref)
			{
				return std::move(arg_.template at<Index_>());
			}
			else
			{
				return arg_.template AtTheoretical<Index_>();
			}
		}
		else
		{
			return std::forward<Arg_>(arg_);
		}
	}

	template<typename Out_, std::size_t Index_, class Arg_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _valid_get_generic_quaternion_arg()
	{
		if constexpr (std::is_same_v<Arg_, Out_>)
		{
			return true;
		}
		else
		{
			if constexpr (!EmuCore::TMP::is_static_castable_v<decltype(_get_generic_quaternion_arg<Index_>(std::declval<Arg_>())), Out_>)
			{
				static_assert(!StaticAssert_, "Unable to retrieve a generic argument for an EmuMath Quaternion as a successful conversion to the required type cannot be performed.");
				return false;
			}
			else
			{
				return true;
			}
		}
	}

	template<typename Out_, std::size_t Index_, class Arg_>
	[[nodiscard]] constexpr inline decltype(auto) _get_generic_quaternion_arg(Arg_&& arg_)
	{
		if constexpr (_valid_get_generic_quaternion_arg<Out_, Index_, Arg_, true>())
		{
			if constexpr (std::is_same_v<Arg_, Out_>)
			{
				return std::forward<Arg_>(arg_);
			}
			else
			{
				return static_cast<Out_>(_get_generic_quaternion_arg<Index_>(std::forward<Arg_>(arg_)));
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Out_>(), "Failed to get a generic EmuMath Quaternion argument. See other static assert messages for more info.");
		}
	}

	template<typename Out_, class Arg_>
	[[nodiscard]] constexpr inline decltype(auto) _get_generic_quaternion_x(Arg_&& arg_)
	{
		return _get_generic_quaternion_arg<Out_, 0>(std::forward<Arg_>(arg_));
	}

	template<typename Out_, class Arg_>
	[[nodiscard]] constexpr inline decltype(auto) _get_generic_quaternion_y(Arg_&& arg_)
	{
		return _get_generic_quaternion_arg<Out_, 1>(std::forward<Arg_>(arg_));
	}

	template<typename Out_, class Arg_>
	[[nodiscard]] constexpr inline decltype(auto) _get_generic_quaternion_z(Arg_&& arg_)
	{
		return _get_generic_quaternion_arg<Out_, 2>(std::forward<Arg_>(arg_));
	}

	template<typename Out_, class Arg_>
	[[nodiscard]] constexpr inline decltype(auto) _get_generic_quaternion_w(Arg_&& arg_)
	{
		return _get_generic_quaternion_arg<Out_, 3>(std::forward<Arg_>(arg_));
	}
#pragma endregion
}

#endif
