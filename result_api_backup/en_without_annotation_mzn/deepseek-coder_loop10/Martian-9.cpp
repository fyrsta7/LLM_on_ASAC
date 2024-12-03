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
        int i = N - 2;
        while (i >= 0 && current[i] >= current[i + 1]) {
            --i;
        }
        if (i < 0) {
            reverse(current.begin(), current.end());
        } else {
            int j = N - 1;
            while (current[j] <= current[i]) {
                --j;
            }
            swap(current[i], current[j]);
            reverse(current.begin() + i + 1, current.end());
        }
    }

    for (int i = 0; i < N; ++i) {
        cout << current[i] << " ";
    }
    cout << endl;

    return 0;
}