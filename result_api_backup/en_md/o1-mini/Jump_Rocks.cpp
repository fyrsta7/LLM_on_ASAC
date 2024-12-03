#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll L, N, M;
    cin >> L >> N >> M;
    vector<ll> rocks;
    rocks.push_back(0);
    for(int i=0;i<N;i++){
        ll d;
        cin >> d;
        rocks.push_back(d);
    }
    rocks.push_back(L);
    sort(rocks.begin(), rocks.end());
    ll left =1, right = L, answer=0;
    while(left <= right){
        ll mid = left + (right - left)/2;
        ll last = 0;
        int removed =0;
        for(int i=1;i<rocks.size();i++){
            if(rocks[i] - last < mid){
                removed++;
            }
            else{
                last = rocks[i];
            }
        }
        if(removed <= M){
            answer = mid;
            left = mid +1;
        }
        else{
            right = mid -1;
        }
    }
    cout << answer;
}