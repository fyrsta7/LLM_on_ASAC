#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int N;
int beads[20];
ll memo_cache[(1<<20)];
bool computed[(1<<20)];

int N_MAX = 20;
ll dp(int mask) {
    if(mask == 0){
        return 0;
    }
    if(computed[mask]){
        return memo_cache[mask];
    }
    ll max_sum = 0;
    for(int j=0; j<N; j++){
        if(mask & (1<<j)){
            // Find left neighbor
            int left = (j -1 + N) % N;
            while(left != j && !(mask & (1<<left))){
                left = (left -1 + N) % N;
            }
            // Find right neighbor
            int right = (j +1) % N;
            while(right != j && !(mask & (1<<right))){
                right = (right +1) % N;
            }
            // If only one bead is left
            if(left == j && right == j){
                // According to the problem, steps are for i in 1..N-1, so we won't add anything
                continue;
            }
            ll product = (ll)beads[j] * beads[left] * beads[right];
            int new_mask = mask ^ (1<<j);
            ll total = product + dp(new_mask);
            if(total > max_sum){
                max_sum = total;
            }
        }
    }
    memo_cache[mask] = max_sum;
    computed[mask] = true;
    return max_sum;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N;
    for(int i=0;i<N;i++) cin>>beads[i];
    memset(computed, 0, sizeof(computed));
    int full_mask = (1<<N) -1;
    ll ans = dp(full_mask);
    cout << ans;
}