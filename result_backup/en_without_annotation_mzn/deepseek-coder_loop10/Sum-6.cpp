#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> color(n);
    vector<int> number(n);
    for (int i = 0; i < n; ++i) {
        cin >> color[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> number[i];
    }

    long long total = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (color[i] == color[j] && 2 * j - i < n && color[j] == color[2 * j - i]) {
                total += (i + 2 * j - i) * (number[i] + number[2 * j - i]);
            }
        }
    }

    int res = total % 10007;
    cout << res << endl;

    return 0;
}