#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

typedef long long ll;

ll compute_max_distance(ll t, ll M){
    // Compute k_max
    ll k = (4*t + M)/14;
    while(k > 0){
        ll needed_mana = 10*k - M;
        ll r;
        if(needed_mana <=0){
            r =0;
        }
        else{
            r = (needed_mana +3)/4;
        }
        if(k + r <= t){
            break;
        }
        k--;
    }
    if(k <0) k=0;
    ll needed_mana = 10*k - M;
    ll r;
    if(needed_mana <=0){
        r =0;
    }
    else{
        r = (needed_mana +3)/4;
    }
    ll t_remain = t -k -r;
    if(t_remain <0) t_remain=0;
    ll distance = 60*k + 17*t_remain;
    return distance;
}

int main(){
    ll M, S, T;
    cin >> M >> S >> T;
    // Binary search for minimal t
    ll low=0, high=T, answer=-1;
    while(low <= high){
        ll mid = low + (high - low)/2;
        ll dist = compute_max_distance(mid, M);
        if(dist >= S){
            answer = mid;
            high = mid -1;
        }
        else{
            low = mid +1;
        }
    }
    if(answer != -1 && answer <= T){
        cout << "Yes\n" << answer;
    }
    else{
        ll max_dist = compute_max_distance(T, M);
        cout << "No\n" << max_dist;
    }
}