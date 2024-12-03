#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, p;
    cin >> n >> p;
    vector<int> a(n);
    for(auto &x: a) cin >> x;
    vector<int> character(n, 0);
    // Compute character[i] using Kadane's algorithm
    int current_sum = a[0];
    character[0] = current_sum;
    for(int i=1;i<n;i++){
        current_sum = max(a[i], current_sum + a[i]);
        character[i] = max(character[i-1], current_sum);
    }
    // Compute score[i]
    vector<long long> score(n, 0);
    score[0] = character[0];
    long long current_max = (long long)character[0] + score[0];
    for(int i=1;i<n;i++){
        score[i] = current_max;
        current_max = max(current_max, (long long)character[i] + score[i]);
    }
    // Find the maximum score
    long long max_score = score[0];
    for(int i=1;i<n;i++) max_score = max(max_score, score[i]);
    // Compute ans
    long long ans = max_score % p;
    cout << ans;
}