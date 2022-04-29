#include<bits/stdc++.h>
using namespace std;
//creating 4 maps for 4 columns
unordered_map<int, vector<int>> inthash;
unordered_map<char, vector<int>> charhash;
unordered_map<float, vector<int>> floathash;
unordered_map<string, vector<int>> stringhash;

//for inserting into the maps
//insert respectively into the maps the row number
//easy
void insert_hash(int a, char b, float c, string d, int row){
    inthash[a].push_back(row);
    charhash[b].push_back(row);
    floathash[c].push_back(row);
    stringhash[d].push_back(row);
}

//finding the intersection of the 4 vectors
//initially the count should be equal to 4
//if the size of a vector is 0, it means we are not considering that column, and the count should be reduced by 1
//here, count = n
//then traversing over all the vectors and updating the count by 1
//finally checking the frequency is equal to n or not
vector<int> intersection(vector<int>& arow, vector<int>& brow, vector<int>& crow, vector<int>& drow){
    vector<int> rows;
    unordered_map<int, int> freq;
    //initially the count should be equal to 4
    //if the size of a vector is 0, it means we are not considering that column, and the count should be reduced by 1
    //here, count = n
    int n = 4;
    if(arow.size() == 0)
        n--;
    if(brow.size() == 0)
        n--;
    if(crow.size() == 0)
        n--;
    if(drow.size() == 0)
        n--;
    //then traversing over all the vectors and updating the count by 1
    for(auto it : arow)
        freq[it]++;
    for(auto it: brow)
        freq[it]++;
    for(auto it : crow)
        freq[it]++;
    for(auto it : drow)
        freq[it]++;
    //finally checking the frequency is equal to n or not
    //if it is, it is the required row number and we push back it
    for(auto it : freq)
        if(it.second == n)
            rows.push_back(it.first);
    //can sort or not depends upon use
    //but have sorted for now
    //can be removed
    sort(rows.begin(), rows.end());
    return rows;
}

//function for retrieving the row numbers
//basically creates a corresponding vector for each column
//using default values for columns not specified and they will point towards empty vectors basically(we don't consider them)
//can change the default values if you like
vector<int> retrieve(int a = INT_MIN, char b = '~', float c = INT_MIN, string d = ""){
    vector<int> arow = inthash[a];
    vector<int> brow = charhash[b];
    vector<int> crow = floathash[c];
    vector<int> drow = stringhash[d];
    return intersection(arow, brow, crow, drow);
}
//driver code
//demonstrates inserting and retrieving
//all the values have to be passed to the function
//the values which will not be given will be default values
int main(){
    //pushing the values
    insert_hash(999, 'F', 3.14, "hello", 1);
    insert_hash(999, 'M', 3.14, "nom nom", 2);
    int a = INT_MIN;
    char b = '~';
    float c = INT_MIN;
    string d = "";
    a = 999;
    //retrieving the values
    vector<int> rows = retrieve(a, b, c, d);
    for(auto it : rows)
        cout << it << " ";
    cout << endl;
}
