#include "libs/Table/Table.hpp"

#include <tuple>
#include <vector>

namespace Table {
    std::vector<Row> select(const std::vector<Predicate>& predicates) {
        std::vector<Row> data;
        // Test the predicates on reach row
        // Predicates follow an SOP form: (c1 AND c2) OR (c3 AND c4 AND c5) OR ...
        // If at least one predicate satisfies, row is selected
        for (auto& row : records) {
            for (auto& pred : predicates) {
                bool include = true;
                // If column specified in predicate and row value matches
                if (std::get<0>(pred.first) && std::get<0>(pred.second) != std::get<0>(row))
                    include = false;
                if (std::get<1>(pred.first) && std::get<1>(pred.second) != std::get<0>(row))
                    include = false;
                if (std::get<2>(pred.first) && std::get<2>(pred.second) != std::get<0>(row))
                    include = false;
                if (std::get<3>(pred.first) && std::get<3>(pred.second).compare(std::get<3>(row)) == 0)
                    include = false;

                if (include) {
                    data.push_back(row);
                    break;
                }
            }
        }
        return data;
    }
} // namespace Table
