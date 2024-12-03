#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>
#include <cstring>
using namespace std;

struct RejectionMask {
    unsigned long long mask1;
    unsigned long long mask2;
} ;

struct State {
    unsigned long long distance;
    int country;
    unsigned long long learned_mask1;
    unsigned long long learned_mask2;
    unsigned long long rejection_mask1;
    unsigned long long rejection_mask2;

    bool operator<(const State& other) const {
        return distance > other.distance;
    }
};

struct Key {
    int country;
    unsigned long long learned_mask1;
    unsigned long long learned_mask2;

    bool operator==(const Key& other) const {
        return country == other.country && learned_mask1 == other.learned_mask1 && learned_mask2 == other.learned_mask2;
    }
};

struct KeyHash {
    size_t operator()(const Key& key) const {
        return hash<int>()(key.country) ^ (hash<unsigned long long>()(key.learned_mask1) << 1) ^ (hash<unsigned long long>()(key.learned_mask2) << 2);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, K, M, S, T;
    cin >> N >> K >> M >> S >> T;
    vector<int> C(N+1);
    for(int i=1;i<=N;i++) cin >> C[i];
    vector<RejectionMask> reject_masks(K+1, RejectionMask{0,0});
    for(int i=1;i<=K;i++){
        for(int j=1;j<=K;j++){
            int a;
            cin >> a;
            if(a){
                if(j-1 < 64){
                    reject_masks[i].mask1 |= (1ULL << (j-1));
                }
                else{
                    reject_masks[i].mask2 |= (1ULL << (j-1-64));
                }
            }
        }
    }
    vector<vector<pair<int, int>>> adj(N+1, vector<pair<int, int>>());
    for(int i=0;i<M;i++){
        int u, v, d;
        cin >> u >> v >> d;
        adj[u].emplace_back(v, d);
        adj[v].emplace_back(u, d);
    }
    // Initialize initial state
    int start_culture = C[S];
    unsigned long long initial_learned1 = 0, initial_learned2 = 0;
    unsigned long long initial_reject1 = reject_masks[start_culture].mask1;
    unsigned long long initial_reject2 = reject_masks[start_culture].mask2;
    if(start_culture-1 < 64){
        initial_learned1 |= (1ULL << (start_culture-1));
    }
    else{
        initial_learned2 |= (1ULL << (start_culture-1-64));
    }
    State initial_state = State{0, S, initial_learned1, initial_learned2, initial_reject1, initial_reject2};
    priority_queue<State> pq;
    pq.push(initial_state);
    unordered_map<Key, bool, KeyHash> visited_map;
    while(!pq.empty()){
        State current = pq.top(); pq.pop();
        if(current.country == T){
            cout << current.distance;
            return 0;
        }
        Key key = Key{current.country, current.learned_mask1, current.learned_mask2};
        if(visited_map.find(key) != visited_map.end()) continue;
        visited_map[key] = true;
        for(auto &[next_country, road_distance] : adj[current.country]){
            int c_next = C[next_country];
            bool in_learned, in_reject;
            if(c_next-1 < 64){
                in_learned = (current.learned_mask1 & (1ULL << (c_next-1))) != 0;
                in_reject = (current.rejection_mask1 & (1ULL << (c_next-1))) != 0;
            }
            else{
                int bit = c_next-1-64;
                in_learned = (current.learned_mask2 & (1ULL << bit)) != 0;
                in_reject = (current.rejection_mask2 & (1ULL << bit)) != 0;
            }
            if(in_learned || in_reject) continue;
            // Create new masks
            unsigned long long new_learned1 = current.learned_mask1;
            unsigned long long new_learned2 = current.learned_mask2;
            if(c_next-1 < 64){
                new_learned1 |= (1ULL << (c_next-1));
            }
            else{
                new_learned2 |= (1ULL << (c_next-1-64));
            }
            unsigned long long new_reject1 = current.rejection_mask1 | reject_masks[c_next].mask1;
            unsigned long long new_reject2 = current.rejection_mask2 | reject_masks[c_next].mask2;
            // Check if the new culture is being rejected by already learned cultures
            // Not needed because rejection is already handled in in_reject
            // Create new state
            State new_state;
            new_state.distance = current.distance + road_distance;
            new_state.country = next_country;
            new_state.learned_mask1 = new_learned1;
            new_state.learned_mask2 = new_learned2;
            new_state.rejection_mask1 = new_reject1;
            new_state.rejection_mask2 = new_reject2;
            Key new_key = Key{new_state.country, new_state.learned_mask1, new_state.learned_mask2};
            if(visited_map.find(new_key) == visited_map.end()){
                pq.push(new_state);
            }
        }
    }
    cout << "-1";
} 