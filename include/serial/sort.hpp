#pragma once

#include <functional>

#include "merge.hpp"

namespace serial {
    template <typename It, typename P = std::less<>>
    void sort(It first, It last, P&& p = {}) {
        auto const size = last - first;
        if (size < 2)
            return;

        auto mid = first + size/2;
        serial::sort(first, mid, p);
        serial::sort(mid, last, p);
        serial::merge(first, mid, last, p);
    }
}
