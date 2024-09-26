#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

int find_min_turns(int N, const vector<int>& T) {
    unordered_map<int, int> visited;
    queue<pair<int, int>> q;
    
    auto enqueue = [&](int y, int t) {
        if (!visited.count(y)) {
            visited[y] = t;
            q.push({y, t});
        }
    };
    
    int x = 1;  // Assuming 'x' is the starting point
    enqueue(x, 0);
    
    while (!q.empty()) {
        int current = q.front().first;
        int turns = q.front().second;
        q.pop();
        
        if (current == x && turns > 0) {
            return turns;
        }
        
        for (int i = 0; i < N; ++i) {
            enqueue(T[current-1], turns + 1);
        }
    }
    return -1;
}

int main() {
    int N;
    cin >> N;
    vector<int> T(N);
    for (int i = 0; i < N; ++i) {
        cin >> T[i];
    }

    int result = find_min_turns(N, T);
    if (result != -1) {
        cout << "turns=" << result << endl;
    } else {
        cout << "No solution found" << endl;
    }
    return 0;
}