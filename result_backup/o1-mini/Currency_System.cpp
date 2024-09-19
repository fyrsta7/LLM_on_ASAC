#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(auto &x: a) cin >> x;
        sort(a.begin(), a.end());
        const int MAX = 1000000;
        bitset<1000001> dp;
        dp.reset();
        dp[0] = 1;
        int m = 0;
        for(auto ai: a){
            if(ai > MAX) { m +=1; continue;}
            if(ai <= MAX && !dp[ai]){
                m +=1;
                if(ai <= MAX){
                    dp |= (dp << ai);
                }
            }
        }
        cout << m << "\n";
    }
}