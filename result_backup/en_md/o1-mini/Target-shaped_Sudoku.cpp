#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

struct Cell {
    int r, c, weight, box;
};

int grid[9][9];
int weight_grid[9][9];
int row_used[9];
int col_used[9];
int box_used[9];
long long max_score = -1;
long long current_score = 0;
vector<Cell> empty_cells;
long long total_weights = 0;

bool compare(const Cell &a, const Cell &b) {
    if(a.weight != b.weight)
        return a.weight > b.weight;
    return false;
}

int main(){
    // Read input
    for(int r=0;r<9;r++) {
        for(int c=0;c<9;c++) {
            cin >> grid[r][c];
        }
    }
    // Assign weights
    for(int r=0;r<9;r++) {
        for(int c=0;c<9;c++) {
            int distance = max(abs(r-4), abs(c-4));
            if(distance ==0) weight_grid[r][c] =10;
            else if(distance ==1) weight_grid[r][c] =9;
            else if(distance ==2) weight_grid[r][c] =8;
            else if(distance ==3) weight_grid[r][c] =7;
            else weight_grid[r][c] =6;
        }
    }
    // Initialize used digits and collect empty cells
    for(int r=0;r<9;r++) {
        for(int c=0;c<9;c++) {
            if(grid[r][c] !=0){
                int num = grid[r][c]-1;
                row_used[r] |= (1<<num);
                col_used[c] |= (1<<num);
                int box = (r/3)*3 + (c/3);
                box_used[box] |= (1<<num);
                current_score += (long long)weight_grid[r][c] * grid[r][c];
            }
            else{
                Cell cell;
                cell.r = r;
                cell.c = c;
                cell.weight = weight_grid[r][c];
                cell.box = (r/3)*3 + (c/3);
                empty_cells.push_back(cell);
                total_weights += weight_grid[r][c];
            }
        }
    }
    // Sort empty cells by descending weight
    sort(empty_cells.begin(), empty_cells.end(), compare);
    int n = empty_cells.size();
    // Precompute maximum remaining score
    vector<long long> max_remaining(n, 0);
    long long tmp =0;
    for(int i=n-1;i>=0;i--){
        tmp += (long long)empty_cells[i].weight * 9;
        max_remaining[i] = tmp;
    }
    // Backtracking
    function<void(int)> backtrack = [&](int idx)-> void{
        if(idx == n){
            if(current_score > max_score){
                max_score = current_score;
            }
            return;
        }
        // Prune if current + max possible < max_score
        if(current_score + max_remaining[idx] <= max_score) return;
        Cell cell = empty_cells[idx];
        int r = cell.r;
        int c = cell.c;
        int b = cell.box;
        for(int num=8; num>=0; num--){
            if( !(row_used[r] & (1<<num)) && !(col_used[c] & (1<<num)) && !(box_used[b] & (1<<num)) ){
                row_used[r] |= (1<<num);
                col_used[c] |= (1<<num);
                box_used[b] |= (1<<num);
                current_score += (long long)cell.weight * (num+1);
                backtrack(idx+1);
                current_score -= (long long)cell.weight * (num+1);
                row_used[r] ^= (1<<num);
                col_used[c] ^= (1<<num);
                box_used[b] ^= (1<<num);
            }
        }
    };
    backtrack(0);
    cout << max_score;
}