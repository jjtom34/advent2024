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

struct robot{
    int row;
    int col;
    int row_vel;
    int col_vel;
};
//No longer a modulo math problem
// Well Kinda but its mostly just implementing visuals
int main(){
    ifstream input_file;
    input_file.open("input.txt");
    string line;
    int rows = 0;
    int cols = 0;
    int safety = 1;

    // Change these when switching to actual input;
    int col_size = 101;
    int row_size = 103;

    vector<vector<char>> visuals(row_size,vector<char>(col_size,'.'));
    vector<robot> robots;
    while(getline(input_file,line)){
        int eq = line.find("=");
        int comma = line.find(",");
        int space = line.find(" ");
        int second_eq = line.find("=",space);
        int second_comma = line.find(",",second_eq);
        int col = stoi(line.substr(eq+1,comma-eq-1));
        int row = stoi(line.substr(comma+1,space-comma-1));
        int col_vel = stoi(line.substr(second_eq+1,second_comma-second_eq-1));
        int row_vel = stoi(line.substr(second_comma+1,line.size()-second_comma-1));
        robot new_robot;
        new_robot.row = row;
        new_robot.col = col;
        new_robot.col_vel = col_vel;
        new_robot.row_vel = row_vel;
        robots.push_back(new_robot);
        visuals[row][col] = '*';
    }
    ofstream output_file;
    output_file.open("output.txt");
    for(int i = 0; i <= 10000; ++i){
        // Print map
        
        for(auto line:visuals){
            string out_line = "";
            for(auto c:line){
                out_line += c;
                //cout << c;
            }
            //cout << endl;
            out_line += '\n';
            output_file << out_line;
        }
        //cout << endl;
        output_file << endl;
        // Reset the map
        for(int j = 0; j < visuals.size(); ++j){
            for(int k = 0; k < visuals[j].size(); ++k){
                visuals[j][k] = '.';
            }
        }
        bool bad = false;
        for(auto rob:robots){
            // Move the robots
            int new_row = (rob.row + i*(rob.row_vel))%row_size;
            int new_col = (rob.col + i*(rob.col_vel))%col_size;
            if(new_row < 0){
                new_row = row_size+new_row;
            }
            if(new_col < 0){
                new_col = col_size+new_col;
            }
            if(visuals[new_row][new_col] == '*'){
                bad = true;
            }
            visuals[new_row][new_col] = '*';
        }
        if(!bad){
            cout << i << endl;
            break;
        }
    }
    for(auto line:visuals){
        for(auto c:line){
            cout << c;
        }
        cout << endl;
    }
}
