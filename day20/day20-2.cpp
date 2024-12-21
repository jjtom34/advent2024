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
  Now need to check every spot within 20
  // Just for loop through the entire section 20 to the left/right/top/down but also check if the spot is reachable in 20;
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
    int left_bound = std::max(col-20,0);
    int right_bound = std::min(col+20,int(this->width-1));
    int top_bound = std::max(row-20,0);
    int bot_bound = std::min(row+20,int(this->length-1));
    for(int i = top_bound; i <= bot_bound; ++i){
        for(int j = left_bound; j <=right_bound; ++j){
            int distance = abs(row-i)+abs(col-j);
            if(distance <= 20 && this->map[get_coord(i,j)] != '#'){
                for(int k = 0; k < this->route.size();++k){
                    if(this->route[k].first == i && this->route[k].second == j){
                        int time = curr + (this->route.size()-1-k);
                        if(time < this->route.size()){
                            if(this->cheats.find(time+distance) == this->cheats.end()){
                                this->cheats[(time+distance)] = 1;
                            }
                            else{
                                this->cheats[(time+distance)] += 1;
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
        std::cout << i << std::endl;
        check_space(i);
    }
    for(auto [cheat,num]:this->cheats){    
        if(this->route.size()-1-cheat >= 100){
            fast_routes += num;
            std::cout << this->route.size()-1-cheat << "|" << num << std::endl;
        }
        
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