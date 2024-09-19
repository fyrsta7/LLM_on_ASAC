#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n+1, vector<int>());
    // To store edges, no duplicates needed
    for(int i=0;i<m;i++){
        int si;
        cin >> si;
        vector<int> S(si);
        for(auto &x:S) cin >> x;
        // Sort S just in case, although input is sorted
        // Not necessary as per problem statement
        // Create a boolean array for presence
        vector<bool> isStop(n+1, false);
        for(auto x:S) isStop[x] = true;
        int origin = S[0];
        int dest = S.back();
        // Iterate y from origin to dest
        for(int y=origin; y<=dest; y++){
            if(!isStop[y]){
                // Find the minimal x in S >= y
                // Since S is sorted, use lower_bound
                int pos = lower_bound(S.begin(), S.end(), y) - S.begin();
                if(pos < S.size()){
                    int x = S[pos];
                    adj[y].push_back(x);
                }
            }
        }
    }
    // Now perform topological sort and find longest path
    vector<int> indegree(n+1, 0);
    for(int y=1;y<=n;y++) {
        for(auto x: adj[y]) {
            indegree[x]++;
        }
    }
    queue<int> q;
    // Initialize levels
    vector<int> level(n+1,1);
    for(int y=1;y<=n;y++) if(indegree[y]==0) q.push(y);
    while(!q.empty()){
        int y = q.front(); q.pop();
        for(auto x: adj[y]){
            if(level[x] < level[y]+1){
                level[x] = level[y]+1;
            }
            indegree[x]--;
            if(indegree[x]==0){
                q.push(x);
            }
        }
    }
    // Find the maximum level
    int max_level = 0;
    for(int y=1;y<=n;y++) if(level[y] > max_level) max_level = level[y];
    cout << max_level;
}