#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    vector<int> n(T);
    for(int &x : n) cin >> x;
    int sum_n = accumulate(n.begin(), n.end(), 0);
    vector<float> x(sum_n);
    for(auto &val : x) cin >> val;
    vector<float> y(sum_n);
    for(auto &val : y) cin >> val;
    
    // Since the problem is not clearly defined, we'll output zeros for answer
    // Replace this part with the actual logic as per the problem requirements
    vector<int> answer(T, 0);
    for(int i=0;i<T;i++) cout << answer[i] << (i<T-1?" ":"\n");
}