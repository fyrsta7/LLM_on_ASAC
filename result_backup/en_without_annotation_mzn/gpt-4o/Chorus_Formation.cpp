#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> T(N);
    for (int i = 0; i < N; i++) {
        cin >> T[i];
    }

    int min_discard = INT_MAX;

    for (int mask = 0; mask < (1 << N); mask++) {
        vector<bool> Select(N);
        vector<int> selected, discarded;
        int discard_count = 0;
        for (int i = 0; i < N; i++) {
            if (mask & (1 << i)) {
                Select[i] = true;
                selected.push_back(T[i]);
            } else {
                Select[i] = false;
                discard_count++;
            }
        }

        bool valid = true;
        for (int i = 0; i < N; i++) {
            if (!Select[i]) {
                valid = true;
                for (int j = 0; j < N; j++) {
                    for (int k = 0; k < N; k++) {
                        if (!(j >= k || Select[j] || Select[k] || ((k > i || T[j] < T[k]) && (j < i || T[j] > T[k])))) {
                            valid = false;
                            break;
                        }
                    }
                    if (!valid) break;
                }
                if (!valid) break;
            }
        }

        if (valid) {
            min_discard = min(min_discard, discard_count);
        }
    }

    cout << min_discard << endl;

    return 0;
}