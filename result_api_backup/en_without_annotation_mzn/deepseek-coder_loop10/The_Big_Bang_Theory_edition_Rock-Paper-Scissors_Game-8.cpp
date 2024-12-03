#include <iostream>
#include <vector>

using namespace std;

enum Match { draw, lose, win };

int main() {
    int N, NA, NB;
    cin >> N >> NA >> NB;
    
    vector<int> loopA(NA);
    vector<int> loopB(NB);
    
    for (int i = 0; i < NA; ++i) cin >> loopA[i];
    for (int i = 0; i < NB; ++i) cin >> loopB[i];
    
    vector<vector<Match>> table = {
        {draw, lose, win, win, lose},
        {win, draw, lose, win, lose},
        {lose, win, draw, lose, win},
        {lose, lose, win, draw, win},
        {win, win, lose, lose, draw}
    };
    
    int scoreA = 0, scoreB = 0;
    
    for (int i = 0; i < N; ++i) {
        int a = loopA[i % NA];
        int b = loopB[i % NB];
        
        if (table[a][b] == win) ++scoreA;
        if (table[b][a] == win) ++scoreB;
    }
    
    cout << scoreA << " " << scoreB << endl;
    
    return 0;
}
