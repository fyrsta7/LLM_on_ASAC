#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> D(n-1);
    for(auto &x:D) cin >> x;
    vector<int> T(m), A(m), B(m);
    for(auto &x:T) cin >> x;
    for(auto &x:A) cin >> x;
    for(auto &x:B) cin >> x;
    // Compute max_T for each node
    vector<int> max_T(n+1, 0);
    for(int j=0;j<m;j++) max_T[A[j]] = max(max_T[A[j]], T[j]);
    // Compute count for each edge
    // Assuming path from 1 to n
    // For each edge i (1..n-1), count number of B[j] >=i+1
    vector<long long> count(n, 0);
    for(int j=0;j<m;j++) {
        if(B[j]>=1 && B[j]<=(n)) count[ B[j]-1 ] +=1;
    }
    // Sort edges by count descending
    vector<int> indices(n-1);
    for(int i=0;i<n-1;i++) indices[i]=i;
    sort(indices.begin(), indices.end(), [&](const int a, const int b) -> bool{
        return count[a] > count[b];
    });
    // Assign save_time
    vector<int> save_time(n-1, 0);
    int remaining_k = k;
    for(auto i:indices){
        if(remaining_k ==0) break;
        int s = min(D[i], remaining_k);
        save_time[i] = s;
        remaining_k -=s;
    }
    // Compute arrive_time
    vector<long long> arrive_time(n+1, 0);
    arrive_time[1] =0;
    for(int i=1;i<n;i++){
        // depart_time[i] = max(arrive_time[i], max_T[i])
        long long depart = max(arrive_time[i], (long long)max_T[i]);
        // arrive_time[i+1] = max(arrive_time[i] +1, depart + D[i-1] - save_time[i-1])
        long long option1 = arrive_time[i] +1;
        long long option2 = depart + (long long)D[i-1] - (long long)save_time[i-1];
        arrive_time[i+1] = max(option1, option2);
    }
    // Compute travel_time
    long long travel_time=0;
    for(int j=0;j<m;j++) travel_time += (arrive_time[B[j]] - (long long)T[j]);
    cout << travel_time;
}