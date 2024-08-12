#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    int d, n;
    cin >> d >> n;

    vector<pair<int, pair<int, int>>> places(n); // {k, {x, y}}
    for (int i = 0; i < n; ++i) {
        cin >> places[i].second.first >> places[i].second.second >> places[i].first;
    }

    int maxCoverage = 0;
    unordered_map<int, int> coverageCount; // {coverage, schemes}
    
    for (int i = 0; i < n; ++i) {
        int x = places[i].second.first;
        int y = places[i].second.second;
        int coverage = 0;

        for (int j = 0; j < n; ++j) {
            int px = places[j].second.first;
            int py = places[j].second.second;
            int k = places[j].first;

            if (px >= x - d && px <= x + d && py >= y - d && py <= y + d) {
                coverage += k;
            }
        }

        if (coverage > maxCoverage) {
            maxCoverage = coverage;
            coverageCount.clear();
            coverageCount[coverage] = 1;
        } else if (coverage == maxCoverage) {
            coverageCount[coverage]++;
        }
    }

    cout << coverageCount[maxCoverage] << " " << maxCoverage << endl;
    return 0;
}