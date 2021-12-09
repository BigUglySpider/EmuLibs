#ifndef EMU_CORE_DEFERRABLE_REFERENCE_WRAPPER_H_INC_
#define EMU_CORE_DEFERRABLE_REFERENCE_WRAPPER_H_INC_

#include "../TMPHelpers/TypeComparators.h"
#include "../TMPHelpers/TypeConvertors.h"
#include <functional>

namespace EmuCore
{
	/// <summary>
	/// <para> Reference wrapper which may be used to assign a reference after the reference's construction. </para>
	/// <para>
	///		This is not recommended for general use, and should only be used for internals which may have a deferred accesss to their references, 
	///		and receive their references still by the end of the construction body function (e.g. reference not available during init, but available after).
	/// </para>
	/// <para> In all other scenarios, it is recommended to use the standard std::reference_wrapper&lt;T&gt; to maintain safety and avoid null references. </para>
	/// <para> This wrapper may implicitly be considered a std::reference_wrapper&lt;T&gt;, but be aware that this results in a new wrapper being constructed. </para>
	/// <para>
	///		FOR SPECIALISATIONS: These wrappers are designed to not be directly-assignable as a normal reference would be; 
	///		implementations contrary to this will make the program ill-formed for any use of said implementation with any Emu libraries.
	/// </para>
	/// </summary>
	/// <typeparam name="T">Type to be referenced by this wrapper. Should not be a reference type; the reference is applied automatically.</typeparam>
	template<typename T>
	struct DeferrableReferenceWrapper
	{
	public:
		/// <summary> The instantiated type that this reference wrapper is. </summary>
		using this_type = DeferrableReferenceWrapper<T>;
		/// <summary> The type that this wrapper references. </summary>
		using value_type = T;
		/// <summary> The expected reference type when using this wrapper as a reference. </summary>
		using reference_type = T&;
		/// <summary> The std::reference_wrapper alternative to this wrapper. </summary>
		using std_wrapper = std::reference_wrapper<T>;

		static constexpr bool is_const = std::is_const_v<value_type>;

		constexpr DeferrableReferenceWrapper() : ptr_(nullptr)
		{
		}
		constexpr DeferrableReferenceWrapper(T& val_) : ptr_(&val_)
		{
		}

		constexpr DeferrableReferenceWrapper(T&&) = delete;

		constexpr DeferrableReferenceWrapper(this_type& to_copy_) : ptr_(to_copy_.ptr_)
		{
		}

		constexpr DeferrableReferenceWrapper(const this_type& to_copy_) : ptr_(to_copy_.ptr_)
		{
			static_assert(is_const, "Attempted to construct a DeferrableReferenceWrapper via a const-copy, but the contained reference is not const.");
		}

		constexpr DeferrableReferenceWrapper(std_wrapper& std_to_copy_) : ptr_(&(std_to_copy_.get()))
		{
		}

		constexpr DeferrableReferenceWrapper(const std_wrapper& std_to_copy_) : ptr_(&(std_to_copy_.get()))
		{
			static_assert(is_const, "Attempted to construct a DeferrableReferenceWrapper via a const-copy, but the contained reference is not const.");
		}

		constexpr inline operator T& ()
		{
			return *ptr_;
		}
		constexpr inline operator const T& () const
		{
			return *ptr_;
		}
		[[nodiscard]] constexpr inline operator std_wrapper()
		{
			return std_wrapper(*ptr_);
		}

		[[nodiscard]] constexpr inline T& get()
		{
			return *ptr_;
		}
		[[nodiscard]] constexpr inline const T& get() const
		{
			return *ptr_;
		}

		/// <summary>
		/// <para> Boolean indicating if this reference is currently assigned. </para>
		/// <para> This will be true even if the reference is dangling. It is only a simple check to determine if a memory address is currently being referenced. </para>
		/// </summary>
		[[nodiscard]] constexpr inline bool Assigned() const
		{
			return ptr_ != nullptr;
		}

		constexpr inline void Set(reference_type ref_)
		{
			ptr_ = &ref_;
		}

		constexpr inline this_type& operator=(DeferrableReferenceWrapper<T>& toSetTo_)
		{
			ptr_ = toSetTo_.ptr_;
			return *this;
		}

		constexpr inline this_type& operator=(const DeferrableReferenceWrapper<T>& toSetTo_)
		{
			if constexpr (is_const)
			{
				ptr_ = toSetTo_.ptr_;
				return *this;
			}
			else
			{
				static_assert(is_const, "Attempted to assign a DeferrableReferenceWrapper via a const-copy, but the contained reference is not const.");
			}
		}

		constexpr inline this_type& operator=(std_wrapper& toSetTo_)
		{
			ptr_ = &(toSetTo_.get());
			return *this;
		}

		constexpr inline this_type& operator=(const std_wrapper& toSetTo_)
		{
			if constexpr (is_const)
			{
				ptr_ = &(toSetTo_.get());
				return *this;
			}
			else
			{
				static_assert(is_const, "Attempted to assign a DeferrableReferenceWrapper via a const-copy, but the contained reference is not const.");
			}
		}


		template<typename...Args_>
		constexpr inline std::invoke_result_t<T&, Args_...> operator()(Args_&&...args_) const
		{
			return std::invoke(*ptr_, std::forward<Args_>(args_)...);
		}

	private:
		T* ptr_;
	};
}

namespace EmuCore::TMP
{
	template<typename T_>
	struct is_reference_wrapper<EmuCore::DeferrableReferenceWrapper<T_>>
	{
		static constexpr bool value = true;
	};

	template<class T_>
	struct get_reference_wrapper_contained_type<EmuCore::DeferrableReferenceWrapper<T_>>
	{
		using type = typename EmuCore::DeferrableReferenceWrapper<T_>::value_type;
	};
}

#endif
