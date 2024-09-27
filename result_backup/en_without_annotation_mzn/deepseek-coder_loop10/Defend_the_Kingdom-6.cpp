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

    vector<int> score(m, 0);
    vector<vector<int>> troop(m, vector<int>(n, 0));

    for (int i = 0; i < m; ++i) {
        bool valid = true;
        for (int j = 0; j < n-1; ++j) {
            if ((road[j][0] == request[i][0] && road[j][1] == request[i][2]) ||
                (road[j][1] == request[i][0] && road[j][0] == request[i][2])) {
                if (request[i][1] == 0 && request[i][3] == 0) {
                    score[i] = -1;
                    valid = false;
                    break;
                }
            }
        }
        if (valid) {
            troop[i][request[i][0]-1] = request[i][1];
            troop[i][request[i][2]-1] = request[i][3];
            for (int j = 0; j < n-1; ++j) {
                if (troop[i][road[j][0]-1] == 0 && troop[i][road[j][1]-1] == 0) {
                    score[i] = -1;
                    valid = false;
                    break;
                }
            }
            if (valid) {
                score[i] = 0;
                for (int j = 0; j < n; ++j) {
                    score[i] += troop[i][j] * p[j];
                }
            }
        }
    }

    int min_score = *min_element(score.begin(), score.end());
    cout << min_score << endl;

    return 0;
}
