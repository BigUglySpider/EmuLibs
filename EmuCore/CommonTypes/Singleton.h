#ifndef EMU_CORE_COMMON_TYPES_SINGLETON_H_INC_
#define EMU_CORE_COMMON_TYPES_SINGLETON_H_INC_ 1

#include <memory>
#include <ostream>
#include <stdexcept>
#include <type_traits>

#include "../CommonConcepts/CommonRequirements.h"
#include "../TMPHelpers/OperatorChecks.h"
#include "../TMPHelpers/VariadicHelpers.h"

namespace EmuCore
{
	/// <summary>
	/// <para> Wrapper type used to form a static Singleton of type T_, with the ability to have object references to said singleton. </para>
	/// <para> T_ must be not be a reference, a pointer, const-qualified, or volatile-qualified. </para>
	/// <para> Object references provide a significant amount of operators where the underlying type T_ also implements such operators. </para>
	/// </summary>
	template<class T_>
	class Singleton
	{
	public:
		static_assert(!std::is_reference_v<T_>, "Invalid Singleton Instance: Input type T_ is a reference; references are not permitted.");
		static_assert(!std::is_pointer_v<T_>, "Invalid Singleton Instance: Input type T_ is a pointer; pointers are not permitted.");
		static_assert(!std::is_const_v<T_>, "Invalid Singleton Instance: Input type T_ is const-qualified; const qualifiers are not permitted.");
		static_assert(!std::is_volatile_v<T_>, "Invalid Singleton Instance: Input type T_ is volatile-qualified; volatile qualifiers are not permitted.");
		using instance_type = T_;

	private:
		inline static std::unique_ptr<T_> _instance = nullptr;

	public:
		/// <summary>
		/// <para> Compile-time check used to determine if variadic construction/instantiation functions can be called for this Singleton type. </para>
		/// </summary>
		/// <returns>True if the passed ConstructionArgs_ are valid for instantiating this Singleton type's instance; otherwise false.</returns>
		template<class...ConstructionArgs_>
		[[nodiscard]] static constexpr inline bool are_valid_variadic_construction_args() noexcept
		{
			constexpr std::size_t num_args = sizeof...(ConstructionArgs_);
			return
			(
				(num_args > 0) && // Default constructor reserved
				(
					(num_args > 1) || // > 1 arg constructors are not reserved; if 1 arg, only allow args that are not some form of instance_type
					(!EmuConcepts::UnqualifiedMatch<typename EmuCore::TMP::first_variadic_arg<ConstructionArgs_...>::type, instance_type>)
				)
			);
		}

#pragma region STATIC_ACCESS
	public:
		/// <summary>
		/// <para> Returns a boolean indicating if the instance of this Singleton type exists. </para>
		/// </summary>
		/// <returns>True if the instance of this Singleton type currently exists; otherwise false.</returns>
		[[nodiscard]] static inline bool Exists() noexcept
		{
			return _instance != nullptr;
		}

		/// <summary>
		/// <para> Returns a constant reference to the instance of this Singleton type. </para>
		/// <para> Does not perform a safety check to ensure instantiation. If such a check is required, use `TryGetConst`. </para>
		/// </summary>
		/// <returns>Const-qualified reference to the instance of this Singleton type.</returns>
		[[nodiscard]] static inline const instance_type& GetConst()
		{
			return *_instance;
		}

		/// <summary>
		/// <para> Returns a reference to the instance of this Singleton type. </para>
		/// <para> Does not perform a safety check to ensure instantiation. If such a check is required, use `TryGetConst`. </para>
		/// </summary>
		/// <returns>Reference to the instance of this Singleton type.</returns>
		[[nodiscard]] static inline instance_type& Get()
		{
			return *_instance;
		}

