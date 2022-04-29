#if !defined(TABLE_HPP)
#define TABLE_HPP

#include <string>
#include <tuple>
#include <vector>

#include "libs/Types/Types.hpp"


namespace Table {
    typedef std::tuple<int, char, float, std::string> Row;

    std::vector<Row> records;

    void insert(const Row&);
    std::vector<Row> select(const std::vector<uint32_t>&, const Row&);
    std::vector<Row> select_index(const std::vector<uint32_t>&, const Row&);
}

#endif // TABLE_HPP
