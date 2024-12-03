#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
vector<int> init_finger;

bool larger(const vector<int>& l, const vector<int>& r, int pointer) {
    if (pointer == N) return false;
    if (l[pointer] > r[pointer]) return true;
    if (l[pointer] == r[pointer]) return larger(l, r, pointer + 1);
    return false;
}

int find_position(const vector<vector<int>>& permutations) {
    for (int i = 0; i < permutations.size(); ++i) {
        if (permutations[i] == init_finger) {
            return i;
        }
    }
    return -1;
}

int main() {
    cin >> N >> M;
    init_finger.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> init_finger[i];
    }

    vector<int> permutation(N);
    for (int i = 0; i < N; ++i) {
        permutation[i] = i + 1;
    }

    vector<vector<int>> permutations;
    do {
        permutations.push_back(permutation);
    } while (next_permutation(permutation.begin(), permutation.end()));

    int pos = find_position(permutations);
    if (pos == -1) {
        cout << "Error: Initial finger configuration not found." << endl;
        return 1;
    }

    int ans = (pos + M) % permutations.size();
    for (int i = 0; i < N; ++i) {
        cout << permutations[ans][i] << " ";
    }
    cout << endl;

    return 0;
}
