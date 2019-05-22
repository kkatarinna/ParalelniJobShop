#pragma once

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
        std::vector<common::value_t<It>> into;
        into.reserve(last - first);
        merge_impl(first, mid, mid, last, std::back_inserter(into), p);
        std::move(into.begin(), into.end(), first);
    }
}
