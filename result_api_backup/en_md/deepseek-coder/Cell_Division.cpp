#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
    int N, m1, m2;
    cin >> N >> m1 >> m2;
    vector<int> S(N);
    for (int i = 0; i < N; ++i) {
        cin >> S[i];
    }

    long long M = 1;
    for (int i = 0; i < m2; ++i) {
        M *= m1;
    }

    int min_time = -1;
    for (int i = 0; i < N; ++i) {
        int time = 0;
        long long cells = 1;
        while (cells < M) {
            cells *= S[i];
            ++time;
        }
        if (cells % M == 0) {
            if (min_time == -1 || time < min_time) {
                min_time = time;
            }
        }
    }

    cout << min_time << endl;
    return 0;
}
