#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main(){
    ifstream input_file;
    input_file.open("input.txt");
    string line;
    vector<int> list1;
    vector<int> list2;
    while(getline(input_file,line)){
        int first_num = stoi(line.substr(0,5));
        int second_num = stoi(line.substr(8,5));
        list1.push_back(first_num);
        list2.push_back(second_num);
    }
    sort(list1.begin(),list1.end());
    sort(list2.begin(),list2.end());
    int sum = 0;
    for(int i = 0; i < list1.size(); ++i){
        sum += abs(list1[i]-list2[i]);
    }
    cout << sum << endl;

}