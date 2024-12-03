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

    int cnt = 0;
    int last_index = -1;
    for (const auto& spot : spots) {
        if (spot.first > last_index) {
            cnt++;
            last_index = spot.second;
        }
    }

    cout << L + 1 - cnt << endl;
    return 0;
}