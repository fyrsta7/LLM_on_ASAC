#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Herb {
    int cost;
    int value;
};

int main() {
    int T, M;
    cin >> T >> M;
    vector<Herb> herbs(M);
    for (int i = 0; i < M; ++i) {
        cin >> herbs[i].cost >> herbs[i].value;
    }

    vector<int> dp(T + 1, 0);

    for (int i = 0; i < M; ++i) {
        for (int j = T; j >= herbs[i].cost; --j) {
            dp[j] = max(dp[j], dp[j - herbs[i].cost] + herbs[i].value);
        }
    }

    cout << dp[T] << endl;
    return 0;
}