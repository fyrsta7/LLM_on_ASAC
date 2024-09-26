#include <iostream>
using namespace std;

int main() {
    int time[7][2];
    
    // Input times 
    for(int i = 0; i < 7; i++) {
        cin >> time[i][0] >> time[i][1];
    }

    bool atLeastOneUnhappy = false;
    int max_time_sum = 0;
    int max_time_index = -1;

    for(int i = 0; i < 7; i++) {
        int time_sum = time[i][0] + time[i][1];
        
        if(time_sum > 8) {
            atLeastOneUnhappy = true;
        }
        
        if(time_sum > max_time_sum) {
            max_time_sum = time_sum;
            max_time_index = i + 1; // 1-based indexing
        }
    }

    if(atLeastOneUnhappy) {
        cout << max_time_index << endl;
    } else {
        cout << "0" << endl;
    }

    return 0;
}