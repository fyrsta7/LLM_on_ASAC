#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, M;
    cin >> N >> M;
    vector<tuple<int, int, int>> conflicts(M);
    int a, b, c;
    int max_c = 0;
    for(int i=0;i<M;i++){
        cin >> a >> b >> c;
        conflicts[i] = make_tuple(a, b, c);
        if(c > max_c) max_c = c;
    }
    auto is_bipartite = [&](int t) -> bool {
        vector<vector<int>> adj(N+1, vector<int>());
        for(auto &[u, v, w] : conflicts){
            if(w > t){
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
        }
        vector<int> color(N+1, -1);
        for(int u=1; u<=N; u++) {
            if(color[u]==-1){
                queue<int> q;
                q.push(u);
                color[u] = 0;
                while(!q.empty()){
                    int v = q.front(); q.pop();
                    for(auto &nei : adj[v]){
                        if(color[nei]==-1){
                            color[nei] = color[v]^1;
                            q.push(nei);
                        }
                        else if(color[nei] == color[v]){
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    };
    int left=0, right=max_c, answer=max_c;
    while(left <= right){
        int mid = left + (right - left)/2;
        if(is_bipartite(mid)){
            answer = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    cout << answer;
}