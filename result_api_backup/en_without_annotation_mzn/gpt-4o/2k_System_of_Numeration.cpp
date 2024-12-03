#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int k, w;
int scale, maxnum;
std::vector<int> len;
std::vector<std::vector<int>> r;

bool different(int len1, int len2, const std::vector<int>& r1, const std::vector<int>& r2) {
    if (len1 != len2) return true;
    for (int i = 0; i < len1; ++i) {
        if (r1[i] != r2[i]) return true;
    }
    return false;
}

int binary(const std::vector<int>& r, int length) {
    if (length > 0) {
        return r[length - 1] + 2 * binary(r, length - 1);
    }
    return 0;
}

bool constraints_valid(int optnum) {
    for (int i = 0; i < optnum; ++i) {
        if (r[i][0] == 0) return false;
        for (int j = 0; j < len[i] - 1; ++j) {
            if (r[i][j] >= r[i][j + 1]) return false;
        }
    }
    for (int i = 0; i < optnum; ++i) {
        for (int j = i + 1; j < optnum; ++j) {
            if (!different(len[i], len[j], r[i], r[j])) return false;
        }
    }
    for (int i = 0; i < optnum; ++i) {
        if (binary(r[i], len[i]) >= std::pow(2, w)) return false;
    }
    return true;
}

int main() {
    std::cin >> k >> w;
    scale = std::pow(2, k);
    maxnum = std::pow(2, w);
    len.resize(maxnum);
    r.resize(maxnum, std::vector<int>(w));

    int optnum = 0;

    for (int i = 0; i <= maxnum; ++i) {
        for (int j = 0; j < i; ++j) {
            len[j] = std::min(w, j + 2);
            for (int l = 0; l < len[j]; ++l) {
                r[j][l] = rand() % scale; // Random generation
            }
        }
        if (constraints_valid(i)) {
            optnum = i;
        }
    }

    std::cout << optnum << std::endl;
    return 0;
}