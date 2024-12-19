#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <sstream>
#include <deque>

using namespace std;

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

long long reverse(vector<int>*program, long long a, int curr_number){
    // Check 0 through 6 for b
    // Calculate everything
    // Only pass through those that match the given
    cout << curr_number << "|" << a<< endl;
    if(curr_number == -1){
        return a;
    }
    for(int i = 0; i < 8; ++i){
        long b = i; 
        long long temp_a = a;
        temp_a = (temp_a<<3) | b;
        b = b^3;
        long long c = temp_a/pow(2,b);
        b = b^5;
        b = b^c;
        b = b%8;
        if(b == program->at(curr_number)){
            // Recurse one step behind
            int res = reverse(program,temp_a,curr_number-1);
            if(res != -1){
                return res;
            }
        }
    }
    return -1;


}

int main(){
    vector<int> input_program;
    int i = 0;
    int a,b,c;
    read_input("input.txt",&input_program,&a,&b,&c);
    cout << reverse(&input_program,0,input_program.size()-1) << endl;




    
}
