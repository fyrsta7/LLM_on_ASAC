#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<int> scores(N);
    for (int i = 0; i < N; ++i) {
        cin >> scores[i];
    }

    vector<int> cards(M);
    for (int i = 0; i < M; ++i) {
        cin >> cards[i];
    }

    // Calculate the maximum index that can be reached
    vector<int> reach(N, 0);
    reach[0] = scores[0];

    for (int i = 0; i < M; ++i) {
        vector<int> nextReach = reach;
        for (int j = 0; j < N; ++j) {
            if (reach[j] > 0) {
                int nextPos = j + cards[i];
                if (nextPos < N) {
                    nextReach[nextPos] = max(nextReach[nextPos], reach[j] + scores[nextPos]);
                }
            }
        }
        reach = nextReach;
    }

    cout << *max_element(reach.begin(), reach.end()) << endl;
    return 0;
}