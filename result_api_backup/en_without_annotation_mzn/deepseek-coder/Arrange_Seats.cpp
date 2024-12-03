#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

int main() {
    int M, N, K, L, D;
    cin >> M >> N >> K >> L >> D;

    vector<int> horizontal_count(M + 1, 0);
    vector<int> vertical_count(N + 1, 0);

    for (int i = 0; i < D; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 == x2) {
            vertical_count[min(y1, y2)]++;
        } else {
            horizontal_count[min(x1, x2)]++;
        }
    }

    vector<pair<int, int>> horizontal_pairs;
    vector<pair<int, int>> vertical_pairs;

    for (int i = 1; i < M; ++i) {
        horizontal_pairs.emplace_back(horizontal_count[i], i);
    }
    for (int i = 1; i < N; ++i) {
        vertical_pairs.emplace_back(vertical_count[i], i);
    }

    sort(horizontal_pairs.rbegin(), horizontal_pairs.rend());
    sort(vertical_pairs.rbegin(), vertical_pairs.rend());

    unordered_set<int> selected_horizontal;
    unordered_set<int> selected_vertical;

    for (int i = 0; i < K; ++i) {
        selected_horizontal.insert(horizontal_pairs[i].second);
    }
    for (int i = 0; i < L; ++i) {
        selected_vertical.insert(vertical_pairs[i].second);
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
