#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool check(vector<int>& mapping, vector<string>& formula, int n) {
    vector<int> carry(n + 1, 0);
    for (int i = n - 1; i >= 0; --i) {
        int sum = carry[i + 1];
        sum += mapping[formula[0][i] - 'A'];
        sum += mapping[formula[1][i] - 'A'];
        if (sum % n != mapping[formula[2][i] - 'A']) return false;
        carry[i] = sum / n;
    }
    return carry[0] == 0;
}

bool solve(vector<int>& mapping, vector<bool>& used, vector<string>& formula, int n, int pos) {
    if (pos == n) return check(mapping, formula, n);

    for (int i = 0; i < n; ++i) {
        if (used[i]) continue;
        mapping[pos] = i;
        used[i] = true;
        if (solve(mapping, used, formula, n, pos + 1)) return true;
        used[i] = false;
    }
    return false;
}

int main() {
    int n;
    cin >> n;
    vector<string> formula(3);
    for (int i = 0; i < 3; ++i) cin >> formula[i];

    vector<int> mapping(26, -1);
    vector<bool> used(n, false);

    solve(mapping, used, formula, n, 0);

    for (int i = 0; i < n; ++i) {
        if (i) cout << " ";
        cout << mapping[i];
    }
    cout << endl;

    return 0;
}