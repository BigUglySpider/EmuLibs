#ifndef EMU_CORE_TMP_HELPERS_UNIQUE_VOID_HPP_INC_
#define EMU_CORE_TMP_HELPERS_UNIQUE_VOID_HPP_INC_ 1

#include <functional>
#include <memory>
#include <stdexcept>
#include <typeindex>
#include <type_traits>
#include <utility>

#include <any>

namespace EmuCore::TMP
{
#pragma region UNIQUE_VOID_PTR_TYPES
	template<bool IsConst_>
	class unique_void_ptr_template
	{
	private:
		template<typename T_>
		[[nodiscard]] static inline decltype(auto) _make_type_info()
		{
			return std::make_unique<std::type_index>(typeid(T_));
		}

	public:
		/// <summary>
		/// <para> The un-pointered `void` type used by this unique_void_ptr type. </para>
		/// <para> Either `const void`, or `void`. </para>
		/// </summary>
		using element_type = typename std::conditional<IsConst_, const void, void>::type;;
		/// <summary>
		/// <para> The void pointer reprsented by this unique_void_ptr type. </para>
		/// <para> Either `const void*`, or `void*`. </para>
		/// </summary>
		using pointer_type = typename std::add_pointer<element_type>::type;
		/// <summary>
		/// <para> The type used as a deleter for this unique_void_ptr type. </para>
		///	<para> Either a void-returning function which takes a `const void*` argument, or a void-returning function which takes a `void*` argument. </para>
		/// </summary>
		using deleter_type = std::function<void(pointer_type)>;

		/// <summary>
		/// <para> Performs a static_assert to ensure the input pointer type is valid to provide to this type. </para>
		/// <para> Covers common requirements for this type, such as disallowing raw arrays and requiring correct const states. </para>
		/// <para>
		///		To check output types, use `is_invalid_cast_type` or `is_valid_cast_type`. 
		///		Be aware that output type checks are runtime-only as they require information regarding the currently-contained type.
		/// </para>
		/// </summary>
		template<typename T_>
		static constexpr inline void assert_valid_pointer_input_type()
		{
			static_assert
			(
				!std::is_array_v<T_>,
				"unique_void_ptr: Attempted to provide with a raw array pointer. Raw arrays are not supported by this type; please use a deferred type such as std::array or std::vector."
			);

			static_assert
			(
				IsConst_ || !std::is_const_v<T_>,
				"unique_void_ptr: Attempted to provide a const-qualified pointer to a non-const unique_void_ptr. Const-qualified pointers may only be provided directly to a unique_const_void_ptr."
			);
		}

		/// <summary>
		/// <para> Deleter used by default for the data held by this Void Pointer type. </para>
		/// <para> Does the job for most supported items. You'll only need to provide a custom deleter other than this if you need to do extra work before-or-after deletion. </para>
		/// </summary>
		template<class T_>
		struct default_deleter
		{
			constexpr default_deleter() noexcept = default;
			constexpr default_deleter(const default_deleter<T_>&) noexcept = default;
			constexpr default_deleter(default_deleter<T_>&&) noexcept = default;
			constexpr default_deleter<T_>& operator=(const default_deleter<T_>&) noexcept = default;
			constexpr default_deleter<T_>& operator=(default_deleter<T_>&&) noexcept = default;

			inline void operator()(void* data_) const
			{
				delete reinterpret_cast<T_*>(data_);
			}

			inline void operator()(const void* data_) const
			{
				delete reinterpret_cast<const T_*>(data_);
			}
		};

		unique_void_ptr_template(const unique_void_ptr_template<IsConst_>&) = delete;
		unique_void_ptr_template<IsConst_>& operator=(const unique_void_ptr_template<IsConst_>&) = delete;

		unique_void_ptr_template() noexcept :
			_pointer(nullptr),
			_type_info(nullptr)
		{
		}
		unique_void_ptr_template(unique_void_ptr_template<IsConst_>&&) noexcept = default;
		unique_void_ptr_template<IsConst_>& operator=(unique_void_ptr_template<IsConst_>&&) noexcept = default;

