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
            int min_wait = numeric_limits<int>::max();
            for (int j = 0; j < times; ++j) {
                if (departure[j] >= T[i]) {
                    min_wait = min(min_wait, departure[j] - T[i]);
                }
            }
            if (min_wait == numeric_limits<int>::max()) {
                min_wait = 0;
            }
            object += min_wait;

            int best_j = 0;
            for (int j = 1; j < times; ++j) {
                if (departure[j] < departure[best_j]) {
                    best_j = j;
                }
            }
            departure[best_j] = max(departure[best_j], T[i]) + m;
        }

        if (object < best_object) {
            best_object = object;
            best_departure = departure;
        }
    }

    cout << best_object << endl;

    return 0;
}
