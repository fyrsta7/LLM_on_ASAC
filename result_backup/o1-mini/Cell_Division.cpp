#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    int m1, m2;
    cin >> m1 >> m2;
    // Factorize m1
    vector<pair<int, int>> factors;
    int x = m1;
    for(int p=2; p*p <=x; p++){
        if(x%p ==0){
            int cnt=0;
            while(x%p ==0){
                cnt++;
                x /=p;
            }
            factors.emplace_back(make_pair(p, cnt));
        }
    }
    if(x >1){
        factors.emplace_back(make_pair(x,1));
    }
    // Now M = m1^m2, so exponents multiplied by m2
    int K = factors.size();
    // Read S_i and process
    ll min_t = 1e18;
    for(int i=0;i<N;i++){
        ll S;
        cin >> S;
        bool possible = true;
        ll current_t = 0;
        ll temp = S;
        vector<int> f(K, 0);
        for(int j=0; j<K; j++){
            int p = factors[j].first;
            while(temp % p ==0){
                f[j]++;
                temp /=p;
            }
        }
        for(int j=0; j<K; j++){
            if(f[j]==0){
                possible = false;
                break;
            }
            ll required = (ll)factors[j].second * m2;
            ll t_j = (required + f[j] -1) / f[j];
            if(t_j > current_t){
                current_t = t_j;
            }
        }
        if(possible){
            if(current_t < min_t){
                min_t = current_t;
            }
        }
    }
    // Check M=1 case
    if(m1 ==1){
        min_t =0;
    }
    if(min_t ==1e18){
        cout << "-1";
    }
    else{
        cout << min_t;
    }
}