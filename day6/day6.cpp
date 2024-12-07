#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

int main(){
    int sum = 0;
    ifstream input_file;
    input_file.open("input.txt");
    string line;
    vector<vector<char>> guard_map;
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
            switch (s){
                case '^':
                    direction = 8;
                    guard_j = j;
                    guard_found = true;
                    break;
                case '>':
                    direction = 6;
                    guard_j = j;
                    guard_found = true;
                    break;
                case '<':
                    direction = 4;
                    guard_j = j;
                    guard_found = true;
                    break;
                case 'v':
                    direction = 2;
                    guard_j = j;
                    guard_found = true;
                    break;
            }
            j+=1;
            newline.push_back((s));
            
        }
        if(!guard_found){
            guard_i+=1;
        }
        guard_map.push_back(newline);
    }
    for(int i = 0; i < guard_map.size(); ++i){
        for(auto j:guard_map[i]){
            cout << j;
        }
        cout <<endl;
    }
    // Start walking
    bool done;
    while(guard_i >= 0 && 
            guard_i < guard_map.size() && 
            guard_j >= 0 && 
            guard_j < guard_map[0].size()){
        if(done){break;}
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
                guard_map[guard_i][guard_j] = 'X';
                if(guard_i-1 < 0){
                    done = true;
                    break;
                }else{
                    if(guard_map[guard_i-1][guard_j] == '#'){
                        // Check if the turned direction is within bounds
                        if(guard_j+1 >= guard_map[0].size()){
                            done = true;
                            break;
                        }else{
                            if(guard_map[guard_i][guard_j+1] == '#'){
                                //If two obstacles forming a corner, equivalent to 180 degree turn.
                                direction = 2;
                                guard_i +=1;
                            }
                            else{
                                direction = 6;
                                guard_j += 1;
                            }
                        }

                    }else{
                        // Move the guard
                        guard_i -= 1;
                    }
                }
                break;

            // East
            case 6:
                guard_map[guard_i][guard_j] = 'X';
                if(guard_j+1 >= guard_map[0].size()){
                    done = true;
                    break;
                }else{
                    if(guard_map[guard_i][guard_j+1] == '#'){
                        // Check if the turned direction is within bounds
                        if(guard_i+1 >= guard_map.size()){
                            done = true;
                            break;
                        }else{
                            if(guard_map[guard_i+1][guard_j] == '#'){
                                //If two obstacles forming a corner, equivalent to 180 degree turn.
                                direction = 4;
                                guard_j -= 1;
                            }
                            else{
                                direction = 2;
                                guard_i += 1;
                            }
                        }
                    }else{
                        // Move the guard
                        guard_j += 1;
                    }
                }
                break;

            // South
            case 2:
                guard_map[guard_i][guard_j] = 'X';
                if(guard_i+1 >= guard_map.size()){
                    done = true;
                    break;
                }else{
                    if(guard_map[guard_i+1][guard_j] == '#'){
                        // Check if the turned direction is within bounds
                        if(guard_j-1 < 0){
                            done = true;
                            break;
                        }else{
                            if(guard_map[guard_i][guard_j-1] == '#'){
                                //If two obstacles forming a corner, equivalent to 180 degree turn.
                                direction = 8;
                                guard_i -=1;
                            }
                            else{
                                direction = 4;
                                guard_j -= 1;
                            }
                        }
                    }else{
                        // Move the guard
                        guard_i += 1;
                    }
                }
                break;

            // West
            case 4:
               guard_map[guard_i][guard_j] = 'X';
                if(guard_j-1 < 0){
                    done = true;
                    break;
                }else{
                    if(guard_map[guard_i][guard_j-1] == '#'){
                        // Check if the turned direction is within bounds
                        if(guard_i-1 < 0){
                            done = true;
                            break;
                        }else{
                            if(guard_map[guard_i-1][guard_j] == '#'){
                                //If two obstacles forming a corner, equivalent to 180 degree turn.
                                direction = 6;
                                guard_j += 1;
                            }
                            else{
                                direction = 8;
                                guard_i -= 1;
                            }
                        }
                    }else{
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
    for(auto i:guard_map){
        for(auto j:i){
            cout << j;
            if(j == 'X'){
                sum += 1;
            }
        }
        cout << endl;
    }
    cout << sum << endl;
}