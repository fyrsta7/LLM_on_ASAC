#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Player {
    int id;
    long long score;
    int strength;

    bool operator<(const Player &other) const {
        if (score == other.score) return id < other.id;
        return score > other.score;
    }
};

int main() {
    int N, R, Q;
    cin >> N >> R >> Q;

    vector<Player> players(2 * N);
    
    for (int i = 0; i < 2 * N; ++i) {
        cin >> players[i].score;
        players[i].id = i + 1;  // Player index from 1 to 2N
    }
    
    for (int i = 0; i < 2 * N; ++i) {
        cin >> players[i].strength;
    }

    for (int r = 0; r < R; ++r) {
        sort(players.begin(), players.end());

        for (int i = 0; i < N; ++i) {
            Player &p1 = players[2 * i];
            Player &p2 = players[2 * i + 1];

            if (p1.strength > p2.strength) {
                p1.score += 1;
            } else {
                p2.score += 1;
            }
        }
    }

    sort(players.begin(), players.end());
    
    cout << players[Q - 1].id << endl;
    return 0;
}