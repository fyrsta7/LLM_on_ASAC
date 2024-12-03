#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> elements(m);
    for(int i=0;i<m;i++){
        cin >> elements[i].first;
        elements[i].second = i;
    }
    sort(elements.begin(), elements.end());
    // Create a value array
    vector<int> X(m);
    for(int i=0;i<m;i++) X[i] = elements[i].first;
    // Create a sorted index array
    // Initialize counts
    vector<vector<int>> ans(m, vector<int>(4, 0));
    for(int i=0;i<m;i++){
        for(int j=i+1;j<m;j++){
            long long d = (long long)X[j] - X[i];
            if(d % 2 != 0) continue;
            long long d_prime = d / 2;
            long long required_k_min = X[j] + 6*d_prime +1;
            // Find the first k where X[k] > X[j] + 6*d'
            int k_start = upper_bound(X.begin(), X.end(), (int)(X[j] + 6*d_prime)) - X.begin();
            for(int k=k_start; k<m; k++){
                long long Xk = X[k];
                long long Xl = Xk + d_prime;
                // Find l such that X[l] == Xk + d_prime
                int l = lower_bound(X.begin(), X.end(), (int)Xl) - X.begin();
                if(l < m && X[l] == Xl){
                    int a = elements[i].second;
                    int b = elements[j].second;
                    int c = elements[k].second;
                    int d_idx = elements[l].second;
                    ans[a][0]++;
                    ans[b][1]++;
                    ans[c][2]++;
                    ans[d_idx][3]++;
                }
            }
        }
    }
    for(int i=0;i<m;i++) cout << ans[i][0] << ' ' << ans[i][1] << ' ' << ans[i][2] << ' ' << ans[i][3] << '\n';
}