#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> coefficient(n + 1);
    for (int i = 0; i <= n; ++i) {
        cin >> coefficient[i];
    }

    vector<bool> if_solution(m + 1, false);
    int solution_num = 0;

    for (int i = 1; i <= m; ++i) {
        int sum = 0;
        for (int j = 0; j <= n; ++j) {
            sum += coefficient[j] * pow(i, j);
        }
        if (sum == 0) {
            if_solution[i] = true;
            ++solution_num;
        }
    }

    cout << solution_num << endl;
    for (int i = 1; i <= m; ++i) {
        if (if_solution[i]) {
            cout << i << endl;
        }
    }

    return 0;
}