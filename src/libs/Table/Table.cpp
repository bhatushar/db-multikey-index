#include "libs/Table/Table.hpp"

#include <tuple>
#include <vector>
#include<unordered_map>
#include<string>
#include<algorithm>

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
    //finding the intersection of the 4 vectors
    //initially the count should be equal to 4
    //if the size of a vector is 0, it means we are not considering that column, and the count should be reduced by 1
    //here, count = n
    //then traversing over all the vectors and updating the count by 1
    //finally checking the frequency is equal to n or not
    std::vector<int> intersection(std::vector<int>& acol, std::vector<int>& bcol, std::vector<int>& ccol, std::vector<int>& dcol){
        std::vector<int> rows;
        std::unordered_map<int, int> freq;
        //initially the count should be equal to 4
        //if the size of a vector is 0, it means we are not considering that column, and the count should be reduced by 1
        //here, count = n
        int n = 4;
        if(acol.size() == 0)
            n--;
        if(bcol.size() == 0)
            n--;
        if(ccol.size() == 0)
            n--;
        if(dcol.size() == 0)
            n--;
        //then traversing over all the vectors and updating the count by 1
        for(auto it : acol)
            freq[it]++;
        for(auto it: bcol)
            freq[it]++;
        for(auto it : ccol)
            freq[it]++;
        for(auto it : dcol)
            freq[it]++;
        //finally checking the frequency is equal to n or not
        //if it is, it is the required row number and we push back it
        for(auto it : freq)
            if(it.second == n)
                rows.push_back(it.first);
        //can sort or not depends upon use
        //but have sorted for now
        //can be removed
        std::sort(rows.begin(), rows.end());
        if(n == 0){
            for(int i = 0; i < records.size(); i++)
                rows.push_back(i);
        }
        return rows;
    }
    //function for retrieving the row numbers
    //basically creates a corresponding vector for each column
    //using default values for columns not specified and they will point towards empty vectors basically(we don't consider them)
    //can change the default values if you like
    std::vector<int> retrieve(int a = INT_MIN, char b = '~', float c = INT_MIN, std::string d = ""){
        std::vector<int> acol = int_index[a];
        std::vector<int> bcol = char_index[b];
        std::vector<int> ccol = float_index[c];
        std::vector<int> dcol = string_index[d];
        return intersection(acol, bcol, ccol, dcol);
    }
    std::vector<Row> select_index(const std::vector<Predicate>& predicates){
        std::vector<Row> data;
        std::vector<int> row_nums;
        // Test the predicates on index
        // Predicates follow an SOP form: (c1 AND c2) OR (c3 AND c4 AND c5) OR ...
        // If at least one predicate satisfies, row is selected
        for(auto& pred : predicates){
            int a = INT_MIN;
            char b = '~';
            float c = INT_MIN;
            std::string d = "";
            if(std::get<0>(pred.first))
                a = std::get<0>(pred.second);
            if(std::get<1>(pred.first))
                b = std::get<1>(pred.second);
            if(std::get<2>(pred.first))
                c = std::get<2>(pred.second);
            if(std::get<3>(pred.first))
                d = std::get<3>(pred.second);
            std::vector<int> temp_rows = retrieve(a, b, c, d);
            row_nums.insert(row_nums.end(), temp_rows.begin(), temp_rows.end());
        }
        for(auto& it : row_nums){
            data.push_back(make_tuple(std::get<0>(records[it]), std::get<1>(records[it]), std::get<2>(records[it]), std::get<3>(records[it])));
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
