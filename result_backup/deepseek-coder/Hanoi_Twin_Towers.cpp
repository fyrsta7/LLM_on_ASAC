#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<long long> dp(n + 1);
    dp[1] = 2;
    
    for (int i = 2; i <= n; ++i) {
        dp[i] = 3 * dp[i - 1] + 2;
    }
    
    cout << dp[n] << endl;
    return 0;
}
