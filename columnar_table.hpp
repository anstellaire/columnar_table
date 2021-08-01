#ifndef ENN_COLUMNAR_TABLE_HPP
#define ENN_COLUMNAR_TABLE_HPP

#include <tuple>
#include <utility>
#include <vector>
#include <cassert>

namespace enn {

    template<typename... Fields>
    class columnar_table {

        static_assert(sizeof...(Fields) > 0, "ERROR: columnar_table is expected to have at least one column");

        using indices = std::index_sequence_for<Fields...>;

        std::tuple<std::vector<Fields>...> cols_;

        template<std::size_t... Indices>
        std::tuple<Fields...> get_row_impl(std::size_t idx, std::index_sequence<Indices...>) const {
            auto getter = [idx](auto const& col) {
                assert(idx < col.size());
                return col[idx];
            };

            return std::tuple<Fields...>(getter(std::get<Indices>(cols_))...);
        }

        template<typename Tuple, std::size_t... Indices>
        void push_row_impl(Tuple&& fields, std::index_sequence<Indices...>) {
            auto pusher = [](auto& col, auto&& val) {
                col.push_back(std::forward<decltype(val)>(val));
                return 0;
            };

            // it is required, since there is a pack of return values
            [](...){}(pusher(std::get<Indices>(cols_), std::get<Indices>(std::forward<Tuple>(fields)))...);
        }

    public:

        std::size_t get_size() const {
            return get_col<0>().size();
        }

        template<std::size_t col_idx>
        auto const& get_col() const {
            return std::get<col_idx>(cols_);
        }

        // TODO: add get_row with std::tuple<Fields&...>
        std::tuple<Fields...> get_row(std::size_t row_idx) const {
            return get_row_impl(row_idx, indices{});
        }

        void push_row(std::tuple<Fields...> const& fields) {
            return push_row_impl(fields, indices{});
        }

        void push_row(std::tuple<Fields...>&& fields) {
            return push_row_impl(std::move(fields), indices{});
        }

    };

} // namespace enn

#endif // ENN_COLUMNAR_TABLE_HPP
