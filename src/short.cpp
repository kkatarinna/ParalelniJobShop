#include <algorithm>
#include <execution>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "common/io.hpp"
#include "common/time.hpp"
#include "parallel/sort.hpp"
#include "serial/sort.hpp"

constexpr size_t SMALL  = 500u;
constexpr size_t MEDIUM = 10000u;
constexpr size_t LARGE  = 5000000u;

void show_help() {
}

void generate_cutoff_data() {
    using namespace std::string_literals;
    auto const m_inf = "resources/merge/5000000.txt"s;
    auto const s_inf = "resources/sort/5000000.txt"s;
    
    auto m_vec = common::read_from_file<int>(m_inf);
    auto s_vec = common::read_from_file<int>(s_inf);

    std::ofstream m_out{ "results/merge_cutoff_raw.txt" };
    std::ofstream s_out{ "results/sort_cutoff_raw.txt" };

    for (size_t cutoff = 2; cutoff < LARGE; cutoff <<= 1) {
            parallel::sort_cutoff = cutoff;
            parallel::merge_cutoff = cutoff;
            for (size_t measurements = 0; measurements < 5; ++measurements) {
            auto const m_parallel_time = common::timeit([m_vec]() mutable {
                    parallel::merge(m_vec.begin(), m_vec.begin() + LARGE/2, m_vec.end());
            });

            m_out << cutoff << '\t' << m_parallel_time << '\n';

            auto const s_parallel_time = common::timeit([s_vec]() mutable {
                    parallel::sort(s_vec.begin(), s_vec.end());
            });

            s_out << cutoff << '\t' << s_parallel_time << '\n';
        }
    }
}

void generate_performance_data() {
}

void test_performance(size_t sz) {
    auto const filename = "resources/sort/" + std::to_string(sz) + ".txt";
    auto xs = common::read_from_file<int>(filename);
    for (size_t i = 0; i < 5; ++i) {   
        std::cout << "Serial sort:\n";
        auto const serial_time = common::timeit([xs]() mutable { 
                serial::sort(xs.begin(), xs.end()); 
        });
        std::cout << "Time passed: " << serial_time << " microseconds.\n";
        
        std::cout << "Parallel sort:\n";
        auto const parallel_time = common::timeit([xs]() mutable { 
                parallel::sort(xs.begin(), xs.end()); 
        });
        std::cout << "Time passed: " << parallel_time << " microseconds.\n";

        std::cout << "STL parallel stable sort:\n";
        auto const stl_time = common::timeit([xs]() mutable { 
                std::stable_sort(std::execution::par, xs.begin(), xs.end()); 
        });
        std::cout << "Time passed: " << stl_time << " microseconds.\n";

        std::cout << '\n';
    }
}

int main(int argc, char *argv[]) {
    using namespace std::string_literals;
    if (argc == 2) {
        if (argv[1] == "-c"s || argv[1] == "--cutoff"s) {
            generate_cutoff_data();
            return 0;
        } else if (argv[1] == "-p"s || argv[1] == "--performance"s) {
            generate_performance_data();
            return 0;
        } else if (argv[1] == "-s"s || argv[1] == "--small"s) {
            test_performance(SMALL);
            return 0;
        } else if (argv[1] == "-m"s || argv[1] == "--medium"s) {
            test_performance(MEDIUM);
            return 0;
        } else if (argv[1] == "-l"s || argv[1] == "--large"s) {
            test_performance(LARGE);
            return 0;
        } else {
            show_help();
            return 1;
        }
    } else {
        show_help();
        return 1;
    }
}
