#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> T(n+1);
    for(int i=1;i<=n;i++) cin >> T[i];
    vector<bool> visited(n+1, false);
    int min_cycle = n+1;
    for(int u=1; u<=n; u++){
        if(!visited[u]){
            vector<int> path;
            int v = u;
            while(true){
                visited[v] = true;
                path.push_back(v);
                int next_v = T[v];
                if(visited[next_v]){
                    // Check if next_v is in path
                    auto it = find(path.begin(), path.end(), next_v);
                    if(it != path.end()){
                        int cycle_length = path.end() - it;
                        min_cycle = min(min_cycle, cycle_length);
                    }
                    break;
                }
                v = next_v;
            }
        }
    }
    cout << min_cycle;
}