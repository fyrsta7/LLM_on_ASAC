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

    vector<int> delete_(sum_n, 0);
    for (int t = 0; t < T; ++t) {
        vector<int> delete_options(n[t] - 1);
        iota(delete_options.begin(), delete_options.end(), 1);
        for (int j = begin_n[t] + 1; j < begin_n[t] + n[t]; ++j) {
            delete_[j] = delete_options.back();
            delete_options.pop_back();
        }
    }

    vector<vector<int>> state(sum_n, vector<int>(max_n, 0));
    for (int t = 0; t < T; ++t) {
        for (int i = 0; i < n[t]; ++i) {
            state[begin_n[t] + i][i] = node[begin_n[t] + i];
        }
    }

    for (int t = 0; t < T; ++t) {
        for (int i = begin_n[t] + 1; i < begin_n[t] + n[t]; ++i) {
            int d = delete_[i];
            state[i][edge[d - 1][0] - 1] = state[i - 1][edge[d - 1][1] - 1];
            state[i][edge[d - 1][1] - 1] = state[i - 1][edge[d - 1][0] - 1];
            for (int k = 0; k < n[t]; ++k) {
                if (k != edge[d - 1][0] - 1 && k != edge[d - 1][1] - 1) {
                    state[i][k] = state[i - 1][k];
                }
            }
        }
    }

    vector<int> p(sum_n);
    for (int t = 0; t < T; ++t) {
        for (int j = 0; j < n[t]; ++j) {
            for (int k = 0; k < n[t]; ++k) {
                if (state[begin_n[t] + n[t] - 1][k] == j + 1) {
                    p[begin_n[t] + j] = k + 1;
                    break;
                }
            }
        }
    }

    vector<int> score(T);
    for (int i = 0; i < T; ++i) {
        score[i] = 0;
        for (int j = 0; j < n[i]; ++j) {
            score[i] += (1 << (n[i] - j - 1)) * p[begin_n[i] + j];
        }
    }

    int total_score = accumulate(score.begin(), score.end(), 0);
    cout << total_score << endl;

    return 0;
}
