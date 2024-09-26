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
    for (int i = 0; i < K && i < sorted_peanuts.size(); ++i) {
        int target = sorted_peanuts[i];
        for (int j = 0; j < M; ++j) {
            for (int k = 0; k < N; ++k) {
                if (peanuts[j][k] == target) {
                    if (j > x) {
                        num += j - x;
                        x = j;
                    } else if (j < x) {
                        num += x - j;
                        x = j;
                    }
                    if (k > y) {
                        num += k - y;
                        y = k;
                    } else if (k < y) {
                        num += y - k;
                        y = k;
                    }
                    num += 1; // Pick action
                    peanuts[j][k] = 0;
                }
            }
        }
    }

    cout << num << endl;
    return 0;
}
