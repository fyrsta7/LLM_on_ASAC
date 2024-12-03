#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Pair {
    int x, y, p, q;
};

bool compare(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second > b.second;
}

int main() {
    int M, N, K, L, D;
    cin >> M >> N >> K >> L >> D;
    vector<int> row(M, 0);
    vector<int> col(N, 0);
    vector<Pair> pairs(D);

    for (int i = 0; i < D; ++i) {
        cin >> pairs[i].x >> pairs[i].y >> pairs[i].p >> pairs[i].q;
        if (pairs[i].x == pairs[i].p) {
            col[min(pairs[i].y, pairs[i].q)]++;
        } else {
            row[min(pairs[i].x, pairs[i].p)]++;
        }
    }

    vector<pair<int, int>> rowPairs, colPairs;
    for (int i = 0; i < M; ++i) {
        if (row[i] > 0) {
            rowPairs.push_back(make_pair(i, row[i]));
        }
    }
    for (int i = 0; i < N; ++i) {
        if (col[i] > 0) {
            colPairs.push_back(make_pair(i, col[i]));
        }
    }

    sort(rowPairs.begin(), rowPairs.end(), compare);
    sort(colPairs.begin(), colPairs.end(), compare);

    vector<int> selectedRows, selectedCols;
    for (int i = 0; i < K; ++i) {
        selectedRows.push_back(rowPairs[i].first);
    }
    for (int i = 0; i < L; ++i) {
        selectedCols.push_back(colPairs[i].first);
    }

    sort(selectedRows.begin(), selectedRows.end());
    sort(selectedCols.begin(), selectedCols.end());

    for (int i = 0; i < K; ++i) {
        cout << selectedRows[i] << (i == K - 1 ? "\n" : " ");
    }
    for (int i = 0; i < L; ++i) {
        cout << selectedCols[i] << (i == L - 1 ? "\n" : " ");
    }

    return 0;
}
