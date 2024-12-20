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
long can_make(vector<string>* towels,unordered_map<string,long> * memo,string pattern){
    if(memo->find(pattern) != memo->end()){
        return memo->at(pattern);
    }
    if(pattern == ""){
        return 1;
    }
    if(pattern.length() == 1){
        if(find(towels->begin(),towels->end(),pattern) == towels->end()){
            if(memo->find(pattern) == memo->end()){
                memo->emplace(pattern,0);
                return 0;
            }
        }
        
    }
    long sum = 0;
    for(int i = 0; i <pattern.size();++i){
        if(find(towels->begin(),towels->end(),pattern.substr(0,i+1)) != towels->end()){
            long temp = can_make(towels,memo,pattern.substr(i+1));
            memo->emplace(pattern.substr(i+1),temp);
            sum += temp;
        }
    }
    return sum;
}
long long find_patterns(vector<string>*towels,vector<string>* patterns){
    long long sum = 0;
    unordered_map<string,long> memo;
    int max_size = 0;
    for(auto towel:*towels){
        memo[towel] = can_make(towels,&memo,towel);
    }
    for(auto pattern:*patterns){
        cout << pattern << endl;
        long long ways = can_make(towels,&memo,pattern);
        sum += ways;
    }
    return sum;
}
int main(){
    vector<string> simple_towels;
    vector<string> simple_patterns;
    read_input("simple.txt",&simple_towels,&simple_patterns);
    int simple = find_patterns(&simple_towels,&simple_patterns);
    if(simple != 16){
        cout <<"Incorrect amount: " << simple << endl;
        return -1;
    }
    vector<string> towels;
    vector<string> patterns;
    read_input("input.txt",&towels,&patterns);
    cout << find_patterns(&towels,&patterns) << endl;
}