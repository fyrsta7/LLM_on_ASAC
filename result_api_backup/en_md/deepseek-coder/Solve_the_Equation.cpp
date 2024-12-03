#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<int> solveEquation(int n, int m, vector<int>& coefficients) {
    vector<int> solutions;
    for (int x = 1; x <= m; ++x) {
        long long sum = 0;
        for (int i = n; i >= 0; --i) {
            sum = sum * x + coefficients[i];
        }
        if (sum == 0) {
            solutions.push_back(x);
        }
    }
    return solutions;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> coefficients(n + 1);
    for (int i = 0; i <= n; ++i) {
        cin >> coefficients[i];
    }

    vector<int> solutions = solveEquation(n, m, coefficients);

    cout << solutions.size() << endl;
    for (int solution : solutions) {
        cout << solution << endl;
    }

    return 0;
}
