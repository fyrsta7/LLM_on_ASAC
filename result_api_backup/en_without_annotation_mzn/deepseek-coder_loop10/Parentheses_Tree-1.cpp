#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> bracket(n);
    vector<int> father(n - 1);
    for (int i = 0; i < n; ++i) cin >> bracket[i];
    for (int i = 0; i < n - 1; ++i) cin >> father[i];

    vector<int> b_num(n);
    for (int i = 0; i < n; ++i) b_num[i] = (bracket[i] == "(") ? 0 : 1;

    vector<vector<int>> route(n, vector<int>(n, 1));
    vector<int> length(n, 1);
    for (int i = 0; i < n; ++i) {
        route[i][0] = 1;
        route[i][1] = i + 1;
        length[i] = 2;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < length[i] - 1; ++j) {
            route[i][j + 1] = father[route[i][j] - 1];
        }
    }

    vector<int> num(n, 0);
    for (int i = 0; i < n; ++i) {
        stack<int> s;
        for (int j = 0; j < length[i]; ++j) {
            if (b_num[route[i][j] - 1] == 0) {
                s.push(route[i][j] - 1);
            } else {
                if (!s.empty()) {
                    s.pop();
                    if (s.empty()) num[i]++;
                }
            }
        }
    }

    vector<int> ans(n);
    ans[0] = num[0];
    for (int i = 1; i < n; ++i) {
        ans[i] = ans[i - 1] ^ (num[i] * i);
    }

    cout << ans[n - 1] << endl;
    return 0;
}