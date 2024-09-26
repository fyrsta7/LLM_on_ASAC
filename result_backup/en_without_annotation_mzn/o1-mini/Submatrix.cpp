#include<bits/stdc++.h>
using namespace std;

int main(){
    int N,M,R,C;
    cin>>N>>M>>R>>C;
    vector<vector<int>> a(N, vector<int>(M));
    for(auto &row:a) for(auto &x:row) cin>>x;
    // Precompute vertical differences
    vector<vector<int>> vert(N-1, vector<int>(M,0));
    for(int i=0;i<N-1;i++) for(int j=0;j<M;j++) vert[i][j]=abs(a[i][j]-a[i+1][j]);
    // Precompute horizontal differences
    vector<vector<int>> hor(N, vector<int>(M-1,0));
    for(int i=0;i<N;i++) for(int j=0;j<M-1;j++) hor[i][j]=abs(a[i][j]-a[i][j+1]);
    // Generate all row combinations
    vector<vector<int>> row_combinations;
    vector<int> current;
    function<void(int, int)> comb_rows = [&](int start, int k)-> void{
        if(k == 0){
            row_combinations.emplace_back(current);
            return;
        }
        for(int i=start;i<=N - k;i++){
            current.push_back(i);
            comb_rows(i+1, k-1);
            current.pop_back();
        }
    };
    comb_rows(0, R);
    // Generate all column combinations
    vector<vector<int>> col_combinations;
    current.clear();
    function<void(int, int)> comb_cols = [&](int start, int k)-> void{
        if(k == 0){
            col_combinations.emplace_back(current);
            return;
        }
        for(int i=start;i<=M - k;i++){
            current.push_back(i);
            comb_cols(i+1, k-1);
            current.pop_back();
        }
    };
    comb_cols(0, C);
    long long min_score = LLONG_MAX;
    for(auto &rows: row_combinations){
        // Precompute vertical sum for this row combination
        long long vert_sum =0;
        for(int j=0;j<C;j++) {
            for(int i=0;i<R-1;i++) vert_sum += vert[rows[i]][current.empty()?0:0];
        }
        // To optimize, compute vertical sum inside the loops
        // Similarly for horizontal
        // But proceed straightforwardly
        // To separate row and column handling
    }
    // Iterate through all combinations
    long long result = LLONG_MAX;
    for(auto &rows: row_combinations){
        for(auto &cols: col_combinations){
            long long score=0;
            // Vertical differences
            for(int j=0;j<C;j++) {
                for(int i=0;i<R-1;i++) {
                    score += abs(a[rows[i]][cols[j]] - a[rows[i+1]][cols[j]]);
                }
            }
            // Horizontal differences
            for(int i=0;i<R;i++) {
                for(int j=0;j<C-1;j++) {
                    score += abs(a[rows[i]][cols[j]] - a[rows[i]][cols[j+1]]);
                }
            }
            if(score < result){
                result = score;
            }
        }
    }
    cout<<"score="<<result;
}