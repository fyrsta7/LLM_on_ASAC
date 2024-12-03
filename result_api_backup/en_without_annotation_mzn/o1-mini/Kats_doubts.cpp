#include <bits/stdc++.h>
using namespace std;

int main(){
    int a, b;
    cin >> a >> b;
    if(__gcd(a, b) != 1){
        // According to the constraints, a and b must be coprime
    }
    int max_ans = 2000;
    int ans = 0;
    for(int x = max_ans; x >=1; x--){
        bool can = false;
        for(int num_a = 0; num_a * a <= x; num_a++){
            if( (x - num_a * a) % b == 0 ){
                can = true;
                break;
            }
        }
        if(!can){
            ans = x;
            break;
        }
    }
    cout << ans;
}