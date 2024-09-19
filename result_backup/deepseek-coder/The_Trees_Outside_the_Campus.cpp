#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int l, m;
    cin >> l >> m;
    vector<pair<int, int>> regions(m);
    for (int i = 0; i < m; ++i) {
        cin >> regions[i].first >> regions[i].second;
    }
    
    sort(regions.begin(), regions.end());
    
    int removedTrees = 0;
    int currentStart = regions[0].first;
    int currentEnd = regions[0].second;
    
    for (int i = 1; i < m; ++i) {
        if (regions[i].first <= currentEnd) {
            currentEnd = max(currentEnd, regions[i].second);
        } else {
            removedTrees += currentEnd - currentStart + 1;
            currentStart = regions[i].first;
            currentEnd = regions[i].second;
        }
    }
    
    removedTrees += currentEnd - currentStart + 1;
    
    int remainingTrees = l + 1 - removedTrees;
    cout << remainingTrees << endl;
    
    return 0;
}
