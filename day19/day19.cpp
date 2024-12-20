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

void read_input(string file,vector<string>*towels,vector<string>* patterns){
    ifstream input_file;
    input_file.open(file);
    string line;
    getline(input_file,line);
    int prev = 0;
    int next = line.find(",",prev);
    towels->push_back(line.substr(prev,next-prev));
    prev = next;
    next = line.find(",",prev+1);
    while(next != -1){
        towels->push_back(line.substr(prev+2,next-prev-2));
        prev = next;
        next = line.find(",",prev+1);
    }
    towels->push_back(line.substr(prev+2,next-prev-1));
    getline(input_file,line);
    while(getline(input_file,line)){
        patterns->push_back(line);
    }
}
// Recursively build the pattern
bool can_make(vector<string>* towels,unordered_map<string,bool> * memo,string pattern, int max_size){
    if(memo->find(pattern) != memo->end()){
        return memo->at(pattern);
    }
    if(pattern == ""){
        return true;
    }
    if(pattern.length() == 1){
        if(memo->find(pattern) == memo->end()){
            memo->emplace(pattern,false);
            return false;
        }
    }
    bool makeable = false;
    for(int i = 1; i <max_size+1;++i){
        if(find(towels->begin(),towels->end(),pattern.substr(0,i)) != towels->end()){
            if(can_make(towels,memo,pattern.substr(i),max_size)){
                memo->emplace(pattern.substr(i),true);
                makeable = true;
                break;
            }
            else{
                memo->emplace(pattern.substr(i),false);
            }
        }        
    }
    return makeable;
}
int find_patterns(vector<string>*towels,vector<string>* patterns){
    int sum = 0;
    unordered_map<string,bool> memo;
    int max_size = 0;
    for(auto towel:*towels){
        memo[towel] = true;
        if(towel.length() > max_size){
            max_size = towel.length();
        }
    }
    for(auto pattern:*patterns){
        cout << pattern << endl;
        if(can_make(towels,&memo,pattern,max_size)){
            sum += 1;
        }
    }
    return sum;
}
int main(){
    vector<string> simple_towels;
    vector<string> simple_patterns;
    read_input("simple.txt",&simple_towels,&simple_patterns);
    int simple = find_patterns(&simple_towels,&simple_patterns);
    if(simple != 6){
        cout <<"Incorrect amount: " << simple << endl;
        return -1;
    }
    vector<string> towels;
    vector<string> patterns;
    read_input("input.txt",&towels,&patterns);
    cout << find_patterns(&towels,&patterns) << endl;
}