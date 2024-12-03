#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<int> H(N+1);
    for(int i=1;i<=N;i++) cin >> H[i];
    int X0;
    cin >> X0; // Unused in MiniZinc
    int M;
    cin >> M;
    vector<int> S(M), X(M);
    for(int i=0;i<M;i++) cin >> S[i];
    for(int i=0;i<M;i++) cin >> X[i];
    // Precompute nearest and second_nearest for each city
    // For each city, find all j > i, sort by (d(i,j), H[j]), pick first and second
    vector<pair<int, int>> nearest(N+1, {N+1, N+1});
    vector<pair<int, int>> second_nearest(N+1, {N+1, N+1});
    for(int i=1;i<=N;i++){
        vector<pair<int, int>> candidates;
        for(int j=i+1;j<=N;j++){
            candidates.emplace_back(abs(H[i]-H[j]), H[j]);
        }
        sort(candidates.begin(), candidates.end(), [&](const pair<int,int> &a,const pair<int,int> &b)->bool{
            if(a.first != b.first) return a.first < b.first;
            return a.second < b.second;
        });
        if(candidates.size() >=1){
            // Find the j corresponding to the first candidate
            for(int j=i+1;j<=N;j++) {
                if(abs(H[i]-H[j]) == candidates[0].first && H[j]==candidates[0].second){
                    nearest[i] = {candidates[0].first, j};
                    break;
                }
            }
        }
        if(candidates.size() >=2){
            for(int j=i+1;j<=N;j++) {
                if(abs(H[i]-H[j]) == candidates[1].first && H[j]==candidates[1].second){
                    second_nearest[i] = {candidates[1].first, j};
                    break;
                }
            }
        }
        if(candidates.size()==1){
            second_nearest[i] = {N+1, N+1};
        }
        if(candidates.empty()){
            nearest[i] = {N+1, N+1};
            second_nearest[i] = {N+1, N+1};
        }
    }
    // Travel function
    // For each query, simulate the travel
    // Alternately plan_A (second_nearest) and plan_B (nearest)
    // Sum distances on odd and even days separately
    vector<pair<long long, long long>> ans(M, {0, 0});
    for(int q=0;q<M;q++){
        int start = S[q];
        int limit = X[q];
        long long total = 0;
        long long dist1 = 0, dist2 = 0;
        int current = start;
        int day =1;
        while(true){
            if(day%2==1){
                // plan_A: second_nearest
                int next = second_nearest[current].second;
                if(next > N){
                    break;
                }
                int d = abs(H[current]-H[next]);
                if(total + d > limit){
                    break;
                }
                dist1 += d;
                total += d;
                current = next;
            }
            else{
                // plan_B: nearest
                int next = nearest[current].second;
                if(next > N){
                    break;
                }
                int d = abs(H[current]-H[next]);
                if(total + d > limit){
                    break;
                }
                dist2 += d;
                total += d;
                current = next;
            }
            day++;
        }
        ans[q] = {dist1, dist2};
    }
    for(int q=0;q<M;q++) cout << ans[q].first << " , " << ans[q].second << "\n";
}