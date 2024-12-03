#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int d, n;
    cin >> d >> n;
    // Grid size 0..128
    vector<vector<long long>> grid(129, vector<long long>(129, 0));
    for(int i=0;i<n;i++){
        int x, y, num;
        cin >> x >> y >> num;
        if(x >=0 && x <=128 && y >=0 && y <=128){
            grid[x][y] += num;
        }
    }
    // Initialize prefix_sum
    vector<vector<long long>> prefix_sum(129, vector<long long>(129, 0));
    for(int x=0;x<=128;x++) {
        for(int y=0;y<=128;y++) {
            prefix_sum[x][y] = grid[x][y];
            if(x >0) prefix_sum[x][y] += prefix_sum[x-1][y];
            if(y >0) prefix_sum[x][y] += prefix_sum[x][y-1];
            if(x >0 && y >0) prefix_sum[x][y] -= prefix_sum[x-1][y-1];
        }
    }
    // Function to get sum in rectangle
    auto get_sum = [&](int x1, int y1, int x2, int y2) -> long long {
        x1 = max(0, x1);
        y1 = max(0, y1);
        x2 = min(128, x2);
        y2 = min(128, y2);
        if(x1 > x2 || y1 > y2) return 0;
        long long res = prefix_sum[x2][y2];
        if(x1 >0) res -= prefix_sum[x1-1][y2];
        if(y1 >0) res -= prefix_sum[x2][y1-1];
        if(x1 >0 && y1 >0) res += prefix_sum[x1-1][y1-1];
        return res;
    };
    // Initialize plans
    vector<pair<int, int>> plans_list;
    long long total_num =0;
    for(int p=0;p<100;p++){
        // Find the center with maximum sum
        long long max_sum = 0;
        int best_x = 0, best_y =0;
        for(int x=0;x<=128;x++){
            for(int y=0;y<=128;y++){
                long long s = get_sum(x-d, y-d, x+d, y+d);
                if(s > max_sum){
                    max_sum = s;
                    best_x = x;
                    best_y = y;
                }
            }
        }
        if(max_sum ==0) break;
        // Add to plans
        plans_list.emplace_back(best_x, best_y);
        total_num += max_sum;
        // Update grid: set covered cells to 0
        int x_min = max(0, best_x -d);
        int x_max = min(128, best_x +d);
        int y_min = max(0, best_y -d);
        int y_max = min(128, best_y +d);
        for(int x=x_min;x<=x_max;x++){
            for(int y=y_min;y<=y_max;y++){
                if(abs(x - best_x) <=d && abs(y - best_y) <=d){
                    if(grid[x][y] >0){
                        grid[x][y] =0;
                    }
                }
            }
        }
        // Recompute prefix_sum
        for(int x=0;x<=128;x++) {
            for(int y=0;y<=128;y++) {
                prefix_sum[x][y] = grid[x][y];
                if(x >0) prefix_sum[x][y] += prefix_sum[x-1][y];
                if(y >0) prefix_sum[x][y] += prefix_sum[x][y-1];
                if(x >0 && y >0) prefix_sum[x][y] -= prefix_sum[x-1][y-1];
            }
        }
    }
    // Output
    cout << plans_list.size() << " " << total_num;
}