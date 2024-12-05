#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <algorithm>


using namespace std;


//Hashmap of page to depencies
//Seperate map of if a page has been updated yet
// When checking rules, check for dependeces and then if that dependency is written yet.

//Start from end
// Evertime you get a page, enable every thing its dependent on
// and check if it breaks any dependencies

//Keep a list of bad nums
// AKA nums that cant be before this one

// To fix the misordering just move the offending number right one and repeat again.
int main(){
    ifstream input_file;
    input_file.open("input.txt");
    string line;
    vector<int> updates;
    int sum = 0;
    unordered_map<int,vector<int>> rules;
    // Get in rules
    // Luckily all 2 digit numbers
    getline(input_file,line);
    while(line != ""){
        int first_num = stoi(line.substr(0,2));
        int second_num = stoi(line.substr(3,2));
        if(rules.find(first_num) != rules.end()){
            rules[first_num].push_back(second_num);
        }
        else{
            vector<int> new_rule = {second_num};
            rules[first_num] = new_rule;
        }
        getline(input_file,line);
    }
    //Check updates;
    while(getline(input_file,line)){
        vector<int> nums;
        // Parse string
        int pos = 0;
        int page;
        while(pos < line.length()){
            int page = stoi(line.substr(pos,2));
            nums.push_back(page);
            pos +=3;
        }
        bool checked = false;
        while_start:
        while(!checked){
            vector<int> bad_nums;
            for(int i = nums.size()-1; i >= 0; i -=1){
                if(find(bad_nums.begin(),bad_nums.end(),nums[i]) != bad_nums.end()){
                    // Number should be later swap it to the left.
                    swap(nums[i],nums[i+1]);
                    goto while_start;
                }
                if(rules.find(nums[i]) != rules.end()){
                    for(auto num:rules[nums[i]]){
                        bad_nums.push_back(num);
                    }
                }

            }
            checked = true;
        }
        for(auto num:nums){
            cout << num << ",";
        }
        cout << endl;
        //Get middle number
        int middle_num = nums[floor(nums.size()/2)];
        // Add to sum
        sum += middle_num;
    }
    cout << sum << endl;
}