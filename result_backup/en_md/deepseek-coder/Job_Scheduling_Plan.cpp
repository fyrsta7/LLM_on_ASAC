#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Operation {
    int workpiece, process, machine, time;
};

int main() {
    int m, n;
    cin >> m >> n;

    vector<int> schedule(m * n);
    for (int i = 0; i < m * n; ++i) {
        cin >> schedule[i];
    }

    vector<vector<int>> machine_order(n, vector<int>(m));
    vector<vector<int>> process_time(n, vector<int>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> machine_order[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> process_time[i][j];
        }
    }

    vector<Operation> operations;
    for (int i = 0; i < m * n; ++i) {
        int workpiece = schedule[i] - 1;
        int process = i % m;
        operations.push_back({workpiece, process, machine_order[workpiece][process] - 1, process_time[workpiece][process]});
    }

    vector<int> machine_time(m, 0);
    vector<int> workpiece_time(n, 0);

    for (const auto& op : operations) {
        int start_time = max(machine_time[op.machine], workpiece_time[op.workpiece]);
        machine_time[op.machine] = start_time + op.time;
        workpiece_time[op.workpiece] = start_time + op.time;
    }

    int total_time = *max_element(machine_time.begin(), machine_time.end());
    cout << total_time << endl;

    return 0;
}
