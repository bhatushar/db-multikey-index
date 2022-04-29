#include "libs/QueryParser/QueryParser.hpp"
#include "libs/table/table.hpp"

#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

namespace parser {
    int query_type(const std::string& query) {
        if (query.rfind("insert") == 0) return TYPE_INSERT;
        if (query.rfind("select") == 0) return TYPE_SELECT;
        if (query.compare("exit") == 0) return TYPE_EXIT;
        throw std::invalid_argument("Unknown query type!");
    }

    table::Row parse_insert(const std::string& query) {
        // insert <integer>:<char>:<float>:<string>
        // float may or may not have fractional part
        std::regex insert_exp("insert ([0-9]+):(.):([0-9]+(?:\\.[0-9]+)?):(.+)");
        std::smatch matches;
        if (std::regex_match(query, matches, insert_exp)) {
            // Query has a valid insert syntax
            return std::make_tuple(
                // matches[0] is the entire query
                std::stoi(matches[1].str()),
                matches[2].str()[0],
                std::stof(matches[3].str()),
                matches[4].str()
            );
        }
        else throw std::invalid_argument("Invalid syntax for INSERT query!");
    }
} // namespace parser
