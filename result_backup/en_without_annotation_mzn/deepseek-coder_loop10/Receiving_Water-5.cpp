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

    for (int i = 0; i < m; ++i) {
        choice[i] = i;
    }

    for (int i = m; i < n; ++i) {
        vector<int> latest(m, -1);
        for (int j = 0; j < i; ++j) {
            latest[choice[j]] = j;
        }

        int min_start = INT_MAX;
        for (int j = 0; j < m; ++j) {
            if (latest[j] != -1) {
                min_start = min(min_start, start[latest[j]] + w[latest[j]]);
            }
        }

        start[i] = min_start;
        int best_choice = 0;
        for (int j = 1; j < m; ++j) {
            if (latest[j] != -1 && start[latest[j]] + w[latest[j]] < start[latest[best_choice]] + w[latest[best_choice]]) {
                best_choice = j;
            }
        }
        choice[i] = best_choice;
    }

    int max_end = 0;
    for (int i = 0; i < n; ++i) {
        max_end = max(max_end, start[i] + w[i]);
    }

    cout << max_end << endl;

    return 0;
}