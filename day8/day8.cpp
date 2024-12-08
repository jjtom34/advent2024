#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <deque>
#include <sstream>
#include <set>

using namespace std;

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
                pair <int,int> ant_1 = second[i];
                pair <int,int> ant_2 = second[j];
                //Get distance between two antennas
                int row_dist = abs(ant_1.first-ant_2.first);
                int col_dist = abs(ant_1.second-ant_2.second);
                int row_1;
                int col_1;
                int row_2;
                int col_2;
                if(ant_1.first > ant_2.first){
                    row_1 = ant_1.first + row_dist;
                    row_2 = ant_2.first - row_dist;
                }
                else{
                    row_1 = ant_1.first - row_dist;
                    row_2 = ant_2.first + row_dist;
                }
                if(ant_1.second > ant_2.second){
                    col_1 = ant_1.second + col_dist;
                    col_2 = ant_2.second - col_dist;
                }
                else{
                    col_1 = ant_1.second - col_dist;
                    col_2 = ant_2.second + col_dist;
                }
                //Check if antinode is outside of bounds
                pair <int,int> anti_1;
                pair <int,int> anti_2;
                if(row_1 >= 0 && row_1 < row && col_1 >=0 && col_1 < col){
                    anti_1 = make_pair(row_1,col_1);
                    antinodes.insert(anti_1);
                }
                if(row_2 >= 0 && row_2 < row && col_2 >=0 && col_2 < col){
                    anti_2= make_pair(row_2,col_2);
                    antinodes.insert(anti_2);
                }
                
            }
        }
    }
    cout << antinodes.size() << endl;
}

// 11
// 22
// 