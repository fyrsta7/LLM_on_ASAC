#include <iostream>
using namespace std;

typedef long long ll;

int main(){
    ll K;
    cin >> K;
    // Binary search to find maximum N where N*(N+1)/2 <= K
    ll left = 0, right = 2e9, N = 0;
    while(left <= right){
        ll mid = left + (right - left)/2;
        ll days = mid*(mid+1)/2;
        if(days <= K){
            N = mid;
            left = mid +1;
        }
        else{
            right = mid -1;
        }
    }
    ll days_in_blocks = N*(N+1)/2;
    ll sum_blocks = N*(N+1)*(2*N+1)/6;
    ll remaining_days = K - days_in_blocks;
    ll total = sum_blocks + (N+1)*remaining_days;
    cout << total;
}