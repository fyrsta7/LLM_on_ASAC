#include<bits/stdc++.h>
using namespace std;

int main(){
    int N,M;
    cin>>N>>M;
    vector<int> score(N+1);
    for(int i=1;i<=N;i++) cin>>score[i];
    vector<int> cards(M);
    for(auto &x: cards) cin>>x;
    int best = INT32_MIN;
    vector<bool> used(M, false);
    // Precompute target
    // Backtracking function
    function<void(int, int, int)> backtrack = [&](int step, int current, int total)-> void{
        if(step == M){
            if(current + cards[step] == N){
                total += score[N];
                best = max(best, total);
            }
            return;
        }
        for(int i=0;i<M;i++){
            if(!used[i]){
                int next = current + cards[i];
                if(next <1 || next >N) continue;
                used[i]=true;
                backtrack(step+1, next, total + score[next]);
                used[i]=false;
            }
        };
    };
    // Modified backtrack to handle M steps and reach N
    // Alternatively, use permutation
    best = INT32_MIN;
    vector<int> perm;
    function<void(int, int, int)> dfs = [&](int step, int current, int total)-> void{
        if(step == M){
            int final = current + 0;
            if(final == N){
                best = max(best, total + score[N]);
            }
            return;
        }
        for(int i=0;i<M;i++){
            if(!used[i]){
                int next = current + cards[i];
                if(next <1 || next >N) continue;
                used[i]=true;
                dfs(step+1, next, total + score[next]);
                used[i]=false;
            }
        };
    };
    // To initiate, exactly M steps from 1 to N
    // So need current + sum(cards) = N -1
    // Implement only sequences where sum(cards) = N-1
    // Better to find all permutations where starting at 1 and ending at N
    // So the sum of cards must be N-1
    if(accumulate(cards.begin(), cards.end(), 0) != N-1){
        // Impossible
        cout<<0;
        return 0;
    }
    // Now perform DFS
    int current =1;
    int total = score[1];
    dfs(0, current, total);
    if(best == INT32_MIN) cout<<0;
    else cout<<best;
}