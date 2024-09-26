#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    vector<int> a(n);
    for(auto &x: a) cin>>x;
    vector<int> b(n);
    for(auto &x: b) cin>>x;
    // Initialize permutation
    vector<int> p(n);
    for(int i=0;i<n;i++) p[i]=i+1;
    ll min_total = LLONG_MAX;
    // Precompute all permutations
    do{
        // Compute position mapping
        vector<int> pos_p(n+1);
        for(int i=0;i<n;i++) pos_p[p[i]] = i;
        // Map a and b to p's indices
        vector<int> A_p(n), B_p(n);
        for(int i=0;i<n;i++) A_p[i] = pos_p[a[i]];
        for(int i=0;i<n;i++) B_p[i] = pos_p[b[i]];
        // Compute inversions for A_p
        int inv_a =0, inv_b=0;
        for(int i=0;i<n;i++) {
            for(int j=i+1;j<n;j++) if(A_p[i]>A_p[j]) inv_a++;
        }
        // Compute inversions for B_p
        for(int i=0;i<n;i++) {
            for(int j=i+1;j<n;j++) if(B_p[i]>B_p[j]) inv_b++;
        }
        ll total = inv_a + inv_b;
        if(total < min_total){
            min_total = total;
        }
    } while(next_permutation(p.begin(), p.end()));
    cout<< (min_total % 99999997);
}