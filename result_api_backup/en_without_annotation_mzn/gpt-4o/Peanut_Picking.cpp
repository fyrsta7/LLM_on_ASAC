#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct Move {
    int x, y;
};

struct State {
    int x, y, num, peanuts;
    vector<string> actions;
};

const vector<Move> MOVES = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
const vector<string> ACTIONS = {"down", "up", "right", "left"};

int M, N, K;
vector<vector<int>> peanuts;
set<int> peanut_set;
vector<State> states;

bool validMove(int x, int y) {
    return x >= 0 && x < M && y >= 0 && y < N;
}

bool compare(const State &a, const State &b) {
    return a.peanuts + peanuts[a.x][a.y] > b.peanuts + peanuts[b.x][b.y];
}

int main() {
    cin >> M >> N >> K;
    peanuts.resize(M, vector<int>(N));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> peanuts[i][j];
            if (peanuts[i][j] > 0) {
                peanut_set.insert(peanuts[i][j]);
            }
        }
    }

    vector<string> best_actions;
    int max_num = 0;

    states.push_back({0, 0, 0, 0, {}});
    while (!states.empty()) {
        State current = states.back();
        states.pop_back();

        if (current.num == K) {
            if (current.peanuts > max_num) {
                max_num = current.peanuts;
                best_actions = current.actions;
            }
            continue;
        }

        for (int i = 0; i < 4; ++i) {
            int new_x = current.x + MOVES[i].x;
            int new_y = current.y + MOVES[i].y;
            if (validMove(new_x, new_y)) {
                vector<string> new_actions = current.actions;
                new_actions.push_back(ACTIONS[i]);
                states.push_back({new_x, new_y, current.num + 1, current.peanuts, new_actions});
            }
        }

        if (peanuts[current.x][current.y] > 0) {
            vector<string> new_actions = current.actions;
            new_actions.push_back("pick");
            states.push_back({current.x, current.y, current.num + 1, current.peanuts + peanuts[current.x][current.y], new_actions});
        }
    }

    cout << max_num << endl;
    return 0;
}