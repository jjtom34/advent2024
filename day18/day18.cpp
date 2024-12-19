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

struct node{
    int row;
    int col;
    int dist;
    int dir;
};
struct custom_comp{
    bool operator()(const node l, const node r){
        return l.dist > r.dist;
    }
};
string stringify(int row, int col,int dir){
    return to_string(row) + '|' + to_string(col) + '|' + to_string(dir);
}
tuple<int,int,int> unstring(string s){
    int bar = s.find('|');
    int bar2 = s.find('|',bar+1);
    return make_tuple(stoi(s.substr(0,bar)),stoi(s.substr(bar+1,bar2-bar-1)),stoi(s.substr(bar2 + 1,1)));
}
int dijkstra(vector<vector<char>>*ma, int start_row, int start_col, int end_row, int end_col,set<pair<int,int>>*uniq){
    int distance = 0;
    //Direction
    // NESW
    // 0123
    int direction = 0;
    vector<vector<char>> map = *ma;
    priority_queue<node,vector<node>,custom_comp> prio;
    unordered_map<string,vector<int>> distances;
    unordered_map<string,vector<string>> prev;
    
    node start{start_row,start_col,0,1};
    prio.push(start);
    bool finished = false;
    while(!prio.empty()){
        // Get closest
        node curr = prio.top();
        prio.pop();
        int curr_dist = curr.dist;
        if(map[curr.row][curr.col] == 'E'){
            distance = distances[stringify(curr.row,curr.col,curr.dir)][curr.dir];
            direction = curr.dir;
            finished = true;
            continue;
        }
        if(curr_dist >= 134588){
            // abandon path
            continue;
        }
        // Check all neighbors
        // North
        if(map[curr.row-1][curr.col] != '#' && curr.dir != 2){
            // Subsequent visit so check if it needs to be updated
            int points = curr_dist;
            if(curr.dir != 0){
                points += 1000;
                // Turning counts as own step
                if(distances.find(stringify(curr.row,curr.col,0)) == distances.end() || points <= distances[stringify(curr.row,curr.col,0)][0]){
                    if(distances.find(stringify(curr.row,curr.col,0)) == distances.end()){
                        vector<string> v = {};
                        prev[stringify(curr.row,curr.col,0)] = v;
                        vector<int> d;
                        for(int i = 0; i < 4; ++i){
                            d.push_back(134590);
                        }
                        distances[stringify(curr.row,curr.col,0)] = d;
                    }
                    if(!finished){
                        // Delete Any that are greater than current
                        if(distances[stringify(curr.row,curr.col,0)][0] > points){
                            while(!prev[stringify(curr.row,curr.col,0)].empty()){
                                prev[stringify(curr.row,curr.col,0)].pop_back();
                            }
                        }
                    }
                    distances[stringify(curr.row,curr.col,0)][0] = points;
                    node north{curr.row, curr.col, points, 0};
                    
                    prev[stringify(curr.row,curr.col,0)].push_back(stringify(curr.row,curr.col,curr.dir));
                    prio.push(north);
                }
            }
            else{
                points += 1;
                if(distances.find(stringify(curr.row-1,curr.col,curr.dir)) == distances.end() || points <= distances[stringify(curr.row-1,curr.col,curr.dir)][0]){
                    if(distances.find(stringify(curr.row-1,curr.col,curr.dir)) == distances.end()){
                        vector<string> v = {};
                        prev[stringify(curr.row-1,curr.col,curr.dir)] = v;
                        vector<int> d;
                        for(int i = 0; i < 4; ++i){
                            d.push_back(134590);
                        }
                        distances[stringify(curr.row-1,curr.col,curr.dir)] = d;
                    }
                    if(!finished){
                        // Delete Any that are greater than current
                        if(distances[stringify(curr.row-1,curr.col,curr.dir)][0] > points){
                            while(!prev[stringify(curr.row-1,curr.col,curr.dir)].empty()){
                                prev[stringify(curr.row-1,curr.col,curr.dir)].pop_back();
                            }
                        }
                    }
                    distances[stringify(curr.row-1,curr.col,curr.dir)][0] = points;
                    node north{curr.row-1, curr.col, points, 0};

                    prev[stringify(curr.row-1,curr.col,curr.dir)].push_back(stringify(curr.row,curr.col,curr.dir));
                    prio.push(north);
                }
            }
            
            
        }
        // South
        if(map[curr.row+1][curr.col] != '#'&& curr.dir != 0){
            // Subsequent visit so check if it needs to be updated
            int points = curr_dist;
            if(curr.dir != 2){
                points += 1000;
                // Turning counts as own step
                if(distances.find(stringify(curr.row,curr.col,2)) == distances.end() || points <= distances[stringify(curr.row,curr.col,2)][2]){
                    if(distances.find(stringify(curr.row,curr.col,2)) == distances.end()){
                        vector<string> v = {};
                        prev[stringify(curr.row,curr.col,2)] = v;
                        vector<int> d;
                        for(int i = 0; i < 4; ++i){
                            d.push_back(134590);
                        }
                        distances[stringify(curr.row,curr.col,2)] = d;
                    }
                    if(!finished){
                        // Delete Any that are greater than current
                        if(distances[stringify(curr.row,curr.col,2)][2] > points){
                            while(!prev[stringify(curr.row,curr.col,2)].empty()){
                                prev[stringify(curr.row,curr.col,2)].pop_back();
                            }
                        }
                    }
                    distances[stringify(curr.row,curr.col,2)][2] = points;
                    node north{curr.row, curr.col, points, 2};
                    prev[stringify(curr.row,curr.col,2)].push_back(stringify(curr.row,curr.col,curr.dir));
                    prio.push(north);
                }
            }
            else{
                points += 1;
                if(distances.find(stringify(curr.row+1,curr.col,curr.dir)) == distances.end() || points <= distances[stringify(curr.row+1,curr.col,curr.dir)][2]){
                    if(distances.find(stringify(curr.row+1,curr.col,curr.dir)) == distances.end()){
                        vector<string> v = {};
                        prev[stringify(curr.row+1,curr.col,curr.dir)] = v;
                        vector<int> d;
                        for(int i = 0; i < 4; ++i){
                            d.push_back(134590);
                        }
                        distances[stringify(curr.row+1,curr.col,curr.dir)] = d;
                    }
                    if(!finished){
                        // Delete Any that are greater than current
                        if(distances[stringify(curr.row+1,curr.col,curr.dir)][2] > points){
                            while(!prev[stringify(curr.row+1,curr.col,curr.dir)].empty()){
                                prev[stringify(curr.row+1,curr.col,curr.dir)].pop_back();
                            }
                        }
                    }
                    distances[stringify(curr.row+1,curr.col,curr.dir)][2] = points;
                    node north{curr.row+1, curr.col, points, 2};
                    prev[stringify(curr.row+1,curr.col,curr.dir)].push_back(stringify(curr.row,curr.col,curr.dir));
                    prio.push(north);
                }
            }
        }
        // East
        if(map[curr.row][curr.col+1] != '#'&& curr.dir != 3){
            // Subsequent visit so check if it needs to be updated
            int points = curr_dist;
            if(curr.dir != 1){
                points += 1000;
                // Turning counts as own step
                if(distances.find(stringify(curr.row,curr.col,1)) == distances.end() || points <= distances[stringify(curr.row,curr.col,1)][1]){
                    if(distances.find(stringify(curr.row,curr.col,1)) == distances.end()){
                        vector<string> v = {};
                        prev[stringify(curr.row,curr.col,1)] = v;
                        vector<int> d;
                        for(int i = 0; i < 4; ++i){
                            d.push_back(134590);
                        }
                        distances[stringify(curr.row,curr.col,1)] = d;
                    }
                    if(!finished){
                        // Delete Any that are greater than current
                        if(distances[stringify(curr.row,curr.col,1)][1] > points){
                            while(!prev[stringify(curr.row,curr.col,1)].empty()){
                                prev[stringify(curr.row,curr.col,1)].pop_back();
                            }
                        }
                    }
                    distances[stringify(curr.row,curr.col,1)][1] = points;
                    node north{curr.row, curr.col, points, 1};
                    prev[stringify(curr.row,curr.col,1)].push_back(stringify(curr.row,curr.col,curr.dir));
                    prio.push(north);
                }
            }
            else{
                points += 1;
                if(distances.find(stringify(curr.row,curr.col+1,curr.dir)) == distances.end() || points <= distances[stringify(curr.row,curr.col+1,curr.dir)][1]){
                    if(distances.find(stringify(curr.row,curr.col+1,curr.dir)) == distances.end()){
                        vector<string> v = {};
                        prev[stringify(curr.row,curr.col+1,curr.dir)] = v;
                        vector<int> d;
                        for(int i = 0; i < 4; ++i){
                            d.push_back(134590);
                        }
                        distances[stringify(curr.row,curr.col+1,curr.dir)] = d;
                    }
                    if(!finished){
                        // Delete Any that are greater than current
                        if(distances[stringify(curr.row,curr.col+1,curr.dir)][1] > points){
                            while(!prev[stringify(curr.row,curr.col+1,curr.dir)].empty()){
                                prev[stringify(curr.row,curr.col+1,curr.dir)].pop_back();
                            }
                        }
                    }
                    distances[stringify(curr.row,curr.col+1,curr.dir)][1] = points;
                    node north{curr.row, curr.col+1, points, 1};
                    prev[stringify(curr.row,curr.col+1,curr.dir)].push_back(stringify(curr.row,curr.col,curr.dir));
                    prio.push(north);
                }
            }
            
        }
        // West
        if(map[curr.row][curr.col-1] != '#' && curr.dir != 1){
            // Subsequent visit so check if it needs to be updated
            int points = curr_dist;
            if(curr.dir != 3){
                points += 1000;
                // Turning counts as own step
                if(distances.find(stringify(curr.row,curr.col,3)) == distances.end() || points <= distances[stringify(curr.row,curr.col,3)][3]){
                    if(distances.find(stringify(curr.row,curr.col,3)) == distances.end()){
                        vector<string> v = {};
                        prev[stringify(curr.row,curr.col,3)] = v;
                        vector<int> d;
                        for(int i = 0; i < 4; ++i){
                            d.push_back(134590);
                        }
                        distances[stringify(curr.row,curr.col,3)] = d;
                    }
                    if(!finished){
                        // Delete Any that are greater than current
                        if(distances[stringify(curr.row,curr.col,3)][3] > points){
                            while(!prev[stringify(curr.row,curr.col,3)].empty()){
                                prev[stringify(curr.row,curr.col,3)].pop_back();
                            }
                        }
                    }
                    distances[stringify(curr.row,curr.col,3)][3] = points;
                    node north{curr.row, curr.col, points, 3};
                    prev[stringify(curr.row,curr.col,3)].push_back(stringify(curr.row,curr.col,curr.dir));
                    prio.push(north);
                }
            }
            else{
                points += 1;
                if(distances.find(stringify(curr.row,curr.col-1,curr.dir)) == distances.end() || points <= distances[stringify(curr.row,curr.col-1,curr.dir)][3]){
                    if(distances.find(stringify(curr.row,curr.col-1,curr.dir)) == distances.end()){
                        vector<string> v = {};
                        prev[stringify(curr.row,curr.col-1,curr.dir)] = v;
                        vector<int> d;
                        for(int i = 0; i < 4; ++i){
                            d.push_back(134590);
                        }
                        distances[stringify(curr.row,curr.col-1,curr.dir)] = d;
                    }
                    if(!finished){
                        // Delete Any that are greater than current
                        if(distances[stringify(curr.row,curr.col-1,curr.dir)][3] > points){
                            while(!prev[stringify(curr.row,curr.col-1,curr.dir)].empty()){
                                prev[stringify(curr.row,curr.col-1,curr.dir)].pop_back();
                            }
                        }
                    }
                    distances[stringify(curr.row,curr.col-1,curr.dir)][3] = points;
                    node north{curr.row, curr.col-1, points, 3};
                    prev[stringify(curr.row,curr.col-1,curr.dir)].push_back(stringify(curr.row,curr.col,curr.dir));
                    prio.push(north);
                }
            }
            
        }
    }
    
    // Read in all prevs of the last tile
    deque<string> node_list;
    for(int i = 0; i < 4; ++i){
        // Add to visited list
        for(auto pre:prev[stringify(end_row,end_col,i)]){
            int row = get<0>(unstring(pre));
            int col = get<1>(unstring(pre));
            int dir = get<2>(unstring(pre));
            uniq->emplace(make_pair(row,col));
            if(find(node_list.begin(), node_list.end(), pre) != node_list.end()){
                continue;
            }
            node_list.push_back(pre);
            map[row][col] = '@';
        } 
    }
    
    while(!node_list.empty()){
        string n = node_list.front();
        node_list.pop_front();
        for(auto pre:prev[n]){
            int row = get<0>(unstring(pre));
            int col = get<1>(unstring(pre));
            int dir = get<2>(unstring(pre));
            if(row == start_row && col == start_col){
                continue;
            }
            uniq->emplace(make_pair(row,col));
            if(find(node_list.begin(), node_list.end(), pre) != node_list.end()){
                continue;
            }for(auto c:map){
                for(auto b:c){
                    cout << b;
                }
                cout << endl;
            }
            node_list.push_back(pre);
            map[row][col] = '@';
        } 
    }
    int count = 0;
    for(auto c:map){
        for(auto b:c){
            cout << b;
            if(b != '.' && b !='#'){
                count += 1;
            }
        }
        cout << endl;
    }
    return count;
}

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
        for(int i = 0; i < map->size();++i){
            cout << map->at(i);
            if((i+1)%(size) == 0){
                cout << endl;
            }
        }
        cout << endl;

        
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
    while ((getline(simple_file,line)) && bytes_fell < 12)
    {
        int comma = line.find(",");
        int col = stoi(line.substr(0,comma));
        int row = stoi(line.substr(comma+1,line.length()-comma));
        simple_map[width*row + col] = '#';
        bytes_fell += 1;
    }
    for(int i = 0; i < simple_map.size();++i){
            cout << simple_map.at(i);
            if((i+1)%(length) == 0){
                cout << endl;
            }
        }
    if(solve_maze(&simple_map,length) != 22){
        cout << "Failed Example 1" << endl;
        return 1;
    }

    // Input Test
    ifstream input_file;
    input_file.open("input.txt");
    length = 71;
    width = 71;
    vector<char> input_map(length*width,'.');
    bytes_fell = 0;
    while ((getline(input_file,line)) && bytes_fell < 1024)
    {
        int comma = line.find(",");
        int col = stoi(line.substr(0,comma));
        int row = stoi(line.substr(comma+1,line.length()-comma));
        input_map[width*row + col] = '#';
        bytes_fell += 1;
    }
    for(int i = 0; i < input_map.size();++i){
            cout << input_map.at(i);
            if((i+1)%(length) == 0){
                cout << endl;
            }
        }
    cout << solve_maze(&input_map,length) << endl;
}