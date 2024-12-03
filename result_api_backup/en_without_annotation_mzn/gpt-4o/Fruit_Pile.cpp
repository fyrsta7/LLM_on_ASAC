#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> fruit(n);
    for (int i = 0; i < n; ++i) {
        cin >> fruit[i];
    }

    vector<vector<int>> stat(n, vector<int>(n));
    vector<vector<int>> merge(n, vector<int>(2));
    int stamina = 0;

    for (int i = 0; i < n; ++i) {
        stat[0][i] = fruit[i];
    }

    for (int i = 1; i < n; ++i) {
        int min_merge = INT_MAX;
        int min_idx1 = -1, min_idx2 = -1;

        for (int j = 0; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (stat[i-1][j] != 0 && stat[i-1][k] != 0) {
                    int current_stamina = stat[i-1][j] + stat[i-1][k];
                    if (current_stamina < min_merge) {
                        min_merge = current_stamina;
                        min_idx1 = j;
                        min_idx2 = k;
                    }
                }
            }
        }

        if (min_idx1 != -1 && min_idx2 != -1) {
            merge[i][0] = min_idx1 + 1;
            merge[i][1] = min_idx2 + 1;
            stamina += min_merge;

            for (int j = 0; j < n; ++j) {
                if (j == min_idx1) {
                    stat[i][j] = stat[i-1][j] + stat[i-1][min_idx2];
                } else if (j == min_idx2) {
                    stat[i][j] = 0;
                } else {
                    stat[i][j] = stat[i-1][j];
                }
            }
        }
    }

    cout << stamina << endl;
    return 0;
}