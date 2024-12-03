#include<bits/stdc++.h>
using namespace std;

int main(){
    int N;
    cin>>N;
    vector<vector<int>> grid(N, vector<int>(N, 0));
    int mid = N/2;
    int current_row =0, current_col = mid;
    grid[current_row][current_col]=1;
    for(int i=2;i<=N*N;i++){
        int new_row = (current_row -1 +N)%N;
        int new_col = (current_col +1)%N;
        if(grid[new_row][new_col]==0){
            grid[new_row][new_col]=i;
            current_row = new_row;
            current_col = new_col;
        }
        else{
            new_row = (current_row +1)%N;
            grid[new_row][current_col]=i;
            current_row = new_row;
        }
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout<<grid[i][j];
            if(j!=N-1) cout<<' ';
            else cout<<'\n';
        }
    }
}