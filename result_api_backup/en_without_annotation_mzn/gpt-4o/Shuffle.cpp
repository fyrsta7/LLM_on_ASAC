#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> T(n);
    for (int i = 0; i < n; i++) {
        cin >> T[i];
    }
    
    int upper_bound = *max_element(T.begin(), T.end()) + m;
    int max_times = min(*max_element(T.begin(), T.end()) / m + 1, n);
    vector<int> departure(max_times, 0);
    int object = INT_MAX;

    for (int times = 1; times <= max_times; times++) {
        for (int i = 0; i < times; i++) {
            departure[i] = i * m;
        }

        int dep_idx = 0;
        int current_object = 0;

        for (int i = 0; i < n; i++) {
            while (dep_idx < times - 1 && departure[dep_idx] < T[i]) {
                dep_idx++;
            }
            if (departure[dep_idx] < T[i]) {
                dep_idx++;
                for (int j = dep_idx; j < times; j++) {
                    departure[j] = departure[j-1] + m;
                }
            }
            current_object += departure[dep_idx] - T[i];
        }

        object = min(object, current_object);
    }

    cout << object << endl;
    return 0;
}