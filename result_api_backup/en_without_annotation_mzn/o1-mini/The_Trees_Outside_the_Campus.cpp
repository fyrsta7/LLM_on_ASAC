#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    long long L;
    int M;
    cin >> L >> M;
    vector<pair<long long, long long>> intervals;
    for(int i=0;i<M;i++){
        long long a, b;
        cin >> a >> b;
        a = max(a, (long long)0);
        b = min(b, L);
        if(a > b) continue;
        intervals.emplace_back(a, b);
    }
    if(intervals.empty()){
        cout << L+1;
        return 0;
    }
    sort(intervals.begin(), intervals.end());
    long long total = 0;
    long long current_start = intervals[0].first;
    long long current_end = intervals[0].second;
    for(int i=1;i<intervals.size();i++){
        if(intervals[i].first <= current_end + 1){
            current_end = max(current_end, intervals[i].second);
        }
        else{
            total += (current_end - current_start + 1);
            current_start = intervals[i].first;
            current_end = intervals[i].second;
        }
    }
    total += (current_end - current_start + 1);
    long long cnt = (L+1) - total;
    cout << cnt;
}