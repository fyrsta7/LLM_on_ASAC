#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
vector<int> graph[MAXN];
vector<int> reverseGraph[MAXN];
bool reachable[MAXN];
bool visited[MAXN];
int dist[MAXN];

void bfs(int start) {
    queue<int> q;
    q.push(start);
    reachable[start] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : reverseGraph[u]) {
            if (!reachable[v]) {
                reachable[v] = true;
                q.push(v);
            }
        }
    }
}

int bfsShortestPath(int start, int end) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    dist[start] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : graph[u]) {
            if (reachable[v] && !visited[v]) {
                visited[v] = true;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return visited[end] ? dist[end] : -1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        reverseGraph[y].push_back(x);
    }
    int s, t;
    scanf("%d %d", &s, &t);

    bfs(t);
    int result = bfsShortestPath(s, t);
    printf("%d\n", result);

    return 0;
}
