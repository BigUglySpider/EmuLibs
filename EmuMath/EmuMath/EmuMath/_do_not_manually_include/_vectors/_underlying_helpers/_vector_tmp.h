#ifndef EMU_MATH_VECTOR_TMP_H_INC_
#define EMU_MATH_VECTOR_TMP_H_INC_ 1

#include <cstddef>
#include "../../../../EmuCore/CommonTypes/DeferrableReferenceWrapper.h"
#include "../../../../EmuCore/TMPHelpers/StdFeatureChecks.h"
#include "../../../../EmuCore/TMPHelpers/TypeComparators.h"
#include "../../../../EmuCore/TMPHelpers/TypeConvertors.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuMath
{
	template<std::size_t Size_, typename T_>
	struct Vector;

#pragma region INTERNAL_REFERENCES
	/// <summary> Type used to store references inside of EmuMath Vectors and, by extension, anything whose underlying storage is an EmuMath Vector. </summary>
	/// <typeparam name="TypeToReference_">: Exact type to be referenced, including const state.</typeparam>
	template<typename TypeToReference_>
	using vector_internal_ref = EmuCore::DeferrableReferenceWrapper<TypeToReference_>;
	/// <summary> Type used to store const references inside of EmuMath Vectors. Same as vector_internal_ref, but const will always be added to the type to reference. </summary>
	/// <typeparam name="TypeToConstReference_">: Type to be referenced. Const will always be applied to this type.</typeparam>
	template<typename TypeToConstReference_>
	using vector_internal_const_ref = vector_internal_ref<const TypeToConstReference_>;

	/// <summary> Wraps the passed reference in a vector_internal_ref. </summary>
	/// <param name="to_ref_">: Reference to wrap as a vector_internal_ref.</param>
	/// <returns>Passed reference to_ref_ wrapped as a vector_internal_ref of the related type.</returns>
	template
		<
		typename TypeToReference_,
		typename = std::enable_if_t
		<
			!EmuCore::TMP::is_instance_of_typeparams_only_v<TypeToReference_, std::reference_wrapper> &&
			!EmuCore::TMP::is_instance_of_typeparams_only_v<TypeToReference_, vector_internal_ref>
		>
	>
	[[nodiscard]] constexpr inline vector_internal_ref<TypeToReference_> make_vector_internal_ref(TypeToReference_& to_ref_)
	{
		return vector_internal_ref<TypeToReference_>(to_ref_);
	}

	/// <summary> Wraps the passed std-wrapped reference in a vector_internal_ref. </summary>
	/// <param name="to_ref_">: Reference to wrap as a vector_internal_ref.</param>
	/// <returns>Passed reference to_ref_ wrapped as a vector_internal_ref of the related type.</returns>
	template<typename TypeToReference_>
	[[nodiscard]] constexpr inline vector_internal_ref<TypeToReference_> make_vector_internal_ref(std::reference_wrapper<TypeToReference_>&& std_ref_)
	{
		return vector_internal_ref<TypeToReference_>(std_ref_.get());
	}

	template<typename TypeToReference_>
	[[nodiscard]] constexpr inline vector_internal_ref<TypeToReference_> make_vector_internal_ref(std::reference_wrapper<TypeToReference_>& std_ref_)
	{
		return vector_internal_ref<TypeToReference_>(std_ref_.get());
	}

	template<typename TypeToReference_, typename = std::enable_if_t<std::is_const_v<TypeToReference_>>>
	[[nodiscard]] constexpr inline vector_internal_const_ref<TypeToReference_> make_vector_internal_ref(const std::reference_wrapper<TypeToReference_>& std_ref_)
	{
		return vector_internal_const_ref<TypeToReference_>(std_ref_.get());
	}

	/// <summary> Wraps the passed wrapped vector_internal_ref in a vector_internal_ref. </summary>
	/// <param name="to_ref_">: Reference to wrap as a vector_internal_ref.</param>
	/// <returns>Passed reference to_ref_ wrapped as a vector_internal_ref of the related type.</returns>
	template<typename TypeToReference_>
	[[nodiscard]] constexpr inline vector_internal_ref<TypeToReference_> make_vector_internal_ref(vector_internal_ref<TypeToReference_>&& vector_ref_)
	{
		return vector_internal_ref<TypeToReference_>(vector_ref_.get());
	}

	template<typename TypeToReference_>
	[[nodiscard]] constexpr inline vector_internal_ref<TypeToReference_> make_vector_internal_ref(vector_internal_ref<TypeToReference_>& vector_ref_)
	{
		return vector_internal_ref<TypeToReference_>(vector_ref_.get());
	}

	template<typename TypeToReference_>
	[[nodiscard]] constexpr inline vector_internal_const_ref<TypeToReference_> make_vector_internal_ref(const vector_internal_ref<TypeToReference_>& vector_ref_)
	{
		return vector_internal_const_ref<TypeToReference_>(vector_ref_.get());
	}

	template<typename TypeToReference_>
	constexpr inline void make_vector_internal_ref(TypeToReference_&&) = delete;

	/// <summary> Wraps the passed reference in a vector_internal_const_ref. </summary>
	/// <param name="to_ref_">: Reference to wrap as a vector_internal_const_ref.</param>
	/// <returns>Passed reference to_ref_ wrapped as a vector_internal_const_ref of the related type.</returns>
	template
	<
		typename TypeToReference_,
		typename = std::enable_if_t
		<
			!EmuCore::TMP::is_instance_of_typeparams_only_v<TypeToReference_, std::reference_wrapper> &&
			!EmuCore::TMP::is_instance_of_typeparams_only_v<TypeToReference_, vector_internal_ref>
		>
	>
	[[nodiscard]] constexpr inline vector_internal_const_ref<TypeToReference_> make_vector_internal_const_ref(const TypeToReference_& to_ref_)
	{
		return vector_internal_const_ref<TypeToReference_>(to_ref_);
	}

	/// <summary> Wraps the passed std-wrapped reference in a vector_internal_const_ref. </summary>
	/// <param name="to_ref_">: Reference to wrap as a vector_internal_const_ref.</param>
	/// <returns>Passed reference to_ref_ wrapped as a vector_internal_const_ref of the related type.</returns>
	template<typename TypeToReference_>
	[[nodiscard]] constexpr inline vector_internal_const_ref<TypeToReference_> make_vector_internal_const_ref(std::reference_wrapper<TypeToReference_>&& std_ref_)
	{
		return vector_internal_const_ref<TypeToReference_>(std_ref_.get());
	}

	template<typename TypeToReference_>
	[[nodiscard]] constexpr inline vector_internal_const_ref<TypeToReference_> make_vector_internal_const_ref(std::reference_wrapper<TypeToReference_>& std_ref_)
	{
		return vector_internal_const_ref<TypeToReference_>(std_ref_.get());
	}

	template<typename TypeToReference_>
	[[nodiscard]] constexpr inline vector_internal_const_ref<TypeToReference_> make_vector_internal_const_ref(const std::reference_wrapper<TypeToReference_>& std_ref_)
	{
		return vector_internal_const_ref<TypeToReference_>(std_ref_.get());
	}

	/// <summary> Wraps the passed wrapped vector_internal_ref in a vector_internal_const_ref. </summary>
	/// <param name="to_ref_">: Reference to wrap as a vector_internal_const_ref.</param>
	/// <returns>Passed reference to_ref_ wrapped as a vector_internal_const_ref of the related type.</returns>
	template<typename TypeToReference_>
	[[nodiscard]] constexpr inline vector_internal_const_ref<TypeToReference_> make_vector_internal_const_ref(vector_internal_ref<TypeToReference_>&& vector_ref_)
	{
		return vector_internal_const_ref<TypeToReference_>(vector_ref_.get());
	}

	template<typename TypeToReference_>
	[[nodiscard]] constexpr inline vector_internal_const_ref<TypeToReference_> make_vector_internal_const_ref(vector_internal_ref<TypeToReference_>& vector_ref_)
	{
		return vector_internal_const_ref<TypeToReference_>(vector_ref_.get());
	}

	template<typename TypeToReference_>
	[[nodiscard]] constexpr inline vector_internal_const_ref<TypeToReference_> make_vector_internal_const_ref(const vector_internal_ref<TypeToReference_>& vector_ref_)
	{
		return vector_internal_const_ref<TypeToReference_>(vector_ref_.get());
	}

	template<typename TypeToReference_>
	constexpr inline void make_vector_internal_const_ref(TypeToReference_&&) = delete;
#pragma endregion
}

