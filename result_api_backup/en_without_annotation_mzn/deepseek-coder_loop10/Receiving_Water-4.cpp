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
    vector<int> choice(n, 0);
    vector<int> latest(m, 0);

    for (int i = 0; i < m; ++i) {
        choice[i] = i;
    }

    for (int i = m; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            latest[j] = 0;
            for (int k = 0; k < i; ++k) {
                if (choice[k] == j) {
                    latest[j] = k;
                }
            }
        }

        int min_start = INT_MAX;
        for (int j = 0; j < m; ++j) {
            min_start = min(min_start, start[latest[j]] + w[latest[j]]);
        }

        start[i] = min_start;
        int best_choice = 0;
        for (int j = 1; j < m; ++j) {
            if (start[latest[j]] + w[latest[j]] < start[latest[best_choice]] + w[latest[best_choice]]) {
                best_choice = j;
            }
        }
        choice[i] = best_choice;
    }

    int max_finish_time = 0;
    for (int i = 0; i < n; ++i) {
        max_finish_time = max(max_finish_time, start[i] + w[i]);
    }

    cout << max_finish_time << endl;

    return 0;
}
