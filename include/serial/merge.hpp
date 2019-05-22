#pragma once

#include <cstdlib>
#include <functional>
#include <vector>

#include "../common/iter.hpp"

namespace serial {
    template <typename It, typename Out, typename P = std::less<>>
    void merge_impl(It l_first, It l_last, It r_first, It r_last, Out o_first, P&& p = {}) {
        while (l_first != l_last && r_first != r_last)
            if (!p(*r_first, *l_first))
                *o_first++ = std::move(*l_first++);
            else
                *o_first++ = std::move(*r_first++);
        o_first = std::move(l_first, l_last, o_first);
        std::move(r_first, r_last, o_first);
    }

    template <typename It, typename P = std::less<>>
    void merge(It first, It mid, It last, P&& p = {}) {
        auto const size = static_cast<size_t>(last - first);
        //std::vector<common::value_t<It>> into;
        //into.reserve(last - first);
        common::value_t<It> *into = static_cast<common::value_t<It>*>(std::malloc(sizeof(common::value_t<It>)*size));
        merge_impl(first, mid, mid, last, into, p);
        std::move(into, into + size, first);
        std::free(into);
    }
}
