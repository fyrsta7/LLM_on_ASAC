#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

int main() {
    int M, N, K, L, D;
    cin >> M >> N >> K >> L >> D;

    vector<pair<int, int>> horizontal_separations(M + 1, {0, 0});
    vector<pair<int, int>> vertical_separations(N + 1, {0, 0});

    for (int i = 0; i < D; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 == x2) {
            int y = min(y1, y2);
            vertical_separations[y].first++;
            vertical_separations[y].second = y;
        } else {
            int x = min(x1, x2);
            horizontal_separations[x].first++;
            horizontal_separations[x].second = x;
        }
    }

    sort(horizontal_separations.begin(), horizontal_separations.end(), greater<pair<int, int>>());
    sort(vertical_separations.begin(), vertical_separations.end(), greater<pair<int, int>>());

    unordered_set<int> selected_horizontal, selected_vertical;

    for (int i = 0; i < K; ++i) {
        selected_horizontal.insert(horizontal_separations[i].second);
    }
    for (int i = 0; i < L; ++i) {
        selected_vertical.insert(vertical_separations[i].second);
    }

    vector<int> result_horizontal(selected_horizontal.begin(), selected_horizontal.end());
    vector<int> result_vertical(selected_vertical.begin(), selected_vertical.end());

    sort(result_horizontal.begin(), result_horizontal.end());
    sort(result_vertical.begin(), result_vertical.end());

    for (int i = 0; i < K; ++i) {
        cout << result_horizontal[i] << (i < K - 1 ? " " : "\n");
    }
    for (int i = 0; i < L; ++i) {
        cout << result_vertical[i] << (i < L - 1 ? " " : "\n");
    }

    return 0;
}
