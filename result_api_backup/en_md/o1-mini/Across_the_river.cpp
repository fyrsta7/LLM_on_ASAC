#include <iostream>
#include <vector>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long L;
    cin >> L;
    int S, T, M;
    cin >> S >> T >> M;
    vector<long long> pebbles(M);
    for(auto &x: pebbles) cin >> x;
    sort(pebbles.begin(), pebbles.end());
    // Use unordered_set for fast lookup
    unordered_set<long long> pebble_set(pebbles.begin(), pebbles.end());
    // BFS with deque for 0-1 BFS
    deque<pair<long long, int>> dq;
    unordered_map<long long, int> visited;
    dq.emplace_back(0, 0);
    visited[0] = 0;
    while(!dq.empty()){
        auto [current, cost] = dq.front();
        dq.pop_front();
        for(int d=S; d<=T; d++){
            long long new_pos = current + d;
            if(new_pos >= L){
                cout << cost;
                return 0;
            }
            int new_cost = cost + (pebble_set.find(new_pos) != pebble_set.end() ? 1 : 0);
            if(visited.find(new_pos) == visited.end() || new_cost < visited[new_pos]){
                visited[new_pos] = new_cost;
                if(pebble_set.find(new_pos) != pebble_set.end()){
                    dq.emplace_back(new_pos, new_cost);
                }
                else{
                    dq.emplace_front(new_pos, new_cost);
                }
            }
        }
    }
    // If not reached by jumps, output M (maximum possible)
    cout << M;
}
