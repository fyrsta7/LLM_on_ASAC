#include <iostream>
#include <vector>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> kindness(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> kindness[i][j];
        }
    }

    vector<vector<int>> dp1(m, vector<int>(n, 0));
    vector<vector<int>> dp2(m, vector<int>(n, 0));
    vector<vector<int>> dp3(m, vector<int>(n, 0));
    vector<vector<int>> dp4(m, vector<int>(n, 0));

    dp1[0][0] = kindness[0][0];
    for (int i = 1; i < m; ++i) dp1[i][0] = dp1[i-1][0] + kindness[i][0];
    for (int j = 1; j < n; ++j) dp1[0][j] = dp1[0][j-1] + kindness[0][j];
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            dp1[i][j] = max(dp1[i-1][j], dp1[i][j-1]) + kindness[i][j];
        }
    }

    dp2[m-1][n-1] = kindness[m-1][n-1];
    for (int i = m-2; i >= 0; --i) dp2[i][n-1] = dp2[i+1][n-1] + kindness[i][n-1];
    for (int j = n-2; j >= 0; --j) dp2[m-1][j] = dp2[m-1][j+1] + kindness[m-1][j];
    for (int i = m-2; i >= 0; --i) {
        for (int j = n-2; j >= 0; --j) {
            dp2[i][j] = max(dp2[i+1][j], dp2[i][j+1]) + kindness[i][j];
        }
    }

    dp3[m-1][0] = kindness[m-1][0];
    for (int i = m-2; i >= 0; --i) dp3[i][0] = dp3[i+1][0] + kindness[i][0];
    for (int j = 1; j < n; ++j) dp3[m-1][j] = dp3[m-1][j-1] + kindness[m-1][j];
    for (int i = m-2; i >= 0; --i) {
        for (int j = 1; j < n; ++j) {
            dp3[i][j] = max(dp3[i+1][j], dp3[i][j-1]) + kindness[i][j];
        }
    }

    dp4[0][n-1] = kindness[0][n-1];
    for (int i = 1; i < m; ++i) dp4[i][n-1] = dp4[i-1][n-1] + kindness[i][n-1];
    for (int j = n-2; j >= 0; --j) dp4[0][j] = dp4[0][j+1] + kindness[0][j];
    for (int i = 1; i < m; ++i) {
        for (int j = n-2; j >= 0; --j) {
            dp4[i][j] = max(dp4[i-1][j], dp4[i][j+1]) + kindness[i][j];
        }
    }

    int maxKindness = 0;
    for (int i = 1; i < m-1; ++i) {
        for (int j = 1; j < n-1; ++j) {
            int kindness1 = dp1[i][j-1] + dp2[i+1][j] + dp3[i][j+1] + dp4[i-1][j];
            int kindness2 = dp1[i-1][j] + dp2[i][j+1] + dp3[i+1][j] + dp4[i][j-1];
            maxKindness = max(maxKindness, max(kindness1, kindness2));
        }
    }

    cout << maxKindness << endl;
    return 0;
}
