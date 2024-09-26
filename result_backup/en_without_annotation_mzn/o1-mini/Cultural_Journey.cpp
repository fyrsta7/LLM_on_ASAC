#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, pair<int, int>> pii;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, K, M, S, T;
    cin >> N >> K >> M >> S >> T;
    vector<int> C(N+1);
    for(int i=1;i<=N;i++) cin >> C[i];
    // Read A
    vector<vector<int>> A(K+1, vector<int>(K+1, 0));
    for(int i=1;i<=K;i++) {
        for(int j=1;j<=K;j++) {
            cin >> A[i][j];
        }
    }
    // Read U, V, D
    vector<int> U(M+1), V(M+1);
    vector<int> D(M+1);
    for(int i=1;i<=M;i++) cin >> U[i] >> V[i] >> D[i];
    // Build adjacency list
    vector<vector<pair<int, int>>> adj(N+1, vector<pair<int, int>>());
    for(int i=1;i<=M;i++){
        adj[U[i]].emplace_back(V[i], D[i]);
        adj[V[i]].emplace_back(U[i], D[i]);
    }
    // Precompute incompatible masks
    vector<int> incompatible(K+1, 0);
    for(int c=1;c<=K;c++){
        for(int c2=1;c2<=K;c2++) {
            if(A[c][c2]) incompatible[c] |= (1 << (c2-1));
        }
    }
    // Priority queue: min-heap based on distance
    priority_queue<pii, vector<pii>, std::greater<pii>> pq;
    // Initial mask
    int start_color = C[S];
    int start_mask = 1 << (start_color-1);
    pq.push({0, {S, start_mask}});
    // Visited array
    int size = 1 << K;
    // To save memory, use vector of bitsets
    // Each node has a bitmask of visited
    // Use vector of vector<uint64_t>
    int words = (size + 63) / 64;
    vector<vector<uint64_t>> visited(N+1, vector<uint64_t>((size + 63)/64, 0));
    // Mark start
    visited[S][start_mask / 64] |= (1ULL << (start_mask % 64));
    while(!pq.empty()){
        auto current = pq.top(); pq.pop();
        ll dist = current.first;
        int u = current.second.first;
        int mask = current.second.second;
        if(u == T){
            cout << "dist=" << dist;
            return 0;
        }
        for(auto &[v, w] : adj[u]){
            int c_new = C[v];
            int bit = 1 << (c_new-1);
            if( (mask & bit) ) continue;
            if( (mask & incompatible[c_new]) ) continue;
            int new_mask = mask | bit;
            int word = new_mask / 64;
            int bit_pos = new_mask % 64;
            if(!(visited[v][word] & (1ULL << bit_pos))){
                visited[v][word] |= (1ULL << bit_pos);
                pq.push({dist + (ll)w, {v, new_mask}});
            }
        }
    }
    cout << "dist=-1";
}