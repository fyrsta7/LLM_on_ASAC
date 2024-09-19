#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    long long A, B, L;
    cin >> A >> B >> L;
    long long min_diff = -1;
    long long resA = 0, resB = 0;
    for(long long Bp =1; Bp <= L; ++Bp){
        // Compute ceil(A * Bp / B)
        long long numerator = A * Bp;
        long long Ap = numerator / B;
        if(numerator % B !=0){
            Ap +=1;
        }
        if(Ap > L){
            continue;
        }
        // Check gcd
        long long g = gcd(Ap, Bp);
        if(g !=1){
            continue;
        }
        // Compute difference: Ap/Bp - A/B = (Ap*B - A*Bp)/(B*Bp)
        long long diff = Ap * B - A * Bp;
        if(diff <0){
            continue;
        }
        if(min_diff == -1 || diff * (resB) * B !=0){
            if(min_diff == -1 || (diff * resB < min_diff * Bp)){
                min_diff = diff;
                resA = Ap;
                resB = Bp;
            }
        }
    }
    cout << resA << " " << resB;
}