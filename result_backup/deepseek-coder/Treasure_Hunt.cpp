#include <iostream>
#include <vector>
using namespace std;

const int MOD = 20123;

int main() {
    int N, M;
    cin >> N >> M;
    vector<vector<pair<int, int>>> floors(N, vector<pair<int, int>>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> floors[i][j].first >> floors[i][j].second;
        }
    }
    int startRoom;
    cin >> startRoom;

    int key = 0;
    for (int i = 0; i < N; ++i) {
        key = (key + floors[i][startRoom].second) % MOD;
        int stairsCount = 0;
        int target = floors[i][startRoom].second % M;
        for (int j = 0; j < M; ++j) {
            int room = (startRoom + j) % M;
            if (floors[i][room].first == 1) {
                stairsCount++;
                if (stairsCount == target + 1) {
                    startRoom = room;
                    break;
                }
            }
        }
    }
    cout << key << endl;
    return 0;
}
