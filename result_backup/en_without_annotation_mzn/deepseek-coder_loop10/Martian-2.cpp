#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
vector<int> init_finger;
vector<vector<int>> fingers;

void generatePermutations(vector<int>& perm, vector<bool>& used, int depth) {
    if (depth == N) {
        fingers.push_back(perm);
        return;
    }
    for (int i = 1; i <= N; ++i) {
        if (!used[i]) {
            used[i] = true;
            perm[depth] = i;
            generatePermutations(perm, used, depth + 1);
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

    vector<int> perm(N);
    vector<bool> used(N + 1, false);
    generatePermutations(perm, used, 0);

    sort(fingers.begin(), fingers.end());

    int idx = -1;
    for (int i = 0; i < fingers.size(); ++i) {
        if (fingers[i] == init_finger) {
            idx = i;
            break;
        }
    }

    if (idx == -1 || idx + M >= fingers.size()) {
        cout << "No valid answer" << endl;
    } else {
        for (int i = 0; i < N; ++i) {
            cout << fingers[idx + M][i] << " ";
        }
        cout << endl;
    }

    return 0;
}
