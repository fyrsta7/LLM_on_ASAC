#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    
    vector<pair<int, int>> belt(m);
    for (int i = 0; i < m; ++i) {
        cin >> belt[i].first >> belt[i].second;
    }
    
    vector<pair<int, int>> order(q);
    int L = 0;
    for (int i = 0; i < q; ++i) {
        cin >> order[i].first >> order[i].second;
        L = max(L, order[i].second);
    }
    
    vector<vector<int>> adj(n + 1);
    for (const auto& b : belt) {
        adj[b.first].push_back(b.second);
        adj[b.second].push_back(b.first);
    }
    
    vector<vector<int>> produce(q, vector<int>(n + 1, 0));
    
    for (int i = 0; i < q; ++i) {
        int start = order[i].first;
        int time = order[i].second;
        
        queue<pair<int, int>> bfs;
        bfs.push({start, time});
        produce[i][start] = time;
        
        while (!bfs.empty()) {
            auto [node, t] = bfs.front();
            bfs.pop();
            
            if (t == 0) continue;
            
            for (int neighbor : adj[node]) {
                if (produce[i][neighbor] < t - 1) {
                    produce[i][neighbor] = t - 1;
                    bfs.push({neighbor, t - 1});
                }
            }
        }
    }
    
    for (int i = 0; i < q; ++i) {
        cout << (produce[i][1] > 0 ? "YES" : "NO") << endl;
    }
    
    return 0;
}
