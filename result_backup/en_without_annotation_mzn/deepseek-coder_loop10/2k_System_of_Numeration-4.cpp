#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int k, w;
int scale, maxnum;

bool different(int len1, int len2, const vector<int>& r1, const vector<int>& r2) {
    if (len1 != len2) return true;
    for (int i = 0; i < len1; ++i) {
        if (r1[i] != r2[i]) return true;
    }
    return false;
}

int binary(const vector<int>& r, int length) {
    int result = 0;
    for (int i = 0; i < length; ++i) {
        result = result * 2 + r[i];
    }
    return result;
}

int main() {
    cin >> k >> w;
    scale = 1 << k;
    maxnum = 1 << w;

    vector<int> len(maxnum, 0);
    vector<vector<int>> r(maxnum, vector<int>(w, 0));

    int optnum = 0;
    for (int i = 1; i < maxnum; ++i) {
        for (int j = 1; j <= w; ++j) {
            if (binary(r[i], j) < (1 << w)) {
                len[i] = j;
                break;
            }
        }
        if (len[i] == 0) continue;
        bool valid = true;
        for (int j = 1; j < i; ++j) {
            if (!different(len[i], len[j], r[i], r[j])) {
                valid = false;
                break;
            }
        }
        if (valid) {
            optnum = i;
            for (int j = 1; j <= len[i]; ++j) {
                r[i][j-1] = (j == 1) ? 1 : r[i][j-2] + 1;
            }
        } else {
            len[i] = 0;
        }
    }

    cout << optnum << endl;
    return 0;
}
