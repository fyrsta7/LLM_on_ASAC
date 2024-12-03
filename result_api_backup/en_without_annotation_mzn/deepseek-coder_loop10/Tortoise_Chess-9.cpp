#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> score(N);
    vector<int> cards(M);
    for (int i = 0; i < N; ++i) cin >> score[i];
    for (int i = 0; i < M; ++i) cin >> cards[i];

    sort(cards.begin(), cards.end(), greater<int>());

    int total_score = score[0] + score[N-1];
    int current_position = 0;

    for (int i = 0; i < M; ++i) {
        current_position += cards[i];
        total_score += score[current_position];
    }

    cout << total_score << endl;
    return 0;
}