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
    for (int i = 2; i <= n; ++i) {
        int min_sum = INT_MAX;
        int min_j = -1, min_k = -1;
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (j != k && stat[i - 1][j] != 0 && stat[i - 1][k] != 0) {
                    int sum = stat[i - 1][j] + stat[i - 1][k];
                    if (sum < min_sum) {
                        min_sum = sum;
                        min_j = j;
                        min_k = k;
                    }
                }
            }
        }
        merge[i] = {min_j + 1, min_k + 1};
        stat[i][min_j] = min_sum;
        stat[i][min_k] = 0;
        for (int j = 0; j < n; ++j) {
            if (j != min_j && j != min_k) {
                stat[i][j] = stat[i - 1][j];
            }
        }
    }

    int stamina = 0;
    for (int i = 2; i <= n; ++i) {
        stamina += stat[i - 1][merge[i].first - 1] + stat[i - 1][merge[i].second - 1];
    }

    cout << stamina << endl;
    return 0;
}
