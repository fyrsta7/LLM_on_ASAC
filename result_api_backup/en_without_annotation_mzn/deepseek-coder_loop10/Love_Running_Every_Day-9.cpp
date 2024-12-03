#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> road(n - 1, vector<int>(2));
    for (int i = 0; i < n - 1; ++i) {
        cin >> road[i][0] >> road[i][1];
    }

    vector<int> watcher(n);
    for (int i = 0; i < n; ++i) {
        cin >> watcher[i];
    }

    vector<vector<int>> player(m, vector<int>(2));
    for (int i = 0; i < m; ++i) {
        cin >> player[i][0] >> player[i][1];
    }

    vector<vector<int>> route(m, vector<int>(n - 1));
    vector<int> time(m);
    vector<vector<int>> location(m, vector<int>(n));

    for (int i = 0; i < m; ++i) {
        vector<int> path;
        int start = player[i][0];
        int end = player[i][1];
        vector<bool> visited(n, false);
        visited[start] = true;
        location[i][0] = start;

        for (int j = 0; j < n - 1; ++j) {
            for (int k = 0; k < n - 1; ++k) {
                if (!visited[road[k][0]] || !visited[road[k][1]]) {
                    if (road[k][0] == start || road[k][1] == start) {
                        path.push_back(k);
                        start = (road[k][0] == start) ? road[k][1] : road[k][0];
                        visited[start] = true;
                        location[i][j + 1] = start;
                        break;
                    }
                }
            }
            if (start == end) {
                time[i] = j + 1;
                break;
            }
        }
        route[i] = path;
    }

    vector<int> watch_num(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (time[j] >= watcher[i] && location[j][watcher[i]] == i) {
                watch_num[i]++;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << watch_num[i] << " ";
    }
    cout << endl;

    return 0;
}
