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

    vector<vector<int>> stat(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        stat[0][i] = fruit[i];
    }

    int stamina = 0;
    for (int i = 1; i < n; ++i) {
        int max1 = -1, max2 = -1;
        int idx1 = -1, idx2 = -1;

        for (int j = 0; j < n; ++j) {
            if (stat[i-1][j] > max1) {
                max2 = max1;
                idx2 = idx1;
                max1 = stat[i-1][j];
                idx1 = j;
            } else if (stat[i-1][j] > max2) {
                max2 = stat[i-1][j];
                idx2 = j;
            }
        }

        stat[i][idx1] = max1 + max2;
        stat[i][idx2] = 0;
        stamina += max1 + max2;

        for (int j = 0; j < n; ++j) {
            if (j != idx1 && j != idx2) {
                stat[i][j] = stat[i-1][j];
            }
        }
    }

    cout << stamina << endl;
    return 0;
}