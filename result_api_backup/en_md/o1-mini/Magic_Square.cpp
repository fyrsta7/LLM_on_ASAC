#include <iostream>
#include <vector>
using namespace std;

int main(){
    int N;
    cin >> N;
    vector<vector<int>> magic(N, vector<int>(N, 0));
    int K =1;
    int row =0;
    int col = N/2;
    magic[row][col]=K;
    for(K=2; K<=N*N; K++){
        int new_row, new_col;
        if(row ==0 && col != N-1){
            new_row = N-1;
            new_col = col +1;
        }
        else if(col == N-1 && row !=0){
            new_row = row -1;
            new_col =0;
        }
        else if(row ==0 && col == N-1){
            new_row = row +1;
            new_col = col;
        }
        else{
            int top_right_row = (row -1 + N) % N;
            int top_right_col = (col +1) % N;
            if(magic[top_right_row][top_right_col] ==0){
                new_row = top_right_row;
                new_col = top_right_col;
            }
            else{
                new_row = (row +1) % N;
                new_col = col;
            }
        }
        magic[new_row][new_col]=K;
        row = new_row;
        col = new_col;
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(j >0) cout << " ";
            cout << magic[i][j];
        }
        cout << "\n";
    }
}