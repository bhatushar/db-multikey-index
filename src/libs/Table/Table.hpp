#if !defined(TABLE_HPP)
#define TABLE_HPP

#include <string>
#include <tuple>
#include <vector>
#include <unordered_map>

namespace table {
    typedef std::tuple<int, char, float, std::string> Row;
    typedef std::pair<std::tuple<bool, bool, bool, bool>, Row> Predicate;

    extern std::vector<Row> records;

    extern std::unordered_map<int, std::vector<int>> int_index;
    extern std::unordered_map<char, std::vector<int>> char_index;
    extern std::unordered_map<float, std::vector<int>> float_index;
    extern std::unordered_map<std::string, std::vector<int>> string_index;

    /**
     * @brief Adds a row to the table and indexes column values
     * 
     * @param row Data to be inserted
     */
    void insert(const Row& row);

    /**
     * @brief Select rows from the table which matches the given predicate.
     * The predicates are in SOP form: (c1 AND c2) OR (c3 AND c4 AND c5) OR ...
     * The predicates only support equality check.
     *
     * @return List of rows passing the predicate
     */
    std::vector<Row> select(const std::vector<Predicate>&);
    std::vector<Row> select_index(const std::vector<Predicate>&);
}

#endif // TABLE_HPP
