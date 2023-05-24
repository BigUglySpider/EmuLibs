#ifndef EMU_SIMD_UNDERLYING_FORWARD_TMP_H_INC_
#define EMU_SIMD_UNDERLYING_FORWARD_TMP_H_INC_ 1

#include "../../../../../../../EmuCore/TMPHelpers/TypeComparators.h"
#include "../../../../../../../EmuCore/TMPHelpers/Values.h"
#include <utility>

namespace EmuSIMD::TMP
{
	template<std::size_t Width_>
	[[nodiscard]] constexpr inline bool _valid_simd_int_element_width()
	{
		return Width_ == 8 || Width_ == 16 || Width_ == 32 || Width_ == 64;
	}

	[[nodiscard]] constexpr inline bool _valid_simd_int_element_width(std::size_t width_)
	{
		return width_ == 8 || width_ == 16 || width_ == 32 || width_ == 64;
	}

	template<std::size_t Width_>
	constexpr inline bool _assert_valid_simd_int_element_width()
	{
		constexpr bool is_valid = _valid_simd_int_element_width<Width_>();
		static_assert(is_valid, "Invalid element width for a SIMD register provided. | Valid per-element widths for integral SIMD registers are: 8, 16, 32, 64");
		return is_valid;
	}

	template<class T_>
	struct is_simd_register : public EmuCore::TMP::type_check_ignore_ref_cv_base<EmuSIMD::TMP::is_simd_register, std::false_type, T_>
	{
	};
	template<class T_>
	static constexpr bool is_simd_register_v = is_simd_register<typename std::remove_cvref<T_>::type>::value;

	template<class SIMDRegister_>
	struct simd_register_width : public EmuCore::TMP::type_check_ignore_ref_cv_base<EmuSIMD::TMP::simd_register_width, std::integral_constant<std::size_t, 0>, SIMDRegister_>
	{
	};
	template<class SIMDRegister_>
	static constexpr std::size_t simd_register_width_v = simd_register_width<SIMDRegister_>::value;

	template<class T_>
	struct is_integral_simd_register : public EmuCore::TMP::type_check_ignore_ref_cv_base<EmuSIMD::TMP::is_integral_simd_register, std::false_type, T_>
	{
	};
	template<class T_>
	static constexpr bool is_integral_simd_register_v = is_integral_simd_register<T_>::value;

	template<class T_>
	struct is_floating_point_simd_register : public EmuCore::TMP::type_check_ignore_ref_cv_base<EmuSIMD::TMP::is_floating_point_simd_register, std::false_type, T_>
	{
	};
	template<class T_>
	static constexpr bool is_floating_point_simd_register_v = is_floating_point_simd_register<T_>::value;

	template<class SIMDRegisterFP_>
	struct floating_point_register_element_count : public EmuCore::TMP::type_check_ignore_ref_cv_base<EmuSIMD::TMP::floating_point_register_element_count, std::integral_constant<std::size_t, 0>, SIMDRegisterFP_>
	{
	};
	template<class SIMDRegisterFP_>
	static constexpr std::size_t floating_point_register_element_count_v = floating_point_register_element_count<SIMDRegisterFP_>::value;

	template<class SIMDRegisterFP_>
	struct floating_point_register_element_width : public EmuCore::TMP::type_check_ignore_ref_cv_base<EmuSIMD::TMP::floating_point_register_element_width, std::integral_constant<std::size_t, 0>, SIMDRegisterFP_>
	{
	};
	template<class SIMDRegisterFP_>
	static constexpr std::size_t floating_point_register_element_width_v = floating_point_register_element_width<SIMDRegisterFP_>::value;

	template<class SIMDRegister_, std::size_t PerElementWidthIfGenericInt_ = 32>
	struct register_element_count
	{
	private:
		static constexpr bool _is_valid = _assert_valid_simd_int_element_width<PerElementWidthIfGenericInt_>();
		static_assert
		(
			_is_valid,
			"Invalid `PerElementWidthIfGenericInt_` specified for `EmuSIMD::TMP::register_element_count`"
		);

		static constexpr auto _get_value()
			-> typename std::conditional<_is_valid, std::size_t, const char[37]>::type
		{
			if constexpr (_is_valid)
			{
				using _register_uq = typename std::remove_cvref<SIMDRegister_>::type;
				if constexpr (std::is_same_v<SIMDRegister_, _register_uq>)
				{
					return std::size_t(0);
				}
				else
				{
					return register_element_count<_register_uq, PerElementWidthIfGenericInt_>::value;
				}
			}
			else
			{
				return "Invalid PerElementWidthIfGenericInt_";
			}
		}

	public:
		static constexpr auto value = _get_value();
	};
	template<class SIMDRegister_, std::size_t PerElementWidthIfGenericInt_ = 32>
	static constexpr auto register_element_count_v = register_element_count<SIMDRegister_, PerElementWidthIfGenericInt_>::value;

	template<class SIMDRegister_, std::size_t Index_, std::size_t PerElementWidthIfGenericInt_ = 32>
	struct valid_register_index
	{
	private:
		static constexpr inline bool _get_value()
		{
			using _register_uq = typename std::remove_cvref<SIMDRegister_>::type;
			if constexpr (_assert_valid_simd_int_element_width<PerElementWidthIfGenericInt_>())
			{
				if constexpr (std::is_same_v<SIMDRegister_, _register_uq> && is_simd_register_v<_register_uq>)
				{
					return valid_register_index<_register_uq, Index_, PerElementWidthIfGenericInt_>::value;
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
					EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(),
					"Invalid `PerElementWidthIfGenericInt_` specified for `EmuSIMD::TMP::valid_register_index`"
				);
				return false;
			}
		}

		static constexpr bool value = _get_value();
	};
	template<class SIMDRegister_, std::size_t Index_, std::size_t PerElementWidthIfGenericInt_ = 32>
	static constexpr bool valid_register_index_v = valid_register_index<SIMDRegister_, Index_, PerElementWidthIfGenericInt_>::value;

	template<class SIMDRegister_>
	struct half_width
	{
	private:
		using _register_uq = typename std::remove_cvref<SIMDRegister_>::type;

	public:
		using type = typename std::conditional_t
		<
			std::is_same_v<SIMDRegister_, _register_uq>,
			EmuCore::TMP::void_type,
			half_width<_register_uq>
		>::type;
	};

	template<class SIMDRegister_>
	struct register_to_arg_type
	{
	private:
		using _register_uq = typename std::remove_cvref<SIMDRegister_>::type;

	public:
		using type = typename std::conditional_t
		<
			std::is_same_v<SIMDRegister_, _register_uq>,
			EmuCore::TMP::dummy_type_wrapper<EmuCore::TMP::emu_tmp_err>,
			register_to_arg_type<_register_uq>
		>::type;
	};

	template<class SIMDRegister_, std::size_t PerElementWidthIfGenericInt_ = 32>
	struct register_movemask_type
	{
		using type = EmuCore::TMP::emu_tmp_err;
	};
	template<class SIMDRegister_, std::size_t PerElementWidthIfGenericInt_ = 32>
	using register_movemask_type_t = typename register_movemask_type<SIMDRegister_, PerElementWidthIfGenericInt_>::type;

	namespace Concepts
	{
		template<typename T_>
		concept KnownSIMD = EmuSIMD::TMP::is_simd_register_v<T_>;
	}
}

namespace EmuConcepts
{
	using namespace EmuSIMD::TMP::Concepts;
}

#endif
