#include <iostream>
#include <vector>
#include <string>
using namespace std;

int mod = 10007;

int evaluate(int a, char op, int b) {
    if (op == '*')
        return a * b;
    else // op == '+'
        return a + b - a * b;
}

int countWays(string s, int l) {
    int n = l + 1;
    vector<vector<int>> zero(n, vector<int>(n, 0)), one(n, vector<int>(n, 0));
    
    // Base cases: Single bit can be either 0 or 1
    for (int i = 0; i < n; i++) {
        zero[i][i] = 1;
        one[i][i] = 1;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            zero[i][j] = 0;
            one[i][j] = 0;
            for (int k = i; k < j; k++) {
                if (s[k] != '+' && s[k] != '*') continue;
                char op = s[k];
                int totalZero = 0, totalOne = 0;
                int z1 = zero[i][k], o1 = one[i][k],
                    z2 = zero[k + 1][j], o2 = one[k + 1][j];

                totalZero += (z1 * z2) % mod;
                totalZero += (o1 * o2 * (op == '*')) % mod;
                totalZero += (o1 * z2 * (op == '^')) % mod;
                totalZero += (z1 * o2 * (op == '^')) % mod;

                totalOne += (o1 * z2 * (op == '*')) % mod;
                totalOne += (z1 * o2 * (op == '*')) % mod;
                totalOne += (o1 * o2 * (op != '*')) % mod;
                totalOne += (z1 * z2 * (op == '+')) % mod;

                zero[i][j] = (zero[i][j] + totalZero) % mod;
                one[i][j] = (one[i][j] + totalOne) % mod;
            }
        }
    }

    return zero[0][n - 1];
}

int main() {
    int L;
    string expr;
    cin >> L;
    cin >> expr;
    
    expr = expr + '+';
    
    cout << countWays(expr, L) << endl;
    
    return 0;
}