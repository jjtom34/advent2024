#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <deque>

using namespace std;

int calc_trailheads(pair<int,int> start, vector<vector<int>> map){
    int trailheads = 0;
    set<pair<int,int>> peaks;
    deque<pair<int,int>> trails;
    trails.push_back(start);
    while(!trails.empty()){
        // Check if reached a peak
        int row = trails.front().first;
        int col = trails.front().second;
        trails.pop_front();
        if((map[row][col]) == 9){
            peaks.emplace(make_pair(row,col));
        }
        // Add in adjacent increasing squares
        // North
        if(row > 0){
            if(map[row-1][col] == map[row][col]+1){
                trails.push_back(make_pair(row-1,col));
            }
        }
        if(row < map.size()-1){
            if(map[row+1][col] == map[row][col]+1){
                trails.push_back(make_pair(row+1,col));
            }
            
        }
        if(col > 0){
            if(map[row][col-1] == map[row][col]+1){
                trails.push_back(make_pair(row,col-1));
            }
            
        }
        if(col < map[0].size()-1){
            if(map[row][col+1] == map[row][col]+1){
                trails.push_back(make_pair(row,col+1));
            }       
        }
    }
    return peaks.size();
}

int main(){
    ifstream input_file;
    input_file.open("input.txt");
    string line;
    vector<vector<int>> map;    
    while(getline(input_file,line)){
        vector<int> row;
        for(auto c:line){
            row.push_back(c-'0');
        }
        map.push_back(row);
    }
    vector<pair<int,int>> starting_locations;
    int sum = 0;
    for(int i = 0; i < map.size(); ++i){
        for(int j = 0; j < map[i].size(); ++j){
            if(map[i][j] == 0){
                starting_locations.push_back(make_pair(i,j));
            }
        }
    }
    for(auto start:starting_locations){
        sum+= calc_trailheads(start,map);
    }
    cout << sum << endl;
}