		/// <summary>
		/// <para> Outputs a constant pointer to the instance of this Singleton type via the output pointer to an instance_type pointer. </para>
		/// </summary>
		/// <param name="pp_out_instance_">Pointer to the const-pointer to output to. If this function returns false, the pointed-to-pointer will be set to nullptr.</param>
		/// <returns>True if the instance of this Singleton type currently exists; otherwise false.</returns>
		[[nodiscard]] static inline bool TryGetConst(const instance_type* const* pp_out_instance_) noexcept
		{
			(*pp_out_instance_) = const_cast<const instance_type*>(_instance.get());
			return (*pp_out_instance_) != nullptr;
		}

		/// <summary>
		/// <para> Outputs a pointer to the instance of this Singleton type via the output pointer to an instance_type pointer. </para>
		/// </summary>
		/// <param name="pp_out_instance_">Pointer to the pointer to output to. If this function returns false, the pointed-to-pointer will be set to nullptr.</param>
		/// <returns>True if the instance of this Singleton type currently exists; otherwise false.</returns>
		[[nodiscard]] static inline bool TryGet(instance_type* const* pp_out_instance_) noexcept
		{
			(*pp_out_instance_) = _instance.get();
			return (*pp_out_instance_) != nullptr;
		}

		/// <summary>
		/// <para> Outputs a constant pointer to the instance of this Singleton type via the output pointer to an instance_type pointer. </para>
		/// </summary>
		/// <param name="pp_out_instance_">Pointer to the const-pointer to output to. If this function returns false, the pointed-to-pointer will be set to nullptr.</param>
		/// <returns>True if the instance of this Singleton type currently exists; otherwise false.</returns>
		[[nodiscard]] static inline bool TryGet(const instance_type* const* pp_out_instance_) noexcept
		{
			return TryGetConst(pp_out_instance_);
		}

		/// <summary>
		/// <para> Instantiates this Singleton type's instance via default-construction, only if it is not currently instantiated. </para>
		/// <para> If instantiation should be performed but an instance may not be default-constructed, this will throw a std::invalid_argument exception. </para>
		/// </summary>
		static inline void TryInstantiate() noexcept(std::is_nothrow_default_constructible_v<instance_type>)
		{
			if (!Exists())
			{
				if constexpr (std::is_default_constructible_v<instance_type>)
				{
					_instance = std::make_unique<instance_type>();
				}
				else
				{
					throw std::invalid_argument("Failed to instantiate a Singleton through default construction as the wrapped type is not default-constructible.");
				}
			}
		}

		/// <summary>
		/// <para> Instantiates this Singleton type's instance via move-construction, only if it is not currently instantiated. </para>
		/// <para> If instantiation should be performed but an instance may not be move-constructed, this will throw a std::invalid_argument exception. </para>
		/// </summary>
		static inline void TryInstantiate([[maybe_unused]] instance_type&& to_move_if_uninstantiated_) noexcept(std::is_nothrow_move_constructible_v<instance_type>)
		{
			if (!Exists())
			{
				if constexpr (std::is_move_constructible_v<instance_type>)
				{
					_instance = std::make_unique<instance_type>(std::move(to_move_if_uninstantiated_));
				}
				else
				{
					throw std::invalid_argument("Failed to instantiate a Singleton through move construction as the wrapped type is not move-constructible.");
				}
			}
		}

		/// <summary>
		/// <para> Instantiates this Singleton type's instance via const-copy-construction, only if it is not currently instantiated. </para>
		/// <para> If instantiation should be performed but an instance may not be const-copy-constructed, this will throw a std::invalid_argument exception. </para>
		/// </summary>
		static inline void TryInstantiate([[maybe_unused]] const instance_type& to_copy_if_uninstantiated_) noexcept(std::is_nothrow_copy_constructible_v<instance_type>)
		{
			if (!Exists())
			{
				if constexpr (std::is_copy_constructible_v<instance_type>)
				{
					_instance = std::make_unique<instance_type>(to_copy_if_uninstantiated_);
				}
				else
				{
					throw std::invalid_argument("Failed to instantiate a Singleton through const-copy construction as the wrapped type is not const-copy-constructible.");
				}
			}
		}
		
