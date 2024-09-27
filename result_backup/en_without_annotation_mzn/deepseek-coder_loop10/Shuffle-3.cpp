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

    int best_object = numeric_limits<int>::max();
    vector<int> best_departure;

    for (int times = 1; times <= max_times; ++times) {
        vector<int> departure(times, 0);
        int object = 0;

        for (int i = 0; i < n; ++i) {
            int min_delay = numeric_limits<int>::max();
            for (int j = 0; j < times; ++j) {
                if (departure[j] >= T[i]) {
                    min_delay = min(min_delay, departure[j] - T[i]);
                }
            }
            if (min_delay == numeric_limits<int>::max()) {
                departure[0] = T[i];
                min_delay = 0;
            }
            object += min_delay;
            for (int j = 0; j < times; ++j) {
                if (departure[j] >= T[i] && departure[j] - T[i] == min_delay) {
                    departure[j] += m;
                    break;
                }
            }
        }

        if (object < best_object) {
            best_object = object;
            best_departure = departure;
        }
    }

    cout << best_object << endl;

    return 0;
}
