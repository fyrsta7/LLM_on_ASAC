#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll N, NA, NB;
    cin >> N >> NA >> NB;
    vector<int> loopA(NA);
    for(auto &x: loopA) cin >> x;
    vector<int> loopB(NB);
    for(auto &x: loopB) cin >> x;
    int table[5][5] = {
        {0,1,2,2,1},
        {2,0,1,2,1},
        {1,2,0,1,2},
        {1,1,2,0,2},
        {2,2,1,1,0}
    };
    ll gcd_val = gcd(NA, NB);
    ll LCM = (NA / gcd_val) * NB;
    ll cycles = N / LCM;
    ll remaining = N % LCM;
    // Compute scoreA_cycle and scoreB_cycle
    ll scoreA_cycle = 0, scoreB_cycle = 0;
    for(ll i=0;i<LCM;i++){
        int a = loopA[i % NA];
        int b = loopB[i % NB];
        if(table[a][b] == 2) scoreA_cycle++;
        if(table[b][a] == 2) scoreB_cycle++;
    }
    // Compute scoreA_remaining and scoreB_remaining
    ll scoreA_remaining = 0, scoreB_remaining = 0;
    for(ll i=0;i<remaining;i++){
        int a = loopA[i % NA];
        int b = loopB[i % NB];
        if(table[a][b] == 2) scoreA_remaining++;
        if(table[b][a] == 2) scoreB_remaining++;
    }
    ll scoreA = cycles * scoreA_cycle + scoreA_remaining;
    ll scoreB = cycles * scoreB_cycle + scoreB_remaining;
    cout << scoreA << " " << scoreB;
}