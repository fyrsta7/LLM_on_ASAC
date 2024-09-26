#include <iostream>
#include <vector>
#include <string>

using namespace std;

int ccw(int start, int num, int n) {
    return (start + num - 1) % n + 1;
}

int cw(int start, int num, int n) {
    return (start + n - num - 1) % n + 1;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> face(n);
    vector<string> person(n);
    for (int i = 0; i < n; ++i) {
        cin >> face[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> person[i];
    }

    vector<pair<int, int>> instruction(m);
    for (int i = 0; i < m; ++i) {
        cin >> instruction[i].first >> instruction[i].second;
    }

    vector<int> state(m + 1);
    state[0] = 1;

    for (int i = 1; i <= m; ++i) {
        if ((face[state[i-1] - 1] == 0 && instruction[i-1].first == 0) || 
            (face[state[i-1] - 1] == 1 && instruction[i-1].first == 1)) {
            state[i] = cw(state[i-1], instruction[i-1].second, n);
        } else {
            state[i] = ccw(state[i-1], instruction[i-1].second, n);
        }
    }

    cout << person[state[m] - 1] << endl;

    return 0;
}