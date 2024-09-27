#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> D(n-1);
    for (int i = 0; i < n-1; ++i) {
        cin >> D[i];
    }

    vector<int> T(m), A(m), B(m);
    for (int i = 0; i < m; ++i) {
        cin >> T[i] >> A[i] >> B[i];
    }

    vector<int> arrive_time(n, 0);
    vector<int> depart_time(n, 0);
    vector<int> save_time(n-1, 0);

    // Initialize depart_time based on the earliest possible departure times
    for (int i = 0; i < m; ++i) {
        depart_time[A[i]-1] = max(depart_time[A[i]-1], T[i]);
    }

    // Calculate arrive_time and depart_time based on constraints
    for (int i = 1; i < n; ++i) {
        arrive_time[i] = max(arrive_time[i-1] + D[i-1], depart_time[i-1]);
        depart_time[i] = max(depart_time[i], arrive_time[i]);
    }

    // Calculate save_time to minimize travel_time
    int total_save_time = 0;
    for (int i = 0; i < n-1; ++i) {
        save_time[i] = max(0, arrive_time[i+1] - depart_time[i] - D[i]);
        total_save_time += save_time[i];
    }

    // Adjust save_time if total_save_time exceeds k
    if (total_save_time > k) {
        int excess_save = total_save_time - k;
        for (int i = 0; i < n-1; ++i) {
            int reduce = min(excess_save, save_time[i]);
            save_time[i] -= reduce;
            excess_save -= reduce;
            if (excess_save == 0) break;
        }
    }

    // Calculate final travel_time
    int travel_time = 0;
    for (int i = 0; i < m; ++i) {
        travel_time += arrive_time[B[i]-1] - T[i];
    }

    cout << travel_time << endl;

    return 0;
}
