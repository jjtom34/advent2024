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

struct box{
    int col;
    int row;
    char type;
};

bool recursive_move(vector<vector<char>> * map,int dir,int row, int col, vector<box> *movables){
    // Check if you can move the block
    // If you can return true;
    // Also keep track of every char visited
    vector<box> move = *movables;
    char curr = map->at(row)[col];
    switch(curr){
        case '.':
            return true;
            break;
        case '#':
            return false;
            break;
    }
    // Not empty so do the next two above

    if(curr == '['){
        box left = box{col,row,'['};
        movables->push_back(left);
        box right = box{col+1,row,']'};
        movables->push_back(right);
        return (recursive_move(map,dir,row+dir,col,movables) && recursive_move(map,dir,row+dir,col+1,movables));    
    }
    else{
        box left = box{col-1,row,'['};
        movables->push_back(left);
        box right = box{col,row,']'};
        movables->push_back(right);
        return (recursive_move(map,dir,row+dir,col,movables) && recursive_move(map,dir,row+dir,col-1,movables));
    }
}

void move_up(vector<vector<char>> * map, int *row, int *col){
    // Check Top space
    char top = map->at(*row-1)[*col];
    switch ((top))
    {
    case '.':
        // Empty space so just move
        map->at(*row)[*col] = '.';
        map->at(*row-1)[*col] = '@';
        *row = *row - 1;
        *col = *col;
        break;
    case '#':
        // Wall do nothing
        break;
    case ']':
    case '[':
    {
        // Start checking the chain of box/boxes
        int i = 0;
        bool empty = false;
        
        // Check if you can even move the box(es)
        vector<box> movables;
        if(recursive_move(map,-1,*row-1,*col,&movables)){
            // Can move everything so do that
            set<pair<int,int>> help;
            for(int i = movables.size()-1; i >=0; i--){
                // Move every box;
                if(help.find(make_pair(movables[i].row,movables[i].col)) == help.end()){
                    map->at(movables[i].row)[movables[i].col] = '.';
                    map->at(movables[i].row-1)[movables[i].col] = movables[i].type;
                    help.emplace(make_pair(movables[i].row,movables[i].col));
                }
            }
            map->at(*row)[*col] = '.';
            map->at(*row-1)[*col] = '@';
            *row = *row - 1;
            *col = *col;
        }
        break;
    }
        
    default:
        cout << "Something is messed up" << endl;
        break;
    }        
}

void move_right(vector<vector<char>> * map ,int *row, int *col){
    // Check right space
    char right = map->at(*row)[*col+1];
    switch ((right))
    {
    case '.':
        // Empty space so just move
        map->at(*row)[*col] = '.';
        map->at(*row)[*col+1] = '@';
        *row = *row;
        *col = *col+1;
        break;
    case '#':
        // Wall do nothing
        break;
    case ']':
    case '[':
    {
        // Start checking the chain of box/boxes
        int i = 0;
        bool empty = false;
        while(map->at(*row)[*col+1+i] != '.' && map->at(*row)[*col+1+i] != '#'){
            i += 1;
            if(map->at(*row)[*col+1+i] == '.'){
                empty = true;
            }
        }
        if(empty){
            // Space found at end of train, move robot up one and box to empty space;
            map->at(*row)[*col] = '.';
            map->at(*row)[*col+1] = '@';
            // Now also need to move every other box b/c uneven
            bool l_bracket = true;
            // Could also do this with a modified for loop but for clarity this is easier.
            for(int j = 1; j < i+1; j++){
                if(l_bracket){
                    map->at(*row)[*col+1+j] = '[';
                }
                else{
                    map->at(*row)[*col+1+j] = ']';
                }
                l_bracket = !l_bracket;
            }
            *row = *row;
            *col = *col+1;
        }
        break;
    }
        
    default:
        cout << "Something is messed up" << endl;
        break;
    }        
}
void move_down(vector<vector<char>> * map, int *row, int *col){
    // Check Top space
    char top = map->at(*row+1)[*col];
    switch ((top))
    {
    case '.':
        // Empty space so just move
        map->at(*row)[*col] = '.';
        map->at(*row+1)[*col] = '@';
        *row = *row + 1;
        *col = *col;
        break;
    case '#':
        // Wall do nothing
        break;
    case ']':
    case '[':
    {
        // Start checking the chain of box/boxes
        int i = 0;
        bool empty = false;
        
        // Check if you can even move the box(es)
        vector<box> movables;
        if(recursive_move(map,1,*row+1,*col,&movables)){
            // Can move everything so do that
            set<pair<int,int>> help;
            for(int i = movables.size()-1; i >=0; i--){
                // Move every box;
                if(help.find(make_pair(movables[i].row,movables[i].col)) == help.end()){
                    map->at(movables[i].row)[movables[i].col] = '.';
                    map->at(movables[i].row+1)[movables[i].col] = movables[i].type;
                    help.emplace(make_pair(movables[i].row,movables[i].col));
                }
            }
            map->at(*row)[*col] = '.';
            map->at(*row+1)[*col] = '@';
            *row = *row + 1;
            *col = *col;
        }
        break;
    }
        
    default:
        cout << "Something is messed up" << endl;
        break;
    }        
}

