#include <bits/stdc++.h>
using namespace std;

bool is_prime(int num){
    if(num < 2) return false;
    if(num ==2) return true;
    if(num%2 ==0) return false;
    int sqrt_n = sqrt(num);
    for(int i=3;i<=sqrt_n;i+=2){
        if(num%i ==0) return false;
    }
    return true;
}

int main(){
    string str;
    getline(cin, str);
    if(str.empty()){
        cout << "No Answer\n0";
        return 0;
    }
    unordered_map<char, int> freq;
    for(char c: str) freq[c]++;
    int maxn = INT32_MIN, minn = INT32_MAX;
    for(auto &[k,v]: freq){
        if(v > maxn) maxn = v;
        if(v < minn) minn = v;
    }
    int diff = maxn - minn;
    if(is_prime(diff)){
        cout << "Lucky Word\n" << diff;
    }
    else{
        cout << "No Answer\n0";
    }
}