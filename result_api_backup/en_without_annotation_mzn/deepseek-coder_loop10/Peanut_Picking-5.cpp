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

    int max_num = 0;
    for (int i = 0; i < min(K, (int)peanut_list.size()); ++i) {
        max_num += peanut_list[i];
    }

    cout << max_num << endl;
    return 0;
}
