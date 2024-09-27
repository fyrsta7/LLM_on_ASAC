#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i];

    vector<vector<int>> road(n-1, vector<int>(2));
    for (int i = 0; i < n-1; ++i) cin >> road[i][0] >> road[i][1];

    vector<vector<int>> request(m, vector<int>(4));
    for (int i = 0; i < m; ++i) cin >> request[i][0] >> request[i][1] >> request[i][2] >> request[i][3];

    vector<vector<int>> troop(m, vector<int>(n, 0));
    vector<int> score(m, 0);

    for (int i = 0; i < m; ++i) {
        int u = request[i][0] - 1;
        int v = request[i][2] - 1;
        int tu = request[i][1];
        int tv = request[i][3];

        bool valid = true;
        for (int j = 0; j < n-1; ++j) {
            if ((road[j][0] == u + 1 && road[j][1] == v + 1) || (road[j][1] == u + 1 && road[j][0] == v + 1)) {
                if (tu == 0 && tv == 0) {
                    score[i] = -1;
                    valid = false;
                    break;
                }
            }
        }

        if (valid) {
            troop[i][u] = tu;
            troop[i][v] = tv;
            for (int j = 0; j < n-1; ++j) {
                if (troop[i][road[j][0] - 1] == 0 && troop[i][road[j][1] - 1] == 0) {
                    score[i] = -1;
                    valid = false;
                    break;
                }
            }
        }

        if (valid && score[i] != -1) {
            score[i] = 0;
            for (int j = 0; j < n; ++j) {
                score[i] += troop[i][j] * p[j];
            }
        }
    }

    int total_score = 0;
    for (int i = 0; i < m; ++i) {
        if (score[i] != -1) {
            total_score += score[i];
        }
    }

    cout << total_score << endl;

    return 0;
}
