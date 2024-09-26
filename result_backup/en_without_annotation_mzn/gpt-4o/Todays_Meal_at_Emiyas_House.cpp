#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 998244353;

int n, m;
vector<vector<int>> a;
vector<vector<pair<int, int>>> plans;
vector<int> methods;
int num = 0;
int result = 0;

bool isValidPlan(const vector<pair<int, int>>& plan) {
    // Check if rows and columns are unique
    vector<bool> rowCheck(n + 1, false), colCheck(m + 1, false);
    for (const auto& p : plan) {
        if (rowCheck[p.first] || colCheck[p.second]) return false;
        rowCheck[p.first] = true;
        colCheck[p.second] = true;
    }

    // Check if values in the plan are positive
    for (const auto& p : plan) {
        if (a[p.first - 1][p.second - 1] <= 0) return false;
    }

    // Check if the number of dishes in each column is at most half the total number
    vector<int> colCount(m + 1, 0);
    for (const auto& p : plan) {
        colCount[p.second]++;
    }
    for (int j = 1; j <= m; j++) {
        if (colCount[j] > int(plan.size() / 2)) return false;
    }

    return true;
}

void generatePlans(vector<pair<int, int>>& current, int row) {
    if (row > n) {
        if (isValidPlan(current)) {
            plans.push_back(current);
            int method = 1;
            for (const auto& p : current) {
                method = (1LL * method * a[p.first - 1][p.second - 1]) % MOD;
            }
            methods.push_back(method);
            num++;
        }
        return;
    }

    for (int col = 1; col <= m; col++) {
        current.push_back({row, col});
        generatePlans(current, row + 1);
        current.pop_back();
    }
    generatePlans(current, row + 1);
}

int main() {
    cin >> n >> m;
    a.resize(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    vector<pair<int, int>> current;
    generatePlans(current, 1);

    for (int i = 0; i < num; i++) {
        result = (result + methods[i]) % MOD;
    }

    cout << result << endl;
    return 0;
}