		template<class T_>
		explicit inline unique_void_ptr_template(T_* pointer_) noexcept :
			_type_info(_make_type_info<T_>()),
			_pointer(pointer_, default_deleter<T_>())
		{
			assert_valid_pointer_input_type<T_>();
		}

		template<class T_>
		requires(IsConst_)
		explicit inline unique_void_ptr_template(const T_* pointer_) noexcept :
			_type_info(_make_type_info<T_>()),
			_pointer(const_cast<T_*>(pointer_), default_deleter<T_>())
		{
			assert_valid_pointer_input_type<T_>();
		}

		template<class T_>
		explicit inline unique_void_ptr_template(T_* pointer_, deleter_type deleter_func_) noexcept :
			_type_info(_make_type_info<T_>()),
			_pointer(pointer_, deleter_func_)
		{
			assert_valid_pointer_input_type<T_>();
		}

		template<class T_>
		requires(IsConst_)
		explicit inline unique_void_ptr_template(const T_* pointer_, deleter_type deleter_func_) noexcept :
			_type_info(_make_type_info<T_>()),
			_pointer(const_cast<T_*>(pointer_), deleter_func_)
		{
			assert_valid_pointer_input_type<T_>();
		}

		template<class T_>
		[[nodiscard]] inline bool is_invalid_cast_type() const noexcept
		{
			return
			(
				(!_type_info) ||
				!(std::is_void_v<T_> || ((*_type_info) == typeid(T_)))
			);
		}

		template<class T_>
		[[nodiscard]] inline bool is_valid_cast_type() const noexcept
		{
			return !is_invalid_cast_type<T_>();
		}

		[[nodiscard]] inline operator bool() const noexcept
		{
			return _pointer.operator bool();
		}

		template<class T_ = element_type>
		[[nodiscard]] inline T_* get() noexcept(std::is_void_v<T_>)
		{
			static_assert
			(
				std::is_const_v<T_> || !IsConst_,
				"Attempted to retrieve a pointer that is not const-qualified from a unique_const_void_ptr. Only const-qualified pointers may be retrieved from unique_const_void_ptr."
			);

			if constexpr (std::is_void_v<T_>)
			{
				return _pointer.get();
			}
			else
			{
				if (is_invalid_cast_type<T_>())
				{
					throw std::bad_cast();
				}
				return reinterpret_cast<T_*>(_pointer.get());
			}
		}

		template<class T_ = element_type>
		[[nodiscard]] inline const T_* get() const noexcept(std::is_void_v<T_>)
		{
			if constexpr (std::is_void_v<T_>)
			{
				return _pointer.get();
			}
			else
			{
				if (is_invalid_cast_type<T_>())
				{
					throw std::bad_cast();
				}
				return reinterpret_cast<const T_*>(_pointer.get());
			}
		}

		[[nodiscard]] inline deleter_type& get_deleter() noexcept
		{
			return _pointer.get_deleter();
		}

		[[nodiscard]] inline const deleter_type& get_deleter() const noexcept
		{
			return _pointer.get_deleter();
		}

		template<class T_ = element_type>
		[[nodiscard]] inline T_* release() noexcept
		{
			static_assert
			(
				std::is_const_v<T_> || !IsConst_,
				"Attempted to release a pointer that is not const-qualified from a unique_const_void_ptr. Only const-qualified pointers may be retrieved from unique_const_void_ptr."
			);
			if (is_invalid_cast_type<T_>())
			{
				throw std::bad_cast();
			}
			_type_info.reset();
			return _pointer.release();
		}

		inline void reset()
		{
			_pointer.reset(nullptr);
			_type_info.reset(nullptr);
		}

		template<class T_>
		inline void reset(T_* new_pointer_)
		{
			reset(new_pointer_, default_deleter<T_>());
		}

		template<class T_>
		requires(IsConst_)
		inline void reset(const T_* new_pointer_)
		{
			reset(new_pointer_, default_deleter<T_>());
		}

		template<class T_>
		inline void reset(T_* new_pointer_, deleter_type new_deleter_)
		{
			assert_valid_pointer_input_type<T_>();
			_pointer.reset(new_pointer_);
			_pointer.get_deleter() = new_deleter_;
			_type_info.reset(_make_type_info<T_>());
		}

