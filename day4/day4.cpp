#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>


using namespace std;

int main(){
    ifstream input_file;
    input_file.open("input.txt");
    string line;
    vector<vector<char>> space;
    int sum = 0;
    while(getline(input_file,line)){
        vector<char> newline;
        for(auto s:line){
            newline.push_back((s));
        }
        space.push_back(newline);
    }
    // Just start on an x and just check every adjacent square.
    for(int i = 0; i < space.size(); ++i){
        for(int j = 0; j < space[i].size(); ++j){
            if(space[i][j] == 'X'){
                // Good ol numpad notation
                //1
                if(i <= space.size()-4 && j >= 3){
                    if(space[i+1][j-1] == 'M'){
                        if(space[i+2][j-2] == 'A'){
                            if(space[i+3][j-3] == 'S'){
                                sum+= 1;
                            }
                        }
                    }
                }
                //2
                if(i <= space.size()-4){
                    if(space[i+1][j] == 'M'){
                        if(space[i+2][j] == 'A'){
                            if(space[i+3][j] == 'S'){
                                sum+= 1;
                            }
                        }
                    }
                }
                //3
                if(i <= space.size()-4 && j <= space[i].size()-4){
                    if(space[i+1][j+1] == 'M'){
                        if(space[i+2][j+2] == 'A'){
                            if(space[i+3][j+3] == 'S'){
                                sum+= 1;
                            }
                        }
                    }
                }
                //4
                if(j >= 3){
                    if(space[i][j-1] == 'M'){
                        if(space[i][j-2] == 'A'){
                            if(space[i][j-3] == 'S'){
                                sum+= 1;
                            }
                        }
                    }
                }
                //5
                // Neutral Baby
                //6
                if(j <= space[i].size()-4){
                    if(space[i][j+1] == 'M'){
                        if(space[i][j+2] == 'A'){
                            if(space[i][j+3] == 'S'){
                                sum+= 1;
                            }
                        }
                    }
                }
                //7
                if(i >= 3 && j >= 3){
                    if(space[i-1][j-1] == 'M'){
                        if(space[i-2][j-2] == 'A'){
                            if(space[i-3][j-3] == 'S'){
                                sum+= 1;
                            }
                        }
                    }
                }
                //8
                if(i >= 3){
                    if(space[i-1][j] == 'M'){
                        if(space[i-2][j] == 'A'){
                            if(space[i-3][j] == 'S'){
                                sum+= 1;
                            }
                        }
                    }
                }
                //9
                if(i >= 3 && j <= space[i].size()-4){
                    if(space[i-1][j+1] == 'M'){
                        if(space[i-2][j+2] == 'A'){
                            if(space[i-3][j+3] == 'S'){
                                sum+= 1;
                            }
                        }
                    }
                }
            }
        }
    }
    cout << sum << endl;
}