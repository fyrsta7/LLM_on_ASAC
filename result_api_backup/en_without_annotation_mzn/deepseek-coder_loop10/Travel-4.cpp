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

    vector<int> first(n);
    for (int i = 0; i < n; ++i) {
        first[i] = route[0];
    }

    sort(first.begin(), first.end());

    int score = 0;
    for (int i = 0; i < n; ++i) {
        score += pow(n, n - i) * first[i];
    }

    cout << score << endl;

    return 0;
}