#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    long long k;
    cin >> n >> k;
    long long g = k ^ (k >> 1);
    string s = "";
    for(int i=n-1;i>=0;i--){
        s += ((g>>i)&1) ? '1':'0';
    }
    cout << s;
}