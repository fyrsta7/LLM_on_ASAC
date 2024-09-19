#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

const int MOD = 10007;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> numbers(n);
    vector<int> colors(n);
    for (int i = 0; i < n; ++i) cin >> numbers[i];
    for (int i = 0; i < n; ++i) cin >> colors[i];

    unordered_map<int, vector<int>> color_positions;
    for (int i = 0; i < n; ++i) {
        color_positions[colors[i]].push_back(i);
    }

    int total_score = 0;
    for (const auto& pair : color_positions) {
        const vector<int>& positions = pair.second;
        int size = positions.size();
        for (int i = 0; i < size; ++i) {
            for (int j = i + 1; j < size; ++j) {
                int x = positions[i];
                int z = positions[j];
                if ((z - x) % 2 == 0) {
                    int y = (x + z) / 2;
                    if (y > x && y < z && colors[y] == colors[x]) {
                        int score = (x + z) * (numbers[x] + numbers[z]) % MOD;
                        total_score = (total_score + score) % MOD;
                    }
                }
            }
        }
    }

    cout << total_score << endl;
    return 0;
}
