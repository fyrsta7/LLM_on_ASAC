#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

int L, N, M;
vector<int> D;

bool is_valid_move(vector<bool>& moved) {
    int count = 0;
    for (bool m : moved)
        if (m) count++;
    return count <= M;
}

int calculate_mindist(const vector<int>& D, const vector<bool>& moved, int L, int N) {
    int predist = INT_MAX;
    for (int i = 0; i < N-1; ++i) {
        if (!moved[i]) {
            for (int j = i+1; j < N; ++j) {
                if (!moved[j]) {
                    predist = min(predist, abs(D[i] - D[j]));
                }
            }
        }
    }

    int predist2 = INT_MAX;
    for (int i = 0; i < N; ++i) {
        if (!moved[i]) {
            predist2 = min(predist2, min(D[i], L - D[i]));
        }
    }
    
    return min(predist, predist2);
}

void maximize_mindist(int index, vector<bool>& moved, int& max_dist) {
    if (!is_valid_move(moved)) return;

    if (index == N) {
        max_dist = max(max_dist, calculate_mindist(D, moved, L, N));
        return;
    }

    moved[index] = true;
    maximize_mindist(index + 1, moved, max_dist);

    moved[index] = false;
    maximize_mindist(index + 1, moved, max_dist);
}

int main() {
    cin >> L >> N >> M;
    D.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> D[i];
    }

    vector<bool> moved(N, false);
    int max_dist = INT_MIN;
    maximize_mindist(0, moved, max_dist);

    cout << "mindist=" << max_dist << endl;
    return 0;
}