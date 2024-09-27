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
    for (int i = 0; i < n; ++i) {
        cin >> bracket[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        cin >> father[i];
    }

    vector<int> b_num(n);
    for (int i = 0; i < n; ++i) {
        b_num[i] = (bracket[i] == "(") ? 0 : 1;
    }

    vector<vector<int>> route(n, vector<int>(n, 0));
    vector<int> length(n, 0);
    vector<int> num(n, 0);
    vector<int> ans(n, 0);

    for (int i = 0; i < n; ++i) {
        route[i][0] = 0;
        int current = i;
        int len = 1;
        while (current != 0) {
            route[i][len++] = father[current - 1];
            current = father[current - 1];
        }
        length[i] = len;
        reverse(route[i].begin(), route[i].begin() + len);
    }

    for (int i = 0; i < n; ++i) {
        stack<int> s;
        for (int j = 0; j < length[i]; ++j) {
            if (b_num[route[i][j]] == 0) {
                s.push(j);
            } else {
                if (!s.empty()) {
                    s.pop();
                    if (s.empty()) {
                        num[i]++;
                    }
                }
            }
        }
    }

    ans[0] = num[0] * 1;
    for (int i = 1; i < n; ++i) {
        ans[i] = ans[i - 1] ^ (num[i] * i);
    }

    cout << ans[n - 1] << endl;
    return 0;
}
