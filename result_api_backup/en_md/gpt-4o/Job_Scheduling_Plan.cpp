#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int m, n;
    cin >> m >> n;

    vector<int> schedule(n * m);
    for (int i = 0; i < n * m; ++i) {
        cin >> schedule[i];
    }

    vector<vector<int>> machineUsage(n, vector<int>(m));
    vector<vector<int>> processingTime(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> machineUsage[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> processingTime[i][j];
        }
    }

    vector<int> machineEndTime(m + 1, 0);
    vector<int> workpieceEndTime(n + 1, 0);

    for (int op : schedule) {
        int workpiece = op - 1;
        int process = 0;
        while (process < m && machineUsage[workpiece][process] == op) {
            ++process;
        }
        int machine = machineUsage[workpiece][process - 1];
        int start = max(machineEndTime[machine], workpieceEndTime[workpiece]);
        int finish = start + processingTime[workpiece][process - 1];
        machineEndTime[machine] = finish;
        workpieceEndTime[workpiece] = finish;
    }
    
    int totalTime = *max_element(machineEndTime.begin(), machineEndTime.end());
    cout << totalTime << endl;

    return 0;
}