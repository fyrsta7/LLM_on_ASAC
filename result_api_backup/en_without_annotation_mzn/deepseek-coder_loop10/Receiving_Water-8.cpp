#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> w(n);
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
    }

    vector<int> start(n, 0);
    vector<int> choice(n, 0);
    vector<int> latest(m, 0);

    for (int i = 0; i < m; ++i) {
        choice[i] = i;
    }

    for (int i = m; i < n; ++i) {
        vector<int> min_start(m, numeric_limits<int>::max());
        for (int j = 0; j < m; ++j) {
            min_start[j] = start[latest[j]] + w[latest[j]];
        }
        int min_val = *min_element(min_start.begin(), min_start.end());
        int chosen_machine = 0;
        for (int j = 0; j < m; ++j) {
            if (min_start[j] == min_val) {
                chosen_machine = j;
                break;
            }
        }
        start[i] = min_val;
        choice[i] = chosen_machine;
        latest[chosen_machine] = i;
    }

    int max_time = 0;
    for (int i = 0; i < n; ++i) {
        max_time = max(max_time, start[i] + w[i]);
    }

    cout << max_time << endl;

    return 0;
}