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

    for (int i = 0; i < M; ++i) {
        horizontal_separations[i].second = i + 1;
    }
    for (int i = 0; i < N; ++i) {
        vertical_separations[i].second = i + 1;
    }

    for (int i = 0; i < D; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 == x2) {
            int min_y = min(y1, y2);
            vertical_separations[min_y - 1].first++;
        } else {
            int min_x = min(x1, x2);
            horizontal_separations[min_x - 1].first++;
        }
    }

    sort(horizontal_separations.rbegin(), horizontal_separations.rend());
    sort(vertical_separations.rbegin(), vertical_separations.rend());

    unordered_set<int> horizontal_selected;
    unordered_set<int> vertical_selected;

    for (int i = 0; i < K; ++i) {
        horizontal_selected.insert(horizontal_separations[i].second);
    }
    for (int i = 0; i < L; ++i) {
        vertical_selected.insert(vertical_separations[i].second);
    }

    vector<int> horizontal_output(horizontal_selected.begin(), horizontal_selected.end());
    vector<int> vertical_output(vertical_selected.begin(), vertical_selected.end());

    sort(horizontal_output.begin(), horizontal_output.end());
    sort(vertical_output.begin(), vertical_output.end());

    for (int i = 0; i < K; ++i) {
        cout << horizontal_output[i] << (i < K - 1 ? " " : "\n");
    }
    for (int i = 0; i < L; ++i) {
        cout << vertical_output[i] << (i < L - 1 ? " " : "\n");
    }

    return 0;
}
