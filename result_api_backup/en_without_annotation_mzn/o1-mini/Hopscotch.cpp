#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct SegmentTree {
    int n;
    vector<ll> tree;
    SegmentTree(int size){
        n = 1;
        while(n < size) n <<=1;
        tree.assign(2*n, LLONG_MIN);
    }
    void update(int pos, ll val){
        pos +=n;
        tree[pos] = max(tree[pos], val);
        pos >>=1;
        while(pos >=1){
            tree[pos] = max(tree[2*pos], tree[2*pos+1]);
            pos >>=1;
        }
    }
    ll query(int l, int r){
        l +=n;
        r +=n;
        ll res = LLONG_MIN;
        while(l <= r){
            if(l%2 ==1){
                res = max(res, tree[l++]);
            }
            if(r%2 ==0){
                res = max(res, tree[r--]);
            }
            l >>=1;
            r >>=1;
        }
        return res;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    ll d, k;
    cin >> n >> d >> k;
    vector<pair<ll, ll>> points(n);
    for(int i=0;i<n;i++) cin >> points[i].first;
    for(int i=0;i<n;i++) cin >> points[i].second;
    sort(points.begin(), points.end());
    vector<ll> X(n), S(n);
    for(int i=0;i<n;i++){ X[i]=points[i].first; S[i]=points[i].second;}
    ll left=0, right=1000000000;
    auto possible = [&](ll g) -> bool{
        SegmentTree st(n);
        ll max_sum =0;
        for(int i=0;i<n;i++){
            ll current = LLONG_MIN;
            if(abs(X[i]-d) <=g){
                current = max(current, (ll)S[i]);
            }
            // Find j where X[j] >= X[i]-d-g and X[j] <= X[i]-d+g
            ll low = X[i] - d - g;
            ll high = X[i] - d + g;
            int L = lower_bound(X.begin(), X.end(), low) - X.begin();
            int R = upper_bound(X.begin(), X.end(), high) - X.begin()-1;
            if(L <= R){
                ll prev_max = st.query(L, R);
                if(prev_max != LLONG_MIN){
                    current = max(current, prev_max + (ll)S[i]);
                }
            }
            if(current != LLONG_MIN){
                // Update max_sum
                max_sum = max(max_sum, current);
                // Update segment tree
                st.update(i, current);
            }
        }
        return max_sum >=k;
    };
    while(left < right){
        ll mid = left + (right - left)/2;
        if(possible(mid)) right = mid;
        else left = mid +1;
    }
    cout << left;
}