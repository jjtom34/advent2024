#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;


// Every time you hit a number segment just check for the first available space that fits it
// Can't do deque now b/c  after you move the numbers theres no guarantee to what the empty spaces are now
// i.e 1.2.3 becomes 1...3 vs 123 to 1.3
int main(){
    ifstream input_file;
    input_file.open("input.txt");
    string line;
    //Create the big string???/Vector??
    vector<long> big_man;
    getline(input_file,line);
    long num = 0;
    bool is_period = false;
    long long sum = 0;
    set<int> moved;
    for(auto c:line){
        int line_num = c - '0';
        for(int i = 0; i <line_num; ++i){\
            if(is_period){
                big_man.push_back(-1);
            }
            else{
                big_man.push_back(num);
            }
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
    long current = big_man[big_man.size()-1];
    int size = 0;
    for(int i = big_man.size()-1; i >=0; i-= 1){
        if(big_man[i] != current){
            if(current == -1){
                current = big_man[i];
            }
            else{
                cout << current << size << endl;
                if(moved.find(current) != moved.end()){
                    cout << "Skipping already done" << endl;
                }
                else{
                    //Look for the first available space
                    bool space_found = false;
                    int space_size = 0;
                    bool checking_size = false;
                    int space_ind = 0;
                    for(int j = 0; j <= i; ++j){
                        if(big_man[j] == -1){
                            if(!checking_size){
                                checking_size = true;
                                space_ind = j;
                            }
                        }
                        if(big_man[j] != -1 && checking_size){
                            if(j-space_ind >= size){
                                space_found = true;
                                break;
                            }
                            // Bad space reset everything
                            space_size = 0;
                            checking_size = false;
                        }
                    }
                    if(checking_size >= size){
                        space_found = true;
                    }
                    // If you found a space start replacing
                    if(space_found){
                        for(int j = 0; j < size; ++j){
                            big_man[space_ind+j] = current;
                            big_man[i+1+j] = -1;
                        }
                        
                    }
                    moved.emplace(current);
                }
                current = big_man[i];
            }
            size = 1;
        }
        else{
            size += 1;
        }
        // for(auto c:big_man){
        //     cout << c << " ";
        // }
        // cout << endl;
    }
    for(auto c:big_man){
        if(c == -1){
            cout<< ".";
        }
        else{
            cout << c;
        }
        
    }
    cout << endl;
    for(int i = 0; i < big_man.size(); ++i){
        if(big_man[i] != -1){
            sum += i * (big_man[i]);
        }
    }
    cout << sum << endl;
}
//0....1.222
//0222.1....