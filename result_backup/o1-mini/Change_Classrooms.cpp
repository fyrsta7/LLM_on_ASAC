#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstring>
using namespace std;

const double INF = 1e18;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, v, e;
    cin >> n >> m >> v >> e;
    vector<int> c(n+1);
    for(int i=1;i<=n;i++) cin >> c[i];
    vector<int> d(n+1);
    for(int i=1;i<=n;i++) cin >> d[i];
    vector<double> k(n+1);
    for(int i=1;i<=n;i++) cin >> k[i];
    // Initialize distance matrix
    vector<vector<long long>> dist(v+1, vector<long long>(v+1, 1e12));
    for(int i=1;i<=v;i++) dist[i][i]=0;
    for(int i=0;i<e;i++){
        int a, b, w;
        cin >> a >> b >> w;
        if(w < dist[a][b]){
            dist[a][b] = w;
            dist[b][a] = w;
        }
    }
    // Floyd-Warshall
    for(int via=1; via<=v; via++){
        for(int i=1; i<=v; i++){
            if(dist[i][via] == 1e12) continue;
            for(int j=1; j<=v; j++){
                if(dist[via][j] == 1e12) continue;
                if(dist[i][j] > dist[i][via] + dist[via][j]){
                    dist[i][j] = dist[i][via] + dist[via][j];
                }
            }
        }
    }
    // Precompute E[i][prev][curr]
    // E[i][prev][curr] represents movement from i-1 to i based on i-1 applied=prev and i applied=curr
    // i from1 ton
    vector<vector<vector<double>>> E(n+1, vector<vector<double>>(2, vector<double>(2, 0.0)));
    for(int i=1;i<=n;i++){
        for(int prev=0; prev<=1; prev++){
            for(int curr=0; curr<=1; curr++){
                if(i==1){
                    E[i][prev][curr] = 0.0;
                }
                else{
                    // Movement from i-1 toi
                    // class i-1 is applied_prev=prev
                    // classi is applied_curr=curr
                    if(prev ==1 && curr ==1){
                        // E = k[i-1]*k[i]*dist[d[i-1]][d[i]] + k[i-1]*(1 -k[i])*dist[d[i-1]][c[i]] + (1 -k[i-1])*k[i]*dist[c[i-1]][d[i]] + (1 -k[i-1])*(1 -k[i])*dist[c[i-1]][c[i]]
                        E[i][prev][curr] = k[i-1]*k[i]*dist[d[i-1]][d[i]] + k[i-1]*(1.0 -k[i])*dist[d[i-1]][c[i]] + (1.0 -k[i-1])*k[i]*dist[c[i-1]][d[i]] + (1.0 -k[i-1])*(1.0 -k[i])*dist[c[i-1]][c[i]];
                    }
                    else if(prev ==1 && curr ==0){
                        // E = k[i-1]*dist[d[i-1]][c[i]] + (1 -k[i-1])*dist[c[i-1]][c[i]]
                        E[i][prev][curr] = k[i-1]*dist[d[i-1]][c[i]] + (1.0 -k[i-1])*dist[c[i-1]][c[i]];
                    }
                    else if(prev ==0 && curr ==1){
                        // E = k[i]*dist[c[i-1]][d[i]] + (1 -k[i])*dist[c[i-1]][c[i]]
                        E[i][prev][curr] = k[i]*dist[c[i-1]][d[i]] + (1.0 -k[i])*dist[c[i-1]][c[i]];
                    }
                    else{ // prev ==0 && curr ==0
                        // E = dist[c[i-1]][c[i]]
                        E[i][prev][curr] = dist[c[i-1]][c[i]];
                    }
                }
            }
        }
    }
    // Initialize DP
    // prev_dp[k][prev_applied]
    vector<vector<double>> prev_dp(m+1, vector<double>(2, INF));
    prev_dp[0][0] =0.0;
    // Iterate through classes
    for(int i=1;i<=n;i++){
        vector<vector<double>> cur_dp(m+1, vector<double>(2, INF));
        for(int k_used=0; k_used<=m; k_used++){
            for(int prev=0; prev<=1; prev++){
                if(prev_dp[k_used][prev] < INF){
                    // Option 1: do not apply to i
                    int new_k = k_used;
                    int curr_applied =0;
                    double E_add = (i==1) ? 0.0 : E[i][prev][curr_applied];
                    if(cur_dp[new_k][curr_applied] > prev_dp[k_used][prev] + E_add){
                        cur_dp[new_k][curr_applied] = prev_dp[k_used][prev] + E_add;
                    }
                    // Option 2: apply to i
                    if(k_used <m){
                        int new_k2 = k_used +1;
                        int curr_applied2 =1;
                        double E_add2 = (i==1) ? 0.0 : E[i][prev][curr_applied2];
                        if(cur_dp[new_k2][curr_applied2] > prev_dp[k_used][prev] + E_add2){
                            cur_dp[new_k2][curr_applied2] = prev_dp[k_used][prev] + E_add2;
                        }
                    }
                }
            }
        }
        prev_dp = move(cur_dp);
    }
    // Find the minimum result
    double res = INF;
    for(int k=0; k<=m; k++){
        for(int prev=0; prev<=1; prev++){
            if(prev_dp[k][prev] < res){
                res = prev_dp[k][prev];
            }
        }
    }
    // Output with exactly two decimal places
    cout << fixed << setprecision(2) << res;
}