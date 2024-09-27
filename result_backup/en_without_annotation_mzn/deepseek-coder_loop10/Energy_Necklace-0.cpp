#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> beads(N);
    for (int i = 0; i < N; ++i) {
        cin >> beads[i];
    }

    vector<vector<int>> steps(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        steps[0][i] = beads[i];
    }

    int max_ans = 0;
    vector<int> choose(N);

    function<int(int, int)> precede = [](int j, int len) {
        return j > 1 ? j - 1 : len;
    };

    function<int(int, int)> follow = [](int j, int len) {
        return j < len ? j + 1 : 1;
    };

    function<void(int, int)> backtrack = [&](int i, int current_ans) {
        if (i == N) {
            max_ans = max(max_ans, current_ans);
            return;
        }

        for (int j = 1; j <= N - i + 1; ++j) {
            choose[i] = j;
            int new_ans = current_ans;
            if (i > 0) {
                new_ans += steps[i-1][choose[i-1]] * steps[i-1][precede(choose[i-1], N-i+2)] * steps[i-1][follow(choose[i-1], N-i+2)];
            }

            for (int k = 1; k < j; ++k) {
                steps[i][k] = steps[i-1][k];
            }
            for (int k = j+1; k <= N-i+1; ++k) {
                steps[i][k-1] = steps[i-1][k];
            }

            backtrack(i + 1, new_ans);
        }
    };

    backtrack(1, 0);
    cout << max_ans << endl;

    return 0;
}
