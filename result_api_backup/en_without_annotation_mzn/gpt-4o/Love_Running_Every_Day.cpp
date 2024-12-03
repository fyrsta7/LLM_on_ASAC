#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Edge {
    int u, v;
};

struct Player {
    int start, end;
};

int n, m;
vector<Edge> roads;
vector<int> watchers;
vector<Player> players;

struct Node {
    int location, route_index, time;
    bool operator<(const Node& other) const {
        return time > other.time;
    }
};

vector<vector<int>> adj;
vector<int> dijkstra(int start) {
    vector<int> dist(n, INT_MAX);
    priority_queue<Node> pq;
    pq.push({start, -1, 0});
    dist[start] = 0;
    
    while (!pq.empty()) {
        Node current = pq.top(); pq.pop();
        
        if (current.time > dist[current.location]) continue;
        
        for (int neighbor : adj[current.location]) {
            Edge road = roads[neighbor];
            int next_location = (road.u == current.location) ? road.v : road.u;
            int next_time = current.time + 1;
            if (next_time < dist[next_location]) {
                dist[next_location] = next_time;
                pq.push({next_location, neighbor, next_time});
            }
        }
    }
    
    return dist;
}

vector<int> get_watch_counts(const vector<vector<int>>& dists) {
    vector<int> watch_counts(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int watch_time = watchers[i];
            if (watch_time < dists[j][i]) continue;
            if (players[j].end == i) continue;
            watch_counts[i]++;
        }
    }
    return watch_counts;
}

int main() {
    cin >> n >> m;
    roads.resize(n-1);
    adj.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        cin >> roads[i].u >> roads[i].v;
        adj[roads[i].u - 1].push_back(i);
        adj[roads[i].v - 1].push_back(i);
    }
    watchers.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> watchers[i];
    }
    players.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> players[i].start >> players[i].end;
        players[i].start--;
        players[i].end--;
    }
    
    vector<vector<int>> dists(m);
    for (int i = 0; i < m; ++i) {
        dists[i] = dijkstra(players[i].start);
    }
    
    vector<int> watch_counts = get_watch_counts(dists);
    for (int count : watch_counts) {
        cout << count << " ";
    }
    cout << endl;
    
    return 0;
}