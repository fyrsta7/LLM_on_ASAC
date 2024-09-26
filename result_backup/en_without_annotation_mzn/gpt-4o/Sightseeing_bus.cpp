#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int n, m, k;
vector<int> D, T, A, B;
vector<int> arrive_time, depart_time, save_time;

int main() {
    cin >> n >> m >> k;
    D.resize(n - 1);
    T.resize(m);
    A.resize(m);
    B.resize(m);
    arrive_time.resize(n);
    depart_time.resize(n);
    save_time.resize(n - 1);

    for (int i = 0; i < n - 1; ++i) cin >> D[i];
    for (int i = 0; i < m; ++i) cin >> T[i] >> A[i] >> B[i];

    arrive_time[0] = 0;

    for (int i = 1; i < n; ++i) {
        arrive_time[i] = arrive_time[i - 1] + D[i - 1];
        save_time[i - 1] = max(0, D[i - 1] - (arrive_time[i] - depart_time[i - 1]));
        if (save_time[i - 1] > 0) {
            arrive_time[i] += save_time[i - 1];
        }
        depart_time[i - 1] = arrive_time[i - 1];
    }

    for (int i = 0; i < m; ++i) {
        if (depart_time[A[i] - 1] < T[i]) {
            depart_time[A[i] - 1] = T[i];
        }
    }

    int travel_time = 0;
    for (int i = 0; i < m; ++i) {
        travel_time += (arrive_time[B[i] - 1] - T[i]);
    }

    cout << travel_time << endl;

    return 0;
}