void move_left(vector<vector<char>> * map, int *row, int *col){
    // Check right space
    char left = map->at(*row)[*col-1];
    switch ((left))
    {
    case '.':
        // Empty space so just move
        map->at(*row)[*col] = '.';
        map->at(*row)[*col-1] = '@';
        *row = *row;
        *col = *col-1;
        break;
    case '#':
        // Wall do nothing
        break;
    case ']':
    case '[':{
        // Start checking the chain of box/boxes
        int i = 0;
        bool empty = false;
        while(map->at(*row)[*col-1-i] != '.' && map->at(*row)[*col-1-i] != '#'){
            i += 1;
            if(map->at(*row)[*col-1-i] == '.'){
                empty = true;
            }
        }
        if(empty){
            // Space found at end of train, move robot up one and box to empty space;
            map->at(*row)[*col] = '.';
            map->at(*row)[*col-1] = '@';
            // Now also need to move every other box b/c uneven
            bool r_bracket = true;
            // Could also do this with a modified for loop but for clarity this is easier.
            for(int j = 1; j < i+1; j++){
                if(r_bracket){
                    map->at(*row)[*col-1-j] = ']';
                }
                else{
                    map->at(*row)[*col-1-j] = '[';
                }
                r_bracket = !r_bracket;
            }
            *row = *row;
            *col = *col-1;
        }
        break;
    }
    default:
        cout << "Something is messed up" << endl;
        break;
    }        
}

void move(vector<vector<char>> * map,char dir,int *row, int *col){
    switch(dir){
        case('^'):
            // Check next space
            move_up(map,row,col);                    
            break;
        case('>'):
            move_right(map,row,col);
            break;
        case('v'):
            move_down(map,row,col);
            break;
        case('<'):
            move_left(map,row,col);
            break;
    }
    for(int i = 0; i < map->size(); ++i){
        for(int j = 0; j < map->at(i).size(); ++j){
            cout << map->at(i)[j];
            if(map->at(i)[j] =='['){
                if(map->at(i)[j+1] != ']'){
                    cout << "";
                }
            }
            else if(map->at(i)[j] == ']'){
                if(map->at(i)[j-1] != '['){
                    cout << "";
                }
            }
        }
        cout << endl;
    }

}

int main(){
    ifstream input_file;
    input_file.open("input.txt");
    string line;
    vector<vector<char>> map;
    int row;
    int col;
    getline(input_file,line);
    while ((line != ""))
    {
        vector<char> new_line;
        for (auto &&c : line)
        {
            switch(c){
                case 'O':
                    new_line.push_back('[');
                    new_line.push_back(']');
                    break;
                case '@':
                    new_line.push_back('@');
                    new_line.push_back('.');
                    break;
                default:
                    new_line.push_back(c);
                    new_line.push_back(c);
                    break;
            }
            
        }
        map.push_back(new_line);
        getline(input_file,line);
    }
    for(int i = 0; i < map.size(); ++i){
        for(int j = 0; j < map[i].size(); ++j){
            if(map[i][j] == '@'){
                row = i;
                col = j;
            }
            cout << map[i][j];
        }
        cout << endl;
    }
    // Read in inputs
    int count = 0;
    while(getline(input_file,line)){
        // Put movement here
        // Whenever you move, check if theres a wall or box
        // If wall do nothing
        // If box need to check for all subsequent tiles in that direction
        // If empty space you can move everything else do nothing
        // If empty space just move
        for(auto &&dir:line){
            // Shouldnt need a boundary check b/c wall is always outside.
            move(&map,dir,&row,&col);
            count += 1;
        }
    }
    long sum = 0;
    int diff = 0;
    // for (size_t i = 0; i < map.size(); i++)
    // {
    //     for (size_t j = 0; j < map[i].size(); j++)
    //     {

    //         if(map[i][j] == '['){
    //             //Top left quadrant
    //             if(i < map.size()/2 && j < map[i].size()/2){
    //                 diff = 100*i + j;
    //                 sum += 100*i + j;
    //             }
    //             // Bot left quandrant
    //             if(i >= map.size()/2 && j < map[i].size()/2){
    //                 diff = 100*(map.size()-i-1) + j;
    //                 sum += 100*(map.size()-i-1) + j;
    //             }
    //         }
    //         if(map[i][j] == ']'){
    //             //Top right quadrant
    //             if(i < map.size()/2 && j > map[i].size()/2){
    //                 diff = 100*i + ((map[i].size())-j-1);
    //                 sum += 100*i + ((map[i].size())-j-1);
    //             }
    //             // Bot right quandrant
    //             if(i >= map.size()/2 && j > map[i].size()/2){
    //                 diff = 100*(map.size()-i-1) + ((map[i].size())-j-1);
    //                 sum += 100*(map.size()-i-1) + ((map[i].size())-j-1);
    //             }
    //         }
    //         cout << map[i][j];
    //     }

    //     cout << endl;
        
    // }
    for (size_t i = 0; i < map.size(); i++)
    {
        for (size_t j = 0; j < map[i].size(); j++)
        {
            if(map[i][j] == '['){
                sum += 100*i + j;
            }
        }
    }
    cout << sum << endl;
}