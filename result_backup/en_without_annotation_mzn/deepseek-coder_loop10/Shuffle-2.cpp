#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> T(n);
    for (int i = 0; i < n; ++i) {
        cin >> T[i];
    }

    sort(T.begin(), T.end());

    int upper_bound = T.back() + m;
    int max_times = min(T.back() / m + 1, n);

    vector<int> departure(max_times, 0);
    int object = numeric_limits<int>::max();

    for (int times = 1; times <= max_times; ++times) {
        vector<int> current_departure(times, 0);
        int current_object = 0;

        for (int i = 0; i < n; ++i) {
            int min_wait = numeric_limits<int>::max();
            for (int j = 0; j < times; ++j) {
                if (current_departure[j] < T[i]) continue;
                min_wait = min(min_wait, current_departure[j] - T[i]);
            }
            if (min_wait == numeric_limits<int>::max()) {
                current_departure[0] = T[i] + m;
                min_wait = 0;
            }
            current_object += min_wait;
        }

        if (current_object < object) {
            object = current_object;
            departure = current_departure;
        }
    }

    cout << object << endl;

    return 0;
}
