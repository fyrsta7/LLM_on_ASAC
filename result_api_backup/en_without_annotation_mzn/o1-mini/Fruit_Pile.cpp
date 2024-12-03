#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    if(n==0){
        cout<<0;
        return 0;
    }
    long long stamina=0;
    priority_queue<long long, vector<long long>, std::greater<long long>> pq;
    for(int i=0;i<n;i++){
        long long x;
        cin>>x;
        pq.push(x);
    }
    while(pq.size()>1){
        long long a = pq.top(); pq.pop();
        long long b = pq.top(); pq.pop();
        stamina += a + b;
        pq.push(a + b);
    }
    cout<<stamina;
}