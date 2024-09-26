#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<long long> time(n);
    for(auto &x: time) cin >> x;
    vector<int> passenger(n);
    for(auto &x: passenger) cin >> x;
    vector<vector<int>> countries(n);
    vector<int> all_countries;
    for(int i=0;i<n;i++){
        int c;
        cin >> c;
        countries[i].reserve(c);
        for(int j=0;j<c;j++){
            int country;
            cin >> country;
            countries[i].push_back(country);
            all_countries.push_back(country);
        }
    }
    // Remove duplicates and sort
    sort(all_countries.begin(), all_countries.end());
    all_countries.erase(unique(all_countries.begin(), all_countries.end()), all_countries.end());
    int m = all_countries.size();
    // Map country id to index
    unordered_map<int, int> country_map;
    for(int i=0;i<m;i++) country_map[all_countries[i]] = i;
    // Convert countries to mapped indices
    vector<vector<int>> mapped_countries(n, vector<int>());
    for(int i=0;i<n;i++) {
        for(auto &c: countries[i]){
            mapped_countries[i].push_back(country_map[c]);
        }
    }
    // Sliding window
    vector<int> result(n,0);
    vector<int> freq(m, 0);
    int unique_count =0;
    int left=0;
    for(int right=0;right<n;right++){
        for(auto &c: mapped_countries[right]){
            if(++freq[c]==1) unique_count++;
        }
        while(left <= right && time[right] - time[left] >= 86400){
            for(auto &c: mapped_countries[left]){
                if(--freq[c]==0) unique_count--;
            }
            left++;
        }
        result[right] = unique_count;
    }
    for(int i=0;i<n;i++) cout << result[i] << (i<n-1?" ":"\n");
}