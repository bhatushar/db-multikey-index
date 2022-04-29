#include "libs/Table/Table.hpp"

#include <tuple>
#include <vector>
#include<unordered_map>
#include<string>

namespace table {
    // Initializing static variables
    std::vector<Row> records = {};
    std::unordered_map<int, std::vector<int>> int_index = {};
    std::unordered_map<char, std::vector<int>> char_index = {};
    std::unordered_map<float, std::vector<int>> float_index = {};
    std::unordered_map<std::string, std::vector<int>> string_index = {};

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
                if (std::get<1>(pred.first) && std::get<1>(pred.second) != std::get<1>(row))
                    include = false;
                if (std::get<2>(pred.first) && std::get<2>(pred.second) != std::get<2>(row))
                    include = false;
                if (std::get<3>(pred.first) && std::get<3>(pred.second).compare(std::get<3>(row)) != 0)
                    include = false;

                if (include) {
                    data.push_back(row);
                    break;
                }
            }
        }
        return data;
    }

    void insert(const Row& row){
        records.push_back(row);
        int row_num = records.size() - 1;
        int_index[std::get<0>(row)].push_back(row_num);
        char_index[std::get<1>(row)].push_back(row_num);
        float_index[std::get<2>(row)].push_back(row_num);
        string_index[std::get<3>(row)].push_back(row_num);
    }
} // namespace Table
