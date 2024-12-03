#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int m, n;
    cin >> m >> n;

    vector<int> schedule(6);
    for (int i = 0; i < 6; i++) {
        cin >> schedule[i];
    }

    vector<vector<int>> machines(n, vector<int>(m));
    vector<vector<int>> times(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> machines[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> times[i][j];
        }
    }

    vector<int> finish_time(m + 1, 0); // Holds finish time for each machine
    int total_time = 0; // Total time taken to complete all processes

    for (int i = 0; i < schedule.size(); i++) {
        int workpiece = schedule[i] - 1; // workpiece index
        int process = i % m; // process index within the workpiece

        int machine = machines[workpiece][process]; // Getting machine for the process
        int processing_time = times[workpiece][process]; // Processing time for the process

        // Ensuring the process starts only after both previous process of the same workpiece and
        // the current machine is free.
        finish_time[machine] = max(finish_time[machine], total_time) + processing_time;
        total_time = finish_time[machine]; // Update total time to the latest finish time
    }

    cout << total_time << endl;
    return 0;
}