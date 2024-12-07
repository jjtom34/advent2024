#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <deque>
#include <sstream>

using namespace std;



bool recursive_calc(deque<long>* nums, long current, long target){
    deque<long> copy = (*nums);
    long next_num = copy.front();
    copy.pop_front();
    // For concat 
    stringstream stream;
    stream << next_num;
    stringstream stream2;
    stream2 << current;
    long concat = stol(stream2.str()+stream.str());
    if(copy.size() == 0){
        if(current + copy.back() == target || current * copy.back() == target || concat == target){
            return true;
        }
        return false;
    }
    return(recursive_calc(&copy,current*next_num,target)||recursive_calc(&copy,current+next_num,target)||recursive_calc(&copy,concat,target));
}

int main(){
    ifstream input_file;
    input_file.open("input.txt");
    string line;
    int colon_pos;
    unsigned long sum = 0;
    while(getline(input_file,line)){
        colon_pos = line.find(":");
        long result = stol(line.substr(0,colon_pos));
        deque<long> nums;
        int num_pos = colon_pos+2;
        int next_space = line.find(" ",num_pos);
        while(next_space != -1){
            nums.push_back(stoi(line.substr(num_pos,next_space-num_pos)));
            num_pos = line.find(" ",num_pos) + 1;
            next_space = line.find(" ",num_pos);
        }
        nums.push_back(stoi(line.substr(num_pos,line.length()-num_pos)));
        // Start testing out numbers
        // Default plus and then cycle through every possiblecombination
        // 2^n calculations per line
        int first_num = nums.front();
        nums.pop_front();
        cout << result << endl;
        if(recursive_calc(&nums,first_num,result)){
            sum += result;
        }
    }
    cout << sum << endl;
}