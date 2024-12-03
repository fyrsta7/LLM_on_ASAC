#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const double INF = 1e18;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, v, e;
    cin >> n >> m >> v >> e;
    vector<int> C(n);
    for(auto &x: C) cin >> x;
    vector<int> D(n);
    for(auto &x: D) cin >> x;
    vector<double> K(n);
    for(auto &x: K) cin >> x;
    vector<int> A(e), B(e), W(e);
    for(int i=0;i<e;i++) cin >> A[i];
    for(int i=0;i<e;i++) cin >> B[i];
    for(int i=0;i<e;i++) cin >> W[i];
    // Build graph
    vector<vector<pair<int, int>>> adj(v+1, vector<pair<int,int>>());
    for(int i=0;i<e;i++){
        adj[A[i]].emplace_back(B[i], W[i]);
        adj[B[i]].emplace_back(A[i], W[i]);
    }
    // Function to compute shortest path from S to T
    auto dijkstra = [&](int S, int T) -> double {
        vector<double> dist(v+1, INF);
        priority_queue<pair<double, int>, vector<pair<double, int>>, std::greater<pair<double, int>>> pq;
        dist[S] = 0;
        pq.emplace(0, S);
        while(!pq.empty()){
            auto [d, u] = pq.top(); pq.pop();
            if(u == T) return d;
            if(d > dist[u]) continue;
            for(auto &[v_neigh, w]: adj[u]){
                if(dist[v_neigh] > dist[u] + w){
                    dist[v_neigh] = dist[u] + w;
                    pq.emplace(dist[v_neigh], v_neigh);
                }
            }
        }
        return INF;
    };
    // Precompute all required paths
    vector<double> pcc(n-1, INF), pdc(n-1, INF), pcd(n-1, INF), pdd(n-1, INF);
    for(int i=0;i<n-1;i++){
        pcc[i] = dijkstra(C[i], C[i+1]);
        pdc[i] = dijkstra(D[i], C[i+1]);
        pcd[i] = dijkstra(C[i], D[i+1]);
        pdd[i] = dijkstra(D[i], D[i+1]);
    }
    // Initialize DP
    // DP[i][k][c]: up to i, k changes, c=0/1
    // To save space, use two layers
    vector<vector<double>> prev_dp(m+2, vector<double>(2, INF));
    vector<vector<double>> curr_dp(m+2, vector<double>(2, INF));
    prev_dp[0][0] = 0.0;
    for(int i=1;i<=n;i++){
        for(int k=0;k<=m;k++) {
            for(int c_prev=0;c_prev<=1;c_prev++){
                if(prev_dp[k][c_prev] < INF){
                    for(int c_curr=0;c_curr<=1;c_curr++){
                        if(k + c_curr > m) continue;
                        double add = 0.0;
                        if(i >1){
                            int idx = i-2;
                            double curr_pcc = pcc[idx];
                            double curr_pdc = pdc[idx];
                            double curr_pcd = pcd[idx];
                            double curr_pdd = pdd[idx];
                            double Ki = K[idx];
                            double Ki1 = (i-1 < n) ? K[i-1] : 0.0;
                            // When i-1 is changed (c_prev) and i is changed (c_curr)
                            if(c_prev && c_curr){
                                add += curr_pcc * (1.0 - Ki) * (1.0 - Ki1);
                                add += curr_pdc * Ki * (1.0 - Ki1);
                                add += curr_pcd * Ki1 * (1.0 - Ki);
                                add += curr_pdd * Ki * Ki1;
                            }
                            // If only i-1 is changed
                            else if(c_prev && !c_curr){
                                add += curr_pcc * (1.0 - Ki);
                                add += curr_pdc * Ki;
                            }
                            // If only i is changed
                            else if(!c_prev && c_curr){
                                add += curr_pcc * (1.0 - Ki1);
                                add += curr_pcd * Ki1;
                            }
                            // If neither is changed
                            else{
                                add += curr_pcc;
                            }
                        }
                        // Update current DP
                        double new_val = prev_dp[k][c_prev] + add;
                        if(new_val < curr_dp[k + c_curr][c_curr]){
                            curr_dp[k + c_curr][c_curr] = new_val;
                        }
                    }
                }
            }
        }
        // Reset prev_dp and copy curr_dp to prev_dp
        for(int k=0;k<=m;k++) {
            for(int c=0;c<=1;c++) {
                prev_dp[k][c] = curr_dp[k][c];
                curr_dp[k][c] = INF;
            }
        }
    }
    // Find the minimum obj
    double answer = INF;
    for(int k=0;k<=m;k++) {
        for(int c=0;c<=1;c++) {
            if(prev_dp[k][c] < answer){
                answer = prev_dp[k][c];
            }
        }
    }
    cout << fixed << setprecision(2) << answer << "\n";
}