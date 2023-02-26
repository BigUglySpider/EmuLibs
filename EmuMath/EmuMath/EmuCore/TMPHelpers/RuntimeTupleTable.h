#ifndef EMU_CORE_RUNTIME_TUPLE_TABLE_H_INC_
#define EMU_CORE_RUNTIME_TUPLE_TABLE_H_INC_ 1

#include <stdexcept>
#include <tuple>
#include <type_traits>

#include "TypeConvertors.h"
#include "Values.h"
#include "../CommonConcepts/StdTypes.h"

namespace EmuCore::TMP
{
    /// <summary>
    /// <para> Executes the passed function with an argument of the element at index Index_ within the passed tuple/ </para>
    /// </summary>
    /// <param name="tuple_">Tuple to pass the selected index of.</param>
    /// <param name="func_">Function to invoke, with an argument of the element at the provided index within `tuple_`.</param>
    /// <returns>Result of executing the passed function on the specified item.</returns>
    template<std::size_t Index_, EmuConcepts::StdTuple Tuple_, class Func_>
    constexpr inline decltype(auto) execute_function_on_tuple_element(Tuple_& tuple_, Func_&& func_)
    {
        using std::get;
        return std::forward<Func_>(func_)(get<Index_>(tuple_));
    }

    /// <summary>
    /// <para> Helper to allow functions to be executed on a tuple at an arbitrary index decided at runtime. </para>
    /// <para> 
    ///     The function may return a non-void type, however all invocations must return the same type (e.g. index 0 cannot return int whilst index 2 returns float). 
    ///     As such, this cannot be used as a runtime version of `get`.
    /// </para>
    /// </summary>
    template<EmuConcepts::StdTuple Tuple_, class Func_>
    class runtime_tuple_table
    {
#pragma region COMMON_BASIC_INFO
    public:
        /// <summary> The instantiated runtime_tuple_type that represents this type. </summary>
        using this_type = runtime_tuple_table<Tuple_, Func_>;
        /// <summary> The type of tuple that this table is constructed for. </summary>
        using tuple_type = Tuple_;
        /// <summary> The number of elements contained within the target tuple type. </summary>
        static constexpr std::size_t num_elements = std::tuple_size_v<tuple_type>;
#pragma endregion

#pragma region COMMON_FUNC_TYPE_INFO
    private:
        static_assert(num_elements > 0, "Invalid tuple type passed to EmuCore::TMP::runtime_tuple_table: The tuple must contain at least 1 element, but the passed tuple type is empty.");
        using _tuple_element_0_type = typename std::tuple_element<0, typename std::remove_cvref<tuple_type>::type>::type;

    public:
        /// <summary> The type resulting from std::forwarding the Func_ type. </summary>
        using func_forward_type = typename EmuCore::TMP::forward_result<Func_>::type;
        /// <summary> 
        /// <para> The type returned when the passed function is called with the 0th element of the passed tuple as an argument. </para>
        /// <para> This is the expected return type from any invocation of Func_ with any element of the target tuple. </para>
        /// </summary>
        using func_return_type = decltype(std::declval<Func_>()(std::declval<_tuple_element_0_type>()));
        /// <summary> The type returned by the arbitrating function used to allow runtime-selected-index calls. Typically identical to func_return_type, but specialisations may choose to approach this differently. </summary>
        using arbitrating_func_return_type = func_return_type;
        /// <summary> Type of the arbitrating function used to allow runtime-selected-index calls. This is returned when accessing via the 1D subscript operator. </summary>
        using arbitrating_func_type = arbitrating_func_return_type(*)(tuple_type& tuple_, func_forward_type forwarded_func_);
#pragma endregion

#pragma region TABLE_CREATION
    private:
        using _arbitrating_func_table_type = std::array<arbitrating_func_type, num_elements>;
        using _index_sequence = std::make_index_sequence<num_elements>;

