#include <iostream>

int main() {
    int maxUnhappiness = 0;
    int unhappiestDay = 0;

    for (int day = 1; day <= 7; ++day) {
        int schoolTime, classTime;
        std::cin >> schoolTime >> classTime;

        int totalHours = schoolTime + classTime;
        if (totalHours > 8 && totalHours > maxUnhappiness) {
            maxUnhappiness = totalHours;
            unhappiestDay = day;
        }
    }

    if (unhappiestDay == 0) {
        std::cout << 0;
    } else {
        std::cout << unhappiestDay;
    }

    return 0;
}