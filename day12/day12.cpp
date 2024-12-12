#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <deque>
#include <sstream>
#include <unordered_map>
#include <cmath>
using namespace std;


int calc_price(vector<vector<char>>* map, vector<vector<bool>>* visited){
    int sum = 0;
    vector<vector<bool>>& visit= *visited;
    for(int i = 0; i < map->size(); ++i){
        for(int j = 0; j < (map->at(i)).size(); ++j){
            // Visited a non visited section
            if(!visited->at(i)[j]){
                // Start doing breadth first search of adjacent sections with the same letter
                deque<pair<int,int>> adj;
                adj.push_back(make_pair(i,j));
                int area_sum = 0;
                int area = 0;
                visited->at(i)[j] = true;
                while(!adj.empty()){
                    area += 1;
                    int row = adj.front().first;
                    int col = adj.front().second;
                    cout << row << "|" << col << endl;
                    
                    adj.pop_front();
                    int temp_sum = 4;
                    //North
                    if(row > 0){
                        if(map->at(row-1)[col] == map->at(row)[col]){
                            if(!visited->at(row-1)[col]){
                                adj.push_back(make_pair(row-1,col));
                                visited->at(row-1)[col] = true;
                            }
                            temp_sum -= 1;
                        }
                    }
                    //East
                    if(col < (map->at(row)).size()-1){
                        if(map->at(row)[col+1] == map->at(row)[col]){
                            if(!visited->at(row)[col+1]){
                                adj.push_back(make_pair(row,col+1));
                                visited->at(row)[col+1] = true;
                            }
                            temp_sum -= 1;
                        }
                    }
                    //South
                    if(row < map->size()-1){
                        if(map->at(row+1)[col] == map->at(row)[col]){
                            if(!visited->at(row+1)[col]){
                                adj.push_back(make_pair(row+1,col));
                                visited->at(row+1)[col] = true;
                            }
                            temp_sum -= 1;
                        }
                    }
                    //West
                    if(col > 0){
                        if(map->at(row)[col-1] == map->at(row)[col]){
                            if(!visited->at(row)[col-1]){
                                adj.push_back(make_pair(row,col-1));
                                visited->at(row)[col-1] = true;
                            }
                            temp_sum -= 1;
                        }
                    }
                    area_sum += temp_sum;
                }
                sum += area_sum*area;
            }
            
        }
    }
    return sum;
}



// Read in 2d vector
// Breadth first search
// Keep track of tracked areas in a second vector
int main(){
    ifstream input_file;
    input_file.open("input.txt");
    string line;
    
    int sum = 0;

    vector<vector<char>> map;
    vector<vector<bool>> visited;
    while(getline(input_file,line)){
        vector<char> l;
        vector<bool> bl;
        for(auto c:line){
            bl.push_back(false);
            l.push_back(c);
        }
        map.push_back(l);
        visited.push_back(bl);
    }
    sum = calc_price(&map,&visited);
    cout << sum << endl;
}