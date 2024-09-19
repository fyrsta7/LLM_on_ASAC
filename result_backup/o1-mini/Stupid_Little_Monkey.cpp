#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

bool is_prime(int n){
    if(n < 2) return false;
    for(int i=2;i<=sqrt(n);i++){
        if(n%i == 0) return false;
    }
    return true;
}

int main(){
    string word;
    cin >> word;
    vector<int> freq(26, 0);
    for(char c : word){
        freq[c - 'a']++;
    }
    int maxn = 0, minn = 0;
    bool first = true;
    for(int f : freq){
        if(f > 0){
            if(first){
                minn = f;
                first = false;
            }
            if(f < minn){
                minn = f;
            }
            if(f > maxn){
                maxn = f;
            }
        }
    }
    int diff = maxn - minn;
    if(is_prime(diff)){
        cout << "Lucky Word\n" << diff;
    }
    else{
        cout << "No Answer\n0";
    }
    return 0;
}