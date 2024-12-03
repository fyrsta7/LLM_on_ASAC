#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n;
vector<string> bracket;
vector<int> father;
vector<int> b_num;
vector<vector<int>> route;
vector<int> length;
vector<int> num;
vector<int> ans;

bool valid(const vector<int>& x, int start, int end) {
    int count0 = 0, count1 = 0;
    for (int i = start; i <= end; ++i) {
        if (x[i] == 0) count0++;
        else count1++;
    }
    if (count0 != count1) return false;
    int open = 0;
    for (int i = start; i <= end; ++i) {
        if (x[i] == 0) open++;
        else {
            open--;
            if (open < 0) return false;
        }
    }
    return true;
}

int bitwise_xor(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    return ((a % 2) + (b % 2)) % 2 + 2 * bitwise_xor(a / 2, b / 2);
}

int main() {
    cin >> n;
    bracket.resize(n);
    father.resize(n - 1);
    b_num.resize(n);
    route.resize(n, vector<int>(n));
    length.resize(n);
    num.resize(n);
    ans.resize(n);

    for (int i = 0; i < n; ++i) {
        cin >> bracket[i];
        b_num[i] = (bracket[i] == "(") ? 0 : 1;
    }

    for (int i = 0; i < n - 1; ++i) {
        cin >> father[i];
    }

    for (int i = 0; i < n; ++i) {
        route[i][0] = 0;
        int current = i;
        int len = 1;
        while (current != 0) {
            route[i][len] = current;
            current = father[current - 1];
            len++;
        }
        route[i][len] = 0;
        length[i] = len;
    }

    for (int i = 0; i < n; ++i) {
        num[i] = 0;
        for (int a = 0; a < length[i]; ++a) {
            for (int b = a; b < length[i]; ++b) {
                if (valid(b_num, route[i][a], route[i][b])) {
                    num[i]++;
                }
            }
        }
    }

    ans[0] = num[0] * 1;
    for (int i = 1; i < n; ++i) {
        ans[i] = bitwise_xor(ans[i - 1], num[i] * (i + 1));
    }

    cout << ans[n - 1] << endl;

    return 0;
}
