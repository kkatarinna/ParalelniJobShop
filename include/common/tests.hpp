#pragma once

namespace test {
    constexpr size_t SMALL = 500u;
    constexpr size_t MEDIUM = 100000u;
    constexpr size_t LARGE = 5000000u;

    void correctness(size_t);

    void performance(size_t);

    void trivial();
}
