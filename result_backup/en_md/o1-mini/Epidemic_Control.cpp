#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll INF = 1e18;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<vector<pair<int, ll>>> adj(n+1, vector<pair<int, ll>>());
    for(int i=0;i<n-1;i++){
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    int m;
    cin >> m;
    vector<int> armies(m);
    for(int &x: armies) cin >> x;
    // Multi-source Dijkstra
    vector<ll> D(n+1, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, std::greater<pair<ll, int>>> pq;
    for(int a: armies){
        if(D[a] > 0){
            D[a] = 0;
            pq.emplace(0, a);
        }
    }
    while(!pq.empty()){
        pair<ll, int> current = pq.top(); pq.pop();
        ll dist = current.first;
        int u = current.second;
        if(dist > D[u]) continue;
        for(auto &[v, w]: adj[u]){
            if(D[v] > D[u] + w){
                D[v] = D[u] + w;
                pq.emplace(D[v], v);
            }
        }
    }
    // Binary search
    ll left = 0, right = 50000000000000LL, answer = -1;
    // DFS feasibility check
    auto dfs = [&](auto &dfs_ref, int u, int parent, ll T, const vector<vector<pair<int, ll>>> &adj, const vector<ll> &D, int &count) -> int {
        bool needs_checkpoint = false;
        bool has_child_checkpoint = false;
        for(auto &[v, w]: adj[u]){
            if(v != parent){
                int state = dfs_ref(dfs_ref, v, u, T, adj, D, count);
                if(state == 0){
                    needs_checkpoint = true;
                }
                if(state == 2){
                    has_child_checkpoint = true;
                }
            }
        }
        if(needs_checkpoint){
            if(D[u] <= T){
                count +=1;
                return 2;
            }
            else{
                return 0;
            }
        }
        if(has_child_checkpoint){
            return 1;
        }
        return 0;
    };
    while(left <= right){
        ll mid = left + (right - left)/2;
        int count =0;
        int state = dfs(dfs, 1, -1, mid, adj, D, count);
        // After DFS, check if root needs to be covered
        bool feasible = true;
        if(state == 0){
            feasible = false;
        }
        if(feasible && count <= m){
            answer = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    // Check if answer is feasible
    if(answer == -1){
        // Check if m is sufficient when T is very large
        // Alternatively, if even with T=INF it's not feasible
        // Run DFS with T=INF
        int count =0;
        int state = dfs(dfs, 1, -1, INF, adj, D, count);
        if(state == 0){
            cout << "-1";
            return 0;
        }
        if(count <= m){
            // The minimal T was not found in the binary search, but it's feasible with T=INF
            cout << left;
            return 0;
        }
        else{
            cout << "-1";
            return 0;
        }
    }
    cout << answer;
}