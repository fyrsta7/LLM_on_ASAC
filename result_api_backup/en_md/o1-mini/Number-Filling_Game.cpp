#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

typedef long long ll;

const int MOD = 1000000007;

int main(){
    int n, m;
    cin >> n >> m;
    int size = 1 << m;
    vector<ll> dp_prev(size, 1);
    for(int row=1; row<n; row++){
        vector<ll> dp_curr(size, 0);
        for(int s_prev=0; s_prev < size; s_prev++){
            ll count = dp_prev[s_prev];
            if(count ==0) continue;
            // Compute required bits
            int required =0;
            for(int j=0; j < m-1; j++){
                if( (s_prev >> (j+1)) &1 ){
                    required |= (1 <<j);
                }
            }
            // free bits are those not in required
            int free_bits = (~required) & ((1 <<m) -1);
            // Enumerate all subsets of free_bits
            // Using subset enumeration
            int subset = free_bits;
            while(true){
                int s_new = required | subset;
                dp_curr[s_new] = (dp_curr[s_new] + count) % MOD;
                if(subset ==0) break;
                subset = (subset -1) & free_bits;
            }
        }
        dp_prev = dp_curr;
    }
    ll result =0;
    for(auto val: dp_prev){
        result = (result + val) % MOD;
    }
    cout << result;
}