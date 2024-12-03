#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<int> T(N);
    for(auto &x:T) cin >> x;
    // Compute len_dec
    vector<int> len_dec(N, 1);
    vector<int> tails_dec;
    for(int i=0;i<N;i++){
        // For decreasing, use -T[i] to use standard LIS
        int pos = upper_bound(tails_dec.begin(), tails_dec.end(), -T[i]) - tails_dec.begin();
        if(pos == tails_dec.size()) tails_dec.push_back(-T[i]);
        else tails_dec[pos] = -T[i];
        len_dec[i] = pos + 1;
    }
    // Compute len_inc
    vector<int> len_inc(N, 1);
    vector<int> tails_inc;
    for(int i=N-1;i>=0;i--){
        int pos = lower_bound(tails_inc.begin(), tails_inc.end(), T[i]) - tails_inc.begin();
        if(pos == tails_inc.size()) tails_inc.push_back(T[i]);
        else tails_inc[pos] = T[i];
        len_inc[i] = pos + 1;
    }
    // Find maximum keep
    int max_keep = 0;
    for(int i=0;i<N;i++) max_keep = max(max_keep, len_dec[i] + len_inc[i] - 1);
    cout << N - max_keep;
}