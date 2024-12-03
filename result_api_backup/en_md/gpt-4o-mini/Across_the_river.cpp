#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    int L;
    cin >> L;

    int S, T, M;
    cin >> S >> T >> M;

    vector<int> pebbles(M);
    for (int i = 0; i < M; i++) {
        cin >> pebbles[i];
    }

    sort(pebbles.begin(), pebbles.end());

    set<int> pebbleSet(pebbles.begin(), pebbles.end());
    queue<pair<int, int>> q; // (current position, number of pebbles stepped on)
    q.push({0, 0});
    vector<bool> visited(L + 1, false);
    visited[0] = true;

    int minPebbles = INT_MAX;

    while (!q.empty()) {
        auto [curr, steps] = q.front();
        q.pop();

        for (int jump = S; jump <= T; jump++) {
            int next = curr + jump;
            if (next > L) {
                minPebbles = min(minPebbles, steps);
            } else if (!visited[next]) {
                visited[next] = true;
                q.push({next, steps + (pebbleSet.count(next) > 0 ? 1 : 0)});
            }
        }
    }

    cout << minPebbles << endl;
    return 0;
}