#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int main() {
    int L, N, M;
    cin >> L >> N >> M;
    vector<int> D(N);
    for (int i = 0; i < N; ++i) {
        cin >> D[i];
    }

    sort(D.begin(), D.end());

    int predist = numeric_limits<int>::max();
    for (int i = 0; i < N - 1; ++i) {
        predist = min(predist, D[i + 1] - D[i]);
    }

    int predist2 = min(D[0], L - D[N - 1]);

    int mindist = min(predist, predist2);

    vector<int> diffs(N - 1);
    for (int i = 0; i < N - 1; ++i) {
        diffs[i] = D[i + 1] - D[i];
    }

    sort(diffs.begin(), diffs.end());

    for (int i = 0; i < min(M, N - 1); ++i) {
        mindist = max(mindist, diffs[i]);
    }

    cout << "mindist=" << mindist << endl;

    return 0;
}
