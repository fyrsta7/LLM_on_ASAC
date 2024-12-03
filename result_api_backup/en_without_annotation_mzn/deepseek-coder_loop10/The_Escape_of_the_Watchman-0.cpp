#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int M, S, T;
    cin >> M >> S >> T;

    int max_dis = 0;
    int min_time = T;
    int current_mana = M;

    for (int t = 1; t <= T; ++t) {
        if (current_mana >= 10) {
            max_dis += 60;
            current_mana -= 10;
        } else {
            max_dis += 17;
        }

        if (max_dis >= S) {
            min_time = t;
            break;
        }

        if (current_mana < 10) {
            current_mana += 4;
        }
    }

    if (max_dis >= S) {
        cout << "Yes\n" << min_time << endl;
    } else {
        cout << "No\n" << max_dis << endl;
    }

    return 0;
}
