#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, r, c;
    cin >> n >> m >> r >> c;
    vector<vector<int>> a(n, vector<int>(m));
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            cin >> a[i][j];
        }
    }
    ll overall_min = LLONG_MAX;
    if(c ==0 || r ==0){
        cout << 0;
        return 0;
    }
    if(c > m || r > n){
        // As per constraints, this should not happen
        cout << 0;
        return 0;
    }
    // Initialize the first mask with c bits set
    if(m ==0 && c >0){
        // No columns to select
    }
    else{
        if(c == m){
            // Only one mask
            vector<int> cols;
            for(int j=0; j<m; j++) cols.push_back(j);
            // Compute horizontal_score
            vector<ll> horizontal_score(n, 0);
            for(int row=0; row<n; row++){
                for(int p=0; p<c-1; p++) horizontal_score[row] += abs(a[row][cols[p]] - a[row][cols[p+1]]);
            }
            // Compute vertical_score
            vector<vector<ll>> vertical_score(n, vector<ll>(n, 0));
            for(int i=0; i<n; i++){
                for(int j=i+1; j<n; j++){
                    for(int p=0; p<c; p++) vertical_score[i][j] += abs(a[i][cols[p]] - a[j][cols[p]]);
                }
            }
            // DP
            vector<ll> dp_prev(n, LLONG_MAX);
            for(int j=0; j<n; j++) dp_prev[j] = horizontal_score[j];
            for(int step=2; step<=r; step++){
                vector<ll> dp_new(n, LLONG_MAX);
                for(int j=0; j<n; j++){
                    for(int i=0; i<j; i++) {
                        if(dp_prev[i] != LLONG_MAX){
                            ll temp = dp_prev[i] + vertical_score[i][j] + horizontal_score[j];
                            if(temp < dp_new[j]){
                                dp_new[j] = temp;
                            }
                        }
                    }
                }
                dp_prev = dp_new;
            }
            // Find minimum score for this column selection
            ll min_score = LLONG_MAX;
            for(int j=0; j<n; j++) min_score = min(min_score, dp_prev[j]);
            // Update overall_min
            overall_min = min(overall_min, min_score);
        }
        else{
            // Iterate through all combinations of c columns
            // Initialize mask with c bits set
            if(c > m){
                // Not possible
            }
            else{
                if(c ==0){
                    // Special case, but as per constraints, c >=1
                }
                else{
                    // Start with the smallest mask with c bits set
                    unsigned int mask = (c == 32) ? 0xFFFFFFFF : ((1u << c) -1);
                    while(mask < (1u << m)){
                        // Extract column indices
                        vector<int> cols;
                        for(int j=0; j<m; j++) if(mask & (1u << j)) cols.push_back(j);
                        // Compute horizontal_score
                        vector<ll> horizontal_score(n, 0);
                        for(int row=0; row<n; row++){
                            for(int p=0; p<c-1; p++) horizontal_score[row] += abs(a[row][cols[p]] - a[row][cols[p+1]]);
                        }
                        // Compute vertical_score
                        vector<vector<ll>> vertical_score(n, vector<ll>(n, 0));
                        for(int i=0; i<n; i++){
                            for(int j=i+1; j<n; j++){
                                for(int p=0; p<c; p++) vertical_score[i][j] += abs(a[i][cols[p]] - a[j][cols[p]]);
                            }
                        }
                        // DP
                        vector<ll> dp_prev(n, LLONG_MAX);
                        for(int j=0; j<n; j++) dp_prev[j] = horizontal_score[j];
                        for(int step=2; step<=r; step++){
                            vector<ll> dp_new(n, LLONG_MAX);
                            for(int j=0; j<n; j++){
                                for(int i=0; i<j; i++) {
                                    if(dp_prev[i] != LLONG_MAX){
                                        ll temp = dp_prev[i] + vertical_score[i][j] + horizontal_score[j];
                                        if(temp < dp_new[j]){
                                            dp_new[j] = temp;
                                        }
                                    }
                                }
                            }
                            dp_prev = dp_new;
                        }
                        // Find minimum score for this column selection
                        ll min_score = LLONG_MAX;
                        for(int j=0; j<n; j++) min_score = min(min_score, dp_prev[j]);
                        // Update overall_min
                        overall_min = min(overall_min, min_score);
                        // Generate next mask with c bits set
                        if(c ==0){
                            break;
                        }
                        if(c == m){
                            break;
                        }
                        unsigned int smallest = mask & -mask;
                        unsigned int ripple = mask + smallest;
                        unsigned int new_smallest = mask ^ ripple;
                        new_smallest = (new_smallest >> 2) / smallest;
                        mask = new_smallest | ripple;
                    }
                }
            }
        }
    }
    cout << overall_min;
}
