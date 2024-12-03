#include <bits/stdc++.h>
using namespace std;

int main(){
    int N, I, J;
    cin >> N >> I >> J;
    // Calculate the value at (I,J) in snake pattern
    int ans;
    if(I % 2 == 1){
        ans = (I-1)*N + J;
    }
    else{
        ans = I*N - J +1;
    }
    cout << "ans=" << ans;
}