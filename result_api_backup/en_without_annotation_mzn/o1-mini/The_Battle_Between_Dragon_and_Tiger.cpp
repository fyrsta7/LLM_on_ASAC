#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> num(n+1);
    for(int i=1;i<=n;i++) cin >> num[i];
    int m, p1, s1, s2;
    cin >> m >> p1 >> s1 >> s2;
    ll sum1=0, sum2=0;
    for(int i=1;i<m;i++) sum1 += (ll)num[i]*(m - i);
    for(int i=m+1;i<=n;i++) sum2 += (ll)num[i]*(i - m);
    ll left_fixed = sum1 + (p1 < m ? (ll)s1*(m - p1) : 0);
    ll right_fixed = sum2 + (p1 > m ? (ll)s1*(p1 - m) : 0);
    ll min_diff = LLONG_MAX;
    int best_p2 = 1;
    for(int p2=1;p2<=n;p2++){
        ll left = left_fixed + (p2 < m ? (ll)s2*(m - p2) : 0);
        ll right = right_fixed + (p2 > m ? (ll)s2*(p2 - m) : 0);
        ll diff = abs(left - right);
        if(diff < min_diff || (diff == min_diff && p2 < best_p2)){
            min_diff = diff;
            best_p2 = p2;
        }
    }
    cout << "p2=" << best_p2;
}