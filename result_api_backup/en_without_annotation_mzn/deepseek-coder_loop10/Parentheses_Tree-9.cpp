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

    vector<vector<int>> route(n, vector<int>(n, 1));
    vector<int> length(n, 1);
    for (int i = 1; i < n; ++i) {
        route[i][1] = i + 1;
        length[i] = 2;
    }

    for (int i = 0; i < n; ++i) {
        int current = i + 1;
        while (current != 1) {
            current = father[current - 2];
            route[i][length[i]++] = current;
        }
    }

    vector<int> num(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int a = 0; a < length[i]; ++a) {
            int open = 0, close = 0;
            for (int b = a; b < length[i]; ++b) {
                if (b_num[route[i][b] - 1] == 0) open++;
                else close++;
                if (open == close) num[i]++;
            }
        }
    }

    vector<int> ans(n);
    ans[0] = num[0] * 1;
    for (int i = 1; i < n; ++i) {
        ans[i] = ans[i - 1] ^ (num[i] * (i + 1));
    }

    cout << ans[n - 1] << endl;
    return 0;
}
