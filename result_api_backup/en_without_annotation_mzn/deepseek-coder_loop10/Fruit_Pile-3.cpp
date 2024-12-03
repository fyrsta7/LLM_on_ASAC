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
        int min_sum = INT_MAX;
        int idx1 = -1, idx2 = -1;
        for (int j = 0; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (stat[i-1][j] != 0 && stat[i-1][k] != 0 && stat[i-1][j] + stat[i-1][k] < min_sum) {
                    min_sum = stat[i-1][j] + stat[i-1][k];
                    idx1 = j;
                    idx2 = k;
                }
            }
        }
        stamina += min_sum;
        stat[i] = stat[i-1];
        stat[i][idx1] = min_sum;
        stat[i][idx2] = 0;
    }

    cout << stamina << endl;
    return 0;
}
