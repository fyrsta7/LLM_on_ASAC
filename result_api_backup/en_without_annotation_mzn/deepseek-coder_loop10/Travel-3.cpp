#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> road(m, vector<int>(2));
    for (int i = 0; i < m; ++i) {
        cin >> road[i][0] >> road[i][1];
    }

    vector<int> route(2 * n);
    for (int i = 0; i < 2 * n; ++i) {
        cin >> route[i];
    }

    int length = 2 * n;
    vector<int> first(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < length; ++j) {
            if (route[j] == i + 1) {
                first[i] = j + 1;
                break;
            }
        }
    }

    sort(first.begin(), first.end());

    int score = 0;
    for (int i = 0; i < n; ++i) {
        score += pow(n, n - i) * (first[i] - 1);
    }

    cout << score << endl;

    return 0;
}