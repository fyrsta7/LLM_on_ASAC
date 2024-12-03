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

    vector<int> peanut_list(peanut_set.begin(), peanut_set.end());
    sort(peanut_list.begin(), peanut_list.end(), greater<int>());

    int num = 0;
    int x = 0, y = 0;
    for (int i = 0; i < K; ++i) {
        if (i < peanut_list.size()) {
            int target = peanut_list[i];
            for (int j = 0; j < M; ++j) {
                for (int k = 0; k < N; ++k) {
                    if (peanuts[j][k] == target) {
                        x = j;
                        y = k;
                        break;
                    }
                }
                if (x != 0 || y != 0) break;
            }
            num += target;
        }
    }

    cout << num << endl;
    return 0;
}
