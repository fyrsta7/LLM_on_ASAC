#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> outcome = {
    { 0, -1,  1,  1, -1}, // Scissors
    { 1,  0, -1,  1, -1}, // Rock
    {-1,  1,  0, -1,  1}, // Paper
    {-1, -1,  1,  0,  1}, // Lizard
    { 1,  1, -1, -1,  0}  // Spock
};

int main() {
    int N, NA, NB;
    cin >> N >> NA >> NB;

    vector<int> cycleA(NA);
    vector<int> cycleB(NB);

    for (int i = 0; i < NA; i++) {
        cin >> cycleA[i];
    }

    for (int i = 0; i < NB; i++) {
        cin >> cycleB[i];
    }

    int scoreA = 0, scoreB = 0;
    for (int i = 0; i < N; i++) {
        int moveA = cycleA[i % NA];
        int moveB = cycleB[i % NB];

        int result = outcome[moveA][moveB];
        if (result == 1) {
            scoreA++;
        } else if (result == -1) {
            scoreB++;
        }
    }

    cout << scoreA << " " << scoreB << endl;

    return 0;
}