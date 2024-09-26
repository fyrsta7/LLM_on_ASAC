#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct TestCase {
    int n;
    vector<int> node;
};

int main() {
    int T;
    cin >> T;

    vector<TestCase> test_cases(T);
    int sum_n = 0;
    for (int t = 0; t < T; ++t) {
        cin >> test_cases[t].n;
        sum_n += test_cases[t].n;
    }

    vector<int> node(sum_n);
    for (int i = 0; i < sum_n; ++i) {
        cin >> node[i];
    }

    vector<vector<int>> edge(sum_n - T, vector<int>(2));
    for (int i = 0; i < sum_n - T; ++i) {
        cin >> edge[i][0] >> edge[i][1];
    }

    vector<int> begin_n(T);
    int current_sum = 0;
    for (int i = 0; i < T; ++i) {
        begin_n[i] = current_sum + 1;
        current_sum += test_cases[i].n;
    }

    vector<vector<int>> state(sum_n, vector<int>(test_cases[0].n));
    vector<int> p(sum_n);

    auto solve_case = [&](int t) {
        int n = test_cases[t].n;
        vector<int> p_case(n);
        iota(p_case.begin(), p_case.end(), 1);
        auto best_p = p_case;
        int best_score = INT_MAX;

        do {
            for (int i = 0; i < n; ++i) {
                state[begin_n[t] + n - 1][i] = node[begin_n[t] + p_case[i] - 1];
            }

            for (int i = begin_n[t] + n - 2; i >= begin_n[t]; --i) {
                int ex_idx = i - begin_n[t];
                int u = edge[ex_idx][0] - 1;
                int v = edge[ex_idx][1] - 1;
                swap(state[i][u], state[i][v]);
                for (int j = 0; j < n; ++j) {
                    if (j != u && j != v)
                        state[i][j] = state[i + 1][j];
                }
            }

            bool valid = true;
            for (int i = begin_n[t]; i < begin_n[t] + n; ++i) {
                vector<bool> visited(n, false);
                for (int j = 0; j < n; ++j) {
                    if (visited[state[i][j] - 1]) {
                        valid = false;
                        break;
                    }
                    visited[state[i][j] - 1] = true;
                }
                if (!valid) break;
            }

            if (valid) {
                int score = 0;
                for (int i = 0; i < n; ++i) {
                    score += pow(2, n - i - 1) * p_case[i];
                }
                if (score < best_score) {
                    best_score = score;
                    best_p = p_case;
                }
            }

        } while (next_permutation(p_case.begin(), p_case.end()));

        for (int i = 0; i < n; ++i) {
            p[begin_n[t] + i - 1] = best_p[i];
        }
    };

    for (int t = 0; t < T; ++t) {
        solve_case(t);
    }

    for (int i = 0; i < sum_n; ++i) {
        cout << p[i] << " ";
    }
    cout << endl;

    return 0;
}