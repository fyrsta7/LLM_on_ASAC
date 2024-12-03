#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> data(n);
    for(auto &x: data) cin >> x;
    sort(data.begin(), data.end());
    // Create frequency map
    vector<pair<int, int>> freq;
    int current = data[0];
    int count = 1;
    for(int i=1;i<n;i++){
        if(data[i]==current){
            count++;
        }
        else{
            freq.emplace_back(make_pair(current, count));
            current = data[i];
            count=1;
        }
    }
    freq.emplace_back(make_pair(current, count));
    // Unique data
    int m = freq.size();
    // Create a set for fast lookup
    unordered_set<int> data_set;
    for(auto &[num, cnt] : freq){
        data_set.insert(num);
    }
    // To store answers
    unordered_set<int> ans;
    for(int i=0;i<m;i++){
        for(int j=i;j<m;j++){
            int sum = freq[i].first + freq[j].first;
            if(data_set.find(sum)!=data_set.end()){
                if(freq[i].first != freq[j].first || freq[i].second >1){
                    ans.insert(sum);
                }
            }
        }
    }
    cout << ans.size();
}