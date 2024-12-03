#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

struct Student {
    int x1, y1, x2, y2;
};

int main() {
    int M, N, K, L, D;
    cin >> M >> N >> K >> L >> D;

    vector<Student> students(D);
    for (int i = 0; i < D; i++) {
        cin >> students[i].x1 >> students[i].y1 >> students[i].x2 >> students[i].y2;
    }

    vector<int> horizontal_count(M, 0);
    vector<int> vertical_count(N, 0);

    for (const auto& s : students) {
        if (s.x1 == s.x2) {
            int y_min = min(s.y1, s.y2);
            vertical_count[y_min]++;
        } else if (s.y1 == s.y2) {
            int x_min = min(s.x1, s.x2);
            horizontal_count[x_min]++;
        }
    }

    vector<pair<int, int>> horizontal_pairs;
    vector<pair<int, int>> vertical_pairs;

    for (int i = 0; i < M; i++) {
        horizontal_pairs.emplace_back(horizontal_count[i], i);
    }
    for (int i = 0; i < N; i++) {
        vertical_pairs.emplace_back(vertical_count[i], i);
    }

    sort(horizontal_pairs.rbegin(), horizontal_pairs.rend());
    sort(vertical_pairs.rbegin(), vertical_pairs.rend());

    unordered_set<int> selected_horizontal;
    unordered_set<int> selected_vertical;

    for (int i = 0; i < K; i++) {
        selected_horizontal.insert(horizontal_pairs[i].second);
    }
    for (int i = 0; i < L; i++) {
        selected_vertical.insert(vertical_pairs[i].second);
    }

    vector<int> horizontal_result(selected_horizontal.begin(), selected_horizontal.end());
    vector<int> vertical_result(selected_vertical.begin(), selected_vertical.end());

    sort(horizontal_result.begin(), horizontal_result.end());
    sort(vertical_result.begin(), vertical_result.end());

    for (int i = 0; i < K; i++) {
        cout << horizontal_result[i] << (i < K - 1 ? " " : "\n");
    }
    for (int i = 0; i < L; i++) {
        cout << vertical_result[i] << (i < L - 1 ? " " : "\n");
    }

    return 0;
}