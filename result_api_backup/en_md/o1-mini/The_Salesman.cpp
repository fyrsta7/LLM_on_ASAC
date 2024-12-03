#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<int> S(N);
    for(auto &x:S) cin>>x;
    vector<int> A(N);
    for(auto &x:A) cin>>x;
    vector<long long> answer(N+1, 0);
    int counts[1001] = {0};
    for(int i=0;i<N;i++){
        counts[A[i]]++;
        long long sum =0;
        int X=0;
        for(int a=1000;a>=1;a--){
            if(counts[a]==0) continue;
            int cnt = counts[a];
            for(int k=0; k<cnt; k++){
                X++;
                sum +=a;
                if(X > N) break;
                if(sum + 2LL * S[i] > answer[X]) answer[X] = sum + 2LL * S[i];
                if(X == i+1) break;
            }
            if(X == i+1) break;
        }
    }
    for(int x=1;x<=N;x++) cout << answer[x] << "\n";
}