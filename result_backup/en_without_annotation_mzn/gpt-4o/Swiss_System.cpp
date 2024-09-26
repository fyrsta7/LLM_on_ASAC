#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Player {
    int id;
    int score;
};

bool comparePlayers(const Player &a, const Player &b) {
    return (a.score > b.score) || (a.score == b.score && a.id < b.id);
}

int main() {
    int N, R, Q;
    cin >> N >> R >> Q;

    vector<Player> players(N * 2);
    // Read initial scores
    for (int i = 0; i < N * 2; ++i) {
        players[i].id = i + 1;
        cin >> players[i].score;
    }
    // Read weights
    vector<int> weights(N * 2);
    for (int i = 0; i < N * 2; ++i) {
        cin >> weights[i];
    }

    // Simulate the rounds
    for (int r = 0; r < R; ++r) {
        // Sort players by scores and ids
        sort(players.begin(), players.end(), comparePlayers);
        // Play each match
        for (int i = 0; i < N; ++i) {
            Player &a = players[2 * i];
            Player &b = players[2 * i + 1];
            if (weights[a.id - 1] > weights[b.id - 1]) {
                a.score++;
            } else {
                b.score++;
            }
        }
    }

    // Sort players for the final round
    sort(players.begin(), players.end(), comparePlayers);
    // Output the result for the Q-th player in the final round
    cout << players[Q - 1].id << endl;

    return 0;
}