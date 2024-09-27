#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> score(N);
    vector<int> cards(M);
    
    for (int i = 0; i < N; ++i) {
        cin >> score[i];
    }
    
    for (int i = 0; i < M; ++i) {
        cin >> cards[i];
    }
    
    vector<int> order(M);
    for (int i = 0; i < M; ++i) {
        order[i] = i;
    }
    
    int max_total_score = 0;
    
    do {
        vector<int> stay(M + 1);
        stay[0] = 0;
        for (int i = 0; i < M; ++i) {
            stay[i + 1] = stay[i] + cards[order[i]];
        }
        
        if (stay[M] == N - 1) {
            int total_score = 0;
            for (int i = 0; i <= M; ++i) {
                total_score += score[stay[i]];
            }
            max_total_score = max(max_total_score, total_score);
        }
    } while (next_permutation(order.begin(), order.end()));
    
    cout << max_total_score << endl;
    
    return 0;
}