#include <iostream>
using namespace std;

int main() {
    int maxHours = 8;
    int unhappiestDay = 0;
    int maxUnhappiness = 0;

    for (int i = 1; i <= 7; ++i) {
        int schoolHours, classHours;
        cin >> schoolHours >> classHours;
        int totalHours = schoolHours + classHours;

        if (totalHours > maxHours) {
            int unhappiness = totalHours - maxHours;
            if (unhappiness > maxUnhappiness) {
                maxUnhappiness = unhappiness;
                unhappiestDay = i;
            }
        }
    }

    cout << unhappiestDay << endl;
    return 0;
}