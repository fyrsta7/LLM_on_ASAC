#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Road {
    int u, v;
};

struct Player {
    int start, end;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<Road> roads(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> roads[i].u >> roads[i].v;
    }

    vector<int> watcher(n);
    for (int i = 0; i < n; ++i) {
        cin >> watcher[i];
    }

    vector<Player> players(m);
    for (int i = 0; i < m; ++i) {
        cin >> players[i].start >> players[i].end;
    }

    vector<vector<int>> route(m, vector<int>(n - 1));
    vector<int> time(m);
    vector<vector<int>> location(m, vector<int>(n));

    for (int i = 0; i < m; ++i) {
        vector<int> path;
        int current = players[i].start;
        while (current != players[i].end) {
            for (int j = 0; j < n - 1; ++j) {
                if ((roads[j].u == current && roads[j].v == players[i].end) ||
                    (roads[j].v == current && roads[j].u == players[i].end)) {
                    path.push_back(j);
                    current = players[i].end;
                    break;
                } else if ((roads[j].u == current || roads[j].v == current) &&
                           find(path.begin(), path.end(), j) == path.end()) {
                    path.push_back(j);
                    current = (roads[j].u == current) ? roads[j].v : roads[j].u;
                    break;
                }
            }
        }
        route[i] = path;
        time[i] = path.size();
        location[i][0] = players[i].start;
        for (int j = 0; j < time[i]; ++j) {
            location[i][j + 1] = (roads[path[j]].u == location[i][j]) ? roads[path[j]].v : roads[path[j]].u;
        }
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
