#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int N;
    cin >> N;
    long long m1, m2;
    cin >> m1 >> m2;
    long long M = pow(m1, m2);
    
    vector<int> S(N);
    for (int i = 0; i < N; ++i) {
        cin >> S[i];
    }

    int min_time = INT_MAX;
    for (int i = 0; i < N; ++i) {
        long long count = 1;
        int time = 0;
        while (count < M) {
            count *= S[i];
            ++time;
            if (count % M == 0) {
                min_time = min(min_time, time);
                break;
            }
        }
    }

    if (min_time == INT_MAX) {
        cout << -1 << endl;
    } else {
        cout << min_time << endl;
    }

    return 0;
}