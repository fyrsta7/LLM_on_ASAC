#include <iostream>
#include <vector>
using namespace std;

int factorial(int x) {
    if (x == 0) return 1;
    int result = 1;
    for (int i = 1; i <= x; ++i) {
        result *= i;
    }
    return result;
}

int main() {
    int T, K;
    cin >> T >> K;
    
    vector<int> n(T), m(T), ans(T);
    
    for (int t = 0; t < T; ++t) {
        cin >> n[t] >> m[t];
    }
    
    for (int t = 0; t < T; ++t) {
        int count = 0;
        for (int i = 1; i <= n[t]; ++i) {
            for (int j = 1; j <= m[t]; ++j) {
                if (j <= i) {
                    int comb = factorial(i) / (factorial(j) * factorial(i - j));
                    if (comb % K == 0) {
                        ++count;
                    }
                }
            }
        }
        ans[t] = count;
    }
    
    for (int t = 0; t < T; ++t) {
        cout << ans[t] << " ";
    }
    cout << endl;
    
    return 0;
}