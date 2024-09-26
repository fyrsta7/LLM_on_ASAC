#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, M;
    cin >> N >> M;
    vector<vector<int>> stairs(N, vector<int>(M));
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            cin >> stairs[i][j];
        }
    }
    vector<vector<int>> number(N, vector<int>(M));
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            cin >> number[i][j];
        }
    }
    int p;
    cin >> p;
    // Initialize code[1] = p +1
    int current = p +1;
    ll answer = 0;
    for(int i=0;i<N;i++){
        // Add number[i][current-1]
        answer += number[i][current-1];
        // Mod is applied at the end
        if(i == N-1) break;
        // go_up for next
        // Get room_with_stairs
        vector<int> room_with_stairs;
        for(int j=0;j<M;j++) if(stairs[i][j]==1) room_with_stairs.push_back(j+1);
        int K = room_with_stairs.size();
        // Find minimal distance
        // room_with_stairs is sorted
        // Use lower_bound to find the first >= current
        int d;
        if(K ==0){
            // Undefined, but assume it's not happening
            d = M;
        }
        else{
            int pos = lower_bound(room_with_stairs.begin(), room_with_stairs.end(), current) - room_with_stairs.begin();
            int dist1, dist2;
            if(pos < K){
                dist1 = room_with_stairs[pos] - current;
            }
            else{
                dist1 = room_with_stairs[0] + M - current;
            }
            if(pos >0){
                dist2 = current - room_with_stairs[pos-1];
            }
            else{
                dist2 = current + M - room_with_stairs[K-1];
            }
            d = min(dist1, dist2);
        }
        // Compute begin = round_next(current, d, M)
        int begin;
        if(current + d <= M){
            begin = current + d;
        }
        else{
            begin = ((current + d -1) % M) +1;
        }
        // Find begin_loc in room_with_stairs
        // room_with_stairs is sorted
        int begin_loc = lower_bound(room_with_stairs.begin(), room_with_stairs.end(), begin) - room_with_stairs.begin();
        // Compute next_loc = round_next(begin_loc +1, number[i][current-1] -1, K)
        // Note: round_next for indices from 1 to K
        int d_steps = number[i][current-1] -1;
        int next_loc;
        if((begin_loc +1) + d_steps <= K){
            next_loc = (begin_loc +1) + d_steps;
        }
        else{
            next_loc = ((begin_loc +1 + d_steps -1) % K) +1;
        }
        current = room_with_stairs[next_loc-1];
    }
    cout << (int)(answer % 20123);
}