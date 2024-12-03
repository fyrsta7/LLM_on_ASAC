#include <iostream>
#include <cmath>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    long long N;
    cin >> N;
    long long sqrtN = sqrt((double)N);
    long long factor = -1;
    for(long long i=2; i<=sqrtN; ++i){
        if(N % i == 0){
            factor = i;
            break;
        }
    }
    if(factor == -1){
        // N is prime, but problem states N is product of two different primes
        // So this should not happen
        cout << N;
    }
    else{
        long long other = N / factor;
        if(other > factor){
            cout << other;
        }
        else{
            cout << factor;
        }
    }
}