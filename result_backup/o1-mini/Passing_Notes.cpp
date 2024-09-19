#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int main(){
    int m, n;
    cin >> m >> n;
    vector<vector<int>> grid(m+1, vector<int>(n+1, 0));
    for(int i=1;i<=m;i++) {
        for(int j=1;j<=n;j++) {
            cin >> grid[i][j];
        }
    }
    // Initialize DP
    // dp[x1][x2] represents the current step
    // Initialize previous and current DP
    const int INF = -1e9;
    vector<vector<int>> prevDP(m+1, vector<int>(m+1, INF));
    prevDP[1][1] = grid[1][1];
    // Iterate over steps
    for(int s=1; s<=m+n-2; s++){
        vector<vector<int>> currDP(m+1, vector<int>(m+1, INF));
        for(int x1=1; x1<=m; x1++){
            int y1 = s - (x1 -1) +1;
            if(y1 <1 || y1 >n) continue;
            for(int x2=1; x2<=m; x2++){
                int y2 = s - (x2 -1) +1;
                if(y2 <1 || y2 >n) continue;
                if(prevDP[x1][x2] == INF) continue;
                // Possible moves for path1
                for(int dx1 = 0; dx1 <=1; dx1++){
                    for(int dx2 = 0; dx2 <=1; dx2++){
                        int prevX1 = x1 - dx1;
                        int prevY1 = y1 - (1 - dx1);
                        int prevX2 = x2 - dx2;
                        int prevY2 = y2 - (1 - dx2);
                        if(prevX1 <1 || prevY1 <1 || prevX2 <1 || prevY2 <1) continue;
                        if(prevDP[prevX1][prevX2] == INF) continue;
                        int val = prevDP[prevX1][prevX2];
                        if(x1 == x2 && y1 == y2){
                            val += grid[x1][y1];
                        }
                        else{
                            val += grid[x1][y1] + grid[x2][y2];
                        }
                        currDP[x1][x2] = max(currDP[x1][x2], val);
                    }
                }
            }
        }
        prevDP = currDP;
    }
    cout << (prevDP[m][m] >=0 ? prevDP[m][m] : 0);
}