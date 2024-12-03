#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Card {
    int value;
    int index;
};

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> score(N);
    for (int i = 0; i < N; ++i) cin >> score[i];

    vector<Card> cards(M);
    for (int i = 0; i < M; ++i) {
        int val;
        cin >> val;
        cards[i] = {val, i+1};
    }

    sort(cards.begin(), cards.end(), [](const Card &a, const Card &b) { return a.value < b.value; });

    vector<int> order(M), stay(M+1, 1);
    for (int i = 0; i < M; ++i) {
        order[i] = cards[i].index;
        stay[i+1] = stay[i] + cards[i].value;
        if (stay[i+1] > N) { 
            cout << -1 << endl;
            return 0;
        }
    }
    stay[M] = N;  // Ensure last entry matches constraint
    
    int total_score = accumulate(stay.begin(), stay.end(), 0, [&](int acc, int s) { return acc + score[s-1]; });

    cout << total_score << endl;
    return 0;
}