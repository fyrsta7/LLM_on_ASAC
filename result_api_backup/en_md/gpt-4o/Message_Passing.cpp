#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> T(n + 1);
    vector<int> indegree(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        cin >> T[i];
        indegree[T[i]]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    int rounds = 0, processed = 0;
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; ++i) {
            int curr = q.front();
            q.pop();
            processed++;
            int target = T[curr];
            if (--indegree[target] == 0) {
                q.push(target);
            }
        }
        rounds++;
    }

    if (processed != n) {
        rounds++;
    }

    cout << rounds << endl;
    return 0;
}