namespace EmuMath::TMP
{
	template<class T_>
	struct is_emu_vector
	{
		static constexpr bool value = std::conditional_t
		<
			std::is_same_v<T_, EmuCore::TMP::remove_ref_cv_t<T_>>,
			std::false_type,
			is_emu_vector<EmuCore::TMP::remove_ref_cv_t<T_>>
		>::value;
	};
	template<std::size_t Size_, typename T_>
	struct is_emu_vector<EmuMath::Vector<Size_, T_>>
	{
		static constexpr bool value = true;
	};
	template<class T_>
	static constexpr bool is_emu_vector_v = is_emu_vector<T_>::value;

	template<std::size_t Index_, class T_>
	struct emu_vector_theoretical_return
	{
	private:
		using no_ref_or_volatile_t = std::remove_reference_t<std::remove_volatile_t<T_>>;

	public:
		using type = typename std::conditional_t
		<
			std::is_same_v<T_, no_ref_or_volatile_t>,
			EmuCore::TMP::dummy_type_wrapper<T_&>,
			emu_vector_theoretical_return<Index_, no_ref_or_volatile_t>
		>::type;
	};
	template<std::size_t Index_, std::size_t Size_, typename T_>
	struct emu_vector_theoretical_return<Index_, EmuMath::Vector<Size_, T_>>
	{
	private:
		using vector_type = EmuMath::Vector<Size_, T_>;

