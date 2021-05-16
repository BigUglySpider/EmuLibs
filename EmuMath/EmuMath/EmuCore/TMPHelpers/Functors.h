#ifndef EMU_CORE_TMP_HELPER_FUNCTORS_H_INC_
#define EMU_CORE_TMP_HELPER_FUNCTORS_H_INC_

#include "TypeComparators.h"
#include "TypeConvertors.h"
#include <type_traits>

namespace EmuCore::TMPHelpers
{
	template<typename Lhs_, typename Rhs_, typename Out_>
	struct _common_arithmetic_functor_info
	{
		static constexpr bool any_fp = EmuCore::TMPHelpers::is_any_floating_point_v<Lhs_, Rhs_, Out_>;
		static constexpr bool lhs_rhs_same = std::is_same_v<Lhs_, Rhs_>;
		static constexpr bool lhs_output_same = std::is_same_v<Lhs_, Out_>;
		static constexpr bool rhs_output_same = std::is_same_v<Rhs_, Out_>;
		static constexpr bool all_same = lhs_rhs_same && lhs_output_same;

		using result_type = std::conditional_t
		<
			all_same,
			Lhs_,
			std::conditional_t
			<
				any_fp,
				EmuCore::TMPHelpers::highest_byte_size_t
				<
					EmuCore::TMPHelpers::best_floating_point_rep_t<Lhs_>,
					EmuCore::TMPHelpers::best_floating_point_rep_t<Rhs_>,
					EmuCore::TMPHelpers::best_floating_point_rep_t<Out_>
				>,
				EmuCore::TMPHelpers::highest_byte_size_t<Lhs_, Rhs_, Out_>
			>
		>;
		static constexpr bool cast_result = std::is_same_v<result_type, Out_>;
	};

	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct plus_diff_types
	{
		using _info_type = _common_arithmetic_functor_info<Lhs_, Rhs_, Out_>;

		Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
		{
			if constexpr (_info_type::all_same)
			{
				return lhs + rhs;
			}
			else
			{
				if constexpr (_info_type::cast_result)
				{
					return static_cast<Out_>(static_cast<typename _info_type::result_type>(lhs) + rhs);
				}
				else
				{
					return static_cast<typename _info_type::result_type>(lhs) + rhs;
				}
			}
		}
	};
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct minus_diff_types
	{
		using _info_type = _common_arithmetic_functor_info<Lhs_, Rhs_, Out_>;

		Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
		{
			if constexpr (_info_type::all_same)
			{
				return lhs - rhs;
			}
			else
			{
				if constexpr (_info_type::cast_result)
				{
					return static_cast<Out_>(static_cast<typename _info_type::result_type>(lhs) - rhs);
				}
				else
				{
					return static_cast<typename _info_type::result_type>(lhs) - rhs;
				}
			}
		}
	};
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct multiplies_diff_types
	{
		using _info_type = _common_arithmetic_functor_info<Lhs_, Rhs_, Out_>;

		Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
		{
			if constexpr (_info_type::all_same)
			{
				return lhs * rhs;
			}
			else
			{
				if constexpr (_info_type::cast_result)
				{
					return static_cast<Out_>(static_cast<typename _info_type::result_type>(lhs) * rhs);
				}
				else
				{
					return static_cast<typename _info_type::result_type>(lhs) * rhs;
				}
			}
		}
	};
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct divides_diff_types
	{
		using _info_type = _common_arithmetic_functor_info<Lhs_, Rhs_, Out_>;

		Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
		{
			if constexpr (_info_type::all_same)
			{
				return lhs / rhs;
			}
			else
			{
				if constexpr (_info_type::cast_result)
				{
					return static_cast<Out_>(static_cast<typename _info_type::result_type>(lhs) / rhs);
				}
				else
				{
					return static_cast<typename _info_type::result_type>(lhs) / rhs;
				}
			}
		}
	};
	template<typename Lhs_, typename Rhs_, typename Out_ = Lhs_>
	struct modulus_diff_types
	{
		using _info_type = _common_arithmetic_functor_info<Lhs_, Rhs_, Out_>;

		Out_ operator()(const Lhs_& lhs, const Rhs_& rhs) const
		{
			if constexpr (_info_type::all_same)
			{
				return lhs % rhs;
			}
			else
			{
				if constexpr (_info_type::cast_result)
				{
					return static_cast<Out_>(static_cast<typename _info_type::result_type>(lhs) % rhs);
				}
				else
				{
					return static_cast<typename _info_type::result_type>(lhs) % rhs;
				}
			}
		}
	};
}

#endif