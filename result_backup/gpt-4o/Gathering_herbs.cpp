#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int T, M;
    cin >> T >> M;

    vector<int> dp(T + 1, 0);
    vector<pair<int, int>> herbs(M);

    for (int i = 0; i < M; ++i) {
        int time, value;
        cin >> time >> value;
        herbs[i] = make_pair(time, value);
    }

    for (const auto& herb : herbs) {
        for (int j = T; j >= herb.first; --j) {
            dp[j] = max(dp[j], dp[j - herb.first] + herb.second);
        }
    }

    cout << dp[T] << endl;

    return 0;
}