	public:
		using type = std::conditional_t
		<
			Index_ < vector_type::size,
			typename vector_type::value_type&,
			typename vector_type::value_type_uq
		>;
	};
	template<std::size_t Index_, std::size_t Size_, typename T_>
	struct emu_vector_theoretical_return<Index_, const EmuMath::Vector<Size_, T_>>
	{
	private:
		using vector_type = EmuMath::Vector<Size_, T_>;

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
	using emu_vector_from_args_theoretical_return = emu_vector_theoretical_return<Index_, EmuMath::Vector<Size_, T_>>;
	template<std::size_t Index_, std::size_t Size_, typename T_>
	using emu_vector_from_args_theoretical_return_t = typename emu_vector_from_args_theoretical_return<Index_, Size_, T_>::type;


	template<std::size_t Index_, std::size_t Size_, typename T_>
	using emu_const_vector_from_args_theoretical_return = emu_vector_theoretical_return<Index_, const EmuMath::Vector<Size_, T_>>;
	template<std::size_t Index_, std::size_t Size_, typename T_>
	using emu_const_vector_from_args_theoretical_return_t = typename emu_const_vector_from_args_theoretical_return<Index_, Size_, T_>::type;

	template<class Lhs_, class Rhs_>
	struct smallest_vector
	{
	private:
		template<typename T_>
		[[nodiscard]] static constexpr inline std::size_t _vector_size()
		{
			if constexpr (is_emu_vector_v<T_>)
			{
				return T_::size;
			}
			else
			{
				return 0;
			}
		}

	public:
		using lhs_uq = EmuCore::TMP::remove_ref_cv_t<Lhs_>;
		using rhs_uq = EmuCore::TMP::remove_ref_cv_t<Rhs_>;

