#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    long long total = 0;
    int m = 1;
    while(true){
        long long start_i = (long long)(m-1)*m/2 +1;
        if(start_i > n) break;
        long long end_i = min( (long long)m*(m+1)/2, (long long)n );
        long long cnt = end_i - start_i +1;
        total += m * cnt;
        m++;
    }
    cout << total;
}