		template<class T_>
		requires(IsConst_)
		inline void reset(const T_* new_pointer_, deleter_type new_deleter_)
		{
			assert_valid_pointer_input_type<T_>();
			_pointer.reset(const_cast<T_*>(new_pointer_));
			_pointer.get_deleter() = new_deleter_;
			_type_info.reset(_make_type_info<T_>());
		}

		inline void swap(unique_void_ptr_template<IsConst_>& other_) noexcept
		{
			_pointer.swap(other_._pointer);
			_type_info.swap(other_._type_info);
		}

		template<class T_>
		inline void swap(std::unique_ptr<T_>& other_, deleter_type new_deleter_)
		{
			assert_valid_pointer_input_type<T_>();
			if (is_invalid_cast_type<T_>())
			{
				throw std::bad_cast();
			}
			T_* other_pointer = other_.release();
			other_.reset(reinterpret_cast<T_*>(_pointer.release()));
			this->reset(other_pointer, new_deleter_);
		}

		template<class T_>
		inline void swap(std::unique_ptr<T_>& other_)
		{
			swap(other_, default_deleter<T_>());
		}

	private:
		std::unique_ptr<element_type, deleter_type> _pointer;
		std::unique_ptr<std::type_index> _type_info;
	};

	using unique_void_ptr = unique_void_ptr_template<false>;
	using unique_const_void_ptr = unique_void_ptr_template<true>;
#pragma endregion

#pragma region MAKE_UNIQUE_VOID_FUNCS
	template<class T_, class...TConstructorArgs_>
	requires(!std::is_const_v<T_>)
	[[nodiscard]] inline unique_void_ptr make_unique_void_custom_deleter(unique_void_ptr::deleter_type custom_deleter_func_, TConstructorArgs_&&...constructor_args_for_type_t_)
	{
		static_assert
		(
			!std::is_array_v<T_>,
			"Attempted to invoke `make_unique_void_custom_deleter` with a raw array type to be held in the pointer. Raw arrays are not supported for this."
		);
		return unique_void_ptr
		(
			new T_(std::forward<TConstructorArgs_>(constructor_args_for_type_t_)...),
			custom_deleter_func_
		);
	}

	template<class T_, class...TConstructorArgs_>
	requires(!std::is_const_v<T_>)
	[[nodiscard]] inline unique_void_ptr make_unique_void(TConstructorArgs_&&...constructor_args_for_type_t_)
	{
		static_assert
		(
			!std::is_array_v<T_>,
			"Attempted to invoke `make_unique_void` with a raw array type to be held in the pointer. Raw arrays are not supported for this."
		);
		return unique_void_ptr
		(
			new T_(std::forward<TConstructorArgs_>(constructor_args_for_type_t_)...)
		);
	}

	template<class T_, class...TConstructorArgs_>
	requires(!std::is_const_v<T_>)
	[[nodiscard]] inline unique_const_void_ptr make_unique_const_void_custom_deleter(unique_const_void_ptr::deleter_type custom_deleter_func_, TConstructorArgs_&&...constructor_args_for_type_t_)
	{
		static_assert
		(
			!std::is_array_v<T_>,
			"Attempted to invoke `make_unique_const_void_custom_deleter` with a raw array type to be held in the pointer. Raw arrays are not supported for this."
		);
		return unique_const_void_ptr
		(
			new T_(std::forward<TConstructorArgs_>(constructor_args_for_type_t_)...),
			custom_deleter_func_
		);
	}

	template<class T_, class...TConstructorArgs_>
	requires(!std::is_const_v<T_>)
	[[nodiscard]] inline unique_const_void_ptr make_unique_const_void(TConstructorArgs_&&...constructor_args_for_type_t_)
	{
		static_assert
		(
			!std::is_array_v<T_>,
			"Attempted to invoke `make_unique_const_void_custom_deleter` with a raw array type to be held in the pointer. Raw arrays are not supported for this."
		);
		return unique_const_void_ptr
		(
			new T_(std::forward<TConstructorArgs_>(constructor_args_for_type_t_)...)
		);
	}
#pragma endregion

#pragma region SWAPS
	/// <summary>
	/// <para> Swaps the data and associated deleter + type information for the two Unique Void Pointers. </para>
	/// </summary>
	/// <param name="a_">Reference to a Unique Void Pointer to move `b_` into.</param>
	/// <param name="b_">Reference to a Unique Void Pointer to move `a_` into.</param>
	inline void swap(unique_void_ptr& a_, unique_void_ptr& b_) noexcept
	{
		a_.swap(b_);
	}

