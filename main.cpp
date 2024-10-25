#include <iostream>
#include <vector>
#include <utility>
#include <queue>    
#include <sstream> 
#include <string>
using namespace std;

/*
compile with: g++ -std=c++14 -o main main.cpp
run with: ./main < pyramid_sample_input.txt

pyramid_recursive() checks if it is at the last row -- if correct product, it will return path, otherwise "DNE" (does not exist)
It will recurse over left and right child, or left and right neighbors 1 row below
It is optimized to only recurse on child if the target will still be divisible by product
*/


//simple function recurses over position and product in pyramid, returns 1st valid path
string pyramid_recursive(const vector<vector<int>> &p, int product, const int target, string path, int row, int col){
    product *= p[row][col]; //update current product

    if(row == p.size()-1 && product == target){ return path; } //reached last element
    if(row == p.size()-1){ return "DNE"; }

    if(target % (product * p[row+1][col]) == 0){ //only recurse if product is still valid (target divisible by target), left
        string ans1 = pyramid_recursive(p, product, target, path+'L', row+1, col);
        if(ans1 != "DNE"){ return ans1; }
    }
    if(target % (product * p[row+1][col+1]) == 0){ //right
        string ans2 = pyramid_recursive(p, product, target, path+'R', row+1, col+1);
        if(ans2 != "DNE"){ return ans2; }
    }
    return "DNE"; //does not exist
}

//reads input.txt, returns pair<target, pyramid>
pair<int, vector<vector<int>>> read_input() {
    // Read the first line to get the target
    string firstLine;
    getline(cin, firstLine);
    size_t colonPos = firstLine.find(':');
    int target = stoi(firstLine.substr(colonPos + 1));

    // Read the pyramid rows until EOF
    vector<vector<int>> pyramid;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue; // Skip empty lines
        vector<int> row;
        string num;
        stringstream ss(line);
        while(getline(ss, num, ',')) {
            // Remove leading/trailing whitespace
            size_t start = num.find_first_not_of(" \t\r\n");
            size_t end = num.find_last_not_of(" \t\r\n");
            string trimmed = num.substr(start, end - start + 1);
            row.push_back(stoi(trimmed));
        }
        pyramid.push_back(row);
    }

    return {target, pyramid};
}

int main(){
    pair<int, vector<vector<int>>> input = read_input();
    cout << pyramid_recursive(input.second, 1, input.first, "", 0, 0) << endl;
}
