#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int schoolTime, classTime;
    int maxUnhappiness = 0, unhappiestDay = 0;

    for (int day = 1; day <= 7; day++) {
        cin >> schoolTime >> classTime;
        int totalTime = schoolTime + classTime;

        if (totalTime > 8) {
            int unhappiness = totalTime - 8;
            if (unhappiness > maxUnhappiness) {
                maxUnhappiness = unhappiness;
                unhappiestDay = day;
            }
        }
    }

    cout << (maxUnhappiness > 0 ? unhappiestDay : 0) << endl;

    return 0;
}