#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Task {
    int order;
    int machine;
    int time;
    int begin_time;
    int end_time;
    int process;
};

vector<int> calculateProcess(const vector<int>& order, int m, int n) {
    vector<int> process(m * n);
    for (int i = 0; i < m * n; ++i) {
        process[i] = count(order.begin(), order.begin() + i + 1, order[i]);
    }
    return process;
}

vector<int> calculateEndTimes(const vector<int>& order, const vector<int>& process, const vector<vector<int>>& time) {
    vector<int> end_time(order.size());
    for (size_t i = 0; i < order.size(); ++i) {
        end_time[i] = time[order[i] - 1][process[i] - 1];
    }
    return end_time;
}

bool no_overlap(int begin1, int end1, int begin2, int end2) {
    return begin1 >= end2 || begin2 >= end1;
}

int main() {
    int m, n;
    cin >> m >> n;
    
    vector<int> order(m * n);
    for (int i = 0; i < m * n; ++i) cin >> order[i];
    
    vector<vector<int>> machine(n, vector<int>(m));
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> machine[i][j];
    
    vector<vector<int>> time(n, vector<int>(m));
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> time[i][j];
    
    vector<int> begin_time(m * n, 0);
    vector<int> end_time(m * n, 0);
    vector<int> process = calculateProcess(order, m, n);
    end_time = calculateEndTimes(order, process, time);
    
    for (int i = 0; i < m * n; ++i) {
        int max_t = process[i] == 1 ? 0 : *max_element(end_time.begin(), end_time.begin() + i);
        
        bool overlap = false;
        for (int j = 0; j < i; ++j) {
            if (machine[order[j] - 1][process[j] - 1] == machine[order[i] - 1][process[i] - 1] &&
                !no_overlap(begin_time[j], end_time[j], max_t, max_t + end_time[i])) {
                overlap = true;
                break;
            }
        }
        
        if (!overlap) {
            begin_time[i] = max_t;
        } else {
            vector<int> candidates;
            for (int j = 0; j < i; ++j) {
                if (machine[order[j] - 1][process[j] - 1] == machine[order[i] - 1][process[i] - 1] &&
                    end_time[j] >= max_t) {
                    bool valid = true;
                    for (int k = 0; k < i; ++k) {
                        if (machine[order[k] - 1][process[k] - 1] == machine[order[i] - 1][process[i] - 1] &&
                            !no_overlap(end_time[j], end_time[j] + end_time[i], begin_time[k], end_time[k])) {
                            valid = false;
                            break;
                        }
                    }
                    if (valid) {
                        candidates.push_back(end_time[j]);
                    }
                }
            }
            if (!candidates.empty()) {
                begin_time[i] = *min_element(candidates.begin(), candidates.end());
            }
        }
        
        end_time[i] = begin_time[i] + end_time[i];
    }
    
    int ans = *max_element(end_time.begin(), end_time.end());
    cout << ans << endl;
    
    return 0;
}