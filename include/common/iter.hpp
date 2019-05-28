#pragma once

#include <iterator>
#include <vector>

namespace common {
    template <typename It>
    using value_t = typename std::iterator_traits<It>::value_type;

    template <typename T>
    auto first(std::vector<T>& xs) -> typename std::vector<T>::iterator {
        return xs.begin();
    }

    template <typename T>
    auto mid(std::vector<T>& xs) -> typename std::vector<T>::iterator {
        return xs.begin() + xs.size()/2;
    }

    template <typename T>
    auto last(std::vector<T>& xs) -> typename std::vector<T>::iterator {
        return xs.end();
    }
}
