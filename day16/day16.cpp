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
pair<int,int> unstring(string s){
    int bar = s.find('|');
    int bar2 = s.find('|',bar+1);
    return make_pair(stoi(s.substr(0,bar)),stoi(s.substr(bar+1,bar2-bar-1)));
}
int dijkstra(vector<vector<char>>*ma, int start_row, int start_col, int end_row, int end_col){
    int distance = 0;
    //Direction
    // NESW
    // 0123
    int direction = 0;
    vector<vector<char>> map = *ma;
    priority_queue<node,vector<node>,custom_comp> prio;
    unordered_map<string,int> distances;
    unordered_map<string,string> prev;
    
    distances[stringify(start_row,start_col,1)];
    node start{start_row,start_col,0,1};
    prio.push(start);
    while(!prio.empty()){
        // Get closest
        node curr = prio.top();
        if(prev[stringify(curr.row,curr.col,curr.dir)] == ""){
            cout << "damn" << endl;
        }
        prio.pop();
        int curr_dist = distances[stringify(curr.row,curr.col,curr.dir)];
        if(map[curr.row][curr.col] == 'E'){
            distance = distances[stringify(curr.row,curr.col,curr.dir)];
            direction = curr.dir;
            break;
        }
        // Check all neighbors
        // North
        if(map[curr.row-1][curr.col] != '#'){
            // Subsequent visit so check if it needs to be updated
            int points = curr_dist;
            if(curr.dir != 0){
                points += 1000;
                // Turning counts as own step
                if(distances.find(stringify(curr.row,curr.col,0)) == distances.end() || points < distances[stringify(curr.row,curr.col,0)]){
                    distances[stringify(curr.row,curr.col,0)] = points;
                    node north{curr.row, curr.col, points, 0};
                    prev[stringify(curr.row,curr.col,0)] = stringify(curr.row,curr.col,curr.dir);
                    prio.push(north);
                }
            }
            else{
                points += 1;
                if(distances.find(stringify(curr.row-1,curr.col,curr.dir)) == distances.end() || points < distances[stringify(curr.row-1,curr.col,curr.dir)]){
                    distances[stringify(curr.row-1,curr.col,curr.dir)] = points;
                    node north{curr.row-1, curr.col, points, 0};
                    prev[stringify(curr.row-1,curr.col,curr.dir)] = stringify(curr.row,curr.col,curr.dir);
                    prio.push(north);
                }
            }
            
            
        }
        // South
        if(map[curr.row+1][curr.col] != '#'){
            // Subsequent visit so check if it needs to be updated
            int points = curr_dist;
            if(curr.dir != 2){
                points += 1000;
                // Turning counts as own step
                if(distances.find(stringify(curr.row,curr.col,2)) == distances.end() || points < distances[stringify(curr.row,curr.col,2)]){
                    distances[stringify(curr.row,curr.col,2)] = points;
                    node north{curr.row, curr.col, points, 2};
                    prev[stringify(curr.row,curr.col,2)] = stringify(curr.row,curr.col,curr.dir);
                    prio.push(north);
                }
            }
            else{
                points += 1;
                if(distances.find(stringify(curr.row+1,curr.col,curr.dir)) == distances.end() || points < distances[stringify(curr.row+1,curr.col,curr.dir)]){
                    distances[stringify(curr.row+1,curr.col,curr.dir)] = points;
                    node north{curr.row+1, curr.col, points, 2};
                    prev[stringify(curr.row+1,curr.col,curr.dir)] = stringify(curr.row,curr.col,curr.dir);
                    prio.push(north);
                }
            }
        }
        // East
        if(map[curr.row][curr.col+1] != '#'){
            // Subsequent visit so check if it needs to be updated
            int points = curr_dist;
            if(curr.dir != 1){
                points += 1000;
                // Turning counts as own step
                if(distances.find(stringify(curr.row,curr.col,1)) == distances.end() || points < distances[stringify(curr.row,curr.col,1)]){
                    distances[stringify(curr.row,curr.col,1)] = points;
                    node north{curr.row, curr.col, points, 1};
                    prev[stringify(curr.row,curr.col,1)] = stringify(curr.row,curr.col,curr.dir);
                    prio.push(north);
                }
            }
            else{
                points += 1;
                if(distances.find(stringify(curr.row,curr.col+1,curr.dir)) == distances.end() || points < distances[stringify(curr.row,curr.col+1,curr.dir)]){
                    distances[stringify(curr.row,curr.col+1,curr.dir)] = points;
                    node north{curr.row, curr.col+1, points, 1};
                    prev[stringify(curr.row,curr.col+1,curr.dir)] = stringify(curr.row,curr.col,curr.dir);
                    prio.push(north);
                }
            }
            
        }
        // West
        if(map[curr.row][curr.col-1] != '#'){
            // Subsequent visit so check if it needs to be updated
            int points = curr_dist;
            if(curr.dir != 3){
                points += 1000;
                // Turning counts as own step
                if(distances.find(stringify(curr.row,curr.col,3)) == distances.end() || points < distances[stringify(curr.row,curr.col,3)]){
                    distances[stringify(curr.row,curr.col,3)] = points;
                    node north{curr.row, curr.col, points, 3};
                    prev[stringify(curr.row,curr.col,3)] = stringify(curr.row,curr.col,curr.dir);
                    prio.push(north);
                }
            }
            else{
                points += 1;
                if(distances.find(stringify(curr.row,curr.col-1,curr.dir)) == distances.end() || points < distances[stringify(curr.row,curr.col-1,curr.dir)]){
                    distances[stringify(curr.row,curr.col-1,curr.dir)] = points;
                    node north{curr.row, curr.col-1, points, 3};
                    prev[stringify(curr.row,curr.col-1,curr.dir)] = stringify(curr.row,curr.col,curr.dir);
                    prio.push(north);
                }
            }
            
        }
    }
    string p = stringify(end_row,end_col,direction);
    while(p != stringify(start_row,start_col,1) && p != ""){
        cout << p << endl;
        map[unstring(p).first][unstring(p).second] = 'X';
        p = prev[p];
    }
    cout << p << endl;
    for(auto c:map){
        for(auto b:c){
            cout << b;
        }
        cout << endl;
    }
    return distance;
}

int main(){
    ifstream input_file;
    input_file.open("input.txt");
    string line;
    vector<vector<char>> map;
    int start_row;
    int start_col;
    int end_row;
    int end_col;
    int rows = 0;
    int cols;
    while ((getline(input_file,line)))
    {
        vector<char> new_line;
        cols = 0;
        for (auto &&c : line)
        {
            if(c == 'S'){
                start_row = rows;
                start_col = cols;
            }
            if(c == 'E'){
                end_row = rows;
                end_col = cols;
            }
            cols++;
            new_line.push_back(c);
        }
        rows++;
        map.push_back(new_line);
    }
    
    cout <<dijkstra(&map,start_row,start_col,end_row,end_col) << endl;
    // Find a Path
    // Dijkstras?
    // Every node is a node

    // On every iteration, visit the shortest node
    // Update every estimate for all visited nodes

}