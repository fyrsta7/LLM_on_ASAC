#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    string M, k;
    getline(cin, M);
    getline(cin, k);
    int M_len = M.length();
    int k_len = k.length();
    string out_str;
    out_str.reserve(M_len);
    auto to_int = [&](char c) -> int{
        if('A' <= c && c <= 'Z') return c - 'A' +1;
        if('a' <= c && c <= 'z') return c - 'a' +1;
        return 1;
    };
    for(int i=0;i<M_len;i++){
        int y = to_int(M[i]);
        int x = to_int(k[i % k_len]);
        int z = (y - x + 26) % 26 +1;
        char c = 'A' + z -1;
        out_str += c;
    }
    cout<<out_str;
}