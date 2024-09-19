#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    // Precompute pow2
    vector<double> pow2(m+1, 1.0);
    for(int k=1; k<=m; ++k){
        pow2[k] = pow2[k-1] * 2.0;
    }
    double total = 0.0;
    for(int line=0; line<n; ++line){
        vector<int> a(m);
        for(int i=0; i<m; ++i){
            cin >> a[i];
        }
        // Initialize DP
        vector<vector<double>> DP(m, vector<double>(m, 0.0));
        for(int len=1; len<=m; ++len){
            for(int l=0; l + len -1 < m; ++l){
                int r = l + len -1;
                int step = m - (r - l);
                if(l == r){
                    DP[l][r] = a[l] * pow2[step];
                }
                else{
                    double take_left = a[l] * pow2[step] + DP[l+1][r];
                    double take_right = a[r] * pow2[step] + DP[l][r-1];
                    DP[l][r] = max(take_left, take_right);
                }
            }
        }
        total += DP[0][m-1];
    }
    unsigned long long answer = static_cast<unsigned long long>(total + 1e-6);
    cout << answer;
}