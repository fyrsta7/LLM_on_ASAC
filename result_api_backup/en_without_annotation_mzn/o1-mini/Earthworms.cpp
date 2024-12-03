#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll N, M, Q, u, v, t;
    cin >> N >> M >> Q >> u >> v >> t;
    vector<ll> A(N);
    for(auto &x:A) cin >> x;
    priority_queue<ll> pq;
    for(auto x:A) pq.emplace(x);
    vector<ll> ans1(M / t, 0);
    ll Q_increment = 0;
    for(ll m =0; m < M; m++){
        if(pq.empty()){
            // Handle empty queue if necessary
            break;
        }
        ll top = pq.top() + Q_increment;
        pq.pop();
        ll val0 = (top * u) / v;
        ll val1 = top - val0;
        pq.emplace(val0 - Q_increment);
        pq.emplace(val1 - Q_increment);
        if((m +1) % t ==0){
            ans1[(m +1)/t -1] = val0;
        }
        Q_increment += Q;
    }
    // Collect all elements
    vector<ll> finalS;
    finalS.reserve(N + M);
    while(!pq.empty()){
        finalS.emplace_back(pq.top() + Q_increment);
        pq.pop();
    }
    sort(finalS.begin(), finalS.end(), greater<ll>());
    // Output ans1
    for(ll i=0;i<ans1.size();i++){
        if(i>0) cout << ' ';
        cout << ans1[i];
    }
    cout << '\n';
    // Output finalS
    for(ll i=0;i<finalS.size();i++){
        if(i>0) cout << ' ';
        cout << finalS[i];
    }
}