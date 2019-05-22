#pragma once

#include <iterator>

namespace common {
    template <typename It>
    using value_t = typename std::iterator_traits<It>::value_type;
}
