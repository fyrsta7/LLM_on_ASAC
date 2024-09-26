#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Player {
    int id;
    int strength;
    int weight;
    int score;
};

bool comparePlayers(const Player &a, const Player &b) {
    if (a.score == b.score) return a.id < b.id;
    return a.score > b.score;
}

int main() {
    int N, R, Q;
    cin >> N >> R >> Q;
    vector<Player> players(2 * N);

    for (int i = 0; i < 2 * N; ++i) {
        players[i].id = i + 1;
        cin >> players[i].score;
    }
    for (int i = 0; i < 2 * N; ++i) {
        cin >> players[i].weight;
    }

    for (int round = 0; round < R; ++round) {
        sort(players.begin(), players.end(), comparePlayers);
        for (int i = 0; i < N; ++i) {
            int a = 2 * i;
            int b = 2 * i + 1;
            if (players[a].weight > players[b].weight) {
                players[a].score++;
            } else {
                players[b].score++;
            }
        }
    }

    sort(players.begin(), players.end(), comparePlayers);
    cout << players[Q - 1].id << endl;

    return 0;
}