		static constexpr bool lhs_is_vector = is_emu_vector_v<lhs_uq>;
		static constexpr bool rhs_is_vector = is_emu_vector_v<rhs_uq>;

		/// <summary>
		/// <para> The smallest of the provided two types in terms of contained elements. </para>
		/// <para> Lhs_ and Rhs_ are EmuMath Vectors: Lhs_ if Lhs_::size is less than or equal to Rhs_::size, otherwise Rhs_. </para>
		/// <para> If only Lhs_ is an EmuMath Vector: Lhs_. </para>
		/// <para> If only Rhs_ is an EmuMath Vector: Rhs_. </para>
		/// <para> If neither Lhs_ nor Rhs_ is an EmuMath Vector: Lhs_. </para>
		/// </summary>
		using type = std::conditional_t
		<
			lhs_is_vector,
			std::conditional_t
			<
				rhs_is_vector,
				std::conditional_t<(lhs_uq::size <= _vector_size<rhs_uq>()), Lhs_, Rhs_>,
				Lhs_
			>,
			std::conditional_t<rhs_is_vector, Rhs_, Lhs_>
		>;
	};
	template<class Lhs_, class Rhs_>
	using smallest_vector_t = typename smallest_vector<Lhs_, Rhs_>::type;

	template<typename T_>
	struct preferred_vector_fp
	{
		using type = typename EmuCore::TMP::floating_point_equivalent<T_>::type;
	};
	template<typename T_>
	struct preferred_vector_fp<EmuMath::vector_internal_ref<T_>>
	{
		using type = typename preferred_vector_fp<T_>::type;
	};
	template<typename T_>
	using preferred_vector_fp_t = typename preferred_vector_fp<T_>::type;

	template<class Lhs_, class Rhs_>
	struct largest_vector
	{
	private:
		template<typename T_>
		[[nodiscard]] static constexpr inline std::size_t _vector_size()
		{
			if constexpr (is_emu_vector_v<T_>)
			{
				return T_::size;
			}
			else
			{
				return 0;
			}
		}

	public:
		using lhs_uq = EmuCore::TMP::remove_ref_cv_t<Lhs_>;
		using rhs_uq = EmuCore::TMP::remove_ref_cv_t<Rhs_>;

		static constexpr bool lhs_is_vector = is_emu_vector_v<lhs_uq>;
		static constexpr bool rhs_is_vector = is_emu_vector_v<rhs_uq>;

		/// <summary>
		/// <para> The largest of the provided two types in terms of contained elements. </para>
		/// <para> Lhs_ and Rhs_ are EmuMath Vectors: Lhs_ if Lhs_::size is greater than or equal to Rhs_::size, otherwise Rhs_. </para>
		/// <para> If only Lhs_ is an EmuMath Vector: Lhs_. </para>
		/// <para> If only Rhs_ is an EmuMath Vector: Rhs_. </para>
		/// <para> If neither Lhs_ nor Rhs_ is an EmuMath Vector: Lhs_. </para>
		/// </summary>
		using type = std::conditional_t
		<
			lhs_is_vector,
			std::conditional_t
			<
				rhs_is_vector,
				std::conditional_t<(lhs_uq::size >= _vector_size<rhs_uq>()), Lhs_, Rhs_>,
				Lhs_
			>,
			std::conditional_t<rhs_is_vector, Rhs_, Lhs_>
		>;
	};
	template<class Lhs_, class Rhs_>
	using largest_vector_t = typename largest_vector<Lhs_, Rhs_>::type;

