#ifndef EMU_MATH_NEW_VECTOR_TMP_H_INC_
#define EMU_MATH_NEW_VECTOR_TMP_H_INC_ 1

#include <cstddef>
#include "../../../../../EmuCore/TMPHelpers/TypeComparators.h"
#include "../../../../../EmuCore/TMPHelpers/TypeConvertors.h"
#include "../../../../../EmuCore/CommonTypes/DeferrableReferenceWrapper.h"

namespace EmuMath
{
	template<std::size_t Size_, typename T_>
	struct NewVector;

	template<typename TypeToReference_>
	using vector_internal_ref = EmuCore::DeferrableReferenceWrapper<TypeToReference_>;
	template<typename TypeToConstReference_>
	using vector_internal_const_ref = vector_internal_ref<const TypeToConstReference_>;
}

namespace EmuMath::TMP
{
	template<class T_>
	struct is_emu_new_vector
	{
		static constexpr bool value = std::conditional_t
		<
			std::is_same_v<T_, EmuCore::TMP::remove_ref_cv_t<T_>>,
			std::false_type,
			is_emu_new_vector<EmuCore::TMP::remove_ref_cv_t<T_>>
		>::value;
	};
	template<std::size_t Size_, typename T_>
	struct is_emu_new_vector<EmuMath::NewVector<Size_, T_>>
	{
		static constexpr bool value = true;
	};
	template<class T_>
	static constexpr bool is_emu_new_vector_v = is_emu_new_vector<T_>::value;

	template<std::size_t Index_, class T_>
	struct emu_vector_theoretical_return
	{
	private:
		using no_ref_or_volatile_t = std::remove_reference_t<std::remove_volatile_t<T_>>;

	public:
		using type = std::conditional_t
		<
			std::is_same_v<T_, no_ref_or_volatile_t>,
			T_,
			typename emu_vector_theoretical_return<Index_, no_ref_or_volatile_t>::type
		>;
	};
	template<std::size_t Index_, std::size_t Size_, typename T_>
	struct emu_vector_theoretical_return<Index_, EmuMath::NewVector<Size_, T_>>
	{
	private:
		using vector_type = EmuMath::NewVector<Size_, T_>;

	public:
		using type = std::conditional_t
		<
			Index_ < vector_type::size,
			typename vector_type::value_type&,
			typename vector_type::value_type_uq
		>;
	};
	template<std::size_t Index_, std::size_t Size_, typename T_>
	struct emu_vector_theoretical_return<Index_, const EmuMath::NewVector<Size_, T_>>
	{
	private:
		using vector_type = EmuMath::NewVector<Size_, T_>;

	public:
		using type = std::conditional_t
		<
			Index_ < vector_type::size,
			const typename vector_type::value_type&,
			typename vector_type::value_type_uq
		>;
	};
	template<std::size_t Index_, class T_>
	using emu_vector_theoretical_return_t = typename emu_vector_theoretical_return<Index_, T_>::type;

	template<std::size_t Index_, std::size_t Size_, typename T_>
	using emu_vector_from_args_theoretical_return = emu_vector_theoretical_return<Index_, EmuMath::NewVector<Size_, T_>>;
	template<std::size_t Index_, std::size_t Size_, typename T_>
	using emu_vector_from_args_theoretical_return_t = typename emu_vector_from_args_theoretical_return<Index_, Size_, T_>::type;


	template<std::size_t Index_, std::size_t Size_, typename T_>
	using emu_const_vector_from_args_theoretical_return = emu_vector_theoretical_return<Index_, const EmuMath::NewVector<Size_, T_>>;
	template<std::size_t Index_, std::size_t Size_, typename T_>
	using emu_const_vector_from_args_theoretical_return_t = typename emu_const_vector_from_args_theoretical_return<Index_, Size_, T_>::type;
}

#endif
