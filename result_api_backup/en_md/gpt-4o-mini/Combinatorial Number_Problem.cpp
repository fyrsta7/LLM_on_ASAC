#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 2000;

vector<vector<long long>> C(MAX_N + 1, vector<long long>(MAX_N + 1));

void precompute() {
    for (int i = 0; i <= MAX_N; ++i) {
        C[i][0] = 1; // C(i, 0) = 1
        for (int j = 1; j <= i; ++j) {
            C[i][j] = C[i-1][j-1] + C[i-1][j]; // Pascal's triangle
        }
    }
}

int main() {
    precompute();
    
    int t, k;
    cin >> t >> k;
    
    while (t--) {
        int n, m;
        cin >> n >> m;
        
        int count = 0;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= min(i, m); ++j) {
                if (C[i][j] % k == 0) {
                    count++;
                }
            }
        }
        
        cout << count << endl;
    }

    return 0;
}