	template<class T_, bool IsEmuVector_ = EmuMath::TMP::is_emu_vector_v<T_>>
	struct emu_vector_value_types
	{
		using value_type = std::remove_reference_t<T_>;
		using value_type_uq = EmuCore::TMP::remove_ref_cv_t<T_>;
	};
	template<class T_>
	struct emu_vector_value_types<T_, true>
	{
		using vector_type_uq = EmuCore::TMP::remove_ref_cv_t<T_>;
		using value_type = typename vector_type_uq::value_type;
		using value_type_uq = typename vector_type_uq::value_type_uq;
	};
	template<typename T_>
	using emu_vector_value_type_uq = typename emu_vector_value_types<T_>::value_type_uq;

	/// <summary>
	/// <para> Helper to instantiate a template using the provided arguments' value_type_uq as template arguments. </para>
	/// <para> If an Arg_ is not an EmuMath Vector: The provided template argument at that position will be the Arg_ type with const, volatile, and reference removed. </para>
	/// <para> If an Arg_ is an EmuMath Vector: The provided template argument at that position will be the Vector's value_type_uq. </para>
	/// <para> Contains two items: </para>
	/// <para> --- `value`: Boolean indicating if the template could successfully be instantiated. </para>
	/// <para> --- `type`: If `value` is true, this will be the instantiated template; otherwise, it will be void. </para>
	/// </summary>
	template<template<class...> class Template_, class...Args_>
	struct template_for_emu_vector_args
	{
	private:
		template<template<class...> class TemplateToBuild_, bool Valid_>
		struct _instance_builder
		{
			using type = void;
		};
		template<template<class...> class TemplateToBuild_>
		struct _instance_builder<TemplateToBuild_, true>
		{
			using type = TemplateToBuild_<emu_vector_value_type_uq<Args_>...>;
		};

	public:
		static constexpr bool value = EmuCore::TMP::valid_template_args_v<Template_, emu_vector_value_type_uq<Args_>...>;
		using type = typename _instance_builder<Template_, value>::type;
	};
	template<template<class...> class Template_, class...Args_>
	using template_for_emu_vector_args_t = typename template_for_emu_vector_args<Template_, Args_...>::type;

	template<class Vector_>
	struct emu_vector_template_args
	{
	private:
		template<class In_>
		struct _generator
		{
			static constexpr std::size_t size_ = 0;
			using t_ = void;
		};
		template<std::size_t Size_, typename T_>
		struct _generator<EmuMath::Vector<Size_, T_>>
		{
			static constexpr std::size_t size_ = Size_;
			using t_ = T_;
		};

		using _results = _generator<EmuCore::TMP::remove_ref_cv_t<Vector_>>;

	public:
		static constexpr bool is_vector = is_emu_vector_v<Vector_>;
		static constexpr std::size_t Size_ = _results::size_;
		using T_ = typename _results::t_;
	};

	template<class T_>
	struct is_recognised_vector_ref_wrapper
	{
	private:
		using _t_uq = typename EmuCore::TMP::remove_ref_cv<T_>::type;

	public:
		static constexpr bool value =
		(
			EmuCore::TMP::is_instance_of_typeparams_only_v<_t_uq, std::reference_wrapper> ||
			EmuCore::TMP::is_instance_of_typeparams_only_v<_t_uq, EmuCore::DeferrableReferenceWrapper> ||
			EmuCore::TMP::is_instance_of_typeparams_only_v<_t_uq, EmuMath::vector_internal_ref> ||
			EmuCore::TMP::is_instance_of_typeparams_only_v<_t_uq, EmuMath::vector_internal_const_ref>
		);
	};
	template<class T_>
	static constexpr bool is_recognised_vector_ref_wrapper_v = is_recognised_vector_ref_wrapper<T_>::value;
}

#pragma region EMU_CORE_TMP_SPECIALISATIONS
namespace EmuCore::TMP
{
	template<std::size_t Size_, typename T_>
	struct floating_point_equivalent<EmuMath::Vector<Size_, T_>>
	{
		using type = EmuMath::Vector<Size_, typename EmuMath::Vector<Size_, T_>::preferred_floating_point>;
	};
}
#pragma endregion

#endif
