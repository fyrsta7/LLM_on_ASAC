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
        int current = i + 1;
        for (int j = 1; j < n; ++j) {
            route[i][j] = current;
            if (current == 1) break;
            current = father[current - 2];
        }
        length[i] = current;
    }

    auto valid = [&](const vector<int>& x) {
        int count0 = 0, count1 = 0;
        for (int v : x) {
            if (v == 0) count0++;
            else count1++;
        }
        if (count0 != count1) return false;
        stack<int> st;
        for (int v : x) {
            if (v == 0) st.push(v);
            else {
                if (st.empty()) return false;
                st.pop();
            }
        }
        return st.empty();
    };

    vector<int> num(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int a = 0; a < length[i]; ++a) {
            for (int b = a; b < length[i]; ++b) {
                vector<int> subarray(b_num.begin() + route[i][a] - 1, b_num.begin() + route[i][b]);
                if (valid(subarray)) num[i]++;
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
