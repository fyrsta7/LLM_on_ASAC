#include <iostream>
#include <vector>
using namespace std;

struct Room {
    int has_stairs;
    int x;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, M;
    cin >> N >> M;
    vector<Room> floors;
    floors.reserve(N * M);
    for(int i=0;i<N*M;i++){
        int a, b;
        cin >> a >> b;
        floors.push_back(Room{a, b});
    }
    int c;
    cin >> c;
    long long sum = 0;
    for(int floor=0; floor<N; floor++){
        int idx = floor * M + c;
        int has_stairs = floors[idx].has_stairs;
        int x = floors[idx].x;
        sum = (sum + x) % 20123;
        // Collect rooms with stairs starting from c
        vector<int> list;
        for(int k=0; k<M; k++){
            int room = (c + k) % M;
            if(floors[floor*M + room].has_stairs){
                list.push_back(room);
            }
        }
        if(list.empty()){
            // No stairs, cannot proceed
            break;
        }
        int K = list.size();
        int target = (x - 1) % K;
        c = list[target];
    }
    cout << sum;
}