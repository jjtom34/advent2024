#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;


bool traverse_map(vector<vector<char>>* thing, int direction,int i, int j,unordered_map<string,vector<bool>>* visited){
    bool done = false;
    vector<vector<char>> map = (*thing);
    unordered_map<string,vector<bool>> visit = (*visited);
    cout << "Last Pos" << i << "|" << j << endl;
    while(!done){
        map[i][j] = 'X';
        switch (direction){
            // North
            case 8:
                if(i-1 < 0){
                    done = true;
                    break;
                }else{
                    if(map[i-1][j] == '#'){
                        // Check if the turned direction is within bounds
                        if(j+1 >= map[0].size()){
                            done = true;
                            break;
                        }else{
                            string pos = to_string(i-1) + "|" + to_string(j);
                            if(visit.find(pos) == visit.end()){
                                vector<bool> dirs = {true, false, false, false};
                                visit[pos] = dirs;
                            }
                            else{
                                if(visit[pos][0]){
                                    return true;
                                }
                                else{
                                    visit[pos][0] = true;
                                }
                            }
                            map[i][j] = '+';
                            direction = 6;
                            
                        }
                    }
                    else{
                        // Move the guard
                        i -= 1;
                    }
                }
                break;

            // East
            case 6:
                if(j+1 >= map[0].size()){
                    done = true;
                    break;
                }else{
                    if(map[i][j+1] == '#'){
                        // Check if the turned direction is within bounds
                        if(i+1 >= map.size()){
                            done = true;
                            break;
                        }
                        else{
                            string pos = to_string(i) + "|" + to_string(j+1);
                            if(visit.find(pos) == visit.end()){
                                vector<bool> dirs = {false, true, false, false};
                                visit[pos] = dirs;
                            }
                            else{
                                if(visit[pos][1]){
                                    return true;
                                }
                                else{
                                    visit[pos][1] = true;
                                }
                            }
                            map[i][j] = '+';
                            direction = 2;
                            
                        }
                    }
                    else{
                        // Move the guard
                        j += 1;
                    }
                }
                break;

            // South
            case 2:
                if(i+1 >= map.size()){
                    done = true;
                    break;
                }else{
                    if(map[i+1][j] == '#'){
                        // Check if the turned direction is within bounds
                        if(j-1 < 0){
                            done = true;
                            break;
                        }
                        else{
                            string pos = to_string(i+1) + "|" + to_string(j);
                            if(visit.find(pos) == visit.end()){
                                vector<bool> dirs = {false, false, true, false};
                                visit[pos] = dirs;
                            }
                            else{
                                if(visit[pos][2]){
                                    return true;
                                }
                                else{
                                    visit[pos][2] = true;
                                }
                            }
                            map[i][j] = '+';
                            direction = 4;
                            
                        }
                    }
                    else{
                        // Move the guard
                        i+=1;
                    }
                }
                break;

            // West
            case 4:
                if(j-1 < 0){
                    done = true;
                    break;
                }else{
                    if(map[i][j-1] == '#'){
                        // Check if the turned direction is within bounds
                        if(i-1 < 0){
                            done = true;
                            break;
                        }
                        else{
                            string pos = to_string(i) + "|" + to_string(j-1);
                            if(visit.find(pos) == visit.end()){
                                vector<bool> dirs = {false, false, false, true};
                                visit[pos] = dirs;
                            }
                            else{
                                if(visit[pos][3]){
                                    return true;
                                }
                                else{
                                    visit[pos][3] = true;
                                }
                            }
                            map[i][j] = '+';
                            direction = 8;
                            
                        }
                    }
                    else{
                        // Move the guard
                        j -= 1;
                    }
                }
                break; 
        }
    //     cout << endl;
    // for(auto i:(map)){
    //     for(auto j:i){
    //         cout << j;
    //     }
    //     cout << endl;
    // }
    }
    return false;
}

