#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int MAXN = 100005;

int n;
string s;
vector<int> adj[MAXN];
int parent[MAXN];
int ans[MAXN];

struct State {
    int open, close, valid;
    State() : open(0), close(0), valid(0) {}
    State(int o, int c, int v) : open(o), close(c), valid(v) {}
};

State merge(const State& left, const State& right) {
    int min_match = min(left.open, right.close);
    return State(left.open + right.open - min_match, left.close + right.close - min_match, left.valid + right.valid + min_match);
}

State dfs(int u) {
    State cur;
    if (s[u - 1] == '(') cur.open = 1;
    else cur.close = 1;

    for (int v : adj[u]) {
        State child = dfs(v);
        cur = merge(cur, child);
    }

    ans[u] = cur.valid;
    return cur;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> s;
    for (int i = 2; i <= n; ++i) {
        cin >> parent[i];
        adj[parent[i]].push_back(i);
    }

    dfs(1);

    int result = 0;
    for (int i = 1; i <= n; ++i) {
        result ^= (i * ans[i]);
    }

    cout << result << endl;
    return 0;
}
