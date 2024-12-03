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
        int min1 = 0, min2 = 1;
        if (stat[i-1][min1] > stat[i-1][min2]) swap(min1, min2);
        for (int j = 2; j < n; ++j) {
            if (stat[i-1][j] < stat[i-1][min1]) {
                min2 = min1;
                min1 = j;
            } else if (stat[i-1][j] < stat[i-1][min2]) {
                min2 = j;
            }
        }
        stat[i][min1] = stat[i-1][min1] + stat[i-1][min2];
        stat[i][min2] = 0;
        for (int j = 0; j < n; ++j) {
            if (j != min1 && j != min2) {
                stat[i][j] = stat[i-1][j];
            }
        }
        stamina += stat[i-1][min1] + stat[i-1][min2];
    }

    cout << stamina << endl;
    return 0;
}