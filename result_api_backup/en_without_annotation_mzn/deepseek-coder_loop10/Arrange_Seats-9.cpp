#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

int main() {
    int M, N, K, L, D;
    cin >> M >> N >> K >> L >> D;

    vector<pair<int, int>> horizontal_separations(M, {0, 0});
    vector<pair<int, int>> vertical_separations(N, {0, 0});

    for (int i = 0; i < D; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        if (x1 == x2) {
            int col = min(y1, y2);
            vertical_separations[col].first++;
            vertical_separations[col].second = col;
        } else if (y1 == y2) {
            int row = min(x1, x2);
            horizontal_separations[row].first++;
            horizontal_separations[row].second = row;
        }
    }

    sort(horizontal_separations.rbegin(), horizontal_separations.rend());
    sort(vertical_separations.rbegin(), vertical_separations.rend());

    unordered_set<int> selected_horizontal;
    unordered_set<int> selected_vertical;

    for (int i = 0; i < K; ++i) {
        selected_horizontal.insert(horizontal_separations[i].second);
    }

    for (int i = 0; i < L; ++i) {
        selected_vertical.insert(vertical_separations[i].second);
    }

    vector<int> sorted_horizontal(selected_horizontal.begin(), selected_horizontal.end());
    vector<int> sorted_vertical(selected_vertical.begin(), selected_vertical.end());

    sort(sorted_horizontal.begin(), sorted_horizontal.end());
    sort(sorted_vertical.begin(), sorted_vertical.end());

    for (int i = 0; i < K; ++i) {
        cout << sorted_horizontal[i] << (i < K - 1 ? " " : "\n");
    }

    for (int i = 0; i < L; ++i) {
        cout << sorted_vertical[i] << (i < L - 1 ? " " : "\n");
    }

    return 0;
}
