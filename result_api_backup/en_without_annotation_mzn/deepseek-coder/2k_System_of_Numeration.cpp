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

bool isValid(int optnum, const vector<int>& len, const vector<vector<int>>& r) {
    for (int i = 0; i < optnum; ++i) {
        if (r[i][0] == 0) return false;
        for (int j = 1; j < len[i]; ++j) {
            if (r[i][j-1] >= r[i][j]) return false;
        }
        if (binary(r[i], len[i]) >= (1 << w)) return false;
    }
    for (int i = 0; i < optnum; ++i) {
        for (int j = i + 1; j < optnum; ++j) {
            if (!different(len[i], len[j], r[i], r[j])) return false;
        }
    }
    return true;
}

int main() {
    cin >> k >> w;
    scale = 1 << k;
    maxnum = 1 << w;

    int optnum = 0;
    vector<int> len(maxnum, 0);
    vector<vector<int>> r(maxnum, vector<int>(w, 0));

    for (int i = 0; i < maxnum; ++i) {
        for (int j = 0; j < w; ++j) {
            r[i][j] = (i >> j) & 1;
        }
        len[i] = w;
    }

    while (isValid(optnum + 1, len, r)) {
        ++optnum;
    }

    cout << optnum << endl;

    return 0;
}
