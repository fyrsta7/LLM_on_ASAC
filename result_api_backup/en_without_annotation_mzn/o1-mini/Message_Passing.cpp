#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<int> T(N+1);
    for(int i=1;i<=N;i++) cin >> T[i];
    vector<bool> visited(N+1, false);
    int min_cycle = N+1;
    for(int i=1;i<=N;i++){
        if(!visited[i]){
            unordered_map<int, int> pos;
            int current = i;
            int step =0;
            while(!visited[current]){
                visited[current]=true;
                pos[current]=step;
                current = T[current];
                step++;
            }
            if(pos.find(current)!=pos.end()){
                int cycle_length = step - pos[current];
                min_cycle = min(min_cycle, cycle_length);
            }
        }
    }
    cout << "turns=" << (min_cycle <= N ? min_cycle : 0);
}