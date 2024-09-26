#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> fruit(n);
    for (int i = 0; i < n; ++i) {
        cin >> fruit[i];
    }

    vector<vector<int>> stat(n + 1, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        stat[1][i] = fruit[i];
    }

    vector<pair<int, int>> merge(n + 1);
    int stamina = 0;

    for (int i = 2; i <= n; ++i) {
        int min_sum = INT_MAX;
        int idx1 = -1, idx2 = -1;

        for (int j = 0; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (stat[i - 1][j] != 0 && stat[i - 1][k] != 0) {
                    int sum = stat[i - 1][j] + stat[i - 1][k];
                    if (sum < min_sum) {
                        min_sum = sum;
                        idx1 = j;
                        idx2 = k;
                    }
                }
            }
        }

        merge[i] = {idx1 + 1, idx2 + 1};
        stat[i][idx1] = stat[i - 1][idx1] + stat[i - 1][idx2];
        stat[i][idx2] = 0;
        for (int j = 0; j < n; ++j) {
            if (j != idx1 && j != idx2) {
                stat[i][j] = stat[i - 1][j];
            }
        }

        stamina += min_sum;
    }

    cout << stamina << endl;

    return 0;
}
