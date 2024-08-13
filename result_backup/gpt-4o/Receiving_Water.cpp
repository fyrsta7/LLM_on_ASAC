#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> w(n);
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < m; ++i) {
        pq.push(w[i]);
    }

    for (int i = m; i < n; ++i) {
        int current_time = pq.top();
        pq.pop();
        pq.push(current_time + w[i]);
    }

    while (pq.size() > 1) {
        pq.pop();
    }

    cout << pq.top() << endl;
    return 0;
}