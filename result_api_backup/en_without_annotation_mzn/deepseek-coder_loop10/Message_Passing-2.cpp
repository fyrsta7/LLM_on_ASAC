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
    for (int start = 1; start <= N; ++start) {
        vector<int> y(N + 1, -1);
        y[0] = start;
        int turns = 0;
        for (int i = 1; i <= N; ++i) {
            y[i] = T[y[i - 1]];
            turns++;
            if (y[i] == start) {
                min_turns = min(min_turns, turns);
                break;
            }
        }
    }

    cout << "turns=" << min_turns << endl;
    return 0;
}