	/// <summary>
	/// <para> Swaps the data and associated deleter for the two Unique pointers. </para>
	/// <para> Unique Void Pointer `a_` will have its type information updated. </para>
	/// <para> Unique Void Pointer `a_` will have its deleter set to the default Unique Void Pointer Deleter for type T_. </para>
	/// <para> Throws a std::bad_cast if the type held in `b_` is not the type held in `a_`. </para>
	/// </summary>
	/// <param name="a_">Reference to a Unique Void Pointer to move `b_` into.</param>
	/// <param name="b_">Reference to a Unique Pointer to move `a_` into. Must hold a pointer to the type held by `a_`, otherwise a std::bad_cast will be thrown.</param>
	template<class T_>
	inline void swap(unique_void_ptr& a_, std::unique_ptr<T_>& b_)
	{
		a_.swap(b_);
	}

	/// <summary>
	/// <para> Swaps the data and associated deleter for the two Unique pointers. </para>
	/// <para> Unique Void Pointer `b_` will have its type information updated. </para>
	/// <para> Unique Void Pointer `b_` will have its deleter set to the default Unique Void Pointer Deleter for type T_. </para>
	/// <para> Throws a std::bad_cast if the type held in `a_` is not the type held in `b_`. </para>
	/// </summary>
	/// <param name="a_">Reference to a Unique Pointer to move `b_` into. Must hold a pointer to the type held by `a_`, otherwise a std::bad_cast will be thrown.</param>
	/// <param name="b_">Reference to a Unique Void Pointer to move `a_` into.</param>
	template<class T_>
	inline void swap(std::unique_ptr<T_>& a_, unique_void_ptr& b_)
	{
		b_.swap(a_);
	}

	/// <summary>
	/// <para> Swaps the data and associated deleter + type information for the two Unique Const Void Pointers. </para>
	/// </summary>
	/// <param name="a_">Reference to a Unique Const Void Pointer to move `b_` into.</param>
	/// <param name="b_">Reference to a Unique Const Void Pointer to move `a_` into.</param>
	inline void swap(unique_const_void_ptr& a_, unique_const_void_ptr& b_) noexcept
	{
		a_.swap(b_);
	}

	/// <summary>
	/// <para> Swaps the data and associated deleter for the two Unique pointers. </para>
	/// <para> Unique Const Void Pointer `a_` will have its type information updated. </para>
	/// <para> Unique Const Void Pointer `a_` will have its deleter set to the default Unique Const Void Pointer Deleter for type T_. </para>
	/// <para> Throws a std::bad_cast if the type held in `b_` is not the type held in `a_`. </para>
	/// </summary>
	/// <param name="a_">Reference to a Unique Const Void Pointer to move `b_` into.</param>
	/// <param name="b_">Reference to a Unique Pointer to move `a_` into. Must hold a pointer to the type held by `a_`, otherwise a std::bad_cast will be thrown.</param>
	template<class T_>
	inline void swap(unique_const_void_ptr& a_, std::unique_ptr<T_>& b_)
	{
		a_.swap(b_);
	}

	/// <summary>
	/// <para> Swaps the data and associated deleter for the two Unique pointers. </para>
	/// <para> Unique Const Void Pointer `b_` will have its type information updated. </para>
	/// <para> Unique Const Void Pointer `b_` will have its deleter set to the default Unique Const Void Pointer Deleter for type T_. </para>
	/// <para> Throws a std::bad_cast if the type held in `a_` is not the type held in `b_`. </para>
	/// </summary>
	/// <param name="a_">Reference to a Unique Pointer to move `b_` into. Must hold a pointer to the type held by `a_`, otherwise a std::bad_cast will be thrown.</param>
	/// <param name="b_">Reference to a Unique Const Void Pointer to move `a_` into.</param>
	template<class T_>
	inline void swap(std::unique_ptr<T_>& a_, unique_const_void_ptr& b_)
	{
		b_.swap(a_);
	}

