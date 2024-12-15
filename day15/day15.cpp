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

void move_up(vector<vector<char>> * map,char dir,int *row, int *col){
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
    case 'O':
    {
        // Start checking the chain of box/boxes
        int i = 0;
        bool empty = false;
        while(map->at(*row-1-i)[*col] != '.' && map->at(*row-1-i)[*col] != '#'){
            i += 1;
            if(map->at(*row-1-i)[*col] == '.'){
                empty = true;
            }
        }
        if(empty){
            // Space found at end of train, move robot up one and box to empty space;
            map->at(*row)[*col] = '.';
            map->at(*row-1)[*col] = '@';
            map->at(*row-1-i)[*col] = 'O';
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

void move_right(vector<vector<char>> * map,char dir,int *row, int *col){
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
    case 'O':
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
            map->at(*row)[*col+1+i] = 'O';
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
void move_down(vector<vector<char>> * map,char dir,int *row, int *col){
    // Check right space
    char down = map->at(*row+1)[*col];
    switch ((down))
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
    case 'O':
    {
        // Start checking the chain of box/boxes
        int i = 0;
        bool empty = false;
        while(map->at(*row+i+1)[*col] != '.' && map->at(*row+i+1)[*col] != '#'){
            i += 1;
            if(map->at(*row+i+1)[*col] == '.'){
                empty = true;
            }
        }
        if(empty){
            // Space found at end of train, move robot up one and box to empty space;
            map->at(*row)[*col] = '.';
            map->at(*row+1)[*col] = '@';
            map->at(*row+1+i)[*col] = 'O';
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

void move_left(vector<vector<char>> * map,char dir,int *row, int *col){
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
    case 'O':{
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
            map->at(*row)[*col-1-i] = 'O';
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
            move_up(map,dir,row,col);                    
            break;
        case('>'):
            move_right(map,dir,row,col);
            break;
        case('v'):
            move_down(map,dir,row,col);
            break;
        case('<'):
            move_left(map,dir,row,col);
            break;
    }
    // for (auto &&i : *map)
    // {
    //     for (auto &&c : i)
    //     {
    //         cout << c;
    //     }
    //     cout << endl;
    // }
    
}

int main(){
    ifstream input_file;
    input_file.open("input.txt");
    string line;
    vector<vector<char>> map;
    int row;
    int col;
    int i = 0;
    int j = 0;
    getline(input_file,line);
    while ((line != ""))
    {
        vector<char> new_line;
        j = 0;
        for (auto &&c : line)
        {
            if(c =='@'){
                col = j;
                row = i;
            }
            j += 1;
            new_line.push_back(c);
        }
        i += 1;
        map.push_back(new_line);
        getline(input_file,line);
    }
    // Read in inputs
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
        }
    }
    long sum = 0;
    for (size_t i = 0; i < map.size(); i++)
    {
        for (size_t j = 0; j < map[i].size(); j++)
        {
            if(map[i][j] == 'O'){
                sum += 100*i + j;
            }
            
        }
        
    }
    cout << sum << endl;
}