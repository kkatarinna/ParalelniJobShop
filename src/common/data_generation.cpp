#include <array>
#include <fstream>
#include <string>
#include <vector>

#include "common/io.hpp"
#include "common/time.hpp"
#include "parallel/merge.hpp"
#include "parallel/sort.hpp"
#include "serial/merge.hpp"
#include "serial/sort.hpp"

namespace generate {
    constexpr std::array<size_t, 10> TEST_SIZES = {
        100u,     500u,
        1000u,    5000u,
        10000u,   50000u,
        100000u,  500000u,
        1000000u, 5000000u
    };

    void cutoff_data() {
        using namespace std::string_literals;
        auto m_vec = common::read_from_file<int>(
            "resources/merge/5000000.txt"
        );
        auto m_vec = common::read_from_file<int>(
            "resources/merge/5000000.txt"
        );

        std::ofstream m_out{ "results/merge_cutoff_raw.txt" };
        std::ofstream s_out{ "results/sort_cutoff_raw.txt" };

        for (size_t cutoff = 2; cutoff < LARGE; cutoff <<= 1) {
            parallel::sort_cutoff = cutoff;
            parallel::merge_cutoff = cutoff;
            for (size_t m = 0; m < 10; ++m) {
                auto const m_parallel_time = common::timeit(
                    [m_vec]() mutable {
                        parallel::merge(
                                m_vec.begin(),
                                m_vec.begin() + LARGE/2,
                                m_vec.end()
                        );
                });
                m_out << cutoff << '\t' << m_parallel_time << '\n';

                auto const s_parallel_time = common::timeit(
                    [s_vec]() mutable {
                        parallel::sort(s_vec.begin(), s_vec.end());
                });
                s_out << cutoff << '\t' << s_parallel_time << '\n';
            }
        }
    }

    void performance_data() {
        std::ofstream m_out{"results/merge_perf_raw.txt"};
        std::ofstream s_out{"results/sort_perf_raw.txt"};

        for (auto const& size : TEST_SIZES) {
            auto m_vec = common::read_from_file<int>(
                "resources/merge/" + std::to_string(size) + ".txt"
            );
            auto s_vec = common::read_from_file<int>(
                "resources/sort/" + std::to_string(size) + ".txt"
            );
           
            for (size_t m = 0; m < 10; ++m) {
                auto const m_time = common::timeit(
                    [m_vec]() mutable {
                        parallel::merge(
                            m_vec.begin(),
                            m_vec.begin() + m_vec.size()/2,
                            m_vec.end()
                        );
                });
                m_out << size << ' ' << m_time << '\n';

                auto const s_time = common::timeit(
                    [s_vec]() mutable {
                        parallel::sort(s_vec.begin(), s_vec.end());
                });
                s_out << size << ' ' << s_time << '\n';
            }
        }
    }
}
