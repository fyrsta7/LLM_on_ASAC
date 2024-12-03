#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 1e9;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> p(n+1);
    for(int i=1;i<=n;i++) cin >> p[i];
    vector<vector<int>> adj(n+1, vector<int>());
    vector<pair<int,int>> roads(n-1);
    set<pair<int,int>> road_set;
    for(int i=0;i<n-1;i++){
        cin >> roads[i].first >> roads[i].second;
        adj[roads[i].first].push_back(roads[i].second);
        adj[roads[i].second].push_back(roads[i].first);
        int u = roads[i].first, v = roads[i].second;
        if(u > v) swap(u, v);
        road_set.emplace(u, v);
    }
    struct Request {
        int u, a, v, b;
    };
    vector<Request> requests(m);
    for(int i=0;i<m;i++) cin >> requests[i].u >> requests[i].a >> requests[i].v >> requests[i].b;
    // Function to compute minimal vertex cover with constraints
    // fixed[j] = -1 means must be in cover
    // fixed[j] = 0 means must not be in cover
    // fixed[j] = -2 means no constraint
    auto compute_vc = [&](const Request &req) -> int{
        int u = req.u, a = req.a, v = req.v, b = req.b;
        // Initialize fixed array
        vector<int> fixed(n+1, -2);
        if(a != -1){
            if(a ==0) fixed[u] =0;
            else fixed[u] =1;
        }
        if(b != -1){
            if(b ==0) fixed[v] =0;
            else fixed[v] =1;
        }
        // DP arrays
        // dp0[u]: min sum if u not in cover
        // dp1[u]: min sum if u is in cover
        // Return minimum of dp0[root] and dp1[root]
        // Choose root as 1
        // To handle disconnected trees, but roads form a tree
        // Implement DFS
        // Use lambda with memoization
        ll res;
        // Initialize
        // If fixed[root] != -2, handle accordingly
        // Implement iterative DFS
        // To simplify, use recursive DFS with limits on n
        // Implement a stack depth of n
        // Implement memoization per request
        // Use memoization within the lambda
        // Alternative: implement global variables inside the lambda
        // Implement recursive DFS
        // Returns pair(dp0, dp1)
        // If impossible, return INF
        function<pair<int, int>(int, int)> dfs = [&](int node, int parent)->pair<int, int>{
            // If node is fixed to be in or not
            bool must_in = false, must_out = false;
            if(fixed[node]==1) {must_in=true;}
            if(fixed[node]==0) {must_out=true;}
            pair<int, int> res_pair;
            if(must_in && must_out){
                // Conflict
                return {INF, INF};
            }
            // If must_in, dp0 is INF
            if(must_in){
                // node must be in cover
                // dp1
                int dp1 = p[node];
                for(auto &child: adj[node]){
                    if(child == parent) continue;
                    pair<int, int> child_res = dfs(child, node);
                    dp1 += min(child_res.first, child_res.second);
                }
                return {INF, dp1};
            }
            if(must_out){
                // node must not be in cover
                // dp0
                int dp0 =0;
                for(auto &child: adj[node]){
                    if(child == parent) continue;
                    pair<int, int> child_res = dfs(child, node);
                    dp0 += child_res.second;
                }
                // dp1
                int dp1 = p[node];
                for(auto &child: adj[node]){
                    if(child == parent) continue;
                    pair<int, int> child_res = dfs(child, node);
                    dp1 += min(child_res.first, child_res.second);
                }
                return {dp0, dp1};
            }
            // No constraint
            // dp0: node not in cover, so all children must be in cover
            int dp0 =0;
            for(auto &child: adj[node]){
                if(child == parent) continue;
                pair<int, int> child_res = dfs(child, node);
                dp0 += child_res.second;
            }
            // dp1: node in cover
            int dp1_val = p[node];
            for(auto &child: adj[node]){
                if(child == parent) continue;
                pair<int, int> child_res = dfs(child, node);
                dp1_val += min(child_res.first, child_res.second);
            }
            return {dp0, dp1_val};
        };
        pair<int, int> total = dfs(1, -1);
        int minimum = min(total.first, total.second);
        if(minimum >= INF) return INF;
        return minimum;
    };
    // Now process each request
    vector<int> scores(m, 0);
    for(int i=0;i<m;i++){
        Request req = requests[i];
        // Check if score[i] can be -1
        if(req.a ==0 && req.b ==0){
            int u = req.u, v = req.v;
            if(u > v) swap(u, v);
            if(road_set.find({u, v}) != road_set.end()){
                scores[i] = -1;
                continue;
            }
        }
        // Else, compute minimal vertex cover with constraints
        int vc = compute_vc(req);
        if(vc >= INF){
            // No solution, but according to constraints, likely always possible
            // Assign a large number
            vc = INF;
        }
        scores[i] = vc;
    }
    // Compute sum
    ll total_sum =0;
    for(int i=0;i<m;i++) total_sum += scores[i];
    // Output as MiniZinc would: show(score), which is the list of scores
    for(int i=0;i<m;i++){
        if(i>0) cout << " ";
        cout << scores[i];
    }
}