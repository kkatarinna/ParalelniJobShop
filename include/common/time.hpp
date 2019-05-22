#pragma once

#include <chrono>

namespace common {
    template <typename F>
    auto timeit(F&& f) -> long long {
        auto const start = std::chrono::steady_clock::now();
        f();
        auto const end = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }
}
