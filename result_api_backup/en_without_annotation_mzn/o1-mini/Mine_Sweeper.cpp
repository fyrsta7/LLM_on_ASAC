#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m, 0));
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            cin >> a[i][j];
        }
    }
    // Directions for 8 neighbors
    int dirs[8][2] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };
    for(int i=0;i<n;i++){
        string s = "";
        for(int j=0;j<m;j++){
            if(a[i][j]==1){
                s += "*";
            }
            else{
                int count = 0;
                for(auto &d: dirs){
                    int ni = i + d[0];
                    int nj = j + d[1];
                    if(ni >=0 && ni <n && nj >=0 && nj <m && a[ni][nj]==1){
                        count++;
                    }
                }
                s += to_string(count);
            }
        }
        cout << s << "\n";
    }
}