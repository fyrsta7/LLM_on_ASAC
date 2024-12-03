#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int M, N, K, L, D;
    cin >> M >> N >> K >> L >> D;
    vector<vector<int>> students(D, vector<int>(4));
    for(auto &row: students) cin >> row[0] >> row[1] >> row[2] >> row[3];
    
    // Precompute for each student the possible horizontal and vertical indices
    vector<int> student_h_possible(D, 0);
    vector<int> student_v_possible(D, 0);
    for(int i=0;i<D;i++){
        // Horizontal
        if(abs(students[i][0] - students[i][2]) ==1 ){
            int j = min(students[i][0], students[i][2]);
            if(j >=1 && j <=M-1){
                student_h_possible[i] |= (1<<(j-1));
            }
        }
        // Vertical
        if(abs(students[i][1] - students[i][3]) ==1 ){
            int j = min(students[i][1], students[i][3]);
            if(j >=1 && j <=N-1){
                student_v_possible[i] |= (1<<(j-1));
            }
        }
    }
    
    // Enumerate all possible V subsets and precompute their coverage
    int total_V = 1<<N;
    vector<int> V_coverage(total_V, 0);
    for(int v=0; v<total_V; v++){
        if(__builtin_popcount(v)!=L) continue;
        int cnt=0;
        for(int i=0;i<D;i++) {
            if(student_v_possible[i] & v) cnt++;
        }
        V_coverage[v] = cnt;
    }
    
    // Enumerate all possible H subsets and find the best V for each
    int best_total = 0;
    int best_H = 0, best_V =0;
    int total_H = 1<<M;
    for(int h=0; h<total_H; h++){
        if(__builtin_popcount(h)!=K) continue;
        int cnt_h=0;
        for(int i=0;i<D;i++) {
            if(student_h_possible[i] & h) cnt_h++;
        }
        // Now find V that maximizes coverage not already covered by H
        // To do this, for each V, find how many it covers excluding those already covered by H
        // Precompute for each V, how many students it can cover excluding those already covered
        // But to simplify, since V_coverage[v] counts all V covers, and overlapping is acceptable
        // The best total would be cnt_h + max(V_coverage[v])
        // However, to account for overlaps where a student is covered by both H and V, we need to subtract
        // The number of students covered by both H and V
        // To simplify, accept possible overlaps and keep cnt_h + V_coverage[v] - overlap
        // but computing overlap is expensive, so instead, just maximize cnt_h + V_coverage[v] where overlap is minimized
        // Alternatively, proceed with cnt_h + V_coverage[v]
        // It's acceptable for correct answer since overlapping is counted once
        // But to get exact, need to compute the overlap
        // To compute exact total, need to compute for each V, how many H and V overlap
        // Implement exact total
        // Find for each V, the overlap with H
        // Precompute which students are covered by both H and V
        // To do it efficiently:
        // For each V, compute how many students are covered by both H and V
        // Implement:
        // For each V, iterate through students and count if both H and V cover it
        // But D up to 1000 and total V up to 1<<20 may be too much
        // Alternatively, proceed with cnt_h + V_coverage[v] - overlap and keep track
        // For the problem's sake, proceed with cnt_h + V_coverage[v]
        // which may overcount, but likely accept as approximation
        // To be correct, skip and choose H and V independently
        // Alternatively, find the maximum distinct coverage by H and V
        // Implement as cnt_h + (V_coverage[v] where student not covered by H)
        // To implement this, need for each V, the number of students it covers that are not in H
        // Precompute for each V, the number of students it covers not in H
        // Implement:
        // For each H, create a mask of covered by H
        // Then for each V, count V_coverage[v] minus overlap
        // To implement fast, precompute for each student the H_mask coverage
        // Implement H-covered mask
        // Create a bitmask where bit i is covered by H
        // But D up to 1000, use bitset
        // Implement using vector<int>
        // Alternatively, iterate through students and mark if covered by H
        // Then for V_coverage[v], subtract the number of V_coverage[v] that are already covered
        // Implement:
        // For each H, create a bitset of D bits indicating covered by H
        // Then for each V, count how many V covers and H does not
        // Implement using bitsets
        // Proceed to implement
        // Assuming D <= 1000
        // Implement H coverage as a bitset
        vector<bool> H_covered(D, false);
        for(int i=0;i<D;i++) if(student_h_possible[i] & h) H_covered[i] = true;
        // Now for each V with popcount L, compute how many V_coverage not in H_covered
        int best_V_for_H = 0;
        for(int v=0; v<total_V; v++) {
            if(__builtin_popcount(v)!=L) continue;
            // Count how many students V can cover that are not covered by H
            int cnt_v =0;
            for(int i=0;i<D;i++) if( (student_v_possible[i] & v) && !H_covered[i]) cnt_v++;
            if(cnt_h + cnt_v > best_total){
                best_total = cnt_h + cnt_v;
                best_H = h;
                best_V = v;
            }
        }
    }
    
    // Extract H and V from best_H and best_V
    vector<int> H_selected, V_selected;
    for(int j=0; j<M; j++) if(best_H & (1<<j)) H_selected.push_back(j+1);
    for(int j=0; j<N; j++) if(best_V & (1<<j)) V_selected.push_back(j+1);
    sort(H_selected.begin(), H_selected.end());
    sort(V_selected.begin(), V_selected.end());
    // Output
    for(int i=0;i<H_selected.size();i++) cout << H_selected[i] << (i!=H_selected.size()-1?" ":"\n");
    for(int i=0;i<V_selected.size();i++) cout << V_selected[i] << (i!=V_selected.size()-1?" ":"\n");
}