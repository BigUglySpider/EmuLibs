#ifndef EMU_CORE_RUNTIME_TUPLE_TABLE_H_INC_
#define EMU_CORE_RUNTIME_TUPLE_TABLE_H_INC_ 1

#include <stdexcept>
#include <tuple>
#include <type_traits>

#include "TypeConvertors.h"
#include "../CommonConcepts/StdTypes.h"

namespace EmuCore::TMP
{
    template<std::size_t Index_, EmuConcepts::StdTuple Tuple_, class Func_>
    constexpr inline auto execute_function_on_tuple_element(Tuple_& tuple_, Func_&& func_)
        -> decltype(std::forward<Func_>(func_)(tuple_))
    {
        return std::forward<Func_>(func_)(std::get<Index_>(tuple_));
    }

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
        using arbitrating_func_return_type = func_return_type;
        using arbitrating_func_type = arbitrating_func_return_type(*)(tuple_type&, func_forward_type);
        using arbitrating_func_table_type = std::array<arbitrating_func_type, num_elements>;
        using index_sequence = std::make_index_sequence<num_elements>;

        template<std::size_t...Indices_>
        [[nodiscard]] static constexpr inline arbitrating_func_table_type _make_underlying_func_table(std::index_sequence<Indices_...> indices_)
        {
            return arbitrating_func_table_type
            ({
                (&execute_function_on_tuple_element<Indices_, tuple_type, Func_>)...
            });
        }

        const arbitrating_func_table_type table;

    public:
        constexpr inline runtime_tuple_table() noexcept : table(_make_underlying_func_table(index_sequence()))
        {
        }
        constexpr inline runtime_tuple_table(const this_type&) = delete;
        constexpr inline runtime_tuple_table(this_type&&) = delete;

        constexpr inline this_type& operator=(const this_type&) = delete;
        constexpr inline this_type& operator=(this_type&&) = delete;

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

        constexpr inline func_return_type execute(tuple_type& tuple_, Func_ func_, std::size_t index_) const
        {
            if (index_ < num_elements)
            {
                return table[index_](tuple_, std::forward<Func_>(func_));
            }
            else
            {
                throw std::out_of_range("Invalid index_ argument to EmuCore::TMP::runtime_tuple_table::execute with runtime index argument: The index is greater than the highest index within the tuple.");
            }
        }

        constexpr inline func_return_type execute_no_bounds_check(tuple_type& tuple_, Func_ func_, std::size_t index_) const
        {
            return table[index_](tuple_, std::forward<Func_>(func_));
        }

        constexpr inline func_return_type operator()(tuple_type& tuple_, Func_ func_, std::size_t index_) const
        {
            if (index_ < num_elements)
            {
                return table[index_](tuple_, std::forward<Func_>(func_));
            }
            else
            {
                throw std::out_of_range("Invalid index_ argument to EmuCore::TMP::runtime_tuple_table::operator() with runtime index argument: The index is greater than the highest index within the tuple.");
            }
        }
    };
}

#endif
