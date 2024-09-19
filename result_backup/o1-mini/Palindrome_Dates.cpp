#include <iostream>
#include <string>

using namespace std;

bool is_leap_year(int y){
    if(y % 400 == 0) return true;
    if(y % 100 == 0) return false;
    if(y % 4 == 0) return true;
    return false;
}

int main(){
    string s1, s2;
    cin >> s1 >> s2;
    long long date1 = 0, date2 = 0;
    for(char c: s1) date1 = date1 *10 + (c - '0');
    for(char c: s2) date2 = date2 *10 + (c - '0');
    int count =0;
    for(int y=1000; y<=9999; y++){
        int y1 = y / 1000;
        int y2 = (y / 100) %10;
        int y3 = (y /10) %10;
        int y4 = y %10;
        int mm = y4 *10 + y3;
        int dd = y2 *10 + y1;
        if(mm >=1 && mm <=12){
            int dim =0;
            switch(mm){
                case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                    dim =31;
                    break;
                case 4: case 6: case 9: case 11:
                    dim =30;
                    break;
                case 2:
                    if(is_leap_year(y)) dim=29;
                    else dim=28;
                    break;
            }
            if(dd >=1 && dd <= dim){
                long long date = (long long)y *10000 + mm *100 + dd;
                if(date >= date1 && date <= date2){
                    count++;
                }
            }
        }
    }
    cout << count;
}