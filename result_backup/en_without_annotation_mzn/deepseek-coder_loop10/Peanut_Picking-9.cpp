#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int M, N, K;
vector<vector<int>> peanuts;
set<int> peanut_set;

int main() {
    cin >> M >> N >> K;
    peanuts.resize(M, vector<int>(N));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> peanuts[i][j];
            if (peanuts[i][j] != 0) {
                peanut_set.insert(peanuts[i][j]);
            }
        }
    }

    vector<int> sorted_peanuts(peanut_set.begin(), peanut_set.end());
    sort(sorted_peanuts.begin(), sorted_peanuts.end(), greater<int>());

    int num = 0;
    int x = 0, y = 0;
    for (int i = 0; i < K; ++i) {
        if (i == 0) {
            x = 1;
        } else if (i == K - 1) {
            x = 0;
        } else {
            if (x == 0) {
                x = 1;
            } else if (x == M) {
                x = M - 1;
            } else if (y == 0) {
                y = 1;
            } else if (y == N) {
                y = N - 1;
            }
        }

        if (peanuts[x][y] != 0) {
            auto it = find(sorted_peanuts.begin(), sorted_peanuts.end(), peanuts[x][y]);
            if (it != sorted_peanuts.end()) {
                num += peanuts[x][y];
                sorted_peanuts.erase(it);
            }
        }
    }

    cout << num << endl;
    return 0;
}
