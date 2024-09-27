#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int sticks[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int use_sticks(int num) {
    int total = 0;
    while (num > 0) {
        total += sticks[num % 10];
        num /= 10;
    }
    return total;
}

bool is_valid(int a, int b, int c, int n) {
    return use_sticks(a) + use_sticks(b) + use_sticks(c) + 4 == n;
}

int main() {
    int n, L = 150;
    cin >> n;

    vector<vector<int>> equations;
    for (int a = 0; a <= 100; ++a) {
        for (int b = 0; b <= 100; ++b) {
            int c = a + b;
            if (c <= 100 && is_valid(a, b, c, n)) {
                equations.push_back({a, b, c});
            }
        }
    }

    int ans = 0;
    vector<bool> used(101, false);
    for (const auto& eq : equations) {
        if (!used[eq[0]] && !used[eq[1]] && !used[eq[2]]) {
            used[eq[0]] = used[eq[1]] = used[eq[2]] = true;
            ++ans;
        }
    }

    cout << ans << endl;
    return 0;
}
