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
                int corners = 0;
                while(!adj.empty()){
                    area += 1;
                    int row = adj.front().first;
                    int col = adj.front().second;
                    cout << row << "|" << col << endl;
                    cout << map->at(row)[col] << endl;
                    vector<bool> adj_check = {false,false,false,false};
                    char curr = map->at(row)[col];
                    adj.pop_front();
                    //North
                    if(row > 0){
                        if(map->at(row-1)[col] == curr){
                            if(!visited->at(row-1)[col]){
                                adj.push_back(make_pair(row-1,col));
                                visited->at(row-1)[col] = true;
                            }
                        }
                        adj_check[0] = true;
                    }
                    //East
                    if(col < (map->at(row)).size()-1){
                        if(map->at(row)[col+1] == curr){
                            if(!visited->at(row)[col+1]){
                                adj.push_back(make_pair(row,col+1));
                                visited->at(row)[col+1] = true;
                            }
                        }
                        adj_check[1] = true;
                    }
                    //South
                    if(row < map->size()-1){
                        if(map->at(row+1)[col] == curr){
                            if(!visited->at(row+1)[col]){
                                adj.push_back(make_pair(row+1,col));
                                visited->at(row+1)[col] = true;
                            }
                        }
                        adj_check[2] = true;
                    }
                    //West
                    if(col > 0){
                        if(map->at(row)[col-1] == curr){
                            if(!visited->at(row)[col-1]){
                                adj.push_back(make_pair(row,col-1));
                                visited->at(row)[col-1] = true;
                            }
                        }
                        adj_check[3] = true;
                    }

                    // if tile is available
                    bool top = adj_check[0];
                    bool left= adj_check[3];
                    bool right = adj_check[1];
                    bool bot = adj_check[2];
                    // Check for corners
                    // North East
                    if(top && right){
                        // all three available check concave/convex
                        if(map->at(row-1)[col] != curr && map->at(row)[col+1] != curr ){
                            corners +=1;
                        }
                        if(map->at(row-1)[col] == curr && map->at(row)[col+1] == curr && map->at(row-1)[col+1] != curr){
                            corners += 1;
                        }
                    }
                    // South East
                    if(bot && right){
                        // all three available check concave/convex
                        if(map->at(row+1)[col] != curr && map->at(row)[col+1] != curr){
                            corners +=1;
                        }
                        if(map->at(row+1)[col] == curr && map->at(row)[col+1] == curr && map->at(row+1)[col+1] != curr){
                            corners += 1;
                        }
                    }
                    // South West
                    if(bot && left){
                        // all three available check concave/convex
                        if(map->at(row+1)[col] != curr && map->at(row)[col-1] != curr){
                            corners +=1;
                        }
                        if(map->at(row+1)[col] == curr && map->at(row)[col-1] == curr && map->at(row+1)[col-1] != curr){
                            corners += 1;
                        }
                    }
                    //North East
                    if(top && left){
                        // all three available check concave/convex
                        if(map->at(row-1)[col] != curr && map->at(row)[col-1] != curr){
                            corners +=1;
                        }
                        if(map->at(row-1)[col] == curr && map->at(row)[col-1] == curr && map->at(row-1)[col-1] != curr){
                            corners += 1;
                        }
                    }

                    // Already in Explicit corners
                    if(!top && !left){
                        corners += 1;
                    }
                    if(!top && !right){
                        corners += 1;
                    }
                    if(!bot && !left){
                        corners += 1;
                    }
                    if(!bot && !right){
                        corners += 1;
                    }
                    // Border cases
                    // Top Border left or right corner
                    if(!top){
                        if(left){
                            if(map->at(row)[col-1] != curr){
                                corners += 1;
                            }
                        }
                        if(right){
                            if(map->at(row)[col+1] != curr){
                                corners += 1;
                            }
                        }   
                    }
                    // On right border and top or bottom corner
                    if(!right){
                        if(top){
                            if(map->at(row-1)[col] != curr){
                                corners += 1;
                            }
                        }
                        if(bot){
                            if(map->at(row+1)[col] != curr){
                                corners += 1;
                            }
                        }   
                    }
                    // On bot border and left or right
                    if(!bot){
                        if(left){
                            if(map->at(row)[col-1] != curr){
                                corners += 1;
                            }
                        }
                        if(right){
                            if(map->at(row)[col+1] != curr){
                                corners += 1;
                            }
                        }   
                    }
                    // On left border and top or bottom corner
                    if(!left){
                        if(top){
                            if(map->at(row-1)[col] != curr){
                                corners += 1;
                            }
                        }
                        if(bot){
                            if(map->at(row+1)[col] != curr){
                                corners += 1;
                            }
                        }   
                    }
                }
                sum += corners*area;
            }
            
        }
    }
    return sum;
}



// Read in 2d vector
// Breadth first search
// Keep track of tracked areas in a second vector

//Keep track of corners instead of perimeters
// Corners = Number of sides
// Corners = 2 adjacent sides empty + corner
// or = 2 adjacent sides full but not corner.
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