#include "columnar_table.hpp"

#include <iostream>
#include <string>

template<typename... Args>
void print(std::tuple<Args...> const& t) {
    std::cout << "std::tuple{" << std::get<0>(t) << ", " << std::get<1>(t) << "};" << std::endl;
}

int main() {
    enn::columnar_table<int, std::string> t{};

    std::tuple<int, std::string> fields(0, "row_one_l_value");

    t.push_row(fields);
    t.push_row(std::tuple<int, std::string>(1, "row_two_r_value"));

    print(t.get_row(0));
    print(t.get_row(1));
}
