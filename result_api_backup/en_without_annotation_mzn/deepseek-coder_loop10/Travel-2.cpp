#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

struct Road {
    int u, v;
};

struct State {
    vector<int> route;
    int length;
    vector<int> first;
    int score;

    bool operator>(const State& other) const {
        return score > other.score;
    }
};

int n, m;
vector<Road> roads;
vector<vector<int>> adj;

int calculateScore(const vector<int>& first) {
    int score = 0;
    for (int i = 0; i < n; ++i) {
        score += pow(n, n - i) * first[i];
    }
    return score;
}

bool isValidRoute(const vector<int>& route, int length) {
    vector<bool> visited(n + 1, false);
    for (int i = 1; i <= length; ++i) {
        if (visited[route[i]]) return false;
        visited[route[i]] = true;
    }
    return true;
}

bool isConnected(const vector<int>& route, int length) {
    for (int i = 2; i <= length; ++i) {
        bool found = false;
        for (int k = 0; k < m; ++k) {
            if ((route[i] == roads[k].u && route[i - 1] == roads[k].v) ||
                (route[i] == roads[k].v && route[i - 1] == roads[k].u)) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

int main() {
    cin >> n >> m;
    roads.resize(m);
    adj.resize(n + 1);
    for (int i = 0; i < m; ++i) {
        cin >> roads[i].u >> roads[i].v;
        adj[roads[i].u].push_back(roads[i].v);
        adj[roads[i].v].push_back(roads[i].u);
    }

    priority_queue<State, vector<State>, greater<State>> pq;
    State initialState;
    initialState.route.resize(2 * n + 1, 0);
    initialState.length = 1;
    initialState.first.resize(n + 1, 0);
    initialState.score = 0;
    pq.push(initialState);

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        if (current.length == 2 * n) {
            cout << "First: ";
            for (int i = 1; i <= n; ++i) {
                cout << current.first[i] << " ";
            }
            cout << endl;
            return 0;
        }

        for (int next : adj[current.route[current.length]]) {
            State nextState = current;
            nextState.route[nextState.length + 1] = next;
            nextState.length++;

            if (isValidRoute(nextState.route, nextState.length) && isConnected(nextState.route, nextState.length)) {
                vector<int> first(n + 1, 0);
                for (int i = 1; i <= n; ++i) {
                    for (int k = 1; k <= nextState.length; ++k) {
                        if (nextState.route[k] == i) {
                            first[i] = k;
                            break;
                        }
                    }
                }
                nextState.first = first;
                nextState.score = calculateScore(first);
                pq.push(nextState);
            }
        }
    }

    cout << "No valid route found." << endl;
    return 0;
}
