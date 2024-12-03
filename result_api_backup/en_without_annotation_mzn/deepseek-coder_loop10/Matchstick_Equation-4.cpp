#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int sticks[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
const int L = 150;

int use_sticks(int num) {
    int total = 0;
    while (num > 0) {
        total += sticks[num % 10];
        num /= 10;
    }
    return total;
}

bool different(const vector<int>& a, const vector<int>& b) {
    return !(a[0] == b[0] && a[1] == b[1] && a[2] == b[2]);
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> equation(L, vector<int>(3));
    int ans = 0;

    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < L; ++j) {
            for (int k = 0; k < L; ++k) {
                if (i + j == k) {
                    vector<int> eq = {i, j, k};
                    bool unique = true;
                    for (int l = 0; l < ans; ++l) {
                        if (!different(equation[l], eq)) {
                            unique = false;
                            break;
                        }
                    }
                    if (unique && use_sticks(i) + use_sticks(j) + use_sticks(k) + 4 == n) {
                        equation[ans] = eq;
                        ++ans;
                    }
                }
            }
        }
    }

    cout << ans << endl;
    return 0;
}
