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
        int min1 = -1, min2 = -1;
        for (int j = 0; j < n; ++j) {
            if (stat[j] != 0) {
                if (min1 == -1 || stat[j] < stat[min1]) {
                    min2 = min1;
                    min1 = j;
                } else if (min2 == -1 || stat[j] < stat[min2]) {
                    min2 = j;
                }
            }
        }

        stamina += stat[min1] + stat[min2];
        stat[min1] += stat[min2];
        stat[min2] = 0;
    }

    cout << stamina << endl;
    return 0;
}
