#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> color(n);
    vector<int> number(n);
    for (int i = 0; i < n; ++i) {
        cin >> color[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> number[i];
    }

    long long total = 0;
    unordered_map<int, vector<int>> color_indices;
    for (int i = 0; i < n; ++i) {
        color_indices[color[i]].push_back(i);
    }

    for (const auto& [col, indices] : color_indices) {
        int sz = indices.size();
        for (int i = 0; i < sz; ++i) {
            for (int j = i + 1; j < sz; ++j) {
                for (int k = j + 1; k < sz; ++k) {
                    if (indices[k] - indices[j] == indices[j] - indices[i]) {
                        total += (indices[i] + indices[k]) * (number[indices[i]] + number[indices[k]]);
                    }
                }
            }
        }
    }

    int res = total % 10007;
    cout << res << endl;

    return 0;
}