#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    vector<int> order(m * n);
    vector<vector<int>> machine(n, vector<int>(m));
    vector<vector<int>> time(n, vector<int>(m));

    for (int i = 0; i < m * n; ++i) cin >> order[i];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> machine[i][j];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> time[i][j];

    vector<int> begin_time(m * n, 0);
    vector<int> end_time(m * n, 0);
    vector<int> process(m * n, 0);

    for (int i = 0; i < m * n; ++i) {
        process[i] = count(order.begin(), order.begin() + i + 1, order[i]);
        int max_t = (process[i] == 1) ? 0 : *max_element(end_time.begin(), end_time.begin() + i, [&](int a, int b) {
            return (order[&a - &end_time[0]] == order[i]) ? a < b : true;
        });

        int min_start = max_t;
        for (int j = 0; j < i; ++j) {
            if (machine[order[j]][process[j] - 1] == machine[order[i]][process[i] - 1]) {
                if (end_time[j] > max_t && end_time[j] > min_start) {
                    bool overlap = false;
                    for (int k = 0; k < i; ++k) {
                        if (machine[order[k]][process[k] - 1] == machine[order[i]][process[i] - 1]) {
                            if (!(end_time[j] + time[order[i]][process[i] - 1] <= begin_time[k] || end_time[j] >= end_time[k])) {
                                overlap = true;
                                break;
                            }
                        }
                    }
                    if (!overlap) min_start = end_time[j];
                }
            }
        }

        begin_time[i] = min_start;
        end_time[i] = begin_time[i] + time[order[i]][process[i] - 1];
    }

    int ans = *max_element(end_time.begin(), end_time.end());
    cout << ans << endl;

    return 0;
}
