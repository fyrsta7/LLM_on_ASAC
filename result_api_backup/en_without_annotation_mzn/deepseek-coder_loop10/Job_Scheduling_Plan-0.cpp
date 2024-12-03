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
    
    for (int i = 0; i < m * n; ++i) {
        cin >> order[i];
        --order[i]; // Convert to 0-based index
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> machine[i][j];
            --machine[i][j]; // Convert to 0-based index
        }
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> time[i][j];
        }
    }
    
    vector<int> begin_time(m * n, 0);
    vector<int> end_time(m * n, 0);
    vector<int> process(m * n, 0);
    
    vector<int> last_end_time(n, 0);
    vector<vector<int>> machine_end_times(m);
    
    for (int i = 0; i < m * n; ++i) {
        int job = order[i];
        int proc = process[i] = (i == 0) ? 0 : process[i - 1] + (order[i] == order[i - 1] ? 0 : 1);
        
        int max_t = (proc == 0) ? 0 : last_end_time[job];
        int mach = machine[job][proc];
        
        auto& end_times = machine_end_times[mach];
        auto it = upper_bound(end_times.begin(), end_times.end(), max_t);
        
        if (it == end_times.end()) {
            begin_time[i] = max_t;
        } else {
            begin_time[i] = *it;
        }
        
        end_time[i] = begin_time[i] + time[job][proc];
        last_end_time[job] = end_time[i];
        end_times.insert(upper_bound(end_times.begin(), end_times.end(), end_time[i]), end_time[i]);
    }
    
    int ans = *max_element(end_time.begin(), end_time.end());
    cout << ans << endl;
    
    return 0;
}
