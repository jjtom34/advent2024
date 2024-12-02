#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    // Safe if all increasing or all decreasing
    // AND
    // Increases or decreases are less than 2
    ifstream input_file;
    input_file.open("input.txt");
    string line;
    int safe_levels = 0;
    while(getline(input_file,line)){

        stringstream ss(line);
        string level;
        // Get first number
        int change = 0;
        ss >> level;
        int prev = stoi(level);
        cout << prev;
        bool safe = true;
        while(ss >> level){
            // Get current level
            // Change to int
            int level_num = stoi(level);
            // Check if its increasing or decreasing
            int diff = level_num - prev;
            cout << level_num;
            if(change == 0){
                if(diff > 0){
                    change = 1;
                }
                else if (diff < 0){
                    change = -1;
                }
            } else{
                switch(change){
                    case 1:
                        if(diff < 0){
                            safe = false;
                            goto endloop;
                        }
                        break;
                    case -1:
                        if(diff > 0){
                            safe = false;
                            goto endloop;
                        }
                        break;
                }
            }
            // Check if its within 2
            if(abs(diff) > 3 || abs(diff) < 1){
                safe = false;
                goto endloop;
            }
            prev = level_num;
        }
        // At end of loop increment safe levels if all good.
        if(safe){
            safe_levels += 1;
            cout << "totally safe";
        }
        endloop:
        cout << endl;
        
    }
    cout<< safe_levels << endl;
}