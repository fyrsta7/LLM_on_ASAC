#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<vector<int>> value(N, vector<int>(N));
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) cin >> value[i][j];
    int half = N / 2;
    int best = 0;
    // Iterate over all subsets of size half
    // Use bitmask
    // If N > 20, use combinations instead
    // Here N <=20 is assumed
    // To iterate all combinations, use recursion or next_combination
    // Here use next_combination with bitmask
    // Start with the first half bits set
    if(N > 20){
        // Handle larger N if needed
    }
    else{
        unsigned int mask = (1u << half) - 1;
        unsigned int limit = (1u << N);
        while(mask < limit){
            // Extract S
            vector<int> S;
            for(int i=0;i<N;i++) if(mask & (1u<<i)) S.push_back(i);
            // Simulate opponent selection
            // Initialize free_set as all not in S
            vector<bool> is_S(N, false);
            for(auto x:S) is_S[x] = true;
            vector<int> free_elements;
            for(int i=0;i<N;i++) if(!is_S[i]) free_elements.push_back(i);
            // Opponent selects T step by step
            vector<int> T;
            vector<int> current_S;
            vector<int> current_free = free_elements;
            for(int i=0;i<half;i++){
                current_S.push_back(S[i]);
                // For each k in current_free, find max value over current_S
                int max_val = INT32_MIN;
                int selected = N;
                for(auto k: current_free){
                    int local_max = INT32_MIN;
                    for(auto j: current_S) local_max = max(local_max, value[j][k]);
                    if(local_max > max_val || (local_max == max_val && k < selected)){
                        max_val = local_max;
                        selected = k;
                    }
                }
                if(selected == N) break;
                T.push_back(selected);
                // Remove selected from current_free
                current_free.erase(find(current_free.begin(), current_free.end(), selected));
            }
            if(T.size() != half) { 
                // Invalid selection
            }
            else{
                // Compute my_value
                int my_value = INT32_MIN;
                for(int i=0;i<half;i++) for(int j=0;j<half;j++) my_value = max(my_value, value[S[i]][S[j]]);
                // Compute oppo_value
                int oppo_value = INT32_MIN;
                for(int i=0;i<half;i++) for(int j=0;j<half;j++) oppo_value = max(oppo_value, value[T[i]][T[j]]);
                if(my_value > oppo_value){
                    best = max(best, my_value);
                }
            }
            // Generate next combination
            // Gosper's hack
            unsigned int c = mask & -mask;
            unsigned int r = mask + c;
            unsigned int new_bits = (((mask ^ r) >> 2)/c);
            mask = r | new_bits;
        }
    }
    if(best >0){
        cout << "1\n" << best << "\n";
    }
    else{
        cout << "0\n0\n";
    }
}