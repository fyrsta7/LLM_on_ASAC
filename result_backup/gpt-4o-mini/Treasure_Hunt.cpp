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
    int currentFloor = 0;
    int currentRoom = startRoom;

    while (currentFloor < N) {
        key = (key + building[currentFloor][currentRoom].second) % 20123;

        int stairsCounter = 0;
        for (int i = 0; i < M; ++i) {
            int roomIndex = (currentRoom - i + M) % M;
            if (building[currentFloor][roomIndex].first == 1) {
                stairsCounter++;
            }
            if (stairsCounter == building[currentFloor][currentRoom].second) {
                currentRoom = roomIndex;
                break;
            }
        }

        currentFloor++;
    }
    
    cout << key << endl;
    return 0;
}