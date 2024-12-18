#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <sstream>
#include <deque>

using namespace std;

int get_combo(int pc, vector<int>*program, int* a, int* b, int* c){
    if(pc<program->size()-1){
        switch(program->at(pc+1)){
            case 0:
            case 1:
            case 2:
            case 3:
                return program->at(pc+1);
            case 4:
                return *a;
            case 5:
                return *b;
            case 6:
                return *c;
        }
    }
    return -1;
}

int get_literal(int pc, vector<int>*program){
    return program->at(pc+1);
}

string run_program(vector<int>*program, int* a, int* b, int* c){
    int pc = 0;
    string result = "";
    bool jump = false;
    int combo;
    while(pc < program->size()){
        int op_code = program->at(pc);
        switch(op_code){
            case 0:
                // Get next operator
                combo = get_combo(pc,program,a,b,c);
                *a = *a/(pow(2,combo));
                break;
            case 1:
                *b = *b^get_literal(pc,program);
                break;
            case 2:
                combo = get_combo(pc,program,a,b,c);
                *b = combo%8;
                break;
            case 3:
                if(*a != 0){
                    pc = get_literal(pc,program);
                    jump = true;
                }
                break;
            case 4:
                *b = *b^*c;
                break;
            case 5:
                result += to_string(get_combo(pc,program,a,b,c)%8) + ",";
                break;
            case 6:
                combo = get_combo(pc,program,a,b,c);
                *b = *a/(pow(2,combo));
                break;
            case 7:
                combo = get_combo(pc,program,a,b,c);
                *c = *a/(pow(2,combo));
                break;
        }
        if(!jump){
            pc += 2;
        }
        else{
            jump = false;
        }
        
    }
    result = result.substr(0,result.length()-1);
    return result;
}

void read_input(string file,vector<int>* program, int* reg_a, int* reg_b, int* reg_c){
    ifstream input_file;
    input_file.open(file);
    string line;
    getline(input_file,line);
    int colon = line.find(':');
    *reg_a = stoi(line.substr(colon + 2,line.length()-colon-1));
    getline(input_file,line);
    *reg_b = stoi(line.substr(colon + 2,line.length()-colon-1));
    getline(input_file,line);
    *reg_c = stoi(line.substr(colon + 2,line.length()-colon-1));
    getline(input_file,line);
    getline(input_file,line);
    colon = line.find(':');
    stringstream stre(line);
    string prog;
    stre >> prog;
    while(stre>>prog){
        program->push_back(stoi(prog));
    }
}

int main(){
    vector<int> simple_program;
    int reg_a,reg_b,reg_c;
    cout << "Example 1" << endl;
    read_input("simple.txt",&simple_program,&reg_a,&reg_b,&reg_c);
    
    if(run_program(&simple_program,&reg_a,&reg_b,&reg_c) != "4,6,3,5,6,3,5,2,1,0"){
        cout << "Broke Example 1";
        return 1;
    }

    vector<int> input_program;
    read_input("input.txt",&input_program,&reg_a,&reg_b,&reg_c);
    cout << run_program(&input_program,&reg_a,&reg_b,&reg_c) << endl;


    
}