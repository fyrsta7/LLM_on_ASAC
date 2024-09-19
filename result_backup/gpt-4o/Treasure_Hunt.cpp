#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<pair<int, int>>> building(N, vector<pair<int, int>>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> building[i][j].first >> building[i][j].second;
        }
    }

    int startRoom;
    cin >> startRoom;

    int key = 0;
    int currentRoom = startRoom;

    for (int i = 0; i < N; ++i) {
        key += building[i][currentRoom].second;
        key %= 20123;

        int x = building[i][currentRoom].second;
        int stairsCount = 0;
        for (int j = currentRoom; stairsCount < x; j = (j - 1 + M) % M) {
            if (building[i][j].first == 1) {
                stairsCount++;
                if (stairsCount == x) {
                    currentRoom = j;
                    break;
                }
            }
        }
    }

    cout << key << endl;

    return 0;
}
