#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    int sticks[10] = {6,2,5,5,4,5,6,3,7,6};
    auto use_sticks = [&](int num) -> int{
        if(num ==0) return sticks[0];
        int s =0;
        while(num >0){
            s += sticks[num%10];
            num /=10;
        }
        return s;
    };
    vector<int> S_list;
    // To avoid duplicates, iterate a <=b
    for(int a=0; a<=1000; a++){
        int sa = use_sticks(a);
        for(int b=a; b<=1000; b++){
            int sb = use_sticks(b);
            int c = a + b;
            int sc = use_sticks(c);
            int S = sa + sb + sc +4;
            if(S > n) break;
            S_list.push_back(S);
        }
    }
    // Knapsack to maximize count
    vector<int> dp(n+1, 0);
    for(auto S:S_list){
        for(int j=n; j>=S; j--){
            if(dp[j - S] +1 > dp[j]){
                dp[j] = dp[j - S] +1;
            }
        }
    }
    int ans =0;
    for(int i=0;i<=n;i++) ans = max(ans, dp[i]);
    cout<<ans;
}