bool is_loop(vector<vector<char>>* thing, int direction,int i, int j,unordered_map<string,vector<bool>>* visited){
    // Immedietely turn right
    // If you ever hit the same direction you've made a loop
    // If you get to the end theres no loop.
    vector<vector<char>> map = (*thing);
    
    switch(direction){
        case 8:
            // Place new obstacle
            if(i-1 < 0){
                break;
            }else{
                if(map[i-1][j] != '.'){
                    return false;
                }
                map[i-1][j] = '#';
                // Follow new path
                
            }
            break;
        case 6:
            // Place new obstacle
            if(j+1 >= map[0].size()){
                break;
            }else{
                if(map[i][j+1] != '.'){
                    return false;
                }
                map[i][j+1] = '#';
                // Follow new path
                
            }
            break;
        case 2:
            // Place new obstacle
            if(i+1 >= map[0].size()){
                break;
            }else{
                if(map[i+1][j] != '.'){
                    return false;
                }
                map[i+1][j] = '#';
                // Follow new path
                
            }
            break;
        case 4:
            // Place new obstacle
            if(j-1 < 0){
                break;
            }else{
                if(map[i][j-1] != '.'){
                    return false;
                }
                map[i][j-1] = '#';
                // Follow new path
                
            }
            break;
    }
    // cout << endl;
    // for(auto i:(map)){
    //     for(auto j:i){
    //         cout << j;
    //     }
    //     cout << endl;
    // }
    return traverse_map(&map,direction,i,j,visited);
}
// Initial solution to part 2
// Just brute force it
// At every step just see if adding another turn either causes a loop or exits the maze
// you know if you cause a loop by reentering a previous part of the path.
int main(){
    int sum = 0;
    ifstream input_file;
    input_file.open("input.txt");
    string line;
    vector<vector<char>> guard_map;
    vector<string> visited;
    // Current direction of the guard
    // numpad notation
    // X8X
    // 4X6
    // X2X
    int direction;
    int guard_i = 0;
    int guard_j = 0;
    
    bool guard_found = false;
    // Read in the map and check the initial direction
    while(getline(input_file,line)){
        vector<char> newline;
        int j = 0;
        for(auto s:line){
            if(s == '^'){
                direction = 8;
                    guard_j = j;
                    guard_found = true;
            }
            j+=1;
            newline.push_back((s));
            
        }
        if(!guard_found){
            guard_i+=1;
        }
        guard_map.push_back(newline);
    }
    int start_i= guard_i;
    int start_j = guard_j;
    for(int i = 0; i < guard_map.size(); ++i){
        for(auto j:guard_map[i]){
            cout << j;
        }
        cout <<endl;
    }
    // Start walking
    bool done = false;
    unordered_map<string,vector<bool>> visited_obstacle;
    while(guard_i >= 0 && 
            guard_i < guard_map.size() && 
            guard_j >= 0 && 
            guard_j < guard_map[0].size()){
        if(done){break;}
        guard_map[guard_i][guard_j] = 'X';
        switch (direction){
            // Current direction of the guard
            // numpad notation
            // X8X
            // 4X6
            // X2X

            // Based on Direction
            // 1. Replace current space with an X
            // 2. Check if next space in direction is either off the map and then wall/space
            // 3. Move if an empty space/x, turn 90 degrees if obstacle.
            // 3b. Also need to check if the turned direction is also an obstacle, if so just reverse the direction instead.
            // North
            case 8:
                
                if(guard_i-1 < 0){
                    done = true;
                    break;
                }else{
                    string pos = to_string(guard_i-1) + "|" + to_string(guard_j);
                    if(guard_map[guard_i-1][guard_j] == '#'){
                        // Check if the turned direction is within bounds
                        if(guard_j+1 >= guard_map[0].size()){
                            done = true;
                            break;
                        }else{
                            if(visited_obstacle.find(pos) == visited_obstacle.end()){
                                vector<bool> dirs = {true, false, false, false};
                                visited_obstacle[pos] = dirs;
                            }
                            else{
                                visited_obstacle[pos][0] = true;
                            }
                            guard_map[guard_i][guard_j] = '+';
                            direction = 6;
                        }

                    }else{
                        if(is_loop(&guard_map,direction,guard_i,guard_j,&visited_obstacle)){
                            if(find(visited.begin(),visited.end(),pos) == visited.end() && ((guard_i-1) != start_i || guard_j != start_j)){
                                visited.push_back(pos);
                            }
                            sum += 1;
                        }
                        // Move the guard
                        guard_i -= 1;
                    }
                }
                break;

            // East
            case 6:
                if(guard_j+1 >= guard_map[0].size()){
                    done = true;
                    break;
                }else{
                    string pos = to_string(guard_i) + "|" + to_string(guard_j+1);
                    if(guard_map[guard_i][guard_j+1] == '#'){
                        // Check if the turned direction is within bounds
                        if(guard_i+1 >= guard_map.size()){
                            done = true;
                            break;
                        }else{
                            
                            if(visited_obstacle.find(pos) == visited_obstacle.end()){
                                vector<bool> dirs = {false, true, false, false};
                                visited_obstacle[pos] = dirs;
                            }
                            else{
                                visited_obstacle[pos][1] = true;
                            }
                            guard_map[guard_i][guard_j] = '+';
                            direction = 2;
                        }
                    }else{
                        if(is_loop(&guard_map,direction,guard_i,guard_j,&visited_obstacle)){
                            if(find(visited.begin(),visited.end(),pos) == visited.end() && (guard_i != start_i || (guard_j+1) != start_j)){
                                visited.push_back(pos);
                            }
                            sum += 1;
                        }
                        // Move the guard
                        guard_j += 1;
                    }
                }
                break;

            // South
            case 2:
                if(guard_i+1 >= guard_map.size()){
                    done = true;
                    break;
                }else{
                    string pos = to_string(guard_i+1) + "|" + to_string(guard_j);
                    if(guard_map[guard_i+1][guard_j] == '#'){
                        // Check if the turned direction is within bounds
                        if(guard_j-1 < 0){
                            done = true;
                            break;
                        }else{
                            
                            if(visited_obstacle.find(pos) == visited_obstacle.end()){
                                vector<bool> dirs = {false, false, true, false};
                                visited_obstacle[pos] = dirs;
                            }
                            else{
                                visited_obstacle[pos][2] = true;
                            }
                            guard_map[guard_i][guard_j] = '+';
                            direction = 4;
                        }
                    }else{
                        if(is_loop(&guard_map,direction,guard_i,guard_j,&visited_obstacle)){
                            if(find(visited.begin(),visited.end(),pos) == visited.end() && ((guard_i+1) != start_i || guard_j != start_j)){
                                visited.push_back(pos);
                            }
                            sum += 1;
                        }
                        // Move the guard
                        guard_i += 1;
                    }
                }
                break;

            // West
            case 4:
                if(guard_j-1 < 0){
                    done = true;
                    break;
                }else{
                    string pos = to_string(guard_i) + "|" + to_string(guard_j-1);
                    if(guard_map[guard_i][guard_j-1] == '#'){
                        // Check if the turned direction is within bounds
                        if(guard_i-1 < 0){
                            done = true;
                            break;
                        }else{
                            if(visited_obstacle.find(pos) == visited_obstacle.end()){
                                vector<bool> dirs = {false, false, false, true};
                                visited_obstacle[pos] = dirs;
                            }
                            else{
                                visited_obstacle[pos][3] = true;
                            }
                            guard_map[guard_i][guard_j] = '+';
                            direction = 8;
                        }
                    }else{
                        if(is_loop(&guard_map,direction,guard_i,guard_j,&visited_obstacle)){
                            if(find(visited.begin(),visited.end(),pos) == visited.end() && (guard_i != start_i || (guard_j-1) != start_j)){
                                visited.push_back(pos);
                            }
                            sum += 1;
                        }
                        // Move the guard
                        guard_j -= 1;
                    }
                }
                break; 
        }
        cout << endl;
        for(auto i:guard_map){
            for(auto j:i){
                cout << j;
            }
            cout << endl;
        }
    }
    // for(auto i:guard_map){
    //     for(auto j:i){
    //         cout << j;
    //         if(j != '#' && j != '.'){
    //             sum += 1;
    //         }
    //     }
    //     cout << endl;
    // }
    sort( visited.begin(), visited.end() );
    visited.erase( unique( visited.begin(), visited.end() ), visited.end() );
    cout << visited.size() << endl;

}