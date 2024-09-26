#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Player {
    int id;
    int score;
    int strength;
};

bool comparePlayers(const Player &a, const Player &b) {
    if (a.score == b.score) return a.id < b.id;
    return a.score > b.score;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, R, Q;
    cin >> N >> R >> Q;

    vector<Player> players(2 * N);
    for (int i = 0; i < 2 * N; ++i) {
        players[i].id = i + 1;
        cin >> players[i].score;
    }
    for (int i = 0; i < 2 * N; ++i) {
        cin >> players[i].strength;
    }

    sort(players.begin(), players.end(), comparePlayers);

    vector<Player> winners(N);
    vector<Player> losers(N);

    for (int round = 0; round < R; ++round) {
        for (int i = 0; i < N; ++i) {
            if (players[2 * i].strength > players[2 * i + 1].strength) {
                players[2 * i].score++;
                winners[i] = players[2 * i];
                losers[i] = players[2 * i + 1];
            } else {
                players[2 * i + 1].score++;
                winners[i] = players[2 * i + 1];
                losers[i] = players[2 * i];
            }
        }
        merge(winners.begin(), winners.end(), losers.begin(), losers.end(), players.begin(), comparePlayers);
    }

    cout << players[Q - 1].id << endl;

    return 0;
}
