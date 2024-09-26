#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<string> bracket(n+1);
    for(int i=1;i<=n;i++) cin >> bracket[i];
    vector<int> father(n+1, 0);
    for(int i=2;i<=n;i++) cin >> father[i];
    vector<ll> ans(n+1, 0);
    ll current_ans = 0;
    for(int i=1;i<=n;i++){
        // Reconstruct the path from root to i
        string s;
        int current = i;
        while(current !=0){
            s.push_back(bracket[current][0]);
            current = father[current];
        }
        reverse(s.begin(), s.end());
        // Compute num[i] using DP
        int L = s.length();
        vector<int> dp(L, 0);
        ll count =0;
        for(int j=1; j<L; j++){
            if(s[j] ==')'){
                if(s[j-1] == '('){
                    dp[j] =1 + ((j>=2)? dp[j-2] : 0);
                }
                else{
                    if(j-1 >=0 && s[j-1] == ')' ){
                        int prev = j - dp[j-1] -1;
                        if(prev >=0 && s[prev] == '('){
                            dp[j] =1 + dp[j-1];
                            if(prev-1 >=0) dp[j] += dp[prev-1];
                        }
                    }
                }
                count += dp[j];
            }
        }
        // Update ans
        current_ans ^= (count * (ll)i);
        ans[i] = current_ans;
    }
    cout << ans[n];
}