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
        int node = i + 1;
        while (node != 1) {
            route[i][length[i]++] = node;
            node = father[node - 2];
        }
    }

    vector<int> num(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int a = 0; a < length[i]; ++a) {
            int balance = 0;
            for (int b = a; b < length[i]; ++b) {
                balance += (b_num[route[i][b]] == 0) ? 1 : -1;
                if (balance == 0) num[i]++;
            }
        }
    }

    vector<int> ans(n);
    ans[0] = num[0] * 1;
    for (int i = 1; i < n; ++i) {
        ans[i] = ans[i - 1] ^ (num[i] * i);
    }

    cout << ans[n - 1] << endl;
    return 0;
}
