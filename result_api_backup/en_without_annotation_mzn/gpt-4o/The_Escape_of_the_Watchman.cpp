#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

enum action { run, flash, rest };

int main() {
    int M, S, T;
    cin >> M >> S >> T;

    vector<int> current_mana(T + 1);
    vector<int> current_dis(T + 1);
    current_dis[0] = 0;
    current_mana[0] = M;

    int min_time = T;
    int max_dis = 0;

    for (int i = 1; i <= T; ++i) {
        if (i >= 10 && current_mana[i - 10] > 0) {
            current_dis[i] = max(current_dis[i - 1] + 17, current_dis[i - 10] + 60);
            current_mana[i] = max(current_mana[i - 1], current_mana[i - 10] - 10);
        } else {
            current_dis[i] = current_dis[i - 1] + 17;
            current_mana[i] = current_mana[i - 1];
        }

        max_dis = max(max_dis, current_dis[i]);

        if (current_dis[i] >= S) {
            min_time = i;
            break;
        }
    }

    if (max_dis >= S)
        cout << "Yes\n" << min_time << '\n';
    else
        cout << "No\n" << max_dis << '\n';

    return 0;
}