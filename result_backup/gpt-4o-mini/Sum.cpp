#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<int> numbers(n);
    vector<int> colors(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }
    
    for (int i = 0; i < n; ++i) {
        cin >> colors[i];
    }
    
    long long totalScore = 0;
    unordered_map<int, vector<pair<int, int>>> colorMap; // color -> (index, number)

    for (int i = 0; i < n; ++i) {
        colorMap[colors[i]].emplace_back(i + 1, numbers[i]); // store 1-based index and number
    }

    for (const auto& entry : colorMap) {
        const auto& indices = entry.second;
        int size = indices.size();

        for (int j = 0; j < size; ++j) {
            for (int k = j + 1; k < size; ++k) {
                int x = indices[j].first;
                int y = indices[k].first;
                int distance = y - x;
                int z = y + distance;

                if (z > n) break; // z must be within bounds
                if (z <= n && colors[x - 1] == colors[z - 1]) { // check color equality
                    totalScore = (totalScore + (x + z) * (indices[j].second + indices[k].second)) % 10007;
                }
            }
        }
    }

    cout << totalScore << endl;
    return 0;
}