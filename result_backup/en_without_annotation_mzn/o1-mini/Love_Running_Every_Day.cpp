#include <bits/stdc++.h>
using namespace std;

struct PlayerPath {
    int time;
    vector<int> path_nodes;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    // roads indexed from 1 to n-1
    vector<pair<int, int>> roads(n-1);
    // Build adjacency list with road indices
    vector<vector<pair<int, int>>> adj(n+1, vector<pair<int, int>>());
    for(int i=1;i<n;i++){
        cin >> roads[i-1].first >> roads[i-1].second;
        adj[roads[i-1].first].emplace_back(roads[i-1].second, i);
        adj[roads[i-1].second].emplace_back(roads[i-1].first, i);
    }
    // Read watcher
    vector<int> watcher(n);
    for(auto &x: watcher) cin >> x;
    // Read players
    vector<pair<int, int>> players(m);
    for(auto &x: players) cin >> x.first >> x.second;
    // Find path for each player
    vector<PlayerPath> player_paths(m);
    for(int i=0;i<m;i++){
        int start = players[i].first;
        int end = players[i].second;
        // BFS to find shortest path
        queue<vector<int>> q;
        vector<bool> visited(n+1, false);
        q.push(vector<int>{start});
        bool found = false;
        while(!q.empty() && !found){
            int size_q = q.size();
            for(int s=0;s<size_q;s++){
                vector<int> path = q.front(); q.pop();
                int last = path.back();
                if(last == end){
                    player_paths[i].time = path.size()-1;
                    player_paths[i].path_nodes = path;
                    found = true;
                    break;
                }
                for(auto &[neighbor, road_idx]: adj[last]){
                    if(find(path.begin(), path.end(), neighbor) == path.end()){
                        vector<int> new_path = path;
                        new_path.push_back(neighbor);
                        q.push(new_path);
                    }
                }
            }
        }
        if(!found){
            // No path found, set time to n
            player_paths[i].time = n;
            player_paths[i].path_nodes = {start};
        }
    }
    // For each player, build location at each time
    // location[j][t] where t from 0 to time[j]
    vector<vector<int>> locations(m, vector<int>());
    for(int i=0;i<m;i++){
        locations[i].push_back(players[i].first);
        for(int t=1;t<=player_paths[i].time;t++){
            locations[i].push_back(player_paths[i].path_nodes[t]);
        }
    }
    // Compute watch_num
    vector<int> watch_num(n, 0);
    for(int i=1;i<=n;i++){
        int t = watcher[i-1];
        for(int j=0;j<m;j++){
            if(t <= player_paths[j].time){
                if(locations[j][t] == i){
                    watch_num[i-1]++;
                }
            }
        }
    }
    // Output watch_num
    for(int i=0;i<n;i++){
        if(i>0) cout << " ";
        cout << watch_num[i];
    }
}