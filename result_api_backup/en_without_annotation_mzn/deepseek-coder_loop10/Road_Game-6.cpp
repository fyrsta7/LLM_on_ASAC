#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, p;
    cin >> n >> m >> p;
    
    vector<vector<int>> coins(n, vector<int>(m));
    vector<int> cost(n);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> coins[i][j];
        }
    }
    
    for (int i = 0; i < n; ++i) {
        cin >> cost[i];
    }
    
    int maxBenefit = 0;
    
    for (int strategy = 1; strategy <= n; ++strategy) {
        for (int runtime = 1; runtime <= m; ++runtime) {
            if (runtime * strategy > m) break;
            
            int totalCoins = 0;
            int totalCost = 0;
            
            for (int i = 0; i < runtime; ++i) {
                int location = (strategy - 2 + i) % n + 1;
                totalCoins += coins[location - 1][i];
            }
            
            totalCost = cost[strategy - 1];
            
            int benefit = totalCoins - totalCost;
            maxBenefit = max(maxBenefit, benefit);
        }
    }
    
    cout << maxBenefit << endl;
    
    return 0;
}