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

    vector<vector<int>> equations(L, vector<int>(3));
    int ans = 0;

    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < L; ++j) {
            for (int k = 0; k < L; ++k) {
                if (i + j == k) {
                    int total_sticks = use_sticks(i) + use_sticks(j) + use_sticks(k) + 4;
                    if (total_sticks == n) {
                        bool unique = true;
                        for (int m = 0; m < ans; ++m) {
                            if (!different({i, j, k}, equations[m])) {
                                unique = false;
                                break;
                            }
                        }
                        if (unique) {
                            equations[ans] = {i, j, k};
                            ++ans;
                        }
                    }
                }
            }
        }
    }

    cout << ans << endl;
    return 0;
}
