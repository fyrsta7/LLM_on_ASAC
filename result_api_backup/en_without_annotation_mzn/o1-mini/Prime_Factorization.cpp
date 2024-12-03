#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    for(int m = n-1; m >=2; m--){
        if(n%m ==0){
            cout<<m;
            return 0;
        }
    }
}