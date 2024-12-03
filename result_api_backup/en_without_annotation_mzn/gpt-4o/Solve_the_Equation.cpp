#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> coefficient(n + 1);
    for (int i = 0; i <= n; ++i) {
        cin >> coefficient[i];
    }
    
    vector<int> solutions;
    for (int i = 1; i <= m; ++i) {
        int sum = 0;
        for (int j = 0; j <= n; ++j) {
            sum += coefficient[j] * pow(i, j);
        }
        if (sum == 0) {
            solutions.push_back(i);
        }
    }
    
    cout << solutions.size() << "\n";
    for (int i = 0; i < solutions.size(); ++i) {
        cout << solutions[i] << "\n";
    }
    
    return 0;
}