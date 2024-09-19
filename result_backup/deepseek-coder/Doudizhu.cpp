#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_RANK = 15;
const int MAX_SUIT = 4;

int main() {
    int T, n;
    cin >> T >> n;
    while (T--) {
        vector<int> count(MAX_RANK, 0);
        vector<vector<int>> cards(MAX_RANK, vector<int>(MAX_SUIT, 0));
        for (int i = 0; i < n; ++i) {
            int a, b;
            cin >> a >> b;
            if (a == 0) a = 14 + b; // Jokers
            else if (a == 1) a = 13; // Ace
            else a -= 2; // Adjust for 3-K
            count[a]++;
            cards[a][b - 1]++;
        }

        int turns = 0;
        for (int i = 0; i < MAX_RANK; ++i) {
            if (count[i] == 0) continue;
            turns += count[i];
            if (count[i] >= 2) {
                int pairs = count[i] / 2;
                turns -= pairs;
                count[i] -= pairs * 2;
            }
            if (count[i] >= 3) {
                int triples = count[i] / 3;
                turns -= triples;
                count[i] -= triples * 3;
            }
            if (count[i] >= 4) {
                int quadruples = count[i] / 4;
                turns -= quadruples;
                count[i] -= quadruples * 4;
            }
        }

        cout << turns << endl;
    }
    return 0;
}
