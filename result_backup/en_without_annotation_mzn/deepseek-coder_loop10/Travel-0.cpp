#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int n, m;
vector<vector<int>> road;
vector<int> route;
vector<int> first;

bool isConnected(int a, int b) {
    for (const auto& r : road) {
        if ((r[0] == a && r[1] == b) || (r[0] == b && r[1] == a)) {
            return true;
        }
    }
    return false;
}

bool isValidRoute() {
    int length = route.size();
    if (route[0] != route[length - 1]) return false;
    vector<bool> visited(n + 1, false);
    for (int i = 0; i < length; ++i) {
        if (visited[route[i]]) return false;
        visited[route[i]] = true;
    }
    for (int i = 1; i < length; ++i) {
        if (!isConnected(route[i], route[i - 1])) return false;
    }
    return true;
}

int calculateScore() {
    int score = 0;
    for (int i = 1; i <= n; ++i) {
        score += pow(n, n - i) * first[i];
    }
    return score;
}

void solve() {
    int bestScore = INT_MAX;
    vector<int> bestFirst;

    vector<int> perm(n);
    for (int i = 0; i < n; ++i) perm[i] = i + 1;

    do {
        route.clear();
        for (int i = 0; i < n; ++i) route.push_back(perm[i]);
        route.push_back(perm[0]);

        if (isValidRoute()) {
            first.assign(n + 1, 0);
            for (int i = 0; i < route.size(); ++i) {
                if (first[route[i]] == 0) first[route[i]] = i + 1;
            }
            int score = calculateScore();
            if (score < bestScore) {
                bestScore = score;
                bestFirst = first;
            }
        }
    } while (next_permutation(perm.begin(), perm.end()));

    for (int i = 1; i <= n; ++i) {
        cout << bestFirst[i] << " ";
    }
    cout << endl;
}

int main() {
    cin >> n >> m;
    road.resize(m, vector<int>(2));
    for (int i = 0; i < m; ++i) {
        cin >> road[i][0] >> road[i][1];
    }
    solve();
    return 0;
}
