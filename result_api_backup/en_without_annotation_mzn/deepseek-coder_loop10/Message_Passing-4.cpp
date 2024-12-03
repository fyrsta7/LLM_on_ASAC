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
        vector<int> visited(N + 1, -1);
        int current = start;
        int turns = 0;

        while (visited[current] == -1) {
            visited[current] = turns;
            current = T[current];
            turns++;
        }

        min_turns = min(min_turns, turns - visited[current]);
    }

    cout << "turns=" << min_turns << endl;

    return 0;
}