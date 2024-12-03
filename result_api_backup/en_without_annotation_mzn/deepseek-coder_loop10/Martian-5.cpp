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

    vector<int> perm = init_finger;
    for (int i = 0; i < M; ++i) {
        next_permutation(perm.begin(), perm.end());
    }

    for (int i = 0; i < N; ++i) {
        cout << perm[i] << " ";
    }
    cout << endl;

    return 0;
}
