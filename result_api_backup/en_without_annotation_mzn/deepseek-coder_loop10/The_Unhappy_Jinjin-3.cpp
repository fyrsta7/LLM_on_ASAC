#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<std::pair<int, int>> time(7);
    for (int i = 0; i < 7; ++i) {
        std::cin >> time[i].first >> time[i].second;
    }

    int longest = 0;
    int unhappy_count = 0;

    for (int i = 0; i < 7; ++i) {
        int total_time = time[i].first + time[i].second;
        if (total_time > 8) {
            ++unhappy_count;
            if (total_time > time[longest].first + time[longest].second) {
                longest = i;
            }
        }
    }

    if (unhappy_count == 0) {
        std::cout << "0" << std::endl;
    } else {
        std::cout << (time[longest].first + time[longest].second) << std::endl;
    }

    return 0;
}