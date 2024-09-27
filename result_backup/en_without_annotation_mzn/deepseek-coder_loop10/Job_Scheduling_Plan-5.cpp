#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    vector<int> order(m * n);
    vector<vector<int>> machine(n, vector<int>(m));
    vector<vector<int>> time(n, vector<int>(m));
    vector<int> begin_time(m * n, 0);
    vector<int> end_time(m * n, 0);
    vector<int> process(m * n, 0);

    for (int i = 0; i < m * n; ++i) {
        cin >> order[i];
        order[i]--;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> machine[i][j];
            machine[i][j]--;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> time[i][j];
        }
    }

    for (int i = 0; i < m * n; ++i) {
        if (i > 0) {
            process[i] = process[i - 1];
            if (order[i] != order[i - 1]) {
                process[i]++;
            }
        }
    }

    for (int i = 0; i < m * n; ++i) {
        int max_t = 0;
        if (process[i] > 0) {
            max_t = 0;
            for (int j = 0; j < i; ++j) {
                if (order[j] == order[i]) {
                    max_t = max(max_t, end_time[j]);
                }
            }
        }

        int machine_id = machine[order[i]][process[i]];
        int min_start_time = max_t;

        for (int j = 0; j < i; ++j) {
            if (machine[order[j]][process[j]] == machine_id) {
                if (end_time[j] > max_t) {
                    bool can_start = true;
                    for (int k = 0; k < i; ++k) {
                        if (machine[order[k]][process[k]] == machine_id) {
                            if (!(end_time[j] >= end_time[k] || end_time[j] + time[order[i]][process[i]] <= begin_time[k])) {
                                can_start = false;
                                break;
                            }
                        }
                    }
                    if (can_start) {
                        min_start_time = min(min_start_time, end_time[j]);
                    }
                }
            }
        }

        begin_time[i] = min_start_time;
        end_time[i] = begin_time[i] + time[order[i]][process[i]];
    }

    int ans = *max_element(end_time.begin(), end_time.end());
    cout << ans << endl;

    return 0;
}
