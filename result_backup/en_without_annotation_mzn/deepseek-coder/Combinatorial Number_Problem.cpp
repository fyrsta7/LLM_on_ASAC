#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 100000;
const int MAXK = 1000000;

vector<int> factorial(MAXN + 1, 1);
vector<vector<int>> binomial(MAXN + 1, vector<int>(MAXN + 1, 1));

void precompute(int K) {
    for (int i = 2; i <= MAXN; ++i) {
        factorial[i] = (factorial[i - 1] * i) % K;
    }
    for (int i = 0; i <= MAXN; ++i) {
        for (int j = 1; j < i; ++j) {
            binomial[i][j] = (binomial[i - 1][j - 1] + binomial[i - 1][j]) % K;
        }
    }
}

int count_divisible(int n, int m, int K) {
    int count = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= min(i, m); ++j) {
            if (binomial[i][j] == 0) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int T, K;
    cin >> T >> K;
    vector<int> n(T), m(T);
    for (int i = 0; i < T; ++i) {
        cin >> n[i] >> m[i];
    }

    precompute(K);

    vector<int> ans(T);
    for (int i = 0; i < T; ++i) {
        ans[i] = count_divisible(n[i], m[i], K);
    }

    for (int i = 0; i < T; ++i) {
        cout << ans[i] << endl;
    }

    return 0;
}
