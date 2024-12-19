#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <sstream>
#include <unordered_map>
#include <cmath>
#include <queue>

using namespace std;

int solve_maze(vector<char> * map,int size){
    // Store row,col + distance
    deque<tuple<int,int,int>> queue;
    queue.push_back(make_tuple(0,0,0));
    // North East South West
    pair<int,int> directions[4] = {make_pair(-1,0),make_pair(0,1),make_pair(1,0),make_pair(0,-1)};
    vector<bool> visited(map->size(),false);
    visited[0] = true;
    while(!queue.empty()){
        tuple<int,int,int> curr = queue.front();
        queue.pop_front();

        if(get<0>(curr) == size-1 && get<1>(curr) == size-1){
            return get<2>(curr);
        }
        for(auto dir:directions){
            int new_row = get<0>(curr) + dir.first;
            int new_col = get<1>(curr) + dir.second;
            if(new_col >= 0 && new_row >= 0 && new_col < size && new_row < size){
                if(map->at(new_row*size+new_col) != '#'){
                    if(!visited[new_row*size + new_col]){
                        visited[new_row*size + new_col] = true;
                        queue.push_back(make_tuple(new_row,new_col,get<2>(curr)+1));
                        map->at(new_row*size+new_col) = '@';
                    }
                }
            }
        }
        // for(int i = 0; i < map->size();++i){
        //     cout << map->at(i);
        //     if((i+1)%(size) == 0){
        //         cout << endl;
        //     }
        // }
        // cout << endl;

        
    }
    return -1;
}


int main(){
    ifstream simple_file;
    string line;
    
    // Example Test
    simple_file.open("simple.txt");
    int length = 7;
    int width = 7;
    vector<char> simple_map(length*width,'.');
    int bytes_fell = 0;
    while ((getline(simple_file,line)))
    {
        int comma = line.find(",");
        int col = stoi(line.substr(0,comma));
        int row = stoi(line.substr(comma+1,line.length()-comma));
        simple_map[width*row + col] = '#';
        if(solve_maze(&simple_map,length) == -1){
            cout << col << "|" << row << endl;
            break;
        }
    }
    // Input Test
    ifstream input_file;
    input_file.open("input.txt");
    length = 71;
    width = 71;
    vector<char> input_map(length*width,'.');
    bytes_fell = 0;
    while ((getline(input_file,line)))
    {
        int comma = line.find(",");
        int col = stoi(line.substr(0,comma));
        int row = stoi(line.substr(comma+1,line.length()-comma));
        input_map[width*row + col] = '#';
        bytes_fell += 1;
        if(bytes_fell >1024 && solve_maze(&input_map,length) == -1){
            cout << col << "|" << row << endl;
            break;
        }
    }
}