#include "libs/QueryParser/QueryParser.hpp"
#include "libs/table/table.hpp"

#include <regex>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

namespace parser {
    int query_type(const std::string& query) {
        if (query.rfind("insert") == 0) return TYPE_INSERT;
        if (query.rfind("select") == 0) return TYPE_SELECT;
        if (query.compare("select indexed") == 0) return TYPE_SELECT_INDEXED;
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

    std::vector<table::Predicate> parse_select(const std::vector<std::string>& where_clause) {
        std::vector<table::Predicate> predicates;
        std::regex predicate_exp("([0-9]+)?:(.)?:([0-9]+(?:\\.[0-9]+)?)?:(.+)?");
        std::smatch matches;

        if (where_clause.size() == 0) {
            // No clause specified, blind select
            predicates = { {
                std::make_tuple(false, false, false, false),
                std::make_tuple(0, '\0', 0.0, "")
            } };
        }

        else {
            for (auto pred_str : where_clause) {
                // Convert each predicate string into a Predicate object
                if (std::regex_match(pred_str, matches, predicate_exp)) {
                    table::Predicate predicate = std::make_pair(
                        std::make_tuple(false, false, false, false),
                        std::make_tuple(0, '\0', 0.0, "")
                    );

                    // If value for any column is specified, add that to the predicate
                    if (matches[1].str().compare("")) {
                        std::get<0>(predicate.first) = true;
                        std::get<0>(predicate.second) = std::stoi(matches[1].str());
                    }
                    if (matches[2].str().compare("")) {
                        std::get<1>(predicate.first) = true;
                        std::get<1>(predicate.second) = matches[2].str()[0];
                    }
                    if (matches[3].str().compare("")) {
                        std::get<2>(predicate.first) = true;
                        std::get<2>(predicate.second) = std::stof(matches[3].str());
                    }
                    if (matches[4].str().compare("")) {
                        std::get<3>(predicate.first) = true;
                        std::get<3>(predicate.second) = matches[4].str();
                    }

                    predicates.emplace_back(predicate);
                }
                else throw std::invalid_argument("Invalid format for SELECT PREDICATE!");
            }
        }
        return predicates;
    }
} // namespace parser
