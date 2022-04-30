#include "libs/timer/timer.hpp"

#include <chrono>

namespace timer {
    std::pair<std::vector<table::Row>, long long> measure(
        std::vector<table::Row>(*f)(const std::vector<table::Predicate>&),
        const std::vector<table::Predicate>& predicates
    ) {
        using std::chrono::high_resolution_clock;
        using std::chrono::duration_cast;
        using std::chrono::milliseconds;

        auto start_time = high_resolution_clock::now();
        auto results = f(predicates);
        auto stop_time = high_resolution_clock::now();
        auto exec_time = duration_cast<milliseconds>(stop_time - start_time);

        return { results, exec_time.count() };
    }

} // namespace timer
