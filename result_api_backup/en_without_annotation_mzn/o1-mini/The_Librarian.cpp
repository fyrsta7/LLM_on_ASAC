#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> index(n);
    for(auto &x:index) cin>>x;
    vector<int> reader_token(q);
    for(auto &x:reader_token) cin>>x;
    vector<int> reader_bit(q);
    int max_bit=1;
    for(auto &x:reader_bit){
        cin>>x;
        if(x > max_bit) max_bit = x;
    }
    sort(index.begin(), index.end());
    // Precompute powers of 10
    vector<long long> pow10(max_bit+1, 1);
    for(int i=1;i<=max_bit;i++) pow10[i]=pow10[i-1]*10;
    // Initialize min_index
    // To save memory, use vector<vector<int>> only up to bit=6
    if(max_bit >7){
        // Handle larger bits if necessary
    }
    vector<vector<int>> min_index(max_bit+1);
    for(int B=1; B<=max_bit; B++){
        if(B>7){
            // Skip or handle accordingly
            min_index[B].resize(1, -1);
            continue;
        }
        int size = pow10[B];
        min_index[B].assign(size, -1);
        for(auto x:index){
            long long R = x % pow10[B];
            if(R >= size) continue;
            if(min_index[B][R]==-1){
                min_index[B][R]=x;
            }
        }
    }
    // Process queries
    for(int i=0;i<q;i++){
        int B = reader_bit[i];
        int T = reader_token[i];
        if(B > max_bit || B >7){
            cout<<-1<<"\n";
            continue;
        }
        if(T >= pow10[B]){
            cout<<-1<<"\n";
            continue;
        }
        if(min_index[B][T]!=-1){
            cout<<min_index[B][T]<<"\n";
        }
        else{
            cout<<-1<<"\n";
        }
    }
}