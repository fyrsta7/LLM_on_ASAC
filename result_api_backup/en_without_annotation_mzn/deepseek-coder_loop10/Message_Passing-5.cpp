#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> T(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> T[i];
    }

    int min_turns = N;
    for (int x = 1; x <= N; ++x) {
        vector<int> y(N + 1, -1);
        y[0] = x;
        int turns = 0;
        for (int i = 1; i <= N; ++i) {
            y[i] = T[y[i - 1]];
            if (y[i] == x) {
                turns = i;
                break;
            }
        }
        min_turns = min(min_turns, turns);
    }

    cout << "turns=" << min_turns << endl;
    return 0;
}