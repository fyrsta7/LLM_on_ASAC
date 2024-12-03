#include <iostream>
#include <vector>

int main() {
    int N, NA, NB;
    std::cin >> N >> NA >> NB;
    
    std::vector<int> loopA(NA);
    std::vector<int> loopB(NB);
    
    for (int i = 0; i < NA; ++i) std::cin >> loopA[i];
    for (int i = 0; i < NB; ++i) std::cin >> loopB[i];
    
    std::vector<std::vector<int>> table = {
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
        if (table[a][b] == 1) ++scoreA;
        else if (table[a][b] == -1) ++scoreB;
    }
    
    std::cout << scoreA << " " << scoreB << std::endl;
    
    return 0;
}
