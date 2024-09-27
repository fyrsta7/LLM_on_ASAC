#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> T(n);
    for (int i = 0; i < n; ++i) {
        cin >> T[i];
    }

    int upper_bound = *max_element(T.begin(), T.end()) + m;
    int max_times = min((*max_element(T.begin(), T.end())) / m + 1, n);

    vector<int> departure(max_times, INT_MAX);
    departure[0] = *min_element(T.begin(), T.end());

    for (int i = 1; i < max_times; ++i) {
        departure[i] = departure[i-1] + m;
    }

    int object = 0;
    for (int i = 0; i < n; ++i) {
        int min_diff = INT_MAX;
        for (int j = 0; j < max_times; ++j) {
            if (departure[j] >= T[i]) {
                min_diff = min(min_diff, departure[j] - T[i]);
            }
        }
        object += min_diff;
    }

    cout << object << endl;
    return 0;
}