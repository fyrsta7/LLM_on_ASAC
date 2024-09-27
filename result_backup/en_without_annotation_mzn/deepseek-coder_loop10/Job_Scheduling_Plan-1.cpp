#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int m, n;
    cin >> m >> n;

    vector<int> order(m * n);
    for (int i = 0; i < m * n; ++i) {
        cin >> order[i];
    }

    vector<vector<int>> machine(n, vector<int>(m));
    vector<vector<int>> time(n, vector<int>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> machine[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> time[i][j];
        }
    }

    vector<int> begin_time(m * n, 0);
    vector<int> end_time(m * n, 0);
    vector<int> process(m * n, 0);

    for (int i = 0; i < m * n; ++i) {
        process[i] = count(order.begin(), order.begin() + i + 1, order[i]);
    }

    for (int i = 0; i < m * n; ++i) {
        int max_t = (process[i] == 1) ? 0 : *max_element(end_time.begin(), end_time.begin() + i, [&](int a, int b) {
            return (order[&a - &end_time[0]] == order[i]) ? a < b : true;
        });

        int machine_id = machine[order[i] - 1][process[i] - 1];
        int job_time = time[order[i] - 1][process[i] - 1];

        bool can_start_at_max_t = true;
        for (int j = 0; j < i; ++j) {
            if (machine[order[j] - 1][process[j] - 1] == machine_id) {
                if (!(begin_time[j] >= max_t + job_time || end_time[j] <= max_t)) {
                    can_start_at_max_t = false;
                    break;
                }
            }
        }

        if (can_start_at_max_t) {
            begin_time[i] = max_t;
        } else {
            begin_time[i] = *min_element(end_time.begin(), end_time.begin() + i, [&](int a, int b) {
                if (machine[order[&a - &end_time[0]] - 1][process[&a - &end_time[0]] - 1] != machine_id || a < max_t) return false;
                for (int k = 0; k < i; ++k) {
                    if (machine[order[k] - 1][process[k] - 1] == machine_id) {
                        if (!(a + job_time <= begin_time[k] || a >= end_time[k])) {
                            return false;
                        }
                    }
                }
                return true;
            });
        }

        end_time[i] = begin_time[i] + job_time;
    }

    int ans = *max_element(end_time.begin(), end_time.end());
    cout << ans << endl;

    return 0;
}
