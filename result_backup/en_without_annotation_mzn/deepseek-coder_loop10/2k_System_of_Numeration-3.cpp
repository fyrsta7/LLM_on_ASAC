#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int k, w;
int scale, maxnum;

bool isDifferent(int len1, int len2, const vector<int>& r1, const vector<int>& r2) {
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

    for (int i = 0; i < maxnum; ++i) {
        for (int j = 0; j < w; ++j) {
            r[i][j] = (i >> j) & (scale - 1);
        }
        len[i] = w;
        bool valid = true;
        for (int j = 0; j < i; ++j) {
            if (!isDifferent(len[i], len[j], r[i], r[j])) {
                valid = false;
                break;
            }
        }
        if (valid) {
            optnum++;
        }
    }

    cout << optnum << endl;

    return 0;
}
