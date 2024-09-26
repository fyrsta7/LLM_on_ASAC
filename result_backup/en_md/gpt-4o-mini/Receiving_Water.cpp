#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    
    priority_queue<int, vector<int>, greater<int>> pq;
    
    for (int i = 0; i < m && i < n; i++) {
        pq.push(w[i]);
    }
    
    int time = 0;
    int idx = m;
    
    while (!pq.empty()) {
        time = pq.top();
        pq.pop();
        
        if (idx < n) {
            pq.push(time + w[idx]);
            idx++;
        }
    }
    
    cout << time << endl;
    return 0;
}