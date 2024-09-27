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

    int upper_bound = *max_element(T.begin(), T.end()) + m;
    int max_times = min(upper_bound / m + 1, n);

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

    auto backtrack = [&](int k, auto&& backtrack) -> void {
        if (k == max_times) {
            object = min(object, calculate_object());
            return;
        }
        for (int d = (k == 0 ? 0 : departure[k-1] + m); d <= upper_bound; ++d) {
            departure[k] = d;
            backtrack(k + 1, backtrack);
        }
    };

    backtrack(0, backtrack);

    cout << object << endl;
    return 0;
}