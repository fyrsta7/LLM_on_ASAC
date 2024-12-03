#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> t(n);
    for(int &x:t) cin>>x;
    vector<int> lis(n,1);
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(t[j]<t[i]){
                if(lis[j]+1 > lis[i]){
                    lis[i]=lis[j]+1;
                }
            }
        }
    }
    vector<int> lds(n,1);
    for(int i=n-1;i>=0;i--){
        for(int j=n-1;j>i;j--){
            if(t[j]<t[i]){
                if(lds[j]+1 > lds[i]){
                    lds[i]=lds[j]+1;
                }
            }
        }
    }
    int max_k=0;
    for(int i=0;i<n;i++){
        if(lis[i] + lds[i] -1 > max_k){
            max_k = lis[i] + lds[i] -1;
        }
    }
    cout << n - max_k;
}