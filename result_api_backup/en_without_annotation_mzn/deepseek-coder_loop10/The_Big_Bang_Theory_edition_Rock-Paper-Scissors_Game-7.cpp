#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, NA, NB;
    cin >> N >> NA >> NB;
    
    vector<int> loopA(NA), loopB(NB);
    for (int i = 0; i < NA; ++i) cin >> loopA[i];
    for (int i = 0; i < NB; ++i) cin >> loopB[i];
    
    vector<vector<int>> table = {
        {0, -1, 1, 1, -1},
        {1, 0, -1, 1, -1},
        {-1, 1, 0, -1, 1},
        {-1, -1, 1, 0, 1},
        {1, 1, -1, -1, 0}
    };
    
    int scoreA = 0, scoreB = 0;
    
    for (int i = 0; i < N; ++i) {
        int a = loopA[i % NA];
        int b = loopB[i % NB];
        if (table[a][b] == 1) scoreA++;
        else if (table[a][b] == -1) scoreB++;
    }
    
    cout << scoreA << " " << scoreB << endl;
    
    return 0;
}
