#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while(T--){
        int n, m;
        cin >> n >> m;
        vector<pair<double, double>> pigs(n);
        for(int i=0;i<n;i++) cin >> pigs[i].first >> pigs[i].second;
        // Precompute all valid subsets
        vector<int> valid_subsets;
        for(int mask=1; mask<(1<<n); mask++){
            int cnt = __builtin_popcount(mask);
            if(cnt ==1){
                valid_subsets.push_back(mask);
                continue;
            }
            // Extract indices
            vector<int> indices;
            bool same_x = false;
            unordered_set<long long> x_set;
            for(int i=0;i<n;i++) if(mask & (1<<i)){
                long long xi = round(pigs[i].first * 1000000);
                if(x_set.find(xi) != x_set.end()){
                    same_x = true;
                    break;
                }
                x_set.insert(xi);
                indices.push_back(i);
            }
            if(same_x) continue;
            // Need at least two points
            if(indices.size() <2){
                // Already handled cnt ==1
                continue;
            }
            // Solve for a and b using first two points
            int i0 = indices[0];
            int i1 = indices[1];
            double x0 = pigs[i0].first;
            double y0 = pigs[i0].second;
            double x1 = pigs[i1].first;
            double y1 = pigs[i1].second;
            double D = x0*x0 * x1 - x1*x1 * x0;
            // Alternatively, use determinant method
            // Setup equations:
            // a*x0^2 + b*x0 = y0
            // a*x1^2 + b*x1 = y1
            // Solve for a and b
            double det = x0*x0 * x1 - x1*x1 * x0;
            // det = x0*x1*(x0 - x1)
            // If x0 ==x1, already handled
            // Use Cramer's rule
            double a, b;
            // To avoid division by zero, use different approach
            // Compute a and b
            // From first equation: a*x0^2 + b*x0 = y0
            // From second equation: a*x1^2 + b*x1 = y1
            // Solve for a:
            // a = (y1 - y0)/(x1^2 - x0^2) - b*(x1 -x0)/(x1^2 -x0^2)
            // Better to use linear equations
            // Using determinants
            double det_a = (y0 * x1) - (y1 * x0);
            double det_b = (x0*x0 * y1) - (x1*x1 * y0);
            double denominator = x0*x1*(x0 -x1);
            if(abs(denominator) < EPS){
                continue;
            }
            a = det_a / denominator;
            b = det_b / denominator;
            if(a >= -EPS){
                continue;
            }
            bool ok = true;
            for(auto idx: indices){
                double xi = pigs[idx].first;
                double yi = pigs[idx].second;
                double val = a*xi*xi + b*xi;
                if(abs(val - yi) > EPS){
                    ok = false;
                    break;
                }
            }
            if(ok){
                valid_subsets.push_back(mask);
            }
        }
        // Initialize DP
        int size = 1<<n;
        vector<int> dp(size, n);
        dp[0] =0;
        for(int mask=0; mask < size; mask++){
            if(dp[mask] >= n) continue;
            for(auto S: valid_subsets){
                int new_mask = mask | S;
                if(dp[new_mask] > dp[mask] +1){
                    dp[new_mask] = dp[mask] +1;
                }
            }
        }
        cout << dp[(1<<n)-1] << "\n";
    }
}