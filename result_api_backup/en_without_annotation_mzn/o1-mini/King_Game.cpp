#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    int n;
    ll a, b;
    cin >> n >> a >> b;
    vector<pair<ll, ll>> minister(n);
    for(int i=0;i<n;i++) cin >> minister[i].first >> minister[i].second;
    // Initialize order with indices 0 to n
    // 0 is fixed, permutation of 1 to n
    vector<int> perm(n);
    for(int i=0;i<n;i++) perm[i]=i+1;
    ll answer = LLONG_MAX;
    do{
        // Calculate money[i]
        ll P = a;
        ll current_max = 0;
        // First element after 0
        for(int i=0;i<n;i++){
            int idx = perm[i]-1;
            ll D = minister[idx].second;
            if(D ==0){
                current_max = LLONG_MAX;
                break;
            }
            ll money = P / D;
            current_max = max(current_max, money);
            P = P * minister[idx].first;
            if(P < 0){
                current_max = LLONG_MAX;
                break;
            }
        }
        answer = min(answer, current_max);
    }while(next_permutation(perm.begin(), perm.end()));
    cout << answer;
}