		/// <summary>
		/// <para> Instantiates this Singleton type's instance via non-const-copy-construction, only if it is not currently instantiated. </para>
		/// <para> If instantiation should be performed but an instance may not be non-const-copy-constructed, this will throw a std::invalid_argument exception. </para>
		/// </summary>
		template<std::size_t Unused_ = 0>
		requires(!std::is_const_v<instance_type>)
		static inline void TryInstantiate([[maybe_unused]] instance_type& to_copy_if_uninstantiated_) noexcept(std::is_nothrow_constructible_v<instance_type, instance_type&>)
		{
			if (!Exists())
			{
				if constexpr (std::is_constructible_v<instance_type, instance_type&>)
				{
					_instance = std::make_unique<instance_type>(to_copy_if_uninstantiated_);
				}
				else
				{
					throw std::invalid_argument("Failed to instantiate a Singleton through non-const-copy construction as the wrapped type is not non-const-copy-constructible.");
				}
			}
		}

		/// <summary>
		/// <para> Instantiates this Singleton type's instance via the passed construction arguments, only if it is not currently instantiated. </para>
		/// <para> Can only be called if the input arguments are valid for constructing an instance. </para>
		/// </summary>
		template<class...ConstructionArgs_>
		requires(are_valid_variadic_construction_args<ConstructionArgs_...>())
		static inline void TryInstantiate([[maybe_unused]] ConstructionArgs_&&...construction_args_) noexcept(std::is_nothrow_constructible_v<instance_type, ConstructionArgs_...>)
		{
			if (!Exists())
			{
				_instance = std::make_unique<instance_type>(std::forward<ConstructionArgs_>(construction_args_)...);
			}
		}

		/// <summary>
		/// <para> Destroys the instance of this Singleton type. </para>
		/// <para> Although this frees up space for a new instance to be instantiated, most scenarios should aim to avoid such a pattern. </para>
		/// <para> This will invalidate any existing objects. This should only be called when existing objects are no longer using the instance. </para>
		/// <para> 
		///		Note that data will be destroyed automatically on program close. 
		///		This only needs to be called if a Singleton is no longer used mid-runtime, and even then only if you wish to free its memory for other uses, security reasons, etc.
		/// </para>
		/// </summary>
		static inline void Destroy() noexcept
		{
			_instance.reset(nullptr);
		}
#pragma endregion

		/// <summary>
		/// <para> Constructor which performs no instantiation, as input of another Singleton suggests instantiation is already completed. </para> 
		/// <para> Useful to avoid instantiation for an object which is not allowed to perform instantiation. </para>
		/// <para> Invoke this using std::declval to generate the argument. </para>
		/// </summary>
		Singleton(const Singleton<T_>&) noexcept {};
		/// <summary>
		/// <para> Constructor which performs no instantiation, as input of another Singleton suggests instantiation is already completed. </para> 
		/// <para> Useful to avoid instantiation for an object which is not allowed to perform instantiation. </para>
		/// <para> Invoke this using std::declval to generate the argument. </para>
		/// </summary>
		Singleton(Singleton<T_>&&) noexcept {};

		/// <summary>
		/// <para> Creates an object reference to this Singleton type. </para>
		/// <para> If this Singleton type has not already been instantiated, this will instantiate it via default-construction. </para>
		/// <para> If instantiation must be performed but the item is not default-constructible, this will throw a std::invalid_argument exception. </para>
		/// <para> It is encouraged to use this sparingly, and only in cases where there may be competition for first-to-construct. All accesses may be performed statically. </para>
		/// </summary>
		explicit inline Singleton() noexcept(std::is_nothrow_default_constructible_v<instance_type>)
		{
			TryInstantiate();
		}

