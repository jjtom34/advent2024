#include <iostream>
#include <fstream>
using namespace std;
int main(){
    ifstream input_file;
    input_file.open("input.txt");
    string line;
    getline(input_file,line);
    int mul_pos = line.find("mul(");
    int sum = 0;
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
                sum += first_int * second_int;
                mul_pos = line.find("mul(",mul_pos+1);
                cout << "Doing mult " << first_int <<" * " << second_int << endl;
                continue; 
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
    cout << sum << endl;
}