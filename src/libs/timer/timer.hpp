#if !defined(TIMER_HPP)
#define TIMER_HPP

#include <chrono>
#include <vector>

#include "libs/table/table.hpp"

namespace timer {
    /**
     * @brief Executes the provided function and records the time it took to finish.
     * Time is measured in miliseconds.
     *
     * @return Pair of data retured by the executed funtion and the time taken
     */
    std::pair<std::vector<table::Row>, long long> measure(
        std::vector<table::Row>(*)(const std::vector<table::Predicate>&),
        const std::vector<table::Predicate>&
    );
} // namespace timer


#endif // TIMER_HPP
