#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

int M, N, K, L, D;
vector<vector<int>> students;
vector<int> horizontal, vertical;

bool horizontal_separate(int i) {
    for (int j : horizontal) {
        if ((students[i][0] == j && students[i][2] == j + 1) || (students[i][0] == j + 1 && students[i][2] == j)) {
            return true;
        }
    }
    return false;
}

bool vertical_separate(int i) {
    for (int j : vertical) {
        if ((students[i][1] == j && students[i][3] == j + 1) || (students[i][1] == j + 1 && students[i][3] == j)) {
            return true;
        }
    }
    return false;
}

int count_separations() {
    int total = 0;
    for (int i = 0; i < D; ++i) {
        if (horizontal_separate(i) || vertical_separate(i)) {
            ++total;
        }
    }
    return total;
}

int main() {
    cin >> M >> N >> K >> L >> D;
    students.resize(D, vector<int>(4));
    for (int i = 0; i < D; ++i) {
        cin >> students[i][0] >> students[i][1] >> students[i][2] >> students[i][3];
    }

    horizontal.resize(K);
    vertical.resize(L);

    unordered_set<int> h_set, v_set;
    for (int i = 1; i <= M - 1; ++i) {
        h_set.insert(i);
    }
    for (int i = 1; i <= N - 1; ++i) {
        v_set.insert(i);
    }

    for (int i = 0; i < D; ++i) {
        if (students[i][0] == students[i][2]) {
            v_set.erase(min(students[i][1], students[i][3]));
        } else {
            h_set.erase(min(students[i][0], students[i][2]));
        }
    }

    for (int i = 0; i < K; ++i) {
        horizontal[i] = *h_set.begin();
        h_set.erase(h_set.begin());
    }
    for (int i = 0; i < L; ++i) {
        vertical[i] = *v_set.begin();
        v_set.erase(v_set.begin());
    }

    sort(horizontal.begin(), horizontal.end());
    sort(vertical.begin(), vertical.end());

    for (int i = 0; i < K; ++i) {
        cout << horizontal[i] << (i < K - 1 ? " " : "\n");
    }
    for (int i = 0; i < L; ++i) {
        cout << vertical[i] << (i < L - 1 ? " " : "\n");
    }

    return 0;
}
