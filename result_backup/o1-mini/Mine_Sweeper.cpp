#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for(int i=0;i<n;i++) {
        cin >> grid[i];
    }
    vector<string> result(n, string(m, '0'));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(grid[i][j] == '*'){
                result[i][j] = '*';
                continue;
            }
            int count = 0;
            for(int di=-1; di<=1; di++){
                for(int dj=-1; dj<=1; dj++){
                    if(di ==0 && dj ==0) continue;
                    int ni = i + di, nj = j + dj;
                    if(ni >=0 && ni <n && nj >=0 && nj <m && grid[ni][nj] == '*') count++;
                }
            }
            result[i][j] = count + '0';
        }
    }
    for(int i=0;i<n;i++) cout << result[i] << "\n";
}