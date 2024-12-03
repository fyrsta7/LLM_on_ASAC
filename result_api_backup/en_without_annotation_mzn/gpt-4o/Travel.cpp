#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int n, m;
vector<pair<int, int>> road;
vector<int> route, first, length;
vector<int> score;

bool is_valid_route(const vector<int>& route, int length) {
    if (route[length - 1] != route[0]) return false;
    vector<bool> visited(n + 1, false);
    for (int i = 0; i < n; ++i) {
        if (find(route.begin(), route.begin() + length, i + 1) == route.begin() + length) return false;
        visited[route[i]] = true;
    }
    for (int i = 1; i < length; ++i) {
        for (int j = 0; j < i - 1; ++j) {
            if (route[i] == route[j]) {
                int idx = -1;
                for (int k = 0; k < i - 1; ++k) {
                    if (route[k] == route[i - 1]) {
                        idx = k;
                        break;
                    }
                }
                if (idx >= 2 && route[i] != route[idx - 1]) return false;
            }
        }
    }
    for (int i = 1; i < length; ++i) {
        bool connected = false;
        for (int k = 0; k < m; ++k) {
            if ((route[i] == road[k].first && route[i - 1] == road[k].second) ||
                (route[i] == road[k].second && route[i - 1] == road[k].first)) {
                connected = true;
                break;
            }
        }
        if (!connected) return false;
    }
    return true;
}

void solve() {
    int best_score = 1e9;
    vector<int> best_first(n);
    for (int i = 1; i <= 2 * n; ++i) {
        length.push_back(i);
        route.resize(i);
        do {
            if (is_valid_route(route, i)) {
                first.resize(n);
                for (int j = 0; j < n; ++j) {
                    for (int k = 0; k < i; ++k) {
                        if (route[k] == j + 1) {
                            first[j] = k + 1;
                            break;
                        }
                    }
                }
                bool valid_min_order = true;
                for (int j = 0; j < n - 1; ++j) {
                    if (first[j] >= first[j + 1]) {
                        valid_min_order = false;
                        break;
                    }
                }
                if (valid_min_order) {
                    int current_score = 0;
                    for (int j = 0; j < n; ++j) {
                        current_score += pow(n, n - j - 1) * first[j];
                    }
                    if (current_score < best_score) {
                        best_score = current_score;
                        best_first = first;
                    }
                }
            }
        } while (next_permutation(route.begin(), route.end()));
    }
    for (int x : best_first) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    cin >> n >> m;
    road.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> road[i].first >> road[i].second;
    }
    solve();
    return 0;
}