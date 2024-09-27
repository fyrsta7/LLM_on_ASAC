#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    int T;
    cin >> T;
    vector<int> n(T);
    for (int i = 0; i < T; ++i) {
        cin >> n[i];
    }

    int sum_n = accumulate(n.begin(), n.end(), 0);
    vector<int> node(sum_n);
    for (int i = 0; i < sum_n; ++i) {
        cin >> node[i];
    }

    int edge_count = sum_n - T;
    vector<vector<int>> edge(edge_count, vector<int>(2));
    for (int i = 0; i < edge_count; ++i) {
        cin >> edge[i][0] >> edge[i][1];
    }

    int max_n = *max_element(n.begin(), n.end());
    vector<int> begin_n(T);
    for (int i = 1; i < T; ++i) {
        begin_n[i] = begin_n[i - 1] + n[i - 1];
    }

    vector<int> delete_(sum_n);
    vector<vector<int>> state(sum_n, vector<int>(max_n));
    vector<int> p(sum_n);
    vector<int> score(T);

    for (int t = 0; t < T; ++t) {
        vector<int> delete_range(n[t] - 1);
        iota(delete_range.begin(), delete_range.end(), 1);
        sort(delete_range.begin(), delete_range.end());

        for (int j = begin_n[t] + 1; j < begin_n[t] + n[t]; ++j) {
            delete_[j] = delete_range[j - begin_n[t] - 1];
        }

        for (int i = begin_n[t]; i < begin_n[t] + n[t]; ++i) {
            for (int k = 0; k < n[t]; ++k) {
                state[i][k] = node[i];
            }
        }

        for (int i = begin_n[t] + 1; i < begin_n[t] + n[t]; ++i) {
            int del = delete_[i];
            state[i][edge[del - 1][0] - 1] = state[i - 1][edge[del - 1][1] - 1];
            state[i][edge[del - 1][1] - 1] = state[i - 1][edge[del - 1][0] - 1];
            for (int k = 0; k < n[t]; ++k) {
                if (k != edge[del - 1][0] - 1 && k != edge[del - 1][1] - 1) {
                    state[i][k] = state[i - 1][k];
                }
            }
        }

        for (int j = 0; j < n[t]; ++j) {
            p[begin_n[t] + j] = state[begin_n[t] + n[t] - 1][j];
        }

        score[t] = 0;
        for (int j = 0; j < n[t]; ++j) {
            score[t] += (1 << (n[t] - j - 1)) * p[begin_n[t] + j];
        }
    }

    int total_score = accumulate(score.begin(), score.end(), 0);
    cout << total_score << endl;

    return 0;
}
