#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct Passenger {
    int T;
    int A;
    int B;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    long long k;
    cin >> n >> m >> k;
    vector<int> D(n);
    for(int i=1;i<=n-1;i++) cin >> D[i];
    // Initialize max_T
    vector<int> max_T(n+1, 0);
    // Initialize diff for cnt_j
    vector<int> diff(n+2, 0);
    // List of passengers
    vector<Passenger> passengers(m);
    for(int i=0;i<m;i++){
        cin >> passengers[i].T >> passengers[i].A >> passengers[i].B;
        diff[passengers[i].A]++;
        diff[passengers[i].B]--;
        if(passengers[i].T > max_T[passengers[i].A]){
            max_T[passengers[i].A] = passengers[i].T;
        }
    }
    // Compute cnt_j using prefix sum
    vector<int> cnt(n, 0);
    int acc =0;
    for(int j=1; j<=n-1;j++){
        acc += diff[j];
        cnt[j] = acc;
    }
    // Create list of j sorted by (cnt[j] desc, j desc)
    vector<int> sorted_j;
    for(int j=1;j<=n-1;j++) sorted_j.push_back(j);
    sort(sorted_j.begin(), sorted_j.end(), [&](const int a, const int b) -> bool{
        if(cnt[a] != cnt[b]) return cnt[a] > cnt[b];
        return a > b;
    });
    // Assign accelerators
    for(auto j: sorted_j){
        if(k ==0) break;
        if(D[j] ==0) continue;
        long long c = min((long long)D[j], k);
        D[j] -= c;
        k -= c;
        if(k ==0) break;
    }
    // Compute departure_time and arrival_time
    vector<long long> arrival_time(n+2, 0);
    vector<long long> departure_time(n+1, 0);
    arrival_time[1] =0;
    for(int s=1;s<=n;s++){
        if(s <=n){
            departure_time[s] = max((long long)arrival_time[s], (long long)max_T[s]);
            if(s <=n-1){
                arrival_time[s+1] = departure_time[s] + (long long)D[s];
            }
        }
    }
    // Compute total sum
    long long total =0;
    for(int i=0;i<m;i++){
        int B = passengers[i].B;
        long long at_B = arrival_time[B];
        total += (at_B - (long long)passengers[i].T);
    }
    cout << total;
}