#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int L, M;
    cin >> L >> M;
    vector<pair<int, int>> spots(M);
    for (int i = 0; i < M; ++i) {
        cin >> spots[i].first >> spots[i].second;
    }

    sort(spots.begin(), spots.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
    });

    vector<bool> index(L + 1, true);
    int cnt = 0;
    int last_end = -1;

    for (const auto& spot : spots) {
        if (spot.first > last_end) {
            for (int i = last_end + 1; i < spot.first; ++i) {
                index[i] = false;
            }
            last_end = spot.second;
        }
    }

    for (int i = last_end + 1; i <= L; ++i) {
        index[i] = false;
    }

    for (int i = 0; i <= L; ++i) {
        if (index[i]) {
            ++cnt;
        }
    }

    cout << cnt << endl;
    return 0;
}