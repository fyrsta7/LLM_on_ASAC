#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Peanut {
    int row;
    int col;
    int amount;
};

bool compare(Peanut a, Peanut b) {
    return a.amount > b.amount;
}

int main() {
    int M, N, K;
    cin >> M >> N >> K;

    vector<vector<int>> field(M, vector<int>(N, 0));
    vector<Peanut> peanuts;

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> field[i][j];
            if (field[i][j] > 0) {
                peanuts.push_back({i, j, field[i][j]});
            }
        }
    }

    sort(peanuts.begin(), peanuts.end(), compare);
    
    int maxPeanuts = 0;
    int timeSpent = 0;
    int currentRow = -1, currentCol = -1;

    for (Peanut p : peanuts) {
        if (currentRow == -1 && currentCol == -1) { // First jump
            timeSpent = p.row + 1;
        } else { // Jumping between plants
            timeSpent += abs(p.row - currentRow) + abs(p.col - currentCol);
        }

        if (timeSpent + p.row + 1 <= K) { // Ensure enough time to return
            maxPeanuts += p.amount;
            timeSpent += 1;
            currentRow = p.row;
            currentCol = p.col;
        } else {
            break;
        }
    }

    cout << maxPeanuts << endl;

    return 0;
}