#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<int> travel_time(n-1);
    for(int i = 0; i < n-1; ++i) {
        cin >> travel_time[i];
    }

    struct Passenger {
        int T, A, B;
    };

    vector<Passenger> passengers(m);
    for(int i = 0; i < m; ++i) {
        cin >> passengers[i].T >> passengers[i].A >> passengers[i].B;
    }
    
    // Sort passengers based on their arrival time
    sort(passengers.begin(), passengers.end(), [](const Passenger &a, const Passenger &b) {
        return a.T < b.T;
    });
    
    int current_time = 0;
    vector<int> arrival_time(n, 0);  // Time when bus reaches each station
    for(int i = 0; i < n-1; ++i) {
        arrival_time[i+1] = arrival_time[i] + travel_time[i];
    }

    // Use a priority queue to manage usage of the accelerators
    priority_queue<pair<int, int>> pq;
    for(int i = 0; i < n-1; ++i) {
        pq.push({travel_time[i], i});
    }

    while(!pq.empty() && k > 0) {
        auto [time, idx] = pq.top();
        pq.pop();
        if(time > 0) {
            travel_time[idx]--;
            k--;
            pq.push({travel_time[idx], idx});
        }
    }

    vector<int> new_arrival_time(n, 0);
    for(int i = 0; i < n-1; ++i) {
        new_arrival_time[i+1] = new_arrival_time[i] + travel_time[i];
    }

    int total_travel_time = 0;
    for(const auto &passenger : passengers) {
        int wait_time = max(0, new_arrival_time[passenger.A - 1] - passenger.T);
        total_travel_time += wait_time + (new_arrival_time[passenger.B - 1] - new_arrival_time[passenger.A - 1]);
    }

    cout << total_travel_time << endl;
    
    return 0;
}