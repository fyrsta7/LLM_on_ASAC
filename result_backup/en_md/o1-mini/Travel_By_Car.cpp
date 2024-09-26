#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

struct JumpInfo {
    int next_city;
    long long sum_A;
    long long sum_B;
} jump_info[20][2][100001];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<long long> h(n+1);
    for(int i=1;i<=n;i++) cin>>h[i];
    
    // Compute next_A and next_B
    vector<int> next_A(n+1, 0);
    vector<int> next_B(n+1, 0);
    set<pair<long long, int>> s_hj; // sorted by h[j], then j
    
    for(int s = n; s >=1; s--){
        long long current_h = h[s];
        pair<long long, int> key = {current_h, s};
        // Find lower and upper
        auto it = s_hj.lower_bound({current_h, -1});
        vector<pair<long long, int>> candidates;
        if(it != s_hj.end()){
            candidates.emplace_back(*it);
        }
        if(it != s_hj.begin()){
            it--;
            candidates.emplace_back(*it);
        }
        // Sort candidates by distance, then by h[j]
        sort(candidates.begin(), candidates.end(), [&](const pair<long long, int> &a, const pair<long long, int> &b) -> bool{
            long long d1 = abs(a.first - current_h);
            long long d2 = abs(b.first - current_h);
            if(d1 != d2) return d1 < d2;
            return a.first < b.first;
        });
        if(candidates.size() >=1){
            next_B[s] = candidates[0].second;
        }
        if(candidates.size() >=2){
            next_A[s] = candidates[1].second;
        }
        // Insert current city
        s_hj.emplace(current_h, s);
    }
    
    // Initialize jump[0][t][s]
    for(int s=1;s<=n;s++){
        if(next_A[s]!=0){
            jump_info[0][0][s].next_city = next_A[s];
            jump_info[0][0][s].sum_A = abs(h[s] - h[next_A[s]]);
            jump_info[0][0][s].sum_B = 0;
        }
        else{
            jump_info[0][0][s].next_city = 0;
            jump_info[0][0][s].sum_A = 0;
            jump_info[0][0][s].sum_B = 0;
        }
        if(next_B[s]!=0){
            jump_info[0][1][s].next_city = next_B[s];
            jump_info[0][1][s].sum_A = 0;
            jump_info[0][1][s].sum_B = abs(h[s] - h[next_B[s]]);
        }
        else{
            jump_info[0][1][s].next_city = 0;
            jump_info[0][1][s].sum_A = 0;
            jump_info[0][1][s].sum_B = 0;
        }
    }
    
    // Precompute jump tables
    int MAX_LOG = 20;
    for(int k=1;k<MAX_LOG;k++){
        for(int t=0;t<2;t++){
            for(int s=1;s<=n;s++){
                JumpInfo first = jump_info[k-1][t][s];
                if(first.next_city ==0){
                    jump_info[k][t][s].next_city =0;
                    jump_info[k][t][s].sum_A =0;
                    jump_info[k][t][s].sum_B =0;
                }
                else{
                    int t_next;
                    if(k-1 ==0) t_next =1-t;
                    else t_next = t;
                    JumpInfo second = jump_info[k-1][t_next][first.next_city];
                    jump_info[k][t][s].next_city = second.next_city;
                    jump_info[k][t][s].sum_A = first.sum_A + second.sum_A;
                    jump_info[k][t][s].sum_B = first.sum_B + second.sum_B;
                }
            }
        }
    }
    
    // Read x0
    long long x0;
    cin >> x0;
    
    // Function to simulate
    auto simulate = [&](int s, long long x) -> pair<long long, long long> {
        int current = s;
        long long sumA =0, sumB =0;
        long long rem =x;
        int t =0; // 0 for A, 1 for B
        for(int k=MAX_LOG-1;k>=0;k--){
            if(jump_info[k][t][current].next_city ==0) continue;
            long long total = jump_info[k][t][current].sum_A + jump_info[k][t][current].sum_B;
            if(total <= rem){
                sumA += jump_info[k][t][current].sum_A;
                sumB += jump_info[k][t][current].sum_B;
                rem -= total;
                current = jump_info[k][t][current].next_city;
                if(k==0){
                    t =1-t;
                }
            }
        }
        return {sumA, sumB};
    };
    
    // Simulate for all s with x0
    vector<long long> sumA(n+1, 0);
    vector<long long> sumB(n+1, 0);
    for(int s=1;s<=n;s++){
        pair<long long, long long> res = simulate(s, x0);
        sumA[s] = res.first;
        sumB[s] = res.second;
    }
    
    // Find s0 with minimum ratio A/B
    // Handle B=0 as infinity
    // In case of tie, choose s with highest h[s]
    int s0=0;
    long long best_A=0, best_B=1; // Initialize to ratio 0/1
    bool first = true;
    for(int s=1;s<=n;s++){
        if(sumB[s] ==0){
            if(best_B !=0){
                // Current best is finite, skip
                continue;
            }
            else{
                // Both inf, choose the one with higher h
                if(first || h[s] > h[s0]){
                    s0 =s;
                }
            }
        }
        else{
            if(best_B ==0){
                // best is inf, current is finite
                best_A = sumA[s];
                best_B = sumB[s];
                s0 =s;
            }
            else{
                // Compare sumA[s]/sumB[s] with best_A/best_B
                long long lhs = sumA[s] * best_B;
                long long rhs = best_A * sumB[s];
                if(lhs < rhs){
                    best_A = sumA[s];
                    best_B = sumB[s];
                    s0 =s;
                }
                else if(lhs == rhs){
                    if(h[s] > h[s0]){
                        s0 =s;
                    }
                }
            }
        }
        first =false;
    }
    if(s0 ==0){
        // All have B[s]=0, choose the one with highest h[s]
        for(int s=1;s<=n;s++) if(s0 ==0 || h[s] > h[s0]) s0 =s;
    }
    cout << s0 << "\n";
    
    // Read m
    int m;
    cin >> m;
    while(m--){
        int s_i;
        long long x_i;
        cin >> s_i >> x_i;
        pair<long long, long long> res = simulate(s_i, x_i);
        cout << res.first << " " << res.second << "\n";
    }
}