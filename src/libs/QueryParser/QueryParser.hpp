#ifndef QUERY_PARSER_HPP
#define QUERY_PARSER_HPP

#include <string>

#include "libs/table/table.hpp"

namespace parser {
    static const int TYPE_INSERT = 1, TYPE_SELECT = 2, TYPE_EXIT = 3;

    /**
     * @return Type of the query passed (insert, select or exit)
     */
    int query_type(const std::string&);

    /**
     * @brief Parses an insert query and returned the data as a tuple with appropriate types.
     * Throws an exception if the syntax is invalid.
     * Correct syntax: insert <integer>:<char>:<float>:<string>
     *
     * @return Row of data extracted from the query
     */
    table::Row parse_insert(const std::string&);
} // namespace parser


#endif // QUERY_PARSER_HPP
