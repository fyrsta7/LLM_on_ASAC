#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<long long> dp_prev(n+1, 0);
    vector<long long> dp_curr(n+1, 0);
    dp_prev[1] = 1;
    for(int step=1; step<=m; step++){
        for(int i=1; i<=n; i++){
            if(dp_prev[i] > 0){
                int left = (i-2+n)%n +1;
                int right = i%n +1;
                dp_curr[left] += dp_prev[i];
                dp_curr[right] += dp_prev[i];
            }
        }
        dp_prev.assign(dp_curr.begin(), dp_curr.end());
        fill(dp_curr.begin(), dp_curr.end(), 0);
    }
    cout << dp_prev[1] << endl;
}