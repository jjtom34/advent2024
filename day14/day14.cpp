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


// Classic modulo math problem
// Teleporting around = modulo around the length/width of the map
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

    int top_left = 0;
    int top_right = 0;
    int bot_left = 0;
    int bot_right = 0;
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
        // Do modulo math
        int new_row = (row + 100*(row_vel))%row_size;
        int new_col = (col + 100*(col_vel))%col_size;
        if(new_row < 0){
            new_row = row_size+new_row;
        }
        if(new_col < 0){
            new_col = col_size+new_col;
        }
        // Top Left
        if(new_row < floor(row_size/2) && new_col < floor(col_size/2)){
            top_left += 1;
        }
        // Top Right
        else if (new_row < floor(row_size/2) && new_col > floor(col_size/2)){
            top_right += 1;
        }
        // Bot Left
        else if (new_row > floor(row_size/2) && new_col < floor(col_size/2)){
            bot_left += 1;
        }
        // Bot Right
        else if (new_row > floor(row_size/2) && new_col > floor(col_size/2)){
            bot_right += 1;
        }
    }
    cout << top_left*top_right*bot_left*bot_right << endl;
}
