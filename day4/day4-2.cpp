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
    // Start on a A and then check corners
    // Just need to make sure theres 2 Ms and 2 Ss and that the same letter is not in opposite corners
    for(int i = 0; i < space.size(); ++i){
        for(int j = 0; j < space[i].size(); ++j){
            if(space[i][j] == 'A' && i >=1 && (i <= space.size()-2) && j >=1 && (j <= space[i].size()-2)){
                char top_right = space[i-1][j+1];
                char top_left = space[i-1][j-1];
                char bot_right = space[i+1][j+1];
                char bot_left = space[i+1][j-1];
                if(top_right != 'M' && top_right != 'S'){
                    continue;
                }
                if(top_left != 'M' && top_left != 'S'){
                    continue;
                }
                if(bot_left != 'M' && bot_left != 'S'){
                    continue;
                }
                if(bot_right != 'M' && bot_right != 'S'){
                    continue;
                }
                if(top_right != bot_left && top_left != bot_right){
                    sum+=1;
                }
            }
        }
    }
    cout << sum << endl;
}