#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    int n, m, q, u, v, t;
    cin >> n >> m >> q >> u >> v >> t;

    // Calculate p = u / v
    double p = static_cast<double>(u) / v;

    vector<int> worms(n);
    priority_queue<int> wormQueue;

    for (int i = 0; i < n; ++i) {
        cin >> worms[i];
        wormQueue.push(worms[i]);
    }

    vector<int> cutLengths;
    for (int second = 1; second <= m; ++second) {
        int cutWorm = wormQueue.top();
        wormQueue.pop();
        cutLengths.push_back(cutWorm);
        
        int newWorm1 = static_cast<int>(p * cutWorm);
        int newWorm2 = cutWorm - newWorm1;

        if (newWorm1 > 0) wormQueue.push(newWorm1);
        if (newWorm2 > 0) wormQueue.push(newWorm2);
        
        for (int i = 0; i < wormQueue.size(); ++i) {
            wormQueue.push(wormQueue.top() + q);
            wormQueue.pop();
        }

        if (second % t == 0) {
            if (second / t > 1) {
                cout << " ";
            }
            cout << cutWorm;
        }
    }
    cout << endl;

    vector<int> finalWorms;
    while (!wormQueue.empty()) {
        finalWorms.push_back(wormQueue.top());
        wormQueue.pop();
    }
    
    reverse(finalWorms.begin(), finalWorms.end());

    for (int i = 0; i < finalWorms.size(); ++i) {
        if (i % t == 0 && i > 0) {
            cout << " ";
        }
        cout << finalWorms[i];
    }
    cout << endl;

    return 0;
}