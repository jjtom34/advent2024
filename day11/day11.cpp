#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <deque>
#include <sstream>
#include <unordered_map>
#include <cmath>
using namespace std;


// Map of number to vector of blinks
// basically calculate the next 25 blinks of every number and access every time you iterate.
// If you ever hit like 7 with x blinks remaining it should be fast.
// 1-9 should always be relevant b/c any time you hit a power of 2 you go down to those.

long sim_25(unordered_map<string,long>*table,long long num,int step){
    //Check if done
    cout << "Num: " << num << " Step: " << step << endl;
    string key = to_string(num) + "|" + to_string(step);
    if(step == 0){
        table->emplace(key,1);
        return 1;
    }
    //Check for memoed
    
    if(table->find(key) != table->end()){
        return table->at(key);
    }
    string string_num = to_string(num);
    if(num == 0){
        table->emplace(key,sim_25(table,1,step-1));
    }
    else if(string_num.size()%2 == 0){
        table->emplace(key,sim_25(table,stol(string_num.substr(0,string_num.size()/2)),step-1) + sim_25(table,stol(string_num.substr(string_num.size()/2,string_num.size()/2)),step-1));
    }
    else{
        table->emplace(key,sim_25(table,num*2024,step-1));    
    }
    return table->at(key);
}

long sim(vector<long>* stones){
    unordered_map<string,long> table;
    long long sum = 0;
    for(int i = 0; i < stones->size();++i){
        string key = to_string(stones->at(i)) + "|" + "75";
        if((table.find(key)) != table.end()){
            sum += table[key];
        }
        else{
            // get the sum;
            sum += sim_25(&table,stones->at(i),75);
        }
    }
    return sum;
}

int main(){
    ifstream input_file;
    input_file.open("input.txt");
    string line;
    getline(input_file,line);
    vector<long> stones;
    // Split into seperate numbers
    stringstream thing(line);
    string stone;
    while(thing >> stone){
        stones.push_back(stol(stone));
    }
    
    cout << sim(&stones) << endl;
}