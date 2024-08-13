#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct General {
    int id;
    vector<int> bonding;
};

int main() {
    int N;
    cin >> N;
    
    vector<vector<int>> bonding_matrix(N, vector<int>(N, 0));
    
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            cin >> bonding_matrix[i][j];
            bonding_matrix[j][i] = bonding_matrix[i][j];
        }
    }

    vector<int> generals(N);
    for (int i = 0; i < N; ++i) {
        generals[i] = i;
    }

    auto calculate_max_bond = [&](vector<int> &team) {
        int max_bond = 0;
        int team_size = team.size();
        for (int i = 0; i < team_size; ++i) {
            for (int j = i + 1; j < team_size; ++j) {
                max_bond = max(max_bond, bonding_matrix[team[i]][team[j]]);
            }
        }
        return max_bond;
    };

    int max_winning_bond = 0;
    bool can_win = false;

    do {
        vector<int> xiao_han_team, computer_team;
        
        for (int i = 0; i < N; ++i) {
            if (i % 2 == 0)
                xiao_han_team.push_back(generals[i]);
            else
                computer_team.push_back(generals[i]);
        }

        int xiao_han_max_bond = calculate_max_bond(xiao_han_team);
        int computer_max_bond = calculate_max_bond(computer_team);
        
        if (xiao_han_max_bond > computer_max_bond) {
            can_win = true;
            max_winning_bond = max(max_winning_bond, xiao_han_max_bond);
        }
    } while (next_permutation(generals.begin(), generals.end()));

    if (can_win) {
        cout << 1 << endl;
        cout << max_winning_bond << endl;
    } else {
        cout << 0 << endl;
    }
    
    return 0;
}