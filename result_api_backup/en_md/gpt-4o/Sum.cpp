#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Square {
    int number;
    int color;
};

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<Square> squares(n);
    for (int i = 0; i < n; ++i) {
        cin >> squares[i].number;
    }
    for (int i = 0; i < n; ++i) {
        cin >> squares[i].color;
    }
    
    unordered_map<int, vector<int>> color_positions;
    for (int i = 0; i < n; ++i) {
        color_positions[squares[i].color].push_back(i);
    }
    
    const int MOD = 10007;
    int score = 0;
    
    for (const auto& pair : color_positions) {
        const vector<int>& positions = pair.second;
        int size = positions.size();
        for (int i = 0; i < size; ++i) {
            for (int j = i + 1; j < size; ++j) {
                int x = positions[i];
                int z = positions[j];
                int y = (x + z) / 2;
                if ((z - x) % 2 == 0 && squares[x].color == squares[z].color && y > x && y < z && squares[y].color == squares[x].color) {
                    int value = (x + 1 + z + 1) * (squares[x].number + squares[z].number) % MOD;
                    score = (score + value) % MOD;
                }
            }
        }
    }
    
    cout << score << endl;
    return 0;
}
