#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    vector<long long> books(n);
    for(int i=0;i<n;i++) cin >> books[i];
    sort(books.begin(), books.end());
    while(q--){
        int l;
        long long r;
        cin >> l >> r;
        long long mod = 1;
        for(int i=0;i<l;i++) mod *=10;
        bool found = false;
        for(auto &code: books){
            if(code % mod == r){
                cout << code << "\n";
                found = true;
                break;
            }
        }
        if(!found) cout << "-1\n";
    }
}