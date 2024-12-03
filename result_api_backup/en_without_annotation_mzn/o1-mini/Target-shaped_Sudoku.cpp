#include <bits/stdc++.h>
using namespace std;

int origin[9][9];
int score_grid[9][9] = {
    {6,6,6,6,6,6,6,6,6},
    {6,7,7,7,7,7,7,7,6},
    {6,7,8,8,8,8,8,7,6},
    {6,7,8,9,9,9,8,7,6},
    {6,7,8,9,10,9,8,7,6},
    {6,7,8,9,9,9,8,7,6},
    {6,7,8,8,8,8,8,7,6},
    {6,7,7,7,7,7,7,7,6},
    {6,6,6,6,6,6,6,6,6}
};
int max_score = 0;

bool rows[9][10];
bool cols[9][10];
bool boxes[9][10];

int cells[81][2];
int num_cells = 0;

int current_score = 0;

int main(){
    // Read origin grid
    for(int i=0;i<9;i++) {
        for(int j=0;j<9;j++) {
            cin >> origin[i][j];
            if(origin[i][j]==0){
                cells[num_cells][0] = i;
                cells[num_cells][1] = j;
                num_cells++;
            }
        }
    }
    // Initialize constraints
    memset(rows, 0, sizeof(rows));
    memset(cols, 0, sizeof(cols));
    memset(boxes, 0, sizeof(boxes));
    // Set initial constraints and current_score
    for(int i=0;i<9;i++) {
        for(int j=0;j<9;j++) {
            if(origin[i][j]!=0){
                int num = origin[i][j];
                rows[i][num] = true;
                cols[j][num] = true;
                int b = (i/3)*3 + j/3;
                boxes[b][num] = true;
                current_score += score_grid[i][j] * num;
            }
        }
    }
    // Precompute maximum possible additional score for pruning
    int max_additional = 0;
    for(int k=0;k<num_cells;k++) {
        int i = cells[k][0];
        int j = cells[k][1];
        max_additional += score_grid[i][j] * 9;
    }
    // Backtracking function
    function<void(int, int)> backtrack = [&](int idx, int total) {
        if(idx == num_cells){
            if(total > max_score){
                max_score = total;
            }
            return;
        }
        // Prune if current total + max possible remaining < max_score
        if(total + (max_additional - total) < max_score){
            return;
        }
        int i = cells[idx][0];
        int j = cells[idx][1];
        int b = (i/3)*3 + j/3;
        // Try numbers from 9 downto 1 to maximize early
        for(int num=9; num>=1; num--){
            if(!rows[i][num] && !cols[j][num] && !boxes[b][num]){
                rows[i][num] = cols[j][num] = boxes[b][num] = true;
                backtrack(idx+1, total + score_grid[i][j] * num);
                rows[i][num] = cols[j][num] = boxes[b][num] = false;
            }
        }
    };
    backtrack(0, current_score);
    cout << max_score;
}