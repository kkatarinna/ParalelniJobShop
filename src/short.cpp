#include <algorithm>
#include <execution>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "common/io.hpp"
#include "common/time.hpp"
#include "parallel/sort.hpp"
#include "serial/sort.hpp"

constexpr size_t SMALL  = 500u;
constexpr size_t MEDIUM = 5000u;
constexpr size_t LARGE  = 5000000u;

void show_help() {
}

void generate_cutoff_data() {
    using namespace std::string_literals;
    auto m_vec = [] {
        auto const m_inf = "resources/merge/5000000.txt"s;
        return common::read_from_file<int>(m_inf);
    }();
    auto s_vec = [] {
        auto const s_inf = "resources/sort/5000000.txt"s;
        return common::read_from_file<int>(s_inf);
    }();

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
    std::cout << "Testing performance for size: " << sz << '\n';
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

    auto const opts = std::map{
        {"-h"s, [] { show_help(); }},
        {"--help"s, [] { show_help(); }},
        {"-s"s, [] { test_performance(SMALL); }},
        {"--small"s, [] { test_performance(SMALL); }},
        {"-m"s, [] { test_performance(MEDIUM); }},
        {"--medium"s, [] { test_performance(MEDIUM); }},
        {"-l"s, [] { test_performance(LARGE); }},
        {"--large"s, [] { test_performance(LARGE); }},
        {"-c"s, [] { generate_cutoff_data(); }},
        {"--cutoff"s, [] { generate_cutoff_data(); }},
        {"-p"s, [] { generate_performance_data(); }},
        {"--performance"s, [] { generate_performance_data(); }},
        {"-ts"s, [] { test_correctness(SMALL); }},
        {"--test-small"s, [] { test_correctness(SMALL); }},
        {"-tm"s, [] { test_correctness(MEDIUM); }},
        {"--test-medium"s, [] { test_correctness(MEDIUM); }},
        {"-tl"s, [] { test_correctness(LARGE); }},
        {"--test-large"s, [] { test_correctness(LARGE); }},
        {"-tt"s, [] { test_trivial(); }},
        {"--test-trivial"s, [] { test_trivial(); }}
    };
    if (argc == 2) {
        opts[argv[1]]();
    } else {
        show_help();
        return 1;
    }
}
