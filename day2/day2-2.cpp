#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Now allowed 1 removed level;
// So keep track on if you used the removal yet.
// If you do use it just skip the update step;
int main(){
    // Safe if all increasing or all decreasing
    // AND
    // Increases or decreases are less than 2
    ifstream input_file;
    input_file.open("input.txt");
    string line;
    int safe_levels = 0;
    while(getline(input_file,line)){
        cout << line <<" ";
        stringstream ss(line);
        string level;
        // Get first number
        int change = 0;
        vector<int> levels;
        while(ss >> level){
            levels.push_back(stoi(level));
        }
        for(int i = 0; i < levels.size(); ++i){
            // Just do it everytime except take one out every time
            int direction = 0;
            int prev = -1;
            int diff = 0;
            bool safe = true;
            for(int j = 0; j < levels.size(); ++j){
                if(j != i){
                    diff = levels[j]-prev;
                    if(direction == 0){
                        if(prev != -1){

                            if(diff > 0){
                                direction = 1;
                            }
                            else if (diff < 0){
                                direction = -1;
                            }
                        }
                    }
                    else{
                        switch (direction){
                            case 1:
                                if(diff < 0){
                                    safe = false;
                                }
                                break;
                            case -1:
                                if(diff > 0){
                                    safe = false;
                                }
                                break;
                        }
                    }
                    if(prev != -1 && (abs(diff) > 3 || abs(diff) < 1)){
                        safe = false;
                    }
                    prev = levels[j];
                }                
            }
            if(safe){
                safe_levels += 1;
                cout << "Pretty Good" << endl;
                break;
            }
        }
    }
    cout << safe_levels << endl;
}