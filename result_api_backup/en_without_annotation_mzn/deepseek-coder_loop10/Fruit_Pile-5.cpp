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

    vector<int> stat(fruit);
    int stamina = 0;

    for (int i = 2; i <= n; ++i) {
        int min_sum = INT_MAX;
        int idx1 = -1, idx2 = -1;

        for (int j = 0; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (stat[j] != 0 && stat[k] != 0 && stat[j] + stat[k] < min_sum) {
                    min_sum = stat[j] + stat[k];
                    idx1 = j;
                    idx2 = k;
                }
            }
        }

        stamina += min_sum;
        stat[idx1] += stat[idx2];
        stat[idx2] = 0;
    }

    cout << stamina << endl;
    return 0;
}