	/// <summary>
	/// <para> Swaps the data and associated deleter for the two Unique pointers. </para>
	/// <para> Unique Void Pointer `a_` will have its type information updated. </para>
	/// <para> Throws a std::bad_cast if the type held in `b_` is not the type held in `a_`. </para>
	/// </summary>
	/// <param name="a_">Reference to a Unique Void Pointer to move `b_` into.</param>
	/// <param name="b_">Reference to a Unique Pointer to move `a_` into. Must hold a pointer to the type held by `a_`, otherwise a std::bad_cast will be thrown.</param>
	/// <param name="new_custom_deleter_for_a_">Custom deleter that will be provided for a_ after the swap.</param>
	template<class T_>
	inline void swap(unique_void_ptr& a_, std::unique_ptr<T_>& b_, unique_void_ptr::deleter_type new_custom_deleter_for_a_)
	{
		a_.swap(b_, new_custom_deleter_for_a_);
	}

	/// <summary>
	/// <para> Swaps the data and associated deleter for the two Unique pointers. </para>
	/// <para> Unique Void Pointer `b_` will have its type information updated. </para>
	/// <para> Throws a std::bad_cast if the type held in `a_` is not the type held in `b_`. </para>
	/// </summary>
	/// <param name="a_">Reference to a Unique Pointer to move `b_` into. Must hold a pointer to the type held by `a_`, otherwise a std::bad_cast will be thrown.</param>
	/// <param name="b_">Reference to a Unique Void Pointer to move `a_` into.</param>
	/// <param name="new_custom_deleter_for_b_">Custom deleter that will be provided for b_ after the swap.</param>
	template<class T_>
	inline void swap(std::unique_ptr<T_>& a_, unique_void_ptr& b_, unique_void_ptr::deleter_type new_custom_deleter_for_b_)
	{
		b_.swap(a_, new_custom_deleter_for_b_);
	}

	/// <summary>
	/// <para> Swaps the data and associated deleter for the two Unique pointers. </para>
	/// <para> Unique Const Void Pointer `a_` will have its type information updated. </para>
	/// <para> Throws a std::bad_cast if the type held in `b_` is not the type held in `a_`. </para>
	/// </summary>
	/// <param name="a_">Reference to a Unique Const Void Pointer to move `b_` into.</param>
	/// <param name="b_">Reference to a Unique Pointer to move `a_` into. Must hold a pointer to the type held by `a_`, otherwise a std::bad_cast will be thrown.</param>
	/// <param name="new_custom_deleter_for_a_">Custom deleter that will be provided for a_ after the swap.</param>
	template<class T_>
	inline void swap(unique_const_void_ptr& a_, std::unique_ptr<T_>& b_, unique_const_void_ptr::deleter_type new_custom_deleter_for_a_)
	{
		a_.swap(b_, new_custom_deleter_for_a_);
	}

	/// <summary>
	/// <para> Swaps the data and associated deleter for the two Unique pointers. </para>
	/// <para> Unique Const Void Pointer `b_` will have its type information updated. </para>
	/// <para> Throws a std::bad_cast if the type held in `a_` is not the type held in `b_`. </para>
	/// </summary>
	/// <param name="a_">Reference to a Unique Pointer to move `b_` into. Must hold a pointer to the type held by `a_`, otherwise a std::bad_cast will be thrown.</param>
	/// <param name="b_">Reference to a Unique Const Void Pointer to move `a_` into.</param>
	/// <param name="new_custom_deleter_for_b_">Custom deleter that will be provided for b_ after the swap.</param>
	template<class T_>
	inline void swap(std::unique_ptr<T_>& a_, unique_const_void_ptr& b_, unique_void_ptr::deleter_type new_custom_deleter_for_b_)
	{
		b_.swap(a_, new_custom_deleter_for_b_);
	}
#pragma endregion
}

namespace std
{
	using EmuCore::TMP::swap;
}

#endif
