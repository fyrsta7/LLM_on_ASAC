#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MOD = 10007;

vector<int> adj[200001];
int weight[200001];
bool visited[200001];

int main() {
    int n;
    cin >> n;
    
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    for(int i = 1; i <= n; i++) {
        cin >> weight[i];
    }
    
    long long max_joint_weight = 0;
    long long sum_joint_weight = 0;
    
    for(int i = 1; i <= n; i++) {
        fill(visited, visited + n + 1, false);
        queue<pair<int, int>> q;
        q.push({i, 0});
        visited[i] = true;
        
        while(!q.empty()) {
            int node = q.front().first;
            int dist = q.front().second;
            q.pop();

            if(dist == 2) {
                long long joint_weight = weight[i] * weight[node];
                max_joint_weight = max(max_joint_weight, joint_weight);
                sum_joint_weight = (sum_joint_weight + joint_weight) % MOD;
            }
            
            if(dist < 2) {
                for(int neighbor : adj[node]) {
                    if(!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push({neighbor, dist + 1});
                    }
                }
            }              
        }
    }
    
    cout << max_joint_weight << " " << sum_joint_weight << endl;
    return 0;
}