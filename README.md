# Columnar Table

Columnar table allows storing data in a table with cache locality along columns

```c++
#include "columnar_table.hpp"

#include <iostream>
#include <string>

template<typename... Args>
void print(std::tuple<Args...> const& t) {
    std::cout << "std::tuple{" << std::get<0>(t) << ", " << std::get<1>(t) << "};" << std::endl;
}

int main() {
    enn::columnar_table<int, std::string> t{};

    t.push_row(std::tuple<int, std::string>(0, "row_one_r_value"));
    t.push_row({1, "row_two_init_list"});

    print(t.get_row(0));
    print(t.get_row(1));
}
```
