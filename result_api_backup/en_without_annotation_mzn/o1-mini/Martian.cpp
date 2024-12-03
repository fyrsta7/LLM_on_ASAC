#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    ll M;
    cin >> N >> M;
    vector<int> init_finger(N);
    for(auto &x: init_finger) cin >> x;
    // Compute factorial
    vector<ll> fact(N+1,1);
    for(int i=1;i<=N;i++) fact[i]=fact[i-1]*i;
    // Compute rank
    vector<int> elements;
    for(int i=1;i<=N;i++) elements.push_back(i);
    // Sort in descending order
    sort(elements.begin(), elements.end(), greater<int>());
    ll rank =0;
    for(int i=0;i<N;i++){
        int pos = find(elements.begin(), elements.end(), init_finger[i]) - elements.begin();
        rank += pos * fact[N-1-i];
        elements.erase(elements.begin()+pos);
    }
    // New rank
    ll new_rank = rank + M;
    // Assuming new_rank < fact[N]
    // Generate permutation at new_rank
    elements.clear();
    for(int i=1;i<=N;i++) elements.push_back(i);
    sort(elements.begin(), elements.end(), greater<int>());
    vector<int> result;
    for(int i=0;i<N;i++){
        ll f = fact[N-1-i];
        int idx = new_rank / f;
        new_rank %= f;
        result.push_back(elements[idx]);
        elements.erase(elements.begin()+idx);
    }
    for(int i=0;i<N;i++) cout << result[i] << (i<N-1?" ":"\n");
}