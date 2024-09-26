#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Pipe {
    int p, l, h;
    bool operator<(const Pipe &other) const {
        return p < other.p;
    }
};

struct State {
    int x, y, taps;
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> rise(n), fall(n);
    for (int i = 0; i < n; ++i) {
        cin >> rise[i] >> fall[i];
    }
    vector<Pipe> pipes(k);
    for (int i = 0; i < k; ++i) {
        cin >> pipes[i].p >> pipes[i].l >> pipes[i].h;
    }
    sort(pipes.begin(), pipes.end());

    vector<vector<bool>> visited(n + 1, vector<bool>(m + 1, false));
    queue<State> q;
    q.push({0, 1, 0});
    visited[0][1] = true;

    int max_gaps = 0;
    while (!q.empty()) {
        State s = q.front();
        q.pop();

        if (s.x == n) {
            cout << 1 << endl << s.taps << endl;
            return 0;
        }

        int next_x = s.x + 1;
        int next_y_rise = min(m, s.y + rise[s.x]);
        int next_y_fall = max(1, s.y - fall[s.x]);

        auto it = lower_bound(pipes.begin(), pipes.end(), Pipe{next_x, 0, 0});
        if (it != pipes.end() && it->p == next_x) {
            if (next_y_rise > it->l && next_y_rise < it->h && !visited[next_x][next_y_rise]) {
                q.push({next_x, next_y_rise, s.taps + 1});
                visited[next_x][next_y_rise] = true;
            }
            if (next_y_fall > it->l && next_y_fall < it->h && !visited[next_x][next_y_fall]) {
                q.push({next_x, next_y_fall, s.taps});
                visited[next_x][next_y_fall] = true;
            }
        } else {
            if (!visited[next_x][next_y_rise]) {
                q.push({next_x, next_y_rise, s.taps + 1});
                visited[next_x][next_y_rise] = true;
            }
            if (!visited[next_x][next_y_fall]) {
                q.push({next_x, next_y_fall, s.taps});
                visited[next_x][next_y_fall] = true;
            }
        }

        if (it != pipes.begin() && (--it)->p == s.x) {
            max_gaps = max(max_gaps, s.x - it->p);
        }
    }

    cout << 0 << endl << max_gaps << endl;
    return 0;
}
