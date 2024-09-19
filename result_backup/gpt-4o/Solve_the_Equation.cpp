#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> coefficients(n + 1);
    for (int i = 0; i <= n; i++) {
        cin >> coefficients[i];
    }

    vector<int> solutions;
    for (int x = 1; x <= m; x++) {
        long long sum = 0;
        long long term = 1;
        for (int i = 0; i <= n; i++) {
            sum += coefficients[i] * term;
            term *= x;
        }
        if (sum == 0) {
            solutions.push_back(x);
        }
    }

    cout << solutions.size() << endl;
    for (int sol : solutions) {
        cout << sol << endl;
    }

    return 0;
}