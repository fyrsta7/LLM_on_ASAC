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
        int max_t = (process[i] == 1) ? 0 : *max_element(end_time.begin(), end_time.begin() + i,
            [&](int a, int b) { return order[&a - &end_time[0]] == order[i] ? a < b : true; });

        int machine_id = machine[order[i] - 1][process[i] - 1];
        int job_time = time[order[i] - 1][process[i] - 1];

        auto overlap_check = [&](int j) {
            return machine[order[j] - 1][process[j] - 1] == machine_id &&
                   !((begin_time[j] >= max_t + job_time) || (end_time[j] <= max_t));
        };

        if (all_of(begin_time.begin(), begin_time.begin() + i, [&](int b) {
            return machine[order[&b - &begin_time[0]] - 1][process[&b - &begin_time[0]] - 1] != machine_id ||
                   (b >= max_t + job_time) || (end_time[&b - &begin_time[0]] <= max_t);
        })) {
            begin_time[i] = max_t;
        } else {
            begin_time[i] = *min_element(end_time.begin(), end_time.begin() + i, [&](int a, int b) {
                return machine[order[&a - &end_time[0]] - 1][process[&a - &end_time[0]] - 1] == machine_id &&
                       a >= max_t &&
                       all_of(begin_time.begin(), begin_time.begin() + i, [&](int b) {
                           return machine[order[&b - &begin_time[0]] - 1][process[&b - &begin_time[0]] - 1] != machine_id ||
                                  (b >= a + job_time) || (end_time[&b - &begin_time[0]] <= a);
                       }) ? a < b : false;
            });
        }

        end_time[i] = begin_time[i] + job_time;
    }

    int ans = *max_element(end_time.begin(), end_time.end());
    cout << ans << endl;

    return 0;
}
