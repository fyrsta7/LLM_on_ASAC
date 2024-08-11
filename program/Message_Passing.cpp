#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> T(n);
    for (int i = 0; i < n; ++i) {
        cin >> T[i];
        T[i]--;  // Convert to 0-based index
    }

    vector<int> inDegree(n, 0);
    for (int i = 0; i < n; ++i) {
        inDegree[T[i]]++;
    }

    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    int rounds = 0;
    while (!q.empty()) {
        int qSize = q.size();
        for (int i = 0; i < qSize; ++i) {
            int curr = q.front();
            q.pop();
            int target = T[curr];
            if (--inDegree[target] == 0) {
                q.push(target);
            }
        }
        rounds++;
    }

    cout << rounds - 1 << endl;
    return 0;
}