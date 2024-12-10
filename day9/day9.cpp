#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

int main(){
    ifstream input_file;
    input_file.open("simple2.txt");
    string line;
    //Create the big string???/Vector??
    vector<int> big_man;
    getline(input_file,line);
    char current = line[0];
    int num = 0;
    bool is_period = false;
    long long sum = 0;
    deque<int> empty_spots;
    int index = 0;
    for(auto c:line){
        int line_num = c - '0';
        for(int i = 0; i <line_num; ++i){
            if(is_period){
                big_man.push_back(-1);
                empty_spots.push_back(index);
            }
            else{
                big_man.push_back(num);
            }
            index += 1;
        }
        if(is_period){
            is_period = false;
        }
        else{
            is_period = true;
            num +=1;
        }
        
    }
    for(auto c:big_man){
        cout << c;
    }
    cout << endl;
    while(big_man.back() == -1){
        big_man.pop_back();
    }
    while(!empty_spots.empty()){
        int empty = empty_spots.front();
        empty_spots.pop_front();
        int last = big_man.back();
        big_man[empty] = last;
        big_man.pop_back();
        while(big_man.back() == -1){
            big_man.pop_back();
            empty_spots.pop_back();
        }
        // for(auto c:big_man){
        //     cout << c << " ";
        // }
        // cout << endl;
    }
    for(int i = 0; i < big_man.size(); ++i){
        sum += i * (big_man[i]);
    }
    cout << sum << endl;
}