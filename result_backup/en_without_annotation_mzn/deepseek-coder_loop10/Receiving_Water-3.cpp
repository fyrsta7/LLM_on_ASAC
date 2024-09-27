#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> w(n);
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
    }

    vector<int> start(n, 0);
    vector<int> latest(m, 0);

    for (int i = m; i < n; ++i) {
        int min_start = INT_MAX;
        for (int j = 0; j < m; ++j) {
            min_start = min(min_start, start[latest[j]] + w[latest[j]]);
        }
        start[i] = min_start;

        int min_index = 0;
        for (int j = 1; j < m; ++j) {
            if (start[latest[j]] + w[latest[j]] < start[latest[min_index]] + w[latest[min_index]]) {
                min_index = j;
            }
        }
        latest[min_index] = i;
    }

    int max_end_time = 0;
    for (int i = 0; i < n; ++i) {
        max_end_time = max(max_end_time, start[i] + w[i]);
    }

    cout << max_end_time << endl;
    return 0;
}
