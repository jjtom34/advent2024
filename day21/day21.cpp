#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <sstream>
#include <deque>
#include <set>

using namespace std;

/*
Numpad robot
Robot 1
Robot 2
Input


<A
v<<A>>^A
v<A<AA>>^AVAA

// Build numpad inputs first
// Then for every one of those expand on robot 1
// Then for every one of those expand on robot 2
// Thats your input

Part 2 probably has more robots so just continue this pattern for x number of robots

*/

class numpad_savage{
    private:
        long num_robots;
        string file;
        vector<string> codes;
        void read_file(string file);
        vector<string> solve_numpad(string code);
        vector<string> solve_direction(vector<string>);
        string get_sequence(string code);
    public:
        numpad_savage(long num, string file){
            num_robots = num;
            read_file(file);
        }
        long calc_complexity();

};
void numpad_savage::read_file(string file){
    ifstream in;
    in.open(file);
    string line;
    while(getline(in,line)){
        codes.push_back(line);
    }
}
string move_vertical(int* row, int target_row,string*move){
    string move2 = "";
    while(*row != target_row){
        // Move up
        if(*row > target_row){
            *row -= 1;
            move2 += '^';
        }
        // Move down
        // Can't move down if at 1
        else if(*row < target_row){
            *row += 1;
            move2 += 'v';
        }
    }
    return *move + move2;
}
string move_horizontal(int* col, int target_col,string*move){
    string move2 = "";
    while(*col != target_col){
        if(*col < target_col ){
            *col +=1;
            move2 += '>';
        }
        // Move Left
        // Cant move left if at 0
        else if(*col > target_col){
            *col -=1;
            move2 += '<';
        }
    }
    return *move + move2;
}
// Based on the current code, solve the movements required on the numpad
vector<string> numpad_savage::solve_numpad(string code){
    int row = 3;
    int col= 2;
    vector<string> moves;
    // 0-9 A
    vector<int> rows = {3,2,2,2,1,1,1,0,0,0,3};
    vector<int> cols = {1,0,1,2,0,1,2,0,1,2,2};
    for(auto c :code){
        int target_row,target_col;
        string move = "";
        if(c != 'A'){
            int num = c-'0';
            target_row = rows[num];
            target_col = cols[num];
        }
        else{
            target_row = rows[10];
            target_col = cols[10];
        }
        // Instead of picking any direction, make sure you don't have to break inbetween
        // Do this by checking if you you would run into a thing first
        
        if(col == 0 && target_row == 3){
            move = move_horizontal(&col,target_col,&move);
            move = move_vertical(&row,target_row,&move);
        }
        else if(row == 3 && target_col == 0){
            move = move_vertical(&row,target_row,&move);
            move = move_horizontal(&col,target_col,&move);
        }
        else{
            // Up Right
            if(row >= target_row && col <= target_col){
                move = move_vertical(&row,target_row,&move);
                move = move_horizontal(&col,target_col,&move);
            }
            // Down Right
            else if(row <= target_row && col <= target_col){
                move = move_vertical(&row,target_row,&move);
                move = move_horizontal(&col,target_col,&move);
            }
            // Left Up
            else if(row >= target_row && col >= target_col){
                move = move_horizontal(&col,target_col,&move);
                move = move_vertical(&row,target_row,&move);
            }
            // Left Down 
            else if(row <= target_row && col >= target_col){
                move = move_horizontal(&col,target_col,&move);
                move = move_vertical(&row,target_row,&move);
            }    
        }
        // You need to actually press the button after reaching a location
        moves.push_back(move);
    }
    return moves;
}
vector<string> numpad_savage::solve_direction(vector<string> codes){
    int row = 0;
    int col= 2;
    vector<string> moves;
    // ^ v < > A
    vector<int> rows = {0,1,1,1,0};
    vector<int> cols = {1,1,0,2,2};
    for(auto code :codes){
        // There needs to be an a press after each movement
        code += "A";
        for(auto c:code){
            int target_row,target_col;
            string move = "";
            int num;
            switch(c){
                    case '^':
                        num = 0;
                        break;
                    case 'v':
                        num = 1;
                        break;
                    case '<':
                        num = 2;
                        break;
                    case '>':
                        num = 3;
                        break;
                    case 'A': 
                        num = 4;
                        break;      
            }
            target_row = rows[num];
            target_col = cols[num];
            if(row == 0 && target_col == 0){
                move = move_vertical(&row,target_row,&move);
                move = move_horizontal(&col,target_col,&move);
            }
            else if (col == 0 && target_row == 0){
                move = move_horizontal(&col,target_col,&move);
                move = move_vertical(&row,target_row,&move);
            }
            else{
                // Up Right
                if(row >= target_row && col <= target_col){
                    move = move_vertical(&row,target_row,&move);
                    move = move_horizontal(&col,target_col,&move);
                }
                // Down Right
                else if(row <= target_row && col <= target_col){
                    move = move_vertical(&row,target_row,&move);
                    move = move_horizontal(&col,target_col,&move);
                }
                // Left Up
                else if(row >= target_row && col >= target_col){
                    move = move_horizontal(&col,target_col,&move);
                    move = move_vertical(&row,target_row,&move);
                }
                // Left Down 
                else if(row <= target_row && col >= target_col){
                    move = move_horizontal(&col,target_col,&move);
                    move = move_vertical(&row,target_row,&move);
                }
            }
            // You need to actually press the button after reaching a location
            moves.push_back(move);
        }
    }
    return moves;
}
// <A^A^^<A<<<A

// <AAv<AA
// v<<AA>^AA
string numpad_savage::get_sequence(string code){
    vector<string> initial = solve_numpad(code);
    string sequence;
    for(int i = 0; i < this->num_robots; ++i){
        initial = solve_direction(initial);
        sequence = "";
        for(auto l:initial){
            sequence += l + "A";
            cout << l <<"A";
        }
        cout << endl;
    }
    return sequence;
}
long numpad_savage::calc_complexity(){
    long complexity = 0;
    for(auto &&c:this->codes){
        //Numeric Part
        long numeric= stoi(c.substr(0,c.find('A')));
        //Length of sequence
        long length = get_sequence(c).length();
        cout << length << "|" << numeric << endl;
        complexity += numeric*length;
    }
    
    return complexity;
}
int main(){
    numpad_savage simple(2,"simple.txt");
    if(simple.calc_complexity() != 126384){
        cout << "Example Broke" << endl;
        return -1;
    }
    numpad_savage puzzle(2,"input.txt");
    cout << puzzle.calc_complexity() << endl;
}