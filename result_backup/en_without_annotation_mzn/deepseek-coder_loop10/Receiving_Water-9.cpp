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
        int min_start = start[latest[0]] + w[latest[0]];
        for (int j = 1; j < m; ++j) {
            min_start = min(min_start, start[latest[j]] + w[latest[j]]);
        }
        start[i] = min_start;

        int chosen_machine = 0;
        int min_end_time = start[latest[0]] + w[latest[0]];
        for (int j = 1; j < m; ++j) {
            int end_time = start[latest[j]] + w[latest[j]];
            if (end_time < min_end_time) {
                min_end_time = end_time;
                chosen_machine = j;
            }
        }
        latest[chosen_machine] = i;
    }

    int max_time = 0;
    for (int i = 0; i < n; ++i) {
        max_time = max(max_time, start[i] + w[i]);
    }

    cout << max_time << endl;
    return 0;
}
