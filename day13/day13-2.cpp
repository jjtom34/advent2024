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

/*
ax + by = c
dx + ey = f

x = (c-by)/a

d(c-by)/a + ey = f

dc/a - dby/a + ey = f
f-(dc/a) = ey - dby/a
f-(dc/a) = y(e-db/a)
f-(dc/a) / (e-db/a)
// Take out the A for floating point precision
(fa-dc)/a / (ea-db)/a
// As cancel out
(fa-dc)/ea-db
*/
int main(){
    ifstream input_file;
    input_file.open("input.txt");
    string line;
    int line_type = 0;
    int a;
    int b;
    long c;
    int d;
    int e;
    long f;
    long sum = 0;
    int first_plus;
    int comma;
    int second_plus;
    int first_eq;
    int second_eq;
    while(getline(input_file,line)){
        switch(line_type){
            case 0:
                // First Button
                first_plus = line.find("+")+1;
                comma = line.find(",");
                second_plus = line.find("+",first_plus+1)+1;
                a = stoi(line.substr(first_plus,comma-first_plus));
                d = stoi(line.substr(second_plus,line.size()-second_plus));
                line_type += 1;
                break;
            case 1:
                first_plus = line.find("+")+1;
                comma = line.find(",");
                second_plus = line.find("+",first_plus+1)+1;
                b = stoi(line.substr(first_plus,comma-first_plus));
                e = stoi(line.substr(second_plus,line.size()-second_plus));
                // Second Button
                line_type +=1;
                break;
            case 2:
                // Target Nums
                first_eq = line.find("=")+1;
                comma = line.find(",");
                second_eq = line.find("=",first_eq+1)+1;
                c = 10000000000000+(stoi(line.substr(first_eq,comma-first_eq)));
                f = 10000000000000+(stoi(line.substr(second_eq,line.size()-second_eq)));
                line_type +=1;
                break;
            case 3:
                //Just an Empty line so might as well solve here
                long temp = (f*a-(d*c));
                long temp2 = (e*a-(d*b));
                if(temp%temp2 == 0){
                    long y = temp/temp2;
                    if((c-(b*y))%a == 0){
                        long x = (c-(b*y))/a;
                        if(x >= 0 && y >= 0){
                            sum += 3*x + y;
                        }
                    }
                }
                line_type = 0;
                break;                
        }
    }
    cout << sum << endl;
}