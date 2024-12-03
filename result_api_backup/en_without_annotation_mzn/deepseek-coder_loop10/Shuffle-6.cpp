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

    auto calculate_object = [&]() {
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            int min_diff = numeric_limits<int>::max();
            for (int j = 0; j < max_times; ++j) {
                if (departure[j] >= T[i]) {
                    min_diff = min(min_diff, departure[j] - T[i]);
                }
            }
            sum += min_diff;
        }
        return sum;
    };

    auto backtrack = [&](int idx, int prev_dep, auto&& backtrack) -> void {
        if (idx == max_times) {
            int obj = calculate_object();
            if (obj < object) {
                object = obj;
            }
            return;
        }

        for (int dep = prev_dep + m; dep <= upper_bound; ++dep) {
            departure[idx] = dep;
            backtrack(idx + 1, dep, backtrack);
        }
    };

    backtrack(0, T.front() - m, backtrack);

    cout << object << endl;
    return 0;
}
