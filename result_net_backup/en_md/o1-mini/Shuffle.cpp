#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> t(n);
    
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }

    sort(t.begin(), t.end());
    
    int total_waiting_time = 0;
    int current_time = 0;
    
    for (int i = 0; i < n; ) {
        int next_bus_time = max(current_time, t[i]);
        int count = 0;
        
        while (i + count < n && t[i + count] <= next_bus_time) {
            count++;
        }
        
        for (int j = i; j < i + count; j++) {
            total_waiting_time += next_bus_time - t[j];
        }
        
        current_time = next_bus_time + m;
        i += count;
    }

    cout << total_waiting_time << endl;
    
    return 0;
}