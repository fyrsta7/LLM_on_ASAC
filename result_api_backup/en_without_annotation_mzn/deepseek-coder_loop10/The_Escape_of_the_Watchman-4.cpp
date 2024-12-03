#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int M, S, T;
    cin >> M >> S >> T;

    int max_dis = 0;
    int mana = M;
    int min_time = 0;

    for (int t = 1; t <= T; ++t) {
        if (mana >= 10) {
            max_dis += 60;
            mana -= 10;
        } else {
            max_dis += 17;
        }

        if (max_dis >= S) {
            cout << "Yes\n" << t << endl;
            return 0;
        }

        if (mana < 10) {
            mana += 4;
        }
    }

    cout << "No\n" << max_dis << endl;
    return 0;
}