		/// <summary>
		/// <para> Creates an object reference to this Singleton type. </para>
		/// <para> If this Singleton type has not already been instantiated, this will instantiate it via move-construction. </para>
		/// <para> If instantiation must be performed but the item is not move-constructible, this will throw a std::invalid_argument exception. </para>
		/// <para> If this Singleton type has already been instantiated, the input argument will not be used. </para>
		/// <para> It is encouraged to use this sparingly, and only in cases where there may be competition for first-to-construct. All accesses may be performed statically. </para>
		/// </summary>
		explicit inline Singleton([[maybe_unused]] instance_type&& to_move_if_uninstantiated_) noexcept(std::is_nothrow_move_constructible_v<instance_type>)
		{
			TryInstantiate(std::move(to_move_if_uninstantiated_));
		}

		/// <summary>
		/// <para> Creates an object reference to this Singleton type. </para>
		/// <para> If this Singleton type has not already been instantiated, this will instantiate it via const-copy-construction. </para>
		/// <para> If instantiation must be performed but the item is not const-copy-constructible, this will throw a std::invalid_argument exception. </para>
		/// <para> If this Singleton type has already been instantiated, the input argument will not be used. </para>
		/// <para> It is encouraged to use this sparingly, and only in cases where there may be competition for first-to-construct. All accesses may be performed statically. </para>
		/// </summary>
		explicit inline Singleton([[maybe_unused]] const instance_type& to_copy_if_uninstantiated_) noexcept(std::is_nothrow_copy_constructible_v<instance_type>)
		{
			TryInstantiate(to_copy_if_uninstantiated_);
		}

		/// <summary>
		/// <para> Creates an object reference to this Singleton type. </para>
		/// <para> If this Singleton type has not already been instantiated, this will instantiate it via non-const-copy-construction. </para>
		/// <para> If instantiation must be performed but the item is not non-const-copy-constructible, this will throw a std::invalid_argument exception. </para>
		/// <para> If this Singleton type has already been instantiated, the input argument will not be used. </para>
		/// <para> It is encouraged to use this sparingly, and only in cases where there may be competition for first-to-construct. All accesses may be performed statically. </para>
		/// </summary>
		template<std::size_t Unused_ = 0>
		requires(!std::is_const_v<instance_type>)
		explicit inline Singleton([[maybe_unused]] instance_type& to_copy_if_uninstantiated_) noexcept(std::is_nothrow_constructible_v<instance_type, instance_type&>)
		{
			TryInstantiate(to_copy_if_uninstantiated_);
		}

		/// <summary>
		/// <para> Creates an object reference to this Singleton type. </para>
		/// <para> If this Singleton type has not already been instantiated, this will instantiate it via construction with the passed arguments. </para>
		/// <para> If this Singleton type has already been instantiated, the input arguments will not be used. </para>
		/// <para> It is encouraged to use this sparingly, and only in cases where there may be competition for first-to-construct. All accesses may be performed statically. </para>
		/// </summary>
		template<class...ConstructionArgs_>
		requires(are_valid_variadic_construction_args<ConstructionArgs_...>())
		explicit inline Singleton([[maybe_unused]] ConstructionArgs_&&...construction_args_) noexcept(std::is_nothrow_constructible_v<instance_type, ConstructionArgs_...>)
		{
			TryInstantiate(std::forward<ConstructionArgs_>(construction_args_)...);
		}

		[[nodiscard]] inline operator instance_type& ()
		{
			return Singleton<T_>::Get();
		}