        template<std::size_t...Indices_>
        [[nodiscard]] static constexpr inline _arbitrating_func_table_type _make_underlying_func_table(std::index_sequence<Indices_...> indices_)
        {
            return _arbitrating_func_table_type
            ({
                (&EmuCore::TMP::execute_function_on_tuple_element<Indices_, tuple_type, Func_>)...
            });
        }
#pragma endregion

#pragma region STL_COMPLIANCE_TYPES
    public:
        /// <summary> Constant forward iterator for STL-style access. </summary>
        using const_iterator = typename _arbitrating_func_table_type::const_iterator;
        /// <summary> Constant reverse iterator for STL-style access. </summary>
        using const_reverse_iterator = typename _arbitrating_func_table_type::const_reverse_iterator;
        /// <summary> Forward iterator for STL-style access; this is identical to const_iterator. </summary>
        using iterator = const_iterator;
        /// <summary> Reverse iterator for STL-style access; this is identical to const_reverse_iterator. </summary>
        using reverse_iterator = const_reverse_iterator;
#pragma endregion

#pragma region UNDERLYING_CHECKS
    private:
        template<std::size_t Unused_>
        [[nodiscard]] static constexpr inline bool _can_default_construct_func()
        {
            return (Unused_ >= 0 || Unused_ <= 0) && std::is_default_constructible_v<Func_>;
        }
#pragma endregion

#pragma region CONSTRUCTORS_AND_ASSIGNMENT_OPERATORS
    public:
        /// <summary>
        /// <para> Initialises this table to support input of runtime index arguments to perform functions on the target tuple. </para>
        /// <para> This constructor does not require explicit invocation. </para>
        /// </summary>
        constexpr inline runtime_tuple_table() noexcept : _func_table(_make_underlying_func_table(_index_sequence()))
        {
        }
        constexpr inline runtime_tuple_table(const this_type&) = delete;
        constexpr inline runtime_tuple_table(this_type&&) = delete;

        constexpr inline this_type& operator=(const this_type&) = delete;
        constexpr inline this_type& operator=(this_type&&) = delete;
#pragma endregion

#pragma region EXECUTORS
    public:
        /// <summary>
        /// <para> Executes `func_` with an argument of `tuple_`'s element at the passed compile-time `Index_`, with a safety bounds check. </para>
        /// <para> A compile-time bounds check will be performed. If the check fails, a static_assert will be triggered to prevent compilation. </para>
        /// </summary>
        /// <param name="tuple_">Tuple to invoke the function on an element of.</param>
        /// <param name="func_">Function to be invoked.</param>
        /// <returns>Result of the invocation of `func_`.</returns>
        template<std::size_t Index_>
        constexpr inline func_return_type Execute(tuple_type& tuple_, Func_ func_) const
        {
            if constexpr (Index_ < num_elements)
            {
                using std::get;
                return func_(get<Index_>(tuple_));
            }
            else
            {
                static_assert
                (
                    EmuCore::TMP::get_false<std::size_t, Index_>(),
                    "Invalid Index_ argument to EmuCore::TMP::runtime_tuple_table::Execute with compile-time index argument: The index is greater than the highest index within the tuple."
                );
            }
        }

        /// <summary>
        /// <para> Invokes a default-constructed Func_ with an argument of `tuple_`'s element at the passed compile-time `Index_`, with a safety bounds check. </para>
        /// <para> A compile-time bounds check will be performed. If the check fails, a static_assert will be triggered to prevent compilation. </para>
        /// </summary>
        /// <param name="tuple_">Tuple to invoke the function on an element of.</param>
        /// <returns>Result of the invocation of a default-constructed Func_.</returns>
        template<std::size_t Index_, typename = std::enable_if_t<_can_default_construct_func<Index_>()>>
        constexpr inline func_return_type Execute(tuple_type& tuple_) const
        {
            if constexpr (Index_ < num_elements)
            {
                using std::get;
                return Func_()(get<Index_>(tuple_));
            }
            else
            {
                static_assert
                (
                    EmuCore::TMP::get_false<std::size_t, Index_>(),
                    "Invalid Index_ argument to EmuCore::TMP::runtime_tuple_table::Execute with compile-time index argument: The index is greater than the highest index within the tuple."
                );
            }
        }

        /// <summary>
        /// <para> Executes `func_` with an argument of `tuple_`'s element at the passed `index_`, with a safety bounds check. </para>
        /// <para> A `std::out_of_range` exception will be thrown if `index_` is greater than the number of elements in the tuple type. </para>
        /// </summary>
        /// <param name="tuple_">Tuple to invoke the function on an element of.</param>
        /// <param name="func_">Function to be invoked.</param>
        /// <param name="index_">Index of the tuple element to use as the argument to `func_`.</param>
        /// <returns>Result of the invocation of `func_`.</returns>
        constexpr inline func_return_type Execute(const std::size_t index_, tuple_type& tuple_, Func_ func_) const
        {
            if (index_ < num_elements)
            {
                return _func_table[index_](tuple_, std::forward<Func_>(func_));
            }
            else
            {
                throw std::out_of_range("Invalid index_ argument to EmuCore::TMP::runtime_tuple_table::Execute with runtime index argument: The index is greater than the highest index within the tuple.");
            }
        }

