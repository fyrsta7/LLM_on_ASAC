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
    vector<vector<int>> state(sum_n, vector<int>(max_n, 0));
    vector<int> p(sum_n, 0);
    vector<int> score(T, 0);

    for (int t = 0; t < T; ++t) {
        for (int j = begin_n[t] + 1; j < begin_n[t] + n[t]; ++j) {
            delete_[j] = j - begin_n[t];
        }
        sort(delete_.begin() + begin_n[t] + 1, delete_.begin() + begin_n[t] + n[t]);

        for (int i = begin_n[t] + 1; i < begin_n[t] + n[t]; ++i) {
            state[i][edge[delete_[i]][0]] = state[i - 1][edge[delete_[i]][1]];
            state[i][edge[delete_[i]][1]] = state[i - 1][edge[delete_[i]][0]];
            for (int k = 1; k <= n[t]; ++k) {
                if (k != edge[delete_[i]][1] && k != edge[delete_[i]][0]) {
                    state[i][k] = state[i - 1][k];
                }
            }
        }

        for (int j = 1; j <= n[t]; ++j) {
            p[j + begin_n[t]] = j;
        }

        for (int j = 1; j <= n[t]; ++j) {
            score[t] += (1 << (n[t] - j)) * p[j + begin_n[t]];
        }
    }

    int total_score = accumulate(score.begin(), score.end(), 0);
    cout << total_score << endl;

    return 0;
}
