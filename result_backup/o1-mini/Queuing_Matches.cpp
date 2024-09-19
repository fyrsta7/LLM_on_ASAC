#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

typedef long long ll;

const int MOD = 100000000 - 3;

// BIT implementation for inversion count
struct BIT {
    int size;
    vector<int> tree;
    BIT(int n){
        size = n;
        tree.assign(n+2, 0);
    }
    void update(int idx){
        while(idx <= size){
            tree[idx]++;
            idx += idx & -idx;
        }
    }
    ll query(int idx){
        ll res =0;
        while(idx >0){
            res += tree[idx];
            idx -= idx & -idx;
        }
        return res;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    vector<ll> a(n), b(n);
    for(auto &x:a) cin>>x;
    for(auto &x:b) cin>>x;
    vector<ll> sorteda = a;
    sort(sorteda.begin(), sorteda.end());
    vector<ll> sortb = b;
    sort(sortb.begin(), sortb.end());
    if(sorteda == sortb){
        // Map element to index in b
        unordered_map<ll, int> elem_to_b;
        for(int i=0;i<n;i++) elem_to_b[b[i]] = i+1;
        // Create mapped a
        vector<int> a_mapped(n);
        for(int i=0;i<n;i++) a_mapped[i] = elem_to_b[a[i]];
        // Count inversions for a to b
        BIT bit1(n);
        ll inv_a_to_b=0;
        for(int i=n-1;i>=0;i--){
            inv_a_to_b += bit1.query(a_mapped[i]-1);
            bit1.update(a_mapped[i]);
            if(inv_a_to_b >= MOD) inv_a_to_b %= MOD;
        }
        // Map element to index in a
        unordered_map<ll, int> elem_to_a;
        for(int i=0;i<n;i++) elem_to_a[a[i]] = i+1;
        // Create mapped b
        vector<int> b_mapped(n);
        for(int i=0;i<n;i++) b_mapped[i] = elem_to_a[b[i]];
        // Count inversions for b to a
        BIT bit2(n);
        ll inv_b_to_a=0;
        for(int i=n-1;i>=0;i--){
            inv_b_to_a += bit2.query(b_mapped[i]-1);
            bit2.update(b_mapped[i]);
            if(inv_b_to_a >= MOD) inv_b_to_a %= MOD;
        }
        // Take minimum
        ll answer = min(inv_a_to_b, inv_b_to_a) % MOD;
        cout<<answer;
    }
    else{
        // Sort a to sorteda
        // Map sorteda element to index
        unordered_map<ll, int> elem_to_sorteda;
        for(int i=0;i<n;i++) elem_to_sorteda[sorteda[i]] = i+1;
        // Create mapped a
        vector<int> a_sorted_mapped(n);
        for(int i=0;i<n;i++) a_sorted_mapped[i] = elem_to_sorteda[a[i]];
        // Count inversions for a to sorteda
        BIT bit_a(n);
        ll inv_a =0;
        for(int i=n-1;i>=0;i--){
            inv_a += bit_a.query(a_sorted_mapped[i]-1);
            bit_a.update(a_sorted_mapped[i]);
            if(inv_a >= MOD) inv_a %= MOD;
        }
        // Sort b to sortb
        unordered_map<ll, int> elem_to_sortb;
        for(int i=0;i<n;i++) elem_to_sortb[sortb[i]] = i+1;
        // Create mapped b
        vector<int> b_sorted_mapped(n);
        for(int i=0;i<n;i++) b_sorted_mapped[i] = elem_to_sortb[b[i]];
        // Count inversions for b to sortb
        BIT bit_b(n);
        ll inv_b_swap=0;
        for(int i=n-1;i>=0;i--){
            inv_b_swap += bit_b.query(b_sorted_mapped[i]-1);
            bit_b.update(b_sorted_mapped[i]);
            if(inv_b_swap >= MOD) inv_b_swap %= MOD;
        }
        // Answer is max(inv_a, inv_b_swap) modulo MOD
        ll answer = max(inv_a, inv_b_swap) % MOD;
        cout<<answer;
    }
}