        /// <summary>
        /// <para> Invokes a default-constructed Func_ with an argument of `tuple_`'s element at the passed `index_`, with a safety bounds check. </para>
        /// <para> A `std::out_of_range` exception will be thrown if `index_` is greater than the number of elements in the tuple type. </para>
        /// <para> Only available if `Func_` may be default constructed. </para>
        /// </summary>
        /// <param name="tuple_">Tuple to invoke the function on an element of.</param>
        /// <param name="index_">Index of the tuple element to use as the argument to the function.</param>
        /// <returns>Result of the invocation of a default-constructed Func_.</returns>
        template<std::size_t Unused_ = 0, typename = std::enable_if_t<_can_default_construct_func<Unused_>()>>
        constexpr inline func_return_type Execute(const std::size_t index_, tuple_type& tuple_) const
        {
            if (index_ < num_elements)
            {
                return _func_table[index_](tuple_, Func_());
            }
            else
            {
                throw std::out_of_range("Invalid index_ argument to EmuCore::TMP::runtime_tuple_table::Execute with runtime index argument: The index is greater than the highest index within the tuple.");
            }
        }

        /// <summary>
        /// <para> Executes `func_` with an argument of `tuple_`'s element at the passed `index_`. </para>
        /// <para> No safety bounds checks are performed. </para>
        /// </summary>
        /// <param name="tuple_">Tuple to invoke the function on an element of.</param>
        /// <param name="func_">Function to be invoked.</param>
        /// <param name="index_">Index of the tuple element to use as the argument to `func_`.</param>
        /// <returns>Result of the invocation of `func_`.</returns>
        constexpr inline func_return_type ExecuteNoBoundsCheck(const std::size_t index_, tuple_type& tuple_, Func_ func_) const noexcept
        {
            return _func_table[index_](tuple_, std::forward<Func_>(func_));
        }

        /// <summary>
        /// <para> Invokes a default-constructed Func_ with an argument of `tuple_`'s element at the passed `index_`. </para>
        /// <para> No safety bounds checks are performed. </para>
        /// <para> Only available if `Func_` may be default constructed. </para>
        /// </summary>
        /// <param name="tuple_">Tuple to invoke the function on an element of.</param>
        /// <param name="index_">Index of the tuple element to use as the argument to the function.</param>
        /// <returns>Result of the invocation of a default-constructed Func_.</returns>
        template<std::size_t Unused_ = 0, typename = std::enable_if_t<_can_default_construct_func<Unused_>()>>
        constexpr inline func_return_type ExecuteNoBoundsCheck(const std::size_t index_, tuple_type& tuple_) const noexcept
        {
            return _func_table[index_](tuple_, Func_());
        }

        /// <summary>
        /// <para> Shorthand for `Execute` with a runtime index argument, performing execution with a safety bounds check. </para>
        /// </summary>
        /// <param name="tuple_">Tuple to invoke the function on an element of.</param>
        /// <param name="func_">Function to be invoked.</param>
        /// <param name="index_">Index of the tuple element to use as the argument to `func_`.</param>
        /// <returns>Result of the invocation of `func_`.</returns>
        constexpr inline func_return_type operator()(const std::size_t index_, tuple_type& tuple_, Func_ func_) const
        {
            if (index_ < num_elements)
            {
                return _func_table[index_](tuple_, std::forward<Func_>(func_));
            }
            else
            {
                throw std::out_of_range("Invalid index_ argument to EmuCore::TMP::runtime_tuple_table::operator() with runtime index argument: The index is greater than the highest index within the tuple.");
            }
        }

