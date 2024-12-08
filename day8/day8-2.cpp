#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <deque>
#include <sstream>
#include <set>

using namespace std;
void extend_antinodes(set<pair<int,int>>* antinodes, pair<int,int> a, pair<int,int> b,int row, int col){
    //Get distance between two antennas
    int row_dist = abs(a.first-b.first);
    int col_dist = abs(a.second-b.second);
    int row_1 = a.first;
    int col_1 = a.second;
    int row_2 = b.first;
    int col_2 = b.second;
    
    while(row_1 >= 0 && row_1 < row && col_1 >=0 && col_1 < col){
        pair <int,int> anti_1 = make_pair(row_1,col_1);
        antinodes->insert(anti_1);
        if(a.first > b.first){
            row_1 = row_1 + row_dist;
        }
        else{
            row_1 = row_1 - row_dist;
        }
        if(a.second > b.second){
            col_1 = col_1 + col_dist;
        }
        else{
            col_1 = col_1 - col_dist;
        }
        
    }
    while(row_2 >= 0 && row_2 < row && col_2 >=0 && col_2 < col){
        pair <int,int> anti_2 = make_pair(row_2,col_2);
        antinodes->insert(anti_2);
        if(a.first > b.first){
            row_2 = row_2 - row_dist;
        }
        else{
            row_2 = row_2 + row_dist;
        }
        if(a.second > b.second){
            col_2 = col_2 - col_dist;
        }
        else{
            col_2 = col_2 + col_dist;
        }
    }
}

int main(){
    ifstream input_file;
    input_file.open("input.txt");
    string line;
    unordered_map<char,vector<pair<int,int>>> antennas;
    unsigned long sum = 0;
    int row=0;
    int col=0;
    while(getline(input_file,line)){
        col = 0;
        for(auto c:line){
            if(c != '.'){
                if(antennas.find(c) != antennas.end()){
                    antennas[c].push_back(make_pair(row,col));
                }
                else{
                    vector<pair<int,int>> new_vec = {make_pair(row,col)};
                    antennas[c] = new_vec;
                }
            }
            
            col += 1;
        }
        row += 1;
    }
    // Start finding antinodes
    set<pair<int,int>> antinodes;
    for(auto [first,second]:antennas){
        for(int i = 0; i < second.size(); ++i){
            for(int j = i+1 ; j < second.size(); ++j){
                extend_antinodes(&antinodes,second[i],second[j],row,col);
            }
        }
    }
    cout << antinodes.size() << endl;
}
