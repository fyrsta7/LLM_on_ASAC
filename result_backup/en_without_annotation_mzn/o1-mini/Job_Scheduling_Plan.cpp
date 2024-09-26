#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int m, n;
    cin >> m >> n;
    int mn = m * n;
    vector<int> order(mn);
    for(auto &x: order) cin >> x;
    // machine[j][p]
    // machine[a][b]: a=1..n, b=1..m
    vector<vector<int>> machine(n+1, vector<int>(m+1));
    for(int a=1; a<=n; a++) {
        for(int b=1; b<=m; b++) cin >> machine[a][b];
    }
    // time[j][p]
    vector<vector<int>> time_(n+1, vector<int>(m+1));
    for(int a=1; a<=n; a++) {
        for(int b=1; b<=m; b++) cin >> time_[a][b];
    }
    // process count per job
    vector<int> count_job(m+1, 0);
    // job_ready[job]
    vector<long long> job_ready(m+1, 0);
    // machine_ready[k]
    // Find the maximum machine index
    int max_machine = 0;
    for(int a=1; a<=n; a++) {
        for(int b=1; b<=m; b++) max_machine = max(max_machine, machine[a][b]);
    }
    vector<long long> machine_ready(max_machine+1, 0);
    long long ans = 0;
    for(int i=0; i<mn; i++){
        int job = order[i];
        count_job[job]++;
        int p = count_job[job];
        int m_id = machine[job][p];
        int t = time_[job][p];
        long long start = max(job_ready[job], machine_ready[m_id]);
        long long end = start + t;
        job_ready[job] = end;
        machine_ready[m_id] = end;
        ans = max(ans, end);
    }
    cout << ans;
}