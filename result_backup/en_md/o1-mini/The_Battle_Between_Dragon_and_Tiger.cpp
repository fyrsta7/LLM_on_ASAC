#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<ll> c(n+1, 0);
    for(int i=1;i<=n;i++) cin >> c[i];
    int m, p1;
    ll s1, s2;
    cin >> m >> p1 >> s1 >> s2;
    ll dragon =0, tiger=0;
    for(int i=1;i<m;i++) dragon += c[i]*(ll)(m -i);
    for(int i=m+1;i<=n;i++) tiger += c[i]*(ll)(i -m);
    if(p1 <m){
        dragon += s1 * (ll)(m - p1);
    }
    else if(p1 >m){
        tiger += s1 * (ll)(p1 - m);
    }
    ll diff = dragon - tiger;
    vector<int> candidates;
    if(diff >0){
        double p_opt = m + ((double)diff)/s2;
        ll floor_p = floor(p_opt);
        ll ceil_p = ceil(p_opt);
        if(floor_p > m && floor_p <=n){
            candidates.push_back((int)floor_p);
        }
        if(ceil_p > m && ceil_p <=n && ceil_p != floor_p){
            candidates.push_back((int)ceil_p);
        }
        if(m+1 <=n){
            candidates.push_back(m+1);
        }
        if(n > m){
            candidates.push_back(n);
        }
    }
    else if(diff <0){
        double p_opt = m + ((double)diff)/s2;
        ll floor_p = floor(p_opt);
        ll ceil_p = ceil(p_opt);
        if(floor_p >=1 && floor_p <m){
            candidates.push_back((int)floor_p);
        }
        if(ceil_p >=1 && ceil_p <m && ceil_p != floor_p){
            candidates.push_back((int)ceil_p);
        }
        if(1 <m){
            candidates.push_back(1);
        }
        if(m-1 >=1){
            candidates.push_back(m-1);
        }
    }
    else{
        candidates.push_back(m);
    }
    // To ensure p2=m is considered when diff !=0
    if(diff !=0){
        candidates.push_back(m);
    }
    // Remove duplicates
    sort(candidates.begin(), candidates.end());
    candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());
    // Now find the best p2
    ll min_abs = LLONG_MAX;
    int answer = n;
    for(auto p2 : candidates){
        ll new_diff = diff;
        if(p2 <m){
            new_diff += s2 * (ll)(m - p2);
        }
        else if(p2 >m){
            new_diff -= s2 * (ll)(p2 - m);
        }
        // if p2 ==m, no change
        ll abs_diff = abs(new_diff);
        if(abs_diff < min_abs){
            min_abs = abs_diff;
            answer = p2;
        }
        else if(abs_diff == min_abs && p2 < answer){
            answer = p2;
        }
    }
    // In case no candidate was added, which shouldn't happen, default to m
    if(candidates.empty()){
        answer = m;
    }
    cout << answer;
}
