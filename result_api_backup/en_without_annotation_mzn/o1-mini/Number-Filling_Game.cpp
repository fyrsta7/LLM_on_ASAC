#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    // Generate all directions: paths from (1,1) to (n,m) with (n-1) downs and (m-1) rights
    int total_steps = n + m - 2;
    int max_mn = 1;
    for(int i = m; i <= m+n-2; ++i) max_mn *= i;
    int denom = 1;
    for(int i =1;i<=n-1;++i) denom *=i;
    max_mn /= denom;
    // Generate all direction vectors
    vector<vector<int>> directions;
    int total_dirs = max_mn;
    string s(n-1, '0');
    s += string(m-1, '1');
    sort(s.begin(), s.end());
    do{
        vector<int> dir;
        for(char c:s) dir.push_back(c-'0');
        directions.push_back(dir);
    }while(next_permutation(s.begin(), s.end()));
    // Precompute all paths for directions
    // Each path is a list of (x,y) positions
    vector<vector<pair<int,int>>> paths;
    for(auto &dir: directions){
        vector<pair<int,int>> path;
        int x=1, y=1;
        path.emplace_back(x,y);
        for(auto d: dir){
            if(d ==0) x++;
            else y++;
            path.emplace_back(x,y);
        }
        paths.push_back(path);
    }
    // Precompute direction order
    // The directions are already in lex order based on binary representation
    // To define 'larger', we consider the binary as a number
    // So we sort the directions accordingly
    // Already sorted in directions
    // Now iterate over all tables
    long long sum_ans =0;
    int total_tables = 1 << (n*m);
    for(int table =0; table < total_tables; ++table){
        // Extract table values
        auto get_val = [&](int x, int y) -> int{
            return (table >> ((x-1)*m + (y-1))) &1;
        };
        // Compute tracks
        vector<string> tracks;
        for(auto &path: paths){
            string track;
            for(auto &[x,y]: path){
                track += to_string(get_val(x,y));
            }
            tracks.push_back(track);
        }
        // Check the condition
        bool ok = true;
        for(int i=0;i<directions.size() && ok;i++) {
            for(int j=0;j<directions.size() && ok;j++) {
                if(i == j) continue;
                // Compare directions[i] and directions[j]
                bool larger = false, same = true;
                for(int k=0; k<total_steps; ++k){
                    if(directions[i][k] > directions[j][k]){
                        larger = true;
                        break;
                    }
                    if(directions[i][k] < directions[j][k]){
                        same = false;
                        break;
                    }
                }
                if(larger){
                    if(tracks[i] <= tracks[j]){
                        ok = false;
                    }
                }
            }
        }
        if(ok) sum_ans++;
    }
    cout << sum_ans;
}