#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int sticks[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int use_sticks(int num) {
    int count = 0;
    while (num > 0) {
        count += sticks[num % 10];
        num /= 10;
    }
    return count;
}

int main() {
    int n, L = 150;
    cin >> n;

    vector<vector<int>> equations;
    int ans = 0;

    for (int a = 0; a <= 100; ++a) {
        for (int b = 0; b <= 100; ++b) {
            int c = a + b;
            if (c > 100) continue;
            int total_sticks = use_sticks(a) + use_sticks(b) + use_sticks(c) + 4;
            if (total_sticks == n) {
                bool unique = true;
                for (const auto& eq : equations) {
                    if (eq[0] == a && eq[1] == b && eq[2] == c) {
                        unique = false;
                        break;
                    }
                }
                if (unique) {
                    equations.push_back({a, b, c});
                    ans++;
                }
            }
        }
    }

    cout << ans << endl;
    return 0;
}
