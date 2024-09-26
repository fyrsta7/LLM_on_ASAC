#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, NA, NB;
    cin >> N >> NA >> NB;
    vector<int> loopA(NA), loopB(NB);
    for (int i = 0; i < NA; ++i) cin >> loopA[i];
    for (int i = 0; i < NB; ++i) cin >> loopB[i];

    vector<vector<char>> table = {
        {'D', 'L', 'W', 'W', 'L'},
        {'W', 'D', 'L', 'W', 'L'},
        {'L', 'W', 'D', 'L', 'W'},
        {'L', 'L', 'W', 'D', 'W'},
        {'W', 'W', 'L', 'L', 'D'} 
    };  

    int scoreA = 0, scoreB = 0;
    for (int i = 0; i < N; ++i) {
        int moveA = loopA[i % NA];
        int moveB = loopB[i % NB];
        if (table[moveA][moveB] == 'W') ++scoreA;
        if (table[moveB][moveA] == 'W') ++scoreB;
    }
    
    cout << scoreA << " " << scoreB << endl;
    return 0;
}