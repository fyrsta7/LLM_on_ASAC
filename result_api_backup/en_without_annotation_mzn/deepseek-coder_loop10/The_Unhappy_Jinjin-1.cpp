#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<vector<int>> time(7, vector<int>(2));
    for (int i = 0; i < 7; ++i) {
        cin >> time[i][0] >> time[i][1];
    }

    int longest = 0;
    int unhappy_count = 0;

    for (int i = 0; i < 7; ++i) {
        int total_time = time[i][0] + time[i][1];
        if (total_time > 8) {
            unhappy_count++;
            if (total_time > time[longest][0] + time[longest][1]) {
                longest = i;
            }
        }
    }

    if (unhappy_count == 0) {
        cout << "0" << endl;
    } else {
        cout << time[longest][0] + time[longest][1] << endl;
    }

    return 0;
}