#include <iostream>
#include <vector>
#include <algorithm>

const int MAXN = 100;
int n;
int like[MAXN][2];
int shift[MAXN][2];
int position[MAXN][MAXN];
int M[MAXN];
int steps;

bool isValid(int step) {
    for (int i = 1; i <= n; ++i) {
        int pre = (i == 1) ? n : i - 1;
        int next = (i == n) ? 1 : i + 1;

        if (!((position[step][pre] == like[position[step][i]][0] && position[step][next] == like[position[step][i]][1]) ||
              (position[step][pre] == like[position[step][i]][1] && position[step][next] == like[position[step][i]][0])))
            return false;
    }
    return true;
}

bool movePossible(int step) {
    for (int i = 0; i < n; ++i) {
        if (shift[step][i] != shift[step + 1][i] && M[step + 1] != shift[step][i])
            return false;
    }
    return true;
}

void solve() {
    std::vector<int> perm(n);
    for (int i = 0; i < n; ++i) perm[i] = i;

    do {
        for (int i = 0; i < n; ++i) position[1][i] = perm[i] + 1;

        for (steps = 2; steps <= n; ++steps) {
            if (isValid(steps)) {
                if (movePossible(steps)) {
                    int res = std::accumulate(M + 1, M + steps, 0);
                    std::cout << res << std::endl;
                    return;
                }
            }
        }
    } while (std::next_permutation(perm.begin(), perm.end()));
}

int main() {
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> like[i][0] >> like[i][1];
    }
    solve();
    return 0;
}