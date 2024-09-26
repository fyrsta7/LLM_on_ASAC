#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<long long> S(n+1);
    for(int i=1;i<=n;i++) cin>>S[i];
    vector<long long> A(n+1);
    for(int i=1;i<=n;i++) cin>>A[i];
    vector<long long> c(n+1, 0);
    for(int i=1;i<=n;i++){
        long long max_c = LLONG_MIN;
        if(i == 1){
            for(int r=1;r<=n;r++) {
                long long current = A[r] + 2 * S[r];
                if(current > max_c) max_c = current;
            }
        }
        else{
            priority_queue<long long, vector<long long>, std::greater<long long>> pq;
            long long sum_top = 0;
            for(int r=1;r<=n;r++){
                if(r >1){
                    pq.push(A[r-1]);
                    sum_top += A[r-1];
                    if((int)pq.size() > i-1){
                        sum_top -= pq.top();
                        pq.pop();
                    }
                }
                if(r >= i){
                    long long current = A[r] + 2 * S[r] + sum_top;
                    if(current > max_c) max_c = current;
                }
            }
        }
        c[i] = max_c;
    }
    for(int i=1;i<=n;i++) cout << c[i] << (i<n ? ' ' : '\n');
}