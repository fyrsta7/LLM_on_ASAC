#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool larger(const vector<int>& l, const vector<int>& r, int pointer = 0) {
    if (pointer >= l.size()) return false;
    if (l[pointer] > r[pointer]) return true;
    if (l[pointer] < r[pointer]) return false;
    return larger(l, r, pointer + 1);
}

void generate_fingers(vector<vector<int>>& fingers, vector<int>& init_finger, int n) {
    fingers.push_back(init_finger);
    while (fingers.size() < fingers.capacity()) {
        vector<int> next_finger = fingers.back();
        next_permutation(next_finger.begin(), next_finger.end());
        if (next_finger == init_finger) break;
        fingers.push_back(next_finger);
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<int> init_finger(N);
    for (int i = 0; i < N; ++i) {
        cin >> init_finger[i];
    }

    int max_size = 1;
    for (int i = 1; i <= N; ++i) {
        max_size *= i;
    }

    vector<vector<int>> fingers;
    fingers.reserve(max_size);
    generate_fingers(fingers, init_finger, N);

    sort(fingers.begin(), fingers.end(), larger);
    auto it = find(fingers.begin(), fingers.end(), init_finger);
    if (it != fingers.end()) {
        int index = distance(fingers.begin(), it) + M;
        if (index < fingers.size()) {
            for (int i = 0; i < N; ++i) {
                cout << fingers[index][i] << " ";
            }
            cout << endl;
        } else {
            cout << "Index out of bounds" << endl;
        }
    } else {
        cout << "Initial finger sequence not found" << endl;
    }

    return 0;
}