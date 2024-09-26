#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<pair<int,int>> like(n);
    for(auto &p: like) cin >> p.first >> p.second;
    // Function to check if a permutation is a target
    auto is_target = [&](const vector<int> &perm) -> bool{
        for(int i=0;i<n;i++){
            int prev = perm[(i-1+n)%n];
            int next = perm[(i+1)%n];
            if( !((prev == like[perm[i]-1].first && next == like[perm[i]-1].second) ||
                  (prev == like[perm[i]-1].second && next == like[perm[i]-1].first)) ){
                return false;
            }
        }
        return true;
    };
    // Create target permutations
    vector<vector<int>> targets;
    // Generate all possible permutations and filter targets
    // Since n<=8 is manageable
    vector<int> perm(n);
    for(int i=0;i<n;i++) perm[i]=i+1;
    do{
        if(is_target(perm)){
            targets.emplace_back(perm);
        }
    }while(next_permutation(perm.begin(), perm.end()));
    if(targets.empty()){
        cout << -1;
        return 0;
    }
    // BFS with Dijkstra
    // Represent permutation as a string
    auto perm_to_str = [&](const vector<int> &p) -> string{
        string s;
        for(auto x: p) s += to_string(x) + ",";
        return s;
    };
    string start = perm_to_str(perm);
    // Reset perm to identity
    perm.assign(n, 0);
    for(int i=0;i<n;i++) perm[i]=i+1;
    start = perm_to_str(perm);
    // Priority queue: (cost, permutation)
    priority_queue<pair<long long, string>, vector<pair<long long, string>>, std::greater<pair<long long, string>>> pq;
    pq.emplace(0, start);
    unordered_map<string, long long> dist;
    dist[start] = 0;
    // Precompute all possible subsets
    vector<vector<int>> subsets;
    for(int mask=1; mask<(1<<n); mask++){
        int bits = __builtin_popcount(mask);
        if(bits <2) continue;
        vector<int> subset;
        for(int i=0;i<n;i++) if(mask & (1<<i)) subset.push_back(i);
        subsets.emplace_back(subset);
    }
    while(!pq.empty()){
        auto [cost, current] = pq.top(); pq.pop();
        if(dist[current] < cost) continue;
        // Convert current to permutation
        vector<int> curr_perm;
        string num = "";
        for(char c: current){
            if(c == ','){
                if(!num.empty()){
                    curr_perm.push_back(stoi(num));
                    num = "";
                }
            }
            else num += c;
        }
        // Check if current is a target
        bool target_found = false;
        for(auto &t: targets){
            if(curr_perm == t){
                cout << cost;
                return 0;
            }
        }
        // Try all possible shifts
        for(auto &subset: subsets){
            // Perform cyclic shift
            vector<int> new_perm = curr_perm;
            int m = subset.size();
            vector<int> temp(m);
            for(int i=0;i<m;i++) temp[i] = new_perm[subset[i]];
            for(int i=0;i<m;i++) new_perm[subset[i]] = temp[(i-1+m)%m];
            // Convert to string
            string new_str;
            for(auto x: new_perm) new_str += to_string(x) + ",";
            // Calculate new cost
            long long new_cost = cost + m;
            if(!dist.count(new_str) || new_cost < dist[new_str]){
                dist[new_str] = new_cost;
                pq.emplace(new_cost, new_str);
            }
        }
    }
    // If no target found
    cout << -1;
}