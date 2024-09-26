#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, S;
    cin >> n >> m >> S;
    vector<pair<int, int>> ores(n);
    vector<int> all_W;
    for(int i=0;i<n;i++){
        cin >> ores[i].first >> ores[i].second;
        all_W.push_back(ores[i].first);
    }
    vector<pair<int, int>> intervals(m);
    for(int i=0;i<m;i++) cin >> intervals[i].first >> intervals[i].second;
    // Get unique sorted W descending
    sort(all_W.begin(), all_W.end(), greater<int>());
    all_W.erase(unique(all_W.begin(), all_W.end()), all_W.end());
    // For each interval, sort ores[j] in [L,R] descending by W and compute prefix sums
    struct IntervalData {
        vector<int> sorted_W;
        vector<long long> prefix_sum;
    };
    vector<IntervalData> interval_data(m, IntervalData());
    for(int i=0;i<m;i++){
        int L = intervals[i].first-1;
        int R = intervals[i].second-1;
        vector<pair<int, int>> temp;
        for(int j=L; j<=R; j++) temp.emplace_back(ores[j].first, ores[j].second);
        sort(temp.begin(), temp.end(), [&](const pair<int,int> &a, const pair<int,int> &b)->bool{
            if(a.first != b.first) return a.first > b.first;
            return a.second > b.second;
        });
        interval_data[i].sorted_W.resize(temp.size());
        interval_data[i].prefix_sum.resize(temp.size()+1, 0);
        for(int k=0;k<temp.size();k++){
            interval_data[i].sorted_W[k] = temp[k].first;
            interval_data[i].prefix_sum[k+1] = interval_data[i].prefix_sum[k] + (long long)temp[k].second;
        }
    }
    long long min_diff = LLONG_MAX;
    for(auto W: all_W){
        long long Y = 0;
        for(int i=0;i<m;i++){
            // Binary search in interval_data[i].sorted_W for first < W
            int pos = lower_bound(interval_data[i].sorted_W.begin(), interval_data[i].sorted_W.end(), W, greater<int>()) - interval_data[i].sorted_W.begin();
            // All sorted_W[0..pos-1] >= W
            // pos is first index where sorted_W[pos] < W
            Y += ((long long)pos) * ((long long)interval_data[i].prefix_sum[pos]);
        }
        long long diff = abs((long long)S - Y);
        if(diff < min_diff){
            min_diff = diff;
        }
    }
    cout << min_diff;
}