#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxFlowers(vector<int>& heights) {
    vector<int> up, down;
    for (int h : heights) {
        if (up.empty() || h > up.back()) {
            up.push_back(h);
        } else {
            auto it = lower_bound(up.begin(), up.end(), h);
            *it = h;
        }
        
        if (down.empty() || h < down.back()) {
            down.push_back(h);
        } else {
            auto it = lower_bound(down.begin(), down.end(), h, greater<int>());
            *it = h;
        }
    }
    return max(up.size(), down.size());
}

int main() {
    int n;
    cin >> n;
    vector<int> heights(n);
    for (int i = 0; i < n; ++i) {
        cin >> heights[i];
    }
    cout << maxFlowers(heights) << endl;
    return 0;
}