#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <sstream>
#include <deque>
#include <set>

/*
Read input
Find path and get fastest time
    Keep vector of coordinates so you know
On that path check every Spot you can cheat
  Check Every spot 2 (or more for part 2??) places away from you and see if you can Reach it
  If you can move there and check the vector of coordinates for remaining time

  // Check bounds then if you are actually skipping a wall
  // Check bounds and then corner
  // // For corners both adjacent would have to be walls and the corner empty
*/

class cheat_finder{
    private:
        std::pair<int,int> start;
        std::pair<int,int> end;
        std::vector<char> map;
        std::vector<std::pair<int,int>> route;
        std::unordered_map<int,int> cheats;
        int length;
        int width;
        void find_route();
        int get_coord(int row, int col);
        void check_space(int curr);
    public:
        void read_map(std::string file);
        int cheat_turbo();
};
int cheat_finder::get_coord(int row, int col){
    return this->width*row + col;
}
void cheat_finder::check_space(int curr){
    int row = this->route[curr].first;
    int col = this->route[curr].second;
    // Check cardinals
    std::pair<int,int> directions[4] = {std::make_pair(-1,0),std::make_pair(0,1),std::make_pair(1,0),std::make_pair(0,-1)};
    for(auto dir:directions){
        // Check bounds
        // Need to check 2 spaces away for cardinals
        int new_row = row + 2*dir.first;
        int new_col = col + 2*dir.second;
        if(new_row >= 0 && new_col >= 0 && new_row < this->length && new_col < this->width){
            if(this->map[get_coord(row+dir.first,col+dir.second)] == '#' && this->map[get_coord(new_row,new_col) == '.']){
                // Valid Cheat so check
                for(int i = 0; i < this->route.size();++i){
                    if(this->route[i].first == new_row && this->route[i].second == new_col){
                        if(curr + (this->route.size()-1-i) < this->route.size()){
                            if(this->cheats.find(curr + (this->route.size()-1-i)+2) == this->cheats.end()){
                                this->cheats[(curr + (this->route.size()-1-i)+2)] = 1;
                            }
                            else{
                                this->cheats[(curr + (this->route.size()-1-i)+2)] += 1;
                            }
                        }
                    }
                }
            }
        }
    }
    //Check Corners
    std::pair<int,int> intercards[4] = {std::make_pair(-1,-1),std::make_pair(1,1),std::make_pair(1,-1),std::make_pair(-1,1)};
    for(auto inter:intercards){
        int new_row = row + inter.first;
        int new_col = col + inter.second;
        if(new_row >= 0 && new_col >= 0 && new_row < this->length && new_col < this->width){
            if(this->map[get_coord(new_row,new_col)] == '.' && this->map[get_coord(row,new_col)] == '#' && this->map[get_coord(row,new_col)] == '#'){
                for(int i = 0; i < this->route.size();++i){
                    if(this->route[i].first == new_row && this->route[i].second == new_col){
                        if(curr + (this->route.size()-1-i) < this->route.size()){
                            if(this->cheats.find(curr + (this->route.size()-1-i)+2) == this->cheats.end()){
                                this->cheats[(curr + (this->route.size()-1-i))+2] = 1;
                            }
                            else{
                                this->cheats[(curr + (this->route.size()-1-i))+2] += 1;
                            }
                        }
                    }
                }
            }
        }
    }
};
int cheat_finder::cheat_turbo(){
    int fast_routes = 0;
    this->find_route();
    int time = 0;
    for(int i = 0; i < this->route.size();++i){
        // Check space around current location;
        check_space(i);
    }
    for(auto [cheat,num]:this->cheats){    
        if(this->route.size()-1-cheat >= 100){fast_routes += num;}
        std::cout << this->route.size()-1-cheat << "|" << num << std::endl;
    }
    return fast_routes;
}

void cheat_finder::find_route(){
    int row,col;
    row = this->start.first;
    col = this->start.second;
    
    while(this->map[get_coord(row,col)] != 'E'){
        std::pair<int,int> directions[4] = {std::make_pair(-1,0),std::make_pair(0,1),std::make_pair(1,0),std::make_pair(0,-1)};
        for(auto dir:directions){
            int new_row = row + dir.first;
            int new_col = col + dir.second;
            if(this->map[get_coord(new_row,new_col)] != '#' && (this->route.empty() || this->route.back() != std::make_pair(new_row,new_col))){
                this->route.push_back(std::make_pair(row,col));
                row = new_row;
                col = new_col;
                break;
            }
        }
    }
    this->route.push_back(std::make_pair(row,col));
}

void cheat_finder::read_map(std::string file){
    std::ifstream input;
    input.open(file);
    std::string line;
    int length = 0;
    int width;
    while(getline(input,line)){
        width = 0;
        for(auto c:line){
            if(c == 'S'){
                this->start.first = length;
                this->start.second = width;
            }
            if(c == 'E'){
                this->end.first = length;
                this->end.second = width;
            }
            this->map.push_back(c);
            width += 1;
        }
        length+=1;
    }
    this->length = length;
    this->width = width;
}



int main(){
    std::vector<char> simple_map;
    std::pair<int,int> simple_start;
    std::pair<int,int> simple_end;
    cheat_finder simple = cheat_finder(); 
    simple.read_map("simple.txt");
    simple.cheat_turbo();

    std::vector<char> smap;
    std::pair<int,int> start;
    std::pair<int,int> end;
    cheat_finder input = cheat_finder(); 
    input.read_map("input.txt");
    std::cout << input.cheat_turbo() << std::endl;
}