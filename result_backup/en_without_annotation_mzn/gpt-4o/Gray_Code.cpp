#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to generate Gray code recursively
void generateGrayCode(int n, vector<vector<int>>& gray) {
    gray[0][0] = 0;
    gray[0][1] = 1;
    for (int i = 1; i < n; ++i) {
        int len = 1 << i;
        for (int j = 0; j < len; ++j) {
            gray[i][j] = gray[i - 1][j];
            gray[i][2 * len - j - 1] = 1 ^ gray[i - 1][j];
        }
    }
}

int main() {
    int n, k;
    cin >> n >> k;

    int max_n = pow(2, n);    
    vector<vector<int>> gray(n, vector<int>(max_n, 0));

    generateGrayCode(n, gray);

    for (int i = 0; i < n; ++i) {
        cout << gray[n - 1][k] % 2;
        k /= 2;
    }
    cout << endl;

    return 0;
}