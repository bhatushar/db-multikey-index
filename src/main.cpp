#include "libs/QueryParser/QueryParser.hpp"
#include "libs/Table/Table.hpp"
#include<iostream>
#include<tuple>
#include<utility>
#include<vector>
#include<algorithm>

int main() {
    std::string arr[10] = {"hello", "world", "potato", "tomato", "oranges", "mango", "lemon", "melon", "peach", "strawberry"};
    table::Row row = std::make_tuple(123, 'A', 3.14, "Hello");
    for(int i = 0; i < 10000; i++){
        //row = std::make_tuple(i % 100, rand() % 26 + 'A', )
    }
    table::insert(row);
    // std::cout << "Table size: " <<table::records.size() << std::endl;

    table::Predicate pred = std::make_pair(std::make_tuple(false, false, false, false), row);
    std::vector<table::Predicate> preds;
    preds.push_back(pred);
    std::vector<table::Row> rowvec = table::select_index(preds);
    // std::cout << "Rows returned: " <<rowvec.size() << std::endl;
    for(auto it : rowvec)
        std::cout << std::get<0>(it) << " " << std::get<1>(it) << " " << std::get<2>(it) << " " << std::get<3>(it) << std::endl;
    std::cout << std::endl;
    pred = std::make_pair(std::make_tuple(true, false, false, false), row);
    preds.clear();
    preds.push_back(pred);
    rowvec = table::select_index(preds);
    // std::cout << "Rows returned: " <<rowvec.size() << std::endl;
    for(auto it : rowvec)
        std::cout << std::get<0>(it) << " " << 
        std::get<1>(it) << " " << std::get<2>(it) << " " << std::get<3>(it) << std::endl;
}
