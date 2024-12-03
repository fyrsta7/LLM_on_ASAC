#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long A, B, L;
    cin >> A >> B >> L;
    long long min_diff = LLONG_MAX;
    long long res_A = 1, res_B = 1;
    for(long long B_s =1; B_s <= L; B_s++){
        // Compute ceil(A * B_s / B)
        long long numerator = A * B_s;
        long long A_s_min = (numerator + B -1) / B;
        if(A_s_min > L) continue;
        for(long long A_s = A_s_min; A_s <= L; A_s++){
            if(__gcd(A_s, B_s) ==1){
                long long diff = A_s * B - A * B_s;
                if(diff < min_diff){
                    min_diff = diff;
                    res_A = A_s;
                    res_B = B_s;
                }
                break;
            }
        }
    }
    cout << res_A << " " << res_B;
}