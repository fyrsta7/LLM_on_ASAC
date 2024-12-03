#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Pair {
    int u;
    int v;
    int bond;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    // Read bond matrix
    // bond[i][j] for i < j
    vector<vector<int>> bond(N, vector<int>());
    for(int i=0;i<N;i++){
        for(int j=i+1;j<N;j++){
            int val;
            cin >> val;
            bond[i].push_back(val);
        }
    }
    // Collect all pairs
    vector<Pair> pairs;
    for(int i=0;i<N;i++){
        for(int j=0;j<bond[i].size();j++){
            pairs.push_back(Pair{ i, i+1+j, bond[i][j] });
        }
    }
    // Sort all pairs descendingly by bond
    sort(pairs.begin(), pairs.end(), [&](const Pair &a, const Pair &b) -> bool{
        return a.bond > b.bond;
    });
    // Binary search over possible L
    int left = 0, right = 1000000000, answer = -1;
    int k = N/2;
    while(left <= right){
        int mid = left + (right - left)/2;
        // Collect all pairs with bond >= mid
        vector<Pair> high_pairs;
        for(auto &p: pairs){
            if(p.bond >= mid){
                high_pairs.push_back(p);
            }
            else{
                break;
            }
        }
        if(high_pairs.empty()){
            // No pairs with bond >= mid, cannot have L >= mid
            right = mid -1;
            continue;
        }
        // Initialize counts
        vector<int> counts(N, 0);
        for(auto &p: high_pairs){
            counts[p.u]++;
            counts[p.v]++;
        }
        // Greedy hitting set
        int hits =0;
        vector<bool> removed_pairs(high_pairs.size(), false);
        vector<bool> blocked(N, false);
        while(true){
            // Find the general with max count
            int max_count = -1, selected = -1;
            for(int i=0;i<N;i++) {
                if(!blocked[i] && counts[i] > max_count){
                    max_count = counts[i];
                    selected = i;
                }
            }
            if(max_count <=0){
                break;
            }
            hits++;
            if(hits > k){
                break;
            }
            // Block this general
            blocked[selected] = true;
            // Remove all pairs involving this general
            for(int idx=0; idx<high_pairs.size(); idx++){
                if(!removed_pairs[idx]){
                    if(high_pairs[idx].u == selected || high_pairs[idx].v == selected){
                        removed_pairs[idx] = true;
                        counts[high_pairs[idx].u]--;
                        counts[high_pairs[idx].v]--;
                    }
                }
            }
        }
        if(hits > k){
            // Computer cannot block all pairs, Xiao Han can have bond >=mid
            answer = mid;
            left = mid +1;
        }
        else{
            // Computer can block all pairs with bond >=mid
            right = mid -1;
        }
    }
    if(answer == -1){
        cout << "0\n";
    }
    else{
        cout << "1\n" << answer;
    }
}