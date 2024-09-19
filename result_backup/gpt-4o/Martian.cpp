#include <iostream>
#include <vector>
#include <algorithm>
void PermutationToIndex(const std::vector<int> &perm, std::vector<int> &fact, int &idx) {
    int N = perm.size();
    std::vector<int> pos(N);
    for (int i = 0; i < N; ++i)
        pos[perm[i] - 1] = i;
    idx = 0;
    for (int i = 0; i < N; ++i) {
        idx += pos[i] * fact[N - 1 - i];
        for (int j = i + 1; j < N; ++j) {
            if (pos[j] > pos[i])
                pos[j]--;
        }
    }
}

void IndexToPermutation(int idx, const std::vector<int> &fact, std::vector<int> &perm) {
    int N = perm.size();
    std::vector<bool> used(N, false);
    for (int i = 0; i < N; ++i) {
        int q = idx / fact[N - 1 - i];
        idx %= fact[N - 1 - i];
        int count = -1;
        for (int j = 0; j < N; ++j) {
            if (!used[j])
                count++;
            if (count == q) {
                perm[i] = j + 1;
                used[j] = true;
                break;
            }
        }
    }
}

int main() {
    int N, M;
    std::cin >> N >> M;
    std::vector<int> perm(N);
    for (int i = 0; i < N; ++i)
        std::cin >> perm[i];
    
    std::vector<int> fact(N + 1, 1);
    for (int i = 2; i <= N; ++i)
        fact[i] = fact[i - 1] * i;
    
    int idx;
    PermutationToIndex(perm, fact, idx);
    
    idx += M;
    
    IndexToPermutation(idx, fact, perm);
    
    for (int i = 0; i < N; ++i) {
        if (i > 0)
            std::cout << ' ';
        std::cout << perm[i];
    }
    
    return 0;
}