        /// <summary>
        /// <para> Shorthand for `Execute` with a runtime index argument, performing execution with a safety bounds check. </para>
        /// <para> Only available if `Func_` may be default constructed. </para>
        /// </summary>
        /// <param name="tuple_">Tuple to invoke the function on an element of.</param>
        /// <param name="index_">Index of the tuple element to use as the argument to the function.</param>
        /// <returns>Result of the invocation of a default-constructed Func_.</returns>
        template<std::size_t Unused_ = 0, typename = std::enable_if_t<_can_default_construct_func<Unused_>()>>
        constexpr inline func_return_type operator()(const std::size_t index_, tuple_type& tuple_) const
        {
            if (index_ < num_elements)
            {
                return _func_table[index_](tuple_, Func_());
            }
            else
            {
                throw std::out_of_range("Invalid index_ argument to EmuCore::TMP::runtime_tuple_table::operator() with runtime index argument: The index is greater than the highest index within the tuple.");
            }
        }
#pragma endregion

#pragma region ACCESSORS
    public:
        /// <summary>
        /// <para> Directly access the arbitrating function for the specified index within the target tuple. </para>
        /// <para> A compile-time bounds check will be performed. If the check fails, a static_assert will be triggered to prevent compilation. </para>
        /// </summary>
        /// <returns>Constant reference to the arbitrating function for the specified index within the target tuple.</returns>
        template<std::size_t Index_>
        [[nodiscard]] constexpr inline const arbitrating_func_type& at() const noexcept
        {
            if constexpr (Index_ < num_elements)
            {
                return _func_table[Index_];
            }
            else
            {
                static_assert
                (
                    EmuCore::TMP::get_false<std::size_t, Index_>(),
                    "Invalid Index_ argument to EmuCore::TMP::runtime_tuple_table::at with compile-time index argument: The index is greater than the highest index within the tuple."
                );
            }
        }

        /// <summary>
        /// <para> Directly access the arbitrating function for the specified index within the target tuple. </para>
        /// <para> A `std::out_of_range` exception will be thrown if `index_` is greater than the number of elements in the tuple type. </para>
        /// </summary>
        /// <returns>Constant reference to the arbitrating function for the specified index within the target tuple.</returns>
        constexpr inline const arbitrating_func_type& at(const std::size_t index_) const
        {
            if (index_ < num_elements)
            {
                return _func_table[index_];
            }
            else
            {
                throw std::out_of_range("Invalid index_ argument to EmuCore::TMP::runtime_tuple_table::at with runtime index argument: The index is greater than the highest index within the tuple.");
            }
        }

        /// <summary>
        /// <para> Directly access the arbitrating function for the specified index within the target tuple. </para>
        /// <para> No safety bounds checks are performed. </para>
        /// </summary>
        /// <returns>Constant reference to the arbitrating function for the specified index within the target tuple.</returns>
        constexpr inline const arbitrating_func_type& operator[](const std::size_t index_) const noexcept
        {
            return _func_table[index_];
        }
#pragma endregion

#pragma region STL_INFO
        [[nodiscard]] static constexpr inline std::size_t size() noexcept
        {
            return num_elements;
        }
#pragma endregion

#pragma region STL_ACCESS
        [[nodiscard]] constexpr inline iterator begin() noexcept
        {
            return _func_table.begin();
        }

        [[nodiscard]] constexpr inline const_iterator begin() const noexcept
        {
            return _func_table.cbegin();
        }

        [[nodiscard]] constexpr inline iterator end() noexcept
        {
            return _func_table.end();
        }

        [[nodiscard]] constexpr inline const_iterator end() const noexcept
        {
            return _func_table.cend();
        }

        [[nodiscard]] constexpr inline reverse_iterator rbegin() noexcept
        {
            return _func_table.rbegin();
        }

        [[nodiscard]] constexpr inline const_reverse_iterator rbegin() const noexcept
        {
            return _func_table.crbegin();
        }

        [[nodiscard]] constexpr inline reverse_iterator rend() noexcept
        {
            return _func_table.rend();
        }

        [[nodiscard]] constexpr inline const_reverse_iterator rend() const noexcept
        {
            return _func_table.crend();
        }

        [[nodiscard]] constexpr inline const_iterator cbegin() const noexcept
        {
            return _func_table.cbegin();
        }

        [[nodiscard]] constexpr inline const_iterator cend() const noexcept
        {
            return _func_table.cend();
        }

        [[nodiscard]] constexpr inline const_reverse_iterator crbegin() const noexcept
        {
            return _func_table.crbegin();
        }

        [[nodiscard]] constexpr inline const_reverse_iterator crend() const noexcept
        {
            return _func_table.crend();
        }
#pragma endregion

#pragma region DATA
    private:
        const _arbitrating_func_table_type _func_table;
#pragma endregion
    };
}

#endif
