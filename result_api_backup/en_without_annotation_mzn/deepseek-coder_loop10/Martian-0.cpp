#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
vector<int> init_finger;
vector<vector<int>> fingers;

void generate_permutations(vector<int>& current, vector<bool>& used) {
    if (current.size() == N) {
        fingers.push_back(current);
        return;
    }
    for (int i = 1; i <= N; ++i) {
        if (!used[i]) {
            used[i] = true;
            current.push_back(i);
            generate_permutations(current, used);
            current.pop_back();
            used[i] = false;
        }
    }
}

int main() {
    cin >> N >> M;
    init_finger.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> init_finger[i];
    }

    vector<int> current;
    vector<bool> used(N + 1, false);
    generate_permutations(current, used);

    sort(fingers.begin(), fingers.end());

    int idx = 0;
    for (idx = 0; idx < fingers.size(); ++idx) {
        if (fingers[idx] == init_finger) {
            break;
        }
    }

    int ans = (idx + M) % fingers.size();
    for (int i = 0; i < N; ++i) {
        cout << fingers[ans][i] << " ";
    }
    cout << endl;

    return 0;
}
