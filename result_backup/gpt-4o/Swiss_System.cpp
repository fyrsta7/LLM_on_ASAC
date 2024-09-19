#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Player {
    int id;
    int score;
    int strength;
};

int main() {
    int N, R, Q;
    cin >> N >> R >> Q;
    
    vector<Player> players(2*N);
    
    for (int i = 0; i < 2*N; ++i) {
        cin >> players[i].score;
        players[i].id = i + 1;
    }
    
    for (int i = 0; i < 2*N; ++i) {
        cin >> players[i].strength;
    }
    
    auto compare = [](const Player &a, const Player &b) {
        if (a.score == b.score)
            return a.id < b.id;
        return a.score > b.score;
    };
    
    for (int r = 0; r < R; ++r) {
        sort(players.begin(), players.end(), compare);
        
        vector<Player> next_round;
        
        for (int i = 0; i < 2*N; i += 2) {
            if (players[i].strength > players[i+1].strength) {
                players[i].score++;
                next_round.push_back(players[i]);
                next_round.push_back(players[i+1]);
            } else {
                players[i+1].score++;
                next_round.push_back(players[i+1]);
                next_round.push_back(players[i]);
            }
        }
        
        players = next_round;
    }
    
    sort(players.begin(), players.end(), compare);
    
    cout << players[Q-1].id << endl;
    
    return 0;
}