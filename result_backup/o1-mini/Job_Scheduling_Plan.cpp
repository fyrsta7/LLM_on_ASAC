#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int main(){
    int m, n;
    cin >> m >> n;
    vector<int> schedule(m * n);
    for(int &x: schedule) cin >> x;
    // Read machine numbers
    vector< vector<int> > machines_info(n, vector<int>(m));
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            cin >> machines_info[i][j];
            machines_info[i][j]--; // convert to 0-based
        }
    }
    // Read processing times
    vector< vector<int> > processing_times(n, vector<int>(m));
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            cin >> processing_times[i][j];
        }
    }
    // Initialize machine schedules
    vector< vector<pair<int, int>> > machine_schedules(m, vector<pair<int, int>>());
    // Initialize workpiece finish times
    vector<int> wp_finish(n, 0);
    // Initialize next process to schedule
    vector<int> next_process(n, 0);
    for(int s : schedule){
        int j = s -1;
        int k = next_process[j];
        next_process[j]++;
        if(k >= m){
            // Should not happen as per problem constraints
            continue;
        }
        int machine = machines_info[j][k];
        int p_time = processing_times[j][k];
        int ready_time = wp_finish[j];
        // Find earliest start time on machine
        int start_time = ready_time;
        for(auto &interval : machine_schedules[machine]){
            if(start_time + p_time <= interval.first){
                break;
            }
            if(start_time >= interval.first && start_time < interval.second){
                start_time = interval.second;
            }
            else if(start_time < interval.first && start_time + p_time > interval.first){
                start_time = interval.second;
            }
        }
        // Now check against all intervals
        // To find the first available slot
        int prev_end = 0;
        bool found = false;
        for(auto &interval : machine_schedules[machine]){
            if(start_time + p_time <= interval.first){
                found = true;
                break;
            }
            if(start_time < interval.second){
                start_time = interval.second;
            }
        }
        // If not found in gaps, schedule at current start_time
        // Now insert the interval
        int finish_time = start_time + p_time;
        // Insert while keeping the schedule sorted
        auto &sched = machine_schedules[machine];
        int pos = 0;
        while(pos < sched.size() && sched[pos].first < start_time){
            pos++;
        }
        sched.insert(sched.begin()+pos, make_pair(start_time, finish_time));
        // Update workpiece finish time
        wp_finish[j] = finish_time;
    }
    // Find the maximum finish time
    int makespan = 0;
    for(int t : wp_finish){
        if(t > makespan) makespan = t;
    }
    cout << makespan;
    return 0;
}