#pragma once

#include <fstream>
#include <vector>

namespace common {
    template <typename T>
    auto read_from_file(std::string filename) -> std::vector<T> {
        std::ifstream in{ std::move(filename) };
        std::vector<T> xs;
        T x;

        while (in >> x)
            xs.emplace_back(x);

        return xs;
    }

    template <>
    auto read_from_file(std::string filename) -> std::vector<char> {
        std::ifstream in{ std::move(filename) };
        std::vector<char> xs;
        int x;
        
        while (in >> x)
            xs.emplace_back(static_cast<char>(x));

        return xs;
    }
}
