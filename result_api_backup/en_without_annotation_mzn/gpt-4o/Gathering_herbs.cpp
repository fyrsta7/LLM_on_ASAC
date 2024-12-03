#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Herb {
    int cost, value;
};

int main() {
    int T, M;
    cin >> T >> M;
    vector<Herb> herbs(M);
    for(int i = 0; i < M; i++) {
        cin >> herbs[i].cost >> herbs[i].value;
    }

    vector<int> dp(T + 1, 0);
    for(const auto &herb : herbs) {
        for(int t = T; t >= herb.cost; t--) {
            dp[t] = max(dp[t], dp[t - herb.cost] + herb.value);
        }
    }

    cout << dp[T] << endl;
    return 0;
}