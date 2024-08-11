#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define MAXN 10010
#define INF 1000000000

using namespace std;

struct State {
    int pos;
    int height;
    int taps;
    bool operator<(const State &other) const {
        return taps > other.taps;
    }
};

struct Pipe {
    int pos;
    int l;
    int h;
};

int n, m, k;
int rise[MAXN], fall[MAXN];
vector<Pipe> pipes;

bool canPass(int h, int l, int u) {
    return !(h >= l && h <= u);
}

int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) {
        cin >> rise[i] >> fall[i];
    }

    pipes.resize(k);
    for (int i = 0; i < k; ++i) {
        cin >> pipes[i].pos >> pipes[i].l >> pipes[i].h;
    }
    
    sort(pipes.begin(), pipes.end(), [](Pipe a, Pipe b) {
        return a.pos < b.pos;
    });

    vector<vector<int>> dp(n, vector<int>(m+1, INF));
    priority_queue<State> pq;
    
    for (int i = 0; i <= m; ++i) {
        dp[0][i] = 0;
        pq.push({0, i, 0});
    }

    int max_pipes = 0;
    
    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();

        if (cur.pos == n-1) {
            cout << 1 << endl;
            cout << cur.taps << endl;
            return 0;
        }

        for (int next_height = max(0, cur.height - fall[cur.pos]); next_height <= min(m, cur.height + rise[cur.pos]); ++next_height) {
            int required_taps = max(0, next_height - cur.height);
            int next_taps = cur.taps + required_taps;

            if (next_taps >= dp[cur.pos + 1][next_height]) continue;

            bool valid = true;
            int currentPipeIdx = lower_bound(pipes.begin(), pipes.end(), Pipe{cur.pos + 1, 0, 0}, 
                        [](Pipe a, Pipe b) { return a.pos < b.pos; }) - pipes.begin();
            
            if (currentPipeIdx < k && pipes[currentPipeIdx].pos == cur.pos + 1) {
                if (!canPass(next_height, pipes[currentPipeIdx].l, pipes[currentPipeIdx].h)) {
                    valid = false;
                }
            }

            if (valid) {
                dp[cur.pos + 1][next_height] = next_taps;
                pq.push({cur.pos + 1, next_height, next_taps});
                max_pipes = max(max_pipes, cur.pos + 1);
            }
        }
    }

    cout << 0 << endl;
    cout << max_pipes << endl;
    return 0;
}