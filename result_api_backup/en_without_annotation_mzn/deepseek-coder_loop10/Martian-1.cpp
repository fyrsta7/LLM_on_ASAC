#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> init_finger(N);
    for (int i = 0; i < N; ++i) {
        cin >> init_finger[i];
    }

    vector<int> current = init_finger;
    for (int m = 0; m < M; ++m) {
        int idx = N - 2;
        while (idx >= 0 && current[idx] >= current[idx + 1]) {
            --idx;
        }
        if (idx < 0) {
            reverse(current.begin(), current.end());
        } else {
            int idx2 = N - 1;
            while (current[idx2] <= current[idx]) {
                --idx2;
            }
            swap(current[idx], current[idx2]);
            reverse(current.begin() + idx + 1, current.end());
        }
    }

    for (int i = 0; i < N; ++i) {
        cout << current[i] << " ";
    }
    cout << endl;

    return 0;
}