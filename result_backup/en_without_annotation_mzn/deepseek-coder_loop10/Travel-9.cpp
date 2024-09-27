#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int n, m;
vector<vector<int>> road;
vector<int> route;
vector<int> first;
int length;
int score;

bool is_valid_route() {
    vector<bool> visited(n + 1, false);
    for (int i = 1; i <= length; ++i) {
        if (visited[route[i]]) return false;
        visited[route[i]] = true;
    }
    for (int i = 2; i <= length; ++i) {
        bool valid_road = false;
        for (int k = 1; k <= m; ++k) {
            if ((route[i] == road[k][0] && route[i-1] == road[k][1]) ||
                (route[i] == road[k][1] && route[i-1] == road[k][0])) {
                valid_road = true;
                break;
            }
        }
        if (!valid_road) return false;
    }
    return true;
}

void calculate_score() {
    first.assign(n + 1, 0);
    vector<int> first_pos(n + 1, 0);
    for (int i = 1; i <= length; ++i) {
        if (first_pos[route[i]] == 0) {
            first_pos[route[i]] = i;
            first[route[i]] = route[i];
        }
    }
    sort(first.begin() + 1, first.end(), [&](int a, int b) {
        return first_pos[a] < first_pos[b];
    });
    score = 0;
    for (int i = 1; i <= n; ++i) {
        score += pow(n, n - i) * first[i];
    }
}

void solve() {
    route.assign(2 * n + 1, 0);
    length = 2 * n;
    for (int i = 1; i <= n; ++i) {
        route[i] = i;
        route[i + n] = i;
    }
    do {
        if (is_valid_route()) {
            calculate_score();
            break;
        }
    } while (next_permutation(route.begin() + 1, route.begin() + length + 1));
}

int main() {
    cin >> n >> m;
    road.assign(m + 1, vector<int>(2));
    for (int i = 1; i <= m; ++i) {
        cin >> road[i][0] >> road[i][1];
    }
    solve();
    for (int i = 1; i <= n; ++i) {
        cout << first[i] << " ";
    }
    cout << endl;
    return 0;
}