		[[nodiscard]] inline operator const instance_type& () const
		{
			return Singleton<T_>::GetConst();
		}

#pragma region ASSIGNMENT_OPERATORS
	public:
		template<class Rhs_>
		requires(std::is_assignable_v<instance_type&, Rhs_>)
		inline decltype(auto) operator=(Rhs_&& rhs_) noexcept(std::is_nothrow_assignable_v<instance_type, Rhs_>)
		{
			return (Get() = std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(std::is_assignable_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator=(Rhs_&& rhs_) const noexcept(std::is_nothrow_assignable_v<const instance_type, Rhs_>)
		{
			return (GetConst() = std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region CMP_OPERATORS
	public:
		template<class Rhs_>
		requires(EmuCore::TMP::has_cmp_equal_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator==(Rhs_&& rhs_)
		{
			return (Get() == std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_cmp_equal_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator==(Rhs_&& rhs_) const
		{
			return (GetConst() == std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_cmp_not_equal_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator!=(Rhs_&& rhs_)
		{
			return (Get() != std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_cmp_not_equal_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator!=(Rhs_&& rhs_) const
		{
			return (GetConst() != std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_cmp_less_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator<(Rhs_&& rhs_)
		{
			return (Get() < std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_cmp_less_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator<(Rhs_&& rhs_) const
		{
			return (GetConst() < std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_cmp_greater_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator>(Rhs_&& rhs_)
		{
			return (Get() > std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_cmp_greater_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator>(Rhs_&& rhs_) const
		{
			return (GetConst() > std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_cmp_less_equal_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator<=(Rhs_&& rhs_)
		{
			return (Get() <= std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_cmp_less_equal_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator<=(Rhs_&& rhs_) const
		{
			return (GetConst() <= std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_cmp_greater_equal_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator>=(Rhs_&& rhs_)
		{
			return (Get() >= std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_cmp_greater_equal_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator>=(Rhs_&& rhs_) const
		{
			return (GetConst() >= std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region LOGICAL_OPERATORS
	public:
		template<std::size_t Unused_ = 0>
		requires(EmuCore::TMP::has_logical_not_operator_v<instance_type&>)
		inline decltype(auto) operator!()
		{
			return (!Get());
		}

		template<std::size_t Unused_ = 0>
		requires(EmuCore::TMP::has_logical_not_operator_v<const instance_type&>)
		inline decltype(auto) operator!() const
		{
			return (!GetConst());
		}

		template<std::size_t Unused_ = 0>
		requires(std::is_convertible_v<instance_type&, bool>)
		inline operator bool()
		{
			return static_cast<bool>(Get());
		}

		template<std::size_t Unused_ = 0>
		requires(std::is_convertible_v<const instance_type&, bool>)
		inline operator bool() const
		{
			return static_cast<bool>(GetConst());
		}
#pragma endregion

#pragma region ARITHMETIC_OPERATORS
	public:
		template<class Rhs_>
		requires(EmuCore::TMP::has_plus_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator+(Rhs_&& rhs_)
		{
			return (Get() + std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_plus_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator+(Rhs_&& rhs_) const
		{
			return (GetConst() + std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_subtract_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator-(Rhs_&& rhs_)
		{
			return (Get() - std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_subtract_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator-(Rhs_&& rhs_) const
		{
			return (GetConst() - std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_multiply_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator*(Rhs_&& rhs_)
		{
			return (Get() * std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_multiply_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator*(Rhs_&& rhs_) const
		{
			return (GetConst() * std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_divide_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator/(Rhs_&& rhs_)
		{
			return (Get() / std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_divide_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator/(Rhs_&& rhs_) const
		{
			return (GetConst() / std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_mod_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator%(Rhs_&& rhs_)
		{
			return (Get() % std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_mod_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator%(Rhs_&& rhs_) const
		{
			return (GetConst() % std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region ARITHMETIC_ASSIGN_OPERATORS
	public:
		template<class Rhs_>
		requires(EmuCore::TMP::has_plus_assign_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator+=(Rhs_&& rhs_)
		{
			return (Get() += std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_plus_assign_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator+=(Rhs_&& rhs_) const
		{
			return (GetConst() += std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_subtract_assign_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator-=(Rhs_&& rhs_)
		{
			return (Get() -= std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_subtract_assign_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator-=(Rhs_&& rhs_) const
		{
			return (GetConst() -= std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_multiply_assign_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator*=(Rhs_&& rhs_)
		{
			return (Get() *= std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_multiply_assign_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator*=(Rhs_&& rhs_) const
		{
			return (GetConst() *= std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_divide_assign_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator/=(Rhs_&& rhs_)
		{
			return (Get() /= std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_divide_assign_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator/=(Rhs_&& rhs_) const
		{
			return (GetConst() /= std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_mod_assign_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator%=(Rhs_&& rhs_)
		{
			return (Get() %= std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_mod_assign_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator%=(Rhs_&& rhs_) const
		{
			return (GetConst() %= std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region UNARY_ARItHMETIC_OPERATORS
	public:
		template<std::size_t Unused_ = 0>
		requires(EmuCore::TMP::has_unary_plus_operator_v<instance_type&>)
		inline decltype(auto) operator+()
		{
			return (+Get());
		}

		template<std::size_t Unused_ = 0>
		requires(EmuCore::TMP::has_unary_plus_operator_v<const instance_type&>)
		inline decltype(auto) operator+() const
		{
			return (+GetConst());
		}
		
		template<std::size_t Unused_ = 0>
		requires(EmuCore::TMP::has_unary_minus_operator_v<instance_type&>)
		inline decltype(auto) operator+()
		{
			return (-Get());
		}

		template<std::size_t Unused_ = 0>
		requires(EmuCore::TMP::has_unary_minus_operator_v<const instance_type&>)
		inline decltype(auto) operator+() const
		{
			return (-GetConst());
		}

		template<std::size_t Unused_ = 0>
		requires(EmuCore::TMP::has_pre_increment_operator_v<instance_type&>)
		inline decltype(auto) operator++()
		{
			return (++Get());
		}

		template<std::size_t Unused_ = 0>
		requires(EmuCore::TMP::has_pre_increment_operator_v<const instance_type&>)
		inline decltype(auto) operator++() const
		{
			return (++GetConst());
		}

		template<std::size_t Unused_ = 0>
		requires(EmuCore::TMP::has_pre_decrement_operator_v<instance_type&>)
		inline decltype(auto) operator--()
		{
			return (--Get());
		}

		template<std::size_t Unused_ = 0>
		requires(EmuCore::TMP::has_pre_decrement_operator_v<const instance_type&>)
		inline decltype(auto) operator--() const
		{
			return (--GetConst());
		}

		template<std::size_t Unused_ = 0>
		requires(EmuCore::TMP::has_post_increment_operator_v<instance_type&>)
		inline decltype(auto) operator++(int)
		{
			return (Get()++);
		}

		template<std::size_t Unused_ = 0>
		requires(EmuCore::TMP::has_post_increment_operator_v<const instance_type&>)
		inline decltype(auto) operator++(int) const
		{
			return (GetConst()++);
		}

		template<std::size_t Unused_ = 0>
		requires(EmuCore::TMP::has_post_decrement_operator_v<instance_type&>)
		inline decltype(auto) operator--(int)
		{
			return (Get()--);
		}

		template<std::size_t Unused_ = 0>
		requires(EmuCore::TMP::has_post_decrement_operator_v<const instance_type&>)
		inline decltype(auto) operator--(int) const
		{
			return (GetConst()--);
		}
#pragma endregion

#pragma region BITWISE_OPERATORS
	public:
		template<class Rhs_>
		requires(EmuCore::TMP::has_bitwise_and_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator&(Rhs_&& rhs_)
		{
			return (Get() & std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_bitwise_and_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator&(Rhs_&& rhs_) const
		{
			return (GetConst() & std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_bitwise_or_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator|(Rhs_&& rhs_)
		{
			return (Get() | std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_bitwise_or_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator|(Rhs_&& rhs_) const
		{
			return (GetConst() | std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_bitwise_xor_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator^(Rhs_&& rhs_)
		{
			return (Get() ^ std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_bitwise_xor_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator^(Rhs_&& rhs_) const
		{
			return (GetConst() ^ std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_left_shift_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator<<(Rhs_&& rhs_)
		{
			return (Get() << std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_left_shift_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator<<(Rhs_&& rhs_) const
		{
			return (GetConst() << std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_right_shift_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator>>(Rhs_&& rhs_)
		{
			return (Get() >> std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_right_shift_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator>>(Rhs_&& rhs_) const
		{
			return (GetConst() >> std::forward<Rhs_>(rhs_));
		}

		template<std::size_t Unused_ = 0>
		requires(EmuCore::TMP::has_bitwise_not_operator_v<instance_type&>)
		inline decltype(auto) operator~()
		{
			return (~Get());
		}

		template<std::size_t Unused_ = 0>
		requires(EmuCore::TMP::has_bitwise_not_operator_v<const instance_type&>)
		inline decltype(auto) operator~() const
		{
			return (~GetConst());
		}
#pragma endregion
	
#pragma region BITWISE_ASSIGN_OPERATORS
	public:
		template<class Rhs_>
		requires(EmuCore::TMP::has_bitwise_and_assign_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator&=(Rhs_&& rhs_)
		{
			return (Get() &= std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_bitwise_and_assign_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator&=(Rhs_&& rhs_) const
		{
			return (GetConst() &= std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_bitwise_or_assign_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator|=(Rhs_&& rhs_)
		{
			return (Get() |= std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_bitwise_or_assign_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator|=(Rhs_&& rhs_) const
		{
			return (GetConst() |= std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_bitwise_xor_assign_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator^=(Rhs_&& rhs_)
		{
			return (Get() ^= std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_bitwise_xor_assign_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator^=(Rhs_&& rhs_) const
		{
			return (GetConst() ^= std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_left_shift_assign_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator<<=(Rhs_&& rhs_)
		{
			return (Get() <<= std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_left_shift_assign_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator<<=(Rhs_&& rhs_) const
		{
			return (GetConst() <<= std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_right_shift_assign_operator_v<instance_type&, Rhs_>)
		inline decltype(auto) operator>>=(Rhs_&& rhs_)
		{
			return (Get() >>= std::forward<Rhs_>(rhs_));
		}

		template<class Rhs_>
		requires(EmuCore::TMP::has_right_shift_assign_operator_v<const instance_type&, Rhs_>)
		inline decltype(auto) operator>>=(Rhs_&& rhs_) const
		{
			return (GetConst() >>= std::forward<Rhs_>(rhs_));
		}
#pragma endregion

#pragma region MISC_OPERATORS
	public:
		template<class Arg_>
		requires(EmuCore::TMP::has_subscript_operator_v<instance_type&, Arg_>)
		inline decltype(auto) operator[](Arg_&& arg_)
		{
			return (Get()[std::forward<Arg_>(arg_)]);
		}

		template<class Arg_>
		requires(EmuCore::TMP::has_subscript_operator_v<const instance_type&, Arg_>)
		inline decltype(auto) operator[](Arg_&& arg_) const
		{
			return (GetConst()[std::forward<Arg_>(arg_)]);
		}

		template<class...Args_>
		requires(std::is_invocable_v<instance_type&, Args_...>)
		inline decltype(auto) operator()(Args_&&...args_) noexcept(std::is_nothrow_invocable_v<instance_type&, Args_...>)
		{
			return (Get()(std::forward<Args_>(args_)...));
		}

		template<class...Args_>
		requires(std::is_invocable_v<const instance_type&, Args_...>)
		inline decltype(auto) operator()(Args_&&...args_) noexcept(std::is_nothrow_invocable_v<const instance_type&, Args_...>)
		{
			return (GetConst()(std::forward<Args_>(args_)...));
		}
#pragma endregion
	};
}

template<class T_, class Elem_, class Traits_>
std::basic_ostream<Elem_, Traits_>& operator<<(std::basic_ostream<Elem_, Traits_>& str_, EmuCore::Singleton<T_>& singleton_)
{
	str_ << singleton_.Get();
	return str_;
}

template<class T_, class Elem_, class Traits_>
std::basic_ostream<Elem_, Traits_>& operator<<(std::basic_ostream<Elem_, Traits_>& str_, const EmuCore::Singleton<T_>& singleton_)
{
	str_ << singleton_.GetConst();
	return str_;
}

#endif
