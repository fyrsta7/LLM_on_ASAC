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
    
    for (int i = 0; i < m; ++i) {
        depart_time[A[i]-1] = max(depart_time[A[i]-1], T[i]);
    }
    
    for (int i = 1; i < n; ++i) {
        arrive_time[i] = max(arrive_time[i], depart_time[i-1] + D[i-1] - save_time[i-1]);
        depart_time[i] = max(depart_time[i], arrive_time[i]);
    }
    
    int travel_time = 0;
    for (int i = 0; i < m; ++i) {
        travel_time += arrive_time[B[i]-1] - T[i];
    }
    
    cout << travel_time << endl;
    
    return 0;
}
