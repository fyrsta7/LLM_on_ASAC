#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct WhisperPair {
    int x1, y1, x2, y2;
};

int main() {
    int M, N, K, L, D;
    cin >> M >> N >> K >> L >> D;

    vector<WhisperPair> whispers(D);
    for (int i = 0; i < D; i++) {
        cin >> whispers[i].x1 >> whispers[i].y1 >> whispers[i].x2 >> whispers[i].y2;
    }

    vector<int> rowCount(M + 1, 0), colCount(N + 1, 0);

    for (const auto& wp : whispers) {
        if (wp.x1 == wp.x2) { // same row
            int row = wp.x1;
            rowCount[row]++;
        } else { // same column
            int col = wp.y1;
            colCount[col]++;
        }
    }

    vector<int> chosenRows, chosenCols;

    for (int i = 1; i < M; i++) {
        if (rowCount[i] > 0) {
            chosenRows.push_back(i);
            if (chosenRows.size() == K) break;
        }
    }

    for (int i = 1; i < N; i++) {
        if (colCount[i] > 0) {
            chosenCols.push_back(i);
            if (chosenCols.size() == L) break;
        }
    }

    for (int i = 0; i < chosenRows.size(); i++) {
        cout << chosenRows[i] << (i == chosenRows.size() - 1 ? "" : " ");
    }
    cout << endl;

    for (int i = 0; i < chosenCols.size(); i++) {
        cout << chosenCols[i] << (i == chosenCols.size() - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}