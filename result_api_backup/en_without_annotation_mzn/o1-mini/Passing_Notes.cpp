#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int m, n;
    cin >> m >> n;
    // 1-based indexing
    vector<vector<int>> students(m+1, vector<int>(n+1, 0));
    for(int i=1;i<=m;i++) {
        for(int j=1;j<=n;j++) {
            cin >> students[i][j];
        }
    }
    int L = m + n -1;
    const int NEG_INF = -1e9;
    // Initialize dp_prev with -INF
    vector<vector<int>> dp_prev(m+1, vector<int>(m+1, NEG_INF));
    // At k=0, both paths are at (1,1)
    dp_prev[1][1] = 2 * students[1][1];
    // Iterate over steps k from 1 to L-1
    for(int k=1; k < L; k++) {
        // Initialize current dp step with -INF
        vector<vector<int>> dp_current(m+1, vector<int>(m+1, NEG_INF));
        // Iterate over possible x1 and x2
        for(int x1=1; x1<=m; x1++) {
            int y1 = k +2 -x1;
            if(y1 <1 || y1 >n) continue;
            for(int x2=1; x2<=m; x2++) {
                int y2 = k +2 -x2;
                if(y2 <1 || y2 >n) continue;
                // Check if paths overlap at non-start/end steps
                if(x1 ==x2 && y1 == y2 && k !=0 && k != L-1) continue;
                // Calculate value to add
                int val;
                if(x1 ==x2 && y1 == y2){
                    if(k ==0 || k == L-1){
                        val = students[x1][y1];
                    }
                    else continue;
                }
                else{
                    val = students[x1][y1] + students[x2][y2];
                }
                // Iterate over possible previous moves
                for(int dx1 =0; dx1 <=1; dx1++) {
                    for(int dx2 =0; dx2 <=1; dx2++) {
                        int prev_x1 = x1 - dx1;
                        int prev_x2 = x2 - dx2;
                        if(prev_x1 <1 || prev_x2 <1) continue;
                        int prev_y1 = y1 - (dx1 ==0 ? 1 : 0);
                        int prev_y2 = y2 - (dx2 ==0 ? 1 : 0);
                        if(prev_y1 <1 || prev_y1 >n) continue;
                        if(prev_y2 <1 || prev_y2 >n) continue;
                        if(dp_prev[prev_x1][prev_x2] == NEG_INF) continue;
                        dp_current[x1][x2] = max(dp_current[x1][x2], dp_prev[prev_x1][prev_x2] + val);
                    }
                }
            }
        }
        // Move to next step
        dp_prev = dp_current;
    }
    // The final value is at dp_prev[m][m]
    cout << dp_prev[m][m];
}