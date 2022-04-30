#if !defined(QUERY_PARSER_HPP)
#define QUERY_PARSER_HPP

#include <string>

#include "libs/table/table.hpp"

namespace parser {
    static const int TYPE_INSERT = 1, TYPE_SELECT = 2, TYPE_SELECT_INDEXED = 3, TYPE_EXIT = 4;

    /**
     * @return Type of the query passed (insert, select or exit)
     */
    int query_type(const std::string&);

    /**
     * @brief Parses an insert query and returned the data as a tuple with appropriate types.
     * Throws an exception if the syntax is invalid.
     * Correct syntax: insert <integer>:<char>:<float>:<string>
     *
     * @param query Insert query string
     * @return Row of data extracted from the query
     */
    table::Row parse_insert(const std::string&);

    /**
     * @brief Parses the where clause of a select query.
     * Each predicate in the clause is of the form `int?:char?:float?:string?`.
     * An empty value indicates that the column value is not part of the predicate.
     *
     * @param where_clause Strings of where clause predicates
     * @return List of Predicate objects extracted from the clause
     */
    std::vector<table::Predicate> parse_select(const std::vector<std::string>&);
} // namespace parser

#endif // QUERY_PARSER_HPP
