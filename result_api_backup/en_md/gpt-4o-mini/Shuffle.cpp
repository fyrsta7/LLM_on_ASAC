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
    int last_departure_time = 0;

    for (int i = 0; i < n; ) {
        // Find the next time we can pick students
        if (last_departure_time < t[i]) {
            last_departure_time = t[i];
        }
        
        // Departure time is set to the last_departure_time
        int departure_time = last_departure_time;

        while (i < n && t[i] <= departure_time) {
            total_waiting_time += departure_time - t[i];
            ++i;
        }
        
        last_departure_time += m;
    }
    
    cout << total_waiting_time << endl;
    return 0;
}