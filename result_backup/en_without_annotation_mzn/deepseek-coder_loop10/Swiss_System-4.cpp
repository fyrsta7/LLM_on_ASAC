#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, R, Q;
    cin >> N >> R >> Q;
    vector<int> s(2 * N), w(2 * N);
    for (int i = 0; i < 2 * N; ++i) cin >> s[i];
    for (int i = 0; i < 2 * N; ++i) cin >> w[i];

    vector<int> players(2 * N);
    for (int i = 0; i < 2 * N; ++i) players[i] = i;

    for (int round = 0; round < R; ++round) {
        vector<int> winners;
        for (int i = 0; i < N; ++i) {
            int a = players[2 * i];
            int b = players[2 * i + 1];
            if (w[a] > w[b]) {
                s[a]++;
                winners.push_back(a);
            } else {
                s[b]++;
                winners.push_back(b);
            }
        }
        sort(winners.begin(), winners.end(), [&](int x, int y) {
            return s[x] != s[y] ? s[x] > s[y] : x < y;
        });
        players = winners;
    }

    cout << players[Q - 1] + 1 << endl;
    return 0;
}
