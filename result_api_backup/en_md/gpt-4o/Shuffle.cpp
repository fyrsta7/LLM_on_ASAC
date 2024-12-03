#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> t(n);
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }
    sort(t.begin(), t.end());
    
    int total_waiting_time = 0;
    for (int i = 0; i < n;  ) {
        int current_time = t[i];
        for (; i < n && t[i] < current_time + m; ++i) {
            total_waiting_time += max(0, current_time - t[i]);
        }
    }
    
    cout << total_waiting_time << endl;
    return 0;
}