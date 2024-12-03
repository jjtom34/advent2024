#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>


using namespace std;
// Now keep track of every mult and its location in a hashmap
// Find every good do section and add in everything in those sections
int main(){
    ifstream input_file;
    input_file.open("input.txt");
    string line;
    getline(input_file,line);
    int mul_pos = line.find("mul(");
    int sum = 0;
    unordered_map<int,int> pos_product;
    while(mul_pos != string::npos){
        //Check for the , and see if within 3 chars of the end of mul(
        int comma_pos = line.find(",",mul_pos);
        if((comma_pos > mul_pos + 4) && (comma_pos < mul_pos + 8)){
            // the "number" before is 1-3 digits;
            // Check if that section is an actual number;
            int num_size = comma_pos-(mul_pos + 4);
            string first_num= "";
            bool bad_num = false;
            for(int i = 0; i <num_size; ++i){
                if(isdigit(line[mul_pos+4+i])){
                    first_num += (line[mul_pos+4+i]);
                }
                else{
                    bad_num = true;
                    // Some part of the number is botched so go to next instance of mul()
                }
            }
            if(bad_num){
                cout <<"Bad first num" << endl;
                mul_pos = line.find("mul(",mul_pos+1);
                continue;
            }
            // All nums are good so turn it into an int
            int first_int = stoi(first_num);
            // Find the ending )
            int bracket_pos = line.find(")",comma_pos);
            if(bracket_pos > comma_pos + 1 && bracket_pos < comma_pos + 5){
                // Repeat the same int steps
                num_size = bracket_pos-(comma_pos+1);
                string second_num= "";
                bad_num = false;
                for(int i = 0; i < num_size; ++i){
                    if(isdigit(line[comma_pos+1+i])){
                        second_num += (line[comma_pos+1+i]);
                    }
                    else{
                        bad_num = true;
                        // Some part of the number is botched so go to next instance of mul()
                    }
                }
                if(bad_num){
                    mul_pos = line.find("mul(",mul_pos+1);
                    continue;
                }
                // Change good num to int
                int second_int = stoi(second_num);
                //Do the mult
                pos_product[mul_pos] = first_int * second_int;
                mul_pos = line.find("mul(",mul_pos+1);
                cout << "Doing mult " << first_int <<" * " << second_int << endl;
                
            }
            else{
                // Either the number is too big or the number doesn't exist
                // So just find the next line
                mul_pos = line.find("mul(",mul_pos+1);
                continue; 
            }
            

        }
        else{
            // Either the number is too big or the number doesn't exist
            // So just find the next line
            mul_pos = line.find("mul(",mul_pos+1);
            continue;
        }
        
        // Repeat until end of line
        
    }
    // Find all do sections
    // Start as a do
    int do_dont = true;
    int do_pos = 0;
    int dont_pos = 0;
    bool end = false;
    vector<pair<int,int>> ranges;
    while(do_pos != string::npos && dont_pos != string::npos){
        //Currently in do mode
        if(do_dont){
            // Look for the next don't
            dont_pos = line.find("don't()",do_pos);
            if(dont_pos == string::npos){
                break;
            }
            // Mark a full cycle
            ranges.push_back(make_pair(do_pos,dont_pos));
            do_dont = false;
        }
        else{// Currently in dont mode
            // Look for the next do
            do_pos = line.find("do()",dont_pos);
            do_dont = true;
        }
    }
    if(do_dont && do_pos != string::npos){
        // if ended on a do last dont is end of line.
        ranges.push_back(make_pair(do_pos,line.size()));
    }
    for(auto [first,second]:pos_product){
        for(auto [start,end]:ranges){
            if(first >= start && first < end){
                // Only add in numbers from between the ranges
                sum += second;
            }
        }
    }
    cout << sum << endl;
}