#ifndef EMU_CORE_RUNTIME_TUPLE_TABLE_H_INC_
#define EMU_CORE_RUNTIME_TUPLE_TABLE_H_INC_ 1

#include <stdexcept>
#include <tuple>
#include <type_traits>

#include "TypeConvertors.h"
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
    constexpr inline auto execute_function_on_tuple_element(Tuple_& tuple_, Func_&& func_)
        -> decltype(std::forward<Func_>(func_)(tuple_))
    {
        return std::forward<Func_>(func_)(std::get<Index_>(tuple_));
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
    public:
        using this_type = runtime_tuple_table<Tuple_, Func_>;
        using tuple_type = Tuple_;
        static constexpr std::size_t num_elements = std::tuple_size_v<tuple_type>;
        using func_forward_type = typename EmuCore::TMP::forward_result<Func_>::type;
        using func_return_type = decltype(std::declval<Func_>()(std::declval<tuple_type&>()));

    private:
        using _arbitrating_func_return_type = func_return_type;
        using _arbitrating_func_type = _arbitrating_func_return_type(*)(tuple_type&, func_forward_type);
        using _arbitrating_func_table_type = std::array<_arbitrating_func_type, num_elements>;
        using _index_sequence = std::make_index_sequence<num_elements>;

        template<std::size_t...Indices_>
        [[nodiscard]] static constexpr inline _arbitrating_func_table_type _make_underlying_func_table(std::index_sequence<Indices_...> indices_)
        {
            return _arbitrating_func_table_type
            ({
                (&EmuCore::TMP::execute_function_on_tuple_element<Indices_, tuple_type, Func_>)...
            });
        }

        const _arbitrating_func_table_type _func_table;

    public:
        constexpr inline runtime_tuple_table() noexcept : _func_table(_make_underlying_func_table(_index_sequence()))
        {
        }
        constexpr inline runtime_tuple_table(const this_type&) = delete;
        constexpr inline runtime_tuple_table(this_type&&) = delete;

        constexpr inline this_type& operator=(const this_type&) = delete;
        constexpr inline this_type& operator=(this_type&&) = delete;

        /// <summary>
        /// <para> Executes `func_` with an argument of `tuple_`'s element at the passed compile-time `Index_`, with a safety bounds check. </para>
        /// <para> A compile-time bounds check will be performed. If the check fails, a static_assert will be triggered to prevent compilation. </para>
        /// </summary>
        /// <param name="tuple_">Tuple to invoke the function on an element of.</param>
        /// <param name="func_">Function to be invoked.</param>
        /// <returns>Result of the invocation of `func_`.</returns>
        template<std::size_t Index_>
        constexpr inline func_return_type execute(tuple_type& tuple_, Func_ func_) const
        {
            if constexpr (Index_ < num_elements)
            {
                return func_(std::get<Index_>(tuple_));
            }
            else
            {
                static_assert
                (
                    EmuCore::TMP::get_false<std::size_t, Index_>(),
                    "Invalid Index_ argument to EmuCore::TMP::runtime_tuple_table::execute with compile-time index argument: The index is greater than the highest index within the tuple."
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
        constexpr inline func_return_type execute(tuple_type& tuple_, Func_ func_, std::size_t index_) const
        {
            if (index_ < num_elements)
            {
                return _func_table[index_](tuple_, std::forward<Func_>(func_));
            }
            else
            {
                throw std::out_of_range("Invalid index_ argument to EmuCore::TMP::runtime_tuple_table::execute with runtime index argument: The index is greater than the highest index within the tuple.");
            }
        }

        /// <summary>
        /// <para> Executes `func_` with an argument of `tuple_`'s element at the passed `index_`. No safety bounds checks are performed. </para>
        /// </summary>
        /// <param name="tuple_">Tuple to invoke the function on an element of.</param>
        /// <param name="func_">Function to be invoked.</param>
        /// <param name="index_">Index of the tuple element to use as the argument to `func_`.</param>
        /// <returns>Result of the invocation of `func_`.</returns>
        constexpr inline func_return_type execute_no_bounds_check(tuple_type& tuple_, Func_ func_, std::size_t index_) const noexcept
        {
            return _func_table[index_](tuple_, std::forward<Func_>(func_));
        }

        /// <summary>
        /// <para> Shorthand for `execute` with a runtime index argument, performing execution with a safety bounds check. </para>
        /// </summary>
        /// <param name="tuple_">Tuple to invoke the function on an element of.</param>
        /// <param name="func_">Function to be invoked.</param>
        /// <param name="index_">Index of the tuple element to use as the argument to `func_`.</param>
        /// <returns>Result of the invocation of `func_`.</returns>
        constexpr inline func_return_type operator()(tuple_type& tuple_, Func_ func_, std::size_t index_) const
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
    };
}

#endif
