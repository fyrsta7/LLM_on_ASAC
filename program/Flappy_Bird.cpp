#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<pair<int, int>> tap(n);
    for (int i = 0; i < n; i++) {
        cin >> tap[i].first >> tap[i].second;
    }

    vector<pair<int, int, int>> pipes(k);
    for (int i = 0; i < k; i++) {
        cin >> pipes[i].first >> pipes[i].second >> pipes[i].third;
    }

    bool canComplete = true;
    int minTaps = 0, maxGaps = 0;
    int birdHeight = m;

    for (int i = 0; i < n; i++) {
        if (birdHeight == 0) {
            canComplete = false;
            break;
        }

        birdHeight += tap[i].first;
        birdHeight = min(birdHeight, m);

        for (auto pipe : pipes) {
            if (i == pipe.first && (birdHeight <= pipe.second || birdHeight >= pipe.third)) {
                canComplete = false;
                break;
            }
        }

        birdHeight -= tap[i].second;
        birdHeight = max(birdHeight, 0);

        if (birdHeight == 0) {
            break;
        }

        if (birdHeight == m) {
            minTaps++;
        }

        maxGaps = max(maxGaps, birdHeight);
    }

    cout << (canComplete ? 1 : 0) << endl;
    cout << (canComplete ? minTaps : maxGaps) << endl;

    return 0;
}