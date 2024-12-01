#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

int main(){
    ifstream input_file;
    input_file.open("input.txt");
    string line;
    vector<int> list1;
    vector<int> list2;
    unordered_map<int,int> count;
    while(getline(input_file,line)){
        int first_num = stoi(line.substr(0,5));
        int second_num = stoi(line.substr(8,5));
        list1.push_back(first_num);
        if(count.find(second_num) != count.end()){
            count[second_num] += 1;
        }
        else{
            count[second_num] = 1;
        }
    }
    int sum = 0;
    for(int i = 0; i < list1.size(); ++i){
        if(count.find(list1[i]) != count.end()){
            sum += list1[i]*count[list1[i]];
        }
    }
    cout << sum << endl;

}