#include <iostream>
using namespace std;

int main(){
    int max_excess = 0;
    int day_of_max = 0;
    for(int day=1; day<=7; day++){
        int school, classes;
        cin >> school >> classes;
        int total = school + classes;
        if(total > 8){
            int excess = total - 8;
            if(excess > max_excess){
                max_excess = excess;
                day_of_max = day;
            }
        }
    }
    if(max_excess == 0){
        cout << "0";
    }
    else{
        cout << day_of_max;
    }
}