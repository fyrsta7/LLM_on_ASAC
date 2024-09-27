#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> T(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> T[i];
    }

    int x;
    cin >> x;

    unordered_map<int, int> dist;
    queue<int> q;
    q.push(x);
    dist[x] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        int next = T[current];
        if (dist.find(next) == dist.end()) {
            dist[next] = dist[current] + 1;
            q.push(next);
        }
    }

    int turns = dist[x];
    cout << "turns=" << turns << endl;

    return 0;
}