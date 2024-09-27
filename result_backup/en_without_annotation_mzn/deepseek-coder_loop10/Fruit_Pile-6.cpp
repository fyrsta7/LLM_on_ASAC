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

    int stamina = 0;
    for (int i = 2; i <= n; ++i) {
        int min_sum = INT_MAX;
        int min_j = -1, min_k = -1;

        for (int j = 0; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (stat[i - 1][j] != 0 && stat[i - 1][k] != 0) {
                    int sum = stat[i - 1][j] + stat[i - 1][k];
                    if (sum < min_sum) {
                        min_sum = sum;
                        min_j = j;
                        min_k = k;
                    }
                }
            }
        }

        stamina += min_sum;
        stat[i][min_j] = min_sum;
        stat[i][min_k] = 0;
        for (int j = 0; j < n; ++j) {
            if (j != min_j && j != min_k) {
                stat[i][j] = stat[i - 1][j];
            }
        }
    }

    cout << stamina << endl;
    return 0;
}
